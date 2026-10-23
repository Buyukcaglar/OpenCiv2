/* The game, diplomacy and treaties: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00448cc0 auto */
void __cdecl diplo_status_icons_global_init(void)

{
  diplo_status_icons_static_init();
  diplo_status_icons_reg_atexit();
  return;
}

/* 00448cda auto */
void __cdecl diplo_status_icons_static_init(void)

{
  sprite_init((Sprite *)&ceasefire_icon_sprite);
  sprite_init((Sprite *)&peace_treaty_icon_sprite);
  sprite_init((Sprite *)&war_icon_sprite);
  sprite_init((Sprite *)&signal_allied_icon_sprite);
  sprite_init((Sprite *)&diplo_popup_portrait_sprite);
  return;
}

/* 00448d1c auto */
void __cdecl diplo_status_icons_reg_atexit(void)

{
  _atexit(diplo_status_icons_static_dtor);
  return;
}

/* 00448d39 auto */
void __cdecl diplo_status_icons_static_dtor(void)

{
  sprite_destroy((Sprite *)&diplo_popup_portrait_sprite);
  sprite_destroy((Sprite *)&signal_allied_icon_sprite);
  sprite_destroy((Sprite *)&war_icon_sprite);
  sprite_destroy((Sprite *)&peace_treaty_icon_sprite);
  sprite_destroy((Sprite *)&ceasefire_icon_sprite);
  return;
}

/* 00456f8b auto */
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl diplo_patience_limit(iptr civ2,iptr civ)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 2;
  if (diplo_cur_attitude < 0x19) {
    local_8 = 3;
  }
  if (0x3c < diplo_cur_attitude) {
    local_8--;
  }
  iVar1 = civ_has_wonder(civ2,0x14);
  if (iVar1 != 0) {
    local_8++;
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) {
    local_8++;
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
    local_8 += 2;
  }
  if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) {
    local_8 = 2;
  }
  return local_8;
}
#undef diplo_cur_attitude
#undef local_8

/* 0045705e auto */
#define diplo_ai_declare_war (*(int *)((u8 *)&g.d_0064b0e8))
#define diplo_ai_fear_level (*(uint *)((u8 *)&g.d_0064b0ec))
#define diplo_ai_outranks_target (*(uint *)((u8 *)&g.d_0064b12c))
#define diplo_cur_attitude (*(uint *)((u8 *)&g.d_0064b114))
#define diplo_initial_eval_done (*(int *)((u8 *)&g.d_00626a1c))
#define diplo_opening_eval_active (*(int *)((u8 *)&g.d_00626a20))
#define diplo_strongest_enemy (*(iptr *)((u8 *)&g.d_0064b0fc))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
void __cdecl diplo_eval_ai_stance(iptr civ2,iptr civ)

{
  uint *puVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  diplo_space_race_threat = ai_spaceship_race_behind(civ);
  local_c = 0;
  for (civ3 = 1; civ3 < 8; civ3++) {
    if ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 0x20) != 0) {
      local_c++;
    }
    if ((((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
        (iVar5 = civ_spaceship_launched(civ3), iVar5 != 0)) && (3 < game.difficulty)) {
      diplo_space_race_threat = 1;
    }
  }
  diplo_ai_outranks_target = (uint)(game.power_rank[civ2] < game.power_rank[civ]);
  diplo_suppressed_aggression = 0;
  if ((diplo_opening_eval_active != 0) && (diplo_initial_eval_done == 0)) {
    diplo_last_treaty_turn = (int)civs[civ2].last_treaty_turn[civ];
  }
  diplo_ai_fear_level = 0;
  diplo_tribute_demand = 0;
  diplo_ai_aggressive = 0;
  diplo_ai_request_mode = 1;
  for (local_14 = 1; local_14 < 0x40; local_14++) {
    if (((1 < civs[civ].num_cities) < civs[civ].continent_cities[local_14]) &&
       (civs[civ].continent_military[local_14] <
        civs[civ2].continent_attack[local_14])) {
      diplo_ai_fear_level = diplo_ai_fear_level +
                     ((uint)civs[civ2].continent_attack[local_14] *
                     ((-(uint)(game.difficulty == '\0') & 2) + 2)) /
                     (civs[civ].continent_military[local_14] + 1);
    }
    else {
      if ((*(short *)&civs[civ].continent_military[local_14] != 0) &&
         (*(short *)&civs[civ2].continent_military[local_14] != 0)) {
        diplo_ai_aggressive = 1;
      }
      if (*(char *)&civs[civ2].continent_cities[local_14] == '\0') {
        if (*(char *)&civs[civ].continent_cities[local_14] == '\0') {
          iVar5 = (uint)civs[civ].continent_attack[local_14] -
                  (uint)civs[civ2].continent_attack[local_14];
          diplo_tribute_demand += ((int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2);
        }
        else {
          diplo_tribute_demand = diplo_tribute_demand +
                         (int)((uint)civs[civ].continent_military[local_14] -
                              (uint)civs[civ2].continent_attack[local_14]) / 2;
        }
      }
      else {
        if ((civs[civ].continent_cities[local_14] < 2) &&
           ((((int)game.turn <= local_c * -0x32 + 200 || (6 < game.power_rank[civ2])) ||
            (6 < game.power_rank[civ])))) {
          uVar6 = (uint)civs[civ].continent_attack[local_14];
        }
        else {
          uVar6 = (uint)civs[civ].continent_attack[local_14] -
                  (uint)civs[civ2].continent_attack[local_14];
        }
        diplo_tribute_demand += uVar6;
      }
    }
  }
  iVar5 = civ_has_wonder(civ,9);
  if (iVar5 != 0) {
    diplo_tribute_demand += ((int)(diplo_tribute_demand + (diplo_tribute_demand >> 0x1f & 3U)) >> 2);
  }
  diplo_target_is_leader = 0;
  if ((((game.power_rank[civ2] == 7) && (4 < civs[civ2].num_cities)) &&
      ((1 < civs[civ].num_cities &&
       ((civs[civ2].units_active[0x2d] == '\0' && (game.difficulty != '\0')))))) &&
     (200 < game.turn)) {
    diplo_target_is_leader = 1;
  }
  diplo_cur_attitude = (uint)civs[civ].attitude[civ2];
  if (((diplo_target_is_leader != 0) ||
      (((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0 &&
       ((uint)civs[civ2].military_strength < (uint)civs[civ].military_strength * 3)))) &&
     (civs[civ2].units_active[0x2d] == '\0')) {
    diplo_tribute_demand = int_clamp(diplo_tribute_demand,(uint)game.power_rank[civ] * 2,9999);
    if (diplo_ai_aggressive == 0) {
      diplo_tribute_demand = int_clamp(diplo_tribute_demand,0,
                                        (civs[civ2].gold / 0x32) /
                                        (int)(8 - (uint)game.power_rank[civ]));
    }
    diplo_ai_aggressive = 1;
    diplo_ai_fear_level = 0;
    if ((int)diplo_cur_attitude < 0x4c) {
      diplo_cur_attitude = 0x4b;
    }
  }
  if ((diplo_space_race_threat != 0) && (diplo_ai_outranks_target != 0)) {
    diplo_ai_aggressive = 1;
  }
  if ((civs[civ].units_active[0x2d] != '\0') &&
     (puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594), *puVar1 = *puVar1 | 0x100,
     civs[civ2].units_active[0x2d] == '\0')) {
    diplo_ai_aggressive = 1;
    diplo_tribute_demand = int_clamp(diplo_tribute_demand,100,9999);
  }
  if ((civs[civ2].units_active[0x2d] != '\0') &&
     ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) {
    if (civs[civ].units_active[0x2d] == '\0') {
      diplo_ai_fear_level = ((int)(uint)civs[civ2].reputation >> 1) + 1;
      if (diplo_ai_fear_level < 5) {
        diplo_ai_fear_level = 4;
      }
    }
    else {
      diplo_tribute_demand = (int)((uint)civs[civ].units_active[0x2d] * (diplo_tribute_demand / 2)) /
                     (int)(uint)civs[civ2].units_active[0x2d];
    }
  }
  diplo_ai_fear_level = (int)diplo_ai_fear_level / ((int)(civs[civ2].reputation - 1) / 2 + 1);
  if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
    diplo_cur_attitude -= 0x19;
  }
  if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) {
    diplo_cur_attitude += 0x19;
  }
  if (civs[civ2].reputation != '\0') {
    diplo_cur_attitude = diplo_cur_attitude +
                   ((civs[civ2].reputation - 1) -
                   (int)civs[civ].field_48[civ2]) * 5;
  }
  if ((int)diplo_cur_attitude < 0x1a) {
    diplo_tribute_demand = diplo_tribute_demand / 2;
    diplo_ai_aggressive = 0;
  }
  else {
    iVar5 = diplo_attitude_level(diplo_cur_attitude);
    if (iVar5 < 4) {
      diplo_tribute_demand = (diplo_tribute_demand * 2) / 3;
    }
    else if (0x4a < (int)diplo_cur_attitude) {
      diplo_tribute_demand = (diplo_tribute_demand * 3) / 2;
      diplo_ai_aggressive = 1;
    }
  }
  if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 8) != 0) {
    diplo_ai_aggressive = 1;
  }
  if (((game.rules & 0x80) != 0) && (civs[civ].science_rate == '\0')) {
    diplo_ai_aggressive = 1;
  }
  if (diplo_ai_fear_level != 0) {
    diplo_ai_aggressive = 0;
    diplo_ai_request_mode = 0;
  }
  iVar5 = civ_has_wonder(civ2,6);
  if ((iVar5 != 0) || (iVar5 = civ_has_wonder(civ2,0x18), iVar5 != 0)) {
    diplo_target_is_leader = 0;
    diplo_suppressed_aggression = diplo_ai_aggressive;
    diplo_ai_aggressive = 0;
    diplo_cur_attitude -= 10;
    diplo_clear_treaty_flags(civ,civ2,0x10000);
  }
  if (civs[civ2].reputation != '\0') {
    diplo_tribute_demand += (int)((uint)civs[civ2].reputation * diplo_tribute_demand) / 2;
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) {
    if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 4) & 1) != 0) {
      diplo_tribute_demand = (int)(diplo_tribute_demand + (diplo_tribute_demand >> 0x1f & 3U)) >> 2;
    }
  }
  else {
    diplo_tribute_demand = diplo_tribute_demand << 1;
  }
  diplo_ai_units_near_cities = 0;
  city = 0;
  do {
    if (game.num_cities <= city) {
LAB_00457d0d:
      iVar5 = (game.difficulty + 1) * diplo_tribute_demand;
      iVar5 = int_clamp((int)(iVar5 + (iVar5 >> 0x1f & 0x1fU)) >> 5,0,0x14);
      diplo_tribute_demand = iVar5 * 0x32;
      if (((civs[civ2].gold < diplo_tribute_demand) && (diplo_tribute_demand < civs[civ2].gold * 2)) &&
         (0x31 < civs[civ2].gold)) {
        diplo_tribute_demand = (civs[civ2].gold / 0x32) * 0x32;
      }
      if ((diplo_tribute_demand == 0) ||
         ((uint)civs[civ].military_strength * 3 < (uint)civs[civ2].military_strength)) {
        diplo_ai_aggressive = 0;
      }
      if (9 < civs[civ].field_50[civ2]) {
        *(i8 *)&civs[civ].field_50[civ2] = 0;
        diplo_ai_aggressive = 0;
      }
      if (diplo_ai_aggressive == 0) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
          diplo_ai_request_mode = 0;
        }
      }
      else {
        diplo_ai_request_mode = 2;
      }
      diplo_ai_initial_aggressive = diplo_ai_aggressive;
      diplo_peace_inclination = 0;
      if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) {
        diplo_peace_inclination = -2;
      }
      if (((game.rules & 0x80) != 0) && (civs[civ].science_rate == '\0')) {
        diplo_peace_inclination--;
      }
      if (civs[civ2].reputation != '\0') {
        diplo_peace_inclination -= (int)(civs[civ2].reputation - 1) / 2;
      }
      diplo_weakest_enemy_civ = -1;
      diplo_strongest_enemy = -1;
      diplo_war_target_civ = -1;
      uVar3 = 0;
      uVar4 = 9999;
      local_20 = 0;
      for (civ3 = 1; civ3 < 8; civ3++) {
        if ((civ2 != civ3) && (civ != civ3)) {
          if ((*(byte *)&civs[civ].treaties[civ3] & 8) != 0) {
            if (game.power_rank[civ] < game.power_rank[civ2]) {
              diplo_peace_inclination--;
            }
            if ((((game.power_rank[civ2] == 7) && (4 < civs[civ2].num_cities)) &&
                (200 < game.turn)) &&
               ((game.difficulty != '\0' &&
                ((*(byte *)&civs[civ3].treaties[civ2] & 1) != 0)))) {
              if (diplo_ai_fear_level == 0) {
                if ((((*(byte *)(civ3 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) &&
                    (iVar5 = civ_has_wonder(civ2,6), iVar5 == 0)) &&
                   (iVar5 = civ_has_wonder(civ2,0x18), iVar5 == 0)) {
                  diplo_ai_aggressive = 1;
                }
              }
              else {
                diplo_ai_fear_level = int_clamp(diplo_ai_fear_level - 4,0,99);
              }
            }
          }
          if ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 8) != 0) {
            local_20++;
          }
          iVar5 = diplo_is_hostile(civ,civ3);
          if (iVar5 != 0) {
            uVar6 = (uint)civs[civ3].military_strength * 4;
            if (uVar6 - civs[civ].military_strength != 0 &&
                civs[civ].military_strength <= uVar6) {
              diplo_peace_inclination++;
            }
            if (civs[civ].military_strength < civs[civ3].military_strength) {
              diplo_peace_inclination++;
            }
            if (((*(byte *)&civs[civ2].treaties[civ3] & 1) != 0) &&
               ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 0x20) == 0)) {
              diplo_war_target_civ = civ3;
            }
            if (((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) != 0) &&
               ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 2) != 0)) {
              if (uVar3 < civs[civ3].military_strength) {
                uVar3 = civs[civ3].military_strength;
                diplo_strongest_enemy = civ3;
              }
              if (civs[civ3].military_strength < uVar4) {
                uVar4 = civs[civ3].military_strength;
                diplo_weakest_enemy_civ = civ3;
              }
            }
          }
        }
      }
      if (local_20 == 0) {
        diplo_clear_treaty_flags(civ,civ2,0x100000);
      }
      diplo_peace_inclination -= leaders[civs[civ].tribe].attack;
      if (civs[civ2].military_strength < civs[civ].military_strength) {
        diplo_peace_inclination--;
      }
      iVar5 = diplo_is_hostile(civ,civ2);
      if (((((int)(uint)(iVar5 != 0) < diplo_peace_inclination) && (diplo_target_is_leader == 0)) &&
          ((civs[civ].treaties[civ2] & 0x808) == 0)) &&
         (diplo_ai_aggressive = 0, (game.turn + civ + civ2 & 0x20U) != 0)) {
        diplo_tribute_demand = 0;
      }
      diplo_captured_city_count = 0;
      for (city = 0; city < game.num_cities; city++) {
        if (((cities[city].id != 0) && (cities[city].founder == civ)) &&
           (cities[city].owner == civ2)) {
          diplo_captured_city_count++;
        }
      }
      if ((((((diplo_initial_eval_done == 0) ||
             (6 < (int)((uint)civs[civ2].reputation -
                       (int)civs[civ].field_48[civ2]))) &&
            ((diplo_ai_declare_war = 0, (*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0 ||
             (4 < diplo_captured_city_count)))) &&
           ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) &&
          (((diplo_ai_aggressive != 0 || ((diplo_space_race_threat != 0 && (2 < game.difficulty)))) ||
           ((diplo_suppressed_aggression != 0 &&
            ((6 < (int)((uint)civs[civ2].reputation -
                       (int)civs[civ].field_48[civ2]) &&
             ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0)))))))) &&
         ((civs[civ].military_strength < civs[civ2].military_strength ||
          (((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0 ||
           (6 < (int)((uint)civs[civ2].reputation -
                     (int)civs[civ].field_48[civ2]))))))) {
        diplo_ai_declare_war = 1;
      }
      if (diplo_ai_declare_war != 0) {
        diplo_ai_aggressive = 0;
        diplo_ai_request_mode = 0;
        if (0x1d < (int)diplo_cur_attitude) {
          diplo_cur_attitude = 0x1e;
        }
      }
      if (((game.game_flags & 0x80) != 0) && (((int)(short)scenario_flags & 0x8000U) != 0)) {
        if (civ == 6) {
          if (civ2 == 7) {
            if (((byte)civs[6].treaties[7] & 8) != 0) {
              diplo_ai_aggressive = 1;
            }
          }
          else if (civ2 == 1) {
            diplo_ai_aggressive = 0;
          }
          else if (civ2 == 3) {
            diplo_ai_aggressive = 1;
          }
          else {
            diplo_ai_aggressive = 0;
          }
        }
        if ((civ == 3) && ((civ2 == 6 || (civ2 == 1)))) {
          diplo_ai_aggressive = 1;
        }
      }
      if (((((diplo_opening_eval_active != 0) &&
            (cVar2 = civs[civ].field_1f, iVar5 = diplo_patience_limit(civ2,civ),
            cVar2 < iVar5)) && (4 < civs[civ].government)) &&
          ((diplo_ai_aggressive != 0 &&
           ((civs[civ].treaties[civ2] & 0x400008) == 0)))) &&
         (((game.game_flags & 0x80) == 0 || ((scenario_flags & 1) == 0)))) {
        if ((((uint)civs[civ].military_strength * 2 < (uint)civs[civ2].military_strength * 3)
            && (diplo_target_is_leader == 0)) &&
           ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0)) {
          diplo_ai_aggressive = 0;
        }
        else {
          ai_choose_government(civ,1);
        }
      }
      if ((diplo_ai_fear_level == 0) && ((int)diplo_cur_attitude < 2)) {
        diplo_cur_attitude = 1;
      }
      if (((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x20) == 0) &&
         (0x62 < (int)diplo_cur_attitude)) {
        diplo_cur_attitude = 99;
      }
      if ((((*(byte *)&civs[civ2].treaties[civ] & 8) != 0) || (diplo_ai_request_mode == 0))
         && (0x49 < (int)diplo_cur_attitude)) {
        diplo_cur_attitude = 0x4a;
      }
      if (((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x20) != 0) &&
         ((int)diplo_cur_attitude < 0x1b)) {
        diplo_cur_attitude = 0x1a;
      }
      return;
    }
    if ((((cities[city].id != 0) && (cities[city].owner == civ2)) &&
        (iVar5 = tile_unit_owner((int)cities[city].x,(int)cities[city].y), iVar5 < 0)) &&
       ((iVar5 = unit_find_nearest((int)cities[city].x,(int)cities[city].y,civ,-1),
        -1 < iVar5 && (unit_nearest_dist < 3)))) {
      diplo_tribute_demand = diplo_tribute_demand << 1;
      diplo_ai_units_near_cities++;
      goto LAB_00457d0d;
    }
    city++;
  } while( true );
}
#undef diplo_ai_declare_war
#undef diplo_ai_fear_level
#undef diplo_ai_outranks_target
#undef diplo_cur_attitude
#undef diplo_initial_eval_done
#undef diplo_opening_eval_active
#undef diplo_strongest_enemy
#undef scenario_flags
#undef local_20
#undef civ3
#undef city
#undef local_14
#undef local_c

/* 00458a3b auto */
#define diplo_cur_attitude (*(i32 *)((u8 *)&g.d_0064b114))
void __cdecl diplo_set_attitude_arg(iptr param_1,iptr civ)

{
  iptr iVar1;
  iptr iVar2;
  
  text_clear();
  iVar1 = diplo_attitude_level(diplo_cur_attitude);
  text_append_string_id(attitude_names[iVar1]);
  if (game_language == 2) {
    text_append(ADDR(0x626a38, ((u8 *)&g.d_00626a38)));
  }
  text_append_space();
  iVar2 = civ_get_adjective(civ);
  text_append(iVar2);
  text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}
#undef diplo_cur_attitude

/* 00458ab1 auto */
#define diplo_session_active (*(i32 *)((u8 *)&g.d_00626a24))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(i8 (*)[8])(frame_ + FRAME_OFF(760)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(768)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl diplo_greet_emissary(iptr civ2,iptr civ)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  iptr iVar4;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  diplo_session_active = 1;
  if (((*(i8 *)((char *)&game.game_options + 2)) & 4) != 0) {
    gfx_get_screen_rect((iptr)local_20);
    iVar2 = int_clamp((local_18 - 0x280) / 3,1,9999);
    iVar3 = int_clamp((local_14 - 0x1e0) / 3,1,9999);
    dialog_set_default_offset(-iVar2,-iVar3);
    dialog_set_position((C_0040bc40_28 *)&local_314,-iVar2,-iVar3);
    diplo_leader_wnd_launch(civ2,civ);
  }
  diplo_set_attitude_arg(civ2,civ);
  iVar4 = civ_leader_name(civ);
  text_set_string_arg(1,iVar4);
  iVar4 = civ_leader_title(civ);
  text_set_string_arg(2,iVar4);
  iVar4 = civ_name_plural(civ);
  text_set_string_arg(3,iVar4);
  text_set_label_arg(5,*(i32 *)
                        (label_string_ids + 0x1a8 +
                        (uint)(leaders[civs[civ].tribe].female == '\0') * -4));
  iVar4 = civ_name_plural(civ2);
  text_set_string_arg(6,iVar4);
  text_clear();
  text_append(ADDR(0x626a3c, ((u8 *)&g.d_00626a3c)));
  if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) {
    text_append(ADDR(0x626a4c, ((u8 *)&g.d_00626a4c)));
  }
  else {
    text_append(ADDR(0x626a48, ((u8 *)&g.d_00626a48)));
  }
  iVar4 = rand_range(0,3);
  text_append_int(iVar4);
  dialog_load_game_text(&local_314,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  if (civs[civ].units_active[0x2d] != '\0') {
    dlg_load_game_section(&local_314,ADDR(0x626a50, ((u8 *)&g.d_00626a50)),0x8000);
  }
  dlg_show_modal(&local_314,0);
  if ((civs[civ2].units_active[0x2d] != '\0') &&
     ((civs[civ2].treaties[civ] & 0x104) != 0x100)) {
    text_clear();
    text_append(ADDR(0x626a60, ((u8 *)&g.d_00626a60)));
    text_append_int(2 - (uint)(civs[civ].units_active[0x2d] == '\0'));
    popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    puVar1 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
    *puVar1 = *puVar1 | 0x100;
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00458dd5 */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
  return;
}
#undef diplo_session_active
#undef local_314
#undef local_20
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00458df9 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define diplo_emissary_asked (*(int *)((u8 *)&g.d_00626a30))
#define diplo_emissary_response (*(int *)((u8 *)&g.d_00626a34))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_314 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_310 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
uint __cdecl diplo_ask_receive_emissary(iptr civ2,iptr civ,iptr param_3,iptr param_4)

{
  int iVar1;
  iptr iVar2;
  iptr iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_14 = 0;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (autoplay_active == 0) {
    if (diplo_emissary_asked == 0) {
      diplo_emissary_asked = 1;
      while (diplo_emissary_response == 0) {
        if ((civs[civ].units_active[0x2d] != '\0') &&
           ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 1) == 0)) {
          local_14 = 1;
        }
        diplo_eval_ai_stance(civ2,civ);
        iVar1 = map_in_bounds(param_3,param_4);
        if ((iVar1 != 0) && (iVar1 = mapviews_ensure_visible(param_3,param_4,civ2), iVar1 == 0)) {
          map_redraw_tile_all_views(param_3,param_4);
        }
        diplo_set_attitude_arg(civ2,civ);
        if (local_14 != 0) {
          iVar2 = civ_get_adjective(civ);
          text_set_string_arg(1,iVar2);
          popup_game(ADDR(0x626a6c, ((u8 *)&g.d_00626a6c)));
          break;
        }
        iVar2 = civ_leader_title(civ);
        text_set_string_arg(1,iVar2);
        iVar2 = civ_leader_name(civ);
        text_set_string_arg(2,iVar2);
        iVar2 = civ_name_plural(civ);
        text_set_string_arg(3,iVar2);
        text_set_label_arg(4,*(i32 *)
                              (label_string_ids + 0x1d8 +
                              (uint)(leaders[civs[civ].tribe].female == '\0') * -4));
        dialog_load_game_text(&local_308,ADDR(0x626a7c, ((u8 *)&g.d_00626a7c)));
        if ((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0) ||
            (iVar1 = civ_has_wonder(human_civ,0x18), iVar1 != 0)) ||
           (iVar1 = civ_has_wonder(human_civ,9), iVar1 != 0)) {
          uVar4 = 0;
          iVar3 = 2;
          iVar2 = label_string(*(i32 *)(label_string_ids + 0x1a0));
          dialog_add_option((DialogOptionList *)&local_308,iVar2,iVar3,uVar4);
        }
        iVar1 = dlg_show_modal(&local_308,0);
        diplo_emissary_response = -iVar1;
        if (diplo_emissary_response != -2) break;
        intel_report_show(civ2,civ);
        diplo_emissary_response = 0;
      }
      if (diplo_emissary_response != -1) {
        diplo_greet_emissary(civ2,civ);
      }
      local_314 = (uint)(diplo_emissary_response != -1);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00459169 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      local_310 = local_314;
    }
    else {
      local_310 = (uint)(diplo_emissary_response != -1);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00459169 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    }
  }
  else {
    diplo_emissary_response = -1;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00459169 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    local_310 = 0;
  }
  return local_310;
}
#undef autoplay_active
#undef diplo_emissary_asked
#undef diplo_emissary_response
#undef human_civ
#undef local_314
#undef local_310
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0045918e auto */
#define diplo_emissary_asked (*(i32 *)((u8 *)&g.d_00626a30))
#define diplo_emissary_response (*(i32 *)((u8 *)&g.d_00626a34))
#define diplo_initial_eval_done (*(i32 *)((u8 *)&g.d_00626a1c))
#define diplo_session_active (*(i32 *)((u8 *)&g.d_00626a24))
void __cdecl diplo_session_reset(void)

{
  diplo_session_active = 0;
  diplo_emissary_asked = 0;
  diplo_emissary_response = 0;
  diplo_initial_eval_done = 0;
  diplo_leader_wnd_close();
  return;
}
#undef diplo_emissary_asked
#undef diplo_emissary_response
#undef diplo_initial_eval_done
#undef diplo_session_active

/* 004591cb auto */
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
i32 __cdecl diplo_offer_sell_tech(iptr civ,iptr civ2,int param_3)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (diplo_wanted_tech < 0) {
    uVar1 = 0;
  }
  else {
    local_c = ai_advance_value(civ2,diplo_wanted_tech);
    local_c = local_c * 0x14;
    if (0x32 < diplo_cur_attitude) {
      local_c = (diplo_cur_attitude * local_c) / 0x32;
    }
    if ((((game.power_rank[civ] == 7) && (4 < civs[civ].num_cities)) && (200 < game.turn)
        ) && (game.difficulty != '\0')) {
      local_c = local_c << 1;
    }
    iVar2 = bits_count8((int)(char)game.advance_known_by[diplo_wanted_tech]);
    iVar2--;
    if (iVar2 < 2) {
      iVar2 = 1;
    }
    iVar2 = local_c / iVar2;
    local_c = iVar2 * 10;
    if (0x5dc < civs[civ].gold) {
      local_c = (iVar2 * 0x1e) / 2;
    }
    if (3000 < civs[civ].gold) {
      local_c = (local_c * 3) / 2;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      if (civs[civ].num_advances < civs[civ2].num_advances) {
        local_c = local_c / 2;
      }
      else {
        local_c -= ((int)(local_c + (local_c >> 0x1f & 3U)) >> 2);
      }
      if (civs[civ].num_advances + 4 < (uint)civs[civ2].num_advances) {
        local_c = local_c / 2;
      }
    }
    if (local_c < 0) {
      local_c = 30000;
    }
    if (local_c < 100) {
      local_c = 100;
    }
    if (civs[civ].gold < local_c) {
      uVar1 = 0;
    }
    else {
      text_set_label_arg(1,advances[diplo_wanted_tech].name);
      text_set_number_arg(0,local_c);
      if (param_3 < 2) {
        local_10 = popup_game(ADDR(0x626a88, ((u8 *)&g.d_00626a88)));
      }
      else {
        local_10 = popup_game(ADDR(0x626a94, ((u8 *)&g.d_00626a94)));
      }
      if (local_10 == 1) {
        civs[civ].gold -= local_c;
        status_draw_info(1);
        civ_give_advance(civ,diplo_wanted_tech,civ2,0,0);
        diplo_set_attitude_arg(civ,civ2);
        uVar1 = 1;
      }
      else {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}
#undef diplo_cur_attitude
#undef local_10
#undef local_c

/* 0045950b auto */
#define diplo_cur_attitude (*(i32 *)((u8 *)&g.d_0064b114))
#define local_39c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_398 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_394 (*(int *)(frame_ + FRAME_OFF(12)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(24)))
#define city (*(iptr *)(frame_ + FRAME_OFF(28)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_374 (*(Dialog *)(frame_ + FRAME_OFF(44)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(800)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(804)))
#define local_78 (*(iptr *)(frame_ + FRAME_OFF(808)))
#define local_74 (*(iptr *)(frame_ + FRAME_OFF(812)))
#define local_70 (*(i8 (*)[80])(frame_ + FRAME_OFF(816)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(896)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(900)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(904)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(908)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(912)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(916)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(920)))
int __cdecl
diplo_tech_exchange(iptr civ2,iptr civ,i32 param_3,i32 param_4,int param_5,int param_6
            )

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  iptr iVar7;
  i8 frame_[FRAME_OFF(928)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_374,0x4000);
  local_8 = 0;
  if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
    bVar5 = false;
  }
  else {
    bVar5 = true;
  }
  do {
    local_398 = 0;
    local_394 = 0;
    local_20 = 0;
    local_7c = 0;
    local_39c = 0;
    local_78 = -1;
    advance2 = -1;
    diplo_offer_tech_2nd = -1;
    diplo_offer_tech_best = -1;
    diplo_wanted_tech = -1;
    for (advance = 0; advance < 100; advance++) {
      if ((advances[advance].preq[0] != -2) || (advances[advance].preq[1] != -2)) {
        iVar6 = civ_has_advance(civ2,advance);
        local_80 = civ_has_advance(civ,advance);
        if ((iVar6 != 0) && (local_39c = local_39c + 1, advance2 < 0)) {
          advance2 = advance;
        }
        if ((local_80 != 0) && (local_7c = local_7c + 1, iVar6 == 0)) {
          for (local_74 = 0; local_74 < 0x1c; local_74++) {
            if (((improvements[local_74 + 0x27].preq == advance) &&
                (game.wonder_city[local_74] == -1)) &&
               (local_18 = local_74 / 7,
               civs[civ].wonders_by_group[local_18] <
               civs[civ2].wonders_by_group[local_18])) {
              for (city = 0; city < game.num_cities; city++) {
                if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
                   ((int)cities[city].building == -(local_74 + 0x27))) {
                  local_78 = local_74;
                  break;
                }
              }
            }
          }
          local_14 = ai_advance_value(civ2,advance);
          if (local_20 <= local_14) {
            diplo_wanted_tech = advance;
            local_20 = local_14;
          }
        }
        if ((iVar6 != 0) && (local_80 == 0)) {
          local_14 = ai_advance_value(civ,advance);
          if (local_14 < local_394) {
            if (local_398 <= local_14) {
              diplo_offer_tech_2nd = advance;
              local_398 = local_14;
            }
          }
          else {
            if (-1 < diplo_offer_tech_best) {
              diplo_offer_tech_2nd = diplo_offer_tech_best;
              local_398 = local_394;
            }
            diplo_offer_tech_best = advance;
            local_394 = local_14;
          }
        }
      }
    }
    if (param_6 != 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
      param_5 = 0;
      goto LAB_0045a526;
    }
    diplo_set_attitude_arg(civ2,civ);
    iVar7 = civ_get_adjective(civ);
    text_set_string_arg(1,iVar7);
    if (!bVar5) {
      if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) ||
          ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x10) != 0)) ||
         (diplo_captured_city_count != 0)) {
        if (param_5 == 0) {
          iVar6 = rand_range(0,2);
          if (iVar6 == 0) {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626ab0, ((u8 *)&g.d_00626ab0)));
          }
          else {
            diplo_leader_play_reaction(4);
            popup_game(ADDR(0x626aa0, ((u8 *)&g.d_00626aa0)));
          }
        }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
        goto LAB_0045a526;
      }
      if ((((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 2) != 0) ||
          ((diplo_ai_aggressive != 0 && (5 < local_7c)))) ||
         (iVar6 = diplo_attitude_level(diplo_cur_attitude), 5 < iVar6)) {
        if (param_5 == 0) {
          iVar6 = rand_range(0,2);
          if (iVar6 == 0) {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626ad4, ((u8 *)&g.d_00626ad4)));
          }
          else {
            diplo_leader_play_reaction(4);
            popup_game(ADDR(0x626ac4, ((u8 *)&g.d_00626ac4)));
          }
        }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
        goto LAB_0045a526;
      }
    }
    if ((-1 < local_78) && (3 < game.difficulty)) {
      if (param_5 == 0) {
        text_set_label_arg(1,improvements[local_78 + 0x27].name);
        popup_game(ADDR(0x626ae8, ((u8 *)&g.d_00626ae8)));
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
      }
      else {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
      }
      goto LAB_0045a526;
    }
    if (local_39c < local_7c) {
      if (param_5 == 1) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
        goto LAB_0045a526;
      }
      uVar3 = civs[civ].treaties[civ2];
      iVar6 = diplo_attitude_level(diplo_cur_attitude);
      if (((int)(5 - (uint)((uVar3 & 4) == 0)) < iVar6) && (!bVar5)) {
        iVar6 = diplo_offer_sell_tech(civ2,civ,param_5);
        if (iVar6 == 0) {
          if (param_5 == 0) {
            iVar7 = civ_get_adjective(civ2);
            text_set_string_arg(1,iVar7);
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626afc, ((u8 *)&g.d_00626afc)));
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
            param_5 = 0;
          }
          else {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
            param_5 = 0;
          }
        }
        else {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        }
        goto LAB_0045a526;
      }
    }
    if ((((((game.power_rank[civ2] == 7) && (4 < civs[civ2].num_cities)) && (!bVar5)) &&
         ((uVar3 = civs[civ].treaties[civ2], bVar4 = game.turn < 0xc9,
          iVar6 = diplo_attitude_level(diplo_cur_attitude),
          (int)((bVar4 + 3) - (uint)((uVar3 & 4) == 0)) < iVar6 &&
          (unit_types[0x16].prerequisite != diplo_offer_tech_best)))) &&
        (unit_types[0x15].prerequisite != diplo_offer_tech_best)) &&
       (((unit_types[0x19].prerequisite != diplo_offer_tech_best &&
         (unit_types[0x1a].prerequisite != diplo_offer_tech_best)) &&
        ((unit_types[0xb].prerequisite != diplo_offer_tech_best &&
         ((unit_types[7].prerequisite != diplo_offer_tech_best && (diplo_offer_tech_best != 0x22)))))))) {
      if (param_5 != 1) {
        iVar6 = diplo_offer_sell_tech(civ2,civ,param_5);
        if (iVar6 != 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
          goto LAB_0045a526;
        }
        if (param_5 == 0) {
          popup_game(ADDR(0x626b10, ((u8 *)&g.d_00626b10)));
        }
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
      param_5 = 0;
      goto LAB_0045a526;
    }
    if ((((diplo_offer_tech_best < 0) && (-1 < diplo_wanted_tech)) &&
        ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0)) &&
       ((bVar1 = civs[civ2].num_advances, cVar2 = leaders[civs[civ].tribe].civilize,
        iVar6 = int_clamp(civs[civ].num_advances / 0xc,0,5),
        (int)(((bVar1 + 6) - (int)cVar2) - iVar6) < (int)(uint)civs[civ].num_advances &&
        ((civs[civ].field_1f < 2 || (param_5 == 3)))))) {
      text_set_label_arg(1,advances[diplo_wanted_tech].name);
      diplo_leader_play_reaction(3);
      if (param_5 < 2) {
        popup_game(ADDR(0x626b20, ((u8 *)&g.d_00626b20)));
      }
      else {
        popup_game(ADDR(0x626b30, ((u8 *)&g.d_00626b30)));
      }
      civ_give_advance(civ2,diplo_wanted_tech,civ,0,0);
      diplo_wanted_tech = -1;
      if (param_5 < 2) {
        civs[civ].field_1f += 2;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
      }
      else {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 1;
      }
      goto LAB_0045a526;
    }
    if ((diplo_wanted_tech < 0) || (diplo_offer_tech_best < 0)) {
      if (param_5 != 1) {
        iVar6 = diplo_offer_sell_tech(civ2,civ,param_5);
        if (iVar6 != 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
          goto LAB_0045a526;
        }
        if (param_5 == 0) {
          popup_game(ADDR(0x626b40, ((u8 *)&g.d_00626b40)));
        }
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
      param_5 = 0;
      goto LAB_0045a526;
    }
    if (1 < param_5) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
      param_5 = 0;
      goto LAB_0045a526;
    }
    iVar6 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4);
    if (iVar6 == 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
      param_5 = 0;
      goto LAB_0045a526;
    }
    text_set_label_arg(1,advances[diplo_wanted_tech].name);
    iVar7 = civ_get_adjective(civ2);
    text_set_string_arg(2,iVar7);
    text_set_label_arg(3,advances[diplo_offer_tech_best].name);
    if (diplo_offer_tech_2nd < 0) {
      if (-1 < advance2) {
        text_set_label_arg(4,advances[advance2].name);
      }
    }
    else {
      text_set_label_arg(4,advances[diplo_offer_tech_2nd].name);
    }
    text_clear();
    text_append(ADDR(0x626b50, ((u8 *)&g.d_00626b50)));
    if (((param_5 == 0) && (diplo_ai_aggressive == 0)) &&
       (iVar6 = diplo_attitude_level(diplo_cur_attitude), iVar6 < 5)) {
      text_append(ADDR(0x626b60, ((u8 *)&g.d_00626b60)));
    }
    else {
      text_append(ADDR(0x626b5c, ((u8 *)&g.d_00626b5c)));
    }
    dialog_init_defaults(&local_374);
    dialog_load_game_text(&local_374,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if ((-1 < diplo_offer_tech_2nd) && (diplo_offer_tech_2nd != diplo_offer_tech_best)) {
      str_clear((iptr)local_70);
      str_append_label((iptr)local_70,0x6b);
      text_expand_vars((iptr)local_70,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      dialog_add_option((DialogOptionList *)&local_374,ADDR(0x679640, ((u8 *)&g.d_00679640)),2,0);
    }
    iVar6 = dlg_show_modal(&local_374,0);
    if (iVar6 == 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
      param_5 = 0;
      goto LAB_0045a526;
    }
    local_1c = local_394 * 2;
    if (iVar6 == 2) {
      iVar6 = civ_has_advance(civ,diplo_offer_tech_2nd);
      if ((((iVar6 != 0) || (iVar6 = civ_has_wonder(civ,9), iVar6 != 0)) ||
          ((game.power_rank[civ2] == 7 && (4 < civs[civ2].num_cities)))) ||
         ((local_398 < local_394 &&
          ((local_39c < local_7c || (iVar6 = diplo_attitude_level(diplo_cur_attitude), 4 < iVar6)))))) {
        diplo_leader_play_reaction(3);
        popup_game(ADDR(0x626b64, ((u8 *)&g.d_00626b64)));
        civs[civ].field_1f++;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
        param_5 = 0;
        goto LAB_0045a526;
      }
      int_swap(ADDR(0x64b124, ((u8 *)&g.d_0064b124)),ADDR(0x64b10c, ((u8 *)&g.d_0064b10c)));
      local_1c = local_398;
    }
    civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
    civ_steal_advance(civ2,civ);
    diplo_offer_tech_best = diplo_offer_tech_2nd;
    diplo_offer_tech_2nd = -1;
    civ_adjust_attitude(civ,civ2,-local_1c);
    civs[civ].flags = civs[civ].flags | 0x80;
    civs[civ2].flags = civs[civ2].flags | 0x80;
    diplo_ai_aggressive = 0;
  } while (param_5 != 0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0045a510 */ { dialog_dtor((Dialog *)((iptr)&local_374)); }
  param_5 = 1;
LAB_0045a526:
  return param_5;
}
#undef diplo_cur_attitude
#undef local_39c
#undef local_398
#undef local_394
#undef advance
#undef city
#undef advance2
#undef local_374
#undef local_80
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0045a535 auto */
#define diplo_ai_declare_war (*(i32 *)((u8 *)&g.d_0064b0e8))
void __cdecl diplo_form_alliance(iptr civ2,iptr civ)

{
  iptr iVar1;
  
  civ_adjust_attitude(civ,civ2,0xffffffe7);
  diplo_set_treaty_flags(civ,civ2,8);
  diplo_eval_ai_stance(civ2,civ);
  civs[civ].field_1f = '\0';
  civs[civ].flags = civs[civ].flags | 0x100;
  diplo_ai_declare_war = 0;
  civs[civ2].last_treaty_turn[civ] = game.turn;
  civs[civ2].flags = civs[civ2].flags | 0x100;
  diplo_set_attitude_arg(civ2,civ);
  iVar1 = civ_get_adjective(civ);
  text_set_string_arg(1,iVar1);
  iVar1 = civ_get_adjective(civ2);
  text_set_string_arg(2,iVar1);
  diplo_leader_play_reaction(2);
  popup_game_with_sprite(ADDR(0x626b74, ((u8 *)&g.d_00626b74)),(iptr)(&diplo_popup_portrait_sprite +
                                    ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
  return;
}
#undef diplo_ai_declare_war

/* 0045a6ab auto */
void __cdecl diplo_sign_peace_treaty(iptr civ2,iptr civ)

{
  iptr iVar1;
  i32 uVar2;
  i32 uVar3;
  
  diplo_set_treaty_flags(civ,civ2,0x4004);
  uVar3 = 0x32;
  uVar2 = 0;
  iVar1 = civ_get_attitude(civ,civ2);
  uVar2 = int_clamp(iVar1,uVar2,uVar3);
  civ_set_attitude(civ,civ2,uVar2);
  diplo_eval_ai_stance(civ2,civ);
  civs[civ].field_1f = '\0';
  civs[civ2].last_treaty_turn[civ] = game.turn;
  diplo_set_attitude_arg(civ2,civ);
  iVar1 = civ_get_adjective(civ);
  text_set_string_arg(1,iVar1);
  iVar1 = civ_get_adjective(civ2);
  text_set_string_arg(2,iVar1);
  diplo_leader_play_reaction(2);
  popup_game_with_sprite(ADDR(0x626b80, ((u8 *)&g.d_00626b80)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
  return;
}

/* 0045a7a8 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl diplo_agree_ceasefire(iptr civ2,iptr civ)

{
  uint *puVar1;
  iptr iVar2;
  i32 uVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  diplo_set_treaty_flags(civ,civ2,0x4002);
  diplo_clear_treaty_flags(civ,civ2,0x40000);
  uVar4 = 0x32;
  uVar3 = 0;
  iVar2 = civ_get_attitude(civ,civ2);
  uVar3 = int_clamp(iVar2,uVar3,uVar4);
  civ_set_attitude(civ,civ2,uVar3);
  diplo_eval_ai_stance(civ2,civ);
  civs[civ2].last_treaty_turn[civ] = game.turn;
  diplo_set_attitude_arg(civ2,civ);
  iVar2 = civ_get_adjective(civ);
  text_set_string_arg(1,iVar2);
  iVar2 = civ_get_adjective(civ2);
  text_set_string_arg(2,iVar2);
  diplo_leader_play_reaction(2);
  popup_game_with_sprite(ADDR(0x626b88, ((u8 *)&g.d_00626b88)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
  for (local_8 = 1; local_8 < 8; local_8++) {
    puVar1 = (uint *)(local_8 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
    *puVar1 = *puVar1 & 0xfffff7ff;
  }
  return;
}
#undef local_8

/* 0045a8e3 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ3 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl diplo_allies_join_war(iptr civ,iptr civ2)

{
  uint *puVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0) {
    for (civ3 = 1; civ3 < 8; civ3++) {
      if ((((civ3 != civ) && (civ3 != civ2)) &&
          ((*(byte *)&civs[civ].treaties[civ3] & 8) != 0)) &&
         (((civs[civ3].treaties[civ2] & 0x2008) == 0 &&
          ((*(byte *)&civs[civ3].treaties[civ2] & 1) != 0)))) {
        iVar2 = civ_name_plural(civ);
        text_set_string_arg(1,iVar2);
        iVar2 = civ_name_plural(civ3);
        text_set_string_arg(2,iVar2);
        iVar2 = civ_name_plural(civ2);
        text_set_string_arg(3,iVar2);
        if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
          if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
            if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
              if (human_civ == civ) {
                popup_game_with_sprite(ADDR(0x626ba4, ((u8 *)&g.d_00626ba4)),(iptr)(&diplo_popup_portrait_sprite +
                                                  ((game.advance_known_by[0xf] != '\0') - 1 &
                                                  0xffff7c80)),0);
              }
              else if ((human_civ != civ) && (2 < game.multiplayer)) {
                net_send_text_args(0x39,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ * 4) * 0x54),4,0,0,0);
              }
            }
            diplo_set_treaty_flags(civ3,civ2,0x2401);
            puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 0x594);
            *puVar1 = *puVar1 | 0x80800;
          }
        }
        else {
          if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
            if (human_civ == civ2) {
              popup_game_with_sprite(ADDR(0x626b94, ((u8 *)&g.d_00626b94)),(iptr)(&diplo_popup_portrait_sprite +
                                                ((game.advance_known_by[0xf] != '\0') - 1 &
                                                0xffff7c80)),0);
            }
            else if ((human_civ != civ2) && (2 < game.multiplayer)) {
              net_send_text_args(0x38,*(i32 *)
                                       (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54
                                       ),4,0,0,0);
            }
          }
          civ_adjust_attitude(civ3,civ2,100);
          diplo_set_treaty_flags(civ3,civ2,0x2401);
          puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 0x594);
          *puVar1 = *puVar1 | 0x80800;
          puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
          *puVar1 = *puVar1 | 0x80800;
          civs[civ2].last_treaty_turn[civ3] = game.turn;
        }
      }
    }
  }
  return;
}
#undef human_civ
#undef civ3

/* 0045ac71 auto */
void __cdecl diplo_declare_war(iptr civ,iptr civ3,iptr civ2)

{
  char *pcVar1;
  uint *puVar2;
  int iVar3;
  
  if (-1 < civ2) {
    pcVar1 = (char *)(civ + ADDR(0x64c6e8, ((u8 *)&civs + 72)) + civ2 * 0x594);
    *pcVar1 = *pcVar1 + 1;
  }
  if ((*(byte *)&civs[civ].treaties[civ3] & 8) == 0) {
    if ((*(byte *)&civs[civ].treaties[civ3] & 6) == 0) {
      if (-1 < civ2) {
        civ_adjust_attitude(civ2,civ,0xfffffffb);
      }
    }
    else {
      if (((*(byte *)&civs[civ].treaties[civ3] & 4) != 0) &&
         ((*(byte *)&civs[civ].treaties[civ3] & 2) != 0)) {
        if ((game.power_rank[civ] == 7) && ((4 < civs[civ].num_cities && (civ2 < 0))))
        {
          civs[civ].reputation++;
        }
        if ((game.difficulty != '\0') && (iVar3 = civ_has_wonder(civ,0x14), iVar3 == 0)) {
          civs[civ].reputation++;
        }
        if ((civ2 < 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
          pcVar1 = (char *)(civ3 + ADDR(0x64c6e8, ((u8 *)&civs + 72)) + civ * 0x594);
          *pcVar1 = *pcVar1 - 1;
        }
      }
      if (((game.power_rank[civ] == 7) && (4 < civs[civ].num_cities)) && (civ2 < 0)) {
        civs[civ].reputation++;
      }
      if ((game.difficulty != '\0') && (iVar3 = civ_has_wonder(civ,0x14), iVar3 == 0)) {
        civs[civ].reputation++;
      }
      if ((civ2 < 0) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
        pcVar1 = (char *)(civ3 + ADDR(0x64c6e8, ((u8 *)&civs + 72)) + civ * 0x594);
        *pcVar1 = *pcVar1 - 1;
      }
      if (-1 < civ2) {
        civ_adjust_attitude(civ2,civ,0xfffffff1);
      }
    }
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
      puVar2 = (uint *)(civ3 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
      *puVar2 = *puVar2 | 0x10;
    }
    diplo_set_treaty_flags(civ,civ3,0x2000);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
      puVar2 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 4);
      *puVar2 = *puVar2 | 0x80800;
      civs[civ].last_treaty_turn[civ3] = game.turn;
      diplo_allies_join_war(civ3,civ);
    }
  }
  else {
    if ((game.difficulty != '\0') && (iVar3 = civ_has_wonder(civ,0x14), iVar3 == 0)) {
      civs[civ].reputation++;
    }
    if ((civ2 < 0) &&
       (civs[civ].reputation = civs[civ].reputation + 1,
       (1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      pcVar1 = (char *)(civ3 + ADDR(0x64c6e8, ((u8 *)&civs + 72)) + civ * 0x594);
      *pcVar1 = *pcVar1 - 1;
    }
    if (-1 < civ2) {
      civ_adjust_attitude(civ2,civ,0xffffffe7);
    }
    diplo_cancel_alliance(civ,civ3);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
      puVar2 = (uint *)(civ3 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
      *puVar2 = *puVar2 | 0x10;
    }
  }
  return;
}

/* 0045b0d6 auto */
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(byte *)(frame_ + FRAME_OFF(16)))
void __cdecl diplo_ally_demand_help(iptr civ,iptr civ2)

{
  int iVar2;
  iptr iVar3;
  int iVar4;
  iptr civ3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ3 = human_civ;
  local_8 = (byte)human_civ;
  if ((((1 << (local_8 & 0x1f) & (uint)game.human_players) != 0) &&
      ((*(byte *)&civs[civ].treaties[human_civ] & 8) != 0)) &&
     ((civs[human_civ].treaties[civ2] & 0x2008) == 0)) {
    iVar2 = diplo_ask_receive_emissary(human_civ,civ,0xffffffff,0xffffffff);
    if (iVar2 == 0) {
      civ_adjust_attitude(civ,civ3,100);
    }
    else {
      iVar3 = civ_name_plural(civ2);
      text_set_string_arg(1,iVar3);
      local_18 = popup_game_with_sprite(ADDR(0x626bb0, ((u8 *)&g.d_00626bb0)),(iptr)(&diplo_popup_portrait_sprite +
                                                   ((game.advance_known_by[0xf] != '\0') - 1 &
                                                   0xffff7c80)),0);
      if (local_18 != 1) {
        local_10 = 0;
        for (local_c = 1; local_c < 0x3f; local_c++) {
          if (((1 < civs[civ].num_cities) < civs[civ].continent_cities[local_c]) &&
             (civs[civ].continent_military[local_c] <
              civs[civ2].continent_attack[local_c])) {
            local_10 = local_10 +
                       ((uint)civs[civ2].continent_attack[local_c] *
                       ((-(uint)(game.difficulty == '\0') & 2) + 2)) /
                       (civs[civ].continent_military[local_c] + 1);
          }
        }
        if (local_10 != 0) {
          iVar4 = int_clamp(local_10,0,civs[civ].gold / 0x32);
          iVar2 = iVar4 * 0x32;
          if (iVar2 != 0) {
            text_set_number_arg(0,iVar2);
            local_18 = popup_game_with_sprite(ADDR(0x626bbc, ((u8 *)&g.d_00626bbc)),(iptr)(&diplo_popup_portrait_sprite +
                                                         ((game.advance_known_by[0xf] != '\0') - 1 &
                                                         0xffff7c80)),0);
            if (local_18 == 1) {
              civs[civ].gold += iVar4 * -0x32;
              civs[civ3].gold += iVar2;
              status_draw_info(1);
            }
          }
        }
      }
      if (local_18 == 1) {
        diplo_declare_war(civ3,civ2,civ);
      }
      else {
        popup_game_with_sprite(ADDR(0x626bc8, ((u8 *)&g.d_00626bc8)),(iptr)(&diplo_popup_portrait_sprite +
                                          ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0
                          );
        if (diplo_cur_attitude < 0x33) {
          civ_adjust_attitude(civ,civ3,100);
        }
        else {
          diplo_cancel_alliance(civ3,civ);
        }
      }
    }
    diplo_session_reset();
  }
  return;
}
#undef diplo_cur_attitude
#undef human_civ
#undef local_18
#undef local_10
#undef local_c
#undef local_8

/* 0045b472 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl diplo_gold_attitude_value(int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_8 = 10;
  local_10 = 0x32;
  while (0 < param_1) {
    iVar1 = int_clamp(param_1,0,local_10);
    local_c += iVar1 / local_8;
    local_8 += 5;
    param_1 -= local_10;
    local_10 = 100;
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 0045b4da auto */
#define diplo_ai_declare_war (*(int *)((u8 *)&g.d_0064b0e8))
#define diplo_ai_fear_level (*(int *)((u8 *)&g.d_0064b0ec))
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
#define diplo_had_ceasefire (*(int *)((u8 *)&g.d_0064b138))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_58 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_54 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_4c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(16)))
#define y2 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(32)))
#define x2 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(52)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(60)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(76)))
i32 __cdecl diplo_ai_answer_proposal(iptr civ2,iptr civ,int param_3)

{
  uint *puVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  byte bVar5;
  i32 uVar6;
  iptr iVar9;
  iptr iVar7;
  iptr iVar8;
  int city;
  uint uVar11;
  uint uVar12;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_24 = 0;
  bVar4 = false;
  local_1c = 0;
  unit_blink_active = 0;
  switch(param_3) {
  case 1:
    local_38 = 0;
    for (local_4c = 1; local_4c < 8; local_4c++) {
      if ((*(byte *)&civs[civ2].treaties[local_4c] & 8) != 0) {
        local_38++;
      }
    }
    local_14 = (uint)(diplo_war_target_civ == -1);
    if (game.difficulty < 2) {
      local_14--;
    }
    if ((game.power_rank[civ] < 5) && (game.power_rank[civ2] < 5)) {
      if ((1 < game.difficulty) && (local_38 == 0)) {
        local_14--;
      }
      local_14--;
    }
    if (game.power_rank[civ2] < game.power_rank[civ]) {
      if (5 < game.power_rank[civ]) {
        local_14++;
      }
      if (6 < game.power_rank[civ]) {
        local_14++;
      }
      if ((game.power_rank[civ2] < 6) &&
         (civs[civ].military_strength < civs[civ2].military_strength)) {
        local_14--;
      }
    }
    if (diplo_target_is_leader == 0) {
      if (2 < (int)((uint)game.power_rank[civ2] - (uint)game.power_rank[civ])) {
        local_14--;
      }
    }
    else {
      local_14++;
    }
    if (diplo_ai_fear_level != 0) {
      local_14--;
    }
    bVar3 = (int)local_14 < diplo_peace_inclination;
    city = diplo_attitude_level(diplo_cur_attitude);
    bVar3 = game.difficulty == '\0' || city < 4 && bVar3;
    if ((game.power_rank[civ2] == 7) && (local_38 != 0)) {
      bVar3 = false;
    }
    if ((int)((-(uint)(game.difficulty == '\0') & 2) + 2) <
        (int)((uint)civs[civ2].reputation - (int)civs[civ].field_48[civ2])
       ) {
      bVar3 = false;
    }
    if ((game.power_rank[civ2] < 4) &&
       ((int)((uint)game.power_rank[civ2] * 0x14) < (int)game.turn)) {
      bVar3 = true;
    }
    if (((0 < diplo_war_target_civ) && (city = diplo_is_hostile(civ2,diplo_war_target_civ), city == 0))
       && ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 1) != 0)) {
      if ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 4) == 0) {
        local_14 = (uint)civs[civ].military_strength << 1;
      }
      else {
        local_14 = ((uint)civs[civ].military_strength * 3) / 2;
      }
      if (((*(byte *)(diplo_war_target_civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 2) != 0) &&
         (local_14 <= civs[diplo_war_target_civ].military_strength)) {
        bVar3 = true;
        local_1c = 2;
      }
    }
    if (((diplo_war_target_civ < 1) || (local_1c == 0)) &&
       ((game.power_rank[civ2] < 7 &&
        ((((game.power_rank[civ] < 7 && (99 < game.turn)) &&
          (local_38 < (int)(7 - (uint)game.power_rank[civ2]))) &&
         (city = diplo_attitude_level(diplo_cur_attitude), city < 5)))))) {
      local_18 = 8;
      local_3c = -1;
      for (local_4c = 1; local_4c < 8; local_4c++) {
        if ((((civ != local_4c) && (civ2 != local_4c)) &&
            (((game.power_rank[civ] <= game.power_rank[local_4c] &&
              (game.power_rank[civ2] <= game.power_rank[local_4c])) &&
             ((((*(byte *)&civs[civ2].treaties[local_4c] & 1) != 0 ||
               ((*(byte *)&civs[civ].treaties[local_4c] & 1) != 0)) &&
              ((*(byte *)(local_4c * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 0x20) == 0)))))) &&
           (((*(byte *)&civs[civ].treaties[local_4c] & 8) == 0 &&
            (local_c = (uint)((*(byte *)&civs[civ2].treaties[local_4c] & 1) != 0),
            (int)(game.power_rank[local_4c] - local_c) < local_18)))) {
          local_3c = local_4c;
          local_18 = game.power_rank[local_4c] - local_c;
        }
      }
      if ((0 < diplo_war_target_civ) && (game.power_rank[diplo_war_target_civ] != 7)) {
        local_3c = diplo_war_target_civ;
      }
      if (0 < local_3c) {
        diplo_war_target_civ = local_3c;
        bVar3 = true;
        local_1c = local_1c | 4;
      }
    }
    if (((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) ||
       (4 < (int)((uint)civs[civ2].reputation -
                 (int)civs[civ].field_48[civ2]))) {
      bVar3 = false;
    }
    if ((-1 < diplo_war_target_civ) &&
       ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 8) != 0)) {
      bVar3 = true;
      local_1c = local_1c | 1;
    }
    if (0x4b < diplo_cur_attitude) {
      bVar3 = false;
    }
    if ((4 < civs[civ].field_1f) && (game.difficulty != '\0')) {
      bVar3 = false;
    }
    diplo_set_attitude_arg(civ2,civ);
    iVar9 = civ_get_adjective(civ2);
    text_set_string_arg(1,iVar9);
    iVar9 = civ_get_adjective(civ);
    text_set_string_arg(2,iVar9);
    if (bVar3) {
      bVar3 = true;
      if (((((1 < civs[civ].field_1f) || (0x19 < diplo_cur_attitude)) ||
           (civs[civ2].reputation != '\0')) || (diplo_ai_declare_war != 0)) &&
         ((((local_1c & 3) == 0 || (diplo_ai_declare_war != 0)) && (0 < diplo_offer_tech_best)))) {
        text_set_label_arg(3,advances[diplo_offer_tech_best].name);
        text_clear();
        diplo_leader_play_reaction(3);
        text_append(ADDR(0x626c58, ((u8 *)&g.d_00626c58)));
        iVar9 = rand_range(0,1);
        text_append_int(iVar9);
        city = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
        if (city == 0) {
          bVar3 = false;
        }
        else {
          bVar4 = true;
          civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
          city = ai_advance_value(civ,diplo_offer_tech_best);
          civ_adjust_attitude(civ,civ2,city * -2);
          diplo_set_attitude_arg(civ2,civ);
          diplo_offer_tech_best = diplo_offer_tech_2nd;
          diplo_offer_tech_2nd = -1;
        }
      }
      if ((((1 < civs[civ].field_1f) || (0x19 < diplo_cur_attitude)) ||
          ((civs[civ2].reputation != '\0' || (diplo_ai_declare_war != 0)))) &&
         (((((local_1c & 2) == 0 || (diplo_ai_declare_war != 0)) && (!bVar4)) && (bVar3)))) {
        city = (int)((civs[civ2].gold / 0x32) * (uint)civs[civ].military_strength) /
                 (int)((uint)civs[civ].military_strength + (uint)civs[civ2].military_strength
                      + 1) + (uint)civs[civ2].reputation * 2;
        local_48 = city * 0x32;
        if (civs[civ].military_strength < civs[civ2].military_strength) {
          local_48 = city * 100;
        }
        for (; civs[civ2].gold < local_48; local_48 -= 0x32) {
        }
        if (0 < local_48) {
          text_set_number_arg(0,local_48);
          text_clear();
          diplo_leader_play_reaction(3);
          text_append(ADDR(0x626c68, ((u8 *)&g.d_00626c68)));
          iVar9 = rand_range(0,1);
          text_append_int(iVar9);
          diplo_leader_play_reaction(3);
          city = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
          if (city == 0) {
            bVar3 = false;
          }
          else {
            civs[civ2].gold -= local_48;
            civs[civ].gold += local_48;
            bVar4 = true;
            city = diplo_gold_attitude_value(local_48);
            civ_adjust_attitude(civ,civ2,-city);
            status_redraw(1);
            diplo_set_attitude_arg(civ2,civ);
          }
        }
      }
      if (bVar3) {
        if (0 < diplo_war_target_civ) {
          iVar9 = civ_name_plural(diplo_war_target_civ);
          text_set_string_arg(4,iVar9);
          diplo_leader_play_reaction(3);
          city = popup_game(ADDR(0x626c8c, ((u8 *)&g.d_00626c8c)));
          if (city == 0) {
            if (((local_1c != 0) || (game.power_rank[civ2] == 7)) ||
               ((2 < (int)((uint)civs[civ2].reputation -
                          (int)civs[civ].field_48[civ2]) ||
                (diplo_ai_declare_war != 0)))) {
              civs[civ].field_1f++;
              diplo_leader_play_reaction(3);
              if (!bVar4) {
                popup_game(ADDR(0x626cb4, ((u8 *)&g.d_00626cb4)));
              }
              else {
                popup_game(ADDR(0x626ca0, ((u8 *)&g.d_00626ca0)));
              }
              local_24 = (uint)!bVar4;
              return local_24;
            }
          }
          else {
            diplo_declare_war(civ2,diplo_war_target_civ,civ);
            if ((local_1c & 4) != 0) {
              diplo_set_treaty_flags(civ,diplo_war_target_civ,0x2001);
              diplo_set_treaty_flags(civ2,diplo_war_target_civ,1);
            }
            puVar1 = (uint *)(diplo_war_target_civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
            *puVar1 = *puVar1 | 0x80800;
            diplo_war_target_civ = -1;
          }
        }
        diplo_form_alliance(civ2,civ);
      }
      else {
        diplo_leader_play_reaction(3);
        popup_game(ADDR(0x626c78, ((u8 *)&g.d_00626c78)));
      }
    }
    else if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) &&
             ((int)((uint)civs[civ2].reputation -
                   (int)civs[civ].field_48[civ2]) < 3)) &&
            (diplo_captured_city_count == 0)) {
      if ((civs[civ2].num_cities < 4) ||
         ((game.power_rank[civ2] != 7 &&
          (((int)((uint)game.power_rank[civ2] - (uint)game.power_rank[civ]) < 3 ||
           (game.power_rank[civ2] < 5)))))) {
        city = diplo_attitude_level(diplo_cur_attitude);
        if (city < 4) {
          if (game.power_rank[civ2] < game.power_rank[civ]) {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626c20, ((u8 *)&g.d_00626c20)));
          }
          else if (civs[civ].field_1f < 3) {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626c44, ((u8 *)&g.d_00626c44)));
          }
          else {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626c30, ((u8 *)&g.d_00626c30)));
          }
        }
        else {
          diplo_leader_play_reaction(4);
          popup_game(ADDR(0x626c0c, ((u8 *)&g.d_00626c0c)));
        }
      }
      else {
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x626bf8, ((u8 *)&g.d_00626bf8)));
      }
    }
    else {
      if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) &&
          (2 < (int)((uint)civs[civ2].reputation -
                    (int)civs[civ].field_48[civ2]))) &&
         ((diplo_ai_fear_level != 0 || (city = diplo_attitude_level((uint)(diplo_cur_attitude < 2)), city != 0)
          ))) {
        diplo_leader_play_reaction(3);
        popup_game(ADDR(0x626bd4, ((u8 *)&g.d_00626bd4)));
      }
      else {
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x626be4, ((u8 *)&g.d_00626be4)));
      }
      civs[civ].field_1f++;
    }
    break;
  case 2:
    bVar5 = diplo_target_is_leader == 0 &&
            (diplo_cur_attitude < 0x33 &&
            (int)((uint)civs[civ2].reputation -
                 (int)civs[civ].field_48[civ2]) <=
            (int)((-(uint)(game.difficulty == '\0') & 2) + 4));
    if (((0 < diplo_war_target_civ) && (city = diplo_is_hostile(civ2,diplo_war_target_civ), city == 0))
       && ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 1) != 0)) {
      if ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 4) == 0) {
        local_14 = (uint)civs[civ].military_strength << 1;
      }
      else {
        local_14 = ((uint)civs[civ].military_strength * 3) / 2;
      }
      if (((*(byte *)(diplo_war_target_civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 2) != 0) &&
         (local_14 <= civs[diplo_war_target_civ].military_strength)) {
        bVar5 = 3;
      }
    }
    if ((0 < diplo_war_target_civ) &&
       ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 8) != 0)) {
      bVar5 = bVar5 | 4;
    }
    if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) &&
        (2 - leaders[civs[civ].tribe].attack <
         (int)((uint)civs[civ2].reputation - (int)civs[civ].field_48[civ2]
              ))) ||
       (6 < (int)((uint)civs[civ2].reputation -
                 (int)civs[civ].field_48[civ2]))) {
      bVar5 = 0;
    }
    if (0x4b < diplo_cur_attitude) {
      bVar5 = 0;
    }
    city = civ_has_wonder(civ2,6);
    if ((city != 0) || (city = civ_has_wonder(civ2,0x18), city != 0)) {
      bVar5 = bVar5 | 8;
    }
    if (bVar5 == 0) {
      if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) &&
          ((int)((uint)civs[civ2].reputation -
                (int)civs[civ].field_48[civ2]) < 5)) && (diplo_captured_city_count < 2)) {
        if ((diplo_target_is_leader == 0) && ((uint)game.power_rank[civ2] <= game.power_rank[civ] + 2))
        {
          if ((diplo_cur_attitude < 0x33) &&
             ((game.power_rank[civ] <= game.power_rank[civ2] || (diplo_cur_attitude < 0x1a)))) {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626d00, ((u8 *)&g.d_00626d00)));
          }
          else {
            diplo_leader_play_reaction(4);
            popup_game(ADDR(0x626cf0, ((u8 *)&g.d_00626cf0)));
          }
        }
        else {
          diplo_leader_play_reaction(4);
          popup_game(ADDR(0x626ce0, ((u8 *)&g.d_00626ce0)));
        }
      }
      else {
        if ((((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) &&
            (4 < (int)((uint)civs[civ2].reputation -
                      (int)civs[civ].field_48[civ2]))) &&
           ((diplo_ai_fear_level != 0 ||
            (city = diplo_attitude_level((uint)(diplo_cur_attitude < 2)), city != 0)))) {
          diplo_leader_play_reaction(3);
          popup_game(ADDR(0x626cc0, ((u8 *)&g.d_00626cc0)));
        }
        else {
          diplo_leader_play_reaction(4);
          popup_game(ADDR(0x626cd0, ((u8 *)&g.d_00626cd0)));
        }
        civs[civ].field_1f++;
      }
    }
    else {
      if ((((1 < civs[civ].field_1f) || (0x32 < diplo_cur_attitude)) ||
          (1 < (int)((uint)civs[civ2].reputation -
                    (int)civs[civ].field_48[civ2]))) &&
         (((bVar5 & 6) == 0 && (0 < diplo_offer_tech_best)))) {
        text_set_label_arg(3,advances[diplo_offer_tech_best].name);
        diplo_leader_play_reaction(3);
        text_clear();
        text_append(ADDR(0x626d10, ((u8 *)&g.d_00626d10)));
        iVar9 = rand_range(0,1);
        text_append_int(iVar9);
        city = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
        if (city == 0) {
          bVar5 = bVar5 & 8;
        }
        else {
          bVar4 = true;
          civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
          city = ai_advance_value(civ,diplo_offer_tech_best);
          civ_adjust_attitude(civ,civ2,city * -2);
          diplo_set_attitude_arg(civ2,civ);
          diplo_offer_tech_best = diplo_offer_tech_2nd;
          diplo_offer_tech_2nd = -1;
        }
      }
      if (((((1 < civs[civ].field_1f) || (0x32 < diplo_cur_attitude)) ||
           (1 < (int)((uint)civs[civ2].reputation -
                     (int)civs[civ].field_48[civ2]))) &&
          (((bVar5 & 4) == 0 && (!bVar4)))) && (bVar5 != 0)) {
        city = (int)((civs[civ2].gold / 0x32) * (uint)civs[civ].military_strength) /
                 (int)((uint)civs[civ].military_strength + (uint)civs[civ2].military_strength
                      + 1) + (uint)civs[civ2].reputation;
        local_48 = city * 0x32;
        if (civs[civ].military_strength < civs[civ2].military_strength) {
          local_48 = city * 100;
        }
        for (; civs[civ2].gold < local_48; local_48 -= 0x32) {
        }
        if (0 < local_48) {
          text_set_number_arg(0,local_48);
          diplo_leader_play_reaction(3);
          text_clear();
          text_append(ADDR(0x626d20, ((u8 *)&g.d_00626d20)));
          iVar9 = rand_range(0,1);
          text_append_int(iVar9);
          city = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
          if (city == 0) {
            bVar5 = bVar5 & 8;
          }
          else {
            civs[civ2].gold -= local_48;
            civs[civ].gold += local_48;
            bVar4 = true;
            city = diplo_gold_attitude_value(local_48);
            civ_adjust_attitude(civ,civ2,-city);
            diplo_set_attitude_arg(civ2,civ);
            status_redraw(1);
          }
        }
      }
      if (bVar5 == 0) {
        diplo_leader_play_reaction(3);
        popup_game(ADDR(0x626d30, ((u8 *)&g.d_00626d30)));
      }
      else {
        if (0 < diplo_war_target_civ) {
          iVar9 = civ_name_plural(diplo_war_target_civ);
          text_set_string_arg(4,iVar9);
          diplo_leader_play_reaction(3);
          city = popup_game(ADDR(0x626d40, ((u8 *)&g.d_00626d40)));
          if (city == 0) {
            if ((((bVar5 & 6) != 0) || (game.power_rank[civ2] == 7)) ||
               (3 < (int)((uint)civs[civ2].reputation -
                         (int)civs[civ].field_48[civ2]))) {
              civs[civ].field_1f++;
              diplo_leader_play_reaction(3);
              if (!bVar4) {
                popup_game(ADDR(0x626d68, ((u8 *)&g.d_00626d68)));
              }
              else {
                popup_game(ADDR(0x626d54, ((u8 *)&g.d_00626d54)));
              }
              local_24 = (uint)!bVar4;
              return local_24;
            }
          }
          else {
            diplo_declare_war(civ2,diplo_war_target_civ,civ);
            diplo_war_target_civ = -1;
          }
        }
        diplo_sign_peace_treaty(civ2,civ);
      }
    }
    break;
  case 3:
  case 4:
  case 5:
    cVar2 = civs[civ].field_1f;
    if (param_3 < 5) {
      uVar6 = diplo_patience_limit(civ2,civ);
      civs[civ].field_1f = (i8)uVar6;
    }
    else {
      civs[civ].field_1f++;
    }
    diplo_set_attitude_arg(civ2,civ);
    if ((diplo_ai_declare_war != 0) || ((*(byte *)&civs[civ].treaties[civ2] & 0x60) != 0))
    {
      diplo_set_attitude_arg(civ2,civ);
      text_clear();
      text_append(ADDR(0x626d74, ((u8 *)&g.d_00626d74)));
      iVar9 = rand_range(0,2);
      text_append_int(iVar9);
      diplo_ai_declare_war = 0;
      diplo_leader_play_reaction(4);
      diplo_set_treaty_flags(civ,civ2,0x2000);
      civs[civ2].last_treaty_turn[civ] = game.turn;
      popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
      return 1;
    }
    if ((param_3 == 3) && (game.power_rank[civ2] < game.power_rank[civ])) {
      diplo_ai_fear_level = (uint)game.power_rank[civ] - (uint)game.power_rank[civ2];
    }
    local_10 = int_clamp(diplo_ai_fear_level,0,civs[civ].gold / 0x32);
    local_10 = local_10 * 0x32;
    if (game.turn - diplo_last_treaty_turn < 8) {
      local_10 = 0;
      diplo_wanted_tech = -1;
    }
    if (game.turn - diplo_last_treaty_turn < 0x10) {
      local_10 = local_10 / 2;
    }
    if ((*(byte *)&civs[civ2].treaties[civ] & 4) == 0) {
      local_10 = local_10 / 2;
    }
    iVar7 = civ_has_wonder(civ,6);
    if ((iVar7 != 0) || (iVar8 = civ_has_wonder(civ,0x18), iVar8 != 0)) {
      local_10 = 0;
    }
    if (((((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) && (-1 < diplo_wanted_tech))
        && ((uint)civs[civ2].num_advances + (uint)game.difficulty <
            (uint)civs[civ].num_advances)) &&
       ((civs[civ].military_strength < civs[civ2].military_strength ||
        (game.power_rank[civ2] < game.power_rank[civ])))) {
      local_10 = 0;
      diplo_ai_fear_level = 1;
    }
    local_58 = 0;
    city = civ_has_wonder(civ2,6);
    if ((city == 0) && (city = civ_has_wonder(civ2,0x18), city == 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    if (6 < (int)((uint)civs[civ2].reputation -
                 (int)civs[civ].field_48[civ2])) {
      bVar4 = false;
    }
    if (((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) &&
       ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) {
      if (((diplo_ai_initial_aggressive != 0) || (0x4a < diplo_cur_attitude)) && ((diplo_ai_fear_level == 0 && (!bVar4)))) {
        uVar11 = _rand();
        uVar12 = (int)uVar11 >> 0x1f;
        if (((int)(uint)civs[civ].government <
             (int)((((uVar11 ^ uVar12) - uVar12 & 1 ^ uVar12) - uVar12) + 5)) &&
           (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x40) == 0 &&
            (0x19 < diplo_cur_attitude)))) goto LAB_0045d5d2;
      }
      for (unit = 0; unit < game.num_units; unit++) {
        if (((units[unit].id != 0) && (units[unit].owner == civ)) &&
           ((char)unit_types[units[unit].type].role < 6)) {
          x2 = (int)units[unit].x;
          y2 = (int)units[unit].y;
          city = tile_is_ocean(x2,y2);
          if (((city == 0) &&
              (city = city_find_nearest(x2,y2,civ2,0xffffffff,-1), -1 < city))
             && ((nearest_city_dist < 3 &&
                 (city = city_find_nearest(x2,y2,civ,0xffffffff,-1), -1 < city)
                 ))) {
            unit_relocate(unit,(int)cities[city].x,(int)cities[city].y,1);
            units[unit].visibility = '\0';
            units[unit].orders = -1;
            map_redraw_tile_all_views(x2,y2);
            local_58++;
          }
        }
      }
    }
LAB_0045d5d2:
    if (param_3 == 5) {
      civ_adjust_attitude(civ,civ2,2);
    }
    else {
      local_54 = 10;
      if (param_3 == 3) {
        if (game.power_rank[civ2] < game.power_rank[civ]) {
          local_54 = 5;
        }
        if (((civs[civ2].num_advances < civs[civ].num_advances) &&
            (game.power_rank[civ2] < game.power_rank[civ])) || (game.power_rank[civ2] < 4)
           ) {
          local_54 = 0;
        }
      }
      civ_adjust_attitude(civ,civ2,local_54);
    }
    if (local_58 != 0) {
      diplo_leader_play_reaction(3);
      popup_game_with_sprite(ADDR(0x626d7c, ((u8 *)&g.d_00626d7c)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
      if (param_3 == 5) {
        return 0;
      }
    }
    if (((local_10 == 0) && ((diplo_wanted_tech < 0 || (diplo_ai_fear_level == 0)))) || (param_3 == 5)) {
      if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
        if (((diplo_ai_initial_aggressive == 0) && (diplo_cur_attitude < 0x4c)) ||
           ((local_58 != 0 ||
            (((((diplo_ai_fear_level != 0 || (bVar4)) ||
               ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x40) != 0)) ||
              (diplo_cur_attitude < 0x1a)) && ((city = _rand(), city % 3 != 0 || (param_3 == 5))))))))
        {
          if (local_58 == 0) {
            diplo_leader_play_reaction(3);
            if (param_3 == 5) {
              popup_game(ADDR(0x626ddc, ((u8 *)&g.d_00626ddc)));
            }
            else {
              popup_game(ADDR(0x626de8, ((u8 *)&g.d_00626de8)));
            }
          }
        }
        else {
          local_24 = 1;
          diplo_set_attitude_arg(civ2,civ);
          text_clear();
          text_append(ADDR(0x626dd4, ((u8 *)&g.d_00626dd4)));
          iVar9 = rand_range(0,2);
          text_append_int(iVar9);
          diplo_ai_declare_war = 0;
          diplo_leader_play_reaction(4);
          diplo_set_treaty_flags(civ,civ2,0x2000);
          popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
          civs[civ2].last_treaty_turn[civ] = game.turn;
        }
      }
      else {
        city = diplo_tech_exchange(civ2,civ,x2,y2,(cVar2 < 2) + 2,0);
        if (city == 0) {
          if (((civs[civ2].num_advances < civs[civ].num_advances) &&
              (game.power_rank[civ2] < game.power_rank[civ])) ||
             (game.power_rank[civ2] < 4)) {
            diplo_leader_play_reaction(3);
            popup_game_with_sprite(ADDR(0x626db0, ((u8 *)&g.d_00626db0)),(iptr)(&diplo_popup_portrait_sprite +
                                              ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80
                                              )),0);
          }
          else if (((diplo_ai_initial_aggressive == 0) && (diplo_cur_attitude < 0x33)) && (diplo_target_is_leader == 0)) {
            if (local_58 == 0) {
              diplo_leader_play_reaction(3);
              popup_game_with_sprite(ADDR(0x626dc8, ((u8 *)&g.d_00626dc8)),(iptr)(&diplo_popup_portrait_sprite +
                                                ((game.advance_known_by[0xf] != '\0') - 1 &
                                                0xffff7c80)),0);
            }
          }
          else {
            diplo_leader_play_reaction(4);
            popup_game_with_sprite(ADDR(0x626dbc, ((u8 *)&g.d_00626dbc)),(iptr)(&diplo_popup_portrait_sprite +
                                              ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80
                                              )),0);
            diplo_cancel_alliance(civ2,civ);
            local_24 = 1;
          }
        }
      }
    }
    else {
      if ((diplo_wanted_tech < 0) ||
         ((local_10 != 0 && (civs[civ].num_advances <= civs[civ2].num_advances)))) {
        text_set_number_arg(0,local_10);
        diplo_leader_play_reaction(2);
        if (param_3 == 3) {
          popup_game_with_sprite(ADDR(0x626d94, ((u8 *)&g.d_00626d94)),(iptr)(&diplo_popup_portrait_sprite +
                                            ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80))
                             ,0);
        }
        else {
          popup_game(ADDR(0x626da4, ((u8 *)&g.d_00626da4)));
        }
        civs[civ2].gold += local_10;
        civs[civ].gold -= local_10;
        status_redraw(1);
      }
      else {
        text_set_label_arg(1,advances[diplo_wanted_tech].name);
        diplo_leader_play_reaction(2);
        popup_game(ADDR(0x626d88, ((u8 *)&g.d_00626d88)));
        civ_give_advance(civ2,diplo_wanted_tech,civ,0,0);
        diplo_wanted_tech = -1;
      }
      if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
        if (diplo_had_ceasefire == 0) {
          diplo_set_treaty_flags(civ,civ2,0x40000);
        }
        diplo_set_treaty_flags(civ,civ2,2);
      }
    }
    break;
  case 6:
    diplo_clear_treaty_flags(civ,civ2,8);
    civ_adjust_attitude(civ,civ2,0x32);
    diplo_eval_ai_stance(civ2,civ);
    diplo_set_attitude_arg(civ2,civ);
    diplo_leader_play_reaction(4);
    popup_game_with_sprite(ADDR(0x626df0, ((u8 *)&g.d_00626df0)),(iptr)(&diplo_popup_portrait_sprite +
                                      ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
    civs[civ2].reputation++;
    diplo_cancel_alliance(civ2,civ);
  }
  return local_24;
}
#undef diplo_ai_declare_war
#undef diplo_ai_fear_level
#undef diplo_cur_attitude
#undef diplo_had_ceasefire
#undef unit_blink_active
#undef local_58
#undef local_54
#undef unit
#undef local_4c
#undef local_48
#undef y2
#undef local_3c
#undef local_38
#undef x2
#undef local_24
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 0045dd7f auto */
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define civ4 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_334 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_330 (*(byte *)(frame_ + FRAME_OFF(16)))
#define local_32c (*(byte *)(frame_ + FRAME_OFF(20)))
#define city (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_324 (*(int *)(frame_ + FRAME_OFF(28)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(32)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(44)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(52)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(808)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(812)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(816)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(824)))
void __cdecl diplo_favor_menu(iptr civ2,iptr civ)

{
  uint *puVar1;
  char cVar2;
  byte bVar3;
  bool bVar4;
  iptr iVar5;
  iptr iVar6;
  iptr iVar7;
  iptr iVar8;
  int civ3;
  uint uVar10;
  byte *pbVar11;
  uint uVar12;
  i32 uVar13;
  i32 uVar14;
  iptr iVar12;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
LAB_0045ddb7:
  do {
    diplo_set_attitude_arg(civ2,civ);
    iVar5 = popup_game(ADDR(0x626dfc, ((u8 *)&g.d_00626dfc)));
    if (iVar5 == 0) {
      civs[civ].field_1f--;
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      goto LAB_0045f0a3;
    }
    if (iVar5 == 1) {
      iVar6 = diplo_tech_exchange(civ2,civ,0xffffffff,0xffffffff,0,0);
      if ((iVar6 != 0) &&
         (cVar2 = civs[civ].field_1f, iVar7 = diplo_patience_limit(civ2,civ),
         cVar2 + 1 < iVar7)) {
        civs[civ].field_1f++;
        goto LAB_0045ddb7;
      }
      net_send_state_diff(0xff,2,0,0,0);
    }
    if (iVar5 != 2) goto LAB_0045eb0a;
    dialog_load_game_text(&local_30c,ADDR(0x626e08, ((u8 *)&g.d_00626e08)));
    for (civ4 = 1; civ4 < 8; civ4++) {
      if ((((1 << ((byte)civ4 & 0x1f) & (uint)game.civs_alive) != 0) && (civ4 != civ))
         && (civ4 != civ2)) {
        uVar13 = 0;
        civ3 = civ4;
        iVar8 = civ_name_plural(civ4);
        dialog_add_option((DialogOptionList *)&local_30c,iVar8,civ3,uVar13);
      }
    }
    civ3 = dlg_show_modal(&local_30c,0);
  } while (civ3 == 0);
  iVar8 = civ_name_plural(civ3);
  text_set_string_arg(1,iVar8);
  if ((*(byte *)&civs[civ].treaties[civ3] & 1) == 0) {
    diplo_leader_play_reaction(3);
    popup_game(ADDR(0x626e14, ((u8 *)&g.d_00626e14)));
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  }
  else if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 4) & 0x20) == 0) {
    local_14 = int_clamp((int)(((((uint)civs[civ2].reputation + civs[civ].gold / 100
                                          ) - (uint)civs[civ3].reputation) -
                                        (int)civs[civ].field_48[civ2]) *
                                       ((int)(uint)civs[civ3].military_strength >> 1)) / 0x32,2,500
                                 );
    local_14 = local_14 * 0x32;
    if ((*(byte *)&civs[civ].treaties[civ3] & 6) == 0) {
      local_14 -= local_14 / 3;
    }
    if (civs[civ].gold < civs[civ2].gold) {
      local_14 += local_14 / 3;
    }
    if ((*(byte *)&civs[civ].treaties[civ3] & 8) != 0) {
      if (7000 < local_14) {
        local_14 = 7000;
      }
      local_14 = int_clamp(local_14 * 3,500,25000);
    }
    if ((game.power_rank[civ3] == 7) && (4 < civs[civ3].num_cities)) {
      local_14 = local_14 / 2;
    }
    if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 4) & 0x20) == 0) {
      local_14 += local_14 / 3;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      bVar4 = true;
      for (local_18 = 1; local_18 < 8; local_18++) {
        if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_18 * 4) & 0x20) != 0) {
          bVar4 = false;
        }
      }
      if (bVar4) {
        local_14 -= ((int)(local_14 + (local_14 >> 0x1f & 3U)) >> 2);
      }
      if ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 0x594) & 0x10) != 0) {
        local_14 -= ((int)(local_14 + (local_14 >> 0x1f & 3U)) >> 2);
      }
      if (game.power_rank[civ2] < game.power_rank[civ]) {
        local_14 -= local_14 / 3;
      }
    }
    if ((*(byte *)(civ2 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ3 * 0x594) & 2) != 0) {
      if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ3 * 4) & 2) == 0) {
        local_14 = local_14 / 2;
      }
      if (game.power_rank[civ2] < game.power_rank[civ3]) {
        local_14 = local_14 / 2;
      }
    }
    local_14 = int_clamp(local_14 / 100,1,500);
    local_14 = local_14 * 0x32;
    text_set_number_arg(0,local_14);
    local_324 = ((uint)civs[civ2].reputation -
                (int)civs[civ].field_48[civ2]) -
                (int)leaders[civs[civ].tribe].attack;
    if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) {
      local_324 += 2;
    }
    if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 4) & 0x20) == 0) {
      local_324++;
    }
    if (game.power_rank[civ3] < game.power_rank[civ2]) {
      local_324++;
    }
    if (game.power_rank[civ] < game.power_rank[civ2]) {
      local_324++;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      local_324 = local_324 / 2;
    }
    if ((local_324 < 7) ||
       ((((*(byte *)&civs[civ].treaties[civ3] & 8) == 0 &&
         ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0)) &&
        (((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 4) & 0x20) != 0 &&
         (game.power_rank[civ2] <= game.power_rank[civ3])))))) {
      if ((*(byte *)&civs[civ].treaties[civ3] & 8) == 0) {
        if ((((civs[civ].gold < 1000) || (civs[civ].gold <= civs[civ2].gold)) ||
            (diplo_offer_tech_best < 0)) || (diplo_offer_tech_2nd < 0)) {
          local_334 = popup_game(ADDR(0x626e54, ((u8 *)&g.d_00626e54)));
        }
        else {
          local_14 = -1;
          text_set_label_arg(2,advances[diplo_offer_tech_best].name);
          text_set_label_arg(3,advances[diplo_offer_tech_2nd].name);
          local_334 = popup_game(ADDR(0x626e48, ((u8 *)&g.d_00626e48)));
        }
      }
      else {
        diplo_leader_play_reaction(4);
        local_334 = popup_game(ADDR(0x626e38, ((u8 *)&g.d_00626e38)));
      }
      if (local_334 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      }
      else {
        if (local_14 < 0) {
          civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
          civ_give_advance(civ,diplo_offer_tech_2nd,civ2,0,0);
          diplo_offer_tech_best = -1;
          diplo_offer_tech_2nd = -1;
        }
        else {
          if (civs[civ2].gold < local_14) {
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626e60, ((u8 *)&g.d_00626e60)));
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
            goto LAB_0045f0a3;
          }
          civs[civ2].gold -= local_14;
          civs[civ].gold += local_14;
        }
        status_redraw(1);
        diplo_set_treaty_flags(civ,civ3,0x2401);
        puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 4);
        *puVar1 = *puVar1 | 0x80800;
        puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
        *puVar1 = *puVar1 | 0x100000;
        net_send_state_diff(0xff,2,0,0,0);
        iVar8 = civ_name_plural(civ);
        text_set_string_arg(1,iVar8);
        iVar8 = civ_name_plural(civ3);
        text_set_string_arg(2,iVar8);
        popup_game(ADDR(0x626e6c, ((u8 *)&g.d_00626e6c)));
        if (2 < game.multiplayer) {
          if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
             (human_civ != civ)) {
            net_send_text_args(0x62,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),
                               3,0,0,0);
          }
          (*(i8 *)((char *)&civ4 + 0)) = (byte)civ3;
          if (((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0) &&
             (human_civ != civ3)) {
            net_send_text_args(0x62,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54),3,
                               0,0,0);
          }
        }
        iVar8 = civ_get_adjective(civ3);
        text_set_string_arg(1,iVar8);
        if ((*(byte *)&civs[civ2].treaties[civ3] & 8) == 0) {
          if ((*(byte *)&civs[civ2].treaties[civ3] & 4) != 0) {
            uVar10 = _rand();
            uVar12 = (int)uVar10 >> 0x1f;
            if (((uVar10 ^ uVar12) - uVar12 & 1 ^ uVar12) == uVar12) {
              civ_adjust_attitude(civ3,civ2,0x19);
              diplo_leader_play_reaction(4);
              popup_game(ADDR(0x626e88, ((u8 *)&g.d_00626e88)));
              diplo_set_treaty_flags(civ2,civ3,0x2000);
              puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 0x594);
              *puVar1 = *puVar1 | 0x10;
            }
          }
        }
        else {
          uVar10 = _rand();
          uVar12 = (int)uVar10 >> 0x1f;
          if (((uVar10 ^ uVar12) - uVar12 & 1 ^ uVar12) == uVar12) {
            civ_adjust_attitude(civ3,civ2,0x19);
            diplo_leader_play_reaction(4);
            popup_game(ADDR(0x626e78, ((u8 *)&g.d_00626e78)));
            diplo_cancel_alliance(civ2,civ3);
          }
        }
        net_send_state_diff(0xff,2,0,0,0);
LAB_0045eb0a:
        if (iVar5 == 3) {
          if ((((((*(byte *)&civs[civ2].treaties[civ] & 8) == 0) &&
                (0 < diplo_cur_attitude)) && (civ3 = civ_has_wonder(civ2,9), civ3 == 0)) &&
              (civ3 = civ_has_wonder(civ2,0xc), civ3 == 0)) ||
             (((0x19 < diplo_cur_attitude || (civ3 = civ_has_advance(civ,0x2e), civ3 == 0)) ||
              (civ3 = civ_has_advance(civ2,0x2e), civ3 == 0)))) {
            iVar8 = civ_get_adjective(civ2);
            text_set_string_arg(1,iVar8);
            diplo_leader_play_reaction(3);
            popup_game(ADDR(0x626e94, ((u8 *)&g.d_00626e94)));
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
            goto LAB_0045f0a3;
          }
          diplo_leader_play_reaction(2);
          popup_game(ADDR(0x626e9c, ((u8 *)&g.d_00626e9c)));
          civs[civ].field_1f += 2;
          uVar10 = 1 << ((byte)civ & 0x1f);
          uVar12 = 1 << ((byte)civ2 & 0x1f);
          y2 = 0;
          x2 = 0;
          net_batch_begin();
          for (local_18 = 0; local_18 < map.area; local_18++) {
            civ3 = tile_at(x2,y2);
            if ((uVar10 & *(byte *)(civ3 + 4)) == 0) {
              if ((((uVar12 & *(byte *)(civ3 + 4)) != 0) &&
                  (tile_set_visible(x2,y2,uVar10,1,1), civ != 0)) &&
                 (civ2 != 0)) {
                uVar14 = 1;
                uVar13 = 1;
                iVar12 = civ;
                civ3 = tile_at(x2,y2);
                bVar3 = *(byte *)(civ3 + 1);
                pbVar11 = (byte *)known_at(x2,y2,civ2);
                known_set(x2,y2,(uint)(bVar3 & *pbVar11),iVar12,uVar13,uVar14);
              }
            }
            else {
              tile_set_visible(x2,y2,uVar12,1,1);
              if ((civ != 0) && (civ2 != 0)) {
                uVar14 = 1;
                uVar13 = 1;
                iVar8 = civ2;
                civ3 = tile_at(x2,y2);
                bVar3 = *(byte *)(civ3 + 1);
                pbVar11 = (byte *)known_at(x2,y2,civ);
                known_set(x2,y2,(uint)(bVar3 & *pbVar11),iVar8,uVar13,uVar14);
              }
            }
            x2 += 2;
            if ((int)map.width <= (int)x2) {
              y2++;
              x2 = y2 & 1;
            }
          }
          net_batch_flush();
          for (unit = 0; local_32c = (byte)uVar10, unit < game.num_units;
              unit = unit + 1) {
            if (units[unit].id != 0) {
              if (((uVar10 & units[unit].visibility) == 0) &&
                 (units[unit].owner != civ)) {
                if (((uVar12 & units[unit].visibility) != 0) ||
                   (units[unit].owner == civ2)) {
                  units[unit].visibility = units[unit].visibility | local_32c;
                }
              }
              else {
                local_330 = (byte)uVar12;
                units[unit].visibility = units[unit].visibility | local_330;
              }
            }
          }
          for (city = 0; city < game.num_cities; city++) {
            if (cities[city].id != 0) {
              if (((uVar10 & (int)(char)cities[city].known_to) == 0) &&
                 (cities[city].owner != civ)) {
                if (((uVar12 & (int)(char)cities[city].known_to) != 0) ||
                   (cities[city].owner == civ2)) {
                  cities[city].known_to = cities[city].known_to | local_32c;
                }
              }
              else {
                city_reveal_to_civ(city,civ2);
              }
            }
          }
          net_send_state_diff(0xff,2,0,0,0);
          map_redraw_all_views(human_civ,1);
        }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
      }
    }
    else {
      diplo_leader_play_reaction(3);
      popup_game(ADDR(0x626e28, ((u8 *)&g.d_00626e28)));
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    }
  }
  else {
    diplo_leader_play_reaction(3);
    popup_game(ADDR(0x626e20, ((u8 *)&g.d_00626e20)));
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0045f08d */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  }
LAB_0045f0a3:
  return;
}
#undef diplo_cur_attitude
#undef human_civ
#undef unit
#undef civ4
#undef local_334
#undef local_330
#undef local_32c
#undef city
#undef local_324
#undef y2
#undef x2
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0045f0b1 auto */
#define diplo_cur_attitude (*(i32 *)((u8 *)&g.d_0064b114))
#define diplo_gifts_this_meeting (*(int *)((u8 *)&g.d_0064b0f0))
#define local_338 (*(int *)(frame_ + FRAME_OFF(0)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_32c (*(int *)(frame_ + FRAME_OFF(12)))
#define advance2 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_320 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_318 (*(Dialog *)(frame_ + FRAME_OFF(32)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(788)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(792)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(796)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(800)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(804)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(808)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(812)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(816)))
void __cdecl diplo_gift_menu(iptr civ2,iptr civ)

{
  char *pcVar1;
  char advance;
  iptr iVar3;
  iptr iVar9;
  iptr iVar7;
  int city;
  iptr unit2;
  iptr iVar6;
  iptr unit;
  int iVar11;
  uint uVar12;
  uint uVar13;
  iptr city3;
  i8 frame_[FRAME_OFF(824)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_318,0x4000);
  local_8 = 0;
  diplo_set_attitude_arg(civ2,civ);
  iVar3 = popup_game(ADDR(0x626ea4, ((u8 *)&g.d_00626ea4)));
  if (iVar3 == 0) {
    civs[civ].field_1f--;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
  }
  else if (iVar3 == 1) {
    diplo_tech_exchange(civ2,civ,0xffffffff,0xffffffff,0,1);
    if (diplo_offer_tech_best < 0) {
      iVar9 = civ_name_plural(civ2);
      text_set_string_arg(1,iVar9);
      diplo_leader_play_reaction(4);
      popup_game(ADDR(0x626eb0, ((u8 *)&g.d_00626eb0)));
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
    }
    else {
      text_set_label_arg(1,advances[diplo_offer_tech_best].name);
      if (diplo_offer_tech_2nd < 0) {
        local_338 = popup_game(ADDR(0x626eb8, ((u8 *)&g.d_00626eb8)));
      }
      else {
        text_set_label_arg(2,advances[diplo_offer_tech_2nd].name);
        local_338 = popup_game(ADDR(0x626ec4, ((u8 *)&g.d_00626ec4)));
      }
      if (local_338 == 0) {
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x626ed0, ((u8 *)&g.d_00626ed0)));
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
      }
      else {
        if (local_338 == 1) {
          local_14 = ai_advance_value(civ,diplo_offer_tech_best);
          local_14 = local_14 << 2;
          civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
        }
        else {
          local_14 = ai_advance_value(civ,diplo_offer_tech_best);
          local_14 = local_14 * 2;
          civ_give_advance(civ,diplo_offer_tech_2nd,civ2,0,0);
        }
        civ_adjust_attitude(civ,civ2,-local_14);
        diplo_set_attitude_arg(civ2,civ);
        iVar9 = civ_get_adjective(civ);
        text_set_string_arg(1,iVar9);
        diplo_leader_play_reaction(2);
        popup_game(ADDR(0x626ed8, ((u8 *)&g.d_00626ed8)));
        civs[civ].field_1f -= ((char)diplo_gifts_this_meeting + 2);
        diplo_gifts_this_meeting++;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
      }
    }
  }
  else if (iVar3 == 2) {
    dialog_load_game_text(&local_318,ADDR(0x626ee0, ((u8 *)&g.d_00626ee0)));
    local_14 = civs[civ2].gold / 0x32;
    local_1c = 0;
    for (local_20 = 1; local_20 < 5; local_20++) {
      local_24 = ((int)(local_20 * local_14 + (local_20 * local_14 >> 0x1f & 3U)) >> 2) * 0x32;
      if ((0 < local_24) && (local_1c != local_24)) {
        local_1c = local_24;
        text_clear();
        text_append_label(0x72);
        text_append_space();
        text_append_gold(local_24);
        dialog_add_option((DialogOptionList *)&local_318,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_24,0);
      }
    }
    local_24 = dlg_show_modal(&local_318,0);
    if (local_24 == 0) {
      diplo_leader_play_reaction(4);
      popup_game(ADDR(0x626eec, ((u8 *)&g.d_00626eec)));
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
    }
    else {
      civs[civ2].gold -= local_24;
      civs[civ].gold += local_24;
      status_redraw(1);
      iVar7 = diplo_gold_attitude_value(local_24);
      civ_adjust_attitude(civ,civ2,-((iVar7 * 3) / 2));
      diplo_set_attitude_arg(civ2,civ);
      iVar9 = civ_get_adjective(civ);
      text_set_string_arg(1,iVar9);
      diplo_leader_play_reaction(2);
      popup_game(ADDR(0x626ef4, ((u8 *)&g.d_00626ef4)));
      civs[civ].field_1f -= ((char)diplo_gifts_this_meeting + 2);
      diplo_gifts_this_meeting++;
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
    }
  }
  else {
    if (iVar3 == 3) {
      local_32c = 0;
      dlg_load_game_section(&local_318,ADDR(0x626efc, ((u8 *)&g.d_00626efc)),1);
      for (city2 = 0; city2 < game.num_cities; city2++) {
        if ((cities[city2].id != 0) && (cities[city2].owner == civ2)) {
          dialog_add_option
                    ((DialogOptionList *)&local_318,(iptr)&cities[city2].name,city2,0);
          local_32c++;
        }
      }
      if (local_32c == 0) {
        popup_game(ADDR(0x626f0c, ((u8 *)&g.d_00626f0c)));
        civs[civ].field_1f--;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0045fd59;
      }
      city = dlg_show_modal(&local_318,0);
      if (city < 0) {
        civs[civ].field_1f--;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0045fd59;
      }
      unit2 = tile_first_unit((int)cities[city].x,(int)cities[city].y);
      if (unit2 < 0) {
        popup_game(ADDR(0x626f1c, ((u8 *)&g.d_00626f1c)));
        civs[civ].field_1f--;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0045fd59;
      }
      city4 = city_find_nearest((int)cities[city].x,(int)cities[city].y,civ,0xffffffff,
                                    -1);
      if ((((city4 < 0) || (iVar6 = diplo_attitude_level(diplo_cur_attitude), 4 < iVar6)) ||
          (civs[civ2].num_advances < civs[civ].num_advances)) ||
         ((game.power_rank[civ2] < game.power_rank[civ] ||
          (civs[civ2].military_strength < civs[civ].military_strength)))) {
        iVar9 = civ_get_adjective(civ);
        text_set_string_arg(1,iVar9);
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x626f2c, ((u8 *)&g.d_00626f2c)));
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0045fd59;
      }
      text_clear();
      text_append_label(0x77);
      text_append_space();
      text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
      unit = unit_stack_select_dialog(unit2,ADDR(0x679640, ((u8 *)&g.d_00679640)),1);
      if (unit < 0) {
        civs[civ].field_1f--;
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0045fd59;
      }
      if ((-1 < unit_types[units[unit].type].obsolete_by) &&
         (iVar11 = civ_has_advance(civ,(int)unit_types[units[unit].type].obsolete_by),
         iVar11 != 0)) {
        iVar9 = civ_get_adjective(civ);
        text_set_string_arg(1,iVar9);
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x626f38, ((u8 *)&g.d_00626f38)));
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
        goto LAB_0045fd59;
      }
      unit_stack_unlink(unit,1);
      city3 = city4;
      pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ2 * 0x594);
      *pcVar1 = *pcVar1 - 1;
      units[unit].owner = (i8)civ;
      units[unit].visibility = '\0';
      pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
      *pcVar1 = *pcVar1 + 1;
      unit_stack_link(unit,(int)cities[city4].x,(int)cities[city4].y,1);
      units[unit].home_city = -1;
      local_320 = (char)unit_types[units[unit].type].cost * 3;
      iVar11 = civ_has_advance(civ,(int)unit_types[units[unit].type].prerequisite);
      if (iVar11 != 0) {
        local_320 = local_320 / 2;
      }
      city_window_refresh_if_city((FrameWindow *)&city_window,city3);
      map_redraw_tile_all_views((int)cities[city3].x,(int)cities[city3].y);
      city_window_refresh_if_city((FrameWindow *)&city_window,city);
      map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
      civ_adjust_attitude(civ,civ2,-local_320);
      iVar9 = civ_get_adjective(civ);
      text_set_string_arg(1,iVar9);
      diplo_leader_play_reaction(2);
      popup_game(ADDR(0x626f44, ((u8 *)&g.d_00626f44)));
      city = civ_has_advance(civ,(int)unit_types[units[unit].type].prerequisite);
      if (city == 0) {
        advance = unit_types[units[unit].type].prerequisite;
        advance2 = -1;
        for (local_330 = 0; local_330 < 100; local_330++) {
          city = civ_has_advance(civ,local_330);
          if ((city == 0) && (city = advance_has_prereq((int)advance,local_330), city != 0)) {
            advance2 = local_330;
            break;
          }
        }
        if (0 < advance2) {
          uVar12 = _rand();
          uVar13 = (int)uVar12 >> 0x1f;
          if (((uVar12 ^ uVar13) - uVar13 & 1 ^ uVar13) == uVar13) {
            iVar9 = civ_get_adjective(civ);
            text_set_string_arg(1,iVar9);
            popup_game(ADDR(0x626f4c, ((u8 *)&g.d_00626f4c)));
            civ_give_advance(civ,advance2,civ2,0,0);
          }
        }
      }
    }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0045fd43 */ { dialog_dtor((Dialog *)((iptr)&local_318)); }
  }
LAB_0045fd59:
  return;
}
#undef diplo_cur_attitude
#undef diplo_gifts_this_meeting
#undef local_338
#undef city2
#undef local_330
#undef local_32c
#undef advance2
#undef local_320
#undef local_318
#undef local_24
#undef local_20
#undef local_1c
#undef city4
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0045fd67 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __cdecl diplo_ai_senate_hawks_notice(iptr civ,iptr civ2)

{
  iptr iVar1;
  int iVar2;
  
  if ((4 < civs[civ].government) &&
     ((((game.game_flags & 0x80) == 0 || ((scenario_flags & 1) == 0)) && (autoplay_active == 0)))) {
    iVar1 = civ_name_plural(civ2);
    text_set_string_arg(1,iVar1);
    iVar2 = civ_has_wonder(civ,0x18);
    if (iVar2 == 0) {
      popup_game(ADDR(0x626f68, ((u8 *)&g.d_00626f68)));
    }
    else {
      popup_game(ADDR(0x626f5c, ((u8 *)&g.d_00626f5c)));
    }
  }
  return;
}
#undef autoplay_active
#undef scenario_flags

/* 0045fe19 auto */
#define local_310 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl diplo_proposal_menu(iptr civ2,iptr civ)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_310 = 0;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  diplo_set_attitude_arg(civ2,civ);
  dialog_load_game_text(&local_304,ADDR(0x626f78, ((u8 *)&g.d_00626f78)));
  iVar3 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x626f84, ((u8 *)&g.d_00626f84)));
  if (iVar3 == 0) {
    text_read_line(1);
    dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
    bVar2 = false;
    bVar1 = false;
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
      if ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) {
        bVar1 = true;
      }
    }
    else {
      bVar2 = true;
    }
    text_read_line(1);
    if (bVar1) {
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),1,0);
    }
    text_read_line(1);
    if ((!bVar1) && (!bVar2)) {
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),2,0);
    }
    text_read_line(1);
    if (bVar2) {
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),3,0);
    }
    text_read_line(1);
    if ((!bVar2) && (civs[civ2].government < 5)) {
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),4,0);
    }
    text_read_line(1);
    if ((bVar1) && ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x40) == 0)) {
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),5,0);
    }
    text_read_line(1);
    if (bVar2) {
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),6,0);
    }
    text_read_line(1);
    dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),7,0);
    text_read_line(1);
    dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),8,0);
    local_310 = dlg_show_modal(&local_304,0);
  }
  text_close_file();
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00460104 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  return local_310;
}
#undef local_310
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00460129 auto */
#define diplo_ai_declare_war (*(int *)((u8 *)&g.d_0064b0e8))
#define diplo_ai_fear_level (*(int *)((u8 *)&g.d_0064b0ec))
#define diplo_ai_outranks_target (*(int *)((u8 *)&g.d_0064b12c))
#define diplo_attitude_civ (*(iptr *)((u8 *)&g.d_0064b110))
#define diplo_attitude_target (*(iptr *)((u8 *)&g.d_0064b120))
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
#define diplo_emissary_asked (*(int *)((u8 *)&g.d_00626a30))
#define diplo_emissary_response (*(uint *)((u8 *)&g.d_00626a34))
#define diplo_gifts_this_meeting (*(i32 *)((u8 *)&g.d_0064b0f0))
#define diplo_had_ceasefire (*(uint *)((u8 *)&g.d_0064b138))
#define diplo_initial_eval_done (*(i32 *)((u8 *)&g.d_00626a1c))
#define diplo_opening_eval_active (*(i32 *)((u8 *)&g.d_00626a20))
#define diplo_strongest_enemy (*(int *)((u8 *)&g.d_0064b0fc))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define _DAT_00626a28 (*(i32 *)((u8 *)&g.d_00626a28))
#define local_7c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_6c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(72)))
#define local_34 (*(uint *)(frame_ + FRAME_OFF(76)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(108)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(112)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(116)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
diplo_ai_meet_player(iptr civ2,iptr civ,i32 param_3,i32 param_4,int param_5)

{
  char *pcVar1;
  uint *puVar2;
  char cVar3;
  byte bVar4;
  char cVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  iptr iVar14;
  i32 uVar15;
  uint uVar16;
  iptr iVar16;
  iptr iVar17;
  int advance2;
  uint uVar19;
  bool bVar20;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar9 = false;
  bVar12 = false;
  bVar8 = false;
  bVar6 = false;
  bVar11 = false;
  bVar13 = false;
  local_34 = 0;
  bVar7 = false;
  bVar10 = false;
  bVar14 = false;
  _DAT_00626a28 = 1;
  if ((scenario_events_loaded != 0) &&
     (iVar14 = events_check_negotiation((ScenarioEvents *)&scenario_events,civ2,civ),
     iVar14 == 0)) {
    _DAT_00626a28 = 0;
    return;
  }
  diplo_attitude_target = civ2;
  diplo_attitude_civ = civ;
  diplo_gifts_this_meeting = 0;
  if (param_5 == 0) {
    civs[civ].field_1f = '\0';
  }
  diplo_initial_eval_done = 0;
  diplo_opening_eval_active = 1;
  diplo_eval_ai_stance(civ2,civ);
  diplo_initial_eval_done = 1;
  diplo_opening_eval_active = 0;
  diplo_had_ceasefire = (uint)((*(byte *)&civs[civ].treaties[civ2] & 2) != 0);
  bVar20 = (*(byte *)&civs[civ].treaties[civ2] & 1) == 0;
  if (param_5 == 0) {
    civs[civ2].last_treaty_turn[civ] = game.turn;
    diplo_clear_treaty_flags(civ,civ2,0x40002);
  }
  else {
    if (civs[civ].field_1f < '\0') {
      civs[civ].field_1f = '\0';
    }
    if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 8) != 0) {
      uVar15 = diplo_patience_limit(civ2,civ);
      civs[civ].field_1f = (i8)uVar15;
    }
    if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 4) & 1) == 0) {
      if ((((3 < game.difficulty) && (advance2 = civ_spaceship_launched(civ), advance2 != 0)) &&
          (advance2 = civ_spaceship_launched(civ2), advance2 != 0)) &&
         ((civs[civ2].spaceship_arrival_year < civs[civ].spaceship_arrival_year &&
          ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0)))) {
        diplo_set_treaty_flags(civ,civ2,0x200000);
      }
    }
    else {
      civs[civ].field_1f = '\0';
      diplo_clear_treaty_flags(civ,civ2,0x200000);
    }
  }
  diplo_emissary_response = (uint)(param_5 != 0);
  if (param_5 != 0) {
    if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 4) & 0x20) != 0) {
      if (diplo_emissary_asked == 0) {
        diplo_set_attitude_arg(civ2,civ);
      }
      diplo_leader_play_reaction(4);
      popup_game(ADDR(0x626f94, ((u8 *)&g.d_00626f94)));
      bVar12 = true;
      goto LAB_00463d3b;
    }
    cVar3 = civs[civ].field_1f;
    advance2 = diplo_patience_limit(civ2,civ);
    if ((advance2 <= cVar3) && ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 4) & 0x80) != 0)) {
      if (diplo_emissary_asked == 0) {
        diplo_set_attitude_arg(civ2,civ);
      }
      if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x626fb0, ((u8 *)&g.d_00626fb0)));
      }
      else {
        diplo_leader_play_reaction(3);
        popup_game_with_sprite(ADDR(0x626fa0, ((u8 *)&g.d_00626fa0)),(iptr)(&diplo_popup_portrait_sprite +
                                          ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0
                          );
      }
      bVar12 = true;
      goto LAB_00463d3b;
    }
    diplo_ask_receive_emissary(civ2,civ,param_3,param_4);
  }
  diplo_set_treaty_flags(civ2,civ,0x800000);
  bVar14 = true;
  local_34 = (uint)((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 4) & 0x40) != 0);
  diplo_clear_treaty_flags(civ,civ2,0x400000);
  if (((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) {
    if (((civ == 3) && (civ2 == 6)) || ((civ == 6 && (civ2 == 3)))) {
      diplo_war_target_civ = 0;
      diplo_offer_tech_best = -1;
      diplo_tribute_demand = 0;
      local_34 = 0;
    }
    if (((civ == 3) && (civ2 == 1)) || ((civ == 1 && (civ2 == 3)))) {
      diplo_offer_tech_best = -1;
      diplo_war_target_civ = 0;
      local_34 = 0;
    }
  }
  diplo_tech_exchange(civ2,civ,param_3,param_4,1,0);
  if ((((diplo_ai_aggressive == 0) && (param_5 == 0)) &&
      ((*(byte *)&civs[civ].treaties[civ2] & 6) != 0)) && (2 < diplo_ai_fear_level))
  goto LAB_00463d3b;
  diplo_set_attitude_arg(civ2,civ);
  if (((0 < diplo_war_target_civ) && (diplo_war_target_civ < 8)) &&
     ((1 << ((byte)diplo_war_target_civ & 0x1f) & (uint)game.civs_alive) == 0)) {
    diplo_war_target_civ = -1;
  }
  if ((((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) && (diplo_space_race_threat != 0)) &&
     (diplo_ai_outranks_target != 0)) {
    diplo_war_target_civ = -1;
  }
  if ((0 < diplo_war_target_civ) &&
     (((diplo_ai_request_mode != 0 || ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0)) &&
      (advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0)))) {
    local_38 = 2;
    if ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 4) != 0) {
      local_38 = 1;
    }
    if ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 8) != 0) {
      local_38 = 0;
    }
    iVar17 = civ_name_plural(diplo_war_target_civ);
    text_set_string_arg(1,iVar17);
    if (diplo_ai_aggressive == 0) {
      local_14 = 0x6d;
    }
    else {
      local_14 = 0x6c;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      local_14 = 0x6e;
    }
    text_set_label_arg(2,*(i32 *)(label_string_ids + local_14 * 4));
    text_clear();
    text_append(ADDR(0x626fbc, ((u8 *)&g.d_00626fbc)));
    text_append_int(local_38);
    advance2 = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (advance2 == 0) {
      if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
        civ_adjust_attitude(civ,civ2,5);
      }
      else {
        if (diplo_ai_request_mode != 0) {
          civ_adjust_attitude(civ,civ2,0x14);
        }
        bVar6 = true;
      }
      civs[civ].field_1f++;
    }
    else {
      diplo_declare_war(civ2,diplo_war_target_civ,civ);
      bVar9 = true;
      diplo_ai_aggressive = 0;
      diplo_strongest_enemy = -1;
      diplo_war_target_civ = -1;
      if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
        uVar16 = _rand();
        uVar19 = (int)uVar16 >> 0x1f;
        if ((((uVar16 ^ uVar19) - uVar19 & 1 ^ uVar19) != uVar19) &&
           (diplo_tribute_demand = 0, diplo_had_ceasefire != 0)) {
          diplo_set_treaty_flags(civ,civ2,2);
        }
      }
      else {
        diplo_tribute_demand = 0;
        bVar8 = true;
      }
    }
    diplo_set_attitude_arg(civ2,civ);
  }
  if ((*(byte *)&civs[civ2].treaties[civ] & 8) != 0) {
    if ((4 < (int)((uint)civs[civ2].reputation -
                  (int)civs[civ].field_48[civ2])) && (!bVar8)) {
      bVar6 = true;
    }
    if (-1 < diplo_offer_tech_best) {
      if (game.power_rank[civ] < game.power_rank[civ2]) {
        if ((civs[civ].num_advances < civs[civ2].num_advances) ||
           (civs[civ2].gold < civs[civ].gold)) {
          diplo_tribute_demand = 0;
        }
      }
      else if ((civs[civ].num_advances < civs[civ2].num_advances) &&
              (civs[civ2].gold < civs[civ].gold)) {
        diplo_tribute_demand = 0;
      }
    }
    if ((diplo_space_race_threat != 0) && (diplo_ai_outranks_target != 0)) {
      bVar6 = true;
      diplo_tribute_demand = 0;
    }
    if (((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) && (civ == 6)
        ) && (civ2 == 7)) {
      diplo_tribute_demand = 0;
      diplo_offer_tech_best = -1;
      bVar6 = true;
    }
  }
  advance2 = civ_has_advance(civ2,0x35);
  if ((advance2 == 0) && (advance2 = civ_has_advance(civ2,0), advance2 == 0)) {
    advance2 = civ_has_advance(civ2,0x11);
    if ((advance2 == 0) && (advance2 = civ_has_advance(civ2,0x51), advance2 == 0)) {
      advance2 = civ_has_advance(civ2,0x23);
      if ((advance2 != 0) && (advance2 = civ_has_advance(civ,0x23), advance2 == 0)) {
        bVar7 = true;
      }
    }
    else {
      advance2 = civ_has_advance(civ,0x11);
      if ((advance2 == 0) && (advance2 = civ_has_advance(civ,0x51), advance2 == 0)) {
        bVar7 = true;
      }
    }
  }
  else {
    advance2 = civ_has_advance(civ,0x35);
    if ((advance2 == 0) && (advance2 = civ_has_advance(civ,0), advance2 == 0)) {
      bVar7 = true;
    }
  }
  if ((civs[civ2].num_advances <= civs[civ].num_advances) &&
     (advance2 = civ_has_advance(civ,0x11), advance2 != 0)) {
    bVar7 = false;
  }
  if (((0 < diplo_tribute_demand) &&
      (((diplo_ai_request_mode == 2 || (bVar6)) && (diplo_tribute_demand <= civs[civ2].gold)))) &&
     (advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0)) {
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      advance2 = civs[civ2].gold / 2;
      if (advance2 < 0x65) {
        advance2 = 100;
      }
      if (advance2 <= diplo_tribute_demand) {
        diplo_tribute_demand = advance2;
      }
    }
    iVar17 = civ_leader_name(civ);
    text_set_string_arg(1,iVar17);
    iVar17 = civ_leader_title(civ);
    text_set_string_arg(2,iVar17);
    iVar17 = civ_get_adjective(civ);
    text_set_string_arg(3,iVar17);
    text_set_label_arg(4,*(i32 *)
                          (label_string_ids + 0x1a8 +
                          (uint)(leaders[civs[civ].tribe].female == '\0') * -4));
    text_set_number_arg(0,diplo_tribute_demand);
    text_clear();
    diplo_leader_play_reaction(4);
    text_append(ADDR(0x626fcc, ((u8 *)&g.d_00626fcc)));
    local_14 = rand_range(0,3);
    if ((local_14 == 3) && (civs[civ].military_strength < civs[civ2].military_strength)) {
      local_14 = 2;
    }
    if ((local_14 == 2) && (game.first_discoverer[0x26] == '\0')) {
      local_14 = 1;
    }
    if (bVar7) {
      local_14 = 8;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      local_14 = 9;
    }
    text_append_int(local_14);
    if (local_14 == 9) {
      local_70 = popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)(&diplo_popup_portrait_sprite +
                                                   ((game.advance_known_by[0xf] != '\0') - 1 &
                                                   0xffff7c80)),0);
    }
    else {
      local_70 = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    if (local_70 == 1) {
      civs[civ2].gold -= diplo_tribute_demand;
      civs[civ].gold += diplo_tribute_demand;
      diplo_ai_aggressive = 0;
      bVar8 = true;
      status_redraw(1);
      if (civs[civ].field_1f != '\0') {
        civs[civ].field_1f--;
      }
      advance2 = diplo_gold_attitude_value(diplo_tribute_demand);
      civ_adjust_attitude(civ,civ2,-advance2);
      diplo_set_attitude_arg(civ2,civ);
      if (diplo_had_ceasefire != 0) {
        diplo_set_treaty_flags(civ,civ2,2);
      }
    }
    diplo_tribute_demand = 999;
  }
  if (((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) &&
     (advance2 = diplo_attitude_level(diplo_cur_attitude), 3 < advance2)) {
    bVar6 = true;
  }
  if ((((diplo_ai_request_mode != 0) || (bVar6)) && (-1 < diplo_offer_tech_best)) &&
     ((diplo_tribute_demand != 999 &&
      (advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0)))) {
    text_set_label_arg(1,advances[diplo_offer_tech_best].name);
    iVar17 = civ_leader_name(civ);
    text_set_string_arg(3,iVar17);
    iVar17 = civ_leader_title(civ);
    text_set_string_arg(2,iVar17);
    text_set_label_arg(4,*(i32 *)
                          (label_string_ids + 0x1a8 +
                          (uint)(leaders[civs[civ].tribe].female == '\0') * -4));
    text_clear();
    text_append(ADDR(0x626fd4, ((u8 *)&g.d_00626fd4)));
    local_14 = rand_range(0,2);
    if ((bVar7) && (local_14 < 2)) {
      local_14 = 8;
    }
    if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      local_14 = 9;
    }
    text_append_int(local_14);
    if (local_14 == 9) {
      local_70 = popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)(&diplo_popup_portrait_sprite +
                                                   ((game.advance_known_by[0xf] != '\0') - 1 &
                                                   0xffff7c80)),0);
    }
    else {
      local_70 = popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    if (local_70 == 1) {
      civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
      advance2 = ai_advance_value(civ,diplo_offer_tech_best);
      civ_adjust_attitude(civ,civ2,-((advance2 * 3) / 2));
      advance2 = diplo_offer_tech_2nd;
      diplo_offer_tech_best = diplo_offer_tech_2nd;
      diplo_offer_tech_2nd = -1;
      if (((diplo_ai_units_near_cities == 0) || (diplo_ai_aggressive == 0)) || (advance2 < 0)) {
        bVar8 = true;
      }
      else {
        text_set_label_arg(1,advances[advance2].name);
        diplo_leader_play_reaction(4);
        advance2 = popup_game(ADDR(0x626fdc, ((u8 *)&g.d_00626fdc)));
        if (advance2 == 1) {
          civ_give_advance(civ,diplo_offer_tech_best,civ2,0,0);
          advance2 = ai_advance_value(civ,diplo_offer_tech_best);
          civ_adjust_attitude(civ,civ2,-((advance2 * 3) / 2));
          diplo_offer_tech_best = -1;
          bVar8 = true;
        }
      }
      if (bVar8) {
        diplo_ai_aggressive = 0;
        if (diplo_had_ceasefire != 0) {
          diplo_set_treaty_flags(civ,civ2,2);
        }
        if (civs[civ].field_1f != '\0') {
          civs[civ].field_1f--;
        }
      }
    }
    else if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
      civ_adjust_attitude(civ,civ2,
                         (civs[civ2].reputation + 2) -
                         (int)civs[civ].field_48[civ2]);
      civs[civ].field_1f++;
    }
    diplo_set_attitude_arg(civ2,civ);
    diplo_tribute_demand = 999;
  }
  if (((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) &&
     ((((diplo_ai_aggressive != 0 || (0x31 < diplo_cur_attitude)) || ((diplo_space_race_threat != 0 && (diplo_ai_outranks_target != 0)))
       ) && (!bVar8)))) {
    diplo_ask_receive_emissary(civ2,civ,param_3,param_4);
    if (diplo_emissary_asked == 0) {
      diplo_set_attitude_arg(civ2,civ);
    }
    diplo_leader_play_reaction(4);
    if (diplo_tribute_demand == 999) {
      popup_game_with_sprite(ADDR(0x626fe8, ((u8 *)&g.d_00626fe8)),(iptr)(&diplo_popup_portrait_sprite +
                                        ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
    }
    else {
      popup_game_with_sprite(ADDR(0x626ff0, ((u8 *)&g.d_00626ff0)),(iptr)(&diplo_popup_portrait_sprite +
                                        ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
    }
    diplo_cancel_alliance(civ,civ2);
    civs[civ2].last_treaty_turn[civ] = game.turn;
    if ((diplo_space_race_threat != 0) && (3 < game.difficulty)) {
      diplo_ai_declare_war = 1;
    }
    goto LAB_00463d3b;
  }
  if ((local_34 == 0) || (diplo_ai_aggressive == 0)) {
    local_34 = 0;
  }
  else {
    local_34 = 1;
  }
  if (local_34 != 0) {
    diplo_ai_aggressive = 0;
  }
  if ((((((bVar20) && (!bVar8)) && (diplo_tribute_demand == 999)) &&
       ((diplo_ai_aggressive == 0 &&
        (advance2 = diplo_attitude_level(diplo_cur_attitude),
        (int)((-(uint)(diplo_ai_initial_aggressive == 0) & 2) + 2) < advance2)))) &&
      (advance2 = civ_has_wonder(civ2,6), advance2 == 0)) &&
     (advance2 = civ_has_wonder(civ2,0x18), advance2 == 0)) {
    uVar16 = _rand();
    uVar19 = (int)uVar16 >> 0x1f;
    if ((int)(uint)civs[civ].government <
        (int)(6 - (((uVar16 ^ uVar19) - uVar19 & 1 ^ uVar19) - uVar19))) {
      diplo_ai_aggressive = 1;
    }
  }
  if (((diplo_ai_aggressive != 0) && (0x32 < diplo_tribute_demand)) &&
     (((*(byte *)&civs[civ].treaties[civ2] & 4) != 0 ||
      (((advance2 = diplo_is_hostile(civ,civ2), advance2 == 0 && (0 < diplo_last_treaty_turn)) &&
       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 4) & 1) == 0)))))) {
    diplo_ask_receive_emissary(civ2,civ,param_3,param_4);
    if (diplo_emissary_asked == 0) {
      diplo_set_attitude_arg(civ2,civ);
    }
    text_clear();
    diplo_leader_play_reaction(4);
    text_append(ADDR(0x626ff8, ((u8 *)&g.d_00626ff8)));
    iVar17 = rand_range(0,2);
    text_append_int(iVar17);
    diplo_set_treaty_flags(civ,civ2,0x2000);
    advance2 = civ_get_attitude(civ,civ2);
    if (advance2 < 0x4b) {
      civ_set_attitude(civ,civ2,0x4b);
    }
    popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
    civs[civ2].last_treaty_turn[civ] = game.turn;
    goto LAB_00463d3b;
  }
  if ((diplo_ai_aggressive != 0) && (diplo_tribute_demand == 999)) {
    if (diplo_emissary_asked == 0) {
      diplo_set_attitude_arg(civ2,civ);
    }
    diplo_leader_play_reaction(4);
    diplo_set_treaty_flags(civ,civ2,0x2000);
    advance2 = civ_get_attitude(civ,civ2);
    if (advance2 < 0x4b) {
      civ_set_attitude(civ,civ2,0x4b);
    }
    popup_game_with_sprite(ADDR(0x627000, ((u8 *)&g.d_00627000)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
    civs[civ2].last_treaty_turn[civ] = game.turn;
    goto LAB_00463d3b;
  }
  if ((diplo_ai_aggressive != 0) &&
     (((diplo_last_treaty_turn < 0 || ((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 4) & 1) != 0)) ||
      (param_5 != 0)))) {
    diplo_ask_receive_emissary(civ2,civ,param_3,param_4);
    if (diplo_emissary_asked == 0) {
      diplo_set_attitude_arg(civ2,civ);
    }
    diplo_leader_play_reaction(4);
    diplo_set_treaty_flags(civ,civ2,0x2000);
    advance2 = civ_get_attitude(civ,civ2);
    if (advance2 < 0x4b) {
      civ_set_attitude(civ,civ2,0x4b);
    }
    popup_game_with_sprite(ADDR(0x627008, ((u8 *)&g.d_00627008)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
    civs[civ2].last_treaty_turn[civ] = game.turn;
    goto LAB_00463d3b;
  }
  if (diplo_ai_aggressive != 0) goto LAB_00463d3b;
  if (((diplo_suppressed_aggression != 0) && ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) &&
     (advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0)) {
    diplo_leader_play_reaction(4);
    advance2 = civ_has_wonder(civ2,6);
    if (advance2 == 0) {
      popup_game(ADDR(0x627020, ((u8 *)&g.d_00627020)));
    }
    else {
      popup_game(ADDR(0x627010, ((u8 *)&g.d_00627010)));
    }
  }
  if ((((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) &&
      ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) && (diplo_target_is_leader == 0)) {
    local_44 = 0;
    for (local_6c = 1; local_6c < 8; local_6c++) {
      if ((*(byte *)&civs[civ2].treaties[local_6c] & 8) != 0) {
        local_44++;
      }
    }
    if ((game.power_rank[civ2] < 6) && (game.power_rank[civ] < 6)) {
      bVar6 = true;
    }
    else {
      bVar6 = false;
    }
    if (((bVar6) && (diplo_war_target_civ < 1)) && (200 < game.turn)) {
      bVar4 = 8;
      for (local_6c = 1; local_6c < 8; local_6c++) {
        if (((((civ != local_6c) && (civ2 != local_6c)) &&
             ((game.power_rank[civ] <= game.power_rank[local_6c] &&
              ((game.power_rank[civ2] <= game.power_rank[local_6c] &&
               (game.power_rank[local_6c] <= bVar4)))))) &&
            ((*(byte *)&civs[civ2].treaties[local_6c] & 1) != 0)) &&
           (((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_6c * 4) & 0x20) == 0 &&
            ((civs[civ].treaties[local_6c] & 0x2008) == 0)))) {
          diplo_war_target_civ = local_6c;
          bVar4 = game.power_rank[local_6c];
        }
      }
    }
    if ((diplo_war_target_civ < 1) ||
       ((*(byte *)&civs[civ2].treaties[diplo_war_target_civ] & 0xe) == 0)) {
      bVar7 = false;
    }
    else {
      bVar7 = true;
    }
    if (((((((diplo_ai_fear_level != 0) || (bVar6)) || (bVar7)) && ((1 < diplo_peace_inclination || (bVar6)))) &&
         ((local_44 == 0 && ((diplo_cur_attitude < 0x19 || ((diplo_cur_attitude < 0x32 && (bVar7)))))))) &&
        ((bVar7 || ((bVar9 || (bVar6)))))) &&
       (((((int)((uint)civs[civ2].reputation -
                (int)civs[civ].field_48[civ2]) < 4 &&
          (((*(byte *)&civs[civ].treaties[civ2] & 2) == 0 && (diplo_captured_city_count < 2))))
         && ((game.power_rank[civ2] < 6 || (game.power_rank[civ] < 5)))) &&
        ((advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0 &&
         (advance2 = popup_game_with_sprite(ADDR(0x62702c, ((u8 *)&g.d_0062702c)),(iptr)(&diplo_popup_portrait_sprite +
                                                     ((game.advance_known_by[0xf] != '\0') - 1 &
                                                     0xffff7c80)),0), advance2 == 0)))))) {
      bVar6 = true;
      if (-1 < diplo_war_target_civ) {
        bVar6 = false;
        iVar17 = civ_name_plural(diplo_war_target_civ);
        text_set_string_arg(4,iVar17);
        diplo_leader_play_reaction(3);
        advance2 = popup_game(ADDR(0x62703c, ((u8 *)&g.d_0062703c)));
        if (advance2 == 1) {
          diplo_declare_war(civ2,diplo_war_target_civ,civ);
          puVar2 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + diplo_war_target_civ * 4);
          *puVar2 = *puVar2 | 0x80800;
          diplo_war_target_civ = -1;
          bVar6 = true;
        }
        else {
          civ_adjust_attitude(civ,civ2,10);
          diplo_set_attitude_arg(civ2,civ);
          if (((diplo_ai_fear_level == 0) ||
              (2 < (int)((uint)civs[civ2].reputation -
                        (int)civs[civ].field_48[civ2]))) ||
             (0x19 < diplo_cur_attitude)) {
            bVar6 = false;
            diplo_leader_play_reaction(4);
            popup_game(ADDR(0x627050, ((u8 *)&g.d_00627050)));
          }
        }
      }
      if (bVar6) {
        diplo_form_alliance(civ2,civ);
        diplo_set_attitude_arg(civ2,civ);
      }
      bVar11 = true;
    }
  }
  if (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) &&
     (advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0)) {
    iVar17 = civ_name_plural(civ);
    text_set_string_arg(1,iVar17);
    if (bVar8) {
      local_70 = popup_game_with_sprite(ADDR(0x627064, ((u8 *)&g.d_00627064)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
    }
    else if ((diplo_suppressed_aggression == 0) && (local_34 == 0)) {
      iVar17 = civ_get_adjective(civ);
      text_set_string_arg(1,iVar17);
      local_70 = popup_game_with_sprite(ADDR(0x62707c, ((u8 *)&g.d_0062707c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
    }
    else {
      local_70 = popup_game_with_sprite(ADDR(0x627070, ((u8 *)&g.d_00627070)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
    }
    if (local_70 != 0) {
      advance2 = civ_has_wonder(civ,6);
      if ((advance2 == 0) && (advance2 = civ_has_wonder(civ,0x18), advance2 == 0)) {
        advance2 = diplo_senate_intervenes(civ2,civ);
        if (advance2 == 0) {
          diplo_ai_senate_hawks_notice(civ2,civ);
        }
        else {
          popup_game_with_sprite(ADDR(0x6270a8, ((u8 *)&g.d_006270a8)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          local_70 = 0;
          bVar10 = true;
        }
      }
      else {
        iVar17 = civ_name_plural(civ);
        text_set_string_arg(1,iVar17);
        advance2 = civ_has_wonder(civ,6);
        if (advance2 == 0) {
          popup_game_with_sprite(ADDR(0x62709c, ((u8 *)&g.d_0062709c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x62708c, ((u8 *)&g.d_0062708c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
        }
        local_70 = 0;
        bVar10 = true;
      }
    }
    local_50 = ((uint)civs[civ2].reputation -
               (int)civs[civ].field_48[civ2]) + 1;
    if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) {
      local_50 = local_50 * 2;
    }
    if (local_70 != 0) {
      if (local_50 == 1 || local_50 - 1 < 0) {
        local_78 = 0;
      }
      else {
        local_78 = _rand();
        local_78 = local_78 % local_50;
      }
      if (local_78 == 0) {
        if (((local_70 != 0) && (3 < diplo_ai_fear_level)) && (-1 < diplo_wanted_tech)) {
          text_set_label_arg(1,advances[diplo_wanted_tech].name);
          diplo_leader_play_reaction(4);
          advance2 = popup_game_with_sprite(ADDR(0x6270b8, ((u8 *)&g.d_006270b8)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          if (advance2 != 0) {
            local_70 = 0;
            civ_give_advance(civ2,diplo_wanted_tech,civ,0,0);
            bVar13 = true;
          }
        }
        if (local_70 != 0) {
          local_14 = int_clamp(diplo_ai_fear_level * 2 - 4,0,civs[civ].gold / 0x32);
          local_14 = local_14 * 0x32;
          advance2 = civ_has_wonder(civ,6);
          if ((advance2 != 0) || (advance2 = civ_has_wonder(civ,0x18), advance2 != 0)) {
            local_14 = local_14 / 2;
          }
          if (local_14 != 0) {
            text_set_number_arg(0,local_14);
            diplo_leader_play_reaction(4);
            advance2 = popup_game_with_sprite(ADDR(0x6270c0, ((u8 *)&g.d_006270c0)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
            if (advance2 != 0) {
              civs[civ].gold -= local_14;
              civs[civ2].gold += local_14;
              local_70 = 0;
              status_redraw(1);
              bVar13 = true;
            }
          }
        }
        if (((local_70 != 0) && (diplo_ai_fear_level != 0)) &&
           ((civs[civ].num_cities < 2 &&
            ((advance2 = civ_has_wonder(civ,6), advance2 == 0 &&
             (advance2 = civ_has_wonder(civ,0x18), advance2 == 0)))))) {
          text_set_number_arg_v(0,civs[civ].gold);
          diplo_leader_play_reaction(4);
          advance2 = popup_game_with_sprite(ADDR(0x6270cc, ((u8 *)&g.d_006270cc)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          if (advance2 != 0) {
            local_70 = 0;
            civs[civ2].gold += civs[civ].gold;
            civs[civ].gold = 0;
            status_redraw(1);
            bVar13 = true;
            for (advance = 0; advance < 100; advance++) {
              advance2 = civ_has_advance(civ,advance);
              if (((advance2 != 0) && (advance2 = civ_has_advance(civ2,advance), advance2 == 0)) &&
                 ((advances[advance].preq[0] != -2 || (advances[advance].preq[1] != -2)))) {
                civ_give_advance(civ2,advance,civ,0,0);
              }
            }
          }
        }
        if (local_70 == 0) {
          diplo_last_treaty_turn = (int)game.turn;
        }
      }
    }
    if (local_70 != 0) {
      diplo_leader_play_reaction(4);
      popup_game(ADDR(0x6270e0, ((u8 *)&g.d_006270e0)));
      civs[civ2].last_treaty_turn[civ] = game.turn;
      goto LAB_00463d3b;
    }
    bVar11 = true;
    diplo_agree_ceasefire(civ2,civ);
    diplo_set_attitude_arg(civ2,civ);
    if (6 < (int)((uint)civs[civ2].reputation -
                 (int)civs[civ].field_48[civ2])) {
      diplo_leader_play_reaction(4);
      popup_game(ADDR(0x6270d4, ((u8 *)&g.d_006270d4)));
    }
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
    local_10 = 3;
    if ((uint)civs[civ2].military_strength * 2 < (uint)civs[civ].military_strength) {
      local_10 = 2;
    }
    if (((uint)civs[civ2].military_strength * 3) / 2 < (uint)civs[civ].military_strength) {
      local_10--;
    }
    if (civs[civ].military_strength < civs[civ2].military_strength) {
      local_10++;
    }
    if ((uint)civs[civ].military_strength * 2 < (uint)civs[civ2].military_strength) {
      local_10++;
    }
    if ((((diplo_suppressed_aggression != 0) ||
         (((bVar8 || (bVar20)) && ((*(byte *)&civs[civ].treaties[civ2] & 2) == 0)))
         ) || ((((diplo_ai_fear_level != 0 ||
                 (advance2 = diplo_attitude_level(diplo_cur_attitude), advance2 <= local_10)) &&
                (diplo_target_is_leader == 0)) &&
               ((int)(((uint)civs[civ2].reputation -
                      (int)civs[civ].field_48[civ2]) + diplo_captured_city_count) <
                diplo_ai_fear_level + 4)))) &&
       (advance2 = diplo_ask_receive_emissary(civ2,civ,param_3,param_4), advance2 != 0)) {
      iVar17 = civ_name_plural(civ);
      text_set_string_arg(1,iVar17);
      local_70 = popup_game_with_sprite(ADDR(0x6270ec, ((u8 *)&g.d_006270ec)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
      if (local_70 != 0) {
        advance2 = civ_has_wonder(civ,6);
        if ((advance2 == 0) && (advance2 = civ_has_wonder(civ,0x18), advance2 == 0)) {
LAB_00462bb9:
          advance2 = diplo_senate_intervenes(civ2,civ);
          if (advance2 == 0) {
LAB_00462c12:
            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x40) == 0) {
              diplo_ai_senate_hawks_notice(civ2,civ);
            }
          }
          else {
            if (bVar10) {
              uVar16 = _rand();
              uVar19 = (int)uVar16 >> 0x1f;
              if (((uVar16 ^ uVar19) - uVar19 & 1 ^ uVar19) == uVar19) goto LAB_00462c12;
            }
            popup_game_with_sprite(ADDR(0x627118, ((u8 *)&g.d_00627118)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
            local_70 = 0;
          }
        }
        else {
          if (bVar10) {
            uVar16 = _rand();
            uVar19 = (int)uVar16 >> 0x1f;
            if (((uVar16 ^ uVar19) - uVar19 & 1 ^ uVar19) == uVar19) goto LAB_00462bb9;
          }
          advance2 = civ_has_wonder(civ,6);
          if (advance2 == 0) {
            popup_game_with_sprite(ADDR(0x62710c, ((u8 *)&g.d_0062710c)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x6270fc, ((u8 *)&g.d_006270fc)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
          }
          local_70 = 0;
        }
      }
      if (local_70 != 0) {
        local_50 = ((uint)civs[civ2].reputation -
                   (int)civs[civ].field_48[civ2]) + 1;
        if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) {
          local_50 = local_50 * 2;
        }
        if (local_50 == 1 || local_50 - 1 < 0) {
          local_7c = 0;
        }
        else {
          local_7c = _rand();
          local_7c = local_7c % local_50;
        }
        if (local_7c == 0) {
          local_14 = int_clamp(diplo_ai_fear_level * 2 - 4,0,civs[civ].gold / 0x32);
          local_14 = local_14 * 0x32;
          advance2 = civ_has_wonder(civ,6);
          if ((advance2 != 0) || (advance2 = civ_has_wonder(civ,0x18), advance2 != 0)) {
            local_14 = local_14 / 2;
          }
          if (local_14 != 0) {
            text_set_number_arg(0,local_14);
            advance2 = popup_game_with_sprite(ADDR(0x627128, ((u8 *)&g.d_00627128)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
            if (advance2 != 0) {
              civs[civ].gold -= local_14;
              civs[civ2].gold += local_14;
              local_70 = 0;
              bVar13 = true;
              status_redraw(1);
            }
          }
        }
      }
      bVar11 = true;
      if (local_70 == 0) {
        diplo_sign_peace_treaty(civ2,civ);
        diplo_set_attitude_arg(civ2,civ);
      }
      else {
        diplo_leader_play_reaction(4);
        popup_game(ADDR(0x627138, ((u8 *)&g.d_00627138)));
      }
    }
  }
  if (((diplo_emissary_asked != 0) || (param_5 != 0)) ||
     (((*(byte *)&civs[civ].treaties[civ2] & 4) == 0 &&
      (((diplo_ai_fear_level != 0 || ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0))
       || ((*(byte *)&civs[civ].treaties[civ2] & 1) == 0)))))) {
    if (6 < (int)((uint)civs[civ2].reputation -
                 (int)civs[civ].field_48[civ2])) {
      local_4c = 0;
      for (local_6c = 1; local_6c < 8; local_6c++) {
        if ((*(byte *)&civs[civ].treaties[local_6c] & 8) != 0) {
          local_4c++;
        }
      }
      if (((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) &&
         (((local_4c != 0 || (diplo_target_is_leader != 0)) ||
          (civs[civ2].military_strength < civs[civ].military_strength)))) {
        diplo_ai_declare_war = 1;
      }
    }
    if (bVar20) {
      diplo_ask_receive_emissary(civ2,civ,param_3,param_4);
    }
    if (((diplo_emissary_asked == 0) || (diplo_emissary_response == 0xffffffff)) && (param_5 == 0)) {
      if (diplo_ai_declare_war == 0) {
        advance2 = civ_has_wonder(civ,6);
        if ((advance2 == 0) && (advance2 = civ_has_wonder(civ,0x18), advance2 == 0)) {
          advance2 = diplo_senate_intervenes(civ2,civ);
          if (advance2 == 0) {
            diplo_ai_senate_hawks_notice(civ2,civ);
          }
          else {
            iVar17 = civ_get_adjective(civ);
            text_set_string_arg(1,iVar17);
            if (((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) &&
               (diplo_ai_fear_level != 0)) {
              popup_game_with_sprite(ADDR(0x627178, ((u8 *)&g.d_00627178)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
              diplo_set_treaty_flags(civ,civ2,4);
              civs[civ2].last_treaty_turn[civ] = game.turn + 0x10;
            }
            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) {
              popup_game_with_sprite(ADDR(0x627184, ((u8 *)&g.d_00627184)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
              diplo_set_treaty_flags(civ,civ2,2);
              civs[civ2].last_treaty_turn[civ] = game.turn;
            }
          }
        }
        else {
          iVar17 = civ_name_plural(civ);
          text_set_string_arg(1,iVar17);
          if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
            if (diplo_ai_fear_level != 0) {
              advance2 = civ_has_wonder(civ,6);
              if (advance2 == 0) {
                popup_game_with_sprite(ADDR(0x627150, ((u8 *)&g.d_00627150)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
              }
              else {
                popup_game_with_sprite(ADDR(0x627140, ((u8 *)&g.d_00627140)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
              }
              diplo_set_treaty_flags(civ,civ2,4);
              civs[civ2].last_treaty_turn[civ] = game.turn + 0x10;
            }
            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) {
              advance2 = civ_has_wonder(civ,6);
              if (advance2 == 0) {
                popup_game_with_sprite(ADDR(0x62716c, ((u8 *)&g.d_0062716c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
              }
              else {
                popup_game_with_sprite(ADDR(0x62715c, ((u8 *)&g.d_0062715c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
              }
              diplo_set_treaty_flags(civ,civ2,2);
              civs[civ2].last_treaty_turn[civ] = game.turn;
            }
          }
        }
      }
    }
    else {
      if (diplo_emissary_asked == 0) {
        diplo_set_attitude_arg(civ2,civ);
      }
      if (bVar11) {
        if (((civs[civ].treaties[civ2] & 0x810) == 0) || (param_5 == 0))
        {
          civ3 = -1;
          cVar3 = -1;
          for (local_6c = 1; local_6c < 8; local_6c++) {
            if ((((civ != local_6c) && (civ2 != local_6c)) &&
                ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_6c * 4) & 0x20) == 0)) &&
               (cVar5 = civs[civ2].field_48[local_6c], cVar5 <= cVar3)) {
              civ3 = local_6c;
              cVar3 = cVar5;
            }
          }
          if (-1 < civ3) {
            iVar17 = civ_name_plural(civ3);
            text_set_string_arg(1,iVar17);
            pcVar1 = (char *)(civ3 + ADDR(0x64c6e8, ((u8 *)&civs + 72)) + civ2 * 0x594);
            *pcVar1 = *pcVar1 + 1;
            text_clear();
            text_append(ADDR(0x627214, ((u8 *)&g.d_00627214)));
            if ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) == 0) {
              if (civs[civ2].military_strength < civs[civ].military_strength) {
                diplo_leader_play_reaction(3);
                text_append(ADDR(0x627228, ((u8 *)&g.d_00627228)));
              }
              else {
                diplo_leader_play_reaction(3);
                text_append(ADDR(0x62722c, ((u8 *)&g.d_0062722c)));
              }
            }
            else {
              diplo_leader_play_reaction(4);
              text_append(ADDR(0x627220, ((u8 *)&g.d_00627220)));
            }
            popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
          }
        }
      }
      else if ((diplo_tribute_demand != 999) || (bVar8)) {
        if (param_5 == 0) {
          local_14 = 0x71;
          if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) {
            if (civs[civ].military_strength < civs[civ2].military_strength) {
              local_14 = 0x70;
            }
            advance2 = diplo_attitude_level(diplo_cur_attitude);
            if ((advance2 < 4) &&
               ((int)((uint)civs[civ2].reputation -
                     (int)civs[civ].field_48[civ2]) < 3)) {
              local_14 = 0x70;
            }
            if (diplo_ai_fear_level != 0) {
              local_14 = 0x6f;
            }
          }
          text_set_label_arg(1,*(i32 *)(label_string_ids + local_14 * 4));
          iVar17 = civ_get_adjective(civ2);
          text_set_string_arg(2,iVar17);
          iVar17 = civ_leader_title(civ2);
          text_set_string_arg(3,iVar17);
          iVar17 = civ_leader_name(civ2);
          text_set_string_arg(4,iVar17);
          diplo_leader_play_reaction(2);
          if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
            if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
              popup_game(ADDR(0x62720c, ((u8 *)&g.d_0062720c)));
            }
            else {
              popup_game(ADDR(0x6271fc, ((u8 *)&g.d_006271fc)));
            }
          }
          else {
            popup_game(ADDR(0x6271f0, ((u8 *)&g.d_006271f0)));
          }
        }
        else {
          iVar17 = civ_name_plural(civ2);
          text_set_string_arg(2,iVar17);
          if (civs[civ].field_1f < 2) {
            diplo_leader_play_reaction(2);
            if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
              if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
                popup_game(ADDR(0x6271d4, ((u8 *)&g.d_006271d4)));
              }
              else {
                popup_game(ADDR(0x6271c8, ((u8 *)&g.d_006271c8)));
              }
            }
            else {
              popup_game(ADDR(0x6271bc, ((u8 *)&g.d_006271bc)));
            }
          }
          else {
            diplo_leader_play_reaction(2);
            if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
              diplo_leader_play_reaction(3);
              popup_game(ADDR(0x6271e8, ((u8 *)&g.d_006271e8)));
            }
            else {
              diplo_leader_play_reaction(2);
              popup_game(ADDR(0x6271dc, ((u8 *)&g.d_006271dc)));
            }
          }
        }
      }
      else {
        diplo_leader_play_reaction(4);
        if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
          if ((*(byte *)&civs[civ].treaties[civ2] & 6) == 0) {
            popup_game(ADDR(0x6271b0, ((u8 *)&g.d_006271b0)));
          }
          else {
            popup_game(ADDR(0x6271a0, ((u8 *)&g.d_006271a0)));
          }
        }
        else {
          popup_game(ADDR(0x627190, ((u8 *)&g.d_00627190)));
        }
      }
      if (((*(byte *)&civs[civ].treaties[civ2] & 0xc) == 0) &&
         (diplo_count_border_intruders(civ,civ2), diplo_border_intruder_count != 0)) {
        text_set_string_arg(1,(iptr)&cities[border_intruder_city].name);
        iVar17 = civ_get_adjective(civ);
        text_set_string_arg(2,iVar17);
        if (border_intruder_city < 2) {
          popup_game(ADDR(0x627244, ((u8 *)&g.d_00627244)));
        }
        else {
          popup_game(ADDR(0x627234, ((u8 *)&g.d_00627234)));
        }
      }
      if ((*(byte *)&civs[civ2].treaties[civ] & 8) != 0) {
        local_1c = 0;
        if (0 < diplo_strongest_enemy) {
          for (local_5c = 1; local_5c < 0x3f; local_5c++) {
            if (((1 < civs[civ].num_cities) < civs[civ].continent_cities[local_5c])
               && (civs[civ].continent_military[local_5c] <
                   civs[diplo_strongest_enemy].continent_attack[local_5c])) {
              local_1c++;
            }
          }
        }
        if (local_1c == 0) {
          if (0 < diplo_weakest_enemy_civ) {
            local_1c = 0;
            for (local_5c = 1; local_5c < 0x3f; local_5c++) {
              if (((1 < civs[diplo_weakest_enemy_civ].num_cities) <
                   civs[diplo_weakest_enemy_civ].continent_cities[local_5c]) &&
                 (civs[diplo_weakest_enemy_civ].continent_military[local_5c] <
                  civs[civ].continent_attack[local_5c])) {
                local_1c++;
              }
            }
            if (local_1c != 0) {
              iVar17 = civ_name_plural(diplo_weakest_enemy_civ);
              text_set_string_arg(1,iVar17);
              diplo_leader_play_reaction(3);
              popup_game(ADDR(0x62725c, ((u8 *)&g.d_0062725c)));
            }
          }
        }
        else {
          iVar17 = civ_name_plural(diplo_strongest_enemy);
          text_set_string_arg(1,iVar17);
          diplo_leader_play_reaction(2);
          popup_game(ADDR(0x627250, ((u8 *)&g.d_00627250)));
        }
      }
      do {
        if (civs[civ].field_1f < '\0') {
          civs[civ].field_1f = '\0';
        }
        advance2 = diplo_proposal_menu(civ2,civ);
        if (advance2 == 0) {
          bVar12 = true;
          goto LAB_00463d3b;
        }
        if (advance2 == 7) {
          diplo_favor_menu(civ2,civ);
        }
        else if (advance2 == 8) {
          diplo_gift_menu(civ2,civ);
        }
        else {
          advance2 = diplo_ai_answer_proposal(civ2,civ,advance2);
          if (advance2 != 0) goto LAB_00463d3b;
        }
        civs[civ].field_1f++;
        cVar3 = civs[civ].field_1f;
        advance2 = diplo_patience_limit(civ2,civ);
      } while (cVar3 < advance2);
      diplo_set_attitude_arg(civ2,civ);
      diplo_leader_play_reaction(3);
      if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
        popup_game(ADDR(0x627278, ((u8 *)&g.d_00627278)));
      }
      else {
        popup_game(ADDR(0x627268, ((u8 *)&g.d_00627268)));
      }
    }
  }
LAB_00463d3b:
  diplo_clear_treaty_flags(civ,civ2,0x10000);
  if ((diplo_ai_declare_war == 0) || ((civs[civ2].treaties[civ] & 0x2008) != 0))
  {
    puVar2 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
    *puVar2 = *puVar2 & 0xffffffdf;
  }
  else {
    puVar2 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
    *puVar2 = *puVar2 | 0x20;
  }
  if (!bVar12) {
    civs[civ].field_1f++;
  }
  if ((bVar13) || (local_34 != 0)) {
    while (iVar16 = diplo_patience_limit(civ2,civ),
          (int)civs[civ].field_1f < (int)(local_34 + iVar16)) {
      civs[civ].field_1f++;
    }
  }
  diplo_session_reset();
  if (((diplo_had_ceasefire != 0) && ((*(byte *)&civs[civ].treaties[civ2] & 2) == 0)) &&
     ((civs[civ2].treaties[civ] & 0x200c) == 0)) {
    iVar17 = civ_name_plural(civ);
    text_set_string_arg(1,iVar17);
    popup_game_with_sprite(ADDR(0x627284, ((u8 *)&g.d_00627284)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
  }
  if ((((game.difficulty == '\0') &&
       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0)) &&
      (((*(byte *)&civs[human_civ].treaties[civ] & 0x80) == 0 &&
       ((advance2 = civ_has_wonder(human_civ,0x18), advance2 == 0 &&
        (advance2 = civ_has_wonder(human_civ,9), advance2 == 0)))))) &&
     (advance2 = civ_has_advance(civ,0x58), advance2 != 0)) {
    iVar17 = civ_name_plural(civ);
    text_set_string_arg(1,iVar17);
    dlg_game_txt_with_unit_flags(ADDR(0x627290, ((u8 *)&g.d_00627290)),0x2e,0);
    puVar2 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
    *puVar2 = *puVar2 | 0x80;
    intel_report_show(civ2,civ);
  }
  if (((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (bVar14)) &&
     (((diplo_emissary_asked != 0 || (param_5 != 0)) &&
      ((((diplo_emissary_response != 0xffffffff && (4 < civs[civ].num_cities)) &&
        (game.power_rank[civ2] + 1 < (uint)game.power_rank[civ])) &&
       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0)))))) {
    iVar17 = civ_name_plural(civ);
    text_set_string_arg(0,iVar17);
    popup_text((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62729c, ((u8 *)&g.d_0062729c)));
  }
  _DAT_00626a28 = 0;
  return;
}
#undef diplo_ai_declare_war
#undef diplo_ai_fear_level
#undef diplo_ai_outranks_target
#undef diplo_attitude_civ
#undef diplo_attitude_target
#undef diplo_cur_attitude
#undef diplo_emissary_asked
#undef diplo_emissary_response
#undef diplo_gifts_this_meeting
#undef diplo_had_ceasefire
#undef diplo_initial_eval_done
#undef diplo_opening_eval_active
#undef diplo_strongest_enemy
#undef human_civ
#undef scenario_events_loaded
#undef scenario_flags
#undef _DAT_00626a28
#undef local_7c
#undef local_78
#undef local_70
#undef local_6c
#undef advance
#undef local_5c
#undef local_50
#undef local_4c
#undef local_44
#undef local_38
#undef local_34
#undef local_1c
#undef local_14
#undef local_10
#undef civ3

/* 00467750 auto */
void __cdecl diplo_clear_treaty_flags(iptr param_1,iptr param_2,uint param_3)

{
  uint *puVar1;
  
  if ((param_3 & 4) != 0) {
    diplo_clear_treaty_flags(param_1,param_2,8);
  }
  if ((param_3 & 0x2000) != 0) {
    diplo_clear_treaty_flags(param_1,param_2,0x1800);
  }
  if ((param_3 & 1) != 0) {
    diplo_clear_treaty_flags(param_1,param_2,0x2000);
  }
  puVar1 = (uint *)(param_1 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + param_2 * 4);
  *puVar1 = *puVar1 & ~param_3;
  puVar1 = (uint *)(param_1 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + param_2 * 0x594);
  *puVar1 = *puVar1 & ~param_3;
  return;
}

/* 00467825 auto */
void __cdecl diplo_set_treaty_flags(iptr param_1,iptr param_2,uint param_3)

{
  uint *puVar1;
  
  if ((param_3 & 8) != 0) {
    diplo_set_treaty_flags(param_1,param_2,4);
  }
  if ((param_3 & 0xe) != 0) {
    diplo_clear_treaty_flags(param_1,param_2,0x2a60);
  }
  if ((param_3 & 0x2000) != 0) {
    diplo_clear_treaty_flags(param_1,param_2,0xe);
    param_3 = param_3 | 0x200000;
  }
  puVar1 = (uint *)(param_1 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + param_2 * 4);
  *puVar1 = *puVar1 | param_3;
  puVar1 = (uint *)(param_2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + param_1 * 4);
  *puVar1 = *puVar1 | param_3;
  return;
}

/* 004679ab auto */
i32 __cdecl diplo_attitude_level(int param_1)

{
  i32 uVar1;
  
  if (param_1 < 0) {
    uVar1 = 0;
  }
  else if (param_1 < 0xb) {
    uVar1 = 1;
  }
  else if (param_1 < 0x1a) {
    uVar1 = 2;
  }
  else if (param_1 < 0x27) {
    uVar1 = 3;
  }
  else if (param_1 < 0x3e) {
    uVar1 = 4;
  }
  else if (param_1 < 0x4b) {
    uVar1 = 5;
  }
  else if (param_1 < 0x5a) {
    uVar1 = 6;
  }
  else if (param_1 < 100) {
    uVar1 = 7;
  }
  else {
    uVar1 = 8;
  }
  return uVar1;
}

/* 00467af0 auto */
uint __cdecl diplo_is_hostile(iptr civ,iptr param_2)

{
  uint uVar1;
  int iVar2;
  
  if ((*(byte *)(param_2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) == 0) {
    if ((*(byte *)&civs[civ].treaties[param_2] & 8) == 0) {
      if (((byte)*(i32 *)&civs[civ].treaties[param_2] & 5) == 1) {
        iVar2 = civ_get_attitude(civ,param_2);
        uVar1 = (uint)(0x31 < iVar2);
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 00467baf auto */
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl diplo_expel_units(int civ2,int civ)

{
  int x;
  int y;
  iptr city3;
  iptr iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == civ2)) {
      x = (int)units[unit].x;
      y = (int)units[unit].y;
      city3 = city_find_nearest(x,y,civ2,0xffffffff,civ);
      if ((-1 < city3) && (cities[city3].owner == civ)) {
        iVar4 = tile_landmass(x,y);
        iVar5 = tile_is_ocean(x,y);
        if ((iVar5 != 0) ||
           ((*(char *)&civs[civ].continent_cities[iVar4] != '\0' &&
            (unit_types[units[unit].type].role != 7)))) {
          if (iVar5 == 0) {
            city2 = city_find_nearest(x,y,civ2,0xffffffff,-1);
          }
          else {
            local_8 = 9999;
            city2 = -1;
            for (city = 0; city < game.num_cities; city++) {
              if ((((cities[city].id != 0) && (cities[city].owner == civ2)) &&
                  (iVar5 = city_adjacent_to_body(city,iVar4), iVar5 != 0)) &&
                 (iVar5 = map_distance_diag(x,y,(int)cities[city].x,
                                             (int)cities[city].y), iVar5 < local_8)) {
                city2 = city;
                local_8 = iVar5;
              }
            }
          }
          if ((-1 < city2) && (units[unit].owner == cities[city2].owner)) {
            unit_lift_off_map(unit,0);
            unit_stack_relocate_all(unit,(int)cities[city2].x,(int)cities[city2].y,1);
            if ((moving_units_mode == 1) && (game.active_unit == unit)) {
              map_cursor_x = cities[city2].x;
              map_cursor_y = cities[city2].y;
            }
            units[unit].orders = -1;
          }
        }
      }
    }
  }
  return;
}
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef unit
#undef city2
#undef city
#undef local_8

/* 00467ef2 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl diplo_cancel_alliance(iptr civ,iptr civ2)

{
  iptr iVar1;
  int iVar2;
  
  diplo_clear_treaty_flags(civ,civ2,8);
  diplo_expel_units(civ,civ2);
  diplo_expel_units(civ2,civ);
  map_redraw_all_views(human_civ,1);
  text_clear();
  text_append(ADDR(0x62831c, ((u8 *)&g.d_0062831c)));
  if (((human_civ == civ) || (human_civ == civ2)) && (autoplay_active == 0)) {
    if (human_civ == civ) {
      iVar1 = civ_name_plural(civ2);
      text_set_string_arg(1,iVar1);
      iVar1 = civ_get_adjective(civ2);
      text_set_string_arg(2,iVar1);
    }
    else {
      iVar1 = civ_name_plural(civ);
      text_set_string_arg(1,iVar1);
      iVar1 = civ_get_adjective(civ);
      text_set_string_arg(2,iVar1);
    }
    text_append(ADDR(0x62832c, ((u8 *)&g.d_0062832c)));
    popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)(&diplo_popup_portrait_sprite +
                                      ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
  }
  else {
    if ((((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) == 0) &&
          (iVar2 = civ_has_wonder(human_civ,0x18), iVar2 == 0)) &&
         ((iVar2 = civ_has_wonder(human_civ,9), iVar2 == 0 &&
          (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) == 0 &&
           (iVar2 = civ_has_wonder(human_civ,0x18), iVar2 == 0)))))) &&
        (iVar2 = civ_has_wonder(human_civ,9), iVar2 == 0)) && (game.reveal_map == '\0')) {
      return;
    }
    if (autoplay_active == 0) {
      iVar1 = civ_name_plural(civ);
      text_set_string_arg(1,iVar1);
      iVar1 = civ_name_plural(civ2);
      text_set_string_arg(2,iVar1);
      text_append(ADDR(0x628330, ((u8 *)&g.d_00628330)));
      popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)(&diplo_popup_portrait_sprite +
                                        ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
    }
  }
  return;
}
#undef autoplay_active
#undef human_civ

/* 00493e50 auto */
#define diplo_leader_sound_ids (*(iptr *)((u8 *)&g.d_0062ca48))
#define diplo_leader_wnd_open (*(char *)((u8 *)&g.d_0062ca38))
void __cdecl diplo_greeting_sound_done_cb(void)

{
  if (diplo_leader_wnd_open != '\0') {
    snd_play_effect(diplo_leader_sound_ids,1,1,0);
  }
  return;
}
#undef diplo_leader_sound_ids
#undef diplo_leader_wnd_open

/* 00493e83: written by hand in src/game/unwind.c */

/* 00493f0f auto */
#define diplo_greeting_sound_id (*(int *)((u8 *)&g.d_0062ca44))
#define diplo_leader_sound_ids (*(int *)((u8 *)&g.d_0062ca48))
#define diplo_leader_wnd_open (*(i8 *)((u8 *)&g.d_0062ca38))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_24 (*(DiploLeaderView * *)(frame_ + FRAME_OFF(12)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(40)))
void __cdecl diplo_leader_wnd_launch(iptr param_1,iptr civ)

{
  DiploLeaderWindow *this;
  int iVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  diplo_leader_wnd_open = 0;
  diplo_greeting_sound_id = ((uint)map.seed + civ & 7) + 0x53;
  if (civs[civ].tribe < 1) {
    local_28 = ~(int)civs[civ].tribe + 1;
  }
  else {
    local_28 = (iptr)civs[civ].tribe;
  }
  diplo_leader_sound_ids = (uint)(byte)(&tribe_leader_sound_set)[local_28] * 4 + 0x70;
  for (local_14 = 0; local_14 < 3; local_14++) {
    *(int *)(&diplo_leader_reaction_sound_ids + local_14 * 4) = diplo_leader_sound_ids + local_14 + 1;
  }
  snd_cd_stop();
  if (diplo_leader_window != 0) {
    if (diplo_leader_window != 0) {
      diplo_leader_wnd_scalar_dtor((void *)diplo_leader_window,1);
    }
    diplo_leader_window = 0;
  }
  this = operator_new(0x108c);
  local_8 = 0;
  if (this == (DiploLeaderWindow *)0x0) {
    local_24 = (DiploLeaderView *)0x0;
  }
  else {
    local_24 = (DiploLeaderView *)diplo_leader_wnd_ctor(this);
  }
  local_8 = 0xffffffff;
  diplo_leader_window = (iptr)local_24;
  if (((local_24 != (DiploLeaderView *)0x0) && (((*(i8 *)((char *)&game.game_options + 2)) & 4) != 0)) &&
     (iVar1 = diplo_leader_wnd_init(local_24,param_1,civ), iVar1 != 0)) {
    diplo_leader_wnd_open = 1;
    if (diplo_leader_window == -200) {
      local_2c = 0;
    }
    else {
      local_2c = diplo_leader_window + 0x110;
    }
    dlg_set_parent_window(local_2c);
    dlg_set_palette(diplo_leader_window + 0x224);
    diplo_leader_wnd_show((DiploLeaderWindow *)diplo_leader_window);
  }
  return;
}
#undef diplo_greeting_sound_id
#undef diplo_leader_sound_ids
#undef diplo_leader_wnd_open
#undef local_2c
#undef local_28
#undef local_24
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 00494148 auto */
#define diplo_greeting_sound_id (*(i32 *)((u8 *)&g.d_0062ca44))
#define diplo_leader_sound_ids (*(int *)((u8 *)&g.d_0062ca48))
#define diplo_leader_wnd_open (*(char *)((u8 *)&g.d_0062ca38))
void __cdecl diplo_leader_wnd_close(void)

{
  if (diplo_leader_wnd_open != '\0') {
    diplo_leader_wnd_open = '\0';
    if (diplo_leader_window != 0) {
      diplo_leader_wnd_teardown((WndBase *)diplo_leader_window);
      if (diplo_leader_window != 0) {
        diplo_leader_wnd_scalar_dtor((void *)diplo_leader_window,1);
      }
      diplo_leader_window = 0;
    }
    diplo_greeting_sound_id = 0;
    ui_delay_ticks(0x1e);
    snd_play_effect(-diplo_leader_sound_ids,0,0,0);
    snd_sync_music_option();
  }
  return;
}
#undef diplo_greeting_sound_id
#undef diplo_leader_sound_ids
#undef diplo_leader_wnd_open

/* 004941ee auto */
#define diplo_leader_video_active (*(char *)((u8 *)&g.d_0062ca40))
void __cdecl diplo_leader_play_reaction(int param_1)

{
  if ((((diplo_leader_video_active != '\0') && (diplo_leader_window != 0)) &&
      ((param_1 == 2 || ((param_1 == 3 || (param_1 == 4)))))) &&
     ((*(int *)(&leader_anim_idle_start + (uint)*(byte *)(diplo_leader_window + 0x1084) * 0x28) <
       *(int *)(diplo_leader_window + 0x1074) &&
      (*(int *)(diplo_leader_window + 0x1074) <
       *(int *)(&leader_anim_idle_end + (uint)*(byte *)(diplo_leader_window + 0x1084) * 0x28))))) {
    *(i8 *)(diplo_leader_window + 0x1088) = (i8)param_1;
    diplo_leader_video_end_cb();
  }
  return;
}
#undef diplo_leader_video_active

/* 004942a3 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
DiploLeaderWindow * __thiscall diplo_leader_wnd_ctor(DiploLeaderWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((C_00408010_b8 *)this);
  local_8 = 0;
  surfwnd_ctor((SurfaceWindow *)this->pad_c8);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_ctor((DibSurface *)&this->frame_right);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  palette_init((GamePalette *)(this->pad_1e4 + 0x40));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  dll_handle_init((DllHandle *)(this->pad_638 + 0x20));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  mmwnd_ctor((C_004083b0_a28 *)(this->pad_638 + 0x24));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),5);
  gfx_get_screen_rect((iptr)&this->control_list);
  this->field_1088 = '\0';
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004943c9 auto */
#define diplo_leader_video_active (*(i8 *)((u8 *)&g.d_0062ca40))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall diplo_leader_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  diplo_leader_video_active = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet FUN_0049444f */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x65c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet FUN_0049445e */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x658)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_0049446d */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0x224)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_0049447c */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x1dc)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_0049448b */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 200)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0049449a */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef diplo_leader_video_active
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004944bb auto */
#define diplo_leader_video_active (*(i8 *)((u8 *)&g.d_0062ca40))
#define local_e4 (*(i8 (*)[96])(frame_ + FRAME_OFF(4)))
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(100)))
i32 __thiscall diplo_leader_wnd_init(DiploLeaderView *this,i32 param_1,iptr param_2)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(232)] __attribute__((aligned(8)));  /* original stack frame */
  
  diplo_leader_video_active = 0;
  palette_get_rgb((GamePalette *)&game_palette,(iptr)local_e4,10,0x20);
  palette_set_rgb((GamePalette *)(this->pad_1e0 + 0x44),10,0x20,(iptr)local_e4);
  this->field_1086 = (u8)param_1;
  this->field_1085 = (u8)param_2;
  this->field_1084 = (u8)civs[this->field_1085].tribe;
  str_clear((iptr)local_84);
  str_append((iptr)local_84,ADDR(0x62cab4, ((u8 *)&g.d_0062cab4)));
  iVar1 = file_resolve_path((iptr)local_84);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    dll_handle_load((DllHandle *)(this->pad_1e0 + 0x478),(iptr)local_84);
    uVar2 = civ_city_style_era((uint)this->field_1085);
    this->field_1087 = (u8)uVar2;
    iVar1 = diplo_leader_init_tile(this);
    if (iVar1 == 0) {
      MessageBoxA((HWND)0x0,s_init_tile_failed__0062cac8,s_NOTICE_0062cac0,0x40);
      uVar2 = 0;
    }
    else {
      iVar1 = diplo_leader_init_background(this);
      if (iVar1 == 0) {
        MessageBoxA((HWND)0x0,s_init_background_failed__0062cae4,s_NOTICE_0062cadc,0x40);
        uVar2 = 0;
      }
      else {
        iVar1 = diplo_leader_init_main_art(this);
        if (iVar1 == 0) {
          MessageBoxA((HWND)0x0,s_init_main_art_failed__0062cb04,s_NOTICE_0062cafc,0x40);
          uVar2 = 0;
        }
        else {
          iVar1 = diplo_leader_init_military(this);
          if (iVar1 == 0) {
            MessageBoxA((HWND)0x0,s_init_military_failed__0062cb24,s_NOTICE_0062cb1c,0x40);
            uVar2 = 0;
          }
          else {
            iVar1 = diplo_leader_init_science(this);
            if (iVar1 == 0) {
              MessageBoxA((HWND)0x0,s_init_science_failed__0062cb44,s_NOTICE_0062cb3c,0x40);
              uVar2 = 0;
            }
            else {
              iVar1 = diplo_leader_init_portrait(this);
              if (iVar1 == 0) {
                MessageBoxA((HWND)0x0,s_init_portrait_failed__0062cb64,s_NOTICE_0062cb5c,0x40);
                uVar2 = 0;
              }
              else {
                if (((*(i8 *)((char *)&game.game_options + 2)) & 0x20) != 0) {
                  diplo_leader_video_active = diplo_leader_init_video(this);
                }
                uVar2 = 1;
              }
            }
          }
        }
      }
    }
  }
  return uVar2;
}
#undef diplo_leader_video_active
#undef local_e4
#undef local_84

/* 00494704 auto */
#define diplo_greeting_sound_id (*(iptr *)((u8 *)&g.d_0062ca44))
#define diplo_leader_video_active (*(char *)((u8 *)&g.d_0062ca40))
void __thiscall diplo_leader_wnd_show(DiploLeaderWindow *this)

{
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)(this->pad_1e4 + 0x40));
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->pad_1e4 + 0x40));
  if (diplo_leader_video_active != '\0') {
    window_show((C_004083b0_4 *)(this->pad_638 + 0x24));
  }
  window_show((C_004083b0_4 *)this->pad_c8);
  wnd_flush_paint();
  if (diplo_leader_video_active != '\0') {
    avi_player_play_range
              ((AviPlayerRangeView *)(this->pad_638 + 0x24),
               *(i32 *)(&leader_anim_frame_starts + (uint)this->leader_tribe * 0x28),
               *(i32 *)(&leader_anim_frame_ends + (uint)this->leader_tribe * 0x28));
  }
  dll_handle_free((DllHandle *)(this->pad_638 + 0x20));
  DAT_0062ca3c = 0;
  snd_play_effect(diplo_greeting_sound_id,1,0,ADDR(0x401a91, diplo_greeting_sound_done_cb));
  return;
}
#undef diplo_greeting_sound_id
#undef diplo_leader_video_active

/* 004947f0 auto */
void __thiscall diplo_leader_wnd_teardown(WndBase *this)

{
  wnd_hide(this + 0x11);
  wnd_flush_paint();
  wnd_set_palette(this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_hide(this);
  wnd_flush_paint();
  wnd_destroy_native(this);
  dll_handle_free((DllHandle *)&this[0x65].field_8);
  dlg_set_parent_window(0);
  dlg_set_palette(0);
  wnd_destroy_with_surface((DibSurface *)&this[0xc].field_8);
  wnd_destroy_native(this);
  dialog_set_default_offset(0,0);
  return;
}

/* 0049488e auto */
uint __thiscall diplo_leader_init_tile(DiploLeaderView *this)

{
  int iVar1;
  
  surface_create((DibSurface *)&this->field_1dc,0x40,0x40);
  iVar1 = surface_load_gif_resource((DibSurface *)&this->field_1dc,299,10,0x20,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  return (uint)(iVar1 != 0);
}

/* 004948e6 auto */
i32 __thiscall diplo_leader_init_background(DiploLeaderView *this)

{
  wnd_create_with_handlers
            ((WndBase *)this,ADDR(0x62cb7c, ((u8 *)&g.d_0062cb7c)),0x800,0,0,this->field_c0,this->field_c4 + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),
             ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  wnd_set_bg_tile(this,(iptr)&this->field_1dc);
  return 1;
}

/* 00494949 auto */
#define local_4d0 (*(i8 (*)[120])(frame_ + FRAME_OFF(0)))
#define local_458 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_454 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_450 (*(i32 *)(frame_ + FRAME_OFF(128)))
#define local_44c (*(GamePalette *)(frame_ + FRAME_OFF(132)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(1208)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(1212)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1216)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1220)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1224)))
uint __thiscall diplo_leader_init_main_art(DiploLeaderView *this)

{
  int iVar1;
  iptr iVar2;
  i32 *puVar3;
  i32 *puVar4;
  i32 *puVar5;
  i8 frame_[FRAME_OFF(1232)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_44c);
  local_8 = 0;
  local_454 = (int)(this->field_c0 - 0x280) / 3;
  local_458 = (int)(this->field_c4 - 0x1e0) / 3;
  wnd_create_with_surface
            ((DibSurface *)this->pad_c8,ADDR(0x62cb80, ((u8 *)&g.d_0062cb80)),0x800,local_454,local_458,0x280,0x1e0,
             (iptr)(this->pad_1e0 + 0x44),(iptr)this);
  iVar1 = surface_load_gif_resource
                    ((DibSurface *)this->pad_c8,civs[this->field_1085].government + 200,10,0xec,
                     (iptr)&local_44c);
  if (iVar1 != 0) {
    puVar5 = &local_14;
    puVar4 = &local_450;
    puVar3 = &local_18;
    iVar2 = civ_color_primary((uint)this->field_1085);
    palette_get_entry
              ((GamePalette *)&game_palette,iVar2,(iptr)puVar3,(iptr)puVar4,(iptr)puVar5);
    palette_set_entry(&local_44c,0x91,local_18,local_450,local_14);
    palette_get_rgb(&local_44c,(iptr)local_4d0,0x6a,0x28);
    palette_set_rgb((GamePalette *)(this->pad_1e0 + 0x44),0x6a,0x28,(iptr)local_4d0)
    ;
    surface_set_palette((DibSurface *)this->pad_c8,(iptr)(this->pad_1e0 + 0x44));
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00494b3a */ { palette_destroy((GamePalette *)((iptr)&local_44c)); }
  }
  else {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00494b3a */ { palette_destroy((GamePalette *)((iptr)&local_44c)); }
  }
  return (uint)(iVar1 != 0);
}
#undef local_4d0
#undef local_458
#undef local_454
#undef local_450
#undef local_44c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00494b5f auto */
#define local_4f4 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_4e4 (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_4e0 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_4dc (*(int *)(frame_ + FRAME_OFF(28)))
#define local_4d8 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_4d4 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_4d0 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_4cc (*(int *)(frame_ + FRAME_OFF(44)))
#define local_4c8 (*(Sprite *)(frame_ + FRAME_OFF(48)))
#define local_48c (*(DibSurface *)(frame_ + FRAME_OFF(108)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(180)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1256)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1260)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1264)))
i32 __thiscall diplo_leader_init_military(DiploLeaderView *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1272)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  sprite_init(&local_4c8);
  local_8 = 0;
  palette_init(&local_444);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_ctor(&local_48c);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  local_4dc = game.power_rank[this->field_1085] - 1;
  if (local_4dc == 0) {
    local_4e0 = 1;
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_00494d71 */ { surface_dtor((DibSurface *)((iptr)&local_48c)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00494d7d */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00494d89 */ { sprite_destroy((Sprite *)((iptr)&local_4c8)); }
  }
  else {
    iVar1 = surface_load_gif_resource(&local_48c,0xd7,10,0xec,(iptr)&local_444);
    if (iVar1 == 0) {
      local_4e4 = 0;
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet FUN_00494d71 */ { surface_dtor((DibSurface *)((iptr)&local_48c)); }
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_00494d7d */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00494d89 */ { sprite_destroy((Sprite *)((iptr)&local_4c8)); }
      local_4e0 = local_4e4;
    }
    else {
      local_4cc = (uint)this->field_1087 * 0x6d + 1;
      local_4d4 = 0x9c;
      sprite_grab_from_surface(&local_4c8,(iptr)&local_48c,9,local_4cc,0x9c,0x6c,0x1e);
      local_4cc = 0x2d;
      local_4d4 = 0x82;
      local_4d8 = 0x1f;
      for (local_4d0 = 0; local_4d0 < local_4dc; local_4d0++) {
        sprite_draw
                  (&local_4c8,(iptr)local_4f4,(iptr)this->pad_c8,local_4cc,local_4d4);
        local_4d4 += local_4d8;
      }
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet FUN_00494d71 */ { surface_dtor((DibSurface *)((iptr)&local_48c)); }
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_00494d7d */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00494d89 */ { sprite_destroy((Sprite *)((iptr)&local_4c8)); }
      local_4e0 = 1;
    }
  }
  return local_4e0;
}
#undef local_4f4
#undef local_4e4
#undef local_4e0
#undef local_4dc
#undef local_4d8
#undef local_4d4
#undef local_4d0
#undef local_4cc
#undef local_4c8
#undef local_48c
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00494e2a auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_7d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_7c0 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_7bc (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_7b8 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_7b4 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_7b0 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_7ac (*(CHAR (*)[252])(frame_ + FRAME_OFF(36)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(288)))
#define local_6ac (*(int *)(frame_ + FRAME_OFF(292)))
#define local_6a8 (*(int *)(frame_ + FRAME_OFF(296)))
#define local_6a4 (*(int *)(frame_ + FRAME_OFF(300)))
#define local_6a0 (*(int *)(frame_ + FRAME_OFF(304)))
#define local_69c (*(int *)(frame_ + FRAME_OFF(308)))
#define local_698 (*(int *)(frame_ + FRAME_OFF(312)))
#define local_694 (*(tagRECT *)(frame_ + FRAME_OFF(316)))
#define local_684 (*(int *)(frame_ + FRAME_OFF(332)))
#define local_680 (*(GameFont *)(frame_ + FRAME_OFF(336)))
#define local_678 (*(i32 *)(frame_ + FRAME_OFF(344)))
#define local_674 (*(CHAR (*)[51])(frame_ + FRAME_OFF(348)))
#define local_60c (*(char *)(frame_ + FRAME_OFF(452)))
#define local_608 (*(int *)(frame_ + FRAME_OFF(456)))
#define local_604 (*(Sprite (*)[4])(frame_ + FRAME_OFF(460)))
#define local_514 (*(Sprite *)(frame_ + FRAME_OFF(700)))
#define local_4d8 (*(DibSurface *)(frame_ + FRAME_OFF(760)))
#define local_490 (*(int (*)[13])(frame_ + FRAME_OFF(832)))
#define local_45c (*(GamePalette *)(frame_ + FRAME_OFF(884)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(1960)))
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(1964)))
#define local_14 (*(i8 *)(frame_ + FRAME_OFF(1980)))
#define local_13 (*(i8 *)(frame_ + FRAME_OFF(1981)))
#define local_12 (*(i8 *)(frame_ + FRAME_OFF(1982)))
#define local_11 (*(i8 *)(frame_ + FRAME_OFF(1983)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1984)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1988)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1992)))
i32 __thiscall diplo_leader_init_science(DiploLeaderView *this)

{
  int iVar1;
  iptr iVar2;
  int iVar3;
  CHAR aCStack_641 [53];
  i8 frame_[FRAME_OFF(2000)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  font_init(&local_680,0,0xb);
  local_8 = 0;
  FUN_005f2620(local_604,0x3c,5,sprite_init,sprite_destroy);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  palette_init(&local_45c);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  surface_ctor(&local_4d8);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),3);
  local_14 = 0x13;
  local_13 = 0x62;
  local_12 = 0x13;
  local_11 = 0x25;
  local_490[0] = -1;
  local_490[1] = -1;
  local_490[2] = 0xffffffff;
  local_490[3] = 0xffffffff;
  local_490[4] = 0xffffffff;
  local_490[5] = 0xffffffff;
  local_490[6] = 0xffffffff;
  local_490[7] = 0xffffffff;
  local_490[8] = 0xffffffff;
  local_490[9] = 0xffffffff;
  local_490[10] = 0xffffffff;
  local_490[0xb] = 0xffffffff;
  local_6ac = 0;
  if (((((*(byte *)&civs[human_civ].treaties[((uint)this->field_1085)] & 0x80) == 0) &&
       (iVar1 = civ_has_wonder(human_civ,0x18), iVar1 == 0)) &&
      (iVar1 = civ_has_wonder(human_civ,9), iVar1 == 0)) && (game.difficulty != '\0')) {
    local_490[0xc] = 0;
  }
  else {
    local_490[0xc] = 1;
  }
  for (advance = 0; advance < 100; advance++) {
    iVar1 = civ_has_advance((uint)this->field_1085,advance);
    if (iVar1 != 0) {
      local_6ac++;
      if (*(int *)(&tech_prereq_depth_cache + advance * 4) < 1) {
        tech_prereq_walk_count = 0;
        advance_count_prereq_depth(advance);
        tech_prereq_walk_count++;
        *(int *)(&tech_prereq_depth_cache + advance * 4) = tech_prereq_walk_count;
        local_608 = tech_prereq_walk_count;
      }
      else {
        local_608 = *(int *)(&tech_prereq_depth_cache + advance * 4);
      }
      if (local_490[1] < local_608) {
        local_490[0] = advance;
        local_490[1] = local_608;
        for (local_684 = 1; local_684 < 6; local_684++) {
          local_7b4 = local_490[local_684 * 2];
          local_7b8 = local_490[local_684 * 2 + 1];
          local_6a0 = local_684 - 1;
          while ((-1 < local_6a0 && (local_7b8 < local_490[local_6a0 * 2 + 1]))) {
            local_490[local_6a0 * 2 + 2] = local_490[local_6a0 * 2];
            local_490[local_6a0 * 2 + 3] = local_490[local_6a0 * 2 + 1];
            local_6a0--;
          }
          local_490[local_6a0 * 2 + 2] = local_7b4;
          local_490[local_6a0 * 2 + 3] = local_7b8;
        }
      }
    }
  }
  if (6 < local_6ac) {
    local_6ac = 6;
  }
  if (local_6ac == 0) {
    local_7bc = 1;
    (*(i8 *)((char *)&local_8 + 0)) = 2;
    /* inlined unwind funclet FUN_00495be2 */ { surface_dtor((DibSurface *)((iptr)&local_4d8)); }
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_00495bee */ { palette_destroy((GamePalette *)((iptr)&local_45c)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00495bfa */ { FUN_005f2490((iptr)&local_604,0x3c,5,sprite_destroy); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00495c10 */ { font_destroy((GameFont *)((iptr)&local_680)); }
  }
  else {
    iVar1 = surface_load_gif_resource(&local_4d8,0xd7,10,0xec,(iptr)&local_45c);
    if (iVar1 == 0) {
      local_7c0 = 0;
      (*(i8 *)((char *)&local_8 + 0)) = 2;
      /* inlined unwind funclet FUN_00495be2 */ { surface_dtor((DibSurface *)((iptr)&local_4d8)); }
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet FUN_00495bee */ { palette_destroy((GamePalette *)((iptr)&local_45c)); }
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_00495bfa */ { FUN_005f2490((iptr)&local_604,0x3c,5,sprite_destroy); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00495c10 */ { font_destroy((GameFont *)((iptr)&local_680)); }
      local_7bc = local_7c0;
    }
    else {
      surface_set_palette(&local_4d8,(iptr)(this->pad_1e0 + 0x44));
      local_678 = (uint)this->field_1087 * 0x6d + 1;
      local_69c = 1;
      sprite_grab_from_surface(local_604 + 3,(iptr)&local_4d8,9,local_678,1,0x6c,0x1e);
      local_69c += 0x1f;
      sprite_grab_from_surface(local_604,(iptr)&local_4d8,9,local_678,local_69c,0x6c,0x1e);
      local_69c += 0x1f;
      sprite_grab_from_surface(local_604 + 1,(iptr)&local_4d8,9,local_678,local_69c,0x6c,0x1e);
      local_69c += 0x1f;
      sprite_grab_from_surface(local_604 + 2,(iptr)&local_4d8,9,local_678,local_69c,0x6c,0x1e);
      local_69c += 0x1f;
      sprite_grab_from_surface(&local_514,(iptr)&local_4d8,9,local_678,local_69c,0x6c,0x1e);
      local_6a4 = 0x1f;
      local_678 = 0x1e5;
      local_69c = 0x82;
      SetRect(&local_24,0,0,0x3a,0x14);
      OffsetRect(&local_24,0x213,0x89);
      local_28 = local_24.right - local_24.left;
      for (local_6a8 = 5; -1 < local_6a8; local_6a8--) {
        advance = local_490[local_6a8 * 2];
        if (-1 < advance) {
          local_698 = (int)(char)advances[advance].category;
          sprite_draw
                    (local_604 + local_698,(iptr)local_7d0,(iptr)this->pad_c8,local_678,local_69c);
          for (local_684 = 0; local_684 < 5; local_684++) {
            str_clear((iptr)(local_7ac + local_684 * 0x32));
          }
          iVar2 = label_string(advances[advance].name);
          str_append((iptr)local_7ac,iVar2);
          CharUpperA(local_7ac);
          local_6a0 = 0;
          do {
            local_60c = '\0';
            while ((local_7ac[(int)local_60c + local_6a0 * 0x32] != '\0' &&
                   (local_7ac[(int)local_60c + local_6a0 * 0x32] != ' '))) {
              local_60c++;
            }
            if (local_7ac[(int)local_60c + local_6a0 * 0x32] != '\0') {
              local_7ac[(int)local_60c + local_6a0 * 0x32] = '\0';
              str_append((iptr)(local_7ac + (local_6a0 * 5 + 5) * 10),
                                 (iptr)(local_7ac + (int)local_60c + local_6a0 * 0x32 + 1));
            }
            local_6a0++;
          } while (local_60c != '\0');
          str_clear((iptr)(aCStack_641 + 1));
          for (local_684 = 0; (local_684 < 5 && (local_7ac[local_684 * 0x32] != '\0'));
              local_684 = local_684 + 1) {
            str_append((iptr)(aCStack_641 + 1),(iptr)(local_7ac + local_684 * 0x32));
            str_append((iptr)(aCStack_641 + 1),ADDR(0x62cb84, ((u8 *)&g.d_0062cb84)));
            iVar1 = font_text_width(&local_680,(iptr)(aCStack_641 + 1));
            if (local_28 < iVar1) break;
          }
          if ((local_7ac[local_684 * 0x32] == '\0') || (local_6a0 == 2)) {
            if (local_6a0 == 2) {
              local_7b0 = 0;
              iVar1 = lstrlenA(aCStack_641 + 1);
              local_60c = (char)iVar1;
              while ((local_60c != '\0' &&
                     (iVar1 = font_text_width(&local_680,(iptr)(aCStack_641 + 1)),
                     local_28 < iVar1))) {
                aCStack_641[local_60c + 1] = '\0';
                local_60c--;
                local_7b0 = 1;
              }
              if (local_7b0 != 0) {
                aCStack_641[local_60c] = '\0';
                str_append((iptr)(aCStack_641 + 1),ADDR(0x62cb88, ((u8 *)&g.d_0062cb88)));
              }
            }
            CopyRect(&local_694,&local_24);
            if (local_490[0xc] != 0) {
              gfx_set_text_color_index(10);
              surface_draw_text_in_rect
                        ((DibSurface *)this->pad_c8,(iptr)&local_680,(iptr)(aCStack_641 + 1),
                         (iptr)&local_694,0);
              OffsetRect(&local_694,-1,-1);
              gfx_set_text_color_index(*(i32 *)(&local_14 + this->field_1087));
              surface_draw_text_in_rect
                        ((DibSurface *)this->pad_c8,(iptr)&local_680,(iptr)(aCStack_641 + 1),
                         (iptr)&local_694,0);
            }
          }
          else {
            str_clear((iptr)(aCStack_641 + 1));
            if (local_684 == 0) {
              str_append((iptr)(aCStack_641 + 1),(iptr)local_7ac);
              local_6a0 = 1;
              iVar1 = lstrlenA(local_674);
              local_7b0 = 0;
              local_60c = (char)iVar1;
              while ((local_60c != '\0' &&
                     (iVar1 = font_text_width(&local_680,(iptr)(aCStack_641 + 1)),
                     local_28 < iVar1))) {
                aCStack_641[local_60c + 1] = '\0';
                local_60c--;
                local_7b0 = 1;
              }
              if (local_7b0 != 0) {
                aCStack_641[local_60c] = '\0';
                str_append((iptr)(aCStack_641 + 1),ADDR(0x62cb8c, ((u8 *)&g.d_0062cb8c)));
              }
            }
            else {
              for (local_6a0 = 0; local_6a0 < local_684; local_6a0++) {
                str_append((iptr)(aCStack_641 + 1),(iptr)(local_7ac + local_6a0 * 0x32));
              }
            }
            if (local_490[0xc] != 0) {
              CopyRect(&local_694,&local_24);
              iVar3 = local_24.bottom - local_24.top;
              iVar1 = font_cached_height(&local_680);
              OffsetRect(&local_694,0,((iVar3 >> 1) - iVar1) + 1);
              gfx_set_text_color_index(10);
              surface_draw_text_in_rect
                        ((DibSurface *)this->pad_c8,(iptr)&local_680,(iptr)(aCStack_641 + 1),
                         (iptr)&local_694,1);
              OffsetRect(&local_694,-1,-1);
              gfx_set_text_color_index(*(i32 *)(&local_14 + this->field_1087));
              surface_draw_text_in_rect
                        ((DibSurface *)this->pad_c8,(iptr)&local_680,(iptr)(aCStack_641 + 1),
                         (iptr)&local_694,1);
            }
            str_clear((iptr)local_674);
            for (; local_6a0 < 5; local_6a0++) {
              str_append((iptr)local_674,(iptr)(local_7ac + local_6a0 * 0x32));
            }
            iVar1 = lstrlenA(local_674);
            local_7b0 = 0;
            local_60c = (char)iVar1;
            while ((local_60c != '\0' &&
                   (iVar1 = font_text_width(&local_680,(iptr)local_674),
                   local_28 < iVar1))) {
              local_674[local_60c] = '\0';
              local_60c--;
              local_7b0 = 1;
            }
            if (local_7b0 != 0) {
              local_674[local_60c - 1] = '\0';
              str_append((iptr)local_674,ADDR(0x62cb90, ((u8 *)&g.d_0062cb90)));
            }
            if (local_490[0xc] != 0) {
              iVar1 = font_cached_height(&local_680);
              OffsetRect(&local_694,0,iVar1 - 3);
              gfx_set_text_color_index(10);
              surface_draw_text_in_rect
                        ((DibSurface *)this->pad_c8,(iptr)&local_680,(iptr)local_674,
                         (iptr)&local_694,1);
              OffsetRect(&local_694,-1,-1);
              gfx_set_text_color_index(*(i32 *)(&local_14 + this->field_1087));
              surface_draw_text_in_rect
                        ((DibSurface *)this->pad_c8,(iptr)&local_680,(iptr)local_674,
                         (iptr)&local_694,1);
            }
          }
          OffsetRect(&local_24,0,local_6a4);
          local_69c += local_6a4;
        }
      }
      (*(i8 *)((char *)&local_8 + 0)) = 2;
      /* inlined unwind funclet FUN_00495be2 */ { surface_dtor((DibSurface *)((iptr)&local_4d8)); }
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet FUN_00495bee */ { palette_destroy((GamePalette *)((iptr)&local_45c)); }
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_00495bfa */ { FUN_005f2490((iptr)&local_604,0x3c,5,sprite_destroy); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00495c10 */ { font_destroy((GameFont *)((iptr)&local_680)); }
      local_7bc = 1;
    }
  }
  return local_7bc;
}
#undef human_civ
#undef local_7d0
#undef local_7c0
#undef local_7bc
#undef local_7b8
#undef local_7b4
#undef local_7b0
#undef local_7ac
#undef advance
#undef local_6ac
#undef local_6a8
#undef local_6a4
#undef local_6a0
#undef local_69c
#undef local_698
#undef local_694
#undef local_684
#undef local_680
#undef local_678
#undef local_674
#undef local_60c
#undef local_608
#undef local_604
#undef local_514
#undef local_4d8
#undef local_490
#undef local_45c
#undef local_28
#undef local_24
#undef local_14
#undef local_13
#undef local_12
#undef local_11
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00495c35 auto */
#define local_59c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_58c (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_588 (*(i8 (*)[192])(frame_ + FRAME_OFF(24)))
#define local_4c8 (*(Sprite *)(frame_ + FRAME_OFF(216)))
#define local_48c (*(DibSurface *)(frame_ + FRAME_OFF(276)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(348)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1424)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1428)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1432)))
i32 __thiscall diplo_leader_init_portrait(DiploLeaderView *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1440)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  sprite_init(&local_4c8);
  local_8 = 0;
  palette_init(&local_444);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_ctor(&local_48c);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  iVar1 = surface_load_gif_resource
                    (&local_48c,civs[this->field_1085].leader_portrait + 0xdc,10,0xec,
                     (iptr)&local_444);
  if (iVar1 == 0) {
    local_58c = 0;
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_00495dcf */ { surface_dtor((DibSurface *)((iptr)&local_48c)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00495ddb */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00495de7 */ { sprite_destroy((Sprite *)((iptr)&local_4c8)); }
  }
  else {
    palette_get_rgb(&local_444,(iptr)local_588,0x2a,0x40);
    palette_set_rgb((GamePalette *)(this->pad_1e0 + 0x44),0x2a,0x40,(iptr)local_588)
    ;
    surface_set_palette(&local_48c,(iptr)(this->pad_1e0 + 0x44));
    sprite_grab_from_surface(&local_4c8,(iptr)&local_48c,9,1,1,0xe1,0x113);
    sprite_draw(&local_4c8,(iptr)local_59c,(iptr)this->pad_c8,0xd0,0x39);
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_00495dcf */ { surface_dtor((DibSurface *)((iptr)&local_48c)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00495ddb */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00495de7 */ { sprite_destroy((Sprite *)((iptr)&local_4c8)); }
    local_58c = 1;
  }
  return local_58c;
}
#undef local_59c
#undef local_58c
#undef local_588
#undef local_4c8
#undef local_48c
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00495e0c auto */
#define local_608 (*(i8 (*)[7])(frame_ + FRAME_OFF(0)))
#define local_601 (*(i8 *)(frame_ + FRAME_OFF(7)))
#define local_5f4 (*(i8 (*)[300])(frame_ + FRAME_OFF(20)))
#define local_4c8 (*(i8 (*)[128])(frame_ + FRAME_OFF(320)))
#define local_448 (*(GamePalette *)(frame_ + FRAME_OFF(448)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1524)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1528)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1532)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1536)))
i8 __thiscall diplo_leader_init_video(DiploLeaderView *this)

{
  i8 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(1544)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_448);
  local_8 = 0;
  this->field_1084 = (u8)civs[this->field_1085].tribe;
  str_clear((iptr)local_4c8);
  str_append((iptr)local_4c8,ADDR(0x62cb94, ((u8 *)&g.d_0062cb94)));
  str_clear((iptr)local_608);
  str_append((iptr)local_608,ADDR(0x62cba0, ((u8 *)&g.d_0062cba0)));
  str_append((iptr)local_608,(iptr)(&leader_video_tribe_codes)[civs[this->field_1085].tribe]);
  local_601 = 0;
  str_append((iptr)local_4c8,(iptr)local_608);
  str_append((iptr)local_4c8,ADDR(0x62cba8, ((u8 *)&g.d_0062cba8)));
  iVar2 = file_resolve_path((iptr)local_4c8);
  if (iVar2 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00496100 */ { palette_destroy((GamePalette *)((iptr)&local_448)); }
    uVar1 = 0;
  }
  else {
    avi_player_create_child
              ((C_004083b0_61c *)(this->pad_1e0 + 0x47c),ADDR(0x62cbb0, ((u8 *)&g.d_0062cbb0)),0x200,
               *(i32 *)(&leader_video_x_table + (uint)this->field_1084 * 8),
               *(i32 *)(&leader_video_y_table + (uint)this->field_1084 * 8),(iptr)this->pad_c8);
    local_14 = avi_player_open((AviPlayerOpenView *)(this->pad_1e0 + 0x47c),(iptr)local_4c8);
    if (local_14 == 0) {
      avi_player_set_end_callback((AviPlayerEndCbSetView *)(this->pad_1e0 + 0x47c),ADDR(0x402441, diplo_leader_video_end_cb));
      avi_player_set_transparent((C_005dd761 *)(this->pad_1e0 + 0x47c),1);
      palette_load_ctab_res(&local_448,this->field_1084 + 1000);
      palette_get_rgb(&local_448,(iptr)local_5f4,0x92,100);
      palette_set_rgb
                ((GamePalette *)(this->pad_1e0 + 0x44),0x92,100,(iptr)local_5f4);
      avi_player_set_palette
                ((DibSurface *)(this->pad_1e0 + 0x47c),(iptr)(this->pad_1e0 + 0x44));
      wnd_set_palette
                ((WndBase *)(this->pad_1e0 + 0x4c4),(iptr)(this->pad_1e0 + 0x44));
      avi_player_show_frame(this->pad_1e0 + 0x47c,0);
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00496100 */ { palette_destroy((GamePalette *)((iptr)&local_448)); }
      uVar1 = 1;
    }
    else {
      if (local_14 == -0x7ffbfeac) {
        popup_game(ADDR(0x62cbb4, ((u8 *)&g.d_0062cbb4)));
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00496100 */ { palette_destroy((GamePalette *)((iptr)&local_448)); }
      uVar1 = 0;
    }
  }
  return uVar1;
}
#undef local_608
#undef local_601
#undef local_5f4
#undef local_4c8
#undef local_448
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00496125 auto */
#define diplo_leader_sound_ids (*(i32 *)((u8 *)&g.d_0062ca48))
#define diplo_leader_video_active (*(char *)((u8 *)&g.d_0062ca40))
void __cdecl diplo_leader_video_end_cb(void)

{
  uptr uVar2;
  iptr iVar1;
  
  iVar1 = diplo_leader_window;
  if (diplo_leader_video_active != '\0') {
    if (*(char *)(diplo_leader_window + 0x1088) == '\0') {
      avi_player_loop_range
                ((AviPlayerLoopView *)(diplo_leader_window + 0x65c),
                 *(i32 *)(&leader_anim_idle_start + (uint)*(byte *)(diplo_leader_window + 0x1084) * 0x28),
                 *(i32 *)(&leader_anim_idle_end + (uint)*(byte *)(diplo_leader_window + 0x1084) * 0x28));
    }
    else {
      uVar2 = (uptr)*(byte *)(diplo_leader_window + 0x1088);
      *(i8 *)(diplo_leader_window + 0x1088) = 0;
      avi_player_play_range
                ((AviPlayerRangeView *)(iVar1 + 0x65c),
                 *(i32 *)(&leader_anim_frame_starts + (uint)*(byte *)(iVar1 + 0x1084) * 0x28 + uVar2 * 8)
                 ,*(i32 *)
                   (&leader_anim_frame_ends + (uint)*(byte *)(iVar1 + 0x1084) * 0x28 + uVar2 * 8));
      snd_play_effect((&diplo_leader_sound_ids)[uVar2],1,0,0);
    }
  }
  return;
}
#undef diplo_leader_sound_ids
#undef diplo_leader_video_active

/* 00497bf0 auto */
void * __thiscall diplo_leader_wnd_scalar_dtor(void *this,uint param_1)

{
  diplo_leader_wnd_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004b75fb auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl diplo_wnd_escape_close(i32 param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = wnd_get_active_child();
  if (local_8 == 0) {
    local_8 = 0;
  }
  else {
    local_8 -= 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  diplo_wnd_close_active();
  return;
}
#undef local_8

/* 004b76d5 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define mp_meeting_pending (*(i32 *)((u8 *)&g.d_00626a2c))
#define nm_parley_cancel_count (*(int *)((u8 *)&g.d_006c91e4))
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define local_8 (*(i8 * *)(frame_ + FRAME_OFF(0)))
i32 __cdecl diplo_wnd_close_active(void)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (i8 *)0x0;
  }
  else {
    local_8 = (i8 *)(iVar1 - 0x48);
  }
  if ((local_8 == &parley_wnd) && (parley_wnd_closed == 0)) {
    if (parley_received_offer != (void *)0x0) {
      operator_delete(parley_received_offer);
      parley_received_offer = (void *)0x0;
    }
    if (((parley_other_civ == -1) || (nm_parley_cancel_count != 0)) || (nm_parley_accept_offer_count != 0)) {
      if (((parley_other_civ != -1) && (nm_parley_cancel_count != 0)) && (nm_parley_accept_offer_count == 0)) {
        nm_parley_cancel_count = 0;
        iVar2 = civ_name_plural(parley_other_civ);
        text_set_string_arg(0,iVar2);
        dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
        popup_game_with_sprite(ADDR(0x62d924, ((u8 *)&g.d_0062d924)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
    }
    else {
      net_send_message(0x81,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),0
                         ,0,0,0,0,0,0,0);
    }
    mp_meeting_pending = 0;
  }
  *(i32 *)(local_8 + 0x114) = 1;
  *(i32 *)(local_8 + 0x118) = 0xffffffff;
  wnd_hide((WndBase *)(local_8 + 0x48));
  wnd_focus_and_raise((WndBase *)&main_frame_wnd);
  ui_flush_input();
  return 1;
}
#undef dlg_pending_idle_callback
#undef mp_meeting_pending
#undef nm_parley_cancel_count
#undef parley_other_civ
#undef local_8

/* 004c59f0 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __cdecl diplo_espionage_incident(iptr civ,iptr civ2)

{
  uint *puVar1;
  iptr iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x20) == 0) {
    if ((*(byte *)&civs[civ2].treaties[civ] & 0xe) == 0) {
      civ_adjust_attitude(civ2,civ,0x14);
    }
    else {
      iVar2 = civ_name_plural(civ);
      text_set_string_arg(0,iVar2);
      iVar2 = civ_name_plural(civ2);
      text_set_string_arg(1,iVar2);
      if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
        if (autoplay_active != 0) {
          return;
        }
        if (civs[civ].government == 4) {
          return;
        }
        if ((game.multiplayer < 3) || (human_civ == civ2)) {
          if ((*(byte *)&civs[civ2].treaties[civ] & 8) == 0) {
            iVar3 = popup_game_with_sprite(ADDR(0x62dd08, ((u8 *)&g.d_0062dd08)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
            if (iVar3 == 1) {
              diplo_set_treaty_flags(civ,civ2,0x2000);
              civs[civ2].last_treaty_turn[civ] = game.turn;
            }
          }
          else {
            iVar3 = popup_game_with_sprite(ADDR(0x62dcf8, ((u8 *)&g.d_0062dcf8)),(iptr)(&diplo_popup_portrait_sprite +
                                                      ((game.advance_known_by[0xf] != '\0') - 1 &
                                                      0xffff7c80)),0);
            if (iVar3 == 1) {
              diplo_clear_treaty_flags(civ,civ2,8);
              civs[civ2].last_treaty_turn[civ] = game.turn;
            }
          }
        }
        else {
          net_send_state_diff(0xff,2,0,0,0);
          net_send_message(0xa4,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                             civ,civ2,0,0,0,0,0,0);
        }
      }
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
         ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
          if (civs[civ].government == 4) {
            puVar1 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
            *puVar1 = *puVar1 | 0x10;
            civ_adjust_attitude(civ2,civ,10);
            if (autoplay_active == 0) {
              iVar2 = civ_get_adjective(civ);
              text_set_string_arg(0,iVar2);
              popup_game_with_sprite(ADDR(0x62dd28, ((u8 *)&g.d_0062dd28)),ADDR(0x646968, ((u8 *)&g.d_00646968)),0);
            }
          }
          else {
            if (autoplay_active == 0) {
              popup_game_with_sprite(ADDR(0x62dd38, ((u8 *)&g.d_0062dd38)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
            }
            diplo_declare_war(civ,civ2,-1);
          }
        }
        else {
          if ((spy_last_mission == 2) && (civs[civ].num_advances < civs[civ2].num_advances)) {
            if (autoplay_active != 0) {
              return;
            }
            diplo_eval_ai_stance(civ,civ2);
            diplo_set_attitude_arg(civ,civ2);
            iVar3 = _rand();
            civ_adjust_attitude(civ2,civ,iVar3 % 0xf + 5);
            popup_game_with_sprite(ADDR(0x62dd10, ((u8 *)&g.d_0062dd10)),(iptr)(&diplo_popup_portrait_sprite +
                                              ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80
                                              )),0);
            return;
          }
          if (autoplay_active == 0) {
            popup_game_with_sprite(ADDR(0x62dd18, ((u8 *)&g.d_0062dd18)),(iptr)(&diplo_popup_portrait_sprite +
                                              ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80
                                              )),0);
          }
          diplo_declare_war(civ,civ2,-1);
        }
      }
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        if (civs[civ].government != 6) {
          uVar4 = _rand();
          uVar5 = (int)uVar4 >> 0x1f;
          if (((uVar4 ^ uVar5) - uVar5 & 1 ^ uVar5) == uVar5) {
            return;
          }
          if (civs[civ].government != 5) {
            return;
          }
        }
        if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 1) == 0)) {
          if (autoplay_active == 0) {
            iVar2 = civ_get_adjective(civ);
            text_set_string_arg(0,iVar2);
            popup_game_with_sprite(ADDR(0x62dd44, ((u8 *)&g.d_0062dd44)),(iptr)(&government_sprites + (uint)civs[civ].government * 0x3c
                                              ),0);
          }
          civ_change_government(civ,0);
        }
      }
    }
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef scenario_flags

/* 0055bbc0 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
int __cdecl diplo_count_border_intruders(iptr civ,iptr param_2)

{
  iptr x;
  int y;
  int iVar3;
  uint uVar4;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  border_intruder_city = -1;
  diplo_border_intruded_cities = 0;
  diplo_border_intruder_units = 0;
  diplo_border_intruder_count = 0;
  diplo_border_repeat_offenses = 0;
  if ((*(byte *)&civs[civ].treaties[param_2] & 8) == 0) {
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        local_1c = 0;
        local_8 = 0;
LAB_0055bc9b:
        if (local_8 < 0x14) {
          x = map_wrap_x((int)cities[city].x + (int)(char)(&city_tile_dx_table)[local_8]);
          y = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[local_8];
          iVar3 = map_in_bounds(x,y);
          if ((((iVar3 == 0) || (iVar3 = tile_is_ocean(x,y), iVar3 != 0)) ||
              (iVar3 = tile_city_owner(x,y), -1 < iVar3)) ||
             (iVar3 = tile_unit_owner(x,y), iVar3 != param_2)) goto LAB_0055bc98;
          uVar4 = tile_improvements(x,y);
          for (unit = tile_first_unit(x,y); -1 < unit;
              unit = unit_next_in_stack(unit)) {
            if (((char)unit_types[units[unit].type].role < 5) &&
               ((units[unit].flags & 4) == 0)) {
              if (city != border_intruder_city) {
                diplo_border_intruded_cities++;
              }
              border_intruder_city = city;
              if ((units[unit].flags & 0x20) == 0) {
                units[unit].flags = units[unit].flags | 0x20;
              }
              else {
                diplo_border_repeat_offenses++;
              }
              units[unit].flags = units[unit].flags | 4;
              y = diplo_border_intruder_count;
              local_1c++;
              diplo_border_intruder_units++;
              diplo_border_intruder_count++;
              if ((uVar4 & 0x10) != 0) {
                diplo_border_intruder_count = y + 2;
              }
              if ((uVar4 & 0x20) != 0) {
                diplo_border_intruder_count++;
              }
              if ((uVar4 & 8) != 0) {
                diplo_border_intruder_count++;
              }
              if ((uVar4 & 4) != 0) {
                diplo_border_intruder_count++;
              }
              if ((uVar4 & 0x40) != 0) {
                diplo_border_intruder_count += 2;
              }
            }
          }
        }
        if (3 < local_1c) {
          diplo_border_repeat_offenses++;
        }
      }
    }
  }
  else {
    diplo_border_intruder_count = 0;
  }
  return diplo_border_intruder_count;
LAB_0055bc98:
  local_8++;
  goto LAB_0055bc9b;
}
#undef unit
#undef local_1c
#undef city
#undef local_8

/* 0055bef9 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl diplo_senate_intervenes(iptr civ,iptr civ2)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civs[civ].government < 5) {
    uVar1 = 0;
  }
  else if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 1) == 0)) {
    local_8 = 0;
    if ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x10) != 0) {
      local_8 = 0x19;
    }
    iVar2 = civ_has_wonder(civ,0x18);
    if (iVar2 != 0) {
      local_8 = 0x32;
    }
    iVar2 = int_clamp(local_8 + (uint)civs[civ2].reputation * 0xf,0,0x4b);
    if ((int)(uint)civs[civ].field_16 < iVar2) {
      uVar1 = 0;
    }
    else if (civs[civ].government < 6) {
      if ((civs[civ].flags & 4) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef scenario_flags
#undef local_8

/* 0055cbd5 auto */
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
i32 __cdecl diplo_ai_feels_secure(iptr civ,iptr civ2)

{
  byte bVar1;
  i32 uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = *(byte *)&civs[civ].treaties[civ2];
  if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 8) == 0) {
    if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) {
      for (civ3 = 1; civ3 < 8; civ3++) {
        if ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) {
          iVar3 = diplo_is_hostile(civ,civ3);
          if (((iVar3 != 0) && (civs[civ2].military_strength < civs[civ3].military_strength))
             && ((*(byte *)&civs[civ3].treaties[civ2] & 8) == 0)) {
            return 0;
          }
          iVar3 = diplo_is_hostile(civ2,civ3);
          if (((iVar3 != 0) && (civs[civ].military_strength < civs[civ3].military_strength))
             && ((*(byte *)&civs[civ3].treaties[civ] & 8) == 0)) {
            return 0;
          }
        }
      }
      if (civs[civ].units_active[0x2d] < civs[civ2].units_active[0x2d]) {
        uVar2 = 0;
      }
      else {
        local_c = 0;
        for (local_10 = 1; local_10 < 8; local_10++) {
          if ((local_10 != civ) && (local_10 != civ2)) {
            iVar3 = diplo_is_hostile(civ,local_10);
            if (iVar3 != 0) {
              local_c++;
            }
            iVar3 = local_c;
            if (((((*(byte *)&civs[civ].treaties[local_10] & 8) != 0) &&
                 ((*(byte *)&civs[civ2].treaties[local_10] & 8) != 0)) &&
                ((1 << ((byte)local_10 & 0x1f) & (uint)game.human_players) != 0)) &&
               ((iVar3 = local_c + 1, game.power_rank[civ] < game.power_rank[local_10] &&
                (game.power_rank[civ2] < game.power_rank[local_10])))) {
              iVar3 = local_c + 2;
            }
            local_c = iVar3;
            if ((((*(byte *)&civs[civ].treaties[local_10] & 8) != 0) &&
                ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_10 * 4) & 0x20) != 0)) &&
               ((1 << ((byte)local_10 & 0x1f) & (uint)game.human_players) != 0)) {
              local_c--;
            }
            if (((game.power_rank[local_10] == 7) && (199 < game.turn)) &&
               ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_10 * 4) & 0x20) != 0)) {
              local_c--;
            }
          }
        }
        iVar3 = diplo_is_hostile(civ,civ2);
        if (iVar3 == 0) {
          local_c++;
        }
        if ((bVar1 & 8) != 0) {
          local_c++;
        }
        local_8 = 0;
        local_1c = 0;
        local_24 = 1;
        for (local_18 = 1; local_18 < 0x3f; local_18++) {
          if ((*(char *)&civs[civ].continent_cities[local_18] != '\0') &&
             ((uint)civs[civ].continent_attack[local_18] +
              (uint)civs[civ].continent_military[local_18] <
              (uint)civs[civ2].continent_attack[local_18])) {
            return 0;
          }
          if ((*(short *)&civs[civ].continent_attack[local_18] != 0) &&
             (*(short *)&civs[civ2].continent_military[local_18] != 0)) {
            local_1c += (uint)civs[civ].continent_attack[local_18];
            local_24 = local_24 +
                       ((int)(uint)civs[civ2].continent_attack[local_18] >> 1) +
                       (uint)civs[civ2].continent_military[local_18];
            local_8 += (uint)civs[civ].continent_cities[local_18];
          }
        }
        if (((local_1c << 2) / local_24 < (local_c - leaders[civs[civ].tribe].attack) + 4) &&
           (local_8 != 0)) {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
      }
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}
#undef local_24
#undef civ3
#undef local_1c
#undef local_18
#undef local_10
#undef local_c
#undef local_8

/* 0055d1e2 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define advance3 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(24)))
i32 __cdecl diplo_ai_swap_advances(uptr civ,uptr civ2)

{
  bool bVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  local_18 = 0;
  local_10 = 0;
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 0x20) == 0)) {
    if (((((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) == 0) ||
        (((game.difficulty == '\0' || (civs[game.civ_by_rank[7]].num_cities < 5)) ||
         (game.turn < 0xc9)))) ||
       ((civs[game.civ_by_rank[7]].num_advances <= civs[civ].num_advances ||
        (civs[game.civ_by_rank[7]].num_advances <= civs[civ2].num_advances)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    for (advance = 0; advance < 100; advance++) {
      if ((advances[advance].preq[0] != -2) || (advances[advance].preq[1] != -2)) {
        iVar3 = civ_has_advance(civ,advance);
        if ((iVar3 == 0) && (iVar3 = civ_has_advance(civ2,advance), iVar3 != 0)) {
          iVar3 = _rand();
          iVar4 = ai_advance_value(civ,advance);
          iVar4 = iVar3 % 3 + iVar4;
          if (((local_10 & 1) == 0) || (local_14 < iVar4)) {
            advance2 = advance;
            local_10 = local_10 | 1;
            local_14 = iVar4;
          }
        }
        else {
          iVar3 = civ_has_advance(civ2,advance);
          if ((iVar3 == 0) && (iVar3 = civ_has_advance(civ,advance), iVar3 != 0)) {
            iVar3 = _rand();
            iVar4 = ai_advance_value(civ2,advance);
            iVar4 = iVar3 % 3 + iVar4;
            if (((local_10 & 2) == 0) || (local_18 < iVar4)) {
              advance3 = advance;
              local_10 = local_10 | 2;
              local_18 = iVar4;
            }
          }
        }
      }
    }
    if (local_10 == 3) {
      civ_give_advance(civ,advance2,civ2,0,0);
      civ_give_advance(civ2,advance3,civ,0,0);
      uVar2 = 1;
    }
    else {
      if (local_10 == 1) {
        if (((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) &&
           ((((int)((uint)civs[civ].num_advances + (6 - (uint)game.difficulty) * 2) <
              (int)(uint)civs[civ2].num_advances || (bVar1)) &&
            ((*(byte *)(civ2 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 0x594) & 4) == 0)))) {
          diplo_set_treaty_flags(civ,civ2,0x40000);
          civ_give_advance(civ,advance2,civ2,0,0);
          return 1;
        }
      }
      else if ((((local_10 == 2) && ((*(byte *)&civs[civ2].treaties[civ] & 8) != 0)
                ) && (((int)((uint)civs[civ2].num_advances + (6 - (uint)game.difficulty) * 2) <
                       (int)(uint)civs[civ].num_advances || (bVar1)))) &&
              ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 4) & 4) == 0)) {
        diplo_set_treaty_flags(civ,civ2,0x40000);
        civ_give_advance(civ2,advance3,civ,0,0);
        return 1;
      }
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}
#undef scenario_flags
#undef advance3
#undef advance2
#undef advance
#undef local_18
#undef local_14
#undef local_10

/* 0055d685 auto */
i32 __cdecl diplo_ally_join_war(iptr civ,iptr civ2,iptr civ3)

{
  uint *puVar1;
  i32 uVar2;
  int iVar3;
  iptr iVar4;
  
  if ((civs[civ].treaties[civ2] & 0x2008) == 0) {
    if ((*(byte *)(civ3 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) {
      if (((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) &&
         ((*(byte *)&civs[civ3].treaties[civ2] & 0x10) != 0)) {
        puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
        *puVar1 = *puVar1 | 0x20;
        puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 0x594);
        *puVar1 = *puVar1 | 0x20;
      }
      uVar2 = 0;
    }
    else {
      if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0) {
          if ((int)civs[civ2].last_treaty_turn[civ] - (int)game.turn < 6) {
            return 0;
          }
          if ((game.power_rank[civ2] < 7) && (iVar3 = _rand(), iVar3 % 3 != 0)) {
            return 0;
          }
        }
        civs[civ2].last_treaty_turn[civ] = game.turn;
        civs[civ2].last_treaty_turn[civ3] = game.turn;
      }
      iVar4 = civ_name_plural(civ);
      text_set_string_arg(0,iVar4);
      iVar4 = civ_name_plural(civ3);
      text_set_string_arg(1,iVar4);
      iVar4 = civ_name_plural(civ2);
      text_set_string_arg(2,iVar4);
      popup_game_with_sprite(ADDR(0x633b00, ((u8 *)&g.d_00633b00)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
      diplo_set_treaty_flags(civ,civ2,0x2000);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0055d8d8 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_meeting_pending (*(i32 *)((u8 *)&g.d_00626a2c))
#define mp_meeting_reply (*(int *)((u8 *)&g.d_0063f278))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define nm_parley_cancel_count (*(int *)((u8 *)&g.d_006c91e4))
#define parley_other_civ (*(uptr *)((u8 *)&g.d_0067a8c0))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define _DAT_0063e4e8 (*(i32 *)((u8 *)&g.d_0063e4e8))
#define civ3 (*(uptr *)(frame_ + FRAME_OFF(4)))
#define civ4 (*(uptr *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl diplo_civs_meet(uptr civ,uptr civ2,iptr x,iptr y)

{
  uint *puVar1;
  bool bVar2;
  bool bVar3;
  int city;
  iptr iVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civ == 0) {
    return;
  }
  if (civ2 == 0) {
    return;
  }
  if (game.turn == 0) {
    return;
  }
  if ((scenario_events_loaded != 0) &&
     (city = events_check_negotiation((ScenarioEvents *)&scenario_events,civ,civ2),
     city == 0)) {
    return;
  }
  if (((game.multiplayer == '\0') || ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)
      ) || ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) {
    if ((((2 < game.multiplayer) && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0))
        && (human_civ != civ)) &&
       ((((*(byte *)&civs[civ].treaties[civ2] & 1) == 0 ||
         ((*(byte *)(civ2 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 0x594) & 1) != 0)) ||
        ((civs[civ].last_treaty_turn[civ2] < 0 ||
         (0xf < (int)game.turn - (int)civs[civ].last_treaty_turn[civ2])))))) {
      net_send_message(0x99,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),
                         civ,civ2,x,y,0,0,0,0);
      return;
    }
    if ((((2 < game.multiplayer) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0))
        && (human_civ != civ2)) &&
       ((((*(byte *)&civs[civ2].treaties[civ] & 1) == 0 ||
         ((*(byte *)(civ * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 0x594) & 1) != 0)) ||
        ((civs[civ2].last_treaty_turn[civ] < 0 ||
         (0xf < (int)game.turn - (int)civs[civ2].last_treaty_turn[civ])))))) {
      net_send_message(0x99,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                         civ2,civ,x,y,0,0,0,0);
      return;
    }
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
        (human_civ == civ)) &&
       (((*(byte *)&civs[civ].treaties[civ2] & 1) == 0 ||
        ((((*(byte *)(civ2 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 0x594) & 1) != 0 ||
          (civs[civ].last_treaty_turn[civ2] < 0)) ||
         (0xf < (int)game.turn - (int)civs[civ].last_treaty_turn[civ2])))))) {
      if ((2 < game.multiplayer) && (human_civ != civ)) {
        return;
      }
      diplo_ai_meet_player(civ,civ2,x,y,0);
    }
    if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
        (human_civ == civ2)) &&
       (((*(byte *)&civs[civ2].treaties[civ] & 1) == 0 ||
        ((((*(byte *)(civ * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 0x594) & 1) != 0 ||
          (civs[civ2].last_treaty_turn[civ] < 0)) ||
         (0xf < (int)game.turn - (int)civs[civ2].last_treaty_turn[civ])))))) {
      if ((2 < game.multiplayer) && (human_civ != civ2)) {
        return;
      }
      diplo_ai_meet_player(civ2,civ,x,y,0);
    }
  }
  else if (game.multiplayer < 3) {
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
        (human_civ == civ)) &&
       (((*(byte *)&civs[civ].treaties[civ2] & 1) == 0 ||
        ((((*(byte *)(civ2 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 0x594) & 1) != 0 ||
          (civs[civ].last_treaty_turn[civ2] < 0)) ||
         (0xf < (int)game.turn - (int)civs[civ].last_treaty_turn[civ2])))))) {
      diplo_ai_meet_player(civ,civ2,x,y,0);
    }
    if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
        (human_civ == civ2)) &&
       ((((*(byte *)&civs[civ2].treaties[civ] & 1) == 0 ||
         (((*(byte *)(civ * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 0x594) & 1) != 0 ||
          (civs[civ2].last_treaty_turn[civ] < 0)))) ||
        (0xf < (int)game.turn - (int)civs[civ2].last_treaty_turn[civ])))) {
      diplo_ai_meet_player(civ2,civ,x,y,0);
    }
  }
  else if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
           ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
          (((*(byte *)&civs[civ].treaties[civ2] & 1) == 0 ||
           ((civs[civ].last_treaty_turn[civ2] < 0 ||
            (0xf < (int)game.turn - (int)civs[civ].last_treaty_turn[civ2]))))))
  {
    mp_meeting_reply = -1;
    mp_meeting_pending = 1;
    net_send_text_args(0x3d,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0,
                       civ,0);
    iVar5 = civ_leader_name(civ2);
    text_set_string_arg(1,iVar5);
    iVar5 = civ_name_plural(civ2);
    text_set_string_arg(2,iVar5);
    dlg_pending_idle_callback = ((void *)ADDR(0x0040326a, mp_meeting_wait_idle));
    _DAT_0063e4e8 = timer_ticks();
    city = popup_game_sprite_flags(ADDR(0x633b08, ((u8 *)&g.d_00633b08)),0x2000001,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    if (net_host_handoff_stage == '\0') {
      if (nm_parley_cancel_count == 0) {
        if (city == -1) {
          net_send_message(0x81,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,
                             0,0,0,0,0,0,0);
          parley_other_civ = 0xffffffff;
          mp_meeting_pending = 0;
        }
        else if (mp_meeting_reply < 1) {
          dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
          popup_game_with_sprite(ADDR(0x633b34, ((u8 *)&g.d_00633b34)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          mp_meeting_pending = 0;
        }
        else if (mp_meeting_reply == 1) {
          mp_meeting_reply = -1;
          parley_other_civ = civ2;
          dlg_pending_idle_callback = ((void *)ADDR(0x0040326a, mp_meeting_wait_idle));
          _DAT_0063e4e8 = timer_ticks();
          iVar5 = civ_name_plural(civ);
          text_set_string_arg(0,iVar5);
          popup_game_with_sprite(ADDR(0x633b44, ((u8 *)&g.d_00633b44)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          if (net_host_handoff_stage == '\0') {
            if (nm_parley_cancel_count == 0) {
              parley_wnd_open((C_004083b0_430 *)&parley_wnd,civ2,3);
            }
            else {
              parley_other_civ = 0xffffffff;
              nm_parley_cancel_count = 0;
              iVar5 = civ_name_plural(civ2);
              text_set_string_arg(0,iVar5);
              dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
              popup_game_with_sprite(ADDR(0x633b5c, ((u8 *)&g.d_00633b5c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
              mp_meeting_pending = 0;
            }
          }
          else {
            parley_other_civ = 0xffffffff;
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            popup_game_with_sprite(ADDR(0x633b50, ((u8 *)&g.d_00633b50)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            mp_meeting_pending = 0;
          }
        }
        else {
          dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
          popup_game_with_sprite(ADDR(0x633b6c, ((u8 *)&g.d_00633b6c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          mp_meeting_pending = 0;
        }
      }
      else {
        nm_parley_cancel_count = 0;
        iVar5 = civ_name_plural(civ2);
        text_set_string_arg(0,iVar5);
        dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
        popup_game_with_sprite(ADDR(0x633b24, ((u8 *)&g.d_00633b24)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        parley_other_civ = 0xffffffff;
        mp_meeting_pending = 0;
      }
    }
    else {
      dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
      popup_game_with_sprite(ADDR(0x633b18, ((u8 *)&g.d_00633b18)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      mp_meeting_pending = 0;
    }
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 1) == 0) {
    diplo_set_treaty_flags(civ,civ2,0x4000);
  }
  bVar7 = (*(byte *)&civs[civ].treaties[civ2] & 1) == 0;
  diplo_set_treaty_flags(civ,civ2,0x401);
  if (((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
       ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) &&
      ((((int)game.turn + civ2 + civ & 3) == 0 || (bVar7)))) &&
     ((((game.game_flags & 0x80) == 0 || (((int)scenario_flags & 0x8000U) == 0)) ||
      ((((civ != 3 || (civ2 != 1)) && ((civ != 1 || (civ2 != 3)))) || (4 < game.turn))
      )))) {
    city = diplo_ai_feels_secure(civ,civ2);
    if (((((city == 0) || (city = civ_has_wonder(civ2,6), city != 0)) ||
         (city = civ_has_wonder(civ2,0x18), city != 0)) ||
        ((4 < civs[civ].government &&
         ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 8) == 0)))) &&
       (((city = diplo_ai_feels_secure(civ2,civ), city == 0 ||
         ((city = civ_has_wonder(civ,6), city != 0 ||
          (city = civ_has_wonder(civ,0x18), city != 0)))) ||
        ((4 < civs[civ2].government &&
         ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 8) == 0)))))) {
      diplo_ai_swap_advances(civ,civ2);
      if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
        if ((autoplay_active == 0) && ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 8) != 0))
        {
          iVar5 = civ_name_plural(civ);
          text_set_string_arg(1,iVar5);
          iVar5 = civ_name_plural(civ2);
          text_set_string_arg(2,iVar5);
          city = civ_has_wonder(civ2,0x18);
          if (city == 0) {
            city = civ_has_wonder(civ2,6);
            if (city != 0) {
              popup_game_with_sprite(ADDR(0x633b80, ((u8 *)&g.d_00633b80)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
            }
          }
          else {
            popup_game_with_sprite(ADDR(0x633b78, ((u8 *)&g.d_00633b78)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
          }
        }
        if ((autoplay_active == 0) && ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 8) != 0))
        {
          iVar5 = civ_name_plural(civ2);
          text_set_string_arg(1,iVar5);
          iVar5 = civ_name_plural(civ);
          text_set_string_arg(2,iVar5);
          city = civ_has_wonder(civ,0x18);
          if (city == 0) {
            city = civ_has_wonder(civ,6);
            if (city != 0) {
              popup_game_with_sprite(ADDR(0x633b94, ((u8 *)&g.d_00633b94)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
            }
          }
          else {
            popup_game_with_sprite(ADDR(0x633b8c, ((u8 *)&g.d_00633b8c)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
          }
        }
        if ((autoplay_active == 0) &&
           ((*(byte *)&civs[human_civ].treaties[civ] & 8) != 0)) {
          iVar5 = civ_name_plural(civ);
          text_set_string_arg(0,iVar5);
          iVar5 = civ_name_plural(civ2);
          text_set_string_arg(1,iVar5);
          popup_game_with_sprite(ADDR(0x633ba0, ((u8 *)&g.d_00633ba0)),(iptr)(&diplo_popup_portrait_sprite +
                                            ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80))
                             ,0);
        }
        else if ((autoplay_active == 0) &&
                ((*(byte *)&civs[human_civ].treaties[civ2] & 8) != 0)) {
          iVar5 = civ_name_plural(civ2);
          text_set_string_arg(0,iVar5);
          iVar5 = civ_name_plural(civ);
          text_set_string_arg(1,iVar5);
          popup_game_with_sprite(ADDR(0x633bb0, ((u8 *)&g.d_00633bb0)),(iptr)(&diplo_popup_portrait_sprite +
                                            ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80))
                             ,0);
        }
        else if ((autoplay_active == 0) &&
                (((((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0 ||
                     (city = civ_has_wonder(human_civ,0x18), city != 0)) ||
                    (city = civ_has_wonder(human_civ,9), city != 0)) ||
                   (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
                    (city = civ_has_wonder(human_civ,0x18), city != 0)))) ||
                  (city = civ_has_wonder(human_civ,9), city != 0)) ||
                 (game.reveal_map != '\0')))) {
          iVar5 = civ_name_plural(civ);
          text_set_string_arg(0,iVar5);
          iVar5 = civ_name_plural(civ2);
          text_set_string_arg(1,iVar5);
          popup_game_with_sprite(ADDR(0x633bc0, ((u8 *)&g.d_00633bc0)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
        }
        diplo_set_treaty_flags(civ,civ2,4);
      }
      else {
        bVar8 = (*(byte *)&civs[civ].treaties[civ2] & 8) != 0;
        bVar2 = false;
        bVar7 = bVar8;
        if ((game.power_rank[civ] == 7) && (3 < game.power_rank[civ2])) {
          bVar7 = false;
          bVar2 = true;
        }
        if ((game.power_rank[civ2] == 7) && (3 < game.power_rank[civ])) {
          bVar7 = false;
          bVar2 = true;
        }
        local_14 = 0;
        civ3 = 0xffffffff;
        bVar3 = false;
        for (civ4 = 1; (int)civ4 < 8; civ4++) {
          if ((civ4 != civ) && (civ4 != civ2)) {
            if (((*(byte *)&civs[civ].treaties[civ4] & 8) == 0) &&
               ((*(byte *)&civs[civ2].treaties[civ4] & 8) == 0)) {
              if (((((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) == 0) ||
                   (game.power_rank[civ4] != 7)) || (game.difficulty == '\0')) ||
                 ((civs[civ4].num_cities < 5 || (game.turn < 0xc9)))) {
                bVar3 = false;
              }
              else {
                bVar3 = true;
              }
              if (bVar3) goto LAB_0055ecb6;
              if (game.difficulty != '\0') {
                if (bVar7) {
                  if (((*(byte *)&civs[civ].treaties[civ4] & 4) == 0) &&
                     ((*(byte *)&civs[civ2].treaties[civ4] & 4) == 0)) {
LAB_0055ecb6:
                    civ3 = civ4;
                    break;
                  }
                }
                else if (((!bVar2) && (city = diplo_is_hostile(civ,civ4), city != 0)) &&
                        ((game.power_rank[civ] <= game.power_rank[civ4] &&
                         ((city = diplo_is_hostile(civ2,civ4), city != 0 &&
                          (game.power_rank[civ2] <= game.power_rank[civ4]))))))
                goto LAB_0055ecb6;
              }
            }
            else {
              local_14++;
            }
          }
        }
        if ((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) &&
           ((((civ == 6 && (civ2 == 7)) || ((civ == 7 && (civ2 == 6)))) &&
            (1 < game.turn)))) {
          civ3 = 0;
        }
        if (((int)civ3 < 1) ||
           ((((!bVar3 || ((int)(uint)civs[game.player_civ].reputation < local_14)) &&
             (local_14 != 0)) && (!bVar7)))) {
          if (((bVar8) && (autoplay_active == 0)) &&
             (((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0 ||
              (((city = civ_has_wonder(human_civ,0x18), city != 0 ||
                (city = civ_has_wonder(human_civ,9), city != 0)) ||
               (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
                (((city = civ_has_wonder(human_civ,0x18), city != 0 ||
                  (city = civ_has_wonder(human_civ,9), city != 0)) ||
                 (game.reveal_map != '\0')))))))))) {
            iVar5 = civ_name_plural(civ);
            text_set_string_arg(0,iVar5);
            iVar5 = civ_name_plural(civ2);
            text_set_string_arg(1,iVar5);
            popup_game_with_sprite(ADDR(0x633be4, ((u8 *)&g.d_00633be4)),(iptr)(&diplo_popup_portrait_sprite +
                                              ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80
                                              )),0);
          }
          diplo_clear_treaty_flags(civ,civ2,8);
        }
        else {
          if (!bVar8) {
            local_1c = 0;
            if (((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0) ||
                 (city = civ_has_wonder(human_civ,0x18), city != 0)) ||
                ((city = civ_has_wonder(human_civ,9), city != 0 ||
                 (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
                  (city = civ_has_wonder(human_civ,0x18), city != 0)))))) ||
               (((city = civ_has_wonder(human_civ,9), city != 0 ||
                 (game.reveal_map != '\0')) ||
                (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0 &&
                 (((*(byte *)&civs[human_civ].treaties[civ] & 1) != 0 ||
                  ((*(byte *)&civs[human_civ].treaties[civ2] & 1) != 0)))))))) {
              iVar5 = civ_name_plural(civ);
              text_set_string_arg(0,iVar5);
              iVar5 = civ_name_plural(civ2);
              text_set_string_arg(1,iVar5);
              if ((autoplay_active == 0) && (bVar3)) {
                city = city_find_nearest(x,y,civ,0xffffffff,civ2);
                if (-1 < city) {
                  text_set_string_arg(2,(iptr)&cities[city].name);
                }
                iVar5 = civ_get_adjective(civ3);
                text_set_string_arg(3,iVar5);
                popup_game_with_sprite(ADDR(0x633bcc, ((u8 *)&g.d_00633bcc)),ADDR(0x648018, ((u8 *)&g.d_00648018)),0);
              }
              else if (autoplay_active == 0) {
                iVar5 = civ_name_plural(civ3);
                text_set_string_arg(2,iVar5);
                popup_game_with_sprite(ADDR(0x633bd8, ((u8 *)&g.d_00633bd8)),ADDR(0x63fc98, ((u8 *)&g.d_0063fc98)),0);
              }
              local_1c = diplo_ally_join_war(civ,civ3,civ2);
              uVar6 = diplo_ally_join_war(civ2,civ3,civ);
              local_1c = local_1c | uVar6;
            }
            if ((((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                (city = civ_spaceship_launched(civ3), city == 0)) && (local_1c == 0)) {
              if ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) == 0) {
                diplo_set_treaty_flags(civ,civ3,0x10000);
              }
              if ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) == 0) {
                diplo_set_treaty_flags(civ2,civ3,0x10000);
              }
            }
          }
          diplo_set_treaty_flags(civ,civ2,8);
        }
      }
    }
    else if (((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) == 0) || (bVar7)) {
      if ((autoplay_active == 0) &&
         ((*(byte *)&civs[human_civ].treaties[civ] & 8) != 0)) {
        city = diplo_ai_feels_secure(civ,civ2);
        if (city == 0) {
          diplo_ally_demand_help(civ,civ2);
        }
        iVar5 = civ_name_plural(civ);
        text_set_string_arg(0,iVar5);
        iVar5 = civ_name_plural(civ2);
        text_set_string_arg(1,iVar5);
        popup_game_with_sprite(ADDR(0x633bf4, ((u8 *)&g.d_00633bf4)),(iptr)(&diplo_popup_portrait_sprite +
                                          ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0
                          );
      }
      else if ((autoplay_active == 0) &&
              ((*(byte *)&civs[human_civ].treaties[civ2] & 8) != 0)) {
        city = diplo_ai_feels_secure(civ2,civ);
        if (city == 0) {
          diplo_ally_demand_help(civ2,civ);
        }
        iVar5 = civ_name_plural(civ2);
        text_set_string_arg(0,iVar5);
        iVar5 = civ_name_plural(civ);
        text_set_string_arg(1,iVar5);
        popup_game_with_sprite(ADDR(0x633c04, ((u8 *)&g.d_00633c04)),(iptr)(&diplo_popup_portrait_sprite +
                                          ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0
                          );
      }
      else if ((autoplay_active == 0) &&
              (((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0 ||
                 (city = civ_has_wonder(human_civ,0x18), city != 0)) ||
                (city = civ_has_wonder(human_civ,9), city != 0)) ||
               ((((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
                 (city = civ_has_wonder(human_civ,0x18), city != 0)) ||
                ((city = civ_has_wonder(human_civ,9), city != 0 ||
                 (game.reveal_map != '\0')))))))) {
        iVar5 = civ_name_plural(civ);
        text_set_string_arg(0,iVar5);
        iVar5 = civ_name_plural(civ2);
        text_set_string_arg(1,iVar5);
        if (((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) ||
           ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0)) {
          popup_game_with_sprite(ADDR(0x633c20, ((u8 *)&g.d_00633c20)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x633c14, ((u8 *)&g.d_00633c14)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
        }
      }
      diplo_clear_treaty_flags(civ,civ2,4);
      diplo_set_treaty_flags(civ,civ2,0x2000);
      if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) {
        diplo_clear_treaty_flags(civ,civ2,0x10);
        puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
        *puVar1 = *puVar1 | 0x800;
      }
    }
  }
  return;
}
#undef autoplay_active
#undef dlg_pending_idle_callback
#undef human_civ
#undef mp_meeting_pending
#undef mp_meeting_reply
#undef net_host_handoff_stage
#undef nm_parley_cancel_count
#undef parley_other_civ
#undef scenario_events_loaded
#undef scenario_flags
#undef _DAT_0063e4e8
#undef civ3
#undef civ4
#undef local_1c
#undef local_14

/* 0055f5a3: written by hand in src/game/bigframes.c */

/* 0055f7d1 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(36)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
void __cdecl diplo_ai_military_aid(iptr civ)

{
  char *pcVar1;
  u8 uVar2;
  u8 uVar3;
  iptr x2;
  iptr y2;
  iptr iVar6;
  int x;
  int y;
  iptr iVar8;
  int city2;
  iptr iVar11;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((civ2 != civ) &&
       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0)) {
      local_14++;
    }
  }
  civ2 = 1;
  do {
    if (7 < civ2) {
      return;
    }
    if (((civ2 != civ) && ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0))
       && ((civs[civ2].military_strength <= civs[civ].military_strength || (local_14 == 0)))
       ) {
      for (civ3 = 1; civ3 < 8; civ3++) {
        if (((((civ3 != civ) && (civ3 != civ2)) &&
             ((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 4) & 0x20) != 0)) &&
            (((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 4) & 2) != 0 &&
             (civs[civ2].military_strength <= civs[civ3].military_strength)))) &&
           (game.power_rank[civ2] <= game.power_rank[civ3])) {
          unit2 = -1;
          local_c = 0;
          for (unit = 0; unit < game.num_units; unit++) {
            if (((units[unit].id != 0) && (units[unit].owner == civ)) &&
               (((char)unit_types[units[unit].type].role < 2 &&
                (unit_types[units[unit].type].domain == '\0')))) {
              x2 = (iptr)units[unit].x;
              y2 = (iptr)units[unit].y;
              iVar6 = map_in_bounds(x2,y2);
              if ((((iVar6 == 0) && (x = tile_city_owner(x2,y2), -1 < x)) &&
                  (x = unit_stack_sum(unit,2), 1 < x)) &&
                 ((x = tile_landmass(x2,y2),
                  *(char *)&civs[civ].continent_policy[x] == 4 ||
                  ((*(char *)&civs[civ].continent_policy[x] == 5 && (local_14 == 0))))))
              {
                uVar2 = unit_types[units[unit].type].attack;
                uVar3 = unit_types[units[unit].type].defense;
                x = unit_max_hp(unit);
                x = ((int)(char)uVar3 + (char)uVar2 * 2) * x;
                if (local_c < x) {
                  unit2 = unit;
                  local_c = x;
                }
              }
            }
          }
          if (-1 < unit2) {
            for (city = 0; city < game.num_cities; city++) {
              if ((cities[city].id != 0) && (cities[city].owner == civ2)) {
                x = (int)cities[city].x;
                y = (int)cities[city].y;
                iVar8 = tile_unit_owner(x,y);
                if (((-1 < iVar8) &&
                    ((((cities[city].flags & 0x80) != 0 &&
                      (city2 = tile_landmass(x,y),
                      *(char *)&civs[civ2].continent_policy[city2] == 1)) &&
                     (city2 = tile_zoc_unit_adjacent(x,y,civ2), city2 == 0)))) &&
                   (city2 = city_at((int)units[unit2].x,(int)units[unit2].y),
                   -1 < city2)) {
                  unit_stack_unlink(unit2,1);
                  pcVar1 = (char *)(units[unit2].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
                  *pcVar1 = *pcVar1 - 1;
                  units[unit2].owner = (byte)civ2;
                  units[unit2].home_city = (i8)city;
                  units[unit2].visibility = '\0';
                  pcVar1 = (char *)(units[unit2].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ2 * 0x594);
                  *pcVar1 = *pcVar1 + 1;
                  unit_stack_link(unit2,x,y,1);
                  city_window_refresh_if_city((FrameWindow *)&city_window,city);
                  map_redraw_tile_all_views((int)cities[city].x,(int)cities[city].y);
                  city_window_refresh_if_city((FrameWindow *)&city_window,city2);
                  map_redraw_tile_all_views((int)cities[city2].x,(int)cities[city2].y);
                  if (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                     (autoplay_active == 0)) {
                    iVar11 = civ_name_plural(civ);
                    text_set_string_arg(0,iVar11);
                    text_set_label_arg(1,unit_types[units[unit2].type].name);
                    iVar11 = civ_name_plural(civ2);
                    text_set_string_arg(2,iVar11);
                    if (human_civ == civ3) {
                      dlg_game_txt_with_unit(ADDR(0x633c2c, ((u8 *)&g.d_00633c2c)),unit2);
                    }
                    else if (2 < game.multiplayer) {
                      net_send_text_args(0x51,*(i32 *)
                                               (&net_player_slots +
                                               *(int *)(&net_civ_slots + civ3 * 4) * 0x54),3,0,
                                         unit2,0);
                    }
                  }
                  if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
                     (autoplay_active == 0)) {
                    iVar11 = civ_name_plural(civ);
                    text_set_string_arg(0,iVar11);
                    text_set_label_arg(1,unit_types[units[unit2].type].name);
                    text_set_string_arg(2,(iptr)&cities[city].name);
                    iVar11 = civ_name_plural(civ3);
                    text_set_string_arg(3,iVar11);
                    if (human_civ == civ2) {
                      dlg_game_txt_with_unit(ADDR(0x633c3c, ((u8 *)&g.d_00633c3c)),unit2);
                    }
                    else if (2 < game.multiplayer) {
                      net_send_text_args(0x52,*(i32 *)
                                               (&net_player_slots +
                                               *(int *)(&net_civ_slots + civ2 * 4) * 0x54),4,0,
                                         unit2,0);
                    }
                  }
                  if (game.multiplayer < 3) {
                    return;
                  }
                  net_send_state_diff(0xff,2,0,0,0);
                  XD_FlushSendBuffer(5000);
                  return;
                }
              }
            }
          }
        }
      }
    }
    civ2++;
  } while( true );
}
#undef autoplay_active
#undef human_civ
#undef unit2
#undef unit
#undef civ3
#undef city
#undef local_14
#undef civ2
#undef local_c

/* 00560d95 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_38 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(12)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
void __cdecl diplo_ai_review_relations(iptr civ,uptr civ2)

{
  iptr x;
  int y;
  iptr iVar5;
  uint uVar6;
  iptr iVar4;
  int iVar7;
  uint uVar8;
  iptr city;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  local_34 = 0x6715d7a0;  /* stale stack the original reads (FRAME_PRESETS) */
  
  diplo_count_border_intruders(civ,civ2);
  city = border_intruder_city;
  if ((diplo_border_intruded_cities != 0) && ((civs[civ].treaties[civ2] & 0x2008) == 0))
  {
    x = (iptr)cities[border_intruder_city].x;
    y = (int)cities[border_intruder_city].y;
    if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
      if (*(int *)(&diplo_recent_peace_table + civ2 * 4) != 0) goto LAB_00561668;
      local_34 = diplo_border_intruder_count;
      uVar6 = _rand();
      uVar8 = (int)uVar6 >> 0x1f;
      local_2c = ((uVar6 ^ uVar8) - uVar8 & 1 ^ uVar8) - uVar8;
      if ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0) {
        diplo_border_repeat_offenses++;
      }
      if (2 < (int)((uint)civs[civ2].reputation + diplo_border_repeat_offenses)) {
        iVar7 = (uint)civs[civ2].reputation + diplo_border_repeat_offenses;
        if (iVar7 == 1 || iVar7 - 1 < 0) {
          local_38 = 0;
        }
        else {
          local_38 = _rand();
          local_38 = local_38 % (int)((uint)civs[civ2].reputation + diplo_border_repeat_offenses);
        }
        if (1 < local_38) {
          local_2c = 0;
          diplo_set_treaty_flags(civ,civ2,0x20);
        }
      }
      if ((game.turn + civ & 3U) == 0) {
        iVar7 = diplo_ask_receive_emissary(civ2,civ,x,y);
        if (iVar7 != 0) {
          if (((1 << ((byte)civ2 & 0x1f) & (int)(char)cities[city].known_to) == 0) &&
             ((int)cities[city].owner != (civ2 & 0xff))) {
            city_reveal_to_civ(city,civ2);
            map_redraw_tile_all_views(x,y);
          }
          text_set_string_arg(1,(iptr)&cities[city].name);
          if (local_2c == 0) {
            popup_game_with_sprite(ADDR(0x633cc0, ((u8 *)&g.d_00633cc0)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          }
          else {
            popup_game_with_sprite(ADDR(0x633cb4, ((u8 *)&g.d_00633cb4)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          }
        }
        diplo_session_reset();
      }
    }
    else {
      if (*(int *)(&diplo_recent_peace_table + civ2 * 4) != 0) {
        text_set_string_arg(1,(iptr)&cities[border_intruder_city].name);
        iVar5 = civ_name_plural(civ);
        text_set_string_arg(2,iVar5);
        iVar5 = civ_get_adjective(civ);
        text_set_string_arg(3,iVar5);
        popup_game_with_sprite(ADDR(0x633c54, ((u8 *)&g.d_00633c54)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
        goto LAB_00561668;
      }
      if ((civs[civ2].last_treaty_turn[civ] < game.turn) &&
         ((int)game.turn - (int)civs[civ2].last_treaty_turn[civ] < 3))
      goto LAB_00561668;
      if (diplo_border_repeat_offenses == 0) {
        diplo_eval_ai_stance(civ2,civ);
        diplo_set_attitude_arg(civ2,civ);
        if (((1 << ((byte)civ2 & 0x1f) & (int)(char)cities[city].known_to) == 0) &&
           ((int)cities[city].owner != (civ2 & 0xff))) {
          city_reveal_to_civ(city,civ2);
          tile_set_visible(x,y,1 << ((byte)civ2 & 0x1f),1,1);
          map_redraw_tile_all_views(x,y);
        }
        local_34 = diplo_border_intruder_count - 1;
        text_set_string_arg(1,(iptr)&cities[city].name);
        if (diplo_border_intruded_cities < 2) {
          popup_game_with_sprite(ADDR(0x633c68, ((u8 *)&g.d_00633c68)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
        }
        else {
          popup_game_with_sprite(ADDR(0x633c5c, ((u8 *)&g.d_00633c5c)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
        }
        goto LAB_00561668;
      }
      diplo_eval_ai_stance(civ2,civ);
      diplo_set_attitude_arg(civ2,civ);
      if (((1 << ((byte)civ2 & 0x1f) & (int)(char)cities[city].known_to) == 0) &&
         ((int)cities[city].owner != (civ2 & 0xff))) {
        city_reveal_to_civ(city,civ2);
        tile_set_visible(x,y,1 << ((byte)civ2 & 0x1f),1,1);
        map_redraw_tile_all_views(x,y);
      }
      text_set_string_arg(1,(iptr)&cities[city].name);
      if (diplo_border_intruded_cities < 2) {
        local_2c = popup_game_with_sprite(ADDR(0x633c80, ((u8 *)&g.d_00633c80)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
      }
      else {
        local_2c = popup_game_with_sprite(ADDR(0x633c74, ((u8 *)&g.d_00633c74)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
      }
      if (local_2c == 0) {
        for (unit = 0; unit < game.num_units; unit++) {
          if ((((units[unit].id != 0) && ((units[unit].flags & 4) != 0)) &&
              (units[unit].flags = units[unit].flags & 0xfffb,
              (int)units[unit].owner == civ2)) &&
             (y = city_find_nearest((int)units[unit].x,(int)units[unit].y,civ2,
                                         0xffffffff,-1), -1 < y)) {
            unit_relocate(unit,(int)cities[y].x,(int)cities[y].y,1);
            units[unit].visibility = '\0';
            units[unit].orders = -1;
            if (unit_types[units[unit].type].range != '\0') {
              units[unit].counter = '\0';
            }
          }
        }
        map_redraw_all_views(human_civ,1);
        text_set_number_arg(0,diplo_border_intruder_units);
        text_clear();
        text_append(ADDR(0x633c8c, ((u8 *)&g.d_00633c8c)));
        if (diplo_border_intruder_units == 1) {
          text_append(ADDR(0x633c98, ((u8 *)&g.d_00633c98)));
        }
        popup_game_with_sprite(ADDR(0x679640, ((u8 *)&g.d_00679640)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
      }
      else {
        if (civs[civ2].government == 6) {
LAB_00561364:
          if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 1) == 0)) {
            iVar5 = civ_get_adjective(civ2);
            text_set_string_arg(0,iVar5);
            popup_game(ADDR(0x633c9c, ((u8 *)&g.d_00633c9c)));
            civ_change_government(civ2,0);
          }
        }
        else {
          uVar6 = _rand();
          uVar8 = (int)uVar6 >> 0x1f;
          if ((((uVar6 ^ uVar8) - uVar8 & 1 ^ uVar8) != uVar8) &&
             (civs[civ2].government == 5)) goto LAB_00561364;
        }
        civ_adjust_attitude(civ,civ2,0x32);
        diplo_declare_war(civ2,civ,-1);
        iVar5 = civ_name_plural(civ);
        text_set_string_arg(1,iVar5);
        popup_game_with_sprite(ADDR(0x633cac, ((u8 *)&g.d_00633cac)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
      }
      diplo_session_reset();
    }
  }
  for (unit = 0; unit < game.num_units; unit++) {
    if (units[unit].id != 0) {
      units[unit].flags = units[unit].flags & 0xfffb;
    }
  }
LAB_00561668:
  local_c = 0;
  local_1c = 0;
  local_8 = 0;
  for (civ3 = 1; civ3 < 8; civ3++) {
    if (civs[civ2].num_advances < civs[civ3].num_advances) {
      local_1c++;
    }
    iVar4 = diplo_is_hostile(civ,civ3);
    if (iVar4 != 0) {
      local_c++;
    }
    y = local_8;
    if (((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 0x594) & 0x20) != 0) &&
       (y = local_8 + 1, civs[civ2].military_strength < civs[civ3].military_strength)) {
      y = local_8 + 2;
    }
    local_8 = y;
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
    if (local_c == 0) {
      if (civs[civ].gold < civs[civ2].gold) {
        local_34++;
      }
      if ((civs[civ].num_advances < civs[civ2].num_advances) && (game.difficulty != '\0')) {
        local_34++;
      }
      if (civs[civ2].num_advances < civs[civ].num_advances) {
        local_34--;
      }
      if (civs[civ].military_strength < civs[civ2].military_strength) {
        local_34++;
      }
      if (civs[civ2].military_strength < civs[civ].military_strength) {
        local_34--;
      }
    }
    else if ((leaders[civs[civ].tribe].attack < 1) || (1 < local_c)) {
      y = (local_c - leaders[civs[civ].tribe].attack) - 1;
      if (y < 2) {
        y = 1;
      }
      local_34 -= y;
    }
    if (civs[civ].num_advances + 8 < (uint)civs[civ2].num_advances) {
      local_34++;
    }
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0) {
    local_34 -= 2;
  }
  if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) {
    local_34--;
  }
  if ((game.power_rank[civ2] < 7) && (200 < game.turn)) {
    local_10 = 7 - (uint)game.power_rank[civ2];
    y = spaceship_race_active();
    if (y != 0) {
      local_10 = 1;
    }
    if (game.turn < 400) {
      local_10 = local_10 + 1 >> 1;
    }
    local_34 -= local_10;
  }
  if ((((game.power_rank[civ2] == 7) && (3 < civs[civ2].num_cities)) && (200 < game.turn))
     && (game.difficulty != '\0')) {
    local_10 = game.difficulty / 3 + 1;
    if (((int)((uint)civs[civ2].reputation - (int)civs[civ].field_48[civ2]
              ) <= local_8) && ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0))
    {
      local_10 = local_10 >> 1;
    }
    local_34 += local_10;
  }
  y = local_34;
  if (((civs[civ2].units_active[0x2d] != '\0') &&
      (y = local_34 - 1, civs[civ].units_active[0x2d] == '\0')) && (0 < y)) {
    y = local_34 - 2;
  }
  local_34 = y;
  y = leaders[civs[civ].tribe].attack * 3 + leaders[civs[civ].tribe].expand * 2;
  if (y < -1) {
    y = -2;
  }
  local_20 = (uint)game.power_rank[civ2] - (uint)game.power_rank[civ];
  if (local_20 < 0) {
    local_20 = local_20 / 2;
  }
  else if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
    local_20 = local_20 / 2;
  }
  local_34 = local_34 + y + local_20;
  if (((game.game_flags & 1) == 0) ||
     (((int)((uint)civs[civ2].reputation - (int)civs[civ].field_48[civ2])
       <= local_8 && ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0)))) {
    if ((uint)civs[civ].military_strength * 4 < (uint)civs[civ2].military_strength) {
      local_34--;
    }
    if ((uint)civs[civ].military_strength * 2 < (uint)civs[civ2].military_strength) {
      local_34--;
    }
    if (((uint)civs[civ].military_strength * 3) / 2 < (uint)civs[civ2].military_strength) {
      local_34--;
    }
  }
  if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
    if (civs[civ2].military_strength < civs[civ].military_strength) {
      local_34++;
    }
    if ((uint)civs[civ2].military_strength * 2 < (uint)civs[civ].military_strength) {
      local_34++;
    }
  }
  y = civ_has_wonder(civ2,6);
  if ((y != 0) || (y = civ_has_wonder(civ2,0x18), y != 0)) {
    if (local_34 < 1) {
      local_34--;
    }
    else {
      local_34 = local_34 >> 1;
    }
  }
  if (local_1c == 0) {
    local_34++;
  }
  if (civs[civ].num_advances < civs[civ2].num_advances) {
    local_34 += (1 - leaders[civs[civ].tribe].civilize);
  }
  if (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) && (local_34 < 1)) {
    local_34 = 0;
  }
  y = civ_has_wonder(civ,0x14);
  if (y != 0) {
    local_34++;
  }
  iVar7 = civ_has_wonder(civ2,0x14);
  y = local_34;
  if (iVar7 != 0) {
    if (0 < local_34) {
      local_34 = local_34 / 2;
    }
    y = local_34 - 1;
    if (-1 < local_34 - 1) {
      y = local_34 - 2;
    }
  }
  local_34 = y;
  if ((*(byte *)&civs[civ].treaties[civ2] & 1) == 0) {
    local_34 = 0;
  }
  civ_adjust_attitude(civ,civ2,local_34);
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef local_38
#undef local_34
#undef unit
#undef local_2c
#undef civ3
#undef local_20
#undef local_1c
#undef local_10
#undef local_c
#undef local_8

/* 00562021 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define civ3 (*(uptr *)(frame_ + FRAME_OFF(12)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_5c (*(i8 (*)[80])(frame_ + FRAME_OFF(20)))
#define local_c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(104)))
void __cdecl diplo_ai_seek_war_ally(uptr civ2,uptr civ)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((int)game.turn & 0x1fU) == civ2 << 2) &&
     ((int)((uint)civs[civ].reputation - (int)civs[civ2].field_48[civ]) <
      6)) {
    for (civ3 = 1; (int)civ3 < 8; civ3++) {
      if (((civ3 != civ2) && (civ3 != civ)) &&
         ((1 << ((byte)civ3 & 0x1f) & (uint)game.civs_alive) != 0)) {
        if ((((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 2) != 0) &&
            ((civs[civ2].treaties[civ] & 0x2008) == 0)) &&
           ((iVar3 = diplo_is_hostile(civ,civ3), iVar3 == 0 &&
            (((*(byte *)&civs[civ].treaties[civ2] & 1) != 0 &&
             ((*(byte *)&civs[civ].treaties[civ3] & 1) != 0)))))) {
          uVar1 = (uint)civs[civ2].military_strength * 2;
          if (uVar1 - civs[civ3].military_strength == 0 ||
              uVar1 < civs[civ3].military_strength) {
            iVar3 = diplo_ask_receive_emissary(civ,civ2,0xffffffff,0xffffffff);
            if (iVar3 == 0) {
              iVar3 = (int)civs[civ].last_treaty_turn[civ2];
              if (iVar3 <= game.turn - 0xf) {
                iVar3 = game.turn - 0xf;
              }
              civs[civ].last_treaty_turn[civ2] = (short)iVar3;
            }
            else {
              iVar3 = int_clamp(civs[civ2].gold / 100,1,10);
              advance = -1;
              local_c = -99;
              for (advance2 = 0; advance2 < 100; advance2++) {
                if (((((advances[advance2].preq[0] != -2) || (advances[advance2].preq[1] != -2)) &&
                     (iVar4 = civ_has_advance(civ,advance2), iVar4 == 0)) &&
                    ((iVar4 = civ_has_advance(civ2,advance2), iVar4 != 0 ||
                     (((iVar4 = civ_has_advance(civ3,advance2), iVar4 != 0 &&
                       ((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) == 0)) &&
                      ((iVar4 = civ_has_wonder(human_civ,0x18), iVar4 == 0 &&
                       (iVar4 = civ_has_wonder(human_civ,9), iVar4 == 0)))))))) &&
                   (local_8 = ai_advance_value(civ,advance2), local_c < local_8)) {
                  advance = advance2;
                  local_c = local_8;
                }
              }
              iVar5 = civ_name_plural(civ3);
              text_set_string_arg(1,iVar5);
              text_set_number_arg(0,iVar3 * 0x32);
              FUN_005f22d0(local_5c,s_HELPME_00633ccc);
              if ((*(byte *)&civs[civ].treaties[civ3] & 8) != 0) {
                str_append((iptr)local_5c,ADDR(0x633cd4, ((u8 *)&g.d_00633cd4)));
              }
              if (-1 < advance) {
                str_append((iptr)local_5c,ADDR(0x633cdc, ((u8 *)&g.d_00633cdc)));
                text_set_label_arg(2,advances[advance].name);
              }
              iVar4 = popup_game_with_sprite((iptr)local_5c,ADDR(0x63fc98, ((u8 *)&g.d_0063fc98)),0);
              if (iVar4 == 0) {
                iVar3 = (int)civs[civ].last_treaty_turn[civ2];
                if (iVar3 <= game.turn - 0xe) {
                  iVar3 = game.turn - 0xe;
                }
                civs[civ].last_treaty_turn[civ2] = (short)iVar3;
              }
              else {
                if (-1 < advance) {
                  iVar4 = civ_has_advance(civ2,advance);
                  if (iVar4 == 0) {
                    civ_give_advance(civ2,advance,civ3,0,0);
                  }
                  civ_give_advance(civ,advance,civ2,0,0);
                }
                diplo_set_treaty_flags(civ2,civ,0xc);
                diplo_declare_war(civ,civ3,civ2);
                diplo_set_treaty_flags(civ,civ3,0x2000);
                puVar2 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 4);
                *puVar2 = *puVar2 | 0x80800;
                civs[civ].last_treaty_turn[civ3] = game.turn;
                civs[civ].last_treaty_turn[civ2] = game.turn + 0x10;
                civs[civ2].gold += iVar3 * -0x32;
                civs[civ].gold += iVar3 * 0x32;
                status_redraw(1);
              }
            }
            diplo_session_reset();
            return;
          }
          if ((civs[civ2].military_strength < civs[civ3].military_strength) &&
             ((game.power_rank[civ] < 6 || (game.power_rank[civ2] < 6)))) {
            iVar3 = diplo_ask_receive_emissary(civ,civ2,0xffffffff,0xffffffff);
            if (iVar3 == 0) {
              iVar3 = (int)civs[civ].last_treaty_turn[civ2];
              if (iVar3 <= game.turn - 0xf) {
                iVar3 = game.turn - 0xf;
              }
              civs[civ].last_treaty_turn[civ2] = (short)iVar3;
            }
            else {
              iVar5 = civ_name_plural(civ3);
              text_set_string_arg(1,iVar5);
              text_set_label_arg(2,*(i32 *)
                                    (label_string_ids +
                                    (((civs[civ2].treaties[civ] & 8) == 0
                                     ) + 0x73) * 4));
              FUN_005f22d0(local_5c,s_CRUSADE_00633ce0);
              if ((*(byte *)&civs[civ].treaties[civ3] & 8) != 0) {
                FUN_005f22d0(local_5c,s_JIHAD_00633ce8);
              }
              iVar3 = popup_game_with_sprite((iptr)local_5c,ADDR(0x63fc98, ((u8 *)&g.d_0063fc98)),0);
              if (iVar3 == 0) {
                iVar3 = (int)civs[civ].last_treaty_turn[civ2];
                if (iVar3 <= game.turn - 0xe) {
                  iVar3 = game.turn - 0xe;
                }
                civs[civ].last_treaty_turn[civ2] = (short)iVar3;
              }
              else {
                diplo_set_treaty_flags(civ2,civ,0xc);
                diplo_declare_war(civ,civ3,civ2);
                civs[civ].last_treaty_turn[civ2] = game.turn + 0x10;
                diplo_set_treaty_flags(civ,civ3,0x2000);
                puVar2 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ3 * 4);
                *puVar2 = *puVar2 | 0x80800;
                civs[civ].last_treaty_turn[civ3] = game.turn;
              }
            }
            diplo_session_reset();
            return;
          }
        }
        puVar2 = (uint *)(civ3 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
        *puVar2 = *puVar2 & 0xfffffdff;
        if (2 < game.multiplayer) {
          net_send_state_diff(0xff,2,0,0,0);
          XD_FlushSendBuffer(5000);
        }
      }
    }
  }
  return;
}
#undef human_civ
#undef advance2
#undef civ3
#undef advance
#undef local_5c
#undef local_c
#undef local_8

/* 00579c40 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl diplo_force_war(iptr civ,iptr civ2)

{
  uint *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  diplo_clear_treaty_flags(civ,civ2,0x60);
  if (((*(byte *)&civs[civ2].treaties[civ] & 6) != 0) &&
     (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 ||
      ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)))) {
    diplo_declare_war(civ,civ2,-1);
  }
  diplo_clear_treaty_flags(civ,civ2,0xc);
  if ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0) {
    diplo_set_treaty_flags(civ,civ2,0x2000);
    civ_set_attitude(civ,civ2,100);
    civ_set_attitude(civ2,civ,100);
    if (((*(byte *)(civ2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x10) == 0) &&
       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x10) == 0)) {
      puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
      *puVar1 = *puVar1 | 0x1000;
      local_8 = 1;
    }
  }
  return local_8;
}
#undef local_8

/* 00579ed0 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl diplo_confirm_attack(iptr civ,iptr civ2,uint param_3)

{
  i32 uVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) == 0) {
    if ((param_3 & civs[civ].treaties[civ2]) == 0) {
      uVar1 = 0;
    }
    else if ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) == 0) {
      uVar1 = 0;
    }
    else {
      iVar2 = civ_name_plural(civ2);
      text_set_string_arg(1,iVar2);
      if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
          if ((*(byte *)&civs[civ].treaties[civ2] & 2) == 0) {
            local_8 = popup_game_with_sprite(ADDR(0x634348, ((u8 *)&g.d_00634348)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
          }
          else if ((*(byte *)(civ2 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 0x594) & 4) == 0) {
            local_8 = popup_game_with_sprite(ADDR(0x63433c, ((u8 *)&g.d_0063433c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          }
          else {
            local_8 = popup_game_with_sprite(ADDR(0x634330, ((u8 *)&g.d_00634330)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
          }
        }
        else {
          local_8 = popup_game_with_sprite(ADDR(0x634324, ((u8 *)&g.d_00634324)),ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),0);
        }
        if (local_8 == 1) {
          iVar3 = diplo_senate_intervenes(civ,civ2);
          if (iVar3 == 0) {
            if (4 < civs[civ].government) {
              iVar3 = civ_has_wonder(civ2,0x18);
              if (iVar3 == 0) {
                if (((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 0x10) == 0) &&
                   (civs[civ2].reputation == '\0')) {
                  popup_game_with_sprite(ADDR(0x634374, ((u8 *)&g.d_00634374)),(iptr)(&government_sprites +
                                                    (uint)civs[civ].government * 0x3c),0);
                }
                else {
                  iVar2 = civ_get_adjective(civ2);
                  text_set_string_arg(0,iVar2);
                  popup_game_with_sprite(ADDR(0x634364, ((u8 *)&g.d_00634364)),(iptr)(&government_sprites +
                                                    (uint)civs[civ].government * 0x3c),0);
                }
              }
              else {
                popup_game_with_sprite(ADDR(0x63435c, ((u8 *)&g.d_0063435c)),(iptr)(&government_sprites +
                                                  (uint)civs[civ].government * 0x3c),0);
              }
            }
            uVar1 = 0;
          }
          else {
            popup_game_with_sprite(ADDR(0x634350, ((u8 *)&g.d_00634350)),(iptr)(&government_sprites + (uint)civs[civ].government * 0x3c
                                              ),0);
            uVar1 = 1;
          }
        }
        else {
          uVar1 = 1;
        }
      }
      else {
        popup_game_with_sprite(ADDR(0x634318, ((u8 *)&g.d_00634318)),(iptr)(&diplo_popup_portrait_sprite +
                                          ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0
                          );
        uVar1 = 1;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef local_8
