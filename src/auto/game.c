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
#define local_744 (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define local_310 (*(int *)(frame_ + FRAME_OFF(1080)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(1084)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(1840)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1844)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1848)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1852)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1856)))
i32 __cdecl setup_hotseat_game(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(1864)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  palette_init(&local_744);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  for (local_310 = 0; local_310 < 8; local_310++) {
    *(i16 *)(&civ_intro_shown + local_310 * 2) = 0;
  }
  mp_turn_time_limit_ms = 0;
  game.multiplayer = 1;
LAB_004191ff:
  surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_744);
  wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
  wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
  wnd_flush_paint();
  setup_dialog_pos_state = 3;
  setup_show_side_picture(0xffffffff,0);
  dlg_load_game_section(&local_30c,ADDR(0x6252a4, ((u8 *)&g.d_006252a4)),1);
  dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_hotseat_menu_choice);
  FUN_005f22d0(&scenario_dir_path,&game_home_dir);
  iVar1 = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
  uVar2 = setup_next_dialog_x(0);
  dialog_set_position((C_0040bc40_28 *)&local_30c,uVar2,iVar1);
  iVar1 = dlg_show_modal(&local_30c,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  if (iVar1 < 0) {
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00419940 */ { palette_destroy((GamePalette *)((iptr)&local_744)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0041994c */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    uVar2 = 1;
LAB_00419962:
    return uVar2;
  }
  prefs_hotseat_menu_choice = (short)iVar1;
  if ((-1 < iVar1) && (iVar1 < 3)) {
    __chdir(&game_home_dir);
    rules_load(1);
  }
  scenario_events_loaded = 0;
  switch(iVar1) {
  case 0:
    iVar1 = setup_choose_map_size();
    if (iVar1 != 0) goto LAB_004191ff;
    local_18 = 0;
    iVar1 = _rand();
    mapgen_land_mass = iVar1 % 3 - 1;
    mapgen_land_form = 0;
    iVar1 = _rand();
    if (iVar1 % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    iVar1 = _rand();
    mapgen_temperature = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_climate = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_age = iVar1 % 3 - 1;
    iVar1 = setup_choose_game_options(local_18,1);
    break;
  case 1:
    iVar1 = map_load_dialog();
    if (iVar1 != 0) goto LAB_004191ff;
    local_18 = 1;
    if (map.flat != 0) {
      local_18 = 2;
    }
    iVar1 = _rand();
    mapgen_land_mass = iVar1 % 3 - 1;
    mapgen_land_form = 0;
    iVar1 = _rand();
    if (iVar1 % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    iVar1 = _rand();
    mapgen_temperature = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_climate = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_age = iVar1 % 3 - 1;
    iVar1 = setup_choose_game_options(local_18,1);
    break;
  case 2:
    iVar1 = setup_choose_map_size();
    if (iVar1 != 0) goto LAB_004191ff;
    local_18 = 0;
    iVar1 = setup_custom_world();
    if (iVar1 != 0) goto LAB_004191ff;
    iVar1 = setup_choose_game_options(local_18,1);
    break;
  case 3:
    event_dont_play_wonders = 0;
    iVar1 = scenario_start_dialog(1);
    if (iVar1 == 0) {
      if (event_dont_play_wonders != 0) {
        game.game_options = game.game_options & 0xfffeffff;
      }
      game.multiplayer = 1;
      local_14 = setup_choose_hotseat_players();
      if (local_14 == 0) {
        FUN_005f22d0(&scenario_dir_path,&game_home_dir);
      }
      else {
        iVar1 = scenario_pick_human_civs(local_14);
        if (iVar1 == 0) {
          text_clear();
          text_append_label(0x363);
          menu_add_item((GameMenu *)&main_menu,1,0x1f2,ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
          prefs_save_civ2dat();
          surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_744);
          wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
          wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
          wnd_flush_paint();
          local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
          /* inlined unwind funclet FUN_00419940 */ { palette_destroy((GamePalette *)((iptr)&local_744)); }
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0041994c */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
          uVar2 = 0;
          goto LAB_00419962;
        }
        FUN_005f22d0(&scenario_dir_path,&game_home_dir);
      }
    }
    else {
      FUN_005f22d0(&scenario_dir_path,&game_home_dir);
    }
    goto LAB_004191ff;
  case 4:
    event_dont_play_wonders = 0;
    iVar1 = game_load_dialog(0,1,1);
    if (iVar1 == 0) {
      if (game.multiplayer != 1) goto code_r0x004196cc;
      text_clear();
      text_append_label(0x363);
      menu_add_item((GameMenu *)&main_menu,1,0x1f2,ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
      prefs_save_civ2dat();
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_744);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      wnd_flush_paint();
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_00419940 */ { palette_destroy((GamePalette *)((iptr)&local_744)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0041994c */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar2 = 0;
      goto LAB_00419962;
    }
    if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    goto LAB_004191ff;
  default:
    goto switchD_004197af_default;
  }
  if (iVar1 == 0) {
switchD_004197af_default:
    net_claimed_civs_mask = 0;
LAB_004197d3:
    game.civs_alive = '\0';
    game.human_players = '\0';
    local_14 = setup_choose_hotseat_players();
    if (local_14 != 0) {
      leaders_reset_custom_names();
      for (local_310 = 0; local_310 < local_14; local_310++) {
        while (iVar1 = setup_choose_tribe(local_310,1,0), iVar1 != 0) {
          local_310--;
          if (local_310 < 0) goto LAB_004197d3;
        }
      }
      setup_choose_opponents(local_14);
      prefs_save_civ2dat();
      rules_load_advances(1);
      rules_load_units(1);
      rules_load_improvements(1);
      snd_menu_end();
      map_generate(local_18);
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
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_00419940 */ { palette_destroy((GamePalette *)((iptr)&local_744)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0041994c */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar2 = 0;
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
#undef local_744
#undef local_310
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
i32 __cdecl app_startup_init(void)

{
  i32 uVar1;
  int iVar2;
  UINT UVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  FUN_005f22d0(&game_txt_path,&startup_game_txt_name_str);
  FUN_005f22d0(&rules_txt_path,s_RULES_006253f0);
  __getcwd(&game_home_dir,0x104);
  FUN_005f22d0(&scenario_dir_path,&game_home_dir);
  for (local_c = 0; local_c < 8; local_c++) {
    *(i16 *)(&map_view_open_flags + local_c * 0x3f0) = 0;
    (&main_view_timer_shown)[local_c * 0xfc] = 0;
  }
  timeBeginPeriod(4);
  uVar1 = timer_ticks();
  FUN_005f2260(uVar1);
  uVar1 = timer_ticks();
  rng_set_seed(uVar1);
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
  FUN_005f22d0(&lang_file_ext,&startup_lang_default_ext_str);
  switch(registry_language_id) {
  case 1:
    FUN_005f22d0(&lang_file_ext,&startup_lang_english_ext_str);
    break;
  case 2:
    FUN_005f22d0(&lang_file_ext,&startup_lang_french_ext_str);
    break;
  case 3:
    FUN_005f22d0(&lang_file_ext,&startup_lang_german_ext_str);
    break;
  case 4:
    FUN_005f22d0(&lang_file_ext,&startup_lang_italian_ext_str);
    break;
  case 5:
    FUN_005f22d0(&lang_file_ext,&startup_lang_spanish_ext_str);
  }
  text_section_index_build(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),0x4000);
  iVar2 = text_open_section((iptr)PTR_s_LABELS_00627674,ADDR(0x625410, ((u8 *)&g.d_00625410)));
  if (iVar2 == 0) {
    text_read_line(1);
    iVar2 = text_next_int();
    if (strpool_capacity < iVar2) {
      strpool_capacity = iVar2;
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
    iVar2 = popup_game(ADDR(0x625458, ((u8 *)&g.d_00625458)));
    if (iVar2 == 0) {
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
  iVar2 = main_frame_create();
  if (iVar2 == 0) {
    uVar1 = 1;
  }
  else {
    iVar2 = wnd_client_width((WndBase *)&main_frame_wnd);
    if (1000 < main_frame_nonclient_width + iVar2) {
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
    uVar1 = 0;
  }
  return uVar1;
}
#undef autoplay_active
#undef main_frame_nonclient_width
#undef main_view_timer_shown
#undef prefs_game_options
#undef saved_resume_new_game
#undef saved_turn_civ
#undef local_c

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
#define local_30c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl setup_choose_map_size(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_30c = 1;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  game.game_flags = 0;
  do {
    setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,2);
    dlg_load_game_section(&local_308,ADDR(0x62553c, ((u8 *)&g.d_0062553c)),1);
    dialog_set_default_choice((DialogOptionList *)&local_308,(int)prefs_map_size);
    dialog_set_position
              ((C_0040bc40_28 *)&local_308,0xfffffc19,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    iVar1 = dlg_show_modal(&local_308,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    if (iVar1 < 0) {
LAB_0041d739:
      if (5999 < (int)map.height * (int)map.width) {
        game.game_flags = game.game_flags | 4;
      }
      if ((int)map.height * (int)map.width < 3000) {
        game.game_flags = game.game_flags | 8;
      }
      map.width = map.width * 2;
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0041d7c5 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      return local_30c;
    }
    if (local_308.field_dc == 0) {
      prefs_map_size = (short)iVar1;
      if (iVar1 == 0) {
        map.width = 0x28;
        map.height = 0x32;
      }
      else if (iVar1 == 2) {
        map.width = 0x4b;
        map.height = 0x78;
      }
      else {
        map.width = 0x32;
        map.height = 0x50;
      }
      local_30c = 0;
      goto LAB_0041d739;
    }
    while( true ) {
      text_set_string_arg_b(1,ADDR(0x625548, ((u8 *)&g.d_00625548)));
      setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,2);
      local_14 = dialog_load_text_section(&local_308,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x625550, ((u8 *)&g.d_00625550)),5,ADDR(0x62554c, ((u8 *)&g.d_0062554c)),0,0,0,1)
      ;
      if (local_14 != 0) {
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        goto LAB_0041d739;
      }
      dialog_set_position
                ((C_0040bc40_28 *)&local_308,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar1 = dlg_show_modal(&local_308,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      if (iVar1 < 0) break;
      iVar1 = _atoi(&text_string_args);
      map.width = (i16)iVar1;
      iVar1 = _atoi(&text_string_arg1);
      map.height = (i16)iVar1;
      if ((((0x13 < map.width) && (map.width < 0xfb)) && (0x13 < map.height)) &&
         (((map.height < 0xfb && ((int)map.height * (int)map.width < 0x2711)) &&
          (999 < (int)map.height * (int)map.width)))) {
        local_30c = 0;
        goto LAB_0041d739;
      }
    }
  } while( true );
}
#undef prefs_map_size
#undef screen_height
#undef local_30c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0041d7ea auto */
#define prefs_world_params (*(short *)((u8 *)&g.d_0064bc2a))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define local_308 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
int __cdecl setup_custom_world(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_308 = 1;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,2);
  dlg_load_game_section(&local_304,ADDR(0x62555c, ((u8 *)&g.d_0062555c)),1);
  dialog_set_default_choice((DialogOptionList *)&local_304,prefs_world_params + 1);
  dialog_set_position
            ((C_0040bc40_28 *)&local_304,0xfffffc19,
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  iVar1 = dlg_show_modal(&local_304,0);
  mapgen_land_mass = iVar1 - 1;
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  if (-2 < mapgen_land_mass) {
    if (local_304.field_dc == 0) {
      prefs_world_params = (short)mapgen_land_mass;
    }
    else {
      iVar1 = _rand();
      mapgen_land_mass = iVar1 % 3 - 1;
    }
    setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,0xc);
    dlg_load_game_section(&local_304,ADDR(0x625568, ((u8 *)&g.d_00625568)),1);
    dialog_set_default_choice((DialogOptionList *)&local_304,prefs_world_land_form + 1);
    dialog_set_position
              ((C_0040bc40_28 *)&local_304,0xfffffc19,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    iVar1 = dlg_show_modal(&local_304,0);
    mapgen_land_form = iVar1 - 1;
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    if (-2 < mapgen_land_form) {
      if (local_304.field_dc == 0) {
        prefs_world_land_form = (short)mapgen_land_form;
      }
      else {
        mapgen_land_form = 0;
        iVar1 = _rand();
        if (iVar1 % 3 == 0) {
          mapgen_land_form = mapgen_land_mass;
        }
      }
      setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,0xb);
      dlg_load_game_section(&local_304,ADDR(0x625574, ((u8 *)&g.d_00625574)),1);
      dialog_set_default_choice((DialogOptionList *)&local_304,prefs_world_climate + 1);
      dialog_set_position
                ((C_0040bc40_28 *)&local_304,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar1 = dlg_show_modal(&local_304,0);
      mapgen_climate = iVar1 - 1;
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      if (-2 < mapgen_climate) {
        if (local_304.field_dc == 0) {
          prefs_world_climate = (short)mapgen_climate;
        }
        else {
          iVar1 = _rand();
          mapgen_climate = iVar1 % 3 - 1;
        }
        setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,0xd);
        dlg_load_game_section(&local_304,ADDR(0x625584, ((u8 *)&g.d_00625584)),1);
        dialog_set_default_choice((DialogOptionList *)&local_304,prefs_world_temperature + 1);
        dialog_set_position
                  ((C_0040bc40_28 *)&local_304,0xfffffc19,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        iVar1 = dlg_show_modal(&local_304,0);
        mapgen_temperature = iVar1 - 1;
        snd_play_effect(0x6a,0,0,0);
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        if (-2 < mapgen_temperature) {
          if (local_304.field_dc == 0) {
            prefs_world_temperature = (short)mapgen_temperature;
          }
          else {
            iVar1 = _rand();
            mapgen_temperature = iVar1 % 3 - 1;
          }
          setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,10);
          dlg_load_game_section(&local_304,ADDR(0x625590, ((u8 *)&g.d_00625590)),1);
          dialog_set_default_choice((DialogOptionList *)&local_304,prefs_world_age + 1);
          dialog_set_position
                    ((C_0040bc40_28 *)&local_304,0xfffffc19,
                     -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) +
                      1));
          iVar1 = dlg_show_modal(&local_304,0);
          mapgen_age = iVar1 - 1;
          snd_play_effect(0x6a,0,0,0);
          setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
          if (-2 < mapgen_age) {
            if (local_304.field_dc == 0) {
              prefs_world_age = (short)mapgen_age;
            }
            else {
              iVar1 = _rand();
              mapgen_age = iVar1 % 3 - 1;
            }
            local_308 = 0;
          }
        }
      }
    }
  }
  if (local_308 == 0) {
    prefs_save_civ2dat();
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0041dc9e */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  return local_308;
}
#undef prefs_world_params
#undef screen_height
#undef local_308
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0041dcc3 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl setup_clear_start_positions(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x15; local_8++) {
    start_x[local_8] = -1;
    start_y[local_8] = -1;
  }
  return;
}
#undef local_8

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
#define local_974 (*(u8 *)(frame_ + FRAME_OFF(12)))
#define local_970 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_96c (*(i8 (*)[260])(frame_ + FRAME_OFF(20)))
#define local_868 (*(GamePalette *)(frame_ + FRAME_OFF(280)))
#define local_434 (*(int *)(frame_ + FRAME_OFF(1356)))
#define local_430 (*(Dialog *)(frame_ + FRAME_OFF(1360)))
#define local_13c (*(iptr *)(frame_ + FRAME_OFF(2116)))
#define local_138 (*(iptr *)(frame_ + FRAME_OFF(2120)))
#define dst (*(i8 (*)[256])(frame_ + FRAME_OFF(2124)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(2380)))
#define aiStack_30 (*(int (*)[8])(frame_ + FRAME_OFF(2384)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2416)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2420)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(2424)))
int __cdecl setup_start_scenario(void)

{
  i32 uVar1;
  iptr iVar2;
  iptr unit;
  int iVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(2432)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_430,0x4000);
  local_8 = 0;
  palette_init(&local_868);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
LAB_0041e028:
  do {
    if (cd_music_available == 0) {
      snd_cd_stop();
      snd_play_effect(0x6b,0,1,0);
    }
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_868);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    local_434 = game_load_dialog(1,0,1);
    if (local_434 != 0) {
LAB_0041e731:
      if (local_434 != 0) {
        snd_play_effect(0x6a,0,0,0);
      }
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_868);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      iVar4 = local_434;
      local_8 = local_8 & 0xffffff00;
      /* inlined unwind funclet FUN_0041e7b2 */ { palette_destroy((GamePalette *)((iptr)&local_868)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0041e7be */ { dialog_dtor((Dialog *)((iptr)&local_430)); }
      return iVar4;
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
    uVar1 = game_turn_to_year((int)game.turn);
    text_append_year(uVar1);
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    if (scenario_max_turns == 0) {
      text_append_year(2000);
    }
    else {
      uVar1 = game_turn_to_year((int)scenario_max_turns);
      text_append_year(uVar1);
    }
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (cd_music_available != 0) {
      snd_menu_end();
    }
    dialog_init_default(&local_430);
    iVar2 = dialog_load_text(&local_430,(iptr)dst,ADDR(0x6255e0, ((u8 *)&g.d_006255e0)),0x4008001);
    if (iVar2 == 0) goto code_r0x0041e1e4;
    iVar4 = popup_game_flags(ADDR(0x6255ec, ((u8 *)&g.d_006255ec)),1);
  } while (iVar4 < 0);
  goto LAB_0041e2b4;
code_r0x0041e1e4:
  unit = (iptr)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((int)units[unit].owner == (int)scenario_objective_civ)) {
    dialog_add_sprite
              ((DialogOptionList *)&local_430,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0
               ,0);
  }
  iVar4 = dlg_show_modal(&local_430,0);
  if (-1 < iVar4) {
LAB_0041e2b4:
    dlg_reset(&local_430,1);
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        iVar5 = civ_name_plural(civ);
        text_append(iVar5);
        text_append_space();
        text_append_lparen();
        iVar5 = civ_leader_name(civ);
        text_append(iVar5);
        text_append_rparen();
        local_13c = dialog_add_option
                              ((DialogOptionList *)&local_430,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
        aiStack_30[*(int *)(local_13c + 4)] = civ;
      }
    }
    iVar4 = dlg_show_modal(&local_430,0);
    if (-1 < iVar4) {
      saved_turn_civ = (i8)human_civ;
      turn_resume_civ = (i8)human_civ;
      (*(i8 *)((char *)&civ + 0)) = (byte)aiStack_30[iVar4];
      game.human_players = (u8)(1 << ((byte)civ & 0x1f));
      game.player_civ = (byte)civ;
      game.turn_civ = (byte)civ;
      game.game_options = game.game_options & 0xfffffeff;
      human_civ = aiStack_30[iVar4];
      while( true ) {
        dlg_load_game_section(&local_430,ADDR(0x6255fc, ((u8 *)&g.d_006255fc)),1);
        dialog_set_default_choice((DialogOptionList *)&local_430,(uint)game.difficulty);
        dialog_set_position
                  ((C_0040bc40_28 *)&local_430,
                   ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        local_34 = dlg_show_modal(&local_430,0);
        if (local_34 < 0) break;
        game.difficulty = (u8)local_34;
        if ((u8)local_34 == '\0') {
          game.game_options = game.game_options | 0x100;
        }
        else {
          game.game_options = game.game_options & 0xfffffeff;
        }
        dlg_load_game_section(&local_430,ADDR(0x625608, ((u8 *)&g.d_00625608)),1);
        dialog_set_default_choice
                  ((DialogOptionList *)&local_430,(uint)leaders[civs[game.player_civ].tribe].female);
        dialog_set_position
                  ((C_0040bc40_28 *)&local_430,0xfffffc19,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        iVar4 = dlg_show_modal(&local_430,0);
        snd_play_effect(0x6a,0,0,0);
        if (-1 < iVar4) {
          local_974 = (u8)iVar4;
          leaders[civs[game.player_civ].tribe].female = local_974;
          civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
          if (iVar4 != 0) {
            civs[human_civ].flags = civs[human_civ].flags | 0x200;
          }
          for (local_138 = 0; local_138 < 7; local_138++) {
            for (local_970 = 0; local_970 < 2; local_970++) {
              leaders[civs[game.player_civ].tribe].titles[local_138][local_970] = (short)(&government_titles[local_138].male)[local_970];
            }
          }
          iVar4 = dlg_game_text_input(ADDR(0x625610, ((u8 *)&g.d_00625610)),0x17,(iptr)&civ_names[game.player_civ].leader_name,(iptr)local_96c
                                    );
          if (iVar4 == 0) {
            FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,local_96c);
            saved_resume_new_game = 1;
            turn_resume_new_game = 1;
            local_434 = 0;
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
#undef local_974
#undef local_970
#undef local_96c
#undef local_868
#undef local_434
#undef local_430
#undef local_13c
#undef local_138
#undef dst
#undef local_34
#undef aiStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0041e8fb auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_43c (*(u8 *)(frame_ + FRAME_OFF(4)))
#define local_438 (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
#define local_334 (*(int *)(frame_ + FRAME_OFF(268)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(272)))
#define local_32c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_328 (*(Dialog *)(frame_ + FRAME_OFF(280)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(1036)))
#define aiStack_30 (*(iptr (*)[8])(frame_ + FRAME_OFF(1040)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1072)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1076)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1080)))
i32 __cdecl load_game_pick_civ(int param_1)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(1088)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_328,0x4000);
  local_8 = 0;
  while( true ) {
    game.human_players = '\0';
    dlg_reset(&local_328,1);
    dialog_prepend_title_label((iptr)&local_328,param_1 + 0x25e);
    local_334 = 0;
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        iVar1 = civ_name_plural(civ);
        text_append(iVar1);
        text_append_space();
        text_append_lparen();
        iVar1 = civ_leader_name(civ);
        text_append(iVar1);
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
        iVar3 = local_334;
        local_334++;
        local_34 = dialog_add_option((DialogOptionList *)&local_328,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar3,0)
        ;
        aiStack_30[*(int *)(local_34 + 4)] = civ;
      }
    }
    local_32c = local_334;
    local_330 = 0;
    for (local_334 = 0; local_334 < local_32c; local_334++) {
      local_34 = dialog_find_option((DialogOptionList *)&local_328,local_334);
      if (local_34 != 0) {
        local_330++;
        dialog_set_option_disabled((DialogOptionList *)&local_328,*(iptr *)(local_34 + 4),0);
        if ((RadioGroupEnableView *)local_328.field_268 != (RadioGroupEnableView *)0x0) {
          radiogrp_enable_item((RadioGroupEnableView *)local_328.field_268,*(iptr *)(local_34 + 4));
        }
      }
    }
    local_328.field_d8 = 0;
    local_328.field_dc = 0;
    iVar2 = dlg_show_modal(&local_328,0);
    if (iVar2 < 0) break;
    human_civ = aiStack_30[iVar2];
    (*(i8 *)((char *)&civ + 0)) = (byte)human_civ;
    game.human_players = game.human_players | (byte)(1 << ((byte)civ & 0x1f));
    game.player_civ = (byte)civ;
    game.turn_civ = (byte)civ;
    iVar3 = civ_check_password(human_civ);
    if (iVar3 != 0) {
      game.game_options = game.game_options & 0xfffffeff;
      dlg_load_game_section(&local_328,ADDR(0x62563c, ((u8 *)&g.d_0062563c)),1);
      dialog_prepend_title_label((iptr)&local_328,param_1 + 0x25e);
      dialog_set_default_choice
                ((DialogOptionList *)&local_328,(uint)leaders[civs[game.player_civ].tribe].female);
      dialog_set_position
                ((C_0040bc40_28 *)&local_328,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar3 = dlg_show_modal(&local_328,0);
      snd_play_effect(0x6a,0,0,0);
      if (-1 < iVar3) {
        local_43c = (u8)iVar3;
        leaders[civs[game.player_civ].tribe].female = local_43c;
        civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
        if (iVar3 != 0) {
          civs[human_civ].flags = civs[human_civ].flags | 0x200;
        }
        uVar7 = 1;
        uVar6 = 0;
        uVar5 = 0;
        uVar4 = 0;
        iVar1 = civ_leader_name((int)game.player_civ);
        iVar3 = dialog_load_text_section
                          (&local_328,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x625644, ((u8 *)&g.d_00625644)),0x17,iVar1,uVar4,uVar5,uVar6,uVar7);
        if (iVar3 == 0) {
          dialog_prepend_title_label((iptr)&local_328,param_1 + 0x25e);
          iVar3 = dialog_run_modal(&local_328,(iptr)local_438,0);
          if (iVar3 == 0) {
            FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,local_438);
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0041eec6 */ { dialog_dtor((Dialog *)((iptr)&local_328)); }
            uVar4 = 0;
LAB_0041eedc:
            return uVar4;
          }
        }
      }
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0041eec6 */ { dialog_dtor((Dialog *)((iptr)&local_328)); }
  uVar4 = 1;
  goto LAB_0041eedc;
}
#undef human_civ
#undef screen_height
#undef civ
#undef local_43c
#undef local_438
#undef local_334
#undef local_330
#undef local_32c
#undef local_328
#undef local_34
#undef aiStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_754 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_750 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_74c (*(GamePalette *)(frame_ + FRAME_OFF(12)))
#define local_318 (*(int *)(frame_ + FRAME_OFF(1088)))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(1092)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(1848)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(1852)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1856)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1860)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1864)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1868)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(1872)))
int __cdecl game_main_menu_loop(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1880)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_318 = 1;
  local_18 = 1;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  palette_init(&local_74c);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  __chdir(&game_home_dir);
  FUN_005f22d0(&scenario_dir_path,&game_home_dir);
  prefs_load_civ2dat();
  game.game_options = prefs_game_options;
  game.multiplayer = '\0';
  ui_flush_input();
  setup_picwnd_load_dll((C_004083b0_430 *)&setup_picwnd);
  snd_wave_set_buffer_count(4);
  if (intro_theme_started == 0) {
    snd_play_effect(0x6b,0,1,0);
  }
  do {
    FUN_005f22d0(&game_txt_path,&menu_game_txt_name_str);
    FUN_005f22d0(&rules_txt_path,s_RULES_00625654);
    prefs_load_civ2dat();
    setup_clear_start_positions();
    events_reset((ScenarioEvents *)&scenario_events,50000);
    for (civ = 0; civ < 8; civ++) {
      civ_refresh_ai_goals(civ);
      civ_reset_standing_goals(civ);
    }
    game_over_reason = 0;
    if (net_lobby_launch_mode == -1) {
      setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,1,6,1);
      dlg_load_game_section(&local_314,ADDR(0x62565c, ((u8 *)&g.d_0062565c)),1);
      dialog_set_default_choice((DialogOptionList *)&local_314,(int)prefs_main_menu_choice);
      dialog_set_position
                ((C_0040bc40_28 *)&local_314,
                 -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      local_754 = dlg_show_modal(&local_314,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      if (local_754 < 0) goto LAB_0041f5ea;
      prefs_main_menu_choice = (short)local_754;
      prefs_save_civ2dat();
    }
    else {
      local_754 = 5;
    }
    snd_play_effect(0x6a,0,0,0);
    scenario_events_loaded = 0;
    net_session_clear(&net_session);
    switch(local_754) {
    case 0:
    case 1:
    case 2:
      __chdir(&game_home_dir);
      rules_load(1);
      if (local_754 == 1) {
        iVar1 = map_load_dialog();
        if (iVar1 != 0) {
          local_754 = -1;
        }
        local_20 = 1;
        if (map.flat != 0) {
          local_20 = 2;
        }
      }
      else {
        iVar1 = setup_choose_map_size();
        if (iVar1 != 0) {
          local_754 = -1;
        }
        local_20 = 0;
      }
      if (local_754 == 2) {
        iVar1 = setup_custom_world();
        if (iVar1 != 0) {
          local_754 = -1;
        }
      }
      else {
        iVar1 = _rand();
        mapgen_land_mass = iVar1 % 3 - 1;
        mapgen_land_form = 0;
        iVar1 = _rand();
        if (iVar1 % 3 == 0) {
          mapgen_land_form = mapgen_land_mass;
        }
        iVar1 = _rand();
        mapgen_temperature = iVar1 % 3 - 1;
        iVar1 = _rand();
        mapgen_climate = iVar1 % 3 - 1;
        iVar1 = _rand();
        mapgen_age = iVar1 % 3 - 1;
      }
      if (-1 < local_754) {
        local_18 = setup_new_game_dialogs(local_20);
      }
      break;
    case 3:
      event_dont_play_wonders = 0;
      local_18 = setup_start_scenario();
      if (local_18 == 0) {
        if (event_dont_play_wonders != 0) {
          game.game_options = game.game_options & 0xfffeffff;
        }
      }
      else {
        FUN_005f22d0(&scenario_dir_path,&game_home_dir);
      }
      break;
    case 4:
      event_dont_play_wonders = 0;
      local_18 = game_load_dialog(0,0,1);
      snd_play_effect(0x6a,0,0,0);
      if ((local_18 == 0) && (game.multiplayer != '\0')) {
        local_18 = load_game_pick_civ(1);
      }
      if (local_18 == 0) {
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
      XD_GetXDaemonVersion(&local_750,&local_1c,&local_14);
      if (((xdaemon_required_major == local_750) && (xdaemon_required_minor == local_1c)) && (xdaemon_required_build == local_14))
      {
        __chdir(&game_home_dir);
        rules_load(1);
        local_18 = setup_choose_multiplayer_type();
        if ((local_18 != 0) && (net_lobby_launch_mode != -1)) goto LAB_0041f5ea;
      }
      else {
        str_clear(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)));
        str_append_int(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)),xdaemon_required_major);
        FUN_005f22e0(&text_string_args,&xdaemon_req_ver_dot1_str);
        str_append_int(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)),xdaemon_required_minor);
        FUN_005f22e0(&text_string_args,&xdaemon_req_ver_dot2_str);
        str_append_int(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)),xdaemon_required_build);
        str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),local_750);
        FUN_005f22e0(&text_string_arg1,&xdaemon_got_ver_dot1_str);
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),local_1c);
        FUN_005f22e0(&text_string_arg1,&xdaemon_got_ver_dot2_str);
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),local_14);
        popup_game_with_sprite(ADDR(0x625678, ((u8 *)&g.d_00625678)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      break;
    case 6:
      hall_of_fame_show(0xffffffff);
      break;
    case 7:
      iVar1 = popup_game_flags(ADDR(0x62568c, ((u8 *)&g.d_0062568c)),1);
      if (iVar1 < 0) {
        text_close_file();
      }
      else {
        snd_play_effect(-0x6b,0,0,0);
        snd_play_effect(-0x6c,0,0,0);
        snd_cd_detect_layout();
        credits_show(iVar1);
        snd_cd_stop();
        ui_flush_input();
        snd_play_effect(0x6b,0,1,0);
      }
    }
  } while (local_18 != 0);
  local_318 = 0;
LAB_0041f5ea:
  snd_play_effect(-0x6b,0,0,0);
  snd_play_effect(-0x6c,0,0,0);
  snd_wave_set_buffer_count(8);
  if ((local_318 == 0) && (snd_cd_detect_layout(), (game.game_options & 8) != 0)) {
    snd_sync_music_option();
  }
  setup_picwnd_free_dll((C_004083b0_430 *)&setup_picwnd);
  iVar1 = local_318;
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet FUN_0041f66e */ { palette_destroy((GamePalette *)((iptr)&local_74c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0041f67a */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  return iVar1;
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
#undef local_754
#undef local_750
#undef local_74c
#undef local_318
#undef local_314
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0041f69f auto */
#define game_session_active (*(i32 *)((u8 *)&g.d_006252c4))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_show_human_starts (*(short *)((u8 *)&g.d_00654c78))
#define net_local_slot (*(int *)((u8 *)&g.d_006ad304))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define y2 (*(uint *)(frame_ + FRAME_OFF(0)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl game_session_begin(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  game_session_active = 1;
  if ((((turn_resume_civ == '\0') && (game.turn == 0)) && (game.multiplayer != '\0')) &&
     ((mp_show_human_starts != 0 || (game.difficulty == '\0')))) {
    y2 = 0;
    x2 = 0;
    net_batch_begin();
    for (local_8 = 0; local_8 < map.area; local_8++) {
      iVar1 = tile_at(x2,y2);
      if ((game.human_players & *(byte *)(iVar1 + 4)) != 0) {
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
#undef local_8

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
#define local_7e8 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_7e4 (*(FileObject *)(frame_ + FRAME_OFF(4)))
#define local_74c (*(int *)(frame_ + FRAME_OFF(156)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(160)))
#define local_744 (*(int *)(frame_ + FRAME_OFF(164)))
#define city (*(iptr *)(frame_ + FRAME_OFF(168)))
#define local_73c (*(UINT *)(frame_ + FRAME_OFF(172)))
#define local_738 (*(GamePalette *)(frame_ + FRAME_OFF(176)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(1252)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2008)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2012)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(2016)))
void __cdecl game_main(void)

{
  char cVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  size_t sVar5;
  LobbyLaunchInfo *pLVar6;
  i8 frame_[FRAME_OFF(2024)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  palette_init(&local_738);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  dbg_log((iptr)PTR_s_5_4_0f_Multiplayer_26_March_99_0062765c);
  dbg_log((iptr)PTR_s_Patch_3_00627660);
  net_session_clear(&net_session);
  iVar2 = app_startup_init();
  if (iVar2 == 0) {
    _memset(&net_lobby_launch_info,0,0xc4);
    pLVar6 = (LobbyLaunchInfo *)&net_lobby_launch_info;
    iVar3 = wnd_get_window((WndBase *)&main_frame_wnd);
    local_744 = XD_LaunchedByLobby(*(void **)(iVar3 + 4),pLVar6);
    if ((local_744 == 2) || (local_744 == 1)) {
      net_lobby_launch_mode = local_744;
      dbg_log(ADDR(0x625698, ((u8 *)&g.d_00625698)));
      dbg_logf_str(ADDR(0x6256bc, ((u8 *)&g.d_006256bc)),ADDR(0x6ad22c, ((u8 *)&g.d_006ad22c)));
      dbg_logf_str(ADDR(0x6256d8, ((u8 *)&g.d_006256d8)),ADDR(0x6ad24c, ((u8 *)&g.d_006ad24c)));
      dbg_logf_str(ADDR(0x6256f4, ((u8 *)&g.d_006256f4)),ADDR(0x6ad28c, ((u8 *)&g.d_006ad28c)));
      dbg_logf_str(ADDR(0x625710, ((u8 *)&g.d_00625710)),ADDR(0x6ad2ac, ((u8 *)&g.d_006ad2ac)));
      dbg_logf(ADDR(0x62572c, ((u8 *)&g.d_0062572c)),net_lobby_is_host);
    }
    else {
      if (((local_744 != -3) && (local_744 != -4)) && (local_744 != -5)) {
        dbg_log(ADDR(0x625768, ((u8 *)&g.d_00625768)));
        local_74c = XD_LobbySendMessage(2);
        if (local_74c != 0) {
          dbg_logf(ADDR(0x62579c, ((u8 *)&g.d_0062579c)),local_74c);
        }
        local_8 = local_8 & 0xffffff00;
        /* inlined unwind funclet FUN_004201fb */ { palette_destroy((GamePalette *)((iptr)&local_738)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_00420207 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
        goto LAB_0042021d;
      }
      dbg_logf(ADDR(0x625748, ((u8 *)&g.d_00625748)),local_744);
      net_lobby_launch_mode = -1;
    }
    ini_simultaneous_allowed = 0;
    local_73c = GetPrivateProfileIntA
                          (s_Civilization_Gold_006257e4,s_Simultaneous_006257d4,-1,
                           s_CIV_INI_006257cc);
    if (0 < (int)local_73c) {
      ini_simultaneous_allowed = 1;
      WritePrivateProfileStringA
                (s_Civilization_Gold_00625814,s_Simultaneous_00625804,&ini_simultaneous_reset_str,
                 s_CIV_INI_006257f8);
    }
    net_max_players = 7;
    local_73c = GetPrivateProfileIntA
                          (s_Civilization_Gold_0062583c,s_MaxPlayers_00625830,-1,s_CIV_INI_00625828)
    ;
    if (4 < (int)local_73c) {
      if (7 < (int)local_73c) {
        local_73c = 7;
      }
      net_max_players = local_73c;
      WritePrivateProfileStringA
                (s_Civilization_Gold_00625868,s_MaxPlayers_0062585c,&ini_max_players_reset_str,s_CIV_INI_00625850
                );
    }
    FUN_005f22d0(&net_game_name,&prefs_net_game_name);
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
      iVar4 = game_main_menu_loop();
      if (iVar4 != 0) goto LAB_004201d0;
      minimap_window_create();
      status_wnd_open();
      mapviews_create_all();
      city_window_create((FrameWindow *)&city_window);
      if (2 < game.multiplayer) {
        parley_wnd_create((C_004083b0_430 *)&chat_wnd,4);
        parley_wnd_create((C_004083b0_430 *)&parley_wnd,3);
      }
      pedia_window_create((C_004083b0_a28 *)&pedia_window);
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_738);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      if (game.multiplayer != '\0') {
        if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
          rules_apply_double_moves();
        }
        if ((2 < game.multiplayer) && (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
          mp_simultaneous_moves = (char)mp_simultaneous_setting;
          net_send_message(0x33,0xff,(int)mp_double_production,(int)mp_double_moves,(int)mp_simultaneous_setting,0,0,0,0
                             ,0);
        }
      }
      if (2 < game.multiplayer) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x120,1);
        dlg_default_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
        cVar1 = net_is_host(&net_session);
        if (cVar1 != '\0') {
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
            iVar4 = game_mp_client_turn_loop();
            if (iVar4 != 0) {
              game_mp_host_turn_loop(1);
            }
          }
          else {
            game_mp_host_turn_loop(0);
          }
        }
        else if (net_host_flag == '\0') {
          iVar4 = net_client_turn_loop();
          if (iVar4 != 0) {
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
        file_obj_init(&local_7e4);
        local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
        diffeng_free_mirror();
        if (net_host_flag != '\0') {
          net_session_shutdown(&net_session,1);
        }
        iVar4 = file_obj_create(&local_7e4,ADDR(0x625888, ((u8 *)&g.d_00625888)));
        if (iVar4 != 0) {
          sVar5 = _strlen(chat_log_buffer);
          file_obj_write(&local_7e4,(iptr)chat_log_buffer,sVar5);
          file_map_close(&local_7e4);
        }
        for (local_7e8 = 0; local_7e8 < 8; local_7e8++) {
          *(i32 *)(&chat_send_to_civs + local_7e8 * 4) = 0;
          *(i32 *)(&chat_muted_civs + local_7e8 * 4) = 0;
        }
        chat_remain_anonymous = 0;
        chat_broadcast_all = 0;
        chat_mute_anonymous = 0;
        parley_wnd_close();
        chat_wnd_close();
        local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
        /* inlined unwind funclet FUN_004201ef */ { file_obj_close((FileObject *)((iptr)&local_7e4)); }
      }
      pedia_close();
      picwnd_close((C_004083b0_488 *)&advisor_window);
      picwnd_close((C_004083b0_488 *)&casualty_window);
      if (app_shutdown_done != 0) {
        local_8 = local_8 & 0xffffff00;
        /* inlined unwind funclet FUN_004201fb */ { palette_destroy((GamePalette *)((iptr)&local_738)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_00420207 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
        goto LAB_0042021d;
      }
      game_session_end();
    } while (net_lobby_launch_mode == -1);
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet FUN_004201fb */ { palette_destroy((GamePalette *)((iptr)&local_738)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00420207 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  else {
LAB_004201d0:
    app_shutdown_cleanup();
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet FUN_004201fb */ { palette_destroy((GamePalette *)((iptr)&local_738)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00420207 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
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
#undef local_7e8
#undef local_7e4
#undef local_74c
#undef unit
#undef local_744
#undef city
#undef local_73c
#undef local_738
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00421bb0 auto */
i32 __cdecl timer_ticks(void)

{
  i32 uVar1;
  
  uVar1 = timer_ticks_60hz();
  return uVar1;
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
#define local_3c (*(uint (*)[10])(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(56)))
i32 __cdecl game_profile_popup(int param_1)

{
  size_t sVar1;
  i32 uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_3c[0] = 0;
  local_3c[1] = 1;
  local_3c[2] = 3;
  local_3c[3] = 7;
  local_3c[4] = 0xf;
  local_3c[5] = 0x1f;
  local_3c[6] = 0x3f;
  local_3c[7] = 0x7f;
  local_3c[8] = 0xff;
  str_clear(ADDR(0x63cc48, ((u8 *)&g.d_0063cc48)));
  FUN_005f22e0(&text_string_args,&net_game_name);
  str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
  str_append_label(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),(mp_open_game == 0) + 0x277);
  str_clear(ADDR(0x63ce50, ((u8 *)&g.d_0063ce50)));
  FUN_005f22e0(&text_string_arg2,&net_host_player_name);
  str_clear(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  sVar1 = _strlen(&scenario_name);
  if (sVar1 == 0) {
    str_append_label(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)),0x34c);
  }
  else {
    FUN_005f22d0(&text_string_arg3,&scenario_name);
  }
  str_append_space(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  str_append_lparen(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)));
  uVar2 = game_turn_to_year((int)game.turn);
  str_append_year(ADDR(0x63cf54, ((u8 *)&g.d_0063cf54)),uVar2);
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
  FUN_005f22e0(&text_string_arg5,&game_profile_double_opts_sep_str);
  str_append_label(ADDR(0x63d15c, ((u8 *)&g.d_0063d15c)),0x352 - (uint)(mp_double_moves == 0));
  str_clear(ADDR(0x63d260, ((u8 *)&g.d_0063d260)));
  str_append_label(ADDR(0x63d260, ((u8 *)&g.d_0063d260)),game.barbarian_activity + 0x27f);
  str_clear(ADDR(0x63d364, ((u8 *)&g.d_0063d364)));
  if (mp_turn_time_limit_ms == 0) {
    str_append_label(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),0x285);
  }
  else {
    iVar3 = (mp_turn_time_limit_ms / 1000) / 0x3c;
    local_c = (mp_turn_time_limit_ms / 1000) % 0x3c;
    if (iVar3 < 10) {
      str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),0);
    }
    str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),iVar3);
    FUN_005f22e0(&game_profile_timer_text,&game_profile_timer_colon_str);
    if (local_c < 10) {
      str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),0);
    }
    str_append_int(ADDR(0x63d364, ((u8 *)&g.d_0063d364)),local_c);
  }
  str_clear(ADDR(0x63d468, ((u8 *)&g.d_0063d468)));
  local_14 = 0;
  local_3c[9] = (uint)game.civs_alive;
  for (local_10 = 1; local_3c[9] = (int)local_3c[9] >> 1, local_10 < 8; local_10++) {
    if ((local_3c[9] & 1) != 0) {
      local_14++;
    }
  }
  str_append_int(ADDR(0x63d468, ((u8 *)&g.d_0063d468)),local_14);
  str_clear(ADDR(0x63d56c, ((u8 *)&g.d_0063d56c)));
  local_8 = 0;
  if (game.multiplayer == '\0') {
    local_8 = 1;
  }
  else if (game.multiplayer == 1) {
    local_8 = (uint)hotseat_human_players;
  }
  else {
    local_8 = local_3c[net_player_count];
  }
  local_14 = 0;
  local_3c[9] = local_8;
  for (local_10 = 0; local_10 < 8; local_10++) {
    if ((local_3c[9] & 1) != 0) {
      local_14++;
    }
    local_3c[9] = (int)local_3c[9] >> 1;
  }
  if (param_1 != 0) {
    local_14--;
  }
  str_append_int(ADDR(0x63d56c, ((u8 *)&g.d_0063d56c)),local_14);
  dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
  uVar2 = popup_text_with_sprite(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x625d74, ((u8 *)&g.d_00625d74)),(uint)(param_1 != 0),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  return uVar2;
}
#undef dlg_pending_idle_callback
#undef hotseat_human_players
#undef mp_double_moves
#undef mp_double_production
#undef mp_open_game
#undef mp_simultaneous_setting
#undef mp_turn_time_limit_ms
#undef scenario_name
#undef local_3c
#undef local_14
#undef local_10
#undef local_c
#undef local_8

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
#define local_888 (*(LobbyList * *)(frame_ + FRAME_OFF(0)))
#define this2 (*(void * *)(frame_ + FRAME_OFF(20)))
#define local_854 (*(char (*)[260])(frame_ + FRAME_OFF(52)))
#define local_750 (*(GamePalette *)(frame_ + FRAME_OFF(312)))
#define local_31c (*(int *)(frame_ + FRAME_OFF(1388)))
#define local_318 (*(int *)(frame_ + FRAME_OFF(1392)))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(1396)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(2152)))
#define local_1c (*(char *)(frame_ + FRAME_OFF(2156)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(2160)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(2164)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2168)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2172)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(2176)))
i32 __cdecl setup_network_game(int param_1)

{
  size_t sVar1;
  int iVar2;
  i32 uVar3;
  int iVar4;
  C_00421f70 *this;
  char *pcVar5;
  size_t sVar6;
  LobbyListCtorView *this_00;
  i8 frame_[FRAME_OFF(2184)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  local_318 = 1;
  palette_init(&local_750);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  if ((((param_1 != 0) && (param_1 != 1)) && (param_1 != 4)) && ((param_1 != 2 && (param_1 != 3))))
  {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62640c, ((u8 *)&g.d_0062640c)),ADDR(0x6263e8, ((u8 *)&g.d_006263e8)),0x21);
  }
  net_connection_type = param_1;
  if ((param_1 == 1) || (param_1 == 4)) {
    dlg_load_game_section(&local_314,ADDR(0x6264a4, ((u8 *)&g.d_006264a4)),1);
    dialog_set_default_choice((DialogOptionList *)&local_314,(int)(short)prefs_net_protocol);
    if (param_1 == 4) {
      dialog_set_option_disabled((DialogOptionList *)&local_314,1,1);
    }
    local_14 = dlg_show_modal(&local_314,0);
    if (local_14 == -1) {
      local_8 = local_8 & 0xffffff00;
      /* inlined unwind funclet FUN_0044525d */ { palette_destroy((GamePalette *)((iptr)&local_750)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00445269 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
      uVar3 = 1;
      goto LAB_0044527f;
    }
    net_protocol = (uint)(local_14 != 0);
    prefs_net_protocol = (ushort)(local_14 != 0);
    if (param_1 == 4) {
      game.multiplayer = 4;
      param_1 = 0;
      net_connection_type = 0;
    }
    else {
      game.multiplayer = 3;
    }
  }
  else if (param_1 == 0) {
    net_protocol = 0;
    game.multiplayer = 4;
  }
  else if (param_1 == 2) {
    net_protocol = 2;
    game.multiplayer = 5;
  }
  else {
    game.multiplayer = 6;
    net_protocol = 3;
  }
  text_clear();
  if (param_1 == 0) {
    text_append_label(0x28f);
  }
  else if ((param_1 == 1) || (param_1 == 4)) {
    if (param_1 == 1) {
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
  sVar1 = _strlen(&text_buffer);
  net_connection_title = operator_new(sVar1 + 1);
  if (net_connection_title == (char *)0x0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6264d4, ((u8 *)&g.d_006264d4)),ADDR(0x6264b0, ((u8 *)&g.d_006264b0)),0x79);
  }
  FUN_005f22d0(net_connection_title,&text_buffer);
  turn_resume_new_game = 0;
  saved_resume_new_game = 0;
LAB_0044465c:
  if (turn_resume_new_game == 1) {
    snd_play_effect(0x6a,0,0,0);
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_750);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_flush_paint();
  }
  for (local_31c = 0; local_31c < 8; local_31c++) {
    *(i16 *)(&civ_intro_shown + local_31c * 2) = 0;
    (&DAT_00654ea4)[local_31c * 0x20] = 0;
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
  FUN_005f22d0(&scenario_dir_path,&game_home_dir);
  if (local_318 == 0) {
    rules_load(1);
  }
  scenario_events_loaded = 0;
  setup_dialog_pos_state = 3;
  setup_show_side_picture(0xffffffff,0);
  FUN_005f22d0(&text_string_args,net_connection_title);
  dlg_load_game_section(&local_314,ADDR(0x6264ec, ((u8 *)&g.d_006264ec)),1);
  iVar2 = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
  uVar3 = setup_next_dialog_x(0);
  dialog_set_position((C_0040bc40_28 *)&local_314,uVar3,iVar2);
  if (net_lobby_launch_mode == 2) {
    dialog_set_option_disabled((DialogOptionList *)&local_314,5,1);
    if (prefs_lan_menu_choice == 5) {
      dialog_set_default_choice((DialogOptionList *)&local_314,0);
    }
    else {
      dialog_set_default_choice((DialogOptionList *)&local_314,(int)prefs_lan_menu_choice);
    }
  }
  else if (net_lobby_launch_mode == 1) {
    dialog_set_option_disabled((DialogOptionList *)&local_314,0,1);
    dialog_set_option_disabled((DialogOptionList *)&local_314,1,1);
    dialog_set_option_disabled((DialogOptionList *)&local_314,2,1);
    dialog_set_option_disabled((DialogOptionList *)&local_314,3,1);
    dialog_set_option_disabled((DialogOptionList *)&local_314,4,1);
    dialog_set_default_choice((DialogOptionList *)&local_314,5);
  }
  else {
    dialog_set_default_choice((DialogOptionList *)&local_314,(int)prefs_lan_menu_choice);
  }
  iVar2 = dlg_show_modal(&local_314,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  local_318 = 0;
  if (iVar2 < 0) {
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet FUN_0044525d */ { palette_destroy((GamePalette *)((iptr)&local_750)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00445269 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
    uVar3 = 1;
    goto LAB_0044527f;
  }
  prefs_lan_menu_choice = (short)iVar2;
  if ((-1 < iVar2) && (iVar2 < 3)) {
    __chdir(&game_home_dir);
  }
  switch(iVar2) {
  case 0:
    iVar4 = setup_choose_map_size();
    if (iVar4 == 0) {
      local_20 = 0;
      iVar4 = _rand();
      mapgen_land_mass = iVar4 % 3 - 1;
      mapgen_land_form = 0;
      iVar4 = _rand();
      if (iVar4 % 3 == 0) {
        mapgen_land_form = mapgen_land_mass;
      }
      iVar4 = _rand();
      mapgen_temperature = iVar4 % 3 - 1;
      iVar4 = _rand();
      mapgen_climate = iVar4 % 3 - 1;
      iVar4 = _rand();
      mapgen_age = iVar4 % 3 - 1;
      iVar4 = setup_choose_game_options(local_20,3);
      goto joined_r0x00444b3b;
    }
    goto LAB_0044465c;
  case 1:
    iVar4 = map_load_dialog();
    if (iVar4 == 0) {
      local_20 = 1;
      if (map.flat != 0) {
        local_20 = 2;
      }
      iVar4 = _rand();
      mapgen_land_mass = iVar4 % 3 - 1;
      mapgen_land_form = 0;
      iVar4 = _rand();
      if (iVar4 % 3 == 0) {
        mapgen_land_form = mapgen_land_mass;
      }
      iVar4 = _rand();
      mapgen_temperature = iVar4 % 3 - 1;
      iVar4 = _rand();
      mapgen_climate = iVar4 % 3 - 1;
      iVar4 = _rand();
      mapgen_age = iVar4 % 3 - 1;
      iVar4 = setup_choose_game_options(local_20,3);
      goto joined_r0x00444b3b;
    }
    goto LAB_0044465c;
  case 2:
    iVar4 = setup_choose_map_size();
    if (iVar4 != 0) goto LAB_0044465c;
    local_20 = 0;
    iVar4 = setup_custom_world();
    if (iVar4 != 0) goto LAB_0044465c;
    iVar4 = setup_choose_game_options(local_20,3);
joined_r0x00444b3b:
    if (iVar4 != 0) goto LAB_0044465c;
    break;
  case 3:
    event_dont_play_wonders = 0;
    iVar4 = setup_mp_load_scenario(3);
    if (iVar4 != 0) {
      FUN_005f22d0(&scenario_dir_path,&game_home_dir);
      goto LAB_0044465c;
    }
    if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    break;
  case 4:
    event_dont_play_wonders = 0;
    iVar4 = game_load_dialog(0,3,1);
    if (iVar4 == 0) {
      if (2 < game.multiplayer) break;
      FUN_005f22d0(&text_string_args,net_connection_title);
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
  if (iVar2 != 5) {
    local_18 = (int)mp_open_game;
    mp_open_game = 1;
    if (((param_1 != 2) && (param_1 != 3)) ||
       ((iVar2 = net_prompt_player_name(), iVar2 != 0 && (iVar2 = net_prompt_game_name(), iVar2 != 0)))) {
      local_1c = net_init_transport(&net_session,net_protocol,1);
      if (local_1c == '\0') {
        if ((net_protocol != 2) && (net_protocol != 3)) {
          dbg_log(ADDR(0x62653c, ((u8 *)&g.d_0062653c)));
          FUN_005f22d0(&text_string_args,net_connection_title);
          popup_game_with_sprite(ADDR(0x62656c, ((u8 *)&g.d_0062656c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        goto LAB_0044465c;
      }
      if ((param_1 != 2) && (param_1 != 3)) {
        iVar2 = net_prompt_player_name();
        if (iVar2 == 0) {
          net_session_shutdown(&net_session,1);
          goto LAB_0044465c;
        }
        iVar2 = net_prompt_game_name();
        if (iVar2 == 0) {
          net_session_shutdown(&net_session,1);
          goto LAB_0044465c;
        }
      }
      if (param_1 == 0) {
        do {
          if (net_lobby_launch_mode != -1) {
            FUN_005f22d0(&prefs_net_ip_address,&net_lobby_launch_info);
            goto LAB_0044501d;
          }
          pcVar5 = XD_GetCurrentProtoAddr(net_xd_adapter_index,net_active_protocol);
          if (pcVar5 == (char *)0x0) {
            prefs_net_ip_address = 0;
          }
          else {
            pcVar5 = XD_GetCurrentProtoAddr(net_adapter_index,net_protocol);
            FUN_005f22d0(&prefs_net_ip_address,pcVar5);
          }
          dialog_load_text_section(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62657c, ((u8 *)&g.d_0062657c)),0x1f,ADDR(0x6665b0, ((u8 *)&g.d_006665b0)),0,0,0,1);
          local_14 = dialog_run_modal(&local_314,(iptr)local_854,0);
          if (local_14 == -1) {
            net_session_shutdown(&net_session,1);
            goto LAB_0044465c;
          }
          sVar1 = _strlen(local_854);
        } while (sVar1 == 0);
        FUN_005f22d0(&prefs_net_ip_address,local_854);
LAB_0044501d:
        sVar1 = _strlen(net_connection_title);
        sVar6 = _strlen(&prefs_net_ip_address);
        pcVar5 = operator_new(sVar1 + sVar6 + 3);
        if (pcVar5 == (char *)0x0) {
          err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6265ac, ((u8 *)&g.d_006265ac)),ADDR(0x626588, ((u8 *)&g.d_00626588)),0x1b9);
        }
        FUN_005f22d0(pcVar5,net_connection_title);
        FUN_005f22e0(pcVar5,&net_title_ip_sep_str);
        FUN_005f22e0(pcVar5,&prefs_net_ip_address);
        operator_delete(net_connection_title);
        net_connection_title = pcVar5;
      }
      else if (((param_1 == 1) || (param_1 == 4)) && (iVar2 = net_prompt_ip_address(), iVar2 == 0)) {
        net_session_shutdown(&net_session,1);
        goto LAB_0044465c;
      }
      this_00 = operator_new(0x70);
      (*(i8 *)((char *)&local_8 + 0)) = 3;
      if (this_00 == (LobbyListCtorView *)0x0) {
        local_888 = (LobbyList *)0x0;
      }
      else {
        local_888 = (LobbyList *)lobby_list_ctor(this_00);
      }
      local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
      net_lobby_list = local_888;
      iVar2 = lobby_host_wait_players(local_888,local_20,param_1);
      if (net_lobby_list != (LobbyList *)0x0) {
        lobby_list_scalar_dtor(net_lobby_list,1);
      }
      net_lobby_list = (LobbyList *)0x0;
      if (iVar2 != 0) goto LAB_004451fb;
      net_session_shutdown(&net_session,1);
      loaded_file_subdir = 0;
      scenario_reset_params();
    }
    goto LAB_0044465c;
  }
  local_1c = net_init_transport(&net_session,net_protocol,0);
  if (local_1c == '\0') {
    dbg_log(ADDR(0x6264fc, ((u8 *)&g.d_006264fc)));
    FUN_005f22d0(&text_string_args,net_connection_title);
    popup_game_with_sprite(ADDR(0x62652c, ((u8 *)&g.d_0062652c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    goto LAB_0044465c;
  }
  iVar2 = net_prompt_player_name();
  if (iVar2 == 0) {
    net_session_shutdown(&net_session,1);
    goto LAB_0044465c;
  }
  if (((param_1 != 2) && (param_1 != 3)) && (iVar2 = net_prompt_ip_address(), iVar2 == 0)) {
    net_session_shutdown(&net_session,1);
    goto LAB_0044465c;
  }
  this = operator_new(0x178);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  if (this == (C_00421f70 *)0x0) {
    this2 = (void *)0x0;
  }
  else {
    this2 = (void *)net_gamelist_view_ctor(this);
  }
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  net_session = (iptr)this2;
  local_14 = FUN_00421fcd(this2,param_1);
  if (net_session != 0) {
    net_gamelist_view_scalar_dtor((void *)net_session,1);
  }
  net_session = 0;
  if (local_14 == 0) {
    net_session_shutdown(&net_session,1);
    loaded_file_subdir = 0;
    scenario_reset_params();
    goto LAB_0044465c;
  }
LAB_004451fb:
  mp_open_game = (short)local_18;
  game_setup_complete = 1;
  prefs_save_civ2dat();
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet FUN_0044525d */ { palette_destroy((GamePalette *)((iptr)&local_750)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00445269 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  uVar3 = 0;
LAB_0044527f:
  return uVar3;
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
#undef local_888
#undef this2
#undef local_854
#undef local_750
#undef local_31c
#undef local_318
#undef local_314
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_844 (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define local_410 (*(Dialog *)(frame_ + FRAME_OFF(1080)))
#define local_11c (*(int *)(frame_ + FRAME_OFF(1836)))
#define dst (*(i8 (*)[260])(frame_ + FRAME_OFF(1840)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(2100)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2104)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2108)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(2112)))
i32 __cdecl setup_mp_load_scenario(i32 param_1)

{
  iptr iVar1;
  i32 uVar1;
  iptr iVar2;
  int unit;
  i8 frame_[FRAME_OFF(2120)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_410,0x4000);
  local_8 = 0;
  palette_init(&local_844);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
LAB_00445759:
  do {
    if (cd_music_available == 0) {
      snd_cd_stop();
      snd_play_effect(0x6b,0,1,0);
    }
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_844);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    iVar1 = game_load_dialog(1,3,1);
    if (iVar1 != 0) {
      snd_play_effect(0x6a,0,0,0);
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_844);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      wnd_flush_paint();
      local_8 = local_8 & 0xffffff00;
      /* inlined unwind funclet FUN_00445e15 */ { palette_destroy((GamePalette *)((iptr)&local_844)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00445e21 */ { dialog_dtor((Dialog *)((iptr)&local_410)); }
      uVar1 = 1;
LAB_00445e37:
      return uVar1;
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
    uVar1 = game_turn_to_year((int)game.turn);
    text_append_year(uVar1);
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    if (scenario_max_turns == 0) {
      text_append_year(2000);
    }
    else {
      uVar1 = game_turn_to_year((int)scenario_max_turns);
      text_append_year(uVar1);
    }
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (cd_music_available != 0) {
      snd_menu_end();
    }
    dialog_init_default(&local_410);
    iVar2 = dialog_load_text(&local_410,(iptr)dst,ADDR(0x6265d8, ((u8 *)&g.d_006265d8)),0x4008001);
    if (iVar2 == 0) goto code_r0x0044597e;
    unit = popup_game_flags(ADDR(0x6265e4, ((u8 *)&g.d_006265e4)),1);
  } while (unit < 0);
  goto LAB_00445a4e;
code_r0x0044597e:
  unit = (int)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((int)units[unit].owner == (int)scenario_objective_civ)) {
    dialog_add_sprite
              ((DialogOptionList *)&local_410,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0
               ,0);
  }
  unit = dlg_show_modal(&local_410,0);
  if (-1 < unit) {
LAB_00445a4e:
    while( true ) {
      dlg_load_game_section(&local_410,ADDR(0x6265f4, ((u8 *)&g.d_006265f4)),1);
      dialog_set_default_choice((DialogOptionList *)&local_410,(uint)game.difficulty);
      dialog_set_position
                ((C_0040bc40_28 *)&local_410,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      local_14 = dlg_show_modal(&local_410,0);
      if (local_14 < 0) break;
      game.difficulty = (u8)local_14;
      if ((u8)local_14 == '\0') {
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
        dialog_load_text_section(&local_410,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x626600, ((u8 *)&g.d_00626600)),0,0,0,0,0,0);
        if (ini_simultaneous_allowed == 0) {
          mp_simultaneous_moves = 0;
          mp_simultaneous_setting = 0;
        }
        else {
          text_clear();
          text_append_label(0x364);
          dialog_add_option((DialogOptionList *)&local_410,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
          dlg_check_set(6,(int)prefs_mp_simultaneous_moves);
        }
        if (((byte)local_410.field_3c & 4) != 0) {
          for (local_11c = 0; local_11c < (int)local_410.field_28; local_11c++) {
            dialog_set_option_checked
                      ((DialogOptionList *)&local_410,local_11c,
                       1 << ((byte)local_11c & 0x1f) & dlg_check_bits);
          }
        }
        dialog_set_position
                  ((C_0040bc40_28 *)&local_410,
                   ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        unit = dlg_show_modal(&local_410,0);
        snd_play_effect(0x6a,0,0,0);
        if (unit < 0) break;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,0);
        mp_open_game = (short)uVar1;
        prefs_mp_open_game = mp_open_game;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,1);
        mp_kill_civ_on_retire = (short)uVar1;
        prefs_mp_kill_on_retire = mp_kill_civ_on_retire;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,2);
        mp_show_human_starts = (short)uVar1;
        prefs_mp_show_human_starts = mp_show_human_starts;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,3);
        mp_chat_from_start = (short)uVar1;
        prefs_mp_chat_from_start = mp_chat_from_start;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,4);
        mp_double_production = (short)uVar1;
        prefs_mp_double_production = mp_double_production;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,5);
        mp_double_moves = (short)uVar1;
        prefs_mp_double_moves = mp_double_moves;
        if (ini_simultaneous_allowed != 0) {
          uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,6);
          mp_simultaneous_setting = (short)uVar1;
          prefs_mp_simultaneous_moves = mp_simultaneous_setting;
        }
        saved_resume_new_game = 1;
        turn_resume_new_game = 1;
        unit = setup_choose_game_timer(0);
        if (unit == 0) {
          turn_resume_civ = (i8)human_civ;
          saved_turn_civ = (i8)human_civ;
          local_8 = local_8 & 0xffffff00;
          /* inlined unwind funclet FUN_00445e15 */ { palette_destroy((GamePalette *)((iptr)&local_844)); }
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_00445e21 */ { dialog_dtor((Dialog *)((iptr)&local_410)); }
          uVar1 = 0;
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
#undef local_844
#undef local_410
#undef local_11c
#undef dst
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_414 (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define local_410 (*(char (*)[1024])(frame_ + FRAME_OFF(8)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(1032)))
#define local_c (*(int * *)(frame_ + FRAME_OFF(1036)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1040)))
void __cdecl registry_load_default_language(void)

{
  i8 frame_[FRAME_OFF(1048)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  _sprintf(local_410,s_Software__s__s_006269a4,PTR_s_MicroProse_Software_0061c354,
           PTR_s_Civilization_II_Multiplayer_Gold_0061c358);
  local_c = (int *)registry_read_value((iptr)local_410,ADDR(0x6269b4, ((u8 *)&g.d_006269b4)),(iptr)&local_10,(iptr)local_414);
  if ((local_c == (int *)0x0) || (local_10 == 0)) {
    local_8 = 0;
  }
  else {
    local_8 = *local_c;
  }
  if (local_8 == 0) {
    local_8 = 1;
  }
  _sprintf(local_410,s_Software__s__s_006269c4,PTR_s_MicroProse_Software_0061c354,
           PTR_s_Civilization_II_Multiplayer_Gold_0061c358);
  registry_write_value((iptr)local_410,ADDR(0x6269d4, ((u8 *)&g.d_006269d4)),(iptr)&local_8,4,4);
  registry_language_id = local_8;
  return;
}
#undef local_414
#undef local_410
#undef local_10
#undef local_c
#undef local_8

/* 0045406c auto */
#define local_10 (*(HKEY *)(frame_ + FRAME_OFF(0)))
#define local_c (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
bool __cdecl registry_write_value(iptr param_1,iptr param_2,iptr param_3,DWORD param_4,DWORD param_5)

{
  LSTATUS LVar1;
  bool bVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  LVar1 = RegCreateKeyExA((HKEY)0x80000002,(LPCSTR)param_1,0,&registry_key_class_str,0,0x20006,
                          (LPSECURITY_ATTRIBUTES)0x0,&local_10,&local_c);
  if (LVar1 == 0) {
    local_8 = RegSetValueExA(local_10,(LPCSTR)param_2,0,param_5,(BYTE *)param_3,param_4);
    RegCloseKey(local_10);
    bVar2 = local_8 == 0;
  }
  else {
    RegCloseKey(local_10);
    bVar2 = false;
  }
  return bVar2;
}
#undef local_10
#undef local_c
#undef local_8

/* 00454103 auto */
#define local_10 (*(DWORD *)(frame_ + FRAME_OFF(0)))
#define local_c (*(HKEY *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(8)))
i8 * __cdecl registry_read_value(iptr param_1,iptr param_2,iptr param_3,iptr param_4)

{
  LSTATUS LVar1;
  i8 *puVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0x800;
  _memset(&registry_value_buffer,0,0x800);
  *(i32 *)param_3 = 0;
  *(i32 *)param_4 = 0;
  LVar1 = RegOpenKeyExA((HKEY)0x80000002,(LPCSTR)param_1,0,0x20019,&local_c);
  if (LVar1 == 0) {
    LVar1 = RegQueryValueExA(local_c,(LPCSTR)param_2,(LPDWORD)0x0,&local_8,&registry_value_buffer,&local_10);
    if (LVar1 == 0) {
      *(DWORD *)param_4 = local_8;
      *(DWORD *)param_3 = local_10;
      RegCloseKey(local_c);
      puVar2 = &registry_value_buffer;
    }
    else {
      RegCloseKey(local_c);
      puVar2 = (i8 *)0x0;
    }
  }
  else {
    RegCloseKey(local_c);
    puVar2 = (i8 *)0x0;
  }
  return puVar2;
}
#undef local_10
#undef local_c
#undef local_8

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
  events_dtor((C_0040bc40_28 *)&scenario_events);
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
  wnd_ctor((C_00408010_b8 *)&main_frame_wnd);
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
#define local_fbc (*(C_00408010_b8 *)(frame_ + FRAME_OFF(4)))
#define local_f04 (*(GamePalette *)(frame_ + FRAME_OFF(188)))
#define local_ad0 (*(DllHandle *)(frame_ + FRAME_OFF(1264)))
#define local_acc (*(i8 (*)[128])(frame_ + FRAME_OFF(1268)))
#define local_a4c (*(i8 (*)[72])(frame_ + FRAME_OFF(1396)))
#define local_a04 (*(i8 (*)[2528])(frame_ + FRAME_OFF(1468)))
#define local_24 (*(i8 (*)[8])(frame_ + FRAME_OFF(3996)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(4004)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(4008)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4012)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(4016)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4020)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(4024)))
void __cdecl intro_play_opening_video(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(4032)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  mmwnd_ctor((C_004083b0_a28 *)local_a4c);
  local_8 = 0;
  wnd_ctor(&local_fbc);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  palette_init(&local_f04);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  dll_handle_init(&local_ad0);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  gfx_get_screen_rect((iptr)local_24);
  opening_video_player = local_a4c;
  str_clear((iptr)local_acc);
  str_append((iptr)local_acc,ADDR(0x62af18, ((u8 *)&g.d_0062af18)));
  iVar1 = file_resolve_path((iptr)local_acc);
  if (iVar1 == 0) {
    (*(i8 *)((char *)&local_8 + 0)) = 2;
    /* inlined unwind funclet FUN_0046dd98 */ { dll_free((DllHandle *)((iptr)&local_ad0)); }
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_0046dda4 */ { palette_destroy((GamePalette *)((iptr)&local_f04)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&local_fbc)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&local_a4c)); }
  }
  else {
    dll_handle_load(&local_ad0,(iptr)local_acc);
    str_clear((iptr)local_acc);
    str_append((iptr)local_acc,ADDR(0x62af2c, ((u8 *)&g.d_0062af2c)));
    iVar1 = file_resolve_path((iptr)local_acc);
    if (iVar1 == 0) {
      (*(i8 *)((char *)&local_8 + 0)) = 2;
      /* inlined unwind funclet FUN_0046dd98 */ { dll_free((DllHandle *)((iptr)&local_ad0)); }
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet FUN_0046dda4 */ { palette_destroy((GamePalette *)((iptr)&local_f04)); }
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&local_fbc)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&local_a4c)); }
    }
    else {
      wnd_create_with_cmd_proc
                ((WndBase *)&local_fbc,ADDR(0x62af44, ((u8 *)&g.d_0062af44)),0x800,0,0,local_1c,local_18 + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
      wnd_set_bg_color((WndBase *)&local_fbc,0);
      opening_video_player = local_a4c;
      avi_player_create((C_004083b0_61c *)local_a4c,ADDR(0x62af48, ((u8 *)&g.d_0062af48)),0x800,0,0);
      wnd_set_lbuttonup_handler((C_00408130 *)(local_a04 + 0x10),ADDR(0x46dea1, intro_video_on_click));
      wnd_set_keydown_handler((C_00408130 *)(local_a04 + 0x10),ADDR(0x46de25, intro_video_on_keydown));
      avi_player_set_end_callback((AviPlayerEndCbSetView *)local_a4c,ADDR(0x46dde0, intro_video_on_end));
      avi_player_set_double_size((C_004083b0_61c *)local_a4c,1);
      local_14 = avi_player_open((AviPlayerOpenView *)local_a4c,(iptr)local_acc);
      if (local_14 == 0) {
        surface_fill((DibSurface *)local_a4c,0);
        wnd_center((WndCenterView *)local_a04);
        wnd_handle_show_raise((WndBase *)&local_fbc);
        wnd_flush_paint();
        window_show((C_004083b0_4 *)local_a4c);
        wnd_flush_paint();
        avi_player_play((AviPlayerPlayView *)local_a4c);
        wnd_set_capture((WndBase *)local_a04);
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((C_00408010_b8 *)local_a04,ADDR(0x403585, net_modal_idle_poll));
        }
        wnd_run_modal_loop((C_00408010_b8 *)local_a04);
        wnd_set_modal_idle_callback((C_00408010_b8 *)local_a04,0);
        wnd_release_capture((WndBase *)local_a04);
        avi_player_pause((AviPlayerPauseView *)local_a4c);
        wnd_hide((WndBase *)local_a04);
        wnd_flush_paint();
        wnd_hide((WndBase *)&local_fbc);
        opening_video_player = (i8 *)0x0;
        dll_handle_free(&local_ad0);
        (*(i8 *)((char *)&local_8 + 0)) = 2;
        /* inlined unwind funclet FUN_0046dd98 */ { dll_free((DllHandle *)((iptr)&local_ad0)); }
        (*(i8 *)((char *)&local_8 + 0)) = 1;
        /* inlined unwind funclet FUN_0046dda4 */ { palette_destroy((GamePalette *)((iptr)&local_f04)); }
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet FUN_0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&local_fbc)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&local_a4c)); }
      }
      else {
        if (local_14 == -0x7ffbfeac) {
          popup_game(ADDR(0x62af4c, ((u8 *)&g.d_0062af4c)));
        }
        opening_video_player = (i8 *)0x0;
        (*(i8 *)((char *)&local_8 + 0)) = 2;
        /* inlined unwind funclet FUN_0046dd98 */ { dll_free((DllHandle *)((iptr)&local_ad0)); }
        (*(i8 *)((char *)&local_8 + 0)) = 1;
        /* inlined unwind funclet FUN_0046dda4 */ { palette_destroy((GamePalette *)((iptr)&local_f04)); }
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet FUN_0046ddb0 */ { wnd_dtor((WndBase *)((iptr)&local_fbc)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0046ddbc */ { avi_player_dtor((AviPlayer *)((iptr)&local_a4c)); }
      }
    }
  }
  return;
}
#undef opening_video_player
#undef local_fbc
#undef local_f04
#undef local_ad0
#undef local_acc
#undef local_a4c
#undef local_a04
#undef local_24
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0046dde0 auto */
#define intro_theme_started (*(i32 *)((u8 *)&g.d_0062af10))
#define opening_video_player (*(int *)((u8 *)&g.d_0062af14))
void __cdecl intro_video_on_end(void)

{
  if (opening_video_player != 0) {
    wnd_end_modal_loop((C_00408010_b8 *)(opening_video_player + 0x48));
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
void __cdecl intro_video_on_keydown(int param_1)

{
  if ((0xcf < param_1) && (param_1 < 0xd3)) {
    snd_play_effect(0x6b,0,1,0);
    intro_theme_started = 1;
    if (opening_video_player != 0) {
      wnd_end_modal_loop((C_00408010_b8 *)(opening_video_player + 0x48));
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
    wnd_end_modal_loop((C_00408010_b8 *)(opening_video_player + 0x48));
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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl save_pack_layout_rects(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  save_layout_record = (i16)saved_layout_valid;
  rect_pack_to_short(ADDR(0x655284, ((u8 *)&g.d_00655284)),ADDR(0x66c602, ((u8 *)&g.d_0066c602)));
  rect_pack_to_short(ADDR(0x655294, ((u8 *)&g.d_00655294)),ADDR(0x66c60a, ((u8 *)&g.d_0066c60a)));
  for (local_8 = 0; local_8 < 8; local_8++) {
    rect_pack_to_short((iptr)(&map_view_saved_rects + local_8 * 0x10),local_8 * 8 + ADDR(0x66c612, ((u8 *)&g.d_0066c60a + 8)));
  }
  rect_pack_to_short(ADDR(0x655324, ((u8 *)&g.d_00655324)),ADDR(0x66c652, ((u8 *)&g.d_0066c652)));
  rect_pack_to_short(ADDR(0x655334, ((u8 *)&g.d_00655334)),ADDR(0x66c65a, ((u8 *)&g.d_0066c65a)));
  rect_pack_to_short(ADDR(0x655344, ((u8 *)&g.d_00655344)),ADDR(0x66c662, ((u8 *)&g.d_0066c662)));
  return;
}
#undef save_layout_record
#undef saved_layout_valid
#undef local_8

/* 00473064 auto */
#define save_layout_record (*(short *)((u8 *)&g.d_0066c600))
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl save_unpack_layout_rects(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  saved_layout_valid = (int)save_layout_record;
  rect_unpack_from_short(ADDR(0x66c602, ((u8 *)&g.d_0066c602)),ADDR(0x655284, ((u8 *)&g.d_00655284)));
  rect_unpack_from_short(ADDR(0x66c60a, ((u8 *)&g.d_0066c60a)),ADDR(0x655294, ((u8 *)&g.d_00655294)));
  for (local_8 = 0; local_8 < 8; local_8++) {
    rect_unpack_from_short(local_8 * 8 + ADDR(0x66c612, ((u8 *)&g.d_0066c60a + 8)),(iptr)(&map_view_saved_rects + local_8 * 0x10));
  }
  rect_unpack_from_short(ADDR(0x66c652, ((u8 *)&g.d_0066c652)),ADDR(0x655324, ((u8 *)&g.d_00655324)));
  rect_unpack_from_short(ADDR(0x66c65a, ((u8 *)&g.d_0066c65a)),ADDR(0x655334, ((u8 *)&g.d_00655334)));
  rect_unpack_from_short(ADDR(0x66c662, ((u8 *)&g.d_0066c662)),ADDR(0x655344, ((u8 *)&g.d_00655344)));
  return;
}
#undef save_layout_record
#undef saved_layout_valid
#undef local_8

/* 004732a6 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl save_read_units_cities(int param_1,iptr param_2)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 < 0x2a) {
    if (param_1 == 0x29) {
      for (unit = 0; unit < game.num_units; unit++) {
        sVar1 = _fread(units + unit,0x1e,1,(FILE *)param_2);
        if (sVar1 == 0) {
          return 0;
        }
      }
      if ((game.num_cities != 0) &&
         (sVar1 = _fread(cities,game.num_cities * 0x58,1,(FILE *)param_2), sVar1 == 0)) {
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
        sVar1 = _fread(units + unit,0x1a,1,(FILE *)param_2);
        if (sVar1 == 0) {
          return 0;
        }
      }
      for (unit = 0; unit < game.num_cities; unit++) {
        sVar1 = _fread(cities + unit,0x54,1,(FILE *)param_2);
        if (sVar1 == 0) {
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
       (sVar1 = _fread(units,(int)game.num_units << 5,1,(FILE *)param_2), sVar1 == 0)) {
      return 0;
    }
    if ((game.num_cities != 0) &&
       (sVar1 = _fread(cities,game.num_cities * 0x58,1,(FILE *)param_2), sVar1 == 0)) {
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
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(8)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i8 (*)[4])(frame_ + FRAME_OFF(16)))
i32 __cdecl save_load_gpk(int param_1,iptr param_2)

{
  size_t sVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 < 0x28) {
    if ((param_1 != 0x26) && (param_1 != 0x27)) {
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
    sVar1 = _fread(&game,0x36,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    sVar1 = _fread(game.first_discoverer,0x5d,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    sVar1 = _fread(game.advance_known_by,0x5d,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    sVar1 = _fread(game.wonder_city,0x4c,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    iVar2 = bits_count8((uint)game.civs_alive);
    local_14 = iVar2 - 1;
    if ((game.civs_alive & 1) != 0) {
      local_14 = iVar2 - 2;
    }
    if (game.num_enemies != local_14) {
      dbg_logf_int2(ADDR(0x62b9ec, ((u8 *)&g.d_0062b9ec)),(uint)game.num_enemies,(uint)game.civs_alive);
      game.num_enemies = (u8)local_14;
    }
    sVar1 = _fread(civ_names,0x790,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    for (civ = 0; civ < 8; civ++) {
      sVar1 = _fread(civs + civ,0x58,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(civs[civ].advances,0xc,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(&civs[civ].num_military_units,0xe,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(civs[civ].advance_source,0x5d,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(civs[civ].units_active,0x36,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(civs[civ].units_lost,0x36,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(civs[civ].units_in_production,0x36,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(local_8,1,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
      sVar1 = _fread(civs[civ].continent_military,0x402,1,(FILE *)param_2);
      if (sVar1 == 0) {
        return 0;
      }
    }
  }
  else {
    sVar1 = _fread(&game,0x14a,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    iVar2 = bits_count8((uint)game.civs_alive);
    local_14 = iVar2 - 1;
    if ((game.civs_alive & 1) != 0) {
      local_14 = iVar2 - 2;
    }
    if (game.num_enemies != local_14) {
      dbg_logf_int2(ADDR(0x62b9a0, ((u8 *)&g.d_0062b9a0)),(uint)game.num_enemies,(uint)game.civs_alive);
      game.num_enemies = (u8)local_14;
    }
    sVar1 = _fread(civ_names,0x790,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
    sVar1 = _fread(civs,0x2ca0,1,(FILE *)param_2);
    if (sVar1 == 0) {
      return 0;
    }
  }
  return 1;
}
#undef local_14
#undef civ
#undef civ2
#undef local_8

/* 00473c12 auto */
i32 __cdecl save_write_str(char *param_1,iptr param_2)

{
  int iVar1;
  i32 uVar2;
  
  iVar1 = _fputs(param_1,(FILE *)param_2);
  if (iVar1 == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = _fputc(0,(FILE *)param_2);
    if (iVar1 == -1) {
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

/* 00473c68 auto */
#define local_114 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_110 (*(char (*)[260])(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(268)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(272)))
/* WARNING: Unable to use type for symbol iVar2 */

int __cdecl save_read_event_str(iptr param_1)

{
  char *pcVar1;
  int iVar3;
  size_t sVar4;
  int iVar2;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_114 = 0;
  do {
    local_c = _fgetc((FILE *)param_1);
    iVar3 = local_c;
    if (local_c == -1) {
      return 0;
    }
    if (0xfe < local_114) break;
    iVar2 = local_114 + 1;
    local_110[local_114] = (char)local_c;
    local_c = iVar3;
    pcVar1 = local_110 + local_114;
    local_114 = iVar2;
  } while (*pcVar1 != '\0');
  local_110[local_114] = '\0';
  sVar4 = _strlen(local_110);
  local_8 = memblock_alloc(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
  if (local_8 == 0) {
    error_report(0xfffffff7,3,0,0,0);
    local_8 = 0;
  }
  else {
    FUN_005f22d0(local_8,local_110);
  }
  return local_8;
}
#undef local_114
#undef local_110
#undef local_c
#undef local_8

/* 00473d5e auto */
void __cdecl save_set_file_ext(int param_1)

{
  if (param_1 == 0) {
    if (game.multiplayer == '\0') {
      FUN_005f22d0(&save_file_path,&save_ext_sav_str);
    }
    else if (game.multiplayer == 1) {
      FUN_005f22d0(&save_file_path,&save_ext_hot_str);
    }
    else if (game.multiplayer == 2) {
      FUN_005f22d0(&save_file_path,&save_ext_eml_str);
    }
    else if ((((game.multiplayer == 3) || (game.multiplayer == 4)) ||
             (game.multiplayer == 5)) || (game.multiplayer == 6)) {
      FUN_005f22d0(&save_file_path,&save_ext_net_str);
    }
  }
  else {
    FUN_005f22d0(&save_file_path,&save_ext_scn_str);
  }
  return;
}

/* 00473e55 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl save_file_filter(int param_1,int param_2,int param_3)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      _memset(&save_file_filter_buf,0,0x104);
      local_8 = save_filter_add_entry((uint)game.multiplayer,ADDR(0x66c4f8, ((u8 *)&g.d_0066c4f8)));
      if (param_1 == 0) {
        if (game.multiplayer != '\0') {
          local_8 = save_filter_add_entry(0,local_8);
        }
        if (game.multiplayer < 3) {
          local_8 = save_filter_add_entry(3,local_8);
        }
        if (game.multiplayer != 1) {
          save_filter_add_entry(1,local_8);
        }
      }
    }
    else {
      _memset(&save_file_filter_buf,0,0x104);
      str_append_label(ADDR(0x66c4f8, ((u8 *)&g.d_0066c4f8)),0x105);
      FUN_005f22e0(&save_file_filter_buf,s____mp__0062ba74);
      sVar1 = _strlen(&save_file_filter_buf);
      FUN_005f22e0(sVar1 + ADDR(0x66c4f9, ((u8 *)&g.d_0066c4f8 + 1)),&save_filter_mp_pattern_str);
    }
  }
  else {
    _memset(&save_file_filter_buf,0,0x104);
    str_append_label(ADDR(0x66c4f8, ((u8 *)&g.d_0066c4f8)),0x19f);
    FUN_005f22e0(&save_file_filter_buf,s____scn__0062ba60);
    sVar1 = _strlen(&save_file_filter_buf);
    FUN_005f22e0(sVar1 + ADDR(0x66c4f9, ((u8 *)&g.d_0066c4f8 + 1)),s___scn_0062ba6c);
  }
  return &save_file_filter_buf;
}
#undef local_8

/* 00473ff2 auto */
char * __cdecl save_filter_add_entry(i32 param_1,iptr param_2)

{
  size_t sVar1;
  char *pcVar2;
  
  switch(param_1) {
  case 0:
    str_append_label(param_2,0xee);
    FUN_005f22e0(param_2,s____sav__0062ba84);
    sVar1 = _strlen((char *)param_2);
    pcVar2 = (char *)(param_2 + sVar1 + 1);
    FUN_005f22e0(pcVar2,s___sav_0062ba90);
    sVar1 = _strlen(pcVar2);
    pcVar2 = pcVar2 + sVar1 + 1;
    break;
  case 1:
    str_append_label(param_2,0x357);
    FUN_005f22e0(param_2,s____hot__0062ba98);
    sVar1 = _strlen((char *)param_2);
    pcVar2 = (char *)(param_2 + sVar1 + 1);
    FUN_005f22e0(pcVar2,s___hot_0062baa4);
    sVar1 = _strlen(pcVar2);
    pcVar2 = pcVar2 + sVar1 + 1;
    break;
  case 2:
    str_append_label(param_2,0x35a);
    FUN_005f22e0(param_2,s____eml__0062baac);
    sVar1 = _strlen((char *)param_2);
    pcVar2 = (char *)(param_2 + sVar1 + 1);
    FUN_005f22e0(pcVar2,s___eml_0062bab8);
    sVar1 = _strlen(pcVar2);
    pcVar2 = pcVar2 + sVar1 + 1;
    break;
  case 3:
  case 4:
  case 5:
  case 6:
    str_append_label(param_2,0x35d);
    FUN_005f22e0(param_2,s____net__0062bac0);
    sVar1 = _strlen((char *)param_2);
    pcVar2 = (char *)(param_2 + sVar1 + 1);
    FUN_005f22e0(pcVar2,s___net_0062bacc);
    sVar1 = _strlen(pcVar2);
    pcVar2 = pcVar2 + sVar1 + 1;
    break;
  default:
    pcVar2 = (char *)0x0;
  }
  return pcVar2;
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
#define local_130 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_12c (*(uint *)(frame_ + FRAME_OFF(4)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_124 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_120 (*(void * *)(frame_ + FRAME_OFF(16)))
#define local_11c (*(FILE * *)(frame_ + FRAME_OFF(20)))
#define local_118 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_114 (*(u8 *)(frame_ + FRAME_OFF(28)))
#define local_110 (*(i16 (*)[2])(frame_ + FRAME_OFF(32)))
#define leader (*(int *)(frame_ + FRAME_OFF(36)))
#define local_108 (*(char (*)[260])(frame_ + FRAME_OFF(40)))
i32 __cdecl save_write_game(iptr param_1,int param_2)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(304)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_118 = 1;
  if (game.multiplayer == 1) {
    local_114 = game.human_players;
    game.human_players = hotseat_human_players;
  }
  save_set_file_ext(param_2);
  FUN_005f22d0(local_108,param_1);
  pcVar1 = _strchr(local_108,0x2e);
  if (pcVar1 == (char *)0x0) {
    FUN_005f22e0(local_108,&save_file_path);
  }
  local_11c = _fopen(local_108,&save_write_mode);
  if (local_11c != (FILE *)0x0) {
    save_write_cstr_eof((iptr)PTR_s_CIVILIZE_0062b990,(iptr)local_11c);
    game.field_1c = (i8)human_civ;
    local_110[0] = 0x2c;
    sVar2 = _fwrite(local_110,2,1,local_11c);
    if (sVar2 != 0) {
      if (param_2 == 0) {
        game.game_flags = game.game_flags & 0xffbf;
      }
      else {
        game.game_flags = game.game_flags | 0x40;
        for (local_124 = 0; local_124 < 100; local_124++) {
          game.advance_known_by[local_124] = '\0';
          for (civ = 1; civ < 8; civ++) {
            iVar3 = civ_has_advance(civ,local_124);
            if (iVar3 != 0) {
              game.advance_known_by[local_124] =
                   game.advance_known_by[local_124] | (byte)(1 << ((byte)civ & 0x1f));
            }
          }
          if (game.advance_known_by[local_124] != '\0') {
            iVar3 = bits_count8((int)(char)game.advance_known_by[local_124]);
            if (iVar3 == 1) {
              for (civ = 1; civ < 8; civ++) {
                iVar3 = civ_has_advance(civ,local_124);
                if (iVar3 != 0) {
                  game.first_discoverer[local_124] = (byte)civ;
                }
              }
            }
            else {
              game.first_discoverer[local_124] = 8;
            }
          }
        }
        for (civ = 1; civ < 8; civ++) {
          civs[civ].flags = civs[civ].flags & 0xff96;
        }
      }
      if ((param_2 != 0) || ((game.game_flags & 0x80) != 0)) {
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
      sVar2 = _fwrite(&game,0x14a,1,local_11c);
      if (((((((sVar2 != 0) && (sVar2 = _fwrite(civ_names,0x790,1,local_11c), sVar2 != 0)) &&
             (sVar2 = _fwrite(civs,0x2ca0,1,local_11c), sVar2 != 0)) &&
            ((iVar3 = map_write((iptr)local_11c,0), iVar3 == 0 &&
             (sVar2 = _fwrite(map_coarse[0],(int)map.quarter_w * (int)map.quarter_h,1,local_11c),
             sVar2 != 0)))) &&
           (sVar2 = _fwrite(map_coarse[1],(int)map.quarter_w * (int)map.quarter_h,1,local_11c),
           sVar2 != 0)) &&
          ((sVar2 = _fwrite(&landmass_table,0x400,1,local_11c), sVar2 != 0 &&
           ((game.num_units == 0 ||
            (sVar2 = _fwrite(units,(int)game.num_units << 5,1,local_11c), sVar2 != 0)))))) &&
         ((game.num_cities == 0 ||
          (sVar2 = _fwrite(cities,game.num_cities * 0x58,1,local_11c), sVar2 != 0)))) {
        for (leader = 0; leader < 0x15; leader++) {
          sVar2 = _fwrite(&leaders[leader].times_used,1,1,local_11c);
          if (((sVar2 == 0) ||
              (sVar2 = _fwrite(&leaders[leader].city_name_index,1,1,local_11c), sVar2 == 0)) ||
             (sVar2 = _fwrite(&leaders[leader].female,1,1,local_11c), sVar2 == 0))
          goto LAB_0047530a;
        }
        sVar2 = _fwrite(&map_cursor_x,2,1,local_11c);
        if ((sVar2 != 0) && (sVar2 = _fwrite(&map_cursor_y,2,1,local_11c), sVar2 != 0)) {
          if (game.multiplayer == '\0') {
            sVar2 = _fwrite(leaders + civs[game.player_civ].tribe,0x30,1,local_11c);
            if (sVar2 == 0) goto LAB_0047530a;
          }
          else {
            civ = (iptr)game.player_civ;
            for (leader = 0; leader < 8; leader++) {
              if ((1 << ((byte)leader & 0x1f) & (uint)game.human_players) != 0) {
                game.player_civ = (byte)leader;
                sVar2 = _fwrite(leaders + civs[(char)(byte)leader].tribe,0x30,1,local_11c);
                if (sVar2 == 0) {
                  game.player_civ = (byte)civ;
                  goto LAB_0047530a;
                }
              }
            }
            game.player_civ = (byte)civ;
          }
          sVar2 = _fwrite(&power_graph_history,0x4b0,1,local_11c);
          if (sVar2 != 0) {
            saved_screen_rect = screen_rect;
            saved_screen_rect_top = screen_rect_top;
            saved_screen_rect_right = ui_screen_rect_right;
            saved_screen_rect_bottom = ui_screen_rect_bottom;
            save_pack_layout_rects();
            sVar2 = _fwrite(&save_layout_record,0x6a,1,local_11c);
            if (sVar2 != 0) {
              for (leader = 0; leader < 8; leader++) {
                sVar2 = _fwrite(&map_view_open_flags + leader * 0x3f0,2,1,local_11c);
                if (((sVar2 == 0) ||
                    (sVar2 = _fwrite(&mapview_track_moves + leader * 0x3f0,2,1,local_11c), sVar2 == 0))
                   || ((sVar2 = _fwrite(&map_view_center_x + leader * 0x1f8,2,1,local_11c), sVar2 == 0
                       || ((sVar2 = _fwrite(&mapview_center_y + leader * 0x1f8,2,1,local_11c),
                           sVar2 == 0 ||
                           (sVar2 = _fwrite(&mapview_zoom + leader * 0x1f8,2,1,local_11c),
                           sVar2 == 0)))))) goto LAB_0047530a;
              }
              if ((((param_2 == 0) && ((game.game_flags & 0x80) == 0)) ||
                  (sVar2 = _fwrite(&scenario_flags,100,1,local_11c), sVar2 != 0)) &&
                 (sVar2 = _fwrite(&destroyed_civ_count,0x152,1,local_11c), sVar2 != 0)) {
                if (game.multiplayer != '\0') {
                  local_12c = (uint)saved_turn_civ;
                  saved_turn_civ = mp_turn_civ;
                  sVar2 = _fwrite(&civ_saved_cursor_x,0x494,1,local_11c);
                  if (sVar2 == 0) goto LAB_0047530a;
                  saved_turn_civ = (byte)local_12c;
                }
                if ((scenario_events_loaded != 0) && (param_2 == 0)) {
                  iVar3 = _fputs(&save_events_tag_str,local_11c);
                  if (iVar3 == -1) goto LAB_0047530a;
                  local_130 = 0;
                  for (local_120 = (void *)events_list_head; local_120 != (void *)0x0;
                      local_120 = *(void **)((int)local_120 + 0x1bc)) {
                    local_130++;
                  }
                  sVar2 = _fwrite(&local_130,4,1,local_11c);
                  if (sVar2 == 0) goto LAB_0047530a;
                  for (local_120 = (void *)events_list_head; local_120 != (void *)0x0;
                      local_120 = *(void **)((int)local_120 + 0x1bc)) {
                    sVar2 = _fwrite(local_120,0x1bc,1,local_11c);
                    if (sVar2 == 0) goto LAB_0047530a;
                  }
                  for (local_120 = (void *)events_list_head; local_120 != (void *)0x0;
                      local_120 = *(void **)((int)local_120 + 0x1bc)) {
                    if (((((*(int *)((int)local_120 + 8) != 0) &&
                          (iVar3 = save_write_str(*(i32 *)((int)local_120 + 8),
                                                      (iptr)local_11c), iVar3 == -1)) ||
                         ((*(int *)((int)local_120 + 0x10) != 0 &&
                          (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x10),
                                                      (iptr)local_11c), iVar3 == -1)))) ||
                        ((*(int *)((int)local_120 + 0x14) != 0 &&
                         (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x14),
                                                     (iptr)local_11c), iVar3 == -1)))) ||
                       ((*(int *)((int)local_120 + 0x20) != 0 &&
                        (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x20),
                                                    (iptr)local_11c), iVar3 == -1))))
                    goto LAB_0047530a;
                    local_130 = 0;
                    while ((local_130 < 0x14 &&
                           (*(int *)((int)local_120 + local_130 * 4 + 0x38) != 0))) {
                      iVar3 = save_write_str(*(i32 *)
                                                  ((int)local_120 + local_130 * 4 + 0x38),
                                                 (iptr)local_11c);
                      if (iVar3 == -1) goto LAB_0047530a;
                      local_130++;
                    }
                    if ((((((*(int *)((int)local_120 + 0x88) != 0) &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x88),
                                                       (iptr)local_11c), iVar3 == -1)) ||
                          ((*(int *)((int)local_120 + 0x90) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x90),
                                                       (iptr)local_11c), iVar3 == -1)))) ||
                         (((*(int *)((int)local_120 + 0xc4) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0xc4),
                                                       (iptr)local_11c), iVar3 == -1)) ||
                          ((*(int *)((int)local_120 + 0xcc) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0xcc),
                                                       (iptr)local_11c), iVar3 == -1)))))) ||
                        ((((*(int *)((int)local_120 + 0xd4) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0xd4),
                                                       (iptr)local_11c), iVar3 == -1)) ||
                          ((*(int *)((int)local_120 + 0xdc) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0xdc),
                                                       (iptr)local_11c), iVar3 == -1)))) ||
                         (((*(int *)((int)local_120 + 0x13c) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x13c),
                                                       (iptr)local_11c), iVar3 == -1)) ||
                          ((*(int *)((int)local_120 + 0x140) != 0 &&
                           (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x140),
                                                       (iptr)local_11c), iVar3 == -1)))))))) ||
                       ((((*(int *)((int)local_120 + 0x148) != 0 &&
                          (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x148),
                                                      (iptr)local_11c), iVar3 == -1)) ||
                         ((*(int *)((int)local_120 + 0x174) != 0 &&
                          (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x174),
                                                      (iptr)local_11c), iVar3 == -1)))) ||
                        ((*(int *)((int)local_120 + 0x184) != 0 &&
                         (iVar3 = save_write_str(*(i32 *)((int)local_120 + 0x184),
                                                     (iptr)local_11c), iVar3 == -1))))))
                    goto LAB_0047530a;
                  }
                }
                local_118 = 0;
              }
            }
          }
        }
      }
    }
  }
LAB_0047530a:
  if (game.multiplayer == 1) {
    game.human_players = local_114;
  }
  if (local_11c != (FILE *)0x0) {
    _fclose(local_11c);
  }
  return local_118;
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
#undef local_130
#undef local_12c
#undef civ
#undef local_124
#undef local_120
#undef local_11c
#undef local_118
#undef local_114
#undef local_110
#undef leader
#undef local_108

/* 00475666: written by hand in src/game/retvals.c */

/* 0047758c auto */
#define game_setup_complete (*(int *)((u8 *)&g.d_00654fd8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define text_buffer (*(char *)((u8 *)&g.d_00679640))
#define local_254 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_250 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_24c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_248 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_240 (*(_SYSTEMTIME *)(frame_ + FRAME_OFF(24)))
#define local_230 (*(char (*)[31])(frame_ + FRAME_OFF(40)))
#define acStack_211 (*(char (*)[261])(frame_ + FRAME_OFF(71)))
#define local_10c (*(char *)(frame_ + FRAME_OFF(332)))
#define acStack_10b (*(char (*)[259])(frame_ + FRAME_OFF(333)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(592)))
void __cdecl game_save_dialog(int param_1)

{
  uptr sVar1;
  uptr sVar2;
  i32 uVar1;
  size_t sVar3;
  iptr iVar4;
  int iVar5;
  char *pcVar6;
  i8 *puVar7;
  i8 *puVar8;
  i32 uVar9;
  i8 frame_[FRAME_OFF(600)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game_setup_complete != 0) {
    mp_turn_timer_stop(1);
    do {
      save_set_file_ext(param_1);
      str_clear((iptr)&local_10c);
      str_append_label((iptr)&local_10c,(-(uint)(param_1 == 0) & 0xffffff4f) + 0x19f);
      str_append_space((iptr)&local_10c);
      str_append_lparen((iptr)&local_10c);
      str_append((iptr)&local_10c,ADDR(0x62bb08, ((u8 *)&g.d_0062bb08)));
      str_append((iptr)&local_10c,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
      str_append_rparen((iptr)&local_10c);
      sVar1 = _strlen(&local_10c);
      local_8 = acStack_10b + sVar1;
      str_clear((iptr)local_8);
      str_append((iptr)local_8,ADDR(0x62bb0c, ((u8 *)&g.d_0062bb0c)));
      str_append((iptr)local_8,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
      sVar2 = _strlen(local_8);
      local_8 = local_8 + sVar2 + 1;
      str_clear((iptr)local_8);
      str_clear((iptr)(acStack_211 + 1));
      uVar1 = civ_leader_name(human_civ);
      FUN_005f22e0(acStack_211 + 1,uVar1);
      acStack_211[3] = 0;
      str_append((iptr)(acStack_211 + 1),ADDR(0x62bb10, ((u8 *)&g.d_0062bb10)));
      local_8 = acStack_211;
      while (local_8 = local_8 + 1, *local_8 != '\0') {
        if ((31 < *local_8) && (*local_8 < 'A')) {
          *local_8 = '_';
        }
      }
      text_clear();
      if (game.year < 0) {
        text_append(ADDR(0x62bb18, ((u8 *)&g.d_0062bb18)));
      }
      else {
        text_append(ADDR(0x62bb14, ((u8 *)&g.d_0062bb14)));
      }
      str_append_space((iptr)(acStack_211 + 1));
      sVar3 = _strlen(acStack_211 + 1);
      acStack_211[sVar3] = text_buffer;
      if (game.year < 1) {
        local_248 = ~(int)game.year + 1;
      }
      else {
        local_248 = (int)game.year;
      }
      str_append_int((iptr)(acStack_211 + 1),local_248);
      if ((game.multiplayer == 2) && (param_1 == 0)) {
        GetLocalTime(&local_240);
        FUN_005f22e0(acStack_211 + 1,&save_name_date_sep_str);
        __itoa((uint)(*(i32 *)((char *)&local_240 + 0)) >> 0x10,local_230,10);
        FUN_005f22e0(acStack_211 + 1,local_230);
        FUN_005f22e0(acStack_211 + 1,&save_name_month_day_sep_str);
        __itoa((uint)local_240.wDay,local_230,10);
        FUN_005f22e0(acStack_211 + 1,local_230);
        FUN_005f22e0(acStack_211 + 1,&save_name_day_year_sep_str);
        __itoa((*(i32 *)((char *)&local_240 + 0)) & 0xffff,local_230,10);
        FUN_005f22e0(acStack_211 + 1,local_230);
        FUN_005f22e0(acStack_211 + 1,&save_name_time_sep_str);
        __itoa((*(i32 *)((char *)&local_240 + 8)) & 0xffff,local_230,10);
        FUN_005f22e0(acStack_211 + 1,local_230);
        FUN_005f22e0(acStack_211 + 1,&save_name_hour_min_sep_str);
        __itoa((uint)(*(i32 *)((char *)&local_240 + 8)) >> 0x10,local_230,10);
        FUN_005f22e0(acStack_211 + 1,local_230);
        FUN_005f22e0(acStack_211 + 1,&save_name_min_sec_sep_str);
        __itoa((*(i32 *)((char *)&local_240 + 12)) & 0xffff,local_230,10);
        FUN_005f22e0(acStack_211 + 1,local_230);
      }
      FUN_005f22e0(acStack_211 + 1,&save_name_ext_dot_str);
      FUN_005f22e0(acStack_211 + 1,&save_file_ext_bare);
      __strlwr(acStack_211 + 1);
      if (((param_1 != 0) || ((game.game_flags & 0x80) != 0)) && (scenario_year_increment < 0)) {
        str_clear((iptr)(acStack_211 + 1));
        if ((int)game.year / 0xc < 1) {
          local_24c = ~((int)game.year / 0xc) + 1;
        }
        else {
          local_24c = (int)game.year / 0xc;
        }
        str_append_int((iptr)(acStack_211 + 1),local_24c);
        if (game.year < 0) {
          if ((int)game.year % 0xc < 1) {
            local_254 = ~((int)game.year % 0xc) + 1;
          }
          else {
            local_254 = (int)game.year % 0xc;
          }
          str_append_label((iptr)(acStack_211 + 1),0x1af - local_254);
        }
        else {
          if ((int)game.year % 0xc < 1) {
            local_250 = ~((int)game.year % 0xc) + 1;
          }
          else {
            local_250 = (int)game.year % 0xc;
          }
          str_append_label((iptr)(acStack_211 + 1),local_250 + 0x1a4);
        }
        FUN_005f22e0(acStack_211 + 1,&save_file_path);
        __strlwr(acStack_211 + 1);
      }
      __chdir(&scenario_dir_path);
      save_file_filter(1,param_1,0);
      uVar9 = 1;
      uVar1 = 0;
      puVar8 = &save_file_ext_bare;
      puVar7 = &save_file_filter_buf;
      pcVar6 = acStack_211 + 1;
      iVar4 = label_string(*(i32 *)
                                  (label_string_ids + 0x680 + (-(uint)(param_1 == 0) & 0xffffff4f) * 4)
                                );
      iVar5 = ui_file_name_dialog(ADDR(0x6553d8, ((u8 *)&g.d_006553d8)),iVar4,(iptr)pcVar6,(iptr)puVar7,(iptr)puVar8,uVar1,uVar9);
      if (iVar5 != 0) {
        __chdir(&game_home_dir);
        iVar5 = save_write_game((iptr)(acStack_211 + 1),param_1);
        if (iVar5 == 0) {
          if (param_1 == 0) {
            if (game.multiplayer == 2) {
              text_set_string_arg(0,(iptr)(acStack_211 + 1));
              popup_game(ADDR(0x62bb4c, ((u8 *)&g.d_0062bb4c)));
            }
            else {
              iVar4 = civ_leader_title(human_civ);
              text_set_string_arg(0,iVar4);
              iVar4 = civ_leader_name(human_civ);
              text_set_string_arg(1,iVar4);
              iVar4 = civ_name_plural(human_civ);
              text_set_string_arg(2,iVar4);
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
#undef local_254
#undef local_250
#undef local_24c
#undef local_248
#undef local_240
#undef local_230
#undef acStack_211
#undef local_10c
#undef acStack_10b
#undef local_8

/* 00477d8c auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define loaded_file_kind (*(i16 *)((u8 *)&g.d_006ad6ac))
#define net_host_flag (*(i8 *)((u8 *)&g.d_006ad2f7))
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_ac4 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_abc (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_ab4 (*(_WIN32_FIND_DATAA *)(frame_ + FRAME_OFF(20)))
#define local_974 (*(CHAR (*)[260])(frame_ + FRAME_OFF(340)))
#define local_870 (*(int *)(frame_ + FRAME_OFF(600)))
#define local_86c (*(char * *)(frame_ + FRAME_OFF(604)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(608)))
#define local_864 (*(i8 (*)[260])(frame_ + FRAME_OFF(612)))
#define local_760 (*(int *)(frame_ + FRAME_OFF(872)))
#define local_75c (*(char *)(frame_ + FRAME_OFF(876)))
#define acStack_75b (*(char (*)[259])(frame_ + FRAME_OFF(877)))
#define local_658 (*(GamePalette *)(frame_ + FRAME_OFF(1136)))
#define local_224 (*(i8 (*)[260])(frame_ + FRAME_OFF(2212)))
#define local_120 (*(char * *)(frame_ + FRAME_OFF(2472)))
#define local_11c (*(int *)(frame_ + FRAME_OFF(2476)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(2480)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(2740)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2744)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2748)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2752)))
int __cdecl game_load_dialog(int param_1,i32 param_2,int param_3)

{
  size_t sVar1;
  iptr iVar2;
  int iVar3;
  char *pcVar4;
  HANDLE pvVar5;
  BOOL BVar6;
  i8 *puVar7;
  i8 *puVar8;
  i8 *puVar9;
  i32 uVar10;
  i32 uVar11;
  i8 frame_[FRAME_OFF(2760)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_760 = 1;
  palette_init(&local_658);
  local_8 = 0;
  if (param_1 == 0) {
    save_set_file_ext(0);
    loaded_file_kind = 1;
  }
  else {
    save_set_file_ext(1);
    loaded_file_kind = 2;
  }
  str_clear((iptr)&local_75c);
  str_append_label((iptr)&local_75c,(-(uint)(param_1 == 0) & 0xffffff4f) + 0x19f);
  str_append_space((iptr)&local_75c);
  str_append_lparen((iptr)&local_75c);
  str_append((iptr)&local_75c,ADDR(0x62bb60, ((u8 *)&g.d_0062bb60)));
  str_append((iptr)&local_75c,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
  str_append_rparen((iptr)&local_75c);
  sVar1 = _strlen(&local_75c);
  local_120 = acStack_75b + sVar1;
  str_clear((iptr)local_120);
  str_append((iptr)local_120,ADDR(0x62bb64, ((u8 *)&g.d_0062bb64)));
  str_append((iptr)local_120,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
  sVar1 = _strlen(local_120);
  local_120 = local_120 + sVar1 + 1;
  str_clear((iptr)local_120);
  FUN_005f22d0(local_864,&load_dialog_wildcard_str);
  FUN_005f22e0(local_864,&save_file_ext_bare);
  __chdir(&scenario_dir_path);
  save_file_filter(0,param_1,0);
  uVar11 = 0;
  uVar10 = 1;
  puVar9 = &save_file_ext_bare;
  puVar8 = &save_file_filter_buf;
  puVar7 = local_864;
  iVar2 = label_string(*(i32 *)
                              (label_string_ids + 0x684 + (-(uint)(param_1 == 0) & 0xffffff4f) * 4));
  iVar3 = ui_file_name_dialog(ADDR(0x6553d8, ((u8 *)&g.d_006553d8)),iVar2,(iptr)puVar7,(iptr)puVar8,(iptr)puVar9,uVar10,uVar11);
  if (iVar3 == 0) {
    __chdir(&game_home_dir);
  }
  else {
    __chdir(&game_home_dir);
    for (local_11c = 1; local_11c < 8; local_11c++) {
      if (*(short *)(&map_view_open_flags + local_11c * 0x3f0) != 0) {
        *(i16 *)(&map_view_open_flags + local_11c * 0x3f0) = 0;
        wnd_destroy_with_surface((DibSurface *)(&map_views + local_11c * 0x3f0));
      }
    }
    FUN_005f22d0(local_118,local_864);
    __strupr(local_118);
    pcVar4 = _strstr(local_118,&game_load_scn_ext_str);
    if (pcVar4 != (char *)0x0) {
      FUN_005f22d0(local_118,local_864);
      local_86c = _strrchr(local_118,0x5c);
      local_86c++;
      *local_86c = '\0';
      FUN_005f22d0(local_974,local_118);
      FUN_005f22e0(local_974,s___ALT_0062bb74);
      local_870 = 0;
      pvVar5 = FindFirstFileA(local_974,&local_ab4);
      if (pvVar5 != (HANDLE)0xffffffff) {
        do {
          local_870++;
          BVar6 = FindNextFileA(pvVar5,&local_ab4);
        } while (BVar6 == 1);
      }
      if (local_870 != 0) {
        iVar3 = _rand();
        local_abc = (uint)(iVar3 * (local_870 + 1)) >> 0xf;
        if (local_abc != 0) {
          pvVar5 = FindFirstFileA(local_974,&local_ab4);
          while (local_abc = local_abc - 1, local_abc != 0) {
            FindNextFileA(pvVar5,&local_ab4);
          }
          FUN_005f22e0(local_118,local_ab4.cFileName);
          FUN_005f22d0(local_864,local_118);
        }
      }
    }
    snd_play_effect(-0x6b,0,0,0);
    snd_play_effect(-0x6c,0,0,0);
    snd_play_effect(0x6a,0,0,0);
    local_14 = save_read_game((iptr)local_864);
    if (local_14 == 0) {
      ui_flush_input();
      if ((scenario_events_loaded == 0) && ((game.game_flags & 0x80) != 0)) {
        scenario_events_loaded = 0;
        __chdir(&scenario_dir_path);
        FUN_005f22d0(local_224,s_EVENTS__0062bbac);
        FUN_005f22e0(local_224,&lang_file_ext);
        iVar3 = file_exists((iptr)local_224);
        if (iVar3 != 0) {
          FUN_005f22d0(local_224,&text_buffer);
          events_reset((ScenarioEvents *)&scenario_events,50000);
          iVar3 = events_parse_file
                            ((ScenarioEvents *)&scenario_events,ADDR(0x62bbc0, ((u8 *)&g.d_0062bbc0)),ADDR(0x62bbb4, ((u8 *)&g.d_0062bbb4)));
          if (iVar3 == 0) {
            events_compact();
            scenario_events_loaded = 1;
          }
          FUN_005f22d0(&text_buffer,local_224);
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
      if (param_3 != 0) {
        ui_flush_input();
        iVar3 = file_exists(ADDR(0x62bbc8, ((u8 *)&g.d_0062bbc8)));
        if ((iVar3 != 0) &&
           (iVar3 = surface_load_gif_file
                              ((DibSurface *)&scenario_title_surface,ADDR(0x62bbd4, ((u8 *)&g.d_0062bbd4)),10,0xc0,(iptr)&local_658),
           iVar3 != 0)) {
          wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x66c670, ((u8 *)&g.d_0066c670)));
          wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
          wnd_maximize((WndBase *)&main_frame_wnd);
          wnd_flush_paint();
          input_flush_events();
        }
      }
      __chdir(&game_home_dir);
      local_760 = 0;
      iVar2 = civ_leader_title(human_civ);
      text_set_string_arg(0,iVar2);
      iVar2 = civ_leader_name(human_civ);
      text_set_string_arg(1,iVar2);
      iVar2 = civ_name_plural(human_civ);
      text_set_string_arg(2,iVar2);
      text_clear();
      text_append_year((int)game.year);
      text_set_string_arg(3,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      text_set_label_arg(4,difficulty_names[game.difficulty]);
      if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
        local_ac4 = 0;
      }
      else {
        local_ac4 = 1;
      }
      menu_set_item_checked((GameMenu *)&main_menu,0x701,local_ac4);
      if ((param_1 == 0) && (game.multiplayer == '\0')) {
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
      text_append((iptr)local_864);
    }
    else {
      switch(local_14) {
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
  iVar3 = local_760;
  if (local_760 != 0) {
    loaded_file_kind = 0;
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004786f8 */ { palette_destroy((GamePalette *)((iptr)&local_658)); }
  return iVar3;
}
#undef human_civ
#undef loaded_file_kind
#undef net_host_flag
#undef prefs_game_options
#undef scenario_events_loaded
#undef text_buffer
#undef local_ac4
#undef local_abc
#undef local_ab4
#undef local_974
#undef local_870
#undef local_86c
#undef unit
#undef local_864
#undef local_760
#undef local_75c
#undef acStack_75b
#undef local_658
#undef local_224
#undef local_120
#undef local_11c
#undef local_118
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0048237d auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define _DAT_006cec80 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl turn_popup_timeout_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  iVar1 = timer_ticks();
  if (0x4b0 < iVar1 - _DAT_006cec80) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((C_00408010_b8 *)(*dialog_stack_top + 0x48));
    _DAT_006cec80 = timer_ticks();
  }
  return;
}
#undef dialog_stack_top
#undef _DAT_006cec80

/* 0048308f auto */
#define events_pool_base (*(char * *)((u8 *)&g.d_0064b98c))
#define scenario_event_count (*(int *)((u8 *)&g.d_0064b998))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define local_54 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(char * *)(frame_ + FRAME_OFF(72)))
#define local_c (*(int *)(frame_ + FRAME_OFF(76)))
void __cdecl events_relink_pool(void)

{
  int iVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = scenario_event_count;
  if (scenario_events_loaded != 0) {
    events_list_head = (iptr)events_pool_base;
    local_10 = events_pool_base;
    local_14 = events_pool_base + scenario_event_count * 0x1c4;
    if ((local_14 <= events_pool_base) || (events_pool_base + events_pool_size <= local_14)) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62c2c4, ((u8 *)&g.d_0062c2c4)),ADDR(0x62c2a0, ((u8 *)&g.d_0062c2a0)),0x913);
    }
    for (local_c = 0; local_c < iVar1; local_c++) {
      local_10[0x1bc] = '\0';
      local_10[0x1bd] = '\0';
      local_10[0x1be] = '\0';
      local_10[0x1bf] = '\0';
      local_10[0x1c0] = '\0';
      local_10[0x1c1] = '\0';
      local_10[0x1c2] = '\0';
      local_10[0x1c3] = '\0';
      if (0 < local_c) {
        *(char **)(local_10 + 0x1c0) = local_10;
        *(int *)(local_10 + 0x1c0) = *(int *)(local_10 + 0x1c0) - 0x1c4;
        *(char **)(*(int *)(local_10 + 0x1c0) + 0x1bc) = local_10;
      }
      local_10 += 0x1c4;
    }
    for (local_10 = (char *)events_list_head; local_10 != (char *)0x0;
        local_10 = *(char **)((int)local_10 + 0x1bc)) {
      if (*(int *)((int)local_10 + 8) != 0) {
        *(char **)((int)local_10 + 8) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x10) {
          local_18 = 0xf;
        }
        else {
          sVar2 = _strlen(local_14);
          local_18 = sVar2 + 1;
        }
        local_14 += local_18;
      }
      if (*(int *)((int)local_10 + 0x10) != 0) {
        *(char **)((int)local_10 + 0x10) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_1c = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_1c = sVar2 + 1;
        }
        local_14 += local_1c;
      }
      if (*(int *)((int)local_10 + 0x14) != 0) {
        *(char **)((int)local_10 + 0x14) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_20 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_20 = sVar2 + 1;
        }
        local_14 += local_20;
      }
      if (*(int *)((int)local_10 + 0x20) != 0) {
        *(char **)((int)local_10 + 0x20) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_24 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_24 = sVar2 + 1;
        }
        local_14 += local_24;
      }
      for (local_c = 0; local_c < 0x14; local_c++) {
        if (*(int *)((int)local_10 + 0x38 + local_c * 4) != 0) {
          *(char **)((int)local_10 + 0x38 + local_c * 4) = local_14;
          sVar2 = _strlen(local_14);
          if (sVar2 + 1 < 2) {
            local_28 = 1;
          }
          else {
            sVar2 = _strlen(local_14);
            local_28 = sVar2 + 1;
          }
          local_14 += local_28;
        }
      }
      if (*(int *)((int)local_10 + 0x88) != 0) {
        *(char **)((int)local_10 + 0x88) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_2c = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_2c = sVar2 + 1;
        }
        local_14 += local_2c;
      }
      if (*(int *)((int)local_10 + 0x90) != 0) {
        *(char **)((int)local_10 + 0x90) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x10) {
          local_30 = 0xf;
        }
        else {
          sVar2 = _strlen(local_14);
          local_30 = sVar2 + 1;
        }
        local_14 += local_30;
      }
      if (*(int *)((int)local_10 + 0xc4) != 0) {
        *(char **)((int)local_10 + 0xc4) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_34 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_34 = sVar2 + 1;
        }
        local_14 += local_34;
      }
      if (*(int *)((int)local_10 + 0xcc) != 0) {
        *(char **)((int)local_10 + 0xcc) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_38 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_38 = sVar2 + 1;
        }
        local_14 += local_38;
      }
      if (*(int *)((int)local_10 + 0xd4) != 0) {
        *(char **)((int)local_10 + 0xd4) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_3c = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_3c = sVar2 + 1;
        }
        local_14 += local_3c;
      }
      if (*(int *)((int)local_10 + 0xdc) != 0) {
        *(char **)((int)local_10 + 0xdc) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x10) {
          local_40 = 0xf;
        }
        else {
          sVar2 = _strlen(local_14);
          local_40 = sVar2 + 1;
        }
        local_14 += local_40;
      }
      if (*(int *)((int)local_10 + 0x13c) != 0) {
        *(char **)((int)local_10 + 0x13c) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_44 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_44 = sVar2 + 1;
        }
        local_14 += local_44;
      }
      if (*(int *)((int)local_10 + 0x140) != 0) {
        *(char **)((int)local_10 + 0x140) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_48 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_48 = sVar2 + 1;
        }
        local_14 += local_48;
      }
      if (*(int *)((int)local_10 + 0x148) != 0) {
        *(char **)((int)local_10 + 0x148) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x10) {
          local_4c = 0xf;
        }
        else {
          sVar2 = _strlen(local_14);
          local_4c = sVar2 + 1;
        }
        local_14 += local_4c;
      }
      if (*(int *)((int)local_10 + 0x174) != 0) {
        *(char **)((int)local_10 + 0x174) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 0x19) {
          local_50 = 0x18;
        }
        else {
          sVar2 = _strlen(local_14);
          local_50 = sVar2 + 1;
        }
        local_14 += local_50;
      }
      if (*(int *)((int)local_10 + 0x184) != 0) {
        *(char **)((int)local_10 + 0x184) = local_14;
        sVar2 = _strlen(local_14);
        if (sVar2 + 1 < 2) {
          local_54 = 1;
        }
        else {
          sVar2 = _strlen(local_14);
          local_54 = sVar2 + 1;
        }
        local_14 += local_54;
      }
    }
  }
  return;
}
#undef events_pool_base
#undef scenario_event_count
#undef scenario_events_loaded
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
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 00484cc0 auto */
#define scenario_flags (*(i16 *)((u8 *)&g.d_0064bc60))
#define scenario_max_turns (*(i16 *)((u8 *)&g.d_0064bcb8))
#define scenario_name (*(i8 *)((u8 *)&g.d_0064bc62))
#define scenario_objective_civ (*(i16 *)((u8 *)&g.d_0064bcba))
#define scenario_start_year (*(i16 *)((u8 *)&g.d_0064bcb6))
#define scenario_tech_paradigm (*(i16 *)((u8 *)&g.d_0064bcb2))
#define scenario_victory_thresholds (*(i16 *)((u8 *)&g.d_0064bcbc))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
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
  for (local_8 = 0; local_8 < 4; local_8++) {
    (&scenario_victory_thresholds)[local_8] = 0;
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
#undef local_8

/* 00484d85 auto */
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define player_has_quit (*(i8 *)((u8 *)&g.d_006ad685))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define local_8 (*(u8 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl main_frame_on_close(void)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((game.multiplayer < 3) || (net_host_handoff_stage == '\0')) &&
     (iVar1 = popup_game_with_sprite(ADDR(0x62c5c4, ((u8 *)&g.d_0062c5c4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0), iVar1 != 0)) {
    if (game.multiplayer == '\0') {
      snd_cd_stop();
      map_display_disable();
    }
    else {
      if (game.multiplayer == 1) {
        local_8 = game.human_players;
        game.human_players = hotseat_human_players;
      }
      if (2 < game.multiplayer) {
        if (mp_turn_timer_handle != 0) {
          game_timer_destroy(mp_turn_timer_handle);
          mp_turn_timer_handle = 0;
        }
        parley_wnd_close();
        chat_wnd_close();
        iVar2 = civ_get_adjective(human_civ);
        text_set_string_arg(0,iVar2);
        iVar2 = civ_leader_title(human_civ);
        text_set_string_arg(1,iVar2);
        iVar2 = civ_leader_name(human_civ);
        text_set_string_arg(2,iVar2);
        iVar2 = civ_name_plural(human_civ);
        text_set_string_arg(3,iVar2);
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
        game.human_players = local_8;
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
#undef local_8

/* 00484fec auto */
#define scenario_start_year (*(short *)((u8 *)&g.d_0064bcb6))
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(20)))
int __cdecl game_turn_to_year(int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = 0;
  local_c = (uint)game.difficulty;
  if ((game.game_flags & 4) != 0) {
    local_c--;
  }
  if ((game.game_flags & 8) != 0) {
    local_c++;
  }
  iVar1 = int_clamp(local_c - 1,0,3);
  if (-1 < game.first_launch_turn) {
    local_18 = param_1 - game.first_launch_turn;
    if (local_18 < 1) {
      local_18 = 0;
    }
    param_1 -= local_18;
  }
  if ((((game.game_flags & 0x80) == 0) || (scenario_year_increment == 0)) || (scenario_start_year == 0)) {
    if (param_1 != 0) {
      param_1--;
    }
    for (local_14 = 0;
        (*(int *)(&year_table_turn_counts + local_14 * 0xc + iVar1 * 0x48) < param_1 && (local_14 < 6));
        local_14 = local_14 + 1) {
      param_1 -= *(int *)(&year_table_turn_counts + local_14 * 0xc + iVar1 * 0x48);
    }
    if (local_14 < 6) {
      local_10 = *(int *)(&year_table_year_steps + local_14 * 0xc + iVar1 * 0x48) * param_1 +
                 *(int *)(&year_table_start_years + local_14 * 0xc + iVar1 * 0x48);
    }
    else {
      local_10 = *(int *)(&year_table_last_year_step + iVar1 * 0x48) * *(int *)(&year_table_last_turn_count + iVar1 * 0x48) +
                 *(int *)(&year_table_last_start_year + iVar1 * 0x48) + param_1;
    }
    if (local_10 == 0) {
      local_10 = 1;
    }
  }
  else {
    if (scenario_year_increment < 1) {
      local_1c = ~(int)scenario_year_increment + 1;
    }
    else {
      local_1c = (int)scenario_year_increment;
    }
    local_10 = (int)scenario_start_year + param_1 * local_1c - 1;
  }
  return local_10 + local_18;
}
#undef scenario_start_year
#undef scenario_year_increment
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 00485c15 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_4c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(16)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(40)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(48)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(52)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(56)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(60)))
#define unit3 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(72)))
void __cdecl game_spawn_barbarians(void)

{
  short y;
  iptr iVar2;
  iptr iVar3;
  int unit;
  int iVar5;
  uint uVar6;
  iptr iVar7;
  uint uVar8;
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
      local_8 = 0xf;
    }
    else if (game.barbarian_activity == 2) {
      local_8 = 7;
    }
    else if (game.barbarian_activity == 3) {
      local_8 = 7;
    }
    if (((local_8 & (int)game.turn + 1U) == 0) &&
       (game.advance_known_by[unit_types[0x16].prerequisite] == '\0')) {
      local_40 = 0;
      do {
        if (map.width == 1 || map.width - 1 < 0) {
          x2 = 0;
        }
        else {
          iVar2 = _rand();
          x2 = iVar2 % (int)map.width;
        }
        if (map.height == 7 || map.height - 7 < 0) {
          local_44 = 0;
        }
        else {
          local_44 = _rand();
          local_44 = local_44 % (map.height - 6);
        }
        y2 = local_44 + 3;
        if ((x2 & 1) != 0) {
          x2--;
        }
        if ((y2 & 1) != 0) {
          x2++;
        }
        local_40++;
        if (1000 < local_40) {
          return;
        }
        iVar3 = tile_is_ocean(x2,y2);
      } while (((iVar3 == 0) || (unit = tile_unit_owner(x2,y2), -1 < unit)) ||
              (unit = tile_landmass(x2,y2),
              *(short *)(&water_body_sizes + unit * 0x10) < 0x10));
      unit = int_clamp((int)game.turn /
                                 (int)((uint)game.barbarian_activity * -0x32 + 0xfa) + 1,1,5);
      local_34 = unit + 1;
      if (game.barbarian_activity == 3) {
        local_34 = unit + 2;
      }
      unit_type2 = 0x20;
      if (game.advance_known_by[0x39] != '\0') {
        unit_type2 = 0x21;
      }
      if (game.advance_known_by[0x2d] != '\0') {
        unit_type2 = 0x23;
      }
      local_38 = 2;
      if ((game.rules & 1) != 0) {
        local_38 = 4;
      }
      if ((game.human_players & game.advance_known_by[0x27]) != 0) {
        local_38 = 5;
      }
      if ((game.advance_known_by[0x33] != '\0') ||
         ((game.barbarian_activity == 3 && (game.advance_known_by[0xb] != '\0')))) {
        if (((x2 & 1) == 0) || ((game.rules & 1) == 0)) {
          local_38 = 0x13;
        }
        else {
          local_38 = 0x12;
        }
      }
      local_c = local_34;
      if (((game.human_players & game.advance_known_by[0x51]) != 0) && ((game.rules & 1) != 0)) {
        local_38 = 0x14;
      }
      while( true ) {
        local_c--;
        if ((int)local_c < 0) break;
        unit_type = local_38;
        if ((local_c != 0) && (local_34 - 1 == local_c)) {
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
        uVar6 = _rand();
        uVar8 = (int)uVar6 >> 0x1f;
        if (((uVar6 ^ uVar8) - uVar8 & 1 ^ uVar8) == uVar8) {
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
      iVar5 = city_treasury_share(city);
      if (unit % 100 < iVar5) {
        local_28 = 0;
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
              local_28 = 200;
              goto LAB_004862b4;
            }
            local_28++;
            if ((int)((uint)game.barbarian_activity * 0x32) <= local_28) goto LAB_004862b4;
            unit = map_in_bounds(x2,y2);
          } while (((unit == 0) || (nearest_city_dist < 5)) ||
                  ((unit = tile_zoc_unit_adjacent(x2,y2,0), unit != 0 ||
                   ((unit = tile_is_ocean(x2,y2), unit != 0 ||
                    (unit = tile_unit_owner(x2,y2), -1 < unit))))));
          unit = tile_landmass((int)cities[city].x,(int)cities[city].y);
          iVar5 = tile_landmass(x2,y2);
        } while (unit != iVar5);
LAB_004862b4:
        if (local_28 < (int)((uint)game.barbarian_activity * 0x32)) {
          if (((game.barbarian_activity == 1) || (game.barbarian_activity == 2)) ||
             (game.barbarian_activity == 3)) {
            local_8 = (uint)cities[city].size;
          }
          if (local_8 == 1 || (int)(local_8 - 1) < 0) {
            local_34 = 0;
          }
          else {
            local_34 = _rand();
            local_34 = local_34 % (int)local_8;
          }
          if ((game.barbarian_activity == 3) && (0x95 < game.turn)) {
            if (-(uint)game.difficulty == -9 || (int)(-(uint)game.difficulty + 9) < 0) {
              local_48 = 0;
            }
            else {
              local_48 = _rand();
              local_48 = local_48 % (int)(10 - (uint)game.difficulty);
            }
            if (local_48 == 0) {
              if ((int)local_8 / 2 == 1 || (int)local_8 / 2 - 1 < 0) {
                local_4c = 0;
              }
              else {
                local_4c = _rand();
                local_4c = local_4c % ((int)local_8 / 2);
              }
              local_34 = local_34 + local_4c + (int)local_8 / 2;
            }
          }
          uVar6 = int_clamp(local_34,2,99);
          local_14 = 0x10;
          local_2c = 0xf;
          unit = _rand();
          if (unit % 3 == 0) {
            int_swap((iptr)&local_14,(iptr)&local_2c);
          }
          iVar7 = label_string(*(i32 *)(label_string_ids + 0x188));
          text_set_string_arg(0,iVar7);
          if ((10 < (int)uVar6) && ((int)cities[city].size / 2 < (int)uVar6)) {
            iVar7 = label_string(*(i32 *)(label_string_ids + 0x18c));
            text_set_string_arg(0,iVar7);
          }
          if (game.advance_known_by[0x23] != '\0') {
            iVar7 = label_string(*(i32 *)(label_string_ids + 400));
            text_set_string_arg(0,iVar7);
            if ((game.rules & 1) != 0) {
              local_14 = 4;
              local_2c = 0x11;
            }
          }
          if (game.advance_known_by[0x25] != '\0') {
            iVar7 = label_string(*(i32 *)(label_string_ids + 0x194));
            text_set_string_arg(0,iVar7);
            local_14 = 0x18;
            local_2c = 7;
            if (game.advance_known_by[unit_types[0x16].prerequisite] != '\0') {
              iVar7 = label_string(*(i32 *)(label_string_ids + 0x198));
              text_set_string_arg(0,iVar7);
              local_2c = 0xb;
              if (((game.rules & 1) != 0) && (local_14 = 0x19, game.advance_known_by[0x22] != '\0'))
              {
                if ((civs[game.field_138].government < 5) ||
                   (cities[city].owner != cities[city].founder)) {
                  local_14 = 0x15;
                  local_2c = 9;
                }
                else {
                  local_2c = 8;
                  iVar7 = label_string(*(i32 *)(label_string_ids + 0x19c));
                  text_set_string_arg(0,iVar7);
                }
              }
            }
          }
          unit2 = -1;
          for (local_c = uVar6; -1 < (int)local_c; local_c--) {
            if ((local_c & 4) == 0) {
              unit_type = local_2c;
            }
            else {
              unit_type = local_14;
            }
            if (local_c == uVar6) {
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
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef unit2
#undef local_38
#undef local_34
#undef city
#undef local_2c
#undef local_28
#undef unit_type2
#undef unit_type
#undef y2
#undef x2
#undef local_14
#undef unit3
#undef local_c
#undef local_8

/* 00486c2e auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl game_update_global_warming(void)

{
  i8 iVar1;
  int iVar2;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = bits_count8((uint)game.human_players);
  local_c = ((int)game.polluted_tiles - (int)game.field_28) + (int)game.field_28 / 2;
  local_14 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (iVar3 = city_has_improvement(city,0x1d), iVar3 != 0)) {
      local_14++;
    }
  }
  if (1 < iVar2) {
    local_c = (iVar2 - 1 + local_c) / iVar2;
  }
  iVar2 = (local_c * 2 + game.global_warmings * -4) - local_14;
  if (iVar2 == game.warming_counter || iVar2 - game.warming_counter < 0) {
    if (((local_c * 2 + game.global_warmings * -4) - local_14) - (int)game.warming_counter < 0) {
      game.warming_counter--;
    }
  }
  else {
    game.warming_counter++;
  }
  uVar4 = int_clamp((int)game.warming_counter,0,99);
  game.warming_counter = (i8)uVar4;
  if (((game.warming_counter == 12) && (6 < local_c)) && (autoplay_active == 0)) {
    if (2 < game.multiplayer) {
      net_send_text_args(4,0xff,0,0,0,0);
    }
    popup_game_with_sprite(ADDR(0x62c5ec, ((u8 *)&g.d_0062c5ec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  iVar1 = game.global_warmings;
  if (16 < game.warming_counter) {
    game.global_warmings++;
    map_apply_global_warming((int)iVar1);
    game.warming_counter = '\0';
  }
  game.field_28 = 0;
  return;
}
#undef autoplay_active
#undef local_14
#undef city
#undef local_c

/* 00487371 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define spaceship_winner_civ (*(iptr *)((u8 *)&g.d_0062c5b4))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl game_advance_turn(iptr civ)

{
  i32 uVar1;
  uint uVar2;
  int iVar3;
  iptr iVar4;
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
  uVar1 = game_turn_to_year((int)game.turn);
  game.year = (i16)uVar1;
  if (199 < game.turn) {
    game.field_2c++;
  }
  game.field_06 = game.field_06 & 0xfffe;
  units_reset_for_turn(civ);
  uVar2 = (uint)game.difficulty;
  if ((int)game.turn % (int)((uVar2 + 1) * 0xc) == 0) {
    for (civ2 = 0; civ2 < 8; civ2++) {
      if (((((int)game.turn % (int)((uVar2 + 1) * 0x18) == 0) ||
           (iVar3 = civ_has_wonder(civ2,0x14), iVar3 != 0)) &&
          ((1 < civs[civ2].reputation || (iVar3 = civ_has_wonder(civ2,0x14), iVar3 != 0)
           ))) && (civs[civ2].reputation != '\0')) {
        civs[civ2].reputation += 0xff;
        if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
          for (civ3 = 0; civ3 < 8; civ3++) {
            uVar1 = int_clamp((int)civs[civ3].field_48[civ2],0,
                                       (uint)civs[civ2].reputation);
            civs[civ3].field_48[civ2] = (char)uVar1;
          }
        }
      }
    }
  }
  if (game.next_history_turn < game.turn) {
    iVar3 = _rand();
    game.next_history_turn = game.turn + (short)(iVar3 % 0x28) + 0x14;
    if (autoplay_active == 0) {
      if (2 < game.multiplayer) {
        net_send_text_args(5,0xff,0,0,0,0);
      }
      if (game.multiplayer == 1) {
        city_window_close();
        wnd_hide((WndBase *)&status_window_wnd);
        wnd_hide((WndBase *)&minimap_wnd);
        for (local_8 = 0; local_8 < 8; local_8++) {
          if (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0) {
            wnd_hide((WndBase *)(&map_view_wnds + local_8 * 0x3f0));
          }
        }
      }
      historian_report_show();
      if (game.multiplayer == 1) {
        window_show((C_004083b0_4 *)&status_window);
        window_show((C_004083b0_4 *)&minimap_window);
        for (local_8 = 0; local_8 < 8; local_8++) {
          if (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0) {
            window_show((C_004083b0_4 *)(&map_views + local_8 * 0x3f0));
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
    iVar3 = civ_spaceship_launched(civ2);
    if (((iVar3 != 0) && (iVar3 = civ_spaceship_arrived(civ2), iVar3 != 0)) &&
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
      iVar4 = civ_get_adjective(civ2);
      text_set_string_arg(0,iVar4);
      if ((human_civ == civ2) ||
         ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) {
        net_send_text_args(6,0xff,1,0,0,0);
        net_send_message(0x6b,0xff,(uint)game.game_flags,2,spaceship_winner_civ,0,0,0,0,0);
      }
      else {
        net_send_message(0x6b,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                           (uint)game.game_flags,1,spaceship_winner_civ,0,0,0,0,0);
        for (local_18 = 1; local_18 < 8; local_18++) {
          if ((((1 << ((byte)local_18 & 0x1f) &
                (uint)(game.civs_alive & game.human_players) & 1 << ((byte)local_18 & 0x1f)) != 0)
              && (human_civ != local_18)) && (local_18 != civ2)) {
            net_send_text_args(6,*(i32 *)
                                  (&net_player_slots + *(int *)(&net_civ_slots + local_18 * 4) * 0x54),1,
                               0,0,0);
            net_send_message(0x6b,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + local_18 * 4) * 0x54)
                               ,(uint)game.game_flags,2,spaceship_winner_civ,0,0,0,0,0);
          }
        }
      }
    }
  }
  if ((autoplay_active == 0) && ((human_civ != civ2 || (game_over_reason == 0)))) {
    iVar4 = civ_get_adjective(civ2);
    text_set_string_arg(0,iVar4);
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
#undef local_18
#undef civ3
#undef local_8

/* 00488937 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_buffer_plus2 (*(i8 *)((u8 *)&g.d_00679642))
#define local_54 (*(i8 (*)[80])(frame_ + FRAME_OFF(4)))
void __cdecl game_autosave(iptr civ)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (human_civ == civ) {
    save_set_file_ext(0);
    text_clear();
    iVar1 = civ_leader_name(civ);
    text_append(iVar1);
    text_buffer_plus2 = 0;
    str_trim(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_append(ADDR(0x62c608, ((u8 *)&g.d_0062c608)));
    text_append_label(0x5c);
    FUN_005f22d0(local_54,&text_buffer);
    str_append((iptr)local_54,ADDR(0x62c60c, ((u8 *)&g.d_0062c60c)));
    text_append(ADDR(0x62c610, ((u8 *)&g.d_0062c610)));
    text_append(ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
    str_append((iptr)local_54,ADDR(0x62c614, ((u8 *)&g.d_0062c614)));
    str_append((iptr)local_54,ADDR(0x66c4e9, ((u8 *)&g.d_0066c4e9)));
    if ((game.turn & 4U) == 0) {
      FUN_005f66b0(local_54);
      FUN_005f6650(&text_buffer,local_54);
    }
    save_write_game(ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
  }
  return;
}
#undef human_civ
#undef text_buffer
#undef text_buffer_plus2
#undef local_54

/* 00489be2 auto */
#define tutorial_hint_shown_this_turn (*(int *)((u8 *)&g.d_0062c5c0))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl tutorial_settler_hints(iptr unit)

{
  u8 uVar1;
  u8 uVar2;
  char cVar3;
  bool bVar4;
  byte bVar5;
  int x;
  int y;
  iptr civ;
  int city;
  iptr x2;
  int iVar11;
  uint uVar12;
  byte *pbVar13;
  uptr terrain;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (tutorial_hint_shown_this_turn == 0) {
    x = (int)units[unit].x;
    y = (int)units[unit].y;
    civ = (iptr)units[unit].owner;
    bVar5 = tile_terrain(x,y);
    terrain = (uptr)bVar5;
    uVar1 = terrain_types[terrain].food;
    uVar2 = terrain_types[terrain].shields;
    city = tile_owner_or_fertility(x,y);
    bVar4 = 9 < city && 1 < (int)(char)uVar1 + (int)(char)uVar2;
    for (local_10 = 0; local_10 < 8; local_10++) {
      x2 = map_wrap_x((char)(&dir_dx_table)[local_10] + x);
      cVar3 = (&dir_dy_table)[local_10];
      iVar11 = map_in_bounds(x2,cVar3 + y);
      if ((iVar11 != 0) && (iVar11 = tile_owner_or_fertility(x2,cVar3 + y), city < iVar11)) {
        bVar4 = false;
      }
    }
    if (bVar4) {
      mapview_center_if_moved(x,y);
      popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c628, ((u8 *)&g.d_0062c628)),unit);
      tutorial_hint_shown_this_turn = 1;
    }
    else if (((int)game.turn - (int)civs[civ].last_city_turn < 0x19) ||
            (5 < civs[civ].num_cities)) {
      city = city_find_nearest(x,y,civ,0xffffffff,-1);
      if ((nearest_city_dist == 1) ||
         ((nearest_city_dist == 2 && (iVar11 = tile_resource(x,y), iVar11 != 0)))) {
        text_set_string_arg(0,(iptr)&cities[city].name);
        uVar12 = tile_improvements(x,y);
        if ((terrain == 4) && ((uVar12 & 0xc) == 0)) {
          mapview_center_if_moved(x,y);
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c63c, ((u8 *)&g.d_0062c63c)),unit);
          tutorial_hint_shown_this_turn = 1;
        }
        if (((terrain == 1) || ((terrain == 2 && (civs[civ].government == 2)))) &&
           (((uVar12 & 0xc) == 0 && (city = tile_has_irrigation_source(x,y), city != 0)))) {
          mapview_center_if_moved(x,y);
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c644, ((u8 *)&g.d_0062c644)),unit);
          tutorial_hint_shown_this_turn = 1;
        }
        else if (((((uint)civs[civ].units_active[0] + (uint)civs[civ].units_active[1] < 2) &&
                  ((uVar12 & 0x10) == 0)) && (terrain_types[terrain].move_cost == 1)) &&
                (pbVar13 = (byte *)tile_at(x,y), (*pbVar13 & 0x80) == 0)) {
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
#undef local_10

/* 0048a004 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
i32 __cdecl game_run_active_unit(void)

{
  bool bVar1;
  bool bVar2;
  i16 iVar3;
  iptr unit;
  iptr iVar5;
  int unit2;
  int iVar7;
  bool bVar8;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = game.num_units;
  local_14 = 0;
  bVar2 = false;
  bVar1 = false;
  unit_blink_active = 1;
  unit = (iptr)game.active_unit;
  if (((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (((int)(short)units[unit].flags & 0x8000U) == 0)) &&
     (units[unit].orders == -1)) {
    if ((unit_types[units[unit].type].role == 5) &&
       (iVar5 = unit_is_selectable(unit), iVar5 != 0)) {
      tutorial_settler_hints((int)game.active_unit);
    }
    else if ((unit_types[units[unit].type].attack != '\0') && (4 < units[unit].damage)) {
      bVar8 = false;
      unit2 = unit_max_hp(unit);
      if ((int)(uint)units[unit].damage < unit2 / 3) {
        if ((game.field_0c & 0x80) == 0) {
          game.field_0c = game.field_0c | 0x80;
          bVar8 = true;
        }
      }
      else {
        bVar8 = (game.field_0c & 0x40) == 0;
        if (bVar8) {
          game.field_0c = game.field_0c | 0xc0;
        }
      }
      if ((bVar8) && (autoplay_active == 0)) {
        popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62c658, ((u8 *)&g.d_0062c658)),unit);
      }
    }
  }
  unit2 = (int)game.active_unit;
  local_1c = 0;
  while (((iVar7 = unit_is_selectable((int)game.active_unit), iVar7 != 0 &&
          ((((unit_blink_active != '\0' || (unit_move_unanimated_state == 2)) && (player_turn_active != '\0')) &&
           ((game_loop_active != '\0' && (game.num_units == iVar3)))))) &&
         ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) != 0))) {
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (unit_move_unanimated_state == 2) {
      unit_blink_active = 1;
      unit_move_unanimated_state = '\0';
      bVar1 = true;
    }
    if ((bVar1) && (units[game.active_unit].orders != 11)) {
      unit_blink_active = '\0';
      bVar1 = false;
    }
    bVar2 = true;
    snd_sync_music_option();
    if (((int)(short)units[unit2].flags & 0x8000U) == 0) {
      iVar7 = unit_execute_orders(unit2);
      if (iVar7 == 0) {
        local_14 = 1;
        win_pump_one_message();
      }
    }
    else {
      unit_continue_active_orders();
      local_1c++;
      if (0x14 < local_1c) {
        unit_exhaust_moves(unit2);
      }
    }
  }
  mapviews_redraw_cursor();
  unit_blink_active = 0;
  if (!bVar2) {
    game.active_unit = -1;
  }
  return local_14;
}
#undef autoplay_active
#undef game_loop_active
#undef human_civ
#undef player_turn_active
#undef unit_blink_active
#undef local_1c
#undef local_14

/* 0048a374 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
void __cdecl game_wait_for_player_input(void)

{
  i16 iVar1;
  
  iVar1 = game.num_units;
  unit_blink_active = 1;
  while ((((unit_blink_active != '\0' && (player_turn_active != '\0')) && (game_loop_active != '\0')) &&
         ((moving_units_mode == 0 && (game.num_units == iVar1))))) {
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
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
void __cdecl game_player_move_loop(void)

{
  short sVar1;
  iptr iVar2;
  uint uVar2;
  int unit;
  iptr city;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  sVar1 = -1;
  game.active_unit = -1;
  ui_focus_active_unit(0);
  player_turn_active = 1;
  tutorial_hint_shown_this_turn = 0;
  if ((2 < game.multiplayer) && (net_host_flag == '\0')) {
    for (local_18 = 0; local_18 < 8; local_18++) {
      if (((*(int *)(&net_meet_pending_flags + local_18 * 4) != 0) &&
          (*(i32 *)(&net_meet_pending_flags + local_18 * 4) = 0,
          ((uint)game.civs_alive & 1 << ((&net_meet_pending_flags)[local_18 * 4] & 0x1f)) != 0)) &&
         (((uint)game.human_players & 1 << ((&net_meet_pending_flags)[local_18 * 4] & 0x1f)) == 0)) {
        diplo_ai_meet_player(*(iptr *)(&net_meet_pending_ai_civ + local_18 * 4),
                           *(iptr *)(&net_meet_pending_civ + local_18 * 4),
                           *(i32 *)(&net_meet_pending_x + local_18 * 4),
                           *(i32 *)(&net_meet_pending_y + local_18 * 4),0);
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
          ((iVar2 = unit_is_selectable((int)game.active_unit), iVar2 == 0 ||
           (game.num_units != sVar1)))))) {
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
    sVar1 = game.num_units;
    unit_move_unanimated_state = '\0';
    unit_focus_done = '\0';
    if (game.active_unit < 0) {
      game.field_06 = game.field_06 | 1;
      if (moving_units_mode == 1) {
        snd_play_effect(100,1,0,0);
      }
      ui_redraw_all_maps(1);
      if (((local_c == 0) || (((*(i8 *)((char *)&game.game_options + 1)) & 0x40) != 0)) || ((game.field_06 & 2) != 0))
      goto LAB_0048a77d;
      player_turn_active = '\0';
    }
    else {
LAB_0048a77d:
      unit_blink_active = 1;
      if (game.active_unit < 0) {
        game.field_06 = game.field_06 & 0xfffd;
        game_wait_for_player_input();
      }
      else {
        game.field_06 = game.field_06 & 0xfffc;
        uVar2 = game_run_active_unit();
        local_c = local_c | uVar2;
      }
      unit = citywnd_get_city((C_004083b0_4 *)&city_window);
      if (unit == -1) {
        game.field_06 = game.field_06 & 0xfffd;
      }
      if (game_loop_active == '\0') {
        return;
      }
      if ((game.field_06 & 2) != 0) {
        local_c = 0;
      }
      if (unit_blink_phase != '\0') {
        mapviews_redraw_cursor();
      }
      unit_blink_active = 0;
    }
    if (((game_loop_active == '\0') || (player_turn_active == '\0')) ||
       ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0)) {
      if ((city_window_closed == 0) &&
         (city = citywnd_get_city((C_004083b0_4 *)&city_window),
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
#undef local_18
#undef unit2
#undef local_c

/* 0048a92d auto */
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl game_calc_human_wonder_range(void)

{
  byte bVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 4; local_8++) {
    (&human_wonders_by_group_max)[local_8] = 0;
    (&human_wonders_by_group_min)[local_8] = 99;
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        bVar1 = civs[civ].wonders_by_group[local_8];
        if (bVar1 <= (byte)(&human_wonders_by_group_max)[local_8]) {
          bVar1 = (&human_wonders_by_group_max)[local_8];
        }
        (&human_wonders_by_group_max)[local_8] = bVar1;
        bVar1 = civs[civ].wonders_by_group[local_8];
        if ((byte)(&human_wonders_by_group_min)[local_8] <= bVar1) {
          bVar1 = (&human_wonders_by_group_min)[local_8];
        }
        (&human_wonders_by_group_min)[local_8] = bVar1;
      }
    }
  }
  return;
}
#undef civ
#undef local_8

/* 0048aa24: written by hand in src/game/retvals.c */

/* 0048aedc auto */
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_max_turns (*(short *)((u8 *)&g.d_0064bcb8))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl game_check_retirement(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (((game.game_flags & 2) == 0) && (game_over_reason == 0)) {
    iVar1 = civ_leader_title(human_civ);
    text_set_string_arg(0,iVar1);
    iVar1 = civ_leader_name(human_civ);
    text_set_string_arg(1,iVar1);
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
        local_8 = 1;
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
      local_8 = 1;
    }
  }
  return local_8;
}
#undef game_over_reason
#undef human_civ
#undef scenario_max_turns
#undef local_8

/* 0048b165 auto */
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define spaceship_winner_civ (*(int *)((u8 *)&g.d_0062c5b4))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
uint __cdecl game_handle_game_over(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
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
        local_8 = 1;
      }
      else {
        iVar1 = popup_game_with_sprite(ADDR(0x62c710, ((u8 *)&g.d_0062c710)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        local_8 = (uint)(iVar1 == 0);
      }
      game.game_flags = game.game_flags | 0x20;
    }
  }
  else {
    local_8 = 1;
  }
  game_over_reason = 0;
  return local_8;
}
#undef game_over_reason
#undef human_civ
#undef spaceship_winner_civ
#undef local_8

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
#define _DAT_0066c990 (*(i32 *)((u8 *)&g.d_0066c990))
#define _DAT_006ad578 (*(i32 *)((u8 *)&g.d_006ad578))
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
#define civ (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_324 (*(byte *)(frame_ + FRAME_OFF(12)))
#define local_318 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(780)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(784)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(788)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(792)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(796)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(800)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(808)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl game_play_loop(void)

{
  bool bVar1;
  bool bVar2;
  int iVar4;
  iptr iVar5;
  iptr iVar3;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_24 = 0;
  bVar1 = false;
  dialog_ctor(&local_318,0x4000);
  local_8 = 0;
  picwnd_close((C_004083b0_488 *)&advisor_window);
  picwnd_close((C_004083b0_488 *)&casualty_window);
  menu_update_states();
  if (game.multiplayer == 1) {
    hotseat_human_players = game.human_players;
  }
  while( true ) {
    bVar2 = false;
    game_calc_human_wonder_range();
    if (turn_resume_civ == 0) {
      game_advance_turn(0xffffffff);
    }
    iVar4 = game_check_retirement();
    if ((iVar4 != 0) || (game_over_reason != 0)) {
      local_20 = bits_count8((uint)game.human_players);
      local_18 = game_handle_game_over();
      if ((game.multiplayer == 1) &&
         ((~(1 << ((byte)human_civ & 0x1f)) & (uint)game.human_players) != 0)) {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
      }
      if (((local_18 != 0) && (game.multiplayer == '\0')) ||
         ((local_18 != 0 && ((game.multiplayer == 1 && (local_20 < 2)))))) goto LAB_0048bf12;
      local_18 = 0;
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
          _DAT_006ad578 = civ;
          local_24 = 1;
          city_window_close();
          wnd_hide((WndBase *)&status_window_wnd);
          wnd_hide((WndBase *)&minimap_wnd);
          for (local_1c = 0; local_1c < 8; local_1c++) {
            if (*(short *)(&map_view_open_flags + local_1c * 0x3f0) != 0) {
              wnd_hide((WndBase *)(&map_view_wnds + local_1c * 0x3f0))
              ;
            }
          }
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          if (game.multiplayer == 1) {
            dlg_load_game_section(&local_318,ADDR(0x62c750, ((u8 *)&g.d_0062c750)),0x2000008);
            dlg_show_modal(&local_318,0);
          }
        }
        else {
          game.player_civ = (byte)civ;
          if (game.multiplayer != '\0') {
            civ_check_password(civ);
          }
          if (game.multiplayer == 1) {
            iVar5 = civ_leader_name(civ);
            text_set_string_arg(0,iVar5);
            iVar5 = civ_name_plural(civ);
            text_set_string_arg(1,iVar5);
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
          iVar3 = human_civ;
          human_civ = civ;
          if (game.multiplayer == 2) {
            if (bVar1) {
              game_save_dialog(0);
              if ((&civ_email_addresses)[civ * 0x20] == '\0') {
                iVar5 = civ_leader_name(civ);
                text_set_string_arg(0,iVar5);
                popup_game(ADDR(0x62c744, ((u8 *)&g.d_0062c744)));
              }
              else {
                iVar5 = civ_leader_name(civ);
                text_set_string_arg(0,iVar5);
                text_set_string_arg(1,(iptr)(&civ_email_addresses + civ * 0x20));
                popup_game(ADDR(0x62c738, ((u8 *)&g.d_0062c738)));
              }
              game_loop_active = '\0';
              goto LAB_0048bf12;
            }
            bVar1 = true;
          }
          if (((iVar3 & 0xffU) != civ) || (turn_resume_civ != 0)) {
            if (mp_turn_time_limit_ms != 0) {
              mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
              _DAT_0066c990 = 0xffffffff;
            }
            mapview_update_title((FrameWindow *)&map_views);
            map_redraw_all_views(human_civ,1);
          }
          status_draw_info(1);
          status_draw_civ_color(civ);
          if (local_24 != 0) {
            local_24 = 0;
            window_show((C_004083b0_4 *)&status_window);
            window_show((C_004083b0_4 *)&minimap_window);
            for (local_1c = 0; local_1c < 8; local_1c++) {
              if (*(short *)(&map_view_open_flags + local_1c * 0x3f0) != 0) {
                window_show((C_004083b0_4 *)(&map_views + local_1c * 0x3f0))
                ;
              }
            }
          }
        }
        status_draw_civ_color(civ);
        if ((game.multiplayer == 1) &&
           ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
          game.human_players = '\0';
          local_324 = (byte)human_civ;
          human_civ = -1;
        }
        if ((turn_resume_civ == 0) || (turn_resume_new_game != 0)) {
          if ((turn_resume_civ != 0) && (turn_resume_new_game != 0)) {
            mapview_update_title((FrameWindow *)&map_views);
            map_redraw_all_views(human_civ,1);
            wnd_flush_paint();
          }
          local_14 = *(int *)(&casualty_counts + human_civ * 4) -
                     *(int *)(&casualty_reported_counts + human_civ * 4);
          if (autoplay_active == 0) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            iVar5 = civ_leader_title(human_civ);
            text_set_string_arg(0,iVar5);
            iVar5 = civ_leader_name(human_civ);
            text_set_string_arg(1,iVar5);
            if (0 < local_14) {
              *(i32 *)(&casualty_reported_counts + human_civ * 4) =
                   *(i32 *)(&casualty_counts + human_civ * 4);
              text_set_number_arg(0,local_14);
              if (local_14 == 1) {
                dialog_load_text_noflags(&local_318,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c760, ((u8 *)&g.d_0062c760)));
              }
              else {
                dialog_load_text_noflags(&local_318,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c76c, ((u8 *)&g.d_0062c76c)));
              }
              dialog_add_sprite((DialogOptionList *)&local_318,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&local_318,0);
              input_flush_events();
              snd_play_effect(0x30,0,0,0);
              dlg_show_modal(&local_318,0);
              if (local_318.field_dc != 0) {
                casualty_timeline_show(human_civ);
              }
            }
          }
          civ_process_turn(civ);
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
             (ai_process_civ_units(), game.multiplayer == 1)) {
            dialog_close(&local_318);
            dialog_init_defaults(&local_318);
            human_civ = (iptr)local_324;
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
          bVar2 = true;
        }
        if (game.multiplayer == 1) {
          game.human_players = hotseat_human_players;
        }
        saved_turn_civ = 0;
        turn_resume_civ = 0;
        saved_resume_new_game = 0;
        turn_resume_new_game = 0;
        game.field_06 = game.field_06 & 0xfffe;
        if (game_loop_active == '\0') goto LAB_0048bf12;
        if (game_over_reason != 0) {
          local_20 = bits_count8((uint)game.human_players);
          local_18 = game_handle_game_over();
          if ((game.multiplayer == 1) &&
             ((~(1 << ((byte)human_civ & 0x1f)) & (uint)game.human_players) != 0)) {
            game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
          }
          if (((local_18 != 0) && (game.multiplayer == '\0')) ||
             ((local_18 != 0 && ((game.multiplayer == 1 && (local_20 < 2))))))
          goto LAB_0048bf12;
          local_18 = 0;
        }
      }
    }
    if ((!bVar2) && (game.multiplayer == '\0')) {
      game.turn_civ = (byte)human_civ;
      game_player_move_loop();
      if ((game_over_reason != 0) && (local_18 = game_handle_game_over(), local_18 != 0))
      goto LAB_0048bf12;
    }
    game.human_players = game.civs_alive & game.human_players;
    if (game_loop_active == '\0') {
LAB_0048bf12:
      mp_turn_timer_stop(0);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0048bf2d */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
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
#undef _DAT_0066c990
#undef _DAT_006ad578
#undef city
#undef civ
#undef local_324
#undef local_318
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define _DAT_0066c990 (*(i32 *)((u8 *)&g.d_0066c990))
#define _DAT_00673b08 (*(i32 *)((u8 *)&g.d_00673b08))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(i8 *)(frame_ + FRAME_OFF(768)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(772)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(776)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl game_mp_client_turn_loop(void)

{
  byte bVar1;
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
  dbg_logf_str_int(ADDR(0x62c778, ((u8 *)&g.d_0062c778)),iVar3,iVar5);
  for (civ = 1; civ < 8; civ++) {
    if (((*(int *)(&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54) != 0) &&
        ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      iVar4 = civ;
      iVar3 = civ_name_plural(civ);
      dbg_logf_str_int(ADDR(0x62c788, ((u8 *)&g.d_0062c788)),iVar3,iVar4);
    }
  }
  net_reset_error_counts();
  human_civ = (&net_slot_civs)[net_local_slot * 0x15];
  turn_resume_civ = saved_turn_civ;
  turn_resume_new_game = (int)saved_resume_new_game;
  picwnd_close((C_004083b0_488 *)&advisor_window);
  picwnd_close((C_004083b0_488 *)&casualty_window);
  menu_update_states();
  game.player_civ = (byte)human_civ;
  game.turn_civ = (byte)human_civ;
  mapview_update_title((FrameWindow *)&map_views);
  local_1c = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
      mapview_center_on
                ((C_004083b0_430 *)&map_views,(int)units[unit].x,(int)units[unit].y);
      local_1c++;
      break;
    }
  }
  if (local_1c == 0) {
    for (unit = 0; unit < game.num_cities; unit++) {
      if ((cities[unit].id != 0) && (cities[unit].owner == human_civ)) {
        mapview_center_on
                  ((C_004083b0_430 *)&map_views,(int)cities[unit].x,(int)cities[unit].y
                  );
        break;
      }
    }
  }
  status_draw_info(1);
  status_draw_civ_color(human_civ);
  ui_redraw_all_maps(1);
  bVar1 = turn_resume_civ;
  if ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0) {
    net_heartbeat_send(net_slot_civs);
    dlg_pending_idle_callback = ((void *)ADDR(0x00401a5a, net_client_hot_wait_idle));
    popup_game_sprite_flags(ADDR(0x62c798, ((u8 *)&g.d_0062c798)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    bVar1 = turn_resume_civ;
  }
LAB_0048c326:
  do {
    turn_resume_civ = bVar1;
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
      iVar4 = net_check_lost_connections();
      if (iVar4 != 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0048c9ce */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
        uVar5 = 0;
        goto LAB_0048c9e4;
      }
    }
    if (net_host_handoff_stage != '\0') {
      iVar4 = net_client_transfer_server();
      if (iVar4 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0048c9ce */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
        uVar5 = 0;
        goto LAB_0048c9e4;
      }
      if (net_host_flag != '\0') {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0048c9ce */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
        uVar5 = 1;
        goto LAB_0048c9e4;
      }
      if (((nm_start_civ_count == 0) && (nm_end_sequence_count == 0)) &&
         ((player_has_quit == '\0' && (bVar1 = turn_resume_civ, game_loop_active != '\0'))))
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
        _DAT_0066c990 = 0xffffffff;
      }
      mapview_update_title((FrameWindow *)&map_views);
      map_redraw_all_views(human_civ,1);
      status_draw_info(1);
      status_draw_civ_color(human_civ);
      local_18 = *(int *)(&casualty_counts + human_civ * 4) -
                 *(int *)(&casualty_reported_counts + human_civ * 4);
      if (autoplay_active == 0) {
        dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
        iVar3 = civ_leader_title(human_civ);
        text_set_string_arg(0,iVar3);
        iVar3 = civ_leader_name(human_civ);
        text_set_string_arg(1,iVar3);
        if (local_18 < 1) {
          dialog_load_text_noflags(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7c0, ((u8 *)&g.d_0062c7c0)));
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
            dialog_load_text_noflags(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7a8, ((u8 *)&g.d_0062c7a8)));
          }
          else {
            dialog_load_text_noflags(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7b4, ((u8 *)&g.d_0062c7b4)));
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
        _DAT_00673b08 = (uint)game.human_players;
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
      local_20 = 0;
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
    local_14 = 0;
    bVar1 = 0;
    if (game_loop_active == '\0') {
      net_send_message(0x2d,0,human_civ,0,0,0,0,0,0,0);
      XD_FlushSendBuffer(60000);
      net_session_shutdown(&net_session,1);
      if (game_over_reason != 0) {
        game_handle_game_over();
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0048c9ce */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
      uVar5 = 0;
LAB_0048c9e4:
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
#undef _DAT_0066c990
#undef _DAT_00673b08
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
#define _DAT_0066c990 (*(i32 *)((u8 *)&g.d_0066c990))
#define _DAT_00673b08 (*(i32 *)((u8 *)&g.d_00673b08))
#define _DAT_006ad578 (*(i32 *)((u8 *)&g.d_006ad578))
#define civ (*(uptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_31c (*(Dialog *)(frame_ + FRAME_OFF(20)))
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

void __cdecl game_mp_host_turn_loop(i32 param_1)

{
  byte bVar1;
  SHORT SVar2;
  iptr iVar3;
  int iVar4;
  iptr iVar5;
  uptr uVar6;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_31c,0x4000);
  local_8 = 0;
  iVar5 = human_civ;
  iVar3 = civ_name_plural(human_civ);
  dbg_logf_str_int(ADDR(0x62c7d0, ((u8 *)&g.d_0062c7d0)),iVar3,iVar5);
  for (civ = 1; (int)civ < 8; civ++) {
    if (((human_civ != civ) &&
        ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      uVar6 = civ;
      iVar3 = civ_name_plural(civ);
      dbg_logf_str_int(ADDR(0x62c7e0, ((u8 *)&g.d_0062c7e0)),iVar3,uVar6);
    }
  }
  net_reset_error_counts();
  map_rebuild_unit_flags();
  picwnd_close((C_004083b0_488 *)&advisor_window);
  picwnd_close((C_004083b0_488 *)&casualty_window);
  menu_update_states();
  ui_redraw_all_maps(1);
  mapview_update_title((FrameWindow *)&map_views);
  local_18 = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
      mapview_center_on
                ((C_004083b0_430 *)&map_views,(int)units[unit].x,(int)units[unit].y);
      local_18++;
      break;
    }
  }
  if (local_18 == 0) {
    for (unit = 0; unit < game.num_cities; unit++) {
      if ((cities[unit].id != 0) && (cities[unit].owner == human_civ)) {
        mapview_center_on
                  ((C_004083b0_430 *)&map_views,(int)cities[unit].x,(int)cities[unit].y
                  );
        break;
      }
    }
  }
  bVar1 = turn_resume_civ;
  if (turn_resume_civ != 0) {
    do {
      if ((1 << (turn_resume_civ & 0x1f) & (uint)game.civs_alive) != 0) goto LAB_0048ccea;
      turn_resume_civ++;
      if (turn_resume_civ == 8) {
        turn_resume_civ = 0;
      }
    } while (turn_resume_civ != bVar1);
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
    iVar4 = game_check_retirement();
    if ((iVar4 != 0) || (game_over_reason != 0)) {
      game_loop_active = '\0';
LAB_0048d957:
      mp_turn_timer_stop(0);
      net_host_quit_handoff();
      if (game_over_reason != 0) {
        game_handle_game_over();
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0048d989 */ { dialog_dtor((Dialog *)((iptr)&local_31c)); }
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
           ((char)param_1 != '\0')) {
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
            _DAT_0066c990 = 0xffffffff;
          }
          _DAT_006ad578 = civ;
          menu_update_states();
          _DAT_0066c990 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          local_28 = main_view_frame_left;
          local_24 = main_view_frame_top;
          local_20 = main_view_frame_right;
          local_1c = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_28);
          net_send_message(0x69,0xff,civ,0,0,0,0,0,0,0);
          mapview_update_title((FrameWindow *)&map_views);
          map_redraw_all_views(human_civ,1);
          status_draw_civ_color(civ);
          local_14 = *(int *)(&casualty_counts + human_civ * 4) -
                     *(int *)(&casualty_reported_counts + human_civ * 4);
          if (autoplay_active == 0) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            iVar3 = civ_leader_title(human_civ);
            text_set_string_arg(0,iVar3);
            iVar3 = civ_leader_name(human_civ);
            text_set_string_arg(1,iVar3);
            if (*(int *)(&casualty_reported_counts + human_civ * 4) <
                *(int *)(&casualty_counts + human_civ * 4)) {
              *(i32 *)(&casualty_reported_counts + human_civ * 4) =
                   *(i32 *)(&casualty_counts + human_civ * 4);
              text_set_number_arg(0,local_14);
              if (local_14 == 1) {
                dialog_load_text_noflags(&local_31c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7f0, ((u8 *)&g.d_0062c7f0)));
              }
              else {
                dialog_load_text_noflags(&local_31c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c7fc, ((u8 *)&g.d_0062c7fc)));
              }
              dialog_add_sprite((DialogOptionList *)&local_31c,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&local_31c,0);
              input_flush_events();
              snd_play_effect(0x30,0,0,0);
              dlg_show_modal(&local_31c,0);
              if (local_31c.field_dc != 0) {
                casualty_timeline_show(human_civ);
              }
            }
            else {
              dialog_load_text_noflags(&local_31c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62c808, ((u8 *)&g.d_0062c808)));
              dialog_add_sprite((DialogOptionList *)&local_31c,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&local_31c,0);
              input_flush_events();
              snd_play_effect(0x30,0,0,0);
              dlg_show_modal(&local_31c,0);
            }
          }
          if (autoplay_active == 0) {
            if (turn_resume_civ == 0) {
              civ_check_throne_room_upgrade();
            }
            if (((turn_resume_civ == 0) || (turn_resume_new_game != 0)) || ((char)param_1 != '\0')) {
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
            _DAT_00673b08 = (uint)game.human_players;
            game.human_players = '\0';
            if (((turn_resume_civ == 0) || (turn_resume_new_game != 0)) || ((char)param_1 != '\0')) {
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
          _DAT_006ad578 = civ;
          menu_update_states();
          _DAT_0066c990 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          local_28 = main_view_frame_left;
          local_24 = main_view_frame_top;
          local_20 = main_view_frame_right;
          local_1c = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_28);
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
          iVar4 = *(int *)(&net_civ_slots + civ * 4);
          _DAT_006ad578 = civ;
          menu_update_states();
          _DAT_0066c990 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          local_28 = main_view_frame_left;
          local_24 = main_view_frame_top;
          local_20 = main_view_frame_right;
          local_1c = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_28);
          nm_start_civ_count = 0;
          *(i32 *)(&net_civ_turn_ended + civ * 4) = 0;
          net_send_message(0x69,0xff,civ,0,0,0,0,0,0,0);
          map_redraw_all_views(human_civ,1);
          status_draw_civ_color(civ);
          net_send_message(0x16,*(i32 *)(&net_player_slots + iVar4 * 0x54),0,0,0,0,0,0,0,0);
          if (*(int *)(&net_civ_new_player_flags + civ * 4) != 0) {
            *(i32 *)(&net_civ_new_player_flags + civ * 4) = 0;
            FUN_005f22d0(&text_string_args,
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
        if ((player_has_quit == '\0') || (_DAT_006ad578 == human_civ)) {
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
        (*(i8 *)((char *)&param_1 + 0)) = '\0';
        game.field_06 = game.field_06 & 0xfffe;
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
#undef _DAT_0066c990
#undef _DAT_00673b08
#undef _DAT_006ad578
#undef civ
#undef city
#undef unit
#undef local_31c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00497da0 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
iptr __cdecl save_read_cstr(iptr param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (i8 *)param_1;
  local_10 = 1;
  for (local_8 = 0; (local_10 != 0 && (local_8 < 0x4f)); local_8++) {
    local_10 = _fgetc((FILE *)param_2);
    *local_c = (i8)local_10;
    local_c++;
  }
  _fgetc((FILE *)param_2);
  return param_1;
}
#undef local_10
#undef local_c
#undef local_8

/* 00497e0f auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl save_write_cstr_eof(iptr param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  while (local_8 != 0) {
    local_8 = (int)*(char *)param_1;
    param_1++;
    _fputc(local_8,(FILE *)param_2);
  }
  _fputc(0x1a,(FILE *)param_2);
  return;
}
#undef local_8

/* 00498784 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl passwords_reset(void)

{
  byte bVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0xff; local_8++) {
    iVar2 = _rand();
    bVar1 = (byte)(iVar2 >> 0x1f);
    (&civ_passwords)[local_8] = (((byte)iVar2 ^ bVar1) - bVar1 ^ bVar1) - bVar1;
  }
  for (local_10 = 0; local_10 < 8; local_10++) {
    (&civ_passwords)[local_10 * 0x20] = 0;
    *(i32 *)(&civ_password_prompt_pending + local_10 * 4) = 0;
    *(i32 *)(&civ_has_password + local_10 * 4) = 0;
  }
  passwords_scramble();
  return;
}
#undef local_10
#undef local_8

/* 0049882b auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl passwords_refresh_flags(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  passwords_unscramble();
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((&civ_passwords)[local_8 * 0x20] == '\0') {
      *(i32 *)(&civ_password_prompt_pending + local_8 * 4) = 0;
      *(i32 *)(&civ_has_password + local_8 * 4) = 0;
    }
    else {
      *(i32 *)(&civ_password_prompt_pending + local_8 * 4) = 1;
      *(i32 *)(&civ_has_password + local_8 * 4) = 1;
    }
  }
  passwords_scramble();
  return;
}
#undef local_8

/* 004988b8 auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(byte *)(frame_ + FRAME_OFF(4)))
void __cdecl passwords_scramble(void)

{
  char cVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  cVar1 = civ_passwords_last_byte;
  for (local_10 = 0; local_c = cVar1 << 5, local_10 < 0x100; local_10++) {
    cVar1 = (&civ_passwords)[local_10];
    (&civ_passwords)[local_10] =
         ((byte)((uint)(int)(char)(&civ_passwords)[local_10] >> 3) & 0x1f | local_c) ^ (byte)local_10
    ;
  }
  return;
}
#undef local_10
#undef local_c

/* 00498943 auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(char *)(frame_ + FRAME_OFF(8)))
void __cdecl passwords_unscramble(void)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = civ_passwords;
  for (local_10 = 0xff; -1 < local_10; local_10--) {
    uVar1 = (uint)local_8;
    (&civ_passwords)[local_10] = (&civ_passwords)[local_10] ^ (byte)local_10;
    local_8 = (&civ_passwords)[local_10];
    (&civ_passwords)[local_10] = (&civ_passwords)[local_10] << 3 | (byte)(uVar1 >> 5) & 7;
  }
  return;
}
#undef local_10
#undef local_8

/* 004989d3 auto */
#define local_84 (*(char (*)[128])(frame_ + FRAME_OFF(4)))
void __cdecl password_dialog_set_title(iptr param_1,int civ,i32 param_3)

{
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  FUN_005f22d0(local_84,(iptr)&civ_names[civ].leader_name);
  str_append_label((iptr)local_84,param_3);
  sVar1 = _strlen(local_84);
  uVar2 = memblock_alloc(param_1 + 0x254,sVar1 + 1);
  *(i32 *)(param_1 + 0x134) = uVar2;
  FUN_005f22d0(*(i32 *)(param_1 + 0x134),local_84);
  return;
}
#undef local_84

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
#define _DAT_0064bc12 (*(i16 *)((u8 *)&g.d_0064bc12))
#define _SCHAR_00h_0064bc1a (*(i16 *)((u8 *)&g.d_0064bc1a))
#define _SCHAR_00h_0064bc1c (*(i16 *)((u8 *)&g.d_0064bc1c))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl prefs_set_defaults(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  prefs_game_rules = 0x3f;
  _DAT_0064bc12 = 0;
  if (999 < screen_width) {
    _DAT_0064bc12 = 2;
  }
  prefs_difficulty = 0;
  prefs_tribe = 0;
  prefs_gender = 0;
  _SCHAR_00h_0064bc1a = 6;
  _SCHAR_00h_0064bc1c = 4;
  prefs_enemies_choice = 0;
  prefs_map_size = 1;
  prefs_game_options = 0x3f3258;
  iVar1 = mem_check_available(10000000);
  if (iVar1 == 0) {
    prefs_game_options = prefs_game_options & 0xffdfffff;
  }
  prefs_message_options = 0;
  prefs_barbarity = 2;
  for (local_8 = 0; local_8 < 5; local_8++) {
    (&prefs_world_params)[local_8] = 0;
  }
  FUN_005f22d0(&DAT_0064bc34,&prefs_defaults_empty_str);
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
#undef _DAT_0064bc12
#undef _SCHAR_00h_0064bc1a
#undef _SCHAR_00h_0064bc1c
#undef local_8

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
#define _DAT_00666540 (*(i16 *)((u8 *)&g.d_00666540))
#define _DAT_006666f2 (*(i16 *)((u8 *)&g.d_006666f2))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl prefs_set_mp_defaults(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  prefs_main_menu_choice = 0;
  prefs_multiplayer_type = 0;
  prefs_hotseat_menu_choice = 0;
  prefs_lan_menu_choice = 0;
  _DAT_00666540 = 0;
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
  FUN_005f22d0(&prefs_turn_timer_custom,&prefs_turn_timer_default_str);
  prefs_hotseat_players_choice = 0;
  _memset(&prefs_parley_wnd_rect,0,0x10);
  _memset(&prefs_chat_wnd_rect,0,0x10);
  prefs_clear_chat_on_new_game = 0;
  prefs_clear_chat_on_boot = 0;
  prefs_mp_double_production = 0;
  prefs_mp_double_moves = 0;
  DAT_00666602 = 0;
  DAT_0066661a = 0;
  DAT_00666632 = 0;
  for (local_8 = 0; local_8 < 7; local_8++) {
    for (local_c = 0; local_c < 0x18; local_c++) {
      (&DAT_0066664a)[local_8 * 0x18 + local_c] = 0;
    }
  }
  _DAT_006666f2 = 0;
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
#undef _DAT_00666540
#undef _DAT_006666f2
#undef local_c
#undef local_8

/* 004a733d auto */
#define prefs_game_rules (*(i16 *)((u8 *)&g.d_0064bc10))
#define prefs_main_menu_choice (*(i16 *)((u8 *)&g.d_00666538))
void __cdecl prefs_load_civ2dat(void)

{
  FILE *_File;
  size_t sVar1;
  
  _File = _fopen(PTR_s_CIV2_DAT_0062cec8,&civ2dat_read_mode_str);
  if (_File == (FILE *)0x0) {
    prefs_set_defaults();
    prefs_set_mp_defaults();
  }
  else {
    sVar1 = _fread(&prefs_game_rules,0x48,1,_File);
    if (sVar1 == 0) {
      prefs_set_defaults();
    }
    sVar1 = _fread(&prefs_main_menu_choice,0x1bc,1,_File);
    if (sVar1 == 0) {
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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl prefs_save_civ2dat(void)

{
  FILE *_File;
  size_t sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  _File = _fopen(PTR_s_CIV2_DAT_0062cec8,&civ2dat_write_mode_str);
  if (((_File != (FILE *)0x0) && (sVar1 = _fwrite(&prefs_game_rules,0x48,1,_File), sVar1 != 0)) &&
     (sVar1 = _fwrite(&prefs_main_menu_choice,0x1bc,1,_File), sVar1 != 0)) {
    local_8 = 0;
  }
  if ((_File != (FILE *)0x0) && (_fclose(_File), local_8 != 0)) {
    FUN_005f66b0(PTR_s_CIV2_DAT_0062cec8);
  }
  return local_8;
}
#undef prefs_game_rules
#undef prefs_main_menu_choice
#undef local_8

/* 004a7754 auto */
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
#define aiStack_180 (*(int (*)[64])(frame_ + FRAME_OFF(16)))
#define y2 (*(int *)(frame_ + FRAME_OFF(272)))
#define aiStack_7c (*(iptr (*)[8])(frame_ + FRAME_OFF(276)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(308)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(312)))
#define y3 (*(int *)(frame_ + FRAME_OFF(316)))
#define x2 (*(int *)(frame_ + FRAME_OFF(320)))
#define x3 (*(int *)(frame_ + FRAME_OFF(324)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(328)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(332)))
#define local_40 (*(uint *)(frame_ + FRAME_OFF(336)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(340)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(344)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(348)))
#define local_30 (*(iptr *)(frame_ + FRAME_OFF(352)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(356)))
#define aiStack_28 (*(int (*)[8])(frame_ + FRAME_OFF(360)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(392)))
void __cdecl game_balance_start_positions(void)

{
  byte bVar1;
  iptr iVar2;
  iptr iVar3;
  int unit;
  byte *pbVar5;
  i8 frame_[FRAME_OFF(400)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_5c = 0; local_5c < 0x40; local_5c++) {
    aiStack_180[local_5c] = 0;
  }
  x3 = (int)map.width >> 1;
  y3 = (int)map.height >> 1;
  for (civ = 1; civ < 8; civ++) {
    iVar2 = unit_find_nearest(x3,y3,civ,-1);
    aiStack_7c[civ] = iVar2;
    if (-1 < iVar2) {
      local_5c = tile_land_landmass(x3,y3);
      if (-1 < local_5c) {
        aiStack_180[local_5c]++;
      }
    }
  }
  local_38 = 0;
  for (civ = 1; civ < 8; civ++) {
    unit = aiStack_7c[civ];
    if (-1 < unit) {
      x3 = (int)units[unit].x;
      y3 = (int)units[unit].y;
      local_5c = tile_land_landmass(x3,y3);
      local_5c = int_clamp(local_5c,0,0x3f);
      local_2c = 0;
      local_34 = 999;
      for (local_3c = 1; local_3c < 8; local_3c++) {
        unit = aiStack_7c[local_3c];
        if ((-1 < unit) && (civ != local_3c)) {
          x2 = (int)units[unit].x;
          y2 = (int)units[unit].y;
          iVar3 = tile_land_landmass(x2,y2);
          if (local_5c == iVar3) {
            local_48 = map_distance_diag(x3,y3,x2,y2);
            if (local_48 < local_34) {
              local_34 = local_48;
            }
          }
        }
      }
      if (9 < local_34) {
        if (local_34 < 0x14) {
          local_2c++;
        }
        else if (local_34 == 999) {
          local_58 = (int)*(short *)(&landmass_table + local_5c * 0x10) / 0x32;
          local_58 = int_clamp(local_58,3,6);
          local_2c += local_58;
        }
        else {
          local_2c += 2;
        }
      }
      local_44 = 0;
      local_8 = 0;
      for (local_30 = 0; local_30 < 0x15; local_30++) {
        x2 = map_wrap_x((char)(&city_tile_dx_table)[local_30] + x3);
        y2 = (char)(&city_tile_dy_table)[local_30] + y3;
        unit = map_in_bounds(x2,y2);
        if (unit != 0) {
          bVar1 = tile_terrain(x2,y2);
          local_40 = (uint)bVar1;
          if (local_40 == 2) {
            local_44++;
          }
          pbVar5 = (byte *)tile_at(x2,y2);
          if ((*pbVar5 & 0x80) != 0) {
            local_8++;
          }
        }
      }
      if (local_8 < 4) {
        if (3 < local_44) {
          local_2c += 2;
        }
      }
      else {
        local_2c += 4;
      }
      switch((int)*(short *)(&landmass_table + local_5c * 0x10) / 0x32) {
      case 0:
        break;
      case 1:
        local_2c++;
        break;
      case 2:
        local_2c += 2;
        break;
      case 3:
        local_2c += 3;
        break;
      default:
        local_2c += 3;
      }
      if (local_38 < local_2c) {
        local_38 = local_2c;
      }
      aiStack_28[civ] = local_2c;
    }
  }
  for (civ = 1; civ < 8; civ++) {
    unit = aiStack_7c[civ];
    if (-1 < unit) {
      if (((3 < local_38 - aiStack_28[civ]) ||
          (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 &&
           (game.difficulty == 5)))) ||
         ((game.multiplayer != '\0' && (game.difficulty == 5)))) {
        unit_create(0,civ,(int)units[unit].x,(int)units[unit].y);
        if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
           (game.difficulty != 5)) {
          aiStack_28[civ] += 3;
        }
        else {
          aiStack_28[civ]++;
        }
      }
      for (local_30 = 0; local_30 < local_38 - aiStack_28[civ]; local_30++) {
        civ_research_complete(civ,0);
      }
    }
  }
  return;
}
#undef civ
#undef aiStack_180
#undef y2
#undef aiStack_7c
#undef local_5c
#undef local_58
#undef y3
#undef x2
#undef x3
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef aiStack_28
#undef local_8

/* 004a9785 auto */
#define path_goal_x (*(iptr *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(i32 *)((u8 *)&g.d_0062d044))
#define path_road_planning (*(i32 *)((u8 *)&g.d_0062d040))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_94 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define y4 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_8c (*(i8 *)(frame_ + FRAME_OFF(20)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(24)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(28)))
#define x4 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define y2 (*(int *)(frame_ + FRAME_OFF(48)))
#define x2 (*(int *)(frame_ + FRAME_OFF(60)))
#define aiStack_60 (*(int (*)[8])(frame_ + FRAME_OFF(64)))
#define local_40 (*(uint *)(frame_ + FRAME_OFF(96)))
#define aiStack_3c (*(int (*)[8])(frame_ + FRAME_OFF(100)))
#define y3 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(140)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(144)))
#define local_c (*(int *)(frame_ + FRAME_OFF(148)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(152)))
void __cdecl game_accelerated_start(int param_1)

{
  char civ2;
  short y5;
  iptr x3;
  byte bVar4;
  iptr iVar5;
  iptr city;
  iptr iVar6;
  iptr unit3;
  iptr iVar9;
  int unit2;
  int iVar11;
  iptr x;
  byte *pbVar13;
  uint uVar14;
  int y;
  uint uVar16;
  uptr civ4;
  uptr civ3;
  i8 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (civ = 0; civ < 8; civ++) {
    aiStack_60[civ] = -1;
    aiStack_3c[civ] = aiStack_60[civ];
  }
  for (unit = 0; unit < game.num_units; unit++) {
    if (units[unit].id != 0) {
      y5 = units[unit].y;
      civ2 = units[unit].owner;
      aiStack_3c[civ2] = (int)units[unit].x;
      aiStack_60[civ2] = (int)y5;
    }
  }
  civ = 1;
  do {
    if (7 < civ) {
      game.turn = ((short)param_1 * 4 + 4) * 5 + 1;
      return;
    }
    x3 = aiStack_3c[civ];
    y = aiStack_60[civ];
    iVar5 = map_in_bounds(x3,y);
    if (iVar5 != 0) {
      civ_give_advance(civ,0x24,0,0,1);
      civ_give_advance(civ,9,0,0,1);
      civ_give_advance(civ,1,0,0,1);
      civ_give_advance(civ,8,0,0,1);
      civs[civ].num_advances = 4;
      if (param_1 != 0) {
        for (local_14 = 0; local_14 < 3; local_14++) {
          civ_research_complete(civ,0);
          civs[civ].num_advances++;
        }
      }
      city = city_create(x3,y,civ);
      if (-1 < city) {
        iVar6 = _rand();
        civs[civ].gold = (iVar6 % 0x32 + 0x19) * (param_1 + 1);
        if (param_1 == 0) {
          cities[city].size = 3;
        }
        else {
          cities[city].size = 5;
        }
        unit3 = tile_first_unit(x3,y);
        iVar9 = unit_stack_sum(unit3,2);
        if (1 < iVar9) {
          local_8c = (i8)city;
          units[unit3].home_city = local_8c;
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
        iVar11 = civ_has_advance(civ,0x57);
        unit_create(0x10 - (uint)(iVar11 == 0),civ3,x,unit2);
        if (param_1 != 0) {
          civ4 = civ;
          x = x3;
          unit2 = y;
          iVar11 = civ_has_advance(civ,0x40);
          unit_create(0x11 - (uint)(iVar11 == 0),civ4,x,unit2);
        }
        city_set_improvement(city,4,1);
        if (param_1 != 0) {
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
        accel_start_develop_city(city,(-(uint)(param_1 == 0) & 0xfffffffe) + 4);
        if (param_1 != 0) {
          local_c = -1;
          local_94 = -1;
          unit2 = tile_landmass(x3,y);
          for (local_14 = 0; local_14 < 8; local_14++) {
            x = map_wrap_x((char)(&dir_dx_table)[local_14] * 5 + x3);
            y3 = (char)(&dir_dy_table)[local_14] * 5 + y;
            iVar11 = map_in_bounds(x,y3);
            if (((iVar11 != 0) && (iVar11 = tile_is_ocean(x,y3), iVar11 == 0)) &&
               (iVar11 = tile_landmass(x,y3), iVar11 == unit2)) {
              city_find_nearest(x,y3,-1,0xffffffff,-1);
              for (unit = 0; unit < game.num_units; unit++) {
                if (((units[unit].id != 0) &&
                    (iVar11 = tile_city_owner((int)units[unit].x,(int)units[unit].y),
                    iVar11 < 0)) &&
                   (local_18 = map_distance_diag((int)units[unit].x,(int)units[unit].y,
                                                  x,y3), local_18 < nearest_city_dist)) {
                  nearest_city_dist = local_18;
                }
              }
              if (4 < local_18) {
                local_8 = 0;
                bVar4 = tile_terrain(x,y3);
                local_40 = (uint)bVar4;
                if (local_40 == 2) {
                  local_8 = 4;
                }
                if (local_40 == 1) {
                  local_8 = 2;
                }
                if (local_8 != 0) {
                  pbVar13 = (byte *)tile_at(x,y3);
                  if ((*pbVar13 & 0x80) != 0) {
                    local_8++;
                  }
                  if (local_c < local_8) {
                    local_c = local_8;
                    local_94 = local_14;
                    y4 = y3;
                    x4 = x;
                  }
                }
              }
            }
          }
          if (local_94 < 0) {
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
            uVar14 = _rand();
            uVar16 = (int)uVar14 >> 0x1f;
            uVar14 = (uVar14 ^ uVar16) - uVar16 & 1 ^ uVar16;
            unit2 = unit_create(3 - (uint)(uVar14 == uVar16),civ,x4,y4);
            units[unit2].orders = 2;
            unit2 = unit_create((uVar14 == uVar16) + 3,civ,x4,y4);
            units[unit2].orders = 2;
            unit_create(0xf,civ,x4,y4);
            accel_start_develop_city(city2,2);
            x2 = (int)cities[city2].x;
            y2 = (int)cities[city2].y;
            local_88 = 0;
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
                     (uVar14 = tile_improvements(x2,y2), (uVar14 & 0x10) == 0)) &&
                    ((pbVar13 = (byte *)tile_at(x2,y2), (*pbVar13 & 0x80) == 0 ||
                     (unit2 = civ_has_advance(civ,7), unit2 != 0)))) &&
                   ((unit2 = tile_city_or_unit_owner(x2,y2), unit2 < 0 &&
                    (unit2 = tile_owner_at_peace(x2,y2,civ), unit2 < 0)))) {
                  tile_set_improvements(x2,y2,0x10,1,1);
                  tile_update_known(x2,y2,civ);
                }
                local_88++;
              } while (local_88 < 0x32);
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
#undef local_94
#undef y4
#undef local_8c
#undef local_88
#undef unit_type
#undef x4
#undef y2
#undef x2
#undef aiStack_60
#undef local_40
#undef aiStack_3c
#undef y3
#undef local_18
#undef local_14
#undef city2
#undef local_c
#undef local_8

/* 004aa9c0 auto */
#define SCHAR_00h_0064bc1a (*(schar *)((u8 *)&g.d_0064bc1a))
#define SCHAR_00h_0064bc1c (*(schar *)((u8 *)&g.d_0064bc1c))
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define prefs_game_options (*(uint *)((u8 *)&g.d_0064bc1e))
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
#define _SCHAR_00h_0064bc1a (*(i16 *)((u8 *)&g.d_0064bc1a))
#define _SCHAR_00h_0064bc1c (*(i16 *)((u8 *)&g.d_0064bc1c))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl game_init_new(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  scenario_reset_params();
  destroyed_civs_clear();
  for (leader = 0; leader < 8; leader++) {
    *(i32 *)(&DAT_00655364 + leader * 0x10) = 0;
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
  game.field_06 = 0;
  game.message_options = prefs_message_options;
  game.field_0c = 0;
  moving_units_mode = 1;
  game.num_units = 0;
  game.num_cities = 0;
  game.active_unit = 0;
  game.turn_civ = '\0';
  game.field_34 = 0;
  game.reveal_map = '\0';
  game.view_civ = -1;
  game.polluted_tiles = 0;
  game.warming_counter = '\0';
  game.global_warmings = '\0';
  game.field_28 = 0;
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
  iVar1 = _rand();
  game.next_history_turn = (i16)(iVar1 % 0x32);
  for (leader = 0; leader < 0x96; leader++) {
    for (local_c = 0; local_c < 8; local_c++) {
      (&power_graph_history)[leader * 8 + local_c] = 0;
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
  iVar1 = bits_count8((uint)game.human_players);
  if (iVar1 == 1) {
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
#undef local_c
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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl diffeng_alloc_mirror(void)

{
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (diffeng_mirror_buf != 0) {
    diffeng_free_mirror();
  }
  diffeng_mirror_size = 0;
  for (local_8 = 0; local_8 < 0x17; local_8++) {
    diffeng_mirror_size += (&diffeng_section_padded_sizes)[local_8 * 6];
  }
  if ((diffeng_mirror_size & 3) != 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d0f0, ((u8 *)&g.d_0062d0f0)),ADDR(0x62d0c8, ((u8 *)&g.d_0062d0c8)),0x22);
  }
  diffeng_mirror_buf = (iptr)operator_new(diffeng_mirror_size);
  if ((void *)diffeng_mirror_buf == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    _memset((void *)diffeng_mirror_buf,0,diffeng_mirror_size);
    sVar1 = diffeng_client_mirror_size;
    if (net_host_flag != '\0') {
      sVar1 = diffeng_mirror_size;
    }
    diffeng_mirror_end = sVar1 + diffeng_mirror_buf;
    diffeng_copy_to_mirror();
    uVar2 = 1;
  }
  return uVar2;
}
#undef diffeng_mirror_end
#undef diffeng_mirror_size
#undef net_host_flag
#undef local_8

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
#define _DAT_00679fec (*(i32 *)((u8 *)&g.d_00679fec))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl diffeng_copy_to_mirror(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = diffeng_mirror_buf;
  for (local_c = 0; local_c < 0x17; local_c++) {
    FUN_005f2110(local_8,(&diffeng_section_ptrs)[local_c * 6],
                 *(i32 *)(&diffeng_sections + local_c * 0x18));
    local_8 += (&diffeng_section_padded_sizes)[local_c * 6];
  }
  diffeng_scan_ptr = diffeng_mirror_buf;
  diffeng_scan_section = 0;
  _DAT_00679fec = 0;
  return;
}
#undef diffeng_scan_ptr
#undef diffeng_scan_section
#undef _DAT_00679fec
#undef local_c
#undef local_8

/* 004b0ad0 auto */
#define diffeng_mirror_size (*(uint *)((u8 *)&g.d_0067a400))
#define diffeng_scan_ptr (*(uint * *)((u8 *)&g.d_00679fe8))
#define diffeng_scan_section (*(i32 *)((u8 *)&g.d_0067a404))
#define _DAT_00679fec (*(i32 *)((u8 *)&g.d_00679fec))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl diffeng_invalidate_mirror(void)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  diffeng_copy_to_mirror();
  diffeng_scan_ptr = (uint *)diffeng_mirror_buf;
  uVar1 = diffeng_mirror_size >> 2;
  for (local_c = 0; local_c < uVar1; local_c++) {
    *diffeng_scan_ptr = ~*diffeng_scan_ptr;
    diffeng_scan_ptr++;
  }
  diffeng_scan_ptr = (uint *)diffeng_mirror_buf;
  diffeng_scan_section = 0;
  _DAT_00679fec = 0;
  return;
}
#undef diffeng_mirror_size
#undef diffeng_scan_ptr
#undef diffeng_scan_section
#undef _DAT_00679fec
#undef local_c

/* 004b14a4 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl diffeng_total_size(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 0; local_c < 0x18; local_c++) {
    if (local_c == 5) {
      local_8 = game.num_units * 0x20 + local_8;
    }
    else if (local_c == 6) {
      local_8 = game.num_cities * 0x58 + local_8;
    }
    else {
      local_8 += *(int *)(&diffeng_sections + local_c * 0x18);
    }
  }
  return local_8 + 0x1e0;
}
#undef local_c
#undef local_8

/* 004b153c auto */
#define diffeng_civ_names_section (*(int *)((u8 *)&g.d_0067a440))
#define diffeng_civ_view_section (*(int *)((u8 *)&g.d_0067a518))
#define diffeng_civs_section (*(int *)((u8 *)&g.d_0067a458))
#define diffeng_events_section (*(int *)((u8 *)&g.d_0067a638))
#define diffeng_game_section (*(int *)((u8 *)&g.d_0067a428))
#define diffeng_leaders_section (*(int *)((u8 *)&g.d_0067a4b8))
#define diffeng_scenario_section (*(int *)((u8 *)&g.d_0067a4e8))
#define _DAT_0067a434 (*(i32 *)((u8 *)&g.d_0067a434))
#define _DAT_0067a44c (*(i32 *)((u8 *)&g.d_0067a44c))
#define _DAT_0067a464 (*(i32 *)((u8 *)&g.d_0067a464))
#define _DAT_0067a4c4 (*(i32 *)((u8 *)&g.d_0067a4c4))
#define _DAT_0067a4f4 (*(i32 *)((u8 *)&g.d_0067a4f4))
#define _DAT_0067a524 (*(i32 *)((u8 *)&g.d_0067a524))
#define _DAT_0067a644 (*(i32 *)((u8 *)&g.d_0067a644))
#define local_14 (*(i32 (*)[2])(frame_ + FRAME_OFF(4)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl diffeng_build_civ_image(iptr param_1)

{
  void *pvVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14[0] = 0;
  local_c = diffeng_game_section + diffeng_leaders_section + diffeng_civs_section + diffeng_civ_names_section + diffeng_scenario_section + diffeng_civ_view_section
            + diffeng_events_section + 0x8c;
  if ((int)local_c < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d218, ((u8 *)&g.d_0062d218)),ADDR(0x62d1f0, ((u8 *)&g.d_0062d1f0)),0x226);
  }
  pvVar1 = operator_new(local_c);
  *(void **)param_1 = pvVar1;
  local_8 = *(int *)param_1;
  if (local_8 == 0) {
    dbg_log(ADDR(0x62d224, ((u8 *)&g.d_0062d224)));
    uVar2 = 0;
  }
  else {
    _DAT_0067a434 = mem_checksum(diffeng_game_data,diffeng_game_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a428, ((u8 *)&g.d_0067a428)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_game_data,diffeng_game_section);
    _DAT_0067a4c4 = mem_checksum(diffeng_leaders_data,diffeng_leaders_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a4b8, ((u8 *)&g.d_0067a4b8)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_leaders_data,diffeng_leaders_section);
    _DAT_0067a464 = mem_checksum(diffeng_civs_data,diffeng_civs_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a458, ((u8 *)&g.d_0067a458)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_civs_data,diffeng_civs_section);
    _DAT_0067a44c = mem_checksum(diffeng_civ_names_data,diffeng_civ_names_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a440, ((u8 *)&g.d_0067a440)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_civ_names_data,diffeng_civ_names_section);
    _DAT_0067a4f4 = mem_checksum(diffeng_scenario_data,diffeng_scenario_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a4e8, ((u8 *)&g.d_0067a4e8)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_scenario_data,diffeng_scenario_section);
    _DAT_0067a524 = mem_checksum(diffeng_civ_view_data,diffeng_civ_view_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a518, ((u8 *)&g.d_0067a518)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_civ_view_data,diffeng_civ_view_section);
    _DAT_0067a644 = mem_checksum(diffeng_events_data,diffeng_events_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a638, ((u8 *)&g.d_0067a638)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_events_data,diffeng_events_section);
    uVar2 = mem_rle_compress(param_1,local_14[0]);
  }
  return uVar2;
}
#undef diffeng_civ_names_section
#undef diffeng_civ_view_section
#undef diffeng_civs_section
#undef diffeng_events_section
#undef diffeng_game_section
#undef diffeng_leaders_section
#undef diffeng_scenario_section
#undef _DAT_0067a434
#undef _DAT_0067a44c
#undef _DAT_0067a464
#undef _DAT_0067a4c4
#undef _DAT_0067a4f4
#undef _DAT_0067a524
#undef _DAT_0067a644
#undef local_14
#undef local_c
#undef local_8

/* 004b187f auto */
void __cdecl diffeng_buf_append(int param_1,iptr param_2,int param_3,iptr param_4,int param_5)

{
  if (param_3 < *(int *)param_2 + param_5) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d294, ((u8 *)&g.d_0062d294)),ADDR(0x62d26c, ((u8 *)&g.d_0062d26c)),0x20d);
  }
  FUN_005f2110(*(int *)param_2 + param_1,param_4,param_5);
  *(int *)param_2 = *(int *)param_2 + param_5;
  return;
}

/* 004b18e1 auto */
#define diffeng_game_section (*(int *)((u8 *)&g.d_0067a428))
#define diffeng_map_header_section (*(int *)((u8 *)&g.d_0067a530))
#define _DAT_0067a434 (*(i32 *)((u8 *)&g.d_0067a434))
#define _DAT_0067a53c (*(i32 *)((u8 *)&g.d_0067a53c))
#define local_14 (*(i32 (*)[2])(frame_ + FRAME_OFF(4)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl diffeng_build_map_header_image(iptr param_1)

{
  void *pvVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14[0] = 0;
  local_c = diffeng_game_section + 0x28 + diffeng_map_header_section;
  pvVar1 = operator_new(local_c);
  *(void **)param_1 = pvVar1;
  local_8 = *(int *)param_1;
  if (local_8 == 0) {
    dbg_log(ADDR(0x62d2b4, ((u8 *)&g.d_0062d2b4)));
    uVar2 = 0;
  }
  else {
    _DAT_0067a434 = mem_checksum(diffeng_game_data,diffeng_game_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a428, ((u8 *)&g.d_0067a428)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_game_data,diffeng_game_section);
    _DAT_0067a53c = mem_checksum(diffeng_map_header_data,diffeng_map_header_section);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,ADDR(0x67a530, ((u8 *)&g.d_0067a530)),0x14);
    diffeng_buf_append(local_8,(iptr)local_14,local_c,diffeng_map_header_data,diffeng_map_header_section);
    uVar2 = mem_rle_compress(param_1,local_14[0]);
  }
  return uVar2;
}
#undef diffeng_game_section
#undef diffeng_map_header_section
#undef _DAT_0067a434
#undef _DAT_0067a53c
#undef local_14
#undef local_c
#undef local_8

/* 004b1a15 auto */
#define local_3c (*(void * *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_2c (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int (*)[5])(frame_ + FRAME_OFF(28)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
i32 __cdecl diffeng_build_full_image(iptr param_1)

{
  uint uVar1;
  void *pvVar2;
  i32 uVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = diffeng_total_size();
  if ((int)uVar1 < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d324, ((u8 *)&g.d_0062d324)),ADDR(0x62d2fc, ((u8 *)&g.d_0062d2fc)),0x27f);
  }
  pvVar2 = operator_new(uVar1);
  *(void **)param_1 = pvVar2;
  local_8 = *(int *)param_1;
  if (local_8 == 0) {
    dbg_log(ADDR(0x62d32c, ((u8 *)&g.d_0062d32c)));
    local_2c = 0;
  }
  else {
    local_c = 0;
    for (local_28 = 0; local_28 < 0x18; local_28++) {
      FUN_005f2110(local_24,&diffeng_sections + local_28 * 0x18,0x14);
      if (local_28 == 5) {
        local_24[0] = (int)game.num_units << 5;
      }
      else if (local_28 == 6) {
        local_24[0] = game.num_cities * 0x58;
      }
      uVar3 = mem_checksum((&diffeng_section_ptrs)[local_28 * 6],local_24[0]);
      *(i32 *)(&diffeng_section_checksums + local_28 * 0x18) = uVar3;
      diffeng_buf_append(local_8,(iptr)&local_c,uVar1,(iptr)local_24,0x14);
      diffeng_buf_append(local_8,(iptr)&local_c,uVar1,(&diffeng_section_ptrs)[local_28 * 6],local_24[0]);
    }
    local_3c = operator_new(local_c);
    if (local_3c == (void *)0x0) {
      dbg_log(ADDR(0x62d374, ((u8 *)&g.d_0062d374)));
      local_2c = 0;
    }
    else {
      local_38 = local_c + (int)local_3c;
      FUN_005f2110(local_3c,local_8,local_c);
      local_34 = *(i32 *)param_1;
      local_30 = local_c + *(int *)param_1;
      iVar4 = diffeng_rle_encode((iptr)&local_3c);
      if (iVar4 == 0) {
        local_10 = 0xffffffff;
        local_2c = local_10;
      }
      else {
        uVar3 = FUN_005f4900(*(i32 *)param_1,local_2c);
        *(i32 *)param_1 = uVar3;
      }
    }
  }
  return local_2c;
}
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_10
#undef local_c
#undef local_8

/* 004b1c11 auto */
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(int (*)[5])(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(i32 (*)[2])(frame_ + FRAME_OFF(32)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
i32 __cdecl diffeng_build_delta_image(iptr param_1)

{
  uint uVar1;
  void *pvVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = diffeng_total_size();
  if ((int)uVar1 < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d3e4, ((u8 *)&g.d_0062d3e4)),ADDR(0x62d3bc, ((u8 *)&g.d_0062d3bc)),0x2c6);
  }
  pvVar2 = operator_new(uVar1);
  *(void **)param_1 = pvVar2;
  local_8 = *(int *)param_1;
  if (local_8 == 0) {
    dbg_log(ADDR(0x62d3ec, ((u8 *)&g.d_0062d3ec)));
    uVar3 = 0;
  }
  else {
    local_10[0] = 0;
    for (local_2c = 0; local_2c < 0x18; local_2c++) {
      FUN_005f2110(local_28,&diffeng_sections + local_2c * 0x18,0x14);
      if (local_2c == 5) {
        local_28[0] = (int)game.num_units << 5;
      }
      else if (local_2c == 6) {
        local_28[0] = game.num_cities * 0x58;
      }
      local_14 = mem_checksum((&diffeng_section_ptrs)[local_2c * 6],local_28[0]);
      if ((*(int *)(&diffeng_section_checksums + local_2c * 0x18) != local_14) && (local_28[0] != 0)) {
        *(int *)(&diffeng_section_checksums + local_2c * 0x18) = local_14;
        diffeng_buf_append(local_8,(iptr)local_10,uVar1,(iptr)local_28,0x14);
        diffeng_buf_append(local_8,(iptr)local_10,uVar1,(&diffeng_section_ptrs)[local_2c * 6],local_28[0]);
      }
    }
    uVar3 = FUN_005f4900(*(i32 *)param_1,local_10[0]);
    *(i32 *)param_1 = uVar3;
    if (*(int *)param_1 == 0) {
      dbg_log(ADDR(0x62d430, ((u8 *)&g.d_0062d430)));
      uVar3 = 0;
    }
    else {
      uVar3 = mem_rle_compress(param_1,local_10[0]);
    }
  }
  return uVar3;
}
#undef local_2c
#undef local_28
#undef local_14
#undef local_10
#undef local_8

/* 004b1de3 auto */
#define local_30 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(void * *)(frame_ + FRAME_OFF(8)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_1c (*(u32 *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(u16 *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(int * *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(40)))
void __cdecl diffeng_apply_image(int *param_1,char param_2)

{
  int *piVar1;
  int *piVar2;
  size_t sVar3;
  int iVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d4a0, ((u8 *)&g.d_0062d4a0)),ADDR(0x62d478, ((u8 *)&g.d_0062d478)),0x2fc);
  }
  local_1c = game.game_options;
  local_18 = game.message_options;
  if (diffeng_section_ptrs == 0) {
    diffeng_register_blocks();
  }
  if (nm_full_gamestate_count == 0) {
    if (param_2 != '\0') {
      local_c = mem_rle_decompress((iptr)param_1);
    }
    local_8 = (int *)*param_1;
    local_c = __msize((void *)*param_1);
  }
  else {
    local_30 = *param_1;
    sVar3 = __msize((void *)*param_1);
    local_2c = local_30 + sVar3;
    local_c = diffeng_rle_decoded_size((iptr)&local_30);
    local_28 = operator_new(local_c);
    if (local_28 == (void *)0x0) {
      dbg_log(ADDR(0x62d4b4, ((u8 *)&g.d_0062d4b4)));
      return;
    }
    local_24 = (int)local_28 + local_c;
    iVar4 = diffeng_rle_decode((iptr)&local_30);
    if (iVar4 == 0) {
      dbg_log(ADDR(0x62d4fc, ((u8 *)&g.d_0062d4fc)));
      return;
    }
    operator_delete((void *)*param_1);
    *param_1 = (int)local_28;
    local_8 = (int *)*param_1;
  }
  local_10 = 0;
  while (local_10 < (int)local_c) {
    local_14 = local_8;
    piVar2 = local_8 + 5;
    local_10 = *local_8 + local_10 + 0x14;
    if ((local_8[2] < 0) || (piVar1 = local_8 + 2, local_8 = piVar2, 0x17 < *piVar1)) {
      local_8 = piVar2;
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d554, ((u8 *)&g.d_0062d554)),ADDR(0x62d52c, ((u8 *)&g.d_0062d52c)),0x338);
    }
    FUN_005f2110((&diffeng_section_ptrs)[local_14[2] * 6],local_8,*local_14);
    uVar5 = mem_checksum((iptr)local_8,*local_14);
    *(i32 *)(&diffeng_section_checksums + local_14[2] * 0x18) = uVar5;
    local_8 = (int *)((int)local_8 + *local_14);
  }
  game.message_options = local_18;
  game.game_options = local_1c;
  return;
}
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004b2010 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl diffeng_apply_map_header_image(int *param_1,char param_2)

{
  u32 uVar1;
  u16 uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d5b0, ((u8 *)&g.d_0062d5b0)),ADDR(0x62d588, ((u8 *)&g.d_0062d588)),0x34b);
  }
  uVar2 = game.message_options;
  uVar1 = game.game_options;
  if (param_2 != '\0') {
    mem_rle_decompress((iptr)param_1);
  }
  local_8 = *param_1;
  map_free();
  iVar3 = diffeng_read_block((iptr)&local_8);
  if (iVar3 != 1) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d5ec, ((u8 *)&g.d_0062d5ec)),ADDR(0x62d5c4, ((u8 *)&g.d_0062d5c4)),0x35a);
  }
  iVar3 = diffeng_read_block((iptr)&local_8);
  if (iVar3 != 0xc) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d628, ((u8 *)&g.d_0062d628)),ADDR(0x62d600, ((u8 *)&g.d_0062d600)),0x35d);
  }
  game.game_options = uVar1;
  game.message_options = uVar2;
  map_alloc();
  diffeng_register_blocks();
  diffeng_alloc_mirror();
  return;
}
#undef local_8

/* 004b2123 auto */
int __cdecl diffeng_read_block(iptr param_1)

{
  int *piVar1;
  i32 uVar2;
  
  piVar1 = *(int **)param_1;
  *(int *)param_1 = *(int *)param_1 + 0x14;
  if ((piVar1[2] < 0) || (0x17 < piVar1[2])) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d66c, ((u8 *)&g.d_0062d66c)),ADDR(0x62d644, ((u8 *)&g.d_0062d644)),0x36d);
  }
  FUN_005f2110((&diffeng_section_ptrs)[piVar1[2] * 6],*(i32 *)param_1,*piVar1);
  uVar2 = mem_checksum(*(iptr *)param_1,*piVar1);
  *(i32 *)(&diffeng_section_checksums + piVar1[2] * 0x18) = uVar2;
  *(int *)param_1 = *(int *)param_1 + *piVar1;
  return piVar1[2];
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
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
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
  local_c = 0;
  for (local_8 = 0; local_8 < 0x17; local_8++) {
    *(int *)(&diffeng_section_offsets + local_8 * 0x18) = local_c;
    local_c += (&diffeng_section_padded_sizes)[local_8 * 6];
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
#undef local_c
#undef local_8

/* 004b24a2 auto */
#define local_10 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(ushort * *)(frame_ + FRAME_OFF(8)))
int __cdecl diffeng_rle_decoded_size(iptr param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = *(ushort **)param_1;
  local_c = 0;
  while (local_8 < *(ushort **)(param_1 + 4)) {
    local_10 = (uint)*local_8;
    if (local_10 < 0x8000) {
      local_8 = (ushort *)((int)local_8 + 3);
    }
    else {
      local_8 = (ushort *)((int)local_8 + (local_10 & 0x7fff) + 2);
    }
    local_c += (local_10 & 0x7fff);
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 004b251a auto */
#define local_10 (*(ushort * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(void * *)(frame_ + FRAME_OFF(4)))
i32 __cdecl diffeng_rle_decode(iptr param_1)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar3 = diffeng_rle_decoded_size(param_1);
  if ((uint)(*(int *)(param_1 + 0xc) - *(int *)(param_1 + 8)) < uVar3) {
    uVar4 = 0;
  }
  else {
    local_10 = *(ushort **)param_1;
    local_c = *(void **)(param_1 + 8);
    while (local_10 < *(ushort **)(param_1 + 4)) {
      uVar2 = *local_10;
      puVar1 = local_10 + 1;
      if (uVar2 < 0x7fff) {
        local_10 = (ushort *)((int)local_10 + 3);
        _memset(local_c,(int)(short)(ushort)(byte)*puVar1,(uint)uVar2);
      }
      else {
        uVar2 += 0x8000;
        FUN_005f2110(local_c,puVar1,(uint)uVar2);
        local_10 = (ushort *)((int)puVar1 + (uint)uVar2);
      }
      local_c = (void *)((int)local_c + (uint)uVar2);
    }
    *(int *)(param_1 + 0x10) = (int)local_c - *(int *)(param_1 + 8);
    uVar4 = 1;
  }
  return uVar4;
}
#undef local_10
#undef local_c

/* 004b263e auto */
#define local_24 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(char * *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(short * *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(uptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(28)))
i32 __cdecl diffeng_rle_encode(iptr param_1)

{
  short *psVar1;
  uint uVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_1c = *(short **)(param_1 + 8);
  local_20 = *(char **)param_1;
  local_24 = local_20 + 1;
  uVar2 = *(int *)(param_1 + 4) - *(int *)param_1;
  local_c = 0;
  uVar3 = *(int *)(param_1 + 0xc) - *(int *)(param_1 + 8);
  do {
    if (*(char **)(param_1 + 4) <= local_20) {
      *(uint *)(param_1 + 0x10) = local_c;
      return 1;
    }
    for (; (local_24 < *(char **)(param_1 + 4) && (*local_24 == *local_20)); local_24 = local_24 + 1
        ) {
    }
    local_14 = (int)local_24 - (int)local_20;
    if (3 < local_14) {
      while (psVar1 = local_1c, local_14 != 0) {
        if ((uVar3 < local_c + 2) || (uVar2 <= local_c + 2)) {
          return 0;
        }
        if (local_14 < 0x8000) {
          *local_1c = (short)local_14;
          local_14 = 0;
        }
        else {
          *local_1c = 0x7fff;
          local_14 -= 0x7fff;
        }
        local_1c++;
        local_c += 3;
        if ((uVar3 < local_c) || (uVar2 <= local_c)) {
          return 0;
        }
        *(char *)local_1c = *local_20;
        local_1c = (short *)((int)psVar1 + 3);
      }
      local_20 = local_24;
    }
    for (; (local_24 < *(char **)(param_1 + 4) && (local_24[1] != *local_24));
        local_24 = local_24 + 1) {
    }
    local_14 = (int)local_24 - (int)local_20;
    while (local_14 != 0) {
      local_c += 2;
      if ((uVar3 < local_c) || (uVar2 <= local_c)) {
        return 0;
      }
      if (local_14 < 0x8000) {
        *local_1c = (short)local_14 - 0x8000;
        local_18 = local_14;
        local_14 = 0;
      }
      else {
        *local_1c = -1;
        local_18 = 0x7fff;
        local_14 -= 0x7fff;
      }
      local_1c++;
      local_c += local_18;
      if ((uVar3 < local_c) || (uVar2 <= local_c)) {
        return 0;
      }
      FUN_005f2110(local_1c,local_20,local_18);
      local_1c = (short *)((int)local_1c + local_18);
      local_20 += local_18;
    }
  } while( true );
}
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_c

/* 004b3080 auto */
void __thiscall diffeng_section_init(DiffEngSection *this,iptr param_1,u32 param_2,u32 param_3)

{
  this->data_ptr = param_1;
  this->data_size = param_2;
  this->section_id = param_3;
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
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
int __cdecl events_alloc_string(char *param_1,iptr param_2,uint param_3)

{
  size_t sVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar1 = _strlen(param_1);
  if ((int)param_3 < (int)(sVar1 + 1)) {
    sVar1 = _strlen(param_1);
    local_c = sVar1 + 1;
  }
  else {
    local_c = param_3;
  }
  iVar2 = memblock_alloc(param_2 + 0x2f4,local_c);
  if (iVar2 == 0) {
    error_report(0xfffffff7,3,0,0,0);
  }
  FUN_005f22d0(iVar2,param_1);
  return iVar2;
}
#undef local_c

/* 004ce98e auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl events_copy(iptr param_1,iptr param_2)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_c = *(iptr *)(param_2 + 0x30c); local_c != 0; local_c = *(iptr *)(local_c + 0x1bc)) {
    iVar1 = events_alloc((ScenarioEvents *)param_1);
    if (iVar1 == 0) {
      error_report(0xfffffff7,3,0,0,0);
    }
    FUN_005f2110(iVar1,local_c,0x1bc);
  }
  local_c = *(iptr *)(param_2 + 0x30c);
  local_10 = *(uptr *)(param_1 + 0x30c);
  do {
    if (local_c == 0) {
      return;
    }
    if (*(int *)(local_c + 8) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 8),param_1,0xf);
      *(i32 *)(local_10 + 8) = uVar2;
      if (*(int *)(local_10 + 8) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x10) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x10),param_1,0x18);
      *(i32 *)(local_10 + 0x10) = uVar2;
      if (*(int *)(local_10 + 0x10) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x14) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x14),param_1,0x18);
      *(i32 *)(local_10 + 0x14) = uVar2;
      if (*(int *)(local_10 + 0x14) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x20) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x20),param_1,0x18);
      *(i32 *)(local_10 + 0x20) = uVar2;
      if (*(int *)(local_10 + 0x20) == 0) {
        return;
      }
    }
    for (local_8 = 0; (local_8 < 0x14 && (*(int *)(local_c + 0x38 + local_8 * 4) != 0));
        local_8 = local_8 + 1) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x38 + local_8 * 4),param_1,1);
      *(i32 *)(local_10 + 0x38 + local_8 * 4) = uVar2;
      if (*(int *)(local_10 + 0x38 + local_8 * 4) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x88) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x88),param_1,0x18);
      *(i32 *)(local_10 + 0x88) = uVar2;
      if (*(int *)(local_10 + 0x88) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x90) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x90),param_1,0xf);
      *(i32 *)(local_10 + 0x90) = uVar2;
      if (*(int *)(local_10 + 0x90) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0xc4) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0xc4),param_1,0x18);
      *(i32 *)(local_10 + 0xc4) = uVar2;
      if (*(int *)(local_10 + 0xc4) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0xcc) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0xcc),param_1,0x18);
      *(i32 *)(local_10 + 0xcc) = uVar2;
      if (*(int *)(local_10 + 0xcc) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0xd4) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0xd4),param_1,0x18);
      *(i32 *)(local_10 + 0xd4) = uVar2;
      if (*(int *)(local_10 + 0xd4) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0xdc) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0xdc),param_1,0xf);
      *(i32 *)(local_10 + 0xdc) = uVar2;
      if (*(int *)(local_10 + 0xdc) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x13c) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x13c),param_1,0x18);
      *(i32 *)(local_10 + 0x13c) = uVar2;
      if (*(int *)(local_10 + 0x13c) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x140) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x140),param_1,0x18);
      *(i32 *)(local_10 + 0x140) = uVar2;
      if (*(int *)(local_10 + 0x140) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x148) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x148),param_1,0xf);
      *(i32 *)(local_10 + 0x148) = uVar2;
      if (*(int *)(local_10 + 0x148) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x174) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x174),param_1,0x18);
      *(i32 *)(local_10 + 0x174) = uVar2;
      if (*(int *)(local_10 + 0x174) == 0) {
        return;
      }
    }
    if (*(int *)(local_c + 0x184) != 0) {
      uVar2 = events_alloc_string(*(i32 *)(local_c + 0x184),param_1,1);
      *(i32 *)(local_10 + 0x184) = uVar2;
      if (*(int *)(local_10 + 0x184) == 0) {
        return;
      }
    }
    local_c = *(iptr *)(local_c + 0x1bc);
    local_10 = *(uptr *)(local_10 + 0x1bc);
  } while( true );
}
#undef local_10
#undef local_c
#undef local_8

/* 004cef35 auto */
#define local_320 (*(ScenarioEvents *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl events_compact(void)

{
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  events_ctor(&local_320,50000);
  local_8 = 0;
  events_reset(&local_320,50000);
  events_copy((iptr)&local_320,ADDR(0x64b690, ((u8 *)&g.d_0064b690)));
  events_reset((ScenarioEvents *)&scenario_events,50000);
  events_copy(ADDR(0x64b690, ((u8 *)&g.d_0064b690)),(iptr)&local_320);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004cefc5 */ { events_dtor((C_0040bc40_28 *)((iptr)&local_320)); }
  return;
}
#undef local_320
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004cefe9 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl events_rename_unit_refs(char *param_1,iptr param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = events_list_head; local_c != 0; local_c = *(iptr *)(local_c + 0x1bc)) {
    if (*(int *)(local_c + 8) != 0) {
      iVar1 = _strcmp(*(char **)(local_c + 8),param_1);
      if (iVar1 == 0) {
        _strncpy(*(char **)(local_c + 8),(char *)param_2,0xf);
        local_8++;
      }
    }
    if (*(int *)(local_c + 0x90) != 0) {
      iVar1 = _strcmp(*(char **)(local_c + 0x90),param_1);
      if (iVar1 == 0) {
        _strncpy(*(char **)(local_c + 0x90),(char *)param_2,0xf);
        local_8++;
      }
    }
    if (*(int *)(local_c + 0xdc) != 0) {
      iVar1 = _strcmp(*(char **)(local_c + 0xdc),param_1);
      if (iVar1 == 0) {
        _strncpy(*(char **)(local_c + 0xdc),(char *)param_2,0xf);
        local_8++;
      }
    }
    if (*(int *)(local_c + 0x148) != 0) {
      iVar1 = _strcmp(*(char **)(local_c + 0x148),param_1);
      if (iVar1 == 0) {
        _strncpy(*(char **)(local_c + 0x148),(char *)param_2,0xf);
        local_8++;
      }
    }
  }
  return local_8;
}
#undef local_c
#undef local_8

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
#define local_8 (*(u8 *)(frame_ + FRAME_OFF(0)))
void __cdecl game_quit_or_retire(int param_1)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((game.multiplayer < 3) || (net_host_handoff_stage == '\0')) {
    if (param_1 == 0) {
      iVar1 = popup_game_with_sprite(ADDR(0x62ec50, ((u8 *)&g.d_0062ec50)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (iVar1 == 0) {
        return;
      }
    }
    else {
      iVar1 = popup_game_with_sprite(ADDR(0x62ec40, ((u8 *)&g.d_0062ec40)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (iVar1 == 0) {
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
        local_8 = game.human_players;
        game.human_players = hotseat_human_players;
      }
      if (2 < game.multiplayer) {
        if (mp_turn_timer_handle != 0) {
          game_timer_destroy(mp_turn_timer_handle);
          mp_turn_timer_handle = 0;
        }
        parley_wnd_close();
        chat_wnd_close();
        iVar2 = civ_get_adjective(human_civ);
        text_set_string_arg(0,iVar2);
        iVar2 = civ_leader_title(human_civ);
        text_set_string_arg(1,iVar2);
        iVar2 = civ_leader_name(human_civ);
        text_set_string_arg(2,iVar2);
        iVar2 = civ_name_plural(human_civ);
        text_set_string_arg(3,iVar2);
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
        game.human_players = local_8;
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
#undef local_8

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
i32 __cdecl events_parse_civ(iptr param_1)

{
  int iVar1;
  i32 uVar2;
  char *_Str2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = __strcmpi((char *)param_1,s_ANYBODY_0062f1f4);
  if (iVar1 == 0) {
    uVar2 = 0xfffffffe;
  }
  else {
    iVar1 = __strcmpi((char *)param_1,s_TRIGGERATTACKER_0062f1fc);
    if (iVar1 == 0) {
      uVar2 = 0xfffffffd;
    }
    else {
      iVar1 = __strcmpi((char *)param_1,s_TRIGGERDEFENDER_0062f20c);
      if (iVar1 == 0) {
        uVar2 = 0xfffffffc;
      }
      else {
        iVar1 = __strcmpi((char *)param_1,s_TRIGGERRECEIVER_0062f21c);
        if (iVar1 == 0) {
          uVar2 = 0xfffffffc;
        }
        else {
          for (civ = 0; civ < 8; civ++) {
            _Str2 = (char *)civ_name_plural(civ);
            iVar1 = __strcmpi((char *)param_1,_Str2);
            if (iVar1 == 0) {
              return civ;
            }
          }
          if (events_parse_verbose != 0) {
            _printf(s_Could_not_find__s__check_spellin_0062f22c,param_1);
          }
          uVar2 = 0xffffffff;
        }
      }
    }
  }
  return uVar2;
}
#undef civ

/* 004fa359 auto */
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl events_parse_unit_type(iptr param_1)

{
  int iVar1;
  i32 uVar2;
  char *_Str2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = __strcmpi((char *)param_1,s_ANYUNIT_0062f250);
  if (iVar1 == 0) {
    uVar2 = 0xfffffffe;
  }
  else {
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      _Str2 = (char *)label_string(unit_types[unit_type].name);
      iVar1 = __strcmpi((char *)param_1,_Str2);
      if (iVar1 == 0) {
        return unit_type;
      }
    }
    if (events_parse_verbose != 0) {
      _printf(s_Could_not_find_unit__s__check_sp_0062f258,param_1);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
#undef unit_type

/* 004fa47e auto */
void __thiscall events_init_string_pool(C_0040bc40_28 *this,uint param_1)

{
  memblock_free((iptr)&this[0x12].field_24);
  memblock_init((iptr)&this[0x12].field_24,0xc,param_1);
  return;
}

/* 004fa4be auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
ScenarioEvents * __thiscall events_ctor(ScenarioEvents *this,i32 param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor((Dialog *)this,0x4000);
  local_8 = 0;
  memblock_ctor((MemBlock *)(this->pad_294 + 0x60));
  this->events_pool_valid = '\0';
  this->event_list = 0;
  this->event_count = 0;
  events_reset(this,param_1);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004fa569 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall events_dtor(C_0040bc40_28 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  memblock_free((iptr)&this[0x12].field_24);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004fa5b8 */ { dialog_dtor(*(Dialog **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004fa5d9 auto */
void __thiscall events_reset(ScenarioEvents *this,i32 param_1)

{
  this->event_list = 0;
  this->event_count = 0;
  events_init_string_pool((C_0040bc40_28 *)this,param_1);
  return;
}

/* 004fa617 auto */
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
void * __thiscall events_alloc(ScenarioEvents *this)

{
  void *_Dst;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = this->event_list;
  if (local_8 != 0) {
    for (; *(int *)(local_8 + 0x1bc) != 0; local_8 = *(uptr *)(local_8 + 0x1bc)) {
    }
  }
  _Dst = (void *)memblock_alloc((iptr)(this->pad_294 + 0x60),0x1c4);
  if (_Dst == (void *)0x0) {
    _Dst = (void *)0x0;
  }
  else {
    _memset(_Dst,0,0x1c4);
    if (local_8 == 0) {
      this->event_list = (uptr)_Dst;
      *(i32 *)((int)_Dst + 0x1bc) = 0;
      *(i32 *)((int)_Dst + 0x1c0) = 0;
    }
    else {
      *(void **)(local_8 + 0x1bc) = _Dst;
      *(uptr *)((int)_Dst + 0x1c0) = local_8;
      *(i32 *)((int)_Dst + 0x1bc) = 0;
    }
    this->event_count++;
  }
  return _Dst;
}
#undef local_8

/* 004fa707 auto */
#define local_f4 (*(i8 (*)[240])(frame_ + FRAME_OFF(4)))
i32 __thiscall events_action_play_wave(C_0040bc40_28 *this,iptr param_1)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(248)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((byte)game.game_options & 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x184) != 0) {
      FUN_005f22d0(local_f4,&scenario_dir_path);
      FUN_005f22e0(local_f4,s__SOUND__0062f2b0);
      FUN_005f22e0(local_f4,*(i32 *)(param_1 + 0x184));
      iVar2 = file_exists((iptr)local_f4);
      if (iVar2 == 0) {
        FUN_005f22d0(local_f4,&game_home_dir);
        FUN_005f22e0(local_f4,s__SOUND__0062f2b8);
        FUN_005f22e0(local_f4,*(i32 *)(param_1 + 0x184));
        iVar2 = file_exists((iptr)local_f4);
        if (iVar2 != 0) {
          snd_wave_play((iptr)local_f4,0,0,0);
        }
      }
      else {
        snd_wave_play((iptr)local_f4,0,0,0);
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}
#undef local_f4

/* 004fa82d auto */
#define event_dont_play_wonders (*(i32 *)((u8 *)&g.d_006a9110))
i32 __thiscall events_action_dont_play_wonders(C_0040bc40_28 *this,iptr param_1)

{
  event_dont_play_wonders = 1;
  return 1;
}
#undef event_dont_play_wonders

/* 004fa854 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_action_play_cd(C_0040bc40_28 *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while (local_8 < 10) {
    local_8++;
    local_c = snd_cd_get_track_count();
    if ((((local_c == 0x18) || (local_c == 0x12)) || (local_c == 0xc)) || (local_c == 10)) break;
    snd_cd_close();
  }
  if (((local_c == 10) || (local_c == 0x12)) || ((local_c == 0x18 || (local_c == 0xc)))) {
    if ((*(int *)(param_1 + 0x188) < 2) || (local_c < *(int *)(param_1 + 0x188))) {
      uVar1 = 0;
    }
    else {
      music_play_track(*(i32 *)(param_1 + 0x188),1);
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef local_c
#undef local_8

/* 004fa944 auto */
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall events_action_change_money(C_0040bc40_28 *this,iptr param_1)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0x178) == -3) {
    civ = *(iptr *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 0x178) == -4) {
    civ = *(iptr *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 0x178) == -4) {
    civ = *(iptr *)(param_1 + 0x24);
  }
  else {
    civ = *(iptr *)(param_1 + 0x178);
  }
  if ((civ < 1) || (7 < civ)) {
    uVar1 = 0;
  }
  else if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x17c) + civs[civ].gold;
    if ((iVar2 < 0) || (30000 < iVar2)) {
      if (*(int *)(param_1 + 0x17c) < 0) {
        civs[civ].gold = 0;
      }
      else {
        civs[civ].gold = 30000;
      }
    }
    else {
      civs[civ].gold = iVar2;
    }
    uVar1 = 1;
  }
  return uVar1;
}
#undef civ

/* 004faab0 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_action_text(Dialog *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  dialog_init_default(this);
  for (local_c = 0; local_c < 0x14; local_c++) {
    if (*(int *)(param_1 + 0x38 + local_c * 4) != 0) {
      dialog_add_line
                ((DialogAddLineView *)this,*(iptr *)(param_1 + 0x38 + local_c * 4),0xffffffff,0xffffffff,
                 0xffffffff,0);
      if (2 < game.multiplayer) {
        FUN_005f22d0(&text_string_args + local_8 * 0x104,*(i32 *)(param_1 + 0x38 + local_c * 4));
        local_8++;
      }
    }
  }
  if (autoplay_active == 0) {
    if (2 < game.multiplayer) {
      net_send_text_args(0x4f,0xff,local_8,0,0,0);
    }
    dlg_show_modal(this,0);
  }
  return 1;
}
#undef autoplay_active
#undef local_c
#undef local_8

/* 004faba6 auto */
#define civ2 (*(int *)(frame_ + FRAME_OFF(4)))
#define civ (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_action_make_aggression(C_0040bc40_28 *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0xd0) == -3) {
    civ2 = *(int *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 0xd0) == -4) {
    civ2 = *(int *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 0xd0) == -4) {
    civ2 = *(int *)(param_1 + 0x24);
  }
  else {
    civ2 = *(int *)(param_1 + 0xd0);
  }
  if (*(int *)(param_1 + 200) == -3) {
    civ = *(int *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 200) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 200) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else {
    civ = *(int *)(param_1 + 200);
  }
  if (((civ < 1) || (7 < civ)) ||
     ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    uVar1 = 0;
  }
  else if (((civ2 < 1) || (7 < civ2)) ||
          ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = diplo_force_war(civ2,civ);
  }
  return uVar1;
}
#undef civ2
#undef civ

/* 004fad02 auto */
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
i32 __thiscall events_action_destroy_civ(C_0040bc40_28 *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0x1b0) == -3) {
    civ = *(int *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 0x1b0) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 0x1b0) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else {
    civ = *(int *)(param_1 + 0x1b0);
  }
  if (((civ < 1) || (7 < civ)) ||
     ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    uVar1 = 0;
  }
  else {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
       (human_civ == civ)) {
      game_over_reason = 4;
    }
    civ_eliminate(civ,1,1);
    uVar1 = 1;
  }
  return uVar1;
}
#undef game_over_reason
#undef human_civ
#undef civ

/* 004fadfb auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
i32 __thiscall events_action_give_tech(C_0040bc40_28 *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0x1b8) == -3) {
    civ = *(int *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 0x1b8) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 0x1b8) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else {
    civ = *(int *)(param_1 + 0x1b8);
  }
  if (((civ < 1) || (7 < civ)) ||
     ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    uVar1 = 0;
  }
  else {
    civ_give_advance(civ,*(iptr *)(param_1 + 0x1b4),0,0,0);
    uVar1 = 1;
  }
  return uVar1;
}
#undef civ

/* 004faed4 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(8)))
#define x2 (*(int *)(frame_ + FRAME_OFF(12)))
#define civ (*(uptr *)(frame_ + FRAME_OFF(20)))
#define city (*(iptr *)(frame_ + FRAME_OFF(24)))
i32 __thiscall events_action_create_unit(C_0040bc40_28 *this,iptr param_1)

{
  iptr x;
  iptr y;
  i32 uVar6;
  iptr iVar2;
  iptr iVar4;
  uptr uVar7;
  iptr unit;
  int city2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = 10000;
  y2 = 10000;
  if (*(int *)(param_1 + 0xd8) == -3) {
    civ = *(uptr *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 0xd8) == -4) {
    civ = *(uptr *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 0xd8) == -4) {
    civ = *(uptr *)(param_1 + 0x24);
  }
  else {
    civ = *(uptr *)(param_1 + 0xd8);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
    uVar6 = 0;
  }
  else {
    for (local_1c = 0; y = y2, x = x2, local_1c < *(int *)(param_1 + 0x134);
        local_1c = local_1c + 1) {
      x = *(iptr *)(param_1 + 0xe4 + local_1c * 8);
      y = *(iptr *)(param_1 + 0xe8 + local_1c * 8);
      iVar2 = map_in_bounds(x,y);
      if (iVar2 != 0) {
        if (unit_types[*(int *)(param_1 + 0xe0)].domain == 2) {
          iVar4 = tile_is_ocean(x,y);
          if (iVar4 != 0) break;
          city2 = city_at(x,y);
          if ((city2 != -1) &&
             (city2 = city_at(x,y), (cities[city2].flags & 0x80) != 0)) {
            uVar7 = tile_city_owner(x,y);
joined_r0x004fb11d:
            if (uVar7 == civ) break;
          }
        }
        else {
          city2 = tile_is_ocean(x,y);
          if (((city2 == 0) || (unit_types[*(int *)(param_1 + 0xe0)].domain == 1)) &&
             ((city2 = city_at(x,y), city2 == -1 ||
              (uVar7 = tile_city_owner(x,y), uVar7 == civ)))) {
            city2 = tile_unit_owner(x,y);
            if (city2 != -1) {
              uVar7 = tile_unit_owner(x,y);
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
      uVar6 = 0;
    }
    else {
      unit = unit_create(*(iptr *)(param_1 + 0xe0),civ,x2,y2);
      if (unit == -1) {
        uVar6 = 0;
      }
      else {
        if (*(int *)(param_1 + 0x138) != 0) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        units[unit].home_city = -1;
        if (*(int *)(param_1 + 0x13c) != 0) {
          for (city = 0; city < game.num_cities; city++) {
            if ((cities[city].id != 0) &&
               (city2 = __strcmpi(cities[city].name,*(char **)(param_1 + 0x13c)), city2 == 0)) {
              if ((int)cities[city].owner == civ) {
                units[unit].home_city = (i8)city;
              }
              break;
            }
          }
        }
        uVar6 = 1;
      }
    }
  }
  return uVar6;
}
#undef local_1c
#undef y2
#undef x2
#undef civ
#undef city

/* 004fb29f auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define civ (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int (*)[4])(frame_ + FRAME_OFF(28)))
#define local_14 (*(int (*)[4])(frame_ + FRAME_OFF(44)))
int __thiscall events_action_move_unit(C_0040bc40_28 *this,iptr param_1)

{
  int x;
  int y;
  int iVar3;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0x8c) == -3) {
    civ = *(int *)(param_1 + 0x18);
  }
  else if (*(int *)(param_1 + 0x8c) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else if (*(int *)(param_1 + 0x8c) == -4) {
    civ = *(int *)(param_1 + 0x24);
  }
  else {
    civ = *(int *)(param_1 + 0x8c);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
    local_38 = 0;
  }
  else if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    for (local_34 = 0; local_34 < 4; local_34++) {
      local_14[local_34] = *(int *)(param_1 + 0x9c + local_34 * 8);
      local_24[local_34] = *(int *)(param_1 + 0xa0 + local_34 * 8);
    }
    local_38 = 0;
    unit = (iptr)game.num_units;
    do {
      do {
        do {
          unit--;
          if (unit < 0) {
            return local_38;
          }
        } while ((((units[unit].id == 0) ||
                  ((((*(int *)(param_1 + 0x94) != unit && (*(int *)(param_1 + 0x94) != -2)) ||
                    (units[unit].owner != civ)) ||
                   (('b' < (char)unit_types[units[unit].type].attack ||
                    (units[unit].orders == 16)))))) || (3 < units[unit].orders)) ||
                (units[unit].orders == 3));
        x = (int)units[unit].x;
        y = (int)units[unit].y;
        iVar3 = map_in_bounds(x,y);
      } while ((((iVar3 == 0) || (x < local_14[0])) ||
               ((local_14[1] < x ||
                (((local_14[2] < x || (x < local_14[3])) || (y < local_24[0])))))) ||
              (((y < local_24[1] || (local_24[2] < y)) || (local_24[3] < y))));
      units[unit].orders = 11;
      units[unit].field_0c = '7';
      units[unit].goto_x = (i16)*(i32 *)(param_1 + 0xbc);
      units[unit].goto_y = (i16)*(i32 *)(param_1 + 0xc0);
      local_38++;
    } while ((local_38 < *(int *)(param_1 + 0x98)) || (*(int *)(param_1 + 0x98) == -2));
  }
  else {
    local_38 = 0;
  }
  return local_38;
}
#undef unit
#undef local_38
#undef local_34
#undef civ
#undef local_24
#undef local_14

/* 004fb5b2 auto */
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define y2 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int (*)[4])(frame_ + FRAME_OFF(36)))
#define local_14 (*(int (*)[4])(frame_ + FRAME_OFF(52)))
int __thiscall events_action_change_terrain(C_0040bc40_28 *this,iptr param_1)

{
  bool bVar1;
  iptr iVar2;
  uptr city2;
  iptr iVar3;
  i8 *puVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 0;
  for (local_3c = 0; local_3c < 4; local_3c++) {
    local_14[local_3c] = *(int *)(param_1 + 400 + local_3c * 8);
    local_24[local_3c] = *(int *)(param_1 + 0x194 + local_3c * 8);
  }
  for (x2 = local_14[0]; x2 <= local_14[1]; x2++) {
    for (y2 = local_24[0]; y2 <= local_24[3]; y2++) {
      iVar2 = map_in_bounds(x2,y2);
      if (iVar2 != 0) {
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
  for (x2 = local_14[0]; x2 <= local_14[1]; x2++) {
    for (y2 = local_24[0]; y2 <= local_24[3]; y2++) {
      iVar3 = map_in_bounds(x2,y2);
      if (iVar3 != 0) {
        puVar3 = (i8 *)tile_at(x2,y2);
        *puVar3 = *(i8 *)(param_1 + 0x18c);
        iVar4 = tile_at(x2,y2);
        *(i8 *)(iVar4 + 1) = 0;
        iVar4 = tile_at(x2,y2);
        *(i8 *)(iVar4 + 2) = 0;
        iVar4 = tile_at(x2,y2);
        *(i8 *)(iVar4 + 3) = 0;
        for (civ = 0; civ < 8; civ++) {
          tile_update_known(x2,y2,civ);
        }
        map_redraw_tile_all_views(x2,y2);
        local_34++;
      }
    }
  }
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      city_refresh_area_tiles(city);
    }
  }
  for (civ = 0; civ < 8; civ++) {
    bVar1 = false;
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        bVar1 = true;
      }
    }
    if (!bVar1) {
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
          iVar4 = tile_at(x2,y2);
          *(byte *)(iVar4 + 4) = *(byte *)(iVar4 + 4) & ~(byte)(1 << ((byte)civ & 0x1f));
        }
      }
      civ_create(civ);
      map_redraw_all_views(human_civ,1);
    }
  }
  return local_34;
}
#undef game_over_reason
#undef human_civ
#undef civ
#undef unit
#undef city
#undef local_3c
#undef y2
#undef local_34
#undef x2
#undef local_24
#undef local_14

/* 004fba0c auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_turn(ScenarioEvents *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if ((*local_8 == 4) && ((local_8[0xb] == -1 || (local_8[0xb] == param_1)))) {
        local_c = 1;
        event_run_actions((Dialog *)this,(iptr)local_8);
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004fba9c auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_turn_interval(ScenarioEvents *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if ((*local_8 == 8) && ((local_8[0xb] == 0 || (param_1 % local_8[0xb] == 0)))) {
        local_c = 1;
        event_run_actions((Dialog *)this,(iptr)local_8);
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004fbb2f auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_random_turn(ScenarioEvents *this,i32 param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if (*local_8 == 0x40) {
        if (local_8[0xc] < 2) {
          local_10 = 1;
        }
        else {
          iVar1 = _rand();
          local_10 = iVar1 % local_8[0xc] + 1;
        }
        if (local_8[0xc] == local_10) {
          local_c = 1;
          event_run_actions((Dialog *)this,(iptr)local_8);
        }
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 004fbbdd auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_received_tech(ScenarioEvents *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if (*local_8 == 0x100) {
        if (local_8[9] == -2) {
          for (civ = 0; civ < 8; civ++) {
            if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
               (iVar1 = civ_has_advance(civ,local_8[0xd]), iVar1 != 0)) {
              local_8[9] = civ;
              local_c = 1;
              event_run_actions((Dialog *)this,(iptr)local_8);
            }
          }
        }
        else if ((((0 < local_8[9]) || (local_8[9] < 8)) &&
                 ((1 << (*(byte *)(local_8 + 9) & 0x1f) & (uint)game.civs_alive) != 0)) &&
                (iVar1 = civ_has_advance(local_8[9],local_8[0xd]), iVar1 != 0)) {
          local_c = 1;
          event_run_actions((Dialog *)this,(iptr)local_8);
        }
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef civ
#undef local_c
#undef local_8

/* 004fbd2b auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall events_check_scenario_loaded(ScenarioEvents *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if (*local_8 == 0x20) {
        local_c = 1;
        event_run_actions((Dialog *)this,(iptr)local_8);
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004fbd9d auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall
events_check_unit_killed(ScenarioEvents *this,int param_1,int param_2,int param_3)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if ((((*local_8 == 1) && (local_8[3] == param_1)) &&
          ((local_8[9] == param_3 || (local_8[9] == -2)))) &&
         ((local_8[6] == param_2 || (local_8[6] == -2)))) {
        local_c = 1;
        if (local_8[6] == -2) {
          local_8[6] = param_2;
        }
        if (local_8[9] == -2) {
          local_8[9] = param_3;
        }
        event_run_actions((Dialog *)this,(iptr)local_8);
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004fbe84 auto */
i32 __thiscall events_check_negotiation(ScenarioEvents *this,iptr param_1,iptr param_2)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  
  piVar1 = (int *)this->event_list;
  do {
    if (piVar1 == (int *)0x0) {
      return 1;
    }
    if (*piVar1 == 0x10) {
      if (((piVar1[6] == param_1) || (piVar1[6] == -2)) &&
         ((((1 << (*(byte *)(piVar1 + 6) & 0x1f) & (uint)game.human_players) != 0 &&
           ((piVar1[7] == 1 || (piVar1[7] == 4)))) ||
          (((1 << (*(byte *)(piVar1 + 6) & 0x1f) & (uint)game.human_players) == 0 &&
           ((piVar1[7] == 2 || (piVar1[7] == 4)))))))) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (((piVar1[9] == param_2) || (piVar1[9] == -2)) &&
         (((((uint)game.human_players & 1 << (*(byte *)(piVar1 + 9) & 0x1f)) != 0 &&
           ((piVar1[10] == 1 || (piVar1[10] == 4)))) ||
          ((((uint)game.human_players & 1 << (*(byte *)(piVar1 + 9) & 0x1f)) == 0 &&
           ((piVar1[10] == 2 || (piVar1[10] == 4)))))))) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
      if ((bVar2) && (bVar3)) {
LAB_004fc1a5:
        if (piVar1[0x60] == 0x1000) {
          event_run_actions((Dialog *)this,(iptr)piVar1);
          return 0;
        }
        event_run_actions((Dialog *)this,(iptr)piVar1);
        return 1;
      }
      if ((2 < game.multiplayer) &&
         (((1 << ((byte)param_1 & 0x1f) & (uint)game.human_players) != 0 &&
          ((1 << ((byte)param_2 & 0x1f) & (uint)game.human_players) != 0)))) {
        if (((piVar1[6] == param_2) || (piVar1[6] == -2)) &&
           ((((1 << (*(byte *)(piVar1 + 6) & 0x1f) & (uint)game.human_players) != 0 &&
             ((piVar1[7] == 1 || (piVar1[7] == 4)))) ||
            (((1 << (*(byte *)(piVar1 + 6) & 0x1f) & (uint)game.human_players) == 0 &&
             ((piVar1[7] == 2 || (piVar1[7] == 4)))))))) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
        if (((piVar1[9] == param_1) || (piVar1[9] == -2)) &&
           (((((uint)game.human_players & 1 << (*(byte *)(piVar1 + 9) & 0x1f)) != 0 &&
             ((piVar1[10] == 1 || (piVar1[10] == 4)))) ||
            ((((uint)game.human_players & 1 << (*(byte *)(piVar1 + 9) & 0x1f)) == 0 &&
             ((piVar1[10] == 2 || (piVar1[10] == 4)))))))) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
        if ((bVar2) && (bVar3)) goto LAB_004fc1a5;
      }
    }
    piVar1 = (int *)piVar1[0x6f];
  } while( true );
}

/* 004fc20d auto */
#define local_c (*(int * *)(frame_ + FRAME_OFF(4)))
i32 __thiscall events_check_no_schism(ScenarioEvents *this,iptr param_1)

{
  bool bVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  local_c = (int *)this->event_list;
  if (local_c == (int *)0x0) {
    uVar2 = 1;
  }
  else {
    do {
      if ((*local_c == 0x80) && ((local_c[9] == param_1 || (local_c[9] == -2)))) {
        event_run_actions((Dialog *)this,(iptr)local_c);
        bVar1 = true;
      }
      local_c = (int *)local_c[0x6f];
    } while (local_c != (int *)0x0);
    if (bVar1) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}
#undef local_c

/* 004fc2bb auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
i32 __thiscall
events_check_city_taken(ScenarioEvents *this,iptr param_1,iptr param_2,iptr param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = (int *)this->event_list;
  if (local_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    do {
      if ((((*local_8 == 2) && (iVar1 = __strcmpi((char *)local_8[4],(char *)param_1), iVar1 == 0))
          && ((local_8[6] == param_2 || (local_8[6] == -2)))) &&
         ((local_8[9] == param_3 || (local_8[9] == -2)))) {
        if (local_8[6] == -2) {
          local_8[6] = param_2;
        }
        if (local_8[9] == -2) {
          local_8[9] = param_3;
        }
        local_c = 1;
        event_run_actions((Dialog *)this,(iptr)local_8);
      }
      local_8 = (int *)local_8[0x6f];
    } while (local_8 != (int *)0x0);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004fc3ae auto */
i32 __thiscall event_run_actions(Dialog *this,iptr param_1)

{
  i32 uVar1;
  
  if (((*(byte *)(param_1 + 4) & 0x40) == 0) || ((*(byte *)(param_1 + 5) & 0x20) == 0)) {
    if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
      events_action_play_wave((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 0x80) != 0) {
      events_action_play_cd((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 4) != 0) {
      events_action_create_unit((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 2) != 0) {
      events_action_move_unit((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 5) & 2) != 0) {
      events_action_change_terrain((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 0x20) != 0) {
      events_action_make_aggression((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 8) != 0) {
      events_action_change_money((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 5) & 4) != 0) {
      events_action_destroy_civ((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 5) & 8) != 0) {
      events_action_give_tech((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 1) != 0) {
      events_action_text(this,param_1);
    }
    if ((*(byte *)(param_1 + 5) & 1) != 0) {
      events_action_dont_play_wonders((C_0040bc40_28 *)this,param_1);
    }
    if ((*(byte *)(param_1 + 4) & 0x40) != 0) {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 0x2000;
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 004fc516 auto */
#define local_84 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_68 (*(int * *)(frame_ + FRAME_OFF(32)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_4c (*(uint *)(frame_ + FRAME_OFF(60)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_3c (*(char * *)(frame_ + FRAME_OFF(76)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(100)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(116)))
#define local_c (*(int *)(frame_ + FRAME_OFF(124)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(128)))
int __thiscall events_parse_file(ScenarioEvents *this,iptr param_1,iptr param_2)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_44 = 1;
  local_4c = 1;
  events_parse_verbose = 0;
  iVar1 = text_open_section(param_1,param_2);
  if (iVar1 == 0) {
    do {
      local_3c = (char *)text_read_line(1);
      if (local_3c == (char *)0x0) {
        local_4c = 10;
      }
      else if (*local_3c == '@') {
        local_3c++;
        iVar1 = __strcmpi(local_3c,&events_kw_if_str);
        if (iVar1 == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_found___creating_new_event_s_0062f2c4);
          }
          local_68 = (int *)events_alloc(this);
          if (local_68 == (int *)0x0) {
            if (events_parse_verbose != 0) {
              _printf(s_Failed_to_create_new_event_struc_0062f2f0);
            }
            goto LAB_004ff6f7;
          }
          if (events_parse_verbose != 0) {
            _printf(s_New_event_structure_created_0062f318);
          }
          local_78 = 0;
          local_34 = 0;
          local_c = 0;
          local_60 = 0;
          local_1c = 0;
          local_5c = 0;
          local_74 = 0;
          local_84 = 0;
          local_70 = 0;
          local_18 = 0;
          local_58 = 0;
          local_28 = 0;
          local_8 = 0;
          local_14 = 0;
          local_6c = 0;
          local_64 = 0;
          local_2c = 0;
          local_54 = 0;
          local_80 = 0;
          local_50 = 0;
          local_48 = 0;
          local_4c = 2;
        }
        else if (local_4c != 6) {
          iVar1 = __strcmpi(local_3c,&events_kw_then_str);
          if (iVar1 == 0) {
            if (events_parse_verbose != 0) {
              _printf(s__THEN_found_0062f340);
            }
            local_4c = 3;
          }
          else {
            iVar1 = __strcmpi(local_3c,s_ENDIF_0062f350);
            if (iVar1 == 0) {
              if (events_parse_verbose != 0) {
                _printf(s__ENDIF_found_0062f358);
              }
              local_4c = 5;
            }
            else {
              iVar1 = __strcmpi(local_3c,s_DEBUG_0062f368);
              if (iVar1 == 0) {
                events_parse_verbose = 1;
                _printf(s_Debugging_filename___s_0062f370,param_1);
              }
              else {
                iVar1 = __strcmpi(local_3c,s_ENDEVENTS_0062f38c);
                if (iVar1 == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s__ENDEVENTS_found_0062f398);
                  }
                  local_4c = 10;
                }
              }
            }
          }
        }
      }
      else if (local_4c == 2) {
        iVar1 = __strcmpi(local_3c,s_UNITKILLED_0062f3ac);
        if (iVar1 == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_UNITKILLED_found_looking_for_0062f3b8);
          }
          while (((local_60 == 0 || (local_34 == 0)) || (local_c == 0))) {
            local_3c = (char *)text_read_line(1);
            if (local_3c == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062f3f8);
              }
              goto LAB_004ff6f7;
            }
            if (*local_3c == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_UNITKILLED_statement_0062f410);
              }
              goto LAB_004ff6f7;
            }
            iVar1 = __strnicmp(local_3c,s_unit__0062f430,5);
            if (iVar1 == 0) {
              pcVar3 = local_3c + 5;
              iVar1 = events_parse_unit_type((iptr)pcVar3);
              if ((iVar1 == -1) || (iVar1 == -2)) {
                if (events_parse_verbose != 0) {
                  _printf(s_found_unit__s__but__s_is_not_val_0062f450,pcVar3,pcVar3);
                }
              }
              else {
                sVar2 = _strlen(pcVar3);
                iVar4 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                local_68[2] = iVar4;
                if (local_68[2] == 0) goto LAB_004ff6f7;
                FUN_005f22d0(local_68[2],pcVar3);
                local_68[3] = iVar1;
                if (events_parse_verbose != 0) {
                  _printf(s_found_unit__s__id__d__0062f438,pcVar3,iVar1);
                }
                local_60 = 1;
              }
            }
            else {
              iVar1 = __strnicmp(local_3c,s_attacker__0062f474,9);
              if (iVar1 == 0) {
                pcVar3 = local_3c + 9;
                local_20 = events_parse_civ((iptr)pcVar3);
                if (local_20 == -1) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_attacker__s__but__s_is_not_0062f4a0,pcVar3,pcVar3);
                  }
                }
                else {
                  sVar2 = _strlen(pcVar3);
                  iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                  local_68[5] = iVar1;
                  if (local_68[5] == 0) goto LAB_004ff6f7;
                  FUN_005f22d0(local_68[5],pcVar3);
                  local_68[6] = local_20;
                  if (events_parse_verbose != 0) {
                    _printf(s_found_attacker__s__king_id__d__0062f480,pcVar3,local_20);
                  }
                  local_c = 1;
                }
              }
              else {
                iVar1 = __strnicmp(local_3c,s_defender__0062f4c8,9);
                if (iVar1 == 0) {
                  pcVar3 = local_3c + 9;
                  local_20 = events_parse_civ((iptr)pcVar3);
                  if (local_20 == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_defender__s__but__s_is_not_0062f4f4,pcVar3,pcVar3);
                    }
                  }
                  else {
                    sVar2 = _strlen(pcVar3);
                    iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                    local_68[8] = iVar1;
                    if (local_68[8] == 0) goto LAB_004ff6f7;
                    FUN_005f22d0(local_68[8],pcVar3);
                    local_68[9] = local_20;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_defender__s__king_id__d__0062f4d4,pcVar3,local_20);
                    }
                    local_34 = 1;
                  }
                }
              }
            }
          }
          *local_68 = 1;
        }
        iVar1 = __strcmpi(local_3c,s_NEGOTIATION_0062f51c);
        if (iVar1 == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_NEGOTIATION_found_looking_fo_0062f528);
          }
          while (((local_34 == 0 || (local_c == 0)) || ((local_2c == 0 || (local_64 == 0))))) {
            local_3c = (char *)text_read_line(1);
            if (local_3c == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062f578);
              }
              goto LAB_004ff6f7;
            }
            if (*local_3c == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_NEGOTIATION_statement_0062f590);
              }
              goto LAB_004ff6f7;
            }
            iVar1 = __strnicmp(local_3c,s_talker__0062f5b0,7);
            if (iVar1 == 0) {
              pcVar3 = local_3c + 7;
              local_20 = events_parse_civ((iptr)pcVar3);
              if (local_20 == -1) {
                if (events_parse_verbose != 0) {
                  _printf(s_found_talker__s__but__s_is_not_v_0062f5d8,pcVar3,pcVar3);
                }
              }
              else {
                sVar2 = _strlen(pcVar3);
                iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                local_68[5] = iVar1;
                if (local_68[5] == 0) goto LAB_004ff6f7;
                FUN_005f22d0(local_68[5],pcVar3);
                local_68[6] = local_20;
                if (events_parse_verbose != 0) {
                  _printf(s_found_talker__s__king_id__d__0062f5b8,pcVar3,local_20);
                }
                local_c = 1;
              }
            }
            else {
              iVar1 = __strnicmp(local_3c,s_talkertype__0062f600,0xb);
              if (iVar1 == 0) {
                pcVar3 = local_3c + 0xb;
                iVar1 = __strcmpi(pcVar3,s_HUMAN_0062f60c);
                if (iVar1 == 0) {
                  local_68[7] = 1;
                  local_2c = 1;
                }
                else {
                  iVar1 = __strcmpi(pcVar3,s_COMPUTER_0062f614);
                  if (iVar1 == 0) {
                    local_68[7] = 2;
                    local_2c = 1;
                  }
                  else {
                    iVar1 = __strcmpi(pcVar3,s_HUMANORCOMPUTER_0062f620);
                    if (iVar1 == 0) {
                      local_68[7] = 4;
                      local_2c = 1;
                    }
                  }
                }
                if (events_parse_verbose != 0) {
                  if (local_2c == 0) {
                    _printf(s_found_talkertype__s__but__s_is_n_0062f648,pcVar3,pcVar3);
                  }
                  else {
                    _printf(s_found_talkertype__s_0062f630,pcVar3);
                  }
                }
              }
              else {
                iVar1 = __strnicmp(local_3c,s_listener__0062f674,9);
                if (iVar1 == 0) {
                  pcVar3 = local_3c + 9;
                  local_20 = events_parse_civ((iptr)pcVar3);
                  if (local_20 == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_listener__s__but__s_is_not_0062f6a0,pcVar3,pcVar3);
                    }
                  }
                  else {
                    sVar2 = _strlen(pcVar3);
                    iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                    local_68[8] = iVar1;
                    if (local_68[8] == 0) goto LAB_004ff6f7;
                    FUN_005f22d0(local_68[8],pcVar3);
                    local_68[9] = local_20;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_listener__s__king_id__d__0062f680,pcVar3,local_20);
                    }
                    local_34 = 1;
                  }
                }
                else {
                  iVar1 = __strnicmp(local_3c,s_listenertype__0062f6c8,0xd);
                  if (iVar1 == 0) {
                    pcVar3 = local_3c + 0xd;
                    iVar1 = __strcmpi(pcVar3,s_HUMAN_0062f6d8);
                    if (iVar1 == 0) {
                      local_68[10] = 1;
                      local_64 = 1;
                    }
                    else {
                      iVar1 = __strcmpi(pcVar3,s_COMPUTER_0062f6e0);
                      if (iVar1 == 0) {
                        local_68[10] = 2;
                        local_64 = 1;
                      }
                      else {
                        iVar1 = __strcmpi(pcVar3,s_HUMANORCOMPUTER_0062f6ec);
                        if (iVar1 == 0) {
                          local_68[10] = 4;
                          local_64 = 1;
                        }
                      }
                    }
                    if (events_parse_verbose != 0) {
                      if (local_2c == 0) {
                        _printf(s_found_listenertype__s__but__s_is_0062f714,pcVar3,pcVar3);
                      }
                      else {
                        _printf(s_found_listenertype__s_0062f6fc,pcVar3);
                      }
                    }
                  }
                }
              }
            }
          }
          *local_68 = 0x10;
          local_68[0x60] = 0x1000;
        }
        iVar1 = __strcmpi(local_3c,s_NOSCHISM_0062f740);
        if (iVar1 == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__IF_NOSCHISM_found_looking_for_w_0062f74c);
          }
          while (local_34 == 0) {
            pcVar3 = (char *)text_read_line(1);
            if (pcVar3 == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062f774);
              }
              goto LAB_004ff6f7;
            }
            if (*pcVar3 == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_NOSCHISM_statement_0062f78c);
              }
              goto LAB_004ff6f7;
            }
            iVar1 = __strnicmp(pcVar3,s_defender__0062f7a8,9);
            if (iVar1 == 0) {
              pcVar3 += 9;
              local_20 = events_parse_civ((iptr)pcVar3);
              if (local_20 == -1) {
                if (events_parse_verbose != 0) {
                  _printf(s_found_defender__s__but__s_is_not_0062f7d4,pcVar3,pcVar3);
                }
              }
              else {
                sVar2 = _strlen(pcVar3);
                iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                local_68[8] = iVar1;
                if (local_68[8] == 0) goto LAB_004ff6f7;
                FUN_005f22d0(local_68[8],pcVar3);
                local_68[9] = local_20;
                if (events_parse_verbose != 0) {
                  _printf(s_found_defender__s__king_id__d__0062f7b4,pcVar3,local_20);
                }
                local_34 = 1;
              }
            }
          }
          *local_68 = 0x80;
        }
        else {
          iVar1 = __strcmpi(local_3c,s_RECEIVEDTECHNOLOGY_0062f7fc);
          if (iVar1 == 0) {
            if (events_parse_verbose != 0) {
              _printf(s__IF_RECEIVEDTECHNOLOGY_found_loo_0062f810);
            }
            while ((local_6c == 0 || (local_34 == 0))) {
              pcVar3 = (char *)text_read_line(1);
              if (pcVar3 == (char *)0x0) {
                if (events_parse_verbose != 0) {
                  _printf(s_Got_early_end_of_file__0062f850);
                }
                goto LAB_004ff6f7;
              }
              if (*pcVar3 == '@') {
                if (events_parse_verbose != 0) {
                  _printf(s_Illegal_RECEIVEDTECHNOLOGY_state_0062f868);
                }
                goto LAB_004ff6f7;
              }
              iVar1 = __strnicmp(pcVar3,s_receiver__0062f890,9);
              if (iVar1 == 0) {
                pcVar3 += 9;
                iVar1 = events_parse_civ((iptr)pcVar3);
                if (iVar1 == -1) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_receiver__s__but__s_is_not_0062f8bc,pcVar3,pcVar3);
                  }
                }
                else {
                  sVar2 = _strlen(pcVar3);
                  iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                  local_68[8] = iVar1;
                  if (local_68[8] == 0) goto LAB_004ff6f7;
                  FUN_005f22d0(local_68[8],pcVar3);
                  iVar1 = events_parse_civ((iptr)pcVar3);
                  local_68[9] = iVar1;
                  if (events_parse_verbose != 0) {
                    _printf(s_found_receiver__s__king_id__d__0062f89c,pcVar3,local_20);
                  }
                  local_34 = 1;
                }
              }
              else {
                iVar1 = __strnicmp(pcVar3,s_technology__0062f8e4,0xb);
                if (iVar1 == 0) {
                  pcVar3 += 0xb;
                  if ((*pcVar3 < '0') || ('9' < *pcVar3)) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_technology__s__but__s_is_n_0062f918,pcVar3,pcVar3);
                    }
                  }
                  else {
                    iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                    local_68[0xd] = iVar1;
                    local_6c = 1;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_technology__s__technology_i_0062f8f0,pcVar3,local_68[0xd]);
                    }
                  }
                }
              }
            }
            *local_68 = 0x100;
          }
          else {
            iVar1 = __strcmpi(local_3c,s_CITYTAKEN_0062f944);
            if (iVar1 == 0) {
              if (events_parse_verbose != 0) {
                _printf(s__IF_CITYTAKEN_found_looking_for_c_0062f950);
              }
              while (((local_78 == 0 || (local_c == 0)) || (local_34 == 0))) {
                pcVar3 = (char *)text_read_line(1);
                if (pcVar3 == (char *)0x0) {
                  if (events_parse_verbose != 0) {
                    _printf(s_Got_early_end_of_file__0062f98c);
                  }
                  goto LAB_004ff6f7;
                }
                if (*pcVar3 == '@') {
                  if (events_parse_verbose != 0) {
                    _printf(s_Illegal_CITYTAKEN_statement_0062f9a4);
                  }
                  goto LAB_004ff6f7;
                }
                iVar1 = __strnicmp(pcVar3,s_attacker__0062f9c4,9);
                if (iVar1 == 0) {
                  pcVar3 += 9;
                  iVar1 = events_parse_civ((iptr)pcVar3);
                  if (iVar1 == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_attacker__s__but__s_is_not_0062f9f0,pcVar3,pcVar3);
                    }
                  }
                  else {
                    sVar2 = _strlen(pcVar3);
                    iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                    local_68[5] = iVar1;
                    if (local_68[5] == 0) goto LAB_004ff6f7;
                    FUN_005f22d0(local_68[5],pcVar3);
                    iVar1 = events_parse_civ((iptr)pcVar3);
                    local_68[6] = iVar1;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_attacker__s__king_id__d__0062f9d0,pcVar3,local_20);
                    }
                    local_c = 1;
                  }
                }
                else {
                  iVar1 = __strnicmp(pcVar3,s_defender__0062fa18,9);
                  if (iVar1 == 0) {
                    pcVar3 += 9;
                    local_20 = events_parse_civ((iptr)pcVar3);
                    if (local_20 == -1) {
                      if (events_parse_verbose != 0) {
                        _printf(s_found_defender__s__but__s_is_not_0062fa44,pcVar3,pcVar3);
                      }
                    }
                    else {
                      sVar2 = _strlen(pcVar3);
                      iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                      local_68[8] = iVar1;
                      if (local_68[8] == 0) goto LAB_004ff6f7;
                      FUN_005f22d0(local_68[8],pcVar3);
                      local_68[9] = local_20;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_defender__s__king_id__d__0062fa24,pcVar3,local_20);
                      }
                      local_34 = 1;
                    }
                  }
                  else {
                    iVar1 = __strnicmp(pcVar3,s_city__0062fa6c,5);
                    if (iVar1 == 0) {
                      pcVar3 += 5;
                      sVar2 = _strlen(pcVar3);
                      iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                      local_68[4] = iVar1;
                      if (local_68[4] == 0) goto LAB_004ff6f7;
                      FUN_005f22d0(local_68[4],pcVar3);
                      if (events_parse_verbose != 0) {
                        _printf(s_found_city__s_0062fa74,pcVar3,local_20);
                      }
                      local_78 = 1;
                    }
                  }
                }
              }
              *local_68 = 2;
            }
            else {
              iVar1 = __strcmpi(local_3c,&events_kw_turn_str);
              if (iVar1 == 0) {
                if (events_parse_verbose != 0) {
                  _printf(s__IF_TURN_found_looking_for_turn__0062fa8c);
                }
                do {
                  do {
                    pcVar3 = (char *)text_read_line(1);
                    if (pcVar3 == (char *)0x0) {
                      if (events_parse_verbose != 0) {
                        _printf(s_Got_early_end_of_file__0062fab0);
                      }
                      goto LAB_004ff6f7;
                    }
                    if (*pcVar3 == '@') {
                      if (events_parse_verbose != 0) {
                        _printf(s_Illegal_TURN_statement_0062fac8);
                      }
                      goto LAB_004ff6f7;
                    }
                    iVar1 = __strnicmp(pcVar3,s_turn__0062fae0,5);
                  } while (iVar1 != 0);
                  pcVar3 += 5;
                  iVar1 = __strcmpi(pcVar3,s_EVERY_0062fae8);
                  if (iVar1 == 0) {
                    local_68[0xb] = -1;
                    *local_68 = 4;
                  }
                  else if (((('/' < *pcVar3) && (*pcVar3 < ':')) || (*pcVar3 == '-')) ||
                          (*pcVar3 == '+')) {
                    iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                    local_68[0xb] = iVar1;
                    *local_68 = 4;
                  }
                  if (events_parse_verbose != 0) {
                    if (*local_68 == 4) {
                      _printf(s_found_turn__s_0062faf0,pcVar3);
                    }
                    else {
                      _printf(s_found_turn__s__but__s_is_not_val_0062fb00,pcVar3,pcVar3);
                    }
                  }
                } while (*local_68 != 4);
              }
              else {
                iVar1 = __strcmpi(local_3c,s_TURNINTERVAL_0062fb24);
                if (iVar1 == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s__IF_TURNINTERVAL_found_looking_f_0062fb34);
                  }
                  do {
                    pcVar3 = (char *)text_read_line(1);
                    if (pcVar3 == (char *)0x0) {
                      if (events_parse_verbose != 0) {
                        _printf(s_Got_early_end_of_file__0062fb64);
                      }
                      goto LAB_004ff6f7;
                    }
                    if (*pcVar3 == '@') {
                      if (events_parse_verbose != 0) {
                        _printf(s_Illegal_TURNINTERVAL_statement_0062fb7c);
                      }
                      goto LAB_004ff6f7;
                    }
                    iVar1 = __strnicmp(pcVar3,s_interval__0062fb9c,9);
                    if (iVar1 == 0) {
                      pcVar3 += 9;
                      if ((((*pcVar3 < '0') || ('9' < *pcVar3)) && (*pcVar3 != '-')) &&
                         (*pcVar3 != '+')) {
                        if (events_parse_verbose != 0) {
                          _printf(s_found_interval__s__but__s_is_not_0062fbbc,pcVar3,pcVar3);
                        }
                      }
                      else {
                        iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                        local_68[0xb] = iVar1;
                        if (events_parse_verbose != 0) {
                          _printf(s_found_interval__s_0062fba8,pcVar3);
                        }
                        *local_68 = 8;
                      }
                    }
                  } while (*local_68 != 8);
                }
                else {
                  iVar1 = __strcmpi(local_3c,s_RANDOMTURN_0062fbe4);
                  if (iVar1 == 0) {
                    if (events_parse_verbose != 0) {
                      _printf(s__IF_RANDOMTURN_found_looking_for_0062fbf0);
                    }
                    do {
                      pcVar3 = (char *)text_read_line(1);
                      if (pcVar3 == (char *)0x0) {
                        if (events_parse_verbose != 0) {
                          _printf(s_Got_early_end_of_file__0062fc20);
                        }
                        goto LAB_004ff6f7;
                      }
                      if (*pcVar3 == '@') {
                        if (events_parse_verbose != 0) {
                          _printf(s_Illegal_RANDOMTURN_statement_0062fc38);
                        }
                        goto LAB_004ff6f7;
                      }
                      iVar1 = __strnicmp(pcVar3,s_denominator__0062fc58,0xc);
                      if (iVar1 == 0) {
                        pcVar3 += 0xc;
                        if ((*pcVar3 < '0') || ('9' < *pcVar3)) {
                          if (events_parse_verbose != 0) {
                            _printf(s_found_denominator__s__but__s_is_n_0062fcac,pcVar3,pcVar3);
                          }
                        }
                        else {
                          iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                          local_68[0xc] = iVar1;
                          if ((local_68[0xc] < 1) || (1000 < local_68[0xc])) {
                            _printf(s_found_denominator__s__but__s_is_n_0062fc68,pcVar3,pcVar3);
                            goto LAB_004ff6f7;
                          }
                          if (events_parse_verbose != 0) {
                            _printf(s_found_denominator__s_0062fc94,pcVar3);
                          }
                          *local_68 = 0x40;
                        }
                      }
                    } while (*local_68 != 0x40);
                  }
                  else {
                    iVar1 = __strcmpi(local_3c,s_SCENARIOLOADED_0062fcd8);
                    if (iVar1 == 0) {
                      if (events_parse_verbose != 0) {
                        _printf(s__IF_SCENARIOLOADED_0062fce8);
                      }
                      *local_68 = 0x20;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (local_4c == 3) {
        iVar1 = __strcmpi(local_3c,&events_kw_text_str);
        if (iVar1 == 0) {
          if (events_parse_verbose != 0) {
            _printf(s__THEN_TEXT_found_looking_for_END_0062fd08);
          }
          local_38 = 0;
          local_3c = (char *)text_read_line(1);
          if (local_3c == (char *)0x0) goto LAB_004ff6f7;
          while (iVar1 = __strcmpi(local_3c,s_ENDTEXT_0062fd30), iVar1 != 0) {
            if (local_38 != 0x14) {
              sVar2 = _strlen(local_3c);
              iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
              local_68[local_38 + 0xe] = iVar1;
              if (local_68[local_38 + 0xe] == 0) goto LAB_004ff6f7;
              FUN_005f22d0(local_68[local_38 + 0xe],local_3c);
              local_38++;
            }
            local_3c = (char *)text_read_line(1);
            if (local_3c == (char *)0x0) {
              if (events_parse_verbose != 0) {
                _printf(s_Got_early_end_of_file__0062fd38);
              }
              goto LAB_004ff6f7;
            }
            if (*local_3c == '@') {
              if (events_parse_verbose != 0) {
                _printf(s_Illegal_TEXT_statement_0062fd50);
              }
              goto LAB_004ff6f7;
            }
          }
          if (events_parse_verbose != 0) {
            _printf(s_found_ENDTEXT_0062fd68);
          }
          local_68[1] = local_68[1] | 1;
        }
        else {
          iVar1 = __strcmpi(local_3c,s_CHANGETERRAIN_0062fd78);
          if (iVar1 == 0) {
            if (events_parse_verbose != 0) {
              _printf(s__THEN_CHANGETERRAIN_found_lookin_0062fd88);
            }
            local_24 = 0;
            while ((local_1c == 0 || (local_24 != 4))) {
              pcVar3 = (char *)text_read_line(1);
              if (pcVar3 == (char *)0x0) {
                if (events_parse_verbose != 0) {
                  _printf(s_Got_early_end_of_file__0062fdc8);
                }
                goto LAB_004ff6f7;
              }
              if (*pcVar3 == '@') {
                if (events_parse_verbose != 0) {
                  _printf(s_Illegal_CHANGETERRAIN_statement_0062fde0);
                }
                goto LAB_004ff6f7;
              }
              iVar1 = __strnicmp(pcVar3,s_terraintype__0062fe04,0xc);
              if (iVar1 == 0) {
                pcVar3 += 0xc;
                if ((*pcVar3 < '0') || ('9' < *pcVar3)) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_terraintype__s__but__s_is_n_0062fe3c,pcVar3,pcVar3);
                  }
                }
                else {
                  iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                  if ((-1 < iVar1) || (iVar1 < 0xb)) {
                    local_68[99] = iVar1;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_terraintype__s__terrainid__0062fe14,pcVar3,iVar1);
                    }
                    local_1c = 1;
                  }
                }
              }
              else {
                iVar1 = __strcmpi(pcVar3,s_maprect_0062fe68);
                if (iVar1 == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s_found_maprect_0062fe70);
                  }
                  iVar1 = text_read_line(1);
                  if (iVar1 == 0) {
                    if (events_parse_verbose != 0) {
                      _printf(s_Got_early_end_of_file__0062fe80);
                    }
                    goto LAB_004ff6f7;
                  }
                  for (local_38 = 0; local_38 < 4; local_38++) {
                    iVar1 = text_next_int();
                    local_68[local_38 * 2 + 100] = iVar1;
                    iVar1 = text_next_int();
                    local_68[local_38 * 2 + 0x65] = iVar1;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_location__d___d___d_0062fe98,local_24,
                              local_68[local_38 * 2 + 100],local_68[local_38 * 2 + 0x65]);
                    }
                    local_24++;
                  }
                }
              }
            }
            local_68[1] = local_68[1] | 0x200;
          }
          else {
            iVar1 = __strcmpi(local_3c,s_CREATEUNIT_0062feb4);
            if (iVar1 == 0) {
              if (events_parse_verbose != 0) {
                _printf(s__THEN_CREATEUNIT_found_looking_f_0062fec0);
              }
              local_24 = 0;
LAB_004fe0af:
              if (((local_74 == 0) || (local_84 == 0)) ||
                 ((local_80 == 0 || ((local_54 == 0 || (local_24 == 0)))))) {
                pcVar3 = (char *)text_read_line(1);
                if (pcVar3 == (char *)0x0) {
                  if (events_parse_verbose != 0) {
                    _printf(s_Got_early_end_of_file__0062ff1c);
                  }
                  goto LAB_004ff6f7;
                }
                if (*pcVar3 == '@') {
                  if (events_parse_verbose != 0) {
                    _printf(s_Illegal_CREATEUNIT_statement_0062ff34);
                  }
                  goto LAB_004ff6f7;
                }
                iVar1 = __strnicmp(pcVar3,s_unit__0062ff54,5);
                if (iVar1 == 0) {
                  pcVar3 += 5;
                  iVar1 = events_parse_unit_type((iptr)pcVar3);
                  if (iVar1 == -1) {
                    if (events_parse_verbose != 0) {
                      _printf(s_found_unit__s__but__s_is_not_val_0062ff78,pcVar3,pcVar3);
                    }
                  }
                  else {
                    sVar2 = _strlen(pcVar3);
                    iVar4 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                    local_68[0x37] = iVar4;
                    if (local_68[0x37] == 0) goto LAB_004ff6f7;
                    FUN_005f22d0(local_68[0x37],pcVar3);
                    local_68[0x38] = iVar1;
                    if (events_parse_verbose != 0) {
                      _printf(s_found_unit__s__unit_id__d__0062ff5c,pcVar3,iVar1);
                    }
                    local_74 = 1;
                  }
                }
                else {
                  iVar1 = __strnicmp(pcVar3,s_owner__0062ff9c,6);
                  if (iVar1 == 0) {
                    pcVar3 += 6;
                    local_20 = events_parse_civ((iptr)pcVar3);
                    if (local_20 == -1) {
                      if (events_parse_verbose != 0) {
                        _printf(s_found_owner__s__but__s_is_not_va_0062ffc4,pcVar3,pcVar3);
                      }
                    }
                    else {
                      sVar2 = _strlen(pcVar3);
                      iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                      local_68[0x35] = iVar1;
                      if (local_68[0x35] == 0) goto LAB_004ff6f7;
                      FUN_005f22d0(local_68[0x35],pcVar3);
                      local_68[0x36] = local_20;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_owner__s__king_id__d__0062ffa4,pcVar3,local_20);
                      }
                      local_84 = 1;
                    }
                  }
                  else {
                    iVar1 = __strnicmp(pcVar3,s_veteran__0062ffec,8);
                    if (iVar1 == 0) {
                      pcVar3 += 8;
                      iVar1 = __strcmpi(pcVar3,&events_bool_yes_str);
                      if ((iVar1 == 0) || (iVar1 = __strcmpi(pcVar3,&events_bool_true_str), iVar1 == 0)) {
                        local_68[0x4e] = 1;
                        local_54 = 1;
                      }
                      else {
                        iVar1 = __strcmpi(pcVar3,&events_bool_no_str);
                        if ((iVar1 == 0) || (iVar1 = __strcmpi(pcVar3,s_false_00630008), iVar1 == 0)
                           ) {
                          local_68[0x4e] = 0;
                          local_54 = 1;
                        }
                        else if (events_parse_verbose != 0) {
                          _printf(s_found_veteran__s__but__s_is_not_v_00630010,pcVar3,pcVar3);
                        }
                      }
                    }
                    else {
                      iVar1 = __strnicmp(pcVar3,s_homecity__00630038,9);
                      if (iVar1 == 0) {
                        pcVar3 += 9;
                        sVar2 = _strlen(pcVar3);
                        iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                        local_68[0x4f] = iVar1;
                        if (local_68[0x4f] == 0) goto LAB_004ff6f7;
                        FUN_005f22d0(local_68[0x4f],pcVar3);
                        if (events_parse_verbose != 0) {
                          _printf(s_found_homecity__s_00630044,pcVar3);
                        }
                        local_80 = 1;
                      }
                      else {
                        iVar1 = __strcmpi(pcVar3,s_locations_00630058);
                        if (iVar1 == 0) {
                          if (events_parse_verbose != 0) {
                            _printf(s_found_locations_00630064);
                          }
                          for (local_38 = 0; local_38 < 10; local_38++) {
                            pcVar3 = (char *)text_read_line(1);
                            if (pcVar3 == (char *)0x0) {
                              if (events_parse_verbose != 0) {
                                _printf(s_Got_early_end_of_file__00630078);
                              }
                              goto LAB_004ff6f7;
                            }
                            if ((((*pcVar3 < '0') || ('9' < *pcVar3)) && (*pcVar3 != '-')) &&
                               (*pcVar3 != '+')) {
                              iVar1 = __strcmpi(pcVar3,s_endlocations_006300ac);
                              if (iVar1 == 0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_endlocations_006300bc,pcVar3,pcVar3);
                                }
                                break;
                              }
                            }
                            else {
                              iVar1 = text_next_int();
                              local_68[local_38 * 2 + 0x39] = iVar1;
                              iVar1 = text_next_int();
                              local_68[local_38 * 2 + 0x3a] = iVar1;
                              if (events_parse_verbose != 0) {
                                _printf(s_found_location__d___d___d_00630090,local_24,
                                        local_68[local_38 * 2 + 0x39],local_68[local_38 * 2 + 0x3a])
                                ;
                              }
                              local_24++;
                            }
                          }
                        }
                      }
                    }
                  }
                }
                goto LAB_004fe0af;
              }
              local_68[0x4d] = local_24;
              local_68[1] = local_68[1] | 4;
            }
            else {
              iVar1 = __strcmpi(local_3c,s_CHANGEMONEY_006300d0);
              if (iVar1 == 0) {
                if (events_parse_verbose != 0) {
                  _printf(s__THEN_CHANGEMONEY_found_looking_f_006300dc);
                }
                while ((local_58 == 0 || (local_18 == 0))) {
                  pcVar3 = (char *)text_read_line(1);
                  if (pcVar3 == (char *)0x0) {
                    if (events_parse_verbose != 0) {
                      _printf(s_Got_early_end_of_file__00630114);
                    }
                    goto LAB_004ff6f7;
                  }
                  if (*pcVar3 == '@') {
                    if (events_parse_verbose != 0) {
                      _printf(s_Illegal_CHANGEMONEY_statement_0063012c);
                    }
                    goto LAB_004ff6f7;
                  }
                  iVar1 = __strnicmp(pcVar3,s_receiver__0063014c,9);
                  if (iVar1 == 0) {
                    pcVar3 += 9;
                    local_20 = events_parse_civ((iptr)pcVar3);
                    if (local_20 == -1) {
                      if (events_parse_verbose != 0) {
                        _printf(s_found_receiver__s__but__s_is_not_00630178,pcVar3,pcVar3);
                      }
                    }
                    else {
                      sVar2 = _strlen(pcVar3);
                      iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                      local_68[0x5d] = iVar1;
                      if (local_68[0x5d] == 0) goto LAB_004ff6f7;
                      FUN_005f22d0(local_68[0x5d],pcVar3);
                      local_68[0x5e] = local_20;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_receiver__s__king_id__d__00630158,pcVar3,local_20);
                      }
                      local_58 = 1;
                    }
                  }
                  else {
                    iVar1 = __strnicmp(pcVar3,s_amount__006301a0,7);
                    if ((iVar1 == 0) &&
                       ((((pcVar3 = pcVar3 + 7, '/' < *pcVar3 && (*pcVar3 < ':')) ||
                         (*pcVar3 == '-')) || (*pcVar3 == '+')))) {
                      iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                      local_68[0x5f] = iVar1;
                      if (events_parse_verbose != 0) {
                        _printf(s_found_amount__s__integer__d__006301a8,pcVar3,local_68[0x5f]);
                      }
                      local_18 = 1;
                    }
                  }
                }
                local_68[1] = local_68[1] | 8;
              }
              else {
                iVar1 = __strcmpi(local_3c,s_JUSTONCE_006301c8);
                if (iVar1 == 0) {
                  if (events_parse_verbose != 0) {
                    _printf(s__THEN_JUSTONCE_found_not_looking_006301d4);
                  }
                  local_68[1] = local_68[1] | 0x40;
                }
                else {
                  iVar1 = __strcmpi(local_3c,s_DONTPLAYWONDERS_00630210);
                  if (iVar1 == 0) {
                    if (events_parse_verbose != 0) {
                      _printf(s__THEN_DONTPLAYWONDERS_found_not_l_00630220);
                    }
                    local_68[1] = local_68[1] | 0x100;
                  }
                  else {
                    iVar1 = __strcmpi(local_3c,s_MAKEAGGRESSION_00630264);
                    if (iVar1 == 0) {
                      if (events_parse_verbose != 0) {
                        _printf(s__THEN_MAKEAGGRESSION_found_looki_00630274);
                      }
                      while ((local_14 == 0 || (local_8 == 0))) {
                        pcVar3 = (char *)text_read_line(1);
                        if (pcVar3 == (char *)0x0) {
                          if (events_parse_verbose != 0) {
                            _printf(s_Got_early_end_of_file__006302a8);
                          }
                          goto LAB_004ff6f7;
                        }
                        if (*pcVar3 == '@') {
                          if (events_parse_verbose != 0) {
                            _printf(s_Illegal_MAKEAGGRESSION_statement_006302c0);
                          }
                          goto LAB_004ff6f7;
                        }
                        iVar1 = __strnicmp(pcVar3,&events_who_prefix_str,4);
                        if (iVar1 == 0) {
                          pcVar3 += 4;
                          local_20 = events_parse_civ((iptr)pcVar3);
                          if (local_20 == -1) {
                            if (events_parse_verbose != 0) {
                              _printf(s_found_who__s__but__s_is_not_vali_00630308,pcVar3,pcVar3);
                            }
                          }
                          else {
                            sVar2 = _strlen(pcVar3);
                            iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                            local_68[0x33] = iVar1;
                            if (local_68[0x33] == 0) goto LAB_004ff6f7;
                            FUN_005f22d0(local_68[0x33],pcVar3);
                            local_68[0x34] = local_20;
                            if (events_parse_verbose != 0) {
                              _printf(s_found_who__s__king_id__d__006302ec,pcVar3,local_20);
                            }
                            local_14 = 1;
                          }
                        }
                        else {
                          iVar1 = __strnicmp(pcVar3,s_whom__0063032c,5);
                          if (iVar1 == 0) {
                            pcVar3 += 5;
                            local_20 = events_parse_civ((iptr)pcVar3);
                            if (local_20 == -1) {
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__but__s_is_not_val_00630350,pcVar3,pcVar3);
                              }
                            }
                            else {
                              sVar2 = _strlen(pcVar3);
                              iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                              local_68[0x31] = iVar1;
                              if (local_68[0x31] == 0) goto LAB_004ff6f7;
                              FUN_005f22d0(local_68[0x31],pcVar3);
                              local_68[0x32] = local_20;
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__king_id__d__00630334,pcVar3,local_20);
                              }
                              local_8 = 1;
                            }
                          }
                        }
                      }
                      local_68[1] = local_68[1] | 0x20;
                    }
                    else {
                      iVar1 = __strcmpi(local_3c,s_DESTROYACIVILIZATION_00630374);
                      if (iVar1 == 0) {
                        if (events_parse_verbose != 0) {
                          _printf(s__THEN_DESTROYACIVILIZATION_found_0063038c);
                        }
                        while (local_28 == 0) {
                          pcVar3 = (char *)text_read_line(1);
                          if (pcVar3 == (char *)0x0) {
                            if (events_parse_verbose != 0) {
                              _printf(s_Got_early_end_of_file__006303c4);
                            }
                            goto LAB_004ff6f7;
                          }
                          if (*pcVar3 == '@') {
                            if (events_parse_verbose != 0) {
                              _printf(s_Illegal_DESTROYACIVILIZATION_sta_006303dc);
                            }
                            goto LAB_004ff6f7;
                          }
                          iVar1 = __strnicmp(pcVar3,s_whom__00630404,5);
                          if (iVar1 == 0) {
                            pcVar3 += 5;
                            local_20 = events_parse_civ((iptr)pcVar3);
                            if (local_20 == -1) {
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__but__s_is_not_val_00630428,pcVar3,pcVar3);
                              }
                            }
                            else {
                              local_68[0x6c] = local_20;
                              if (events_parse_verbose != 0) {
                                _printf(s_found_whom__s__king_id__d__0063040c,pcVar3,local_20);
                              }
                              local_28 = 1;
                            }
                          }
                        }
                        local_68[1] = local_68[1] | 0x400;
                      }
                      else {
                        iVar1 = __strcmpi(local_3c,s_GIVETECHNOLOGY_0063044c);
                        if (iVar1 == 0) {
                          if (events_parse_verbose != 0) {
                            _printf(s__THEN_GIVETECHNOLOGY_found_looki_0063045c);
                          }
                          while ((local_48 == 0 || (local_50 == 0))) {
                            pcVar3 = (char *)text_read_line(1);
                            if (pcVar3 == (char *)0x0) {
                              if (events_parse_verbose != 0) {
                                _printf(s_Got_early_end_of_file__0063048c);
                              }
                              goto LAB_004ff6f7;
                            }
                            if (*pcVar3 == '@') {
                              if (events_parse_verbose != 0) {
                                _printf(s_Illegal_GIVETECHNOLOGY_statement_006304a4);
                              }
                              goto LAB_004ff6f7;
                            }
                            iVar1 = __strnicmp(pcVar3,s_receiver__006304c8,9);
                            if (iVar1 == 0) {
                              pcVar3 += 9;
                              local_20 = events_parse_civ((iptr)pcVar3);
                              if (local_20 == -1) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_receiver__s__but__s_is_not_006304f4,pcVar3,pcVar3)
                                  ;
                                }
                              }
                              else {
                                local_68[0x6e] = local_20;
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_receiver__s__king_id__d__006304d4,pcVar3,local_20)
                                  ;
                                }
                                local_50 = 1;
                              }
                            }
                            else {
                              iVar1 = __strnicmp(pcVar3,s_technology__0063051c,0xb);
                              if (((iVar1 == 0) && (pcVar3 = pcVar3 + 0xb, '/' < *pcVar3)) &&
                                 (*pcVar3 < ':')) {
                                iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                                local_68[0x6d] = iVar1;
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_technology__s__integer__d__00630528,pcVar3,
                                          local_68[0x6d]);
                                }
                                local_48 = 1;
                              }
                            }
                          }
                          local_68[1] = local_68[1] | 0x800;
                        }
                        else {
                          iVar1 = __strcmpi(local_3c,s_MOVEUNIT_0063054c);
                          if (iVar1 == 0) {
                            if (events_parse_verbose != 0) {
                              _printf(s__THEN_MOVEUNIT_found_looking_for_00630558);
                            }
                            local_24 = 0;
                            while ((((local_74 == 0 || (local_84 == 0)) || (local_24 != 4)) ||
                                   ((local_5c == 0 || (local_70 == 0))))) {
                              pcVar3 = (char *)text_read_line(1);
                              if (pcVar3 == (char *)0x0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_Got_early_end_of_file__006305a8);
                                }
                                goto LAB_004ff6f7;
                              }
                              if (*pcVar3 == '@') {
                                if (events_parse_verbose != 0) {
                                  _printf(s_Illegal_MOVEUNIT_statement_006305c0);
                                }
                                goto LAB_004ff6f7;
                              }
                              iVar1 = __strnicmp(pcVar3,s_unit__006305dc,5);
                              if (iVar1 == 0) {
                                pcVar3 += 5;
                                iVar1 = events_parse_unit_type((iptr)pcVar3);
                                if (iVar1 == -1) {
                                  if (events_parse_verbose != 0) {
                                    _printf(s_found_unit__s__but__s_is_not_val_00630600,pcVar3,
                                            pcVar3);
                                  }
                                }
                                else {
                                  sVar2 = _strlen(pcVar3);
                                  iVar4 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1)
                                  ;
                                  local_68[0x24] = iVar4;
                                  if (local_68[0x24] == 0) goto LAB_004ff6f7;
                                  FUN_005f22d0(local_68[0x24],pcVar3);
                                  local_68[0x25] = iVar1;
                                  if (events_parse_verbose != 0) {
                                    _printf(s_found_unit__s__unit_id__d__006305e4,pcVar3,iVar1);
                                  }
                                  local_74 = 1;
                                }
                              }
                              else {
                                iVar1 = __strnicmp(pcVar3,s_owner__00630624,6);
                                if (iVar1 == 0) {
                                  pcVar3 += 6;
                                  local_20 = events_parse_civ((iptr)pcVar3);
                                  if (local_20 == -1) {
                                    if (events_parse_verbose != 0) {
                                      _printf(s_found_owner__s__but__s_is_not_va_0063064c,pcVar3,
                                              pcVar3);
                                    }
                                  }
                                  else {
                                    sVar2 = _strlen(pcVar3);
                                    iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),
                                                               sVar2 + 1);
                                    local_68[0x22] = iVar1;
                                    if (local_68[0x22] == 0) goto LAB_004ff6f7;
                                    FUN_005f22d0(local_68[0x22],pcVar3);
                                    local_68[0x23] = local_20;
                                    if (events_parse_verbose != 0) {
                                      _printf(s_found_owner__s__king_id__d__0063062c,pcVar3,local_20
                                             );
                                    }
                                    local_84 = 1;
                                  }
                                }
                                else {
                                  iVar1 = __strcmpi(pcVar3,s_maprect_00630674);
                                  if (iVar1 == 0) {
                                    if (events_parse_verbose != 0) {
                                      _printf(s_found_maprect_0063067c);
                                    }
                                    iVar1 = text_read_line(1);
                                    if (iVar1 == 0) {
                                      if (events_parse_verbose != 0) {
                                        _printf(s_Got_early_end_of_file__0063068c);
                                      }
                                      goto LAB_004ff6f7;
                                    }
                                    for (local_38 = 0; local_38 < 4; local_38++) {
                                      iVar1 = text_next_int();
                                      local_68[local_38 * 2 + 0x27] = iVar1;
                                      iVar1 = text_next_int();
                                      local_68[local_38 * 2 + 0x28] = iVar1;
                                      if (events_parse_verbose != 0) {
                                        _printf(s_found_location__d___d___d_006306a4,local_24,
                                                local_68[local_38 * 2 + 0x27],
                                                local_68[local_38 * 2 + 0x28]);
                                      }
                                      local_24++;
                                    }
                                  }
                                  else {
                                    iVar1 = __strcmpi(pcVar3,s_moveto_006306c0);
                                    if (iVar1 == 0) {
                                      if (events_parse_verbose != 0) {
                                        _printf(s_found_moveto_006306c8);
                                      }
                                      pcVar3 = (char *)text_read_line(1);
                                      if (pcVar3 == (char *)0x0) {
                                        if (events_parse_verbose != 0) {
                                          _printf(s_Got_early_end_of_file__006306d8);
                                        }
                                        goto LAB_004ff6f7;
                                      }
                                      if (((('/' < *pcVar3) && (*pcVar3 < ':')) || (*pcVar3 == '-'))
                                         || (*pcVar3 == '+')) {
                                        iVar1 = text_next_int();
                                        local_68[0x2f] = iVar1;
                                        iVar1 = text_next_int();
                                        local_68[0x30] = iVar1;
                                        if (events_parse_verbose != 0) {
                                          _printf(s_found_moveto___d___d_006306f0,local_68[0x2f],
                                                  local_68[0x30]);
                                        }
                                        local_5c = 1;
                                      }
                                    }
                                    else {
                                      iVar1 = __strnicmp(pcVar3,s_numbertomove__00630708,0xd);
                                      if (iVar1 == 0) {
                                        pcVar3 += 0xd;
                                        if ((*pcVar3 < '0') || ('9' < *pcVar3)) {
                                          iVar1 = __strcmpi(pcVar3,&events_numbertomove_all_str);
                                          if (iVar1 == 0) {
                                            local_68[0x26] = -2;
                                            if (events_parse_verbose != 0) {
                                              _printf(s_found_numbertomove__s_00630740,pcVar3);
                                            }
                                            local_70 = 1;
                                          }
                                          else if (events_parse_verbose != 0) {
                                            _printf(s_found_numbertomove__s__but__s_is_00630758,
                                                    pcVar3,pcVar3);
                                          }
                                        }
                                        else {
                                          iVar1 = str_parse_int_prefixed((iptr)pcVar3);
                                          local_68[0x26] = iVar1;
                                          if (events_parse_verbose != 0) {
                                            _printf(s_found_numbertomove__s__integer___00630718,
                                                    pcVar3,local_68[0x26]);
                                          }
                                          local_70 = 1;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                            local_68[1] = local_68[1] | 2;
                          }
                          else {
                            iVar1 = __strcmpi(local_3c,s_PLAYCDTRACK_00630784);
                            if (iVar1 == 0) {
                              if (events_parse_verbose != 0) {
                                _printf(s__THEN_PLAYCDTRACK_found__looking_00630790);
                              }
                              iVar1 = text_read_line(1);
                              if (iVar1 == 0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_Got_early_end_of_file__006307c4);
                                }
                                goto LAB_004ff6f7;
                              }
                              iVar1 = text_next_int();
                              local_68[0x62] = iVar1;
                              if (0 < local_68[0x62]) {
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_cd_track__d_006307dc,local_68[0x62]);
                                }
                                local_68[1] = local_68[1] | 0x80;
                              }
                            }
                            else {
                              iVar1 = __strcmpi(local_3c,s_PLAYWAVEFILE_006307f0);
                              if (iVar1 == 0) {
                                if (events_parse_verbose != 0) {
                                  _printf(s__THEN_PLAYWAVEFILE_found__lookin_00630800);
                                }
                                pcVar3 = (char *)text_read_line(1);
                                if (pcVar3 == (char *)0x0) {
                                  if (events_parse_verbose != 0) {
                                    _printf(s_Got_early_end_of_file__00630834);
                                  }
                                  goto LAB_004ff6f7;
                                }
                                sVar2 = _strlen(pcVar3);
                                iVar1 = memblock_alloc((iptr)(this->pad_294 + 0x60),sVar2 + 1);
                                local_68[0x61] = iVar1;
                                if (local_68[0x61] == 0) goto LAB_004ff6f7;
                                FUN_005f22d0(local_68[0x61],pcVar3);
                                if (events_parse_verbose != 0) {
                                  _printf(s_found_wave_file_name__s_0063084c,local_68[0x61]);
                                }
                                local_68[1] = local_68[1] | 0x10;
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
    } while (local_4c < 10);
    local_44 = 0;
  }
LAB_004ff6f7:
  if (local_44 != 0) {
    __chdir(&game_home_dir);
    popup_game(ADDR(0x630868, ((u8 *)&g.d_00630868)));
    __chdir(&scenario_dir_path);
  }
  return local_44;
}
#undef local_84
#undef local_80
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_3c
#undef local_38
#undef local_34
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 0051d9a0 auto */
#define net_adapter_index (*(UINT *)((u8 *)&g.d_006ad2fc))
#define net_max_players (*(UINT *)((u8 *)&g.d_006c3164))
#define net_timeout_seconds (*(UINT *)((u8 *)&g.d_006ad8b8))
#define net_xd_adapter_index (*(UINT *)((u8 *)&g.d_006c8fbc))
#define prefs_multiplayer_type (*(short *)((u8 *)&g.d_0066653a))
#define scenario_events_loaded (*(i32 *)((u8 *)&g.d_00627670))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define local_30c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(UINT *)(frame_ + FRAME_OFF(8)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl setup_choose_multiplayer_type(void)

{
  UINT UVar1;
  UINT UVar2;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
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
  local_308 = GetPrivateProfileIntA
                        (s_Civilization_Gold_00631fa8,s_MaxPlayers_00631f9c,-1,s_CIV_INI_00631f94);
  if (4 < (int)local_308) {
    if (7 < (int)local_308) {
      local_308 = 7;
    }
    net_max_players = local_308;
    WritePrivateProfileStringA
              (s_Civilization_Gold_00631fd4,s_MaxPlayers_00631fc8,&net_ini_maxplayers_clear_str,s_CIV_INI_00631fbc);
  }
  game.multiplayer = '\0';
  game.civs_alive = '\0';
  game.human_players = '\0';
  FUN_005f22d0(&scenario_dir_path,&game_home_dir);
  scenario_events_loaded = 0;
  passwords_reset();
  if (net_lobby_launch_mode == -1) {
    setup_show_side_picture(7,1);
    dlg_load_game_section(&local_304,ADDR(0x631fe8, ((u8 *)&g.d_00631fe8)),1);
    dialog_set_default_choice((DialogOptionList *)&local_304,(int)prefs_multiplayer_type);
    iVar3 = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
    uVar4 = setup_next_dialog_x(1);
    dialog_set_position((C_0040bc40_28 *)&local_304,uVar4,iVar3);
    local_30c = dlg_show_modal(&local_304,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    if (local_30c < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0051dd72 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
      uVar4 = 1;
      goto LAB_0051dd88;
    }
    prefs_multiplayer_type = (short)local_30c;
  }
  else {
    local_30c = 2;
  }
  if ((local_30c < 0) || (3 < local_30c)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x632020, ((u8 *)&g.d_00632020)),ADDR(0x631ff4, ((u8 *)&g.d_00631ff4)),0x66);
  }
  switch(local_30c) {
  case 0:
    iVar3 = setup_hotseat_game();
    break;
  case 1:
    iVar3 = setup_network_game(1);
    break;
  case 2:
    iVar3 = setup_network_game(0);
    if (iVar3 == 0) goto switchD_0051dd3a_default;
    UVar2 = net_adapter_index;
    UVar1 = net_xd_adapter_index;
    if (net_lobby_launch_mode != -1) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0051dd72 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
      uVar4 = 1;
LAB_0051dd88:
      return uVar4;
    }
    goto LAB_0051daa8;
  case 3:
    net_max_players = 2;
    iVar3 = setup_network_game(4);
    break;
  default:
    goto switchD_0051dd3a_default;
  }
  UVar2 = net_adapter_index;
  UVar1 = net_xd_adapter_index;
  if (iVar3 == 0) {
switchD_0051dd3a_default:
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0051dd72 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    uVar4 = 0;
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
#undef local_30c
#undef local_308
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_32c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_328 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_324 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_314 (*(u8 *)(frame_ + FRAME_OFF(28)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(792)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(796)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(800)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(808)))
i32 __cdecl setup_choose_game_options(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  setup_select_opponents = 0;
  setup_accelerated_start = 0;
  leaders_fixup_names();
  game.field_0e = 0;
LAB_0051ddf1:
  do {
    do {
      setup_show_side_picture(3,0);
      dlg_load_game_section(&local_30c,ADDR(0x63203c, ((u8 *)&g.d_0063203c)),1);
      dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_difficulty);
      dialog_set_position
                ((C_0040bc40_28 *)&local_30c,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      local_14 = dlg_show_modal(&local_30c,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      if (local_14 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0051e9e7 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
        uVar4 = 1;
LAB_0051e9fd:
        return uVar4;
      }
      game.difficulty = (u8)local_14;
      prefs_difficulty = (short)local_14;
      setup_show_side_picture(4,0);
      dlg_load_game_section(&local_30c,ADDR(0x632048, ((u8 *)&g.d_00632048)),1);
      dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_enemies_choice);
      dialog_set_position
                ((C_0040bc40_28 *)&local_30c,
                 -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar2 = dlg_show_modal(&local_30c,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    } while (iVar2 < 0);
    if (local_30c.field_dc == 0) {
      prefs_enemies_choice = (short)iVar2;
      game.num_enemies = 6 - (char)iVar2;
    }
    else {
      iVar2 = _rand();
      game.num_enemies = (char)(iVar2 % 5) + 2;
    }
    setup_show_side_picture(5,0);
    dlg_load_game_section(&local_30c,ADDR(0x632054, ((u8 *)&g.d_00632054)),1);
    dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_barbarity);
    dialog_set_position
              ((C_0040bc40_28 *)&local_30c,
               ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    iVar2 = dlg_show_modal(&local_30c,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  } while (iVar2 < 0);
  if (local_30c.field_dc == 0) {
    local_314 = (u8)iVar2;
    game.barbarian_activity = local_314;
    prefs_barbarity = (short)iVar2;
  }
  else if (game.difficulty < 2) {
    iVar2 = _rand();
    bVar1 = (byte)(iVar2 >> 0x1f);
    game.barbarian_activity =
         ((((byte)iVar2 ^ bVar1) - bVar1 & 1 ^ bVar1) - bVar1) + game.difficulty;
  }
  else if (game.difficulty < 5) {
    iVar2 = _rand();
    game.barbarian_activity = (char)(iVar2 % 3) + 1;
  }
  else {
    iVar2 = _rand();
    bVar1 = (byte)(iVar2 >> 0x1f);
    game.barbarian_activity = ((((byte)iVar2 ^ bVar1) - bVar1 & 1 ^ bVar1) - bVar1) + 2;
  }
LAB_0051e0f3:
  game.rules = 0x3f;
  setup_show_side_picture(9,0);
  dlg_load_game_section(&local_30c,ADDR(0x632060, ((u8 *)&g.d_00632060)),1);
  dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_rules_choice);
  dialog_set_position
            ((C_0040bc40_28 *)&local_30c,
             -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  iVar2 = dlg_show_modal(&local_30c,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  if (-1 < iVar2) {
    prefs_rules_choice = (short)iVar2;
    if (iVar2 != 0) goto LAB_0051e1c8;
    goto LAB_0051e6b0;
  }
  goto LAB_0051ddf1;
LAB_0051e1c8:
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
  setup_show_side_picture(9,0);
  dialog_load_text_section(&local_30c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632068, ((u8 *)&g.d_00632068)),0,0,0,0,0,0);
  if (((byte)local_30c.field_3c & 4) != 0) {
    for (local_18 = 0; local_18 < (int)local_30c.field_28; local_18++) {
      dialog_set_option_checked
                ((DialogOptionList *)&local_30c,local_18,1 << ((byte)local_18 & 0x1f) & dlg_check_bits);
    }
  }
  dialog_set_position
            ((C_0040bc40_28 *)&local_30c,
             ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  iVar2 = dlg_show_modal(&local_30c,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  if (-1 < iVar2) {
    dlg_help_pressed = local_30c.field_dc;
    if (((byte)local_30c.field_3c & 4) != 0) {
      dlg_check_bits = 0;
      for (local_18 = 0; local_18 < (int)local_30c.field_28; local_18++) {
        iVar2 = dialog_option_is_checked((DialogOptionList *)&local_30c,local_18);
        if (iVar2 != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)local_18 & 0x1f);
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
    setup_select_opponents = dlg_check_get(2);
    setup_accelerated_start = dlg_check_get(3);
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
    if (setup_accelerated_start != 0) {
      game.first_launch_turn = -1;
      iVar2 = game_turn_to_year(0);
      if (iVar2 < 1) {
        uVar3 = game_turn_to_year(0);
        local_324 = ~uVar3 + 1;
      }
      else {
        local_324 = game_turn_to_year(0);
      }
      text_set_number_arg(0,local_324);
      iVar2 = game_turn_to_year(0x15);
      if (iVar2 < 1) {
        uVar3 = game_turn_to_year(0x15);
        local_328 = ~uVar3 + 1;
      }
      else {
        local_328 = game_turn_to_year(0x15);
      }
      text_set_number_arg(1,local_328);
      iVar2 = game_turn_to_year(0x29);
      if (iVar2 < 1) {
        uVar3 = game_turn_to_year(0x29);
        local_32c = ~uVar3 + 1;
      }
      else {
        local_32c = game_turn_to_year(0x29);
      }
      text_set_number_arg(2,local_32c);
      setup_show_side_picture(9,0);
      dlg_load_game_section(&local_30c,ADDR(0x632074, ((u8 *)&g.d_00632074)),1);
      dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_accelerated_start);
      dialog_set_position
                ((C_0040bc40_28 *)&local_30c,
                 -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      setup_accelerated_start = dlg_show_modal(&local_30c,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
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
      dialog_load_text_section(&local_30c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632080, ((u8 *)&g.d_00632080)),0,0,0,0,0,0);
      if (ini_simultaneous_allowed == 0) {
        mp_simultaneous_moves = 0;
        mp_simultaneous_setting = 0;
      }
      else {
        text_clear();
        text_append_label(0x364);
        dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
        dlg_check_set(6,(int)prefs_mp_simultaneous_moves);
      }
      if (((byte)local_30c.field_3c & 4) != 0) {
        for (local_18 = 0; local_18 < (int)local_30c.field_28; local_18++) {
          dialog_set_option_checked
                    ((DialogOptionList *)&local_30c,local_18,
                     1 << ((byte)local_18 & 0x1f) & dlg_check_bits);
        }
      }
      if ((param_2 == 1) &&
         (dialog_set_option_disabled((DialogOptionList *)&local_30c,3,1), ini_simultaneous_allowed != 0))
      {
        dialog_set_option_disabled((DialogOptionList *)&local_30c,6,1);
      }
      dialog_set_position
                ((C_0040bc40_28 *)&local_30c,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar2 = dlg_show_modal(&local_30c,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      if (iVar2 < 0) break;
      uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,0);
      mp_open_game = (short)uVar4;
      prefs_mp_open_game = mp_open_game;
      uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,1);
      mp_kill_civ_on_retire = (short)uVar4;
      prefs_mp_kill_on_retire = mp_kill_civ_on_retire;
      uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,2);
      mp_show_human_starts = (short)uVar4;
      prefs_mp_show_human_starts = mp_show_human_starts;
      uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,3);
      mp_chat_from_start = (short)uVar4;
      prefs_mp_chat_from_start = mp_chat_from_start;
      uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,4);
      mp_double_production = (short)uVar4;
      prefs_mp_double_production = mp_double_production;
      uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,5);
      mp_double_moves = (short)uVar4;
      prefs_mp_double_moves = mp_double_moves;
      if (ini_simultaneous_allowed != 0) {
        uVar4 = dialog_option_is_checked((DialogOptionList *)&local_30c,6);
        mp_simultaneous_setting = (short)uVar4;
        prefs_mp_simultaneous_moves = mp_simultaneous_setting;
      }
      if (param_2 == 1) {
        mp_chat_from_start = 0;
        mp_simultaneous_setting = 0;
      }
      if ((param_2 == 2) || (iVar2 = setup_choose_game_timer(0), iVar2 == 0)) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0051e9e7 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
        uVar4 = 0;
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
#undef local_32c
#undef local_328
#undef local_324
#undef local_314
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0051ea8e auto */
#define autoplay_active (*(ushort *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(short *)((u8 *)&g.d_00654faa))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define net_vote_status (*(int *)((u8 *)&g.d_006ad670))
#define prefs_turn_timer_choice (*(short *)((u8 *)&g.d_006665d0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define _DAT_006cec80 (*(i32 *)((u8 *)&g.d_006cec80))
#define local_324 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_320 (*(char (*)[16])(frame_ + FRAME_OFF(8)))
#define local_310 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(780)))
#define local_18 (*(short *)(frame_ + FRAME_OFF(784)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(788)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(792)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(800)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl setup_choose_game_timer(int param_1)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_310,0x2000);
  local_8 = 0;
  local_18 = prefs_turn_timer_choice;
  local_14 = mp_turn_time_limit_ms;
LAB_0051ead8:
  prefs_turn_timer_choice = local_18;
  if ((param_1 == 0) && (turn_resume_new_game == 0)) {
    setup_show_side_picture(0xffffffff,0);
    dlg_load_game_section(&local_310,ADDR(0x63208c, ((u8 *)&g.d_0063208c)),1);
    dialog_set_default_choice((DialogOptionList *)&local_310,(int)prefs_turn_timer_choice);
    dialog_set_position
              ((C_0040bc40_28 *)&local_310,0xfffffc19,
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  }
  else {
    dlg_load_game_section(&local_310,ADDR(0x632098, ((u8 *)&g.d_00632098)),1);
    dialog_set_default_choice((DialogOptionList *)&local_310,(int)prefs_turn_timer_choice);
    dialog_set_position((C_0040bc40_28 *)&local_310,0xfffffc19,0xfffffc19);
  }
  local_324 = dlg_show_modal(&local_310,0);
  if (local_324 < 0) {
    if (param_1 == 0) {
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
    uVar2 = 1;
    goto LAB_0051f10b;
  }
  prefs_turn_timer_choice = (short)local_324;
  switch(local_324) {
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
  if (param_1 == 0) {
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    if (local_324 == 6) {
      FUN_005f22d0(&prefs_turn_timer_custom,local_320);
    }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
    uVar2 = 0;
    goto LAB_0051f10b;
  }
  if (1 < net_player_count) {
    FUN_005f22d0(&text_string_args,&net_local_player_name);
    str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
    if (mp_turn_time_limit_ms == 0) {
      str_append_label(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0x285);
    }
    else {
      iVar1 = (mp_turn_time_limit_ms / 1000) / 0x3c;
      iVar3 = (mp_turn_time_limit_ms / 1000) % 0x3c;
      if (iVar1 < 10) {
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0);
      }
      str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),iVar1);
      FUN_005f22e0(&text_string_arg1,&setup_timer_minsec_sep_str);
      if (iVar3 < 10) {
        str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0);
      }
      str_append_int(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),iVar3);
    }
    net_vote_replies_pending = net_player_count - 1;
    net_vote_status = 0;
    net_send_text_args(0x40,0xff,2,0,0,0);
    dlg_pending_idle_callback = ((void *)ADDR(0x004019b5, net_vote_wait_idle_cb));
    _DAT_006cec80 = timer_ticks();
    iVar1 = popup_game_sprite_flags(ADDR(0x6320b8, ((u8 *)&g.d_006320b8)),0x2000001,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    if (((iVar1 < 0) || (net_vote_status == -1)) || (net_vote_replies_pending != 0)) {
      prefs_turn_timer_choice = local_18;
      mp_turn_time_limit_ms = local_14;
      net_send_text_args(0x41,0xff,0,0,0,0);
      popup_game_with_sprite(ADDR(0x6320cc, ((u8 *)&g.d_006320cc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
      uVar2 = 1;
      goto LAB_0051f10b;
    }
    net_send_text_args(0x42,0xff,0,0,0,0);
    popup_game_with_sprite(ADDR(0x6320dc, ((u8 *)&g.d_006320dc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  uVar2 = 0;
LAB_0051f10b:
  return uVar2;
switchD_0051edf7_caseD_6:
  while( true ) {
    iVar1 = dialog_load_text_section(&local_310,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6320a4, ((u8 *)&g.d_006320a4)),4,ADDR(0x6665d2, ((u8 *)&g.d_006665d2)),0,0,0,1);
    if (iVar1 != 0) {
      if (param_1 == 0) {
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0051f0f5 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
      uVar2 = 1;
      goto LAB_0051f10b;
    }
    if (param_1 == 0) {
      dialog_set_position
                ((C_0040bc40_28 *)&local_310,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    }
    else {
      dialog_set_position((C_0040bc40_28 *)&local_310,0xfffffc19,0xfffffc19);
    }
    local_324 = dialog_run_modal(&local_310,(iptr)local_320,0);
    snd_play_effect(0x6a,0,0,0);
    if (local_324 < 0) break;
    local_1c = _atoi(local_320);
    if (local_1c < 0) {
      autoplay_active = autoplay_active ^ 1;
      autoplay_turns_left = -(short)local_1c;
    }
    else if ((local_1c < 0xe11) && (9 < local_1c)) {
      mp_turn_time_limit_ms = local_1c * 1000;
      goto switchD_0051edf7_default;
    }
  }
  if (param_1 == 0) {
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
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
#undef _DAT_006cec80
#undef local_324
#undef local_320
#undef local_310
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define _DAT_006ad120 (*(i32 *)((u8 *)&g.d_006ad120))
#define _DAT_006ad124 (*(i32 *)((u8 *)&g.d_006ad124))
#define _DAT_006ad128 (*(i32 *)((u8 *)&g.d_006ad128))
#define _DAT_006ad12c (*(i32 *)((u8 *)&g.d_006ad12c))
#define _DAT_006ad178 (*(i32 *)((u8 *)&g.d_006ad178))
#define _DAT_006ad674 (*(i32 *)((u8 *)&g.d_006ad674))
#define local_448 (*(i8 * *)(frame_ + FRAME_OFF(0)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_43c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_434 (*(u8 *)(frame_ + FRAME_OFF(20)))
#define local_430 (*(char (*)[260])(frame_ + FRAME_OFF(24)))
#define local_32c (*(int *)(frame_ + FRAME_OFF(284)))
#define local_328 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_324 (*(int *)(frame_ + FRAME_OFF(292)))
#define local_320 (*(iptr *)(frame_ + FRAME_OFF(296)))
#define local_31c (*(Dialog *)(frame_ + FRAME_OFF(300)))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(1056)))
#define local_24 (*(byte * *)(frame_ + FRAME_OFF(1060)))
#define leader2 (*(iptr *)(frame_ + FRAME_OFF(1064)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(1068)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1072)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1076)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1088)))
/* WARNING: Removing unreachable block (ram,0x005212c5) */
/* WARNING: Removing unreachable block (ram,0x005213cc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl setup_choose_tribe(int param_1,int param_2,int param_3)

{
  int iVar1;
  iptr iVar2;
  int iVar3;
  i32 uVar4;
  iptr iVar4;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  leader2 = -1;
  local_324 = 1;
  local_28 = -1;
  dialog_ctor(&local_31c,0x2000);
  local_8 = 0;
  local_320 = 0;
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
      for (local_1c = 0; local_1c < 7; local_1c++) {
        if (leaders[leader2].titles[local_1c][0] < 1) {
          *(ushort *)&leaders[leader2].titles[local_1c][0] =
               ~*(ushort *)&leaders[leader2].titles[local_1c][0] + 1;
        }
        if (leaders[leader2].titles[local_1c][1] < 1) {
          *(ushort *)&leaders[leader2].titles[local_1c][1] =
               ~*(ushort *)&leaders[leader2].titles[local_1c][1] + 1;
        }
      }
    }
    if (param_3 == 0) {
      setup_show_side_picture(6,0);
    }
    dlg_load_game_section(&local_31c,ADDR(0x6320ec, ((u8 *)&g.d_006320ec)),1);
    dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
    dialog_set_default_choice((DialogOptionList *)&local_31c,(int)prefs_gender);
    if (param_3 == 0) {
      dialog_set_position
                ((C_0040bc40_28 *)&local_31c,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    }
    if (2 < param_2) {
      dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
    }
    iVar1 = dlg_show_modal(&local_31c,0);
    snd_play_effect(0x6a,0,0,0);
    if (param_3 == 0) {
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    }
    if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
      text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
      FUN_005f22d0(&text_string_args,net_connection_title);
      if (nm_server_canceled_count == 0) {
        popup_game_with_sprite(ADDR(0x632100, ((u8 *)&g.d_00632100)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      else {
        popup_game_with_sprite(ADDR(0x6320f4, ((u8 *)&g.d_006320f4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      local_324 = 1;
      goto LAB_0052144f;
    }
    if (iVar1 < 0) goto LAB_0052144f;
    prefs_gender = (short)iVar1;
    _DAT_006ad128 = (int)prefs_gender;
    if (param_3 == 0) {
      setup_show_side_picture(0xffffffff,0);
    }
    local_18 = dialog_load_text(&local_31c,ADDR(0x632114, ((u8 *)&g.d_00632114)),ADDR(0x63210c, ((u8 *)&g.d_0063210c)),0x801);
    if (local_18 != 0) {
      if (param_3 == 0) {
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      }
      goto LAB_0052144f;
    }
    if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
      text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
      FUN_005f22d0(&text_string_args,net_connection_title);
      if (nm_server_canceled_count == 0) {
        popup_game_with_sprite(ADDR(0x632128, ((u8 *)&g.d_00632128)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      else {
        popup_game_with_sprite(ADDR(0x63211c, ((u8 *)&g.d_0063211c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      local_324 = 1;
      goto LAB_0052144f;
    }
    dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
    dialog_set_columns((C_0040bc40_3c *)&local_31c,3);
    local_328 = 0;
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
        for (local_1c = 0; local_1c < 7; local_1c++) {
          if (leaders[leader].titles[local_1c][0] < 1) {
            *(ushort *)&leaders[leader].titles[local_1c][0] =
                 ~*(ushort *)&leaders[leader].titles[local_1c][0] + 1;
          }
          if (leaders[leader].titles[local_1c][1] < 1) {
            *(ushort *)&leaders[leader].titles[local_1c][1] =
                 ~*(ushort *)&leaders[leader].titles[local_1c][1] + 1;
          }
        }
      }
      if ((((uint)game.human_players & 1 << ((byte)leaders[leader].color & 0x1f)) == 0) ||
         (-1 < leaders[leader].plural)) {
        uVar4 = 0;
        iVar4 = leader;
        iVar2 = label_string((int)leaders[leader].plural);
        dialog_add_option((DialogOptionList *)&local_31c,iVar2,iVar4,uVar4);
      }
      else {
        dialog_add_option
                  ((DialogOptionList *)&local_31c,(iptr)&civ_names[leaders[leader].color].tribe_name,leader
                   ,0);
      }
    }
LAB_0051f8c0:
    local_328 = 0;
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
        for (local_1c = 0; local_1c < 7; local_1c++) {
          if (leaders[leader].titles[local_1c][0] < 1) {
            *(ushort *)&leaders[leader].titles[local_1c][0] =
                 ~*(ushort *)&leaders[leader].titles[local_1c][0] + 1;
          }
          if (leaders[leader].titles[local_1c][1] < 1) {
            *(ushort *)&leaders[leader].titles[local_1c][1] =
                 ~*(ushort *)&leaders[leader].titles[local_1c][1] + 1;
          }
        }
      }
      if ((((uint)game.human_players & 1 << ((byte)leaders[leader].color & 0x1f)) == 0) &&
         (((int)net_claimed_civs_mask & 1 << ((byte)leaders[leader].color & 0x1f)) == 0)) {
        local_328++;
        dialog_set_option_disabled((DialogOptionList *)&local_31c,leader,0);
        if ((RadioGroupDisableView *)local_31c.field_268 != (RadioGroupDisableView *)0x0) {
          radiogrp_enable_item((RadioGroupEnableView *)local_31c.field_268,leader);
        }
      }
      else {
        dialog_set_option_disabled((DialogOptionList *)&local_31c,leader,1);
        if ((RadioGroupDisableView *)local_31c.field_268 != (RadioGroupDisableView *)0x0) {
          radiogrp_disable_item((RadioGroupDisableView *)local_31c.field_268,leader);
        }
      }
    }
    if (local_328 == 0) {
      popup_game(ADDR(0x632134, ((u8 *)&g.d_00632134)));
      dialog_close(&local_31c);
      goto LAB_0052144f;
    }
    for (local_32c = 0; local_32c < 0x15; local_32c++) {
      local_24 = (byte *)dialog_find_option((DialogOptionList *)&local_31c,local_320);
      if ((local_24 != (byte *)0x0) && ((*local_24 & 1) == 0)) {
        dialog_set_default_choice((DialogOptionList *)&local_31c,*(iptr *)(local_24 + 4));
        if ((RadioGroupDisableView *)local_31c.field_268 != (RadioGroupDisableView *)0x0) {
          radiogrp_set_selected
                    ((RadioGroupSetSelView *)local_31c.field_268,*(i32 *)(local_24 + 4));
        }
        break;
      }
      local_320++;
      if (local_320 == 0x15) {
        local_320 = 0;
      }
    }
    if (param_3 == 0) {
      dialog_set_position
                ((C_0040bc40_28 *)&local_31c,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    }
    if (2 < param_2) {
      net_reset_msg_counts();
      _DAT_006ad674 = timer_ticks();
    }
    local_31c.field_3c = local_31c.field_3c & 0xfffffbff;
    local_31c.field_d8 = 0;
    local_31c.field_dc = 0;
    if (2 < param_2) {
      dlg_pending_idle_callback = ((void *)ADDR(0x0040126c, net_lock_wait_idle_cb));
    }
    leader2 = dlg_show_modal(&local_31c,0);
    local_320 = radiogrp_get_selected((RadioGroupGetSelView *)local_31c.field_268);
    if (2 < param_2) {
      if (nm_lock_data_count == 0) {
        if ((nm_server_canceled_count == 0) && (nm_lost_server_on_join_count == 0)) goto LAB_0051fdd1;
        text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
        FUN_005f22d0(&text_string_args,net_connection_title);
        if (nm_server_canceled_count == 0) {
          popup_game_with_sprite(ADDR(0x63214c, ((u8 *)&g.d_0063214c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x632140, ((u8 *)&g.d_00632140)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        if (param_3 == 0) {
          setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        }
        dialog_close(&local_31c);
        goto LAB_0052144f;
      }
      local_28 = leader2;
      goto LAB_0051f8c0;
    }
LAB_0051fdd1:
    snd_play_effect(0x6a,0,0,0);
    if (leader2 < 0) {
      if (param_3 == 0) {
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      }
      dialog_close(&local_31c);
      goto LAB_0051f1f6;
    }
    local_320 = leader2;
    _DAT_006ad124 = leader2;
    game.player_civ = (i8)leaders[leader2].color;
    _DAT_006ad120 = (int)game.player_civ;
    if (2 < param_2) {
      net_reset_msg_counts();
      net_send_message(0x30,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
      if (net_host_flag == '\0') {
        local_14 = timer_ticks();
        while (((nm_nation_accept_count == 0 && (nm_nation_reject_count == 0)) &&
               (iVar3 = timer_ticks(), iVar3 - local_14 < net_timeout_seconds * 0x3c))) {
          if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
            text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
            FUN_005f22d0(&text_string_args,net_connection_title);
            if (nm_server_canceled_count == 0) {
              popup_game_with_sprite(ADDR(0x632164, ((u8 *)&g.d_00632164)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            else {
              popup_game_with_sprite(ADDR(0x632158, ((u8 *)&g.d_00632158)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            local_324 = 1;
            goto LAB_0052144f;
          }
          net_process_messages((NetSession *)&net_session,1,0);
        }
      }
      if ((nm_nation_accept_count == 0) && (nm_nation_reject_count == 0)) {
        popup_game_with_sprite(ADDR(0x632170, ((u8 *)&g.d_00632170)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        if (param_3 == 0) {
          setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        }
        dialog_close(&local_31c);
        goto LAB_0052144f;
      }
      if (nm_nation_reject_count == 0) goto LAB_0051ffec;
      local_28 = leader2;
      popup_game_with_sprite(ADDR(0x632184, ((u8 *)&g.d_00632184)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      goto LAB_0051f8c0;
    }
LAB_0051ffec:
    if (param_3 == 0) {
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    }
    prefs_tribe = (i16)leader2;
    civs[game.player_civ].tribe = prefs_tribe;
    civs[game.player_civ].leader_portrait = (u8)leader2;
    if (iVar1 != 0) {
      civs[game.player_civ].leader_portrait += 21;
    }
    human_civ = (iptr)game.player_civ;
    game.human_players = (byte)(1 << (game.player_civ & 0x1fU)) | game.human_players;
    local_434 = (u8)iVar1;
    leaders[civs[game.player_civ].tribe].female = local_434;
    leaders[civs[game.player_civ].tribe].leader_name =
         leaders[civs[game.player_civ].tribe].names[((uint)leaders[civs[game.player_civ].tribe].female)];
    uVar4 = label_string((int)leaders[civs[game.player_civ].tribe].leader_name);
    FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,uVar4);
    leaders[civs[game.player_civ].tribe].leader_name =
         -leaders[civs[game.player_civ].tribe].leader_name;
    iVar3 = civ_check_password(human_civ);
    if (iVar3 != 0) {
      _DAT_006ad12c = 0;
      _DAT_006ad178 = 0;
      if (local_31c.field_dc == 0) {
        do {
          if (param_3 == 0) {
            setup_show_side_picture(7,0);
          }
          dialog_load_text_section
                    (&local_31c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6321f8, ((u8 *)&g.d_006321f8)),0x17,(iptr)&civ_names[game.player_civ].leader_name,0,0,0,1);
          dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
          if (param_3 == 0) {
            dialog_set_position
                      ((C_0040bc40_28 *)&local_31c,0xfffffc19,
                       -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
          }
          if (2 < param_2) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          }
          local_18 = dialog_run_modal(&local_31c,(iptr)local_430,0);
        } while (local_430[0] == '\0');
        if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
          text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
          FUN_005f22d0(&text_string_args,net_connection_title);
          if (nm_server_canceled_count == 0) {
            popup_game_with_sprite(ADDR(0x63220c, ((u8 *)&g.d_0063220c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x632200, ((u8 *)&g.d_00632200)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          local_324 = 1;
          goto LAB_0052144f;
        }
        snd_play_effect(0x6a,0,0,0);
        if (param_3 == 0) {
          setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        }
        if (local_18 != 0) {
          game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
          if (2 < param_2) {
            net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
          }
          goto LAB_0051f1f6;
        }
        FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,local_430);
        FUN_005f22d0(&net_player_info_leader_name,local_430);
        net_player_info_tribe_name = '\0';
        net_player_info_adjective = '\0';
      }
      else {
        if (((net_player_info_tribe_name == '\0') || (net_player_info_adjective == '\0')) || (param_2 == 1)) {
          uVar4 = label_string((int)leaders[civs[game.player_civ].tribe].plural);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].tribe_name,uVar4);
          uVar4 = label_string((int)leaders[civs[game.player_civ].tribe].adjective);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].adjective,uVar4);
        }
        else {
          FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,&net_player_info_leader_name);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].tribe_name,&net_player_info_tribe_name);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].adjective,&net_player_info_adjective);
        }
        leaders[civs[game.player_civ].tribe].plural = -leaders[civs[game.player_civ].tribe].plural;
        leaders[civs[game.player_civ].tribe].adjective =
             -leaders[civs[game.player_civ].tribe].adjective;
        for (local_1c = 0; local_1c < 7; local_1c++) {
          uVar4 = label_string((int)leaders[civs[game.player_civ].tribe].titles[local_1c][iVar1]);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].titles[local_1c],uVar4);
          leaders[civs[game.player_civ].tribe].titles[local_1c][iVar1] =
               -leaders[civs[game.player_civ].tribe].titles[local_1c][iVar1]
          ;
        }
        while( true ) {
          text_set_string_arg_b(1,(iptr)&civ_names[game.player_civ].tribe_name);
          text_set_string_arg_b(2,(iptr)&civ_names[game.player_civ].adjective);
          if (param_3 == 0) {
            setup_show_side_picture(7,0);
          }
          local_18 = dialog_load_text_section
                               (&local_31c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6321ac, ((u8 *)&g.d_006321ac)),0x17,(iptr)&civ_names[game.player_civ].leader_name,
                                0,0,0,1);
          if (local_18 != 0) {
            game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
            if (param_3 == 0) {
              setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
            }
            if (2 < param_2) {
              net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
            }
            goto LAB_0052144f;
          }
          dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
          if (param_3 == 0) {
            dialog_set_position
                      ((C_0040bc40_28 *)&local_31c,0xfffffc19,
                       -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
          }
          if (2 < param_2) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          }
          iVar1 = dlg_show_modal(&local_31c,0);
          snd_play_effect(0x6a,0,0,0);
          if (param_3 == 0) {
            setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
          }
          if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
            text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
            FUN_005f22d0(&text_string_args,net_connection_title);
            if (nm_server_canceled_count == 0) {
              popup_game_with_sprite(ADDR(0x6321c4, ((u8 *)&g.d_006321c4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            else {
              popup_game_with_sprite(ADDR(0x6321b8, ((u8 *)&g.d_006321b8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            }
            local_324 = 1;
            goto LAB_0052144f;
          }
          if (iVar1 < 0) {
            game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
            if (2 < param_2) {
              net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
            }
            goto LAB_0051f1f6;
          }
          FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,&text_string_args);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].tribe_name,&text_string_arg1);
          FUN_005f22d0((iptr)&civ_names[game.player_civ].adjective,&text_string_arg2);
          FUN_005f22d0(&net_player_info_leader_name,&text_string_args);
          FUN_005f22d0(&net_player_info_tribe_name,&text_string_arg1);
          FUN_005f22d0(&net_player_info_adjective,&text_string_arg2);
          _DAT_006ad12c = 1;
          if (local_31c.field_dc != 1) break;
          if (param_3 == 0) {
            setup_show_side_picture(7,0);
          }
          local_18 = dlg_load_game_section(&local_31c,ADDR(0x6321d0, ((u8 *)&g.d_006321d0)),1);
          if (local_18 != 0) {
            game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
            if (param_3 == 0) {
              setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
            }
            if (2 < param_2) {
              net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
            }
            goto LAB_0052144f;
          }
          dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
          for (local_1c = 0; local_1c < 7; local_1c++) {
            text_clear();
            text_append_string_id(government_names[local_1c]);
            text_append_colon();
            if (((&net_player_info_govt_titles)[local_1c * 0x18] == '\0') || (param_2 == 1)) {
              dialog_add_edit_field
                        ((DialogOptionList *)&local_31c,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&civ_names[game.player_civ].titles[local_1c],0x17);
            }
            else {
              dialog_add_edit_field
                        ((DialogOptionList *)&local_31c,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                         (iptr)(&net_player_info_govt_titles + local_1c * 0x18),0x17);
            }
          }
          if (param_3 == 0) {
            dialog_set_position
                      ((C_0040bc40_28 *)&local_31c,0xfffffc19,
                       -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
          }
          if (2 < param_2) {
            dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          }
          iVar1 = dlg_show_modal(&local_31c,0);
          if (iVar1 == 0) {
            for (local_1c = 0; local_1c < 7; local_1c++) {
              FUN_005f22d0((iptr)&civ_names[game.player_civ].titles[local_1c],
                           &text_string_args + local_1c * 0x104);
              FUN_005f22d0(&net_player_info_govt_titles + local_1c * 0x18,&text_string_args + local_1c * 0x104);
            }
            _DAT_006ad178 = 1;
          }
          snd_play_effect(0x6a,0,0,0);
          if (param_3 == 0) {
            setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
          }
        }
        if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
          text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
          FUN_005f22d0(&text_string_args,net_connection_title);
          if (nm_server_canceled_count == 0) {
            popup_game_with_sprite(ADDR(0x6321ec, ((u8 *)&g.d_006321ec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x6321e0, ((u8 *)&g.d_006321e0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          local_324 = 1;
          goto LAB_0052144f;
        }
      }
      if (param_3 == 0) {
        setup_show_side_picture(8,0);
      }
      dlg_load_game_section(&local_31c,ADDR(0x632218, ((u8 *)&g.d_00632218)),0x20001);
      dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
      for (local_43c = 0; local_43c < 4; local_43c++) {
        iVar2 = label_string(*(i32 *)(label_string_ids + 0x3d8 + local_43c * 4));
        dialog_add_sprite
                  ((DialogOptionList *)&local_31c,local_43c * 0x1e0 + ADDR(0x63fff4, ((u8 *)&g.d_0063fe8c + 360)),local_43c,iVar2);
      }
      dialog_set_default_choice
                ((DialogOptionList *)&local_31c,(int)leaders[civs[game.player_civ].tribe].city_style);
      if (param_3 == 0) {
        dialog_set_position
                  ((C_0040bc40_28 *)&local_31c,
                   -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1)
                   ,-(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1
                     ));
      }
      if (2 < param_2) {
        dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
      }
      iVar1 = dlg_show_modal(&local_31c,0);
      if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
        text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
        FUN_005f22d0(&text_string_args,net_connection_title);
        if (nm_server_canceled_count == 0) {
          popup_game_with_sprite(ADDR(0x632230, ((u8 *)&g.d_00632230)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x632224, ((u8 *)&g.d_00632224)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        local_324 = 1;
        goto LAB_0052144f;
      }
      snd_play_effect(0x6a,0,0,0);
      if (param_3 == 0) {
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
      }
      if (iVar1 < 0) {
        game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
        if (2 < param_2) {
          net_send_message(0x31,0,leader2,(int)game.player_civ,0,0,0,0,0,0);
        }
      }
      else {
        net_player_info_city_style = iVar1;
        civ_names[game.player_civ].city_style = (i16)iVar1;
        local_324 = 0;
        *(iptr *)(&setup_player_tribes + param_1 * 4) = leader2;
        if (param_2 != 2) goto LAB_0052144f;
        if (param_3 == 0) {
          setup_show_side_picture(7,0);
        }
        if (param_1 == 0) {
          local_448 = &prefs_email_address;
        }
        else {
          local_448 = &setup_input_blank_default;
        }
        dialog_load_text_section
                  (&local_31c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632240, ((u8 *)&g.d_00632240)),0x1f,(iptr)local_448,0,0,0,1);
        dialog_prepend_title_label((iptr)&local_31c,param_1 + 0x25e);
        if (param_3 == 0) {
          dialog_set_position
                    ((C_0040bc40_28 *)&local_31c,0xfffffc19,
                     -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) +
                      1));
        }
        local_18 = dialog_run_modal(&local_31c,(iptr)local_430,0);
        if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
          text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
          FUN_005f22d0(&text_string_args,net_connection_title);
          if (nm_server_canceled_count == 0) {
            popup_game_with_sprite(ADDR(0x63225c, ((u8 *)&g.d_0063225c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x632250, ((u8 *)&g.d_00632250)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          local_324 = 1;
          goto LAB_0052144f;
        }
        snd_play_effect(0x6a,0,0,0);
        if (param_3 == 0) {
          setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        }
        if (local_18 == 0) {
          FUN_005f22d0(&civ_email_addresses + game.player_civ * 0x20,local_430);
          if (param_1 == 0) {
            FUN_005f22d0(&prefs_email_address,local_430);
            saved_turn_civ = (i8)human_civ;
            turn_resume_civ = (i8)human_civ;
          }
LAB_0052144f:
          iVar1 = local_324;
          if ((local_324 == 1) && (-1 < leader2)) {
            if (leaders[leader2].leader_name < 1) {
              leaders[leader2].leader_name = ~leaders[leader2].leader_name + 1;
            }
            if (leaders[leader2].plural < 1) {
              leaders[leader2].plural = ~leaders[leader2].plural + 1;
            }
            if (leaders[leader2].adjective < 1) {
              leaders[leader2].adjective = ~leaders[leader2].adjective + 1;
            }
            for (local_1c = 0; local_1c < 7; local_1c++) {
              if (leaders[leader2].titles[local_1c][0] < 1) {
                *(ushort *)&leaders[leader2].titles[local_1c][0] =
                     ~*(ushort *)&leaders[leader2].titles[local_1c][0] + 1;
              }
              if (leaders[leader2].titles[local_1c][1] < 1) {
                *(ushort *)&leaders[leader2].titles[local_1c][1] =
                     ~*(ushort *)&leaders[leader2].titles[local_1c][1] + 1;
              }
            }
          }
          if (((param_3 == 0) && (local_324 == 1)) && (0 < param_1)) {
            if (leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].leader_name < 1) {
              leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].leader_name =
                   ~leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].leader_name + 1;
            }
            if (leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].plural < 1) {
              leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].plural =
                   ~leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].plural + 1;
            }
            if (leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].adjective < 1) {
              leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].adjective =
                   ~leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].adjective + 1;
            }
            for (local_1c = 0; local_1c < 7; local_1c++) {
              if (leaders[(*(int *)(&setup_prev_player_tribe + param_1 * 4))].titles[local_1c][0]
                  < 1) {
                *(ushort *)&leaders[(*(int *)(&setup_prev_player_tribe + param_1 * 4))].titles[local_1c][0]
                     = ~*(ushort *)
                         (*(int *)(&setup_prev_player_tribe + param_1 * 4) * 0x30 + ADDR(0x65550c, ((u8 *)&leaders + 20)) + local_1c * 4) +
                       1;
              }
              if (leaders[(*(int *)(&setup_prev_player_tribe + param_1 * 4))].titles[local_1c][1]
                  < 1) {
                *(ushort *)&leaders[(*(int *)(&setup_prev_player_tribe + param_1 * 4))].titles[local_1c][1]
                     = ~*(ushort *)
                         (*(int *)(&setup_prev_player_tribe + param_1 * 4) * 0x30 + ADDR(0x65550e, ((u8 *)&leaders + 22)) + local_1c * 4) +
                       1;
              }
            }
            game.human_players =
                 ~(byte)(1 << ((byte)leaders[*(int *)(&setup_prev_player_tribe + param_1 * 4)].color & 0x1f)) &
                 game.human_players;
          }
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_00521807 */ { dialog_dtor((Dialog *)((iptr)&local_31c)); }
          return iVar1;
        }
        game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
      }
      goto LAB_0051f1f6;
    }
    if ((nm_server_canceled_count != 0) || (nm_lost_server_on_join_count != 0)) {
      text_set_string_arg(1,ADDR(0x6ad59c, ((u8 *)&g.d_006ad59c)));
      FUN_005f22d0(&text_string_args,net_connection_title);
      if (nm_server_canceled_count == 0) {
        popup_game_with_sprite(ADDR(0x6321a0, ((u8 *)&g.d_006321a0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      else {
        popup_game_with_sprite(ADDR(0x632194, ((u8 *)&g.d_00632194)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      local_324 = 1;
      goto LAB_0052144f;
    }
    snd_play_effect(0x6a,0,0,0);
    if (param_3 == 0) {
      setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
    }
    game.human_players = ~(byte)(1 << (game.player_civ & 0x1fU)) & game.human_players;
    if (2 < param_2) {
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
#undef _DAT_006ad120
#undef _DAT_006ad124
#undef _DAT_006ad128
#undef _DAT_006ad12c
#undef _DAT_006ad178
#undef _DAT_006ad674
#undef local_448
#undef leader
#undef local_43c
#undef local_434
#undef local_430
#undef local_32c
#undef local_328
#undef local_324
#undef local_320
#undef local_31c
#undef local_28
#undef local_24
#undef leader2
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_844 (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define local_410 (*(Dialog *)(frame_ + FRAME_OFF(1080)))
#define local_11c (*(int *)(frame_ + FRAME_OFF(1836)))
#define dst (*(i8 (*)[260])(frame_ + FRAME_OFF(1840)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(2100)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2104)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2108)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(2112)))
i32 __cdecl scenario_start_dialog(int param_1)

{
  iptr iVar1;
  i32 uVar1;
  iptr iVar2;
  int unit;
  i8 frame_[FRAME_OFF(2120)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_410,0x4000);
  local_8 = 0;
  palette_init(&local_844);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
LAB_00521912:
  do {
    if (cd_music_available == 0) {
      snd_cd_stop();
      snd_play_effect(0x6b,0,1,0);
    }
    surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_844);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_flush_paint();
    iVar1 = game_load_dialog(1,param_1,1);
    if (iVar1 != 0) {
      snd_play_effect(0x6a,0,0,0);
      surface_load_gif_resource((DibSurface *)&setup_backdrop_surface,0x5a,10,0xc0,(iptr)&local_844);
      wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x63cbd0, ((u8 *)&g.d_0063cbd0)));
      wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
      wnd_flush_paint();
      local_8 = local_8 & 0xffffff00;
      /* inlined unwind funclet FUN_00521faf */ { palette_destroy((GamePalette *)((iptr)&local_844)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00521fbb */ { dialog_dtor((Dialog *)((iptr)&local_410)); }
      uVar1 = 1;
LAB_00521fd1:
      return uVar1;
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
    uVar1 = game_turn_to_year((int)game.turn);
    text_append_year(uVar1);
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    if (scenario_max_turns == 0) {
      text_append_year(2000);
    }
    else {
      uVar1 = game_turn_to_year((int)scenario_max_turns);
      text_append_year(uVar1);
    }
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (cd_music_available != 0) {
      snd_menu_end();
    }
    dialog_init_default(&local_410);
    iVar2 = dialog_load_text(&local_410,(iptr)dst,ADDR(0x63226c, ((u8 *)&g.d_0063226c)),0x4008001);
    if (iVar2 == 0) goto code_r0x00521b37;
    unit = popup_game_flags(ADDR(0x632278, ((u8 *)&g.d_00632278)),1);
  } while (unit < 0);
  goto LAB_00521c07;
code_r0x00521b37:
  unit = (int)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((int)units[unit].owner == (int)scenario_objective_civ)) {
    dialog_add_sprite
              ((DialogOptionList *)&local_410,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0
               ,0);
  }
  unit = dlg_show_modal(&local_410,0);
  if (-1 < unit) {
LAB_00521c07:
    while( true ) {
      dlg_load_game_section(&local_410,ADDR(0x632288, ((u8 *)&g.d_00632288)),1);
      dialog_set_default_choice((DialogOptionList *)&local_410,(uint)game.difficulty);
      dialog_set_position
                ((C_0040bc40_28 *)&local_410,
                 ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      local_14 = dlg_show_modal(&local_410,0);
      if (local_14 < 0) break;
      game.difficulty = (u8)local_14;
      if ((u8)local_14 == '\0') {
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
        dialog_load_text_section(&local_410,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632294, ((u8 *)&g.d_00632294)),0,0,0,0,0,0);
        if (ini_simultaneous_allowed == 0) {
          mp_simultaneous_moves = 0;
          mp_simultaneous_setting = 0;
        }
        else {
          text_clear();
          text_append_label(0x364);
          dialog_add_option((DialogOptionList *)&local_410,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
          dlg_check_set(6,(int)prefs_mp_simultaneous_moves);
        }
        if (((byte)local_410.field_3c & 4) != 0) {
          for (local_11c = 0; local_11c < (int)local_410.field_28; local_11c++) {
            dialog_set_option_checked
                      ((DialogOptionList *)&local_410,local_11c,
                       1 << ((byte)local_11c & 0x1f) & dlg_check_bits);
          }
        }
        dialog_set_position
                  ((C_0040bc40_28 *)&local_410,
                   ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1,
                   -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1)
                  );
        unit = dlg_show_modal(&local_410,0);
        snd_play_effect(0x6a,0,0,0);
        if (unit < 0) break;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,0);
        mp_open_game = (short)uVar1;
        prefs_mp_open_game = mp_open_game;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,1);
        mp_kill_civ_on_retire = (short)uVar1;
        prefs_mp_kill_on_retire = mp_kill_civ_on_retire;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,2);
        mp_show_human_starts = (short)uVar1;
        prefs_mp_show_human_starts = mp_show_human_starts;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,3);
        mp_chat_from_start = (short)uVar1;
        prefs_mp_chat_from_start = mp_chat_from_start;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,4);
        mp_double_production = (short)uVar1;
        prefs_mp_double_production = mp_double_production;
        uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,5);
        mp_double_moves = (short)uVar1;
        prefs_mp_double_moves = mp_double_moves;
        if (ini_simultaneous_allowed != 0) {
          uVar1 = dialog_option_is_checked((DialogOptionList *)&local_410,6);
          mp_simultaneous_setting = (short)uVar1;
          prefs_mp_simultaneous_moves = mp_simultaneous_setting;
        }
        if ((param_1 == 2) || (unit = setup_choose_game_timer(0), unit == 0)) {
          local_8 = local_8 & 0xffffff00;
          /* inlined unwind funclet FUN_00521faf */ { palette_destroy((GamePalette *)((iptr)&local_844)); }
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_00521fbb */ { dialog_dtor((Dialog *)((iptr)&local_410)); }
          uVar1 = 0;
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
#undef local_844
#undef local_410
#undef local_11c
#undef dst
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00521fe0 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(i32 *)((u8 *)&g.d_0062c488))
#define civ (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_440 (*(u8 *)(frame_ + FRAME_OFF(8)))
#define local_43c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_438 (*(i8 (*)[260])(frame_ + FRAME_OFF(16)))
#define local_334 (*(int *)(frame_ + FRAME_OFF(276)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(280)))
#define local_32c (*(Dialog *)(frame_ + FRAME_OFF(284)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(1040)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(1044)))
#define auStack_30 (*(uptr (*)[8])(frame_ + FRAME_OFF(1048)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1088)))
i32 __cdecl scenario_pick_human_civs(int param_1)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_32c,0x4000);
  local_8 = 0;
  game.human_players = '\0';
  turn_resume_civ = 0;
  local_330 = 0;
  do {
    if (param_1 <= local_330) {
      saved_turn_civ = turn_resume_civ;
      human_civ = (iptr)turn_resume_civ;
      game.turn_civ = turn_resume_civ;
      saved_resume_new_game = 1;
      turn_resume_new_game = 1;
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00522617 */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
      uVar4 = 0;
LAB_0052262d:
      return uVar4;
    }
    while( true ) {
      while( true ) {
        do {
          dlg_reset(&local_32c,1);
          dialog_prepend_title_label((iptr)&local_32c,local_330 + 0x25e);
          local_334 = 0;
          for (civ = 1; (int)civ < 8; civ++) {
            if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
              text_clear();
              iVar1 = civ_name_plural(civ);
              text_append(iVar1);
              text_append_space();
              text_append_lparen();
              iVar1 = civ_leader_name(civ);
              text_append(iVar1);
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
              local_38 = dialog_add_option
                                   ((DialogOptionList *)&local_32c,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
              auStack_30[*(int *)(local_38 + 4)] = civ;
              if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
                if (local_334 == 0) {
                  local_334 = 1;
                  dialog_set_default_choice
                            ((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4));
                }
              }
              else {
                dialog_set_option_disabled
                          ((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4),1);
              }
            }
          }
          iVar2 = dlg_show_modal(&local_32c,0);
          if (iVar2 < 0) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_00522617 */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
            uVar4 = 1;
            goto LAB_0052262d;
          }
          human_civ = auStack_30[iVar2];
          (*(i8 *)((char *)&civ + 0)) = (byte)human_civ;
          if (local_330 == 0) {
            turn_resume_civ = (byte)civ;
          }
          game.human_players = game.human_players | (byte)(1 << ((byte)civ & 0x1f));
          game.player_civ = (byte)civ;
          game.turn_civ = (byte)civ;
          game.game_options = game.game_options & 0xfffffeff;
          iVar3 = dialog_load_text_section
                            (&local_32c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6322a8, ((u8 *)&g.d_006322a8)),0x17,(iptr)&civ_names[((char)(byte)civ)].leader_name,0,0,0,1);
        } while (iVar3 != 0);
        dialog_prepend_title_label((iptr)&local_32c,local_330 + 0x25e);
        iVar3 = dialog_run_modal(&local_32c,(iptr)local_438,0);
        if (iVar3 == 0) break;
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
      }
      FUN_005f22d0((iptr)&civ_names[game.player_civ].leader_name,local_438);
      dlg_load_game_section(&local_32c,ADDR(0x6322b0, ((u8 *)&g.d_006322b0)),1);
      dialog_prepend_title_label((iptr)&local_32c,local_330 + 0x25e);
      dialog_set_default_choice
                ((DialogOptionList *)&local_32c,(uint)leaders[civs[game.player_civ].tribe].female);
      dialog_set_position
                ((C_0040bc40_28 *)&local_32c,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar3 = dlg_show_modal(&local_32c,0);
      snd_play_effect(0x6a,0,0,0);
      if (-1 < iVar3) break;
      game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
    }
    local_440 = (u8)iVar3;
    leaders[civs[game.player_civ].tribe].female = local_440;
    civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
    if (iVar3 != 0) {
      civs[human_civ].flags = civs[human_civ].flags | 0x200;
    }
    for (local_34 = 0; local_34 < 7; local_34++) {
      for (local_43c = 0; local_43c < 2; local_43c++) {
        leaders[civs[game.player_civ].tribe].titles[local_34][local_43c] =
             (short)(&government_titles[local_34].male)[local_43c];
      }
    }
    local_330++;
  } while( true );
}
#undef human_civ
#undef saved_resume_new_game
#undef saved_turn_civ
#undef screen_height
#undef turn_resume_civ
#undef turn_resume_new_game
#undef civ
#undef local_440
#undef local_43c
#undef local_438
#undef local_334
#undef local_330
#undef local_32c
#undef local_38
#undef local_34
#undef auStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0052263c auto */
void __cdecl setup_show_side_picture(int param_1,int param_2)

{
  if (param_2 != 0) {
    setup_side_picture_id = 5;
  }
  if (param_1 == -1) {
    if (setup_side_picture_id == 5) {
      setup_side_picture_id = 7;
    }
    else if (setup_side_picture_id == 6) {
      setup_side_picture_id = 5;
    }
    else if (setup_side_picture_id == 7) {
      setup_side_picture_id = 6;
    }
    setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,setup_side_picture_id);
  }
  else {
    setup_picwnd_show((C_004083b0_430 *)&setup_picwnd,2,6,param_1);
  }
  return;
}

/* 005226fa auto */
int __cdecl setup_next_dialog_x(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    setup_dialog_pos_state = 1;
  }
  switch(setup_dialog_pos_state) {
  case 1:
    setup_dialog_pos_state = 3;
    iVar1 = -999;
    break;
  case 2:
    setup_dialog_pos_state = 1;
    iVar1 = ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1;
    break;
  case 3:
    setup_dialog_pos_state = 4;
    iVar1 = -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1);
    break;
  case 4:
    setup_dialog_pos_state = 2;
    iVar1 = -999;
    break;
  default:
    iVar1 = -999;
  }
  return iVar1;
}

/* 005227e3 auto */
#define net_max_players (*(int *)((u8 *)&g.d_006c3164))
#define prefs_hotseat_players_choice (*(short *)((u8 *)&g.d_006665d8))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define local_30c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
int __cdecl setup_choose_hotseat_players(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (game.multiplayer < 3) {
    setup_show_side_picture(0xffffffff,0);
    dlg_load_game_section(&local_308,ADDR(0x6322b8, ((u8 *)&g.d_006322b8)),1);
    if (4 < net_max_players) {
      text_clear();
      text_append_label(0x365);
      dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),3,0);
    }
    if (5 < net_max_players) {
      text_clear();
      text_append_label(0x366);
      dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),4,0);
    }
    if (6 < net_max_players) {
      text_clear();
      text_append_label(0x367);
      dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),5,0);
    }
    dialog_set_default_choice((DialogOptionList *)&local_308,(int)prefs_hotseat_players_choice);
    dialog_set_position
              ((C_0040bc40_28 *)&local_308,
               -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
               -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
    switch(game.num_enemies) {
    case 1:
      dialog_set_option_disabled((DialogOptionList *)&local_308,1,1);
    case 2:
      dialog_set_option_disabled((DialogOptionList *)&local_308,2,1);
    case 3:
      if (4 < net_max_players) {
        dialog_set_option_disabled((DialogOptionList *)&local_308,3,1);
      }
    case 4:
      if (5 < net_max_players) {
        dialog_set_option_disabled((DialogOptionList *)&local_308,4,1);
      }
    case 5:
      if (6 < net_max_players) {
        dialog_set_option_disabled((DialogOptionList *)&local_308,5,1);
      }
    }
    if (prefs_hotseat_players_choice + 1 < (int)(uint)game.num_enemies) {
      dialog_set_default_choice((DialogOptionList *)&local_308,(int)prefs_hotseat_players_choice);
    }
    local_14 = dlg_show_modal(&local_308,0);
    if (local_14 < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00522b06 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      iVar1 = 0;
      goto LAB_00522b1c;
    }
    prefs_hotseat_players_choice = (short)local_14;
    local_14 += 2;
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  }
  else {
    local_14 = 0;
    for (local_30c = 1; local_30c < 8; local_30c++) {
      if ((1 << ((byte)local_30c & 0x1f) & (uint)game.human_players) != 0) {
        local_14++;
      }
    }
  }
  iVar1 = local_14;
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00522b06 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
LAB_00522b1c:
  return iVar1;
}
#undef net_max_players
#undef prefs_hotseat_players_choice
#undef screen_height
#undef local_30c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00522b2b auto */
#define hotseat_human_players (*(u8 *)((u8 *)&g.d_006c31a9))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_max_players (*(int *)((u8 *)&g.d_006c3164))
#define local_324 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_320 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_318 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(772)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(776)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(780)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(784)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(788)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(792)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(800)))
void __cdecl game_join_dialog(void)

{
  int iVar2;
  iptr iVar3;
  iptr iVar1;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_318,0x4000);
  iVar1 = human_civ;
  local_8 = 0;
  local_20 = (int)game.player_civ;
  local_24 = (uint)game.human_players;
  game.human_players = hotseat_human_players;
  mp_turn_timer_stop(1);
  city_window_close();
  wnd_hide((WndBase *)&status_window_wnd);
  wnd_hide((WndBase *)&minimap_wnd);
  for (local_14 = 0; local_14 < 8; local_14++) {
    if (*(short *)(&map_view_open_flags + local_14 * 0x3f0) != 0) {
      wnd_hide((WndBase *)(&map_view_wnds + local_14 * 0x3f0));
    }
  }
  wnd_flush_paint();
  local_18 = 0;
  local_1c = 0;
  local_324 = 0;
  for (local_320 = 1; local_320 < 8; local_320++) {
    if ((1 << ((byte)local_320 & 0x1f) & (uint)game.civs_alive) != 0) {
      local_18++;
      if ((1 << ((byte)local_320 & 0x1f) & (uint)game.human_players) == 0) {
        local_1c++;
      }
      else {
        local_324++;
      }
    }
  }
  if (net_max_players == local_324) {
    text_set_number_arg(0,net_max_players);
    popup_game(ADDR(0x6322c4, ((u8 *)&g.d_006322c4)));
  }
  else if (local_1c == 0) {
    popup_game(ADDR(0x6322d0, ((u8 *)&g.d_006322d0)));
  }
  else {
    iVar2 = setup_join_pick_civ(local_324 - 1);
    if (iVar2 == 0) {
      iVar3 = civ_name_plural(human_civ);
      text_set_string_arg_b(0,iVar3);
      popup_game(ADDR(0x6322dc, ((u8 *)&g.d_006322dc)));
    }
  }
  game.player_civ = (i8)local_20;
  hotseat_human_players = game.human_players;
  game.human_players = (u8)local_24;
  human_civ = iVar1;
  window_show((C_004083b0_4 *)&status_window);
  window_show((C_004083b0_4 *)&minimap_window);
  for (local_14 = 0; local_14 < 8; local_14++) {
    if (*(short *)(&map_view_open_flags + local_14 * 0x3f0) != 0) {
      window_show((C_004083b0_4 *)(&map_views + local_14 * 0x3f0));
    }
  }
  mp_turn_timer_resume(1);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00522dd6 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
  return;
}
#undef hotseat_human_players
#undef human_civ
#undef net_max_players
#undef local_324
#undef local_320
#undef local_318
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00522f8f auto */
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define setup_select_opponents (*(int *)((u8 *)&g.d_00631ee4))
#define local_314 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_310 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(764)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(768)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl setup_choose_opponents(int param_1)

{
  byte bVar1;
  int iVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_310,0x4000);
  local_8 = 0;
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
      for (local_18 = 0; local_18 < 7; local_18++) {
        if (leaders[leader].titles[local_18][0] < 1) {
          *(ushort *)&leaders[leader].titles[local_18][0] =
               ~*(ushort *)&leaders[leader].titles[local_18][0] + 1;
        }
        if (leaders[leader].titles[local_18][1] < 1) {
          *(ushort *)&leaders[leader].titles[local_18][1] =
               ~*(ushort *)&leaders[leader].titles[local_18][1] + 1;
        }
      }
    }
  }
  for (local_18 = 0; local_18 < (int)((game.num_enemies + 1) - param_1); local_18++) {
    iVar2 = _rand();
    bVar1 = (byte)(iVar2 >> 0x1f);
    (*(i8 *)((char *)&local_314 + 0)) = (((byte)iVar2 ^ bVar1) - bVar1 & 7 ^ bVar1) - bVar1;
    if ((1 << ((byte)local_314 & 0x1f) & (uint)game.civs_alive) == 0) {
      game.civs_alive = game.civs_alive | (byte)(1 << ((byte)local_314 & 0x1f));
    }
    else {
      local_18--;
    }
  }
  if (setup_select_opponents != 0) {
    local_14 = 0;
    for (local_314 = 1; local_314 < 8; local_314++) {
      if (((1 << ((byte)local_314 & 0x1f) & (uint)game.human_players) == 0) &&
         ((1 << ((byte)local_314 & 0x1f) & (uint)game.civs_alive) != 0)) {
        local_14++;
        text_set_number_arg(0,local_14);
        setup_show_side_picture(9,0);
        dlg_load_game_section(&local_310,ADDR(0x6322e8, ((u8 *)&g.d_006322e8)),1);
        *(i32 *)(local_310.field_228 + 4) = 0x15;
        for (leader = 0; leader < 0x15; leader++) {
          if (leaders[leader].color == local_314) {
            text_clear();
            text_append_string_id((int)leaders[leader].plural);
            text_append_space();
            text_append_lparen();
            text_append_string_id((int)leaders[leader].leader_name);
            text_append_rparen();
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),leader,0);
          }
        }
        iVar2 = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
        uVar3 = setup_next_dialog_x(0);
        dialog_set_position((C_0040bc40_28 *)&local_310,uVar3,iVar2);
        leader = dlg_show_modal(&local_310,0);
        snd_play_effect(0x6a,0,0,0);
        setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
        if (leader < 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_005233d8 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
          goto LAB_005233ee;
        }
        if (leader < 0x15) {
          (&setup_chosen_leaders)[local_314] = (byte)leader;
        }
      }
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005233d8 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
LAB_005233ee:
  return;
}
#undef screen_height
#undef setup_select_opponents
#undef local_314
#undef local_310
#undef leader
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00523f02 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_448 (*(u8 *)(frame_ + FRAME_OFF(8)))
#define local_444 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_440 (*(i8 (*)[260])(frame_ + FRAME_OFF(16)))
#define local_33c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_338 (*(int *)(frame_ + FRAME_OFF(280)))
#define local_334 (*(int *)(frame_ + FRAME_OFF(284)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_32c (*(Dialog *)(frame_ + FRAME_OFF(292)))
#define local_38 (*(byte * *)(frame_ + FRAME_OFF(1048)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(1052)))
#define aiStack_30 (*(iptr (*)[8])(frame_ + FRAME_OFF(1056)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1088)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1092)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1096)))
i32 __cdecl setup_join_pick_civ(int param_1)

{
  iptr iVar1;
  iptr iVar3;
  int iVar2;
  iptr iVar4;
  int civ;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  i32 uVar9;
  i8 frame_[FRAME_OFF(1104)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_32c,0x4000);
  local_8 = 0;
  local_330 = 0;
  do {
    dlg_reset(&local_32c,1);
    dialog_prepend_title_label((iptr)&local_32c,param_1 + 0x25f);
    local_33c = 0;
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        iVar1 = civ_name_plural(civ2);
        text_append(iVar1);
        text_append_space();
        text_append_lparen();
        iVar1 = civ_leader_name(civ2);
        text_append(iVar1);
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
        civ = local_33c;
        local_33c++;
        local_38 = (byte *)dialog_add_option
                                     ((DialogOptionList *)&local_32c,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
        aiStack_30[*(int *)(local_38 + 4)] = civ2;
      }
    }
    local_334 = local_33c;
    local_338 = 0;
    for (local_33c = 0; local_33c < local_334; local_33c++) {
      local_38 = (byte *)dialog_find_option((DialogOptionList *)&local_32c,local_33c);
      if (local_38 != (byte *)0x0) {
        (*(i8 *)((char *)&civ2 + 0)) = (byte)aiStack_30[*(int *)(local_38 + 4)];
        if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
          local_338++;
          dialog_set_option_disabled((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4),0)
          ;
          if ((RadioGroupDisableView *)local_32c.field_268 != (RadioGroupDisableView *)0x0) {
            radiogrp_enable_item
                      ((RadioGroupEnableView *)local_32c.field_268,*(iptr *)(local_38 + 4));
          }
        }
        else {
          dialog_set_option_disabled((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4),1)
          ;
          if ((RadioGroupDisableView *)local_32c.field_268 != (RadioGroupDisableView *)0x0) {
            radiogrp_disable_item
                      ((RadioGroupDisableView *)local_32c.field_268,*(iptr *)(local_38 + 4));
          }
        }
      }
    }
    local_330 = 0;
    for (local_33c = 0; local_33c < local_334; local_33c++) {
      local_38 = (byte *)dialog_find_option((DialogOptionList *)&local_32c,local_330);
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
    iVar3 = dlg_show_modal(&local_32c,0);
    if (iVar3 < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_005246bf */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
      uVar6 = 1;
LAB_005246d5:
      return uVar6;
    }
    civ = aiStack_30[iVar3];
    (*(i8 *)((char *)&civ2 + 0)) = (byte)civ;
    game.human_players = game.human_players | (byte)(1 << ((byte)civ2 & 0x1f));
    uVar9 = 1;
    uVar8 = 0;
    uVar7 = 0;
    uVar6 = 0;
    human_civ = civ;
    iVar1 = civ_leader_name(civ);
    iVar2 = dialog_load_text_section
                      (&local_32c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x632338, ((u8 *)&g.d_00632338)),0x17,iVar1,uVar6,uVar7,uVar8,uVar9);
    if (iVar2 == 0) {
      dialog_prepend_title_label((iptr)&local_32c,param_1 + 0x25f);
      iVar2 = dialog_run_modal(&local_32c,(iptr)local_440,0);
      if (iVar2 == 0) {
        FUN_005f22d0((iptr)&civ_names[civ].leader_name,local_440);
        if (0 < leaders[civs[civ].tribe].leader_name) {
          leaders[civs[civ].tribe].leader_name = -leaders[civs[civ].tribe].leader_name;
        }
        iVar4 = civ_check_password(human_civ);
        if (iVar4 == 0) {
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ2 & 0x1f));
        }
        else {
          dlg_load_game_section(&local_32c,ADDR(0x632340, ((u8 *)&g.d_00632340)),1);
          dialog_prepend_title_label((iptr)&local_32c,param_1 + 0x25f);
          dialog_set_default_choice
                    ((DialogOptionList *)&local_32c,(uint)leaders[civs[game.player_civ].tribe].female)
          ;
          dialog_set_position
                    ((C_0040bc40_28 *)&local_32c,0xfffffc19,
                     -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) +
                      1));
          civ = dlg_show_modal(&local_32c,0);
          snd_play_effect(0x6a,0,0,0);
          if (-1 < civ) {
            local_448 = (u8)civ;
            leaders[civs[game.player_civ].tribe].female = local_448;
            civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
            if (civ != 0) {
              civs[human_civ].flags = civs[human_civ].flags | 0x200;
            }
            for (local_34 = 0; local_34 < 7; local_34++) {
              for (local_444 = 0; local_444 < 2; local_444++) {
                leaders[civs[game.player_civ].tribe].titles[local_34][local_444] = (short)(&government_titles[local_34].male)[local_444];
              }
            }
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_005246bf */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
            uVar6 = 0;
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
#undef local_448
#undef local_444
#undef local_440
#undef local_33c
#undef local_338
#undef local_334
#undef local_330
#undef local_32c
#undef local_38
#undef local_34
#undef aiStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00548df0 auto */
void __cdecl events_editor_focus_redraw(void)

{
  HWND hWnd;
  
  hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0xad0));
  SetFocus(hWnd);
  events_editor_draw((C_004083b0_430 *)active_editor_wnd);
  return;
}

/* 00548e23 auto */
#define local_5c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_54 (*(char (*)[80])(frame_ + FRAME_OFF(12)))
/* WARNING: Type propagation algorithm not settling */

void __cdecl events_write_actions(iptr param_1,iptr param_2)

{
  int iVar1;
  uint uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = _fputs(s__THEN_0063257c,(FILE *)param_1);
  if (((iVar1 == -1) || (local_5c = 1, param_2 == 0)) || (*(int *)(param_2 + 4) == 0)) {
    return;
  }
  do {
    uVar2 = *(uint *)(param_2 + 4) & local_5c;
    if (uVar2 < 9) {
      if (uVar2 == 8) {
        iVar1 = _fputs(s_CHANGEMONEY_00632680,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_receiver__s_00632690,*(i32 *)(param_2 + 0x174));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_amount__d_006326a0,*(i32 *)(param_2 + 0x17c));
        iVar1 = _fputs(local_54,(FILE *)param_1);
      }
      else if (uVar2 == 1) {
        iVar1 = _fputs(s_TEXT_00632584,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        for (local_58 = 0; (local_58 < 0x14 && (*(int *)(param_2 + 0x38 + local_58 * 4) != 0));
            local_58 = local_58 + 1) {
          iVar1 = _fputs(*(char **)(param_2 + 0x38 + local_58 * 4),(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
          iVar1 = _fputs(&events_text_line_newline_str,(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
        }
        iVar1 = _fputs(s_ENDTEXT_00632590,(FILE *)param_1);
      }
      else if (uVar2 == 2) {
        iVar1 = _fputs(s_MOVEUNIT_0063259c,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_unit__s_006325a8,*(i32 *)(param_2 + 0x90));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_owner__s_006325b4,*(i32 *)(param_2 + 0x88));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        iVar1 = _fputs(s_maprect_006325c0,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        for (local_58 = 0; local_58 < 4; local_58++) {
          _sprintf(local_54,s__d__d_006325cc,*(i32 *)(param_2 + 0x9c + local_58 * 8),
                   *(i32 *)(param_2 + 0xa0 + local_58 * 8));
          if (local_58 < 3) {
            FUN_005f22e0(local_54,&events_moveunit_rect_sep_str);
          }
          iVar1 = _fputs(local_54,(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
        }
        iVar1 = _fputs(s_moveto_006325d8,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s__d__d_006325e4,*(i32 *)(param_2 + 0xbc),
                 *(i32 *)(param_2 + 0xc0));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        if (*(int *)(param_2 + 0x98) == -2) {
          _sprintf(local_54,s_numbertomove_ALL_006325ec);
        }
        else {
          _sprintf(local_54,s_numbertomove__d_00632600,*(i32 *)(param_2 + 0x98));
        }
        iVar1 = _fputs(local_54,(FILE *)param_1);
      }
      else {
        if (uVar2 != 4) goto LAB_005499f7;
        iVar1 = _fputs(s_CREATEUNIT_00632614,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_unit__s_00632620,*(i32 *)(param_2 + 0xdc));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_owner__s_0063262c,*(i32 *)(param_2 + 0xd4));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_veteran__s_00632640,
                 &events_veteran_yes_no_strs + ((*(int *)(param_2 + 0x138) != 0) - 1 & 4));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_homecity__s_0063264c,*(i32 *)(param_2 + 0x13c));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        iVar1 = _fputs(s_locations_0063265c,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        for (local_58 = 0; local_58 < *(int *)(param_2 + 0x134); local_58++) {
          _sprintf(local_54,s__d__d_00632668,*(i32 *)(param_2 + 0xe4 + local_58 * 8),
                   *(i32 *)(param_2 + 0xe8 + local_58 * 8));
          iVar1 = _fputs(local_54,(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
        }
        iVar1 = _fputs(s_endlocations_00632670,(FILE *)param_1);
      }
joined_r0x0054934c:
      if (iVar1 == -1) {
        return;
      }
    }
    else {
      if (0x20 < uVar2) {
        if (uVar2 < 0x81) {
          if (uVar2 == 0x80) {
            iVar1 = _fputs(s_PLAYCDTRACK_00632700,(FILE *)param_1);
            if (iVar1 == -1) {
              return;
            }
            _sprintf(local_54,&events_cd_track_fmt,*(i32 *)(param_2 + 0x188));
            iVar1 = _fputs(local_54,(FILE *)param_1);
          }
          else {
            if (uVar2 != 0x40) goto LAB_005499f7;
            iVar1 = _fputs(s_JUSTONCE_006326e4,(FILE *)param_1);
          }
        }
        else if (uVar2 < 0x201) {
          if (uVar2 == 0x200) {
            iVar1 = _fputs(s_CHANGETERRAIN_00632728,(FILE *)param_1);
            if (iVar1 == -1) {
              return;
            }
            _sprintf(local_54,s_terraintype__d_00632738,*(i32 *)(param_2 + 0x18c));
            iVar1 = _fputs(local_54,(FILE *)param_1);
            if (iVar1 == -1) {
              return;
            }
            iVar1 = _fputs(s_maprect_00632748,(FILE *)param_1);
            if (iVar1 == -1) {
              return;
            }
            for (local_58 = 0; local_58 < 4; local_58++) {
              _sprintf(local_54,s__d__d_00632754,*(i32 *)(param_2 + 400 + local_58 * 8),
                       *(i32 *)(param_2 + 0x194 + local_58 * 8));
              if (local_58 < 3) {
                FUN_005f22e0(local_54,&events_terrain_rect_sep_str);
              }
              iVar1 = _fputs(local_54,(FILE *)param_1);
              if (iVar1 == -1) {
                return;
              }
            }
            iVar1 = _fputs(&events_terrain_rect_end_str,(FILE *)param_1);
          }
          else {
            if (uVar2 != 0x100) goto LAB_005499f7;
            iVar1 = _fputs(s_DONTPLAYWONDERS_00632714,(FILE *)param_1);
          }
        }
        else if (uVar2 == 0x400) {
          iVar1 = _fputs(s_DESTROYACIVILIZATION_00632764,(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
          if (*(int *)(param_2 + 0x1b0) < 0) {
            if ((*(byte *)(param_2 + 1) & 1) == 0) {
              if (*(int *)(param_2 + 0x1b0) == -3) {
                _sprintf(local_54,s_whom_TRIGGERATTACKER_006327a0);
              }
              else {
                _sprintf(local_54,s_whom_TRIGGERDEFENDER_006327b8);
              }
            }
            else {
              _sprintf(local_54,s_whom_TRIGGERRECEIVER_00632788);
            }
          }
          else {
            uVar3 = civ_name_plural(*(iptr *)(param_2 + 0x1b0));
            _sprintf(local_54,s_whom__s_0063277c,uVar3);
          }
          iVar1 = _fputs(local_54,(FILE *)param_1);
        }
        else if (uVar2 == 0x800) {
          iVar1 = _fputs(s_GIVETECHNOLOGY_006327d0,(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
          if (*(int *)(param_2 + 0x1b8) < 0) {
            if ((*(byte *)(param_2 + 1) & 1) == 0) {
              if (*(int *)(param_2 + 0x1b8) == -3) {
                _sprintf(local_54,s_receiver_TRIGGERATTACKER_0063280c);
              }
              else {
                _sprintf(local_54,s_receiver_TRIGGERDEFENDER_00632828);
              }
            }
            else {
              _sprintf(local_54,s_receiver_TRIGGERRECEIVER_006327f0);
            }
          }
          else {
            uVar3 = civ_name_plural(*(iptr *)(param_2 + 0x1b8));
            _sprintf(local_54,s_receiver__s_006327e0,uVar3);
          }
          iVar1 = _fputs(local_54,(FILE *)param_1);
          if (iVar1 == -1) {
            return;
          }
          _sprintf(local_54,s_technology__d_00632844,*(i32 *)(param_2 + 0x1b4));
          iVar1 = _fputs(local_54,(FILE *)param_1);
        }
        else {
          if (uVar2 != 0x2000) goto LAB_005499f7;
          iVar1 = _fputs(s_HASTRIGGERED_006326f0,(FILE *)param_1);
        }
        goto joined_r0x0054934c;
      }
      if (uVar2 == 0x20) {
        iVar1 = _fputs(s_MAKEAGGRESSION_006326c0,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_who__s_006326d0,*(i32 *)(param_2 + 0xcc));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,s_whom__s_006326d8,*(i32 *)(param_2 + 0xc4));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        goto joined_r0x0054934c;
      }
      if (uVar2 == 0x10) {
        iVar1 = _fputs(s_PLAYWAVEFILE_006326ac,(FILE *)param_1);
        if (iVar1 == -1) {
          return;
        }
        _sprintf(local_54,&events_wave_file_fmt,*(i32 *)(param_2 + 0x184));
        iVar1 = _fputs(local_54,(FILE *)param_1);
        goto joined_r0x0054934c;
      }
    }
LAB_005499f7:
    local_5c = local_5c << 1;
    if (local_5c == 0x8000) {
      return;
    }
  } while( true );
}
#undef local_5c
#undef local_58
#undef local_54

/* 00549aee auto */
#define local_108 (*(uint * *)(frame_ + FRAME_OFF(0)))
#define local_104 (*(char (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl events_write_list(iptr param_1)

{
  uint uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_108 = (uint *)events_list_head;
  do {
    if (local_108 == (uint *)0x0) {
      _fputs(&events_list_end_str,(FILE *)param_1);
      return;
    }
    iVar2 = _fputs(s__IF_00632854,(FILE *)param_1);
    if (iVar2 == -1) {
      return;
    }
    uVar1 = *local_108;
    if (uVar1 < 9) {
      if (uVar1 == 8) {
        iVar2 = _fputs(s_TURNINTERVAL_006328e0,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_interval__d_006328f0,local_108[0xb]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
      }
      else if (uVar1 == 1) {
        iVar2 = _fputs(s_UNITKILLED_0063285c,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_unit__s_00632868,local_108[2]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_attacker__s_00632874,local_108[5]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_defender__s_00632884,local_108[8]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
      }
      else if (uVar1 == 2) {
        iVar2 = _fputs(s_CITYTAKEN_00632894,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_city__s_006328a0,local_108[4]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_attacker__s_006328ac,local_108[5]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_defender__s_006328bc,local_108[8]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
      }
      else if (uVar1 == 4) {
        iVar2 = _fputs(s_TURN_006328cc,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_turn__d_006328d4,local_108[0xb]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
      }
    }
    else {
      switch(uVar1) {
      case 0x10:
        iVar2 = _fputs(s_NEGOTIATION_00632900,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_talker__s_00632910,local_108[5]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_talkertype__0063291c);
        if (local_108[7] == 1) {
          FUN_005f22e0(local_104,s_Human_00632928);
        }
        if (local_108[7] == 2) {
          FUN_005f22e0(local_104,s_Computer_00632930);
        }
        if (local_108[7] == 4) {
          FUN_005f22e0(local_104,s_HumanOrComputer_0063293c);
        }
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_listener__s_00632950,local_108[8]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_listenertype__00632960);
        if (local_108[10] == 1) {
          FUN_005f22e0(local_104,s_Human_00632970);
        }
        if (local_108[10] == 2) {
          FUN_005f22e0(local_104,s_Computer_00632978);
        }
        if (local_108[10] == 4) {
          FUN_005f22e0(local_104,s_HumanOrComputer_00632984);
        }
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
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
        iVar2 = _fputs(s_SCENARIOLOADED_00632998,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
        break;
      case 0x40:
        iVar2 = _fputs(s_RANDOMTURN_006329a8,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_denominator__d_006329b4,local_108[0xc]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
        break;
      case 0x80:
        iVar2 = _fputs(s_NOSCHISM_006329c4,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_defender__s_006329d0,local_108[8]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
        break;
      case 0x100:
        iVar2 = _fputs(s_RECEIVEDTECHNOLOGY_006329e0,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_technology__d_006329f4,local_108[0xd]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        _sprintf(local_104,s_receiver__s_00632a04,local_108[8]);
        iVar2 = _fputs(local_104,(FILE *)param_1);
        if (iVar2 == -1) {
          return;
        }
        events_write_actions(param_1,(iptr)local_108);
      }
    }
    iVar2 = _fputs(s__ENDIF_00632a14,(FILE *)param_1);
    if (iVar2 == -1) {
      return;
    }
    local_108 = (uint *)local_108[0x6f];
  } while( true );
}
#undef local_108
#undef local_104

/* 0054a4c4 auto */
#define local_228 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_224 (*(FILE * *)(frame_ + FRAME_OFF(4)))
#define local_220 (*(FILE * *)(frame_ + FRAME_OFF(8)))
#define local_21c (*(char (*)[260])(frame_ + FRAME_OFF(12)))
#define local_118 (*(i8 (*)[16])(frame_ + FRAME_OFF(272)))
#define s (*(char (*)[260])(frame_ + FRAME_OFF(288)))
i32 __cdecl events_write_file(void)

{
  int iVar1;
  char *pcVar2;
  i8 frame_[FRAME_OFF(552)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_224 = (FILE *)0x0;
  local_220 = (FILE *)0x0;
  FUN_005f22d0(local_118,s_EVENTS__00632a20);
  FUN_005f22e0(local_118,&lang_file_ext);
  local_228 = 0;
  __getcwd(local_21c,0x104);
  __chdir(&scenario_dir_path);
  iVar1 = file_exists(ADDR(0x632a28, ((u8 *)&g.d_00632a28)));
  if (((iVar1 == 0) || (iVar1 = FUN_005f66b0(s_EVENTS_BAK_00632a34), iVar1 == 0)) &&
     ((iVar1 = file_exists((iptr)local_118), iVar1 == 0 ||
      (iVar1 = FUN_005f6650(local_118,s_EVENTS_BAK_00632a40), iVar1 == 0)))) {
    local_224 = (FILE *)file_open_path(ADDR(0x632a50, ((u8 *)&g.d_00632a50)),ADDR(0x632a4c, ((u8 *)&g.d_00632a4c)));
    local_220 = (FILE *)file_open_path((iptr)local_118,ADDR(0x632a5c, ((u8 *)&g.d_00632a5c)));
    if (local_220 != (FILE *)0x0) {
      if (local_224 == (FILE *)0x0) {
        iVar1 = _fputs(s__BEGINEVENTS_00632a70,local_220);
        if (iVar1 == -1) goto LAB_0054a7eb;
      }
      else {
        do {
          pcVar2 = _fgets(s,0x100,local_224);
          if ((pcVar2 == (char *)0x0) || (iVar1 = _fputs(s,local_220), iVar1 == -1))
          goto LAB_0054a7eb;
          str_strip_newline((iptr)s);
          str_trim((iptr)s);
          iVar1 = __strcmpi(s,s__BEGINEVENTS_00632a60);
        } while (iVar1 != 0);
      }
      events_write_list((iptr)local_220);
      if (local_224 == (FILE *)0x0) {
        iVar1 = _fputs(s__ENDEVENTS_00632a98,local_220);
        if (iVar1 != -1) {
LAB_0054a7e1:
          local_228 = 1;
        }
      }
      else {
        do {
          pcVar2 = _fgets(s,0x100,local_224);
          if (pcVar2 == (char *)0x0) goto LAB_0054a7eb;
          str_strip_newline((iptr)s);
          str_trim((iptr)s);
          iVar1 = __strcmpi(s,s__ENDEVENTS_00632a80);
        } while (iVar1 != 0);
        iVar1 = _fputs(s__ENDEVENTS_00632a8c,local_220);
        while (iVar1 != -1) {
          pcVar2 = _fgets(s,0x100,local_224);
          if (pcVar2 == (char *)0x0) goto LAB_0054a7e1;
          iVar1 = _fputs(s,local_220);
        }
      }
    }
  }
LAB_0054a7eb:
  if (local_224 != (FILE *)0x0) {
    _fclose(local_224);
  }
  if (local_220 != (FILE *)0x0) {
    _fclose(local_220);
  }
  __chdir(local_21c);
  return local_228;
}
#undef local_228
#undef local_224
#undef local_220
#undef local_21c
#undef local_118
#undef s

/* 0054a912 auto */
#define local_318 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
i32 __cdecl events_editor_pick_item(int param_1,iptr param_2,i32 param_3)

{
  iptr iVar1;
  iptr iVar3;
  i32 uVar4;
  iptr iVar2;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  dlg_reset(&local_308,0x1001);
  dialog_set_title((DialogWindowView *)&local_308,param_2);
  dialog_set_width((DialogWindowView *)&local_308,0xdc);
  dialog_set_listbox((DialogTextView *)&local_308,8,0xdc,0);
  switch(param_3) {
  case 0:
    if (param_1 == 0) {
      param_1 = 1;
    }
    for (civ = 1; civ < 8; civ++) {
      uVar4 = 0;
      iVar3 = civ;
      iVar1 = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 1:
    for (civ = 0; civ < 0x3e; civ++) {
      uVar4 = 0;
      iVar3 = civ;
      iVar1 = label_string(unit_types[civ].name);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 2:
    for (advance = 0; advance < 100; advance++) {
      uVar4 = 0;
      iVar3 = advance;
      iVar1 = label_string(advances[advance].name);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 3:
    dialog_add_option((DialogOptionList *)&local_308,ADDR(0x632adc, ((u8 *)&g.d_00632adc)),-2,0);
    for (civ = 0; civ < 0x3e; civ++) {
      uVar4 = 0;
      iVar3 = civ;
      iVar1 = label_string(unit_types[civ].name);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 4:
    if (param_1 == 0) {
      param_1 = -2;
    }
    dialog_add_option((DialogOptionList *)&local_308,ADDR(0x632aa4, ((u8 *)&g.d_00632aa4)),-2,0);
    for (civ = 1; civ < 8; civ++) {
      uVar4 = 0;
      iVar3 = civ;
      iVar1 = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 5:
    if (param_1 == 0) {
      param_1 = -3;
    }
    dialog_add_option((DialogOptionList *)&local_308,ADDR(0x632aac, ((u8 *)&g.d_00632aac)),-3,0);
    dialog_add_option((DialogOptionList *)&local_308,ADDR(0x632abc, ((u8 *)&g.d_00632abc)),-4,0);
    for (civ = 1; civ < 8; civ++) {
      uVar4 = 0;
      iVar3 = civ;
      iVar1 = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 6:
    if (param_1 == 0) {
      param_1 = -4;
    }
    dialog_add_option((DialogOptionList *)&local_308,ADDR(0x632acc, ((u8 *)&g.d_00632acc)),-4,0);
    for (civ = 1; civ < 8; civ++) {
      uVar4 = 0;
      iVar3 = civ;
      iVar1 = civ_name_plural(civ);
      dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
    }
    break;
  case 7:
    for (terrain2 = 0; terrain2 < 0xb; terrain2++) {
      uVar4 = 0;
      iVar2 = terrain2;
      iVar3 = label_string(terrain_types[terrain2].name);
      dialog_add_option((DialogOptionList *)&local_308,iVar3,iVar2,uVar4);
    }
  }
  dialog_set_default_choice((DialogOptionList *)&local_308,param_1);
  if (active_editor_wnd == 0) {
    local_318 = 0;
  }
  else {
    local_318 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_318);
  uVar4 = dlg_show_modal(&local_308,0);
  dlg_set_parent_window(0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0054ada1 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  return uVar4;
}
#undef local_318
#undef advance
#undef civ
#undef local_308
#undef terrain2
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0054adc6 auto */
int __cdecl events_editor_pick_action_civ(int civ,i32 param_2,int param_3,iptr param_4)

{
  i32 uVar1;
  
  if (param_3 == 0x100) {
    civ = events_editor_pick_item(civ,param_2,6);
    if (civ != -1) {
      if (civ < 0) {
        *(char **)param_4 = s_TRIGGERRECEIVER_00632ae4;
      }
      else {
        uVar1 = civ_name_plural(civ);
        *(i32 *)param_4 = uVar1;
      }
    }
  }
  else {
    civ = events_editor_pick_item(civ,param_2,5);
    if (civ != -1) {
      if (civ < 0) {
        if (civ == -3) {
          *(char **)param_4 = s_TRIGGERATTACKER_00632af4;
        }
        else {
          *(char **)param_4 = s_TRIGGERDEFENDER_00632b04;
        }
      }
      else {
        uVar1 = civ_name_plural(civ);
        *(i32 *)param_4 = uVar1;
      }
    }
  }
  return civ;
}

/* 0054ae93 auto */
#define local_14 (*(byte * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl events_editor_update_buttons(i32 param_1)

{
  int iVar1;
  uint uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl_enable((Control *)(active_editor_wnd + 0x92c));
  local_8 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  if (local_8 < 0) {
    ctrl_disable((Control *)(active_editor_wnd + 0x968));
    ctrl_disable((Control *)(active_editor_wnd + 0x9a4));
    ctrl_disable((Control *)(active_editor_wnd + 0x9e0));
    ctrl_disable((Control *)(active_editor_wnd + 0xa1c));
    ctrl_disable((Control *)(active_editor_wnd + 0xa58));
  }
  else {
    ctrl_enable((Control *)(active_editor_wnd + 0x9a4));
    local_14 = (byte *)events_list_head;
    while ((local_14 != (byte *)0x0 && (local_8 != 0))) {
      local_14 = *(byte **)(local_14 + 0x1bc);
      local_8--;
    }
    if ((*local_14 & 0x20) == 0) {
      ctrl_enable((Control *)(active_editor_wnd + 0x968));
    }
    else {
      ctrl_disable((Control *)(active_editor_wnd + 0x968));
    }
    if (*(int *)local_14 == 0x20) {
      local_10 = 0;
      while ((1 << ((byte)local_10 & 0x1f) & (*(uint *)(local_14 + 4) | 0xfffffe6f)) != 0) {
        local_10++;
      }
    }
    else {
      local_10 = 0;
      while ((*(uint *)(local_14 + 4) & 1 << ((byte)local_10 & 0x1f)) != 0) {
        local_10++;
      }
    }
    if ((local_10 < 0xc) && ((*local_14 & 0x90) == 0)) {
      ctrl_enable((Control *)(active_editor_wnd + 0x9e0));
    }
    else {
      ctrl_disable((Control *)(active_editor_wnd + 0x9e0));
    }
    iVar1 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
    if (iVar1 < 0) {
      ctrl_disable((Control *)(active_editor_wnd + 0xa1c));
      ctrl_disable((Control *)(active_editor_wnd + 0xa58));
    }
    else {
      ctrl_enable((Control *)(active_editor_wnd + 0xa58));
      uVar2 = bits_nth_set(iVar1,*(i32 *)(local_14 + 4));
      if ((uVar2 & 0x3140) == 0) {
        ctrl_enable((Control *)(active_editor_wnd + 0xa1c));
      }
      else {
        ctrl_disable((Control *)(active_editor_wnd + 0xa1c));
      }
    }
  }
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 0054b0ed auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define editor_value_clamped (*(int *)((u8 *)&g.d_0062e014))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl events_editor_on_ok(void)

{
  iptr iVar1;
  iptr iVar2;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (editor_value_clamped == 0) {
    events_compact();
    iVar1 = events_write_file();
    if (iVar1 == 0) {
      _sprintf(local_24,s_Error_updating_EVENTS__s_00632b1c,&lang_file_ext);
      uType = 0x10;
      lpCaption = s_File_I_O_Error_00632b38;
      lpText = local_24;
      iVar2 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar2 + 4),lpText,lpCaption,uType);
    }
    editor_running = 0;
    wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
    menu_update_states();
  }
  else {
    if (active_editor_wnd == 0) {
      local_28 = 0;
    }
    else {
      local_28 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_28);
    popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x632b14, ((u8 *)&g.d_00632b14)));
    dlg_set_parent_window(0);
    editor_value_clamped = 0;
    events_editor_focus_redraw();
  }
  return;
}
#undef editor_running
#undef editor_value_clamped
#undef local_28
#undef local_24

/* 0054b1d5 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(8)))
void __cdecl events_editor_help_trigger(i32 param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(param_1) {
  case 0:
    local_8 = s_HELPUNITKILLED_00632b48;
    break;
  case 1:
    local_8 = s_HELPCITYTAKEN_00632b58;
    break;
  case 2:
    local_8 = s_HELPTURN_00632b68;
    break;
  case 3:
    local_8 = s_HELPTURNINTERVAL_00632b74;
    break;
  case 4:
    local_8 = s_HELPNEGOTIATION_00632b88;
    break;
  case 5:
    local_8 = s_HELPSCENARIOLOADED_00632b98;
    break;
  case 6:
    local_8 = s_HELPRANDOMTURN_00632bac;
    break;
  case 7:
    local_8 = s_HELPNOSCHISM_00632bbc;
    break;
  case 8:
    local_8 = s_HELPRECEIVEDTECHNOLOGY_00632bcc;
  }
  if (active_editor_wnd == 0) {
    local_c = 0;
  }
  else {
    local_c = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_c);
  popup_text(ADDR(0x632be4, ((u8 *)&g.d_00632be4)),(iptr)local_8);
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef local_c
#undef local_8

/* 0054b2ec auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(8)))
void __cdecl events_editor_help_action(i32 param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(param_1) {
  case 0:
    local_8 = s_HELPTEXT_00632bec;
    break;
  case 1:
    local_8 = s_HELPMOVEUNIT_00632bf8;
    break;
  case 2:
    local_8 = s_HELPCREATEUNIT_00632c08;
    break;
  case 3:
    local_8 = s_HELPCHANGEMONEY_00632c18;
    break;
  case 4:
    local_8 = s_HELPPLAYWAVEFILE_00632c28;
    break;
  case 5:
    local_8 = s_HELPMAKEAGGRESSION_00632c3c;
    break;
  case 6:
    local_8 = s_HELPJUSTONCE_00632c50;
    break;
  case 7:
    local_8 = s_HELPPLAYCDTRACK_00632c60;
    break;
  case 8:
    local_8 = s_HELPDONTPLAYWONDERS_00632c70;
    break;
  case 9:
    local_8 = s_HELPCHANGETERRAIN_00632c84;
    break;
  case 10:
    local_8 = s_HELPDESTROYACIVILIZATION_00632c98;
    break;
  case 0xb:
    local_8 = s_HELPGIVETECHNOLOGY_00632cb4;
  }
  if (active_editor_wnd == 0) {
    local_c = 0;
  }
  else {
    local_c = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_c);
  popup_text(ADDR(0x632cc8, ((u8 *)&g.d_00632cc8)),(iptr)local_8);
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef local_c
#undef local_8

/* 0054b433 auto */
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(uint * *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
void __cdecl events_editor_on_help(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
  if (iVar1 < 0) {
    local_c = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
    if (local_c < 0) {
      if (active_editor_wnd == 0) {
        local_20 = 0;
      }
      else {
        local_20 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_20);
      popup_text(ADDR(0x632cd8, ((u8 *)&g.d_00632cd8)),ADDR(0x632cd0, ((u8 *)&g.d_00632cd0)));
      dlg_set_parent_window(0);
      events_editor_focus_redraw();
    }
    else {
      local_14 = (uint *)events_list_head;
      while ((local_14 != (uint *)0x0 && (local_c != 0))) {
        local_14 = (uint *)local_14[0x6f];
        local_c--;
      }
      local_10 = *local_14;
      local_c = 0;
      for (; (local_10 & 1) == 0; local_10 = local_10 >> 1) {
        local_c++;
      }
      if (local_14 != (uint *)0x0) {
        events_editor_help_trigger(local_c);
      }
    }
  }
  else {
    local_c = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
    local_14 = (uint *)events_list_head;
    while ((local_14 != (uint *)0x0 && (local_c != 0))) {
      local_14 = *(uint **)((int)local_14 + 0x1bc);
      local_c--;
    }
    local_10 = bits_nth_set(iVar1,*(i32 *)((int)local_14 + 4));
    local_c = 0;
    for (; (local_10 & 1) == 0; local_10 = local_10 >> 1) {
      local_c++;
    }
    if (local_14 != (uint *)0x0) {
      events_editor_help_action(local_c);
    }
  }
  return;
}
#undef local_20
#undef local_14
#undef local_10
#undef local_c

/* 0054b5eb auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define events_editor_backup (*(iptr *)((u8 *)&g.d_00632578))
void __cdecl events_editor_on_cancel(void)

{
  events_reset((ScenarioEvents *)&scenario_events,50000);
  events_copy(ADDR(0x64b690, ((u8 *)&g.d_0064b690)),events_editor_backup);
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running
#undef events_editor_backup

/* 0054b635 auto */
#define local_114 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_110 (*(char * *)(frame_ + FRAME_OFF(8)))
#define local_10c (*(uint * *)(frame_ + FRAME_OFF(12)))
#define local_108 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_104 (*(char (*)[256])(frame_ + FRAME_OFF(20)))
void __cdecl events_editor_fill_triggers(void)

{
  i32 uVar1;
  uint uVar2;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_108 = 0;
  listbox_clear((ListBoxClearView *)(active_editor_wnd + 0xad0));
  for (local_10c = (uint *)events_list_head; local_10c != (uint *)0x0;
      local_10c = (uint *)local_10c[0x6f]) {
    local_108++;
    uVar2 = *local_10c;
    if (uVar2 < 9) {
      if (uVar2 == 8) {
        _sprintf(local_104,s__d__TURNINTERVAL___d__00632d68,local_108,local_10c[0xb]);
      }
      else if (uVar2 == 1) {
        if (((local_10c[2] == 0) || (local_10c[5] == 0)) || (local_10c[8] == 0)) {
          _sprintf(local_104,s__d__UNITKILLED_00632d0c,local_108);
        }
        else {
          _sprintf(local_104,s__d__UNITKILLED___s_attacker__s_d_00632ce0,local_108,local_10c[2],
                   local_10c[5],local_10c[8]);
        }
      }
      else if (uVar2 == 2) {
        if (((local_10c[4] == 0) || (local_10c[5] == 0)) || (local_10c[8] == 0)) {
          _sprintf(local_104,s__d__CITYTAKEN_00632d48,local_108);
        }
        else {
          _sprintf(local_104,s__d__CITYTAKEN___s_attacker__s_de_00632d1c,local_108,local_10c[4],
                   local_10c[5],local_10c[8]);
        }
      }
      else if (uVar2 == 4) {
        _sprintf(local_104,s__d__TURN___d__00632d58,local_108,local_10c[0xb]);
      }
    }
    else {
      switch(uVar2) {
      case 0x10:
        if ((local_10c[5] == 0) || (local_10c[8] == 0)) {
          _sprintf(local_104,s__d__NEGOTIATION_00632dfc,local_108);
        }
        else {
          if (local_10c[10] == 1) {
            local_110 = s_HUMAN_00632d80;
          }
          else if (local_10c[10] == 2) {
            local_110 = s_COMPUTER_00632d88;
          }
          else {
            local_110 = s_HUMANORCOMPUTER_00632d94;
          }
          if (local_10c[7] == 1) {
            local_114 = s_HUMAN_00632da4;
          }
          else if (local_10c[7] == 2) {
            local_114 = s_COMPUTER_00632dac;
          }
          else {
            local_114 = s_HUMANORCOMPUTER_00632db8;
          }
          _sprintf(local_104,s__d__NEGOTIATION__talker__s___s__l_00632dc8,local_108,local_10c[5],
                   local_114,local_10c[8],local_110);
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
        _sprintf(local_104,s__d__SCENARIOLOADED_00632e0c,local_108);
        break;
      case 0x40:
        if (local_10c[0xc] == 0) {
          _sprintf(local_104,s__d__RANDOMTURN_00632e40,local_108);
        }
        else {
          _sprintf(local_104,s__d__RANDOMTURN__denominator__d__00632e20,local_108,local_10c[0xc]);
        }
        break;
      case 0x80:
        if (local_10c[8] == 0) {
          _sprintf(local_104,s__d__NOSCHISM_00632e64,local_108);
        }
        else {
          _sprintf(local_104,s__d__NOSCHISM___s__00632e50,local_108,local_10c[8]);
        }
        break;
      case 0x100:
        if (local_10c[8] == 0) {
          _sprintf(local_104,s__d__RECEIVEDTECHNOLOGY_00632e98,local_108);
        }
        else {
          uVar2 = local_10c[8];
          uVar1 = label_string(advances[local_10c[0xd]].name);
          _sprintf(local_104,s__d__RECEIVEDTECHNOLOGY___s_whom__00632e74,local_108,uVar1,uVar2);
        }
      }
    }
    listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xad0),(iptr)local_104);
  }
  events_editor_update_buttons(0);
  return;
}
#undef local_114
#undef local_110
#undef local_10c
#undef local_108
#undef local_104

/* 0054bc1a auto */
#define local_11c (*(char (*)[16])(frame_ + FRAME_OFF(4)))
#define local_10c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_108 (*(uint *)(frame_ + FRAME_OFF(24)))
#define local_104 (*(char (*)[256])(frame_ + FRAME_OFF(28)))
void __cdecl events_editor_fill_actions(i32 param_1)

{
  int iVar1;
  uint uVar2;
  i32 uVar3;
  i32 uVar4;
  bool bVar5;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_108 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  local_10c = events_list_head;
  while ((local_10c != 0 &&
         (iVar1 = local_108 - 1, bVar5 = local_108 != 0, local_108 = iVar1, bVar5))) {
    local_10c = *(iptr *)(local_10c + 0x1bc);
  }
  listbox_clear((ListBoxClearView *)(active_editor_wnd + 0xb0c));
  local_108 = 1;
  if (local_10c != 0) {
    do {
      local_104[0] = '\0';
      uVar2 = *(uint *)(local_10c + 4) & local_108;
      if (uVar2 < 9) {
        if (uVar2 == 8) {
          if (*(int *)(local_10c + 0x174) == 0) {
            _sprintf(local_104,s_CHANGEMONEY_00632f50);
          }
          else {
            _sprintf(local_104,s_CHANGEMONEY__receiver__s_amount__00632f2c,
                     *(i32 *)(local_10c + 0x174),*(i32 *)(local_10c + 0x17c));
          }
        }
        else if (uVar2 == 1) {
          if (*(int *)(local_10c + 0x38) == 0) {
            _sprintf(local_104,&events_editor_text_caption);
          }
          else {
            _sprintf(local_104,s_TEXT___s__00632eb0,*(i32 *)(local_10c + 0x38));
          }
        }
        else if (uVar2 == 2) {
          if ((*(int *)(local_10c + 0x90) == 0) || (*(int *)(local_10c + 0x88) == 0)) {
            _sprintf(local_104,s_MOVEUNIT_00632edc);
          }
          else {
            _sprintf(local_104,s_MOVEUNIT___s_owner__s__00632ec4,*(i32 *)(local_10c + 0x90),
                     *(i32 *)(local_10c + 0x88));
          }
        }
        else if (uVar2 == 4) {
          if (((*(int *)(local_10c + 0xdc) == 0) || (*(int *)(local_10c + 0xd4) == 0)) ||
             (*(int *)(local_10c + 0x13c) == 0)) {
            _sprintf(local_104,s_CREATEUNIT_00632f20);
          }
          else {
            _sprintf(local_104,s_CREATEUNIT___s_owner__s_veteran__00632ef0,
                     *(i32 *)(local_10c + 0xdc),*(i32 *)(local_10c + 0xd4),
                     &events_editor_yes_no_strs + ((*(int *)(local_10c + 0x138) != 0) - 1 & 4),
                     *(i32 *)(local_10c + 0x13c));
          }
        }
      }
      else if (uVar2 < 0x21) {
        if (uVar2 == 0x20) {
          if ((*(int *)(local_10c + 0xcc) == 0) || (*(int *)(local_10c + 0xc4) == 0)) {
            _sprintf(local_104,s_MAKEAGGRESSION_00632fa8);
          }
          else {
            _sprintf(local_104,s_MAKEAGGRESSION__aggressor__s_vic_00632f80,
                     *(i32 *)(local_10c + 0xcc),*(i32 *)(local_10c + 0xc4));
          }
        }
        else if (uVar2 == 0x10) {
          if (*(int *)(local_10c + 0x184) == 0) {
            _sprintf(local_104,s_PLAYWAVEFILE_00632f70);
          }
          else {
            _sprintf(local_104,s_PLAYWAVEFILE___s__00632f5c,*(i32 *)(local_10c + 0x184));
          }
        }
      }
      else if (uVar2 < 0x81) {
        if (uVar2 == 0x80) {
          if (*(int *)(local_10c + 0x188) == 0) {
            _sprintf(local_104,s_PLAYCDTRACK_00632fe8);
          }
          else {
            _sprintf(local_104,s_PLAYCDTRACK___d__00632fd4,*(i32 *)(local_10c + 0x188));
          }
        }
        else if (uVar2 == 0x40) {
          _sprintf(local_104,s_JUSTONCE_00632fb8);
        }
      }
      else if (uVar2 < 0x201) {
        if (uVar2 == 0x200) {
          uVar3 = label_string(terrain_types[*(int *)(local_10c + 0x18c)].name);
          _sprintf(local_104,s_CHANGETERRAIN___s__00633004,uVar3);
        }
        else if (uVar2 == 0x100) {
          _sprintf(local_104,s_DONTPLAYWONDERS_00632ff4);
        }
      }
      else if (uVar2 == 0x400) {
        if (*(int *)(local_10c + 0x1b0) < 0) {
          if ((*(byte *)(local_10c + 1) & 1) == 0) {
            if (*(int *)(local_10c + 0x1b0) == -3) {
              _sprintf(local_104,s_DESTROYACIVILIZATION__TRIGGERATT_0063305c);
            }
            else {
              _sprintf(local_104,s_DESTROYACIVILIZATION__TRIGGERDEF_00633084);
            }
          }
          else {
            _sprintf(local_104,s_DESTROYACIVILIZATION__TRIGGERREC_00633034);
          }
        }
        else {
          uVar3 = civ_name_plural(*(iptr *)(local_10c + 0x1b0));
          _sprintf(local_104,s_DESTROYACIVILIZATION___s__00633018,uVar3);
        }
      }
      else if (uVar2 == 0x800) {
        if (*(int *)(local_10c + 0x1b8) == 0) {
          _sprintf(local_104,s_GIVETECHNOLOGY_00633134);
        }
        else if (*(int *)(local_10c + 0x1b8) < 0) {
          if ((*(byte *)(local_10c + 1) & 1) == 0) {
            if (*(int *)(local_10c + 0x1b8) == -3) {
              _sprintf(local_11c,s_TRIGGERATTACKER_006330e8);
            }
            else {
              _sprintf(local_11c,s_TRIGGERDEFENDER_006330f8);
            }
          }
          else {
            _sprintf(local_11c,s_TRIGGERRECEIVER_006330d8);
          }
          uVar3 = label_string(advances[*(int *)(local_10c + 0x1b4)].name);
          _sprintf(local_104,s_GIVETECHNOLOGY__receiver__s_tech_00633108,local_11c,uVar3);
        }
        else {
          uVar3 = label_string(advances[*(int *)(local_10c + 0x1b4)].name);
          uVar4 = civ_name_plural(*(iptr *)(local_10c + 0x1b8));
          _sprintf(local_104,s_GIVETECHNOLOGY__receiver__s_tech_006330ac,uVar4,uVar3);
        }
      }
      else if (uVar2 == 0x2000) {
        _sprintf(local_104,s_HASTRIGGERED_00632fc4);
      }
      if (local_104[0] != '\0') {
        listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xb0c),(iptr)local_104);
      }
      local_108 = local_108 << 1;
    } while (local_108 != 0x8000);
  }
  events_editor_update_buttons(0);
  return;
}
#undef local_11c
#undef local_10c
#undef local_108
#undef local_104

/* 0054c36e auto */
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
void __cdecl events_editor_on_delete_trigger(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_14 = 0;
  }
  else {
    local_14 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_14);
  iVar1 = popup_game(ADDR(0x633144, ((u8 *)&g.d_00633144)));
  if (iVar1 != 0) {
    iVar1 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
    local_c = iVar1;
    for (local_10 = events_list_head; local_10 != 0; local_10 = *(iptr *)(local_10 + 0x1bc)) {
      if (local_c == 0) break;
      local_c--;
    }
    if (*(int *)(local_10 + 0x1c0) != 0) {
      *(i32 *)(*(int *)(local_10 + 0x1c0) + 0x1bc) = *(i32 *)(local_10 + 0x1bc);
    }
    if (*(int *)(local_10 + 0x1bc) != 0) {
      *(i32 *)(*(int *)(local_10 + 0x1bc) + 0x1c0) = *(i32 *)(local_10 + 0x1c0);
    }
    if (iVar1 == 0) {
      events_list_head = *(iptr *)(local_10 + 0x1bc);
    }
    events_compact();
    events_editor_fill_triggers();
    events_editor_fill_actions(0);
  }
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef local_14
#undef local_10
#undef local_c

/* 0054c4a1 auto */
#define local_148 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_144 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_140 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_13c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_138 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_134 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_130 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_128 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_124 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_120 (*(uint * *)(frame_ + FRAME_OFF(40)))
#define local_11c (*(char (*)[260])(frame_ + FRAME_OFF(44)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(304)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(308)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(312)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(316)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(320)))
i32 __cdecl events_editor_edit_trigger(i32 param_1)

{
  size_t sVar1;
  int iVar2;
  i32 uVar3;
  uint uVar4;
  bool bVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(328)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_124 = 0;
  if (active_editor_wnd == 0) {
    local_128 = 0;
  }
  else {
    local_128 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_128);
  local_10 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  local_120 = (uint *)events_list_head;
  local_18 = local_10;
  while ((local_120 != (uint *)0x0 &&
         (iVar2 = local_18 - 1, bVar5 = local_18 != 0, local_18 = iVar2, bVar5))) {
    local_120 = (uint *)local_120[0x6f];
  }
  uVar4 = *local_120;
  if (uVar4 < 9) {
    if (uVar4 == 8) {
      if (active_editor_wnd == 0) {
        local_138 = 0;
      }
      else {
        local_138 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_138);
      local_c = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633194, ((u8 *)&g.d_00633194)),local_120[0xb],(iptr)&local_14);
      if (active_editor_wnd == 0) {
        local_13c = 0;
      }
      else {
        local_13c = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_13c);
      if (local_c == 0) {
        uVar4 = editor_clamp_value(local_14,0,0x7fff);
        local_120[0xb] = uVar4;
        local_124 = 1;
      }
    }
    else if (uVar4 == 1) {
      uVar6 = 1;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x890));
      local_c = events_editor_pick_item(local_120[3],uVar3,uVar6);
      if (local_c != 0xffffffff) {
        if ((int)local_c < 0) {
          local_120[3] = 0xfffffffe;
          local_8 = s_ANYUNIT_00633150;
        }
        else {
          local_120[3] = local_c;
          local_8 = (char *)label_string(unit_types[local_120[3]].name);
        }
        sVar1 = _strlen(local_8);
        uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
        local_120[2] = uVar4;
        if (local_120[2] != 0) {
          FUN_005f22d0(local_120[2],local_8);
          uVar6 = 4;
          uVar3 = label_string(*(i32 *)(label_string_ids + 0x894));
          local_c = events_editor_pick_item(local_120[6],uVar3,uVar6);
          if (local_c != 0xffffffff) {
            if ((int)local_c < 0) {
              local_120[6] = 0xfffffffe;
              local_8 = s_ANYBODY_00633158;
            }
            else {
              local_120[6] = local_c;
              local_8 = (char *)civ_name_plural(local_120[6]);
            }
            sVar1 = _strlen(local_8);
            uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
            local_120[5] = uVar4;
            if (local_120[5] != 0) {
              FUN_005f22d0(local_120[5],local_8);
              uVar6 = 4;
              uVar3 = label_string(*(i32 *)(label_string_ids + 0x898));
              local_c = events_editor_pick_item(local_120[9],uVar3,uVar6);
              if (local_c != 0xffffffff) {
                if ((int)local_c < 0) {
                  local_120[9] = 0xfffffffe;
                  local_8 = s_ANYBODY_00633160;
                }
                else {
                  local_120[9] = local_c;
                  local_8 = (char *)civ_name_plural(local_120[9]);
                }
                sVar1 = _strlen(local_8);
                uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
                local_120[8] = uVar4;
                if (local_120[8] != 0) {
                  FUN_005f22d0(local_120[8],local_8);
                  local_124 = 1;
                }
              }
            }
          }
        }
      }
    }
    else if (uVar4 == 2) {
      do {
        if (local_120[4] == 0) {
          local_120[4] = (uint)&events_city_default_str;
        }
        if (active_editor_wnd == 0) {
          local_130 = 0;
        }
        else {
          local_130 = active_editor_wnd + 0x48;
        }
        dlg_set_parent_window(local_130);
        local_c = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x63316c, ((u8 *)&g.d_0063316c)),0x17,local_120[4],(iptr)local_11c);
        dlg_set_parent_window(0);
      } while ((-1 < (int)local_c) &&
              ((sVar1 = _strlen(local_11c), sVar1 == 0 ||
               (iVar2 = editor_check_city_name((iptr)local_11c), iVar2 == 0))));
      if ((-1 < (int)local_c) && (sVar1 = _strlen(local_11c), sVar1 != 0)) {
        sVar1 = _strlen(local_11c);
        uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
        local_120[4] = uVar4;
        if (local_120[4] != 0) {
          FUN_005f22d0(local_120[4],local_11c);
          uVar6 = 4;
          uVar3 = label_string(*(i32 *)(label_string_ids + 0x894));
          local_c = events_editor_pick_item(local_120[6],uVar3,uVar6);
          if (local_c != 0xffffffff) {
            if ((int)local_c < 0) {
              local_120[6] = 0xfffffffe;
              local_8 = s_ANYBODY_00633178;
            }
            else {
              local_120[6] = local_c;
              local_8 = (char *)civ_name_plural(local_120[6]);
            }
            sVar1 = _strlen(local_8);
            uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
            local_120[5] = uVar4;
            if (local_120[5] != 0) {
              FUN_005f22d0(local_120[5],local_8);
              uVar6 = 4;
              uVar3 = label_string(*(i32 *)(label_string_ids + 0x898));
              local_c = events_editor_pick_item(local_120[9],uVar3,uVar6);
              if (local_c != 0xffffffff) {
                if ((int)local_c < 0) {
                  local_120[9] = 0xfffffffe;
                  local_8 = s_ANYBODY_00633180;
                }
                else {
                  local_120[9] = local_c;
                  local_8 = (char *)civ_name_plural(local_120[9]);
                }
                sVar1 = _strlen(local_8);
                uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
                local_120[8] = uVar4;
                if (local_120[8] != 0) {
                  FUN_005f22d0(local_120[8],local_8);
                  local_124 = 1;
                }
              }
            }
          }
        }
      }
    }
    else if (uVar4 == 4) {
      if (active_editor_wnd == 0) {
        local_134 = 0;
      }
      else {
        local_134 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_134);
      local_c = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633188, ((u8 *)&g.d_00633188)),local_120[0xb],(iptr)&local_14);
      dlg_set_parent_window(0);
      if (local_c == 0) {
        uVar4 = editor_clamp_value(local_14,0xffffffff,0x7fff);
        local_120[0xb] = uVar4;
        local_124 = 1;
      }
    }
  }
  else {
    switch(uVar4) {
    case 0x10:
      uVar6 = 4;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x89c));
      local_c = events_editor_pick_item(local_120[6],uVar3,uVar6);
      if (local_c != 0xffffffff) {
        if ((int)local_c < 0) {
          local_120[6] = 0xfffffffe;
          local_8 = s_ANYBODY_006331a4;
        }
        else {
          local_120[6] = local_c;
          local_8 = (char *)civ_name_plural(local_120[6]);
        }
        sVar1 = _strlen(local_8);
        uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
        local_120[5] = uVar4;
        if (local_120[5] != 0) {
          FUN_005f22d0(local_120[5],local_8);
          if ((local_120[7] == 0) || (local_120[7] == 1)) {
            local_c = 0;
          }
          else if (local_120[7] == 2) {
            local_c = 1;
          }
          else {
            local_c = 2;
          }
          if (active_editor_wnd == 0) {
            local_140 = 0;
          }
          else {
            local_140 = active_editor_wnd + 0x48;
          }
          dlg_set_parent_window(local_140);
          local_c = popup_text_run(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6331ac, ((u8 *)&g.d_006331ac)),local_c,0,0,0,1);
          dlg_set_parent_window(0);
          if (-1 < (int)local_c) {
            if (local_c == 0) {
              local_120[7] = 1;
            }
            else if (local_c == 1) {
              local_120[7] = 2;
            }
            else {
              local_120[7] = 4;
            }
            uVar6 = 4;
            uVar3 = label_string(*(i32 *)(label_string_ids + 0x8a0));
            local_c = events_editor_pick_item(local_120[9],uVar3,uVar6);
            if (local_c != 0xffffffff) {
              if ((int)local_c < 0) {
                local_120[9] = 0xfffffffe;
                local_8 = s_ANYBODY_006331b8;
              }
              else {
                local_120[9] = local_c;
                local_8 = (char *)civ_name_plural(local_120[9]);
              }
              sVar1 = _strlen(local_8);
              uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
              local_120[8] = uVar4;
              if (local_120[8] != 0) {
                FUN_005f22d0(local_120[8],local_8);
                if ((local_120[10] == 0) || (local_120[10] == 1)) {
                  local_c = 0;
                }
                else if (local_120[10] == 2) {
                  local_c = 1;
                }
                else {
                  local_c = 2;
                }
                if (active_editor_wnd == 0) {
                  local_144 = 0;
                }
                else {
                  local_144 = active_editor_wnd + 0x48;
                }
                dlg_set_parent_window(local_144);
                local_c = popup_text_run(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6331c0, ((u8 *)&g.d_006331c0)),local_c,0,0,0,1);
                dlg_set_parent_window(0);
                if (-1 < (int)local_c) {
                  if (local_c == 0) {
                    local_120[10] = 1;
                  }
                  else if (local_c == 1) {
                    local_120[10] = 2;
                  }
                  else {
                    local_120[10] = 4;
                  }
                  local_124 = 1;
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
      local_124 = 1;
      break;
    case 0x40:
      uVar4 = editor_clamp_value(local_120[0xc],1,1000);
      local_120[0xc] = uVar4;
      if (active_editor_wnd == 0) {
        local_148 = 0;
      }
      else {
        local_148 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_148);
      local_c = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6331cc, ((u8 *)&g.d_006331cc)),local_120[0xc],(iptr)&local_14);
      dlg_set_parent_window(0);
      if (local_c == 0) {
        uVar4 = editor_clamp_value(local_14,1,1000);
        local_120[0xc] = uVar4;
        local_124 = 1;
      }
      break;
    case 0x80:
      uVar6 = 4;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8a4));
      local_c = events_editor_pick_item(local_120[9],uVar3,uVar6);
      if (local_c != 0xffffffff) {
        if ((int)local_c < 0) {
          local_120[9] = 0xfffffffe;
          local_8 = s_ANYBODY_006331d8;
        }
        else {
          local_120[9] = local_c;
          local_8 = (char *)civ_name_plural(local_120[9]);
        }
        sVar1 = _strlen(local_8);
        uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
        local_120[8] = uVar4;
        if (local_120[8] != 0) {
          FUN_005f22d0(local_120[8],local_8);
          local_124 = 1;
        }
      }
      break;
    case 0x100:
      uVar6 = 4;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8a8));
      local_c = events_editor_pick_item(local_120[9],uVar3,uVar6);
      if (local_c != 0xffffffff) {
        if ((int)local_c < 0) {
          local_120[9] = 0xfffffffe;
          local_8 = s_ANYBODY_006331e0;
        }
        else {
          local_120[9] = local_c;
          local_8 = (char *)civ_name_plural(local_120[9]);
        }
        sVar1 = _strlen(local_8);
        uVar4 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar1 + 1);
        local_120[8] = uVar4;
        if (local_120[8] != 0) {
          FUN_005f22d0(local_120[8],local_8);
          uVar6 = 2;
          uVar3 = label_string(*(i32 *)(label_string_ids + 0x8ac));
          local_c = events_editor_pick_item(local_120[0xd],uVar3,uVar6);
          if (local_c != 0xffffffff) {
            local_120[0xd] = local_c;
            local_124 = 1;
          }
        }
      }
    }
  }
  events_compact();
  events_editor_fill_triggers();
  listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xad0),local_10);
  events_editor_update_buttons(0);
  events_editor_focus_redraw();
  dlg_set_parent_window(0);
  return local_124;
}
#undef local_148
#undef local_144
#undef local_140
#undef local_13c
#undef local_138
#undef local_134
#undef local_130
#undef local_128
#undef local_124
#undef local_120
#undef local_11c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0054d4ca auto */
void __cdecl events_editor_on_edit_trigger(i32 param_1)

{
  events_editor_edit_trigger(param_1);
  return;
}

/* 0054d4e6 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl events_editor_on_add_trigger(void)

{
  int *piVar1;
  LPCSTR lpCaption;
  LPCSTR lpText;
  iptr iVar2;
  int iVar3;
  UINT uType;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  while( true ) {
    if (active_editor_wnd == 0) {
      local_14 = 0;
    }
    else {
      local_14 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_14);
    dlg_help_pressed = 0;
    local_c = popup_game_ex(ADDR(0x6331e8, ((u8 *)&g.d_006331e8)),local_c,1);
    dlg_set_parent_window(0);
    if (dlg_help_pressed == 0) break;
    events_editor_help_trigger(local_c);
  }
  if (local_c != -1) {
    if ((events_pool_bytes_free < 0x1c4) ||
       (piVar1 = (int *)events_alloc((ScenarioEvents *)&scenario_events),
       piVar1 == (int *)0x0)) {
      uType = 0;
      lpCaption = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8d0));
      lpText = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8e8));
      iVar2 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar2 + 4),lpText,lpCaption,uType);
    }
    else {
      *piVar1 = 1 << ((byte)local_c & 0x1f);
      events_editor_fill_triggers();
      events_editor_fill_actions(0);
      iVar3 = listbox_get_count((C_00551d20 *)(active_editor_wnd + 0xad0));
      listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xad0),iVar3 - 1);
      iVar3 = events_editor_edit_trigger(0);
      if (iVar3 == 0) {
        for (local_10 = events_list_head; *(int *)(local_10 + 0x1bc) != 0;
            local_10 = *(iptr *)(local_10 + 0x1bc)) {
        }
        if (*(int *)(local_10 + 0x1c0) == 0) {
          events_list_head = *(iptr *)(local_10 + 0x1bc);
        }
        else {
          *(i32 *)(*(int *)(local_10 + 0x1c0) + 0x1bc) = *(i32 *)(local_10 + 0x1bc);
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
#undef local_14
#undef local_10
#undef local_c

/* 0054d6da auto */
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
void __cdecl events_editor_on_delete_action(void)

{
  int iVar1;
  i32 uVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  for (local_10 = events_list_head; local_10 != 0; local_10 = *(iptr *)(local_10 + 0x1bc)) {
    if (local_c == 0) break;
    local_c--;
  }
  if (active_editor_wnd == 0) {
    local_18 = 0;
  }
  else {
    local_18 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_18);
  iVar1 = popup_game(ADDR(0x6331f4, ((u8 *)&g.d_006331f4)));
  if (iVar1 != 0) {
    uVar2 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
    iVar1 = bits_nth_set(uVar2,*(i32 *)(local_10 + 4));
    if (iVar1 == 1) {
      *(i32 *)(local_10 + 0x38) = 0;
    }
    uVar3 = bits_nth_set(uVar2,*(i32 *)(local_10 + 4));
    *(uint *)(local_10 + 4) = *(uint *)(local_10 + 4) & ~uVar3;
    events_editor_fill_actions(0);
    events_compact();
  }
  dlg_set_parent_window(0);
  events_editor_focus_redraw();
  return;
}
#undef local_18
#undef local_10
#undef local_c

/* 0054d7ef auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_1f8 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_1f4 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_1f0 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_1ec (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_1e8 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_1e4 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_1e0 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_1dc (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_1d8 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_1d4 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_1d0 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_1cc (*(iptr *)(frame_ + FRAME_OFF(44)))
#define local_1c4 (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_1bc (*(uint *)(frame_ + FRAME_OFF(60)))
#define local_1b8 (*(i32 * *)(frame_ + FRAME_OFF(64)))
#define local_1b0 (*(char (*)[260])(frame_ + FRAME_OFF(72)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(332)))
#define local_a8 (*(C_0040f380_48 *)(frame_ + FRAME_OFF(336)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(408)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(412)))
#define local_58 (*(char (*)[64])(frame_ + FRAME_OFF(416)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(480)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(484)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(488)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(492)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(496)))
uint __cdecl events_editor_edit_action(i32 param_1)

{
  i32 uVar1;
  uint uVar2;
  i32 uVar3;
  size_t sVar4;
  int iVar5;
  char *pcVar6;
  long lVar7;
  bool bVar8;
  char **ppcVar9;
  i8 frame_[FRAME_OFF(504)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  edit_ctor(&local_a8);
  local_8 = 0;
  local_1bc = 0;
  if (active_editor_wnd == 0) {
    local_1c4 = 0;
  }
  else {
    local_1c4 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_1c4);
  local_ac = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  local_1b8 = (i32 *)events_list_head;
  while ((local_1b8 != (i32 *)0x0 &&
         (iVar5 = local_ac - 1, bVar8 = local_ac != 0, local_ac = iVar5, bVar8))) {
    local_1b8 = (i32 *)local_1b8[0x6f];
  }
  uVar3 = local_1b8[1];
  uVar1 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xb0c));
  uVar2 = bits_nth_set(uVar1,uVar3);
  if (uVar2 < 9) {
    if (uVar2 == 8) {
      ppcVar9 = &local_14;
      uVar3 = *local_1b8;
      uVar1 = label_string(*(i32 *)(label_string_ids + 0x8a8));
      local_18 = events_editor_pick_action_civ(local_1b8[0x5e],uVar1,uVar3,(iptr)ppcVar9);
      if (local_18 != -1) {
        local_1b8[0x5e] = local_18;
        sVar4 = _strlen(local_14);
        uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
        local_1b8[0x5d] = uVar3;
        if (local_1b8[0x5d] != 0) {
          FUN_005f22d0(local_1b8[0x5d],local_14);
          if (active_editor_wnd == 0) {
            local_1ec = 0;
          }
          else {
            local_1ec = active_editor_wnd + 0x48;
          }
          dlg_set_parent_window(local_1ec);
          local_18 = editor_input_long(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633278, ((u8 *)&g.d_00633278)),local_1b8[0x5f],(iptr)&local_60);
          dlg_set_parent_window(0);
          if (local_18 == 0) {
            uVar3 = editor_clamp_value(local_60,0xffff8ad0,30000);
            local_1b8[0x5f] = uVar3;
            local_1bc = 1;
          }
        }
      }
    }
    else if (uVar2 == 1) {
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8b0));
      iVar5 = editor_text_edit_dialog((iptr)(local_1b8 + 0xe),uVar3);
      local_1bc = (uint)(iVar5 != 0);
    }
    else if (uVar2 == 2) {
      uVar1 = 3;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8b4));
      local_18 = events_editor_pick_item(local_1b8[0x25],uVar3,uVar1);
      if (local_18 != -1) {
        if (local_18 < 0) {
          local_1b8[0x25] = 0xfffffffe;
          local_14 = s_ANYUNIT_00633200;
        }
        else {
          local_1b8[0x25] = local_18;
          local_14 = (char *)label_string(unit_types[local_1b8[0x25]].name);
        }
        sVar4 = _strlen(local_14);
        uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
        local_1b8[0x24] = uVar3;
        if (local_1b8[0x24] != 0) {
          FUN_005f22d0(local_1b8[0x24],local_14);
          ppcVar9 = &local_14;
          uVar3 = *local_1b8;
          uVar1 = label_string(*(i32 *)(label_string_ids + 0x8b8));
          local_18 = events_editor_pick_action_civ(local_1b8[0x23],uVar1,uVar3,(iptr)ppcVar9);
          if (local_18 != -1) {
            local_1b8[0x23] = local_18;
            sVar4 = _strlen(local_14);
            uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
            local_1b8[0x22] = uVar3;
            if (local_1b8[0x22] != 0) {
              FUN_005f22d0(local_1b8[0x22],local_14);
              _sprintf(local_58,s__d__d__d__d__d__d__d__d_00633208,local_1b8[0x27],local_1b8[0x28],
                       local_1b8[0x29],local_1b8[0x2a],local_1b8[0x2b],local_1b8[0x2c],
                       local_1b8[0x2d],local_1b8[0x2e]);
              if (active_editor_wnd == 0) {
                local_1cc = 0;
              }
              else {
                local_1cc = active_editor_wnd + 0x48;
              }
              dlg_set_parent_window(local_1cc);
              do {
                local_18 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633220, ((u8 *)&g.d_00633220)),0x1f,(iptr)local_58,(iptr)local_1b0)
                ;
                if (local_18 == -1) break;
                sVar4 = _strlen(local_1b0);
              } while (sVar4 == 0);
              dlg_set_parent_window(0);
              if (local_18 != -1) {
                sVar4 = _strlen(local_1b0);
                if (sVar4 != 0) {
                  FUN_005f22d0(&text_buffer,local_1b0);
                  for (local_ac = 0; local_ac < 4; local_ac++) {
                    uVar1 = 0x7fff;
                    uVar3 = 0;
                    pcVar6 = (char *)text_next_token();
                    lVar7 = _atol(pcVar6);
                    uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
                    local_1b8[local_ac * 2 + 0x27] = uVar3;
                    uVar1 = 0x7fff;
                    uVar3 = 0;
                    pcVar6 = (char *)text_next_token();
                    lVar7 = _atol(pcVar6);
                    uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
                    local_1b8[local_ac * 2 + 0x28] = uVar3;
                  }
                }
                _sprintf(local_58,s__d__d_00633228,local_1b8[0x2f],local_1b8[0x30]);
                if (active_editor_wnd == 0) {
                  local_1d0 = 0;
                }
                else {
                  local_1d0 = active_editor_wnd + 0x48;
                }
                dlg_set_parent_window(local_1d0);
                local_18 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633230, ((u8 *)&g.d_00633230)),8,(iptr)local_58,(iptr)local_1b0);
                if (active_editor_wnd == 0) {
                  local_1d4 = 0;
                }
                else {
                  local_1d4 = active_editor_wnd + 0x48;
                }
                dlg_set_parent_window(local_1d4);
                if (local_18 != -1) {
                  sVar4 = _strlen(local_1b0);
                  if (sVar4 != 0) {
                    FUN_005f22d0(&text_buffer,local_1b0);
                    uVar1 = 0x7fff;
                    uVar3 = 0;
                    pcVar6 = (char *)text_next_token();
                    lVar7 = _atol(pcVar6);
                    uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
                    local_1b8[0x2f] = uVar3;
                    uVar1 = 0x7fff;
                    uVar3 = 0;
                    pcVar6 = (char *)text_next_token();
                    lVar7 = _atol(pcVar6);
                    uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
                    local_1b8[0x30] = uVar3;
                  }
                  if (active_editor_wnd == 0) {
                    local_1d8 = 0;
                  }
                  else {
                    local_1d8 = active_editor_wnd + 0x48;
                  }
                  dlg_set_parent_window(local_1d8);
                  if (local_1b8[0x26] == -2) {
                    local_1dc = 0xffffffff;
                  }
                  else {
                    local_1dc = local_1b8[0x26];
                  }
                  local_18 = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x63323c, ((u8 *)&g.d_0063323c)),local_1dc,(iptr)&local_60);
                  dlg_set_parent_window(0);
                  if (local_18 == 0) {
                    if (local_60 == -1) {
                      local_1b8[0x26] = 0xfffffffe;
                    }
                    else {
                      uVar3 = editor_clamp_value(local_60,0,0x7fff);
                      local_1b8[0x26] = uVar3;
                    }
                    local_1bc = 1;
                  }
                }
              }
            }
          }
        }
      }
    }
    else if (uVar2 == 4) {
      uVar1 = 1;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8bc));
      local_18 = events_editor_pick_item(local_1b8[0x38],uVar3,uVar1);
      if (local_18 != -1) {
        local_1b8[0x38] = local_18;
        local_14 = (char *)label_string(unit_types[local_1b8[0x38]].name);
        sVar4 = _strlen(local_14);
        uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
        local_1b8[0x37] = uVar3;
        if (local_1b8[0x37] != 0) {
          FUN_005f22d0(local_1b8[0x37],local_14);
          ppcVar9 = &local_14;
          uVar3 = *local_1b8;
          uVar1 = label_string(*(i32 *)(label_string_ids + 0x8b8));
          local_18 = events_editor_pick_action_civ(local_1b8[0x36],uVar1,uVar3,(iptr)ppcVar9);
          if (local_18 != -1) {
            local_1b8[0x36] = local_18;
            sVar4 = _strlen(local_14);
            uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
            local_1b8[0x35] = uVar3;
            if (local_1b8[0x35] != 0) {
              FUN_005f22d0(local_1b8[0x35],local_14);
              if (active_editor_wnd == 0) {
                local_1e0 = 0;
              }
              else {
                local_1e0 = active_editor_wnd + 0x48;
              }
              dlg_set_parent_window(local_1e0);
              local_5c = popup_debug_ex(ADDR(0x633248, ((u8 *)&g.d_00633248)),local_1b8[0x4e],0);
              dlg_set_parent_window(0);
              if (-1 < local_5c) {
                local_1b8[0x4e] = local_5c;
                do {
                  if (local_1b8[0x4f] == 0) {
                    local_1b8[0x4f] = &events_homecity_default_str;
                  }
                  if (active_editor_wnd == 0) {
                    local_1e4 = 0;
                  }
                  else {
                    local_1e4 = active_editor_wnd + 0x48;
                  }
                  dlg_set_parent_window(local_1e4);
                  local_18 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633254, ((u8 *)&g.d_00633254)),0x17,local_1b8[0x4f],
                                                (iptr)local_1b0);
                  dlg_set_parent_window(0);
                } while ((-1 < local_18) &&
                        ((sVar4 = _strlen(local_1b0), sVar4 == 0 ||
                         (iVar5 = editor_check_city_name((iptr)local_1b0), iVar5 == 0))));
                if ((-1 < local_18) && (sVar4 = _strlen(local_1b0), sVar4 != 0)) {
                  sVar4 = _strlen(local_1b0);
                  uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
                  local_1b8[0x4f] = uVar3;
                  if (local_1b8[0x4f] != 0) {
                    FUN_005f22d0(local_1b8[0x4f],local_1b0);
                    for (local_ac = 0; local_ac < 10; local_ac++) {
                      local_1b8[0x4d] = local_ac;
                      _sprintf(local_58,s__d__d_00633264,local_1b8[local_ac * 2 + 0x39],
                               local_1b8[local_ac * 2 + 0x3a]);
                      if (active_editor_wnd == 0) {
                        local_1e8 = 0;
                      }
                      else {
                        local_1e8 = active_editor_wnd + 0x48;
                      }
                      dlg_set_parent_window(local_1e8);
                      text_set_number_arg(0,local_ac + 1);
                      local_18 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x63326c, ((u8 *)&g.d_0063326c)),8,(iptr)local_58,
                                                    (iptr)local_1b0);
                      dlg_set_parent_window(0);
                      if (local_18 == -1) {
                        if (local_ac == 0) break;
                        do {
                          local_1b8[local_ac * 2 + 0x39] = 0;
                          local_1b8[local_ac * 2 + 0x3a] = 0;
                          local_ac++;
                        } while (local_ac < 10);
                      }
                      else {
                        sVar4 = _strlen(local_1b0);
                        if (sVar4 != 0) {
                          FUN_005f22d0(&text_buffer,local_1b0);
                          uVar1 = 0x7fff;
                          uVar3 = 0;
                          pcVar6 = (char *)text_next_token();
                          lVar7 = _atol(pcVar6);
                          uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
                          local_1b8[local_ac * 2 + 0x39] = uVar3;
                          uVar1 = 0x7fff;
                          uVar3 = 0;
                          pcVar6 = (char *)text_next_token();
                          lVar7 = _atol(pcVar6);
                          uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
                          local_1b8[local_ac * 2 + 0x3a] = uVar3;
                        }
                      }
                    }
                    if (local_1b8[0x4d] != 0) {
                      local_1bc = 1;
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
  else if (uVar2 < 0x21) {
    if (uVar2 == 0x20) {
      uVar1 = 0;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8c0));
      local_18 = events_editor_pick_item(local_1b8[0x34],uVar3,uVar1);
      if (local_18 != -1) {
        local_1b8[0x34] = local_18;
        local_14 = (char *)civ_name_plural(local_1b8[0x34]);
        sVar4 = _strlen(local_14);
        uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
        local_1b8[0x33] = uVar3;
        if (local_1b8[0x33] != 0) {
          FUN_005f22d0(local_1b8[0x33],local_14);
          uVar1 = 0;
          uVar3 = label_string(*(i32 *)(label_string_ids + 0x8c4));
          local_18 = events_editor_pick_item(local_1b8[0x32],uVar3,uVar1);
          if (local_18 != -1) {
            local_1b8[0x32] = local_18;
            local_14 = (char *)civ_name_plural(local_1b8[0x32]);
            sVar4 = _strlen(local_14);
            uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
            local_1b8[0x31] = uVar3;
            if (local_1b8[0x31] != 0) {
              FUN_005f22d0(local_1b8[0x31],local_14);
              local_1bc = 1;
            }
          }
        }
      }
    }
    else if (uVar2 == 0x10) {
      if (local_1b8[0x61] == 0) {
        local_1b8[0x61] = &events_wavfile_default_str;
      }
      if (active_editor_wnd == 0) {
        local_1f0 = 0;
      }
      else {
        local_1f0 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_1f0);
      do {
        local_18 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633284, ((u8 *)&g.d_00633284)),10,local_1b8[0x61],(iptr)local_1b0);
        if (local_18 == -1) break;
        sVar4 = _strlen(local_1b0);
      } while (sVar4 == 0);
      dlg_set_parent_window(0);
      if (-1 < local_18) {
        sVar4 = _strlen(local_1b0);
        if (sVar4 != 0) {
          pcVar6 = _strchr(local_1b0,0x2e);
          if (pcVar6 == (char *)0x0) {
            FUN_005f22e0(local_1b0,&events_wav_ext_str);
          }
          __strupr(local_1b0);
          sVar4 = _strlen(local_1b0);
          uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar4 + 1);
          local_1b8[0x61] = uVar3;
          if (local_1b8[0x61] == 0) goto LAB_0054ee13;
          FUN_005f22d0(local_1b8[0x61],local_1b0);
        }
        local_1bc = 1;
      }
    }
  }
  else if (uVar2 < 0x81) {
    if (uVar2 == 0x80) {
      uVar3 = editor_clamp_value(local_1b8[0x62],2,0x18);
      local_1b8[0x62] = uVar3;
      text_set_number_arg(0,2);
      text_set_number_arg(1,0x18);
      if (active_editor_wnd == 0) {
        local_1f4 = 0;
      }
      else {
        local_1f4 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_1f4);
      local_18 = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633294, ((u8 *)&g.d_00633294)),local_1b8[0x62],(iptr)&local_60);
      dlg_set_parent_window(0);
      if (local_18 == 0) {
        uVar3 = editor_clamp_value(local_60,2,0x18);
        local_1b8[0x62] = uVar3;
        local_1bc = 1;
      }
    }
    else if (uVar2 == 0x40) {
      local_1bc = 1;
    }
  }
  else if (uVar2 < 0x201) {
    if (uVar2 == 0x200) {
      uVar1 = 7;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x970));
      local_18 = events_editor_pick_item(local_1b8[99],uVar3,uVar1);
      if (local_18 == -1) {
        local_18 = -1;
      }
      else {
        local_1b8[99] = local_18;
        _sprintf(local_58,s__d__d__d__d__d__d__d__d_0063329c,local_1b8[100],local_1b8[0x65],
                 local_1b8[0x66],local_1b8[0x67],local_1b8[0x68],local_1b8[0x69],local_1b8[0x6a],
                 local_1b8[0x6b]);
        if (active_editor_wnd == 0) {
          local_1f8 = 0;
        }
        else {
          local_1f8 = active_editor_wnd + 0x48;
        }
        dlg_set_parent_window(local_1f8);
        do {
          local_18 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6332b4, ((u8 *)&g.d_006332b4)),0x1f,(iptr)local_58,(iptr)local_1b0);
          if (local_18 == -1) break;
          sVar4 = _strlen(local_1b0);
        } while (sVar4 == 0);
        dlg_set_parent_window(0);
        if (local_18 != -1) {
          sVar4 = _strlen(local_1b0);
          if (sVar4 != 0) {
            FUN_005f22d0(&text_buffer,local_1b0);
            for (local_ac = 0; local_ac < 4; local_ac++) {
              uVar1 = 0x7fff;
              uVar3 = 0;
              pcVar6 = (char *)text_next_token();
              lVar7 = _atol(pcVar6);
              uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
              local_1b8[local_ac * 2 + 100] = uVar3;
              uVar1 = 0x7fff;
              uVar3 = 0;
              pcVar6 = (char *)text_next_token();
              lVar7 = _atol(pcVar6);
              uVar3 = editor_clamp_value(lVar7,uVar3,uVar1);
              local_1b8[local_ac * 2 + 0x65] = uVar3;
            }
          }
          local_1bc = 1;
        }
      }
    }
    else if (uVar2 == 0x100) {
      local_1bc = 1;
    }
  }
  else if (uVar2 == 0x400) {
    ppcVar9 = &local_14;
    uVar3 = *local_1b8;
    uVar1 = label_string(*(i32 *)(label_string_ids + 0x8c8));
    local_18 = events_editor_pick_action_civ(local_1b8[0x6c],uVar1,uVar3,(iptr)ppcVar9);
    if (local_18 != -1) {
      local_1b8[0x6c] = local_18;
      local_1bc = 1;
    }
  }
  else if (uVar2 == 0x800) {
    ppcVar9 = &local_14;
    uVar3 = *local_1b8;
    uVar1 = label_string(*(i32 *)(label_string_ids + 0x8a8));
    local_18 = events_editor_pick_action_civ(local_1b8[0x6e],uVar1,uVar3,(iptr)ppcVar9);
    if (local_18 == -1) {
      local_18 = -1;
    }
    else {
      local_1b8[0x6e] = local_18;
      uVar1 = 2;
      uVar3 = label_string(*(i32 *)(label_string_ids + 0x8ac));
      local_18 = events_editor_pick_item(local_1b8[0x6d],uVar3,uVar1);
      if (local_18 != -1) {
        local_1b8[0x6d] = local_18;
        local_1bc = 1;
      }
    }
  }
  else if (uVar2 == 0x2000) {
    local_1bc = 1;
  }
LAB_0054ee13:
  events_compact();
  events_editor_fill_actions(0);
  local_5c = bits_index_of(uVar2,local_1b8[1]);
  listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xb0c),local_5c);
  events_editor_update_buttons(0);
  events_editor_focus_redraw();
  dlg_set_parent_window(0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0054ee8f */ { edit_dtor((Control *)((iptr)&local_a8)); }
  return local_1bc;
}
#undef text_buffer
#undef local_1f8
#undef local_1f4
#undef local_1f0
#undef local_1ec
#undef local_1e8
#undef local_1e4
#undef local_1e0
#undef local_1dc
#undef local_1d8
#undef local_1d4
#undef local_1d0
#undef local_1cc
#undef local_1c4
#undef local_1bc
#undef local_1b8
#undef local_1b0
#undef local_ac
#undef local_a8
#undef local_60
#undef local_5c
#undef local_58
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0054eeb4 auto */
void __cdecl events_editor_on_edit_action(i32 param_1)

{
  events_editor_edit_action(param_1);
  return;
}

/* 0054eed0 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(int * *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl events_editor_on_add_action(void)

{
  LPCSTR lpCaption;
  LPCSTR lpText;
  i32 uVar1;
  int iVar2;
  UINT uType;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
  local_18 = (int *)events_list_head;
  while ((local_18 != (int *)0x0 && (local_14 != 0))) {
    local_18 = (int *)local_18[0x6f];
    local_14--;
  }
  if (*local_18 == 0x20) {
    local_14 = 0;
    while ((1 << ((byte)local_14 & 0x1f) & (local_18[1] | 0xfffffe6fU)) != 0) {
      local_14++;
    }
  }
  else {
    local_14 = 0;
    while ((local_18[1] & 1 << ((byte)local_14 & 0x1f)) != 0) {
      local_14++;
    }
  }
  if (local_14 < 0xd) {
    while( true ) {
      if (active_editor_wnd == 0) {
        local_20 = 0;
      }
      else {
        local_20 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_20);
      dlg_help_pressed = 0;
      if (*local_18 == 0x20) {
        local_14 = editor_options_dialog(ADDR(0x6332bc, ((u8 *)&g.d_006332bc)),local_14,local_18[1] | 0xfffffe6f,1);
      }
      else {
        local_14 = editor_options_dialog(ADDR(0x6332c4, ((u8 *)&g.d_006332c4)),local_14,local_18[1],1);
      }
      dlg_set_parent_window(0);
      if (dlg_help_pressed == 0) break;
      events_editor_help_action(local_14);
    }
    if (local_14 != -1) {
      local_18[1] = local_18[1] | 1 << ((byte)local_14 & 0x1f);
      uVar1 = bits_index_of(1 << ((byte)local_14 & 0x1f),local_18[1]);
      events_editor_fill_actions(0);
      listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xb0c),uVar1);
      iVar2 = events_editor_edit_action(0);
      if (iVar2 == 0) {
        local_8 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xad0));
        local_18 = (int *)events_list_head;
        while ((local_18 != (int *)0x0 && (local_8 != 0))) {
          local_18 = *(int **)((int)local_18 + 0x1bc);
          local_8--;
        }
        *(uint *)((int)local_18 + 4) =
             *(uint *)((int)local_18 + 4) & ~(1 << ((byte)local_14 & 0x1f));
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
#undef local_20
#undef local_18
#undef local_14
#undef local_8

/* 0054f16b auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __thiscall events_editor_draw(C_004083b0_430 *this)

{
  u32 uVar1;
  uptr uVar2;
  iptr iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  frame_wnd_draw_caption((FrameWindow *)this);
  gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1a);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  iVar6 = this->client_x + (int)this->client_width / 2;
  uVar1 = this->client_y;
  uVar2 = this->field_2e8;
  text_clear();
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x8d4));
  text_append_str(iVar3);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar6,(uVar1 - uVar2) + 0x19,0);
  uVar1 = this->client_y;
  uVar2 = this->field_2e8;
  text_clear();
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x8d8));
  text_append_str(iVar3);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar6,(uVar1 - uVar2) + 0xc3,0);
  uVar1 = this->client_x;
  iVar6 = uVar1 + 0x211;
  iVar4 = this->client_y + 0x1a;
  text_clear();
  _sprintf(&text_buffer,&events_pool_free_fmt,(uint)events_pool_bytes_free);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),uVar1 + 0x216,(iVar4 - this->field_2e8) - 2,0);
  uVar5 = ((uint)events_pool_bytes_free * 0x13b) / (uint)events_pool_size;
  gfx_fill_rect_xywh((iptr)this,iVar6,iVar4,10,uVar5,0x2a);
  gfx_fill_rect_xywh((iptr)this,iVar6,uVar5 + iVar4,10,0x13b - uVar5,0x6a);
  gfx_draw_frame_rect((iptr)this,iVar6,iVar4,10,0x13b,10);
  gfx_draw_frame_rect((iptr)this,iVar6,iVar4,10,uVar5,10);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef text_buffer

/* 0054f3b9 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define editor_value_clamped (*(i32 *)((u8 *)&g.d_0062e014))
#define events_editor_backup (*(ScenarioEvents * *)((u8 *)&g.d_00632578))
#define local_4a0 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_49c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_498 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_494 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_48c (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(28)))
#define local_480 (*(u8 * *)(frame_ + FRAME_OFF(32)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(36)))
#define local_478 (*(u8 * *)(frame_ + FRAME_OFF(40)))
#define local_474 (*(u8 * *)(frame_ + FRAME_OFF(44)))
#define local_470 (*(u8 * *)(frame_ + FRAME_OFF(48)))
#define local_464 (*(ScenarioEvents * *)(frame_ + FRAME_OFF(60)))
#define local_454 (*(i8 (*)[16])(frame_ + FRAME_OFF(76)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(92)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1168)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1172)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1176)))
void __thiscall events_editor_run(C_004083b0_a28 *this)

{
  ScenarioEvents *this_00;
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
  i8 frame_[FRAME_OFF(1184)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_444);
  local_8 = 0;
  editor_running = 1;
  active_editor_wnd = (iptr)this;
  this_00 = operator_new(0x310);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  if (this_00 == (ScenarioEvents *)0x0) {
    local_464 = (ScenarioEvents *)0x0;
  }
  else {
    local_464 = (ScenarioEvents *)events_ctor(this_00,50000);
  }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  events_editor_backup = local_464;
  events_reset(local_464,50000);
  events_copy((iptr)events_editor_backup,ADDR(0x64b690, ((u8 *)&g.d_0064b690)));
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
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x73c));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  this->field_2e0 = 0x97;
  iVar4 = this->client_y + 0x90;
  iVar3 = this->client_x + 0x32;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_470 = (u8 *)0x0;
  }
  else {
    local_470 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8dc));
  button_create
            ((Control *)(this->pad_65c + 0x2d0),(iptr)local_470,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_65c + 0x2d0),ADDR(0x403643, events_editor_on_add_trigger));
  iVar3 = iVar3 + this->field_2e0 + 3;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_474 = (u8 *)0x0;
  }
  else {
    local_474 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8e0));
  button_create
            ((Control *)(this->pad_65c + 0x30c),(iptr)local_474,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_65c + 0x30c),ADDR(0x40114a, events_editor_on_edit_trigger));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 3,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8e4));
  button_create
            ((Control *)(this->pad_980 + 0x24),(iptr)local_478,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_980 + 0x24),ADDR(0x40164a, events_editor_on_delete_trigger));
  iVar4 = this->client_y + 0x13a;
  iVar3 = this->client_x + 0x32;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8dc));
  button_create
            ((Control *)(this->pad_980 + 0x60),(iptr)local_47c,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_980 + 0x60),ADDR(0x402c84, events_editor_on_add_action));
  iVar3 = iVar3 + this->field_2e0 + 3;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8e0));
  button_create
            ((Control *)&this->edit_action_button,(iptr)local_480,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this->edit_action_button,ADDR(0x402919, events_editor_on_edit_action));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 3,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8e4));
  button_create
            ((Control *)&this[1].field_30,(iptr)local_484,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_30,ADDR(0x4027c5, events_editor_on_delete_action));
  rect_set_xywh((iptr)local_454,this->client_x + 0x32,this->client_y + 0x1b,0x1cb,0x6e);
  iVar3 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_a28 *)0x0) {
    local_48c = (u8 *)0x0;
  }
  else {
    local_48c = this->pad_48;
  }
  listbox_create
            ((Control *)(this[1].pad_48 + 0x60),(iptr)local_48c,iVar3,(iptr)local_454);
  listbox_set_font((ListBoxFontView *)(this[1].pad_48 + 0x60),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  listbox_set_select_callback((ListBoxSelectSetView *)(this[1].pad_48 + 0x60),ADDR(0x4038f0, events_editor_fill_actions));
  listbox_set_dblclick_callback((ListBoxDblClickSetView *)(this[1].pad_48 + 0x60),ADDR(0x40114a, events_editor_on_edit_trigger));
  events_editor_fill_triggers();
  listbox_set_cur_sel((ListBoxSetSelView *)(this[1].pad_48 + 0x60),0);
  rect_set_xywh((iptr)local_454,this->client_x + 0x32,this->client_y + 0xc5,0x1cb,0x6e);
  iVar3 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_a28 *)0x0) {
    local_494 = (u8 *)0x0;
  }
  else {
    local_494 = this->pad_48;
  }
  listbox_create
            ((Control *)(this[1].pad_48 + 0x9c),(iptr)local_494,iVar3,(iptr)local_454);
  listbox_set_font((ListBoxFontView *)(this[1].pad_48 + 0x9c),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  listbox_set_select_callback((ListBoxSelectSetView *)(this[1].pad_48 + 0x9c),ADDR(0x401983, events_editor_update_buttons));
  listbox_set_dblclick_callback((ListBoxDblClickSetView *)(this[1].pad_48 + 0x9c),ADDR(0x402919, events_editor_on_edit_action));
  events_editor_fill_actions(0);
  events_editor_update_buttons(0);
  this->field_2e0 = (int)(this->client_width - 8) / 3;
  iVar4 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_498 = (u8 *)0x0;
  }
  else {
    local_498 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)(this->pad_65c + 0x78),(iptr)local_498,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_65c + 0x78),ADDR(0x402ced, events_editor_on_ok));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_49c = (u8 *)0x0;
  }
  else {
    local_49c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)(this->pad_65c + 0xb4),(iptr)local_49c,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_65c + 0xb4),ADDR(0x401861, events_editor_on_help));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_a28 *)0x0) {
    local_4a0 = (u8 *)0x0;
  }
  else {
    local_4a0 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)(this->pad_65c + 0xf0),(iptr)local_4a0,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this->pad_65c + 0xf0),ADDR(0x40317a, events_editor_on_cancel));
  ctrl_set_cancel_button((Control *)(this->pad_65c + 0xf0));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  editor_value_clamped = 0;
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402ed2, events_editor_focus_redraw));
  wnd_repaint((SurfaceWindow *)this);
  window_show((C_004083b0_4 *)this);
  wnd_run_modal_loop((C_00408010_b8 *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (events_editor_backup != (ScenarioEvents *)0x0) {
    events_delete((C_0040bc40_28 *)events_editor_backup,1);
  }
  events_editor_backup = (ScenarioEvents *)0x0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0054ffa4 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_next_ctrl_id
#undef editor_running
#undef editor_value_clamped
#undef events_editor_backup
#undef local_4a0
#undef local_49c
#undef local_498
#undef local_494
#undef local_48c
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_470
#undef local_464
#undef local_454
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0054ffc8 auto */
#define local_b58 (*(C_004083b0_a28 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl events_editor_open(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  events_editor_run(&local_b58);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00550017 */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00551cd0 auto */
C_0040bc40_28 * __thiscall events_delete(C_0040bc40_28 *this,uint param_1)

{
  events_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00554297 auto */
#define mp_turn_time_limit_ms (*(i32 *)((u8 *)&g.d_00654b70))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl cheat_toggle_mode(void)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 0; local_c < 8; local_c++) {
    if (*(int *)(&civ_has_password + local_c * 4) != 0) {
      local_8++;
    }
  }
  if (local_8 == 0) {
    if (((game.game_options & 0x8000) == 0) && ((game.game_flags & 0x10) == 0)) {
      iVar3 = popup_game_with_sprite(ADDR(0x633740, ((u8 *)&g.d_00633740)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (iVar3 == 0) {
        return;
      }
      uVar2 = game.game_flags | 0x10;
      uVar1 = game.game_flags & 0x80;
      game.game_flags = uVar2;
      if (uVar1 != 0) {
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
    text_set_number_arg(0,local_8);
    if (local_8 == 1) {
      popup_game_with_sprite(ADDR(0x633718, ((u8 *)&g.d_00633718)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
    else {
      popup_game_with_sprite(ADDR(0x63372c, ((u8 *)&g.d_0063372c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
  }
  return;
}
#undef mp_turn_time_limit_ms
#undef local_c
#undef local_8

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
#define local_318 (*(byte *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_30c (*(i8 (*)[4])(frame_ + FRAME_OFF(12)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl cheat_edit_technologies(void)

{
  uptr civ;
  iptr iVar2;
  iptr iVar1;
  int advance3;
  int iVar4;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_14 = -1;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  unit_blink_active = 0;
  civ = dbg_pick_player(0);
  if ((int)civ < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0055493e */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  }
  else {
    while( true ) {
      dlg_load_game_section(&local_308,ADDR(0x633774, ((u8 *)&g.d_00633774)),1);
      for (advance = 0; advance < 100; advance++) {
        if (advances[advance].enabled != '\0') {
          text_clear();
          text_append_string_id(advances[advance].name);
          text_append_space();
          iVar2 = civ_has_advance(civ,advance);
          if (iVar2 == 0) {
            iVar1 = civ_has_advance(civ,(int)advances[advance].preq[0]);
            if ((iVar1 == 0) ||
               (advance3 = civ_has_advance(civ,(int)advances[advance].preq[1]), advance3 == 0)) {
              text_append(ADDR(0x633784, ((u8 *)&g.d_00633784)));
            }
          }
          else {
            text_append(ADDR(0x633780, ((u8 *)&g.d_00633780)));
          }
          dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),advance,0);
        }
      }
      if (-1 < local_14) {
        dialog_set_default_choice((DialogOptionList *)&local_308,local_14);
      }
      advance3 = dlg_show_modal(&local_308,0);
      if (advance3 < 0) break;
      if (local_308.field_dc == 0) {
        iVar4 = civ_has_advance(civ,advance3);
        if (iVar4 == 0) {
          civ_give_advance(civ,advance3,0,0,0);
        }
        else {
          bit_index_split(advance3,(iptr)&advance2,(iptr)local_30c);
          civs[civ].advances[advance2] =
               civs[civ].advances[advance2] & ~local_30c[0];
          local_318 = (byte)civ;
          game.advance_known_by[advance3] =
               game.advance_known_by[advance3] & ~(byte)(1 << (local_318 & 0x1f));
        }
        civs[civ].num_advances = '\0';
        local_14 = advance3;
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
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0055493e */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  }
  return;
}
#undef unit_blink_active
#undef local_318
#undef advance
#undef advance2
#undef local_30c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_324 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_320 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(776)))
#define y2 (*(int *)(frame_ + FRAME_OFF(780)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(784)))
#define local_14 (*(byte *)(frame_ + FRAME_OFF(788)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(792)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(800)))
void __cdecl cheat_change_terrain(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uptr terrain;
  iptr x;
  uint uVar5;
  uptr uVar6;
  i32 uVar8;
  uptr uVar7;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  iVar2 = map_in_bounds((int)map_cursor_x,(int)map_cursor_y);
  if (iVar2 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  }
  else {
    iVar2 = tile_city_owner((int)map_cursor_x,(int)map_cursor_y);
    if (iVar2 < 0) {
      pbVar3 = (byte *)tile_at((int)map_cursor_x,(int)map_cursor_y);
      bVar1 = tile_terrain((int)map_cursor_x,(int)map_cursor_y);
      uVar5 = (uint)bVar1;
      terrain2 = uVar5;
      iVar2 = tile_is_ocean((int)map_cursor_x,(int)map_cursor_y);
      if (iVar2 == 0) {
        dialog_load_text(&local_314,ADDR(0x633794, ((u8 *)&g.d_00633794)),ADDR(0x633788, ((u8 *)&g.d_00633788)),1);
        uVar8 = 0;
        uVar7 = terrain2;
        x = label_string(terrain_types[terrain2].name);
        dialog_add_option((DialogOptionList *)&local_314,x,uVar7,uVar8);
        while (-1 < terrain_types[terrain2].irrigate_to) {
          terrain = (uptr)terrain_types[terrain2].irrigate_to;
          uVar8 = 0;
          terrain2 = terrain;
          x = label_string(terrain_types[terrain].name);
          dialog_add_option((DialogOptionList *)&local_314,x,terrain,uVar8);
        }
        if (uVar5 != terrain2) {
          if ((cheat_terrain_saved_bits < 0) &&
             (terrain2 = dlg_show_modal(&local_314,0), (int)terrain2 < 0)) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
            goto LAB_005551a5;
          }
          *pbVar3 = *pbVar3 & 0x80;
          *pbVar3 = *pbVar3 | (byte)terrain2;
        }
        local_14 = pbVar3[1];
        dlg_check_set(0,local_14 & 4);
        dlg_check_set(1,local_14 & 8);
        dlg_check_set(2,local_14 & 0x10);
        dlg_check_set(3,local_14 & 0x20);
        dlg_check_set(4,(uint)((local_14 & 0x42) == 0x40));
        dlg_check_set(5,(uint)((local_14 & 0x42) == 0x42));
        dlg_check_set(6,local_14 & 0x80);
        if (cheat_terrain_saved_bits < 0) {
          iVar2 = popup_text_flags(ADDR(0x6337a4, ((u8 *)&g.d_006337a4)),ADDR(0x63379c, ((u8 *)&g.d_0063379c)),1);
          if (iVar2 < 0) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
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
          if ((local_14 & 0x80) != 0) {
            game.polluted_tiles--;
          }
          local_14 = local_14 & 1;
          iVar2 = dlg_check_get(0);
          if (iVar2 != 0) {
            local_14 = local_14 | 4;
          }
          iVar2 = dlg_check_get(1);
          if (iVar2 != 0) {
            local_14 = local_14 | 8;
          }
          iVar2 = dlg_check_get(2);
          if (iVar2 != 0) {
            local_14 = local_14 | 0x10;
          }
          iVar2 = dlg_check_get(3);
          if (iVar2 != 0) {
            local_14 = local_14 | 0x30;
          }
          iVar2 = dlg_check_get(4);
          if (iVar2 != 0) {
            local_14 = local_14 | 0x40;
          }
          iVar2 = dlg_check_get(5);
          if (iVar2 != 0) {
            local_14 = local_14 | 0x42;
          }
          iVar2 = dlg_check_get(6);
          if (iVar2 != 0) {
            local_14 = local_14 | 0x80;
            game.polluted_tiles++;
          }
          pbVar3[1] = local_14;
          for (local_324 = 1; local_324 < 8; local_324++) {
            iVar2 = tile_visible_to((int)map_cursor_x,(int)map_cursor_y,local_324);
            if (iVar2 != 0) {
              tile_update_known((int)map_cursor_x,(int)map_cursor_y,local_324);
            }
          }
          map_redraw_area_all_views((int)map_cursor_x,(int)map_cursor_y,1,human_civ,1);
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
          goto LAB_005551a5;
        }
      }
      dialog_close(&local_314);
      dialog_init_defaults(&local_314);
      dialog_load_text(&local_314,ADDR(0x6337b8, ((u8 *)&g.d_006337b8)),ADDR(0x6337ac, ((u8 *)&g.d_006337ac)),1);
      for (terrain2 = 0; (int)terrain2 < 0xb; terrain2++) {
        uVar8 = 0;
        uVar6 = terrain2;
        x = label_string(terrain_types[terrain2].name);
        dialog_add_option((DialogOptionList *)&local_314,x,uVar6,uVar8);
        if (uVar5 == terrain2) {
          dialog_set_default_choice((DialogOptionList *)&local_314,terrain2);
        }
      }
      terrain2 = dlg_show_modal(&local_314,0);
      if ((int)terrain2 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
      }
      else if (uVar5 == terrain2) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
      }
      else {
        if (terrain2 == 10) {
          *pbVar3 = 10;
          local_320 = 0x3f;
          for (local_18 = 0; local_18 < 8; local_18++) {
            x = map_wrap_x((int)(char)(&dir_dx_table)[local_18] + (int)map_cursor_x);
            y2 = (int)(char)(&dir_dy_table)[local_18] + (int)map_cursor_y;
            iVar2 = map_in_bounds(x,y2);
            if (((iVar2 != 0) && (iVar2 = tile_is_ocean(x,y2), iVar2 != 0)) &&
               (iVar2 = tile_landmass(x,y2), iVar2 < local_320)) {
              local_320 = iVar2;
            }
          }
          pbVar3[3] = (byte)local_320;
        }
        else {
          *pbVar3 = *pbVar3 & 0x80;
          *pbVar3 = *pbVar3 | (byte)terrain2;
          if (uVar5 == 10) {
            local_320 = 0x3f;
            for (local_18 = 0; local_18 < 8; local_18++) {
              x = map_wrap_x((int)(char)(&dir_dx_table)[local_18] + (int)map_cursor_x);
              y2 = (int)(char)(&dir_dy_table)[local_18] + (int)map_cursor_y;
              iVar2 = map_in_bounds(x,y2);
              if (((iVar2 != 0) && (iVar2 = tile_is_ocean(x,y2), iVar2 == 0)) &&
                 (iVar2 = tile_landmass(x,y2), iVar2 < local_320)) {
                local_320 = iVar2;
              }
            }
            pbVar3[3] = (byte)local_320;
          }
        }
        map_redraw_tile_all_views((int)map_cursor_x,(int)map_cursor_y);
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
      }
    }
    else {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0055518f */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
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
#undef local_324
#undef local_320
#undef local_314
#undef terrain2
#undef y2
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005551b3 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
void __cdecl cheat_create_unit(void)

{
  iptr iVar1;
  iptr iVar2;
  int unit;
  iptr iVar5;
  i32 uVar6;
  iptr iVar4;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  if (human_civ != cheat_unit_last_human_civ) {
    cheat_unit_last_human_civ = human_civ;
    cheat_unit_owner_civ = 0xffffffff;
  }
  if ((int)cheat_unit_owner_civ < 0) {
    cheat_unit_owner_civ = human_civ;
  }
  while( true ) {
    dialog_load_text(&local_304,ADDR(0x6337cc, ((u8 *)&g.d_006337cc)),ADDR(0x6337c0, ((u8 *)&g.d_006337c0)),1);
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      if ((((unit_types[unit_type].obsolete_by < '\0') ||
           (iVar1 = civ_has_advance(cheat_unit_owner_civ,(int)unit_types[unit_type].obsolete_by),
           iVar1 == 0)) || (cheat_unit_show_obsolete != '\0')) &&
         ((cheat_unit_ignore_prereq != '\0' ||
          (iVar2 = civ_has_advance(cheat_unit_owner_civ,(int)unit_types[unit_type].prerequisite),
          iVar2 != 0)))) {
        text_clear();
        if (cheat_unit_veteran != '\0') {
          text_append_label(0xd);
          text_append_space();
        }
        text_append_string_id(unit_types[unit_type].name);
        dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_type,0);
        if (cheat_unit_last_type < 0) {
          cheat_unit_last_type = unit_type;
        }
      }
    }
    if (-1 < cheat_unit_last_type) {
      dialog_set_default_choice((DialogOptionList *)&local_304,cheat_unit_last_type);
    }
    unit = dlg_show_modal(&local_304,0);
    cheat_unit_last_type = unit;
    if (unit < 0) break;
    switch(local_304.field_dc) {
    case 1:
      dlg_reset(&local_304,1);
      for (cheat_unit_owner_civ = 0; (int)cheat_unit_owner_civ < 8; cheat_unit_owner_civ++) {
        if ((cheat_unit_owner_civ == 0) || ((1 << ((byte)cheat_unit_owner_civ & 0x1f) & (uint)game.civs_alive) != 0)
           ) {
          uVar6 = 0;
          iVar4 = cheat_unit_owner_civ;
          iVar5 = civ_name_plural(cheat_unit_owner_civ);
          dialog_add_option((DialogOptionList *)&local_304,iVar5,iVar4,uVar6);
        }
      }
      cheat_unit_owner_civ = dlg_show_modal(&local_304,0);
      if ((int)cheat_unit_owner_civ < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_005555eb */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
      }
      else {
switchD_00555538_default:
        unit = unit_create(unit,cheat_unit_owner_civ,(int)map_cursor_x,(int)map_cursor_y);
        if ((-1 < unit) && (cheat_unit_veteran != '\0')) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        map_redraw_tile_all_views((int)map_cursor_x,(int)map_cursor_y);
        unit_blink_active = 0;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_005555eb */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
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
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005555eb */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  goto LAB_00555601;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef unit_blink_active
#undef unit_type
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0055560f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(i8 *)(frame_ + FRAME_OFF(8)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl cheat_reveal_map(void)

{
  iptr iVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  dialog_load_text(&local_304,ADDR(0x6337e0, ((u8 *)&g.d_006337e0)),ADDR(0x6337d4, ((u8 *)&g.d_006337d4)),1);
  for (civ = 0; civ < 8; civ++) {
    text_clear();
    iVar1 = civ_get_adjective(civ);
    text_append(iVar1);
    dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
  }
  uVar4 = 0;
  iVar3 = 0x62;
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x13c));
  dialog_add_option((DialogOptionList *)&local_304,iVar1,iVar3,uVar4);
  uVar4 = 0;
  iVar3 = 99;
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x138));
  dialog_add_option((DialogOptionList *)&local_304,iVar1,iVar3,uVar4);
  if ((game.reveal_map == '\0') && (game.view_civ < '\0')) {
    dialog_set_default_choice((DialogOptionList *)&local_304,0x62);
  }
  else {
    dialog_set_default_choice((DialogOptionList *)&local_304,99);
  }
  iVar2 = dlg_show_modal(&local_304,0);
  if (iVar2 < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0055581b */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  else {
    if (iVar2 == 0x62) {
      game.reveal_map = 1;
      game.view_civ = -1;
    }
    else if (iVar2 == 99) {
      game.reveal_map = '\0';
      game.view_civ = -1;
    }
    else {
      game.reveal_map = '\0';
      local_308 = (i8)iVar2;
      game.view_civ = local_308;
    }
    if (-1 < game.view_civ) {
      human_civ = (iptr)game.view_civ;
      game.human_players = (u8)(1 << (game.view_civ & 0x1fU));
    }
    mapview_update_title((FrameWindow *)&map_views);
    map_redraw_all_views(human_civ,1);
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0055581b */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  return;
}
#undef human_civ
#undef civ
#undef local_308
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0055583f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(byte *)(frame_ + FRAME_OFF(8)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl cheat_set_human_player(void)

{
  iptr iVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  dialog_load_text(&local_304,ADDR(0x6337f4, ((u8 *)&g.d_006337f4)),ADDR(0x6337e8, ((u8 *)&g.d_006337e8)),1);
  for (civ = 1; civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
      text_clear();
      iVar1 = civ_get_adjective(civ);
      text_append(iVar1);
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
    }
  }
  uVar4 = 0;
  iVar3 = 99;
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x140));
  dialog_add_option((DialogOptionList *)&local_304,iVar1,iVar3,uVar4);
  iVar2 = dlg_show_modal(&local_304,0);
  if (iVar2 < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_005559de */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  else {
    if (iVar2 == 99) {
      game.human_players = '\0';
      player_turn_active = 0;
    }
    else {
      local_308 = (byte)iVar2;
      game.human_players = (u8)(1 << (local_308 & 0x1f));
      game.player_civ = local_308;
      game.turn_civ = local_308;
      human_civ = iVar2;
      map_redraw_all_views(iVar2,1);
      ui_redraw_all_maps(1);
    }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_005559de */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  return;
}
#undef human_civ
#undef player_turn_active
#undef civ
#undef local_308
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00555a02 auto */
#define local_8 (*(short (*)[2])(frame_ + FRAME_OFF(0)))
void __cdecl cheat_set_game_year(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_set_number_arg(0,(int)game.turn);
  iVar1 = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6337fc, ((u8 *)&g.d_006337fc)),(int)game.turn,(iptr)local_8);
  if (iVar1 == 0) {
    game.turn = local_8[0];
    uVar2 = game_turn_to_year((int)local_8[0]);
    game.year = (i16)uVar2;
    status_redraw(1);
    city_window_refresh((FrameWindow *)&city_window);
  }
  return;
}
#undef local_8

/* 00555a8b auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ2 (*(int *)(frame_ + FRAME_OFF(0)))
#define city (*(uptr *)(frame_ + FRAME_OFF(8)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl cheat_kill_civ(void)

{
  iptr iVar1;
  int civ;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  dialog_load_text(&local_304,ADDR(0x633810, ((u8 *)&g.d_00633810)),ADDR(0x633808, ((u8 *)&g.d_00633808)),1);
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) {
      text_clear();
      iVar1 = civ_get_adjective(civ2);
      text_append(iVar1);
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ2,0);
    }
  }
  civ = dlg_show_modal(&local_304,0);
  if (civ < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00555c8d */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
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
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00555c8d */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  return;
}
#undef human_civ
#undef civ2
#undef city
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl cheat_change_money(void)

{
  iptr civ;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = dbg_pick_player(0);
  if (-1 < civ) {
    iVar2 = civ_get_adjective(civ);
    text_set_string_arg(0,iVar2);
    text_set_number_arg_v(0,civs[civ].gold);
    iVar3 = dlg_input_number(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633818, ((u8 *)&g.d_00633818)),civs[civ].gold,(iptr)&local_8);
    if (iVar3 == 0) {
      if (30000 < local_8) {
        local_8 = 30000;
      }
      if (local_8 < 0) {
        local_8 = 0;
      }
      civs[civ].gold = local_8;
      city_window_refresh((FrameWindow *)&city_window);
      status_redraw(1);
    }
  }
  return;
}
#undef local_8

/* 0055625b auto */
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_318 (*(u8 *)(frame_ + FRAME_OFF(8)))
#define city (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_310 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(u8 (*)[4])(frame_ + FRAME_OFF(776)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl cheat_edit_unit(void)

{
  char civ;
  int iVar2;
  iptr iVar3;
  iptr iVar5;
  i32 uVar6;
  iptr iVar4;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  iVar2 = map_in_bounds((int)map_cursor_x,(int)map_cursor_y);
  if (iVar2 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_005569bf */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  }
  else {
    unit = tile_first_unit((int)map_cursor_x,(int)map_cursor_y);
    if (unit < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_005569bf */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    }
    else {
      iVar2 = unit_stack_sum(unit,2);
      if (1 < iVar2) {
        uVar6 = 1;
        iVar3 = label_string(*(i32 *)(label_string_ids + 0xf8));
        unit = unit_stack_select_dialog(unit,iVar3,uVar6);
        if (unit < 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_005569bf */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
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
                  iVar3 = civ_get_adjective((int)civ);
                  text_set_string_arg(0,iVar3);
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
                  iVar2 = popup_game(ADDR(0x633820, ((u8 *)&g.d_00633820)));
                  if (iVar2 == 0) {
                    local_8 = 0xffffffff;
                    /* inlined unwind funclet FUN_005569bf */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
                    goto LAB_005569d5;
                  }
                  if (iVar2 != 1) break;
                  units[unit].flags = units[unit].flags ^ 0x2000;
                  map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
                  status_redraw(1);
                }
                if (iVar2 != 2) break;
                units[unit].moves_used = '\0';
                map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
                status_redraw(1);
              }
              if (iVar2 != 3) break;
              uVar6 = unit_max_hp(unit);
              text_set_number_arg(0,uVar6);
              iVar2 = dlg_input_number_game(ADDR(0x63382c, ((u8 *)&g.d_0063382c)),(uint)units[unit].damage,(iptr)local_18);
              if (iVar2 == 0) {
                units[unit].damage = local_18[0];
              }
              map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
              status_redraw(1);
            }
            if (iVar2 != 4) break;
            local_310 = 0;
            dlg_load_game_section(&local_30c,ADDR(0x63383c, ((u8 *)&g.d_0063383c)),1);
            for (city = 0; city < game.num_cities; city++) {
              if ((cities[city].id != 0) && ((int)cities[city].owner == (int)civ)) {
                dialog_add_option
                          ((DialogOptionList *)&local_30c,(iptr)&cities[city].name,city,0);
                local_310++;
              }
            }
            if ((local_310 != 0) &&
               (iVar2 = dlg_show_modal(&local_30c,0), -1 < iVar2)) {
              if (local_30c.field_dc == 0) {
                local_318 = (u8)iVar2;
                units[unit].home_city = local_318;
              }
              else {
                units[unit].home_city = -1;
              }
              map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
              status_redraw(1);
            }
          }
          if (iVar2 != 5) break;
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
        if (iVar2 != 6) break;
        if (unit_types[units[unit].type].role == 7) {
          dlg_load_game_section(&local_30c,ADDR(0x63384c, ((u8 *)&g.d_0063384c)),1);
          for (local_14 = 0; local_14 < 0x10; local_14++) {
            uVar6 = 0;
            iVar4 = local_14;
            iVar3 = label_string(commodity_names[local_14]);
            dialog_add_option((DialogOptionList *)&local_30c,iVar3,iVar4,uVar6);
            if ((char)units[unit].counter == local_14) {
              dialog_set_default_choice((DialogOptionList *)&local_30c,local_14);
            }
          }
          uVar6 = 0;
          iVar5 = 0x10;
          iVar3 = label_string(*(i32 *)(label_string_ids + 0x300));
          dialog_add_option((DialogOptionList *)&local_30c,iVar3,iVar5,uVar6);
          if ((char)units[unit].counter < '\0') {
            dialog_set_default_choice((DialogOptionList *)&local_30c,0x10);
          }
          iVar2 = dlg_show_modal(&local_30c,0);
          if (-1 < iVar2) {
            if (iVar2 < 0x10) {
              local_318 = (u8)iVar2;
              units[unit].counter = local_318;
            }
            else {
              units[unit].counter = 0xff;
            }
            map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
            status_redraw(1);
          }
        }
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_005569bf */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    }
  }
LAB_005569d5:
  return;
}
#undef map_cursor_x
#undef map_cursor_y
#undef unit
#undef local_318
#undef city
#undef local_310
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005569e3 auto */
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(760)))
#define local_1c (*(i8 (*)[4])(frame_ + FRAME_OFF(764)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(768)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl cheat_edit_city(void)

{
  char civ;
  bool bVar2;
  iptr iVar3;
  iptr city;
  iptr iVar5;
  int iVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  iVar3 = map_in_bounds((int)map_cursor_x,(int)map_cursor_y);
  if (iVar3 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00556f30 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  }
  else {
    city = city_at((int)map_cursor_x,(int)map_cursor_y);
    if (city < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00556f30 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
    }
    else {
      civ = cities[city].owner;
      while( true ) {
        text_set_number_arg(0,(cities[city].flags & 0x4000000) >> 0x1a);
        text_clear();
        text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
        text_append_space();
        text_append_lparen();
        iVar5 = civ_get_adjective((int)civ);
        text_append(iVar5);
        text_append_rparen();
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        iVar6 = popup_game(ADDR(0x63385c, ((u8 *)&g.d_0063385c)));
        if (iVar6 == 0) break;
        if (iVar6 == 1) {
          iVar6 = dlg_input_number_game(ADDR(0x633868, ((u8 *)&g.d_00633868)),(int)cities[city].size,(iptr)local_1c);
          if (iVar6 == 0) {
            cities[city].size = local_1c[0];
          }
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
          status_redraw(1);
        }
        else if (iVar6 == 2) {
          for (local_20 = 0; local_20 < 0x1c; local_20++) {
            if (game.wonder_city[local_20] == city) {
              game.wonder_city[local_20] = -1;
            }
          }
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
          status_redraw(1);
        }
        else if (iVar6 == 3) {
          cities[city].flags = cities[city].flags & 0xfffffffc;
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
        }
        else if (iVar6 == 4) {
          dlg_load_game_section(&local_314,ADDR(0x633874, ((u8 *)&g.d_00633874)),1);
          bVar2 = false;
          for (city2 = 0; city2 < game.num_cities; city2++) {
            if ((cities[city2].id != 0) && (city2 != city)) {
              dialog_add_option
                        ((DialogOptionList *)&local_314,(iptr)&cities[city2].name,city2,0);
              bVar2 = true;
            }
          }
          if ((bVar2) &&
             (city2 = dlg_show_modal(&local_314,0), -1 < city2)) {
            uVar7 = city_has_improvement(city,1);
            for (improvement = 0; improvement < 5; improvement++) {
              *(i8 *)&cities[city].improvements[improvement] =
                   *(i8 *)&cities[city2].improvements[improvement];
            }
            city_set_improvement(city,1,uVar7);
            city_window_refresh((FrameWindow *)&city_window);
          }
        }
        else if (iVar6 == 5) {
          iVar6 = dlg_input_number_game(ADDR(0x633880, ((u8 *)&g.d_00633880)),(int)cities[city].shield_box,(iptr)local_1c);
          if (iVar6 == 0) {
            cities[city].shield_box = (*(i16 *)((char *)&local_1c + 0));
          }
          map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
          status_redraw(1);
          city_window_refresh((FrameWindow *)&city_window);
        }
        else {
          if (iVar6 != 6) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_00556f30 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
            goto LAB_00556f46;
          }
          cities[city].flags = cities[city].flags ^ 0x4000000;
        }
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00556f30 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
    }
  }
LAB_00556f46:
  return;
}
#undef map_cursor_x
#undef map_cursor_y
#undef local_314
#undef local_20
#undef local_1c
#undef improvement
#undef city2
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00556f54 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_318 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(u8 (*)[4])(frame_ + FRAME_OFF(768)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(772)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(776)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl cheat_edit_king(void)

{
  uint *puVar1;
  iptr civ;
  iptr iVar3;
  int iVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  civ = dbg_pick_player(0);
  if (civ < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00557e08 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  }
  else {
    while( true ) {
      text_set_number_arg(0,(civs[civ].flags & 0x200) >> 9);
      text_clear();
      iVar3 = civ_leader_name(civ);
      text_append(iVar3);
      text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      iVar4 = popup_game(ADDR(0x633890, ((u8 *)&g.d_00633890)));
      if (iVar4 == 0) break;
      if (iVar4 == 1) {
        civ2 = dbg_pick_player(0);
        if (-1 < civ2) {
          iVar3 = civ_leader_name(civ2);
          text_set_string_arg(1,iVar3);
          dlg_checks_clear();
          dlg_check_set(0,civs[civ].treaties[civ2] & 1);
          dlg_check_set(1,(civs[civ].treaties[civ2] & 2) >> 1);
          dlg_check_set(2,(civs[civ].treaties[civ2] & 4) >> 2);
          dlg_check_set(3,(civs[civ].treaties[civ2] & 8) >> 3);
          dlg_check_set(4,(civs[civ].treaties[civ2] & 0x2000) >> 0xd)
          ;
          dlg_check_set(5,(civs[civ].treaties[civ2] & 0x10) >> 4);
          dlg_check_set(6,(civs[civ].treaties[civ2] & 0x80) >> 7);
          iVar4 = popup_game_flags(ADDR(0x63389c, ((u8 *)&g.d_0063389c)),1);
          if (-1 < iVar4) {
            diplo_clear_treaty_flags(civ,civ2,0x60);
            iVar4 = dlg_check_get(0);
            if (iVar4 == 0) {
              diplo_clear_treaty_flags(civ,civ2,1);
            }
            else {
              diplo_set_treaty_flags(civ,civ2,1);
            }
            iVar4 = dlg_check_get(4);
            if (iVar4 == 0) {
              diplo_clear_treaty_flags(civ,civ2,0x200e);
              iVar4 = dlg_check_get(1);
              if (iVar4 != 0) {
                diplo_set_treaty_flags(civ,civ2,2);
              }
              iVar4 = dlg_check_get(2);
              if (iVar4 != 0) {
                diplo_set_treaty_flags(civ,civ2,4);
              }
              iVar4 = dlg_check_get(3);
              if (iVar4 != 0) {
                diplo_set_treaty_flags(civ,civ2,8);
              }
            }
            else {
              diplo_set_treaty_flags(civ,civ2,0x2000);
            }
            puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
            *puVar1 = *puVar1 & 0xffffff6f;
            iVar4 = dlg_check_get(5);
            if (iVar4 != 0) {
              puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
              *puVar1 = *puVar1 | 0x10;
            }
            iVar4 = dlg_check_get(6);
            if (iVar4 != 0) {
              puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
              *puVar1 = *puVar1 | 0x80;
            }
          }
        }
      }
      else if (iVar4 == 2) {
        civ2 = dbg_pick_player(0);
        if (-1 < civ2) {
          iVar3 = civ_leader_name(civ2);
          text_set_string_arg(1,iVar3);
          text_set_number_arg(0,(int)game.turn);
          iVar4 = dlg_input_number_game(ADDR(0x6338ac, ((u8 *)&g.d_006338ac)),(int)civs[civ].last_treaty_turn[civ2],(iptr)local_20);
          if (iVar4 == 0) {
            civs[civ].last_treaty_turn[civ2] = (*(i16 *)((char *)&local_20 + 0));
          }
        }
      }
      else if (iVar4 == 3) {
        civ2 = dbg_pick_player(0);
        if (-1 < civ2) {
          iVar3 = civ_leader_name(civ2);
          text_set_string_arg(1,iVar3);
          iVar4 = dlg_input_number_game(ADDR(0x6338b8, ((u8 *)&g.d_006338b8)),(uint)civs[civ].attitude[civ2],
                                     (iptr)local_20);
          if (iVar4 == 0) {
            civs[civ].attitude[civ2] = local_20[0];
          }
        }
      }
      else if (iVar4 == 4) {
        iVar4 = dlg_input_number_game(ADDR(0x6338c8, ((u8 *)&g.d_006338c8)),(uint)civs[civ].reputation,(iptr)local_20);
        if (iVar4 == 0) {
          civs[civ].reputation = local_20[0];
        }
      }
      else if (iVar4 == 5) {
        civs[civ].field_1f = '\0';
      }
      else if (iVar4 == 6) {
        for (local_14 = 0; local_14 < 8; local_14++) {
          for (civ2 = 0; civ2 < 8; civ2++) {
            civs[civ2].last_treaty_turn[local_14] = game.turn;
          }
        }
      }
      else if (iVar4 == 7) {
        civ_choose_research_dialog(civ,1);
      }
      else if (iVar4 == 8) {
        uVar5 = civ_research_cost(civ);
        text_set_number_arg(0,uVar5);
        iVar4 = dlg_input_number_game(ADDR(0x6338d4, ((u8 *)&g.d_006338d4)),(int)civs[civ].research_progress,(iptr)local_20);
        if (iVar4 == 0) {
          civs[civ].research_progress = (*(i16 *)((char *)&local_20 + 0));
          status_redraw(1);
        }
      }
      else if (iVar4 == 9) {
        civs[civ].researching = -1;
      }
      else if (iVar4 == 10) {
        text_clear();
        iVar3 = civ_name_plural(civ);
        text_append(iVar3);
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        if (-1 < leaders[civs[civ].tribe].leader_name) {
          uVar5 = label_string((int)leaders[civs[civ].tribe].leader_name);
          FUN_005f22d0((iptr)&civ_names[civ].leader_name,uVar5);
          leaders[civs[civ].tribe].leader_name = -leaders[civs[civ].tribe].leader_name;
        }
        if (-1 < leaders[civs[civ].tribe].plural) {
          uVar5 = label_string((int)leaders[civs[civ].tribe].plural);
          FUN_005f22d0((iptr)&civ_names[civ].tribe_name,uVar5);
          leaders[civs[civ].tribe].plural = -leaders[civs[civ].tribe].plural;
        }
        if (-1 < leaders[civs[civ].tribe].adjective) {
          uVar5 = label_string((int)leaders[civs[civ].tribe].adjective);
          FUN_005f22d0((iptr)&civ_names[civ].adjective,uVar5);
          leaders[civs[civ].tribe].adjective = -leaders[civs[civ].tribe].adjective;
        }
        for (local_18 = 0; local_18 < 7; local_18++) {
          for (local_318 = 0; local_318 < 2; local_318++) {
            leaders[civs[civ].tribe].titles[local_18][local_318] =
                 (short)(&government_titles[local_18].male)[local_318];
          }
        }
        text_set_string_arg(1,(iptr)&civ_names[civ].tribe_name);
        text_set_string_arg(2,(iptr)&civ_names[civ].adjective);
        dialog_load_text_section
                  (&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6338e4, ((u8 *)&g.d_006338e4)),0x17,(iptr)&civ_names[civ].leader_name,0,0,0,1);
        iVar4 = dlg_show_modal(&local_314,0);
        if (-1 < iVar4) {
          FUN_005f22d0((iptr)&civ_names[civ].leader_name,&text_string_args);
          FUN_005f22d0((iptr)&civ_names[civ].tribe_name,&text_string_arg1);
          FUN_005f22d0((iptr)&civ_names[civ].adjective,&text_string_arg2);
        }
      }
      else if (iVar4 == 0xb) {
        civ2 = dbg_pick_player(0);
        if (0 < civ2) {
          for (advance = 0; advance < 0xd; advance++) {
            *(i8 *)&civs[civ].advances[advance] =
                 *(i8 *)&civs[civ2].advances[advance];
          }
          civs[civ].num_advances = '\0';
          for (advance = 0; advance < 100; advance++) {
            iVar4 = civ_has_advance(civ,advance);
            if (iVar4 != 0) {
              civs[civ].num_advances++;
            }
          }
        }
      }
      else {
        if (iVar4 != 0xc) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_00557e08 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
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
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00557e08 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  }
LAB_00557e1e:
  return;
}
#undef advance
#undef local_318
#undef local_314
#undef local_20
#undef civ2
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00557e2c auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_victory_thresholds (*(short *)((u8 *)&g.d_0064bcbc))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_310 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(i8 (*)[4])(frame_ + FRAME_OFF(772)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(776)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl cheat_edit_victory(void)

{
  iptr iVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  iptr iVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_310,0x4000);
  local_8 = 0;
  while( true ) {
    local_18 = 0;
    local_14 = 0;
    for (city = 0; city < game.num_cities; city++) {
      if (cities[city].id != 0) {
        iVar1 = city_objective_value(city);
        local_18 += iVar1;
        if ((int)cities[city].owner == (int)scenario_objective_civ) {
          iVar2 = city_objective_value(city);
          local_14 += iVar2;
        }
      }
    }
    text_clear();
    text_append_int(local_18);
    text_append(ADDR(0x6338f4, ((u8 *)&g.d_006338f4)));
    text_append_int(local_14);
    text_append(ADDR(0x6338f8, ((u8 *)&g.d_006338f8)));
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    iVar3 = civ_name_plural((int)scenario_objective_civ);
    text_set_string_arg(0,iVar3);
    text_set_number_arg(0,((int)(short)scenario_flags & 2U) >> 1);
    text_set_number_arg(1,((int)(short)scenario_flags & 4U) >> 2);
    text_set_number_arg(2,(int)scenario_victory_thresholds);
    text_set_number_arg(3,(int)scenario_marginal_victory_score);
    text_set_number_arg(4,(int)scenario_marginal_defeat_score);
    text_set_number_arg(5,(int)scenario_decisive_defeat_score);
    iVar4 = popup_game(ADDR(0x6338fc, ((u8 *)&g.d_006338fc)));
    if (iVar4 < 1) break;
    if (iVar4 == 1) {
      scenario_flags = scenario_flags ^ 2;
    }
    else if (iVar4 == 2) {
      scenario_flags = scenario_flags ^ 4;
    }
    else if (iVar4 == 3) {
      dlg_reset(&local_310,1);
      uVar7 = 0;
      iVar6 = 0;
      iVar3 = label_string(*(i32 *)(label_string_ids + 0x38));
      dialog_add_option((DialogOptionList *)&local_310,iVar3,iVar6,uVar7);
      for (civ = 1; civ < 8; civ++) {
        uVar7 = 0;
        iVar4 = civ;
        iVar3 = civ_name_plural(civ);
        dialog_add_option((DialogOptionList *)&local_310,iVar3,iVar4,uVar7);
      }
      iVar4 = dlg_show_modal(&local_310,0);
      if (-1 < iVar4) {
        scenario_objective_civ = (short)iVar4;
      }
    }
    else {
      if ((iVar4 < 4) || (7 < iVar4)) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_00558177 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
LAB_0055818d:
        return;
      }
      iVar5 = dlg_input_number_game(ADDR(0x633908, ((u8 *)&g.d_00633908)),(int)(short)(&scenario_year_increment)[iVar4],(iptr)local_1c);
      if (iVar5 == 0) {
        (&scenario_year_increment)[iVar4] = (*(i16 *)((char *)&local_1c + 0));
      }
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00558177 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  goto LAB_0055818d;
}
#undef scenario_flags
#undef scenario_objective_civ
#undef scenario_victory_thresholds
#undef scenario_year_increment
#undef civ
#undef city
#undef local_310
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0055819b auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __cdecl cheat_edit_scenario_rules(void)

{
  int iVar1;
  
  while( true ) {
    while( true ) {
      while( true ) {
        while( true ) {
          text_set_number_arg(0,((int)(short)scenario_flags & 0x10U) >> 4);
          text_set_number_arg(1,((int)(short)scenario_flags & 0x20U) >> 5);
          text_set_number_arg(2,((int)(short)scenario_flags & 0x40U) >> 6);
          text_set_number_arg(3,((int)(short)scenario_flags & 0x8000U) >> 0xf);
          iVar1 = popup_game(ADDR(0x633918, ((u8 *)&g.d_00633918)));
          if (iVar1 == 0) {
            return;
          }
          if (iVar1 != 1) break;
          scenario_flags = scenario_flags ^ 0x10;
        }
        if (iVar1 != 2) break;
        scenario_flags = scenario_flags ^ 0x20;
      }
      if (iVar1 != 3) break;
      scenario_flags = scenario_flags ^ 0x40;
    }
    if (iVar1 != 4) break;
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
#define local_140 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_138 (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(268)))
#define aiStack_30 (*(int (*)[8])(frame_ + FRAME_OFF(272)))
#define local_10 (*(Tile * *)(frame_ + FRAME_OFF(304)))
#define local_c (*(i8 (*)[4])(frame_ + FRAME_OFF(308)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(312)))
void __cdecl cheat_scenario_params(void)

{
  i32 uVar1;
  iptr iVar4;
  iptr iVar2;
  iptr iVar3;
  int iVar5;
  uint uVar6;
  i8 frame_[FRAME_OFF(320)] __attribute__((aligned(8)));  /* original stack frame */
  
  while( true ) {
    uVar1 = game_turn_to_year((int)game.turn);
    game.year = (i16)uVar1;
    status_redraw(1);
    city_window_refresh((FrameWindow *)&city_window);
    text_set_number_arg(0,(int)scenario_tech_paradigm);
    text_set_number_arg(1,(int)scenario_year_increment);
    text_set_number_arg(2,(int)scenario_start_year);
    text_set_number_arg(3,(int)scenario_max_turns);
    text_set_number_arg(4,(int)(short)scenario_flags & 1);
    if ((game.game_flags & 0x80) == 0) {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0x68c));
      text_set_string_arg(0,iVar4);
    }
    else {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0x688));
      text_set_string_arg(0,iVar4);
    }
    text_set_string_arg(1,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)));
    iVar2 = popup_game(ADDR(0x633924, ((u8 *)&g.d_00633924)));
    if (iVar2 == 0) break;
    if (iVar2 == 1) {
      iVar3 = dlg_input_number_game(ADDR(0x633930, ((u8 *)&g.d_00633930)),(int)scenario_tech_paradigm,(iptr)local_c);
      if (iVar3 == 0) {
        scenario_tech_paradigm = (*(i16 *)((char *)&local_c + 0));
      }
    }
    else if (iVar2 == 2) {
      iVar5 = dlg_input_number_game(ADDR(0x633940, ((u8 *)&g.d_00633940)),(int)scenario_year_increment,(iptr)local_c);
      if (iVar5 == 0) {
        scenario_year_increment = (*(i16 *)((char *)&local_c + 0));
      }
    }
    else if (iVar2 == 3) {
      iVar5 = dlg_input_number_game(ADDR(0x633950, ((u8 *)&g.d_00633950)),(int)scenario_start_year,(iptr)local_c);
      if (iVar5 == 0) {
        scenario_start_year = (*(i16 *)((char *)&local_c + 0));
      }
    }
    else if (iVar2 == 4) {
      iVar5 = dlg_input_number_game(ADDR(0x633960, ((u8 *)&g.d_00633960)),(int)scenario_max_turns,(iptr)local_c);
      if (iVar5 == 0) {
        scenario_max_turns = (*(i16 *)((char *)&local_c + 0));
      }
    }
    else if (iVar2 == 5) {
      local_10 = map_tiles;
      for (local_8 = 0; local_8 < map.area; local_8++) {
        if ((local_10->owner & 0xf0) == 0xf0) {
          local_10->owner = local_10->owner & 0xf;
        }
        local_10++;
      }
      map_redraw_all_views(human_civ,1);
    }
    else if (iVar2 == 6) {
      local_10 = map_tiles;
      for (local_8 = 0; local_8 < map.area; local_8++) {
        if (((local_10->owner & 0xf0) != 0xf0) && ((local_10->improvements & 3) == 0)) {
          local_10->owner = local_10->owner | 0xf0;
        }
        local_10++;
      }
      map_redraw_all_views(human_civ,1);
    }
    else if (iVar2 == 7) {
      local_34 = tile_at(0,0);
      for (local_140 = 1; local_140 < 8; local_140++) {
        iVar5 = known_at(0,0,local_140);
        aiStack_30[local_140] = iVar5;
      }
      for (local_8 = 0; local_8 < map.area; local_8++) {
        *(i8 *)(local_34 + 4) = 0xff;
        for (local_140 = 1; local_140 < 8; local_140++) {
          *(i8 *)aiStack_30[local_140] = *(i8 *)(local_34 + 1);
          aiStack_30[local_140]++;
        }
        local_34 += 6;
      }
      for (city = 0; city < game.num_cities; city++) {
        if (cities[city].id != 0) {
          cities[city].known_to = 0xff;
          for (local_140 = 0; local_140 < 8; local_140++) {
            *(i8 *)&cities[city].revealed_size[local_140] = cities[city].size;
          }
          iVar5 = tile_at((int)cities[city].x,(int)cities[city].y);
          *(i8 *)(iVar5 + 4) = 0xff;
        }
      }
      scenario_flags = scenario_flags | 8;
      map_redraw_all_views(human_civ,1);
    }
    else if (iVar2 == 8) {
      local_34 = tile_at(0,0);
      for (local_8 = 0; local_8 < map.area; local_8++) {
        *(i8 *)(local_34 + 4) = 0;
        if (((*(byte *)(local_34 + 1) & 3) != 0) &&
           (uVar6 = (int)(uint)*(byte *)(local_34 + 5) >> 4, uVar6 < 8)) {
          (*(i8 *)((char *)&local_140 + 0)) = (sbyte)uVar6;
          *(char *)(local_34 + 4) = (char)(1 << (sbyte)local_140);
        }
        local_34 += 6;
      }
      scenario_flags = scenario_flags & 0xfff7;
      map_redraw_all_views(human_civ,1);
    }
    else if (iVar2 == 9) {
      iVar5 = dlg_game_text_input(ADDR(0x633970, ((u8 *)&g.d_00633970)),0x18,ADDR(0x64bc62, ((u8 *)&g.d_0064bc62)),(iptr)local_138);
      if (iVar5 == 0) {
        FUN_005f22d0(&scenario_name,local_138);
      }
    }
    else if (iVar2 == 10) {
      scenario_flags = scenario_flags ^ 1;
    }
    else if (iVar2 == 0xb) {
      cheat_edit_victory();
    }
    else {
      if (iVar2 != 0xc) {
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
#undef local_140
#undef city
#undef local_138
#undef local_34
#undef aiStack_30
#undef local_10
#undef local_c
#undef local_8

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
  setup_picwnd_ctor((C_004083b0_430 *)&setup_picwnd);
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
  setup_picwnd_dtor((C_004083b0_430 *)&setup_picwnd);
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
#define local_48c (*(DibSurface *)(frame_ + FRAME_OFF(4)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(76)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1152)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1156)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1160)))
void __cdecl setup_picwnd_load_image(i32 param_1,i32 param_2)

{
  i8 frame_[FRAME_OFF(1168)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_48c);
  local_8 = 0;
  palette_init(&local_444);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  win_flush_pending_msgs();
  surface_load_gif_resource(&local_48c,setup_picwnd_image_id + 900,10,0xc0,(iptr)&local_444);
  win_flush_pending_msgs();
  surface_create((DibSurface *)&setup_picwnd_surface,param_1,param_2);
  gfx_copy_rect_same_pos((iptr)&local_48c,ADDR(0x6ab4b8, ((u8 *)&g.d_006ab4b8)),0,0,param_1,param_2);
  surface_release(&local_48c);
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_00559dbd */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00559dc9 */ { surface_dtor((DibSurface *)((iptr)&local_48c)); }
  return;
}
#undef local_48c
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00559ded auto */
void __thiscall setup_picwnd_reset_fields(C_004083b0_430 *this)

{
  this->field_2dc = 100;
  this->field_2d8 = this->field_2dc;
  this->field_2e0 = 1;
  this->field_2e4 = 0;
  return;
}

/* 00559e3c auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
C_004083b0_430 * __thiscall setup_picwnd_ctor(C_004083b0_430 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  dll_handle_init((DllHandle *)&this->field_2f8);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  this->vtable = (u32)&PTR_FUN_0061d6e0;
  setup_picwnd_reset_fields(this);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00559ed4 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CMiniFrameWnd::~CMiniFrameWnd(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall setup_picwnd_dtor(C_004083b0_430 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6e0;
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  setup_picwnd_reset_fields(this);
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_00559f30 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x2f8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00559f3f */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00559f60 auto */
void __thiscall setup_picwnd_blit_image_rect(C_004083b0_12c *this,int *param_1)

{
  i32 uVar1;
  i32 uVar2;
  
  uVar1 = rect_height((iptr)param_1);
  uVar2 = rect_width((iptr)param_1);
  gfx_copy_rect_xywh(ADDR(0x6ab4b8, ((u8 *)&g.d_006ab4b8)),(iptr)this,*param_1 - this->client_x,param_1[1] - this->client_y,
                     *param_1,param_1[1],uVar2,uVar1);
  return;
}

/* 00559fcf auto */
void __thiscall setup_picwnd_draw_image(C_004083b0_12c *this,iptr param_1)

{
  gfx_set_draw_target((iptr)this);
  text_set_surface((iptr)this);
  setup_picwnd_blit_image_rect(this,param_1);
  return;
}

/* 0055a00b auto */
void __thiscall
setup_picwnd_client_rect
          (SetupPicWndRectView *this,iptr param_1,int param_2,int param_3,iptr param_4,iptr param_5)

{
  rect_set_xywh(param_1,this->field_124 + param_2,this->field_128 + param_3,param_4,param_5);
  return;
}

/* 0055a051 auto */
void __thiscall setup_picwnd_redraw(C_004083b0_430 *this)

{
  frame_wnd_layout((FrameWindow *)this);
  setup_picwnd_load_image(this->field_2d8,this->field_2dc);
  setup_picwnd_client_rect
            ((SetupPicWndRectView *)this,(iptr)&this->field_2e8,0,0,this->field_2d8,this->field_2dc);
  gfx_set_draw_target((iptr)this);
  frame_wnd_draw_caption((FrameWindow *)this);
  setup_picwnd_draw_image((C_004083b0_12c *)this,(iptr)&this->field_2e8);
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
setup_picwnd_frame_rect(iptr param_1,i32 param_2,i32 param_3,int param_4,int param_5)

{
  rect_set_xywh(param_1,param_2,param_3,param_4 + 0x10 + sys_dlgframe_w2,
                     param_5 + 0x10 + sys_dlgframe_h2);
  return;
}

/* 0055a15e auto */
void __cdecl setup_picwnd_on_redraw(void)

{
  setup_picwnd_redraw((C_004083b0_430 *)&setup_picwnd);
  return;
}

/* 0055a178 auto */
void __cdecl setup_picwnd_on_restore(void)

{
  setup_picwnd_redraw((C_004083b0_430 *)&setup_picwnd);
  return;
}

/* 0055a192 auto */
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
int __cdecl setup_picwnd_position_coord(int param_1,int param_2)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
  case 5:
    param_1 = 0;
    break;
  case 1:
    param_1 = ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1;
    break;
  case 2:
    iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
    param_1 = (iVar1 - (param_2 + 0x10)) / 2;
    break;
  case 3:
    iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
    param_1 = ((iVar1 - (param_2 + 0x10)) -
              ((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3)) - 1;
    break;
  case 4:
    iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
    param_1 = iVar1 - (param_2 + 0x10);
    if (param_1 < 0) {
      param_1 = 0;
    }
    break;
  case 6:
    param_1 = ((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1;
    break;
  case 7:
    iVar1 = wnd_client_height((WndBase *)&main_frame_wnd);
    param_1 = (iVar1 - (param_2 + 0x10)) / 2;
    break;
  case 8:
    iVar1 = wnd_client_height((WndBase *)&main_frame_wnd);
    param_1 = ((iVar1 - (param_2 + 0x10)) -
              ((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3)) - 1;
    break;
  case 9:
    iVar1 = wnd_client_height((WndBase *)&main_frame_wnd);
    param_1 = iVar1 - (param_2 + 0x10);
    if (param_1 < 0) {
      param_1 = 0;
    }
  }
  return param_1;
}
#undef screen_height

/* 0055a329 auto */
i32 __cdecl setup_picwnd_image_size(int param_1,i32 param_2)

{
  i32 uVar1;
  
  switch(param_2) {
  case 1:
    if (param_1 == 0) {
      uVar1 = 0x178;
    }
    else {
      uVar1 = 0xe3;
    }
    break;
  case 2:
  case 3:
  case 4:
  case 5:
    if (param_1 == 0) {
      uVar1 = 0x247;
    }
    else {
      uVar1 = 0x101;
    }
    break;
  case 6:
  case 7:
  case 8:
  case 9:
    if (param_1 == 0) {
      uVar1 = 0x248;
    }
    else {
      uVar1 = 0x102;
    }
    break;
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
    if (param_1 == 0) {
      uVar1 = 0x196;
    }
    else {
      uVar1 = 0x102;
    }
    break;
  default:
    uVar1 = 100;
  }
  return uVar1;
}

/* 0055a41d auto */
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall
setup_picwnd_show(C_004083b0_430 *this,i32 param_1,i32 param_2,u32 param_3)

{
  u32 uVar1;
  i32 uVar2;
  i32 uVar3;
  int iVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->field_2e4 != 0) {
    this->field_2e0 = param_3;
    uVar1 = setup_picwnd_image_size(0,this->field_2e0);
    this->field_2d8 = uVar1;
    uVar1 = setup_picwnd_image_size(1,this->field_2e0);
    this->field_2dc = uVar1;
    uVar2 = setup_picwnd_position_coord(param_1,this->field_2d8);
    uVar3 = setup_picwnd_position_coord(param_2,this->field_2dc);
    setup_picwnd_frame_rect((iptr)&local_14,uVar2,uVar3,this->field_2d8,this->field_2dc);
    uVar6 = 8;
    uVar3 = 8;
    uVar2 = 0;
    iVar4 = rect_height((iptr)&local_14);
    iVar4 -= sys_dlgframe_h2;
    iVar5 = rect_width((iptr)&local_14);
    frame_wnd_create
              ((FrameWindow *)this,0,2,local_14,local_10,iVar5 - sys_dlgframe_w2,iVar4,uVar2,uVar3,
               uVar6);
    wnd_set_close_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x401005, setup_picwnd_on_close));
    wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x403544, setup_picwnd_on_redraw));
    wnd_set_restore_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x403b0c, setup_picwnd_on_restore));
    wnd_repaint((SurfaceWindow *)this);
    window_show((C_004083b0_4 *)this);
  }
  return;
}
#undef local_14
#undef local_10

/* 0055a567 auto */
void __thiscall setup_picwnd_close(C_004083b0_430 *this)

{
  if (this->field_2e4 != 0) {
    wnd_destroy_with_surface((DibSurface *)this);
    surface_release((DibSurface *)&setup_picwnd_surface);
    ui_flush_input();
  }
  return;
}

/* 0055a5e4 auto */
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
void __thiscall setup_picwnd_load_dll(C_004083b0_430 *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  FUN_005f22d0(local_84,s_civ2_intro_dll_00633a2c);
  iVar1 = file_resolve_path((iptr)local_84);
  if (iVar1 != 0) {
    dll_handle_load((DllHandle *)&this->field_2f8,(iptr)local_84);
    this->field_2e4 = 1;
  }
  return;
}
#undef local_84

/* 0055a64a auto */
void __thiscall setup_picwnd_free_dll(C_004083b0_430 *this)

{
  if (this->field_2e4 != 0) {
    dll_handle_free((DllHandle *)&this->field_2f8);
    this->field_2e4 = 0;
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
  city_window_bring_to_top((C_004083b0_4 *)&city_window);
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
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_calc_font_sizes(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  status_text_bottom = 0;
  local_8 = 2;
  local_10 = 2;
  status_panel_x = 0;
  status_panel_width = status_client_width;
  local_14 = status_client_height - 0x28;
  status_upper_panel_height = 0x28;
  if ((0xf4 < status_client_width) && (0x12e < local_14)) {
    local_10 = 4;
    status_upper_panel_height = 0x50;
    local_14 = status_client_height - 0x50;
  }
  if (((local_10 == 2) && (0xb9 < status_client_width)) && (0xed < local_14)) {
    local_10 = 3;
    status_upper_panel_height += (status_upper_panel_height >> 1);
    local_14 -= 0x14;
  }
  status_panel_gap = 8;
  if (local_14 < 0xb2) {
    if (local_14 < 0x10) {
      status_lower_panel_height = 0;
    }
    else {
      status_lower_panel_height = local_14 - 8;
    }
  }
  else {
    status_lower_panel_height = local_14 - 8;
  }
  if ((local_10 == 4) && (0x128 < status_lower_panel_height)) {
    local_8 = 4;
  }
  if (((2 < local_10) && (local_8 == 2)) && (0xfe < status_lower_panel_height)) {
    local_8 = 3;
  }
  if (local_8 != status_font_scale) {
    status_font_scale = local_8;
    font_set_styled((GameFont *)&status_font,0,local_8 * 0xb >> 1,1);
  }
  if (local_10 != status_info_font_scale) {
    status_info_font_scale = local_10;
    font_set_styled((GameFont *)&status_info_font,0,(int)(local_10 * 0xb) >> 1,1);
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
#undef local_14
#undef local_10
#undef local_8

/* 00568e86 auto */
#define status_indicator_rect (*(i32 *)((u8 *)&g.d_006abf24))
#define status_lower_panel_height (*(int *)((u8 *)&g.d_006abc5c))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_draw_civ_color(iptr civ)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((status_wnd_hidden == '\0') && (status_lower_panel_height != 0)) {
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    local_c = status_client_right;
    local_8 = status_client_bottom;
    local_14 = status_client_right - 8;
    local_10 = status_client_bottom - 6;
    uVar1 = civ_color_primary(civ);
    gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&local_14,uVar1);
    win_flush_pending_msgs();
    wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&local_14);
    surface_reset_clip((DibSurface *)&status_window);
    win_flush_pending_msgs();
  }
  return;
}
#undef status_indicator_rect
#undef status_lower_panel_height
#undef status_wnd_hidden
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00568f43 auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define status_end_turn_visible (*(char *)((u8 *)&g.d_00633dfc))
#define status_wnd_hidden (*(char *)((u8 *)&g.d_00633e00))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
void __cdecl status_draw_end_of_turn(int param_1)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  int iVar4;
  int iVar5;
  i32 uVar6;
  i32 uVar7;
  
  if ((((status_wnd_hidden == '\0') && (unit_blink_active != '\0')) && (status_end_turn_visible != '\0')) &&
     (((game.field_06 & 1) != 0 && (iVar1 = rect_height(ADDR(0x6abc18, ((u8 *)&g.d_006abc18))), 0 < iVar1)))) {
    text_set_surface(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
    uVar7 = 0;
    uVar6 = 0;
    uVar2 = rect_height(ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
    uVar3 = rect_width(ADDR(0x6abc18, ((u8 *)&g.d_006abc18)));
    gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_end_turn_rect,status_end_turn_rect_top,uVar3,uVar2,uVar6,uVar7);
    text_set_colors((-(uint)((moving_units_mode == 0) == (bool)status_end_turn_blink_phase) & 0xf) + 0x1a,10,1,0);
    text_set_font(ADDR(0x6abc50, ((u8 *)&g.d_006abc50)));
    iVar4 = font_text_width((GameFont *)&status_font,ADDR(0x633e10, ((u8 *)&g.d_00633e10)));
    iVar4 = status_end_turn_rect + iVar4;
    iVar5 = font_cached_height((GameFont *)&status_font);
    iVar1 = status_end_turn_rect_top;
    text_clear();
    text_append_label(0x1b);
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar4,iVar1);
    text_clear();
    text_append_space();
    text_append_lparen();
    text_append_label(0x1c);
    text_append_rparen();
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar4,iVar1 + iVar5 - 1);
    win_flush_pending_msgs();
    if (param_1 != 0) {
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
i32 __cdecl status_draw_cursor_loc(iptr x,iptr y,i32 param_3,iptr param_4)

{
  iptr iVar1;
  i32 uVar2;
  
  text_clear();
  text_append_label(0xb);
  text_append_colon();
  text_append_lparen();
  text_append_int(x);
  text_append_comma();
  text_append_int(y);
  text_append_rparen();
  text_append_space();
  iVar1 = tile_landmass(x,y);
  text_append_int(iVar1);
  uVar2 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_3,param_4);
  return uVar2;
}

/* 005691a1 auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl status_append_unit_orders(iptr unit)

{
  iptr iVar1;
  uint uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = (iptr)units[unit].orders;
  if ((iVar1 == -1) || (0xf < iVar1)) {
    text_append_label(0x1a);
  }
  else if (iVar1 == 5) {
    uVar1 = tile_improvements((int)units[unit].x,(int)units[unit].y);
    if ((uVar1 & 0x10) == 0) {
      text_append_string_id(order_names[5].name);
    }
    else {
      text_append_label(0xa0);
    }
  }
  else {
    text_append_string_id(order_names[iVar1].name);
    if (iVar1 == 0xb) {
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
#define local_58 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_54 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(80)))
void __cdecl status_draw_info(int param_1)

{
  short sVar1;
  i32 uVar2;
  i32 uVar3;
  int iVar4;
  uint uVar5;
  i32 uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    gfx_set_draw_target(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    uVar7 = 0;
    uVar6 = 0;
    uVar2 = rect_height(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    uVar3 = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_upper_rect,status_upper_rect_top,uVar3,uVar2,uVar6,uVar7);
  }
  text_set_surface(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
  text_set_font(ADDR(0x6abf98, ((u8 *)&g.d_006abf98)));
  local_28 = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  if (1 < game.field_2c) {
    iVar4 = int_clamp(game.field_2c * 3,0,100);
    local_20 = (iVar4 * local_28) / 100;
    if (local_20 != 0) {
      gfx_draw_hline(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),status_upper_rect,status_upper_rect + local_20 - 1,status_upper_rect_top,0x55);
      gfx_draw_hline(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),status_upper_rect,status_upper_rect + local_20 - 1,status_upper_rect_top + 1,0x55);
    }
  }
  local_c = font_text_width((GameFont *)&status_info_font,ADDR(0x633e14, ((u8 *)&g.d_00633e14)));
  local_c = status_upper_rect + local_c;
  local_8 = font_cached_height((GameFont *)&status_info_font);
  local_8--;
  local_34 = status_upper_rect_top;
  local_30 = local_c;
  local_2c = status_info_font_scale * 4 - 8;
  surface_set_clip((DibSurface *)&status_window,ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  text_set_colors(0x10,0x21,1,1);
  text_clear();
  text_append_population(human_civ,0xffffffff);
  text_append_space();
  text_append_label(0x1e);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_30,local_34);
  local_30 = local_c;
  local_34 += local_8;
  text_clear();
  text_append_year((int)game.year);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_30,local_34);
  local_30 = local_c;
  local_34 += local_8;
  text_clear();
  text_append_gold(civs[human_civ].gold);
  text_append_space();
  text_append_space();
  text_append_int((uint)civs[human_civ].tax_rate);
  FUN_005f22e0(&text_buffer,&status_tax_sep_str);
  text_append_int(10 - ((uint)civs[human_civ].science_rate +
                          (uint)civs[human_civ].tax_rate));
  FUN_005f22e0(&text_buffer,&status_lux_sep_str);
  text_append_int((uint)civs[human_civ].science_rate);
  local_30 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_30,local_34);
  local_24 = gfx_zoom_scale(0xe,local_2c);
  local_1c = local_24;
  iVar4 = rect_height(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  local_18 = ((iVar4 >> 1) + status_upper_rect_top) - (local_24 >> 1);
  uVar5 = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
  if ((int)(uVar5 & 0xfffffffe) < 200) {
    local_58 = 100;
  }
  else {
    local_58 = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    local_58 = local_58 >> 1;
  }
  local_14 = status_upper_rect + local_58;
  gfx_set_zoom_scale(local_2c);
  sVar1 = civs[human_civ].research_progress;
  local_10 = civ_research_cost(human_civ);
  local_10 = ((int)sVar1 << 2) / local_10;
  local_10 = int_clamp(local_10,0,3);
  sprite_draw
            ((Sprite *)(&research_flask_sprites + local_10 * 0x3c),(iptr)local_44,ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),local_14,
             local_18);
  local_14 += (local_1c * 3) / 2;
  if (game.warming_counter != '\0') {
    local_10 = int_clamp((int)game.warming_counter >> 2,0,3);
    sprite_draw
              ((Sprite *)(&global_warming_sprites + local_10 * 0x3c),(iptr)local_54,ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),local_14,
               local_18);
  }
  gfx_reset_zoom_scale();
  surface_reset_clip((DibSurface *)&status_window);
  if (param_1 != 0) {
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
#undef local_58
#undef local_54
#undef local_44
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
#define local_54 (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(28)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(36)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(48)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(68)))
void __cdecl status_draw_unit_panel(void)

{
  u8 uVar1;
  u8 uVar2;
  bool bVar3;
  byte terrain;
  int iVar5;
  int iVar6;
  i32 uVar7;
  iptr iVar8;
  iptr iVar9;
  int iVar10;
  iptr iVar12;
  byte *pbVar13;
  iptr unit3;
  int iVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  status_draw_info(0);
  if (status_lower_panel_height != 0) {
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    text_set_font(ADDR(0x6abc50, ((u8 *)&g.d_006abc50)));
    iVar5 = font_text_width((GameFont *)&status_font,ADDR(0x633e20, ((u8 *)&g.d_00633e20)));
    iVar5 = status_lower_rect + iVar5;
    iVar6 = font_cached_height((GameFont *)&status_font);
    iVar14 = status_lower_rect_top;
    iVar6--;
    text_clear();
    text_append_label((moving_units_mode == 0) + 9);
    text_set_colors(0x29,10,1,0);
    uVar7 = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),status_lower_rect,iVar14,uVar7);
    text_set_colors(0x10,0x21,1,1);
    local_54 = iVar14 + iVar6 + (iVar6 >> 1);
    iVar14 = status_font_scale * 3;
    local_3c = 0;
    if (((moving_units_mode == 1) && (-1 < game.active_unit)) && (player_turn_active != '\0')) {
      local_3c = 1;
      unit2 = (iptr)game.active_unit;
      x2 = (iptr)units[unit2].x;
      y2 = (iptr)units[unit2].y;
      gfx_draw_unit(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),unit2,4,iVar5,local_54,iVar14 - 8,0);
      iVar8 = local_54 - 2;
      iVar9 = gfx_zoom_scale(0x40,iVar14 - 8);
      iVar15 = iVar5 + iVar9 + 2;
      iVar10 = gfx_zoom_scale(0x30,iVar14 - 8);
      local_54 = local_54 + iVar10 + 2;
      iVar10 = unit_max_moves(unit2);
      iVar10 -= (uint)units[unit2].moves_used;
      iVar18 = iVar10 % (int)(uint)cosmic.road_move_mult;
      uVar16 = (uint)cosmic.road_move_mult;
      text_clear();
      text_append_label(0xc);
      text_append_colon();
      text_append_int(iVar10 / (int)uVar16);
      if (iVar18 != 0) {
        text_append_space();
        text_append_int(iVar18);
        FUN_005f22e0(&text_buffer,&status_moves_frac_sep_str);
        text_append_int((uint)cosmic.road_move_mult);
      }
      if ('\0' < (char)unit_types[units[unit2].type].range) {
        text_append_space();
        text_append_lparen();
        uVar1 = unit_types[units[unit2].type].range;
        uVar2 = units[unit2].counter;
        iVar10 = unit_max_moves(unit2);
        text_append_int((int)(((int)(char)uVar1 - (int)(char)uVar2) * iVar10 -
                                (uint)units[unit2].moves_used) / (int)(uint)cosmic.road_move_mult
                          );
        text_append_rparen();
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar15,iVar8);
      text_clear();
      iVar12 = unit_home_city_name(unit2);
      text_append_str(iVar12);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar15,iVar8 + iVar6);
      text_clear();
      iVar12 = civ_get_adjective((int)units[unit2].owner);
      text_append_str(iVar12);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar15,iVar8 + iVar6 + iVar6);
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
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
    }
    else {
      x2 = (iptr)map_cursor_x;
      y2 = (iptr)map_cursor_y;
      unit2 = -1;
      status_draw_cursor_loc(x2,y2,iVar5,local_54);
    }
    local_54 += iVar6;
    iVar10 = map_in_bounds(x2,y2);
    if ((iVar10 == 0) ||
       ((game.reveal_map == '\0' &&
        (iVar10 = tile_visible_to(x2,y2,human_civ), iVar10 == 0)))) {
      text_clear();
      text_append_lparen();
      text_append_label(0xf5);
      text_append_rparen();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
      local_54 += iVar6;
    }
    else {
      terrain = tile_terrain(x2,y2);
      text_clear();
      text_append_lparen();
      text_append_string_id(terrain_types[terrain].name);
      pbVar13 = (byte *)tile_at(x2,y2);
      if ((*pbVar13 & 0x80) != 0) {
        text_append_comma();
        text_append_label(0x12);
      }
      text_append_rparen();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
      local_54 += iVar6;
      iVar10 = tile_resource(x2,y2);
      if (iVar10 != 0) {
        text_clear();
        text_append_lparen();
        text_append_string_id(terrain_types[iVar10 * 0xb + (uint)terrain].name);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
        local_54 += iVar6;
      }
      iVar10 = tile_has_hut(x2,y2);
      if (iVar10 != 0) {
        text_clear();
        text_append_lparen();
        text_append_label(0x1d);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
        local_54 += iVar6;
      }
      if ((game.reveal_map == '\0') && (human_civ != 0)) {
        pbVar13 = (byte *)known_at(x2,y2,human_civ);
        terrain = *pbVar13;
      }
      else {
        iVar10 = tile_at(x2,y2);
        terrain = *(byte *)(iVar10 + 1);
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
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
        local_54 += iVar6;
      }
      if ((terrain & 0x40) != 0) {
        text_clear();
        text_append_lparen();
        text_append_label((-(uint)((terrain & 2) == 0) & 0xffffffcd) + 0x61);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
        local_54 += iVar6;
      }
      if ((terrain & 0x80) != 0) {
        text_clear();
        text_append_lparen();
        text_append_label(0x2f);
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
        local_54 += iVar6;
      }
      local_54 += (iVar6 >> 1);
      if ((game.field_06 & 1) == 0) {
        local_34 = 1;
      }
      else {
        local_34 = 3;
      }
      unit3 = tile_first_unit(x2,y2);
      iVar10 = unit_stack_sum(unit3,2);
      for (unit = unit3; iVar15 = status_lower_rect_bottom, -1 < unit;
          unit = unit_next_in_stack(unit)) {
        if (unit2 != unit) {
          bVar3 = false;
          if ((units[unit].owner != human_civ) &&
             (((bVar3 = true, unit != unit3 ||
               (((1 << ((byte)human_civ & 0x1f) & (uint)units[unit3].visibility) == 0 &&
                ((int)units[unit3].owner != (human_civ & 0xffU))))) &&
              (game.reveal_map == '\0')))) break;
          if (iVar10 - 1 == local_3c) {
            local_34--;
          }
          iVar18 = gfx_zoom_scale(0x30,iVar14 - 8);
          if (iVar15 - (iVar18 + iVar6 * local_34 + 1) <= local_54) {
            text_clear();
            text_append_lparen();
            text_append_int(iVar10 - local_3c);
            text_append_space();
            text_append_label(0x18);
            text_append_space();
            text_append_label((-(uint)(iVar10 - local_3c == 1) & 99) + 0x19);
            text_append_rparen();
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5,local_54);
            local_54 += iVar6;
            break;
          }
          local_3c++;
          gfx_draw_unit(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),unit,4,iVar5,local_54,iVar14 - 8,0);
          iVar15 = local_54 - 2;
          iVar18 = gfx_zoom_scale(0x40,iVar14 - 8);
          iVar17 = iVar5 + iVar18 + 2;
          iVar18 = gfx_zoom_scale(0x30,iVar14 - 8);
          local_54 = local_54 + iVar18 + 2;
          if (bVar3) {
            text_clear();
            iVar12 = civ_get_adjective((int)units[unit].owner);
            text_append_str(iVar12);
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
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar17,iVar15);
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
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar17,iVar15 + iVar6);
            if (game.reveal_map != '\0') {
              text_clear();
              status_append_unit_orders(unit);
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar17,iVar15 + iVar6 + iVar6);
            }
          }
          else {
            text_clear();
            iVar12 = unit_home_city_name(unit);
            text_append_str(iVar12);
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
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar17,iVar15);
            text_clear();
            status_append_unit_orders(unit);
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar17,iVar15 + iVar6);
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
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar17,iVar15 + iVar6 + iVar6);
          }
        }
      }
    }
    status_text_bottom = local_54;
    if ((game.field_06 & 1) == 0) {
      status_end_turn_visible = 0;
    }
    else {
      status_end_turn_rect = status_lower_rect;
      status_end_turn_rect_right = status_lower_rect_right;
      status_end_turn_rect_bottom = status_lower_rect_bottom;
      status_end_turn_rect_top = local_54;
      while (iVar14 = rect_height(ADDR(0x6abc18, ((u8 *)&g.d_006abc18))), iVar6 * 3 < iVar14) {
        status_end_turn_rect_top += iVar6;
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
#undef local_54
#undef unit
#undef local_3c
#undef y2
#undef local_34
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
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_redraw(int param_1)

{
  i32 uVar1;
  i32 uVar2;
  i32 uVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (status_wnd_hidden == '\0') {
    local_8 = status_text_bottom;
    gfx_set_draw_target(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)));
    uVar4 = 0;
    uVar3 = 0;
    uVar1 = rect_height(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    uVar2 = rect_width(ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
    gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_upper_rect,status_upper_rect_top,uVar2,uVar1,uVar3,uVar4);
    if (status_lower_panel_height != 0) {
      uVar4 = 0;
      uVar3 = 0;
      uVar1 = rect_height(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
      uVar2 = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
      gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x640990, ((u8 *)&g.d_00640990)),status_lower_rect,status_lower_rect_top,uVar2,uVar1,uVar3,uVar4);
    }
    status_calc_font_sizes();
    status_draw_unit_panel();
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)&status_window,ADDR(0x6abc28, ((u8 *)&g.d_006abc28)));
      local_18 = status_lower_rect;
      local_14 = status_lower_rect_top;
      local_10 = status_lower_rect_right;
      local_c = status_text_bottom;
      if (status_text_bottom <= local_8) {
        local_c = local_8;
      }
      wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&local_18);
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
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

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
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl status_wnd_repaint(void)

{
  i32 uVar1;
  i32 uVar2;
  int iVar3;
  i32 uVar4;
  i32 uVar5;
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
      rect_set((iptr)&local_14,status_upper_rect,status_upper_rect_bottom,status_upper_rect_right,status_lower_rect_top);
      rect_inflate((iptr)&local_14,frame_bevel_width,0);
      local_24 = local_14;
      local_20 = local_10;
      local_1c = local_c;
      local_18 = local_8;
      rect_deflate((iptr)&local_24,0,frame_bevel_width);
      uVar5 = 0;
      uVar4 = 0;
      uVar1 = rect_height((iptr)&local_24);
      uVar2 = rect_width((iptr)&local_24);
      gfx_tile_fill(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x647f18, ((u8 *)&g.d_00647f18)),local_24,local_20,uVar2,uVar1,uVar4,uVar5);
      local_8 = local_10 + frame_bevel_width;
      gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&local_14,frame_highlight_color);
      iVar3 = rect_height((iptr)&local_24);
      rect_offset((iptr)&local_14,0,frame_bevel_width + iVar3);
      gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&local_14,frame_shadow_color);
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
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0056a98b auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
void __cdecl status_wnd_on_click(void)

{
  if (city_turn_processing == 0) {
    if ((game.field_06 & 1) == 0) {
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
  i32 uVar1;
  int iVar2;
  iptr iVar3;
  int iVar4;
  
  uVar1 = minimap_wnd_rect;
  iVar2 = rect_height(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  iVar2 = minimap_wnd_rect_top + iVar2;
  iVar3 = rect_width(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  iVar4 = wnd_client_height((WndBase *)&main_frame_wnd);
  rect_set_xywh(ADDR(0x655334, ((u8 *)&g.d_00655334)),uVar1,iVar2,iVar3,(iVar4 - iVar2) - 1 + sys_dlgframe_h2);
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
  int iVar1;
  int iVar2;
  i32 uVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  i32 uVar9;
  
  status_wnd_hidden = 0;
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    status_calc_wnd_rect();
  }
  uVar9 = 0;
  uVar8 = 0;
  uVar7 = 6;
  iVar1 = rect_height(ADDR(0x655334, ((u8 *)&g.d_00655334)));
  iVar1 -= sys_dlgframe_h2;
  iVar2 = rect_width(ADDR(0x655334, ((u8 *)&g.d_00655334)));
  iVar2 -= sys_dlgframe_w2;
  uVar4 = 6;
  uVar5 = status_wnd_rect;
  uVar6 = status_wnd_rect_top;
  uVar3 = label_string(*(i32 *)(label_string_ids + 0x14));
  frame_wnd_create
            ((FrameWindow *)&status_window,uVar3,uVar4,uVar5,uVar6,iVar2,iVar1,uVar7,uVar8,uVar9);
  wnd_set_min_size((C_00408010_b8 *)&status_window_wnd,0x28,0x4c);
  wnd_set_minimize_handler((C_00408130 *)&status_wnd_events,ADDR(0x402914, status_wnd_on_minimize));
  wnd_set_restore_handler((C_00408130 *)&status_wnd_events,ADDR(0x403909, status_wnd_on_restore));
  wnd_set_close_handler((C_00408130 *)&status_wnd_events,ADDR(0x402671, status_wnd_on_close));
  wnd_set_icon((WndBase *)&status_window_wnd,1);
  wnd_set_lbuttonup_handler((C_00408130 *)&status_wnd_events,ADDR(0x401e06, status_wnd_on_click));
  wnd_set_rbuttonup_handler((C_00408130 *)&status_wnd_events,ADDR(0x401e06, status_wnd_on_click));
  wnd_set_keydown_handler((C_00408130 *)&status_wnd_events,ADDR(0x402cd4, map_window_key));
  wnd_set_char_handler((C_00408130 *)&status_wnd_events,ADDR(0x401e56, map_window_ascii));
  wnd_set_redraw_callback((SurfaceWindow *)&status_window,ADDR(0x401c30, status_wnd_repaint));
  wnd_set_size_handler((C_00408130 *)&status_wnd_events,ADDR(0x403ada, status_wnd_on_size));
  wnd_set_move_handler((C_00408130 *)&status_wnd_events,ADDR(0x402973, status_wnd_on_move));
  wnd_repaint((SurfaceWindow *)&status_window);
  if (game.multiplayer != 1) {
    window_show((C_004083b0_4 *)&status_window);
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
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl status_draw_timer_bar(int param_1,int param_2)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((status_timer_surface_init & 1) == 0) {
    status_timer_surface_init = status_timer_surface_init | 1;
    surface_ctor((DibSurface *)&status_timer_bg_surface);
    _atexit(status_timer_bg_surface_static_dtor);
  }
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  if (((status_wnd_hidden == '\0') && (status_lower_panel_height != 0)) &&
     ((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) != 0)) {
    surface_set_clip((DibSurface *)&status_window,ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    local_14 = status_indicator_rect;
    local_8 = status_client_bottom;
    local_c = status_client_right - 8;
    local_10 = status_client_bottom - 6;
    iVar1 = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
    if (iVar1 != status_timer_last_width) {
      status_timer_last_width = rect_width(ADDR(0x6abfa8, ((u8 *)&g.d_006abfa8)));
      status_timer_last_color = -1;
      status_timer_last_percent = -1;
      surface_alloc_dib8((DibSurface *)&status_timer_bg_surface,(iptr)&local_14);
      uVar2 = rect_height((iptr)&local_14);
      uVar3 = rect_width((iptr)&local_14);
      gfx_copy_rect_xywh(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),ADDR(0x6abf48, ((u8 *)&g.d_006abf48)),local_14,local_10,0,0,uVar3,uVar2);
    }
    if (((status_timer_last_color != param_2) || (iVar1 = _memcmp(&local_14,&status_timer_last_rect,0x10), iVar1 != 0))
       || (status_timer_last_percent != param_1)) {
      status_timer_last_color = param_2;
      status_timer_last_rect = local_14;
      status_timer_last_rect_top = local_10;
      status_timer_last_rect_right = local_c;
      status_timer_last_rect_bottom = local_8;
      status_timer_last_percent = param_1;
      uVar2 = rect_height((iptr)&local_14);
      uVar3 = rect_width((iptr)&local_14);
      gfx_copy_rect_xywh(ADDR(0x6abf48, ((u8 *)&g.d_006abf48)),ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),0,0,local_14,local_10,uVar3,uVar2);
      wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&local_14);
      if (-1 < param_2) {
        iVar1 = rect_width((iptr)&local_14);
        local_c = local_14 + (param_1 * iVar1) / 100;
        gfx_fill_rect(ADDR(0x6abc68, ((u8 *)&g.d_006abc68)),(iptr)&local_14,param_2);
        win_flush_pending_msgs();
        wnd_blit_surface_rect((DibSurface *)&status_window,(iptr)&local_14);
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
#undef local_14
#undef local_10
#undef local_c
#undef local_8

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
#define _DAT_006acbb4 (*(i32 *)((u8 *)&g.d_006acbb4))
#define local_708 (*(i8 (*)[708])(frame_ + FRAME_OFF(0)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(708)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1792)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl main_frame_create(void)

{
  int iVar1;
  iptr iVar2;
  i32 uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(1800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_444);
  local_8 = 0;
  text_clear();
  text_append_label(2);
  WritePrivateProfileStringA
            (s_Civilization_Gold_00634734,s_Window_Name_00634728,&text_buffer,s_CIV_INI_00634720);
  wnd_create_with_cmd_proc((WndBase *)&main_frame_wnd,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x7c,0,0,600,400,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  iVar1 = file_require_cdrom(ADDR(0x634748, ((u8 *)&g.d_00634748)));
  if (iVar1 != 0) {
    uVar3 = 8;
    uVar2 = 0x10000;
    iVar2 = wnd_get_window((WndBase *)&main_frame_wnd);
    snd_wave_open(*(i32 *)(iVar2 + 4),uVar2,uVar3);
    menu_build_main();
    surface_load_gif_resource((DibSurface *)&main_frame_bg_surface,0x5a,10,0xc0,(iptr)&local_444);
    wnd_set_bg_surface((WndBase *)&main_frame_wnd,ADDR(0x6acb68, ((u8 *)&g.d_006acb68)));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_set_icon((WndBase *)&main_frame_wnd,1);
    main_frame_nonclient_width = wnd_frame_width((WndBase *)&main_frame_wnd);
    _DAT_006acbb4 = wnd_nonclient_height((WndBase *)&main_frame_wnd);
    wnd_maximize((WndBase *)&main_frame_wnd);
    palette_get_rgb((GamePalette *)&game_palette,(iptr)local_708,10,0xec);
    intro_play_opening_video();
    palette_set_rgb((GamePalette *)&game_palette,10,0xec,(iptr)local_708);
    palette_commit_range((GamePalette *)&game_palette,10,0xec);
    wnd_set_close_handler((C_00408130 *)&main_frame_base_wnd,ADDR(0x402446, main_frame_on_close));
    wnd_set_keydown_handler((C_00408130 *)&main_frame_base_wnd,ADDR(0x402cd4, map_window_key));
    wnd_set_char_handler((C_00408130 *)&main_frame_base_wnd,ADDR(0x401e56, map_window_ascii));
    wnd_set_bg_color((WndBase *)&main_frame_wnd,0x9e);
    wnd_flush_paint();
    main_frame_created = 1;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00589c54 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  }
  else {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00589c54 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  }
  return (uint)(iVar1 != 0);
}
#undef main_frame_created
#undef main_frame_nonclient_width
#undef text_buffer
#undef _DAT_006acbb4
#undef local_708
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

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
#define local_310 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl setup_pbem_game(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  for (local_310 = 0; local_310 < 8; local_310++) {
    *(i16 *)(&civ_intro_shown + local_310 * 2) = 0;
    (&civ_email_addresses)[local_310 * 0x20] = 0;
  }
  mp_turn_time_limit_ms = 0;
  game.multiplayer = 2;
LAB_005ae610:
  setup_dialog_pos_state = 3;
  setup_show_side_picture(0xffffffff,0);
  dlg_load_game_section(&local_30c,ADDR(0x635dcc, ((u8 *)&g.d_00635dcc)),1);
  dialog_set_default_choice((DialogOptionList *)&local_30c,(int)prefs_pbem_menu_choice);
  FUN_005f22d0(&scenario_dir_path,&game_home_dir);
  iVar1 = -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1);
  uVar2 = setup_next_dialog_x(0);
  dialog_set_position((C_0040bc40_28 *)&local_30c,uVar2,iVar1);
  iVar1 = dlg_show_modal(&local_30c,0);
  snd_play_effect(0x6a,0,0,0);
  setup_picwnd_close((C_004083b0_430 *)&setup_picwnd);
  if (iVar1 < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_005aebef */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    uVar2 = 1;
LAB_005aec05:
    return uVar2;
  }
  prefs_pbem_menu_choice = (short)iVar1;
  if ((-1 < iVar1) && (iVar1 < 3)) {
    __chdir(&game_home_dir);
    rules_load(1);
  }
  scenario_events_loaded = 0;
  switch(iVar1) {
  case 0:
    iVar1 = setup_choose_map_size();
    if (iVar1 != 0) goto LAB_005ae610;
    local_18 = 0;
    iVar1 = _rand();
    mapgen_land_mass = iVar1 % 3 - 1;
    mapgen_land_form = 0;
    iVar1 = _rand();
    if (iVar1 % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    iVar1 = _rand();
    mapgen_temperature = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_climate = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_age = iVar1 % 3 - 1;
    iVar1 = setup_choose_game_options(local_18,2);
    break;
  case 1:
    iVar1 = map_load_dialog();
    if (iVar1 != 0) goto LAB_005ae610;
    local_18 = 1;
    if (map.flat != 0) {
      local_18 = 2;
    }
    iVar1 = _rand();
    mapgen_land_mass = iVar1 % 3 - 1;
    mapgen_land_form = 0;
    iVar1 = _rand();
    if (iVar1 % 3 == 0) {
      mapgen_land_form = mapgen_land_mass;
    }
    iVar1 = _rand();
    mapgen_temperature = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_climate = iVar1 % 3 - 1;
    iVar1 = _rand();
    mapgen_age = iVar1 % 3 - 1;
    iVar1 = setup_choose_game_options(local_18,2);
    break;
  case 2:
    iVar1 = setup_choose_map_size();
    if (iVar1 != 0) goto LAB_005ae610;
    local_18 = 0;
    iVar1 = setup_custom_world();
    if (iVar1 != 0) goto LAB_005ae610;
    iVar1 = setup_choose_game_options(local_18,2);
    break;
  case 3:
    event_dont_play_wonders = 0;
    iVar1 = scenario_start_dialog(2);
    if (iVar1 == 0) {
      if (event_dont_play_wonders != 0) {
        game.game_options = game.game_options & 0xfffeffff;
      }
      game.multiplayer = 2;
      local_14 = setup_choose_hotseat_players();
      if (local_14 == 0) {
        FUN_005f22d0(&scenario_dir_path,&game_home_dir);
      }
      else {
        iVar1 = scenario_pick_human_civs(local_14);
        if (iVar1 == 0) {
          prefs_save_civ2dat();
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_005aebef */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
          uVar2 = 0;
          goto LAB_005aec05;
        }
        FUN_005f22d0(&scenario_dir_path,&game_home_dir);
      }
    }
    else {
      FUN_005f22d0(&scenario_dir_path,&game_home_dir);
    }
    goto LAB_005ae610;
  case 4:
    event_dont_play_wonders = 0;
    iVar1 = game_load_dialog(0,2,1);
    if (iVar1 == 0) {
      if (game.multiplayer != 2) goto code_r0x005aea27;
      prefs_save_civ2dat();
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_005aebef */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar2 = 0;
      goto LAB_005aec05;
    }
    if (event_dont_play_wonders != 0) {
      game.game_options = game.game_options & 0xfffeffff;
    }
    goto LAB_005ae610;
  default:
    goto switchD_005aea9a_default;
  }
  if (iVar1 == 0) {
switchD_005aea9a_default:
    game.civs_alive = '\0';
    game.human_players = '\0';
    local_14 = setup_choose_hotseat_players();
    if (local_14 != 0) {
      leaders_reset_custom_names();
      for (local_310 = 0; local_310 < local_14; local_310++) {
        while (iVar1 = setup_choose_tribe(local_310,2,0), iVar1 != 0) {
          local_310--;
          if (local_310 < 0) goto switchD_005aea9a_default;
        }
      }
      setup_choose_opponents(local_14);
      prefs_save_civ2dat();
      rules_load_advances(1);
      rules_load_units(1);
      rules_load_improvements(1);
      snd_menu_end();
      map_generate(local_18);
      game_init_new();
      if (setup_accelerated_start != 0) {
        game_accelerated_start(setup_accelerated_start - 1);
      }
      game.multiplayer = 2;
      if (turn_resume_civ != '\0') {
        game.player_civ = turn_resume_civ;
        human_civ = (iptr)turn_resume_civ;
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_005aebef */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar2 = 0;
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
#undef local_310
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005d1f50 auto */
#define local_18 (*(TimerManager * *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
i32 __cdecl game_timer_create(iptr param_1,i32 param_2,i32 param_3)

{
  TimerManagerCtorView *this;
  i32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (game_timer_mgr == (TimerManager *)0x0) {
    this = operator_new(0x90);
    local_8 = 0;
    if (this == (TimerManagerCtorView *)0x0) {
      local_18 = (TimerManager *)0x0;
    }
    else {
      local_18 = (TimerManager *)timer_mgr_ctor(this);
    }
    game_timer_mgr = local_18;
  }
  local_8 = 0xffffffff;
  uVar1 = timer_mgr_add(game_timer_mgr,param_1,param_2,param_3);
  return uVar1;
}
#undef local_18
#undef local_10
#undef puStack_c
#undef local_8

/* 005d2004 auto */
void __cdecl game_timer_destroy(iptr param_1)

{
  if (game_timer_mgr == (TimerManager *)0x0) {
    dbg_log(ADDR(0x6382d4, ((u8 *)&g.d_006382d4)));
  }
  else {
    game_timer_kill_slot(game_timer_mgr,param_1);
  }
  return;
}

/* 005d2042 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
iptr __thiscall
timer_mgr_add(TimerManager *this,u32 param_1,i32 param_2,u32 param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  while ((local_8 < 0x11 && (this[local_8 + 1].field_0 != 0))) {
    local_8++;
  }
  if (local_8 < 0x11) {
    iVar1 = timer_wnd_start_slot(this->timer_hwnd,param_2,local_8);
    if (iVar1 == 0) {
      local_8 = 0;
    }
    else {
      this[local_8 + 1].field_0 = param_1;
      this[local_8 + 0x12].field_0 = param_3;
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
#undef local_8

/* 005d20e6 auto */
void __thiscall game_timer_kill_slot(TimerManager *this,iptr param_1)

{
  this[param_1 + 1].field_0 = 0;
  timer_wnd_kill_slot(this->timer_hwnd,param_1);
  return;
}

/* 005d211e auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
TimerManagerCtorView * __thiscall timer_mgr_ctor(TimerManagerCtorView *this)

{
  u8 *puVar1;
  u32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 1; local_8 < 0x11; local_8++) {
    puVar1 = this->pad_4 + local_8 * 4;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_4 + local_8 * 4 + 0x44;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  uVar2 = timer_wnd_create((iptr)this);
  this->timer_wnd = uVar2;
  return this;
}
#undef local_8

/* 005d2182 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall timer_mgr_dtor(TimerManager *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    if (this[local_8 + 1].field_0 != 0) {
      game_timer_kill_slot(this,local_8);
    }
  }
  timer_wnd_destroy(this->timer_hwnd);
  return;
}
#undef local_8

/* 005d41e0 auto */
uint __cdecl timer_ticks_60hz(void)

{
  DWORD DVar1;
  
  DVar1 = GetTickCount();
  return (DVar1 * 6) / 100;
}

/* 005d4204 auto */
void __cdecl timer_busy_wait_ticks(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = timer_ticks_60hz();
  while( true ) {
    iVar2 = timer_ticks_60hz();
    if (iVar1 + param_1 <= iVar2) break;
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
#define local_8 (*(HWND *)(frame_ + FRAME_OFF(0)))
HWND __cdecl timer_wnd_create(iptr param_1)

{
  MMRESULT uTimerID;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (HWND)0x0;
  timerdll_module = LoadLibraryA(s_timerdll_dll_006383c0);
  if (timerdll_module == (HMODULE)0x0) {
    local_8 = CreateWindowExA(0,s_MSMrTimerClass_006384a4,s_MrTimer_0063849c,0xcf0000,-0x80000000,
                              -0x80000000,-0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,app_hinstance,
                              (LPVOID)0x0);
    if (local_8 != (HWND)0x0) {
      SetWindowLongA(local_8,0,param_1);
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
      local_8 = CreateWindowExA(0,s_MSMrTimerClass_00638458,s_MrTimer_00638450,0xcf0000,-0x80000000,
                                -0x80000000,-0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,
                                app_hinstance,(LPVOID)0x0);
      if (local_8 == (HWND)0x0) {
        err_report((ErrorContext *)&err_report_ctx,10,ADDR(0x638484, ((u8 *)&g.d_00638484)),ADDR(0x638468, ((u8 *)&g.d_00638468)),0x71);
        FreeLibrary(timerdll_module);
      }
      else {
        timeBeginPeriod(5);
        SetWindowLongA(local_8,0,param_1);
        uTimerID = timeSetEvent(100,5,timerdll_timer_callback,(DWORD_PTR)local_8,1);
        if (uTimerID == 0) {
          timer_mm_available = 0;
        }
        else {
          timeKillEvent(uTimerID);
        }
      }
    }
  }
  return local_8;
}
#undef app_hinstance
#undef timer_mm_available
#undef timerdll_get_timer_id
#undef timerdll_reset_timer_notified
#undef timerdll_set_timer_id
#undef timerdll_timer_callback
#undef local_8

/* 005d447c auto */
#define timerdll_timer_callback (*(i32 *)((u8 *)&g.d_006e4808))
void __cdecl timer_wnd_destroy(HWND param_1)

{
  if (param_1 != (HWND)0x0) {
    timeEndPeriod(5);
    DestroyWindow(param_1);
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
i32 __cdecl timer_wnd_start_slot(HWND param_1,UINT param_2,iptr param_3)

{
  MMRESULT MVar1;
  i32 uVar2;
  UINT_PTR UVar3;
  
  if (timer_mm_available == 0) {
    if (timer_alt_kind_request == 0) {
      UVar3 = SetTimer(param_1,param_3,param_2,(TIMERPROC)0x0);
      if (UVar3 == 0) {
        err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x638530, ((u8 *)&g.d_00638530)),ADDR(0x638514, ((u8 *)&g.d_00638514)),0xc3);
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      MVar1 = timeSetEvent(param_2,5,timerdll_timer_callback,(DWORD_PTR)param_1,1);
      if (MVar1 == 0) {
        err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x638560, ((u8 *)&g.d_00638560)),ADDR(0x638544, ((u8 *)&g.d_00638544)),0xd7);
        uVar2 = 0;
      }
      else {
        (*timerdll_set_timer_id)(param_3,MVar1);
        uVar2 = 1;
      }
    }
  }
  else if (timer_alt_kind_request == 0) {
    MVar1 = timeSetEvent(param_2,5,timerdll_timer_callback,(DWORD_PTR)param_1,1);
    if (MVar1 == 0) {
      err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x6384d0, ((u8 *)&g.d_006384d0)),ADDR(0x6384b4, ((u8 *)&g.d_006384b4)),0xa8);
      uVar2 = 0;
    }
    else {
      (*timerdll_set_timer_id)(param_3,MVar1);
      uVar2 = 1;
    }
  }
  else {
    UVar3 = SetTimer(param_1,param_3,param_2,(TIMERPROC)0x0);
    if (UVar3 == 0) {
      err_report((ErrorContext *)&err_report_ctx,0xb,ADDR(0x638500, ((u8 *)&g.d_00638500)),ADDR(0x6384e4, ((u8 *)&g.d_006384e4)),0xb4);
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
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
void __cdecl timer_wnd_kill_slot(HWND param_1,iptr param_2)

{
  UINT UVar1;
  
  if (timer_mm_available == 0) {
    if (timer_alt_kind_request == 0) {
      KillTimer(param_1,param_2);
    }
    else {
      UVar1 = (*timerdll_get_timer_id)(param_2);
      timeKillEvent(UVar1);
      (*timerdll_set_timer_id)(param_2,0);
    }
  }
  else if (timer_alt_kind_request == 0) {
    UVar1 = (*timerdll_get_timer_id)(param_2);
    timeKillEvent(UVar1);
    (*timerdll_set_timer_id)(param_2,0);
  }
  else {
    KillTimer(param_1,param_2);
  }
  return;
}
#undef timer_alt_kind_request
#undef timer_mm_available
#undef timerdll_get_timer_id
#undef timerdll_set_timer_id

/* 005d4700 auto */
#define timerdll_reset_timer_notified (*(code * *)((u8 *)&g.d_006e480c))
LRESULT __stdcall timer_wnd_proc(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  TimerManager *this;
  LRESULT LVar1;
  
  this = (TimerManager *)GetWindowLongA(param_1,0);
  if (this == (TimerManager *)0x0) {
    LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  else {
    if (param_2 == 0x113) {
      game_timer_fire_slot(this,param_3);
    }
    else {
      if (param_2 != 0x52c) {
        LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
        return LVar1;
      }
      game_timer_fire_slot(this,param_3);
      (*timerdll_reset_timer_notified)(param_3);
    }
    LVar1 = 0;
  }
  return LVar1;
}
#undef timerdll_reset_timer_notified

/* 005d47d0 auto */
void __thiscall game_timer_fire_slot(TimerManager *this,iptr param_1)

{
  if ((this[param_1 + 1].field_0 != 0) && (this[param_1 + 0x12].field_0 != 0)) {
    if (0 < (int)this[param_1 + 0x12].field_0) {
      this[param_1 + 0x12].field_0--;
    }
    (*(code *)this[param_1 + 1].field_0)(param_1,this[param_1 + 0x12].field_0);
    if (this[param_1 + 0x12].field_0 == 0) {
      game_timer_kill_slot(this,param_1);
    }
  }
  return;
}

/* 005dbb20 auto */
#define app_hinstance (*(i32 *)((u8 *)&g.d_006e4ff0))
#define app_prev_instance (*(i32 *)((u8 *)&g.d_006e4fec))
i32 __cdecl app_startup(i32 param_1,i32 param_2)

{
  app_hinstance = param_1;
  app_prev_instance = param_2;
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
  time_t tVar1;
  
  if (app_prev_instance == 0) {
    app_register_wnd_classes();
  }
  snd_system_init();
  app_init_hook_nop();
  tVar1 = _time((time_t *)0x0);
  FUN_005f2260((int)tVar1);
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
#define local_2c (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
void __cdecl app_register_wnd_classes(void)

{
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_2c.style = 0x28;
  local_2c.lpfnWndProc = wnd_base_wndproc;
  local_2c.cbClsExtra = 0;
  local_2c.cbWndExtra = 0x14;
  local_2c.hInstance = app_hinstance;
  local_2c.hIcon = (HICON)0x0;
  local_2c.hCursor = (HCURSOR)0x0;
  local_2c.hbrBackground = (HBRUSH)0x0;
  local_2c.lpszMenuName = (LPCSTR)0x0;
  local_2c.lpszClassName = s_MSWindowClass_00638810;
  RegisterClassA(&local_2c);
  local_2c.style = 0x28;
  local_2c.lpfnWndProc = moviewnd_wndproc;
  local_2c.cbClsExtra = 0;
  local_2c.cbWndExtra = 0x14;
  local_2c.hInstance = app_hinstance;
  local_2c.hIcon = (HICON)0x0;
  local_2c.hCursor = (HCURSOR)0x0;
  local_2c.hbrBackground = (HBRUSH)0x0;
  local_2c.lpszMenuName = (LPCSTR)0x0;
  local_2c.lpszClassName = s_MSMovieClass_00638820;
  RegisterClassA(&local_2c);
  local_2c.style = 0x88;
  local_2c.lpfnWndProc = ctrl_default_wndproc;
  local_2c.cbClsExtra = 0;
  local_2c.cbWndExtra = 0x10;
  local_2c.hInstance = app_hinstance;
  local_2c.hIcon = (HICON)0x0;
  local_2c.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_2c.hbrBackground = (HBRUSH)0x0;
  local_2c.lpszMenuName = (LPCSTR)0x0;
  local_2c.lpszClassName = s_MSControlClass_00638830;
  RegisterClassA(&local_2c);
  local_2c.style = 0;
  local_2c.lpfnWndProc = timer_wnd_proc;
  local_2c.cbClsExtra = 0;
  local_2c.cbWndExtra = 4;
  local_2c.hInstance = app_hinstance;
  local_2c.hIcon = (HICON)0x0;
  local_2c.hCursor = (HCURSOR)0x0;
  local_2c.hbrBackground = (HBRUSH)0x0;
  local_2c.lpszMenuName = (LPCSTR)0x0;
  local_2c.lpszClassName = s_MSMrTimerClass_00638840;
  RegisterClassA(&local_2c);
  return;
}
#undef app_hinstance
#undef local_2c

/* 005dbe88: written by hand in src/game/retvals.c */

/* 005dcac0 auto */
TimerManager * __thiscall timer_mgr_scalar_dtor(TimerManager *this,uint param_1)

{
  timer_mgr_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
