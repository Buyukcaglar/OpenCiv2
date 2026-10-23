/* The game, units: movement, orders, combat, pathfinding, diplomats and spies: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 004131c0 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
#define unit_blink_skip_tick (*(char *)((u8 *)&g.d_0062805c))
void __cdecl unit_blink_timer_tick(void)

{
  if (2 < game.multiplayer) {
    net_process_messages((NetSession *)&net_session,1,1);
  }
  if (((unit_blink_skip_tick == '\0') && (player_turn_active != '\0')) && (game_loop_active != '\0')) {
    if (unit_blink_active != '\0') {
      unit_blink_phase = unit_blink_phase == '\0';
      mapviews_redraw_cursor();
    }
  }
  else {
    unit_blink_skip_tick = '\0';
  }
  return;
}
#undef game_loop_active
#undef player_turn_active
#undef unit_blink_active
#undef unit_blink_phase
#undef unit_blink_skip_tick

/* 0042738c auto */
void __cdecl unit_cancel_goto_on_contact(iptr unit)

{
  if (((units[unit].orders & 0xfU) == 0xb) && (unit_types[units[unit].type].role != 7)) {
    units[unit].orders = -1;
  }
  return;
}

/* 004273e6 auto */
void __cdecl unit_stack_wake_sentries(iptr unit)

{
  int iVar1;
  
  for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit)) {
    if ((units[unit].orders == 3) &&
       ((unit_types[units[unit].type].domain != '\0' ||
        (iVar1 = tile_is_ocean((int)units[unit].x,(int)units[unit].y), iVar1 == 0)))) {
      units[unit].orders = -1;
    }
  }
  return;
}

/* 004274a6 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_50 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_30 (*(uint *)(frame_ + FRAME_OFF(48)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
void __cdecl unit_reveal_surroundings(iptr unit,int param_2)

{
  byte civ3;
  u8 uVar2;
  byte unit_type2;
  byte unit_type;
  u8 uVar5;
  bool bVar6;
  bool bVar7;
  u8 uVar8;
  int x2;
  int y;
  uptr civ2;
  uint uVar12;
  uint uVar13;
  int y3;
  iptr iVar15;
  iptr x;
  iptr y4;
  iptr iVar17;
  uint uVar21;
  iptr iVar18;
  char *pcVar22;
  int y2;
  int city;
  uptr civ;
  int iVar26;
  iptr unit2;
  int iVar27;
  uint uVar28;
  bool bVar29;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar7 = false;
  x2 = (int)units[unit].x;
  y = (int)units[unit].y;
  civ3 = units[unit].owner;
  civ2 = (uptr)(char)civ3;
  uVar12 = unit_types[units[unit].type].flags & 1;
  uVar13 = unit_types[units[unit].type].flags & 8;
  uVar2 = unit_types[units[unit].type].domain;
  y3 = tile_is_ocean(x2,y);
  uVar28 = 1 << (civ3 & 0x1f) & 0xff;
  local_30 = 0;
  bVar29 = human_civ == civ2;
  if (civ2 == 0) {
    iVar15 = tile_at(x2,y);
    units[unit].visibility = *(byte *)(iVar15 + 4) | units[unit].visibility;
  }
  uVar8 = game.reveal_map;
  if ((game.reveal_map == '\0') && (((game.game_flags & 0x80) == 0 || ((scenario_flags & 8) == 0)))) {
    bVar6 = false;
  }
  else {
    bVar6 = true;
  }
  net_batch_begin();
  for (local_10 = 0; local_10 < 0x19; local_10++) {
    x = map_wrap_x((char)(&city_tile_dx_table)[local_10] + x2);
    y4 = (char)(&city_tile_dy_table)[local_10] + y;
    iVar17 = map_in_bounds(x,y4);
    if ((iVar17 != 0) &&
       (((local_10 < 8 || (local_10 == 0x14)) ||
        ((uVar12 != 0 &&
         ((uVar2 == 1 || (uVar21 = tile_is_ocean(x,y4), uVar21 == (uVar2 == 2))))
         ))))) {
      iVar18 = tile_at(x,y4);
      if (civ2 != 0) {
        pcVar22 = (char *)known_at(x,y4,civ2);
        if (((bVar29) && (!bVar6)) &&
           ((*(char *)(iVar18 + 1) != *pcVar22 || ((uVar28 & *(byte *)(iVar18 + 4)) == 0)))) {
          if (local_10 < 8) {
            local_30 = local_30 | 5;
          }
          else {
            local_30 = local_30 | 10;
          }
        }
        known_set(x,y4,CONCAT31((int3)((uint)iVar18 >> 8),*(i8 *)(iVar18 + 1)),
                  civ2,0,1);
      }
      tile_set_visible(x,y4,uVar28,1,1);
    }
  }
  for (local_10 = 0; local_10 < 8; local_10++) {
    x = map_wrap_x((char)(&dir_dx_table)[local_10] + x2);
    y2 = (char)(&dir_dy_table)[local_10] + y;
    city = map_in_bounds(x,y2);
    if (city != 0) {
      city = city_at(x,y2);
      if ((-1 < city) && (civ = (uptr)cities[city].owner, civ != civ2)) {
        if ((bVar29) && (!bVar6)) {
          if ((uVar28 & (int)(char)cities[city].known_to) == 0) {
            local_30 = local_30 | 5;
          }
          else if (*(char *)&cities[city].revealed_size[civ2] != cities[city].size) {
            local_30 = local_30 | 1;
          }
        }
        city_reveal_to_civ(city,civ2);
        if (uVar13 == 0) {
          unit_stack_set_seen_by(unit,civ);
        }
        if ((uVar2 == '\0') && ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0)) {
          civ_add_ai_goal(civ,x,y2,0,4);
          civ_add_ai_goal(civ,x,y2,1,2);
        }
      }
      iVar26 = tile_is_ocean(x,y2);
      if ((uVar13 == 0) || (iVar26 != 0)) {
        unit2 = tile_first_unit(x,y2);
        if (unit2 < 0) {
          city = tile_is_ocean(x2,y);
          if ((((city == 0) && (civ = tile_city_owner(x,y2), -1 < (int)civ)) &&
              (civ != civ2)) && ((*(byte *)&civs[civ2].treaties[civ] & 1) == 0))
          {
            if (!bVar7) {
              map_redraw_tile_all_views(x2,y);
              if (2 < game.multiplayer) {
                net_send_state_diff(0xff,2,0,0,0);
                net_send_message(0x72,0xff,x2,y,0,0,0,0,0,0);
              }
              bVar7 = true;
            }
            if (param_2 != 0) {
              diplo_civs_meet(civ2,civ,x,y2);
            }
          }
        }
        else {
          unit_type2 = units[unit2].owner;
          civ = (uptr)(char)unit_type2;
          if (civ != civ2) {
            unit_type = units[unit2].type;
            if ((uVar13 == 0) || ((unit_types[unit_type].flags & 0x4000) != 0)) {
              iVar27 = tile_city_owner(x2,y);
              if (iVar27 < 0) {
                unit_stack_set_seen_by(unit,civ);
              }
              if ((*(byte *)&civs[civ2].treaties[civ] & 8) == 0) {
                unit_stack_wake_sentries(unit2);
              }
              if ((1 << (unit_type2 & 0x1f) & (uint)game.human_players) == 0) {
                if ((iVar26 != 0) || (y3 == 0)) {
                  unit_cancel_goto_on_contact(unit2);
                }
              }
              else if (iVar26 == y3) {
                unit_cancel_goto_on_contact(unit2);
              }
            }
            if ((((unit_types[unit_type].flags & 8) == 0) ||
                (iVar27 = unit_stack_sum(unit2,2), 1 < iVar27)) ||
               ((unit_types[units[unit].type].flags & 0x4000) != 0)) {
              if (city < 0) {
                if (((bVar29) && (uVar8 == '\0')) && ((uVar28 & units[unit2].visibility) == 0)) {
                  local_30 = local_30 | 1;
                }
                unit_stack_set_seen_by(unit2,civ2);
              }
              if ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) {
                if (((y3 != 0) || (iVar26 == 0)) || (uVar2 == 1)) {
                  unit_cancel_goto_on_contact(unit);
                }
              }
              else if ((iVar26 == y3) || (uVar2 == 1)) {
                unit_cancel_goto_on_contact(unit);
              }
              if (((iVar26 != 0) && (civ != 0)) &&
                 ((*(byte *)&civs[civ2].treaties[civ] & 4) == 0)) {
                civ_add_ai_goal(civ2,x,y2,2,
                                   3 - (uint)((unit_types[unit_type].flags & 8) == 0));
              }
            }
            if (((unit_types[units[unit].type].domain == '\0') && (y3 == 0)) &&
               ((iVar26 == 0 && ((unit_types[unit_type].domain != 1 || (-1 < city)))))) {
              if ((!bVar7) && (uVar8 == '\0')) {
                map_redraw_tile_all_views(x2,y);
                if (2 < game.multiplayer) {
                  net_send_state_diff(0xff,2,0,0,0);
                  net_send_message(0x72,0xff,x2,y,0,0,0,0,0,0);
                }
                bVar7 = true;
              }
              if ((param_2 != 0) && (units[unit].type != '\t')) {
                diplo_civs_meet(civ2,civ,x,y2);
              }
              if ((char)unit_types[units[unit].type].role < 6) {
                civ_add_ai_goal(civ,x,y2,1,2 - (uint)(civ2 == 0));
              }
              if ((*(byte *)&civs[civ2].treaties[civ] & 4) == 0) {
                local_8 = 1;
                if (((civ != 0) && (unit_types[unit_type].role != 6)) &&
                   ((units[unit2].orders != 2 || (unit_types[unit_type].role != 1)))) {
                  local_8 = 3;
                }
                civ_add_ai_goal(civ2,x,y2,0,local_8);
              }
            }
          }
        }
      }
    }
  }
  for (local_10 = 8; local_10 < 0x19; local_10++) {
    if (local_10 != 0x14) {
      x = map_wrap_x((char)(&city_tile_dx_table)[local_10] + x2);
      y3 = (char)(&city_tile_dy_table)[local_10] + y;
      y2 = map_in_bounds(x,y3);
      if (y2 != 0) {
        y2 = tile_first_unit(x,y3);
        civ = tile_city_or_unit_owner(x,y3);
        city = city_at(x,y3);
        if (civ != civ2) {
          if ((uVar12 != 0) &&
             ((uVar2 == 1 ||
              (uVar21 = tile_is_ocean(x,y3), uVar21 == (uVar2 == 2))))) {
            if (-1 < city) {
              if ((bVar29) && (!bVar6)) {
                if ((uVar28 & (int)(char)cities[city].known_to) == 0) {
                  local_30 = local_30 | 10;
                }
                else if (*(char *)&cities[city].revealed_size[civ2] != cities[city].size) {
                  local_30 = local_30 | 2;
                }
              }
              city_reveal_to_civ(city,civ2);
            }
            if ((-1 < y2) && ((unit_types[units[y2].type].flags & 8) == 0)) {
              if (city < 0) {
                if (((bVar29) && (uVar8 == '\0')) && ((uVar28 & units[unit].visibility) == 0)) {
                  local_30 = local_30 | 2;
                }
                unit_stack_set_seen_by(y2,civ2);
              }
              iVar26 = tile_is_ocean(x,y3);
              if (((iVar26 != 0) && (civ != 0)) &&
                 ((*(byte *)&civs[civ2].treaties[civ] & 4) == 0)) {
                civ_add_ai_goal(civ2,x,y3,2,2);
              }
            }
          }
          if (((-1 < y2) && (uVar13 == 0)) &&
             ((unit_type2 = units[y2].type, (unit_types[unit_type2].flags & 1) != 0 &&
              ((unit_types[unit_type2].domain == 1 ||
               (uVar5 = unit_types[unit_type2].domain, uVar21 = tile_is_ocean(x2,y),
               (uVar5 == 2) == uVar21)))))) {
            unit_cancel_goto_on_contact(y2);
            unit_stack_wake_sentries(y2);
            y2 = tile_city_owner(x2,y);
            if (y2 < 0) {
              unit_stack_set_seen_by(unit,civ);
            }
            y3 = tile_is_ocean(x,y3);
            if (((y3 == 0) && (civ != 0)) &&
               ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0)) {
              civ_add_ai_goal(civ,x2,y,2,2);
            }
          }
          if (((-1 < city) && (y3 = tile_visible_to(x2,y,civ), y3 != 0)) &&
             ((unit_types[units[unit].type].attack != '\0' && (uVar13 == 0)))) {
            unit_stack_set_seen_by(unit,civ);
          }
        }
      }
    }
  }
  if (game.turn == 0) {
    net_batch_flush();
  }
  else {
    net_send_state_diff(0xff,2,0,0,0);
    if (((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) && (human_civ != civ2)) {
      for (local_50 = 1; (int)local_50 < 8; local_50++) {
        if (((1 << ((byte)local_50 & 0x1f) & (uint)game.human_players) != 0) &&
           (((game.reveal_map != '\0' ||
             ((1 << ((byte)local_50 & 0x1f) & (uint)units[unit].visibility) != 0)) ||
            ((int)units[unit].owner == (local_50 & 0xff))))) {
          if (human_civ == local_50) {
            map_redraw_neighbors_all_views(x2,y);
          }
          else if (2 < game.multiplayer) {
            net_send_message(0x75,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + local_50 * 4) * 0x54)
                               ,x2,y,0,0,0,0,0,0);
          }
        }
      }
      if ((!bVar7) && (map_redraw_tile_all_views(x2,y), 2 < game.multiplayer)) {
        net_send_message(0x72,0xff,x2,y,0,0,0,0,0,0);
      }
    }
    else {
      local_5c = 2;
      if ((uVar12 == 0) || ((local_30 & 2) == 0)) {
        local_5c = 1;
        if ((local_30 & 4) != 0) {
          local_5c = 2;
        }
      }
      else if ((local_30 & 8) != 0) {
        local_5c = 3;
      }
      if ((local_30 == 0) && (local_5c = 0, bVar7)) {
        net_batch_flush();
        return;
      }
      if (human_civ == civ2) {
        map_redraw_area_all_views(x2,y,local_5c,civ2,1);
      }
      else if (2 < game.multiplayer) {
        net_send_message(0x76,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),x2
                           ,y,local_5c,civ2,0,0,0,0);
      }
    }
    net_batch_flush();
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef local_5c
#undef local_50
#undef local_30
#undef local_10
#undef local_8

/* 00440750 auto */
#define city_food_box_rows (*(int *)((u8 *)&g.d_006a6560))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define local_40 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_28 (*(uptr *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define city2 (*(uptr *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
void __cdecl unit_caravan_establish_trade(iptr unit,uptr city)

{
  byte civ2;
  byte civ3;
  iptr civ;
  int civ4;
  int iVar5;
  int iVar6;
  uptr uVar7;
  int iVar7;
  uint uVar8;
  iptr iVar9;
  uint unit_type2;
  uint uVar11;
  bool unit_type;
  i32 uVar13;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = units[unit].owner;
  civ = (iptr)(char)civ2;
  civ3 = cities[city].owner;
  civ4 = (int)(char)civ3;
  if (units[unit].home_city == -1) {
    city2 = 0xffffffff;
  }
  else {
    city2 = (uptr)(byte)units[unit].home_city;
  }
  if (((int)city2 < 0) &&
     (city2 = city_find_nearest((int)units[unit].x,(int)units[unit].y,civ,0xffffffff,-1)
     , (int)city2 < 0)) {
    city2 = 0;
  }
  local_1c = map_distance_diag((int)cities[city].x,(int)cities[city].y,
                                (int)cities[city2].x,(int)cities[city2].y);
  if ((game.game_flags & 4) != 0) {
    local_1c = (local_1c << 2) / 5;
  }
  if ((game.game_flags & 8) != 0) {
    local_1c = (int)(local_1c * 5 + (local_1c * 5 >> 0x1f & 3U)) >> 2;
  }
  local_1c = (((int)cities[city2].base_trade + (int)cities[city].base_trade) * (local_1c + 10)
             ) / 0x18;
  iVar5 = tile_landmass((int)cities[city].x,(int)cities[city].y);
  iVar6 = tile_landmass((int)cities[city2].x,(int)cities[city2].y);
  if (iVar6 != iVar5) {
    local_1c = local_1c << 1;
  }
  if (civ == civ4) {
    local_1c = local_1c >> 1;
  }
  uVar7 = (uptr)(char)units[unit].counter;
  unit_type = units[unit].type == '1';
  if (unit_type) {
    local_1c += (local_1c >> 1);
  }
  local_c = (uint)unit_type;
  local_34 = map_road_connection(civ,(int)cities[city].x,(int)cities[city].y,
                                (int)cities[city2].x,(int)cities[city2].y);
  iVar7 = city_has_improvement(city,0x20);
  if ((iVar7 != 0) && (iVar7 = city_has_improvement(city2,0x20), iVar7 != 0)) {
    if (iVar6 == iVar5) {
      local_34++;
    }
    else {
      local_34 += 2;
    }
  }
  iVar5 = city_has_improvement(city,0x19);
  if (iVar5 != 0) {
    local_34++;
  }
  iVar5 = city_has_improvement(city2,0x19);
  if (iVar5 != 0) {
    local_34++;
  }
  local_1c += (local_34 * local_1c >> 1);
  local_30 = 0;
  switch(uVar7) {
  case 3:
  case 5:
  case 8:
  case 10:
    local_30 = local_1c / 2;
    break;
  case 9:
  case 0xb:
  case 0xc:
  case 0xd:
    local_30 = local_1c;
    break;
  case 0xe:
    local_30 = (local_1c * 3) / 2;
    break;
  case 0xf:
    local_30 = local_1c * 2;
  }
  for (local_18 = 0; local_18 < 3; local_18++) {
    if ((int)*(char *)&cities[city].demands[local_18] == uVar7) {
      if (units[unit].owner == civ) {
        local_1c = local_1c * 2 + local_30;
      }
      else {
        local_1c = (local_1c + local_30) * 2;
      }
    }
  }
  if (((game.turn < 200) && (iVar5 = civ_has_advance(civ,0x26), iVar5 == 0)) &&
     (iVar5 = civ_has_advance(civ,0x39), iVar5 == 0)) {
    local_1c = local_1c << 1;
  }
  iVar5 = civ_has_advance(civ,0x43);
  if (iVar5 != 0) {
    local_1c -= local_1c / 3;
  }
  iVar5 = civ_has_advance(civ,0x1e);
  if (iVar5 != 0) {
    local_1c -= local_1c / 3;
  }
  uVar13 = 30000;
  iVar5 = _rand();
  iVar5 = iVar5 % 10 + 200;
  iVar6 = civ_research_cost(civ);
  uVar13 = int_clamp((iVar6 * 2) / 3,iVar5,uVar13);
  iVar5 = int_clamp(local_1c,0,uVar13);
  if ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) {
    if ((int)uVar7 < 0) {
      text_set_label_arg(0,*(i32 *)(label_string_ids + 0x100));
    }
    else {
      text_set_label_arg(0,commodity_names[uVar7]);
    }
    text_set_string_arg(1,(iptr)&cities[city2].name);
    text_set_string_arg(2,(iptr)&cities[city].name);
    text_set_number_arg(0,iVar5);
    snd_play_effect((-(uint)(local_c == 0) & 0x14) + 0x16,1,0,0);
    if ((int)uVar7 < 0) {
      if (game.multiplayer < 3) {
        dlg_game_txt_with_unit(ADDR(0x6262ec, ((u8 *)&g.d_006262ec)),unit);
      }
      else {
        if (human_civ == civ) {
          dlg_game_txt_with_unit(ADDR(0x6262f8, ((u8 *)&g.d_006262f8)),unit);
        }
        else if ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) {
          net_send_text_args(0x10,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),3,1,
                             unit,local_c);
        }
        if (civ != civ4) {
          if (human_civ == civ4) {
            dlg_game_txt_with_unit(ADDR(0x626304, ((u8 *)&g.d_00626304)),unit);
          }
          else if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
            net_send_text_args(0x10,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ4 * 4) * 0x54),3,
                               1,unit,local_c);
          }
        }
      }
    }
    else if (game.multiplayer < 3) {
      dlg_game_txt_with_unit(ADDR(0x6262d4, ((u8 *)&g.d_006262d4)),unit);
    }
    else {
      if (human_civ == civ) {
        dlg_game_txt_with_unit(ADDR(0x6262dc, ((u8 *)&g.d_006262dc)),unit);
      }
      else if ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) {
        net_send_text_args(0xf,*(i32 *)
                                (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),3,1,
                           unit,local_c);
      }
      if (civ != civ4) {
        if (human_civ == civ4) {
          dlg_game_txt_with_unit(ADDR(0x6262e4, ((u8 *)&g.d_006262e4)),unit);
        }
        else if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
          net_send_text_args(0xf,*(i32 *)
                                  (&net_player_slots + *(int *)(&net_civ_slots + civ4 * 4) * 0x54),3,1,
                             unit,local_c);
        }
      }
    }
  }
  civ_adjust_attitude(civ4,civ,0xfffffff6);
  civ_adjust_attitude(civ,civ4,0xfffffff6);
  if ((int)uVar7 < 0) {
    city_recalc(city,0);
    cities[city].food_box =
         cities[city].food_box + (short)(((cities[city].size + 1) * city_food_box_rows) / 2);
  }
  else {
    civs[civ].gold += iVar5;
    civs[civ].research_progress += (short)iVar5;
    if (human_civ == civ) {
      status_draw_info(1);
    }
  }
  unit_type2 = (uint)units[unit].type;
  unit_destroy_redraw(unit,1);
  city_add_trade_route(city2,city,uVar7);
  if (-1 < (int)uVar7) {
    local_10 = 0;
    local_40 = 0xffffffff;
    for (local_18 = 0; local_18 < 3; local_18++) {
      uVar8 = _rand();
      uVar11 = (int)uVar8 >> 0x1f;
      local_8 = ((uVar8 ^ uVar11) - uVar11 & 7 ^ uVar11) - uVar11;
      local_28 = (uptr)*(char *)&cities[city].supplies[local_18];
      if ((int)local_28 < 0) {
        if ((int)local_28 < 1) {
          local_28 = ~local_28 + 1;
        }
      }
      else {
        local_8 += 10;
      }
      if (local_28 != uVar7) {
        if (9 < local_8) {
          for (local_24 = 0; local_24 < 3; local_24++) {
            if ((int)*(char *)&cities[city2].demands[local_24] == local_28) {
              local_8 += 10;
            }
          }
        }
        if (local_10 <= local_8) {
          local_10 = local_8;
          local_40 = local_28;
        }
      }
    }
    city_add_trade_route(city,city2,local_40);
    if (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) &&
       ((civ != civ4 || (2 < game.multiplayer)))) {
      snd_play_effect((-(uint)(local_c == 0) & 0x14) + 0x16,1,0,0);
      iVar9 = civ_get_adjective(civ);
      text_set_string_arg(0,iVar9);
      text_set_label_arg(1,commodity_names[uVar7]);
      text_set_string_arg(2,(iptr)&cities[city2].name);
      text_set_string_arg(3,(iptr)&cities[city].name);
      text_set_label_arg(4,commodity_names[local_40]);
      if ((human_civ == civ4) && (civ != civ4)) {
        dlg_game_txt_with_unit_flags(ADDR(0x626310, ((u8 *)&g.d_00626310)),unit_type2,(ui_large_screen == 0) - 1 & 8);
      }
      else if ((2 < game.multiplayer) && (human_civ != civ4)) {
        net_send_text_args(0x11,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ4 * 4) * 0x54),5,0,
                           unit_type2,(ui_large_screen == 0) - 1 & 8);
      }
      if ((2 < game.multiplayer) && (civ != civ4)) {
        if (human_civ == civ) {
          dlg_game_txt_with_unit_flags(ADDR(0x626320, ((u8 *)&g.d_00626320)),unit_type2,(ui_large_screen == 0) - 1 & 8);
        }
        else if (((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) && (human_civ != civ)
                ) {
          net_send_text_args(0x11,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),5,0,
                             unit_type2,(ui_large_screen == 0) - 1 & 8);
        }
      }
    }
  }
  return;
}
#undef city_food_box_rows
#undef human_civ
#undef ui_large_screen
#undef local_40
#undef local_34
#undef local_30
#undef local_28
#undef local_24
#undef local_1c
#undef local_18
#undef city2
#undef local_10
#undef local_c
#undef local_8

/* 00447ebe auto */
void __cdecl nuke_anim_sprites_global_init(void)

{
  nuke_anim_sprites_static_init();
  nuke_anim_sprites_reg_atexit();
  return;
}

/* 00447ed8 auto */
void __cdecl nuke_anim_sprites_static_init(void)

{
  FUN_005f2620(&nuke_anim_sprites,0x3c,0xb,sprite_init,sprite_destroy);
  return;
}

/* 00447f00 auto */
void __cdecl nuke_anim_sprites_reg_atexit(void)

{
  _atexit(nuke_anim_sprites_static_dtor);
  return;
}

/* 00447f1d auto */
void __cdecl nuke_anim_sprites_static_dtor(void)

{
  FUN_005f2490(&nuke_anim_sprites,0x3c,0xb,sprite_destroy);
  return;
}

/* 00448103 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl unit_shield_sprite_global_init(void)

{
  unit_shield_sprite_static_init();
  unit_shield_sprite_reg_atexit();
  return;
}

/* 0044811d auto */
void __cdecl unit_shield_sprite_static_init(void)

{
  sprite_init((Sprite *)&unit_shield_sprite);
  return;
}

/* 00448137 auto */
void __cdecl unit_shield_sprite_reg_atexit(void)

{
  _atexit(unit_shield_sprite_static_dtor);
  return;
}

/* 00448154 auto */
void __cdecl unit_shield_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&unit_shield_sprite);
  return;
}

/* 00448272 auto */
void __cdecl unit_sprites_global_init(void)

{
  unit_sprites_static_init();
  unit_sprites_reg_atexit();
  return;
}

/* 0044828c auto */
void __cdecl unit_sprites_static_init(void)

{
  FUN_005f2620(&unit_sprites,0x3c,0x3f,sprite_init,sprite_destroy);
  return;
}

/* 004482b4 auto */
void __cdecl unit_sprites_reg_atexit(void)

{
  _atexit(unit_sprites_static_dtor);
  return;
}

/* 004482d1 auto */
void __cdecl unit_sprites_static_dtor(void)

{
  FUN_005f2490(&unit_sprites,0x3c,0x3f,sprite_destroy);
  return;
}

/* 004482f4 auto */
void __cdecl fortify_overlay_sprites_global_init(void)

{
  fortify_overlay_sprites_static_init();
  fortify_overlay_sprites_reg_atexit();
  return;
}

/* 0044830e auto */
void __cdecl fortify_overlay_sprites_static_init(void)

{
  FUN_005f2620(&fortify_overlay_sprites,0x3c,8,sprite_init,sprite_destroy);
  return;
}

/* 00448336 auto */
void __cdecl fortify_overlay_sprites_reg_atexit(void)

{
  _atexit(fortify_overlay_sprites_static_dtor);
  return;
}

/* 00448353 auto */
void __cdecl fortify_overlay_sprites_static_dtor(void)

{
  FUN_005f2490(&fortify_overlay_sprites,0x3c,8,sprite_destroy);
  return;
}

/* 00448a4d auto */
void __cdecl explosion_sprites_global_init(void)

{
  explosion_sprites_static_init();
  explosion_sprites_reg_atexit();
  return;
}

/* 00448a67 auto */
void __cdecl explosion_sprites_static_init(void)

{
  FUN_005f2620(&explosion_sprites,0x3c,8,sprite_init,sprite_destroy);
  return;
}

/* 00448a8f auto */
void __cdecl explosion_sprites_reg_atexit(void)

{
  _atexit(explosion_sprites_static_dtor);
  return;
}

/* 00448aac auto */
void __cdecl explosion_sprites_static_dtor(void)

{
  FUN_005f2490(&explosion_sprites,0x3c,8,sprite_destroy);
  return;
}

/* 0044b239 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl unit_sprite_scan_shield_offset(int param_1,int param_2,int param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)(&unit_shield_x_offsets + param_1 * 4) = 0;
  *(i32 *)(&unit_shield_y_offsets + param_1 * 4) = 0;
  for (local_c = 0; local_c < 0x40; local_c++) {
    iVar1 = surface_get_pixel
                      ((DibSurface *)&gfx_sheet_surface,param_2 - 1 + local_c + 1,param_3 - 1);
    if (iVar1 == 4) {
      *(int *)(&unit_shield_x_offsets + param_1 * 4) = local_c;
    }
  }
  for (local_14 = 0; local_14 < 0x30; local_14++) {
    iVar1 = surface_get_pixel
                      ((DibSurface *)&gfx_sheet_surface,param_2 - 1,param_3 - 1 + local_14 + 1);
    if (iVar1 == 4) {
      *(int *)(&unit_shield_y_offsets + param_1 * 4) = local_14;
    }
  }
  return;
}
#undef local_14
#undef local_c

/* 00472d20 auto */
#define dummy_unit_owner (*(i8 *)((u8 *)&units[2048] + 7))
i32 __cdecl unit_make_dummy(iptr param_1,iptr param_2)

{
  dummy_unit_type = (i8)param_1;
  dummy_unit_owner = (i8)param_2;
  dummy_unit_x = 0xffce;
  dummy_unit_y = 0xffce;
  dummy_unit_flags = 0;
  dummy_unit_home_city = 0xff;
  dummy_unit_moves_used = 0;
  dummy_unit_visibility = 0;
  dummy_unit_byte_0e = 0;
  dummy_unit_counter = 0;
  dummy_unit_prev_in_stack = 0xffff;
  dummy_unit_next_in_stack = 0xffff;
  dummy_unit_orders = 0xff;
  dummy_unit_goto_x = 0xffff;
  dummy_unit_goto_y = 0xffff;
  return 0x800;
}
#undef dummy_unit_owner

/* 0048710a auto */
#define unit (*(uptr *)(frame_ + FRAME_OFF(0)))
void __cdecl units_reset_for_turn(iptr civ)

{
  uint *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  map_rebuild_unit_flags();
  if (civ == -3) {
    for (unit = 0; (int)unit < (int)game.num_units; unit++) {
      if (units[unit].id != 0) {
        unit_exhaust_moves(unit);
      }
    }
  }
  for (unit = 0; (int)unit < (int)game.num_units; unit++) {
    if ((units[unit].id != 0) &&
       (((tile_set_improvements((int)units[unit].x,(int)units[unit].y,1,1,1), civ == -1 ||
         (civ == -2)) || (units[unit].owner == civ)))) {
      if ((units[unit].flags & 2) == 0) {
        units[unit].moves_used = '\0';
        units[unit].field_0e = '\0';
        units[unit].flags = units[unit].flags & 0xbfff;
        if ((((units[unit].flags & 0x20) != 0) && ((units[unit].flags & 4) == 0)) &&
           ((((int)game.turn ^ unit & 3) & 3) == 0)) {
          units[unit].flags = units[unit].flags & 0xffdf;
        }
        units[unit].flags = units[unit].flags & 0xfffb;
      }
      else {
        units[unit].field_0e += 0xff;
        if (units[unit].field_0e == '\0') {
          units[unit].flags = units[unit].flags & 0xfffd;
          puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + (char)units[unit].counter * 4);
          *puVar1 = *puVar1 & 0xfeffffff;
          spy_try_escape(unit,0,(int)(char)units[unit].counter);
        }
      }
    }
  }
  return;
}
#undef unit

/* 00489859 auto */
#define active_unit_lost_in_combat (*(int *)((u8 *)&g.d_0062c5bc))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl unit_activate_next(i32 param_1)

{
  iptr unit;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_unit_lost_in_combat == 0) {
    unit2 = (iptr)game.active_unit;
  }
  else {
    unit2 = -1;
  }
  unit = unit_find_nearest_selectable(unit2,param_1);
  active_unit_lost_in_combat = 0;
  game.active_unit = (i16)unit;
  if (((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) {
    if (((units[unit].orders != 1) && (units[unit].orders != 2)) &&
       ((units[unit].orders == -1 || ('\n' < units[unit].orders)))) {
      units[unit].field_0e = '\0';
      map_cursor_x = units[unit].x;
      map_cursor_y = units[unit].y;
      status_redraw(1);
      mapviews_ensure_visible((int)units[unit].x,(int)units[unit].y,(int)units[unit].owner);
      menu_update_states();
    }
    if (units[unit].moves_used == '\0') {
      unit_reveal_surroundings(unit,1);
    }
    if (mp_simultaneous_moves == '\0') {
      input_flush_events();
    }
  }
  if ((unit < 0) || (units[unit].id == 0)) {
    ui_redraw_all_maps(0);
  }
  return;
}
#undef active_unit_lost_in_combat
#undef map_cursor_x
#undef map_cursor_y
#undef mp_simultaneous_moves
#undef unit2

/* 004ad01e auto */
i32 __cdecl path_grid_get_cost(int param_1,int param_2)

{
  return *(i32 *)
          ((param_1 - path_grid_center_x) * 0xc0 +
           ((param_1 - path_grid_center_x) + (param_2 - path_grid_center_y) >> 1) * -0xbc + ADDR(0x6cffc0, ((u8 *)&g.d_006cedc0 + 4608)));
}

/* 004ad076 auto */
void __cdecl path_grid_set_cost(int param_1,int param_2,i32 param_3)

{
  *(i32 *)
   ((param_1 - path_grid_center_x) * 0xc0 +
    ((param_2 - path_grid_center_y) + (param_1 - path_grid_center_x) >> 1) * -0xbc + ADDR(0x6cffc0, ((u8 *)&g.d_006cedc0 + 4608))) = param_3;
  return;
}

/* 004ad20f auto */
#define path_debug_pending (*(i32 *)((u8 *)&g.d_0062d04c))
#define path_debug_requested (*(int *)((u8 *)&g.d_0062d050))
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define local_60 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_58 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_48 (*(uint *)(frame_ + FRAME_OFF(24)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_30 (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(52)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(60)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(64)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(72)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(76)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
int __cdecl path_coarse_find_waypoint(i32 param_1,i32 param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  i8 *puVar4;
  char *pcVar5;
  byte *pbVar6;
  int iVar7;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_40 = 0;
  local_8 = path_debug_requested;
  path_goal_x = param_3;
  path_goal_y = param_4;
  local_24 = (uint)(unit_types[path_unit_type].domain == 2);
  iVar3 = path_coarse_snap_cell(param_1,param_2,local_24);
  iVar2 = path_goal_y;
  iVar7 = path_goal_x;
  if (iVar3 == 0) {
    path_goal_x = param_3;
    path_goal_y = param_4;
  }
  else {
    path_coarse_start_x = path_goal_x;
    path_coarse_start_y = path_goal_y;
    path_coarse_snap_cell(param_3,param_4,local_24);
    _memset(map_coarse[2],0,(int)map.quarter_w * (int)map.quarter_h);
    path_queue_head = 0;
    path_queue_x = path_goal_x;
    path_queue_y = path_goal_y;
    path_queue_tail = 1;
    puVar4 = (i8 *)map_coarse2_at(path_goal_x,path_goal_y);
    *puVar4 = 1;
    while( true ) {
      local_34 = (&path_queue_x)[path_queue_head];
      local_3c = (&path_queue_y)[path_queue_head];
      path_queue_head = path_queue_head + 1U & 0xff;
      if ((local_34 == iVar7) && (local_3c == iVar2)) break;
      pbVar6 = (byte *)map_coarse2_at(local_34,local_3c);
      local_20 = (uint)*pbVar6;
      if (local_24 == 0) {
        pbVar6 = (byte *)map_coarse0_at(local_34,local_3c);
        bVar1 = *pbVar6;
      }
      else {
        pbVar6 = (byte *)map_coarse1_at(local_34,local_3c);
        bVar1 = *pbVar6;
      }
      local_58 = (uint)bVar1;
      local_18 = local_58;
      for (local_14 = 0; local_14 < 8; local_14++) {
        if ((local_18 & 1 << ((byte)local_14 & 0x1f)) != 0) {
          local_1c = coarse_wrap_x((char)(&coarse_dir_dx_table)[local_14] + local_34);
          local_28 = (char)(&coarse_dir_dy_table)[local_14] + local_3c;
          if ((((-1 < local_1c) && (local_1c < map.quarter_w)) && (-1 < local_28)) &&
             ((local_28 < map.quarter_h &&
              (pcVar5 = (char *)map_coarse2_at(local_1c,local_28), *pcVar5 == '\0')))) {
            pcVar5 = (char *)map_coarse2_at(local_1c,local_28);
            *pcVar5 = (char)local_20 + 1;
            (&path_queue_x)[path_queue_tail] = local_1c;
            (&path_queue_y)[path_queue_tail] = local_28;
            path_queue_tail = path_queue_tail + 1U & 0xff;
          }
        }
      }
      if ((local_40 != 0) || (path_queue_head == path_queue_tail)) goto LAB_004ad51c;
    }
    local_40 = 1;
LAB_004ad51c:
    local_38 = 0;
    if (local_40 != 0) {
      local_c = 99;
      local_30 = -1;
      if (local_24 == 0) {
        pbVar6 = (byte *)map_coarse0_at(iVar7,iVar2);
        bVar1 = *pbVar6;
      }
      else {
        pbVar6 = (byte *)map_coarse1_at(iVar7,iVar2);
        bVar1 = *pbVar6;
      }
      local_60 = (uint)bVar1;
      local_18 = local_60;
      for (local_14 = 0; local_14 < 8; local_14++) {
        if ((local_18 & 1 << ((byte)local_14 & 0x1f)) != 0) {
          local_1c = coarse_wrap_x((char)(&coarse_dir_dx_table)[local_14] + iVar7);
          local_28 = (char)(&coarse_dir_dy_table)[local_14] + iVar2;
          if ((((-1 < local_1c) && (local_1c < map.quarter_w)) && (-1 < local_28)) &&
             (local_28 < map.quarter_h)) {
            pbVar6 = (byte *)map_coarse2_at(local_1c,local_28);
            local_48 = (uint)*pbVar6;
            if (local_48 != 0) {
              if ((int)local_48 < (int)local_c) {
                local_30 = local_14;
                local_c = local_48;
                local_20 = map_distance_diag(param_3,param_4,local_1c * 4 + 1,local_28 * 4 + 1);
              }
              else if ((local_48 == local_c) &&
                      (local_2c = map_distance_diag(param_3,param_4,local_1c * 4 + 1,
                                                     local_28 * 4 + 1),
                      (int)local_2c < (int)local_20)) {
                local_30 = local_14;
                local_20 = local_2c;
              }
            }
          }
        }
      }
      if (-1 < local_30) {
        iVar7 = coarse_wrap_x((char)(&coarse_dir_dx_table)[local_30] + iVar7);
        local_4c = iVar7 * 4 + 1;
        local_50 = ((char)(&coarse_dir_dy_table)[local_30] + iVar2) * 4 + 1;
        local_38 = 1;
        local_44 = local_4c;
        local_10 = local_50;
        map_diag_tile_by_ocean(local_4c,local_50,(iptr)&local_4c,(iptr)&local_50,local_24);
      }
    }
    if (local_38 == 0) {
      path_goal_x = param_3;
      path_goal_y = param_4;
    }
    else {
      path_goal_x = local_4c;
      path_goal_y = local_50;
    }
  }
  if (local_8 != 0) {
    path_debug_pending = 1;
  }
  return local_40;
}
#undef path_debug_pending
#undef path_debug_requested
#undef path_goal_x
#undef path_goal_y
#undef local_60
#undef local_58
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
#undef local_8

/* 004ad822 auto */
#define path_goal_x (*(i32 *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define x2 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
uint __cdecl path_coarse_snap_cell(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_24 = -1;
  iVar1 = param_1 >> 2;
  iVar2 = param_2 >> 2;
  if (param_3 == 0) {
    pcVar3 = (char *)map_coarse0_at(iVar1,iVar2);
    if (*pcVar3 != '\0') {
      local_24 = 8;
    }
  }
  else {
    pcVar3 = (char *)map_coarse1_at(iVar1,iVar2);
    if (*pcVar3 != '\0') {
      local_24 = 8;
    }
  }
  if (local_24 == 8) {
    iVar4 = map_diag_tile_by_ocean(iVar1 * 4 + 1,iVar2 * 4 + 1,(iptr)&x2,(iptr)&y2,param_3);
    if (iVar4 == 0) {
      local_24 = -1;
    }
    else {
      iVar4 = map_path_length(x2,y2,param_1,param_2,param_3,0x12);
      if (iVar4 < 0) {
        local_24 = -1;
      }
    }
  }
  if (local_24 < 0) {
    local_8 = 99;
    for (local_10 = 0; local_10 < 8; local_10++) {
      iVar4 = coarse_wrap_x((char)(&dir_dx_table)[local_10] + iVar1);
      iVar5 = (char)(&dir_dy_table)[local_10] + iVar2;
      if (((((-1 < iVar4) && (iVar4 < map.quarter_w)) && (-1 < iVar5)) && (iVar5 < map.quarter_h))
         && (((param_3 != 0 && (pcVar3 = (char *)map_coarse1_at(iVar4,iVar5), *pcVar3 != '\0')) ||
             ((param_3 == 0 && (pcVar3 = (char *)map_coarse0_at(iVar4,iVar5), *pcVar3 != '\0'))))))
      {
        x2 = iVar4 * 4 + 1;
        y2 = iVar5 * 4 + 1;
        iVar4 = map_in_bounds(x2,y2);
        if (((iVar4 != 0) &&
            (iVar4 = map_distance_diag(param_1,param_2,x2,y2), iVar4 < local_8)) &&
           ((iVar5 = map_diag_tile_by_ocean(x2,y2,(iptr)&x2,(iptr)&y2,param_3),
            iVar5 != 0 &&
            (iVar5 = map_path_length(x2,y2,param_1,param_2,param_3,0x12), -1 < iVar5))
           )) {
          local_24 = local_10;
          local_8 = iVar4;
        }
      }
    }
  }
  local_10 = local_24;
  if (local_24 < 0) {
    local_10 = 8;
  }
  path_goal_x = coarse_wrap_x((char)(&dir_dx_table)[local_10] + iVar1);
  path_goal_y = (char)(&dir_dy_table)[local_10] + iVar2;
  return (uint)(-1 < local_24);
}
#undef path_goal_x
#undef path_goal_y
#undef local_24
#undef y2
#undef local_10
#undef x2
#undef local_8

/* 004adafc auto */
#define path_debug_pending (*(i32 *)((u8 *)&g.d_0062d04c))
#define path_debug_requested (*(i32 *)((u8 *)&g.d_0062d050))
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define y2 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_70 (*(uint *)(frame_ + FRAME_OFF(24)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_54 (*(uptr *)(frame_ + FRAME_OFF(52)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_30 (*(uint *)(frame_ + FRAME_OFF(88)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(96)))
#define local_24 (*(uptr *)(frame_ + FRAME_OFF(100)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(104)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(108)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(112)))
uptr __cdecl unit_goto_next_dir(iptr unit)

{
  u8 uVar1;
  byte bVar2;
  byte terrain;
  int iVar4;
  int iVar5;
  int x2;
  int y;
  int civ;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  byte *pbVar13;
  uint uVar14;
  int x;
  int iVar16;
  int iVar17;
  uint uVar18;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_54 = 0xffffffff;
  iVar4 = (int)units[unit].goto_x;
  iVar5 = (int)units[unit].goto_y;
  x2 = (int)units[unit].x;
  y = (int)units[unit].y;
  path_unit_type = (iptr)units[unit].type;
  uVar1 = unit_types[units[unit].type].domain;
  civ = map_in_bounds(iVar4,iVar5);
  if ((civ != 0) && ((iVar4 != x2 || (iVar5 != y)))) {
    civ = (int)units[unit].owner;
    uVar9 = (uint)game.human_players & 1 << (units[unit].owner & 0x1fU);
    local_70 = iVar4 - x2;
    if ((game.rules & 0x8000) == 0) {
      if ((map.width - 2 <= iVar4) && (x2 < 2)) {
        local_70 = -1;
      }
      if ((iVar4 < 2) && (map.width - 2 <= x2)) {
        local_70 = 1;
      }
    }
    iVar10 = map_distance(x2,y,iVar4,iVar5);
    if (iVar10 < 2) {
      local_54 = map_dir_from_delta(local_70,iVar5 - y);
    }
    else {
      iVar10 = iVar4;
      x = iVar5;
      if (unit_types[units[unit].type].domain != 1) {
        iVar10 = map_distance(x2,y,iVar4,iVar5);
        if ((iVar10 < 0x17) &&
           (path_goal_x = iVar4, path_goal_y = iVar5,
           local_54 = map_path_next_dir(x2,y,999), -1 < (int)local_54)) {
          path_debug_pending = 0;
          path_debug_requested = 0;
          return local_54;
        }
        iVar16 = path_coarse_find_waypoint(x2,y,iVar4,iVar5);
        iVar10 = path_goal_x;
        x = path_goal_y;
        if (iVar16 != 0) {
          iVar10 = map_distance(x2,y,path_goal_x,path_goal_y);
          if (iVar10 < 0x17) {
            local_54 = map_path_next_dir(x2,y,0x3e6);
          }
          else {
            local_54 = 0xffffffff;
          }
          iVar10 = path_goal_x;
          x = path_goal_y;
          if (-1 < (int)local_54) {
            path_debug_pending = 0;
            path_debug_requested = 0;
            return local_54;
          }
        }
      }
      path_goal_y = x;
      path_goal_x = iVar10;
      uVar11 = path_goal_x - x2;
      uVar12 = path_goal_y - y;
      local_1c = uVar11;
      if ((int)uVar11 < 1) {
        local_1c = ~uVar11 + 1;
      }
      local_28 = uVar12;
      if ((int)uVar12 < 1) {
        local_28 = ~uVar12 + 1;
      }
      local_70 = uVar11;
      if ((((game.rules & 0x8000) == 0) && ((int)map.width >> 1 < (int)local_1c)) &&
         (local_1c = (int)map.width - local_1c, local_70 = local_1c, -1 < (int)uVar11)) {
        local_70 = -local_1c;
      }
      iVar10 = (int)(local_28 + local_1c) >> 1;
      if ((int)local_28 < (int)local_1c) {
        local_38 = local_1c * 2 - ((iVar10 - local_28) + 1);
      }
      else {
        local_38 = local_28 * 2 - ((iVar10 - local_1c) + 1);
      }
      if ((local_70 == 0) && (uVar12 == 0)) {
        units[unit].orders = -1;
        unit_exhaust_moves(unit);
      }
      else {
        local_18 = 9999;
        local_54 = 8;
        uVar11 = tile_improvements(x2,y);
        pbVar13 = (byte *)tile_at(x2,y);
        bVar2 = *pbVar13;
        uVar14 = tile_improvements(x2,y);
        iVar10 = tile_in_enemy_zoc(x2,y,civ);
        for (local_24 = 0; (int)local_24 < 8; local_24++) {
          x = map_wrap_x((char)(&dir_dx_table)[local_24] + x2);
          y2 = (char)(&dir_dy_table)[local_24] + y;
          local_20 = local_70 - (int)(char)(&dir_dx_table)[local_24];
          local_30 = uVar12 - (int)(char)(&dir_dy_table)[local_24];
          if ((int)local_20 < 1) {
            local_20 = ~local_20 + 1;
          }
          if ((int)local_30 < 1) {
            local_30 = ~local_30 + 1;
          }
          iVar16 = (int)(local_20 + local_30) >> 1;
          if ((int)local_30 < (int)local_20) {
            local_48 = local_20 * 2 - ((iVar16 - local_30) + 1);
          }
          else {
            local_48 = local_30 * 2 - ((iVar16 - local_20) + 1);
          }
          if ((((uVar9 == 0) || (local_48 <= local_38)) &&
              (iVar16 = map_in_bounds(x,y2), iVar16 != 0)) &&
             (((unit_types[units[unit].type].domain != 1 ||
               (iVar16 = tile_airbase_owner(x,y2), iVar16 < 0)) ||
              ((x == path_goal_x && (y2 == path_goal_y)))))) {
            terrain = tile_terrain(x,y2);
            iVar16 = tile_unit_owner(x,y2);
            if ((((iVar16 < 0) || (civ == iVar16)) &&
                ((((terrain == 10) == (uVar1 == 2) &&
                  (((iVar10 == 0 ||
                    (iVar17 = tile_in_enemy_zoc(x,y2,civ), iVar17 == 0)) ||
                   ((unit_types[units[unit].type].flags & 2) != 0)))) ||
                 (unit_types[units[unit].type].domain == 1)))) ||
               (((iVar17 = tile_city_owner(x,y2), iVar17 == civ && (x == iVar4))
                && (y2 == iVar5)))) {
              if (unit_types[units[unit].type].domain == '\0') {
                if (((uVar14 & 0x20) == 0) ||
                   (uVar18 = tile_improvements(x,y2), (uVar18 & 0x20) == 0)) {
                  if (((uVar11 & 0x10) == 0) ||
                     (uVar18 = tile_improvements(x,y2), (uVar18 & 0x10) == 0)) {
                    if ((((bVar2 & 0x80) != 0) &&
                        (pbVar13 = (byte *)tile_at(x,y2), (*pbVar13 & 0x80) != 0)) &&
                       (x = map_dx_wrapped(x2,x), x == 1)) {
                      if (y == y2 || y - y2 < 0) {
                        y2 = ~(y - y2) + 1;
                      }
                      else {
                        y2 = y - y2;
                      }
                      if (y2 == 1) {
                        local_58 = 4;
                        goto LAB_004ae320;
                      }
                    }
                    x = unit_max_moves(unit);
                    if ((int)(uint)cosmic.road_move_mult < x) {
                      local_58 = (int)(char)terrain_types[terrain].move_cost *
                                 (uint)cosmic.road_move_mult * 4;
                    }
                    else {
                      local_58 = (uint)cosmic.road_move_mult << 2;
                    }
                  }
                  else {
                    local_58 = 4;
                  }
                }
                else {
                  local_58 = 1;
                }
              }
              else {
                local_58 = (uint)cosmic.road_move_mult << 2;
              }
LAB_004ae320:
              local_58 = (local_48 * 4 + local_58 + local_20 + local_30) * 4;
              if ((local_48 != 0) && (-1 < iVar16)) {
                local_58++;
              }
              if (local_58 < local_18) {
                local_54 = local_24;
                local_18 = local_58;
              }
            }
          }
        }
        if (((-1 < (char)units[unit].last_dir) &&
            (((int)(char)units[unit].last_dir ^ 4U) == local_54)) &&
           ((unit_types[units[unit].type].domain != 1 && (units[unit].moves_used != '\0')
            ))) {
          local_54 = 0xffffffff;
          units[unit].orders = -1;
          if ((uVar9 == 0) || (((int)(short)units[unit].flags & 0x8000U) != 0)) {
            if (uVar9 != 0) {
              units[unit].flags = units[unit].flags & 0x7fff;
            }
            unit_exhaust_moves(unit);
          }
        }
        if (local_54 == 8) {
          units[unit].orders = -1;
          if ((uVar9 == 0) || (((int)(short)units[unit].flags & 0x8000U) != 0)) {
            if (uVar9 != 0) {
              units[unit].flags = units[unit].flags & 0x7fff;
            }
            unit_exhaust_moves(unit);
          }
          local_54 = 0xffffffff;
        }
      }
    }
  }
  path_debug_pending = 0;
  path_debug_requested = 0;
  return local_54;
}
#undef path_debug_pending
#undef path_debug_requested
#undef path_goal_x
#undef path_goal_y
#undef y2
#undef local_70
#undef local_58
#undef local_54
#undef local_48
#undef local_38
#undef local_30
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18

/* 004c42a0 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl unit_do_terrain_work(iptr unit,iptr param_2)

{
  char terrain2;
  char cVar2;
  byte bVar3;
  int x;
  int y;
  uint uVar6;
  byte *pbVar7;
  int iVar8;
  uint terrain;
  uptr uVar9;
  i32 uVar12;
  uptr uVar11;
  iptr unit2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = unit;
  local_8 = 1;
  terrain2 = units[unit].owner;
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  bVar3 = tile_terrain(x,y);
  terrain = (uint)bVar3;
  cVar2 = units[unit].orders;
  units[unit].orders = (i8)param_2;
  switch(param_2) {
  case 4:
    local_8 = (int)(char)terrain_types[terrain].move_cost / 2 + 3;
    break;
  case 5:
    uVar6 = tile_improvements(x,y);
    local_8 = ((-(uint)((uVar6 & 0x10) == 0) & 0xfffffffe) + 4) *
              (int)(char)terrain_types[terrain].move_cost;
    pbVar7 = (byte *)tile_at(x,y);
    if ((*pbVar7 & 0x80) != 0) {
      local_8 += 2;
    }
    break;
  case 6:
    local_8 = (int)(char)terrain_types[terrain].irrigate_turns;
    break;
  case 7:
    local_8 = (int)(char)terrain_types[terrain].mine_turns;
    break;
  case 8:
    local_8 = (int)(char)terrain_types[terrain].move_cost * (uint)cosmic.transform_time;
    break;
  case 9:
    local_8 = 4;
    break;
  case 10:
    local_8 = 4;
  }
  unit_blink_active = 0;
  unit_exhaust_moves(unit);
  unit3 = -1;
  unit = unit_stack_first(unit);
  do {
    if (unit < 0) {
LAB_004c44ea:
      if (-1 < unit3) {
        units[unit2].counter += units[unit3].counter;
        units[unit3].counter = '\0';
      }
      units[unit2].counter++;
      if (units[unit2].type == 1) {
        units[unit2].counter++;
      }
      if ((char)units[unit2].counter < local_8) {
        map_redraw_area_all_views(x,y,0,human_civ,1);
        if (units[unit2].orders != cVar2) {
          city_window_on_unit_change((FrameWindow *)&city_window,unit2,-99,-99);
        }
      }
      else {
        for (unit = unit_stack_first(unit2); -1 < unit;
            unit = unit_next_in_stack(unit)) {
          if ((unit_types[units[unit].type].role == 5) && (units[unit].orders == param_2)
             ) {
            units[unit].counter = '\0';
            units[unit].orders = -1;
          }
        }
        switch(param_2) {
        case 4:
          iVar8 = tile_city_owner(x,y);
          if (iVar8 < 0) {
            tile_set_improvements(x,y,0x40,1,1);
            tile_set_improvements(x,y,2,0,1);
          }
          break;
        case 5:
          terrain = tile_improvements(x,y);
          if (((terrain & 0x10) == 0) && (iVar8 = tile_city_owner(x,y), iVar8 < 0)) {
            tile_set_improvements(x,y,0x10,1,1);
          }
          else {
            iVar8 = civ_has_advance((int)terrain2,0x43);
            if (iVar8 != 0) {
              tile_set_improvements(x,y,0x30,1,1);
            }
          }
          break;
        case 6:
        case 7:
          if (*(char *)(param_2 + ADDR(0x627cc8, ((u8 *)&terrain_types + 8)) + terrain * 0x18) < '\0') {
            if (param_2 == 6) {
              terrain = tile_improvements(x,y);
              if ((terrain & 4) == 0) {
                tile_set_improvements(x,y,8,0,1);
                tile_set_improvements(x,y,4,1,1);
              }
              else {
                iVar8 = civ_has_advance((int)terrain2,0x46);
                if (iVar8 != 0) {
                  tile_set_improvements(x,y,0xc,1,1);
                }
              }
            }
            else {
              tile_set_improvements(x,y,4,0,1);
              tile_set_improvements(x,y,8,1,1);
            }
          }
          else {
            tile_set_terrain(x,y,(int)*(char *)(param_2 + ADDR(0x627cc8, ((u8 *)&terrain_types + 8)) + terrain * 0x18),1);
            terrain2 = *(char *)(param_2 + ADDR(0x627cc8, ((u8 *)&terrain_types + 8)) + terrain * 0x18);
            if ((terrain_types[terrain2].irrigate_to != -2) &&
               (terrain = tile_improvements(x,y), (terrain & 4) != 0)) {
              tile_set_improvements(x,y,0xc,0,1);
            }
            if ((terrain_types[terrain2].mine_to != -2) &&
               (uVar12 = tile_improvements(x,y), ((byte)uVar12 & 0xc) == 8)) {
              tile_set_improvements(x,y,8,0,1);
            }
          }
          break;
        case 8:
          tile_set_terrain(x,y,(int)terrain_types[terrain].transform_to,1);
          terrain2 = terrain_types[terrain].transform_to;
          if ((terrain_types[terrain2].irrigate_to != -2) &&
             (uVar9 = tile_improvements(x,y), (uVar9 & 4) != 0)) {
            tile_set_improvements(x,y,0xc,0,1);
          }
          if ((terrain_types[terrain2].mine_to != -2) &&
             (uVar12 = tile_improvements(x,y), ((byte)uVar12 & 0xc) == 8)) {
            tile_set_improvements(x,y,8,0,1);
          }
          break;
        case 9:
          uVar11 = tile_improvements(x,y);
          if ((uVar11 & 0x80) != 0) {
            game.polluted_tiles--;
          }
          tile_set_improvements(x,y,0x80,0,1);
          break;
        case 10:
          iVar8 = tile_city_owner(x,y);
          if (iVar8 < 0) {
            tile_set_improvements(x,y,0x42,1,1);
          }
        }
        tile_update_known(x,y,(int)units[unit2].owner);
        map_redraw_area_all_views(x,y,1,human_civ,1);
        if (units[unit2].owner == human_civ) {
          status_redraw(1);
        }
        if (units[unit2].orders != cVar2) {
          city_window_on_unit_change((FrameWindow *)&city_window,unit2,-99,-99);
        }
        city_window_refresh_if_near((C_004083b0_4 *)&city_window,x,y);
      }
      return;
    }
    if (((unit_types[units[unit].type].role == 5) && (units[unit].orders == param_2)) &&
       (unit != unit2)) {
      unit3 = unit;
      goto LAB_004c44ea;
    }
    unit = unit_next_in_stack(unit);
  } while( true );
}
#undef human_civ
#undef unit_blink_active
#undef unit3
#undef local_8

/* 004c4ada auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_c (*(i8 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
void __cdecl unit_set_fortified(iptr unit)

{
  iptr city;
  i32 uVar1;
  iptr city2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  units[unit].orders = 2;
  if ((((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) == 0) &&
     (-1 < units[unit].home_city)) {
    city = city_at((int)units[unit].x,(int)units[unit].y);
    if (city < 0) {
      uVar1 = tile_improvements((int)units[unit].x,(int)units[unit].y);
      if (((((byte)uVar1 & 0x42) == 0x40) &&
          (city2 = city_find_nearest((int)units[unit].x,(int)units[unit].y,
                                      (int)units[unit].owner,0xffffffff,-1), -1 < city2)) &&
         (2 < cities[city2].size)) {
        if (units[unit].home_city == -1) {
          local_8 = 0xffffffff;
        }
        else {
          local_8 = (uint)(byte)units[unit].home_city;
        }
        local_c = (i8)city2;
        units[unit].home_city = local_c;
        if (-1 < (int)local_8) {
          city_window_refresh_if_city((FrameWindow *)&city_window,local_8);
        }
        city_window_refresh_if_city((FrameWindow *)&city_window,city2);
      }
    }
    else if (2 < cities[city].size) {
      if (units[unit].home_city == -1) {
        local_8 = 0xffffffff;
      }
      else {
        local_8 = (uint)(byte)units[unit].home_city;
      }
      local_c = (i8)city;
      units[unit].home_city = local_c;
      if (-1 < (int)local_8) {
        city_window_refresh_if_city((FrameWindow *)&city_window,local_8);
      }
      city_window_refresh_if_city((FrameWindow *)&city_window,city);
    }
  }
  map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
  city_window_on_unit_change((FrameWindow *)&city_window,unit,-99,-99);
  return;
}
#undef unit_blink_active
#undef local_c
#undef local_8

/* 004c4d1e auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_found_city(iptr unit,iptr city,iptr param_3)

{
  int x;
  int y;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  if ((game.reveal_map != '\0') || (units[unit].owner == human_civ)) {
    mapviews_ensure_visible(x,y,(int)units[unit].owner);
  }
  if ((-1 < city) ||
     (city = city_create(x,y,(int)units[unit].owner), -1 < city)) {
    if (param_3 != 0) {
      FUN_005f22d0((iptr)&cities[city].name,param_3);
    }
    unit_delete(unit,1);
    tile_set_improvements(x,y,0x7c,0,1);
    for (local_10 = 1; local_10 < 8; local_10++) {
      tile_update_known(x,y,local_10);
    }
    map_redraw_area_all_views(x,y,1,human_civ,1);
  }
  return;
}
#undef human_civ
#undef local_10

/* 004c4e6d auto */
#define path_owner_civ (*(int *)((u8 *)&g.d_0062d044))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
void __cdecl unit_goto_step(iptr unit)

{
  byte civ;
  byte bVar2;
  uptr uVar3;
  int iVar4;
  
  unit_blink_active = 0;
  civ = units[unit].owner;
  bVar2 = units[unit].orders;
  path_owner_civ = (int)(char)civ;
  if ((bVar2 & 0x10) != 0) {
    path_owner_civ = -1;
  }
  uVar3 = unit_goto_next_dir(unit);
  if (((int)uVar3 < 0) || (uVar3 == 8)) {
    if ((uVar3 != 8) && (units[unit].orders = -1, unit_types[units[unit].type].role == 4)
       ) {
      units[unit].counter = (byte)game.turn & 7;
    }
  }
  else {
    iVar4 = unit_move_dir(unit,uVar3,3);
    if (iVar4 == 0) {
      return;
    }
    units[unit].flags = units[unit].flags & 0xff7f;
    if (((units[unit].x == units[unit].goto_x) && (units[unit].y == units[unit].goto_y))
       && ((bVar2 & 0x10) == 0)) {
      units[unit].orders = -1;
      units[unit].flags = units[unit].flags | 0x80;
      if (((1 << (civ & 0x1f) & (uint)game.human_players) == 0) &&
         (((unit_types[units[unit].type].domain == 2 ||
           (('\t' < (char)units[unit].field_0e &&
            (iVar4 = tile_adjacent_nonallied_unit((int)units[unit].x,(int)units[unit].y,(int)(char)civ
                                       ), iVar4 == 0)))) &&
          (unit_exhaust_moves(unit), unit_types[units[unit].type].role == 4)))) {
        units[unit].counter = (byte)game.turn & 7;
      }
    }
  }
  path_owner_civ = 0xffffffff;
  return;
}
#undef path_owner_civ
#undef unit_blink_active

/* 004c50d0 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl unit_pillage(iptr unit,int param_2)

{
  byte civ;
  int x;
  int y;
  iptr city2;
  iptr iVar5;
  int city;
  byte *pbVar7;
  
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  civ = units[unit].owner;
  city2 = city_find_nearest(x,y,-1,0xffffffff,-1);
  if ((((city2 < 0) || ((int)cities[city2].owner == (int)(char)civ)) ||
      ((1 << (civ & 0x1f) & (uint)game.human_players) == 0)) ||
     (iVar5 = diplo_confirm_attack((int)(char)civ,(int)cities[city2].owner,0xe), iVar5 == 0)) {
    city = tile_at(x,y);
    pbVar7 = (byte *)(city + 1);
    if (param_2 < 1) {
      if ((units[unit].type == '\t') && ((*pbVar7 & 0x10) != 0)) {
        if ((*pbVar7 & 0x20) == 0) {
          tile_set_improvements(x,y,0x10,0,1);
        }
        else {
          tile_set_improvements(x,y,0x20,0,1);
        }
      }
      else if ((*pbVar7 & 0xc) == 0) {
        if ((*pbVar7 & 0x40) == 0) {
          if ((*pbVar7 & 0x20) == 0) {
            tile_set_improvements(x,y,0x10,0,1);
          }
          else {
            tile_set_improvements(x,y,0x20,0,1);
          }
        }
        else {
          tile_set_improvements(x,y,0x42,0,1);
        }
      }
      else if ((*pbVar7 & 8) == 0) {
        tile_set_improvements(x,y,4,0,1);
      }
      else {
        tile_set_improvements(x,y,8,0,1);
      }
    }
    else {
      tile_set_improvements(x,y,param_2,0,1);
    }
    city = city_find_nearest(x,y,-1,0xffffffff,-1);
    if (-1 < city) {
      tile_update_known(x,y,(int)units[unit].owner);
      tile_update_known(x,y,(int)cities[city].owner);
      diplo_set_treaty_flags((int)units[unit].owner,(int)cities[city].owner,0x2000);
      if (cities[city].owner != units[unit].owner) {
        civ_add_ai_goal((int)units[unit].owner,x,y,0,4);
      }
    }
    map_redraw_area_all_views(x,y,1,human_civ,1);
    unit_exhaust_moves(unit);
  }
  return;
}
#undef human_civ

/* 004c5408 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl unit_execute_orders(iptr unit)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  switch(units[unit].orders) {
  case 1:
    unit_set_fortified(unit);
    break;
  default:
    local_8 = 0;
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case '\t':
  case '\n':
    unit_do_terrain_work(unit,(int)units[unit].orders);
    break;
  case 11:
  case 27:
    unit_goto_step(unit);
  }
  return local_8;
}
#undef local_8

/* 004c54da auto */
#define y3 (*(int *)(frame_ + FRAME_OFF(0)))
#define y2 (*(int *)(frame_ + FRAME_OFF(4)))
#define x3 (*(int *)(frame_ + FRAME_OFF(8)))
#define x2 (*(int *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(32)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define local_c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
void __cdecl unit_go_home(iptr unit)

{
  byte unit_type;
  byte civ;
  u8 uVar3;
  u8 uVar4;
  int x;
  int y;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  iptr unit2;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = unit;
  local_8 = 999;
  unit_type = units[unit].type;
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  civ = units[unit].owner;
  local_20 = -1;
  if (unit_types[units[unit].type].domain == '\0') {
    local_20 = tile_landmass(x,y);
  }
  nearest_city_dist = 9999;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
        ((local_20 < 0 ||
         (iVar8 = tile_landmass((int)cities[city].x,(int)cities[city].y), iVar8 == local_20)
         ))) && (iVar8 = map_distance(x,y,(int)cities[city].x,
                                            (int)cities[city].y), iVar8 < nearest_city_dist)) {
      city2 = city;
      nearest_city_dist = iVar8;
    }
  }
  if (unit_types[units[unit].type].domain == 1) {
    for (unit = 0; unit < game.num_units; unit++) {
      if (((units[unit].id != 0) && (units[unit].owner == civ)) &&
         ((((unit_types[units[unit].type].flags & 0x80) != 0 ||
           (((unit_types[unit_type].flags & 0x1000) != 0 &&
            ((unit_types[units[unit].type].flags & 8) != 0)))) &&
          (iVar8 = map_distance(x,y,(int)units[unit].x,(int)units[unit].y),
          iVar8 < local_8)))) {
        x3 = (int)units[unit].x;
        y3 = (int)units[unit].y;
        local_8 = iVar8;
      }
    }
    iVar8 = tile_airbase_owner(x,y);
    if (-1 < iVar8) {
      if ((1 << (civ & 0x1f) & (uint)game.human_players) != 0) {
        return;
      }
      unit_exhaust_moves(unit2);
      return;
    }
  }
  local_c = 999;
  y2 = y;
  x2 = x;
  if (nearest_city_dist < 999) {
    x2 = (int)cities[city2].x;
    y2 = (int)cities[city2].y;
    local_c = nearest_city_dist;
  }
  if (local_8 < local_c) {
    x2 = x3;
    y2 = y3;
    local_c = local_8;
  }
  if (local_c < 999) {
    if (((1 << (civ & 0x1f) & (uint)game.human_players) != 0) &&
       (unit_types[units[unit2].type].range != '\0')) {
      uVar3 = unit_types[units[unit2].type].range;
      uVar4 = units[unit2].counter;
      iVar8 = unit_max_moves(unit2);
      iVar9 = unit_moves_left(unit2);
      uVar11 = (uint)cosmic.road_move_mult;
      iVar10 = map_distance(x,y,x2,y2);
      if ((((int)(char)uVar3 - ((char)uVar4 + 1)) * iVar8 + iVar9) / (int)uVar11 < iVar10) {
        return;
      }
    }
    if ((x == x2) && (y == y2)) {
      unit_exhaust_moves(unit2);
    }
    else {
      units[unit2].orders = 11;
      units[unit2].goto_x = (i16)x2;
      units[unit2].goto_y = (i16)y2;
    }
  }
  return;
}
#undef y3
#undef y2
#undef x3
#undef x2
#undef city
#undef local_20
#undef city2
#undef local_c
#undef local_8

/* 004c5fae auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(24)))
i32 __cdecl spy_try_escape(iptr unit,int param_2,iptr civ)

{
  byte civ2;
  int civ3;
  uint uVar3;
  int x;
  int y;
  iptr city;
  uint uVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = units[unit].owner;
  civ3 = (int)(char)civ2;
  if (-1 < param_2) {
    units[unit].moves_used += cosmic.road_move_mult;
  }
  if (units[unit].type == '/') {
    local_8 = (param_2 < 0) + 2;
    if ((units[unit].flags & 0x2000) != 0) {
      local_8 = local_8 * 2;
    }
    if (0 < param_2) {
      local_8 = local_8 / 2;
    }
    if (local_8 < 2) {
      uVar3 = _rand();
      uVar6 = (int)uVar3 >> 0x1f;
      if (((uVar3 ^ uVar6) - uVar6 & 1 ^ uVar6) == uVar6) {
        local_8++;
      }
    }
    if (local_8 == 1 || (int)(local_8 - 1) < 0) {
      local_1c = 0;
    }
    else {
      local_1c = _rand();
      local_1c = local_1c % (int)local_8;
    }
    if (local_1c != 0) {
      x = (int)units[unit].x;
      y = (int)units[unit].y;
      city = city_find_nearest(x,y,civ3,0xffffffff,-1);
      if (-1 < city) {
        unit_relocate(unit,(int)cities[city].x,(int)cities[city].y,1);
        unit_exhaust_moves(unit);
        map_redraw_tile_all_views(x,y);
        map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
        if (2 < game.multiplayer) {
          net_send_state_diff(0xff,2,0,0,0);
          net_send_message(0x72,0xff,x,y,0,0,0,0,0,0);
          net_send_message(0x72,0xff,(int)cities[city].x,(int)cities[city].y,0,0,0,0,0,0);
        }
        text_set_string_arg(1,(iptr)&cities[city].name);
      }
      if (-1 < param_2) {
        if ((autoplay_active == 0) && ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0)) {
          if ((units[unit].flags & 0x2000) == 0) {
            if (human_civ == civ3) {
              popup_game_with_sprite(ADDR(0x62dd54, ((u8 *)&g.d_0062dd54)),(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),8
                                );
            }
            else if (2 < game.multiplayer) {
              net_send_text_args(0x26,*(i32 *)
                                       (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                                 2,0,(uint)units[unit].type,8);
            }
          }
          else if (human_civ == civ3) {
            popup_game_with_sprite(ADDR(0x62dd5c, ((u8 *)&g.d_0062dd5c)),(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),8);
          }
          else if (2 < game.multiplayer) {
            net_send_text_args(0x27,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),2,
                               0,(uint)units[unit].type,8);
          }
        }
        units[unit].flags = units[unit].flags | 0x2000;
      }
      return 0;
    }
    if (((autoplay_active == 0) && ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
       (-1 < param_2)) {
      if (human_civ == civ3) {
        popup_game_with_sprite(ADDR(0x62dd64, ((u8 *)&g.d_0062dd64)),(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),8);
      }
      else if (game.multiplayer == 3) {
        net_send_text_args(0x28,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),0,0,
                           (uint)units[unit].type,8);
      }
    }
  }
  unit_destroy_redraw(unit,1);
  if ((0 < civ) && (-1 < param_2)) {
    diplo_espionage_incident(civ3,civ);
  }
  return 1;
}
#undef autoplay_active
#undef human_civ
#undef local_1c
#undef local_8

/* 004c64aa auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
i32 __cdecl spy_check_caught(iptr unit,iptr civ)

{
  byte civ2;
  byte unit_type;
  int iVar3;
  i32 uVar4;
  
  civ2 = units[unit].owner;
  unit_type = units[unit].type;
  iVar3 = spy_try_escape(unit,0xffffffff,civ);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    if ((autoplay_active == 0) && ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0)) {
      popup_game_with_sprite(ADDR(0x62dd70, ((u8 *)&g.d_0062dd70)),(iptr)(&unit_sprites + (uint)unit_type * 0x3c),8);
    }
    uVar4 = 1;
  }
  return uVar4;
}
#undef autoplay_active

/* 004c654d auto */
uint __cdecl spy_confirm_treaty_breach(iptr civ,iptr param_2)

{
  uint uVar1;
  int iVar2;
  
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    uVar1 = 0;
  }
  else if ((*(byte *)&civs[civ].treaties[param_2] & 0xe) == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = popup_game(ADDR(0x62dd78, ((u8 *)&g.d_0062dd78)));
    uVar1 = (uint)(iVar2 != 1);
  }
  return uVar1;
}

/* 004c6bf5 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_3f8 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_3f4 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_3f0 (*(int (*)[16])(frame_ + FRAME_OFF(8)))
#define civ (*(uptr *)(frame_ + FRAME_OFF(72)))
#define local_3ac (*(int *)(frame_ + FRAME_OFF(76)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(80)))
#define civ3 (*(uptr *)(frame_ + FRAME_OFF(84)))
#define local_3a0 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_39c (*(int *)(frame_ + FRAME_OFF(92)))
#define unit_type3 (*(uint *)(frame_ + FRAME_OFF(96)))
#define local_394 (*(int *)(frame_ + FRAME_OFF(100)))
#define unit_type (*(uptr *)(frame_ + FRAME_OFF(104)))
#define local_38c (*(uint *)(frame_ + FRAME_OFF(108)))
#define local_388 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_384 (*(Dialog *)(frame_ + FRAME_OFF(116)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(872)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(876)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(880)))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(884)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(888)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(892)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(896)))
#define improvement2 (*(iptr *)(frame_ + FRAME_OFF(900)))
#define local_70 (*(i8 (*)[80])(frame_ + FRAME_OFF(904)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(984)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(988)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(992)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(996)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1000)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1004)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1008)))
void __cdecl spy_city_mission(iptr unit,iptr city)

{
  uint *puVar1;
  u8 uVar2;
  iptr unit2;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool unit_type2;
  iptr iVar8;
  i32 uVar9;
  uptr civ4;
  iptr iVar9;
  i8 frame_[FRAME_OFF(1016)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_384,0x4000);
  local_8 = 0;
  unit_blink_active = 0;
  civ = (uptr)units[unit].owner;
  civ2 = (uptr)cities[city].owner;
  unit_type3 = (uint)units[unit].type;
  diplo_set_treaty_flags(civ,civ2,1);
  unit_type2 = units[unit].type != '/';
  if (unit_type2) {
    local_38c = 0;
  }
  else {
    local_38c = 1;
  }
  local_38c = (uint)!unit_type2;
  if (((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
     (human_civ == civ)) {
    unit2 = civ_get_adjective(civ);
    text_set_string_arg(0,unit2);
    text_set_label_arg(1,unit_types[units[unit].type].name);
    text_set_string_arg(2,(iptr)&cities[city].name);
    dlg_load_game_section(&local_384,ADDR(0x62dd90, ((u8 *)&g.d_0062dd90)),1);
    dialog_add_sprite
              ((DialogOptionList *)&local_384,(iptr)(&unit_sprites + (uint)units[unit].type * 0x3c)
               ,0,0);
    dialog_set_image_zoom((DialogWindowView *)&local_384,8);
    iVar4 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x62dd98, ((u8 *)&g.d_0062dd98)));
    if (iVar4 != 0) goto switchD_004c94cc_default;
    text_read_line(1);
    if (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) == 0) &&
       (iVar4 = civ_has_wonder(human_civ,0x18), iVar4 == 0)) {
      if (local_38c != 0) {
        str_append_space(ADDR(0x679640, ((u8 *)&g.d_00679640)));
        str_append_lparen(ADDR(0x679640, ((u8 *)&g.d_00679640)));
        text_append_label(0xed);
        str_append_rparen(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      }
      dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
    }
    text_read_line(1);
    if (local_38c != 0) {
      str_append_space(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      str_append_lparen(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      text_append_label(0xed);
      str_append_rparen(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),1,0);
    text_read_line(1);
    if (((cities[city].flags & 8) == 0) || (local_38c != 0)) {
      dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),2,0);
    }
    text_read_line(1);
    dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),3,0);
    text_read_line(1);
    if ((local_38c != 0) && (1 < cities[city].size)) {
      dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),4,0);
    }
    text_read_line(1);
    if ((((local_38c != 0) && (iVar4 = civ_has_advance(civ,0x49), iVar4 != 0)) &&
        (iVar4 = civ_has_advance(civ,0x3a), iVar4 != 0)) &&
       (iVar4 = wonder_get_city(0x17), iVar4 != -1)) {
      dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),5,0);
    }
    text_read_line(1);
    iVar4 = city_has_improvement(city,1);
    if (iVar4 == 0) {
      dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
    }
    if (((2 < game.multiplayer) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
       && ((iVar4 = city_has_improvement(city,1), iVar4 != 0 &&
           ((*(byte *)(civ * 0x594 + ADDR(0x64c6c3, ((u8 *)&civs + 35)) + civ2 * 4) & 1) == 0)))) {
      uVar9 = 0;
      iVar8 = 7;
      unit2 = label_string(*(i32 *)(label_string_ids + 0xd28));
      dialog_add_option((DialogOptionList *)&local_384,unit2,iVar8,uVar9);
    }
    text_close_file();
    local_3ac = dlg_show_modal(&local_384,0);
    if (local_3ac < 0) goto switchD_004c94cc_default;
  }
  else {
    local_3ac = 2;
    if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) &&
        (iVar4 = _rand(), iVar4 % 3 == 0)) && (local_38c != 0)) {
      local_3ac = 4;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) {
      local_3ac = 2;
    }
    if ((((3 < game.difficulty) || ((game.difficulty == 3 && (5 < civs[civ2].field_1c))))
        && (local_3ac == 2)) &&
       (((civs[civ].treaties[civ2] & 0x2010) != 0 &&
        (civs[civ2].government != 6)))) {
      local_3ac = 6;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      local_3ac = 2;
    }
    if (((((cities[city].flags & 8) != 0) && (local_38c == 0)) && (local_3ac == 2)) &&
       (local_3ac = 3, (*(byte *)&civs[civ].treaties[civ2] & 0xe) != 0)) {
      local_3ac = 0;
    }
  }
LAB_004c72a8:
  spy_last_mission = local_3ac;
  switch(local_3ac) {
  case 0:
    if ((*(byte *)&civs[civ].treaties[civ2] & 0x80) == 0) {
      puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
      *puVar1 = *puVar1 | 0x80;
      if ((human_civ == civ) || (human_civ == civ2)) {
        snd_play_effect(0x44,0,0,0);
      }
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        unit_destroy_redraw(unit,1);
      }
      else {
        intel_report_show(civ,civ2);
        if (local_38c == 0) {
          unit_delete(unit,1);
        }
        else {
          units[unit].moves_used++;
        }
      }
      if ((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
        unit2 = civ_name_plural(civ);
        text_set_string_arg(0,unit2);
        if ((game.multiplayer < 3) || (human_civ == civ2)) {
          popup_game_with_sprite(ADDR(0x62dda4, ((u8 *)&g.d_0062dda4)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
        }
        else {
          net_send_text_args(0x55,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),1
                             ,0,0,0);
        }
      }
      break;
    }
    local_3ac = 1;
    goto LAB_004c72a8;
  case 1:
    if ((human_civ == civ) || (human_civ == civ2)) {
      snd_play_effect(0x44,1,0,0);
    }
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      unit_destroy_redraw(unit,1);
    }
    else {
      city_window_open((C_004083b0_12c *)&city_window,city);
      if (local_38c == 0) {
        spy_try_escape(unit,0,-1);
      }
      else if ((cities[city].flags & 0x400000) == 0) {
        units[unit].moves_used++;
      }
      cities[city].flags = cities[city].flags | 0x400000;
    }
    if ((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
      unit2 = civ_name_plural(civ);
      text_set_string_arg(0,unit2);
      text_set_string_arg(1,(iptr)&cities[city].name);
      if ((game.multiplayer < 3) || (human_civ == civ2)) {
        popup_game_with_sprite(ADDR(0x62ddb4, ((u8 *)&g.d_0062ddb4)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
      }
      else {
        net_send_text_args(0x56,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),2,0
                           ,0,0);
      }
    }
    break;
  case 2:
    iVar4 = spy_confirm_treaty_breach(civ,civ2);
    if (iVar4 != 0) break;
    advance = -1;
    iVar4 = _rand();
    local_8c = iVar4 % 100;
    for (local_3a0 = 0; local_3a0 < 100; local_3a0++) {
      advance2 = (local_8c + local_3a0) % 100;
      if ((((advances[advance2].preq[0] != -2) || (advances[advance2].preq[1] != -2)) &&
          (iVar4 = civ_has_advance(civ,advance2), iVar4 == 0)) &&
         (iVar4 = civ_has_advance(civ2,advance2), iVar4 != 0)) {
        advance = advance2;
        iVar4 = spaceship_race_active();
        if ((((iVar4 == 0) ||
             ((game.difficulty < 2 &&
              ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)))) ||
            (improvements[0x23].preq == advance2)) ||
           (((improvements[0x24].preq == advance2 || (improvements[0x25].preq == advance2)) ||
            (advance2 == 0x20)))) break;
      }
    }
    if (-1 < advance) {
      local_88 = 0;
      if ((cities[city].flags & 8) == 0) {
        if (((autoplay_active == 0) && (local_38c != 0)) &&
           ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
          local_3ac = popup_game_sprite_flags(ADDR(0x62dddc, ((u8 *)&g.d_0062dddc)),1,(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
          if (local_3ac < 0) break;
          if (local_3ac == 1) {
            iVar4 = spy_check_caught(unit,civ2);
            if (iVar4 == 0) {
              if (human_civ == civ) {
                snd_play_effect(0x44,1,0,0);
              }
              civ_steal_advance(civ,civ2);
              spy_try_escape(unit,1,civ2);
              cities[city].flags = cities[city].flags | 8;
            }
            break;
          }
        }
      }
      else {
        if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)
           ) {
          unit2 = civ_name_plural(civ2);
          text_set_string_arg(0,unit2);
          text_set_string_arg(1,(iptr)&cities[city].name);
          local_3ac = popup_game_with_city(ADDR(0x62ddd0, ((u8 *)&g.d_0062ddd0)),city);
          if (local_3ac != 1) break;
        }
        iVar4 = spy_check_caught(unit,civ2);
        if (iVar4 != 0) break;
        local_88 = 1;
      }
      unit3 = unit;
      local_14 = 0;
      unit = tile_first_unit((int)cities[city].x,(int)cities[city].y);
      goto LAB_004c7ad5;
    }
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
      units[unit].moves_used += cosmic.road_move_mult;
      if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0))
      {
        popup_game_with_sprite(ADDR(0x62ddc8, ((u8 *)&g.d_0062ddc8)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
      }
      break;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 0xe) == 0) {
      local_3ac = 3;
    }
    else {
      local_3ac = 0;
    }
    goto LAB_004c72a8;
  case 3:
    local_88 = 0;
    iVar4 = spy_confirm_treaty_breach(civ,civ2);
    if (iVar4 != 0) break;
    str_clear((iptr)local_70);
    if (cities[city].building < '\0') {
      str_append_string_id((iptr)local_70,improvements[-(int)cities[city].building].name);
    }
    else {
      str_append_string_id((iptr)local_70,unit_types[cities[city].building].name);
    }
    improvement2 = 0;
    local_8c = _rand();
    local_8c = local_8c % 0x27;
    improvement = 0;
    goto LAB_004c7f43;
  case 4:
    iVar4 = spy_confirm_treaty_breach(civ,civ2);
    if (iVar4 == 0) {
      if (cities[city].size < 2) {
        cities[city].food_box = 0;
      }
      else {
        cities[city].size--;
      }
      city_reveal_to_civ(city,civ);
      map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
      text_set_string_arg(0,(iptr)&cities[city].name);
      unit2 = civ_get_adjective(civ);
      text_set_string_arg(1,unit2);
      if ((((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
          && (2 < game.multiplayer)) && (human_civ != civ2)) {
        net_send_text_args(0x5b,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),2,0
                           ,0,0);
      }
      if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0))
      {
        snd_play_effect(0x44,1,0,0);
        popup_game_with_sprite(ADDR(0x62de50, ((u8 *)&g.d_0062de50)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
      }
      civ4 = civ2;
      uVar5 = _rand();
      uVar6 = (int)uVar5 >> 0x1f;
      spy_try_escape(unit,((uVar5 ^ uVar6) - uVar6 & 1 ^ uVar6) - uVar6,civ4);
    }
    break;
  case 5:
    if (((((autoplay_active == 0) &&
          (iVar4 = popup_game_with_sprite(ADDR(0x62de5c, ((u8 *)&g.d_0062de5c)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8),
          iVar4 == 1)) && (iVar4 = spy_check_caught(unit,civ2), iVar4 == 0)) &&
        ((iVar4 = spy_check_caught(unit,civ2), iVar4 == 0 &&
         (iVar4 = spy_check_caught(unit,civ2), iVar4 == 0)))) &&
       ((iVar4 = city_has_improvement(city,1), iVar4 == 0 ||
        (iVar4 = spy_check_caught(unit,civ2), iVar4 == 0)))) {
      unit_nuclear_attack(civ,(int)cities[city].x,(int)cities[city].y,0);
      text_set_string_arg(0,(iptr)&cities[city].name);
      unit2 = civ_get_adjective(civ);
      text_set_string_arg(1,unit2);
      unit2 = civ_name_plural(civ);
      text_set_string_arg(2,unit2);
      text_clear();
      text_append(ADDR(0x62de6c, ((u8 *)&g.d_0062de6c)));
      local_3f0[0xf] = 0;
      if (civs[civ].government != 4) {
        local_1c = 2;
        if ((units[unit].flags & 0x2000) != 0) {
          local_1c = 4;
        }
        if (local_1c == 1 || local_1c - 1 < 0) {
          local_3f8 = 0;
        }
        else {
          local_3f8 = _rand();
          local_3f8 = local_3f8 % local_1c;
        }
        if (local_3f8 == 0) {
          text_append(ADDR(0x62de78, ((u8 *)&g.d_0062de78)));
          local_3f0[0xf] = 1;
          for (civ3 = 1; (int)civ3 < 8; civ3++) {
            if (civ != civ3) {
              civ_adjust_attitude(civ3,civ,100);
              diplo_set_treaty_flags(civ,civ3,0x2000);
            }
          }
        }
      }
      popup_game_with_improvement(ADDR(0x679640, ((u8 *)&g.d_00679640)),0x3e,8);
      if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) && (2 < game.multiplayer)
         ) {
        if (local_3f0[0xf] == 0) {
          net_send_text_args(0x5c,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3
                             ,0,0,0);
        }
        else {
          net_send_text_args(0x5d,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3
                             ,0,0,0);
        }
      }
    }
    break;
  case 6:
    if (civs[civ2].government == 6) {
      if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0))
      {
        popup_game_with_sprite(ADDR(0x62de7c, ((u8 *)&g.d_0062de7c)),ADDR(0x6469e0, ((u8 *)&g.d_006469e0)),0);
      }
      break;
    }
    local_7c = civ_distance_to_capital(civ2,(int)units[unit].x,(int)units[unit].y);
    if (local_7c < 2) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) break;
      local_3ac = 2;
    }
    else {
      if ((civs[civ2].government == 3) && (9 < local_7c)) {
        local_7c = 10;
      }
      iVar4 = city_has_improvement(city,7);
      if (iVar4 != 0) {
        local_7c = local_7c / 2;
      }
      local_388 = (int)cities[city].size * ((civs[civ2].gold + 1000) / (local_7c + 3));
      if (local_388 < 0) {
        local_388 = 30000;
      }
      if ((cities[city].flags & 1) != 0) {
        local_388 = local_388 / 2;
      }
      iVar4 = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
      if (iVar4 < 0) {
        local_388 = local_388 / 2;
      }
      if ((int)cities[city].founder == civ) {
        local_388 = local_388 / 2;
      }
      if (local_38c != 0) {
        if ((units[unit].flags & 0x2000) == 0) {
          local_388 -= local_388 / 6;
        }
        else {
          local_388 -= local_388 / 3;
        }
      }
      unit_type2 = (*(byte *)&civs[civ].treaties[civ2] & 0xe) == 0;
      if (unit_type2) {
        local_18 = 0;
      }
      else {
        local_18 = 1;
      }
      local_18 = (uint)!unit_type2;
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
LAB_004c8f6f:
        if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)
           ) {
          text_set_string_arg(0,(iptr)&cities[city].name);
          text_set_number_arg(0,local_388);
          dialog_load_game_text(&local_384,ADDR(0x62de88, ((u8 *)&g.d_0062de88)));
          if (local_388 <= civs[civ].gold) {
            iVar4 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x62de94, ((u8 *)&g.d_0062de94)));
            if (iVar4 != 0) break;
            text_read_line(1);
            dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
            text_read_line(1);
            if (local_18 == 0) {
              dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),1,0);
            }
            text_read_line(1);
            if (local_18 != 0) {
              dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),1,0);
            }
            text_read_line(1);
            if (((local_18 != 0) && (local_388 * 2 <= civs[civ].gold)) && (local_388 < 0x3a99)
               ) {
              dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),2,0);
            }
            text_close_file();
          }
          local_3ac = dlg_show_modal(&local_384,0);
        }
        else {
          local_3ac = 1;
        }
        if (0 < local_3ac) {
          civs[civ].gold -= local_388 * local_3ac;
          civs[civ].field_1c += 2;
          if (human_civ == civ) {
            status_draw_info(1);
          }
          spy_try_escape(unit,0,0);
          if (local_3ac == 1) {
            diplo_espionage_incident(civ,civ2);
          }
          if (local_3ac == 2) {
            puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
            *puVar1 = *puVar1 | 0x10;
            cities[city].founder = (byte)civ;
          }
          if ((human_civ == civ) || (human_civ == civ2)) {
            snd_play_effect(0x44,1,0,0);
          }
          city_incite_transfer(city,civ,local_3ac);
        }
        break;
      }
      local_394 = local_388 * 2;
      if (((local_394 <= civs[civ].gold) && (local_18 == 0)) && (-1 < local_394))
      goto LAB_004c8f6f;
      local_3ac = 2;
    }
    goto LAB_004c72a8;
  case 7:
    if ((human_civ == civ) || (human_civ == civ2)) {
      snd_play_effect(0x44,0,0,0);
    }
    local_3f0[9] = 5;
    local_3f0[10] = 4;
    local_3f0[0xb] = 3;
    local_3f0[0xc] = 2;
    local_3f0[0xd] = 1;
    local_3f0[0xe] = 0;
    local_3f0[0] = 0;
    local_3f0[1] = 0;
    local_3f0[2] = 0;
    local_3f0[3] = 0;
    local_3f0[4] = 1;
    local_3f0[5] = 2;
    local_3f0[6] = 2;
    local_3f0[7] = 3;
    local_3f0[8] = 4;
    if (local_38c == 0) {
      units[unit].field_0e = 5;
    }
    else {
      units[unit].field_0e = '\n';
    }
    units[unit].field_0e = (char)local_3f0[game.difficulty + 9] + units[unit].field_0e;
    if ((units[unit].flags & 0x2000) != 0) {
      units[unit].field_0e += 2;
    }
    units[unit].field_0e =
         units[unit].field_0e -
         (char)local_3f0[civs[civ2].attitude[civ]];
    uVar2 = units[unit].field_0e;
    iVar4 = _rand();
    units[unit].field_0e = uVar2 + (char)(iVar4 % 6);
    units[unit].counter = (byte)civ2;
    units[unit].flags = units[unit].flags | 2;
    puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
    *puVar1 = *puVar1 | 0x1000000;
    popup_game_with_sprite(ADDR(0x62dea8, ((u8 *)&g.d_0062dea8)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
  default:
    break;
  }
switchD_004c94cc_default:
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004c9504 */ { dialog_dtor((Dialog *)((iptr)&local_384)); }
  return;
LAB_004c7f43:
  if (0x26 < improvement) goto LAB_004c7fc1;
  local_78 = (improvement + local_8c) % 0x27;
  if (((local_78 != 0) && (local_78 != 1)) &&
     ((local_78 != 0x11 && (iVar4 = city_has_improvement(city,local_78), iVar4 != 0)))) {
    improvement2 = local_78;
    goto LAB_004c7fc1;
  }
  improvement++;
  goto LAB_004c7f43;
LAB_004c7fc1:
  if ((((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
      (local_38c != 0)) && (0 < improvement2)) {
    local_3ac = popup_game_sprite_flags(ADDR(0x62ddfc, ((u8 *)&g.d_0062ddfc)),1,(iptr)(&unit_sprites + unit_type3 * 0x3c),8);
    if (local_3ac < 0) goto switchD_004c94cc_default;
    if (local_3ac == 1) {
      dlg_load_game_section(&local_384,ADDR(0x62de10, ((u8 *)&g.d_0062de10)),1);
      dialog_add_sprite
                ((DialogOptionList *)&local_384,(iptr)(&unit_sprites + unit_type3 * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_384,8);
      for (improvement = 1; improvement < 0x27; improvement++) {
        if ((improvement != 1) && (iVar4 = city_has_improvement(city,improvement), iVar4 != 0)) {
          uVar9 = 0;
          iVar9 = improvement;
          unit2 = label_string(improvements[improvement].name);
          dialog_add_option((DialogOptionList *)&local_384,unit2,iVar9,uVar9);
        }
      }
      text_clear();
      text_append((iptr)local_70);
      text_append_space();
      text_append_lparen();
      text_append_label(0x78);
      text_append_rparen();
      dialog_add_option((DialogOptionList *)&local_384,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
      improvement2 = dlg_show_modal(&local_384,0);
      if (improvement2 < 0) goto switchD_004c94cc_default;
      if (improvement2 == 0x11) {
        popup_game_with_improvement(ADDR(0x62de1c, ((u8 *)&g.d_0062de1c)),0x11,8);
        goto switchD_004c94cc_default;
      }
      iVar4 = city_has_improvement(city,1);
      if (((((iVar4 != 0) || (improvement2 == 8)) &&
           (local_3ac = popup_game_with_sprite(ADDR(0x62de28, ((u8 *)&g.d_0062de28)),(iptr)(&unit_sprites + unit_type3 * 0x3c),8),
           local_3ac != 1)) ||
          ((iVar4 = spy_check_caught(unit,civ2), iVar4 != 0 ||
           ((iVar4 = city_has_improvement(city,1), iVar4 != 0 &&
            (iVar4 = spy_check_caught(unit,civ2), iVar4 != 0)))))) ||
         (((improvement2 == 8 && (iVar4 = spy_check_caught(unit,civ2), iVar4 != 0)) ||
          ((improvement2 == 0x11 &&
           ((iVar4 = spy_check_caught(unit,civ2), iVar4 != 0 ||
            (iVar4 = spy_check_caught(unit,civ2), iVar4 != 0))))))))
      goto switchD_004c94cc_default;
      local_88 = 1;
    }
  }
  if ((local_88 == 0) && (cities[city].shield_box != 0)) {
    local_1c = 2;
    if (local_38c != 0) {
      local_1c = 3;
    }
    if ((units[unit].flags & 0x2000) != 0) {
      local_1c++;
    }
    if (local_1c - 1 < 1) {
      local_3f4 = 0;
    }
    else {
      local_3f4 = _rand();
      local_3f4 = local_3f4 % local_1c;
    }
    if (local_3f4 == 0) {
      improvement2 = 0;
    }
  }
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) ||
     ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
    if ((human_civ == civ) || (human_civ == civ2)) {
      iVar4 = civ_has_advance(civ,0x23);
      if ((iVar4 == 0) || (human_civ != civ)) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
    }
    if (improvement2 == 0) {
      cities[city].shield_box = 0;
      city_window_refresh_if_city((FrameWindow *)&city_window,city);
      text_set_string_arg(0,(iptr)local_70);
      if (((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
         && ((2 < game.multiplayer && (human_civ != civ2)))) {
        net_send_text_args(0x5a,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),1,0
                           ,civ,0);
      }
      if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0))
      {
        popup_game(ADDR(0x62de38, ((u8 *)&g.d_0062de38)));
      }
    }
    else {
      city_set_improvement(city,improvement2,0);
      map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
      text_set_label_arg(0,improvements[improvement2].name);
      net_send_state_diff(0xff,2,0,0,0);
      if ((((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
          && (2 < game.multiplayer)) && (human_civ != civ2)) {
        net_send_message(0x72,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                           (int)cities[city].x,(int)cities[city].y,0,0,0,0,0,0);
        net_send_message(0x8a,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0
                           ,0,0,0,0,0,0);
        net_send_text_args(0x59,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),1,0
                           ,improvement2,civ);
      }
      if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0))
      {
        city_window_refresh_if_city((FrameWindow *)&city_window,city);
        popup_game_with_sprite(ADDR(0x62de44, ((u8 *)&g.d_0062de44)),(iptr)(&improvement_icon_sprites + improvement2 * 0x3c),8);
      }
    }
  }
  spy_try_escape(unit,local_88,civ2);
  goto switchD_004c94cc_default;
LAB_004c7ad5:
  if (unit < 0) goto LAB_004c7b9b;
  if (unit_types[units[unit].type].role == 6) {
    local_39c = 0x14;
    if ((units[unit].type == '/') && (local_39c = 0x28, (units[unit].flags & 0x2000) != 0)) {
      local_39c = 0x3c;
    }
    iVar4 = _rand();
    if (iVar4 % 100 < local_39c) {
      local_14 = 1;
      unit_type = (uptr)units[unit].type;
      goto LAB_004c7b9b;
    }
  }
  unit = unit_next_in_stack(unit);
  goto LAB_004c7ad5;
LAB_004c7b9b:
  unit2 = unit3;
  if (local_14 == 0) {
    iVar8 = civ_name_plural(civ);
    text_set_string_arg(0,iVar8);
    text_set_label_arg(1,advances[advance].name);
    if ((((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
        && (2 < game.multiplayer)) && (human_civ != civ2)) {
      net_send_text_args(0x57,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),2,0,0
                         ,0);
    }
    if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite(ADDR(0x62ddf4, ((u8 *)&g.d_0062ddf4)),(iptr)(&advance_category_icon_sprites +
                                        (char)advances[advance].epoch * 0x3c +
                                        (char)advances[advance].category * 0xf0),8);
    }
    civ_give_advance(civ,advance,civ2,0,0);
    cities[city].flags = cities[city].flags | 8;
    spy_try_escape(unit2,local_88,civ2);
  }
  else {
    unit_exhaust_moves(unit3);
    map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
    text_set_label_arg(1,unit_types[unit_type].name);
    unit2 = civ_get_adjective(civ);
    text_set_string_arg(2,unit2);
    if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite(ADDR(0x62ddec, ((u8 *)&g.d_0062ddec)),(iptr)(&unit_sprites + unit_type * 0x3c),8);
    }
    if ((((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
        && (2 < game.multiplayer)) && (human_civ != civ2)) {
      net_send_text_args(0x58,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3,0,0
                         ,0);
    }
  }
  goto switchD_004c94cc_default;
}
#undef autoplay_active
#undef human_civ
#undef unit_blink_active
#undef local_3f8
#undef local_3f4
#undef local_3f0
#undef civ
#undef local_3ac
#undef improvement
#undef civ3
#undef local_3a0
#undef local_39c
#undef unit_type3
#undef local_394
#undef unit_type
#undef local_38c
#undef local_388
#undef local_384
#undef advance2
#undef local_8c
#undef local_88
#undef unit3
#undef civ2
#undef local_7c
#undef local_78
#undef improvement2
#undef local_70
#undef advance
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004c9528 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_bribe_answer (*(int *)((u8 *)&g.d_006a1870))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(i8 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl unit_bribe(iptr unit,iptr civ)

{
  char *pcVar1;
  byte civ3;
  iptr civ2;
  iptr iVar4;
  iptr iVar5;
  iptr iVar6;
  int iVar7;
  int city;
  int iVar9;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ3 = units[unit].owner;
  civ2 = (iptr)(char)civ3;
  iVar4 = unit_stack_sum(unit,2);
  if (1 < iVar4) {
    return;
  }
  if (civs[civ2].government == 6) {
    if (autoplay_active != 0) {
      return;
    }
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      return;
    }
    if ((2 < game.multiplayer) && (human_civ != civ)) {
      net_send_text_args(0x21,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),0,0,0,
                         0);
      return;
    }
    popup_game_with_sprite(ADDR(0x62deb8, ((u8 *)&g.d_0062deb8)),ADDR(0x6469e0, ((u8 *)&g.d_006469e0)),0);
    return;
  }
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
     (iVar5 = civ_has_advance(civ,(int)unit_types[0x2e].prerequisite), iVar5 == 0)) {
    return;
  }
  local_c = civ_distance_to_capital(civ2,(int)units[unit].x,(int)units[unit].y);
  if ((civs[civ].government == 3) && (9 < local_c)) {
    local_c = 10;
  }
  local_18 = (int)(char)unit_types[units[unit].type].cost *
             ((civs[civ2].gold + 0x2ee) / (local_c + 2));
  if (local_18 < 0) {
    local_18 = 30000;
  }
  if (unit_types[units[unit].type].role != 5) {
    local_18 = local_18 / 2;
  }
  if ((unit_types[units[unit].type].role == 7) &&
     ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
    return;
  }
  iVar6 = civ_get_adjective(civ2);
  text_set_string_arg(0,iVar6);
  text_set_label_arg(1,unit_types[units[unit].type].name);
  if ((autoplay_active == 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
    text_set_number_arg(0,local_18);
    text_clear();
    text_append(ADDR(0x62dec8, ((u8 *)&g.d_0062dec8)));
    if (human_civ == civ) {
      if (local_18 <= civs[civ].gold) {
        text_append(ADDR(0x62ded0, ((u8 *)&g.d_0062ded0)));
      }
      iVar9 = dlg_game_txt_with_unit(ADDR(0x679640, ((u8 *)&g.d_00679640)),unit);
    }
    else {
      if (game.multiplayer < 3) goto LAB_004c99a0;
      if (civs[civ].gold < local_18) {
        net_send_text_args(0x23,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),2,1,
                           human_civ,unit);
      }
      else {
        net_send_text_args(0x24,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),2,1,
                           human_civ,unit);
      }
      net_bribe_answer = -1;
      city = timer_ticks();
      while ((iVar7 = timer_ticks(), iVar9 = net_bribe_answer,
             iVar7 - city < net_timeout_seconds * 0x3c && (net_bribe_answer == -1))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
    if (iVar9 != 1) {
      return;
    }
  }
  else if (civs[civ].gold / 2 < local_18) {
    return;
  }
LAB_004c99a0:
  if ((game.multiplayer < 3) || (net_host_flag != '\0')) {
    civs[civ].gold -= local_18;
    pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ2 * 0x594);
    *pcVar1 = *pcVar1 - 1;
    pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
    *pcVar1 = *pcVar1 + 1;
    civs[civ].field_1c++;
    units[unit].owner = (byte)civ;
    units[unit].home_city = -1;
    units[unit].moves_used = '\0';
    units[unit].orders = -1;
    city = city_find_nearest((int)units[unit].x,(int)units[unit].y,-1,0xffffffff,-1);
    if ((-1 < city) && (cities[city].owner == civ)) {
      local_10 = (i8)city;
      units[unit].home_city = local_10;
    }
    unit_set_seen_by(unit,civ2);
    tile_set_owner((int)units[unit].x,(int)units[unit].y,civ,1);
    net_send_state_diff(0xff,2,0,0,1);
  }
  else {
    net_send_message(99,0,unit,civ,local_18,0,0,0,0,0);
    city = timer_ticks();
    while ((units[unit].owner != civ && (iVar9 = timer_ticks(), iVar9 - city < 0xe10)
           )) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (units[unit].owner != civ) {
      dbg_log(ADDR(0x62ded4, ((u8 *)&g.d_0062ded4)));
      popup_game_with_sprite(ADDR(0x62df04, ((u8 *)&g.d_0062df04)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
  }
  if ((human_civ == civ2) || (human_civ == civ)) {
    snd_play_effect(0x44,1,0,0);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
    if (human_civ == civ) {
      status_draw_info(1);
    }
    else if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      net_send_message(0x7a,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),0x44,1
                         ,0,0,0,0,0,0);
      net_send_message(0x78,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),0,0,0,
                         0,0,0,0,0);
    }
  }
  if ((autoplay_active == 0) && ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) {
    iVar6 = civ_name_plural(civ);
    text_set_string_arg(2,iVar6);
    if (human_civ == civ2) {
      mapviews_ensure_visible((int)units[unit].x,(int)units[unit].y,civ2);
      dlg_game_txt_with_unit(ADDR(0x62df18, ((u8 *)&g.d_0062df18)),unit);
    }
    else if ((2 < game.multiplayer) && (human_civ != civ2)) {
      net_send_state_diff(0xff,2,0,0,0);
      net_send_message(0x71,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                         (int)units[unit].x,(int)units[unit].y,civ2,0,0,0,0,0);
      net_send_text_args(0x22,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3,0,
                         unit,0);
    }
  }
  map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x72,0xff,(int)units[unit].x,(int)units[unit].y,0,0,0,0,0,0);
  }
  if (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) && (human_civ == civ2)) {
    ui_delay_ticks(0x1e);
  }
  return;
}
#undef autoplay_active
#undef game_loop_active
#undef human_civ
#undef net_bribe_answer
#undef net_host_flag
#undef net_timeout_seconds
#undef local_18
#undef local_10
#undef local_c

/* 004c9ebd auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
i32 __cdecl spy_unit_mission(iptr unit2,iptr unit,iptr civ)

{
  int x;
  i32 uVar2;
  iptr iVar3;
  int y;
  int iVar5;
  
  x = unit_stack_sum(unit,2);
  if (x < 2) {
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
        (units[unit2].type != '/')) || ((game.rules & 0x10) == 0)) {
      unit_bribe(unit,civ);
      uVar2 = 0;
    }
    else {
      x = popup_game_with_unit(ADDR(0x62df24, ((u8 *)&g.d_0062df24)),1,unit2);
      if (x < 0) {
        uVar2 = 0;
      }
      else if (x == 0) {
        unit_bribe(unit,civ);
        uVar2 = 0;
      }
      else {
        if ((human_civ == units[unit].owner) || (human_civ == civ)) {
          snd_play_effect(0x43,1,0,0);
        }
        iVar3 = civ_get_adjective((int)units[unit].owner);
        text_set_string_arg(0,iVar3);
        text_set_label_arg(1,unit_types[units[unit].type].name);
        iVar3 = civ_get_adjective(civ);
        text_set_string_arg(2,iVar3);
        text_set_label_arg(3,unit_types[units[unit2].type].name);
        dlg_game_txt_with_unit(ADDR(0x62df34, ((u8 *)&g.d_0062df34)),unit2);
        if ((2 < game.multiplayer) &&
           (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0)) {
          net_send_text_args(0x25,*(i32 *)
                                   (&net_player_slots +
                                   *(int *)(&net_civ_slots + units[unit].owner * 4) * 0x54),4,0,
                             unit2,0);
        }
        x = (int)units[unit].x;
        y = (int)units[unit].y;
        map_animate_explosion(x,y,0);
        if (2 < game.multiplayer) {
          net_send_message(0x7c,0xff,x,y,0,0,0,0,0,0);
        }
        iVar5 = unit_hp_remaining(unit);
        units[unit].damage = (char)(iVar5 / 2) + units[unit].damage;
        map_redraw_tile_all_views(x,y);
        if (2 < game.multiplayer) {
          net_send_state_diff(0xff,2,0,0,1);
          net_send_message(0x72,0xff,x,y,0,0,0,0,0,0);
        }
        spy_try_escape(unit2,0,-1);
        uVar2 = 1;
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}
#undef human_civ

/* 004ca1cd auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_airlift_perform(iptr unit,iptr city2,iptr city,int param_4,iptr civ)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  cities[city2].flags = cities[city2].flags | 0x10000;
  cities[city].flags = cities[city].flags | 0x10000;
  unit_exhaust_moves(unit);
  units[unit].orders = -1;
  unit_relocate(unit,(int)cities[city].x,(int)cities[city].y,1);
  city_window_on_unit_change((FrameWindow *)&city_window,unit,-1,-1);
  if (param_4 != 0) {
    for (local_8 = 0; local_8 < param_4; local_8++) {
      iVar1 = _rand();
      if (iVar1 % 6 == 0) {
        if ((units[unit].owner == human_civ) && (autoplay_active == 0)) {
          iVar2 = civ_name_plural(civ);
          text_set_string_arg(0,iVar2);
          dlg_game_txt_with_unit_flags(ADDR(0x62df40, ((u8 *)&g.d_0062df40)),0x1b,(ui_large_screen == 0) - 1 & 8);
        }
        unit_delete(unit,1);
        return;
      }
    }
  }
  if ((units[unit].owner == human_civ) && (autoplay_active == 0)) {
    text_set_string_arg(0,(iptr)&cities[city2].name);
    text_set_string_arg(1,(iptr)&cities[city].name);
    dlg_game_txt_with_unit(ADDR(0x62df4c, ((u8 *)&g.d_0062df4c)),unit);
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef ui_large_screen
#undef local_8

/* 004ca39e auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define local_6c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_68 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_64 (*(uint *)(frame_ + FRAME_OFF(12)))
#define aiStack_60 (*(int (*)[8])(frame_ + FRAME_OFF(16)))
#define aiStack_40 (*(int (*)[8])(frame_ + FRAME_OFF(48)))
#define civ4 (*(uptr *)(frame_ + FRAME_OFF(80)))
#define y2 (*(int *)(frame_ + FRAME_OFF(84)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(88)))
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(92)))
#define city (*(int *)(frame_ + FRAME_OFF(96)))
#define local_c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(104)))
void __cdecl unit_paradrop(iptr unit,int x,int y)

{
  byte civ3;
  short x3;
  short y3;
  uptr civ;
  int iVar5;
  uptr city2;
  iptr x2;
  uptr uVar8;
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ3 = units[unit].owner;
  civ = (uptr)(char)civ3;
  x3 = units[unit].x;
  y3 = units[unit].y;
  text_set_number_arg_u8(0,CONCAT31((int3)(char)((ushort)y3 >> 8),cosmic.paradrop_range));
  iVar5 = tile_is_ocean(x,y);
  if (iVar5 == 0) {
    civ4 = tile_unit_owner(x,y);
    if (((int)civ4 < 0) || (civ4 == civ)) {
      iVar5 = map_distance((int)units[unit].x,(int)units[unit].y,x,y);
      if ((int)(uint)cosmic.paradrop_range < iVar5) {
        if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
          dlg_game_txt_with_unit(ADDR(0x62df74, ((u8 *)&g.d_0062df74)),unit);
        }
      }
      else {
        civ4 = tile_owner(x,y);
        city2 = city_at(x,y);
        if (((-1 < (int)city2) && (civ4 != civ)) &&
           ((*(byte *)&civs[civ].treaties[civ4] & 0xe) != 0)) {
          if ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) {
            unit_exhaust_moves(unit);
            return;
          }
          iVar5 = diplo_confirm_attack(civ,civ4,0xe);
          if (iVar5 != 0) {
            return;
          }
        }
        for (civ2 = 1; (int)civ2 < 8; civ2++) {
          if (((2 < game.multiplayer) || (human_civ == civ2)) &&
             (((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0 &&
              ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)))) {
            aiStack_60[civ2] = 0;
            aiStack_40[civ2] = aiStack_60[civ2];
            if ((civ == civ2) || (game.reveal_map != '\0')) {
              aiStack_60[civ2] = 1;
            }
            if ((((-1 < (int)city2) && (civ4 != civ)) &&
                (iVar5 = tile_visible_to(x,y,civ2), iVar5 != 0)) &&
               (((*(byte *)&civs[civ2].treaties[civ] & 0x80) != 0 ||
                ((*(byte *)&civs[civ2].treaties[civ4] & 0x80) != 0)))) {
              aiStack_60[civ2] = 1;
            }
            for (local_14 = 0; (int)local_14 < 9; local_14++) {
              x2 = map_wrap_x((char)(&dir_dx_table)[local_14] + x);
              y2 = (char)(&dir_dy_table)[local_14] + y;
              iVar5 = map_in_bounds(x2,y2);
              if ((iVar5 != 0) &&
                 (uVar8 = tile_city_or_unit_owner(x2,y2), uVar8 == civ2)) {
                aiStack_60[civ2] = 1;
              }
            }
            if ((aiStack_60[civ2] != 0) &&
               (((civ == civ2 || (((*(i8 *)((char *)&game.game_options + 1)) & 0x10) != 0)) || (-1 < (int)city2)
                ))) {
              aiStack_40[civ2] = 1;
            }
          }
        }
        x2 = civ_get_adjective(civ);
        text_set_string_arg(0,x2);
        text_set_label_arg(1,unit_types[units[unit].type].name);
        city = city_find_nearest(x,y,-1,0xffffffff,-1);
        text_set_string_arg(2,(iptr)&cities[city].name);
        if (((aiStack_60[human_civ] != 0) &&
            (mapviews_ensure_visible(x,y,civ),
            (1 << (civ3 & 0x1f) & (uint)game.human_players) == 0)) && (autoplay_active == 0)) {
          dlg_game_txt_with_unit(ADDR(0x62df84, ((u8 *)&g.d_0062df84)),unit);
        }
        if (2 < game.multiplayer) {
          for (civ2 = 1; (int)civ2 < 8; civ2++) {
            if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) &&
                ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
               ((human_civ != civ2 &&
                (((aiStack_60[civ2] != 0 &&
                  ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0)) && (autoplay_active == 0))))
               )) {
              net_send_text_args(0x15,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3,0,unit,0)
              ;
            }
          }
        }
        local_c = 0;
        local_64 = 0xffffffff;
        for (local_14 = 0; (int)local_14 < 8; local_14++) {
          x2 = map_wrap_x((char)(&dir_dx_table)[local_14] + x);
          y2 = (char)(&dir_dy_table)[local_14] + y;
          iVar5 = map_in_bounds(x2,y2);
          if (iVar5 != 0) {
            local_8 = _rand();
            local_8 = local_8 % 6;
            if (((&dir_dx_table)[local_14] != '\0') && ((&dir_dy_table)[local_14] != '\0')) {
              local_8 += 3;
            }
            iVar5 = tile_city_or_unit_owner(x2,y2);
            if (iVar5 < 0) {
              local_8 += 200;
            }
            if (local_c < local_8) {
              local_c = local_8;
              local_64 = local_14 ^ 4;
              local_6c = y2;
              local_68 = x2;
            }
          }
        }
        if ((int)local_64 < 0) {
          for (civ2 = 1; (int)civ2 < 8; civ2++) {
            aiStack_40[civ2] = 0;
          }
        }
        units[unit].orders = -1;
        unit_lift_off_map(unit,0);
        if (((human_civ == civ) || (game.reveal_map != '\0')) ||
           (((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) != 0 ||
            ((int)units[unit].owner == (human_civ & 0xffU))))) {
          map_redraw_tile_all_views((int)x3,(int)y3);
        }
        if (aiStack_40[human_civ] != 0) {
          map_animate_unit_move(unit,local_68,local_6c,local_64,0xffffffff,0xffffffff);
        }
        unit_stack_clear_visibility(unit);
        if ((game.active_unit == unit) && (human_civ == civ)) {
          map_cursor_x = (i16)x;
          map_cursor_y = (i16)y;
        }
        unit_stack_relocate_all(unit,x,y,0);
        if (2 < game.multiplayer) {
          net_send_state_diff(0xff,2,0,0,0);
          for (civ2 = 1; (int)civ2 < 8; civ2++) {
            if (((human_civ != civ2) &&
                ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0)) &&
               ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
              if (((game.reveal_map != '\0') ||
                  ((1 << ((byte)civ2 & 0x1f) & (uint)units[unit].visibility) != 0)) ||
                 ((int)units[unit].owner == (civ2 & 0xff))) {
                net_send_message(0x72,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ2 * 4) * 0x54),x,
                                   y,0,0,0,0,0,0);
              }
              if (aiStack_40[civ2] != 0) {
                net_send_message(0x70,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ2 * 4) * 0x54),unit,
                                   x,y,local_64,-1,0,0,0);
              }
            }
          }
        }
        units[unit].flags = units[unit].flags | 0x10;
        if ((-1 < (int)city2) && (civ4 != civ)) {
          if ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) {
            unit_exhaust_moves(unit);
          }
          units[unit].damage = '\0';
          game.moving_unit = (i16)unit;
          city_capture_aftermath(city2,civ,0);
          unit = (iptr)game.moving_unit;
        }
        unit_reveal_surroundings(unit,1);
        city_window_on_unit_change
                  ((FrameWindow *)&city_window,unit,(int)x3,(int)y3);
        units[unit].flags = units[unit].flags & 0xfeff;
        status_redraw(1);
      }
    }
    else if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
      dlg_game_txt_with_unit(ADDR(0x62df64, ((u8 *)&g.d_0062df64)),unit);
    }
  }
  else if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
    dlg_game_txt_with_unit(ADDR(0x62df54, ((u8 *)&g.d_0062df54)),unit);
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef local_6c
#undef local_68
#undef local_64
#undef aiStack_60
#undef aiStack_40
#undef civ4
#undef y2
#undef civ2
#undef local_14
#undef city
#undef local_c
#undef local_8

/* 004ec1c6 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_pick_caravan_commodity(iptr city,iptr unit)

{
  iptr iVar1;
  iptr iVar3;
  iptr iVar2;
  int iVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  units[unit].counter = 0xff;
  iVar1 = _rand();
  local_8 = 0;
  do {
    if (2 < local_8) {
LAB_004ec264:
      if ((char)units[unit].counter < '\0') {
        iVar3 = _rand();
        iVar4 = iVar3 % 3;
        if (*(char *)&cities[city].supplies[iVar4] < 1) {
          units[unit].counter = ~cities[city].supplies[iVar4] + 1;
        }
        else {
          units[unit].counter = cities[city].supplies[iVar4];
        }
      }
      cities[city].flags = cities[city].flags | 0x1000;
      return;
    }
    iVar2 = (iVar1 % 3 + local_8) % 3;
    if (-1 < *(char *)&cities[city].supplies[iVar2]) {
      units[unit].counter = cities[city].supplies[iVar2];
      goto LAB_004ec264;
    }
    local_8++;
  } while( true );
}
#undef local_8

/* 00531567 auto */
void __cdecl unit_stack_wake_by_role(iptr unit,uint param_2,int param_3)

{
  unit = unit_stack_first(unit);
  while ((-1 < unit &&
         (((units[unit].orders != 3 ||
           ((param_2 & 1 << (unit_types[units[unit].type].role & 0x1f)) == 0)) ||
          (units[unit].orders = -1, param_3 == 0))))) {
    unit = unit_next_in_stack(unit);
  }
  return;
}

/* 00531607 auto */
void __cdecl unit_set_goto(iptr unit,i32 param_2,i32 param_3,i32 param_4)

{
  units[unit].orders = 11;
  units[unit].field_0c = (u8)param_2;
  units[unit].goto_x = (i16)param_3;
  units[unit].goto_y = (i16)param_4;
  return;
}

/* 00543b80 auto */
void __cdecl unit_continue_active_orders(void)

{
  iptr unit;
  int iVar2;
  
  ui_flush_input();
  unit = (iptr)game.active_unit;
  if ((((((units[unit].moves_used != '\0') && (units[unit].orders == 11)) &&
        (unit_types[units[unit].type].hold == '\0')) &&
       ((unit_types[units[unit].type].role != 2 ||
        (iVar2 = tile_adjacent_nonallied_civ((int)units[unit].x,(int)units[unit].y,(int)units[unit].owner)
        , iVar2 == 0)))) ||
      ((iVar2 = ai_unit_choose_orders(), iVar2 == 0 && (iVar2 = unit_moves_left(unit), iVar2 != 0))
      )) && (iVar2 = unit_execute_orders(unit), iVar2 == 0)) {
    unit_exhaust_moves(unit);
  }
  return;
}

/* 0056b96e auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(20)))
iptr __cdecl unit_stack_pick_display_unit(iptr unit)

{
  int x;
  int y;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  local_1c = -1;
  if (-1 < unit) {
    x = (int)units[unit].x;
    y = (int)units[unit].y;
    iVar3 = map_in_bounds(x,y);
    if (iVar3 != 0) {
      tile_is_ocean(x,y);
    }
    for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit))
    {
      local_18 = 1;
      if (unit_types[units[unit].type].domain != '\0') {
        local_18 = 2;
      }
      if ((game.active_unit == unit) && ((int)units[unit].owner == (uint)(byte)human_civ))
      {
        local_18 = 4;
      }
      if ((unit_types[units[unit].type].domain == 1) &&
         (iVar3 = tile_airbase_owner(x,y), -1 < iVar3)) {
        local_18 = -1;
      }
      if (local_1c < local_18) {
        local_1c = local_18;
        local_c = unit;
      }
    }
  }
  return local_c;
}
#undef human_civ
#undef local_1c
#undef local_18
#undef local_c

/* 0057e2c3 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl unit_attack_strength(iptr unit)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (char)unit_types[units[unit].type].attack * 8;
  if ((units[unit].flags & 0x2000) != 0) {
    local_8 += (local_8 >> 1);
  }
  if ((units[unit].flags & 0x10) != 0) {
    local_8 += (local_8 >> 1);
  }
  return local_8;
}
#undef local_8

/* 0057e33a auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl unit_defense_strength(iptr unit,int param_2,iptr unit2)

{
  u8 uVar1;
  byte unit_type;
  int x;
  int y;
  byte *pbVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  if (param_2 != 0) {
    unit_type = tile_terrain(x,y);
    unit_defense_terrain = (uptr)unit_type;
    combat_defender_city = city_at(x,y);
  }
  uVar1 = unit_types[units[unit].type].defense;
  pbVar5 = (byte *)tile_at(x,y);
  local_8 = ((uint)(*pbVar5 >> 7) + (int)(char)terrain_types[unit_defense_terrain].defense) *
            (char)uVar1 * 4;
  combat_defense_bonus_halves = 2;
  if ((units[unit].orders == 2) && (unit_types[units[unit].type].domain == '\0')) {
    combat_defense_bonus_halves = 3;
  }
  uVar6 = tile_improvements(x,y);
  if (((byte)uVar6 & 0x42) == 0x40) {
    if (unit2 < 0) {
      combat_defense_bonus_halves = 4;
    }
    else if ((unit_types[units[unit2].type].domain != 1) &&
            ((unit_types[units[unit2].type].flags & 0x40) == 0)) {
      combat_defense_bonus_halves = 4;
    }
  }
  if (-1 < (int)combat_defender_city) {
    if ((((unit_types[units[unit].type].domain == 1) && (-1 < unit2)) &&
        ((unit_types[units[unit].type].flags & 0x10) != 0)) &&
       ((unit_type = units[unit2].type, unit_types[unit_type].domain == 1 &&
        ((unit_types[unit_type].flags & 0x1000) == 0)))) {
      if ((unit_types[unit_type].flags & 0x10) == 0) {
        combat_defense_bonus_halves = combat_defense_bonus_halves << 2;
      }
      else {
        combat_defense_bonus_halves = combat_defense_bonus_halves << 1;
      }
      goto LAB_0057e694;
    }
    x = city_has_improvement(combat_defender_city,8);
    if (((x != 0) || (x = civ_has_wonder((int)units[unit].owner,6), x != 0)) &&
       (unit_types[units[unit].type].domain == '\0')) {
      if (unit2 < 0) {
        combat_defense_bonus_halves = 6;
      }
      else if ((unit_types[units[unit2].type].domain == '\0') &&
              ((unit_types[units[unit2].type].flags & 0x40) == 0)) {
        combat_defense_bonus_halves = 6;
      }
    }
  }
  if (unit_types[units[unit].type].domain != '\0') {
    combat_defense_bonus_halves = 2;
  }
LAB_0057e694:
  if (combat_defense_bonus_halves != 2) {
    local_8 = local_8 * combat_defense_bonus_halves >> 1;
  }
  if ((units[unit].flags & 0x2000) != 0) {
    local_8 += (local_8 >> 1);
  }
  return local_8;
}
#undef local_8

/* 0057e6e2 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
iptr __cdecl unit_stack_best_defender(iptr unit,iptr unit2)

{
  short x;
  short y;
  byte bVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_c = unit;
  if (-1 < unit) {
    x = units[unit].x;
    y = units[unit].y;
    bVar3 = tile_terrain((int)x,(int)y);
    unit_defense_terrain = (uptr)bVar3;
    combat_defender_city = city_at((int)x,(int)y);
    for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit))
    {
      if ((unit_defense_terrain != 10) || (unit_types[units[unit].type].domain != '\0')) {
        local_10 = unit_defense_strength(unit,0,unit2);
        if ((game.rules & 0x10) != 0) {
          iVar4 = unit_hp_remaining(unit);
          iVar5 = unit_max_hp(unit);
          local_10 = (iVar4 * local_10) / iVar5;
        }
        if ((unit_types[units[unit].type].flags & 0x400) != 0) {
          local_10++;
        }
        if ((unit_types[units[unit].type].flags & 0x2000) != 0) {
          if (unit2 == -1) {
            local_10++;
          }
          else if (unit_types[units[unit2].type].domain == 1) {
            if ((unit_types[units[unit2].type].flags & 0x1000) == 0) {
              local_10 = local_10 * 3;
            }
            else {
              local_10 = local_10 * 5;
            }
          }
        }
        if (((((unit_types[units[unit].type].flags & 0x10) != 0) && (unit2 != -1)) &&
            (unit_types[units[unit2].type].domain == 1)) &&
           ((unit_types[units[unit2].type].flags & 0x10) != 0)) {
          local_10 = local_10 << 1;
        }
        if ((unit_types[units[unit].type].domain == 2) && (-1 < (int)combat_defender_city)) {
          if (unit2 == -1) {
            local_10 = local_10 / 2;
          }
          else if ((unit_types[units[unit2].type].domain == 1) &&
                  (iVar4 = city_has_improvement(combat_defender_city,0x1b), iVar4 == 0)) {
            local_10 = local_10 << 1;
          }
          else {
            local_10 = local_10 / 2;
          }
        }
        if (local_8 <= local_10) {
          local_8 = local_10;
          local_c = unit;
        }
      }
    }
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 0057e9f9 auto */
#define combat_kill_count (*(int *)((u8 *)&g.d_006acb0c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
void __cdecl unit_kill_in_combat(iptr unit,iptr unit2,iptr param_3,iptr param_4)

{
  char *pcVar1;
  
  if (*(char *)&civs[units[unit].owner].units_lost[units[unit].type] != -1) {
    pcVar1 = (char *)(units[unit].type + ADDR(0x64c7b6, ((u8 *)&civs + 278)) + units[unit].owner * 0x594);
    *pcVar1 = *pcVar1 + 1;
  }
  if ((units[unit].owner == human_civ) || (game.multiplayer < 3)) {
    casualty_log_add(unit,unit2,(int)game.year,param_3,param_4);
  }
  else if ((2 < game.multiplayer) &&
          (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0)) {
    net_send_message(100,*(i32 *)
                            (&net_player_slots +
                            *(int *)(&net_civ_slots + units[unit].owner * 4) * 0x54),unit,
                       unit2,(int)game.year,param_3,param_4,0,0,0);
  }
  combat_kill_count++;
  if (scenario_events_loaded != 0) {
    events_check_unit_killed
              ((ScenarioEvents *)&scenario_events,(uint)units[unit].type,(int)units[unit2].owner,
               (int)units[unit].owner);
  }
  unit_delete(unit,1);
  return;
}
#undef combat_kill_count
#undef human_civ
#undef scenario_events_loaded

/* 0057eb94 auto */
#define combat_kill_count (*(i32 *)((u8 *)&g.d_006acb0c))
void __cdecl unit_kill_stack_in_combat(iptr unit,iptr unit2,i32 param_3,i32 param_4)

{
  short sVar1;
  
  combat_kill_count = 0;
  unit = unit_stack_first(unit);
  while (-1 < unit) {
    sVar1 = units[unit].next_in_stack;
    unit_kill_in_combat(unit,unit2,param_3,param_4);
    unit = (iptr)sVar1;
  }
  return;
}
#undef combat_kill_count

/* 0057ebfd auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl unit_promote_veteran(iptr unit)

{
  if (((((units[unit].flags & 0x2000) == 0) &&
       ((unit_types[units[unit].type].flags & 0x1000) == 0)) &&
      (units[unit].flags = units[unit].flags | 0x2000,
      ((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0)) && (autoplay_active == 0)
     ) {
    text_set_label_arg(0,unit_types[units[unit].type].name);
    if (units[unit].owner == human_civ) {
      dlg_game_txt_with_unit(ADDR(0x634428, ((u8 *)&g.d_00634428)),unit);
    }
    else if (2 < game.multiplayer) {
      net_send_text_args(0x20,*(i32 *)
                               (&net_player_slots +
                               *(int *)(&net_civ_slots + units[unit].owner * 4) * 0x54),1,0,
                         unit,0);
    }
  }
  return;
}
#undef autoplay_active
#undef human_civ

/* 0057f9e3 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_c (*(byte *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
i32 __cdecl unit_nuclear_attack(iptr civ,int x,int y,int param_4)

{
  uint *puVar1;
  char cVar2;
  iptr iVar3;
  iptr x2;
  iptr iVar5;
  int unit;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = tile_city_or_unit_owner(x,y);
  x2 = civ_name_plural(civ);
  text_set_string_arg(0,x2);
  local_c = (byte)iVar3;
  if (((game.multiplayer < 3) || ((1 << (local_c & 0x1f) & (uint)game.human_players) == 0)) ||
     (human_civ == iVar3)) {
    if ((1 << (local_c & 0x1f) & (uint)game.human_players) != 0) {
      popup_game_with_improvement(ADDR(0x634434, ((u8 *)&g.d_00634434)),0x3e,8);
    }
  }
  else {
    net_send_text_args(0x29,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + iVar3 * 4) * 0x54),1,0,0,0);
  }
  if (param_4 != 0) {
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && (cities[city].owner != civ)) &&
         ((iVar5 = city_has_improvement(city,0x11), iVar5 != 0 &&
          (unit = map_distance((int)cities[city].x,(int)cities[city].y,x,
                                      y), unit < 4)))) {
        text_set_string_arg(0,(iptr)&cities[city].name);
        if (((game.multiplayer < 3) ||
            (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) == 0)) ||
           (cities[city].owner == human_civ)) {
          if (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0) {
            popup_game_with_improvement(ADDR(0x634440, ((u8 *)&g.d_00634440)),0x11,8);
          }
        }
        else {
          net_send_text_args(0x2a,*(i32 *)
                                   (&net_player_slots +
                                   *(int *)(&net_civ_slots + cities[city].owner * 4) * 0x54),1,0,
                             0,0);
        }
        if (((game.multiplayer < 3) ||
            ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) ||
           (human_civ == civ)) {
          if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
            popup_game_with_improvement(ADDR(0x634444, ((u8 *)&g.d_00634444)),0x11,8);
          }
        }
        else {
          net_send_text_args(0x2a,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),1,
                             0,0,0);
        }
        return 0;
      }
    }
  }
  if (((2 < game.multiplayer) && ((1 << (local_c & 0x1f) & (uint)game.human_players) != 0)) &&
     (human_civ != iVar3)) {
    net_send_message(0x7d,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + iVar3 * 4) * 0x54),x,
                       y,0,0,0,0,0,0);
  }
  map_animate_nuke(x,y);
  for (local_8 = 0; local_8 < 9; local_8++) {
    x2 = map_wrap_x((char)(&dir_dx_table)[local_8] + x);
    cVar2 = (&dir_dy_table)[local_8];
    unit = map_in_bounds(x2,cVar2 + y);
    if ((unit != 0) && (unit = tile_first_unit(x2,cVar2 + y), -1 < unit)) {
      if (units[unit].owner != civ) {
        puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + units[unit].owner * 0x594);
        *puVar1 = *puVar1 | 0x110;
        puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + units[unit].owner * 4);
        *puVar1 = *puVar1 | 0x20000;
        civ_adjust_attitude((int)units[unit].owner,civ,100);
      }
      unit_stack_delete_all(unit,1);
    }
  }
  nuclear_blast(x,y);
  return 1;
}
#undef human_civ
#undef city
#undef local_c
#undef local_8

/* 00580341 auto */
#define active_unit_lost_in_combat (*(i32 *)((u8 *)&g.d_0062c5bc))
#define anim_combat_defender (*(iptr *)((u8 *)&g.d_00633e48))
#define anim_combat_defender_x (*(iptr *)((u8 *)&g.d_00633e40))
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define combat_kill_count (*(int *)((u8 *)&g.d_006acb0c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define unit_move_flags (*(byte *)((u8 *)&g.d_006ad0cc))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_e0 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_dc (*(int *)(frame_ + FRAME_OFF(12)))
#define local_d8 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_d4 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_d0 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_cc (*(sbyte *)(frame_ + FRAME_OFF(28)))
#define local_c8 (*(uptr *)(frame_ + FRAME_OFF(32)))
#define local_c4 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_c0 (*(uint *)(frame_ + FRAME_OFF(40)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(44)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(60)))
#define local_a0 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_98 (*(uint *)(frame_ + FRAME_OFF(80)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(124)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_60 (*(uptr *)(frame_ + FRAME_OFF(136)))
#define aiStack_58 (*(int (*)[8])(frame_ + FRAME_OFF(144)))
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(176)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(180)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(184)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(188)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(192)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(196)))
#define local_20 (*(uptr *)(frame_ + FRAME_OFF(200)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(204)))
#define civ3 (*(uptr *)(frame_ + FRAME_OFF(208)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(212)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(216)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(220)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(224)))
i32 __cdecl unit_resolve_attack(iptr unit,iptr param_2,int param_3)

{
  char *pcVar1;
  byte civ4;
  byte civ5;
  byte unit_type;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  uptr civ;
  int x2;
  int y2;
  int y;
  iptr x;
  uptr civ2;
  iptr iVar14;
  iptr iVar12;
  int unit3;
  iptr iVar15;
  int city2;
  i32 uVar17;
  uint uVar18;
  bool bVar19;
  uptr city;
  i8 frame_[FRAME_OFF(232)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_28 = 0;
  improvement = 0;
  bVar19 = false;
  bVar7 = false;
  local_30 = 0;
  local_b0 = 0;
  local_10 = 0;
  local_24 = 0;
  local_ac = 0;
  local_38 = 1;
  for (civ3 = 1; (int)civ3 < 8; civ3++) {
    *(i32 *)(civ3 * 4 + ADDR(0x6acae8, ((u8 *)&g.d_006aca14 + 212))) = 0;
    *(i32 *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) = 0;
  }
  civ4 = units[unit].owner;
  civ = (uptr)(char)civ4;
  x2 = (int)units[unit].x;
  y2 = (int)units[unit].y;
  local_a0 = unit_attack_strength(unit);
  local_78 = (int)(char)unit_types[units[unit].type].firepower;
  y = unit_moves_left(unit);
  if (y < (int)(uint)cosmic.road_move_mult) {
    local_98 = unit_moves_left(unit);
  }
  else {
    local_98 = (uint)cosmic.road_move_mult;
  }
  if (param_3 != 0) {
    local_a0 = (int)(local_a0 * local_98) / (int)(uint)cosmic.road_move_mult;
  }
  x = map_wrap_x((char)(&dir_dx_table)[param_2] + x2);
  y = (char)(&dir_dy_table)[param_2] + y2;
  local_14 = y;
  local_8 = x;
  unit2 = tile_first_unit(x,y);
  if (unit2 < 0) {
    return 999;
  }
  unit2 = unit_stack_best_defender(unit2,unit);
  civ5 = units[unit2].owner;
  civ2 = (uptr)(char)civ5;
  local_64 = unit_defense_strength(unit2,0,unit);
  local_34 = (int)(char)unit_types[units[unit2].type].firepower;
  if (((unit_types[units[unit].type].role == 3) &&
      (unit_types[units[unit2].type].domain == 1)) &&
     (unit_types[units[unit2].type].range == '\0')) {
    local_64 -= (local_64 >> 1);
    local_34 = 1;
  }
  if ((unit_types[units[unit2].type].flags & 0x400) != 0) {
    local_c4 = unit_max_moves(unit);
    if (mp_double_moves != 0) {
      local_c4 -= (int)(char)unit_types[units[unit].type].move / 2;
    }
    if ((((uint)cosmic.road_move_mult * 2 == local_c4) &&
        (unit_types[units[unit].type].domain == '\0')) &&
       (iVar14 = unit_max_hp(unit), iVar14 == 10)) {
      local_64 += (local_64 >> 1);
    }
  }
  if (((unit_types[units[unit2].type].flags & 0x2000) != 0) &&
     (unit_types[units[unit].type].domain == 1)) {
    if ((unit_types[units[unit].type].flags & 0x1000) == 0) {
      local_64 = local_64 * 3;
    }
    else {
      local_64 = local_64 * 5;
    }
  }
  if ((((0 < (int)combat_defender_city) && (unit_types[units[unit].type].domain == 2)) &&
      (unit_types[units[unit2].type].domain != 2)) &&
     ((iVar12 = city_has_improvement(combat_defender_city,0x1c), iVar12 != 0 &&
      (local_64 = local_64 << 1, param_3 != 0)))) {
    improvement = 0x1c;
    cities[combat_defender_city].flags = cities[combat_defender_city].flags | 0x8000000;
  }
  if ((0 < (int)combat_defender_city) && (unit_types[units[unit].type].domain == 1)) {
    if (((unit_types[units[unit2].type].flags & 0x10) == 0) ||
       ((unit_types[units[unit].type].flags & 0x1000) != 0)) {
      unit3 = city_has_improvement(combat_defender_city,0x11);
      if (((unit3 != 0) && ((unit_types[units[unit].type].flags & 0x1000) != 0)) &&
         ((char)unit_types[units[unit].type].attack < 'c')) {
        local_64 = local_64 << 1;
        local_24 = 1;
        if (param_3 != 0) {
          improvement = 0x11;
        }
      }
      unit3 = city_has_improvement(combat_defender_city,0x1b);
      if ((unit3 != 0) && (local_64 = local_64 << 1, param_3 != 0)) {
        improvement = 0x1b;
      }
    }
    else if (param_3 != 0) {
      local_28 = 1;
    }
  }
  if ((units[unit].type == '\t') && (unit_types[units[unit2].type].attack == '\0')) {
    local_a0 = local_a0 << 3;
  }
  if ((unit_types[units[unit].type].domain == 2) &&
     (unit_types[units[unit2].type].domain == '\0')) {
    local_78 = 1;
    local_34 = 1;
  }
  if ((unit_types[units[unit2].type].flags & 8) != 0) {
    local_34 = 1;
  }
  if (((unit_types[units[unit].type].flags & 8) != 0) &&
     ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0)) {
    civ_clear_standing_goals_near(civ2,0x12,x,y,3);
    civ_add_standing_goal(civ2,x,y,0x12,2);
  }
  if (((unit_types[units[unit2].type].domain == 2) &&
      (unit3 = tile_is_ocean(x,y), unit3 == 0)) &&
     (unit_types[units[unit].type].domain != 2)) {
    local_34 = 1;
    if (unit_types[units[unit].type].domain == 1) {
      local_10 = 1;
      local_78 = local_78 << 1;
    }
    else {
      local_10 = 1;
      local_78 = local_78 << 1;
    }
  }
  if (civ == 0) {
    if ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) {
      local_a0 = local_a0 / 2;
    }
    else {
      local_a0 = (game.difficulty + 1) * local_a0;
      local_a0 = (int)(local_a0 + (local_a0 >> 0x1f & 3U)) >> 2;
    }
    if (-1 < (int)combat_defender_city) {
      if (civs[civ2].num_cities < 2) {
        local_a0 = 0;
      }
      unit3 = city_has_improvement(combat_defender_city,1);
      bVar19 = unit3 != 0;
      if (bVar19) {
        local_a0 = local_a0 >> 1;
      }
      if (civs[civ2].num_cities < 8) {
        bVar19 = true;
      }
    }
    unit3 = civ_has_wonder(civ2,6);
    if (unit3 != 0) {
      local_a0 = local_a0 / 2;
    }
  }
  if (civ2 == 0) {
    if (((units[unit2].type == 4) ||
        ((units[unit2].type == 5 && ((game.human_players & game.advance_known_by[0x27]) == 0)
         ))) && (local_64 = local_64 / 2, local_64 < 2)) {
      local_64 = 1;
    }
    unit3 = civ_has_wonder(civ,6);
    if (unit3 != 0) {
      local_a0 = local_a0 << 1;
    }
  }
  if (param_3 == 0) {
    if ((game.rules & 0x10) != 0) {
      x2 = unit_hp_remaining(unit);
      local_a0 = (x2 + local_78 * 8) * local_a0;
      x2 = unit_hp_remaining(unit2);
      local_64 = (x2 + local_34 * 8) * local_64;
    }
    for (; 3999 < local_a0; local_a0 = local_a0 >> 1) {
      local_64 = local_64 >> 1;
    }
    x2 = (local_a0 << 3) / (local_64 + 1);
    if (x2 < 0x401) {
      return x2;
    }
    return 0x400;
  }
  if ((unit_move_flags & 2) != 0) {
    units[unit].moves_used += cosmic.road_move_mult;
  }
  if (((1 << (civ4 & 0x1f) & (uint)game.human_players) != 0) &&
     (unit3 = diplo_confirm_attack(civ,civ2,0xd), unit3 != 0)) {
    return 1;
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
    return 1;
  }
  if ((civ != 0) && (civ2 != 0)) {
    game.field_2c = 0;
  }
  diplo_set_treaty_flags(civ,civ2,0x200);
  if (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) ||
     (((*(byte *)&civs[civ2].treaties[civ] & 6) == 0 &&
      ((((*(byte *)&civs[civ2].treaties[civ] & 1) == 0 &&
        ((*(byte *)&civs[civ].treaties[civ2] & 0x40) == 0)) ||
       ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x20) != 0)))))) {
    if (((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) ||
       ((*(byte *)&civs[civ2].treaties[civ] & 4) != 0)) {
      if (game.multiplayer < 3) {
        if (((1 << (civ4 & 0x1f) & (uint)game.human_players) == 0) &&
           ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0)) {
          if ((*(byte *)&civs[human_civ].treaties[civ2] & 8) == 0) {
            if ((*(byte *)&civs[human_civ].treaties[civ] & 8) == 0) {
              if (game.reveal_map != '\0') {
                local_30 = 1;
              }
            }
            else {
              local_b0 = 2;
            }
          }
          else {
            local_b0 = 1;
          }
        }
        else {
          local_30 = 1;
        }
      }
      else {
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) {
            if (civ == civ3) {
              *(i32 *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) = 1;
            }
            else if (civ2 == civ3) {
              *(i32 *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) = 1;
            }
            else if (game.reveal_map != '\0') {
              *(i32 *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) = 1;
            }
            if (*(int *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) != 0) {
              local_30 = 1;
            }
          }
        }
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) {
            if ((civ2 == civ3) ||
               ((*(byte *)&civs[civ3].treaties[civ2] & 8) == 0)) {
              if ((civ != civ3) &&
                 ((*(byte *)&civs[civ3].treaties[civ] & 8) != 0)) {
                *(i32 *)(civ3 * 4 + ADDR(0x6acae8, ((u8 *)&g.d_006aca14 + 212))) = 2;
                local_b0 = 2;
              }
            }
            else {
              *(i32 *)(civ3 * 4 + ADDR(0x6acae8, ((u8 *)&g.d_006aca14 + 212))) = 1;
              local_b0 = 1;
            }
          }
        }
      }
    }
  }
  else {
    if (4 < civs[civ].government) {
      local_6c = _rand();
      local_6c = local_6c % 100;
      if ((civs[civ].government == 5) ||
         (unit3 = civ_has_wonder(civ,0x18), unit3 != 0)) {
        local_6c -= 0x32;
      }
      if ((-1 < (int)(local_6c + (uint)civs[civ2].reputation * -10)) &&
         ((1 << (civ4 & 0x1f) & (uint)game.human_players) == 0)) {
        ai_choose_government(civ,1);
      }
    }
    if (((*(byte *)&civs[civ2].treaties[civ] & 2) == 0) ||
       ((*(byte *)&civs[civ2].treaties[civ] & 4) != 0)) {
      if ((autoplay_active == 0) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0)) {
        iVar15 = civ_get_adjective(civ);
        text_set_string_arg(0,iVar15);
        if (human_civ == civ2) {
          dlg_game_txt_with_unit(ADDR(0x634454, ((u8 *)&g.d_00634454)),unit);
        }
        else if (2 < game.multiplayer) {
          net_send_text_args(0x2e,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),1,0
                             ,unit,0);
        }
      }
    }
    else if ((autoplay_active == 0) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0)) {
      iVar15 = civ_name_plural(civ);
      text_set_string_arg(0,iVar15);
      if (human_civ == civ2) {
        dlg_game_txt_with_unit(ADDR(0x634448, ((u8 *)&g.d_00634448)),unit);
      }
      else if (2 < game.multiplayer) {
        net_send_text_args(0x2d,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),1,0,
                           unit,0);
      }
    }
    local_a0 = local_a0 << 1;
    civs[civ2].last_treaty_turn[civ] = game.turn;
  }
  unit3 = diplo_force_war(civ,civ2);
  if (civ != 0) {
    if ((game.difficulty < 2) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0)) {
      local_a0 = local_a0 >> 1;
    }
    if ((game.difficulty == '\0') && ((1 << (civ4 & 0x1f) & (uint)game.human_players) != 0)) {
      local_a0 = local_a0 << 1;
    }
  }
  bVar5 = false;
  for (civ3 = 1; (int)civ3 < 8; civ3++) {
    aiStack_58[civ3] = 0;
    if ((((2 < game.multiplayer) || (human_civ == civ3)) &&
        ((1 << ((byte)civ3 & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0)) {
      if (game.multiplayer < 3) {
        if (((((civ == civ3) || (civ2 == civ3)) ||
             ((game.reveal_map != '\0' ||
              ((((1 << ((byte)civ3 & 0x1f) & (uint)units[unit].visibility) != 0 ||
                ((int)units[unit].owner == (civ3 & 0xff))) ||
               ((1 << ((byte)civ3 & 0x1f) & (uint)units[unit2].visibility) != 0)))))) ||
            ((int)units[unit2].owner == (civ3 & 0xff))) ||
           (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
          aiStack_58[civ3] = 1;
          bVar5 = true;
        }
      }
      else if ((civ == civ3) || (civ2 == civ3)) {
        aiStack_58[civ3] = 1;
        bVar5 = true;
      }
    }
  }
  if (bVar5) {
    unit_set_seen_by(unit,civ2);
    net_send_state_diff(0xff,2,0,0,0);
    for (civ3 = 1; (int)civ3 < 8; civ3++) {
      if (aiStack_58[civ3] != 0) {
        if (human_civ == civ3) {
          city2 = mapviews_ensure_visible(x,y,civ);
          if (city2 == 0) {
            map_redraw_tile_all_views(x2,y2);
          }
        }
        else {
          local_c8 = civ2;
          if (civ == civ3) {
            local_c8 = civ;
          }
          net_send_message(0x71,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             x,y,local_c8,0,0,0,0,0);
          net_send_message(0x72,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             x2,y2,0,0,0,0,0,0);
        }
      }
    }
    unit_lift_off_map(unit,1);
    for (local_1c = 0; local_1c < 8; local_1c++) {
      if ((local_1c == 0) || (*(short *)(&map_view_open_flags + local_1c * 0x3f0) != 0)) {
        mapview_draw_unit_at
                  ((C_004083b0_430 *)(&map_views + local_1c * 0x3f0),unit2);
        mapview_blit_tile
                  ((C_004083b0_430 *)(&map_views + local_1c * 0x3f0),x,y);
      }
    }
    if ((unit_types[units[unit].type].flags & 0x1008) != 0) {
      ui_delay_ticks(10);
    }
    if (((((unit_types[units[unit].type].flags & 0x1000) != 0) &&
         ((char)unit_types[units[unit].type].attack < 'c')) &&
        ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0)) &&
       ((city2 = city_find_nearest(x,y,-1,0xffffffff,-1), -1 < city2 &&
        (text_set_string_arg(0,(iptr)&cities[city2].name), autoplay_active == 0)))) {
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if (aiStack_58[civ3] != 0) {
          if (human_civ == civ3) {
            dlg_game_txt_with_unit(ADDR(0x63445c, ((u8 *)&g.d_0063445c)),unit);
          }
          else {
            net_send_text_args(0x2f,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,1,0,unit,0);
          }
        }
      }
    }
    if (local_10 != 0) {
      iVar15 = civ_get_adjective(civ);
      text_set_string_arg(0,iVar15);
      text_set_label_arg(1,unit_types[units[unit].type].name);
      iVar15 = civ_get_adjective(civ2);
      text_set_string_arg(2,iVar15);
      if (autoplay_active == 0) {
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if (aiStack_58[civ3] != 0) {
            if (human_civ == civ3) {
              dlg_game_txt_with_unit(ADDR(0x63446c, ((u8 *)&g.d_0063446c)),unit);
            }
            else {
              net_send_text_args(0x30,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),3,0,unit,0)
              ;
            }
          }
        }
      }
    }
    if (improvement != 0) {
      text_set_label_arg(1,improvements[improvement].name);
      text_set_string_arg(2,(iptr)&cities[combat_defender_city].name);
      if ((local_24 == 0) || (improvement == 0x11)) {
        if (autoplay_active == 0) {
          for (civ3 = 1; (int)civ3 < 8; civ3++) {
            if (aiStack_58[civ3] != 0) {
              if (human_civ == civ3) {
                popup_game_with_improvement(ADDR(0x634484, ((u8 *)&g.d_00634484)),improvement,8);
              }
              else {
                net_send_text_args(0x32,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ3 * 4) * 0x54),3,0,improvement
                                   ,0);
              }
            }
          }
        }
      }
      else {
        text_set_label_arg(3,improvements[0x11].name);
        if (autoplay_active == 0) {
          for (civ3 = 1; (int)civ3 < 8; civ3++) {
            if (aiStack_58[civ3] != 0) {
              if (human_civ == civ3) {
                popup_game_with_improvement(ADDR(0x634478, ((u8 *)&g.d_00634478)),improvement,8);
              }
              else {
                net_send_text_args(0x31,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ3 * 4) * 0x54),4,0,improvement
                                   ,0);
              }
            }
          }
        }
      }
    }
    if (local_28 != 0) {
      iVar15 = civ_get_adjective(civ2);
      text_set_string_arg(0,iVar15);
      text_set_label_arg(1,unit_types[units[unit2].type].name);
      text_set_string_arg(2,(iptr)&cities[combat_defender_city].name);
      if (autoplay_active == 0) {
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if (aiStack_58[civ3] != 0) {
            if (human_civ == civ3) {
              dlg_game_txt_with_unit(ADDR(0x63448c, ((u8 *)&g.d_0063448c)),unit2);
            }
            else {
              net_send_text_args(0x33,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),3,0,unit2,0)
              ;
            }
          }
        }
      }
    }
    if ((unit_types[units[unit].type].domain == '\0') &&
       (city2 = tile_is_ocean(x2,y2), city2 != 0)) {
      iVar15 = civ_get_adjective(civ);
      text_set_string_arg(1,iVar15);
      text_set_label_arg(2,unit_types[units[unit].type].name);
      if (autoplay_active == 0) {
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if (aiStack_58[civ3] != 0) {
            if (human_civ == civ3) {
              dlg_game_txt_with_unit(ADDR(0x634498, ((u8 *)&g.d_00634498)),unit);
            }
            else {
              net_send_text_args(0x34,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),3,0,unit,0)
              ;
            }
          }
        }
      }
    }
    local_ac = 0;
    unit_type = units[unit].type;
    snd_last_effect_id = -1;
    snd_last_effect_arg = -1;
    if (unit_type == 0x36) {
      snd_play_effect(0x7d,1,0,0);
    }
    else if (unit_type == 0x37) {
      snd_play_effect(0x7e,1,0,0);
    }
    else if (unit_type == 0x38) {
      snd_play_effect(0x7f,1,0,0);
    }
    else if (unit_type == 0x39) {
      snd_play_effect(0x80,1,0,0);
    }
    else if (unit_type == 0x3a) {
      snd_play_effect(0x81,1,0,0);
    }
    else if (unit_type == 0x3b) {
      snd_play_effect(0x82,1,0,0);
    }
    else if (unit_type == 0x3c) {
      snd_play_effect(0x83,1,0,0);
    }
    else if (unit_type == 0x3d) {
      snd_play_effect(0x84,1,0,0);
    }
    else if (unit_type == 0x33) {
      snd_play_effect(0x65,1,0,0);
    }
    else if (unit_type == 0x34) {
      snd_play_effect(0x66,1,0,0);
    }
    else if (unit_type == 0x35) {
      snd_play_effect(0x67,1,0,0);
    }
    else if ((unit_types[units[unit].type].flags & 0x1000) == 0) {
      if (unit_types[units[unit].type].domain == 1) {
        if (unit_types[units[unit2].type].domain == 1) {
          if (units[unit].type < 0x1e) {
            snd_play_effect(0,0,0,0);
          }
          else {
            snd_play_effect(0x52,0,0,0);
          }
        }
        else if (unit_types[units[unit].type].range == '\0') {
          snd_play_effect(0x21,1,0,0);
        }
        else if (units[unit].type < 0x1e) {
          snd_play_effect(0x18,1,0,0);
        }
        else {
          snd_play_effect(0x50,1,0,0);
        }
      }
      else if (unit_types[units[unit].type].domain == 2) {
        if ((unit_types[units[unit].type].flags & 8) == 0) {
          local_ac = 6;
          if (((unit_type == 0x28) || (unit_type == 0x26)) || ((unit_type == 0x27 || (unit_type == 0x25)))) {
            local_ac = 0x2e;
          }
        }
        else {
          snd_play_effect(0x4d,1,0,0);
        }
      }
      else if (unit_type == 0x11) {
        snd_play_effect(0x19,1,0,0);
      }
      else if ((((unit_type == 0xf) || (unit_type == 0x10)) || (unit_type == 0x13)) || (unit_type == 0x12)) {
        snd_play_effect(0x4a,1,0,0);
      }
      else if ((unit_type == 0x14) || (unit_type == 0x15)) {
        snd_play_effect(0xc,1,0,0);
      }
      else if (((unit_type == 7) || (unit_type == 0xb)) || ((unit_type == 10 || (unit_type == 9)))) {
        snd_play_effect(0x22,1,0,0);
      }
      else if ((((unit_type == 8) || (unit_type == 0xd)) || (unit_type == 0xc)) || (unit_type == 0xe)) {
        snd_play_effect(0x26,1,0,0);
      }
      else if ((unit_type < 0x16) || (0x1a < unit_type)) {
        snd_play_effect(0x49,1,0,0);
      }
      else if (unit_type == 0x17) {
        snd_play_effect(10,1,0,0);
      }
      else {
        local_ac = 0x28;
        if (0x17 < unit_type) {
          snd_play_effect(0x1c,1,0,0);
          ui_delay_ticks(0x14);
        }
      }
    }
    else if ((char)unit_types[units[unit].type].attack < 'c') {
      snd_play_effect(0x29,1,0,0);
    }
    anim_combat_defender = unit2;
    anim_combat_defender_x = x;
    anim_combat_defender_y = y;
    if (2 < game.multiplayer) {
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if ((human_civ != civ3) && (aiStack_58[civ3] != 0)) {
          net_send_message(0x9a,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             snd_last_effect_id,snd_last_effect_arg,0,0,0,0,0,0);
          net_send_message(0x70,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             unit,x2,y2,param_2,anim_combat_defender,0,0,0);
        }
      }
    }
    map_animate_unit_move(unit,x2,y2,param_2,0xffffffff,0xffffffff);
    unit_stack_relocate_all(unit,x2,y2,0);
    map_redraw_combat_tiles(x,y,x2,y2);
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if ((human_civ != civ3) && (aiStack_58[civ3] != 0)) {
          net_send_message(0x73,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             x,y,x2,y2,0,0,0,0);
        }
      }
    }
  }
  if ('b' < (char)unit_types[units[unit].type].attack) {
    anim_combat_defender = 0xffffffff;
    unit3 = unit_nuclear_attack(civ,x,y,1);
    if (unit3 == 0) {
      unit_delete(unit,1);
      map_redraw_tile_all_views(x2,y2);
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if ((human_civ != civ3) && (aiStack_58[civ3] != 0)) {
            net_send_message(0x72,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,x2,y2,0,0,0,0,0,0);
          }
        }
      }
    }
    else {
      *(i8 *)&civs[civ].field_50[civ2] = 0;
    }
    if (((unit3 != 0) && ((1 << (civ4 & 0x1f) & (uint)game.human_players) == 0)) &&
       (-1 < (int)combat_defender_city)) {
      ai_respond_to_attack(civ,x,y);
    }
    return 0;
  }
  bVar6 = false;
  if ((local_78 == 0) && (local_34 == 0)) {
    local_c0 = 0;
  }
  else {
    if (((char)unit_types[units[unit2].type].hit_points < 30) &&
       ((char)unit_types[units[unit].type].hit_points < 30)) {
      local_cc = 1;
    }
    else {
      local_cc = 0;
    }
    local_2c = 10 >> local_cc;
    if ((unit_types[units[unit].type].flags & 0x1000) != 0) {
      local_2c = 0;
      bVar6 = false;
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if (aiStack_58[civ3] != 0) {
          if (human_civ == civ3) {
            map_animate_explosion(x,y,local_ac);
          }
          else {
            net_send_message(0x7c,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,x,y,local_ac,0,0,0,0,0);
          }
        }
      }
    }
    do {
      while( true ) {
        city2 = unit_hp_remaining(unit);
        if ((city2 == 0) || (city2 = unit_hp_remaining(unit2), city2 == 0)) {
          local_c0 = unit_hp_remaining(unit);
          goto LAB_00582cbe;
        }
        if (local_a0 == 1 || local_a0 - 1 < 0) {
          local_d0 = 0;
        }
        else {
          local_d0 = _rand();
          local_d0 = local_d0 % local_a0;
        }
        if (local_64 == 1 || local_64 - 1 < 0) {
          local_d4 = 0;
        }
        else {
          local_d4 = _rand();
          local_d4 = local_d4 % local_64;
        }
        local_c0 = (uint)(local_d4 < local_d0);
        if ((bVar19) && (local_c0 != 0)) {
          if (local_a0 == 1 || local_a0 - 1 < 0) {
            local_d8 = 0;
          }
          else {
            local_d8 = _rand();
            local_d8 = local_d8 % local_a0;
          }
          if (local_64 == 1 || local_64 - 1 < 0) {
            local_dc = 0;
          }
          else {
            local_dc = _rand();
            local_dc = local_dc % local_64;
          }
          if (local_d8 < local_dc) {
            local_c0 = 0;
          }
        }
        if (local_c0 == 0) break;
        unit_type = units[unit2].damage;
        units[unit2].damage += (char)local_78;
        if (((bVar5) && (local_2c != 0)) &&
           ((int)((longlong)(ulonglong)units[unit2].damage / (longlong)local_2c) !=
            (int)(uint)unit_type / local_2c)) {
          bVar6 = true;
          net_send_state_diff(0xff,2,0,0,0);
          for (civ3 = 1; (int)civ3 < 8; civ3++) {
            if (aiStack_58[civ3] != 0) {
              if (human_civ == civ3) {
                map_animate_explosion(x,y,local_ac);
                city2 = unit_hp_remaining(unit2);
                if (city2 != 0) {
                  map_redraw_combat_tiles(x,y,x2,y2);
                }
              }
              else {
                net_send_message(0x7c,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ3 * 4) * 0x54),x,
                                   y,local_ac,0,0,0,0,0);
                city2 = unit_hp_remaining(unit2);
                if (city2 != 0) {
                  net_send_message(0x73,*(i32 *)
                                           (&net_player_slots +
                                           *(int *)(&net_civ_slots + civ3 * 4) * 0x54),x,
                                     y,x2,y2,0,0,0,0);
                }
              }
            }
          }
        }
        if ((game.rules & 0x10) == 0) goto LAB_00582cbe;
      }
      unit_type = units[unit].damage;
      units[unit].damage += (char)local_34;
      if (((bVar5) && (local_2c != 0)) &&
         ((int)((longlong)(ulonglong)units[unit].damage / (longlong)local_2c) !=
          (int)(uint)unit_type / local_2c)) {
        bVar6 = true;
        net_send_state_diff(0xff,2,0,0,0);
        for (civ3 = 1; (int)civ3 < 8; civ3++) {
          if (aiStack_58[civ3] != 0) {
            if (human_civ == civ3) {
              map_animate_explosion(x2,y2,local_ac);
              city2 = unit_hp_remaining(unit);
              if (city2 != 0) {
                map_redraw_combat_tiles(x,y,x2,y2);
              }
            }
            else {
              net_send_message(0x7c,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),x2,y2,
                                 local_ac,0,0,0,0,0);
              city2 = unit_hp_remaining(unit);
              if (city2 != 0) {
                net_send_message(0x73,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ3 * 4) * 0x54),x,
                                   y,x2,y2,0,0,0,0);
              }
            }
          }
        }
      }
    } while ((game.rules & 0x10) != 0);
  }
LAB_00582cbe:
  if (local_c0 == 0) {
    active_unit_lost_in_combat = 1;
  }
  if (bVar5) {
    snd_last_effect_id = -1;
    if ((((local_c0 == 0) || (unit_types[units[unit2].type].domain != 1)) ||
        (-1 < (int)combat_defender_city)) &&
       (((local_c0 != 0 || (unit_types[units[unit].type].domain != 1)) ||
        ((unit_types[units[unit].type].flags & 0x1000) != 0)))) {
      if (local_ac != 0) {
        snd_play_effect(0x23,1,0,0);
      }
    }
    else if (local_c0 == 0) {
      if (units[unit].type < 0x1e) {
        snd_play_effect(0x17,1,0,0);
      }
      else {
        snd_play_effect(0x4f,1,0,0);
      }
    }
    else if (units[unit2].type < 0x1e) {
      snd_play_effect(0x17,1,0,0);
    }
    else {
      snd_play_effect(0x4f,1,0,0);
    }
    if ((2 < game.multiplayer) && (snd_last_effect_id != -1)) {
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if ((human_civ != civ3) && (aiStack_58[civ3] != 0)) {
          net_send_message(0x7a,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             snd_last_effect_id,snd_last_effect_arg,0,0,0,0,0,0);
        }
      }
    }
  }
  net_send_state_diff(0xff,2,0,0,0);
  if (bVar5) {
    for (civ3 = 1; (int)civ3 < 8; civ3++) {
      if (aiStack_58[civ3] != 0) {
        if (human_civ == civ3) {
          map_redraw_combat_tiles(x,y,x2,y2);
          if (local_c0 == 0) {
            if (!bVar6) {
              map_animate_explosion(x2,y2,0);
            }
          }
          else if (!bVar6) {
            map_animate_explosion(x,y,0);
          }
        }
        else {
          net_send_message(0x73,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             x,y,x2,y2,0,0,0,0);
          if (local_c0 == 0) {
            if (!bVar6) {
              net_send_message(0x7c,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),x2,y2,0,
                                 0,0,0,0,0);
            }
          }
          else if (!bVar6) {
            net_send_message(0x7c,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,x,y,0,0,0,0,0,0);
          }
        }
      }
    }
  }
  anim_combat_defender = 0xffffffff;
  combat_kill_count = 0;
  if (local_c0 == 0) {
    pcVar1 = (char *)(civ2 + ADDR(0x64c6f0, ((u8 *)&civs + 80)) + civ * 0x594);
    *pcVar1 = *pcVar1 + 1;
    if (local_64 + local_a0 == 1 || local_64 + local_a0 - 1 < 0) {
      local_e4 = 0;
    }
    else {
      local_e4 = _rand();
      local_e4 = local_e4 % (local_64 + local_a0);
    }
    if ((local_e4 <= local_a0) || (city2 = civ_has_wonder(civ2,7), city2 != 0)) {
      unit_promote_veteran(unit2);
    }
  }
  else {
    *(i8 *)&civs[civ].field_50[civ2] = 0;
    if (local_64 + local_a0 == 1 || local_64 + local_a0 - 1 < 0) {
      local_e0 = 0;
    }
    else {
      local_e0 = _rand();
      local_e0 = local_e0 % (local_64 + local_a0);
    }
    if ((local_e0 <= local_64) || (city2 = civ_has_wonder(civ,7), city2 != 0)) {
      unit_promote_veteran(unit);
    }
  }
  if (local_c0 == 0) {
    local_20 = civ2;
    unit_lift_off_map(unit,1);
    unit_kill_stack_in_combat(unit,unit2,local_8,local_14);
    local_60 = civ;
  }
  else {
    if ((civ2 == 0) && (4 < (char)unit_types[units[unit2].type].role)) {
      bVar7 = true;
    }
    local_20 = civ;
    if ((((int)combat_defender_city < 0) &&
        (uVar17 = tile_improvements(x,y), ((byte)uVar17 & 0x42) != 0x40)) &&
       (city2 = tile_airbase_owner(x,y), city2 < 0)) {
      unit_kill_stack_in_combat(unit2,unit,local_8,local_14);
    }
    else {
      unit_kill_in_combat(unit2,unit,local_8,local_14);
    }
    city = combat_defender_city;
    local_60 = civ2;
    if (-1 < (int)combat_defender_city) {
      cities[combat_defender_city].flags = cities[combat_defender_city].flags | 0x20;
      city2 = tile_is_ocean(x2,y2);
      if (((city2 == 0) && (city2 = city_has_improvement(city,8), city2 == 0)) &&
         ((city2 = civ_has_wonder(civ2,6), city2 == 0 &&
          ((game.difficulty != '\0' || ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0))))))
      {
        cities[city].size--;
        if (cities[city].size == '\0') {
          city_delete(city,0);
          for (local_bc = 1; local_bc < 8; local_bc++) {
            tile_update_known(x,y,local_bc);
          }
          map_redraw_neighbors_all_views(x,y);
          city2 = civ_check_destroyed(civ2,civ);
          if (city2 != 0) {
            local_30 = 0;
            for (civ3 = 1; (int)civ3 < 8; civ3++) {
              *(i32 *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) = 0;
            }
          }
        }
        else {
          city_reveal_to_civ(city,civ);
          city2 = tile_unit_owner(x,y);
          if ((city2 < 0) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0)) {
            iVar15 = tile_landmass(x,y);
            civ_reset_city_production(civ2,iVar15);
          }
        }
      }
      city2 = tile_unit_owner(x,y);
      if ((city2 < 0) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0)) {
        ai_transports_raid_empty_city(city);
      }
    }
  }
  net_send_state_diff(0xff,2,0,0,0);
  if (bVar5) {
    if (2 < game.multiplayer) {
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if ((human_civ != civ3) && (aiStack_58[civ3] != 0)) {
          net_send_message(0x73,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                             x,y,x2,y2,0,0,0,0);
        }
      }
    }
    map_redraw_combat_tiles(x,y,x2,y2);
  }
  if ((autoplay_active == 0) && (1 < combat_kill_count)) {
    text_set_number_arg(0,combat_kill_count);
    if (human_civ == local_60) {
      popup_game(ADDR(0x6344a8, ((u8 *)&g.d_006344a8)));
    }
    else if (human_civ == local_20) {
      popup_game(ADDR(0x6344b8, ((u8 *)&g.d_006344b8)));
    }
    if (((game.multiplayer < 3) || ((1 << ((byte)local_60 & 0x1f) & (uint)game.human_players) == 0))
       || (human_civ == local_60)) {
      if (((2 < game.multiplayer) &&
          ((1 << ((byte)local_20 & 0x1f) & (uint)game.human_players) != 0)) &&
         (human_civ != local_20)) {
        net_send_text_args(0x36,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + local_20 * 4) * 0x54),0,1
                           ,0,0);
      }
    }
    else {
      net_send_text_args(0x35,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + local_60 * 4) * 0x54),0,1,0
                         ,0);
    }
  }
  if (bVar7) {
    uVar18 = ((uint)game.barbarian_activity * 100) / 2;
    civs[civ].gold += uVar18;
    text_set_number_arg(0,uVar18);
    if ((human_civ == civ) && (autoplay_active == 0)) {
      dlg_game_txt_with_unit_flags(ADDR(0x6344c4, ((u8 *)&g.d_006344c4)),0x3e,0);
      status_draw_info(1);
    }
    else if ((2 < game.multiplayer) && (autoplay_active == 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if ((aiStack_58[civ3] != 0) && (human_civ != civ3)) {
          net_send_text_args(0x37,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),1
                             ,0,0x3e,0);
          net_send_message(0x78,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),0
                             ,0,0,0,0,0,0,0);
        }
      }
    }
  }
  if (unit3 != 0) {
    diplo_allies_join_war(civ2,civ);
  }
  if ((autoplay_active == 0) && ((local_30 != 0 || (local_b0 != 0)))) {
    iVar15 = civ_name_plural(civ2);
    text_set_string_arg(0,iVar15);
    iVar15 = civ_name_plural(civ);
    text_set_string_arg(1,iVar15);
    if (game.multiplayer < 3) {
      if (local_30 == 0) {
        if (local_b0 == 1) {
          popup_game(ADDR(0x6344d8, ((u8 *)&g.d_006344d8)));
          diplo_ally_demand_help(civ2,civ);
        }
        else {
          popup_game(ADDR(0x6344e8, ((u8 *)&g.d_006344e8)));
        }
      }
      else {
        popup_game(ADDR(0x6344cc, ((u8 *)&g.d_006344cc)));
      }
    }
    else if (autoplay_active == 0) {
      for (civ3 = 1; (int)civ3 < 8; civ3++) {
        if (*(int *)(civ3 * 4 + ADDR(0x6acb10, ((u8 *)&g.d_006acb0c + 4))) != 0) {
          if (human_civ == civ3) {
            popup_game(ADDR(0x6344f8, ((u8 *)&g.d_006344f8)));
          }
          else {
            net_send_text_args(0x3a,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,2,0,0,0);
          }
        }
        if ((*(int *)(civ3 * 4 + ADDR(0x6acae8, ((u8 *)&g.d_006aca14 + 212))) != 0) && (autoplay_active == 0)) {
          if (human_civ == civ3) {
            if (*(int *)(civ3 * 4 + ADDR(0x6acae8, ((u8 *)&g.d_006aca14 + 212))) == 1) {
              popup_game(ADDR(0x634504, ((u8 *)&g.d_00634504)));
              diplo_ally_demand_help(civ2,civ);
            }
            else {
              popup_game(ADDR(0x634514, ((u8 *)&g.d_00634514)));
            }
          }
          else if (*(int *)(civ3 * 4 + ADDR(0x6acae8, ((u8 *)&g.d_006aca14 + 212))) == 1) {
            net_send_text_args(0x3b,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,2,0,0,0);
            if ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) {
              net_send_message(0x7e,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),civ2,civ,0
                                 ,0,0,0,0,0);
            }
          }
          else {
            net_send_text_args(0x3c,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54)
                               ,2,0,0,0);
          }
        }
      }
    }
  }
  advisor_refresh_if_open(2);
  if (2 < game.multiplayer) {
    net_send_message(0x7f,0xff,2,0,0,0,0,0,0,0);
  }
  if (local_c0 == 0) {
    local_38 = 0;
  }
  else {
    unit3 = (int)game.moving_unit;
    if ((unit_types[units[unit3].type].domain == 1) &&
       (unit_types[units[unit3].type].range != 1)) {
      unit_exhaust_moves(unit3);
    }
    if ((((local_c0 == 0) || ((1 << (civ4 & 0x1f) & (uint)game.human_players) != 0)) ||
        ((int)combat_defender_city < 0)) || (city2 = tile_first_unit(x,y), -1 < city2)) {
      if ((local_c0 != 0) && ((unit_types[units[unit3].type].flags & 0x1000) != 0)) {
        unit_delete(unit3,1);
        local_38 = 0;
      }
    }
    else {
      if ((unit_types[units[unit3].type].flags & 0x1000) == 0) {
        if (((unit_types[units[unit3].type].domain == 1) &&
            (unit_types[units[unit3].type].range != '\0')) &&
           (units[unit3].counter = units[unit3].counter + 1,
           (char)unit_types[units[unit3].type].range <= (char)units[unit3].counter))
        goto LAB_00583d2b;
      }
      else {
        unit_delete(unit3,1);
        map_redraw_neighbors_all_views(x2,y2);
      }
      ai_respond_to_attack(civ,x,y);
      local_38 = 0;
    }
  }
LAB_00583d2b:
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
    for (civ3 = 1; (int)civ3 < 8; civ3++) {
      if ((human_civ != civ3) && (aiStack_58[civ3] != 0)) {
        net_send_message(0xa3,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),0,0
                           ,0,0,0,0,0,0);
        net_send_message(0x75,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),
                           x2,y2,0,0,0,0,0,0);
      }
    }
  }
  return local_38;
}
#undef active_unit_lost_in_combat
#undef anim_combat_defender
#undef anim_combat_defender_x
#undef autoplay_active
#undef combat_kill_count
#undef human_civ
#undef mp_double_moves
#undef scenario_flags
#undef unit_move_flags
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef local_d4
#undef local_d0
#undef local_cc
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_bc
#undef improvement
#undef local_b0
#undef local_ac
#undef local_a0
#undef local_98
#undef local_78
#undef local_6c
#undef local_64
#undef local_60
#undef aiStack_58
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef civ3
#undef local_14
#undef local_10
#undef unit2
#undef local_8

/* 0058a5b0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl unit_sound_editor_global_init(void)

{
  unit_sound_editor_static_init();
  unit_sound_editor_reg_atexit();
  return;
}

/* 0058a5ca auto */
void __cdecl unit_sound_editor_static_init(void)

{
  frame_wnd_ctor((SurfaceWindow *)&unit_sound_editor_window);
  return;
}

/* 0058a5e4 auto */
void __cdecl unit_sound_editor_reg_atexit(void)

{
  _atexit(unit_sound_editor_static_dtor);
  return;
}

/* 0058a601 auto */
void __cdecl unit_sound_editor_static_dtor(void)

{
  frame_wnd_dtor((DibSurface *)&unit_sound_editor_window);
  return;
}

/* 0058a61b auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define _DAT_006ace6c (*(i32 *)((u8 *)&g.d_006ace6c))
#define _DAT_006acf54 (*(i32 *)((u8 *)&g.d_006acf54))
#define _DAT_006ad000 (*(i32 *)((u8 *)&g.d_006ad000))
#define _DAT_006ad024 (*(i32 *)((u8 *)&g.d_006ad024))
#define _DAT_006ad028 (*(i32 *)((u8 *)&g.d_006ad028))
#define _DAT_006ad02c (*(i32 *)((u8 *)&g.d_006ad02c))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
unit_sound_editor_create_wnd(int param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    FUN_005f22d0(&unit_sound_editor_title,&unit_sound_editor_empty_title);
  }
  else {
    FUN_005f22d0(&unit_sound_editor_title,param_1);
  }
  _DAT_006ad02c = &ui_text_font;
  _DAT_006ad024 = &caption_font;
  _DAT_006ad028 = &caption_small_font;
  _DAT_006ace6c = param_2;
  unit_sound_editor_caption_height = param_8;
  unit_sound_editor_border_width = param_9;
  unit_sound_editor_resize_border = param_7;
  _DAT_006acf54 = 0;
  _DAT_006ad000 = 0;
  if ((param_2 & 4) != 0) {
    unit_sound_editor_caption_height = frame_caption_height;
    unit_sound_editor_border_width = frame_border_width;
  }
  if ((param_2 & 8) == 0) {
    local_8 = 0x202;
  }
  else {
    local_8 = 0x802;
  }
  if (unit_sound_editor_caption_height != 0) {
    local_8 = local_8 | 0x400;
  }
  if (param_7 != 0) {
    local_8 = local_8 | 0x1000;
  }
  if ((param_2 & 2) == 0) {
    param_5 += unit_sound_editor_border_width * 2;
    param_6 = param_6 + unit_sound_editor_caption_height + unit_sound_editor_border_width;
  }
  if ((param_2 & 1) != 0) {
    param_3 = (screen_width >> 1) - (param_5 >> 1);
    param_4 = (screen_height >> 1) - (param_6 >> 1);
  }
  if (active_editor_wnd == 0) {
    local_c = 0;
  }
  else {
    local_c = active_editor_wnd + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)&unit_sound_editor_window,0,local_8,param_3,param_4,param_5,param_6,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),
             local_c);
  if (unit_sound_editor_caption_height != 0) {
    wnd_set_caption_height((WndBase *)&unit_sound_editor_wnd,unit_sound_editor_caption_height);
  }
  if (unit_sound_editor_resize_border != 0) {
    wnd_set_resize_border((WndBase *)&unit_sound_editor_wnd,unit_sound_editor_resize_border);
  }
  frame_wnd_layout((FrameWindow *)&unit_sound_editor_window);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef _DAT_006ace6c
#undef _DAT_006acf54
#undef _DAT_006ad000
#undef _DAT_006ad024
#undef _DAT_006ad028
#undef _DAT_006ad02c
#undef local_c
#undef local_8

/* 0058a905 auto */
#define local_508 (*(i8 (*)[256])(frame_ + FRAME_OFF(0)))
#define local_408 (*(char (*)[256])(frame_ + FRAME_OFF(256)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(512)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1268)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1272)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1276)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1280)))
/* WARNING: Removing unreachable block (ram,0x0058a97f) */
/* WARNING: Removing unreachable block (ram,0x0058a9fb) */

void __cdecl unit_sound_editor_pick_wav(int param_1)

{
  i32 uVar1;
  iptr iVar2;
  int iVar3;
  DWORD DVar4;
  i8 *puVar5;
  char *pcVar6;
  i32 uVar7;
  i8 *puVar8;
  i32 uVar9;
  i32 uVar10;
  i8 frame_[FRAME_OFF(1288)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (*(int *)(&unit_sound_effects_by_ctrl + param_1 * 4) < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0058abca */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  }
  else {
    dlg_set_parent_window(ADDR(0x6acda0, ((u8 *)&g.d_006acda0)));
    do {
      uVar10 = 0;
      uVar9 = 0;
      uVar7 = 0;
      uVar1 = label_string(*(i32 *)(label_string_ids + 0x888));
      _sprintf(local_408,s__s____WAV__c__WAV_c_c_00634968,uVar1,uVar7,uVar9,uVar10);
      FUN_005f22d0(local_508,s___WAV_00634980);
      uVar7 = 0;
      uVar1 = 1;
      puVar8 = &unit_sound_wav_default_ext;
      pcVar6 = local_408;
      puVar5 = local_508;
      iVar2 = label_string(*(i32 *)(label_string_ids + 0x88c));
      iVar3 = ui_file_name_dialog(ADDR(0x6acda0, ((u8 *)&g.d_006acda0)),iVar2,(iptr)puVar5,(iptr)pcVar6,(iptr)puVar8,uVar1,uVar7);
      if (iVar3 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0058abca */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
        goto LAB_0058abe0;
      }
      dialog_load_text(&local_308,ADDR(0x634998, ((u8 *)&g.d_00634998)),ADDR(0x63498c, ((u8 *)&g.d_0063498c)),0x801);
      do {
        local_308.field_dc = 0;
        local_14 = dlg_show_modal(&local_308,0);
        if (local_308.field_dc != 0) {
          snd_wave_play((iptr)local_508,0,0,0);
        }
      } while (local_308.field_dc != 0);
      dialog_close(&local_308);
      dialog_init_defaults(&local_308);
    } while (local_14 != 0);
    FUN_005f22d0(local_408,&scenario_dir_path);
    FUN_005f22e0(local_408,s__SOUND_006349a0);
    DVar4 = GetFileAttributesA(local_408);
    if (DVar4 == 0xffffffff) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0058abca */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    }
    else {
      FUN_005f22e0(local_408,&unit_sound_path_sep_str);
      FUN_005f22e0(local_408,s_AIRCOMBT_0062af70 + *(int *)(&unit_sound_effects_by_ctrl + param_1 * 4) * 9);
      FUN_005f22e0(local_408,&unit_sound_wav_suffix_str);
      iVar3 = file_exists((iptr)local_408);
      if ((iVar3 == 0) || (iVar3 = FUN_005f66b0(local_408), iVar3 == 0)) {
        file_copy((iptr)local_508,(iptr)local_408);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0058abca */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    }
  }
LAB_0058abe0:
  return;
}
#undef local_508
#undef local_408
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0058abee auto */
#define unit_sound_editor_running (*(i32 *)((u8 *)&g.d_006acd50))
void __cdecl unit_sound_editor_ok_clicked(void)

{
  unit_sound_editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)&unit_sound_editor_wnd);
  return;
}
#undef unit_sound_editor_running

/* 0058ac13 auto */
#define unit_sound_editor_running (*(i32 *)((u8 *)&g.d_006acd50))
void __cdecl unit_sound_editor_cancel_clicked(void)

{
  unit_sound_editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)&unit_sound_editor_wnd);
  return;
}
#undef unit_sound_editor_running

/* 0058ac38 auto */
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl unit_sound_editor_redraw(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption((FrameWindow *)&unit_sound_editor_window);
  gfx_fill_rect(ADDR(0x6acd58, ((u8 *)&g.d_006acd58)),ADDR(0x6ad014, ((u8 *)&g.d_006ad014)),0x1d);
  text_set_surface(ADDR(0x6acd58, ((u8 *)&g.d_006acd58)));
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(10,10,0,0);
  iVar1 = font_line_spacing((GameFont *)dialog_font_ptr);
  iVar1 += 8;
  iVar2 = unit_sound_editor_client_width + (unit_sound_editor_client_width >> 0x1f & 3U);
  iVar3 = iVar2 >> 2;
  for (local_28 = 0; local_28 < 6; local_28++) {
    iVar4 = (iVar1 * 3) / 2 + (local_28 / 3) * iVar1 * 4 + unit_sound_editor_client_y;
    iVar5 = (local_28 % 3) * iVar3 * 5;
    iVar5 = ((int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2) + ((int)(iVar3 + (iVar2 >> 0x1f & 3U)) >> 2)
            + unit_sound_editor_client_x;
    rect_set_xywh((iptr)local_14,iVar5,iVar4,iVar3,iVar1);
    gfx_draw_bevel_rect(ADDR(0x6acd58, ((u8 *)&g.d_006acd58)),(iptr)local_14,10,10);
    if (-1 < *(int *)(&unit_sound_slot_effects + local_28 * 4)) {
      text_clear();
      text_append_str((iptr)(s_AIRCOMBT_0062af70 + *(int *)(&unit_sound_slot_effects + local_28 * 4) * 9));
      text_append_str(ADDR(0x6349b4, ((u8 *)&g.d_006349b4)));
      text_draw_centered(ADDR(0x6acd58, ((u8 *)&g.d_006acd58)),ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5 + iVar3 / 2,iVar4 + 4,0);
    }
  }
  text_clear();
  text_append_label(0x25b);
  text_draw_centered(ADDR(0x6acd58, ((u8 *)&g.d_006acd58)),ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_sound_editor_client_x + unit_sound_editor_client_width / 2,unit_sound_editor_client_y + 10,0);
  wnd_blit_surface((DibSurface *)&unit_sound_editor_window);
  return;
}
#undef local_28
#undef local_14

/* 0058ae6c auto */
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(40)))
void __cdecl unit_sound_editor_on_dblclick(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  param_2 -= unit_sound_editor_client_y;
  param_1 -= unit_sound_editor_client_x;
  iVar1 = font_line_spacing((GameFont *)dialog_font_ptr);
  iVar1 += 8;
  iVar2 = unit_sound_editor_client_width + (unit_sound_editor_client_width >> 0x1f & 3U);
  iVar3 = iVar2 >> 2;
  local_2c = 0;
  while( true ) {
    if (5 < local_2c) {
      return;
    }
    iVar4 = (local_2c % 3) * iVar3 * 5;
    rect_set_xywh((iptr)&local_18,
                       ((int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2) +
                       ((int)(iVar3 + (iVar2 >> 0x1f & 3U)) >> 2),
                       (iVar1 * 3) / 2 + (local_2c / 3) * iVar1 * 4,iVar3,iVar1);
    if ((-1 < *(int *)(&unit_sound_slot_effects + local_2c * 4)) &&
       (iVar4 = point_in_rect_ltrb(param_1,param_2,local_18,local_14,local_10,local_c), iVar4 != 0))
    break;
    local_2c++;
  }
  local_8 = game.game_options;
  game.game_options = game.game_options | 0x10;
  snd_play_effect(*(iptr *)(&unit_sound_slot_effects + local_2c * 4),0,0,0);
  game.game_options = local_8;
  return;
}
#undef local_2c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0058afb6 auto */
#define _DAT_006acd38 (*(i32 *)((u8 *)&g.d_006acd38))
#define _DAT_006acd40 (*(i32 *)((u8 *)&g.d_006acd40))
#define _DAT_006acd44 (*(i32 *)((u8 *)&g.d_006acd44))
#define _DAT_006acd48 (*(i32 *)((u8 *)&g.d_006acd48))
#define _DAT_006acd4c (*(i32 *)((u8 *)&g.d_006acd4c))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl unit_sound_editor_set_slots(int param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = -1;
  for (local_8 = 0; local_8 < 6; local_8++) {
    *(i32 *)(&unit_sound_slot_effects + local_8 * 4) = 0xffffffff;
  }
  if (*(int *)(&editor_item_field8 + param_1 * 0x58) != 0) {
    if (param_1 == 0x36) {
      _DAT_006acd38 = 0x7d;
    }
    else if (param_1 == 0x37) {
      _DAT_006acd38 = 0x7e;
    }
    else if (param_1 == 0x38) {
      _DAT_006acd38 = 0x7f;
    }
    else if (param_1 == 0x39) {
      _DAT_006acd38 = 0x80;
    }
    else if (param_1 == 0x3a) {
      _DAT_006acd38 = 0x81;
    }
    else if (param_1 == 0x3b) {
      _DAT_006acd38 = 0x82;
    }
    else if (param_1 == 0x3c) {
      _DAT_006acd38 = 0x83;
    }
    else if (param_1 == 0x3d) {
      _DAT_006acd38 = 0x84;
    }
    else if (param_1 == 0x33) {
      _DAT_006acd38 = 0x65;
    }
    else if (param_1 == 0x34) {
      _DAT_006acd38 = 0x66;
    }
    else if (param_1 == 0x35) {
      _DAT_006acd38 = 0x67;
    }
    else if (((&editor_item_flags_byte1)[param_1 * 0x58] & 0x10) == 0) {
      if (*(int *)(&editor_item_field3 + param_1 * 0x58) == 1) {
        if (*(int *)(&editor_item_field7 + param_1 * 0x58) == 0) {
          _DAT_006acd38 = 0x21;
          if (param_1 < 0x1e) {
            _DAT_006acd48 = 0x17;
          }
          else {
            _DAT_006acd48 = 0x4f;
          }
        }
        else if (param_1 < 0x1e) {
          _DAT_006acd38 = 0;
          _DAT_006acd44 = 0x18;
          _DAT_006acd48 = 0x17;
          _DAT_006acd4c = 0x1a;
        }
        else {
          _DAT_006acd38 = 0x52;
          _DAT_006acd44 = 0x50;
          _DAT_006acd48 = 0x4f;
          _DAT_006acd4c = 0x4e;
        }
      }
      else if (*(int *)(&editor_item_field3 + param_1 * 0x58) == 2) {
        if (((&editor_item_flags)[param_1 * 0x58] & 8) == 0) {
          local_10 = 6;
          if (((param_1 == 0x28) || (param_1 == 0x26)) || ((param_1 == 0x27 || (param_1 == 0x25))))
          {
            local_10 = 0x2e;
          }
        }
        else {
          _DAT_006acd38 = 0x4d;
        }
      }
      else if (param_1 == 0x11) {
        _DAT_006acd38 = 0x19;
      }
      else if ((((param_1 == 0xf) || (param_1 == 0x10)) || (param_1 == 0x13)) || (param_1 == 0x12))
      {
        _DAT_006acd38 = 0x4a;
      }
      else if ((param_1 == 0x14) || (param_1 == 0x15)) {
        _DAT_006acd38 = 0xc;
      }
      else if (((param_1 == 7) || (param_1 == 0xb)) || ((param_1 == 10 || (param_1 == 9)))) {
        _DAT_006acd38 = 0x22;
      }
      else if ((((param_1 == 8) || (param_1 == 0xd)) || (param_1 == 0xc)) || (param_1 == 0xe)) {
        _DAT_006acd38 = 0x26;
      }
      else if ((param_1 < 0x16) || (0x1a < param_1)) {
        _DAT_006acd38 = 0x49;
      }
      else if (param_1 == 0x17) {
        _DAT_006acd38 = 10;
      }
      else {
        local_10 = 0x28;
        if (0x17 < param_1) {
          _DAT_006acd38 = 0x1c;
        }
      }
    }
    else if (*(int *)(&editor_item_field8 + param_1 * 0x58) < 99) {
      _DAT_006acd38 = 0x29;
    }
    else {
      _DAT_006acd38 = 0x32;
    }
  }
  unit_sound_orders_effect = local_10;
  if (-1 < local_10) {
    _DAT_006acd40 = 0x23;
  }
  for (local_8 = 0; local_8 < 6; local_8++) {
    if (*(int *)(&unit_sound_slot_effects + local_8 * 4) < 0) {
      ctrl_disable((Control *)(local_8 * 0x3c + param_2));
    }
    else {
      ctrl_enable((Control *)(local_8 * 0x3c + param_2));
    }
  }
  return;
}
#undef _DAT_006acd38
#undef _DAT_006acd40
#undef _DAT_006acd44
#undef _DAT_006acd48
#undef _DAT_006acd4c
#undef local_10
#undef local_8

/* 0058b47e auto */
#define unit_sound_editor_running (*(int *)((u8 *)&g.d_006acd50))
#define _DAT_006ace88 (*(i32 *)((u8 *)&g.d_006ace88))
#define local_214 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_210 (*(Control *)(frame_ + FRAME_OFF(8)))
#define local_1d4 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_1d0 (*(Control (*)[6])(frame_ + FRAME_OFF(72)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(432)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(436)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(440)))
#define local_5c (*(i8 (*)[16])(frame_ + FRAME_OFF(444)))
#define local_4c (*(Control *)(frame_ + FRAME_OFF(460)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(520)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(524)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(528)))
/* WARNING: Removing unreachable block (ram,0x0058b6f2) */
/* WARNING: Removing unreachable block (ram,0x0058b77b) */
/* WARNING: Removing unreachable block (ram,0x0058b5ea) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl unit_sound_editor_run(iptr param_1,i32 param_2)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(536)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  button_ctor(&local_4c);
  local_8 = 0;
  button_ctor(&local_210);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  FUN_005f2620(local_1d0,0x3c,6,button_ctor,ctrl_dtor)
  ;
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
  unit_sound_editor_running = 1;
  unit_sound_editor_create_wnd(param_1,0xd,0,0,0x21c,0x118,0,0,0);
  local_68 = font_line_spacing((GameFont *)dialog_font_ptr);
  local_68 += 8;
  local_60 = (int)(unit_sound_editor_client_width + (unit_sound_editor_client_width >> 0x1f & 3U)) >> 2;
  for (local_214 = 0; local_214 < 6; local_214++) {
    local_1d4 = local_68 * 3 + (local_214 / 3) * local_68 * 4 + unit_sound_editor_client_y;
    iVar1 = (local_214 % 3) * local_60 * 5;
    local_64 = ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) +
               ((int)(local_60 + (local_60 >> 0x1f & 3U)) >> 2) + unit_sound_editor_client_x;
    rect_set_xywh((iptr)local_5c,local_64,local_1d4,local_60,local_68);
    iVar2 = label_string(*(i32 *)
                                (label_string_ids + *(int *)(&unit_sound_button_label_ids + local_214 * 4) * 4));
    button_create
              (local_1d0 + local_214,ADDR(0x6acda0, ((u8 *)&g.d_006acda0)),local_214 + 0xc9,(iptr)local_5c,iVar2);
    button_set_callback(local_1d0 + local_214,ADDR(0x403b4d, unit_sound_editor_pick_wav));
  }
  unit_sound_editor_set_slots(param_2,(iptr)local_1d0);
  local_60 = (unit_sound_editor_client_width - 6) / 2;
  local_1d4 = (unit_sound_editor_client_y + _DAT_006ace88) - (local_68 + 2);
  local_64 = unit_sound_editor_client_x + 2;
  rect_set_xywh((iptr)local_5c,local_64,local_1d4,local_60,local_68);
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create(&local_4c,ADDR(0x6acda0, ((u8 *)&g.d_006acda0)),0x65,(iptr)local_5c,iVar2);
  button_set_callback(&local_4c,ADDR(0x4022c0, unit_sound_editor_ok_clicked));
  local_64 = local_64 + local_60 + 2;
  rect_set_xywh((iptr)local_5c,local_64,local_1d4,local_60,local_68);
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create(&local_210,ADDR(0x6acda0, ((u8 *)&g.d_006acda0)),0x66,(iptr)local_5c,iVar2);
  button_set_callback(&local_210,ADDR(0x402da1, unit_sound_editor_cancel_clicked));
  ctrl_set_cancel_button(&local_210);
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)&unit_sound_editor_wnd_handlers,ADDR(0x402559, unit_sound_editor_on_dblclick));
  wnd_set_redraw_callback((SurfaceWindow *)&unit_sound_editor_window,ADDR(0x4017d5, unit_sound_editor_redraw));
  wnd_repaint((SurfaceWindow *)&unit_sound_editor_window);
  window_show((C_004083b0_4 *)&unit_sound_editor_window);
  wnd_run_modal_loop((C_00408010_b8 *)&unit_sound_editor_wnd);
  while (unit_sound_editor_running != 0) {
    win_pump_one_message();
  }
  dlg_set_parent_window(0);
  frame_wnd_close((DibSurface *)&unit_sound_editor_window);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_0058b859 */ { FUN_005f2490((iptr)&local_1d0,0x3c,6,ctrl_dtor); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_0058b86f */ { ctrl_dtor((Control *)((iptr)&local_210)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0058b87b */ { ctrl_dtor((Control *)((iptr)&local_4c)); }
  return;
}
#undef unit_sound_editor_running
#undef _DAT_006ace88
#undef local_214
#undef local_210
#undef local_1d4
#undef local_1d0
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0058bdfd auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
void __cdecl unit_cmd_wait(void)

{
  units[game.active_unit].flags = units[game.active_unit].flags | 0x4000;
  unit_blink_active = 0;
  unit_blink_phase = 0;
  mapviews_redraw_cursor();
  unit_activate_next(0);
  return;
}
#undef unit_blink_active
#undef unit_blink_phase

/* 0058be56 auto */
#define city_turn_processing (*(i32 *)((u8 *)&g.d_0062edf8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_118 (*(i8 (*)[260])(frame_ + FRAME_OFF(0)))
#define y2 (*(int *)(frame_ + FRAME_OFF(260)))
#define x2 (*(int *)(frame_ + FRAME_OFF(264)))
#define y3 (*(int *)(frame_ + FRAME_OFF(268)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(272)))
void __cdecl unit_cmd_build_city(void)

{
  iptr unit;
  iptr civ;
  iptr iVar3;
  iptr city2;
  iptr x;
  int iVar6;
  uptr city;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  unit = (iptr)game.active_unit;
  x2 = (int)units[unit].x;
  y2 = (int)units[unit].y;
  civ = (iptr)units[unit].owner;
  if (unit_types[units[unit].type].role == 5) {
    iVar3 = tile_is_ocean(x2,y2);
    if (iVar3 == 0) {
      city2 = city_at(x2,y2);
      if (city2 < 0) {
        for (local_8 = 0; local_8 < 8; local_8++) {
          x = map_wrap_x((char)(&dir_dx_table)[local_8] + x2);
          y3 = (char)(&dir_dy_table)[local_8] + y2;
          iVar6 = map_in_bounds(x,y3);
          if ((iVar6 != 0) && (iVar6 = tile_city_owner(x,y3), -1 < iVar6)) {
            x = city_at(x,y3);
            popup_game_with_city(ADDR(0x6349f8, ((u8 *)&g.d_006349f8)),x);
            return;
          }
        }
        city = city_create(x2,y2,civ);
        if (-1 < (int)city) {
          iVar6 = dlg_game_text_input(ADDR(0x634a08, ((u8 *)&g.d_00634a08)),0xf,(iptr)&cities[city].name,(iptr)local_118);
          if (iVar6 == 0) {
            unit_found_city(unit,city,(iptr)local_118);
            text_set_string_arg(0,(iptr)&cities[city].name);
            text_clear();
            text_append_year((int)game.year);
            text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
            snd_play_effect(7,1,0,0);
            popup_city_picture_zoom(ADDR(0x634a14, ((u8 *)&g.d_00634a14)),city,0x4c,1,civ);
            if ((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (civs[civ].num_cities == 1)) {
              popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x634a1c, ((u8 *)&g.d_00634a1c)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
            }
            city_turn_processing = 1;
            city_window_begin_notice((C_004083b0_4 *)&city_window);
            city_window_open((C_004083b0_12c *)&city_window,city);
            city_window_end_notice((C_004083b0_12c *)&city_window);
            city_turn_processing = 0;
          }
          else {
            city_delete(city,0);
            leaders[civs[civ].tribe].city_name_index =
                 leaders[civs[civ].tribe].city_name_index + 0xff;
          }
        }
      }
      else if ((int)cities[city2].size < (int)(uint)cosmic.aqueduct_size) {
        cities[city2].size++;
        unit_delete(unit,1);
        city_window_refresh_if_city((FrameWindow *)&city_window,city2);
        map_redraw_area_all_views(x2,y2,1,human_civ,1);
      }
      else {
        text_set_number_arg_u8(0,CONCAT31(cities[city2].size >> 7,cosmic.aqueduct_size));
        popup_game_with_city(ADDR(0x6349f0, ((u8 *)&g.d_006349f0)),city2);
      }
    }
    else {
      popup_game(ADDR(0x6349e4, ((u8 *)&g.d_006349e4)));
    }
  }
  else {
    dlg_game_txt_with_unit_flags(ADDR(0x6349d4, ((u8 *)&g.d_006349d4)),0,(ui_large_screen == 0) - 1 & 8);
  }
  return;
}
#undef city_turn_processing
#undef human_civ
#undef ui_large_screen
#undef unit_blink_active
#undef local_118
#undef y2
#undef x2
#undef y3
#undef local_8

/* 0058c295 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define x2 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl unit_cmd_disband(void)

{
  char civ;
  short x;
  short y;
  iptr iVar4;
  int city;
  int iVar7;
  uptr city2;
  iptr iVar6;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (moving_units_mode == 1) {
    unit = (iptr)game.active_unit;
  }
  else {
    x2 = (int)map_cursor_x;
    y2 = (iptr)map_cursor_y;
    unit = tile_first_unit(x2,y2);
  }
  if ((game.multiplayer < 3) || (units[unit].owner == human_civ)) {
    if (unit < 0) {
      if (((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) != 0) && (game.multiplayer == '\0')) &&
         (city2 = city_at(x2,y2), -1 < (int)city2)) {
        civ = cities[city2].owner;
        text_set_string_arg_b(0,(iptr)&cities[city2].name);
        iVar6 = popup_game_with_city(ADDR(0x634a34, ((u8 *)&g.d_00634a34)),city2);
        if (iVar6 == 1) {
          city_delete(city2,0);
          civ_check_destroyed((int)civ,0);
          map_redraw_all_views(human_civ,1);
        }
      }
    }
    else if ((units[unit].owner == human_civ) || (game.reveal_map != '\0')) {
      unit_blink_active = 0;
      text_set_label_arg(0,unit_types[units[unit].type].name);
      iVar4 = dlg_game_txt_with_unit(ADDR(0x634a2c, ((u8 *)&g.d_00634a2c)),unit);
      if (iVar4 == 1) {
        x = units[unit].x;
        y = units[unit].y;
        city = city_at((int)x,(int)y);
        if (-1 < city) {
          cities[city].shield_box =
               (short)((int)((int)(char)unit_types[units[unit].type].cost *
                            (uint)cosmic.shield_box_rows) / 2) + cities[city].shield_box;
          iVar7 = citywnd_get_city((C_004083b0_4 *)&city_window);
          if (iVar7 == city) {
            city_save_build_state(city);
          }
          iVar7 = citywnd_get_city((C_004083b0_4 *)&city_window);
          if (iVar7 == city) {
            city_window_refresh((FrameWindow *)&city_window);
          }
        }
        unit_delete_with_cargo(unit,1);
        map_redraw_area_all_views((int)x,(int)y,0,human_civ,1);
      }
    }
  }
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef unit_blink_active
#undef unit
#undef y2
#undef x2

/* 0058c65e auto */
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
void __cdecl unit_cmd_terraform(iptr param_1)

{
  char cVar1;
  byte bVar2;
  iptr unit;
  int x;
  int y;
  int civ;
  int iVar7;
  i32 uVar8;
  byte *pbVar9;
  uint uVar10;
  
  unit = (iptr)game.active_unit;
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  civ = (int)units[unit].owner;
  bVar2 = tile_terrain(x,y);
  unit_blink_active = 0;
  if (unit_types[units[unit].type].role != 5) {
    popup_game_with_improvement(ADDR(0x634a3c, ((u8 *)&g.d_00634a3c)),0,8);
    return;
  }
  if (param_1 == 10) {
    iVar7 = civ_has_advance(civ,0x42);
    if (iVar7 == 0) {
      popup_game_with_advance(ADDR(0x634a4c, ((u8 *)&g.d_00634a4c)),0x42,8);
      return;
    }
    iVar7 = tile_city_owner(x,y);
    if (((-1 < iVar7) || (uVar8 = tile_improvements(x,y), ((byte)uVar8 & 0x42) == 0x40)) ||
       (iVar7 = tile_is_ocean(x,y), iVar7 != 0)) {
      dlg_game_txt_with_unit(ADDR(0x634a54, ((u8 *)&g.d_00634a54)),unit);
      return;
    }
    iVar7 = tile_airbase_owner(x,y);
    if (-1 < iVar7) {
      dlg_game_txt_with_unit(ADDR(0x634a60, ((u8 *)&g.d_00634a60)),unit);
      return;
    }
  }
  if (param_1 == 4) {
    iVar7 = civ_has_advance(civ,0x12);
    if (iVar7 == 0) {
      popup_game_with_advance(ADDR(0x634a6c, ((u8 *)&g.d_00634a6c)),0x12,8);
      return;
    }
    iVar7 = tile_city_owner(x,y);
    if (((-1 < iVar7) || (iVar7 = tile_is_ocean(x,y), iVar7 != 0)) ||
       (uVar8 = tile_improvements(x,y), ((byte)uVar8 & 0x42) == 0x40)) {
      dlg_game_txt_with_unit(ADDR(0x634a7c, ((u8 *)&g.d_00634a7c)),unit);
      return;
    }
    uVar8 = tile_improvements(x,y);
    if (((byte)uVar8 & 0x42) == 0x40) {
      dlg_game_txt_with_unit(ADDR(0x634a88, ((u8 *)&g.d_00634a88)),unit);
      return;
    }
  }
  if (param_1 == 5) {
    iVar7 = tile_city_owner(x,y);
    if ((-1 < iVar7) || (iVar7 = tile_is_ocean(x,y), iVar7 != 0)) {
      dlg_game_txt_with_unit(ADDR(0x634a94, ((u8 *)&g.d_00634a94)),unit);
      return;
    }
    pbVar9 = (byte *)tile_at(x,y);
    if (((*pbVar9 & 0x80) != 0) && (iVar7 = civ_has_advance(civ,7), iVar7 == 0)) {
      popup_game_with_advance(ADDR(0x634aa0, ((u8 *)&g.d_00634aa0)),7,8);
      return;
    }
    uVar10 = tile_improvements(x,y);
    if ((uVar10 & 0x20) != 0) {
      dlg_game_txt_with_unit(ADDR(0x634ab0, ((u8 *)&g.d_00634ab0)),unit);
      return;
    }
    uVar10 = tile_improvements(x,y);
    if (((uVar10 & 0x10) != 0) && (iVar7 = civ_has_advance(civ,0x43), iVar7 == 0)) {
      popup_game_with_advance(ADDR(0x634abc, ((u8 *)&g.d_00634abc)),0x43,8);
      return;
    }
  }
  if (((param_1 == 6) || (param_1 == 7)) &&
     (cVar1 = *(char *)(param_1 + ADDR(0x627cc8, ((u8 *)&terrain_types + 8)) + (uint)bVar2 * 0x18), cVar1 < '\0')) {
    if (cVar1 == -1) {
      dlg_game_txt_with_unit(ADDR(0x634ac8, ((u8 *)&g.d_00634ac8)),unit);
      return;
    }
    iVar7 = tile_city_owner(x,y);
    if (-1 < iVar7) {
      dlg_game_txt_with_unit(ADDR(0x634ad4, ((u8 *)&g.d_00634ad4)),unit);
      return;
    }
    if (param_1 == 7) {
      uVar8 = tile_improvements(x,y);
      if (((byte)uVar8 & 0xc) == 8) {
        popup_game_with_sprite(ADDR(0x634ae0, ((u8 *)&g.d_00634ae0)),ADDR(0x644730, ((u8 *)&g.d_00644730)),0);
        return;
      }
    }
    else {
      iVar7 = tile_has_irrigation_source(x,y);
      if (iVar7 == 0) {
        dlg_game_txt_with_unit(ADDR(0x634af0, ((u8 *)&g.d_00634af0)),unit);
        return;
      }
      uVar8 = tile_improvements(x,y);
      if (((byte)uVar8 & 0xc) == 0xc) {
        dlg_game_txt_with_unit(ADDR(0x634af8, ((u8 *)&g.d_00634af8)),unit);
        return;
      }
      uVar10 = tile_improvements(x,y);
      if (((uVar10 & 4) != 0) && (civ = civ_has_advance(civ,0x46), civ == 0)) {
        popup_game_with_advance(ADDR(0x634b08, ((u8 *)&g.d_00634b08)),0x46,8);
        return;
      }
    }
  }
  if (param_1 == 8) {
    civ = tile_is_ocean(x,y);
    if (civ != 0) {
      dlg_game_txt_with_unit(ADDR(0x634b14, ((u8 *)&g.d_00634b14)),unit);
      return;
    }
    if (units[unit].type != 1) {
      dlg_game_txt_with_unit_flags(ADDR(0x634b20, ((u8 *)&g.d_00634b20)),1,(ui_large_screen == 0) - 1 & 8);
      return;
    }
  }
  if ((param_1 == 9) && (uVar10 = tile_improvements(x,y), (uVar10 & 0x80) == 0)) {
    popup_game_with_sprite(ADDR(0x634b2c, ((u8 *)&g.d_00634b2c)),ADDR(0x641808, ((u8 *)&g.d_00641808)),8);
  }
  else {
    map_redraw_tile_all_views(x,y);
    unit_do_terrain_work(unit,param_1);
  }
  return;
}
#undef ui_large_screen
#undef unit_blink_active

/* 0058cbe1 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_10 (*(i8 *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_cmd_home_city(void)

{
  byte city;
  iptr unit;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  unit = (iptr)game.active_unit;
  iVar3 = city_at((int)units[unit].x,(int)units[unit].y);
  if (iVar3 < 0) {
    unit_go_home(unit);
  }
  else if ((unit_types[units[unit].type].role == 7) && (units[unit].home_city != -1)) {
    dlg_game_txt_with_unit(ADDR(0x634b38, ((u8 *)&g.d_00634b38)),unit);
  }
  else {
    city = units[unit].home_city;
    local_10 = (i8)iVar3;
    units[unit].home_city = local_10;
    city_window_refresh_if_city((FrameWindow *)&city_window,(uint)city);
    city_window_refresh_if_city((FrameWindow *)&city_window,iVar3);
  }
  return;
}
#undef unit_blink_active
#undef local_10

/* 0058cce6 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
void __cdecl unit_cmd_fortify(void)

{
  iptr unit;
  int x;
  int y;
  int iVar4;
  
  unit_blink_active = 0;
  unit = (iptr)game.active_unit;
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  iVar4 = tile_is_ocean(x,y);
  if (iVar4 == 0) {
    if (unit_types[units[unit].type].domain == 1) {
      iVar4 = tile_city_owner(x,y);
      if (iVar4 < 0) {
        iVar4 = tile_airbase_owner(x,y);
        if (iVar4 < 0) goto LAB_0058cd8e;
      }
    }
    units[unit].orders = 1;
    unit_exhaust_moves(unit);
    map_redraw_tile_all_views(x,y);
    city_window_on_unit_change((FrameWindow *)&city_window,unit,-99,-99);
  }
  else {
LAB_0058cd8e:
    popup_game(ADDR(0x634b44, ((u8 *)&g.d_00634b44)));
  }
  return;
}
#undef unit_blink_active

/* 0058cde5 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_cmd_sleep(void)

{
  char cVar1;
  bool bVar2;
  iptr unit;
  int x;
  int y;
  int iVar6;
  iptr x2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  unit = (iptr)game.active_unit;
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  if (unit_types[units[unit].type].domain == 1) {
    bVar2 = false;
    iVar6 = tile_is_ocean(x,y);
    if ((iVar6 != 0) &&
       ((iVar6 = unit_stack_sum(unit,9), iVar6 != 0 ||
        (((unit_types[units[unit].type].flags & 0x1000) != 0 &&
         (iVar6 = unit_stack_sum(unit,10), iVar6 != 0)))))) {
      bVar2 = true;
    }
    if ((!bVar2) && (iVar6 = tile_city_owner(x,y), iVar6 < 0)) {
      popup_game(ADDR(0x634b4c, ((u8 *)&g.d_00634b4c)));
      return;
    }
  }
  if ((unit_types[units[unit].type].flags & 0x20) != 0) {
    bVar2 = false;
    for (local_8 = 0; local_8 < 9; local_8++) {
      x2 = map_wrap_x((char)(&dir_dx_table)[local_8] + x);
      cVar1 = (&dir_dy_table)[local_8];
      iVar6 = map_in_bounds(x2,cVar1 + y);
      if ((iVar6 != 0) && (iVar6 = tile_is_ocean(x2,cVar1 + y), iVar6 == 0)) {
        bVar2 = true;
      }
    }
    if (!bVar2) {
      popup_game(ADDR(0x634b54, ((u8 *)&g.d_00634b54)));
      return;
    }
  }
  unit_set_sleep(unit);
  return;
}
#undef unit_blink_active
#undef local_8

/* 0058cfcd auto */
#define unit_move_flags (*(i8 *)((u8 *)&g.d_006ad0cc))
#define local_310 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(756)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(760)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl unit_cmd_pillage(void)

{
  iptr unit;
  int civ;
  iptr x;
  iptr y;
  iptr iVar5;
  iptr iVar6;
  int city;
  byte bVar8;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_18 = 0;
  dialog_ctor(&local_310,0x4000);
  local_8 = 0;
  unit = (iptr)game.active_unit;
  civ = (int)units[unit].owner;
  x = (iptr)units[unit].x;
  y = (iptr)units[unit].y;
  if (unit_types[units[unit].type].attack == '\0') {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  }
  else if (unit_types[units[unit].type].domain == '\0') {
    iVar5 = tile_city_owner(x,y);
    if (iVar5 < 0) {
      iVar6 = tile_at(x,y);
      local_14 = (uint)*(byte *)(iVar6 + 1);
      if ((*(byte *)(iVar6 + 1) & 0x5c) == 0) {
        popup_game(ADDR(0x634b64, ((u8 *)&g.d_00634b64)));
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
      }
      else {
        dlg_load_game_section(&local_310,ADDR(0x634b6c, ((u8 *)&g.d_00634b6c)),1);
        city = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x634b78, ((u8 *)&g.d_00634b78)));
        if (city == 0) {
          text_read_line(1);
          bVar8 = ((byte)local_14 & 0xc) == 0xc;
          if ((bool)bVar8) {
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xc,0);
          }
          text_read_line(1);
          if (((byte)local_14 & 0xc) == 4) {
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),4,0);
            bVar8++;
          }
          text_read_line(1);
          if (((byte)local_14 & 0xc) == 8) {
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),8,0);
            bVar8++;
          }
          text_read_line(1);
          if (((byte)local_14 & 0x42) == 0x42) {
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x42,0);
            bVar8++;
          }
          text_read_line(1);
          if (((byte)local_14 & 0x42) == 0x40) {
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x40,0);
            bVar8++;
          }
          text_read_line(1);
          if ((local_14 & 0x20) == 0) {
            text_read_line(1);
            if ((local_14 & 0x10) != 0) {
              dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x10,0);
              bVar8++;
            }
          }
          else {
            dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x20,0);
            bVar8++;
          }
          if ((1 < bVar8) &&
             (local_18 = dlg_show_modal(&local_310,0), local_18 < 0)) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
            goto LAB_0058d434;
          }
        }
        city = city_find_nearest(x,y,-1,0xffffffff,-1);
        if (((0 < city) && (civ2 = (int)cities[city].owner, -1 < civ2)) &&
           (civ2 != civ)) {
          unit_move_flags = 1;
          city = diplo_confirm_attack(civ,civ2,0xe);
          if (city != 0) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
            goto LAB_0058d434;
          }
          if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) {
            diplo_declare_war(civ,civ2,-1);
          }
        }
        unit_pillage(unit,local_18);
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
      }
    }
    else {
      popup_game(ADDR(0x634b5c, ((u8 *)&g.d_00634b5c)));
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
    }
  }
  else {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0058d41e */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  }
LAB_0058d434:
  return;
}
#undef unit_move_flags
#undef local_310
#undef civ2
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0058d60a auto */
void __cdecl unit_cmd_paradrop(void)

{
  iptr unit;
  uint uVar1;
  
  unit = (iptr)game.active_unit;
  if ((units[unit].moves_used == '\0') && ((units[unit].flags & 0x10) == 0)) {
    uVar1 = tile_improvements((int)units[unit].x,(int)units[unit].y);
    if ((uVar1 & 2) == 0) {
      dlg_game_txt_with_unit(ADDR(0x634b94, ((u8 *)&g.d_00634b94)),unit);
    }
    else {
      mapviews_set_paradrop_cursor();
    }
  }
  else {
    dlg_game_txt_with_unit(ADDR(0x634b84, ((u8 *)&g.d_00634b84)),unit);
  }
  return;
}

/* 0058d6af auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_32c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_320 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_318 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(780)))
#define y2 (*(int *)(frame_ + FRAME_OFF(784)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(788)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(792)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(796)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(800)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(808)))
void __cdecl unit_cmd_goto_city(void)

{
  u8 uVar1;
  u8 uVar2;
  u8 uVar3;
  iptr unit;
  iptr civ;
  int x;
  int y;
  int iVar8;
  iptr iVar9;
  iptr iVar10;
  int iVar11;
  int iVar12;
  iptr x2;
  int city2;
  uint uVar15;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_318,0x2000);
  local_8 = 0;
  unit = (iptr)game.active_unit;
  civ = (iptr)units[unit].owner;
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  iVar8 = tile_landmass(x,y);
  local_24 = tile_is_ocean(x,y);
  uVar1 = unit_types[units[unit].type].role;
  local_1c = 0;
LAB_0058d7b4:
  do {
    text_set_label_arg(0,unit_types[units[unit].type].name);
    dlg_load_game_section(&local_318,ADDR(0x634ba4, ((u8 *)&g.d_00634ba4)),0x800001);
    local_32c = 0;
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && ((cities[city].owner == civ || (local_1c != 0)))) {
        iVar9 = tile_landmass((int)cities[city].x,(int)cities[city].y);
        if (unit_types[units[unit].type].domain == 2) {
          if (local_24 == 0) {
            city3 = city_at(x,y);
            if (city < 0) goto LAB_0058daa2;
            iVar10 = cities_share_ocean(city3,city);
          }
          else {
            iVar10 = city_adjacent_to_body(city,iVar8);
          }
          if (iVar10 == 0) goto LAB_0058d80c;
        }
        else if (unit_types[units[unit].type].domain == '\0') {
          if (iVar9 != iVar8) goto LAB_0058d80c;
        }
        else if ((unit_types[units[unit].type].domain == 1) &&
                (unit_types[units[unit].type].range != '\0')) {
          uVar2 = unit_types[units[unit].type].range;
          uVar3 = units[unit].counter;
          city2 = unit_max_moves(unit);
          iVar11 = unit_moves_left(unit);
          uVar15 = (uint)cosmic.road_move_mult;
          iVar12 = map_distance(x,y,(int)cities[city].x,(int)cities[city].y)
          ;
          if ((iVar11 + ((int)(char)uVar2 - ((char)uVar3 + 1)) * city2) / (int)uVar15 < iVar12)
          goto LAB_0058d80c;
        }
LAB_0058daa2:
        if (((cities[city].owner == civ) ||
            (*(char *)&cities[city].revealed_size[civ] != '\0')) || (game.reveal_map != '\0'))
        {
          text_clear();
          text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
          if (uVar1 == 5) {
            local_320 = 0;
            for (local_18 = 0; local_18 < 0x14; local_18++) {
              x2 = map_wrap_x((int)cities[city].x + (int)(char)(&city_tile_dx_table)[local_18]);
              y2 = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[local_18];
              city2 = map_in_bounds(x2,y2);
              if ((city2 != 0) &&
                 (uVar15 = tile_improvements(x2,y2), (uVar15 & 0x80) != 0)) {
                local_320++;
              }
            }
            if (local_320 != 0) {
              text_append_space();
              text_append_lparen();
              text_append_int(local_320);
              text_append_space();
              text_append_label(0x2f);
              text_append_rparen();
            }
          }
          if ((cities[city].owner == civ) &&
             (city2 = city_has_improvement(city,0x20), city2 != 0)) {
            text_append_space();
            text_append_lparen();
            text_append_string_id(improvements[0x20].name);
            text_append_rparen();
          }
          dialog_add_option((DialogOptionList *)&local_318,ADDR(0x679640, ((u8 *)&g.d_00679640)),city,0);
          local_32c++;
        }
      }
LAB_0058d80c: ;
    }
    if (local_32c != 0) {
      city2 = dlg_show_modal(&local_318,0);
      if (city2 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0058ddaa */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0058ddc0;
      }
      if (local_318.field_dc == 0) {
        units[unit].orders = 11;
        units[unit].goto_x = cities[city2].x;
        units[unit].goto_y = cities[city2].y;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0058ddaa */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0058ddc0;
      }
      local_1c = (uint)(local_1c == 0);
      goto LAB_0058d7b4;
    }
    if (local_1c != 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0058ddaa */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
LAB_0058ddc0:
      return;
    }
    local_1c = 1;
  } while( true );
}
#undef city
#undef local_32c
#undef local_320
#undef local_318
#undef local_24
#undef y2
#undef local_1c
#undef local_18
#undef city3
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0058ddce auto */
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl unit_cmd_unload(void)

{
  iptr unit2;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  if (-1 < game.active_unit) {
    unit2 = (iptr)game.active_unit;
    if (unit_types[units[unit2].type].domain == 2) {
      units[unit2].flags = units[unit2].flags | 0x4000;
    }
    for (unit = unit_stack_first((int)game.active_unit); -1 < unit;
        unit = unit_next_in_stack(unit)) {
      if ((unit_types[units[unit].type].domain == '\0') && (units[unit].orders == 3)) {
        units[unit].orders = -1;
        iVar2 = unit_is_selectable(unit);
        if (iVar2 != 0) {
          local_c = unit;
        }
      }
    }
    if (-1 < local_c) {
      game.active_unit = (i16)local_c;
      moving_units_mode = 0;
      ui_focus_active_unit(0);
    }
  }
  return;
}
#undef moving_units_mode
#undef local_c
#undef unit

/* 0058df14 auto */
void __cdecl unit_cmd_automate(void)

{
  iptr unit;
  
  unit = (iptr)game.active_unit;
  if (unit_types[units[unit].type].role == 5) {
    units[unit].flags = units[unit].flags | 0x8000;
  }
  return;
}

/* 0058df7b auto */
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_31c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_314 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_310 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(772)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(776)))
#define city (*(iptr *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl unit_cmd_airlift(void)

{
  iptr unit2;
  int civ;
  iptr city2;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  iptr unit3;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_310,0x2000);
  local_8 = 0;
  unit2 = (iptr)game.active_unit;
  if (unit2 < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  }
  else {
    civ = (int)units[unit2].owner;
    if (unit_types[units[unit2].type].domain == 2) {
      dlg_game_txt_with_unit(ADDR(0x634bac, ((u8 *)&g.d_00634bac)),unit2);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
    }
    else if (unit_types[units[unit2].type].domain == 1) {
      dlg_game_txt_with_unit(ADDR(0x634bb8, ((u8 *)&g.d_00634bb8)),unit2);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
    }
    else {
      city2 = city_at((int)units[unit2].x,(int)units[unit2].y);
      if (city2 < 0) {
        popup_game_with_sprite(ADDR(0x634bc4, ((u8 *)&g.d_00634bc4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
      }
      else {
        iVar5 = city_has_improvement(city2,0x20);
        if (iVar5 == 0) {
          popup_game_with_city(ADDR(0x634bd0, ((u8 *)&g.d_00634bd0)),city2);
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
        }
        else if ((cities[city2].flags & 0x10000) == 0) {
          dlg_load_game_section(&local_310,ADDR(0x634bec, ((u8 *)&g.d_00634bec)),1);
          local_314 = 0;
          for (city = 0; city < game.num_cities; city++) {
            if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
                (city != city2)) && (iVar5 = city_has_improvement(city,0x20), iVar5 != 0)) {
              local_314++;
              dialog_add_option
                        ((DialogOptionList *)&local_310,(iptr)&cities[city].name,city,0);
            }
          }
          if (local_314 == 0) {
            popup_game_with_improvement(ADDR(0x634bfc, ((u8 *)&g.d_00634bfc)),0x20,8);
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
          }
          else {
            city = dlg_show_modal(&local_310,0);
            if (city < 0) {
              local_8 = 0xffffffff;
              /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
            }
            else if ((cities[city].flags & 0x10000) == 0) {
              local_31c = 0;
              local_1c = unit2;
              for (unit = 0; unit3 = local_1c, unit < game.num_units;
                  unit = unit + 1) {
                iVar5 = local_31c;
                if (((units[unit].id != 0) && (units[unit].owner != civ)) &&
                   ((unit_types[units[unit].type].role == 3 &&
                    ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + units[unit].owner * 4) & 0x20) != 0)
                    ))) {
                  iVar6 = unit_max_moves(unit);
                  uVar8 = (uint)cosmic.road_move_mult;
                  iVar7 = map_distance((int)cities[city2].x,(int)cities[city2].y,
                                             (int)units[unit].x,(int)units[unit].y);
                  if (iVar6 / (int)uVar8 < iVar7) {
                    iVar6 = unit_max_moves(unit);
                    uVar8 = (uint)cosmic.road_move_mult;
                    iVar7 = map_distance((int)cities[city].x,(int)cities[city].y,
                                               (int)units[unit].x,(int)units[unit].y);
                    if (iVar6 / (int)uVar8 < iVar7) goto LAB_0058e34c;
                  }
                  civ2 = (int)units[unit].owner;
                  iVar5 = local_31c + 1;
                  if ((units[unit].flags & 0x2000) != 0) {
                    iVar5 = local_31c + 2;
                  }
                }
LAB_0058e34c:
                local_31c = iVar5;
              }
              if ((local_31c == 0) ||
                 (civ = dlg_game_txt_with_unit_flags(ADDR(0x634c18, ((u8 *)&g.d_00634c18)),0x1b,(ui_large_screen == 0) - 1 & 8), civ != 0)
                 ) {
                unit_airlift_perform(unit3,city2,city,local_31c,civ2);
                local_8 = 0xffffffff;
                /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
              }
              else {
                local_8 = 0xffffffff;
                /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
              }
            }
            else {
              text_set_string_arg(0,(iptr)&cities[city].name);
              popup_game_with_city(ADDR(0x634c08, ((u8 *)&g.d_00634c08)),city2);
              local_8 = 0xffffffff;
              /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
            }
          }
        }
        else {
          text_set_string_arg(0,(iptr)&cities[city2].name);
          popup_game_with_city(ADDR(0x634bdc, ((u8 *)&g.d_00634bdc)),city2);
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0058e5c4 */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
        }
      }
    }
  }
  return;
}
#undef ui_large_screen
#undef unit
#undef local_31c
#undef local_314
#undef local_310
#undef local_1c
#undef civ2
#undef city
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0058f040: written by hand in src/game/retvals.c */

/* 0058fedb auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_31c (*(int *)(frame_ + FRAME_OFF(4)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_310 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(776)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
i32 __cdecl unit_caravan_enter_city(iptr unit,uptr city)

{
  byte civ2;
  int civ;
  iptr iVar3;
  char city2;
  iptr iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  if (autoplay_active == 0) {
    civ2 = units[unit].owner;
    civ = (int)(char)civ2;
    local_31c = 1;
    if (((int)units[unit].home_city == city) &&
       ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0)) {
      local_31c = 0;
    }
    if (cities[city].owner == civ) {
      if (((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) &&
         ((cities[city].flags & 0x200) != 0)) {
        local_31c = 0;
      }
      if ((units[unit].orders == 11) &&
         ((cities[city].x != units[unit].goto_x ||
          (cities[city].y != units[unit].goto_y)))) {
        local_31c = 0;
      }
    }
    if (((((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) && (human_civ == civ)) &&
        (cities[city].owner == civ)) && (local_31c != 0)) {
      if ((char)units[unit].counter < '\0') {
        text_set_label_arg(0,*(i32 *)(label_string_ids + 0x100));
      }
      else {
        text_set_label_arg(0,commodity_names[(char)units[unit].counter]);
      }
      dialog_load_game_text(&local_30c,ADDR(0x634d14, ((u8 *)&g.d_00634d14)));
      dialog_add_sprite
                ((DialogOptionList *)&local_30c,
                 (iptr)(&unit_sprites + (uint)units[unit].type * 0x3c),0,0);
      if (-1 < (char)units[unit].counter) {
        text_clear();
        text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
        text_append_space();
        local_14 = 0;
        for (local_18 = 0; local_18 < 3; local_18++) {
          if (cities[city].demands[local_18] == units[unit].counter) {
            local_14 = 1;
          }
        }
        if (local_14 == 0) {
          text_append_label(0x134);
        }
        else {
          text_append_label(0x133);
        }
        text_append_space();
        text_append_string_id(commodity_names[(char)units[unit].counter]);
        text_append_period();
        dialog_add_line
                  ((DialogAddLineView *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
      }
      uVar6 = 0;
      iVar5 = 0;
      iVar3 = label_string(*(i32 *)(label_string_ids + 0x284));
      dialog_add_option((DialogOptionList *)&local_30c,iVar3,iVar5,uVar6);
      city2 = (int)units[unit].home_city != city;
      if ((bool)city2) {
        uVar6 = 0;
        iVar5 = 1;
        iVar3 = label_string(*(i32 *)(label_string_ids + 0x288));
        dialog_add_option((DialogOptionList *)&local_30c,iVar3,iVar5,uVar6);
      }
      if (cities[city].building < -0x26) {
        uVar6 = 0;
        iVar5 = 2;
        iVar3 = label_string(*(i32 *)(label_string_ids + 0x28c));
        dialog_add_option((DialogOptionList *)&local_30c,iVar3,iVar5,uVar6);
        city2++;
      }
      local_31c = 0;
      if (city2 != '\0') {
        local_31c = dlg_show_modal(&local_30c,0);
      }
    }
    if (local_31c == 1) {
      unit_caravan_establish_trade(unit,city);
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00590607 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar6 = 1;
    }
    else if (local_31c == 2) {
      if (units[unit].type == '1') {
        snd_play_effect(0x16,1,0,0);
      }
      else {
        snd_play_effect(0x2c,1,0,0);
      }
      cities[city].shield_box =
           (short)(char)unit_types[units[unit].type].cost * (ushort)cosmic.shield_box_rows +
           cities[city].shield_box;
      text_set_string_arg(0,(iptr)&cities[city].name);
      text_set_number_arg(0,(int)(char)unit_types[units[unit].type].cost *
                           (uint)cosmic.shield_box_rows);
      if (cities[city].building < 1) {
        improvement = ~(int)cities[city].building + 1;
      }
      else {
        improvement = (iptr)cities[city].building;
      }
      local_310 = (uint)improvements[improvement].cost * (uint)cosmic.shield_box_rows -
                  (int)cities[city].shield_box;
      if (local_310 < 0) {
        local_310 = 0;
      }
      text_set_number_arg(1,local_310);
      popup_game(ADDR(0x634d20, ((u8 *)&g.d_00634d20)));
      if (units[unit].home_city != -1) {
        cities[(byte)units[unit].home_city].flags =
             cities[(byte)units[unit].home_city].flags | 0x20000;
      }
      unit_destroy_redraw(unit,1);
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00590607 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar6 = 1;
    }
    else {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00590607 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      uVar6 = 0;
    }
  }
  else {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00590607 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    uVar6 = 0;
  }
  return uVar6;
}
#undef autoplay_active
#undef human_civ
#undef local_31c
#undef improvement
#undef local_310
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0059062c auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define nm_stacker_ack_count (*(int *)((u8 *)&g.d_006c914c))
#define saved_human_players (*(i8 *)((u8 *)&g.d_00673b08))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_move_anim_active (*(i32 *)((u8 *)&g.d_00636058))
#define unit_move_flags (*(byte *)((u8 *)&g.d_006ad0cc))
#define _DAT_00673b08 (*(i32 *)((u8 *)&g.d_00673b08))
#define local_120 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_118 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_114 (*(int *)(frame_ + FRAME_OFF(12)))
#define unit7 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define y2 (*(int *)(frame_ + FRAME_OFF(36)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_f0 (*(uint *)(frame_ + FRAME_OFF(48)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(60)))
#define unit5 (*(iptr *)(frame_ + FRAME_OFF(72)))
#define y3 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_c4 (*(uint *)(frame_ + FRAME_OFF(92)))
#define x3 (*(int *)(frame_ + FRAME_OFF(100)))
#define unit4 (*(iptr *)(frame_ + FRAME_OFF(108)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(124)))
#define aiStack_a0 (*(int (*)[8])(frame_ + FRAME_OFF(128)))
#define aiStack_80 (*(int (*)[8])(frame_ + FRAME_OFF(160)))
#define y5 (*(int *)(frame_ + FRAME_OFF(192)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(196)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(200)))
#define local_54 (*(uint *)(frame_ + FRAME_OFF(204)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(208)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(212)))
#define y4 (*(int *)(frame_ + FRAME_OFF(216)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(220)))
#define local_40 (*(uint *)(frame_ + FRAME_OFF(224)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(228)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(232)))
#define local_34 (*(uptr *)(frame_ + FRAME_OFF(236)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(240)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(244)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(248)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(252)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(256)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(260)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(264)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(268)))
#define x5 (*(iptr *)(frame_ + FRAME_OFF(272)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(276)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(280)))
/* WARNING: Removing unreachable block (ram,0x0059103e) */
/* WARNING: Removing unreachable block (ram,0x0059104b) */
/* WARNING: Removing unreachable block (ram,0x00590f5a) */
/* WARNING: Removing unreachable block (ram,0x0059100a) */
/* WARNING: Removing unreachable block (ram,0x00591023) */
/* WARNING: Removing unreachable block (ram,0x00591027) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl unit_move_dir(iptr unit,uptr param_2,i32 param_3)

{
  uint *puVar1;
  short *psVar2;
  u8 uVar3;
  byte civ3;
  u8 uVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  char cVar9;
  SHORT SVar11;
  uptr civ;
  iptr iVar13;
  iptr iVar14;
  byte unit_type;
  int city3;
  uptr city;
  iptr unit3;
  uint uVar17;
  i32 uVar18;
  byte *pbVar19;
  byte *pbVar20;
  uptr uVar21;
  iptr unit6;
  iptr x;
  iptr iVar19;
  iptr iVar22;
  iptr x4;
  int iVar25;
  uint uVar26;
  iptr iVar9;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  aiStack_a0[1] = aiStack_a0[2] = aiStack_a0[3] = aiStack_a0[4] = aiStack_a0[5] = aiStack_a0[6] = aiStack_a0[7] = 1;  /* stale stack the original reads (FRAME_PRESETS) */
  
  local_4c = 0;
  bVar8 = false;
  local_c = 0;
  local_30 = 1;
  bVar6 = false;
  if ((((unit_move_in_progress != 0) || (units[unit].id == 0)) || (units[unit].x < 0)) ||
     (units[unit].y < 0)) {
    return 0;
  }
  unit_move_in_progress = 1;
  unit_move_flags = (byte)param_3;
  win_flush_pending_msgs();
  while( true ) {
    iVar9 = unit;
    unit_move_unanimated_state = '\0';
    bVar7 = false;
    local_a4 = 0;
    local_f0 = 0;
    if ((unit_move_flags & 1) != 0) {
      unit_blink_active = 0;
    }
    local_2c = (int)game.num_units;
    game.field_06 = game.field_06 | 4;
    x3 = (int)units[unit].x;
    y3 = (int)units[unit].y;
    y2 = y3;
    x2 = x3;
    if (-1 < (int)param_2) {
      x2 = map_wrap_x((char)(&dir_dx_table)[param_2] + x3);
      y2 = (char)(&dir_dy_table)[param_2] + y3;
    }
    uVar3 = unit_types[units[unit].type].domain;
    civ3 = units[unit].owner;
    civ = (uptr)(char)civ3;
    iVar13 = city_at(x3,y3);
    if (iVar13 < 0) {
      tile_set_owner(x3,y3,civ,1);
    }
    unit_move_by_local_human = autoplay_active == 0 && human_civ == civ;
    iVar14 = map_in_bounds(x2,y2);
    if (iVar14 == 0) {
      if (((unit_move_flags & 1) != 0) && (unit_move_by_local_human != '\0')) {
        popup_game_with_sprite(ADDR(0x634d2c, ((u8 *)&g.d_00634d2c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      unit = iVar9;
      if (((int)(short)units[unit].flags & 0x8000U) != 0) {
        unit_exhaust_moves(unit);
      }
      goto LAB_00594a80;
    }
    if (((2 < game.multiplayer) && (mp_simultaneous_moves != '\0')) &&
       (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0 && (-1 < (int)param_2)))) {
      city3 = net_lock_map(civ,x3,y3,x2,y2,local_30);
      if (city3 == 0) {
        if (((int)(short)units[unit].flags & 0x8000U) != 0) {
          unit_exhaust_moves(unit);
        }
        goto LAB_00594aaa;
      }
      bVar8 = true;
    }
    cVar9 = tile_terrain(x3,y3);
    unit_type = tile_terrain(x2,y2);
    terrain2 = (uptr)unit_type;
    local_54 = (uint)(cVar9 == '\n');
    local_40 = (uint)(terrain2 == 10);
    civ2 = tile_city_or_unit_owner(x2,y2);
    unit2 = tile_first_unit(x2,y2);
    if (-1 < unit2) {
      civ2 = (uptr)units[unit2].owner;
    }
    city = city_at(x2,y2);
    if (-1 < (int)city) {
      civ2 = (uptr)cities[city].owner;
    }
    if ((int)param_2 < 0) {
      unit_exhaust_moves(unit);
      unit3 = unit;
      goto LAB_00593d80;
    }
    units[unit].flags = units[unit].flags | 0x40;
    if (uVar3 == '\0') {
      if ((((unit2 < 0) && (city3 = tile_in_enemy_zoc(x3,y3,civ), city3 != 0))
          && (city3 = tile_in_enemy_zoc(x2,y2,civ), city3 != 0)) &&
         ((local_54 == 0 && ((unit_types[units[unit].type].flags & 2) == 0)))) {
        if ((unit_move_by_local_human != '\0') && ((unit_move_flags & 1) != 0)) {
          snd_play_effect(0x69,1,0,0);
          if ((unit_move_by_local_human != '\0') && (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0)) {
            popup_game_with_sprite(ADDR(0x634d38, ((u8 *)&g.d_00634d38)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
          }
          map_reveal_adjacent_units(x2,y2,civ);
        }
        unit = iVar9;
        if (((int)(short)units[unit].flags & 0x8000U) != 0) {
          unit_exhaust_moves(unit);
        }
        goto LAB_00594a80;
      }
      if ((unit_types[units[unit].type].role == 7) && (-1 < (int)city)) {
        if ((civ2 != civ) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)
           ) {
          if (2 < game.multiplayer) {
            net_send_message(0x71,0xff,x3,y3,civ,0,0,0,0,0);
          }
          mapviews_ensure_visible(x3,y3,civ);
          ui_delay_ticks(10);
          unit_lift_off_map(unit,1);
          map_animate_unit_move(unit,x3,y3,param_2,0xffffffff,0xffffffff);
          unit_relocate(unit,x3,y3,1);
          if (2 < game.multiplayer) {
            net_send_message(0x75,0xff,x2,y2,0,0,0,0,0,0);
          }
          map_redraw_tile_all_views(x2,y2);
        }
        city3 = unit_caravan_enter_city(unit,city);
        unit = iVar9;
        if (city3 != 0) goto LAB_00594a80;
      }
      if (((unit_types[units[unit].type].role == 6) && (-1 < (int)civ2)) &&
         (civ2 != civ)) {
        if (-1 < (int)city) {
          if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
            if (2 < game.multiplayer) {
              net_send_message(0x71,0xff,x3,y3,civ,0,0,0,0,0);
            }
            mapviews_ensure_visible(x3,y3,civ);
            ui_delay_ticks(0x14);
            unit_lift_off_map(unit,1);
            map_animate_unit_move(unit,x3,y3,param_2,0xffffffff,0xffffffff);
            unit_relocate(unit,x3,y3,1);
            if (2 < game.multiplayer) {
              net_send_message(0x75,0xff,x2,y2,0,0,0,0,0,0);
            }
            map_redraw_tile_all_views(x2,y2);
          }
          spy_city_mission(unit,city);
          unit = iVar9;
          goto LAB_00594a80;
        }
        city3 = spy_unit_mission(unit,unit2,civ);
        unit = iVar9;
        if (city3 != 0) goto LAB_00594a80;
        civ2 = tile_city_or_unit_owner(x2,y2);
      }
      if (((-1 < (int)city) && (-1 < (int)civ2)) &&
         ((civ2 != civ && ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0))))
      {
        local_14 = unit_max_hp(unit);
        local_14 = local_14 / 10;
        city3 = city_has_improvement(city,2);
        if (city3 != 0) {
          local_14 = local_14 << 1;
        }
        local_14 = int_clamp(local_14,0,(uint)units[unit].damage);
        units[unit].damage -= (char)local_14;
        unit_exhaust_moves(unit);
        units[unit].flags = units[unit].flags & 0xffbf;
        if (((autoplay_active == 0) && ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) &&
           (human_civ == civ)) {
          snd_play_effect(0x68,1,0,0);
          unit3 = civ_name_plural(civ2);
          text_set_string_arg(1,unit3);
          text_set_label_arg(2,unit_types[units[unit].type].name);
          popup_game_with_sprite(ADDR(0x634d3c, ((u8 *)&g.d_00634d3c)),(iptr)(&diplo_popup_portrait_sprite +
                                            ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80))
                             ,0);
        }
        unit = iVar9;
        if (((int)(short)units[unit].flags & 0x8000U) != 0) {
          unit_exhaust_moves(unit);
        }
        goto LAB_00594a80;
      }
    }
    if ((uVar3 == '\0') && (local_40 != 0)) {
      unit = iVar9;
      if ((civ2 != civ) || (city3 = unit_stack_sum(unit2,6), city3 < 1))
      goto LAB_00594a80;
      bVar7 = true;
    }
    if ((-1 < unit2) && ((int)units[unit2].owner != civ)) {
      civ2 = (uptr)units[unit2].owner;
      if ((local_54 != 0) && ((uVar3 == '\0' && ((unit_types[units[unit].type].flags & 4) == 0)))
         ) {
        unit = iVar9;
        if (((unit_move_flags & 1) != 0) && (unit_move_by_local_human != '\0')) {
          popup_game_with_sprite(ADDR(0x634d4c, ((u8 *)&g.d_00634d4c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        goto LAB_00594a80;
      }
      if ((local_40 == 0) && (unit = iVar9, (unit_types[units[unit].type].flags & 8) != 0))
      goto LAB_00594a80;
      if (((unit_types[units[unit2].type].flags & 8) != 0) &&
         ((((city3 = unit_stack_sum(unit2,2), city3 == 1 &&
            ((1 << (civ3 & 0x1f) & (uint)units[unit2].visibility) == 0)) &&
           ((int)units[unit2].owner != (uint)civ3)) &&
          ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)))) {
        unit = iVar9;
        if ((unit_move_flags & 1) != 0) {
          units[unit].orders = -1;
          unit_set_seen_by(unit2,civ);
          map_redraw_tile_all_views(x2,y2);
          net_send_message(0x72,0xff,x2,y2,0,0,0,0,0,0);
        }
        goto LAB_00594a80;
      }
      if (unit_types[units[unit].type].role == 6) {
        units[unit].orders = -1;
        local_f0 = (uint)game.human_players & 1 << (civ3 & 0x1f);
        unit = iVar9;
        goto LAB_00594a80;
      }
      if (unit_types[units[unit].type].attack == '\0') {
        if ((((unit_move_flags & 1) != 0) && (unit_move_by_local_human != '\0')) &&
           ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) {
          snd_play_effect(0x69,0,0,0);
          popup_game_with_sprite(ADDR(0x634d54, ((u8 *)&g.d_00634d54)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        unit = iVar9;
        if (((int)(short)units[unit].flags & 0x8000U) != 0) {
          unit_exhaust_moves(unit);
        }
        goto LAB_00594a80;
      }
      if ((((int)city < 0) && (city3 = tile_airbase_owner(x2,y2), city3 < 0)) &&
         ((city3 = unit_stack_sum(unit2,7), city3 != 0 &&
          (((unit_types[units[unit].type].flags & 0x10) == 0 &&
           (city3 = unit_stack_sum(unit2,9), city3 == 0)))))) {
        if (((unit_move_flags & 1) != 0) && (unit_move_by_local_human != '\0')) {
          popup_game_with_sprite(ADDR(0x634d60, ((u8 *)&g.d_00634d60)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        unit = iVar9;
        if (((int)(short)units[unit].flags & 0x8000U) != 0) {
          unit_exhaust_moves(unit);
        }
        goto LAB_00594a80;
      }
      if (((unit_types[units[unit2].type].role == 6) &&
          (city3 = unit_stack_sum(unit2,2), city3 == 1)) &&
         ((*(byte *)&civs[civ].treaties[civ2] & 6) != 0)) {
        city2 = city_find_nearest(x2,y2,-1,0xffffffff,-1);
        if ((city2 < 0) || ((int)cities[city2].owner != civ)) {
          if ((autoplay_active == 0) && ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) {
            text_set_label_arg(1,unit_types[units[unit2].type].name);
            if (unit_types[units[unit2].type].role != 6) {
              text_set_label_arg(1,*(i32 *)(label_string_ids + 0x234));
            }
            popup_game_with_sprite(ADDR(0x634dc4, ((u8 *)&g.d_00634dc4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
        }
        else {
          unit3 = civ_get_adjective(civ2);
          text_set_string_arg(0,unit3);
          text_set_label_arg(1,unit_types[units[unit2].type].name);
          unit3 = civ_name_plural(civ);
          text_set_string_arg(2,unit3);
          if (((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) &&
             ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) {
            if (autoplay_active == 0) {
              local_e4 = dlg_game_txt_with_unit(ADDR(0x634d68, ((u8 *)&g.d_00634d68)),unit2);
            }
          }
          else {
            local_e4 = 0;
          }
          unit = iVar9;
          if (local_e4 == 2) goto LAB_00594a80;
          if (local_e4 == 0) {
            if (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) ||
               ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
              if (2 < game.multiplayer) {
                net_send_message(0x71,0xff,x3,y3,civ,0,0,0,0,0);
              }
              mapviews_ensure_visible(x3,y3,civ);
              ui_delay_ticks(10);
              unit_lift_off_map(unit,1);
              map_animate_unit_move(unit,x3,y3,param_2,0xffffffff,0xffffffff);
              unit_relocate(unit,x3,y3,1);
              if (2 < game.multiplayer) {
                net_send_message(0x75,0xff,x3,y3,civ,0,0,0,0,0);
              }
              map_redraw_tile_all_views(x2,y2);
            }
            city4 = -1;
            local_18 = -1;
            if (unit_types[units[unit2].type].role != 6) {
              local_18 = 9999;
            }
            for (city2 = 0; city2 < game.num_cities; city2++) {
              if ((cities[city2].id != 0) && ((int)cities[city2].owner == civ2)) {
                if (unit_types[units[unit2].type].role == 6) {
                  local_3c = (int)cities[city2].size;
                  city3 = city_has_improvement(city2,1);
                  if (city3 != 0) {
                    local_3c += 0x32;
                  }
                  if (local_18 < local_3c) {
                    local_18 = local_3c;
                    city4 = city2;
                  }
                }
                else {
                  local_3c = map_distance_diag(x3,y3,(int)cities[city].x,
                                                (int)cities[city].y);
                  if (local_3c < local_18) {
                    city4 = city2;
                    local_18 = local_3c;
                  }
                }
              }
            }
            if (-1 < city4) {
              city2 = city4;
              unit_relocate(unit2,(int)cities[city4].x,(int)cities[city4].y,1);
              units[unit2].visibility = '\0';
              text_set_string_arg(3,(iptr)&cities[city2].name);
            }
            map_redraw_tile_all_views(x2,y2);
            net_send_message(0x72,0xff,x2,y2,0,0,0,0,0,0);
            if ((autoplay_active == 0) &&
               ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
              if (game.multiplayer < 3) {
                snd_play_effect(0x5d,0,0,0);
                dlg_game_txt_with_unit(ADDR(0x634d80, ((u8 *)&g.d_00634d80)),unit2);
              }
              else if (human_civ == civ2) {
                snd_play_effect(0x5d,0,0,0);
                dlg_game_txt_with_unit(ADDR(0x634d70, ((u8 *)&g.d_00634d70)),unit2);
                if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
                  net_send_text_args(0x60,*(i32 *)
                                           (&net_player_slots +
                                           *(int *)(&net_civ_slots + civ * 4) * 0x54),4,0,unit2
                                     ,0);
                }
              }
              else {
                net_send_text_args(0x5f,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ2 * 4) * 0x54),4,0,unit2
                                   ,0);
                if (human_civ == civ) {
                  snd_play_effect(0x5d,0,0,0);
                  dlg_game_txt_with_unit(ADDR(0x634d78, ((u8 *)&g.d_00634d78)),unit2);
                }
              }
            }
            else if ((autoplay_active == 0) &&
                    (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0 &&
                     ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0)))) {
              if (game.multiplayer < 3) {
                snd_play_effect(0x5d,0,0,0);
                dlg_game_txt_with_unit(ADDR(0x634da0, ((u8 *)&g.d_00634da0)),unit2);
              }
              else if (human_civ == civ) {
                snd_play_effect(0x5d,0,0,0);
                dlg_game_txt_with_unit(ADDR(0x634d88, ((u8 *)&g.d_00634d88)),unit2);
                if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
                  net_send_text_args(0x61,*(i32 *)
                                           (&net_player_slots +
                                           *(int *)(&net_civ_slots + civ2 * 4) * 0x54),4,0,
                                     unit2,0);
                }
              }
              else {
                net_send_text_args(0x61,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ * 4) * 0x54),4,0,unit2,0
                                  );
                if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
                   (human_civ == civ2)) {
                  snd_play_effect(0x5d,0,0,0);
                  dlg_game_txt_with_unit(ADDR(0x634d94, ((u8 *)&g.d_00634d94)),unit2);
                }
              }
            }
            else if ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) {
              if (game.multiplayer < 3) {
                if (autoplay_active == 0) {
                  snd_play_effect(0x5d,0,0,0);
                  dlg_game_txt_with_unit(ADDR(0x634dbc, ((u8 *)&g.d_00634dbc)),unit2);
                }
              }
              else if (human_civ == civ) {
                if (autoplay_active == 0) {
                  snd_play_effect(0x5d,0,0,0);
                  dlg_game_txt_with_unit(ADDR(0x634dac, ((u8 *)&g.d_00634dac)),unit2);
                  if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
                    net_send_text_args(0x60,*(i32 *)
                                             (&net_player_slots +
                                             *(int *)(&net_civ_slots + civ2 * 4) * 0x54),4,0,
                                       unit2,0);
                  }
                }
              }
              else if (autoplay_active == 0) {
                net_send_text_args(0x60,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ * 4) * 0x54),4,0,unit2,0
                                  );
                if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
                   (human_civ == civ2)) {
                  snd_play_effect(0x5d,0,0,0);
                  dlg_game_txt_with_unit(ADDR(0x634db4, ((u8 *)&g.d_00634db4)),unit2);
                }
              }
              city3 = ai_spaceship_race_behind(civ2);
              if (city3 == 0) {
                uVar17 = _rand();
                uVar26 = (int)uVar17 >> 0x1f;
                civ_adjust_attitude(civ2,civ,
                                   ((uVar17 ^ uVar26) - uVar26 & 3 ^ uVar26) - uVar26);
              }
              else if ((*(byte *)&civs[civ2].treaties[civ] & 0x20) == 0) {
                puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
                *puVar1 = *puVar1 | 0x20;
              }
              else {
                puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
                *puVar1 = *puVar1 & 0xffffffd9;
                puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
                *puVar1 = *puVar1 | 0x40;
              }
            }
            goto LAB_00594a80;
          }
        }
      }
      city3 = unit_moves_left(unit);
      if (city3 < (int)(uint)cosmic.road_move_mult) {
        if ((unit_move_by_local_human == '\0') || ((unit_move_flags & 1) == 0)) {
          if (((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) &&
             (city3 = unit_moves_left(unit), unit = iVar9,
             city3 < (int)(cosmic.road_move_mult - 1))) goto LAB_00594a80;
        }
        else {
          uVar18 = unit_moves_left(unit);
          uVar18 = text_set_number_arg(0,uVar18);
          text_set_number_arg_u8(1,CONCAT31((int3)((uint)uVar18 >> 8),cosmic.road_move_mult));
          city3 = dlg_game_txt_with_unit(ADDR(0x634dcc, ((u8 *)&g.d_00634dcc)),unit);
          unit = iVar9;
          if (city3 != 0) goto LAB_00594a80;
        }
      }
      game.moving_unit = (i16)unit;
      units[unit].flags = units[unit].flags & 0xfeff;
      if ((unit_move_flags & 2) == 0) {
        city3 = unit_resolve_attack(unit,param_2,1);
        if (city3 == 0) {
          local_f0 = 1;
          unit = iVar9;
        }
        else {
          local_f0 = 0;
          unit = iVar9;
        }
      }
      else {
        city3 = unit_resolve_attack(unit,param_2,1);
        unit = iVar9;
        if (city3 != 0) {
          local_4c = 1;
          unit3 = (int)game.moving_unit;
          y2 = y3;
          x2 = x3;
          goto LAB_00593d80;
        }
      }
      goto LAB_00594a80;
    }
    if (((local_40 != 0) || (-1 < (int)city)) || (uVar3 != 2)) break;
    unit = iVar9;
    if ((unit_move_by_local_human == '\0') || (city3 = tile_city_owner(x3,y3), -1 < city3))
    goto LAB_00594a80;
    if (game.num_units == local_2c) {
      units[unit].orders = -1;
    }
    local_2c = 0;
    unit7 = -1;
    local_50 = 0;
    for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit))
    {
      if ((unit_types[units[unit].type].domain == '\0') &&
         (((units[unit].orders != 3 || (units[unit].goto_x < 0)) ||
          (units[unit].goto_x == iVar9)))) {
        local_50 = 1;
        city3 = unit_moves_left(unit);
        if ((int)(uint)cosmic.road_move_mult <= city3) {
          unit7 = unit;
          break;
        }
      }
    }
    if (unit7 < 0) {
      unit = iVar9;
      if (((autoplay_active == 0) && (local_50 != 0)) && ((unit_move_flags & 1) != 0)) {
        dlg_game_txt_with_unit(ADDR(0x634dd4, ((u8 *)&g.d_00634dd4)),iVar9);
      }
      goto LAB_00594a80;
    }
    if (((autoplay_active == 0) && ((unit_move_flags & 1) != 0)) &&
       (local_e4 = dlg_game_txt_with_unit(ADDR(0x634de0, ((u8 *)&g.d_00634de0)),iVar9), unit = iVar9, local_e4 == 0))
    goto LAB_00594a80;
    unit = unit7;
    units[unit7].orders = -1;
  }
  if ((-1 < (int)city) && ((int)cities[city].owner != civ)) {
    civ2 = (uptr)cities[city].owner;
    if ((uVar3 != '\0') && ((uVar3 != 1 || (unit_types[units[unit].type].range != '\0')))) {
      if ((char)unit_types[units[unit].type].attack < 'c') {
        unit = iVar9;
        if ((((unit_move_flags & 1) != 0) && ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0))
           && (unit_move_by_local_human != '\0')) {
          snd_play_effect(0x69,0,0,0);
          popup_game_with_sprite(ADDR(0x634dec, ((u8 *)&g.d_00634dec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
      }
      else if ((unit_move_flags & 2) == 0) {
        local_f0 = 1;
        unit = iVar9;
      }
      else {
        city3 = unit_nuclear_attack(civ,x2,y2,1);
        if (city3 == 0) {
          unit_delete_with_cargo(unit,1);
          map_redraw_tile_all_views(x3,y3);
          net_send_message(0x72,0xff,x3,y3,0,0,0,0,0,0);
          unit = iVar9;
        }
        else {
          *(i8 *)&civs[civ].field_50[civ2] = 0;
          unit = iVar9;
        }
      }
      goto LAB_00594a80;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 0xe) != 0) {
      if ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) {
        units[unit].orders = -1;
        unit = iVar9;
        goto LAB_00594a80;
      }
      if ((((unit_move_flags & 1) != 0) && (unit_move_by_local_human != '\0')) &&
         (city3 = diplo_confirm_attack(civ,civ2,0xe), unit = iVar9, city3 != 0))
      goto LAB_00594a80;
    }
  }
  city3 = unit_moves_left(unit);
  unit = iVar9;
  if (city3 == 0) goto LAB_00594a80;
  if (uVar3 == '\0') {
    pbVar19 = (byte *)tile_at(x3,y3);
    pbVar20 = (byte *)tile_at(x2,y2);
    if (((pbVar19[1] & 0x22) == 0) || ((pbVar20[1] & 0x22) == 0)) {
      if ((unit_types[units[unit].type].flags & 0x200) == 0) {
        if (((pbVar19[1] & 0x12) == 0) || ((pbVar20[1] & 0x12) == 0)) {
          if (((*pbVar20 & *pbVar19 & 0x80) != 0) &&
             (city3 = map_dx_wrapped(x3,x2), city3 == 1)) {
            if (y3 == y2 || y3 - y2 < 0) {
              local_114 = ~(y3 - y2) + 1;
            }
            else {
              local_114 = y3 - y2;
            }
            if (local_114 == 1) goto LAB_00592870;
          }
          local_24 = (int)(char)terrain_types[terrain2].move_cost * (uint)cosmic.road_move_mult;
        }
        else {
LAB_00592870:
          local_24 = 1;
        }
      }
      else {
        local_24 = 1;
      }
    }
    else {
      local_24 = 0;
    }
  }
  else {
    local_24 = (uint)cosmic.road_move_mult;
  }
  city3 = unit_moves_left(unit);
  if ((((city3 < (int)local_24) && (uVar3 == '\0')) && (units[unit].moves_used != '\0')) &&
     ((((unit_move_by_local_human != '\0' && ((unit_move_flags & 1) != 0)) ||
       ((human_civ == civ && ((unit_move_flags & 1) != 0)))) ||
      (((unit_move_flags & 2) != 0 && ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0)))))) {
    if (local_24 == 1 || (int)(local_24 - 1) < 0) {
      local_118 = 0;
    }
    else {
      local_118 = _rand();
      local_118 = local_118 % (int)local_24;
    }
    city3 = unit_moves_left(unit);
    if (city3 <= local_118) {
      unit_exhaust_moves(unit);
      local_f0 = 1;
      goto LAB_00594a80;
    }
  }
  if ((unit_move_flags & 2) == 0) {
    local_f0 = 1;
    goto LAB_00594a80;
  }
  unit_type = units[unit].moves_used;
  local_1c = (uint)unit_type;
  units[unit].moves_used += (char)local_24;
  if ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) {
    if (((((unit_types[units[unit].type].role == 6) ||
          ((unit_types[units[unit].type].role == '\0' &&
           ((char)unit_types[units[unit].type].defense * 2 <
            (int)(char)unit_types[units[unit].type].attack)))) && (units[unit].orders == 11)
         ) && (((unit_type != 0 &&
                (uVar5 = unit_types[units[unit].type].role, city3 = unit_moves_left(unit),
                city3 <= (int)(uint)(uVar5 != 6))) &&
               (city3 = unit_max_moves(unit), (int)local_24 < city3)))) &&
       ((city3 = map_distance(x2,y2,(int)units[unit].goto_x,
                                     (int)units[unit].goto_y), city3 == 1 ||
        (((city3 = tile_adjacent_nonallied_civ(x2,y2,civ), city3 != 0 ||
          ((game.human_players & units[unit].visibility) != 0)) &&
         (city3 = tile_adjacent_nonallied_civ(x3,y3,civ), city3 == 0))))))
    goto LAB_00594a80;
    if (((((int)(char)units[unit].last_dir ^ 4U) == param_2) && (local_1c != 0)) &&
       ((unit_types[units[unit].type].domain != 1 &&
        (city3 = unit_stack_sum(unit,2), city3 < 3)))) {
      unit_exhaust_moves(unit);
      goto LAB_00594a80;
    }
    if ((((-1 < unit2) && (civ2 == civ)) && ((int)city < 0)) &&
       ((uVar3 == '\0' && (unit_types[units[unit].type].role != 6)))) {
      city3 = unit_moves_left(unit);
      iVar25 = unit_stack_sum(unit2,2);
      if ((int)((-(uint)(city3 == 0) & 0xfffffffe) + 4) <= iVar25) {
        unit_exhaust_moves(unit);
        goto LAB_00594a80;
      }
    }
  }
  if (((civ == 0) && (local_40 == 0)) &&
     (((city3 = tile_visible_to(x3,y3,human_civ), city3 != 0 &&
       ((((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) == 0 &&
         ((int)units[unit].owner != (human_civ & 0xffU))) &&
        (city3 = city_find_nearest(x3,y3,-1,0xffffffff,-1), -1 < city3)))) &&
      (cities[city3].owner == human_civ)))) {
    city3 = tile_at(x3,y3);
    units[unit].visibility = *(byte *)(city3 + 4) | units[unit].visibility;
  }
  if ((((-1 < (int)city) && (civ2 != civ)) &&
      (city3 = tile_visible_to(x2,y2,human_civ), city3 != 0)) &&
     ((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0 ||
       ((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0)) ||
      (human_civ == civ2)))) {
    unit_set_seen_by(unit,human_civ);
  }
  for (local_34 = 1; (int)local_34 < 8; local_34++) {
    aiStack_a0[local_34] = 0;
    aiStack_80[local_34] = aiStack_a0[local_34];
    if ((((1 << ((byte)local_34 & 0x1f) & (uint)game.civs_alive) != 0) &&
        ((2 < game.multiplayer || (human_civ == local_34)))) &&
       (((autoplay_active != 0 && ((_DAT_00673b08 & 1 << ((byte)local_34 & 0x1f)) != 0)) ||
        ((1 << ((byte)local_34 & 0x1f) & (uint)game.human_players) != 0)))) {
      if (((((1 << ((byte)local_34 & 0x1f) & (uint)units[unit].visibility) == 0) &&
           ((int)units[unit].owner != (local_34 & 0xff))) && (civ != local_34)) &&
         (game.reveal_map == '\0')) {
        for (local_38 = 0; local_38 < 8; local_38++) {
          x5 = map_wrap_x((char)(&dir_dx_table)[local_38] + x2);
          y5 = (char)(&dir_dy_table)[local_38] + y2;
          city3 = map_in_bounds(x5,y5);
          if ((city3 != 0) &&
             (uVar21 = tile_city_or_unit_owner(x5,y5), uVar21 == local_34)) {
            aiStack_a0[local_34] = 1;
            break;
          }
        }
      }
      else {
        aiStack_a0[local_34] = 1;
      }
      if ((human_civ == local_34) && (aiStack_a0[local_34] != 0)) {
        if (((human_civ == civ) || (((*(i8 *)((char *)&game.game_options + 1)) & 0x10) != 0)) ||
           (-1 < (int)city)) {
          aiStack_80[human_civ] = 1;
          SVar11 = GetAsyncKeyState(0x10);
          local_8 = (uint)(byte)((ushort)SVar11 >> 8);
          if (local_8 != 0) {
            aiStack_80[human_civ] = 0;
          }
          if ((((local_24 == 0) || (local_8 != 0)) ||
              ((human_civ == civ && (uVar3 == 1)))) &&
             ((human_civ != civ || (units[unit].orders == 11)))) {
            aiStack_80[human_civ] = 0;
            unit_move_unanimated_state = 1;
            if (human_civ == civ) {
              unit_move_unanimated_state = 2;
              map_cursor_x = (i16)x2;
              map_cursor_y = (i16)y2;
            }
          }
        }
      }
      else if (((human_civ != local_34) && (aiStack_a0[local_34] != 0)) &&
              (((aiStack_80[local_34] = 1, local_24 == 0 ||
                ((civ == local_34 && (unit_types[units[unit].type].domain == 1)))) &&
               ((civ != local_34 || (units[unit].orders == 11)))))) {
        aiStack_80[local_34] = 0;
      }
    }
  }
  if (((((((aiStack_a0[human_civ] != 0) &&
          (mapviews_ensure_visible(x3,y3,civ), local_54 != 0)) && (local_40 == 0)) &&
        ((human_civ != civ && (civ != 0)))) &&
       (unit_types[units[unit].type].domain == '\0')) &&
      ((city3 = tile_landmass(x2,y2),
       *(short *)&civs[civ].continent_military[city3] == 0 &&
       (psVar2 = (short *)(city3 * 2 + ADDR(0x64c832, ((u8 *)&civs + 402)) + civ * 0x594), *psVar2 = *psVar2 + 1,
       (*(byte *)&civs[civ].treaties[civ2] & 6) == 0)))) &&
     ((city3 = city_find_nearest(x3,y3,-1,0xffffffff,-1), 0 < city3 &&
      ((cities[city3].owner == human_civ && (autoplay_active == 0)))))) {
    unit3 = civ_name_plural(civ);
    text_set_string_arg(0,unit3);
    text_set_string_arg(1,(iptr)&cities[city3].name);
    dlg_game_txt_with_unit(ADDR(0x634df4, ((u8 *)&g.d_00634df4)),unit);
  }
  net_send_state_diff(0xff,2,0,0,1);
  if (((game.multiplayer < 3) || (net_host_flag != '\0')) ||
     ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0)) {
    unit_lift_off_map(unit,0);
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,1);
      for (local_34 = 1; (int)local_34 < 8; local_34++) {
        if ((human_civ == local_34) || (aiStack_80[local_34] == 0)) {
          if ((human_civ != local_34) && (aiStack_a0[local_34] != 0)) {
            net_send_message(0x72,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + local_34 * 4) * 0x54)
                               ,x3,y3,0,0,0,0,0,0);
          }
        }
        else {
          net_send_message(0x70,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + local_34 * 4) * 0x54),
                             unit,x3,y3,param_2,-1,1,0,0);
        }
      }
      XD_FlushSendBuffer(5000);
    }
    if (aiStack_80[human_civ] == 0) {
      if (aiStack_a0[human_civ] != 0) {
        map_redraw_tile_all_views(x3,y3);
      }
    }
    else {
      snd_play_effect(99,1,0,0);
      map_animate_unit_move(unit,x3,y3,param_2,0xffffffff,0xffffffff);
    }
    unit_stack_clear_visibility(unit);
    if (local_40 == 0) {
      unit_stack_set_seen_by(unit,civ2);
    }
    local_a4 = tile_has_hut(x2,y2);
    unit_stack_relocate_all(unit,x2,y2,0);
    net_send_state_diff(0xff,2,0,0,1);
  }
  else {
    local_a4 = tile_has_hut(x2,y2);
    nm_stacker_ack_count = -2;
    net_send_message(0x5a,0,civ,civ2,unit,local_40,x2,y2,0,0);
    bVar6 = true;
    XD_FlushSendBuffer(5000);
    if (aiStack_80[human_civ] == 0) {
      if (aiStack_a0[human_civ] != 0) {
        map_redraw_tile_all_views(x3,y3);
      }
    }
    else {
      snd_play_effect(99,1,0,0);
      city3 = tile_at(x3,y3);
      uVar18 = 2;
      unit6 = tile_first_unit(x3,y3);
      iVar25 = unit_stack_sum(unit6,uVar18);
      if (iVar25 == 1) {
        *(byte *)(city3 + 1) = *(byte *)(city3 + 1) & 0xfe;
      }
      else if (1 < iVar25) {
        anim_origin_x = (int)units[unit].x;
        anim_origin_y = (int)units[unit].y;
        iVar25 = unit_stack_sum(unit,5);
        if (iVar25 == 0) {
          if (units[unit].next_in_stack < 0) {
            if (units[unit].prev_in_stack < 0) {
              *(byte *)(city3 + 1) = *(byte *)(city3 + 1) & 0xfe;
            }
            else {
              anim_origin_stack_unit = (iptr)units[unit].prev_in_stack;
            }
          }
          else {
            anim_origin_stack_unit = (iptr)units[unit].next_in_stack;
          }
        }
        else {
          iVar25 = unit_stack_sum(unit,5);
          if (iVar25 < 2) {
            *(byte *)(city3 + 1) = *(byte *)(city3 + 1) & 0xfe;
          }
          else {
            anim_origin_stack_unit = unit_stack_first(unit);
            do {
              if ((anim_origin_stack_unit != unit) &&
                 (unit_types[units[anim_origin_stack_unit].type].domain == 2)) goto LAB_005936b6;
              anim_origin_stack_unit = (iptr)units[anim_origin_stack_unit].next_in_stack;
            } while (-1 < anim_origin_stack_unit);
            *(byte *)(city3 + 1) = *(byte *)(city3 + 1) & 0xfe;
          }
        }
      }
LAB_005936b6:
      unit_move_anim_active = 1;
      map_animate_unit_move(unit,x3,y3,param_2,0xffffffff,0xffffffff);
      unit_move_anim_active = 0;
      uVar18 = 2;
      unit3 = tile_first_unit(x3,y3);
      iVar25 = unit_stack_sum(unit3,uVar18);
      if (iVar25 != 0) {
        if (net_host_flag == '\0') {
          *(byte *)(city3 + 1) = *(byte *)(city3 + 1) | 1;
        }
        else {
          tile_set_improvements(x3,y3,1,1,1);
        }
      }
    }
    for (local_34 = 1; (int)local_34 < 8; local_34++) {
      if ((human_civ == local_34) || (aiStack_80[local_34] == 0)) {
        if (human_civ != local_34) {
          net_send_message(0x72,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + local_34 * 4) * 0x54),
                             x3,y3,0,0,0,0,0,0);
        }
      }
      else {
        net_send_message(0x70,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + local_34 * 4) * 0x54),
                           unit,x3,y3,param_2,-1,1,0,0);
      }
    }
    if (local_30 != 0) {
      city3 = timer_ticks();
      while ((iVar25 = timer_ticks(), iVar25 - city3 < 0xe10 && (nm_stacker_ack_count != 1))) {
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (nm_stacker_ack_count != 1) {
        dbg_log(ADDR(0x634dfc, ((u8 *)&g.d_00634dfc)));
        popup_game_with_sprite(ADDR(0x634e3c, ((u8 *)&g.d_00634e3c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    bVar8 = false;
  }
  if (((uVar3 == '\0') && (local_54 != 0)) && (local_40 == 0)) {
    city3 = tile_landmass(x2,y2);
    psVar2 = (short *)(city3 * 2 + ADDR(0x64c832, ((u8 *)&civs + 402)) + civ * 0x594);
    *psVar2 = *psVar2 + 1;
  }
  if ((-1 < (int)city) && (civ2 != civ)) {
    units[unit].damage = '\0';
    game.moving_unit = (i16)unit;
    city_capture_aftermath(city,civ,0);
    unit = (iptr)game.moving_unit;
  }
  unit3 = unit;
  if (((civ == 0) && (local_40 == 0)) &&
     ((city3 = tile_visible_to(x2,y2,human_civ), city3 != 0 &&
      (((((1 << (civ3 & 0x1f) & (uint)units[unit].visibility) == 0 &&
         ((int)units[unit].owner != (uint)civ3)) &&
        (city3 = city_find_nearest(x2,y2,-1,0xffffffff,-1), -1 < city3)) &&
       (cities[city3].owner == human_civ)))))) {
    city3 = tile_at(x2,y2);
    unit_stack_add_visibility(unit,(uint)*(byte *)(city3 + 4));
  }
  if (((local_54 != 0) && (-1 < (int)city)) &&
     (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0 &&
      (unit_types[units[unit].type].hold != '\0')))) {
    for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit))
    {
      if (units[unit].orders == 3) {
        units[unit].orders = -1;
      }
    }
  }
LAB_00593d80:
  unit = unit3;
  unit3 = unit;
  if ((((game.multiplayer < 3) || (net_host_flag != '\0')) || (!bVar6)) &&
     ((-1 < units[unit].next_in_stack && (unit_types[units[unit].type].attack == '\0')))) {
    unit_move_to_stack_bottom(unit,0);
  }
  unit_reveal_surroundings(unit,1);
  city_window_on_unit_change((FrameWindow *)&city_window,unit,x3,y3);
  if ((((human_civ != civ) && (aiStack_a0[human_civ] != 0)) &&
      (((*(i8 *)((char *)&game.game_options + 1)) & 8) == 0)) &&
     (SVar11 = GetAsyncKeyState(0x10), (char)((ushort)SVar11 >> 8) == '\0')) {
    if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x10) == 0) || (unit_move_unanimated_state != '\0')) {
      ui_delay_ticks(10);
    }
    else {
      ui_delay_ticks(0xf);
    }
  }
  if (unit_types[units[unit].type].domain == 1) {
    city3 = tile_city_owner(x2,y2);
    if ((city3 < 0) && (city3 = tile_airbase_owner(x2,y2), city3 < 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (!bVar6) {
      for (unit5 = unit_stack_first(unit); -1 < unit5;
          unit5 = unit_next_in_stack(unit5)) {
        if ((unit_types[units[unit5].type].flags & 0x80) != 0) {
          bVar6 = true;
          break;
        }
        if (((unit_types[units[unit5].type].flags & 8) != 0) &&
           ((unit_types[units[unit].type].flags & 0x1000) != 0)) {
          bVar6 = true;
          break;
        }
      }
    }
    if ((((bVar6) && (unit_types[units[unit].type].range == 1)) &&
        (city3 = unit_moves_left(unit), city3 != 0)) && (local_4c != 0)) {
      bVar6 = false;
    }
    if (bVar6) {
      units[unit].counter = '\0';
      unit_exhaust_moves(unit);
      unit_move_to_stack_bottom(unit,1);
      map_redraw_tile_all_views(x2,y2);
      net_send_message(0x72,0xff,x2,y2,0,0,0,0,0,0);
      goto LAB_00594255;
    }
    if (((unit_types[units[unit].type].range == '\0') ||
        (city3 = unit_moves_left(unit), city3 != 0)) ||
       (units[unit].counter = units[unit].counter + 1,
       (char)units[unit].counter < (char)unit_types[units[unit].type].range))
    goto LAB_00594255;
    if (unit_move_by_local_human != '\0') {
      if (units[unit].type < 0x1e) {
        snd_play_effect(0x1a,0,0,0);
      }
      else {
        snd_play_effect(0x4e,0,0,0);
      }
    }
    x3 = (int)units[unit].x;
    y3 = (int)units[unit].y;
    unit_type = units[unit].type;
    unit_delete(unit,1);
    map_redraw_area_all_views(x3,y3,0,human_civ,1);
    net_send_message(0x75,0xff,x3,y3,0,0,0,0,0,0);
    if (unit_move_by_local_human != '\0') {
      dlg_game_txt_with_unit_flags(ADDR(0x634e50, ((u8 *)&g.d_00634e50)),(uint)unit_type,(ui_large_screen == 0) - 1 & 8);
    }
  }
  else {
LAB_00594255:
    if ((((unit_types[units[unit].type].flags & 0x20) != 0) && (unit_move_by_local_human != '\0')) &&
       ((city3 = unit_moves_left(unit), city3 == 0 &&
        (city3 = civ_has_wonder(civ,3), city3 == 0)))) {
      local_c4 = (uint)cosmic.trireme_loss_chance;
      city3 = civ_has_advance(civ,0x4b);
      if ((city3 != 0) && (local_c4 = local_c4 * 2, local_c4 < 3)) {
        local_c4 = 2;
      }
      city3 = civ_has_advance(civ,0x39);
      if (city3 != 0) {
        local_c4 = local_c4 << 1;
      }
      if ((int)(local_c4 - 1) < 1) {
        local_120 = 0;
      }
      else {
        local_120 = _rand();
        local_120 = local_120 % (int)local_c4;
      }
      if (local_120 == 0) {
        bVar6 = false;
        for (local_38 = 0; local_38 < 9; local_38++) {
          x = map_wrap_x((char)(&dir_dx_table)[local_38] + x2);
          y4 = (char)(&dir_dy_table)[local_38] + y2;
          city3 = map_in_bounds(x,y4);
          if ((city3 != 0) && (city3 = tile_is_ocean(x,y4), city3 == 0)) {
            bVar6 = true;
            break;
          }
        }
        if (!bVar6) {
          if (unit_move_by_local_human != '\0') {
            snd_play_effect(9,1,0,0);
          }
          x3 = (int)units[unit].x;
          y3 = (int)units[unit].y;
          unit_type = units[unit].type;
          unit_delete_with_cargo(unit,1);
          map_redraw_area_all_views(x3,y3,0,human_civ,1);
          net_send_message(0x75,0xff,x3,y3,0,0,0,0,0,0);
          if (unit_move_by_local_human != '\0') {
            dlg_game_txt_with_unit_flags(ADDR(0x634e58, ((u8 *)&g.d_00634e58)),(uint)unit_type,(ui_large_screen == 0) - 1 & 8);
          }
          goto LAB_00594a80;
        }
      }
    }
    if ((local_a4 != 0) && (unit_types[units[unit].type].domain == '\0')) {
      unit_enter_hut(unit);
    }
    if ((((uVar3 == 2) && (unit_types[units[unit].type].hold != '\0')) &&
        ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) &&
       ((city3 = unit_moves_left(unit), city3 == 0 &&
        (city3 = unit_stack_count_role(unit,0), city3 != 0)))) {
      bVar6 = false;
      for (local_38 = 0; local_38 < 8; local_38++) {
        x = map_wrap_x((char)(&dir_dx_table)[local_38] + x2);
        y4 = (char)(&dir_dy_table)[local_38] + y2;
        iVar19 = map_in_bounds(x,y4);
        if (((iVar19 != 0) && (iVar22 = tile_is_ocean(x,y4), iVar22 == 0)) &&
           (city3 = tile_landmass(x,y4),
           *(char *)&civs[civ].continent_policy[city3] != 4)) {
          for (local_5c = 0; local_5c < 8; local_5c++) {
            x4 = map_wrap_x((char)(&dir_dx_table)[local_5c] + x);
            city3 = (char)(&dir_dy_table)[local_5c] + y4;
            iVar25 = map_in_bounds(x4,city3);
            if ((iVar25 != 0) && (city3 = tile_visible_to(x4,city3,civ), city3 == 0)) {
              bVar6 = true;
              break;
            }
          }
          if (bVar6) break;
        }
      }
      if (bVar6) {
        for (unit = unit_stack_first(unit); -1 < unit;
            unit = unit_next_in_stack(unit)) {
          if (((unit_types[units[unit].type].role == '\0') &&
              (unit_types[units[unit].type].attack == '\0')) &&
             (units[unit].moves_used == '\0')) {
            units[unit].orders = -1;
          }
        }
      }
    }
    if (bVar7) {
      unit_set_sleep(unit3);
      unit_exhaust_moves(unit3);
      for (unit4 = unit_stack_first(unit3); -1 < unit4;
          unit4 = unit_next_in_stack(unit4)) {
        if (((unit_types[units[unit4].type].domain == 2) &&
            (unit_type = units[unit4].moves_used, city3 = unit_max_moves(unit4),
            (int)(uint)unit_type <= city3)) &&
           (unit_gather_cargo(unit4,0,0), units[unit3].goto_x == unit4)) {
          units[unit4].orders = -1;
          game.active_unit = (i16)unit4;
          break;
        }
      }
      map_redraw_tile_all_views(x2,y2);
      net_send_state_diff(0xff,2,0,0,0);
      net_send_message(0x72,0xff,x2,y2,0,0,0,0,0,0);
    }
    if (unit_move_by_local_human != '\0') {
      if ((units[unit3].orders == 11) || (((int)(short)units[unit3].flags & 0x8000U) != 0)) {
        units[unit3].field_0e++;
        if (((int)(char)units[unit3].last_dir ^ 4U) == param_2) {
          units[unit3].field_0e += 15;
        }
        if ('/' < (char)units[unit3].field_0e) {
          city3 = dlg_game_txt_with_unit(ADDR(0x634e60, ((u8 *)&g.d_00634e60)),unit3);
          if (city3 != 0) {
            units[unit3].orders = -1;
            units[unit3].flags = units[unit3].flags & 0x7fff;
          }
          units[unit3].field_0e = '\0';
        }
      }
      else {
        units[unit3].field_0e = '\0';
      }
    }
    units[unit3].last_dir = (u8)param_2;
    local_f0 = 1;
    unit = unit3;
  }
LAB_00594a80:
  if (bVar8) {
    net_unlock_map(civ,local_30);
  }
LAB_00594aaa:
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x75,0xff,x3,y3,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  if (game.num_units != local_2c) {
    unit_move_in_progress = 0;
    return 0;
  }
  if (local_f0 == 0) {
    units[unit].orders = -1;
    if (((int)(short)units[unit].flags & 0x8000U) != 0) {
      unit_exhaust_moves(unit);
    }
    if (unit_types[units[unit].type].role == 4) {
      units[unit].counter = (byte)game.turn & 7;
    }
    if ((1 << (civ3 & 0x1f) & (uint)game.human_players) == 0) {
      if ((units[unit].flags & 0x100) != 0) {
        units[unit].orders = 2;
      }
      units[unit].field_0e++;
      if (19 < (char)units[unit].field_0e) {
        units[unit].field_0e = '\0';
        unit_exhaust_moves(unit);
      }
    }
  }
  else {
    units[unit].flags = units[unit].flags & 0xfeff;
  }
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
  }
  unit_move_in_progress = 0;
  return local_f0;
}
#undef autoplay_active
#undef game_loop_active
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef mp_simultaneous_moves
#undef net_host_flag
#undef nm_stacker_ack_count
#undef saved_human_players
#undef ui_large_screen
#undef unit_blink_active
#undef unit_move_anim_active
#undef unit_move_flags
#undef _DAT_00673b08
#undef local_120
#undef local_118
#undef local_114
#undef unit7
#undef y2
#undef city4
#undef local_f0
#undef x2
#undef local_e4
#undef unit5
#undef y3
#undef local_c4
#undef x3
#undef unit4
#undef local_a4
#undef aiStack_a0
#undef aiStack_80
#undef y5
#undef local_5c
#undef terrain2
#undef local_54
#undef local_50
#undef local_4c
#undef y4
#undef civ2
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef unit2
#undef local_24
#undef city2
#undef local_1c
#undef local_18
#undef local_14
#undef x5
#undef local_c
#undef local_8

/* 005aef20 auto */
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_editor_load_rules(void)

{
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    _Count = 0x28;
    _Source = (char *)label_string(unit_types[unit_type].name);
    _strncpy(&editor_item_names + unit_type * 0x28,_Source,_Count);
    (&editor_item_name_ends)[unit_type * 0x28] = 0;
    *(int *)(&editor_items + unit_type * 0x58) = (int)unit_types[unit_type].prerequisite;
    *(int *)(&editor_item_field1 + unit_type * 0x58) = (int)unit_types[unit_type].obsolete_by;
    *(int *)(&editor_item_field2 + unit_type * 0x58) = (int)(char)unit_types[unit_type].role;
    *(int *)(&editor_item_field3 + unit_type * 0x58) = (int)(char)unit_types[unit_type].domain;
    *(int *)(&editor_item_field4 + unit_type * 0x58) = (int)(char)unit_types[unit_type].cost;
    *(int *)(&editor_item_field5 + unit_type * 0x58) = (int)(char)unit_types[unit_type].hold;
    *(int *)(&editor_item_field6 + unit_type * 0x58) =
         (int)(char)unit_types[unit_type].move / (int)(uint)cosmic.road_move_mult;
    *(int *)(&editor_item_field7 + unit_type * 0x58) = (int)(char)unit_types[unit_type].range;
    *(int *)(&editor_item_field8 + unit_type * 0x58) = (int)(char)unit_types[unit_type].attack;
    *(int *)(&editor_item_field9 + unit_type * 0x58) = (int)(char)unit_types[unit_type].defense;
    *(int *)(&editor_item_field10 + unit_type * 0x58) = (int)(char)unit_types[unit_type].hit_points / 10;
    *(int *)(&editor_item_field11 + unit_type * 0x58) = (int)(char)unit_types[unit_type].firepower;
    *(u32 *)(&editor_item_flags + unit_type * 0x58) = unit_types[unit_type].flags;
  }
  return;
}
#undef unit_type

/* 005af140 auto */
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_editor_store_rules(void)

{
  char *_Dest;
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    _Count = 0xf;
    _Source = &editor_item_names + unit_type * 0x28;
    _Dest = (char *)label_string(unit_types[unit_type].name);
    _strncpy(_Dest,_Source,_Count);
    unit_types[unit_type].prerequisite = (&editor_items)[unit_type * 0x58];
    unit_types[unit_type].obsolete_by = (&editor_item_field1)[unit_type * 0x58];
    unit_types[unit_type].role = (&editor_item_field2)[unit_type * 0x58];
    unit_types[unit_type].domain = (&editor_item_field3)[unit_type * 0x58];
    unit_types[unit_type].cost = (&editor_item_field4)[unit_type * 0x58];
    unit_types[unit_type].hold = (&editor_item_field5)[unit_type * 0x58];
    unit_types[unit_type].move =
         (char)*(i32 *)(&editor_item_field6 + unit_type * 0x58) * cosmic.road_move_mult;
    unit_types[unit_type].range = (&editor_item_field7)[unit_type * 0x58];
    unit_types[unit_type].attack = (&editor_item_field8)[unit_type * 0x58];
    unit_types[unit_type].defense = (&editor_item_field9)[unit_type * 0x58];
    unit_types[unit_type].hit_points = (char)*(i32 *)(&editor_item_field10 + unit_type * 0x58) * '\n';
    unit_types[unit_type].firepower = (&editor_item_field11)[unit_type * 0x58];
    unit_types[unit_type].flags = *(u32 *)(&editor_item_flags + unit_type * 0x58);
  }
  return;
}
#undef unit_type

/* 005af343 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl unit_editor_load_controls(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_14 = 1; local_14 < 0xd; local_14++) {
    if (*(int *)(&unit_editor_ctrl_kinds + local_14 * 8) == 9) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&unit_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd));
      _sprintf(local_10,&unit_editor_int_fmt,
               *(i32 *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58));
      ctrl_set_text
                ((ControlTextView *)
                 (*(int *)(&unit_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
    }
    else if (*(int *)(&unit_editor_ctrl_kinds + local_14 * 8) == 0xc) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&unit_editor_ctrl_slots + local_14 * 8) * 0x38));
      local_8 = *(iptr *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58);
      if ((local_14 == 1) || (local_14 == 2)) {
        local_8 += 2;
      }
      combo_set_cur_sel
                ((ComboBoxSetSelView *)
                 (active_editor_wnd + 0x2fc + *(int *)(&unit_editor_ctrl_slots + local_14 * 8) * 0x38),local_8);
    }
  }
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 005af4ae auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl unit_editor_store_controls(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  for (local_18 = 1; local_18 < 0xd; local_18++) {
    if (*(int *)(&unit_editor_ctrl_kinds + local_18 * 8) == 9) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&unit_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd));
      iVar1 -= 0xca;
      ctrl_get_text
                ((ControlTextView *)
                 (*(int *)(&unit_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
      local_8 = _atoi(local_10);
      uVar2 = int_clamp(local_8,*(i32 *)(&unit_editor_field_min_table + iVar1 * 4),
                                 *(i32 *)(&unit_editor_field_max_table + iVar1 * 4));
      *(i32 *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = uVar2;
      if (*(int *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) != local_8) {
        local_14++;
      }
    }
    else if (*(int *)(&unit_editor_ctrl_kinds + local_18 * 8) == 0xc) {
      local_8 = combo_get_cur_sel
                          ((ComboBoxGetSelView *)
                           (active_editor_wnd + 0x2fc + *(int *)(&unit_editor_ctrl_slots + local_18 * 8) * 0x38));
      if ((local_18 == 1) || (local_18 == 2)) {
        local_8 -= 2;
      }
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&unit_editor_ctrl_slots + local_18 * 8) * 0x38));
      *(int *)(&editor_ctrl_values + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = local_8;
    }
  }
  return local_14;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 005af682 auto */
void __cdecl unit_editor_redraw(void)

{
  unit_editor_paint((C_004083b0_430 *)active_editor_wnd);
  return;
}

/* 005af69d auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_10 (*(size_t *)(frame_ + FRAME_OFF(0)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
i32 __cdecl unit_editor_write_units(FILE *param_1)

{
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    text_clear();
    text_append_string_id(unit_types[unit_type].name);
    FUN_005f22e0(&text_buffer,&units_txt_name_sep);
    pcVar1 = (char *)label_string(unit_types[unit_type].name);
    sVar2 = _strlen(pcVar1);
    if (sVar2 < 0xd) {
      pcVar1 = (char *)label_string(unit_types[unit_type].name);
      local_10 = _strlen(pcVar1);
    }
    else {
      local_10 = 0xd;
    }
    text_append_spaces(0xd - local_10);
    text_append_advance_abbrev((int)unit_types[unit_type].obsolete_by,1);
    text_append_int_2d((int)(char)unit_types[unit_type].domain);
    FUN_005f22e0(&text_buffer,&units_txt_domain_sep);
    text_append_int_2d((int)(char)unit_types[unit_type].move / (int)(uint)cosmic.road_move_mult);
    FUN_005f22e0(&text_buffer,&units_txt_move_suffix);
    text_append_int((int)(char)unit_types[unit_type].range);
    FUN_005f22e0(&text_buffer,&units_txt_range_sep);
    text_append_int_2d((int)(char)unit_types[unit_type].attack);
    FUN_005f22e0(&text_buffer,&units_txt_attack_suffix);
    text_append_int((int)(char)unit_types[unit_type].defense);
    FUN_005f22e0(&text_buffer,&units_txt_defense_suffix);
    if ((char)unit_types[unit_type].defense < '\n') {
      text_append_space();
    }
    text_append_int_2d((int)(char)unit_types[unit_type].hit_points / 10);
    FUN_005f22e0(&text_buffer,&units_txt_hp_suffix);
    text_append_int((int)(char)unit_types[unit_type].firepower);
    FUN_005f22e0(&text_buffer,&units_txt_firepower_suffix);
    text_append_int_2d((int)(char)unit_types[unit_type].cost);
    FUN_005f22e0(&text_buffer,&units_txt_cost_sep);
    text_append_int((int)(char)unit_types[unit_type].hold);
    FUN_005f22e0(&text_buffer,&units_txt_hold_sep);
    text_append_int_2d((int)(char)unit_types[unit_type].role);
    FUN_005f22e0(&text_buffer,&units_txt_role_sep);
    text_append_advance_abbrev((int)unit_types[unit_type].prerequisite,1);
    text_append_space();
    for (local_8 = 0xe; -1 < local_8; local_8--) {
      FUN_005f22e0(&text_buffer,
                   &units_txt_flag_digits +
                   (((unit_types[unit_type].flags & 1 << ((byte)local_8 & 0x1f)) != 0) - 1 & 4));
    }
    FUN_005f22e0(&text_buffer,&units_txt_line_end);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_10
#undef unit_type
#undef local_8

/* 005af9e3 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define local_50 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_4c (*(char (*)[32])(frame_ + FRAME_OFF(4)))
#define local_2c (*(char (*)[32])(frame_ + FRAME_OFF(36)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(72)))
void __cdecl unit_editor_on_ok(void)

{
  iptr iVar1;
  HWND hWnd;
  char *pcVar1;
  iptr iVar2;
  i32 uVar2;
  int iVar3;
  char *pcVar4;
  i8 *puVar5;
  UINT UVar6;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = unit_editor_store_controls();
  if (iVar1 == 0) {
    local_8 = 0;
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      pcVar4 = &editor_item_names + unit_type * 0x28;
      pcVar1 = (char *)label_string(unit_types[unit_type].name);
      iVar2 = _strcmp(pcVar1,pcVar4);
      if (iVar2 != 0) {
        puVar5 = &editor_item_names + unit_type * 0x28;
        uVar2 = label_string(unit_types[unit_type].name);
        iVar3 = events_rename_unit_refs(uVar2,(iptr)puVar5);
        local_8 += iVar3;
      }
    }
    if (local_8 != 0) {
      iVar3 = events_write_file();
      if (iVar3 == 0) {
        _sprintf(local_2c,s_Error_updating_EVENTS__s_00635f4c,&lang_file_ext);
        UVar6 = 0x10;
        pcVar1 = s_File_I_O_Error_00635f68;
        pcVar4 = local_2c;
        iVar3 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
        MessageBoxA(*(HWND *)(iVar3 + 4),pcVar4,pcVar1,UVar6);
      }
    }
    unit_editor_store_rules();
    rules_edit_set_section(ADDR(0x635f78, ((u8 *)&g.d_00635f78)),ADDR(0x4036de, unit_editor_write_units));
    iVar3 = rules_write_sections();
    if (iVar3 == 0) {
      _sprintf(local_4c,s_Error_updating_RULES__s_00635f80,&lang_file_ext);
      UVar6 = 0x10;
      pcVar1 = s_File_I_O_Error_00635f98;
      pcVar4 = local_4c;
      iVar3 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar3 + 4),pcVar4,pcVar1,UVar6);
    }
    editor_running = 0;
    wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
    menu_update_states();
  }
  else {
    unit_editor_load_controls();
    unit_editor_redraw();
    if (active_editor_wnd == 0) {
      local_50 = 0;
    }
    else {
      local_50 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_50);
    popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x635f44, ((u8 *)&g.d_00635f44)));
    dlg_set_parent_window(0);
    hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
    SetFocus(hWnd);
  }
  return;
}
#undef editor_running
#undef local_50
#undef local_4c
#undef local_2c
#undef unit_type
#undef local_8

/* 005afbca auto */
#define local_12c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_128 (*(char (*)[14])(frame_ + FRAME_OFF(8)))
#define local_11a (*(i8 *)(frame_ + FRAME_OFF(22)))
#define local_114 (*(char (*)[260])(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(292)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(296)))
void __cdecl unit_editor_on_rename(void)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(304)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = *(int *)(active_editor_wnd + 0x2ec);
  _strncpy(local_128,&editor_item_names + local_10 * 0x28,0xf);
  local_11a = 0;
  do {
    if (active_editor_wnd == 0) {
      local_12c = 0;
    }
    else {
      local_12c = active_editor_wnd + 0x48;
    }
    dlg_push_parent_window(local_12c);
    local_8 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x635fa8, ((u8 *)&g.d_00635fa8)),0xe,(iptr)local_128,(iptr)local_114);
    dlg_pop_parent_window();
    if (local_8 == -1) break;
    sVar1 = _strlen(local_114);
  } while (sVar1 == 0);
  if (-1 < local_8) {
    FUN_005f22d0(&editor_item_names + local_10 * 0x28,local_114);
    local_c = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x2fc));
    for (local_10 = 0; local_10 < 0x3e; local_10++) {
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x2fc),(iptr)(&editor_item_names + local_10 * 0x28));
    }
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),local_c);
    unit_editor_redraw();
  }
  return;
}
#undef local_12c
#undef local_128
#undef local_11a
#undef local_114
#undef local_10
#undef local_c
#undef local_8

/* 005afd3b auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_editor_on_help(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x635fbc, ((u8 *)&g.d_00635fbc)),ADDR(0x635fb4, ((u8 *)&g.d_00635fb4)));
  dlg_set_parent_window(0);
  return;
}
#undef local_8

/* 005afd9a auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl unit_editor_on_cancel(void)

{
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 005afdc2 auto */
void __cdecl unit_editor_edit_sprite(void)

{
  i32 uVar1;
  i32 uVar2;
  i8 *puVar3;
  
  puVar3 = ((void *)ADDR(0x0040177b, sprite_sheet_save_units));
  uVar2 = 0xb;
  uVar1 = label_string(*(i32 *)(label_string_ids + 0x7d8));
  sprite_editor_run((iptr)(&unit_sprites + *(int *)(active_editor_wnd + 0x2ec) * 0x3c),uVar1,uVar2,
                     (iptr)puVar3);
  unit_editor_redraw();
  return;
}

/* 005afe15 auto */
#define local_84 (*(char (*)[128])(frame_ + FRAME_OFF(4)))
void __cdecl unit_editor_edit_sound(void)

{
  i32 uVar1;
  i8 *puVar2;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_editor_store_controls();
  puVar2 = &editor_item_names + *(int *)(active_editor_wnd + 0x2ec) * 0x28;
  uVar1 = label_string(*(i32 *)(label_string_ids + 0x7dc));
  _sprintf(local_84,s__s____s_00635fc4,uVar1,puVar2);
  unit_sound_editor_run((iptr)local_84,*(i32 *)(active_editor_wnd + 0x2ec));
  return;
}
#undef local_84

/* 005afe84 auto */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __cdecl unit_editor_set_flag_check(i32 param_1,int param_2)

{
  dlg_check_set(param_1,(uint)(param_2 != 0));
  return;
}

/* 005afea8 auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
void __cdecl unit_editor_edit_flags(void)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(active_editor_wnd + 0x2ec);
  dlg_checks_clear();
  unit_editor_set_flag_check(0,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 1);
  unit_editor_set_flag_check(1,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 2);
  unit_editor_set_flag_check(2,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 4);
  unit_editor_set_flag_check(3,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 8);
  unit_editor_set_flag_check(4,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x10);
  unit_editor_set_flag_check(5,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x20);
  unit_editor_set_flag_check(6,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x40);
  unit_editor_set_flag_check(7,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x80);
  unit_editor_set_flag_check(8,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x100);
  unit_editor_set_flag_check(9,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x200);
  unit_editor_set_flag_check(10,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x400);
  unit_editor_set_flag_check(0xb,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x800);
  unit_editor_set_flag_check(0xc,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x1000);
  unit_editor_set_flag_check(0xd,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x2000);
  unit_editor_set_flag_check(0xe,*(uint *)(&editor_item_flags + iVar1 * 0x58) & 0x4000);
  text_set_string_arg(0,(iptr)(&editor_item_names + iVar1 * 0x28));
  if (active_editor_wnd == 0) {
    local_10 = 0;
  }
  else {
    local_10 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_10);
  iVar2 = popup_game_flags(ADDR(0x635fcc, ((u8 *)&g.d_00635fcc)),1);
  if (iVar2 == 0) {
    iVar2 = dlg_check_get(0);
    local_8 = (uint)(iVar2 != 0);
    iVar2 = dlg_check_get(1);
    if (iVar2 != 0) {
      local_8 = local_8 | 2;
    }
    iVar2 = dlg_check_get(2);
    if (iVar2 != 0) {
      local_8 = local_8 | 4;
    }
    iVar2 = dlg_check_get(3);
    if (iVar2 != 0) {
      local_8 = local_8 | 8;
    }
    iVar2 = dlg_check_get(4);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x10;
    }
    iVar2 = dlg_check_get(5);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x20;
    }
    iVar2 = dlg_check_get(6);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x40;
    }
    iVar2 = dlg_check_get(7);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x80;
    }
    iVar2 = dlg_check_get(8);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x100;
    }
    iVar2 = dlg_check_get(9);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x200;
    }
    iVar2 = dlg_check_get(10);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x400;
    }
    iVar2 = dlg_check_get(0xb);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x800;
    }
    iVar2 = dlg_check_get(0xc);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x1000;
    }
    iVar2 = dlg_check_get(0xd);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x2000;
    }
    iVar2 = dlg_check_get(0xe);
    if (iVar2 != 0) {
      local_8 = local_8 | 0x4000;
    }
    *(uint *)(&editor_item_flags + iVar1 * 0x58) = local_8;
  }
  dlg_set_parent_window(0);
  return;
}
#undef local_10
#undef local_8

/* 005b02a5 auto */
void __cdecl unit_editor_update_domain_ctrls(void)

{
  int iVar1;
  
  iVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x3dc));
  if (iVar1 == 0) {
    control_hide((Control *)(active_editor_wnd + 0x494));
    control_hide((Control *)(active_editor_wnd + 0x524));
  }
  else if (iVar1 == 1) {
    control_hide((Control *)(active_editor_wnd + 0x494));
    ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x524));
  }
  else if (iVar1 == 2) {
    ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x494));
    control_hide((Control *)(active_editor_wnd + 0x524));
  }
  return;
}

/* 005b0373 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_editor_on_combo(int param_1)

{
  int iVar1;
  HWND hWnd;
  i32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0xc9) {
    iVar1 = unit_editor_store_controls();
    if (iVar1 == 0) {
      uVar2 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
      *(i32 *)(active_editor_wnd + 0x2ec) = uVar2;
      unit_editor_load_controls();
      unit_editor_update_domain_ctrls();
      unit_editor_redraw();
    }
    else {
      combo_set_cur_sel
                ((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),*(iptr *)(active_editor_wnd + 0x2ec));
      unit_editor_load_controls();
      unit_editor_redraw();
      if (active_editor_wnd == 0) {
        local_8 = 0;
      }
      else {
        local_8 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_8);
      popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x635fd8, ((u8 *)&g.d_00635fd8)));
      dlg_set_parent_window(0);
      hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
      SetFocus(hWnd);
    }
  }
  else if (param_1 == 0xcd) {
    unit_editor_update_domain_ctrls();
  }
  return;
}
#undef local_8

/* 005b0473 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define local_2c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(12)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(28)))
void __thiscall unit_editor_create_combo(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(&unit_editor_ctrl_positions + param_1 * 8) + this->client_x;
  iVar2 = *(int *)(&unit_editor_ctrl_pos_ys + param_1 * 8) + this->client_y;
  if (param_1 == 0) {
    rect_set_xywh((iptr)local_14,iVar1 - 0xf,iVar2,0x82,this->field_2e8 << 3);
  }
  else {
    rect_set_xywh((iptr)local_14,iVar1 - 0x1e,iVar2,0xa0,this->field_2e8 << 3);
  }
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_2c = (u8 *)0x0;
  }
  else {
    local_2c = this->pad_48;
  }
  combo_create
            ((Control *)(this->pad_2d4 + param_1 * 0x38 + 0x28),(iptr)local_2c,iVar1,
             (iptr)local_14);
  combo_set_font((ComboBoxFontView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  combo_set_callback((ComboBoxCallbackSetView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x40326f, unit_editor_on_combo));
  switch(param_1) {
  case 0:
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      iVar3 = label_string(unit_types[unit_type].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    }
    break;
  case 1:
  case 2:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c4));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    for (advance = 0; advance < 100; advance++) {
      iVar3 = label_string(advances[advance].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    }
    break;
  case 3:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x794));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x798));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7e0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7e4));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7e8));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7ec));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7f0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7f4));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    break;
  case 4:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7f8));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7fc));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x800));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
  }
  return;
}
#undef editor_next_ctrl_id
#undef local_2c
#undef advance
#undef unit_type
#undef local_14

/* 005b08e8 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define unit_editor_edit_x_table (*(i32 *)((u8 *)&g.d_00635e20))
#define unit_editor_edit_y_table (*(i32 *)((u8 *)&g.d_00635e24))
#define local_24 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall unit_editor_create_edit(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,(&unit_editor_edit_x_table)[param_1 * 2] + this->client_x,
                     (&unit_editor_edit_y_table)[param_1 * 2] + this->client_y,0x30,this->field_2e8 + 6);
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_24 = (u8 *)0x0;
  }
  else {
    local_24 = this->pad_48;
  }
  edit_create
            ((EditControl *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),(iptr)local_24,iVar1,
             (iptr)local_14,ADDR(0x635fe0, ((u8 *)&g.d_00635fe0)));
  edit_set_max_len((EditMaxLenView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),3);
  edit_set_callback((EditCallbackSetView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),ADDR(0x401019, editor_numeric_edit_filter));
  return;
}
#undef editor_next_ctrl_id
#undef unit_editor_edit_x_table
#undef unit_editor_edit_y_table
#undef local_24
#undef local_14

/* 005b09dc auto */
#define editor_bg_surface (*(int *)((u8 *)&g.d_0062e018))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define unit_editor_edit_x_table (*(int *)((u8 *)&g.d_00635e20))
#define unit_editor_edit_y_table (*(int *)((u8 *)&g.d_00635e24))
#define _DAT_00635e1c (*(i32 *)((u8 *)&g.d_00635e1c))
#define _DAT_00635e34 (*(i32 *)((u8 *)&g.d_00635e34))
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(Sprite * *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall unit_editor_paint(C_004083b0_430 *this)

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
  local_18 = (Sprite *)(&unit_sprites + this->field_2ec * 0x3c);
  bVar1 = sprite_get_key_color(local_18);
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x40,0x40,(uint)bVar1);
  sprite_draw_keyed(local_18,(iptr)local_28,(iptr)this,0,local_8,local_c + 8);
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x40,0x40,6);
  gfx_draw_tiled_frame((iptr)this,this->client_x + 0x79,this->client_y + 0x4f,0x14d,0x47,6);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  local_10 = this->client_x + (int)this->field_2d8 / 2 + 5;
  local_14 = unit_editor_prereq_y + this->client_y + this->field_2e8 * -2 - 2;
  text_clear();
  text_append_label(0x1e9);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_prereq_x + this->client_x + 0x32;
  local_14 = ((unit_editor_prereq_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x7e);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_obsolete_x + this->client_x + 0x32;
  local_14 = ((unit_editor_obsolete_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1de);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_role_x + this->client_x + 0x32;
  local_14 = ((unit_editor_role_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1df);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_domain_x + this->client_x + 0x32;
  local_14 = ((this->client_y + _DAT_00635e1c) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e0);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_edit_x_table + this->client_x + 0x18;
  local_14 = ((unit_editor_edit_y_table + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e1);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_holds_x + this->client_x + 0x18;
  local_14 = ((unit_editor_holds_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e2);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_move_x + this->client_x + 0x18;
  local_14 = ((this->client_y + _DAT_00635e34) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e3);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_edit3_x + this->client_x + 0x18;
  local_14 = ((unit_editor_edit3_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e4);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_edit4_x + this->client_x + 0x18;
  local_14 = ((unit_editor_edit4_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e5);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_edit5_x + this->client_x + 0x18;
  local_14 = ((unit_editor_edit5_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e6);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_edit6_x + this->client_x + 0x18;
  local_14 = ((unit_editor_edit6_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e7);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = unit_editor_edit7_x + this->client_x + 0x18;
  local_14 = ((unit_editor_edit7_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e8);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef editor_bg_surface
#undef editor_running
#undef unit_editor_edit_x_table
#undef unit_editor_edit_y_table
#undef _DAT_00635e1c
#undef _DAT_00635e34
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005b1037 auto */
#define editor_bg_surface (*(DibSurface * *)((u8 *)&g.d_0062e018))
#define editor_next_ctrl_id (*(i32 *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define _DAT_00635ef0 (*(i32 *)((u8 *)&g.d_00635ef0))
#define _DAT_00635f00 (*(i32 *)((u8 *)&g.d_00635f00))
#define local_48c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_488 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_480 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_478 (*(u8 * *)(frame_ + FRAME_OFF(24)))
#define local_474 (*(u8 * *)(frame_ + FRAME_OFF(28)))
#define local_468 (*(DibSurface * *)(frame_ + FRAME_OFF(40)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_454 (*(i8 (*)[16])(frame_ + FRAME_OFF(60)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(76)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1152)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1156)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1160)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall unit_editor_window_run(C_004083b0_430 *this)

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
  surface_load_gif_file(editor_bg_surface,ADDR(0x635fe4, ((u8 *)&g.d_00635fe4)),10,0xc0,(iptr)&local_444);
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
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x72c));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  for (local_460 = 0; local_460 < 0xd; local_460++) {
    if (*(int *)(&unit_editor_ctrl_kinds + local_460 * 8) == 9) {
      unit_editor_create_edit(this,*(i32 *)(&unit_editor_ctrl_slots + local_460 * 8));
    }
    else if (*(int *)(&unit_editor_ctrl_kinds + local_460 * 8) == 0xc) {
      unit_editor_create_combo(this,*(i32 *)(&unit_editor_ctrl_slots + local_460 * 8));
    }
  }
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_width - 10;
  this->field_2e0 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
  iVar4 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_474 = (u8 *)0x0;
  }
  else {
    local_474 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this[1].field_2a4,(iptr)local_474,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x401767, unit_editor_on_ok));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xa8));
  button_create
            ((Control *)&this[1].field_358,(iptr)local_478,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_358,ADDR(0x403210, unit_editor_on_rename));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)&this[1].field_2e0,(iptr)local_47c,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x403788, unit_editor_on_help));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this[1].field_31c,(iptr)local_480,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x403c88, unit_editor_on_cancel));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  iVar3 = sprite_width
                    ((Sprite *)(&terrain_base_sprites + this->field_2ec * 0x3c));
  this->field_2e0 = iVar3 + 0xd;
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar4 = this->client_x + 0x19;
  iVar3 = sprite_height
                    ((Sprite *)(&terrain_base_sprites + this->field_2ec * 0x3c));
  iVar3 = iVar3 * 2 + this->client_y + 0x28;
  rect_set_xywh((iptr)local_454,iVar4,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x7cc));
  button_create
            ((Control *)(this[1].pad_364 + 0x30),(iptr)local_484,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_364 + 0x30),ADDR(0x402202, unit_editor_edit_sprite));
  iVar3 = iVar3 + this->field_2e4 + 2;
  rect_set_xywh((iptr)local_454,iVar4,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_488 = (u8 *)0x0;
  }
  else {
    local_488 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 2000));
  button_create
            ((Control *)(this[2].pad_48 + 0x48),(iptr)local_488,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[2].pad_48 + 0x48),ADDR(0x4029b4, unit_editor_edit_sound));
  rect_set_xywh((iptr)local_454,iVar4,iVar3 + this->field_2e4 + 2,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_48c = (u8 *)0x0;
  }
  else {
    local_48c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x7d4));
  button_create
            ((Control *)(this[2].pad_48 + 0xc),(iptr)local_48c,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[2].pad_48 + 0xc),ADDR(0x403a85, unit_editor_edit_flags));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  _DAT_00635ef0 = (i32)(0x7f / (ulonglong)(longlong)(int)(uint)cosmic.road_move_mult);
  _DAT_00635f00 = 0xc;
  unit_editor_load_rules();
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_2fc,this->field_2ec);
  unit_editor_load_controls();
  unit_editor_update_domain_ctrls();
  this->field_2f8 = 5;
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4019d8, editor_wnd_on_move_close_dropdowns));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x401e01, unit_editor_redraw));
  wnd_repaint((SurfaceWindow *)this);
  window_show((C_004083b0_4 *)this);
  wnd_run_modal_loop((C_00408010_b8 *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (editor_bg_surface != (DibSurface *)0x0) {
    surface_delete(editor_bg_surface,1);
  }
  editor_bg_surface = (DibSurface *)0x0;
  this->field_2f8 = 0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005b1a05 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_bg_surface
#undef editor_next_ctrl_id
#undef editor_running
#undef _DAT_00635ef0
#undef _DAT_00635f00
#undef local_48c
#undef local_488
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_468
#undef local_460
#undef local_454
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005b1a29 auto */
#define local_b58 (*(C_004083b0_a28 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl unit_editor_run(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  unit_editor_window_run((C_004083b0_430 *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005b1a82 */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005b2590 auto */
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit4 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(32)))
i32 __cdecl unit_stack_validate(iptr unit)

{
  short x;
  short y;
  iptr iVar3;
  iptr unit5;
  iptr unit3;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((unit < 0) || (0x801 < unit)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x63607c, ((u8 *)&g.d_0063607c)),ADDR(0x636060, ((u8 *)&g.d_00636060)),0x11);
  }
  local_8 = 1;
  if (DAT_006ad918 == 0) {
    iVar3 = unit_stack_sum(unit,0xb);
    if (0x7ff < iVar3) {
      dbg_logf(ADDR(0x63609c, ((u8 *)&g.d_0063609c)),unit);
      local_8 = 0;
      unit4 = unit;
      x = units[unit].next_in_stack;
      do {
        unit2 = (iptr)x;
        if (unit4 < 0) break;
        x = units[unit4].x;
        y = units[unit4].y;
        unit_stack_unlink(unit4,0);
        unit_stack_link(unit4,(int)x,(int)y,0);
        unit4 = unit2;
        x = units[unit2].next_in_stack;
      } while (unit2 != unit);
    }
    unit2 = unit;
    unit3 = unit2;
    while (unit2 = unit3, -1 < units[unit2].prev_in_stack) {
      unit5 = (iptr)units[unit2].prev_in_stack;
      unit3 = unit5;
      if (units[units[unit2].prev_in_stack].id == 0) {
        dbg_logf(ADDR(0x6360c8, ((u8 *)&g.d_006360c8)),unit2);
        local_8 = 0;
        units[unit2].prev_in_stack = -1;
        unit3 = unit5;
        if (units[unit5].next_in_stack == unit2) {
          units[unit5].next_in_stack = -1;
          unit3 = unit5;
        }
      }
    }
    unit2 = unit;
    unit3 = unit2;
    while (unit2 = unit3, -1 < units[unit2].next_in_stack) {
      unit3 = (iptr)units[unit2].next_in_stack;
      if (units[unit2].id == 0) {
        dbg_logf(ADDR(0x6360f8, ((u8 *)&g.d_006360f8)),unit2);
        local_8 = 0;
        units[unit2].next_in_stack = -1;
        if (units[unit3].prev_in_stack == unit2) {
          units[unit3].prev_in_stack = -1;
        }
      }
    }
    unit2 = unit;
    unit3 = unit2;
    while (unit2 = unit3, -1 < units[unit2].prev_in_stack) {
      unit3 = (iptr)units[unit2].prev_in_stack;
      if ((units[units[unit2].prev_in_stack].x != units[unit2].x) ||
         (units[units[unit2].prev_in_stack].y != units[unit2].y)) {
        dbg_logf(ADDR(0x636128, ((u8 *)&g.d_00636128)),unit2);
        local_8 = 0;
        units[unit2].prev_in_stack = -1;
        if (units[unit3].next_in_stack == unit2) {
          units[unit3].next_in_stack = -1;
        }
      }
    }
    unit2 = unit;
    unit3 = unit2;
    while (unit2 = unit3, -1 < units[unit2].next_in_stack) {
      unit3 = (iptr)units[unit2].next_in_stack;
      if ((units[units[unit2].next_in_stack].x != units[unit2].x) ||
         (units[units[unit2].next_in_stack].y != units[unit2].y)) {
        dbg_logf(ADDR(0x636160, ((u8 *)&g.d_00636160)),unit2);
        local_8 = 0;
        units[unit2].next_in_stack = -1;
        if (units[unit3].prev_in_stack == unit2) {
          units[unit3].prev_in_stack = -1;
        }
      }
    }
  }
  else {
    local_8 = 1;
  }
  return local_8;
}
#undef unit2
#undef unit4
#undef local_8

/* 005b29aa auto */
int __cdecl unit_max_hp(iptr unit)

{
  return (int)(char)unit_types[units[unit].type].hit_points;
}

/* 005b29d7 auto */
int __cdecl unit_hp_remaining(iptr unit)

{
  int iVar1;
  
  if ((game.rules & 0x10) == 0) {
    units[unit].damage = '\0';
  }
  iVar1 = unit_max_hp(unit);
  iVar1 -= (uint)units[unit].damage;
  if (iVar1 < 1) {
    iVar1 = 0;
  }
  return iVar1;
}

/* 005b2a39 auto */
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
uint __cdecl unit_max_moves(iptr unit)

{
  int civ;
  int iVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = (uint)(char)unit_types[units[unit].type].move;
  if (local_10 == 0) {
    uVar3 = 0;
  }
  else {
    if (unit_types[units[unit].type].domain == 2) {
      civ = (int)units[unit].owner;
      iVar2 = civ_has_advance(civ,0x3b);
      if (iVar2 != 0) {
        local_10 += cosmic.road_move_mult;
      }
      iVar2 = civ_has_wonder(civ,0xc);
      if (iVar2 != 0) {
        local_10 += (uint)cosmic.road_move_mult * 2;
      }
      civ = civ_has_wonder(civ,3);
      if ((civ != 0) && ((unit_types[units[unit].type].flags & 0x20) == 0)) {
        local_10 += cosmic.road_move_mult;
      }
    }
    uVar3 = local_10;
    if (((units[unit].damage != '\0') && ((game.rules & 0x10) != 0)) &&
       (unit_types[units[unit].type].domain != 1)) {
      civ = unit_max_hp(unit);
      if (civ < 2) {
        civ = 1;
      }
      iVar2 = unit_hp_remaining(unit);
      local_10 = (int)(iVar2 * local_10) / civ;
      if ((int)local_10 % (int)(uint)cosmic.road_move_mult != 0) {
        local_10 = local_10 +
                   ((uint)cosmic.road_move_mult - (int)local_10 % (int)(uint)cosmic.road_move_mult);
      }
      if (unit_types[units[unit].type].domain == 2) {
        local_14 = (uint)cosmic.road_move_mult * 2;
      }
      else {
        local_14 = (uint)cosmic.road_move_mult;
      }
      uVar3 = local_14;
      if ((int)local_14 <= (int)local_10) {
        uVar3 = local_10;
      }
    }
  }
  return uVar3;
}
#undef local_14
#undef local_10

/* 005b2c3d auto */
int __cdecl unit_moves_left(iptr unit)

{
  int iVar1;
  
  iVar1 = unit_max_moves(unit);
  iVar1 -= (uint)units[unit].moves_used;
  if (iVar1 < 1) {
    iVar1 = 0;
  }
  return iVar1;
}

/* 005b2c82 auto */
iptr __cdecl unit_next_in_stack(iptr unit)

{
  if (-1 < unit) {
    unit_stack_validate(unit);
    unit = (iptr)units[unit].next_in_stack;
  }
  return unit;
}

/* 005b2cc3 auto */
iptr __cdecl unit_stack_last(iptr unit)

{
  if (-1 < unit) {
    unit_stack_validate(unit);
    for (; (-1 < units[unit].next_in_stack && (units[unit].next_in_stack != unit));
        unit = (iptr)units[unit].next_in_stack) {
    }
  }
  return unit;
}

/* 005b2d39 auto */
iptr __cdecl unit_stack_first(iptr unit)

{
  if (-1 < unit) {
    unit_stack_validate(unit);
    for (; (-1 < units[unit].prev_in_stack && (units[unit].prev_in_stack != unit));
        unit = (iptr)units[unit].prev_in_stack) {
    }
  }
  return unit;
}

/* 005b2daf auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl unit_stack_first_at(int civ,int x,int y)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = -1;
  for (unit = 0; (unit2 < 0 && (unit < game.num_units)); unit++) {
    if ((units[unit].id != 0) &&
       (((units[unit].x == x && (units[unit].y == y)) &&
        (units[unit].owner == civ)))) {
      unit2 = unit;
    }
  }
  uVar1 = unit_stack_first(unit2);
  return uVar1;
}
#undef unit
#undef unit2

/* 005b2f50 auto */
void __cdecl unit_set_sleep(iptr unit)

{
  if (units[unit].orders != 3) {
    units[unit].goto_x = -1;
  }
  units[unit].orders = 3;
  return;
}

/* 005b2f92 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl unit_stack_nth(int unit,int param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = -1;
  local_c = -1;
  for (unit = unit_stack_first(unit); (local_c < 0 && (-1 < unit));
      unit = unit_next_in_stack(unit)) {
    local_8++;
    if (local_8 == param_2) {
      local_c = unit;
    }
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 005b319e auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_unit_picked_up_count (*(int *)((u8 *)&g.d_006c90e0))
#define unit_stack_unlink_busy (*(i32 *)((u8 *)&g.d_006ad8d8))
void __cdecl unit_stack_unlink(iptr unit,int param_2)

{
  char cVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  
  unit_stack_unlink_busy = 1;
  if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
    bVar5 = -1 < units[unit].prev_in_stack;
    if (bVar5) {
      units[units[unit].prev_in_stack].next_in_stack = units[unit].next_in_stack;
    }
    bVar6 = -1 < units[unit].next_in_stack;
    if (bVar6) {
      units[units[unit].next_in_stack].prev_in_stack = units[unit].prev_in_stack;
    }
    units[unit].prev_in_stack = -1;
    units[unit].next_in_stack = -1;
    if ((!bVar6 && !bVar5) &&
       (iVar4 = map_in_bounds((int)units[unit].x,(int)units[unit].y), iVar4 != 0)) {
      iVar4 = tile_at((int)units[unit].x,(int)units[unit].y);
      *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 0xfe;
    }
    units[unit].x = (units[unit].owner * 4 + 4) * -0x19;
    units[unit].y = (units[unit].owner * 4 + 4) * -0x19;
    if ((2 < game.multiplayer) && (param_2 != 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    unit_stack_unlink_busy = 0;
  }
  else {
    unit_stack_unlink_busy = 0;
    nm_unit_picked_up_count = -2;
    net_send_message(0x3f,0,unit,0,0,0,0,0,0,0);
    iVar2 = timer_ticks();
    while ((nm_unit_picked_up_count == -2 && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_unit_picked_up_count == -2) {
      dbg_log(ADDR(0x636198, ((u8 *)&g.d_00636198)));
      popup_game_with_sprite(ADDR(0x6361c8, ((u8 *)&g.d_006361c8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return;
}
#undef game_loop_active
#undef nm_unit_picked_up_count
#undef unit_stack_unlink_busy

/* 005b345f auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_unit_put_down_count (*(int *)((u8 *)&g.d_006c90e8))
#define unit_stack_link_busy (*(i32 *)((u8 *)&g.d_006ad8dc))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl unit_stack_link(iptr unit,iptr x,iptr y,int param_4)

{
  char cVar1;
  iptr iVar2;
  iptr iVar3;
  int unit2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_stack_link_busy = 1;
  if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
    unit2 = unit_stack_first_at((int)units[unit].owner,x,y);
    units[unit].x = (i16)x;
    units[unit].y = (i16)y;
    units[unit].prev_in_stack = -1;
    units[unit].next_in_stack = (i16)unit2;
    if (unit2 < 0) {
      unit2 = map_in_bounds(x,y);
      if (unit2 != 0) {
        unit2 = tile_at(x,y);
        *(byte *)(unit2 + 1) = *(byte *)(unit2 + 1) | 1;
        civ = (int)units[unit].owner;
        if ((civ < 0) || (8 < civ)) {
          civ = 0xf;
        }
        unit2 = tile_at(x,y);
        *(byte *)(unit2 + 5) = *(byte *)(unit2 + 5) & 0xf;
        *(byte *)(unit2 + 5) = *(byte *)(unit2 + 5) | (byte)(civ << 4);
      }
    }
    else {
      units[unit2].prev_in_stack = (i16)unit;
    }
    if ((2 < game.multiplayer) && (param_4 != 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    unit_stack_link_busy = 0;
  }
  else {
    unit_stack_link_busy = 0;
    nm_unit_put_down_count = -2;
    net_send_message(0x41,0,unit,x,y,0,0,0,0,0);
    iVar2 = timer_ticks();
    while ((nm_unit_put_down_count == -2 && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_unit_put_down_count == -2) {
      dbg_log(ADDR(0x6361dc, ((u8 *)&g.d_006361dc)));
      popup_game_with_sprite(ADDR(0x63620c, ((u8 *)&g.d_0063620c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return;
}
#undef game_loop_active
#undef nm_unit_put_down_count
#undef unit_stack_link_busy
#undef civ

/* 005b36df auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_unit_relocated_count (*(int *)((u8 *)&g.d_006c90f8))
#define unit_relocate_busy (*(i32 *)((u8 *)&g.d_006ad8e4))
void __cdecl unit_relocate(iptr unit,iptr x,iptr y,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  unit_relocate_busy = 1;
  if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
    unit_stack_unlink(unit,0);
    unit_stack_link(unit,x,y,0);
    if ((2 < game.multiplayer) && (param_4 != 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    unit_relocate_busy = 0;
  }
  else {
    unit_relocate_busy = 0;
    nm_unit_relocated_count = -2;
    net_send_message(0x45,0,unit,x,y,0,0,0,0,0);
    iVar2 = timer_ticks();
    while ((nm_unit_relocated_count == -2 && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_unit_relocated_count == -2) {
      dbg_log(ADDR(0x636220, ((u8 *)&g.d_00636220)));
      popup_game_with_sprite(ADDR(0x636250, ((u8 *)&g.d_00636250)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return;
}
#undef game_loop_active
#undef nm_unit_relocated_count
#undef unit_relocate_busy

/* 005b3863 auto */
void __cdecl unit_relocate_in_place(iptr unit,i32 param_2)

{
  unit_relocate(unit,(int)units[unit].x,(int)units[unit].y,param_2);
  return;
}

/* 005b389f auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_bottomed_count (*(int *)((u8 *)&g.d_006c90f0))
#define unit_stack_bottom_busy (*(i32 *)((u8 *)&g.d_006ad8e0))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl unit_move_to_stack_bottom(iptr unit,int param_2)

{
  i16 x;
  i16 y;
  char cVar3;
  iptr iVar4;
  iptr iVar5;
  int unit2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (-1 < units[unit].next_in_stack) {
    unit_stack_bottom_busy = 1;
    if ((game.multiplayer < 3) || (cVar3 = net_is_host(&net_session), cVar3 != '\0')) {
      if (-1 < units[unit].next_in_stack) {
        x = units[unit].x;
        y = units[unit].y;
        unit3 = unit_stack_first(unit);
        if (unit3 == unit) {
          unit3 = unit_next_in_stack(unit);
        }
        unit_stack_unlink(unit,0);
        unit2 = unit_stack_last(unit3);
        units[unit2].next_in_stack = (i16)unit;
        units[unit].prev_in_stack = (i16)unit2;
        units[unit].next_in_stack = -1;
        units[unit].x = x;
        units[unit].y = y;
      }
      if ((2 < game.multiplayer) && (param_2 != 0)) {
        net_send_state_diff(0xff,2,0,0,0);
        XD_FlushSendBuffer(5000);
      }
      unit_stack_bottom_busy = 0;
    }
    else {
      unit_stack_bottom_busy = 0;
      nm_bottomed_count = -2;
      net_send_message(0x43,0,unit,0,0,0,0,0,0,0);
      iVar4 = timer_ticks();
      while ((nm_bottomed_count == -2 && (iVar5 = timer_ticks(), iVar5 - iVar4 < 0xe10))) {
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (nm_bottomed_count == -2) {
        dbg_log(ADDR(0x636264, ((u8 *)&g.d_00636264)));
        popup_game_with_sprite(ADDR(0x636294, ((u8 *)&g.d_00636294)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
      while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
  }
  return;
}
#undef game_loop_active
#undef nm_bottomed_count
#undef unit_stack_bottom_busy
#undef unit3

/* 005b3ae0 auto */
#define unit2 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_stack_relocate_all(iptr unit,iptr x,iptr y,int param_4)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = unit_stack_first(unit);
  while (-1 < unit2) {
    iVar1 = unit_next_in_stack(unit2);
    unit_relocate(unit2,x,y,0);
    unit2 = iVar1;
  }
  if ((2 < game.multiplayer) && (param_4 != 0)) {
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  return;
}
#undef unit2

/* 005b3b78 auto */
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl unit_stack_ships_to_top(iptr unit,i32 param_2)

{
  short x;
  short y;
  iptr iVar3;
  iptr iVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = -1;
  if (-1 < unit) {
    x = units[unit].x;
    y = units[unit].y;
    iVar3 = unit_stack_first(unit);
    iVar5 = iVar3;
    while (unit = iVar5, -1 < unit) {
      iVar4 = unit_next_in_stack(unit);
      iVar5 = iVar4;
      if (unit_types[units[unit].type].domain == 2) {
        unit2 = unit;
        unit_relocate(unit,(units[unit].owner * 4 + 4) * -0x4b,
                           (units[unit].owner * 4 + 4) * -0x4b,param_2);
        iVar5 = iVar4;
      }
    }
    if (-1 < unit2) {
      unit = unit_stack_first(unit2);
      while (-1 < unit) {
        iVar5 = unit_next_in_stack(unit);
        unit_relocate(unit,(int)x,(int)y,param_2);
        unit = iVar5;
      }
    }
  }
  return;
}
#undef unit2

/* 005b3d06 auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define nm_unit_created_result (*(int *)((u8 *)&g.d_006c90d8))
#define unit_create_busy (*(i32 *)((u8 *)&g.d_006ad8bc))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i8 *)(frame_ + FRAME_OFF(4)))
iptr __cdecl unit_create(iptr unit_type,uptr civ,iptr x,iptr y)

{
  char *pcVar1;
  char cVar2;
  iptr iVar3;
  iptr iVar4;
  i32 uVar3;
  int city;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_create_busy = 1;
  if ((game.multiplayer < 3) || (cVar2 = net_is_host(&net_session), cVar2 != '\0')) {
    for (unit = 0; (unit < game.num_units && (units[unit].id != 0));
        unit = unit + 1) {
    }
    if (game.num_units == unit) {
      if (((0x7ff < game.num_units) || (0x79c < civs[civ].num_military_units)) ||
         (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 && (0x7f7 < game.num_units)
          ))) {
        if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
           (game.multiplayer < 3)) {
          popup_game_with_sprite(ADDR(0x6362ec, ((u8 *)&g.d_006362ec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        unit_create_busy = 0;
        return 0xffffffff;
      }
      game.num_units++;
    }
    if ((char)unit_types[unit_type].role < 5) {
      civs[civ].num_military_units++;
    }
    pcVar1 = (char *)(unit_type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
    *pcVar1 = *pcVar1 + 1;
    *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) + 1;
    units[unit].type = (u8)unit_type;
    units[unit].owner = (byte)civ;
    units[unit].id = next_unit_id;
    next_unit_id++;
    if (game.multiplayer < 3) {
      units[unit].moves_used = '\0';
    }
    else if (mp_simultaneous_moves == '\0') {
      units[unit].moves_used = '\0';
    }
    else {
      uVar3 = unit_max_moves(unit);
      units[unit].moves_used = (u8)uVar3;
    }
    units[unit].damage = '\0';
    units[unit].field_0c = 'X';
    units[unit].flags = 0;
    units[unit].visibility = '\0';
    units[unit].orders = -1;
    units[unit].home_city = -1;
    city = city_find_nearest(x,y,-1,0xffffffff,-1);
    if (((civ != 0) && (-1 < city)) && ((int)cities[city].owner == (civ & 0xff))) {
      local_c = (i8)city;
      units[unit].home_city = local_c;
    }
    units[unit].counter = '\0';
    units[unit].field_0e = '\0';
    units[unit].last_dir = 0xff;
    units[unit].prev_in_stack = -1;
    units[unit].next_in_stack = -1;
    units[unit].x = -1;
    units[unit].y = -1;
    units[unit].goto_x = -1;
    units[unit].goto_y = -1;
    unit_stack_link(unit,x,y,0);
    unit_reveal_surroundings(unit,1);
    if (((game.turn != 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
       (game.multiplayer == '\0')) {
      if (unit_types[unit_type].domain == 2) {
        if ((game.field_0c & 4) == 0) {
          if (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) {
            popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x6362fc, ((u8 *)&g.d_006362fc)),unit);
          }
          game.field_0c = game.field_0c | 4;
        }
      }
      else if (unit_types[unit_type].domain == 1) {
        if ((game.field_0c & 2) == 0) {
          if (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) {
            popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x636304, ((u8 *)&g.d_00636304)),unit);
          }
          game.field_0c = game.field_0c | 2;
        }
      }
      else if (unit_types[unit_type].role == 7) {
        if ((game.field_0c & 0x10) == 0) {
          if (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) {
            popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x63630c, ((u8 *)&g.d_0063630c)),unit);
          }
          game.field_0c = game.field_0c | 0x10;
        }
      }
      else if ((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && ((char)unit_types[unit_type].role < 5)) {
        if (civs[civ].num_military_units == 1) {
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x636314, ((u8 *)&g.d_00636314)),unit);
        }
        if (civs[civ].num_military_units == 2) {
          popup_text_with_unit_noflags((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x636320, ((u8 *)&g.d_00636320)),unit);
        }
      }
    }
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    unit_create_busy = 0;
  }
  else {
    unit_create_busy = 0;
    nm_unit_created_result = -2;
    net_send_message(0x3d,0,unit_type,civ,x,y,0,0,0,0);
    iVar3 = timer_ticks();
    while ((nm_unit_created_result == -2 && (iVar4 = timer_ticks(), iVar4 - iVar3 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_unit_created_result == -2) {
      dbg_log(ADDR(0x6362a8, ((u8 *)&g.d_006362a8)));
      popup_game_with_sprite(ADDR(0x6362d8, ((u8 *)&g.d_006362d8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (unit = nm_unit_created_result, net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return unit;
}
#undef game_loop_active
#undef mp_simultaneous_moves
#undef nm_unit_created_result
#undef unit_create_busy
#undef unit
#undef local_c

/* 005b4391 auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define net_unit_deleted_ack (*(int *)((u8 *)&g.d_006c90c0))
#define unit_delete_busy (*(i32 *)((u8 *)&g.d_006ad8c0))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(0)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl unit_delete(iptr unit,int param_2)

{
  char *pcVar1;
  byte unit_type;
  short x;
  short y;
  char cVar5;
  iptr iVar6;
  iptr iVar7;
  int civ;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < unit) && (units[unit].id != 0)) {
    unit_delete_busy = 1;
    if ((game.multiplayer < 3) || (cVar5 = net_is_host(&net_session), cVar5 != '\0')) {
      x = units[unit].x;
      y = units[unit].y;
      unit_type = units[unit].type;
      if (units[unit].home_city == -1) {
        local_20 = 0xffffffff;
      }
      else {
        local_20 = (uint)(byte)units[unit].home_city;
      }
      civ = (int)units[unit].owner;
      if ((-1 < civ) && (unit < 0x800)) {
        if ((civs[civ].num_military_units != 0) &&
           ((char)unit_types[units[unit].type].role < 5)) {
          civs[civ].num_military_units--;
        }
        if (*(char *)&civs[civ].units_active[units[unit].type] != '\0') {
          pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
          *pcVar1 = *pcVar1 - 1;
        }
        if (*(int *)(&civ_unit_counts + civ * 4) != 0) {
          *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) - 1;
        }
      }
      unit_stack_unlink(unit,0);
      units[unit].id = 0;
      if (game.num_units - 1 == unit) {
        game.num_units--;
      }
      for (unit2 = 0; unit2 < game.num_units; unit2++) {
        if ((units[unit2].orders == 3) && (units[unit2].goto_x == unit)) {
          units[unit2].orders = -1;
        }
      }
      if ((param_2 != 0) &&
         (city_window_on_unit_change
                    ((FrameWindow *)&city_window,-1,(int)x,(int)y), -1 < (int)local_20))
      {
        city_window_refresh_if_city((FrameWindow *)&city_window,local_20);
      }
      if (((unit_types[unit_type].role == 5) && (civs[civ].num_cities == 0)) &&
         (*(char *)&civs[civ].units_active[unit_type] == '\0')) {
        civ_check_destroyed(civ,-1);
      }
      if ((2 < game.multiplayer) && (param_2 != 0)) {
        net_send_state_diff(0xff,2,0,0,0);
        net_send_message(0x87,0xff,-1,(int)x,(int)y,0,0,0,0,0);
        if (0 < (int)local_20) {
          net_send_message(0x88,0xff,local_20,0,0,0,0,0,0,0);
        }
        XD_FlushSendBuffer(5000);
      }
      unit_delete_busy = 0;
    }
    else {
      unit_delete_busy = 0;
      net_unit_deleted_ack = -2;
      net_send_message(0x37,0,unit,0,0,0,0,0,0,0);
      iVar6 = timer_ticks();
      while ((net_unit_deleted_ack == -2 && (iVar7 = timer_ticks(), iVar7 - iVar6 < 0xe10))) {
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (net_unit_deleted_ack == -2) {
        dbg_log(ADDR(0x63632c, ((u8 *)&g.d_0063632c)));
        popup_game_with_sprite(ADDR(0x63635c, ((u8 *)&g.d_0063635c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
      while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
  }
  return;
}
#undef game_loop_active
#undef net_unit_deleted_ack
#undef unit_delete_busy
#undef local_20
#undef unit2

/* 005b47fa auto */
void __cdecl unit_stack_delete_all(iptr unit,int param_2)

{
  iptr iVar1;
  
  unit = unit_stack_first(unit);
  while (-1 < unit) {
    iVar1 = unit_next_in_stack(unit);
    unit_delete(unit,0);
    unit = iVar1;
  }
  if ((2 < game.multiplayer) && (param_2 != 0)) {
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  return;
}

/* 005b488a auto */
void __cdecl unit_clear_visibility(iptr unit)

{
  if (-1 < unit) {
    units[unit].visibility = '\0';
  }
  return;
}

/* 005b48b1 auto */
void __cdecl unit_stack_clear_visibility(iptr unit)

{
  int unit2;
  
  for (unit2 = unit_stack_first(unit); -1 < unit2; unit2 = unit_next_in_stack(unit2)) {
    unit_clear_visibility(unit2);
  }
  return;
}

/* 005b490e auto */
void __cdecl unit_set_seen_by(iptr unit,iptr civ)

{
  if (((-1 < civ) && (units[unit].owner != civ)) && (-1 < unit)) {
    units[unit].visibility = units[unit].visibility | (byte)(1 << ((byte)civ & 0x1f));
  }
  return;
}

/* 005b496e auto */
void __cdecl unit_stack_set_seen_by(iptr unit,iptr civ)

{
  int unit2;
  
  for (unit2 = unit_stack_first(unit); -1 < unit2; unit2 = unit_next_in_stack(unit2)) {
    unit_set_seen_by(unit2,civ);
  }
  return;
}

/* 005b4ee2 auto */
void __cdecl unit_stack_add_visibility(iptr unit,i32 param_2)

{
  for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit)) {
    units[unit].visibility = units[unit].visibility | (byte)param_2;
  }
  return;
}

/* 005b50ad auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl unit_stack_sum(iptr unit,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (param_2 != 0xb) {
    unit = unit_stack_first(unit);
  }
  while ((-1 < unit && (local_8 < 0x800))) {
    switch(param_2) {
    case 0:
      local_8 += (char)unit_types[units[unit].type].cost;
      break;
    case 1:
      local_8 += (char)unit_types[units[unit].type].defense;
      break;
    case 2:
    case 0xb:
      local_8++;
      break;
    case 3:
      local_8 += (char)unit_types[units[unit].type].attack;
      break;
    case 4:
      if ((-1 < units[unit].prev_in_stack) && (unit_types[units[unit].type].role == 1)) {
        local_8++;
      }
      break;
    case 5:
      if (unit_types[units[unit].type].domain == 2) {
        local_8++;
      }
      break;
    case 6:
      if (unit_types[units[unit].type].domain == 2) {
        local_8 += (char)unit_types[units[unit].type].hold;
      }
      else if (unit_types[units[unit].type].domain == '\0') {
        local_8--;
      }
      break;
    case 7:
      if ((unit_types[units[unit].type].domain == 1) &&
         (1 < (char)unit_types[units[unit].type].range)) {
        local_8++;
      }
      break;
    case 8:
      if ((unit_types[units[unit].type].flags & 0x1000) != 0) {
        local_8++;
      }
      break;
    case 9:
      if ((unit_types[units[unit].type].flags & 0x80) != 0) {
        local_8++;
      }
      break;
    case 10:
      if ((unit_types[units[unit].type].flags & 8) != 0) {
        local_8++;
      }
    }
    if (param_2 == 0xb) {
      unit = (iptr)units[unit].next_in_stack;
    }
    else {
      unit = unit_next_in_stack(unit);
    }
  }
  return local_8;
}
#undef local_8

/* 005b53b6 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl unit_stack_count_role(iptr unit,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit)) {
    if ((char)unit_types[units[unit].type].role == param_2) {
      local_8++;
    }
  }
  return local_8;
}
#undef local_8

/* 005b542e auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_ship_stacked_result (*(int *)((u8 *)&g.d_006c9108))
#define unit_gather_cargo_busy (*(i32 *)((u8 *)&g.d_006ad8f8))
#define local_3c (*(int *)(frame_ + FRAME_OFF(4)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_30 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(48)))
int __cdecl unit_gather_cargo(iptr unit,iptr param_2,int param_3)

{
  bool bVar1;
  u8 uVar2;
  char civ;
  int x;
  int y;
  int iVar6;
  uint uVar7;
  iptr iVar8;
  iptr iVar9;
  bool bVar8;
  iptr iVar3;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  if ((unit < -1) || (0x801 < unit)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x63638c, ((u8 *)&g.d_0063638c)),ADDR(0x636370, ((u8 *)&g.d_00636370)),0x61d);
  }
  unit_gather_cargo_busy = 1;
  if ((game.multiplayer < 3) || (civ = net_is_host(&net_session), civ != '\0')) {
    if (param_2 != 0) {
      unit_stack_ships_to_top(unit,0);
    }
    local_30 = unit_stack_first(unit);
    if (local_30 == unit) {
      local_30 = unit_next_in_stack(unit);
    }
    x = (int)units[unit].x;
    y = (int)units[unit].y;
    iVar6 = map_in_bounds(x,y);
    if (iVar6 != 0) {
      local_10 = tile_is_ocean(x,y);
    }
    if (param_2 == 0) {
      for (unit2 = local_30; -1 < unit2; unit2 = unit_next_in_stack(unit2)) {
        units[unit2].flags = units[unit2].flags & 0xefff;
      }
    }
    else {
      unit_relocate(unit,(units[unit].owner * 5 + 5) * -0x28,
                         (units[unit].owner * 5 + 5) * -0x28,0);
    }
    local_28 = (int)(char)unit_types[units[unit].type].hold;
    uVar7 = unit_types[units[unit].type].flags & 0x80;
    if (((local_28 == 0) && (uVar7 == 0)) && ((unit_types[units[unit].type].flags & 8) != 0)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((uVar7 != 0) || (bVar1)) {
      local_28 = 0x14;
    }
    if (units[unit].owner == '\0') {
      local_28 = 0x14;
    }
    local_18 = 0;
    while( true ) {
      if ((uVar7 != 0) || (bVar1)) {
        local_3c = 1;
      }
      else {
        local_3c = 2;
      }
      if ((local_3c <= local_18) || (unit2 = local_30, iVar3 = unit2, local_28 == 0)) break;
LAB_005b57d5:
      unit2 = iVar3;
      if ((-1 < unit2) && (local_28 != 0)) {
        iVar8 = unit_next_in_stack(unit2);
        bVar8 = false;
        if ((uVar7 != 0) || (bVar1)) {
          uVar2 = 1;
        }
        else {
          uVar2 = '\0';
        }
        if (unit_types[units[unit2].type].domain == uVar2) goto code_r0x005b584c;
        goto LAB_005b5a3a;
      }
      local_18++;
    }
    if ((2 < game.multiplayer) && (param_3 != 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    unit_gather_cargo_busy = 0;
  }
  else {
    unit_gather_cargo_busy = 0;
    nm_ship_stacked_result = -2;
    net_send_message(0x49,0,unit,param_2,0,0,0,0,0,0);
    x = timer_ticks();
    while ((nm_ship_stacked_result == -2 && (y = timer_ticks(), y - x < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_ship_stacked_result == -2) {
      dbg_log(ADDR(0x6363b0, ((u8 *)&g.d_006363b0)));
      popup_game_with_sprite(ADDR(0x6363dc, ((u8 *)&g.d_006363dc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (local_28 = nm_ship_stacked_result, net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return local_28;
code_r0x005b584c:
  if ((!bVar1) || (iVar3 = iVar8, (unit_types[units[unit2].type].flags & 0x1000) != 0)) {
    if (local_18 == 0) {
      if ((uVar7 != 0) || (bVar1)) {
        bVar8 = true;
      }
      else if ((units[unit2].orders == 3) && (units[unit2].goto_x == unit)) {
        bVar8 = true;
      }
    }
    else if (local_18 == 1) {
      if (((uint)game.human_players & 1 << (units[unit2].owner & 0x1fU)) == 0) {
        if (((units[unit2].orders != 1) && (units[unit2].orders != 2)) ||
           (local_10 != 0)) {
          if ((iVar6 != 0) && (local_10 == 0)) {
            civ = units[unit2].owner;
            iVar9 = tile_landmass(x,y);
            if ((*(char *)&civs[civ].continent_policy[iVar9] != 1) ||
               (4 < (char)unit_types[units[unit2].type].role)) {
              bVar8 = true;
            }
          }
          else {
            bVar8 = true;
          }
        }
      }
      else if (units[unit2].orders == 3) {
        bVar8 = units[unit2].goto_x < 0;
      }
      else if (local_10 != 0) {
        bVar8 = true;
      }
    }
LAB_005b5a3a:
    if ((param_2 == 0) && ((units[unit2].flags & 0x1000) != 0)) {
      bVar8 = false;
    }
    iVar3 = iVar8;
    if (bVar8) {
      if (local_30 == unit2) {
        local_30 = iVar8;
      }
      if ((uVar7 != 0) || (bVar1)) {
        if (units[unit2].orders != 3) {
          units[unit2].orders = -1;
        }
      }
      else {
        unit_set_sleep(unit2);
        units[unit2].goto_x = (i16)unit;
      }
      if (param_2 == 0) {
        units[unit2].flags = units[unit2].flags | 0x1000;
      }
      else {
        unit_relocate(unit2,(units[unit2].owner * 5 + 5) * -0x28,
                           (units[unit2].owner * 5 + 5) * -0x28,0);
      }
      local_28--;
      iVar3 = iVar8;
    }
  }
  goto LAB_005b57d5;
}
#undef game_loop_active
#undef nm_ship_stacked_result
#undef unit_gather_cargo_busy
#undef local_3c
#undef unit2
#undef local_30
#undef local_28
#undef local_18
#undef local_10

/* 005b5bab auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_unit_stacked_count (*(int *)((u8 *)&g.d_006c9110))
#define unit_lift_off_map_busy (*(i32 *)((u8 *)&g.d_006ad8fc))
void __cdecl unit_lift_off_map(iptr unit,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  if (-1 < unit) {
    unit_lift_off_map_busy = 1;
    if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
      if (unit_types[units[unit].type].domain == 2) {
        unit_gather_cargo(unit,1,0);
      }
      else {
        unit_relocate(unit,(units[unit].owner * 5 + 5) * -0x28,
                           (units[unit].owner * 5 + 5) * -0x28,0);
      }
      if ((2 < game.multiplayer) && (param_2 != 0)) {
        net_send_state_diff(0xff,2,0,0,0);
        XD_FlushSendBuffer(5000);
      }
      unit_lift_off_map_busy = 0;
    }
    else {
      unit_lift_off_map_busy = 0;
      nm_unit_stacked_count = -2;
      net_send_message(0x4b,0,unit,0,0,0,0,0,0,0);
      iVar2 = timer_ticks();
      while ((nm_unit_stacked_count == -2 && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (nm_unit_stacked_count == -2) {
        dbg_log(ADDR(0x6363f0, ((u8 *)&g.d_006363f0)));
        popup_game_with_sprite(ADDR(0x63641c, ((u8 *)&g.d_0063641c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
      while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
  }
  return;
}
#undef game_loop_active
#undef nm_unit_stacked_count
#undef unit_lift_off_map_busy

/* 005b5d93 auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_safely_deleted_count (*(int *)((u8 *)&g.d_006c9118))
#define unit_delete_cargo_busy (*(i32 *)((u8 *)&g.d_006ad900))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl unit_delete_with_cargo(iptr unit,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar4 = false;
  unit_delete_cargo_busy = 1;
  if ((2 < game.multiplayer) && (cVar1 = net_is_host(&net_session), cVar1 == '\0')) {
    unit_delete_cargo_busy = 0;
    nm_safely_deleted_count = -2;
    net_send_message(0x4d,0,unit,0,0,0,0,0,0,0);
    iVar2 = timer_ticks();
    while ((nm_safely_deleted_count == -2 && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_safely_deleted_count == -2) {
      dbg_log(ADDR(0x636430, ((u8 *)&g.d_00636430)));
      popup_game_with_sprite(ADDR(0x636460, ((u8 *)&g.d_00636460)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    return;
  }
  x2 = (iptr)units[unit].x;
  y2 = (iptr)units[unit].y;
  if (unit_types[units[unit].type].domain == 2) {
    x2 = (iptr)units[unit].x;
    y2 = (iptr)units[unit].y;
    iVar2 = map_in_bounds(x2,y2);
    if (iVar2 == 0) {
      if (-x2 == (units[unit].owner * 5 + 5) * 0x28) {
        unit_stack_delete_all(unit,0);
        goto LAB_005b5fed;
      }
      bVar4 = true;
    }
    else {
      iVar2 = tile_is_ocean(x2,y2);
      bVar4 = iVar2 != 0;
    }
  }
  if (bVar4) {
    unit_gather_cargo(unit,0,0);
    unit_stack_delete_all(unit,0);
    city_window_on_unit_change((FrameWindow *)&city_window,-1,x2,y2);
  }
  else {
    unit_delete(unit,0);
  }
LAB_005b5fed:
  if ((2 < game.multiplayer) && (param_2 != 0)) {
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  unit_delete_cargo_busy = 0;
  return;
}
#undef game_loop_active
#undef nm_safely_deleted_count
#undef unit_delete_cargo_busy
#undef y2
#undef x2

/* 005b6042 auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define nm_visibly_deleted_count (*(int *)((u8 *)&g.d_006c9120))
#define unit_destroy_redraw_busy (*(i32 *)((u8 *)&g.d_006ad904))
void __cdecl unit_destroy_redraw(iptr unit,int param_2)

{
  char cVar1;
  int x;
  int y;
  int iVar4;
  
  unit_destroy_redraw_busy = 1;
  if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
    x = (int)units[unit].x;
    y = (int)units[unit].y;
    unit_delete_with_cargo(unit,0);
    iVar4 = map_in_bounds(x,y);
    if (iVar4 != 0) {
      map_redraw_tile_all_views(x,y);
    }
    if ((2 < game.multiplayer) && (param_2 != 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      net_send_message(0x72,0xff,x,y,0,0,0,0,0,0);
    }
    unit_destroy_redraw_busy = 0;
  }
  else {
    unit_destroy_redraw_busy = 0;
    nm_visibly_deleted_count = -2;
    net_send_message(0x4f,0,unit,0,0,0,0,0,0,0);
    x = timer_ticks();
    while ((nm_visibly_deleted_count == -2 && (y = timer_ticks(), y - x < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_visibly_deleted_count == -2) {
      dbg_log(ADDR(0x636474, ((u8 *)&g.d_00636474)));
      popup_game_with_sprite(ADDR(0x6364a4, ((u8 *)&g.d_006364a4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return;
}
#undef game_loop_active
#undef nm_visibly_deleted_count
#undef unit_destroy_redraw_busy

/* 005b633f auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl unit_is_selectable(iptr unit)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     (iVar1 = map_in_bounds((int)units[unit].x,(int)units[unit].y), iVar1 != 0)) {
    if ((((int)units[unit].owner == (uint)(byte)game.turn_civ) &&
        (units[unit].orders != 3)) &&
       ((units[unit].orders != 2 &&
        ((iVar1 = unit_moves_left(unit), iVar1 != 0 && ((units[unit].flags & 2) == 0))))))
    {
      local_8 = 1;
    }
    else {
      local_8 = 0;
    }
  }
  return local_8;
}
#undef local_8

/* 005b6458 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl unit_is_awake_with_moves(iptr unit)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     (-1 < units[unit].x)) {
    if ((units[unit].orders == 3) || (iVar1 = unit_moves_left(unit), iVar1 == 0)) {
      local_8 = 0;
    }
    else {
      local_8 = 1;
    }
  }
  return local_8;
}
#undef local_8

/* 005b6512 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define y2 (*(int *)(frame_ + FRAME_OFF(4)))
#define x2 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
iptr __cdecl unit_find_nearest_selectable(iptr unit,int param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 9999;
  local_20 = -1;
  local_c = -1;
  x2 = (int)map_cursor_x;
  y2 = (int)map_cursor_y;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     (game.turn_civ != '\0')) {
    x2 = (int)units[unit].x;
    y2 = (int)units[unit].y;
    local_c = (int)game.active_unit;
  }
  local_14 = 0;
  while( true ) {
    if (2 < local_14) {
      return local_20;
    }
    for (unit = 0; unit < game.num_units; unit++) {
      if (((units[unit].id != 0) && (iVar1 = unit_is_selectable(unit), iVar1 != 0)) &&
         (((units[unit].flags & 0x4000) == 0 &&
          ((param_2 != 1 || (units[unit].owner == human_civ)))))) {
        iVar1 = map_distance_diag(x2,y2,(int)units[unit].x,(int)units[unit].y);
        local_10 = iVar1 * 2 + 1;
        if (unit_types[units[unit].type].domain != 2) {
          local_10 = iVar1 * 2;
        }
        if (local_10 < local_8) {
          local_8 = local_10;
          local_20 = unit;
        }
        else if ((local_10 == local_8) && (game.active_unit == unit)) {
          local_20 = unit;
        }
      }
    }
    if (-1 < local_20) break;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) && ((local_14 != 0 || (unit != local_c)))) {
        units[unit].flags = units[unit].flags & 0xbfff;
      }
    }
    local_14++;
  }
  return local_20;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef local_20
#undef y2
#undef x2
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005b6787 auto */
void __cdecl unit_exhaust_moves(iptr unit)

{
  i32 uVar1;
  
  uVar1 = unit_max_moves(unit);
  units[unit].moves_used = (u8)uVar1;
  return;
}

/* 005b67af auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
iptr __cdecl unit_find_nearest(i32 param_1,i32 param_2,iptr param_3,iptr param_4)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  unit_nearest_dist = 9999;
  for (unit = 0; unit < game.num_units; unit++) {
    if (((units[unit].id != 0) &&
        (((param_3 < 0 || ((int)units[unit].owner == (param_3 & 0xffU))) &&
         (unit != param_4)))) &&
       (iVar1 = map_distance_diag(param_1,param_2,(int)units[unit].x,(int)units[unit].y),
       iVar1 <= unit_nearest_dist)) {
      local_c = unit;
      unit_nearest_dist = iVar1;
    }
  }
  return local_c;
}
#undef unit
#undef local_c

/* 005b6898 auto */
int __cdecl unit_home_city_name(iptr unit)

{
  int iVar1;
  
  if (units[unit].home_city == -1) {
    iVar1 = label_string(*(i32 *)(label_string_ids + 0x38));
  }
  else {
    iVar1 = (uint)(byte)units[unit].home_city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32));
  }
  return iVar1;
}

/* 005b6a58 auto */
i32 __cdecl unit_dlg_wake_unit_cb(iptr unit)

{
  if (-1 < unit) {
    units[unit].orders = -1;
    units[unit].flags = units[unit].flags & 0x7fff;
  }
  return 0;
}

/* 005b6aa0 auto */
i32 __cdecl unit_dlg_dblclick_accept_cb(void)

{
  return 1;
}

/* 005b6ab5 auto */
void __cdecl
unit_dlg_draw_sprite_cb(i32 param_1,iptr param_2,iptr unit,i32 param_4,int param_5,
            i32 param_6)

{
  gfx_draw_unit(param_2,unit,4,param_5 + 2,param_6,dlg_unit_sprite_zoom,0);
  return;
}

/* 005b6aea auto */
#define city (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_344 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_340 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(832)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(836)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(840)))
i32 __cdecl unit_stack_select_dialog(iptr unit,iptr param_2,int param_3)

{
  iptr iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(848)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  sprite_init(&local_4c);
  local_8 = 0;
  dialog_ctor(&local_340,0x4000);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  sprite_create_solid(&local_4c,0x42,0x30,0);
  dlg_unit_sprite_zoom = 0xffffffff;
  dlg_reset(&local_340,0x20001 - (uint)(param_3 == 0));
  dialog_set_title((DialogWindowView *)&local_340,param_2);
  dialog_set_width((DialogWindowView *)&local_340,0x154);
  dialog_set_sprite_click_fn((DialogOptionList *)&local_340,ADDR(0x402c11, unit_dlg_wake_unit_cb));
  dialog_set_sprite_dblclick_fn((DialogOptionList *)&local_340,ADDR(0x4018c0, unit_dlg_dblclick_accept_cb));
  dialog_set_sprite_draw_fn((C_0040bc40_28 *)&local_340,ADDR(0x402059, unit_dlg_draw_sprite_cb));
  dialog_set_image_zoom((DialogWindowView *)&local_340,0xffffffff);
  local_344 = 0;
  for (unit = unit_stack_first(unit); -1 < unit; unit = unit_next_in_stack(unit)) {
    local_344++;
    if (local_344 < 10) {
      text_clear();
      iVar1 = civ_adjective((int)units[unit].owner);
      text_append_str(iVar1);
      text_append_space();
      if ((units[unit].flags & 0x2000) != 0) {
        text_append_label(0xd);
        text_append_space();
      }
      text_append_string_id(unit_types[units[unit].type].name);
      text_append_space();
      text_append_lparen();
      if (units[unit].home_city == -1) {
        city = 0xffffffff;
      }
      else {
        city = (uint)(byte)units[unit].home_city;
      }
      text_append_city_name(city);
      if (unit_types[units[unit].type].role == 7) {
        text_append_comma();
        if ((char)units[unit].counter < '\0') {
          text_append_string_id(*(i32 *)(label_string_ids + 0x300));
        }
        else {
          text_append_string_id(commodity_names[(char)units[unit].counter]);
        }
      }
      text_append_rparen();
      dialog_add_sprite
                ((DialogOptionList *)&local_340,(iptr)&local_4c,unit,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
  }
  uVar2 = dlg_show_modal(&local_340,0);
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet FUN_005b6d9f */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005b6dab */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  return uVar2;
}
#undef city
#undef local_344
#undef local_340
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005b9179 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl nuclear_blast(iptr param_1,int param_2)

{
  int y;
  iptr x;
  iptr iVar3;
  iptr city;
  int iVar5;
  i32 uVar6;
  uint uVar7;
  uint uVar8;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  y = map_in_bounds(param_1,param_2);
  if (y != 0) {
    net_batch_begin();
    for (local_8 = 0; local_8 < 9; local_8++) {
      x = map_wrap_x((char)(&dir_dx_table)[local_8] + param_1);
      y = (char)(&dir_dy_table)[local_8] + param_2;
      iVar3 = map_in_bounds(x,y);
      if (iVar3 != 0) {
        city = city_at(x,y);
        if (city < 0) {
          iVar5 = tile_is_ocean(x,y);
          if (iVar5 == 0) {
            iVar5 = tile_at(x,y);
            uVar6 = tile_improvements(x,y);
            if (((byte)uVar6 & 0x42) == 0x40) {
              tile_set_improvements(x,y,0x40,0,1);
            }
            uVar7 = _rand();
            uVar8 = (int)uVar7 >> 0x1f;
            if (((uVar7 ^ uVar8) - uVar8 & 1 ^ uVar8) != uVar8) {
              tile_set_improvements(x,y,0x20,0,1);
            }
            if (((*(byte *)(iVar5 + 1) & 8) == 0) || ((*(byte *)(iVar5 + 1) & 4) == 0)) {
              uVar7 = _rand();
              uVar8 = (int)uVar7 >> 0x1f;
              if (((uVar7 ^ uVar8) - uVar8 & 1 ^ uVar8) != uVar8) {
                tile_set_improvements(x,y,8,0,1);
              }
              uVar7 = _rand();
              uVar8 = (int)uVar7 >> 0x1f;
              if (((uVar7 ^ uVar8) - uVar8 & 1 ^ uVar8) != uVar8) {
                tile_set_improvements(x,y,4,0,1);
              }
            }
            else {
              uVar7 = _rand();
              uVar8 = (int)uVar7 >> 0x1f;
              if (((uVar7 ^ uVar8) - uVar8 & 1 ^ uVar8) != uVar8) {
                tile_set_improvements(x,y,8,0,1);
              }
            }
            for (local_18 = 1; local_18 < 8; local_18++) {
              tile_update_known(x,y,local_18);
            }
            iVar5 = _rand();
            if (iVar5 % 3 != 0) {
              tile_add_pollution(x,y);
            }
            map_redraw_tile_all_views(x,y);
          }
        }
        else {
          cities[city].size -= (cities[city].size >> 1);
          map_redraw_area_all_views(x,y,0,human_civ,1);
        }
      }
    }
    net_batch_flush();
  }
  return;
}
#undef human_civ
#undef local_18
#undef local_8

/* 005badf0 auto */
#define local_58 (*(char * *)(frame_ + FRAME_OFF(0)))
#define local_54 (*(char (*)[80])(frame_ + FRAME_OFF(4)))
char * __cdecl path_join_upper(char *param_1,iptr param_2,i32 param_3)

{
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  FUN_005f22d0(local_54,param_2);
  for (local_58 = local_54; *local_58 != '\0'; local_58++) {
  }
  if (local_58[-1] != '\\') {
    FUN_005f22e0(local_54,&path_separator_str);
  }
  FUN_005f22d0(param_1,local_54);
  FUN_005f22e0(param_1,param_3);
  __strupr(param_1);
  return param_1;
}
#undef local_58
#undef local_54
