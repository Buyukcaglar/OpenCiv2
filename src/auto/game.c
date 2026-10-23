/* The game, the game: start-up, turns, saving, scenarios, events, cheats: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00411bd7 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl cheat_throneroom_upgrade(void)

{
  throneroom_show_upgrade(human_civ);
  return;
}
#undef human_civ

/* 0041325d auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
void __cdecl eot_blink_timer_tick(void)

{
  if ((unit_blink_active != '\0') && (game_loop_active != '\0')) {
    status_end_turn_blink_phase = status_end_turn_blink_phase == '\0';
    status_draw_end_of_turn(1);
  }
  return;
}
#undef game_loop_active
#undef unit_blink_active

/* 00419170 auto */
#define event_dont_play_wonders (*(int *)((u8 *)&g.d_006a9110))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_time_limit_ms (*(i32 *)((u8 *)&g.d_00654b70))
#define net_claimed_civs_mask (*(i16 *)((u8 *)&g.d_00654fb0))
#define prefs_hotseat_menu_choice (*(short *)((u8 *)&g.d_0066653c))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(1080)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1084)))
#define map_source (*(i32 *)(frame_ + FRAME_OFF(1840)))
#define num_players (*(int *)(frame_ + FRAME_OFF(1844)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1848)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1852)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(1856)))
i32 __cdecl setup_hotseat_game(void)

{
  int choice;
  i32 result;
  i8 frame_[FRAME_OFF(1864)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  palette_init(&palette);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  for (i = 0; i < 8; i++) {
    *(i16 *)(&civ_intro_shown + i * 2) = 0;
  }
  mp_turn_time_limit_ms = 0;
  game.multiplayer = 1;
LAB_004191ff:
  surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
  wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
  wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
  wnd_flush_paint();
  setup_dialog_pos_state = 3;
  setup_show_side_picture(0xffffffff,0);
  dlg_load_game_section(&dlg,ADDR(0x6252a4, ((u8 *)&g.d_006252a4)),1);
  dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_hotseat_menu_choice);
  crt_strcpy(&scenario_dir_path,&game_home_dir);
  choice = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
  result = setup_next_dialog_x(0);
  dialog_set_position((DialogCore *)&dlg,result,choice);
  choice = dlg_show_modal(&dlg,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((ViewWindow *)&setup_picwnd);
  if (choice < 0) {
    eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
    /* inlined unwind funclet 00419940 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 0041994c */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
    result = 1;
LAB_00419962:
    return result;
  }
  prefs_hotseat_menu_choice = (short)choice;
  if ((-1 < choice) && (choice < 3)) {
    __chdir(&game_home_dir);
    rules_load(1);
  }
  scenario_events_loaded = 0;
  switch(choice) {
  case 0:
    choice = setup_choose_map_size();
    if (choice != 0) goto LAB_004191ff;
    map_source = 0;
    choice = _rand();
    mapgen_land_mass = choice % 3 - 1;
    mapgen_land_form = 0;
    choice = _rand();
    if (choice % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    choice = _rand();
    mapgen_temperature = choice % 3 - 1;
    choice = _rand();
    mapgen_climate = choice % 3 - 1;
    choice = _rand();
    mapgen_age = choice % 3 - 1;
    choice = setup_choose_game_options(map_source,1);
    break;
  case 1:
    choice = map_load_dialog();
    if (choice != 0) goto LAB_004191ff;
    map_source = 1;
    if (map.flat != 0) {
      map_source = 2;
    }
    choice = _rand();
    mapgen_land_mass = choice % 3 - 1;
    mapgen_land_form = 0;
    choice = _rand();
    if (choice % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    choice = _rand();
    mapgen_temperature = choice % 3 - 1;
    choice = _rand();
    mapgen_climate = choice % 3 - 1;
    choice = _rand();
    mapgen_age = choice % 3 - 1;
    choice = setup_choose_game_options(map_source,1);
    break;
  case 2:
    choice = setup_choose_map_size();
    if (choice != 0) goto LAB_004191ff;
    map_source = 0;
    choice = setup_custom_world();
    if (choice != 0) goto LAB_004191ff;
    choice = setup_choose_game_options(map_source,1);
    break;
  case 3:
    event_dont_play_wonders = 0;
    choice = scenario_start_dialog(1);
    if (choice == 0) {
      if (event_dont_play_wonders != 0) {
        game.game_options = game.game_options & 0xfffeffff;
      }
      game.multiplayer = 1;
      num_players = setup_choose_hotseat_players();
      if (num_players == 0) {
        crt_strcpy(&scenario_dir_path,&game_home_dir);
      }
      else {
        choice = scenario_pick_human_civs(num_players);
        if (choice == 0) {
          text_clear();
          text_append_label(0x363);
          menu_add_item((GameMenu *)&main_menu,1,0x1f2,ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
          prefs_save_civ2dat();
          surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
          wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
          wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
          wnd_flush_paint();
          eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
          /* inlined unwind funclet 00419940 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
          eh_state = 0xffffffff;
          /* inlined unwind funclet 0041994c */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
          result = 0;
          goto LAB_00419962;
        }
        crt_strcpy(&scenario_dir_path,&game_home_dir);
      }
    }
    else {
      crt_strcpy(&scenario_dir_path,&game_home_dir);
    }
    goto LAB_004191ff;
  case 4:
    event_dont_play_wonders = 0;
    choice = game_load_dialog(0,1,1);
    if (choice == 0) {
      if (game.multiplayer != 1) goto code_r0x004196cc;
      text_clear();
      text_append_label(0x363);
      menu_add_item((GameMenu *)&main_menu,1,0x1f2,ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
      prefs_save_civ2dat();
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      wnd_flush_paint();
      eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
      /* inlined unwind funclet 00419940 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0041994c */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      result = 0;
      goto LAB_00419962;
    }
    if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    goto LAB_004191ff;
  default:
    goto switchD_004197af_default;
  }
  if (choice == 0) {
switchD_004197af_default:
    net_claimed_civs_mask = 0;
LAB_004197d3:
    game.civs_alive = '\0';
    game.human_players = '\0';
    num_players = setup_choose_hotseat_players();
    if (num_players != 0) {
      leaders_reset_custom_names();
      for (i = 0; i < num_players; i++) {
        while (choice = setup_choose_tribe(i,1,0), choice != 0) {
          i--;
          if (i < 0) goto LAB_004197d3;
        }
      }
      setup_choose_opponents(num_players);
      prefs_save_civ2dat();
      rules_load_advances(1);
      rules_load_units(1);
      rules_load_improvements(1);
      snd_menu_end();
      map_generate(map_source);
      game_init_new();
      if (setup_accelerated_start != 0) {
        game_accelerated_start(setup_accelerated_start - 1);
      }
      game.multiplayer = 1;
      if (turn_resume_civ != '\0') {
        game.player_civ = turn_resume_civ;
        human_civ = (iptr)turn_resume_civ;
      }
      text_clear();
      text_append_label(0x363);
      menu_add_item((GameMenu *)&main_menu,1,0x1f2,ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
      eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
      /* inlined unwind funclet 00419940 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0041994c */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      result = 0;
      goto LAB_00419962;
    }
  }
  goto LAB_004191ff;
code_r0x004196cc:
  popup_game_with_sprite(ADDR(0x6252b0, ((u8 *)&g.d_006252b0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  if (event_dont_play_wonders != 0) {
    game.game_options = game.game_options & 0xfffeffff;
  }
  goto LAB_004191ff;
}
#undef event_dont_play_wonders
#undef human_civ
#undef mp_turn_time_limit_ms
#undef net_claimed_civs_mask
#undef prefs_hotseat_menu_choice
#undef scenario_events_loaded
#undef screen_height
#undef turn_resume_civ
#undef palette
#undef i
#undef dlg
#undef map_source
#undef num_players
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00419c20 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl setup_backdrop_surface_global_init(void)

{
  setup_backdrop_surface_static_init();
  setup_backdrop_surface_reg_atexit();
  return;
}

/* 00419c3a auto */
void __cdecl setup_backdrop_surface_static_init(void)

{
  surface_ctor((DibSurface *)&setup_backdrop_surface);
  return;
}

/* 00419c54 auto */
void __cdecl setup_backdrop_surface_reg_atexit(void)

{
  _atexit(setup_backdrop_surface_atexit_dtor);
  return;
}

/* 00419c71 auto */
void __cdecl setup_backdrop_surface_atexit_dtor(void)

{
  surface_dtor((DibSurface *)&setup_backdrop_surface);
  return;
}

/* 0041b48f auto */
#define app_shutdown_done (*(i32 *)((u8 *)&g.d_0062c5b0))
#define game_session_active (*(int *)((u8 *)&g.d_006252c4))
void __cdecl app_fatal_cleanup(void)

{
  if (game_session_active != 0) {
    game_session_end();
  }
  app_shutdown_cleanup();
  app_shutdown_done = 1;
  return;
}
#undef app_shutdown_done
#undef game_session_active

/* 0041b4c0 auto */
#define autoplay_active (*(i16 *)((u8 *)&g.d_00654fa8))
#define main_frame_nonclient_width (*(int *)((u8 *)&g.d_006acbb0))
#define main_view_timer_shown (*(i32 *)((u8 *)&g.d_0066c988))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define i (*(int *)(frame_ + FRAME_OFF(4)))
i32 __cdecl app_startup_init(void)

{
  i32 result;
  int rc;
  UINT UVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  crt_strcpy(&game_txt_path,&startup_game_txt_name_str);
  crt_strcpy(&rules_txt_path,s_RULES_006253f0);
  __getcwd(&game_home_dir,0x104);
  crt_strcpy(&scenario_dir_path,&game_home_dir);
  for (i = 0; i < 8; i++) {
    *(i16 *)(&map_view_open_flags + i * 0x3f0) = 0;
    (&main_view_timer_shown)[i * 0xfc] = 0;
  }
  timeBeginPeriod(4);
  result = timer_ticks();
  crt_srand(result);
  result = timer_ticks();
  rng_set_seed(result);
  dialog_set_colors(0x10,0x21,0x25,0x1a,0x1d,0x25,0x12,0x1a,10);
  ui_set_radio_text_color(0x10);
  ui_set_radio_text_shadow(0x21,1,1);
  ui_set_radio_disabled_color(0x1a);
  ui_set_ctrl_text_color(0x10);
  ui_set_ctrl_text_shadow(0x21,1,1);
  dialog_set_list_colors(0x23,10,10,0x17,0x29,10,0x12);
  gfx_load_game_sprites();
  registry_load_default_language();
  game_language = registry_language_id - 1;
  if (2 < game_language) {
    game_language = 0;
  }
  crt_strcpy(&lang_file_ext,&startup_lang_default_ext_str);
  switch(registry_language_id) {
  case 1:
    crt_strcpy(&lang_file_ext,&startup_lang_english_ext_str);
    break;
  case 2:
    crt_strcpy(&lang_file_ext,&startup_lang_french_ext_str);
    break;
  case 3:
    crt_strcpy(&lang_file_ext,&startup_lang_german_ext_str);
    break;
  case 4:
    crt_strcpy(&lang_file_ext,&startup_lang_italian_ext_str);
    break;
  case 5:
    crt_strcpy(&lang_file_ext,&startup_lang_spanish_ext_str);
  }
  text_section_index_build(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),0x4000);
  rc = text_open_section((iptr)PTR_s_LABELS_00627674,ADDR(0x625410, ((u8 *)&g.d_00625410)));
  if (rc == 0) {
    text_read_line(1);
    rc = text_next_int();
    if (strpool_capacity < rc) {
      strpool_capacity = rc;
    }
  }
  strpool_init(strpool_capacity);
  strpool_add(ADDR(0x62541c, ((u8 *)&g.d_0062541c)));
  labels_load();
  dialog_load_button_labels();
  prefs_load_civ2dat();
  game.game_options = prefs_game_options;
  UVar3 = GetPrivateProfileIntA
                    (s_Civilization_Gold_00625444,s_Herald_Warning_Shown_0062542c,0,
                     s_CIV_INI_00625424);
  if (UVar3 == 0) {
    rc = popup_game(ADDR(0x625458, ((u8 *)&g.d_00625458)));
    if (rc == 0) {
      prefs_game_options = prefs_game_options & 0xffdfffff;
    }
    else {
      prefs_game_options = prefs_game_options | 0x200000;
    }
    game.game_options = prefs_game_options;
    prefs_save_civ2dat();
    WritePrivateProfileStringA
              (s_Civilization_Gold_0062548c,s_Herald_Warning_Shown_00625474,&ini_herald_warning_value_str,
               s_CIV_INI_00625468);
  }
  rc = main_frame_create();
  if (rc == 0) {
    result = 1;
  }
  else {
    rc = wnd_client_width((WndBase *)&main_frame_wnd);
    if (1000 < main_frame_nonclient_width + rc) {
      font_set((GameFont *)dialog_default_text_font,0,0x18);
      font_set((GameFont *)dialog_default_list_font,0,0x14);
      font_set((GameFont *)dialog_default_title_font,0,0x18);
      dlg_set_scale(3,2);
    }
    ui_init_screen_metrics();
    err_register_cleanup_fn(ADDR(0x40234c, app_fatal_cleanup));
    rules_parse_sections(1);
    frame_texture_load();
    city_load_citypref();
    passwords_reset();
    autoplay_active = 0;
    saved_turn_civ = 0;
    saved_resume_new_game = 0;
    result = 0;
  }
  return result;
}
#undef autoplay_active
#undef main_frame_nonclient_width
#undef main_view_timer_shown
#undef prefs_game_options
#undef saved_resume_new_game
#undef saved_turn_civ
#undef i

/* 0041b8b0 auto */
void __cdecl app_shutdown_cleanup(void)

{
  ui_flush_input();
  snd_shutdown();
  ui_flush_input();
  frame_texture_free();
  ui_flush_input();
  text_section_index_free();
  labels_free();
  strpool_free();
  ui_flush_input();
  main_frame_destroy();
  ui_flush_input();
  timeEndPeriod(4);
  return;
}

/* 0041d417 auto */
#define prefs_map_size (*(short *)((u8 *)&g.d_0064bc26))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define result (*(i32 *)(frame_ + FRAME_OFF(4)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define rc (*(int *)(frame_ + FRAME_OFF(764)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl setup_choose_map_size(void)

{
  int choice;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  result = 1;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  game.game_flags = 0;
  do {
    setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,2);
    dlg_load_game_section(&dlg,ADDR(0x62553c, ((u8 *)&g.d_0062553c)),1);
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_map_size);
    dialog_set_position
              ((DialogCore *)&dlg,0xfffffc19,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    choice = dlg_show_modal(&dlg,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
    if (choice < 0) {
LAB_0041d739:
      if (5999 < (int)map.height * (int)map.width) {
        game.game_flags = game.game_flags | 4;
      }
      if ((int)map.height * (int)map.width < 3000) {
        game.game_flags = game.game_flags | 8;
      }
      map.width = map.width * 2;
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0041d7c5 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      return result;
    }
    if (dlg.result_extra == 0) {
      prefs_map_size = (short)choice;
      if (choice == 0) {
        map.width = 0x28;
        map.height = 0x32;
      }
      else if (choice == 2) {
        map.width = 0x4b;
        map.height = 0x78;
      }
      else {
        map.width = 0x32;
        map.height = 0x50;
      }
      result = 0;
      goto LAB_0041d739;
    }
    while( true ) {
      text_set_string_arg_b(1,ADDR(0x625548, ((u8 *)&g.d_00625548)));
      setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,2);
      rc = dialog_load_text_section(&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x625550, ((u8 *)&g.d_00625550)),5,ADDR(0x62554c, ((u8 *)&g.d_0062554c)),0,0,0,1)
      ;
      if (rc != 0) {
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
        goto LAB_0041d739;
      }
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg_show_modal(&dlg,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
      if (choice < 0) break;
      choice = _atoi(&text_string_args);
      map.width = (i16)choice;
      choice = _atoi(&text_string_arg1);
      map.height = (i16)choice;
      if ((((0x13 < map.width) && (map.width < 0xfb)) && (0x13 < map.height)) &&
         (((map.height < 0xfb && ((int)map.height * (int)map.width < 0x2711)) &&
          (999 < (int)map.height * (int)map.width)))) {
        result = 0;
        goto LAB_0041d739;
      }
    }
  } while( true );
}
#undef prefs_map_size
#undef screen_height
#undef result
#undef dlg
#undef rc
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0041d7ea auto */
#define prefs_world_params (*(short *)((u8 *)&g.d_0064bc2a))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define result (*(int *)(frame_ + FRAME_OFF(0)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(760)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(768)))
int __cdecl setup_custom_world(void)

{
  int choice;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  result = 1;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,2);
  dlg_load_game_section(&dlg,ADDR(0x62555c, ((u8 *)&g.d_0062555c)),1);
  dialog_set_default_choice((DialogOptionList *)&dlg,prefs_world_params + 1);
  dialog_set_position
            ((DialogCore *)&dlg,0xfffffc19,
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  choice = dlg_show_modal(&dlg,0);
  mapgen_land_mass = choice - 1;
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((ViewWindow *)&setup_picwnd);
  if (-2 < mapgen_land_mass) {
    if (dlg.result_extra == 0) {
      prefs_world_params = (short)mapgen_land_mass;
    }
    else {
      choice = _rand();
      mapgen_land_mass = choice % 3 - 1;
    }
    setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,0xc);
    dlg_load_game_section(&dlg,ADDR(0x625568, ((u8 *)&g.d_00625568)),1);
    dialog_set_default_choice((DialogOptionList *)&dlg,prefs_world_land_form + 1);
    dialog_set_position
              ((DialogCore *)&dlg,0xfffffc19,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    choice = dlg_show_modal(&dlg,0);
    mapgen_land_form = choice - 1;
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
    if (-2 < mapgen_land_form) {
      if (dlg.result_extra == 0) {
        prefs_world_land_form = (short)mapgen_land_form;
      }
      else {
        mapgen_land_form = 0;
        choice = _rand();
        if (choice % 3 == 0) {
          mapgen_land_form = mapgen_land_mass;
        }
      }
      setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,0xb);
      dlg_load_game_section(&dlg,ADDR(0x625574, ((u8 *)&g.d_00625574)),1);
      dialog_set_default_choice((DialogOptionList *)&dlg,prefs_world_climate + 1);
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg_show_modal(&dlg,0);
      mapgen_climate = choice - 1;
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
      if (-2 < mapgen_climate) {
        if (dlg.result_extra == 0) {
          prefs_world_climate = (short)mapgen_climate;
        }
        else {
          choice = _rand();
          mapgen_climate = choice % 3 - 1;
        }
        setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,0xd);
        dlg_load_game_section(&dlg,ADDR(0x625584, ((u8 *)&g.d_00625584)),1);
        dialog_set_default_choice((DialogOptionList *)&dlg,prefs_world_temperature + 1);
        dialog_set_position
                  ((DialogCore *)&dlg,0xfffffc19,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        choice = dlg_show_modal(&dlg,0);
        mapgen_temperature = choice - 1;
        snd_play_effect(0x6a,0,0,0);
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
        if (-2 < mapgen_temperature) {
          if (dlg.result_extra == 0) {
            prefs_world_temperature = (short)mapgen_temperature;
          }
          else {
            choice = _rand();
            mapgen_temperature = choice % 3 - 1;
          }
          setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,10);
          dlg_load_game_section(&dlg,ADDR(0x625590, ((u8 *)&g.d_00625590)),1);
          dialog_set_default_choice((DialogOptionList *)&dlg,prefs_world_age + 1);
          dialog_set_position
                    ((DialogCore *)&dlg,0xfffffc19,
                     -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) +
                      1));
          choice = dlg_show_modal(&dlg,0);
          mapgen_age = choice - 1;
          snd_play_effect(0x6a,0,0,0);
          setup_picwnd_close((ViewWindow *)&setup_picwnd);
          if (-2 < mapgen_age) {
            if (dlg.result_extra == 0) {
              prefs_world_age = (short)mapgen_age;
            }
            else {
              choice = _rand();
              mapgen_age = choice % 3 - 1;
            }
            result = 0;
          }
        }
      }
    }
  }
  if (result == 0) {
    prefs_save_civ2dat();
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0041dc9e */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  return result;
}
#undef prefs_world_params
#undef screen_height
#undef result
#undef dlg
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0041dcc3 auto */
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl setup_clear_start_positions(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 0x15; i++) {
    start_x[i] = -1;
    start_y[i] = -1;
  }
  return;
}
#undef i

/* 0041dfe1 auto */
#define cd_music_available (*(int *)((u8 *)&g.d_0062b420))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define scenario_max_turns (*(short *)((u8 *)&g.d_0064bcb8))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_tech_paradigm (*(short *)((u8 *)&g.d_0064bcb2))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(i8 *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(i32 *)((u8 *)&g.d_0062c488))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define is_female (*(u8 *)(frame_ + FRAME_OFF(12)))
#define gender (*(iptr *)(frame_ + FRAME_OFF(16)))
#define name_buf (*(i8 (*)[260])(frame_ + FRAME_OFF(20)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(280)))
#define result (*(int *)(frame_ + FRAME_OFF(1356)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1360)))
#define option (*(iptr *)(frame_ + FRAME_OFF(2116)))
#define gov (*(iptr *)(frame_ + FRAME_OFF(2120)))
#define dst (*(i8 (*)[256])(frame_ + FRAME_OFF(2124)))
#define level (*(int *)(frame_ + FRAME_OFF(2380)))
#define option_civs (*(int (*)[8])(frame_ + FRAME_OFF(2384)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(2416)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2420)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(2424)))
int __cdecl setup_start_scenario(void)

{
  i32 year;
  iptr rc;
  iptr unit;
  int choice;
  iptr name2;
  i8 frame_[FRAME_OFF(2432)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  palette_init(&palette);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
LAB_0041e028:
  do {
    if (cd_music_available == 0) {
      snd_cd_stop();
      snd_play_effect(0x6b,0,1,0);
    }
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    result = game_load_dialog(1,0,1);
    if (result != 0) {
LAB_0041e731:
      if (result != 0) {
        snd_play_effect(0x6a,0,0,0);
      }
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      choice = result;
      eh_state = eh_state & 0xffffff00;
      /* inlined unwind funclet 0041e7b2 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0041e7be */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      return choice;
    }
    path_set_extension((iptr)dst,ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x62cd24, ((u8 *)&g.d_0062cd24)));
    if (cd_music_available != 0) {
      snd_play_effect(0x6a,0,0,0);
    }
    game.game_options = prefs_game_options & 0xffff7fff;
    game.message_options = prefs_message_options;
    text_set_string_arg(0,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)));
    text_set_number_arg(0,(int)scenario_tech_paradigm);
    text_clear();
    year = game_turn_to_year((int)game.turn);
    text_append_year(year);
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    if (scenario_max_turns == 0) {
      text_append_year(2000);
    }
    else {
      year = game_turn_to_year((int)scenario_max_turns);
      text_append_year(year);
    }
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (cd_music_available != 0) {
      snd_menu_end();
    }
    dialog_init_default(&dlg);
    rc = dialog_load_text(&dlg,(iptr)dst,ADDR(0x6255e0, ((u8 *)&g.d_006255e0)),0x4008001);
    if (rc == 0) goto code_r0x0041e1e4;
    choice = popup_game_flags(ADDR(0x6255ec, ((u8 *)&g.d_006255ec)),1);
  } while (choice < 0);
  goto LAB_0041e2b4;
code_r0x0041e1e4:
  unit = (iptr)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((int)units[unit].owner == (int)scenario_objective_civ)) {
    dialog_add_sprite
              ((DialogOptionList *)&dlg,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0
               ,0);
  }
  choice = dlg_show_modal(&dlg,0);
  if (-1 < choice) {
LAB_0041e2b4:
    dlg_reset(&dlg,1);
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        name2 = civ_name_plural(civ);
        text_append(name2);
        text_append_space();
        text_append_lparen();
        name2 = civ_leader_name(civ);
        text_append(name2);
        text_append_rparen();
        option = dialog_add_option
                              ((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
        option_civs[*(int *)(option + 4)] = civ;
      }
    }
    choice = dlg_show_modal(&dlg,0);
    if (-1 < choice) {
      saved_turn_civ = (i8)human_civ;
      turn_resume_civ = (i8)human_civ;
      (*(i8 *)((char *)&civ + 0)) = (byte)option_civs[choice];
      game.human_players = (u8)(1 << ((byte)civ & 0x1f));
      game.player_civ = (byte)civ;
      game.turn_civ = (byte)civ;
      game.game_options = game.game_options & 0xfffffeff;
      human_civ = option_civs[choice];
      while( true ) {
        dlg_load_game_section(&dlg,ADDR(0x6255fc, ((u8 *)&g.d_006255fc)),1);
        dialog_set_default_choice((DialogOptionList *)&dlg,(uint)game.difficulty);
        dialog_set_position
                  ((DialogCore *)&dlg,
                   ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        level = dlg_show_modal(&dlg,0);
        if (level < 0) break;
        game.difficulty = (u8)level;
        if ((u8)level == '\0') {
          game.game_options = game.game_options | 0x100;
        }
        else {
          game.game_options = game.game_options & 0xfffffeff;
        }
        dlg_load_game_section(&dlg,ADDR(0x625608, ((u8 *)&g.d_00625608)),1);
        dialog_set_default_choice
                  ((DialogOptionList *)&dlg,(uint)leaders[civs[game.player_civ].tribe].female);
        dialog_set_position
                  ((DialogCore *)&dlg,0xfffffc19,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        choice = dlg_show_modal(&dlg,0);
        snd_play_effect(0x6a,0,0,0);
        if (-1 < choice) {
          is_female = (u8)choice;
          leaders[civs[game.player_civ].tribe].female = is_female;
          civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
          if (choice != 0) {
            civs[human_civ].flags = civs[human_civ].flags | 0x200;
          }
          for (gov = 0; gov < 7; gov++) {
            for (gender = 0; gender < 2; gender++) {
              leaders[civs[game.player_civ].tribe].titles[gov][gender] = (short)(&government_titles[gov].male)[gender];
            }
          }
          choice = dlg_game_text_input(ADDR(0x625610, ((u8 *)&g.d_00625610)),0x17,(iptr)&civ_names[game.player_civ].leader_name,(iptr)name_buf
                                    );
          if (choice == 0) {
            crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,name_buf);
            saved_resume_new_game = 1;
            turn_resume_new_game = 1;
            result = 0;
            goto LAB_0041e731;
          }
        }
      }
    }
  }
  goto LAB_0041e028;
}
#undef cd_music_available
#undef human_civ
#undef prefs_game_options
#undef prefs_message_options
#undef saved_resume_new_game
#undef saved_turn_civ
#undef scenario_max_turns
#undef scenario_objective_civ
#undef scenario_tech_paradigm
#undef screen_height
#undef turn_resume_civ
#undef turn_resume_new_game
#undef civ
#undef is_female
#undef gender
#undef name_buf
#undef palette
#undef result
#undef dlg
#undef option
#undef gov
#undef dst
#undef level
#undef option_civs
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0041e8fb auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define is_female (*(u8 *)(frame_ + FRAME_OFF(4)))
#define name_buf (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
#define option_idx (*(int *)(frame_ + FRAME_OFF(268)))
#define enabled_count (*(int *)(frame_ + FRAME_OFF(272)))
#define option_count2 (*(int *)(frame_ + FRAME_OFF(276)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(280)))
#define option (*(iptr *)(frame_ + FRAME_OFF(1036)))
#define option_civs (*(iptr (*)[8])(frame_ + FRAME_OFF(1040)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1072)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1076)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(1080)))
i32 __cdecl load_game_pick_civ(int title_offset)

{
  iptr name2;
  iptr sel;
  int choice;
  i32 arg4;
  i32 arg5;
  i32 arg6;
  i32 arg7;
  i8 frame_[FRAME_OFF(1088)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  while( true ) {
    game.human_players = '\0';
    dlg_reset(&dlg,1);
    dialog_prepend_title_label((iptr)&dlg,title_offset + 0x25e);
    option_idx = 0;
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        name2 = civ_name_plural(civ);
        text_append(name2);
        text_append_space();
        text_append_lparen();
        name2 = civ_leader_name(civ);
        text_append(name2);
        text_append_rparen();
        text_append_space();
        text_append_lparen();
        text_append_int((int)civs[civ].num_cities);
        text_append_space();
        text_append_label(0xc5);
        text_append(ADDR(0x625634, ((u8 *)&g.d_00625634)));
        text_append_int((int)civs[civ].num_military_units);
        text_append_space();
        text_append_label(0xc4);
        text_append(ADDR(0x625638, ((u8 *)&g.d_00625638)));
        choice = option_idx;
        option_idx++;
        option = dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),choice,0)
        ;
        option_civs[*(int *)(option + 4)] = civ;
      }
    }
    option_count2 = option_idx;
    enabled_count = 0;
    for (option_idx = 0; option_idx < option_count2; option_idx++) {
      option = dialog_find_option((DialogOptionList *)&dlg,option_idx);
      if (option != 0) {
        enabled_count++;
        dialog_set_option_disabled((DialogOptionList *)&dlg,*(iptr *)(option + 4),0);
        if ((RadioGroupEnableView *)dlg.radio_group != (RadioGroupEnableView *)0x0) {
          radiogrp_enable_item((RadioGroupEnableView *)dlg.radio_group,*(iptr *)(option + 4));
        }
      }
    }
    dlg.result_id = 0;
    dlg.result_extra = 0;
    sel = dlg_show_modal(&dlg,0);
    if (sel < 0) break;
    human_civ = option_civs[sel];
    (*(i8 *)((char *)&civ + 0)) = (byte)human_civ;
    game.human_players = game.human_players | (byte)(1 << ((byte)civ & 0x1f));
    game.player_civ = (byte)civ;
    game.turn_civ = (byte)civ;
    choice = civ_check_password(human_civ);
    if (choice != 0) {
      game.game_options = game.game_options & 0xfffffeff;
      dlg_load_game_section(&dlg,ADDR(0x62563c, ((u8 *)&g.d_0062563c)),1);
      dialog_prepend_title_label((iptr)&dlg,title_offset + 0x25e);
      dialog_set_default_choice
                ((DialogOptionList *)&dlg,(uint)leaders[civs[game.player_civ].tribe].female);
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg_show_modal(&dlg,0);
      snd_play_effect(0x6a,0,0,0);
      if (-1 < choice) {
        is_female = (u8)choice;
        leaders[civs[game.player_civ].tribe].female = is_female;
        civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
        if (choice != 0) {
          civs[human_civ].flags = civs[human_civ].flags | 0x200;
        }
        arg7 = 1;
        arg6 = 0;
        arg5 = 0;
        arg4 = 0;
        name2 = civ_leader_name((int)game.player_civ);
        choice = dialog_load_text_section
                          (&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x625644, ((u8 *)&g.d_00625644)),0x17,name2,arg4,arg5,arg6,arg7);
        if (choice == 0) {
          dialog_prepend_title_label((iptr)&dlg,title_offset + 0x25e);
          choice = dialog_run_modal(&dlg,(iptr)name_buf,0);
          if (choice == 0) {
            crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,name_buf);
            eh_state = 0xffffffff;
            /* inlined unwind funclet 0041eec6 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
            arg4 = 0;
LAB_0041eedc:
            return arg4;
          }
        }
      }
    }
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0041eec6 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  arg4 = 1;
  goto LAB_0041eedc;
}
#undef human_civ
#undef screen_height
#undef civ
#undef is_female
#undef name_buf
#undef option_idx
#undef enabled_count
#undef option_count2
#undef dlg
#undef option
#undef option_civs
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0041eeeb auto */
#define event_dont_play_wonders (*(int *)((u8 *)&g.d_006a9110))
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define intro_theme_started (*(int *)((u8 *)&g.d_0062af10))
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
#define prefs_main_menu_choice (*(short *)((u8 *)&g.d_00666538))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define choice (*(int *)(frame_ + FRAME_OFF(4)))
#define xd_major (*(int *)(frame_ + FRAME_OFF(8)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(12)))
#define result (*(int *)(frame_ + FRAME_OFF(1088)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1092)))
#define map_source (*(i32 *)(frame_ + FRAME_OFF(1848)))
#define xd_minor (*(int *)(frame_ + FRAME_OFF(1852)))
#define retry (*(int *)(frame_ + FRAME_OFF(1856)))
#define xd_build (*(int *)(frame_ + FRAME_OFF(1860)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1864)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1868)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(1872)))
int __cdecl game_main_menu_loop(void)

{
  int rc;
  i8 frame_[FRAME_OFF(1880)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  result = 1;
  retry = 1;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  palette_init(&palette);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
  __chdir(&game_home_dir);
  crt_strcpy(&scenario_dir_path,&game_home_dir);
  prefs_load_civ2dat();
  game.game_options = prefs_game_options;
  game.multiplayer = '\0';
  ui_flush_input();
  setup_picwnd_load_dll((ViewWindow *)&setup_picwnd);
  snd_wave_set_buffer_count(4);
  if (intro_theme_started == 0) {
    snd_play_effect(0x6b,0,1,0);
  }
  do {
    crt_strcpy(&game_txt_path,&menu_game_txt_name_str);
    crt_strcpy(&rules_txt_path,s_RULES_00625654);
    prefs_load_civ2dat();
    setup_clear_start_positions();
    events_reset((ScenarioEvents *)&scenario_events,50000);
    for (civ = 0; civ < 8; civ++) {
      civ_refresh_ai_goals(civ);
      civ_reset_standing_goals(civ);
    }
    game_over_reason = 0;
    if (net_lobby_launch_mode == -1) {
      setup_picwnd_show((ViewWindow *)&setup_picwnd,1,6,1);
      dlg_load_game_section(&dlg,ADDR(0x62565c, ((u8 *)&g.d_0062565c)),1);
      dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_main_menu_choice);
      dialog_set_position
                ((DialogCore *)&dlg,
                 -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg_show_modal(&dlg,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
      if (choice < 0) goto LAB_0041f5ea;
      prefs_main_menu_choice = (short)choice;
      prefs_save_civ2dat();
    }
    else {
      choice = 5;
    }
    snd_play_effect(0x6a,0,0,0);
    scenario_events_loaded = 0;
    net_session_clear(&net_session);
    switch(choice) {
    case 0:
    case 1:
    case 2:
      __chdir(&game_home_dir);
      rules_load(1);
      if (choice == 1) {
        rc = map_load_dialog();
        if (rc != 0) {
          choice = -1;
        }
        map_source = 1;
        if (map.flat != 0) {
          map_source = 2;
        }
      }
      else {
        rc = setup_choose_map_size();
        if (rc != 0) {
          choice = -1;
        }
        map_source = 0;
      }
      if (choice == 2) {
        rc = setup_custom_world();
        if (rc != 0) {
          choice = -1;
        }
      }
      else {
        rc = _rand();
        mapgen_land_mass = rc % 3 - 1;
        mapgen_land_form = 0;
        rc = _rand();
        if (rc % 3 == 0) {
          mapgen_land_form = mapgen_land_mass;
        }
        rc = _rand();
        mapgen_temperature = rc % 3 - 1;
        rc = _rand();
        mapgen_climate = rc % 3 - 1;
        rc = _rand();
        mapgen_age = rc % 3 - 1;
      }
      if (-1 < choice) {
        retry = setup_new_game_dialogs(map_source);
      }
      break;
    case 3:
      event_dont_play_wonders = 0;
      retry = setup_start_scenario();
      if (retry == 0) {
        if (event_dont_play_wonders != 0) {
          game.game_options = game.game_options & 0xfffeffff;
        }
      }
      else {
        crt_strcpy(&scenario_dir_path,&game_home_dir);
      }
      break;
    case 4:
      event_dont_play_wonders = 0;
      retry = game_load_dialog(0,0,1);
      snd_play_effect(0x6a,0,0,0);
      if ((retry == 0) && (game.multiplayer != '\0')) {
        retry = load_game_pick_civ(1);
      }
      if (retry == 0) {
        saved_turn_civ = (byte)human_civ;
        turn_resume_civ = (byte)human_civ;
        game.multiplayer = '\0';
        game.human_players = (u8)(1 << ((byte)human_civ & 0x1f));
      }
      else if (event_dont_play_wonders != 0) {
        game.game_options = game.game_options & 0xfffeffff;
      }
      break;
    case 5:
      XD_GetXDaemonVersion(&xd_major,&xd_minor,&xd_build);
      if (((xdaemon_required_major == xd_major) && (xdaemon_required_minor == xd_minor)) && (xdaemon_required_build == xd_build))
      {
        __chdir(&game_home_dir);
        rules_load(1);
        retry = setup_choose_multiplayer_type();
        if ((retry != 0) && (net_lobby_launch_mode != -1)) goto LAB_0041f5ea;
      }
      else {
        str_clear(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)));
        str_append_int(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)),xdaemon_required_major);
        crt_strcat(&text_string_args,&xdaemon_req_ver_dot1_str);
        str_append_int(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)),xdaemon_required_minor);
        crt_strcat(&text_string_args,&xdaemon_req_ver_dot2_str);
        str_append_int(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)),xdaemon_required_build);
        str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),xd_major);
        crt_strcat(&text_string_arg1,&xdaemon_got_ver_dot1_str);
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),xd_minor);
        crt_strcat(&text_string_arg1,&xdaemon_got_ver_dot2_str);
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),xd_build);
        popup_game_with_sprite(ADDR(0x625678, ((u8 *)&g.d_00625678)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      break;
    case 6:
      hall_of_fame_show(0xffffffff);
      break;
    case 7:
      rc = popup_game_flags(ADDR(0x62568c, ((u8 *)&g.d_0062568c)),1);
      if (rc < 0) {
        text_close_file();
      }
      else {
        snd_play_effect(-0x6b,0,0,0);
        snd_play_effect(-0x6c,0,0,0);
        snd_cd_detect_layout();
        credits_show(rc);
        snd_cd_stop();
        ui_flush_input();
        snd_play_effect(0x6b,0,1,0);
      }
    }
  } while (retry != 0);
  result = 0;
LAB_0041f5ea:
  snd_play_effect(-0x6b,0,0,0);
  snd_play_effect(-0x6c,0,0,0);
  snd_wave_set_buffer_count(8);
  if ((result == 0) && (snd_cd_detect_layout(), (game.game_options & 8) != 0)) {
    snd_sync_music_option();
  }
  setup_picwnd_free_dll((ViewWindow *)&setup_picwnd);
  rc = result;
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 0041f66e */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0041f67a */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  return rc;
}
#undef event_dont_play_wonders
#undef game_over_reason
#undef human_civ
#undef intro_theme_started
#undef prefs_game_options
#undef prefs_main_menu_choice
#undef saved_turn_civ
#undef scenario_events_loaded
#undef screen_height
#undef turn_resume_civ
#undef civ
#undef choice
#undef xd_major
#undef palette
#undef result
#undef dlg
#undef map_source
#undef xd_minor
#undef retry
#undef xd_build
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0041f69f auto */
#define game_session_active (*(i32 *)((u8 *)&g.d_006252c4))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_show_human_starts (*(short *)((u8 *)&g.d_00654c78))
#define net_local_slot (*(int *)((u8 *)&g.d_006ad304))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define y2 (*(uint *)(frame_ + FRAME_OFF(0)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl game_session_begin(void)

{
  iptr tile;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  game_session_active = 1;
  if ((((turn_resume_civ == '\0') && (game.turn == 0)) && (game.multiplayer != '\0')) &&
     ((mp_show_human_starts != 0 || (game.difficulty == '\0')))) {
    y2 = 0;
    x2 = 0;
    net_batch_begin();
    for (i = 0; i < map.area; i++) {
      tile = tile_at(x2,y2);
      if ((game.human_players & *(byte *)(tile + 4)) != 0) {
        tile_set_visible(x2,y2,(uint)game.human_players,1,1);
      }
      x2 += 2;
      if ((int)map.width <= (int)x2) {
        y2++;
        x2 = y2 & 1;
      }
    }
    net_batch_flush();
  }
  if ((game.multiplayer != '\0') && ((mp_show_human_starts != 0 || (game.difficulty == '\0')))) {
    for (x2 = 0; (int)x2 < 8; x2++) {
      if ((1 << ((byte)x2 & 0x1f) & (uint)game.human_players) != 0) {
        for (y2 = 0; (int)y2 < 8; y2++) {
          if ((1 << ((byte)y2 & 0x1f) & (uint)game.human_players) != 0) {
            diplo_set_treaty_flags(x2,y2,1);
          }
        }
      }
    }
  }
  if (2 < game.multiplayer) {
    human_civ = (&net_slot_civs)[net_local_slot * 0x15];
  }
  return;
}
#undef game_session_active
#undef human_civ
#undef mp_show_human_starts
#undef net_local_slot
#undef net_slot_civs
#undef turn_resume_civ
#undef y2
#undef x2
#undef i

/* 0041f878 auto */
#define game_session_active (*(i32 *)((u8 *)&g.d_006252c4))
void __cdecl game_session_end(void)

{
  ui_flush_input();
  if (game.multiplayer == 1) {
    menu_remove_item((GameMenu *)&main_menu,0x1f2);
  }
  mapviews_destroy_all();
  city_window_destroy((DibSurface *)&city_window);
  status_wnd_close();
  minimap_window_destroy();
  map_free();
  ui_flush_input();
  game_session_active = 0;
  return;
}
#undef game_session_active

/* 0041f8d9 auto */
#define app_shutdown_done (*(int *)((u8 *)&g.d_0062c5b0))
#define chat_broadcast_all (*(i32 *)((u8 *)&g.d_0068aee4))
#define chat_log_buffer (*(char * *)((u8 *)&g.d_0062d870))
#define chat_mute_anonymous (*(i32 *)((u8 *)&g.d_0068aee0))
#define chat_remain_anonymous (*(i32 *)((u8 *)&g.d_0068aedc))
#define dlg_default_idle_callback (*(i8 * *)((u8 *)&g.d_00635a40))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define game_setup_complete (*(i32 *)((u8 *)&g.d_00654fd8))
#define ini_simultaneous_allowed (*(i32 *)((u8 *)&g.d_006c3160))
#define loaded_file_kind (*(i16 *)((u8 *)&g.d_006ad6ac))
#define loaded_file_name (*(i8 *)((u8 *)&g.d_006ad6ae))
#define loaded_file_subdir (*(i8 *)((u8 *)&g.d_006ad7b2))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define mp_simultaneous_setting (*(i8 *)((u8 *)&g.d_00654c7c))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_max_players (*(UINT *)((u8 *)&g.d_006c3164))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define prefs_net_game_name (*(i8 *)((u8 *)&g.d_00666550))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define i (*(int *)(frame_ + FRAME_OFF(0)))
#define log_file (*(FileObject *)(frame_ + FRAME_OFF(4)))
#define send_rc (*(int *)(frame_ + FRAME_OFF(156)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(160)))
#define lobby_rc (*(int *)(frame_ + FRAME_OFF(164)))
#define city (*(iptr *)(frame_ + FRAME_OFF(168)))
#define ini_value (*(UINT *)(frame_ + FRAME_OFF(172)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(176)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1252)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(2008)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2012)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(2016)))
void __cdecl game_main(void)

{
  char is_host;
  iptr rc;
  iptr hwnd_info;
  int result;
  size_t log_len;
  LobbyLaunchInfo *pLVar6;
  i8 frame_[FRAME_OFF(2024)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  palette_init(&palette);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
  dbg_log((iptr)PTR_s_5_4_0f_Multiplayer_26_March_99_0062765c);
  dbg_log((iptr)PTR_s_Patch_3_00627660);
  net_session_clear(&net_session);
  rc = app_startup_init();
  if (rc == 0) {
    _memset(&net_lobby_launch_info,0,0xc4);
    pLVar6 = (LobbyLaunchInfo *)&net_lobby_launch_info;
    hwnd_info = wnd_get_window((WndBase *)&main_frame_wnd);
    lobby_rc = XD_LaunchedByLobby(*(void **)(hwnd_info + 4),pLVar6);
    if ((lobby_rc == 2) || (lobby_rc == 1)) {
      net_lobby_launch_mode = lobby_rc;
      dbg_log(ADDR(0x625698, ((u8 *)&g.d_00625698)));
      dbg_logf_str(ADDR(0x6256bc, ((u8 *)&g.d_006256bc)),ADDR(0x6ad22c, ((u8 *)&g.d_006ad22c)));
      dbg_logf_str(ADDR(0x6256d8, ((u8 *)&g.d_006256d8)),ADDR(0x6ad24c, ((u8 *)&g.d_006ad24c)));
      dbg_logf_str(ADDR(0x6256f4, ((u8 *)&g.d_006256f4)),ADDR(0x6ad28c, ((u8 *)&g.d_006ad28c)));
      dbg_logf_str(ADDR(0x625710, ((u8 *)&g.d_00625710)),ADDR(0x6ad2ac, ((u8 *)&g.d_006ad2ac)));
      dbg_logf(ADDR(0x62572c, ((u8 *)&g.d_0062572c)),net_lobby_is_host);
    }
    else {
      if (((lobby_rc != -3) && (lobby_rc != -4)) && (lobby_rc != -5)) {
        dbg_log(ADDR(0x625768, ((u8 *)&g.d_00625768)));
        send_rc = XD_LobbySendMessage(2);
        if (send_rc != 0) {
          dbg_logf(ADDR(0x62579c, ((u8 *)&g.d_0062579c)),send_rc);
        }
        eh_state = eh_state & 0xffffff00;
        /* inlined unwind funclet 004201fb */ { palette_destroy((GamePalette *)((iptr)&palette)); }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 00420207 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
        goto LAB_0042021d;
      }
      dbg_logf(ADDR(0x625748, ((u8 *)&g.d_00625748)),lobby_rc);
      net_lobby_launch_mode = -1;
    }
    ini_simultaneous_allowed = 0;
    ini_value = GetPrivateProfileIntA
                          (s_Civilization_Gold_006257e4,s_Simultaneous_006257d4,-1,
                           s_CIV_INI_006257cc);
    if (0 < (int)ini_value) {
      ini_simultaneous_allowed = 1;
      WritePrivateProfileStringA
                (s_Civilization_Gold_00625814,s_Simultaneous_00625804,&ini_simultaneous_reset_str,
                 s_CIV_INI_006257f8);
    }
    net_max_players = 7;
    ini_value = GetPrivateProfileIntA
                          (s_Civilization_Gold_0062583c,s_MaxPlayers_00625830,-1,s_CIV_INI_00625828)
    ;
    if (4 < (int)ini_value) {
      if (7 < (int)ini_value) {
        ini_value = 7;
      }
      net_max_players = ini_value;
      WritePrivateProfileStringA
                (s_Civilization_Gold_00625868,s_MaxPlayers_0062585c,&ini_max_players_reset_str,s_CIV_INI_00625850
                );
    }
    crt_strcpy(&net_game_name,&prefs_net_game_name);
    do {
      game_loop_active = 1;
      loaded_file_kind = 0;
      loaded_file_name = 0;
      loaded_file_subdir = 0;
      for (unit = 0; unit < 8; unit++) {
        *(i32 *)(&casualty_counts + unit * 4) = 0;
        *(i32 *)(&casualty_reported_counts + unit * 4) = 0;
        *(i32 *)(&casualty_log_first + unit * 4) = 0;
        *(i32 *)(&casualty_log_next + unit * 4) = 0;
      }
      passwords_reset();
      events_reset((ScenarioEvents *)&scenario_events,50000);
      _memset(&net_map_lock_slots,-1,0xc0);
      for (unit = 0; unit < 0x800; unit++) {
        units[unit].id = 0;
        units[unit].prev_in_stack = -1;
        units[unit].next_in_stack = -1;
      }
      game.num_units = 0;
      for (city = 0; city < 0x100; city++) {
        cities[city].id = 0;
      }
      game.num_cities = 0;
      result = game_main_menu_loop();
      if (result != 0) goto LAB_004201d0;
      minimap_window_create();
      status_wnd_open();
      mapviews_create_all();
      city_window_create((FrameWindow *)&city_window);
      if (2 < game.multiplayer) {
        parley_wnd_create((ViewWindow *)&chat_wnd,4);
        parley_wnd_create((ViewWindow *)&parley_wnd,3);
      }
      pedia_window_create((DocumentWindow *)&pedia_window);
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      if (game.multiplayer != '\0') {
        if ((game.multiplayer < 3) || (is_host = net_is_host(&net_session), is_host != '\0')) {
          rules_apply_double_moves();
        }
        if ((2 < game.multiplayer) && (is_host = net_is_host(&net_session), is_host != '\0')) {
          mp_simultaneous_moves = (char)mp_simultaneous_setting;
          net_send_message(0x33,0xff,(int)mp_double_production,(int)mp_double_moves,(int)mp_simultaneous_setting,0,0,0,0
                             ,0);
        }
      }
      if (2 < game.multiplayer) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x120,1);
        dlg_default_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
        is_host = net_is_host(&net_session);
        if (is_host != '\0') {
          net_send_rules_tables(0xff);
        }
        net_tile_sync_enabled = 1;
        XD_FlushSendBuffer(180000);
        mp_mouse_watchdog_start();
      }
      game_session_begin();
      if ((((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (2 < game.multiplayer)) &&
          (mp_simultaneous_moves != '\0')) && (simul_tutorial_shown == 0)) {
        popup_game_with_sprite(ADDR(0x62587c, ((u8 *)&g.d_0062587c)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
        simul_tutorial_shown = 1;
      }
      ui_set_button_font(ADDR(0x6cec90, ((u8 *)&g.d_006cec90)));
      game_setup_complete = 1;
      if (game.multiplayer < 3) {
        game_play_loop();
      }
      else {
        if (net_host_flag == '\0') {
          XD_FlushSendBuffer(5000);
          while (nm_ready_to_start_count == 0) {
            net_process_messages((NetSession *)&net_session,1,0);
          }
        }
        else {
          net_send_message(0x9c,0xff,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
        }
        if (mp_simultaneous_moves == '\0') {
          if (net_host_flag == '\0') {
            result = game_mp_client_turn_loop();
            if (result != 0) {
              game_mp_host_turn_loop(1);
            }
          }
          else {
            game_mp_host_turn_loop(0);
          }
        }
        else if (net_host_flag == '\0') {
          result = net_client_turn_loop();
          if (result != 0) {
            net_host_turn_loop();
          }
        }
        else {
          net_host_turn_loop();
        }
      }
      prefs_save_civ2dat();
      dlg_default_idle_callback = (i8 *)0x0;
      scenario_events_loaded = 0;
      mp_turn_timer_stop(1);
      mp_mouse_watchdog_stop();
      if (2 < game.multiplayer) {
        file_obj_init(&log_file);
        eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),2);
        diffeng_free_mirror();
        if (net_host_flag != '\0') {
          net_session_shutdown(&net_session,1);
        }
        result = file_obj_create(&log_file,ADDR(0x625888, ((u8 *)&g.d_00625888)));
        if (result != 0) {
          log_len = _strlen(chat_log_buffer);
          file_obj_write(&log_file,(iptr)chat_log_buffer,log_len);
          file_map_close(&log_file);
        }
        for (i = 0; i < 8; i++) {
          *(i32 *)(&chat_send_to_civs + i * 4) = 0;
          *(i32 *)(&chat_muted_civs + i * 4) = 0;
        }
        chat_remain_anonymous = 0;
        chat_broadcast_all = 0;
        chat_mute_anonymous = 0;
        parley_wnd_close();
        chat_wnd_close();
        eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
        /* inlined unwind funclet 004201ef */ { file_obj_close((FileObject *)((iptr)&log_file)); }
      }
      pedia_close();
      picwnd_close((PictureWindowCore *)&advisor_window);
      picwnd_close((PictureWindowCore *)&casualty_window);
      if (app_shutdown_done != 0) {
        eh_state = eh_state & 0xffffff00;
        /* inlined unwind funclet 004201fb */ { palette_destroy((GamePalette *)((iptr)&palette)); }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 00420207 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
        goto LAB_0042021d;
      }
      game_session_end();
    } while (net_lobby_launch_mode == -1);
    eh_state = eh_state & 0xffffff00;
    /* inlined unwind funclet 004201fb */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 00420207 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  }
  else {
LAB_004201d0:
    app_shutdown_cleanup();
    eh_state = eh_state & 0xffffff00;
    /* inlined unwind funclet 004201fb */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 00420207 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  }
LAB_0042021d:
  return;
}
#undef app_shutdown_done
#undef chat_broadcast_all
#undef chat_log_buffer
#undef chat_mute_anonymous
#undef chat_remain_anonymous
#undef dlg_default_idle_callback
#undef game_loop_active
#undef game_setup_complete
#undef ini_simultaneous_allowed
#undef loaded_file_kind
#undef loaded_file_name
#undef loaded_file_subdir
#undef mp_double_moves
#undef mp_double_production
#undef mp_simultaneous_moves
#undef mp_simultaneous_setting
#undef net_host_flag
#undef net_max_players
#undef net_tile_sync_enabled
#undef prefs_net_game_name
#undef scenario_events_loaded
#undef i
#undef log_file
#undef send_rc
#undef unit
#undef lobby_rc
#undef city
#undef ini_value
#undef palette
#undef dlg
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00421bb0 auto */
i32 __cdecl timer_ticks(void)

{
  i32 ticks;
  
  ticks = timer_ticks_60hz();
  return ticks;
}

/* 004259a6 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define hotseat_human_players (*(byte *)((u8 *)&g.d_006c31a9))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_simultaneous_setting (*(short *)((u8 *)&g.d_00654c7c))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define scenario_name (*(i8 *)((u8 *)&g.d_0064bc62))
#define slot_masks (*(uint (*)[10])(frame_ + FRAME_OFF(4)))
#define count (*(int *)(frame_ + FRAME_OFF(44)))
#define i (*(int *)(frame_ + FRAME_OFF(48)))
#define seconds (*(int *)(frame_ + FRAME_OFF(52)))
#define human_mask (*(uint *)(frame_ + FRAME_OFF(56)))
i32 __cdecl game_profile_popup(int is_join)

{
  size_t name_len;
  i32 result;
  int minutes;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  slot_masks[0] = 0;
  slot_masks[1] = 1;
  slot_masks[2] = 3;
  slot_masks[3] = 7;
  slot_masks[4] = 0xf;
  slot_masks[5] = 0x1f;
  slot_masks[6] = 0x3f;
  slot_masks[7] = 0x7f;
  slot_masks[8] = 0xff;
  str_clear(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)));
  crt_strcat(&text_string_args,&net_game_name);
  str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
  str_append_label(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),(mp_open_game == 0) + 0x277);
  str_clear(ADDR(0x63ce50, ((u8 *)&g.d_0063ce50)));
  crt_strcat(&text_string_arg2,&net_host_player_name);
  str_clear(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  name_len = _strlen(&scenario_name);
  if (name_len == 0) {
    str_append_label(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)),0x34c);
  }
  else {
    crt_strcpy(&text_string_arg3,&scenario_name);
  }
  str_append_space(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  str_append_lparen(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  result = game_turn_to_year((int)game.turn);
  str_append_year(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)),result);
  str_append_rparen(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  str_clear(ADDR(0x63d058, ((u8 *)&g.d_0063d058)));
  str_append_label(ADDR(0x63d058, ((u8 *)&g.d_0063d058)),game.difficulty + 0x279);
  str_append_space(ADDR(0x63d058, ((u8 *)&g.d_0063d058)));
  str_append_lparen(ADDR(0x63d058, ((u8 *)&g.d_0063d058)));
  str_append_label(ADDR(0x63d058, ((u8 *)&g.d_0063d058)),0x34e - (uint)(mp_simultaneous_setting == 0));
  str_append_rparen(ADDR(0x63d058, ((u8 *)&g.d_0063d058)));
  str_clear(ADDR(0x63d670, ((u8 *)&g.d_0063d670)));
  str_append_int(ADDR(0x63d670, ((u8 *)&g.d_0063d670)),(int)map.width / 2);
  str_clear(ADDR(0x63d774, ((u8 *)&g.d_0063d774)));
  str_append_int(ADDR(0x63d774, ((u8 *)&g.d_0063d774)),(int)map.height);
  str_clear(ADDR(0x63d15c, ((u8 *)&g.d_0063d15c)));
  str_append_label(ADDR(0x63d15c, ((u8 *)&g.d_0063d15c)),0x350 - (uint)(mp_double_production == 0));
  crt_strcat(&text_string_arg5,&game_profile_double_opts_sep_str);
  str_append_label(ADDR(0x63d15c, ((u8 *)&g.d_0063d15c)),0x352 - (uint)(mp_double_moves == 0));
  str_clear(ADDR(0x63d260, ((u8 *)&g.d_0063d260)));
  str_append_label(ADDR(0x63d260, ((u8 *)&g.d_0063d260)),game.barbarian_activity + 0x27f);
  str_clear(ADDR(0x63d364, ((u8 *)&g.d_0063d364)));
  if (mp_turn_time_limit_ms == 0) {
    str_append_label(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),0x285);
  }
  else {
    minutes = (mp_turn_time_limit_ms / 1000) / 0x3c;
    seconds = (mp_turn_time_limit_ms / 1000) % 0x3c;
    if (minutes < 10) {
      str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),0);
    }
    str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),minutes);
    crt_strcat(&game_profile_timer_text,&game_profile_timer_colon_str);
    if (seconds < 10) {
      str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),0);
    }
    str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),seconds);
  }
  str_clear(ADDR(0x63d468, ((u8 *)&g.d_0063d468)));
  count = 0;
  slot_masks[9] = (uint)game.civs_alive;
  for (i = 1; slot_masks[9] = (int)slot_masks[9] >> 1, i < 8; i++) {
    if ((slot_masks[9] & 1) != 0) {
      count++;
    }
  }
  str_append_int(ADDR(0x63d468, ((u8 *)&g.d_0063d468)),count);
  str_clear(ADDR(0x63d56c, ((u8 *)&g.d_0063d56c)));
  human_mask = 0;
  if (game.multiplayer == '\0') {
    human_mask = 1;
  }
  else if (game.multiplayer == 1) {
    human_mask = (uint)hotseat_human_players;
  }
  else {
    human_mask = slot_masks[net_player_count];
  }
  count = 0;
  slot_masks[9] = human_mask;
  for (i = 0; i < 8; i++) {
    if ((slot_masks[9] & 1) != 0) {
      count++;
    }
    slot_masks[9] = (int)slot_masks[9] >> 1;
  }
  if (is_join != 0) {
    count--;
  }
  str_append_int(ADDR(0x63d56c, ((u8 *)&g.d_0063d56c)),count);
  dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
  result = popup_text_with_sprite(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x625d74, ((u8 *)&g.d_00625d74)),(uint)(is_join != 0),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  return result;
}
#undef dlg_pending_idle_callback
#undef hotseat_human_players
#undef mp_double_moves
#undef mp_double_production
#undef mp_open_game
#undef mp_simultaneous_setting
#undef mp_turn_time_limit_ms
#undef scenario_name
#undef slot_masks
#undef count
#undef i
#undef seconds
#undef human_mask

/* 00444310 auto */
#define event_dont_play_wonders (*(int *)((u8 *)&g.d_006a9110))
#define game_setup_complete (*(i32 *)((u8 *)&g.d_00654fd8))
#define loaded_file_kind (*(i16 *)((u8 *)&g.d_006ad6ac))
#define loaded_file_subdir (*(i8 *)((u8 *)&g.d_006ad7b2))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_turn_time_limit_ms (*(i32 *)((u8 *)&g.d_00654b70))
#define net_active_protocol (*(int *)((u8 *)&g.d_006c9288))
#define net_adapter_index (*(uint *)((u8 *)&g.d_006ad2fc))
#define net_claimed_civs_mask (*(i16 *)((u8 *)&g.d_00654fb0))
#define net_connection_title (*(char * *)((u8 *)&g.d_006ad63c))
#define net_lobby_list (*(LobbyList * *)((u8 *)&g.d_006ad10c))
#define net_protocol (*(uint *)((u8 *)&g.d_006ad2f8))
#define net_xd_adapter_index (*(uint *)((u8 *)&g.d_006c8fbc))
#define prefs_lan_menu_choice (*(short *)((u8 *)&g.d_0066653e))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define prefs_net_protocol (*(ushort *)((u8 *)&g.d_00666544))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define turn_resume_civ (*(i8 *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define lobby_list (*(LobbyList * *)(frame_ + FRAME_OFF(0)))
#define this2 (*(void * *)(frame_ + FRAME_OFF(20)))
#define ip_buf (*(char (*)[260])(frame_ + FRAME_OFF(52)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(312)))
#define i (*(int *)(frame_ + FRAME_OFF(1388)))
#define first_pass (*(int *)(frame_ + FRAME_OFF(1392)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1396)))
#define map_source (*(i32 *)(frame_ + FRAME_OFF(2152)))
#define transport_ok (*(char *)(frame_ + FRAME_OFF(2156)))
#define saved_open_game (*(int *)(frame_ + FRAME_OFF(2160)))
#define rc (*(int *)(frame_ + FRAME_OFF(2164)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(2168)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2172)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(2176)))
i32 __cdecl setup_network_game(int conn_type)

{
  size_t len;
  int choice;
  i32 result;
  int rc2;
  NetGamelistViewCtorView *this;
  char *title_buf;
  size_t ip_len;
  LobbyListCtorView *this_00;
  i8 frame_[FRAME_OFF(2184)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  first_pass = 1;
  palette_init(&palette);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
  if ((((conn_type != 0) && (conn_type != 1)) && (conn_type != 4)) && ((conn_type != 2 && (conn_type != 3))))
  {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62640c, ((u8 *)&g.d_0062640c)),ADDR(0x6263e8, ((u8 *)&g.d_006263e8)),0x21);
  }
  net_connection_type = conn_type;
  if ((conn_type == 1) || (conn_type == 4)) {
    dlg_load_game_section(&dlg,ADDR(0x6264a4, ((u8 *)&g.d_006264a4)),1);
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)(short)prefs_net_protocol);
    if (conn_type == 4) {
      dialog_set_option_disabled((DialogOptionList *)&dlg,1,1);
    }
    rc = dlg_show_modal(&dlg,0);
    if (rc == -1) {
      eh_state = eh_state & 0xffffff00;
      /* inlined unwind funclet 0044525d */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 00445269 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      result = 1;
      goto LAB_0044527f;
    }
    net_protocol = (uint)(rc != 0);
    prefs_net_protocol = (ushort)(rc != 0);
    if (conn_type == 4) {
      game.multiplayer = 4;
      conn_type = 0;
      net_connection_type = 0;
    }
    else {
      game.multiplayer = 3;
    }
  }
  else if (conn_type == 0) {
    net_protocol = 0;
    game.multiplayer = 4;
  }
  else if (conn_type == 2) {
    net_protocol = 2;
    game.multiplayer = 5;
  }
  else {
    game.multiplayer = 6;
    net_protocol = 3;
  }
  text_clear();
  if (conn_type == 0) {
    text_append_label(0x28f);
  }
  else if ((conn_type == 1) || (conn_type == 4)) {
    if (conn_type == 1) {
      text_append_label(0x290);
    }
    else {
      text_append_label(0x362);
    }
    text_append_space();
    if (net_protocol == 0) {
      text_append_label(0x291);
    }
    else if (net_protocol == 1) {
      text_append_label(0x292);
    }
  }
  else {
    text_append_label(0x349);
  }
  if (net_connection_title != (char *)0x0) {
    operator_delete(net_connection_title);
    net_connection_title = (char *)0x0;
  }
  len = _strlen(&text_buffer);
  net_connection_title = operator_new(len + 1);
  if (net_connection_title == (char *)0x0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6264d4, ((u8 *)&g.d_006264d4)),ADDR(0x6264b0, ((u8 *)&g.d_006264b0)),0x79);
  }
  crt_strcpy(net_connection_title,&text_buffer);
  turn_resume_new_game = 0;
  saved_resume_new_game = 0;
LAB_0044465c:
  if (turn_resume_new_game == 1) {
    snd_play_effect(0x6a,0,0,0);
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_flush_paint();
  }
  for (i = 0; i < 8; i++) {
    *(i16 *)(&civ_intro_shown + i * 2) = 0;
    (&net_player_setup_table)[i * 0x20] = 0;
  }
  mp_turn_time_limit_ms = 0;
  turn_resume_civ = 0;
  saved_turn_civ = 0;
  turn_resume_new_game = 0;
  saved_resume_new_game = 0;
  loaded_file_subdir = 0;
  loaded_file_kind = 0;
  scenario_reset_params();
  game.turn = 0;
  game.first_launch_turn = -1;
  game.game_flags = 0;
  crt_strcpy(&scenario_dir_path,&game_home_dir);
  if (first_pass == 0) {
    rules_load(1);
  }
  scenario_events_loaded = 0;
  setup_dialog_pos_state = 3;
  setup_show_side_picture(0xffffffff,0);
  crt_strcpy(&text_string_args,net_connection_title);
  dlg_load_game_section(&dlg,ADDR(0x6264ec, ((u8 *)&g.d_006264ec)),1);
  choice = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
  result = setup_next_dialog_x(0);
  dialog_set_position((DialogCore *)&dlg,result,choice);
  if (net_lobby_launch_mode == 2) {
    dialog_set_option_disabled((DialogOptionList *)&dlg,5,1);
    if (prefs_lan_menu_choice == 5) {
      dialog_set_default_choice((DialogOptionList *)&dlg,0);
    }
    else {
      dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_lan_menu_choice);
    }
  }
  else if (net_lobby_launch_mode == 1) {
    dialog_set_option_disabled((DialogOptionList *)&dlg,0,1);
    dialog_set_option_disabled((DialogOptionList *)&dlg,1,1);
    dialog_set_option_disabled((DialogOptionList *)&dlg,2,1);
    dialog_set_option_disabled((DialogOptionList *)&dlg,3,1);
    dialog_set_option_disabled((DialogOptionList *)&dlg,4,1);
    dialog_set_default_choice((DialogOptionList *)&dlg,5);
  }
  else {
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_lan_menu_choice);
  }
  choice = dlg_show_modal(&dlg,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((ViewWindow *)&setup_picwnd);
  first_pass = 0;
  if (choice < 0) {
    eh_state = eh_state & 0xffffff00;
    /* inlined unwind funclet 0044525d */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 00445269 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
    result = 1;
    goto LAB_0044527f;
  }
  prefs_lan_menu_choice = (short)choice;
  if ((-1 < choice) && (choice < 3)) {
    __chdir(&game_home_dir);
  }
  switch(choice) {
  case 0:
    rc2 = setup_choose_map_size();
    if (rc2 == 0) {
      map_source = 0;
      rc2 = _rand();
      mapgen_land_mass = rc2 % 3 - 1;
      mapgen_land_form = 0;
      rc2 = _rand();
      if (rc2 % 3 == 0) {
        mapgen_land_form = mapgen_land_mass;
      }
      rc2 = _rand();
      mapgen_temperature = rc2 % 3 - 1;
      rc2 = _rand();
      mapgen_climate = rc2 % 3 - 1;
      rc2 = _rand();
      mapgen_age = rc2 % 3 - 1;
      rc2 = setup_choose_game_options(map_source,3);
      goto joined_r0x00444b3b;
    }
    goto LAB_0044465c;
  case 1:
    rc2 = map_load_dialog();
    if (rc2 == 0) {
      map_source = 1;
      if (map.flat != 0) {
        map_source = 2;
      }
      rc2 = _rand();
      mapgen_land_mass = rc2 % 3 - 1;
      mapgen_land_form = 0;
      rc2 = _rand();
      if (rc2 % 3 == 0) {
        mapgen_land_form = mapgen_land_mass;
      }
      rc2 = _rand();
      mapgen_temperature = rc2 % 3 - 1;
      rc2 = _rand();
      mapgen_climate = rc2 % 3 - 1;
      rc2 = _rand();
      mapgen_age = rc2 % 3 - 1;
      rc2 = setup_choose_game_options(map_source,3);
      goto joined_r0x00444b3b;
    }
    goto LAB_0044465c;
  case 2:
    rc2 = setup_choose_map_size();
    if (rc2 != 0) goto LAB_0044465c;
    map_source = 0;
    rc2 = setup_custom_world();
    if (rc2 != 0) goto LAB_0044465c;
    rc2 = setup_choose_game_options(map_source,3);
joined_r0x00444b3b:
    if (rc2 != 0) goto LAB_0044465c;
    break;
  case 3:
    event_dont_play_wonders = 0;
    rc2 = setup_mp_load_scenario(3);
    if (rc2 != 0) {
      crt_strcpy(&scenario_dir_path,&game_home_dir);
      goto LAB_0044465c;
    }
    if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    break;
  case 4:
    event_dont_play_wonders = 0;
    rc2 = game_load_dialog(0,3,1);
    if (rc2 == 0) {
      if (2 < game.multiplayer) break;
      crt_strcpy(&text_string_args,net_connection_title);
      popup_game_with_sprite(ADDR(0x6264f4, ((u8 *)&g.d_006264f4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
    else if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    goto LAB_0044465c;
  case 5: ;
  }
  net_claimed_civs_mask = 0;
  prefs_save_civ2dat();
  game_setup_complete = 0;
  game.human_players = '\0';
  if (choice != 5) {
    saved_open_game = (int)mp_open_game;
    mp_open_game = 1;
    if (((conn_type != 2) && (conn_type != 3)) ||
       ((choice = net_prompt_player_name(), choice != 0 && (choice = net_prompt_game_name(), choice != 0)))) {
      transport_ok = net_init_transport(&net_session,net_protocol,1);
      if (transport_ok == '\0') {
        if ((net_protocol != 2) && (net_protocol != 3)) {
          dbg_log(ADDR(0x62653c, ((u8 *)&g.d_0062653c)));
          crt_strcpy(&text_string_args,net_connection_title);
          popup_game_with_sprite(ADDR(0x62656c, ((u8 *)&g.d_0062656c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        goto LAB_0044465c;
      }
      if ((conn_type != 2) && (conn_type != 3)) {
        choice = net_prompt_player_name();
        if (choice == 0) {
          net_session_shutdown(&net_session,1);
          goto LAB_0044465c;
        }
        choice = net_prompt_game_name();
        if (choice == 0) {
          net_session_shutdown(&net_session,1);
          goto LAB_0044465c;
        }
      }
      if (conn_type == 0) {
        do {
          if (net_lobby_launch_mode != -1) {
            crt_strcpy(&prefs_net_ip_address,&net_lobby_launch_info);
            goto LAB_0044501d;
          }
          title_buf = XD_GetCurrentProtoAddr(net_xd_adapter_index,net_active_protocol);
          if (title_buf == (char *)0x0) {
            prefs_net_ip_address = 0;
          }
          else {
            title_buf = XD_GetCurrentProtoAddr(net_adapter_index,net_protocol);
            crt_strcpy(&prefs_net_ip_address,title_buf);
          }
          dialog_load_text_section(&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62657c, ((u8 *)&g.d_0062657c)),0x1f,ADDR(0x6665b0, ((u8 *)&g.d_006665b0)),0,0,0,1);
          rc = dialog_run_modal(&dlg,(iptr)ip_buf,0);
          if (rc == -1) {
            net_session_shutdown(&net_session,1);
            goto LAB_0044465c;
          }
          len = _strlen(ip_buf);
        } while (len == 0);
        crt_strcpy(&prefs_net_ip_address,ip_buf);
LAB_0044501d:
        len = _strlen(net_connection_title);
        ip_len = _strlen(&prefs_net_ip_address);
        title_buf = operator_new(len + ip_len + 3);
        if (title_buf == (char *)0x0) {
          err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6265ac, ((u8 *)&g.d_006265ac)),ADDR(0x626588, ((u8 *)&g.d_00626588)),0x1b9);
        }
        crt_strcpy(title_buf,net_connection_title);
        crt_strcat(title_buf,&net_title_ip_sep_str);
        crt_strcat(title_buf,&prefs_net_ip_address);
        operator_delete(net_connection_title);
        net_connection_title = title_buf;
      }
      else if (((conn_type == 1) || (conn_type == 4)) && (choice = net_prompt_ip_address(), choice == 0)) {
        net_session_shutdown(&net_session,1);
        goto LAB_0044465c;
      }
      this_00 = operator_new(0x70);
      (*(i8 *)((char *)&eh_state + 0)) = 3;
      if (this_00 == (LobbyListCtorView *)0x0) {
        lobby_list = (LobbyList *)0x0;
      }
      else {
        lobby_list = (LobbyList *)lobby_list_ctor(this_00);
      }
      eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
      net_lobby_list = lobby_list;
      choice = lobby_host_wait_players(lobby_list,map_source,conn_type);
      if (net_lobby_list != (LobbyList *)0x0) {
        lobby_list_scalar_dtor(net_lobby_list,1);
      }
      net_lobby_list = (LobbyList *)0x0;
      if (choice != 0) goto LAB_004451fb;
      net_session_shutdown(&net_session,1);
      loaded_file_subdir = 0;
      scenario_reset_params();
    }
    goto LAB_0044465c;
  }
  transport_ok = net_init_transport(&net_session,net_protocol,0);
  if (transport_ok == '\0') {
    dbg_log(ADDR(0x6264fc, ((u8 *)&g.d_006264fc)));
    crt_strcpy(&text_string_args,net_connection_title);
    popup_game_with_sprite(ADDR(0x62652c, ((u8 *)&g.d_0062652c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    goto LAB_0044465c;
  }
  choice = net_prompt_player_name();
  if (choice == 0) {
    net_session_shutdown(&net_session,1);
    goto LAB_0044465c;
  }
  if (((conn_type != 2) && (conn_type != 3)) && (choice = net_prompt_ip_address(), choice == 0)) {
    net_session_shutdown(&net_session,1);
    goto LAB_0044465c;
  }
  this = operator_new(0x178);
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  if (this == (NetGamelistViewCtorView *)0x0) {
    this2 = (void *)0x0;
  }
  else {
    this2 = (void *)net_gamelist_view_ctor(this);
  }
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
  net_session = (iptr)this2;
  rc = net_session_init(this2,conn_type);
  if (net_session != 0) {
    net_gamelist_view_scalar_dtor((void *)net_session,1);
  }
  net_session = 0;
  if (rc == 0) {
    net_session_shutdown(&net_session,1);
    loaded_file_subdir = 0;
    scenario_reset_params();
    goto LAB_0044465c;
  }
LAB_004451fb:
  mp_open_game = (short)saved_open_game;
  game_setup_complete = 1;
  prefs_save_civ2dat();
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 0044525d */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 00445269 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  result = 0;
LAB_0044527f:
  return result;
}
#undef event_dont_play_wonders
#undef game_setup_complete
#undef loaded_file_kind
#undef loaded_file_subdir
#undef mp_open_game
#undef mp_turn_time_limit_ms
#undef net_active_protocol
#undef net_adapter_index
#undef net_claimed_civs_mask
#undef net_connection_title
#undef net_lobby_list
#undef net_protocol
#undef net_xd_adapter_index
#undef prefs_lan_menu_choice
#undef prefs_net_ip_address
#undef prefs_net_protocol
#undef saved_resume_new_game
#undef saved_turn_civ
#undef scenario_events_loaded
#undef screen_height
#undef text_buffer
#undef turn_resume_civ
#undef turn_resume_new_game
#undef lobby_list
#undef this2
#undef ip_buf
#undef palette
#undef i
#undef first_pass
#undef dlg
#undef map_source
#undef transport_ok
#undef saved_open_game
#undef rc
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00445712 auto */
#define cd_music_available (*(int *)((u8 *)&g.d_0062b420))
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define ini_simultaneous_allowed (*(int *)((u8 *)&g.d_006c3160))
#define mp_chat_from_start (*(short *)((u8 *)&g.d_00654c7a))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_show_human_starts (*(short *)((u8 *)&g.d_00654c78))
#define mp_simultaneous_moves (*(i8 *)((u8 *)&g.d_006ad684))
#define mp_simultaneous_setting (*(short *)((u8 *)&g.d_00654c7c))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
#define prefs_mp_chat_from_start (*(short *)((u8 *)&g.d_0066654c))
#define prefs_mp_double_moves (*(short *)((u8 *)&g.d_00666600))
#define prefs_mp_double_production (*(short *)((u8 *)&g.d_006665fe))
#define prefs_mp_kill_on_retire (*(short *)((u8 *)&g.d_00666548))
#define prefs_mp_open_game (*(short *)((u8 *)&g.d_00666546))
#define prefs_mp_show_human_starts (*(short *)((u8 *)&g.d_0066654a))
#define prefs_mp_simultaneous_moves (*(short *)((u8 *)&g.d_0066654e))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define scenario_max_turns (*(short *)((u8 *)&g.d_0064bcb8))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_tech_paradigm (*(short *)((u8 *)&g.d_0064bcb2))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(i8 *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(i32 *)((u8 *)&g.d_0062c488))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1080)))
#define i (*(int *)(frame_ + FRAME_OFF(1836)))
#define dst (*(i8 (*)[260])(frame_ + FRAME_OFF(1840)))
#define level (*(int *)(frame_ + FRAME_OFF(2100)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(2104)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2108)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(2112)))
i32 __cdecl setup_mp_load_scenario(i32 mp_mode)

{
  iptr rc;
  i32 value;
  iptr load_rc;
  int unit;
  i8 frame_[FRAME_OFF(2120)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  palette_init(&palette);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
LAB_00445759:
  do {
    if (cd_music_available == 0) {
      snd_cd_stop();
      snd_play_effect(0x6b,0,1,0);
    }
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    rc = game_load_dialog(1,3,1);
    if (rc != 0) {
      snd_play_effect(0x6a,0,0,0);
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      wnd_flush_paint();
      eh_state = eh_state & 0xffffff00;
      /* inlined unwind funclet 00445e15 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 00445e21 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      value = 1;
LAB_00445e37:
      return value;
    }
    path_set_extension((iptr)dst,ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x62cd24, ((u8 *)&g.d_0062cd24)));
    if (cd_music_available != 0) {
      snd_play_effect(0x6a,0,0,0);
    }
    game.game_options = prefs_game_options & 0xffff7fff;
    game.message_options = prefs_message_options;
    game.human_players = '\0';
    text_set_string_arg(0,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)));
    text_set_number_arg(0,(int)scenario_tech_paradigm);
    text_clear();
    value = game_turn_to_year((int)game.turn);
    text_append_year(value);
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    if (scenario_max_turns == 0) {
      text_append_year(2000);
    }
    else {
      value = game_turn_to_year((int)scenario_max_turns);
      text_append_year(value);
    }
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (cd_music_available != 0) {
      snd_menu_end();
    }
    dialog_init_default(&dlg);
    load_rc = dialog_load_text(&dlg,(iptr)dst,ADDR(0x6265d8, ((u8 *)&g.d_006265d8)),0x4008001);
    if (load_rc == 0) goto code_r0x0044597e;
    unit = popup_game_flags(ADDR(0x6265e4, ((u8 *)&g.d_006265e4)),1);
  } while (unit < 0);
  goto LAB_00445a4e;
code_r0x0044597e:
  unit = (int)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((int)units[unit].owner == (int)scenario_objective_civ)) {
    dialog_add_sprite
              ((DialogOptionList *)&dlg,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0
               ,0);
  }
  unit = dlg_show_modal(&dlg,0);
  if (-1 < unit) {
LAB_00445a4e:
    while( true ) {
      dlg_load_game_section(&dlg,ADDR(0x6265f4, ((u8 *)&g.d_006265f4)),1);
      dialog_set_default_choice((DialogOptionList *)&dlg,(uint)game.difficulty);
      dialog_set_position
                ((DialogCore *)&dlg,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      level = dlg_show_modal(&dlg,0);
      if (level < 0) break;
      game.difficulty = (u8)level;
      if ((u8)level == '\0') {
        game.game_options = game.game_options | 0x100;
      }
      else {
        game.game_options = game.game_options & 0xfffffeff;
      }
      while( true ) {
        saved_resume_new_game = 0;
        turn_resume_new_game = 0;
        dlg_checks_clear();
        dlg_check_set(0,(int)prefs_mp_open_game);
        dlg_check_set(1,(int)prefs_mp_kill_on_retire);
        dlg_check_set(2,(int)prefs_mp_show_human_starts);
        dlg_check_set(3,(int)prefs_mp_chat_from_start);
        dlg_check_set(4,(int)prefs_mp_double_production);
        dlg_check_set(5,(int)prefs_mp_double_moves);
        dialog_load_text_section(&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x626600, ((u8 *)&g.d_00626600)),0,0,0,0,0,0);
        if (ini_simultaneous_allowed == 0) {
          mp_simultaneous_moves = 0;
          mp_simultaneous_setting = 0;
        }
        else {
          text_clear();
          text_append_label(0x364);
          dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
          dlg_check_set(6,(int)prefs_mp_simultaneous_moves);
        }
        if (((byte)dlg.style_flags & 4) != 0) {
          for (i = 0; i < (int)dlg.option_count; i++) {
            dialog_set_option_checked
                      ((DialogOptionList *)&dlg,i,
                       1 << ((byte)i & 0x1f) & dlg_check_bits);
          }
        }
        dialog_set_position
                  ((DialogCore *)&dlg,
                   ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        unit = dlg_show_modal(&dlg,0);
        snd_play_effect(0x6a,0,0,0);
        if (unit < 0) break;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,0);
        mp_open_game = (short)value;
        prefs_mp_open_game = mp_open_game;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,1);
        mp_kill_civ_on_retire = (short)value;
        prefs_mp_kill_on_retire = mp_kill_civ_on_retire;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,2);
        mp_show_human_starts = (short)value;
        prefs_mp_show_human_starts = mp_show_human_starts;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,3);
        mp_chat_from_start = (short)value;
        prefs_mp_chat_from_start = mp_chat_from_start;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,4);
        mp_double_production = (short)value;
        prefs_mp_double_production = mp_double_production;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,5);
        mp_double_moves = (short)value;
        prefs_mp_double_moves = mp_double_moves;
        if (ini_simultaneous_allowed != 0) {
          value = dialog_option_is_checked((DialogOptionList *)&dlg,6);
          mp_simultaneous_setting = (short)value;
          prefs_mp_simultaneous_moves = mp_simultaneous_setting;
        }
        saved_resume_new_game = 1;
        turn_resume_new_game = 1;
        unit = setup_choose_game_timer(0);
        if (unit == 0) {
          turn_resume_civ = (i8)human_civ;
          saved_turn_civ = (i8)human_civ;
          eh_state = eh_state & 0xffffff00;
          /* inlined unwind funclet 00445e15 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
          eh_state = 0xffffffff;
          /* inlined unwind funclet 00445e21 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
          value = 0;
          goto LAB_00445e37;
        }
      }
    }
  }
  goto LAB_00445759;
}
#undef cd_music_available
#undef dlg_check_bits
#undef human_civ
#undef ini_simultaneous_allowed
#undef mp_chat_from_start
#undef mp_double_moves
#undef mp_double_production
#undef mp_kill_civ_on_retire
#undef mp_open_game
#undef mp_show_human_starts
#undef mp_simultaneous_moves
#undef mp_simultaneous_setting
#undef prefs_game_options
#undef prefs_message_options
#undef prefs_mp_chat_from_start
#undef prefs_mp_double_moves
#undef prefs_mp_double_production
#undef prefs_mp_kill_on_retire
#undef prefs_mp_open_game
#undef prefs_mp_show_human_starts
#undef prefs_mp_simultaneous_moves
#undef saved_resume_new_game
#undef saved_turn_civ
#undef scenario_max_turns
#undef scenario_objective_civ
#undef scenario_tech_paradigm
#undef screen_height
#undef turn_resume_civ
#undef turn_resume_new_game
#undef palette
#undef dlg
#undef i
#undef dst
#undef level
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00448de6 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl tutorial_icon_sprite_global_init(void)

{
  tutorial_icon_sprite_static_init();
  tutorial_icon_sprite_reg_atexit();
  return;
}

/* 00448e00 auto */
void __cdecl tutorial_icon_sprite_static_init(void)

{
  sprite_init((Sprite *)&tutorial_icon_sprite);
  return;
}

/* 00448e1a auto */
void __cdecl tutorial_icon_sprite_reg_atexit(void)

{
  _atexit(tutorial_icon_sprite_static_dtor);
  return;
}

/* 00448e37 auto */
void __cdecl tutorial_icon_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&tutorial_icon_sprite);
  return;
}

/* 00453f90 auto */
#define value_type (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define key_path (*(char (*)[1024])(frame_ + FRAME_OFF(8)))
#define value_size (*(int *)(frame_ + FRAME_OFF(1032)))
#define value_ptr (*(int * *)(frame_ + FRAME_OFF(1036)))
#define language (*(int *)(frame_ + FRAME_OFF(1040)))
void __cdecl registry_load_default_language(void)

{
  i8 frame_[FRAME_OFF(1048)] __attribute__((aligned(8)));  /* original stack frame */
  
  language = 1;
  _sprintf(key_path,s_Software__s__s_006269a4,PTR_s_MicroProse_Software_0061c354,
           PTR_s_Civilization_II_Multiplayer_Gold_0061c358);
  value_ptr = (int *)registry_read_value((iptr)key_path,ADDR(0x6269b4, ((u8 *)&g.d_006269b4)),(iptr)&value_size,(iptr)value_type);
  if ((value_ptr == (int *)0x0) || (value_size == 0)) {
    language = 0;
  }
  else {
    language = *value_ptr;
  }
  if (language == 0) {
    language = 1;
  }
  _sprintf(key_path,s_Software__s__s_006269c4,PTR_s_MicroProse_Software_0061c354,
           PTR_s_Civilization_II_Multiplayer_Gold_0061c358);
  registry_write_value((iptr)key_path,ADDR(0x6269d4, ((u8 *)&g.d_006269d4)),(iptr)&language,4,4);
  registry_language_id = language;
  return;
}
#undef value_type
#undef key_path
#undef value_size
#undef value_ptr
#undef language

/* 0045406c auto */
#define hkey (*(HKEY *)(frame_ + FRAME_OFF(0)))
#define disposition (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define rc (*(int *)(frame_ + FRAME_OFF(8)))
bool __cdecl registry_write_value(iptr key_path,iptr value_name,iptr data,DWORD data_size,DWORD value_type)

{
  LSTATUS LVar1;
  bool ok;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  LVar1 = RegCreateKeyExA((HKEY)0x80000002,(LPCSTR)key_path,0,&registry_key_class_str,0,0x20006,
                          (LPSECURITY_ATTRIBUTES)0x0,&hkey,&disposition);
  if (LVar1 == 0) {
    rc = RegSetValueExA(hkey,(LPCSTR)value_name,0,value_type,(BYTE *)data,data_size);
    RegCloseKey(hkey);
    ok = rc == 0;
  }
  else {
    RegCloseKey(hkey);
    ok = false;
  }
  return ok;
}
#undef hkey
#undef disposition
#undef rc

/* 00454103 auto */
#define data_size2 (*(DWORD *)(frame_ + FRAME_OFF(0)))
#define hkey (*(HKEY *)(frame_ + FRAME_OFF(4)))
#define value_type (*(DWORD *)(frame_ + FRAME_OFF(8)))
i8 * __cdecl registry_read_value(iptr key_path,iptr value_name,iptr out_size,iptr out_type)

{
  LSTATUS LVar1;
  i8 *result;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  data_size2 = 0x800;
  _memset(&registry_value_buffer,0,0x800);
  *(i32 *)out_size = 0;
  *(i32 *)out_type = 0;
  LVar1 = RegOpenKeyExA((HKEY)0x80000002,(LPCSTR)key_path,0,0x20019,&hkey);
  if (LVar1 == 0) {
    LVar1 = RegQueryValueExA(hkey,(LPCSTR)value_name,(LPDWORD)0x0,&value_type,&registry_value_buffer,&data_size2);
    if (LVar1 == 0) {
      *(DWORD *)out_type = value_type;
      *(DWORD *)out_size = data_size2;
      RegCloseKey(hkey);
      result = &registry_value_buffer;
    }
    else {
      RegCloseKey(hkey);
      result = (i8 *)0x0;
    }
  }
  else {
    RegCloseKey(hkey);
    result = (i8 *)0x0;
  }
  return result;
}
#undef data_size2
#undef hkey
#undef value_type

/* 004675b0 auto */
void __cdecl scenario_events_global_init(void)

{
  scenario_events_static_init();
  scenario_events_reg_atexit();
  return;
}

/* 004675ca auto */
void __cdecl scenario_events_static_init(void)

{
  events_ctor((ScenarioEvents *)&scenario_events,50000);
  return;
}

/* 004675e9 auto */
void __cdecl scenario_events_reg_atexit(void)

{
  _atexit(scenario_events_static_dtor);
  return;
}

/* 00467606 auto */
void __cdecl scenario_events_static_dtor(void)

{
  events_dtor((DialogCore *)&scenario_events);
  return;
}

/* 00467620 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl main_frame_wnd_global_init(void)

{
  main_frame_wnd_static_init();
  main_frame_wnd_reg_atexit();
  return;
}

/* 0046763a auto */
void __cdecl main_frame_wnd_static_init(void)

{
  wnd_ctor((ModalMenuWindow *)&main_frame_wnd);
  return;
}

/* 00467654 auto */
void __cdecl main_frame_wnd_reg_atexit(void)

{
  _atexit(main_frame_wnd_atexit_dtor);
  return;
}

/* 00467671 auto */
void __cdecl main_frame_wnd_atexit_dtor(void)

{
  wnd_dtor((WndBase *)&main_frame_wnd);
  return;
}

/* 0046da40 auto */
#define opening_video_player (*(i8 * *)((u8 *)&g.d_0062af14))
#define host_wnd (*(ModalMenuWindow *)(frame_ + FRAME_OFF(4)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(188)))
#define dll (*(DllHandle *)(frame_ + FRAME_OFF(1264)))
#define path (*(i8 (*)[128])(frame_ + FRAME_OFF(1268)))
#define player (*(i8 (*)[72])(frame_ + FRAME_OFF(1396)))
#define player_wnd (*(i8 (*)[2528])(frame_ + FRAME_OFF(1468)))
#define screen_rect2 (*(i8 (*)[8])(frame_ + FRAME_OFF(3996)))
#define rect_width2 (*(i32 *)(frame_ + FRAME_OFF(4004)))
#define rect_height2 (*(int *)(frame_ + FRAME_OFF(4008)))
#define open_rc (*(int *)(frame_ + FRAME_OFF(4012)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(4016)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4020)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(4024)))
void __cdecl intro_play_opening_video(void)

{
  int found;
  i8 frame_[FRAME_OFF(4032)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  mmwnd_ctor((DocumentWindow *)player);
  eh_state = 0;
  wnd_ctor(&host_wnd);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  palette_init(&palette);
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  dll_handle_init(&dll);
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  gfx_get_screen_rect((iptr)screen_rect2);
  opening_video_player = player;
  str_clear((iptr)path);
  str_append((iptr)path,ADDR(0x62af18, ((u8 *)&g.d_0062af18)));
  found = file_resolve_path((iptr)path);
  if (found == 0) {
    (*(i8 *)((char *)&eh_state + 0)) = 2;
    /* inlined unwind funclet 0046dd98 */ { dll_free((DllHandle *)((iptr)&dll)); }
    (*(i8 *)((char *)&eh_state + 0)) = 1;
    /* inlined unwind funclet 0046dda4 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
    /* inlined unwind funclet 0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&host_wnd)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&player)); }
  }
  else {
    dll_handle_load(&dll,(iptr)path);
    str_clear((iptr)path);
    str_append((iptr)path,ADDR(0x62af2c, ((u8 *)&g.d_0062af2c)));
    found = file_resolve_path((iptr)path);
    if (found == 0) {
      (*(i8 *)((char *)&eh_state + 0)) = 2;
      /* inlined unwind funclet 0046dd98 */ { dll_free((DllHandle *)((iptr)&dll)); }
      (*(i8 *)((char *)&eh_state + 0)) = 1;
      /* inlined unwind funclet 0046dda4 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
      /* inlined unwind funclet 0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&host_wnd)); }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&player)); }
    }
    else {
      wnd_create_with_cmd_proc
                ((WndBase *)&host_wnd,ADDR(0x62af44, ((u8 *)&g.d_0062af44)),0x800,0,0,rect_width2,rect_height2 + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
      wnd_set_bg_color((WndBase *)&host_wnd,0);
      opening_video_player = player;
      avi_player_create((MediaWindow *)player,ADDR(0x62af48, ((u8 *)&g.d_0062af48)),0x800,0,0);
      wnd_set_lbuttonup_handler((WndEventHandlers *)(player_wnd + 0x10),ADDR(0x46dea1, intro_video_on_click));
      wnd_set_keydown_handler((WndEventHandlers *)(player_wnd + 0x10),ADDR(0x46de25, intro_video_on_keydown));
      avi_player_set_end_callback((AviPlayerEndCbSetView *)player,ADDR(0x46dde0, intro_video_on_end));
      avi_player_set_double_size((MediaWindow *)player,1);
      open_rc = avi_player_open((AviPlayerOpenView *)player,(iptr)path);
      if (open_rc == 0) {
        surface_fill((DibSurface *)player,0);
        wnd_center((WndCenterView *)player_wnd);
        wnd_handle_show_raise((WndBase *)&host_wnd);
        wnd_flush_paint();
        window_show((WindowObjectView *)player);
        wnd_flush_paint();
        avi_player_play((AviPlayerPlayView *)player);
        wnd_set_capture((WndBase *)player_wnd);
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((ModalMenuWindow *)player_wnd,ADDR(0x403585, net_modal_idle_poll));
        }
        wnd_run_modal_loop((ModalMenuWindow *)player_wnd);
        wnd_set_modal_idle_callback((ModalMenuWindow *)player_wnd,0);
        wnd_release_capture((WndBase *)player_wnd);
        avi_player_pause((AviPlayerPauseView *)player);
        wnd_hide((WndBase *)player_wnd);
        wnd_flush_paint();
        wnd_hide((WndBase *)&host_wnd);
        opening_video_player = (i8 *)0x0;
        dll_handle_free(&dll);
        (*(i8 *)((char *)&eh_state + 0)) = 2;
        /* inlined unwind funclet 0046dd98 */ { dll_free((DllHandle *)((iptr)&dll)); }
        (*(i8 *)((char *)&eh_state + 0)) = 1;
        /* inlined unwind funclet 0046dda4 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
        eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
        /* inlined unwind funclet 0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&host_wnd)); }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&player)); }
      }
      else {
        if (open_rc == -0x7ffbfeac) {
          popup_game(ADDR(0x62af4c, ((u8 *)&g.d_0062af4c)));
        }
        opening_video_player = (i8 *)0x0;
        (*(i8 *)((char *)&eh_state + 0)) = 2;
        /* inlined unwind funclet 0046dd98 */ { dll_free((DllHandle *)((iptr)&dll)); }
        (*(i8 *)((char *)&eh_state + 0)) = 1;
        /* inlined unwind funclet 0046dda4 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
        eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
        /* inlined unwind funclet 0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&host_wnd)); }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&player)); }
      }
    }
  }
  return;
}
#undef opening_video_player
#undef host_wnd
#undef palette
#undef dll
#undef path
#undef player
#undef player_wnd
#undef screen_rect2
#undef rect_width2
#undef rect_height2
#undef open_rc
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0046dde0 auto */
#define intro_theme_started (*(i32 *)((u8 *)&g.d_0062af10))
#define opening_video_player (*(int *)((u8 *)&g.d_0062af14))
void __cdecl intro_video_on_end(void)

{
  if (opening_video_player != 0) {
    wnd_end_modal_loop((ModalMenuWindow *)(opening_video_player + 0x48));
    intro_theme_started = 1;
    snd_play_effect(0x6b,0,1,0);
  }
  return;
}
#undef intro_theme_started
#undef opening_video_player

/* 0046de25 auto */
#define intro_theme_started (*(i32 *)((u8 *)&g.d_0062af10))
#define opening_video_player (*(int *)((u8 *)&g.d_0062af14))
void __cdecl intro_video_on_keydown(int key)

{
  if ((0xcf < key) && (key < 0xd3)) {
    snd_play_effect(0x6b,0,1,0);
    intro_theme_started = 1;
    if (opening_video_player != 0) {
      wnd_end_modal_loop((ModalMenuWindow *)(opening_video_player + 0x48));
    }
  }
  return;
}
#undef intro_theme_started
#undef opening_video_player

/* 0046dea1 auto */
#define opening_video_player (*(int *)((u8 *)&g.d_0062af14))
void __cdecl intro_video_on_click(void)

{
  if (opening_video_player != 0) {
    wnd_end_modal_loop((ModalMenuWindow *)(opening_video_player + 0x48));
  }
  return;
}
#undef opening_video_player

/* 00472f10 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl scenario_title_surface_global_init(void)

{
  scenario_title_surface_static_init();
  scenario_title_surface_reg_atexit();
  return;
}

/* 00472f2a auto */
void __cdecl scenario_title_surface_static_init(void)

{
  surface_ctor((DibSurface *)&scenario_title_surface);
  return;
}

/* 00472f44 auto */
void __cdecl scenario_title_surface_reg_atexit(void)

{
  _atexit(scenario_title_surface_atexit_dtor);
  return;
}

/* 00472f61 auto */
void __cdecl scenario_title_surface_atexit_dtor(void)

{
  surface_dtor((DibSurface *)&scenario_title_surface);
  return;
}

/* 00472f7b auto */
#define save_layout_record (*(i16 *)((u8 *)&g.d_0066c600))
#define saved_layout_valid (*(i32 *)((u8 *)&g.d_00655280))
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl save_pack_layout_rects(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  save_layout_record = (i16)saved_layout_valid;
  rect_pack_to_short(ADDR(0x655284, ((u8 *)&g.d_00655284)),ADDR(0x66c602, ((u8 *)&g.d_0066c602)));
  rect_pack_to_short(ADDR(0x655294, ((u8 *)&g.d_00655294)),ADDR(0x66c60a, ((u8 *)&g.d_0066c60a)));
  for (i = 0; i < 8; i++) {
    rect_pack_to_short((iptr)(&map_view_saved_rects + i * 0x10),i * 8 + ADDR(0x66c612, ((u8 *)&g.d_0066c60a + 8)));
  }
  rect_pack_to_short(ADDR(0x655324, ((u8 *)&g.d_00655324)),ADDR(0x66c652, ((u8 *)&g.d_0066c652)));
  rect_pack_to_short(ADDR(0x655334, ((u8 *)&g.d_00655334)),ADDR(0x66c65a, ((u8 *)&g.d_0066c65a)));
  rect_pack_to_short(ADDR(0x655344, ((u8 *)&g.d_00655344)),ADDR(0x66c662, ((u8 *)&g.d_0066c662)));
  return;
}
#undef save_layout_record
#undef saved_layout_valid
#undef i

/* 00473064 auto */
#define save_layout_record (*(short *)((u8 *)&g.d_0066c600))
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl save_unpack_layout_rects(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  saved_layout_valid = (int)save_layout_record;
  rect_unpack_from_short(ADDR(0x66c602, ((u8 *)&g.d_0066c602)),ADDR(0x655284, ((u8 *)&g.d_00655284)));
  rect_unpack_from_short(ADDR(0x66c60a, ((u8 *)&g.d_0066c60a)),ADDR(0x655294, ((u8 *)&g.d_00655294)));
  for (i = 0; i < 8; i++) {
    rect_unpack_from_short(i * 8 + ADDR(0x66c612, ((u8 *)&g.d_0066c60a + 8)),(iptr)(&map_view_saved_rects + i * 0x10));
  }
  rect_unpack_from_short(ADDR(0x66c652, ((u8 *)&g.d_0066c652)),ADDR(0x655324, ((u8 *)&g.d_00655324)));
  rect_unpack_from_short(ADDR(0x66c65a, ((u8 *)&g.d_0066c65a)),ADDR(0x655334, ((u8 *)&g.d_00655334)));
  rect_unpack_from_short(ADDR(0x66c662, ((u8 *)&g.d_0066c662)),ADDR(0x655344, ((u8 *)&g.d_00655344)));
  return;
}
#undef save_layout_record
#undef saved_layout_valid
#undef i

/* 004732a6 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl save_read_units_cities(int version,iptr file)

{
  size_t nread;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (version < 0x2a) {
    if (version == 0x29) {
      for (unit = 0; unit < game.num_units; unit++) {
        nread = _fread(units + unit,0x1e,1,(FILE *)file);
        if (nread == 0) {
          return 0;
        }
      }
      if ((game.num_cities != 0) &&
         (nread = _fread(cities,game.num_cities * 0x58,1,(FILE *)file), nread == 0)) {
        return 0;
      }
      for (unit = 0; unit < game.num_units; unit++) {
        if (units[unit].id != 0) {
          units[unit].id = next_unit_id;
          next_unit_id++;
        }
      }
      for (unit = 0; unit < game.num_cities; unit++) {
        if (cities[unit].id != 0) {
          cities[unit].id = next_city_id;
          next_city_id++;
        }
      }
    }
    else {
      for (unit = 0; unit < game.num_units; unit++) {
        nread = _fread(units + unit,0x1a,1,(FILE *)file);
        if (nread == 0) {
          return 0;
        }
      }
      for (unit = 0; unit < game.num_cities; unit++) {
        nread = _fread(cities + unit,0x54,1,(FILE *)file);
        if (nread == 0) {
          return 0;
        }
      }
      for (unit = 0; unit < game.num_units; unit++) {
        units[unit].id = next_unit_id;
        next_unit_id++;
      }
      for (unit = 0; unit < game.num_cities; unit++) {
        cities[unit].id = next_city_id;
        next_city_id++;
      }
    }
  }
  else {
    if ((game.num_units != 0) &&
       (nread = _fread(units,(int)game.num_units << 5,1,(FILE *)file), nread == 0)) {
      return 0;
    }
    if ((game.num_cities != 0) &&
       (nread = _fread(cities,game.num_cities * 0x58,1,(FILE *)file), nread == 0)) {
      return 0;
    }
    for (unit = 0; unit < game.num_units; unit++) {
      if (units[unit].id != 0) {
        units[unit].id = next_unit_id;
        next_unit_id++;
      }
    }
    for (unit = 0; unit < game.num_cities; unit++) {
      if (cities[unit].id != 0) {
        cities[unit].id = next_city_id;
        next_city_id++;
      }
    }
  }
  return 1;
}
#undef unit

/* 00473660 auto */
#define enemy_count (*(uint *)(frame_ + FRAME_OFF(4)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(8)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(12)))
#define pad (*(i8 (*)[4])(frame_ + FRAME_OFF(16)))
i32 __cdecl save_load_gpk(int version,iptr file)

{
  size_t nread;
  int alive_count;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (version < 0x28) {
    if ((version != 0x26) && (version != 0x27)) {
      return 0;
    }
    for (civ2 = 0; civ2 < 8; civ2++) {
      for (civ = 0; civ < 0x3e; civ++) {
        *(i8 *)&civs[civ2].units_active[civ] = 0;
        *(i8 *)&civs[civ2].units_lost[civ] = 0;
        *(i8 *)&civs[civ2].units_in_production[civ] = 0;
      }
    }
    for (civ = 0; civ < 100; civ++) {
      game.first_discoverer[civ] = '\0';
      game.advance_known_by[civ] = '\0';
      for (civ2 = 0; civ2 < 8; civ2++) {
        *(i8 *)&civs[civ2].advance_source[civ] = 0;
      }
    }
    for (civ2 = 0; civ2 < 8; civ2++) {
      for (civ = 0; civ < 0xd; civ++) {
        *(i8 *)&civs[civ2].advances[civ] = 0;
      }
    }
    nread = _fread(&game,0x36,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    nread = _fread(game.first_discoverer,0x5d,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    nread = _fread(game.advance_known_by,0x5d,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    nread = _fread(game.wonder_city,0x4c,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    alive_count = bits_count8((uint)game.civs_alive);
    enemy_count = alive_count - 1;
    if ((game.civs_alive & 1) != 0) {
      enemy_count = alive_count - 2;
    }
    if (game.num_enemies != enemy_count) {
      dbg_logf_int2(ADDR(0x62b9ec, ((u8 *)&g.d_0062b9ec)),(uint)game.num_enemies,(uint)game.civs_alive);
      game.num_enemies = (u8)enemy_count;
    }
    nread = _fread(civ_names,0x790,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    for (civ = 0; civ < 8; civ++) {
      nread = _fread(civs + civ,0x58,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(civs[civ].advances,0xc,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(&civs[civ].num_military_units,0xe,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(civs[civ].advance_source,0x5d,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(civs[civ].units_active,0x36,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(civs[civ].units_lost,0x36,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(civs[civ].units_in_production,0x36,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(pad,1,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
      nread = _fread(civs[civ].continent_military,0x402,1,(FILE *)file);
      if (nread == 0) {
        return 0;
      }
    }
  }
  else {
    nread = _fread(&game,0x14a,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    alive_count = bits_count8((uint)game.civs_alive);
    enemy_count = alive_count - 1;
    if ((game.civs_alive & 1) != 0) {
      enemy_count = alive_count - 2;
    }
    if (game.num_enemies != enemy_count) {
      dbg_logf_int2(ADDR(0x62b9a0, ((u8 *)&g.d_0062b9a0)),(uint)game.num_enemies,(uint)game.civs_alive);
      game.num_enemies = (u8)enemy_count;
    }
    nread = _fread(civ_names,0x790,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
    nread = _fread(civs,0x2ca0,1,(FILE *)file);
    if (nread == 0) {
      return 0;
    }
  }
  return 1;
}
#undef enemy_count
#undef civ
#undef civ2
#undef pad

/* 00473c12 auto */
i32 __cdecl save_write_str(char *str,iptr file)

{
  int rc;
  i32 result;
  
  rc = _fputs(str,(FILE *)file);
  if (rc == -1) {
    result = 0xffffffff;
  }
  else {
    rc = _fputc(0,(FILE *)file);
    if (rc == -1) {
      result = 0xffffffff;
    }
    else {
      result = 0;
    }
  }
  return result;
}

/* 00473c68 auto */
#define len (*(iptr *)(frame_ + FRAME_OFF(4)))
#define buf (*(char (*)[260])(frame_ + FRAME_OFF(8)))
#define ch (*(int *)(frame_ + FRAME_OFF(268)))
#define result (*(int *)(frame_ + FRAME_OFF(272)))
/* WARNING: Unable to use type for symbol next_len */

int __cdecl save_read_event_str(iptr file)

{
  char *cur;
  int saved_ch;
  size_t str_len;
  int next_len;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = 0;
  do {
    ch = _fgetc((FILE *)file);
    saved_ch = ch;
    if (ch == -1) {
      return 0;
    }
    if (0xfe < len) break;
    next_len = len + 1;
    buf[len] = (char)ch;
    ch = saved_ch;
    cur = buf + len;
    len = next_len;
  } while (*cur != '\0');
  buf[len] = '\0';
  str_len = _strlen(buf);
  result = memblock_alloc(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),str_len + 1);
  if (result == 0) {
    error_report(0xfffffff7,3,0,0,0);
    result = 0;
  }
  else {
    crt_strcpy(result,buf);
  }
  return result;
}
#undef len
#undef buf
#undef ch
#undef result

/* 00473d5e auto */
void __cdecl save_set_file_ext(int is_scenario)

{
  if (is_scenario == 0) {
    if (game.multiplayer == '\0') {
      crt_strcpy(&save_file_path,&save_ext_sav_str);
    }
    else if (game.multiplayer == 1) {
      crt_strcpy(&save_file_path,&save_ext_hot_str);
    }
    else if (game.multiplayer == 2) {
      crt_strcpy(&save_file_path,&save_ext_eml_str);
    }
    else if ((((game.multiplayer == 3) || (game.multiplayer == 4)) ||
             (game.multiplayer == 5)) || (game.multiplayer == 6)) {
      crt_strcpy(&save_file_path,&save_ext_net_str);
    }
  }
  else {
    crt_strcpy(&save_file_path,&save_ext_scn_str);
  }
  return;
}

/* 00473e55 auto */
#define cursor (*(iptr *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl save_file_filter(int save_only,int is_scenario,int is_mp)

{
  size_t len;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (is_scenario == 0) {
    if (is_mp == 0) {
      _memset(&save_file_filter_buf,0,0x104);
      cursor = save_filter_add_entry((uint)game.multiplayer,ADDR(0x66c4f8, ((u8 *)&g.d_0066c4f8)));
      if (save_only == 0) {
        if (game.multiplayer != '\0') {
          cursor = save_filter_add_entry(0,cursor);
        }
        if (game.multiplayer < 3) {
          cursor = save_filter_add_entry(3,cursor);
        }
        if (game.multiplayer != 1) {
          save_filter_add_entry(1,cursor);
        }
      }
    }
    else {
      _memset(&save_file_filter_buf,0,0x104);
      str_append_label(ADDR(0x66c4f8, ((u8 *)&g.d_0066c4f8)),0x105);
      crt_strcat(&save_file_filter_buf,s____mp__0062ba74);
      len = _strlen(&save_file_filter_buf);
      crt_strcat(len + ADDR(0x66c4f9, ((u8 *)&g.d_0066c4f8 + 1)),&save_filter_mp_pattern_str);
    }
  }
  else {
    _memset(&save_file_filter_buf,0,0x104);
    str_append_label(ADDR(0x66c4f8, ((u8 *)&g.d_0066c4f8)),0x19f);
    crt_strcat(&save_file_filter_buf,s____scn__0062ba60);
    len = _strlen(&save_file_filter_buf);
    crt_strcat(len + ADDR(0x66c4f9, ((u8 *)&g.d_0066c4f8 + 1)),s___scn_0062ba6c);
  }
  return &save_file_filter_buf;
}
#undef cursor

/* 00473ff2 auto */
char * __cdecl save_filter_add_entry(i32 kind,iptr buf)

{
  size_t len;
  char *next;
  
  switch(kind) {
  case 0:
    str_append_label(buf,0xee);
    crt_strcat(buf,s____sav__0062ba84);
    len = _strlen((char *)buf);
    next = (char *)(buf + len + 1);
    crt_strcat(next,s___sav_0062ba90);
    len = _strlen(next);
    next = next + len + 1;
    break;
  case 1:
    str_append_label(buf,0x357);
    crt_strcat(buf,s____hot__0062ba98);
    len = _strlen((char *)buf);
    next = (char *)(buf + len + 1);
    crt_strcat(next,s___hot_0062baa4);
    len = _strlen(next);
    next = next + len + 1;
    break;
  case 2:
    str_append_label(buf,0x35a);
    crt_strcat(buf,s____eml__0062baac);
    len = _strlen((char *)buf);
    next = (char *)(buf + len + 1);
    crt_strcat(next,s___eml_0062bab8);
    len = _strlen(next);
    next = next + len + 1;
    break;
  case 3:
  case 4:
  case 5:
  case 6:
    str_append_label(buf,0x35d);
    crt_strcat(buf,s____net__0062bac0);
    len = _strlen((char *)buf);
    next = (char *)(buf + len + 1);
    crt_strcat(next,s___net_0062bacc);
    len = _strlen(next);
    next = next + len + 1;
    break;
  default:
    next = (char *)0x0;
  }
  return next;
}

/* 004741be auto */
#define destroyed_civ_count (*(i16 *)((u8 *)&g.d_00655128))
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define map_view_center_x (*(i16 *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(i16 *)((u8 *)&g.d_0066ca8a))
#define mapview_zoom (*(i16 *)((u8 *)&g.d_0066ca8c))
#define mp_turn_civ (*(byte *)((u8 *)&g.d_006ad578))
#define save_layout_record (*(i16 *)((u8 *)&g.d_0066c600))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define scenario_flags (*(i16 *)((u8 *)&g.d_0064bc60))
#define count (*(int *)(frame_ + FRAME_OFF(0)))
#define saved_civ (*(uint *)(frame_ + FRAME_OFF(4)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(8)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(12)))
#define event (*(void * *)(frame_ + FRAME_OFF(16)))
#define file (*(FILE * *)(frame_ + FRAME_OFF(20)))
#define result (*(i32 *)(frame_ + FRAME_OFF(24)))
#define saved_humans (*(u8 *)(frame_ + FRAME_OFF(28)))
#define version (*(i16 (*)[2])(frame_ + FRAME_OFF(32)))
#define leader (*(int *)(frame_ + FRAME_OFF(36)))
#define path (*(char (*)[260])(frame_ + FRAME_OFF(40)))
i32 __cdecl save_write_game(iptr file_name,int is_scenario)

{
  char *dot;
  size_t nwritten;
  int rc;
  i8 frame_[FRAME_OFF(304)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  if (game.multiplayer == 1) {
    saved_humans = game.human_players;
    game.human_players = hotseat_human_players;
  }
  save_set_file_ext(is_scenario);
  crt_strcpy(path,file_name);
  dot = _strchr(path,0x2e);
  if (dot == (char *)0x0) {
    crt_strcat(path,&save_file_path);
  }
  file = _fopen(path,&save_write_mode);
  if (file != (FILE *)0x0) {
    save_write_cstr_eof((iptr)PTR_s_CIVILIZE_0062b990,(iptr)file);
    game.saved_current_civ = (i8)human_civ;
    version[0] = 0x2c;
    nwritten = _fwrite(version,2,1,file);
    if (nwritten != 0) {
      if (is_scenario == 0) {
        game.game_flags = game.game_flags & 0xffbf;
      }
      else {
        game.game_flags = game.game_flags | 0x40;
        for (advance = 0; advance < 100; advance++) {
          game.advance_known_by[advance] = '\0';
          for (civ = 1; civ < 8; civ++) {
            rc = civ_has_advance(civ,advance);
            if (rc != 0) {
              game.advance_known_by[advance] =
                   game.advance_known_by[advance] | (byte)(1 << ((byte)civ & 0x1f));
            }
          }
          if (game.advance_known_by[advance] != '\0') {
            rc = bits_count8((int)(char)game.advance_known_by[advance]);
            if (rc == 1) {
              for (civ = 1; civ < 8; civ++) {
                rc = civ_has_advance(civ,advance);
                if (rc != 0) {
                  game.first_discoverer[advance] = (byte)civ;
                }
              }
            }
            else {
              game.first_discoverer[advance] = 8;
            }
          }
        }
        for (civ = 1; civ < 8; civ++) {
          civs[civ].flags = civs[civ].flags & 0xff96;
        }
      }
      if ((is_scenario != 0) || ((game.game_flags & 0x80) != 0)) {
        for (civ = 1; civ < 8; civ++) {
          if (-1 < leaders[civs[civ].tribe].adjective) {
            str_clear(civ * 0xf2 + ADDR(0x64bd2a, ((u8 *)&civ_names + 50)));
            str_append_string_id((iptr)&civ_names[civ].adjective,
                               (int)leaders[civs[civ].tribe].adjective);
          }
          if (-1 < leaders[civs[civ].tribe].plural) {
            str_clear(civ * 0xf2 + ADDR(0x64bd12, ((u8 *)&civ_names + 26)));
            str_append_string_id((iptr)&civ_names[civ].tribe_name,
                               (int)leaders[civs[civ].tribe].plural);
          }
          if (-1 < leaders[civs[civ].tribe].leader_name) {
            str_clear(civ * 0xf2 + ADDR(0x64bcfa, ((u8 *)&civ_names + 2)));
            str_append_string_id((iptr)&civ_names[civ].leader_name,
                               (int)leaders[civs[civ].tribe].leader_name);
          }
        }
      }
      nwritten = _fwrite(&game,0x14a,1,file);
      if (((((((nwritten != 0) && (nwritten = _fwrite(civ_names,0x790,1,file), nwritten != 0)) &&
             (nwritten = _fwrite(civs,0x2ca0,1,file), nwritten != 0)) &&
            ((rc = map_write((iptr)file,0), rc == 0 &&
             (nwritten = _fwrite(map_coarse[0],(int)map.quarter_w * (int)map.quarter_h,1,file),
             nwritten != 0)))) &&
           (nwritten = _fwrite(map_coarse[1],(int)map.quarter_w * (int)map.quarter_h,1,file),
           nwritten != 0)) &&
          ((nwritten = _fwrite(&landmass_table,0x400,1,file), nwritten != 0 &&
           ((game.num_units == 0 ||
            (nwritten = _fwrite(units,(int)game.num_units << 5,1,file), nwritten != 0)))))) &&
         ((game.num_cities == 0 ||
          (nwritten = _fwrite(cities,game.num_cities * 0x58,1,file), nwritten != 0)))) {
        for (leader = 0; leader < 0x15; leader++) {
          nwritten = _fwrite(&leaders[leader].times_used,1,1,file);
          if (((nwritten == 0) ||
              (nwritten = _fwrite(&leaders[leader].city_name_index,1,1,file), nwritten == 0)) ||
             (nwritten = _fwrite(&leaders[leader].female,1,1,file), nwritten == 0))
          goto LAB_0047530a;
        }
        nwritten = _fwrite(&map_cursor_x,2,1,file);
        if ((nwritten != 0) && (nwritten = _fwrite(&map_cursor_y,2,1,file), nwritten != 0)) {
          if (game.multiplayer == '\0') {
            nwritten = _fwrite(leaders + civs[game.player_civ].tribe,0x30,1,file);
            if (nwritten == 0) goto LAB_0047530a;
          }
          else {
            civ = (iptr)game.player_civ;
            for (leader = 0; leader < 8; leader++) {
              if ((1 << ((byte)leader & 0x1f) & (uint)game.human_players) != 0) {
                game.player_civ = (byte)leader;
                nwritten = _fwrite(leaders + civs[(char)(byte)leader].tribe,0x30,1,file);
                if (nwritten == 0) {
                  game.player_civ = (byte)civ;
                  goto LAB_0047530a;
                }
              }
            }
            game.player_civ = (byte)civ;
          }
          nwritten = _fwrite(&power_graph_history,0x4b0,1,file);
          if (nwritten != 0) {
            saved_screen_rect = screen_rect;
            saved_screen_rect_top = screen_rect_top;
            saved_screen_rect_right = ui_screen_rect_right;
            saved_screen_rect_bottom = ui_screen_rect_bottom;
            save_pack_layout_rects();
            nwritten = _fwrite(&save_layout_record,0x6a,1,file);
            if (nwritten != 0) {
              for (leader = 0; leader < 8; leader++) {
                nwritten = _fwrite(&map_view_open_flags + leader * 0x3f0,2,1,file);
                if (((nwritten == 0) ||
                    (nwritten = _fwrite(&mapview_track_moves + leader * 0x3f0,2,1,file), nwritten == 0))
                   || ((nwritten = _fwrite(&map_view_center_x + leader * 0x1f8,2,1,file), nwritten == 0
                       || ((nwritten = _fwrite(&mapview_center_y + leader * 0x1f8,2,1,file),
                           nwritten == 0 ||
                           (nwritten = _fwrite(&mapview_zoom + leader * 0x1f8,2,1,file),
                           nwritten == 0)))))) goto LAB_0047530a;
              }
              if ((((is_scenario == 0) && ((game.game_flags & 0x80) == 0)) ||
                  (nwritten = _fwrite(&scenario_flags,100,1,file), nwritten != 0)) &&
                 (nwritten = _fwrite(&destroyed_civ_count,0x152,1,file), nwritten != 0)) {
                if (game.multiplayer != '\0') {
                  saved_civ = (uint)saved_turn_civ;
                  saved_turn_civ = mp_turn_civ;
                  nwritten = _fwrite(&civ_saved_cursor_x,0x494,1,file);
                  if (nwritten == 0) goto LAB_0047530a;
                  saved_turn_civ = (byte)saved_civ;
                }
                if ((scenario_events_loaded != 0) && (is_scenario == 0)) {
                  rc = _fputs(&save_events_tag_str,file);
                  if (rc == -1) goto LAB_0047530a;
                  count = 0;
                  for (event = (void *)events_list_head; event != (void *)0x0;
                      event = *(void **)((int)event + 0x1bc)) {
                    count++;
                  }
                  nwritten = _fwrite(&count,4,1,file);
                  if (nwritten == 0) goto LAB_0047530a;
                  for (event = (void *)events_list_head; event != (void *)0x0;
                      event = *(void **)((int)event + 0x1bc)) {
                    nwritten = _fwrite(event,0x1bc,1,file);
                    if (nwritten == 0) goto LAB_0047530a;
                  }
                  for (event = (void *)events_list_head; event != (void *)0x0;
                      event = *(void **)((int)event + 0x1bc)) {
                    if (((((*(int *)((int)event + 8) != 0) &&
                          (rc = save_write_str(*(i32 *)((int)event + 8),
                                                      (iptr)file), rc == -1)) ||
                         ((*(int *)((int)event + 0x10) != 0 &&
                          (rc = save_write_str(*(i32 *)((int)event + 0x10),
                                                      (iptr)file), rc == -1)))) ||
                        ((*(int *)((int)event + 0x14) != 0 &&
                         (rc = save_write_str(*(i32 *)((int)event + 0x14),
                                                     (iptr)file), rc == -1)))) ||
                       ((*(int *)((int)event + 0x20) != 0 &&
                        (rc = save_write_str(*(i32 *)((int)event + 0x20),
                                                    (iptr)file), rc == -1))))
                    goto LAB_0047530a;
                    count = 0;
                    while ((count < 0x14 &&
                           (*(int *)((int)event + count * 4 + 0x38) != 0))) {
                      rc = save_write_str(*(i32 *)
                                                  ((int)event + count * 4 + 0x38),
                                                 (iptr)file);
                      if (rc == -1) goto LAB_0047530a;
                      count++;
                    }
                    if ((((((*(int *)((int)event + 0x88) != 0) &&
                           (rc = save_write_str(*(i32 *)((int)event + 0x88),
                                                       (iptr)file), rc == -1)) ||
                          ((*(int *)((int)event + 0x90) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0x90),
                                                       (iptr)file), rc == -1)))) ||
                         (((*(int *)((int)event + 0xc4) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0xc4),
                                                       (iptr)file), rc == -1)) ||
                          ((*(int *)((int)event + 0xcc) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0xcc),
                                                       (iptr)file), rc == -1)))))) ||
                        ((((*(int *)((int)event + 0xd4) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0xd4),
                                                       (iptr)file), rc == -1)) ||
                          ((*(int *)((int)event + 0xdc) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0xdc),
                                                       (iptr)file), rc == -1)))) ||
                         (((*(int *)((int)event + 0x13c) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0x13c),
                                                       (iptr)file), rc == -1)) ||
                          ((*(int *)((int)event + 0x140) != 0 &&
                           (rc = save_write_str(*(i32 *)((int)event + 0x140),
                                                       (iptr)file), rc == -1)))))))) ||
                       ((((*(int *)((int)event + 0x148) != 0 &&
                          (rc = save_write_str(*(i32 *)((int)event + 0x148),
                                                      (iptr)file), rc == -1)) ||
                         ((*(int *)((int)event + 0x174) != 0 &&
                          (rc = save_write_str(*(i32 *)((int)event + 0x174),
                                                      (iptr)file), rc == -1)))) ||
                        ((*(int *)((int)event + 0x184) != 0 &&
                         (rc = save_write_str(*(i32 *)((int)event + 0x184),
                                                     (iptr)file), rc == -1))))))
                    goto LAB_0047530a;
                  }
                }
                result = 0;
              }
            }
          }
        }
      }
    }
  }
LAB_0047530a:
  if (game.multiplayer == 1) {
    game.human_players = saved_humans;
  }
  if (file != (FILE *)0x0) {
    _fclose(file);
  }
  return result;
}
#undef destroyed_civ_count
#undef hotseat_human_players
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef map_view_center_x
#undef mapview_center_y
#undef mapview_zoom
#undef mp_turn_civ
#undef save_layout_record
#undef saved_turn_civ
#undef scenario_events_loaded
#undef scenario_flags
#undef count
#undef saved_civ
#undef civ
#undef advance
#undef event
#undef file
#undef result
#undef saved_humans
#undef version
#undef leader
#undef path

/* 00475666: written by hand in src/game/retvals.c */

/* 0047758c auto */
#define game_setup_complete (*(int *)((u8 *)&g.d_00654fd8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define text_buffer (*(char *)((u8 *)&g.d_00679640))
#define abs_year_rem_neg (*(int *)(frame_ + FRAME_OFF(4)))
#define abs_year_rem_pos (*(int *)(frame_ + FRAME_OFF(8)))
#define abs_year_div (*(int *)(frame_ + FRAME_OFF(12)))
#define abs_year (*(int *)(frame_ + FRAME_OFF(16)))
#define local_time (*(_SYSTEMTIME *)(frame_ + FRAME_OFF(24)))
#define num_buf (*(char (*)[31])(frame_ + FRAME_OFF(40)))
#define file_name_buf (*(char (*)[261])(frame_ + FRAME_OFF(71)))
#define filter_text (*(char *)(frame_ + FRAME_OFF(332)))
#define filter_text_tail (*(char (*)[259])(frame_ + FRAME_OFF(333)))
#define str_ptr (*(char * *)(frame_ + FRAME_OFF(592)))
void __cdecl game_save_dialog(int is_scenario)

{
  uptr desc_len;
  uptr pattern_len;
  i32 leader_name;
  size_t name_len;
  iptr title;
  int result;
  char *name_arg;
  i8 *filter_arg;
  i8 *ext_arg;
  i32 flag_arg;
  i8 frame_[FRAME_OFF(600)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game_setup_complete != 0) {
    mp_turn_timer_stop(1);
    do {
      save_set_file_ext(is_scenario);
      str_clear((iptr)&filter_text);
      str_append_label((iptr)&filter_text,(-(uint)(is_scenario == 0) & 0xffffff4f) + 0x19f);
      str_append_space((iptr)&filter_text);
      str_append_lparen((iptr)&filter_text);
      str_append((iptr)&filter_text,ADDR(0x62bb08, ((u8 *)&g.d_0062bb08)));
      str_append((iptr)&filter_text,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
      str_append_rparen((iptr)&filter_text);
      desc_len = _strlen(&filter_text);
      str_ptr = filter_text_tail + desc_len;
      str_clear((iptr)str_ptr);
      str_append((iptr)str_ptr,ADDR(0x62bb0c, ((u8 *)&g.d_0062bb0c)));
      str_append((iptr)str_ptr,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
      pattern_len = _strlen(str_ptr);
      str_ptr = str_ptr + pattern_len + 1;
      str_clear((iptr)str_ptr);
      str_clear((iptr)(file_name_buf + 1));
      leader_name = civ_leader_name(human_civ);
      crt_strcat(file_name_buf + 1,leader_name);
      file_name_buf[3] = 0;
      str_append((iptr)(file_name_buf + 1),ADDR(0x62bb10, ((u8 *)&g.d_0062bb10)));
      str_ptr = file_name_buf;
      while (str_ptr = str_ptr + 1, *str_ptr != '\0') {
        if ((31 < *str_ptr) && (*str_ptr < 'A')) {
          *str_ptr = '_';
        }
      }
      text_clear();
      if (game.year < 0) {
        text_append(ADDR(0x62bb18, ((u8 *)&g.d_0062bb18)));
      }
      else {
        text_append(ADDR(0x62bb14, ((u8 *)&g.d_0062bb14)));
      }
      str_append_space((iptr)(file_name_buf + 1));
      name_len = _strlen(file_name_buf + 1);
      file_name_buf[name_len] = text_buffer;
      if (game.year < 1) {
        abs_year = ~(int)game.year + 1;
      }
      else {
        abs_year = (int)game.year;
      }
      str_append_int((iptr)(file_name_buf + 1),abs_year);
      if ((game.multiplayer == 2) && (is_scenario == 0)) {
        GetLocalTime(&local_time);
        crt_strcat(file_name_buf + 1,&save_name_date_sep_str);
        __itoa((uint)(*(i32 *)((char *)&local_time + 0)) >> 0x10,num_buf,10);
        crt_strcat(file_name_buf + 1,num_buf);
        crt_strcat(file_name_buf + 1,&save_name_month_day_sep_str);
        __itoa((uint)local_time.wDay,num_buf,10);
        crt_strcat(file_name_buf + 1,num_buf);
        crt_strcat(file_name_buf + 1,&save_name_day_year_sep_str);
        __itoa((*(i32 *)((char *)&local_time + 0)) & 0xffff,num_buf,10);
        crt_strcat(file_name_buf + 1,num_buf);
        crt_strcat(file_name_buf + 1,&save_name_time_sep_str);
        __itoa((*(i32 *)((char *)&local_time + 8)) & 0xffff,num_buf,10);
        crt_strcat(file_name_buf + 1,num_buf);
        crt_strcat(file_name_buf + 1,&save_name_hour_min_sep_str);
        __itoa((uint)(*(i32 *)((char *)&local_time + 8)) >> 0x10,num_buf,10);
        crt_strcat(file_name_buf + 1,num_buf);
        crt_strcat(file_name_buf + 1,&save_name_min_sec_sep_str);
        __itoa((*(i32 *)((char *)&local_time + 12)) & 0xffff,num_buf,10);
        crt_strcat(file_name_buf + 1,num_buf);
      }
      crt_strcat(file_name_buf + 1,&save_name_ext_dot_str);
      crt_strcat(file_name_buf + 1,&save_file_ext_bare);
      __strlwr(file_name_buf + 1);
      if (((is_scenario != 0) || ((game.game_flags & 0x80) != 0)) && (scenario_year_increment < 0)) {
        str_clear((iptr)(file_name_buf + 1));
        if ((int)game.year / 0xc < 1) {
          abs_year_div = ~((int)game.year / 0xc) + 1;
        }
        else {
          abs_year_div = (int)game.year / 0xc;
        }
        str_append_int((iptr)(file_name_buf + 1),abs_year_div);
        if (game.year < 0) {
          if ((int)game.year % 0xc < 1) {
            abs_year_rem_neg = ~((int)game.year % 0xc) + 1;
          }
          else {
            abs_year_rem_neg = (int)game.year % 0xc;
          }
          str_append_label((iptr)(file_name_buf + 1),0x1af - abs_year_rem_neg);
        }
        else {
          if ((int)game.year % 0xc < 1) {
            abs_year_rem_pos = ~((int)game.year % 0xc) + 1;
          }
          else {
            abs_year_rem_pos = (int)game.year % 0xc;
          }
          str_append_label((iptr)(file_name_buf + 1),abs_year_rem_pos + 0x1a4);
        }
        crt_strcat(file_name_buf + 1,&save_file_path);
        __strlwr(file_name_buf + 1);
      }
      __chdir(&scenario_dir_path);
      save_file_filter(1,is_scenario,0);
      flag_arg = 1;
      leader_name = 0;
      ext_arg = &save_file_ext_bare;
      filter_arg = &save_file_filter_buf;
      name_arg = file_name_buf + 1;
      title = label_string(*(i32 *)
                                  (label_string_ids + 0x680 + (-(uint)(is_scenario == 0) & 0xffffff4f) * 4)
                                );
      result = ui_file_name_dialog(ADDR(0x6553d8, ((u8 *)&g.d_006553d8)),title,(iptr)name_arg,(iptr)filter_arg,(iptr)ext_arg,leader_name,flag_arg);
      if (result != 0) {
        __chdir(&game_home_dir);
        result = save_write_game((iptr)(file_name_buf + 1),is_scenario);
        if (result == 0) {
          if (is_scenario == 0) {
            if (game.multiplayer == 2) {
              text_set_string_arg(0,(iptr)(file_name_buf + 1));
              popup_game(ADDR(0x62bb4c, ((u8 *)&g.d_0062bb4c)));
            }
            else {
              title = civ_leader_title(human_civ);
              text_set_string_arg(0,title);
              title = civ_leader_name(human_civ);
              text_set_string_arg(1,title);
              title = civ_name_plural(human_civ);
              text_set_string_arg(2,title);
              text_clear();
              text_append_year((int)game.year);
              text_set_string_arg(3,ADDR(0x679640, ((u8 *)&g.d_00679640)));
              text_set_label_arg(4,difficulty_names[game.difficulty]);
              popup_game(ADDR(0x62bb58, ((u8 *)&g.d_0062bb58)));
            }
          }
          else {
            text_set_string_arg(0,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)));
            popup_game(ADDR(0x62bb44, ((u8 *)&g.d_0062bb44)));
          }
        }
        else {
          text_set_string_arg_b(0,(iptr)(&PTR_s_No_error_00639e60)[crt_errno]);
          popup_game(ADDR(0x62bb38, ((u8 *)&g.d_0062bb38)));
        }
        break;
      }
      __chdir(&game_home_dir);
    } while (game.multiplayer == 2);
    mp_turn_timer_resume(1);
  }
  return;
}
#undef game_setup_complete
#undef human_civ
#undef scenario_year_increment
#undef text_buffer
#undef abs_year_rem_neg
#undef abs_year_rem_pos
#undef abs_year_div
#undef abs_year
#undef local_time
#undef num_buf
#undef file_name_buf
#undef filter_text
#undef filter_text_tail
#undef str_ptr

/* 00477d8c auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define loaded_file_kind (*(i16 *)((u8 *)&g.d_006ad6ac))
#define net_host_flag (*(i8 *)((u8 *)&g.d_006ad2f7))
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define cheat_checked (*(i32 *)(frame_ + FRAME_OFF(4)))
#define pick_index (*(uint *)(frame_ + FRAME_OFF(12)))
#define find_data (*(_WIN32_FIND_DATAA *)(frame_ + FRAME_OFF(20)))
#define alt_pattern (*(CHAR (*)[260])(frame_ + FRAME_OFF(340)))
#define alt_count (*(int *)(frame_ + FRAME_OFF(600)))
#define slash_ptr (*(char * *)(frame_ + FRAME_OFF(604)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(608)))
#define file_path (*(i8 (*)[260])(frame_ + FRAME_OFF(612)))
#define failed (*(int *)(frame_ + FRAME_OFF(872)))
#define filter_text (*(char *)(frame_ + FRAME_OFF(876)))
#define filter_text_tail (*(char (*)[259])(frame_ + FRAME_OFF(877)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(1136)))
#define events_path (*(i8 (*)[260])(frame_ + FRAME_OFF(2212)))
#define str_ptr (*(char * *)(frame_ + FRAME_OFF(2472)))
#define view_index (*(int *)(frame_ + FRAME_OFF(2476)))
#define upper_path (*(char (*)[260])(frame_ + FRAME_OFF(2480)))
#define load_error (*(int *)(frame_ + FRAME_OFF(2740)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(2744)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2748)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(2752)))
int __cdecl game_load_dialog(int is_scenario,i32 unused_arg,int show_title)

{
  size_t str_len;
  iptr str_arg;
  int result;
  char *ext_match;
  HANDLE find_handle;
  BOOL BVar6;
  i8 *name_arg;
  i8 *filter_arg;
  i8 *ext_arg;
  i32 flag_arg;
  i32 flag_arg2;
  i8 frame_[FRAME_OFF(2760)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  failed = 1;
  palette_init(&palette);
  seh_state = 0;
  if (is_scenario == 0) {
    save_set_file_ext(0);
    loaded_file_kind = 1;
  }
  else {
    save_set_file_ext(1);
    loaded_file_kind = 2;
  }
  str_clear((iptr)&filter_text);
  str_append_label((iptr)&filter_text,(-(uint)(is_scenario == 0) & 0xffffff4f) + 0x19f);
  str_append_space((iptr)&filter_text);
  str_append_lparen((iptr)&filter_text);
  str_append((iptr)&filter_text,ADDR(0x62bb60, ((u8 *)&g.d_0062bb60)));
  str_append((iptr)&filter_text,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
  str_append_rparen((iptr)&filter_text);
  str_len = _strlen(&filter_text);
  str_ptr = filter_text_tail + str_len;
  str_clear((iptr)str_ptr);
  str_append((iptr)str_ptr,ADDR(0x62bb64, ((u8 *)&g.d_0062bb64)));
  str_append((iptr)str_ptr,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
  str_len = _strlen(str_ptr);
  str_ptr = str_ptr + str_len + 1;
  str_clear((iptr)str_ptr);
  crt_strcpy(file_path,&load_dialog_wildcard_str);
  crt_strcat(file_path,&save_file_ext_bare);
  __chdir(&scenario_dir_path);
  save_file_filter(0,is_scenario,0);
  flag_arg2 = 0;
  flag_arg = 1;
  ext_arg = &save_file_ext_bare;
  filter_arg = &save_file_filter_buf;
  name_arg = file_path;
  str_arg = label_string(*(i32 *)
                              (label_string_ids + 0x684 + (-(uint)(is_scenario == 0) & 0xffffff4f) * 4));
  result = ui_file_name_dialog(ADDR(0x6553d8, ((u8 *)&g.d_006553d8)),str_arg,(iptr)name_arg,(iptr)filter_arg,(iptr)ext_arg,flag_arg,flag_arg2);
  if (result == 0) {
    __chdir(&game_home_dir);
  }
  else {
    __chdir(&game_home_dir);
    for (view_index = 1; view_index < 8; view_index++) {
      if (*(short *)(&map_view_open_flags + view_index * 0x3f0) != 0) {
        *(i16 *)(&map_view_open_flags + view_index * 0x3f0) = 0;
        wnd_destroy_with_surface((DibSurface *)(&map_views + view_index * 0x3f0));
      }
    }
    crt_strcpy(upper_path,file_path);
    __strupr(upper_path);
    ext_match = _strstr(upper_path,&game_load_scn_ext_str);
    if (ext_match != (char *)0x0) {
      crt_strcpy(upper_path,file_path);
      slash_ptr = _strrchr(upper_path,0x5c);
      slash_ptr++;
      *slash_ptr = '\0';
      crt_strcpy(alt_pattern,upper_path);
      crt_strcat(alt_pattern,s___ALT_0062bb74);
      alt_count = 0;
      find_handle = FindFirstFileA(alt_pattern,&find_data);
      if (find_handle != (HANDLE)0xffffffff) {
        do {
          alt_count++;
          BVar6 = FindNextFileA(find_handle,&find_data);
        } while (BVar6 == 1);
      }
      if (alt_count != 0) {
        result = _rand();
        pick_index = (uint)(result * (alt_count + 1)) >> 0xf;
        if (pick_index != 0) {
          find_handle = FindFirstFileA(alt_pattern,&find_data);
          while (pick_index = pick_index - 1, pick_index != 0) {
            FindNextFileA(find_handle,&find_data);
          }
          crt_strcat(upper_path,find_data.cFileName);
          crt_strcpy(file_path,upper_path);
        }
      }
    }
    snd_play_effect(-0x6b,0,0,0);
    snd_play_effect(-0x6c,0,0,0);
    snd_play_effect(0x6a,0,0,0);
    load_error = save_read_game((iptr)file_path);
    if (load_error == 0) {
      ui_flush_input();
      if ((scenario_events_loaded == 0) && ((game.game_flags & 0x80) != 0)) {
        scenario_events_loaded = 0;
        __chdir(&scenario_dir_path);
        crt_strcpy(events_path,s_EVENTS__0062bbac);
        crt_strcat(events_path,&lang_file_ext);
        result = file_exists((iptr)events_path);
        if (result != 0) {
          crt_strcpy(events_path,&text_buffer);
          events_reset((ScenarioEvents *)&scenario_events,50000);
          result = events_parse_file
                            ((ScenarioEvents *)&scenario_events,ADDR(0x62bbc0, ((u8 *)&g.d_0062bbc0)),ADDR(0x62bbb4, ((u8 *)&g.d_0062bbb4)));
          if (result == 0) {
            events_compact();
            scenario_events_loaded = 1;
          }
          crt_strcpy(&text_buffer,events_path);
        }
      }
      if (scenario_events_loaded == 0) {
        events_reset((ScenarioEvents *)&scenario_events,50000);
      }
      game.game_options = prefs_game_options;
      snd_wave_set_buffer_count(8);
      snd_cd_detect_layout();
      if ((game.game_options & 8) != 0) {
        if (scenario_events_loaded == 0) {
          snd_sync_music_option();
        }
        else {
          events_check_scenario_loaded((ScenarioEvents *)&scenario_events);
          snd_sync_music_option();
        }
      }
      if (show_title != 0) {
        ui_flush_input();
        result = file_exists(ADDR(0x62bbc8, ((u8 *)&g.d_0062bbc8)));
        if ((result != 0) &&
           (result = surface_load_gif_file
                              ((DibSurface *)&scenario_title_surface,ADDR(0x62bbd4, ((u8 *)&g.d_0062bbd4)),10,0xc0,(iptr)&palette),
           result != 0)) {
          wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x66c670, ((u8 *)&g.d_0066c670)));
          wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
          wnd_maximize((WndBase *)&main_frame_wnd);
          wnd_flush_paint();
          input_flush_events();
        }
      }
      __chdir(&game_home_dir);
      failed = 0;
      str_arg = civ_leader_title(human_civ);
      text_set_string_arg(0,str_arg);
      str_arg = civ_leader_name(human_civ);
      text_set_string_arg(1,str_arg);
      str_arg = civ_name_plural(human_civ);
      text_set_string_arg(2,str_arg);
      text_clear();
      text_append_year((int)game.year);
      text_set_string_arg(3,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      text_set_label_arg(4,difficulty_names[game.difficulty]);
      if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
        cheat_checked = 0;
      }
      else {
        cheat_checked = 1;
      }
      menu_set_item_checked((GameMenu *)&main_menu,0x701,cheat_checked);
      if ((is_scenario == 0) && (game.multiplayer == '\0')) {
        popup_game(ADDR(0x62bbe0, ((u8 *)&g.d_0062bbe0)));
      }
      net_host_flag = 1;
      for (unit = 0; unit < game.num_units; unit++) {
        if (units[unit].id == 0) {
          units[unit].next_in_stack = -1;
          units[unit].prev_in_stack = -1;
        }
        else {
          unit_stack_validate(unit);
          if ((units[unit].x < 0) || (units[unit].y < 0)) {
            dbg_logf3(ADDR(0x62bbe8, ((u8 *)&g.d_0062bbe8)),unit,(uint)units[unit].type,(int)units[unit].owner)
            ;
            unit_delete(unit,0);
          }
        }
      }
      text_clear();
      text_append((iptr)file_path);
    }
    else {
      switch(load_error) {
      case 1:
        popup_game(ADDR(0x62bb7c, ((u8 *)&g.d_0062bb7c)));
        break;
      case 2:
        popup_game(ADDR(0x62bb88, ((u8 *)&g.d_0062bb88)));
        break;
      case 3:
        text_set_string_arg_b(0,(iptr)(&PTR_s_No_error_00639e60)[crt_errno]);
        popup_game(ADDR(0x62bb94, ((u8 *)&g.d_0062bb94)));
        break;
      case 4:
        text_set_string_arg_b(0,(iptr)(&PTR_s_No_error_00639e60)[crt_errno]);
        popup_game(ADDR(0x62bba0, ((u8 *)&g.d_0062bba0)));
      }
    }
  }
  result = failed;
  if (failed != 0) {
    loaded_file_kind = 0;
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004786f8 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return result;
}
#undef human_civ
#undef loaded_file_kind
#undef net_host_flag
#undef prefs_game_options
#undef scenario_events_loaded
#undef text_buffer
#undef cheat_checked
#undef pick_index
#undef find_data
#undef alt_pattern
#undef alt_count
#undef slash_ptr
#undef unit
#undef file_path
#undef failed
#undef filter_text
#undef filter_text_tail
#undef palette
#undef events_path
#undef str_ptr
#undef view_index
#undef upper_path
#undef load_error
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0048237d auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl turn_popup_timeout_idle(void)

{
  int now;
  
  net_process_messages((NetSession *)&net_session,1,0);
  now = timer_ticks();
  if (0x4b0 < now - dialog_timeout_start_i32) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
    dialog_timeout_start_i32 = timer_ticks();
  }
  return;
}
#undef dialog_stack_top
#undef dialog_timeout_start_i32

/* 0048308f auto */
#define events_pool_base (*(char * *)((u8 *)&g.d_0064b98c))
#define scenario_event_count (*(int *)((u8 *)&g.d_0064b998))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define len_184 (*(int *)(frame_ + FRAME_OFF(4)))
#define len_174 (*(int *)(frame_ + FRAME_OFF(8)))
#define len_148 (*(int *)(frame_ + FRAME_OFF(12)))
#define len_140 (*(int *)(frame_ + FRAME_OFF(16)))
#define len_13c (*(int *)(frame_ + FRAME_OFF(20)))
#define len_dc (*(int *)(frame_ + FRAME_OFF(24)))
#define len_d4 (*(int *)(frame_ + FRAME_OFF(28)))
#define len_cc (*(int *)(frame_ + FRAME_OFF(32)))
#define len_c4 (*(int *)(frame_ + FRAME_OFF(36)))
#define len_90 (*(int *)(frame_ + FRAME_OFF(40)))
#define len_88 (*(int *)(frame_ + FRAME_OFF(44)))
#define len_slot (*(int *)(frame_ + FRAME_OFF(48)))
#define len_20 (*(int *)(frame_ + FRAME_OFF(52)))
#define len_14 (*(int *)(frame_ + FRAME_OFF(56)))
#define len_10 (*(int *)(frame_ + FRAME_OFF(60)))
#define len_08 (*(int *)(frame_ + FRAME_OFF(64)))
#define string_ptr (*(char * *)(frame_ + FRAME_OFF(68)))
#define event (*(char * *)(frame_ + FRAME_OFF(72)))
#define i (*(int *)(frame_ + FRAME_OFF(76)))
void __cdecl events_relink_pool(void)

{
  int event_count;
  size_t str_len;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  event_count = scenario_event_count;
  if (scenario_events_loaded != 0) {
    events_list_head = (iptr)events_pool_base;
    event = events_pool_base;
    string_ptr = events_pool_base + scenario_event_count * 0x1c4;
    if ((string_ptr <= events_pool_base) || (events_pool_base + events_pool_size <= string_ptr)) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62c2c4, ((u8 *)&g.d_0062c2c4)),ADDR(0x62c2a0, ((u8 *)&g.d_0062c2a0)),0x913);
    }
    for (i = 0; i < event_count; i++) {
      event[0x1bc] = '\0';
      event[0x1bd] = '\0';
      event[0x1be] = '\0';
      event[0x1bf] = '\0';
      event[0x1c0] = '\0';
      event[0x1c1] = '\0';
      event[0x1c2] = '\0';
      event[0x1c3] = '\0';
      if (0 < i) {
        *(char **)(event + 0x1c0) = event;
        *(int *)(event + 0x1c0) = *(int *)(event + 0x1c0) - 0x1c4;
        *(char **)(*(int *)(event + 0x1c0) + 0x1bc) = event;
      }
      event += 0x1c4;
    }
    for (event = (char *)events_list_head; event != (char *)0x0;
        event = *(char **)((int)event + 0x1bc)) {
      if (*(int *)((int)event + 8) != 0) {
        *(char **)((int)event + 8) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x10) {
          len_08 = 0xf;
        }
        else {
          str_len = _strlen(string_ptr);
          len_08 = str_len + 1;
        }
        string_ptr += len_08;
      }
      if (*(int *)((int)event + 0x10) != 0) {
        *(char **)((int)event + 0x10) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_10 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_10 = str_len + 1;
        }
        string_ptr += len_10;
      }
      if (*(int *)((int)event + 0x14) != 0) {
        *(char **)((int)event + 0x14) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_14 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_14 = str_len + 1;
        }
        string_ptr += len_14;
      }
      if (*(int *)((int)event + 0x20) != 0) {
        *(char **)((int)event + 0x20) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_20 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_20 = str_len + 1;
        }
        string_ptr += len_20;
      }
      for (i = 0; i < 0x14; i++) {
        if (*(int *)((int)event + 0x38 + i * 4) != 0) {
          *(char **)((int)event + 0x38 + i * 4) = string_ptr;
          str_len = _strlen(string_ptr);
          if (str_len + 1 < 2) {
            len_slot = 1;
          }
          else {
            str_len = _strlen(string_ptr);
            len_slot = str_len + 1;
          }
          string_ptr += len_slot;
        }
      }
      if (*(int *)((int)event + 0x88) != 0) {
        *(char **)((int)event + 0x88) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_88 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_88 = str_len + 1;
        }
        string_ptr += len_88;
      }
      if (*(int *)((int)event + 0x90) != 0) {
        *(char **)((int)event + 0x90) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x10) {
          len_90 = 0xf;
        }
        else {
          str_len = _strlen(string_ptr);
          len_90 = str_len + 1;
        }
        string_ptr += len_90;
      }
      if (*(int *)((int)event + 0xc4) != 0) {
        *(char **)((int)event + 0xc4) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_c4 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_c4 = str_len + 1;
        }
        string_ptr += len_c4;
      }
      if (*(int *)((int)event + 0xcc) != 0) {
        *(char **)((int)event + 0xcc) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_cc = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_cc = str_len + 1;
        }
        string_ptr += len_cc;
      }
      if (*(int *)((int)event + 0xd4) != 0) {
        *(char **)((int)event + 0xd4) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_d4 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_d4 = str_len + 1;
        }
        string_ptr += len_d4;
      }
      if (*(int *)((int)event + 0xdc) != 0) {
        *(char **)((int)event + 0xdc) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x10) {
          len_dc = 0xf;
        }
        else {
          str_len = _strlen(string_ptr);
          len_dc = str_len + 1;
        }
        string_ptr += len_dc;
      }
      if (*(int *)((int)event + 0x13c) != 0) {
        *(char **)((int)event + 0x13c) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_13c = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_13c = str_len + 1;
        }
        string_ptr += len_13c;
      }
      if (*(int *)((int)event + 0x140) != 0) {
        *(char **)((int)event + 0x140) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_140 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_140 = str_len + 1;
        }
        string_ptr += len_140;
      }
      if (*(int *)((int)event + 0x148) != 0) {
        *(char **)((int)event + 0x148) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x10) {
          len_148 = 0xf;
        }
        else {
          str_len = _strlen(string_ptr);
          len_148 = str_len + 1;
        }
        string_ptr += len_148;
      }
      if (*(int *)((int)event + 0x174) != 0) {
        *(char **)((int)event + 0x174) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 0x19) {
          len_174 = 0x18;
        }
        else {
          str_len = _strlen(string_ptr);
          len_174 = str_len + 1;
        }
        string_ptr += len_174;
      }
      if (*(int *)((int)event + 0x184) != 0) {
        *(char **)((int)event + 0x184) = string_ptr;
        str_len = _strlen(string_ptr);
        if (str_len + 1 < 2) {
          len_184 = 1;
        }
        else {
          str_len = _strlen(string_ptr);
          len_184 = str_len + 1;
        }
        string_ptr += len_184;
      }
    }
  }
  return;
}
#undef events_pool_base
#undef scenario_event_count
#undef scenario_events_loaded
#undef len_184
#undef len_174
#undef len_148
#undef len_140
#undef len_13c
#undef len_dc
#undef len_d4
#undef len_cc
#undef len_c4
#undef len_90
#undef len_88
#undef len_slot
#undef len_20
#undef len_14
#undef len_10
#undef len_08
#undef string_ptr
#undef event
#undef i

/* 00484cc0 auto */
#define scenario_flags (*(i16 *)((u8 *)&g.d_0064bc60))
#define scenario_max_turns (*(i16 *)((u8 *)&g.d_0064bcb8))
#define scenario_name (*(i8 *)((u8 *)&g.d_0064bc62))
#define scenario_objective_civ (*(i16 *)((u8 *)&g.d_0064bcba))
#define scenario_start_year (*(i16 *)((u8 *)&g.d_0064bcb6))
#define scenario_tech_paradigm (*(i16 *)((u8 *)&g.d_0064bcb2))
#define scenario_victory_thresholds (*(i16 *)((u8 *)&g.d_0064bcbc))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl scenario_reset_params(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  scenario_flags = 0;
  scenario_name = 0;
  scenario_tech_paradigm = 10;
  scenario_year_increment = 0;
  scenario_start_year = 0;
  scenario_max_turns = 0;
  scenario_objective_civ = 0;
  for (i = 0; i < 4; i++) {
    (&scenario_victory_thresholds)[i] = 0;
  }
  return;
}
#undef scenario_flags
#undef scenario_max_turns
#undef scenario_name
#undef scenario_objective_civ
#undef scenario_start_year
#undef scenario_tech_paradigm
#undef scenario_victory_thresholds
#undef scenario_year_increment
#undef i

/* 00484d85 auto */
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define player_has_quit (*(i8 *)((u8 *)&g.d_006ad685))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define saved_human_players2 (*(u8 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl main_frame_on_close(void)

{
  int confirmed;
  iptr name_str;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((game.multiplayer < 3) || (net_host_handoff_stage == '\0')) &&
     (confirmed = popup_game_with_sprite(ADDR(0x62c5c4, ((u8 *)&g.d_0062c5c4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0), confirmed != 0)) {
    if (game.multiplayer == '\0') {
      snd_cd_stop();
      map_display_disable();
    }
    else {
      if (game.multiplayer == 1) {
        saved_human_players2 = game.human_players;
        game.human_players = hotseat_human_players;
      }
      if (2 < game.multiplayer) {
        if (mp_turn_timer_handle != 0) {
          game_timer_destroy(mp_turn_timer_handle);
          mp_turn_timer_handle = 0;
        }
        parley_wnd_close();
        chat_wnd_close();
        name_str = civ_get_adjective(human_civ);
        text_set_string_arg(0,name_str);
        name_str = civ_leader_title(human_civ);
        text_set_string_arg(1,name_str);
        name_str = civ_leader_name(human_civ);
        text_set_string_arg(2,name_str);
        name_str = civ_name_plural(human_civ);
        text_set_string_arg(3,name_str);
        if (mp_kill_civ_on_retire == 0) {
          net_send_text_args(1,0xff,4,0,0,0);
        }
        else {
          net_send_text_args(0,0xff,4,0,0,0);
        }
      }
      unit_blink_phase = 0;
      mapviews_redraw_cursor();
      if ((~(1 << ((byte)human_civ & 0x1f)) & (uint)game.human_players) == 0) {
        if (game.multiplayer < 3) {
          game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
        }
        else {
          net_send_message(0x31,0,0,human_civ,0,0,0,0,0,0);
        }
        map_display_disable();
        snd_cd_stop();
      }
      else {
        civ_eliminate(human_civ,0,0);
        if (2 < game.multiplayer) {
          map_display_disable();
        }
      }
      player_turn_active = 0;
      player_has_quit = 1;
      if (game.multiplayer == 1) {
        hotseat_human_players = game.human_players;
        game.human_players = saved_human_players2;
      }
    }
  }
  return 0;
}
#undef hotseat_human_players
#undef human_civ
#undef mp_kill_civ_on_retire
#undef net_host_handoff_stage
#undef player_has_quit
#undef player_turn_active
#undef unit_blink_phase
#undef saved_human_players2

/* 00484fec auto */
#define scenario_start_year (*(short *)((u8 *)&g.d_0064bcb6))
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define abs_increment (*(int *)(frame_ + FRAME_OFF(4)))
#define extra_turns (*(int *)(frame_ + FRAME_OFF(8)))
#define period (*(int *)(frame_ + FRAME_OFF(12)))
#define year2 (*(int *)(frame_ + FRAME_OFF(16)))
#define level (*(uint *)(frame_ + FRAME_OFF(20)))
int __cdecl game_turn_to_year(int turn)

{
  int table_index;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  extra_turns = 0;
  level = (uint)game.difficulty;
  if ((game.game_flags & 4) != 0) {
    level--;
  }
  if ((game.game_flags & 8) != 0) {
    level++;
  }
  table_index = int_clamp(level - 1,0,3);
  if (-1 < game.first_launch_turn) {
    extra_turns = turn - game.first_launch_turn;
    if (extra_turns < 1) {
      extra_turns = 0;
    }
    turn -= extra_turns;
  }
  if ((((game.game_flags & 0x80) == 0) || (scenario_year_increment == 0)) || (scenario_start_year == 0)) {
    if (turn != 0) {
      turn--;
    }
    for (period = 0;
        (*(int *)(&year_table_turn_counts + period * 0xc + table_index * 0x48) < turn && (period < 6));
        period = period + 1) {
      turn -= *(int *)(&year_table_turn_counts + period * 0xc + table_index * 0x48);
    }
    if (period < 6) {
      year2 = *(int *)(&year_table_year_steps + period * 0xc + table_index * 0x48) * turn +
                 *(int *)(&year_table_start_years + period * 0xc + table_index * 0x48);
    }
    else {
      year2 = *(int *)(&year_table_last_year_step + table_index * 0x48) * *(int *)(&year_table_last_turn_count + table_index * 0x48) +
                 *(int *)(&year_table_last_start_year + table_index * 0x48) + turn;
    }
    if (year2 == 0) {
      year2 = 1;
    }
  }
  else {
    if (scenario_year_increment < 1) {
      abs_increment = ~(int)scenario_year_increment + 1;
    }
    else {
      abs_increment = (int)scenario_year_increment;
    }
    year2 = (int)scenario_start_year + turn * abs_increment - 1;
  }
  return year2 + extra_turns;
}
#undef scenario_start_year
#undef scenario_year_increment
#undef abs_increment
#undef extra_turns
#undef period
#undef year2
#undef level

/* 00485c15 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define bonus_roll (*(int *)(frame_ + FRAME_OFF(4)))
#define surge_roll (*(int *)(frame_ + FRAME_OFF(8)))
#define rand_y (*(int *)(frame_ + FRAME_OFF(12)))
#define tries (*(int *)(frame_ + FRAME_OFF(16)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define escort_type (*(iptr *)(frame_ + FRAME_OFF(24)))
#define horde_count (*(int *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(32)))
#define alt_type (*(iptr *)(frame_ + FRAME_OFF(36)))
#define attempts (*(int *)(frame_ + FRAME_OFF(40)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(48)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(52)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(56)))
#define main_type (*(iptr *)(frame_ + FRAME_OFF(60)))
#define unit3 (*(int *)(frame_ + FRAME_OFF(64)))
#define remaining (*(uint *)(frame_ + FRAME_OFF(68)))
#define freq_mask (*(uint *)(frame_ + FRAME_OFF(72)))
void __cdecl game_spawn_barbarians(void)

{
  short y;
  iptr rand_x;
  iptr is_ocean;
  int unit;
  int share;
  uint horde_size;
  iptr label;
  uint sign_mask;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game.barbarian_activity != '\0') {
    if (game.difficulty < 5) {
      unit = ((3 - (uint)game.barbarian_activity) * 3 + 0x1e) * (5 - (uint)game.difficulty);
      if (unit - game.turn != 0 && game.turn <= unit) {
        return;
      }
    }
    else if ((int)game.turn < (int)((3 - (uint)game.barbarian_activity) * 3 + 0xf)) {
      return;
    }
    if (game.barbarian_activity == 1) {
      freq_mask = 0xf;
    }
    else if (game.barbarian_activity == 2) {
      freq_mask = 7;
    }
    else if (game.barbarian_activity == 3) {
      freq_mask = 7;
    }
    if (((freq_mask & (int)game.turn + 1U) == 0) &&
       (game.advance_known_by[unit_types[0x16].prerequisite] == '\0')) {
      tries = 0;
      do {
        if (map.width == 1 || map.width - 1 < 0) {
          x2 = 0;
        }
        else {
          rand_x = _rand();
          x2 = rand_x % (int)map.width;
        }
        if (map.height == 7 || map.height - 7 < 0) {
          rand_y = 0;
        }
        else {
          rand_y = _rand();
          rand_y = rand_y % (map.height - 6);
        }
        y2 = rand_y + 3;
        if ((x2 & 1) != 0) {
          x2--;
        }
        if ((y2 & 1) != 0) {
          x2++;
        }
        tries++;
        if (1000 < tries) {
          return;
        }
        is_ocean = tile_is_ocean(x2,y2);
      } while (((is_ocean == 0) || (unit = tile_unit_owner(x2,y2), -1 < unit)) ||
              (unit = tile_landmass(x2,y2),
              *(short *)(&water_body_sizes + unit * 0x10) < 0x10));
      unit = int_clamp((int)game.turn /
                                 (int)((uint)game.barbarian_activity * -0x32 + 0xfa) + 1,1,5);
      horde_count = unit + 1;
      if (game.barbarian_activity == 3) {
        horde_count = unit + 2;
      }
      unit_type2 = 0x20;
      if (game.advance_known_by[0x39] != '\0') {
        unit_type2 = 0x21;
      }
      if (game.advance_known_by[0x2d] != '\0') {
        unit_type2 = 0x23;
      }
      escort_type = 2;
      if ((game.rules & 1) != 0) {
        escort_type = 4;
      }
      if ((game.human_players & game.advance_known_by[0x27]) != 0) {
        escort_type = 5;
      }
      if ((game.advance_known_by[0x33] != '\0') ||
         ((game.barbarian_activity == 3 && (game.advance_known_by[0xb] != '\0')))) {
        if (((x2 & 1) == 0) || ((game.rules & 1) == 0)) {
          escort_type = 0x13;
        }
        else {
          escort_type = 0x12;
        }
      }
      remaining = horde_count;
      if (((game.human_players & game.advance_known_by[0x51]) != 0) && ((game.rules & 1) != 0)) {
        escort_type = 0x14;
      }
      while( true ) {
        remaining--;
        if ((int)remaining < 0) break;
        unit_type = escort_type;
        if ((remaining != 0) && (horde_count - 1 == remaining)) {
          unit_type = 0x2e;
        }
        unit = unit_create(unit_type,0,x2,y2);
        if (-1 < unit) {
          unit_set_sleep(unit);
        }
      }
      unit = unit_create(unit_type2,0,x2,y2);
      unit3 = unit;
      if (unit < 0) {
        unit = tile_first_unit(x2,y2);
        if (-1 < unit) {
          unit_stack_delete_all(unit,1);
        }
      }
      else {
        horde_size = _rand();
        sign_mask = (int)horde_size >> 0x1f;
        if (((horde_size ^ sign_mask) - sign_mask & 1 ^ sign_mask) == sign_mask) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        unit_relocate_in_place(unit3,1);
      }
    }
    if (game.num_cities == 1 || game.num_cities - 1 < 0) {
      city = 0;
    }
    else {
      unit = _rand();
      city = unit % (int)game.num_cities;
    }
    if (((city < game.num_cities) && (cities[city].id != 0)) &&
       (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) {
      unit = _rand();
      share = city_treasury_share(city);
      if (unit % 100 < share) {
        attempts = 0;
        do {
          do {
            unit = _rand();
            x2 = map_wrap_x((int)cities[city].x + (unit % 0xd) * 2 - 6);
            y = cities[city].y;
            unit = _rand();
            y2 = ((int)y + unit % 0xd) - 6;
            if ((x2 & 1) != 0) {
              x2--;
            }
            if ((y2 & 1) != 0) {
              x2++;
            }
            unit = map_in_bounds(x2,y2);
            if ((unit != 0) &&
               (city = city_find_nearest(x2,y2,-1,0xffffffff,-1), city < 0)) {
              attempts = 200;
              goto LAB_004862b4;
            }
            attempts++;
            if ((int)((uint)game.barbarian_activity * 0x32) <= attempts) goto LAB_004862b4;
            unit = map_in_bounds(x2,y2);
          } while (((unit == 0) || (nearest_city_dist < 5)) ||
                  ((unit = tile_zoc_unit_adjacent(x2,y2,0), unit != 0 ||
                   ((unit = tile_is_ocean(x2,y2), unit != 0 ||
                    (unit = tile_unit_owner(x2,y2), -1 < unit))))));
          unit = tile_landmass((int)cities[city].x,(int)cities[city].y);
          share = tile_landmass(x2,y2);
        } while (unit != share);
LAB_004862b4:
        if (attempts < (int)((uint)game.barbarian_activity * 0x32)) {
          if (((game.barbarian_activity == 1) || (game.barbarian_activity == 2)) ||
             (game.barbarian_activity == 3)) {
            freq_mask = (uint)cities[city].size;
          }
          if (freq_mask == 1 || (int)(freq_mask - 1) < 0) {
            horde_count = 0;
          }
          else {
            horde_count = _rand();
            horde_count = horde_count % (int)freq_mask;
          }
          if ((game.barbarian_activity == 3) && (0x95 < game.turn)) {
            if (-(uint)game.difficulty == -9 || (int)(-(uint)game.difficulty + 9) < 0) {
              surge_roll = 0;
            }
            else {
              surge_roll = _rand();
              surge_roll = surge_roll % (int)(10 - (uint)game.difficulty);
            }
            if (surge_roll == 0) {
              if ((int)freq_mask / 2 == 1 || (int)freq_mask / 2 - 1 < 0) {
                bonus_roll = 0;
              }
              else {
                bonus_roll = _rand();
                bonus_roll = bonus_roll % ((int)freq_mask / 2);
              }
              horde_count = horde_count + bonus_roll + (int)freq_mask / 2;
            }
          }
          horde_size = int_clamp(horde_count,2,99);
          main_type = 0x10;
          alt_type = 0xf;
          unit = _rand();
          if (unit % 3 == 0) {
            int_swap((iptr)&main_type,(iptr)&alt_type);
          }
          label = label_string(*(i32 *)(label_string_ids + 0x188));
          text_set_string_arg(0,label);
          if ((10 < (int)horde_size) && ((int)cities[city].size / 2 < (int)horde_size)) {
            label = label_string(*(i32 *)(label_string_ids + 0x18c));
            text_set_string_arg(0,label);
          }
          if (game.advance_known_by[0x23] != '\0') {
            label = label_string(*(i32 *)(label_string_ids + 400));
            text_set_string_arg(0,label);
            if ((game.rules & 1) != 0) {
              main_type = 4;
              alt_type = 0x11;
            }
          }
          if (game.advance_known_by[0x25] != '\0') {
            label = label_string(*(i32 *)(label_string_ids + 0x194));
            text_set_string_arg(0,label);
            main_type = 0x18;
            alt_type = 7;
            if (game.advance_known_by[unit_types[0x16].prerequisite] != '\0') {
              label = label_string(*(i32 *)(label_string_ids + 0x198));
              text_set_string_arg(0,label);
              alt_type = 0xb;
              if (((game.rules & 1) != 0) && (main_type = 0x19, game.advance_known_by[0x22] != '\0'))
              {
                if ((civs[game.best_human_rank].government < 5) ||
                   (cities[city].owner != cities[city].founder)) {
                  main_type = 0x15;
                  alt_type = 9;
                }
                else {
                  alt_type = 8;
                  label = label_string(*(i32 *)(label_string_ids + 0x19c));
                  text_set_string_arg(0,label);
                }
              }
            }
          }
          unit2 = -1;
          for (remaining = horde_size; -1 < (int)remaining; remaining--) {
            if ((remaining & 4) == 0) {
              unit_type = alt_type;
            }
            else {
              unit_type = main_type;
            }
            if (remaining == horde_size) {
              unit_type = 0x2e;
            }
            unit2 = unit_create(unit_type,0,x2,y2);
            if (-1 < unit2) {
              if (unit_type == 8) {
                units[unit2].flags = units[unit2].flags | 0x2000;
              }
              unit = tile_at(x2,y2);
              units[unit2].visibility = *(byte *)(unit + 4) | units[unit2].visibility;
            }
          }
          if ((-1 < unit2) && (autoplay_active == 0)) {
            text_set_string_arg(1,(iptr)&cities[city].name);
            if ((cities[city].owner == human_civ) &&
               (unit = tile_visible_to(x2,y2,human_civ), unit != 0)) {
              dlg_game_txt_with_unit(ADDR(0x62c5d0, ((u8 *)&g.d_0062c5d0)),unit2);
            }
            else if ((((cities[city].owner != human_civ) && (2 < game.multiplayer)) &&
                     (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) &&
                    (unit = tile_visible_to(x2,y2,(int)cities[city].owner),
                    unit != 0)) {
              net_send_message(0x72,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + cities[city].owner * 4) * 0x54),
                                 x2,y2,0,0,0,0,0,0);
              net_send_text_args(2,*(i32 *)
                                    (&net_player_slots +
                                    *(int *)(&net_civ_slots + cities[city].owner * 4) * 0x54),2,0
                                 ,unit2,0);
            }
          }
          if (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0) {
            map_redraw_tile_all_views(x2,y2);
          }
        }
      }
    }
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef bonus_roll
#undef surge_roll
#undef rand_y
#undef tries
#undef unit2
#undef escort_type
#undef horde_count
#undef city
#undef alt_type
#undef attempts
#undef unit_type2
#undef unit_type
#undef y2
#undef x2
#undef main_type
#undef unit3
#undef remaining
#undef freq_mask

/* 00486c2e auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define transit_count (*(int *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define pollution (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl game_update_global_warming(void)

{
  i8 old_warmings;
  int delta;
  int has_transit;
  i32 clamped;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  delta = bits_count8((uint)game.human_players);
  pollution = ((int)game.polluted_tiles - (int)game.warming_pollution) + (int)game.warming_pollution / 2;
  transit_count = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (has_transit = city_has_improvement(city,0x1d), has_transit != 0)) {
      transit_count++;
    }
  }
  if (1 < delta) {
    pollution = (delta - 1 + pollution) / delta;
  }
  delta = (pollution * 2 + game.global_warmings * -4) - transit_count;
  if (delta == game.warming_counter || delta - game.warming_counter < 0) {
    if (((pollution * 2 + game.global_warmings * -4) - transit_count) - (int)game.warming_counter < 0) {
      game.warming_counter--;
    }
  }
  else {
    game.warming_counter++;
  }
  clamped = int_clamp((int)game.warming_counter,0,99);
  game.warming_counter = (i8)clamped;
  if (((game.warming_counter == 12) && (6 < pollution)) && (autoplay_active == 0)) {
    if (2 < game.multiplayer) {
      net_send_text_args(4,0xff,0,0,0,0);
    }
    popup_game_with_sprite(ADDR(0x62c5ec, ((u8 *)&g.d_0062c5ec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  old_warmings = game.global_warmings;
  if (16 < game.warming_counter) {
    game.global_warmings++;
    map_apply_global_warming((int)old_warmings);
    game.warming_counter = '\0';
  }
  game.warming_pollution = 0;
  return;
}
#undef autoplay_active
#undef transit_count
#undef city
#undef pollution

/* 00487371 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define spaceship_winner_civ (*(iptr *)((u8 *)&g.d_0062c5b4))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define other_civ (*(int *)(frame_ + FRAME_OFF(8)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(20)))
#define view_index (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl game_advance_turn(iptr civ)

{
  i32 value;
  uint level;
  int result;
  iptr adjective;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game.turn != 0) {
    game_spawn_barbarians();
    game_update_global_warming();
    civ_update_power_ranks();
    if (game.multiplayer == '\0') {
      civ_check_throne_room_upgrade();
    }
  }
  game.turn++;
  value = game_turn_to_year((int)game.turn);
  game.year = (i16)value;
  if (199 < game.turn) {
    game.peace_turns++;
  }
  game.transient_flags = game.transient_flags & 0xfffe;
  units_reset_for_turn(civ);
  level = (uint)game.difficulty;
  if ((int)game.turn % (int)((level + 1) * 0xc) == 0) {
    for (civ2 = 0; civ2 < 8; civ2++) {
      if (((((int)game.turn % (int)((level + 1) * 0x18) == 0) ||
           (result = civ_has_wonder(civ2,0x14), result != 0)) &&
          ((1 < civs[civ2].reputation || (result = civ_has_wonder(civ2,0x14), result != 0)
           ))) && (civs[civ2].reputation != '\0')) {
        civs[civ2].reputation += 0xff;
        if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
          for (civ3 = 0; civ3 < 8; civ3++) {
            value = int_clamp((int)civs[civ3].reputation_credit[civ2],0,
                                       (uint)civs[civ2].reputation);
            civs[civ3].reputation_credit[civ2] = (char)value;
          }
        }
      }
    }
  }
  if (game.next_history_turn < game.turn) {
    result = _rand();
    game.next_history_turn = game.turn + (short)(result % 0x28) + 0x14;
    if (autoplay_active == 0) {
      if (2 < game.multiplayer) {
        net_send_text_args(5,0xff,0,0,0,0);
      }
      if (game.multiplayer == 1) {
        city_window_close();
        wnd_hide((WndBase *)&status_window_wnd);
        wnd_hide((WndBase *)&minimap_wnd);
        for (view_index = 0; view_index < 8; view_index++) {
          if (*(short *)(&map_view_open_flags + view_index * 0x3f0) != 0) {
            wnd_hide((WndBase *)(&map_view_wnds + view_index * 0x3f0));
          }
        }
      }
      historian_report_show();
      if (game.multiplayer == 1) {
        window_show((WindowObjectView *)&status_window);
        window_show((WindowObjectView *)&minimap_window);
        for (view_index = 0; view_index < 8; view_index++) {
          if (*(short *)(&map_view_open_flags + view_index * 0x3f0) != 0) {
            window_show((WindowObjectView *)(&map_views + view_index * 0x3f0));
          }
        }
      }
    }
  }
  civ2 = 1;
  while( true ) {
    if (7 < civ2) {
      return;
    }
    result = civ_spaceship_launched(civ2);
    if (((result != 0) && (result = civ_spaceship_arrived(civ2), result != 0)) &&
       ((civs[civ2].spaceship_flags & 4) == 0)) break;
    civ2++;
  }
  civs[civ2].spaceship_flags = civs[civ2].spaceship_flags | 4;
  if ((game.game_flags & 2) == 0) {
    civs[civ2].spaceship_flags = civs[civ2].spaceship_flags | 0x10;
    spaceship_winner_civ = civ2;
    if (human_civ == civ2) {
      game_over_reason = 1;
    }
    else {
      game_over_reason = 2;
    }
    if (2 < game.multiplayer) {
      adjective = civ_get_adjective(civ2);
      text_set_string_arg(0,adjective);
      if ((human_civ == civ2) ||
         ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) {
        net_send_text_args(6,0xff,1,0,0,0);
        net_send_message(0x6b,0xff,(uint)game.game_flags,2,spaceship_winner_civ,0,0,0,0,0);
      }
      else {
        net_send_message(0x6b,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                           (uint)game.game_flags,1,spaceship_winner_civ,0,0,0,0,0);
        for (other_civ = 1; other_civ < 8; other_civ++) {
          if ((((1 << ((byte)other_civ & 0x1f) &
                (uint)(game.civs_alive & game.human_players) & 1 << ((byte)other_civ & 0x1f)) != 0)
              && (human_civ != other_civ)) && (other_civ != civ2)) {
            net_send_text_args(6,*(i32 *)
                                  (&net_player_slots + *(int *)(&net_civ_slots + other_civ * 4) * 0x54),1,
                               0,0,0);
            net_send_message(0x6b,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + other_civ * 4) * 0x54)
                               ,(uint)game.game_flags,2,spaceship_winner_civ,0,0,0,0,0);
          }
        }
      }
    }
  }
  if ((autoplay_active == 0) && ((human_civ != civ2 || (game_over_reason == 0)))) {
    adjective = civ_get_adjective(civ2);
    text_set_string_arg(0,adjective);
    if ((2 < game.multiplayer) && (game_over_reason == 0)) {
      net_send_text_args(6,0xff,1,0,0,0);
    }
    popup_game_with_sprite(ADDR(0x62c5f8, ((u8 *)&g.d_0062c5f8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  game.game_flags = game.game_flags | 2;
  return;
}
#undef autoplay_active
#undef game_over_reason
#undef human_civ
#undef spaceship_winner_civ
#undef civ2
#undef other_civ
#undef civ3
#undef view_index

/* 00488937 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_buffer_plus2 (*(i8 *)((u8 *)&g.d_00679642))
#define backup_path (*(i8 (*)[80])(frame_ + FRAME_OFF(4)))
void __cdecl game_autosave(iptr civ)

{
  iptr leader_name;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (human_civ == civ) {
    save_set_file_ext(0);
    text_clear();
    leader_name = civ_leader_name(civ);
    text_append(leader_name);
    text_buffer_plus2 = 0;
    str_trim(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_append(ADDR(0x62c608, ((u8 *)&g.d_0062c608)));
    text_append_label(0x5c);
    crt_strcpy(backup_path,&text_buffer);
    str_append((iptr)backup_path,ADDR(0x62c60c, ((u8 *)&g.d_0062c60c)));
    text_append(ADDR(0x62c610, ((u8 *)&g.d_0062c610)));
    text_append(ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
    str_append((iptr)backup_path,ADDR(0x62c614, ((u8 *)&g.d_0062c614)));
    str_append((iptr)backup_path,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
    if ((game.turn & 4U) == 0) {
      crt_remove(backup_path);
      crt_rename(&text_buffer,backup_path);
    }
    save_write_game(ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
  }
  return;
}
#undef human_civ
#undef text_buffer
#undef text_buffer_plus2
#undef backup_path

/* 00489be2 auto */
#define tutorial_hint_shown_this_turn (*(int *)((u8 *)&g.d_0062c5c0))
#define dir (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl tutorial_settler_hints(iptr unit)

{
  u8 food_yield;
  u8 shield_yield;
  char dy;
  bool good_site;
  byte terrain_id;
  int x;
  int y;
  iptr civ;
  int city;
  iptr x2;
  int value;
  uint improvements2;
  byte *tile;
  uptr terrain;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (tutorial_hint_shown_this_turn == 0) {
    x = (int)units[unit].x;
    y = (int)units[unit].y;
    civ = (iptr)units[unit].owner;
    terrain_id = tile_terrain(x,y);
    terrain = (uptr)terrain_id;
    food_yield = terrain_types[terrain].food;
    shield_yield = terrain_types[terrain].shields;
    city = tile_owner_or_fertility(x,y);
    good_site = 9 < city && 1 < (int)(char)food_yield + (int)(char)shield_yield;
    for (dir = 0; dir < 8; dir++) {
      x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x);
      dy = (&dir_dy_table)[dir];
      value = map_in_bounds(x2,dy + y);
      if ((value != 0) && (value = tile_owner_or_fertility(x2,dy + y), city < value)) {
        good_site = false;
      }
    }
    if (good_site) {
      mapview_center_if_moved(x,y);
      popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c628, ((u8 *)&g.d_0062c628)),unit);
      tutorial_hint_shown_this_turn = 1;
    }
    else if (((int)game.turn - (int)civs[civ].last_city_turn < 0x19) ||
            (5 < civs[civ].num_cities)) {
      city = city_find_nearest(x,y,civ,0xffffffff,-1);
      if ((nearest_city_dist == 1) ||
         ((nearest_city_dist == 2 && (value = tile_resource(x,y), value != 0)))) {
        text_set_string_arg(0,(iptr)&cities[city].name);
        improvements2 = tile_improvements(x,y);
        if ((terrain == 4) && ((improvements2 & 0xc) == 0)) {
          mapview_center_if_moved(x,y);
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c63c, ((u8 *)&g.d_0062c63c)),unit);
          tutorial_hint_shown_this_turn = 1;
        }
        if (((terrain == 1) || ((terrain == 2 && (civs[civ].government == 2)))) &&
           (((improvements2 & 0xc) == 0 && (city = tile_has_irrigation_source(x,y), city != 0)))) {
          mapview_center_if_moved(x,y);
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c644, ((u8 *)&g.d_0062c644)),unit);
          tutorial_hint_shown_this_turn = 1;
        }
        else if (((((uint)civs[civ].units_active[0] + (uint)civs[civ].units_active[1] < 2) &&
                  ((improvements2 & 0x10) == 0)) && (terrain_types[terrain].move_cost == 1)) &&
                (tile = (byte *)tile_at(x,y), (*tile & 0x80) == 0)) {
          mapview_center_if_moved(x,y);
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c650, ((u8 *)&g.d_0062c650)),unit);
          tutorial_hint_shown_this_turn = 1;
        }
      }
    }
    else {
      popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c634, ((u8 *)&g.d_0062c634)),unit);
      civs[civ].last_city_turn = game.turn;
      tutorial_hint_shown_this_turn = 1;
    }
  }
  return;
}
#undef tutorial_hint_shown_this_turn
#undef dir

/* 0048a004 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define spin_count (*(int *)(frame_ + FRAME_OFF(4)))
#define waited (*(i32 *)(frame_ + FRAME_OFF(12)))
i32 __cdecl game_run_active_unit(void)

{
  bool resumed_move;
  bool had_unit;
  i16 start_unit_count;
  iptr unit;
  iptr selectable;
  int unit2;
  int result;
  bool show_hint;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  start_unit_count = game.num_units;
  waited = 0;
  had_unit = false;
  resumed_move = false;
  unit_blink_active = 1;
  unit = (iptr)game.active_unit;
  if (((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (((int)(short)units[unit].flags & 0x8000U) == 0)) &&
     (units[unit].orders == -1)) {
    if ((unit_types[units[unit].type].role == 5) &&
       (selectable = unit_is_selectable(unit), selectable != 0)) {
      tutorial_settler_hints((int)game.active_unit);
    }
    else if ((unit_types[units[unit].type].attack != '\0') && (4 < units[unit].damage)) {
      show_hint = false;
      unit2 = unit_max_hp(unit);
      if ((int)(uint)units[unit].damage < unit2 / 3) {
        if ((game.shown_event_flags & 0x80) == 0) {
          game.shown_event_flags = game.shown_event_flags | 0x80;
          show_hint = true;
        }
      }
      else {
        show_hint = (game.shown_event_flags & 0x40) == 0;
        if (show_hint) {
          game.shown_event_flags = game.shown_event_flags | 0xc0;
        }
      }
      if ((show_hint) && (autoplay_active == 0)) {
        popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c658, ((u8 *)&g.d_0062c658)),unit);
      }
    }
  }
  unit2 = (int)game.active_unit;
  spin_count = 0;
  while (((result = unit_is_selectable((int)game.active_unit), result != 0 &&
          ((((unit_blink_active != '\0' || (unit_move_unanimated_state == 2)) && (player_turn_active != '\0')) &&
           ((game_loop_active != '\0' && (game.num_units == start_unit_count)))))) &&
         ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) != 0))) {
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (unit_move_unanimated_state == 2) {
      unit_blink_active = 1;
      unit_move_unanimated_state = '\0';
      resumed_move = true;
    }
    if ((resumed_move) && (units[game.active_unit].orders != 11)) {
      unit_blink_active = '\0';
      resumed_move = false;
    }
    had_unit = true;
    snd_sync_music_option();
    if (((int)(short)units[unit2].flags & 0x8000U) == 0) {
      result = unit_execute_orders(unit2);
      if (result == 0) {
        waited = 1;
        win_pump_one_message();
      }
    }
    else {
      unit_continue_active_orders();
      spin_count++;
      if (0x14 < spin_count) {
        unit_exhaust_moves(unit2);
      }
    }
  }
  mapviews_redraw_cursor();
  unit_blink_active = 0;
  if (!had_unit) {
    game.active_unit = -1;
  }
  return waited;
}
#undef autoplay_active
#undef game_loop_active
#undef human_civ
#undef player_turn_active
#undef unit_blink_active
#undef spin_count
#undef waited

/* 0048a374 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
void __cdecl game_wait_for_player_input(void)

{
  i16 start_unit_count;
  
  start_unit_count = game.num_units;
  unit_blink_active = 1;
  while ((((unit_blink_active != '\0' && (player_turn_active != '\0')) && (game_loop_active != '\0')) &&
         ((moving_units_mode == 0 && (game.num_units == start_unit_count))))) {
    snd_sync_music_option();
    win_pump_one_message();
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  unit_blink_active = 0;
  return;
}
#undef game_loop_active
#undef moving_units_mode
#undef player_turn_active
#undef unit_blink_active

/* 0048a416 auto */
#define city_window_closed (*(int *)((u8 *)&g.d_006aa75c))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define tutorial_hint_shown_this_turn (*(i32 *)((u8 *)&g.d_0062c5c0))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
#define unit_focus_done (*(char *)((u8 *)&g.d_00673b04))
#define slot (*(int *)(frame_ + FRAME_OFF(0)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define waited (*(uint *)(frame_ + FRAME_OFF(12)))
void __cdecl game_player_move_loop(void)

{
  short last_unit_count;
  iptr selectable;
  uint run_result;
  int unit;
  iptr city;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  waited = 0;
  last_unit_count = -1;
  game.active_unit = -1;
  ui_focus_active_unit(0);
  player_turn_active = 1;
  tutorial_hint_shown_this_turn = 0;
  if ((2 < game.multiplayer) && (net_host_flag == '\0')) {
    for (slot = 0; slot < 8; slot++) {
      if (((*(int *)(&net_meet_pending_flags + slot * 4) != 0) &&
          (*(i32 *)(&net_meet_pending_flags + slot * 4) = 0,
          ((uint)game.civs_alive & 1 << ((&net_meet_pending_flags)[slot * 4] & 0x1f)) != 0)) &&
         (((uint)game.human_players & 1 << ((&net_meet_pending_flags)[slot * 4] & 0x1f)) == 0)) {
        diplo_ai_meet_player(*(iptr *)(&net_meet_pending_ai_civ + slot * 4),
                           *(iptr *)(&net_meet_pending_civ + slot * 4),
                           *(i32 *)(&net_meet_pending_x + slot * 4),
                           *(i32 *)(&net_meet_pending_y + slot * 4),0);
      }
    }
  }
  do {
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (moving_units_mode == 1) {
      unit_is_selectable((int)game.active_unit);
      if (((game.active_unit < 0) || (game.num_units <= game.active_unit)) ||
         ((units[game.active_unit].id == 0 ||
          ((selectable = unit_is_selectable((int)game.active_unit), selectable == 0 ||
           (game.num_units != last_unit_count)))))) {
        unit_activate_next(0);
      }
      else if (unit_focus_done == '\0') {
        unit = (int)game.active_unit;
        map_cursor_x = units[unit].x;
        map_cursor_y = units[unit].y;
        if ((unit_move_unanimated_state == '\0') || (units[unit].orders != 11)) {
          status_redraw(1);
          mapviews_ensure_visible((int)units[unit].x,(int)units[unit].y,(int)units[unit].owner);
          menu_update_states();
        }
      }
    }
    if ((((2 < game.multiplayer) && (mp_turn_time_limit_ms != 0)) && (mp_turn_timer_handle == 0)) &&
       (0 < mp_turn_seconds_left)) {
      dbg_log(ADDR(0x62c660, ((u8 *)&g.d_0062c660)));
      mp_turn_timer_resume(0);
    }
    last_unit_count = game.num_units;
    unit_move_unanimated_state = '\0';
    unit_focus_done = '\0';
    if (game.active_unit < 0) {
      game.transient_flags = game.transient_flags | 1;
      if (moving_units_mode == 1) {
        snd_play_effect(100,1,0,0);
      }
      ui_redraw_all_maps(1);
      if (((waited == 0) || (((*(i8 *)((char *)&game.game_options + 1)) & 0x40) != 0)) || ((game.transient_flags & 2) != 0))
      goto LAB_0048a77d;
      player_turn_active = '\0';
    }
    else {
LAB_0048a77d:
      unit_blink_active = 1;
      if (game.active_unit < 0) {
        game.transient_flags = game.transient_flags & 0xfffd;
        game_wait_for_player_input();
      }
      else {
        game.transient_flags = game.transient_flags & 0xfffc;
        run_result = game_run_active_unit();
        waited = waited | run_result;
      }
      unit = citywnd_get_city((WindowObjectView *)&city_window);
      if (unit == -1) {
        game.transient_flags = game.transient_flags & 0xfffd;
      }
      if (game_loop_active == '\0') {
        return;
      }
      if ((game.transient_flags & 2) != 0) {
        waited = 0;
      }
      if (unit_blink_phase != '\0') {
        mapviews_redraw_cursor();
      }
      unit_blink_active = 0;
    }
    if (((game_loop_active == '\0') || (player_turn_active == '\0')) ||
       ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0)) {
      if ((city_window_closed == 0) &&
         (city = citywnd_get_city((WindowObjectView *)&city_window),
         cities[city].owner != human_civ)) {
        city_window_close();
      }
      input_flush_events();
      player_turn_active = 0;
      if (game.multiplayer != '\0') {
        for (unit2 = 0; unit2 < game.num_units; unit2++) {
          if ((units[unit2].id != 0) && (units[unit2].owner == game.turn_civ)) {
            unit_exhaust_moves(unit2);
          }
        }
      }
      return;
    }
  } while( true );
}
#undef city_window_closed
#undef game_loop_active
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef mp_turn_seconds_left
#undef mp_turn_time_limit_ms
#undef net_host_flag
#undef player_turn_active
#undef tutorial_hint_shown_this_turn
#undef unit_blink_active
#undef unit_blink_phase
#undef unit_focus_done
#undef slot
#undef unit2
#undef waited

/* 0048a92d auto */
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define group (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl game_calc_human_wonder_range(void)

{
  byte count;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (group = 0; group < 4; group++) {
    (&human_wonders_by_group_max)[group] = 0;
    (&human_wonders_by_group_min)[group] = 99;
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        count = civs[civ].wonders_by_group[group];
        if (count <= (byte)(&human_wonders_by_group_max)[group]) {
          count = (&human_wonders_by_group_max)[group];
        }
        (&human_wonders_by_group_max)[group] = count;
        count = civs[civ].wonders_by_group[group];
        if ((byte)(&human_wonders_by_group_min)[group] <= count) {
          count = (&human_wonders_by_group_min)[group];
        }
        (&human_wonders_by_group_min)[group] = count;
      }
    }
  }
  return;
}
#undef civ
#undef group

/* 0048aa24: written by hand in src/game/retvals.c */

/* 0048aedc auto */
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_max_turns (*(short *)((u8 *)&g.d_0064bcb8))
#define game_ended (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl game_check_retirement(void)

{
  iptr name_str;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  game_ended = 0;
  if (((game.game_flags & 2) == 0) && (game_over_reason == 0)) {
    name_str = civ_leader_title(human_civ);
    text_set_string_arg(0,name_str);
    name_str = civ_leader_name(human_civ);
    text_set_string_arg(1,name_str);
    if (((game.game_flags & 0x80) == 0) || (scenario_max_turns == 0)) {
      if (game.year == 2000) {
        if (2 < game.multiplayer) {
          net_send_text_args(9,0xff,0,0,0,0);
        }
        popup_game_with_sprite(ADDR(0x62c6f8, ((u8 *)&g.d_0062c6f8)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      }
      else if (game.year == 0x7e4) {
        if (2 < game.multiplayer) {
          net_send_text_args(10,0xff,0,0,0,0);
        }
        popup_game_with_sprite(ADDR(0x62c704, ((u8 *)&g.d_0062c704)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
        game.game_flags = game.game_flags | 2;
        game_over_reason = 5;
        if (2 < game.multiplayer) {
          net_send_message(0x6b,0xff,(uint)game.game_flags,5,0,0,0,0,0,0);
        }
        game_ended = 1;
      }
    }
    else if (scenario_max_turns - 5 == (int)game.turn) {
      if (2 < game.multiplayer) {
        net_send_text_args(7,0xff,0,0,0,0);
      }
      popup_game_with_sprite(ADDR(0x62c6dc, ((u8 *)&g.d_0062c6dc)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
    }
    else if (scenario_max_turns == game.turn) {
      if (2 < game.multiplayer) {
        net_send_text_args(8,0xff,0,0,0,0);
      }
      popup_game_with_sprite(ADDR(0x62c6ec, ((u8 *)&g.d_0062c6ec)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      game.game_flags = game.game_flags | 2;
      game_over_reason = 5;
      if (2 < game.multiplayer) {
        net_send_message(0x6b,0xff,(uint)game.game_flags,5,0,0,0,0,0,0);
      }
      game_ended = 1;
    }
  }
  return game_ended;
}
#undef game_over_reason
#undef human_civ
#undef scenario_max_turns
#undef game_ended

/* 0048b165 auto */
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define spaceship_winner_civ (*(int *)((u8 *)&g.d_0062c5b4))
#define quit (*(uint *)(frame_ + FRAME_OFF(0)))
uint __cdecl game_handle_game_over(void)

{
  int choice;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  quit = 0;
  switch(game_over_reason) {
  case 1:
  case 2:
    if ((spaceship_winner_civ == 0) || (human_civ == spaceship_winner_civ)) {
      endgame_spaceship_arrival(human_civ);
    }
    else {
      endgame_spaceship_arrival(-spaceship_winner_civ);
    }
    break;
  case 3:
    destroyed_civs_show(human_civ);
    break;
  case 4:
    endgame_defeat_movie(human_civ);
    break;
  case 5: ;
  }
  powergraph_show();
  if ((game.game_flags & 0x20) == 0) {
    civ_score_window_show(human_civ);
    civ_rating_window_show(human_civ);
    hall_of_fame_add_entry(human_civ);
  }
  if (game.multiplayer == '\0') {
    if ((((game_over_reason == 1) || (game_over_reason == 2)) || (game_over_reason == 4)) ||
       (((game_over_reason == 5 && (game.year == 0x7e4)) || (game_over_reason == 3)))) {
      if (game_over_reason == 4) {
        quit = 1;
      }
      else {
        choice = popup_game_with_sprite(ADDR(0x62c710, ((u8 *)&g.d_0062c710)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        quit = (uint)(choice == 0);
      }
      game.game_flags = game.game_flags | 0x20;
    }
  }
  else {
    quit = 1;
  }
  game_over_reason = 0;
  return quit;
}
#undef game_over_reason
#undef human_civ
#undef spaceship_winner_civ
#undef quit

/* 0048b340 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define map_view_center_x (*(i16 *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(i16 *)((u8 *)&g.d_0066ca8a))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
#define civ (*(uptr *)(frame_ + FRAME_OFF(4)))
#define saved_human_civ (*(byte *)(frame_ + FRAME_OFF(12)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define views_hidden (*(int *)(frame_ + FRAME_OFF(780)))
#define human_count (*(int *)(frame_ + FRAME_OFF(784)))
#define view_index (*(int *)(frame_ + FRAME_OFF(788)))
#define quit (*(int *)(frame_ + FRAME_OFF(792)))
#define casualties (*(int *)(frame_ + FRAME_OFF(796)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(800)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(808)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl game_play_loop(void)

{
  bool pbem_saved;
  bool human_moved;
  int retired;
  iptr name_str;
  iptr prev_human_civ;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  views_hidden = 0;
  pbem_saved = false;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  picwnd_close((PictureWindowCore *)&advisor_window);
  picwnd_close((PictureWindowCore *)&casualty_window);
  menu_update_states();
  if (game.multiplayer == 1) {
    hotseat_human_players = game.human_players;
  }
  while( true ) {
    human_moved = false;
    game_calc_human_wonder_range();
    if (turn_resume_civ == 0) {
      game_advance_turn(0xffffffff);
    }
    retired = game_check_retirement();
    if ((retired != 0) || (game_over_reason != 0)) {
      human_count = bits_count8((uint)game.human_players);
      quit = game_handle_game_over();
      if ((game.multiplayer == 1) &&
         ((~(1 << ((byte)human_civ & 0x1f)) & (uint)game.human_players) != 0)) {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
      }
      if (((quit != 0) && (game.multiplayer == '\0')) ||
         ((quit != 0 && ((game.multiplayer == 1 && (human_count < 2)))))) goto LAB_0048bf12;
      quit = 0;
    }
    if ((game.multiplayer == 1) && (game.human_players == '\0')) break;
    if ((scenario_events_loaded != 0) && ((turn_resume_civ == 0 || (turn_resume_new_game != 0)))) {
      events_check_turn((ScenarioEvents *)&scenario_events,(int)game.turn);
      events_check_turn_interval((ScenarioEvents *)&scenario_events,(int)game.turn);
      events_check_random_turn((ScenarioEvents *)&scenario_events,(int)game.turn);
      events_check_received_tech((ScenarioEvents *)&scenario_events);
    }
    for (civ = 0; (game_loop_active != '\0' && ((int)civ < 8)); civ++) {
      if (((int)(uint)turn_resume_civ <= (int)civ) &&
         ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) {
        game.turn_civ = (byte)civ;
        if (game.multiplayer == 1) {
          hotseat_human_players = game.human_players;
          mp_turn_civ_i32 = civ;
          views_hidden = 1;
          city_window_close();
          wnd_hide((WndBase *)&status_window_wnd);
          wnd_hide((WndBase *)&minimap_wnd);
          for (view_index = 0; view_index < 8; view_index++) {
            if (*(short *)(&map_view_open_flags + view_index * 0x3f0) != 0) {
              wnd_hide((WndBase *)(&map_view_wnds + view_index * 0x3f0))
              ;
            }
          }
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          if (game.multiplayer == 1) {
            dlg_load_game_section(&dialog2,ADDR(0x62c750, ((u8 *)&g.d_0062c750)),0x2000008);
            dlg_show_modal(&dialog2,0);
          }
        }
        else {
          game.player_civ = (byte)civ;
          if (game.multiplayer != '\0') {
            civ_check_password(civ);
          }
          if (game.multiplayer == 1) {
            name_str = civ_leader_name(civ);
            text_set_string_arg(0,name_str);
            name_str = civ_name_plural(civ);
            text_set_string_arg(1,name_str);
            popup_game_with_sprite(ADDR(0x62c72c, ((u8 *)&g.d_0062c72c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            *(i16 *)(&civ_saved_cursor_x + human_civ * 2) = map_cursor_x;
            *(i16 *)(&civ_saved_cursor_y + human_civ * 2) = map_cursor_y;
            if (*(short *)(&civ_intro_shown + civ * 2) == 1) {
              map_cursor_x = *(i16 *)(&civ_saved_cursor_x + civ * 2);
              map_cursor_y = *(i16 *)(&civ_saved_cursor_y + civ * 2);
              map_view_center_x = map_cursor_x;
              mapview_center_y = map_cursor_y;
            }
            else {
              civ_intro_popup(civ);
              for (city = 0; city < game.num_cities; city++) {
                if ((cities[city].id != 0) && ((int)cities[city].owner == civ)) {
                  map_cursor_x = cities[city].x;
                  map_cursor_y = cities[city].y;
                  map_view_center_x = map_cursor_x;
                  mapview_center_y = map_cursor_y;
                  break;
                }
              }
              *(i16 *)(&civ_intro_shown + civ * 2) = 1;
            }
          }
          prev_human_civ = human_civ;
          human_civ = civ;
          if (game.multiplayer == 2) {
            if (pbem_saved) {
              game_save_dialog(0);
              if ((&civ_email_addresses)[civ * 0x20] == '\0') {
                name_str = civ_leader_name(civ);
                text_set_string_arg(0,name_str);
                popup_game(ADDR(0x62c744, ((u8 *)&g.d_0062c744)));
              }
              else {
                name_str = civ_leader_name(civ);
                text_set_string_arg(0,name_str);
                text_set_string_arg(1,(iptr)(&civ_email_addresses + civ * 0x20));
                popup_game(ADDR(0x62c738, ((u8 *)&g.d_0062c738)));
              }
              game_loop_active = '\0';
              goto LAB_0048bf12;
            }
            pbem_saved = true;
          }
          if (((prev_human_civ & 0xffU) != civ) || (turn_resume_civ != 0)) {
            if (mp_turn_time_limit_ms != 0) {
              mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
              main_view_timer_cache_i32 = 0xffffffff;
            }
            mapview_update_title((FrameWindow *)&map_views);
            map_redraw_all_views(human_civ,1);
          }
          status_draw_info(1);
          status_draw_civ_color(civ);
          if (views_hidden != 0) {
            views_hidden = 0;
            window_show((WindowObjectView *)&status_window);
            window_show((WindowObjectView *)&minimap_window);
            for (view_index = 0; view_index < 8; view_index++) {
              if (*(short *)(&map_view_open_flags + view_index * 0x3f0) != 0) {
                window_show((WindowObjectView *)(&map_views + view_index * 0x3f0))
                ;
              }
            }
          }
        }
        status_draw_civ_color(civ);
        if ((game.multiplayer == 1) &&
           ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
          game.human_players = '\0';
          saved_human_civ = (byte)human_civ;
          human_civ = -1;
        }
        if ((turn_resume_civ == 0) || (turn_resume_new_game != 0)) {
          if ((turn_resume_civ != 0) && (turn_resume_new_game != 0)) {
            mapview_update_title((FrameWindow *)&map_views);
            map_redraw_all_views(human_civ,1);
            wnd_flush_paint();
          }
          casualties = *(int *)(&casualty_counts + human_civ * 4) -
                     *(int *)(&casualty_reported_counts + human_civ * 4);
          if (autoplay_active == 0) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            name_str = civ_leader_title(human_civ);
            text_set_string_arg(0,name_str);
            name_str = civ_leader_name(human_civ);
            text_set_string_arg(1,name_str);
            if (0 < casualties) {
              *(i32 *)(&casualty_reported_counts + human_civ * 4) =
                   *(i32 *)(&casualty_counts + human_civ * 4);
              text_set_number_arg(0,casualties);
              if (casualties == 1) {
                dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c760, ((u8 *)&g.d_0062c760)));
              }
              else {
                dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c76c, ((u8 *)&g.d_0062c76c)));
              }
              dialog_add_sprite((DialogOptionList *)&dialog2,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
              input_flush_events();
              snd_play_effect(0x30,0,0,0);
              dlg_show_modal(&dialog2,0);
              if (dialog2.result_extra != 0) {
                casualty_timeline_show(human_civ);
              }
            }
          }
          civ_process_turn(civ);
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
             (ai_process_civ_units(), game.multiplayer == 1)) {
            dialog_close(&dialog2);
            dialog_init_defaults(&dialog2);
            human_civ = (iptr)saved_human_civ;
          }
        }
        else {
          if (game.multiplayer == 1) {
            game.human_players = game.human_players & (byte)(1 << ((byte)civ & 0x1f));
          }
          game_turn_start_popups();
          if ((game.multiplayer == 1) && (mp_turn_time_limit_ms != 0)) {
            mp_turn_timer_start(1);
            game_player_move_loop();
            mp_turn_timer_stop(1);
          }
          else {
            game_player_move_loop();
          }
          human_moved = true;
        }
        if (game.multiplayer == 1) {
          game.human_players = hotseat_human_players;
        }
        saved_turn_civ = 0;
        turn_resume_civ = 0;
        saved_resume_new_game = 0;
        turn_resume_new_game = 0;
        game.transient_flags = game.transient_flags & 0xfffe;
        if (game_loop_active == '\0') goto LAB_0048bf12;
        if (game_over_reason != 0) {
          human_count = bits_count8((uint)game.human_players);
          quit = game_handle_game_over();
          if ((game.multiplayer == 1) &&
             ((~(1 << ((byte)human_civ & 0x1f)) & (uint)game.human_players) != 0)) {
            game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
          }
          if (((quit != 0) && (game.multiplayer == '\0')) ||
             ((quit != 0 && ((game.multiplayer == 1 && (human_count < 2))))))
          goto LAB_0048bf12;
          quit = 0;
        }
      }
    }
    if ((!human_moved) && (game.multiplayer == '\0')) {
      game.turn_civ = (byte)human_civ;
      game_player_move_loop();
      if ((game_over_reason != 0) && (quit = game_handle_game_over(), quit != 0))
      goto LAB_0048bf12;
    }
    game.human_players = game.civs_alive & game.human_players;
    if (game_loop_active == '\0') {
LAB_0048bf12:
      mp_turn_timer_stop(0);
      seh_state = 0xffffffff;
      /* inlined unwind funclet 0048bf2d */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      return;
    }
  }
  popup_game_with_sprite(ADDR(0x62c71c, ((u8 *)&g.d_0062c71c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  goto LAB_0048bf12;
}
#undef autoplay_active
#undef dlg_pending_idle_callback
#undef game_loop_active
#undef game_over_reason
#undef hotseat_human_players
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef map_view_center_x
#undef mapview_center_y
#undef mp_turn_civ
#undef mp_turn_seconds_left
#undef mp_turn_time_limit_ms
#undef saved_resume_new_game
#undef saved_turn_civ
#undef scenario_events_loaded
#undef turn_resume_civ
#undef turn_resume_new_game
#undef main_view_timer_cache_i32
#undef mp_turn_civ_i32
#undef city
#undef civ
#undef saved_human_civ
#undef dialog2
#undef views_hidden
#undef human_count
#undef view_index
#undef quit
#undef casualties
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0048bfec auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(i16 *)((u8 *)&g.d_00654faa))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_local_slot (*(int *)((u8 *)&g.d_006ad304))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define nm_start_civ_count (*(int *)((u8 *)&g.d_006c9038))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
#define saved_human_players (*(u8 *)((u8 *)&g.d_00673b08))
#define saved_resume_new_game (*(short *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define saved_human_players_i32 (*(i32 *)((u8 *)&g.d_00673b08))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define still_playing (*(i8 *)(frame_ + FRAME_OFF(768)))
#define found_unit (*(int *)(frame_ + FRAME_OFF(772)))
#define casualties (*(int *)(frame_ + FRAME_OFF(776)))
#define first_turn (*(i32 *)(frame_ + FRAME_OFF(780)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(784)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(792)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl game_mp_client_turn_loop(void)

{
  byte resume_civ;
  SHORT SVar2;
  iptr name_str;
  int result;
  i32 ret;
  iptr slot_civ;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  first_turn = 1;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  still_playing = 1;
  slot_civ = net_slot_civs;
  name_str = civ_name_plural(net_slot_civs);
  dbg_logf_str_int(ADDR(0x62c778, ((u8 *)&g.d_0062c778)),name_str,slot_civ);
  for (civ = 1; civ < 8; civ++) {
    if (((*(int *)(&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54) != 0) &&
        ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      result = civ;
      name_str = civ_name_plural(civ);
      dbg_logf_str_int(ADDR(0x62c788, ((u8 *)&g.d_0062c788)),name_str,result);
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
  found_unit = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
      mapview_center_on
                ((ViewWindow *)&map_views,(int)units[unit].x,(int)units[unit].y);
      found_unit++;
      break;
    }
  }
  if (found_unit == 0) {
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
  resume_civ = turn_resume_civ;
  if ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0) {
    net_heartbeat_send(net_slot_civs);
    dlg_pending_idle_callback = ((void *)ADDR(0x00401a5a, net_client_hot_wait_idle));
    popup_game_sprite_flags(ADDR(0x62c798, ((u8 *)&g.d_0062c798)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    resume_civ = turn_resume_civ;
  }
LAB_0048c326:
  do {
    turn_resume_civ = resume_civ;
    if ((uint)turn_resume_civ != human_civ) {
      for (unit = 0; unit < game.num_units; unit++) {
        if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
          unit_exhaust_moves(unit);
        }
      }
    }
    net_heartbeat_send(net_slot_civs);
    while ((((nm_start_civ_count == 0 && (net_host_handoff_stage == '\0')) && (nm_end_sequence_count == 0)) &&
           ((player_has_quit == '\0' && (game_loop_active != '\0'))))) {
      net_process_messages((NetSession *)&net_session,1,0);
      net_heartbeat_check(net_slot_civs);
      result = net_check_lost_connections();
      if (result != 0) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 0048c9ce */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        ret = 0;
        goto LAB_0048c9e4;
      }
    }
    if (net_host_handoff_stage != '\0') {
      result = net_client_transfer_server();
      if (result == 0) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 0048c9ce */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        ret = 0;
        goto LAB_0048c9e4;
      }
      if (net_host_flag != '\0') {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 0048c9ce */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        ret = 1;
        goto LAB_0048c9e4;
      }
      if (((nm_start_civ_count == 0) && (nm_end_sequence_count == 0)) &&
         ((player_has_quit == '\0' && (resume_civ = turn_resume_civ, game_loop_active != '\0'))))
      goto LAB_0048c326;
    }
    if ((nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
      nm_start_civ_count = 0;
      human_civ = (&net_slot_civs)[net_local_slot * 0x15];
      game.player_civ = (byte)human_civ;
      game.turn_civ = (byte)human_civ;
      if ((uint)turn_resume_civ != human_civ) {
        units_reset_for_turn(human_civ);
      }
      if (mp_turn_time_limit_ms != 0) {
        mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
        main_view_timer_cache_i32 = 0xffffffff;
      }
      mapview_update_title((FrameWindow *)&map_views);
      map_redraw_all_views(human_civ,1);
      status_draw_info(1);
      status_draw_civ_color(human_civ);
      casualties = *(int *)(&casualty_counts + human_civ * 4) -
                 *(int *)(&casualty_reported_counts + human_civ * 4);
      if (autoplay_active == 0) {
        dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
        name_str = civ_leader_title(human_civ);
        text_set_string_arg(0,name_str);
        name_str = civ_leader_name(human_civ);
        text_set_string_arg(1,name_str);
        if (casualties < 1) {
          dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7c0, ((u8 *)&g.d_0062c7c0)));
          dialog_add_sprite((DialogOptionList *)&dialog2,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
          dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
          input_flush_events();
          snd_play_effect(0x30,0,0,0);
          dlg_show_modal(&dialog2,0);
        }
        else {
          *(i32 *)(&casualty_reported_counts + human_civ * 4) =
               *(i32 *)(&casualty_counts + human_civ * 4);
          text_set_number_arg(0,casualties);
          if (casualties == 1) {
            dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7a8, ((u8 *)&g.d_0062c7a8)));
          }
          else {
            dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7b4, ((u8 *)&g.d_0062c7b4)));
          }
          dialog_add_sprite((DialogOptionList *)&dialog2,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
          dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
          input_flush_events();
          snd_play_effect(0x30,0,0,0);
          dlg_show_modal(&dialog2,0);
          if (dialog2.result_extra != 0) {
            casualty_timeline_show(human_civ);
          }
        }
      }
      if (autoplay_active == 0) {
        if (turn_resume_civ == 0) {
          civ_check_throne_room_upgrade();
        }
        if ((turn_resume_civ == 0) || (turn_resume_new_game != 0)) {
          civ_process_turn(human_civ);
          net_send_state_diff(0xff,2,0,0,0);
        }
        game_turn_start_popups();
        if ((*(short *)(&civ_intro_shown + human_civ * 2) == 0) && (autoplay_active == 0)) {
          civ_intro_popup(human_civ);
          *(i16 *)(&civ_intro_shown + human_civ * 2) = 1;
        }
        if (mp_turn_time_limit_ms != 0) {
          mp_turn_timer_start(1);
        }
        game_player_move_loop();
      }
      else {
        saved_human_players_i32 = (uint)game.human_players;
        game.human_players = '\0';
        if ((turn_resume_civ == 0) || (turn_resume_new_game != 0)) {
          civ_process_turn(human_civ);
        }
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
    }
    else {
      still_playing = 0;
    }
    mp_turn_timer_stop(1);
    status_redraw(1);
    ui_pump_messages();
    if (game_over_reason != 0) {
      game_loop_active = '\0';
    }
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0xa2,0,human_civ,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    saved_turn_civ = 0;
    turn_resume_civ = 0;
    saved_resume_new_game = 0;
    turn_resume_new_game = 0;
    first_turn = 0;
    resume_civ = 0;
    if (game_loop_active == '\0') {
      net_send_message(0x2d,0,human_civ,0,0,0,0,0,0,0);
      XD_FlushSendBuffer(60000);
      net_session_shutdown(&net_session,1);
      if (game_over_reason != 0) {
        game_handle_game_over();
      }
      seh_state = 0xffffffff;
      /* inlined unwind funclet 0048c9ce */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      ret = 0;
LAB_0048c9e4:
      return ret;
    }
  } while( true );
}
#undef autoplay_active
#undef autoplay_turns_left
#undef dlg_pending_idle_callback
#undef game_loop_active
#undef game_over_reason
#undef human_civ
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
#undef civ
#undef unit
#undef dialog2
#undef still_playing
#undef found_unit
#undef casualties
#undef first_turn
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0048c9f3 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(short *)((u8 *)&g.d_00654faa))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define net_claimed_civs_mask (*(i16 *)((u8 *)&g.d_00654fb0))
#define net_local_slot (*(int *)((u8 *)&g.d_006ad304))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define nm_start_civ_count (*(i32 *)((u8 *)&g.d_006c9038))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
#define saved_human_players (*(u8 *)((u8 *)&g.d_00673b08))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define saved_human_players_i32 (*(i32 *)((u8 *)&g.d_00673b08))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define civ (*(uptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(16)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define rect_left2 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define rect_top2 (*(i32 *)(frame_ + FRAME_OFF(780)))
#define rect_right2 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define rect_bottom2 (*(i32 *)(frame_ + FRAME_OFF(788)))
#define found_unit (*(int *)(frame_ + FRAME_OFF(792)))
#define casualties (*(int *)(frame_ + FRAME_OFF(796)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(800)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(808)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl game_mp_host_turn_loop(i32 force_process)

{
  byte start_civ;
  SHORT SVar2;
  iptr name_str;
  int result;
  iptr host_civ;
  uptr log_civ;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  host_civ = human_civ;
  name_str = civ_name_plural(human_civ);
  dbg_logf_str_int(ADDR(0x62c7d0, ((u8 *)&g.d_0062c7d0)),name_str,host_civ);
  for (civ = 1; (int)civ < 8; civ++) {
    if (((human_civ != civ) &&
        ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      log_civ = civ;
      name_str = civ_name_plural(civ);
      dbg_logf_str_int(ADDR(0x62c7e0, ((u8 *)&g.d_0062c7e0)),name_str,log_civ);
    }
  }
  net_reset_error_counts();
  map_rebuild_unit_flags();
  picwnd_close((PictureWindowCore *)&advisor_window);
  picwnd_close((PictureWindowCore *)&casualty_window);
  menu_update_states();
  ui_redraw_all_maps(1);
  mapview_update_title((FrameWindow *)&map_views);
  found_unit = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
      mapview_center_on
                ((ViewWindow *)&map_views,(int)units[unit].x,(int)units[unit].y);
      found_unit++;
      break;
    }
  }
  if (found_unit == 0) {
    for (unit = 0; unit < game.num_cities; unit++) {
      if ((cities[unit].id != 0) && (cities[unit].owner == human_civ)) {
        mapview_center_on
                  ((ViewWindow *)&map_views,(int)cities[unit].x,(int)cities[unit].y
                  );
        break;
      }
    }
  }
  start_civ = turn_resume_civ;
  if (turn_resume_civ != 0) {
    do {
      if ((1 << (turn_resume_civ & 0x1f) & (uint)game.civs_alive) != 0) goto LAB_0048ccea;
      turn_resume_civ++;
      if (turn_resume_civ == 8) {
        turn_resume_civ = 0;
      }
    } while (turn_resume_civ != start_civ);
    game_over_reason = 1;
  }
LAB_0048ccea:
  do {
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(60000);
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    game_calc_human_wonder_range();
    if (turn_resume_civ == 0) {
      game_advance_turn(0xfffffffd);
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(60000);
    }
    result = game_check_retirement();
    if ((result != 0) || (game_over_reason != 0)) {
      game_loop_active = '\0';
LAB_0048d957:
      mp_turn_timer_stop(0);
      net_host_quit_handoff();
      if (game_over_reason != 0) {
        game_handle_game_over();
      }
      seh_state = 0xffffffff;
      /* inlined unwind funclet 0048d989 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      return;
    }
    if ((scenario_events_loaded != 0) && ((turn_resume_civ == 0 || (turn_resume_new_game != 0)))) {
      events_check_turn((ScenarioEvents *)&scenario_events,(int)game.turn);
      events_check_turn_interval((ScenarioEvents *)&scenario_events,(int)game.turn);
      events_check_random_turn((ScenarioEvents *)&scenario_events,(int)game.turn);
      events_check_received_tech((ScenarioEvents *)&scenario_events);
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    for (civ = 0; (game_loop_active != '\0' && ((int)civ < 8)); civ++) {
      game.human_players = (pending_human_players | game.human_players) & (byte)net_claimed_civs_mask;
      pending_human_players = 0;
      human_civ = (&net_slot_civs)[net_local_slot * 0x15];
      game.player_civ = (i8)human_civ;
      if (((int)(uint)turn_resume_civ <= (int)civ) &&
         ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) {
        if ((((turn_resume_civ != 0) && (turn_resume_civ != civ)) || (turn_resume_civ == 0)) ||
           ((char)force_process != '\0')) {
          units_reset_for_turn(civ);
        }
        net_send_state_diff(0xff,2,0,0,0);
        XD_FlushSendBuffer(5000);
        while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
          net_process_messages((NetSession *)&net_session,1,0);
        }
        game.turn_civ = (byte)civ;
        if (human_civ == civ) {
          *(i32 *)(&net_civ_new_player_flags + civ * 4) = 0;
          if (game_loop_active == '\0') {
            net_send_message(0x31,0,0,human_civ,0,0,0,0,0,0);
            goto LAB_0048d957;
          }
          if ((*(short *)(&civ_intro_shown + civ * 2) == 0) && (autoplay_active == 0)) {
            civ_intro_popup(civ);
            *(i16 *)(&civ_intro_shown + civ * 2) = 1;
          }
          if (mp_turn_time_limit_ms != 0) {
            mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
            main_view_timer_cache_i32 = 0xffffffff;
          }
          mp_turn_civ_i32 = civ;
          menu_update_states();
          main_view_timer_cache_i32 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          rect_left2 = main_view_frame_left;
          rect_top2 = main_view_frame_top;
          rect_right2 = main_view_frame_right;
          rect_bottom2 = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&rect_left2);
          net_send_message(0x69,0xff,civ,0,0,0,0,0,0,0);
          mapview_update_title((FrameWindow *)&map_views);
          map_redraw_all_views(human_civ,1);
          status_draw_civ_color(civ);
          casualties = *(int *)(&casualty_counts + human_civ * 4) -
                     *(int *)(&casualty_reported_counts + human_civ * 4);
          if (autoplay_active == 0) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            name_str = civ_leader_title(human_civ);
            text_set_string_arg(0,name_str);
            name_str = civ_leader_name(human_civ);
            text_set_string_arg(1,name_str);
            if (*(int *)(&casualty_reported_counts + human_civ * 4) <
                *(int *)(&casualty_counts + human_civ * 4)) {
              *(i32 *)(&casualty_reported_counts + human_civ * 4) =
                   *(i32 *)(&casualty_counts + human_civ * 4);
              text_set_number_arg(0,casualties);
              if (casualties == 1) {
                dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7f0, ((u8 *)&g.d_0062c7f0)));
              }
              else {
                dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7fc, ((u8 *)&g.d_0062c7fc)));
              }
              dialog_add_sprite((DialogOptionList *)&dialog2,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
              input_flush_events();
              snd_play_effect(0x30,0,0,0);
              dlg_show_modal(&dialog2,0);
              if (dialog2.result_extra != 0) {
                casualty_timeline_show(human_civ);
              }
            }
            else {
              dialog_load_text_noflags(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c808, ((u8 *)&g.d_0062c808)));
              dialog_add_sprite((DialogOptionList *)&dialog2,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
              input_flush_events();
              snd_play_effect(0x30,0,0,0);
              dlg_show_modal(&dialog2,0);
            }
          }
          if (autoplay_active == 0) {
            if (turn_resume_civ == 0) {
              civ_check_throne_room_upgrade();
            }
            if (((turn_resume_civ == 0) || (turn_resume_new_game != 0)) || ((char)force_process != '\0')) {
              if ((turn_resume_civ != 0) && (turn_resume_new_game != 0)) {
                mapview_update_title((FrameWindow *)&map_views);
                map_redraw_all_views(human_civ,1);
                wnd_flush_paint();
              }
              civ_process_turn(civ);
            }
            game_turn_start_popups();
            if (mp_turn_time_limit_ms != 0) {
              mp_turn_timer_start(1);
            }
            game_player_move_loop();
          }
          else {
            saved_human_players_i32 = (uint)game.human_players;
            game.human_players = '\0';
            if (((turn_resume_civ == 0) || (turn_resume_new_game != 0)) || ((char)force_process != '\0')) {
              if ((turn_resume_civ != 0) && (turn_resume_new_game != 0)) {
                mapview_update_title((FrameWindow *)&map_views);
                map_redraw_all_views(human_civ,1);
                wnd_flush_paint();
              }
              civ_process_turn(civ);
            }
            if (mp_turn_time_limit_ms != 0) {
              mp_turn_timer_start(1);
            }
            ai_process_civ_units();
            game.human_players = saved_human_players;
            SVar2 = GetAsyncKeyState(0x1b);
            if (((int)SVar2 & 0x8001U) != 0) {
              autoplay_turns_left = 1;
            }
            autoplay_turns_left--;
            if (autoplay_turns_left == 0) {
              autoplay_active = 0;
            }
          }
          if (mp_turn_time_limit_ms != 0) {
            mp_turn_timer_stop(1);
          }
        }
        else if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          *(i32 *)(&net_civ_new_player_flags + civ * 4) = 0;
          net_tile_sync_enabled = 0;
          mp_turn_civ_i32 = civ;
          menu_update_states();
          main_view_timer_cache_i32 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          rect_left2 = main_view_frame_left;
          rect_top2 = main_view_frame_top;
          rect_right2 = main_view_frame_right;
          rect_bottom2 = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&rect_left2);
          net_send_message(0x69,0xff,civ,0,0,0,0,0,0,0);
          map_redraw_all_views(human_civ,1);
          status_draw_civ_color(civ);
          if ((turn_resume_civ == 0) || (turn_resume_new_game != 0)) {
            if ((turn_resume_civ != 0) && (turn_resume_new_game != 0)) {
              mapview_update_title((FrameWindow *)&map_views);
              wnd_flush_paint();
            }
            civ_process_turn(civ);
          }
          ai_process_civ_units();
          net_tile_sync_enabled = 1;
        }
        else {
          result = *(int *)(&net_civ_slots + civ * 4);
          mp_turn_civ_i32 = civ;
          menu_update_states();
          main_view_timer_cache_i32 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          rect_left2 = main_view_frame_left;
          rect_top2 = main_view_frame_top;
          rect_right2 = main_view_frame_right;
          rect_bottom2 = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&rect_left2);
          nm_start_civ_count = 0;
          *(i32 *)(&net_civ_turn_ended + civ * 4) = 0;
          net_send_message(0x69,0xff,civ,0,0,0,0,0,0,0);
          map_redraw_all_views(human_civ,1);
          status_draw_civ_color(civ);
          net_send_message(0x16,*(i32 *)(&net_player_slots + result * 0x54),0,0,0,0,0,0,0,0);
          if (*(int *)(&net_civ_new_player_flags + civ * 4) != 0) {
            *(i32 *)(&net_civ_new_player_flags + civ * 4) = 0;
            crt_strcpy(&text_string_args,
                         &net_slot_player_names + *(int *)(&net_civ_slots + civ * 4) * 0x54);
            net_send_text_args(0x3f,0xff,1,0,
                               *(iptr *)(&net_player_slots +
                                        *(int *)(&net_civ_slots + civ * 4) * 0x54),0);
            popup_game_with_sprite(ADDR(0x62c818, ((u8 *)&g.d_0062c818)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          net_heartbeat_send(civ);
          while ((((*(int *)(&net_civ_turn_ended + civ * 4) == 0 && (nm_end_sequence_count == 0)) &&
                  (player_has_quit == '\0')) && (game_loop_active != '\0'))) {
            net_process_messages((NetSession *)&net_session,1,0);
            net_heartbeat_check(civ);
          }
          nm_start_civ_count = 0;
          nm_end_sequence_count = 0;
        }
        status_redraw(1);
        net_check_lost_connections();
        if ((player_has_quit == '\0') || (mp_turn_civ_i32 == human_civ)) {
          for (unit = 0; unit < game.num_units; unit++) {
            if ((units[unit].id != 0) && ((int)units[unit].owner == civ)) {
              unit_exhaust_moves(unit);
            }
          }
          city = (iptr)game.num_cities;
          while (city = city - 1, -1 < city) {
            if (cities[city].id != 0) {
              cities[city].flags = cities[city].flags & 0xffbfffff;
            }
          }
        }
        saved_turn_civ = 0;
        turn_resume_civ = 0;
        saved_resume_new_game = 0;
        turn_resume_new_game = 0;
        (*(i8 *)((char *)&force_process + 0)) = '\0';
        game.transient_flags = game.transient_flags & 0xfffe;
        ui_pump_messages();
        if (game_loop_active == '\0') goto LAB_0048d957;
        if ((game_loop_active != '\0') && (game_over_reason != 0)) {
          game_loop_active = '\0';
          goto LAB_0048d957;
        }
      }
    }
    if (game_loop_active == '\0') goto LAB_0048d957;
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
#undef net_claimed_civs_mask
#undef net_local_slot
#undef net_slot_civs
#undef net_tile_sync_enabled
#undef nm_start_civ_count
#undef player_has_quit
#undef saved_human_players
#undef saved_resume_new_game
#undef saved_turn_civ
#undef scenario_events_loaded
#undef turn_resume_civ
#undef turn_resume_new_game
#undef main_view_timer_cache_i32
#undef saved_human_players_i32
#undef mp_turn_civ_i32
#undef civ
#undef city
#undef unit
#undef dialog2
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2
#undef found_unit
#undef casualties
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00497da0 auto */
#define ch (*(int *)(frame_ + FRAME_OFF(0)))
#define dst (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
iptr __cdecl save_read_cstr(iptr buf,iptr file)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  dst = (i8 *)buf;
  ch = 1;
  for (i = 0; (ch != 0 && (i < 0x4f)); i++) {
    ch = _fgetc((FILE *)file);
    *dst = (i8)ch;
    dst++;
  }
  _fgetc((FILE *)file);
  return buf;
}
#undef ch
#undef dst
#undef i

/* 00497e0f auto */
#define ch (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl save_write_cstr_eof(iptr str,iptr file)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ch = 1;
  while (ch != 0) {
    ch = (int)*(char *)str;
    str++;
    _fputc(ch,(FILE *)file);
  }
  _fputc(0x1a,(FILE *)file);
  return;
}
#undef ch

/* 00498784 auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define i (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl passwords_reset(void)

{
  byte sign;
  int rnd;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 0xff; i++) {
    rnd = _rand();
    sign = (byte)(rnd >> 0x1f);
    (&civ_passwords)[i] = (((byte)rnd ^ sign) - sign ^ sign) - sign;
  }
  for (civ = 0; civ < 8; civ++) {
    (&civ_passwords)[civ * 0x20] = 0;
    *(i32 *)(&civ_password_prompt_pending + civ * 4) = 0;
    *(i32 *)(&civ_has_password + civ * 4) = 0;
  }
  passwords_scramble();
  return;
}
#undef civ
#undef i

/* 0049882b auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl passwords_refresh_flags(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  passwords_unscramble();
  for (civ = 0; civ < 8; civ++) {
    if ((&civ_passwords)[civ * 0x20] == '\0') {
      *(i32 *)(&civ_password_prompt_pending + civ * 4) = 0;
      *(i32 *)(&civ_has_password + civ * 4) = 0;
    }
    else {
      *(i32 *)(&civ_password_prompt_pending + civ * 4) = 1;
      *(i32 *)(&civ_has_password + civ * 4) = 1;
    }
  }
  passwords_scramble();
  return;
}
#undef civ

/* 004988b8 auto */
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
#define carry (*(byte *)(frame_ + FRAME_OFF(4)))
void __cdecl passwords_scramble(void)

{
  char prev_byte;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  prev_byte = civ_passwords_last_byte;
  for (i = 0; carry = prev_byte << 5, i < 0x100; i++) {
    prev_byte = (&civ_passwords)[i];
    (&civ_passwords)[i] =
         ((byte)((uint)(int)(char)(&civ_passwords)[i] >> 3) & 0x1f | carry) ^ (byte)i
    ;
  }
  return;
}
#undef i
#undef carry

/* 00498943 auto */
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
#define prev_byte (*(char *)(frame_ + FRAME_OFF(8)))
void __cdecl passwords_unscramble(void)

{
  uint carry;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  prev_byte = civ_passwords;
  for (i = 0xff; -1 < i; i--) {
    carry = (uint)prev_byte;
    (&civ_passwords)[i] = (&civ_passwords)[i] ^ (byte)i;
    prev_byte = (&civ_passwords)[i];
    (&civ_passwords)[i] = (&civ_passwords)[i] << 3 | (byte)(carry >> 5) & 7;
  }
  return;
}
#undef i
#undef prev_byte

/* 004989d3 auto */
#define title (*(char (*)[128])(frame_ + FRAME_OFF(4)))
void __cdecl password_dialog_set_title(iptr dialog,int civ,i32 label_id)

{
  size_t title_len;
  i32 title_mem;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  crt_strcpy(title,(iptr)&civ_names[civ].leader_name);
  str_append_label((iptr)title,label_id);
  title_len = _strlen(title);
  title_mem = memblock_alloc(dialog + 0x254,title_len + 1);
  *(i32 *)(dialog + 0x134) = title_mem;
  crt_strcpy(*(i32 *)(dialog + 0x134),title);
  return;
}
#undef title

/* 004a70b0 auto */
#define SCHAR_00h_0064bc1a (*(i8 *)((u8 *)&g.d_0064bc1a))
#define SCHAR_00h_0064bc1c (*(i8 *)((u8 *)&g.d_0064bc1c))
#define prefs_accelerated_start (*(i16 *)((u8 *)&g.d_0064bc56))
#define prefs_barbarity (*(i16 *)((u8 *)&g.d_0064bc28))
#define prefs_difficulty (*(i16 *)((u8 *)&g.d_0064bc14))
#define prefs_enemies_choice (*(i16 *)((u8 *)&g.d_0064bc24))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define prefs_game_rules (*(i16 *)((u8 *)&g.d_0064bc10))
#define prefs_gender (*(i16 *)((u8 *)&g.d_0064bc18))
#define prefs_map_size (*(i16 *)((u8 *)&g.d_0064bc26))
#define prefs_message_options (*(i16 *)((u8 *)&g.d_0064bc22))
#define prefs_rules_choice (*(i16 *)((u8 *)&g.d_0064bc54))
#define prefs_tribe (*(i16 *)((u8 *)&g.d_0064bc16))
#define prefs_world_params (*(i16 *)((u8 *)&g.d_0064bc2a))
#define prefs_default_level_i16 (*(i16 *)((u8 *)&g.d_0064bc12))
#define _SCHAR_00h_0064bc1a (*(i16 *)((u8 *)&g.d_0064bc1a))
#define _SCHAR_00h_0064bc1c (*(i16 *)((u8 *)&g.d_0064bc1c))
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl prefs_set_defaults(void)

{
  int has_memory;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  prefs_game_rules = 0x3f;
  prefs_default_level_i16 = 0;
  if (999 < screen_width) {
    prefs_default_level_i16 = 2;
  }
  prefs_difficulty = 0;
  prefs_tribe = 0;
  prefs_gender = 0;
  _SCHAR_00h_0064bc1a = 6;
  _SCHAR_00h_0064bc1c = 4;
  prefs_enemies_choice = 0;
  prefs_map_size = 1;
  prefs_game_options = 0x3f3258;
  has_memory = mem_check_available(10000000);
  if (has_memory == 0) {
    prefs_game_options = prefs_game_options & 0xffdfffff;
  }
  prefs_message_options = 0;
  prefs_barbarity = 2;
  for (i = 0; i < 5; i++) {
    (&prefs_world_params)[i] = 0;
  }
  crt_strcpy(&prefs_text_field,&prefs_defaults_empty_str);
  prefs_rules_choice = 0;
  prefs_accelerated_start = 0;
  return;
}
#undef SCHAR_00h_0064bc1a
#undef SCHAR_00h_0064bc1c
#undef prefs_accelerated_start
#undef prefs_barbarity
#undef prefs_difficulty
#undef prefs_enemies_choice
#undef prefs_game_options
#undef prefs_game_rules
#undef prefs_gender
#undef prefs_map_size
#undef prefs_message_options
#undef prefs_rules_choice
#undef prefs_tribe
#undef prefs_world_params
#undef prefs_default_level_i16
#undef _SCHAR_00h_0064bc1a
#undef _SCHAR_00h_0064bc1c
#undef i

/* 004a71bb auto */
#define prefs_clear_chat_on_boot (*(i16 *)((u8 *)&g.d_006665fc))
#define prefs_clear_chat_on_new_game (*(i16 *)((u8 *)&g.d_006665fa))
#define prefs_email_address (*(i8 *)((u8 *)&g.d_00666590))
#define prefs_hotseat_menu_choice (*(i16 *)((u8 *)&g.d_0066653c))
#define prefs_hotseat_players_choice (*(i16 *)((u8 *)&g.d_006665d8))
#define prefs_lan_menu_choice (*(i16 *)((u8 *)&g.d_0066653e))
#define prefs_main_menu_choice (*(i16 *)((u8 *)&g.d_00666538))
#define prefs_mp_chat_from_start (*(i16 *)((u8 *)&g.d_0066654c))
#define prefs_mp_double_moves (*(i16 *)((u8 *)&g.d_00666600))
#define prefs_mp_double_production (*(i16 *)((u8 *)&g.d_006665fe))
#define prefs_mp_kill_on_retire (*(i16 *)((u8 *)&g.d_00666548))
#define prefs_mp_open_game (*(i16 *)((u8 *)&g.d_00666546))
#define prefs_mp_show_human_starts (*(i16 *)((u8 *)&g.d_0066654a))
#define prefs_mp_simultaneous_moves (*(i16 *)((u8 *)&g.d_0066654e))
#define prefs_multiplayer_type (*(i16 *)((u8 *)&g.d_0066653a))
#define prefs_net_game_name (*(i8 *)((u8 *)&g.d_00666550))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
#define prefs_net_protocol (*(i16 *)((u8 *)&g.d_00666544))
#define prefs_pbem_menu_choice (*(i16 *)((u8 *)&g.d_00666542))
#define prefs_turn_timer_choice (*(i16 *)((u8 *)&g.d_006665d0))
#define mp_prefs_setting_1_i16 (*(i16 *)((u8 *)&g.d_00666540))
#define mp_prefs_setting_5_i16 (*(i16 *)((u8 *)&g.d_006666f2))
#define j (*(iptr *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl prefs_set_mp_defaults(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  prefs_main_menu_choice = 0;
  prefs_multiplayer_type = 0;
  prefs_hotseat_menu_choice = 0;
  prefs_lan_menu_choice = 0;
  mp_prefs_setting_1_i16 = 0;
  prefs_pbem_menu_choice = 0;
  prefs_net_protocol = 0;
  prefs_mp_open_game = 0;
  prefs_mp_kill_on_retire = 0;
  prefs_mp_show_human_starts = 0;
  prefs_mp_chat_from_start = 0;
  prefs_mp_simultaneous_moves = 0;
  prefs_net_game_name = 0;
  prefs_net_player_name = 0;
  prefs_email_address = 0;
  prefs_net_ip_address = 0;
  prefs_turn_timer_choice = 0;
  crt_strcpy(&prefs_turn_timer_custom,&prefs_turn_timer_default_str);
  prefs_hotseat_players_choice = 0;
  _memset(&prefs_parley_wnd_rect,0,0x10);
  _memset(&prefs_chat_wnd_rect,0,0x10);
  prefs_clear_chat_on_new_game = 0;
  prefs_clear_chat_on_boot = 0;
  prefs_mp_double_production = 0;
  prefs_mp_double_moves = 0;
  mp_prefs_setting_2 = 0;
  mp_prefs_setting_3 = 0;
  mp_prefs_setting_4 = 0;
  for (i = 0; i < 7; i++) {
    for (j = 0; j < 0x18; j++) {
      (&mp_prefs_settings_table)[i * 0x18 + j] = 0;
    }
  }
  mp_prefs_setting_5_i16 = 0;
  return;
}
#undef prefs_clear_chat_on_boot
#undef prefs_clear_chat_on_new_game
#undef prefs_email_address
#undef prefs_hotseat_menu_choice
#undef prefs_hotseat_players_choice
#undef prefs_lan_menu_choice
#undef prefs_main_menu_choice
#undef prefs_mp_chat_from_start
#undef prefs_mp_double_moves
#undef prefs_mp_double_production
#undef prefs_mp_kill_on_retire
#undef prefs_mp_open_game
#undef prefs_mp_show_human_starts
#undef prefs_mp_simultaneous_moves
#undef prefs_multiplayer_type
#undef prefs_net_game_name
#undef prefs_net_ip_address
#undef prefs_net_player_name
#undef prefs_net_protocol
#undef prefs_pbem_menu_choice
#undef prefs_turn_timer_choice
#undef mp_prefs_setting_1_i16
#undef mp_prefs_setting_5_i16
#undef j
#undef i

/* 004a733d auto */
#define prefs_game_rules (*(i16 *)((u8 *)&g.d_0064bc10))
#define prefs_main_menu_choice (*(i16 *)((u8 *)&g.d_00666538))
void __cdecl prefs_load_civ2dat(void)

{
  FILE *_File;
  size_t read_count;
  
  _File = _fopen(PTR_s_CIV2_DAT_0062cec8,&civ2dat_read_mode_str);
  if (_File == (FILE *)0x0) {
    prefs_set_defaults();
    prefs_set_mp_defaults();
  }
  else {
    read_count = _fread(&prefs_game_rules,0x48,1,_File);
    if (read_count == 0) {
      prefs_set_defaults();
    }
    read_count = _fread(&prefs_main_menu_choice,0x1bc,1,_File);
    if (read_count == 0) {
      prefs_set_mp_defaults();
    }
    _fclose(_File);
  }
  return;
}
#undef prefs_game_rules
#undef prefs_main_menu_choice

/* 004a73d9 auto */
#define prefs_game_rules (*(i16 *)((u8 *)&g.d_0064bc10))
#define prefs_main_menu_choice (*(i16 *)((u8 *)&g.d_00666538))
#define failed (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl prefs_save_civ2dat(void)

{
  FILE *_File;
  size_t write_count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  failed = 1;
  _File = _fopen(PTR_s_CIV2_DAT_0062cec8,&civ2dat_write_mode_str);
  if (((_File != (FILE *)0x0) && (write_count = _fwrite(&prefs_game_rules,0x48,1,_File), write_count != 0)) &&
     (write_count = _fwrite(&prefs_main_menu_choice,0x1bc,1,_File), write_count != 0)) {
    failed = 0;
  }
  if ((_File != (FILE *)0x0) && (_fclose(_File), failed != 0)) {
    crt_remove(PTR_s_CIV2_DAT_0062cec8);
  }
  return failed;
}
#undef prefs_game_rules
#undef prefs_main_menu_choice
#undef failed

/* 004a7754 auto */
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
#define landmass_starts (*(int (*)[64])(frame_ + FRAME_OFF(16)))
#define y2 (*(int *)(frame_ + FRAME_OFF(272)))
#define start_units (*(iptr (*)[8])(frame_ + FRAME_OFF(276)))
#define landmass2 (*(iptr *)(frame_ + FRAME_OFF(308)))
#define size_bonus (*(int *)(frame_ + FRAME_OFF(312)))
#define y3 (*(int *)(frame_ + FRAME_OFF(316)))
#define x2 (*(int *)(frame_ + FRAME_OFF(320)))
#define x3 (*(int *)(frame_ + FRAME_OFF(324)))
#define dist (*(int *)(frame_ + FRAME_OFF(328)))
#define grass_count (*(int *)(frame_ + FRAME_OFF(332)))
#define terrain2 (*(uint *)(frame_ + FRAME_OFF(336)))
#define other_civ (*(iptr *)(frame_ + FRAME_OFF(340)))
#define max_score (*(int *)(frame_ + FRAME_OFF(344)))
#define min_dist (*(int *)(frame_ + FRAME_OFF(348)))
#define k (*(iptr *)(frame_ + FRAME_OFF(352)))
#define score (*(int *)(frame_ + FRAME_OFF(356)))
#define civ_scores (*(int (*)[8])(frame_ + FRAME_OFF(360)))
#define special_count (*(int *)(frame_ + FRAME_OFF(392)))
void __cdecl game_balance_start_positions(void)

{
  byte terrain_id;
  iptr found_unit;
  iptr other_landmass;
  int unit;
  byte *tile;
  i8 frame_[FRAME_OFF(400)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (landmass2 = 0; landmass2 < 0x40; landmass2++) {
    landmass_starts[landmass2] = 0;
  }
  x3 = (int)map.width >> 1;
  y3 = (int)map.height >> 1;
  for (civ = 1; civ < 8; civ++) {
    found_unit = unit_find_nearest(x3,y3,civ,-1);
    start_units[civ] = found_unit;
    if (-1 < found_unit) {
      landmass2 = tile_land_landmass(x3,y3);
      if (-1 < landmass2) {
        landmass_starts[landmass2]++;
      }
    }
  }
  max_score = 0;
  for (civ = 1; civ < 8; civ++) {
    unit = start_units[civ];
    if (-1 < unit) {
      x3 = (int)units[unit].x;
      y3 = (int)units[unit].y;
      landmass2 = tile_land_landmass(x3,y3);
      landmass2 = int_clamp(landmass2,0,0x3f);
      score = 0;
      min_dist = 999;
      for (other_civ = 1; other_civ < 8; other_civ++) {
        unit = start_units[other_civ];
        if ((-1 < unit) && (civ != other_civ)) {
          x2 = (int)units[unit].x;
          y2 = (int)units[unit].y;
          other_landmass = tile_land_landmass(x2,y2);
          if (landmass2 == other_landmass) {
            dist = map_distance_diag(x3,y3,x2,y2);
            if (dist < min_dist) {
              min_dist = dist;
            }
          }
        }
      }
      if (9 < min_dist) {
        if (min_dist < 0x14) {
          score++;
        }
        else if (min_dist == 999) {
          size_bonus = (int)*(short *)(&landmass_table + landmass2 * 0x10) / 0x32;
          size_bonus = int_clamp(size_bonus,3,6);
          score += size_bonus;
        }
        else {
          score += 2;
        }
      }
      grass_count = 0;
      special_count = 0;
      for (k = 0; k < 0x15; k++) {
        x2 = map_wrap_x((char)(&city_tile_dx_table)[k] + x3);
        y2 = (char)(&city_tile_dy_table)[k] + y3;
        unit = map_in_bounds(x2,y2);
        if (unit != 0) {
          terrain_id = tile_terrain(x2,y2);
          terrain2 = (uint)terrain_id;
          if (terrain2 == 2) {
            grass_count++;
          }
          tile = (byte *)tile_at(x2,y2);
          if ((*tile & 0x80) != 0) {
            special_count++;
          }
        }
      }
      if (special_count < 4) {
        if (3 < grass_count) {
          score += 2;
        }
      }
      else {
        score += 4;
      }
      switch((int)*(short *)(&landmass_table + landmass2 * 0x10) / 0x32) {
      case 0:
        break;
      case 1:
        score++;
        break;
      case 2:
        score += 2;
        break;
      case 3:
        score += 3;
        break;
      default:
        score += 3;
      }
      if (max_score < score) {
        max_score = score;
      }
      civ_scores[civ] = score;
    }
  }
  for (civ = 1; civ < 8; civ++) {
    unit = start_units[civ];
    if (-1 < unit) {
      if (((3 < max_score - civ_scores[civ]) ||
          (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 &&
           (game.difficulty == 5)))) ||
         ((game.multiplayer != '\0' && (game.difficulty == 5)))) {
        unit_create(0,civ,(int)units[unit].x,(int)units[unit].y);
        if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
           (game.difficulty != 5)) {
          civ_scores[civ] += 3;
        }
        else {
          civ_scores[civ]++;
        }
      }
      for (k = 0; k < max_score - civ_scores[civ]; k++) {
        civ_research_complete(civ,0);
      }
    }
  }
  return;
}
#undef civ
#undef landmass_starts
#undef y2
#undef start_units
#undef landmass2
#undef size_bonus
#undef y3
#undef x2
#undef x3
#undef dist
#undef grass_count
#undef terrain2
#undef other_civ
#undef max_score
#undef min_dist
#undef k
#undef score
#undef civ_scores
#undef special_count

/* 004a9785 auto */
#define path_goal_x (*(iptr *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(i32 *)((u8 *)&g.d_0062d044))
#define path_road_planning (*(i32 *)((u8 *)&g.d_0062d040))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define best_dir (*(iptr *)(frame_ + FRAME_OFF(12)))
#define y4 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define home_id (*(i8 *)(frame_ + FRAME_OFF(20)))
#define steps (*(int *)(frame_ + FRAME_OFF(24)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(28)))
#define x4 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define y2 (*(int *)(frame_ + FRAME_OFF(48)))
#define x2 (*(int *)(frame_ + FRAME_OFF(60)))
#define start_y2 (*(int (*)[8])(frame_ + FRAME_OFF(64)))
#define terrain2 (*(uint *)(frame_ + FRAME_OFF(96)))
#define start_x2 (*(int (*)[8])(frame_ + FRAME_OFF(100)))
#define y3 (*(int *)(frame_ + FRAME_OFF(132)))
#define dist (*(int *)(frame_ + FRAME_OFF(136)))
#define i (*(iptr *)(frame_ + FRAME_OFF(140)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(144)))
#define best_score (*(int *)(frame_ + FRAME_OFF(148)))
#define site_score (*(int *)(frame_ + FRAME_OFF(152)))
void __cdecl game_accelerated_start(int extra_level)

{
  char civ2;
  short y5;
  iptr x3;
  byte terrain_id;
  iptr in_bounds;
  iptr city;
  iptr rnd;
  iptr unit3;
  iptr stack_count;
  int unit2;
  int result;
  iptr x;
  byte *tile;
  uint coin;
  int y;
  uint sign_mask;
  uptr civ4;
  uptr civ3;
  i8 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (civ = 0; civ < 8; civ++) {
    start_y2[civ] = -1;
    start_x2[civ] = start_y2[civ];
  }
  for (unit = 0; unit < game.num_units; unit++) {
    if (units[unit].id != 0) {
      y5 = units[unit].y;
      civ2 = units[unit].owner;
      start_x2[civ2] = (int)units[unit].x;
      start_y2[civ2] = (int)y5;
    }
  }
  civ = 1;
  do {
    if (7 < civ) {
      game.turn = ((short)extra_level * 4 + 4) * 5 + 1;
      return;
    }
    x3 = start_x2[civ];
    y = start_y2[civ];
    in_bounds = map_in_bounds(x3,y);
    if (in_bounds != 0) {
      civ_give_advance(civ,0x24,0,0,1);
      civ_give_advance(civ,9,0,0,1);
      civ_give_advance(civ,1,0,0,1);
      civ_give_advance(civ,8,0,0,1);
      civs[civ].num_advances = 4;
      if (extra_level != 0) {
        for (i = 0; i < 3; i++) {
          civ_research_complete(civ,0);
          civs[civ].num_advances++;
        }
      }
      city = city_create(x3,y,civ);
      if (-1 < city) {
        rnd = _rand();
        civs[civ].gold = (rnd % 0x32 + 0x19) * (extra_level + 1);
        if (extra_level == 0) {
          cities[city].size = 3;
        }
        else {
          cities[city].size = 5;
        }
        unit3 = tile_first_unit(x3,y);
        stack_count = unit_stack_sum(unit3,2);
        if (1 < stack_count) {
          home_id = (i8)city;
          units[unit3].home_city = home_id;
        }
        unit_type = (iptr)cities[city].building;
        _rand();
        if (unit_type != 6) {
          unit_type = 4;
        }
        unit2 = unit_create(unit_type,civ,x3,y);
        units[unit2].orders = 2;
        unit2 = unit_create(3,civ,x3,y);
        units[unit2].orders = 2;
        civ3 = civ;
        x = x3;
        unit2 = y;
        result = civ_has_advance(civ,0x57);
        unit_create(0x10 - (uint)(result == 0),civ3,x,unit2);
        if (extra_level != 0) {
          civ4 = civ;
          x = x3;
          unit2 = y;
          result = civ_has_advance(civ,0x40);
          unit_create(0x11 - (uint)(result == 0),civ4,x,unit2);
        }
        city_set_improvement(city,4,1);
        if (extra_level != 0) {
          unit2 = civ_has_advance(civ,0x41);
          if (unit2 != 0) {
            city_set_improvement(city,3,1);
          }
          unit2 = civ_has_advance(civ,0x14);
          if (unit2 == 0) {
            city_set_improvement(city,2,1);
          }
          else {
            city_set_improvement(city,5,1);
          }
        }
        accel_start_develop_city(city,(-(uint)(extra_level == 0) & 0xfffffffe) + 4);
        if (extra_level != 0) {
          best_score = -1;
          best_dir = -1;
          unit2 = tile_landmass(x3,y);
          for (i = 0; i < 8; i++) {
            x = map_wrap_x((char)(&dir_dx_table)[i] * 5 + x3);
            y3 = (char)(&dir_dy_table)[i] * 5 + y;
            result = map_in_bounds(x,y3);
            if (((result != 0) && (result = tile_is_ocean(x,y3), result == 0)) &&
               (result = tile_landmass(x,y3), result == unit2)) {
              city_find_nearest(x,y3,-1,0xffffffff,-1);
              for (unit = 0; unit < game.num_units; unit++) {
                if (((units[unit].id != 0) &&
                    (result = tile_city_owner((int)units[unit].x,(int)units[unit].y),
                    result < 0)) &&
                   (dist = map_distance_diag((int)units[unit].x,(int)units[unit].y,
                                                  x,y3), dist < nearest_city_dist)) {
                  nearest_city_dist = dist;
                }
              }
              if (4 < dist) {
                site_score = 0;
                terrain_id = tile_terrain(x,y3);
                terrain2 = (uint)terrain_id;
                if (terrain2 == 2) {
                  site_score = 4;
                }
                if (terrain2 == 1) {
                  site_score = 2;
                }
                if (site_score != 0) {
                  tile = (byte *)tile_at(x,y3);
                  if ((*tile & 0x80) != 0) {
                    site_score++;
                  }
                  if (best_score < site_score) {
                    best_score = site_score;
                    best_dir = i;
                    y4 = y3;
                    x4 = x;
                  }
                }
              }
            }
          }
          if (best_dir < 0) {
            civ_give_advance(civ,0x14,0,0,1);
            civ_give_advance(civ,0x2f,0,0,1);
            civ_give_advance(civ,0x12,0,0,1);
            civ_give_advance(civ,0x38,0,0,1);
            civ_give_advance(civ,0xc,0,0,1);
            civ_give_advance(civ,0x36,0,0,1);
            cities[city].size = 7;
            city_set_improvement(city,0xe,1);
            civs[civ].gold += 0x19;
            accel_start_develop_city(city,2);
            unit_create(4,civ,(int)cities[city].x,(int)cities[city].y);
            unit_create(5,civ,(int)cities[city].x,(int)cities[city].y);
            unit_create(0x10,civ,(int)cities[city].x,(int)cities[city].y);
          }
          else {
            city2 = city_create(x4,y4,civ);
            cities[city2].size = 3;
            coin = _rand();
            sign_mask = (int)coin >> 0x1f;
            coin = (coin ^ sign_mask) - sign_mask & 1 ^ sign_mask;
            unit2 = unit_create(3 - (uint)(coin == sign_mask),civ,x4,y4);
            units[unit2].orders = 2;
            unit2 = unit_create((coin == sign_mask) + 3,civ,x4,y4);
            units[unit2].orders = 2;
            unit_create(0xf,civ,x4,y4);
            accel_start_develop_city(city2,2);
            x2 = (int)cities[city2].x;
            y2 = (int)cities[city2].y;
            steps = 0;
            unit2 = map_distance(x3,y,x2,y2);
            if (unit2 < 0x17) {
              path_road_planning = 1;
              path_owner_civ = 0xffffffff;
              path_unit_type = 2;
              path_goal_x = x3;
              path_goal_y = y;
              do {
                unit2 = map_path_next_dir(x2,y2,99);
                if ((unit2 < 0) || (unit2 == 8)) break;
                x2 = map_wrap_x((char)(&dir_dx_table)[unit2] + x2);
                y2 += (char)(&dir_dy_table)[unit2];
                if ((x3 == x2) && (y == y2)) break;
                unit2 = tile_city_owner(x2,y2);
                if ((((unit2 < 0) &&
                     (coin = tile_improvements(x2,y2), (coin & 0x10) == 0)) &&
                    ((tile = (byte *)tile_at(x2,y2), (*tile & 0x80) == 0 ||
                     (unit2 = civ_has_advance(civ,7), unit2 != 0)))) &&
                   ((unit2 = tile_city_or_unit_owner(x2,y2), unit2 < 0 &&
                    (unit2 = tile_owner_at_peace(x2,y2,civ), unit2 < 0)))) {
                  tile_set_improvements(x2,y2,0x10,1,1);
                  tile_update_known(x2,y2,civ);
                }
                steps++;
              } while (steps < 0x32);
              path_road_planning = 0;
            }
          }
        }
        y = civ_has_advance(civ,0x36);
        if (y != 0) {
          civs[civ].government = 2;
        }
      }
    }
    civ++;
  } while( true );
}
#undef path_goal_x
#undef path_goal_y
#undef path_owner_civ
#undef path_road_planning
#undef civ
#undef unit
#undef best_dir
#undef y4
#undef home_id
#undef steps
#undef unit_type
#undef x4
#undef y2
#undef x2
#undef start_y2
#undef terrain2
#undef start_x2
#undef y3
#undef dist
#undef i
#undef city2
#undef best_score
#undef site_score

/* 004aa9c0 auto */
#define SCHAR_00h_0064bc1a (*(schar *)((u8 *)&g.d_0064bc1a))
#define SCHAR_00h_0064bc1c (*(schar *)((u8 *)&g.d_0064bc1c))
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
#define _SCHAR_00h_0064bc1a (*(i16 *)((u8 *)&g.d_0064bc1a))
#define _SCHAR_00h_0064bc1c (*(i16 *)((u8 *)&g.d_0064bc1c))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define j (*(iptr *)(frame_ + FRAME_OFF(4)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl game_init_new(void)

{
  int value;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  scenario_reset_params();
  destroyed_civs_clear();
  for (leader = 0; leader < 8; leader++) {
    *(i32 *)(&leader_flags_table + leader * 0x10) = 0;
  }
  for (leader = 0; leader < 0x15; leader++) {
    leaders[leader].times_used = '\0';
  }
  game.turn = 0;
  game.year = -4000;
  game.first_launch_turn = -1;
  if (game.difficulty == '\0') {
    game.game_options = prefs_game_options & 0xffff7fff | 0x300;
  }
  else {
    game.game_options = prefs_game_options & 0xffff7eff;
  }
  game.transient_flags = 0;
  game.message_options = prefs_message_options;
  game.shown_event_flags = 0;
  moving_units_mode = 1;
  game.num_units = 0;
  game.num_cities = 0;
  game.active_unit = 0;
  game.turn_civ = '\0';
  game.unused_34 = 0;
  game.reveal_map = '\0';
  game.view_civ = -1;
  game.polluted_tiles = 0;
  game.warming_counter = '\0';
  game.global_warmings = '\0';
  game.warming_pollution = 0;
  for (leader = 0; leader < 100; leader++) {
    game.first_discoverer[leader] = '\0';
    game.advance_known_by[leader] = '\0';
  }
  for (leader = 0; leader < 0x1c; leader++) {
    game.wonder_city[leader] = -1;
  }
  for (civ = 0; civ < 8; civ++) {
    civ_reset_spaceship(civ);
    civs[civ].num_cities = 0;
    *(i32 *)(&civ_unit_counts + civ * 4) = 0;
    civs[civ].num_military_units = 0;
    civs[civ].num_ships = 0;
    civs[civ].total_city_size = 0;
    civs[civ].military_strength = 0;
    civs[civ].total_attack = 0;
    civs[civ].researching = -1;
    for (leader = 0; leader < 0x40; leader++) {
      *(i16 *)&civs[civ].continent_military[leader] = 0;
      *(i16 *)&civs[civ].continent_attack[leader] = 0;
      *(i8 *)&civs[civ].continent_cities[leader] = 0;
      *(i8 *)&civs[civ].continent_city_size[leader] = 0;
    }
  }
  value = _rand();
  game.next_history_turn = (i16)(value % 0x32);
  for (leader = 0; leader < 0x96; leader++) {
    for (j = 0; j < 8; j++) {
      (&power_graph_history)[leader * 8 + j] = 0;
    }
  }
  for (civ = 0; civ < 8; civ++) {
    civ_create(civ);
  }
  game.civs_at_start = game.civs_alive;
  game_balance_start_positions();
  if (((10 < (int)_SCHAR_00h_0064bc1a + (int)_SCHAR_00h_0064bc1c) || (6 < _SCHAR_00h_0064bc1a)) ||
     (6 < _SCHAR_00h_0064bc1c)) {
    _SCHAR_00h_0064bc1a = 6;
    _SCHAR_00h_0064bc1c = 4;
  }
  value = bits_count8((uint)game.human_players);
  if (value == 1) {
    civs[game.player_civ].science_rate = SCHAR_00h_0064bc1a;
    civs[game.player_civ].tax_rate = SCHAR_00h_0064bc1c;
    if (game.difficulty == '\0') {
      civs[game.player_civ].gold = 0x32;
    }
  }
  else {
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        civs[civ].science_rate = 6;
        civs[civ].tax_rate = 4;
        if (game.difficulty == '\0') {
          civs[civ].gold = 0x32;
        }
      }
    }
  }
  return;
}
#undef SCHAR_00h_0064bc1a
#undef SCHAR_00h_0064bc1c
#undef moving_units_mode
#undef prefs_game_options
#undef prefs_message_options
#undef _SCHAR_00h_0064bc1a
#undef _SCHAR_00h_0064bc1c
#undef civ
#undef j
#undef leader

/* 004b08e0 auto */
/* Library Function - Single Match
    _$E2
   
   Library: Visual Studio 1998 Debug */

void __cdecl diffeng_global_init(void)

{
  diffeng_static_init_stub();
  return;
}

/* 004b08f5 auto */
/* Library Function - Single Match
    _$E1
   
   Library: Visual Studio 1998 Debug */

void __cdecl diffeng_static_init_stub(void)

{
  return;
}

/* 004b0905 auto */
#define diffeng_mirror_end (*(int *)((u8 *)&g.d_0067a408))
#define diffeng_mirror_size (*(uint *)((u8 *)&g.d_0067a400))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define section (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl diffeng_alloc_mirror(void)

{
  size_t mirror_len;
  i32 result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (diffeng_mirror_buf != 0) {
    diffeng_free_mirror();
  }
  diffeng_mirror_size = 0;
  for (section = 0; section < 0x17; section++) {
    diffeng_mirror_size += (&diffeng_section_padded_sizes)[section * 6];
  }
  if ((diffeng_mirror_size & 3) != 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d0f0, ((u8 *)&g.d_0062d0f0)),ADDR(0x62d0c8, ((u8 *)&g.d_0062d0c8)),0x22);
  }
  diffeng_mirror_buf = (iptr)operator_new(diffeng_mirror_size);
  if ((void *)diffeng_mirror_buf == (void *)0x0) {
    result = 0;
  }
  else {
    _memset((void *)diffeng_mirror_buf,0,diffeng_mirror_size);
    mirror_len = diffeng_client_mirror_size;
    if (net_host_flag != '\0') {
      mirror_len = diffeng_mirror_size;
    }
    diffeng_mirror_end = mirror_len + diffeng_mirror_buf;
    diffeng_copy_to_mirror();
    result = 1;
  }
  return result;
}
#undef diffeng_mirror_end
#undef diffeng_mirror_size
#undef net_host_flag
#undef section

/* 004b0a0a auto */
void __cdecl diffeng_free_mirror(void)

{
  operator_delete((void *)diffeng_mirror_buf);
  diffeng_mirror_buf = 0;
  return;
}

/* 004b0a41 auto */
#define diffeng_scan_ptr (*(iptr *)((u8 *)&g.d_00679fe8))
#define diffeng_scan_section (*(i32 *)((u8 *)&g.d_0067a404))
#define diffeng_scan_offset_i32 (*(i32 *)((u8 *)&g.d_00679fec))
#define section (*(int *)(frame_ + FRAME_OFF(4)))
#define dst (*(iptr *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl diffeng_copy_to_mirror(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  dst = diffeng_mirror_buf;
  for (section = 0; section < 0x17; section++) {
    crt_memcpy(dst,(&diffeng_section_ptrs)[section * 6],
                 *(i32 *)(&diffeng_sections + section * 0x18));
    dst += (&diffeng_section_padded_sizes)[section * 6];
  }
  diffeng_scan_ptr = diffeng_mirror_buf;
  diffeng_scan_section = 0;
  diffeng_scan_offset_i32 = 0;
  return;
}
#undef diffeng_scan_ptr
#undef diffeng_scan_section
#undef diffeng_scan_offset_i32
#undef section
#undef dst

/* 004b0ad0 auto */
#define diffeng_mirror_size (*(uint *)((u8 *)&g.d_0067a400))
#define diffeng_scan_ptr (*(uint * *)((u8 *)&g.d_00679fe8))
#define diffeng_scan_section (*(i32 *)((u8 *)&g.d_0067a404))
#define diffeng_scan_offset_i32 (*(i32 *)((u8 *)&g.d_00679fec))
#define i (*(uint *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl diffeng_invalidate_mirror(void)

{
  uint word_count;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  diffeng_copy_to_mirror();
  diffeng_scan_ptr = (uint *)diffeng_mirror_buf;
  word_count = diffeng_mirror_size >> 2;
  for (i = 0; i < word_count; i++) {
    *diffeng_scan_ptr = ~*diffeng_scan_ptr;
    diffeng_scan_ptr++;
  }
  diffeng_scan_ptr = (uint *)diffeng_mirror_buf;
  diffeng_scan_section = 0;
  diffeng_scan_offset_i32 = 0;
  return;
}
#undef diffeng_mirror_size
#undef diffeng_scan_ptr
#undef diffeng_scan_section
#undef diffeng_scan_offset_i32
#undef i

/* 004b14a4 auto */
#define section (*(int *)(frame_ + FRAME_OFF(4)))
#define total (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl diffeng_total_size(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  total = 0;
  for (section = 0; section < 0x18; section++) {
    if (section == 5) {
      total = game.num_units * 0x20 + total;
    }
    else if (section == 6) {
      total = game.num_cities * 0x58 + total;
    }
    else {
      total += *(int *)(&diffeng_sections + section * 0x18);
    }
  }
  return total + 0x1e0;
}
#undef section
#undef total

/* 004b153c auto */
#define diffeng_civ_names_section (*(int *)((u8 *)&g.d_0067a440))
#define diffeng_civ_view_section (*(int *)((u8 *)&g.d_0067a518))
#define diffeng_civs_section (*(int *)((u8 *)&g.d_0067a458))
#define diffeng_events_section (*(int *)((u8 *)&g.d_0067a638))
#define diffeng_game_section (*(int *)((u8 *)&g.d_0067a428))
#define diffeng_leaders_section (*(int *)((u8 *)&g.d_0067a4b8))
#define diffeng_scenario_section (*(int *)((u8 *)&g.d_0067a4e8))
#define diffeng_game_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a434))
#define diffeng_civ_names_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a44c))
#define diffeng_civs_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a464))
#define diffeng_leaders_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a4c4))
#define diffeng_scenario_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a4f4))
#define diffeng_civ_view_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a524))
#define diffeng_events_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a644))
#define write_pos (*(i32 (*)[2])(frame_ + FRAME_OFF(4)))
#define capacity2 (*(uint *)(frame_ + FRAME_OFF(12)))
#define buf (*(int *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl diffeng_build_civ_image(iptr out_buf)

{
  void *alloc;
  i32 result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  write_pos[0] = 0;
  capacity2 = diffeng_game_section + diffeng_leaders_section + diffeng_civs_section + diffeng_civ_names_section + diffeng_scenario_section + diffeng_civ_view_section
            + diffeng_events_section + 0x8c;
  if ((int)capacity2 < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d218, ((u8 *)&g.d_0062d218)),ADDR(0x62d1f0, ((u8 *)&g.d_0062d1f0)),0x226);
  }
  alloc = operator_new(capacity2);
  *(void **)out_buf = alloc;
  buf = *(int *)out_buf;
  if (buf == 0) {
    dbg_log(ADDR(0x62d224, ((u8 *)&g.d_0062d224)));
    result = 0;
  }
  else {
    diffeng_game_checksum_i32 = mem_checksum(diffeng_game_data,diffeng_game_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a428, ((u8 *)&g.d_0067a428)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_game_data,diffeng_game_section);
    diffeng_leaders_checksum_i32 = mem_checksum(diffeng_leaders_data,diffeng_leaders_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a4b8, ((u8 *)&g.d_0067a4b8)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_leaders_data,diffeng_leaders_section);
    diffeng_civs_checksum_i32 = mem_checksum(diffeng_civs_data,diffeng_civs_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a458, ((u8 *)&g.d_0067a458)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_civs_data,diffeng_civs_section);
    diffeng_civ_names_checksum_i32 = mem_checksum(diffeng_civ_names_data,diffeng_civ_names_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a440, ((u8 *)&g.d_0067a440)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_civ_names_data,diffeng_civ_names_section);
    diffeng_scenario_checksum_i32 = mem_checksum(diffeng_scenario_data,diffeng_scenario_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a4e8, ((u8 *)&g.d_0067a4e8)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_scenario_data,diffeng_scenario_section);
    diffeng_civ_view_checksum_i32 = mem_checksum(diffeng_civ_view_data,diffeng_civ_view_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a518, ((u8 *)&g.d_0067a518)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_civ_view_data,diffeng_civ_view_section);
    diffeng_events_checksum_i32 = mem_checksum(diffeng_events_data,diffeng_events_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a638, ((u8 *)&g.d_0067a638)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_events_data,diffeng_events_section);
    result = mem_rle_compress(out_buf,write_pos[0]);
  }
  return result;
}
#undef diffeng_civ_names_section
#undef diffeng_civ_view_section
#undef diffeng_civs_section
#undef diffeng_events_section
#undef diffeng_game_section
#undef diffeng_leaders_section
#undef diffeng_scenario_section
#undef diffeng_game_checksum_i32
#undef diffeng_civ_names_checksum_i32
#undef diffeng_civs_checksum_i32
#undef diffeng_leaders_checksum_i32
#undef diffeng_scenario_checksum_i32
#undef diffeng_civ_view_checksum_i32
#undef diffeng_events_checksum_i32
#undef write_pos
#undef capacity2
#undef buf

/* 004b187f auto */
void __cdecl diffeng_buf_append(int buf,iptr pos_ptr,int capacity,iptr src,int len)

{
  if (capacity < *(int *)pos_ptr + len) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d294, ((u8 *)&g.d_0062d294)),ADDR(0x62d26c, ((u8 *)&g.d_0062d26c)),0x20d);
  }
  crt_memcpy(*(int *)pos_ptr + buf,src,len);
  *(int *)pos_ptr = *(int *)pos_ptr + len;
  return;
}

/* 004b18e1 auto */
#define diffeng_game_section (*(int *)((u8 *)&g.d_0067a428))
#define diffeng_map_header_section (*(int *)((u8 *)&g.d_0067a530))
#define diffeng_game_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a434))
#define diffeng_map_header_checksum_i32 (*(i32 *)((u8 *)&g.d_0067a53c))
#define write_pos (*(i32 (*)[2])(frame_ + FRAME_OFF(4)))
#define capacity2 (*(uint *)(frame_ + FRAME_OFF(12)))
#define buf (*(int *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl diffeng_build_map_header_image(iptr out_buf)

{
  void *alloc;
  i32 result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  write_pos[0] = 0;
  capacity2 = diffeng_game_section + 0x28 + diffeng_map_header_section;
  alloc = operator_new(capacity2);
  *(void **)out_buf = alloc;
  buf = *(int *)out_buf;
  if (buf == 0) {
    dbg_log(ADDR(0x62d2b4, ((u8 *)&g.d_0062d2b4)));
    result = 0;
  }
  else {
    diffeng_game_checksum_i32 = mem_checksum(diffeng_game_data,diffeng_game_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a428, ((u8 *)&g.d_0067a428)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_game_data,diffeng_game_section);
    diffeng_map_header_checksum_i32 = mem_checksum(diffeng_map_header_data,diffeng_map_header_section);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,ADDR(0x67a530, ((u8 *)&g.d_0067a530)),0x14);
    diffeng_buf_append(buf,(iptr)write_pos,capacity2,diffeng_map_header_data,diffeng_map_header_section);
    result = mem_rle_compress(out_buf,write_pos[0]);
  }
  return result;
}
#undef diffeng_game_section
#undef diffeng_map_header_section
#undef diffeng_game_checksum_i32
#undef diffeng_map_header_checksum_i32
#undef write_pos
#undef capacity2
#undef buf

/* 004b1a15 auto */
#define src_copy (*(void * *)(frame_ + FRAME_OFF(4)))
#define src_end (*(int *)(frame_ + FRAME_OFF(8)))
#define dst_begin (*(i32 *)(frame_ + FRAME_OFF(12)))
#define dst_end (*(int *)(frame_ + FRAME_OFF(16)))
#define result (*(i32 *)(frame_ + FRAME_OFF(20)))
#define section (*(int *)(frame_ + FRAME_OFF(24)))
#define header (*(int (*)[5])(frame_ + FRAME_OFF(28)))
#define error_code (*(i32 *)(frame_ + FRAME_OFF(48)))
#define write_pos (*(uint *)(frame_ + FRAME_OFF(52)))
#define buf (*(int *)(frame_ + FRAME_OFF(56)))
i32 __cdecl diffeng_build_full_image(iptr out_buf)

{
  uint capacity;
  void *alloc;
  i32 checksum;
  int encoded;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  capacity = diffeng_total_size();
  if ((int)capacity < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d324, ((u8 *)&g.d_0062d324)),ADDR(0x62d2fc, ((u8 *)&g.d_0062d2fc)),0x27f);
  }
  alloc = operator_new(capacity);
  *(void **)out_buf = alloc;
  buf = *(int *)out_buf;
  if (buf == 0) {
    dbg_log(ADDR(0x62d32c, ((u8 *)&g.d_0062d32c)));
    result = 0;
  }
  else {
    write_pos = 0;
    for (section = 0; section < 0x18; section++) {
      crt_memcpy(header,&diffeng_sections + section * 0x18,0x14);
      if (section == 5) {
        header[0] = (int)game.num_units << 5;
      }
      else if (section == 6) {
        header[0] = game.num_cities * 0x58;
      }
      checksum = mem_checksum((&diffeng_section_ptrs)[section * 6],header[0]);
      *(i32 *)(&diffeng_section_checksums + section * 0x18) = checksum;
      diffeng_buf_append(buf,(iptr)&write_pos,capacity,(iptr)header,0x14);
      diffeng_buf_append(buf,(iptr)&write_pos,capacity,(&diffeng_section_ptrs)[section * 6],header[0]);
    }
    src_copy = operator_new(write_pos);
    if (src_copy == (void *)0x0) {
      dbg_log(ADDR(0x62d374, ((u8 *)&g.d_0062d374)));
      result = 0;
    }
    else {
      src_end = write_pos + (int)src_copy;
      crt_memcpy(src_copy,buf,write_pos);
      dst_begin = *(i32 *)out_buf;
      dst_end = write_pos + *(int *)out_buf;
      encoded = diffeng_rle_encode((iptr)&src_copy);
      if (encoded == 0) {
        error_code = 0xffffffff;
        result = error_code;
      }
      else {
        checksum = crt_realloc(*(i32 *)out_buf,result);
        *(i32 *)out_buf = checksum;
      }
    }
  }
  return result;
}
#undef src_copy
#undef src_end
#undef dst_begin
#undef dst_end
#undef result
#undef section
#undef header
#undef error_code
#undef write_pos
#undef buf

/* 004b1c11 auto */
#define section (*(int *)(frame_ + FRAME_OFF(4)))
#define header (*(int (*)[5])(frame_ + FRAME_OFF(8)))
#define checksum2 (*(int *)(frame_ + FRAME_OFF(28)))
#define write_pos (*(i32 (*)[2])(frame_ + FRAME_OFF(32)))
#define buf (*(int *)(frame_ + FRAME_OFF(40)))
i32 __cdecl diffeng_build_delta_image(iptr out_buf)

{
  uint capacity;
  void *alloc;
  i32 result;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  capacity = diffeng_total_size();
  if ((int)capacity < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d3e4, ((u8 *)&g.d_0062d3e4)),ADDR(0x62d3bc, ((u8 *)&g.d_0062d3bc)),0x2c6);
  }
  alloc = operator_new(capacity);
  *(void **)out_buf = alloc;
  buf = *(int *)out_buf;
  if (buf == 0) {
    dbg_log(ADDR(0x62d3ec, ((u8 *)&g.d_0062d3ec)));
    result = 0;
  }
  else {
    write_pos[0] = 0;
    for (section = 0; section < 0x18; section++) {
      crt_memcpy(header,&diffeng_sections + section * 0x18,0x14);
      if (section == 5) {
        header[0] = (int)game.num_units << 5;
      }
      else if (section == 6) {
        header[0] = game.num_cities * 0x58;
      }
      checksum2 = mem_checksum((&diffeng_section_ptrs)[section * 6],header[0]);
      if ((*(int *)(&diffeng_section_checksums + section * 0x18) != checksum2) && (header[0] != 0)) {
        *(int *)(&diffeng_section_checksums + section * 0x18) = checksum2;
        diffeng_buf_append(buf,(iptr)write_pos,capacity,(iptr)header,0x14);
        diffeng_buf_append(buf,(iptr)write_pos,capacity,(&diffeng_section_ptrs)[section * 6],header[0]);
      }
    }
    result = crt_realloc(*(i32 *)out_buf,write_pos[0]);
    *(i32 *)out_buf = result;
    if (*(int *)out_buf == 0) {
      dbg_log(ADDR(0x62d430, ((u8 *)&g.d_0062d430)));
      result = 0;
    }
    else {
      result = mem_rle_compress(out_buf,write_pos[0]);
    }
  }
  return result;
}
#undef section
#undef header
#undef checksum2
#undef write_pos
#undef buf

/* 004b1de3 auto */
#define src_begin (*(int *)(frame_ + FRAME_OFF(0)))
#define src_end (*(int *)(frame_ + FRAME_OFF(4)))
#define dst_buf (*(void * *)(frame_ + FRAME_OFF(8)))
#define dst_end (*(int *)(frame_ + FRAME_OFF(12)))
#define saved_game_options (*(u32 *)(frame_ + FRAME_OFF(20)))
#define saved_msg_options (*(u16 *)(frame_ + FRAME_OFF(24)))
#define header (*(int * *)(frame_ + FRAME_OFF(28)))
#define offset (*(int *)(frame_ + FRAME_OFF(32)))
#define total_size (*(uint *)(frame_ + FRAME_OFF(36)))
#define cursor (*(int * *)(frame_ + FRAME_OFF(40)))
void __cdecl diffeng_apply_image(int *image_buf,char compressed)

{
  int *section_id_ptr;
  int *payload;
  size_t src_size;
  int decoded;
  i32 checksum;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((image_buf == (int *)0x0) || (*image_buf == 0)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d4a0, ((u8 *)&g.d_0062d4a0)),ADDR(0x62d478, ((u8 *)&g.d_0062d478)),0x2fc);
  }
  saved_game_options = game.game_options;
  saved_msg_options = game.message_options;
  if (diffeng_section_ptrs == 0) {
    diffeng_register_blocks();
  }
  if (nm_full_gamestate_count == 0) {
    if (compressed != '\0') {
      total_size = mem_rle_decompress((iptr)image_buf);
    }
    cursor = (int *)*image_buf;
    total_size = __msize((void *)*image_buf);
  }
  else {
    src_begin = *image_buf;
    src_size = __msize((void *)*image_buf);
    src_end = src_begin + src_size;
    total_size = diffeng_rle_decoded_size((iptr)&src_begin);
    dst_buf = operator_new(total_size);
    if (dst_buf == (void *)0x0) {
      dbg_log(ADDR(0x62d4b4, ((u8 *)&g.d_0062d4b4)));
      return;
    }
    dst_end = (int)dst_buf + total_size;
    decoded = diffeng_rle_decode((iptr)&src_begin);
    if (decoded == 0) {
      dbg_log(ADDR(0x62d4fc, ((u8 *)&g.d_0062d4fc)));
      return;
    }
    operator_delete((void *)*image_buf);
    *image_buf = (int)dst_buf;
    cursor = (int *)*image_buf;
  }
  offset = 0;
  while (offset < (int)total_size) {
    header = cursor;
    payload = cursor + 5;
    offset = *cursor + offset + 0x14;
    if ((cursor[2] < 0) || (section_id_ptr = cursor + 2, cursor = payload, 0x17 < *section_id_ptr)) {
      cursor = payload;
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d554, ((u8 *)&g.d_0062d554)),ADDR(0x62d52c, ((u8 *)&g.d_0062d52c)),0x338);
    }
    crt_memcpy((&diffeng_section_ptrs)[header[2] * 6],cursor,*header);
    checksum = mem_checksum((iptr)cursor,*header);
    *(i32 *)(&diffeng_section_checksums + header[2] * 0x18) = checksum;
    cursor = (int *)((int)cursor + *header);
  }
  game.message_options = saved_msg_options;
  game.game_options = saved_game_options;
  return;
}
#undef src_begin
#undef src_end
#undef dst_buf
#undef dst_end
#undef saved_game_options
#undef saved_msg_options
#undef header
#undef offset
#undef total_size
#undef cursor

/* 004b2010 auto */
#define cursor (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl diffeng_apply_map_header_image(int *image_buf,char compressed)

{
  u32 saved_game_options;
  u16 saved_msg_options;
  int section_id;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((image_buf == (int *)0x0) || (*image_buf == 0)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d5b0, ((u8 *)&g.d_0062d5b0)),ADDR(0x62d588, ((u8 *)&g.d_0062d588)),0x34b);
  }
  saved_msg_options = game.message_options;
  saved_game_options = game.game_options;
  if (compressed != '\0') {
    mem_rle_decompress((iptr)image_buf);
  }
  cursor = *image_buf;
  map_free();
  section_id = diffeng_read_block((iptr)&cursor);
  if (section_id != 1) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d5ec, ((u8 *)&g.d_0062d5ec)),ADDR(0x62d5c4, ((u8 *)&g.d_0062d5c4)),0x35a);
  }
  section_id = diffeng_read_block((iptr)&cursor);
  if (section_id != 0xc) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d628, ((u8 *)&g.d_0062d628)),ADDR(0x62d600, ((u8 *)&g.d_0062d600)),0x35d);
  }
  game.game_options = saved_game_options;
  game.message_options = saved_msg_options;
  map_alloc();
  diffeng_register_blocks();
  diffeng_alloc_mirror();
  return;
}
#undef cursor

/* 004b2123 auto */
int __cdecl diffeng_read_block(iptr cursor_ptr)

{
  int *header;
  i32 checksum;
  
  header = *(int **)cursor_ptr;
  *(int *)cursor_ptr = *(int *)cursor_ptr + 0x14;
  if ((header[2] < 0) || (0x17 < header[2])) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d66c, ((u8 *)&g.d_0062d66c)),ADDR(0x62d644, ((u8 *)&g.d_0062d644)),0x36d);
  }
  crt_memcpy((&diffeng_section_ptrs)[header[2] * 6],*(i32 *)cursor_ptr,*header);
  checksum = mem_checksum(*(iptr *)cursor_ptr,*header);
  *(i32 *)(&diffeng_section_checksums + header[2] * 0x18) = checksum;
  *(int *)cursor_ptr = *(int *)cursor_ptr + *header;
  return header[2];
}

/* 004b21d7 auto */
#define diffeng_civ_names_section (*(i32 *)((u8 *)&g.d_0067a440))
#define diffeng_civ_view_section (*(i32 *)((u8 *)&g.d_0067a518))
#define diffeng_civs_section (*(i32 *)((u8 *)&g.d_0067a458))
#define diffeng_events_section (*(i32 *)((u8 *)&g.d_0067a638))
#define diffeng_game_section (*(i32 *)((u8 *)&g.d_0067a428))
#define diffeng_leaders_section (*(i32 *)((u8 *)&g.d_0067a4b8))
#define diffeng_map_header_section (*(i32 *)((u8 *)&g.d_0067a530))
#define diffeng_scenario_section (*(i32 *)((u8 *)&g.d_0067a4e8))
#define events_pool_base (*(iptr *)((u8 *)&g.d_0064b98c))
#define offset (*(int *)(frame_ + FRAME_OFF(4)))
#define section (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl diffeng_register_blocks(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  memblock_ensure_locked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)));
  diffeng_section_init((DiffEngSection *)&diffeng_sections,ADDR(0x62d0b8, ((u8 *)&g.d_0062d0b8)),4,0);
  diffeng_section_init((DiffEngSection *)&diffeng_game_section,ADDR(0x655ae8, ((u8 *)&game)),0x14c,1);
  diffeng_section_init((DiffEngSection *)&diffeng_civ_names_section,ADDR(0x64bcf8, ((u8 *)&civ_names)),0x790,2);
  diffeng_section_init((DiffEngSection *)&diffeng_civs_section,ADDR(0x64c6a0, ((u8 *)&civs)),0x2ca0,3);
  diffeng_section_init((DiffEngSection *)&diffeng_landmass_section,ADDR(0x666130, ((u8 *)&g.d_00666130)),0x400,4);
  diffeng_section_init((DiffEngSection *)&diffeng_units_section,ADDR(0x6560f0, ((u8 *)&units)),0x10000,5);
  diffeng_section_init((DiffEngSection *)&diffeng_cities_section,ADDR(0x64f340, ((u8 *)&cities)),0x5800,6);
  diffeng_section_init((DiffEngSection *)&diffeng_leaders_section,ADDR(0x6554f8, ((u8 *)&leaders)),0x3f0,7);
  diffeng_section_init((DiffEngSection *)&diffeng_power_graph_section,ADDR(0x655c38, ((u8 *)&g.d_00655c38)),0x4b0,8);
  diffeng_section_init((DiffEngSection *)&diffeng_scenario_section,ADDR(0x64bc60, ((u8 *)&g.d_0064bc60)),100,9);
  diffeng_section_init((DiffEngSection *)&diffeng_destroyed_civs_section,ADDR(0x655128, ((u8 *)&g.d_00655128)),0x154,10);
  diffeng_section_init((DiffEngSection *)&diffeng_civ_view_section,ADDR(0x654b40, ((u8 *)&g.d_00654b40)),0x494,0xb);
  diffeng_section_init((DiffEngSection *)&diffeng_map_header_section,ADDR(0x6d1160, ((u8 *)&map)),0x10,0xc);
  diffeng_section_init
            ((DiffEngSection *)&diffeng_map_coarse0_section,(iptr)map_coarse[0],(int)map.quarter_w * (int)map.quarter_h
             ,0xd);
  diffeng_section_init
            ((DiffEngSection *)&diffeng_map_coarse1_section,(iptr)map_coarse[1],(int)map.quarter_w * (int)map.quarter_h
             ,0xe);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known1_section,(iptr)map_known[1],(int)map.area,0xf);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known2_section,(iptr)map_known[2],(int)map.area,0x10);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known3_section,(iptr)map_known[3],(int)map.area,0x11);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known4_section,(iptr)map_known[4],(int)map.area,0x12);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known5_section,(iptr)map_known[5],(int)map.area,0x13);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known6_section,(iptr)map_known[6],(int)map.area,0x14);
  diffeng_section_init((DiffEngSection *)&diffeng_map_known7_section,(iptr)map_known[7],(int)map.area,0x15);
  diffeng_section_init((DiffEngSection *)&diffeng_map_tiles_section,(iptr)map_tiles,map.area * 6,0x16);
  diffeng_section_init((DiffEngSection *)&diffeng_events_section,events_pool_base,50000,0x17);
  offset = 0;
  for (section = 0; section < 0x17; section++) {
    *(int *)(&diffeng_section_offsets + section * 0x18) = offset;
    offset += (&diffeng_section_padded_sizes)[section * 6];
  }
  return;
}
#undef diffeng_civ_names_section
#undef diffeng_civ_view_section
#undef diffeng_civs_section
#undef diffeng_events_section
#undef diffeng_game_section
#undef diffeng_leaders_section
#undef diffeng_map_header_section
#undef diffeng_scenario_section
#undef events_pool_base
#undef offset
#undef section

/* 004b24a2 auto */
#define code (*(uint *)(frame_ + FRAME_OFF(0)))
#define total (*(int *)(frame_ + FRAME_OFF(4)))
#define src (*(ushort * *)(frame_ + FRAME_OFF(8)))
int __cdecl diffeng_rle_decoded_size(iptr stream)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  src = *(ushort **)stream;
  total = 0;
  while (src < *(ushort **)(stream + 4)) {
    code = (uint)*src;
    if (code < 0x8000) {
      src = (ushort *)((int)src + 3);
    }
    else {
      src = (ushort *)((int)src + (code & 0x7fff) + 2);
    }
    total += (code & 0x7fff);
  }
  return total;
}
#undef code
#undef total
#undef src

/* 004b251a auto */
#define src (*(ushort * *)(frame_ + FRAME_OFF(0)))
#define dst (*(void * *)(frame_ + FRAME_OFF(4)))
i32 __cdecl diffeng_rle_decode(iptr stream)

{
  ushort *payload;
  ushort run_len;
  uint decoded_size;
  i32 result;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  decoded_size = diffeng_rle_decoded_size(stream);
  if ((uint)(*(int *)(stream + 0xc) - *(int *)(stream + 8)) < decoded_size) {
    result = 0;
  }
  else {
    src = *(ushort **)stream;
    dst = *(void **)(stream + 8);
    while (src < *(ushort **)(stream + 4)) {
      run_len = *src;
      payload = src + 1;
      if (run_len < 0x7fff) {
        src = (ushort *)((int)src + 3);
        _memset(dst,(int)(short)(ushort)(byte)*payload,(uint)run_len);
      }
      else {
        run_len += 0x8000;
        crt_memcpy(dst,payload,(uint)run_len);
        src = (ushort *)((int)payload + (uint)run_len);
      }
      dst = (void *)((int)dst + (uint)run_len);
    }
    *(int *)(stream + 0x10) = (int)dst - *(int *)(stream + 8);
    result = 1;
  }
  return result;
}
#undef src
#undef dst

/* 004b263e auto */
#define scan (*(char * *)(frame_ + FRAME_OFF(4)))
#define run_start (*(char * *)(frame_ + FRAME_OFF(8)))
#define dst (*(short * *)(frame_ + FRAME_OFF(12)))
#define chunk_len (*(uptr *)(frame_ + FRAME_OFF(16)))
#define run_len (*(uint *)(frame_ + FRAME_OFF(20)))
#define out_len (*(uint *)(frame_ + FRAME_OFF(28)))
i32 __cdecl diffeng_rle_encode(iptr stream)

{
  short *code_ptr;
  uint src_len;
  uint dst_capacity;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  dst = *(short **)(stream + 8);
  run_start = *(char **)stream;
  scan = run_start + 1;
  src_len = *(int *)(stream + 4) - *(int *)stream;
  out_len = 0;
  dst_capacity = *(int *)(stream + 0xc) - *(int *)(stream + 8);
  do {
    if (*(char **)(stream + 4) <= run_start) {
      *(uint *)(stream + 0x10) = out_len;
      return 1;
    }
    for (; (scan < *(char **)(stream + 4) && (*scan == *run_start)); scan = scan + 1
        ) {
    }
    run_len = (int)scan - (int)run_start;
    if (3 < run_len) {
      while (code_ptr = dst, run_len != 0) {
        if ((dst_capacity < out_len + 2) || (src_len <= out_len + 2)) {
          return 0;
        }
        if (run_len < 0x8000) {
          *dst = (short)run_len;
          run_len = 0;
        }
        else {
          *dst = 0x7fff;
          run_len -= 0x7fff;
        }
        dst++;
        out_len += 3;
        if ((dst_capacity < out_len) || (src_len <= out_len)) {
          return 0;
        }
        *(char *)dst = *run_start;
        dst = (short *)((int)code_ptr + 3);
      }
      run_start = scan;
    }
    for (; (scan < *(char **)(stream + 4) && (scan[1] != *scan));
        scan = scan + 1) {
    }
    run_len = (int)scan - (int)run_start;
    while (run_len != 0) {
      out_len += 2;
      if ((dst_capacity < out_len) || (src_len <= out_len)) {
        return 0;
      }
      if (run_len < 0x8000) {
        *dst = (short)run_len - 0x8000;
        chunk_len = run_len;
        run_len = 0;
      }
      else {
        *dst = -1;
        chunk_len = 0x7fff;
        run_len -= 0x7fff;
      }
      dst++;
      out_len += chunk_len;
      if ((dst_capacity < out_len) || (src_len <= out_len)) {
        return 0;
      }
      crt_memcpy(dst,run_start,chunk_len);
      dst = (short *)((int)dst + chunk_len);
      run_start += chunk_len;
    }
  } while( true );
}
#undef scan
#undef run_start
#undef dst
#undef chunk_len
#undef run_len
#undef out_len

/* 004b3080 auto */
void __thiscall diffeng_section_init(DiffEngSection *this,iptr data_ptr,u32 data_size,u32 section_id)

{
  this->data_ptr = data_ptr;
  this->data_size = data_size;
  this->section_id = section_id;
  this->checksum = 0;
  this->padded_size = this->data_size;
  if ((this->data_size & 3) != 0) {
    this->padded_size = (4 - (this->data_size & 3)) + this->padded_size;
  }
  return;
}

/* 004c4280 auto */
void __cdecl game_main_entry(void)

{
  game_main();
  return;
}

/* 004ce903 auto */
#define alloc_len (*(i32 *)(frame_ + FRAME_OFF(4)))
int __cdecl events_alloc_string(char *text,iptr events,uint min_len)

{
  size_t len;
  int str;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = _strlen(text);
  if ((int)min_len < (int)(len + 1)) {
    len = _strlen(text);
    alloc_len = len + 1;
  }
  else {
    alloc_len = min_len;
  }
  str = memblock_alloc(events + 0x2f4,alloc_len);
  if (str == 0) {
    error_report(0xfffffff7,3,0,0,0);
  }
  crt_strcpy(str,text);
  return str;
}
#undef alloc_len

/* 004ce98e auto */
#define dst_event (*(uptr *)(frame_ + FRAME_OFF(0)))
#define src_event (*(iptr *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl events_copy(iptr dst_events,iptr src_events)

{
  int new_event;
  i32 str;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (src_event = *(iptr *)(src_events + 0x30c); src_event != 0; src_event = *(iptr *)(src_event + 0x1bc)) {
    new_event = events_alloc((ScenarioEvents *)dst_events);
    if (new_event == 0) {
      error_report(0xfffffff7,3,0,0,0);
    }
    crt_memcpy(new_event,src_event,0x1bc);
  }
  src_event = *(iptr *)(src_events + 0x30c);
  dst_event = *(uptr *)(dst_events + 0x30c);
  do {
    if (src_event == 0) {
      return;
    }
    if (*(int *)(src_event + 8) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 8),dst_events,0xf);
      *(i32 *)(dst_event + 8) = str;
      if (*(int *)(dst_event + 8) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x10) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x10),dst_events,0x18);
      *(i32 *)(dst_event + 0x10) = str;
      if (*(int *)(dst_event + 0x10) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x14) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x14),dst_events,0x18);
      *(i32 *)(dst_event + 0x14) = str;
      if (*(int *)(dst_event + 0x14) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x20) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x20),dst_events,0x18);
      *(i32 *)(dst_event + 0x20) = str;
      if (*(int *)(dst_event + 0x20) == 0) {
        return;
      }
    }
    for (i = 0; (i < 0x14 && (*(int *)(src_event + 0x38 + i * 4) != 0));
        i = i + 1) {
      str = events_alloc_string(*(i32 *)(src_event + 0x38 + i * 4),dst_events,1);
      *(i32 *)(dst_event + 0x38 + i * 4) = str;
      if (*(int *)(dst_event + 0x38 + i * 4) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x88) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x88),dst_events,0x18);
      *(i32 *)(dst_event + 0x88) = str;
      if (*(int *)(dst_event + 0x88) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x90) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x90),dst_events,0xf);
      *(i32 *)(dst_event + 0x90) = str;
      if (*(int *)(dst_event + 0x90) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0xc4) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0xc4),dst_events,0x18);
      *(i32 *)(dst_event + 0xc4) = str;
      if (*(int *)(dst_event + 0xc4) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0xcc) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0xcc),dst_events,0x18);
      *(i32 *)(dst_event + 0xcc) = str;
      if (*(int *)(dst_event + 0xcc) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0xd4) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0xd4),dst_events,0x18);
      *(i32 *)(dst_event + 0xd4) = str;
      if (*(int *)(dst_event + 0xd4) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0xdc) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0xdc),dst_events,0xf);
      *(i32 *)(dst_event + 0xdc) = str;
      if (*(int *)(dst_event + 0xdc) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x13c) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x13c),dst_events,0x18);
      *(i32 *)(dst_event + 0x13c) = str;
      if (*(int *)(dst_event + 0x13c) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x140) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x140),dst_events,0x18);
      *(i32 *)(dst_event + 0x140) = str;
      if (*(int *)(dst_event + 0x140) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x148) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x148),dst_events,0xf);
      *(i32 *)(dst_event + 0x148) = str;
      if (*(int *)(dst_event + 0x148) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x174) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x174),dst_events,0x18);
      *(i32 *)(dst_event + 0x174) = str;
      if (*(int *)(dst_event + 0x174) == 0) {
        return;
      }
    }
    if (*(int *)(src_event + 0x184) != 0) {
      str = events_alloc_string(*(i32 *)(src_event + 0x184),dst_events,1);
      *(i32 *)(dst_event + 0x184) = str;
      if (*(int *)(dst_event + 0x184) == 0) {
        return;
      }
    }
    src_event = *(iptr *)(src_event + 0x1bc);
    dst_event = *(uptr *)(dst_event + 0x1bc);
  } while( true );
}
#undef dst_event
#undef src_event
#undef i

/* 004cef35 auto */
#define temp_events (*(ScenarioEvents *)(frame_ + FRAME_OFF(0)))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(784)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl events_compact(void)

{
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  events_ctor(&temp_events,50000);
  eh_state = 0;
  events_reset(&temp_events,50000);
  events_copy((iptr)&temp_events,ADDR(0x64b690, ((u8 *)&g.d_0064b690)));
  events_reset((ScenarioEvents *)&scenario_events,50000);
  events_copy(ADDR(0x64b690, ((u8 *)&g.d_0064b690)),(iptr)&temp_events);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004cefc5 */ { events_dtor((DialogCore *)((iptr)&temp_events)); }
  return;
}
#undef temp_events
#undef eh_next
#undef eh_handler
#undef eh_state

/* 004cefe9 auto */
#define event (*(iptr *)(frame_ + FRAME_OFF(4)))
#define count (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl events_rename_unit_refs(char *old_name,iptr new_name)

{
  int cmp;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  count = 0;
  for (event = events_list_head; event != 0; event = *(iptr *)(event + 0x1bc)) {
    if (*(int *)(event + 8) != 0) {
      cmp = _strcmp(*(char **)(event + 8),old_name);
      if (cmp == 0) {
        _strncpy(*(char **)(event + 8),(char *)new_name,0xf);
        count++;
      }
    }
    if (*(int *)(event + 0x90) != 0) {
      cmp = _strcmp(*(char **)(event + 0x90),old_name);
      if (cmp == 0) {
        _strncpy(*(char **)(event + 0x90),(char *)new_name,0xf);
        count++;
      }
    }
    if (*(int *)(event + 0xdc) != 0) {
      cmp = _strcmp(*(char **)(event + 0xdc),old_name);
      if (cmp == 0) {
        _strncpy(*(char **)(event + 0xdc),(char *)new_name,0xf);
        count++;
      }
    }
    if (*(int *)(event + 0x148) != 0) {
      cmp = _strcmp(*(char **)(event + 0x148),old_name);
      if (cmp == 0) {
        _strncpy(*(char **)(event + 0x148),(char *)new_name,0xf);
        count++;
      }
    }
  }
  return count;
}
#undef event
#undef count

/* 004e0140 auto */
void __cdecl main_menu_global_init(void)

{
  main_menu_static_init();
  main_menu_reg_atexit();
  return;
}

/* 004e015a auto */
void __cdecl main_menu_static_init(void)

{
  menu_ctor((GameMenu *)&main_menu,0x1000);
  return;
}

/* 004e0179 auto */
void __cdecl main_menu_reg_atexit(void)

{
  _atexit(main_menu_static_dtor);
  return;
}

/* 004e0196 auto */
void __cdecl main_menu_static_dtor(void)

{
  menu_dtor((GameMenu *)&main_menu);
  return;
}

/* 004e22c9 auto */
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define player_has_quit (*(i8 *)((u8 *)&g.d_006ad685))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define saved_human_players2 (*(u8 *)(frame_ + FRAME_OFF(0)))
void __cdecl game_quit_or_retire(int retire)

{
  int confirmed;
  iptr text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((game.multiplayer < 3) || (net_host_handoff_stage == '\0')) {
    if (retire == 0) {
      confirmed = popup_game_with_sprite(ADDR(0x62ec50, ((u8 *)&g.d_0062ec50)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (confirmed == 0) {
        return;
      }
    }
    else {
      confirmed = popup_game_with_sprite(ADDR(0x62ec40, ((u8 *)&g.d_0062ec40)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (confirmed == 0) {
        return;
      }
      powergraph_show();
      if ((game.game_flags & 0x20) == 0) {
        civ_score_window_show(human_civ);
        civ_rating_window_show(human_civ);
        hall_of_fame_add_entry(human_civ);
      }
    }
    if (game.multiplayer == '\0') {
      snd_cd_stop();
      map_display_disable();
    }
    else {
      if (game.multiplayer == 1) {
        saved_human_players2 = game.human_players;
        game.human_players = hotseat_human_players;
      }
      if (2 < game.multiplayer) {
        if (mp_turn_timer_handle != 0) {
          game_timer_destroy(mp_turn_timer_handle);
          mp_turn_timer_handle = 0;
        }
        parley_wnd_close();
        chat_wnd_close();
        text = civ_get_adjective(human_civ);
        text_set_string_arg(0,text);
        text = civ_leader_title(human_civ);
        text_set_string_arg(1,text);
        text = civ_leader_name(human_civ);
        text_set_string_arg(2,text);
        text = civ_name_plural(human_civ);
        text_set_string_arg(3,text);
        if (mp_kill_civ_on_retire == 0) {
          net_send_text_args(1,0xff,4,0,0,0);
        }
        else {
          net_send_text_args(0,0xff,4,0,0,0);
        }
      }
      unit_blink_phase = 0;
      mapviews_redraw_cursor();
      if ((~(1 << ((byte)human_civ & 0x1f)) & (uint)game.human_players) == 0) {
        if (game.multiplayer < 3) {
          game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
        }
        else {
          net_send_message(0x31,0,0,human_civ,0,0,0,0,0,0);
        }
        map_display_disable();
        snd_cd_stop();
      }
      else {
        civ_eliminate(human_civ,0,0);
        if (2 < game.multiplayer) {
          map_display_disable();
        }
      }
      player_turn_active = 0;
      player_has_quit = 1;
      if (game.multiplayer == 1) {
        hotseat_human_players = game.human_players;
        game.human_players = saved_human_players2;
      }
    }
  }
  return;
}
#undef hotseat_human_players
#undef human_civ
#undef mp_kill_civ_on_retire
#undef net_host_handoff_stage
#undef player_has_quit
#undef player_turn_active
#undef unit_blink_phase
#undef saved_human_players2

/* 004fa1c0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl game_palette_global_init(void)

{
  game_palette_static_init();
  game_palette_reg_atexit();
  return;
}

/* 004fa1da auto */
void __cdecl game_palette_static_init(void)

{
  palette_init((GamePalette *)&game_palette);
  return;
}

/* 004fa1f4 auto */
void __cdecl game_palette_reg_atexit(void)

{
  _atexit(game_palette_atexit_dtor);
  return;
}

/* 004fa211 auto */
void __cdecl game_palette_atexit_dtor(void)

{
  palette_destroy((GamePalette *)&game_palette);
  return;
}

/* 004fa250 auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl events_parse_civ(iptr name2)

{
  int cmp;
  i32 result;
  char *_Str2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  cmp = __strcmpi((char *)name2,s_ANYBODY_0062f1f4);
  if (cmp == 0) {
    result = 0xfffffffe;
  }
  else {
    cmp = __strcmpi((char *)name2,s_TRIGGERATTACKER_0062f1fc);
    if (cmp == 0) {
      result = 0xfffffffd;
    }
    else {
      cmp = __strcmpi((char *)name2,s_TRIGGERDEFENDER_0062f20c);
      if (cmp == 0) {
        result = 0xfffffffc;
      }
      else {
        cmp = __strcmpi((char *)name2,s_TRIGGERRECEIVER_0062f21c);
        if (cmp == 0) {
          result = 0xfffffffc;
        }
        else {
          for (civ = 0; civ < 8; civ++) {
            _Str2 = (char *)civ_name_plural(civ);
            cmp = __strcmpi((char *)name2,_Str2);
            if (cmp == 0) {
              return civ;
            }
          }
          if (events_parse_verbose != 0) {
            _printf(s_Could_not_find__s__check_spellin_0062f22c,name2);
          }
          result = 0xffffffff;
        }
      }
    }
  }
  return result;
}
#undef civ

/* 004fa359 auto */
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl events_parse_unit_type(iptr name2)

{
  int cmp;
  i32 result;
  char *_Str2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  cmp = __strcmpi((char *)name2,s_ANYUNIT_0062f250);
  if (cmp == 0) {
    result = 0xfffffffe;
  }
  else {
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      _Str2 = (char *)label_string(unit_types[unit_type].name);
      cmp = __strcmpi((char *)name2,_Str2);
      if (cmp == 0) {
        return unit_type;
      }
    }
    if (events_parse_verbose != 0) {
      _printf(s_Could_not_find_unit__s__check_sp_0062f258,name2);
    }
    result = 0xffffffff;
  }
  return result;
}
#undef unit_type

/* 004fa47e auto */
void __thiscall events_init_string_pool(DialogCore *this,uint pool_size)

{
  memblock_free((iptr)&this[0x12].field_24);
  memblock_init((iptr)&this[0x12].field_24,0xc,pool_size);
  return;
}

/* 004fa4be auto */
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
ScenarioEvents * __thiscall events_ctor(ScenarioEvents *this,i32 pool_size)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor((Dialog *)this,0x4000);
  eh_state = 0;
  memblock_ctor((MemBlock *)(this->pad_294 + 0x60));
  this->events_pool_valid = '\0';
  this->event_list = 0;
  this->event_count = 0;
  events_reset(this,pool_size);
  return this;
}
#undef eh_next
#undef eh_handler
#undef eh_state

/* 004fa569 auto */
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall events_dtor(DialogCore *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0;
  memblock_free((iptr)&this[0x12].field_24);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004fa5b8 */ { dialog_dtor(*(Dialog **)((iptr)&this)); }
  return;
}
#undef eh_next
#undef eh_handler
#undef eh_state

/* 004fa5d9 auto */
void __thiscall events_reset(ScenarioEvents *this,i32 pool_size)

{
  this->event_list = 0;
  this->event_count = 0;
  events_init_string_pool((DialogCore *)this,pool_size);
  return;
}

/* 004fa617 auto */
#define last (*(uptr *)(frame_ + FRAME_OFF(0)))
void * __thiscall events_alloc(ScenarioEvents *this)

{
  void *_Dst;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  last = this->event_list;
  if (last != 0) {
    for (; *(int *)(last + 0x1bc) != 0; last = *(uptr *)(last + 0x1bc)) {
    }
  }
  _Dst = (void *)memblock_alloc((iptr)(this->pad_294 + 0x60),0x1c4);
  if (_Dst == (void *)0x0) {
    _Dst = (void *)0x0;
  }
  else {
    _memset(_Dst,0,0x1c4);
    if (last == 0) {
      this->event_list = (uptr)_Dst;
      *(i32 *)((int)_Dst + 0x1bc) = 0;
      *(i32 *)((int)_Dst + 0x1c0) = 0;
    }
    else {
      *(void **)(last + 0x1bc) = _Dst;
      *(uptr *)((int)_Dst + 0x1c0) = last;
      *(i32 *)((int)_Dst + 0x1bc) = 0;
    }
    this->event_count++;
  }
  return _Dst;
}
#undef last

/* 004fa707 auto */
#define path (*(i8 (*)[240])(frame_ + FRAME_OFF(4)))
i32 __thiscall events_action_play_wave(DialogCore *this,iptr event)

{
  i32 result;
  int exists;
  i8 frame_[FRAME_OFF(248)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((byte)game.game_options & 0x10) == 0) {
    result = 0;
  }
  else {
    if (*(int *)(event + 0x184) != 0) {
      crt_strcpy(path,&scenario_dir_path);
      crt_strcat(path,s__SOUND__0062f2b0);
      crt_strcat(path,*(i32 *)(event + 0x184));
      exists = file_exists((iptr)path);
      if (exists == 0) {
        crt_strcpy(path,&game_home_dir);
        crt_strcat(path,s__SOUND__0062f2b8);
        crt_strcat(path,*(i32 *)(event + 0x184));
        exists = file_exists((iptr)path);
        if (exists != 0) {
          snd_wave_play((iptr)path,0,0,0);
        }
      }
      else {
        snd_wave_play((iptr)path,0,0,0);
      }
    }
    result = 1;
  }
  return result;
}
#undef path

/* 004fa82d auto */
#define event_dont_play_wonders (*(i32 *)((u8 *)&g.d_006a9110))
i32 __thiscall events_action_dont_play_wonders(DialogCore *this,iptr event)

{
  event_dont_play_wonders = 1;
  return 1;
}
#undef event_dont_play_wonders

/* 004fa854 auto */
#define track_count (*(int *)(frame_ + FRAME_OFF(4)))
#define attempts (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_action_play_cd(DialogCore *this,iptr event)

{
  i32 result;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  attempts = 0;
  while (attempts < 10) {
    attempts++;
    track_count = snd_cd_get_track_count();
    if ((((track_count == 0x18) || (track_count == 0x12)) || (track_count == 0xc)) || (track_count == 10)) break;
    snd_cd_close();
  }
  if (((track_count == 10) || (track_count == 0x12)) || ((track_count == 0x18 || (track_count == 0xc)))) {
    if ((*(int *)(event + 0x188) < 2) || (track_count < *(int *)(event + 0x188))) {
      result = 0;
    }
    else {
      music_play_track(*(i32 *)(event + 0x188),1);
      result = 1;
    }
  }
  else {
    result = 0;
  }
  return result;
}
#undef track_count
#undef attempts

/* 004fa944 auto */
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall events_action_change_money(DialogCore *this,iptr event)

{
  i32 result;
  int new_gold;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(event + 0x178) == -3) {
    civ = *(iptr *)(event + 0x18);
  }
  else if (*(int *)(event + 0x178) == -4) {
    civ = *(iptr *)(event + 0x24);
  }
  else if (*(int *)(event + 0x178) == -4) {
    civ = *(iptr *)(event + 0x24);
  }
  else {
    civ = *(iptr *)(event + 0x178);
  }
  if ((civ < 1) || (7 < civ)) {
    result = 0;
  }
  else if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
    result = 0;
  }
  else {
    new_gold = *(int *)(event + 0x17c) + civs[civ].gold;
    if ((new_gold < 0) || (30000 < new_gold)) {
      if (*(int *)(event + 0x17c) < 0) {
        civs[civ].gold = 0;
      }
      else {
        civs[civ].gold = 30000;
      }
    }
    else {
      civs[civ].gold = new_gold;
    }
    result = 1;
  }
  return result;
}
#undef civ

/* 004faab0 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define line (*(int *)(frame_ + FRAME_OFF(4)))
#define arg_count (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_action_text(Dialog *this,iptr event)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  arg_count = 0;
  dialog_init_default(this);
  for (line = 0; line < 0x14; line++) {
    if (*(int *)(event + 0x38 + line * 4) != 0) {
      dialog_add_line
                ((DialogAddLineView *)this,*(iptr *)(event + 0x38 + line * 4),0xffffffff,0xffffffff,
                 0xffffffff,0);
      if (2 < game.multiplayer) {
        crt_strcpy(&text_string_args + arg_count * 0x104,*(i32 *)(event + 0x38 + line * 4));
        arg_count++;
      }
    }
  }
  if (autoplay_active == 0) {
    if (2 < game.multiplayer) {
      net_send_text_args(0x4f,0xff,arg_count,0,0,0);
    }
    dlg_show_modal(this,0);
  }
  return 1;
}
#undef autoplay_active
#undef line
#undef arg_count

/* 004faba6 auto */
#define civ2 (*(int *)(frame_ + FRAME_OFF(4)))
#define civ (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_action_make_aggression(DialogCore *this,iptr event)

{
  i32 result;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(event + 0xd0) == -3) {
    civ2 = *(int *)(event + 0x18);
  }
  else if (*(int *)(event + 0xd0) == -4) {
    civ2 = *(int *)(event + 0x24);
  }
  else if (*(int *)(event + 0xd0) == -4) {
    civ2 = *(int *)(event + 0x24);
  }
  else {
    civ2 = *(int *)(event + 0xd0);
  }
  if (*(int *)(event + 200) == -3) {
    civ = *(int *)(event + 0x18);
  }
  else if (*(int *)(event + 200) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else if (*(int *)(event + 200) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else {
    civ = *(int *)(event + 200);
  }
  if (((civ < 1) || (7 < civ)) ||
     ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    result = 0;
  }
  else if (((civ2 < 1) || (7 < civ2)) ||
          ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) == 0)) {
    result = 0;
  }
  else {
    result = diplo_force_war(civ2,civ);
  }
  return result;
}
#undef civ2
#undef civ

/* 004fad02 auto */
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
i32 __thiscall events_action_destroy_civ(DialogCore *this,iptr event)

{
  i32 result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(event + 0x1b0) == -3) {
    civ = *(int *)(event + 0x18);
  }
  else if (*(int *)(event + 0x1b0) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else if (*(int *)(event + 0x1b0) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else {
    civ = *(int *)(event + 0x1b0);
  }
  if (((civ < 1) || (7 < civ)) ||
     ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    result = 0;
  }
  else {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
       (human_civ == civ)) {
      game_over_reason = 4;
    }
    civ_eliminate(civ,1,1);
    result = 1;
  }
  return result;
}
#undef game_over_reason
#undef human_civ
#undef civ

/* 004fadfb auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
i32 __thiscall events_action_give_tech(DialogCore *this,iptr event)

{
  i32 result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(event + 0x1b8) == -3) {
    civ = *(int *)(event + 0x18);
  }
  else if (*(int *)(event + 0x1b8) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else if (*(int *)(event + 0x1b8) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else {
    civ = *(int *)(event + 0x1b8);
  }
  if (((civ < 1) || (7 < civ)) ||
     ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    result = 0;
  }
  else {
    civ_give_advance(civ,*(iptr *)(event + 0x1b4),0,0,0);
    result = 1;
  }
  return result;
}
#undef civ

/* 004faed4 auto */
#define loc (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(8)))
#define x2 (*(int *)(frame_ + FRAME_OFF(12)))
#define civ (*(uptr *)(frame_ + FRAME_OFF(20)))
#define city (*(iptr *)(frame_ + FRAME_OFF(24)))
i32 __thiscall events_action_create_unit(DialogCore *this,iptr event)

{
  iptr x;
  iptr y;
  i32 result;
  iptr in_bounds;
  iptr is_ocean;
  uptr owner;
  iptr unit;
  int city2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = 10000;
  y2 = 10000;
  if (*(int *)(event + 0xd8) == -3) {
    civ = *(uptr *)(event + 0x18);
  }
  else if (*(int *)(event + 0xd8) == -4) {
    civ = *(uptr *)(event + 0x24);
  }
  else if (*(int *)(event + 0xd8) == -4) {
    civ = *(uptr *)(event + 0x24);
  }
  else {
    civ = *(uptr *)(event + 0xd8);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
    result = 0;
  }
  else {
    for (loc = 0; y = y2, x = x2, loc < *(int *)(event + 0x134);
        loc = loc + 1) {
      x = *(iptr *)(event + 0xe4 + loc * 8);
      y = *(iptr *)(event + 0xe8 + loc * 8);
      in_bounds = map_in_bounds(x,y);
      if (in_bounds != 0) {
        if (unit_types[*(int *)(event + 0xe0)].domain == 2) {
          is_ocean = tile_is_ocean(x,y);
          if (is_ocean != 0) break;
          city2 = city_at(x,y);
          if ((city2 != -1) &&
             (city2 = city_at(x,y), (cities[city2].flags & 0x80) != 0)) {
            owner = tile_city_owner(x,y);
joined_r0x004fb11d:
            if (owner == civ) break;
          }
        }
        else {
          city2 = tile_is_ocean(x,y);
          if (((city2 == 0) || (unit_types[*(int *)(event + 0xe0)].domain == 1)) &&
             ((city2 = city_at(x,y), city2 == -1 ||
              (owner = tile_city_owner(x,y), owner == civ)))) {
            city2 = tile_unit_owner(x,y);
            if (city2 != -1) {
              owner = tile_unit_owner(x,y);
              goto joined_r0x004fb11d;
            }
            break;
          }
        }
      }
    }
    x2 = x;
    y2 = y;
    if ((x2 == 10000) && (y2 == 10000)) {
      result = 0;
    }
    else {
      unit = unit_create(*(iptr *)(event + 0xe0),civ,x2,y2);
      if (unit == -1) {
        result = 0;
      }
      else {
        if (*(int *)(event + 0x138) != 0) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        units[unit].home_city = -1;
        if (*(int *)(event + 0x13c) != 0) {
          for (city = 0; city < game.num_cities; city++) {
            if ((cities[city].id != 0) &&
               (city2 = __strcmpi(cities[city].name,*(char **)(event + 0x13c)), city2 == 0)) {
              if ((int)cities[city].owner == civ) {
                units[unit].home_city = (i8)city;
              }
              break;
            }
          }
        }
        result = 1;
      }
    }
  }
  return result;
}
#undef loc
#undef y2
#undef x2
#undef civ
#undef city

/* 004fb29f auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define moved (*(int *)(frame_ + FRAME_OFF(8)))
#define i (*(iptr *)(frame_ + FRAME_OFF(12)))
#define civ (*(int *)(frame_ + FRAME_OFF(24)))
#define rect_y (*(int (*)[4])(frame_ + FRAME_OFF(28)))
#define rect_x (*(int (*)[4])(frame_ + FRAME_OFF(44)))
int __thiscall events_action_move_unit(DialogCore *this,iptr event)

{
  int x;
  int y;
  int in_bounds;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(event + 0x8c) == -3) {
    civ = *(int *)(event + 0x18);
  }
  else if (*(int *)(event + 0x8c) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else if (*(int *)(event + 0x8c) == -4) {
    civ = *(int *)(event + 0x24);
  }
  else {
    civ = *(int *)(event + 0x8c);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
    moved = 0;
  }
  else if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    for (i = 0; i < 4; i++) {
      rect_x[i] = *(int *)(event + 0x9c + i * 8);
      rect_y[i] = *(int *)(event + 0xa0 + i * 8);
    }
    moved = 0;
    unit = (iptr)game.num_units;
    do {
      do {
        do {
          unit--;
          if (unit < 0) {
            return moved;
          }
        } while ((((units[unit].id == 0) ||
                  ((((*(int *)(event + 0x94) != unit && (*(int *)(event + 0x94) != -2)) ||
                    (units[unit].owner != civ)) ||
                   (('b' < (char)unit_types[units[unit].type].attack ||
                    (units[unit].orders == 16)))))) || (3 < units[unit].orders)) ||
                (units[unit].orders == 3));
        x = (int)units[unit].x;
        y = (int)units[unit].y;
        in_bounds = map_in_bounds(x,y);
      } while ((((in_bounds == 0) || (x < rect_x[0])) ||
               ((rect_x[1] < x ||
                (((rect_x[2] < x || (x < rect_x[3])) || (y < rect_y[0])))))) ||
              (((y < rect_y[1] || (rect_y[2] < y)) || (rect_y[3] < y))));
      units[unit].orders = 11;
      units[unit].ai_task = '7';
      units[unit].goto_x = (i16)*(i32 *)(event + 0xbc);
      units[unit].goto_y = (i16)*(i32 *)(event + 0xc0);
      moved++;
    } while ((moved < *(int *)(event + 0x98)) || (*(int *)(event + 0x98) == -2));
  }
  else {
    moved = 0;
  }
  return moved;
}
#undef unit
#undef moved
#undef i
#undef civ
#undef rect_y
#undef rect_x

/* 004fb5b2 auto */
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define i (*(iptr *)(frame_ + FRAME_OFF(12)))
#define y2 (*(int *)(frame_ + FRAME_OFF(16)))
#define changed (*(int *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(24)))
#define rect_y (*(int (*)[4])(frame_ + FRAME_OFF(36)))
#define rect_x (*(int (*)[4])(frame_ + FRAME_OFF(52)))
int __thiscall events_action_change_terrain(DialogCore *this,iptr event)

{
  bool has_city;
  iptr in_bounds;
  uptr city2;
  iptr in_bounds2;
  i8 *terrain;
  int tile;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  changed = 0;
  for (i = 0; i < 4; i++) {
    rect_x[i] = *(int *)(event + 400 + i * 8);
    rect_y[i] = *(int *)(event + 0x194 + i * 8);
  }
  for (x2 = rect_x[0]; x2 <= rect_x[1]; x2++) {
    for (y2 = rect_y[0]; y2 <= rect_y[3]; y2++) {
      in_bounds = map_in_bounds(x2,y2);
      if (in_bounds != 0) {
        city2 = city_at(x2,y2);
        if (-1 < (int)city2) {
          city_delete(city2,0);
        }
        for (unit = tile_first_unit(x2,y2); -1 < unit;
            unit = unit_next_in_stack(unit)) {
          unit_delete(unit,1);
        }
      }
    }
  }
  for (x2 = rect_x[0]; x2 <= rect_x[1]; x2++) {
    for (y2 = rect_y[0]; y2 <= rect_y[3]; y2++) {
      in_bounds2 = map_in_bounds(x2,y2);
      if (in_bounds2 != 0) {
        terrain = (i8 *)tile_at(x2,y2);
        *terrain = *(i8 *)(event + 0x18c);
        tile = tile_at(x2,y2);
        *(i8 *)(tile + 1) = 0;
        tile = tile_at(x2,y2);
        *(i8 *)(tile + 2) = 0;
        tile = tile_at(x2,y2);
        *(i8 *)(tile + 3) = 0;
        for (civ = 0; civ < 8; civ++) {
          tile_update_known(x2,y2,civ);
        }
        map_redraw_tile_all_views(x2,y2);
        changed++;
      }
    }
  }
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      city_refresh_area_tiles(city);
    }
  }
  for (civ = 0; civ < 8; civ++) {
    has_city = false;
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        has_city = true;
      }
    }
    if (!has_city) {
      unit = (iptr)game.num_units;
      while (unit = unit - 1, -1 < unit) {
        if ((units[unit].id != 0) && (units[unit].owner == civ)) {
          unit_delete(unit,1);
        }
      }
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
         (human_civ == civ)) {
        game_over_reason = 4;
      }
      for (x2 = 0; x2 < map.width; x2++) {
        for (y2 = 0; y2 < map.height; y2++) {
          tile = tile_at(x2,y2);
          *(byte *)(tile + 4) = *(byte *)(tile + 4) & ~(byte)(1 << ((byte)civ & 0x1f));
        }
      }
      civ_create(civ);
      map_redraw_all_views(human_civ,1);
    }
  }
  return changed;
}
#undef game_over_reason
#undef human_civ
#undef civ
#undef unit
#undef city
#undef i
#undef y2
#undef changed
#undef x2
#undef rect_y
#undef rect_x

/* 004fba0c auto */
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_turn(ScenarioEvents *this,int turn)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if ((*event == 4) && ((event[0xb] == -1 || (event[0xb] == turn)))) {
        triggered = 1;
        event_run_actions((Dialog *)this,(iptr)event);
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef triggered
#undef event

/* 004fba9c auto */
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_turn_interval(ScenarioEvents *this,int turn)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if ((*event == 8) && ((event[0xb] == 0 || (turn % event[0xb] == 0)))) {
        triggered = 1;
        event_run_actions((Dialog *)this,(iptr)event);
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef triggered
#undef event

/* 004fbb2f auto */
#define roll (*(int *)(frame_ + FRAME_OFF(0)))
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_random_turn(ScenarioEvents *this,i32 turn)

{
  int rnd;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if (*event == 0x40) {
        if (event[0xc] < 2) {
          roll = 1;
        }
        else {
          rnd = _rand();
          roll = rnd % event[0xc] + 1;
        }
        if (event[0xc] == roll) {
          triggered = 1;
          event_run_actions((Dialog *)this,(iptr)event);
        }
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef roll
#undef triggered
#undef event

/* 004fbbdd auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_received_tech(ScenarioEvents *this)

{
  int has_tech;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if (*event == 0x100) {
        if (event[9] == -2) {
          for (civ = 0; civ < 8; civ++) {
            if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
               (has_tech = civ_has_advance(civ,event[0xd]), has_tech != 0)) {
              event[9] = civ;
              triggered = 1;
              event_run_actions((Dialog *)this,(iptr)event);
            }
          }
        }
        else if ((((0 < event[9]) || (event[9] < 8)) &&
                 ((1 << (*(byte *)(event + 9) & 0x1f) & (uint)game.civs_alive) != 0)) &&
                (has_tech = civ_has_advance(event[9],event[0xd]), has_tech != 0)) {
          triggered = 1;
          event_run_actions((Dialog *)this,(iptr)event);
        }
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef civ
#undef triggered
#undef event

/* 004fbd2b auto */
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_scenario_loaded(ScenarioEvents *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if (*event == 0x20) {
        triggered = 1;
        event_run_actions((Dialog *)this,(iptr)event);
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef triggered
#undef event

/* 004fbd9d auto */
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall
events_check_unit_killed(ScenarioEvents *this,int unit_type,int attacker_civ,int defender_civ)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if ((((*event == 1) && (event[3] == unit_type)) &&
          ((event[9] == defender_civ || (event[9] == -2)))) &&
         ((event[6] == attacker_civ || (event[6] == -2)))) {
        triggered = 1;
        if (event[6] == -2) {
          event[6] = attacker_civ;
        }
        if (event[9] == -2) {
          event[9] = defender_civ;
        }
        event_run_actions((Dialog *)this,(iptr)event);
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef triggered
#undef event

/* 004fbe84 auto */
i32 __thiscall events_check_negotiation(ScenarioEvents *this,iptr talker_civ,iptr listener_civ)

{
  int *event;
  bool talker_match;
  bool listener_match;
  
  event = (int *)this->event_list;
  do {
    if (event == (int *)0x0) {
      return 1;
    }
    if (*event == 0x10) {
      if (((event[6] == talker_civ) || (event[6] == -2)) &&
         ((((1 << (*(byte *)(event + 6) & 0x1f) & (uint)game.human_players) != 0 &&
           ((event[7] == 1 || (event[7] == 4)))) ||
          (((1 << (*(byte *)(event + 6) & 0x1f) & (uint)game.human_players) == 0 &&
           ((event[7] == 2 || (event[7] == 4)))))))) {
        talker_match = true;
      }
      else {
        talker_match = false;
      }
      if (((event[9] == listener_civ) || (event[9] == -2)) &&
         (((((uint)game.human_players & 1 << (*(byte *)(event + 9) & 0x1f)) != 0 &&
           ((event[10] == 1 || (event[10] == 4)))) ||
          ((((uint)game.human_players & 1 << (*(byte *)(event + 9) & 0x1f)) == 0 &&
           ((event[10] == 2 || (event[10] == 4)))))))) {
        listener_match = true;
      }
      else {
        listener_match = false;
      }
      if ((talker_match) && (listener_match)) {
LAB_004fc1a5:
        if (event[0x60] == 0x1000) {
          event_run_actions((Dialog *)this,(iptr)event);
          return 0;
        }
        event_run_actions((Dialog *)this,(iptr)event);
        return 1;
      }
      if ((2 < game.multiplayer) &&
         (((1 << ((byte)talker_civ & 0x1f) & (uint)game.human_players) != 0 &&
          ((1 << ((byte)listener_civ & 0x1f) & (uint)game.human_players) != 0)))) {
        if (((event[6] == listener_civ) || (event[6] == -2)) &&
           ((((1 << (*(byte *)(event + 6) & 0x1f) & (uint)game.human_players) != 0 &&
             ((event[7] == 1 || (event[7] == 4)))) ||
            (((1 << (*(byte *)(event + 6) & 0x1f) & (uint)game.human_players) == 0 &&
             ((event[7] == 2 || (event[7] == 4)))))))) {
          talker_match = true;
        }
        else {
          talker_match = false;
        }
        if (((event[9] == talker_civ) || (event[9] == -2)) &&
           (((((uint)game.human_players & 1 << (*(byte *)(event + 9) & 0x1f)) != 0 &&
             ((event[10] == 1 || (event[10] == 4)))) ||
            ((((uint)game.human_players & 1 << (*(byte *)(event + 9) & 0x1f)) == 0 &&
             ((event[10] == 2 || (event[10] == 4)))))))) {
          listener_match = true;
        }
        else {
          listener_match = false;
        }
        if ((talker_match) && (listener_match)) goto LAB_004fc1a5;
      }
    }
    event = (int *)event[0x6f];
  } while( true );
}

/* 004fc20d auto */
#define event (*(int * *)(frame_ + FRAME_OFF(4)))
i32 __thiscall events_check_no_schism(ScenarioEvents *this,iptr civ)

{
  bool triggered;
  i32 result;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = false;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    result = 1;
  }
  else {
    do {
      if ((*event == 0x80) && ((event[9] == civ || (event[9] == -2)))) {
        event_run_actions((Dialog *)this,(iptr)event);
        triggered = true;
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
    if (triggered) {
      result = 0;
    }
    else {
      result = 1;
    }
  }
  return result;
}
#undef event

/* 004fc2bb auto */
#define triggered (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall
events_check_city_taken(ScenarioEvents *this,iptr city_name,iptr attacker_civ,iptr defender_civ)

{
  int cmp;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  triggered = 0;
  event = (int *)this->event_list;
  if (event == (int *)0x0) {
    triggered = 0;
  }
  else {
    do {
      if ((((*event == 2) && (cmp = __strcmpi((char *)event[4],(char *)city_name), cmp == 0))
          && ((event[6] == attacker_civ || (event[6] == -2)))) &&
         ((event[9] == defender_civ || (event[9] == -2)))) {
        if (event[6] == -2) {
          event[6] = attacker_civ;
        }
        if (event[9] == -2) {
          event[9] = defender_civ;
        }
        triggered = 1;
        event_run_actions((Dialog *)this,(iptr)event);
      }
      event = (int *)event[0x6f];
    } while (event != (int *)0x0);
  }
  return triggered;
}
#undef triggered
#undef event

/* 004fc3ae auto */
i32 __thiscall event_run_actions(Dialog *this,iptr event)

{
  i32 result;
  
  if (((*(byte *)(event + 4) & 0x40) == 0) || ((*(byte *)(event + 5) & 0x20) == 0)) {
    if ((*(byte *)(event + 4) & 0x10) != 0) {
      events_action_play_wave((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 0x80) != 0) {
      events_action_play_cd((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 4) != 0) {
      events_action_create_unit((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 2) != 0) {
      events_action_move_unit((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 5) & 2) != 0) {
      events_action_change_terrain((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 0x20) != 0) {
      events_action_make_aggression((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 8) != 0) {
      events_action_change_money((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 5) & 4) != 0) {
      events_action_destroy_civ((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 5) & 8) != 0) {
      events_action_give_tech((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 1) != 0) {
      events_action_text(this,event);
    }
    if ((*(byte *)(event + 5) & 1) != 0) {
      events_action_dont_play_wonders((DialogCore *)this,event);
    }
    if ((*(byte *)(event + 4) & 0x40) != 0) {
      *(uint *)(event + 4) = *(uint *)(event + 4) | 0x2000;
    }
    result = 1;
  }
  else {
    result = 0;
  }
  return result;
}

/* 004fc516 auto */
#define have_owner (*(int *)(frame_ + FRAME_OFF(4)))
#define have_homecity (*(int *)(frame_ + FRAME_OFF(8)))
#define have_city (*(int *)(frame_ + FRAME_OFF(16)))
#define have_unit (*(int *)(frame_ + FRAME_OFF(20)))
#define have_move_count (*(int *)(frame_ + FRAME_OFF(24)))
#define have_tech (*(int *)(frame_ + FRAME_OFF(28)))
#define event (*(int * *)(frame_ + FRAME_OFF(32)))
#define have_listener_type (*(int *)(frame_ + FRAME_OFF(36)))
#define have_unit_killed (*(int *)(frame_ + FRAME_OFF(40)))
#define have_moveto (*(int *)(frame_ + FRAME_OFF(44)))
#define have_receiver (*(int *)(frame_ + FRAME_OFF(48)))
#define have_veteran (*(int *)(frame_ + FRAME_OFF(52)))
#define have_tech_receiver (*(int *)(frame_ + FRAME_OFF(56)))
#define state (*(uint *)(frame_ + FRAME_OFF(60)))
#define have_tech_id (*(int *)(frame_ + FRAME_OFF(64)))
#define failed (*(int *)(frame_ + FRAME_OFF(68)))
#define line (*(char * *)(frame_ + FRAME_OFF(76)))
#define i (*(iptr *)(frame_ + FRAME_OFF(80)))
#define have_defender (*(int *)(frame_ + FRAME_OFF(84)))
#define have_talker_type (*(int *)(frame_ + FRAME_OFF(92)))
#define have_destroy_whom (*(int *)(frame_ + FRAME_OFF(96)))
#define loc_count (*(int *)(frame_ + FRAME_OFF(100)))
#define parsed_civ (*(int *)(frame_ + FRAME_OFF(104)))
#define have_terrain (*(int *)(frame_ + FRAME_OFF(108)))
#define have_amount (*(int *)(frame_ + FRAME_OFF(112)))
#define have_who (*(int *)(frame_ + FRAME_OFF(116)))
#define have_attacker (*(int *)(frame_ + FRAME_OFF(124)))
#define have_whom (*(int *)(frame_ + FRAME_OFF(128)))
int __thiscall events_parse_file(ScenarioEvents *this,iptr filename,iptr section)

{
  int cmp;
  size_t len;
  char *arg;
  int str_buf;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  failed = 1;
  state = 1;
  events_parse_verbose = 0;
  cmp = text_open_section(filename,section);
  if (cmp == 0) {
    do {
      line = (char *)text_read_line(1);
      if (line == (char *)0x0) {
        state = 10;
      }
      else if (*line == '@') {
        line++;
        cmp = __strcmpi(line,&events_kw_if_str);
        if (cmp == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_found___creating_new_event_s_0062f2c4);
          }
          event = (int *)events_alloc(this);
          if (event == (int *)0x0) {
            if (events_parse_verbose != 0) {
              _printf(s_Failed_to_create_new_event_struc_0062f2f0);
            }
            goto LAB_004ff6f7;
          }
          if (events_parse_verbose != 0) {
            _printf(s_New_event_structure_created_0062f318);
          }
          have_city = 0;
          have_defender = 0;
          have_attacker = 0;
          have_unit_killed = 0;
          have_terrain = 0;
          have_moveto = 0;
          have_unit = 0;
          have_owner = 0;
          have_move_count = 0;
          have_amount = 0;
          have_receiver = 0;
          have_destroy_whom = 0;
          have_whom = 0;
          have_who = 0;
          have_tech = 0;
          have_listener_type = 0;
          have_talker_type = 0;
          have_veteran = 0;
          have_homecity = 0;
          have_tech_receiver = 0;
          have_tech_id = 0;
          state = 2;
        }
        else if (state != 6) {
          cmp = __strcmpi(line,&events_kw_then_str);
          if (cmp == 0) {
            if (events_parse_verbose != 0) {
              _printf(s__THEN_found_0062f340);
            }
            state = 3;
          }
          else {
            cmp = __strcmpi(line,s_ENDIF_0062f350);
            if (cmp == 0) {
              if (events_parse_verbose != 0) {
                _printf(s__ENDIF_found_0062f358);
              }
              state = 5;
            }
            else {
              cmp = __strcmpi(line,s_DEBUG_0062f368);
              if (cmp == 0) {
                events_parse_verbose = 1;
                _printf(s_Debugging_filename___s_0062f370,filename);
              }
              else {
                cmp = __strcmpi(line,s_ENDEVENTS_0062f38c);
                if (cmp == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s__ENDEVENTS_found_0062f398);
                  }
                  state = 10;
                }
              }
            }
          }
        }
      }
      else if (state == 2) {
        cmp = __strcmpi(line,s_UNITKILLED_0062f3ac);
        if (cmp == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_UNITKILLED_found_looking_for_0062f3b8);
          }
          while (((have_unit_killed == 0 || (have_defender == 0)) || (have_attacker == 0))) {
            line = (char *)text_read_line(1);
            if (line == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062f3f8);
              }
              goto LAB_004ff6f7;
            }
            if (*line == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_UNITKILLED_statement_0062f410);
              }
              goto LAB_004ff6f7;
            }
            cmp = __strnicmp(line,s_unit__0062f430,5);
            if (cmp == 0) {
              arg = line + 5;
              cmp = events_parse_unit_type((iptr)arg);
              if ((cmp == -1) || (cmp == -2)) {
                if (events_parse_verbose != 0) {
                  _printf(s_found_unit__s__but__s_is_not_val_0062f450,arg,arg);
                }
              }
              else {
                len = _strlen(arg);
                str_buf = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                event[2] = str_buf;
                if (event[2] == 0) goto LAB_004ff6f7;
                crt_strcpy(event[2],arg);
                event[3] = cmp;
                if (events_parse_verbose != 0) {
                  _printf(s_found_unit__s__id__d__0062f438,arg,cmp);
                }
                have_unit_killed = 1;
              }
            }
            else {
              cmp = __strnicmp(line,s_attacker__0062f474,9);
              if (cmp == 0) {
                arg = line + 9;
                parsed_civ = events_parse_civ((iptr)arg);
                if (parsed_civ == -1) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_attacker__s__but__s_is_not_0062f4a0,arg,arg);
                  }
                }
                else {
                  len = _strlen(arg);
                  cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                  event[5] = cmp;
                  if (event[5] == 0) goto LAB_004ff6f7;
                  crt_strcpy(event[5],arg);
                  event[6] = parsed_civ;
                  if (events_parse_verbose != 0) {
                    _printf(s_found_attacker__s__king_id__d__0062f480,arg,parsed_civ);
                  }
                  have_attacker = 1;
                }
              }
              else {
                cmp = __strnicmp(line,s_defender__0062f4c8,9);
                if (cmp == 0) {
                  arg = line + 9;
                  parsed_civ = events_parse_civ((iptr)arg);
                  if (parsed_civ == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_defender__s__but__s_is_not_0062f4f4,arg,arg);
                    }
                  }
                  else {
                    len = _strlen(arg);
                    cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                    event[8] = cmp;
                    if (event[8] == 0) goto LAB_004ff6f7;
                    crt_strcpy(event[8],arg);
                    event[9] = parsed_civ;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_defender__s__king_id__d__0062f4d4,arg,parsed_civ);
                    }
                    have_defender = 1;
                  }
                }
              }
            }
          }
          *event = 1;
        }
        cmp = __strcmpi(line,s_NEGOTIATION_0062f51c);
        if (cmp == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_NEGOTIATION_found_looking_fo_0062f528);
          }
          while (((have_defender == 0 || (have_attacker == 0)) || ((have_talker_type == 0 || (have_listener_type == 0))))) {
            line = (char *)text_read_line(1);
            if (line == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062f578);
              }
              goto LAB_004ff6f7;
            }
            if (*line == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_NEGOTIATION_statement_0062f590);
              }
              goto LAB_004ff6f7;
            }
            cmp = __strnicmp(line,s_talker__0062f5b0,7);
            if (cmp == 0) {
              arg = line + 7;
              parsed_civ = events_parse_civ((iptr)arg);
              if (parsed_civ == -1) {
                if (events_parse_verbose != 0) {
                  _printf(s_found_talker__s__but__s_is_not_v_0062f5d8,arg,arg);
                }
              }
              else {
                len = _strlen(arg);
                cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                event[5] = cmp;
                if (event[5] == 0) goto LAB_004ff6f7;
                crt_strcpy(event[5],arg);
                event[6] = parsed_civ;
                if (events_parse_verbose != 0) {
                  _printf(s_found_talker__s__king_id__d__0062f5b8,arg,parsed_civ);
                }
                have_attacker = 1;
              }
            }
            else {
              cmp = __strnicmp(line,s_talkertype__0062f600,0xb);
              if (cmp == 0) {
                arg = line + 0xb;
                cmp = __strcmpi(arg,s_HUMAN_0062f60c);
                if (cmp == 0) {
                  event[7] = 1;
                  have_talker_type = 1;
                }
                else {
                  cmp = __strcmpi(arg,s_COMPUTER_0062f614);
                  if (cmp == 0) {
                    event[7] = 2;
                    have_talker_type = 1;
                  }
                  else {
                    cmp = __strcmpi(arg,s_HUMANORCOMPUTER_0062f620);
                    if (cmp == 0) {
                      event[7] = 4;
                      have_talker_type = 1;
                    }
                  }
                }
                if (events_parse_verbose != 0) {
                  if (have_talker_type == 0) {
                    _printf(s_found_talkertype__s__but__s_is_n_0062f648,arg,arg);
                  }
                  else {
                    _printf(s_found_talkertype__s_0062f630,arg);
                  }
                }
              }
              else {
                cmp = __strnicmp(line,s_listener__0062f674,9);
                if (cmp == 0) {
                  arg = line + 9;
                  parsed_civ = events_parse_civ((iptr)arg);
                  if (parsed_civ == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_listener__s__but__s_is_not_0062f6a0,arg,arg);
                    }
                  }
                  else {
                    len = _strlen(arg);
                    cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                    event[8] = cmp;
                    if (event[8] == 0) goto LAB_004ff6f7;
                    crt_strcpy(event[8],arg);
                    event[9] = parsed_civ;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_listener__s__king_id__d__0062f680,arg,parsed_civ);
                    }
                    have_defender = 1;
                  }
                }
                else {
                  cmp = __strnicmp(line,s_listenertype__0062f6c8,0xd);
                  if (cmp == 0) {
                    arg = line + 0xd;
                    cmp = __strcmpi(arg,s_HUMAN_0062f6d8);
                    if (cmp == 0) {
                      event[10] = 1;
                      have_listener_type = 1;
                    }
                    else {
                      cmp = __strcmpi(arg,s_COMPUTER_0062f6e0);
                      if (cmp == 0) {
                        event[10] = 2;
                        have_listener_type = 1;
                      }
                      else {
                        cmp = __strcmpi(arg,s_HUMANORCOMPUTER_0062f6ec);
                        if (cmp == 0) {
                          event[10] = 4;
                          have_listener_type = 1;
                        }
                      }
                    }
                    if (events_parse_verbose != 0) {
                      if (have_talker_type == 0) {
                        _printf(s_found_listenertype__s__but__s_is_0062f714,arg,arg);
                      }
                      else {
                        _printf(s_found_listenertype__s_0062f6fc,arg);
                      }
                    }
                  }
                }
              }
            }
          }
          *event = 0x10;
          event[0x60] = 0x1000;
        }
        cmp = __strcmpi(line,s_NOSCHISM_0062f740);
        if (cmp == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_NOSCHISM_found_looking_for_w_0062f74c);
          }
          while (have_defender == 0) {
            arg = (char *)text_read_line(1);
            if (arg == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062f774);
              }
              goto LAB_004ff6f7;
            }
            if (*arg == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_NOSCHISM_statement_0062f78c);
              }
              goto LAB_004ff6f7;
            }
            cmp = __strnicmp(arg,s_defender__0062f7a8,9);
            if (cmp == 0) {
              arg += 9;
              parsed_civ = events_parse_civ((iptr)arg);
              if (parsed_civ == -1) {
                if (events_parse_verbose != 0) {
                  _printf(s_found_defender__s__but__s_is_not_0062f7d4,arg,arg);
                }
              }
              else {
                len = _strlen(arg);
                cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                event[8] = cmp;
                if (event[8] == 0) goto LAB_004ff6f7;
                crt_strcpy(event[8],arg);
                event[9] = parsed_civ;
                if (events_parse_verbose != 0) {
                  _printf(s_found_defender__s__king_id__d__0062f7b4,arg,parsed_civ);
                }
                have_defender = 1;
              }
            }
          }
          *event = 0x80;
        }
        else {
          cmp = __strcmpi(line,s_RECEIVEDTECHNOLOGY_0062f7fc);
          if (cmp == 0) {
            if (events_parse_verbose != 0) {
              _printf(s__IF_RECEIVEDTECHNOLOGY_found_loo_0062f810);
            }
            while ((have_tech == 0 || (have_defender == 0))) {
              arg = (char *)text_read_line(1);
              if (arg == (char *)0x0) {
                if (events_parse_verbose != 0) {
                  _printf(s_Got_early_end_of_file__0062f850);
                }
                goto LAB_004ff6f7;
              }
              if (*arg == '@') {
                if (events_parse_verbose != 0) {
                  _printf(s_Illegal_RECEIVEDTECHNOLOGY_state_0062f868);
                }
                goto LAB_004ff6f7;
              }
              cmp = __strnicmp(arg,s_receiver__0062f890,9);
              if (cmp == 0) {
                arg += 9;
                cmp = events_parse_civ((iptr)arg);
                if (cmp == -1) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_receiver__s__but__s_is_not_0062f8bc,arg,arg);
                  }
                }
                else {
                  len = _strlen(arg);
                  cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                  event[8] = cmp;
                  if (event[8] == 0) goto LAB_004ff6f7;
                  crt_strcpy(event[8],arg);
                  cmp = events_parse_civ((iptr)arg);
                  event[9] = cmp;
                  if (events_parse_verbose != 0) {
                    _printf(s_found_receiver__s__king_id__d__0062f89c,arg,parsed_civ);
                  }
                  have_defender = 1;
                }
              }
              else {
                cmp = __strnicmp(arg,s_technology__0062f8e4,0xb);
                if (cmp == 0) {
                  arg += 0xb;
                  if ((*arg < '0') || ('9' < *arg)) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_technology__s__but__s_is_n_0062f918,arg,arg);
                    }
                  }
                  else {
                    cmp = str_parse_int_prefixed((iptr)arg);
                    event[0xd] = cmp;
                    have_tech = 1;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_technology__s__technology_i_0062f8f0,arg,event[0xd]);
                    }
                  }
                }
              }
            }
            *event = 0x100;
          }
          else {
            cmp = __strcmpi(line,s_CITYTAKEN_0062f944);
            if (cmp == 0) {
              if (events_parse_verbose != 0) {
                _printf(s__IF_CITYTAKEN_found_looking_for_c_0062f950);
              }
              while (((have_city == 0 || (have_attacker == 0)) || (have_defender == 0))) {
                arg = (char *)text_read_line(1);
                if (arg == (char *)0x0) {
                  if (events_parse_verbose != 0) {
                    _printf(s_Got_early_end_of_file__0062f98c);
                  }
                  goto LAB_004ff6f7;
                }
                if (*arg == '@') {
                  if (events_parse_verbose != 0) {
                    _printf(s_Illegal_CITYTAKEN_statement_0062f9a4);
                  }
                  goto LAB_004ff6f7;
                }
                cmp = __strnicmp(arg,s_attacker__0062f9c4,9);
                if (cmp == 0) {
                  arg += 9;
                  cmp = events_parse_civ((iptr)arg);
                  if (cmp == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_attacker__s__but__s_is_not_0062f9f0,arg,arg);
                    }
                  }
                  else {
                    len = _strlen(arg);
                    cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                    event[5] = cmp;
                    if (event[5] == 0) goto LAB_004ff6f7;
                    crt_strcpy(event[5],arg);
                    cmp = events_parse_civ((iptr)arg);
                    event[6] = cmp;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_attacker__s__king_id__d__0062f9d0,arg,parsed_civ);
                    }
                    have_attacker = 1;
                  }
                }
                else {
                  cmp = __strnicmp(arg,s_defender__0062fa18,9);
                  if (cmp == 0) {
                    arg += 9;
                    parsed_civ = events_parse_civ((iptr)arg);
                    if (parsed_civ == -1) {
                      if (events_parse_verbose != 0) {
                        _printf(s_found_defender__s__but__s_is_not_0062fa44,arg,arg);
                      }
                    }
                    else {
                      len = _strlen(arg);
                      cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                      event[8] = cmp;
                      if (event[8] == 0) goto LAB_004ff6f7;
                      crt_strcpy(event[8],arg);
                      event[9] = parsed_civ;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_defender__s__king_id__d__0062fa24,arg,parsed_civ);
                      }
                      have_defender = 1;
                    }
                  }
                  else {
                    cmp = __strnicmp(arg,s_city__0062fa6c,5);
                    if (cmp == 0) {
                      arg += 5;
                      len = _strlen(arg);
                      cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                      event[4] = cmp;
                      if (event[4] == 0) goto LAB_004ff6f7;
                      crt_strcpy(event[4],arg);
                      if (events_parse_verbose != 0) {
                        _printf(s_found_city__s_0062fa74,arg,parsed_civ);
                      }
                      have_city = 1;
                    }
                  }
                }
              }
              *event = 2;
            }
            else {
              cmp = __strcmpi(line,&events_kw_turn_str);
              if (cmp == 0) {
                if (events_parse_verbose != 0) {
                  _printf(s__IF_TURN_found_looking_for_turn__0062fa8c);
                }
                do {
                  do {
                    arg = (char *)text_read_line(1);
                    if (arg == (char *)0x0) {
                      if (events_parse_verbose != 0) {
                        _printf(s_Got_early_end_of_file__0062fab0);
                      }
                      goto LAB_004ff6f7;
                    }
                    if (*arg == '@') {
                      if (events_parse_verbose != 0) {
                        _printf(s_Illegal_TURN_statement_0062fac8);
                      }
                      goto LAB_004ff6f7;
                    }
                    cmp = __strnicmp(arg,s_turn__0062fae0,5);
                  } while (cmp != 0);
                  arg += 5;
                  cmp = __strcmpi(arg,s_EVERY_0062fae8);
                  if (cmp == 0) {
                    event[0xb] = -1;
                    *event = 4;
                  }
                  else if (((('/' < *arg) && (*arg < ':')) || (*arg == '-')) ||
                          (*arg == '+')) {
                    cmp = str_parse_int_prefixed((iptr)arg);
                    event[0xb] = cmp;
                    *event = 4;
                  }
                  if (events_parse_verbose != 0) {
                    if (*event == 4) {
                      _printf(s_found_turn__s_0062faf0,arg);
                    }
                    else {
                      _printf(s_found_turn__s__but__s_is_not_val_0062fb00,arg,arg);
                    }
                  }
                } while (*event != 4);
              }
              else {
                cmp = __strcmpi(line,s_TURNINTERVAL_0062fb24);
                if (cmp == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s__IF_TURNINTERVAL_found_looking_f_0062fb34);
                  }
                  do {
                    arg = (char *)text_read_line(1);
                    if (arg == (char *)0x0) {
                      if (events_parse_verbose != 0) {
                        _printf(s_Got_early_end_of_file__0062fb64);
                      }
                      goto LAB_004ff6f7;
                    }
                    if (*arg == '@') {
                      if (events_parse_verbose != 0) {
                        _printf(s_Illegal_TURNINTERVAL_statement_0062fb7c);
                      }
                      goto LAB_004ff6f7;
                    }
                    cmp = __strnicmp(arg,s_interval__0062fb9c,9);
                    if (cmp == 0) {
                      arg += 9;
                      if ((((*arg < '0') || ('9' < *arg)) && (*arg != '-')) &&
                         (*arg != '+')) {
                        if (events_parse_verbose != 0) {
                          _printf(s_found_interval__s__but__s_is_not_0062fbbc,arg,arg);
                        }
                      }
                      else {
                        cmp = str_parse_int_prefixed((iptr)arg);
                        event[0xb] = cmp;
                        if (events_parse_verbose != 0) {
                          _printf(s_found_interval__s_0062fba8,arg);
                        }
                        *event = 8;
                      }
                    }
                  } while (*event != 8);
                }
                else {
                  cmp = __strcmpi(line,s_RANDOMTURN_0062fbe4);
                  if (cmp == 0) {
                    if (events_parse_verbose != 0) {
                      _printf(s__IF_RANDOMTURN_found_looking_for_0062fbf0);
                    }
                    do {
                      arg = (char *)text_read_line(1);
                      if (arg == (char *)0x0) {
                        if (events_parse_verbose != 0) {
                          _printf(s_Got_early_end_of_file__0062fc20);
                        }
                        goto LAB_004ff6f7;
                      }
                      if (*arg == '@') {
                        if (events_parse_verbose != 0) {
                          _printf(s_Illegal_RANDOMTURN_statement_0062fc38);
                        }
                        goto LAB_004ff6f7;
                      }
                      cmp = __strnicmp(arg,s_denominator__0062fc58,0xc);
                      if (cmp == 0) {
                        arg += 0xc;
                        if ((*arg < '0') || ('9' < *arg)) {
                          if (events_parse_verbose != 0) {
                            _printf(s_found_denominator__s__but__s_is_n_0062fcac,arg,arg);
                          }
                        }
                        else {
                          cmp = str_parse_int_prefixed((iptr)arg);
                          event[0xc] = cmp;
                          if ((event[0xc] < 1) || (1000 < event[0xc])) {
                            _printf(s_found_denominator__s__but__s_is_n_0062fc68,arg,arg);
                            goto LAB_004ff6f7;
                          }
                          if (events_parse_verbose != 0) {
                            _printf(s_found_denominator__s_0062fc94,arg);
                          }
                          *event = 0x40;
                        }
                      }
                    } while (*event != 0x40);
                  }
                  else {
                    cmp = __strcmpi(line,s_SCENARIOLOADED_0062fcd8);
                    if (cmp == 0) {
                      if (events_parse_verbose != 0) {
                        _printf(s__IF_SCENARIOLOADED_0062fce8);
                      }
                      *event = 0x20;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (state == 3) {
        cmp = __strcmpi(line,&events_kw_text_str);
        if (cmp == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__THEN_TEXT_found_looking_for_END_0062fd08);
          }
          i = 0;
          line = (char *)text_read_line(1);
          if (line == (char *)0x0) goto LAB_004ff6f7;
          while (cmp = __strcmpi(line,s_ENDTEXT_0062fd30), cmp != 0) {
            if (i != 0x14) {
              len = _strlen(line);
              cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
              event[i + 0xe] = cmp;
              if (event[i + 0xe] == 0) goto LAB_004ff6f7;
              crt_strcpy(event[i + 0xe],line);
              i++;
            }
            line = (char *)text_read_line(1);
            if (line == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062fd38);
              }
              goto LAB_004ff6f7;
            }
            if (*line == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_TEXT_statement_0062fd50);
              }
              goto LAB_004ff6f7;
            }
          }
          if (events_parse_verbose != 0) {
            _printf(s_found_ENDTEXT_0062fd68);
          }
          event[1] = event[1] | 1;
        }
        else {
          cmp = __strcmpi(line,s_CHANGETERRAIN_0062fd78);
          if (cmp == 0) {
            if (events_parse_verbose != 0) {
              _printf(s__THEN_CHANGETERRAIN_found_lookin_0062fd88);
            }
            loc_count = 0;
            while ((have_terrain == 0 || (loc_count != 4))) {
              arg = (char *)text_read_line(1);
              if (arg == (char *)0x0) {
                if (events_parse_verbose != 0) {
                  _printf(s_Got_early_end_of_file__0062fdc8);
                }
                goto LAB_004ff6f7;
              }
              if (*arg == '@') {
                if (events_parse_verbose != 0) {
                  _printf(s_Illegal_CHANGETERRAIN_statement_0062fde0);
                }
                goto LAB_004ff6f7;
              }
              cmp = __strnicmp(arg,s_terraintype__0062fe04,0xc);
              if (cmp == 0) {
                arg += 0xc;
                if ((*arg < '0') || ('9' < *arg)) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_terraintype__s__but__s_is_n_0062fe3c,arg,arg);
                  }
                }
                else {
                  cmp = str_parse_int_prefixed((iptr)arg);
                  if ((-1 < cmp) || (cmp < 0xb)) {
                    event[99] = cmp;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_terraintype__s__terrainid__0062fe14,arg,cmp);
                    }
                    have_terrain = 1;
                  }
                }
              }
              else {
                cmp = __strcmpi(arg,s_maprect_0062fe68);
                if (cmp == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_maprect_0062fe70);
                  }
                  cmp = text_read_line(1);
                  if (cmp == 0) {
                    if (events_parse_verbose != 0) {
                      _printf(s_Got_early_end_of_file__0062fe80);
                    }
                    goto LAB_004ff6f7;
                  }
                  for (i = 0; i < 4; i++) {
                    cmp = text_next_int();
                    event[i * 2 + 100] = cmp;
                    cmp = text_next_int();
                    event[i * 2 + 0x65] = cmp;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_location__d___d___d_0062fe98,loc_count,
                              event[i * 2 + 100],event[i * 2 + 0x65]);
                    }
                    loc_count++;
                  }
                }
              }
            }
            event[1] = event[1] | 0x200;
          }
          else {
            cmp = __strcmpi(line,s_CREATEUNIT_0062feb4);
            if (cmp == 0) {
              if (events_parse_verbose != 0) {
                _printf(s__THEN_CREATEUNIT_found_looking_f_0062fec0);
              }
              loc_count = 0;
LAB_004fe0af:
              if (((have_unit == 0) || (have_owner == 0)) ||
                 ((have_homecity == 0 || ((have_veteran == 0 || (loc_count == 0)))))) {
                arg = (char *)text_read_line(1);
                if (arg == (char *)0x0) {
                  if (events_parse_verbose != 0) {
                    _printf(s_Got_early_end_of_file__0062ff1c);
                  }
                  goto LAB_004ff6f7;
                }
                if (*arg == '@') {
                  if (events_parse_verbose != 0) {
                    _printf(s_Illegal_CREATEUNIT_statement_0062ff34);
                  }
                  goto LAB_004ff6f7;
                }
                cmp = __strnicmp(arg,s_unit__0062ff54,5);
                if (cmp == 0) {
                  arg += 5;
                  cmp = events_parse_unit_type((iptr)arg);
                  if (cmp == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_unit__s__but__s_is_not_val_0062ff78,arg,arg);
                    }
                  }
                  else {
                    len = _strlen(arg);
                    str_buf = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                    event[0x37] = str_buf;
                    if (event[0x37] == 0) goto LAB_004ff6f7;
                    crt_strcpy(event[0x37],arg);
                    event[0x38] = cmp;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_unit__s__unit_id__d__0062ff5c,arg,cmp);
                    }
                    have_unit = 1;
                  }
                }
                else {
                  cmp = __strnicmp(arg,s_owner__0062ff9c,6);
                  if (cmp == 0) {
                    arg += 6;
                    parsed_civ = events_parse_civ((iptr)arg);
                    if (parsed_civ == -1) {
                      if (events_parse_verbose != 0) {
                        _printf(s_found_owner__s__but__s_is_not_va_0062ffc4,arg,arg);
                      }
                    }
                    else {
                      len = _strlen(arg);
                      cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                      event[0x35] = cmp;
                      if (event[0x35] == 0) goto LAB_004ff6f7;
                      crt_strcpy(event[0x35],arg);
                      event[0x36] = parsed_civ;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_owner__s__king_id__d__0062ffa4,arg,parsed_civ);
                      }
                      have_owner = 1;
                    }
                  }
                  else {
                    cmp = __strnicmp(arg,s_veteran__0062ffec,8);
                    if (cmp == 0) {
                      arg += 8;
                      cmp = __strcmpi(arg,&events_bool_yes_str);
                      if ((cmp == 0) || (cmp = __strcmpi(arg,&events_bool_true_str), cmp == 0)) {
                        event[0x4e] = 1;
                        have_veteran = 1;
                      }
                      else {
                        cmp = __strcmpi(arg,&events_bool_no_str);
                        if ((cmp == 0) || (cmp = __strcmpi(arg,s_false_00630008), cmp == 0)
                           ) {
                          event[0x4e] = 0;
                          have_veteran = 1;
                        }
                        else if (events_parse_verbose != 0) {
                          _printf(s_found_veteran__s__but__s_is_not_v_00630010,arg,arg);
                        }
                      }
                    }
                    else {
                      cmp = __strnicmp(arg,s_homecity__00630038,9);
                      if (cmp == 0) {
                        arg += 9;
                        len = _strlen(arg);
                        cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                        event[0x4f] = cmp;
                        if (event[0x4f] == 0) goto LAB_004ff6f7;
                        crt_strcpy(event[0x4f],arg);
                        if (events_parse_verbose != 0) {
                          _printf(s_found_homecity__s_00630044,arg);
                        }
                        have_homecity = 1;
                      }
                      else {
                        cmp = __strcmpi(arg,s_locations_00630058);
                        if (cmp == 0) {
                          if (events_parse_verbose != 0) {
                            _printf(s_found_locations_00630064);
                          }
                          for (i = 0; i < 10; i++) {
                            arg = (char *)text_read_line(1);
                            if (arg == (char *)0x0) {
                              if (events_parse_verbose != 0) {
                                _printf(s_Got_early_end_of_file__00630078);
                              }
                              goto LAB_004ff6f7;
                            }
                            if ((((*arg < '0') || ('9' < *arg)) && (*arg != '-')) &&
                               (*arg != '+')) {
                              cmp = __strcmpi(arg,s_endlocations_006300ac);
                              if (cmp == 0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_endlocations_006300bc,arg,arg);
                                }
                                break;
                              }
                            }
                            else {
                              cmp = text_next_int();
                              event[i * 2 + 0x39] = cmp;
                              cmp = text_next_int();
                              event[i * 2 + 0x3a] = cmp;
                              if (events_parse_verbose != 0) {
                                _printf(s_found_location__d___d___d_00630090,loc_count,
                                        event[i * 2 + 0x39],event[i * 2 + 0x3a])
                                ;
                              }
                              loc_count++;
                            }
                          }
                        }
                      }
                    }
                  }
                }
                goto LAB_004fe0af;
              }
              event[0x4d] = loc_count;
              event[1] = event[1] | 4;
            }
            else {
              cmp = __strcmpi(line,s_CHANGEMONEY_006300d0);
              if (cmp == 0) {
                if (events_parse_verbose != 0) {
                  _printf(s__THEN_CHANGEMONEY_found_looking_f_006300dc);
                }
                while ((have_receiver == 0 || (have_amount == 0))) {
                  arg = (char *)text_read_line(1);
                  if (arg == (char *)0x0) {
                    if (events_parse_verbose != 0) {
                      _printf(s_Got_early_end_of_file__00630114);
                    }
                    goto LAB_004ff6f7;
                  }
                  if (*arg == '@') {
                    if (events_parse_verbose != 0) {
                      _printf(s_Illegal_CHANGEMONEY_statement_0063012c);
                    }
                    goto LAB_004ff6f7;
                  }
                  cmp = __strnicmp(arg,s_receiver__0063014c,9);
                  if (cmp == 0) {
                    arg += 9;
                    parsed_civ = events_parse_civ((iptr)arg);
                    if (parsed_civ == -1) {
                      if (events_parse_verbose != 0) {
                        _printf(s_found_receiver__s__but__s_is_not_00630178,arg,arg);
                      }
                    }
                    else {
                      len = _strlen(arg);
                      cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                      event[0x5d] = cmp;
                      if (event[0x5d] == 0) goto LAB_004ff6f7;
                      crt_strcpy(event[0x5d],arg);
                      event[0x5e] = parsed_civ;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_receiver__s__king_id__d__00630158,arg,parsed_civ);
                      }
                      have_receiver = 1;
                    }
                  }
                  else {
                    cmp = __strnicmp(arg,s_amount__006301a0,7);
                    if ((cmp == 0) &&
                       ((((arg = arg + 7, '/' < *arg && (*arg < ':')) ||
                         (*arg == '-')) || (*arg == '+')))) {
                      cmp = str_parse_int_prefixed((iptr)arg);
                      event[0x5f] = cmp;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_amount__s__integer__d__006301a8,arg,event[0x5f]);
                      }
                      have_amount = 1;
                    }
                  }
                }
                event[1] = event[1] | 8;
              }
              else {
                cmp = __strcmpi(line,s_JUSTONCE_006301c8);
                if (cmp == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s__THEN_JUSTONCE_found_not_looking_006301d4);
                  }
                  event[1] = event[1] | 0x40;
                }
                else {
                  cmp = __strcmpi(line,s_DONTPLAYWONDERS_00630210);
                  if (cmp == 0) {
                    if (events_parse_verbose != 0) {
                      _printf(s__THEN_DONTPLAYWONDERS_found_not_l_00630220);
                    }
                    event[1] = event[1] | 0x100;
                  }
                  else {
                    cmp = __strcmpi(line,s_MAKEAGGRESSION_00630264);
                    if (cmp == 0) {
                      if (events_parse_verbose != 0) {
                        _printf(s__THEN_MAKEAGGRESSION_found_looki_00630274);
                      }
                      while ((have_who == 0 || (have_whom == 0))) {
                        arg = (char *)text_read_line(1);
                        if (arg == (char *)0x0) {
                          if (events_parse_verbose != 0) {
                            _printf(s_Got_early_end_of_file__006302a8);
                          }
                          goto LAB_004ff6f7;
                        }
                        if (*arg == '@') {
                          if (events_parse_verbose != 0) {
                            _printf(s_Illegal_MAKEAGGRESSION_statement_006302c0);
                          }
                          goto LAB_004ff6f7;
                        }
                        cmp = __strnicmp(arg,&events_who_prefix_str,4);
                        if (cmp == 0) {
                          arg += 4;
                          parsed_civ = events_parse_civ((iptr)arg);
                          if (parsed_civ == -1) {
                            if (events_parse_verbose != 0) {
                              _printf(s_found_who__s__but__s_is_not_vali_00630308,arg,arg);
                            }
                          }
                          else {
                            len = _strlen(arg);
                            cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                            event[0x33] = cmp;
                            if (event[0x33] == 0) goto LAB_004ff6f7;
                            crt_strcpy(event[0x33],arg);
                            event[0x34] = parsed_civ;
                            if (events_parse_verbose != 0) {
                              _printf(s_found_who__s__king_id__d__006302ec,arg,parsed_civ);
                            }
                            have_who = 1;
                          }
                        }
                        else {
                          cmp = __strnicmp(arg,s_whom__0063032c,5);
                          if (cmp == 0) {
                            arg += 5;
                            parsed_civ = events_parse_civ((iptr)arg);
                            if (parsed_civ == -1) {
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__but__s_is_not_val_00630350,arg,arg);
                              }
                            }
                            else {
                              len = _strlen(arg);
                              cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                              event[0x31] = cmp;
                              if (event[0x31] == 0) goto LAB_004ff6f7;
                              crt_strcpy(event[0x31],arg);
                              event[0x32] = parsed_civ;
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__king_id__d__00630334,arg,parsed_civ);
                              }
                              have_whom = 1;
                            }
                          }
                        }
                      }
                      event[1] = event[1] | 0x20;
                    }
                    else {
                      cmp = __strcmpi(line,s_DESTROYACIVILIZATION_00630374);
                      if (cmp == 0) {
                        if (events_parse_verbose != 0) {
                          _printf(s__THEN_DESTROYACIVILIZATION_found_0063038c);
                        }
                        while (have_destroy_whom == 0) {
                          arg = (char *)text_read_line(1);
                          if (arg == (char *)0x0) {
                            if (events_parse_verbose != 0) {
                              _printf(s_Got_early_end_of_file__006303c4);
                            }
                            goto LAB_004ff6f7;
                          }
                          if (*arg == '@') {
                            if (events_parse_verbose != 0) {
                              _printf(s_Illegal_DESTROYACIVILIZATION_sta_006303dc);
                            }
                            goto LAB_004ff6f7;
                          }
                          cmp = __strnicmp(arg,s_whom__00630404,5);
                          if (cmp == 0) {
                            arg += 5;
                            parsed_civ = events_parse_civ((iptr)arg);
                            if (parsed_civ == -1) {
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__but__s_is_not_val_00630428,arg,arg);
                              }
                            }
                            else {
                              event[0x6c] = parsed_civ;
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__king_id__d__0063040c,arg,parsed_civ);
                              }
                              have_destroy_whom = 1;
                            }
                          }
                        }
                        event[1] = event[1] | 0x400;
                      }
                      else {
                        cmp = __strcmpi(line,s_GIVETECHNOLOGY_0063044c);
                        if (cmp == 0) {
                          if (events_parse_verbose != 0) {
                            _printf(s__THEN_GIVETECHNOLOGY_found_looki_0063045c);
                          }
                          while ((have_tech_id == 0 || (have_tech_receiver == 0))) {
                            arg = (char *)text_read_line(1);
                            if (arg == (char *)0x0) {
                              if (events_parse_verbose != 0) {
                                _printf(s_Got_early_end_of_file__0063048c);
                              }
                              goto LAB_004ff6f7;
                            }
                            if (*arg == '@') {
                              if (events_parse_verbose != 0) {
                                _printf(s_Illegal_GIVETECHNOLOGY_statement_006304a4);
                              }
                              goto LAB_004ff6f7;
                            }
                            cmp = __strnicmp(arg,s_receiver__006304c8,9);
                            if (cmp == 0) {
                              arg += 9;
                              parsed_civ = events_parse_civ((iptr)arg);
                              if (parsed_civ == -1) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_receiver__s__but__s_is_not_006304f4,arg,arg)
                                  ;
                                }
                              }
                              else {
                                event[0x6e] = parsed_civ;
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_receiver__s__king_id__d__006304d4,arg,parsed_civ)
                                  ;
                                }
                                have_tech_receiver = 1;
                              }
                            }
                            else {
                              cmp = __strnicmp(arg,s_technology__0063051c,0xb);
                              if (((cmp == 0) && (arg = arg + 0xb, '/' < *arg)) &&
                                 (*arg < ':')) {
                                cmp = str_parse_int_prefixed((iptr)arg);
                                event[0x6d] = cmp;
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_technology__s__integer__d__00630528,arg,
                                          event[0x6d]);
                                }
                                have_tech_id = 1;
                              }
                            }
                          }
                          event[1] = event[1] | 0x800;
                        }
                        else {
                          cmp = __strcmpi(line,s_MOVEUNIT_0063054c);
                          if (cmp == 0) {
                            if (events_parse_verbose != 0) {
                              _printf(s__THEN_MOVEUNIT_found_looking_for_00630558);
                            }
                            loc_count = 0;
                            while ((((have_unit == 0 || (have_owner == 0)) || (loc_count != 4)) ||
                                   ((have_moveto == 0 || (have_move_count == 0))))) {
                              arg = (char *)text_read_line(1);
                              if (arg == (char *)0x0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_Got_early_end_of_file__006305a8);
                                }
                                goto LAB_004ff6f7;
                              }
                              if (*arg == '@') {
                                if (events_parse_verbose != 0) {
                                  _printf(s_Illegal_MOVEUNIT_statement_006305c0);
                                }
                                goto LAB_004ff6f7;
                              }
                              cmp = __strnicmp(arg,s_unit__006305dc,5);
                              if (cmp == 0) {
                                arg += 5;
                                cmp = events_parse_unit_type((iptr)arg);
                                if (cmp == -1) {
                                  if (events_parse_verbose != 0) {
                                    _printf(s_found_unit__s__but__s_is_not_val_00630600,arg,
                                            arg);
                                  }
                                }
                                else {
                                  len = _strlen(arg);
                                  str_buf = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1)
                                  ;
                                  event[0x24] = str_buf;
                                  if (event[0x24] == 0) goto LAB_004ff6f7;
                                  crt_strcpy(event[0x24],arg);
                                  event[0x25] = cmp;
                                  if (events_parse_verbose != 0) {
                                    _printf(s_found_unit__s__unit_id__d__006305e4,arg,cmp);
                                  }
                                  have_unit = 1;
                                }
                              }
                              else {
                                cmp = __strnicmp(arg,s_owner__00630624,6);
                                if (cmp == 0) {
                                  arg += 6;
                                  parsed_civ = events_parse_civ((iptr)arg);
                                  if (parsed_civ == -1) {
                                    if (events_parse_verbose != 0) {
                                      _printf(s_found_owner__s__but__s_is_not_va_0063064c,arg,
                                              arg);
                                    }
                                  }
                                  else {
                                    len = _strlen(arg);
                                    cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),
                                                               len + 1);
                                    event[0x22] = cmp;
                                    if (event[0x22] == 0) goto LAB_004ff6f7;
                                    crt_strcpy(event[0x22],arg);
                                    event[0x23] = parsed_civ;
                                    if (events_parse_verbose != 0) {
                                      _printf(s_found_owner__s__king_id__d__0063062c,arg,parsed_civ
                                             );
                                    }
                                    have_owner = 1;
                                  }
                                }
                                else {
                                  cmp = __strcmpi(arg,s_maprect_00630674);
                                  if (cmp == 0) {
                                    if (events_parse_verbose != 0) {
                                      _printf(s_found_maprect_0063067c);
                                    }
                                    cmp = text_read_line(1);
                                    if (cmp == 0) {
                                      if (events_parse_verbose != 0) {
                                        _printf(s_Got_early_end_of_file__0063068c);
                                      }
                                      goto LAB_004ff6f7;
                                    }
                                    for (i = 0; i < 4; i++) {
                                      cmp = text_next_int();
                                      event[i * 2 + 0x27] = cmp;
                                      cmp = text_next_int();
                                      event[i * 2 + 0x28] = cmp;
                                      if (events_parse_verbose != 0) {
                                        _printf(s_found_location__d___d___d_006306a4,loc_count,
                                                event[i * 2 + 0x27],
                                                event[i * 2 + 0x28]);
                                      }
                                      loc_count++;
                                    }
                                  }
                                  else {
                                    cmp = __strcmpi(arg,s_moveto_006306c0);
                                    if (cmp == 0) {
                                      if (events_parse_verbose != 0) {
                                        _printf(s_found_moveto_006306c8);
                                      }
                                      arg = (char *)text_read_line(1);
                                      if (arg == (char *)0x0) {
                                        if (events_parse_verbose != 0) {
                                          _printf(s_Got_early_end_of_file__006306d8);
                                        }
                                        goto LAB_004ff6f7;
                                      }
                                      if (((('/' < *arg) && (*arg < ':')) || (*arg == '-'))
                                         || (*arg == '+')) {
                                        cmp = text_next_int();
                                        event[0x2f] = cmp;
                                        cmp = text_next_int();
                                        event[0x30] = cmp;
                                        if (events_parse_verbose != 0) {
                                          _printf(s_found_moveto___d___d_006306f0,event[0x2f],
                                                  event[0x30]);
                                        }
                                        have_moveto = 1;
                                      }
                                    }
                                    else {
                                      cmp = __strnicmp(arg,s_numbertomove__00630708,0xd);
                                      if (cmp == 0) {
                                        arg += 0xd;
                                        if ((*arg < '0') || ('9' < *arg)) {
                                          cmp = __strcmpi(arg,&events_numbertomove_all_str);
                                          if (cmp == 0) {
                                            event[0x26] = -2;
                                            if (events_parse_verbose != 0) {
                                              _printf(s_found_numbertomove__s_00630740,arg);
                                            }
                                            have_move_count = 1;
                                          }
                                          else if (events_parse_verbose != 0) {
                                            _printf(s_found_numbertomove__s__but__s_is_00630758,
                                                    arg,arg);
                                          }
                                        }
                                        else {
                                          cmp = str_parse_int_prefixed((iptr)arg);
                                          event[0x26] = cmp;
                                          if (events_parse_verbose != 0) {
                                            _printf(s_found_numbertomove__s__integer___00630718,
                                                    arg,event[0x26]);
                                          }
                                          have_move_count = 1;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                            event[1] = event[1] | 2;
                          }
                          else {
                            cmp = __strcmpi(line,s_PLAYCDTRACK_00630784);
                            if (cmp == 0) {
                              if (events_parse_verbose != 0) {
                                _printf(s__THEN_PLAYCDTRACK_found__looking_00630790);
                              }
                              cmp = text_read_line(1);
                              if (cmp == 0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_Got_early_end_of_file__006307c4);
                                }
                                goto LAB_004ff6f7;
                              }
                              cmp = text_next_int();
                              event[0x62] = cmp;
                              if (0 < event[0x62]) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_cd_track__d_006307dc,event[0x62]);
                                }
                                event[1] = event[1] | 0x80;
                              }
                            }
                            else {
                              cmp = __strcmpi(line,s_PLAYWAVEFILE_006307f0);
                              if (cmp == 0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s__THEN_PLAYWAVEFILE_found__lookin_00630800);
                                }
                                arg = (char *)text_read_line(1);
                                if (arg == (char *)0x0) {
                                  if (events_parse_verbose != 0) {
                                    _printf(s_Got_early_end_of_file__00630834);
                                  }
                                  goto LAB_004ff6f7;
                                }
                                len = _strlen(arg);
                                cmp = memblock_alloc((iptr)(this->pad_294 + 0x60),len + 1);
                                event[0x61] = cmp;
                                if (event[0x61] == 0) goto LAB_004ff6f7;
                                crt_strcpy(event[0x61],arg);
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_wave_file_name__s_0063084c,event[0x61]);
                                }
                                event[1] = event[1] | 0x10;
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
      }
    } while (state < 10);
    failed = 0;
  }
LAB_004ff6f7:
  if (failed != 0) {
    __chdir(&game_home_dir);
    popup_game(ADDR(0x630868, ((u8 *)&g.d_00630868)));
    __chdir(&scenario_dir_path);
  }
  return failed;
}
#undef have_owner
#undef have_homecity
#undef have_city
#undef have_unit
#undef have_move_count
#undef have_tech
#undef event
#undef have_listener_type
#undef have_unit_killed
#undef have_moveto
#undef have_receiver
#undef have_veteran
#undef have_tech_receiver
#undef state
#undef have_tech_id
#undef failed
#undef line
#undef i
#undef have_defender
#undef have_talker_type
#undef have_destroy_whom
#undef loc_count
#undef parsed_civ
#undef have_terrain
#undef have_amount
#undef have_who
#undef have_attacker
#undef have_whom

/* 0051d9a0 auto */
#define net_adapter_index (*(UINT *)((u8 *)&g.d_006ad2fc))
#define net_max_players (*(UINT *)((u8 *)&g.d_006c3164))
#define net_timeout_seconds (*(UINT *)((u8 *)&g.d_006ad8b8))
#define net_xd_adapter_index (*(UINT *)((u8 *)&g.d_006c8fbc))
#define prefs_multiplayer_type (*(short *)((u8 *)&g.d_0066653a))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define choice (*(int *)(frame_ + FRAME_OFF(4)))
#define max_players (*(UINT *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(768)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl setup_choose_multiplayer_type(void)

{
  UINT UVar1;
  UINT UVar2;
  int status;
  i32 result;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  UVar2 = GetPrivateProfileIntA
                    (s_Civilization_Gold_00631f08,s_NetTimeOut_00631efc,-1,s_CIV_INI_00631ef4);
  if (UVar2 == 0xffffffff) {
    WritePrivateProfileStringA
              (s_Civilization_Gold_00631f34,s_NetTimeOut_00631f28,&net_ini_timeout_default_str,s_CIV_INI_00631f1c);
    net_timeout_seconds = 0x1e;
    UVar2 = net_timeout_seconds;
  }
  net_timeout_seconds = UVar2;
  UVar2 = GetPrivateProfileIntA
                    (s_Civilization_Gold_00631f58,s_Adapter_00631f50,-1,s_CIV_INI_00631f48);
  UVar1 = UVar2;
  if (UVar2 == 0xffffffff) {
    WritePrivateProfileStringA
              (s_Civilization_Gold_00631f80,s_Adapter_00631f78,&net_ini_adapter_default_str,s_CIV_INI_00631f6c);
    net_xd_adapter_index = 0;
    net_adapter_index = 0;
    UVar2 = net_adapter_index;
    UVar1 = net_xd_adapter_index;
  }
LAB_0051daa8:
  net_xd_adapter_index = UVar1;
  net_adapter_index = UVar2;
  net_max_players = 7;
  max_players = GetPrivateProfileIntA
                        (s_Civilization_Gold_00631fa8,s_MaxPlayers_00631f9c,-1,s_CIV_INI_00631f94);
  if (4 < (int)max_players) {
    if (7 < (int)max_players) {
      max_players = 7;
    }
    net_max_players = max_players;
    WritePrivateProfileStringA
              (s_Civilization_Gold_00631fd4,s_MaxPlayers_00631fc8,&net_ini_maxplayers_clear_str,s_CIV_INI_00631fbc);
  }
  game.multiplayer = '\0';
  game.civs_alive = '\0';
  game.human_players = '\0';
  crt_strcpy(&scenario_dir_path,&game_home_dir);
  scenario_events_loaded = 0;
  passwords_reset();
  if (net_lobby_launch_mode == -1) {
    setup_show_side_picture(7,1);
    dlg_load_game_section(&dialog2,ADDR(0x631fe8, ((u8 *)&g.d_00631fe8)),1);
    dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_multiplayer_type);
    status = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
    result = setup_next_dialog_x(1);
    dialog_set_position((DialogCore *)&dialog2,result,status);
    choice = dlg_show_modal(&dialog2,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
    if (choice < 0) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0051dd72 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      result = 1;
      goto LAB_0051dd88;
    }
    prefs_multiplayer_type = (short)choice;
  }
  else {
    choice = 2;
  }
  if ((choice < 0) || (3 < choice)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x632020, ((u8 *)&g.d_00632020)),ADDR(0x631ff4, ((u8 *)&g.d_00631ff4)),0x66);
  }
  switch(choice) {
  case 0:
    status = setup_hotseat_game();
    break;
  case 1:
    status = setup_network_game(1);
    break;
  case 2:
    status = setup_network_game(0);
    if (status == 0) goto switchD_0051dd3a_default;
    UVar2 = net_adapter_index;
    UVar1 = net_xd_adapter_index;
    if (net_lobby_launch_mode != -1) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0051dd72 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      result = 1;
LAB_0051dd88:
      return result;
    }
    goto LAB_0051daa8;
  case 3:
    net_max_players = 2;
    status = setup_network_game(4);
    break;
  default:
    goto switchD_0051dd3a_default;
  }
  UVar2 = net_adapter_index;
  UVar1 = net_xd_adapter_index;
  if (status == 0) {
switchD_0051dd3a_default:
    eh_state = 0xffffffff;
    /* inlined unwind funclet 0051dd72 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    result = 0;
    goto LAB_0051dd88;
  }
  goto LAB_0051daa8;
}
#undef net_adapter_index
#undef net_max_players
#undef net_timeout_seconds
#undef net_xd_adapter_index
#undef prefs_multiplayer_type
#undef scenario_events_loaded
#undef screen_height
#undef choice
#undef max_players
#undef dialog2
#undef eh_next
#undef eh_handler
#undef eh_state

/* 0051dd97 auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define ini_simultaneous_allowed (*(int *)((u8 *)&g.d_006c3160))
#define mp_chat_from_start (*(short *)((u8 *)&g.d_00654c7a))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_show_human_starts (*(short *)((u8 *)&g.d_00654c78))
#define mp_simultaneous_moves (*(i8 *)((u8 *)&g.d_006ad684))
#define mp_simultaneous_setting (*(short *)((u8 *)&g.d_00654c7c))
#define prefs_accelerated_start (*(short *)((u8 *)&g.d_0064bc56))
#define prefs_barbarity (*(short *)((u8 *)&g.d_0064bc28))
#define prefs_difficulty (*(short *)((u8 *)&g.d_0064bc14))
#define prefs_enemies_choice (*(short *)((u8 *)&g.d_0064bc24))
#define prefs_game_rules (*(ushort *)((u8 *)&g.d_0064bc10))
#define prefs_mp_chat_from_start (*(short *)((u8 *)&g.d_0066654c))
#define prefs_mp_double_moves (*(short *)((u8 *)&g.d_00666600))
#define prefs_mp_double_production (*(short *)((u8 *)&g.d_006665fe))
#define prefs_mp_kill_on_retire (*(short *)((u8 *)&g.d_00666548))
#define prefs_mp_open_game (*(short *)((u8 *)&g.d_00666546))
#define prefs_mp_show_human_starts (*(short *)((u8 *)&g.d_0066654a))
#define prefs_mp_simultaneous_moves (*(short *)((u8 *)&g.d_0066654e))
#define prefs_rules_choice (*(short *)((u8 *)&g.d_0064bc54))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define setup_select_opponents (*(i32 *)((u8 *)&g.d_00631ee4))
#define late_year (*(int *)(frame_ + FRAME_OFF(4)))
#define mid_year (*(int *)(frame_ + FRAME_OFF(8)))
#define start_year (*(int *)(frame_ + FRAME_OFF(12)))
#define barbarity (*(u8 *)(frame_ + FRAME_OFF(28)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(36)))
#define i (*(int *)(frame_ + FRAME_OFF(792)))
#define difficulty2 (*(int *)(frame_ + FRAME_OFF(796)))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(800)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(808)))
i32 __cdecl setup_choose_game_options(int rules_mode,int mp_mode)

{
  byte sign;
  int choice;
  uint year;
  i32 value;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  setup_select_opponents = 0;
  setup_accelerated_start = 0;
  leaders_fixup_names();
  game.unused_0e = 0;
LAB_0051ddf1:
  do {
    do {
      setup_show_side_picture(3,0);
      dlg_load_game_section(&dialog2,ADDR(0x63203c, ((u8 *)&g.d_0063203c)),1);
      dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_difficulty);
      dialog_set_position
                ((DialogCore *)&dialog2,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      difficulty2 = dlg_show_modal(&dialog2,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
      if (difficulty2 < 0) {
        eh_state = 0xffffffff;
        /* inlined unwind funclet 0051e9e7 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        value = 1;
LAB_0051e9fd:
        return value;
      }
      game.difficulty = (u8)difficulty2;
      prefs_difficulty = (short)difficulty2;
      setup_show_side_picture(4,0);
      dlg_load_game_section(&dialog2,ADDR(0x632048, ((u8 *)&g.d_00632048)),1);
      dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_enemies_choice);
      dialog_set_position
                ((DialogCore *)&dialog2,
                 -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg_show_modal(&dialog2,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
    } while (choice < 0);
    if (dialog2.result_extra == 0) {
      prefs_enemies_choice = (short)choice;
      game.num_enemies = 6 - (char)choice;
    }
    else {
      choice = _rand();
      game.num_enemies = (char)(choice % 5) + 2;
    }
    setup_show_side_picture(5,0);
    dlg_load_game_section(&dialog2,ADDR(0x632054, ((u8 *)&g.d_00632054)),1);
    dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_barbarity);
    dialog_set_position
              ((DialogCore *)&dialog2,
               ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    choice = dlg_show_modal(&dialog2,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
  } while (choice < 0);
  if (dialog2.result_extra == 0) {
    barbarity = (u8)choice;
    game.barbarian_activity = barbarity;
    prefs_barbarity = (short)choice;
  }
  else if (game.difficulty < 2) {
    choice = _rand();
    sign = (byte)(choice >> 0x1f);
    game.barbarian_activity =
         ((((byte)choice ^ sign) - sign & 1 ^ sign) - sign) + game.difficulty;
  }
  else if (game.difficulty < 5) {
    choice = _rand();
    game.barbarian_activity = (char)(choice % 3) + 1;
  }
  else {
    choice = _rand();
    sign = (byte)(choice >> 0x1f);
    game.barbarian_activity = ((((byte)choice ^ sign) - sign & 1 ^ sign) - sign) + 2;
  }
LAB_0051e0f3:
  game.rules = 0x3f;
  setup_show_side_picture(9,0);
  dlg_load_game_section(&dialog2,ADDR(0x632060, ((u8 *)&g.d_00632060)),1);
  dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_rules_choice);
  dialog_set_position
            ((DialogCore *)&dialog2,
             -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  choice = dlg_show_modal(&dialog2,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((ViewWindow *)&setup_picwnd);
  if (-1 < choice) {
    prefs_rules_choice = (short)choice;
    if (choice != 0) goto LAB_0051e1c8;
    goto LAB_0051e6b0;
  }
  goto LAB_0051ddf1;
LAB_0051e1c8:
  game.rules = prefs_game_rules;
  if (rules_mode == 1) {
    game.rules = prefs_game_rules & 0x7fff;
  }
  else if (rules_mode == 2) {
    game.rules = prefs_game_rules | 0x8000;
  }
  dlg_checks_clear();
  dlg_check_set(0,(uint)((game.rules & 0x10) == 0));
  dlg_check_set(1,game.rules & 0x8000);
  dlg_check_set(2,0);
  dlg_check_set(3,(int)prefs_accelerated_start);
  dlg_check_set(4,game.rules & 0x80);
  dlg_check_set(5,game.rules & 0x100);
  setup_show_side_picture(9,0);
  dialog_load_text_section(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632068, ((u8 *)&g.d_00632068)),0,0,0,0,0,0);
  if (((byte)dialog2.style_flags & 4) != 0) {
    for (i = 0; i < (int)dialog2.option_count; i++) {
      dialog_set_option_checked
                ((DialogOptionList *)&dialog2,i,1 << ((byte)i & 0x1f) & dlg_check_bits);
    }
  }
  dialog_set_position
            ((DialogCore *)&dialog2,
             ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  choice = dlg_show_modal(&dialog2,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((ViewWindow *)&setup_picwnd);
  if (-1 < choice) {
    dlg_help_pressed = dialog2.result_extra;
    if (((byte)dialog2.style_flags & 4) != 0) {
      dlg_check_bits = 0;
      for (i = 0; i < (int)dialog2.option_count; i++) {
        choice = dialog_option_is_checked((DialogOptionList *)&dialog2,i);
        if (choice != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)i & 0x1f);
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
    setup_select_opponents = dlg_check_get(2);
    setup_accelerated_start = dlg_check_get(3);
    choice = dlg_check_get(4);
    if (choice != 0) {
      game.rules = game.rules | 0x80;
    }
    choice = dlg_check_get(5);
    if (choice != 0) {
      game.rules = game.rules | 0x100;
    }
    if (rules_mode == 0) {
      prefs_game_rules = game.rules;
    }
    else {
      prefs_game_rules = game.rules & 0x7fff | prefs_game_rules & 0x8000;
    }
    if (setup_accelerated_start != 0) {
      game.first_launch_turn = -1;
      choice = game_turn_to_year(0);
      if (choice < 1) {
        year = game_turn_to_year(0);
        start_year = ~year + 1;
      }
      else {
        start_year = game_turn_to_year(0);
      }
      text_set_number_arg(0,start_year);
      choice = game_turn_to_year(0x15);
      if (choice < 1) {
        year = game_turn_to_year(0x15);
        mid_year = ~year + 1;
      }
      else {
        mid_year = game_turn_to_year(0x15);
      }
      text_set_number_arg(1,mid_year);
      choice = game_turn_to_year(0x29);
      if (choice < 1) {
        year = game_turn_to_year(0x29);
        late_year = ~year + 1;
      }
      else {
        late_year = game_turn_to_year(0x29);
      }
      text_set_number_arg(2,late_year);
      setup_show_side_picture(9,0);
      dlg_load_game_section(&dialog2,ADDR(0x632074, ((u8 *)&g.d_00632074)),1);
      dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_accelerated_start);
      dialog_set_position
                ((DialogCore *)&dialog2,
                 -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      setup_accelerated_start = dlg_show_modal(&dialog2,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
      if (setup_accelerated_start < 0) {
        setup_accelerated_start = 0;
        goto LAB_0051e0f3;
      }
    }
    prefs_accelerated_start = (short)setup_accelerated_start;
LAB_0051e6b0:
    while( true ) {
      setup_show_side_picture(9,0);
      dlg_checks_clear();
      dlg_check_set(0,(int)prefs_mp_open_game);
      dlg_check_set(1,(int)prefs_mp_kill_on_retire);
      dlg_check_set(2,(int)prefs_mp_show_human_starts);
      dlg_check_set(3,(int)prefs_mp_chat_from_start);
      dlg_check_set(4,(int)prefs_mp_double_production);
      dlg_check_set(5,(int)prefs_mp_double_moves);
      dialog_load_text_section(&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632080, ((u8 *)&g.d_00632080)),0,0,0,0,0,0);
      if (ini_simultaneous_allowed == 0) {
        mp_simultaneous_moves = 0;
        mp_simultaneous_setting = 0;
      }
      else {
        text_clear();
        text_append_label(0x364);
        dialog_add_option((DialogOptionList *)&dialog2,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
        dlg_check_set(6,(int)prefs_mp_simultaneous_moves);
      }
      if (((byte)dialog2.style_flags & 4) != 0) {
        for (i = 0; i < (int)dialog2.option_count; i++) {
          dialog_set_option_checked
                    ((DialogOptionList *)&dialog2,i,
                     1 << ((byte)i & 0x1f) & dlg_check_bits);
        }
      }
      if ((mp_mode == 1) &&
         (dialog_set_option_disabled((DialogOptionList *)&dialog2,3,1), ini_simultaneous_allowed != 0))
      {
        dialog_set_option_disabled((DialogOptionList *)&dialog2,6,1);
      }
      dialog_set_position
                ((DialogCore *)&dialog2,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg_show_modal(&dialog2,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
      if (choice < 0) break;
      value = dialog_option_is_checked((DialogOptionList *)&dialog2,0);
      mp_open_game = (short)value;
      prefs_mp_open_game = mp_open_game;
      value = dialog_option_is_checked((DialogOptionList *)&dialog2,1);
      mp_kill_civ_on_retire = (short)value;
      prefs_mp_kill_on_retire = mp_kill_civ_on_retire;
      value = dialog_option_is_checked((DialogOptionList *)&dialog2,2);
      mp_show_human_starts = (short)value;
      prefs_mp_show_human_starts = mp_show_human_starts;
      value = dialog_option_is_checked((DialogOptionList *)&dialog2,3);
      mp_chat_from_start = (short)value;
      prefs_mp_chat_from_start = mp_chat_from_start;
      value = dialog_option_is_checked((DialogOptionList *)&dialog2,4);
      mp_double_production = (short)value;
      prefs_mp_double_production = mp_double_production;
      value = dialog_option_is_checked((DialogOptionList *)&dialog2,5);
      mp_double_moves = (short)value;
      prefs_mp_double_moves = mp_double_moves;
      if (ini_simultaneous_allowed != 0) {
        value = dialog_option_is_checked((DialogOptionList *)&dialog2,6);
        mp_simultaneous_setting = (short)value;
        prefs_mp_simultaneous_moves = mp_simultaneous_setting;
      }
      if (mp_mode == 1) {
        mp_chat_from_start = 0;
        mp_simultaneous_setting = 0;
      }
      if ((mp_mode == 2) || (choice = setup_choose_game_timer(0), choice == 0)) {
        eh_state = 0xffffffff;
        /* inlined unwind funclet 0051e9e7 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        value = 0;
        goto LAB_0051e9fd;
      }
    }
  }
  goto LAB_0051e0f3;
}
#undef dlg_check_bits
#undef dlg_help_pressed
#undef ini_simultaneous_allowed
#undef mp_chat_from_start
#undef mp_double_moves
#undef mp_double_production
#undef mp_kill_civ_on_retire
#undef mp_open_game
#undef mp_show_human_starts
#undef mp_simultaneous_moves
#undef mp_simultaneous_setting
#undef prefs_accelerated_start
#undef prefs_barbarity
#undef prefs_difficulty
#undef prefs_enemies_choice
#undef prefs_game_rules
#undef prefs_mp_chat_from_start
#undef prefs_mp_double_moves
#undef prefs_mp_double_production
#undef prefs_mp_kill_on_retire
#undef prefs_mp_open_game
#undef prefs_mp_show_human_starts
#undef prefs_mp_simultaneous_moves
#undef prefs_rules_choice
#undef screen_height
#undef setup_select_opponents
#undef late_year
#undef mid_year
#undef start_year
#undef barbarity
#undef dialog2
#undef i
#undef difficulty2
#undef eh_next
#undef eh_handler
#undef eh_state

/* 0051ea8e auto */
#define autoplay_active (*(ushort *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(short *)((u8 *)&g.d_00654faa))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define net_vote_status (*(int *)((u8 *)&g.d_006ad670))
#define prefs_turn_timer_choice (*(short *)((u8 *)&g.d_006665d0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define choice (*(int *)(frame_ + FRAME_OFF(4)))
#define custom_text (*(char (*)[16])(frame_ + FRAME_OFF(8)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define custom_seconds (*(int *)(frame_ + FRAME_OFF(780)))
#define saved_choice (*(short *)(frame_ + FRAME_OFF(784)))
#define saved_limit (*(int *)(frame_ + FRAME_OFF(788)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(792)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(800)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl setup_choose_game_timer(int in_game)

{
  int minutes;
  i32 result;
  int seconds;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x2000);
  try_level = 0;
  saved_choice = prefs_turn_timer_choice;
  saved_limit = mp_turn_time_limit_ms;
LAB_0051ead8:
  prefs_turn_timer_choice = saved_choice;
  if ((in_game == 0) && (turn_resume_new_game == 0)) {
    setup_show_side_picture(0xffffffff,0);
    dlg_load_game_section(&dlg,ADDR(0x63208c, ((u8 *)&g.d_0063208c)),1);
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_turn_timer_choice);
    dialog_set_position
              ((DialogCore *)&dlg,0xfffffc19,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  }
  else {
    dlg_load_game_section(&dlg,ADDR(0x632098, ((u8 *)&g.d_00632098)),1);
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_turn_timer_choice);
    dialog_set_position((DialogCore *)&dlg,0xfffffc19,0xfffffc19);
  }
  choice = dlg_show_modal(&dlg,0);
  if (choice < 0) {
    if (in_game == 0) {
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
    }
    try_level = 0xffffffff;
    /* inlined unwind funclet 0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
    result = 1;
    goto LAB_0051f10b;
  }
  prefs_turn_timer_choice = (short)choice;
  switch(choice) {
  case 0:
    mp_turn_time_limit_ms = 0;
    break;
  case 1:
    mp_turn_time_limit_ms = 30000;
    break;
  case 2:
    mp_turn_time_limit_ms = 60000;
    break;
  case 3:
    mp_turn_time_limit_ms = 120000;
    break;
  case 4:
    mp_turn_time_limit_ms = 180000;
    break;
  case 5:
    mp_turn_time_limit_ms = 300000;
    break;
  case 6:
    goto switchD_0051edf7_caseD_6;
  }
switchD_0051edf7_default:
  if (in_game == 0) {
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
    if (choice == 6) {
      crt_strcpy(&prefs_turn_timer_custom,custom_text);
    }
    try_level = 0xffffffff;
    /* inlined unwind funclet 0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
    result = 0;
    goto LAB_0051f10b;
  }
  if (1 < net_player_count) {
    crt_strcpy(&text_string_args,&net_local_player_name);
    str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
    if (mp_turn_time_limit_ms == 0) {
      str_append_label(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0x285);
    }
    else {
      minutes = (mp_turn_time_limit_ms / 1000) / 0x3c;
      seconds = (mp_turn_time_limit_ms / 1000) % 0x3c;
      if (minutes < 10) {
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0);
      }
      str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),minutes);
      crt_strcat(&text_string_arg1,&setup_timer_minsec_sep_str);
      if (seconds < 10) {
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0);
      }
      str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),seconds);
    }
    net_vote_replies_pending = net_player_count - 1;
    net_vote_status = 0;
    net_send_text_args(0x40,0xff,2,0,0,0);
    dlg_pending_idle_callback = ((void *)ADDR(0x004019b5, net_vote_wait_idle_cb));
    dialog_timeout_start_i32 = timer_ticks();
    minutes = popup_game_sprite_flags(ADDR(0x6320b8, ((u8 *)&g.d_006320b8)),0x2000001,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    if (((minutes < 0) || (net_vote_status == -1)) || (net_vote_replies_pending != 0)) {
      prefs_turn_timer_choice = saved_choice;
      mp_turn_time_limit_ms = saved_limit;
      net_send_text_args(0x41,0xff,0,0,0,0);
      popup_game_with_sprite(ADDR(0x6320cc, ((u8 *)&g.d_006320cc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      try_level = 0xffffffff;
      /* inlined unwind funclet 0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      result = 1;
      goto LAB_0051f10b;
    }
    net_send_text_args(0x42,0xff,0,0,0,0);
    popup_game_with_sprite(ADDR(0x6320dc, ((u8 *)&g.d_006320dc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  try_level = 0xffffffff;
  /* inlined unwind funclet 0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  result = 0;
LAB_0051f10b:
  return result;
switchD_0051edf7_caseD_6:
  while( true ) {
    minutes = dialog_load_text_section(&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6320a4, ((u8 *)&g.d_006320a4)),4,ADDR(0x6665d2, ((u8 *)&g.d_006665d2)),0,0,0,1);
    if (minutes != 0) {
      if (in_game == 0) {
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
      }
      try_level = 0xffffffff;
      /* inlined unwind funclet 0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      result = 1;
      goto LAB_0051f10b;
    }
    if (in_game == 0) {
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    }
    else {
      dialog_set_position((DialogCore *)&dlg,0xfffffc19,0xfffffc19);
    }
    choice = dialog_run_modal(&dlg,(iptr)custom_text,0);
    snd_play_effect(0x6a,0,0,0);
    if (choice < 0) break;
    custom_seconds = _atoi(custom_text);
    if (custom_seconds < 0) {
      autoplay_active = autoplay_active ^ 1;
      autoplay_turns_left = -(short)custom_seconds;
    }
    else if ((custom_seconds < 0xe11) && (9 < custom_seconds)) {
      mp_turn_time_limit_ms = custom_seconds * 1000;
      goto switchD_0051edf7_default;
    }
  }
  if (in_game == 0) {
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
  }
  goto LAB_0051ead8;
}
#undef autoplay_active
#undef autoplay_turns_left
#undef dlg_pending_idle_callback
#undef mp_turn_time_limit_ms
#undef net_vote_status
#undef prefs_turn_timer_choice
#undef screen_height
#undef turn_resume_new_game
#undef dialog_timeout_start_i32
#undef choice
#undef custom_text
#undef dlg
#undef custom_seconds
#undef saved_choice
#undef saved_limit
#undef seh_prev
#undef seh_handler
#undef try_level

/* 0051f19c auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define net_claimed_civs_mask (*(short *)((u8 *)&g.d_00654fb0))
#define net_connection_title (*(i32 *)((u8 *)&g.d_006ad63c))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define prefs_email_address (*(i8 *)((u8 *)&g.d_00666590))
#define prefs_gender (*(short *)((u8 *)&g.d_0064bc18))
#define prefs_tribe (*(i16 *)((u8 *)&g.d_0064bc16))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(i8 *)((u8 *)&g.d_00628048))
#define net_player_info_civ_i32 (*(i32 *)((u8 *)&g.d_006ad120))
#define net_player_info_leader_index_i32 (*(i32 *)((u8 *)&g.d_006ad124))
#define net_player_info_gender_i32 (*(i32 *)((u8 *)&g.d_006ad128))
#define net_player_info_has_names_i32 (*(i32 *)((u8 *)&g.d_006ad12c))
#define net_player_info_has_titles_i32 (*(i32 *)((u8 *)&g.d_006ad178))
#define net_wait_start_ticks_i32 (*(i32 *)((u8 *)&g.d_006ad674))
#define email_default (*(i8 * *)(frame_ + FRAME_OFF(0)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(8)))
#define style2 (*(int *)(frame_ + FRAME_OFF(12)))
#define is_female (*(u8 *)(frame_ + FRAME_OFF(20)))
#define input_text (*(char (*)[260])(frame_ + FRAME_OFF(24)))
#define tries (*(int *)(frame_ + FRAME_OFF(284)))
#define avail_count (*(int *)(frame_ + FRAME_OFF(288)))
#define result (*(int *)(frame_ + FRAME_OFF(292)))
#define sel_tribe (*(iptr *)(frame_ + FRAME_OFF(296)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(300)))
#define retry_tribe (*(iptr *)(frame_ + FRAME_OFF(1056)))
#define option (*(byte * *)(frame_ + FRAME_OFF(1060)))
#define leader2 (*(iptr *)(frame_ + FRAME_OFF(1064)))
#define title (*(iptr *)(frame_ + FRAME_OFF(1068)))
#define cancelled (*(int *)(frame_ + FRAME_OFF(1072)))
#define wait_start (*(int *)(frame_ + FRAME_OFF(1076)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(1088)))
/* WARNING: Removing unreachable block (ram,0x005212c5) */
/* WARNING: Removing unreachable block (ram,0x005213cc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl setup_choose_tribe(int player_slot,int game_mode,int in_game)

{
  int choice;
  iptr label;
  int now_ticks;
  i32 str;
  iptr tribe_arg;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  leader2 = -1;
  result = 1;
  retry_tribe = -1;
  dialog_ctor(&dlg,0x2000);
  try_level = 0;
  sel_tribe = 0;
LAB_0051f1f6:
  do {
    if (-1 < leader2) {
      if (leaders[leader2].leader_name < 1) {
        leaders[leader2].leader_name = ~leaders[leader2].leader_name + 1;
      }
      if (leaders[leader2].plural < 1) {
        leaders[leader2].plural = ~leaders[leader2].plural + 1;
      }
      if (leaders[leader2].adjective < 1) {
        leaders[leader2].adjective = ~leaders[leader2].adjective + 1;
      }
      for (title = 0; title < 7; title++) {
        if (leaders[leader2].titles[title][0] < 1) {
          *(ushort *)&leaders[leader2].titles[title][0] =
               ~*(ushort *)&leaders[leader2].titles[title][0] + 1;
        }
        if (leaders[leader2].titles[title][1] < 1) {
          *(ushort *)&leaders[leader2].titles[title][1] =
               ~*(ushort *)&leaders[leader2].titles[title][1] + 1;
        }
      }
    }
    if (in_game == 0) {
      setup_show_side_picture(6,0);
    }
    dlg_load_game_section(&dlg,ADDR(0x6320ec, ((u8 *)&g.d_006320ec)),1);
    dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_gender);
    if (in_game == 0) {
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    }
    if (2 < game_mode) {
      dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
    }
    choice = dlg_show_modal(&dlg,0);
    snd_play_effect(0x6a,0,0,0);
    if (in_game == 0) {
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
    }
    if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
      text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
      crt_strcpy(&text_string_args,net_connection_title);
      if (nm_server_canceled_count == 0) {
        popup_game_with_sprite(ADDR(0x632100, ((u8 *)&g.d_00632100)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      else {
        popup_game_with_sprite(ADDR(0x6320f4, ((u8 *)&g.d_006320f4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      result = 1;
      goto LAB_0052144f;
    }
    if (choice < 0) goto LAB_0052144f;
    prefs_gender = (short)choice;
    net_player_info_gender_i32 = (int)prefs_gender;
    if (in_game == 0) {
      setup_show_side_picture(0xffffffff,0);
    }
    cancelled = dialog_load_text(&dlg,ADDR(0x632114, ((u8 *)&g.d_00632114)),ADDR(0x63210c, ((u8 *)&g.d_0063210c)),0x801);
    if (cancelled != 0) {
      if (in_game == 0) {
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
      }
      goto LAB_0052144f;
    }
    if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
      text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
      crt_strcpy(&text_string_args,net_connection_title);
      if (nm_server_canceled_count == 0) {
        popup_game_with_sprite(ADDR(0x632128, ((u8 *)&g.d_00632128)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      else {
        popup_game_with_sprite(ADDR(0x63211c, ((u8 *)&g.d_0063211c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      result = 1;
      goto LAB_0052144f;
    }
    dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
    dialog_set_columns((DialogButtonsView *)&dlg,3);
    avail_count = 0;
    for (leader = 0; leader < 0x15; leader++) {
      if ((((uint)game.human_players & 1 << ((byte)leaders[leader].color & 0x1f)) == 0) &&
         (((int)net_claimed_civs_mask & 1 << ((byte)leaders[leader].color & 0x1f)) == 0)) {
        if (leaders[leader].leader_name < 1) {
          leaders[leader].leader_name = ~leaders[leader].leader_name + 1;
        }
        if (leaders[leader].plural < 1) {
          leaders[leader].plural = ~leaders[leader].plural + 1;
        }
        if (leaders[leader].adjective < 1) {
          leaders[leader].adjective = ~leaders[leader].adjective + 1;
        }
        for (title = 0; title < 7; title++) {
          if (leaders[leader].titles[title][0] < 1) {
            *(ushort *)&leaders[leader].titles[title][0] =
                 ~*(ushort *)&leaders[leader].titles[title][0] + 1;
          }
          if (leaders[leader].titles[title][1] < 1) {
            *(ushort *)&leaders[leader].titles[title][1] =
                 ~*(ushort *)&leaders[leader].titles[title][1] + 1;
          }
        }
      }
      if ((((uint)game.human_players & 1 << ((byte)leaders[leader].color & 0x1f)) == 0) ||
         (-1 < leaders[leader].plural)) {
        str = 0;
        tribe_arg = leader;
        label = label_string((int)leaders[leader].plural);
        dialog_add_option((DialogOptionList *)&dlg,label,tribe_arg,str);
      }
      else {
        dialog_add_option
                  ((DialogOptionList *)&dlg,(iptr)&civ_names[leaders[leader].color].tribe_name,leader
                   ,0);
      }
    }
LAB_0051f8c0:
    avail_count = 0;
    for (leader = 0; leader < 0x15; leader++) {
      if ((((uint)game.human_players & 1 << ((byte)leaders[leader].color & 0x1f)) == 0) &&
         (((int)net_claimed_civs_mask & 1 << ((byte)leaders[leader].color & 0x1f)) == 0)) {
        if (leaders[leader].leader_name < 1) {
          leaders[leader].leader_name = ~leaders[leader].leader_name + 1;
        }
        if (leaders[leader].plural < 1) {
          leaders[leader].plural = ~leaders[leader].plural + 1;
        }
        if (leaders[leader].adjective < 1) {
          leaders[leader].adjective = ~leaders[leader].adjective + 1;
        }
        for (title = 0; title < 7; title++) {
          if (leaders[leader].titles[title][0] < 1) {
            *(ushort *)&leaders[leader].titles[title][0] =
                 ~*(ushort *)&leaders[leader].titles[title][0] + 1;
          }
          if (leaders[leader].titles[title][1] < 1) {
            *(ushort *)&leaders[leader].titles[title][1] =
                 ~*(ushort *)&leaders[leader].titles[title][1] + 1;
          }
        }
      }
      if ((((uint)game.human_players & 1 << ((byte)leaders[leader].color & 0x1f)) == 0) &&
         (((int)net_claimed_civs_mask & 1 << ((byte)leaders[leader].color & 0x1f)) == 0)) {
        avail_count++;
        dialog_set_option_disabled((DialogOptionList *)&dlg,leader,0);
        if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
          radiogrp_enable_item((RadioGroupEnableView *)dlg.radio_group,leader);
        }
      }
      else {
        dialog_set_option_disabled((DialogOptionList *)&dlg,leader,1);
        if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
          radiogrp_disable_item((RadioGroupDisableView *)dlg.radio_group,leader);
        }
      }
    }
    if (avail_count == 0) {
      popup_game(ADDR(0x632134, ((u8 *)&g.d_00632134)));
      dialog_close(&dlg);
      goto LAB_0052144f;
    }
    for (tries = 0; tries < 0x15; tries++) {
      option = (byte *)dialog_find_option((DialogOptionList *)&dlg,sel_tribe);
      if ((option != (byte *)0x0) && ((*option & 1) == 0)) {
        dialog_set_default_choice((DialogOptionList *)&dlg,*(iptr *)(option + 4));
        if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
          radiogrp_set_selected
                    ((RadioGroupSetSelView *)dlg.radio_group,*(i32 *)(option + 4));
        }
        break;
      }
      sel_tribe++;
      if (sel_tribe == 0x15) {
        sel_tribe = 0;
      }
    }
    if (in_game == 0) {
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    }
    if (2 < game_mode) {
      net_reset_msg_counts();
      net_wait_start_ticks_i32 = timer_ticks();
    }
    dlg.style_flags = dlg.style_flags & 0xfffffbff;
    dlg.result_id = 0;
    dlg.result_extra = 0;
    if (2 < game_mode) {
      dlg_pending_idle_callback = ((void *)ADDR(0x0040126c, net_lock_wait_idle_cb));
    }
    leader2 = dlg_show_modal(&dlg,0);
    sel_tribe = radiogrp_get_selected((RadioGroupGetSelView *)dlg.radio_group);
    if (2 < game_mode) {
      if (nm_lock_data_count == 0) {
        if ((nm_server_canceled_count == 0) && (nm_lost_server_on_join_count == 0)) goto LAB_0051fdd1;
        text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
        crt_strcpy(&text_string_args,net_connection_title);
        if (nm_server_canceled_count == 0) {
          popup_game_with_sprite(ADDR(0x63214c, ((u8 *)&g.d_0063214c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x632140, ((u8 *)&g.d_00632140)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        if (in_game == 0) {
          setup_picwnd_close((ViewWindow *)&setup_picwnd);
        }
        dialog_close(&dlg);
        goto LAB_0052144f;
      }
      retry_tribe = leader2;
      goto LAB_0051f8c0;
    }
LAB_0051fdd1:
    snd_play_effect(0x6a,0,0,0);
    if (leader2 < 0) {
      if (in_game == 0) {
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
      }
      dialog_close(&dlg);
      goto LAB_0051f1f6;
    }
    sel_tribe = leader2;
    net_player_info_leader_index_i32 = leader2;
    game.player_civ = (i8)leaders[leader2].color;
    net_player_info_civ_i32 = (int)game.player_civ;
    if (2 < game_mode) {
      net_reset_msg_counts();
      net_send_message(0x30,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
      if (net_host_flag == '\0') {
        wait_start = timer_ticks();
        while (((nm_nation_accept_count == 0 && (nm_nation_reject_count == 0)) &&
               (now_ticks = timer_ticks(), now_ticks - wait_start < net_timeout_seconds * 0x3c))) {
          if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
            text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
            crt_strcpy(&text_string_args,net_connection_title);
            if (nm_server_canceled_count == 0) {
              popup_game_with_sprite(ADDR(0x632164, ((u8 *)&g.d_00632164)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            else {
              popup_game_with_sprite(ADDR(0x632158, ((u8 *)&g.d_00632158)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            result = 1;
            goto LAB_0052144f;
          }
          net_process_messages((NetSession *)&net_session,1,0);
        }
      }
      if ((nm_nation_accept_count == 0) && (nm_nation_reject_count == 0)) {
        popup_game_with_sprite(ADDR(0x632170, ((u8 *)&g.d_00632170)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        if (in_game == 0) {
          setup_picwnd_close((ViewWindow *)&setup_picwnd);
        }
        dialog_close(&dlg);
        goto LAB_0052144f;
      }
      if (nm_nation_reject_count == 0) goto LAB_0051ffec;
      retry_tribe = leader2;
      popup_game_with_sprite(ADDR(0x632184, ((u8 *)&g.d_00632184)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      goto LAB_0051f8c0;
    }
LAB_0051ffec:
    if (in_game == 0) {
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
    }
    prefs_tribe = (i16)leader2;
    civs[game.player_civ].tribe = prefs_tribe;
    civs[game.player_civ].leader_portrait = (u8)leader2;
    if (choice != 0) {
      civs[game.player_civ].leader_portrait += 21;
    }
    human_civ = (iptr)game.player_civ;
    game.human_players = (byte)(1 << (game.player_civ & 0x1fU)) | game.human_players;
    is_female = (u8)choice;
    leaders[civs[game.player_civ].tribe].female = is_female;
    leaders[civs[game.player_civ].tribe].leader_name =
         leaders[civs[game.player_civ].tribe].names[((uint)leaders[civs[game.player_civ].tribe].female)];
    str = label_string((int)leaders[civs[game.player_civ].tribe].leader_name);
    crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,str);
    leaders[civs[game.player_civ].tribe].leader_name =
         -leaders[civs[game.player_civ].tribe].leader_name;
    now_ticks = civ_check_password(human_civ);
    if (now_ticks != 0) {
      net_player_info_has_names_i32 = 0;
      net_player_info_has_titles_i32 = 0;
      if (dlg.result_extra == 0) {
        do {
          if (in_game == 0) {
            setup_show_side_picture(7,0);
          }
          dialog_load_text_section
                    (&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6321f8, ((u8 *)&g.d_006321f8)),0x17,(iptr)&civ_names[game.player_civ].leader_name,0,0,0,1);
          dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
          if (in_game == 0) {
            dialog_set_position
                      ((DialogCore *)&dlg,0xfffffc19,
                       -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
          }
          if (2 < game_mode) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          }
          cancelled = dialog_run_modal(&dlg,(iptr)input_text,0);
        } while (input_text[0] == '\0');
        if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
          text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
          crt_strcpy(&text_string_args,net_connection_title);
          if (nm_server_canceled_count == 0) {
            popup_game_with_sprite(ADDR(0x63220c, ((u8 *)&g.d_0063220c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x632200, ((u8 *)&g.d_00632200)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          result = 1;
          goto LAB_0052144f;
        }
        snd_play_effect(0x6a,0,0,0);
        if (in_game == 0) {
          setup_picwnd_close((ViewWindow *)&setup_picwnd);
        }
        if (cancelled != 0) {
          game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
          if (2 < game_mode) {
            net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
          }
          goto LAB_0051f1f6;
        }
        crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,input_text);
        crt_strcpy(&net_player_info_leader_name,input_text);
        net_player_info_tribe_name = '\0';
        net_player_info_adjective = '\0';
      }
      else {
        if (((net_player_info_tribe_name == '\0') || (net_player_info_adjective == '\0')) || (game_mode == 1)) {
          str = label_string((int)leaders[civs[game.player_civ].tribe].plural);
          crt_strcpy((iptr)&civ_names[game.player_civ].tribe_name,str);
          str = label_string((int)leaders[civs[game.player_civ].tribe].adjective);
          crt_strcpy((iptr)&civ_names[game.player_civ].adjective,str);
        }
        else {
          crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,&net_player_info_leader_name);
          crt_strcpy((iptr)&civ_names[game.player_civ].tribe_name,&net_player_info_tribe_name);
          crt_strcpy((iptr)&civ_names[game.player_civ].adjective,&net_player_info_adjective);
        }
        leaders[civs[game.player_civ].tribe].plural = -leaders[civs[game.player_civ].tribe].plural;
        leaders[civs[game.player_civ].tribe].adjective =
             -leaders[civs[game.player_civ].tribe].adjective;
        for (title = 0; title < 7; title++) {
          str = label_string((int)leaders[civs[game.player_civ].tribe].titles[title][choice]);
          crt_strcpy((iptr)&civ_names[game.player_civ].titles[title],str);
          leaders[civs[game.player_civ].tribe].titles[title][choice] =
               -leaders[civs[game.player_civ].tribe].titles[title][choice]
          ;
        }
        while( true ) {
          text_set_string_arg_b(1,(iptr)&civ_names[game.player_civ].tribe_name);
          text_set_string_arg_b(2,(iptr)&civ_names[game.player_civ].adjective);
          if (in_game == 0) {
            setup_show_side_picture(7,0);
          }
          cancelled = dialog_load_text_section
                               (&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6321ac, ((u8 *)&g.d_006321ac)),0x17,(iptr)&civ_names[game.player_civ].leader_name,
                                0,0,0,1);
          if (cancelled != 0) {
            game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
            if (in_game == 0) {
              setup_picwnd_close((ViewWindow *)&setup_picwnd);
            }
            if (2 < game_mode) {
              net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
            }
            goto LAB_0052144f;
          }
          dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
          if (in_game == 0) {
            dialog_set_position
                      ((DialogCore *)&dlg,0xfffffc19,
                       -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
          }
          if (2 < game_mode) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          }
          choice = dlg_show_modal(&dlg,0);
          snd_play_effect(0x6a,0,0,0);
          if (in_game == 0) {
            setup_picwnd_close((ViewWindow *)&setup_picwnd);
          }
          if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
            text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
            crt_strcpy(&text_string_args,net_connection_title);
            if (nm_server_canceled_count == 0) {
              popup_game_with_sprite(ADDR(0x6321c4, ((u8 *)&g.d_006321c4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            else {
              popup_game_with_sprite(ADDR(0x6321b8, ((u8 *)&g.d_006321b8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            result = 1;
            goto LAB_0052144f;
          }
          if (choice < 0) {
            game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
            if (2 < game_mode) {
              net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
            }
            goto LAB_0051f1f6;
          }
          crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,&text_string_args);
          crt_strcpy((iptr)&civ_names[game.player_civ].tribe_name,&text_string_arg1);
          crt_strcpy((iptr)&civ_names[game.player_civ].adjective,&text_string_arg2);
          crt_strcpy(&net_player_info_leader_name,&text_string_args);
          crt_strcpy(&net_player_info_tribe_name,&text_string_arg1);
          crt_strcpy(&net_player_info_adjective,&text_string_arg2);
          net_player_info_has_names_i32 = 1;
          if (dlg.result_extra != 1) break;
          if (in_game == 0) {
            setup_show_side_picture(7,0);
          }
          cancelled = dlg_load_game_section(&dlg,ADDR(0x6321d0, ((u8 *)&g.d_006321d0)),1);
          if (cancelled != 0) {
            game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
            if (in_game == 0) {
              setup_picwnd_close((ViewWindow *)&setup_picwnd);
            }
            if (2 < game_mode) {
              net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
            }
            goto LAB_0052144f;
          }
          dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
          for (title = 0; title < 7; title++) {
            text_clear();
            text_append_string_id(government_names[title]);
            text_append_colon();
            if (((&net_player_info_govt_titles)[title * 0x18] == '\0') || (game_mode == 1)) {
              dialog_add_edit_field
                        ((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&civ_names[game.player_civ].titles[title],0x17);
            }
            else {
              dialog_add_edit_field
                        ((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                         (iptr)(&net_player_info_govt_titles + title * 0x18),0x17);
            }
          }
          if (in_game == 0) {
            dialog_set_position
                      ((DialogCore *)&dlg,0xfffffc19,
                       -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
          }
          if (2 < game_mode) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          }
          choice = dlg_show_modal(&dlg,0);
          if (choice == 0) {
            for (title = 0; title < 7; title++) {
              crt_strcpy((iptr)&civ_names[game.player_civ].titles[title],
                           &text_string_args + title * 0x104);
              crt_strcpy(&net_player_info_govt_titles + title * 0x18,&text_string_args + title * 0x104);
            }
            net_player_info_has_titles_i32 = 1;
          }
          snd_play_effect(0x6a,0,0,0);
          if (in_game == 0) {
            setup_picwnd_close((ViewWindow *)&setup_picwnd);
          }
        }
        if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
          text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
          crt_strcpy(&text_string_args,net_connection_title);
          if (nm_server_canceled_count == 0) {
            popup_game_with_sprite(ADDR(0x6321ec, ((u8 *)&g.d_006321ec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x6321e0, ((u8 *)&g.d_006321e0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          result = 1;
          goto LAB_0052144f;
        }
      }
      if (in_game == 0) {
        setup_show_side_picture(8,0);
      }
      dlg_load_game_section(&dlg,ADDR(0x632218, ((u8 *)&g.d_00632218)),0x20001);
      dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
      for (style2 = 0; style2 < 4; style2++) {
        label = label_string(*(i32 *)(label_string_ids + 0x3d8 + style2 * 4));
        dialog_add_sprite
                  ((DialogOptionList *)&dlg,style2 * 0x1e0 + ADDR(0x63fff4, ((u8 *)&g.d_0063fe8c + 360)),style2,label);
      }
      dialog_set_default_choice
                ((DialogOptionList *)&dlg,(int)leaders[civs[game.player_civ].tribe].city_style);
      if (in_game == 0) {
        dialog_set_position
                  ((DialogCore *)&dlg,
                   -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1)
                   ,-(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1
                     ));
      }
      if (2 < game_mode) {
        dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
      }
      choice = dlg_show_modal(&dlg,0);
      if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
        text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
        crt_strcpy(&text_string_args,net_connection_title);
        if (nm_server_canceled_count == 0) {
          popup_game_with_sprite(ADDR(0x632230, ((u8 *)&g.d_00632230)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x632224, ((u8 *)&g.d_00632224)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        result = 1;
        goto LAB_0052144f;
      }
      snd_play_effect(0x6a,0,0,0);
      if (in_game == 0) {
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
      }
      if (choice < 0) {
        game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
        if (2 < game_mode) {
          net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
        }
      }
      else {
        net_player_info_city_style = choice;
        civ_names[game.player_civ].city_style = (i16)choice;
        result = 0;
        *(iptr *)(&setup_player_tribes + player_slot * 4) = leader2;
        if (game_mode != 2) goto LAB_0052144f;
        if (in_game == 0) {
          setup_show_side_picture(7,0);
        }
        if (player_slot == 0) {
          email_default = &prefs_email_address;
        }
        else {
          email_default = &setup_input_blank_default;
        }
        dialog_load_text_section
                  (&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632240, ((u8 *)&g.d_00632240)),0x1f,(iptr)email_default,0,0,0,1);
        dialog_prepend_title_label((iptr)&dlg,player_slot + 0x25e);
        if (in_game == 0) {
          dialog_set_position
                    ((DialogCore *)&dlg,0xfffffc19,
                     -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) +
                      1));
        }
        cancelled = dialog_run_modal(&dlg,(iptr)input_text,0);
        if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
          text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
          crt_strcpy(&text_string_args,net_connection_title);
          if (nm_server_canceled_count == 0) {
            popup_game_with_sprite(ADDR(0x63225c, ((u8 *)&g.d_0063225c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x632250, ((u8 *)&g.d_00632250)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          result = 1;
          goto LAB_0052144f;
        }
        snd_play_effect(0x6a,0,0,0);
        if (in_game == 0) {
          setup_picwnd_close((ViewWindow *)&setup_picwnd);
        }
        if (cancelled == 0) {
          crt_strcpy(&civ_email_addresses + game.player_civ * 0x20,input_text);
          if (player_slot == 0) {
            crt_strcpy(&prefs_email_address,input_text);
            saved_turn_civ = (i8)human_civ;
            turn_resume_civ = (i8)human_civ;
          }
LAB_0052144f:
          choice = result;
          if ((result == 1) && (-1 < leader2)) {
            if (leaders[leader2].leader_name < 1) {
              leaders[leader2].leader_name = ~leaders[leader2].leader_name + 1;
            }
            if (leaders[leader2].plural < 1) {
              leaders[leader2].plural = ~leaders[leader2].plural + 1;
            }
            if (leaders[leader2].adjective < 1) {
              leaders[leader2].adjective = ~leaders[leader2].adjective + 1;
            }
            for (title = 0; title < 7; title++) {
              if (leaders[leader2].titles[title][0] < 1) {
                *(ushort *)&leaders[leader2].titles[title][0] =
                     ~*(ushort *)&leaders[leader2].titles[title][0] + 1;
              }
              if (leaders[leader2].titles[title][1] < 1) {
                *(ushort *)&leaders[leader2].titles[title][1] =
                     ~*(ushort *)&leaders[leader2].titles[title][1] + 1;
              }
            }
          }
          if (((in_game == 0) && (result == 1)) && (0 < player_slot)) {
            if (leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].leader_name < 1) {
              leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].leader_name =
                   ~leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].leader_name + 1;
            }
            if (leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].plural < 1) {
              leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].plural =
                   ~leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].plural + 1;
            }
            if (leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].adjective < 1) {
              leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].adjective =
                   ~leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].adjective + 1;
            }
            for (title = 0; title < 7; title++) {
              if (leaders[(*(int *)(&setup_prev_player_tribe + player_slot * 4))].titles[title][0]
                  < 1) {
                *(ushort *)&leaders[(*(int *)(&setup_prev_player_tribe + player_slot * 4))].titles[title][0]
                     = ~*(ushort *)
                         (*(int *)(&setup_prev_player_tribe + player_slot * 4) * 0x30 + ADDR(0x65550c, ((u8 *)&leaders + 20)) + title * 4) +
                       1;
              }
              if (leaders[(*(int *)(&setup_prev_player_tribe + player_slot * 4))].titles[title][1]
                  < 1) {
                *(ushort *)&leaders[(*(int *)(&setup_prev_player_tribe + player_slot * 4))].titles[title][1]
                     = ~*(ushort *)
                         (*(int *)(&setup_prev_player_tribe + player_slot * 4) * 0x30 + ADDR(0x65550e, ((u8 *)&leaders + 22)) + title * 4) +
                       1;
              }
            }
            game.human_players =
                 ~(byte)(1 << ((byte)leaders[*(int *)(&setup_prev_player_tribe + player_slot * 4)].color & 0x1f)) &
                 game.human_players;
          }
          try_level = 0xffffffff;
          /* inlined unwind funclet 00521807 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
          return choice;
        }
        game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
      }
      goto LAB_0051f1f6;
    }
    if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
      text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
      crt_strcpy(&text_string_args,net_connection_title);
      if (nm_server_canceled_count == 0) {
        popup_game_with_sprite(ADDR(0x6321a0, ((u8 *)&g.d_006321a0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      else {
        popup_game_with_sprite(ADDR(0x632194, ((u8 *)&g.d_00632194)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      result = 1;
      goto LAB_0052144f;
    }
    snd_play_effect(0x6a,0,0,0);
    if (in_game == 0) {
      setup_picwnd_close((ViewWindow *)&setup_picwnd);
    }
    game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
    if (2 < game_mode) {
      net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
    }
  } while( true );
}
#undef dlg_pending_idle_callback
#undef human_civ
#undef net_claimed_civs_mask
#undef net_connection_title
#undef net_host_flag
#undef net_timeout_seconds
#undef prefs_email_address
#undef prefs_gender
#undef prefs_tribe
#undef saved_turn_civ
#undef screen_height
#undef turn_resume_civ
#undef net_player_info_civ_i32
#undef net_player_info_leader_index_i32
#undef net_player_info_gender_i32
#undef net_player_info_has_names_i32
#undef net_player_info_has_titles_i32
#undef net_wait_start_ticks_i32
#undef email_default
#undef leader
#undef style2
#undef is_female
#undef input_text
#undef tries
#undef avail_count
#undef result
#undef sel_tribe
#undef dlg
#undef retry_tribe
#undef option
#undef leader2
#undef title
#undef cancelled
#undef wait_start
#undef seh_prev
#undef seh_handler
#undef try_level

/* 005218cb auto */
#define cd_music_available (*(int *)((u8 *)&g.d_0062b420))
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define ini_simultaneous_allowed (*(int *)((u8 *)&g.d_006c3160))
#define mp_chat_from_start (*(short *)((u8 *)&g.d_00654c7a))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_show_human_starts (*(short *)((u8 *)&g.d_00654c78))
#define mp_simultaneous_moves (*(i8 *)((u8 *)&g.d_006ad684))
#define mp_simultaneous_setting (*(short *)((u8 *)&g.d_00654c7c))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
#define prefs_mp_chat_from_start (*(short *)((u8 *)&g.d_0066654c))
#define prefs_mp_double_moves (*(short *)((u8 *)&g.d_00666600))
#define prefs_mp_double_production (*(short *)((u8 *)&g.d_006665fe))
#define prefs_mp_kill_on_retire (*(short *)((u8 *)&g.d_00666548))
#define prefs_mp_open_game (*(short *)((u8 *)&g.d_00666546))
#define prefs_mp_show_human_starts (*(short *)((u8 *)&g.d_0066654a))
#define prefs_mp_simultaneous_moves (*(short *)((u8 *)&g.d_0066654e))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define scenario_max_turns (*(short *)((u8 *)&g.d_0064bcb8))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_tech_paradigm (*(short *)((u8 *)&g.d_0064bcb2))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_new_game (*(i32 *)((u8 *)&g.d_0062c488))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(1080)))
#define opt (*(int *)(frame_ + FRAME_OFF(1836)))
#define dst (*(i8 (*)[260])(frame_ + FRAME_OFF(1840)))
#define difficulty2 (*(int *)(frame_ + FRAME_OFF(2100)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(2104)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2108)))
#define try_level (*(uint *)(frame_ + FRAME_OFF(2112)))
i32 __cdecl scenario_start_dialog(int game_mode)

{
  iptr load_result;
  i32 value;
  iptr text_result;
  int unit;
  i8 frame_[FRAME_OFF(2120)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  try_level = 0;
  palette_init(&palette);
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),1);
LAB_00521912:
  do {
    if (cd_music_available == 0) {
      snd_cd_stop();
      snd_play_effect(0x6b,0,1,0);
    }
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_flush_paint();
    load_result = game_load_dialog(1,game_mode,1);
    if (load_result != 0) {
      snd_play_effect(0x6a,0,0,0);
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&palette);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      wnd_flush_paint();
      try_level = try_level & 0xffffff00;
      /* inlined unwind funclet 00521faf */ { palette_destroy((GamePalette *)((iptr)&palette)); }
      try_level = 0xffffffff;
      /* inlined unwind funclet 00521fbb */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      value = 1;
LAB_00521fd1:
      return value;
    }
    path_set_extension((iptr)dst,ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x62cd24, ((u8 *)&g.d_0062cd24)));
    if (cd_music_available != 0) {
      snd_play_effect(0x6a,0,0,0);
    }
    game.game_options = prefs_game_options & 0xffff7fff;
    game.message_options = prefs_message_options;
    text_set_string_arg(0,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)));
    text_set_number_arg(0,(int)scenario_tech_paradigm);
    text_clear();
    value = game_turn_to_year((int)game.turn);
    text_append_year(value);
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    if (scenario_max_turns == 0) {
      text_append_year(2000);
    }
    else {
      value = game_turn_to_year((int)scenario_max_turns);
      text_append_year(value);
    }
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (cd_music_available != 0) {
      snd_menu_end();
    }
    dialog_init_default(&dlg);
    text_result = dialog_load_text(&dlg,(iptr)dst,ADDR(0x63226c, ((u8 *)&g.d_0063226c)),0x4008001);
    if (text_result == 0) goto code_r0x00521b37;
    unit = popup_game_flags(ADDR(0x632278, ((u8 *)&g.d_00632278)),1);
  } while (unit < 0);
  goto LAB_00521c07;
code_r0x00521b37:
  unit = (int)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((int)units[unit].owner == (int)scenario_objective_civ)) {
    dialog_add_sprite
              ((DialogOptionList *)&dlg,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0
               ,0);
  }
  unit = dlg_show_modal(&dlg,0);
  if (-1 < unit) {
LAB_00521c07:
    while( true ) {
      dlg_load_game_section(&dlg,ADDR(0x632288, ((u8 *)&g.d_00632288)),1);
      dialog_set_default_choice((DialogOptionList *)&dlg,(uint)game.difficulty);
      dialog_set_position
                ((DialogCore *)&dlg,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      difficulty2 = dlg_show_modal(&dlg,0);
      if (difficulty2 < 0) break;
      game.difficulty = (u8)difficulty2;
      if ((u8)difficulty2 == '\0') {
        game.game_options = game.game_options | 0x100;
      }
      else {
        game.game_options = game.game_options & 0xfffffeff;
      }
      while( true ) {
        saved_resume_new_game = 0;
        turn_resume_new_game = 0;
        dlg_checks_clear();
        dlg_check_set(0,(int)prefs_mp_open_game);
        dlg_check_set(1,(int)prefs_mp_kill_on_retire);
        dlg_check_set(2,(int)prefs_mp_show_human_starts);
        dlg_check_set(3,(int)prefs_mp_chat_from_start);
        dlg_check_set(4,(int)prefs_mp_double_production);
        dlg_check_set(5,(int)prefs_mp_double_moves);
        dialog_load_text_section(&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632294, ((u8 *)&g.d_00632294)),0,0,0,0,0,0);
        if (ini_simultaneous_allowed == 0) {
          mp_simultaneous_moves = 0;
          mp_simultaneous_setting = 0;
        }
        else {
          text_clear();
          text_append_label(0x364);
          dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
          dlg_check_set(6,(int)prefs_mp_simultaneous_moves);
        }
        if (((byte)dlg.style_flags & 4) != 0) {
          for (opt = 0; opt < (int)dlg.option_count; opt++) {
            dialog_set_option_checked
                      ((DialogOptionList *)&dlg,opt,
                       1 << ((byte)opt & 0x1f) & dlg_check_bits);
          }
        }
        dialog_set_position
                  ((DialogCore *)&dlg,
                   ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        unit = dlg_show_modal(&dlg,0);
        snd_play_effect(0x6a,0,0,0);
        if (unit < 0) break;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,0);
        mp_open_game = (short)value;
        prefs_mp_open_game = mp_open_game;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,1);
        mp_kill_civ_on_retire = (short)value;
        prefs_mp_kill_on_retire = mp_kill_civ_on_retire;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,2);
        mp_show_human_starts = (short)value;
        prefs_mp_show_human_starts = mp_show_human_starts;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,3);
        mp_chat_from_start = (short)value;
        prefs_mp_chat_from_start = mp_chat_from_start;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,4);
        mp_double_production = (short)value;
        prefs_mp_double_production = mp_double_production;
        value = dialog_option_is_checked((DialogOptionList *)&dlg,5);
        mp_double_moves = (short)value;
        prefs_mp_double_moves = mp_double_moves;
        if (ini_simultaneous_allowed != 0) {
          value = dialog_option_is_checked((DialogOptionList *)&dlg,6);
          mp_simultaneous_setting = (short)value;
          prefs_mp_simultaneous_moves = mp_simultaneous_setting;
        }
        if ((game_mode == 2) || (unit = setup_choose_game_timer(0), unit == 0)) {
          try_level = try_level & 0xffffff00;
          /* inlined unwind funclet 00521faf */ { palette_destroy((GamePalette *)((iptr)&palette)); }
          try_level = 0xffffffff;
          /* inlined unwind funclet 00521fbb */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
          value = 0;
          goto LAB_00521fd1;
        }
      }
    }
  }
  goto LAB_00521912;
}
#undef cd_music_available
#undef dlg_check_bits
#undef ini_simultaneous_allowed
#undef mp_chat_from_start
#undef mp_double_moves
#undef mp_double_production
#undef mp_kill_civ_on_retire
#undef mp_open_game
#undef mp_show_human_starts
#undef mp_simultaneous_moves
#undef mp_simultaneous_setting
#undef prefs_game_options
#undef prefs_message_options
#undef prefs_mp_chat_from_start
#undef prefs_mp_double_moves
#undef prefs_mp_double_production
#undef prefs_mp_kill_on_retire
#undef prefs_mp_open_game
#undef prefs_mp_show_human_starts
#undef prefs_mp_simultaneous_moves
#undef saved_resume_new_game
#undef scenario_max_turns
#undef scenario_objective_civ
#undef scenario_tech_paradigm
#undef screen_height
#undef turn_resume_new_game
#undef palette
#undef dlg
#undef opt
#undef dst
#undef difficulty2
#undef seh_prev
#undef seh_handler
#undef try_level

/* 00521fe0 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(i32 *)((u8 *)&g.d_0062c488))
#define civ (*(uptr *)(frame_ + FRAME_OFF(4)))
#define is_female (*(u8 *)(frame_ + FRAME_OFF(8)))
#define sex (*(iptr *)(frame_ + FRAME_OFF(12)))
#define name_text (*(i8 (*)[260])(frame_ + FRAME_OFF(16)))
#define has_default (*(int *)(frame_ + FRAME_OFF(276)))
#define player_idx (*(int *)(frame_ + FRAME_OFF(280)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(284)))
#define option (*(iptr *)(frame_ + FRAME_OFF(1040)))
#define govt (*(iptr *)(frame_ + FRAME_OFF(1044)))
#define option_civs (*(uptr (*)[8])(frame_ + FRAME_OFF(1048)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(1088)))
i32 __cdecl scenario_pick_human_civs(int num_players)

{
  iptr str;
  iptr choice;
  int result;
  i32 ret;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  try_level = 0;
  game.human_players = '\0';
  turn_resume_civ = 0;
  player_idx = 0;
  do {
    if (num_players <= player_idx) {
      saved_turn_civ = turn_resume_civ;
      human_civ = (iptr)turn_resume_civ;
      game.turn_civ = turn_resume_civ;
      saved_resume_new_game = 1;
      turn_resume_new_game = 1;
      try_level = 0xffffffff;
      /* inlined unwind funclet 00522617 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      ret = 0;
LAB_0052262d:
      return ret;
    }
    while( true ) {
      while( true ) {
        do {
          dlg_reset(&dlg,1);
          dialog_prepend_title_label((iptr)&dlg,player_idx + 0x25e);
          has_default = 0;
          for (civ = 1; (int)civ < 8; civ++) {
            if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
              text_clear();
              str = civ_name_plural(civ);
              text_append(str);
              text_append_space();
              text_append_lparen();
              str = civ_leader_name(civ);
              text_append(str);
              text_append_rparen();
              text_append_space();
              text_append_lparen();
              text_append_int((int)civs[civ].num_cities);
              text_append_space();
              text_append_label(0xc5);
              text_append(ADDR(0x6322a0, ((u8 *)&g.d_006322a0)));
              text_append_int((int)civs[civ].num_military_units);
              text_append_space();
              text_append_label(0xc4);
              text_append(ADDR(0x6322a4, ((u8 *)&g.d_006322a4)));
              option = dialog_add_option
                                   ((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
              option_civs[*(int *)(option + 4)] = civ;
              if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
                if (has_default == 0) {
                  has_default = 1;
                  dialog_set_default_choice
                            ((DialogOptionList *)&dlg,*(iptr *)(option + 4));
                }
              }
              else {
                dialog_set_option_disabled
                          ((DialogOptionList *)&dlg,*(iptr *)(option + 4),1);
              }
            }
          }
          choice = dlg_show_modal(&dlg,0);
          if (choice < 0) {
            try_level = 0xffffffff;
            /* inlined unwind funclet 00522617 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
            ret = 1;
            goto LAB_0052262d;
          }
          human_civ = option_civs[choice];
          (*(i8 *)((char *)&civ + 0)) = (byte)human_civ;
          if (player_idx == 0) {
            turn_resume_civ = (byte)civ;
          }
          game.human_players = game.human_players | (byte)(1 << ((byte)civ & 0x1f));
          game.player_civ = (byte)civ;
          game.turn_civ = (byte)civ;
          game.game_options = game.game_options & 0xfffffeff;
          result = dialog_load_text_section
                            (&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6322a8, ((u8 *)&g.d_006322a8)),0x17,(iptr)&civ_names[((char)(byte)civ)].leader_name,0,0,0,1);
        } while (result != 0);
        dialog_prepend_title_label((iptr)&dlg,player_idx + 0x25e);
        result = dialog_run_modal(&dlg,(iptr)name_text,0);
        if (result == 0) break;
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
      }
      crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,name_text);
      dlg_load_game_section(&dlg,ADDR(0x6322b0, ((u8 *)&g.d_006322b0)),1);
      dialog_prepend_title_label((iptr)&dlg,player_idx + 0x25e);
      dialog_set_default_choice
                ((DialogOptionList *)&dlg,(uint)leaders[civs[game.player_civ].tribe].female);
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      result = dlg_show_modal(&dlg,0);
      snd_play_effect(0x6a,0,0,0);
      if (-1 < result) break;
      game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
    }
    is_female = (u8)result;
    leaders[civs[game.player_civ].tribe].female = is_female;
    civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
    if (result != 0) {
      civs[human_civ].flags = civs[human_civ].flags | 0x200;
    }
    for (govt = 0; govt < 7; govt++) {
      for (sex = 0; sex < 2; sex++) {
        leaders[civs[game.player_civ].tribe].titles[govt][sex] =
             (short)(&government_titles[govt].male)[sex];
      }
    }
    player_idx++;
  } while( true );
}
#undef human_civ
#undef saved_resume_new_game
#undef saved_turn_civ
#undef screen_height
#undef turn_resume_civ
#undef turn_resume_new_game
#undef civ
#undef is_female
#undef sex
#undef name_text
#undef has_default
#undef player_idx
#undef dlg
#undef option
#undef govt
#undef option_civs
#undef seh_prev
#undef seh_handler
#undef try_level

/* 0052263c auto */
void __cdecl setup_show_side_picture(int picture_id,int reset)

{
  if (reset != 0) {
    setup_side_picture_id = 5;
  }
  if (picture_id == -1) {
    if (setup_side_picture_id == 5) {
      setup_side_picture_id = 7;
    }
    else if (setup_side_picture_id == 6) {
      setup_side_picture_id = 5;
    }
    else if (setup_side_picture_id == 7) {
      setup_side_picture_id = 6;
    }
    setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,setup_side_picture_id);
  }
  else {
    setup_picwnd_show((ViewWindow *)&setup_picwnd,2,6,picture_id);
  }
  return;
}

/* 005226fa auto */
int __cdecl setup_next_dialog_x(int reset)

{
  int x;
  
  if (reset != 0) {
    setup_dialog_pos_state = 1;
  }
  switch(setup_dialog_pos_state) {
  case 1:
    setup_dialog_pos_state = 3;
    x = -999;
    break;
  case 2:
    setup_dialog_pos_state = 1;
    x = ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1;
    break;
  case 3:
    setup_dialog_pos_state = 4;
    x = -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1);
    break;
  case 4:
    setup_dialog_pos_state = 2;
    x = -999;
    break;
  default:
    x = -999;
  }
  return x;
}

/* 005227e3 auto */
#define net_max_players (*(int *)((u8 *)&g.d_006c3164))
#define prefs_hotseat_players_choice (*(short *)((u8 *)&g.d_006665d8))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define num_players (*(int *)(frame_ + FRAME_OFF(764)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(776)))
int __cdecl setup_choose_hotseat_players(void)

{
  int result;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  try_level = 0;
  if (game.multiplayer < 3) {
    setup_show_side_picture(0xffffffff,0);
    dlg_load_game_section(&dlg,ADDR(0x6322b8, ((u8 *)&g.d_006322b8)),1);
    if (4 < net_max_players) {
      text_clear();
      text_append_label(0x365);
      dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),3,0);
    }
    if (5 < net_max_players) {
      text_clear();
      text_append_label(0x366);
      dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),4,0);
    }
    if (6 < net_max_players) {
      text_clear();
      text_append_label(0x367);
      dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),5,0);
    }
    dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_hotseat_players_choice);
    dialog_set_position
              ((DialogCore *)&dlg,
               -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    switch(game.num_enemies) {
    case 1:
      dialog_set_option_disabled((DialogOptionList *)&dlg,1,1);
    case 2:
      dialog_set_option_disabled((DialogOptionList *)&dlg,2,1);
    case 3:
      if (4 < net_max_players) {
        dialog_set_option_disabled((DialogOptionList *)&dlg,3,1);
      }
    case 4:
      if (5 < net_max_players) {
        dialog_set_option_disabled((DialogOptionList *)&dlg,4,1);
      }
    case 5:
      if (6 < net_max_players) {
        dialog_set_option_disabled((DialogOptionList *)&dlg,5,1);
      }
    }
    if (prefs_hotseat_players_choice + 1 < (int)(uint)game.num_enemies) {
      dialog_set_default_choice((DialogOptionList *)&dlg,(int)prefs_hotseat_players_choice);
    }
    num_players = dlg_show_modal(&dlg,0);
    if (num_players < 0) {
      try_level = 0xffffffff;
      /* inlined unwind funclet 00522b06 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      result = 0;
      goto LAB_00522b1c;
    }
    prefs_hotseat_players_choice = (short)num_players;
    num_players += 2;
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((ViewWindow *)&setup_picwnd);
  }
  else {
    num_players = 0;
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        num_players++;
      }
    }
  }
  result = num_players;
  try_level = 0xffffffff;
  /* inlined unwind funclet 00522b06 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
LAB_00522b1c:
  return result;
}
#undef net_max_players
#undef prefs_hotseat_players_choice
#undef screen_height
#undef civ
#undef dlg
#undef num_players
#undef seh_prev
#undef seh_handler
#undef try_level

/* 00522b2b auto */
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_max_players (*(int *)((u8 *)&g.d_006c3164))
#define human_count (*(int *)(frame_ + FRAME_OFF(4)))
#define civ (*(int *)(frame_ + FRAME_OFF(8)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define saved_humans (*(uint *)(frame_ + FRAME_OFF(772)))
#define saved_player_civ (*(int *)(frame_ + FRAME_OFF(776)))
#define ai_count (*(int *)(frame_ + FRAME_OFF(780)))
#define alive_count (*(int *)(frame_ + FRAME_OFF(784)))
#define view_idx (*(int *)(frame_ + FRAME_OFF(788)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(792)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(800)))
void __cdecl game_join_dialog(void)

{
  int picked;
  iptr civ_name;
  iptr saved_human_civ;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  saved_human_civ = human_civ;
  try_level = 0;
  saved_player_civ = (int)game.player_civ;
  saved_humans = (uint)game.human_players;
  game.human_players = hotseat_human_players;
  mp_turn_timer_stop(1);
  city_window_close();
  wnd_hide((WndBase *)&status_window_wnd);
  wnd_hide((WndBase *)&minimap_wnd);
  for (view_idx = 0; view_idx < 8; view_idx++) {
    if (*(short *)(&map_view_open_flags + view_idx * 0x3f0) != 0) {
      wnd_hide((WndBase *)(&map_view_wnds + view_idx * 0x3f0));
    }
  }
  wnd_flush_paint();
  alive_count = 0;
  ai_count = 0;
  human_count = 0;
  for (civ = 1; civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
      alive_count++;
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        ai_count++;
      }
      else {
        human_count++;
      }
    }
  }
  if (net_max_players == human_count) {
    text_set_number_arg(0,net_max_players);
    popup_game(ADDR(0x6322c4, ((u8 *)&g.d_006322c4)));
  }
  else if (ai_count == 0) {
    popup_game(ADDR(0x6322d0, ((u8 *)&g.d_006322d0)));
  }
  else {
    picked = setup_join_pick_civ(human_count - 1);
    if (picked == 0) {
      civ_name = civ_name_plural(human_civ);
      text_set_string_arg_b(0,civ_name);
      popup_game(ADDR(0x6322dc, ((u8 *)&g.d_006322dc)));
    }
  }
  game.player_civ = (i8)saved_player_civ;
  hotseat_human_players = game.human_players;
  game.human_players = (u8)saved_humans;
  human_civ = saved_human_civ;
  window_show((WindowObjectView *)&status_window);
  window_show((WindowObjectView *)&minimap_window);
  for (view_idx = 0; view_idx < 8; view_idx++) {
    if (*(short *)(&map_view_open_flags + view_idx * 0x3f0) != 0) {
      window_show((WindowObjectView *)(&map_views + view_idx * 0x3f0));
    }
  }
  mp_turn_timer_resume(1);
  try_level = 0xffffffff;
  /* inlined unwind funclet 00522dd6 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  return;
}
#undef hotseat_human_players
#undef human_civ
#undef net_max_players
#undef human_count
#undef civ
#undef dlg
#undef saved_humans
#undef saved_player_civ
#undef ai_count
#undef alive_count
#undef view_idx
#undef seh_prev
#undef seh_handler
#undef try_level

/* 00522f8f auto */
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define setup_select_opponents (*(int *)((u8 *)&g.d_00631ee4))
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(764)))
#define i (*(int *)(frame_ + FRAME_OFF(768)))
#define opponent_num (*(int *)(frame_ + FRAME_OFF(772)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(776)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl setup_choose_opponents(int num_humans)

{
  byte sign;
  int rnd;
  i32 dlg_x;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  try_level = 0;
  game.civs_alive = game.human_players | 1;
  for (leader = 1; leader < 8; leader++) {
    if ((1 << ((byte)leader & 0x1f) & (uint)game.human_players) == 0) {
      if (leaders[leader].leader_name < 1) {
        leaders[leader].leader_name = ~leaders[leader].leader_name + 1;
      }
      if (leaders[leader].plural < 1) {
        leaders[leader].plural = ~leaders[leader].plural + 1;
      }
      if (leaders[leader].adjective < 1) {
        leaders[leader].adjective = ~leaders[leader].adjective + 1;
      }
      for (i = 0; i < 7; i++) {
        if (leaders[leader].titles[i][0] < 1) {
          *(ushort *)&leaders[leader].titles[i][0] =
               ~*(ushort *)&leaders[leader].titles[i][0] + 1;
        }
        if (leaders[leader].titles[i][1] < 1) {
          *(ushort *)&leaders[leader].titles[i][1] =
               ~*(ushort *)&leaders[leader].titles[i][1] + 1;
        }
      }
    }
  }
  for (i = 0; i < (int)((game.num_enemies + 1) - num_humans); i++) {
    rnd = _rand();
    sign = (byte)(rnd >> 0x1f);
    (*(i8 *)((char *)&civ + 0)) = (((byte)rnd ^ sign) - sign & 7 ^ sign) - sign;
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
      game.civs_alive = game.civs_alive | (byte)(1 << ((byte)civ & 0x1f));
    }
    else {
      i--;
    }
  }
  if (setup_select_opponents != 0) {
    opponent_num = 0;
    for (civ = 1; civ < 8; civ++) {
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
         ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) {
        opponent_num++;
        text_set_number_arg(0,opponent_num);
        setup_show_side_picture(9,0);
        dlg_load_game_section(&dlg,ADDR(0x6322e8, ((u8 *)&g.d_006322e8)),1);
        *(i32 *)(dlg.option_list + 4) = 0x15;
        for (leader = 0; leader < 0x15; leader++) {
          if (leaders[leader].color == civ) {
            text_clear();
            text_append_string_id((int)leaders[leader].plural);
            text_append_space();
            text_append_lparen();
            text_append_string_id((int)leaders[leader].leader_name);
            text_append_rparen();
            dialog_add_option((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),leader,0);
          }
        }
        rnd = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
        dlg_x = setup_next_dialog_x(0);
        dialog_set_position((DialogCore *)&dlg,dlg_x,rnd);
        leader = dlg_show_modal(&dlg,0);
        snd_play_effect(0x6a,0,0,0);
        setup_picwnd_close((ViewWindow *)&setup_picwnd);
        if (leader < 0) {
          try_level = 0xffffffff;
          /* inlined unwind funclet 005233d8 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
          goto LAB_005233ee;
        }
        if (leader < 0x15) {
          (&setup_chosen_leaders)[civ] = (byte)leader;
        }
      }
    }
  }
  try_level = 0xffffffff;
  /* inlined unwind funclet 005233d8 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
LAB_005233ee:
  return;
}
#undef screen_height
#undef setup_select_opponents
#undef civ
#undef dlg
#undef leader
#undef i
#undef opponent_num
#undef seh_prev
#undef seh_handler
#undef try_level

/* 00523f02 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define is_female (*(u8 *)(frame_ + FRAME_OFF(8)))
#define sex (*(iptr *)(frame_ + FRAME_OFF(12)))
#define name_text (*(i8 (*)[260])(frame_ + FRAME_OFF(16)))
#define opt_idx (*(int *)(frame_ + FRAME_OFF(276)))
#define avail_count (*(int *)(frame_ + FRAME_OFF(280)))
#define opt_count (*(int *)(frame_ + FRAME_OFF(284)))
#define sel_idx (*(int *)(frame_ + FRAME_OFF(288)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(292)))
#define option (*(byte * *)(frame_ + FRAME_OFF(1048)))
#define govt (*(iptr *)(frame_ + FRAME_OFF(1052)))
#define option_civs (*(iptr (*)[8])(frame_ + FRAME_OFF(1056)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1088)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1092)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(1096)))
i32 __cdecl setup_join_pick_civ(int player_idx)

{
  iptr str;
  iptr choice;
  int result;
  iptr pw_ok;
  int civ;
  i32 ret;
  i32 arg_b;
  i32 arg_c;
  i32 arg_d;
  i8 frame_[FRAME_OFF(1104)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  try_level = 0;
  sel_idx = 0;
  do {
    dlg_reset(&dlg,1);
    dialog_prepend_title_label((iptr)&dlg,player_idx + 0x25f);
    opt_idx = 0;
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        str = civ_name_plural(civ2);
        text_append(str);
        text_append_space();
        text_append_lparen();
        str = civ_leader_name(civ2);
        text_append(str);
        text_append_rparen();
        text_append_space();
        text_append_lparen();
        text_append_int((int)civs[civ2].num_cities);
        text_append_space();
        text_append_label(0xc5);
        text_append(ADDR(0x632330, ((u8 *)&g.d_00632330)));
        text_append_int((int)civs[civ2].num_military_units);
        text_append_space();
        text_append_label(0xc4);
        text_append(ADDR(0x632334, ((u8 *)&g.d_00632334)));
        civ = opt_idx;
        opt_idx++;
        option = (byte *)dialog_add_option
                                     ((DialogOptionList *)&dlg,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
        option_civs[*(int *)(option + 4)] = civ2;
      }
    }
    opt_count = opt_idx;
    avail_count = 0;
    for (opt_idx = 0; opt_idx < opt_count; opt_idx++) {
      option = (byte *)dialog_find_option((DialogOptionList *)&dlg,opt_idx);
      if (option != (byte *)0x0) {
        (*(i8 *)((char *)&civ2 + 0)) = (byte)option_civs[*(int *)(option + 4)];
        if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
          avail_count++;
          dialog_set_option_disabled((DialogOptionList *)&dlg,*(iptr *)(option + 4),0)
          ;
          if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
            radiogrp_enable_item
                      ((RadioGroupEnableView *)dlg.radio_group,*(iptr *)(option + 4));
          }
        }
        else {
          dialog_set_option_disabled((DialogOptionList *)&dlg,*(iptr *)(option + 4),1)
          ;
          if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
            radiogrp_disable_item
                      ((RadioGroupDisableView *)dlg.radio_group,*(iptr *)(option + 4));
          }
        }
      }
    }
    sel_idx = 0;
    for (opt_idx = 0; opt_idx < opt_count; opt_idx++) {
      option = (byte *)dialog_find_option((DialogOptionList *)&dlg,sel_idx);
      if ((option != (byte *)0x0) && ((*option & 1) == 0)) {
        dialog_set_default_choice((DialogOptionList *)&dlg,*(iptr *)(option + 4));
        if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
          radiogrp_set_selected
                    ((RadioGroupSetSelView *)dlg.radio_group,*(i32 *)(option + 4));
        }
        break;
      }
      sel_idx++;
      if (sel_idx == opt_count) {
        sel_idx = 0;
      }
    }
    choice = dlg_show_modal(&dlg,0);
    if (choice < 0) {
      try_level = 0xffffffff;
      /* inlined unwind funclet 005246bf */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      ret = 1;
LAB_005246d5:
      return ret;
    }
    civ = option_civs[choice];
    (*(i8 *)((char *)&civ2 + 0)) = (byte)civ;
    game.human_players = game.human_players | (byte)(1 << ((byte)civ2 & 0x1f));
    arg_d = 1;
    arg_c = 0;
    arg_b = 0;
    ret = 0;
    human_civ = civ;
    str = civ_leader_name(civ);
    result = dialog_load_text_section
                      (&dlg,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632338, ((u8 *)&g.d_00632338)),0x17,str,ret,arg_b,arg_c,arg_d);
    if (result == 0) {
      dialog_prepend_title_label((iptr)&dlg,player_idx + 0x25f);
      result = dialog_run_modal(&dlg,(iptr)name_text,0);
      if (result == 0) {
        crt_strcpy((iptr)&civ_names[civ].leader_name,name_text);
        if (0 < leaders[civs[civ].tribe].leader_name) {
          leaders[civs[civ].tribe].leader_name = -leaders[civs[civ].tribe].leader_name;
        }
        pw_ok = civ_check_password(human_civ);
        if (pw_ok == 0) {
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ2 & 0x1f));
        }
        else {
          dlg_load_game_section(&dlg,ADDR(0x632340, ((u8 *)&g.d_00632340)),1);
          dialog_prepend_title_label((iptr)&dlg,player_idx + 0x25f);
          dialog_set_default_choice
                    ((DialogOptionList *)&dlg,(uint)leaders[civs[game.player_civ].tribe].female)
          ;
          dialog_set_position
                    ((DialogCore *)&dlg,0xfffffc19,
                     -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) +
                      1));
          civ = dlg_show_modal(&dlg,0);
          snd_play_effect(0x6a,0,0,0);
          if (-1 < civ) {
            is_female = (u8)civ;
            leaders[civs[game.player_civ].tribe].female = is_female;
            civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
            if (civ != 0) {
              civs[human_civ].flags = civs[human_civ].flags | 0x200;
            }
            for (govt = 0; govt < 7; govt++) {
              for (sex = 0; sex < 2; sex++) {
                leaders[civs[game.player_civ].tribe].titles[govt][sex] = (short)(&government_titles[govt].male)[sex];
              }
            }
            try_level = 0xffffffff;
            /* inlined unwind funclet 005246bf */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
            ret = 0;
            goto LAB_005246d5;
          }
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ2 & 0x1f));
        }
      }
      else {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ2 & 0x1f));
      }
    }
  } while( true );
}
#undef human_civ
#undef screen_height
#undef civ2
#undef is_female
#undef sex
#undef name_text
#undef opt_idx
#undef avail_count
#undef opt_count
#undef sel_idx
#undef dlg
#undef option
#undef govt
#undef option_civs
#undef seh_prev
#undef seh_handler
#undef try_level

/* 00548df0 auto */
void __cdecl events_editor_focus_redraw(void)

{
  HWND hWnd;
  
  hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0xad0));
  SetFocus(hWnd);
  events_editor_draw((ViewWindow *)active_editor_wnd);
  return;
}

/* 00548e23 auto */
#define action_bit (*(uint *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
#define line (*(char (*)[80])(frame_ + FRAME_OFF(12)))
/* WARNING: Type propagation algorithm not settling */

void __cdecl events_write_actions(iptr fp,iptr event)

{
  int rc;
  uint action;
  i32 civ_name;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  rc = _fputs(s__THEN_0063257c,(FILE *)fp);
  if (((rc == -1) || (action_bit = 1, event == 0)) || (*(int *)(event + 4) == 0)) {
    return;
  }
  do {
    action = *(uint *)(event + 4) & action_bit;
    if (action < 9) {
      if (action == 8) {
        rc = _fputs(s_CHANGEMONEY_00632680,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_receiver__s_00632690,*(i32 *)(event + 0x174));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_amount__d_006326a0,*(i32 *)(event + 0x17c));
        rc = _fputs(line,(FILE *)fp);
      }
      else if (action == 1) {
        rc = _fputs(s_TEXT_00632584,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        for (i = 0; (i < 0x14 && (*(int *)(event + 0x38 + i * 4) != 0));
            i = i + 1) {
          rc = _fputs(*(char **)(event + 0x38 + i * 4),(FILE *)fp);
          if (rc == -1) {
            return;
          }
          rc = _fputs(&events_text_line_newline_str,(FILE *)fp);
          if (rc == -1) {
            return;
          }
        }
        rc = _fputs(s_ENDTEXT_00632590,(FILE *)fp);
      }
      else if (action == 2) {
        rc = _fputs(s_MOVEUNIT_0063259c,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_unit__s_006325a8,*(i32 *)(event + 0x90));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_owner__s_006325b4,*(i32 *)(event + 0x88));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        rc = _fputs(s_maprect_006325c0,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        for (i = 0; i < 4; i++) {
          _sprintf(line,s__d__d_006325cc,*(i32 *)(event + 0x9c + i * 8),
                   *(i32 *)(event + 0xa0 + i * 8));
          if (i < 3) {
            crt_strcat(line,&events_moveunit_rect_sep_str);
          }
          rc = _fputs(line,(FILE *)fp);
          if (rc == -1) {
            return;
          }
        }
        rc = _fputs(s_moveto_006325d8,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s__d__d_006325e4,*(i32 *)(event + 0xbc),
                 *(i32 *)(event + 0xc0));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        if (*(int *)(event + 0x98) == -2) {
          _sprintf(line,s_numbertomove_ALL_006325ec);
        }
        else {
          _sprintf(line,s_numbertomove__d_00632600,*(i32 *)(event + 0x98));
        }
        rc = _fputs(line,(FILE *)fp);
      }
      else {
        if (action != 4) goto LAB_005499f7;
        rc = _fputs(s_CREATEUNIT_00632614,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_unit__s_00632620,*(i32 *)(event + 0xdc));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_owner__s_0063262c,*(i32 *)(event + 0xd4));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_veteran__s_00632640,
                 &events_veteran_yes_no_strs + ((*(int *)(event + 0x138) != 0) - 1 & 4));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_homecity__s_0063264c,*(i32 *)(event + 0x13c));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        rc = _fputs(s_locations_0063265c,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        for (i = 0; i < *(int *)(event + 0x134); i++) {
          _sprintf(line,s__d__d_00632668,*(i32 *)(event + 0xe4 + i * 8),
                   *(i32 *)(event + 0xe8 + i * 8));
          rc = _fputs(line,(FILE *)fp);
          if (rc == -1) {
            return;
          }
        }
        rc = _fputs(s_endlocations_00632670,(FILE *)fp);
      }
joined_r0x0054934c:
      if (rc == -1) {
        return;
      }
    }
    else {
      if (0x20 < action) {
        if (action < 0x81) {
          if (action == 0x80) {
            rc = _fputs(s_PLAYCDTRACK_00632700,(FILE *)fp);
            if (rc == -1) {
              return;
            }
            _sprintf(line,&events_cd_track_fmt,*(i32 *)(event + 0x188));
            rc = _fputs(line,(FILE *)fp);
          }
          else {
            if (action != 0x40) goto LAB_005499f7;
            rc = _fputs(s_JUSTONCE_006326e4,(FILE *)fp);
          }
        }
        else if (action < 0x201) {
          if (action == 0x200) {
            rc = _fputs(s_CHANGETERRAIN_00632728,(FILE *)fp);
            if (rc == -1) {
              return;
            }
            _sprintf(line,s_terraintype__d_00632738,*(i32 *)(event + 0x18c));
            rc = _fputs(line,(FILE *)fp);
            if (rc == -1) {
              return;
            }
            rc = _fputs(s_maprect_00632748,(FILE *)fp);
            if (rc == -1) {
              return;
            }
            for (i = 0; i < 4; i++) {
              _sprintf(line,s__d__d_00632754,*(i32 *)(event + 400 + i * 8),
                       *(i32 *)(event + 0x194 + i * 8));
              if (i < 3) {
                crt_strcat(line,&events_terrain_rect_sep_str);
              }
              rc = _fputs(line,(FILE *)fp);
              if (rc == -1) {
                return;
              }
            }
            rc = _fputs(&events_terrain_rect_end_str,(FILE *)fp);
          }
          else {
            if (action != 0x100) goto LAB_005499f7;
            rc = _fputs(s_DONTPLAYWONDERS_00632714,(FILE *)fp);
          }
        }
        else if (action == 0x400) {
          rc = _fputs(s_DESTROYACIVILIZATION_00632764,(FILE *)fp);
          if (rc == -1) {
            return;
          }
          if (*(int *)(event + 0x1b0) < 0) {
            if ((*(byte *)(event + 1) & 1) == 0) {
              if (*(int *)(event + 0x1b0) == -3) {
                _sprintf(line,s_whom_TRIGGERATTACKER_006327a0);
              }
              else {
                _sprintf(line,s_whom_TRIGGERDEFENDER_006327b8);
              }
            }
            else {
              _sprintf(line,s_whom_TRIGGERRECEIVER_00632788);
            }
          }
          else {
            civ_name = civ_name_plural(*(iptr *)(event + 0x1b0));
            _sprintf(line,s_whom__s_0063277c,civ_name);
          }
          rc = _fputs(line,(FILE *)fp);
        }
        else if (action == 0x800) {
          rc = _fputs(s_GIVETECHNOLOGY_006327d0,(FILE *)fp);
          if (rc == -1) {
            return;
          }
          if (*(int *)(event + 0x1b8) < 0) {
            if ((*(byte *)(event + 1) & 1) == 0) {
              if (*(int *)(event + 0x1b8) == -3) {
                _sprintf(line,s_receiver_TRIGGERATTACKER_0063280c);
              }
              else {
                _sprintf(line,s_receiver_TRIGGERDEFENDER_00632828);
              }
            }
            else {
              _sprintf(line,s_receiver_TRIGGERRECEIVER_006327f0);
            }
          }
          else {
            civ_name = civ_name_plural(*(iptr *)(event + 0x1b8));
            _sprintf(line,s_receiver__s_006327e0,civ_name);
          }
          rc = _fputs(line,(FILE *)fp);
          if (rc == -1) {
            return;
          }
          _sprintf(line,s_technology__d_00632844,*(i32 *)(event + 0x1b4));
          rc = _fputs(line,(FILE *)fp);
        }
        else {
          if (action != 0x2000) goto LAB_005499f7;
          rc = _fputs(s_HASTRIGGERED_006326f0,(FILE *)fp);
        }
        goto joined_r0x0054934c;
      }
      if (action == 0x20) {
        rc = _fputs(s_MAKEAGGRESSION_006326c0,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_who__s_006326d0,*(i32 *)(event + 0xcc));
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_whom__s_006326d8,*(i32 *)(event + 0xc4));
        rc = _fputs(line,(FILE *)fp);
        goto joined_r0x0054934c;
      }
      if (action == 0x10) {
        rc = _fputs(s_PLAYWAVEFILE_006326ac,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,&events_wave_file_fmt,*(i32 *)(event + 0x184));
        rc = _fputs(line,(FILE *)fp);
        goto joined_r0x0054934c;
      }
    }
LAB_005499f7:
    action_bit = action_bit << 1;
    if (action_bit == 0x8000) {
      return;
    }
  } while( true );
}
#undef action_bit
#undef i
#undef line

/* 00549aee auto */
#define event (*(uint * *)(frame_ + FRAME_OFF(0)))
#define line (*(char (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl events_write_list(iptr fp)

{
  uint trigger;
  int rc;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  event = (uint *)events_list_head;
  do {
    if (event == (uint *)0x0) {
      _fputs(&events_list_end_str,(FILE *)fp);
      return;
    }
    rc = _fputs(s__IF_00632854,(FILE *)fp);
    if (rc == -1) {
      return;
    }
    trigger = *event;
    if (trigger < 9) {
      if (trigger == 8) {
        rc = _fputs(s_TURNINTERVAL_006328e0,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_interval__d_006328f0,event[0xb]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
      }
      else if (trigger == 1) {
        rc = _fputs(s_UNITKILLED_0063285c,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_unit__s_00632868,event[2]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_attacker__s_00632874,event[5]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_defender__s_00632884,event[8]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
      }
      else if (trigger == 2) {
        rc = _fputs(s_CITYTAKEN_00632894,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_city__s_006328a0,event[4]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_attacker__s_006328ac,event[5]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_defender__s_006328bc,event[8]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
      }
      else if (trigger == 4) {
        rc = _fputs(s_TURN_006328cc,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_turn__d_006328d4,event[0xb]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
      }
    }
    else {
      switch(trigger) {
      case 0x10:
        rc = _fputs(s_NEGOTIATION_00632900,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_talker__s_00632910,event[5]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_talkertype__0063291c);
        if (event[7] == 1) {
          crt_strcat(line,s_Human_00632928);
        }
        if (event[7] == 2) {
          crt_strcat(line,s_Computer_00632930);
        }
        if (event[7] == 4) {
          crt_strcat(line,s_HumanOrComputer_0063293c);
        }
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_listener__s_00632950,event[8]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_listenertype__00632960);
        if (event[10] == 1) {
          crt_strcat(line,s_Human_00632970);
        }
        if (event[10] == 2) {
          crt_strcat(line,s_Computer_00632978);
        }
        if (event[10] == 4) {
          crt_strcat(line,s_HumanOrComputer_00632984);
        }
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
        break;
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x2a:
      case 0x2b:
      case 0x2c:
      case 0x2d:
      case 0x2e:
      case 0x2f:
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
      case 0x3a:
      case 0x3b:
      case 0x3c:
      case 0x3d:
      case 0x3e:
      case 0x3f:
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5b:
      case 0x5c:
      case 0x5d:
      case 0x5e:
      case 0x5f:
      case 0x60:
      case 0x61:
      case 0x62:
      case 99:
      case 100:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
      case 0x7b:
      case 0x7c:
      case 0x7d:
      case 0x7e:
      case 0x7f:
      case 0x81:
      case 0x82:
      case 0x83:
      case 0x84:
      case 0x85:
      case 0x86:
      case 0x87:
      case 0x88:
      case 0x89:
      case 0x8a:
      case 0x8b:
      case 0x8c:
      case 0x8d:
      case 0x8e:
      case 0x8f:
      case 0x90:
      case 0x91:
      case 0x92:
      case 0x93:
      case 0x94:
      case 0x95:
      case 0x96:
      case 0x97:
      case 0x98:
      case 0x99:
      case 0x9a:
      case 0x9b:
      case 0x9c:
      case 0x9d:
      case 0x9e:
      case 0x9f:
      case 0xa0:
      case 0xa1:
      case 0xa2:
      case 0xa3:
      case 0xa4:
      case 0xa5:
      case 0xa6:
      case 0xa7:
      case 0xa8:
      case 0xa9:
      case 0xaa:
      case 0xab:
      case 0xac:
      case 0xad:
      case 0xae:
      case 0xaf:
      case 0xb0:
      case 0xb1:
      case 0xb2:
      case 0xb3:
      case 0xb4:
      case 0xb5:
      case 0xb6:
      case 0xb7:
      case 0xb8:
      case 0xb9:
      case 0xba:
      case 0xbb:
      case 0xbc:
      case 0xbd:
      case 0xbe:
      case 0xbf:
      case 0xc0:
      case 0xc1:
      case 0xc2:
      case 0xc3:
      case 0xc4:
      case 0xc5:
      case 0xc6:
      case 199:
      case 200:
      case 0xc9:
      case 0xca:
      case 0xcb:
      case 0xcc:
      case 0xcd:
      case 0xce:
      case 0xcf:
      case 0xd0:
      case 0xd1:
      case 0xd2:
      case 0xd3:
      case 0xd4:
      case 0xd5:
      case 0xd6:
      case 0xd7:
      case 0xd8:
      case 0xd9:
      case 0xda:
      case 0xdb:
      case 0xdc:
      case 0xdd:
      case 0xde:
      case 0xdf:
      case 0xe0:
      case 0xe1:
      case 0xe2:
      case 0xe3:
      case 0xe4:
      case 0xe5:
      case 0xe6:
      case 0xe7:
      case 0xe8:
      case 0xe9:
      case 0xea:
      case 0xeb:
      case 0xec:
      case 0xed:
      case 0xee:
      case 0xef:
      case 0xf0:
      case 0xf1:
      case 0xf2:
      case 0xf3:
      case 0xf4:
      case 0xf5:
      case 0xf6:
      case 0xf7:
      case 0xf8:
      case 0xf9:
      case 0xfa:
      case 0xfb:
      case 0xfc:
      case 0xfd:
      case 0xfe:
      case 0xff:
        break;
      case 0x20:
        rc = _fputs(s_SCENARIOLOADED_00632998,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
        break;
      case 0x40:
        rc = _fputs(s_RANDOMTURN_006329a8,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_denominator__d_006329b4,event[0xc]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
        break;
      case 0x80:
        rc = _fputs(s_NOSCHISM_006329c4,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_defender__s_006329d0,event[8]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
        break;
      case 0x100:
        rc = _fputs(s_RECEIVEDTECHNOLOGY_006329e0,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_technology__d_006329f4,event[0xd]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        _sprintf(line,s_receiver__s_00632a04,event[8]);
        rc = _fputs(line,(FILE *)fp);
        if (rc == -1) {
          return;
        }
        events_write_actions(fp,(iptr)event);
      }
    }
    rc = _fputs(s__ENDIF_00632a14,(FILE *)fp);
    if (rc == -1) {
      return;
    }
    event = (uint *)event[0x6f];
  } while( true );
}
#undef event
#undef line

/* 0054a4c4 auto */
#define ok (*(i32 *)(frame_ + FRAME_OFF(0)))
#define src_fp (*(FILE * *)(frame_ + FRAME_OFF(4)))
#define dst_fp (*(FILE * *)(frame_ + FRAME_OFF(8)))
#define saved_cwd (*(char (*)[260])(frame_ + FRAME_OFF(12)))
#define filename (*(i8 (*)[16])(frame_ + FRAME_OFF(272)))
#define s (*(char (*)[260])(frame_ + FRAME_OFF(288)))
i32 __cdecl events_write_file(void)

{
  int rc;
  char *got;
  i8 frame_[FRAME_OFF(552)] __attribute__((aligned(8)));  /* original stack frame */
  
  src_fp = (FILE *)0x0;
  dst_fp = (FILE *)0x0;
  crt_strcpy(filename,s_EVENTS__00632a20);
  crt_strcat(filename,&lang_file_ext);
  ok = 0;
  __getcwd(saved_cwd,0x104);
  __chdir(&scenario_dir_path);
  rc = file_exists(ADDR(0x632a28, ((u8 *)&g.d_00632a28)));
  if (((rc == 0) || (rc = crt_remove(s_EVENTS_BAK_00632a34), rc == 0)) &&
     ((rc = file_exists((iptr)filename), rc == 0 ||
      (rc = crt_rename(filename,s_EVENTS_BAK_00632a40), rc == 0)))) {
    src_fp = (FILE *)file_open_path(ADDR(0x632a50, ((u8 *)&g.d_00632a50)),ADDR(0x632a4c, ((u8 *)&g.d_00632a4c)));
    dst_fp = (FILE *)file_open_path((iptr)filename,ADDR(0x632a5c, ((u8 *)&g.d_00632a5c)));
    if (dst_fp != (FILE *)0x0) {
      if (src_fp == (FILE *)0x0) {
        rc = _fputs(s__BEGINEVENTS_00632a70,dst_fp);
        if (rc == -1) goto LAB_0054a7eb;
      }
      else {
        do {
          got = _fgets(s,0x100,src_fp);
          if ((got == (char *)0x0) || (rc = _fputs(s,dst_fp), rc == -1))
          goto LAB_0054a7eb;
          str_strip_newline((iptr)s);
          str_trim((iptr)s);
          rc = __strcmpi(s,s__BEGINEVENTS_00632a60);
        } while (rc != 0);
      }
      events_write_list((iptr)dst_fp);
      if (src_fp == (FILE *)0x0) {
        rc = _fputs(s__ENDEVENTS_00632a98,dst_fp);
        if (rc != -1) {
LAB_0054a7e1:
          ok = 1;
        }
      }
      else {
        do {
          got = _fgets(s,0x100,src_fp);
          if (got == (char *)0x0) goto LAB_0054a7eb;
          str_strip_newline((iptr)s);
          str_trim((iptr)s);
          rc = __strcmpi(s,s__ENDEVENTS_00632a80);
        } while (rc != 0);
        rc = _fputs(s__ENDEVENTS_00632a8c,dst_fp);
        while (rc != -1) {
          got = _fgets(s,0x100,src_fp);
          if (got == (char *)0x0) goto LAB_0054a7e1;
          rc = _fputs(s,dst_fp);
        }
      }
    }
  }
LAB_0054a7eb:
  if (src_fp != (FILE *)0x0) {
    _fclose(src_fp);
  }
  if (dst_fp != (FILE *)0x0) {
    _fclose(dst_fp);
  }
  __chdir(saved_cwd);
  return ok;
}
#undef ok
#undef src_fp
#undef dst_fp
#undef saved_cwd
#undef filename
#undef s

/* 0054a912 auto */
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(12)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(772)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(776)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(784)))
i32 __cdecl events_editor_pick_item(int default_choice,iptr title,i32 kind)

{
  iptr name_str;
  iptr item;
  i32 result;
  iptr terrain_item;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  try_level = 0;
  dlg_reset(&dlg,0x1001);
  dialog_set_title((DialogWindowView *)&dlg,title);
  dialog_set_width((DialogWindowView *)&dlg,0xdc);
  dialog_set_listbox((DialogTextView *)&dlg,8,0xdc,0);
  switch(kind) {
  case 0:
    if (default_choice == 0) {
      default_choice = 1;
    }
    for (civ = 1; civ < 8; civ++) {
      result = 0;
      item = civ;
      name_str = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 1:
    for (civ = 0; civ < 0x3e; civ++) {
      result = 0;
      item = civ;
      name_str = label_string(unit_types[civ].name);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 2:
    for (advance = 0; advance < 100; advance++) {
      result = 0;
      item = advance;
      name_str = label_string(advances[advance].name);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 3:
    dialog_add_option((DialogOptionList *)&dlg,ADDR(0x632adc, ((u8 *)&g.d_00632adc)),-2,0);
    for (civ = 0; civ < 0x3e; civ++) {
      result = 0;
      item = civ;
      name_str = label_string(unit_types[civ].name);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 4:
    if (default_choice == 0) {
      default_choice = -2;
    }
    dialog_add_option((DialogOptionList *)&dlg,ADDR(0x632aa4, ((u8 *)&g.d_00632aa4)),-2,0);
    for (civ = 1; civ < 8; civ++) {
      result = 0;
      item = civ;
      name_str = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 5:
    if (default_choice == 0) {
      default_choice = -3;
    }
    dialog_add_option((DialogOptionList *)&dlg,ADDR(0x632aac, ((u8 *)&g.d_00632aac)),-3,0);
    dialog_add_option((DialogOptionList *)&dlg,ADDR(0x632abc, ((u8 *)&g.d_00632abc)),-4,0);
    for (civ = 1; civ < 8; civ++) {
      result = 0;
      item = civ;
      name_str = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 6:
    if (default_choice == 0) {
      default_choice = -4;
    }
    dialog_add_option((DialogOptionList *)&dlg,ADDR(0x632acc, ((u8 *)&g.d_00632acc)),-4,0);
    for (civ = 1; civ < 8; civ++) {
      result = 0;
      item = civ;
      name_str = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&dlg,name_str,item,result);
    }
    break;
  case 7:
    for (terrain2 = 0; terrain2 < 0xb; terrain2++) {
      result = 0;
      terrain_item = terrain2;
      item = label_string(terrain_types[terrain2].name);
      dialog_add_option((DialogOptionList *)&dlg,item,terrain_item,result);
    }
  }
  dialog_set_default_choice((DialogOptionList *)&dlg,default_choice);
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  result = dlg_show_modal(&dlg,0);
  dlg_set_parent_window(0);
  try_level = 0xffffffff;
  /* inlined unwind funclet 0054ada1 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  return result;
}
#undef parent_wnd2
#undef advance
#undef civ
#undef dlg
#undef terrain2
#undef seh_prev
#undef seh_handler
#undef try_level

/* 0054adc6 auto */
int __cdecl events_editor_pick_action_civ(int civ,i32 title,int action,iptr out_name)

{
  i32 name2;
  
  if (action == 0x100) {
    civ = events_editor_pick_item(civ,title,6);
    if (civ != -1) {
      if (civ < 0) {
        *(char **)out_name = s_TRIGGERRECEIVER_00632ae4;
      }
      else {
        name2 = civ_name_plural(civ);
        *(i32 *)out_name = name2;
      }
    }
  }
  else {
    civ = events_editor_pick_item(civ,title,5);
    if (civ != -1) {
      if (civ < 0) {
        if (civ == -3) {
          *(char **)out_name = s_TRIGGERATTACKER_00632af4;
        }
        else {
          *(char **)out_name = s_TRIGGERDEFENDER_00632b04;
        }
      }
      else {
        name2 = civ_name_plural(civ);
        *(i32 *)out_name = name2;
      }
    }
  }
  return civ;
}

/* 0054ae93 auto */
#define event (*(byte * *)(frame_ + FRAME_OFF(4)))
#define action_count (*(int *)(frame_ + FRAME_OFF(8)))
#define sel (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl events_editor_update_buttons(i32 unused)

{
  int action_sel;
  uint action_bit;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl_enable((Control *)(active_editor_wnd + 0x92c));
  sel = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  if (sel < 0) {
    ctrl_disable((Control *)(active_editor_wnd + 0x968));
    ctrl_disable((Control *)(active_editor_wnd + 0x9a4));
    ctrl_disable((Control *)(active_editor_wnd + 0x9e0));
    ctrl_disable((Control *)(active_editor_wnd + 0xa1c));
    ctrl_disable((Control *)(active_editor_wnd + 0xa58));
  }
  else {
    ctrl_enable((Control *)(active_editor_wnd + 0x9a4));
    event = (byte *)events_list_head;
    while ((event != (byte *)0x0 && (sel != 0))) {
      event = *(byte **)(event + 0x1bc);
      sel--;
    }
    if ((*event & 0x20) == 0) {
      ctrl_enable((Control *)(active_editor_wnd + 0x968));
    }
    else {
      ctrl_disable((Control *)(active_editor_wnd + 0x968));
    }
    if (*(int *)event == 0x20) {
      action_count = 0;
      while ((1 << ((byte)action_count & 0x1f) & (*(uint *)(event + 4) | 0xfffffe6f)) != 0) {
        action_count++;
      }
    }
    else {
      action_count = 0;
      while ((*(uint *)(event + 4) & 1 << ((byte)action_count & 0x1f)) != 0) {
        action_count++;
      }
    }
    if ((action_count < 0xc) && ((*event & 0x90) == 0)) {
      ctrl_enable((Control *)(active_editor_wnd + 0x9e0));
    }
    else {
      ctrl_disable((Control *)(active_editor_wnd + 0x9e0));
    }
    action_sel = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
    if (action_sel < 0) {
      ctrl_disable((Control *)(active_editor_wnd + 0xa1c));
      ctrl_disable((Control *)(active_editor_wnd + 0xa58));
    }
    else {
      ctrl_enable((Control *)(active_editor_wnd + 0xa58));
      action_bit = bits_nth_set(action_sel,*(i32 *)(event + 4));
      if ((action_bit & 0x3140) == 0) {
        ctrl_enable((Control *)(active_editor_wnd + 0xa1c));
      }
      else {
        ctrl_disable((Control *)(active_editor_wnd + 0xa1c));
      }
    }
  }
  return;
}
#undef event
#undef action_count
#undef sel

/* 0054b0ed auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define editor_value_clamped (*(int *)((u8 *)&g.d_0062e014))
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define msg (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl events_editor_on_ok(void)

{
  iptr ok;
  iptr wnd;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (editor_value_clamped == 0) {
    events_compact();
    ok = events_write_file();
    if (ok == 0) {
      _sprintf(msg,s_Error_updating_EVENTS__s_00632b1c,&lang_file_ext);
      uType = 0x10;
      lpCaption = s_File_I_O_Error_00632b38;
      lpText = msg;
      wnd = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(wnd + 4),lpText,lpCaption,uType);
    }
    editor_running = 0;
    wnd_end_modal_loop((ModalMenuWindow *)(active_editor_wnd + 0x48));
    menu_update_states();
  }
  else {
    if (active_editor_wnd == 0) {
      parent_wnd2 = 0;
    }
    else {
      parent_wnd2 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(parent_wnd2);
    popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x632b14, ((u8 *)&g.d_00632b14)));
    dlg_set_parent_window(0);
    editor_value_clamped = 0;
    events_editor_focus_redraw();
  }
  return;
}
#undef editor_running
#undef editor_value_clamped
#undef parent_wnd2
#undef msg

/* 0054b1d5 auto */
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define help_key (*(char * *)(frame_ + FRAME_OFF(8)))
void __cdecl events_editor_help_trigger(i32 trigger_idx)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(trigger_idx) {
  case 0:
    help_key = s_HELPUNITKILLED_00632b48;
    break;
  case 1:
    help_key = s_HELPCITYTAKEN_00632b58;
    break;
  case 2:
    help_key = s_HELPTURN_00632b68;
    break;
  case 3:
    help_key = s_HELPTURNINTERVAL_00632b74;
    break;
  case 4:
    help_key = s_HELPNEGOTIATION_00632b88;
    break;
  case 5:
    help_key = s_HELPSCENARIOLOADED_00632b98;
    break;
  case 6:
    help_key = s_HELPRANDOMTURN_00632bac;
    break;
  case 7:
    help_key = s_HELPNOSCHISM_00632bbc;
    break;
  case 8:
    help_key = s_HELPRECEIVEDTECHNOLOGY_00632bcc;
  }
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  popup_text(ADDR(0x632be4, ((u8 *)&g.d_00632be4)),(iptr)help_key);
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef parent_wnd2
#undef help_key

/* 0054b2ec auto */
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define help_key (*(char * *)(frame_ + FRAME_OFF(8)))
void __cdecl events_editor_help_action(i32 action_idx)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(action_idx) {
  case 0:
    help_key = s_HELPTEXT_00632bec;
    break;
  case 1:
    help_key = s_HELPMOVEUNIT_00632bf8;
    break;
  case 2:
    help_key = s_HELPCREATEUNIT_00632c08;
    break;
  case 3:
    help_key = s_HELPCHANGEMONEY_00632c18;
    break;
  case 4:
    help_key = s_HELPPLAYWAVEFILE_00632c28;
    break;
  case 5:
    help_key = s_HELPMAKEAGGRESSION_00632c3c;
    break;
  case 6:
    help_key = s_HELPJUSTONCE_00632c50;
    break;
  case 7:
    help_key = s_HELPPLAYCDTRACK_00632c60;
    break;
  case 8:
    help_key = s_HELPDONTPLAYWONDERS_00632c70;
    break;
  case 9:
    help_key = s_HELPCHANGETERRAIN_00632c84;
    break;
  case 10:
    help_key = s_HELPDESTROYACIVILIZATION_00632c98;
    break;
  case 0xb:
    help_key = s_HELPGIVETECHNOLOGY_00632cb4;
  }
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  popup_text(ADDR(0x632cc8, ((u8 *)&g.d_00632cc8)),(iptr)help_key);
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef parent_wnd2
#undef help_key

/* 0054b433 auto */
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define event (*(uint * *)(frame_ + FRAME_OFF(12)))
#define bits2 (*(uint *)(frame_ + FRAME_OFF(16)))
#define idx (*(int *)(frame_ + FRAME_OFF(20)))
void __cdecl events_editor_on_help(void)

{
  int action_sel;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  action_sel = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
  if (action_sel < 0) {
    idx = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
    if (idx < 0) {
      if (active_editor_wnd == 0) {
        parent_wnd2 = 0;
      }
      else {
        parent_wnd2 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd2);
      popup_text(ADDR(0x632cd8, ((u8 *)&g.d_00632cd8)),ADDR(0x632cd0, ((u8 *)&g.d_00632cd0)));
      dlg_set_parent_window(0);
      events_editor_focus_redraw();
    }
    else {
      event = (uint *)events_list_head;
      while ((event != (uint *)0x0 && (idx != 0))) {
        event = (uint *)event[0x6f];
        idx--;
      }
      bits2 = *event;
      idx = 0;
      for (; (bits2 & 1) == 0; bits2 = bits2 >> 1) {
        idx++;
      }
      if (event != (uint *)0x0) {
        events_editor_help_trigger(idx);
      }
    }
  }
  else {
    idx = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
    event = (uint *)events_list_head;
    while ((event != (uint *)0x0 && (idx != 0))) {
      event = *(uint **)((int)event + 0x1bc);
      idx--;
    }
    bits2 = bits_nth_set(action_sel,*(i32 *)((int)event + 4));
    idx = 0;
    for (; (bits2 & 1) == 0; bits2 = bits2 >> 1) {
      idx++;
    }
    if (event != (uint *)0x0) {
      events_editor_help_action(idx);
    }
  }
  return;
}
#undef parent_wnd2
#undef event
#undef bits2
#undef idx

/* 0054b5eb auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define events_editor_backup (*(iptr *)((u8 *)&g.d_00632578))
void __cdecl events_editor_on_cancel(void)

{
  events_reset((ScenarioEvents *)&scenario_events,50000);
  events_copy(ADDR(0x64b690, ((u8 *)&g.d_0064b690)),events_editor_backup);
  editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running
#undef events_editor_backup

/* 0054b635 auto */
#define talker_type (*(char * *)(frame_ + FRAME_OFF(4)))
#define listener_type (*(char * *)(frame_ + FRAME_OFF(8)))
#define event (*(uint * *)(frame_ + FRAME_OFF(12)))
#define num (*(int *)(frame_ + FRAME_OFF(16)))
#define line (*(char (*)[256])(frame_ + FRAME_OFF(20)))
void __cdecl events_editor_fill_triggers(void)

{
  i32 tech_name;
  uint trigger;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  num = 0;
  listbox_clear((ListBoxClearView *)(active_editor_wnd + 0xad0));
  for (event = (uint *)events_list_head; event != (uint *)0x0;
      event = (uint *)event[0x6f]) {
    num++;
    trigger = *event;
    if (trigger < 9) {
      if (trigger == 8) {
        _sprintf(line,s__d__TURNINTERVAL___d__00632d68,num,event[0xb]);
      }
      else if (trigger == 1) {
        if (((event[2] == 0) || (event[5] == 0)) || (event[8] == 0)) {
          _sprintf(line,s__d__UNITKILLED_00632d0c,num);
        }
        else {
          _sprintf(line,s__d__UNITKILLED___s_attacker__s_d_00632ce0,num,event[2],
                   event[5],event[8]);
        }
      }
      else if (trigger == 2) {
        if (((event[4] == 0) || (event[5] == 0)) || (event[8] == 0)) {
          _sprintf(line,s__d__CITYTAKEN_00632d48,num);
        }
        else {
          _sprintf(line,s__d__CITYTAKEN___s_attacker__s_de_00632d1c,num,event[4],
                   event[5],event[8]);
        }
      }
      else if (trigger == 4) {
        _sprintf(line,s__d__TURN___d__00632d58,num,event[0xb]);
      }
    }
    else {
      switch(trigger) {
      case 0x10:
        if ((event[5] == 0) || (event[8] == 0)) {
          _sprintf(line,s__d__NEGOTIATION_00632dfc,num);
        }
        else {
          if (event[10] == 1) {
            listener_type = s_HUMAN_00632d80;
          }
          else if (event[10] == 2) {
            listener_type = s_COMPUTER_00632d88;
          }
          else {
            listener_type = s_HUMANORCOMPUTER_00632d94;
          }
          if (event[7] == 1) {
            talker_type = s_HUMAN_00632da4;
          }
          else if (event[7] == 2) {
            talker_type = s_COMPUTER_00632dac;
          }
          else {
            talker_type = s_HUMANORCOMPUTER_00632db8;
          }
          _sprintf(line,s__d__NEGOTIATION__talker__s___s__l_00632dc8,num,event[5],
                   talker_type,event[8],listener_type);
        }
        break;
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x2a:
      case 0x2b:
      case 0x2c:
      case 0x2d:
      case 0x2e:
      case 0x2f:
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
      case 0x3a:
      case 0x3b:
      case 0x3c:
      case 0x3d:
      case 0x3e:
      case 0x3f:
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5b:
      case 0x5c:
      case 0x5d:
      case 0x5e:
      case 0x5f:
      case 0x60:
      case 0x61:
      case 0x62:
      case 99:
      case 100:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
      case 0x7b:
      case 0x7c:
      case 0x7d:
      case 0x7e:
      case 0x7f:
      case 0x81:
      case 0x82:
      case 0x83:
      case 0x84:
      case 0x85:
      case 0x86:
      case 0x87:
      case 0x88:
      case 0x89:
      case 0x8a:
      case 0x8b:
      case 0x8c:
      case 0x8d:
      case 0x8e:
      case 0x8f:
      case 0x90:
      case 0x91:
      case 0x92:
      case 0x93:
      case 0x94:
      case 0x95:
      case 0x96:
      case 0x97:
      case 0x98:
      case 0x99:
      case 0x9a:
      case 0x9b:
      case 0x9c:
      case 0x9d:
      case 0x9e:
      case 0x9f:
      case 0xa0:
      case 0xa1:
      case 0xa2:
      case 0xa3:
      case 0xa4:
      case 0xa5:
      case 0xa6:
      case 0xa7:
      case 0xa8:
      case 0xa9:
      case 0xaa:
      case 0xab:
      case 0xac:
      case 0xad:
      case 0xae:
      case 0xaf:
      case 0xb0:
      case 0xb1:
      case 0xb2:
      case 0xb3:
      case 0xb4:
      case 0xb5:
      case 0xb6:
      case 0xb7:
      case 0xb8:
      case 0xb9:
      case 0xba:
      case 0xbb:
      case 0xbc:
      case 0xbd:
      case 0xbe:
      case 0xbf:
      case 0xc0:
      case 0xc1:
      case 0xc2:
      case 0xc3:
      case 0xc4:
      case 0xc5:
      case 0xc6:
      case 199:
      case 200:
      case 0xc9:
      case 0xca:
      case 0xcb:
      case 0xcc:
      case 0xcd:
      case 0xce:
      case 0xcf:
      case 0xd0:
      case 0xd1:
      case 0xd2:
      case 0xd3:
      case 0xd4:
      case 0xd5:
      case 0xd6:
      case 0xd7:
      case 0xd8:
      case 0xd9:
      case 0xda:
      case 0xdb:
      case 0xdc:
      case 0xdd:
      case 0xde:
      case 0xdf:
      case 0xe0:
      case 0xe1:
      case 0xe2:
      case 0xe3:
      case 0xe4:
      case 0xe5:
      case 0xe6:
      case 0xe7:
      case 0xe8:
      case 0xe9:
      case 0xea:
      case 0xeb:
      case 0xec:
      case 0xed:
      case 0xee:
      case 0xef:
      case 0xf0:
      case 0xf1:
      case 0xf2:
      case 0xf3:
      case 0xf4:
      case 0xf5:
      case 0xf6:
      case 0xf7:
      case 0xf8:
      case 0xf9:
      case 0xfa:
      case 0xfb:
      case 0xfc:
      case 0xfd:
      case 0xfe:
      case 0xff:
        break;
      case 0x20:
        _sprintf(line,s__d__SCENARIOLOADED_00632e0c,num);
        break;
      case 0x40:
        if (event[0xc] == 0) {
          _sprintf(line,s__d__RANDOMTURN_00632e40,num);
        }
        else {
          _sprintf(line,s__d__RANDOMTURN__denominator__d__00632e20,num,event[0xc]);
        }
        break;
      case 0x80:
        if (event[8] == 0) {
          _sprintf(line,s__d__NOSCHISM_00632e64,num);
        }
        else {
          _sprintf(line,s__d__NOSCHISM___s__00632e50,num,event[8]);
        }
        break;
      case 0x100:
        if (event[8] == 0) {
          _sprintf(line,s__d__RECEIVEDTECHNOLOGY_00632e98,num);
        }
        else {
          trigger = event[8];
          tech_name = label_string(advances[event[0xd]].name);
          _sprintf(line,s__d__RECEIVEDTECHNOLOGY___s_whom__00632e74,num,tech_name,trigger);
        }
      }
    }
    listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xad0),(iptr)line);
  }
  events_editor_update_buttons(0);
  return;
}
#undef talker_type
#undef listener_type
#undef event
#undef num
#undef line

/* 0054bc1a auto */
#define who_str (*(char (*)[16])(frame_ + FRAME_OFF(4)))
#define event (*(iptr *)(frame_ + FRAME_OFF(20)))
#define action_bit (*(uint *)(frame_ + FRAME_OFF(24)))
#define line (*(char (*)[256])(frame_ + FRAME_OFF(28)))
void __cdecl events_editor_fill_actions(i32 unused)

{
  int next_idx;
  uint action;
  i32 name_str;
  i32 civ_name;
  bool more;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  action_bit = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  event = events_list_head;
  while ((event != 0 &&
         (next_idx = action_bit - 1, more = action_bit != 0, action_bit = next_idx, more))) {
    event = *(iptr *)(event + 0x1bc);
  }
  listbox_clear((ListBoxClearView *)(active_editor_wnd + 0xb0c));
  action_bit = 1;
  if (event != 0) {
    do {
      line[0] = '\0';
      action = *(uint *)(event + 4) & action_bit;
      if (action < 9) {
        if (action == 8) {
          if (*(int *)(event + 0x174) == 0) {
            _sprintf(line,s_CHANGEMONEY_00632f50);
          }
          else {
            _sprintf(line,s_CHANGEMONEY__receiver__s_amount__00632f2c,
                     *(i32 *)(event + 0x174),*(i32 *)(event + 0x17c));
          }
        }
        else if (action == 1) {
          if (*(int *)(event + 0x38) == 0) {
            _sprintf(line,&events_editor_text_caption);
          }
          else {
            _sprintf(line,s_TEXT___s__00632eb0,*(i32 *)(event + 0x38));
          }
        }
        else if (action == 2) {
          if ((*(int *)(event + 0x90) == 0) || (*(int *)(event + 0x88) == 0)) {
            _sprintf(line,s_MOVEUNIT_00632edc);
          }
          else {
            _sprintf(line,s_MOVEUNIT___s_owner__s__00632ec4,*(i32 *)(event + 0x90),
                     *(i32 *)(event + 0x88));
          }
        }
        else if (action == 4) {
          if (((*(int *)(event + 0xdc) == 0) || (*(int *)(event + 0xd4) == 0)) ||
             (*(int *)(event + 0x13c) == 0)) {
            _sprintf(line,s_CREATEUNIT_00632f20);
          }
          else {
            _sprintf(line,s_CREATEUNIT___s_owner__s_veteran__00632ef0,
                     *(i32 *)(event + 0xdc),*(i32 *)(event + 0xd4),
                     &events_editor_yes_no_strs + ((*(int *)(event + 0x138) != 0) - 1 & 4),
                     *(i32 *)(event + 0x13c));
          }
        }
      }
      else if (action < 0x21) {
        if (action == 0x20) {
          if ((*(int *)(event + 0xcc) == 0) || (*(int *)(event + 0xc4) == 0)) {
            _sprintf(line,s_MAKEAGGRESSION_00632fa8);
          }
          else {
            _sprintf(line,s_MAKEAGGRESSION__aggressor__s_vic_00632f80,
                     *(i32 *)(event + 0xcc),*(i32 *)(event + 0xc4));
          }
        }
        else if (action == 0x10) {
          if (*(int *)(event + 0x184) == 0) {
            _sprintf(line,s_PLAYWAVEFILE_00632f70);
          }
          else {
            _sprintf(line,s_PLAYWAVEFILE___s__00632f5c,*(i32 *)(event + 0x184));
          }
        }
      }
      else if (action < 0x81) {
        if (action == 0x80) {
          if (*(int *)(event + 0x188) == 0) {
            _sprintf(line,s_PLAYCDTRACK_00632fe8);
          }
          else {
            _sprintf(line,s_PLAYCDTRACK___d__00632fd4,*(i32 *)(event + 0x188));
          }
        }
        else if (action == 0x40) {
          _sprintf(line,s_JUSTONCE_00632fb8);
        }
      }
      else if (action < 0x201) {
        if (action == 0x200) {
          name_str = label_string(terrain_types[*(int *)(event + 0x18c)].name);
          _sprintf(line,s_CHANGETERRAIN___s__00633004,name_str);
        }
        else if (action == 0x100) {
          _sprintf(line,s_DONTPLAYWONDERS_00632ff4);
        }
      }
      else if (action == 0x400) {
        if (*(int *)(event + 0x1b0) < 0) {
          if ((*(byte *)(event + 1) & 1) == 0) {
            if (*(int *)(event + 0x1b0) == -3) {
              _sprintf(line,s_DESTROYACIVILIZATION__TRIGGERATT_0063305c);
            }
            else {
              _sprintf(line,s_DESTROYACIVILIZATION__TRIGGERDEF_00633084);
            }
          }
          else {
            _sprintf(line,s_DESTROYACIVILIZATION__TRIGGERREC_00633034);
          }
        }
        else {
          name_str = civ_name_plural(*(iptr *)(event + 0x1b0));
          _sprintf(line,s_DESTROYACIVILIZATION___s__00633018,name_str);
        }
      }
      else if (action == 0x800) {
        if (*(int *)(event + 0x1b8) == 0) {
          _sprintf(line,s_GIVETECHNOLOGY_00633134);
        }
        else if (*(int *)(event + 0x1b8) < 0) {
          if ((*(byte *)(event + 1) & 1) == 0) {
            if (*(int *)(event + 0x1b8) == -3) {
              _sprintf(who_str,s_TRIGGERATTACKER_006330e8);
            }
            else {
              _sprintf(who_str,s_TRIGGERDEFENDER_006330f8);
            }
          }
          else {
            _sprintf(who_str,s_TRIGGERRECEIVER_006330d8);
          }
          name_str = label_string(advances[*(int *)(event + 0x1b4)].name);
          _sprintf(line,s_GIVETECHNOLOGY__receiver__s_tech_00633108,who_str,name_str);
        }
        else {
          name_str = label_string(advances[*(int *)(event + 0x1b4)].name);
          civ_name = civ_name_plural(*(iptr *)(event + 0x1b8));
          _sprintf(line,s_GIVETECHNOLOGY__receiver__s_tech_006330ac,civ_name,name_str);
        }
      }
      else if (action == 0x2000) {
        _sprintf(line,s_HASTRIGGERED_00632fc4);
      }
      if (line[0] != '\0') {
        listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xb0c),(iptr)line);
      }
      action_bit = action_bit << 1;
    } while (action_bit != 0x8000);
  }
  events_editor_update_buttons(0);
  return;
}
#undef who_str
#undef event
#undef action_bit
#undef line

/* 0054c36e auto */
#define parent_wnd2 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define event (*(iptr *)(frame_ + FRAME_OFF(8)))
#define idx (*(i32 *)(frame_ + FRAME_OFF(12)))
void __cdecl events_editor_on_delete_trigger(void)

{
  int sel;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  sel = popup_game(ADDR(0x633144, ((u8 *)&g.d_00633144)));
  if (sel != 0) {
    sel = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
    idx = sel;
    for (event = events_list_head; event != 0; event = *(iptr *)(event + 0x1bc)) {
      if (idx == 0) break;
      idx--;
    }
    if (*(int *)(event + 0x1c0) != 0) {
      *(i32 *)(*(int *)(event + 0x1c0) + 0x1bc) = *(i32 *)(event + 0x1bc);
    }
    if (*(int *)(event + 0x1bc) != 0) {
      *(i32 *)(*(int *)(event + 0x1bc) + 0x1c0) = *(i32 *)(event + 0x1c0);
    }
    if (sel == 0) {
      events_list_head = *(iptr *)(event + 0x1bc);
    }
    events_compact();
    events_editor_fill_triggers();
    events_editor_fill_actions(0);
  }
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef parent_wnd2
#undef event
#undef idx

/* 0054c4a1 auto */
#define parent_wnd_h (*(iptr *)(frame_ + FRAME_OFF(0)))
#define parent_wnd_f (*(iptr *)(frame_ + FRAME_OFF(4)))
#define parent_wnd_e (*(iptr *)(frame_ + FRAME_OFF(8)))
#define parent_wnd_b (*(iptr *)(frame_ + FRAME_OFF(12)))
#define parent_wnd_a (*(iptr *)(frame_ + FRAME_OFF(16)))
#define parent_wnd_d (*(iptr *)(frame_ + FRAME_OFF(20)))
#define parent_wnd_c (*(iptr *)(frame_ + FRAME_OFF(24)))
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define changed (*(i32 *)(frame_ + FRAME_OFF(36)))
#define event (*(uint * *)(frame_ + FRAME_OFF(40)))
#define city_name (*(char (*)[260])(frame_ + FRAME_OFF(44)))
#define skip (*(int *)(frame_ + FRAME_OFF(304)))
#define number (*(i32 *)(frame_ + FRAME_OFF(308)))
#define sel (*(int *)(frame_ + FRAME_OFF(312)))
#define choice (*(uint *)(frame_ + FRAME_OFF(316)))
#define name2 (*(char * *)(frame_ + FRAME_OFF(320)))
i32 __cdecl events_editor_edit_trigger(i32 unused)

{
  size_t len;
  int check;
  i32 title;
  uint value;
  bool more;
  i32 kind;
  i8 frame_[FRAME_OFF(328)] __attribute__((aligned(8)));  /* original stack frame */
  
  changed = 0;
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  sel = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  event = (uint *)events_list_head;
  skip = sel;
  while ((event != (uint *)0x0 &&
         (check = skip - 1, more = skip != 0, skip = check, more))) {
    event = (uint *)event[0x6f];
  }
  value = *event;
  if (value < 9) {
    if (value == 8) {
      if (active_editor_wnd == 0) {
        parent_wnd_a = 0;
      }
      else {
        parent_wnd_a = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd_a);
      choice = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633194, ((u8 *)&g.d_00633194)),event[0xb],(iptr)&number);
      if (active_editor_wnd == 0) {
        parent_wnd_b = 0;
      }
      else {
        parent_wnd_b = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd_b);
      if (choice == 0) {
        value = editor_clamp_value(number,0,0x7fff);
        event[0xb] = value;
        changed = 1;
      }
    }
    else if (value == 1) {
      kind = 1;
      title = label_string(*(i32 *)(label_string_ids + 0x890));
      choice = events_editor_pick_item(event[3],title,kind);
      if (choice != 0xffffffff) {
        if ((int)choice < 0) {
          event[3] = 0xfffffffe;
          name2 = s_ANYUNIT_00633150;
        }
        else {
          event[3] = choice;
          name2 = (char *)label_string(unit_types[event[3]].name);
        }
        len = _strlen(name2);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[2] = value;
        if (event[2] != 0) {
          crt_strcpy(event[2],name2);
          kind = 4;
          title = label_string(*(i32 *)(label_string_ids + 0x894));
          choice = events_editor_pick_item(event[6],title,kind);
          if (choice != 0xffffffff) {
            if ((int)choice < 0) {
              event[6] = 0xfffffffe;
              name2 = s_ANYBODY_00633158;
            }
            else {
              event[6] = choice;
              name2 = (char *)civ_name_plural(event[6]);
            }
            len = _strlen(name2);
            value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
            event[5] = value;
            if (event[5] != 0) {
              crt_strcpy(event[5],name2);
              kind = 4;
              title = label_string(*(i32 *)(label_string_ids + 0x898));
              choice = events_editor_pick_item(event[9],title,kind);
              if (choice != 0xffffffff) {
                if ((int)choice < 0) {
                  event[9] = 0xfffffffe;
                  name2 = s_ANYBODY_00633160;
                }
                else {
                  event[9] = choice;
                  name2 = (char *)civ_name_plural(event[9]);
                }
                len = _strlen(name2);
                value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
                event[8] = value;
                if (event[8] != 0) {
                  crt_strcpy(event[8],name2);
                  changed = 1;
                }
              }
            }
          }
        }
      }
    }
    else if (value == 2) {
      do {
        if (event[4] == 0) {
          event[4] = (uint)&events_city_default_str;
        }
        if (active_editor_wnd == 0) {
          parent_wnd_c = 0;
        }
        else {
          parent_wnd_c = active_editor_wnd + 0x48;
        }
        dlg_set_parent_window(parent_wnd_c);
        choice = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x63316c, ((u8 *)&g.d_0063316c)),0x17,event[4],(iptr)city_name);
        dlg_set_parent_window(0);
      } while ((-1 < (int)choice) &&
              ((len = _strlen(city_name), len == 0 ||
               (check = editor_check_city_name((iptr)city_name), check == 0))));
      if ((-1 < (int)choice) && (len = _strlen(city_name), len != 0)) {
        len = _strlen(city_name);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[4] = value;
        if (event[4] != 0) {
          crt_strcpy(event[4],city_name);
          kind = 4;
          title = label_string(*(i32 *)(label_string_ids + 0x894));
          choice = events_editor_pick_item(event[6],title,kind);
          if (choice != 0xffffffff) {
            if ((int)choice < 0) {
              event[6] = 0xfffffffe;
              name2 = s_ANYBODY_00633178;
            }
            else {
              event[6] = choice;
              name2 = (char *)civ_name_plural(event[6]);
            }
            len = _strlen(name2);
            value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
            event[5] = value;
            if (event[5] != 0) {
              crt_strcpy(event[5],name2);
              kind = 4;
              title = label_string(*(i32 *)(label_string_ids + 0x898));
              choice = events_editor_pick_item(event[9],title,kind);
              if (choice != 0xffffffff) {
                if ((int)choice < 0) {
                  event[9] = 0xfffffffe;
                  name2 = s_ANYBODY_00633180;
                }
                else {
                  event[9] = choice;
                  name2 = (char *)civ_name_plural(event[9]);
                }
                len = _strlen(name2);
                value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
                event[8] = value;
                if (event[8] != 0) {
                  crt_strcpy(event[8],name2);
                  changed = 1;
                }
              }
            }
          }
        }
      }
    }
    else if (value == 4) {
      if (active_editor_wnd == 0) {
        parent_wnd_d = 0;
      }
      else {
        parent_wnd_d = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd_d);
      choice = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633188, ((u8 *)&g.d_00633188)),event[0xb],(iptr)&number);
      dlg_set_parent_window(0);
      if (choice == 0) {
        value = editor_clamp_value(number,0xffffffff,0x7fff);
        event[0xb] = value;
        changed = 1;
      }
    }
  }
  else {
    switch(value) {
    case 0x10:
      kind = 4;
      title = label_string(*(i32 *)(label_string_ids + 0x89c));
      choice = events_editor_pick_item(event[6],title,kind);
      if (choice != 0xffffffff) {
        if ((int)choice < 0) {
          event[6] = 0xfffffffe;
          name2 = s_ANYBODY_006331a4;
        }
        else {
          event[6] = choice;
          name2 = (char *)civ_name_plural(event[6]);
        }
        len = _strlen(name2);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[5] = value;
        if (event[5] != 0) {
          crt_strcpy(event[5],name2);
          if ((event[7] == 0) || (event[7] == 1)) {
            choice = 0;
          }
          else if (event[7] == 2) {
            choice = 1;
          }
          else {
            choice = 2;
          }
          if (active_editor_wnd == 0) {
            parent_wnd_e = 0;
          }
          else {
            parent_wnd_e = active_editor_wnd + 0x48;
          }
          dlg_set_parent_window(parent_wnd_e);
          choice = popup_text_run(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6331ac, ((u8 *)&g.d_006331ac)),choice,0,0,0,1);
          dlg_set_parent_window(0);
          if (-1 < (int)choice) {
            if (choice == 0) {
              event[7] = 1;
            }
            else if (choice == 1) {
              event[7] = 2;
            }
            else {
              event[7] = 4;
            }
            kind = 4;
            title = label_string(*(i32 *)(label_string_ids + 0x8a0));
            choice = events_editor_pick_item(event[9],title,kind);
            if (choice != 0xffffffff) {
              if ((int)choice < 0) {
                event[9] = 0xfffffffe;
                name2 = s_ANYBODY_006331b8;
              }
              else {
                event[9] = choice;
                name2 = (char *)civ_name_plural(event[9]);
              }
              len = _strlen(name2);
              value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
              event[8] = value;
              if (event[8] != 0) {
                crt_strcpy(event[8],name2);
                if ((event[10] == 0) || (event[10] == 1)) {
                  choice = 0;
                }
                else if (event[10] == 2) {
                  choice = 1;
                }
                else {
                  choice = 2;
                }
                if (active_editor_wnd == 0) {
                  parent_wnd_f = 0;
                }
                else {
                  parent_wnd_f = active_editor_wnd + 0x48;
                }
                dlg_set_parent_window(parent_wnd_f);
                choice = popup_text_run(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6331c0, ((u8 *)&g.d_006331c0)),choice,0,0,0,1);
                dlg_set_parent_window(0);
                if (-1 < (int)choice) {
                  if (choice == 0) {
                    event[10] = 1;
                  }
                  else if (choice == 1) {
                    event[10] = 2;
                  }
                  else {
                    event[10] = 4;
                  }
                  changed = 1;
                }
              }
            }
          }
        }
      }
      break;
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x3f:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    case 0x8f:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x9a:
    case 0x9b:
    case 0x9c:
    case 0x9d:
    case 0x9e:
    case 0x9f:
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
    case 0xab:
    case 0xac:
    case 0xad:
    case 0xae:
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:
    case 0xc0:
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 199:
    case 200:
    case 0xc9:
    case 0xca:
    case 0xcb:
    case 0xcc:
    case 0xcd:
    case 0xce:
    case 0xcf:
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3:
    case 0xd4:
    case 0xd5:
    case 0xd6:
    case 0xd7:
    case 0xd8:
    case 0xd9:
    case 0xda:
    case 0xdb:
    case 0xdc:
    case 0xdd:
    case 0xde:
    case 0xdf:
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0xe3:
    case 0xe4:
    case 0xe5:
    case 0xe6:
    case 0xe7:
    case 0xe8:
    case 0xe9:
    case 0xea:
    case 0xeb:
    case 0xec:
    case 0xed:
    case 0xee:
    case 0xef:
    case 0xf0:
    case 0xf1:
    case 0xf2:
    case 0xf3:
    case 0xf4:
    case 0xf5:
    case 0xf6:
    case 0xf7:
    case 0xf8:
    case 0xf9:
    case 0xfa:
    case 0xfb:
    case 0xfc:
    case 0xfd:
    case 0xfe:
    case 0xff:
      break;
    case 0x20:
      changed = 1;
      break;
    case 0x40:
      value = editor_clamp_value(event[0xc],1,1000);
      event[0xc] = value;
      if (active_editor_wnd == 0) {
        parent_wnd_h = 0;
      }
      else {
        parent_wnd_h = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd_h);
      choice = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6331cc, ((u8 *)&g.d_006331cc)),event[0xc],(iptr)&number);
      dlg_set_parent_window(0);
      if (choice == 0) {
        value = editor_clamp_value(number,1,1000);
        event[0xc] = value;
        changed = 1;
      }
      break;
    case 0x80:
      kind = 4;
      title = label_string(*(i32 *)(label_string_ids + 0x8a4));
      choice = events_editor_pick_item(event[9],title,kind);
      if (choice != 0xffffffff) {
        if ((int)choice < 0) {
          event[9] = 0xfffffffe;
          name2 = s_ANYBODY_006331d8;
        }
        else {
          event[9] = choice;
          name2 = (char *)civ_name_plural(event[9]);
        }
        len = _strlen(name2);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[8] = value;
        if (event[8] != 0) {
          crt_strcpy(event[8],name2);
          changed = 1;
        }
      }
      break;
    case 0x100:
      kind = 4;
      title = label_string(*(i32 *)(label_string_ids + 0x8a8));
      choice = events_editor_pick_item(event[9],title,kind);
      if (choice != 0xffffffff) {
        if ((int)choice < 0) {
          event[9] = 0xfffffffe;
          name2 = s_ANYBODY_006331e0;
        }
        else {
          event[9] = choice;
          name2 = (char *)civ_name_plural(event[9]);
        }
        len = _strlen(name2);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[8] = value;
        if (event[8] != 0) {
          crt_strcpy(event[8],name2);
          kind = 2;
          title = label_string(*(i32 *)(label_string_ids + 0x8ac));
          choice = events_editor_pick_item(event[0xd],title,kind);
          if (choice != 0xffffffff) {
            event[0xd] = choice;
            changed = 1;
          }
        }
      }
    }
  }
  events_compact();
  events_editor_fill_triggers();
  listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xad0),sel);
  events_editor_update_buttons(0);
  events_editor_focus_redraw();
  dlg_set_parent_window(0);
  return changed;
}
#undef parent_wnd_h
#undef parent_wnd_f
#undef parent_wnd_e
#undef parent_wnd_b
#undef parent_wnd_a
#undef parent_wnd_d
#undef parent_wnd_c
#undef parent_wnd2
#undef changed
#undef event
#undef city_name
#undef skip
#undef number
#undef sel
#undef choice
#undef name2

/* 0054d4ca auto */
void __cdecl events_editor_on_edit_trigger(i32 mode)

{
  events_editor_edit_trigger(mode);
  return;
}

/* 0054d4e6 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define event (*(iptr *)(frame_ + FRAME_OFF(8)))
#define trigger_type (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl events_editor_on_add_trigger(void)

{
  int *new_event;
  LPCSTR lpCaption;
  LPCSTR lpText;
  iptr window;
  int result;
  UINT uType;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  trigger_type = 0;
  while( true ) {
    if (active_editor_wnd == 0) {
      parent_wnd2 = 0;
    }
    else {
      parent_wnd2 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(parent_wnd2);
    dlg_help_pressed = 0;
    trigger_type = popup_game_ex(ADDR(0x6331e8, ((u8 *)&g.d_006331e8)),trigger_type,1);
    dlg_set_parent_window(0);
    if (dlg_help_pressed == 0) break;
    events_editor_help_trigger(trigger_type);
  }
  if (trigger_type != -1) {
    if ((events_pool_bytes_free < 0x1c4) ||
       (new_event = (int *)events_alloc((ScenarioEvents *)&scenario_events),
       new_event == (int *)0x0)) {
      uType = 0;
      lpCaption = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8d0));
      lpText = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8e8));
      window = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(window + 4),lpText,lpCaption,uType);
    }
    else {
      *new_event = 1 << ((byte)trigger_type & 0x1f);
      events_editor_fill_triggers();
      events_editor_fill_actions(0);
      result = listbox_get_count((ListboxGetCountView *)(active_editor_wnd + 0xad0));
      listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xad0),result - 1);
      result = events_editor_edit_trigger(0);
      if (result == 0) {
        for (event = events_list_head; *(int *)(event + 0x1bc) != 0;
            event = *(iptr *)(event + 0x1bc)) {
        }
        if (*(int *)(event + 0x1c0) == 0) {
          events_list_head = *(iptr *)(event + 0x1bc);
        }
        else {
          *(i32 *)(*(int *)(event + 0x1c0) + 0x1bc) = *(i32 *)(event + 0x1bc);
        }
        events_compact();
        events_editor_fill_triggers();
        events_editor_fill_actions(0);
      }
      events_editor_update_buttons(0);
    }
  }
  events_editor_focus_redraw();
  return;
}
#undef dlg_help_pressed
#undef parent_wnd2
#undef event
#undef trigger_type

/* 0054d6da auto */
#define parent_wnd2 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define event (*(iptr *)(frame_ + FRAME_OFF(8)))
#define sel_index (*(i32 *)(frame_ + FRAME_OFF(12)))
void __cdecl events_editor_on_delete_action(void)

{
  int result;
  i32 action_sel;
  uint action_bit;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  sel_index = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  for (event = events_list_head; event != 0; event = *(iptr *)(event + 0x1bc)) {
    if (sel_index == 0) break;
    sel_index--;
  }
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  result = popup_game(ADDR(0x6331f4, ((u8 *)&g.d_006331f4)));
  if (result != 0) {
    action_sel = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
    result = bits_nth_set(action_sel,*(i32 *)(event + 4));
    if (result == 1) {
      *(i32 *)(event + 0x38) = 0;
    }
    action_bit = bits_nth_set(action_sel,*(i32 *)(event + 4));
    *(uint *)(event + 4) = *(uint *)(event + 4) & ~action_bit;
    events_editor_fill_actions(0);
    events_compact();
  }
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef parent_wnd2
#undef event
#undef sel_index

/* 0054d7ef auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define parent_wnd12 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define parent_wnd11 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define parent_wnd10 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define parent_wnd22 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define parent_wnd9 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define parent_wnd8 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define parent_wnd7 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define default_value (*(i32 *)(frame_ + FRAME_OFF(28)))
#define parent_wnd6 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define parent_wnd5 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define parent_wnd4 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define parent_wnd3 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(52)))
#define changed (*(uint *)(frame_ + FRAME_OFF(60)))
#define event (*(i32 * *)(frame_ + FRAME_OFF(64)))
#define input_buf (*(char (*)[260])(frame_ + FRAME_OFF(72)))
#define idx (*(int *)(frame_ + FRAME_OFF(332)))
#define edit_ctl (*(InputControl *)(frame_ + FRAME_OFF(336)))
#define number_value (*(int *)(frame_ + FRAME_OFF(408)))
#define choice (*(int *)(frame_ + FRAME_OFF(412)))
#define default_text (*(char (*)[64])(frame_ + FRAME_OFF(416)))
#define result (*(int *)(frame_ + FRAME_OFF(480)))
#define name_str (*(char * *)(frame_ + FRAME_OFF(484)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(488)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(492)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(496)))
uint __cdecl events_editor_edit_action(i32 mode)

{
  i32 arg2;
  uint action_bit;
  i32 value;
  size_t len;
  int prev_count;
  char *token;
  long parsed;
  bool nonzero;
  char **name_out;
  i8 frame_[FRAME_OFF(504)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  edit_ctor(&edit_ctl);
  seh_state = 0;
  changed = 0;
  if (active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  idx = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  event = (i32 *)events_list_head;
  while ((event != (i32 *)0x0 &&
         (prev_count = idx - 1, nonzero = idx != 0, idx = prev_count, nonzero))) {
    event = (i32 *)event[0x6f];
  }
  value = event[1];
  arg2 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
  action_bit = bits_nth_set(arg2,value);
  if (action_bit < 9) {
    if (action_bit == 8) {
      name_out = &name_str;
      value = *event;
      arg2 = label_string(*(i32 *)(label_string_ids + 0x8a8));
      result = events_editor_pick_action_civ(event[0x5e],arg2,value,(iptr)name_out);
      if (result != -1) {
        event[0x5e] = result;
        len = _strlen(name_str);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[0x5d] = value;
        if (event[0x5d] != 0) {
          crt_strcpy(event[0x5d],name_str);
          if (active_editor_wnd == 0) {
            parent_wnd22 = 0;
          }
          else {
            parent_wnd22 = active_editor_wnd + 0x48;
          }
          dlg_set_parent_window(parent_wnd22);
          result = editor_input_long(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633278, ((u8 *)&g.d_00633278)),event[0x5f],(iptr)&number_value);
          dlg_set_parent_window(0);
          if (result == 0) {
            value = editor_clamp_value(number_value,0xffff8ad0,30000);
            event[0x5f] = value;
            changed = 1;
          }
        }
      }
    }
    else if (action_bit == 1) {
      value = label_string(*(i32 *)(label_string_ids + 0x8b0));
      prev_count = editor_text_edit_dialog((iptr)(event + 0xe),value);
      changed = (uint)(prev_count != 0);
    }
    else if (action_bit == 2) {
      arg2 = 3;
      value = label_string(*(i32 *)(label_string_ids + 0x8b4));
      result = events_editor_pick_item(event[0x25],value,arg2);
      if (result != -1) {
        if (result < 0) {
          event[0x25] = 0xfffffffe;
          name_str = s_ANYUNIT_00633200;
        }
        else {
          event[0x25] = result;
          name_str = (char *)label_string(unit_types[event[0x25]].name);
        }
        len = _strlen(name_str);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[0x24] = value;
        if (event[0x24] != 0) {
          crt_strcpy(event[0x24],name_str);
          name_out = &name_str;
          value = *event;
          arg2 = label_string(*(i32 *)(label_string_ids + 0x8b8));
          result = events_editor_pick_action_civ(event[0x23],arg2,value,(iptr)name_out);
          if (result != -1) {
            event[0x23] = result;
            len = _strlen(name_str);
            value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
            event[0x22] = value;
            if (event[0x22] != 0) {
              crt_strcpy(event[0x22],name_str);
              _sprintf(default_text,s__d__d__d__d__d__d__d__d_00633208,event[0x27],event[0x28],
                       event[0x29],event[0x2a],event[0x2b],event[0x2c],
                       event[0x2d],event[0x2e]);
              if (active_editor_wnd == 0) {
                parent_wnd3 = 0;
              }
              else {
                parent_wnd3 = active_editor_wnd + 0x48;
              }
              dlg_set_parent_window(parent_wnd3);
              do {
                result = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633220, ((u8 *)&g.d_00633220)),0x1f,(iptr)default_text,(iptr)input_buf)
                ;
                if (result == -1) break;
                len = _strlen(input_buf);
              } while (len == 0);
              dlg_set_parent_window(0);
              if (result != -1) {
                len = _strlen(input_buf);
                if (len != 0) {
                  crt_strcpy(&text_buffer,input_buf);
                  for (idx = 0; idx < 4; idx++) {
                    arg2 = 0x7fff;
                    value = 0;
                    token = (char *)text_next_token();
                    parsed = _atol(token);
                    value = editor_clamp_value(parsed,value,arg2);
                    event[idx * 2 + 0x27] = value;
                    arg2 = 0x7fff;
                    value = 0;
                    token = (char *)text_next_token();
                    parsed = _atol(token);
                    value = editor_clamp_value(parsed,value,arg2);
                    event[idx * 2 + 0x28] = value;
                  }
                }
                _sprintf(default_text,s__d__d_00633228,event[0x2f],event[0x30]);
                if (active_editor_wnd == 0) {
                  parent_wnd4 = 0;
                }
                else {
                  parent_wnd4 = active_editor_wnd + 0x48;
                }
                dlg_set_parent_window(parent_wnd4);
                result = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633230, ((u8 *)&g.d_00633230)),8,(iptr)default_text,(iptr)input_buf);
                if (active_editor_wnd == 0) {
                  parent_wnd5 = 0;
                }
                else {
                  parent_wnd5 = active_editor_wnd + 0x48;
                }
                dlg_set_parent_window(parent_wnd5);
                if (result != -1) {
                  len = _strlen(input_buf);
                  if (len != 0) {
                    crt_strcpy(&text_buffer,input_buf);
                    arg2 = 0x7fff;
                    value = 0;
                    token = (char *)text_next_token();
                    parsed = _atol(token);
                    value = editor_clamp_value(parsed,value,arg2);
                    event[0x2f] = value;
                    arg2 = 0x7fff;
                    value = 0;
                    token = (char *)text_next_token();
                    parsed = _atol(token);
                    value = editor_clamp_value(parsed,value,arg2);
                    event[0x30] = value;
                  }
                  if (active_editor_wnd == 0) {
                    parent_wnd6 = 0;
                  }
                  else {
                    parent_wnd6 = active_editor_wnd + 0x48;
                  }
                  dlg_set_parent_window(parent_wnd6);
                  if (event[0x26] == -2) {
                    default_value = 0xffffffff;
                  }
                  else {
                    default_value = event[0x26];
                  }
                  result = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x63323c, ((u8 *)&g.d_0063323c)),default_value,(iptr)&number_value);
                  dlg_set_parent_window(0);
                  if (result == 0) {
                    if (number_value == -1) {
                      event[0x26] = 0xfffffffe;
                    }
                    else {
                      value = editor_clamp_value(number_value,0,0x7fff);
                      event[0x26] = value;
                    }
                    changed = 1;
                  }
                }
              }
            }
          }
        }
      }
    }
    else if (action_bit == 4) {
      arg2 = 1;
      value = label_string(*(i32 *)(label_string_ids + 0x8bc));
      result = events_editor_pick_item(event[0x38],value,arg2);
      if (result != -1) {
        event[0x38] = result;
        name_str = (char *)label_string(unit_types[event[0x38]].name);
        len = _strlen(name_str);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[0x37] = value;
        if (event[0x37] != 0) {
          crt_strcpy(event[0x37],name_str);
          name_out = &name_str;
          value = *event;
          arg2 = label_string(*(i32 *)(label_string_ids + 0x8b8));
          result = events_editor_pick_action_civ(event[0x36],arg2,value,(iptr)name_out);
          if (result != -1) {
            event[0x36] = result;
            len = _strlen(name_str);
            value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
            event[0x35] = value;
            if (event[0x35] != 0) {
              crt_strcpy(event[0x35],name_str);
              if (active_editor_wnd == 0) {
                parent_wnd7 = 0;
              }
              else {
                parent_wnd7 = active_editor_wnd + 0x48;
              }
              dlg_set_parent_window(parent_wnd7);
              choice = popup_debug_ex(ADDR(0x633248, ((u8 *)&g.d_00633248)),event[0x4e],0);
              dlg_set_parent_window(0);
              if (-1 < choice) {
                event[0x4e] = choice;
                do {
                  if (event[0x4f] == 0) {
                    event[0x4f] = &events_homecity_default_str;
                  }
                  if (active_editor_wnd == 0) {
                    parent_wnd8 = 0;
                  }
                  else {
                    parent_wnd8 = active_editor_wnd + 0x48;
                  }
                  dlg_set_parent_window(parent_wnd8);
                  result = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633254, ((u8 *)&g.d_00633254)),0x17,event[0x4f],
                                                (iptr)input_buf);
                  dlg_set_parent_window(0);
                } while ((-1 < result) &&
                        ((len = _strlen(input_buf), len == 0 ||
                         (prev_count = editor_check_city_name((iptr)input_buf), prev_count == 0))));
                if ((-1 < result) && (len = _strlen(input_buf), len != 0)) {
                  len = _strlen(input_buf);
                  value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
                  event[0x4f] = value;
                  if (event[0x4f] != 0) {
                    crt_strcpy(event[0x4f],input_buf);
                    for (idx = 0; idx < 10; idx++) {
                      event[0x4d] = idx;
                      _sprintf(default_text,s__d__d_00633264,event[idx * 2 + 0x39],
                               event[idx * 2 + 0x3a]);
                      if (active_editor_wnd == 0) {
                        parent_wnd9 = 0;
                      }
                      else {
                        parent_wnd9 = active_editor_wnd + 0x48;
                      }
                      dlg_set_parent_window(parent_wnd9);
                      text_set_number_arg(0,idx + 1);
                      result = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x63326c, ((u8 *)&g.d_0063326c)),8,(iptr)default_text,
                                                    (iptr)input_buf);
                      dlg_set_parent_window(0);
                      if (result == -1) {
                        if (idx == 0) break;
                        do {
                          event[idx * 2 + 0x39] = 0;
                          event[idx * 2 + 0x3a] = 0;
                          idx++;
                        } while (idx < 10);
                      }
                      else {
                        len = _strlen(input_buf);
                        if (len != 0) {
                          crt_strcpy(&text_buffer,input_buf);
                          arg2 = 0x7fff;
                          value = 0;
                          token = (char *)text_next_token();
                          parsed = _atol(token);
                          value = editor_clamp_value(parsed,value,arg2);
                          event[idx * 2 + 0x39] = value;
                          arg2 = 0x7fff;
                          value = 0;
                          token = (char *)text_next_token();
                          parsed = _atol(token);
                          value = editor_clamp_value(parsed,value,arg2);
                          event[idx * 2 + 0x3a] = value;
                        }
                      }
                    }
                    if (event[0x4d] != 0) {
                      changed = 1;
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
  else if (action_bit < 0x21) {
    if (action_bit == 0x20) {
      arg2 = 0;
      value = label_string(*(i32 *)(label_string_ids + 0x8c0));
      result = events_editor_pick_item(event[0x34],value,arg2);
      if (result != -1) {
        event[0x34] = result;
        name_str = (char *)civ_name_plural(event[0x34]);
        len = _strlen(name_str);
        value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
        event[0x33] = value;
        if (event[0x33] != 0) {
          crt_strcpy(event[0x33],name_str);
          arg2 = 0;
          value = label_string(*(i32 *)(label_string_ids + 0x8c4));
          result = events_editor_pick_item(event[0x32],value,arg2);
          if (result != -1) {
            event[0x32] = result;
            name_str = (char *)civ_name_plural(event[0x32]);
            len = _strlen(name_str);
            value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
            event[0x31] = value;
            if (event[0x31] != 0) {
              crt_strcpy(event[0x31],name_str);
              changed = 1;
            }
          }
        }
      }
    }
    else if (action_bit == 0x10) {
      if (event[0x61] == 0) {
        event[0x61] = &events_wavfile_default_str;
      }
      if (active_editor_wnd == 0) {
        parent_wnd10 = 0;
      }
      else {
        parent_wnd10 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd10);
      do {
        result = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633284, ((u8 *)&g.d_00633284)),10,event[0x61],(iptr)input_buf);
        if (result == -1) break;
        len = _strlen(input_buf);
      } while (len == 0);
      dlg_set_parent_window(0);
      if (-1 < result) {
        len = _strlen(input_buf);
        if (len != 0) {
          token = _strchr(input_buf,0x2e);
          if (token == (char *)0x0) {
            crt_strcat(input_buf,&events_wav_ext_str);
          }
          __strupr(input_buf);
          len = _strlen(input_buf);
          value = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),len + 1);
          event[0x61] = value;
          if (event[0x61] == 0) goto LAB_0054ee13;
          crt_strcpy(event[0x61],input_buf);
        }
        changed = 1;
      }
    }
  }
  else if (action_bit < 0x81) {
    if (action_bit == 0x80) {
      value = editor_clamp_value(event[0x62],2,0x18);
      event[0x62] = value;
      text_set_number_arg(0,2);
      text_set_number_arg(1,0x18);
      if (active_editor_wnd == 0) {
        parent_wnd11 = 0;
      }
      else {
        parent_wnd11 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd11);
      result = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633294, ((u8 *)&g.d_00633294)),event[0x62],(iptr)&number_value);
      dlg_set_parent_window(0);
      if (result == 0) {
        value = editor_clamp_value(number_value,2,0x18);
        event[0x62] = value;
        changed = 1;
      }
    }
    else if (action_bit == 0x40) {
      changed = 1;
    }
  }
  else if (action_bit < 0x201) {
    if (action_bit == 0x200) {
      arg2 = 7;
      value = label_string(*(i32 *)(label_string_ids + 0x970));
      result = events_editor_pick_item(event[99],value,arg2);
      if (result == -1) {
        result = -1;
      }
      else {
        event[99] = result;
        _sprintf(default_text,s__d__d__d__d__d__d__d__d_0063329c,event[100],event[0x65],
                 event[0x66],event[0x67],event[0x68],event[0x69],event[0x6a],
                 event[0x6b]);
        if (active_editor_wnd == 0) {
          parent_wnd12 = 0;
        }
        else {
          parent_wnd12 = active_editor_wnd + 0x48;
        }
        dlg_set_parent_window(parent_wnd12);
        do {
          result = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6332b4, ((u8 *)&g.d_006332b4)),0x1f,(iptr)default_text,(iptr)input_buf);
          if (result == -1) break;
          len = _strlen(input_buf);
        } while (len == 0);
        dlg_set_parent_window(0);
        if (result != -1) {
          len = _strlen(input_buf);
          if (len != 0) {
            crt_strcpy(&text_buffer,input_buf);
            for (idx = 0; idx < 4; idx++) {
              arg2 = 0x7fff;
              value = 0;
              token = (char *)text_next_token();
              parsed = _atol(token);
              value = editor_clamp_value(parsed,value,arg2);
              event[idx * 2 + 100] = value;
              arg2 = 0x7fff;
              value = 0;
              token = (char *)text_next_token();
              parsed = _atol(token);
              value = editor_clamp_value(parsed,value,arg2);
              event[idx * 2 + 0x65] = value;
            }
          }
          changed = 1;
        }
      }
    }
    else if (action_bit == 0x100) {
      changed = 1;
    }
  }
  else if (action_bit == 0x400) {
    name_out = &name_str;
    value = *event;
    arg2 = label_string(*(i32 *)(label_string_ids + 0x8c8));
    result = events_editor_pick_action_civ(event[0x6c],arg2,value,(iptr)name_out);
    if (result != -1) {
      event[0x6c] = result;
      changed = 1;
    }
  }
  else if (action_bit == 0x800) {
    name_out = &name_str;
    value = *event;
    arg2 = label_string(*(i32 *)(label_string_ids + 0x8a8));
    result = events_editor_pick_action_civ(event[0x6e],arg2,value,(iptr)name_out);
    if (result == -1) {
      result = -1;
    }
    else {
      event[0x6e] = result;
      arg2 = 2;
      value = label_string(*(i32 *)(label_string_ids + 0x8ac));
      result = events_editor_pick_item(event[0x6d],value,arg2);
      if (result != -1) {
        event[0x6d] = result;
        changed = 1;
      }
    }
  }
  else if (action_bit == 0x2000) {
    changed = 1;
  }
LAB_0054ee13:
  events_compact();
  events_editor_fill_actions(0);
  choice = bits_index_of(action_bit,event[1]);
  listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xb0c),choice);
  events_editor_update_buttons(0);
  events_editor_focus_redraw();
  dlg_set_parent_window(0);
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0054ee8f */ { edit_dtor((Control *)((iptr)&edit_ctl)); }
  return changed;
}
#undef text_buffer
#undef parent_wnd12
#undef parent_wnd11
#undef parent_wnd10
#undef parent_wnd22
#undef parent_wnd9
#undef parent_wnd8
#undef parent_wnd7
#undef default_value
#undef parent_wnd6
#undef parent_wnd5
#undef parent_wnd4
#undef parent_wnd3
#undef parent_wnd2
#undef changed
#undef event
#undef input_buf
#undef idx
#undef edit_ctl
#undef number_value
#undef choice
#undef default_text
#undef result
#undef name_str
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 0054eeb4 auto */
void __cdecl events_editor_on_edit_action(i32 mode)

{
  events_editor_edit_action(mode);
  return;
}

/* 0054eed0 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define parent_wnd2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define event (*(int * *)(frame_ + FRAME_OFF(8)))
#define action_index (*(int *)(frame_ + FRAME_OFF(12)))
#define sel_index (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl events_editor_on_add_action(void)

{
  LPCSTR lpCaption;
  LPCSTR lpText;
  i32 list_pos;
  int result;
  UINT uType;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  action_index = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  event = (int *)events_list_head;
  while ((event != (int *)0x0 && (action_index != 0))) {
    event = (int *)event[0x6f];
    action_index--;
  }
  if (*event == 0x20) {
    action_index = 0;
    while ((1 << ((byte)action_index & 0x1f) & (event[1] | 0xfffffe6fU)) != 0) {
      action_index++;
    }
  }
  else {
    action_index = 0;
    while ((event[1] & 1 << ((byte)action_index & 0x1f)) != 0) {
      action_index++;
    }
  }
  if (action_index < 0xd) {
    while( true ) {
      if (active_editor_wnd == 0) {
        parent_wnd2 = 0;
      }
      else {
        parent_wnd2 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(parent_wnd2);
      dlg_help_pressed = 0;
      if (*event == 0x20) {
        action_index = editor_options_dialog(ADDR(0x6332bc, ((u8 *)&g.d_006332bc)),action_index,event[1] | 0xfffffe6f,1);
      }
      else {
        action_index = editor_options_dialog(ADDR(0x6332c4, ((u8 *)&g.d_006332c4)),action_index,event[1],1);
      }
      dlg_set_parent_window(0);
      if (dlg_help_pressed == 0) break;
      events_editor_help_action(action_index);
    }
    if (action_index != -1) {
      event[1] = event[1] | 1 << ((byte)action_index & 0x1f);
      list_pos = bits_index_of(1 << ((byte)action_index & 0x1f),event[1]);
      events_editor_fill_actions(0);
      listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xb0c),list_pos);
      result = events_editor_edit_action(0);
      if (result == 0) {
        sel_index = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
        event = (int *)events_list_head;
        while ((event != (int *)0x0 && (sel_index != 0))) {
          event = *(int **)((int)event + 0x1bc);
          sel_index--;
        }
        *(uint *)((int)event + 4) =
             *(uint *)((int)event + 4) & ~(1 << ((byte)action_index & 0x1f));
        events_editor_fill_actions(0);
      }
    }
  }
  else {
    uType = 0;
    lpCaption = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8d0));
    lpText = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8cc));
    MessageBoxA((HWND)0x0,lpText,lpCaption,uType);
  }
  events_editor_focus_redraw();
  return;
}
#undef dlg_help_pressed
#undef parent_wnd2
#undef event
#undef action_index
#undef sel_index

/* 0054f16b auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __thiscall events_editor_draw(ViewWindow *this)

{
  u32 top;
  uptr line_height;
  iptr label;
  int bar_y;
  uint bar_height;
  int x;
  
  frame_wnd_draw_caption((FrameWindow *)this);
  gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1a);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  x = this->client_x + (int)this->client_width / 2;
  top = this->client_y;
  line_height = this->sci_rate_sel;
  text_clear();
  label = label_string(*(i32 *)(label_string_ids + 0x8d4));
  text_append_str(label);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),x,(top - line_height) + 0x19,0);
  top = this->client_y;
  line_height = this->sci_rate_sel;
  text_clear();
  label = label_string(*(i32 *)(label_string_ids + 0x8d8));
  text_append_str(label);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),x,(top - line_height) + 0xc3,0);
  top = this->client_x;
  x = top + 0x211;
  bar_y = this->client_y + 0x1a;
  text_clear();
  _sprintf(&text_buffer,&events_pool_free_fmt,(uint)events_pool_bytes_free);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),top + 0x216,(bar_y - this->sci_rate_sel) - 2,0);
  bar_height = ((uint)events_pool_bytes_free * 0x13b) / (uint)events_pool_size;
  gfx_fill_rect_xywh((iptr)this,x,bar_y,10,bar_height,0x2a);
  gfx_fill_rect_xywh((iptr)this,x,bar_height + bar_y,10,0x13b - bar_height,0x6a);
  gfx_draw_frame_rect((iptr)this,x,bar_y,10,0x13b,10);
  gfx_draw_frame_rect((iptr)this,x,bar_y,10,bar_height,10);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef text_buffer

/* 0054f3b9 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define editor_value_clamped (*(i32 *)((u8 *)&g.d_0062e014))
#define events_editor_backup (*(ScenarioEvents * *)((u8 *)&g.d_00632578))
#define parent6 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define parent5 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define parent4 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define list_parent2 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define list_parent (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define parent9 (*(u8 * *)(frame_ + FRAME_OFF(28)))
#define parent8 (*(u8 * *)(frame_ + FRAME_OFF(32)))
#define parent7 (*(u8 * *)(frame_ + FRAME_OFF(36)))
#define parent3 (*(u8 * *)(frame_ + FRAME_OFF(40)))
#define parent22 (*(u8 * *)(frame_ + FRAME_OFF(44)))
#define parent2 (*(u8 * *)(frame_ + FRAME_OFF(48)))
#define backup (*(ScenarioEvents * *)(frame_ + FRAME_OFF(60)))
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(76)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(92)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1168)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(1172)))
#define seh_state (*(int *)(frame_ + FRAME_OFF(1176)))
void __thiscall events_editor_run(DocumentWindow *this)

{
  ScenarioEvents *this_00;
  uptr font_height;
  i32 title;
  int x;
  int y;
  iptr label;
  i32 style;
  i32 arg_x;
  i32 arg_y;
  u32 width;
  u32 height;
  i32 arg_a;
  i32 arg_b;
  i32 arg_c;
  i8 frame_[FRAME_OFF(1184)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  palette_init(&palette);
  seh_state = 0;
  editor_running = 1;
  active_editor_wnd = (iptr)this;
  this_00 = operator_new(0x310);
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  if (this_00 == (ScenarioEvents *)0x0) {
    backup = (ScenarioEvents *)0x0;
  }
  else {
    backup = (ScenarioEvents *)events_ctor(this_00,50000);
  }
  seh_state = (uint)(*(i32 *)((char *)&seh_state + 1)) << 8;
  events_editor_backup = backup;
  events_reset(backup,50000);
  events_copy((iptr)events_editor_backup,ADDR(0x64b690, ((u8 *)&g.d_0064b690)));
  font_set((GameFont *)&editor_font,0,editor_font_size);
  ui_set_default_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_text_color(0x29);
  ui_set_ctrl_text_shadow(0x12,1,1);
  ui_set_ctrl_disabled_color(0x25);
  this->rates_civ = 0x230;
  this->max_rate_value = 0x17c;
  this->init_tax_rate = 0;
  editor_next_ctrl_id = 0xc9;
  font_height = font_cached_height((GameFont *)&editor_font);
  this->sci_rate_sel = font_height;
  arg_c = 0;
  arg_b = 0;
  arg_a = 0;
  height = this->max_rate_value;
  width = this->rates_civ;
  arg_y = 0;
  arg_x = 0;
  style = 0xd;
  title = label_string(*(i32 *)(label_string_ids + 0x73c));
  frame_wnd_create
            ((FrameWindow *)this,title,style,arg_x,arg_y,width,height,arg_a,arg_b,arg_c);
  x = font_line_spacing((GameFont *)dialog_font_ptr);
  this->lux_rate_sel = x + 8;
  this->tax_rate_sel = 0x97;
  y = this->client_y + 0x90;
  x = this->client_x + 0x32;
  rect_set_xywh((iptr)rect,x,y,this->tax_rate_sel,this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent2 = (u8 *)0x0;
  }
  else {
    parent2 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8dc));
  button_create
            ((Control *)(this->pad_65c + 0x2d0),(iptr)parent2,0x65,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_65c + 0x2d0),ADDR(0x403643, events_editor_on_add_trigger));
  x = x + this->tax_rate_sel + 3;
  rect_set_xywh((iptr)rect,x,y,this->tax_rate_sel,this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent22 = (u8 *)0x0;
  }
  else {
    parent22 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8e0));
  button_create
            ((Control *)(this->pad_65c + 0x30c),(iptr)parent22,0x65,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_65c + 0x30c),ADDR(0x40114a, events_editor_on_edit_trigger));
  rect_set_xywh((iptr)rect,x + this->tax_rate_sel + 3,y,this->tax_rate_sel,
                     this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent3 = (u8 *)0x0;
  }
  else {
    parent3 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8e4));
  button_create
            ((Control *)(this->pad_980 + 0x24),(iptr)parent3,0x65,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_980 + 0x24),ADDR(0x40164a, events_editor_on_delete_trigger));
  y = this->client_y + 0x13a;
  x = this->client_x + 0x32;
  rect_set_xywh((iptr)rect,x,y,this->tax_rate_sel,this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent7 = (u8 *)0x0;
  }
  else {
    parent7 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8dc));
  button_create
            ((Control *)(this->pad_980 + 0x60),(iptr)parent7,0x65,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_980 + 0x60),ADDR(0x402c84, events_editor_on_add_action));
  x = x + this->tax_rate_sel + 3;
  rect_set_xywh((iptr)rect,x,y,this->tax_rate_sel,this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent8 = (u8 *)0x0;
  }
  else {
    parent8 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8e0));
  button_create
            ((Control *)&this->edit_action_button,(iptr)parent8,0x65,(iptr)rect,label);
  button_set_callback((Control *)&this->edit_action_button,ADDR(0x402919, events_editor_on_edit_action));
  rect_set_xywh((iptr)rect,x + this->tax_rate_sel + 3,y,this->tax_rate_sel,
                     this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent9 = (u8 *)0x0;
  }
  else {
    parent9 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8e4));
  button_create
            ((Control *)&this[1].field_30,(iptr)parent9,0x65,(iptr)rect,label);
  button_set_callback((Control *)&this[1].field_30,ADDR(0x4027c5, events_editor_on_delete_action));
  rect_set_xywh((iptr)rect,this->client_x + 0x32,this->client_y + 0x1b,0x1cb,0x6e);
  x = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (DocumentWindow *)0x0) {
    list_parent = (u8 *)0x0;
  }
  else {
    list_parent = this->pad_48;
  }
  listbox_create
            ((Control *)(this[1].pad_48 + 0x60),(iptr)list_parent,x,(iptr)rect);
  listbox_set_font((ListBoxFontView *)(this[1].pad_48 + 0x60),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  listbox_set_select_callback((ListBoxSelectSetView *)(this[1].pad_48 + 0x60),ADDR(0x4038f0, events_editor_fill_actions));
  listbox_set_dblclick_callback((ListBoxDblClickSetView *)(this[1].pad_48 + 0x60),ADDR(0x40114a, events_editor_on_edit_trigger));
  events_editor_fill_triggers();
  listbox_set_cur_sel((ListBoxSetSelView *)(this[1].pad_48 + 0x60),0);
  rect_set_xywh((iptr)rect,this->client_x + 0x32,this->client_y + 0xc5,0x1cb,0x6e);
  x = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (DocumentWindow *)0x0) {
    list_parent2 = (u8 *)0x0;
  }
  else {
    list_parent2 = this->pad_48;
  }
  listbox_create
            ((Control *)(this[1].pad_48 + 0x9c),(iptr)list_parent2,x,(iptr)rect);
  listbox_set_font((ListBoxFontView *)(this[1].pad_48 + 0x9c),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  listbox_set_select_callback((ListBoxSelectSetView *)(this[1].pad_48 + 0x9c),ADDR(0x401983, events_editor_update_buttons));
  listbox_set_dblclick_callback((ListBoxDblClickSetView *)(this[1].pad_48 + 0x9c),ADDR(0x402919, events_editor_on_edit_action));
  events_editor_fill_actions(0);
  events_editor_update_buttons(0);
  this->tax_rate_sel = (int)(this->client_width - 8) / 3;
  y = (this->client_y + this->client_height) - (this->lux_rate_sel + 2);
  x = this->client_x + 2;
  rect_set_xywh((iptr)rect,x,y,this->tax_rate_sel,this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent4 = (u8 *)0x0;
  }
  else {
    parent4 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)(this->pad_65c + 0x78),(iptr)parent4,0x65,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_65c + 0x78),ADDR(0x402ced, events_editor_on_ok));
  x = x + this->tax_rate_sel + 2;
  rect_set_xywh((iptr)rect,x,y,this->tax_rate_sel,this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent5 = (u8 *)0x0;
  }
  else {
    parent5 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)(this->pad_65c + 0xb4),(iptr)parent5,0x66,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_65c + 0xb4),ADDR(0x401861, events_editor_on_help));
  rect_set_xywh((iptr)rect,x + this->tax_rate_sel + 2,y,this->tax_rate_sel,
                     this->lux_rate_sel);
  if (this == (DocumentWindow *)0x0) {
    parent6 = (u8 *)0x0;
  }
  else {
    parent6 = this->pad_48;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)(this->pad_65c + 0xf0),(iptr)parent6,0x66,(iptr)rect,label);
  button_set_callback((Control *)(this->pad_65c + 0xf0),ADDR(0x40317a, events_editor_on_cancel));
  ctrl_set_cancel_button((Control *)(this->pad_65c + 0xf0));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  editor_value_clamped = 0;
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402ed2, events_editor_focus_redraw));
  wnd_repaint((SurfaceWindow *)this);
  window_show((WindowObjectView *)this);
  wnd_run_modal_loop((ModalMenuWindow *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (events_editor_backup != (ScenarioEvents *)0x0) {
    events_delete((DialogCore *)events_editor_backup,1);
  }
  events_editor_backup = (ScenarioEvents *)0x0;
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0054ffa4 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef editor_next_ctrl_id
#undef editor_running
#undef editor_value_clamped
#undef events_editor_backup
#undef parent6
#undef parent5
#undef parent4
#undef list_parent2
#undef list_parent
#undef parent9
#undef parent8
#undef parent7
#undef parent3
#undef parent22
#undef parent2
#undef backup
#undef rect
#undef palette
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 0054ffc8 auto */
#define editor_wnd (*(DocumentWindow *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl events_editor_open(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  editor_wnd_ctor(&editor_wnd);
  seh_state = 0;
  events_editor_run(&editor_wnd);
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00550017 */ { editor_wnd_dtor((EditorWindow *)((iptr)&editor_wnd)); }
  return;
}
#undef editor_wnd
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00551cd0 auto */
DialogCore * __thiscall events_delete(DialogCore *this,uint flags)

{
  events_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00554297 auto */
#define mp_turn_time_limit_ms (*(i32 *)((u8 *)&g.d_00654b70))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define password_count (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl cheat_toggle_mode(void)

{
  ushort was_flag80;
  ushort new_flags;
  int answer;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  password_count = 0;
  for (civ = 0; civ < 8; civ++) {
    if (*(int *)(&civ_has_password + civ * 4) != 0) {
      password_count++;
    }
  }
  if (password_count == 0) {
    if (((game.game_options & 0x8000) == 0) && ((game.game_flags & 0x10) == 0)) {
      answer = popup_game_with_sprite(ADDR(0x633740, ((u8 *)&g.d_00633740)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (answer == 0) {
        return;
      }
      new_flags = game.game_flags | 0x10;
      was_flag80 = game.game_flags & 0x80;
      game.game_flags = new_flags;
      if (was_flag80 != 0) {
        popup_text(ADDR(0x633754, ((u8 *)&g.d_00633754)),ADDR(0x63374c, ((u8 *)&g.d_0063374c)));
      }
    }
    game.game_options = game.game_options ^ 0x8000;
    if ((game.multiplayer == '\0') || ((game.game_options & 0x8000) == 0)) {
      if (game.multiplayer != '\0') {
        mp_turn_timer_stop(1);
        mp_turn_time_limit_ms = cheat_saved_turn_time_ms;
        mp_turn_timer_resume(1);
      }
    }
    else {
      mp_turn_timer_stop(1);
      cheat_saved_turn_time_ms = mp_turn_time_limit_ms;
      mp_turn_time_limit_ms = 0;
    }
    menu_update_states();
  }
  else {
    text_set_number_arg(0,password_count);
    if (password_count == 1) {
      popup_game_with_sprite(ADDR(0x633718, ((u8 *)&g.d_00633718)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
    else {
      popup_game_with_sprite(ADDR(0x63372c, ((u8 *)&g.d_0063372c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
  }
  return;
}
#undef mp_turn_time_limit_ms
#undef civ
#undef password_count

/* 00554423 auto */
void __cdecl cheat_tech_advance(void)

{
  uptr civ;
  
  civ = dbg_pick_player(0);
  if (-1 < (int)civ) {
    civ_research_complete(civ,0);
  }
  return;
}

/* 00554460 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl cheat_toggle_all_advances(uptr civ)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civs[civ].future_techs == '\0') {
    for (advance = 0; advance < 100; advance++) {
      civ_give_advance(civ,advance,0,0,0);
    }
    civs[civ].future_techs = 1;
    popup_debug_text(ADDR(0x63375c, ((u8 *)&g.d_0063375c)));
  }
  else {
    for (advance = 0; advance < 0xd; advance++) {
      *(i8 *)&civs[civ].advances[advance] = 0;
    }
    for (advance = 0; advance < 100; advance++) {
      game.advance_known_by[advance] =
           game.advance_known_by[advance] & ~(byte)(1 << ((byte)civ & 0x1f));
    }
    civs[civ].future_techs = '\0';
    civs[civ].num_advances = 1;
    popup_debug_text(ADDR(0x633768, ((u8 *)&g.d_00633768)));
  }
  city_window_refresh((FrameWindow *)&city_window);
  return;
}
#undef advance

/* 005545d3 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define civ_byte (*(byte *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define bit_mask (*(i8 (*)[4])(frame_ + FRAME_OFF(12)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define last_choice (*(int *)(frame_ + FRAME_OFF(772)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(776)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl cheat_edit_technologies(void)

{
  uptr civ;
  iptr has_it;
  iptr has_preq1;
  int advance3;
  int already_known;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  last_choice = -1;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  unit_blink_active = 0;
  civ = dbg_pick_player(0);
  if ((int)civ < 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0055493e */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    while( true ) {
      dlg_load_game_section(&dialog2,ADDR(0x633774, ((u8 *)&g.d_00633774)),1);
      for (advance = 0; advance < 100; advance++) {
        if (advances[advance].enabled != '\0') {
          text_clear();
          text_append_string_id(advances[advance].name);
          text_append_space();
          has_it = civ_has_advance(civ,advance);
          if (has_it == 0) {
            has_preq1 = civ_has_advance(civ,(int)advances[advance].preq[0]);
            if ((has_preq1 == 0) ||
               (advance3 = civ_has_advance(civ,(int)advances[advance].preq[1]), advance3 == 0)) {
              text_append(ADDR(0x633784, ((u8 *)&g.d_00633784)));
            }
          }
          else {
            text_append(ADDR(0x633780, ((u8 *)&g.d_00633780)));
          }
          dialog_add_option((DialogOptionList *)&dialog2,ADDR(0x679640, ((u8 *)&g.d_00679640)),advance,0);
        }
      }
      if (-1 < last_choice) {
        dialog_set_default_choice((DialogOptionList *)&dialog2,last_choice);
      }
      advance3 = dlg_show_modal(&dialog2,0);
      if (advance3 < 0) break;
      if (dialog2.result_extra == 0) {
        already_known = civ_has_advance(civ,advance3);
        if (already_known == 0) {
          civ_give_advance(civ,advance3,0,0,0);
        }
        else {
          bit_index_split(advance3,(iptr)&advance2,(iptr)bit_mask);
          civs[civ].advances[advance2] =
               civs[civ].advances[advance2] & ~bit_mask[0];
          civ_byte = (byte)civ;
          game.advance_known_by[advance3] =
               game.advance_known_by[advance3] & ~(byte)(1 << (civ_byte & 0x1f));
        }
        civs[civ].num_advances = '\0';
        last_choice = advance3;
        for (advance = 0; advance < 100; advance++) {
          advance3 = civ_has_advance(civ,advance);
          if (advance3 != 0) {
            civs[civ].num_advances++;
          }
        }
        city_window_refresh((FrameWindow *)&city_window);
      }
      else {
        cheat_toggle_all_advances(civ);
      }
    }
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0055493e */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  return;
}
#undef unit_blink_active
#undef civ_byte
#undef advance
#undef advance2
#undef bit_mask
#undef dialog2
#undef last_choice
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00554962 auto */
void __cdecl cheat_force_government(void)

{
  int civ;
  
  civ = dbg_pick_player(0);
  if (-1 < civ) {
    civ_select_government_dialog(civ,1);
  }
  return;
}

/* 0055499f auto */
#define cheat_terrain_saved_bits (*(int *)((u8 *)&g.d_00633678))
#define dlg_check_bits (*(int *)((u8 *)&g.d_00631ed8))
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define min_landmass (*(int *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(776)))
#define y2 (*(int *)(frame_ + FRAME_OFF(780)))
#define dir (*(iptr *)(frame_ + FRAME_OFF(784)))
#define improvements2 (*(byte *)(frame_ + FRAME_OFF(788)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(792)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(800)))
void __cdecl cheat_change_terrain(void)

{
  byte old_terrain_byte;
  int result;
  byte *tile;
  uptr terrain;
  iptr x;
  uint old_terrain;
  uptr option_terrain;
  i32 option_flags;
  uptr first_terrain;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  result = map_in_bounds((int)map_cursor_x,(int)map_cursor_y);
  if (result == 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    result = tile_city_owner((int)map_cursor_x,(int)map_cursor_y);
    if (result < 0) {
      tile = (byte *)tile_at((int)map_cursor_x,(int)map_cursor_y);
      old_terrain_byte = tile_terrain((int)map_cursor_x,(int)map_cursor_y);
      old_terrain = (uint)old_terrain_byte;
      terrain2 = old_terrain;
      result = tile_is_ocean((int)map_cursor_x,(int)map_cursor_y);
      if (result == 0) {
        dialog_load_text(&dialog2,ADDR(0x633794, ((u8 *)&g.d_00633794)),ADDR(0x633788, ((u8 *)&g.d_00633788)),1);
        option_flags = 0;
        first_terrain = terrain2;
        x = label_string(terrain_types[terrain2].name);
        dialog_add_option((DialogOptionList *)&dialog2,x,first_terrain,option_flags);
        while (-1 < terrain_types[terrain2].irrigate_to) {
          terrain = (uptr)terrain_types[terrain2].irrigate_to;
          option_flags = 0;
          terrain2 = terrain;
          x = label_string(terrain_types[terrain].name);
          dialog_add_option((DialogOptionList *)&dialog2,x,terrain,option_flags);
        }
        if (old_terrain != terrain2) {
          if ((cheat_terrain_saved_bits < 0) &&
             (terrain2 = dlg_show_modal(&dialog2,0), (int)terrain2 < 0)) {
            seh_state = 0xffffffff;
            /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
            goto LAB_005551a5;
          }
          *tile = *tile & 0x80;
          *tile = *tile | (byte)terrain2;
        }
        improvements2 = tile[1];
        dlg_check_set(0,improvements2 & 4);
        dlg_check_set(1,improvements2 & 8);
        dlg_check_set(2,improvements2 & 0x10);
        dlg_check_set(3,improvements2 & 0x20);
        dlg_check_set(4,(uint)((improvements2 & 0x42) == 0x40));
        dlg_check_set(5,(uint)((improvements2 & 0x42) == 0x42));
        dlg_check_set(6,improvements2 & 0x80);
        if (cheat_terrain_saved_bits < 0) {
          result = popup_text_flags(ADDR(0x6337a4, ((u8 *)&g.d_006337a4)),ADDR(0x63379c, ((u8 *)&g.d_0063379c)),1);
          if (result < 0) {
            seh_state = 0xffffffff;
            /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
            goto LAB_005551a5;
          }
          if (dlg_help_pressed == 0) {
            cheat_terrain_saved_bits = dlg_check_bits;
          }
        }
        else {
          dlg_check_bits = cheat_terrain_saved_bits;
        }
        if (dlg_help_pressed == 0) {
          if ((improvements2 & 0x80) != 0) {
            game.polluted_tiles--;
          }
          improvements2 = improvements2 & 1;
          result = dlg_check_get(0);
          if (result != 0) {
            improvements2 = improvements2 | 4;
          }
          result = dlg_check_get(1);
          if (result != 0) {
            improvements2 = improvements2 | 8;
          }
          result = dlg_check_get(2);
          if (result != 0) {
            improvements2 = improvements2 | 0x10;
          }
          result = dlg_check_get(3);
          if (result != 0) {
            improvements2 = improvements2 | 0x30;
          }
          result = dlg_check_get(4);
          if (result != 0) {
            improvements2 = improvements2 | 0x40;
          }
          result = dlg_check_get(5);
          if (result != 0) {
            improvements2 = improvements2 | 0x42;
          }
          result = dlg_check_get(6);
          if (result != 0) {
            improvements2 = improvements2 | 0x80;
            game.polluted_tiles++;
          }
          tile[1] = improvements2;
          for (civ = 1; civ < 8; civ++) {
            result = tile_visible_to((int)map_cursor_x,(int)map_cursor_y,civ);
            if (result != 0) {
              tile_update_known((int)map_cursor_x,(int)map_cursor_y,civ);
            }
          }
          map_redraw_area_all_views((int)map_cursor_x,(int)map_cursor_y,1,human_civ,1);
          seh_state = 0xffffffff;
          /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
          goto LAB_005551a5;
        }
      }
      dialog_close(&dialog2);
      dialog_init_defaults(&dialog2);
      dialog_load_text(&dialog2,ADDR(0x6337b8, ((u8 *)&g.d_006337b8)),ADDR(0x6337ac, ((u8 *)&g.d_006337ac)),1);
      for (terrain2 = 0; (int)terrain2 < 0xb; terrain2++) {
        option_flags = 0;
        option_terrain = terrain2;
        x = label_string(terrain_types[terrain2].name);
        dialog_add_option((DialogOptionList *)&dialog2,x,option_terrain,option_flags);
        if (old_terrain == terrain2) {
          dialog_set_default_choice((DialogOptionList *)&dialog2,terrain2);
        }
      }
      terrain2 = dlg_show_modal(&dialog2,0);
      if ((int)terrain2 < 0) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      }
      else if (old_terrain == terrain2) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      }
      else {
        if (terrain2 == 10) {
          *tile = 10;
          min_landmass = 0x3f;
          for (dir = 0; dir < 8; dir++) {
            x = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)map_cursor_x);
            y2 = (int)(char)(&dir_dy_table)[dir] + (int)map_cursor_y;
            result = map_in_bounds(x,y2);
            if (((result != 0) && (result = tile_is_ocean(x,y2), result != 0)) &&
               (result = tile_landmass(x,y2), result < min_landmass)) {
              min_landmass = result;
            }
          }
          tile[3] = (byte)min_landmass;
        }
        else {
          *tile = *tile & 0x80;
          *tile = *tile | (byte)terrain2;
          if (old_terrain == 10) {
            min_landmass = 0x3f;
            for (dir = 0; dir < 8; dir++) {
              x = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)map_cursor_x);
              y2 = (int)(char)(&dir_dy_table)[dir] + (int)map_cursor_y;
              result = map_in_bounds(x,y2);
              if (((result != 0) && (result = tile_is_ocean(x,y2), result == 0)) &&
                 (result = tile_landmass(x,y2), result < min_landmass)) {
                min_landmass = result;
              }
            }
            tile[3] = (byte)min_landmass;
          }
        }
        map_redraw_tile_all_views((int)map_cursor_x,(int)map_cursor_y);
        seh_state = 0xffffffff;
        /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      }
    }
    else {
      seh_state = 0xffffffff;
      /* inlined unwind funclet 0055518f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
  }
LAB_005551a5:
  return;
}
#undef cheat_terrain_saved_bits
#undef dlg_check_bits
#undef dlg_help_pressed
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef civ
#undef min_landmass
#undef dialog2
#undef terrain2
#undef y2
#undef dir
#undef improvements2
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 005551b3 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(760)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(768)))
void __cdecl cheat_create_unit(void)

{
  iptr obsolete_known;
  iptr has_prereq;
  int unit;
  iptr civ_name;
  i32 option_flags;
  iptr option_civ;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  if (human_civ != cheat_unit_last_human_civ) {
    cheat_unit_last_human_civ = human_civ;
    cheat_unit_owner_civ = 0xffffffff;
  }
  if ((int)cheat_unit_owner_civ < 0) {
    cheat_unit_owner_civ = human_civ;
  }
  while( true ) {
    dialog_load_text(&dialog2,ADDR(0x6337cc, ((u8 *)&g.d_006337cc)),ADDR(0x6337c0, ((u8 *)&g.d_006337c0)),1);
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      if ((((unit_types[unit_type].obsolete_by < '\0') ||
           (obsolete_known = civ_has_advance(cheat_unit_owner_civ,(int)unit_types[unit_type].obsolete_by),
           obsolete_known == 0)) || (cheat_unit_show_obsolete != '\0')) &&
         ((cheat_unit_ignore_prereq != '\0' ||
          (has_prereq = civ_has_advance(cheat_unit_owner_civ,(int)unit_types[unit_type].prerequisite),
          has_prereq != 0)))) {
        text_clear();
        if (cheat_unit_veteran != '\0') {
          text_append_label(0xd);
          text_append_space();
        }
        text_append_string_id(unit_types[unit_type].name);
        dialog_add_option((DialogOptionList *)&dialog2,ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_type,0);
        if (cheat_unit_last_type < 0) {
          cheat_unit_last_type = unit_type;
        }
      }
    }
    if (-1 < cheat_unit_last_type) {
      dialog_set_default_choice((DialogOptionList *)&dialog2,cheat_unit_last_type);
    }
    unit = dlg_show_modal(&dialog2,0);
    cheat_unit_last_type = unit;
    if (unit < 0) break;
    switch(dialog2.result_extra) {
    case 1:
      dlg_reset(&dialog2,1);
      for (cheat_unit_owner_civ = 0; (int)cheat_unit_owner_civ < 8; cheat_unit_owner_civ++) {
        if ((cheat_unit_owner_civ == 0) || ((1 << ((byte)cheat_unit_owner_civ & 0x1f) & (uint)game.civs_alive) != 0)
           ) {
          option_flags = 0;
          option_civ = cheat_unit_owner_civ;
          civ_name = civ_name_plural(cheat_unit_owner_civ);
          dialog_add_option((DialogOptionList *)&dialog2,civ_name,option_civ,option_flags);
        }
      }
      cheat_unit_owner_civ = dlg_show_modal(&dialog2,0);
      if ((int)cheat_unit_owner_civ < 0) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 005555eb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      }
      else {
switchD_00555538_default:
        unit = unit_create(unit,cheat_unit_owner_civ,(int)map_cursor_x,(int)map_cursor_y);
        if ((-1 < unit) && (cheat_unit_veteran != '\0')) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        map_redraw_tile_all_views((int)map_cursor_x,(int)map_cursor_y);
        unit_blink_active = 0;
        seh_state = 0xffffffff;
        /* inlined unwind funclet 005555eb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      }
LAB_00555601:
      return;
    case 2:
      cheat_unit_veteran = cheat_unit_veteran == '\0';
      cheat_unit_last_type = -1;
      break;
    case 3:
      cheat_unit_show_obsolete = cheat_unit_show_obsolete == '\0';
      cheat_unit_last_type = -1;
      break;
    case 4:
      cheat_unit_ignore_prereq = cheat_unit_ignore_prereq == '\0';
      cheat_unit_last_type = -1;
      break;
    default:
      goto switchD_00555538_default;
    }
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 005555eb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  goto LAB_00555601;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef unit_blink_active
#undef unit_type
#undef dialog2
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 0055560f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define view_civ_byte (*(i8 *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl cheat_reveal_map(void)

{
  iptr label;
  int choice;
  iptr option_id;
  i32 option_flags;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  dialog_load_text(&dialog2,ADDR(0x6337e0, ((u8 *)&g.d_006337e0)),ADDR(0x6337d4, ((u8 *)&g.d_006337d4)),1);
  for (civ = 0; civ < 8; civ++) {
    text_clear();
    label = civ_get_adjective(civ);
    text_append(label);
    dialog_add_option((DialogOptionList *)&dialog2,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
  }
  option_flags = 0;
  option_id = 0x62;
  label = label_string(*(i32 *)(label_string_ids + 0x13c));
  dialog_add_option((DialogOptionList *)&dialog2,label,option_id,option_flags);
  option_flags = 0;
  option_id = 99;
  label = label_string(*(i32 *)(label_string_ids + 0x138));
  dialog_add_option((DialogOptionList *)&dialog2,label,option_id,option_flags);
  if ((game.reveal_map == '\0') && (game.view_civ < '\0')) {
    dialog_set_default_choice((DialogOptionList *)&dialog2,0x62);
  }
  else {
    dialog_set_default_choice((DialogOptionList *)&dialog2,99);
  }
  choice = dlg_show_modal(&dialog2,0);
  if (choice < 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0055581b */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    if (choice == 0x62) {
      game.reveal_map = 1;
      game.view_civ = -1;
    }
    else if (choice == 99) {
      game.reveal_map = '\0';
      game.view_civ = -1;
    }
    else {
      game.reveal_map = '\0';
      view_civ_byte = (i8)choice;
      game.view_civ = view_civ_byte;
    }
    if (-1 < game.view_civ) {
      human_civ = (iptr)game.view_civ;
      game.human_players = (u8)(1 << (game.view_civ & 0x1fU));
    }
    mapview_update_title((FrameWindow *)&map_views);
    map_redraw_all_views(human_civ,1);
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0055581b */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  return;
}
#undef human_civ
#undef civ
#undef view_civ_byte
#undef dialog2
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 0055583f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define civ_byte (*(byte *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl cheat_set_human_player(void)

{
  iptr label;
  int choice;
  iptr option_id;
  i32 option_flags;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  dialog_load_text(&dialog2,ADDR(0x6337f4, ((u8 *)&g.d_006337f4)),ADDR(0x6337e8, ((u8 *)&g.d_006337e8)),1);
  for (civ = 1; civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
      text_clear();
      label = civ_get_adjective(civ);
      text_append(label);
      dialog_add_option((DialogOptionList *)&dialog2,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
    }
  }
  option_flags = 0;
  option_id = 99;
  label = label_string(*(i32 *)(label_string_ids + 0x140));
  dialog_add_option((DialogOptionList *)&dialog2,label,option_id,option_flags);
  choice = dlg_show_modal(&dialog2,0);
  if (choice < 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 005559de */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    if (choice == 99) {
      game.human_players = '\0';
      player_turn_active = 0;
    }
    else {
      civ_byte = (byte)choice;
      game.human_players = (u8)(1 << (civ_byte & 0x1f));
      game.player_civ = civ_byte;
      game.turn_civ = civ_byte;
      human_civ = choice;
      map_redraw_all_views(choice,1);
      ui_redraw_all_maps(1);
    }
    seh_state = 0xffffffff;
    /* inlined unwind funclet 005559de */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  return;
}
#undef human_civ
#undef player_turn_active
#undef civ
#undef civ_byte
#undef dialog2
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00555a02 auto */
#define turn_value (*(short (*)[2])(frame_ + FRAME_OFF(0)))
void __cdecl cheat_set_game_year(void)

{
  int result;
  i32 year;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_set_number_arg(0,(int)game.turn);
  result = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6337fc, ((u8 *)&g.d_006337fc)),(int)game.turn,(iptr)turn_value);
  if (result == 0) {
    game.turn = turn_value[0];
    year = game_turn_to_year((int)turn_value[0]);
    game.year = (i16)year;
    status_redraw(1);
    city_window_refresh((FrameWindow *)&city_window);
  }
  return;
}
#undef turn_value

/* 00555a8b auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ2 (*(int *)(frame_ + FRAME_OFF(0)))
#define city (*(uptr *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl cheat_kill_civ(void)

{
  iptr adjective;
  int civ;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  dialog_load_text(&dialog2,ADDR(0x633810, ((u8 *)&g.d_00633810)),ADDR(0x633808, ((u8 *)&g.d_00633808)),1);
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) {
      text_clear();
      adjective = civ_get_adjective(civ2);
      text_append(adjective);
      dialog_add_option((DialogOptionList *)&dialog2,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ2,0);
    }
  }
  civ = dlg_show_modal(&dialog2,0);
  if (civ < 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 00555c8d */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    (*(i8 *)((char *)&civ2 + 0)) = (byte)civ;
    game.human_players = game.human_players & ~(byte)(1 << ((byte)civ2 & 0x1f));
    if (2 < game.multiplayer) {
      net_send_message(0x31,0,0,civ,0,0,0,0,0,0);
    }
    city = (uptr)game.num_cities;
    while (city = city - 1, -1 < (int)city) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        city_delete(city,0);
      }
    }
    civ_check_destroyed(civ,human_civ);
    seh_state = 0xffffffff;
    /* inlined unwind funclet 00555c8d */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  return;
}
#undef human_civ
#undef civ2
#undef city
#undef dialog2
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00555cb1 auto */
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
void __cdecl cheat_destroy_units_at_cursor(void)

{
  iptr unit;
  
  unit = tile_first_unit((int)map_cursor_x,(int)map_cursor_y);
  unit_stack_delete_all(unit,1);
  return;
}
#undef map_cursor_x
#undef map_cursor_y

/* 0055615c auto */
#define gold2 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl cheat_change_money(void)

{
  iptr civ;
  iptr adjective;
  int result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = dbg_pick_player(0);
  if (-1 < civ) {
    adjective = civ_get_adjective(civ);
    text_set_string_arg(0,adjective);
    text_set_number_arg_v(0,civs[civ].gold);
    result = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633818, ((u8 *)&g.d_00633818)),civs[civ].gold,(iptr)&gold2);
    if (result == 0) {
      if (30000 < gold2) {
        gold2 = 30000;
      }
      if (gold2 < 0) {
        gold2 = 0;
      }
      civs[civ].gold = gold2;
      city_window_refresh((FrameWindow *)&city_window);
      status_redraw(1);
    }
  }
  return;
}
#undef gold2

/* 0055625b auto */
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define byte_value (*(u8 *)(frame_ + FRAME_OFF(8)))
#define city (*(iptr *)(frame_ + FRAME_OFF(12)))
#define city_count (*(int *)(frame_ + FRAME_OFF(16)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define damage_input (*(u8 (*)[4])(frame_ + FRAME_OFF(776)))
#define commodity (*(iptr *)(frame_ + FRAME_OFF(780)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(784)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl cheat_edit_unit(void)

{
  char civ;
  int choice;
  iptr label;
  iptr option_id;
  i32 arg;
  iptr commodity_opt;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  choice = map_in_bounds((int)map_cursor_x,(int)map_cursor_y);
  if (choice == 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 005569bf */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    unit = tile_first_unit((int)map_cursor_x,(int)map_cursor_y);
    if (unit < 0) {
      seh_state = 0xffffffff;
      /* inlined unwind funclet 005569bf */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
    else {
      choice = unit_stack_sum(unit,2);
      if (1 < choice) {
        arg = 1;
        label = label_string(*(i32 *)(label_string_ids + 0xf8));
        unit = unit_stack_select_dialog(unit,label,arg);
        if (unit < 0) {
          seh_state = 0xffffffff;
          /* inlined unwind funclet 005569bf */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
          goto LAB_005569d5;
        }
      }
      civ = units[unit].owner;
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              while( true ) {
                while( true ) {
                  label = civ_get_adjective((int)civ);
                  text_set_string_arg(0,label);
                  text_clear();
                  text_append_string_id(unit_types[units[unit].type].name);
                  if ((units[unit].flags & 0x2000) != 0) {
                    text_append_space();
                    text_append_lparen();
                    text_append_label(0xd);
                    text_append_rparen();
                  }
                  text_append_space();
                  text_append_lparen();
                  if (units[unit].home_city == -1) {
                    text_append_label(0xe);
                  }
                  else {
                    text_append((uint)(byte)units[unit].home_city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
                  }
                  text_append_rparen();
                  text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
                  choice = popup_game(ADDR(0x633820, ((u8 *)&g.d_00633820)));
                  if (choice == 0) {
                    seh_state = 0xffffffff;
                    /* inlined unwind funclet 005569bf */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
                    goto LAB_005569d5;
                  }
                  if (choice != 1) break;
                  units[unit].flags = units[unit].flags ^ 0x2000;
                  map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
                  status_redraw(1);
                }
                if (choice != 2) break;
                units[unit].moves_used = '\0';
                map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
                status_redraw(1);
              }
              if (choice != 3) break;
              arg = unit_max_hp(unit);
              text_set_number_arg(0,arg);
              choice = dlg_input_number_game(ADDR(0x63382c, ((u8 *)&g.d_0063382c)),(uint)units[unit].damage,(iptr)damage_input);
              if (choice == 0) {
                units[unit].damage = damage_input[0];
              }
              map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
              status_redraw(1);
            }
            if (choice != 4) break;
            city_count = 0;
            dlg_load_game_section(&dialog2,ADDR(0x63383c, ((u8 *)&g.d_0063383c)),1);
            for (city = 0; city < game.num_cities; city++) {
              if ((cities[city].id != 0) && ((int)cities[city].owner == (int)civ)) {
                dialog_add_option
                          ((DialogOptionList *)&dialog2,(iptr)&cities[city].name,city,0);
                city_count++;
              }
            }
            if ((city_count != 0) &&
               (choice = dlg_show_modal(&dialog2,0), -1 < choice)) {
              if (dialog2.result_extra == 0) {
                byte_value = (u8)choice;
                units[unit].home_city = byte_value;
              }
              else {
                units[unit].home_city = -1;
              }
              map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
              status_redraw(1);
            }
          }
          if (choice != 5) break;
          if (unit_types[units[unit].type].domain == '\0') {
            if (units[unit].orders == 2) {
              units[unit].orders = -1;
            }
            else {
              units[unit].orders = 2;
            }
            map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
            status_redraw(1);
          }
        }
        if (choice != 6) break;
        if (unit_types[units[unit].type].role == 7) {
          dlg_load_game_section(&dialog2,ADDR(0x63384c, ((u8 *)&g.d_0063384c)),1);
          for (commodity = 0; commodity < 0x10; commodity++) {
            arg = 0;
            commodity_opt = commodity;
            label = label_string(commodity_names[commodity]);
            dialog_add_option((DialogOptionList *)&dialog2,label,commodity_opt,arg);
            if ((char)units[unit].counter == commodity) {
              dialog_set_default_choice((DialogOptionList *)&dialog2,commodity);
            }
          }
          arg = 0;
          option_id = 0x10;
          label = label_string(*(i32 *)(label_string_ids + 0x300));
          dialog_add_option((DialogOptionList *)&dialog2,label,option_id,arg);
          if ((char)units[unit].counter < '\0') {
            dialog_set_default_choice((DialogOptionList *)&dialog2,0x10);
          }
          choice = dlg_show_modal(&dialog2,0);
          if (-1 < choice) {
            if (choice < 0x10) {
              byte_value = (u8)choice;
              units[unit].counter = byte_value;
            }
            else {
              units[unit].counter = 0xff;
            }
            map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
            status_redraw(1);
          }
        }
      }
      seh_state = 0xffffffff;
      /* inlined unwind funclet 005569bf */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
  }
LAB_005569d5:
  return;
}
#undef map_cursor_x
#undef map_cursor_y
#undef unit
#undef byte_value
#undef city
#undef city_count
#undef dialog2
#undef damage_input
#undef commodity
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 005569e3 auto */
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define wonder (*(iptr *)(frame_ + FRAME_OFF(760)))
#define number_input (*(i8 (*)[4])(frame_ + FRAME_OFF(764)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(768)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(772)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(776)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl cheat_edit_city(void)

{
  char civ;
  bool has_other;
  iptr in_bounds;
  iptr city;
  iptr adjective;
  int choice;
  i32 on;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  in_bounds = map_in_bounds((int)map_cursor_x,(int)map_cursor_y);
  if (in_bounds == 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 00556f30 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    city = city_at((int)map_cursor_x,(int)map_cursor_y);
    if (city < 0) {
      seh_state = 0xffffffff;
      /* inlined unwind funclet 00556f30 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
    else {
      civ = cities[city].owner;
      while( true ) {
        text_set_number_arg(0,(cities[city].flags & 0x4000000) >> 0x1a);
        text_clear();
        text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
        text_append_space();
        text_append_lparen();
        adjective = civ_get_adjective((int)civ);
        text_append(adjective);
        text_append_rparen();
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        choice = popup_game(ADDR(0x63385c, ((u8 *)&g.d_0063385c)));
        if (choice == 0) break;
        if (choice == 1) {
          choice = dlg_input_number_game(ADDR(0x633868, ((u8 *)&g.d_00633868)),(int)cities[city].size,(iptr)number_input);
          if (choice == 0) {
            cities[city].size = number_input[0];
          }
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
          status_redraw(1);
        }
        else if (choice == 2) {
          for (wonder = 0; wonder < 0x1c; wonder++) {
            if (game.wonder_city[wonder] == city) {
              game.wonder_city[wonder] = -1;
            }
          }
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
          status_redraw(1);
        }
        else if (choice == 3) {
          cities[city].flags = cities[city].flags & 0xfffffffc;
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
        }
        else if (choice == 4) {
          dlg_load_game_section(&dialog2,ADDR(0x633874, ((u8 *)&g.d_00633874)),1);
          has_other = false;
          for (city2 = 0; city2 < game.num_cities; city2++) {
            if ((cities[city2].id != 0) && (city2 != city)) {
              dialog_add_option
                        ((DialogOptionList *)&dialog2,(iptr)&cities[city2].name,city2,0);
              has_other = true;
            }
          }
          if ((has_other) &&
             (city2 = dlg_show_modal(&dialog2,0), -1 < city2)) {
            on = city_has_improvement(city,1);
            for (improvement = 0; improvement < 5; improvement++) {
              *(i8 *)&cities[city].improvements[improvement] =
                   *(i8 *)&cities[city2].improvements[improvement];
            }
            city_set_improvement(city,1,on);
            city_window_refresh((FrameWindow *)&city_window);
          }
        }
        else if (choice == 5) {
          choice = dlg_input_number_game(ADDR(0x633880, ((u8 *)&g.d_00633880)),(int)cities[city].shield_box,(iptr)number_input);
          if (choice == 0) {
            cities[city].shield_box = (*(i16 *)((char *)&number_input + 0));
          }
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
          status_redraw(1);
          city_window_refresh((FrameWindow *)&city_window);
        }
        else {
          if (choice != 6) {
            seh_state = 0xffffffff;
            /* inlined unwind funclet 00556f30 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
            goto LAB_00556f46;
          }
          cities[city].flags = cities[city].flags ^ 0x4000000;
        }
      }
      seh_state = 0xffffffff;
      /* inlined unwind funclet 00556f30 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
  }
LAB_00556f46:
  return;
}
#undef map_cursor_x
#undef map_cursor_y
#undef dialog2
#undef wonder
#undef number_input
#undef improvement
#undef city2
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00556f54 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define gender (*(iptr *)(frame_ + FRAME_OFF(8)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define number_input (*(u8 (*)[4])(frame_ + FRAME_OFF(768)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(772)))
#define gov (*(iptr *)(frame_ + FRAME_OFF(776)))
#define other_civ (*(int *)(frame_ + FRAME_OFF(780)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(784)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl cheat_edit_king(void)

{
  uint *treaty_ptr;
  iptr civ;
  iptr name2;
  int choice;
  i32 value;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  civ = dbg_pick_player(0);
  if (civ < 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 00557e08 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    while( true ) {
      text_set_number_arg(0,(civs[civ].flags & 0x200) >> 9);
      text_clear();
      name2 = civ_leader_name(civ);
      text_append(name2);
      text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      choice = popup_game(ADDR(0x633890, ((u8 *)&g.d_00633890)));
      if (choice == 0) break;
      if (choice == 1) {
        civ2 = dbg_pick_player(0);
        if (-1 < civ2) {
          name2 = civ_leader_name(civ2);
          text_set_string_arg(1,name2);
          dlg_checks_clear();
          dlg_check_set(0,civs[civ].treaties[civ2] & 1);
          dlg_check_set(1,(civs[civ].treaties[civ2] & 2) >> 1);
          dlg_check_set(2,(civs[civ].treaties[civ2] & 4) >> 2);
          dlg_check_set(3,(civs[civ].treaties[civ2] & 8) >> 3);
          dlg_check_set(4,(civs[civ].treaties[civ2] & 0x2000) >> 0xd)
          ;
          dlg_check_set(5,(civs[civ].treaties[civ2] & 0x10) >> 4);
          dlg_check_set(6,(civs[civ].treaties[civ2] & 0x80) >> 7);
          choice = popup_game_flags(ADDR(0x63389c, ((u8 *)&g.d_0063389c)),1);
          if (-1 < choice) {
            diplo_clear_treaty_flags(civ,civ2,0x60);
            choice = dlg_check_get(0);
            if (choice == 0) {
              diplo_clear_treaty_flags(civ,civ2,1);
            }
            else {
              diplo_set_treaty_flags(civ,civ2,1);
            }
            choice = dlg_check_get(4);
            if (choice == 0) {
              diplo_clear_treaty_flags(civ,civ2,0x200e);
              choice = dlg_check_get(1);
              if (choice != 0) {
                diplo_set_treaty_flags(civ,civ2,2);
              }
              choice = dlg_check_get(2);
              if (choice != 0) {
                diplo_set_treaty_flags(civ,civ2,4);
              }
              choice = dlg_check_get(3);
              if (choice != 0) {
                diplo_set_treaty_flags(civ,civ2,8);
              }
            }
            else {
              diplo_set_treaty_flags(civ,civ2,0x2000);
            }
            treaty_ptr = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
            *treaty_ptr = *treaty_ptr & 0xffffff6f;
            choice = dlg_check_get(5);
            if (choice != 0) {
              treaty_ptr = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
              *treaty_ptr = *treaty_ptr | 0x10;
            }
            choice = dlg_check_get(6);
            if (choice != 0) {
              treaty_ptr = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
              *treaty_ptr = *treaty_ptr | 0x80;
            }
          }
        }
      }
      else if (choice == 2) {
        civ2 = dbg_pick_player(0);
        if (-1 < civ2) {
          name2 = civ_leader_name(civ2);
          text_set_string_arg(1,name2);
          text_set_number_arg(0,(int)game.turn);
          choice = dlg_input_number_game(ADDR(0x6338ac, ((u8 *)&g.d_006338ac)),(int)civs[civ].last_treaty_turn[civ2],(iptr)number_input);
          if (choice == 0) {
            civs[civ].last_treaty_turn[civ2] = (*(i16 *)((char *)&number_input + 0));
          }
        }
      }
      else if (choice == 3) {
        civ2 = dbg_pick_player(0);
        if (-1 < civ2) {
          name2 = civ_leader_name(civ2);
          text_set_string_arg(1,name2);
          choice = dlg_input_number_game(ADDR(0x6338b8, ((u8 *)&g.d_006338b8)),(uint)civs[civ].attitude[civ2],
                                     (iptr)number_input);
          if (choice == 0) {
            civs[civ].attitude[civ2] = number_input[0];
          }
        }
      }
      else if (choice == 4) {
        choice = dlg_input_number_game(ADDR(0x6338c8, ((u8 *)&g.d_006338c8)),(uint)civs[civ].reputation,(iptr)number_input);
        if (choice == 0) {
          civs[civ].reputation = number_input[0];
        }
      }
      else if (choice == 5) {
        civs[civ].diplo_request_count = '\0';
      }
      else if (choice == 6) {
        for (other_civ = 0; other_civ < 8; other_civ++) {
          for (civ2 = 0; civ2 < 8; civ2++) {
            civs[civ2].last_treaty_turn[other_civ] = game.turn;
          }
        }
      }
      else if (choice == 7) {
        civ_choose_research_dialog(civ,1);
      }
      else if (choice == 8) {
        value = civ_research_cost(civ);
        text_set_number_arg(0,value);
        choice = dlg_input_number_game(ADDR(0x6338d4, ((u8 *)&g.d_006338d4)),(int)civs[civ].research_progress,(iptr)number_input);
        if (choice == 0) {
          civs[civ].research_progress = (*(i16 *)((char *)&number_input + 0));
          status_redraw(1);
        }
      }
      else if (choice == 9) {
        civs[civ].researching = -1;
      }
      else if (choice == 10) {
        text_clear();
        name2 = civ_name_plural(civ);
        text_append(name2);
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        if (-1 < leaders[civs[civ].tribe].leader_name) {
          value = label_string((int)leaders[civs[civ].tribe].leader_name);
          crt_strcpy((iptr)&civ_names[civ].leader_name,value);
          leaders[civs[civ].tribe].leader_name = -leaders[civs[civ].tribe].leader_name;
        }
        if (-1 < leaders[civs[civ].tribe].plural) {
          value = label_string((int)leaders[civs[civ].tribe].plural);
          crt_strcpy((iptr)&civ_names[civ].tribe_name,value);
          leaders[civs[civ].tribe].plural = -leaders[civs[civ].tribe].plural;
        }
        if (-1 < leaders[civs[civ].tribe].adjective) {
          value = label_string((int)leaders[civs[civ].tribe].adjective);
          crt_strcpy((iptr)&civ_names[civ].adjective,value);
          leaders[civs[civ].tribe].adjective = -leaders[civs[civ].tribe].adjective;
        }
        for (gov = 0; gov < 7; gov++) {
          for (gender = 0; gender < 2; gender++) {
            leaders[civs[civ].tribe].titles[gov][gender] =
                 (short)(&government_titles[gov].male)[gender];
          }
        }
        text_set_string_arg(1,(iptr)&civ_names[civ].tribe_name);
        text_set_string_arg(2,(iptr)&civ_names[civ].adjective);
        dialog_load_text_section
                  (&dialog2,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6338e4, ((u8 *)&g.d_006338e4)),0x17,(iptr)&civ_names[civ].leader_name,0,0,0,1);
        choice = dlg_show_modal(&dialog2,0);
        if (-1 < choice) {
          crt_strcpy((iptr)&civ_names[civ].leader_name,&text_string_args);
          crt_strcpy((iptr)&civ_names[civ].tribe_name,&text_string_arg1);
          crt_strcpy((iptr)&civ_names[civ].adjective,&text_string_arg2);
        }
      }
      else if (choice == 0xb) {
        civ2 = dbg_pick_player(0);
        if (0 < civ2) {
          for (advance = 0; advance < 0xd; advance++) {
            *(i8 *)&civs[civ].advances[advance] =
                 *(i8 *)&civs[civ2].advances[advance];
          }
          civs[civ].num_advances = '\0';
          for (advance = 0; advance < 100; advance++) {
            choice = civ_has_advance(civ,advance);
            if (choice != 0) {
              civs[civ].num_advances++;
            }
          }
        }
      }
      else {
        if (choice != 0xc) {
          seh_state = 0xffffffff;
          /* inlined unwind funclet 00557e08 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
          goto LAB_00557e1e;
        }
        civs[civ].flags = civs[civ].flags ^ 0x200;
        if ((civs[civ].flags & 0x200) == 0) {
          leaders[civs[civ].tribe].female = '\0';
        }
        else {
          leaders[civs[civ].tribe].female = 1;
        }
        civs[civ].leader_portrait = (u8)civs[civ].tribe;
        if (leaders[civs[civ].tribe].female != '\0') {
          civs[civ].leader_portrait += 21;
        }
      }
    }
    seh_state = 0xffffffff;
    /* inlined unwind funclet 00557e08 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
LAB_00557e1e:
  return;
}
#undef advance
#undef gender
#undef dialog2
#undef number_input
#undef civ2
#undef gov
#undef other_civ
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00557e2c auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_victory_thresholds (*(short *)((u8 *)&g.d_0064bcbc))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(12)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define number_input (*(i8 (*)[4])(frame_ + FRAME_OFF(772)))
#define total_value (*(int *)(frame_ + FRAME_OFF(776)))
#define objective_value (*(int *)(frame_ + FRAME_OFF(780)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(784)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl cheat_edit_victory(void)

{
  iptr value;
  iptr owned_value;
  iptr name2;
  int choice;
  int result;
  iptr option_id;
  i32 option_flags;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  while( true ) {
    total_value = 0;
    objective_value = 0;
    for (city = 0; city < game.num_cities; city++) {
      if (cities[city].id != 0) {
        value = city_objective_value(city);
        total_value += value;
        if ((int)cities[city].owner == (int)scenario_objective_civ) {
          owned_value = city_objective_value(city);
          objective_value += owned_value;
        }
      }
    }
    text_clear();
    text_append_int(total_value);
    text_append(ADDR(0x6338f4, ((u8 *)&g.d_006338f4)));
    text_append_int(objective_value);
    text_append(ADDR(0x6338f8, ((u8 *)&g.d_006338f8)));
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    name2 = civ_name_plural((int)scenario_objective_civ);
    text_set_string_arg(0,name2);
    text_set_number_arg(0,((int)(short)scenario_flags & 2U) >> 1);
    text_set_number_arg(1,((int)(short)scenario_flags & 4U) >> 2);
    text_set_number_arg(2,(int)scenario_victory_thresholds);
    text_set_number_arg(3,(int)scenario_marginal_victory_score);
    text_set_number_arg(4,(int)scenario_marginal_defeat_score);
    text_set_number_arg(5,(int)scenario_decisive_defeat_score);
    choice = popup_game(ADDR(0x6338fc, ((u8 *)&g.d_006338fc)));
    if (choice < 1) break;
    if (choice == 1) {
      scenario_flags = scenario_flags ^ 2;
    }
    else if (choice == 2) {
      scenario_flags = scenario_flags ^ 4;
    }
    else if (choice == 3) {
      dlg_reset(&dialog2,1);
      option_flags = 0;
      option_id = 0;
      name2 = label_string(*(i32 *)(label_string_ids + 0x38));
      dialog_add_option((DialogOptionList *)&dialog2,name2,option_id,option_flags);
      for (civ = 1; civ < 8; civ++) {
        option_flags = 0;
        choice = civ;
        name2 = civ_name_plural(civ);
        dialog_add_option((DialogOptionList *)&dialog2,name2,choice,option_flags);
      }
      choice = dlg_show_modal(&dialog2,0);
      if (-1 < choice) {
        scenario_objective_civ = (short)choice;
      }
    }
    else {
      if ((choice < 4) || (7 < choice)) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 00558177 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
LAB_0055818d:
        return;
      }
      result = dlg_input_number_game(ADDR(0x633908, ((u8 *)&g.d_00633908)),(int)(short)(&scenario_year_increment)[choice],(iptr)number_input);
      if (result == 0) {
        (&scenario_year_increment)[choice] = (*(i16 *)((char *)&number_input + 0));
      }
    }
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00558177 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  goto LAB_0055818d;
}
#undef scenario_flags
#undef scenario_objective_civ
#undef scenario_victory_thresholds
#undef scenario_year_increment
#undef civ
#undef city
#undef dialog2
#undef number_input
#undef total_value
#undef objective_value
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 0055819b auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __cdecl cheat_edit_scenario_rules(void)

{
  int choice;
  
  while( true ) {
    while( true ) {
      while( true ) {
        while( true ) {
          text_set_number_arg(0,((int)(short)scenario_flags & 0x10U) >> 4);
          text_set_number_arg(1,((int)(short)scenario_flags & 0x20U) >> 5);
          text_set_number_arg(2,((int)(short)scenario_flags & 0x40U) >> 6);
          text_set_number_arg(3,((int)(short)scenario_flags & 0x8000U) >> 0xf);
          choice = popup_game(ADDR(0x633918, ((u8 *)&g.d_00633918)));
          if (choice == 0) {
            return;
          }
          if (choice != 1) break;
          scenario_flags = scenario_flags ^ 0x10;
        }
        if (choice != 2) break;
        scenario_flags = scenario_flags ^ 0x20;
      }
      if (choice != 3) break;
      scenario_flags = scenario_flags ^ 0x40;
    }
    if (choice != 4) break;
    scenario_flags = scenario_flags ^ 0x8000;
  }
  return;
}
#undef scenario_flags

/* 005582ad auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define scenario_max_turns (*(short *)((u8 *)&g.d_0064bcb8))
#define scenario_name (*(i8 *)((u8 *)&g.d_0064bc62))
#define scenario_start_year (*(short *)((u8 *)&g.d_0064bcb6))
#define scenario_tech_paradigm (*(short *)((u8 *)&g.d_0064bcb2))
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define player (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define name_buf (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
#define tile_ptr (*(iptr *)(frame_ + FRAME_OFF(268)))
#define known_ptrs (*(int (*)[8])(frame_ + FRAME_OFF(272)))
#define tile (*(Tile * *)(frame_ + FRAME_OFF(304)))
#define number_input (*(i8 (*)[4])(frame_ + FRAME_OFF(308)))
#define tile_index (*(int *)(frame_ + FRAME_OFF(312)))
void __cdecl cheat_scenario_params(void)

{
  i32 year;
  iptr label;
  iptr choice;
  iptr result;
  int value;
  uint owner;
  i8 frame_[FRAME_OFF(320)] __attribute__((aligned(8)));  /* original stack frame */
  
  while( true ) {
    year = game_turn_to_year((int)game.turn);
    game.year = (i16)year;
    status_redraw(1);
    city_window_refresh((FrameWindow *)&city_window);
    text_set_number_arg(0,(int)scenario_tech_paradigm);
    text_set_number_arg(1,(int)scenario_year_increment);
    text_set_number_arg(2,(int)scenario_start_year);
    text_set_number_arg(3,(int)scenario_max_turns);
    text_set_number_arg(4,(int)(short)scenario_flags & 1);
    if ((game.game_flags & 0x80) == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0x68c));
      text_set_string_arg(0,label);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0x688));
      text_set_string_arg(0,label);
    }
    text_set_string_arg(1,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)));
    choice = popup_game(ADDR(0x633924, ((u8 *)&g.d_00633924)));
    if (choice == 0) break;
    if (choice == 1) {
      result = dlg_input_number_game(ADDR(0x633930, ((u8 *)&g.d_00633930)),(int)scenario_tech_paradigm,(iptr)number_input);
      if (result == 0) {
        scenario_tech_paradigm = (*(i16 *)((char *)&number_input + 0));
      }
    }
    else if (choice == 2) {
      value = dlg_input_number_game(ADDR(0x633940, ((u8 *)&g.d_00633940)),(int)scenario_year_increment,(iptr)number_input);
      if (value == 0) {
        scenario_year_increment = (*(i16 *)((char *)&number_input + 0));
      }
    }
    else if (choice == 3) {
      value = dlg_input_number_game(ADDR(0x633950, ((u8 *)&g.d_00633950)),(int)scenario_start_year,(iptr)number_input);
      if (value == 0) {
        scenario_start_year = (*(i16 *)((char *)&number_input + 0));
      }
    }
    else if (choice == 4) {
      value = dlg_input_number_game(ADDR(0x633960, ((u8 *)&g.d_00633960)),(int)scenario_max_turns,(iptr)number_input);
      if (value == 0) {
        scenario_max_turns = (*(i16 *)((char *)&number_input + 0));
      }
    }
    else if (choice == 5) {
      tile = map_tiles;
      for (tile_index = 0; tile_index < map.area; tile_index++) {
        if ((tile->owner & 0xf0) == 0xf0) {
          tile->owner = tile->owner & 0xf;
        }
        tile++;
      }
      map_redraw_all_views(human_civ,1);
    }
    else if (choice == 6) {
      tile = map_tiles;
      for (tile_index = 0; tile_index < map.area; tile_index++) {
        if (((tile->owner & 0xf0) != 0xf0) && ((tile->improvements & 3) == 0)) {
          tile->owner = tile->owner | 0xf0;
        }
        tile++;
      }
      map_redraw_all_views(human_civ,1);
    }
    else if (choice == 7) {
      tile_ptr = tile_at(0,0);
      for (player = 1; player < 8; player++) {
        value = known_at(0,0,player);
        known_ptrs[player] = value;
      }
      for (tile_index = 0; tile_index < map.area; tile_index++) {
        *(i8 *)(tile_ptr + 4) = 0xff;
        for (player = 1; player < 8; player++) {
          *(i8 *)known_ptrs[player] = *(i8 *)(tile_ptr + 1);
          known_ptrs[player]++;
        }
        tile_ptr += 6;
      }
      for (city = 0; city < game.num_cities; city++) {
        if (cities[city].id != 0) {
          cities[city].known_to = 0xff;
          for (player = 0; player < 8; player++) {
            *(i8 *)&cities[city].revealed_size[player] = cities[city].size;
          }
          value = tile_at((int)cities[city].x,(int)cities[city].y);
          *(i8 *)(value + 4) = 0xff;
        }
      }
      scenario_flags = scenario_flags | 8;
      map_redraw_all_views(human_civ,1);
    }
    else if (choice == 8) {
      tile_ptr = tile_at(0,0);
      for (tile_index = 0; tile_index < map.area; tile_index++) {
        *(i8 *)(tile_ptr + 4) = 0;
        if (((*(byte *)(tile_ptr + 1) & 3) != 0) &&
           (owner = (int)(uint)*(byte *)(tile_ptr + 5) >> 4, owner < 8)) {
          (*(i8 *)((char *)&player + 0)) = (sbyte)owner;
          *(char *)(tile_ptr + 4) = (char)(1 << (sbyte)player);
        }
        tile_ptr += 6;
      }
      scenario_flags = scenario_flags & 0xfff7;
      map_redraw_all_views(human_civ,1);
    }
    else if (choice == 9) {
      value = dlg_game_text_input(ADDR(0x633970, ((u8 *)&g.d_00633970)),0x18,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)),(iptr)name_buf);
      if (value == 0) {
        crt_strcpy(&scenario_name,name_buf);
      }
    }
    else if (choice == 10) {
      scenario_flags = scenario_flags ^ 1;
    }
    else if (choice == 0xb) {
      cheat_edit_victory();
    }
    else {
      if (choice != 0xc) {
        return;
      }
      cheat_edit_scenario_rules();
    }
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef scenario_max_turns
#undef scenario_name
#undef scenario_start_year
#undef scenario_tech_paradigm
#undef scenario_year_increment
#undef player
#undef city
#undef name_buf
#undef tile_ptr
#undef known_ptrs
#undef tile
#undef number_input
#undef tile_index

/* 0055891d auto */
void __cdecl cheat_save_as_scenario(void)

{
  game_save_dialog(1);
  return;
}

/* 00559c20 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl setup_picwnd_global_init(void)

{
  setup_picwnd_static_init();
  setup_picwnd_reg_atexit();
  return;
}

/* 00559c3a auto */
void __cdecl setup_picwnd_static_init(void)

{
  setup_picwnd_ctor((ViewWindow *)&setup_picwnd);
  return;
}

/* 00559c54 auto */
void __cdecl setup_picwnd_reg_atexit(void)

{
  _atexit(setup_picwnd_static_dtor);
  return;
}

/* 00559c71 auto */
void __cdecl setup_picwnd_static_dtor(void)

{
  setup_picwnd_dtor((ViewWindow *)&setup_picwnd);
  return;
}

/* 00559c8b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl setup_picwnd_surface_global_init(void)

{
  setup_picwnd_surface_static_init();
  setup_picwnd_surface_reg_atexit();
  return;
}

/* 00559ca5 auto */
void __cdecl setup_picwnd_surface_static_init(void)

{
  surface_ctor((DibSurface *)&setup_picwnd_surface);
  return;
}

/* 00559cbf auto */
void __cdecl setup_picwnd_surface_reg_atexit(void)

{
  _atexit(setup_picwnd_surface_static_dtor);
  return;
}

/* 00559cdc auto */
void __cdecl setup_picwnd_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)&setup_picwnd_surface);
  return;
}

/* 00559cf6 auto */
#define surface (*(DibSurface *)(frame_ + FRAME_OFF(4)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(76)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1152)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(1156)))
#define seh_state (*(int *)(frame_ + FRAME_OFF(1160)))
void __cdecl setup_picwnd_load_image(i32 width,i32 height)

{
  i8 frame_[FRAME_OFF(1168)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  surface_ctor(&surface);
  seh_state = 0;
  palette_init(&palette);
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  win_flush_pending_msgs();
  surface_load_gif_resource(&surface,setup_picwnd_image_id + 900,10,0xc0,(iptr)&palette);
  win_flush_pending_msgs();
  surface_create((DibSurface *)&setup_picwnd_surface,width,height);
  gfx_copy_rect_same_pos((iptr)&surface,ADDR(0x6ab4b8, ((u8 *)&g.d_006ab4b8)),0,0,width,height);
  surface_release(&surface);
  seh_state = (uint)(*(i32 *)((char *)&seh_state + 1)) << 8;
  /* inlined unwind funclet 00559dbd */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00559dc9 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
  return;
}
#undef surface
#undef palette
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00559ded auto */
void __thiscall setup_picwnd_reset_fields(ViewWindow *this)

{
  this->max_rate_value = 100;
  this->rates_civ = this->max_rate_value;
  this->tax_rate_sel = 1;
  this->lux_rate_sel = 0;
  return;
}

/* 00559e3c auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
ViewWindow * __thiscall setup_picwnd_ctor(ViewWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  seh_state = 0;
  dll_handle_init((DllHandle *)&this->dialog_w);
  seh_state = CONCAT31((*(i32 *)((char *)&seh_state + 1)),1);
  this->vtable = (u32)&PTR_FUN_0061d6e0;
  setup_picwnd_reset_fields(this);
  return this;
}
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00559ed4 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CMiniFrameWnd::~CMiniFrameWnd(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall setup_picwnd_dtor(ViewWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6e0;
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  (*(i32 *)((char *)&seh_state + 1)) = 0;
  setup_picwnd_reset_fields(this);
  seh_state = (uint)(*(i32 *)((char *)&seh_state + 1)) << 8;
  /* inlined unwind funclet 00559f30 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x2f8)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00559f3f */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef seh_handler
#undef seh_scope
#undef seh_state

/* 00559f60 auto */
void __thiscall setup_picwnd_blit_image_rect(ScaledWindowView *this,int *rect)

{
  i32 height;
  i32 width;
  
  height = rect_height((iptr)rect);
  width = rect_width((iptr)rect);
  gfx_copy_rect_xywh(ADDR(0x6ab4b8, ((u8 *)&g.d_006ab4b8)),(iptr)this,*rect - this->client_x,rect[1] - this->client_y,
                     *rect,rect[1],width,height);
  return;
}

/* 00559fcf auto */
void __thiscall setup_picwnd_draw_image(ScaledWindowView *this,iptr rect)

{
  gfx_set_draw_target((iptr)this);
  text_set_surface((iptr)this);
  setup_picwnd_blit_image_rect(this,rect);
  return;
}

/* 0055a00b auto */
void __thiscall
setup_picwnd_client_rect
          (SetupPicWndRectView *this,iptr rect,int x,int y,iptr width,iptr height)

{
  rect_set_xywh(rect,this->client_origin_x + x,this->client_origin_y + y,width,height);
  return;
}

/* 0055a051 auto */
void __thiscall setup_picwnd_redraw(ViewWindow *this)

{
  frame_wnd_layout((FrameWindow *)this);
  setup_picwnd_load_image(this->rates_civ,this->max_rate_value);
  setup_picwnd_client_rect
            ((SetupPicWndRectView *)this,(iptr)&this->sci_rate_sel,0,0,this->rates_civ,this->max_rate_value);
  gfx_set_draw_target((iptr)this);
  frame_wnd_draw_caption((FrameWindow *)this);
  setup_picwnd_draw_image((ScaledWindowView *)this,(iptr)&this->sci_rate_sel);
  wnd_blit_surface((DibSurface *)this);
  return;
}

/* 0055a0e1 auto */
i32 __cdecl setup_picwnd_on_close(void)

{
  wnd_hide((WndBase *)&setup_picwnd_wnd);
  wnd_focus_and_raise((WndBase *)&main_frame_wnd);
  ui_flush_input();
  return 0;
}

/* 0055a10d auto */
void __cdecl
setup_picwnd_frame_rect(iptr rect,i32 x,i32 y,int width,int height)

{
  rect_set_xywh(rect,x,y,width + 0x10 + sys_dlgframe_w2,
                     height + 0x10 + sys_dlgframe_h2);
  return;
}

/* 0055a15e auto */
void __cdecl setup_picwnd_on_redraw(void)

{
  setup_picwnd_redraw((ViewWindow *)&setup_picwnd);
  return;
}

/* 0055a178 auto */
void __cdecl setup_picwnd_on_restore(void)

{
  setup_picwnd_redraw((ViewWindow *)&setup_picwnd);
  return;
}

/* 0055a192 auto */
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
int __cdecl setup_picwnd_position_coord(int position,int size)

{
  int client_size;
  
  switch(position) {
  case 0:
  case 5:
    position = 0;
    break;
  case 1:
    position = ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1;
    break;
  case 2:
    client_size = wnd_client_width((WndBase *)&main_frame_wnd);
    position = (client_size - (size + 0x10)) / 2;
    break;
  case 3:
    client_size = wnd_client_width((WndBase *)&main_frame_wnd);
    position = ((client_size - (size + 0x10)) -
              ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3)) - 1;
    break;
  case 4:
    client_size = wnd_client_width((WndBase *)&main_frame_wnd);
    position = client_size - (size + 0x10);
    if (position < 0) {
      position = 0;
    }
    break;
  case 6:
    position = ((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1;
    break;
  case 7:
    client_size = wnd_client_height((WndBase *)&main_frame_wnd);
    position = (client_size - (size + 0x10)) / 2;
    break;
  case 8:
    client_size = wnd_client_height((WndBase *)&main_frame_wnd);
    position = ((client_size - (size + 0x10)) -
              ((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)) - 1;
    break;
  case 9:
    client_size = wnd_client_height((WndBase *)&main_frame_wnd);
    position = client_size - (size + 0x10);
    if (position < 0) {
      position = 0;
    }
  }
  return position;
}
#undef screen_height

/* 0055a329 auto */
i32 __cdecl setup_picwnd_image_size(int is_height,i32 image_id)

{
  i32 size;
  
  switch(image_id) {
  case 1:
    if (is_height == 0) {
      size = 0x178;
    }
    else {
      size = 0xe3;
    }
    break;
  case 2:
  case 3:
  case 4:
  case 5:
    if (is_height == 0) {
      size = 0x247;
    }
    else {
      size = 0x101;
    }
    break;
  case 6:
  case 7:
  case 8:
  case 9:
    if (is_height == 0) {
      size = 0x248;
    }
    else {
      size = 0x102;
    }
    break;
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
    if (is_height == 0) {
      size = 0x196;
    }
    else {
      size = 0x102;
    }
    break;
  default:
    size = 100;
  }
  return size;
}

/* 0055a41d auto */
#define rect (*(i32 *)(frame_ + FRAME_OFF(4)))
#define rect_top2 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall
setup_picwnd_show(ViewWindow *this,i32 x_pos,i32 y_pos,u32 image_id)

{
  u32 size;
  i32 x;
  i32 y;
  int height;
  int width;
  i32 style;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->lux_rate_sel != 0) {
    this->tax_rate_sel = image_id;
    size = setup_picwnd_image_size(0,this->tax_rate_sel);
    this->rates_civ = size;
    size = setup_picwnd_image_size(1,this->tax_rate_sel);
    this->max_rate_value = size;
    x = setup_picwnd_position_coord(x_pos,this->rates_civ);
    y = setup_picwnd_position_coord(y_pos,this->max_rate_value);
    setup_picwnd_frame_rect((iptr)&rect,x,y,this->rates_civ,this->max_rate_value);
    style = 8;
    y = 8;
    x = 0;
    height = rect_height((iptr)&rect);
    height -= sys_dlgframe_h2;
    width = rect_width((iptr)&rect);
    frame_wnd_create
              ((FrameWindow *)this,0,2,rect,rect_top2,width - sys_dlgframe_w2,height,x,y,
               style);
    wnd_set_close_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x401005, setup_picwnd_on_close));
    wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x403544, setup_picwnd_on_redraw));
    wnd_set_restore_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x403b0c, setup_picwnd_on_restore));
    wnd_repaint((SurfaceWindow *)this);
    window_show((WindowObjectView *)this);
  }
  return;
}
#undef rect
#undef rect_top2

/* 0055a567 auto */
void __thiscall setup_picwnd_close(ViewWindow *this)

{
  if (this->lux_rate_sel != 0) {
    wnd_destroy_with_surface((DibSurface *)this);
    surface_release((DibSurface *)&setup_picwnd_surface);
    ui_flush_input();
  }
  return;
}

/* 0055a5e4 auto */
#define dll_path (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
void __thiscall setup_picwnd_load_dll(ViewWindow *this)

{
  int found;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  crt_strcpy(dll_path,s_civ2_intro_dll_00633a2c);
  found = file_resolve_path((iptr)dll_path);
  if (found != 0) {
    dll_handle_load((DllHandle *)&this->dialog_w,(iptr)dll_path);
    this->lux_rate_sel = 1;
  }
  return;
}
#undef dll_path

/* 0055a64a auto */
void __thiscall setup_picwnd_free_dll(ViewWindow *this)

{
  if (this->lux_rate_sel != 0) {
    dll_handle_free((DllHandle *)&this->dialog_w);
    this->lux_rate_sel = 0;
  }
  return;
}

/* 00568b00 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl status_window_global_init(void)

{
  status_window_static_init();
  status_window_reg_atexit();
  return;
}

/* 00568b1a auto */
void __cdecl status_window_static_init(void)

{
  frame_wnd_ctor((SurfaceWindow *)&status_window);
  return;
}

/* 00568b34 auto */
void __cdecl status_window_reg_atexit(void)

{
  _atexit(status_window_static_dtor);
  return;
}

/* 00568b51 auto */
void __cdecl status_window_static_dtor(void)

{
  frame_wnd_dtor((DibSurface *)&status_window);
  return;
}

/* 00568b6b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl status_info_font_global_init(void)

{
  status_info_font_static_init();
  status_info_font_reg_atexit();
  return;
}

/* 00568b85 auto */
void __cdecl status_info_font_static_init(void)

{
  font_init_empty((GameFont *)&status_info_font);
  return;
}

/* 00568b9f auto */
void __cdecl status_info_font_reg_atexit(void)

{
  _atexit(status_info_font_static_dtor);
  return;
}

/* 00568bbc auto */
void __cdecl status_info_font_static_dtor(void)

{
  font_destroy((GameFont *)&status_info_font);
  return;
}

/* 00568bd6 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl status_font_global_init(void)

{
  status_font_static_init();
  status_font_reg_atexit();
  return;
}

/* 00568bf0 auto */
void __cdecl status_font_static_init(void)

{
  font_init_empty((GameFont *)&status_font);
  return;
}

/* 00568c0a auto */
void __cdecl status_font_reg_atexit(void)

{
  _atexit(status_font_static_dtor);
  return;
}

/* 00568c27 auto */
void __cdecl status_font_static_dtor(void)

{
  font_destroy((GameFont *)&status_font);
  return;
}

/* 00568c41 auto */
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
void __cdecl status_wnd_on_minimize(void)

{
  status_wnd_hidden = 1;
  return;
}
#undef status_wnd_hidden

/* 00568c58 auto */
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
void __cdecl status_wnd_on_restore(void)

{
  city_window_bring_to_top((WindowObjectView *)&city_window);
  status_wnd_hidden = 0;
  status_wnd_repaint();
  return;
}
#undef status_wnd_hidden

/* 00568c7e auto */
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
i32 __cdecl status_wnd_on_close(void)

{
  status_wnd_hidden = 1;
  wnd_minimize((WndBase *)&status_window_wnd);
  return 0;
}
#undef status_wnd_hidden

/* 00568ca2 auto */
#define status_info_font_scale (*(uint *)((u8 *)&g.d_00633df4))
#define status_lower_panel_height (*(int *)((u8 *)&g.d_006abc5c))
#define status_panel_gap (*(i8 *)((u8 *)&g.d_006abf40))
#define status_panel_width (*(int *)((u8 *)&g.d_006abc58))
#define status_panel_x (*(i8 *)((u8 *)&g.d_006abc60))
#define status_text_bottom (*(i32 *)((u8 *)&g.d_006abc38))
#define status_upper_panel_height (*(int *)((u8 *)&g.d_006abf44))
#define lower_height (*(int *)(frame_ + FRAME_OFF(4)))
#define info_scale (*(uint *)(frame_ + FRAME_OFF(8)))
#define font_scale (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_calc_font_sizes(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  status_text_bottom = 0;
  font_scale = 2;
  info_scale = 2;
  status_panel_x = 0;
  status_panel_width = status_client_width;
  lower_height = status_client_height - 0x28;
  status_upper_panel_height = 0x28;
  if ((0xf4 < status_client_width) && (0x12e < lower_height)) {
    info_scale = 4;
    status_upper_panel_height = 0x50;
    lower_height = status_client_height - 0x50;
  }
  if (((info_scale == 2) && (0xb9 < status_client_width)) && (0xed < lower_height)) {
    info_scale = 3;
    status_upper_panel_height += (status_upper_panel_height >> 1);
    lower_height -= 0x14;
  }
  status_panel_gap = 8;
  if (lower_height < 0xb2) {
    if (lower_height < 0x10) {
      status_lower_panel_height = 0;
    }
    else {
      status_lower_panel_height = lower_height - 8;
    }
  }
  else {
    status_lower_panel_height = lower_height - 8;
  }
  if ((info_scale == 4) && (0x128 < status_lower_panel_height)) {
    font_scale = 4;
  }
  if (((2 < info_scale) && (font_scale == 2)) && (0xfe < status_lower_panel_height)) {
    font_scale = 3;
  }
  if (font_scale != status_font_scale) {
    status_font_scale = font_scale;
    font_set_styled((GameFont *)&status_font,0,font_scale * 0xb >> 1,1);
  }
  if (info_scale != status_info_font_scale) {
    status_info_font_scale = info_scale;
    font_set_styled((GameFont *)&status_info_font,0,(int)(info_scale * 0xb) >> 1,1);
  }
  return;
}
#undef status_info_font_scale
#undef status_lower_panel_height
#undef status_panel_gap
#undef status_panel_width
#undef status_panel_x
#undef status_text_bottom
#undef status_upper_panel_height
#undef lower_height
#undef info_scale
#undef font_scale

/* 00568e86 auto */
#define status_indicator_rect (*(i32 *)((u8 *)&g.d_006abf24))
#define status_lower_panel_height (*(int *)((u8 *)&g.d_006abc5c))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define rect (*(int *)(frame_ + FRAME_OFF(4)))
#define rect_top2 (*(int *)(frame_ + FRAME_OFF(8)))
#define rect_right2 (*(int *)(frame_ + FRAME_OFF(12)))
#define rect_bottom2 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_draw_civ_color(iptr civ)

{
  i32 color;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((status_wnd_hidden == '\0') && (status_lower_panel_height != 0)) {
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    rect_right2 = status_client_right;
    rect_bottom2 = status_client_bottom;
    rect = status_client_right - 8;
    rect_top2 = status_client_bottom - 6;
    color = civ_color_primary(civ);
    gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&rect,color);
    win_flush_pending_msgs();
    wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&rect);
    surface_reset_clip((DibSurface *)&status_window);
    win_flush_pending_msgs();
  }
  return;
}
#undef status_indicator_rect
#undef status_lower_panel_height
#undef status_wnd_hidden
#undef rect
#undef rect_top2
#undef rect_right2
#undef rect_bottom2

/* 00568f43 auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define status_end_turn_visible (*(char *)((u8 *)&g.d_00633dfc))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
void __cdecl status_draw_end_of_turn(int blit)

{
  int text_y;
  i32 height;
  i32 width;
  int text_x;
  int line_height;
  i32 src_x;
  i32 src_y;
  
  if ((((status_wnd_hidden == '\0') && (unit_blink_active != '\0')) && (status_end_turn_visible != '\0')) &&
     (((game.transient_flags & 1) != 0 && (text_y = rect_height(ADDR(0x6abc18, ((u8 *)&g.d_006abc18))), 0 < text_y)))) {
    text_set_surface(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
    src_y = 0;
    src_x = 0;
    height = rect_height(ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
    width = rect_width(ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
    gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_end_turn_rect,status_end_turn_rect_top,width,height,src_x,src_y);
    text_set_colors((-(uint)((moving_units_mode == 0) == (bool)status_end_turn_blink_phase) & 0xf) + 0x1a,10,1,0);
    text_set_font(ADDR(0x6abc50, ((u8 *)&g.d_006abc50)));
    text_x = font_text_width((GameFont *)&status_font,ADDR(0x633e10, ((u8 *)&g.d_00633e10)));
    text_x = status_end_turn_rect + text_x;
    line_height = font_cached_height((GameFont *)&status_font);
    text_y = status_end_turn_rect_top;
    text_clear();
    text_append_label(0x1b);
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y);
    text_clear();
    text_append_space();
    text_append_lparen();
    text_append_label(0x1c);
    text_append_rparen();
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y + line_height - 1);
    win_flush_pending_msgs();
    if (blit != 0) {
      wnd_blit_surface_rect((DibSurface *)&status_window,ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
      win_flush_pending_msgs();
    }
    surface_reset_clip((DibSurface *)&status_window);
  }
  return;
}
#undef moving_units_mode
#undef status_end_turn_visible
#undef status_wnd_hidden
#undef unit_blink_active

/* 0056911d auto */
i32 __cdecl status_draw_cursor_loc(iptr x,iptr y,i32 draw_x,iptr draw_y)

{
  iptr landmass;
  i32 result;
  
  text_clear();
  text_append_label(0xb);
  text_append_colon();
  text_append_lparen();
  text_append_int(x);
  text_append_comma();
  text_append_int(y);
  text_append_rparen();
  text_append_space();
  landmass = tile_landmass(x,y);
  text_append_int(landmass);
  result = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),draw_x,draw_y);
  return result;
}

/* 005691a1 auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl status_append_unit_orders(iptr unit)

{
  iptr orders;
  uint improvements2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  orders = (iptr)units[unit].orders;
  if ((orders == -1) || (0xf < orders)) {
    text_append_label(0x1a);
  }
  else if (orders == 5) {
    improvements2 = tile_improvements((int)units[unit].x,(int)units[unit].y);
    if ((improvements2 & 0x10) == 0) {
      text_append_string_id(order_names[5].name);
    }
    else {
      text_append_label(0xa0);
    }
  }
  else {
    text_append_string_id(order_names[orders].name);
    if (orders == 0xb) {
      text_append_space();
      city = city_at((int)units[unit].goto_x,(int)units[unit].goto_y);
      if ((((-1 < city) && (game.reveal_map == '\0')) &&
          ((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) == 0)) &&
         ((int)cities[city].owner != (uint)(byte)human_civ)) {
        city = -1;
      }
      if (city < 0) {
        text_append_lparen();
        text_append_int((int)units[unit].goto_x);
        text_append_comma();
        text_append_int((int)units[unit].goto_y);
        text_append_rparen();
      }
      else {
        text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
      }
    }
  }
  return;
}
#undef human_civ
#undef city

/* 00569363 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define status_info_font_scale (*(int *)((u8 *)&g.d_00633df4))
#define status_upper_rect (*(int *)((u8 *)&g.d_006abc28))
#define status_upper_rect_top (*(int *)((u8 *)&g.d_006abc2c))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define icon_offset (*(int *)(frame_ + FRAME_OFF(0)))
#define warming_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define flask_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define text_y2 (*(int *)(frame_ + FRAME_OFF(36)))
#define text_x2 (*(int *)(frame_ + FRAME_OFF(40)))
#define zoom2 (*(int *)(frame_ + FRAME_OFF(44)))
#define panel_width2 (*(int *)(frame_ + FRAME_OFF(48)))
#define icon_size (*(int *)(frame_ + FRAME_OFF(52)))
#define bar_width (*(int *)(frame_ + FRAME_OFF(56)))
#define icon_width (*(int *)(frame_ + FRAME_OFF(60)))
#define icon_y (*(int *)(frame_ + FRAME_OFF(64)))
#define icon_x (*(int *)(frame_ + FRAME_OFF(68)))
#define stage (*(int *)(frame_ + FRAME_OFF(72)))
#define line_x (*(int *)(frame_ + FRAME_OFF(76)))
#define line_height (*(int *)(frame_ + FRAME_OFF(80)))
void __cdecl status_draw_info(int full_redraw)

{
  short progress;
  i32 height;
  i32 width;
  int percent;
  uint rect_w;
  i32 src_x;
  i32 src_y;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (full_redraw != 0) {
    gfx_set_draw_target(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    src_y = 0;
    src_x = 0;
    height = rect_height(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    width = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_upper_rect,status_upper_rect_top,width,height,src_x,src_y);
  }
  text_set_surface(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
  text_set_font(ADDR(0x6abf98, ((u8 *)&g.d_006abf98)));
  panel_width2 = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  if (1 < game.peace_turns) {
    percent = int_clamp(game.peace_turns * 3,0,100);
    bar_width = (percent * panel_width2) / 100;
    if (bar_width != 0) {
      gfx_draw_hline(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),status_upper_rect,status_upper_rect + bar_width - 1,status_upper_rect_top,0x55);
      gfx_draw_hline(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),status_upper_rect,status_upper_rect + bar_width - 1,status_upper_rect_top + 1,0x55);
    }
  }
  line_x = font_text_width((GameFont *)&status_info_font,ADDR(0x633e14, ((u8 *)&g.d_00633e14)));
  line_x = status_upper_rect + line_x;
  line_height = font_cached_height((GameFont *)&status_info_font);
  line_height--;
  text_y2 = status_upper_rect_top;
  text_x2 = line_x;
  zoom2 = status_info_font_scale * 4 - 8;
  surface_set_clip((DibSurface *)&status_window,ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  text_set_colors(0x10,0x21,1,1);
  text_clear();
  text_append_population(human_civ,0xffffffff);
  text_append_space();
  text_append_label(0x1e);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x2,text_y2);
  text_x2 = line_x;
  text_y2 += line_height;
  text_clear();
  text_append_year((int)game.year);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x2,text_y2);
  text_x2 = line_x;
  text_y2 += line_height;
  text_clear();
  text_append_gold(civs[human_civ].gold);
  text_append_space();
  text_append_space();
  text_append_int((uint)civs[human_civ].tax_rate);
  crt_strcat(&text_buffer,&status_tax_sep_str);
  text_append_int(10 - ((uint)civs[human_civ].science_rate +
                          (uint)civs[human_civ].tax_rate));
  crt_strcat(&text_buffer,&status_lux_sep_str);
  text_append_int((uint)civs[human_civ].science_rate);
  text_x2 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x2,text_y2);
  icon_size = gfx_zoom_scale(0xe,zoom2);
  icon_width = icon_size;
  percent = rect_height(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  icon_y = ((percent >> 1) + status_upper_rect_top) - (icon_size >> 1);
  rect_w = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  if ((int)(rect_w & 0xfffffffe) < 200) {
    icon_offset = 100;
  }
  else {
    icon_offset = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    icon_offset = icon_offset >> 1;
  }
  icon_x = status_upper_rect + icon_offset;
  gfx_set_zoom_scale(zoom2);
  progress = civs[human_civ].research_progress;
  stage = civ_research_cost(human_civ);
  stage = ((int)progress << 2) / stage;
  stage = int_clamp(stage,0,3);
  sprite_draw
            ((Sprite *)(&research_flask_sprites + stage * 0x3c),(iptr)flask_rect,ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),icon_x,
             icon_y);
  icon_x += (icon_width * 3) / 2;
  if (game.warming_counter != '\0') {
    stage = int_clamp((int)game.warming_counter >> 2,0,3);
    sprite_draw
              ((Sprite *)(&global_warming_sprites + stage * 0x3c),(iptr)warming_rect,ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),icon_x,
               icon_y);
  }
  gfx_reset_zoom_scale();
  surface_reset_clip((DibSurface *)&status_window);
  if (full_redraw != 0) {
    win_flush_pending_msgs();
    wnd_blit_surface_rect((DibSurface *)&status_window,ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    win_flush_pending_msgs();
  }
  return;
}
#undef human_civ
#undef status_info_font_scale
#undef status_upper_rect
#undef status_upper_rect_top
#undef text_buffer
#undef icon_offset
#undef warming_rect
#undef flask_rect
#undef text_y2
#undef text_x2
#undef zoom2
#undef panel_width2
#undef icon_size
#undef bar_width
#undef icon_width
#undef icon_y
#undef icon_x
#undef stage
#undef line_x
#undef line_height

/* 00569801 auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define status_end_turn_visible (*(i8 *)((u8 *)&g.d_00633dfc))
#define status_lower_panel_height (*(int *)((u8 *)&g.d_006abc5c))
#define status_lower_rect (*(int *)((u8 *)&g.d_006abfa8))
#define status_lower_rect_bottom (*(int *)((u8 *)&g.d_006abfb4))
#define status_lower_rect_top (*(int *)((u8 *)&g.d_006abfac))
#define status_text_bottom (*(int *)((u8 *)&g.d_006abc38))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_y2 (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define shown_count (*(int *)(frame_ + FRAME_OFF(28)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define reserved_lines (*(int *)(frame_ + FRAME_OFF(36)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(48)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(68)))
void __cdecl status_draw_unit_panel(void)

{
  u8 range;
  u8 turns_used;
  bool is_foreign;
  byte terrain;
  int text_x;
  int line_height;
  i32 width;
  iptr info_y;
  iptr icon_width;
  int value;
  iptr str;
  byte *tile_ptr;
  iptr unit3;
  int zoom;
  int row_pos;
  uint move_mult;
  int info_x;
  int scaled;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  status_draw_info(0);
  if (status_lower_panel_height != 0) {
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    text_set_font(ADDR(0x6abc50, ((u8 *)&g.d_006abc50)));
    text_x = font_text_width((GameFont *)&status_font,ADDR(0x633e20, ((u8 *)&g.d_00633e20)));
    text_x = status_lower_rect + text_x;
    line_height = font_cached_height((GameFont *)&status_font);
    zoom = status_lower_rect_top;
    line_height--;
    text_clear();
    text_append_label((moving_units_mode == 0) + 9);
    text_set_colors(0x29,10,1,0);
    width = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),status_lower_rect,zoom,width);
    text_set_colors(0x10,0x21,1,1);
    text_y2 = zoom + line_height + (line_height >> 1);
    zoom = status_font_scale * 3;
    shown_count = 0;
    if (((moving_units_mode == 1) && (-1 < game.active_unit)) && (player_turn_active != '\0')) {
      shown_count = 1;
      unit2 = (iptr)game.active_unit;
      x2 = (iptr)units[unit2].x;
      y2 = (iptr)units[unit2].y;
      gfx_draw_unit(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),unit2,4,text_x,text_y2,zoom - 8,0);
      info_y = text_y2 - 2;
      icon_width = gfx_zoom_scale(0x40,zoom - 8);
      row_pos = text_x + icon_width + 2;
      value = gfx_zoom_scale(0x30,zoom - 8);
      text_y2 = text_y2 + value + 2;
      value = unit_max_moves(unit2);
      value -= (uint)units[unit2].moves_used;
      scaled = value % (int)(uint)cosmic.road_move_mult;
      move_mult = (uint)cosmic.road_move_mult;
      text_clear();
      text_append_label(0xc);
      text_append_colon();
      text_append_int(value / (int)move_mult);
      if (scaled != 0) {
        text_append_space();
        text_append_int(scaled);
        crt_strcat(&text_buffer,&status_moves_frac_sep_str);
        text_append_int((uint)cosmic.road_move_mult);
      }
      if ('\0' < (char)unit_types[units[unit2].type].range) {
        text_append_space();
        text_append_lparen();
        range = unit_types[units[unit2].type].range;
        turns_used = units[unit2].counter;
        value = unit_max_moves(unit2);
        text_append_int((int)(((int)(char)range - (int)(char)turns_used) * value -
                                (uint)units[unit2].moves_used) / (int)(uint)cosmic.road_move_mult
                          );
        text_append_rparen();
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),row_pos,info_y);
      text_clear();
      str = unit_home_city_name(unit2);
      text_append_str(str);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),row_pos,info_y + line_height);
      text_clear();
      str = civ_get_adjective((int)units[unit2].owner);
      text_append_str(str);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),row_pos,info_y + line_height + line_height);
      text_clear();
      if (((int)(short)units[unit2].flags & 0x8000U) != 0) {
        text_append_label(0x5c);
        text_append_space();
      }
      text_append_string_id(unit_types[units[unit2].type].name);
      if (unit_types[units[unit2].type].role == 7) {
        text_append_colon();
        if ((char)units[unit2].counter < '\0') {
          text_append_label(0x40);
        }
        else {
          text_append_string_id(commodity_names[(char)units[unit2].counter]);
        }
      }
      else if ((units[unit2].flags & 0x2000) != 0) {
        text_append_space();
        text_append_lparen();
        text_append_label(0xd);
        text_append_rparen();
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
    }
    else {
      x2 = (iptr)map_cursor_x;
      y2 = (iptr)map_cursor_y;
      unit2 = -1;
      status_draw_cursor_loc(x2,y2,text_x,text_y2);
    }
    text_y2 += line_height;
    value = map_in_bounds(x2,y2);
    if ((value == 0) ||
       ((game.reveal_map == '\0' &&
        (value = tile_visible_to(x2,y2,human_civ), value == 0)))) {
      text_clear();
      text_append_lparen();
      text_append_label(0xf5);
      text_append_rparen();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
      text_y2 += line_height;
    }
    else {
      terrain = tile_terrain(x2,y2);
      text_clear();
      text_append_lparen();
      text_append_string_id(terrain_types[terrain].name);
      tile_ptr = (byte *)tile_at(x2,y2);
      if ((*tile_ptr & 0x80) != 0) {
        text_append_comma();
        text_append_label(0x12);
      }
      text_append_rparen();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
      text_y2 += line_height;
      value = tile_resource(x2,y2);
      if (value != 0) {
        text_clear();
        text_append_lparen();
        text_append_string_id(terrain_types[value * 0xb + (uint)terrain].name);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
        text_y2 += line_height;
      }
      value = tile_has_hut(x2,y2);
      if (value != 0) {
        text_clear();
        text_append_lparen();
        text_append_label(0x1d);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
        text_y2 += line_height;
      }
      if ((game.reveal_map == '\0') && (human_civ != 0)) {
        tile_ptr = (byte *)known_at(x2,y2,human_civ);
        terrain = *tile_ptr;
      }
      else {
        value = tile_at(x2,y2);
        terrain = *(byte *)(value + 1);
      }
      if ((terrain & 0x1c) != 0) {
        text_clear();
        text_append_lparen();
        if ((terrain & 0x30) != 0) {
          if ((terrain & 0x20) == 0) {
            text_append_label(0x14);
          }
          else {
            text_append_label(0x13);
          }
          if ((terrain & 0xc) != 0) {
            text_append_comma();
          }
        }
        if ((terrain & 0xc) != 0) {
          if ((terrain & 8) == 0) {
            text_append_label(0x17);
          }
          else if ((terrain & 4) == 0) {
            text_append_label(0x16);
          }
          else {
            text_append_label(0x15);
          }
        }
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
        text_y2 += line_height;
      }
      if ((terrain & 0x40) != 0) {
        text_clear();
        text_append_lparen();
        text_append_label((-(uint)((terrain & 2) == 0) & 0xffffffcd) + 0x61);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
        text_y2 += line_height;
      }
      if ((terrain & 0x80) != 0) {
        text_clear();
        text_append_lparen();
        text_append_label(0x2f);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
        text_y2 += line_height;
      }
      text_y2 += (line_height >> 1);
      if ((game.transient_flags & 1) == 0) {
        reserved_lines = 1;
      }
      else {
        reserved_lines = 3;
      }
      unit3 = tile_first_unit(x2,y2);
      value = unit_stack_sum(unit3,2);
      for (unit = unit3; row_pos = status_lower_rect_bottom, -1 < unit;
          unit = unit_next_in_stack(unit)) {
        if (unit2 != unit) {
          is_foreign = false;
          if ((units[unit].owner != human_civ) &&
             (((is_foreign = true, unit != unit3 ||
               (((1 << ((byte)human_civ & 0x1f) & (uint)units[unit3].visibility) == 0 &&
                ((int)units[unit3].owner != (human_civ & 0xffU))))) &&
              (game.reveal_map == '\0')))) break;
          if (value - 1 == shown_count) {
            reserved_lines--;
          }
          scaled = gfx_zoom_scale(0x30,zoom - 8);
          if (row_pos - (scaled + line_height * reserved_lines + 1) <= text_y2) {
            text_clear();
            text_append_lparen();
            text_append_int(value - shown_count);
            text_append_space();
            text_append_label(0x18);
            text_append_space();
            text_append_label((-(uint)(value - shown_count == 1) & 99) + 0x19);
            text_append_rparen();
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x,text_y2);
            text_y2 += line_height;
            break;
          }
          shown_count++;
          gfx_draw_unit(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),unit,4,text_x,text_y2,zoom - 8,0);
          row_pos = text_y2 - 2;
          scaled = gfx_zoom_scale(0x40,zoom - 8);
          info_x = text_x + scaled + 2;
          scaled = gfx_zoom_scale(0x30,zoom - 8);
          text_y2 = text_y2 + scaled + 2;
          if (is_foreign) {
            text_clear();
            str = civ_get_adjective((int)units[unit].owner);
            text_append_str(str);
            if (game.reveal_map != '\0') {
              text_append_space();
              text_append_lparen();
              text_append_int(unit);
              if ((unit_types[units[unit].type].role == 5) &&
                 ((units[unit].flags & 0x200) != 0)) {
                text_append(ADDR(0x633e28, ((u8 *)&g.d_00633e28)));
              }
              text_append_rparen();
            }
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),info_x,row_pos);
            if ((units[unit].flags & 0x2000) != 0) {
              text_append_space();
              text_append_label(0xd);
            }
            text_clear();
            if (((int)(short)units[unit].flags & 0x8000U) != 0) {
              text_append_label(0x5c);
              text_append_space();
            }
            text_append_string_id(unit_types[units[unit].type].name);
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),info_x,row_pos + line_height);
            if (game.reveal_map != '\0') {
              text_clear();
              status_append_unit_orders(unit);
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),info_x,row_pos + line_height + line_height);
            }
          }
          else {
            text_clear();
            str = unit_home_city_name(unit);
            text_append_str(str);
            if (game.reveal_map != '\0') {
              text_append_space();
              text_append_lparen();
              text_append_int(unit);
              if ((unit_types[units[unit].type].role == 5) &&
                 ((units[unit].flags & 0x200) != 0)) {
                text_append(ADDR(0x633e2c, ((u8 *)&g.d_00633e2c)));
              }
              text_append_rparen();
            }
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),info_x,row_pos);
            text_clear();
            status_append_unit_orders(unit);
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),info_x,row_pos + line_height);
            text_clear();
            text_append_string_id(unit_types[units[unit].type].name);
            if (unit_types[units[unit].type].role == 7) {
              text_append_colon();
              if ((char)units[unit].counter < '\0') {
                text_append_label(0x40);
              }
              else {
                text_append_string_id(commodity_names[(char)units[unit].counter]);
              }
            }
            else if ((units[unit].flags & 0x2000) != 0) {
              text_append_space();
              text_append_lparen();
              text_append_label(0xd);
              text_append_rparen();
            }
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),info_x,row_pos + line_height + line_height);
          }
        }
      }
    }
    status_text_bottom = text_y2;
    if ((game.transient_flags & 1) == 0) {
      status_end_turn_visible = 0;
    }
    else {
      status_end_turn_rect = status_lower_rect;
      status_end_turn_rect_right = status_lower_rect_right;
      status_end_turn_rect_bottom = status_lower_rect_bottom;
      status_end_turn_rect_top = text_y2;
      while (zoom = rect_height(ADDR(0x6abc18, ((u8 *)&g.d_006abc18))), line_height * 3 < zoom) {
        status_end_turn_rect_top += line_height;
      }
      status_end_turn_visible = 1;
      status_draw_end_of_turn(0);
      status_text_bottom = status_end_turn_rect_bottom;
    }
    surface_reset_clip((DibSurface *)&status_window);
  }
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef player_turn_active
#undef status_end_turn_visible
#undef status_lower_panel_height
#undef status_lower_rect
#undef status_lower_rect_bottom
#undef status_lower_rect_top
#undef status_text_bottom
#undef text_buffer
#undef text_y2
#undef unit
#undef shown_count
#undef y2
#undef reserved_lines
#undef x2
#undef unit2

/* 0056a65e auto */
#define status_lower_panel_height (*(int *)((u8 *)&g.d_006abc5c))
#define status_lower_rect (*(i32 *)((u8 *)&g.d_006abfa8))
#define status_lower_rect_bottom (*(i32 *)((u8 *)&g.d_006abfb4))
#define status_lower_rect_top (*(i32 *)((u8 *)&g.d_006abfac))
#define status_text_bottom (*(int *)((u8 *)&g.d_006abc38))
#define status_upper_rect (*(i32 *)((u8 *)&g.d_006abc28))
#define status_upper_rect_top (*(i32 *)((u8 *)&g.d_006abc2c))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define rect_left2 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define rect_top2 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define rect_right2 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define rect_bottom2 (*(int *)(frame_ + FRAME_OFF(12)))
#define old_bottom (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_redraw(int blit)

{
  i32 height;
  i32 width;
  i32 src_x;
  i32 src_y;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (status_wnd_hidden == '\0') {
    old_bottom = status_text_bottom;
    gfx_set_draw_target(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    src_y = 0;
    src_x = 0;
    height = rect_height(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    width = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_upper_rect,status_upper_rect_top,width,height,src_x,src_y);
    if (status_lower_panel_height != 0) {
      src_y = 0;
      src_x = 0;
      height = rect_height(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
      width = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
      gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_lower_rect,status_lower_rect_top,width,height,src_x,src_y);
    }
    status_calc_font_sizes();
    status_draw_unit_panel();
    if (blit != 0) {
      wnd_blit_surface_rect((DibSurface *)&status_window,ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
      rect_left2 = status_lower_rect;
      rect_top2 = status_lower_rect_top;
      rect_right2 = status_lower_rect_right;
      rect_bottom2 = status_text_bottom;
      if (status_text_bottom <= old_bottom) {
        rect_bottom2 = old_bottom;
      }
      wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&rect_left2);
    }
  }
  return;
}
#undef status_lower_panel_height
#undef status_lower_rect
#undef status_lower_rect_bottom
#undef status_lower_rect_top
#undef status_text_bottom
#undef status_upper_rect
#undef status_upper_rect_top
#undef status_wnd_hidden
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2
#undef old_bottom

/* 0056a787 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define status_lower_panel_height (*(iptr *)((u8 *)&g.d_006abc5c))
#define status_lower_rect_top (*(i32 *)((u8 *)&g.d_006abfac))
#define status_panel_gap (*(byte *)((u8 *)&g.d_006abf40))
#define status_panel_width (*(iptr *)((u8 *)&g.d_006abc58))
#define status_panel_x (*(byte *)((u8 *)&g.d_006abc60))
#define status_upper_panel_height (*(iptr *)((u8 *)&g.d_006abf44))
#define status_upper_rect (*(i32 *)((u8 *)&g.d_006abc28))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define inner_rect (*(i32 *)(frame_ + FRAME_OFF(4)))
#define inner_top (*(int *)(frame_ + FRAME_OFF(8)))
#define inner_right (*(i32 *)(frame_ + FRAME_OFF(12)))
#define inner_bottom (*(int *)(frame_ + FRAME_OFF(16)))
#define bevel_rect (*(i32 *)(frame_ + FRAME_OFF(20)))
#define bevel_top (*(int *)(frame_ + FRAME_OFF(24)))
#define bevel_right (*(i32 *)(frame_ + FRAME_OFF(28)))
#define bevel_bottom (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl status_wnd_repaint(void)

{
  i32 height;
  i32 width;
  int inner_height;
  i32 src_x;
  i32 src_y;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((status_wnd_hidden == '\0') && (game_loop_active != '\0')) {
    frame_wnd_layout((FrameWindow *)&status_window);
    status_calc_font_sizes();
    gfx_set_draw_target(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    rect_set_xywh(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)),(uint)status_panel_x,0,status_panel_width,status_upper_panel_height);
    rect_set_xywh(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)),(uint)status_panel_x,0,status_panel_width,status_lower_panel_height);
    rect_offset(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)),status_client_x,status_client_y);
    rect_offset(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)),status_client_x,(uint)status_panel_gap + status_upper_rect_bottom);
    status_redraw(0);
    frame_wnd_draw_caption((FrameWindow *)&status_window);
    surface_reset_clip((DibSurface *)&status_window);
    if (status_lower_panel_height != 0) {
      rect_set((iptr)&bevel_rect,status_upper_rect,status_upper_rect_bottom,status_upper_rect_right,status_lower_rect_top);
      rect_inflate((iptr)&bevel_rect,frame_bevel_width,0);
      inner_rect = bevel_rect;
      inner_top = bevel_top;
      inner_right = bevel_right;
      inner_bottom = bevel_bottom;
      rect_deflate((iptr)&inner_rect,0,frame_bevel_width);
      src_y = 0;
      src_x = 0;
      height = rect_height((iptr)&inner_rect);
      width = rect_width((iptr)&inner_rect);
      gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x647f18, ((u8 *)&g.d_00647f18)),inner_rect,inner_top,width,height,src_x,src_y);
      bevel_bottom = bevel_top + frame_bevel_width;
      gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&bevel_rect,frame_highlight_color);
      inner_height = rect_height((iptr)&inner_rect);
      rect_offset((iptr)&bevel_rect,0,frame_bevel_width + inner_height);
      gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&bevel_rect,frame_shadow_color);
    }
    wnd_blit_surface((DibSurface *)&status_window);
  }
  return;
}
#undef game_loop_active
#undef status_lower_panel_height
#undef status_lower_rect_top
#undef status_panel_gap
#undef status_panel_width
#undef status_panel_x
#undef status_upper_panel_height
#undef status_upper_rect
#undef status_wnd_hidden
#undef inner_rect
#undef inner_top
#undef inner_right
#undef inner_bottom
#undef bevel_rect
#undef bevel_top
#undef bevel_right
#undef bevel_bottom

/* 0056a98b auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
void __cdecl status_wnd_on_click(void)

{
  if (city_turn_processing == 0) {
    if ((game.transient_flags & 1) == 0) {
      if (moving_units_mode == 1) {
        ui_redraw_all_maps(0);
      }
      else {
        ui_focus_active_unit(1);
      }
    }
    else {
      player_turn_active = 0;
    }
  }
  else {
    city_window_modal_notice();
  }
  return;
}
#undef city_turn_processing
#undef moving_units_mode
#undef player_turn_active

/* 0056a9f4 auto */
#define minimap_wnd_rect_top (*(int *)((u8 *)&g.d_00655328))
void __cdecl status_calc_wnd_rect(void)

{
  i32 left;
  int top;
  iptr width;
  int client_height;
  
  left = minimap_wnd_rect;
  top = rect_height(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  top = minimap_wnd_rect_top + top;
  width = rect_width(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  client_height = wnd_client_height((WndBase *)&main_frame_wnd);
  rect_set_xywh(ADDR(0x655334, ((u8 *)&g.d_00655334)),left,top,width,(client_height - top) - 1 + sys_dlgframe_h2);
  return;
}
#undef minimap_wnd_rect_top

/* 0056aa7f auto */
void __cdecl status_wnd_on_size(void)

{
  wnd_get_rect_in_parent((WndBase *)&status_window_wnd,ADDR(0x655334, ((u8 *)&g.d_00655334)));
  return;
}

/* 0056aaa5 auto */
void __cdecl status_wnd_on_move(void)

{
  wnd_get_rect_in_parent((WndBase *)&status_window_wnd,ADDR(0x655334, ((u8 *)&g.d_00655334)));
  return;
}

/* 0056aacb auto */
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __cdecl status_wnd_open(void)

{
  int height;
  int width;
  i32 title;
  i32 style;
  i32 x;
  i32 y;
  i32 flags;
  i32 arg_a;
  i32 arg_b;
  
  status_wnd_hidden = 0;
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    status_calc_wnd_rect();
  }
  arg_b = 0;
  arg_a = 0;
  flags = 6;
  height = rect_height(ADDR(0x655334, ((u8 *)&g.d_00655334)));
  height -= sys_dlgframe_h2;
  width = rect_width(ADDR(0x655334, ((u8 *)&g.d_00655334)));
  width -= sys_dlgframe_w2;
  style = 6;
  x = status_wnd_rect;
  y = status_wnd_rect_top;
  title = label_string(*(i32 *)(label_string_ids + 0x14));
  frame_wnd_create
            ((FrameWindow *)&status_window,title,style,x,y,width,height,flags,arg_a,arg_b);
  wnd_set_min_size((ModalMenuWindow *)&status_window_wnd,0x28,0x4c);
  wnd_set_minimize_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x402914, status_wnd_on_minimize));
  wnd_set_restore_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x403909, status_wnd_on_restore));
  wnd_set_close_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x402671, status_wnd_on_close));
  wnd_set_icon((WndBase *)&status_window_wnd,1);
  wnd_set_lbuttonup_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x401e06, status_wnd_on_click));
  wnd_set_rbuttonup_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x401e06, status_wnd_on_click));
  wnd_set_keydown_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x402cd4, map_window_key));
  wnd_set_char_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x401e56, map_window_ascii));
  wnd_set_redraw_callback((SurfaceWindow *)&status_window,ADDR(0x401c30, status_wnd_repaint));
  wnd_set_size_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x403ada, status_wnd_on_size));
  wnd_set_move_handler((WndEventHandlers *)&status_wnd_events,ADDR(0x402973, status_wnd_on_move));
  wnd_repaint((SurfaceWindow *)&status_window);
  if (game.multiplayer != 1) {
    window_show((WindowObjectView *)&status_window);
  }
  return;
}
#undef saved_layout_valid
#undef status_wnd_hidden
#undef turn_resume_civ

/* 0056ac46 auto */
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
void __cdecl status_wnd_close(void)

{
  status_wnd_hidden = 1;
  wnd_destroy_with_surface((DibSurface *)&status_window);
  return;
}
#undef status_wnd_hidden

/* 0056ac67 auto */
#define mp_turn_civ (*(byte *)((u8 *)&g.d_006ad578))
#define status_indicator_rect (*(int *)((u8 *)&g.d_006abf24))
#define status_lower_panel_height (*(int *)((u8 *)&g.d_006abc5c))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define bar_left (*(int *)(frame_ + FRAME_OFF(4)))
#define bar_top (*(int *)(frame_ + FRAME_OFF(8)))
#define bar_right (*(int *)(frame_ + FRAME_OFF(12)))
#define bar_bottom (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_draw_timer_bar(int percent,int color)

{
  int width;
  i32 height;
  i32 bar_width;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((status_timer_surface_init & 1) == 0) {
    status_timer_surface_init = status_timer_surface_init | 1;
    surface_ctor((DibSurface *)&status_timer_bg_surface);
    _atexit(status_timer_bg_surface_static_dtor);
  }
  bar_left = 0;
  bar_top = 0;
  bar_right = 0;
  bar_bottom = 0;
  if (((status_wnd_hidden == '\0') && (status_lower_panel_height != 0)) &&
     ((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) != 0)) {
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    bar_left = status_indicator_rect;
    bar_bottom = status_client_bottom;
    bar_right = status_client_right - 8;
    bar_top = status_client_bottom - 6;
    width = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    if (width != status_timer_last_width) {
      status_timer_last_width = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
      status_timer_last_color = -1;
      status_timer_last_percent = -1;
      surface_alloc_dib8((DibSurface *)&status_timer_bg_surface,(iptr)&bar_left);
      height = rect_height((iptr)&bar_left);
      bar_width = rect_width((iptr)&bar_left);
      gfx_copy_rect_xywh(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x6abf48, ((u8 *)&g.d_006abf48)),bar_left,bar_top,0,0,bar_width,height);
    }
    if (((status_timer_last_color != color) || (width = _memcmp(&bar_left,&status_timer_last_rect,0x10), width != 0))
       || (status_timer_last_percent != percent)) {
      status_timer_last_color = color;
      status_timer_last_rect = bar_left;
      status_timer_last_rect_top = bar_top;
      status_timer_last_rect_right = bar_right;
      status_timer_last_rect_bottom = bar_bottom;
      status_timer_last_percent = percent;
      height = rect_height((iptr)&bar_left);
      bar_width = rect_width((iptr)&bar_left);
      gfx_copy_rect_xywh(ADDR(0x6abf48, ((u8 *)&g.d_006abf48)),ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),0,0,bar_left,bar_top,bar_width,height);
      wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&bar_left);
      if (-1 < color) {
        width = rect_width((iptr)&bar_left);
        bar_right = bar_left + (percent * width) / 100;
        gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&bar_left,color);
        win_flush_pending_msgs();
        wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&bar_left);
      }
      surface_reset_clip((DibSurface *)&status_window);
      win_flush_pending_msgs();
    }
  }
  return;
}
#undef mp_turn_civ
#undef status_indicator_rect
#undef status_lower_panel_height
#undef status_wnd_hidden
#undef bar_left
#undef bar_top
#undef bar_right
#undef bar_bottom

/* 0056aeed auto */
void __cdecl status_timer_bg_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)&status_timer_bg_surface);
  return;
}

/* 0056b810: written by hand in src/game/regargs.c */

/* 005899f0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl main_frame_bg_surface_global_init(void)

{
  main_frame_bg_surface_init();
  main_frame_bg_surface_atexit();
  return;
}

/* 00589a0a auto */
void __cdecl main_frame_bg_surface_init(void)

{
  surface_ctor((DibSurface *)&main_frame_bg_surface);
  return;
}

/* 00589a24 auto */
void __cdecl main_frame_bg_surface_atexit(void)

{
  _atexit(main_frame_bg_surface_static_dtor);
  return;
}

/* 00589a41 auto */
void __cdecl main_frame_bg_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)&main_frame_bg_surface);
  return;
}

/* 00589a5b auto */
#define main_frame_created (*(i32 *)((u8 *)&g.d_00634718))
#define main_frame_nonclient_width (*(i32 *)((u8 *)&g.d_006acbb0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define main_frame_nonclient_height_i32 (*(i32 *)((u8 *)&g.d_006acbb4))
#define saved_rgb2 (*(i8 (*)[708])(frame_ + FRAME_OFF(0)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(708)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1784)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1788)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(1792)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl main_frame_create(void)

{
  int cd_ok;
  iptr wnd_info;
  i32 wave_rate;
  i32 wave_bits;
  i8 frame_[FRAME_OFF(1800)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  text_clear();
  text_append_label(2);
  WritePrivateProfileStringA
            (s_Civilization_Gold_00634734,s_Window_Name_00634728,&text_buffer,s_CIV_INI_00634720);
  wnd_create_with_cmd_proc((WndBase *)&main_frame_wnd,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x7c,0,0,600,400,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  cd_ok = file_require_cdrom(ADDR(0x634748, ((u8 *)&g.d_00634748)));
  if (cd_ok != 0) {
    wave_bits = 8;
    wave_rate = 0x10000;
    wnd_info = wnd_get_window((WndBase *)&main_frame_wnd);
    snd_wave_open(*(i32 *)(wnd_info + 4),wave_rate,wave_bits);
    menu_build_main();
    surface_load_gif_resource((DibSurface *)&main_frame_bg_surface,0x5a,10,0xc0,(iptr)&palette);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x6acb68, ((u8 *)&g.d_006acb68)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_set_icon((WndBase *)&main_frame_wnd,1);
    main_frame_nonclient_width = wnd_frame_width((WndBase *)&main_frame_wnd);
    main_frame_nonclient_height_i32 = wnd_nonclient_height((WndBase *)&main_frame_wnd);
    wnd_maximize((WndBase *)&main_frame_wnd);
    palette_get_rgb((GamePalette *)&game_palette,(iptr)saved_rgb2,10,0xec);
    intro_play_opening_video();
    palette_set_rgb((GamePalette *)&game_palette,10,0xec,(iptr)saved_rgb2);
    palette_commit_range((GamePalette *)&game_palette,10,0xec);
    wnd_set_close_handler((WndEventHandlers *)&main_frame_base_wnd,ADDR(0x402446, main_frame_on_close));
    wnd_set_keydown_handler((WndEventHandlers *)&main_frame_base_wnd,ADDR(0x402cd4, map_window_key));
    wnd_set_char_handler((WndEventHandlers *)&main_frame_base_wnd,ADDR(0x401e56, map_window_ascii));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_flush_paint();
    main_frame_created = 1;
    eh_state = 0xffffffff;
    /* inlined unwind funclet 00589c54 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  }
  else {
    eh_state = 0xffffffff;
    /* inlined unwind funclet 00589c54 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  }
  return (uint)(cd_ok != 0);
}
#undef main_frame_created
#undef main_frame_nonclient_width
#undef text_buffer
#undef main_frame_nonclient_height_i32
#undef saved_rgb2
#undef palette
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00589c79 auto */
#define main_frame_created (*(i32 *)((u8 *)&g.d_00634718))
void __cdecl main_frame_destroy(void)

{
  wnd_destroy_native((WndBase *)&main_frame_wnd);
  main_frame_created = 0;
  return;
}
#undef main_frame_created

/* 005ae580 auto */
#define event_dont_play_wonders (*(int *)((u8 *)&g.d_006a9110))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_time_limit_ms (*(i32 *)((u8 *)&g.d_00654b70))
#define prefs_pbem_menu_choice (*(short *)((u8 *)&g.d_00666542))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define i (*(int *)(frame_ + FRAME_OFF(0)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define map_mode (*(i32 *)(frame_ + FRAME_OFF(760)))
#define num_players (*(int *)(frame_ + FRAME_OFF(764)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl setup_pbem_game(void)

{
  int choice;
  i32 result;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  for (i = 0; i < 8; i++) {
    *(i16 *)(&civ_intro_shown + i * 2) = 0;
    (&civ_email_addresses)[i * 0x20] = 0;
  }
  mp_turn_time_limit_ms = 0;
  game.multiplayer = 2;
LAB_005ae610:
  setup_dialog_pos_state = 3;
  setup_show_side_picture(0xffffffff,0);
  dlg_load_game_section(&dialog2,ADDR(0x635dcc, ((u8 *)&g.d_00635dcc)),1);
  dialog_set_default_choice((DialogOptionList *)&dialog2,(int)prefs_pbem_menu_choice);
  crt_strcpy(&scenario_dir_path,&game_home_dir);
  choice = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
  result = setup_next_dialog_x(0);
  dialog_set_position((DialogCore *)&dialog2,result,choice);
  choice = dlg_show_modal(&dialog2,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((ViewWindow *)&setup_picwnd);
  if (choice < 0) {
    eh_state = 0xffffffff;
    /* inlined unwind funclet 005aebef */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    result = 1;
LAB_005aec05:
    return result;
  }
  prefs_pbem_menu_choice = (short)choice;
  if ((-1 < choice) && (choice < 3)) {
    __chdir(&game_home_dir);
    rules_load(1);
  }
  scenario_events_loaded = 0;
  switch(choice) {
  case 0:
    choice = setup_choose_map_size();
    if (choice != 0) goto LAB_005ae610;
    map_mode = 0;
    choice = _rand();
    mapgen_land_mass = choice % 3 - 1;
    mapgen_land_form = 0;
    choice = _rand();
    if (choice % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    choice = _rand();
    mapgen_temperature = choice % 3 - 1;
    choice = _rand();
    mapgen_climate = choice % 3 - 1;
    choice = _rand();
    mapgen_age = choice % 3 - 1;
    choice = setup_choose_game_options(map_mode,2);
    break;
  case 1:
    choice = map_load_dialog();
    if (choice != 0) goto LAB_005ae610;
    map_mode = 1;
    if (map.flat != 0) {
      map_mode = 2;
    }
    choice = _rand();
    mapgen_land_mass = choice % 3 - 1;
    mapgen_land_form = 0;
    choice = _rand();
    if (choice % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    choice = _rand();
    mapgen_temperature = choice % 3 - 1;
    choice = _rand();
    mapgen_climate = choice % 3 - 1;
    choice = _rand();
    mapgen_age = choice % 3 - 1;
    choice = setup_choose_game_options(map_mode,2);
    break;
  case 2:
    choice = setup_choose_map_size();
    if (choice != 0) goto LAB_005ae610;
    map_mode = 0;
    choice = setup_custom_world();
    if (choice != 0) goto LAB_005ae610;
    choice = setup_choose_game_options(map_mode,2);
    break;
  case 3:
    event_dont_play_wonders = 0;
    choice = scenario_start_dialog(2);
    if (choice == 0) {
      if (event_dont_play_wonders != 0) {
        game.game_options = game.game_options & 0xfffeffff;
      }
      game.multiplayer = 2;
      num_players = setup_choose_hotseat_players();
      if (num_players == 0) {
        crt_strcpy(&scenario_dir_path,&game_home_dir);
      }
      else {
        choice = scenario_pick_human_civs(num_players);
        if (choice == 0) {
          prefs_save_civ2dat();
          eh_state = 0xffffffff;
          /* inlined unwind funclet 005aebef */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
          result = 0;
          goto LAB_005aec05;
        }
        crt_strcpy(&scenario_dir_path,&game_home_dir);
      }
    }
    else {
      crt_strcpy(&scenario_dir_path,&game_home_dir);
    }
    goto LAB_005ae610;
  case 4:
    event_dont_play_wonders = 0;
    choice = game_load_dialog(0,2,1);
    if (choice == 0) {
      if (game.multiplayer != 2) goto code_r0x005aea27;
      prefs_save_civ2dat();
      eh_state = 0xffffffff;
      /* inlined unwind funclet 005aebef */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      result = 0;
      goto LAB_005aec05;
    }
    if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    goto LAB_005ae610;
  default:
    goto switchD_005aea9a_default;
  }
  if (choice == 0) {
switchD_005aea9a_default:
    game.civs_alive = '\0';
    game.human_players = '\0';
    num_players = setup_choose_hotseat_players();
    if (num_players != 0) {
      leaders_reset_custom_names();
      for (i = 0; i < num_players; i++) {
        while (choice = setup_choose_tribe(i,2,0), choice != 0) {
          i--;
          if (i < 0) goto switchD_005aea9a_default;
        }
      }
      setup_choose_opponents(num_players);
      prefs_save_civ2dat();
      rules_load_advances(1);
      rules_load_units(1);
      rules_load_improvements(1);
      snd_menu_end();
      map_generate(map_mode);
      game_init_new();
      if (setup_accelerated_start != 0) {
        game_accelerated_start(setup_accelerated_start - 1);
      }
      game.multiplayer = 2;
      if (turn_resume_civ != '\0') {
        game.player_civ = turn_resume_civ;
        human_civ = (iptr)turn_resume_civ;
      }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 005aebef */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      result = 0;
      goto LAB_005aec05;
    }
  }
  goto LAB_005ae610;
code_r0x005aea27:
  popup_game_with_sprite(ADDR(0x635dd4, ((u8 *)&g.d_00635dd4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  if (event_dont_play_wonders != 0) {
    game.game_options = game.game_options & 0xfffeffff;
  }
  goto LAB_005ae610;
}
#undef event_dont_play_wonders
#undef human_civ
#undef mp_turn_time_limit_ms
#undef prefs_pbem_menu_choice
#undef scenario_events_loaded
#undef screen_height
#undef turn_resume_civ
#undef i
#undef dialog2
#undef map_mode
#undef num_players
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 005d1f50 auto */
#define new_mgr (*(TimerManager * *)(frame_ + FRAME_OFF(0)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(8)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(16)))
i32 __cdecl game_timer_create(iptr callback,i32 interval_ms,i32 repeat_count)

{
  TimerManagerCtorView *this;
  i32 slot;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  if (game_timer_mgr == (TimerManager *)0x0) {
    this = operator_new(0x90);
    eh_state = 0;
    if (this == (TimerManagerCtorView *)0x0) {
      new_mgr = (TimerManager *)0x0;
    }
    else {
      new_mgr = (TimerManager *)timer_mgr_ctor(this);
    }
    game_timer_mgr = new_mgr;
  }
  eh_state = 0xffffffff;
  slot = timer_mgr_add(game_timer_mgr,callback,interval_ms,repeat_count);
  return slot;
}
#undef new_mgr
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 005d2004 auto */
void __cdecl game_timer_destroy(iptr slot)

{
  if (game_timer_mgr == (TimerManager *)0x0) {
    dbg_log(ADDR(0x6382d4, ((u8 *)&g.d_006382d4)));
  }
  else {
    game_timer_kill_slot(game_timer_mgr,slot);
  }
  return;
}

/* 005d2042 auto */
#define slot (*(iptr *)(frame_ + FRAME_OFF(0)))
iptr __thiscall
timer_mgr_add(TimerManager *this,u32 callback,i32 interval_ms,u32 repeat_count)

{
  int started;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  slot = 1;
  while ((slot < 0x11 && (this[slot + 1].field_0 != 0))) {
    slot++;
  }
  if (slot < 0x11) {
    started = timer_wnd_start_slot(this->timer_hwnd,interval_ms,slot);
    if (started == 0) {
      slot = 0;
    }
    else {
      this[slot + 1].field_0 = callback;
      this[slot + 0x12].field_0 = repeat_count;
    }
  }
  else {
    slot = 0;
  }
  return slot;
}
#undef slot

/* 005d20e6 auto */
void __thiscall game_timer_kill_slot(TimerManager *this,iptr slot)

{
  this[slot + 1].field_0 = 0;
  timer_wnd_kill_slot(this->timer_hwnd,slot);
  return;
}

/* 005d211e auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
TimerManagerCtorView * __thiscall timer_mgr_ctor(TimerManagerCtorView *this)

{
  u8 *entry;
  u32 hwnd;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 1; i < 0x11; i++) {
    entry = this->pad_4 + i * 4;
    entry[0] = '\0';
    entry[1] = '\0';
    entry[2] = '\0';
    entry[3] = '\0';
    entry = this->pad_4 + i * 4 + 0x44;
    entry[0] = '\0';
    entry[1] = '\0';
    entry[2] = '\0';
    entry[3] = '\0';
  }
  hwnd = timer_wnd_create((iptr)this);
  this->timer_wnd = hwnd;
  return this;
}
#undef i

/* 005d2182 auto */
#define slot (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall timer_mgr_dtor(TimerManager *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (slot = 0; slot < 0x10; slot++) {
    if (this[slot + 1].field_0 != 0) {
      game_timer_kill_slot(this,slot);
    }
  }
  timer_wnd_destroy(this->timer_hwnd);
  return;
}
#undef slot

/* 005d41e0 auto */
uint __cdecl timer_ticks_60hz(void)

{
  DWORD DVar1;
  
  DVar1 = GetTickCount();
  return (DVar1 * 6) / 100;
}

/* 005d4204 auto */
void __cdecl timer_busy_wait_ticks(int ticks)

{
  int start_ticks;
  int now_ticks;
  
  start_ticks = timer_ticks_60hz();
  while( true ) {
    now_ticks = timer_ticks_60hz();
    if (start_ticks + ticks <= now_ticks) break;
    win_flush_pending_msgs();
  }
  return;
}

/* 005d423c auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define timer_mm_available (*(i32 *)((u8 *)&g.d_006383bc))
#define timerdll_get_timer_id (*(FARPROC *)((u8 *)&g.d_006e47fc))
#define timerdll_reset_timer_notified (*(FARPROC *)((u8 *)&g.d_006e480c))
#define timerdll_set_timer_id (*(FARPROC *)((u8 *)&g.d_006e4810))
#define timerdll_timer_callback (*(FARPROC *)((u8 *)&g.d_006e4808))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(0)))
HWND __cdecl timer_wnd_create(iptr timer_mgr)

{
  MMRESULT uTimerID;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  hwnd2 = (HWND)0x0;
  timerdll_module = LoadLibraryA(s_timerdll_dll_006383c0);
  if (timerdll_module == (HMODULE)0x0) {
    hwnd2 = CreateWindowExA(0,s_MSMrTimerClass_006384a4,s_MrTimer_0063849c,0xcf0000,-0x80000000,
                              -0x80000000,-0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,app_hinstance,
                              (LPVOID)0x0);
    if (hwnd2 != (HWND)0x0) {
      SetWindowLongA(hwnd2,0,timer_mgr);
      timer_mm_available = 0;
    }
  }
  else {
    timerdll_timer_callback = GetProcAddress(timerdll_module,s_TimerCallBack_006383d0);
    timerdll_set_timer_id = GetProcAddress(timerdll_module,s_SetTimerID_006383e0);
    timerdll_get_timer_id = GetProcAddress(timerdll_module,s_GetTimerID_006383ec);
    timerdll_get_timer_index = GetProcAddress(timerdll_module,s_GetTimerIndex_006383f8);
    timerdll_reset_timer_notified = GetProcAddress(timerdll_module,s_ResetTimerNotified_00638408);
    if ((((timerdll_timer_callback == (FARPROC)0x0) || (timerdll_set_timer_id == (FARPROC)0x0)) ||
        (timerdll_get_timer_id == (FARPROC)0x0)) ||
       ((timerdll_get_timer_index == (FARPROC)0x0 || (timerdll_reset_timer_notified == (FARPROC)0x0)))) {
      err_report((ErrorContext *)&err_report_ctx,9,ADDR(0x638438, ((u8 *)&g.d_00638438)),ADDR(0x63841c, ((u8 *)&g.d_0063841c)),0x55);
      FreeLibrary(timerdll_module);
    }
    else {
      hwnd2 = CreateWindowExA(0,s_MSMrTimerClass_00638458,s_MrTimer_00638450,0xcf0000,-0x80000000,
                                -0x80000000,-0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,
                                app_hinstance,(LPVOID)0x0);
      if (hwnd2 == (HWND)0x0) {
        err_report((ErrorContext *)&err_report_ctx,10,ADDR(0x638484, ((u8 *)&g.d_00638484)),ADDR(0x638468, ((u8 *)&g.d_00638468)),0x71);
        FreeLibrary(timerdll_module);
      }
      else {
        timeBeginPeriod(5);
        SetWindowLongA(hwnd2,0,timer_mgr);
        uTimerID = timeSetEvent(100,5,timerdll_timer_callback,(DWORD_PTR)hwnd2,1);
        if (uTimerID == 0) {
          timer_mm_available = 0;
        }
        else {
          timeKillEvent(uTimerID);
        }
      }
    }
  }
  return hwnd2;
}
#undef app_hinstance
#undef timer_mm_available
#undef timerdll_get_timer_id
#undef timerdll_reset_timer_notified
#undef timerdll_set_timer_id
#undef timerdll_timer_callback
#undef hwnd2

/* 005d447c auto */
#define timerdll_timer_callback (*(i32 *)((u8 *)&g.d_006e4808))
void __cdecl timer_wnd_destroy(HWND hwnd)

{
  if (hwnd != (HWND)0x0) {
    timeEndPeriod(5);
    DestroyWindow(hwnd);
    timerdll_timer_callback = 0;
    FreeLibrary(timerdll_module);
  }
  return;
}
#undef timerdll_timer_callback

/* 005d44be auto */
#define timer_alt_kind_request (*(int *)((u8 *)&g.d_00637ef8))
#define timer_mm_available (*(int *)((u8 *)&g.d_006383bc))
#define timerdll_set_timer_id (*(code * *)((u8 *)&g.d_006e4810))
#define timerdll_timer_callback (*(LPTIMECALLBACK *)((u8 *)&g.d_006e4808))
i32 __cdecl timer_wnd_start_slot(HWND hwnd,UINT interval_ms,iptr slot)

{
  MMRESULT MVar1;
  i32 result;
  UINT_PTR UVar3;
  
  if (timer_mm_available == 0) {
    if (timer_alt_kind_request == 0) {
      UVar3 = SetTimer(hwnd,slot,interval_ms,(TIMERPROC)0x0);
      if (UVar3 == 0) {
        err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x638530, ((u8 *)&g.d_00638530)),ADDR(0x638514, ((u8 *)&g.d_00638514)),0xc3);
        result = 0;
      }
      else {
        result = 1;
      }
    }
    else {
      MVar1 = timeSetEvent(interval_ms,5,timerdll_timer_callback,(DWORD_PTR)hwnd,1);
      if (MVar1 == 0) {
        err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x638560, ((u8 *)&g.d_00638560)),ADDR(0x638544, ((u8 *)&g.d_00638544)),0xd7);
        result = 0;
      }
      else {
        (*timerdll_set_timer_id)(slot,MVar1);
        result = 1;
      }
    }
  }
  else if (timer_alt_kind_request == 0) {
    MVar1 = timeSetEvent(interval_ms,5,timerdll_timer_callback,(DWORD_PTR)hwnd,1);
    if (MVar1 == 0) {
      err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x6384d0, ((u8 *)&g.d_006384d0)),ADDR(0x6384b4, ((u8 *)&g.d_006384b4)),0xa8);
      result = 0;
    }
    else {
      (*timerdll_set_timer_id)(slot,MVar1);
      result = 1;
    }
  }
  else {
    UVar3 = SetTimer(hwnd,slot,interval_ms,(TIMERPROC)0x0);
    if (UVar3 == 0) {
      err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x638500, ((u8 *)&g.d_00638500)),ADDR(0x6384e4, ((u8 *)&g.d_006384e4)),0xb4);
      result = 0;
    }
    else {
      result = 1;
    }
  }
  return result;
}
#undef timer_alt_kind_request
#undef timer_mm_available
#undef timerdll_set_timer_id
#undef timerdll_timer_callback

/* 005d4664 auto */
#define timer_alt_kind_request (*(int *)((u8 *)&g.d_00637ef8))
#define timer_mm_available (*(int *)((u8 *)&g.d_006383bc))
#define timerdll_get_timer_id (*(code * *)((u8 *)&g.d_006e47fc))
#define timerdll_set_timer_id (*(code * *)((u8 *)&g.d_006e4810))
void __cdecl timer_wnd_kill_slot(HWND hwnd,iptr slot)

{
  UINT UVar1;
  
  if (timer_mm_available == 0) {
    if (timer_alt_kind_request == 0) {
      KillTimer(hwnd,slot);
    }
    else {
      UVar1 = (*timerdll_get_timer_id)(slot);
      timeKillEvent(UVar1);
      (*timerdll_set_timer_id)(slot,0);
    }
  }
  else if (timer_alt_kind_request == 0) {
    UVar1 = (*timerdll_get_timer_id)(slot);
    timeKillEvent(UVar1);
    (*timerdll_set_timer_id)(slot,0);
  }
  else {
    KillTimer(hwnd,slot);
  }
  return;
}
#undef timer_alt_kind_request
#undef timer_mm_available
#undef timerdll_get_timer_id
#undef timerdll_set_timer_id

/* 005d4700 auto */
#define timerdll_reset_timer_notified (*(code * *)((u8 *)&g.d_006e480c))
LRESULT __stdcall timer_wnd_proc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)

{
  TimerManager *this;
  LRESULT LVar1;
  
  this = (TimerManager *)GetWindowLongA(hwnd,0);
  if (this == (TimerManager *)0x0) {
    LVar1 = DefWindowProcA(hwnd,msg,wparam,lparam);
  }
  else {
    if (msg == 0x113) {
      game_timer_fire_slot(this,wparam);
    }
    else {
      if (msg != 0x52c) {
        LVar1 = DefWindowProcA(hwnd,msg,wparam,lparam);
        return LVar1;
      }
      game_timer_fire_slot(this,wparam);
      (*timerdll_reset_timer_notified)(wparam);
    }
    LVar1 = 0;
  }
  return LVar1;
}
#undef timerdll_reset_timer_notified

/* 005d47d0 auto */
void __thiscall game_timer_fire_slot(TimerManager *this,iptr slot)

{
  if ((this[slot + 1].field_0 != 0) && (this[slot + 0x12].field_0 != 0)) {
    if (0 < (int)this[slot + 0x12].field_0) {
      this[slot + 0x12].field_0--;
    }
    (*(code *)this[slot + 1].field_0)(slot,this[slot + 0x12].field_0);
    if (this[slot + 0x12].field_0 == 0) {
      game_timer_kill_slot(this,slot);
    }
  }
  return;
}

/* 005dbb20 auto */
#define app_hinstance (*(i32 *)((u8 *)&g.d_006e4ff0))
#define app_prev_instance (*(i32 *)((u8 *)&g.d_006e4fec))
i32 __cdecl app_startup(i32 hinstance,i32 prev_instance)

{
  app_hinstance = hinstance;
  app_prev_instance = prev_instance;
  app_init_graphics();
  app_init_system();
  return 1;
}
#undef app_hinstance
#undef app_prev_instance

/* 005dbb4f auto */
i32 __cdecl app_shutdown(void)

{
  app_shutdown_system();
  dbg_log(ADDR(0x6387f4, ((u8 *)&g.d_006387f4)));
  if (game_timer_mgr != (TimerManager *)0x0) {
    if (game_timer_mgr != (TimerManager *)0x0) {
      timer_mgr_scalar_dtor(game_timer_mgr,1);
    }
  }
  GdiFlush();
  return 1;
}

/* 005dbbb3 auto */
void __cdecl app_init_graphics(void)

{
  font_set((GameFont *)&default_draw_font_obj,2,0xe);
  gfx_scale_init();
  return;
}

/* 005dbbd6 auto */
#define app_prev_instance (*(int *)((u8 *)&g.d_006e4fec))
void __cdecl app_init_system(void)

{
  time_t now;
  
  if (app_prev_instance == 0) {
    app_register_wnd_classes();
  }
  snd_system_init();
  app_init_hook_nop();
  now = _time((time_t *)0x0);
  crt_srand((int)now);
  Ordinal_17();
  return;
}
#undef app_prev_instance

/* 005dbc1b auto */
void __cdecl app_shutdown_system(void)

{
  wnd_stack_check_leaks_nop();
  app_shutdown_hook_nop();
  snd_system_shutdown();
  return;
}

/* 005dbc3a auto */
void __cdecl app_init_hook_nop(void)

{
  return;
}

/* 005dbc4a auto */
void __cdecl app_shutdown_hook_nop(void)

{
  return;
}

/* 005dbc5a auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define wnd_class (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
void __cdecl app_register_wnd_classes(void)

{
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_class.style = 0x28;
  wnd_class.lpfnWndProc = wnd_base_wndproc;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 0x14;
  wnd_class.hInstance = app_hinstance;
  wnd_class.hIcon = (HICON)0x0;
  wnd_class.hCursor = (HCURSOR)0x0;
  wnd_class.hbrBackground = (HBRUSH)0x0;
  wnd_class.lpszMenuName = (LPCSTR)0x0;
  wnd_class.lpszClassName = s_MSWindowClass_00638810;
  RegisterClassA(&wnd_class);
  wnd_class.style = 0x28;
  wnd_class.lpfnWndProc = moviewnd_wndproc;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 0x14;
  wnd_class.hInstance = app_hinstance;
  wnd_class.hIcon = (HICON)0x0;
  wnd_class.hCursor = (HCURSOR)0x0;
  wnd_class.hbrBackground = (HBRUSH)0x0;
  wnd_class.lpszMenuName = (LPCSTR)0x0;
  wnd_class.lpszClassName = s_MSMovieClass_00638820;
  RegisterClassA(&wnd_class);
  wnd_class.style = 0x88;
  wnd_class.lpfnWndProc = ctrl_default_wndproc;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 0x10;
  wnd_class.hInstance = app_hinstance;
  wnd_class.hIcon = (HICON)0x0;
  wnd_class.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  wnd_class.hbrBackground = (HBRUSH)0x0;
  wnd_class.lpszMenuName = (LPCSTR)0x0;
  wnd_class.lpszClassName = s_MSControlClass_00638830;
  RegisterClassA(&wnd_class);
  wnd_class.style = 0;
  wnd_class.lpfnWndProc = timer_wnd_proc;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 4;
  wnd_class.hInstance = app_hinstance;
  wnd_class.hIcon = (HICON)0x0;
  wnd_class.hCursor = (HCURSOR)0x0;
  wnd_class.hbrBackground = (HBRUSH)0x0;
  wnd_class.lpszMenuName = (LPCSTR)0x0;
  wnd_class.lpszClassName = s_MSMrTimerClass_00638840;
  RegisterClassA(&wnd_class);
  return;
}
#undef app_hinstance
#undef wnd_class

/* 005dbe88: written by hand in src/game/retvals.c */

/* 005dcac0 auto */
TimerManager * __thiscall timer_mgr_scalar_dtor(TimerManager *this,uint flags)

{
  timer_mgr_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
