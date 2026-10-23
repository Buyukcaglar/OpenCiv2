/* The game, the world map: terrain, generation, visibility: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 004087c0 auto */
i32 __cdecl map_in_bounds(iptr param_1,iptr param_2)

{
  i32 uVar1;
  
  if ((((param_2 < 0) || (map.height <= param_2)) || (param_1 < 0)) || (map.width <= param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 00408830 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl map_fill_tile_byte(iptr param_1,i32 param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < map.area; local_8++) {
    *(i8 *)param_1 = (i8)param_2;
    param_1 += 6;
  }
  return;
}
#undef local_8

/* 00408903 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl map_copy_tile_byte(iptr param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < map.area; local_8++) {
    *(i8 *)param_1 = *(i8 *)param_2;
    param_2 += 6;
    param_1 += 6;
  }
  return;
}
#undef local_8

/* 0040897f auto */
#define local_84 (*(uptr *)(frame_ + FRAME_OFF(4)))
#define aiStack_80 (*(int (*)[22])(frame_ + FRAME_OFF(8)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(96)))
#define y3 (*(uint *)(frame_ + FRAME_OFF(100)))
#define x3 (*(uint *)(frame_ + FRAME_OFF(104)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(108)))
#define y2 (*(int *)(frame_ + FRAME_OFF(112)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(116)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(120)))
#define local_c (*(int *)(frame_ + FRAME_OFF(124)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(128)))
void __cdecl mapgen_calc_fertility(void)

{
  byte bVar1;
  iptr iVar2;
  int iVar4;
  byte *pbVar5;
  iptr terrain;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_28 = 0; local_28 < 0x40; local_28++) {
    *(i16 *)(&landmass_fertile_tiles + local_28 * 0x10) = 0;
  }
  for (terrain2 = 0; (int)terrain2 < 0x16; terrain2++) {
    terrain = (int)terrain2 % 0xb;
    aiStack_80[terrain2] =
         (char)terrain_types[terrain2].food * 3 + (int)(char)terrain_types[terrain2].trade;
    if (terrain != 2) {
      aiStack_80[terrain2] += (char)terrain_types[terrain2].shields * 2;
    }
    if (terrain_types[terrain].mine_to == -2) {
      if (terrain == 4) {
        aiStack_80[terrain2] += 3;
      }
      else {
        aiStack_80[terrain2]++;
      }
    }
    else if (terrain_types[terrain].irrigate_to == -2) {
      aiStack_80[terrain2] += 2;
    }
  }
  for (y3 = 0; (int)y3 < (int)map.height; y3++) {
    for (x3 = (uint)((y3 & 1) != 0); (int)x3 < (int)map.width;
        x3 = x3 + 2) {
      bVar1 = tile_terrain(x3,y3);
      terrain2 = (uptr)bVar1;
      if ((terrain2 == 2) || (terrain2 == 1)) {
        local_c = 0;
        for (local_10 = 0; local_10 < 0x15; local_10++) {
          local_8 = 0;
          x2 = map_wrap_x((int)(char)(&city_tile_dx_table)[local_10] + x3);
          y2 = (int)(char)(&city_tile_dy_table)[local_10] + y3;
          iVar2 = map_in_bounds(x2,y2);
          if (iVar2 != 0) {
            bVar1 = tile_terrain(x2,y2);
            local_84 = (uptr)bVar1;
            if ((local_84 == 2) && (iVar4 = tile_grassland_has_shield(x2,y2), iVar4 != 0)) {
              local_8 += 2;
            }
            iVar4 = tile_resource(x2,y2);
            if ((iVar4 != 0) && (local_10 != 0x14)) {
              local_84 += 0xb;
            }
            local_8 += aiStack_80[local_84];
            pbVar5 = (byte *)tile_at(x2,y2);
            if ((*pbVar5 & 0x80) != 0) {
              local_8++;
            }
            if (((local_10 < 8) || (iVar4 = local_8, local_10 == 0x14)) &&
               (iVar4 = local_8 * 2, local_10 == 0x14)) {
              local_8 = local_8 * 4;
              pbVar5 = (byte *)tile_at(x2,y2);
              iVar4 = local_8;
              if ((*pbVar5 & 0x80) != 0) {
                iVar4 = local_8 + local_8 / 2;
              }
            }
            local_8 = iVar4;
            local_c += local_8;
          }
        }
        if ((terrain2 != 1) && (iVar4 = tile_grassland_has_shield(x3,y3), iVar4 == 0)) {
          local_c -= 0x10;
        }
        iVar4 = int_clamp(local_c - 0x78 >> 3,1,0xf);
        local_8 = (iVar4 >> 1) + 8;
        local_28 = tile_landmass(x3,y3);
        if (-1 < local_28) {
          *(short *)(&landmass_fertile_tiles + local_28 * 0x10) =
               *(short *)(&landmass_fertile_tiles + local_28 * 0x10) + 1;
        }
        iVar4 = tile_at(x3,y3);
        *(char *)(iVar4 + 5) = (char)local_8 - 0x10;
      }
      else {
        iVar4 = tile_at(x3,y3);
        *(i8 *)(iVar4 + 5) = 0xf0;
      }
    }
  }
  return;
}
#undef local_84
#undef aiStack_80
#undef local_28
#undef y3
#undef x3
#undef terrain2
#undef y2
#undef x2
#undef local_10
#undef local_c
#undef local_8

/* 00408d33 auto */
#define mapgen_min_x (*(i32 *)((u8 *)&g.d_0063cb9c))
#define mapgen_min_y (*(i32 *)((u8 *)&g.d_0063cba0))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define local_3ec (*(int *)(frame_ + FRAME_OFF(4)))
#define local_3e4 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_3dc (*(int *)(frame_ + FRAME_OFF(20)))
#define local_3d4 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_3bc (*(int *)(frame_ + FRAME_OFF(52)))
#define local_3b8 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_3b4 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_3b0 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_3ac (*(int *)(frame_ + FRAME_OFF(68)))
#define local_398 (*(iptr *)(frame_ + FRAME_OFF(88)))
#define local_390 (*(uptr *)(frame_ + FRAME_OFF(96)))
#define local_388 (*(int (*)[11])(frame_ + FRAME_OFF(104)))
#define local_35c (*(uint *)(frame_ + FRAME_OFF(148)))
#define local_358 (*(int *)(frame_ + FRAME_OFF(152)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(156)))
#define local_350 (*(Dialog *)(frame_ + FRAME_OFF(160)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(916)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(920)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(924)))
#define local_50 (*(Tile * *)(frame_ + FRAME_OFF(928)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(932)))
#define local_48 (*(uint *)(frame_ + FRAME_OFF(936)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(940)))
#define local_40 (*(uptr *)(frame_ + FRAME_OFF(944)))
#define y3 (*(int *)(frame_ + FRAME_OFF(948)))
#define local_38 (*(uint *)(frame_ + FRAME_OFF(952)))
#define local_34 (*(Tile * *)(frame_ + FRAME_OFF(956)))
#define local_30 (*(uptr *)(frame_ + FRAME_OFF(960)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(964)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(968)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(972)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(976)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(980)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(984)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(988)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(992)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(996)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1000)))
void __cdecl map_generate(int param_1)

{
  u8 uVar1;
  byte bVar2;
  iptr x;
  uint uVar4;
  iptr iVar5;
  i8 *puVar5;
  iptr iVar6;
  int iVar7;
  uptr uVar7;
  uptr uVar8;
  uint uVar9;
  int iVar10;
  i8 frame_[FRAME_OFF(1008)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_350,0x4000);
  local_8 = 0;
  dlg_reset(&local_350,8);
  dialog_set_position
            ((C_0040bc40_28 *)&local_350,
             -(((int)(screen_width - 0x280 + (screen_width - 0x280 >> 0x1f & 7U)) >> 3) + 1),
             -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
  x = label_string(*(i32 *)(label_string_ids + 8));
  dialog_set_title((DialogWindowView *)&local_350,x);
  dialog_set_width((DialogWindowView *)&local_350,0x100);
  dialog_add_line
            ((DialogAddLineView *)&local_350,ADDR(0x624efc, ((u8 *)&g.d_00624efc)),0xffffffff,0xffffffff,0xffffffff,0);
  text_clear();
  text_append(ADDR(0x624f00, ((u8 *)&g.d_00624f00)));
  text_append_label(8);
  dialog_add_line
            ((DialogAddLineView *)&local_350,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
  dialog_add_line
            ((DialogAddLineView *)&local_350,ADDR(0x624f04, ((u8 *)&g.d_00624f04)),0xffffffff,0xffffffff,0xffffffff,0);
  dlg_show_modal(&local_350,0);
  wnd_set_cursor((WndBase *)(local_350.field_0 + 0x48),0x200);
  wnd_set_cursor((WndBase *)&main_frame_wnd,0x200);
  ui_flush_input();
  if (param_1 == 0) {
    for (local_398 = 0; local_398 < 0x15; local_398++) {
      start_x[local_398] = -1;
      start_y[local_398] = -1;
    }
    map_new_seed();
    if ((game.rules & 0x8000) != 0) {
      mapgen_climate = mapgen_climate << 1;
      mapgen_temperature = mapgen_temperature << 1;
    }
    map.flat = game.rules & 0x8000;
    map_alloc();
    mapgen_land_placed = 0;
    map_fill_tile_byte((iptr)map_tiles,10);
    map_fill_tile_byte((iptr)&map_tiles->improvements,0);
    mapgen_min_y = 0;
    mapgen_max_y = map.height - 1;
    mapgen_min_x = 3;
    mapgen_max_x = map.width - 3;
    uVar4 = _rand();
    uVar7 = (int)uVar4 >> 0x1f;
    local_44 = ((uVar4 ^ uVar7) - uVar7 & 1 ^ uVar7) - uVar7;
    if (local_44 == 0) {
      mapgen_max_y = map.height - 5;
    }
    else {
      mapgen_min_y = 4;
    }
    iVar7 = mapgen_land_form;
    if (mapgen_land_form < 1) {
      iVar7 = 0;
    }
    local_20 = ((int)map.height * (int)map.width >> 1) / 400;
    local_14 = (local_20 * ((mapgen_land_mass * 8 + 8 + iVar7 * 8) * 5 + 0x50) * 8) / 10;
    do {
      mapgen_add_landmass(0);
    } while (mapgen_land_placed < local_14);
    map_assign_landmass_ids();
    local_358 = 0;
    for (local_48 = 0; (int)local_48 < 0x40; local_48++) {
      if (*(short *)(&landmass_table + local_48 * 0x10) != 0) {
        local_358++;
      }
    }
    local_24 = 0x40 - (local_358 + 1);
    if (0 < local_24) {
      for (local_48 = 0; (int)local_48 < local_24; local_48++) {
        mapgen_add_landmass(1);
      }
    }
    for (y2 = 1; (int)y2 < map.height - 2; y2++) {
      for (x2 = y2 & 1; (int)x2 < map.width - 2; x2 += 2) {
        local_38 = 0;
        iVar7 = tile_at(x2,y2);
        if (*(char *)(iVar7 + 1) != '\0') {
          local_38 = local_38 | 1;
        }
        iVar7 = tile_at(x2 + 1,y2 + 1);
        if (*(char *)(iVar7 + 1) != '\0') {
          local_38 = local_38 | 2;
        }
        iVar7 = tile_at(x2 + 1,y2 - 1);
        if (*(char *)(iVar7 + 1) != '\0') {
          local_38 = local_38 | 4;
        }
        iVar7 = tile_at(x2 + 2,y2);
        if (*(char *)(iVar7 + 1) != '\0') {
          local_38 = local_38 | 8;
        }
        if ((local_38 == 6) || (local_38 == 9)) {
          iVar7 = tile_at(x2 + 1,y2 + 1);
          *(i8 *)(iVar7 + 1) = 1;
          iVar7 = tile_at(x2 + 1,y2 - 1);
          *(i8 *)(iVar7 + 1) = 1;
          iVar7 = tile_at(x2 + 2,y2);
          *(i8 *)(iVar7 + 1) = 1;
          if (((int)x2 < 2) || ((int)y2 < 2)) {
            if ((int)y2 < 2) {
              if (1 < (int)x2) {
                x2 -= 2;
              }
            }
            else {
              y2--;
              x2++;
            }
          }
          else {
            x2--;
            y2--;
          }
        }
      }
    }
    ui_pump_messages_net();
    if ((game.rules & 0x8000) == 0) {
      local_4c = (int)map.height / 0xc;
    }
    else {
      local_4c = (int)((int)map.height + ((int)map.height >> 0x1f & 7U)) >> 3;
    }
    if (local_4c < 3) {
      local_4c = 2;
    }
    local_50 = map_tiles;
    y2 = 0;
    x2 = 0;
    for (local_30 = 0; (int)local_30 < (int)map.area; local_30++) {
      local_35c = (uint)local_50->improvements;
      if (local_35c == 0) {
        local_38 = 10;
      }
      else if (local_35c == 1) {
        local_58 = mapgen_temperature * -3;
        if ((game.rules & 0x8000) != 0) {
          local_58 = mapgen_temperature * -6;
        }
        iVar10 = ((int)map.height >> 1) + 8;
        uVar4 = _rand();
        uVar8 = (int)uVar4 >> 0x1f;
        iVar7 = y2 + (((uVar4 ^ uVar8) - uVar8 & 0xf ^ uVar8) - uVar8) + 1;
        if (iVar10 == iVar7 || iVar10 - iVar7 < 0) {
          iVar7 = (int)map.height;
          uVar4 = _rand();
          uVar9 = (int)uVar4 >> 0x1f;
          local_28 = ~(((iVar7 >> 1) + 8) -
                      (y2 + (((uVar4 ^ uVar9) - uVar9 & 0xf ^ uVar9) - uVar9) + 1)) + 1;
        }
        else {
          iVar7 = (int)map.height;
          uVar4 = _rand();
          uVar9 = (int)uVar4 >> 0x1f;
          local_28 = ((iVar7 >> 1) + 8) -
                     (y2 + (((uVar4 ^ uVar9) - uVar9 & 0xf ^ uVar9) - uVar9) + 1);
        }
        local_28 += local_58;
        if (local_28 < 1) {
          local_28 = 0;
        }
        local_28 = local_28 / local_4c;
        switch(local_28) {
        case 0:
          local_38 = 0;
          break;
        case 1:
        case 2:
        case 3:
          local_38 = 1;
          break;
        case 4:
          uVar4 = _rand();
          uVar9 = (int)uVar4 >> 0x1f;
          if (((uVar4 ^ uVar9) - uVar9 & 1 ^ uVar9) == uVar9) {
            local_38 = 1;
          }
          else {
            local_38 = 6;
          }
          break;
        case 5:
        case 6:
          local_38 = 6;
          break;
        default:
          local_38 = 7;
        }
      }
      else if (local_35c == 2) {
        local_38 = 4;
      }
      else {
        local_38 = 5;
      }
      local_50->terrain = (u8)local_38;
      local_50++;
      x2 += 2;
      if ((int)map.width <= (int)x2) {
        y2++;
        x2 = y2 & 1;
      }
      ui_pump_messages_net();
    }
    local_50 = map_tiles;
    local_34 = map_tiles + map.area - 1;
    for (y2 = 0; (int)y2 < (int)map.height; y2++) {
      if ((int)map.height >> 1 == y2 || (int)(((int)map.height >> 1) - y2) < 0) {
        local_28 = ~(((int)map.height >> 1) - y2) + 1;
      }
      else {
        local_28 = ((int)map.height >> 1) - y2;
      }
      if ((int)map.height >> 2 == local_28 || ((int)map.height >> 2) - local_28 < 0) {
        local_3ac = ~(((int)map.height >> 2) - local_28) + 1;
      }
      else {
        local_3ac = ((int)map.height >> 2) - local_28;
      }
      if (mapgen_climate * 4 + 4 + local_3ac < 1) {
        local_54 = 0;
      }
      else {
        if ((int)map.height >> 2 == local_28 || ((int)map.height >> 2) - local_28 < 0) {
          local_3b0 = ~(((int)map.height >> 2) - local_28) + 1;
        }
        else {
          local_3b0 = ((int)map.height >> 2) - local_28;
        }
        local_54 = _rand();
        local_54 = local_54 % (mapgen_climate * 4 + local_3b0 + 5);
      }
      for (x2 = (uint)((y2 & 1) != 0); (int)x2 < (int)map.width;
          x2 = x2 + 2) {
        uVar1 = local_50->terrain;
        if (uVar1 == '\n') {
          if ((int)map.height >> 2 == local_28 || ((int)map.height >> 2) - local_28 < 0) {
            local_3b4 = ~(((int)map.height >> 2) - local_28) + 1;
          }
          else {
            local_3b4 = ((int)map.height >> 2) - local_28;
          }
          if (local_54 < mapgen_climate * 4 + 4 + local_3b4) {
            local_54++;
          }
        }
        else if (0 < local_54) {
          if (mapgen_climate * -2 != -6 && -1 < mapgen_climate * -2 + 6) {
            iVar7 = _rand();
            local_54 -= iVar7 % (mapgen_climate * -2 + 7);
          }
          switch(uVar1) {
          case '\0':
            local_50->terrain = 1;
            break;
          case 1:
            local_50->terrain = 2;
            break;
          case 4:
            local_50->terrain = 3;
            break;
          case 5:
            local_54 -= 3;
            break;
          case 6:
            local_50->terrain = 3;
          }
        }
        local_50++;
      }
      local_54 = 0;
      for (x2 = (int)map.width - ((y2 & 1) + 1); -1 < (int)x2;
          x2 = x2 - 2) {
        uVar1 = local_34->terrain;
        if (uVar1 == '\n') {
          if (local_54 < (local_28 >> 1) + mapgen_climate + 1) {
            local_54++;
          }
        }
        else if (0 < local_54) {
          iVar7 = -(mapgen_climate * 2 + 2);
          if (iVar7 != -6 && -1 < iVar7 + 6) {
            iVar7 = _rand();
            local_54 -= iVar7 % (7 - (mapgen_climate * 2 + 2));
          }
          switch(uVar1) {
          case '\0':
            local_34->terrain = 1;
            break;
          case 1:
            local_34->terrain = 2;
            break;
          case 2:
            if (local_28 < (map.height * 3) / 10) {
              if (local_28 < 10) {
                local_34->terrain = '\t';
              }
              else {
                local_34->terrain = 8;
              }
            }
            else {
              local_34->terrain = 3;
            }
            local_54 -= 2;
            break;
          case 4:
            local_34->terrain = 3;
            break;
          case 5:
            local_54 -= 3;
            break;
          case 6:
            local_34->terrain = 1;
            break;
          case 8:
            local_34->terrain = 3;
          }
        }
        local_34--;
      }
      ui_pump_messages_net();
    }
    for (local_48 = 0; (int)local_48 < (mapgen_age * 5 + 10) * 0xa0; local_48++) {
      if ((local_48 & 1) == 0) {
        if (map.height == 1 || map.height - 1 < 0) {
          y2 = 0;
        }
        else {
          iVar7 = _rand();
          y2 = iVar7 % (int)map.height;
        }
        if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
          local_3b8 = 0;
        }
        else {
          local_3b8 = _rand();
          local_3b8 = local_3b8 % ((int)map.width / 2);
        }
        x2 = (y2 & 1) + local_3b8 * 2;
      }
      else {
        uVar4 = _rand();
        uVar9 = (int)uVar4 >> 0x1f;
        iVar7 = ((uVar4 ^ uVar9) - uVar9 & 7 ^ uVar9) - uVar9;
        x2 = map_wrap_x((int)(char)(&dir_dx_table)[iVar7] + x2);
        y2 += (int)(char)(&dir_dy_table)[iVar7];
      }
      if ((int)map.height >> 1 == y2 || (int)(((int)map.height >> 1) - y2) < 0) {
        local_28 = ~(((int)map.height >> 1) - y2) + 1;
      }
      else {
        local_28 = ((int)map.height >> 1) - y2;
      }
      iVar7 = map_in_bounds(x2,y2);
      if (iVar7 != 0) {
        local_50 = (Tile *)tile_at(x2,y2);
        switch(local_50->terrain) {
        case '\0':
          local_50->terrain = 1;
          break;
        case 1:
          local_50->terrain = 4;
          break;
        case 2:
          local_50->terrain = 3;
          break;
        case 3:
          if (local_28 < (map.height * 3) / 10) {
            local_50->terrain = '\t';
          }
          else {
            local_50->terrain = 1;
          }
          break;
        case 4:
          local_50->terrain = 5;
          break;
        case 5:
          mapgen_try_place_lake(x2,y2);
          break;
        case 6:
          local_50->terrain = 4;
          break;
        case 7:
          local_50->terrain = 5;
          break;
        case 8:
          local_50->terrain = 2;
          break;
        case '\t':
          local_50->terrain = 8;
        }
      }
    }
    ui_pump_messages_net();
    for (local_48 = 0; (int)local_48 < (3 - (mapgen_age + 2)) * 800; local_48++) {
      if ((local_48 & 1) == 0) {
        if (map.height == 1 || map.height - 1 < 0) {
          y2 = 0;
        }
        else {
          iVar7 = _rand();
          y2 = iVar7 % (int)map.height;
        }
        if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
          local_3bc = 0;
        }
        else {
          local_3bc = _rand();
          local_3bc = local_3bc % ((int)map.width / 2);
        }
        x2 = (y2 & 1) + local_3bc * 2;
        local_390 = 0xffffffff;
      }
      else {
        uVar4 = _rand();
        uVar9 = (int)uVar4 >> 0x1f;
        iVar7 = ((uVar4 ^ uVar9) - uVar9 & 7 ^ uVar9) - uVar9;
        x2 = map_wrap_x((int)(char)(&dir_dx_table)[iVar7] + x2);
        y2 += (int)(char)(&dir_dy_table)[iVar7];
      }
      iVar7 = map_in_bounds(x2,y2);
      if ((iVar7 != 0) && (iVar7 = tile_is_ocean(x2,y2), iVar7 == 0)) {
        bVar2 = tile_terrain(x2,y2);
        local_40 = (uptr)bVar2;
        if (((int)local_390 < 0) || (local_390 != local_40)) {
          local_2c = (uint)(2 < local_40);
          local_50 = (Tile *)tile_at(x2,y2);
          for (local_40 = 0; (int)local_40 < 0xb; local_40++) {
            local_388[local_40] = 0;
          }
          if (mapgen_climate == -1) {
            local_388[0]++;
            local_388[1]++;
            local_388[8]--;
          }
          else if (mapgen_climate == 1) {
            local_388[2]++;
            local_388[8]++;
            if (-1 < mapgen_temperature) {
              local_388[9]++;
            }
          }
          if (mapgen_temperature == -1) {
            local_388[6]++;
            local_388[3]++;
            local_388[0]--;
          }
          else if (mapgen_temperature == 1) {
            local_388[1]++;
            local_388[6]--;
            local_388[7]--;
            if (mapgen_climate == -1) {
              local_388[2]--;
              local_388[9]--;
            }
          }
          for (local_30 = 0; (int)local_30 < 8; local_30++) {
            x = map_wrap_x((int)(char)(&dir_dx_table)[local_30] + x2);
            y3 = (int)(char)(&dir_dy_table)[local_30] + y2;
            iVar7 = map_in_bounds(x,y3);
            if (iVar7 != 0) {
              bVar2 = tile_terrain(x,y3);
              local_40 = (uptr)bVar2;
              if (local_40 != 10) {
                if (((2 < local_40) && (local_2c != 0)) && (local_388[local_40] != 0)) {
                  local_388[local_40]++;
                }
                if ((local_30 & 1) == 0) {
                  local_388[local_40]++;
                }
                local_388[local_40]++;
              }
            }
          }
          local_1c = 0;
          for (local_40 = 0; (int)local_40 < 0xb; local_40++) {
            if (local_1c < local_388[local_40]) {
              local_1c = local_388[local_40];
              local_50->terrain = (u8)local_40;
              local_390 = local_40;
            }
          }
        }
      }
    }
    ui_pump_messages_net();
    mapgen_place_rivers();
    ui_pump_messages_net();
  }
  if ((game.rules & 0x8000) == 0) {
    for (x2 = 0; (int)x2 < (int)map.width; x2 += 2) {
      iVar5 = tile_is_ocean(x2 + 1,1);
      if (iVar5 == 0) {
        puVar5 = (i8 *)tile_at(x2,0);
        *puVar5 = 7;
      }
      iVar6 = tile_is_ocean(x2,map.height - 2);
      if (iVar6 == 0) {
        puVar5 = (i8 *)tile_at(x2 + 1,map.height - 1);
        *puVar5 = 7;
      }
    }
  }
  map_assign_landmass_ids();
  map_build_coarse_connectivity();
  mapgen_calc_fertility();
  if ((game.rules & 0x8000) == 0) {
    for (x2 = 0; (int)x2 < (int)map.width; x2 += 2) {
      puVar5 = (i8 *)tile_at(x2,0);
      *puVar5 = 7;
      puVar5 = (i8 *)tile_at(x2 + 1,map.height - 1);
      *puVar5 = 7;
    }
    if (param_1 == 0) {
      for (local_48 = 0; (int)local_48 < (int)map.width >> 3; local_48++) {
        if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
          local_3d4 = 0;
        }
        else {
          local_3d4 = _rand();
          local_3d4 = local_3d4 % ((int)map.width / 2);
        }
        puVar5 = (i8 *)tile_at(local_3d4 * 2,0);
        *puVar5 = 6;
        if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
          local_3dc = 0;
        }
        else {
          local_3dc = _rand();
          local_3dc = local_3dc % ((int)map.width / 2);
        }
        puVar5 = (i8 *)tile_at(local_3dc * 2 + 1,1);
        *puVar5 = 6;
        if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
          local_3e4 = 0;
        }
        else {
          local_3e4 = _rand();
          local_3e4 = local_3e4 % ((int)map.width / 2);
        }
        puVar5 = (i8 *)tile_at(local_3e4 * 2 + 1,map.height - 1);
        *puVar5 = 6;
        if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
          local_3ec = 0;
        }
        else {
          local_3ec = _rand();
          local_3ec = local_3ec % ((int)map.width / 2);
        }
        puVar5 = (i8 *)tile_at(local_3ec * 2,map.height - 2);
        *puVar5 = 6;
      }
    }
  }
  map_fill_tile_byte((iptr)&map_tiles->improvements,0);
  if (DAT_00628060 == 0) {
    local_50 = map_tiles;
    y2 = 0;
    x2 = 0;
    for (local_48 = 0; (int)local_48 < (int)map.area; local_48++) {
      if ((local_50->terrain == '\n') && (iVar7 = tile_resource(x2,y2), iVar7 != 0)) {
        local_18 = 0;
        for (local_30 = 0; (local_18 == 0 && ((int)local_30 < 0x14)); local_30++) {
          x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_30] + x2);
          y3 = (int)(char)(&city_tile_dy_table)[local_30] + y2;
          iVar7 = map_in_bounds(x,y3);
          if ((iVar7 != 0) && (iVar7 = tile_is_ocean(x,y3), iVar7 == 0)) {
            local_18 = 1;
          }
        }
        if (local_18 == 0) {
          local_50->terrain = local_50->terrain | 0x40;
        }
      }
      local_50++;
      x2 += 2;
      if ((int)map.width <= (int)x2) {
        y2++;
        x2 = y2 & 1;
      }
      ui_pump_messages_net();
    }
  }
  FUN_005f2110(&map_offmap_tile,map_tiles,6);
  wnd_set_cursor((WndBase *)&main_frame_wnd,0x201);
  ui_flush_input();
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0040a54e */ { dialog_dtor((Dialog *)((iptr)&local_350)); }
  return;
}
#undef mapgen_min_x
#undef mapgen_min_y
#undef screen_height
#undef local_3ec
#undef local_3e4
#undef local_3dc
#undef local_3d4
#undef local_3bc
#undef local_3b8
#undef local_3b4
#undef local_3b0
#undef local_3ac
#undef local_398
#undef local_390
#undef local_388
#undef local_35c
#undef local_358
#undef y2
#undef local_350
#undef x2
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef y3
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
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0040a572 auto */
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define y2 (*(int *)(frame_ + FRAME_OFF(4)))
#define x2 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl mapgen_add_landmass(int param_1)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  map_fill_tile_byte((iptr)&map_tiles->owner,0);
  do {
    if (map.width == 0x11 || map.width - 0x11 < 0) {
      x2 = 0;
    }
    else {
      x2 = _rand();
      x2 = x2 % (map.width - 0x10);
    }
    x2 += 8;
    if (map.height == 9 || map.height - 9 < 0) {
      y2 = 0;
    }
    else {
      y2 = _rand();
      y2 = y2 % (map.height - 8);
    }
    y2 += 4;
    if (param_1 == 0) {
      if (mapgen_land_form == -1 || mapgen_land_form + 1 < 0) {
        local_28 = 0;
      }
      else {
        local_28 = _rand();
        local_28 = local_28 % (mapgen_land_form + 2);
      }
      if (local_28 != 0) break;
    }
    iVar1 = tile_at(x2,y2);
  } while (*(char *)(iVar1 + 1) != '\0');
  if (param_1 == 0) {
    if (mapgen_land_form < 1) {
      mapgen_land_walk(x2,y2);
    }
    else {
      mapgen_land_walk_wide(x2,y2);
    }
  }
  else {
    iVar2 = _rand();
    mapgen_islet_walk(x2,y2);
    if (6 < iVar2 % 10) {
      mapgen_islet_walk(x2,y2);
    }
    if (8 < iVar2 % 10) {
      mapgen_islet_walk(x2,y2);
    }
  }
  local_1c = &map_tiles->owner;
  local_18 = &map_tiles->improvements;
  for (local_8 = 0; local_8 < map.area; local_8++) {
    if (*local_1c != '\0') {
      *local_18 = *local_18 + 1;
      mapgen_land_placed++;
    }
    local_1c += 6;
    local_18 += 6;
  }
  ui_pump_messages_net();
  return;
}
#undef local_28
#undef y2
#undef x2
#undef local_1c
#undef local_18
#undef local_8

/* 0040a763 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapgen_land_walk(int x,int y)

{
  int iVar1;
  uint uVar2;
  iptr iVar2;
  iptr iVar3;
  uint uVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar2 = _rand();
  uVar3 = (int)uVar2 >> 0x1f;
  local_8 = ((uVar2 ^ uVar3) - uVar3 & 0x3f ^ uVar3) - uVar3;
  iVar2 = tile_at(x,y);
  if (*(char *)(iVar2 + 1) != '\0') {
    local_8 = local_8 >> 1;
  }
  local_8++;
  while( true ) {
    if (local_8 == 0) break;
    iVar3 = mapgen_in_bounds(x,y);
    if (iVar3 == 0) break;
    mapgen_mark_tile_cluster(x,y);
    uVar2 = _rand();
    uVar3 = (int)uVar2 >> 0x1f;
    iVar1 = (((uVar2 ^ uVar3) - uVar3 & 3 ^ uVar3) - uVar3) * 2;
    x += (char)(&mapgen_cardinal_dx_table)[iVar1];
    y += (char)(&mapgen_cardinal_dy_table)[iVar1];
    local_8--;
  }
  ui_pump_messages_net();
  return;
}
#undef local_8

/* 0040a824 auto */
#define mapgen_min_x (*(int *)((u8 *)&g.d_0063cb9c))
#define mapgen_min_y (*(int *)((u8 *)&g.d_0063cba0))
i32 __cdecl mapgen_in_bounds(int param_1,int param_2)

{
  i32 uVar1;
  
  if (((game.rules & 0x8000) == 0) || ((mapgen_min_x <= param_1 && (param_1 <= mapgen_max_x)))) {
    if ((param_2 < mapgen_min_y) || (mapgen_max_y < param_2)) {
      uVar1 = 0;
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
#undef mapgen_min_x
#undef mapgen_min_y

/* 0040a892 auto */
void __cdecl mapgen_mark_tile_cluster(int param_1,int y)

{
  mapgen_mark_tile(param_1,y);
  mapgen_mark_tile(param_1 + 1,y - 1);
  mapgen_mark_tile(param_1 + 1,y + 1);
  ui_pump_messages_net();
  return;
}

/* 0040a8db auto */
void __cdecl mapgen_mark_tile(iptr param_1,iptr y)

{
  iptr x;
  iptr iVar2;
  iptr iVar3;
  
  x = map_wrap_x(param_1);
  iVar2 = mapgen_in_bounds(x,y);
  if (iVar2 != 0) {
    iVar3 = tile_at(x,y);
    *(i8 *)(iVar3 + 5) = 1;
  }
  return;
}

/* 0040a92f auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapgen_land_walk_wide(int x,int y)

{
  int iVar3;
  iptr iVar1;
  iptr iVar2;
  uint uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = _rand();
  local_8 = local_8 % 0x30;
  iVar1 = tile_at(x,y);
  if (*(char *)(iVar1 + 1) != '\0') {
    local_8 = local_8 >> 1;
  }
  local_8++;
  while( true ) {
    if (local_8 == 0) break;
    iVar2 = mapgen_in_bounds(x,y);
    if (iVar2 == 0) break;
    mapgen_mark_tile_cluster(x,y);
    uVar4 = _rand();
    uVar5 = (int)uVar4 >> 0x1f;
    if (((uVar4 ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5) {
      mapgen_mark_tile_cluster(x + 2,y);
    }
    uVar4 = _rand();
    uVar5 = (int)uVar4 >> 0x1f;
    if (((uVar4 ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5) {
      mapgen_mark_tile_cluster(x - 2,y);
    }
    uVar4 = _rand();
    uVar5 = (int)uVar4 >> 0x1f;
    if (((uVar4 ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5) {
      mapgen_mark_tile_cluster(x,y + 2);
    }
    uVar4 = _rand();
    uVar5 = (int)uVar4 >> 0x1f;
    if (((uVar4 ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5) {
      mapgen_mark_tile_cluster(x,y - 2);
    }
    uVar4 = _rand();
    uVar5 = (int)uVar4 >> 0x1f;
    iVar3 = (((uVar4 ^ uVar5) - uVar5 & 3 ^ uVar5) - uVar5) * 2;
    x += (char)(&mapgen_cardinal_dx_table)[iVar3];
    y += (char)(&mapgen_cardinal_dy_table)[iVar3];
    local_8--;
  }
  ui_pump_messages_net();
  return;
}
#undef local_8

/* 0040aaa4 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapgen_islet_walk(int param_1,int y)

{
  uint uVar1;
  iptr iVar2;
  uint uVar2;
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = _rand();
  uVar2 = (int)uVar1 >> 0x1f;
  local_8 = (((uVar1 ^ uVar2) - uVar2 & 0xf ^ uVar2) - uVar2) + 1;
  while( true ) {
    if (local_8 == 0) break;
    iVar2 = mapgen_in_bounds(param_1,y);
    if (iVar2 == 0) break;
    mapgen_mark_tile(param_1,y);
    uVar1 = _rand();
    uVar2 = (int)uVar1 >> 0x1f;
    iVar1 = (((uVar1 ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2) * 2;
    param_1 += (char)(&dir_dx_table)[iVar1];
    y += (char)(&dir_dy_table)[iVar1];
    local_8--;
  }
  ui_pump_messages_net();
  return;
}
#undef local_8

/* 0040ab41 auto */
i32 __cdecl mapgen_try_place_lake(int x,int y)

{
  int iVar1;
  i32 uVar2;
  i8 *puVar3;
  
  iVar1 = map_in_bounds(x,y);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if ((((x < 2) || (y < 2)) || (map.width - 2 <= x)) ||
          (map.height - 2 <= y)) {
    uVar2 = 0;
  }
  else {
    iVar1 = tile_is_ocean(x - 2,y);
    if (iVar1 == 0) {
      iVar1 = tile_is_ocean(x + 2,y);
      if (iVar1 == 0) {
        iVar1 = tile_is_ocean(x,y - 2);
        if (iVar1 == 0) {
          iVar1 = tile_is_ocean(x,y + 2);
          if (iVar1 == 0) {
            puVar3 = (i8 *)tile_at(x,y);
            *puVar3 = 10;
            uVar2 = 1;
          }
          else {
            uVar2 = 0;
          }
        }
        else {
          uVar2 = 0;
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

/* 0040ac5a auto */
#define local_44 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_3c (*(uptr *)(frame_ + FRAME_OFF(12)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(28)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(32)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_c (*(int *)(frame_ + FRAME_OFF(60)))
void __cdecl mapgen_place_rivers(void)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  iptr iVar5;
  int y;
  byte *pbVar7;
  uint uVar8;
  iptr x;
  iptr iVar9;
  iptr iVar10;
  int iVar12;
  uint uVar13;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 0;
  local_30 = 0;
  do {
    map_copy_tile_byte((iptr)&map_tiles->owner,(iptr)map_tiles);
    local_30++;
    local_2c = 0;
    do {
      if (map.height == 1 || map.height - 1 < 0) {
        y2 = 0;
      }
      else {
        y = _rand();
        y2 = y % (int)map.height;
      }
      uVar4 = y2;
      if ((int)map.width / 2 == 1 || (int)map.width / 2 - 1 < 0) {
        local_44 = 0;
      }
      else {
        local_44 = _rand();
        local_44 = local_44 % ((int)map.width / 2);
      }
      x2 = local_44 * 2;
      if ((y2 & 1) != 0) {
        x2++;
      }
      iVar5 = x2;
      pbVar7 = (byte *)tile_at(x2,y2);
      bVar1 = *pbVar7;
    } while ((bVar1 == 5) || (bVar1 == 10));
    uVar8 = _rand();
    uVar13 = (int)uVar8 >> 0x1f;
    local_3c = ((uVar8 ^ uVar13) - uVar13 & 3 ^ uVar13) - uVar13;
    do {
      switch(bVar1) {
      case 0:
        bVar1 = 1;
        y = _rand();
        if ((1 < y % 10) || (3 < (int)local_2c)) {
          bVar1 = 2;
        }
        break;
      case 1:
        y = _rand();
        if (3 < y % 10) {
          bVar1 = 2;
        }
        break;
      case 3:
        y = _rand();
        if (2 < y % 10) {
          bVar1 = 2;
        }
        break;
      case 4:
      case 5:
        bVar1 = 2;
        break;
      case 6:
        bVar1 = 1;
        break;
      case 7:
        bVar1 = 6;
        break;
      case 8:
        y = _rand();
        if (3 < y % 10) {
          bVar1 = 9;
        }
      }
      bVar1 = bVar1 | 0x80;
      pbVar7 = (byte *)tile_at(x2,y2);
      *pbVar7 = bVar1;
      local_2c++;
      bVar3 = false;
      for (local_14 = 0; (!bVar3 && (local_14 < 4)); local_14++) {
        x = map_wrap_x((char)(&diag_dx_table)[local_14] + x2);
        cVar2 = (&diag_dy_table)[local_14];
        iVar9 = map_in_bounds(x,(int)cVar2 + y2);
        if ((iVar9 != 0) && (iVar10 = tile_is_ocean(x,(int)cVar2 + y2), iVar10 != 0)) {
          bVar3 = true;
        }
      }
      uVar8 = _rand();
      uVar13 = (int)uVar8 >> 0x1f;
      local_3c = (local_3c + (((uVar8 ^ uVar13) - uVar13 & 1 ^ uVar13) - uVar13)) - (local_2c & 1) &
                 3;
      x2 = map_wrap_x((char)(&diag_dx_table)[local_3c] + x2);
      y2 += (int)(char)(&diag_dy_table)[local_3c];
      y = map_in_bounds(x2,y2);
      if (y != 0) {
        y = tile_at(x2,y2);
        bVar1 = *(byte *)(y + 5);
      }
    } while (((!bVar3) && (y = map_in_bounds(x2,y2), y != 0)) &&
            ((bVar1 & 0x80) == 0));
    if (((bVar3) || ((bVar1 & 0x80) != 0)) && (5 - local_30 / 800 <= (int)local_2c)) {
      local_34++;
      for (local_14 = 0; local_14 < 0x14; local_14++) {
        x = map_wrap_x((char)(&city_tile_dx_table)[local_14] + iVar5);
        y = (int)(char)(&city_tile_dy_table)[local_14] + uVar4;
        iVar12 = map_in_bounds(x,y);
        if (iVar12 != 0) {
          if ((int)map.height >> 1 == y || ((int)map.height >> 1) - y < 0) {
            local_c = ~(((int)map.height >> 1) - y) + 1;
          }
          else {
            local_c = ((int)map.height >> 1) - y;
          }
          pbVar7 = (byte *)tile_at(x,y);
          if (((*pbVar7 & 0xf) == 3) && (local_c < (map.height * 3) / 10)) {
            _rand();
          }
        }
      }
    }
    else {
      map_copy_tile_byte((iptr)map_tiles,(iptr)&map_tiles->owner);
    }
    ui_pump_messages_net();
  } while ((local_30 < 0x400) && (local_34 < mapgen_land_mass * 2 + mapgen_climate * 2 + 0xc));
  return;
}
#undef local_44
#undef local_3c
#undef local_34
#undef local_30
#undef local_2c
#undef y2
#undef x2
#undef local_14
#undef local_c

/* 0040bcb0 auto */
uint __cdecl tile_grassland_has_shield(int param_1,int param_2)

{
  return (uint)((-(param_2 + param_1 >> 1) - param_1 & 2U) == 0);
}

/* 00410d98 auto */
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
uint __cdecl map_set_cursor_pos(iptr param_1,iptr param_2)

{
  int iVar1;
  
  iVar1 = map_in_bounds(param_1,param_2);
  if (iVar1 != 0) {
    unit_blink_phase = 0;
    mapview_redraw_cursor_tile((C_004083b0_430 *)&map_views);
    map_cursor_x = (i16)param_1;
    map_cursor_y = (i16)param_2;
    status_redraw(1);
    unit_blink_phase = 1;
    mapview_redraw_cursor_tile((C_004083b0_430 *)&map_views);
  }
  return (uint)(iVar1 != 0);
}
#undef map_cursor_x
#undef map_cursor_y
#undef unit_blink_phase

/* 00410f77 auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_click_in_progress (*(i32 *)((u8 *)&g.d_0062bcb0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define unit_create_busy (*(int *)((u8 *)&g.d_006ad8bc))
#define unit_delete_busy (*(int *)((u8 *)&g.d_006ad8c0))
#define unit_delete_cargo_busy (*(int *)((u8 *)&g.d_006ad900))
#define unit_destroy_redraw_busy (*(int *)((u8 *)&g.d_006ad904))
#define unit_gather_cargo_busy (*(int *)((u8 *)&g.d_006ad8f8))
#define unit_lift_off_map_busy (*(int *)((u8 *)&g.d_006ad8fc))
#define unit_relocate_busy (*(int *)((u8 *)&g.d_006ad8e4))
#define unit_stack_bottom_busy (*(int *)((u8 *)&g.d_006ad8e0))
#define unit_stack_link_busy (*(int *)((u8 *)&g.d_006ad8dc))
#define unit_stack_unlink_busy (*(int *)((u8 *)&g.d_006ad8d8))
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31b8 (*(i32 *)((u8 *)&g.d_006c31b8))
#define _DAT_006c31cc (*(i32 *)((u8 *)&g.d_006c31cc))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(20)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_c (*(C_004083b0_430 * *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(32)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl map_window_click(i32 param_1,i32 param_2,int param_3)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((game.multiplayer == '\0') || (ui_input_busy == 0)) {
    iVar1 = XD_InFlushSendBuffer();
    if (((((iVar1 == 0) &&
          (((((unit_create_busy == 0 && (unit_delete_busy == 0)) && (city_create_busy == 0)) &&
            ((city_delete_busy == 0 && (net_lock_map_busy == 0)))) && (net_unlock_map_busy == 0)))) &&
         (((unit_stack_unlink_busy == 0 && (unit_stack_link_busy == 0)) && (unit_stack_bottom_busy == 0)))) &&
        ((((unit_relocate_busy == 0 && (city_acquire_wonder_busy == 0)) && (civ_eliminate_busy == 0)) &&
         ((civ_create_busy == 0 && (civ_check_destroyed_busy == 0)))))) &&
       (((unit_gather_cargo_busy == 0 && ((unit_lift_off_map_busy == 0 && (unit_delete_cargo_busy == 0)))) && (unit_destroy_redraw_busy == 0))
       )) {
      ui_input_busy = 1;
      if (city_turn_processing == 0) {
        iVar2 = wnd_get_active_child();
        if (iVar2 == 0) {
          local_c = (C_004083b0_430 *)0x0;
        }
        else {
          local_c = (C_004083b0_430 *)(iVar2 - 0x48);
        }
        local_8 = (uint)(local_c->field_358 == 0x1fe);
        local_20 = ui_paradrop_cursor_active();
        mapview_cancel_drag();
        if (param_3 == 0) {
          mapviews_reset_cursor();
        }
        iVar3 = mapview_screen_to_tile
                          ((MapViewHitView *)local_c,(iptr)&x2,(iptr)&y2,param_1,param_2);
        if (iVar3 == 0) {
          map_click_in_progress = 1;
          iVar3 = map_in_bounds(x2,y2);
          if (iVar3 != 0) {
            map_click_tile_x = x2;
            map_click_tile_y = y2;
            if ((local_20 != 0) && (param_3 != 0)) {
              unit_blink_phase = 0;
              mapview_redraw_cursor_tile(local_c);
              mapview_center_on(local_c,x2,y2);
              map_click_in_progress = 0;
              ui_input_busy = 0;
              return;
            }
            if ((moving_units_mode == 0) || (param_3 != 0)) {
              if (local_c->field_2d8 == 0) {
                ui_redraw_all_maps(0);
                map_set_cursor_pos(x2,y2);
              }
              if (param_3 == 0) {
                city = city_at(x2,y2);
                if (-1 < city) {
                  if (((cities[city].owner == human_civ) || (game.reveal_map != '\0')) ||
                     ((cities[city].flags & 0x400000) != 0)) {
                    city_window_open((C_004083b0_12c *)&city_window,city);
                  }
                  else {
                    iVar3 = civ_has_advance(human_civ,0x54);
                    if (((iVar3 != 0) &&
                        (iVar3 = tile_visible_to(x2,y2,human_civ), iVar3 != 0)) &&
                       ((((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to)
                          != 0 || ((int)cities[city].owner == (human_civ & 0xffU))) ||
                        (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))))) {
                      city_info_popup(city);
                    }
                  }
                  map_click_in_progress = 0;
                  ui_input_busy = 0;
                  return;
                }
                ui_pick_unit_from_stack();
              }
            }
            else {
              if (local_8 != 0) {
                unit = (iptr)game.active_unit;
                if (-1 < unit) {
                  units[unit].goto_x = (i16)x2;
                  units[unit].goto_y = (i16)y2;
                  units[unit].orders = 11;
                  unit_goto_step(unit);
                }
                map_click_in_progress = 0;
                ui_input_busy = 0;
                return;
              }
              if (local_20 != 0) {
                unit_paradrop((int)game.active_unit,x2,y2);
                map_click_in_progress = 0;
                ui_input_busy = 0;
                return;
              }
              if ((499 < (int)local_c->field_358) && ((int)local_c->field_358 < 0x1fc)) {
                local_14 = local_c->field_358 - 0x1f5;
                if ((int)local_14 < 0) {
                  local_14 = 7;
                }
                unit_move_dir((int)game.active_unit,local_14,3);
                map_click_in_progress = 0;
                ui_input_busy = 0;
                return;
              }
              city = city_at(x2,y2);
              if (-1 < city) {
                if (((cities[city].owner == human_civ) || (game.reveal_map != '\0')) ||
                   ((cities[city].flags & 0x400000) != 0)) {
                  city_window_open((C_004083b0_12c *)&city_window,city);
                }
                else {
                  iVar3 = civ_has_advance(human_civ,0x54);
                  if (((iVar3 != 0) &&
                      (iVar3 = tile_visible_to(x2,y2,human_civ), iVar3 != 0)) &&
                     ((((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to)
                        != 0 || ((int)cities[city].owner == (human_civ & 0xffU))) ||
                      (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))))) {
                    city_info_popup(city);
                  }
                }
                map_click_in_progress = 0;
                ui_input_busy = 0;
                return;
              }
              unit = tile_first_unit(x2,y2);
              if ((-1 < unit) && (units[unit].owner == human_civ)) {
                ui_redraw_all_maps(0);
                map_set_cursor_pos(x2,y2);
                ui_pick_unit_from_stack();
              }
              unit_blink_phase = 0;
              mapviews_redraw_cursor();
            }
            mapview_center_on(local_c,x2,y2);
          }
          map_click_in_progress = 0;
          ui_input_busy = 0;
        }
        else {
          ui_input_busy = 0;
        }
      }
      else {
        city_window_modal_notice();
        ui_input_busy = 0;
      }
    }
    else {
      dbg_log(ADDR(0x624f78, ((u8 *)&g.d_00624f78)));
      blocked_input_kind = 1;
      _DAT_006c31b0 = param_1;
      _DAT_006c31b4 = param_2;
      _DAT_006c31b8 = param_3;
      _DAT_006c31cc = wnd_get_active_child();
      if (_DAT_006c31cc == 0) {
        _DAT_006c31cc = 0;
      }
      else {
        _DAT_006c31cc -= 0x48;
      }
    }
  }
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_turn_processing
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef human_civ
#undef map_click_in_progress
#undef moving_units_mode
#undef net_lock_map_busy
#undef net_unlock_map_busy
#undef scenario_flags
#undef unit_blink_phase
#undef unit_create_busy
#undef unit_delete_busy
#undef unit_delete_cargo_busy
#undef unit_destroy_redraw_busy
#undef unit_gather_cargo_busy
#undef unit_lift_off_map_busy
#undef unit_relocate_busy
#undef unit_stack_bottom_busy
#undef unit_stack_link_busy
#undef unit_stack_unlink_busy
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31b8
#undef _DAT_006c31cc
#undef x2
#undef local_20
#undef unit
#undef city
#undef local_14
#undef y2
#undef local_c
#undef local_8

/* 00411705 auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
#define unit_create_busy (*(int *)((u8 *)&g.d_006ad8bc))
#define unit_delete_busy (*(int *)((u8 *)&g.d_006ad8c0))
#define unit_delete_cargo_busy (*(int *)((u8 *)&g.d_006ad900))
#define unit_destroy_redraw_busy (*(int *)((u8 *)&g.d_006ad904))
#define unit_gather_cargo_busy (*(int *)((u8 *)&g.d_006ad8f8))
#define unit_lift_off_map_busy (*(int *)((u8 *)&g.d_006ad8fc))
#define unit_relocate_busy (*(int *)((u8 *)&g.d_006ad8e4))
#define unit_stack_bottom_busy (*(int *)((u8 *)&g.d_006ad8e0))
#define unit_stack_link_busy (*(int *)((u8 *)&g.d_006ad8dc))
#define unit_stack_unlink_busy (*(int *)((u8 *)&g.d_006ad8d8))
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31cc (*(i32 *)((u8 *)&g.d_006c31cc))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl map_window_double_click(i32 param_1,i32 param_2)

{
  bool bVar1;
  iptr x;
  iptr y;
  byte bVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  if ((game.multiplayer != '\0') && (ui_input_busy != 0)) {
    bVar1 = true;
  }
  iVar5 = XD_InFlushSendBuffer();
  if (((((((iVar5 == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
        (((city_create_busy == 0 && (city_delete_busy == 0)) &&
         ((net_lock_map_busy == 0 && ((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)))))))) &&
       ((unit_stack_link_busy == 0 && (((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0))))
       )) && (((civ_eliminate_busy == 0 && (civ_create_busy == 0)) &&
              (((civ_check_destroyed_busy == 0 && ((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)))) &&
               (unit_delete_cargo_busy == 0)))))) && (unit_destroy_redraw_busy == 0)) {
    if (!bVar1) {
      ui_input_busy = 1;
    }
    if (city_turn_processing == 0) {
      wnd_get_active_child();
      y = map_click_tile_y;
      x = map_click_tile_x;
      iVar5 = map_in_bounds(map_click_tile_x,map_click_tile_y);
      if (((iVar5 != 0) && (iVar5 = tile_city_or_unit_owner(x,y), iVar5 < 0)) &&
         (iVar5 = tile_visible_to(x,y,human_civ), iVar5 != 0)) {
        bVar4 = tile_terrain(x,y);
        if (bVar4 == 2) {
          iVar5 = tile_grassland_has_shield(x,y);
          local_8 = (uint)(iVar5 != 0);
        }
        else {
          local_8 = tile_resource(x,y);
        }
        pedia_show_terrain_modal
                  ((C_004083b0_a28 *)&pedia_window,local_8 * 0xb + (uint)bVar4);
      }
      if (!bVar1) {
        ui_input_busy = 0;
      }
    }
    else {
      city_window_modal_notice();
      if (!bVar1) {
        ui_input_busy = 0;
      }
    }
  }
  else {
    dbg_log(ADDR(0x624fc0, ((u8 *)&g.d_00624fc0)));
    blocked_input_kind = 2;
    _DAT_006c31b0 = param_1;
    _DAT_006c31b4 = param_2;
    _DAT_006c31cc = wnd_get_active_child();
    if (_DAT_006c31cc == 0) {
      _DAT_006c31cc = 0;
    }
    else {
      _DAT_006c31cc -= 0x48;
    }
  }
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_turn_processing
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef human_civ
#undef net_lock_map_busy
#undef net_unlock_map_busy
#undef unit_create_busy
#undef unit_delete_busy
#undef unit_delete_cargo_busy
#undef unit_destroy_redraw_busy
#undef unit_gather_cargo_busy
#undef unit_lift_off_map_busy
#undef unit_relocate_busy
#undef unit_stack_bottom_busy
#undef unit_stack_link_busy
#undef unit_stack_unlink_busy
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31cc
#undef local_8

/* 00411a13 auto */
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
void __cdecl map_cursor_step_dir(iptr param_1)

{
  char cVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = map_wrap_x((int)(char)(&dir_dx_table)[param_1] + (int)map_cursor_x);
  cVar1 = (&dir_dy_table)[param_1];
  iVar4 = (int)map_cursor_y;
  iVar3 = map_set_cursor_pos(uVar2,cVar1 + iVar4);
  if (iVar3 != 0) {
    mapview_scroll_if_near_edge((C_004083b0_430 *)&map_views,uVar2,cVar1 + iVar4);
  }
  return;
}
#undef map_cursor_x
#undef map_cursor_y

/* 00411a85 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __cdecl map_ascii_view_mode(int param_1)

{
  iptr city;
  int iVar2;
  
  if ((param_1 == 0xd) || (param_1 == 0x20)) {
    if (((game.field_06 & 1) == 0) || (param_1 != 0xd)) {
      city = city_at((int)map_cursor_x,(int)map_cursor_y);
      if (-1 < city) {
        if (((cities[city].owner == human_civ) || (game.reveal_map != '\0')) ||
           ((cities[city].flags & 0x400000) != 0)) {
          city_window_open((C_004083b0_12c *)&city_window,city);
        }
        else {
          iVar2 = civ_has_advance(human_civ,0x54);
          if ((iVar2 != 0) || (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
            city_info_popup(city);
          }
        }
      }
    }
    else {
      player_turn_active = 0;
    }
  }
  else if (param_1 == 0x43) {
    mapview_center_on
              ((C_004083b0_430 *)&map_views,(int)map_cursor_x,(int)map_cursor_y);
  }
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef player_turn_active
#undef scenario_flags

/* 00411bf5 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __cdecl map_ascii_unit_cmd(int param_1,int param_2)

{
  iptr unit;
  iptr city;
  int iVar3;
  
  unit = (iptr)game.active_unit;
  if (((game.multiplayer < 3) || (units[unit].owner == human_civ)) || (param_1 == 0xd)) {
    switch(param_1) {
    case 0xd:
      city = city_at((int)map_cursor_x,(int)map_cursor_y);
      if (-1 < city) {
        if (((cities[city].owner == human_civ) || (game.reveal_map != '\0')) ||
           ((cities[city].flags & 0x400000) != 0)) {
          city_window_open((C_004083b0_12c *)&city_window,city);
        }
        else {
          iVar3 = civ_has_advance(human_civ,0x54);
          if ((iVar3 != 0) || (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
            city_info_popup(city);
          }
        }
      }
      break;
    case 0x20:
      cmd_unit_skip_turn();
      break;
    case 0x42:
      unit_cmd_build_city();
      break;
    case 0x43:
      mapview_center_on
                ((C_004083b0_430 *)&map_views,(int)units[unit].x,(int)units[unit].y);
      break;
    case 0x45:
      unit_cmd_terraform(10);
      break;
    case 0x46:
      if (unit_types[units[unit].type].role == 5) {
        unit_cmd_terraform(4);
      }
      else {
        unit_cmd_fortify();
      }
      break;
    case 0x47:
      unit_cmd_goto_city();
      break;
    case 0x48:
      unit_cmd_home_city();
      break;
    case 0x49:
      unit_cmd_terraform(6);
      break;
    case 0x4b:
      unit_cmd_automate();
      break;
    case 0x4c:
      unit_cmd_airlift();
      break;
    case 0x4d:
      unit_cmd_terraform(7);
      break;
    case 0x4f:
      unit_cmd_terraform(8);
      break;
    case 0x50:
      if ((param_2 == 0x70) && ((unit_types[units[unit].type].flags & 0x100) != 0)) {
        unit_cmd_paradrop();
      }
      else if (unit_types[units[unit].type].role == 5) {
        unit_cmd_terraform(9);
      }
      else if (param_2 == 0x50) {
        unit_cmd_pillage();
      }
      break;
    case 0x51:
      if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) != 0) && (game.multiplayer == '\0')) {
        cheat_throneroom_upgrade();
      }
      break;
    case 0x52:
      unit_cmd_terraform(5);
      break;
    case 0x53:
      unit_cmd_sleep();
      break;
    case 0x55:
      unit_cmd_unload();
      break;
    case 0x57:
      unit_cmd_wait();
    }
  }
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef scenario_flags

/* 00411f91 auto */
#define blocked_input_char (*(char *)((u8 *)&g.d_006c31c8))
#define blocked_input_char_pending (*(i32 *)((u8 *)&g.d_006c31c4))
#define blocked_input_kind (*(int *)((u8 *)&g.d_006c31ac))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define game_session_active (*(int *)((u8 *)&g.d_006252c4))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(i16 *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(i16 *)((u8 *)&g.d_0064b1b0))
#define map_view_center_x (*(i16 *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(i16 *)((u8 *)&g.d_0066ca8a))
#define mapview_zoom (*(short *)((u8 *)&g.d_0066ca8c))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
void __cdecl map_window_ascii(uint param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = param_1;
  if (game_session_active == 0) {
    return;
  }
  if ((game.multiplayer != '\0') && (ui_input_busy != 0)) {
    return;
  }
  if (blocked_input_kind == 4) {
    dbg_log(ADDR(0x625008, ((u8 *)&g.d_00625008)));
    blocked_input_char_pending = 3;
    blocked_input_char = (char)param_1;
    return;
  }
  ui_input_busy = 1;
  if (city_turn_processing != 0) {
    if ((char)param_1 == '\r') {
      ui_input_busy = 0;
      return;
    }
    if ((char)param_1 == 27) {
      ui_input_busy = 0;
      return;
    }
    if ((char)param_1 == '\n') {
      ui_input_busy = 0;
      return;
    }
    city_window_modal_notice();
    ui_input_busy = 0;
    return;
  }
  iVar3 = city_window_is_closed((C_004083b0_4 *)&city_window);
  if ((iVar3 == 0) && (((byte)game.game_options & 0x40) != 0)) {
    switch(param_1 & 0xff) {
    case 0xd:
    case 0x45:
    case 0x58:
    case 0x65:
    case 0x78:
      city_window_exit_clicked(0);
      break;
    default:
      goto switchD_00412142_caseD_e;
    case 0x41:
    case 0x43:
    case 0x61:
    case 99:
      city_button_change(0);
      break;
    case 0x42:
    case 0x62:
      city_button_buy(0);
      break;
    case 0x48:
    case 0x68:
      city_button_happy(0);
      break;
    case 0x49:
    case 0x69:
      city_button_info(0);
      break;
    case 0x4d:
    case 0x6d:
      city_button_map(0);
      break;
    case 0x52:
    case 0x72:
      city_button_rename(0);
      break;
    case 0x56:
    case 0x76:
      city_button_view(0);
    }
  }
  else {
switchD_00412142_caseD_e:
    mapview_cancel_drag();
    iVar3 = ui_paradrop_cursor_active();
    if ((iVar3 == 0) || (mapviews_reset_cursor(), (char)param_1 != 'p')) {
      iVar3 = _isalpha(param_1 & 0xff);
      if (iVar3 != 0) {
        uVar4 = FUN_005f2700(param_1 & 0xff);
        param_1 = uVar4 & 0xff;
      }
      bVar1 = false;
      switch(uVar2 & 0xff) {
      case 0x43:
        menu_find_city();
        break;
      case 0x44:
        unit_cmd_disband();
        break;
      default:
        bVar1 = true;
        break;
      case 0x48:
        if (game.multiplayer != 1) {
          throneroom_show(human_civ);
        }
        break;
      case 0x52:
        menu_revolution();
        break;
      case 0x53:
        if (game.multiplayer != 2) {
          game_save_dialog(0);
        }
        break;
      case 0x54:
        taxrate_dialog_show(human_civ);
        break;
      case 0x58:
        mapview_zoom = -3;
        mapview_redraw((C_004083b0_430 *)&map_views,human_civ,1);
        break;
      case 0x5a:
        mapview_zoom = 0;
        map_view_center_x = map_cursor_x;
        mapview_center_y = map_cursor_y;
        mapview_redraw((C_004083b0_430 *)&map_views,human_civ,1);
      }
      if (bVar1) {
        switch(param_1 & 0xff) {
        case 0x41:
          ui_pick_unit_from_stack();
          break;
        case 0x54:
          menu_show_hidden_terrain();
          break;
        case 0x56:
          if (moving_units_mode == 1) {
            ui_redraw_all_maps(0);
          }
          else {
            ui_focus_active_unit(1);
          }
          break;
        case 0x58:
          if (-7 < mapview_zoom) {
            mapview_zoom--;
            mapview_redraw((C_004083b0_430 *)&map_views,human_civ,1);
          }
          break;
        case 0x5a:
          if (mapview_zoom < 8) {
            mapview_zoom++;
            mapview_redraw((C_004083b0_430 *)&map_views,human_civ,1);
          }
        }
        if (((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) != 0) && (game.multiplayer == '\0')) &&
           ((param_1 & 0xff) == 0x59)) {
          game.reveal_map = game.reveal_map == '\0';
          map_redraw_all_views(human_civ,1);
        }
        if (moving_units_mode == 0) {
          thunk_map_ascii_view_mode(param_1 & 0xff,uVar2 & 0xff);
        }
        else {
          map_ascii_unit_cmd(param_1 & 0xff,uVar2 & 0xff);
        }
      }
    }
  }
  ui_input_busy = 0;
  return;
}
#undef blocked_input_char
#undef blocked_input_char_pending
#undef blocked_input_kind
#undef city_turn_processing
#undef game_session_active
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef map_view_center_x
#undef mapview_center_y
#undef mapview_zoom
#undef moving_units_mode

/* 004125c6 auto */
#define blocked_input_char_pending (*(i32 *)((u8 *)&g.d_006c31c4))
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define cheat_terrain_saved_bits (*(i32 *)((u8 *)&g.d_00633678))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define game_session_active (*(int *)((u8 *)&g.d_006252c4))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mapview_zoom (*(i16 *)((u8 *)&g.d_0066ca8c))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
#define unit_create_busy (*(int *)((u8 *)&g.d_006ad8bc))
#define unit_delete_busy (*(int *)((u8 *)&g.d_006ad8c0))
#define unit_delete_cargo_busy (*(int *)((u8 *)&g.d_006ad900))
#define unit_destroy_redraw_busy (*(int *)((u8 *)&g.d_006ad904))
#define unit_gather_cargo_busy (*(int *)((u8 *)&g.d_006ad8f8))
#define unit_lift_off_map_busy (*(int *)((u8 *)&g.d_006ad8fc))
#define unit_relocate_busy (*(int *)((u8 *)&g.d_006ad8e4))
#define unit_stack_bottom_busy (*(int *)((u8 *)&g.d_006ad8e0))
#define unit_stack_link_busy (*(int *)((u8 *)&g.d_006ad8dc))
#define unit_stack_unlink_busy (*(int *)((u8 *)&g.d_006ad8d8))
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl map_window_key(int param_1)

{
  SHORT SVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game_session_active == 0) {
    return;
  }
  if (((game.multiplayer != '\0') && (city_turn_processing != 0)) &&
     ((param_1 == 0xd2 || (param_1 == 0xd0)))) {
    iVar2 = city_window_is_closed((C_004083b0_4 *)&city_window);
    if (iVar2 == 0) {
      city_window_exit_clicked(0);
      return;
    }
    return;
  }
  if ((game.multiplayer != '\0') && (ui_input_busy != 0)) {
    return;
  }
  iVar2 = XD_InFlushSendBuffer();
  if (((((((iVar2 != 0) || (unit_create_busy != 0)) || (unit_delete_busy != 0)) ||
        (((city_create_busy != 0 || (city_delete_busy != 0)) ||
         ((net_lock_map_busy != 0 || ((net_unlock_map_busy != 0 || (unit_stack_unlink_busy != 0)))))))) ||
       (unit_stack_link_busy != 0)) ||
      ((((unit_stack_bottom_busy != 0 || (unit_relocate_busy != 0)) || (city_acquire_wonder_busy != 0)) ||
       (((civ_eliminate_busy != 0 || (civ_create_busy != 0)) ||
        (((civ_check_destroyed_busy != 0 || ((unit_gather_cargo_busy != 0 || (unit_lift_off_map_busy != 0)))) || (unit_delete_cargo_busy != 0)
         ))))))) || (unit_destroy_redraw_busy != 0)) {
    dbg_log(ADDR(0x625048, ((u8 *)&g.d_00625048)));
    blocked_input_kind = 4;
    _DAT_006c31b0 = param_1;
    blocked_input_char_pending = 0;
    return;
  }
  ui_input_busy = 1;
  local_8 = 0xffffffff;
  if (city_turn_processing != 0) {
    if ((param_1 != 0xd2) && (param_1 != 0xd0)) {
      city_window_modal_notice();
      ui_input_busy = 0;
      return;
    }
    iVar2 = city_window_is_closed((C_004083b0_4 *)&city_window);
    if (iVar2 != 0) {
      ui_input_busy = 0;
      return;
    }
    city_window_exit_clicked(0);
    ui_input_busy = 0;
    return;
  }
  if (param_1 == 0x100) {
    ui_input_busy = 0;
    return;
  }
  if (param_1 == 0) {
    ui_input_busy = 0;
    return;
  }
  mapview_cancel_drag();
  mapviews_reset_cursor();
  iVar2 = city_window_is_closed((C_004083b0_4 *)&city_window);
  if ((iVar2 == 0) && ((game.game_options & 0x40) != 0)) {
    switch(param_1) {
    case 0xa2:
    case 0xa6:
    case 0xc1:
    case 0xc3:
      city_button_next_city(0);
      ui_input_busy = 0;
      return;
    case 0xa4:
    case 0xa8:
    case 0xc0:
    case 0xc2:
      city_button_prev_city(0);
      ui_input_busy = 0;
      return;
    }
  }
  if (param_1 < 0xd3) {
    if (param_1 == 0xd2) {
      iVar2 = city_window_is_closed((C_004083b0_4 *)&city_window);
      if (iVar2 == 0) {
        city_window_close();
      }
    }
    else {
      switch(param_1) {
      case 0xb0:
        city_status_show(human_civ);
        break;
      case 0xb1:
        defense_minister_show(human_civ);
        break;
      case 0xb2:
        foreign_minister_show(human_civ);
        break;
      case 0xb3:
        attitude_advisor_show(human_civ);
        break;
      case 0xb4:
        trade_advisor_show(human_civ);
        break;
      case 0xb5:
        science_advisor_show(human_civ);
        break;
      case 0xb6:
        wonders_report_show(human_civ);
        break;
      case 0xb7:
        top_cities_show(human_civ);
        break;
      case 0xb8:
        civ_score_window_show(human_civ);
        if (game.reveal_map != '\0') {
          civ_rating_window_show(human_civ);
          powergraph_show();
        }
        break;
      case 0xba:
        demographics_show(human_civ);
        break;
      case 0xbb:
        if ((game.rules & 0x80) == 0) {
          spaceship_select_view_dialog(human_civ);
        }
      }
    }
  }
  else if (param_1 < 0x355) {
    if (param_1 == 0x354) {
      if ((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
         (SVar1 = GetAsyncKeyState(0x10), (char)((ushort)SVar1 >> 8) == '\0')) {
        council_show(human_civ,0);
      }
      else {
        council_show(human_civ,1);
      }
    }
    else {
      switch(param_1) {
      case 0x243:
        if (2 < game.multiplayer) {
          parley_wnd_open((C_004083b0_430 *)&chat_wnd,0,4);
        }
        break;
      case 0x244:
        casualty_timeline_show(human_civ);
        break;
      case 0x245:
        menu_message_options();
        break;
      case 0x246:
        if (game.multiplayer == '\0') {
          editor_toggle_scenario_flag();
        }
        break;
      case 0x247:
        game.game_options = game.game_options ^ 0x20;
        menu_set_item_checked
                  ((GameMenu *)&main_menu,0x327,(game.game_options & 0x20) >> 5);
        map_redraw_all_views(human_civ,1);
        prefs_game_options = game.game_options;
        prefs_save_civ2dat();
        break;
      case 0x248:
        if ((game.multiplayer == 1) &&
           (iVar2 = popup_game_with_sprite(ADDR(0x625084, ((u8 *)&g.d_00625084)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0), iVar2 != 0)) {
          snd_cd_stop();
          map_display_disable();
        }
        break;
      case 0x24a:
        if ((mp_open_game != 0) && (game.multiplayer == 1)) {
          game_join_dialog();
        }
        break;
      case 0x24b:
        if ((game.multiplayer == '\0') || (mp_cheat_menu_allowed != 0)) {
          cheat_toggle_mode();
        }
        break;
      case 0x24c:
        if (game.multiplayer == '\0') {
          menu_load_game();
        }
        break;
      case 0x24e:
        cmd_end_player_turn();
        break;
      case 0x24f:
        menu_game_options();
        break;
      case 0x250:
        menu_graphic_options();
        break;
      case 0x251:
        game_quit_or_retire(0);
        break;
      case 0x252:
        game_quit_or_retire(1);
        break;
      case 0x253:
        if (game.multiplayer != 2) {
          game_save_dialog(0);
        }
        break;
      case 0x254:
        if (((game.multiplayer != '\0') && (game.multiplayer != 2)) && (net_host_flag != '\0'))
        {
          mp_cmd_change_timer();
        }
        break;
      case 599:
        civ_change_password_dialog(human_civ);
        break;
      case 600:
        mapview_zoom = 0xfff9;
        mapview_redraw((C_004083b0_430 *)&map_views,human_civ,1);
        break;
      case 0x259:
        if (game.multiplayer != '\0') {
          menu_multiplayer_options();
        }
        break;
      case 0x25a:
        mapview_zoom = 8;
        mapview_redraw((C_004083b0_430 *)&map_views,human_civ,1);
      }
    }
  }
  if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0'))
  goto switchD_00412ef0_default;
  if (param_1 < 0x332) {
    if (param_1 == 0x331) {
      tech_editor_run();
      goto switchD_00412ef0_default;
    }
    switch(param_1) {
    case 0x1b0:
      cheat_create_unit();
      break;
    case 0x1b1:
      cheat_reveal_map();
      break;
    case 0x1b2:
      cheat_set_human_player();
      break;
    case 0x1b3:
      cheat_set_game_year();
      break;
    case 0x1b4:
      cheat_kill_civ();
      break;
    case 0x1b5:
      cheat_tech_advance();
      break;
    case 0x1b6:
      cheat_force_government();
      break;
    case 0x1b7:
      cheat_terrain_saved_bits = 0xffffffff;
      goto switchD_00412f3a_caseD_3b7;
    case 0x1b8:
      cheat_change_money();
    }
  }
  else {
    switch(param_1) {
    case 0x332:
      city_editor_run();
      break;
    case 0x333:
      cosmic_editor_run();
      break;
    case 0x334:
      impr_editor_run();
      break;
    case 0x335:
      terrain_editor_open();
      break;
    case 0x336:
      tribe_editor_run();
      break;
    case 0x337:
      unit_editor_run();
      break;
    case 0x338:
      events_editor_open();
      break;
    case 0x343:
      cheat_edit_city();
      break;
    case 0x344:
      cheat_destroy_units_at_cursor();
      break;
    case 0x34b:
      cheat_edit_king();
      break;
    case 0x350:
      cheat_scenario_params();
      break;
    case 0x353:
      cheat_save_as_scenario();
      break;
    case 0x355:
      cheat_edit_unit();
      break;
    case 0x3b5:
      cheat_edit_technologies();
      break;
    case 0x3b7:
switchD_00412f3a_caseD_3b7:
      cheat_change_terrain();
    }
  }
switchD_00412ef0_default:
  switch(param_1) {
  case 0xa1:
  case 199:
    local_8 = 4;
    break;
  case 0xa2:
  case 0xc1:
    local_8 = 3;
    break;
  case 0xa3:
  case 0xc6:
    local_8 = 2;
    break;
  case 0xa4:
  case 0xc2:
    local_8 = 5;
    break;
  case 0xa6:
  case 0xc3:
    local_8 = 1;
    break;
  case 0xa7:
  case 0xc4:
    local_8 = 6;
    break;
  case 0xa8:
  case 0xc0:
    local_8 = 7;
    break;
  case 0xa9:
  case 0xc5:
    local_8 = 0;
  }
  if ((((-1 < game.active_unit) && (game.active_unit < game.num_units)) &&
      (units[game.active_unit].id != 0)) && (-1 < (int)local_8)) {
    if (moving_units_mode == 1) {
      unit_move_dir((int)game.active_unit,local_8,3);
    }
    else {
      map_cursor_step_dir(local_8);
    }
  }
  ui_input_busy = 0;
  return;
}
#undef blocked_input_char_pending
#undef blocked_input_kind
#undef cheat_terrain_saved_bits
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_turn_processing
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef game_session_active
#undef human_civ
#undef mapview_zoom
#undef moving_units_mode
#undef mp_open_game
#undef net_host_flag
#undef net_lock_map_busy
#undef net_unlock_map_busy
#undef prefs_game_options
#undef unit_create_busy
#undef unit_delete_busy
#undef unit_delete_cargo_busy
#undef unit_destroy_redraw_busy
#undef unit_gather_cargo_busy
#undef unit_lift_off_map_busy
#undef unit_relocate_busy
#undef unit_stack_bottom_busy
#undef unit_stack_link_busy
#undef unit_stack_unlink_busy
#undef _DAT_006c31b0
#undef local_8

/* 0041dd0e auto */
#define local_120 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_11c (*(char (*)[256])(frame_ + FRAME_OFF(4)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(260)))
#define local_18 (*(FILE * *)(frame_ + FRAME_OFF(264)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(268)))
#define local_10 (*(Tile * *)(frame_ + FRAME_OFF(272)))
#define local_c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(280)))
i32 __cdecl map_load_dialog(void)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  char *pcVar4;
  i8 *puVar5;
  i32 uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 1;
  local_18 = (FILE *)0x0;
  FUN_005f22d0(local_11c,&map_load_wildcard_str);
  iVar1 = save_file_filter(0,0,1);
  uVar7 = 0;
  uVar6 = 1;
  puVar5 = &map_load_default_ext_str;
  pcVar4 = local_11c;
  local_1c = iVar1;
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x40c));
  iVar3 = ui_file_name_dialog(ADDR(0x6553d8, ((u8 *)&g.d_006553d8)),iVar2,(iptr)pcVar4,iVar1,(iptr)puVar5,uVar6,uVar7);
  if (iVar3 != 0) {
    local_18 = _fopen(local_11c,&map_load_open_mode_str);
    if (local_18 == (FILE *)0x0) {
      popup_game(ADDR(0x6255ac, ((u8 *)&g.d_006255ac)));
    }
    else {
      iVar3 = map_read((iptr)local_18,1);
      if (iVar3 == 0) {
        local_10 = map_tiles;
        for (local_8 = 0; local_8 < map.area; local_8++) {
          local_10->improvements = '\0';
          local_10->radius = '\0';
          local_10->visible = '\0';
          local_10->landmass = '\0';
          local_10->owner = 0xf0;
          local_10++;
        }
        for (local_120 = 1; local_120 < 8; local_120++) {
          _memset(map_known[local_120],0,(int)map.area);
        }
        if (map.seed < 2) {
          map_new_seed();
        }
        else {
          iVar3 = popup_game(ADDR(0x6255cc, ((u8 *)&g.d_006255cc)));
          if (iVar3 == 0) {
            map_new_seed();
          }
          snd_play_effect(0x6a,0,0,0);
        }
        local_c = 0;
        for (local_8 = 0; local_8 < 0x15; local_8++) {
          if (-1 < start_x[local_8]) {
            local_c = 1;
            break;
          }
        }
        if ((local_c != 0) && (iVar3 = popup_game(ADDR(0x6255d4, ((u8 *)&g.d_006255d4))), iVar3 == 0)) {
          snd_play_effect(0x6a,0,0,0);
          for (local_8 = 0; local_8 < 0x15; local_8++) {
            start_x[local_8] = -1;
            start_y[local_8] = -1;
          }
        }
        if (map.flat == 0) {
          game.rules = game.rules & 0x7fff;
        }
        else {
          game.rules = game.rules | 0x8000;
        }
        local_14 = 0;
      }
      else {
        popup_game(ADDR(0x6255bc, ((u8 *)&g.d_006255bc)));
      }
    }
  }
  return local_14;
}
#undef local_120
#undef local_11c
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004272d0 auto */
void __cdecl tile_reveal_to_civ(iptr x,iptr y,int civ)

{
  int city;
  iptr unit;
  
  if (-1 < civ) {
    net_batch_begin();
    tile_set_visible(x,y,1 << ((byte)civ & 0x1f) & 0xff,1,1);
    tile_update_known(x,y,civ);
    city = city_at(x,y);
    if (city < 0) {
      unit = tile_first_unit(x,y);
      unit_stack_set_seen_by(unit,civ);
    }
    else {
      city_reveal_to_civ(city,civ);
    }
    net_batch_flush();
  }
  return;
}

/* 0042a6f8 auto */
void __cdecl tiles_dll_global_init(void)

{
  tiles_dll_static_init();
  tiles_dll_reg_atexit();
  return;
}

/* 0042a712 auto */
void __cdecl tiles_dll_static_init(void)

{
  resource_dll_load((DllHandle *)&tiles_dll,ADDR(0x625ed4, ((u8 *)&g.d_00625ed4)));
  return;
}

/* 0042a731 auto */
void __cdecl tiles_dll_reg_atexit(void)

{
  _atexit(tiles_dll_static_dtor);
  return;
}

/* 0042a74e auto */
void __cdecl tiles_dll_static_dtor(void)

{
  dll_free((DllHandle *)&tiles_dll);
  return;
}

/* 0043c3f0 auto */
DllHandle * __thiscall resource_dll_load(DllHandle *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = res_dll_load_library(param_1);
  this->hmodule = uVar1;
  return this;
}

/* 00447320 auto */
void __cdecl terrain_base_sprites_global_init(void)

{
  terrain_base_sprites_static_init();
  terrain_base_sprites_reg_atexit();
  return;
}

/* 0044733a auto */
void __cdecl terrain_base_sprites_static_init(void)

{
  FUN_005f2620(&terrain_base_sprites,0x3c,0xb,sprite_init,sprite_destroy);
  return;
}

/* 00447362 auto */
void __cdecl terrain_base_sprites_reg_atexit(void)

{
  _atexit(terrain_base_sprites_atexit_dtor);
  return;
}

/* 0044737f auto */
void __cdecl terrain_base_sprites_atexit_dtor(void)

{
  FUN_005f2490(&terrain_base_sprites,0x3c,0xb,sprite_destroy);
  return;
}

/* 004473a2 auto */
void __cdecl terrain_dither_sprites_global_init(void)

{
  terrain_dither_sprites_static_init();
  terrain_dither_sprites_reg_atexit();
  return;
}

/* 004473bc auto */
void __cdecl terrain_dither_sprites_static_init(void)

{
  FUN_005f2620(&terrain_dither_sprites,0x3c,0x34,sprite_init,sprite_destroy);
  return;
}

/* 004473e4 auto */
void __cdecl terrain_dither_sprites_reg_atexit(void)

{
  _atexit(terrain_dither_sprites_atexit_dtor);
  return;
}

/* 00447401 auto */
void __cdecl terrain_dither_sprites_atexit_dtor(void)

{
  FUN_005f2490(&terrain_dither_sprites,0x3c,0x34,sprite_destroy);
  return;
}

/* 00447424 auto */
void __cdecl river_sprites_global_init(void)

{
  river_sprites_static_init();
  river_sprites_reg_atexit();
  return;
}

/* 0044743e auto */
void __cdecl river_sprites_static_init(void)

{
  FUN_005f2620(&river_sprites,0x3c,0x10,sprite_init,sprite_destroy);
  return;
}

/* 00447466 auto */
void __cdecl river_sprites_reg_atexit(void)

{
  _atexit(river_sprites_atexit_dtor);
  return;
}

/* 00447483 auto */
void __cdecl river_sprites_atexit_dtor(void)

{
  FUN_005f2490(&river_sprites,0x3c,0x10,sprite_destroy);
  return;
}

/* 004474a6 auto */
void __cdecl forest_sprites_global_init(void)

{
  forest_sprites_static_init();
  forest_sprites_reg_atexit();
  return;
}

/* 004474c0 auto */
void __cdecl forest_sprites_static_init(void)

{
  FUN_005f2620(&forest_sprites,0x3c,0x10,sprite_init,sprite_destroy);
  return;
}

/* 004474e8 auto */
void __cdecl forest_sprites_reg_atexit(void)

{
  _atexit(forest_sprites_atexit_dtor);
  return;
}

/* 00447505 auto */
void __cdecl forest_sprites_atexit_dtor(void)

{
  FUN_005f2490(&forest_sprites,0x3c,0x10,sprite_destroy);
  return;
}

/* 00447528 auto */
void __cdecl mountain_sprites_global_init(void)

{
  mountain_sprites_static_init();
  mountain_sprites_reg_atexit();
  return;
}

/* 00447542 auto */
void __cdecl mountain_sprites_static_init(void)

{
  FUN_005f2620(&mountain_sprites,0x3c,0x10,sprite_init,sprite_destroy);
  return;
}

/* 0044756a auto */
void __cdecl mountain_sprites_reg_atexit(void)

{
  _atexit(mountain_sprites_atexit_dtor);
  return;
}

/* 00447587 auto */
void __cdecl mountain_sprites_atexit_dtor(void)

{
  FUN_005f2490(&mountain_sprites,0x3c,0x10,sprite_destroy);
  return;
}

/* 004475aa auto */
void __cdecl hill_sprites_global_init(void)

{
  hill_sprites_static_init();
  hill_sprites_reg_atexit();
  return;
}

/* 004475c4 auto */
void __cdecl hill_sprites_static_init(void)

{
  FUN_005f2620(&hill_sprites,0x3c,0x10,sprite_init,sprite_destroy);
  return;
}

/* 004475ec auto */
void __cdecl hill_sprites_reg_atexit(void)

{
  _atexit(hill_sprites_atexit_dtor);
  return;
}

/* 00447609 auto */
void __cdecl hill_sprites_atexit_dtor(void)

{
  FUN_005f2490(&hill_sprites,0x3c,0x10,sprite_destroy);
  return;
}

/* 0044762c auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl hut_sprite_global_init(void)

{
  hut_sprite_static_init();
  hut_sprite_reg_atexit();
  return;
}

/* 00447646 auto */
void __cdecl hut_sprite_static_init(void)

{
  sprite_init((Sprite *)&hut_sprite);
  return;
}

/* 00447660 auto */
void __cdecl hut_sprite_reg_atexit(void)

{
  _atexit(hut_sprite_atexit_dtor);
  return;
}

/* 0044767d auto */
void __cdecl hut_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)&hut_sprite);
  return;
}

/* 00447697 auto */
void __cdecl unused_sprite_pair_global_init(void)

{
  unused_sprite_pair_static_init();
  unused_sprite_pair_reg_atexit();
  return;
}

/* 004476b1 auto */
void __cdecl unused_sprite_pair_static_init(void)

{
  FUN_005f2620(&DAT_00644e88,0x3c,2,sprite_init,sprite_destroy);
  return;
}

/* 004476d9 auto */
void __cdecl unused_sprite_pair_reg_atexit(void)

{
  _atexit(unused_sprite_pair_atexit_dtor);
  return;
}

/* 004476f6 auto */
void __cdecl unused_sprite_pair_atexit_dtor(void)

{
  FUN_005f2490(&DAT_00644e88,0x3c,2,sprite_destroy);
  return;
}

/* 00447719 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl tile_pick_mask_sprite_global_init(void)

{
  tile_pick_mask_sprite_static_init();
  tile_pick_mask_sprite_reg_atexit();
  return;
}

/* 00447733 auto */
void __cdecl tile_pick_mask_sprite_static_init(void)

{
  sprite_init((Sprite *)&tile_pick_mask_sprite);
  return;
}

/* 0044774d auto */
void __cdecl tile_pick_mask_sprite_reg_atexit(void)

{
  _atexit(tile_pick_mask_sprite_atexit_dtor);
  return;
}

/* 0044776a auto */
void __cdecl tile_pick_mask_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)&tile_pick_mask_sprite);
  return;
}

/* 00447784 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl tile_direction_mask_sprite_global_init(void)

{
  tile_direction_mask_sprite_static_init();
  tile_direction_mask_sprite_reg_atexit();
  return;
}

/* 0044779e auto */
void __cdecl tile_direction_mask_sprite_static_init(void)

{
  sprite_init((Sprite *)&tile_direction_mask_sprite);
  return;
}

/* 004477b8 auto */
void __cdecl tile_direction_mask_sprite_reg_atexit(void)

{
  _atexit(tile_direction_mask_sprite_atexit_dtor);
  return;
}

/* 004477d5 auto */
void __cdecl tile_direction_mask_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)&tile_direction_mask_sprite);
  return;
}

/* 004477ef auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl unexplored_tile_sprite_global_init(void)

{
  unexplored_tile_sprite_static_init();
  unexplored_tile_sprite_reg_atexit();
  return;
}

/* 00447809 auto */
void __cdecl unexplored_tile_sprite_static_init(void)

{
  sprite_init((Sprite *)&unexplored_tile_sprite);
  return;
}

/* 00447823 auto */
void __cdecl unexplored_tile_sprite_reg_atexit(void)

{
  _atexit(unexplored_tile_sprite_atexit_dtor);
  return;
}

/* 00447840 auto */
void __cdecl unexplored_tile_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)&unexplored_tile_sprite);
  return;
}

/* 0044785a auto */
void __cdecl coast_quarter_sprites_global_init(void)

{
  coast_quarter_sprites_static_init();
  coast_quarter_sprites_reg_atexit();
  return;
}

/* 00447874 auto */
void __cdecl coast_quarter_sprites_static_init(void)

{
  FUN_005f2620(&coast_quarter_sprites,0x3c,0x20,sprite_init,sprite_destroy);
  return;
}

/* 0044789c auto */
void __cdecl coast_quarter_sprites_reg_atexit(void)

{
  _atexit(coast_quarter_sprites_atexit_dtor);
  return;
}

/* 004478b9 auto */
void __cdecl coast_quarter_sprites_atexit_dtor(void)

{
  FUN_005f2490(&coast_quarter_sprites,0x3c,0x20,sprite_destroy);
  return;
}

/* 004478dc auto */
void __cdecl river_mouth_sprites_global_init(void)

{
  river_mouth_sprites_static_init();
  river_mouth_sprites_reg_atexit();
  return;
}

/* 004478f6 auto */
void __cdecl river_mouth_sprites_static_init(void)

{
  FUN_005f2620(&river_mouth_sprites,0x3c,4,sprite_init,sprite_destroy);
  return;
}

/* 0044791e auto */
void __cdecl river_mouth_sprites_reg_atexit(void)

{
  _atexit(river_mouth_sprites_atexit_dtor);
  return;
}

/* 0044793b auto */
void __cdecl river_mouth_sprites_atexit_dtor(void)

{
  FUN_005f2490(&river_mouth_sprites,0x3c,4,sprite_destroy);
  return;
}

/* 0044795e auto */
void __cdecl road_sprites_global_init(void)

{
  road_sprites_static_init();
  road_sprites_reg_atexit();
  return;
}

/* 00447978 auto */
void __cdecl road_sprites_static_init(void)

{
  FUN_005f2620(&road_sprites,0x3c,0x12,sprite_init,sprite_destroy);
  return;
}

/* 004479a0 auto */
void __cdecl road_sprites_reg_atexit(void)

{
  _atexit(road_sprites_atexit_dtor);
  return;
}

/* 004479bd auto */
void __cdecl road_sprites_atexit_dtor(void)

{
  FUN_005f2490(&road_sprites,0x3c,0x12,sprite_destroy);
  return;
}

/* 004479e0 auto */
void __cdecl land_improvement_sprites_global_init(void)

{
  land_improvement_sprites_static_init();
  land_improvement_sprites_reg_atexit();
  return;
}

/* 004479fa auto */
void __cdecl land_improvement_sprites_static_init(void)

{
  FUN_005f2620(&land_improvement_sprites,0x3c,3,sprite_init,sprite_destroy);
  return;
}

/* 00447a22 auto */
void __cdecl land_improvement_sprites_reg_atexit(void)

{
  _atexit(land_improvement_sprites_atexit_dtor);
  return;
}

/* 00447a3f auto */
void __cdecl land_improvement_sprites_atexit_dtor(void)

{
  FUN_005f2490(&land_improvement_sprites,0x3c,3,sprite_destroy);
  return;
}

/* 00447a62 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl pollution_sprite_global_init(void)

{
  pollution_sprite_static_init();
  pollution_sprite_reg_atexit();
  return;
}

/* 00447a7c auto */
void __cdecl pollution_sprite_static_init(void)

{
  sprite_init((Sprite *)&pollution_sprite);
  return;
}

/* 00447a96 auto */
void __cdecl pollution_sprite_reg_atexit(void)

{
  _atexit(pollution_sprite_atexit_dtor);
  return;
}

/* 00447ab3 auto */
void __cdecl pollution_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)&pollution_sprite);
  return;
}

/* 00447acd auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl grassland_shield_sprite_global_init(void)

{
  grassland_shield_sprite_static_init();
  grassland_shield_sprite_reg_atexit();
  return;
}

/* 00447ae7 auto */
void __cdecl grassland_shield_sprite_static_init(void)

{
  sprite_init((Sprite *)&grassland_shield_sprite);
  return;
}

/* 00447b01 auto */
void __cdecl grassland_shield_sprite_reg_atexit(void)

{
  _atexit(grassland_shield_sprite_atexit_dtor);
  return;
}

/* 00447b1e auto */
void __cdecl grassland_shield_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)&grassland_shield_sprite);
  return;
}

/* 00447b38 auto */
void __cdecl terrain_resource_sprites_global_init(void)

{
  terrain_resource_sprites_static_init();
  terrain_resource_sprites_reg_atexit();
  return;
}

/* 00447b52 auto */
void __cdecl terrain_resource_sprites_static_init(void)

{
  FUN_005f2620(&terrain_resource_sprites,0x3c,0x16,sprite_init,sprite_destroy);
  return;
}

/* 00447b7a auto */
void __cdecl terrain_resource_sprites_reg_atexit(void)

{
  _atexit(terrain_resource_sprites_atexit_dtor);
  return;
}

/* 00447b97 auto */
void __cdecl terrain_resource_sprites_atexit_dtor(void)

{
  FUN_005f2490(&terrain_resource_sprites,0x3c,0x16,sprite_destroy);
  return;
}

/* 00447bba auto */
void __cdecl airbase_sprites_global_init(void)

{
  airbase_sprites_static_init();
  airbase_sprites_reg_atexit();
  return;
}

/* 00447bd4 auto */
void __cdecl airbase_sprites_static_init(void)

{
  FUN_005f2620(&airbase_sprites,0x3c,2,sprite_init,sprite_destroy);
  return;
}

/* 00447bfc auto */
void __cdecl airbase_sprites_reg_atexit(void)

{
  _atexit(airbase_sprites_atexit_dtor);
  return;
}

/* 00447c19 auto */
void __cdecl airbase_sprites_atexit_dtor(void)

{
  FUN_005f2490(&airbase_sprites,0x3c,2,sprite_destroy);
  return;
}

/* 00448098 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl map_cursor_sprite_global_init(void)

{
  map_cursor_sprite_static_init();
  map_cursor_sprite_reg_atexit();
  return;
}

/* 004480b2 auto */
void __cdecl map_cursor_sprite_static_init(void)

{
  sprite_init((Sprite *)&map_cursor_sprite);
  return;
}

/* 004480cc auto */
void __cdecl map_cursor_sprite_reg_atexit(void)

{
  _atexit(map_cursor_sprite_static_dtor);
  return;
}

/* 004480e9 auto */
void __cdecl map_cursor_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&map_cursor_sprite);
  return;
}

/* 0044847a auto */
void __cdecl resource_shortage_icon_sprites_global_init(void)

{
  resource_shortage_icon_sprites_static_init();
  resource_shortage_icon_sprites_reg_atexit();
  return;
}

/* 00448494 auto */
void __cdecl resource_shortage_icon_sprites_static_init(void)

{
  FUN_005f2620(&resource_shortage_icon_sprites,0x3c,6,sprite_init,sprite_destroy);
  return;
}

/* 004484bc auto */
void __cdecl resource_shortage_icon_sprites_reg_atexit(void)

{
  _atexit(resource_shortage_icon_sprites_static_dtor);
  return;
}

/* 004484d9 auto */
void __cdecl resource_shortage_icon_sprites_static_dtor(void)

{
  FUN_005f2490(&resource_shortage_icon_sprites,0x3c,6,sprite_destroy);
  return;
}

/* 00448acf auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl map_grid_sprite_global_init(void)

{
  map_grid_sprite_static_init();
  map_grid_sprite_reg_atexit();
  return;
}

/* 00448ae9 auto */
void __cdecl map_grid_sprite_static_init(void)

{
  sprite_init((Sprite *)&map_grid_sprite);
  return;
}

/* 00448b03 auto */
void __cdecl map_grid_sprite_reg_atexit(void)

{
  _atexit(map_grid_sprite_static_dtor);
  return;
}

/* 00448b20 auto */
void __cdecl map_grid_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&map_grid_sprite);
  return;
}

/* 00479d20 auto */
void __cdecl map_views_global_init(void)

{
  map_views_static_init();
  map_views_reg_atexit();
  return;
}

/* 00479d3a auto */
void __cdecl map_views_static_init(void)

{
  FUN_005f2620(&map_views,0x3f0,8,((void *)ADDR(0x004037f6, mapview_ctor)),((void *)ADDR(0x0040340e, mapview_dtor)));
  return;
}

/* 00479d65 auto */
void __cdecl map_views_reg_atexit(void)

{
  _atexit(map_views_atexit_dtor);
  return;
}

/* 00479d82 auto */
void __cdecl map_views_atexit_dtor(void)

{
  FUN_005f2490(&map_views,0x3f0,8,((void *)ADDR(0x0040340e, mapview_dtor)));
  return;
}

/* 0047a747 auto */
#define local_14 (*(char *)(frame_ + FRAME_OFF(4)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl tile_calc_coast_masks(iptr param_1,int param_2)

{
  char cVar1;
  iptr iVar2;
  iptr x;
  iptr iVar3;
  uptr uVar4;
  int iVar5;
  uptr uVar5;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 0; (int)local_c < 4; local_c++) {
    (&coast_quarter_land_masks)[local_c] = 0;
  }
  iVar2 = map_in_bounds(param_1,param_2);
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    for (local_c = 0; (int)local_c < 8; local_c++) {
      x = map_wrap_x((char)(&dir_dx_table)[local_c] + param_1);
      cVar1 = (&dir_dy_table)[local_c];
      iVar3 = map_in_bounds(x,cVar1 + param_2);
      if (iVar3 == 0) {
        local_14 = 7;
      }
      else {
        local_14 = tile_terrain(x,cVar1 + param_2);
      }
      if (local_14 != '\n') {
        local_8++;
        if ((local_c & 1) == 0) {
          iVar5 = (int)local_c >> 1;
          uVar5 = iVar5 + 1U & 3;
          (&coast_quarter_land_masks)[iVar5] = (&coast_quarter_land_masks)[iVar5] | 4;
          (&coast_quarter_land_masks)[uVar5] = (&coast_quarter_land_masks)[uVar5] | 1;
        }
        else {
          uVar4 = (local_c + 1 & 6) >> 1;
          (&coast_quarter_land_masks)[uVar4] = (&coast_quarter_land_masks)[uVar4] | 2;
        }
      }
    }
  }
  return local_8;
}
#undef local_14
#undef local_c
#undef local_8

/* 0047c2f2 auto */
i32 __cdecl map_x_in_span(int param_1,int param_2,int param_3)

{
  i32 uVar1;
  
  if ((game.rules & 0x8000) == 0) {
    if (param_1 < param_2) {
      param_1 += map.width;
    }
    if (param_2 + param_3 <= param_1) {
      param_1 -= map.width;
    }
  }
  if (param_1 < param_2) {
    uVar1 = 0;
  }
  else if ((param_2 + param_3) - param_1 < 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 0047c37f auto */
i32 __cdecl
map_tile_in_box(i32 param_1,int param_2,iptr param_3,iptr param_4,i32 param_5,int param_6
            )

{
  int iVar1;
  i32 uVar2;
  
  iVar1 = map_x_in_span(param_1,param_3,param_5);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (param_2 < param_4) {
    uVar2 = 0;
  }
  else if (param_2 < param_6 + param_4) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0047ce1e auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl
map_redraw_area_all_views(i32 param_1,i32 param_2,i32 param_3,iptr param_4,
            i32 param_5)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      mapview_redraw_area
                ((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),param_1,param_2,param_3,param_4
                 ,param_5);
    }
  }
  return;
}
#undef local_8

/* 0047cea6 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl map_redraw_tile_all_views(i32 param_1,i32 param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      mapview_redraw_tile
                ((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),param_1,param_2);
    }
  }
  return;
}
#undef local_8

/* 0047cf22 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl map_redraw_neighbors_all_views(i32 param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      mapview_redraw_tile_neighbors
                ((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),param_1,param_2);
    }
  }
  return;
}
#undef local_8

/* 0047cf9e auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl map_redraw_all_views(iptr param_1,i32 param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      mapview_redraw
                ((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),param_1,param_2);
    }
  }
  return;
}
#undef local_8

/* 00484d3b auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
void __cdecl map_display_disable(void)

{
  game_loop_active = 0;
  return;
}
#undef game_loop_active

/* 004868fb auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(12)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(32)))
void __cdecl map_apply_global_warming(uint param_1)

{
  char cVar1;
  byte bVar2;
  iptr x;
  int iVar4;
  byte *pbVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (autoplay_active == 0) {
    if (2 < game.multiplayer) {
      net_send_text_args(3,0xff,0,0,0,0);
    }
    popup_game_with_sprite(ADDR(0x62c5dc, ((u8 *)&g.d_0062c5dc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  y2 = 0;
  x2 = 0;
  net_batch_begin();
  for (local_20 = 0; local_20 < map.area; local_20++) {
    bVar2 = tile_terrain(x2,y2);
    if (bVar2 < 4) {
      local_14 = 0;
      for (local_8 = 0; local_8 < 0x14; local_8++) {
        x = map_wrap_x((int)(char)(&dir_dx_table)[local_8] + x2);
        cVar1 = (&dir_dy_table)[local_8];
        iVar4 = map_in_bounds(x,(int)cVar1 + y2);
        if ((iVar4 != 0) && (iVar4 = tile_is_ocean(x,(int)cVar1 + y2), iVar4 != 0)) {
          local_14++;
        }
      }
      if (local_14 < (int)(7 - param_1)) {
        if ((x2 * 3 + y2 * -3 & 7) == param_1) {
          iVar4 = tile_owner(x2,y2);
          if (iVar4 < 0) {
            tile_set_owner(x2,y2,0,1);
          }
          if (bVar2 < 2) {
            tile_set_terrain(x2,y2,0,1);
          }
          else {
            tile_set_terrain(x2,y2,1,1);
          }
          iVar4 = tile_visible_to(x2,y2,human_civ);
          if (iVar4 != 0) {
            map_redraw_tile_all_views(x2,y2);
          }
        }
      }
      else {
        iVar4 = tile_owner(x2,y2);
        if (iVar4 < 0) {
          tile_set_owner(x2,y2,0,1);
        }
        if (bVar2 == 3) {
          tile_set_terrain(x2,y2,9,1);
        }
        else {
          tile_set_terrain(x2,y2,8,1);
        }
        tile_set_improvements(x2,y2,0xc,0,1);
        for (local_24 = 1; local_24 < 8; local_24++) {
          iVar4 = tile_visible_to(x2,y2,local_24);
          if (((iVar4 != 0) &&
              (pbVar5 = (byte *)known_at(x2,y2,local_24), (*pbVar5 & 0xc) != 0)) &&
             (tile_update_known(x2,y2,local_24), human_civ == local_24)) {
            map_redraw_tile_all_views(x2,y2);
          }
        }
      }
    }
    x2 += 2;
    if ((int)map.width <= (int)x2) {
      y2++;
      x2 = y2 & 1;
    }
  }
  net_batch_flush();
  return;
}
#undef autoplay_active
#undef human_civ
#undef local_24
#undef local_20
#undef y2
#undef x2
#undef local_14
#undef local_8

/* 00487007 auto */
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(12)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(16)))
void __cdecl map_rebuild_unit_flags(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_tile_sync_enabled = 0;
  y2 = 0;
  x2 = 0;
  for (local_10 = 0; local_10 < map.area; local_10++) {
    tile_set_improvements(x2,y2,1,0,1);
    x2 += 2;
    if ((int)map.width <= (int)x2) {
      y2++;
      x2 = y2 & 1;
    }
  }
  for (unit = 0; unit < game.num_units; unit++) {
    if (units[unit].id != 0) {
      tile_set_improvements((int)units[unit].x,(int)units[unit].y,1,1,1);
    }
  }
  net_tile_sync_enabled = 1;
  net_send_state_diff(0xff,2,0,0,1);
  return;
}
#undef net_tile_sync_enabled
#undef unit
#undef local_10
#undef y2
#undef x2

/* 00488a45 auto */
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(i32 *)((u8 *)&g.d_0062d044))
#define path_road_planning (*(i32 *)((u8 *)&g.d_0062d040))
#define path_roads_only (*(i32 *)((u8 *)&g.d_0062d048))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define y3 (*(int *)(frame_ + FRAME_OFF(8)))
#define x3 (*(int *)(frame_ + FRAME_OFF(16)))
i32 __cdecl map_road_connection(iptr civ,int x,int y,int x2,int y2)

{
  bool bVar1;
  bool bVar2;
  iptr iVar3;
  iptr iVar4;
  i32 uVar3;
  int iVar5;
  uint uVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  x3 = x;
  y3 = y;
  iVar3 = tile_land_landmass(x,y);
  iVar4 = tile_land_landmass(x2,y2);
  local_20 = 0;
  bVar2 = true;
  if (iVar4 == iVar3) {
    iVar5 = map_distance(x2,y2,x,y);
    if (iVar5 < 0x17) {
      path_road_planning = 1;
      path_owner_civ = 0xffffffff;
      path_goal_x = x2;
      path_goal_y = y2;
      path_unit_type = 2;
      path_roads_only = 1;
      bVar1 = true;
      while( true ) {
        iVar5 = map_path_next_dir(x3,y3,99);
        if ((iVar5 < 0) || (iVar5 == 8)) goto LAB_00488ca7;
        x3 = map_wrap_x((char)(&dir_dx_table)[iVar5] + x3);
        y3 += (char)(&dir_dy_table)[iVar5];
        iVar5 = map_in_bounds(x3,y3);
        if (iVar5 == 0) goto LAB_00488ca7;
        if ((x3 == x2) && (y3 == y2)) break;
        iVar5 = tile_city_owner(x3,y3);
        if (civ == iVar5) {
          bVar1 = false;
          goto LAB_00488ca7;
        }
        if ((((-1 < iVar5) && ((*(byte *)&civs[civ].treaties[iVar5] & 8) == 0)) ||
            ((iVar5 = tile_city_or_unit_owner(x3,y3), 0 < iVar5 &&
             ((civ != iVar5 && ((*(byte *)&civs[civ].treaties[iVar5] & 8) == 0))))
            )) || (uVar6 = tile_improvements(x3,y3), (uVar6 & 0x10) == 0))
        goto LAB_00488ca7;
        uVar6 = tile_improvements(x3,y3);
        if ((uVar6 & 0x20) == 0) {
          bVar2 = false;
        }
        local_20++;
        if (0x32 < local_20) goto LAB_00488ca7;
      }
      bVar1 = false;
LAB_00488ca7:
      path_road_planning = 0;
      path_roads_only = 0;
      if (bVar1) {
        uVar3 = 0;
      }
      else if (bVar2) {
        uVar3 = 2;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}
#undef path_goal_x
#undef path_goal_y
#undef path_owner_civ
#undef path_road_planning
#undef path_roads_only
#undef local_20
#undef y3
#undef x3

/* 004abea0 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
iptr __cdecl map_dir_from_delta(int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 8;
  if (param_1 < 1) {
    if (param_1 < 0) {
      param_1 = -1;
    }
    else {
      param_1 = 0;
    }
  }
  else {
    param_1 = 1;
  }
  if (param_2 < 1) {
    if (param_2 < 0) {
      param_2 = -1;
    }
    else {
      param_2 = 0;
    }
  }
  else {
    param_2 = 1;
  }
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((char)(&dir_dx_table)[local_8] < 1) {
      if ((char)(&dir_dx_table)[local_8] < '\0') {
        local_10 = -1;
      }
      else {
        local_10 = 0;
      }
    }
    else {
      local_10 = 1;
    }
    if (param_1 == local_10) {
      if ((char)(&dir_dy_table)[local_8] < 1) {
        if ((char)(&dir_dy_table)[local_8] < '\0') {
          local_14 = -1;
        }
        else {
          local_14 = 0;
        }
      }
      else {
        local_14 = 1;
      }
      if (param_2 == local_14) {
        local_c = local_8;
      }
    }
  }
  return local_c;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004abfe5 auto */
#define map_view_center_x (*(i16 *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(i16 *)((u8 *)&g.d_0066ca8a))
#define mapview_zoom (*(short *)((u8 *)&g.d_0066ca8c))
#define path_debug_pending (*(int *)((u8 *)&g.d_0062d04c))
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(int *)((u8 *)&g.d_0062d044))
#define path_road_planning (*(int *)((u8 *)&g.d_0062d040))
#define path_roads_only (*(int *)((u8 *)&g.d_0062d048))
#define local_94 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(20)))
#define civ (*(int *)(frame_ + FRAME_OFF(24)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_50 (*(iptr *)(frame_ + FRAME_OFF(72)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(124)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(136)))
iptr __cdecl map_path_next_dir(int x,int y,int param_3)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  byte terrain;
  int y4;
  int iVar8;
  iptr unit;
  uint uVar10;
  byte *pbVar11;
  int iVar12;
  int y3;
  iptr x3;
  int iVar15;
  int y2;
  i32 uVar17;
  iptr x2;
  int iVar19;
  bool bVar20;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  civ = 0;  /* stale stack the original reads (FRAME_PRESETS) */
  
  iVar19 = path_debug_pending;
  path_grid_center_x = path_goal_x;
  path_grid_center_y = path_goal_y;
  bVar20 = unit_types[path_unit_type].domain == 2;
  bVar2 = (int)(uint)cosmic.road_move_mult < (int)(char)unit_types[path_unit_type].move;
  if ((bVar20) && (y4 = tile_is_ocean(x,y), y4 == 0)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  path_result_cost = 0;
  local_40 = x - path_grid_center_x;
  if ((game.rules & 0x8000) == 0) {
    if (local_40 < 0) {
      local_40 += map.width;
    }
    if ((int)map.width >> 1 <= local_40) {
      local_40 -= map.width;
    }
  }
  local_40 += path_grid_center_x;
  if (((path_goal_x != path_flood_goal_x) || (path_goal_y != path_flood_goal_y)) ||
     (y4 = path_grid_get_cost(local_40,y), y4 == 0)) {
    path_flood_goal_x = path_goal_x;
    path_flood_goal_y = path_goal_y;
    _memset(&path_cost_grid,0,0x2400);
    path_queue_head = 0;
    path_queue_x = path_goal_x;
    path_queue_y = path_goal_y;
    path_queue_tail = 1;
    path_grid_set_cost(path_goal_x,path_goal_y,1);
    path_result_cost = param_3;
    do {
      x3 = (&path_queue_x)[path_queue_head];
      y4 = (&path_queue_y)[path_queue_head];
      path_queue_head++;
      if (0x8ff < path_queue_head) {
        path_queue_head = 0;
      }
      y3 = map_wrap_x(x3);
      iVar15 = path_grid_get_cost(x3,y4);
      iVar12 = path_result_cost;
      if ((iVar15 <= path_result_cost) && ((y3 != x || (iVar12 = iVar15, y4 != y))))
      {
        uVar10 = tile_improvements(y3,y4);
        if (((uVar10 & 0x10) == 0) && (iVar12 = tile_city_owner(y3,y4), iVar12 < 0)) {
          bVar4 = false;
        }
        else {
          bVar4 = true;
        }
        pbVar11 = (byte *)tile_at(y3,y4);
        bVar1 = *pbVar11;
        uVar10 = tile_improvements(y3,y4);
        if (((uVar10 & 0x20) == 0) && (iVar12 = tile_city_owner(y3,y4), iVar12 < 0)) {
          bVar5 = false;
        }
        else {
          bVar5 = true;
        }
        for (local_1c = 0; iVar12 = path_result_cost, local_1c < 8; local_1c++) {
          iVar12 = (char)(&dir_dx_table)[local_1c] + x3;
          y2 = (char)(&dir_dy_table)[local_1c] + y4;
          x2 = map_wrap_x(iVar12);
          if (iVar12 - path_goal_x < 1) {
            local_7c = ~(iVar12 - path_goal_x) + 1;
          }
          else {
            local_7c = iVar12 - path_goal_x;
          }
          if (y2 - path_goal_y < 1) {
            local_84 = ~(y2 - path_goal_y) + 1;
          }
          else {
            local_84 = y2 - path_goal_y;
          }
          if (((int)(local_84 + local_7c & 0xfffffffeU) < 0x30) &&
             (iVar8 = map_in_bounds(x2,y2), iVar8 != 0)) {
            terrain = tile_terrain(x2,y2);
            if (((((terrain == 10) == bVar20) || ((x == x2 && (y2 == y)))) ||
                ((path_flood_goal_x == x2 && (y2 == path_flood_goal_y)))) &&
               ((!bVar3 ||
                ((iVar8 = tile_landmass(x2,y2), iVar8 != 0x3f &&
                 (*(short *)(&water_body_sizes + iVar8 * 0x10) != 1)))))) {
              local_30 = iVar15;
              if (-1 < path_owner_civ) {
                civ = tile_city_or_unit_owner(x2,y2);
                if ((-1 < civ) && (path_owner_civ != civ)) goto LAB_004ac32b;
                if ((path_owner_civ == civ) &&
                   ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 &&
                     (uVar17 = tile_improvements(x2,y2), ((byte)uVar17 & 0x43) == 1)) &&
                    (iVar8 = tile_adjacent_nonallied_unit(x2,y2,civ), iVar8 != 0)))) {
                  unit = tile_first_unit(x2,y2);
                  iVar8 = unit_stack_count_role(unit,(int)(char)unit_types[path_unit_type].role);
                  local_30 = iVar15 + iVar8 * 0x10;
                }
                iVar8 = tile_owner_at_peace(x2,y2,path_owner_civ);
                if ((-1 < iVar8) && ((char)unit_types[path_unit_type].role < 5)) {
                  local_30 += (uint)cosmic.road_move_mult * 4;
                }
              }
              if ((path_road_planning != 0) ||
                 ((bVar5 && ((uVar10 = tile_improvements(x2,y2), (uVar10 & 0x20) != 0 ||
                             (iVar8 = tile_city_owner(x2,y2), -1 < iVar8)))))) {
                local_30++;
              }
              else if ((unit_types[path_unit_type].flags & 0x200) == 0) {
                if ((bVar4) &&
                   ((uVar10 = tile_improvements(x2,y2), (uVar10 & 0x10) != 0 ||
                    (iVar8 = tile_city_owner(x2,y2), -1 < iVar8)))) {
                  local_30 += 4;
                }
                else {
                  if (path_roads_only != 0) goto LAB_004ac32b;
                  if ((((bVar1 & 0x80) != 0) &&
                      (pbVar11 = (byte *)tile_at(x2,y2), (*pbVar11 & 0x80) != 0)) &&
                     (iVar8 = map_dx_wrapped(y3,x2), iVar8 == 1)) {
                    if (y4 == y2 || y4 - y2 < 0) {
                      local_90 = ~(y4 - y2) + 1;
                    }
                    else {
                      local_90 = y4 - y2;
                    }
                    if (local_90 == 1) {
                      local_30 += 4;
                      goto LAB_004ac755;
                    }
                  }
                  if (bVar2) {
                    local_30 = local_30 +
                               (int)(char)terrain_types[terrain].move_cost *
                               (uint)cosmic.road_move_mult * 4;
                  }
                  else {
                    local_30 += (uint)cosmic.road_move_mult * 4;
                  }
                }
              }
              else {
                local_30 += 4;
              }
LAB_004ac755:
              if (((unit_types[path_unit_type].flags & 0x20) != 0) &&
                 (pbVar11 = (byte *)tile_at(x2,y2), (*pbVar11 & 0x40) != 0)) {
                local_30 += (uint)cosmic.road_move_mult * 4;
              }
              iVar8 = path_grid_get_cost(iVar12,y2);
              if ((iVar8 == 0) || (local_30 < iVar8)) {
                path_grid_set_cost(iVar12,y2,local_30);
                (&path_queue_x)[path_queue_tail] = iVar12;
                (&path_queue_y)[path_queue_tail] = y2;
                path_queue_tail++;
                if (0x8ff < path_queue_tail) {
                  path_queue_tail = 0;
                }
                if (path_queue_head == path_queue_tail) goto LAB_004ac850;
              }
            }
          }
LAB_004ac32b: ;
        }
      }
      path_result_cost = iVar12;
    } while ((path_queue_head != path_queue_tail) && (path_queue_head != 0));
  }
LAB_004ac850:
  local_50 = -1;
  if (path_result_cost < param_3) {
    local_10 = 19999;
    local_20 = 19999;
    uVar10 = tile_improvements(x,y);
    if (((uVar10 & 0x10) == 0) && (y4 = tile_city_owner(x,y), y4 < 0)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    pbVar11 = (byte *)tile_at(x,y);
    bVar1 = *pbVar11;
    uVar10 = tile_improvements(x,y);
    if (((uVar10 & 0x20) == 0) && (y4 = tile_city_owner(x,y), y4 < 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    y4 = path_grid_get_cost(local_40,y);
    for (local_1c = 0; local_1c < 8; local_1c++) {
      iVar12 = (char)(&dir_dx_table)[local_1c] + x;
      y3 = (char)(&dir_dy_table)[local_1c] + y;
      x3 = map_wrap_x(iVar12);
      if (iVar12 - path_goal_x < 1) {
        local_7c = ~(iVar12 - path_goal_x) + 1;
      }
      else {
        local_7c = iVar12 - path_goal_x;
      }
      if (y3 - path_goal_y < 1) {
        local_84 = ~(y3 - path_goal_y) + 1;
      }
      else {
        local_84 = y3 - path_goal_y;
      }
      if (((int)(local_84 + local_7c & 0xfffffffeU) < 0x30) &&
         (iVar15 = map_in_bounds(x3,y3), iVar15 != 0)) {
        terrain = tile_terrain(x3,y3);
        if ((((terrain == 10) == bVar20) || ((x == x3 && (y3 == y)))) ||
           ((path_flood_goal_x == x3 && (y3 == path_flood_goal_y)))) {
          local_3c = iVar12 - path_grid_center_x;
          if ((game.rules & 0x8000) == 0) {
            if (local_3c < 0) {
              local_3c += map.width;
            }
            if ((int)map.width >> 1 <= local_3c) {
              local_3c -= map.width;
            }
          }
          iVar15 = path_grid_get_cost(local_3c + path_grid_center_x,y3);
          if (((((iVar15 == 0) || (path_owner_civ < 0)) ||
               (civ = tile_city_or_unit_owner(x3,y3), civ < 0)) ||
              (path_owner_civ == civ)) && ((iVar15 != 0 && (iVar15 < y4)))) {
            if (path_road_planning == 0) {
              if ((bVar4) &&
                 ((uVar10 = tile_improvements(x3,y3), (uVar10 & 0x20) != 0 ||
                  (y2 = tile_city_owner(x3,y3), -1 < y2)))) {
                local_58 = 1;
              }
              else if ((unit_types[path_unit_type].flags & 0x200) == 0) {
                if ((bVar3) &&
                   ((uVar10 = tile_improvements(x3,y3), (uVar10 & 0x10) != 0 ||
                    (y2 = tile_city_owner(x3,y3), -1 < y2)))) {
                  local_58 = 4;
                }
                else {
                  if (path_roads_only != 0) goto LAB_004ac936;
                  if ((((bVar1 & 0x80) != 0) &&
                      (pbVar11 = (byte *)tile_at(x3,y3), (*pbVar11 & 0x80) != 0)) &&
                     (y2 = map_dx_wrapped(x,x3), y2 == 1)) {
                    if (y == y3 || y - y3 < 0) {
                      local_94 = ~(y - y3) + 1;
                    }
                    else {
                      local_94 = y - y3;
                    }
                    if (local_94 == 1) {
                      local_58 = 4;
                      goto LAB_004acce1;
                    }
                  }
                  if (bVar2) {
                    local_58 = (int)(char)terrain_types[terrain].move_cost *
                               (uint)cosmic.road_move_mult * 4;
                  }
                  else {
                    local_58 = (uint)cosmic.road_move_mult << 2;
                  }
                }
              }
              else {
                local_58 = 4;
              }
LAB_004acce1:
              if (((unit_types[path_unit_type].flags & 0x20) != 0) &&
                 (pbVar11 = (byte *)tile_at(x3,y3), (*pbVar11 & 0x40) != 0)) {
                local_58 += (uint)cosmic.road_move_mult * 4;
              }
              if (((path_owner_civ == civ) &&
                  ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) &&
                 ((uVar17 = tile_improvements(x3,y3), ((byte)uVar17 & 0x43) == 1 &&
                  (y2 = tile_adjacent_nonallied_unit(x3,y3,civ), y2 != 0)))) {
                x2 = tile_first_unit(x3,y3);
                y2 = unit_stack_count_role(x2,(int)(char)unit_types[path_unit_type].role);
                local_58 += y2 * 8;
              }
              y2 = tile_owner_at_peace(x3,y3,path_owner_civ);
              if ((-1 < y2) && ((char)unit_types[path_unit_type].role < 5)) {
                local_58 += (uint)cosmic.road_move_mult * 4;
              }
            }
            else {
              local_58 = 1;
            }
            iVar15 += local_58;
            if (iVar15 <= local_10) {
              iVar12 = map_distance_diag(path_goal_x,path_goal_y,iVar12,y3);
              if (iVar15 < local_10) {
                local_50 = local_1c;
                local_20 = iVar12;
                local_10 = iVar15;
              }
              else if (iVar12 < local_20) {
                local_50 = local_1c;
                local_20 = iVar12;
              }
            }
          }
        }
      }
LAB_004ac936: ;
    }
  }
  if (local_50 < 0) {
    path_goal_x = path_flood_goal_x;
    path_goal_y = path_flood_goal_y;
  }
  if (iVar19 != 0) {
    map_view_center_x = (i16)x;
    mapview_center_y = (i16)y;
    while( true ) {
      while( true ) {
        while( true ) {
          while( true ) {
            mapview_redraw((C_004083b0_430 *)&map_views,-1,1);
            for (local_54 = 0; local_54 < 0x30; local_54++) {
              for (local_60 = 0; local_60 < 0x30; local_60++) {
                if (*(int *)(&path_cost_grid + local_60 * 4 + local_54 * 0xc0) != 0) {
                  mapview_draw_tile_number(local_60 - 0x18 + local_54 - 0x18 + path_grid_center_x,
                                     ((local_60 - 0x18) - (local_54 - 0x18)) + path_grid_center_y,
                                     *(i32 *)(&path_cost_grid + local_60 * 4 + local_54 * 0xc0)
                                     ,0x29);
                }
              }
            }
            iVar19 = popup_debug_text(ADDR(0x62d054, ((u8 *)&g.d_0062d054)));
            if (iVar19 != 1) break;
            mapview_zoom--;
          }
          if (iVar19 != 2) break;
          mapview_zoom++;
        }
        if (iVar19 != 3) break;
        mapview_center_on((C_004083b0_430 *)&map_views,x,y);
      }
      if (iVar19 != 4) break;
      mapview_center_on((C_004083b0_430 *)&map_views,path_goal_x,path_goal_y);
    }
  }
  return local_50;
}
#undef map_view_center_x
#undef mapview_center_y
#undef mapview_zoom
#undef path_debug_pending
#undef path_goal_x
#undef path_goal_y
#undef path_owner_civ
#undef path_road_planning
#undef path_roads_only
#undef local_94
#undef local_90
#undef local_84
#undef civ
#undef local_7c
#undef local_60
#undef local_58
#undef local_54
#undef local_50
#undef local_40
#undef local_3c
#undef local_30
#undef local_20
#undef local_1c
#undef local_10

/* 004ad0d1 auto */
#define path_goal_x (*(int *)((u8 *)&g.d_00673fa0))
#define path_goal_y (*(int *)((u8 *)&g.d_00673fa4))
#define path_owner_civ (*(i32 *)((u8 *)&g.d_0062d044))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
int __cdecl
map_path_length(int x,int y,int param_3,int param_4,int param_5,i32 param_6)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = path_owner_civ;
  if (x == param_3 || x - param_3 < 0) {
    local_14 = ~(x - param_3) + 1;
  }
  else {
    local_14 = x - param_3;
  }
  if (((game.rules & 0x8000) == 0) && ((int)map.width >> 1 < local_14)) {
    local_14 = map.width - local_14;
  }
  if (y == param_4 || y - param_4 < 0) {
    local_18 = ~(y - param_4) + 1;
  }
  else {
    local_18 = y - param_4;
  }
  iVar2 = local_18 + local_14 >> 1;
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else if (iVar2 < 0x17) {
    if (param_5 == 0) {
      path_unit_type = 2;
    }
    else {
      path_unit_type = 0x21;
    }
    path_goal_x = param_3;
    path_goal_y = param_4;
    path_owner_civ = 0xffffffff;
    iVar2 = map_path_next_dir(x,y,param_6);
    if (-1 < iVar2) {
      iVar2 = path_result_cost;
    }
  }
  else {
    iVar2 = -1;
  }
  path_owner_civ = uVar1;
  return iVar2;
}
#undef path_goal_x
#undef path_goal_y
#undef path_owner_civ
#undef local_18
#undef local_14

/* 004ad784 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl map_diag_tile_by_ocean(int param_1,int param_2,iptr param_3,iptr param_4,int param_5)

{
  iptr x;
  int y;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while( true ) {
    if (1 < local_8) {
      return 0;
    }
    x = map_wrap_x(param_1 + local_8);
    y = param_2 + local_8;
    iVar3 = map_in_bounds(x,y);
    if ((iVar3 != 0) && (iVar3 = tile_is_ocean(x,y), iVar3 == param_5)) break;
    local_8++;
  }
  *(iptr *)param_3 = x;
  *(int *)param_4 = y;
  return 1;
}
#undef local_8

/* 004aee90 auto */
u8 * __cdecl map_coarse0_at(int param_1,int param_2)

{
  return map_coarse[0] + map.quarter_w * param_2 + param_1;
}

/* 004aeec0 auto */
u8 * __cdecl map_coarse1_at(int param_1,int param_2)

{
  return map_coarse[1] + map.quarter_w * param_2 + param_1;
}

/* 004aeef0 auto */
u8 * __cdecl map_coarse2_at(int param_1,int param_2)

{
  return map_coarse[2] + map.quarter_w * param_2 + param_1;
}

/* 004b3110 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(byte (*)[4])(frame_ + FRAME_OFF(8)))
void __cdecl landmass_set_border_bit(int param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bit_index_split(param_2,(iptr)&local_c,(iptr)local_8);
  (&landmass_border_bits)[param_1 * 0x10 + local_c] = (&landmass_border_bits)[param_1 * 0x10 + local_c] | local_8[0]
  ;
  return;
}
#undef local_c
#undef local_8

/* 004b315c auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(4)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(16)))
void __cdecl landmass_compute_borders(void)

{
  int y;
  i32 uVar2;
  iptr x;
  int iVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_18 = 0; local_18 < 0x40; local_18++) {
    for (local_8 = 0; (int)local_8 < 8; local_8++) {
      (&landmass_border_bits)[local_8 + local_18 * 0x10] = 0;
    }
  }
  for (y2 = 0; (int)y2 < (int)map.height; y2++) {
    for (x2 = (uint)((y2 & 1) != 0); (int)x2 < (int)map.width;
        x2 = x2 + 2) {
      y = tile_is_ocean(x2,y2);
      if (y == 0) {
        uVar2 = tile_landmass(x2,y2);
        for (local_8 = 0; (int)local_8 < 8; local_8++) {
          x = map_wrap_x((int)(char)(&dir_dx_table)[local_8] + x2);
          y = (int)(char)(&dir_dy_table)[local_8] + y2;
          iVar4 = map_in_bounds(x,y);
          if ((iVar4 != 0) && (iVar4 = tile_is_ocean(x,y), iVar4 != 0)) {
            uVar5 = tile_landmass(x,y);
            landmass_set_border_bit(uVar2,uVar5);
            local_8 += (2 - (local_8 & 1));
          }
        }
      }
    }
    ui_pump_messages_net();
  }
  return;
}
#undef local_18
#undef y2
#undef x2
#undef local_8

/* 004b32fe auto */
#define local_68 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_54 (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_4c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_44 (*(uint *)(frame_ + FRAME_OFF(36)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(40)))
#define local_38 (*(u8 * *)(frame_ + FRAME_OFF(48)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(52)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_28 (*(ushort * *)(frame_ + FRAME_OFF(64)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(76)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(84)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(96)))
uint __cdecl map_assign_landmass_ids(void)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  iptr iVar4;
  void *_Dst;
  ushort *_Dst_00;
  int iVar5;
  uptr uVar6;
  uint uVar7;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_44 = 0;
  local_4c = 0;
  for (local_50 = 0; local_50 < 0x40; local_50++) {
    *(i16 *)(&landmass_table + local_50 * 0x10) = 0;
    *(i16 *)(&water_body_sizes + local_50 * 0x10) = 0;
  }
  iVar4 = mem_handle_alloc_tracked(0x20000);
  _Dst = (void *)mem_lock_handle(iVar4);
  if (_Dst == (void *)0x0) {
    error_report(0xfffffff7,8,0,1,0);
  }
  else {
    local_4c = mem_handle_alloc_tracked((int)map.area << 2);
    _Dst_00 = (ushort *)mem_lock_handle(local_4c);
    if (_Dst_00 == (ushort *)0x0) {
      error_report(0xfffffff7,8,0,2,0);
    }
    else {
      map_fill_tile_byte((iptr)&map_tiles->landmass,0);
      for (local_18 = 1; -1 < local_18; local_18--) {
        _memset(_Dst,0,0x20000);
        _memset(_Dst_00,0,(int)map.area << 2);
        local_14 = 0;
        local_54 = 0;
        bVar3 = false;
        for (y2 = 0; (int)y2 < (int)map.height; y2++) {
          if ((game.rules & 0x8000) != 0) {
            bVar3 = false;
            local_54 = 0;
          }
          for (x2 = (uint)((y2 & 1) != 0); (int)x2 < (int)map.width;
              x2 = x2 + 2) {
            iVar5 = tile_is_ocean(x2,y2);
            if (iVar5 == local_18) {
              if (y2 != 0) {
                for (local_10 = 0; local_10 < 3; local_10++) {
                  uVar6 = local_10 - 2U & 7;
                  uVar7 = map_wrap_x((int)(char)(&dir_dx_table)[uVar6] + x2);
                  cVar2 = (&dir_dy_table)[uVar6];
                  iVar5 = map_in_bounds(uVar7,(int)cVar2 + y2);
                  if ((iVar5 != 0) &&
                     (uVar7 = (uint)*(ushort *)
                                     (((int)map.width & 0xfffffffeU) * ((int)cVar2 + y2) +
                                      (uVar7 & 0xfffffffe) + (int)_Dst_00), uVar7 != 0)) {
                    local_8 = uVar7;
                    if ((local_54 != 0) && (uVar7 != local_54)) {
                      if ((int)local_54 <= (int)uVar7) {
                        local_8 = local_54;
                      }
                      if ((int)uVar7 <= (int)local_54) {
                        uVar7 = local_54;
                      }
                      piVar1 = (int *)((int)_Dst + local_8 * 4);
                      *piVar1 = *piVar1 + *(int *)((int)_Dst + uVar7 * 4);
                      *(i32 *)((int)_Dst + uVar7 * 4) = 0;
                      local_28 = _Dst_00;
                      for (local_1c = 0; (int)local_1c <= (int)y2; local_1c++) {
                        for (local_68 = (uint)((local_1c & 1) != 0); (int)local_68 < (int)map.width;
                            local_68 = local_68 + 2) {
                          if ((uint)*local_28 == (uVar7 & 0xffff)) {
                            *local_28 = (ushort)local_8;
                          }
                          local_28++;
                        }
                      }
                    }
                    local_54 = local_8;
                  }
                }
              }
              if (local_54 == 0) {
                if (!bVar3) {
                  local_14 = 0;
                  do {
                    local_14++;
                    if (0x7ffe < (int)local_14) break;
                  } while (*(int *)((int)_Dst + local_14 * 4) != 0);
                }
                local_54 = local_14;
              }
              *(short *)(((int)map.width & 0xfffffffeU) * y2 + (x2 & 0xfffffffe) +
                        (int)_Dst_00) = (short)local_54;
              piVar1 = (int *)((int)_Dst + local_54 * 4);
              *piVar1 = *piVar1 + 1;
              bVar3 = true;
            }
            else {
              bVar3 = false;
              local_54 = 0;
            }
          }
          ui_pump_messages_net();
        }
        if (local_18 != 0) {
          local_30 = 0;
          for (local_50 = 0; local_50 < 0x3f; local_50++) {
            if (*(int *)((int)_Dst + local_50 * 4) < 9) {
              *(int *)((int)_Dst + 0xfc) =
                   *(int *)((int)_Dst + 0xfc) + *(int *)((int)_Dst + local_50 * 4);
              *(i32 *)((int)_Dst + local_50 * 4) = 0xffffffff;
              local_30++;
            }
          }
          if (local_30 != 0) {
            local_28 = _Dst_00;
            for (local_10 = 0; local_10 < map.area; local_10++) {
              if (*(int *)((int)_Dst + (uint)*local_28 * 4) < 0) {
                *local_28 = 0x3f;
              }
              local_28++;
            }
            for (local_50 = 0; local_50 < 0x3f; local_50++) {
              if (*(int *)((int)_Dst + local_50 * 4) < 0) {
                *(i32 *)((int)_Dst + local_50 * 4) = 0;
              }
            }
          }
        }
        local_38 = &map_tiles->landmass;
        local_28 = _Dst_00;
        for (local_10 = 0; local_10 < map.area; local_10++) {
          if (*local_28 != 0) {
            if (0x3f < *local_28) {
              if (*(int *)((int)_Dst + (uint)*local_28 * 4) < 1) {
                if (*(int *)((int)_Dst + (uint)*local_28 * 4) < 1) {
                  *local_28 = ~(ushort)*(i32 *)((int)_Dst + (uint)*local_28 * 4) + 1;
                }
                else {
                  *local_28 = (ushort)*(i32 *)((int)_Dst + (uint)*local_28 * 4);
                }
              }
              else {
                local_14 = 0;
                do {
                  local_14++;
                } while (*(int *)((int)_Dst + local_14 * 4) != 0);
                if (((int)local_14 < 0x40) &&
                   ((local_18 == 0 || (0x10 < *(int *)((int)_Dst + (uint)*local_28 * 4))))) {
                  *(i32 *)((int)_Dst + local_14 * 4) =
                       *(i32 *)((int)_Dst + (uint)*local_28 * 4);
                  *(uint *)((int)_Dst + (uint)*local_28 * 4) = -local_14;
                  *local_28 = (ushort)local_14;
                }
                else {
                  local_44 = local_44 | 1 << ((byte)local_18 & 0x1f);
                  *local_28 = 0x3f;
                }
              }
            }
            *local_38 = (u8)*local_28;
          }
          local_28++;
          local_38 += 6;
          ui_pump_messages_net();
        }
        for (local_20 = 0; local_20 < 0x40; local_20++) {
          if (local_18 == 0) {
            *(short *)(&landmass_table + local_20 * 0x10) =
                 (short)*(i32 *)((int)_Dst + local_20 * 4);
          }
          else {
            *(short *)(&water_body_sizes + local_20 * 0x10) =
                 (short)*(i32 *)((int)_Dst + local_20 * 4);
          }
        }
      }
      landmass_compute_borders();
    }
  }
  mem_unlock_handle(local_4c);
  mem_free_handle(local_4c);
  mem_unlock_handle(iVar4);
  mem_free_handle(iVar4);
  return local_44;
}
#undef local_68
#undef local_54
#undef local_50
#undef local_4c
#undef local_44
#undef y2
#undef local_38
#undef x2
#undef local_30
#undef local_28
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 00519200 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl terrain_editor_load_rules(void)

{
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (terrain2 = 0; terrain2 < 0x21; terrain2++) {
    _Count = 0x28;
    _Source = (char *)label_string(terrain_types[terrain2].name);
    _strncpy(&editor_item_names + terrain2 * 0x28,_Source,_Count);
    (&editor_item_name_ends)[terrain2 * 0x28] = 0;
    *(int *)(&editor_items + terrain2 * 0x58) = (int)(char)terrain_types[terrain2].move_cost;
    *(int *)(&editor_item_field1 + terrain2 * 0x58) = (int)(char)terrain_types[terrain2].defense;
    for (local_c = 0; local_c < 3; local_c++) {
      *(int *)(&editor_item_field2 + local_c * 4 + terrain2 * 0x58) =
           (int)*(char *)(local_c + ADDR(0x627cca, ((u8 *)&terrain_types + 10)) + terrain2 * 0x18);
    }
    if (terrain2 < 0xb) {
      for (local_c = 0; local_c < 2; local_c++) {
        *(int *)(&editor_item_field5 + local_c * 0x10 + terrain2 * 0x58) =
             (int)*(char *)(local_c + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18);
        *(int *)(&editor_item_field6 + local_c * 0x10 + terrain2 * 0x58) =
             (int)*(char *)(local_c + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18);
        *(int *)(&editor_item_field7 + local_c * 0x10 + terrain2 * 0x58) =
             (int)*(char *)(local_c + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18);
        *(int *)(&editor_item_field8 + local_c * 0x10 + terrain2 * 0x58) =
             (int)*(char *)(local_c + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + terrain2 * 0x18);
      }
      *(int *)(&editor_item_field13 + terrain2 * 0x58) = (int)terrain_types[terrain2].transform_to;
    }
  }
  return;
}
#undef local_c
#undef terrain2

/* 005193ed auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl terrain_editor_store_rules(void)

{
  char *_Dest;
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (terrain2 = 0; terrain2 < 0x21; terrain2++) {
    _Count = 0xf;
    _Source = &editor_item_names + terrain2 * 0x28;
    _Dest = (char *)label_string(terrain_types[terrain2].name);
    _strncpy(_Dest,_Source,_Count);
    terrain_types[terrain2].move_cost = (&editor_items)[terrain2 * 0x58];
    terrain_types[terrain2].defense = (&editor_item_field1)[terrain2 * 0x58];
    for (local_c = 0; local_c < 3; local_c++) {
      *(i8 *)(local_c + ADDR(0x627cca, ((u8 *)&terrain_types + 10)) + terrain2 * 0x18) =
           (&editor_item_field2)[local_c * 4 + terrain2 * 0x58];
    }
    if (terrain2 < 0xb) {
      for (local_c = 0; local_c < 2; local_c++) {
        *(i8 *)(local_c + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18) =
             (&editor_item_field5)[local_c * 0x10 + terrain2 * 0x58];
        *(i8 *)(local_c + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18) =
             (&editor_item_field6)[local_c * 0x10 + terrain2 * 0x58];
        *(i8 *)(local_c + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18) =
             (&editor_item_field7)[local_c * 0x10 + terrain2 * 0x58];
        *(i8 *)(local_c + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + terrain2 * 0x18) =
             (&editor_item_field8)[local_c * 0x10 + terrain2 * 0x58];
      }
      terrain_types[terrain2].transform_to = (&editor_item_field13)[terrain2 * 0x58];
    }
  }
  return;
}
#undef local_c
#undef terrain2

/* 005195c4 auto */
int __cdecl terrain_editor_terrain_to_sel(int param_1)

{
  if (0x17 < param_1) {
    param_1--;
  }
  if (0xc < param_1) {
    param_1--;
  }
  return param_1;
}

/* 005195f1 auto */
int __cdecl terrain_editor_sel_to_terrain(int param_1)

{
  if (0xc < param_1) {
    param_1++;
  }
  if (0x17 < param_1) {
    param_1++;
  }
  return param_1;
}

/* 0051961e auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl terrain_editor_load_controls(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_14 = 1; local_14 < 0xf; local_14++) {
    if (*(int *)(&terrain_editor_ctrl_kinds + local_14 * 8) == 9) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&terrain_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd));
      _sprintf(local_10,&terrain_editor_int_fmt,
               *(i32 *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58));
      ctrl_set_text
                ((ControlTextView *)
                 (*(int *)(&terrain_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
    }
    else if (*(int *)(&terrain_editor_ctrl_kinds + local_14 * 8) == 0xc) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&terrain_editor_ctrl_slots + local_14 * 8) * 0x38));
      local_8 = *(int *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58);
      if (local_14 == 0) {
        local_8 = terrain_editor_terrain_to_sel(local_8);
      }
      if ((local_14 == 6) || (local_14 == 10)) {
        local_8 += 2;
      }
      if (local_14 == 0xe) {
        local_8++;
      }
      combo_set_cur_sel
                ((ComboBoxSetSelView *)
                 (active_editor_wnd + 0x2fc + *(int *)(&terrain_editor_ctrl_slots + local_14 * 8) * 0x38),local_8);
    }
  }
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 005197af auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl terrain_editor_store_controls(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  for (local_18 = 1; local_18 < 0xf; local_18++) {
    if (*(int *)(&terrain_editor_ctrl_kinds + local_18 * 8) == 9) {
      ctrl_get_text
                ((ControlTextView *)
                 (*(int *)(&terrain_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&terrain_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd));
      iVar1 -= 0xca;
      local_8 = _atoi(local_10);
      uVar2 = int_clamp(local_8,*(i32 *)(&terrain_editor_field_min_table + iVar1 * 4),
                                 *(i32 *)(&terrain_editor_field_max_table + iVar1 * 4));
      *(i32 *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = uVar2;
      if (*(int *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) != local_8) {
        local_14++;
      }
    }
    else if (*(int *)(&terrain_editor_ctrl_kinds + local_18 * 8) == 0xc) {
      local_8 = combo_get_cur_sel
                          ((ComboBoxGetSelView *)
                           (active_editor_wnd + 0x2fc + *(int *)(&terrain_editor_ctrl_slots + local_18 * 8) * 0x38));
      if (local_18 == 0) {
        local_8 = terrain_editor_sel_to_terrain(local_8);
      }
      if ((local_18 == 6) || (local_18 == 10)) {
        local_8 -= 2;
      }
      if (local_18 == 0xe) {
        local_8--;
      }
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&terrain_editor_ctrl_slots + local_18 * 8) * 0x38));
      *(int *)(&editor_ctrl_values + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = local_8;
    }
  }
  return local_14;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 005199a9 auto */
void __cdecl terrain_editor_redraw(void)

{
  terrain_editor_draw((C_004083b0_430 *)active_editor_wnd);
  return;
}

/* 005199c4 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __cdecl terrain_editor_append_rule_ref(iptr param_1,int param_2)

{
  if (param_1 == -1) {
    FUN_005f22e0(&text_buffer,&terrain_txt_ref_no_strs + ((param_2 != 0) - 1 & 8));
  }
  else if (param_1 == -2) {
    FUN_005f22e0(&text_buffer,&terrain_txt_ref_yes_strs + ((param_2 != 0) - 1 & 8));
  }
  else if (param_1 < 0xb) {
    FUN_005f22e0(&text_buffer,terrain_types + param_1);
    if (param_2 != 0) {
      FUN_005f22e0(&text_buffer,&terrain_txt_ref_comma_str);
    }
  }
  else {
    FUN_005f22e0(&text_buffer,&terrain_txt_ref_err_strs + ((param_2 != 0) - 1 & 8));
  }
  return;
}
#undef text_buffer

/* 00519ab0 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_10 (*(size_t *)(frame_ + FRAME_OFF(0)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl terrain_editor_write_section(FILE *param_1)

{
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (terrain2 = 0; terrain2 < 0x21; terrain2++) {
    text_clear();
    text_append_string_id(terrain_types[terrain2].name);
    FUN_005f22e0(&text_buffer,&terrain_txt_name_sep);
    pcVar1 = (char *)label_string(terrain_types[terrain2].name);
    sVar2 = _strlen(pcVar1);
    if (sVar2 < 0xb) {
      pcVar1 = (char *)label_string(terrain_types[terrain2].name);
      local_10 = _strlen(pcVar1);
    }
    else {
      local_10 = 0xb;
    }
    text_append_spaces(0xb - local_10);
    text_append_int((int)(char)terrain_types[terrain2].move_cost);
    FUN_005f22e0(&text_buffer,&terrain_txt_move_sep);
    text_append_int((int)(char)terrain_types[terrain2].defense);
    FUN_005f22e0(&text_buffer,&terrain_txt_defense_sep);
    text_append_spaces(2);
    for (local_8 = 0; local_8 < 3; local_8++) {
      text_append_int((int)*(char *)(local_8 + ADDR(0x627cca, ((u8 *)&terrain_types + 10)) + terrain2 * 0x18));
      FUN_005f22e0(&text_buffer,&terrain_txt_yield_sep);
    }
    if (terrain2 < 0xb) {
      for (local_8 = 0; local_8 < 2; local_8++) {
        text_append_spaces(3);
        terrain_editor_append_rule_ref((int)*(char *)(local_8 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18),1);
        text_append_int_2d((int)*(char *)(local_8 + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18));
        FUN_005f22e0(&text_buffer,&terrain_txt_bonus_sep);
        text_append_int_2d((int)*(char *)(local_8 + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18));
        FUN_005f22e0(&text_buffer,&terrain_txt_turns_sep);
        if (local_8 == 1) {
          text_append_space();
        }
        text_append_int_2d((int)*(char *)(local_8 + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + terrain2 * 0x18));
        FUN_005f22e0(&text_buffer,&terrain_txt_ai_gov_sep);
      }
      text_append_spaces(2);
      terrain_editor_append_rule_ref((int)terrain_types[terrain2].transform_to,1);
      FUN_005f22e0(&text_buffer,s___00631d18);
      terrain_editor_append_rule_ref(terrain2,0);
    }
    FUN_005f22e0(&text_buffer,&terrain_txt_line_end_str);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_10
#undef terrain2
#undef local_8

/* 00519d67 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl terrain_editor_on_ok(void)

{
  iptr iVar1;
  HWND hWnd;
  iptr iVar2;
  int iVar3;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = terrain_editor_store_controls();
  if (iVar1 == 0) {
    terrain_editor_store_rules();
    rules_edit_set_section(ADDR(0x631d2c, ((u8 *)&g.d_00631d2c)),ADDR(0x402f2c, terrain_editor_write_section));
    iVar2 = rules_write_sections();
    if (iVar2 == 0) {
      _sprintf(local_24,s_Error_updating_RULES__s_00631d34,&lang_file_ext);
      uType = 0x10;
      lpCaption = s_File_I_O_Error_00631d4c;
      lpText = local_24;
      iVar3 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar3 + 4),lpText,lpCaption,uType);
    }
    editor_running = 0;
    wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
    menu_update_states();
  }
  else {
    terrain_editor_load_controls();
    terrain_editor_redraw();
    if (active_editor_wnd == 0) {
      local_28 = 0;
    }
    else {
      local_28 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_28);
    popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631d24, ((u8 *)&g.d_00631d24)));
    dlg_set_parent_window(0);
    hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
    SetFocus(hWnd);
  }
  return;
}
#undef editor_running
#undef local_28
#undef local_24

/* 00519e74 auto */
#define local_138 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_134 (*(char (*)[14])(frame_ + FRAME_OFF(4)))
#define local_126 (*(i8 *)(frame_ + FRAME_OFF(18)))
#define local_120 (*(char (*)[260])(frame_ + FRAME_OFF(24)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(284)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(292)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(296)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(300)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(304)))
void __cdecl terrain_editor_on_rename(void)

{
  size_t sVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(312)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = *(int *)(active_editor_wnd + 0x2ec);
  _strncpy(local_134,&editor_item_names + local_18 * 0x28,0xf);
  local_126 = 0;
  do {
    if (active_editor_wnd == 0) {
      local_138 = 0;
    }
    else {
      local_138 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_138);
    local_8 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631d5c, ((u8 *)&g.d_00631d5c)),0xe,(iptr)local_134,(iptr)local_120);
    dlg_set_parent_window(0);
    if (local_8 == -1) break;
    sVar1 = _strlen(local_120);
  } while (sVar1 == 0);
  if (-1 < local_8) {
    FUN_005f22d0(&editor_item_names + local_18 * 0x28,local_120);
    local_c = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
    local_10 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x334));
    local_14 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x3a4));
    local_1c = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x414));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x2fc));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x334));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x3a4));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x414));
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7bc));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x334),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7bc));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x3a4),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x334),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x3a4),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x414),iVar2);
    for (local_18 = 0; local_18 < 0x21; local_18++) {
      if ((local_18 != 0xd) && (local_18 != 0x18)) {
        combo_add_string
                  ((ComboBoxAddView *)(active_editor_wnd + 0x2fc),(iptr)(&editor_item_names + local_18 * 0x28));
      }
    }
    for (local_18 = 0; local_18 < 0xb; local_18++) {
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x334),(iptr)(&editor_item_names + local_18 * 0x28));
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x3a4),(iptr)(&editor_item_names + local_18 * 0x28));
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x414),(iptr)(&editor_item_names + local_18 * 0x28));
    }
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),local_c);
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x334),local_10);
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x3a4),local_14);
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x414),local_1c);
    terrain_editor_redraw();
  }
  return;
}
#undef local_138
#undef local_134
#undef local_126
#undef local_120
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0051a1e5 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl terrain_editor_on_help(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x631d70, ((u8 *)&g.d_00631d70)),ADDR(0x631d68, ((u8 *)&g.d_00631d68)));
  dlg_set_parent_window(0);
  return;
}
#undef local_8

/* 0051a244 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl terrain_editor_on_cancel(void)

{
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 0051a26c auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(i8 * *)(frame_ + FRAME_OFF(16)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(i8 * *)(frame_ + FRAME_OFF(32)))
void __cdecl terrain_editor_on_edit_icon(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = (i8 *)0x0;
  local_8 = ((void *)ADDR(0x00402590, sprite_sheet_save_terrain1));
  local_10 = 7;
  if (*(int *)(active_editor_wnd + 0x2ec) == 3) {
    if (active_editor_wnd == 0) {
      local_1c = 0;
    }
    else {
      local_1c = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_1c);
    while( true ) {
      dlg_help_pressed = 0;
      iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631d78, ((u8 *)&g.d_00631d78)),1);
      if (dlg_help_pressed == 0) break;
      popup_text(ADDR(0x631d8c, ((u8 *)&g.d_00631d8c)),ADDR(0x631d80, ((u8 *)&g.d_00631d80)));
    }
    if (iVar1 != -1) {
      if (iVar1 == 0) {
        local_18 = &terrain_base_sprites + *(int *)(active_editor_wnd + 0x2ec) * 0x3c;
      }
      else {
        local_18 = &forest_sprites + (iVar1 * 4 - 4) * 0xf;
      }
    }
    if (0 < iVar1) {
      local_8 = ((void *)ADDR(0x00402e87, sprite_sheet_save_terrain2));
      local_10 = 8;
    }
    dlg_set_parent_window(0);
  }
  else if (*(int *)(active_editor_wnd + 0x2ec) == 4) {
    if (active_editor_wnd == 0) {
      local_20 = 0;
    }
    else {
      local_20 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_20);
    while( true ) {
      dlg_help_pressed = 0;
      iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631d94, ((u8 *)&g.d_00631d94)),1);
      if (dlg_help_pressed == 0) break;
      popup_text(ADDR(0x631da8, ((u8 *)&g.d_00631da8)),ADDR(0x631d9c, ((u8 *)&g.d_00631d9c)));
    }
    if (iVar1 != -1) {
      if (iVar1 == 0) {
        local_18 = &terrain_base_sprites + *(int *)(active_editor_wnd + 0x2ec) * 0x3c;
      }
      else {
        local_18 = &hill_sprites + (iVar1 * 4 - 4) * 0xf;
      }
    }
    if (0 < iVar1) {
      local_8 = ((void *)ADDR(0x00402e87, sprite_sheet_save_terrain2));
      local_10 = 8;
    }
    dlg_set_parent_window(0);
  }
  else if (*(int *)(active_editor_wnd + 0x2ec) == 5) {
    if (active_editor_wnd == 0) {
      local_24 = 0;
    }
    else {
      local_24 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_24);
    while( true ) {
      dlg_help_pressed = 0;
      iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631db0, ((u8 *)&g.d_00631db0)),1);
      if (dlg_help_pressed == 0) break;
      popup_text(ADDR(0x631dcc, ((u8 *)&g.d_00631dcc)),ADDR(0x631dbc, ((u8 *)&g.d_00631dbc)));
    }
    if (iVar1 != -1) {
      if (iVar1 == 0) {
        local_18 = &terrain_base_sprites + *(int *)(active_editor_wnd + 0x2ec) * 0x3c;
      }
      else {
        local_18 = &mountain_sprites + (iVar1 * 4 - 4) * 0xf;
      }
    }
    if (0 < iVar1) {
      local_8 = ((void *)ADDR(0x00402e87, sprite_sheet_save_terrain2));
      local_10 = 8;
    }
    dlg_set_parent_window(0);
  }
  else if (*(int *)(active_editor_wnd + 0x2ec) < 0xb) {
    local_18 = &terrain_base_sprites + *(int *)(active_editor_wnd + 0x2ec) * 0x3c;
  }
  else if (*(int *)(active_editor_wnd + 0x2ec) < 0x16) {
    local_18 = &terrain_resource_sprites + (*(int *)(active_editor_wnd + 0x2ec) % 0xb) * 0x78;
  }
  else {
    local_18 = &terrain_resource2_sprites + (*(int *)(active_editor_wnd + 0x2ec) % 0xb) * 0x78;
  }
  if (local_18 != (i8 *)0x0) {
    uVar2 = label_string(*(i32 *)(label_string_ids + 0x7d8));
    sprite_editor_run((iptr)local_18,uVar2,local_10,(iptr)local_8);
  }
  terrain_editor_redraw();
  return;
}
#undef dlg_help_pressed
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_10
#undef local_8

/* 0051a678 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i8 * *)(frame_ + FRAME_OFF(8)))
void __cdecl terrain_editor_on_edit_river(void)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  i8 *puVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = (i8 *)0x0;
  if (active_editor_wnd == 0) {
    local_14 = 0;
  }
  else {
    local_14 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_14);
  while( true ) {
    dlg_help_pressed = 0;
    iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631dd4, ((u8 *)&g.d_00631dd4)),1);
    if (dlg_help_pressed == 0) break;
    popup_text(ADDR(0x631de8, ((u8 *)&g.d_00631de8)),ADDR(0x631ddc, ((u8 *)&g.d_00631ddc)));
  }
  if (iVar1 != -1) {
    if (iVar1 < 0x10) {
      local_10 = &river_sprites + iVar1 * 0x3c;
    }
    else {
      local_10 = &river_mouth_sprites + (iVar1 * 4 - 0x40) * 0xf;
    }
  }
  dlg_set_parent_window(0);
  if (local_10 != (i8 *)0x0) {
    puVar4 = ((void *)ADDR(0x00402e87, sprite_sheet_save_terrain2));
    uVar3 = 8;
    uVar2 = label_string(*(i32 *)(label_string_ids + 0x7d8));
    sprite_editor_run((iptr)local_10,uVar2,uVar3,(iptr)puVar4);
  }
  terrain_editor_redraw();
  return;
}
#undef dlg_help_pressed
#undef local_14
#undef local_10

/* 0051a797 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i8 * *)(frame_ + FRAME_OFF(8)))
void __cdecl terrain_editor_on_edit_coast(void)

{
  uint uVar1;
  i32 uVar2;
  uint uVar3;
  i32 uVar4;
  i8 *puVar5;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = (i8 *)0x0;
  if (active_editor_wnd == 0) {
    local_14 = 0;
  }
  else {
    local_14 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_14);
  while( true ) {
    dlg_help_pressed = 0;
    uVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631df0, ((u8 *)&g.d_00631df0)),1);
    if (dlg_help_pressed == 0) break;
    popup_text(ADDR(0x631e04, ((u8 *)&g.d_00631e04)),ADDR(0x631df8, ((u8 *)&g.d_00631df8)));
  }
  if (uVar1 != 0xffffffff) {
    uVar3 = (int)uVar1 >> 0x1f;
    local_10 = &coast_quarter_sprites +
               (((uVar1 ^ uVar3) - uVar3 & 3 ^ uVar3) - uVar3) * 0x3c +
               ((int)(uVar1 + (uVar3 & 3)) >> 2) * 0xf0;
  }
  dlg_set_parent_window(0);
  if (local_10 != (i8 *)0x0) {
    puVar5 = ((void *)ADDR(0x00402e87, sprite_sheet_save_terrain2));
    uVar4 = 9;
    uVar2 = label_string(*(i32 *)(label_string_ids + 0x7d8));
    sprite_editor_run((iptr)local_10,uVar2,uVar4,(iptr)puVar5);
  }
  terrain_editor_redraw();
  return;
}
#undef dlg_help_pressed
#undef local_14
#undef local_10

/* 0051a8b7 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i8 * *)(frame_ + FRAME_OFF(8)))
void __cdecl terrain_editor_on_edit_misc(void)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  i8 *puVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = (i8 *)0x0;
  if (active_editor_wnd == 0) {
    local_14 = 0;
  }
  else {
    local_14 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_14);
  while( true ) {
    dlg_help_pressed = 0;
    iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631e0c, ((u8 *)&g.d_00631e0c)),1);
    if (dlg_help_pressed == 0) break;
    popup_text(ADDR(0x631e28, ((u8 *)&g.d_00631e28)),ADDR(0x631e18, ((u8 *)&g.d_00631e18)));
  }
  if (iVar1 != -1) {
    if (iVar1 < 3) {
      local_10 = &land_improvement_sprites + iVar1 * 0x3c;
    }
    else if (iVar1 == 0xc) {
      local_10 = &pollution_sprite;
    }
    else if (iVar1 == 0xd) {
      local_10 = &grassland_shield_sprite;
    }
    else if (iVar1 == 0xe) {
      local_10 = &hut_sprite;
    }
    else if (2 < iVar1 % 0xc) {
      local_10 = &road_sprites + ((iVar1 % 0xc) * 4 - 0xc) * 0xf + (iVar1 / 0xc) * 0x21c;
    }
  }
  dlg_set_parent_window(0);
  if (local_10 != (i8 *)0x0) {
    puVar4 = ((void *)ADDR(0x00402590, sprite_sheet_save_terrain1));
    uVar3 = 10;
    uVar2 = label_string(*(i32 *)(label_string_ids + 0x7d8));
    sprite_editor_run((iptr)local_10,uVar2,uVar3,(iptr)puVar4);
  }
  terrain_editor_redraw();
  return;
}
#undef dlg_help_pressed
#undef local_14
#undef local_10

/* 0051aa4e auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl terrain_editor_update_visibility(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(active_editor_wnd + 0x2ec) < 0xb) {
    ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x334));
    iVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x334));
    if (iVar1 == 0) {
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x5b4));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x5fc));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x36c));
    }
    else if (iVar1 == 1) {
      control_hide((Control *)(active_editor_wnd + 0x5b4));
      control_hide((Control *)(active_editor_wnd + 0x5fc));
      control_hide((Control *)(active_editor_wnd + 0x36c));
    }
    else {
      control_hide((Control *)(active_editor_wnd + 0x5b4));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x5fc));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x36c));
    }
    ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x3a4));
    iVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x3a4));
    if (iVar1 == 0) {
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x644));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x68c));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x3dc));
    }
    else if (iVar1 == 1) {
      control_hide((Control *)(active_editor_wnd + 0x644));
      control_hide((Control *)(active_editor_wnd + 0x68c));
      control_hide((Control *)(active_editor_wnd + 0x3dc));
    }
    else {
      control_hide((Control *)(active_editor_wnd + 0x644));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x68c));
      ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x3dc));
    }
    ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x414));
  }
  else {
    for (local_8 = 5; local_8 < 9; local_8++) {
      control_hide((Control *)(local_8 * 0x48 + 0x44c + active_editor_wnd));
    }
    for (local_8 = 1; local_8 < 6; local_8++) {
      control_hide((Control *)(active_editor_wnd + 0x2fc + local_8 * 0x38));
    }
  }
  return;
}
#undef local_8

/* 0051acdc auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
void __cdecl terrain_editor_on_combo(int param_1)

{
  int iVar1;
  HWND hWnd;
  i32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0xc9) {
    iVar1 = terrain_editor_store_controls();
    if (iVar1 == 0) {
      uVar2 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
      uVar2 = terrain_editor_sel_to_terrain(uVar2);
      *(i32 *)(active_editor_wnd + 0x2ec) = uVar2;
      terrain_editor_load_controls();
      terrain_editor_update_visibility();
      terrain_editor_redraw();
    }
    else {
      combo_set_cur_sel
                ((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),*(iptr *)(active_editor_wnd + 0x2ec));
      terrain_editor_load_controls();
      terrain_editor_redraw();
      if (active_editor_wnd == 0) {
        local_c = 0;
      }
      else {
        local_c = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_c);
      popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x631e30, ((u8 *)&g.d_00631e30)));
      dlg_set_parent_window(0);
      hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
      SetFocus(hWnd);
    }
  }
  else if ((param_1 == 0xcf) || (param_1 == 0xd3)) {
    terrain_editor_update_visibility();
    terrain_editor_redraw();
  }
  return;
}
#undef local_c

/* 0051adfd auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define local_28 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall terrain_editor_create_combo(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(&terrain_editor_combo_pos_x + param_1 * 8) + this->client_x;
  iVar2 = *(int *)(&terrain_editor_combo_pos_y + param_1 * 8) + this->client_y;
  if (param_1 == 0) {
    rect_set_xywh((iptr)local_14,iVar1 - 0x1e,iVar2,0xa0,this->field_2e8 << 3);
  }
  else if ((param_1 == 2) || (param_1 == 4)) {
    rect_set_xywh((iptr)local_14,iVar1 - 0x1e,iVar2,0x82,this->field_2e8 << 3);
  }
  else {
    rect_set_xywh((iptr)local_14,iVar1,iVar2,100,this->field_2e8 << 3);
  }
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_28 = (u8 *)0x0;
  }
  else {
    local_28 = this->pad_48;
  }
  combo_create
            ((Control *)(this->pad_2d4 + param_1 * 0x38 + 0x28),(iptr)local_28,iVar1,
             (iptr)local_14);
  combo_set_font((ComboBoxFontView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  combo_set_callback((ComboBoxCallbackSetView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x4011fe, terrain_editor_on_combo));
  switch(param_1) {
  case 0:
    for (terrain2 = 0; terrain2 < 0x21; terrain2++) {
      if ((terrain2 != 0xd) && (terrain2 != 0x18)) {
        iVar3 = label_string(terrain_types[terrain2].name);
        combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
      }
    }
    break;
  case 1:
  case 3:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7bc));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    for (terrain2 = 0; terrain2 < 0xb; terrain2++) {
      iVar3 = label_string(terrain_types[terrain2].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    }
    break;
  case 2:
  case 4:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c8));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    for (terrain2 = 1; terrain2 < 7; terrain2++) {
      iVar3 = label_string(government_names[terrain2]);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    }
    break;
  case 5:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    for (terrain2 = 0; terrain2 < 0xb; terrain2++) {
      iVar3 = label_string(terrain_types[terrain2].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    }
  }
  return;
}
#undef editor_next_ctrl_id
#undef local_28
#undef terrain2
#undef local_14

/* 0051b1c2 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define terrain_editor_field_pos_x (*(i32 *)((u8 *)&g.d_00631bb0))
#define terrain_editor_field_pos_y (*(i32 *)((u8 *)&g.d_00631bb4))
#define local_24 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall terrain_editor_create_edit(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,(&terrain_editor_field_pos_x)[param_1 * 2] + this->client_x,
                     (&terrain_editor_field_pos_y)[param_1 * 2] + this->client_y,0x30,this->field_2e8 + 6);
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
             (iptr)local_14,ADDR(0x631e38, ((u8 *)&g.d_00631e38)));
  edit_set_max_len((EditMaxLenView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),3);
  edit_set_callback((EditCallbackSetView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),ADDR(0x401019, editor_numeric_edit_filter));
  return;
}
#undef editor_next_ctrl_id
#undef terrain_editor_field_pos_x
#undef terrain_editor_field_pos_y
#undef local_24
#undef local_14

/* 0051b2b6 auto */
#define editor_bg_surface (*(int *)((u8 *)&g.d_0062e018))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define terrain_editor_field_pos_x (*(int *)((u8 *)&g.d_00631bb0))
#define terrain_editor_field_pos_y (*(int *)((u8 *)&g.d_00631bb4))
#define local_38 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_18 (*(Sprite * *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
void __thiscall terrain_editor_draw(C_004083b0_430 *this)

{
  byte bVar1;
  int iVar2;
  i32 uVar3;
  uint uVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
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
  if ((int)this->field_2ec < 0xb) {
    local_18 = (Sprite *)(&terrain_base_sprites + this->field_2ec * 0x3c);
  }
  else if ((int)this->field_2ec < 0x16) {
    local_18 = (Sprite *)(&terrain_resource_sprites + ((int)this->field_2ec % 0xb) * 0x78);
  }
  else {
    local_18 = (Sprite *)(&terrain_resource2_sprites + ((int)this->field_2ec % 0xb) * 0x78);
  }
  bVar1 = sprite_get_key_color(local_18);
  uVar4 = (uint)bVar1;
  iVar2 = sprite_height(local_18);
  iVar2 = iVar2 * 2;
  uVar3 = sprite_width(local_18);
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,uVar3,iVar2,uVar4);
  iVar2 = sprite_height(local_18);
  sprite_draw_keyed(local_18,(iptr)local_28,(iptr)this,0,local_8,local_c + iVar2 / 2);
  uVar5 = 6;
  iVar2 = sprite_height(local_18);
  iVar2 = iVar2 * 2;
  uVar3 = sprite_width(local_18);
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,uVar3,iVar2,uVar5);
  local_18 = (Sprite *)0x0;
  if (this->field_2ec == 3) {
    local_18 = (Sprite *)&forest_sprites;
  }
  else if (this->field_2ec == 4) {
    local_18 = (Sprite *)&hill_sprites;
  }
  else if (this->field_2ec == 5) {
    local_18 = (Sprite *)&mountain_sprites;
  }
  if (local_18 != (Sprite *)0x0) {
    iVar2 = sprite_height(local_18);
    sprite_draw(local_18,(iptr)local_38,(iptr)this,local_8,local_c + iVar2 / 2);
  }
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  gfx_draw_tiled_frame((iptr)this,this->client_x + 0x1c,this->client_y + 0xc2,0x1e6,0x21,6);
  gfx_draw_tiled_frame((iptr)this,this->client_x + 0x1c,this->client_y + 0xf9,0x1e6,0x21,6);
  local_10 = terrain_editor_field_pos_x + this->client_x + 0x18;
  local_14 = ((terrain_editor_field_pos_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1d0);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_defense_field_x + this->client_x + 0x18;
  local_14 = ((terrain_editor_defense_field_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1d1);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0x32);
  local_10 = terrain_editor_food_field_x + this->client_x + 0x18;
  local_14 = terrain_editor_food_field_y + this->client_y + this->field_2e8 * -2 - 2;
  text_clear();
  text_append_label(0x1d2);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_shield_field_x + this->client_x + 0x18;
  local_14 = terrain_editor_shield_field_y + this->client_y + this->field_2e8 * -2;
  text_clear();
  text_append_label(0x1d3);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_trade_field_x + this->client_x + 0x18;
  local_14 = terrain_editor_trade_field_y + this->client_y + this->field_2e8 * -2;
  text_clear();
  text_append_label(0x1d4);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_food_field_x + this->client_x + 0x18;
  local_14 = ((terrain_editor_food_field_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1d5);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_shield_field_x + this->client_x + 0x18;
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_trade_field_x + this->client_x + 0x18;
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_irrigate_bonus_x + this->client_x + 0x18;
  local_14 = ((terrain_editor_irrigate_bonus_y + this->client_y) - this->field_2e8) - 10;
  text_clear();
  text_append_label(0x1d9);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_irrigate_turns_x + this->client_x + 0x18;
  local_14 = ((terrain_editor_irrigate_turns_y + this->client_y) - this->field_2e8) - 10;
  text_clear();
  text_append_label(0x1da);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_irrig_combo_x + this->client_x + 0x32;
  local_14 = ((terrain_editor_irrig_combo_y + this->client_y) - this->field_2e8) - 10;
  text_clear();
  text_append_label(0x1d8);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_irrig_ai_combo_x + this->client_x + 0x32;
  local_14 = ((terrain_editor_irrig_ai_combo_y + this->client_y) - this->field_2e8) - 10;
  text_clear();
  text_append_label(0x1db);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_transform_combo_x + this->client_x + 0x32;
  local_14 = ((terrain_editor_transform_combo_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1dc);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = terrain_editor_irrig_combo_x + this->client_x;
  local_14 = terrain_editor_irrig_combo_y + this->client_y + 4;
  text_clear();
  text_append_label(0x1d6);
  iVar2 = font_text_width((GameFont *)&editor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,-10 - iVar2);
  local_10 = terrain_editor_mine_combo_x + this->client_x;
  local_14 = terrain_editor_mine_combo_y + this->client_y + 4;
  text_clear();
  text_append_label(0x1d7);
  iVar2 = font_text_width((GameFont *)&editor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,-10 - iVar2);
  local_10 = terrain_editor_irrigate_bonus_x + this->client_x + 0x30;
  local_14 = terrain_editor_irrigate_bonus_y + this->client_y + 4;
  text_clear();
  text_append_label(0x1d2);
  iVar2 = font_text_width((GameFont *)&editor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,iVar2 + 10);
  local_10 = terrain_editor_mine_bonus_x + this->client_x + 0x30;
  local_14 = terrain_editor_mine_bonus_y + this->client_y + 4;
  text_clear();
  text_append_label(0x1dd);
  iVar2 = font_text_width((GameFont *)&editor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,iVar2 + 10);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef editor_bg_surface
#undef editor_running
#undef terrain_editor_field_pos_x
#undef terrain_editor_field_pos_y
#undef local_38
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0051bba1 auto */
#define editor_bg_surface (*(DibSurface * *)((u8 *)&g.d_0062e018))
#define editor_next_ctrl_id (*(i32 *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define local_490 (*(u8 * *)(frame_ + FRAME_OFF(0)))
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
void __thiscall terrain_editor_run(C_004083b0_430 *this)

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
  this->field_2d8 = 0x230;
  this->field_2dc = 0x17c;
  this->field_2ec = 0;
  editor_next_ctrl_id = 0xc9;
  surface_load_gif_file(editor_bg_surface,ADDR(0x631e3c, ((u8 *)&g.d_00631e3c)),10,0xc0,(iptr)&local_444);
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
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x728));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  for (local_460 = 0; local_460 < 0xf; local_460++) {
    if (*(int *)(&terrain_editor_ctrl_kinds + local_460 * 8) == 9) {
      terrain_editor_create_edit(this,*(i32 *)(&terrain_editor_ctrl_slots + local_460 * 8));
    }
    else if (*(int *)(&terrain_editor_ctrl_kinds + local_460 * 8) == 0xc) {
      terrain_editor_create_combo(this,*(i32 *)(&terrain_editor_ctrl_slots + local_460 * 8));
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
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x402711, terrain_editor_on_ok));
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
  button_set_callback((Control *)&this[1].field_358,ADDR(0x401a69, terrain_editor_on_rename));
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
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x40243c, terrain_editor_on_help));
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
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x402347, terrain_editor_on_cancel));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  iVar3 = sprite_width
                    ((Sprite *)(&terrain_base_sprites + this->field_2ec * 0x3c));
  this->field_2e0 = iVar3 + 0xd;
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  uVar10 = this->client_x;
  iVar3 = sprite_height
                    ((Sprite *)(&terrain_base_sprites + this->field_2ec * 0x3c));
  rect_set_xywh((iptr)local_454,uVar10 + 0x19,iVar3 * 2 + this->client_y + 0x28,
                     this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x7cc));
  button_create
            ((Control *)(this[1].pad_364 + 0x30),(iptr)local_484,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_364 + 0x30),ADDR(0x40196a, terrain_editor_on_edit_icon));
  iVar4 = (this->client_width + this->client_x - 0x19) - this->field_2e0;
  iVar3 = this->client_y + 0x28;
  rect_set_xywh((iptr)local_454,iVar4,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_488 = (u8 *)0x0;
  }
  else {
    local_488 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8f4));
  button_create
            ((Control *)(this[1].pad_3c0 + 0x10),(iptr)local_488,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_3c0 + 0x10),ADDR(0x401cfd, terrain_editor_on_edit_river));
  iVar3 = iVar3 + this->field_2e4 + 2;
  rect_set_xywh((iptr)local_454,iVar4,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_48c = (u8 *)0x0;
  }
  else {
    local_48c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8f8));
  button_create
            ((Control *)(this[1].pad_3c0 + 0x4c),(iptr)local_48c,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_3c0 + 0x4c),ADDR(0x403535, terrain_editor_on_edit_coast));
  rect_set_xywh((iptr)local_454,iVar4,iVar3 + this->field_2e4 + 2,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_490 = (u8 *)0x0;
  }
  else {
    local_490 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8f0));
  button_create
            ((Control *)&this[2].field_18,(iptr)local_490,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[2].field_18,ADDR(0x40344f, terrain_editor_on_edit_misc));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  terrain_editor_load_rules();
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_2fc,this->field_2ec);
  terrain_editor_load_controls();
  terrain_editor_update_visibility();
  this->field_2f8 = 6;
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4019d8, editor_wnd_on_move_close_dropdowns));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402c7a, terrain_editor_redraw));
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
  /* inlined unwind funclet FUN_0051c611 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_bg_surface
#undef editor_next_ctrl_id
#undef editor_running
#undef local_490
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

/* 0051c635 auto */
#define local_b58 (*(C_004083b0_a28 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl terrain_editor_open(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  terrain_editor_run((C_004083b0_430 *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0051c68e */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0055a980 auto */
#define path_road_planning (*(i32 *)((u8 *)&g.d_0062d040))
#define local_48 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_44 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_40 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define y2 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(28)))
#define x2 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_8 (*(u8 * *)(frame_ + FRAME_OFF(64)))
void __cdecl map_build_coarse_connectivity(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  path_road_planning = 1;
  for (local_3c = 0; local_3c < 2; local_3c++) {
    if (local_3c == 0) {
      local_8 = map_coarse[0];
    }
    else {
      local_8 = map_coarse[1];
    }
    local_2c = (uint)(local_3c != 0);
    _memset(local_8,0,(int)map.quarter_w * (int)map.quarter_h);
    for (local_34 = 0; local_34 < map.quarter_w; local_34++) {
      for (local_20 = 0; local_20 < map.quarter_h; local_20++) {
        local_1c = local_34 * 4 + 1;
        local_24 = local_20 * 4 + 1;
        local_18 = map_coarse_cell_landmass(local_1c,local_24,(iptr)&x2,(iptr)&y2,local_2c);
        if (-1 < local_18) {
          for (local_44 = 0; local_44 < 4; local_44++) {
            local_10 = map_wrap_x((char)(&coarse_dir_dx_table)[local_44] * 4 + local_1c);
            local_14 = (char)(&coarse_dir_dy_table)[local_44] * 4 + local_24;
            iVar1 = map_in_bounds(local_10,local_14);
            if ((((iVar1 != 0) &&
                 (local_c = map_coarse_cell_landmass(local_10,local_14,(iptr)&local_40,(iptr)&local_48,local_2c)
                 , local_c == local_18)) &&
                (local_38 = map_path_length(x2,y2,local_40,local_48,local_2c,5),
                0 < local_38)) && (local_38 < 5)) {
              local_8[map.quarter_w * local_20 + local_34] =
                   local_8[map.quarter_w * local_20 + local_34] |
                   (byte)(1 << ((byte)local_44 & 0x1f));
              local_10 = coarse_wrap_x((char)(&coarse_dir_dx_table)[local_44] + local_34);
              local_14 = (char)(&coarse_dir_dy_table)[local_44] + local_20;
              if (((-1 < local_10) && (-1 < local_14)) &&
                 ((local_10 < map.quarter_w && (local_14 < map.quarter_h)))) {
                local_8[map.quarter_w * local_14 + local_10] =
                     local_8[map.quarter_w * local_14 + local_10] |
                     (byte)(1 << ((char)local_44 - 4U & 7));
              }
            }
          }
        }
      }
      ui_pump_messages_net();
    }
  }
  path_road_planning = 0;
  return;
}
#undef path_road_planning
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef y2
#undef local_2c
#undef x2
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0055ac37 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl map_coarse_cell_landmass(iptr param_1,int param_2,iptr param_3,iptr param_4,int param_5)

{
  iptr x;
  int y;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while( true ) {
    if (1 < local_8) {
      return 0xffffffff;
    }
    x = map_wrap_x(param_1 + local_8);
    y = param_2 + local_8;
    iVar3 = map_in_bounds(x,y);
    if ((iVar3 != 0) && (iVar3 = tile_is_ocean(x,y), iVar3 == param_5)) break;
    local_8++;
  }
  uVar4 = tile_landmass(x,y);
  *(iptr *)param_3 = x;
  *(int *)param_4 = y;
  return uVar4;
}
#undef local_8

/* 0056b8a0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl map_label_font_global_init(void)

{
  map_label_font_static_init();
  map_label_font_reg_atexit();
  return;
}

/* 0056b8ba auto */
void __cdecl map_label_font_static_init(void)

{
  font_init_empty((GameFont *)&map_label_font);
  return;
}

/* 0056b8d4 auto */
void __cdecl map_label_font_reg_atexit(void)

{
  _atexit(map_label_font_static_dtor);
  return;
}

/* 0056b8f1 auto */
void __cdecl map_label_font_static_dtor(void)

{
  font_destroy((GameFont *)&map_label_font);
  return;
}

/* 0056c705 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_redraw_busy (*(i32 *)((u8 *)&g.d_006ad908))
#define mapview_half_tile_height (*(i32 *)((u8 *)&g.d_0066cabc))
#define mapview_origin_x (*(i32 *)((u8 *)&g.d_0066ca90))
#define mapview_origin_y (*(i32 *)((u8 *)&g.d_0066ca94))
#define mapview_zoom (*(i16 *)((u8 *)&g.d_0066ca8c))
#define net_move_anim_sound (*(i32 *)((u8 *)&g.d_006ad6a4))
#define net_move_anim_sound_arg (*(i32 *)((u8 *)&g.d_006ad6a8))
#define aiStack_454 (*(int (*)[8])(frame_ + FRAME_OFF(4)))
#define local_434 (*(int *)(frame_ + FRAME_OFF(36)))
#define auStack_430 (*(i32 (*)[8])(frame_ + FRAME_OFF(40)))
#define local_410 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_40c (*(i32 *)(frame_ + FRAME_OFF(76)))
#define aiStack_408 (*(int (*)[8])(frame_ + FRAME_OFF(80)))
#define aiStack_3e8 (*(int (*)[8])(frame_ + FRAME_OFF(112)))
#define local_3c8 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_3c4 (*(int *)(frame_ + FRAME_OFF(148)))
#define local_3c0 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_3bc (*(int *)(frame_ + FRAME_OFF(156)))
#define local_3b8 (*(int *)(frame_ + FRAME_OFF(160)))
#define auStack_3b4 (*(i32 (*)[8])(frame_ + FRAME_OFF(164)))
#define aiStack_394 (*(int (*)[8])(frame_ + FRAME_OFF(196)))
#define local_374 (*(int *)(frame_ + FRAME_OFF(228)))
#define aiStack_370 (*(int (*)[8])(frame_ + FRAME_OFF(232)))
#define aiStack_350 (*(int (*)[8])(frame_ + FRAME_OFF(264)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(296)))
#define aiStack_32c (*(int (*)[8])(frame_ + FRAME_OFF(300)))
#define acStack_30c (*(char (*)[8])(frame_ + FRAME_OFF(332)))
#define local_304 (*(DWORD *)(frame_ + FRAME_OFF(340)))
#define local_300 (*(DibSurface (*)[8])(frame_ + FRAME_OFF(344)))
#define local_c0 (*(int *)(frame_ + FRAME_OFF(920)))
#define local_bc (*(DWORD *)(frame_ + FRAME_OFF(924)))
#define local_b8 (*(int *)(frame_ + FRAME_OFF(928)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(932)))
#define aiStack_b0 (*(int (*)[8])(frame_ + FRAME_OFF(936)))
#define local_90 (*(iptr *)(frame_ + FRAME_OFF(968)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(972)))
#define aiStack_88 (*(int (*)[8])(frame_ + FRAME_OFF(976)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(1008)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(1012)))
#define local_60 (*(i8 (*)[16])(frame_ + FRAME_OFF(1016)))
#define aiStack_50 (*(int (*)[8])(frame_ + FRAME_OFF(1032)))
#define aiStack_30 (*(int (*)[8])(frame_ + FRAME_OFF(1064)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1096)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1100)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1104)))
void __cdecl
map_animate_unit_move(iptr unit,int param_2,int param_3,iptr param_4,int param_5,iptr param_6)

{
  char cVar1;
  int iVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(1112)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_8c = 0;
  FUN_005f2620(local_300,0x48,8,surface_ctor,surface_dtor);
  local_8 = 0;
  local_64 = 0;
  map_redraw_busy = 1;
  net_move_anim_sound = 0xffffffff;
  net_move_anim_sound_arg = 0xffffffff;
  local_410 = (int)(char)(&dir_dx_table)[param_4];
  cVar1 = (&dir_dy_table)[param_4];
  local_40c = map_wrap_x(local_410 + param_2);
  local_434 = cVar1 + param_3;
  map_redraw_area_all_views(param_2,param_3,0,human_civ,0);
  map_redraw_area_all_views(local_40c,local_434,0,human_civ,0);
  anim_origin_stack_unit = -1;
  for (local_90 = 0; local_90 < 8; local_90++) {
    acStack_30c[local_90] = '\0';
    if (((local_90 == 0) || (*(short *)(&map_view_open_flags + local_90 * 0x3f0) != 0)) &&
       ((iVar2 = mapview_tile_in_view
                           ((C_004083b0_430 *)(&map_views + local_90 * 0x3f0),param_2,param_3),
        iVar2 != 0 ||
        (iVar2 = mapview_tile_in_view
                           ((C_004083b0_430 *)(&map_views + local_90 * 0x3f0),local_40c,local_434
                           ), iVar2 != 0)))) {
      acStack_30c[local_90] = 1;
      aiStack_30[local_90] = (&mapview_origin_x)[local_90 * 0xfc];
      aiStack_88[local_90] = (&mapview_origin_y)[local_90 * 0xfc];
      mapview_tile_to_screen
                ((C_004083b0_430 *)(&map_views + local_90 * 0x3f0),(iptr)&local_68,
                 (iptr)&local_330,param_2,param_3);
      mapview_tile_to_screen
                ((C_004083b0_430 *)(&map_views + local_90 * 0x3f0),(iptr)&local_b4,
                 (iptr)&local_374,local_40c,local_434);
      local_330 -= (&mapview_half_tile_height)[local_90 * 0xfc];
      local_374 -= (&mapview_half_tile_height)[local_90 * 0xfc];
      iVar2 = local_b4;
      if (local_68 <= local_b4) {
        iVar2 = local_68;
      }
      aiStack_370[local_90] = iVar2;
      iVar2 = local_374;
      if (local_330 <= local_374) {
        iVar2 = local_330;
      }
      aiStack_3e8[local_90] = iVar2;
      iVar2 = local_b4;
      if (local_b4 <= local_68) {
        iVar2 = local_68;
      }
      aiStack_394[local_90] = *(int *)(&mapview_tile_width + local_90 * 0x3f0) + iVar2 - 1;
      iVar2 = local_374;
      if (local_374 <= local_330) {
        iVar2 = local_330;
      }
      aiStack_408[local_90] = *(int *)(&mapview_unit_sprite_height + local_90 * 0x3f0) + iVar2 - 1;
      aiStack_32c[local_90] = local_68;
      aiStack_350[local_90] = local_330;
      rect_set((iptr)local_60,aiStack_370[local_90],aiStack_3e8[local_90],
                         aiStack_394[local_90] + 1,aiStack_408[local_90] + 1);
      uVar3 = rect_width((iptr)local_60);
      auStack_3b4[local_90] = uVar3;
      uVar3 = rect_height((iptr)local_60);
      auStack_430[local_90] = uVar3;
      if (local_8c == 0) {
        local_8c = 1;
        local_3c8 = 0x10;
        iVar2 = map_view_zoom_scale_round((MapViewZoomView *)(&map_views + local_90 * 0x3f0),2);
        aiStack_b0[local_90] = iVar2;
        iVar2 = aiStack_b0[local_90];
        if (iVar2 < 2) {
          iVar2 = 1;
        }
        aiStack_b0[local_90] = iVar2;
        if (aiStack_b0[local_90] == 3) {
          aiStack_b0[local_90] = 4;
        }
        local_b8 = *(int *)(&mapview_tile_height + local_90 * 0x3f0) / aiStack_b0[local_90] + 1;
        local_3c8 = (local_3c8 << 4) / local_b8;
        if ((unit_types[units[unit].type].domain == 1) &&
           (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0)) {
          aiStack_b0[local_90] = aiStack_b0[local_90] << 1;
          local_b8 = *(int *)(&mapview_tile_height + local_90 * 0x3f0) / aiStack_b0[local_90] + 1;
        }
      }
      else {
        aiStack_b0[local_90] = *(int *)(&mapview_tile_height + local_90 * 0x3f0) / local_b8;
      }
      surface_create(local_300 + local_90,auStack_3b4[local_90],auStack_430[local_90]);
      gfx_copy_rect_clipped((iptr)(&map_views + local_90 * 0x3f0),(iptr)(local_300 + local_90),
                         aiStack_370[local_90],aiStack_3e8[local_90],
                         (&mapview_client_origin_x)[local_90 * 0xfc],(&mapview_client_origin_y)[local_90 * 0xfc],0,0,0,0,
                         auStack_3b4[local_90],auStack_430[local_90]);
      aiStack_454[local_90] = aiStack_b0[local_90] * local_410;
      aiStack_50[local_90] = (aiStack_b0[local_90] * (int)cVar1) / 2;
    }
  }
  if (local_8c == 0) {
    map_redraw_busy = 0;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0056d25b */ { FUN_005f2490((iptr)&local_300,0x48,8,surface_dtor); }
  }
  else {
    local_bc = timeGetTime();
    for (local_c0 = 0; local_c0 < local_b8; local_c0++) {
      for (local_90 = 0; local_90 < 8; local_90++) {
        if (acStack_30c[local_90] != '\0') {
          iVar2 = mapview_tile_in_view
                            ((C_004083b0_430 *)(&map_views + local_90 * 0x3f0),param_2,param_3);
          if (((iVar2 == 0) || ((&mapview_origin_x)[local_90 * 0xfc] != aiStack_30[local_90])) ||
             ((&mapview_origin_y)[local_90 * 0xfc] != aiStack_88[local_90])) {
            acStack_30c[local_90] = '\0';
          }
          else {
            if ((local_64 == 0) && (-1 < param_5)) {
              local_64 = 1;
              snd_play_effect(param_5,param_6,0,0);
            }
            gfx_draw_unit((iptr)(&map_views + local_90 * 0x3f0),unit,5,
                               aiStack_32c[local_90],aiStack_350[local_90],
                               (int)(short)(&mapview_zoom)[local_90 * 0x1f8],1);
            rect_set_xywh((iptr)&local_3c4,aiStack_32c[local_90] + aiStack_b0[local_90] * -2,
                               aiStack_350[local_90] + aiStack_b0[local_90] * -2,
                               aiStack_b0[local_90] * 4 + *(int *)(&mapview_tile_width + local_90 * 0x3f0)
                               ,aiStack_b0[local_90] * 4 +
                                *(int *)(&mapview_unit_sprite_height + local_90 * 0x3f0));
            iVar2 = aiStack_370[local_90];
            if (aiStack_370[local_90] <= local_3c4) {
              iVar2 = local_3c4;
            }
            local_3c4 = iVar2;
            iVar2 = aiStack_3e8[local_90];
            if (aiStack_3e8[local_90] <= local_3c0) {
              iVar2 = local_3c0;
            }
            local_3c0 = iVar2;
            iVar2 = aiStack_394[local_90] + 1;
            if (local_3bc <= aiStack_394[local_90] + 1) {
              iVar2 = local_3bc;
            }
            local_3bc = iVar2;
            iVar2 = aiStack_408[local_90] + 1;
            if (local_3b8 <= aiStack_408[local_90] + 1) {
              iVar2 = local_3b8;
            }
            local_3b8 = iVar2;
            wnd_blit_surface_rect
                      ((DibSurface *)(&map_views + local_90 * 0x3f0),(iptr)&local_3c4);
            gfx_copy_rect_clipped((iptr)(local_300 + local_90),(iptr)(&map_views + local_90 * 0x3f0)
                               ,aiStack_32c[local_90] - aiStack_370[local_90],
                               aiStack_350[local_90] - aiStack_3e8[local_90],0,0,
                               aiStack_32c[local_90],aiStack_350[local_90],
                               (&mapview_client_origin_x)[local_90 * 0xfc],(&mapview_client_origin_y)[local_90 * 0xfc],
                               *(i32 *)(&mapview_tile_width + local_90 * 0x3f0),
                               *(i32 *)(&mapview_unit_sprite_height + local_90 * 0x3f0));
            aiStack_32c[local_90] += aiStack_454[local_90];
            aiStack_350[local_90] += aiStack_50[local_90];
          }
        }
      }
      if ((((*(i8 *)((char *)&game.game_options + 1)) & 4) == 0) && (local_c0 < local_b8 - 1)) {
        do {
          win_flush_pending_msgs();
          local_304 = timeGetTime();
          if (2 < game.multiplayer) {
            net_process_messages((NetSession *)&net_session,1,0);
          }
        } while ((int)(local_304 - local_bc) < local_3c8);
        local_bc = local_304;
      }
    }
    map_redraw_busy = 0;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0056d25b */ { FUN_005f2490((iptr)&local_300,0x48,8,surface_dtor); }
  }
  return;
}
#undef human_civ
#undef map_redraw_busy
#undef mapview_half_tile_height
#undef mapview_origin_x
#undef mapview_origin_y
#undef mapview_zoom
#undef net_move_anim_sound
#undef net_move_anim_sound_arg
#undef aiStack_454
#undef local_434
#undef auStack_430
#undef local_410
#undef local_40c
#undef aiStack_408
#undef aiStack_3e8
#undef local_3c8
#undef local_3c4
#undef local_3c0
#undef local_3bc
#undef local_3b8
#undef auStack_3b4
#undef aiStack_394
#undef local_374
#undef aiStack_370
#undef aiStack_350
#undef local_330
#undef aiStack_32c
#undef acStack_30c
#undef local_304
#undef local_300
#undef local_c0
#undef local_bc
#undef local_b8
#undef local_b4
#undef aiStack_b0
#undef local_90
#undef local_8c
#undef aiStack_88
#undef local_68
#undef local_64
#undef local_60
#undef aiStack_50
#undef aiStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0056e180 auto */
i32 __thiscall map_view_zoom_scale_round(MapViewZoomView *this,i32 param_1)

{
  i32 uVar1;
  
  uVar1 = gfx_zoom_scale_round(param_1,(int)(short)this->zoom);
  return uVar1;
}

/* 0057ed3f auto */
#define map_redraw_busy (*(i32 *)((u8 *)&g.d_006ad908))
#define mapview_origin_x (*(i32 *)((u8 *)&g.d_0066ca90))
#define mapview_origin_y (*(i32 *)((u8 *)&g.d_0066ca94))
#define mapview_zoom (*(i16 *)((u8 *)&g.d_0066ca8c))
#define local_3d8 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_3c8 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define aiStack_3c4 (*(iptr (*)[8])(frame_ + FRAME_OFF(20)))
#define aiStack_3a4 (*(iptr (*)[8])(frame_ + FRAME_OFF(52)))
#define local_384 (*(DWORD *)(frame_ + FRAME_OFF(84)))
#define auStack_380 (*(i32 (*)[8])(frame_ + FRAME_OFF(88)))
#define aiStack_360 (*(int (*)[8])(frame_ + FRAME_OFF(120)))
#define local_340 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_33c (*(DWORD *)(frame_ + FRAME_OFF(156)))
#define aiStack_338 (*(int (*)[8])(frame_ + FRAME_OFF(160)))
#define local_318 (*(DibSurface (*)[8])(frame_ + FRAME_OFF(192)))
#define local_d8 (*(int *)(frame_ + FRAME_OFF(768)))
#define aiStack_d4 (*(int (*)[8])(frame_ + FRAME_OFF(772)))
#define local_b4 (*(iptr *)(frame_ + FRAME_OFF(804)))
#define auStack_b0 (*(i8 (*)[128])(frame_ + FRAME_OFF(808)))
#define aiStack_30 (*(int (*)[8])(frame_ + FRAME_OFF(936)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(968)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(972)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(976)))
i32 __cdecl map_animate_explosion(i32 param_1,i32 param_2,int param_3)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(984)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  FUN_005f2620(local_318,0x48,8,surface_ctor,surface_dtor);
  local_8 = 0;
  local_340 = 0;
  map_redraw_busy = 1;
  nm_abort_kaboom_count = 0;
  for (local_b4 = 0; local_b4 < 8; local_b4++) {
    aiStack_338[local_b4] = 0;
    if (((local_b4 == 0) || (*(short *)(&map_view_open_flags + local_b4 * 0x3f0) != 0)) &&
       (iVar1 = mapview_tile_in_view
                          ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),param_1,param_2),
       iVar1 != 0)) {
      aiStack_338[local_b4] = 1;
      local_340 = 1;
      aiStack_30[local_b4] = (&mapview_origin_x)[local_b4 * 0xfc];
      aiStack_d4[local_b4] = (&mapview_origin_y)[local_b4 * 0xfc];
      iVar2 = mapview_zoom_scale
                        ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),0x20);
      aiStack_3a4[local_b4] = iVar2;
      iVar2 = mapview_zoom_scale
                        ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),0x20);
      aiStack_3c4[local_b4] = iVar2;
      mapview_tile_to_screen
                ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),(iptr)(aiStack_360 + local_b4)
                 ,(iptr)(auStack_380 + local_b4),param_1,param_2);
      aiStack_360[local_b4] += *(int *)(&mapview_quarter_tile_width + local_b4 * 0x3f0);
      rect_set_xywh((iptr)(auStack_b0 + local_b4 * 0x10),aiStack_360[local_b4],
                         auStack_380[local_b4],aiStack_3a4[local_b4],aiStack_3c4[local_b4]);
      surface_create
                (local_318 + local_b4,*(i32 *)(&mapview_tile_width + local_b4 * 0x3f0),
                 *(i32 *)(&mapview_tile_height + local_b4 * 0x3f0));
      gfx_copy_rect_clipped((iptr)(&map_views + local_b4 * 0x3f0),(iptr)(local_318 + local_b4),
                         aiStack_360[local_b4],auStack_380[local_b4],
                         (&mapview_client_origin_x)[local_b4 * 0xfc],(&mapview_client_origin_y)[local_b4 * 0xfc],0,0,0,0,
                         aiStack_3a4[local_b4],aiStack_3c4[local_b4]);
    }
  }
  if (local_340 == 0) {
    map_redraw_busy = 0;
    local_3c8 = 0;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0057f628 */ { FUN_005f2490((iptr)&local_318,0x48,8,surface_dtor); }
  }
  else {
    if (param_3 != 0) {
      snd_play_effect(param_3,1,0,0);
    }
    local_384 = timeGetTime();
    for (local_d8 = 0; local_d8 < 8; local_d8++) {
      for (local_b4 = 0; local_b4 < 8; local_b4++) {
        if (aiStack_338[local_b4] != 0) {
          iVar1 = mapview_tile_in_view
                            ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),param_1,param_2);
          if (iVar1 == 0) {
            aiStack_338[local_b4] = 0;
          }
          else {
            if (((&mapview_origin_x)[local_b4 * 0xfc] != aiStack_30[local_b4]) ||
               ((&mapview_origin_y)[local_b4 * 0xfc] != aiStack_d4[local_b4])) {
              aiStack_30[local_b4] = (&mapview_origin_x)[local_b4 * 0xfc];
              aiStack_d4[local_b4] = (&mapview_origin_y)[local_b4 * 0xfc];
              iVar2 = mapview_zoom_scale
                                ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),0x20);
              aiStack_3a4[local_b4] = iVar2;
              iVar2 = mapview_zoom_scale
                                ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),0x20);
              aiStack_3c4[local_b4] = iVar2;
              mapview_tile_to_screen
                        ((C_004083b0_430 *)(&map_views + local_b4 * 0x3f0),
                         (iptr)(aiStack_360 + local_b4),(iptr)(auStack_380 + local_b4),param_1,
                         param_2);
              aiStack_360[local_b4] =
                   aiStack_360[local_b4] + *(int *)(&mapview_quarter_tile_width + local_b4 * 0x3f0);
              rect_set_xywh((iptr)(auStack_b0 + local_b4 * 0x10),aiStack_360[local_b4],
                                 auStack_380[local_b4],aiStack_3a4[local_b4],aiStack_3c4[local_b4]);
              surface_create
                        (local_318 + local_b4,*(i32 *)(&mapview_tile_width + local_b4 * 0x3f0),
                         *(i32 *)(&mapview_tile_height + local_b4 * 0x3f0));
              gfx_copy_rect_clipped((iptr)(&map_views + local_b4 * 0x3f0),
                                 (iptr)(local_318 + local_b4),aiStack_360[local_b4],
                                 auStack_380[local_b4],(&mapview_client_origin_x)[local_b4 * 0xfc],
                                 (&mapview_client_origin_y)[local_b4 * 0xfc],0,0,0,0,aiStack_3a4[local_b4],
                                 aiStack_3c4[local_b4]);
            }
            gfx_set_zoom_scale((int)(short)(&mapview_zoom)[local_b4 * 0x1f8]);
            sprite_draw
                      ((Sprite *)(&explosion_sprites + local_d8 * 0x3c),(iptr)local_3d8,
                       (iptr)(&map_views + local_b4 * 0x3f0),aiStack_360[local_b4],
                       auStack_380[local_b4]);
            wnd_blit_surface_rect
                      ((DibSurface *)(&map_views + local_b4 * 0x3f0),
                       (iptr)(auStack_b0 + local_b4 * 0x10));
          }
        }
      }
      do {
        win_flush_pending_msgs();
        local_33c = timeGetTime();
        if ((2 < game.multiplayer) &&
           (net_process_messages((NetSession *)&net_session,1,0), nm_abort_kaboom_count != 0))
        goto LAB_0057f5f8;
      } while ((int)(local_33c - local_384) < 0x40);
      local_384 = local_33c;
      for (local_b4 = 0; local_b4 < 8; local_b4++) {
        if (aiStack_338[local_b4] != 0) {
          gfx_copy_rect_clipped((iptr)(local_318 + local_b4),(iptr)(&map_views + local_b4 * 0x3f0),0
                             ,0,0,0,aiStack_360[local_b4],auStack_380[local_b4],
                             (&mapview_client_origin_x)[local_b4 * 0xfc],(&mapview_client_origin_y)[local_b4 * 0xfc],
                             aiStack_3a4[local_b4],aiStack_3c4[local_b4]);
        }
      }
    }
    ui_delay_ticks(10);
LAB_0057f5f8:
    gfx_reset_zoom_scale();
    map_redraw_busy = 0;
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0057f628 */ { FUN_005f2490((iptr)&local_318,0x48,8,surface_dtor); }
    local_3c8 = 1;
  }
  return local_3c8;
}
#undef map_redraw_busy
#undef mapview_origin_x
#undef mapview_origin_y
#undef mapview_zoom
#undef local_3d8
#undef local_3c8
#undef aiStack_3c4
#undef aiStack_3a4
#undef local_384
#undef auStack_380
#undef aiStack_360
#undef local_340
#undef local_33c
#undef aiStack_338
#undef local_318
#undef local_d8
#undef aiStack_d4
#undef local_b4
#undef auStack_b0
#undef aiStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0057f657 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_redraw_busy (*(i32 *)((u8 *)&g.d_006ad908))
#define mapview_half_tile_height (*(int *)((u8 *)&g.d_0066cabc))
#define local_60 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_50 (*(DibSurface * *)(frame_ + FRAME_OFF(16)))
#define local_4c (*(DibSurface * *)(frame_ + FRAME_OFF(20)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_3c (*(DWORD *)(frame_ + FRAME_OFF(36)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_2c (*(DWORD *)(frame_ + FRAME_OFF(52)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_24 (*(DibSurface * *)(frame_ + FRAME_OFF(60)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(80)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(88)))
void __cdecl map_animate_nuke(iptr x,iptr y)

{
  int iVar1;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  iVar1 = map_in_bounds(x,y);
  if ((iVar1 != 0) && (iVar1 = tile_visible_to(x,y,human_civ), iVar1 != 0)) {
    map_redraw_busy = 1;
    local_4c = operator_new(0x48);
    local_8 = 0;
    if (local_4c == (DibSurface *)0x0) {
      local_50 = (DibSurface *)0x0;
    }
    else {
      local_50 = (DibSurface *)surface_ctor(local_4c);
    }
    local_8 = 0xffffffff;
    local_24 = local_50;
    mapviews_ensure_visible(x,y,human_civ);
    ui_flush_input();
    snd_play_effect(0x32,0,0,0);
    if (((byte)game.game_options & 0x10) != 0) {
      win_flush_pending_msgs();
      local_3c = timeGetTime();
      do {
        win_flush_pending_msgs();
        if (2 < game.multiplayer) {
          net_process_messages((NetSession *)&net_session,1,0);
        }
        local_2c = timeGetTime();
      } while ((int)(local_2c - local_3c) < 0x157c);
    }
    local_38 = mapview_zoom_scale((C_004083b0_430 *)&map_views,0x5b);
    local_44 = mapview_zoom_scale((C_004083b0_430 *)&map_views,0x48);
    surface_create(local_24,local_38,local_44);
    mapview_tile_to_screen
              ((C_004083b0_430 *)&map_views,(iptr)&local_48,(iptr)&local_28,x,y);
    local_30 = (mapview_half_tile_width + local_48) - (local_38 >> 1);
    local_40 = (mapview_half_tile_height + local_28) - (local_44 >> 1);
    gfx_copy_rect_clipped(ADDR(0x66c7a8, ((u8 *)&g.d_0066c7a8)),(iptr)local_24,local_30,local_40,mapview_client_origin_x,mapview_client_origin_y,0,0,0,0,
                       local_38,local_44);
    rect_set_xywh((iptr)&local_20,local_30,local_40,local_38,local_44);
    if (local_20 < 0) {
      local_20 = 0;
    }
    if (local_1c < 0) {
      local_1c = 0;
    }
    iVar1 = rect_width((iptr)&local_20);
    if ((0 < iVar1) && (iVar1 = rect_height((iptr)&local_20), 0 < iVar1)) {
      local_3c = timeGetTime();
      mapview_apply_zoom((C_004083b0_430 *)&map_views);
      for (local_34 = 0; local_34 < 0xb; local_34++) {
        sprite_draw
                  ((Sprite *)(&nuke_anim_sprites + local_34 * 0x3c),(iptr)local_60,ADDR(0x66c7a8, ((u8 *)&g.d_0066c7a8)),
                   local_30,local_40);
        wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_20);
        do {
          win_flush_pending_msgs();
          if (2 < game.multiplayer) {
            net_process_messages((NetSession *)&net_session,1,0);
          }
          local_2c = timeGetTime();
        } while ((int)(local_2c - local_3c) < 100);
        local_3c = local_2c;
        gfx_copy_rect_clipped((iptr)local_24,ADDR(0x66c7a8, ((u8 *)&g.d_0066c7a8)),0,0,0,0,local_30,local_40,mapview_client_origin_x,
                           mapview_client_origin_y,local_38,local_44);
      }
      gfx_reset_zoom_scale();
      wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_20);
    }
    if (local_24 != (DibSurface *)0x0) {
      surface_delete(local_24,1);
    }
    map_redraw_busy = 0;
  }
  return;
}
#undef human_civ
#undef map_redraw_busy
#undef mapview_half_tile_height
#undef local_60
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
#undef local_10
#undef puStack_c
#undef local_8

/* 005802fd auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl
map_redraw_combat_tiles(i32 param_1,i32 param_2,i32 param_3,i32 param_4)

{
  map_redraw_area_all_views(param_1,param_2,0,human_civ,1);
  map_redraw_area_all_views(param_3,param_4,0,human_civ,1);
  return;
}
#undef human_civ

/* 0058c56c auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl tile_has_irrigation_source(int param_1,int param_2)

{
  iptr x;
  int y;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  do {
    if (4 < local_8) {
      return 0;
    }
    x = map_wrap_x((char)(&diag_dx_table)[local_8] + param_1);
    y = (char)(&diag_dy_table)[local_8] + param_2;
    iVar3 = map_in_bounds(x,y);
    if (iVar3 != 0) {
      iVar3 = tile_is_ocean(x,y);
      if (iVar3 != 0) {
        return 1;
      }
      pbVar4 = (byte *)tile_at(x,y);
      if ((*pbVar4 & 0x80) != 0) {
        return 1;
      }
      uVar5 = tile_improvements(x,y);
      if ((uVar5 & 4) != 0) {
        return 1;
      }
    }
    local_8++;
  } while( true );
}
#undef local_8

/* 0058fda9 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl map_reveal_adjacent_units(int x,int y,iptr civ)

{
  int iVar1;
  iptr x2;
  int y2;
  int iVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = tile_is_ocean(x,y);
  net_batch_begin();
  for (local_8 = 0; local_8 < 8; local_8++) {
    x2 = map_wrap_x((char)(&dir_dx_table)[local_8] + x);
    y2 = (char)(&dir_dy_table)[local_8] + y;
    iVar4 = map_in_bounds(x2,y2);
    if ((((iVar4 != 0) && (iVar4 = tile_is_ocean(x2,y2), iVar4 == iVar1)) &&
        (iVar4 = tile_unit_owner(x2,y2), -1 < iVar4)) &&
       (tile_reveal_to_civ(x2,y2,civ), human_civ == civ)) {
      map_redraw_area_all_views(x2,y2,0,civ,1);
      net_send_message(0x75,0xff,x2,y2,0,0,0,0,0,0);
    }
  }
  net_batch_flush();
  return;
}
#undef human_civ
#undef local_8

/* 005ae052 auto */
iptr __cdecl map_wrap_x(iptr param_1)

{
  if ((game.rules & 0x8000) == 0) {
    if (param_1 < 0) {
      param_1 = map.width + param_1;
    }
    else if (map.width <= param_1) {
      param_1 -= map.width;
    }
  }
  return param_1;
}

/* 005ae10e auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl map_dx_wrapped(int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == param_2 || param_1 - param_2 < 0) {
    local_8 = ~(param_1 - param_2) + 1;
  }
  else {
    local_8 = param_1 - param_2;
  }
  if (((game.rules & 0x8000) == 0) && ((int)map.width >> 1 < local_8)) {
    local_8 = map.width - local_8;
  }
  return local_8;
}
#undef local_8

/* 005ae1b0 auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl map_distance(int param_1,int param_2,int param_3,int param_4)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == param_3 || param_1 - param_3 < 0) {
    local_8 = ~(param_1 - param_3) + 1;
  }
  else {
    local_8 = param_1 - param_3;
  }
  if (((game.rules & 0x8000) == 0) && ((int)map.width >> 1 < local_8)) {
    local_8 = map.width - local_8;
  }
  if (param_2 == param_4 || param_2 - param_4 < 0) {
    local_c = ~(param_2 - param_4) + 1;
  }
  else {
    local_c = param_2 - param_4;
  }
  return local_c + local_8 >> 1;
}
#undef local_c
#undef local_8

/* 005ae31d auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
i32 __cdecl map_distance_diag(i32 param_1,int param_2,i32 param_3,int param_4)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = map_dx_wrapped(param_1,param_3);
  if (param_2 == param_4 || param_2 - param_4 < 0) {
    local_c = ~(param_2 - param_4) + 1;
  }
  else {
    local_c = param_2 - param_4;
  }
  uVar1 = dist_from_deltas(uVar1,local_c);
  return uVar1;
}
#undef local_c

/* 005b2e69 auto */
#define unit_move_anim_active (*(int *)((u8 *)&g.d_00636058))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl tile_first_unit(int x,int y)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit2 = -1;
  if ((unit_move_anim_active == 0) || (iVar1 = tile_unit_owner(x,y), -1 < iVar1)) {
    for (unit = 0; (unit2 < 0 && (unit < game.num_units)); unit++) {
      if ((units[unit].id != 0) &&
         ((units[unit].x == x && (units[unit].y == y)))) {
        unit2 = unit;
      }
    }
    if (-1 < unit2) {
      unit_stack_validate(unit2);
    }
    uVar2 = unit_stack_first(unit2);
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
#undef unit_move_anim_active
#undef unit
#undef unit2

/* 005b49cf auto */
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
uint __cdecl tile_adjacent_nonallied_civ(iptr x,int y,iptr civ)

{
  int iVar1;
  iptr x2;
  int y2;
  int iVar4;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_1c = tile_is_ocean(x,y);
  iVar1 = tile_city_owner(x,y);
  adjacent_foreign_civ = -1;
  for (local_8 = 0; (adjacent_foreign_civ < 0 && (local_8 < 8)); local_8++) {
    x2 = map_wrap_x((char)(&dir_dx_table)[local_8] + x);
    y2 = (char)(&dir_dy_table)[local_8] + y;
    iVar4 = map_in_bounds(x2,y2);
    if (iVar4 != 0) {
      if (iVar1 < 0) {
        local_c = tile_is_ocean(x2,y2);
      }
      else {
        local_c = local_1c;
      }
      local_20 = tile_city_owner(x2,y2);
      if (local_20 < 0) {
        local_20 = tile_unit_owner(x2,y2);
      }
      else {
        local_1c = local_c;
      }
      if ((((-1 < local_20) && (local_20 != civ)) && (local_c == local_1c)) &&
         ((*(byte *)&civs[civ].treaties[local_20] & 8) == 0)) {
        adjacent_foreign_civ = local_20;
      }
    }
  }
  return (uint)(-1 < adjacent_foreign_civ);
}
#undef local_20
#undef local_1c
#undef local_c
#undef local_8

/* 005b4b66 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
uint __cdecl tile_adjacent_nonallied_unit(int param_1,int param_2,iptr civ)

{
  char cVar1;
  iptr x;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  adjacent_foreign_civ = -1;
  for (local_8 = 0; (adjacent_foreign_civ < 0 && (local_8 < 8)); local_8++) {
    x = map_wrap_x((char)(&dir_dx_table)[local_8] + param_1);
    cVar1 = (&dir_dy_table)[local_8];
    iVar3 = map_in_bounds(x,cVar1 + param_2);
    if ((iVar3 != 0) &&
       (((iVar3 = tile_unit_owner(x,cVar1 + param_2), -1 < iVar3 && (civ != iVar3)) &&
        ((*(byte *)&civs[civ].treaties[iVar3] & 8) == 0)))) {
      adjacent_foreign_civ = iVar3;
    }
  }
  return (uint)(-1 < adjacent_foreign_civ);
}
#undef local_8

/* 005b4c63 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
uint __cdecl tile_zoc_unit_adjacent(int x,int y,iptr civ)

{
  int iVar1;
  iptr x2;
  int y2;
  int iVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  adjacent_foreign_civ = -1;
  iVar1 = tile_is_ocean(x,y);
  for (local_8 = 0; (adjacent_foreign_civ < 0 && (local_8 < 8)); local_8++) {
    x2 = map_wrap_x((char)(&dir_dx_table)[local_8] + x);
    y2 = (char)(&dir_dy_table)[local_8] + y;
    iVar4 = map_in_bounds(x2,y2);
    if (((iVar4 != 0) &&
        (((iVar4 = tile_unit_owner(x2,y2), -1 < iVar4 && (iVar4 != civ)) &&
         (y2 = tile_is_ocean(x2,y2), y2 == iVar1)))) &&
       ((*(byte *)&civs[civ].treaties[iVar4] & 8) == 0)) {
      adjacent_foreign_civ = iVar4;
    }
  }
  return (uint)(-1 < adjacent_foreign_civ);
}
#undef local_8

/* 005b4d8c auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl tile_in_enemy_zoc(iptr x,i32 y,iptr civ)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  adjacent_foreign_civ = -1;
  iVar1 = tile_city_owner(x,y);
  if (iVar1 < 0) {
    local_8 = tile_zoc_unit_adjacent(x,y,civ);
  }
  return local_8;
}
#undef local_8

/* 005b7fe0 auto */
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(Tile * *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(16)))
void __cdecl map_alloc(void)

{
  void *pvVar1;
  u8 *puVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  map.quarter_w = (i16)(map.width + 3 >> 2);
  map.quarter_h = (i16)(map.height + 3 >> 2);
  map.area = (map.width / 2) * map.height;
  local_8 = map.area * 6;
  if ((local_8 & 3) != 0) {
    local_8 = (4 - (local_8 & 3)) + local_8;
  }
  map_tiles_handle = (void *)mem_handle_alloc_tracked(local_8);
  if (map_tiles_handle == (void *)0x0) {
    error_report(0xfffffff7,5,0,(int)map.width,(int)map.height);
  }
  map_tiles = (Tile *)mem_lock_handle((iptr)map_tiles_handle);
  if (map_tiles == (Tile *)0x0) {
    error_report(0xfffffff6,5,0,(int)map.width,(int)map.height);
  }
  local_14 = map_tiles;
  for (local_c = 0; local_c < map.area; local_c++) {
    local_14->terrain = '\n';
    local_14->improvements = '\0';
    local_14->radius = '\0';
    local_14->landmass = '\0';
    local_14->visible = '\0';
    local_14->owner = '\0';
    local_14++;
  }
  local_8 = (uint)map.area;
  if ((local_8 & 3) != 0) {
    local_8 = (4 - (local_8 & 3)) + local_8;
  }
  for (local_18 = 1; local_18 < 8; local_18++) {
    pvVar1 = (void *)mem_handle_alloc_tracked(local_8);
    map_known_handles[local_18] = pvVar1;
    if (map_known_handles[local_18] == (void *)0x0) {
      error_report(0xfffffff7,5,0,0xea,local_18);
    }
    puVar2 = (u8 *)mem_lock_handle((iptr)map_known_handles[local_18]);
    map_known[local_18] = puVar2;
    if (map_known[local_18] == (u8 *)0x0) {
      error_report(0xfffffff6,5,0,0xea,local_18);
    }
    _memset(map_known[local_18],0,(int)map.area);
  }
  local_8 = (int)map.quarter_w * (int)map.quarter_h;
  if ((local_8 & 3) != 0) {
    local_8 = (4 - (local_8 & 3)) + local_8;
  }
  map_coarse_handles[0] = (void *)mem_handle_alloc_tracked(local_8);
  if (map_coarse_handles[0] == (void *)0x0) {
    error_report(0xfffffff7,5,0,(int)map.quarter_w,0);
  }
  map_coarse[0] = (u8 *)mem_lock_handle((iptr)map_coarse_handles[0]);
  if (map_coarse[0] == (u8 *)0x0) {
    error_report(0xfffffff6,5,0,(int)map.quarter_w,0);
  }
  map_coarse_handles[1] = (void *)mem_handle_alloc_tracked(local_8);
  if (map_coarse_handles[1] == (void *)0x0) {
    error_report(0xfffffff7,5,0,(int)map.quarter_w,1);
  }
  map_coarse[1] = (u8 *)mem_lock_handle((iptr)map_coarse_handles[1]);
  if (map_coarse[1] == (u8 *)0x0) {
    error_report(0xfffffff6,5,0,(int)map.quarter_w,1);
  }
  map_coarse_handles[2] = (void *)mem_handle_alloc_tracked(local_8);
  if (map_coarse_handles[2] == (void *)0x0) {
    error_report(0xfffffff7,5,0,(int)map.quarter_w,2);
  }
  map_coarse[2] = (u8 *)mem_lock_handle((iptr)map_coarse_handles[2]);
  if (map_coarse[2] == (u8 *)0x0) {
    error_report(0xfffffff6,5,0,(int)map.quarter_w,2);
  }
  map_coarse_handles[3] = (void *)mem_handle_alloc_tracked(local_8);
  if (map_coarse_handles[3] == (void *)0x0) {
    error_report(0xfffffff7,5,0,(int)map.quarter_w,3);
  }
  map_coarse[3] = (u8 *)mem_lock_handle((iptr)map_coarse_handles[3]);
  if (map_coarse[3] == (u8 *)0x0) {
    error_report(0xfffffff6,5,0,(int)map.quarter_w,3);
  }
  map_allocated = 1;
  return;
}
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 005b8416 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl map_free(void)

{
  u8 *puVar1;
  void *pvVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (map_allocated != '\0') {
    if (map_coarse[3] != (u8 *)0x0) {
      map_coarse[3] = (u8 *)mem_unlock_handle((iptr)map_coarse_handles[3]);
    }
    if (map_coarse_handles[3] != (void *)0x0) {
      map_coarse_handles[3] = (void *)mem_free_handle((iptr)map_coarse_handles[3]);
    }
    if (map_coarse[2] != (u8 *)0x0) {
      map_coarse[2] = (u8 *)mem_unlock_handle((iptr)map_coarse_handles[2]);
    }
    if (map_coarse_handles[2] != (void *)0x0) {
      map_coarse_handles[2] = (void *)mem_free_handle((iptr)map_coarse_handles[2]);
    }
    if (map_coarse[1] != (u8 *)0x0) {
      map_coarse[1] = (u8 *)mem_unlock_handle((iptr)map_coarse_handles[1]);
    }
    if (map_coarse_handles[1] != (void *)0x0) {
      map_coarse_handles[1] = (void *)mem_free_handle((iptr)map_coarse_handles[1]);
    }
    if (map_coarse[0] != (u8 *)0x0) {
      map_coarse[0] = (u8 *)mem_unlock_handle((iptr)map_coarse_handles[0]);
    }
    if (map_coarse_handles[0] != (void *)0x0) {
      map_coarse_handles[0] = (void *)mem_free_handle((iptr)map_coarse_handles[0]);
    }
    if (map_tiles != (Tile *)0x0) {
      map_tiles = (Tile *)mem_unlock_handle((iptr)map_tiles_handle);
    }
    if (map_tiles_handle != (void *)0x0) {
      map_tiles_handle = (void *)mem_free_handle((iptr)map_tiles_handle);
    }
    for (local_8 = 1; local_8 < 8; local_8++) {
      if (map_known[local_8] != (u8 *)0x0) {
        puVar1 = (u8 *)mem_unlock_handle((iptr)map_known_handles[local_8]);
        map_known[local_8] = puVar1;
      }
      if (map_known_handles[local_8] != (void *)0x0) {
        pvVar2 = (void *)mem_free_handle((iptr)map_known_handles[local_8]);
        map_known_handles[local_8] = pvVar2;
      }
    }
    map_allocated = '\0';
  }
  return;
}
#undef local_8

/* 005b85fe auto */
void __cdecl map_new_seed(void)

{
  uint uVar1;
  
  uVar1 = timer_ticks();
  map.seed = (ushort)uVar1 & 0x7fff;
  if ((uVar1 & 0x7fff) == 0) {
    map.seed++;
  }
  return;
}

/* 005b8635 auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
i32 __cdecl map_write(iptr param_1,int param_2)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 1;
  sVar1 = _fwrite(&map,0xe,1,(FILE *)param_1);
  if (sVar1 != 0) {
    if (param_2 == 0) {
      for (local_10 = 1; local_10 < 8; local_10++) {
        sVar1 = _fwrite(map_known[local_10],(int)map.area,1,(FILE *)param_1);
        if (sVar1 == 0) {
          return 1;
        }
      }
    }
    else {
      sVar1 = _fwrite(start_x,0x2a,1,(FILE *)param_1);
      if (sVar1 == 0) {
        return 1;
      }
      sVar1 = _fwrite(start_y,0x2a,1,(FILE *)param_1);
      if (sVar1 == 0) {
        return 1;
      }
    }
    sVar1 = _fwrite(map_tiles,map.area * 6,1,(FILE *)param_1);
    if (sVar1 != 0) {
      local_c = 0;
    }
  }
  return local_c;
}
#undef local_10
#undef local_c

/* 005b8783 auto */
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_28 (*(i8 (*)[36])(frame_ + FRAME_OFF(16)))
i32 __cdecl map_read(iptr param_1,int param_2)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_30 = 1;
  sVar1 = _fread(local_28,0xe,1,(FILE *)param_1);
  if (sVar1 != 0) {
    if (param_2 == 0) {
      for (local_34 = 0; local_34 < 0x15; local_34++) {
        start_x[local_34] = -1;
        start_y[local_34] = -1;
      }
    }
    else {
      sVar1 = _fread(start_x,0x2a,1,(FILE *)param_1);
      if (sVar1 == 0) {
        return 1;
      }
      sVar1 = _fread(start_y,0x2a,1,(FILE *)param_1);
      if (sVar1 == 0) {
        return 1;
      }
    }
    map_free();
    FUN_005f2110(&map,local_28,0xe);
    map_alloc();
    if (param_2 == 0) {
      for (local_34 = 1; local_34 < 8; local_34++) {
        sVar1 = _fread(map_known[local_34],(int)map.area,1,(FILE *)param_1);
        if (sVar1 == 0) {
          return 1;
        }
      }
    }
    sVar1 = _fread(map_tiles,map.area * 6,1,(FILE *)param_1);
    if (sVar1 != 0) {
      local_30 = 0;
    }
  }
  return local_30;
}
#undef local_34
#undef local_30
#undef local_28

/* 005b8931 auto */
Tile * __cdecl tile_at(iptr param_1,iptr param_2)

{
  int iVar1;
  Tile *pTVar2;
  
  iVar1 = map_in_bounds(param_1,param_2);
  if (iVar1 == 0) {
    pTVar2 = &map_offmap_tile;
  }
  else {
    pTVar2 = (Tile *)(&map_tiles->terrain +
                     ((int)map.width & 0xfffffffeU) * param_2 * 3 + (param_1 & 0xfffffffeU) * 3);
  }
  return pTVar2;
}

/* 005b898b auto */
u8 * __cdecl known_at(int param_1,int param_2,iptr param_3)

{
  return map_known[param_3] + (param_1 >> 1) + ((int)map.width >> 1) * param_2;
}

/* 005b89bb auto */
byte __cdecl tile_terrain(iptr x,iptr y)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)tile_at(x,y);
  return *pbVar1 & 0xf;
}

/* 005b89e4 auto */
uint __cdecl tile_is_ocean(i32 x,i32 y)

{
  char cVar1;
  
  cVar1 = tile_terrain(x,y);
  return (uint)(cVar1 == '\n');
}

/* 005b8a1d auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl tile_owner(iptr x,iptr y)

{
  iptr iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = map_in_bounds(x,y);
  if (iVar1 == 0) {
    local_8 = -1;
  }
  else {
    iVar2 = tile_at(x,y);
    local_8 = (int)(uint)*(byte *)(iVar2 + 5) >> 4;
    if (local_8 == 0xf) {
      local_8 = -1;
    }
  }
  return local_8;
}
#undef local_8

/* 005b8a81 auto */
uint __cdecl tile_landmass(iptr x,iptr y)

{
  iptr iVar1;
  
  iVar1 = tile_at(x,y);
  return (uint)*(byte *)(iVar1 + 3);
}

/* 005b8aa8 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl tile_land_landmass(iptr x,iptr y)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  iVar1 = tile_is_ocean(x,y);
  if (iVar1 == 0) {
    local_8 = tile_landmass(x,y);
  }
  return local_8;
}
#undef local_8

/* 005b8af0 auto */
int __cdecl tile_radius_civ(iptr x,iptr y)

{
  iptr iVar1;
  
  iVar1 = tile_at(x,y);
  return (int)(uint)*(byte *)(iVar1 + 2) >> 5;
}

/* 005b8b1a auto */
void __cdecl tile_update_known(iptr x,iptr y,iptr param_3)

{
  iptr iVar1;
  i32 uVar1;
  i32 uVar2;
  
  if (param_3 != 0) {
    uVar2 = 1;
    uVar1 = 0;
    iVar1 = tile_at(x,y);
    known_set(x,y,CONCAT31((int3)((uint)iVar1 >> 8),*(i8 *)(iVar1 + 1)),param_3,
              uVar1,uVar2);
  }
  return;
}

/* 005b8b65 auto */
uint __cdecl tile_visible_to(iptr x,iptr y,iptr param_3)

{
  uint uVar1;
  iptr iVar2;
  
  if (param_3 < 0) {
    uVar1 = 1;
  }
  else {
    iVar2 = tile_at(x,y);
    uVar1 = (uint)*(byte *)(iVar2 + 4) & 1 << ((byte)param_3 & 0x1f);
  }
  return uVar1;
}

/* 005b8c18 auto */
uint __cdecl tile_get_fertility(iptr x,iptr y)

{
  iptr iVar1;
  
  iVar1 = tile_at(x,y);
  return *(byte *)(iVar1 + 5) & 0xf;
}

/* 005b8c42 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl tile_owner_or_fertility(i32 x,iptr y)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = tile_radius_civ(x,y);
  if (((local_8 == 0) && (local_8 = tile_get_fertility(x,y), local_8 != 0)) &&
     (local_8 < 9)) {
    local_8 = 8;
  }
  return local_8;
}
#undef local_8

/* 005b8ca6 auto */
i32 __cdecl tile_city_owner(iptr x,iptr y)

{
  int iVar1;
  i32 uVar2;
  
  iVar1 = map_in_bounds(x,y);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = tile_improvements(x,y);
    if (((byte)uVar2 & 0x42) == 2) {
      uVar2 = tile_owner(x,y);
    }
    else {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

/* 005b8d15 auto */
i32 __cdecl tile_airbase_owner(i32 x,i32 y)

{
  i32 uVar1;
  
  uVar1 = tile_improvements(x,y);
  if (((byte)uVar1 & 0x42) == 0x42) {
    uVar1 = tile_owner(x,y);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* 005b8d62 auto */
i32 __cdecl tile_unit_owner(i32 x,i32 y)

{
  uint uVar1;
  i32 uVar2;
  
  uVar1 = tile_improvements(x,y);
  if ((uVar1 & 1) == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = tile_owner(x,y);
  }
  return uVar2;
}

/* 005b8da4 auto */
int __cdecl tile_city_or_unit_owner(iptr x,i32 y)

{
  int iVar1;
  
  iVar1 = tile_city_owner(x,y);
  if (iVar1 < 0) {
    iVar1 = tile_unit_owner(x,y);
  }
  return iVar1;
}

/* 005b8dec auto */
i32 __cdecl tile_owner_at_peace(iptr x,iptr y,iptr civ)

{
  int iVar1;
  
  iVar1 = map_in_bounds(x,y);
  if ((((iVar1 != 0) && (0 < civ)) && (iVar1 = tile_is_ocean(x,y), iVar1 == 0)) &&
     ((iVar1 = tile_radius_civ(x,y), 0 < iVar1 && (iVar1 != civ)))) {
    if ((*(byte *)&civs[civ].treaties[iVar1] & 8) != 0) {
      return 0xffffffff;
    }
    if ((*(byte *)&civs[civ].treaties[iVar1] & 4) != 0) {
      return iVar1;
    }
  }
  return 0xffffffff;
}

/* 005b8ee1 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl tile_resource(int x,int y)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = map_in_bounds(x,y);
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    pbVar2 = (byte *)tile_at(x,y);
    if ((*pbVar2 & 0x40) == 0) {
      if ((*pbVar2 & 0xf) == 2) {
        local_8 = 0;
      }
      else {
        uVar3 = y + x >> 1;
        uVar4 = x - (y + x >> 1);
        if ((uVar3 & 3) + (uVar4 & 3) * 4 ==
            ((y + x >> 3) * 0xb + ((int)uVar4 >> 2) * 0xd + (uint)map.seed & 0xf)) {
          local_8 = 1;
          uVar5 = 1 << ((byte)(map.seed >> 4) & 3);
          if ((uVar5 & uVar3) == (uVar5 & uVar4)) {
            local_8 = 2;
          }
        }
        else {
          local_8 = 0;
        }
      }
    }
    else {
      local_8 = 0;
    }
  }
  return local_8;
}
#undef local_8

/* 005b8ffa auto */
i32 __cdecl tile_has_hut(int x,int y)

{
  int iVar1;
  i32 uVar2;
  uint uVar3;
  
  iVar1 = map_in_bounds(x,y);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = tile_is_ocean(x,y);
    if (iVar1 == 0) {
      iVar1 = tile_owner(x,y);
      if (iVar1 < 0) {
        uVar3 = x - (x + y >> 1);
        if ((x + y >> 1 & 3U) + (uVar3 & 3) * 4 ==
            ((x + y >> 3) * 0xb + ((int)uVar3 >> 2) * 0xd + (uint)map.seed + 8 & 0x1f))
        {
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

/* 005b90df auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl tile_add_pollution(iptr x,iptr y)

{
  int iVar1;
  uint uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = map_in_bounds(x,y);
  if ((iVar1 != 0) && (uVar2 = tile_improvements(x,y), (uVar2 & 0x80) == 0)) {
    tile_set_improvements(x,y,0x80,1,1);
    for (local_8 = 1; local_8 < 8; local_8++) {
      tile_update_known(x,y,local_8);
    }
    game.polluted_tiles++;
  }
  return;
}
#undef local_8

/* 005b9431 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
uint __cdecl landmass_borders_body(int param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bit_index_split(param_2,(iptr)&local_c,(iptr)&local_8);
  return (uint)((local_8 & (byte)(&landmass_border_bits)[local_c + param_1 * 0x10]) != 0);
}
#undef local_c
#undef local_8

/* 005b947f auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl landmass_count_bordering(iptr param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 1; local_c < 0x3f; local_c++) {
    iVar1 = landmass_borders_body(local_c,param_1);
    if (iVar1 != 0) {
      local_8++;
    }
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 005b94d5 auto */
uint __cdecl tile_improvements(iptr x,iptr y)

{
  iptr iVar1;
  
  iVar1 = tile_at(x,y);
  return (uint)*(byte *)(iVar1 + 1);
}

/* 005b94fc auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_improvements(iptr x,iptr y,iptr param_3,iptr param_4,int param_5)

{
  char cVar1;
  iptr iVar2;
  
  iVar2 = tile_at(x,y);
  cVar1 = *(char *)(iVar2 + 1);
  if (param_4 == 0) {
    *(byte *)(iVar2 + 1) = *(byte *)(iVar2 + 1) & ~(byte)param_3;
  }
  else {
    *(byte *)(iVar2 + 1) = *(byte *)(iVar2 + 1) | (byte)param_3;
  }
  if (((param_5 != 0) && (*(char *)(iVar2 + 1) != cVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(0,x,y,param_3,param_4,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x90,0,x,y,param_3,param_4,1,0,0,0);
      }
      else {
        net_send_message(0x90,0xff,x,y,param_3,param_4,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b9646 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_terrain(iptr x,iptr y,iptr param_3,iptr param_4)

{
  byte bVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)tile_at(x,y);
  bVar1 = *pbVar2;
  *pbVar2 = *pbVar2 & 0xf0;
  *pbVar2 = *pbVar2 | (byte)param_3;
  if (((param_4 != 0) && (*pbVar2 != bVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(1,x,y,param_3,0,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x91,0,x,y,param_3,1,0,0,0,0);
      }
      else {
        net_send_message(0x91,0xff,x,y,param_3,0,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b976d auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_visible(iptr x,iptr y,iptr param_3,iptr param_4,int param_5)

{
  char cVar1;
  iptr iVar2;
  
  iVar2 = tile_at(x,y);
  cVar1 = *(char *)(iVar2 + 4);
  if (param_4 == 0) {
    *(byte *)(iVar2 + 4) = *(byte *)(iVar2 + 4) & ~(byte)param_3;
  }
  else {
    *(byte *)(iVar2 + 4) = *(byte *)(iVar2 + 4) | (byte)param_3;
  }
  if (((param_5 != 0) && (*(char *)(iVar2 + 4) != cVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(2,x,y,param_3,param_4,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x92,0,x,y,param_3,param_4,1,0,0,0);
      }
      else {
        net_send_message(0x92,0xff,x,y,param_3,param_4,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b98b7 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_fertility(iptr x,iptr y,iptr param_3,iptr param_4)

{
  char cVar1;
  iptr iVar2;
  
  iVar2 = tile_at(x,y);
  cVar1 = *(char *)(iVar2 + 5);
  *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) & 0xf0;
  *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) | (byte)param_3 & 0xf;
  if (((param_4 != 0) && (*(char *)(iVar2 + 5) != cVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(3,x,y,param_3,0,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x93,0,x,y,param_3,1,0,0,0,0);
      }
      else {
        net_send_message(0x93,0xff,x,y,param_3,0,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b99e8 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_owner(iptr x,iptr y,iptr param_3,iptr param_4)

{
  char cVar1;
  iptr iVar2;
  
  if ((param_3 < 0) || (8 < param_3)) {
    param_3 = 0xf;
  }
  iVar2 = tile_at(x,y);
  cVar1 = *(char *)(iVar2 + 5);
  *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) & 0xf;
  *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) | (byte)(param_3 << 4);
  if (((param_4 != 0) && (*(char *)(iVar2 + 5) != cVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(4,x,y,param_3,0,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x94,0,x,y,param_3,1,0,0,0,0);
      }
      else {
        net_send_message(0x94,0xff,x,y,param_3,0,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b9b35 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_landmass(iptr x,iptr y,iptr param_3,iptr param_4)

{
  char cVar1;
  iptr iVar2;
  
  iVar2 = tile_at(x,y);
  cVar1 = *(char *)(iVar2 + 3);
  *(i8 *)(iVar2 + 3) = (i8)param_3;
  if (((param_4 != 0) && (*(char *)(iVar2 + 3) != cVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(5,x,y,param_3,0,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x95,0,x,y,param_3,1,0,0,0,0);
      }
      else {
        net_send_message(0x95,0xff,x,y,param_3,0,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b9c49 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl tile_set_radius_civ(iptr x,iptr y,iptr param_3,iptr param_4)

{
  char cVar1;
  iptr iVar2;
  
  iVar2 = tile_at(x,y);
  cVar1 = *(char *)(iVar2 + 2);
  *(byte *)(iVar2 + 2) = *(byte *)(iVar2 + 2) & 0x1f;
  *(byte *)(iVar2 + 2) = (byte)((param_3 & 7U) << 5) | *(byte *)(iVar2 + 2);
  if (((param_4 != 0) && (*(char *)(iVar2 + 2) != cVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(6,x,y,param_3,0,0);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x96,0,x,y,param_3,1,0,0,0,0);
      }
      else {
        net_send_message(0x96,0xff,x,y,param_3,0,0,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled

/* 005b9d81 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(char *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(char *)((u8 *)&g.d_006ad699))
void __cdecl known_set(iptr param_1,iptr param_2,uptr param_3,iptr param_4,int param_5,int param_6)

{
  byte bVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)known_at(param_1,param_2,param_4);
  bVar1 = *pbVar2;
  if (param_5 == 0) {
    *pbVar2 = (byte)param_3;
  }
  else {
    *pbVar2 = *pbVar2 | (byte)param_3;
  }
  if (((param_6 != 0) && (*pbVar2 != bVar1)) && (2 < game.multiplayer)) {
    if ((net_host_flag == '\0') && (net_tile_batch_active != '\0')) {
      net_batch_add(7,param_1,param_2,param_3 & 0xff,param_4,param_5);
    }
    else if (net_tile_sync_enabled != '\0') {
      if (net_host_flag == '\0') {
        net_send_message(0x97,0,param_1,param_2,param_3 & 0xff,param_4,param_5,1,0,0);
      }
      else {
        net_send_message(0x97,0xff,param_1,param_2,param_3 & 0xff,param_4,param_5,0,0,0);
      }
    }
  }
  return;
}
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled
