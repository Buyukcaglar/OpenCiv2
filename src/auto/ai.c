/* The game, the computer players: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00442885 auto */
#define dir (*(uptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl ai_city_touches_landmass(iptr city,int landmass)

{
  short x2;
  short y2;
  int y;
  i32 result;
  iptr x;
  int check;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = cities[city].x;
  y2 = cities[city].y;
  y = tile_landmass((int)x2,(int)y2);
  if (y == landmass) {
    result = 1;
  }
  else {
    for (dir = 0; (int)dir < 8; dir++) {
      x = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)x2);
      y = (int)(char)(&dir_dy_table)[dir] + (int)y2;
      check = map_in_bounds(x,y);
      if ((check != 0) && (check = tile_is_ocean(x,y), check != 0)) {
        x = tile_landmass(x,y);
        y = landmass_borders_body(landmass,x);
        if (y != 0) {
          return 1;
        }
        dir += (2 - (dir & 1));
      }
    }
    result = 0;
  }
  return result;
}
#undef dir

/* 004bdb2c auto */
#define size_needed (*(uint *)(frame_ + FRAME_OFF(4)))
#define civilize_mod (*(int *)(frame_ + FRAME_OFF(8)))
#define free_continent (*(int *)(frame_ + FRAME_OFF(12)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(16)))
#define city (*(iptr *)(frame_ + FRAME_OFF(20)))
#define continent (*(iptr *)(frame_ + FRAME_OFF(24)))
#define max_size (*(int *)(frame_ + FRAME_OFF(28)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define wonder (*(iptr *)(frame_ + FRAME_OFF(40)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define expand_bonus (*(uint *)(frame_ + FRAME_OFF(48)))
#define value (*(int *)(frame_ + FRAME_OFF(56)))
int __cdecl ai_advance_value(iptr civ,iptr advance)

{
  byte size_limit;
  bool human_contact;
  bool contested;
  iptr settler_prereq;
  iptr has_prereq;
  int check;
  int city2;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  civilize_mod = (int)leaders[civs[civ].tribe].civilize;
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) && (-1 < civilize_mod)) {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
          ((*(byte *)(civ2 * 4 + (iptr)((u8 *)&civs + 33) + civ * 0x594) & 0x20) != 0)) &&
         (civs[civ].num_advances < civs[civ2].num_advances)) {
        for (continent = 1; continent < 0x3f; continent++) {
          if ((*(char *)&civs[civ].continent_cities[continent] != '\0') &&
             (*(char *)&civs[civ2].continent_cities[continent] != '\0')) {
            if (-1 < civilize_mod) {
              civilize_mod--;
            }
            if (6 < civs[civ2].reputation) {
              civilize_mod = -1;
            }
          }
        }
      }
    }
  }
  value = advances[advance].civilized_mod * civilize_mod + (int)advances[advance].ai_value;
  settler_prereq = advance_has_prereq((int)unit_types[0x20].prerequisite,advance);
  if (settler_prereq == 0) {
    city2 = advance_has_prereq((int)unit_types[0x21].prerequisite,advance);
    if ((city2 == 0) &&
       (city2 = advance_has_prereq((int)unit_types[0x23].prerequisite,advance), city2 == 0)) {
      city2 = advance_has_prereq((int)unit_types[0x2b].prerequisite,advance);
      if (city2 == 0) {
        expand_bonus = 0;
      }
      else {
        expand_bonus = 1;
      }
    }
    else {
      expand_bonus = 2;
    }
  }
  else {
    expand_bonus = 3;
  }
  if ((game.game_flags & 4) != 0) {
    expand_bonus = expand_bonus << 1;
  }
  if (expand_bonus != 0) {
    free_continent = 0;
    human_contact = false;
    for (continent = 1; continent < 0x3f; continent++) {
      if (*(char *)&civs[civ].continent_cities[continent] != '\0') {
        contested = false;
        for (civ2 = 0; civ2 < 8; civ2++) {
          if ((civ != civ2) &&
             ((*(char *)&civs[civ].continent_cities[continent] != '\0' ||
              (*(short *)&civs[civ].continent_military[continent] != 0)))) {
            contested = true;
            if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
              human_contact = true;
            }
            break;
          }
        }
        if (!contested) {
          free_continent = 1;
          break;
        }
      }
    }
    if (free_continent == 0) {
      if ((!human_contact) || ((game.game_flags & 4) != 0)) {
        value++;
      }
    }
    else {
      value += expand_bonus;
    }
  }
  if (improvements[0x22].preq == advance) {
    value = value + ((int)((int)civs[civ].num_ships +
                              ((int)civs[civ].num_ships >> 0x1f & 3U)) >> 2);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    if ((game.human_players & game.advance_known_by[0x4c]) != 0) {
      has_prereq = advance_has_prereq(0x20,advance);
      if (has_prereq != 0) {
        value += 2;
      }
      for (improvement = 0x23; improvement < 0x26; improvement++) {
        if (improvements[improvement].preq == advance) {
          value += 3;
        }
      }
    }
    city2 = value;
    if ((((-1 < unit_types[0x1c].prerequisite) &&
         ((game.human_players & game.advance_known_by[unit_types[0x1c].prerequisite]) != 0)) &&
        (check = advance_has_prereq((int)unit_types[0x1c].prerequisite,advance), check != 0)) &&
       (city2 = value + 2, unit_types[0x1c].prerequisite == advance)) {
      city2 = value + 5;
    }
    value = city2;
    for (wonder = 0; wonder < 0x1c; wonder++) {
      if (wonder_expires[wonder] == advance) {
        city2 = civ_has_wonder(civ,wonder);
        if ((city2 != 0) && (advance != 0x25)) {
          value -= 2;
        }
        city2 = wonder_get_city(wonder);
        if ((-1 < city2) && (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0))
        {
          value += 2;
        }
      }
    }
  }
  if ((improvements[9].preq == advance) || (improvements[0x17].preq == advance)) {
    max_size = 0;
    for (city = 0; city < game.num_cities; city++) {
      city2 = max_size;
      if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
         (city2 = (int)cities[city].size, cities[city].size <= max_size)) {
        city2 = max_size;
      }
      max_size = city2;
    }
    size_limit = cosmic.sewer_size;
    if (improvements[9].preq == advance) {
      size_limit = cosmic.aqueduct_size;
    }
    size_needed = (uint)size_limit;
    if ((int)size_needed <= max_size) {
      value += 2;
    }
  }
  if ((-1 < leaders[civs[civ].tribe].civilize) &&
     (city2 = civ_has_advance(civ,0x55), city2 != 0)) {
    city2 = advance_has_prereq(0x10,advance);
    if (city2 != 0) {
      value = value + leaders[civs[civ].tribe].civilize + 1;
    }
    if (advance == 0x10) {
      value += 2;
    }
  }
  check = civ_has_advance(civ,0x26);
  city2 = value;
  if ((check != 0) && (check = advance_has_prereq(0x25,advance), check != 0)) {
    check = civ_has_advance(civ,0x39);
    city2 = value + 1;
    if (check != 0) {
      city2 = value + 2;
    }
  }
  value = city2;
  switch(civs[civ].tribe) {
  case 0:
    if (((advance == 0x27) || (advance == 8)) || (advance == 0x56)) {
      value += 2;
    }
    if (advance == 0x37) {
      value--;
    }
    break;
  case 1:
    if (advance == 0xc) {
      value++;
    }
    break;
  case 2:
    if (advance == 6) {
      value++;
    }
    if (advance == 0x52) {
      value++;
    }
    if (advance == 0x3c) {
      value++;
    }
    break;
  case 3:
    if (advance == 0x2f) {
      value += 2;
    }
    break;
  case 4:
    if (advance == 0x15) {
      value += 2;
    }
    if (advance == 0xf) {
      value--;
    }
    if (advance == 0x49) {
      value++;
    }
    if (advance == 0x10) {
      value++;
    }
    if (advance == 0x2a) {
      value++;
    }
    break;
  case 5:
    if (advance == 0x40) {
      value++;
    }
    if (advance == 8) {
      value++;
    }
    if (advance == 1) {
      value++;
    }
    if (advance == 0x2e) {
      value++;
    }
    if (advance == 0x37) {
      value--;
    }
    if (advance == 0x3c) {
      value += 2;
    }
    break;
  case 6:
    if (advance == 0x40) {
      value += 2;
    }
    if (advance == 0x24) {
      value++;
    }
    if (advance == 0x38) {
      value++;
    }
    if (advance == 9) {
      value++;
    }
    if (advance == 0x37) {
      value--;
    }
    break;
  case 7:
    if (advance == 0xf) {
      value += 2;
    }
    if (advance == 0x3c) {
      value++;
    }
    if (advance == 0x22) {
      value++;
    }
    break;
  case 8:
    if (advance == 0x40) {
      value += 2;
    }
    if (advance == 0x24) {
      value++;
    }
    if (advance == 0x38) {
      value++;
    }
    if (advance == 9) {
      value++;
    }
    if (advance == 8) {
      value--;
    }
    if (advance == 0x27) {
      value--;
    }
    break;
  case 9:
    if (advance == 0x2a) {
      value++;
    }
    if (advance == 0x51) {
      value++;
    }
    if (advance == 0x11) {
      value++;
    }
    break;
  case 10:
    if (advance == 0x23) {
      value -= 2;
    }
    if (advance == 0x37) {
      value--;
    }
    break;
  case 0xb:
    if (free_continent != 0) {
      value -= expand_bonus;
    }
    if (advance == 0x23) {
      value++;
    }
    break;
  case 0xc:
    if (advance == 0x37) {
      value++;
    }
    if (expand_bonus != 0) {
      value++;
    }
    break;
  case 0xf:
    if (advance == 0x4f) {
      value++;
    }
    if (advance == 0x34) {
      value++;
    }
    break;
  case 0x10:
    if (advance == 0x2e) {
      value++;
    }
    break;
  case 0x11:
    if (1 < expand_bonus) {
      value++;
    }
    if (advance == 0x37) {
      value++;
    }
    break;
  case 0x12:
  case 0x13:
    if (advance == 0x40) {
      value += 2;
    }
    if (advance == 0x24) {
      value++;
    }
    if (advance == 0x38) {
      value++;
    }
    if (advance == 9) {
      value++;
    }
    if (advance == 0x37) {
      value--;
    }
    break;
  case 0x14:
    if (advance == 0x24) {
      value += 2;
    }
  }
  if (game.advance_known_by[advance] == '\0') {
    value++;
  }
  for (advance2 = 0; advance2 < 100; advance2++) {
    if (((advances[advance2].preq[0] == advance) || (advances[advance2].preq[1] == advance)) &&
       (city2 = civ_has_advance(civ,advance2), city2 != 0)) {
      value--;
    }
  }
  if (value < 2) {
    value = 1;
  }
  return value;
}
#undef size_needed
#undef civilize_mod
#undef free_continent
#undef improvement
#undef city
#undef continent
#undef max_size
#undef advance2
#undef wonder
#undef civ2
#undef expand_bonus
#undef value

/* 004f03b7 auto */
#define city_tile_job_found (*(i32 *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_x (*(int *)((u8 *)&g.d_006a65e0))
#define city_tile_job_y (*(int *)((u8 *)&g.d_006a65e8))
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(i32 *)((u8 *)&g.d_0062d044))
#define path_road_planning (*(i32 *)((u8 *)&g.d_0062d040))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define steps (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(32)))
#define pass (*(int *)(frame_ + FRAME_OFF(36)))
i32 __cdecl ai_find_road_link_tile(iptr city)

{
  bool road_ok;
  iptr landmass;
  int civ;
  int x;
  int y;
  iptr landmass2;
  iptr distance;
  int dir;
  uint tile_imps;
  byte *tile;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  landmass = tile_land_landmass((int)cities[city].x,(int)cities[city].y);
  civ = (int)cities[city].owner;
  if (1 < civs[civ].continent_cities[landmass]) {
    for (pass = 0; pass < 2; pass++) {
      for (city2 = 0; city2 < game.num_cities; city2++) {
        if (((cities[city2].id != 0) && (city != city2)) &&
           ((cities[city2].owner == civ ||
            ((pass != 0 &&
             ((*(byte *)&civs[civ].treaties[cities[city2].owner] & 0xc) != 0)))))) {
          x = (int)cities[city2].x;
          y = (int)cities[city2].y;
          x2 = (int)cities[city].x;
          y2 = (int)cities[city].y;
          steps = 0;
          landmass2 = tile_land_landmass(x,y);
          if ((landmass == landmass2) &&
             (distance = map_distance(x,y,x2,y2), distance < 0x17)) {
            path_road_planning = 1;
            path_owner_civ = 0xffffffff;
            path_unit_type = 2;
            road_ok = true;
            path_goal_x = x;
            path_goal_y = y;
            while ((dir = map_path_next_dir(x2,y2,99), -1 < dir && (dir != 8))) {
              x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
              y2 += (char)(&dir_dy_table)[dir];
              if ((x2 == x) && (y2 == y)) break;
              dir = tile_city_owner(x2,y2);
              if (dir < 0) {
                tile_imps = tile_improvements(x2,y2);
                if ((tile_imps & 0x10) == 0) {
                  tile = (byte *)tile_at(x2,y2);
                  if (((*tile & 0x80) == 0) || (dir = civ_has_advance(civ,7), dir != 0))
                  {
                    road_ok = false;
                  }
                }
                else {
                  tile_imps = tile_improvements(x2,y2);
                  if (((tile_imps & 0x20) == 0) && (dir = civ_has_advance(civ,0x43), dir != 0))
                  {
                    road_ok = false;
                  }
                }
              }
              steps++;
              if ((0x32 < steps) || (!road_ok)) break;
            }
            path_road_planning = 0;
            if (((!road_ok) &&
                ((x = tile_city_or_unit_owner(x2,y2), x < 0 || (civ == x))
                )) && ((x = tile_owner_at_peace(x2,y2,civ), x < 0 ||
                       (civ == x)))) {
              city_tile_job_found = 1;
              city_tile_job_x = x2;
              city_tile_job_y = y2;
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}
#undef city_tile_job_found
#undef city_tile_job_x
#undef city_tile_job_y
#undef path_goal_x
#undef path_goal_y
#undef path_owner_civ
#undef path_road_planning
#undef city2
#undef steps
#undef y2
#undef x2
#undef pass

/* 00531287 auto */
#define ai_role (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl ai_unit_role(iptr unit)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ai_role = (int)(char)unit_types[units[unit].type].role;
  if ((ai_role == 5) && ((units[unit].flags & 0x200) != 0)) {
    ai_role = 0x15;
  }
  return ai_role;
}
#undef ai_role

/* 005312e4 auto */
#define best_dir (*(iptr *)(frame_ + FRAME_OFF(4)))
#define dir2 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define owner_byte (*(byte *)(frame_ + FRAME_OFF(28)))
#define dir (*(iptr *)(frame_ + FRAME_OFF(32)))
#define best_score (*(int *)(frame_ + FRAME_OFF(36)))
#define score (*(int *)(frame_ + FRAME_OFF(40)))
iptr __cdecl ai_ship_best_landing_dir(iptr unit)

{
  short x3;
  short y3;
  int civ;
  iptr x2;
  int y2;
  int y;
  iptr x;
  int owner_civ;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  x3 = units[unit].x;
  y3 = units[unit].y;
  civ = (int)units[unit].owner;
  best_score = -1;
  best_dir = -1;
  for (dir = 0; dir < 9; dir++) {
    x2 = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)x3);
    y2 = (int)(char)(&dir_dy_table)[dir] + (int)y3;
    y = map_in_bounds(x2,y2);
    if (((y != 0) && (y = tile_is_ocean(x2,y2), y != 0)) &&
       ((dir == 8 || (y = tile_unit_owner(x2,y2), y < 0)))) {
      score = 0;
      for (dir2 = 0; dir2 < 8; dir2++) {
        x = map_wrap_x((char)(&dir_dx_table)[dir2] + x2);
        y = (char)(&dir_dy_table)[dir2] + y2;
        owner_civ = map_in_bounds(x,y);
        if ((((owner_civ != 0) && (owner_civ = tile_is_ocean(x,y), owner_civ == 0)) &&
            (owner_civ = tile_unit_owner(x,y), owner_civ < 0)) &&
           (((owner_civ = tile_owner_or_fertility(x,y), 7 < owner_civ ||
             (owner_byte = (byte)owner_civ, (1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0)) ||
            ((*(byte *)&civs[civ].treaties[owner_civ] & 6) == 0)))) {
          owner_civ = tile_city_owner(x,y);
          if (((-1 < owner_civ) && (owner_civ != civ)) &&
             ((y = tile_unit_owner(x,y), y < 0 &&
              ((y = diplo_is_hostile(civ,owner_civ), y != 0 && (dir == 8)))))) {
            score += 0xc;
          }
          score++;
        }
      }
      if (best_score <= score) {
        best_score = score;
        best_dir = dir;
      }
    }
  }
  return best_dir;
}
#undef best_dir
#undef dir2
#undef owner_byte
#undef dir
#undef best_score
#undef score

/* 00531653 auto */
#define dest_y (*(int *)(frame_ + FRAME_OFF(4)))
#define dest_x (*(iptr *)(frame_ + FRAME_OFF(8)))
#define dir (*(iptr *)(frame_ + FRAME_OFF(24)))
#define offset (*(iptr *)(frame_ + FRAME_OFF(32)))
void __cdecl ai_ship_goto_near_shore(iptr unit,i32 goto_mode,iptr x,int y)

{
  bool found_land;
  int ship_landmass;
  int target_landmass;
  iptr x3;
  int y3;
  int y2;
  iptr x2;
  int check;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  dest_x = x;
  dest_y = y;
  ship_landmass = tile_landmass((int)units[unit].x,(int)units[unit].y);
  target_landmass = tile_landmass(x,y);
  for (offset = 0; y3 = dest_y, x3 = dest_x, offset < 0x14; offset++) {
    x3 = map_wrap_x((char)(&city_tile_dx_table)[offset] + x);
    y3 = (char)(&city_tile_dy_table)[offset] + y;
    y2 = map_in_bounds(x3,y3);
    if (((y2 != 0) && (y2 = tile_is_ocean(x3,y3), y2 != 0)) &&
       (y2 = tile_landmass(x3,y3), y2 == ship_landmass)) {
      found_land = false;
      for (dir = 0; dir < 8; dir++) {
        x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x3);
        y2 = (char)(&dir_dy_table)[dir] + y3;
        check = map_in_bounds(x2,y2);
        if (((check != 0) && (check = tile_is_ocean(x2,y2), check == 0)) &&
           ((check = tile_landmass(x2,y2), check == target_landmass &&
            (y2 = tile_city_owner(x2,y2), y2 < 0)))) {
          found_land = true;
        }
      }
      if (found_land) break;
    }
  }
  dest_x = x3;
  dest_y = y3;
  unit_set_goto(unit,goto_mode,dest_x,dest_y);
  return;
}
#undef dest_y
#undef dest_x
#undef dir
#undef offset

/* 0053184d auto */
#define city_calc_cached_id (*(i32 *)((u8 *)&g.d_0062ee08))
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define density (*(int *)(frame_ + FRAME_OFF(0)))
#define unit (*(uptr *)(frame_ + FRAME_OFF(20)))
#define settler_divisor (*(int *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(36)))
#define attack_count (*(int *)(frame_ + FRAME_OFF(40)))
#define goal_weight (*(int (*)[48])(frame_ + FRAME_OFF(44)))
#define is_human (*(uint *)(frame_ + FRAME_OFF(236)))
#define continent (*(iptr *)(frame_ + FRAME_OFF(240)))
#define unit_type (*(uptr *)(frame_ + FRAME_OFF(244)))
#define old_policy (*(uint *)(frame_ + FRAME_OFF(248)))
#define y2 (*(int *)(frame_ + FRAME_OFF(252)))
#define x3 (*(int *)(frame_ + FRAME_OFF(256)))
#define base_density (*(int *)(frame_ + FRAME_OFF(260)))
#define ai_role (*(int *)(frame_ + FRAME_OFF(264)))
#define scenario_mode (*(int *)(frame_ + FRAME_OFF(268)))
#define x2 (*(int *)(frame_ + FRAME_OFF(272)))
#define crowded (*(uint *)(frame_ + FRAME_OFF(276)))
#define settler_count (*(int (*)[64])(frame_ + FRAME_OFF(280)))
#define done (*(int *)(frame_ + FRAME_OFF(536)))
#define rival_military (*(int *)(frame_ + FRAME_OFF(540)))
#define threat_count (*(int *)(frame_ + FRAME_OFF(544)))
#define settlers_total (*(int *)(frame_ + FRAME_OFF(548)))
#define settle_goals (*(int (*)[64])(frame_ + FRAME_OFF(552)))
#define wonder (*(int *)(frame_ + FRAME_OFF(808)))
#define y3 (*(int *)(frame_ + FRAME_OFF(812)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(816)))
#define defend_count (*(int *)(frame_ + FRAME_OFF(820)))
#define goal_dist (*(int *)(frame_ + FRAME_OFF(824)))
#define goal_idx (*(iptr *)(frame_ + FRAME_OFF(828)))
#define rival_cities (*(int *)(frame_ + FRAME_OFF(832)))
#define goal (*(iptr *)(frame_ + FRAME_OFF(836)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(840)))
#define land_city_count (*(int *)(frame_ + FRAME_OFF(844)))
#define best_dist (*(int *)(frame_ + FRAME_OFF(848)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(852)))
#define group (*(iptr *)(frame_ + FRAME_OFF(856)))
#define best_goal (*(iptr *)(frame_ + FRAME_OFF(860)))
#define settler_quota (*(int *)(frame_ + FRAME_OFF(864)))
void __cdecl ai_civ_turn_assess(uptr civ)

{
  char *counter;
  short *mil_counter;
  byte city2;
  u16 saved_flags;
  iptr has_para;
  iptr occupant;
  int city6;
  int y;
  int dist;
  uptr owner_civ;
  iptr unit2;
  uptr city5;
  uint tile_imps;
  i32 imps;
  i8 frame_[FRAME_OFF(872)] __attribute__((aligned(8)));  /* original stack frame */
  
  settlers_total = 0;
  scenario_mode = 0;
  has_para = civ_has_advance(civ,(int)unit_types[0xd].prerequisite);
  if (((has_para != 0) && (civs[civ].units_active[0xd] != '\0')) &&
     ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && ((int)cities[city].owner != civ)) &&
         ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + cities[city].owner * 4) & 0x20) != 0)) {
        x2 = (int)cities[city].x;
        y2 = (int)cities[city].y;
        occupant = tile_unit_owner(x2,y2);
        if (occupant < 0) {
          for (city3 = 0; city3 < game.num_cities; city3++) {
            if ((cities[city3].id != 0) && ((int)cities[city3].owner == civ)) {
              city6 = (int)cities[city3].x;
              y3 = (int)cities[city3].y;
              y = map_distance(x2,y2,city6,y3);
              if (y <= (int)(uint)cosmic.paradrop_range) {
                done = 0;
                for (unit = tile_first_unit(city6,y3); -1 < (int)unit;
                    unit = unit_next_in_stack(unit)) {
                  if ((unit_types[units[unit].type].flags & 0x100) != 0) {
                    done = 1;
                    break;
                  }
                }
                if (done != 0) break;
                for (city4 = 0; city4 < game.num_cities; city4++) {
                  if (2 < game.multiplayer) {
                    net_process_messages((NetSession *)&net_session,1,0);
                  }
                  if ((cities[city4].id != 0) && ((int)cities[city4].owner == civ)) {
                    x3 = (int)cities[city4].x;
                    y = (int)cities[city4].y;
                    dist = map_distance(x2,y2,x3,y);
                    if (((int)(uint)cosmic.paradrop_range < dist) &&
                       (dist = map_distance(city6,y3,x3,y),
                       dist <= (int)(uint)cosmic.paradrop_range)) {
                      for (unit = tile_first_unit(x3,y); -1 < (int)unit;
                          unit = unit_next_in_stack(unit)) {
                        if (((unit_types[units[unit].type].flags & 0x100) != 0) &&
                           (y = unit_moves_left(unit), y != 0)) {
                          unit_relocate(unit,city6,y3,1);
                          units[unit].visibility = '\0';
                          unit_exhaust_moves(unit);
                          done = 1;
                          break;
                        }
                      }
                      if (done != 0) break;
                    }
                  }
                }
                if (done != 0) break;
              }
            }
          }
        }
      }
    }
  }
  for (group = 0; group < 4; group++) {
    *(i8 *)&civs[civ].wonders_by_group[group] = 0;
  }
  for (wonder = 0; wonder < 0x1c; wonder++) {
    city6 = civ_has_wonder(civ,wonder);
    if (city6 != 0) {
      group = wonder / 7;
      counter = (char *)(group + (iptr)((u8 *)&civs + 23) + civ * 0x594);
      *counter = *counter + 1;
    }
  }
  for (continent = 0; continent < 0x40; continent++) {
    *(i16 *)&civs[civ].continent_military[continent] = 0;
    *(i16 *)&civs[civ].continent_attack[continent] = 0;
    *(i8 *)&civs[civ].continent_city_size[continent] = 0;
    *(i8 *)&civs[civ].continent_trade_units[continent] = 0;
    *(i8 *)&civs[civ].continent_flags[continent] = 0;
    settler_count[continent] = 0;
    settle_goals[continent] = 0;
  }
  *(i32 *)(&civ_unit_counts + civ * 4) = 0;
  civs[civ].num_military_units = 0;
  civs[civ].num_cities = 0;
  civs[civ].num_ships = 0;
  civs[civ].total_city_size = 0;
  civs[civ].military_strength = 0;
  civs[civ].total_attack = 0;
  for (unit_type = 0; (int)unit_type < 0x3e; unit_type++) {
    *(i8 *)&civs[civ].units_active[unit_type] = 0;
    *(i8 *)&civs[civ].units_in_production[unit_type] = 0;
  }
  for (goal = 0; goal < 0x30; goal++) {
    if ((civs[civ].ai_goals[goal].role == 21) &&
       ('\0' < civs[civ].ai_goals[goal].priority)) {
      continent = tile_land_landmass((int)civs[civ].ai_goals[goal].x,
                                     (int)civs[civ].ai_goals[goal].y);
      if (-1 < continent) {
        settle_goals[continent]++;
      }
    }
  }
  for (unit = 0; (int)unit < (int)game.num_units; unit++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (((units[unit].id != 0) && ((int)units[unit].owner == civ)) &&
       (units[unit].flags = units[unit].flags & 0xfc7f,
       unit_types[units[unit].type].role == 5)) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        units[unit].flags = units[unit].flags | 0x200;
      }
      if (units[unit].home_city == -1) {
        settlers_total++;
        city6 = tile_is_ocean((int)units[unit].x,(int)units[unit].y);
        if (city6 == 0) {
          units[unit].flags = units[unit].flags | 0x200;
          city6 = tile_landmass((int)units[unit].x,(int)units[unit].y);
          settler_count[city6]++;
          city6 = city_find_nearest((int)units[unit].x,(int)units[unit].y,-1,0xffffffff,
                                     -1);
          if ((nearest_city_dist < 4) && ((int)cities[city6].owner == civ)) {
            cities[city6].flags = cities[city6].flags | 0x40;
          }
        }
      }
    }
  }
  for (unit = 0; (int)unit < (int)game.num_units; unit++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (units[unit].id != 0) {
      if ((int)units[unit].owner == civ) {
        unit_type = (uptr)units[unit].type;
        counter = (char *)(unit_type + (iptr)((u8 *)&civs + 216) + civ * 0x594);
        *counter = *counter + 1;
        if ((char)unit_types[unit_type].attack < 'c') {
          if ((units[unit].orders == 1) || (units[unit].orders == 2)) {
            units[unit].flags = units[unit].flags | 0x100;
          }
          x2 = (int)units[unit].x;
          y2 = (int)units[unit].y;
          city6 = map_in_bounds(x2,y2);
          if (city6 == 0) {
            continent = -1;
            unit_set_sleep(unit);
          }
          else {
            continent = tile_land_landmass(x2,y2);
            if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
              if ((units[unit].orders == 3) &&
                 ((unit_types[unit_type].domain != '\0' ||
                  (city6 = tile_is_ocean(x2,y2), city6 == 0)))) {
                units[unit].orders = -1;
              }
              if (15 < units[unit].orders) {
                units[unit].orders = -1;
              }
              if ((units[unit].orders == -1) &&
                 (city6 = tile_zoc_unit_adjacent(x2,y2,civ), city6 != 0)) {
                units[unit].orders = 16;
              }
            }
            city6 = tile_is_ocean(x2,y2);
            if ((city6 != 0) && (unit_types[units[unit].type].domain == '\0')) {
              unit_set_sleep(unit);
            }
          }
          *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) + 1;
          if (((char)unit_types[unit_type].role < 5) &&
             (civs[civ].num_military_units = civs[civ].num_military_units + 1,
             -1 < continent)) {
            mil_counter = (short *)(continent * 2 + (iptr)((u8 *)&civs + 402) + civ * 0x594);
            *mil_counter = *mil_counter + 1;
          }
          if (((unit_types[units[unit].type].role == 7) &&
              (units[unit].home_city != -1)) &&
             (cities[(byte)units[unit].home_city].flags =
                   cities[(byte)units[unit].home_city].flags | 0x1000, -1 < continent)) {
            counter = (char *)(continent + (iptr)((u8 *)&civs + 786) + civ * 0x594);
            *counter = *counter + 1;
          }
          if ((unit_types[unit_type].role == 5) && (units[unit].home_city != -1)) {
            settlers_total++;
            if (continent < 0) goto LAB_0053232b;
            settler_count[continent]++;
            if (*(char *)&civs[civ].continent_cities[continent] != '\0') {
              if (civs[civ].government < 2) {
                settler_divisor = 4;
              }
              else if (civs[civ].government < 5) {
                settler_divisor = 3;
              }
              else {
                settler_divisor = 2;
              }
              settler_quota = (int)(((settler_divisor >> 1) - (int)leaders[civs[civ].tribe].expand) - 1 +
                             (uint)civs[civ].continent_cities[continent]) / settler_divisor;
              if (unit_type == 1) {
                settler_quota++;
              }
              city6 = settle_goals[continent];
              if (settler_quota <= settle_goals[continent]) {
                city6 = settler_quota;
              }
              settler_quota = city6;
              if (settler_count[continent] <= city6) {
                units[unit].flags = units[unit].flags | 0x200;
              }
            }
            if (units[unit].home_city != -1) {
              city2 = units[unit].home_city;
              if ((((cities[city2].flags & 0x40) != 0) && ((units[unit].flags & 0x200) != 0))
                 && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
                settler_count[continent]--;
                units[unit].flags = units[unit].flags & 0xfdff;
              }
              if (((units[unit].flags & 0x200) != 0) &&
                 (city6 = map_distance_diag(x2,y2,(int)cities[city2].x,
                                             (int)cities[city2].y), city6 < 5)) {
                cities[city2].flags = cities[city2].flags | 0x40;
              }
            }
          }
          if (unit_types[units[unit].type].domain == 2) {
            civs[civ].num_ships++;
          }
          civs[civ].total_attack =
               (short)(char)unit_types[unit_type].attack + civs[civ].total_attack;
          civs[civ].military_strength =
               (short)(char)unit_types[unit_type].attack +
               (short)(char)unit_types[unit_type].defense + civs[civ].military_strength;
          if (-1 < continent) {
            *(short *)&civs[civ].continent_attack[continent] =
                 *(short *)&civs[civ].continent_attack[continent] +
                 (short)(char)unit_types[unit_type].attack;
          }
        }
      }
      else if ((((game.rules & 0x10) != 0) &&
               ((*(byte *)&civs[civ].treaties[units[unit].owner] & 6) == 0)) &&
              (((1 << ((byte)civ & 0x1f) & (uint)units[unit].visibility) != 0 ||
               ((int)units[unit].owner == (civ & 0xff))))) {
        city6 = unit_max_hp(unit);
        y = unit_hp_remaining(unit);
        if (y <= city6 / 2) {
          y = 1;
          city6 = tile_is_ocean((int)units[unit].x,(int)units[unit].y);
          civ_add_ai_goal(civ,(int)units[unit].x,(int)units[unit].y,
                             (city6 == 0) - 1 & 2,y);
        }
      }
    }
LAB_0053232b: ;
  }
  for (continent = 0; continent < 0x40; continent++) {
    *(i8 *)&civs[civ].continent_cities[continent] = 0;
  }
  land_city_count = 0;
  for (city = 0; city < game.num_cities; city++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (cities[city].id != 0) {
      x2 = (int)cities[city].x;
      y2 = (int)cities[city].y;
      city6 = map_in_bounds(x2,y2);
      if (city6 != 0) {
        if ((int)cities[city].owner == civ) {
          civs[civ].num_cities++;
          civs[civ].total_city_size =
               (short)cities[city].size + civs[civ].total_city_size;
          if (-1 < cities[city].building) {
            counter = (char *)(cities[city].building + (iptr)((u8 *)&civs + 340) + civ * 0x594);
            *counter = *counter + 1;
          }
          continent = tile_land_landmass(x2,y2);
          if (-1 < continent) {
            *(char *)&civs[civ].continent_city_size[continent] =
                 *(char *)&civs[civ].continent_city_size[continent] + cities[city].size;
            counter = (char *)(continent + (iptr)((u8 *)&civs + 658) + civ * 0x594);
            *counter = *counter + 1;
            if ((0 < continent) && (continent < 0x3f)) {
              land_city_count++;
            }
          }
          city6 = tile_unit_owner(x2,y2);
          if (city6 < 0) {
            civ_add_ai_goal(civ,x2,y2,1,5);
          }
        }
        else if ((((200 < (int)((uint)game.difficulty * (int)game.turn)) ||
                  ((1 << ((byte)civ & 0x1f) & (int)(char)cities[city].known_to) != 0)) ||
                 ((int)cities[city].owner == (civ & 0xff))) ||
                (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) == 0)) {
          city6 = diplo_is_hostile(civ,(int)cities[city].owner);
          if (((city6 != 0) ||
              (((*(byte *)&civs[civ].treaties[cities[city].owner] & 0x20) != 0 &&
               ((*(byte *)&civs[civ].treaties[cities[city].owner] & 8) == 0))))
             && ((game.turn + city) % 3 != 0)) {
            city6 = city_has_improvement(city,8);
            civ_add_ai_goal(civ,x2,y2,0,(-(uint)(city6 == 0) & 2) + 2);
          }
          city6 = tile_unit_owner(x2,y2);
          if ((city6 < 0) &&
             ((*(byte *)&civs[civ].treaties[cities[city].owner] & 0xe) == 0)) {
            civ_add_ai_goal(civ,x2,y2,1,2);
            civ_add_ai_goal(civ,x2,y2,0,3);
          }
        }
      }
    }
  }
  civs[civ].continent_policy[0] = 5;
  civs[civ].continent_policy[0x3f] = 5;
  civs[civ].flags = civs[civ].flags & 0xfffd;
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    if ((civ != civ2) &&
       ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 0x20) != 0)) {
      civs[civ].flags = civs[civ].flags | 2;
    }
  }
  for (continent = 1; continent < 0x3f; continent++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    threat_count = 0;
    defend_count = 0;
    attack_count = 0;
    rival_military = 0;
    rival_cities = 0;
    old_policy = (uint)civs[civ].continent_policy[continent];
    for (civ2 = 1; (int)civ2 < 8; civ2++) {
      if ((*(short *)&civs[civ2].continent_military[continent] != 0) &&
         (((uint)((int)(uint)civs[civ].continent_attack[continent] >> 2) <
           (uint)civs[civ2].continent_attack[continent] ||
          (*(char *)&civs[civ2].continent_cities[continent] != '\0')))) {
        if (civ != civ2) {
          city6 = diplo_is_hostile(civ,civ2);
          if ((city6 != 0) || ((*(byte *)&civs[civ].treaties[civ2] & 0x20) != 0))
          {
            if ((civs[civ2].continent_military[continent] <
                 civs[civ].continent_attack[continent]) ||
               ((civs[civ2].continent_attack[continent] <
                 civs[civ].continent_military[continent] ||
                (*(char *)&civs[civ].continent_cities[continent] == '\0')))) {
              attack_count++;
            }
            else {
              defend_count++;
            }
          }
          if ((((*(short *)&civs[civ2].continent_military[continent] != 0) &&
               ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
              ((*(byte *)&civs[civ].treaties[civ2] & 6) != 0)) &&
             (((int)(uint)civs[civ].continent_attack[continent] >> 1) +
              (uint)civs[civ].continent_military[continent] <
              (uint)civs[civ2].continent_attack[continent])) {
            threat_count++;
          }
        }
        rival_military += (uint)civs[civ2].continent_military[continent];
        rival_cities += (uint)civs[civ2].continent_cities[continent];
        if (civ != civ2) {
          if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
            if (*(char *)&civs[civ2].continent_cities[continent] != '\0') {
              if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
                civs[civ].continent_flags[continent] =
                     civs[civ].continent_flags[continent] | 1;
              }
              else {
                civs[civ].continent_flags[continent] =
                     civs[civ].continent_flags[continent] | 2;
              }
            }
            if (*(short *)&civs[civ2].continent_military[continent] != 0) {
              if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
                civs[civ].continent_flags[continent] =
                     civs[civ].continent_flags[continent] | 4;
              }
              else {
                civs[civ].continent_flags[continent] =
                     civs[civ].continent_flags[continent] | 8;
              }
            }
          }
          else {
            rival_military += (uint)civs[civ2].continent_military[continent];
            rival_cities += (uint)civs[civ2].continent_cities[continent];
          }
        }
      }
    }
    if (civs[0].continent_cities[continent] != '\0') {
      attack_count++;
    }
    base_density = 6;
    if (((((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0) &&
        (4 < civs[game.civ_by_rank[7]].num_cities)) && (0x96 < game.turn)) {
      base_density = 7;
    }
    if ((game.game_flags & 4) != 0) {
      base_density++;
    }
    city6 = ((uint)civs[civ].continent_military[continent] + rival_military) * 2;
    crowded = (uint)(city6 - *(short *)(&landmass_table + continent * 0x10) != 0 &&
                      *(short *)(&landmass_table + continent * 0x10) <= city6);
    if (*(char *)&civs[civ].continent_flags[continent] == '\0') {
      density = leaders[civs[civ].tribe].expand + base_density + 1;
    }
    else {
      density = base_density;
    }
    if ((int)*(short *)(&landmass_fertile_tiles + continent * 0x10) <
        (int)(((uint)civs[civ].continent_cities[continent] + rival_cities) * density + 2))
    {
      crowded = 1;
    }
    city6 = civ_has_advance(civ,0x2e);
    if (city6 == 0) {
      crowded = 0;
    }
    if (crowded == 0) {
      *(i8 *)&civs[civ].continent_policy[continent] = 5;
    }
    else {
      *(i8 *)&civs[civ].continent_policy[continent] = 4;
    }
    if (attack_count != 0) {
      *(i8 *)&civs[civ].continent_policy[continent] = 0;
    }
    if ((defend_count != 0) || (threat_count != 0)) {
      *(i8 *)&civs[civ].continent_policy[continent] = 1;
    }
    if (defend_count != 0) {
      civs[civ].continent_flags[continent] =
           civs[civ].continent_flags[continent] | 0x10;
    }
    if (((*(short *)&civs[civ].continent_military[continent] == 0) &&
        (*(char *)&civs[civ].continent_cities[continent] == '\0')) &&
       ((civs[civ].continent_flags[continent] & 0xc) != 8)) {
      *(i8 *)&civs[civ].continent_policy[continent] = 0;
    }
    if ((civs[civ].continent_policy[continent] != old_policy) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
      civ_reset_city_production(civ,continent);
    }
  }
  if ((civs[civ].continent_cities[0x3f] != '\0') &&
     (land_city_count <= (int)(uint)civs[civ].continent_cities[0x3f])) {
    civs[civ].continent_policy[0x3f] = 4;
  }
  if (civ != 0) {
    is_human = (uint)game.human_players & 1 << ((byte)civ & 0x1f);
    if (is_human == 0) {
      if ((settlers_total == 0) && (civs[civ].num_cities == 0)) {
        civ_check_destroyed(civ,0);
      }
      if (((int)game.turn + civ & 7) == 0) {
        ai_choose_government(civ,0);
      }
    }
    city6 = int_clamp((int)civs[civ].num_military_units >> 3,3,99);
    for (goal_idx = 0; goal_idx < 0x30; goal_idx++) {
      goal_weight[goal_idx] = city6;
      if (civs[civ].ai_goals[goal_idx].role == '\0') {
        goal_weight[goal_idx] = goal_weight[goal_idx] << 1;
      }
    }
    scenario_mode = 0;
    if (((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) && (civ == 3)
        ) && (is_human == 0)) {
      scenario_mode = 1;
    }
    unit = (uptr)game.num_units;
LAB_00533de4:
    unit--;
    if (-1 < (int)unit) {
      if (2 < game.multiplayer) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
      if (((units[unit].id != 0) && ((int)units[unit].owner == civ)) &&
         ((is_human == 0 || (((int)(short)units[unit].flags & 0x8000U) != 0)))) {
        if ((char)unit_types[units[unit].type].attack < 'c') {
          if ((units[unit].orders != 16) &&
             ((((15 < units[unit].orders || (units[unit].orders == 11)) ||
               (units[unit].ai_task = '?', units[unit].orders < 4)) &&
              (units[unit].orders != 3)))) {
            x2 = (int)units[unit].x;
            y2 = (int)units[unit].y;
            y = map_in_bounds(x2,y2);
            if ((y != 0) &&
               (continent = tile_landmass(x2,y2), units[unit].ai_task != '7')) {
              if (((scenario_mode != 0) &&
                  (((units[unit].type == 22 || (units[unit].type == '\n')) &&
                   (0x27 < y2)))) && (y2 < 0x5d)) {
                saved_flags = units[unit].flags;
                if ((game.turn == 1) || (owner_civ = tile_owner(0x2b,0x35), owner_civ != civ)) {
LAB_005340a6:
                  unit_set_goto(unit,0x31,0x2b,0x35);
                  units[unit].flags = units[unit].flags & 0xfffc;
                  goto LAB_00533de4;
                }
                if (units[unit].type == '\n') {
                  imps = 2;
                  unit2 = tile_first_unit(0x2b,0x35);
                  y = unit_stack_sum(unit2,imps);
                  if (y < 3) goto LAB_005340a6;
                }
                if (((units[unit].type == 22) && (3 < game.turn)) && (game.turn < 0xd)) {
                  if ((units[unit].flags & 3) == 0) {
                    y = _rand();
                    if (y % 3 == 0) {
                      units[unit].flags = units[unit].flags | 2;
                    }
                    else {
                      units[unit].flags = units[unit].flags | 1;
                    }
                  }
                  if (((units[unit].flags & 1) == 0) ||
                     (owner_civ = tile_owner(0x4c,0x22), owner_civ == civ)) {
                    if ((units[unit].flags & 2) != 0) {
                      owner_civ = tile_owner(0x3e,0x48);
                      if (owner_civ == civ) {
                        owner_civ = tile_owner(0x43,0x5b);
                        if (owner_civ != civ) {
                          unit_set_goto(unit,0x31,0x43,0x5b);
                        }
                      }
                      else {
                        unit_set_goto(unit,0x31,0x43,0x5b);
                      }
                    }
                  }
                  else {
                    unit_set_goto(unit,0x31,0x4c,0x22);
                  }
                }
                units[unit].flags = saved_flags;
              }
              if (((((int)game.turn & unit & 0xf) == 0) && (is_human == 0)) &&
                 ((((-1 < unit_types[units[unit].type].obsolete_by &&
                    (y = civ_has_advance(civ,(int)unit_types[units[unit].type].
                                                             obsolete_by), y != 0)) ||
                   (((1 < civs[civ].government &&
                     (*(char *)&civs[civ].continent_policy[continent] == 4)) &&
                    (units[unit].type == 2)))) &&
                  ((y = tile_zoc_unit_adjacent(x2,y2,civ), y == 0 &&
                   (((y = tile_city_owner(x2,y2), y < 0 ||
                     (y = unit_stack_sum(unit,2), 1 < y)) &&
                    ((y = tile_is_ocean(x2,y2), y == 0 &&
                     ((civs[civ].continent_flags[continent] & 0x10) == 0)))))))))) {
                if ((((unit_types[units[unit].type].obsolete_by < '\0') ||
                     (y = civ_has_advance(civ,(int)unit_types[units[unit].type].
                                                              obsolete_by), y == 0)) ||
                    ((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) != 0))
                   || (((int)units[unit].owner == (uint)(byte)human_civ ||
                       ((imps = tile_improvements(x2,y2),
                        ((byte)imps & 0x42) != 0x40 &&
                        ((y = tile_city_owner(x2,y2), y < 0 ||
                         (y = unit_stack_sum(unit,2), y != 1)))))))) {
                  city5 = city_at(x2,y2);
                  if (-1 < (int)city5) {
                    city_calc_cached_id = 0xffffffff;
                    city_calc_unit_support(city5);
                    cities[city5].shield_box =
                         (short)(((char)unit_types[units[unit].type].cost * city_shield_rows) / 2)
                         + cities[city5].shield_box;
                  }
                  unit_destroy_redraw(unit,1);
                  goto LAB_00533de4;
                }
                for (unit_type = 0; (int)unit_type < 0x3e; unit_type++) {
                  if ((unit_types[units[unit].type].obsolete_by ==
                       unit_types[unit_type].prerequisite) &&
                     (unit_types[units[unit].type].role == unit_types[unit_type].role)) {
                    units[unit].type = (u8)unit_type;
                    units[unit].flags = units[unit].flags & 0xdfff;
                    break;
                  }
                }
              }
              best_dist = 9999;
              best_goal = -1;
              ai_role = ai_unit_role(unit);
              if (((((ai_role != 7) || (units[unit].orders != 11)) ||
                   (y = map_in_bounds((int)units[unit].goto_x,(int)units[unit].goto_y)
                   , y == 0)) ||
                  ((civ2 = tile_city_owner((int)units[unit].goto_x,
                                               (int)units[unit].goto_y), (int)civ2 < 0 ||
                   (civ == civ2)))) &&
                 ((unit_types[units[unit].type].role != '\0' ||
                  (unit_types[units[unit].type].attack != '\0')))) {
                for (goal = 0; goal < 0x30; goal++) {
                  if (((civs[civ].ai_goals[goal].role != -1) &&
                      ('\0' < civs[civ].ai_goals[goal].priority)) &&
                     (y = map_in_bounds((int)civs[civ].ai_goals[goal].x,
                                            (int)civs[civ].ai_goals[goal].y), y != 0)) {
                    if (((civs[civ].ai_goals[goal].role == 18) &&
                        (ai_role == 2)) &&
                       ((unit_types[units[unit].type].flags & 0x4000) != 0)) {
                      ai_role = 0x12;
                    }
                    if (((civs[civ].ai_goals[goal].role == ai_role) &&
                        (y = tile_landmass((int)civs[civ].ai_goals[goal].x,
                                               (int)civs[civ].ai_goals[goal].y), y == continent))
                       || (((unit_types[units[unit].type].domain == 1 &&
                            ((char)unit_types[0x1c].attack <=
                             (char)unit_types[units[unit].type].attack)) &&
                           ((civs[civ].ai_goals[goal].role == ai_role ||
                            (civs[civ].ai_goals[goal].role == 2)))))) {
                      goal_dist = map_distance_diag(x2,y2,
                                                    (int)civs[civ].ai_goals[goal].x,
                                                    (int)civs[civ].ai_goals[goal].y);
                      if (unit_types[units[unit].type].domain == 1) {
                        if (unit_types[units[unit].type].range == 1) {
                          if (goal_dist <=
                              (int)(char)unit_types[units[unit].type].move /
                              (int)(uint)cosmic.road_move_mult - 2 >> 1) goto LAB_00534c18;
                        }
                        else if (((*(byte *)&civs[civ].ai_goals[goal].priority & 1) != 0)
                                && ((((int)game.turn >> 1) + goal & 1U) != 0)) {
                          goal_dist = (int)((((goal_dist <=
                                             (int)(char)unit_types[units[unit].type].move /
                                             (int)(uint)cosmic.road_move_mult) - 1 & 0xfffffffe) + 4
                                           ) * goal_dist) /
                                     (civs[civ].ai_goals[goal].priority + 1);
                          goto LAB_00534c18;
                        }
                      }
                      else {
                        goal_dist = ((goal_weight[goal] /
                                    (int)((civs[civ].ai_goals[goal].role ==
                                          '\0') + 1)) * goal_dist) /
                                   (civs[civ].ai_goals[goal].priority + 1);
LAB_00534c18:
                        if (((units[unit].orders != 1) &&
                            (units[unit].orders != 2)) ||
                           ((1 < civs[civ].ai_goals[goal].priority &&
                            (((goal_dist <=
                               civs[civ].ai_goals[goal].priority * city6 ||
                              (goal_weight[goal] /
                               (int)((civs[civ].ai_goals[goal].role == '\0')
                                    + 1) == city6)) &&
                             (y = tile_city_owner(x2,y2), y < 0)))))) {
                          if (((is_human != 0) && (goal_weight[goal] == city6)) &&
                             (tile_imps = tile_improvements((int)civs[civ].ai_goals[goal].x,
                                                         (int)civs[civ].ai_goals[goal].y),
                             (tile_imps & 0x80) != 0)) {
                            goal_dist = (int)(goal_dist + (goal_dist >> 0x1f & 7U)) >> 3;
                          }
                          if ((goal_dist < best_dist) &&
                             (goal_dist / city6 <
                              civs[civ].ai_goals[goal].priority * 4)) {
                            best_dist = goal_dist;
                            best_goal = goal;
                          }
                        }
                      }
                    }
                  }
                }
                if (-1 < best_goal) {
                  if ((civs[civ].ai_goals[best_goal].x == units[unit].x)
                     && (civs[civ].ai_goals[best_goal].y == units[unit].y)
                     ) {
                    units[unit].orders = 16;
                    units[unit].flags = units[unit].flags | 0x80;
                    goto LAB_00533de4;
                  }
                  if ((ai_role == 1) &&
                     (imps = tile_improvements((int)units[unit].x,(int)units[unit].y),
                     ((byte)imps & 0x42) == 0x40)) {
                    if ((*(byte *)&civs[civ].ai_goals[best_goal].priority & 1) == 0)
                    goto LAB_00533de4;
                    civ_add_standing_goal(civ,(int)units[unit].x,(int)units[unit].y,1,2);
                  }
                  if (((unit_types[units[unit].type].flags & 0x100) == 0) ||
                     (owner_civ = tile_city_owner((int)civs[civ].ai_goals[best_goal].x,
                                               (int)civs[civ].ai_goals[best_goal].y), owner_civ == civ))
                  {
                    unit_set_goto(unit,0x31,
                                       (int)civs[civ].ai_goals[best_goal].x,
                                       (int)civs[civ].ai_goals[best_goal].y);
                    if ((unit_types[units[unit].type].role == 5) &&
                       (y = tile_city_owner((int)civs[civ].ai_goals[best_goal].x,
                                                (int)civs[civ].ai_goals[best_goal].y), -1 < y)) {
                      civs[civ].ai_goals[best_goal].priority = 0;
                    }
                    goal_weight[best_goal]++;
                  }
                }
              }
            }
          }
        }
        else {
          units[unit].ai_task = '!';
        }
      }
      goto LAB_00533de4;
    }
  }
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && ((int)cities[city].owner == civ)) {
      if ((cities[city].flags & 0x400) == 0) {
        cities[city].flags = cities[city].flags & 0xfffffdff;
      }
      cities[city].flags = cities[city].flags & 0xfffffbff;
    }
  }
  civ_refresh_ai_goals(civ);
  return;
}
#undef city_calc_cached_id
#undef city_shield_rows
#undef human_civ
#undef scenario_flags
#undef density
#undef unit
#undef settler_divisor
#undef city
#undef attack_count
#undef goal_weight
#undef is_human
#undef continent
#undef unit_type
#undef old_policy
#undef y2
#undef x3
#undef base_density
#undef ai_role
#undef scenario_mode
#undef x2
#undef crowded
#undef settler_count
#undef done
#undef rival_military
#undef threat_count
#undef settlers_total
#undef settle_goals
#undef wonder
#undef y3
#undef civ2
#undef defend_count
#undef goal_dist
#undef goal_idx
#undef rival_cities
#undef goal
#undef city4
#undef land_city_count
#undef best_dist
#undef city3
#undef group
#undef best_goal
#undef settler_quota

/* 005351aa auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define step_dy (*(int *)(frame_ + FRAME_OFF(0)))
#define step_dx (*(int *)(frame_ + FRAME_OFF(4)))
#define abs_dx (*(uint *)(frame_ + FRAME_OFF(8)))
#define dy_toward (*(int *)(frame_ + FRAME_OFF(20)))
#define x3 (*(uint *)(frame_ + FRAME_OFF(32)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define city (*(iptr *)(frame_ + FRAME_OFF(40)))
#define ransom (*(int *)(frame_ + FRAME_OFF(52)))
#define best_dir (*(iptr *)(frame_ + FRAME_OFF(72)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(84)))
#define line (*(iptr *)(frame_ + FRAME_OFF(92)))
#define sea_body (*(int *)(frame_ + FRAME_OFF(108)))
#define dir (*(iptr *)(frame_ + FRAME_OFF(112)))
#define civ_byte (*(byte *)(frame_ + FRAME_OFF(116)))
#define best_score (*(int *)(frame_ + FRAME_OFF(120)))
#define score (*(int *)(frame_ + FRAME_OFF(124)))
i32 __cdecl ai_barbarian_unit_move(void)

{
  u8 move_pts;
  short y4;
  short y5;
  short x4;
  char here_terrain;
  iptr unit;
  iptr civ2;
  int x2;
  iptr y;
  iptr in_bounds;
  int y3;
  iptr transport_count;
  iptr x;
  iptr valid;
  byte terrain;
  int y2;
  int check;
  iptr unit2;
  iptr civ;
  int value;
  uint tile_imps;
  i32 misc;
  uptr unit_type;
  bool at_city;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  best_dir = 8;
  unit = (iptr)game.active_unit;
  civ2 = (iptr)units[unit].owner;
  if (units[unit].orders != 11) {
    units[unit].orders = -1;
  }
  x2 = (int)units[unit].x;
  y4 = units[unit].y;
  y = (iptr)y4;
  if (((y < 2) || (map.height - 2 <= y)) ||
     (in_bounds = map_in_bounds(x2,y), in_bounds == 0)) {
    unit_delete_with_cargo(unit,1);
    return 1;
  }
  y3 = tile_in_enemy_zoc(x2,y,civ2);
  unit_type = (uptr)units[unit].type;
  city = city_find_nearest(x2,y,-1,0xffffffff,-1);
  if (unit_types[unit_type].hold != '\0') {
    y3 = unit_stack_sum(unit,2);
    transport_count = unit_stack_count_role(unit,6);
    if (y3 - transport_count < 2) {
      unit_destroy_redraw(unit,1);
      return 1;
    }
    units[unit].counter++;
    if (30 < (char)units[unit].counter) {
      unit_destroy_redraw(unit,1);
      return 1;
    }
    for (dir = 0; dir < 8; dir++) {
      x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
      y3 = (char)(&dir_dy_table)[dir] + y;
      valid = map_in_bounds(x,y3);
      if (valid != 0) {
        if (((-1 < city) && (nearest_city_dist < 9)) &&
           ((y2 = tile_is_ocean(x,y3), y2 == 0 &&
            (((y2 = tile_city_or_unit_owner(x,y3), y2 < 0 && (1 < y3)) &&
             (y3 < map.height - 2)))))) {
          y2 = tile_landmass((int)cities[city].x,(int)cities[city].y);
          check = tile_landmass(x,y3);
          if (y2 == check) {
            y2 = unit_stack_sum(unit,2);
            if (((y2 < 3) && (y2 = unit_stack_count_role(unit,0), y2 == 0)) &&
               ((y2 = unit_stack_count_role(unit,1), y2 == 0 && (nearest_city_dist < 3)))) {
              unit_destroy_redraw(unit,1);
            }
            else {
              for (civ3 = 1; civ3 < 8; civ3++) {
                if ((((1 << ((byte)civ3 & 0x1f) & (uint)game.civs_alive) != 0) &&
                    ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0)) &&
                   ((y2 = tile_visible_to(x,y3,civ3), y2 != 0 &&
                    ((cities[city].owner == civ3 && (autoplay_active == 0)))))) {
                  city = city_find_nearest(x,y3,-1,0xffffffff,-1);
                  text_set_string_arg(0,(iptr)&cities[city].name);
                  if (human_civ == civ3) {
                    if (game.multiplayer == '\0') {
                      unit_stack_set_seen_by(unit,civ3);
                      mapviews_ensure_visible(x,y3,civ2);
                      map_redraw_tile_all_views(x,y3);
                    }
                    dlg_game_txt_with_unit((iptr)((u8 *)&g.d_00632528),unit);
                  }
                  else if (2 < game.multiplayer) {
                    net_send_text_args(0x4e,*(i32 *)
                                             (&net_player_slots +
                                             *(int *)(&net_civ_slots + civ3 * 4) * 0x54),1,0,
                                       unit,0);
                  }
                }
              }
              y3 = tile_at(x,y3);
              units[unit].visibility = *(byte *)(y3 + 4) | units[unit].visibility;
              units[unit].ai_task = 'U';
              unit_stack_wake_by_role(unit,0xffff,0);
              unit_exhaust_moves(unit);
            }
            goto LAB_0053692c;
          }
        }
        y2 = tile_is_ocean(x,y3);
        if ((y2 != 0) && (y3 = tile_unit_owner(x,y3), 0 < y3)) {
          best_dir = dir;
          goto LAB_00536859;
        }
      }
    }
    if (units[unit].orders != 11) {
      best_score = 0;
      city2 = -1;
      y3 = tile_is_ocean(x2,y);
      if (y3 == 0) {
        sea_body = -1;
      }
      else {
        sea_body = tile_landmass(x2,y);
      }
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city].owner != '\0')) {
          if (-1 < sea_body) {
            misc = tile_landmass((int)cities[city].x,(int)cities[city].y);
            y3 = landmass_borders_body(misc,sea_body);
            if (y3 == 0) goto LAB_00535741;
          }
          y3 = city_treasury_share(city);
          y2 = map_distance_diag(x2,y,(int)cities[city].x,(int)cities[city].y);
          y3 = (y3 + 0x32) / (y2 + 1);
          if (best_score < y3) {
            city2 = city;
            best_score = y3;
          }
        }
LAB_00535741: ;
      }
      if (city2 < 0) {
        unit_destroy_redraw(unit,1);
        return 1;
      }
      ai_ship_goto_near_shore(unit,0x70,(int)cities[city2].x,(int)cities[city2].y);
    }
    goto LAB_0053692c;
  }
  if ((nearest_city_dist == 0) ||
     (misc = tile_improvements(x2,y), ((byte)misc & 0x42) == 0x40)) {
    y2 = unit_stack_sum(unit,2);
    check = unit_stack_count_role(unit,6);
    if ((((1 < y2 - check) || (y3 != 0)) && (unit_types[unit_type].role != 1)) ||
       ((at_city = nearest_city_dist == 0, y2 = unit_stack_sum(unit,2),
        (int)(at_city + 2 + (uint)(y3 == 0)) <= y2 &&
        ((char)unit_types[unit_type].defense <= (char)unit_types[unit_type].attack)))) goto LAB_005359af;
    units[unit].orders = 1;
    best_dir = 8;
  }
  else {
LAB_005359af:
    if (((-1 < city) && ((game.turn + unit & 3U) == 0)) &&
       ((y2 = tile_is_ocean(x2,y), y2 == 0 || (unit_types[unit_type].hold != '\0')))) {
      y2 = tile_landmass((int)cities[city].x,(int)cities[city].y);
      check = tile_landmass(x2,y);
      if ((y2 != check) || (8 < nearest_city_dist)) {
        unit_destroy_redraw(unit,1);
        return 1;
      }
    }
    dy_toward = -3;
    x3 = -3;
    if (-1 < city) {
      y2 = tile_landmass((int)cities[city].x,(int)cities[city].y);
      check = tile_landmass(x2,y);
      if ((y2 == check) &&
         (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) {
        x3 = cities[city].x - x2;
        if ((game.rules & 0x8000) == 0) {
          abs_dx = x3;
          if ((int)x3 < 1) {
            abs_dx = ~x3 + 1;
          }
          if ((int)map.width >> 1 <= (int)abs_dx) {
            x3 = -x3;
          }
        }
        if ((int)x3 < 1) {
          if ((int)x3 < 0) {
            x3 = -1;
          }
          else {
            x3 = 0;
          }
        }
        else {
          x3 = 1;
        }
        if (cities[city].y == -3 || cities[city].y + 3 < 0) {
          if (cities[city].y + 3 < 0) {
            dy_toward = -1;
          }
          else {
            dy_toward = 0;
          }
        }
        else {
          dy_toward = 1;
        }
      }
    }
    if (-1 < city) {
      if (cities[city].owner == civ2) {
        dy_toward = -3;
        x3 = -3;
      }
      if (civs[cities[city].owner].num_cities < 2) {
        dy_toward = -3;
        x3 = -3;
      }
      if (civs[cities[city].owner].gold < 100) {
        dy_toward = -3;
        x3 = -3;
      }
    }
    if (x3 != -3) {
      units[unit].goto_x = cities[city].x;
      units[unit].goto_y = cities[city].y;
      misc = unit_goto_next_dir(unit);
      units[unit].last_dir = (u8)misc;
    }
    if (4 < (char)unit_types[unit_type].role) {
      here_terrain = tile_terrain(x2,y);
      y2 = unit_stack_sum(unit,2);
      if (((1 < y2) && (here_terrain != '\n')) &&
         (y2 = unit_stack_count_role(unit,(int)(char)unit_types[unit_type].role), y2 < 2)) {
        best_dir = 8;
        goto LAB_00536859;
      }
      if (here_terrain == '\n') {
        if (nearest_city_dist < 3) {
          unit_destroy_redraw(unit,1);
          return 1;
        }
      }
      else {
        y2 = unit_find_nearest(x2,y,civ2,unit);
        if ((unit_nearest_dist < 4) && ((char)unit_types[units[y2].type].role < 2)) {
          unit_set_goto(unit,0x58,(int)units[y2].x,(int)units[y2].y);
          goto LAB_0053692c;
        }
        if ((int)(((int)game.turn & 7U) + 4) <= nearest_city_dist) {
          unit_destroy_redraw(unit,1);
          return 1;
        }
      }
    }
    best_score = -999;
    for (dir = 0; dir < 8; dir++) {
      x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
      y2 = (char)(&dir_dy_table)[dir] + y;
      check = map_in_bounds(x,y2);
      if (check != 0) {
        terrain = tile_terrain(x,y2);
        if ((unit_types[unit_type].domain == 2) == (terrain == 10)) {
          check = tile_unit_owner(x,y2);
          unit2 = tile_first_unit(x,y2);
          score = 0;
          if ((char)unit_types[unit_type].role < 5) {
            civ = tile_city_owner(x,y2);
            if ((civ < 0) || (civ2 == civ)) {
LAB_005364bc:
              value = tile_owner(x,y2);
              if (civ2 != value) {
                score = 4;
              }
              tile_imps = tile_improvements(x,y2);
              if ((tile_imps & 0x40) == 0) {
                tile_imps = tile_improvements(x,y2);
                if ((tile_imps & 0xc) != 0) {
                  score += 6;
                }
              }
              else {
                score += 8;
              }
              value = rand_range(0,5);
              score += value;
              if (unit2 < 0) {
LAB_005365f1:
                if ((((y3 == 0) || (unit_types[unit_type].role != '\0')) || (-1 < unit2)) ||
                   ((y2 = tile_in_enemy_zoc(x,y2,civ2), y2 == 0 ||
                    ((unit_types[units[unit].type].flags & 2) != 0)))) {
                  if ((char)units[unit].last_dir == dir) {
                    score += 6;
                  }
                  if (x3 != -3) {
                    if ((char)(&dir_dx_table)[dir] < 1) {
                      if ((char)(&dir_dx_table)[dir] < '\0') {
                        step_dx = -1;
                      }
                      else {
                        step_dx = 0;
                      }
                    }
                    else {
                      step_dx = 1;
                    }
                    if (x3 == step_dx) {
                      score += 2;
                    }
                  }
                  if (dy_toward != -3) {
                    if ((char)(&dir_dy_table)[dir] < 1) {
                      if ((char)(&dir_dy_table)[dir] < '\0') {
                        step_dy = -1;
                      }
                      else {
                        step_dy = 0;
                      }
                    }
                    else {
                      step_dy = 1;
                    }
                    if (dy_toward == step_dy) {
                      score += 2;
                    }
                  }
                  goto LAB_0053673f;
                }
              }
              else if (check == civ2) {
                check = tile_is_ocean(x2,y);
                if (check != 0) {
                  score -= 0x14;
                  goto LAB_005365f1;
                }
              }
              else {
                check = tile_is_ocean(x2,y);
                if (check == 0) {
                  if (unit_type == 9) {
                    if ((char)unit_types[units[unit2].type].role < 5) goto LAB_00535e74;
                    score += 99;
                  }
                  else if (unit_types[units[unit2].type].role != 6) {
                    score += 99;
                  }
                  goto LAB_005365f1;
                }
              }
            }
            else {
              value = tile_is_ocean(x2,y);
              if (value == 0) {
                value = tile_unit_owner(x,y2);
                if (value < 0) {
                  value = civs[civ].gold / 2;
                  if (value < 0x33) {
                    value = 0x32;
                  }
                  ransom = cities[city].size * 0x19;
                  if (ransom <= value) {
                    ransom = value;
                  }
                  if ((((game.power_rank[civ] == 7) && (200 < game.year)) &&
                      (4 < civs[civ].num_cities)) &&
                     (ransom = (civs[civ].gold / 100) * 100, ransom < 1000)) {
                    ransom = civs[civ].gold + 1;
                  }
                  text_set_number_arg(0,ransom);
                  if (((game.multiplayer < 3) &&
                      (civ_byte = (byte)civ,
                      (1 << (civ_byte & 0x1f) & (uint)game.human_players) != 0)) &&
                     (ransom <= civs[civ].gold)) {
                    city = city_at(x,y2);
                    text_set_string_arg(1,(iptr)&cities[city].name);
                    __chdir(&scenario_dir_path);
                    value = text_open_section((iptr)((u8 *)&g.d_00632544),(iptr)((u8 *)&g.d_00632538));
                    if (value != 0) {
                      __chdir(&game_home_dir);
                      value = text_open_section((iptr)((u8 *)&g.d_00632558),(iptr)((u8 *)&g.d_0063254c));
                      if (value != 0) goto LAB_0053692c;
                    }
                    __chdir(&game_home_dir);
                    text_read_line(1);
                    value = _atoi(&text_buffer);
                    if (0 < value) {
                      y5 = cities[city].y;
                      x4 = cities[city].x;
                      for (line = 0; line <= (y5 * 3 + x4 * 5) % value;
                          line = line + 1) {
                        text_read_line(1);
                      }
                      text_set_string_arg(0,(iptr)((u8 *)&g.d_00679640));
                      mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,civ);
                      if ((autoplay_active == 0) &&
                         (value = dlg_game_txt_with_unit((iptr)((u8 *)&g.d_00632560),unit), value != 0)) {
                        civs[civ].gold -= ransom;
                        status_draw_info(1);
                        for (line = 0; line < 0x14; line++) {
                          x = map_wrap_x((int)cities[city].x +
                                              (int)(char)(&city_tile_dx_table)[line]);
                          x2 = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[line];
                          y3 = map_in_bounds(x,x2);
                          if (((y3 != 0) &&
                              (y3 = tile_first_unit(x,x2), -1 < y3)) &&
                             (units[y3].owner == '\0')) {
                            unit_stack_delete_all(y3,1);
                            map_redraw_tile_all_views(x,x2);
                          }
                        }
                        return 1;
                      }
                    }
                  }
                }
                if ((unit_type != 9) || (value = tile_unit_owner(x,y2), value < 0)) {
                  best_dir = dir;
                  goto LAB_00536859;
                }
                if ((game.turn + unit & 7U) != 0) {
                  value = unit_stack_sum(unit,2);
                  if ((value < 2) && (units[unit].orders = 1, best_score < 99)) {
                    best_score = 99;
                    best_dir = 8;
                  }
                  goto LAB_005364bc;
                }
              }
            }
          }
          else {
            if (-1 < unit2) {
              if (check == civ2) {
                score = 99;
              }
              else {
                score = -99;
              }
            }
            city_find_nearest(x,y2,-1,0xffffffff,-1);
            move_pts = terrain_types[terrain].move_cost;
            y2 = rand_range(0,3);
            score = score + (char)move_pts + y2 + nearest_city_dist * 4;
LAB_0053673f:
            if (best_score <= score) {
              best_score = score;
              best_dir = dir;
            }
          }
        }
      }
LAB_00535e74: ;
    }
    y3 = tile_city_owner(x2,y);
    if (((y3 < 0) || (y3 = unit_stack_sum(unit,2), 1 < y3)) || (0x62 < best_score)) {
      if ((((best_score < 99) &&
           (y3 = unit_moves_left(unit), y3 <= (int)(uint)cosmic.road_move_mult)) &&
          (-1 < city)) &&
         (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) {
        y3 = tile_at(x2,y);
        if (((*(byte *)(y3 + 1) & 0x4c) != 0) ||
           ((unit_type == 9 && ((*(byte *)(y3 + 1) & 0x10) != 0)))) {
          unit_pillage(unit,0);
          unit_exhaust_moves(unit);
          goto LAB_0053692c;
        }
      }
    }
    else {
      best_dir = 8;
    }
  }
LAB_00536859:
  if (best_dir == 8) {
    units[unit].last_dir = 0xff;
    unit_exhaust_moves(unit);
    if (((unit_types[unit_type].role == 1) ||
        (misc = tile_improvements(x2,y), ((byte)misc & 0x42) == 0x40)) &&
       (units[unit].orders = 1, (units[unit].flags & 0x100) != 0)) {
      units[unit].orders = 2;
    }
  }
  else {
    units[unit].orders = 27;
    misc = map_wrap_x((char)(&dir_dx_table)[best_dir] + x2);
    units[unit].goto_x = (i16)misc;
    units[unit].goto_y = (char)(&dir_dy_table)[best_dir] + y4;
  }
LAB_0053692c:
  if (((units[unit].orders == 11) && (units[unit].goto_x == x2)) &&
     (units[unit].goto_y == y)) {
    units[unit].orders = -1;
  }
  return 0;
}
#undef autoplay_active
#undef human_civ
#undef text_buffer
#undef step_dy
#undef step_dx
#undef abs_dx
#undef dy_toward
#undef x3
#undef city2
#undef city
#undef ransom
#undef best_dir
#undef civ3
#undef line
#undef sea_body
#undef dir
#undef civ_byte
#undef best_score
#undef score

/* 005369f3 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl ai_transports_raid_empty_city(iptr city)

{
  char civ2;
  short x;
  short y;
  int civ;
  int max_moves;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  x = cities[city].x;
  y = cities[city].y;
  civ2 = cities[city].owner;
  for (unit = 0; unit < game.num_units; unit++) {
    if (units[unit].id != 0) {
      civ = (int)units[unit].owner;
      if ((((civ != 0) && ((1 << (units[unit].owner & 0x1fU) & (uint)game.human_players) == 0)
           ) && (civ2 != civ)) &&
         ((((*(byte *)&civs[civ].treaties[civ2] & 4) == 0 &&
           (unit_types[units[unit].type].hold != '\0')) &&
          ((civ = unit_stack_sum(unit,2), 1 < civ &&
           (civ = tile_is_ocean((int)units[unit].x,(int)units[unit].y), civ != 0)))))) {
        civ = map_distance_diag((int)x,(int)y,(int)units[unit].x,
                                   (int)units[unit].y);
        max_moves = unit_max_moves(unit);
        if (civ < max_moves) {
          units[unit].orders = 11;
          units[unit].goto_x = x;
          units[unit].goto_y = y;
        }
      }
    }
  }
  return;
}
#undef unit

/* 00536bc9 auto */
#define quota (*(i32 *)(frame_ + FRAME_OFF(4)))
#define remaining (*(i32 *)(frame_ + FRAME_OFF(12)))
#define weight (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl ai_continent_defense_quota(iptr civ,iptr continent)

{
  uint batch;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  quota = 0;
  remaining = (uint)civs[civ].continent_cities[continent];
  weight = 3;
  do {
    batch = remaining;
    if (4 < (int)remaining) {
      batch = 5;
    }
    remaining -= batch;
    quota += weight * batch;
    weight--;
  } while ((remaining != 0) && (0 < weight));
  return quota;
}
#undef quota
#undef remaining
#undef weight

/* 00536c4c auto */
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define unit2 (*(int *)(frame_ + FRAME_OFF(16)))
#define dir (*(uptr *)(frame_ + FRAME_OFF(28)))
#define best_score (*(int *)(frame_ + FRAME_OFF(32)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define score (*(int *)(frame_ + FRAME_OFF(40)))
i32 __cdecl ai_nuke_pick_target(iptr unit)

{
  uint strength;
  uint *treaty;
  bool in_range;
  iptr civ;
  iptr civ2;
  int y;
  iptr x;
  int owner_civ;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (iptr)units[unit].owner;
  best_score = -1;
  city2 = -1;
  city = 0;
  do {
    if (game.num_cities <= city) {
      y = 5 - civs[civ].num_cities;
      if (y < 1) {
        y = 0;
      }
      if ((10 - y <= best_score) &&
         (1 < civs[civ].units_active[units[unit].type])) {
        for (dir = 0; (int)dir < 8; dir++) {
          x = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)cities[city2].x);
          y = (int)(char)(&dir_dy_table)[dir] + (int)cities[city2].y;
          owner_civ = map_in_bounds(x,y);
          if (((owner_civ != 0) && (owner_civ = tile_city_owner(x,y), owner_civ < 0)) &&
             (owner_civ = tile_unit_owner(x,y), owner_civ < 0)) {
            unit_relocate(unit,x,y,1);
            units[unit].visibility = '\0';
            if (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0) {
              if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 34) + cities[city2].owner * 4) & 2) == 0) {
                treaty = (uint *)(civ * 0x594 + (iptr)((u8 *)&civs + 32) + cities[city2].owner * 4);
                *treaty = *treaty | 0x20000;
                treaty = (uint *)(civ * 0x594 + (iptr)((u8 *)&civs + 32) + cities[city2].owner * 4);
                *treaty = *treaty & 0xffffffef;
                diplo_set_treaty_flags(civ,(int)cities[city2].owner,0x10000);
              }
              else {
                civs[cities[city2].owner].last_treaty_turn[civ] =
                     civs[cities[city2].owner].last_treaty_turn[civ] - 2;
              }
            }
            return dir ^ 4;
          }
        }
      }
      return 8;
    }
    if ((((((cities[city].id != 0) && (civ2 = (iptr)cities[city].owner, civ2 != civ)) &&
          (y = city_has_improvement(city,0x11), y == 0)) &&
         (4 < cities[city].size)) &&
        (((strength = (uint)civs[civ2].military_strength * 2,
          strength + (uint)civs[civ].military_strength * -3 != 0 &&
          (uint)civs[civ].military_strength * 3 <= strength ||
          ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0)) ||
         ((civs[civ2].units_active[0x2d] == '\0' &&
          (strength = (uint)civs[civ2].military_strength * 2,
          strength - civs[civ].military_strength != 0 && civs[civ].military_strength <= strength))))))
       && ((civs[civ].treaties[civ2] & 0x104) == 0x100)) {
      score = 0;
      for (dir = 0; (int)dir < 9; dir++) {
        x = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)cities[city].x);
        y = (int)(char)(&dir_dy_table)[dir] + (int)cities[city].y;
        owner_civ = map_in_bounds(x,y);
        if ((owner_civ != 0) && (owner_civ = tile_unit_owner(x,y), 0 < owner_civ)) {
          if (owner_civ == civ) {
            score -= 2;
          }
          else if ((civs[civ].treaties[owner_civ] & 0x104) == 0x100) {
            for (unit2 = tile_first_unit(x,y); -1 < unit2;
                unit2 = unit_next_in_stack(unit2)) {
              score++;
            }
          }
          else {
            score -= 99;
          }
        }
      }
      score += ((int)cities[city].size >> 1);
      if (best_score < score) {
        in_range = false;
        for (city3 = 0; city3 < game.num_cities; city3++) {
          if ((cities[city3].id != 0) && (cities[city3].owner == civ)) {
            y = map_distance((int)cities[city3].x,(int)cities[city3].y,
                                       (int)cities[city].x,(int)cities[city].y);
            owner_civ = unit_max_moves(unit);
            if (y <= owner_civ / (int)(uint)cosmic.road_move_mult) {
              in_range = true;
              break;
            }
          }
        }
        if (in_range) {
          city2 = city;
          best_score = score;
        }
      }
    }
    city++;
  } while( true );
}
#undef city2
#undef city
#undef unit2
#undef dir
#undef best_score
#undef city3
#undef score

/* 00537331 auto */
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define x3 (*(int *)(frame_ + FRAME_OFF(4)))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define best_threat (*(int *)(frame_ + FRAME_OFF(24)))
#define home_dist (*(int *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(36)))
#define threat_score (*(int *)(frame_ + FRAME_OFF(56)))
#define y3 (*(int *)(frame_ + FRAME_OFF(60)))
#define city_dist (*(int *)(frame_ + FRAME_OFF(68)))
#define dir (*(uptr *)(frame_ + FRAME_OFF(72)))
#define defense_power (*(int *)(frame_ + FRAME_OFF(76)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(80)))
#define range_left (*(int *)(frame_ + FRAME_OFF(84)))
#define best_score (*(int *)(frame_ + FRAME_OFF(88)))
#define nearest_city (*(iptr *)(frame_ + FRAME_OFF(92)))
#define score (*(int *)(frame_ + FRAME_OFF(96)))
i32 __cdecl
ai_air_unit_orders(iptr unit,iptr unit_type,iptr x,iptr y,int mode,iptr out_flag,
            int may_go_home,iptr landmass,int set_flag)

{
  byte civ2;
  char small_val;
  u8 stat_a;
  u8 stat_b;
  u8 att_fp;
  short x4;
  short y4;
  ushort own_flags;
  bool at_airbase;
  byte terrain;
  int civ;
  int value;
  int y2;
  int check;
  int target_dist;
  i32 tile_imps;
  iptr x2;
  uint move_mult;
  iptr unit2;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = unit;
  civ2 = units[unit].owner;
  civ = (int)(char)civ2;
  if (unit_types[units[unit].type].range == '\0') {
    range_left = unit_max_moves(unit);
    range_left = range_left * 2;
  }
  else {
    stat_a = unit_types[units[unit].type].range;
    stat_b = units[unit].counter;
    value = unit_max_moves(unit);
    range_left = unit_moves_left(unit);
    range_left = ((int)(char)stat_a - ((char)stat_b + 1)) * value + range_left;
  }
  range_left = range_left / (int)(uint)cosmic.road_move_mult;
  home_dist = 9999;
  for (city = 0; city < game.num_cities; city++) {
    if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
       (value = map_distance(*(i32 *)x,*(i32 *)y,
                                    (int)cities[city].x,(int)cities[city].y),
       value < home_dist)) {
      home_dist = value;
    }
  }
  if (unit_types[units[unit].type].range != '\0') {
    if (unit_types[units[unit].type].range == 1) {
      if (units[unit].orders != 11) {
        value = unit_max_moves(unit);
        y2 = unit_moves_left(unit);
        if (((y2 <= value >> 1) && (range_left < home_dist + 1)) && (home_dist <= range_left)) {
          units[unit].ai_task = 'H';
          unit_go_home(unit);
          return 0xffffffff;
        }
      }
    }
    else if (((int)(char)unit_types[units[unit].type].range / 2 <=
              (int)(char)units[unit].counter) && (home_dist <= range_left)) {
      units[unit].ai_task = 'H';
      unit_go_home(unit);
      return 0xffffffff;
    }
  }
  if (((unit_types[units[unit].type].flags & 0x1000) != 0) &&
     ((char)unit_types[unit_type].attack < 'c')) {
    best_score = (int)(char)unit_types[units[unit].type].cost << 2;
    unit3 = -1;
    unit = 0;
    do {
      if (game.num_units <= unit) {
        if (-1 < unit3) {
          x4 = units[unit3].x;
          y4 = units[unit3].y;
          for (dir = 0; (int)dir < 8; dir++) {
            x2 = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)x4);
            value = (int)(char)(&dir_dy_table)[dir] + (int)y4;
            y2 = map_in_bounds(x2,value);
            if ((y2 != 0) && (y2 = tile_city_or_unit_owner(x2,value), y2 < 0)) {
              unit_relocate(unit2,x2,value,1);
              units[unit2].visibility = '\0';
              *(iptr *)x = x2;
              *(int *)y = value;
              return dir ^ 4;
            }
          }
        }
        value = unit_stack_sum(unit2,8);
        if (1 < value) {
          for (city = 0; city < game.num_cities; city++) {
            if ((cities[city].id != 0) && (cities[city].owner == civ)) {
              x2 = tile_first_unit((int)cities[city].x,(int)cities[city].y);
              y2 = unit_stack_sum(x2,8);
              if (y2 < value) {
                y2 = map_distance(*(i32 *)x,*(i32 *)y,
                                            (int)cities[city].x,(int)cities[city].y);
                check = unit_max_moves(unit2);
                if (y2 <= check / (int)(uint)cosmic.road_move_mult) {
                  unit_relocate(unit2,(int)cities[city].x,(int)cities[city].y,1);
                  units[unit2].visibility = '\0';
                  *(int *)x = (int)cities[city].x;
                  *(int *)y = (int)cities[city].y;
                  return 8;
                }
              }
            }
          }
        }
        return 8;
      }
      if ((((units[unit].id != 0) && (units[unit].owner != civ)) &&
          ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + units[unit].owner * 4) & 0x20) != 0)) &&
         (unit_types[units[unit].type].domain != 1)) {
        value = (int)units[unit].x;
        y2 = (int)units[unit].y;
        check = map_in_bounds(value,y2);
        if (check != 0) {
          check = unit_max_moves(unit2);
          move_mult = (uint)cosmic.road_move_mult;
          target_dist = map_distance(*(i32 *)x,*(i32 *)y,value,y2);
          if (target_dist <= check / (int)move_mult) {
            score = (int)(char)unit_types[units[unit].type].cost;
            tile_imps = tile_improvements(value,y2);
            if ((((byte)tile_imps & 0x42) == 0x40) ||
               (check = tile_airbase_owner(value,y2), check != 0)) {
              at_airbase = true;
            }
            else {
              at_airbase = false;
            }
            if ((at_airbase) || (check = tile_city_owner(value,y2), -1 < check)) {
              if (!at_airbase) {
                check = unit_stack_sum(unit,2);
                if (check == 1) {
                  score = score << 1;
                }
                for (dir = 0; (int)dir < 8; dir++) {
                  x2 = map_wrap_x((char)(&dir_dx_table)[dir] + value);
                  small_val = (&dir_dy_table)[dir];
                  check = map_in_bounds(x2,small_val + y2);
                  if ((check != 0) &&
                     (check = tile_unit_owner(x2,small_val + y2), check == civ)) {
                    score = score << 1;
                    break;
                  }
                }
              }
            }
            else {
              score = unit_stack_sum(unit,0);
            }
            check = tile_is_ocean(value,y2);
            if (check != 0) {
              score = score << 1;
            }
            tile_imps = tile_improvements(value,y2);
            if (((byte)tile_imps & 0x42) == 0x40) {
              score = score << 1;
            }
            score += (char)unit_types[units[unit].type].hold;
            if (best_score <= score) {
              unit3 = unit;
              best_score = score;
            }
          }
        }
      }
      unit++;
    } while( true );
  }
  if (mode == 3) {
    best_score = 9999;
    best_threat = 9999;
    unit3 = -1;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((((units[unit].id != 0) && (units[unit].owner != civ)) &&
          ((*(byte *)&civs[civ].treaties[units[unit].owner] & 6) == 0)) &&
         (((1 << (civ2 & 0x1f) & (uint)units[unit].visibility) != 0 ||
          ((int)units[unit].owner == (uint)civ2)))) {
        if (unit_types[units[unit].type].domain == 1) {
LAB_00537ec2:
          value = map_distance(*(i32 *)x,*(i32 *)y,
                                      (int)units[unit].x,(int)units[unit].y);
          threat_score = value * 2;
          if (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0) {
            threat_score = threat_score >> 1;
          }
          if (unit_types[units[unit].type].range != '\0') {
            threat_score--;
          }
          y2 = unit_stack_sum(unit,2);
          if (y2 == 1) {
            threat_score--;
          }
          if (threat_score <= best_threat) {
            best_threat = threat_score;
            unit3 = unit;
            best_score = value;
          }
        }
        else {
          if (unit_types[units[unit].type].hold == '\0') {
            value = unit_stack_sum(unit,2);
          }
          else {
            value = unit_stack_sum(unit,5);
          }
          if (value < 2) {
            own_flags = units[unit2].flags;
            stat_a = unit_types[unit_type].attack;
            stat_b = unit_types[unit_type].hit_points;
            att_fp = unit_types[unit_type].firepower;
            defense_power = (int)(char)unit_types[units[unit].type].hit_points *
                       (int)(char)unit_types[units[unit].type].defense *
                       (int)(char)unit_types[units[unit].type].firepower *
                       (3 - (uint)((units[unit].flags & 0x2000) == 0));
            if ((unit_types[units[unit].type].hold != '\0') &&
               (value = unit_stack_sum(unit,2), value == 1)) {
              defense_power = defense_power * 2;
            }
            terrain = tile_terrain((int)units[unit].x,(int)units[unit].y);
            if ((defense_power * (char)terrain_types[terrain].defense >> 1) * 3 <=
                (int)((3 - (uint)((own_flags & 0x2000) == 0)) * (int)(char)stat_a * (int)(char)stat_b *
                      (int)(char)att_fp * 2)) goto LAB_00537ec2;
          }
        }
      }
    }
    if (-1 < unit3) {
      if ((best_score <= range_left) || (range_left < home_dist)) {
        if (((home_dist <= range_left - best_score) && (best_score == 1)) || (range_left < home_dist)) {
          unit_set_goto(unit2,0x41,(int)units[unit3].x,(int)units[unit3].y);
          return 0xffffffff;
        }
        best_threat = 9999;
        for (dir = 0; (int)dir < 8; dir++) {
          x2 = map_wrap_x((int)(char)(&dir_dx_table)[dir] + (int)units[unit3].x);
          value = (int)(char)(&dir_dy_table)[dir] + (int)units[unit3].y;
          y2 = map_in_bounds(x2,value);
          if ((((y2 != 0) && (y2 = tile_city_owner(x2,value), y2 < 0)) &&
              ((y2 = tile_unit_owner(x2,value), y2 < 0 || (civ == y2)))) &&
             (y2 = map_distance(*(i32 *)x,*(i32 *)y,x2,
                                          value), y2 <= best_score - 1)) {
            nearest_city_dist = 9999;
            nearest_city = -1;
            for (city = 0; city < game.num_cities; city++) {
              if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
                 (y2 = map_distance(x2,value,(int)cities[city].x,
                                              (int)cities[city].y), y2 < nearest_city_dist)) {
                nearest_city = city;
                nearest_city_dist = y2;
              }
            }
            if (nearest_city < 0) {
              nearest_city_dist = 0;
            }
            if (nearest_city_dist < best_threat) {
              best_threat = nearest_city_dist;
            }
          }
        }
        if (best_score + best_threat <= range_left) {
          unit_set_goto(unit2,0x41,(int)units[unit3].x,(int)units[unit3].y);
          return 0xffffffff;
        }
      }
      x3 = (int)units[unit3].x;
      y3 = (int)units[unit3].y;
      city = 0;
      do {
        if (game.num_cities <= city) {
          best_score = 999;
          city2 = -1;
          for (city = 0; city < game.num_cities; city++) {
            if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
               ((value = map_distance(*(i32 *)x,*(i32 *)y,
                                             (int)cities[city].x,(int)cities[city].y),
                value <= range_left &&
                (value = map_distance(x3,y3,(int)cities[city].x,
                                             (int)cities[city].y), value < best_score)))) {
              city2 = city;
              best_score = value;
            }
          }
          if (-1 < city2) {
            unit_set_goto(unit2,0x61,(int)cities[city2].x,(int)cities[city2].y);
            return 0xffffffff;
          }
          if (may_go_home != 0) {
            unit_go_home(unit2);
            return 0xffffffff;
          }
          units[unit2].ai_task = 'h';
          return 8;
        }
        if (((cities[city].id != 0) &&
            (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) &&
           ((cities[city].flags & 0x10000) != 0)) {
          city_dist = map_distance(x3,y3,(int)cities[city].x,
                                        (int)cities[city].y);
          if ((*(byte *)&civs[civ].treaties[cities[city].owner] & 0x10) == 0) {
            if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + cities[city].owner * 4) & 0x20) == 0) {
              city_dist = city_dist << 1;
            }
            if ((*(byte *)&civs[civ].treaties[cities[city].owner] & 4) != 0)
            goto LAB_00538277;
          }
          if (city_dist < best_score) {
            best_score = city_dist;
            x3 = (int)cities[city].x;
            y3 = (int)cities[city].y;
          }
        }
LAB_00538277:
        city++;
      } while( true );
    }
    if (may_go_home != 0) {
      unit_go_home(unit2);
      return 0xffffffff;
    }
  }
  if (((mode == 0) && (unit_types[units[unit2].type].range != '\0')) &&
     ((char)unit_types[unit_type].attack < 'c')) {
    if (units[unit2].orders == 11) {
      if ((units[unit2].counter == '\0') && (set_flag != 0)) {
        *(i32 *)out_flag = 1;
        if (*(int *)out_flag != 0) {
          return 0xfffffffe;
        }
        return 0xffffffff;
      }
    }
    else {
      unit3 = -1;
      best_score = -9999;
      if ((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) &&
         ((game.turn == 1 &&
          ((scenario_objective_civ == civ && (value = tile_unit_owner(0x2d,0x35), -1 < value)))))) {
        unit_set_goto(unit2,0x42,0x2d,0x35);
        if (set_flag != 0) {
          *(i32 *)out_flag = 1;
        }
        if (*(int *)out_flag != 0) {
          return 0xfffffffe;
        }
        return 0xffffffff;
      }
      for (city = 0; city < game.num_cities; city++) {
        if (((cities[city].id != 0) && (cities[city].owner != civ)) &&
           ((*(byte *)&civs[civ].treaties[cities[city].owner] & 6) == 0)) {
          value = map_distance(*(i32 *)x,*(i32 *)y,
                                      (int)cities[city].x,(int)cities[city].y);
          y2 = unit_moves_left(unit2);
          if ((value <= y2 / (int)(uint)cosmic.road_move_mult) &&
             (value = tile_first_unit((int)cities[city].x,(int)cities[city].y),
             -1 < value)) {
            small_val = cities[city].size;
            value = unit_stack_sum(value,2);
            score = small_val * 10 + value * -0x19;
            value = tile_landmass((int)cities[city].x,(int)cities[city].y);
            if (value == landmass) {
              score += 0x28;
            }
            for (dir = 0; (int)dir < 8; dir++) {
              x2 = map_wrap_x((int)cities[city].x + (int)(char)(&dir_dx_table)[dir]);
              value = (int)cities[city].y + (int)(char)(&dir_dy_table)[dir];
              y2 = map_in_bounds(x2,value);
              if ((y2 != 0) && (value = tile_unit_owner(x2,value), value == civ)) {
                score += 0x3c;
              }
            }
            if (best_score <= score) {
              best_score = score;
              unit3 = city;
            }
          }
        }
      }
      if (-1 < unit3) {
        unit_set_goto(unit2,0x42,(int)cities[unit3].x,(int)cities[unit3].y);
        if (set_flag != 0) {
          *(i32 *)out_flag = 1;
        }
        if (*(int *)out_flag != 0) {
          return 0xfffffffe;
        }
        return 0xffffffff;
      }
    }
  }
  return 0xffffff9d;
}
#undef scenario_flags
#undef scenario_objective_civ
#undef x3
#undef unit3
#undef best_threat
#undef home_dist
#undef city
#undef threat_score
#undef y3
#undef city_dist
#undef dir
#undef defense_power
#undef city2
#undef range_left
#undef best_score
#undef nearest_city
#undef score

/* 00538a29 auto */
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define cargo_target (*(int *)(frame_ + FRAME_OFF(0)))
#define x4 (*(uint *)(frame_ + FRAME_OFF(12)))
#define work_flags (*(uint *)(frame_ + FRAME_OFF(24)))
#define goal_match (*(int *)(frame_ + FRAME_OFF(28)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(32)))
#define city6 (*(uptr *)(frame_ + FRAME_OFF(40)))
#define in_enemy_zoc (*(int *)(frame_ + FRAME_OFF(48)))
#define civ4 (*(int *)(frame_ + FRAME_OFF(60)))
#define unit_domain (*(int *)(frame_ + FRAME_OFF(68)))
#define trade_target (*(int *)(frame_ + FRAME_OFF(72)))
#define city (*(uptr *)(frame_ + FRAME_OFF(84)))
#define needed_defenders (*(uptr *)(frame_ + FRAME_OFF(108)))
#define is_attack (*(int *)(frame_ + FRAME_OFF(112)))
#define sea_south (*(int *)(frame_ + FRAME_OFF(116)))
#define ally_civ (*(uptr *)(frame_ + FRAME_OFF(120)))
#define y4 (*(int *)(frame_ + FRAME_OFF(124)))
#define near_landmass (*(int *)(frame_ + FRAME_OFF(132)))
#define max_score (*(int *)(frame_ + FRAME_OFF(140)))
#define fort_need (*(int *)(frame_ + FRAME_OFF(148)))
#define ally_territory (*(int *)(frame_ + FRAME_OFF(152)))
#define y3 (*(int *)(frame_ + FRAME_OFF(160)))
#define ai_role (*(uint *)(frame_ + FRAME_OFF(164)))
#define tile_count (*(int *)(frame_ + FRAME_OFF(168)))
#define needs_units (*(int *)(frame_ + FRAME_OFF(172)))
#define damage_level (*(uint *)(frame_ + FRAME_OFF(176)))
#define x2 (*(int *)(frame_ + FRAME_OFF(180)))
#define x3 (*(iptr *)(frame_ + FRAME_OFF(184)))
#define unit4 (*(uptr *)(frame_ + FRAME_OFF(188)))
#define best_dir (*(uptr *)(frame_ + FRAME_OFF(192)))
#define flag (*(uint *)(frame_ + FRAME_OFF(196)))
#define explore_flag (*(i32 *)(frame_ + FRAME_OFF(200)))
#define on_fortress (*(uint *)(frame_ + FRAME_OFF(204)))
#define sea_north (*(int *)(frame_ + FRAME_OFF(208)))
#define goto_city (*(int *)(frame_ + FRAME_OFF(212)))
#define role_count (*(int *)(frame_ + FRAME_OFF(216)))
#define attack_bonus (*(int *)(frame_ + FRAME_OFF(220)))
#define room_aboard (*(uint *)(frame_ + FRAME_OFF(224)))
#define has_orders (*(int *)(frame_ + FRAME_OFF(228)))
#define type_flags (*(u32 *)(frame_ + FRAME_OFF(232)))
#define defender_count (*(int *)(frame_ + FRAME_OFF(236)))
#define unit5 (*(iptr *)(frame_ + FRAME_OFF(240)))
#define retried (*(int *)(frame_ + FRAME_OFF(244)))
#define hold_pos (*(int *)(frame_ + FRAME_OFF(248)))
#define x6 (*(int *)(frame_ + FRAME_OFF(252)))
#define city4 (*(uptr *)(frame_ + FRAME_OFF(256)))
#define home_dist (*(int *)(frame_ + FRAME_OFF(260)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(264)))
#define dir2 (*(uptr *)(frame_ + FRAME_OFF(268)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(272)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(276)))
#define cand_score (*(int *)(frame_ + FRAME_OFF(280)))
#define is_ocean (*(uint *)(frame_ + FRAME_OFF(284)))
#define explore (*(int *)(frame_ + FRAME_OFF(288)))
#define attack_cost (*(int *)(frame_ + FRAME_OFF(292)))
#define dir (*(uptr *)(frame_ + FRAME_OFF(296)))
#define civ3 (*(uptr *)(frame_ + FRAME_OFF(300)))
#define own_landmass (*(int *)(frame_ + FRAME_OFF(304)))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(308)))
#define will_attack (*(int *)(frame_ + FRAME_OFF(312)))
#define sea_east (*(int *)(frame_ + FRAME_OFF(316)))
#define is_guard (*(int *)(frame_ + FRAME_OFF(320)))
#define city5 (*(uptr *)(frame_ + FRAME_OFF(324)))
#define city2 (*(uptr *)(frame_ + FRAME_OFF(328)))
#define own_dist (*(int *)(frame_ + FRAME_OFF(332)))
#define best_score (*(int *)(frame_ + FRAME_OFF(336)))
#define freed_count (*(int *)(frame_ + FRAME_OFF(340)))
#define divisor (*(int *)(frame_ + FRAME_OFF(344)))
#define target_policy (*(uint *)(frame_ + FRAME_OFF(348)))
#define sea_west (*(int *)(frame_ + FRAME_OFF(352)))
#define race_behind (*(int *)(frame_ + FRAME_OFF(356)))
#define no_moves (*(int *)(frame_ + FRAME_OFF(360)))
#define here_landmass (*(int *)(frame_ + FRAME_OFF(364)))
#define score (*(int *)(frame_ + FRAME_OFF(368)))
#define tile_flags (*(uint *)(frame_ + FRAME_OFF(372)))
#define attack_value (*(int *)(frame_ + FRAME_OFF(376)))
#define tasks_mask (*(uint *)(frame_ + FRAME_OFF(380)))
#define ocean_count (*(int *)(frame_ + FRAME_OFF(384)))
i32 __cdecl ai_unit_choose_orders(void)

{
  uint *treaty;
  u8 stat;
  ushort military;
  bool forced_attack;
  bool stay_home;
  bool ally_near;
  byte tile_byte;
  uptr civ;
  i32 result;
  iptr landmass;
  iptr attitude;
  iptr roll;
  int city7;
  uptr city3;
  uptr quota;
  iptr dest_landmass;
  iptr x;
  iptr x5;
  int y;
  uptr here_imps;
  uptr goto_imps;
  byte owner_byte;
  uint terrain;
  byte *tile;
  uptr road_imps;
  int check;
  int near_dist;
  uptr unit_type;
  uint policy;
  bool is_settler;
  bool settler_type;
  bool cond;
  bool trade_drop;
  i32 arg_hi;
  iptr unit2;
  i8 frame_[FRAME_OFF(392)] __attribute__((aligned(8)));  /* original stack frame */
  defender_count = 0x108; needed_defenders = 0x64a8c19c; cand_score = 0x3bd; best_score = 0; goal_match = 4;  /* stale stack the original reads (FRAME_PRESETS) */
  
  near_landmass = -1;
  own_landmass = -1;
  settler_type = false;
  is_settler = false;
  retried = 0;
  hold_pos = 0;
  stay_home = false;
  has_orders = 0;
  forced_attack = false;
  no_moves = 0;
  is_guard = 0;
  goto_city = 0;
  unit = (iptr)game.active_unit;
  owner_byte = units[unit].owner;
  civ = (uptr)(char)owner_byte;
  if (civ == 0) {
    result = ai_barbarian_unit_move();
    return result;
  }
  if ((3 < units[unit].orders) && (units[unit].orders < '\n')) goto LAB_005436c1;
  x2 = (int)units[unit].x;
  y3 = (int)units[unit].y;
  unit_type = (uptr)units[unit].type;
  best_dir = 8;
  near_dist = map_in_bounds(x2,y3);
  if (near_dist == 0) {
    unit_set_sleep(unit);
    goto LAB_005436c1;
  }
  in_enemy_zoc = tile_in_enemy_zoc(x2,y3,civ);
  city4 = city_find_nearest(x2,y3,-1,0xffffffff,-1);
  near_dist = nearest_city_dist;
  if (-1 < (int)city4) {
    near_landmass = tile_land_landmass((int)cities[city4].x,(int)cities[city4].y);
  }
  city2 = city_find_nearest(x2,y3,civ,0xffffffff,-1);
  own_dist = nearest_city_dist;
  if (-1 < (int)city2) {
    own_landmass = tile_land_landmass((int)cities[city2].x,(int)cities[city2].y);
  }
  tile_byte = tile_terrain(x2,y3);
  terrain2 = (uptr)tile_byte;
  landmass = tile_landmass(x2,y3);
  result = tile_improvements(x2,y3);
  on_fortress = (uint)(((byte)result & 0x42) == 0x40);
  if (((8 < own_dist) || (landmass != own_landmass)) &&
     ((1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0)) {
    units[unit].flags = units[unit].flags & 0xfdff;
  }
  ai_role = ai_unit_role(unit);
  type_flags = unit_types[units[unit].type].flags;
  unit_domain = (int)(char)unit_types[units[unit].type].domain;
  policy = (uint)civs[civ].continent_policy[landmass];
  if (((in_enemy_zoc != 0) && (adjacent_foreign_civ != 0)) &&
     ((city2 == city4 && ((*(byte *)&civs[civ].treaties[adjacent_foreign_civ] & 4) != 0))
     )) {
    civ_adjust_attitude(civ,adjacent_foreign_civ,1);
    if ((((1 << ((byte)adjacent_foreign_civ & 0x1f) & (uint)game.human_players) != 0) &&
        (2 < game.difficulty)) &&
       ((attitude = civ_get_attitude(civ,adjacent_foreign_civ), 0x3c < attitude &&
        ((game.power_rank[civ] < game.power_rank[adjacent_foreign_civ] &&
         (roll = rand_range(0,3), roll == 0)))))) {
      treaty = (uint *)(civ * 0x594 + (iptr)((u8 *)&civs + 32) + adjacent_foreign_civ * 4);
      *treaty = *treaty | 0x20;
    }
  }
  city3 = city4;
  if (((((near_dist == 1) && (city2 != city4)) && (unit_domain == 0)) &&
      (((char)unit_types[units[unit].type].role < 6 &&
       (city7 = tile_unit_owner((int)cities[city4].x,(int)cities[city4].y), city7 < 0)))) &&
     ((*(byte *)&civs[civ].treaties[cities[city3].owner] & 0xe) == 0)) {
    units[unit].orders = -1;
    in_enemy_zoc = 1;
    adjacent_foreign_civ = (iptr)cities[city3].owner;
    forced_attack = true;
  }
  damage_level = (uint)(units[unit].damage != '\0');
  if ((int)(char)unit_types[unit_type].hit_points >> 2 < (int)(uint)units[unit].damage) {
    damage_level = 2;
  }
  if ((int)(char)unit_types[unit_type].hit_points >> 1 < (int)(uint)units[unit].damage) {
    damage_level = 3;
  }
  if ((unit_types[units[unit].type].hold != '\0') &&
     (city7 = unit_moves_left(unit), city7 == 0)) {
    no_moves = 1;
    goto LAB_0053be12;
  }
  if (damage_level != 0) {
    ally_territory = 0;
    civ2 = tile_radius_civ(x2,y3);
    if ((((0 < (int)civ2) && ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0)) &&
        ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) &&
       ((int)((uint)civs[civ2].reputation - (int)civs[civ].reputation_credit[civ2])
        < 6)) {
      ally_territory = 1;
    }
    if (near_dist != 0) {
      if (near_dist == 1) {
        if (city4 == city2) {
          unit_set_goto(unit,100,(int)cities[city4].x,(int)cities[city4].y);
          goto LAB_005436c1;
        }
        if (forced_attack) {
          damage_level = 0;
        }
      }
      goto LAB_005392a6;
    }
    hold_pos = 1;
    is_guard = 1;
    goto LAB_0053b8f0;
  }
LAB_005392a6:
  if ((((((damage_level == 0) || (units[unit].moves_used != '\0')) ||
        ((ally_territory != 0 || ((unit_domain != 1 || (unit_types[units[unit].type].range != '\0')))))
        ) || (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 != 0)) ||
      ((own_dist < 0xd || (units[unit].visibility != '\0')))) ||
     (((damage_level != 2 && ((units[unit].flags & 8) == 0)) &&
      ((((damage_level != 3 || (own_dist == 0)) || (own_dist < 0x18)) || (near_dist < 9)))))) {
    units[unit].flags = units[unit].flags & 0xfff7;
    if (((((damage_level != 0) && (units[unit].moves_used == '\0')) && (ally_territory == 0)) &&
        ((unit_domain == 0 ||
         (((unit_domain == 2 && (city7 = unit_stack_sum(unit,2), city7 < 2)) &&
          ((damage_level == 1 || ((int)(uint)units[unit].damage >> 1 <= own_dist / 2)))))))) &&
       (((unit_domain != 2 || ((game.human_players & units[unit].visibility) == 0)) &&
        ((damage_level == 3 ||
         (((int)(char)unit_types[units[unit].type].role != policy || (unit_domain == 2)))))))) {
      if (unit_domain == 0) {
        cond = in_enemy_zoc == 0;
      }
      else {
        city7 = tile_adjacent_nonallied_unit(x2,y3,civ);
        if (city7 == 0) {
          cond = true;
        }
        else {
          cond = false;
        }
      }
      if (cond) {
        units[unit].ai_task = 'd';
        best_dir = 8;
        city3 = best_dir;
        goto LAB_005435ca;
      }
    }
    if (((damage_level == 2) && (unit_domain == 2)) &&
       ((ai_role == 2 ||
        ((ai_role == 4 && (city7 = unit_stack_sum(unit,2), city7 < 2)))))) {
      unit_go_home(unit);
      city7 = unit_moves_left(unit);
      if (city7 == 0) goto LAB_005436c1;
      if (units[unit].orders == 11) {
        has_orders = 1;
        goto LAB_005414d7;
      }
    }
    if (damage_level == 3) {
      units[unit].ai_task = 'D';
      if (((unit_domain == 0) && ((int)ai_role < 2)) &&
         (((((units[unit].flags & 0x100) != 0 ||
            (2 < (char)terrain_types[terrain2].defense)) &&
           ((((ai_role == 1 ||
              (city7 = unit_max_moves(unit), city7 <= (int)(uint)cosmic.road_move_mult))
             || (in_enemy_zoc == 0)) || (8 < own_dist)))) && (ally_territory == 0)))) {
        best_dir = 8;
        city3 = best_dir;
      }
      else {
        if (((unit_domain != 0) || (on_fortress == 0)) || (ally_territory != 0)) {
          if (((ai_role != 4) || (city7 = unit_stack_sum(unit,2), city7 < 2)) &&
             ((unit_go_home(unit), units[unit].orders == 11 ||
              (city7 = unit_moves_left(unit), city7 == 0)))) goto LAB_005436c1;
          goto LAB_005397e7;
        }
        best_dir = 8;
        city3 = best_dir;
      }
    }
    else {
LAB_005397e7:
      if (((((game.game_flags & 0x80) == 0) || (((int)(short)scenario_flags & 0x8000U) == 0)) ||
          (civ != 1)) ||
         (((((*(i8 *)((char *)&civs[1].treaties[3] + 1)) & 0x20) != 0 || (5 < game.turn)) ||
          (0x4f < units[unit].x)))) {
        if (((unit_domain == 0) && (own_dist == 0)) &&
           (((units[unit].flags & 0x100) == 0 &&
            (((cities[city2].flags & 0x200) != 0 && (policy != ai_role)))))) {
          stay_home = true;
        }
        else {
          if (unit_domain == 1) {
            unit4 = ai_air_unit_orders(unit,unit_type,(iptr)&x2,(iptr)&y3,ai_role,
                                          (iptr)&has_orders,own_dist,landmass,in_enemy_zoc);
            if (unit4 == 0xfffffffe) goto LAB_005414d7;
            if (unit4 == 0xffffffff) goto LAB_005436c1;
            city3 = unit4;
            if (-1 < (int)unit4) goto LAB_005435ca;
          }
          if ('b' < (char)unit_types[unit_type].attack) {
            city3 = ai_nuke_pick_target(unit);
            x2 = (int)units[unit].x;
            y3 = (int)units[unit].y;
            goto LAB_005435ca;
          }
          if (ai_role == 6) {
            if ((((units[unit].orders == 11) &&
                 (city7 = city_at((int)units[unit].goto_x,
                                              (int)units[unit].goto_y), -1 < city7)) &&
                ((int)cities[city7].owner != civ)) &&
               ((*(byte *)&civs[civ].treaties[cities[city7].owner] & 0xe) == 0)) {
              has_orders = 1;
            }
            else {
              city7 = tile_is_ocean(x2,y3);
              if (city7 == 0) {
                race_behind = ai_spaceship_race_behind(civ);
                best_score = -999;
                city6 = 0xffffffff;
                for (city = 0; (int)city < (int)game.num_cities; city = city + 1
                    ) {
                  if (cities[city].id != 0) {
                    city7 = tile_landmass((int)cities[city].x,(int)cities[city].y);
                    y = tile_is_ocean(x2,y3);
                    if (y == 0) {
                      if (city7 == landmass) {
LAB_00539cb3:
                        civ2 = (uptr)cities[city].owner;
                        cand_score = map_distance_diag(x2,y3,(int)cities[city].x,
                                                      (int)cities[city].y);
                        if (((uint)(byte)units[unit].home_city % 3 != (int)city % 3) &&
                           (terrain = tile_improvements(x2,y3),
                           (int)(((terrain & 0x10) >> 4) + 3) < cand_score)) {
                          cand_score += 8;
                        }
                        if (civ2 == civ) {
                          score = 99 - cand_score;
                        }
                        else {
                          score = 100;
                          if ((*(byte *)&civs[civ].treaties[civ2] & 0xe) != 0) {
                            if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) ||
                                ((cities[city].flags & 8) != 0)) ||
                               ((city7 = ai_spaceship_race_behind(civ), city7 == 0 &&
                                ((game.power_rank[civ2] < game.power_rank[civ] ||
                                 ((((units[unit].type != '/' &&
                                    ((int)((uint)civs[civ2].num_advances -
                                          (uint)civs[civ].num_advances) < 10)) &&
                                   (((4 < civs[civ].government || (game.power_rank[civ2] < 7))
                                    || (((*(byte *)&civs[civ].treaties[civ2] & 8) !=
                                         0 && (civs[civ2].num_advances <
                                               civs[civ].num_advances)))))) ||
                                  (((*(byte *)&civs[civ].treaties[civ2] & 8) == 0 &&
                                   (((4 < civs[civ2].government &&
                                     (civs[civ].continent_military[landmass] <
                                      civs[civ2].continent_attack[landmass])) &&
                                    (*(char *)&civs[civ].continent_cities[landmass] != '\0')))))))))))
                               ) goto LAB_00539b29;
                            score = score / 2;
                          }
                          if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 0x20) == 0) {
                            city7 = civ_get_attitude(civ,civ2);
                            score += city7;
                          }
                          else {
                            score += 100;
                          }
                          score = score / (cand_score + 1);
                          if ((cities[city].flags & 8) != 0) {
                            score = score / 2;
                            if (civs[civ].num_advances + 6 < (uint)civs[civ2].num_advances) {
                              score = score / 2;
                            }
                            if (race_behind != 0) {
                              score = 1;
                            }
                          }
                          score += 100;
                        }
                        if (best_score < score) {
                          best_score = score;
                          city6 = city;
                        }
                      }
                    }
                    else {
                      flag = 0;
                      for (dir = 0; (int)dir < 8; dir++) {
                        x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
                        y2 = (char)(&dir_dy_table)[dir] + y3;
                        y = map_in_bounds(x,y2);
                        if (((y != 0) && (y = tile_is_ocean(x,y2), y == 0)
                            ) && (y = tile_landmass(x,y2), y == city7)) {
                          flag = 1;
                          break;
                        }
                      }
                      if (flag != 0) goto LAB_00539cb3;
                    }
                  }
LAB_00539b29: ;
                }
                if ((int)city6 < 0) {
                  if (units[unit].orders != 11) {
                    unit_destroy_redraw(unit,1);
                    return 1;
                  }
                  goto LAB_005436c1;
                }
                has_orders = 1;
                if ((units[unit].orders != 11) || ((int)cities[city6].owner != civ)) {
                  unit_set_goto(unit,0x53,(int)cities[city6].x,
                                     (int)cities[city6].y);
                }
              }
            }
            goto LAB_005414d7;
          }
          if (ai_role == 7) {
            if (units[unit].orders == 11) goto LAB_005436c1;
            city7 = tile_is_ocean(x2,y3);
            if (city7 != 0) {
              city6 = 0xffffffff;
              best_score = 0;
              for (dir = 0; (int)dir < 8; dir++) {
                x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
                y2 = (char)(&dir_dy_table)[dir] + y3;
                city7 = map_in_bounds(x,y2);
                if (((city7 != 0) && (city7 = tile_is_ocean(x,y2), city7 == 0)) &&
                   (city7 = tile_landmass(x,y2),
                   *(char *)&civs[civ].continent_flags[city7] != '\0')) {
                  score = 0;
                  for (civ2 = 1; (int)civ2 < 8; civ2++) {
                    if (civ2 == civ) {
                      city7 = (int)(civs[civ].continent_city_size[landmass] + 1) >> 1;
                    }
                    else {
                      city7 = (uint)civs[civ].continent_city_size[landmass] * 2;
                    }
                    score += city7;
                  }
                  if (best_score < score) {
                    best_score = score;
                    city6 = dir;
                  }
                }
              }
              if (-1 < (int)city6) {
                units[unit].ai_task = 't';
                best_dir = city6;
                city3 = best_dir;
                goto LAB_005435ca;
              }
            }
            best_score = 0;
            city6 = 0xffffffff;
            if (units[unit].home_city == -1) {
              city5 = 0xffffffff;
            }
            else {
              city5 = (uptr)(byte)units[unit].home_city;
            }
            if ((int)city5 < 0) {
              city5 = city2;
            }
            if ((int)city5 < 0) {
              unit_destroy_redraw(unit,1);
              return 1;
            }
            for (city = 0; (int)city < (int)game.num_cities; city++) {
              if ((cities[city].id != 0) &&
                 (city7 = tile_landmass((int)cities[city].x,(int)cities[city].y),
                 city7 == landmass)) {
                flag = 1;
                for (dir = 0; (int)dir < (int)(char)cities[city5].trade_routes;
                    dir = dir + 1) {
                  if ((int)cities[city5].route_partner[dir] == city) {
                    flag = 0;
                  }
                }
                city7 = map_distance_diag((int)cities[city].x,(int)cities[city].y,
                                            (int)cities[city5].x,(int)cities[city5].y);
                cand_score = (((int)cities[city5].base_trade + (int)cities[city].base_trade) *
                           city7) / 0x18;
                if ((int)cities[city].owner == civ) {
                  cand_score = cand_score / 2;
                }
                else {
                  arg_hi = 100;
                  result = 0;
                  x = civ_get_attitude(civ,(int)cities[city].owner);
                  unit4 = int_clamp(x,result,arg_hi);
                  cand_score = (int)((200 - unit4) * cand_score) / 100;
                }
                if (flag == 0) {
                  cand_score = cand_score / 2;
                }
                cand_score = ((5 - (char)cities[city].trade_routes) * cand_score) / 5;
                if ((((-1 < (int)city4) && (city2 != city4)) && (landmass == near_landmass)) &&
                   ((cities[city].owner != cities[city4].owner &&
                    (cand_score = cand_score / 3,
                    ((uint)game.human_players & 1 << (cities[city4].owner & 0x1fU)) != 0)))) {
                  cand_score = cand_score / 2;
                }
                if (best_score < cand_score) {
                  best_score = cand_score;
                  city6 = city;
                }
              }
            }
            if (-1 < (int)city6) {
              unit_set_goto(unit,99,(int)cities[city6].x,(int)cities[city6].y);
              goto LAB_005436c1;
            }
            if (units[unit].home_city != -1) {
              tile_byte = units[unit].home_city;
              city7 = tile_landmass((int)cities[tile_byte].x,(int)cities[tile_byte].y);
              if (city7 == landmass) {
                unit_set_goto(unit,99,(int)cities[tile_byte].x,(int)cities[tile_byte].y);
                goto LAB_005436c1;
              }
            }
          }
          is_settler = ai_role == 5;
          settler_type = unit_types[units[unit].type].role == 5;
          best_score = tile_owner_or_fertility(x2,y3);
          if (((near_dist < 4) && (landmass == near_landmass)) && (7 < best_score)) {
            best_score = 8;
          }
          city7 = tile_is_ocean(x2,y3);
          if (city7 != 0) {
            best_score = 0;
          }
          if ((((is_settler) &&
               (civ_clear_standing_goals_near(civ,5,x2,y3,0), civs[civ].num_cities == 0)) &&
              (game.turn == 1)) &&
             (((start_x[civs[civ].tribe] == x2 && (start_y[civs[civ].tribe] == y3))
              && (7 < best_score)))) {
            unit_found_city(unit,-1,0);
            return 1;
          }
          city = city4;
          if (((best_score != 0) && (((int)ai_role < 2 || (settler_type)))) && (!forced_attack)) {
            best_dir = 0xffffffff;
            if (is_settler) {
              tile_count = 0x14;
            }
            else {
              tile_count = 8;
            }
            for (dir = 0; (int)dir < tile_count; dir++) {
              x = map_wrap_x((char)(&city_tile_dx_table)[dir] + x2);
              y2 = (char)(&city_tile_dy_table)[dir] + y3;
              city7 = map_in_bounds(x,y2);
              if (((city7 != 0) && (city7 = tile_is_ocean(x,y2), city7 == 0)) &&
                 (city7 = tile_landmass(x,y2), city7 == landmass)) {
                score = tile_owner_or_fertility(x,y2);
                if (best_score < score) {
                  best_dir = dir;
                  best_score = score;
                }
                city7 = tile_has_hut(x,y2);
                if (((city7 != 0) && ((int)ai_role < 2)) && ((int)dir < 8)) {
                  best_dir = dir;
                  units[unit].ai_task = 'U';
                  city3 = best_dir;
                  goto LAB_005435ca;
                }
              }
            }
            if (((7 < best_score) && (in_enemy_zoc == 0)) &&
               (((0xf - near_dist <= best_score ||
                 (((is_settler && ((int)best_dir < 0)) &&
                  (*(char *)&civs[civ].continent_cities[landmass] == '\0')))) ||
                (((is_settler && ((int)best_dir < 0)) &&
                 (units[unit].aux_timer = units[unit].aux_timer + 1,
                 4 < (char)units[unit].aux_timer)))))) {
              if (is_settler) {
                if ((int)best_dir < 0) {
                  unit_found_city(unit,-1,0);
                  return 1;
                }
                units[unit].ai_task = '2';
                city3 = best_dir;
                if ((int)best_dir < 8) goto LAB_005435ca;
                city7 = (char)(&city_tile_dy_table)[best_dir] + y3;
                result = map_wrap_x((char)(&city_tile_dx_table)[best_dir] + x2);
                unit_set_goto(unit,0x32,result,city7);
              }
              else if ((-1 < (int)best_dir) && ((int)best_dir < 8)) {
                y = 2;
                arg_hi = 5;
                city7 = (char)(&city_tile_dy_table)[best_dir] + y3;
                result = map_wrap_x((char)(&city_tile_dx_table)[best_dir] + x2);
                civ_add_standing_goal(civ,result,city7,arg_hi,y);
              }
            }
          }
          if (((((((is_settler) && (game.difficulty != '\0')) && (-1 < (int)city4)) &&
                ((city = city4,
                 ((uint)game.human_players & 1 << (cities[city4].owner & 0x1fU)) != 0 &&
                 (in_enemy_zoc == 0)))) && (1 < near_dist)) &&
              ((civs[civ].num_advances < civs[cities[city4].owner].num_advances &&
               (score = tile_get_fertility(x2,y3), 8 < score)))) &&
             (0xe - near_dist <= score)) {
            unit_found_city(unit,-1,0);
            return 1;
          }
          if ((unit_types[units[unit].type].flags & 0x100) != 0) {
            if (own_dist == 0) {
              if ((units[unit].moves_used == '\0') && (units[unit].orders != 11)) {
                best_score = 0;
                for (city = 0; (int)city < (int)game.num_cities; city = city + 1
                    ) {
                  if ((((cities[city].id != 0) && ((int)cities[city].owner != civ)) &&
                      ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + cities[city].owner * 4) & 0x20) !=
                       0)) && (city7 = map_distance(x2,y3,
                                                           (int)cities[city].x,
                                                           (int)cities[city].y),
                              city7 <= (int)(uint)cosmic.paradrop_range)) {
                    city7 = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
                    if ((city7 < 0) && (best_score < cities[city].size + 999)) {
                      best_score = cities[city].size + 999;
                      x6 = (int)cities[city].x;
                      y4 = (int)cities[city].y;
                    }
                    if (0 < best_score) {
                      best_score = 0;
                      city6 = 0xffffffff;
                      for (dir = 9; -1 < (int)dir; dir--) {
                        x = map_wrap_x((char)(&dir_dx_table)[dir] + x6);
                        y2 = (char)(&dir_dy_table)[dir] + y4;
                        city7 = map_in_bounds(x,y2);
                        if ((city7 != 0) &&
                           (city7 = map_distance(x2,y3,x,y2),
                           city7 <= (int)(uint)cosmic.paradrop_range)) {
                          civ2 = tile_unit_owner(x,y2);
                          if (civ2 == civ) {
                            city6 = 0xffffffff;
                            break;
                          }
                          if ((int)civ2 < 0) {
                            score = 0;
                            if (dir == 8) {
                              score = 500;
                            }
                            result = tile_improvements(x,y2);
                            if (((byte)result & 0x42) == 0x40) {
                              score += 0x32;
                            }
                            tile_byte = tile_terrain(x,y2);
                            score += (char)terrain_types[tile_byte].defense * 3;
                            city7 = map_distance(x2,y3,x,y2);
                            score += city7;
                            if (best_score < score) {
                              city6 = dir;
                              best_score = score;
                            }
                          }
                        }
                      }
                      if (-1 < (int)city6) {
                        x6 = map_wrap_x((char)(&dir_dx_table)[city6] + x6);
                        unit_paradrop(unit,x6,
                                           y4 + (char)(&dir_dy_table)[city6]);
                        return 0;
                      }
                    }
                  }
                }
              }
              if (units[unit].orders != 11) {
                hold_pos = 1;
                goto LAB_005414d7;
              }
            }
            else {
              if (((city2 == city4) && (landmass == own_landmass)) &&
                 (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 == 0)) {
                unit_set_goto(unit,99,(int)cities[city].x,(int)cities[city].y);
                goto LAB_005436c1;
              }
              if ((on_fortress != 0) && (city7 = unit_stack_sum(unit,2), city7 == 1)) {
                units[unit].ai_task = 'F';
                best_dir = 8;
                goto LAB_005436c1;
              }
            }
          }
        }
        if ((unit_type == 9) && (units[unit].moves_used == '\0')) {
          if (in_enemy_zoc == 0) {
            if ((char)units[unit].counter < 15) {
              units[unit].counter++;
            }
          }
          else if (units[unit].counter != '\0') {
            units[unit].counter += 0xff;
          }
          if ('\t' < (char)units[unit].counter) {
            on_fortress = 0;
          }
          if (on_fortress != 0) {
            best_score = 9999;
            city6 = 0xffffffff;
            for (city = 0; (int)city < (int)game.num_cities; city++) {
              if ((((cities[city].id != 0) && (city != city4)) &&
                  (city7 = tile_landmass((int)cities[city].x,(int)cities[city].y),
                  city7 == landmass)) &&
                 ((cand_score = map_distance_diag(x2,y3,(int)cities[city].x,
                                                 (int)cities[city].y), cand_score < best_score ||
                  ((cand_score == best_score && ((int)cities[city].owner == civ)))))) {
                city6 = city;
                best_score = cand_score;
              }
            }
            if ((city2 != city4) &&
               (((int)city6 < 0 || ((int)cities[city6].owner != civ)))) {
              on_fortress = 0;
            }
          }
        }
        if ((((on_fortress == 0) || (unit4 = tile_radius_civ(x2,y3), (int)unit4 < 1))
            || (unit4 == civ)) ||
           ((((*(byte *)&civs[civ].treaties[unit4] & 4) != 0 &&
             ((int)((uint)civs[unit4].reputation -
                   (int)civs[civ].reputation_credit[unit4]) < 7)) &&
            (((*(byte *)&civs[civ].treaties[unit4] & 8) != 0 || (2 < own_dist)))))) {
LAB_0053b8f0:
          if (own_dist == 0) {
            role_count = unit_stack_count_role(unit,1);
            if (((ai_role == 1) && (1 < role_count)) || (ai_role == 4)) {
              city7 = tile_zoc_unit_adjacent(x2,y3,civ);
              if (city7 == 0) {
                divisor = 4;
              }
              else {
                divisor = 3;
              }
              city7 = city_has_improvement(city2,1);
              if (city7 == 0) {
                if (policy == 5) {
                  divisor++;
                }
              }
              else {
                divisor--;
              }
              quota = (int)cities[city2].size / divisor + 1;
              city7 = city_has_improvement(city2,1);
              needed_defenders = quota;
              if (city7 != 0) {
                unit4 = 1;
                if (3 < cities[city2].size) {
                  unit4 = 2;
                }
                if (7 < civs[civ].num_cities) {
                  unit4 = 3;
                }
                if (0xb < civs[civ].num_cities) {
                  unit4 = 4;
                }
                needed_defenders = unit4;
                if ((int)unit4 <= (int)quota) {
                  needed_defenders = quota;
                }
              }
            }
            if (ai_role == 1) {
              if (role_count < 2) {
                is_guard = 1;
              }
              else {
                defender_count = unit_stack_best_defender(unit,-1);
                if (unit == defender_count) {
                  is_guard = 1;
                }
                else {
                  if (role_count < (int)needed_defenders) {
                    civ_add_ai_goal(civ,x2,y3,1,3);
                  }
                  if ((int)needed_defenders < role_count) {
                    unit4 = (uptr)units[unit].orders;
                    units[unit].orders = 2;
                    city7 = unit_stack_best_defender(unit,-1);
                    if ((city7 == unit) &&
                       (city7 = unit_stack_sum(unit,4), city7 <= (int)needed_defenders)) {
                      units[unit].orders = (i8)unit4;
                      is_guard = 1;
                    }
                    else {
                      units[unit].orders = (i8)unit4;
                      if (((game.turn + unit & 7U) == 0) &&
                         (((units[unit].orders == 3 || (units[unit].orders == 1)
                           ) || (units[unit].orders == 2)))) {
                        units[unit].orders = -1;
                      }
                    }
                  }
                  else {
                    is_guard = 1;
                  }
                }
              }
            }
            else {
              city7 = unit_stack_sum(unit,2);
              if ((city7 < 2) &&
                 ((civ_add_ai_goal(civ,x2,y3,1,5), !settler_type ||
                  (city7 = tile_zoc_unit_adjacent(x2,y3,civ), city7 != 0)))) {
                is_guard = 1;
              }
            }
          }
          if (is_guard == 0) {
            if (stay_home) {
              hold_pos = 1;
            }
            if (hold_pos == 0) {
LAB_0053be12:
              do {
                if (unit_domain == 2) {
                  tasks_mask = 0;
                  freed_count = 0;
                  defender_count = 0;
                  unit5 = unit;
                  for (unit = unit_stack_first(unit); unit2 = unit5, -1 < unit;
                      unit = unit_next_in_stack(unit)) {
                    if (unit_types[units[unit].type].domain == '\0') {
                      if (units[unit].orders == 2) {
                        if (((own_dist == 0) && (defender_count = defender_count + 1, (int)needed_defenders < defender_count)
                            ) && ((policy == 4 || (freed_count == 0)))) {
                          units[unit].orders = -1;
                          tasks_mask = tasks_mask | 1 << (unit_types[units[unit].type].role & 0x1f);
                          freed_count++;
                        }
                      }
                      else if ((unit_types[units[unit].type].role == 1) &&
                              (defender_count < (int)needed_defenders)) {
                        defender_count++;
                        units[unit].orders = 1;
                      }
                      else {
                        units[unit].orders = -1;
                        tasks_mask = tasks_mask | 1 << (unit_types[units[unit].type].role & 0x1f);
                        freed_count++;
                      }
                    }
                  }
                  unit = unit5;
                  if (ai_role == 2) {
                    civ_clear_standing_goals_near(civ,2,x2,y3,0);
                    civ_clear_standing_goals_near(civ,0x12,x2,y3,0);
                  }
                  if (ai_role == 4) {
                    if ((near_dist == 0) && ((char)units[unit2].counter < '\0')) {
                      units[unit2].counter = (byte)game.turn & 7;
                    }
                    if (((tasks_mask & 0xffffff7f) == 0x20) &&
                       (freed_count < (char)unit_types[units[unit2].type].hold)) {
                      room_aboard = 1;
                    }
                    else {
                      room_aboard = 0;
                    }
                    if ((tasks_mask == 0x20) && (units[unit2].orders != 11)) {
                      unit4 = 1;
                    }
                    else {
                      unit4 = 0;
                    }
                    flag = (uint)(no_moves == 0);
                    if (no_moves == 0) {
                      if ((near_dist == 0) || (unit4 != 0)) {
                        cargo_target = (int)(char)unit_types[units[unit2].type].hold;
                        if (2 < cargo_target) {
                          cargo_target = 3;
                        }
                      }
                      else {
                        cargo_target = 1;
                      }
                      if ((freed_count < cargo_target) || (room_aboard != 0)) {
                        flag = room_aboard;
                        best_score = 999;
                        trade_target = 0;
                        for (city = 0; (int)city < (int)game.num_cities;
                            city = city + 1) {
                          if ((((cities[city].id != 0) &&
                               ((int)cities[city].owner == civ)) &&
                              ((cities[city].flags & 0x80) != 0)) &&
                             (((cities[city].flags & 0x200) == 0 ||
                              (((char)units[unit2].counter < '\0' &&
                               ((int)(char)units[unit2].counter == -1 - (city & 0x3f))))))) {
                            dest_landmass = tile_landmass((int)cities[city].x,(int)cities[city].y
                                                  );
                            if (own_dist == 0) {
                              city7 = cities_share_ocean(city2,city);
                            }
                            else {
                              city7 = city_adjacent_to_body(city,landmass);
                            }
                            if (city7 != 0) {
                              needs_units = 0;
                              military = civs[civ].continent_military[dest_landmass];
                              city7 = ai_continent_defense_quota(civ,dest_landmass);
                              if (((int)(uint)military < city7) &&
                                 (*(char *)&civs[civ].continent_policy[dest_landmass] != 4)) {
                                if (*(char *)&civs[civ].continent_trade_units[dest_landmass] == '\0')
                                goto LAB_0053c1e5;
                                needs_units = 1;
                              }
                              cand_score = map_distance_diag(x2,y3,
                                                            (int)cities[city].x,
                                                            (int)cities[city].y);
                              unit3 = tile_first_unit((int)cities[city].x,
                                                            (int)cities[city].y);
                              if ((-1 < unit3) &&
                                 (city7 = unit_stack_count_role(unit3,4),
                                 (int)(uint)(cand_score == 0) < city7)) {
                                cand_score += 0x10;
                              }
                              if ((*(char *)&civs[civ].continent_policy[dest_landmass] == 4) ||
                                 (*(char *)&civs[civ].continent_flags[dest_landmass] == '\0')) {
                                cand_score = cand_score -
                                           ((int)(uint)*(ushort *)
                                                        (dest_landmass * 2 + (iptr)((u8 *)&civs + 530) + civ * 0x594) >> 2
                                           );
                              }
                              else {
                                cand_score += 0x10;
                              }
                              if (cand_score < best_score) {
                                best_score = cand_score;
                                city6 = city;
                                trade_target = needs_units;
                                target_policy = (uint)civs[civ].continent_policy[dest_landmass];
                                unit_set_goto(unit2,0x33,(int)cities[city].x,
                                                   (int)cities[city].y);
                              }
                            }
                          }
LAB_0053c1e5: ;
                        }
                        if (((near_dist == 0) &&
                            ((((int)(char)units[unit2].counter ^ (int)game.turn - 1U & 3) & 3) != 0)
                            ) && (((tasks_mask & 0x20) == 0 ||
                                  ((tasks_mask == 0x20 ||
                                   (freed_count < (char)unit_types[units[unit2].type].hold)))))) {
                          best_score = 1000;
                        }
                        if (target_policy == 4) {
                          cand_score = 4;
                        }
                        else {
                          cand_score = 2;
                        }
                        if (best_score < cand_score * 3) {
                          units[unit2].counter = 0xff - ((byte)city6 & 0x3f);
                          cities[city6].flags = cities[city6].flags | 0x600;
                          if (trade_target == 0) {
                            result = 5;
                            x = tile_first_unit((int)units[unit2].goto_x,
                                                        (int)units[unit2].goto_y);
                            city7 = unit_stack_count_role(x,result);
                            if (city7 == 0) {
                              if (target_policy != 5) {
                                civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                   (int)units[unit2].goto_y,5,cand_score);
                              }
                              if (target_policy != 5) {
                                civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                   (int)units[unit2].goto_y,0x15,cand_score - 1);
                              }
                            }
                            if (target_policy != 1) {
                              civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                 (int)units[unit2].goto_y,1,cand_score);
                            }
                            if (target_policy != 0) {
                              civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                 (int)units[unit2].goto_y,0,cand_score);
                            }
                            if ((target_policy == 4) || (target_policy == 5)) {
                              civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                 (int)units[unit2].goto_y,6,cand_score);
                            }
                          }
                          civ_add_ai_goal(civ,(int)units[unit2].goto_x,(int)units[unit2].goto_y
                                             ,7,2);
                        }
                        else if (((own_dist == 0) &&
                                 (city7 = unit_stack_count_role(unit2,4), city7 < 2)) &&
                                (((city7 = rand_range(0,3), city7 != 0 ||
                                  (best_score == 1000)) &&
                                 ((civs[civ].continent_flags[landmass] & 0x10) == 0)))) {
                          military = civs[civ].continent_military[landmass];
                          city7 = ai_continent_defense_quota(civ,landmass);
                          city3 = city2;
                          if ((city7 <= (int)(uint)military) || (policy == 4)) {
                            needs_units = 1;
                          }
                          if (*(char *)&civs[civ].continent_trade_units[landmass] != '\0') {
                            trade_target = 1;
                          }
                          if ((needs_units != 0) || (trade_target != 0)) {
                            cities[city2].flags = cities[city2].flags | 0x600;
                            if (needs_units != 0) {
                              result = 5;
                              x = tile_first_unit((int)cities[city2].x,
                                                          (int)cities[city2].y);
                              near_dist = unit_stack_count_role(x,result);
                              if ((near_dist == 0) && (policy != 5)) {
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,5,cand_score);
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,0x15,cand_score - 1);
                              }
                              if (policy != 1) {
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,1,cand_score);
                              }
                              if (policy != 0) {
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,0,cand_score);
                              }
                              if ((policy == 4) || (policy == 5)) {
                                civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                   (int)units[unit2].goto_y,6,cand_score);
                              }
                            }
                            civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y,7,2
                                              );
                            best_dir = 8;
                            city3 = best_dir;
                            goto LAB_005435ca;
                          }
                        }
                      }
                    }
                    if (own_dist == 0) {
                      for (unit4 = unit_stack_first(unit2); -1 < (int)unit4;
                          unit4 = unit_next_in_stack(unit4)) {
                        if (unit_types[units[unit4].type].role == 5) {
                          unit_relocate_in_place(unit4,1);
                          break;
                        }
                      }
                    }
                    if (((((flag != 0) && (units[unit2].ai_task == 'A')) &&
                         (units[unit2].orders == 11)) &&
                        ((near_dist != 0 &&
                         (city7 = city_at((int)units[unit2].goto_x,
                                                      (int)units[unit2].goto_y), -1 < city7)))) &&
                       (((cities[city7].flags & 0x80) != 0 &&
                        ((city7 = city_adjacent_to_body(city7,landmass), city7 != 0 &&
                         ((game.turn & 0xfU) != 0)))))) {
                      flag = 0;
                    }
                    if (((flag != 0) || (retried != 0)) || (no_moves != 0)) {
                      cond = tasks_mask == 0x80;
                      for (dir = 0; (int)dir < 8; dir++) {
                        x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
                        y2 = (char)(&dir_dy_table)[dir] + y3;
                        city7 = map_in_bounds(x,y2);
                        if (((city7 != 0) && (city7 = tile_is_ocean(x,y2), city7 == 0)
                            ) && ((civ2 = tile_unit_owner(x,y2), (int)civ2 < 0 ||
                                  (civ2 == civ)))) {
                          if (civ2 == civ) {
                            result = 2;
                            x5 = tile_first_unit(x,y2);
                            city7 = unit_stack_sum(x5,result);
                            if (1 < city7) goto LAB_0053cdd1;
                          }
                          ally_near = false;
                          if (((-1 < (int)city4) && ((int)cities[city4].owner != civ)) &&
                             (((*(byte *)&civs[civ].treaties[cities[city4].owner] & 4
                               ) != 0 && (near_dist < 4)))) {
                            ally_near = true;
                          }
                          city7 = tile_landmass(x,y2);
                          city3 = city4;
                          needs_units = 0;
                          trade_drop = false;
                          explore_flag = 0;
                          if ((tasks_mask & 0x80) == 0) {
                            if (ally_near) goto LAB_0053cdd1;
                          }
                          else if (city7 == near_landmass) {
                            city5 = 0xffffffff;
                            for (unit4 = unit_stack_first(unit2); -1 < (int)unit4;
                                unit4 = unit_next_in_stack(unit4)) {
                              if (unit_types[units[unit4].type].role == 7) {
                                if (units[unit4].home_city == -1) {
                                  city5 = 0xffffffff;
                                }
                                else {
                                  city5 = (uptr)(byte)units[unit4].home_city;
                                }
                              }
                            }
                            if ((int)city5 < 0) {
                              city5 = city_find_nearest(x,y2,civ,0xffffffff,-1);
                            }
                            if ((int)city5 < 1) {
                              city5 = 0;
                            }
                            trade_drop = units[unit2].ai_task != '3';
                            y = tile_landmass((int)cities[city5].x,(int)cities[city5].y);
                            if ((y == near_landmass) &&
                               (y = map_distance_diag((int)cities[city3].x,
                                                            (int)cities[city3].y,
                                                            (int)cities[city5].x,
                                                            (int)cities[city5].y), y < 0x10)
                               ) {
                              trade_drop = false;
                            }
                            if ((int)cities[city3].owner == civ) {
                              if (cities[city3].size < 8) {
                                trade_drop = false;
                              }
                              y = map_distance_diag((int)cities[city3].x,
                                                          (int)cities[city3].y,
                                                          (int)cities[city5].x,
                                                          (int)cities[city5].y);
                              if (y < 0x10) {
                                trade_drop = false;
                              }
                            }
                            for (dir2 = 0;
                                (int)dir2 < (int)(char)cities[city5].trade_routes;
                                dir2 = dir2 + 1) {
                              if ((int)cities[city5].route_partner[dir2] ==
                                  city3) {
                                trade_drop = false;
                              }
                            }
                          }
                          military = civs[civ].continent_military[city7];
                          y = ai_continent_defense_quota(civ,city7);
                          if (((int)(uint)military < y) &&
                             (*(char *)&civs[civ].continent_policy[city7] != 4)) {
                            needs_units = 1;
                          }
                          if ((*(char *)&civs[civ].continent_cities[city7] == '\0') &&
                             (civs[civ].continent_military[city7] < 8)) {
                            needs_units = 1;
                          }
                          if ((1 << (civs[civ].continent_policy[city7] & 0x1f) & tasks_mask
                              & 3) != 0) {
                            needs_units = 1;
                          }
                          if (((((tasks_mask & 1) != 0) && (-1 < (int)city4)) &&
                              (city2 != city4)) &&
                             (((10 < own_dist && (near_dist < 4)) &&
                              ((city7 == near_landmass &&
                               ((((uint)game.human_players & 1 << (cities[city4].owner & 0x1fU))
                                 != 0 && ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) +
                                                    cities[city4].owner * 4) & 0x20) != 0))))))))
                          {
                            needs_units = 1;
                          }
                          if (((units[unit2].orders == 11) &&
                              (y = tile_landmass((int)units[unit2].goto_x,
                                                      (int)units[unit2].goto_y), y == city7))
                             && (units[unit2].ai_task != '3')) {
                            needs_units = 1;
                            goal_match = 1;
                          }
                          if (((tasks_mask & 0x20) == 0) &&
                             (*(char *)&civs[civ].continent_flags[city7] == '\0')) {
                            if ((*(short *)&civs[civ].continent_military[city7] == 0) &&
                               (0x31 < *(short *)(&landmass_table + city7 * 0x10))) {
                              civs[civ].continent_flags[city7] =
                                   civs[civ].continent_flags[city7] | 0x80;
                              explore_flag = 1;
                            }
                            else {
                              needs_units = 0;
                            }
                          }
                          if ((room_aboard != 0) &&
                             ((civs[civ].continent_flags[city7] & 5) != 0)) {
                            needs_units = 0;
                          }
                          if (1 < (int)damage_level) {
                            needs_units = 1;
                          }
                          if ((((room_aboard == 0) &&
                               (y = tile_city_owner(x,y2), -1 < y)) &&
                              (civ2 != civ)) &&
                             (y = diplo_is_hostile(civ,civ2), y != 0)) {
                            needs_units = 1;
                          }
                          if (cond) {
                            needs_units = 0;
                          }
                          if (goal_match != 0) {
                            if (cond) {
                              if (!trade_drop) {
                                units[unit2].counter = (byte)game.turn & 7;
                              }
                            }
                            else if (needs_units == 0) {
                              units[unit2].counter = (byte)game.turn & 7;
                            }
                          }
                          if (((needs_units != 0) && (4 < *(short *)(&landmass_fertile_tiles + city7 * 0x10)))
                             && ((1 < (int)y2 && ((int)y2 < map.height - 2)))) {
                            y = unit_moves_left(unit2);
                            if ((((int)(uint)cosmic.road_move_mult <= y) &&
                                ((near_dist != 0 || (policy != 1)))) &&
                               ((best_dir = ai_ship_best_landing_dir(unit2), -1 < (int)best_dir &&
                                (best_dir != 8)))) {
                              units[unit2].ai_task = 'b';
                              city3 = best_dir;
                              goto LAB_005435ca;
                            }
                            if (*(char *)&civs[civ].continent_policy[city7] == '\0') {
                              civ_add_ai_goal(civ,x2,y3,2,5);
                            }
                            units[unit2].ai_task = 'U';
                            unit_exhaust_moves(unit2);
                            units[unit2].orders = -1;
                            if (!trade_drop) {
                              tasks_mask = tasks_mask & 0xffffff7f;
                            }
                            unit_stack_wake_by_role(unit2,tasks_mask,explore_flag);
                            goto LAB_005436c1;
                          }
                          if (((trade_drop) && (1 < (int)y2)) && ((int)y2 < map.height - 2)
                             ) {
                            if (*(char *)&civs[civ].continent_policy[city7] == '\0') {
                              civ_add_ai_goal(civ,x2,y3,2,5);
                            }
                            units[unit2].ai_task = 'u';
                            unit_exhaust_moves(unit2);
                            tasks_mask = 0x80;
                            if (!ally_near) {
                              tasks_mask = 0x82;
                            }
                            unit_stack_wake_by_role(unit2,tasks_mask,explore_flag);
                            units[unit2].orders = -1;
                            goto LAB_005436c1;
                          }
                          if ((game.turn & 3U) == 0) {
                            units[unit2].orders = -1;
                          }
                        }
LAB_0053cdd1: ;
                      }
                      city7 = unit_moves_left(unit2);
                      if ((city7 <= (int)(uint)cosmic.road_move_mult) &&
                         (units[unit2].orders == 11)) {
                        x4 = units[unit2].goto_x + x2 >> 1;
                        y2 = units[unit2].goto_y + y3 >> 1;
                        if ((x4 & 1) != 0) {
                          x4--;
                        }
                        if ((y2 & 1) != 0) {
                          x4++;
                        }
                        civ_add_ai_goal(civ,x4,y2,2,3);
                      }
                    }
                  }
                  if (no_moves != 0) {
                    return 1;
                  }
                  if ((ai_role == 4) || (in_enemy_zoc == 0)) {
                    if ((units[unit2].orders != 11) &&
                       (((tasks_mask & 3) != 0 && (unit_types[units[unit2].type].hold != '\0')))) {
                      best_score = 0x18;
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if (((cities[city].id != 0) && ((int)cities[city].owner == civ))
                           && (city7 = tile_landmass((int)cities[city].x,
                                                      (int)cities[city].y),
                              *(char *)&civs[civ].continent_policy[city7] == 1)) {
                          if (own_dist == 0) {
                            city7 = cities_share_ocean(city2,city);
                          }
                          else {
                            city7 = city_adjacent_to_body(city,landmass);
                          }
                          if (city7 != 0) {
                            cand_score = map_distance_diag(x2,y3,(int)cities[city].x
                                                          ,(int)cities[city].y);
                            city7 = tile_unit_owner((int)cities[city].x,
                                                     (int)cities[city].y);
                            if (city7 < 0) {
                              cand_score = cand_score / 2;
                            }
                            else {
                              city7 = civ_ai_goal_get_priority(civ,(int)cities[city].x,
                                                          (int)cities[city].y,1);
                              if (city7 != 0) {
                                cand_score -= cand_score / 3;
                              }
                            }
                            if (cand_score < best_score) {
                              best_score = cand_score;
                              unit_set_goto(unit2,0x41,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if ((units[unit2].orders != 11) && ((tasks_mask & 3) != 0)) {
                      best_score = 999;
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if (((cities[city].id != 0) &&
                            (civ2 = (uptr)cities[city].owner, civ2 != civ)) &&
                           (((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 0x20) != 0 &&
                            (city7 = tile_unit_owner((int)cities[city].x,
                                                      (int)cities[city].y), city7 < 0)))) {
                          tile_landmass((int)cities[city].x,(int)cities[city].y);
                          if (own_dist == 0) {
                            city7 = cities_share_ocean(city2,city);
                          }
                          else {
                            city7 = city_adjacent_to_body(city,landmass);
                          }
                          if (city7 != 0) {
                            cand_score = map_distance_diag(x2,y3,(int)cities[city].x
                                                          ,(int)cities[city].y);
                            for (civ4 = 1; civ4 < 8; civ4++) {
                              if ((((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0)
                                  && ((*(byte *)&civs[civ].treaties[civ4] & 8) != 0
                                     )) && ((*(byte *)(civ4 * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4)
                                            & 0x20) != 0)) {
                                cand_score = cand_score / 2;
                                break;
                              }
                            }
                            if ((cities[city].flags & 0x8000000) != 0) {
                              cand_score = cand_score << 1;
                            }
                            if (cand_score < best_score) {
                              best_score = cand_score;
                              units[unit2].counter = (byte)city & 7;
                              unit_set_goto(unit2,0x49,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if (units[unit2].orders != 11) {
                      ally_civ = 0xffffffff;
                      for (civ2 = 0; (int)civ2 < 8; civ2++) {
                        if (((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) &&
                           (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0 ||
                            ((int)ally_civ < 0)))) {
                          ally_civ = civ2;
                        }
                      }
                      if (((tasks_mask & 1) != 0) || ((tasks_mask & 0x20) == 0)) {
                        best_score = 999;
                        here_landmass = tile_land_landmass(x2,y3);
                        for (city = (int)(char)units[unit2].counter & 7;
                            (int)city < (int)game.num_cities; city += 8) {
                          if ((((((cities[city].id != 0) &&
                                 (civ2 = (uptr)cities[city].owner, civ2 != civ)) &&
                                ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) &&
                               (((*(byte *)&civs[civ].treaties[civ2] & 4) == 0 ||
                                ((*(byte *)&civs[civ].treaties[civ2] & 0x20) != 0)))
                               ) && ((((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f))
                                      == 0 || (game.civ_by_rank[7] == civ)))) &&
                             (city7 = tile_landmass((int)cities[city].x,
                                                     (int)cities[city].y), here_landmass != city7))
                          {
                            if (own_dist == 0) {
                              city7 = ai_city_touches_landmass(city2,city7);
                            }
                            else {
                              city7 = landmass_borders_body(city7,landmass);
                            }
                            if (city7 != 0) {
                              cand_score = map_distance_diag(x2,y3,
                                                            (int)cities[city].x,
                                                            (int)cities[city].y);
                              if ((0 < (int)ally_civ) &&
                                 ((*(byte *)(civ2 * 4 + (iptr)((u8 *)&civs + 33) + ally_civ * 0x594) & 0x20) !=
                                  0)) {
                                cand_score = cand_score / 2;
                              }
                              if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 8) != 0) {
                                cand_score = cand_score / 2;
                              }
                              if (((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 0x20) != 0)
                                 && (city7 = tile_unit_owner((int)cities[city].x,
                                                              (int)cities[city].y), city7 < 0)
                                 ) {
                                cand_score = cand_score / 2;
                              }
                              if ((cities[city].flags & 0x8000000) != 0) {
                                cand_score = cand_score << 1;
                              }
                              if (cand_score < best_score) {
                                best_score = cand_score;
                                unit_set_goto(unit2,0x34,(int)cities[city].x,
                                                   (int)cities[city].y);
                              }
                            }
                          }
                        }
                      }
                    }
                    if (((units[unit2].orders != 11) && ((tasks_mask & 0x80) != 0)) &&
                       (unit_types[units[unit2].type].hold != '\0')) {
                      best_score = -999;
                      here_landmass = tile_land_landmass(x2,y3);
                      city5 = 0xffffffff;
                      unit5 = unit2;
                      for (unit = unit_stack_first(unit2); x = unit5, -1 < unit;
                          unit = unit_next_in_stack(unit)) {
                        if ((unit_types[units[unit].type].role == 7) &&
                           (units[unit].home_city != -1)) {
                          city5 = (uptr)(byte)units[unit].home_city;
                        }
                      }
                      unit = unit5;
                      if (((int)city5 < 0) &&
                         (city5 = city_find_nearest(x2,y3,civ,0xffffffff,-1),
                         (int)city5 < 0)) {
                        city5 = 0;
                      }
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if ((cities[city].id != 0) &&
                           (city7 = tile_landmass((int)cities[city].x,(int)cities[city].y
                                                  ), here_landmass != city7)) {
                          if (own_dist == 0) {
                            if ((int)cities[city].owner == civ) {
                              city7 = cities_share_ocean(city2,city);
                            }
                            else {
                              city7 = ai_city_touches_landmass(city2,city7);
                            }
                          }
                          else if ((int)cities[city].owner == civ) {
                            city7 = city_adjacent_to_body(city,landmass);
                          }
                          else {
                            city7 = landmass_borders_body(city7,landmass);
                          }
                          if (city7 != 0) {
                            cand_score = map_distance_diag((int)cities[city5].x,
                                                          (int)cities[city5].y,
                                                          (int)cities[city].x,
                                                          (int)cities[city].y);
                            if ((int)cities[city].owner == civ) {
                              cand_score = cand_score / 2;
                            }
                            if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + cities[city].owner * 4) &
                                0x20) != 0) {
                              cand_score -= cand_score / 3;
                            }
                            if ((*(byte *)&civs[civ].treaties[cities[city].owner] &
                                8) != 0) {
                              cand_score += cand_score / 3;
                            }
                            if (((((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)
                                  ) != 0) && (game.power_rank[cities[city].owner] == 7)) &&
                               (4 < civs[civ2].num_cities)) {
                              cand_score = cand_score / 2;
                            }
                            cand_score = cities[city].base_trade * cand_score;
                            city7 = map_distance_diag(x2,y3,(int)cities[city].x,
                                                        (int)cities[city].y);
                            cand_score = cand_score / ((city7 >> 3) + 1);
                            if (best_score < cand_score) {
                              best_score = cand_score;
                              unit_set_goto(x,0x54,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if (units[unit].orders != 11) {
                      best_score = 999;
                      here_landmass = tile_land_landmass(x2,y3);
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if (((cities[city].id != 0) &&
                            (civ2 = (uptr)cities[city].owner, civ2 == civ)) &&
                           ((cand_score = map_distance_diag(x2,y3,
                                                           (int)cities[city].x,
                                                           (int)cities[city].y), 7 < cand_score
                            && ((city7 = tile_landmass((int)cities[city].x,
                                                        (int)cities[city].y),
                                here_landmass != city7 &&
                                (*(char *)&civs[civ].continent_policy[city7] != 4)))))) {
                          if (own_dist == 0) {
                            y = cities_share_ocean(city2,city);
                          }
                          else {
                            y = city_adjacent_to_body(city,landmass);
                          }
                          if (y != 0) {
                            if ((tasks_mask &
                                1 << (civs[civ].continent_policy[city7] & 0x1f)) == 0) {
                              cand_score = cand_score << 1;
                            }
                            if (cand_score < best_score) {
                              best_score = cand_score;
                              unit_set_goto(unit,0x35,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if ((units[unit].orders != 11) &&
                       (unit_types[units[unit].type].hold != '\0')) {
                      if (units[unit].ai_task == 'V') {
                        x4 = (uint)units[unit].goto_x;
                        y2 = (uint)units[unit].goto_y;
                      }
                      else {
                        y2 = rand_range(0,map.height - 1);
                        x4 = rand_range(0,map.width - 1);
                        if ((x4 & 1) != 0) {
                          x4--;
                        }
                        if ((y2 & 1) != 0) {
                          x4++;
                        }
                      }
                      city7 = tile_land_landmass(x4,y2);
                      here_landmass = tile_land_landmass(x2,y3);
                      if ((((0 < city7) && (city7 < 0x3f)) &&
                          (0x10 < *(short *)(&landmass_fertile_tiles + city7 * 0x10))) &&
                         ((here_landmass != city7 &&
                          (*(char *)&civs[civ].continent_cities[city7] == '\0')))) {
                        flag = 1;
                        if (own_dist == 0) {
                          city7 = ai_city_touches_landmass(city2,city7);
                          if (city7 == 0) {
                            flag = 0;
                          }
                        }
                        else {
                          city7 = landmass_borders_body(city7,landmass);
                          if (city7 == 0) {
                            flag = 0;
                          }
                        }
                        if (flag != 0) {
                          ai_ship_goto_near_shore(unit,0x56,x4,y2);
                        }
                      }
                    }
                    if (units[unit].orders != 11) {
                      for (dir = 2; (int)dir < 0x18; dir++) {
                        dir2 = rand_range(0,7);
                        x = map_wrap_x((int)(char)(&dir_dx_table)[dir2] * dir +
                                            x2);
                        y2 = (int)(char)(&dir_dy_table)[dir2] * dir + y3;
                        city7 = map_in_bounds(x,y2);
                        if (((city7 != 0) && (1 < (int)y2)) &&
                           (((int)y2 <= map.height - 3 &&
                            ((city7 = tile_is_ocean(x,y2), city7 == 0 &&
                             (city7 = tile_landmass(x,y2),
                             *(char *)&civs[civ].continent_cities[city7] == '\0')))))) {
                          if (own_dist == 0) {
                            city7 = ai_city_touches_landmass(city2,city7);
                          }
                          else {
                            city7 = landmass_borders_body(city7,landmass);
                          }
                          if (city7 != 0) {
                            ai_ship_goto_near_shore(unit,0x36,x,y2);
                          }
                        }
                      }
                    }
                  }
                }
                city3 = city4;
                city7 = unit_max_moves(unit);
                if (((((city7 <= (int)(uint)cosmic.road_move_mult) && (-1 < (int)city3)) &&
                     (((uint)game.human_players & 1 << (cities[city3].owner & 0x1fU)) != 0)) &&
                    (((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + cities[city3].owner * 4) & 0x20) != 0
                     && (unit_types[units[unit].type].domain == '\0')))) &&
                   (unit_types[units[unit].type].attack != '\0')) {
                  city7 = tile_at(x2,y3);
                  tile_byte = *(byte *)(city7 + 1);
                  tile_flags = (uint)tile_byte;
                  unit4 = 0;
                  if (((tile_byte & 0x4c) == 0) || (3 < near_dist)) {
                    if (((tile_byte & 0x5c) != 0) &&
                       (((*(char *)&civs[civ].continent_cities[landmass] == '\0' && (near_dist < 8)) ||
                        (unit_type == 9)))) {
                      unit4 = 1;
                    }
                  }
                  else {
                    unit4 = 1;
                  }
                  if ((unit4 != 0) && (!forced_attack)) {
                    unit_pillage(unit,0);
                    goto LAB_005436c1;
                  }
                }
                if (unit_type == 9) {
                  unit5 = unit;
                  for (unit = 0; unit < game.num_units; unit++) {
                    if (((((units[unit].id != 0) &&
                          (4 < (char)unit_types[units[unit].type].role)) &&
                         ((civ2 = (uptr)units[unit].owner, civ2 != civ &&
                          (((*(byte *)&civs[civ].treaties[civ2] & 6) == 0 &&
                           (city7 = map_distance(x2,y3,(int)units[unit].x,
                                                        (int)units[unit].y), city7 < 4))))))
                        && (((1 << (owner_byte & 0x1f) & (uint)units[unit].visibility) != 0 ||
                            ((int)units[unit].owner == (uint)owner_byte)))) &&
                       (city7 = tile_landmass((int)units[unit].x,(int)units[unit].y),
                       city7 == landmass)) {
                      unit_set_goto(unit5,0x50,(int)units[unit].x,
                                         (int)units[unit].y);
                      has_orders = 1;
                      break;
                    }
                  }
                  unit = unit5;
                  if (has_orders != 0) break;
                }
                if ((((unit_type == 9) && (-1 < (int)city3)) &&
                    (((uint)game.human_players & 1 << (cities[city3].owner & 0x1fU)) != 0)) &&
                   ((*(byte *)&civs[civ].treaties[cities[city3].owner] & 6) == 0)) {
                  cand_score = map_distance_diag(x2,y3,(int)cities[city3].x,
                                                (int)cities[city3].y);
                  city6 = 0xffffffff;
                  for (dir = 0; (int)dir < 8; dir++) {
                    x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
                    y2 = (char)(&dir_dy_table)[dir] + y3;
                    city7 = map_in_bounds(x,y2);
                    if ((city7 != 0) && (city7 = tile_unit_owner(x,y2), city7 < 0)) {
                      city7 = tile_city_owner(x,y2);
                      if (-1 < city7) {
                        city6 = 0xffffffff;
                        break;
                      }
                      city7 = map_distance_diag(x,y2,(int)cities[city3].x,
                                                  (int)cities[city3].y);
                      if ((city7 <= cand_score) &&
                         (terrain = tile_improvements(x,y2), (terrain & 0x5c) != 0)) {
                        city6 = dir;
                      }
                    }
                  }
                  if (-1 < (int)city6) {
                    units[unit].ai_task = 'p';
                    best_dir = city6;
                    city3 = best_dir;
                    goto LAB_005435ca;
                  }
                }
                fort_need = 0;
                if (((settler_type) || (ai_role == 1)) &&
                   (city7 = civ_has_advance(civ,0x12), city7 != 0)) {
                  home_dist = own_dist;
                  if (-1 < (int)city2) {
                    home_dist = map_distance(x2,y3,(int)cities[city2].x,
                                                  (int)cities[city2].y);
                  }
                  if (((own_dist != 0) && (city2 == city4)) &&
                     ((on_fortress == 0 &&
                      ((city7 = tile_airbase_owner(x2,y3), city7 < 0 &&
                       (city7 = tile_is_ocean(x2,y3), city7 == 0)))))) {
                    ocean_count = 0;
                    sea_south = 0;
                    sea_north = 0;
                    sea_east = 0;
                    sea_west = 0;
                    for (dir = 0; (int)dir < 8; dir++) {
                      x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
                      y2 = (char)(&dir_dy_table)[dir] + y3;
                      city7 = map_in_bounds(x,y2);
                      if (city7 != 0) {
                        result = tile_improvements(x,y2);
                        if ((((byte)result & 0x42) == 0x40) ||
                           (city7 = tile_city_owner(x,y2), -1 < city7))
                        goto LAB_0053fc8d;
                        city7 = tile_is_ocean(x,y2);
                        if (city7 != 0) {
                          ocean_count++;
                          if (3 < ocean_count) goto LAB_0053fc8d;
                          if ((char)(&dir_dy_table)[dir] < '\0') {
                            sea_north = 1;
                          }
                          if ('\0' < (char)(&dir_dy_table)[dir]) {
                            sea_south = 1;
                          }
                          if ((char)(&dir_dx_table)[dir] < '\0') {
                            sea_west = 1;
                          }
                          if ('\0' < (char)(&dir_dx_table)[dir]) {
                            sea_east = 1;
                          }
                        }
                        city7 = civ_ai_goal_get_priority(civ,x,y2,1);
                        if (city7 != 0) goto LAB_0053fc8d;
                      }
                    }
                    terrain = tile_improvements(x2,y3);
                    if (((((terrain & 0x10) != 0) && (1 < own_dist)) && (own_dist < 4)) &&
                       (city2 == city4)) {
                      fort_need = 1;
                    }
                    for (dir = 0xfffffffe; (int)dir < 3; dir++) {
                      x = map_wrap_x(dir + x2);
                      city7 = map_in_bounds(x,y3 - 2);
                      if (((city7 != 0) && (sea_north == 0)) &&
                         ((city7 = tile_is_ocean(x,y3 - 2), city7 != 0 ||
                          (result = tile_improvements(x,y3 - 2),
                          ((byte)result & 0x42) == 0x40)))) {
                        sea_north = 2;
                      }
                      city7 = map_in_bounds(x,y3 + 2);
                      if (((city7 != 0) && (sea_south == 0)) &&
                         ((city7 = tile_is_ocean(x,y3 + 2), city7 != 0 ||
                          (result = tile_improvements(x,y3 + 2),
                          ((byte)result & 0x42) == 0x40)))) {
                        sea_south = 2;
                      }
                    }
                    for (dir = 0xfffffffe; (int)dir < 3; dir++) {
                      y2 = dir + y3;
                      x = map_wrap_x(x2 - 2);
                      city7 = map_in_bounds(x,y2);
                      if (((city7 != 0) && (sea_west == 0)) &&
                         ((city7 = tile_is_ocean(x,y2), city7 != 0 ||
                          (result = tile_improvements(x,y2),
                          ((byte)result & 0x42) == 0x40)))) {
                        sea_west = 2;
                      }
                      x = map_wrap_x(x2 + 2);
                      city7 = map_in_bounds(x,y2);
                      if (((city7 != 0) && (sea_east == 0)) &&
                         ((city7 = tile_is_ocean(x,y2), city7 != 0 ||
                          (result = tile_improvements(x,y2),
                          ((byte)result & 0x42) == 0x40)))) {
                        sea_east = 2;
                      }
                    }
                    if ((1 < sea_north + sea_south) && ((sea_west == 0 || (sea_east == 0)))) {
                      fort_need = 2;
                    }
                    if ((1 < sea_east + sea_west) && ((sea_north == 0 || (sea_south == 0)))) {
                      fort_need = 2;
                    }
                    if (fort_need != 0) {
                      if (settler_type) {
                        civ_add_standing_goal(civ,x2,y3,1,2);
                      }
                      else {
                        civ_add_standing_goal(civ,x2,y3,0x15,
                                           (uint)(home_dist < 4) + fort_need);
                      }
                    }
                  }
                }
LAB_0053fc8d:
                if (((ai_role == 5) && (units[unit].orders == 11)) &&
                   (city7 = tile_city_owner((int)units[unit].goto_x,
                                             (int)units[unit].goto_y), -1 < city7)) {
                  goto_city = 1;
                }
                if (((settler_type) && (!forced_attack)) &&
                   ((goto_city == 0 &&
                    ((city7 = tile_is_ocean(x2,y3), city7 == 0 &&
                     (city7 = tile_city_owner(x2,y3), city7 < 0)))))) {
                  city7 = unit_stack_sum(unit,2);
                  flag = (uint)(1 < city7);
                  if (flag == 0) {
                    for (dir = 0; (int)dir < 8; dir++) {
                      x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
                      y2 = (char)(&dir_dy_table)[dir] + y3;
                      city7 = map_in_bounds(x,y2);
                      if ((city7 != 0) && (city7 = tile_unit_owner(x,y2), -1 < city7))
                      {
                        flag = 1;
                        break;
                      }
                    }
                  }
                  if (flag == 0) {
                    civ_add_ai_goal(civ,x2,y3,1,2);
                  }
                  civ_clear_standing_goals_near(civ,0x15,x2,y3,0);
                  here_imps = tile_improvements(x2,y3);
                  if ((here_imps & 0x80) != 0) {
                    units[unit].orders = '\t';
                    units[unit].ai_task = 'p';
                    goto LAB_005436c1;
                  }
                  if (((((1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0) ||
                       (units[unit].orders != 11)) ||
                      (city7 = map_in_bounds((int)units[unit].goto_x,
                                              (int)units[unit].goto_y), city7 == 0)) ||
                     (goto_imps = tile_improvements((int)units[unit].goto_x,
                                                 (int)units[unit].goto_y), (goto_imps & 0x80) == 0
                     )) {
                    if (((fort_need == 2) && ((1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0))
                       && ((city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 == 0 ||
                           (city7 = unit_stack_sum(unit,2), 1 < city7)))) {
                      units[unit].orders = 4;
                      units[unit].ai_task = 'X';
                      goto LAB_005436c1;
                    }
                    work_flags = 0;
                    if ((is_settler) && ((units[unit].flags & 0x80) != 0)) {
                      work_flags = 1;
                    }
                    else {
                      city7 = civ_ai_goal_get_priority(civ,x2,y3,0x15);
                      if (city7 != 0) {
                        work_flags = 1;
                      }
                    }
                    if ((((2 < own_dist) || ((cities[city2].flags & 0x40) == 0)) || (!is_settler)) ||
                       (units[unit].orders != 11)) {
                      if ((((own_dist != 0) && (own_dist < 3)) &&
                          ((((int)(char)terrain_types[terrain2].irrigate_turns / 5) * 3 - 3 <=
                            (int)cities[city2].size ||
                           (city7 = tile_resource(x2,y3), city7 != 0)))) &&
                         ((city7 = ai_tile_improve_choice(civ,x2,y3), city7 != 0 ||
                          (policy == 4)))) {
                        work_flags = work_flags | 2;
                      }
                      if (work_flags != 0) {
                        if ((work_flags & 2) != 0) {
                          city7 = ai_tile_improve_choice(civ,x2,y3);
                          if (city7 == 1) {
                            units[unit].orders = 6;
                            units[unit].ai_task = 'I';
                            goto LAB_005436c1;
                          }
                          if (city7 == 2) {
                            units[unit].orders = 7;
                            units[unit].ai_task = 'M';
                            goto LAB_005436c1;
                          }
                        }
                        city7 = tile_at(x2,y3);
                        tile_byte = *(byte *)(city7 + 1);
                        tile_flags = (uint)tile_byte;
                        if (((tile_byte & 0x10) == 0) || ((tile_byte & 0x20) != 0)) {
                          if (((tile_byte & 0x10) == 0) &&
                             ((tile = (byte *)tile_at(x2,y3), (*tile & 0x80) == 0
                              || (city7 = civ_has_advance(civ,7), city7 != 0)))) {
                            work_flags = work_flags & 1;
                            if (((tile_flags & 0xc) != 0) &&
                               ((tile = (byte *)tile_at(x2,y3),
                                (*tile & 0x80) != 0 || ((int)terrain2 < 3)))) {
                              work_flags = work_flags | 2;
                            }
                            if (work_flags != 0) {
                              units[unit].orders = 5;
                              units[unit].ai_task = 'r';
                              goto LAB_005436c1;
                            }
                          }
                        }
                        else {
                          city7 = civ_has_advance(civ,0x43);
                          if (city7 != 0) {
                            work_flags = work_flags & 1;
                            city7 = tile_resource(x2,y3);
                            if (city7 != 0) {
                              work_flags = work_flags | 2;
                            }
                            if ((tile_flags & 8) != 0) {
                              work_flags = work_flags | 2;
                            }
                            if (1 < (char)terrain_types[terrain2].shields) {
                              work_flags = work_flags | 2;
                            }
                            if (work_flags != 0) {
                              units[unit].orders = 5;
                              units[unit].ai_task = 'R';
                              goto LAB_005436c1;
                            }
                          }
                        }
                      }
                      if (((fort_need != 0) &&
                          ((1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0)) &&
                         ((city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 == 0 ||
                          (city7 = unit_stack_sum(unit,2), 1 < city7)))) {
                        units[unit].orders = 4;
                        units[unit].ai_task = 'X';
                        goto LAB_005436c1;
                      }
                      city3 = city2;
                      if (((units[unit].orders == 11) &&
                          ((units[unit].flags & 0x200) == 0)) &&
                         (city7 = (leaders[civs[civ].tribe].expand + 1) *
                                   (int)*(short *)(&landmass_fertile_tiles + landmass * 0x10),
                         terrain = (uint)civs[civ].continent_cities[landmass],
                         city7 + terrain * -0x10 != 0 && (int)(terrain * 0x10) <= city7))
                      goto LAB_005436c1;
                      if (own_dist < 2) {
                        for (dir = 0; (int)dir < 8; dir++) {
                          dir2 = (int)game.turn + dir & 7;
                          x = map_wrap_x((char)(&dir_dx_table)[dir2] + x2);
                          y2 = (char)(&dir_dy_table)[dir2] + y3;
                          city7 = map_in_bounds(x,y2);
                          if (((city7 != 0) &&
                              (city7 = tile_city_owner(x,y2), city7 < 0)) &&
                             (((unit3 = tile_first_unit(x,y2), unit3 < 0 ||
                               (((int)units[unit3].owner == civ &&
                                (city7 = unit_stack_count_role(unit3,5), city7 == 0)))) &&
                              (city7 = ai_tile_improve_choice(civ,x,y2), city7 != 0)))) {
                            tile_byte = tile_terrain(x,y2);
                            unit4 = (uptr)tile_byte;
                            if (((((int)(char)terrain_types[unit4].irrigate_turns / 5) * 3 - 3
                                  <= (int)cities[city3].size) ||
                                (city7 = tile_resource(x,y2), city7 != 0)) &&
                               (city7 = map_distance_diag(x2,y3,x,y2),
                               city7 < 3)) {
                              units[unit].ai_task = 's';
                              best_dir = dir2;
                              city3 = best_dir;
                              goto LAB_005435ca;
                            }
                          }
                        }
                      }
                      terrain = tile_improvements(x2,y3);
                      if ((((terrain & 0x10) == 0) &&
                          ((tile = (byte *)tile_at(x2,y3), (*tile & 0x80) == 0 ||
                           (city7 = civ_has_advance(civ,7), city7 != 0)))) &&
                         ((own_dist < 3 && ((int)terrain2 < 3)))) {
                        units[unit].ai_task = 'r';
                        units[unit].orders = 5;
                        goto LAB_005436c1;
                      }
                    }
                  }
                }
                if (((ai_role == 0x15) && (units[unit].orders != 11)) &&
                   ((!forced_attack &&
                    (((goto_city == 0 && (own_dist != 0)) &&
                     (city7 = tile_is_ocean(x2,y3), city7 == 0)))))) {
                  if (units[unit].home_city == -1) {
                    city = city2;
                  }
                  else {
                    city = (uptr)(byte)units[unit].home_city;
                  }
                  if ((-1 < (int)city) &&
                     (city7 = tile_landmass((int)cities[city].x,(int)cities[city].y),
                     city7 != landmass)) {
                    city = city2;
                  }
                  if ((-1 < (int)city) &&
                     (city7 = map_distance_diag(x2,y3,(int)cities[city].x,
                                                  (int)cities[city].y), 4 < city7)) {
                    unit_set_goto(unit,99,(int)cities[city].x,
                                       (int)cities[city].y);
                    goto LAB_005436c1;
                  }
                  terrain = tile_improvements(x2,y3);
                  if (((terrain & 0x10) == 0) &&
                     ((tile = (byte *)tile_at(x2,y3), (*tile & 0x80) == 0 ||
                      (city7 = civ_has_advance(civ,7), city7 != 0)))) {
                    units[unit].ai_task = 'r';
                    units[unit].orders = 5;
                    goto LAB_005436c1;
                  }
                  if ((-1 < (int)city2) && (in_enemy_zoc != 0)) {
                    unit_set_goto(unit,99,(int)cities[city2].x,(int)cities[city2].y)
                    ;
                    goto LAB_005436c1;
                  }
                  if (own_dist < 3) {
                    city7 = tile_at(x2,y3);
                    tile_byte = *(byte *)(city7 + 1);
                    tile_flags = (uint)tile_byte;
                    if ((tile_byte & 0xe) == 0) {
                      if ((terrain_types[terrain2].mine_ai_govt != '\0') &&
                         ((char)terrain_types[terrain2].mine_ai_govt <
                          (char)terrain_types[terrain2].irrigate_ai_govt)) {
                        units[unit].orders = 7;
                        goto LAB_005436c1;
                      }
                      if (terrain_types[terrain2].irrigate_ai_govt != '\0') {
                        units[unit].orders = 6;
                        goto LAB_005436c1;
                      }
                    }
                    if ((tile_byte & 0x80) != 0) {
                      units[unit].orders = '\t';
                      goto LAB_005436c1;
                    }
                    terrain = tile_improvements(x2,y3);
                    if (((terrain & 0x20) == 0) &&
                       (city7 = civ_has_advance(civ,0x43), city7 != 0)) {
                      units[unit].ai_task = 'r';
                      units[unit].orders = 5;
                      goto LAB_005436c1;
                    }
                    city3 = city2;
                    for (dir = 0; (int)dir < 0x14; dir++) {
                      x = map_wrap_x((int)(char)(&city_tile_dx_table)[dir] +
                                          (int)cities[city3].x);
                      y2 = (int)cities[city3].y + (int)(char)(&city_tile_dy_table)[dir];
                      city7 = map_in_bounds(x,y2);
                      if (city7 != 0) {
                        tile_byte = tile_terrain(x,y2);
                        city7 = tile_at(x,y2);
                        tile_flags = (uint)*(byte *)(city7 + 1);
                        if ((*(byte *)(city7 + 1) & 0xe) == 0) {
                          if ((terrain_types[tile_byte].mine_ai_govt != '\0') &&
                             ((char)terrain_types[tile_byte].mine_ai_govt <
                              (char)terrain_types[tile_byte].irrigate_ai_govt)) {
                            unit_set_goto(unit,0x6d,x,y2);
                            goto LAB_005436c1;
                          }
                          if (terrain_types[tile_byte].irrigate_ai_govt != '\0') {
                            unit_set_goto(unit,0x69,x,y2);
                            goto LAB_005436c1;
                          }
                        }
                        tile = (byte *)tile_at(x,y2);
                        if ((((*tile & 0x80) == 0) ||
                            (city7 = civ_has_advance(civ,7), city7 != 0)) &&
                           ((terrain = tile_improvements(x,y2), (terrain & 0x10) == 0 ||
                            ((terrain = tile_improvements(x,y2), (terrain & 0x20) == 0 &&
                             (city7 = civ_has_advance(civ,0x43), city7 != 0)))))) {
                          unit_set_goto(unit,0x72,x,y2);
                          goto LAB_005436c1;
                        }
                      }
                    }
                  }
                  else {
                    terrain = tile_improvements(x2,y3);
                    if (((terrain & 0x20) == 0) &&
                       (city7 = civ_has_advance(civ,0x43), city7 != 0)) {
                      units[unit].ai_task = 'r';
                      units[unit].orders = 5;
                      goto LAB_005436c1;
                    }
                  }
                }
                if ((units[unit].orders != 11) ||
                   (((ai_role == 2 &&
                     (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 != 0)) || (forced_attack)
                    ))) goto LAB_00541001;
                flag = 1;
                city7 = map_distance(x2,y3,(int)units[unit].goto_x,
                                            (int)units[unit].goto_y);
                if (1 < city7) {
                  if (((int)ai_role < 5) &&
                     (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 != 0)) {
                    has_orders = 1;
                    flag = 0;
                  }
                  goto LAB_00540fea;
                }
                civ2 = tile_city_or_unit_owner
                                     ((int)units[unit].goto_x,(int)units[unit].goto_y);
                if (((int)civ2 < 0) || (civ2 == civ)) goto LAB_00540fea;
                if ((ai_role != 4) ||
                   ((city7 = unit_stack_sum(unit,2), city7 < 2 || (retried != 0))))
                goto LAB_00540f1e;
                units[unit].orders = -1;
                retried = 1;
              } while( true );
            }
          }
          else {
            unit4 = (uptr)(char)unit_types[units[unit].type].defense;
            city7 = city_has_improvement(city2,8);
            if (city7 == 0) {
              if ((units[unit].flags & 0x100) != 0) {
                unit4 = (int)(unit4 * 3) / 2;
              }
            }
            else {
              unit4 = unit4 << 1;
            }
            if ((int)(char)unit_types[units[unit].type].attack < (int)unit4) {
              units[unit].ai_task = 'F';
              units[unit].home_city = (i8)city2;
              stay_home = false;
              best_dir = 8;
              city3 = best_dir;
              goto LAB_005435ca;
            }
            hold_pos = 1;
          }
        }
        else {
          if (ai_role != 1) {
            if (ai_role == 0) {
              if (in_enemy_zoc != 0) {
                hold_pos = 1;
              }
              city7 = unit_stack_sum(unit,2);
              if (((city7 == 1) && (-1 < unit_types[units[unit].type].obsolete_by)) &&
                 (game.advance_known_by[unit_types[units[unit].type].obsolete_by] != '\0')) {
                hold_pos = 1;
              }
              if (hold_pos != 0) goto LAB_005414d7;
            }
            goto LAB_0053b8f0;
          }
          city7 = unit_stack_count_role(unit,1);
          if ((1 < city7) && (units[unit].orders == 11)) goto LAB_0053b8f0;
          units[unit].ai_task = 'F';
          hold_pos = 1;
        }
LAB_005414d7:
        best_score = -999;
        max_score = -999;
        best_dir = 8;
        explore = 0;
        will_attack = 0;
        if (((ai_role == 4) && (own_dist != 0)) &&
           ((city7 = unit_stack_sum(unit,2), 1 < city7 &&
            (units[unit].orders == 11)))) {
          has_orders = 1;
        }
        city7 = tile_zoc_unit_adjacent(x2,y3,civ);
        if (city7 == 0) {
          if (has_orders == 0) {
            explore = 1;
          }
          else {
            explore = 0;
          }
        }
        else {
          units[unit].last_dir = 0xff;
        }
        if (((game.game_flags & 0x80) != 0) && ((scenario_flags & 8) != 0)) {
          explore = 0;
        }
        if (ai_role == 1) {
          if (((char)unit_types[unit_type].defense < (char)unit_types[unit_type].attack) &&
             ((civs[civ].continent_flags[landmass] & 0x10) == 0)) {
            ai_role = 0;
          }
          if (((char)unit_types[unit_type].defense <= (char)unit_types[unit_type].attack) && (policy == 0)
             ) {
            ai_role = 0;
          }
        }
        for (dir = 0; (int)dir < 8; dir++) {
          x = map_wrap_x((char)(&dir_dx_table)[dir] + x2);
          y2 = (char)(&dir_dy_table)[dir] + y3;
          city7 = map_in_bounds(x,y2);
          if (city7 != 0) {
            civ2 = tile_owner(x,y2);
            owner_byte = tile_terrain(x,y2);
            terrain = (uint)owner_byte;
            is_ocean = (uint)(terrain == 10);
            if ((is_ocean == 0) || (unit_domain != 0)) {
              unit3 = tile_first_unit(x,y2);
              while (((-1 < unit3 && (-1 < units[unit3].next_in_stack)) &&
                     (4 < (char)unit_types[units[unit3].type].role))) {
                unit3 = unit_next_in_stack(unit3);
              }
              if (((((((in_enemy_zoc == 0) || (unit_domain != 0)) ||
                     ((-1 < unit3 ||
                      ((city7 = tile_in_enemy_zoc(x,y2,civ), city7 == 0 ||
                       ((type_flags & 2) != 0)))))) || (is_ocean != 0)) &&
                   ((((is_ocean == 0 || (unit_domain != 0)) || (unit3 < 0)) || (civ2 == civ))
                   )) && (((unit_domain != 2 || (is_ocean != 0)) ||
                          (((-1 < unit3 && ((civ2 != civ && (terrain2 == 10)))) &&
                           ((type_flags & 8) == 0)))))) &&
                 ((((unit3 < 0 || (civ2 != civ)) ||
                   (city7 = unit_stack_sum(unit3,2), city7 < 2)) ||
                  ((city7 = tile_city_owner(x,y2), -1 < city7 ||
                   (result = tile_improvements(x,y2), ((byte)result & 0x42) == 0x40))))))
              {
                score = 0;
                if (settler_type) {
                  if ((terrain2 == 10) &&
                     (city7 = tile_zoc_unit_adjacent(x,y2,civ), city7 != 0))
                  goto LAB_0054168e;
                  score = rand_range(0,4);
                }
                else if ((units[unit].visibility == '\0') && (terrain2 != 10)) {
                  if (ai_role == 0) {
                    score = rand_range(0,2);
                    score += (char)terrain_types[terrain].move_cost * -2;
                  }
                  else {
                    score = rand_range(0,2);
                    score -= (char)terrain_types[terrain].defense;
                  }
                }
                else {
                  score = rand_range(0,4);
                  if ((unit3 < 0) || (civ2 != civ)) {
                    if ((int)ai_role < 6) {
                      score += (char)terrain_types[terrain].defense * 4;
                    }
                    else {
                      score = score +
                                 (6 - ((char)terrain_types[terrain].move_cost - 1) *
                                      (uint)cosmic.road_move_mult);
                      if ((near_dist < 4) && (city2 != city4)) {
                        cand_score = map_distance(x,y2,(int)cities[city4].x,
                                                      (int)cities[city4].y);
                        if (cand_score == 1) {
                          if ((int)(uint)cosmic.road_move_mult <
                              (int)(char)terrain_types[terrain].move_cost) {
                            score -= 4;
                          }
                          else {
                            score += 8;
                          }
                        }
                        else if (((cand_score == 2) &&
                                 ((int)(char)terrain_types[terrain].move_cost <=
                                  (int)(uint)cosmic.road_move_mult)) &&
                                (road_imps = tile_improvements(x,y2), (road_imps & 0x10) != 0))
                        {
                          score += 4;
                        }
                      }
                    }
                  }
                  else {
                    result = tile_improvements(x,y2);
                    if ((((byte)result & 0x43) == 1) &&
                       (city7 = tile_adjacent_nonallied_unit(x,y2,civ), city7 != 0)) {
                      switch(ai_role) {
                      case 0:
                        unit4 = unit_stack_count_role(unit3,0);
                        if (((int)unit4 < 1) &&
                           (city7 = unit_stack_count_role(unit3,1), city7 != 0)) {
                          score += 8;
                        }
                        else {
                          score += unit4 * -8;
                        }
                        break;
                      case 1:
                        unit4 = unit_stack_count_role(unit3,1);
                        if ((int)unit4 < 1) {
                          score += 8;
                        }
                        else {
                          score += unit4 * -4;
                        }
                        break;
                      case 2:
                        city7 = unit_stack_count_role(unit3,4);
                        if (city7 != 0) {
                          score += 8;
                        }
                        city7 = unit_stack_count_role(unit3,2);
                        score += city7 * -4;
                        break;
                      case 4:
                        city7 = unit_stack_count_role(unit3,2);
                        if (city7 != 0) {
                          score += 8;
                        }
                        city7 = unit_stack_count_role(unit3,4);
                        score += city7 * -8;
                        break;
                      case 5:
                      case 0x15:
                        score -= 4;
                        break;
                      case 6:
                        city7 = unit_stack_count_role(unit3,0);
                        y = unit_stack_count_role(unit3,1);
                        if (city7 + y != 0) {
                          score += 8;
                        }
                      }
                    }
                    else {
                      switch(ai_role) {
                      case 0:
                        city7 = unit_stack_sum(unit3,0);
                        y = unit_stack_sum(unit3,2);
                        score += (city7 * 4) / (y + 1);
                        break;
                      case 1:
                        city7 = unit_stack_sum(unit3,3);
                        y = unit_stack_sum(unit3,0);
                        score += (city7 * 2) / (y + 1);
                        break;
                      case 5:
                        stat = terrain_types[terrain].defense;
                        city7 = unit_stack_sum(unit3,0);
                        score += ((char)stat + city7) * 2;
                        break;
                      case 6:
                        city7 = unit_stack_count_role(unit3,0);
                        y = unit_stack_count_role(unit3,1);
                        if (city7 + y != 0) {
                          score += 8;
                        }
                      }
                    }
                  }
                }
                if (unit_domain == 1) {
                  score = rand_range(0,2);
                }
                if (-1 < (char)units[unit].last_dir) {
                  if ((int)(char)units[unit].last_dir == dir ||
                      (int)((int)(char)units[unit].last_dir - dir) < 0) {
                    unit4 = ~((int)(char)units[unit].last_dir - dir) + 1;
                  }
                  else {
                    unit4 = (int)(char)units[unit].last_dir - dir;
                  }
                  if (4 < (int)unit4) {
                    unit4 = 8 - unit4;
                  }
                  score += unit4 * unit4 * -2;
                }
                is_attack = 0;
                flag = 0;
                if (((unit3 < 0) &&
                    (city7 = tile_is_ocean(x,y2), city3 = city4, city7 == 0)) &&
                   ((char)unit_types[units[unit].type].role < 5)) {
                  if ((((near_dist < 4) && ((int)cities[city4].owner != civ)) &&
                      (((*(byte *)&civs[civ].treaties[cities[city4].owner] & 6) != 0
                       && ((*(byte *)&civs[civ].treaties[cities[city4].owner] & 8) ==
                           0)))) &&
                     (((*(byte *)&civs[civ].treaties[cities[city4].owner] & 4) != 0
                      || (city7 = civ_get_attitude(civ,(int)cities[city4].owner),
                         city7 < 0x32)))) {
                    cand_score = map_distance_diag((int)cities[city3].x,(int)cities[city3].y,x
                                                  ,y2);
                    if ((near_dist < cand_score) && (near_dist < 3)) {
                      score += 5;
                      flag = 1;
                    }
                    if (cand_score < near_dist) goto LAB_0054168e;
                    if (cand_score == near_dist) {
                      score -= 5;
                    }
                  }
                  civ3 = tile_radius_civ(x,y2);
                  if ((((0 < (int)civ3) && (civ3 != civ)) &&
                      ((*(byte *)&civs[civ].treaties[civ3] & 6) != 0)) &&
                     ((*(byte *)&civs[civ].treaties[civ3] & 8) == 0)) {
                    if ((((*(byte *)&civs[civ].treaties[civ3] & 4) != 0) &&
                        ((int)((uint)civs[civ3].reputation -
                              (int)*(char *)((int)civs + civ * 0x595 + 0x48)) < 7)) &&
                       (flag == 0)) goto LAB_0054168e;
                    if ((((*(byte *)&civs[civ].treaties[civ3] & 4) != 0) &&
                        ((int)((uint)civs[civ3].reputation -
                              (int)*(char *)((int)civs + civ * 0x595 + 0x48)) < 7)) ||
                       (city7 = civ_get_attitude(civ,civ3), city7 < 0x32)) {
                      score -= 5;
                      tile_flags = tile_improvements(x,y2);
                      if ((tile_flags & 0x1c) != 0) {
                        score -= 3;
                      }
                    }
                  }
                }
                if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
                  score -= 6;
                }
                if (unit3 < 0) {
                  city7 = tile_city_owner(x,y2);
                  if ((-1 < city7) && (civ2 != civ)) {
                    if (((*(byte *)&civs[civ].treaties[civ2] & 0xe) != 0) &&
                       (((civs[civ2].reputation < 7 ||
                         ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0)) ||
                        ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0))))
                    goto LAB_0054168e;
                    score = 999;
                    has_orders = 0;
                    hold_pos = 0;
                  }
                  city7 = tile_has_hut(x,y2);
                  if (city7 != 0) {
                    score += 0x14;
                  }
                }
                else {
                  if (civ2 != civ) {
                    is_attack = 1;
                    attack_bonus = 0;
                    if (((settler_type) || (unit_types[units[unit].type].role == 7)) ||
                       ((((unit_domain == 2 && (unit_types[units[unit].type].hold != '\0')) &&
                         (((city7 = tile_is_ocean(x,y2), city7 == 0 &&
                           ((char)unit_types[units[unit].type].attack < 3)) ||
                          ((city7 = unit_stack_sum(unit,2), 1 < city7 &&
                           (((char)unit_types[units[unit].type].attack <=
                             (char)unit_types[units[unit3].type].defense ||
                            ((char)unit_types[units[unit3].type].attack <=
                             (char)unit_types[units[unit].type].defense)))))))) ||
                        ((city7 = tile_is_ocean(x2,y3), city7 != 0 &&
                         ((unit_domain == 0 && ((unit_types[units[unit].type].flags & 4) == 0))))
                        )))) goto LAB_0054168e;
                    if ((*(byte *)&civs[civ].treaties[civ2] & 6) == 0) {
                      if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
LAB_005429fe:
                        unit3 = unit_stack_best_defender(unit3,unit);
                        if (((((unit_types[units[unit3].type].domain != 1) ||
                              (unit_types[units[unit3].type].range == '\0')) ||
                             ((unit_types[units[unit].type].flags & 0x10) != 0)) ||
                            (((city7 = tile_city_owner(x,y2), -1 < city7 ||
                              (city7 = tile_airbase_owner(x,y2), -1 < city7)) ||
                             (city7 = unit_stack_sum(unit3,9), city7 != 0)))) &&
                           (((unit_types[units[unit3].type].role != 7 ||
                             (city2 != city4)) ||
                            (((civs[civ].government < civs[civ2].government ||
                              ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0)) &&
                             (city7 = rand_range(0,(uint)civs[civ2].government -
                                                            (uint)civs[civ].government),
                             city7 != 0)))))) {
                          attack_value = unit_resolve_attack(unit,dir,0);
                          city7 = unit_stack_sum(unit3,0);
                          attack_value = ((city7 + 1) * attack_value) /
                                     (int)(char)unit_types[units[unit].type].cost;
                          city7 = tile_city_owner(x,y2);
                          if (-1 < city7) {
                            attack_value = attack_value * 3;
                          }
                          if ((ai_role == 2) && (unit_types[units[unit3].type].role == 4))
                          {
                            attack_value = attack_value << 1;
                          }
                          if (is_guard == 0) {
                            if (ai_role == 0) {
                              if (policy == 0) {
                                attack_value = attack_value << 1;
                              }
                              stat = unit_types[units[unit].type].attack;
                              city7 = unit_stack_sum(unit,3);
                              if ((char)stat * 2 < city7) {
                                attack_value = attack_value << 1;
                                attack_bonus = 1;
                              }
                              city7 = unit_stack_count_role(unit3,0);
                              if (city7 != 0) {
                                attack_value = attack_value << 1;
                                attack_bonus = 1;
                              }
                              city7 = civ_ai_goal_get_priority(civ,x2,y3,0);
                              if (city7 != 0) {
                                attack_value = attack_value << 1;
                              }
                            }
                            if ((game.rules & 0x10) != 0) {
                              city7 = unit_max_hp(unit3);
                              y = unit_hp_remaining(unit3);
                              if (y <= city7 / 3) {
                                attack_bonus = 1;
                                attack_value = attack_value << 1;
                              }
                            }
                            if ((unit_types[units[unit3].type].flags & 8) != 0) {
                              attack_value = attack_value * 3;
                            }
                          }
                          else {
                            attack_value = attack_value / 2;
                            if ((char)unit_types[units[unit3].type].attack <=
                                (char)unit_types[units[unit].type].defense) {
                              attack_value = 0;
                            }
                          }
                          if ((unit_type == 9) &&
                             (4 < (char)unit_types[units[unit3].type].role)) {
                            attack_bonus = 2;
                          }
                          unit4 = (uptr)(char)unit_types[units[unit3].type].role;
                          if ((civ2 == 0) && (unit4 == 7)) {
                            if ((game.human_players & 1) == 0) {
                              attack_value = attack_value / 2;
                            }
                          }
                          else if ((civ2 == 0) && (4 < (int)unit4)) {
                            attack_value += 0xc;
                          }
                          else if (unit4 == 6) {
                            attack_value = attack_value << 1;
                          }
                          if ((int)((-(uint)(civ2 == 0) & 6) + 6) <= attack_value) {
                            score += attack_value * 4;
                            goto LAB_0054314b;
                          }
                          score = -999;
                          if ((((((policy == 0) && (ai_role == 0)) && (unit_domain == 0)) &&
                               (((units[unit3].flags & 0x2000) != 0 ||
                                (units[unit3].orders == 2)))) &&
                              ((3 < (char)terrain_types[terrain].defense ||
                               (result = tile_improvements(x,y2),
                               ((byte)result & 0x42) == 0x40)))) &&
                             (((city7 = unit_stack_sum(unit3,2), city7 < 2 &&
                               (city7 = tile_city_owner(x,y2), city7 < 0)) &&
                              (city7 = rand_range(0,3), city7 == 0)))) {
                            unit_bribe(unit3,civ);
                          }
                        }
                        goto LAB_0054168e;
                      }
                      if (ai_role != 6) {
                        owner_byte = civs[civ2].reputation;
                        city7 = civ_get_attitude(civ,civ2);
                        y = rand_range(0,0x13);
                        if (0x32 < (int)((uint)owner_byte * 5 + city7 + y - 10))
                        goto LAB_005429fe;
                      }
                    }
                    if (((((*(byte *)&civs[civ].treaties[civ2] & 6) == 0) ||
                         (unit_types[units[unit3].type].role != 6)) ||
                        (city7 = unit_stack_sum(unit3,2), city7 != 1)) ||
                       ((unit_types[units[unit].type].attack == '\0' ||
                        (city7 = city_find_nearest(x,y2,-1,0xffffffff,-1),
                        (int)cities[city7].owner != civ)))) {
                      if (ai_role == 6) {
                        if ((policy == 0) ||
                           ((policy == 5 ||
                            ((*(byte *)&civs[civ].treaties[civ2] & 6) == 0)))) {
LAB_0054272e:
                          if (((ai_role == 6) || (city2 == city4)) && (2 < game.difficulty))
                          {
LAB_00542801:
                            if (unit_domain == 0) {
                              unit4 = 0;
                              if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
                                for (civ4 = 1; civ4 < 8; civ4++) {
                                  if (((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) !=
                                       0) && (city7 = diplo_is_hostile(civ2,civ4),
                                             city7 == 0)) {
                                    unit4 = 1;
                                  }
                                }
                              }
                              if (unit4 == 0) {
                                unit4 = 1;
                                for (civ4 = 1; civ4 < 8; civ4++) {
                                  if (((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) !=
                                       0) && (*(char *)&civs[civ4].continent_cities[landmass] !=
                                              '\0')) {
                                    unit4 = 0;
                                    break;
                                  }
                                }
                                if ((((unit4 != 0) &&
                                     (city7 = unit_stack_sum(unit3,2), city7 < 2)) &&
                                    (city7 = tile_city_owner(x,y2), city7 < 0)) &&
                                   ((city7 = rand_range(0,7), city7 == 0 ||
                                    ((-1 < (int)city4 &&
                                     (((uint)game.human_players &
                                      1 << (cities[city4].owner & 0x1fU)) != 0)))))) {
                                  unit_bribe(unit3,civ);
                                }
                              }
                            }
                          }
                          else if (units[unit3].orders == 2) {
                            unit4 = 0;
                            for (civ4 = 1; civ4 < 8; civ4++) {
                              if (((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0)
                                 && (city7 = diplo_is_hostile(civ,civ4), city7 != 0)) {
                                unit4 = 1;
                              }
                            }
                            if (unit4 != 0) goto LAB_00542801;
                          }
                        }
                      }
                      else if ((policy == 0) && (ai_role == 0)) goto LAB_0054272e;
                    }
                    else {
                      score = 0x3c;
                      if (best_score < 0x3c) {
                        max_score = 0x3c;
                        best_score = 0x3c;
                        best_dir = dir;
                        will_attack = 1;
                        attack_cost = 2;
                      }
                    }
                    goto LAB_0054168e;
                  }
                  score -= (char)unit_types[units[unit].type].defense;
                }
LAB_0054314b:
                if (((own_dist != 0) && (unit_domain == 2)) && ((unit3 < 0 || (civ2 == civ)))
                   ) {
                  city7 = tile_landmass(x,y2);
                  y = city_adjacent_sea_info(city2,0,0);
                  if (city7 == y) {
                    score += 10;
                  }
                }
                if ((((unit_domain != 1) || (city7 = tile_airbase_owner(x,y2), city7 < 0)
                     ) || (civ2 == civ)) || (-1 < unit3)) {
                  if (explore != 0) {
                    x5 = map_wrap_x((char)(&dir_dx_table)[dir] * 4 + x2);
                    city7 = (char)(&dir_dy_table)[dir] * 4 + y3;
                    y = map_in_bounds(x5,city7);
                    if ((y != 0) &&
                       (y = tile_visible_to(x5,city7,civ), y == 0)) {
                      y = tile_is_ocean(x5,city7);
                      if (y == 0) {
                        score += 8;
                      }
                      else {
                        score += 2;
                      }
                    }
                    for (dir2 = 0; (int)dir2 < 8; dir2++) {
                      x3 = map_wrap_x((char)(&dir_dx_table)[dir2] + x5);
                      y = (char)(&dir_dy_table)[dir2] + city7;
                      check = map_in_bounds(x3,y);
                      if (check != 0) {
                        check = tile_visible_to(x3,y,civ);
                        if ((check == 0) &&
                           ((check = tile_is_ocean(x3,y), check == 0 ||
                            (unit_domain == 2)))) {
                          score += 2;
                        }
                        check = tile_unit_owner(x3,y);
                        if (-1 < check) {
                          score -= 2;
                        }
                        if (settler_type) {
                          owner_byte = tile_terrain(x3,y);
                          score += (char)terrain_types[owner_byte].food;
                          if ((game.multiplayer != '\0') && (mp_double_production != 0)) {
                            owner_byte = tile_terrain(x3,y);
                            score += (char)terrain_types[owner_byte].food;
                          }
                        }
                      }
                    }
                  }
                  if ((y2 == 0) || ((int)map.height - 1U == y2)) {
                    score = score / 3;
                  }
                  city7 = score;
                  if (((is_attack != 0) &&
                      (y = unit_moves_left(unit),
                      y < (int)(uint)cosmic.road_move_mult)) &&
                     (y = tile_city_owner(x,y2), y < 0)) {
                    y = unit_stack_sum(unit,0);
                    arg_hi = 99;
                    result = 1;
                    x = unit_stack_sum(unit,3);
                    check = int_clamp(x,result,arg_hi);
                    score = (y / check) * score;
                  }
                  if (best_score < score) {
                    best_score = score;
                    best_dir = dir;
                    will_attack = is_attack;
                    attack_cost = attack_bonus;
                  }
                  if (max_score < city7) {
                    max_score = city7;
                  }
                }
              }
            }
          }
LAB_0054168e: ;
        }
        if ((will_attack != 0) &&
           (city7 = (uint)cosmic.road_move_mult - attack_cost, near_dist = unit_moves_left(unit),
           near_dist < city7)) {
          best_dir = 8;
        }
        if (max_score != best_score) {
          best_dir = 8;
        }
        if (best_dir == 8) {
          will_attack = 0;
        }
        if ((has_orders != 0) && (will_attack == 0)) goto LAB_005436c1;
        if ((hold_pos != 0) && (will_attack == 0)) {
          best_dir = 8;
        }
        units[unit].ai_task = '9';
        city3 = best_dir;
      }
      else {
        best_dir = 8;
        city3 = best_dir;
      }
    }
  }
  else {
    units[unit].flags = units[unit].flags | 8;
    units[unit].ai_task = 'd';
    best_dir = 8;
    city3 = best_dir;
  }
LAB_005435ca:
  best_dir = city3;
  if (best_dir == 8) {
    units[unit].last_dir = 0xff;
    units[unit].orders = -1;
  }
  else {
    x2 = map_wrap_x((char)(&dir_dx_table)[best_dir] + x2);
    y3 += (char)(&dir_dy_table)[best_dir];
    near_dist = map_in_bounds(x2,y3);
    if (near_dist == 0) {
      units[unit].orders = -1;
      unit_exhaust_moves(unit);
    }
    else {
      units[unit].orders = 27;
      units[unit].goto_x = (i16)x2;
      units[unit].goto_y = (i16)y3;
    }
  }
LAB_005436c1:
  if ((((units[unit].orders == -1) || (units[unit].orders == 16)) ||
      (units[unit].orders == 1)) || (units[unit].orders == 2)) {
    if (units[unit].orders == 16) {
      units[unit].ai_task = '0';
    }
    if (unit_types[units[unit].type].domain == 1) {
      units[unit].orders = -1;
      units[unit].moves_used += cosmic.road_move_mult;
      return 1;
    }
    unit_exhaust_moves(unit);
    if ((unit_domain == 0) && (unit_types[units[unit].type].role != 5)) {
      units[unit].orders = 1;
      if ((units[unit].flags & 0x100) != 0) {
        units[unit].orders = 2;
      }
      if (stay_home) {
        units[unit].orders = -1;
      }
    }
    else {
      units[unit].orders = -1;
    }
  }
  if (((units[unit].orders == 11) && (units[unit].goto_x == units[unit].x)) &&
     (units[unit].y == units[unit].goto_y)) {
    units[unit].flags = units[unit].flags | 0x80;
    units[unit].orders = -1;
    if (units[unit].moves_used != '\0') {
      if (unit_types[units[unit].type].role == 2) {
        near_dist = unit_stack_count_role(unit,4);
        if (near_dist != 0) {
          unit_exhaust_moves(unit);
        }
      }
      else {
        unit_exhaust_moves(unit);
      }
    }
  }
  return 0;
LAB_00540f1e:
  if (((*(byte *)&civs[civ].treaties[civ2] & 0xe) != 0) &&
     ((ai_role != 7 ||
      (city7 = tile_city_owner((int)units[unit].goto_x,(int)units[unit].goto_y),
      city7 < 0)))) {
    flag = 0;
    units[unit].orders = -1;
  }
LAB_00540fea:
  if (flag != 0) goto LAB_005436c1;
LAB_00541001:
  if ((((ai_role == 1) && (terrain2 != 10)) && (has_orders == 0)) && (!forced_attack)) {
    flag = 0;
    city7 = unit_stack_sum(unit,2);
    if ((city7 < 2) && (own_dist < 4)) {
      flag = flag | 1;
    }
    if (((in_enemy_zoc != 0) && (city7 = unit_stack_count_role(unit,1), city7 == 1)) &&
       ((((int)city4 < 0 ||
         (((city4 == city2 || (4 < near_dist)) ||
          ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + cities[city4].owner * 4) & 0x20) != 0)))) ||
        (6 < (int)((uint)civs[cities[city4].owner].reputation -
                  (int)civs[civ].reputation_credit[cities[city4].owner]))))) {
      flag = flag | 2;
    }
    if ((fort_need != 0) || (on_fortress != 0)) {
      city7 = unit_stack_count_role(unit,1);
      if (city7 == 1) {
        flag = flag | 4;
      }
      if ((flag != 0) || ((units[unit].flags & 0x100) != 0)) {
        flag = flag | 8;
      }
    }
    terrain = flag;
    if (((char)unit_types[unit_type].defense <= (char)unit_types[unit_type].attack) &&
       (terrain = flag & 0xfffffffe,
       (char)unit_types[unit_type].defense < (char)unit_types[unit_type].attack)) {
      terrain = flag & 0xfffffff4;
    }
    flag = terrain;
    civ2 = tile_radius_civ(x2,y3);
    if ((((0 < (int)civ2) && (civ2 != civ)) &&
        ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0)) &&
       ((int)((uint)civs[civ2].reputation - (int)civs[civ].reputation_credit[civ2])
        < 7)) {
      flag = 0;
    }
    if (flag != 0) {
      if ((flag & 0xc) != 0) {
        civ_clear_standing_goals_near(civ,1,x2,y3,1);
      }
      units[unit].ai_task = 'F';
      if ((char)unit_types[unit_type].attack < (char)unit_types[unit_type].defense) {
        best_dir = 8;
        city3 = best_dir;
        goto LAB_005435ca;
      }
      hold_pos = 1;
      goto LAB_005414d7;
    }
  }
  if (((is_settler) &&
      (*(short *)(&landmass_fertile_tiles + landmass * 0x10) >> 3 <
       (short)(ushort)civs[civ].continent_cities[landmass])) &&
     (units[unit].home_city != -1)) {
    if ((own_dist == 0) && (cities[city2].size < '\n')) {
      cities[city2].size++;
      unit_destroy_redraw(unit,1);
      city_window_refresh_if_city((FrameWindow *)&city_window,city2);
      map_redraw_area_all_views(x2,y3,1,1,1);
      return 1;
    }
    if (((-1 < (int)city2) && (landmass == own_landmass)) && (cities[city2].size < '\n')) {
      unit_set_goto(unit,0x42,(int)cities[city2].x,(int)cities[city2].y);
      goto LAB_005436c1;
    }
  }
  goto LAB_005414d7;
}
#undef mp_double_production
#undef scenario_flags
#undef cargo_target
#undef x4
#undef work_flags
#undef goal_match
#undef unit
#undef city6
#undef in_enemy_zoc
#undef civ4
#undef unit_domain
#undef trade_target
#undef city
#undef needed_defenders
#undef is_attack
#undef sea_south
#undef ally_civ
#undef y4
#undef near_landmass
#undef max_score
#undef fort_need
#undef ally_territory
#undef y3
#undef ai_role
#undef tile_count
#undef needs_units
#undef damage_level
#undef x2
#undef x3
#undef unit4
#undef best_dir
#undef flag
#undef explore_flag
#undef on_fortress
#undef sea_north
#undef goto_city
#undef role_count
#undef attack_bonus
#undef room_aboard
#undef has_orders
#undef type_flags
#undef defender_count
#undef unit5
#undef retried
#undef hold_pos
#undef x6
#undef city4
#undef home_dist
#undef terrain2
#undef dir2
#undef civ2
#undef y2
#undef cand_score
#undef is_ocean
#undef explore
#undef attack_cost
#undef dir
#undef civ3
#undef own_landmass
#undef unit3
#undef will_attack
#undef sea_east
#undef is_guard
#undef city5
#undef city2
#undef own_dist
#undef best_score
#undef freed_count
#undef divisor
#undef target_policy
#undef sea_west
#undef race_behind
#undef no_moves
#undef here_landmass
#undef score
#undef tile_flags
#undef attack_value
#undef tasks_mask
#undef ocean_count

/* 00543cd6 auto */
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define order_steps (*(int *)(frame_ + FRAME_OFF(4)))
#define pass (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl ai_process_civ_units(void)

{
  bool naval_first_turn;
  i16 prev_num_units;
  int civ;
  int result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (int)game.turn_civ;
  naval_first_turn = false;
  if (((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) && (game.turn == 1)
      ) && (scenario_objective_civ == civ)) {
    naval_first_turn = true;
  }
  pass = 0;
  do {
    if (1 < pass) {
      return;
    }
    unit = (iptr)game.num_units;
    while (unit = unit - 1, -1 < unit) {
      if (2 < game.multiplayer) {
        if (net_host_handoff_stage != '\0') {
          return;
        }
        if (player_has_quit != '\0') {
          return;
        }
      }
      if (((units[unit].id != 0) && (units[unit].owner == civ)) &&
         ((order_steps = 0, !naval_first_turn ||
          ((pass != 0 || (unit_types[units[unit].type].domain == 1)))))) {
        while (result = unit_is_awake_with_moves(unit), result != 0) {
          if (2 < game.multiplayer) {
            net_send_state_diff(0xff,2,0,0,0);
            XD_FlushSendBuffer(5000);
            net_process_messages((NetSession *)&net_session,1,0);
          }
          prev_num_units = game.num_units;
          game.active_unit = (i16)unit;
          unit_continue_active_orders();
          if (game.num_units != prev_num_units) break;
          if ((units[unit].orders != 11) &&
             (unit_types[units[unit].type].domain != 1)) {
            order_steps++;
          }
          order_steps++;
          if (0x14 < order_steps) {
            unit_exhaust_moves(unit);
            break;
          }
          if ((((pass == 0) && (civ != 0)) && (unit_types[units[unit].type].hold != '\0'))
             && (((result = unit_moves_left(unit), result == 0 &&
                  (result = tile_is_ocean((int)units[unit].x,(int)units[unit].y), result != 0)
                  ) && ((result = unit_stack_sum(unit,2), 1 < result &&
                        (((game.human_players & units[unit].visibility) != 0 ||
                         (result = tile_adjacent_nonallied_civ((int)units[unit].x,(int)units[unit].y,
                                                     civ), result != 0)))))))) {
            unit_continue_active_orders();
          }
        }
        mapviews_redraw_cursor();
      }
    }
    pass++;
  } while( true );
}
#undef net_host_handoff_stage
#undef player_has_quit
#undef scenario_flags
#undef scenario_objective_civ
#undef unit
#undef order_steps
#undef pass

/* 0057febc auto */
#define path_goal_x (*(iptr *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(iptr *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(int *)((u8 *)&g.d_0062d044))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl ai_respond_to_attack(iptr civ,iptr x,iptr y)

{
  int civ2;
  int target_landmass;
  int result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit = 0;
  while( true ) {
    if (game.num_units <= unit) {
      civ2 = tile_owner(x,y);
      target_landmass = tile_landmass(x,y);
      for (unit = 0; unit < game.num_units; unit++) {
        if (((units[unit].id != 0) &&
            ((((units[unit].owner == civ ||
               (((units[unit].owner != civ2 &&
                 ((*(byte *)&civs[civ].treaties[units[unit].owner] & 8) != 0)) &&
                (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) == 0)))) &&
              (((unit_types[units[unit].type].domain == '\0' &&
                (unit_types[units[unit].type].attack != '\0')) &&
               (result = unit_moves_left(unit), result != 0)))) &&
             ((unit_types[units[unit].type].role != 1 ||
              (result = tile_city_owner((int)units[unit].x,(int)units[unit].y), result < 0))))
            )) && ((result = map_distance(x,y,(int)units[unit].x,
                                               (int)units[unit].y), result < 7 &&
                   (result = tile_landmass((int)units[unit].x,(int)units[unit].y),
                   result == target_landmass)))) {
          path_owner_civ = (int)units[unit].owner;
          path_unit_type = (iptr)units[unit].type;
          path_goal_x = x;
          path_goal_y = y;
          result = unit_moves_left(unit);
          result = map_path_next_dir((int)units[unit].x,(int)units[unit].y,result * 2);
          if ((0 < result) && (result != 8)) {
            units[unit].orders = 11;
            units[unit].goto_x = (i16)x;
            units[unit].goto_y = (i16)y;
            units[unit].ai_task = 'K';
          }
        }
      }
      return;
    }
    if (((((units[unit].id != 0) && (units[unit].owner == civ)) &&
         ((unit_types[units[unit].type].flags & 0x100) != 0)) &&
        (civ2 = tile_city_owner((int)units[unit].x,(int)units[unit].y), -1 < civ2)) &&
       (((units[unit].moves_used == '\0' || ((units[unit].flags & 0x100) != 0)) &&
        (((units[unit].flags & 0x10) == 0 &&
         (civ2 = map_distance((int)units[unit].x,(int)units[unit].y,x,y),
         civ2 <= (int)(uint)cosmic.paradrop_range)))))) break;
    unit++;
  }
  unit_paradrop(unit,x,y);
  return;
}
#undef path_goal_x
#undef path_goal_y
#undef path_owner_civ
#undef unit

/* 00598d45 auto */
#define own_progress (*(int *)(frame_ + FRAME_OFF(0)))
#define part (*(int *)(frame_ + FRAME_OFF(8)))
#define rival_progress (*(int *)(frame_ + FRAME_OFF(12)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(16)))
i32 __cdecl ai_spaceship_race_behind(iptr civ)

{
  iptr race_active;
  iptr launched;
  int result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  race_active = spaceship_race_active();
  if ((((race_active != 0) && (launched = civ_spaceship_launched(civ), launched == 0)) &&
      ((game.game_flags & 2) == 0)) &&
     ((game.difficulty != '\0' && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0))))
  {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
         (result = civ_spaceship_launched(civ2), result != 0)) {
        return 1;
      }
    }
    own_progress = 0;
    for (part = 0; part < 6; part++) {
      result = int_clamp((part + 1) / 2,0,2);
      own_progress = own_progress +
                 (int)civs[civ].spaceship_parts[part] *
                 (uint)improvements[result + 0x23].cost;
    }
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
          (result = civ_has_advance(civ2,0x4c), result != 0)) && (civ2 != civ)) {
        rival_progress = 0;
        for (part = 0; part < 6; part++) {
          result = int_clamp((part + 1) / 2,0,2);
          rival_progress = rival_progress + (int)civs[civ2].spaceship_parts[part] *
                              (uint)improvements[result + 0x23].cost;
        }
        if (own_progress <= rival_progress) {
          return 1;
        }
      }
    }
  }
  return 0;
}
#undef own_progress
#undef part
#undef rival_progress
#undef civ2

/* 005b68f6 auto */
#define level (*(iptr *)(frame_ + FRAME_OFF(4)))
i32 __cdecl ai_tile_improve_choice(iptr civ,iptr x,i32 y)

{
  byte terrain_byte;
  int result;
  uint improvements_mask;
  uint terrain;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = tile_city_owner(x,y);
  if (((result < 0) && (improvements_mask = tile_improvements(x,y), (improvements_mask & 8) == 0)) &&
     (((improvements_mask & 4) == 0 || (result = civ_has_advance(civ,0x46), result != 0)))) {
    terrain_byte = tile_terrain(x,y);
    terrain = (uint)terrain_byte;
    for (level = 0; level < 2; level++) {
      if (level == 0) {
        result = tile_has_irrigation_source(x,y);
        if (result == 0) {
          return 0;
        }
      }
      else if ((improvements_mask & 4) != 0) {
        return 0;
      }
      if (((*(char *)(level + (iptr)((u8 *)&terrain_types + 14) + terrain * 0x18) != -1) &&
          (*(char *)(level + (iptr)((u8 *)&terrain_types + 20) + terrain * 0x18) != '\0')) &&
         ((int)*(char *)(level + (iptr)((u8 *)&terrain_types + 20) + terrain * 0x18) <= (int)(uint)civs[civ].government))
      {
        return level + 1;
      }
    }
  }
  return 0;
}
#undef level
