/* The game, the computer players: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00442885 auto */
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl ai_city_touches_landmass(iptr city,int param_2)

{
  short x2;
  short y2;
  int y;
  i32 uVar4;
  iptr x;
  int iVar6;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = cities[city].x;
  y2 = cities[city].y;
  y = tile_landmass((int)x2,(int)y2);
  if (y == param_2) {
    uVar4 = 1;
  }
  else {
    for (local_8 = 0; (int)local_8 < 8; local_8++) {
      x = map_wrap_x((int)(char)(&dir_dx_table)[local_8] + (int)x2);
      y = (int)(char)(&dir_dy_table)[local_8] + (int)y2;
      iVar6 = map_in_bounds(x,y);
      if ((iVar6 != 0) && (iVar6 = tile_is_ocean(x,y), iVar6 != 0)) {
        x = tile_landmass(x,y);
        y = landmass_borders_body(param_2,x);
        if (y != 0) {
          return 1;
        }
        local_8 += (2 - (local_8 & 1));
      }
    }
    uVar4 = 0;
  }
  return uVar4;
}
#undef local_8

/* 004bdb2c auto */
#define local_3c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(12)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(16)))
#define city (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(48)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
int __cdecl ai_advance_value(iptr civ,iptr advance)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  iptr iVar4;
  iptr iVar5;
  int iVar6;
  int city2;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_38 = (int)leaders[civs[civ].tribe].civilize;
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) && (-1 < local_38)) {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
          ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) != 0)) &&
         (civs[civ].num_advances < civs[civ2].num_advances)) {
        for (local_28 = 1; local_28 < 0x3f; local_28++) {
          if ((*(char *)&civs[civ].continent_cities[local_28] != '\0') &&
             (*(char *)&civs[civ2].continent_cities[local_28] != '\0')) {
            if (-1 < local_38) {
              local_38--;
            }
            if (6 < civs[civ2].reputation) {
              local_38 = -1;
            }
          }
        }
      }
    }
  }
  local_8 = advances[advance].civilized_mod * local_38 + (int)advances[advance].ai_value;
  iVar4 = advance_has_prereq((int)unit_types[0x20].prerequisite,advance);
  if (iVar4 == 0) {
    city2 = advance_has_prereq((int)unit_types[0x21].prerequisite,advance);
    if ((city2 == 0) &&
       (city2 = advance_has_prereq((int)unit_types[0x23].prerequisite,advance), city2 == 0)) {
      city2 = advance_has_prereq((int)unit_types[0x2b].prerequisite,advance);
      if (city2 == 0) {
        local_10 = 0;
      }
      else {
        local_10 = 1;
      }
    }
    else {
      local_10 = 2;
    }
  }
  else {
    local_10 = 3;
  }
  if ((game.game_flags & 4) != 0) {
    local_10 = local_10 << 1;
  }
  if (local_10 != 0) {
    local_34 = 0;
    bVar2 = false;
    for (local_28 = 1; local_28 < 0x3f; local_28++) {
      if (*(char *)&civs[civ].continent_cities[local_28] != '\0') {
        bVar3 = false;
        for (civ2 = 0; civ2 < 8; civ2++) {
          if ((civ != civ2) &&
             ((*(char *)&civs[civ].continent_cities[local_28] != '\0' ||
              (*(short *)&civs[civ].continent_military[local_28] != 0)))) {
            bVar3 = true;
            if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
              bVar2 = true;
            }
            break;
          }
        }
        if (!bVar3) {
          local_34 = 1;
          break;
        }
      }
    }
    if (local_34 == 0) {
      if ((!bVar2) || ((game.game_flags & 4) != 0)) {
        local_8++;
      }
    }
    else {
      local_8 += local_10;
    }
  }
  if (improvements[0x22].preq == advance) {
    local_8 = local_8 + ((int)((int)civs[civ].num_ships +
                              ((int)civs[civ].num_ships >> 0x1f & 3U)) >> 2);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    if ((game.human_players & game.advance_known_by[0x4c]) != 0) {
      iVar5 = advance_has_prereq(0x20,advance);
      if (iVar5 != 0) {
        local_8 += 2;
      }
      for (improvement = 0x23; improvement < 0x26; improvement++) {
        if (improvements[improvement].preq == advance) {
          local_8 += 3;
        }
      }
    }
    city2 = local_8;
    if ((((-1 < unit_types[0x1c].prerequisite) &&
         ((game.human_players & game.advance_known_by[unit_types[0x1c].prerequisite]) != 0)) &&
        (iVar6 = advance_has_prereq((int)unit_types[0x1c].prerequisite,advance), iVar6 != 0)) &&
       (city2 = local_8 + 2, unit_types[0x1c].prerequisite == advance)) {
      city2 = local_8 + 5;
    }
    local_8 = city2;
    for (local_18 = 0; local_18 < 0x1c; local_18++) {
      if (wonder_expires[local_18] == advance) {
        city2 = civ_has_wonder(civ,local_18);
        if ((city2 != 0) && (advance != 0x25)) {
          local_8 -= 2;
        }
        city2 = wonder_get_city(local_18);
        if ((-1 < city2) && (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0))
        {
          local_8 += 2;
        }
      }
    }
  }
  if ((improvements[9].preq == advance) || (improvements[0x17].preq == advance)) {
    local_24 = 0;
    for (city = 0; city < game.num_cities; city++) {
      city2 = local_24;
      if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
         (city2 = (int)cities[city].size, cities[city].size <= local_24)) {
        city2 = local_24;
      }
      local_24 = city2;
    }
    bVar1 = cosmic.sewer_size;
    if (improvements[9].preq == advance) {
      bVar1 = cosmic.aqueduct_size;
    }
    local_3c = (uint)bVar1;
    if ((int)local_3c <= local_24) {
      local_8 += 2;
    }
  }
  if ((-1 < leaders[civs[civ].tribe].civilize) &&
     (city2 = civ_has_advance(civ,0x55), city2 != 0)) {
    city2 = advance_has_prereq(0x10,advance);
    if (city2 != 0) {
      local_8 = local_8 + leaders[civs[civ].tribe].civilize + 1;
    }
    if (advance == 0x10) {
      local_8 += 2;
    }
  }
  iVar6 = civ_has_advance(civ,0x26);
  city2 = local_8;
  if ((iVar6 != 0) && (iVar6 = advance_has_prereq(0x25,advance), iVar6 != 0)) {
    iVar6 = civ_has_advance(civ,0x39);
    city2 = local_8 + 1;
    if (iVar6 != 0) {
      city2 = local_8 + 2;
    }
  }
  local_8 = city2;
  switch(civs[civ].tribe) {
  case 0:
    if (((advance == 0x27) || (advance == 8)) || (advance == 0x56)) {
      local_8 += 2;
    }
    if (advance == 0x37) {
      local_8--;
    }
    break;
  case 1:
    if (advance == 0xc) {
      local_8++;
    }
    break;
  case 2:
    if (advance == 6) {
      local_8++;
    }
    if (advance == 0x52) {
      local_8++;
    }
    if (advance == 0x3c) {
      local_8++;
    }
    break;
  case 3:
    if (advance == 0x2f) {
      local_8 += 2;
    }
    break;
  case 4:
    if (advance == 0x15) {
      local_8 += 2;
    }
    if (advance == 0xf) {
      local_8--;
    }
    if (advance == 0x49) {
      local_8++;
    }
    if (advance == 0x10) {
      local_8++;
    }
    if (advance == 0x2a) {
      local_8++;
    }
    break;
  case 5:
    if (advance == 0x40) {
      local_8++;
    }
    if (advance == 8) {
      local_8++;
    }
    if (advance == 1) {
      local_8++;
    }
    if (advance == 0x2e) {
      local_8++;
    }
    if (advance == 0x37) {
      local_8--;
    }
    if (advance == 0x3c) {
      local_8 += 2;
    }
    break;
  case 6:
    if (advance == 0x40) {
      local_8 += 2;
    }
    if (advance == 0x24) {
      local_8++;
    }
    if (advance == 0x38) {
      local_8++;
    }
    if (advance == 9) {
      local_8++;
    }
    if (advance == 0x37) {
      local_8--;
    }
    break;
  case 7:
    if (advance == 0xf) {
      local_8 += 2;
    }
    if (advance == 0x3c) {
      local_8++;
    }
    if (advance == 0x22) {
      local_8++;
    }
    break;
  case 8:
    if (advance == 0x40) {
      local_8 += 2;
    }
    if (advance == 0x24) {
      local_8++;
    }
    if (advance == 0x38) {
      local_8++;
    }
    if (advance == 9) {
      local_8++;
    }
    if (advance == 8) {
      local_8--;
    }
    if (advance == 0x27) {
      local_8--;
    }
    break;
  case 9:
    if (advance == 0x2a) {
      local_8++;
    }
    if (advance == 0x51) {
      local_8++;
    }
    if (advance == 0x11) {
      local_8++;
    }
    break;
  case 10:
    if (advance == 0x23) {
      local_8 -= 2;
    }
    if (advance == 0x37) {
      local_8--;
    }
    break;
  case 0xb:
    if (local_34 != 0) {
      local_8 -= local_10;
    }
    if (advance == 0x23) {
      local_8++;
    }
    break;
  case 0xc:
    if (advance == 0x37) {
      local_8++;
    }
    if (local_10 != 0) {
      local_8++;
    }
    break;
  case 0xf:
    if (advance == 0x4f) {
      local_8++;
    }
    if (advance == 0x34) {
      local_8++;
    }
    break;
  case 0x10:
    if (advance == 0x2e) {
      local_8++;
    }
    break;
  case 0x11:
    if (1 < local_10) {
      local_8++;
    }
    if (advance == 0x37) {
      local_8++;
    }
    break;
  case 0x12:
  case 0x13:
    if (advance == 0x40) {
      local_8 += 2;
    }
    if (advance == 0x24) {
      local_8++;
    }
    if (advance == 0x38) {
      local_8++;
    }
    if (advance == 9) {
      local_8++;
    }
    if (advance == 0x37) {
      local_8--;
    }
    break;
  case 0x14:
    if (advance == 0x24) {
      local_8 += 2;
    }
  }
  if (game.advance_known_by[advance] == '\0') {
    local_8++;
  }
  for (advance2 = 0; advance2 < 100; advance2++) {
    if (((advances[advance2].preq[0] == advance) || (advances[advance2].preq[1] == advance)) &&
       (city2 = civ_has_advance(civ,advance2), city2 != 0)) {
      local_8--;
    }
  }
  if (local_8 < 2) {
    local_8 = 1;
  }
  return local_8;
}
#undef local_3c
#undef local_38
#undef local_34
#undef improvement
#undef city
#undef local_28
#undef local_24
#undef advance2
#undef local_18
#undef civ2
#undef local_10
#undef local_8

/* 004f03b7 auto */
#define city_tile_job_found (*(i32 *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_x (*(int *)((u8 *)&g.d_006a65e0))
#define city_tile_job_y (*(int *)((u8 *)&g.d_006a65e8))
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(i32 *)((u8 *)&g.d_0062d044))
#define path_road_planning (*(i32 *)((u8 *)&g.d_0062d040))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(36)))
i32 __cdecl ai_find_road_link_tile(iptr city)

{
  bool bVar1;
  iptr iVar2;
  int civ;
  int x;
  int y;
  iptr iVar6;
  iptr iVar7;
  int iVar8;
  uint uVar9;
  byte *pbVar10;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = tile_land_landmass((int)cities[city].x,(int)cities[city].y);
  civ = (int)cities[city].owner;
  if (1 < civs[civ].continent_cities[iVar2]) {
    for (local_14 = 0; local_14 < 2; local_14++) {
      for (city2 = 0; city2 < game.num_cities; city2++) {
        if (((cities[city2].id != 0) && (city != city2)) &&
           ((cities[city2].owner == civ ||
            ((local_14 != 0 &&
             ((*(byte *)&civs[civ].treaties[cities[city2].owner] & 0xc) != 0)))))) {
          x = (int)cities[city2].x;
          y = (int)cities[city2].y;
          x2 = (int)cities[city].x;
          y2 = (int)cities[city].y;
          local_34 = 0;
          iVar6 = tile_land_landmass(x,y);
          if ((iVar2 == iVar6) &&
             (iVar7 = map_distance(x,y,x2,y2), iVar7 < 0x17)) {
            path_road_planning = 1;
            path_owner_civ = 0xffffffff;
            path_unit_type = 2;
            bVar1 = true;
            path_goal_x = x;
            path_goal_y = y;
            while ((iVar8 = map_path_next_dir(x2,y2,99), -1 < iVar8 && (iVar8 != 8))) {
              x2 = map_wrap_x((char)(&dir_dx_table)[iVar8] + x2);
              y2 += (char)(&dir_dy_table)[iVar8];
              if ((x2 == x) && (y2 == y)) break;
              iVar8 = tile_city_owner(x2,y2);
              if (iVar8 < 0) {
                uVar9 = tile_improvements(x2,y2);
                if ((uVar9 & 0x10) == 0) {
                  pbVar10 = (byte *)tile_at(x2,y2);
                  if (((*pbVar10 & 0x80) == 0) || (iVar8 = civ_has_advance(civ,7), iVar8 != 0))
                  {
                    bVar1 = false;
                  }
                }
                else {
                  uVar9 = tile_improvements(x2,y2);
                  if (((uVar9 & 0x20) == 0) && (iVar8 = civ_has_advance(civ,0x43), iVar8 != 0))
                  {
                    bVar1 = false;
                  }
                }
              }
              local_34++;
              if ((0x32 < local_34) || (!bVar1)) break;
            }
            path_road_planning = 0;
            if (((!bVar1) &&
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
#undef local_34
#undef y2
#undef x2
#undef local_14

/* 00531287 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl ai_unit_role(iptr unit)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (int)(char)unit_types[units[unit].type].role;
  if ((local_8 == 5) && ((units[unit].flags & 0x200) != 0)) {
    local_8 = 0x15;
  }
  return local_8;
}
#undef local_8

/* 005312e4 auto */
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_14 (*(byte *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
iptr __cdecl ai_ship_best_landing_dir(iptr unit)

{
  short x3;
  short y3;
  int civ;
  iptr x2;
  int y2;
  int y;
  iptr x;
  int iVar8;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  x3 = units[unit].x;
  y3 = units[unit].y;
  civ = (int)units[unit].owner;
  local_c = -1;
  local_2c = -1;
  for (local_10 = 0; local_10 < 9; local_10++) {
    x2 = map_wrap_x((int)(char)(&dir_dx_table)[local_10] + (int)x3);
    y2 = (int)(char)(&dir_dy_table)[local_10] + (int)y3;
    y = map_in_bounds(x2,y2);
    if (((y != 0) && (y = tile_is_ocean(x2,y2), y != 0)) &&
       ((local_10 == 8 || (y = tile_unit_owner(x2,y2), y < 0)))) {
      local_8 = 0;
      for (local_24 = 0; local_24 < 8; local_24++) {
        x = map_wrap_x((char)(&dir_dx_table)[local_24] + x2);
        y = (char)(&dir_dy_table)[local_24] + y2;
        iVar8 = map_in_bounds(x,y);
        if ((((iVar8 != 0) && (iVar8 = tile_is_ocean(x,y), iVar8 == 0)) &&
            (iVar8 = tile_unit_owner(x,y), iVar8 < 0)) &&
           (((iVar8 = tile_owner_or_fertility(x,y), 7 < iVar8 ||
             (local_14 = (byte)iVar8, (1 << (local_14 & 0x1f) & (uint)game.human_players) == 0)) ||
            ((*(byte *)&civs[civ].treaties[iVar8] & 6) == 0)))) {
          iVar8 = tile_city_owner(x,y);
          if (((-1 < iVar8) && (iVar8 != civ)) &&
             ((y = tile_unit_owner(x,y), y < 0 &&
              ((y = diplo_is_hostile(civ,iVar8), y != 0 && (local_10 == 8)))))) {
            local_8 += 0xc;
          }
          local_8++;
        }
      }
      if (local_c <= local_8) {
        local_c = local_8;
        local_2c = local_10;
      }
    }
  }
  return local_2c;
}
#undef local_2c
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00531653 auto */
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(32)))
void __cdecl ai_ship_goto_near_shore(iptr unit,i32 param_2,iptr x,int y)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  iptr x3;
  int y3;
  int y2;
  iptr x2;
  int iVar8;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_20 = x;
  local_24 = y;
  iVar2 = tile_landmass((int)units[unit].x,(int)units[unit].y);
  iVar3 = tile_landmass(x,y);
  for (local_8 = 0; y3 = local_24, x3 = local_20, local_8 < 0x14; local_8++) {
    x3 = map_wrap_x((char)(&city_tile_dx_table)[local_8] + x);
    y3 = (char)(&city_tile_dy_table)[local_8] + y;
    y2 = map_in_bounds(x3,y3);
    if (((y2 != 0) && (y2 = tile_is_ocean(x3,y3), y2 != 0)) &&
       (y2 = tile_landmass(x3,y3), y2 == iVar2)) {
      bVar1 = false;
      for (local_10 = 0; local_10 < 8; local_10++) {
        x2 = map_wrap_x((char)(&dir_dx_table)[local_10] + x3);
        y2 = (char)(&dir_dy_table)[local_10] + y3;
        iVar8 = map_in_bounds(x2,y2);
        if (((iVar8 != 0) && (iVar8 = tile_is_ocean(x2,y2), iVar8 == 0)) &&
           ((iVar8 = tile_landmass(x2,y2), iVar8 == iVar3 &&
            (y2 = tile_city_owner(x2,y2), y2 < 0)))) {
          bVar1 = true;
        }
      }
      if (bVar1) break;
    }
  }
  local_20 = x3;
  local_24 = y3;
  unit_set_goto(unit,param_2,local_20,local_24);
  return;
}
#undef local_24
#undef local_20
#undef local_10
#undef local_8

/* 0053184d auto */
#define city_calc_cached_id (*(i32 *)((u8 *)&g.d_0062ee08))
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define local_368 (*(int *)(frame_ + FRAME_OFF(0)))
#define unit (*(uptr *)(frame_ + FRAME_OFF(20)))
#define local_34c (*(int *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_340 (*(int *)(frame_ + FRAME_OFF(40)))
#define aiStack_33c (*(int (*)[48])(frame_ + FRAME_OFF(44)))
#define local_27c (*(uint *)(frame_ + FRAME_OFF(236)))
#define local_278 (*(iptr *)(frame_ + FRAME_OFF(240)))
#define unit_type (*(uptr *)(frame_ + FRAME_OFF(244)))
#define local_270 (*(uint *)(frame_ + FRAME_OFF(248)))
#define y2 (*(int *)(frame_ + FRAME_OFF(252)))
#define x3 (*(int *)(frame_ + FRAME_OFF(256)))
#define local_264 (*(int *)(frame_ + FRAME_OFF(260)))
#define local_260 (*(int *)(frame_ + FRAME_OFF(264)))
#define local_25c (*(int *)(frame_ + FRAME_OFF(268)))
#define x2 (*(int *)(frame_ + FRAME_OFF(272)))
#define local_254 (*(uint *)(frame_ + FRAME_OFF(276)))
#define aiStack_250 (*(int (*)[64])(frame_ + FRAME_OFF(280)))
#define local_150 (*(int *)(frame_ + FRAME_OFF(536)))
#define local_14c (*(int *)(frame_ + FRAME_OFF(540)))
#define local_148 (*(int *)(frame_ + FRAME_OFF(544)))
#define local_144 (*(int *)(frame_ + FRAME_OFF(548)))
#define aiStack_140 (*(int (*)[64])(frame_ + FRAME_OFF(552)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(808)))
#define y3 (*(int *)(frame_ + FRAME_OFF(812)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(816)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(820)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(824)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(828)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(832)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(836)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(840)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(844)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(848)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(852)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(856)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(860)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(864)))
void __cdecl ai_civ_turn_assess(uptr civ)

{
  char *pcVar1;
  short *psVar2;
  byte city2;
  u16 uVar4;
  iptr iVar5;
  iptr iVar7;
  int iVar8;
  int y;
  int iVar9;
  uptr uVar11;
  iptr unit2;
  uptr city5;
  uint uVar13;
  i32 uVar14;
  i8 frame_[FRAME_OFF(872)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_144 = 0;
  local_25c = 0;
  iVar5 = civ_has_advance(civ,(int)unit_types[0xd].prerequisite);
  if (((iVar5 != 0) && (civs[civ].units_active[0xd] != '\0')) &&
     ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && ((int)cities[city].owner != civ)) &&
         ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + cities[city].owner * 4) & 0x20) != 0)) {
        x2 = (int)cities[city].x;
        y2 = (int)cities[city].y;
        iVar7 = tile_unit_owner(x2,y2);
        if (iVar7 < 0) {
          for (city3 = 0; city3 < game.num_cities; city3++) {
            if ((cities[city3].id != 0) && ((int)cities[city3].owner == civ)) {
              iVar8 = (int)cities[city3].x;
              y3 = (int)cities[city3].y;
              y = map_distance(x2,y2,iVar8,y3);
              if (y <= (int)(uint)cosmic.paradrop_range) {
                local_150 = 0;
                for (unit = tile_first_unit(iVar8,y3); -1 < (int)unit;
                    unit = unit_next_in_stack(unit)) {
                  if ((unit_types[units[unit].type].flags & 0x100) != 0) {
                    local_150 = 1;
                    break;
                  }
                }
                if (local_150 != 0) break;
                for (city4 = 0; city4 < game.num_cities; city4++) {
                  if (2 < game.multiplayer) {
                    net_process_messages((NetSession *)&net_session,1,0);
                  }
                  if ((cities[city4].id != 0) && ((int)cities[city4].owner == civ)) {
                    x3 = (int)cities[city4].x;
                    y = (int)cities[city4].y;
                    iVar9 = map_distance(x2,y2,x3,y);
                    if (((int)(uint)cosmic.paradrop_range < iVar9) &&
                       (iVar9 = map_distance(iVar8,y3,x3,y),
                       iVar9 <= (int)(uint)cosmic.paradrop_range)) {
                      for (unit = tile_first_unit(x3,y); -1 < (int)unit;
                          unit = unit_next_in_stack(unit)) {
                        if (((unit_types[units[unit].type].flags & 0x100) != 0) &&
                           (y = unit_moves_left(unit), y != 0)) {
                          unit_relocate(unit,iVar8,y3,1);
                          units[unit].visibility = '\0';
                          unit_exhaust_moves(unit);
                          local_150 = 1;
                          break;
                        }
                      }
                      if (local_150 != 0) break;
                    }
                  }
                }
                if (local_150 != 0) break;
              }
            }
          }
        }
      }
    }
  }
  for (local_10 = 0; local_10 < 4; local_10++) {
    *(i8 *)&civs[civ].wonders_by_group[local_10] = 0;
  }
  for (local_40 = 0; local_40 < 0x1c; local_40++) {
    iVar8 = civ_has_wonder(civ,local_40);
    if (iVar8 != 0) {
      local_10 = local_40 / 7;
      pcVar1 = (char *)(local_10 + ADDR(0x64c6b7, ((u8 *)&civs + 23)) + civ * 0x594);
      *pcVar1 = *pcVar1 + 1;
    }
  }
  for (local_278 = 0; local_278 < 0x40; local_278++) {
    *(i16 *)&civs[civ].continent_military[local_278] = 0;
    *(i16 *)&civs[civ].continent_attack[local_278] = 0;
    *(i8 *)&civs[civ].continent_city_size[local_278] = 0;
    *(i8 *)&civs[civ].continent_trade_units[local_278] = 0;
    *(i8 *)&civs[civ].continent_flags[local_278] = 0;
    aiStack_250[local_278] = 0;
    aiStack_140[local_278] = 0;
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
  for (local_24 = 0; local_24 < 0x30; local_24++) {
    if ((civs[civ].ai_goals[local_24].role == 21) &&
       ('\0' < civs[civ].ai_goals[local_24].priority)) {
      local_278 = tile_land_landmass((int)civs[civ].ai_goals[local_24].x,
                                     (int)civs[civ].ai_goals[local_24].y);
      if (-1 < local_278) {
        aiStack_140[local_278]++;
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
        local_144++;
        iVar8 = tile_is_ocean((int)units[unit].x,(int)units[unit].y);
        if (iVar8 == 0) {
          units[unit].flags = units[unit].flags | 0x200;
          iVar8 = tile_landmass((int)units[unit].x,(int)units[unit].y);
          aiStack_250[iVar8]++;
          iVar8 = city_find_nearest((int)units[unit].x,(int)units[unit].y,-1,0xffffffff,
                                     -1);
          if ((nearest_city_dist < 4) && ((int)cities[iVar8].owner == civ)) {
            cities[iVar8].flags = cities[iVar8].flags | 0x40;
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
        pcVar1 = (char *)(unit_type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
        *pcVar1 = *pcVar1 + 1;
        if ((char)unit_types[unit_type].attack < 'c') {
          if ((units[unit].orders == 1) || (units[unit].orders == 2)) {
            units[unit].flags = units[unit].flags | 0x100;
          }
          x2 = (int)units[unit].x;
          y2 = (int)units[unit].y;
          iVar8 = map_in_bounds(x2,y2);
          if (iVar8 == 0) {
            local_278 = -1;
            unit_set_sleep(unit);
          }
          else {
            local_278 = tile_land_landmass(x2,y2);
            if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
              if ((units[unit].orders == 3) &&
                 ((unit_types[unit_type].domain != '\0' ||
                  (iVar8 = tile_is_ocean(x2,y2), iVar8 == 0)))) {
                units[unit].orders = -1;
              }
              if (15 < units[unit].orders) {
                units[unit].orders = -1;
              }
              if ((units[unit].orders == -1) &&
                 (iVar8 = tile_zoc_unit_adjacent(x2,y2,civ), iVar8 != 0)) {
                units[unit].orders = 16;
              }
            }
            iVar8 = tile_is_ocean(x2,y2);
            if ((iVar8 != 0) && (unit_types[units[unit].type].domain == '\0')) {
              unit_set_sleep(unit);
            }
          }
          *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) + 1;
          if (((char)unit_types[unit_type].role < 5) &&
             (civs[civ].num_military_units = civs[civ].num_military_units + 1,
             -1 < local_278)) {
            psVar2 = (short *)(local_278 * 2 + ADDR(0x64c832, ((u8 *)&civs + 402)) + civ * 0x594);
            *psVar2 = *psVar2 + 1;
          }
          if (((unit_types[units[unit].type].role == 7) &&
              (units[unit].home_city != -1)) &&
             (cities[(byte)units[unit].home_city].flags =
                   cities[(byte)units[unit].home_city].flags | 0x1000, -1 < local_278)) {
            pcVar1 = (char *)(local_278 + ADDR(0x64c9b2, ((u8 *)&civs + 786)) + civ * 0x594);
            *pcVar1 = *pcVar1 + 1;
          }
          if ((unit_types[unit_type].role == 5) && (units[unit].home_city != -1)) {
            local_144++;
            if (local_278 < 0) goto LAB_0053232b;
            aiStack_250[local_278]++;
            if (*(char *)&civs[civ].continent_cities[local_278] != '\0') {
              if (civs[civ].government < 2) {
                local_34c = 4;
              }
              else if (civs[civ].government < 5) {
                local_34c = 3;
              }
              else {
                local_34c = 2;
              }
              local_8 = (int)(((local_34c >> 1) - (int)leaders[civs[civ].tribe].expand) - 1 +
                             (uint)civs[civ].continent_cities[local_278]) / local_34c;
              if (unit_type == 1) {
                local_8++;
              }
              iVar8 = aiStack_140[local_278];
              if (local_8 <= aiStack_140[local_278]) {
                iVar8 = local_8;
              }
              local_8 = iVar8;
              if (aiStack_250[local_278] <= iVar8) {
                units[unit].flags = units[unit].flags | 0x200;
              }
            }
            if (units[unit].home_city != -1) {
              city2 = units[unit].home_city;
              if ((((cities[city2].flags & 0x40) != 0) && ((units[unit].flags & 0x200) != 0))
                 && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
                aiStack_250[local_278]--;
                units[unit].flags = units[unit].flags & 0xfdff;
              }
              if (((units[unit].flags & 0x200) != 0) &&
                 (iVar8 = map_distance_diag(x2,y2,(int)cities[city2].x,
                                             (int)cities[city2].y), iVar8 < 5)) {
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
          if (-1 < local_278) {
            *(short *)&civs[civ].continent_attack[local_278] =
                 *(short *)&civs[civ].continent_attack[local_278] +
                 (short)(char)unit_types[unit_type].attack;
          }
        }
      }
      else if ((((game.rules & 0x10) != 0) &&
               ((*(byte *)&civs[civ].treaties[units[unit].owner] & 6) == 0)) &&
              (((1 << ((byte)civ & 0x1f) & (uint)units[unit].visibility) != 0 ||
               ((int)units[unit].owner == (civ & 0xff))))) {
        iVar8 = unit_max_hp(unit);
        y = unit_hp_remaining(unit);
        if (y <= iVar8 / 2) {
          y = 1;
          iVar8 = tile_is_ocean((int)units[unit].x,(int)units[unit].y);
          civ_add_ai_goal(civ,(int)units[unit].x,(int)units[unit].y,
                             (iVar8 == 0) - 1 & 2,y);
        }
      }
    }
LAB_0053232b: ;
  }
  for (local_278 = 0; local_278 < 0x40; local_278++) {
    *(i8 *)&civs[civ].continent_cities[local_278] = 0;
  }
  local_1c = 0;
  for (city = 0; city < game.num_cities; city++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if (cities[city].id != 0) {
      x2 = (int)cities[city].x;
      y2 = (int)cities[city].y;
      iVar8 = map_in_bounds(x2,y2);
      if (iVar8 != 0) {
        if ((int)cities[city].owner == civ) {
          civs[civ].num_cities++;
          civs[civ].total_city_size =
               (short)cities[city].size + civs[civ].total_city_size;
          if (-1 < cities[city].building) {
            pcVar1 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + civ * 0x594);
            *pcVar1 = *pcVar1 + 1;
          }
          local_278 = tile_land_landmass(x2,y2);
          if (-1 < local_278) {
            *(char *)&civs[civ].continent_city_size[local_278] =
                 *(char *)&civs[civ].continent_city_size[local_278] + cities[city].size;
            pcVar1 = (char *)(local_278 + ADDR(0x64c932, ((u8 *)&civs + 658)) + civ * 0x594);
            *pcVar1 = *pcVar1 + 1;
            if ((0 < local_278) && (local_278 < 0x3f)) {
              local_1c++;
            }
          }
          iVar8 = tile_unit_owner(x2,y2);
          if (iVar8 < 0) {
            civ_add_ai_goal(civ,x2,y2,1,5);
          }
        }
        else if ((((200 < (int)((uint)game.difficulty * (int)game.turn)) ||
                  ((1 << ((byte)civ & 0x1f) & (int)(char)cities[city].known_to) != 0)) ||
                 ((int)cities[city].owner == (civ & 0xff))) ||
                (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) == 0)) {
          iVar8 = diplo_is_hostile(civ,(int)cities[city].owner);
          if (((iVar8 != 0) ||
              (((*(byte *)&civs[civ].treaties[cities[city].owner] & 0x20) != 0 &&
               ((*(byte *)&civs[civ].treaties[cities[city].owner] & 8) == 0))))
             && ((game.turn + city) % 3 != 0)) {
            iVar8 = city_has_improvement(city,8);
            civ_add_ai_goal(civ,x2,y2,0,(-(uint)(iVar8 == 0) & 2) + 2);
          }
          iVar8 = tile_unit_owner(x2,y2);
          if ((iVar8 < 0) &&
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
       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0)) {
      civs[civ].flags = civs[civ].flags | 2;
    }
  }
  for (local_278 = 1; local_278 < 0x3f; local_278++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    local_148 = 0;
    local_34 = 0;
    local_340 = 0;
    local_14c = 0;
    local_28 = 0;
    local_270 = (uint)civs[civ].continent_policy[local_278];
    for (civ2 = 1; (int)civ2 < 8; civ2++) {
      if ((*(short *)&civs[civ2].continent_military[local_278] != 0) &&
         (((uint)((int)(uint)civs[civ].continent_attack[local_278] >> 2) <
           (uint)civs[civ2].continent_attack[local_278] ||
          (*(char *)&civs[civ2].continent_cities[local_278] != '\0')))) {
        if (civ != civ2) {
          iVar8 = diplo_is_hostile(civ,civ2);
          if ((iVar8 != 0) || ((*(byte *)&civs[civ].treaties[civ2] & 0x20) != 0))
          {
            if ((civs[civ2].continent_military[local_278] <
                 civs[civ].continent_attack[local_278]) ||
               ((civs[civ2].continent_attack[local_278] <
                 civs[civ].continent_military[local_278] ||
                (*(char *)&civs[civ].continent_cities[local_278] == '\0')))) {
              local_340++;
            }
            else {
              local_34++;
            }
          }
          if ((((*(short *)&civs[civ2].continent_military[local_278] != 0) &&
               ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
              ((*(byte *)&civs[civ].treaties[civ2] & 6) != 0)) &&
             (((int)(uint)civs[civ].continent_attack[local_278] >> 1) +
              (uint)civs[civ].continent_military[local_278] <
              (uint)civs[civ2].continent_attack[local_278])) {
            local_148++;
          }
        }
        local_14c += (uint)civs[civ2].continent_military[local_278];
        local_28 += (uint)civs[civ2].continent_cities[local_278];
        if (civ != civ2) {
          if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
            if (*(char *)&civs[civ2].continent_cities[local_278] != '\0') {
              if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
                civs[civ].continent_flags[local_278] =
                     civs[civ].continent_flags[local_278] | 1;
              }
              else {
                civs[civ].continent_flags[local_278] =
                     civs[civ].continent_flags[local_278] | 2;
              }
            }
            if (*(short *)&civs[civ2].continent_military[local_278] != 0) {
              if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
                civs[civ].continent_flags[local_278] =
                     civs[civ].continent_flags[local_278] | 4;
              }
              else {
                civs[civ].continent_flags[local_278] =
                     civs[civ].continent_flags[local_278] | 8;
              }
            }
          }
          else {
            local_14c += (uint)civs[civ2].continent_military[local_278];
            local_28 += (uint)civs[civ2].continent_cities[local_278];
          }
        }
      }
    }
    if (civs[0].continent_cities[local_278] != '\0') {
      local_340++;
    }
    local_264 = 6;
    if (((((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0) &&
        (4 < civs[game.civ_by_rank[7]].num_cities)) && (0x96 < game.turn)) {
      local_264 = 7;
    }
    if ((game.game_flags & 4) != 0) {
      local_264++;
    }
    iVar8 = ((uint)civs[civ].continent_military[local_278] + local_14c) * 2;
    local_254 = (uint)(iVar8 - *(short *)(&landmass_table + local_278 * 0x10) != 0 &&
                      *(short *)(&landmass_table + local_278 * 0x10) <= iVar8);
    if (*(char *)&civs[civ].continent_flags[local_278] == '\0') {
      local_368 = leaders[civs[civ].tribe].expand + local_264 + 1;
    }
    else {
      local_368 = local_264;
    }
    if ((int)*(short *)(&landmass_fertile_tiles + local_278 * 0x10) <
        (int)(((uint)civs[civ].continent_cities[local_278] + local_28) * local_368 + 2))
    {
      local_254 = 1;
    }
    iVar8 = civ_has_advance(civ,0x2e);
    if (iVar8 == 0) {
      local_254 = 0;
    }
    if (local_254 == 0) {
      *(i8 *)&civs[civ].continent_policy[local_278] = 5;
    }
    else {
      *(i8 *)&civs[civ].continent_policy[local_278] = 4;
    }
    if (local_340 != 0) {
      *(i8 *)&civs[civ].continent_policy[local_278] = 0;
    }
    if ((local_34 != 0) || (local_148 != 0)) {
      *(i8 *)&civs[civ].continent_policy[local_278] = 1;
    }
    if (local_34 != 0) {
      civs[civ].continent_flags[local_278] =
           civs[civ].continent_flags[local_278] | 0x10;
    }
    if (((*(short *)&civs[civ].continent_military[local_278] == 0) &&
        (*(char *)&civs[civ].continent_cities[local_278] == '\0')) &&
       ((civs[civ].continent_flags[local_278] & 0xc) != 8)) {
      *(i8 *)&civs[civ].continent_policy[local_278] = 0;
    }
    if ((civs[civ].continent_policy[local_278] != local_270) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
      civ_reset_city_production(civ,local_278);
    }
  }
  if ((civs[civ].continent_cities[0x3f] != '\0') &&
     (local_1c <= (int)(uint)civs[civ].continent_cities[0x3f])) {
    civs[civ].continent_policy[0x3f] = 4;
  }
  if (civ != 0) {
    local_27c = (uint)game.human_players & 1 << ((byte)civ & 0x1f);
    if (local_27c == 0) {
      if ((local_144 == 0) && (civs[civ].num_cities == 0)) {
        civ_check_destroyed(civ,0);
      }
      if (((int)game.turn + civ & 7) == 0) {
        ai_choose_government(civ,0);
      }
    }
    iVar8 = int_clamp((int)civs[civ].num_military_units >> 3,3,99);
    for (local_2c = 0; local_2c < 0x30; local_2c++) {
      aiStack_33c[local_2c] = iVar8;
      if (civs[civ].ai_goals[local_2c].role == '\0') {
        aiStack_33c[local_2c] = aiStack_33c[local_2c] << 1;
      }
    }
    local_25c = 0;
    if (((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) && (civ == 3)
        ) && (local_27c == 0)) {
      local_25c = 1;
    }
    unit = (uptr)game.num_units;
LAB_00533de4:
    unit--;
    if (-1 < (int)unit) {
      if (2 < game.multiplayer) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
      if (((units[unit].id != 0) && ((int)units[unit].owner == civ)) &&
         ((local_27c == 0 || (((int)(short)units[unit].flags & 0x8000U) != 0)))) {
        if ((char)unit_types[units[unit].type].attack < 'c') {
          if ((units[unit].orders != 16) &&
             ((((15 < units[unit].orders || (units[unit].orders == 11)) ||
               (units[unit].field_0c = '?', units[unit].orders < 4)) &&
              (units[unit].orders != 3)))) {
            x2 = (int)units[unit].x;
            y2 = (int)units[unit].y;
            y = map_in_bounds(x2,y2);
            if ((y != 0) &&
               (local_278 = tile_landmass(x2,y2), units[unit].field_0c != '7')) {
              if (((local_25c != 0) &&
                  (((units[unit].type == 22 || (units[unit].type == '\n')) &&
                   (0x27 < y2)))) && (y2 < 0x5d)) {
                uVar4 = units[unit].flags;
                if ((game.turn == 1) || (uVar11 = tile_owner(0x2b,0x35), uVar11 != civ)) {
LAB_005340a6:
                  unit_set_goto(unit,0x31,0x2b,0x35);
                  units[unit].flags = units[unit].flags & 0xfffc;
                  goto LAB_00533de4;
                }
                if (units[unit].type == '\n') {
                  uVar14 = 2;
                  unit2 = tile_first_unit(0x2b,0x35);
                  y = unit_stack_sum(unit2,uVar14);
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
                     (uVar11 = tile_owner(0x4c,0x22), uVar11 == civ)) {
                    if ((units[unit].flags & 2) != 0) {
                      uVar11 = tile_owner(0x3e,0x48);
                      if (uVar11 == civ) {
                        uVar11 = tile_owner(0x43,0x5b);
                        if (uVar11 != civ) {
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
                units[unit].flags = uVar4;
              }
              if (((((int)game.turn & unit & 0xf) == 0) && (local_27c == 0)) &&
                 ((((-1 < unit_types[units[unit].type].obsolete_by &&
                    (y = civ_has_advance(civ,(int)unit_types[units[unit].type].
                                                             obsolete_by), y != 0)) ||
                   (((1 < civs[civ].government &&
                     (*(char *)&civs[civ].continent_policy[local_278] == 4)) &&
                    (units[unit].type == 2)))) &&
                  ((y = tile_zoc_unit_adjacent(x2,y2,civ), y == 0 &&
                   (((y = tile_city_owner(x2,y2), y < 0 ||
                     (y = unit_stack_sum(unit,2), 1 < y)) &&
                    ((y = tile_is_ocean(x2,y2), y == 0 &&
                     ((civs[civ].continent_flags[local_278] & 0x10) == 0)))))))))) {
                if ((((unit_types[units[unit].type].obsolete_by < '\0') ||
                     (y = civ_has_advance(civ,(int)unit_types[units[unit].type].
                                                              obsolete_by), y == 0)) ||
                    ((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) != 0))
                   || (((int)units[unit].owner == (uint)(byte)human_civ ||
                       ((uVar14 = tile_improvements(x2,y2),
                        ((byte)uVar14 & 0x42) != 0x40 &&
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
              local_18 = 9999;
              local_c = -1;
              local_260 = ai_unit_role(unit);
              if (((((local_260 != 7) || (units[unit].orders != 11)) ||
                   (y = map_in_bounds((int)units[unit].goto_x,(int)units[unit].goto_y)
                   , y == 0)) ||
                  ((civ2 = tile_city_owner((int)units[unit].goto_x,
                                               (int)units[unit].goto_y), (int)civ2 < 0 ||
                   (civ == civ2)))) &&
                 ((unit_types[units[unit].type].role != '\0' ||
                  (unit_types[units[unit].type].attack != '\0')))) {
                for (local_24 = 0; local_24 < 0x30; local_24++) {
                  if (((civs[civ].ai_goals[local_24].role != -1) &&
                      ('\0' < civs[civ].ai_goals[local_24].priority)) &&
                     (y = map_in_bounds((int)civs[civ].ai_goals[local_24].x,
                                            (int)civs[civ].ai_goals[local_24].y), y != 0)) {
                    if (((civs[civ].ai_goals[local_24].role == 18) &&
                        (local_260 == 2)) &&
                       ((unit_types[units[unit].type].flags & 0x4000) != 0)) {
                      local_260 = 0x12;
                    }
                    if (((civs[civ].ai_goals[local_24].role == local_260) &&
                        (y = tile_landmass((int)civs[civ].ai_goals[local_24].x,
                                               (int)civs[civ].ai_goals[local_24].y), y == local_278))
                       || (((unit_types[units[unit].type].domain == 1 &&
                            ((char)unit_types[0x1c].attack <=
                             (char)unit_types[units[unit].type].attack)) &&
                           ((civs[civ].ai_goals[local_24].role == local_260 ||
                            (civs[civ].ai_goals[local_24].role == 2)))))) {
                      local_30 = map_distance_diag(x2,y2,
                                                    (int)civs[civ].ai_goals[local_24].x,
                                                    (int)civs[civ].ai_goals[local_24].y);
                      if (unit_types[units[unit].type].domain == 1) {
                        if (unit_types[units[unit].type].range == 1) {
                          if (local_30 <=
                              (int)(char)unit_types[units[unit].type].move /
                              (int)(uint)cosmic.road_move_mult - 2 >> 1) goto LAB_00534c18;
                        }
                        else if (((*(byte *)&civs[civ].ai_goals[local_24].priority & 1) != 0)
                                && ((((int)game.turn >> 1) + local_24 & 1U) != 0)) {
                          local_30 = (int)((((local_30 <=
                                             (int)(char)unit_types[units[unit].type].move /
                                             (int)(uint)cosmic.road_move_mult) - 1 & 0xfffffffe) + 4
                                           ) * local_30) /
                                     (civs[civ].ai_goals[local_24].priority + 1);
                          goto LAB_00534c18;
                        }
                      }
                      else {
                        local_30 = ((aiStack_33c[local_24] /
                                    (int)((civs[civ].ai_goals[local_24].role ==
                                          '\0') + 1)) * local_30) /
                                   (civs[civ].ai_goals[local_24].priority + 1);
LAB_00534c18:
                        if (((units[unit].orders != 1) &&
                            (units[unit].orders != 2)) ||
                           ((1 < civs[civ].ai_goals[local_24].priority &&
                            (((local_30 <=
                               civs[civ].ai_goals[local_24].priority * iVar8 ||
                              (aiStack_33c[local_24] /
                               (int)((civs[civ].ai_goals[local_24].role == '\0')
                                    + 1) == iVar8)) &&
                             (y = tile_city_owner(x2,y2), y < 0)))))) {
                          if (((local_27c != 0) && (aiStack_33c[local_24] == iVar8)) &&
                             (uVar13 = tile_improvements((int)civs[civ].ai_goals[local_24].x,
                                                         (int)civs[civ].ai_goals[local_24].y),
                             (uVar13 & 0x80) != 0)) {
                            local_30 = (int)(local_30 + (local_30 >> 0x1f & 7U)) >> 3;
                          }
                          if ((local_30 < local_18) &&
                             (local_30 / iVar8 <
                              civs[civ].ai_goals[local_24].priority * 4)) {
                            local_18 = local_30;
                            local_c = local_24;
                          }
                        }
                      }
                    }
                  }
                }
                if (-1 < local_c) {
                  if ((civs[civ].ai_goals[local_c].x == units[unit].x)
                     && (civs[civ].ai_goals[local_c].y == units[unit].y)
                     ) {
                    units[unit].orders = 16;
                    units[unit].flags = units[unit].flags | 0x80;
                    goto LAB_00533de4;
                  }
                  if ((local_260 == 1) &&
                     (uVar14 = tile_improvements((int)units[unit].x,(int)units[unit].y),
                     ((byte)uVar14 & 0x42) == 0x40)) {
                    if ((*(byte *)&civs[civ].ai_goals[local_c].priority & 1) == 0)
                    goto LAB_00533de4;
                    civ_add_standing_goal(civ,(int)units[unit].x,(int)units[unit].y,1,2);
                  }
                  if (((unit_types[units[unit].type].flags & 0x100) == 0) ||
                     (uVar11 = tile_city_owner((int)civs[civ].ai_goals[local_c].x,
                                               (int)civs[civ].ai_goals[local_c].y), uVar11 == civ))
                  {
                    unit_set_goto(unit,0x31,
                                       (int)civs[civ].ai_goals[local_c].x,
                                       (int)civs[civ].ai_goals[local_c].y);
                    if ((unit_types[units[unit].type].role == 5) &&
                       (y = tile_city_owner((int)civs[civ].ai_goals[local_c].x,
                                                (int)civs[civ].ai_goals[local_c].y), -1 < y)) {
                      civs[civ].ai_goals[local_c].priority = 0;
                    }
                    aiStack_33c[local_c]++;
                  }
                }
              }
            }
          }
        }
        else {
          units[unit].field_0c = '!';
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
#undef local_368
#undef unit
#undef local_34c
#undef city
#undef local_340
#undef aiStack_33c
#undef local_27c
#undef local_278
#undef unit_type
#undef local_270
#undef y2
#undef x3
#undef local_264
#undef local_260
#undef local_25c
#undef x2
#undef local_254
#undef aiStack_250
#undef local_150
#undef local_14c
#undef local_148
#undef local_144
#undef aiStack_140
#undef local_40
#undef y3
#undef civ2
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef city4
#undef local_1c
#undef local_18
#undef city3
#undef local_10
#undef local_c
#undef local_8

/* 005351aa auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_88 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_80 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(20)))
#define x3 (*(uint *)(frame_ + FRAME_OFF(32)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define city (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_40 (*(iptr *)(frame_ + FRAME_OFF(72)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(92)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(112)))
#define local_14 (*(byte *)(frame_ + FRAME_OFF(116)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_c (*(int *)(frame_ + FRAME_OFF(124)))
i32 __cdecl ai_barbarian_unit_move(void)

{
  u8 uVar1;
  short y4;
  short y5;
  short x4;
  char cVar5;
  iptr unit;
  iptr civ2;
  int x2;
  iptr y;
  iptr iVar11;
  int y3;
  iptr iVar12;
  iptr x;
  iptr iVar13;
  byte terrain;
  int y2;
  int iVar19;
  iptr unit2;
  iptr civ;
  int iVar20;
  uint uVar21;
  i32 uVar22;
  uptr unit_type;
  bool bVar23;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_40 = 8;
  unit = (iptr)game.active_unit;
  civ2 = (iptr)units[unit].owner;
  if (units[unit].orders != 11) {
    units[unit].orders = -1;
  }
  x2 = (int)units[unit].x;
  y4 = units[unit].y;
  y = (iptr)y4;
  if (((y < 2) || (map.height - 2 <= y)) ||
     (iVar11 = map_in_bounds(x2,y), iVar11 == 0)) {
    unit_delete_with_cargo(unit,1);
    return 1;
  }
  y3 = tile_in_enemy_zoc(x2,y,civ2);
  unit_type = (uptr)units[unit].type;
  city = city_find_nearest(x2,y,-1,0xffffffff,-1);
  if (unit_types[unit_type].hold != '\0') {
    y3 = unit_stack_sum(unit,2);
    iVar12 = unit_stack_count_role(unit,6);
    if (y3 - iVar12 < 2) {
      unit_destroy_redraw(unit,1);
      return 1;
    }
    units[unit].counter++;
    if (30 < (char)units[unit].counter) {
      unit_destroy_redraw(unit,1);
      return 1;
    }
    for (local_18 = 0; local_18 < 8; local_18++) {
      x = map_wrap_x((char)(&dir_dx_table)[local_18] + x2);
      y3 = (char)(&dir_dy_table)[local_18] + y;
      iVar13 = map_in_bounds(x,y3);
      if (iVar13 != 0) {
        if (((-1 < city) && (nearest_city_dist < 9)) &&
           ((y2 = tile_is_ocean(x,y3), y2 == 0 &&
            (((y2 = tile_city_or_unit_owner(x,y3), y2 < 0 && (1 < y3)) &&
             (y3 < map.height - 2)))))) {
          y2 = tile_landmass((int)cities[city].x,(int)cities[city].y);
          iVar19 = tile_landmass(x,y3);
          if (y2 == iVar19) {
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
                    dlg_game_txt_with_unit(ADDR(0x632528, ((u8 *)&g.d_00632528)),unit);
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
              units[unit].field_0c = 'U';
              unit_stack_wake_by_role(unit,0xffff,0);
              unit_exhaust_moves(unit);
            }
            goto LAB_0053692c;
          }
        }
        y2 = tile_is_ocean(x,y3);
        if ((y2 != 0) && (y3 = tile_unit_owner(x,y3), 0 < y3)) {
          local_40 = local_18;
          goto LAB_00536859;
        }
      }
    }
    if (units[unit].orders != 11) {
      local_10 = 0;
      city2 = -1;
      y3 = tile_is_ocean(x2,y);
      if (y3 == 0) {
        local_1c = -1;
      }
      else {
        local_1c = tile_landmass(x2,y);
      }
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city].owner != '\0')) {
          if (-1 < local_1c) {
            uVar22 = tile_landmass((int)cities[city].x,(int)cities[city].y);
            y3 = landmass_borders_body(uVar22,local_1c);
            if (y3 == 0) goto LAB_00535741;
          }
          y3 = city_treasury_share(city);
          y2 = map_distance_diag(x2,y,(int)cities[city].x,(int)cities[city].y);
          y3 = (y3 + 0x32) / (y2 + 1);
          if (local_10 < y3) {
            city2 = city;
            local_10 = y3;
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
     (uVar22 = tile_improvements(x2,y), ((byte)uVar22 & 0x42) == 0x40)) {
    y2 = unit_stack_sum(unit,2);
    iVar19 = unit_stack_count_role(unit,6);
    if ((((1 < y2 - iVar19) || (y3 != 0)) && (unit_types[unit_type].role != 1)) ||
       ((bVar23 = nearest_city_dist == 0, y2 = unit_stack_sum(unit,2),
        (int)(bVar23 + 2 + (uint)(y3 == 0)) <= y2 &&
        ((char)unit_types[unit_type].defense <= (char)unit_types[unit_type].attack)))) goto LAB_005359af;
    units[unit].orders = 1;
    local_40 = 8;
  }
  else {
LAB_005359af:
    if (((-1 < city) && ((game.turn + unit & 3U) == 0)) &&
       ((y2 = tile_is_ocean(x2,y), y2 == 0 || (unit_types[unit_type].hold != '\0')))) {
      y2 = tile_landmass((int)cities[city].x,(int)cities[city].y);
      iVar19 = tile_landmass(x2,y);
      if ((y2 != iVar19) || (8 < nearest_city_dist)) {
        unit_destroy_redraw(unit,1);
        return 1;
      }
    }
    local_74 = -3;
    x3 = -3;
    if (-1 < city) {
      y2 = tile_landmass((int)cities[city].x,(int)cities[city].y);
      iVar19 = tile_landmass(x2,y);
      if ((y2 == iVar19) &&
         (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) {
        x3 = cities[city].x - x2;
        if ((game.rules & 0x8000) == 0) {
          local_80 = x3;
          if ((int)x3 < 1) {
            local_80 = ~x3 + 1;
          }
          if ((int)map.width >> 1 <= (int)local_80) {
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
            local_74 = -1;
          }
          else {
            local_74 = 0;
          }
        }
        else {
          local_74 = 1;
        }
      }
    }
    if (-1 < city) {
      if (cities[city].owner == civ2) {
        local_74 = -3;
        x3 = -3;
      }
      if (civs[cities[city].owner].num_cities < 2) {
        local_74 = -3;
        x3 = -3;
      }
      if (civs[cities[city].owner].gold < 100) {
        local_74 = -3;
        x3 = -3;
      }
    }
    if (x3 != -3) {
      units[unit].goto_x = cities[city].x;
      units[unit].goto_y = cities[city].y;
      uVar22 = unit_goto_next_dir(unit);
      units[unit].last_dir = (u8)uVar22;
    }
    if (4 < (char)unit_types[unit_type].role) {
      cVar5 = tile_terrain(x2,y);
      y2 = unit_stack_sum(unit,2);
      if (((1 < y2) && (cVar5 != '\n')) &&
         (y2 = unit_stack_count_role(unit,(int)(char)unit_types[unit_type].role), y2 < 2)) {
        local_40 = 8;
        goto LAB_00536859;
      }
      if (cVar5 == '\n') {
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
    local_10 = -999;
    for (local_18 = 0; local_18 < 8; local_18++) {
      x = map_wrap_x((char)(&dir_dx_table)[local_18] + x2);
      y2 = (char)(&dir_dy_table)[local_18] + y;
      iVar19 = map_in_bounds(x,y2);
      if (iVar19 != 0) {
        terrain = tile_terrain(x,y2);
        if ((unit_types[unit_type].domain == 2) == (terrain == 10)) {
          iVar19 = tile_unit_owner(x,y2);
          unit2 = tile_first_unit(x,y2);
          local_c = 0;
          if ((char)unit_types[unit_type].role < 5) {
            civ = tile_city_owner(x,y2);
            if ((civ < 0) || (civ2 == civ)) {
LAB_005364bc:
              iVar20 = tile_owner(x,y2);
              if (civ2 != iVar20) {
                local_c = 4;
              }
              uVar21 = tile_improvements(x,y2);
              if ((uVar21 & 0x40) == 0) {
                uVar21 = tile_improvements(x,y2);
                if ((uVar21 & 0xc) != 0) {
                  local_c += 6;
                }
              }
              else {
                local_c += 8;
              }
              iVar20 = rand_range(0,5);
              local_c += iVar20;
              if (unit2 < 0) {
LAB_005365f1:
                if ((((y3 == 0) || (unit_types[unit_type].role != '\0')) || (-1 < unit2)) ||
                   ((y2 = tile_in_enemy_zoc(x,y2,civ2), y2 == 0 ||
                    ((unit_types[units[unit].type].flags & 2) != 0)))) {
                  if ((char)units[unit].last_dir == local_18) {
                    local_c += 6;
                  }
                  if (x3 != -3) {
                    if ((char)(&dir_dx_table)[local_18] < 1) {
                      if ((char)(&dir_dx_table)[local_18] < '\0') {
                        local_84 = -1;
                      }
                      else {
                        local_84 = 0;
                      }
                    }
                    else {
                      local_84 = 1;
                    }
                    if (x3 == local_84) {
                      local_c += 2;
                    }
                  }
                  if (local_74 != -3) {
                    if ((char)(&dir_dy_table)[local_18] < 1) {
                      if ((char)(&dir_dy_table)[local_18] < '\0') {
                        local_88 = -1;
                      }
                      else {
                        local_88 = 0;
                      }
                    }
                    else {
                      local_88 = 1;
                    }
                    if (local_74 == local_88) {
                      local_c += 2;
                    }
                  }
                  goto LAB_0053673f;
                }
              }
              else if (iVar19 == civ2) {
                iVar19 = tile_is_ocean(x2,y);
                if (iVar19 != 0) {
                  local_c -= 0x14;
                  goto LAB_005365f1;
                }
              }
              else {
                iVar19 = tile_is_ocean(x2,y);
                if (iVar19 == 0) {
                  if (unit_type == 9) {
                    if ((char)unit_types[units[unit2].type].role < 5) goto LAB_00535e74;
                    local_c += 99;
                  }
                  else if (unit_types[units[unit2].type].role != 6) {
                    local_c += 99;
                  }
                  goto LAB_005365f1;
                }
              }
            }
            else {
              iVar20 = tile_is_ocean(x2,y);
              if (iVar20 == 0) {
                iVar20 = tile_unit_owner(x,y2);
                if (iVar20 < 0) {
                  iVar20 = civs[civ].gold / 2;
                  if (iVar20 < 0x33) {
                    iVar20 = 0x32;
                  }
                  local_54 = cities[city].size * 0x19;
                  if (local_54 <= iVar20) {
                    local_54 = iVar20;
                  }
                  if ((((game.power_rank[civ] == 7) && (200 < game.year)) &&
                      (4 < civs[civ].num_cities)) &&
                     (local_54 = (civs[civ].gold / 100) * 100, local_54 < 1000)) {
                    local_54 = civs[civ].gold + 1;
                  }
                  text_set_number_arg(0,local_54);
                  if (((game.multiplayer < 3) &&
                      (local_14 = (byte)civ,
                      (1 << (local_14 & 0x1f) & (uint)game.human_players) != 0)) &&
                     (local_54 <= civs[civ].gold)) {
                    city = city_at(x,y2);
                    text_set_string_arg(1,(iptr)&cities[city].name);
                    __chdir(&scenario_dir_path);
                    iVar20 = text_open_section(ADDR(0x632544, ((u8 *)&g.d_00632544)),ADDR(0x632538, ((u8 *)&g.d_00632538)));
                    if (iVar20 != 0) {
                      __chdir(&game_home_dir);
                      iVar20 = text_open_section(ADDR(0x632558, ((u8 *)&g.d_00632558)),ADDR(0x63254c, ((u8 *)&g.d_0063254c)));
                      if (iVar20 != 0) goto LAB_0053692c;
                    }
                    __chdir(&game_home_dir);
                    text_read_line(1);
                    iVar20 = _atoi(&text_buffer);
                    if (0 < iVar20) {
                      y5 = cities[city].y;
                      x4 = cities[city].x;
                      for (local_2c = 0; local_2c <= (y5 * 3 + x4 * 5) % iVar20;
                          local_2c = local_2c + 1) {
                        text_read_line(1);
                      }
                      text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
                      mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,civ);
                      if ((autoplay_active == 0) &&
                         (iVar20 = dlg_game_txt_with_unit(ADDR(0x632560, ((u8 *)&g.d_00632560)),unit), iVar20 != 0)) {
                        civs[civ].gold -= local_54;
                        status_draw_info(1);
                        for (local_2c = 0; local_2c < 0x14; local_2c++) {
                          x = map_wrap_x((int)cities[city].x +
                                              (int)(char)(&city_tile_dx_table)[local_2c]);
                          x2 = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[local_2c];
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
                if ((unit_type != 9) || (iVar20 = tile_unit_owner(x,y2), iVar20 < 0)) {
                  local_40 = local_18;
                  goto LAB_00536859;
                }
                if ((game.turn + unit & 7U) != 0) {
                  iVar20 = unit_stack_sum(unit,2);
                  if ((iVar20 < 2) && (units[unit].orders = 1, local_10 < 99)) {
                    local_10 = 99;
                    local_40 = 8;
                  }
                  goto LAB_005364bc;
                }
              }
            }
          }
          else {
            if (-1 < unit2) {
              if (iVar19 == civ2) {
                local_c = 99;
              }
              else {
                local_c = -99;
              }
            }
            city_find_nearest(x,y2,-1,0xffffffff,-1);
            uVar1 = terrain_types[terrain].move_cost;
            y2 = rand_range(0,3);
            local_c = local_c + (char)uVar1 + y2 + nearest_city_dist * 4;
LAB_0053673f:
            if (local_10 <= local_c) {
              local_10 = local_c;
              local_40 = local_18;
            }
          }
        }
      }
LAB_00535e74: ;
    }
    y3 = tile_city_owner(x2,y);
    if (((y3 < 0) || (y3 = unit_stack_sum(unit,2), 1 < y3)) || (0x62 < local_10)) {
      if ((((local_10 < 99) &&
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
      local_40 = 8;
    }
  }
LAB_00536859:
  if (local_40 == 8) {
    units[unit].last_dir = 0xff;
    unit_exhaust_moves(unit);
    if (((unit_types[unit_type].role == 1) ||
        (uVar22 = tile_improvements(x2,y), ((byte)uVar22 & 0x42) == 0x40)) &&
       (units[unit].orders = 1, (units[unit].flags & 0x100) != 0)) {
      units[unit].orders = 2;
    }
  }
  else {
    units[unit].orders = 27;
    uVar22 = map_wrap_x((char)(&dir_dx_table)[local_40] + x2);
    units[unit].goto_x = (i16)uVar22;
    units[unit].goto_y = (char)(&dir_dy_table)[local_40] + y4;
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
#undef local_88
#undef local_84
#undef local_80
#undef local_74
#undef x3
#undef city2
#undef city
#undef local_54
#undef local_40
#undef civ3
#undef local_2c
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 005369f3 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl ai_transports_raid_empty_city(iptr city)

{
  char civ2;
  short x;
  short y;
  int civ;
  int iVar5;
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
        iVar5 = unit_max_moves(unit);
        if (civ < iVar5) {
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
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl ai_continent_defense_quota(iptr civ,iptr param_2)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  local_c = (uint)civs[civ].continent_cities[param_2];
  local_8 = 3;
  do {
    uVar1 = local_c;
    if (4 < (int)local_c) {
      uVar1 = 5;
    }
    local_c -= uVar1;
    local_14 += local_8 * uVar1;
    local_8--;
  } while ((local_c != 0) && (0 < local_8));
  return local_14;
}
#undef local_14
#undef local_c
#undef local_8

/* 00536c4c auto */
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define unit2 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
i32 __cdecl ai_nuke_pick_target(iptr unit)

{
  uint uVar1;
  uint *puVar2;
  bool bVar3;
  iptr civ;
  iptr civ2;
  int y;
  iptr x;
  int iVar8;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (iptr)units[unit].owner;
  local_10 = -1;
  city2 = -1;
  city = 0;
  do {
    if (game.num_cities <= city) {
      y = 5 - civs[civ].num_cities;
      if (y < 1) {
        y = 0;
      }
      if ((10 - y <= local_10) &&
         (1 < civs[civ].units_active[units[unit].type])) {
        for (local_14 = 0; (int)local_14 < 8; local_14++) {
          x = map_wrap_x((int)(char)(&dir_dx_table)[local_14] + (int)cities[city2].x);
          y = (int)(char)(&dir_dy_table)[local_14] + (int)cities[city2].y;
          iVar8 = map_in_bounds(x,y);
          if (((iVar8 != 0) && (iVar8 = tile_city_owner(x,y), iVar8 < 0)) &&
             (iVar8 = tile_unit_owner(x,y), iVar8 < 0)) {
            unit_relocate(unit,x,y,1);
            units[unit].visibility = '\0';
            if (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0) {
              if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + cities[city2].owner * 4) & 2) == 0) {
                puVar2 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + cities[city2].owner * 4);
                *puVar2 = *puVar2 | 0x20000;
                puVar2 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + cities[city2].owner * 4);
                *puVar2 = *puVar2 & 0xffffffef;
                diplo_set_treaty_flags(civ,(int)cities[city2].owner,0x10000);
              }
              else {
                civs[cities[city2].owner].last_treaty_turn[civ] =
                     civs[cities[city2].owner].last_treaty_turn[civ] - 2;
              }
            }
            return local_14 ^ 4;
          }
        }
      }
      return 8;
    }
    if ((((((cities[city].id != 0) && (civ2 = (iptr)cities[city].owner, civ2 != civ)) &&
          (y = city_has_improvement(city,0x11), y == 0)) &&
         (4 < cities[city].size)) &&
        (((uVar1 = (uint)civs[civ2].military_strength * 2,
          uVar1 + (uint)civs[civ].military_strength * -3 != 0 &&
          (uint)civs[civ].military_strength * 3 <= uVar1 ||
          ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0)) ||
         ((civs[civ2].units_active[0x2d] == '\0' &&
          (uVar1 = (uint)civs[civ2].military_strength * 2,
          uVar1 - civs[civ].military_strength != 0 && civs[civ].military_strength <= uVar1))))))
       && ((civs[civ].treaties[civ2] & 0x104) == 0x100)) {
      local_8 = 0;
      for (local_14 = 0; (int)local_14 < 9; local_14++) {
        x = map_wrap_x((int)(char)(&dir_dx_table)[local_14] + (int)cities[city].x);
        y = (int)(char)(&dir_dy_table)[local_14] + (int)cities[city].y;
        iVar8 = map_in_bounds(x,y);
        if ((iVar8 != 0) && (iVar8 = tile_unit_owner(x,y), 0 < iVar8)) {
          if (iVar8 == civ) {
            local_8 -= 2;
          }
          else if ((civs[civ].treaties[iVar8] & 0x104) == 0x100) {
            for (unit2 = tile_first_unit(x,y); -1 < unit2;
                unit2 = unit_next_in_stack(unit2)) {
              local_8++;
            }
          }
          else {
            local_8 -= 99;
          }
        }
      }
      local_8 += ((int)cities[city].size >> 1);
      if (local_10 < local_8) {
        bVar3 = false;
        for (city3 = 0; city3 < game.num_cities; city3++) {
          if ((cities[city3].id != 0) && (cities[city3].owner == civ)) {
            y = map_distance((int)cities[city3].x,(int)cities[city3].y,
                                       (int)cities[city].x,(int)cities[city].y);
            iVar8 = unit_max_moves(unit);
            if (y <= iVar8 / (int)(uint)cosmic.road_move_mult) {
              bVar3 = true;
              break;
            }
          }
        }
        if (bVar3) {
          city2 = city;
          local_10 = local_8;
        }
      }
    }
    city++;
  } while( true );
}
#undef city2
#undef city
#undef unit2
#undef local_14
#undef local_10
#undef city3
#undef local_8

/* 00537331 auto */
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define x3 (*(int *)(frame_ + FRAME_OFF(4)))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(56)))
#define y3 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_20 (*(uptr *)(frame_ + FRAME_OFF(72)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(76)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(92)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(96)))
i32 __cdecl
ai_air_unit_orders(iptr unit,iptr unit_type,iptr x,iptr y,int param_5,iptr param_6,
            int param_7,iptr param_8,int param_9)

{
  byte civ2;
  char cVar2;
  u8 uVar3;
  u8 uVar4;
  u8 uVar5;
  short x4;
  short y4;
  ushort uVar8;
  bool bVar9;
  byte terrain;
  int civ;
  int iVar12;
  int y2;
  int iVar14;
  int iVar15;
  i32 uVar16;
  iptr x2;
  uint uVar18;
  iptr unit2;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = unit;
  civ2 = units[unit].owner;
  civ = (int)(char)civ2;
  if (unit_types[units[unit].type].range == '\0') {
    local_14 = unit_max_moves(unit);
    local_14 = local_14 * 2;
  }
  else {
    uVar3 = unit_types[units[unit].type].range;
    uVar4 = units[unit].counter;
    iVar12 = unit_max_moves(unit);
    local_14 = unit_moves_left(unit);
    local_14 = ((int)(char)uVar3 - ((char)uVar4 + 1)) * iVar12 + local_14;
  }
  local_14 = local_14 / (int)(uint)cosmic.road_move_mult;
  local_4c = 9999;
  for (city = 0; city < game.num_cities; city++) {
    if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
       (iVar12 = map_distance(*(i32 *)x,*(i32 *)y,
                                    (int)cities[city].x,(int)cities[city].y),
       iVar12 < local_4c)) {
      local_4c = iVar12;
    }
  }
  if (unit_types[units[unit].type].range != '\0') {
    if (unit_types[units[unit].type].range == 1) {
      if (units[unit].orders != 11) {
        iVar12 = unit_max_moves(unit);
        y2 = unit_moves_left(unit);
        if (((y2 <= iVar12 >> 1) && (local_14 < local_4c + 1)) && (local_4c <= local_14)) {
          units[unit].field_0c = 'H';
          unit_go_home(unit);
          return 0xffffffff;
        }
      }
    }
    else if (((int)(char)unit_types[units[unit].type].range / 2 <=
              (int)(char)units[unit].counter) && (local_4c <= local_14)) {
      units[unit].field_0c = 'H';
      unit_go_home(unit);
      return 0xffffffff;
    }
  }
  if (((unit_types[units[unit].type].flags & 0x1000) != 0) &&
     ((char)unit_types[unit_type].attack < 'c')) {
    local_10 = (int)(char)unit_types[units[unit].type].cost << 2;
    unit3 = -1;
    unit = 0;
    do {
      if (game.num_units <= unit) {
        if (-1 < unit3) {
          x4 = units[unit3].x;
          y4 = units[unit3].y;
          for (local_20 = 0; (int)local_20 < 8; local_20++) {
            x2 = map_wrap_x((int)(char)(&dir_dx_table)[local_20] + (int)x4);
            iVar12 = (int)(char)(&dir_dy_table)[local_20] + (int)y4;
            y2 = map_in_bounds(x2,iVar12);
            if ((y2 != 0) && (y2 = tile_city_or_unit_owner(x2,iVar12), y2 < 0)) {
              unit_relocate(unit2,x2,iVar12,1);
              units[unit2].visibility = '\0';
              *(iptr *)x = x2;
              *(int *)y = iVar12;
              return local_20 ^ 4;
            }
          }
        }
        iVar12 = unit_stack_sum(unit2,8);
        if (1 < iVar12) {
          for (city = 0; city < game.num_cities; city++) {
            if ((cities[city].id != 0) && (cities[city].owner == civ)) {
              x2 = tile_first_unit((int)cities[city].x,(int)cities[city].y);
              y2 = unit_stack_sum(x2,8);
              if (y2 < iVar12) {
                y2 = map_distance(*(i32 *)x,*(i32 *)y,
                                            (int)cities[city].x,(int)cities[city].y);
                iVar14 = unit_max_moves(unit2);
                if (y2 <= iVar14 / (int)(uint)cosmic.road_move_mult) {
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
          ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + units[unit].owner * 4) & 0x20) != 0)) &&
         (unit_types[units[unit].type].domain != 1)) {
        iVar12 = (int)units[unit].x;
        y2 = (int)units[unit].y;
        iVar14 = map_in_bounds(iVar12,y2);
        if (iVar14 != 0) {
          iVar14 = unit_max_moves(unit2);
          uVar18 = (uint)cosmic.road_move_mult;
          iVar15 = map_distance(*(i32 *)x,*(i32 *)y,iVar12,y2);
          if (iVar15 <= iVar14 / (int)uVar18) {
            local_8 = (int)(char)unit_types[units[unit].type].cost;
            uVar16 = tile_improvements(iVar12,y2);
            if ((((byte)uVar16 & 0x42) == 0x40) ||
               (iVar14 = tile_airbase_owner(iVar12,y2), iVar14 != 0)) {
              bVar9 = true;
            }
            else {
              bVar9 = false;
            }
            if ((bVar9) || (iVar14 = tile_city_owner(iVar12,y2), -1 < iVar14)) {
              if (!bVar9) {
                iVar14 = unit_stack_sum(unit,2);
                if (iVar14 == 1) {
                  local_8 = local_8 << 1;
                }
                for (local_20 = 0; (int)local_20 < 8; local_20++) {
                  x2 = map_wrap_x((char)(&dir_dx_table)[local_20] + iVar12);
                  cVar2 = (&dir_dy_table)[local_20];
                  iVar14 = map_in_bounds(x2,cVar2 + y2);
                  if ((iVar14 != 0) &&
                     (iVar14 = tile_unit_owner(x2,cVar2 + y2), iVar14 == civ)) {
                    local_8 = local_8 << 1;
                    break;
                  }
                }
              }
            }
            else {
              local_8 = unit_stack_sum(unit,0);
            }
            iVar14 = tile_is_ocean(iVar12,y2);
            if (iVar14 != 0) {
              local_8 = local_8 << 1;
            }
            uVar16 = tile_improvements(iVar12,y2);
            if (((byte)uVar16 & 0x42) == 0x40) {
              local_8 = local_8 << 1;
            }
            local_8 += (char)unit_types[units[unit].type].hold;
            if (local_10 <= local_8) {
              unit3 = unit;
              local_10 = local_8;
            }
          }
        }
      }
      unit++;
    } while( true );
  }
  if (param_5 == 3) {
    local_10 = 9999;
    local_50 = 9999;
    unit3 = -1;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((((units[unit].id != 0) && (units[unit].owner != civ)) &&
          ((*(byte *)&civs[civ].treaties[units[unit].owner] & 6) == 0)) &&
         (((1 << (civ2 & 0x1f) & (uint)units[unit].visibility) != 0 ||
          ((int)units[unit].owner == (uint)civ2)))) {
        if (unit_types[units[unit].type].domain == 1) {
LAB_00537ec2:
          iVar12 = map_distance(*(i32 *)x,*(i32 *)y,
                                      (int)units[unit].x,(int)units[unit].y);
          local_30 = iVar12 * 2;
          if (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0) {
            local_30 = local_30 >> 1;
          }
          if (unit_types[units[unit].type].range != '\0') {
            local_30--;
          }
          y2 = unit_stack_sum(unit,2);
          if (y2 == 1) {
            local_30--;
          }
          if (local_30 <= local_50) {
            local_50 = local_30;
            unit3 = unit;
            local_10 = iVar12;
          }
        }
        else {
          if (unit_types[units[unit].type].hold == '\0') {
            iVar12 = unit_stack_sum(unit,2);
          }
          else {
            iVar12 = unit_stack_sum(unit,5);
          }
          if (iVar12 < 2) {
            uVar8 = units[unit2].flags;
            uVar3 = unit_types[unit_type].attack;
            uVar4 = unit_types[unit_type].hit_points;
            uVar5 = unit_types[unit_type].firepower;
            local_1c = (int)(char)unit_types[units[unit].type].hit_points *
                       (int)(char)unit_types[units[unit].type].defense *
                       (int)(char)unit_types[units[unit].type].firepower *
                       (3 - (uint)((units[unit].flags & 0x2000) == 0));
            if ((unit_types[units[unit].type].hold != '\0') &&
               (iVar12 = unit_stack_sum(unit,2), iVar12 == 1)) {
              local_1c = local_1c * 2;
            }
            terrain = tile_terrain((int)units[unit].x,(int)units[unit].y);
            if ((local_1c * (char)terrain_types[terrain].defense >> 1) * 3 <=
                (int)((3 - (uint)((uVar8 & 0x2000) == 0)) * (int)(char)uVar3 * (int)(char)uVar4 *
                      (int)(char)uVar5 * 2)) goto LAB_00537ec2;
          }
        }
      }
    }
    if (-1 < unit3) {
      if ((local_10 <= local_14) || (local_14 < local_4c)) {
        if (((local_4c <= local_14 - local_10) && (local_10 == 1)) || (local_14 < local_4c)) {
          unit_set_goto(unit2,0x41,(int)units[unit3].x,(int)units[unit3].y);
          return 0xffffffff;
        }
        local_50 = 9999;
        for (local_20 = 0; (int)local_20 < 8; local_20++) {
          x2 = map_wrap_x((int)(char)(&dir_dx_table)[local_20] + (int)units[unit3].x);
          iVar12 = (int)(char)(&dir_dy_table)[local_20] + (int)units[unit3].y;
          y2 = map_in_bounds(x2,iVar12);
          if ((((y2 != 0) && (y2 = tile_city_owner(x2,iVar12), y2 < 0)) &&
              ((y2 = tile_unit_owner(x2,iVar12), y2 < 0 || (civ == y2)))) &&
             (y2 = map_distance(*(i32 *)x,*(i32 *)y,x2,
                                          iVar12), y2 <= local_10 - 1)) {
            nearest_city_dist = 9999;
            local_c = -1;
            for (city = 0; city < game.num_cities; city++) {
              if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
                 (y2 = map_distance(x2,iVar12,(int)cities[city].x,
                                              (int)cities[city].y), y2 < nearest_city_dist)) {
                local_c = city;
                nearest_city_dist = y2;
              }
            }
            if (local_c < 0) {
              nearest_city_dist = 0;
            }
            if (nearest_city_dist < local_50) {
              local_50 = nearest_city_dist;
            }
          }
        }
        if (local_10 + local_50 <= local_14) {
          unit_set_goto(unit2,0x41,(int)units[unit3].x,(int)units[unit3].y);
          return 0xffffffff;
        }
      }
      x3 = (int)units[unit3].x;
      y3 = (int)units[unit3].y;
      city = 0;
      do {
        if (game.num_cities <= city) {
          local_10 = 999;
          city2 = -1;
          for (city = 0; city < game.num_cities; city++) {
            if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
               ((iVar12 = map_distance(*(i32 *)x,*(i32 *)y,
                                             (int)cities[city].x,(int)cities[city].y),
                iVar12 <= local_14 &&
                (iVar12 = map_distance(x3,y3,(int)cities[city].x,
                                             (int)cities[city].y), iVar12 < local_10)))) {
              city2 = city;
              local_10 = iVar12;
            }
          }
          if (-1 < city2) {
            unit_set_goto(unit2,0x61,(int)cities[city2].x,(int)cities[city2].y);
            return 0xffffffff;
          }
          if (param_7 != 0) {
            unit_go_home(unit2);
            return 0xffffffff;
          }
          units[unit2].field_0c = 'h';
          return 8;
        }
        if (((cities[city].id != 0) &&
            (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) &&
           ((cities[city].flags & 0x10000) != 0)) {
          local_24 = map_distance(x3,y3,(int)cities[city].x,
                                        (int)cities[city].y);
          if ((*(byte *)&civs[civ].treaties[cities[city].owner] & 0x10) == 0) {
            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + cities[city].owner * 4) & 0x20) == 0) {
              local_24 = local_24 << 1;
            }
            if ((*(byte *)&civs[civ].treaties[cities[city].owner] & 4) != 0)
            goto LAB_00538277;
          }
          if (local_24 < local_10) {
            local_10 = local_24;
            x3 = (int)cities[city].x;
            y3 = (int)cities[city].y;
          }
        }
LAB_00538277:
        city++;
      } while( true );
    }
    if (param_7 != 0) {
      unit_go_home(unit2);
      return 0xffffffff;
    }
  }
  if (((param_5 == 0) && (unit_types[units[unit2].type].range != '\0')) &&
     ((char)unit_types[unit_type].attack < 'c')) {
    if (units[unit2].orders == 11) {
      if ((units[unit2].counter == '\0') && (param_9 != 0)) {
        *(i32 *)param_6 = 1;
        if (*(int *)param_6 != 0) {
          return 0xfffffffe;
        }
        return 0xffffffff;
      }
    }
    else {
      unit3 = -1;
      local_10 = -9999;
      if ((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) &&
         ((game.turn == 1 &&
          ((scenario_objective_civ == civ && (iVar12 = tile_unit_owner(0x2d,0x35), -1 < iVar12)))))) {
        unit_set_goto(unit2,0x42,0x2d,0x35);
        if (param_9 != 0) {
          *(i32 *)param_6 = 1;
        }
        if (*(int *)param_6 != 0) {
          return 0xfffffffe;
        }
        return 0xffffffff;
      }
      for (city = 0; city < game.num_cities; city++) {
        if (((cities[city].id != 0) && (cities[city].owner != civ)) &&
           ((*(byte *)&civs[civ].treaties[cities[city].owner] & 6) == 0)) {
          iVar12 = map_distance(*(i32 *)x,*(i32 *)y,
                                      (int)cities[city].x,(int)cities[city].y);
          y2 = unit_moves_left(unit2);
          if ((iVar12 <= y2 / (int)(uint)cosmic.road_move_mult) &&
             (iVar12 = tile_first_unit((int)cities[city].x,(int)cities[city].y),
             -1 < iVar12)) {
            cVar2 = cities[city].size;
            iVar12 = unit_stack_sum(iVar12,2);
            local_8 = cVar2 * 10 + iVar12 * -0x19;
            iVar12 = tile_landmass((int)cities[city].x,(int)cities[city].y);
            if (iVar12 == param_8) {
              local_8 += 0x28;
            }
            for (local_20 = 0; (int)local_20 < 8; local_20++) {
              x2 = map_wrap_x((int)cities[city].x + (int)(char)(&dir_dx_table)[local_20]);
              iVar12 = (int)cities[city].y + (int)(char)(&dir_dy_table)[local_20];
              y2 = map_in_bounds(x2,iVar12);
              if ((y2 != 0) && (iVar12 = tile_unit_owner(x2,iVar12), iVar12 == civ)) {
                local_8 += 0x3c;
              }
            }
            if (local_10 <= local_8) {
              local_10 = local_8;
              unit3 = city;
            }
          }
        }
      }
      if (-1 < unit3) {
        unit_set_goto(unit2,0x42,(int)cities[unit3].x,(int)cities[unit3].y);
        if (param_9 != 0) {
          *(i32 *)param_6 = 1;
        }
        if (*(int *)param_6 != 0) {
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
#undef local_50
#undef local_4c
#undef city
#undef local_30
#undef y3
#undef local_24
#undef local_20
#undef local_1c
#undef city2
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00538a29 auto */
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_188 (*(int *)(frame_ + FRAME_OFF(0)))
#define x4 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_170 (*(uint *)(frame_ + FRAME_OFF(24)))
#define local_16c (*(int *)(frame_ + FRAME_OFF(28)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(32)))
#define city6 (*(uptr *)(frame_ + FRAME_OFF(40)))
#define local_158 (*(int *)(frame_ + FRAME_OFF(48)))
#define civ4 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_144 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_140 (*(int *)(frame_ + FRAME_OFF(72)))
#define city (*(uptr *)(frame_ + FRAME_OFF(84)))
#define local_11c (*(uptr *)(frame_ + FRAME_OFF(108)))
#define local_118 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_114 (*(int *)(frame_ + FRAME_OFF(116)))
#define local_110 (*(uptr *)(frame_ + FRAME_OFF(120)))
#define y4 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_104 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_fc (*(int *)(frame_ + FRAME_OFF(140)))
#define local_f4 (*(int *)(frame_ + FRAME_OFF(148)))
#define local_f0 (*(int *)(frame_ + FRAME_OFF(152)))
#define y3 (*(int *)(frame_ + FRAME_OFF(160)))
#define local_e4 (*(uint *)(frame_ + FRAME_OFF(164)))
#define local_e0 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_dc (*(int *)(frame_ + FRAME_OFF(172)))
#define local_d8 (*(uint *)(frame_ + FRAME_OFF(176)))
#define x2 (*(int *)(frame_ + FRAME_OFF(180)))
#define x3 (*(iptr *)(frame_ + FRAME_OFF(184)))
#define unit4 (*(uptr *)(frame_ + FRAME_OFF(188)))
#define local_c8 (*(uptr *)(frame_ + FRAME_OFF(192)))
#define local_c4 (*(uint *)(frame_ + FRAME_OFF(196)))
#define local_c0 (*(i32 *)(frame_ + FRAME_OFF(200)))
#define local_bc (*(uint *)(frame_ + FRAME_OFF(204)))
#define local_b8 (*(int *)(frame_ + FRAME_OFF(208)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(212)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(216)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(220)))
#define local_a8 (*(uint *)(frame_ + FRAME_OFF(224)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(228)))
#define local_a0 (*(u32 *)(frame_ + FRAME_OFF(232)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(236)))
#define unit5 (*(iptr *)(frame_ + FRAME_OFF(240)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(244)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(248)))
#define x6 (*(int *)(frame_ + FRAME_OFF(252)))
#define city4 (*(uptr *)(frame_ + FRAME_OFF(256)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(260)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(264)))
#define local_7c (*(uptr *)(frame_ + FRAME_OFF(268)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(272)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(276)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(280)))
#define local_6c (*(uint *)(frame_ + FRAME_OFF(284)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(292)))
#define local_60 (*(uptr *)(frame_ + FRAME_OFF(296)))
#define civ3 (*(uptr *)(frame_ + FRAME_OFF(300)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(304)))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(308)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(312)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(316)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(320)))
#define city5 (*(uptr *)(frame_ + FRAME_OFF(324)))
#define city2 (*(uptr *)(frame_ + FRAME_OFF(328)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(332)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(336)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(340)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(344)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(348)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(352)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(356)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(360)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(364)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(368)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(372)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(376)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(380)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(384)))
i32 __cdecl ai_unit_choose_orders(void)

{
  uint *puVar1;
  u8 uVar2;
  ushort uVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  byte bVar7;
  uptr civ;
  i32 uVar10;
  iptr iVar11;
  iptr iVar12;
  iptr iVar14;
  int city7;
  uptr city3;
  uptr uVar15;
  iptr iVar13;
  iptr x;
  iptr x5;
  int y;
  uptr uVar17;
  uptr uVar18;
  byte bVar8;
  uint terrain;
  byte *pbVar25;
  uptr uVar16;
  int iVar26;
  int iVar27;
  uptr unit_type;
  uint uVar28;
  bool bVar29;
  bool bVar30;
  bool bVar31;
  bool bVar32;
  i32 uVar33;
  iptr unit2;
  i8 frame_[FRAME_OFF(392)] __attribute__((aligned(8)));  /* original stack frame */
  local_9c = 0x108; local_11c = 0x64a8c19c; local_70 = 0x3bd; local_38 = 0; local_16c = 4;  /* stale stack the original reads (FRAME_PRESETS) */
  
  local_104 = -1;
  local_58 = -1;
  bVar30 = false;
  bVar29 = false;
  local_94 = 0;
  local_90 = 0;
  bVar5 = false;
  local_a4 = 0;
  bVar4 = false;
  local_20 = 0;
  local_48 = 0;
  local_b4 = 0;
  unit = (iptr)game.active_unit;
  bVar8 = units[unit].owner;
  civ = (uptr)(char)bVar8;
  if (civ == 0) {
    uVar10 = ai_barbarian_unit_move();
    return uVar10;
  }
  if ((3 < units[unit].orders) && (units[unit].orders < '\n')) goto LAB_005436c1;
  x2 = (int)units[unit].x;
  y3 = (int)units[unit].y;
  unit_type = (uptr)units[unit].type;
  local_c8 = 8;
  iVar27 = map_in_bounds(x2,y3);
  if (iVar27 == 0) {
    unit_set_sleep(unit);
    goto LAB_005436c1;
  }
  local_158 = tile_in_enemy_zoc(x2,y3,civ);
  city4 = city_find_nearest(x2,y3,-1,0xffffffff,-1);
  iVar27 = nearest_city_dist;
  if (-1 < (int)city4) {
    local_104 = tile_land_landmass((int)cities[city4].x,(int)cities[city4].y);
  }
  city2 = city_find_nearest(x2,y3,civ,0xffffffff,-1);
  local_3c = nearest_city_dist;
  if (-1 < (int)city2) {
    local_58 = tile_land_landmass((int)cities[city2].x,(int)cities[city2].y);
  }
  bVar7 = tile_terrain(x2,y3);
  terrain2 = (uptr)bVar7;
  iVar11 = tile_landmass(x2,y3);
  uVar10 = tile_improvements(x2,y3);
  local_bc = (uint)(((byte)uVar10 & 0x42) == 0x40);
  if (((8 < local_3c) || (iVar11 != local_58)) &&
     ((1 << (bVar8 & 0x1f) & (uint)game.human_players) == 0)) {
    units[unit].flags = units[unit].flags & 0xfdff;
  }
  local_e4 = ai_unit_role(unit);
  local_a0 = unit_types[units[unit].type].flags;
  local_144 = (int)(char)unit_types[units[unit].type].domain;
  uVar28 = (uint)civs[civ].continent_policy[iVar11];
  if (((local_158 != 0) && (adjacent_foreign_civ != 0)) &&
     ((city2 == city4 && ((*(byte *)&civs[civ].treaties[adjacent_foreign_civ] & 4) != 0))
     )) {
    civ_adjust_attitude(civ,adjacent_foreign_civ,1);
    if ((((1 << ((byte)adjacent_foreign_civ & 0x1f) & (uint)game.human_players) != 0) &&
        (2 < game.difficulty)) &&
       ((iVar12 = civ_get_attitude(civ,adjacent_foreign_civ), 0x3c < iVar12 &&
        ((game.power_rank[civ] < game.power_rank[adjacent_foreign_civ] &&
         (iVar14 = rand_range(0,3), iVar14 == 0)))))) {
      puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + adjacent_foreign_civ * 4);
      *puVar1 = *puVar1 | 0x20;
    }
  }
  city3 = city4;
  if (((((iVar27 == 1) && (city2 != city4)) && (local_144 == 0)) &&
      (((char)unit_types[units[unit].type].role < 6 &&
       (city7 = tile_unit_owner((int)cities[city4].x,(int)cities[city4].y), city7 < 0)))) &&
     ((*(byte *)&civs[civ].treaties[cities[city3].owner] & 0xe) == 0)) {
    units[unit].orders = -1;
    local_158 = 1;
    adjacent_foreign_civ = (iptr)cities[city3].owner;
    bVar4 = true;
  }
  local_d8 = (uint)(units[unit].damage != '\0');
  if ((int)(char)unit_types[unit_type].hit_points >> 2 < (int)(uint)units[unit].damage) {
    local_d8 = 2;
  }
  if ((int)(char)unit_types[unit_type].hit_points >> 1 < (int)(uint)units[unit].damage) {
    local_d8 = 3;
  }
  if ((unit_types[units[unit].type].hold != '\0') &&
     (city7 = unit_moves_left(unit), city7 == 0)) {
    local_20 = 1;
    goto LAB_0053be12;
  }
  if (local_d8 != 0) {
    local_f0 = 0;
    civ2 = tile_radius_civ(x2,y3);
    if ((((0 < (int)civ2) && ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0)) &&
        ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0)) &&
       ((int)((uint)civs[civ2].reputation - (int)civs[civ].field_48[civ2])
        < 6)) {
      local_f0 = 1;
    }
    if (iVar27 != 0) {
      if (iVar27 == 1) {
        if (city4 == city2) {
          unit_set_goto(unit,100,(int)cities[city4].x,(int)cities[city4].y);
          goto LAB_005436c1;
        }
        if (bVar4) {
          local_d8 = 0;
        }
      }
      goto LAB_005392a6;
    }
    local_90 = 1;
    local_48 = 1;
    goto LAB_0053b8f0;
  }
LAB_005392a6:
  if ((((((local_d8 == 0) || (units[unit].moves_used != '\0')) ||
        ((local_f0 != 0 || ((local_144 != 1 || (unit_types[units[unit].type].range != '\0')))))
        ) || (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 != 0)) ||
      ((local_3c < 0xd || (units[unit].visibility != '\0')))) ||
     (((local_d8 != 2 && ((units[unit].flags & 8) == 0)) &&
      ((((local_d8 != 3 || (local_3c == 0)) || (local_3c < 0x18)) || (iVar27 < 9)))))) {
    units[unit].flags = units[unit].flags & 0xfff7;
    if (((((local_d8 != 0) && (units[unit].moves_used == '\0')) && (local_f0 == 0)) &&
        ((local_144 == 0 ||
         (((local_144 == 2 && (city7 = unit_stack_sum(unit,2), city7 < 2)) &&
          ((local_d8 == 1 || ((int)(uint)units[unit].damage >> 1 <= local_3c / 2)))))))) &&
       (((local_144 != 2 || ((game.human_players & units[unit].visibility) == 0)) &&
        ((local_d8 == 3 ||
         (((int)(char)unit_types[units[unit].type].role != uVar28 || (local_144 == 2)))))))) {
      if (local_144 == 0) {
        bVar31 = local_158 == 0;
      }
      else {
        city7 = tile_adjacent_nonallied_unit(x2,y3,civ);
        if (city7 == 0) {
          bVar31 = true;
        }
        else {
          bVar31 = false;
        }
      }
      if (bVar31) {
        units[unit].field_0c = 'd';
        local_c8 = 8;
        city3 = local_c8;
        goto LAB_005435ca;
      }
    }
    if (((local_d8 == 2) && (local_144 == 2)) &&
       ((local_e4 == 2 ||
        ((local_e4 == 4 && (city7 = unit_stack_sum(unit,2), city7 < 2)))))) {
      unit_go_home(unit);
      city7 = unit_moves_left(unit);
      if (city7 == 0) goto LAB_005436c1;
      if (units[unit].orders == 11) {
        local_a4 = 1;
        goto LAB_005414d7;
      }
    }
    if (local_d8 == 3) {
      units[unit].field_0c = 'D';
      if (((local_144 == 0) && ((int)local_e4 < 2)) &&
         (((((units[unit].flags & 0x100) != 0 ||
            (2 < (char)terrain_types[terrain2].defense)) &&
           ((((local_e4 == 1 ||
              (city7 = unit_max_moves(unit), city7 <= (int)(uint)cosmic.road_move_mult))
             || (local_158 == 0)) || (8 < local_3c)))) && (local_f0 == 0)))) {
        local_c8 = 8;
        city3 = local_c8;
      }
      else {
        if (((local_144 != 0) || (local_bc == 0)) || (local_f0 != 0)) {
          if (((local_e4 != 4) || (city7 = unit_stack_sum(unit,2), city7 < 2)) &&
             ((unit_go_home(unit), units[unit].orders == 11 ||
              (city7 = unit_moves_left(unit), city7 == 0)))) goto LAB_005436c1;
          goto LAB_005397e7;
        }
        local_c8 = 8;
        city3 = local_c8;
      }
    }
    else {
LAB_005397e7:
      if (((((game.game_flags & 0x80) == 0) || (((int)(short)scenario_flags & 0x8000U) == 0)) ||
          (civ != 1)) ||
         (((((*(i8 *)((char *)&civs[1].treaties[3] + 1)) & 0x20) != 0 || (5 < game.turn)) ||
          (0x4f < units[unit].x)))) {
        if (((local_144 == 0) && (local_3c == 0)) &&
           (((units[unit].flags & 0x100) == 0 &&
            (((cities[city2].flags & 0x200) != 0 && (uVar28 != local_e4)))))) {
          bVar5 = true;
        }
        else {
          if (local_144 == 1) {
            unit4 = ai_air_unit_orders(unit,unit_type,(iptr)&x2,(iptr)&y3,local_e4,
                                          (iptr)&local_a4,local_3c,iVar11,local_158);
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
          if (local_e4 == 6) {
            if ((((units[unit].orders == 11) &&
                 (city7 = city_at((int)units[unit].goto_x,
                                              (int)units[unit].goto_y), -1 < city7)) &&
                ((int)cities[city7].owner != civ)) &&
               ((*(byte *)&civs[civ].treaties[cities[city7].owner] & 0xe) == 0)) {
              local_a4 = 1;
            }
            else {
              city7 = tile_is_ocean(x2,y3);
              if (city7 == 0) {
                local_24 = ai_spaceship_race_behind(civ);
                local_38 = -999;
                city6 = 0xffffffff;
                for (city = 0; (int)city < (int)game.num_cities; city = city + 1
                    ) {
                  if (cities[city].id != 0) {
                    city7 = tile_landmass((int)cities[city].x,(int)cities[city].y);
                    y = tile_is_ocean(x2,y3);
                    if (y == 0) {
                      if (city7 == iVar11) {
LAB_00539cb3:
                        civ2 = (uptr)cities[city].owner;
                        local_70 = map_distance_diag(x2,y3,(int)cities[city].x,
                                                      (int)cities[city].y);
                        if (((uint)(byte)units[unit].home_city % 3 != (int)city % 3) &&
                           (terrain = tile_improvements(x2,y3),
                           (int)(((terrain & 0x10) >> 4) + 3) < local_70)) {
                          local_70 += 8;
                        }
                        if (civ2 == civ) {
                          local_18 = 99 - local_70;
                        }
                        else {
                          local_18 = 100;
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
                                     (civs[civ].continent_military[iVar11] <
                                      civs[civ2].continent_attack[iVar11])) &&
                                    (*(char *)&civs[civ].continent_cities[iVar11] != '\0')))))))))))
                               ) goto LAB_00539b29;
                            local_18 = local_18 / 2;
                          }
                          if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) {
                            city7 = civ_get_attitude(civ,civ2);
                            local_18 += city7;
                          }
                          else {
                            local_18 += 100;
                          }
                          local_18 = local_18 / (local_70 + 1);
                          if ((cities[city].flags & 8) != 0) {
                            local_18 = local_18 / 2;
                            if (civs[civ].num_advances + 6 < (uint)civs[civ2].num_advances) {
                              local_18 = local_18 / 2;
                            }
                            if (local_24 != 0) {
                              local_18 = 1;
                            }
                          }
                          local_18 += 100;
                        }
                        if (local_38 < local_18) {
                          local_38 = local_18;
                          city6 = city;
                        }
                      }
                    }
                    else {
                      local_c4 = 0;
                      for (local_60 = 0; (int)local_60 < 8; local_60++) {
                        x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
                        y2 = (char)(&dir_dy_table)[local_60] + y3;
                        y = map_in_bounds(x,y2);
                        if (((y != 0) && (y = tile_is_ocean(x,y2), y == 0)
                            ) && (y = tile_landmass(x,y2), y == city7)) {
                          local_c4 = 1;
                          break;
                        }
                      }
                      if (local_c4 != 0) goto LAB_00539cb3;
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
                local_a4 = 1;
                if ((units[unit].orders != 11) || ((int)cities[city6].owner != civ)) {
                  unit_set_goto(unit,0x53,(int)cities[city6].x,
                                     (int)cities[city6].y);
                }
              }
            }
            goto LAB_005414d7;
          }
          if (local_e4 == 7) {
            if (units[unit].orders == 11) goto LAB_005436c1;
            city7 = tile_is_ocean(x2,y3);
            if (city7 != 0) {
              city6 = 0xffffffff;
              local_38 = 0;
              for (local_60 = 0; (int)local_60 < 8; local_60++) {
                x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
                y2 = (char)(&dir_dy_table)[local_60] + y3;
                city7 = map_in_bounds(x,y2);
                if (((city7 != 0) && (city7 = tile_is_ocean(x,y2), city7 == 0)) &&
                   (city7 = tile_landmass(x,y2),
                   *(char *)&civs[civ].continent_flags[city7] != '\0')) {
                  local_18 = 0;
                  for (civ2 = 1; (int)civ2 < 8; civ2++) {
                    if (civ2 == civ) {
                      city7 = (int)(civs[civ].continent_city_size[iVar11] + 1) >> 1;
                    }
                    else {
                      city7 = (uint)civs[civ].continent_city_size[iVar11] * 2;
                    }
                    local_18 += city7;
                  }
                  if (local_38 < local_18) {
                    local_38 = local_18;
                    city6 = local_60;
                  }
                }
              }
              if (-1 < (int)city6) {
                units[unit].field_0c = 't';
                local_c8 = city6;
                city3 = local_c8;
                goto LAB_005435ca;
              }
            }
            local_38 = 0;
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
                 city7 == iVar11)) {
                local_c4 = 1;
                for (local_60 = 0; (int)local_60 < (int)(char)cities[city5].trade_routes;
                    local_60 = local_60 + 1) {
                  if ((int)cities[city5].route_partner[local_60] == city) {
                    local_c4 = 0;
                  }
                }
                city7 = map_distance_diag((int)cities[city].x,(int)cities[city].y,
                                            (int)cities[city5].x,(int)cities[city5].y);
                local_70 = (((int)cities[city5].base_trade + (int)cities[city].base_trade) *
                           city7) / 0x18;
                if ((int)cities[city].owner == civ) {
                  local_70 = local_70 / 2;
                }
                else {
                  uVar33 = 100;
                  uVar10 = 0;
                  x = civ_get_attitude(civ,(int)cities[city].owner);
                  unit4 = int_clamp(x,uVar10,uVar33);
                  local_70 = (int)((200 - unit4) * local_70) / 100;
                }
                if (local_c4 == 0) {
                  local_70 = local_70 / 2;
                }
                local_70 = ((5 - (char)cities[city].trade_routes) * local_70) / 5;
                if ((((-1 < (int)city4) && (city2 != city4)) && (iVar11 == local_104)) &&
                   ((cities[city].owner != cities[city4].owner &&
                    (local_70 = local_70 / 3,
                    ((uint)game.human_players & 1 << (cities[city4].owner & 0x1fU)) != 0)))) {
                  local_70 = local_70 / 2;
                }
                if (local_38 < local_70) {
                  local_38 = local_70;
                  city6 = city;
                }
              }
            }
            if (-1 < (int)city6) {
              unit_set_goto(unit,99,(int)cities[city6].x,(int)cities[city6].y);
              goto LAB_005436c1;
            }
            if (units[unit].home_city != -1) {
              bVar7 = units[unit].home_city;
              city7 = tile_landmass((int)cities[bVar7].x,(int)cities[bVar7].y);
              if (city7 == iVar11) {
                unit_set_goto(unit,99,(int)cities[bVar7].x,(int)cities[bVar7].y);
                goto LAB_005436c1;
              }
            }
          }
          bVar29 = local_e4 == 5;
          bVar30 = unit_types[units[unit].type].role == 5;
          local_38 = tile_owner_or_fertility(x2,y3);
          if (((iVar27 < 4) && (iVar11 == local_104)) && (7 < local_38)) {
            local_38 = 8;
          }
          city7 = tile_is_ocean(x2,y3);
          if (city7 != 0) {
            local_38 = 0;
          }
          if ((((bVar29) &&
               (civ_clear_standing_goals_near(civ,5,x2,y3,0), civs[civ].num_cities == 0)) &&
              (game.turn == 1)) &&
             (((start_x[civs[civ].tribe] == x2 && (start_y[civs[civ].tribe] == y3))
              && (7 < local_38)))) {
            unit_found_city(unit,-1,0);
            return 1;
          }
          city = city4;
          if (((local_38 != 0) && (((int)local_e4 < 2 || (bVar30)))) && (!bVar4)) {
            local_c8 = 0xffffffff;
            if (bVar29) {
              local_e0 = 0x14;
            }
            else {
              local_e0 = 8;
            }
            for (local_60 = 0; (int)local_60 < local_e0; local_60++) {
              x = map_wrap_x((char)(&city_tile_dx_table)[local_60] + x2);
              y2 = (char)(&city_tile_dy_table)[local_60] + y3;
              city7 = map_in_bounds(x,y2);
              if (((city7 != 0) && (city7 = tile_is_ocean(x,y2), city7 == 0)) &&
                 (city7 = tile_landmass(x,y2), city7 == iVar11)) {
                local_18 = tile_owner_or_fertility(x,y2);
                if (local_38 < local_18) {
                  local_c8 = local_60;
                  local_38 = local_18;
                }
                city7 = tile_has_hut(x,y2);
                if (((city7 != 0) && ((int)local_e4 < 2)) && ((int)local_60 < 8)) {
                  local_c8 = local_60;
                  units[unit].field_0c = 'U';
                  city3 = local_c8;
                  goto LAB_005435ca;
                }
              }
            }
            if (((7 < local_38) && (local_158 == 0)) &&
               (((0xf - iVar27 <= local_38 ||
                 (((bVar29 && ((int)local_c8 < 0)) &&
                  (*(char *)&civs[civ].continent_cities[iVar11] == '\0')))) ||
                (((bVar29 && ((int)local_c8 < 0)) &&
                 (units[unit].field_0e = units[unit].field_0e + 1,
                 4 < (char)units[unit].field_0e)))))) {
              if (bVar29) {
                if ((int)local_c8 < 0) {
                  unit_found_city(unit,-1,0);
                  return 1;
                }
                units[unit].field_0c = '2';
                city3 = local_c8;
                if ((int)local_c8 < 8) goto LAB_005435ca;
                city7 = (char)(&city_tile_dy_table)[local_c8] + y3;
                uVar10 = map_wrap_x((char)(&city_tile_dx_table)[local_c8] + x2);
                unit_set_goto(unit,0x32,uVar10,city7);
              }
              else if ((-1 < (int)local_c8) && ((int)local_c8 < 8)) {
                y = 2;
                uVar33 = 5;
                city7 = (char)(&city_tile_dy_table)[local_c8] + y3;
                uVar10 = map_wrap_x((char)(&city_tile_dx_table)[local_c8] + x2);
                civ_add_standing_goal(civ,uVar10,city7,uVar33,y);
              }
            }
          }
          if (((((((bVar29) && (game.difficulty != '\0')) && (-1 < (int)city4)) &&
                ((city = city4,
                 ((uint)game.human_players & 1 << (cities[city4].owner & 0x1fU)) != 0 &&
                 (local_158 == 0)))) && (1 < iVar27)) &&
              ((civs[civ].num_advances < civs[cities[city4].owner].num_advances &&
               (local_18 = tile_get_fertility(x2,y3), 8 < local_18)))) &&
             (0xe - iVar27 <= local_18)) {
            unit_found_city(unit,-1,0);
            return 1;
          }
          if ((unit_types[units[unit].type].flags & 0x100) != 0) {
            if (local_3c == 0) {
              if ((units[unit].moves_used == '\0') && (units[unit].orders != 11)) {
                local_38 = 0;
                for (city = 0; (int)city < (int)game.num_cities; city = city + 1
                    ) {
                  if ((((cities[city].id != 0) && ((int)cities[city].owner != civ)) &&
                      ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + cities[city].owner * 4) & 0x20) !=
                       0)) && (city7 = map_distance(x2,y3,
                                                           (int)cities[city].x,
                                                           (int)cities[city].y),
                              city7 <= (int)(uint)cosmic.paradrop_range)) {
                    city7 = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
                    if ((city7 < 0) && (local_38 < cities[city].size + 999)) {
                      local_38 = cities[city].size + 999;
                      x6 = (int)cities[city].x;
                      y4 = (int)cities[city].y;
                    }
                    if (0 < local_38) {
                      local_38 = 0;
                      city6 = 0xffffffff;
                      for (local_60 = 9; -1 < (int)local_60; local_60--) {
                        x = map_wrap_x((char)(&dir_dx_table)[local_60] + x6);
                        y2 = (char)(&dir_dy_table)[local_60] + y4;
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
                            local_18 = 0;
                            if (local_60 == 8) {
                              local_18 = 500;
                            }
                            uVar10 = tile_improvements(x,y2);
                            if (((byte)uVar10 & 0x42) == 0x40) {
                              local_18 += 0x32;
                            }
                            bVar7 = tile_terrain(x,y2);
                            local_18 += (char)terrain_types[bVar7].defense * 3;
                            city7 = map_distance(x2,y3,x,y2);
                            local_18 += city7;
                            if (local_38 < local_18) {
                              city6 = local_60;
                              local_38 = local_18;
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
                local_90 = 1;
                goto LAB_005414d7;
              }
            }
            else {
              if (((city2 == city4) && (iVar11 == local_58)) &&
                 (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 == 0)) {
                unit_set_goto(unit,99,(int)cities[city].x,(int)cities[city].y);
                goto LAB_005436c1;
              }
              if ((local_bc != 0) && (city7 = unit_stack_sum(unit,2), city7 == 1)) {
                units[unit].field_0c = 'F';
                local_c8 = 8;
                goto LAB_005436c1;
              }
            }
          }
        }
        if ((unit_type == 9) && (units[unit].moves_used == '\0')) {
          if (local_158 == 0) {
            if ((char)units[unit].counter < 15) {
              units[unit].counter++;
            }
          }
          else if (units[unit].counter != '\0') {
            units[unit].counter += 0xff;
          }
          if ('\t' < (char)units[unit].counter) {
            local_bc = 0;
          }
          if (local_bc != 0) {
            local_38 = 9999;
            city6 = 0xffffffff;
            for (city = 0; (int)city < (int)game.num_cities; city++) {
              if ((((cities[city].id != 0) && (city != city4)) &&
                  (city7 = tile_landmass((int)cities[city].x,(int)cities[city].y),
                  city7 == iVar11)) &&
                 ((local_70 = map_distance_diag(x2,y3,(int)cities[city].x,
                                                 (int)cities[city].y), local_70 < local_38 ||
                  ((local_70 == local_38 && ((int)cities[city].owner == civ)))))) {
                city6 = city;
                local_38 = local_70;
              }
            }
            if ((city2 != city4) &&
               (((int)city6 < 0 || ((int)cities[city6].owner != civ)))) {
              local_bc = 0;
            }
          }
        }
        if ((((local_bc == 0) || (unit4 = tile_radius_civ(x2,y3), (int)unit4 < 1))
            || (unit4 == civ)) ||
           ((((*(byte *)&civs[civ].treaties[unit4] & 4) != 0 &&
             ((int)((uint)civs[unit4].reputation -
                   (int)civs[civ].field_48[unit4]) < 7)) &&
            (((*(byte *)&civs[civ].treaties[unit4] & 8) != 0 || (2 < local_3c)))))) {
LAB_0053b8f0:
          if (local_3c == 0) {
            local_b0 = unit_stack_count_role(unit,1);
            if (((local_e4 == 1) && (1 < local_b0)) || (local_e4 == 4)) {
              city7 = tile_zoc_unit_adjacent(x2,y3,civ);
              if (city7 == 0) {
                local_30 = 4;
              }
              else {
                local_30 = 3;
              }
              city7 = city_has_improvement(city2,1);
              if (city7 == 0) {
                if (uVar28 == 5) {
                  local_30++;
                }
              }
              else {
                local_30--;
              }
              uVar15 = (int)cities[city2].size / local_30 + 1;
              city7 = city_has_improvement(city2,1);
              local_11c = uVar15;
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
                local_11c = unit4;
                if ((int)unit4 <= (int)uVar15) {
                  local_11c = uVar15;
                }
              }
            }
            if (local_e4 == 1) {
              if (local_b0 < 2) {
                local_48 = 1;
              }
              else {
                local_9c = unit_stack_best_defender(unit,-1);
                if (unit == local_9c) {
                  local_48 = 1;
                }
                else {
                  if (local_b0 < (int)local_11c) {
                    civ_add_ai_goal(civ,x2,y3,1,3);
                  }
                  if ((int)local_11c < local_b0) {
                    unit4 = (uptr)units[unit].orders;
                    units[unit].orders = 2;
                    city7 = unit_stack_best_defender(unit,-1);
                    if ((city7 == unit) &&
                       (city7 = unit_stack_sum(unit,4), city7 <= (int)local_11c)) {
                      units[unit].orders = (i8)unit4;
                      local_48 = 1;
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
                    local_48 = 1;
                  }
                }
              }
            }
            else {
              city7 = unit_stack_sum(unit,2);
              if ((city7 < 2) &&
                 ((civ_add_ai_goal(civ,x2,y3,1,5), !bVar30 ||
                  (city7 = tile_zoc_unit_adjacent(x2,y3,civ), city7 != 0)))) {
                local_48 = 1;
              }
            }
          }
          if (local_48 == 0) {
            if (bVar5) {
              local_90 = 1;
            }
            if (local_90 == 0) {
LAB_0053be12:
              do {
                if (local_144 == 2) {
                  local_c = 0;
                  local_34 = 0;
                  local_9c = 0;
                  unit5 = unit;
                  for (unit = unit_stack_first(unit); unit2 = unit5, -1 < unit;
                      unit = unit_next_in_stack(unit)) {
                    if (unit_types[units[unit].type].domain == '\0') {
                      if (units[unit].orders == 2) {
                        if (((local_3c == 0) && (local_9c = local_9c + 1, (int)local_11c < local_9c)
                            ) && ((uVar28 == 4 || (local_34 == 0)))) {
                          units[unit].orders = -1;
                          local_c = local_c | 1 << (unit_types[units[unit].type].role & 0x1f);
                          local_34++;
                        }
                      }
                      else if ((unit_types[units[unit].type].role == 1) &&
                              (local_9c < (int)local_11c)) {
                        local_9c++;
                        units[unit].orders = 1;
                      }
                      else {
                        units[unit].orders = -1;
                        local_c = local_c | 1 << (unit_types[units[unit].type].role & 0x1f);
                        local_34++;
                      }
                    }
                  }
                  unit = unit5;
                  if (local_e4 == 2) {
                    civ_clear_standing_goals_near(civ,2,x2,y3,0);
                    civ_clear_standing_goals_near(civ,0x12,x2,y3,0);
                  }
                  if (local_e4 == 4) {
                    if ((iVar27 == 0) && ((char)units[unit2].counter < '\0')) {
                      units[unit2].counter = (byte)game.turn & 7;
                    }
                    if (((local_c & 0xffffff7f) == 0x20) &&
                       (local_34 < (char)unit_types[units[unit2].type].hold)) {
                      local_a8 = 1;
                    }
                    else {
                      local_a8 = 0;
                    }
                    if ((local_c == 0x20) && (units[unit2].orders != 11)) {
                      unit4 = 1;
                    }
                    else {
                      unit4 = 0;
                    }
                    local_c4 = (uint)(local_20 == 0);
                    if (local_20 == 0) {
                      if ((iVar27 == 0) || (unit4 != 0)) {
                        local_188 = (int)(char)unit_types[units[unit2].type].hold;
                        if (2 < local_188) {
                          local_188 = 3;
                        }
                      }
                      else {
                        local_188 = 1;
                      }
                      if ((local_34 < local_188) || (local_a8 != 0)) {
                        local_c4 = local_a8;
                        local_38 = 999;
                        local_140 = 0;
                        for (city = 0; (int)city < (int)game.num_cities;
                            city = city + 1) {
                          if ((((cities[city].id != 0) &&
                               ((int)cities[city].owner == civ)) &&
                              ((cities[city].flags & 0x80) != 0)) &&
                             (((cities[city].flags & 0x200) == 0 ||
                              (((char)units[unit2].counter < '\0' &&
                               ((int)(char)units[unit2].counter == -1 - (city & 0x3f))))))) {
                            iVar13 = tile_landmass((int)cities[city].x,(int)cities[city].y
                                                  );
                            if (local_3c == 0) {
                              city7 = cities_share_ocean(city2,city);
                            }
                            else {
                              city7 = city_adjacent_to_body(city,iVar11);
                            }
                            if (city7 != 0) {
                              local_dc = 0;
                              uVar3 = civs[civ].continent_military[iVar13];
                              city7 = ai_continent_defense_quota(civ,iVar13);
                              if (((int)(uint)uVar3 < city7) &&
                                 (*(char *)&civs[civ].continent_policy[iVar13] != 4)) {
                                if (*(char *)&civs[civ].continent_trade_units[iVar13] == '\0')
                                goto LAB_0053c1e5;
                                local_dc = 1;
                              }
                              local_70 = map_distance_diag(x2,y3,
                                                            (int)cities[city].x,
                                                            (int)cities[city].y);
                              unit3 = tile_first_unit((int)cities[city].x,
                                                            (int)cities[city].y);
                              if ((-1 < unit3) &&
                                 (city7 = unit_stack_count_role(unit3,4),
                                 (int)(uint)(local_70 == 0) < city7)) {
                                local_70 += 0x10;
                              }
                              if ((*(char *)&civs[civ].continent_policy[iVar13] == 4) ||
                                 (*(char *)&civs[civ].continent_flags[iVar13] == '\0')) {
                                local_70 = local_70 -
                                           ((int)(uint)*(ushort *)
                                                        (iVar13 * 2 + ADDR(0x64c8b2, ((u8 *)&civs + 530)) + civ * 0x594) >> 2
                                           );
                              }
                              else {
                                local_70 += 0x10;
                              }
                              if (local_70 < local_38) {
                                local_38 = local_70;
                                city6 = city;
                                local_140 = local_dc;
                                local_2c = (uint)civs[civ].continent_policy[iVar13];
                                unit_set_goto(unit2,0x33,(int)cities[city].x,
                                                   (int)cities[city].y);
                              }
                            }
                          }
LAB_0053c1e5: ;
                        }
                        if (((iVar27 == 0) &&
                            ((((int)(char)units[unit2].counter ^ (int)game.turn - 1U & 3) & 3) != 0)
                            ) && (((local_c & 0x20) == 0 ||
                                  ((local_c == 0x20 ||
                                   (local_34 < (char)unit_types[units[unit2].type].hold)))))) {
                          local_38 = 1000;
                        }
                        if (local_2c == 4) {
                          local_70 = 4;
                        }
                        else {
                          local_70 = 2;
                        }
                        if (local_38 < local_70 * 3) {
                          units[unit2].counter = 0xff - ((byte)city6 & 0x3f);
                          cities[city6].flags = cities[city6].flags | 0x600;
                          if (local_140 == 0) {
                            uVar10 = 5;
                            x = tile_first_unit((int)units[unit2].goto_x,
                                                        (int)units[unit2].goto_y);
                            city7 = unit_stack_count_role(x,uVar10);
                            if (city7 == 0) {
                              if (local_2c != 5) {
                                civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                   (int)units[unit2].goto_y,5,local_70);
                              }
                              if (local_2c != 5) {
                                civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                   (int)units[unit2].goto_y,0x15,local_70 - 1);
                              }
                            }
                            if (local_2c != 1) {
                              civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                 (int)units[unit2].goto_y,1,local_70);
                            }
                            if (local_2c != 0) {
                              civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                 (int)units[unit2].goto_y,0,local_70);
                            }
                            if ((local_2c == 4) || (local_2c == 5)) {
                              civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                 (int)units[unit2].goto_y,6,local_70);
                            }
                          }
                          civ_add_ai_goal(civ,(int)units[unit2].goto_x,(int)units[unit2].goto_y
                                             ,7,2);
                        }
                        else if (((local_3c == 0) &&
                                 (city7 = unit_stack_count_role(unit2,4), city7 < 2)) &&
                                (((city7 = rand_range(0,3), city7 != 0 ||
                                  (local_38 == 1000)) &&
                                 ((civs[civ].continent_flags[iVar11] & 0x10) == 0)))) {
                          uVar3 = civs[civ].continent_military[iVar11];
                          city7 = ai_continent_defense_quota(civ,iVar11);
                          city3 = city2;
                          if ((city7 <= (int)(uint)uVar3) || (uVar28 == 4)) {
                            local_dc = 1;
                          }
                          if (*(char *)&civs[civ].continent_trade_units[iVar11] != '\0') {
                            local_140 = 1;
                          }
                          if ((local_dc != 0) || (local_140 != 0)) {
                            cities[city2].flags = cities[city2].flags | 0x600;
                            if (local_dc != 0) {
                              uVar10 = 5;
                              x = tile_first_unit((int)cities[city2].x,
                                                          (int)cities[city2].y);
                              iVar27 = unit_stack_count_role(x,uVar10);
                              if ((iVar27 == 0) && (uVar28 != 5)) {
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,5,local_70);
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,0x15,local_70 - 1);
                              }
                              if (uVar28 != 1) {
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,1,local_70);
                              }
                              if (uVar28 != 0) {
                                civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y
                                                   ,0,local_70);
                              }
                              if ((uVar28 == 4) || (uVar28 == 5)) {
                                civ_add_ai_goal(civ,(int)units[unit2].goto_x,
                                                   (int)units[unit2].goto_y,6,local_70);
                              }
                            }
                            civ_add_ai_goal(civ,(int)cities[city3].x,(int)cities[city3].y,7,2
                                              );
                            local_c8 = 8;
                            city3 = local_c8;
                            goto LAB_005435ca;
                          }
                        }
                      }
                    }
                    if (local_3c == 0) {
                      for (unit4 = unit_stack_first(unit2); -1 < (int)unit4;
                          unit4 = unit_next_in_stack(unit4)) {
                        if (unit_types[units[unit4].type].role == 5) {
                          unit_relocate_in_place(unit4,1);
                          break;
                        }
                      }
                    }
                    if (((((local_c4 != 0) && (units[unit2].field_0c == 'A')) &&
                         (units[unit2].orders == 11)) &&
                        ((iVar27 != 0 &&
                         (city7 = city_at((int)units[unit2].goto_x,
                                                      (int)units[unit2].goto_y), -1 < city7)))) &&
                       (((cities[city7].flags & 0x80) != 0 &&
                        ((city7 = city_adjacent_to_body(city7,iVar11), city7 != 0 &&
                         ((game.turn & 0xfU) != 0)))))) {
                      local_c4 = 0;
                    }
                    if (((local_c4 != 0) || (local_94 != 0)) || (local_20 != 0)) {
                      bVar31 = local_c == 0x80;
                      for (local_60 = 0; (int)local_60 < 8; local_60++) {
                        x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
                        y2 = (char)(&dir_dy_table)[local_60] + y3;
                        city7 = map_in_bounds(x,y2);
                        if (((city7 != 0) && (city7 = tile_is_ocean(x,y2), city7 == 0)
                            ) && ((civ2 = tile_unit_owner(x,y2), (int)civ2 < 0 ||
                                  (civ2 == civ)))) {
                          if (civ2 == civ) {
                            uVar10 = 2;
                            x5 = tile_first_unit(x,y2);
                            city7 = unit_stack_sum(x5,uVar10);
                            if (1 < city7) goto LAB_0053cdd1;
                          }
                          bVar6 = false;
                          if (((-1 < (int)city4) && ((int)cities[city4].owner != civ)) &&
                             (((*(byte *)&civs[civ].treaties[cities[city4].owner] & 4
                               ) != 0 && (iVar27 < 4)))) {
                            bVar6 = true;
                          }
                          city7 = tile_landmass(x,y2);
                          city3 = city4;
                          local_dc = 0;
                          bVar32 = false;
                          local_c0 = 0;
                          if ((local_c & 0x80) == 0) {
                            if (bVar6) goto LAB_0053cdd1;
                          }
                          else if (city7 == local_104) {
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
                            bVar32 = units[unit2].field_0c != '3';
                            y = tile_landmass((int)cities[city5].x,(int)cities[city5].y);
                            if ((y == local_104) &&
                               (y = map_distance_diag((int)cities[city3].x,
                                                            (int)cities[city3].y,
                                                            (int)cities[city5].x,
                                                            (int)cities[city5].y), y < 0x10)
                               ) {
                              bVar32 = false;
                            }
                            if ((int)cities[city3].owner == civ) {
                              if (cities[city3].size < 8) {
                                bVar32 = false;
                              }
                              y = map_distance_diag((int)cities[city3].x,
                                                          (int)cities[city3].y,
                                                          (int)cities[city5].x,
                                                          (int)cities[city5].y);
                              if (y < 0x10) {
                                bVar32 = false;
                              }
                            }
                            for (local_7c = 0;
                                (int)local_7c < (int)(char)cities[city5].trade_routes;
                                local_7c = local_7c + 1) {
                              if ((int)cities[city5].route_partner[local_7c] ==
                                  city3) {
                                bVar32 = false;
                              }
                            }
                          }
                          uVar3 = civs[civ].continent_military[city7];
                          y = ai_continent_defense_quota(civ,city7);
                          if (((int)(uint)uVar3 < y) &&
                             (*(char *)&civs[civ].continent_policy[city7] != 4)) {
                            local_dc = 1;
                          }
                          if ((*(char *)&civs[civ].continent_cities[city7] == '\0') &&
                             (civs[civ].continent_military[city7] < 8)) {
                            local_dc = 1;
                          }
                          if ((1 << (civs[civ].continent_policy[city7] & 0x1f) & local_c
                              & 3) != 0) {
                            local_dc = 1;
                          }
                          if (((((local_c & 1) != 0) && (-1 < (int)city4)) &&
                              (city2 != city4)) &&
                             (((10 < local_3c && (iVar27 < 4)) &&
                              ((city7 == local_104 &&
                               ((((uint)game.human_players & 1 << (cities[city4].owner & 0x1fU))
                                 != 0 && ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) +
                                                    cities[city4].owner * 4) & 0x20) != 0))))))))
                          {
                            local_dc = 1;
                          }
                          if (((units[unit2].orders == 11) &&
                              (y = tile_landmass((int)units[unit2].goto_x,
                                                      (int)units[unit2].goto_y), y == city7))
                             && (units[unit2].field_0c != '3')) {
                            local_dc = 1;
                            local_16c = 1;
                          }
                          if (((local_c & 0x20) == 0) &&
                             (*(char *)&civs[civ].continent_flags[city7] == '\0')) {
                            if ((*(short *)&civs[civ].continent_military[city7] == 0) &&
                               (0x31 < *(short *)(&landmass_table + city7 * 0x10))) {
                              civs[civ].continent_flags[city7] =
                                   civs[civ].continent_flags[city7] | 0x80;
                              local_c0 = 1;
                            }
                            else {
                              local_dc = 0;
                            }
                          }
                          if ((local_a8 != 0) &&
                             ((civs[civ].continent_flags[city7] & 5) != 0)) {
                            local_dc = 0;
                          }
                          if (1 < (int)local_d8) {
                            local_dc = 1;
                          }
                          if ((((local_a8 == 0) &&
                               (y = tile_city_owner(x,y2), -1 < y)) &&
                              (civ2 != civ)) &&
                             (y = diplo_is_hostile(civ,civ2), y != 0)) {
                            local_dc = 1;
                          }
                          if (bVar31) {
                            local_dc = 0;
                          }
                          if (local_16c != 0) {
                            if (bVar31) {
                              if (!bVar32) {
                                units[unit2].counter = (byte)game.turn & 7;
                              }
                            }
                            else if (local_dc == 0) {
                              units[unit2].counter = (byte)game.turn & 7;
                            }
                          }
                          if (((local_dc != 0) && (4 < *(short *)(&landmass_fertile_tiles + city7 * 0x10)))
                             && ((1 < (int)y2 && ((int)y2 < map.height - 2)))) {
                            y = unit_moves_left(unit2);
                            if ((((int)(uint)cosmic.road_move_mult <= y) &&
                                ((iVar27 != 0 || (uVar28 != 1)))) &&
                               ((local_c8 = ai_ship_best_landing_dir(unit2), -1 < (int)local_c8 &&
                                (local_c8 != 8)))) {
                              units[unit2].field_0c = 'b';
                              city3 = local_c8;
                              goto LAB_005435ca;
                            }
                            if (*(char *)&civs[civ].continent_policy[city7] == '\0') {
                              civ_add_ai_goal(civ,x2,y3,2,5);
                            }
                            units[unit2].field_0c = 'U';
                            unit_exhaust_moves(unit2);
                            units[unit2].orders = -1;
                            if (!bVar32) {
                              local_c = local_c & 0xffffff7f;
                            }
                            unit_stack_wake_by_role(unit2,local_c,local_c0);
                            goto LAB_005436c1;
                          }
                          if (((bVar32) && (1 < (int)y2)) && ((int)y2 < map.height - 2)
                             ) {
                            if (*(char *)&civs[civ].continent_policy[city7] == '\0') {
                              civ_add_ai_goal(civ,x2,y3,2,5);
                            }
                            units[unit2].field_0c = 'u';
                            unit_exhaust_moves(unit2);
                            local_c = 0x80;
                            if (!bVar6) {
                              local_c = 0x82;
                            }
                            unit_stack_wake_by_role(unit2,local_c,local_c0);
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
                  if (local_20 != 0) {
                    return 1;
                  }
                  if ((local_e4 == 4) || (local_158 == 0)) {
                    if ((units[unit2].orders != 11) &&
                       (((local_c & 3) != 0 && (unit_types[units[unit2].type].hold != '\0')))) {
                      local_38 = 0x18;
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if (((cities[city].id != 0) && ((int)cities[city].owner == civ))
                           && (city7 = tile_landmass((int)cities[city].x,
                                                      (int)cities[city].y),
                              *(char *)&civs[civ].continent_policy[city7] == 1)) {
                          if (local_3c == 0) {
                            city7 = cities_share_ocean(city2,city);
                          }
                          else {
                            city7 = city_adjacent_to_body(city,iVar11);
                          }
                          if (city7 != 0) {
                            local_70 = map_distance_diag(x2,y3,(int)cities[city].x
                                                          ,(int)cities[city].y);
                            city7 = tile_unit_owner((int)cities[city].x,
                                                     (int)cities[city].y);
                            if (city7 < 0) {
                              local_70 = local_70 / 2;
                            }
                            else {
                              city7 = civ_ai_goal_get_priority(civ,(int)cities[city].x,
                                                          (int)cities[city].y,1);
                              if (city7 != 0) {
                                local_70 -= local_70 / 3;
                              }
                            }
                            if (local_70 < local_38) {
                              local_38 = local_70;
                              unit_set_goto(unit2,0x41,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if ((units[unit2].orders != 11) && ((local_c & 3) != 0)) {
                      local_38 = 999;
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if (((cities[city].id != 0) &&
                            (civ2 = (uptr)cities[city].owner, civ2 != civ)) &&
                           (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0 &&
                            (city7 = tile_unit_owner((int)cities[city].x,
                                                      (int)cities[city].y), city7 < 0)))) {
                          tile_landmass((int)cities[city].x,(int)cities[city].y);
                          if (local_3c == 0) {
                            city7 = cities_share_ocean(city2,city);
                          }
                          else {
                            city7 = city_adjacent_to_body(city,iVar11);
                          }
                          if (city7 != 0) {
                            local_70 = map_distance_diag(x2,y3,(int)cities[city].x
                                                          ,(int)cities[city].y);
                            for (civ4 = 1; civ4 < 8; civ4++) {
                              if ((((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0)
                                  && ((*(byte *)&civs[civ].treaties[civ4] & 8) != 0
                                     )) && ((*(byte *)(civ4 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4)
                                            & 0x20) != 0)) {
                                local_70 = local_70 / 2;
                                break;
                              }
                            }
                            if ((cities[city].flags & 0x8000000) != 0) {
                              local_70 = local_70 << 1;
                            }
                            if (local_70 < local_38) {
                              local_38 = local_70;
                              units[unit2].counter = (byte)city & 7;
                              unit_set_goto(unit2,0x49,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if (units[unit2].orders != 11) {
                      local_110 = 0xffffffff;
                      for (civ2 = 0; (int)civ2 < 8; civ2++) {
                        if (((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) &&
                           (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0 ||
                            ((int)local_110 < 0)))) {
                          local_110 = civ2;
                        }
                      }
                      if (((local_c & 1) != 0) || ((local_c & 0x20) == 0)) {
                        local_38 = 999;
                        local_1c = tile_land_landmass(x2,y3);
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
                                                     (int)cities[city].y), local_1c != city7))
                          {
                            if (local_3c == 0) {
                              city7 = ai_city_touches_landmass(city2,city7);
                            }
                            else {
                              city7 = landmass_borders_body(city7,iVar11);
                            }
                            if (city7 != 0) {
                              local_70 = map_distance_diag(x2,y3,
                                                            (int)cities[city].x,
                                                            (int)cities[city].y);
                              if ((0 < (int)local_110) &&
                                 ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_110 * 0x594) & 0x20) !=
                                  0)) {
                                local_70 = local_70 / 2;
                              }
                              if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 8) != 0) {
                                local_70 = local_70 / 2;
                              }
                              if (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0)
                                 && (city7 = tile_unit_owner((int)cities[city].x,
                                                              (int)cities[city].y), city7 < 0)
                                 ) {
                                local_70 = local_70 / 2;
                              }
                              if ((cities[city].flags & 0x8000000) != 0) {
                                local_70 = local_70 << 1;
                              }
                              if (local_70 < local_38) {
                                local_38 = local_70;
                                unit_set_goto(unit2,0x34,(int)cities[city].x,
                                                   (int)cities[city].y);
                              }
                            }
                          }
                        }
                      }
                    }
                    if (((units[unit2].orders != 11) && ((local_c & 0x80) != 0)) &&
                       (unit_types[units[unit2].type].hold != '\0')) {
                      local_38 = -999;
                      local_1c = tile_land_landmass(x2,y3);
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
                                                  ), local_1c != city7)) {
                          if (local_3c == 0) {
                            if ((int)cities[city].owner == civ) {
                              city7 = cities_share_ocean(city2,city);
                            }
                            else {
                              city7 = ai_city_touches_landmass(city2,city7);
                            }
                          }
                          else if ((int)cities[city].owner == civ) {
                            city7 = city_adjacent_to_body(city,iVar11);
                          }
                          else {
                            city7 = landmass_borders_body(city7,iVar11);
                          }
                          if (city7 != 0) {
                            local_70 = map_distance_diag((int)cities[city5].x,
                                                          (int)cities[city5].y,
                                                          (int)cities[city].x,
                                                          (int)cities[city].y);
                            if ((int)cities[city].owner == civ) {
                              local_70 = local_70 / 2;
                            }
                            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + cities[city].owner * 4) &
                                0x20) != 0) {
                              local_70 -= local_70 / 3;
                            }
                            if ((*(byte *)&civs[civ].treaties[cities[city].owner] &
                                8) != 0) {
                              local_70 += local_70 / 3;
                            }
                            if (((((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)
                                  ) != 0) && (game.power_rank[cities[city].owner] == 7)) &&
                               (4 < civs[civ2].num_cities)) {
                              local_70 = local_70 / 2;
                            }
                            local_70 = cities[city].base_trade * local_70;
                            city7 = map_distance_diag(x2,y3,(int)cities[city].x,
                                                        (int)cities[city].y);
                            local_70 = local_70 / ((city7 >> 3) + 1);
                            if (local_38 < local_70) {
                              local_38 = local_70;
                              unit_set_goto(x,0x54,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if (units[unit].orders != 11) {
                      local_38 = 999;
                      local_1c = tile_land_landmass(x2,y3);
                      for (city = 0; (int)city < (int)game.num_cities;
                          city = city + 1) {
                        if (((cities[city].id != 0) &&
                            (civ2 = (uptr)cities[city].owner, civ2 == civ)) &&
                           ((local_70 = map_distance_diag(x2,y3,
                                                           (int)cities[city].x,
                                                           (int)cities[city].y), 7 < local_70
                            && ((city7 = tile_landmass((int)cities[city].x,
                                                        (int)cities[city].y),
                                local_1c != city7 &&
                                (*(char *)&civs[civ].continent_policy[city7] != 4)))))) {
                          if (local_3c == 0) {
                            y = cities_share_ocean(city2,city);
                          }
                          else {
                            y = city_adjacent_to_body(city,iVar11);
                          }
                          if (y != 0) {
                            if ((local_c &
                                1 << (civs[civ].continent_policy[city7] & 0x1f)) == 0) {
                              local_70 = local_70 << 1;
                            }
                            if (local_70 < local_38) {
                              local_38 = local_70;
                              unit_set_goto(unit,0x35,(int)cities[city].x,
                                                 (int)cities[city].y);
                            }
                          }
                        }
                      }
                    }
                    if ((units[unit].orders != 11) &&
                       (unit_types[units[unit].type].hold != '\0')) {
                      if (units[unit].field_0c == 'V') {
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
                      local_1c = tile_land_landmass(x2,y3);
                      if ((((0 < city7) && (city7 < 0x3f)) &&
                          (0x10 < *(short *)(&landmass_fertile_tiles + city7 * 0x10))) &&
                         ((local_1c != city7 &&
                          (*(char *)&civs[civ].continent_cities[city7] == '\0')))) {
                        local_c4 = 1;
                        if (local_3c == 0) {
                          city7 = ai_city_touches_landmass(city2,city7);
                          if (city7 == 0) {
                            local_c4 = 0;
                          }
                        }
                        else {
                          city7 = landmass_borders_body(city7,iVar11);
                          if (city7 == 0) {
                            local_c4 = 0;
                          }
                        }
                        if (local_c4 != 0) {
                          ai_ship_goto_near_shore(unit,0x56,x4,y2);
                        }
                      }
                    }
                    if (units[unit].orders != 11) {
                      for (local_60 = 2; (int)local_60 < 0x18; local_60++) {
                        local_7c = rand_range(0,7);
                        x = map_wrap_x((int)(char)(&dir_dx_table)[local_7c] * local_60 +
                                            x2);
                        y2 = (int)(char)(&dir_dy_table)[local_7c] * local_60 + y3;
                        city7 = map_in_bounds(x,y2);
                        if (((city7 != 0) && (1 < (int)y2)) &&
                           (((int)y2 <= map.height - 3 &&
                            ((city7 = tile_is_ocean(x,y2), city7 == 0 &&
                             (city7 = tile_landmass(x,y2),
                             *(char *)&civs[civ].continent_cities[city7] == '\0')))))) {
                          if (local_3c == 0) {
                            city7 = ai_city_touches_landmass(city2,city7);
                          }
                          else {
                            city7 = landmass_borders_body(city7,iVar11);
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
                    (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + cities[city3].owner * 4) & 0x20) != 0
                     && (unit_types[units[unit].type].domain == '\0')))) &&
                   (unit_types[units[unit].type].attack != '\0')) {
                  city7 = tile_at(x2,y3);
                  bVar7 = *(byte *)(city7 + 1);
                  local_14 = (uint)bVar7;
                  unit4 = 0;
                  if (((bVar7 & 0x4c) == 0) || (3 < iVar27)) {
                    if (((bVar7 & 0x5c) != 0) &&
                       (((*(char *)&civs[civ].continent_cities[iVar11] == '\0' && (iVar27 < 8)) ||
                        (unit_type == 9)))) {
                      unit4 = 1;
                    }
                  }
                  else {
                    unit4 = 1;
                  }
                  if ((unit4 != 0) && (!bVar4)) {
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
                        && (((1 << (bVar8 & 0x1f) & (uint)units[unit].visibility) != 0 ||
                            ((int)units[unit].owner == (uint)bVar8)))) &&
                       (city7 = tile_landmass((int)units[unit].x,(int)units[unit].y),
                       city7 == iVar11)) {
                      unit_set_goto(unit5,0x50,(int)units[unit].x,
                                         (int)units[unit].y);
                      local_a4 = 1;
                      break;
                    }
                  }
                  unit = unit5;
                  if (local_a4 != 0) break;
                }
                if ((((unit_type == 9) && (-1 < (int)city3)) &&
                    (((uint)game.human_players & 1 << (cities[city3].owner & 0x1fU)) != 0)) &&
                   ((*(byte *)&civs[civ].treaties[cities[city3].owner] & 6) == 0)) {
                  local_70 = map_distance_diag(x2,y3,(int)cities[city3].x,
                                                (int)cities[city3].y);
                  city6 = 0xffffffff;
                  for (local_60 = 0; (int)local_60 < 8; local_60++) {
                    x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
                    y2 = (char)(&dir_dy_table)[local_60] + y3;
                    city7 = map_in_bounds(x,y2);
                    if ((city7 != 0) && (city7 = tile_unit_owner(x,y2), city7 < 0)) {
                      city7 = tile_city_owner(x,y2);
                      if (-1 < city7) {
                        city6 = 0xffffffff;
                        break;
                      }
                      city7 = map_distance_diag(x,y2,(int)cities[city3].x,
                                                  (int)cities[city3].y);
                      if ((city7 <= local_70) &&
                         (terrain = tile_improvements(x,y2), (terrain & 0x5c) != 0)) {
                        city6 = local_60;
                      }
                    }
                  }
                  if (-1 < (int)city6) {
                    units[unit].field_0c = 'p';
                    local_c8 = city6;
                    city3 = local_c8;
                    goto LAB_005435ca;
                  }
                }
                local_f4 = 0;
                if (((bVar30) || (local_e4 == 1)) &&
                   (city7 = civ_has_advance(civ,0x12), city7 != 0)) {
                  local_84 = local_3c;
                  if (-1 < (int)city2) {
                    local_84 = map_distance(x2,y3,(int)cities[city2].x,
                                                  (int)cities[city2].y);
                  }
                  if (((local_3c != 0) && (city2 == city4)) &&
                     ((local_bc == 0 &&
                      ((city7 = tile_airbase_owner(x2,y3), city7 < 0 &&
                       (city7 = tile_is_ocean(x2,y3), city7 == 0)))))) {
                    local_8 = 0;
                    local_114 = 0;
                    local_b8 = 0;
                    local_4c = 0;
                    local_28 = 0;
                    for (local_60 = 0; (int)local_60 < 8; local_60++) {
                      x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
                      y2 = (char)(&dir_dy_table)[local_60] + y3;
                      city7 = map_in_bounds(x,y2);
                      if (city7 != 0) {
                        uVar10 = tile_improvements(x,y2);
                        if ((((byte)uVar10 & 0x42) == 0x40) ||
                           (city7 = tile_city_owner(x,y2), -1 < city7))
                        goto LAB_0053fc8d;
                        city7 = tile_is_ocean(x,y2);
                        if (city7 != 0) {
                          local_8++;
                          if (3 < local_8) goto LAB_0053fc8d;
                          if ((char)(&dir_dy_table)[local_60] < '\0') {
                            local_b8 = 1;
                          }
                          if ('\0' < (char)(&dir_dy_table)[local_60]) {
                            local_114 = 1;
                          }
                          if ((char)(&dir_dx_table)[local_60] < '\0') {
                            local_28 = 1;
                          }
                          if ('\0' < (char)(&dir_dx_table)[local_60]) {
                            local_4c = 1;
                          }
                        }
                        city7 = civ_ai_goal_get_priority(civ,x,y2,1);
                        if (city7 != 0) goto LAB_0053fc8d;
                      }
                    }
                    terrain = tile_improvements(x2,y3);
                    if (((((terrain & 0x10) != 0) && (1 < local_3c)) && (local_3c < 4)) &&
                       (city2 == city4)) {
                      local_f4 = 1;
                    }
                    for (local_60 = 0xfffffffe; (int)local_60 < 3; local_60++) {
                      x = map_wrap_x(local_60 + x2);
                      city7 = map_in_bounds(x,y3 - 2);
                      if (((city7 != 0) && (local_b8 == 0)) &&
                         ((city7 = tile_is_ocean(x,y3 - 2), city7 != 0 ||
                          (uVar10 = tile_improvements(x,y3 - 2),
                          ((byte)uVar10 & 0x42) == 0x40)))) {
                        local_b8 = 2;
                      }
                      city7 = map_in_bounds(x,y3 + 2);
                      if (((city7 != 0) && (local_114 == 0)) &&
                         ((city7 = tile_is_ocean(x,y3 + 2), city7 != 0 ||
                          (uVar10 = tile_improvements(x,y3 + 2),
                          ((byte)uVar10 & 0x42) == 0x40)))) {
                        local_114 = 2;
                      }
                    }
                    for (local_60 = 0xfffffffe; (int)local_60 < 3; local_60++) {
                      y2 = local_60 + y3;
                      x = map_wrap_x(x2 - 2);
                      city7 = map_in_bounds(x,y2);
                      if (((city7 != 0) && (local_28 == 0)) &&
                         ((city7 = tile_is_ocean(x,y2), city7 != 0 ||
                          (uVar10 = tile_improvements(x,y2),
                          ((byte)uVar10 & 0x42) == 0x40)))) {
                        local_28 = 2;
                      }
                      x = map_wrap_x(x2 + 2);
                      city7 = map_in_bounds(x,y2);
                      if (((city7 != 0) && (local_4c == 0)) &&
                         ((city7 = tile_is_ocean(x,y2), city7 != 0 ||
                          (uVar10 = tile_improvements(x,y2),
                          ((byte)uVar10 & 0x42) == 0x40)))) {
                        local_4c = 2;
                      }
                    }
                    if ((1 < local_b8 + local_114) && ((local_28 == 0 || (local_4c == 0)))) {
                      local_f4 = 2;
                    }
                    if ((1 < local_4c + local_28) && ((local_b8 == 0 || (local_114 == 0)))) {
                      local_f4 = 2;
                    }
                    if (local_f4 != 0) {
                      if (bVar30) {
                        civ_add_standing_goal(civ,x2,y3,1,2);
                      }
                      else {
                        civ_add_standing_goal(civ,x2,y3,0x15,
                                           (uint)(local_84 < 4) + local_f4);
                      }
                    }
                  }
                }
LAB_0053fc8d:
                if (((local_e4 == 5) && (units[unit].orders == 11)) &&
                   (city7 = tile_city_owner((int)units[unit].goto_x,
                                             (int)units[unit].goto_y), -1 < city7)) {
                  local_b4 = 1;
                }
                if (((bVar30) && (!bVar4)) &&
                   ((local_b4 == 0 &&
                    ((city7 = tile_is_ocean(x2,y3), city7 == 0 &&
                     (city7 = tile_city_owner(x2,y3), city7 < 0)))))) {
                  city7 = unit_stack_sum(unit,2);
                  local_c4 = (uint)(1 < city7);
                  if (local_c4 == 0) {
                    for (local_60 = 0; (int)local_60 < 8; local_60++) {
                      x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
                      y2 = (char)(&dir_dy_table)[local_60] + y3;
                      city7 = map_in_bounds(x,y2);
                      if ((city7 != 0) && (city7 = tile_unit_owner(x,y2), -1 < city7))
                      {
                        local_c4 = 1;
                        break;
                      }
                    }
                  }
                  if (local_c4 == 0) {
                    civ_add_ai_goal(civ,x2,y3,1,2);
                  }
                  civ_clear_standing_goals_near(civ,0x15,x2,y3,0);
                  uVar17 = tile_improvements(x2,y3);
                  if ((uVar17 & 0x80) != 0) {
                    units[unit].orders = '\t';
                    units[unit].field_0c = 'p';
                    goto LAB_005436c1;
                  }
                  if (((((1 << (bVar8 & 0x1f) & (uint)game.human_players) == 0) ||
                       (units[unit].orders != 11)) ||
                      (city7 = map_in_bounds((int)units[unit].goto_x,
                                              (int)units[unit].goto_y), city7 == 0)) ||
                     (uVar18 = tile_improvements((int)units[unit].goto_x,
                                                 (int)units[unit].goto_y), (uVar18 & 0x80) == 0
                     )) {
                    if (((local_f4 == 2) && ((1 << (bVar8 & 0x1f) & (uint)game.human_players) == 0))
                       && ((city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 == 0 ||
                           (city7 = unit_stack_sum(unit,2), 1 < city7)))) {
                      units[unit].orders = 4;
                      units[unit].field_0c = 'X';
                      goto LAB_005436c1;
                    }
                    local_170 = 0;
                    if ((bVar29) && ((units[unit].flags & 0x80) != 0)) {
                      local_170 = 1;
                    }
                    else {
                      city7 = civ_ai_goal_get_priority(civ,x2,y3,0x15);
                      if (city7 != 0) {
                        local_170 = 1;
                      }
                    }
                    if ((((2 < local_3c) || ((cities[city2].flags & 0x40) == 0)) || (!bVar29)) ||
                       (units[unit].orders != 11)) {
                      if ((((local_3c != 0) && (local_3c < 3)) &&
                          ((((int)(char)terrain_types[terrain2].irrigate_turns / 5) * 3 - 3 <=
                            (int)cities[city2].size ||
                           (city7 = tile_resource(x2,y3), city7 != 0)))) &&
                         ((city7 = ai_tile_improve_choice(civ,x2,y3), city7 != 0 ||
                          (uVar28 == 4)))) {
                        local_170 = local_170 | 2;
                      }
                      if (local_170 != 0) {
                        if ((local_170 & 2) != 0) {
                          city7 = ai_tile_improve_choice(civ,x2,y3);
                          if (city7 == 1) {
                            units[unit].orders = 6;
                            units[unit].field_0c = 'I';
                            goto LAB_005436c1;
                          }
                          if (city7 == 2) {
                            units[unit].orders = 7;
                            units[unit].field_0c = 'M';
                            goto LAB_005436c1;
                          }
                        }
                        city7 = tile_at(x2,y3);
                        bVar7 = *(byte *)(city7 + 1);
                        local_14 = (uint)bVar7;
                        if (((bVar7 & 0x10) == 0) || ((bVar7 & 0x20) != 0)) {
                          if (((bVar7 & 0x10) == 0) &&
                             ((pbVar25 = (byte *)tile_at(x2,y3), (*pbVar25 & 0x80) == 0
                              || (city7 = civ_has_advance(civ,7), city7 != 0)))) {
                            local_170 = local_170 & 1;
                            if (((local_14 & 0xc) != 0) &&
                               ((pbVar25 = (byte *)tile_at(x2,y3),
                                (*pbVar25 & 0x80) != 0 || ((int)terrain2 < 3)))) {
                              local_170 = local_170 | 2;
                            }
                            if (local_170 != 0) {
                              units[unit].orders = 5;
                              units[unit].field_0c = 'r';
                              goto LAB_005436c1;
                            }
                          }
                        }
                        else {
                          city7 = civ_has_advance(civ,0x43);
                          if (city7 != 0) {
                            local_170 = local_170 & 1;
                            city7 = tile_resource(x2,y3);
                            if (city7 != 0) {
                              local_170 = local_170 | 2;
                            }
                            if ((local_14 & 8) != 0) {
                              local_170 = local_170 | 2;
                            }
                            if (1 < (char)terrain_types[terrain2].shields) {
                              local_170 = local_170 | 2;
                            }
                            if (local_170 != 0) {
                              units[unit].orders = 5;
                              units[unit].field_0c = 'R';
                              goto LAB_005436c1;
                            }
                          }
                        }
                      }
                      if (((local_f4 != 0) &&
                          ((1 << (bVar8 & 0x1f) & (uint)game.human_players) == 0)) &&
                         ((city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 == 0 ||
                          (city7 = unit_stack_sum(unit,2), 1 < city7)))) {
                        units[unit].orders = 4;
                        units[unit].field_0c = 'X';
                        goto LAB_005436c1;
                      }
                      city3 = city2;
                      if (((units[unit].orders == 11) &&
                          ((units[unit].flags & 0x200) == 0)) &&
                         (city7 = (leaders[civs[civ].tribe].expand + 1) *
                                   (int)*(short *)(&landmass_fertile_tiles + iVar11 * 0x10),
                         terrain = (uint)civs[civ].continent_cities[iVar11],
                         city7 + terrain * -0x10 != 0 && (int)(terrain * 0x10) <= city7))
                      goto LAB_005436c1;
                      if (local_3c < 2) {
                        for (local_60 = 0; (int)local_60 < 8; local_60++) {
                          local_7c = (int)game.turn + local_60 & 7;
                          x = map_wrap_x((char)(&dir_dx_table)[local_7c] + x2);
                          y2 = (char)(&dir_dy_table)[local_7c] + y3;
                          city7 = map_in_bounds(x,y2);
                          if (((city7 != 0) &&
                              (city7 = tile_city_owner(x,y2), city7 < 0)) &&
                             (((unit3 = tile_first_unit(x,y2), unit3 < 0 ||
                               (((int)units[unit3].owner == civ &&
                                (city7 = unit_stack_count_role(unit3,5), city7 == 0)))) &&
                              (city7 = ai_tile_improve_choice(civ,x,y2), city7 != 0)))) {
                            bVar7 = tile_terrain(x,y2);
                            unit4 = (uptr)bVar7;
                            if (((((int)(char)terrain_types[unit4].irrigate_turns / 5) * 3 - 3
                                  <= (int)cities[city3].size) ||
                                (city7 = tile_resource(x,y2), city7 != 0)) &&
                               (city7 = map_distance_diag(x2,y3,x,y2),
                               city7 < 3)) {
                              units[unit].field_0c = 's';
                              local_c8 = local_7c;
                              city3 = local_c8;
                              goto LAB_005435ca;
                            }
                          }
                        }
                      }
                      terrain = tile_improvements(x2,y3);
                      if ((((terrain & 0x10) == 0) &&
                          ((pbVar25 = (byte *)tile_at(x2,y3), (*pbVar25 & 0x80) == 0 ||
                           (city7 = civ_has_advance(civ,7), city7 != 0)))) &&
                         ((local_3c < 3 && ((int)terrain2 < 3)))) {
                        units[unit].field_0c = 'r';
                        units[unit].orders = 5;
                        goto LAB_005436c1;
                      }
                    }
                  }
                }
                if (((local_e4 == 0x15) && (units[unit].orders != 11)) &&
                   ((!bVar4 &&
                    (((local_b4 == 0 && (local_3c != 0)) &&
                     (city7 = tile_is_ocean(x2,y3), city7 == 0)))))) {
                  if (units[unit].home_city == -1) {
                    city = city2;
                  }
                  else {
                    city = (uptr)(byte)units[unit].home_city;
                  }
                  if ((-1 < (int)city) &&
                     (city7 = tile_landmass((int)cities[city].x,(int)cities[city].y),
                     city7 != iVar11)) {
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
                     ((pbVar25 = (byte *)tile_at(x2,y3), (*pbVar25 & 0x80) == 0 ||
                      (city7 = civ_has_advance(civ,7), city7 != 0)))) {
                    units[unit].field_0c = 'r';
                    units[unit].orders = 5;
                    goto LAB_005436c1;
                  }
                  if ((-1 < (int)city2) && (local_158 != 0)) {
                    unit_set_goto(unit,99,(int)cities[city2].x,(int)cities[city2].y)
                    ;
                    goto LAB_005436c1;
                  }
                  if (local_3c < 3) {
                    city7 = tile_at(x2,y3);
                    bVar7 = *(byte *)(city7 + 1);
                    local_14 = (uint)bVar7;
                    if ((bVar7 & 0xe) == 0) {
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
                    if ((bVar7 & 0x80) != 0) {
                      units[unit].orders = '\t';
                      goto LAB_005436c1;
                    }
                    terrain = tile_improvements(x2,y3);
                    if (((terrain & 0x20) == 0) &&
                       (city7 = civ_has_advance(civ,0x43), city7 != 0)) {
                      units[unit].field_0c = 'r';
                      units[unit].orders = 5;
                      goto LAB_005436c1;
                    }
                    city3 = city2;
                    for (local_60 = 0; (int)local_60 < 0x14; local_60++) {
                      x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_60] +
                                          (int)cities[city3].x);
                      y2 = (int)cities[city3].y + (int)(char)(&city_tile_dy_table)[local_60];
                      city7 = map_in_bounds(x,y2);
                      if (city7 != 0) {
                        bVar7 = tile_terrain(x,y2);
                        city7 = tile_at(x,y2);
                        local_14 = (uint)*(byte *)(city7 + 1);
                        if ((*(byte *)(city7 + 1) & 0xe) == 0) {
                          if ((terrain_types[bVar7].mine_ai_govt != '\0') &&
                             ((char)terrain_types[bVar7].mine_ai_govt <
                              (char)terrain_types[bVar7].irrigate_ai_govt)) {
                            unit_set_goto(unit,0x6d,x,y2);
                            goto LAB_005436c1;
                          }
                          if (terrain_types[bVar7].irrigate_ai_govt != '\0') {
                            unit_set_goto(unit,0x69,x,y2);
                            goto LAB_005436c1;
                          }
                        }
                        pbVar25 = (byte *)tile_at(x,y2);
                        if ((((*pbVar25 & 0x80) == 0) ||
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
                      units[unit].field_0c = 'r';
                      units[unit].orders = 5;
                      goto LAB_005436c1;
                    }
                  }
                }
                if ((units[unit].orders != 11) ||
                   (((local_e4 == 2 &&
                     (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 != 0)) || (bVar4)
                    ))) goto LAB_00541001;
                local_c4 = 1;
                city7 = map_distance(x2,y3,(int)units[unit].goto_x,
                                            (int)units[unit].goto_y);
                if (1 < city7) {
                  if (((int)local_e4 < 5) &&
                     (city7 = tile_adjacent_nonallied_unit(x2,y3,civ), city7 != 0)) {
                    local_a4 = 1;
                    local_c4 = 0;
                  }
                  goto LAB_00540fea;
                }
                civ2 = tile_city_or_unit_owner
                                     ((int)units[unit].goto_x,(int)units[unit].goto_y);
                if (((int)civ2 < 0) || (civ2 == civ)) goto LAB_00540fea;
                if ((local_e4 != 4) ||
                   ((city7 = unit_stack_sum(unit,2), city7 < 2 || (local_94 != 0))))
                goto LAB_00540f1e;
                units[unit].orders = -1;
                local_94 = 1;
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
              units[unit].field_0c = 'F';
              units[unit].home_city = (i8)city2;
              bVar5 = false;
              local_c8 = 8;
              city3 = local_c8;
              goto LAB_005435ca;
            }
            local_90 = 1;
          }
        }
        else {
          if (local_e4 != 1) {
            if (local_e4 == 0) {
              if (local_158 != 0) {
                local_90 = 1;
              }
              city7 = unit_stack_sum(unit,2);
              if (((city7 == 1) && (-1 < unit_types[units[unit].type].obsolete_by)) &&
                 (game.advance_known_by[unit_types[units[unit].type].obsolete_by] != '\0')) {
                local_90 = 1;
              }
              if (local_90 != 0) goto LAB_005414d7;
            }
            goto LAB_0053b8f0;
          }
          city7 = unit_stack_count_role(unit,1);
          if ((1 < city7) && (units[unit].orders == 11)) goto LAB_0053b8f0;
          units[unit].field_0c = 'F';
          local_90 = 1;
        }
LAB_005414d7:
        local_38 = -999;
        local_fc = -999;
        local_c8 = 8;
        local_68 = 0;
        local_50 = 0;
        if (((local_e4 == 4) && (local_3c != 0)) &&
           ((city7 = unit_stack_sum(unit,2), 1 < city7 &&
            (units[unit].orders == 11)))) {
          local_a4 = 1;
        }
        city7 = tile_zoc_unit_adjacent(x2,y3,civ);
        if (city7 == 0) {
          if (local_a4 == 0) {
            local_68 = 1;
          }
          else {
            local_68 = 0;
          }
        }
        else {
          units[unit].last_dir = 0xff;
        }
        if (((game.game_flags & 0x80) != 0) && ((scenario_flags & 8) != 0)) {
          local_68 = 0;
        }
        if (local_e4 == 1) {
          if (((char)unit_types[unit_type].defense < (char)unit_types[unit_type].attack) &&
             ((civs[civ].continent_flags[iVar11] & 0x10) == 0)) {
            local_e4 = 0;
          }
          if (((char)unit_types[unit_type].defense <= (char)unit_types[unit_type].attack) && (uVar28 == 0)
             ) {
            local_e4 = 0;
          }
        }
        for (local_60 = 0; (int)local_60 < 8; local_60++) {
          x = map_wrap_x((char)(&dir_dx_table)[local_60] + x2);
          y2 = (char)(&dir_dy_table)[local_60] + y3;
          city7 = map_in_bounds(x,y2);
          if (city7 != 0) {
            civ2 = tile_owner(x,y2);
            bVar8 = tile_terrain(x,y2);
            terrain = (uint)bVar8;
            local_6c = (uint)(terrain == 10);
            if ((local_6c == 0) || (local_144 != 0)) {
              unit3 = tile_first_unit(x,y2);
              while (((-1 < unit3 && (-1 < units[unit3].next_in_stack)) &&
                     (4 < (char)unit_types[units[unit3].type].role))) {
                unit3 = unit_next_in_stack(unit3);
              }
              if (((((((local_158 == 0) || (local_144 != 0)) ||
                     ((-1 < unit3 ||
                      ((city7 = tile_in_enemy_zoc(x,y2,civ), city7 == 0 ||
                       ((local_a0 & 2) != 0)))))) || (local_6c != 0)) &&
                   ((((local_6c == 0 || (local_144 != 0)) || (unit3 < 0)) || (civ2 == civ))
                   )) && (((local_144 != 2 || (local_6c != 0)) ||
                          (((-1 < unit3 && ((civ2 != civ && (terrain2 == 10)))) &&
                           ((local_a0 & 8) == 0)))))) &&
                 ((((unit3 < 0 || (civ2 != civ)) ||
                   (city7 = unit_stack_sum(unit3,2), city7 < 2)) ||
                  ((city7 = tile_city_owner(x,y2), -1 < city7 ||
                   (uVar10 = tile_improvements(x,y2), ((byte)uVar10 & 0x42) == 0x40))))))
              {
                local_18 = 0;
                if (bVar30) {
                  if ((terrain2 == 10) &&
                     (city7 = tile_zoc_unit_adjacent(x,y2,civ), city7 != 0))
                  goto LAB_0054168e;
                  local_18 = rand_range(0,4);
                }
                else if ((units[unit].visibility == '\0') && (terrain2 != 10)) {
                  if (local_e4 == 0) {
                    local_18 = rand_range(0,2);
                    local_18 += (char)terrain_types[terrain].move_cost * -2;
                  }
                  else {
                    local_18 = rand_range(0,2);
                    local_18 -= (char)terrain_types[terrain].defense;
                  }
                }
                else {
                  local_18 = rand_range(0,4);
                  if ((unit3 < 0) || (civ2 != civ)) {
                    if ((int)local_e4 < 6) {
                      local_18 += (char)terrain_types[terrain].defense * 4;
                    }
                    else {
                      local_18 = local_18 +
                                 (6 - ((char)terrain_types[terrain].move_cost - 1) *
                                      (uint)cosmic.road_move_mult);
                      if ((iVar27 < 4) && (city2 != city4)) {
                        local_70 = map_distance(x,y2,(int)cities[city4].x,
                                                      (int)cities[city4].y);
                        if (local_70 == 1) {
                          if ((int)(uint)cosmic.road_move_mult <
                              (int)(char)terrain_types[terrain].move_cost) {
                            local_18 -= 4;
                          }
                          else {
                            local_18 += 8;
                          }
                        }
                        else if (((local_70 == 2) &&
                                 ((int)(char)terrain_types[terrain].move_cost <=
                                  (int)(uint)cosmic.road_move_mult)) &&
                                (uVar16 = tile_improvements(x,y2), (uVar16 & 0x10) != 0))
                        {
                          local_18 += 4;
                        }
                      }
                    }
                  }
                  else {
                    uVar10 = tile_improvements(x,y2);
                    if ((((byte)uVar10 & 0x43) == 1) &&
                       (city7 = tile_adjacent_nonallied_unit(x,y2,civ), city7 != 0)) {
                      switch(local_e4) {
                      case 0:
                        unit4 = unit_stack_count_role(unit3,0);
                        if (((int)unit4 < 1) &&
                           (city7 = unit_stack_count_role(unit3,1), city7 != 0)) {
                          local_18 += 8;
                        }
                        else {
                          local_18 += unit4 * -8;
                        }
                        break;
                      case 1:
                        unit4 = unit_stack_count_role(unit3,1);
                        if ((int)unit4 < 1) {
                          local_18 += 8;
                        }
                        else {
                          local_18 += unit4 * -4;
                        }
                        break;
                      case 2:
                        city7 = unit_stack_count_role(unit3,4);
                        if (city7 != 0) {
                          local_18 += 8;
                        }
                        city7 = unit_stack_count_role(unit3,2);
                        local_18 += city7 * -4;
                        break;
                      case 4:
                        city7 = unit_stack_count_role(unit3,2);
                        if (city7 != 0) {
                          local_18 += 8;
                        }
                        city7 = unit_stack_count_role(unit3,4);
                        local_18 += city7 * -8;
                        break;
                      case 5:
                      case 0x15:
                        local_18 -= 4;
                        break;
                      case 6:
                        city7 = unit_stack_count_role(unit3,0);
                        y = unit_stack_count_role(unit3,1);
                        if (city7 + y != 0) {
                          local_18 += 8;
                        }
                      }
                    }
                    else {
                      switch(local_e4) {
                      case 0:
                        city7 = unit_stack_sum(unit3,0);
                        y = unit_stack_sum(unit3,2);
                        local_18 += (city7 * 4) / (y + 1);
                        break;
                      case 1:
                        city7 = unit_stack_sum(unit3,3);
                        y = unit_stack_sum(unit3,0);
                        local_18 += (city7 * 2) / (y + 1);
                        break;
                      case 5:
                        uVar2 = terrain_types[terrain].defense;
                        city7 = unit_stack_sum(unit3,0);
                        local_18 += ((char)uVar2 + city7) * 2;
                        break;
                      case 6:
                        city7 = unit_stack_count_role(unit3,0);
                        y = unit_stack_count_role(unit3,1);
                        if (city7 + y != 0) {
                          local_18 += 8;
                        }
                      }
                    }
                  }
                }
                if (local_144 == 1) {
                  local_18 = rand_range(0,2);
                }
                if (-1 < (char)units[unit].last_dir) {
                  if ((int)(char)units[unit].last_dir == local_60 ||
                      (int)((int)(char)units[unit].last_dir - local_60) < 0) {
                    unit4 = ~((int)(char)units[unit].last_dir - local_60) + 1;
                  }
                  else {
                    unit4 = (int)(char)units[unit].last_dir - local_60;
                  }
                  if (4 < (int)unit4) {
                    unit4 = 8 - unit4;
                  }
                  local_18 += unit4 * unit4 * -2;
                }
                local_118 = 0;
                local_c4 = 0;
                if (((unit3 < 0) &&
                    (city7 = tile_is_ocean(x,y2), city3 = city4, city7 == 0)) &&
                   ((char)unit_types[units[unit].type].role < 5)) {
                  if ((((iVar27 < 4) && ((int)cities[city4].owner != civ)) &&
                      (((*(byte *)&civs[civ].treaties[cities[city4].owner] & 6) != 0
                       && ((*(byte *)&civs[civ].treaties[cities[city4].owner] & 8) ==
                           0)))) &&
                     (((*(byte *)&civs[civ].treaties[cities[city4].owner] & 4) != 0
                      || (city7 = civ_get_attitude(civ,(int)cities[city4].owner),
                         city7 < 0x32)))) {
                    local_70 = map_distance_diag((int)cities[city3].x,(int)cities[city3].y,x
                                                  ,y2);
                    if ((iVar27 < local_70) && (iVar27 < 3)) {
                      local_18 += 5;
                      local_c4 = 1;
                    }
                    if (local_70 < iVar27) goto LAB_0054168e;
                    if (local_70 == iVar27) {
                      local_18 -= 5;
                    }
                  }
                  civ3 = tile_radius_civ(x,y2);
                  if ((((0 < (int)civ3) && (civ3 != civ)) &&
                      ((*(byte *)&civs[civ].treaties[civ3] & 6) != 0)) &&
                     ((*(byte *)&civs[civ].treaties[civ3] & 8) == 0)) {
                    if ((((*(byte *)&civs[civ].treaties[civ3] & 4) != 0) &&
                        ((int)((uint)civs[civ3].reputation -
                              (int)*(char *)((int)civs + civ * 0x595 + 0x48)) < 7)) &&
                       (local_c4 == 0)) goto LAB_0054168e;
                    if ((((*(byte *)&civs[civ].treaties[civ3] & 4) != 0) &&
                        ((int)((uint)civs[civ3].reputation -
                              (int)*(char *)((int)civs + civ * 0x595 + 0x48)) < 7)) ||
                       (city7 = civ_get_attitude(civ,civ3), city7 < 0x32)) {
                      local_18 -= 5;
                      local_14 = tile_improvements(x,y2);
                      if ((local_14 & 0x1c) != 0) {
                        local_18 -= 3;
                      }
                    }
                  }
                }
                if ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0) {
                  local_18 -= 6;
                }
                if (unit3 < 0) {
                  city7 = tile_city_owner(x,y2);
                  if ((-1 < city7) && (civ2 != civ)) {
                    if (((*(byte *)&civs[civ].treaties[civ2] & 0xe) != 0) &&
                       (((civs[civ2].reputation < 7 ||
                         ((*(byte *)&civs[civ].treaties[civ2] & 0x10) == 0)) ||
                        ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0))))
                    goto LAB_0054168e;
                    local_18 = 999;
                    local_a4 = 0;
                    local_90 = 0;
                  }
                  city7 = tile_has_hut(x,y2);
                  if (city7 != 0) {
                    local_18 += 0x14;
                  }
                }
                else {
                  if (civ2 != civ) {
                    local_118 = 1;
                    local_ac = 0;
                    if (((bVar30) || (unit_types[units[unit].type].role == 7)) ||
                       ((((local_144 == 2 && (unit_types[units[unit].type].hold != '\0')) &&
                         (((city7 = tile_is_ocean(x,y2), city7 == 0 &&
                           ((char)unit_types[units[unit].type].attack < 3)) ||
                          ((city7 = unit_stack_sum(unit,2), 1 < city7 &&
                           (((char)unit_types[units[unit].type].attack <=
                             (char)unit_types[units[unit3].type].defense ||
                            ((char)unit_types[units[unit3].type].attack <=
                             (char)unit_types[units[unit].type].defense)))))))) ||
                        ((city7 = tile_is_ocean(x2,y3), city7 != 0 &&
                         ((local_144 == 0 && ((unit_types[units[unit].type].flags & 4) == 0))))
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
                          local_10 = unit_resolve_attack(unit,local_60,0);
                          city7 = unit_stack_sum(unit3,0);
                          local_10 = ((city7 + 1) * local_10) /
                                     (int)(char)unit_types[units[unit].type].cost;
                          city7 = tile_city_owner(x,y2);
                          if (-1 < city7) {
                            local_10 = local_10 * 3;
                          }
                          if ((local_e4 == 2) && (unit_types[units[unit3].type].role == 4))
                          {
                            local_10 = local_10 << 1;
                          }
                          if (local_48 == 0) {
                            if (local_e4 == 0) {
                              if (uVar28 == 0) {
                                local_10 = local_10 << 1;
                              }
                              uVar2 = unit_types[units[unit].type].attack;
                              city7 = unit_stack_sum(unit,3);
                              if ((char)uVar2 * 2 < city7) {
                                local_10 = local_10 << 1;
                                local_ac = 1;
                              }
                              city7 = unit_stack_count_role(unit3,0);
                              if (city7 != 0) {
                                local_10 = local_10 << 1;
                                local_ac = 1;
                              }
                              city7 = civ_ai_goal_get_priority(civ,x2,y3,0);
                              if (city7 != 0) {
                                local_10 = local_10 << 1;
                              }
                            }
                            if ((game.rules & 0x10) != 0) {
                              city7 = unit_max_hp(unit3);
                              y = unit_hp_remaining(unit3);
                              if (y <= city7 / 3) {
                                local_ac = 1;
                                local_10 = local_10 << 1;
                              }
                            }
                            if ((unit_types[units[unit3].type].flags & 8) != 0) {
                              local_10 = local_10 * 3;
                            }
                          }
                          else {
                            local_10 = local_10 / 2;
                            if ((char)unit_types[units[unit3].type].attack <=
                                (char)unit_types[units[unit].type].defense) {
                              local_10 = 0;
                            }
                          }
                          if ((unit_type == 9) &&
                             (4 < (char)unit_types[units[unit3].type].role)) {
                            local_ac = 2;
                          }
                          unit4 = (uptr)(char)unit_types[units[unit3].type].role;
                          if ((civ2 == 0) && (unit4 == 7)) {
                            if ((game.human_players & 1) == 0) {
                              local_10 = local_10 / 2;
                            }
                          }
                          else if ((civ2 == 0) && (4 < (int)unit4)) {
                            local_10 += 0xc;
                          }
                          else if (unit4 == 6) {
                            local_10 = local_10 << 1;
                          }
                          if ((int)((-(uint)(civ2 == 0) & 6) + 6) <= local_10) {
                            local_18 += local_10 * 4;
                            goto LAB_0054314b;
                          }
                          local_18 = -999;
                          if ((((((uVar28 == 0) && (local_e4 == 0)) && (local_144 == 0)) &&
                               (((units[unit3].flags & 0x2000) != 0 ||
                                (units[unit3].orders == 2)))) &&
                              ((3 < (char)terrain_types[terrain].defense ||
                               (uVar10 = tile_improvements(x,y2),
                               ((byte)uVar10 & 0x42) == 0x40)))) &&
                             (((city7 = unit_stack_sum(unit3,2), city7 < 2 &&
                               (city7 = tile_city_owner(x,y2), city7 < 0)) &&
                              (city7 = rand_range(0,3), city7 == 0)))) {
                            unit_bribe(unit3,civ);
                          }
                        }
                        goto LAB_0054168e;
                      }
                      if (local_e4 != 6) {
                        bVar8 = civs[civ2].reputation;
                        city7 = civ_get_attitude(civ,civ2);
                        y = rand_range(0,0x13);
                        if (0x32 < (int)((uint)bVar8 * 5 + city7 + y - 10))
                        goto LAB_005429fe;
                      }
                    }
                    if (((((*(byte *)&civs[civ].treaties[civ2] & 6) == 0) ||
                         (unit_types[units[unit3].type].role != 6)) ||
                        (city7 = unit_stack_sum(unit3,2), city7 != 1)) ||
                       ((unit_types[units[unit].type].attack == '\0' ||
                        (city7 = city_find_nearest(x,y2,-1,0xffffffff,-1),
                        (int)cities[city7].owner != civ)))) {
                      if (local_e4 == 6) {
                        if ((uVar28 == 0) ||
                           ((uVar28 == 5 ||
                            ((*(byte *)&civs[civ].treaties[civ2] & 6) == 0)))) {
LAB_0054272e:
                          if (((local_e4 == 6) || (city2 == city4)) && (2 < game.difficulty))
                          {
LAB_00542801:
                            if (local_144 == 0) {
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
                                       0) && (*(char *)&civs[civ4].continent_cities[iVar11] !=
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
                      else if ((uVar28 == 0) && (local_e4 == 0)) goto LAB_0054272e;
                    }
                    else {
                      local_18 = 0x3c;
                      if (local_38 < 0x3c) {
                        local_fc = 0x3c;
                        local_38 = 0x3c;
                        local_c8 = local_60;
                        local_50 = 1;
                        local_64 = 2;
                      }
                    }
                    goto LAB_0054168e;
                  }
                  local_18 -= (char)unit_types[units[unit].type].defense;
                }
LAB_0054314b:
                if (((local_3c != 0) && (local_144 == 2)) && ((unit3 < 0 || (civ2 == civ)))
                   ) {
                  city7 = tile_landmass(x,y2);
                  y = city_adjacent_sea_info(city2,0,0);
                  if (city7 == y) {
                    local_18 += 10;
                  }
                }
                if ((((local_144 != 1) || (city7 = tile_airbase_owner(x,y2), city7 < 0)
                     ) || (civ2 == civ)) || (-1 < unit3)) {
                  if (local_68 != 0) {
                    x5 = map_wrap_x((char)(&dir_dx_table)[local_60] * 4 + x2);
                    city7 = (char)(&dir_dy_table)[local_60] * 4 + y3;
                    y = map_in_bounds(x5,city7);
                    if ((y != 0) &&
                       (y = tile_visible_to(x5,city7,civ), y == 0)) {
                      y = tile_is_ocean(x5,city7);
                      if (y == 0) {
                        local_18 += 8;
                      }
                      else {
                        local_18 += 2;
                      }
                    }
                    for (local_7c = 0; (int)local_7c < 8; local_7c++) {
                      x3 = map_wrap_x((char)(&dir_dx_table)[local_7c] + x5);
                      y = (char)(&dir_dy_table)[local_7c] + city7;
                      iVar26 = map_in_bounds(x3,y);
                      if (iVar26 != 0) {
                        iVar26 = tile_visible_to(x3,y,civ);
                        if ((iVar26 == 0) &&
                           ((iVar26 = tile_is_ocean(x3,y), iVar26 == 0 ||
                            (local_144 == 2)))) {
                          local_18 += 2;
                        }
                        iVar26 = tile_unit_owner(x3,y);
                        if (-1 < iVar26) {
                          local_18 -= 2;
                        }
                        if (bVar30) {
                          bVar8 = tile_terrain(x3,y);
                          local_18 += (char)terrain_types[bVar8].food;
                          if ((game.multiplayer != '\0') && (mp_double_production != 0)) {
                            bVar8 = tile_terrain(x3,y);
                            local_18 += (char)terrain_types[bVar8].food;
                          }
                        }
                      }
                    }
                  }
                  if ((y2 == 0) || ((int)map.height - 1U == y2)) {
                    local_18 = local_18 / 3;
                  }
                  city7 = local_18;
                  if (((local_118 != 0) &&
                      (y = unit_moves_left(unit),
                      y < (int)(uint)cosmic.road_move_mult)) &&
                     (y = tile_city_owner(x,y2), y < 0)) {
                    y = unit_stack_sum(unit,0);
                    uVar33 = 99;
                    uVar10 = 1;
                    x = unit_stack_sum(unit,3);
                    iVar26 = int_clamp(x,uVar10,uVar33);
                    local_18 = (y / iVar26) * local_18;
                  }
                  if (local_38 < local_18) {
                    local_38 = local_18;
                    local_c8 = local_60;
                    local_50 = local_118;
                    local_64 = local_ac;
                  }
                  if (local_fc < city7) {
                    local_fc = city7;
                  }
                }
              }
            }
          }
LAB_0054168e: ;
        }
        if ((local_50 != 0) &&
           (city7 = (uint)cosmic.road_move_mult - local_64, iVar27 = unit_moves_left(unit),
           iVar27 < city7)) {
          local_c8 = 8;
        }
        if (local_fc != local_38) {
          local_c8 = 8;
        }
        if (local_c8 == 8) {
          local_50 = 0;
        }
        if ((local_a4 != 0) && (local_50 == 0)) goto LAB_005436c1;
        if ((local_90 != 0) && (local_50 == 0)) {
          local_c8 = 8;
        }
        units[unit].field_0c = '9';
        city3 = local_c8;
      }
      else {
        local_c8 = 8;
        city3 = local_c8;
      }
    }
  }
  else {
    units[unit].flags = units[unit].flags | 8;
    units[unit].field_0c = 'd';
    local_c8 = 8;
    city3 = local_c8;
  }
LAB_005435ca:
  local_c8 = city3;
  if (local_c8 == 8) {
    units[unit].last_dir = 0xff;
    units[unit].orders = -1;
  }
  else {
    x2 = map_wrap_x((char)(&dir_dx_table)[local_c8] + x2);
    y3 += (char)(&dir_dy_table)[local_c8];
    iVar27 = map_in_bounds(x2,y3);
    if (iVar27 == 0) {
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
      units[unit].field_0c = '0';
    }
    if (unit_types[units[unit].type].domain == 1) {
      units[unit].orders = -1;
      units[unit].moves_used += cosmic.road_move_mult;
      return 1;
    }
    unit_exhaust_moves(unit);
    if ((local_144 == 0) && (unit_types[units[unit].type].role != 5)) {
      units[unit].orders = 1;
      if ((units[unit].flags & 0x100) != 0) {
        units[unit].orders = 2;
      }
      if (bVar5) {
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
        iVar27 = unit_stack_count_role(unit,4);
        if (iVar27 != 0) {
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
     ((local_e4 != 7 ||
      (city7 = tile_city_owner((int)units[unit].goto_x,(int)units[unit].goto_y),
      city7 < 0)))) {
    local_c4 = 0;
    units[unit].orders = -1;
  }
LAB_00540fea:
  if (local_c4 != 0) goto LAB_005436c1;
LAB_00541001:
  if ((((local_e4 == 1) && (terrain2 != 10)) && (local_a4 == 0)) && (!bVar4)) {
    local_c4 = 0;
    city7 = unit_stack_sum(unit,2);
    if ((city7 < 2) && (local_3c < 4)) {
      local_c4 = local_c4 | 1;
    }
    if (((local_158 != 0) && (city7 = unit_stack_count_role(unit,1), city7 == 1)) &&
       ((((int)city4 < 0 ||
         (((city4 == city2 || (4 < iVar27)) ||
          ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + cities[city4].owner * 4) & 0x20) != 0)))) ||
        (6 < (int)((uint)civs[cities[city4].owner].reputation -
                  (int)civs[civ].field_48[cities[city4].owner]))))) {
      local_c4 = local_c4 | 2;
    }
    if ((local_f4 != 0) || (local_bc != 0)) {
      city7 = unit_stack_count_role(unit,1);
      if (city7 == 1) {
        local_c4 = local_c4 | 4;
      }
      if ((local_c4 != 0) || ((units[unit].flags & 0x100) != 0)) {
        local_c4 = local_c4 | 8;
      }
    }
    terrain = local_c4;
    if (((char)unit_types[unit_type].defense <= (char)unit_types[unit_type].attack) &&
       (terrain = local_c4 & 0xfffffffe,
       (char)unit_types[unit_type].defense < (char)unit_types[unit_type].attack)) {
      terrain = local_c4 & 0xfffffff4;
    }
    local_c4 = terrain;
    civ2 = tile_radius_civ(x2,y3);
    if ((((0 < (int)civ2) && (civ2 != civ)) &&
        ((*(byte *)&civs[civ].treaties[civ2] & 4) != 0)) &&
       ((int)((uint)civs[civ2].reputation - (int)civs[civ].field_48[civ2])
        < 7)) {
      local_c4 = 0;
    }
    if (local_c4 != 0) {
      if ((local_c4 & 0xc) != 0) {
        civ_clear_standing_goals_near(civ,1,x2,y3,1);
      }
      units[unit].field_0c = 'F';
      if ((char)unit_types[unit_type].attack < (char)unit_types[unit_type].defense) {
        local_c8 = 8;
        city3 = local_c8;
        goto LAB_005435ca;
      }
      local_90 = 1;
      goto LAB_005414d7;
    }
  }
  if (((bVar29) &&
      (*(short *)(&landmass_fertile_tiles + iVar11 * 0x10) >> 3 <
       (short)(ushort)civs[civ].continent_cities[iVar11])) &&
     (units[unit].home_city != -1)) {
    if ((local_3c == 0) && (cities[city2].size < '\n')) {
      cities[city2].size++;
      unit_destroy_redraw(unit,1);
      city_window_refresh_if_city((FrameWindow *)&city_window,city2);
      map_redraw_area_all_views(x2,y3,1,1,1);
      return 1;
    }
    if (((-1 < (int)city2) && (iVar11 == local_58)) && (cities[city2].size < '\n')) {
      unit_set_goto(unit,0x42,(int)cities[city2].x,(int)cities[city2].y);
      goto LAB_005436c1;
    }
  }
  goto LAB_005414d7;
}
#undef mp_double_production
#undef scenario_flags
#undef local_188
#undef x4
#undef local_170
#undef local_16c
#undef unit
#undef city6
#undef local_158
#undef civ4
#undef local_144
#undef local_140
#undef city
#undef local_11c
#undef local_118
#undef local_114
#undef local_110
#undef y4
#undef local_104
#undef local_fc
#undef local_f4
#undef local_f0
#undef y3
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef x2
#undef x3
#undef unit4
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef unit5
#undef local_94
#undef local_90
#undef x6
#undef city4
#undef local_84
#undef terrain2
#undef local_7c
#undef civ2
#undef y2
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef civ3
#undef local_58
#undef unit3
#undef local_50
#undef local_4c
#undef local_48
#undef city5
#undef city2
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

/* 00543cd6 auto */
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
#define scenario_flags (*(short *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl ai_process_civ_units(void)

{
  bool bVar1;
  i16 iVar2;
  int civ;
  int iVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (int)game.turn_civ;
  bVar1 = false;
  if (((((game.game_flags & 0x80) != 0) && (((int)scenario_flags & 0x8000U) != 0)) && (game.turn == 1)
      ) && (scenario_objective_civ == civ)) {
    bVar1 = true;
  }
  local_c = 0;
  do {
    if (1 < local_c) {
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
         ((local_14 = 0, !bVar1 ||
          ((local_c != 0 || (unit_types[units[unit].type].domain == 1)))))) {
        while (iVar4 = unit_is_awake_with_moves(unit), iVar4 != 0) {
          if (2 < game.multiplayer) {
            net_send_state_diff(0xff,2,0,0,0);
            XD_FlushSendBuffer(5000);
            net_process_messages((NetSession *)&net_session,1,0);
          }
          iVar2 = game.num_units;
          game.active_unit = (i16)unit;
          unit_continue_active_orders();
          if (game.num_units != iVar2) break;
          if ((units[unit].orders != 11) &&
             (unit_types[units[unit].type].domain != 1)) {
            local_14++;
          }
          local_14++;
          if (0x14 < local_14) {
            unit_exhaust_moves(unit);
            break;
          }
          if ((((local_c == 0) && (civ != 0)) && (unit_types[units[unit].type].hold != '\0'))
             && (((iVar4 = unit_moves_left(unit), iVar4 == 0 &&
                  (iVar4 = tile_is_ocean((int)units[unit].x,(int)units[unit].y), iVar4 != 0)
                  ) && ((iVar4 = unit_stack_sum(unit,2), 1 < iVar4 &&
                        (((game.human_players & units[unit].visibility) != 0 ||
                         (iVar4 = tile_adjacent_nonallied_civ((int)units[unit].x,(int)units[unit].y,
                                                     civ), iVar4 != 0)))))))) {
            unit_continue_active_orders();
          }
        }
        mapviews_redraw_cursor();
      }
    }
    local_c++;
  } while( true );
}
#undef net_host_handoff_stage
#undef player_has_quit
#undef scenario_flags
#undef scenario_objective_civ
#undef unit
#undef local_14
#undef local_c

/* 0057febc auto */
#define path_goal_x (*(iptr *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(iptr *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(int *)((u8 *)&g.d_0062d044))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl ai_respond_to_attack(iptr civ,iptr x,iptr y)

{
  int civ2;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit = 0;
  while( true ) {
    if (game.num_units <= unit) {
      civ2 = tile_owner(x,y);
      iVar2 = tile_landmass(x,y);
      for (unit = 0; unit < game.num_units; unit++) {
        if (((units[unit].id != 0) &&
            ((((units[unit].owner == civ ||
               (((units[unit].owner != civ2 &&
                 ((*(byte *)&civs[civ].treaties[units[unit].owner] & 8) != 0)) &&
                (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) == 0)))) &&
              (((unit_types[units[unit].type].domain == '\0' &&
                (unit_types[units[unit].type].attack != '\0')) &&
               (iVar3 = unit_moves_left(unit), iVar3 != 0)))) &&
             ((unit_types[units[unit].type].role != 1 ||
              (iVar3 = tile_city_owner((int)units[unit].x,(int)units[unit].y), iVar3 < 0))))
            )) && ((iVar3 = map_distance(x,y,(int)units[unit].x,
                                               (int)units[unit].y), iVar3 < 7 &&
                   (iVar3 = tile_landmass((int)units[unit].x,(int)units[unit].y),
                   iVar3 == iVar2)))) {
          path_owner_civ = (int)units[unit].owner;
          path_unit_type = (iptr)units[unit].type;
          path_goal_x = x;
          path_goal_y = y;
          iVar3 = unit_moves_left(unit);
          iVar3 = map_path_next_dir((int)units[unit].x,(int)units[unit].y,iVar3 * 2);
          if ((0 < iVar3) && (iVar3 != 8)) {
            units[unit].orders = 11;
            units[unit].goto_x = (i16)x;
            units[unit].goto_y = (i16)y;
            units[unit].field_0c = 'K';
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
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(16)))
i32 __cdecl ai_spaceship_race_behind(iptr civ)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = spaceship_race_active();
  if ((((iVar1 != 0) && (iVar2 = civ_spaceship_launched(civ), iVar2 == 0)) &&
      ((game.game_flags & 2) == 0)) &&
     ((game.difficulty != '\0' && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0))))
  {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
         (iVar3 = civ_spaceship_launched(civ2), iVar3 != 0)) {
        return 1;
      }
    }
    local_18 = 0;
    for (local_10 = 0; local_10 < 6; local_10++) {
      iVar3 = int_clamp((local_10 + 1) / 2,0,2);
      local_18 = local_18 +
                 (int)civs[civ].spaceship_parts[local_10] *
                 (uint)improvements[iVar3 + 0x23].cost;
    }
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
          (iVar3 = civ_has_advance(civ2,0x4c), iVar3 != 0)) && (civ2 != civ)) {
        local_c = 0;
        for (local_10 = 0; local_10 < 6; local_10++) {
          iVar3 = int_clamp((local_10 + 1) / 2,0,2);
          local_c = local_c + (int)civs[civ2].spaceship_parts[local_10] *
                              (uint)improvements[iVar3 + 0x23].cost;
        }
        if (local_18 <= local_c) {
          return 1;
        }
      }
    }
  }
  return 0;
}
#undef local_18
#undef local_10
#undef local_c
#undef civ2

/* 005b68f6 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
i32 __cdecl ai_tile_improve_choice(iptr civ,iptr x,i32 y)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = tile_city_owner(x,y);
  if (((iVar2 < 0) && (uVar3 = tile_improvements(x,y), (uVar3 & 8) == 0)) &&
     (((uVar3 & 4) == 0 || (iVar2 = civ_has_advance(civ,0x46), iVar2 != 0)))) {
    bVar1 = tile_terrain(x,y);
    uVar4 = (uint)bVar1;
    for (local_c = 0; local_c < 2; local_c++) {
      if (local_c == 0) {
        iVar2 = tile_has_irrigation_source(x,y);
        if (iVar2 == 0) {
          return 0;
        }
      }
      else if ((uVar3 & 4) != 0) {
        return 0;
      }
      if (((*(char *)(local_c + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + uVar4 * 0x18) != -1) &&
          (*(char *)(local_c + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + uVar4 * 0x18) != '\0')) &&
         ((int)*(char *)(local_c + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + uVar4 * 0x18) <= (int)(uint)civs[civ].government))
      {
        return local_c + 1;
      }
    }
  }
  return 0;
}
#undef local_c
