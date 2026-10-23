/* The game, graphics: sprites, surfaces, palettes, fonts: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00407f90 auto */
int __cdecl rect_width(iptr param_1)

{
  return *(int *)(param_1 + 8) - *(int *)param_1;
}

/* 00407fc0 auto */
int __cdecl rect_height(iptr param_1)

{
  return *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4);
}

/* 004083f0 auto */
void __thiscall surface_release(DibSurface *this)

{
  surface_create(this,0,0);
  return;
}

/* 00408680 auto */
void __cdecl rect_set(iptr param_1,int param_2,int param_3,int param_4,int param_5)

{
  SetRect((LPRECT)param_1,param_2,param_3,param_4,param_5);
  return;
}

/* 004086c0 auto */
void __cdecl rect_set_xywh(iptr param_1,int param_2,int param_3,iptr param_4,iptr param_5)

{
  SetRect((LPRECT)param_1,param_2,param_3,param_4 + param_2,param_5 + param_3);
  return;
}

/* 00408700 auto */
#define gfx_draw_target (*(i32 *)((u8 *)&g.d_00635c64))
void __cdecl gfx_target_frame_rect(iptr param_1,i32 param_2)

{
  gfx_draw_box_ltrb(gfx_draw_target,*(i32 *)param_1,*(i32 *)(param_1 + 4),
                     *(int *)(param_1 + 8) - 1,*(int *)(param_1 + 0xc) - 1,param_2);
  return;
}
#undef gfx_draw_target

/* 00408750 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl gfx_fill_draw_target(i32 param_1)

{
  gfx_fill_surface(gfx_draw_target,param_1);
  return;
}
#undef gfx_draw_target

/* 00408780 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl
gfx_target_fill_rect(i32 param_1,i32 param_2,i32 param_3,iptr param_4,
            i32 param_5)

{
  gfx_fill_rect_xywh(gfx_draw_target,param_1,param_2,param_3,param_4,param_5);
  return;
}
#undef gfx_draw_target

/* 0040ef70 auto */
u32 __thiscall font_cached_height(GameFont *this)

{
  return this->cached_height;
}

/* 0040efa0 auto */
/* Library Function - Single Match
    public: __thiscall _Timevec::~_Timevec(void)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall font_line_spacing(GameFont *this)

{
  i32 uVar1;
  
  uVar1 = font_handle_line_spacing(this->hfont);
  return uVar1;
}

/* 0040efd0 auto */
i32 __thiscall font_text_width(GameFont *this,iptr param_1)

{
  i32 uVar1;
  
  uVar1 = font_measure_width(this->hfont,param_1);
  return uVar1;
}

/* 0040f010 auto */
DibSurface * __thiscall surface_delete(DibSurface *this,uint param_1)

{
  surface_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 0040fdb0 auto */
void __cdecl gfx_fill_rect(iptr param_1,iptr param_2,i32 param_3)

{
  iptr iVar1;
  i32 uVar2;
  
  iVar1 = rect_height(param_2);
  uVar2 = rect_width(param_2);
  gfx_fill_rect_xywh(param_1,*(i32 *)param_2,*(i32 *)(param_2 + 4),uVar2,iVar1,param_3
                    );
  return;
}

/* 00417ef0 auto */
void __thiscall font_set(GameFont *this,i32 param_1,iptr param_2)

{
  u32 uVar1;
  
  if (this->hfont != 0) {
    font_handle_destroy(this->hfont);
  }
  uVar1 = font_handle_create(param_1,param_2,0);
  this->hfont = uVar1;
  uVar1 = font_measure_height(this->hfont);
  this->cached_height = uVar1;
  return;
}

/* 00417f70 auto */
u8 __thiscall sprite_get_key_color(Sprite *this)

{
  return this->key_color;
}

/* 00418cb0 auto */
u32 __thiscall font_get_hfont(GameFont *this)

{
  return this->hfont;
}

/* 0043c460 auto */
GameFont * __thiscall
font_init(GameFont *this,i32 param_1,i32 param_2)

{
  u32 uVar1;
  
  uVar1 = font_handle_create(param_1,param_2,0);
  this->hfont = uVar1;
  uVar1 = font_measure_height(this->hfont);
  this->cached_height = uVar1;
  return this;
}

/* 0043c4c0 auto */
GameFont * __thiscall
font_init_styled
          (GameFont *this,i32 param_1,i32 param_2,i32 param_3)

{
  u32 uVar1;
  
  uVar1 = font_handle_create(param_1,param_2,param_3);
  this->hfont = uVar1;
  uVar1 = font_measure_height(this->hfont);
  this->cached_height = uVar1;
  return this;
}

/* 0043c520 auto */
GameFont * __thiscall font_destroy(GameFont *this)

{
  if (this->hfont != 0) {
    this = (GameFont *)font_handle_destroy(this->hfont);
  }
  return this;
}

/* 0043c560 auto */
/* Library Function - Single Match
    public: class CView * __thiscall COleClientItem::GetActiveView(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall surface_height(DibSurface *this)

{
  return this->pixel_height;
}

/* 0043c590 auto */
/* Library Function - Single Match
    public: class CView * __thiscall COleClientItem::GetActiveView(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall surface_width(DibSurface *this)

{
  return this->pixel_width;
}

/* 0043c690 auto */
GameFont * __thiscall font_init_empty(GameFont *this)

{
  this->hfont = 0;
  return this;
}

/* 0043c6c0 auto */
void __thiscall
font_set_styled
          (GameFont *this,i32 param_1,i32 param_2,i32 param_3)

{
  u32 uVar1;
  
  if (this->hfont != 0) {
    font_handle_destroy(this->hfont);
  }
  uVar1 = font_handle_create(param_1,param_2,param_3);
  this->hfont = uVar1;
  uVar1 = font_measure_height(this->hfont);
  this->cached_height = uVar1;
  return;
}

/* 0043c740 auto */
GamePalette * __thiscall palette_scalar_dtor(GamePalette *this,uint param_1)

{
  palette_destroy(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 0043c790 auto */
void __cdecl rect_offset(iptr param_1,int param_2,int param_3)

{
  OffsetRect((LPRECT)param_1,param_2,param_3);
  return;
}

/* 0043c7c0 auto */
void __cdecl gfx_draw_rect_frame(iptr param_1,iptr param_2,i32 param_3)

{
  gfx_draw_box_ltrb(param_1,*(i32 *)param_2,*(i32 *)(param_2 + 4),
                     *(int *)(param_2 + 8) - 1,*(int *)(param_2 + 0xc) - 1,param_3);
  return;
}

/* 0043c8d0 auto */
i32 __cdecl gfx_draw_text(iptr param_1,i32 param_2,iptr param_3)

{
  i32 uVar1;
  
  uVar1 = text_draw_shadowed(text_draw_surface,param_1,param_2,param_3);
  return uVar1;
}

/* 0043c910 auto */
void __cdecl gfx_draw_text_centered(iptr param_1,i32 param_2,iptr param_3,i32 param_4)

{
  text_draw_centered(text_draw_surface,param_1,param_2,param_3,param_4);
  return;
}

/* 0043c950 auto */
i32 __cdecl
gfx_draw_text_right(iptr param_1,i32 param_2,i32 param_3,i32 param_4)

{
  i32 uVar1;
  
  uVar1 = text_draw_right_aligned(text_draw_surface,param_1,param_2,param_3,param_4);
  return uVar1;
}

/* 0043cbb0 auto */
Sprite * __thiscall sprite_scalar_dtor(Sprite *this,uint param_1)

{
  sprite_destroy(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00447f40 auto */
void __cdecl sprite_editor_tool_sprites_global_init(void)

{
  sprite_editor_tool_sprites_static_init();
  sprite_editor_tool_sprites_reg_atexit();
  return;
}

/* 00447f5a auto */
void __cdecl sprite_editor_tool_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&sprite_editor_tool_sprites,0x3c,0xf,sprite_init,sprite_destroy);
  return;
}

/* 00447f82 auto */
void __cdecl sprite_editor_tool_sprites_reg_atexit(void)

{
  _atexit(sprite_editor_tool_sprites_static_dtor);
  return;
}

/* 00447f9f auto */
void __cdecl sprite_editor_tool_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&sprite_editor_tool_sprites,0x3c,0xf,sprite_destroy);
  return;
}

/* 004483f8 auto */
void __cdecl small_citizen_sprites_global_init(void)

{
  small_citizen_sprites_static_init();
  small_citizen_sprites_reg_atexit();
  return;
}

/* 00448412 auto */
void __cdecl small_citizen_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&small_citizen_sprites,0x3c,0xb,sprite_init,sprite_destroy);
  return;
}

/* 0044843a auto */
void __cdecl small_citizen_sprites_reg_atexit(void)

{
  _atexit(small_citizen_sprites_static_dtor);
  return;
}

/* 00448457 auto */
void __cdecl small_citizen_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&small_citizen_sprites,0x3c,0xb,sprite_destroy);
  return;
}

/* 0044857e auto */
void __cdecl small_resource_icon_sprites_global_init(void)

{
  small_resource_icon_sprites_static_init();
  small_resource_icon_sprites_reg_atexit();
  return;
}

/* 00448598 auto */
void __cdecl small_resource_icon_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&small_resource_icon_sprites,0x3c,3,sprite_init,sprite_destroy);
  return;
}

/* 004485c0 auto */
void __cdecl small_resource_icon_sprites_reg_atexit(void)

{
  _atexit(small_resource_icon_sprites_static_dtor);
  return;
}

/* 004485dd auto */
void __cdecl small_resource_icon_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&small_resource_icon_sprites,0x3c,3,sprite_destroy);
  return;
}

/* 00448682 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl small_unhappy_icon_sprite_global_init(void)

{
  small_unhappy_icon_sprite_static_init();
  small_unhappy_icon_sprite_reg_atexit();
  return;
}

/* 0044869c auto */
void __cdecl small_unhappy_icon_sprite_static_init(void)

{
  sprite_init((Sprite *)&small_unhappy_icon_sprite);
  return;
}

/* 004486b6 auto */
void __cdecl small_unhappy_icon_sprite_reg_atexit(void)

{
  _atexit(small_unhappy_icon_sprite_static_dtor);
  return;
}

/* 004486d3 auto */
void __cdecl small_unhappy_icon_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&small_unhappy_icon_sprite);
  return;
}

/* 0044885c auto */
void __cdecl icon_misc_sprites_global_init(void)

{
  icon_misc_sprites_static_init();
  icon_misc_sprites_reg_atexit();
  return;
}

/* 00448876 auto */
void __cdecl icon_misc_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&icon_misc_sprites,0x3c,6,sprite_init,sprite_destroy);
  return;
}

/* 0044889e auto */
void __cdecl icon_misc_sprites_reg_atexit(void)

{
  _atexit(icon_misc_sprites_static_dtor);
  return;
}

/* 004488bb auto */
void __cdecl icon_misc_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&icon_misc_sprites,0x3c,6,sprite_destroy);
  return;
}

/* 004488de auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl icons_unused_tall_sprite_global_init(void)

{
  icons_unused_tall_sprite_static_init();
  icons_unused_tall_sprite_reg_atexit();
  return;
}

/* 004488f8 auto */
void __cdecl icons_unused_tall_sprite_static_init(void)

{
  sprite_init((Sprite *)&icons_unused_tall_sprite);
  return;
}

/* 00448912 auto */
void __cdecl icons_unused_tall_sprite_reg_atexit(void)

{
  _atexit(icons_unused_tall_sprite_static_dtor);
  return;
}

/* 0044892f auto */
void __cdecl icons_unused_tall_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&icons_unused_tall_sprite);
  return;
}

/* 00448b3a auto */
void __cdecl icons_pair_sprites_global_init(void)

{
  icons_pair_sprites_static_init();
  icons_pair_sprites_reg_atexit();
  return;
}

/* 00448b54 auto */
void __cdecl icons_pair_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&icons_pair_sprites,0x3c,4,sprite_init,sprite_destroy);
  return;
}

/* 00448b7c auto */
void __cdecl icons_pair_sprites_reg_atexit(void)

{
  _atexit(icons_pair_sprites_static_dtor);
  return;
}

/* 00448b99 auto */
void __cdecl icons_pair_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&icons_pair_sprites,0x3c,4,sprite_destroy);
  return;
}

/* 00448f27 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl gfx_sheet_surface_global_init(void)

{
  gfx_sheet_surface_static_init();
  gfx_sheet_surface_reg_atexit();
  return;
}

/* 00448f41 auto */
void __cdecl gfx_sheet_surface_static_init(void)

{
  surface_ctor((DibSurface *)&gfx_sheet_surface);
  return;
}

/* 00448f5b auto */
void __cdecl gfx_sheet_surface_reg_atexit(void)

{
  _atexit(gfx_sheet_surface_static_dtor);
  return;
}

/* 00448f78 auto */
void __cdecl gfx_sheet_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)&gfx_sheet_surface);
  return;
}

/* 00449030 auto */
#define local_f0 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_e0 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_c0 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_ac (*(Sprite *)(frame_ + FRAME_OFF(68)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_68 (*(i32 *)(frame_ + FRAME_OFF(136)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(140)))
#define local_60 (*(i32 *)(frame_ + FRAME_OFF(144)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(148)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(156)))
#define local_50 (*(uint *)(frame_ + FRAME_OFF(160)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(164)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(224)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(228)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(232)))
void __cdecl gfx_load_terrain_sprites(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(240)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  sprite_init(&local_4c);
  local_8 = 0;
  sprite_init(&local_ac);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  __chdir(&scenario_dir_path);
  iVar1 = gfx_load_bmp_640x480(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x6266e0, ((u8 *)&g.d_006266e0)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 == 0) {
    iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x6266f0, ((u8 *)&g.d_006266f0)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    if (iVar1 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x626700, ((u8 *)&g.d_00626700)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_5c = 1;
  local_60 = 0x83;
  local_68 = 0xc4;
  local_64 = 1;
  for (local_54 = 0; local_54 < 0xb; local_54++) {
    sprite_free((Sprite *)(&terrain_base_sprites + local_54 * 0x3c));
    sprite_free((Sprite *)(&terrain_resource_sprites + local_54 * 0x78));
    sprite_free((Sprite *)(&terrain_resource2_sprites + local_54 * 0x78));
    sprite_grab_tile_cell((iptr)(&terrain_base_sprites + local_54 * 0x3c),local_5c,local_64);
    sprite_grab_tile_cell((iptr)(&terrain_resource_sprites + local_54 * 0x78),local_60,local_64);
    sprite_grab_tile_cell((iptr)(&terrain_resource2_sprites + local_54 * 0x78),local_68,local_64);
    local_64 += 0x21;
  }
  local_5c = 0x1c8;
  local_64 = 100;
  for (local_50 = 0; (int)local_50 < 3; local_50++) {
    sprite_free((Sprite *)(&land_improvement_sprites + local_50 * 0x3c));
    sprite_grab_tile_cell((iptr)(&land_improvement_sprites + local_50 * 0x3c),local_5c,local_64);
    local_64 += 0x21;
  }
  sprite_free((Sprite *)&pollution_sprite);
  sprite_grab_tile_cell(ADDR(0x641808, ((u8 *)&g.d_00641808)),local_5c,local_64);
  local_64 += 0x21;
  sprite_free((Sprite *)&grassland_shield_sprite);
  sprite_grab_tile_cell(ADDR(0x63fc18, ((u8 *)&g.d_0063fc18)),local_5c,local_64);
  local_64 += 0x21;
  sprite_free((Sprite *)&hut_sprite);
  sprite_grab_tile_cell(ADDR(0x646158, ((u8 *)&g.d_00646158)),local_5c,local_64);
  local_64 = 0x16c;
  local_5c = 1;
  for (local_50 = 0; (int)local_50 < 9; local_50++) {
    sprite_free((Sprite *)(&road_sprites + local_50 * 0x3c));
    sprite_free((Sprite *)(&railroad_sprites + local_50 * 0x3c));
    sprite_grab_tile_cell((iptr)(&road_sprites + local_50 * 0x3c),local_5c,local_64);
    sprite_grab_tile_cell((iptr)(&railroad_sprites + local_50 * 0x3c),local_5c,local_64 + 0x21);
    local_5c += 0x41;
  }
  sprite_free(&local_4c);
  sprite_grab_tile_cell((iptr)&local_4c,1,0x1bf);
  sprite_free((Sprite *)&tile_pick_mask_sprite);
  sprite_grab_tile_cell(ADDR(0x63fcd8, ((u8 *)&g.d_0063fcd8)),0x42,0x1bf);
  sprite_free((Sprite *)&unexplored_tile_sprite);
  sprite_grab_tile_cell(ADDR(0x646118, ((u8 *)&g.d_00646118)),0x83,0x1bf);
  sprite_free((Sprite *)&tile_direction_mask_sprite);
  sprite_grab_tile_cell(ADDR(0x647ed8, ((u8 *)&g.d_00647ed8)),0x105,0x1bf);
  sprite_free(&local_ac);
  sprite_grab_tile_cell((iptr)&local_ac,0xc4,0x1bf);
  for (local_54 = 0; local_54 < 0xd; local_54++) {
    gfx_fill_rect_xywh(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),0,0,0x40,0x20,7);
    if (local_54 < 0xb) {
      sprite_draw
                ((Sprite *)(&terrain_base_sprites + local_54 * 0x3c),(iptr)local_c0,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),0,0);
    }
    else if (local_54 == 0xb) {
      sprite_draw((Sprite *)&unexplored_tile_sprite,(iptr)local_d0,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),0,0);
    }
    else {
      sprite_draw(&local_ac,(iptr)local_e0,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),0,0);
    }
    sprite_draw_keyed(&local_4c,(iptr)local_f0,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),10,0,0);
    for (local_6c = 0; local_6c < 4; local_6c++) {
      if (local_6c < 2) {
        local_5c = 0x20;
      }
      else {
        local_5c = 0;
      }
      if ((local_6c < 1) || (2 < local_6c)) {
        local_64 = 0;
      }
      else {
        local_64 = 0x10;
      }
      sprite_free
                ((Sprite *)(&terrain_dither_sprites + local_6c * 0x3c + local_54 * 0xf0));
      sprite_grab_from_sheet((iptr)(&terrain_dither_sprites + local_54 * 0xf0 + local_6c * 0x3c),local_5c,local_64,0x20,
                   0x10);
    }
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  iVar1 = gfx_load_bmp_640x480(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x626710, ((u8 *)&g.d_00626710)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 == 0) {
    iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x626720, ((u8 *)&g.d_00626720)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    if (iVar1 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x626730, ((u8 *)&g.d_00626730)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_58 = 1;
  local_70 = 0x43;
  for (local_50 = 0; (int)local_50 < 0x10; local_50++) {
    local_5c = (local_50 & 7) * 0x41;
    local_64 = ((int)local_50 >> 3) * 0x21;
    sprite_free((Sprite *)(&river_sprites + local_50 * 0x3c));
    sprite_free((Sprite *)(&forest_sprites + local_50 * 0x3c));
    sprite_free((Sprite *)(&mountain_sprites + local_50 * 0x3c));
    sprite_free((Sprite *)(&hill_sprites + local_50 * 0x3c));
    sprite_grab_tile_cell((iptr)(&river_sprites + local_50 * 0x3c),local_58 + local_5c,local_70 + local_64);
    sprite_grab_tile_cell((iptr)(&forest_sprites + local_50 * 0x3c),local_58 + local_5c,
                 local_70 + local_64 + 0x42);
    sprite_grab_tile_cell((iptr)(&mountain_sprites + local_50 * 0x3c),local_58 + local_5c,
                 local_70 + local_64 + 0x84);
    sprite_grab_tile_cell((iptr)(&hill_sprites + local_50 * 0x3c),local_58 + local_5c,
                 local_70 + local_64 + 0xc6);
  }
  local_58 = 1;
  local_70 = 0x1ad;
  for (local_b0 = 0; local_b0 < 8; local_b0++) {
    sprite_free((Sprite *)(&coast_quarter_sprites + local_b0 * 0xf0));
    sprite_free((Sprite *)(&coast_quarter_east_sprites + local_b0 * 0xf0));
    sprite_free((Sprite *)(&coast_quarter_south_sprites + local_b0 * 0xf0));
    sprite_free((Sprite *)(&coast_quarter_west_sprites + local_b0 * 0xf0));
    sprite_grab_from_sheet((iptr)(&coast_quarter_sprites + local_b0 * 0xf0),local_58,local_70,0x20,0x10);
    sprite_grab_from_sheet((iptr)(&coast_quarter_east_sprites + local_b0 * 0xf0),local_58 + 0x21,local_70 + 0x22,0x20,0x10);
    sprite_grab_from_sheet((iptr)(&coast_quarter_south_sprites + local_b0 * 0xf0),local_58,local_70 + 0x11,0x20,0x10);
    sprite_grab_from_sheet((iptr)(&coast_quarter_west_sprites + local_b0 * 0xf0),local_58,local_70 + 0x22,0x20,0x10);
    local_58 += 0x42;
  }
  local_58 = 1;
  local_70 = 0x14b;
  for (local_50 = 0; (int)local_50 < 4; local_50++) {
    sprite_free((Sprite *)(&river_mouth_sprites + local_50 * 0x3c));
    sprite_grab_tile_cell((iptr)(&river_mouth_sprites + local_50 * 0x3c),local_58,local_70);
    local_58 += 0x41;
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet 0044996f */ { sprite_destroy((Sprite *)((iptr)&local_ac)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044997b */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  return;
}
#undef local_f0
#undef local_e0
#undef local_d0
#undef local_c0
#undef local_b0
#undef local_ac
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
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044999c auto */
void __cdecl sprite_grab_tile_cell(iptr param_1,i32 param_2,i32 param_3)

{
  sprite_grab_from_surface((Sprite *)param_1,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),7,param_2,param_3,0x40,0x20);
  sprite_replace_color((Sprite *)param_1,9,7);
  return;
}

/* 004499d3 auto */
void __cdecl
sprite_grab_from_sheet(iptr param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5)

{
  sprite_grab_from_surface((Sprite *)param_1,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),7,param_2,param_3,param_4,param_5);
  sprite_replace_color((Sprite *)param_1,9,7);
  return;
}

/* 00449a0e auto */
#define dlg_client_tile_surface (*(i8 * *)((u8 *)&g.d_00635aa4))
#define local_46c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_464 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_45c (*(GamePalette *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(1096)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(1100)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(1104)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(1108)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1112)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1116)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1120)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1124)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1128)))
void __cdecl gfx_load_icon_sprites(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_45c);
  local_8 = 0;
  __chdir(&scenario_dir_path);
  iVar1 = surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x55,10,0xc0,(iptr)&local_45c);
  if (iVar1 == 0) {
    __chdir(&game_home_dir);
    surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x55,10,0xc0,(iptr)&local_45c);
  }
  __chdir(&game_home_dir);
  local_20 = 1;
  local_24 = 1;
  local_460 = 0;
  for (local_18 = 0; local_18 < 0xb; local_18++) {
    sprite_free((Sprite *)(&nuke_anim_sprites + local_18 * 0x3c));
    sprite_grab_from_sheet((iptr)(&nuke_anim_sprites + local_18 * 0x3c),local_20,local_24,0x5b,0x48);
    local_20 += 0x5c;
    local_460++;
    if (local_460 == 6) {
      local_20 = 1;
      local_24 += 0x49;
    }
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  iVar1 = gfx_load_bmp_640x480(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x626740, ((u8 *)&g.d_00626740)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 == 0) {
    iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x62674c, ((u8 *)&g.d_0062674c)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    if (iVar1 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x626758, ((u8 *)&g.d_00626758)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  sprite_free((Sprite *)&map_cursor_sprite);
  sprite_free((Sprite *)&map_grid_sprite);
  sprite_free((Sprite *)&city_radius_grid_sprite);
  sprite_grab_tile_cell(ADDR(0x640b98, ((u8 *)&g.d_00640b98)),199,0x100);
  sprite_grab_tile_cell(ADDR(0x646198, ((u8 *)&g.d_00646198)),199,0x121);
  sprite_grab_tile_cell(ADDR(0x647bc8, ((u8 *)&g.d_00647bc8)),0xf8,0x1ae);
  sprite_free((Sprite *)&fortify_overlay_alt_sprite);
  gfx_grab_fortify_overlay(1,0x20,0xbb);
  sprite_free((Sprite *)&icon_sprite_6);
  sprite_grab_icon_cell_keyed(ADDR(0x64668c, ((u8 *)&g.d_0064668c)),0x22,0xdf);
  sprite_free((Sprite *)&pollution_icon_sprite);
  sprite_grab_from_sheet(ADDR(0x6466c8, ((u8 *)&g.d_006466c8)),0x43,0xdf,0x20,0x20);
  sprite_free((Sprite *)&icon_sprite_7);
  sprite_free((Sprite *)&icon_sprite_8);
  sprite_free((Sprite *)&city_disorder_icon_sprite);
  sprite_grab_icon_cell_keyed(ADDR(0x646704, ((u8 *)&g.d_00646704)),100,0xdf);
  sprite_grab_icon_cell_keyed(ADDR(0x646740, ((u8 *)&g.d_00646740)),0x85,0xdf);
  sprite_grab_from_sheet(ADDR(0x64677c, ((u8 *)&g.d_0064677c)),0xa6,0xdf,0x1e,0x1e);
  sprite_free((Sprite *)&icon_misc_sprites);
  sprite_free((Sprite *)&icon_sprite_1);
  sprite_free((Sprite *)&icon_sprite_4);
  sprite_free((Sprite *)&icon_sprite_5);
  sprite_grab_icon_cell_keyed(ADDR(0x63f6f0, ((u8 *)&g.d_0063f6f0)),199,0x100);
  sprite_grab_icon_cell_keyed(ADDR(0x63f72c, ((u8 *)&g.d_0063f72c)),0xe8,0x100);
  sprite_grab_icon_cell_keyed(ADDR(0x63f7e0, ((u8 *)&g.d_0063f7e0)),0x109,0x100);
  sprite_grab_icon_cell_keyed(ADDR(0x63f81c, ((u8 *)&g.d_0063f81c)),0x12a,0x100);
  sprite_free((Sprite *)&icon_sprite_2);
  sprite_free((Sprite *)&icon_sprite_3);
  sprite_free((Sprite *)&icons_unused_tall_sprite);
  sprite_grab_from_sheet(ADDR(0x63f768, ((u8 *)&g.d_0063f768)),0x137,1,0x1f,0x60);
  sprite_grab_from_sheet(ADDR(0x63f7a4, ((u8 *)&g.d_0063f7a4)),0x137,0x62,0x1f,0x60);
  sprite_grab_from_sheet(ADDR(0x648098, ((u8 *)&g.d_00648098)),0x109,0x121,0x38,0x83);
  local_20 = 1;
  local_24 = 0x122;
  for (local_18 = 0; local_18 < 3; local_18++) {
    for (local_28 = 0; local_28 < 2; local_28++) {
      sprite_free((Sprite *)(&resource_shortage_icon_sprites + local_18 * 0x78));
      sprite_free((Sprite *)(&resource_icon_sprites + local_18 * 0x78));
      sprite_grab_square((iptr)(&resource_shortage_icon_sprites + local_18 * 0x78),local_20,local_24,0xe);
      sprite_grab_square((iptr)(&resource_icon_sprites + local_18 * 0x78),local_20,local_24 + 0xf,0xe);
    }
    local_20 += 0xf;
  }
  local_20 = 1;
  local_24 = 0x140;
  for (local_18 = 0; local_18 < 3; local_18++) {
    sprite_free((Sprite *)(&tax_rate_icon_sprites + local_18 * 0x3c));
    sprite_grab_square((iptr)(&tax_rate_icon_sprites + local_18 * 0x3c),local_20,local_24,0xe);
    local_20 += 0xf;
  }
  local_20 = 0x31;
  local_24 = 0x14e;
  for (local_18 = 0; local_18 < 3; local_18++) {
    sprite_free((Sprite *)(&small_resource_icon_sprites + local_18 * 0x3c));
    sprite_grab_square((iptr)(&small_resource_icon_sprites + local_18 * 0x3c),local_20,local_24,10);
    local_20 += 0xb;
  }
  local_20 = 0x31;
  local_24 = 0x159;
  for (local_18 = 0; local_18 < 3; local_18++) {
    sprite_free((Sprite *)(&lux_tax_sci_icon_sprites + local_18 * 0x3c));
    sprite_grab_square((iptr)(&lux_tax_sci_icon_sprites + local_18 * 0x3c),local_20,local_24,10);
    local_20 += 0xb;
  }
  sprite_free((Sprite *)&small_unhappy_icon_sprite);
  sprite_free((Sprite *)&unhappy_suppressed_icon_sprite);
  sprite_grab_square(ADDR(0x646598, ((u8 *)&g.d_00646598)),0x52,0x14e,10);
  sprite_grab_square(ADDR(0x648058, ((u8 *)&g.d_00648058)),0x52,0x159,10);
  local_20 = 0x31;
  local_24 = 0x122;
  for (local_18 = 0; local_18 < 4; local_18++) {
    sprite_free((Sprite *)(&research_flask_sprites + local_18 * 0x3c));
    sprite_free((Sprite *)(&global_warming_sprites + local_18 * 0x3c));
    sprite_grab_square((iptr)(&research_flask_sprites + local_18 * 0x3c),local_20,local_24,0xe);
    sprite_grab_square((iptr)(&global_warming_sprites + local_18 * 0x3c),local_20,0x131,0xe);
    local_20 += 0xf;
  }
  local_20 = 1;
  local_24 = 0x164;
  for (local_18 = 0; local_18 < 8; local_18++) {
    sprite_free((Sprite *)(&explosion_sprites + local_18 * 0x3c));
    sprite_grab_from_sheet((iptr)(&explosion_sprites + local_18 * 0x3c),local_20,local_24,0x20,0x20);
    local_20 += 0x21;
  }
  surface_create((DibSurface *)&window_border_tile_surface,0x40,0x20);
  gfx_copy_rect_xywh(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x647f18, ((u8 *)&g.d_00647f18)),199,0x142,0,0,0x40,0x20);
  dialog_set_frame_tile_surface(ADDR(0x647f18, ((u8 *)&g.d_00647f18)));
  frame_set_border_tile(ADDR(0x647f18, ((u8 *)&g.d_00647f18)));
  surface_create((DibSurface *)&panel_texture_surface,0x20,0x20);
  gfx_copy_rect_xywh(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x640990, ((u8 *)&g.d_00640990)),0x12a,0xbe,0,0,0x20,0x20);
  dlg_client_tile_surface = &panel_texture_surface;
  local_20 = 0x157;
  local_24 = 1;
  local_464 = 0;
  for (local_18 = 1; local_18 < 0x27; local_18++) {
    sprite_free((Sprite *)(&improvement_icon_sprites + local_18 * 0x3c));
    sprite_grab_from_sheet((iptr)(&improvement_icon_sprites + local_18 * 0x3c),local_20,local_24,0x24,0x14);
    local_20 += 0x25;
    local_464++;
    if (7 < local_464) {
      local_464 = 0;
      local_24 += 0x15;
      local_20 = 0x157;
    }
  }
  local_20 = 0x157;
  local_24 = 0x6a;
  local_464 = 0;
  for (local_18 = 0; local_18 < 0x1c; local_18++) {
    sprite_free((Sprite *)(&wonder_icon_sprites + local_18 * 0x3c));
    sprite_grab_from_sheet((iptr)(&wonder_icon_sprites + local_18 * 0x3c),local_20,local_24,0x24,0x14);
    local_20 += 0x25;
    local_464++;
    if (6 < local_464) {
      local_464 = 0;
      local_24 += 0x15;
      local_20 = 0x157;
    }
  }
  local_24 = 0xd3;
  for (local_18 = 0; local_18 < 4; local_18++) {
    local_20 = 0x157;
    for (local_1c = 0; local_1c < 5; local_1c++) {
      sprite_free
                ((Sprite *)(&advance_category_icon_sprites + local_1c * 0xf0 + local_18 * 0x3c));
      sprite_grab_from_sheet((iptr)(&advance_category_icon_sprites + local_18 * 0x3c + local_1c * 0xf0),local_20,local_24,0x24,
                   0x14);
      local_20 += 0x25;
    }
    local_24 += 0x15;
  }
  sprite_free((Sprite *)&icons_pair_sprites);
  sprite_free((Sprite *)&icon_sprite_9);
  sprite_grab_from_sheet(ADDR(0x647b50, ((u8 *)&g.d_00647b50)),0x15e,0xff,0x40,0x20);
  sprite_grab_from_sheet(ADDR(0x647b8c, ((u8 *)&g.d_00647b8c)),0x15e,0x120,0x40,0x20);
  sprite_free((Sprite *)&caption_close_button_sprite);
  sprite_free((Sprite *)&caption_zoom_out_sprite);
  sprite_free((Sprite *)&caption_zoom_out_button_sprite);
  sprite_free((Sprite *)&caption_view_mode_button_sprite);
  sprite_grab_from_sheet(ADDR(0x645120, ((u8 *)&g.d_00645120)),1,0x185,0x10,0x10);
  sprite_grab_from_sheet(ADDR(0x648820, ((u8 *)&g.d_00648820)),0x12,0x185,0x10,0x10);
  sprite_grab_from_sheet(ADDR(0x647788, ((u8 *)&g.d_00647788)),0x23,0x185,0x10,0x10);
  sprite_grab_from_sheet(ADDR(0x647348, ((u8 *)&g.d_00647348)),0x34,0x185,0x10,0x10);
  sprite_free((Sprite *)&scroll_up_button_sprite);
  sprite_free((Sprite *)&city_down_arrow_sprite);
  sprite_grab_from_sheet(ADDR(0x644770, ((u8 *)&g.d_00644770)),0xe3,0x185,0x12,0x18);
  sprite_grab_from_sheet(ADDR(0x6480d8, ((u8 *)&g.d_006480d8)),0xf6,0x185,0x12,0x18);
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&game_home_dir);
  iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x626764, ((u8 *)&g.d_00626764)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 != 0) {
    local_20 = 1;
    local_24 = 0x1bf;
    for (local_18 = 0; local_18 < 0xf; local_18++) {
      sprite_free((Sprite *)(&sprite_editor_tool_sprites + local_18 * 0x3c));
      sprite_grab_from_sheet((iptr)(&sprite_editor_tool_sprites + local_18 * 0x3c),local_20,local_24,0x20,0x20);
      local_20 += 0x21;
    }
  }
  sprite_free((Sprite *)&editor_unit_backdrop_sprite);
  sprite_grab_from_surface((Sprite *)&editor_unit_backdrop_sprite,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),7,0x23f,1,0x40,0x30);
  sprite_free((Sprite *)&editor_tile_backdrop_sprite);
  sprite_grab_from_surface((Sprite *)&editor_tile_backdrop_sprite,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),7,0x23f,0x32,0x40,0x20);
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  iVar1 = gfx_load_bmp_640x480(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x626774, ((u8 *)&g.d_00626774)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 == 0) {
    iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x626780, ((u8 *)&g.d_00626780)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    if (iVar1 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x62678c, ((u8 *)&g.d_0062678c)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_24 = 6;
  for (local_14 = 0; local_14 < 4; local_14++) {
    local_20 = 2;
    for (local_18 = 0; local_18 < 0xb; local_18++) {
      sprite_free
                ((Sprite *)(&citizen_sprites + local_14 * 0x294 + local_18 * 0x3c));
      sprite_grab_from_sheet((iptr)(&citizen_sprites + local_18 * 0x3c + local_14 * 0x294),local_20,local_24,0x1b
                   ,0x1e);
      local_20 += 0x1c;
    }
    local_24 += 0x1f;
  }
  local_20 = 2;
  local_24 = 0x89;
  for (local_18 = 0; local_18 < 0xb; local_18++) {
    sprite_free((Sprite *)(&small_citizen_sprites + local_18 * 0x3c));
    sprite_grab_from_sheet((iptr)(&small_citizen_sprites + local_18 * 0x3c),local_20,local_24,0xf,0x1a);
    local_20 += 0x10;
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  iVar1 = surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x56,10,0xc0,(iptr)&local_45c);
  if (iVar1 == 0) {
    __chdir(&game_home_dir);
    surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x56,10,0xc0,(iptr)&local_45c);
  }
  __chdir(&game_home_dir);
  local_20 = 2;
  local_24 = 0x44;
  sprite_free((Sprite *)&government_sprites);
  sprite_free((Sprite *)&government_despotism_sprite);
  sprite_grab_from_sheet(ADDR(0x646878, ((u8 *)&g.d_00646878)),local_20,local_24,0x22,0x22);
  sprite_grab_from_sheet(ADDR(0x6468b4, ((u8 *)&g.d_006468b4)),local_20,local_24,0x22,0x22);
  local_20 += 0x42;
  sprite_free((Sprite *)&government_sprite_communism);
  sprite_grab_from_sheet(ADDR(0x64692c, ((u8 *)&g.d_0064692c)),local_20,local_24,0x22,0x22);
  local_20 += 0x42;
  sprite_free((Sprite *)&government_sprite_fundamentalism);
  sprite_grab_from_sheet(ADDR(0x646968, ((u8 *)&g.d_00646968)),local_20,local_24,0x22,0x22);
  local_20 += 0x42;
  sprite_free((Sprite *)&government_monarchy_sprite);
  sprite_grab_from_sheet(ADDR(0x6468f0, ((u8 *)&g.d_006468f0)),local_20,local_24,0x22,0x22);
  local_20 += 0x42;
  sprite_free((Sprite *)&government_sprite_democracy);
  sprite_grab_from_sheet(ADDR(0x6469e0, ((u8 *)&g.d_006469e0)),local_20,local_24,0x22,0x22);
  local_20 += 0x42;
  sprite_free((Sprite *)&government_sprite_republic);
  sprite_grab_from_sheet(ADDR(0x6469a4, ((u8 *)&g.d_006469a4)),local_20,local_24,0x22,0x22);
  local_20 = 2;
  local_24 = 200;
  sprite_free((Sprite *)&ceasefire_icon_sprite);
  sprite_grab_from_sheet(ADDR(0x647748, ((u8 *)&g.d_00647748)),local_20,local_24,0x40,0x40);
  local_20 += 0x42;
  sprite_free((Sprite *)&peace_treaty_icon_sprite);
  sprite_grab_from_sheet(ADDR(0x6409d8, ((u8 *)&g.d_006409d8)),local_20,local_24,0x40,0x40);
  local_20 += 0x42;
  sprite_free((Sprite *)&war_icon_sprite);
  sprite_grab_from_sheet(ADDR(0x644e48, ((u8 *)&g.d_00644e48)),local_20,local_24,0x40,0x40);
  local_20 += 0x42;
  sprite_free((Sprite *)&signal_allied_icon_sprite);
  sprite_grab_from_sheet(ADDR(0x63fc98, ((u8 *)&g.d_0063fc98)),local_20,local_24,0x40,0x40);
  local_20 += 0x42;
  sprite_free((Sprite *)&diplo_popup_portrait_sprite);
  sprite_grab_from_sheet(ADDR(0x648018, ((u8 *)&g.d_00648018)),local_20,local_24,0x40,0x40);
  sprite_free((Sprite *)&popup_info_icon_sprite);
  sprite_free((Sprite *)&tutorial_icon_sprite);
  sprite_grab_from_sheet(ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0x18e,0x86,0x40,0x40);
  sprite_grab_from_sheet(ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0x86,0x18e,0x40,0x40);
  for (local_46c = 0; local_46c < 8; local_46c++) {
    sprite_free((Sprite *)(&civ_portrait_sprites + local_46c * 0x3c));
    sprite_grab_from_sheet((iptr)(&civ_portrait_sprites + local_46c * 0x3c),2,0x18e,0x40,0x40);
    sprite_replace_color
              ((Sprite *)(&civ_portrait_sprites + local_46c * 0x3c),8,
               *(i32 *)(&civ_primary_colors + local_46c * 0x10));
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044ab4e */ { palette_destroy((GamePalette *)((iptr)&local_45c)); }
  return;
}
#undef dlg_client_tile_surface
#undef local_46c
#undef local_464
#undef local_460
#undef local_45c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044ab72 auto */
void __cdecl sprite_grab_icon_cell_keyed(iptr param_1,i32 param_2,i32 param_3)

{
  sprite_grab_from_surface((Sprite *)param_1,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),7,param_2,param_3,0x20,0x20);
  sprite_replace_color((Sprite *)param_1,9,7);
  return;
}

/* 0044aba9 auto */
void __cdecl sprite_grab_square(iptr param_1,i32 param_2,i32 param_3,i32 param_4)

{
  sprite_grab_from_sheet(param_1,param_2,param_3,param_4,param_4);
  return;
}

/* 0044abd5 auto */
void __cdecl gfx_grab_fortify_overlay(int param_1,i32 param_2,i32 param_3)

{
  sprite_grab_city_cell((iptr)(&fortify_overlay_sprites + param_1 * 0x3c),param_2,param_3);
  return;
}

/* 0044ac07 auto */
void __cdecl sprite_grab_city_cell(iptr param_1,i32 param_2,i32 param_3)

{
  sprite_grab_from_surface((Sprite *)param_1,ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),7,param_2,param_3,0x40,0x30);
  sprite_replace_color((Sprite *)param_1,9,7);
  return;
}

/* 0044ae4c auto */
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl gfx_load_city_sprites(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  __chdir(&scenario_dir_path);
  iVar1 = gfx_load_bmp_640x480(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x626798, ((u8 *)&g.d_00626798)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 == 0) {
    iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x6267a4, ((u8 *)&g.d_006267a4)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    if (iVar1 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x6267b0, ((u8 *)&g.d_006267b0)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_14 = 0x27;
  for (local_28 = 0; local_28 < 6; local_28++) {
    for (local_8 = 0; local_8 < 4; local_8++) {
      sprite_free
                ((Sprite *)(&city_sprites + local_8 * 0x78 + local_28 * 0x1e0));
      sprite_free
                ((Sprite *)(&city_walled_sprites + local_8 * 0x78 + local_28 * 0x1e0));
      iVar1 = local_8 * 0x41;
      sprite_grab_city_cell((iptr)(&city_sprites + local_28 * 0x1e0 + local_8 * 0x78),iVar1 + 1,local_14);
      city_sprite_scan_flag_offset(local_28,local_8,0,iVar1 + 1,local_14);
      city_sprite_scan_size_box_offset(local_28,local_8,0,iVar1 + 1,local_14);
      sprite_grab_city_cell((iptr)(&city_walled_sprites + local_28 * 0x1e0 + local_8 * 0x78),iVar1 + 0x14e,local_14)
      ;
      city_sprite_scan_flag_offset(local_28,local_8,1,iVar1 + 0x14e,local_14);
      city_sprite_scan_size_box_offset(local_28,local_8,1,iVar1 + 0x14e,local_14);
    }
    local_14 += 0x31;
  }
  local_c = 1;
  for (local_24 = 0; local_24 < 8; local_24++) {
    sprite_free((Sprite *)(&civ_flag_sprites + local_24 * 0x78));
    sprite_free((Sprite *)(&civ_flag_dark_sprites + local_24 * 0x78));
    sprite_grab_from_sheet((iptr)(&civ_flag_sprites + local_24 * 0x78),local_c,0x1a9,0xe,0x16);
    sprite_grab_from_sheet((iptr)(&civ_flag_dark_sprites + local_24 * 0x78),local_c,0x1c0,0xe,0x16);
    uVar2 = surface_get_pixel((DibSurface *)&gfx_sheet_surface,local_c + 3,0x1ad);
    *(i32 *)(&civ_primary_colors + local_24 * 0x10) = uVar2;
    uVar2 = surface_get_pixel((DibSurface *)&gfx_sheet_surface,local_c + 6,0x1ad);
    *(i32 *)(&civ_mid_colors + local_24 * 0x10) = uVar2;
    uVar2 = surface_get_pixel((DibSurface *)&gfx_sheet_surface,local_c,0x1a7);
    *(i32 *)(&civ_secondary_colors + local_24 * 0x10) = uVar2;
    local_c += 0xf;
  }
  sprite_free((Sprite *)&fortify_overlay_sprites);
  sprite_free((Sprite *)&fortress_sprite);
  sprite_grab_city_cell(ADDR(0x6465d8, ((u8 *)&g.d_006465d8)),0x8f,0x1a7);
  sprite_grab_city_cell(ADDR(0x646650, ((u8 *)&g.d_00646650)),0xd0,0x1a7);
  sprite_free((Sprite *)&airbase_sprites);
  sprite_free((Sprite *)&airbase_occupied_sprite);
  sprite_grab_city_cell(ADDR(0x647fa0, ((u8 *)&g.d_00647fa0)),0x111,0x1a7);
  sprite_grab_city_cell(ADDR(0x647fdc, ((u8 *)&g.d_00647fdc)),0x152,0x1a7);
  surface_release((DibSurface *)&gfx_sheet_surface);
  return;
}
#undef local_28
#undef local_24
#undef local_14
#undef local_c
#undef local_8

/* 0044b30e auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_load_unit_sprites(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __chdir(&scenario_dir_path);
  iVar1 = gfx_load_bmp_640x480(ADDR(0x63fe08, ((u8 *)&g.d_0063fe08)),ADDR(0x6267bc, ((u8 *)&g.d_006267bc)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 == 0) {
    iVar1 = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x6267c8, ((u8 *)&g.d_006267c8)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    if (iVar1 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,ADDR(0x6267d4, ((u8 *)&g.d_006267d4)),10,0xc0,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_18 = 0;
  local_c = 1;
  local_8 = 1;
  for (local_14 = 0; local_14 < 0x3f; local_14++) {
    sprite_free((Sprite *)(&unit_sprites + local_14 * 0x3c));
    sprite_grab_city_cell((iptr)(&unit_sprites + local_14 * 0x3c),local_8,local_c);
    unit_sprite_scan_shield_offset(local_14,local_8,local_c);
    local_18++;
    local_8 += 0x41;
    if (8 < local_18) {
      local_18 = 0;
      local_c += 0x31;
      local_8 = 1;
    }
  }
  sprite_free((Sprite *)&unit_shield_sprite);
  sprite_grab_from_sheet(ADDR(0x647f60, ((u8 *)&g.d_00647f60)),0x24a,1,0xc,0x14);
  surface_release((DibSurface *)&gfx_sheet_surface);
  return;
}
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 0044b49e auto */
#define local_124 (*(SurfaceWindow *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(280)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(284)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(288)))
void __cdecl gfx_load_game_sprites(void)

{
  i8 frame_[FRAME_OFF(296)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor(&local_124);
  local_8 = 0;
  gfx_load_city_sprites();
  gfx_load_icon_sprites();
  gfx_load_terrain_sprites();
  gfx_load_unit_sprites();
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044b4f6 */ { surfwnd_dtor((SurfaceWindow *)((iptr)&local_124)); }
  return;
}
#undef local_124
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00451830 auto */
i32 __thiscall sprite_get_width(Sprite *this)

{
  i32 uVar1;
  
  uVar1 = rect_width((iptr)&this->bounds_rect);
  return uVar1;
}

/* 00451860 auto */
i32 __thiscall sprite_get_height(Sprite *this)

{
  i32 uVar1;
  
  uVar1 = rect_height((iptr)&this->bounds_rect);
  return uVar1;
}

/* 0046e9d0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl grey_palette_global_init(void)

{
  grey_palette_static_init();
  grey_palette_reg_atexit();
  return;
}

/* 0046e9ea auto */
void __cdecl grey_palette_static_init(void)

{
  palette_init((GamePalette *)&grey_palette);
  return;
}

/* 0046ea04 auto */
void __cdecl grey_palette_reg_atexit(void)

{
  _atexit(grey_palette_atexit_dtor);
  return;
}

/* 0046ea21 auto */
void __cdecl grey_palette_atexit_dtor(void)

{
  palette_destroy((GamePalette *)&grey_palette);
  return;
}

/* 0046ea3b auto */
#define grey_remap_handle (*(int *)((u8 *)&g.d_0066c408))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl gfx_build_grey_remap(void)

{
  int iVar1;
  iptr iVar2;
  int iVar3;
  LOGPALETTE *plpal;
  HPALETTE h;
  iptr iVar4;
  iptr iVar5;
  UINT UVar4;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = mem_handle_alloc(0x2c4);
  if (iVar1 == 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62b56c, ((u8 *)&g.d_0062b56c)),ADDR(0x62b550, ((u8 *)&g.d_0062b550)),0x22);
  }
  else {
    iVar2 = mem_handle_lock(iVar1);
    palette_get_rgb((GamePalette *)&game_palette,iVar2,10,0x20);
    iVar3 = mem_handle_alloc(0x88);
    if (iVar3 == 0) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62b59c, ((u8 *)&g.d_0062b59c)),ADDR(0x62b580, ((u8 *)&g.d_0062b580)),0x2a);
      mem_handle_unlock(iVar1);
      mem_handle_free(iVar1);
    }
    else {
      plpal = (LOGPALETTE *)mem_handle_lock(iVar3);
      plpal->palVersion = 0x300;
      plpal->palNumEntries = 0x20;
      for (local_24 = 0; local_24 < 0x60; local_24 += 3) {
        plpal->palPalEntry[local_24 / 3].peRed = *(BYTE *)(local_24 + iVar2);
        plpal->palPalEntry[local_24 / 3].peGreen = *(BYTE *)(local_24 + 1 + iVar2);
        plpal->palPalEntry[local_24 / 3].peBlue = *(BYTE *)(local_24 + 2 + iVar2);
        plpal->palPalEntry[local_24 / 3].peFlags = 4;
      }
      h = CreatePalette(plpal);
      if (h == (HPALETTE)0x0) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62b5c0, ((u8 *)&g.d_0062b5c0)),ADDR(0x62b5a4, ((u8 *)&g.d_0062b5a4)),0x3e);
        mem_handle_unlock(iVar1);
        mem_handle_free(iVar1);
      }
      else {
        mem_handle_unlock(iVar3);
        mem_handle_free(iVar3);
        iVar3 = mem_handle_alloc(0x2c4);
        if (iVar3 == 0) {
          err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62b5ec, ((u8 *)&g.d_0062b5ec)),ADDR(0x62b5d0, ((u8 *)&g.d_0062b5d0)),0x48);
          mem_handle_unlock(iVar1);
          mem_handle_free(iVar1);
        }
        else {
          iVar4 = mem_handle_lock(iVar3);
          grey_remap_handle = mem_handle_alloc(0xec);
          if (grey_remap_handle == 0) {
            err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62b618, ((u8 *)&g.d_0062b618)),ADDR(0x62b5fc, ((u8 *)&g.d_0062b5fc)),0x51);
            mem_handle_unlock(iVar1);
            mem_handle_free(iVar1);
            mem_handle_unlock(iVar3);
            mem_handle_free(iVar3);
          }
          else {
            iVar5 = mem_handle_lock(grey_remap_handle);
            palette_get_rgb((GamePalette *)&game_palette,iVar4,10,0xec);
            for (local_24 = 0; local_24 < 0x2c4; local_24 += 3) {
              UVar4 = GetNearestPaletteIndex
                                (h,(uint)CONCAT12(*(i8 *)(local_24 + 2 + iVar4),
                                                  CONCAT11(*(i8 *)(local_24 + 1 + iVar4),
                                                           *(i8 *)(local_24 + iVar4))));
              *(char *)(iVar5 + local_24 / 3) = (char)UVar4 + '\n';
              palette_set_entry
                        ((GamePalette *)&grey_palette,local_24 / 3 + 10,
                         CONCAT31((int3)(UVar4 * 3 >> 8),*(i8 *)(UVar4 * 3 + iVar2)),
                         CONCAT31((int3)(UVar4 * 3 >> 8),*(i8 *)(UVar4 * 3 + 1 + iVar2)),
                         CONCAT31((int3)(UVar4 * 3 >> 8),*(i8 *)(UVar4 * 3 + 2 + iVar2)));
            }
            DeleteObject(h);
            mem_handle_unlock(iVar3);
            mem_handle_free(iVar3);
            mem_handle_unlock(iVar1);
            mem_handle_free(iVar1);
            mem_handle_unlock(grey_remap_handle);
          }
        }
      }
    }
  }
  return;
}
#undef grey_remap_handle
#undef local_24

/* 0046ee1e auto */
#define grey_remap_handle (*(int *)((u8 *)&g.d_0066c408))
void __cdecl gfx_free_grey_remap(void)

{
  if (grey_remap_handle != 0) {
    grey_remap_handle = mem_handle_free(grey_remap_handle);
  }
  return;
}
#undef grey_remap_handle

/* 0046ee4e auto */
#define grey_remap_handle (*(i32 *)((u8 *)&g.d_0066c408))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl gfx_grey_out_windows(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = mem_handle_lock(grey_remap_handle);
  if (iVar1 != 0) {
    for (local_c = 0; local_c < 8; local_c++) {
      if ((local_c == 0) || (*(short *)(&map_view_open_flags + local_c * 0x3f0) != 0)) {
        surface_remap_colors
                  ((DibSurface *)(&map_views + local_c * 0x3f0),iVar1,10,0xec);
      }
    }
    surface_remap_colors((DibSurface *)&status_window,iVar1,10,0xec);
    surface_remap_colors((DibSurface *)&minimap_window,iVar1,10,0xec);
    surface_remap_colors((DibSurface *)&city_window,iVar1,10,0xec);
    mem_handle_unlock(grey_remap_handle);
    ui_blit_all_windows();
  }
  return;
}
#undef grey_remap_handle
#undef local_c

/* 0046ef3f auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl gfx_repaint_main_windows(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      wnd_repaint((SurfaceWindow *)(&map_views + local_8 * 0x3f0));
    }
  }
  wnd_repaint((SurfaceWindow *)&minimap_window);
  wnd_repaint((SurfaceWindow *)&status_window);
  wnd_repaint((SurfaceWindow *)&city_window);
  wnd_flush_paint();
  return;
}
#undef local_8

/* 0046efd6 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl screen_fade_out(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  if (gfx_palettized_display != 0) {
    palette_fade_begin((GamePalette *)&game_palette,10,0xec,10,ADDR(0x66bfd0, ((u8 *)&g.d_0066bfd0)));
    ui_blit_all_windows();
    local_8 = 10;
    while (-1 < local_8) {
      palette_fade_step((GamePalette *)&game_palette,local_8);
      ui_delay_ticks(1);
      local_8--;
    }
    palette_set_nocollapse_all();
    gfx_grey_out_windows();
    palette_fade_end((GamePalette *)&game_palette);
    palette_set_nocollapse_all();
  }
  return;
}
#undef unit_blink_active
#undef local_8

/* 0046f06f auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl screen_fade_in(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (gfx_palettized_display != 0) {
    palette_fade_begin((GamePalette *)&game_palette,10,0xec,10,ADDR(0x66bfd0, ((u8 *)&g.d_0066bfd0)));
    palette_fade_step((GamePalette *)&game_palette,0);
    gfx_repaint_main_windows();
    ui_blit_all_windows();
    local_8 = 0;
    while (local_8 < 0xb) {
      palette_fade_step((GamePalette *)&game_palette,local_8);
      ui_delay_ticks(1);
      local_8++;
    }
    palette_fade_end((GamePalette *)&game_palette);
    palette_set_nocollapse_all();
  }
  return;
}
#undef local_8

/* 0046f108 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl palette_set_nocollapse_all(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = palette_get_logpalette((GamePalette *)&game_palette);
  if (iVar1 == 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62b640, ((u8 *)&g.d_0062b640)),ADDR(0x62b624, ((u8 *)&g.d_0062b624)),0xbc);
  }
  for (local_c = 0; local_c < 0x100; local_c++) {
    *(i8 *)(iVar1 + 7 + local_c * 4) = 4;
  }
  palette_commit_range((GamePalette *)&game_palette,10,0xec);
  return;
}
#undef local_c

/* 0046f440 auto */
GamePalette * __thiscall palette_get_logpalette(GamePalette *this)

{
  return this;
}

/* 0046f460 auto */
#define local_468 (*(char *)(frame_ + FRAME_OFF(0)))
#define local_464 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_45c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_456 (*(short *)(frame_ + FRAME_OFF(18)))
#define local_454 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_444 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_43c (*(FILE * *)(frame_ + FRAME_OFF(44)))
#define local_438 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_434 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_430 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_42c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_428 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_424 (*(uint *)(frame_ + FRAME_OFF(68)))
#define local_420 (*(char * *)(frame_ + FRAME_OFF(72)))
#define local_41c (*(uint (*)[4])(frame_ + FRAME_OFF(76)))
#define local_40c (*(uint *)(frame_ + FRAME_OFF(92)))
#define local_408 (*(char * *)(frame_ + FRAME_OFF(96)))
#define local_404 (*(i8 (*)[2])(frame_ + FRAME_OFF(100)))
#define auStack_402 (*(i32 (*)[255])(frame_ + FRAME_OFF(102)))
int __cdecl gfx_load_bmp_640x480(iptr param_1,iptr param_2,int param_3,int param_4,iptr param_5)

{
  char cVar1;
  size_t sVar2;
  iptr iVar3;
  int iVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(1128)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_408 = &gfx_load_bmp_no_error_str;
  local_438 = 0;
  local_43c = __fsopen((char *)param_2,&gfx_bmp_read_mode,0x40);
  if (local_43c == (FILE *)0x0) {
    local_438 = 0;
  }
  else {
    sVar2 = _fread(local_41c,0xe,1,local_43c);
    if (sVar2 == 0) {
      local_408 = s_Error_reading_file_header_0062b67c;
    }
    else if ((local_41c[0] & 0xffff) == 0x4d42) {
      sVar2 = _fread(&local_464,4,1,local_43c);
      if ((sVar2 == 0) || (sVar2 = _fread(&local_460,local_464 - 4,1,local_43c), sVar2 == 0)) {
        local_408 = s_Error_reading_info_header_0062b6ac;
      }
      else {
        sVar2 = _fread(local_404,0x400,1,local_43c);
        if (sVar2 == 0) {
          local_408 = s_Error_reading_file_palette_0062b6c8;
        }
        else if (((local_460 == 0x280) && (local_45c == 0x1e0)) && (local_456 == 8)) {
          local_438 = 1;
          if (param_5 != 0) {
            iVar4 = param_4;
            if ((local_444 != 0) && (iVar4 = local_444, param_4 <= local_444)) {
              iVar4 = param_4;
            }
            param_4 = iVar4;
            if (0x100 < param_4 + param_3) {
              param_4 = 0x100 - param_3;
            }
            local_434 = 0;
            for (local_430 = param_3; local_430 < param_4 + param_3; local_430++) {
              uVar7 = *(i32 *)(local_404 + local_434 * 4);
              uVar6 = *(i32 *)(local_404 + local_434 * 4 + 1);
              uVar5 = *(i32 *)(local_404 + local_434 * 4 + 2);
              iVar4 = local_430;
              iVar3 = palette_get_logpalette((GamePalette *)param_5);
              palette_set_entry_rgb(iVar3,iVar4,uVar5,uVar6,uVar7);
              local_434++;
            }
            palette_commit_range((GamePalette *)param_5,param_3,param_4);
          }
          surface_create((DibSurface *)param_1,local_460,local_45c);
          cVar1 = (char)param_3;
          if (local_454 == 0) {
            do {
              local_42c = local_45c - 1;
              if ((local_42c < 0) || (local_438 == 0)) goto LAB_0046fbb4;
              local_420 = (char *)surface_pixel_ptr((DibSurface *)param_1,0,local_42c);
              for (local_428 = 0; local_45c = local_42c, local_428 < local_460;
                  local_428 = local_428 + 1) {
                local_40c = CRT_GETC(local_43c);
                if (local_40c == 0xffffffff) {
                  local_408 = s_Error_reading_bitmap_image_0062b704;
                  local_438 = 0;
                  local_45c = local_42c;
                  break;
                }
                *local_420 = (char)local_40c + cVar1;
                local_420++;
              }
            } while( true );
          }
          if (local_454 == 1) {
            local_42c = local_45c - 1;
            local_420 = (char *)surface_pixel_ptr((DibSurface *)param_1,0,local_42c);
            while( true ) {
              local_40c = CRT_GETC(local_43c);
              if (local_40c == 0xffffffff) break;
              if (local_40c == 0) {
                local_40c = CRT_GETC(local_43c);
                if (local_40c == 0) {
                  local_42c--;
                  local_420 = (char *)surface_pixel_ptr
                                                ((DibSurface *)param_1,0,local_42c);
                }
                else {
                  if (local_40c == 1) break;
                  if (local_40c == 2) {
                    iVar4 = CRT_GETC(local_43c);
                    local_42c -= iVar4;
                    iVar4 = CRT_GETC(local_43c);
                    local_428 += iVar4;
                    local_420 = (char *)surface_pixel_ptr
                                                  ((DibSurface *)param_1,local_428,local_42c);
                  }
                  else {
                    for (local_430 = 0; local_430 < (int)local_40c; local_430++) {
                      iVar4 = CRT_GETC(local_43c);
                      local_468 = (char)iVar4;
                      *local_420 = local_468 + cVar1;
                      local_420++;
                    }
                    if ((local_40c & 1) != 0) {
                      CRT_GETC(local_43c);
                    }
                    local_428 += local_40c;
                  }
                }
              }
              else {
                local_424 = CRT_GETC(local_43c);
                for (local_430 = 0; local_430 < (int)local_40c; local_430++) {
                  *local_420 = cVar1 + (char)local_424;
                  local_420++;
                }
                local_428 += local_40c;
              }
            }
          }
          else if (local_454 == 2) {
            local_438 = 0;
            local_408 = s_Incompatable_compression_mode__B_0062b720;
          }
        }
        else {
          local_408 = s_Image_not_640_x_480_x_256_color_0062b6e4;
        }
      }
    }
    else {
      local_408 = s_Invalid_bitmap_file_0062b698;
    }
LAB_0046fbb4:
    _fclose(local_43c);
    if (local_438 == 0) {
      MessageBoxA((HWND)0x0,local_408,(LPCSTR)0x0,0);
    }
  }
  return local_438;
}
#undef local_468
#undef local_464
#undef local_460
#undef local_45c
#undef local_456
#undef local_454
#undef local_444
#undef local_43c
#undef local_438
#undef local_434
#undef local_430
#undef local_42c
#undef local_428
#undef local_424
#undef local_420
#undef local_41c
#undef local_40c
#undef local_408
#undef local_404
#undef auStack_402

/* 0046fbf3 auto */
#define local_460 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_45c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_458 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_454 (*(i16 *)(frame_ + FRAME_OFF(12)))
#define local_452 (*(i16 *)(frame_ + FRAME_OFF(14)))
#define local_450 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_44c (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_448 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_444 (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_440 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_43c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_438 (*(FILE * *)(frame_ + FRAME_OFF(40)))
#define local_434 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_430 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_42c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_428 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_424 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_420 (*(byte * *)(frame_ + FRAME_OFF(64)))
#define local_41c (*(i16 *)(frame_ + FRAME_OFF(68)))
#define local_41a (*(i32 *)(frame_ + FRAME_OFF(70)))
#define local_416 (*(i16 *)(frame_ + FRAME_OFF(74)))
#define local_414 (*(i16 *)(frame_ + FRAME_OFF(76)))
#define local_412 (*(i32 *)(frame_ + FRAME_OFF(78)))
#define local_40c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_408 (*(char * *)(frame_ + FRAME_OFF(88)))
#define local_404 (*(i8 (*)[1024])(frame_ + FRAME_OFF(92)))
int __cdecl gfx_save_bmp_640x480(iptr param_1,iptr param_2,int param_3,int param_4,iptr param_5)

{
  iptr iVar1;
  size_t sVar2;
  int iVar3;
  i8 *puVar4;
  i8 *puVar5;
  i8 *puVar6;
  i8 frame_[FRAME_OFF(1120)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_434 = 0;
  local_408 = &gfx_save_bmp_no_error_str;
  local_41c = 0x4d42;
  local_41a = 0x4b436;
  local_416 = 0;
  local_414 = 0;
  local_412 = 0x436;
  local_460 = 0x28;
  local_45c = 0x280;
  local_458 = 0x1e0;
  local_454 = 1;
  local_452 = 8;
  local_450 = 0;
  local_44c = 0x4b000;
  local_448 = 0;
  local_444 = 0;
  local_440 = 0;
  local_43c = 0;
  for (local_42c = 0; local_42c < 0x100; local_42c++) {
    local_404[local_42c * 4] = 0;
    local_404[local_42c * 4 + 1] = local_404[local_42c * 4];
    local_404[local_42c * 4 + 2] = local_404[local_42c * 4 + 1];
  }
  for (local_42c = 0xec; local_42c < 0xfa; local_42c++) {
    local_404[local_42c * 4] = 0xff;
    local_404[local_42c * 4 + 1] = local_404[local_42c * 4];
  }
  local_404[1000] = 0xff;
  local_404[0x3ee] = 0x7f;
  local_404[0x3f2] = 0xff;
  local_404[0x3f4] = 0xff;
  local_404[0x3f6] = 0xff;
  local_404[0x3f9] = 0xff;
  local_404[0x3fc] = 0x87;
  local_404[0x3fe] = 0x87;
  local_404[0x3fd] = 0x54;
  if (param_5 != 0) {
    local_430 = 0;
    for (local_42c = param_3; local_42c < param_4 + param_3; local_42c++) {
      puVar6 = local_404 + local_430 * 4;
      puVar5 = local_404 + local_430 * 4 + 1;
      puVar4 = local_404 + local_430 * 4 + 2;
      iVar3 = local_42c;
      iVar1 = palette_get_logpalette((GamePalette *)param_5);
      palette_get_entry_rgb(iVar1,iVar3,(iptr)puVar4,(iptr)puVar5,(iptr)puVar6);
      local_430++;
    }
  }
  local_438 = __fsopen((char *)param_2,&gfx_bmp_write_mode,0x40);
  if (local_438 == (FILE *)0x0) {
    local_434 = 0;
  }
  else {
    sVar2 = _fwrite(&local_41c,0xe,1,local_438);
    if (sVar2 == 0) {
      local_408 = s_Error_writing_file_header_0062b750;
    }
    else {
      sVar2 = _fwrite(&local_460,0x28,1,local_438);
      if (sVar2 == 0) {
        local_408 = s_Error_writing_info_header_0062b76c;
      }
      else {
        sVar2 = _fwrite(local_404,0x400,1,local_438);
        if (sVar2 != 0) {
          local_434 = 1;
          local_428 = local_458;
          do {
            local_428--;
            if ((local_428 < 0) || (local_434 == 0)) goto LAB_0046ffb7;
            local_420 = (byte *)surface_pixel_ptr((DibSurface *)param_1,0,local_428);
            for (local_424 = 0; local_424 < local_45c; local_424++) {
              local_40c = (uint)*local_420 - param_3;
              local_420++;
              iVar3 = _fputc(local_40c,local_438);
              if (iVar3 == -1) {
                local_408 = s_Error_writing_bitmap_image_0062b7a4;
                local_434 = 0;
                break;
              }
            }
          } while( true );
        }
        local_408 = s_Error_writing_file_palette_0062b788;
      }
    }
LAB_0046ffb7:
    _fclose(local_438);
    if (local_434 == 0) {
      MessageBoxA((HWND)0x0,local_408,(LPCSTR)0x0,0);
    }
  }
  return local_434;
}
#undef local_460
#undef local_45c
#undef local_458
#undef local_454
#undef local_452
#undef local_450
#undef local_44c
#undef local_448
#undef local_444
#undef local_440
#undef local_43c
#undef local_438
#undef local_434
#undef local_430
#undef local_42c
#undef local_428
#undef local_424
#undef local_420
#undef local_41c
#undef local_41a
#undef local_416
#undef local_414
#undef local_412
#undef local_40c
#undef local_408
#undef local_404

/* 00471070 auto */
/* Library Function - Single Match
    public: class CRichEditView * __thiscall CRichEditCntrItem::GetActiveView(void)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall surface_get_width(DibSurface *this)

{
  i32 uVar1;
  
  uVar1 = surface_width(this);
  return uVar1;
}

/* 004710a0 auto */
/* Library Function - Single Match
    public: class CRichEditView * __thiscall CRichEditCntrItem::GetActiveView(void)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall surface_get_height(DibSurface *this)

{
  i32 uVar1;
  
  uVar1 = surface_height(this);
  return uVar1;
}

/* 00472cf0 auto */
int __cdecl gfx_zoom_scale(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (param_2 + 8) * param_1;
  return (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
}

/* 0047314e auto */
void __cdecl rect_pack_to_short(iptr param_1,iptr param_2)

{
  *(short *)param_2 = (short)*(i32 *)param_1;
  *(short *)(param_2 + 4) = (short)*(i32 *)(param_1 + 8);
  *(short *)(param_2 + 2) = (short)*(i32 *)(param_1 + 4);
  *(short *)(param_2 + 6) = (short)*(i32 *)(param_1 + 0xc);
  return;
}

/* 00473190 auto */
void __cdecl rect_unpack_from_short(iptr param_1,iptr param_2)

{
  *(int *)param_2 = (int)*(short *)param_1;
  *(int *)(param_2 + 8) = (int)*(short *)(param_1 + 4);
  *(int *)(param_2 + 4) = (int)*(short *)(param_1 + 2);
  *(int *)(param_2 + 0xc) = (int)*(short *)(param_1 + 6);
  return;
}

/* 0047df20 auto */
void __cdecl gfx_set_zoom_scale(int param_1)

{
  gfx_set_scale_ratio(param_1 + 8,8);
  return;
}

/* 0047df50 auto */
void __cdecl gfx_reset_zoom_scale(void)

{
  gfx_set_scale_ratio(1,1);
  return;
}

/* 0047df80 auto */
void __cdecl rect_intersect_into(LPRECT param_1,iptr param_2,iptr param_3)

{
  IntersectRect(param_1,(RECT *)param_2,(RECT *)param_3);
  return;
}

/* 0049621d auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
PortraitDialog * __thiscall portrait_dlg_ctor(PortraitDialog *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  surface_ctor((DibSurface *)&this->style_flags);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  button_ctor((Control *)this->pad_15c);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  button_ctor((Control *)(this->pad_15c + 0x3c));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),3);
  dll_handle_init((DllHandle *)(this->pad_1bc + 0x18));
  this->vtable = (u32)&PTR_FUN_0061d6c0;
  this->portrait_civ = 0;
  this->show_turn_timer = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0049632a auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CCommandLineInfo::~CCommandLineInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall portrait_dlg_dtor(PortraitDlgDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->pad_0 = &PTR_FUN_0061d6c0;
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 004963a5 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x1d4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 004963b4 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x198)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 004963c3 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x15c)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 004963d2 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x114)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004963e1 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00496402 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
i32 __thiscall portrait_dlg_create(PortraitDialog *this)

{
  wnd_create_with_surface
            ((DibSurface *)this,ADDR(0x62cbc8, ((u8 *)&g.d_0062cbc8)),0xc00,0,0,frame_border_width * 8 + 0x276,
             frame_border_width * 4 + frame_caption_height + 0x16e,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  portrait_dlg_create_buttons((WindowObjectView *)this);
  wnd_set_caption_height((WndBase *)this->pad_48,frame_caption_height);
  wnd_set_lbuttonup_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x403ce7, portrait_dlg_on_click));
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)(this->pad_48 + 0x10),ADDR(0x401f14, portrait_dlg_on_dblclick));
  portrait_dlg_paint(this);
  wnd_repaint((SurfaceWindow *)this);
  wnd_center((WndCenterView *)this->pad_48);
  return 1;
}
#undef frame_border_width
#undef frame_caption_height

/* 004964b3 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_1c (*(WindowObjectView * *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(WindowObjectView * *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __thiscall portrait_dlg_create_buttons(WindowObjectView *this)

{
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&local_14,frame_border_width + 2,frame_border_width * 3 + frame_caption_height + frame_bevel_width + 0x14a,
          (frame_border_width * 8 + 0x276 >> 1) - 2,
          frame_border_width * 3 + frame_caption_height + 0x16e + frame_bevel_width);
  if (this == (WindowObjectView *)0x0) {
    local_18 = (WindowObjectView *)0x0;
  }
  else {
    local_18 = this + 0x12;
  }
  button_create_with_callback
            ((Control *)(this + 0x66),(iptr)local_18,0x65,(iptr)&local_14,0x21,ADDR(0x62cbcc, ((u8 *)&g.d_0062cbcc)));
  OffsetRect(&local_14,((frame_border_width * 8 + 0x276 >> 1) + 2) - frame_border_width,0);
  if (this == (WindowObjectView *)0x0) {
    local_1c = (WindowObjectView *)0x0;
  }
  else {
    local_1c = this + 0x12;
  }
  button_create_with_callback
            ((Control *)(this + 0x57),(iptr)local_1c,100,(iptr)&local_14,0x21,ADDR(0x62cbd0, ((u8 *)&g.d_0062cbd0)));
  button_set_callback((Control *)(this + 0x57),ADDR(0x403616, portrait_dlg_on_button));
  button_set_callback((Control *)(this + 0x66),ADDR(0x403616, portrait_dlg_on_button));
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef local_1c
#undef local_18
#undef local_14

/* 004965ff auto */
void __thiscall portrait_dlg_run(PortraitDialog *this)

{
  ctrl_show_and_redraw((Control *)this->pad_15c);
  ctrl_show_and_redraw((Control *)(this->pad_15c + 0x3c));
  window_show((WindowObjectView *)this);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)this->pad_48,ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((ModalMenuWindow *)this->pad_48);
  wnd_set_modal_idle_callback((ModalMenuWindow *)this->pad_48,0);
  wnd_hide((WndBase *)this->pad_48);
  wnd_flush_paint();
  control_hide((Control *)this->pad_15c);
  control_hide((Control *)(this->pad_15c + 0x3c));
  civs[this->portrait_civ].leader_portrait = (u8)this->show_turn_status;
  return;
}

/* 004966c4 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_3c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(24)))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(40)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(56)))
void __thiscall portrait_dlg_paint(PortraitDialog *this)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  RECT *lprcSrc;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = label_string(*(i32 *)(label_string_ids + 0x4a8));
  dll_handle_load((DllHandle *)(this->pad_1bc + 0x18),ADDR(0x62cbd8, ((u8 *)&g.d_0062cbd8)));
  iVar1 = surface_load_gif_resource
                    ((DibSurface *)&this->style_flags,
                     0xd3 - (uint)(leaders[civs[this->portrait_civ].tribe].female == '\0'),10,0xec,
                     ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  if (iVar1 != 0) {
    dll_handle_free((DllHandle *)(this->pad_1bc + 0x18));
    iVar1 = frame_caption_height + frame_bevel_width * -2;
    uVar2 = surface_get_width((DibSurface *)this);
    gfx_tile_fill((iptr)this,frame_border_tile,0,frame_bevel_width,uVar2,iVar1,0,frame_bevel_width);
    uVar2 = surface_get_height((DibSurface *)this);
    iVar1 = frame_border_width + frame_bevel_width * -2;
    local_30 = frame_bevel_width;
    iVar3 = frame_caption_height - frame_bevel_width;
    for (local_34 = 0; local_34 < 8; local_34++) {
      gfx_tile_fill((iptr)this,frame_border_tile,local_30,iVar3,iVar1,uVar2,local_30,iVar3);
      local_30 = local_30 + frame_border_width + 0x5a;
    }
    iVar4 = frame_border_width + frame_bevel_width * -2;
    local_38 = frame_bevel_width + frame_caption_height + 0x6e;
    iVar5 = surface_get_width((DibSurface *)this);
    iVar3 = frame_bevel_width;
    iVar1 = frame_bevel_width * -2;
    for (local_34 = 0; local_34 < 2; local_34++) {
      gfx_tile_fill((iptr)this,frame_border_tile,iVar3,local_38,iVar5 + iVar1,iVar4,iVar3,local_38);
      local_38 = local_38 + frame_border_width + 0x6e;
    }
    iVar1 = frame_border_width * 2;
    iVar5 = surface_get_width((DibSurface *)this);
    iVar4 = frame_bevel_width;
    iVar3 = frame_bevel_width * -2;
    iVar6 = surface_get_height((DibSurface *)this);
    iVar6 = iVar6 + frame_border_width * -2 - 0x24 + frame_bevel_width;
    gfx_tile_fill((iptr)this,frame_border_tile,iVar4,iVar6,iVar5 + iVar3,iVar1 + 0x24,iVar4,iVar6);
    SetRect(&local_28,frame_border_width - frame_bevel_width,frame_caption_height - frame_bevel_width,
            frame_bevel_width * 2 + (frame_border_width - frame_bevel_width) + 0x5a,
            frame_bevel_width * 2 + (frame_caption_height - frame_bevel_width) + 0x6e);
    SetRect(&local_18,1,1,0x5b,0x6f);
    for (local_34 = 0; local_34 < 3; local_34++) {
      for (local_3c = 0; local_3c < 7; local_3c++) {
        for (local_2c = 0; local_2c < frame_bevel_width; local_2c++) {
          gfx_draw_bevel_rect((iptr)this,(iptr)&local_28,frame_shadow_color,frame_highlight_color);
          InflateRect(&local_28,-1,-1);
        }
        surface_blit
                  ((DibSurface *)&this->style_flags,(iptr)this,(iptr)&local_18,(iptr)&local_28);
        OffsetRect(&local_18,0x5b,0);
        InflateRect(&local_28,frame_bevel_width,frame_bevel_width);
        OffsetRect(&local_28,frame_border_width + 0x5a,0);
      }
      OffsetRect(&local_18,-0x27d,0x6f);
      OffsetRect(&local_28,(frame_border_width + 0x5a) * -7,frame_border_width + 0x6e);
    }
    lprcSrc = (RECT *)surface_get_rect((DibSurface *)this);
    CopyRect(&local_28,lprcSrc);
    for (local_2c = 0; local_2c < frame_bevel_width; local_2c++) {
      gfx_draw_bevel_rect((iptr)this,(iptr)&local_28,frame_highlight_color,frame_shadow_color);
      InflateRect(&local_28,-1,-1);
    }
    SetRect(&local_28,frame_border_width - frame_bevel_width,frame_caption_height - frame_bevel_width,
            frame_bevel_width * 2 + (frame_border_width - frame_bevel_width) + 0x5a,
            frame_bevel_width * 2 + (frame_caption_height - frame_bevel_width) + 0x6e);
    for (local_2c = 0; local_2c < frame_bevel_width; local_2c++) {
      gfx_draw_bevel_rect((iptr)this,(iptr)&local_28,0x5e,0x5e);
      InflateRect(&local_28,-1,-1);
    }
    iVar3 = surface_get_width((DibSurface *)this);
    iVar4 = font_text_width((GameFont *)&caption_font,local_8);
    iVar1 = frame_bevel_width;
    iVar4 = (iVar3 >> 1) - (iVar4 + 4 >> 1);
    iVar3 = frame_bevel_width + 1;
    gfx_set_text_color_index(0x12);
    surface_draw_text((DibSurface *)this,ADDR(0x6ab190, ((u8 *)&g.d_006ab190)),local_8,iVar4 + 3,iVar1 + 2,5);
    gfx_set_text_color_index(0x29);
    surface_draw_text((DibSurface *)this,ADDR(0x6ab190, ((u8 *)&g.d_006ab190)),local_8,iVar4 + 1,iVar3,5);
    surface_draw_text((DibSurface *)this,ADDR(0x6ab190, ((u8 *)&g.d_006ab190)),local_8,iVar4,iVar3,5);
  }
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_18
#undef local_8

/* 00496c3c auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_40 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_2c (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(u32 *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(DibSurface * *)(frame_ + FRAME_OFF(56)))
void __cdecl portrait_dlg_on_click(int param_1,int param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (DibSurface *)0x0;
  }
  else {
    local_8 = (DibSurface *)(iVar1 - 0x48);
  }
  local_14 = local_8[6].field_30;
  iVar1 = surface_get_height(local_8);
  if (param_2 <= iVar1 - 0x24 + frame_border_width * -2) {
    iVar1 = (param_2 - frame_caption_height) / (frame_border_width + 0x6e);
    local_8[6].field_30 =
         ((param_1 - (frame_border_width >> 1)) / (frame_border_width + 0x5a) - iVar1) + iVar1 * 8;
    local_10 = (((int)local_8[6].field_30 % 7) * (frame_border_width + 0x5a) + frame_border_width) -
               frame_bevel_width;
    local_1c = (((int)local_8[6].field_30 / 7) * (frame_border_width + 0x6e) + frame_caption_height) -
               frame_bevel_width;
    local_18 = ((frame_border_width + 0x5a) * ((int)local_14 % 7) + frame_border_width) - frame_bevel_width;
    local_30 = ((frame_border_width + 0x6e) * ((int)local_14 / 7) + frame_caption_height) - frame_bevel_width;
    SetRect(&local_2c,local_10,local_1c,frame_bevel_width * 2 + local_10 + 0x5a,
            frame_bevel_width * 2 + local_1c + 0x6e);
    SetRect(&local_40,local_18,local_30,frame_bevel_width * 2 + local_18 + 0x5a,
            frame_bevel_width * 2 + local_30 + 0x6e);
    for (local_c = 0; local_c < frame_bevel_width; local_c++) {
      gfx_draw_bevel_rect((iptr)local_8,(iptr)&local_2c,0x5e,0x5e);
      InflateRect(&local_2c,-1,-1);
      gfx_draw_bevel_rect((iptr)local_8,(iptr)&local_40,frame_shadow_color,frame_highlight_color);
      InflateRect(&local_40,-1,-1);
    }
    wnd_blit_surface(local_8);
  }
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef local_40
#undef local_30
#undef local_2c
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00496e5d auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl portrait_dlg_on_dblclick(i32 param_1,int param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  portrait_dlg_on_click(param_1,param_2);
  iVar1 = surface_get_height((DibSurface *)local_8);
  if (param_2 < iVar1 - 0x24 + frame_border_width * -2) {
    portrait_dlg_on_button(100);
  }
  return;
}
#undef frame_border_width
#undef local_8

/* 00496ecf auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl portrait_dlg_on_button(int param_1)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (((param_1 != 100) && (param_1 == 0x65)) &&
     (*(i32 *)(local_8 + 0x1e4) = *(i32 *)(local_8 + 0x1e0),
     leaders[civs[*(int *)(local_8 + 0x1dc)].tribe].female != '\0')) {
    *(int *)(local_8 + 0x1e4) = *(int *)(local_8 + 0x1e4) + 0x15;
  }
  wnd_end_modal_loop((ModalMenuWindow *)(local_8 + 0x48));
  return;
}
#undef local_8

/* 00497c40 auto */
void __thiscall
palette_get_entry
          (GamePalette *this,iptr param_1,iptr param_2,iptr param_3,iptr param_4)

{
  palette_get_entry_rgb((iptr)this,param_1,param_2,param_3,param_4);
  return;
}

/* 00497c90 auto */
u32 * __thiscall surface_get_rect(DibSurface *this)

{
  return &this->bounds_rect;
}

/* 004a6980 auto */
i32 __thiscall sprite_width(Sprite *this)

{
  i32 uVar1;
  
  uVar1 = rect_width((iptr)this);
  return uVar1;
}

/* 004b3ca0 auto */
void __cdecl font_size16_bold_global_init(void)

{
  font_size16_bold_static_init();
  font_size16_bold_reg_atexit();
  return;
}

/* 004b3cba auto */
void __cdecl font_size16_bold_static_init(void)

{
  font_init_styled((GameFont *)&font_size16_bold,0,0x10,1);
  return;
}

/* 004b3cda auto */
void __cdecl font_size16_bold_reg_atexit(void)

{
  _atexit(font_size16_bold_static_dtor);
  return;
}

/* 004b3cf7 auto */
void __cdecl font_size16_bold_static_dtor(void)

{
  font_destroy((GameFont *)&font_size16_bold);
  return;
}

/* 004b3d11 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl font_size20_global_init(void)

{
  font_size20_static_init();
  font_size20_reg_atexit();
  return;
}

/* 004b3d2b auto */
void __cdecl font_size20_static_init(void)

{
  font_init((GameFont *)&font_size20,0,0x14);
  return;
}

/* 004b3d49 auto */
void __cdecl font_size20_reg_atexit(void)

{
  _atexit(font_size20_static_dtor);
  return;
}

/* 004b3d66 auto */
void __cdecl font_size20_static_dtor(void)

{
  font_destroy((GameFont *)&font_size20);
  return;
}

/* 004b3d80 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl font_size14_global_init(void)

{
  font_size14_static_init();
  font_size14_reg_atexit();
  return;
}

/* 004b3d9a auto */
void __cdecl font_size14_static_init(void)

{
  font_init((GameFont *)&font_size14,0,0xe);
  return;
}

/* 004b3db8 auto */
void __cdecl font_size14_reg_atexit(void)

{
  _atexit(font_size14_static_dtor);
  return;
}

/* 004b3dd5 auto */
void __cdecl font_size14_static_dtor(void)

{
  font_destroy((GameFont *)&font_size14);
  return;
}

/* 004b3def auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl font_size16_global_init(void)

{
  font_size16_static_init();
  font_size16_reg_atexit();
  return;
}

/* 004b3e09 auto */
void __cdecl font_size16_static_init(void)

{
  font_init((GameFont *)&font_size16,0,0x10);
  return;
}

/* 004b3e27 auto */
void __cdecl font_size16_reg_atexit(void)

{
  _atexit(font_size16_static_dtor);
  return;
}

/* 004b3e44 auto */
void __cdecl font_size16_static_dtor(void)

{
  font_destroy((GameFont *)&font_size16);
  return;
}

/* 004b3e5e auto */
void __cdecl font_size24_bold_global_init(void)

{
  font_size24_bold_static_init();
  font_size24_bold_reg_atexit();
  return;
}

/* 004b3e78 auto */
void __cdecl font_size24_bold_static_init(void)

{
  font_init_styled((GameFont *)&font_size24_bold,0,0x18,1);
  return;
}

/* 004b3e98 auto */
void __cdecl font_size24_bold_reg_atexit(void)

{
  _atexit(font_size24_bold_static_dtor);
  return;
}

/* 004b3eb5 auto */
void __cdecl font_size24_bold_static_dtor(void)

{
  font_destroy((GameFont *)&font_size24_bold);
  return;
}

/* 004b3ecf auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl font_size30_global_init(void)

{
  font_size30_static_init();
  font_size30_reg_atexit();
  return;
}

/* 004b3ee9 auto */
void __cdecl font_size30_static_init(void)

{
  font_init((GameFont *)&font_size30,0,0x1e);
  return;
}

/* 004b3f07 auto */
void __cdecl font_size30_reg_atexit(void)

{
  _atexit(font_size30_static_dtor);
  return;
}

/* 004b3f24 auto */
void __cdecl font_size30_static_dtor(void)

{
  font_destroy((GameFont *)&font_size30);
  return;
}

/* 004b3f3e auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl font_size21_global_init(void)

{
  font_size21_static_init();
  font_size21_reg_atexit();
  return;
}

/* 004b3f58 auto */
void __cdecl font_size21_static_init(void)

{
  font_init((GameFont *)&font_size21,0,0x15);
  return;
}

/* 004b3f76 auto */
void __cdecl font_size21_reg_atexit(void)

{
  _atexit(font_size21_static_dtor);
  return;
}

/* 004b3f93 auto */
void __cdecl font_size21_static_dtor(void)

{
  font_destroy((GameFont *)&font_size21);
  return;
}

/* 004b3fad auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl font_size24_global_init(void)

{
  font_size24_static_init();
  font_size24_reg_atexit();
  return;
}

/* 004b3fc7 auto */
void __cdecl font_size24_static_init(void)

{
  font_init((GameFont *)&font_size24,0,0x18);
  return;
}

/* 004b3fe5 auto */
void __cdecl font_size24_reg_atexit(void)

{
  _atexit(font_size24_static_dtor);
  return;
}

/* 004b4002 auto */
void __cdecl font_size24_static_dtor(void)

{
  font_destroy((GameFont *)&font_size24);
  return;
}

/* 004bb540 auto */
i32 __thiscall sprite_height(Sprite *this)

{
  i32 uVar1;
  
  uVar1 = rect_height((iptr)this);
  return uVar1;
}

/* 004bb800 auto */
void __cdecl rect_deflate(iptr param_1,int param_2,int param_3)

{
  rect_inflate(param_1,-param_2,-param_3);
  return;
}

/* 004bb840 auto */
void __cdecl rect_inflate(iptr param_1,int param_2,int param_3)

{
  InflateRect((LPRECT)param_1,param_2,param_3);
  return;
}

/* 004ccb6a auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_draw_tiled_frame(iptr param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  i32 uVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = param_2 - param_6;
  iVar2 = param_3 - param_6;
  rect_set_xywh((iptr)local_14,iVar1,iVar2,param_4 + param_6 * 2,param_5 + param_6 * 2);
  uVar3 = rect_width((iptr)local_14);
  gfx_tile_fill(param_1,ADDR(0x647f18, ((u8 *)&g.d_00647f18)),iVar1,iVar2 + 2,uVar3,param_6 - 4,0,2);
  iVar4 = rect_height((iptr)local_14);
  iVar4 -= (param_6 - 2);
  gfx_tile_fill(param_1,ADDR(0x647f18, ((u8 *)&g.d_00647f18)),iVar1,iVar4 + iVar2,uVar3,param_6 - 4,0,iVar4);
  uVar3 = rect_height((iptr)local_14);
  gfx_tile_fill(param_1,ADDR(0x647f18, ((u8 *)&g.d_00647f18)),iVar1 + 2,iVar2,param_6 - 4,uVar3,2,0);
  iVar4 = rect_width((iptr)local_14);
  iVar4 -= (param_6 - 2);
  gfx_tile_fill(param_1,ADDR(0x647f18, ((u8 *)&g.d_00647f18)),iVar4 + iVar1,iVar2,param_6 - 4,uVar3,iVar4,0);
  for (local_18 = 0; local_18 < 2; local_18++) {
    gfx_draw_bevel_rect(param_1,(iptr)local_14,0x25,0x12);
    rect_deflate((iptr)local_14,1,1);
  }
  rect_deflate((iptr)local_14,param_6 - 4,0);
  local_10 = local_10 + param_6 - 4;
  local_8 -= (param_6 - 4);
  for (local_18 = 0; local_18 < 2; local_18++) {
    gfx_draw_bevel_rect(param_1,(iptr)local_14,0x12,0x25);
    rect_deflate((iptr)local_14,1,1);
  }
  return;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 004d8af0 auto */
u32 __thiscall font_get_handle(GameFont *this)

{
  return this->hfont;
}

/* 00548c78 auto */
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl
sprite_draw_spaced_row(iptr param_1,iptr param_2,int param_3,i32 param_4,int param_5,int param_6,
            int param_7,i32 param_8,int param_9)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  u32 pargs_[4] = {(u32)(uptr)param_6, (u32)(uptr)param_7, (u32)(uptr)param_8, (u32)(uptr)param_9};  /* the arguments, contiguous as on the original stack */
#define param_6 (*(int *)&pargs_[0])
#define param_7 (*(int *)&pargs_[1])
#define param_8 (*(i32 *)&pargs_[2])
#define param_9 (*(int *)&pargs_[3])
  
  local_10 = 0;
  local_8 = param_6;
  param_7 = ui_calc_item_spacing(param_6,param_7,param_8,(iptr)&param_6,(iptr)&local_14);
  if (((local_8 != 0) && (param_6 != local_8)) && (param_5 != local_8)) {
    param_5 = (param_6 * param_5) / local_8;
  }
  local_c = 0;
  while( true ) {
    iVar1 = param_6;
    if (param_5 <= param_6) {
      iVar1 = param_5;
    }
    if (iVar1 <= local_c) break;
    sprite_draw((Sprite *)param_2,(iptr)local_24,param_1,param_3,param_4);
    param_3 += param_7;
    if ((param_9 != 0) && (1 < param_6)) {
      for (local_10 = local_10 + local_14; param_6 - 1 <= local_10;
          local_10 = local_10 - (param_6 - 1)) {
        param_3++;
      }
    }
    local_c++;
  }
  return;
}
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8
#undef param_6
#undef param_7
#undef param_8
#undef param_9

/* 0054a874 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
uint __cdecl bits_nth_set(int param_1,uint param_2)

{
  bool bVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  do {
    if (local_8 == 0) {
      local_8 = 1;
    }
    else {
      local_8 = local_8 << 1;
    }
    for (; (param_2 & local_8) == 0; local_8 = local_8 << 1) {
    }
    bVar1 = param_1 != 0;
    param_1--;
  } while (bVar1);
  return local_8;
}
#undef local_8

/* 0054a8d3 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl bits_index_of(uint param_1,uint param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while (param_1 = param_1 >> 1, param_1 != 0) {
    if ((param_2 & param_1) != 0) {
      local_8++;
    }
  }
  return local_8;
}
#undef local_8

/* 0055a930 auto */
void __cdecl
gfx_copy_rect_same_pos(iptr param_1,iptr param_2,i32 param_3,i32 param_4,i32 param_5,
            i32 param_6)

{
  gfx_copy_rect_xywh(param_1,param_2,param_3,param_4,param_3,param_4,param_5,param_6);
  return;
}

/* 005683c5 auto */
#define local_44 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_3c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(32)))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(48)))
#define local_8 (*(LPVOID *)(frame_ + FRAME_OFF(64)))
i32 __cdecl gfx_dissolve_blit(iptr param_1,iptr param_2,uint param_3,int param_4)

{
  int lo;
  int iVar2;
  uint uVar3;
  uint uVar4;
  HGLOBAL pvVar5;
  i32 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    lo = surface_get_height((DibSurface *)param_1);
    iVar2 = surface_get_width((DibSurface *)param_1);
    SetRect(&local_28,0,0,iVar2,lo);
  }
  else {
    CopyRect(&local_28,(RECT *)param_2);
  }
  lo = rect_width((iptr)&local_28);
  uVar3 = lo / (int)param_3;
  lo = rect_height((iptr)&local_28);
  uVar4 = lo / (int)param_3;
  local_34 = uVar4 * uVar3;
  pvVar5 = GlobalAlloc(0x40,local_34 * 8);
  local_8 = GlobalLock(pvVar5);
  if (local_8 == (LPVOID)0x0) {
    uVar6 = 0;
  }
  else {
    switch(param_4) {
    case 1:
      for (local_3c = 0; local_3c < uVar3; local_3c++) {
        for (local_44 = 0; local_44 < uVar4; local_44++) {
          win_flush_pending_msgs();
          *(uint *)((int)local_8 + (local_3c * uVar4 + local_44) * 8) =
               ((uVar3 - local_3c) - 1) * param_3;
          *(uint *)((int)local_8 + (local_3c * uVar4 + local_44) * 8 + 4) = local_44 * param_3;
        }
      }
      break;
    case 2:
    case 5:
      for (local_3c = 0; local_3c < uVar3; local_3c++) {
        for (local_44 = 0; local_44 < uVar4; local_44++) {
          win_flush_pending_msgs();
          *(uint *)((int)local_8 + (local_3c * uVar4 + local_44) * 8) = local_3c * param_3;
          *(uint *)((int)local_8 + (local_3c * uVar4 + local_44) * 8 + 4) = local_44 * param_3;
        }
      }
      break;
    case 3:
      for (local_44 = 0; local_44 < uVar4; local_44++) {
        for (local_3c = 0; local_3c < uVar3; local_3c++) {
          win_flush_pending_msgs();
          *(uint *)((int)local_8 + (local_44 * uVar3 + local_3c) * 8) = local_3c * param_3;
          *(uint *)((int)local_8 + (local_44 * uVar3 + local_3c) * 8 + 4) = local_44 * param_3;
        }
      }
      break;
    case 4:
      for (local_44 = 0; local_44 < uVar4; local_44++) {
        for (local_3c = 0; local_3c < uVar3; local_3c++) {
          win_flush_pending_msgs();
          *(uint *)((int)local_8 + (local_44 * uVar3 + local_3c) * 8) = local_3c * param_3;
          *(uint *)((int)local_8 + (local_44 * uVar3 + local_3c) * 8 + 4) =
               ((uVar4 - local_44) - 1) * param_3;
        }
      }
    }
    if (param_4 == 5) {
      while (local_34 != 0) {
        win_flush_pending_msgs();
        iVar2 = rand_range(0,local_34 - 1);
        iVar7 = *(int *)((int)local_8 + iVar2 * 8) + local_28.left;
        iVar8 = *(int *)((int)local_8 + iVar2 * 8 + 4) + local_28.top;
        lo = param_3 + iVar8;
        if (local_28.bottom - 1 <= lo) {
          lo = local_28.bottom - 1;
        }
        iVar10 = param_3 + iVar7;
        iVar9 = local_28.right - 1;
        if (iVar10 <= local_28.right - 1) {
          iVar9 = iVar10;
        }
        SetRect(&local_18,iVar7,iVar8,iVar9,lo);
        wnd_blit_surface_rect((DibSurface *)param_1,(iptr)&local_18);
        local_34--;
        *(i32 *)((int)local_8 + iVar2 * 8) = *(i32 *)((int)local_8 + local_34 * 8);
        *(i32 *)((int)local_8 + iVar2 * 8 + 4) =
             *(i32 *)((int)local_8 + local_34 * 8 + 4);
      }
    }
    else {
      while (local_34 != 0) {
        win_flush_pending_msgs();
        lo = (local_34 - 1) - (uVar4 * 0x14) / param_3;
        if (lo < 1) {
          lo = 0;
        }
        iVar2 = rand_range(lo,local_34 - 1);
        iVar7 = *(int *)((int)local_8 + iVar2 * 8) + local_28.left;
        iVar8 = *(int *)((int)local_8 + iVar2 * 8 + 4) + local_28.top;
        lo = param_3 + iVar8;
        if (local_28.bottom - 1 <= lo) {
          lo = local_28.bottom - 1;
        }
        iVar10 = param_3 + iVar7;
        iVar9 = local_28.right - 1;
        if (iVar10 <= local_28.right - 1) {
          iVar9 = iVar10;
        }
        SetRect(&local_18,iVar7,iVar8,iVar9,lo);
        wnd_blit_surface_rect((DibSurface *)param_1,(iptr)&local_18);
        local_34--;
        *(i32 *)((int)local_8 + iVar2 * 8) = *(i32 *)((int)local_8 + local_34 * 8);
        *(i32 *)((int)local_8 + iVar2 * 8 + 4) =
             *(i32 *)((int)local_8 + local_34 * 8 + 4);
      }
    }
    pvVar5 = GlobalHandle(local_8);
    GlobalUnlock(pvVar5);
    pvVar5 = GlobalHandle(local_8);
    GlobalFree(pvVar5);
    uVar6 = 1;
  }
  return uVar6;
}
#undef local_44
#undef local_3c
#undef local_34
#undef local_28
#undef local_18
#undef local_8

/* 0056b90b auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl gfx_select_zoom_font(i32 param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = gfx_zoom_scale(0x20,param_1);
  local_8 = local_8 / 3;
  if (local_8 == 10) {
    local_8 = 0xb;
  }
  if (local_8 != map_label_font_size) {
    font_set((GameFont *)&map_label_font,1,local_8);
    map_label_font_size = local_8;
  }
  return;
}
#undef local_8

/* 0056baff auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define local_15c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_158 (*(i8 (*)[16])(frame_ + FRAME_OFF(8)))
#define local_148 (*(i8 (*)[16])(frame_ + FRAME_OFF(24)))
#define local_138 (*(i8 (*)[16])(frame_ + FRAME_OFF(40)))
#define local_128 (*(i8 (*)[16])(frame_ + FRAME_OFF(56)))
#define local_118 (*(i8 (*)[16])(frame_ + FRAME_OFF(72)))
#define local_108 (*(i8 (*)[16])(frame_ + FRAME_OFF(88)))
#define local_f8 (*(i8 (*)[16])(frame_ + FRAME_OFF(104)))
#define local_e8 (*(i8 (*)[16])(frame_ + FRAME_OFF(120)))
#define local_d8 (*(uptr *)(frame_ + FRAME_OFF(136)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(140)))
#define local_d0 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(148)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(152)))
#define local_c4 (*(uint *)(frame_ + FRAME_OFF(156)))
#define local_c0 (*(iptr *)(frame_ + FRAME_OFF(160)))
#define local_bc (*(uint *)(frame_ + FRAME_OFF(164)))
#define local_b8 (*(uint *)(frame_ + FRAME_OFF(168)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(172)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(176)))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(184)))
#define local_a4 (*(i32 *)(frame_ + FRAME_OFF(188)))
#define local_a0 (*(i32 *)(frame_ + FRAME_OFF(192)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(196)))
#define local_98 (*(i32 *)(frame_ + FRAME_OFF(200)))
#define local_94 (*(uint *)(frame_ + FRAME_OFF(204)))
#define unit_type (*(uint *)(frame_ + FRAME_OFF(208)))
#define local_8c (*(iptr *)(frame_ + FRAME_OFF(212)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(216)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(220)))
#define local_80 (*(i32 *)(frame_ + FRAME_OFF(224)))
#define local_7c (*(i32 *)(frame_ + FRAME_OFF(228)))
#define local_78 (*(i32 *)(frame_ + FRAME_OFF(232)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(236)))
#define local_70 (*(u8 (*)[80])(frame_ + FRAME_OFF(240)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(320)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(324)))
#define local_18 (*(u8 *)(frame_ + FRAME_OFF(328)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(332)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(336)))
#define local_c (*(int *)(frame_ + FRAME_OFF(340)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(344)))
void __cdecl
gfx_draw_unit(iptr param_1,iptr unit,uint param_3,int param_4,int param_5,int param_6,int param_7)

{
  int iVar1;
  iptr iVar2;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(352)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = '\0';
  gfx_set_zoom_scale(param_6);
  unit2 = unit;
  if (((param_3 & 2) != 0) && (unit2 = unit_stack_pick_display_unit(unit), unit2 < 0))
  goto LAB_0056c5e8;
  civ = (iptr)units[unit2].owner;
  unit_type = (uint)units[unit2].type;
  local_94 = unit_type;
  if ((unit_type == 0x2e) && (civ == 0)) {
    local_94 = 0x3e;
  }
  local_78 = civ_color_primary(civ);
  local_80 = civ_color_mid(civ);
  local_d0 = gfx_zoom_scale(*(i32 *)(&unit_shield_x_offsets + local_94 * 4),param_6);
  local_d0 = param_4 + local_d0;
  local_74 = gfx_zoom_scale(*(i32 *)(&unit_shield_y_offsets + local_94 * 4),param_6);
  local_74 = param_5 + local_74;
  local_8c = gfx_zoom_scale(0xc,param_6);
  local_c0 = gfx_zoom_scale(0x14,param_6);
  local_1c = 1;
  if (*(int *)(&unit_shield_x_offsets + local_94 * 4) < 0x20) {
    local_1c = -1;
  }
  if (((param_3 & 1) != 0) &&
     ((-1 < units[unit2].prev_in_stack || (-1 < units[unit2].next_in_stack)))) {
    iVar1 = gfx_zoom_scale(4,param_6);
    local_c4 = iVar1 * local_1c;
    local_cc = 0;
    rect_set_xywh((iptr)&local_b4,local_c4 + local_d0,local_74,local_8c,local_c0);
    if ((int)local_c4 < 1) {
      local_15c = ~local_c4 + 1;
    }
    else {
      local_15c = local_c4;
    }
    if (2 < (int)local_15c) {
      sprite_draw
                ((Sprite *)&unit_shield_sprite,(iptr)local_e8,param_1,
                 local_1c + local_c4 + local_d0,local_cc + local_74 + 1);
      rect_offset((iptr)&local_b4,local_1c,1);
      surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x106,0xf);
      surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x105,0xf);
      rect_offset((iptr)&local_b4,-local_1c,0xffffffff);
    }
    sprite_draw
              ((Sprite *)&unit_shield_sprite,(iptr)local_f8,param_1,local_c4 + local_d0,
               local_cc + local_74);
    surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x106,local_80);
    surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x105,local_80);
  }
  rect_set_xywh((iptr)&local_b4,local_d0,local_74,local_8c,local_c0);
  sprite_draw
            ((Sprite *)&unit_shield_sprite,(iptr)local_108,param_1,local_1c + local_d0,local_74 + 1
            );
  rect_offset((iptr)&local_b4,local_1c,1);
  surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x106,0x10);
  surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x105,0x10);
  rect_offset((iptr)&local_b4,-local_1c,0xffffffff);
  sprite_draw
            ((Sprite *)&unit_shield_sprite,(iptr)local_118,param_1,local_d0,local_74);
  surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x106,local_78);
  surface_replace_color((DibSurface *)param_1,(iptr)&local_b4,0x105,local_80);
  iVar2 = gfx_zoom_scale(2,param_6);
  rect_set_xywh((iptr)&local_a4,local_d0,local_74,local_8c,iVar2);
  gfx_fill_rect(param_1,(iptr)&local_a4,10);
  iVar1 = rect_height((iptr)&local_a4);
  local_b0 += iVar1;
  iVar2 = gfx_zoom_scale(3,param_6);
  rect_set_xywh((iptr)&local_14,local_d0,local_b0,local_8c,iVar2);
  iVar1 = rect_height((iptr)&local_14);
  local_b0 += iVar1;
  iVar2 = gfx_zoom_scale(2,param_6);
  rect_set_xywh((iptr)&local_a4,local_d0,local_b0,local_8c,iVar2);
  gfx_fill_rect(param_1,(iptr)&local_a4,10);
  iVar1 = rect_height((iptr)&local_a4);
  local_b0 += iVar1;
  local_84 = rect_width((iptr)&local_14);
  local_88 = (int)(char)unit_types[units[unit2].type].hit_points;
  local_b8 = (uint)units[unit2].damage;
  if (local_88 == 0) {
    local_88 = 10;
  }
  if ((game.rules & 0x10) == 0) {
    local_b8 = 0;
  }
  if ((param_3 & 4) == 0) {
    local_b8 = 0;
  }
  if (param_6 < -3) {
    local_b8 = 0;
  }
  local_20 = (int)((local_88 - local_b8) * local_84) / local_88;
  if ((int)local_b8 < local_88 / 3) {
    local_7c = 0x2a;
  }
  else if ((int)local_b8 < (local_88 * 2) / 3) {
    local_7c = 0x7a;
  }
  else {
    local_7c = 0x6a;
  }
  if (local_84 != local_20) {
    gfx_fill_rect(param_1,(iptr)&local_14,10);
  }
  if (local_20 != 0) {
    local_a4 = local_14;
    local_a0 = local_10;
    local_98 = local_8;
    local_9c = local_c - (local_84 - local_20);
    gfx_fill_rect(param_1,(iptr)&local_a4,local_7c);
  }
  local_d8 = (int)units[unit2].orders & 0xf;
  if (units[unit2].orders == 16) {
    local_d8 = 0xffffffff;
  }
  if ((int)local_d8 < 1) {
LAB_0056c269:
    local_18 = '-';
    if (((int)(short)units[unit2].flags & 0x8000U) != 0) {
      local_18 = '*';
    }
  }
  else if ((int)local_d8 < 0xb) {
    local_18 = order_names[local_d8].key;
  }
  else {
    if (local_d8 != 0xb) goto LAB_0056c269;
    if ((game.reveal_map == '\0') ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        local_18 = '-';
      }
      else {
        local_18 = order_names[0xb].key;
      }
    }
    else {
      local_18 = units[unit2].field_0c;
    }
  }
  if (local_18 != '\0') {
    local_70[0] = local_18;
    local_70[1] = 0;
    iVar1 = gfx_zoom_scale(3,param_6);
    local_a8 -= iVar1;
    iVar1 = crt_toupper((int)(char)local_18);
    if (iVar1 == 0x4d) {
      iVar1 = gfx_zoom_scale(1,param_6);
      local_b0 -= iVar1;
      iVar1 = gfx_zoom_scale(1,param_6);
      local_a8 -= iVar1;
    }
    gfx_select_zoom_font(param_6);
    gfx_set_text_color_index(10);
    if (((int)(short)units[unit2].flags & 0x8000U) != 0) {
      gfx_set_text_color_index(0x1d);
    }
    uVar4 = 0;
    iVar1 = rect_height((iptr)&local_b4);
    iVar3 = local_b0 + iVar1 / 2;
    iVar1 = rect_width((iptr)&local_b4);
    surface_draw_text
              ((DibSurface *)param_1,ADDR(0x6ac090, ((u8 *)&g.d_006ac090)),(iptr)local_70,local_b4 + iVar1 / 2,iVar3,uVar4);
  }
  local_bc = (uint)(units[unit2].orders == 3);
  if ((((unit_types[units[unit2].type].domain == 1) &&
       (iVar1 = map_in_bounds((int)units[unit2].x,(int)units[unit2].y), iVar1 != 0)) &&
      (iVar1 = tile_airbase_owner((int)units[unit2].x,(int)units[unit2].y), -1 < iVar1)) &&
     (((game.active_unit != unit2 || (moving_units_mode != 1)) || (unit_blink_active == '\0')))) {
    local_bc = 1;
  }
  if (local_bc == 0) {
    sprite_draw
              ((Sprite *)(&unit_sprites + local_94 * 0x3c),(iptr)local_138,param_1,param_4,
               param_5);
  }
  else {
    sprite_draw_silhouette
              ((Sprite *)(&unit_sprites + local_94 * 0x3c),(iptr)local_128,param_1,param_4,
               param_5,0x1a);
  }
  if (units[unit2].orders == 2) {
    sprite_draw
              ((Sprite *)&fortify_overlay_sprites,(iptr)local_148,param_1,param_4,param_5);
  }
  iVar1 = map_in_bounds((int)units[unit2].x,(int)units[unit2].y);
  if (((iVar1 != 0) &&
      (uVar4 = tile_improvements((int)units[unit2].x,(int)units[unit2].y),
      ((byte)uVar4 & 0x42) == 0x40)) && (param_7 == 0)) {
    sprite_draw
              ((Sprite *)&fortress_sprite,(iptr)local_158,param_1,param_4,param_5);
  }
LAB_0056c5e8:
  gfx_reset_zoom_scale();
  return;
}
#undef moving_units_mode
#undef unit_blink_active
#undef local_15c
#undef local_158
#undef local_148
#undef local_138
#undef local_128
#undef local_118
#undef local_108
#undef local_f8
#undef local_e8
#undef local_d8
#undef civ
#undef local_d0
#undef local_cc
#undef unit2
#undef local_c4
#undef local_c0
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_98
#undef local_94
#undef unit_type
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0056c5fc auto */
void __cdecl
gfx_copy_rect_clipped(iptr param_1,iptr param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9,int param_10,int param_11,int param_12)

{
  param_3 -= param_5;
  param_4 -= param_6;
  param_7 -= param_9;
  param_8 -= param_10;
  if (param_3 < 0) {
    param_7 -= param_3;
    param_11 += param_3;
    param_3 = 0;
  }
  if (param_7 < 0) {
    param_3 -= param_7;
    param_11 += param_7;
    param_7 = 0;
  }
  if (param_4 < 0) {
    param_8 -= param_4;
    param_12 += param_4;
    param_4 = 0;
  }
  if (param_8 < 0) {
    param_4 -= param_8;
    param_12 += param_8;
    param_8 = 0;
  }
  if ((0 < param_11) && (0 < param_12)) {
    gfx_copy_rect_xywh(param_1,param_2,param_5 + param_3,param_6 + param_4,param_9 + param_7,
                       param_10 + param_8,param_11,param_12);
  }
  return;
}

/* 0056d289 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_8c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_7c (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_6c (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_50 (*(iptr *)(frame_ + FRAME_OFF(64)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_48 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_40 (*(i32 *)(frame_ + FRAME_OFF(80)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(92)))
#define local_30 (*(i8 (*)[8])(frame_ + FRAME_OFF(96)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(104)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(108)))
#define local_20 (*(char (*)[8])(frame_ + FRAME_OFF(112)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(124)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(136)))
void __cdecl
gfx_draw_city(iptr param_1,iptr city,uint param_3,int param_4,int param_5,int param_6)

{
  char cVar1;
  short sVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_set_zoom_scale(param_6);
  local_50 = gfx_zoom_scale(0x40,param_6);
  local_54 = gfx_zoom_scale(0x30,param_6);
  civ = (iptr)cities[city].owner;
  rect_set_xywh((iptr)&local_18,param_4,param_5,local_50,local_54);
  gfx_set_draw_target(param_1);
  local_48 = civ_color_mid(civ);
  local_40 = civ_color_primary(civ);
  iVar3 = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
  local_28 = (uint)(-1 < iVar3);
  iVar3 = city_has_improvement(city,8);
  if ((iVar3 == 0) && (iVar3 = civ_has_wonder(civ,6), iVar3 == 0)) {
    local_24 = 0;
  }
  else {
    local_24 = 1;
  }
  local_3c = (-1 < param_6) + 1;
  sVar2 = leaders[civs[civ].tribe].city_style;
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
    sVar2 = civ_names[civ].city_style;
  }
  local_58 = (int)sVar2;
  iVar3 = civ_has_advance(civ,0x25);
  if (iVar3 != 0) {
    local_58 = 4;
  }
  iVar3 = civ_has_advance(civ,5);
  if ((iVar3 != 0) && (iVar3 = civ_has_advance(civ,0x18), iVar3 != 0)) {
    local_58 = 5;
  }
  if ((((human_civ == civ) || (game.reveal_map != '\0')) ||
      (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) || ((param_3 & 0x1000) != 0))
  {
    cVar1 = cities[city].size;
  }
  else {
    cVar1 = *(char *)&cities[city].revealed_size[human_civ];
  }
  local_8 = (int)cVar1;
  if (local_58 < 4) {
    if (local_8 < 4) {
      local_4c = 0;
    }
    else if (local_8 < 6) {
      local_4c = 1;
    }
    else if (local_8 < 8) {
      local_4c = 2;
    }
    else {
      local_4c = 3;
    }
  }
  else if (local_58 == 4) {
    if (local_8 < 5) {
      local_4c = 0;
    }
    else if (local_8 < 8) {
      local_4c = 1;
    }
    else if (local_8 < 0xb) {
      local_4c = 2;
    }
    else {
      local_4c = 3;
    }
  }
  else if (local_8 < 5) {
    local_4c = 0;
  }
  else if (local_8 < 0xb) {
    local_4c = 1;
  }
  else if (local_8 < 0x13) {
    local_4c = 2;
  }
  else {
    local_4c = 3;
  }
  iVar3 = city_has_improvement(city,1);
  if ((iVar3 != 0) &&
     (((human_civ == civ ||
       ((game.difficulty < 3 && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0))))
      && (local_4c < 3)))) {
    local_4c++;
  }
  sprite_draw
            ((Sprite *)(&city_sprites + local_4c * 0x78 + local_24 * 0x3c + local_58 * 0x1e0)
             ,(iptr)local_6c,param_1,param_4,param_5);
  iVar3 = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
  if ((-1 < iVar3) && ((param_3 & 2) == 0)) {
    local_38 = gfx_zoom_scale(*(i32 *)
                                   (&city_flag_x_offsets + local_58 * 0x20 + local_24 * 4 + local_4c * 8),
                                  param_6);
    local_38 = param_4 + local_38;
    local_44 = gfx_zoom_scale(*(i32 *)
                                   (&city_flag_y_offsets + local_58 * 0x20 + local_24 * 4 + local_4c * 8),
                                  param_6);
    local_44 = param_5 + local_44;
    sprite_draw
              ((Sprite *)(&civ_flag_sprites + civ * 0x78),(iptr)local_7c,param_1,local_38,
               local_44);
  }
  if ((param_3 & 1) == 0) {
    if ((cities[city].flags & 1) == 0) {
      gfx_select_zoom_font(param_6);
      text_set_font(ADDR(0x6ac090, ((u8 *)&g.d_006ac090)));
      text_set_surface(param_1);
      __itoa(local_8,local_20,10);
      local_50 = font_text_width((GameFont *)&map_label_font,(iptr)local_20);
      local_54 = font_cached_height((GameFont *)&map_label_font);
      crt_strcpy(local_30,&city_size_digit_str);
      sVar4 = _strlen(local_20);
      if (1 < sVar4) {
        crt_strcat(local_30,&city_size_digit2_str);
      }
      local_34 = font_text_width((GameFont *)&map_label_font,(iptr)local_30);
      local_34 -= local_50;
      if (local_34 < 0) {
        local_34 = 0;
      }
      local_50 = local_50 + local_34 + 5;
      local_54 += 2;
      rect_set_xywh((iptr)&local_18,0,0,local_50,local_54);
      iVar3 = gfx_zoom_scale(*(i32 *)
                                  (&city_label_y_offsets + local_58 * 0x20 + local_24 * 4 + local_4c * 8),
                                 param_6);
      iVar3 = param_5 + iVar3;
      iVar5 = gfx_zoom_scale(*(i32 *)
                                  (&city_size_box_x_offsets + local_58 * 0x20 + local_24 * 4 + local_4c * 8),
                                 param_6);
      rect_offset((iptr)&local_18,param_4 + iVar5,iVar3);
      gfx_draw_rect_frame(param_1,(iptr)&local_18,10);
      rect_deflate((iptr)&local_18,1,1);
      gfx_fill_rect(param_1,(iptr)&local_18,local_40);
      text_set_colors(10,10,1,0);
      gfx_draw_text((iptr)local_20,local_18 + (local_34 >> 1) + 1,local_14);
    }
    else {
      sprite_draw
                ((Sprite *)&city_disorder_icon_sprite,(iptr)local_8c,param_1,param_4,param_5);
      surface_replace_color((DibSurface *)param_1,(iptr)&local_18,0x106,local_40);
    }
  }
  gfx_reset_zoom_scale();
  return;
}
#undef human_civ
#undef scenario_flags
#undef local_8c
#undef local_7c
#undef local_6c
#undef civ
#undef local_58
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
#undef local_28
#undef local_24
#undef local_20
#undef local_18
#undef local_14
#undef local_8

/* 0056e1c0 auto */
int __cdecl gfx_zoom_scale_round(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (param_2 + 8) * param_1 + 4;
  return (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
}

/* 0056f910 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_sheet_surface_global_init(void)

{
  sprite_sheet_surface_static_init();
  sprite_sheet_surface_reg_atexit();
  return;
}

/* 0056f92a auto */
void __cdecl sprite_sheet_surface_static_init(void)

{
  surface_ctor((DibSurface *)&sprite_sheet_surface);
  return;
}

/* 0056f944 auto */
void __cdecl sprite_sheet_surface_reg_atexit(void)

{
  _atexit(sprite_sheet_surface_static_dtor);
  return;
}

/* 0056f961 auto */
void __cdecl sprite_sheet_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)&sprite_sheet_surface);
  return;
}

/* 0056f97b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_editor_orig_sprite_global_init(void)

{
  sprite_editor_orig_sprite_static_init();
  sprite_editor_orig_sprite_reg_atexit();
  return;
}

/* 0056f995 auto */
void __cdecl sprite_editor_orig_sprite_static_init(void)

{
  sprite_init((Sprite *)&sprite_editor_orig_sprite);
  return;
}

/* 0056f9af auto */
void __cdecl sprite_editor_orig_sprite_reg_atexit(void)

{
  _atexit(sprite_editor_orig_sprite_static_dtor);
  return;
}

/* 0056f9cc auto */
void __cdecl sprite_editor_orig_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&sprite_editor_orig_sprite);
  return;
}

/* 0056f9e6 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_editor_result_global_init(void)

{
  sprite_editor_result_static_init();
  sprite_editor_result_reg_atexit();
  return;
}

/* 0056fa00 auto */
void __cdecl sprite_editor_result_static_init(void)

{
  sprite_init((Sprite *)&sprite_editor_result_sprite);
  return;
}

/* 0056fa1a auto */
void __cdecl sprite_editor_result_reg_atexit(void)

{
  _atexit(sprite_editor_result_static_dtor);
  return;
}

/* 0056fa37 auto */
void __cdecl sprite_editor_result_static_dtor(void)

{
  sprite_destroy((Sprite *)&sprite_editor_result_sprite);
  return;
}

/* 0056fa51 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_picker_sprite_global_init(void)

{
  sprite_picker_sprite_static_init();
  sprite_picker_sprite_reg_atexit();
  return;
}

/* 0056fa6b auto */
void __cdecl sprite_picker_sprite_static_init(void)

{
  sprite_init((Sprite *)&sprite_picker_sprite);
  return;
}

/* 0056fa85 auto */
void __cdecl sprite_picker_sprite_reg_atexit(void)

{
  _atexit(sprite_picker_sprite_static_dtor);
  return;
}

/* 0056faa2 auto */
void __cdecl sprite_picker_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&sprite_picker_sprite);
  return;
}

/* 0056fabc auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_editor_surface_global_init(void)

{
  sprite_editor_surface_static_init();
  sprite_editor_surface_reg_atexit();
  return;
}

/* 0056fad6 auto */
void __cdecl sprite_editor_surface_static_init(void)

{
  surface_ctor((DibSurface *)&sprite_editor_surface);
  return;
}

/* 0056faf0 auto */
void __cdecl sprite_editor_surface_reg_atexit(void)

{
  _atexit(sprite_editor_surface_static_dtor);
  return;
}

/* 0056fb0d auto */
void __cdecl sprite_editor_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)&sprite_editor_surface);
  return;
}

/* 0056fb27 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_editor_window_global_init(void)

{
  sprite_editor_window_static_init();
  sprite_editor_window_reg_atexit();
  return;
}

/* 0056fb41 auto */
void __cdecl sprite_editor_window_static_init(void)

{
  frame_wnd_ctor((SurfaceWindow *)&sprite_editor_window);
  return;
}

/* 0056fb5b auto */
void __cdecl sprite_editor_window_reg_atexit(void)

{
  _atexit(sprite_editor_window_static_dtor);
  return;
}

/* 0056fb78 auto */
void __cdecl sprite_editor_window_static_dtor(void)

{
  frame_wnd_dtor((DibSurface *)&sprite_editor_window);
  return;
}

/* 0056fb92 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl sprite_picker_window_global_init(void)

{
  sprite_picker_window_static_init();
  sprite_picker_window_reg_atexit();
  return;
}

/* 0056fbac auto */
void __cdecl sprite_picker_window_static_init(void)

{
  sprite_picker_ctor((ViewWindow *)&sprite_picker_window);
  return;
}

/* 0056fbc6 auto */
void __cdecl sprite_picker_window_reg_atexit(void)

{
  _atexit(sprite_picker_window_static_dtor);
  return;
}

/* 0056fbe3 auto */
void __cdecl sprite_picker_window_static_dtor(void)

{
  sprite_picker_dtor((WindowObjectView *)&sprite_picker_window);
  return;
}

/* 0056fbfd auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl sprite_sheet_draw_shield_marks(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = param_2 - 1;
  iVar2 = param_3 - 1;
  for (local_c = 0; local_c < 0x40; local_c++) {
    surface_set_pixel((DibSurface *)&sprite_sheet_surface,iVar1 + local_c + 1,iVar2,8);
  }
  surface_set_pixel
            ((DibSurface *)&sprite_sheet_surface,iVar1 + *(int *)(&unit_shield_x_offsets + param_1 * 4) + 1,iVar2,
             4);
  for (local_14 = 0; local_14 < 0x30; local_14++) {
    surface_set_pixel((DibSurface *)&sprite_sheet_surface,iVar1,local_14 + iVar2 + 1,8);
  }
  surface_set_pixel
            ((DibSurface *)&sprite_sheet_surface,iVar1,*(int *)(&unit_shield_y_offsets + param_1 * 4) + iVar2 + 1,
             4);
  return;
}
#undef local_14
#undef local_c

/* 0056fce4 auto */
#define local_580 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_570 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_560 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_55c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_558 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_554 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_550 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_54c (*(GamePalette *)(frame_ + FRAME_OFF(52)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(1128)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1388)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1392)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1396)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1400)))
void __cdecl sprite_sheet_save_units(void)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(1408)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_54c);
  local_8 = 0;
  __getcwd(local_118,0x104);
  __chdir(&scenario_dir_path);
  iVar2 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x634010, ((u8 *)&g.d_00634010)),10,0xc0,(iptr)&local_54c);
  if (iVar2 == 0) {
    iVar2 = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,ADDR(0x63401c, ((u8 *)&g.d_0063401c)),10,0xc0,(iptr)&local_54c);
    if (iVar2 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,ADDR(0x634028, ((u8 *)&g.d_00634028)),10,0xc0,(iptr)&local_54c);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_554 = 1;
  local_560 = 0;
  local_55c = 0;
  local_550 = 1;
  local_14 = 1;
  for (local_558 = 0; local_558 < 0x3f; local_558++) {
    bVar1 = sprite_get_key_color((Sprite *)(&unit_sprites + local_558 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&unit_sprites + local_558 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&unit_sprites + local_558 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_14,local_550,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_570,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_14,local_550);
    sprite_draw
              ((Sprite *)(&unit_sprites + local_558 * 0x3c),(iptr)local_580,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_14
               ,local_550);
    sprite_sheet_draw_shield_marks(local_558,local_14,local_550);
    local_55c++;
    local_14 += 0x41;
    if (8 < local_55c) {
      local_55c = 0;
      local_560++;
      local_550 += 0x31;
      local_14 = local_554;
    }
  }
  __chdir(&scenario_dir_path);
  iVar2 = file_exists(ADDR(0x634034, ((u8 *)&g.d_00634034)));
  if (iVar2 != 0) {
    iVar2 = crt_remove(s_UNITS_BMP_00634040);
    if (iVar2 != 0) goto LAB_0056ff8c;
  }
  gfx_save_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x63404c, ((u8 *)&g.d_0063404c)),10,0xc0,(iptr)&local_54c);
LAB_0056ff8c:
  __chdir(local_118);
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0056ffb6 */ { palette_destroy((GamePalette *)((iptr)&local_54c)); }
  return;
}
#undef local_580
#undef local_570
#undef local_560
#undef local_55c
#undef local_558
#undef local_554
#undef local_550
#undef local_54c
#undef local_118
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0056ffda auto */
#define local_64c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_63c (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_62c (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_61c (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_60c (*(i8 (*)[16])(frame_ + FRAME_OFF(68)))
#define local_5fc (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define local_5ec (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define local_5dc (*(i8 (*)[16])(frame_ + FRAME_OFF(116)))
#define local_5cc (*(i8 (*)[16])(frame_ + FRAME_OFF(132)))
#define local_5bc (*(i8 (*)[16])(frame_ + FRAME_OFF(148)))
#define local_5ac (*(i8 (*)[16])(frame_ + FRAME_OFF(164)))
#define local_59c (*(i8 (*)[16])(frame_ + FRAME_OFF(180)))
#define local_58c (*(i8 (*)[16])(frame_ + FRAME_OFF(196)))
#define local_57c (*(i8 (*)[16])(frame_ + FRAME_OFF(212)))
#define local_56c (*(int *)(frame_ + FRAME_OFF(228)))
#define local_568 (*(int *)(frame_ + FRAME_OFF(232)))
#define local_564 (*(int *)(frame_ + FRAME_OFF(236)))
#define local_560 (*(i32 *)(frame_ + FRAME_OFF(240)))
#define local_55c (*(i32 *)(frame_ + FRAME_OFF(244)))
#define local_558 (*(int *)(frame_ + FRAME_OFF(248)))
#define local_554 (*(int *)(frame_ + FRAME_OFF(252)))
#define local_550 (*(int *)(frame_ + FRAME_OFF(256)))
#define local_54c (*(GamePalette *)(frame_ + FRAME_OFF(260)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(1336)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1596)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1600)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1604)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1608)))
void __cdecl sprite_sheet_save_cities(void)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(1616)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_54c);
  local_8 = 0;
  __getcwd(local_118,0x104);
  __chdir(&scenario_dir_path);
  iVar2 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x634058, ((u8 *)&g.d_00634058)),10,0xc0,(iptr)&local_54c);
  if (iVar2 == 0) {
    iVar2 = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,ADDR(0x634064, ((u8 *)&g.d_00634064)),10,0xc0,(iptr)&local_54c);
    if (iVar2 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,ADDR(0x634070, ((u8 *)&g.d_00634070)),10,0xc0,(iptr)&local_54c);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_550 = 1;
  local_554 = 0x27;
  local_558 = 0x14e;
  for (local_56c = 0; local_56c < 6; local_56c++) {
    for (local_14 = 0; local_14 < 4; local_14++) {
      local_564 = local_14 * 0x41;
      bVar1 = sprite_get_key_color
                        ((Sprite *)(&city_sprites + local_14 * 0x78 + local_56c * 0x1e0));
      uVar5 = (uint)bVar1;
      iVar3 = sprite_height
                        ((Sprite *)(&city_sprites + local_14 * 0x78 + local_56c * 0x1e0));
      uVar4 = sprite_width
                        ((Sprite *)(&city_sprites + local_14 * 0x78 + local_56c * 0x1e0));
      gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_564 + local_550,local_554,uVar4,iVar3,uVar5);
      sprite_draw
                ((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_57c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_564 + local_550,
                 local_554);
      sprite_draw
                ((Sprite *)(&city_sprites + local_14 * 0x78 + local_56c * 0x1e0),
                 (iptr)local_58c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_564 + local_550,local_554);
      bVar1 = sprite_get_key_color
                        ((Sprite *)(&city_walled_sprites + local_14 * 0x78 + local_56c * 0x1e0));
      uVar5 = (uint)bVar1;
      iVar3 = sprite_height
                        ((Sprite *)(&city_walled_sprites + local_14 * 0x78 + local_56c * 0x1e0));
      uVar4 = sprite_width
                        ((Sprite *)(&city_walled_sprites + local_14 * 0x78 + local_56c * 0x1e0));
      gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_564 + local_558,local_554,uVar4,iVar3,uVar5);
      sprite_draw
                ((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_59c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_564 + local_558,
                 local_554);
      sprite_draw
                ((Sprite *)(&city_walled_sprites + local_14 * 0x78 + local_56c * 0x1e0),
                 (iptr)local_5ac,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_564 + local_558,local_554);
    }
    local_554 += 0x31;
  }
  local_550 = 1;
  local_55c = 0x1a9;
  local_560 = 0x1c0;
  for (local_568 = 0; local_568 < 8; local_568++) {
    bVar1 = sprite_get_key_color((Sprite *)(&civ_flag_sprites + local_568 * 0x78));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&civ_flag_sprites + local_568 * 0x78));
    uVar4 = sprite_width((Sprite *)(&civ_flag_sprites + local_568 * 0x78));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_55c,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&civ_flag_sprites + local_568 * 0x78),(iptr)local_5bc,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550,local_55c);
    bVar1 = sprite_get_key_color((Sprite *)(&civ_flag_dark_sprites + local_568 * 0x78));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&civ_flag_dark_sprites + local_568 * 0x78));
    uVar4 = sprite_width((Sprite *)(&civ_flag_dark_sprites + local_568 * 0x78));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_560,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&civ_flag_dark_sprites + local_568 * 0x78),(iptr)local_5cc,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550,local_560);
    local_550 += 0xf;
  }
  bVar1 = sprite_get_key_color((Sprite *)&fortify_overlay_sprites);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&fortify_overlay_sprites);
  uVar4 = sprite_width((Sprite *)&fortify_overlay_sprites);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x8f,0x1a7,uVar4,iVar3,uVar5);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_5dc,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x8f,0x1a7);
  sprite_draw((Sprite *)&fortify_overlay_sprites,(iptr)local_5ec,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x8f,0x1a7);
  bVar1 = sprite_get_key_color((Sprite *)&fortress_sprite);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&fortress_sprite);
  uVar4 = sprite_width((Sprite *)&fortress_sprite);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0xd0,0x1a7,uVar4,iVar3,uVar5);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_5fc,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0xd0,0x1a7);
  sprite_draw((Sprite *)&fortress_sprite,(iptr)local_60c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0xd0,0x1a7);
  bVar1 = sprite_get_key_color((Sprite *)&airbase_sprites);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&airbase_sprites);
  uVar4 = sprite_width((Sprite *)&airbase_sprites);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x111,0x1a7,uVar4,iVar3,uVar5);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_61c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x111,0x1a7);
  sprite_draw((Sprite *)&airbase_sprites,(iptr)local_62c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x111,0x1a7);
  bVar1 = sprite_get_key_color((Sprite *)&airbase_occupied_sprite);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&airbase_occupied_sprite);
  uVar4 = sprite_width((Sprite *)&airbase_occupied_sprite);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x152,0x1a7,uVar4,iVar3,uVar5);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_63c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x152,0x1a7);
  sprite_draw((Sprite *)&airbase_occupied_sprite,(iptr)local_64c,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),0x152,0x1a7);
  __chdir(&scenario_dir_path);
  iVar2 = file_exists(ADDR(0x63407c, ((u8 *)&g.d_0063407c)));
  if (iVar2 != 0) {
    iVar2 = crt_remove(s_CITIES_BMP_00634088);
    if (iVar2 != 0) goto LAB_00570732;
  }
  gfx_save_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x634094, ((u8 *)&g.d_00634094)),10,0xc0,(iptr)&local_54c);
LAB_00570732:
  __chdir(local_118);
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0057075c */ { palette_destroy((GamePalette *)((iptr)&local_54c)); }
  return;
}
#undef local_64c
#undef local_63c
#undef local_62c
#undef local_61c
#undef local_60c
#undef local_5fc
#undef local_5ec
#undef local_5dc
#undef local_5cc
#undef local_5bc
#undef local_5ac
#undef local_59c
#undef local_58c
#undef local_57c
#undef local_56c
#undef local_568
#undef local_564
#undef local_560
#undef local_55c
#undef local_558
#undef local_554
#undef local_550
#undef local_54c
#undef local_118
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00570780 auto */
#define local_680 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_670 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_660 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_650 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_640 (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define local_630 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define local_620 (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define local_610 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define local_600 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_5f0 (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define local_5e0 (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define local_5d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define local_5c0 (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define local_5b0 (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define local_5a0 (*(i8 (*)[16])(frame_ + FRAME_OFF(224)))
#define local_590 (*(i8 (*)[16])(frame_ + FRAME_OFF(240)))
#define local_580 (*(i8 (*)[16])(frame_ + FRAME_OFF(256)))
#define local_570 (*(i8 (*)[16])(frame_ + FRAME_OFF(272)))
#define local_560 (*(i32 *)(frame_ + FRAME_OFF(288)))
#define local_55c (*(i32 *)(frame_ + FRAME_OFF(292)))
#define local_558 (*(int *)(frame_ + FRAME_OFF(296)))
#define local_554 (*(int *)(frame_ + FRAME_OFF(300)))
#define local_550 (*(GamePalette *)(frame_ + FRAME_OFF(304)))
#define local_11c (*(char (*)[260])(frame_ + FRAME_OFF(1380)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1640)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1644)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1648)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1652)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1656)))
void __cdecl sprite_sheet_save_terrain1(void)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(1664)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_550);
  local_8 = 0;
  __getcwd(local_11c,0x104);
  __chdir(&scenario_dir_path);
  iVar2 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x6340a0, ((u8 *)&g.d_006340a0)),10,0xc0,(iptr)&local_550);
  if (iVar2 == 0) {
    iVar2 = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,ADDR(0x6340b0, ((u8 *)&g.d_006340b0)),10,0xc0,(iptr)&local_550);
    if (iVar2 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,ADDR(0x6340c0, ((u8 *)&g.d_006340c0)),10,0xc0,(iptr)&local_550);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_554 = 1;
  local_55c = 0x83;
  local_560 = 0xc4;
  local_558 = 1;
  for (local_18 = 0; local_18 < 0xb; local_18++) {
    bVar1 = sprite_get_key_color((Sprite *)(&terrain_base_sprites + local_18 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&terrain_base_sprites + local_18 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&terrain_base_sprites + local_18 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_570,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
    sprite_draw
              ((Sprite *)(&terrain_base_sprites + local_18 * 0x3c),(iptr)local_580,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554
               ,local_558);
    bVar1 = sprite_get_key_color((Sprite *)(&terrain_resource_sprites + local_18 * 0x78));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&terrain_resource_sprites + local_18 * 0x78));
    uVar4 = sprite_width((Sprite *)(&terrain_resource_sprites + local_18 * 0x78));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_55c,local_558,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_590,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_55c,local_558);
    sprite_draw
              ((Sprite *)(&terrain_resource_sprites + local_18 * 0x78),(iptr)local_5a0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_55c
               ,local_558);
    bVar1 = sprite_get_key_color((Sprite *)(&terrain_resource2_sprites + local_18 * 0x78));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&terrain_resource2_sprites + local_18 * 0x78));
    uVar4 = sprite_width((Sprite *)(&terrain_resource2_sprites + local_18 * 0x78));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_560,local_558,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_5b0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_560,local_558);
    sprite_draw
              ((Sprite *)(&terrain_resource2_sprites + local_18 * 0x78),(iptr)local_5c0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_560
               ,local_558);
    local_558 += 0x21;
  }
  local_554 = 0x1c8;
  local_558 = 100;
  for (local_14 = 0; local_14 < 3; local_14++) {
    bVar1 = sprite_get_key_color((Sprite *)(&land_improvement_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&land_improvement_sprites + local_18 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&land_improvement_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_5d0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
    sprite_draw
              ((Sprite *)(&land_improvement_sprites + local_14 * 0x3c),(iptr)local_5e0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554
               ,local_558);
    local_558 += 0x21;
  }
  bVar1 = sprite_get_key_color((Sprite *)&pollution_sprite);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&pollution_sprite);
  uVar4 = sprite_width((Sprite *)&pollution_sprite);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558,uVar4,iVar3,uVar5);
  sprite_draw
            ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_5f0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
  sprite_draw
            ((Sprite *)&pollution_sprite,(iptr)local_600,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
  local_558 += 0x21;
  bVar1 = sprite_get_key_color((Sprite *)&grassland_shield_sprite);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&grassland_shield_sprite);
  uVar4 = sprite_width((Sprite *)&grassland_shield_sprite);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558,uVar4,iVar3,uVar5);
  sprite_draw
            ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_610,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
  sprite_draw
            ((Sprite *)&grassland_shield_sprite,(iptr)local_620,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
  local_558 += 0x21;
  bVar1 = sprite_get_key_color((Sprite *)&hut_sprite);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&hut_sprite);
  uVar4 = sprite_width((Sprite *)&hut_sprite);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558,uVar4,iVar3,uVar5);
  sprite_draw
            ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_630,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
  sprite_draw
            ((Sprite *)&hut_sprite,(iptr)local_640,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
  local_558 = 0x16c;
  local_554 = 1;
  for (local_14 = 0; local_14 < 9; local_14++) {
    bVar1 = sprite_get_key_color((Sprite *)(&road_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&road_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&road_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_650,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558);
    sprite_draw
              ((Sprite *)(&road_sprites + local_14 * 0x3c),(iptr)local_660,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554
               ,local_558);
    bVar1 = sprite_get_key_color((Sprite *)(&railroad_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&railroad_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&railroad_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558 + 0x21,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_670,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554,local_558 + 0x21);
    sprite_draw
              ((Sprite *)(&railroad_sprites + local_14 * 0x3c),(iptr)local_680,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_554
               ,local_558 + 0x21);
    local_554 += 0x41;
  }
  __chdir(&scenario_dir_path);
  iVar2 = file_exists(ADDR(0x6340d0, ((u8 *)&g.d_006340d0)));
  if (iVar2 != 0) {
    iVar2 = crt_remove(s_TERRAIN1_BMP_006340e0);
    if (iVar2 != 0) goto LAB_00570f78;
  }
  gfx_save_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x6340f0, ((u8 *)&g.d_006340f0)),10,0xc0,(iptr)&local_550);
LAB_00570f78:
  __chdir(local_11c);
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00570fa2 */ { palette_destroy((GamePalette *)((iptr)&local_550)); }
  return;
}
#undef local_680
#undef local_670
#undef local_660
#undef local_650
#undef local_640
#undef local_630
#undef local_620
#undef local_610
#undef local_600
#undef local_5f0
#undef local_5e0
#undef local_5d0
#undef local_5c0
#undef local_5b0
#undef local_5a0
#undef local_590
#undef local_580
#undef local_570
#undef local_560
#undef local_55c
#undef local_558
#undef local_554
#undef local_550
#undef local_11c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00570fc6 auto */
#define local_640 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_630 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_620 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_610 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_600 (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define local_5f0 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define local_5e0 (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define local_5d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define local_5c0 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_5b0 (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define local_5a0 (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define local_590 (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define local_580 (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define local_570 (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define local_560 (*(int *)(frame_ + FRAME_OFF(224)))
#define local_55c (*(int *)(frame_ + FRAME_OFF(228)))
#define local_558 (*(int *)(frame_ + FRAME_OFF(232)))
#define local_554 (*(int *)(frame_ + FRAME_OFF(236)))
#define local_550 (*(int *)(frame_ + FRAME_OFF(240)))
#define local_54c (*(GamePalette *)(frame_ + FRAME_OFF(244)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(1320)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(1580)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1584)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1588)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1592)))
void __cdecl sprite_sheet_save_terrain2(void)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(1600)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_54c);
  local_8 = 0;
  __getcwd(local_118,0x104);
  __chdir(&scenario_dir_path);
  iVar2 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x634100, ((u8 *)&g.d_00634100)),10,0xc0,(iptr)&local_54c);
  if (iVar2 == 0) {
    iVar2 = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,ADDR(0x634110, ((u8 *)&g.d_00634110)),10,0xc0,(iptr)&local_54c);
    if (iVar2 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,ADDR(0x634120, ((u8 *)&g.d_00634120)),10,0xc0,(iptr)&local_54c);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_550 = 1;
  local_55c = 0x43;
  for (local_14 = 0; (int)local_14 < 0x10; local_14++) {
    local_554 = (local_14 & 7) * 0x41;
    local_558 = ((int)local_14 >> 3) * 0x21;
    bVar1 = sprite_get_key_color((Sprite *)(&river_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&river_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&river_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,local_55c + local_558,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_570,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,
               local_55c + local_558);
    sprite_draw
              ((Sprite *)(&river_sprites + local_14 * 0x3c),(iptr)local_580,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550 + local_554,local_55c + local_558);
    bVar1 = sprite_get_key_color((Sprite *)(&forest_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&forest_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&forest_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,local_55c + local_558 + 0x42,uVar4,iVar3,uVar5
                      );
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_590,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,
               local_55c + local_558 + 0x42);
    sprite_draw
              ((Sprite *)(&forest_sprites + local_14 * 0x3c),(iptr)local_5a0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550 + local_554,local_55c + local_558 + 0x42);
    bVar1 = sprite_get_key_color((Sprite *)(&mountain_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&mountain_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&mountain_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,local_55c + local_558 + 0x84,uVar4,iVar3,uVar5
                      );
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_5b0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,
               local_55c + local_558 + 0x84);
    sprite_draw
              ((Sprite *)(&mountain_sprites + local_14 * 0x3c),(iptr)local_5c0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550 + local_554,local_55c + local_558 + 0x84);
    bVar1 = sprite_get_key_color((Sprite *)(&hill_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&hill_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&hill_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,local_55c + local_558 + 0xc6,uVar4,iVar3,uVar5
                      );
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_5d0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + local_554,
               local_55c + local_558 + 0xc6);
    sprite_draw
              ((Sprite *)(&hill_sprites + local_14 * 0x3c),(iptr)local_5e0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550 + local_554,local_55c + local_558 + 0xc6);
  }
  local_550 = 1;
  local_55c = 0x14b;
  for (local_14 = 0; (int)local_14 < 4; local_14++) {
    bVar1 = sprite_get_key_color((Sprite *)(&river_mouth_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&river_mouth_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&river_mouth_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_55c,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_5f0,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_55c);
    sprite_draw
              ((Sprite *)(&river_mouth_sprites + local_14 * 0x3c),(iptr)local_600,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550
               ,local_55c);
    local_550 += 0x41;
  }
  local_550 = 1;
  local_55c = 0x1ad;
  for (local_560 = 0; local_560 < 8; local_560++) {
    bVar1 = sprite_get_key_color((Sprite *)(&coast_quarter_sprites + local_560 * 0xf0));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&coast_quarter_sprites + local_560 * 0xf0));
    uVar4 = sprite_width((Sprite *)(&coast_quarter_sprites + local_560 * 0xf0));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_55c,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&coast_quarter_sprites + local_560 * 0xf0),(iptr)local_610,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550,local_55c);
    bVar1 = sprite_get_key_color((Sprite *)(&coast_quarter_east_sprites + local_560 * 0xf0));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&coast_quarter_east_sprites + local_560 * 0xf0));
    uVar4 = sprite_width((Sprite *)(&coast_quarter_east_sprites + local_560 * 0xf0));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550 + 0x21,local_55c + 0x22,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&coast_quarter_east_sprites + local_560 * 0xf0),(iptr)local_620,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550 + 0x21,local_55c + 0x22);
    bVar1 = sprite_get_key_color((Sprite *)(&coast_quarter_south_sprites + local_560 * 0xf0));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&coast_quarter_south_sprites + local_560 * 0xf0));
    uVar4 = sprite_width((Sprite *)(&coast_quarter_south_sprites + local_560 * 0xf0));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_55c + 0x11,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&coast_quarter_south_sprites + local_560 * 0xf0),(iptr)local_630,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550,local_55c + 0x11);
    bVar1 = sprite_get_key_color((Sprite *)(&coast_quarter_west_sprites + local_560 * 0xf0));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&coast_quarter_west_sprites + local_560 * 0xf0));
    uVar4 = sprite_width((Sprite *)(&coast_quarter_west_sprites + local_560 * 0xf0));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_550,local_55c + 0x22,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&coast_quarter_west_sprites + local_560 * 0xf0),(iptr)local_640,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),
               local_550,local_55c + 0x22);
    local_550 += 0x42;
  }
  __chdir(&scenario_dir_path);
  iVar2 = file_exists(ADDR(0x634130, ((u8 *)&g.d_00634130)));
  if (iVar2 != 0) {
    iVar2 = crt_remove(s_TERRAIN2_BMP_00634140);
    if (iVar2 != 0) goto LAB_005718c2;
  }
  gfx_save_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x634150, ((u8 *)&g.d_00634150)),10,0xc0,(iptr)&local_54c);
LAB_005718c2:
  __chdir(local_118);
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005718ec */ { palette_destroy((GamePalette *)((iptr)&local_54c)); }
  return;
}
#undef local_640
#undef local_630
#undef local_620
#undef local_610
#undef local_600
#undef local_5f0
#undef local_5e0
#undef local_5d0
#undef local_5c0
#undef local_5b0
#undef local_5a0
#undef local_590
#undef local_580
#undef local_570
#undef local_560
#undef local_55c
#undef local_558
#undef local_554
#undef local_550
#undef local_54c
#undef local_118
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00571910 auto */
#define local_568 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_558 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_554 (*(GamePalette *)(frame_ + FRAME_OFF(20)))
#define local_120 (*(int *)(frame_ + FRAME_OFF(1096)))
#define local_11c (*(char (*)[260])(frame_ + FRAME_OFF(1100)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1360)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1364)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1368)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1372)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1376)))
void __cdecl sprite_sheet_save_tech_icons(void)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(1384)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_554);
  local_8 = 0;
  __getcwd(local_11c,0x104);
  __chdir(&scenario_dir_path);
  iVar2 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x634160, ((u8 *)&g.d_00634160)),10,0xc0,(iptr)&local_554);
  if (iVar2 == 0) {
    iVar2 = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,ADDR(0x63416c, ((u8 *)&g.d_0063416c)),10,0xc0,(iptr)&local_554);
    if (iVar2 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,ADDR(0x634178, ((u8 *)&g.d_00634178)),10,0xc0,(iptr)&local_554);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_558 = 0xd3;
  for (local_14 = 0; local_14 < 4; local_14++) {
    local_120 = 0x157;
    for (local_18 = 0; local_18 < 5; local_18++) {
      bVar1 = sprite_get_key_color
                        ((Sprite *)(&advance_category_icon_sprites + local_18 * 0xf0 + local_14 * 0x3c));
      uVar5 = (uint)bVar1;
      iVar3 = sprite_height
                        ((Sprite *)(&advance_category_icon_sprites + local_18 * 0xf0 + local_14 * 0x3c));
      uVar4 = sprite_width
                        ((Sprite *)(&advance_category_icon_sprites + local_18 * 0xf0 + local_14 * 0x3c));
      gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_120,local_558,uVar4,iVar3,uVar5);
      sprite_draw
                ((Sprite *)(&advance_category_icon_sprites + local_18 * 0xf0 + local_14 * 0x3c),
                 (iptr)local_568,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_120,local_558);
      local_120 += 0x25;
    }
    local_558 += 0x15;
  }
  __chdir(&scenario_dir_path);
  iVar2 = file_exists(ADDR(0x634184, ((u8 *)&g.d_00634184)));
  if (iVar2 != 0) {
    iVar2 = crt_remove(s_ICONS_BMP_00634190);
    if (iVar2 != 0) goto LAB_00571b80;
  }
  gfx_save_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x63419c, ((u8 *)&g.d_0063419c)),10,0xc0,(iptr)&local_554);
LAB_00571b80:
  __chdir(local_11c);
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00571baa */ { palette_destroy((GamePalette *)((iptr)&local_554)); }
  return;
}
#undef local_568
#undef local_558
#undef local_554
#undef local_120
#undef local_11c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00571bce auto */
#define local_598 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_588 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_578 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_568 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_558 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_554 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_550 (*(GamePalette *)(frame_ + FRAME_OFF(72)))
#define local_11c (*(int *)(frame_ + FRAME_OFF(1148)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(1152)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1412)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1416)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1420)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1424)))
void __cdecl sprite_sheet_save_building_icons(void)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(1432)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_550);
  local_8 = 0;
  __getcwd(local_118,0x104);
  __chdir(&scenario_dir_path);
  iVar2 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x6341a8, ((u8 *)&g.d_006341a8)),10,0xc0,(iptr)&local_550);
  if (iVar2 == 0) {
    iVar2 = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,ADDR(0x6341b4, ((u8 *)&g.d_006341b4)),10,0xc0,(iptr)&local_550);
    if (iVar2 == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,ADDR(0x6341c0, ((u8 *)&g.d_006341c0)),10,0xc0,(iptr)&local_550);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  local_11c = 0x157;
  local_554 = 1;
  local_558 = 0;
  for (local_14 = 1; local_14 < 0x27; local_14++) {
    bVar1 = sprite_get_key_color((Sprite *)(&improvement_icon_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&improvement_icon_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&improvement_icon_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_11c,local_554,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&improvement_icon_sprites + local_14 * 0x3c),(iptr)local_568,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_11c
               ,local_554);
    local_11c += 0x25;
    local_558++;
    if (7 < local_558) {
      local_558 = 0;
      local_554 += 0x15;
      local_11c = 0x157;
    }
  }
  local_11c = 0x157;
  local_554 = 0x6a;
  local_558 = 0;
  for (local_14 = 0; local_14 < 0x1c; local_14++) {
    bVar1 = sprite_get_key_color((Sprite *)(&wonder_icon_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&wonder_icon_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&wonder_icon_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_11c,local_554,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&wonder_icon_sprites + local_14 * 0x3c),(iptr)local_578,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_11c
               ,local_554);
    local_11c += 0x25;
    local_558++;
    if (6 < local_558) {
      local_558 = 0;
      local_554 += 0x15;
      local_11c = 0x157;
    }
  }
  bVar1 = sprite_get_key_color((Sprite *)&map_cursor_sprite);
  uVar5 = (uint)bVar1;
  iVar3 = sprite_height((Sprite *)&map_cursor_sprite);
  uVar4 = sprite_width((Sprite *)&map_cursor_sprite);
  gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),199,0x100,uVar4,iVar3,uVar5);
  sprite_draw((Sprite *)&map_cursor_sprite,(iptr)local_588,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),199,0x100);
  local_11c = 1;
  local_554 = 0x164;
  for (local_14 = 0; local_14 < 8; local_14++) {
    bVar1 = sprite_get_key_color((Sprite *)(&explosion_sprites + local_14 * 0x3c));
    uVar5 = (uint)bVar1;
    iVar3 = sprite_height((Sprite *)(&explosion_sprites + local_14 * 0x3c));
    uVar4 = sprite_width((Sprite *)(&explosion_sprites + local_14 * 0x3c));
    gfx_fill_rect_xywh(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_11c,local_554,uVar4,iVar3,uVar5);
    sprite_draw
              ((Sprite *)(&explosion_sprites + local_14 * 0x3c),(iptr)local_598,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),local_11c
               ,local_554);
    local_11c += 0x21;
  }
  __chdir(&scenario_dir_path);
  iVar2 = file_exists(ADDR(0x6341cc, ((u8 *)&g.d_006341cc)));
  if (iVar2 != 0) {
    iVar2 = crt_remove(s_ICONS_BMP_006341d8);
    if (iVar2 != 0) goto LAB_0057203b;
  }
  gfx_save_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),ADDR(0x6341e4, ((u8 *)&g.d_006341e4)),10,0xc0,(iptr)&local_550);
LAB_0057203b:
  __chdir(local_118);
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00572065 */ { palette_destroy((GamePalette *)((iptr)&local_550)); }
  return;
}
#undef local_598
#undef local_588
#undef local_578
#undef local_568
#undef local_558
#undef local_554
#undef local_550
#undef local_11c
#undef local_118
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00572089 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define sprite_editor_style_flags_i32 (*(i32 *)((u8 *)&g.d_006ac2c4))
#define sprite_editor_caption_button_count_i32 (*(i32 *)((u8 *)&g.d_006ac3ac))
#define sprite_editor_caption_button_cb_i32 (*(i32 *)((u8 *)&g.d_006ac458))
#define sprite_editor_title_font_i32 (*(i32 *)((u8 *)&g.d_006ac47c))
#define sprite_editor_title_small_font_i32 (*(i32 *)((u8 *)&g.d_006ac480))
#define sprite_editor_text_font_i32 (*(i32 *)((u8 *)&g.d_006ac484))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
/* WARNING: Removing unreachable block (ram,0x0057228e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
sprite_editor_create_window(int param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    crt_strcpy(&sprite_editor_title,&sprite_editor_default_title);
  }
  else {
    crt_strcpy(&sprite_editor_title,param_1);
  }
  sprite_editor_text_font_i32 = &ui_text_font;
  sprite_editor_title_font_i32 = &caption_font;
  sprite_editor_title_small_font_i32 = &caption_small_font;
  sprite_editor_style_flags_i32 = param_2;
  sprite_editor_caption_height = param_8;
  sprite_editor_border_width = param_9;
  sprite_editor_resize_border = param_7;
  sprite_editor_caption_button_count_i32 = 0;
  sprite_editor_caption_button_cb_i32 = 0;
  if ((param_2 & 4) != 0) {
    sprite_editor_caption_height = frame_caption_height;
    sprite_editor_border_width = frame_border_width;
  }
  if ((param_2 & 8) == 0) {
    local_8 = 0x202;
  }
  else {
    local_8 = 0x802;
  }
  if (sprite_editor_caption_height != 0) {
    local_8 = local_8 | 0x400;
  }
  if (param_7 != 0) {
    local_8 = local_8 | 0x1000;
  }
  if ((param_2 & 2) == 0) {
    param_5 += sprite_editor_border_width * 2;
    param_6 = param_6 + sprite_editor_caption_height + sprite_editor_border_width;
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
            ((DibSurface *)&sprite_editor_window,0,local_8,param_3,param_4,param_5,param_6,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),
             local_c);
  if (sprite_editor_caption_height != 0) {
    wnd_set_caption_height((WndBase *)&sprite_editor_wnd,sprite_editor_caption_height);
  }
  if (sprite_editor_resize_border != 0) {
    wnd_set_resize_border((WndBase *)&sprite_editor_wnd,sprite_editor_resize_border);
  }
  frame_wnd_layout((FrameWindow *)&sprite_editor_window);
  dlg_set_parent_window(ADDR(0x6ac1f8, ((u8 *)&g.d_006ac1f8)));
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef sprite_editor_style_flags_i32
#undef sprite_editor_caption_button_count_i32
#undef sprite_editor_caption_button_cb_i32
#undef sprite_editor_title_font_i32
#undef sprite_editor_title_small_font_i32
#undef sprite_editor_text_font_i32
#undef local_c
#undef local_8

/* 005722ab auto */
#define sprite_editor_flag_x (*(i32 *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(i32 *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(iptr *)((u8 *)&g.d_006ac87c))
#define sprite_editor_ok_callback (*(code * *)((u8 *)&g.d_006ac888))
#define sprite_editor_running (*(i32 *)((u8 *)&g.d_006ac88c))
#define sprite_editor_width (*(iptr *)((u8 *)&g.d_006ac878))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl sprite_editor_ok_clicked(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,0,0,sprite_editor_width,sprite_editor_height);
  surface_replace_color_clip((DibSurface *)&sprite_editor_surface,0x109,0x107);
  sprite_grab_surface_rect(sprite_editor_target_sprite,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),(iptr)local_14);
  *(i32 *)(&unit_shield_x_offsets + *(int *)(active_editor_wnd + 0x2ec) * 4) = sprite_editor_flag_x;
  *(i32 *)(&unit_shield_y_offsets + *(int *)(active_editor_wnd + 0x2ec) * 4) = sprite_editor_flag_y;
  if (sprite_editor_ok_callback != (code *)0x0) {
    (*sprite_editor_ok_callback)();
  }
  sprite_editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)&sprite_editor_wnd);
  wnd_repaint((SurfaceWindow *)&map_views);
  return;
}
#undef sprite_editor_flag_x
#undef sprite_editor_flag_y
#undef sprite_editor_height
#undef sprite_editor_ok_callback
#undef sprite_editor_running
#undef sprite_editor_width
#undef local_14

/* 00572364 auto */
#define sprite_editor_running (*(i32 *)((u8 *)&g.d_006ac88c))
void __cdecl sprite_editor_cancel_clicked(void)

{
  sprite_editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)&sprite_editor_wnd);
  return;
}
#undef sprite_editor_running

/* 00572389 auto */
#define sprite_editor_flag_x (*(i32 *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(i32 *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(iptr *)((u8 *)&g.d_006ac87c))
#define sprite_editor_undo_flag_x (*(i32 *)((u8 *)&g.d_006ac0a4))
#define sprite_editor_undo_flag_y (*(i32 *)((u8 *)&g.d_006ac0a0))
#define sprite_editor_width (*(iptr *)((u8 *)&g.d_006ac878))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl sprite_editor_rebuild_sprite(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_free((Sprite *)&sprite_editor_result_sprite);
  rect_set_xywh((iptr)local_14,0,0,sprite_editor_width,sprite_editor_height);
  sprite_grab_rect((Sprite *)&sprite_editor_result_sprite,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0xfe,(iptr)local_14);
  sprite_editor_undo_flag_x = sprite_editor_flag_x;
  sprite_editor_undo_flag_y = sprite_editor_flag_y;
  return;
}
#undef sprite_editor_flag_x
#undef sprite_editor_flag_y
#undef sprite_editor_height
#undef sprite_editor_undo_flag_x
#undef sprite_editor_undo_flag_y
#undef sprite_editor_width
#undef local_14

/* 005723ee auto */
#define sprite_editor_key_color (*(int *)((u8 *)&g.d_006ac874))
#define sprite_sheet_mode (*(int *)((u8 *)&g.d_006ac924))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl sprite_editor_draw_swatches(void)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (sprite_editor_right_color == 0) {
    local_18 = sprite_editor_key_color;
  }
  else {
    local_18 = sprite_editor_right_color;
  }
  gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x142,sprite_editor_origin_y + 0xac,0x20,0x20,local_18);
  gfx_draw_frame_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x142,sprite_editor_origin_y + 0xac,0x20,0x20,10);
  if (sprite_editor_left_color == 0) {
    local_1c = sprite_editor_key_color;
  }
  else {
    local_1c = sprite_editor_left_color;
  }
  gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x14a,sprite_editor_origin_y + 0xb4,0x10,0x10,local_1c);
  gfx_draw_frame_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x14a,sprite_editor_origin_y + 0xb4,0x10,0x10,10);
  if (sprite_editor_prev_left_color == 0) {
    local_20 = sprite_editor_key_color;
  }
  else {
    local_20 = sprite_editor_prev_left_color;
  }
  gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x11e,sprite_editor_origin_y + 0xac,0x20,0x20,local_20);
  gfx_draw_frame_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x11e,sprite_editor_origin_y + 0xac,0x20,0x20,10);
  if (sprite_sheet_mode != 0xb) {
    if (sprite_editor_prev_right_color == 0) {
      local_24 = sprite_editor_key_color;
    }
    else {
      local_24 = sprite_editor_prev_right_color;
    }
    gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x166,sprite_editor_origin_y + 0xac,0x20,0x20,local_24);
    gfx_draw_frame_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 0x166,sprite_editor_origin_y + 0xac,0x20,0x20,10);
  }
  rect_set_xywh((iptr)local_14,sprite_editor_origin_x + 0x11e,sprite_editor_origin_y + 0xac,0x68,0x20);
  wnd_blit_surface_rect((DibSurface *)&sprite_editor_window,(iptr)local_14);
  return;
}
#undef sprite_editor_key_color
#undef sprite_sheet_mode
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 0057261a auto */
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl sprite_editor_draw_palette_cell(iptr param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((9 < param_4) && (param_4 < 0xca)) {
    uVar3 = (int)(param_4 - 10U) >> 0x1f;
    iVar1 = ((param_4 - 10U ^ uVar3) - uVar3 & 0x1f ^ uVar3) - uVar3;
    iVar2 = (int)(param_4 - 10 + (param_4 - 10 >> 0x1f & 0x1fU)) >> 5;
    rect_set_xywh((iptr)local_14,iVar1 * 0xc + param_2,iVar2 * 0xc + param_3,10,10);
    gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),(iptr)local_14,param_4);
    gfx_draw_bevel_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),(iptr)local_14,10,10);
    rect_set_xywh((iptr)local_14,iVar1 * 0xc + param_2 - 1,iVar2 * 0xc + param_3 - 1,0xc,0xc)
    ;
    if ((param_4 == sprite_editor_right_color) || (param_4 == sprite_editor_left_color)) {
      gfx_draw_bevel_rect(param_1,(iptr)local_14,0x29,0x29);
    }
    else {
      gfx_draw_bevel_rect(param_1,(iptr)local_14,0x1d,0x1d);
    }
    wnd_blit_surface_rect((DibSurface *)param_1,(iptr)local_14);
  }
  return;
}
#undef local_14

/* 00572740 auto */
int __cdecl sprite_editor_tool_hit_test(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 - 0x11e;
  iVar1 = param_2 - 0x14;
  if ((((iVar2 < 0) || (0x6c < iVar2)) || (iVar1 < 0)) ||
     (((0xbe < iVar1 || (0x20 < iVar2 % 0x24)) || (0x20 < iVar1 % 0x26)))) {
    iVar2 = -1;
  }
  else {
    iVar2 = iVar2 / 0x24 + (iVar1 / 0x26) * 3;
  }
  return iVar2;
}

/* 005727d8 auto */
#define sprite_editor_key_color (*(i32 *)((u8 *)&g.d_006ac874))
#define sprite_sheet_mode (*(i32 *)((u8 *)&g.d_006ac924))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl sprite_editor_draw_backdrop(void)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_fill((DibSurface *)&sprite_editor_surface,sprite_editor_key_color);
  switch(sprite_sheet_mode) {
  case 1:
  case 2:
  case 0xb:
    sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)local_14,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0,0);
    break;
  case 5:
  case 7:
  case 8:
  case 10:
    sprite_draw((Sprite *)&editor_tile_backdrop_sprite,(iptr)local_24,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0,0);
  case 3:
  case 4:
  case 6:
  case 9: ;
  }
  return;
}
#undef sprite_editor_key_color
#undef sprite_sheet_mode
#undef local_24
#undef local_14

/* 00572887 auto */
#define sprite_editor_brush_size (*(int *)((u8 *)&g.d_006ac124))
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_key_color (*(int *)((u8 *)&g.d_006ac874))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define local_3c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(44)))
i8 * __cdecl sprite_editor_plot_pixel(int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (sprite_editor_brush_size == 0) {
    if (sprite_editor_paint_color == 0) {
      local_18 = sprite_editor_key_color;
    }
    else {
      local_18 = sprite_editor_paint_color;
    }
    surface_set_pixel((DibSurface *)&sprite_editor_surface,param_1,param_2,local_18);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0x10,sprite_editor_origin_y + param_2 * 4 + 0x10,
                       4,4);
    if (sprite_editor_paint_color == 0) {
      local_1c = sprite_editor_key_color;
    }
    else {
      local_1c = sprite_editor_paint_color;
    }
    gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_1c);
  }
  else if (sprite_editor_brush_size == 1) {
    surface_get_clip((DibSurface *)&sprite_editor_window,(iptr)local_14);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),sprite_editor_origin_x + 0x10,sprite_editor_origin_y + 0x10,sprite_editor_width << 2,
                       sprite_editor_height << 2);
    surface_set_clip((DibSurface *)&sprite_editor_window,ADDR(0x6ac108, ((u8 *)&g.d_006ac108)));
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 - 1,param_2,3,1);
    if (sprite_editor_paint_color == 0) {
      local_20 = sprite_editor_key_color;
    }
    else {
      local_20 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_20);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0xc,sprite_editor_origin_y + param_2 * 4 + 0x10,
                       0xc,4);
    if (sprite_editor_paint_color == 0) {
      local_24 = sprite_editor_key_color;
    }
    else {
      local_24 = sprite_editor_paint_color;
    }
    gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_24);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1,param_2 - 1,1,3);
    if (sprite_editor_paint_color == 0) {
      local_28 = sprite_editor_key_color;
    }
    else {
      local_28 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_28);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0x10,param_2 * 4 + sprite_editor_origin_y + 0xc,4
                       ,0xc);
    if (sprite_editor_paint_color == 0) {
      local_2c = sprite_editor_key_color;
    }
    else {
      local_2c = sprite_editor_paint_color;
    }
    gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_2c);
    surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)local_14);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0xc,param_2 * 4 + sprite_editor_origin_y + 0xc,
                       0xc,0xc);
  }
  else if (sprite_editor_brush_size == 2) {
    surface_get_clip((DibSurface *)&sprite_editor_window,(iptr)local_14);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),sprite_editor_origin_x + 0x10,sprite_editor_origin_y + 0x10,sprite_editor_width << 2,
                       sprite_editor_height << 2);
    surface_set_clip((DibSurface *)&sprite_editor_window,ADDR(0x6ac108, ((u8 *)&g.d_006ac108)));
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 - 1,param_2,4,2);
    if (sprite_editor_paint_color == 0) {
      local_30 = sprite_editor_key_color;
    }
    else {
      local_30 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_30);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0xc,sprite_editor_origin_y + param_2 * 4 + 0x10,
                       0x10,8);
    if (sprite_editor_paint_color == 0) {
      local_34 = sprite_editor_key_color;
    }
    else {
      local_34 = sprite_editor_paint_color;
    }
    gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_34);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1,param_2 - 1,2,4);
    if (sprite_editor_paint_color == 0) {
      local_38 = sprite_editor_key_color;
    }
    else {
      local_38 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_38);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0x10,param_2 * 4 + sprite_editor_origin_y + 0xc,8
                       ,0x10);
    if (sprite_editor_paint_color == 0) {
      local_3c = sprite_editor_key_color;
    }
    else {
      local_3c = sprite_editor_paint_color;
    }
    gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),local_3c);
    surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)local_14);
    rect_set_xywh(ADDR(0x6ac108, ((u8 *)&g.d_006ac108)),param_1 * 4 + sprite_editor_origin_x + 0xc,param_2 * 4 + sprite_editor_origin_y + 0xc,
                       0x10,0x10);
  }
  return &sprite_editor_plot_rect;
}
#undef sprite_editor_brush_size
#undef sprite_editor_height
#undef sprite_editor_key_color
#undef sprite_editor_width
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

/* 00572da0 auto */
#define sprite_editor_flag_x (*(int *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(int *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl sprite_editor_draw_flag_marker(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_repaint((SurfaceWindow *)&sprite_editor_window);
  iVar1 = sprite_editor_flag_y;
  local_8 = sprite_editor_flag_x;
  surface_get_clip((DibSurface *)&sprite_editor_window,(iptr)local_18);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),sprite_editor_origin_x + 0x10,sprite_editor_origin_y + 0x10,sprite_editor_width << 2,
                     sprite_editor_height << 2);
  surface_set_clip((DibSurface *)&sprite_editor_window,ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)));
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),sprite_editor_origin_x + 0x20,sprite_editor_origin_y + 0x10,4,0x3c);
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),0x6a);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),sprite_editor_origin_x + 0x20,sprite_editor_origin_y + 0x4c,0xb4,4);
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),0x6a);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),sprite_editor_origin_x + 0xd0,sprite_editor_origin_y + 0x10,4,0x3c);
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),0x6a);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),local_8 * 4 + sprite_editor_origin_x + 8,sprite_editor_origin_y + iVar1 * 4 + 0x10,0x14,4)
  ;
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),10);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),local_8 * 4 + sprite_editor_origin_x + 0x10,iVar1 * 4 + sprite_editor_origin_y + 8,4,0x14)
  ;
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),10);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),local_8 * 4 + sprite_editor_origin_x + 9,sprite_editor_origin_y + iVar1 * 4 + 0x11,0x12,2)
  ;
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),0x29);
  rect_set_xywh(ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),local_8 * 4 + sprite_editor_origin_x + 0x11,iVar1 * 4 + sprite_editor_origin_y + 9,2,0x12)
  ;
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac0f8, ((u8 *)&g.d_006ac0f8)),0x29);
  surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)local_18);
  wnd_blit_surface((DibSurface *)&sprite_editor_window);
  return;
}
#undef sprite_editor_flag_x
#undef sprite_editor_flag_y
#undef sprite_editor_height
#undef sprite_editor_width
#undef local_18
#undef local_8

/* 00572fff auto */
#define sprite_editor_brush_size (*(i32 *)((u8 *)&g.d_006ac124))
#define sprite_editor_cursor_id (*(i32 *)((u8 *)&g.d_006ac898))
#define sprite_editor_flag_x (*(iptr *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(iptr *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(iptr *)((u8 *)&g.d_006ac87c))
#define sprite_editor_paint_tool (*(int *)((u8 *)&g.d_006ac118))
#define sprite_editor_painting (*(i32 *)((u8 *)&g.d_006ac8a4))
#define sprite_editor_tool (*(int *)((u8 *)&g.d_006ac120))
#define sprite_editor_undo_flag_x (*(iptr *)((u8 *)&g.d_006ac0a4))
#define sprite_editor_undo_flag_y (*(iptr *)((u8 *)&g.d_006ac0a0))
#define sprite_editor_width (*(iptr *)((u8 *)&g.d_006ac878))
#define sprite_sheet_mode (*(int *)((u8 *)&g.d_006ac924))
#define local_80 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_6c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_68 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_64 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_5c (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(52)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(112)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(116)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(120)))
void __cdecl sprite_editor_on_mouse_down(int param_1,int param_2)

{
  iptr iVar1;
  iptr iVar2;
  SHORT SVar3;
  iptr iVar4;
  i32 uVar4;
  int iVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  sprite_init(&local_4c);
  local_8 = 0;
  iVar4 = wnd_get_window((WndBase *)&sprite_editor_wnd);
  SetCapture(*(HWND *)(iVar4 + 4));
  param_1 -= sprite_editor_origin_x;
  param_2 -= sprite_editor_origin_y;
  uVar4 = sprite_editor_tool_hit_test(param_1,param_2);
  iVar2 = sprite_editor_flag_x;
  iVar1 = sprite_editor_flag_y;
  switch(uVar4) {
  case 0:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    SVar3 = GetKeyState(1);
    if (((int)SVar3 & 0x8000U) != 0) {
      sprite_editor_prev_left_color = sprite_editor_left_color;
      local_70 = sprite_editor_left_color;
      sprite_editor_left_color = 0;
    }
    SVar3 = GetKeyState(2);
    if (((int)SVar3 & 0x8000U) != 0) {
      sprite_editor_prev_right_color = sprite_editor_right_color;
      local_70 = sprite_editor_right_color;
      sprite_editor_right_color = 0;
    }
    sprite_editor_draw_swatches();
    sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),sprite_editor_origin_x + 10,sprite_editor_origin_y + 0xe0,local_70);
    param_2 = 0;
    param_1 = 0;
    break;
  case 1:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = 1;
    sprite_editor_paint_tool = 1;
    break;
  case 2:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = 2;
    sprite_editor_paint_tool = 2;
    break;
  case 3:
    local_68 = sprite_editor_flag_x;
    local_6c = sprite_editor_flag_y;
    sprite_editor_flag_x = sprite_editor_undo_flag_x;
    sprite_editor_flag_y = sprite_editor_undo_flag_y;
    sprite_editor_undo_flag_x = iVar2;
    sprite_editor_undo_flag_y = iVar1;
    sprite_free(&local_4c);
    rect_set_xywh((iptr)local_5c,0,0,sprite_editor_width,sprite_editor_height);
    sprite_grab_rect(&local_4c,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0xfe,(iptr)local_5c);
    sprite_draw_keyed((Sprite *)&sprite_editor_result_sprite,(iptr)local_80,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0xfe,0,0);
    sprite_free((Sprite *)&sprite_editor_result_sprite);
    sprite_merge_onto(&local_4c,ADDR(0x6ac8a8, ((u8 *)&g.d_006ac8a8)));
    sprite_editor_redraw();
    if (sprite_editor_tool == 3) {
      sprite_editor_draw_flag_marker();
    }
    break;
  case 4:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = 0;
    break;
  case 5:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_rebuild_sprite();
    sprite_editor_draw_backdrop();
    sprite_editor_redraw();
    break;
  case 6:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_rebuild_sprite();
    surface_replace_color_clip((DibSurface *)&sprite_editor_surface,sprite_editor_right_color,sprite_editor_left_color);
    sprite_editor_redraw();
    break;
  case 7:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_rebuild_sprite();
    surface_replace_color_clip((DibSurface *)&sprite_editor_surface,sprite_editor_left_color,1);
    surface_replace_color_clip((DibSurface *)&sprite_editor_surface,sprite_editor_right_color,sprite_editor_left_color);
    surface_replace_color_clip((DibSurface *)&sprite_editor_surface,1,sprite_editor_right_color);
    sprite_editor_redraw();
    break;
  case 8:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_import_sheet();
    break;
  case 9:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_brush_size = 0;
    break;
  case 10:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_brush_size = 1;
    break;
  case 0xb:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    sprite_editor_brush_size = 2;
    break;
  case 0xc:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    SVar3 = GetKeyState(1);
    iVar5 = sprite_editor_left_color;
    if (((int)SVar3 & 0x8000U) != 0) {
      local_70 = sprite_editor_left_color;
      sprite_editor_left_color = sprite_editor_prev_left_color;
      local_60 = sprite_editor_prev_left_color;
      sprite_editor_prev_left_color = iVar5;
    }
    SVar3 = GetKeyState(2);
    iVar5 = sprite_editor_right_color;
    if (((int)SVar3 & 0x8000U) != 0) {
      local_70 = sprite_editor_right_color;
      sprite_editor_right_color = sprite_editor_prev_left_color;
      local_60 = sprite_editor_prev_left_color;
      sprite_editor_prev_right_color = iVar5;
    }
    sprite_editor_draw_swatches();
    iVar5 = sprite_editor_origin_x + 10;
    iVar6 = sprite_editor_origin_y + 0xe0;
    sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_70);
    sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_60);
    param_2 = 0;
    param_1 = 0;
    break;
  case 0xd:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    break;
  case 0xe:
    if (sprite_sheet_mode == 0xb) {
      sprite_editor_rebuild_sprite();
      sprite_editor_tool = 3;
      sprite_editor_flag_x = int_clamp(sprite_editor_flag_x,5,0x2f);
      sprite_editor_flag_y = int_clamp(sprite_editor_flag_y,0,0xe);
      sprite_editor_draw_flag_marker();
    }
    else {
      if (sprite_editor_tool == 3) {
        wnd_repaint((SurfaceWindow *)&sprite_editor_window);
      }
      sprite_editor_tool = sprite_editor_paint_tool;
      SVar3 = GetKeyState(1);
      iVar5 = sprite_editor_left_color;
      if (((int)SVar3 & 0x8000U) != 0) {
        local_70 = sprite_editor_left_color;
        sprite_editor_left_color = sprite_editor_prev_right_color;
        local_60 = sprite_editor_prev_right_color;
        sprite_editor_prev_left_color = iVar5;
      }
      SVar3 = GetKeyState(2);
      iVar5 = sprite_editor_right_color;
      if (((int)SVar3 & 0x8000U) != 0) {
        local_70 = sprite_editor_right_color;
        sprite_editor_right_color = sprite_editor_prev_right_color;
        local_60 = sprite_editor_prev_right_color;
        sprite_editor_prev_right_color = iVar5;
      }
      sprite_editor_draw_swatches();
      iVar5 = sprite_editor_origin_x + 10;
      iVar6 = sprite_editor_origin_y + 0xe0;
      sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_70);
      sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_60);
      param_2 = 0;
      param_1 = 0;
    }
  }
  if ((((param_1 < 9) || (0x187 < param_1)) || (param_2 < 0xdf)) || (0x125 < param_2)) {
    if (((0xf < param_1) && (param_1 < sprite_editor_width * 4 + 0x10)) &&
       ((0xf < param_2 && (param_2 < sprite_editor_height * 4 + 0x10)))) {
      switch(sprite_editor_tool) {
      case 0:
        local_60 = surface_get_pixel
                             ((DibSurface *)&sprite_editor_surface,param_1 - 0x10 >> 2,
                              param_2 - 0x10 >> 2);
        SVar3 = GetKeyState(1);
        if (((int)SVar3 & 0x8000U) == 0) {
          SVar3 = GetKeyState(2);
          if (((int)SVar3 & 0x8000U) != 0) {
            sprite_editor_prev_right_color = sprite_editor_right_color;
            local_70 = sprite_editor_right_color;
            sprite_editor_right_color = local_60;
          }
        }
        else {
          sprite_editor_prev_left_color = sprite_editor_left_color;
          local_70 = sprite_editor_left_color;
          sprite_editor_left_color = local_60;
        }
        sprite_editor_draw_swatches();
        iVar5 = sprite_editor_origin_x + 10;
        iVar6 = sprite_editor_origin_y + 0xe0;
        sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_70);
        sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_60);
        if (sprite_editor_tool == 3) {
          wnd_repaint((SurfaceWindow *)&sprite_editor_window);
        }
        sprite_editor_tool = sprite_editor_paint_tool;
        sprite_editor_cursor_id = 0x204;
        wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x204);
        ui_flush_input();
        break;
      case 1:
      case 2:
        sprite_editor_rebuild_sprite();
        sprite_editor_painting = 1;
        iVar5 = (int)(param_1 - 0x10 + (param_1 - 0x10 >> 0x1f & 3U)) >> 2;
        iVar6 = (int)(param_2 - 0x10 + (param_2 - 0x10 >> 0x1f & 3U)) >> 2;
        sprite_editor_last_px = iVar5;
        sprite_editor_last_py = iVar6;
        SVar3 = GetKeyState(1);
        if (((int)SVar3 & 0x8000U) == 0) {
          SVar3 = GetKeyState(2);
          if (((int)SVar3 & 0x8000U) != 0) {
            sprite_editor_paint_color = sprite_editor_right_color;
          }
        }
        else {
          sprite_editor_paint_color = sprite_editor_left_color;
        }
        local_64 = sprite_editor_plot_pixel(iVar5,iVar6);
        wnd_blit_surface_rect((DibSurface *)&sprite_editor_window,local_64);
        break;
      case 3:
        sprite_editor_rebuild_sprite();
        sprite_editor_flag_x = int_clamp((int)(param_1 - 0x10 + (param_1 - 0x10 >> 0x1f & 3U)) >>
                                          2,5,0x2f);
        sprite_editor_flag_y = int_clamp((int)(param_2 - 0x10 + (param_2 - 0x10 >> 0x1f & 3U)) >>
                                          2,0,0xe);
        sprite_editor_draw_flag_marker();
      }
    }
  }
  else {
    SVar3 = GetKeyState(1);
    if (((int)SVar3 & 0x8000U) == 0) {
      SVar3 = GetKeyState(2);
      if (((int)SVar3 & 0x8000U) != 0) {
        sprite_editor_prev_right_color = sprite_editor_right_color;
        local_70 = sprite_editor_right_color;
        sprite_editor_right_color = ((param_2 - 0xdf) / 0xc) * 0x20 + (param_1 - 9) / 0xc + 10;
        local_60 = sprite_editor_right_color;
      }
    }
    else {
      sprite_editor_prev_left_color = sprite_editor_left_color;
      local_70 = sprite_editor_left_color;
      sprite_editor_left_color = ((param_2 - 0xdf) / 0xc) * 0x20 + (param_1 - 9) / 0xc + 10;
      local_60 = sprite_editor_left_color;
    }
    sprite_editor_draw_swatches();
    iVar5 = sprite_editor_origin_x + 10;
    iVar6 = sprite_editor_origin_y + 0xe0;
    sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_70);
    sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),iVar5,iVar6,local_60);
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00573adc */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  return;
}
#undef sprite_editor_brush_size
#undef sprite_editor_cursor_id
#undef sprite_editor_flag_x
#undef sprite_editor_flag_y
#undef sprite_editor_height
#undef sprite_editor_paint_tool
#undef sprite_editor_painting
#undef sprite_editor_tool
#undef sprite_editor_undo_flag_x
#undef sprite_editor_undo_flag_y
#undef sprite_editor_width
#undef sprite_sheet_mode
#undef local_80
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00573afd auto */
#define sprite_editor_painting (*(i32 *)((u8 *)&g.d_006ac8a4))
void __cdecl sprite_editor_on_mouse_up(void)

{
  sprite_editor_painting = 0;
  ReleaseCapture();
  return;
}
#undef sprite_editor_painting

/* 00573b1d auto */
#define sprite_editor_cursor_id (*(int *)((u8 *)&g.d_006ac898))
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_painting (*(int *)((u8 *)&g.d_006ac8a4))
#define sprite_editor_tool (*(int *)((u8 *)&g.d_006ac120))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl sprite_editor_on_mouse_move(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  param_1 -= sprite_editor_origin_x;
  param_2 -= sprite_editor_origin_y;
  if ((((param_1 < 9) || (0x187 < param_1)) || (param_2 < 0xdf)) || (0x125 < param_2)) {
    if (((param_1 < 0x10) || (sprite_editor_width * 4 + 0x10 <= param_1)) ||
       ((param_2 < 0x10 || (sprite_editor_height * 4 + 0x10 <= param_2)))) {
      if (sprite_editor_cursor_id != 0x201) {
        sprite_editor_cursor_id = 0x201;
        wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x201);
        ui_flush_input();
      }
      sprite_editor_last_py = -1;
      sprite_editor_last_px = -1;
      iVar1 = sprite_editor_last_px;
      iVar2 = sprite_editor_last_py;
    }
    else {
      if (sprite_editor_tool == 0) {
        if (sprite_editor_cursor_id != 0x205) {
          sprite_editor_cursor_id = 0x205;
          wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x205);
          ui_flush_input();
        }
      }
      else if (((0 < sprite_editor_tool) && (sprite_editor_tool < 3)) && (sprite_editor_cursor_id != 0x204)) {
        sprite_editor_cursor_id = 0x204;
        wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x204);
        ui_flush_input();
      }
      iVar1 = sprite_editor_last_px;
      iVar2 = sprite_editor_last_py;
      if (sprite_editor_painting != 0) {
        iVar1 = (int)(param_1 - 0x10 + (param_1 - 0x10 >> 0x1f & 3U)) >> 2;
        iVar2 = (int)(param_2 - 0x10 + (param_2 - 0x10 >> 0x1f & 3U)) >> 2;
        if (sprite_editor_tool == 1) {
          if ((sprite_editor_last_px < 0) || (sprite_editor_last_py < 0)) {
            sprite_editor_last_px = iVar1;
            sprite_editor_last_py = iVar2;
          }
          iVar4 = iVar1 - sprite_editor_last_px;
          iVar5 = iVar2 - sprite_editor_last_py;
          local_8 = -1;
          local_18 = -1;
          local_10 = sprite_editor_last_px << 8;
          local_14 = sprite_editor_last_py << 8;
          while( true ) {
            iVar6 = local_10 >> 8;
            iVar7 = local_14 >> 8;
            if ((iVar6 == iVar1) && (iVar7 == iVar2)) break;
            if ((iVar6 != local_18) || (iVar7 != local_8)) {
              sprite_editor_plot_pixel(iVar6,iVar7);
              local_18 = iVar6;
              local_8 = iVar7;
            }
            local_10 += iVar4;
            local_14 += iVar5;
          }
          wnd_blit_surface((DibSurface *)&sprite_editor_window);
        }
        else if (sprite_editor_tool == 2) {
          iVar3 = sprite_editor_plot_pixel(iVar1,iVar2);
          wnd_blit_surface_rect((DibSurface *)&sprite_editor_window,iVar3);
        }
      }
    }
  }
  else {
    iVar1 = sprite_editor_last_px;
    iVar2 = sprite_editor_last_py;
    if (sprite_editor_cursor_id != 0x205) {
      sprite_editor_cursor_id = 0x205;
      wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x205);
      ui_flush_input();
      iVar1 = sprite_editor_last_px;
      iVar2 = sprite_editor_last_py;
    }
  }
  sprite_editor_last_py = iVar2;
  sprite_editor_last_px = iVar1;
  return;
}
#undef sprite_editor_cursor_id
#undef sprite_editor_height
#undef sprite_editor_painting
#undef sprite_editor_tool
#undef sprite_editor_width
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 00573e59 auto */
#define sprite_editor_brush_size (*(i32 *)((u8 *)&g.d_006ac124))
#define sprite_editor_cursor_id (*(i32 *)((u8 *)&g.d_006ac898))
#define sprite_editor_flag_x (*(i32 *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(i32 *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(i32 *)((u8 *)&g.d_006ac87c))
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define sprite_editor_ok_callback (*(iptr *)((u8 *)&g.d_006ac888))
#define sprite_editor_paint_tool (*(i32 *)((u8 *)&g.d_006ac118))
#define sprite_editor_painting (*(i32 *)((u8 *)&g.d_006ac8a4))
#define sprite_editor_running (*(int *)((u8 *)&g.d_006ac88c))
#define sprite_editor_tool (*(i32 *)((u8 *)&g.d_006ac120))
#define sprite_editor_undo_flag_x (*(i32 *)((u8 *)&g.d_006ac0a4))
#define sprite_editor_undo_flag_y (*(i32 *)((u8 *)&g.d_006ac0a0))
#define sprite_editor_width (*(i32 *)((u8 *)&g.d_006ac878))
#define sprite_sheet_mode (*(i32 *)((u8 *)&g.d_006ac924))
#define sprite_editor_client_height_i32 (*(i32 *)((u8 *)&g.d_006ac2e0))
#define local_b8 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_a4 (*(Control *)(frame_ + FRAME_OFF(20)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_5c (*(i8 (*)[16])(frame_ + FRAME_OFF(92)))
#define local_4c (*(Control *)(frame_ + FRAME_OFF(108)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(168)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(172)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(176)))
/* WARNING: Removing unreachable block (ram,0x0057405e) */
/* WARNING: Removing unreachable block (ram,0x005740e7) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl sprite_editor_run(iptr param_1,i32 param_2,i32 param_3,iptr param_4)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(184)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  button_ctor(&local_4c);
  local_8 = 0;
  button_ctor(&local_a4);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  sprite_sheet_mode = param_3;
  sprite_editor_target_sprite = (Sprite *)param_1;
  sprite_editor_width = sprite_width((Sprite *)param_1);
  sprite_editor_height = sprite_height(sprite_editor_target_sprite);
  bVar1 = sprite_get_key_color(sprite_editor_target_sprite);
  sprite_editor_key_color = (uint)bVar1;
  sprite_editor_ok_callback = param_4;
  sprite_free((Sprite *)&sprite_editor_orig_sprite);
  sprite_merge_onto(sprite_editor_target_sprite,ADDR(0x6ac170, ((u8 *)&g.d_006ac170)));
  surface_create((DibSurface *)&sprite_editor_surface,sprite_editor_width,sprite_editor_height);
  sprite_editor_draw_backdrop();
  sprite_draw((Sprite *)&sprite_editor_orig_sprite,(iptr)local_b8,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0,0);
  sprite_editor_undo_flag_x = *(i32 *)(&unit_shield_x_offsets + *(int *)(active_editor_wnd + 0x2ec) * 4);
  sprite_editor_undo_flag_y = *(i32 *)(&unit_shield_y_offsets + *(int *)(active_editor_wnd + 0x2ec) * 4);
  sprite_editor_flag_y = sprite_editor_undo_flag_y;
  sprite_editor_flag_x = sprite_editor_undo_flag_x;
  sprite_editor_rebuild_sprite();
  sprite_editor_tool = 1;
  sprite_editor_paint_tool = 1;
  sprite_editor_brush_size = 0;
  sprite_editor_cursor_id = 0x201;
  sprite_editor_running = 1;
  sprite_editor_painting = 0;
  sprite_editor_create_window(param_2,0xd,0,0,0x192,0x14e,0,0,0);
  iVar2 = font_line_spacing((GameFont *)dialog_font_ptr);
  local_68 = iVar2 + 8;
  local_60 = (sprite_editor_client_width - 6) / 2;
  local_a8 = (sprite_editor_origin_y + sprite_editor_client_height_i32) - (iVar2 + 10);
  local_64 = sprite_editor_origin_x + 2;
  rect_set_xywh((iptr)local_5c,local_64,local_a8,local_60,local_68);
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create(&local_4c,ADDR(0x6ac1f8, ((u8 *)&g.d_006ac1f8)),0x65,(iptr)local_5c,iVar3);
  button_set_callback(&local_4c,ADDR(0x401f73, sprite_editor_ok_clicked));
  local_64 = local_64 + local_60 + 2;
  rect_set_xywh((iptr)local_5c,local_64,local_a8,local_60,local_68);
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create(&local_a4,ADDR(0x6ac1f8, ((u8 *)&g.d_006ac1f8)),0x66,(iptr)local_5c,iVar3);
  button_set_callback(&local_a4,ADDR(0x4011ea, sprite_editor_cancel_clicked));
  ctrl_set_cancel_button(&local_a4);
  wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,ADDR(0x401b4f, sprite_editor_on_mouse_down));
  wnd_set_rbuttondown_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,ADDR(0x401b4f, sprite_editor_on_mouse_down));
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,ADDR(0x401b4f, sprite_editor_on_mouse_down));
  wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,ADDR(0x402013, sprite_editor_on_mouse_up));
  wnd_set_rbuttonup_any_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,ADDR(0x402013, sprite_editor_on_mouse_up));
  wnd_set_mousemove_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,ADDR(0x403c0b, sprite_editor_on_mouse_move));
  wnd_set_redraw_callback((SurfaceWindow *)&sprite_editor_window,ADDR(0x401bf9, sprite_editor_redraw));
  wnd_repaint((SurfaceWindow *)&sprite_editor_window);
  window_show((WindowObjectView *)&sprite_editor_window);
  wnd_run_modal_loop((ModalMenuWindow *)&sprite_editor_wnd);
  while (sprite_editor_running != 0) {
    win_pump_one_message();
  }
  dlg_set_parent_window(0);
  frame_wnd_close((DibSurface *)&sprite_editor_window);
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet 0057420c */ { ctrl_dtor((Control *)((iptr)&local_a4)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00574218 */ { ctrl_dtor((Control *)((iptr)&local_4c)); }
  return;
}
#undef sprite_editor_brush_size
#undef sprite_editor_cursor_id
#undef sprite_editor_flag_x
#undef sprite_editor_flag_y
#undef sprite_editor_height
#undef sprite_editor_key_color
#undef sprite_editor_ok_callback
#undef sprite_editor_paint_tool
#undef sprite_editor_painting
#undef sprite_editor_running
#undef sprite_editor_tool
#undef sprite_editor_undo_flag_x
#undef sprite_editor_undo_flag_y
#undef sprite_editor_width
#undef sprite_sheet_mode
#undef sprite_editor_client_height_i32
#undef local_b8
#undef local_a8
#undef local_a4
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00574239 auto */
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define local_50 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_40 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(60)))
void __cdecl sprite_editor_redraw(void)

{
  byte bVar1;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption((FrameWindow *)&sprite_editor_window);
  gfx_fill_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),ADDR(0x6ac46c, ((u8 *)&g.d_006ac46c)),0x1d);
  local_20 = sprite_editor_origin_x + 0x10;
  local_24 = sprite_editor_origin_y + 0x10;
  local_18 = sprite_editor_width << 2;
  local_1c = sprite_editor_height << 2;
  rect_set_xywh((iptr)local_14,0,0,sprite_editor_width,sprite_editor_height);
  sprite_grab_surface_rect((Sprite *)&sprite_editor_orig_sprite,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),(iptr)local_14);
  bVar1 = sprite_get_key_color((Sprite *)&sprite_editor_orig_sprite);
  sprite_editor_key_color = (uint)bVar1;
  gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_20,local_24,local_18,local_1c,sprite_editor_key_color);
  gfx_set_scale_ratio(4,1);
  sprite_draw_keyed
            ((Sprite *)&sprite_editor_orig_sprite,(iptr)local_40,ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),0,local_20,local_24);
  gfx_set_scale_ratio(1,1);
  gfx_draw_tiled_frame(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_20,local_24,local_18,local_1c,6);
  local_20 = sprite_editor_origin_x + 10;
  local_24 = sprite_editor_origin_y + 0xe0;
  for (local_28 = 0; local_28 < 0xc0; local_28++) {
    sprite_editor_draw_palette_cell(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_20,local_24,local_28 + 10);
  }
  local_20 = sprite_editor_origin_x + 0x11e;
  local_24 = sprite_editor_origin_y + 0x14;
  for (local_2c = 0; local_2c < 3; local_2c++) {
    for (local_30 = 0; local_30 < 5; local_30++) {
      if (local_30 == 0 && local_2c == 0) {
        gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_2c * 0x24 + local_20,local_30 * 0x26 + local_24,0x20,0x20,
                           sprite_editor_key_color);
      }
      else {
        gfx_fill_rect_xywh(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_2c * 0x24 + local_20,local_30 * 0x26 + local_24,0x20,0x20,
                           0x29);
        sprite_draw
                  ((Sprite *)(&sprite_editor_tool_sprites + (local_30 * 3 + local_2c) * 0x3c),
                   (iptr)local_50,ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_2c * 0x24 + local_20,local_30 * 0x26 + local_24);
      }
      gfx_draw_frame_rect(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)),local_2c * 0x24 + local_20,local_30 * 0x26 + local_24,0x20,0x20,10
                        );
    }
  }
  sprite_editor_draw_swatches();
  text_set_surface(ADDR(0x6ac1b0, ((u8 *)&g.d_006ac1b0)));
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  wnd_blit_surface((DibSurface *)&sprite_editor_window);
  return;
}
#undef sprite_editor_height
#undef sprite_editor_key_color
#undef sprite_editor_width
#undef local_50
#undef local_40
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 00574522 auto */
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define local_2c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall sprite_picker_draw(FrameWindow *this)

{
  byte bVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption(this);
  gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1d);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6ab1a0, ((u8 *)&g.d_006ab1a0)));
  bVar1 = sprite_get_key_color((Sprite *)&sprite_picker_sprite);
  sprite_editor_key_color = (uint)bVar1;
  local_c = sprite_width((Sprite *)&sprite_picker_sprite);
  local_c = local_c * 2;
  local_10 = sprite_height((Sprite *)&sprite_picker_sprite);
  local_10 = local_10 * 2;
  local_1c = font_line_spacing((GameFont *)dialog_font_ptr);
  local_1c += 8;
  local_8 = GetSystemMetrics(3);
  local_8 += 2;
  local_14 = this->client_x + (int)(this->client_width - local_c) / 2;
  local_18 = this->client_y + (int)((((this->client_height - local_10) - local_1c) - local_8) - 4) / 2
  ;
  gfx_fill_rect_xywh((iptr)this,local_14,local_18,local_c,local_10,sprite_editor_key_color);
  gfx_set_scale_ratio(2,1);
  sprite_draw_keyed
            ((Sprite *)&sprite_picker_sprite,(iptr)local_2c,(iptr)this,0,local_14,local_18);
  gfx_set_scale_ratio(1,1);
  gfx_draw_tiled_frame((iptr)this,local_14,local_18,local_c,local_10,6);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef sprite_editor_key_color
#undef local_2c
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00574686 auto */
#define sprite_picker_dialog (*(FrameWindow * *)((u8 *)&g.d_006ac11c))
void __cdecl sprite_picker_redraw_cb(void)

{
  sprite_picker_draw(sprite_picker_dialog);
  return;
}
#undef sprite_picker_dialog

/* 005746a1 auto */
#define sprite_sheet_mode (*(uint *)((u8 *)&g.d_006ac924))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl sprite_editor_cell_rect(uint param_1,iptr param_2,iptr param_3,iptr param_4,iptr param_5)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)param_5 = 0;
  *(i32 *)param_4 = *(i32 *)param_5;
  *(i32 *)param_3 = *(i32 *)param_4;
  *(i32 *)param_2 = *(i32 *)param_3;
  local_8 = *(i32 *)param_2;
  if (sprite_sheet_mode < 0xc) {
    uVar1 = (int)param_1 >> 0x1f;
    switch(sprite_sheet_mode) {
    case 0:
      local_8 = 0x14;
      *(int *)param_2 = ((int)(param_1 + (uVar1 & 3)) >> 2) * 0x25 + 0x157;
      *(uint *)param_3 = (((param_1 ^ uVar1) - uVar1 & 3 ^ uVar1) - uVar1) * 0x15 + 0xd3;
      *(i32 *)param_4 = 0x24;
      *(i32 *)param_5 = 0x14;
      break;
    case 1:
      if ((int)param_1 < 0x18) {
        *(i32 *)param_2 = 1;
      }
      else {
        *(i32 *)param_2 = 0x14e;
        param_1 -= 0x18;
      }
      uVar1 = (int)param_1 >> 0x1f;
      *(uint *)param_2 = *(int *)param_2 + (((param_1 ^ uVar1) - uVar1 & 3 ^ uVar1) - uVar1) * 0x41;
      *(int *)param_3 = ((int)(param_1 + (uVar1 & 3)) >> 2) * 0x31 + 0x27;
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x30;
      local_8 = 0x30;
      break;
    case 2:
      local_8 = 4;
      *(uint *)param_2 = param_1 * 0x41 + 0x8f;
      *(i32 *)param_3 = 0x1a7;
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x30;
      break;
    case 3:
      local_8 = 0x12;
      *(i32 *)param_4 = 0xe;
      *(i32 *)param_5 = 0x16;
      *(int *)param_2 = (((int)param_1 >> 1) % 9) * (*(int *)param_4 + 1) + 1;
      *(uint *)param_3 = (*(int *)param_5 + 1) * (param_1 & 1) + 0x1a9;
      break;
    case 4:
      local_8 = 0x42;
      *(i32 *)param_4 = 0x24;
      *(i32 *)param_5 = 0x14;
      if ((int)param_1 < 0x26) {
        *(uint *)param_2 = (((param_1 ^ uVar1) - uVar1 & 7 ^ uVar1) - uVar1) * 0x25 + 0x157;
        *(int *)param_3 = ((int)(param_1 + (uVar1 & 7)) >> 3) * 0x15 + 1;
      }
      else {
        *(int *)param_2 = ((int)(param_1 - 0x26) % 7) * 0x25 + 0x157;
        *(int *)param_3 = ((int)(param_1 - 0x26) / 7) * 0x15 + 0x6a;
      }
      break;
    case 5:
      local_8 = 1;
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x20;
      *(i32 *)param_2 = 199;
      *(i32 *)param_3 = 0x100;
      break;
    case 6:
      local_8 = 8;
      *(i32 *)param_4 = 0x20;
      *(i32 *)param_5 = 0x20;
      *(uint *)param_2 = (*(int *)param_4 + 1) * param_1 + 1;
      *(i32 *)param_3 = 0x164;
      break;
    case 7:
      local_8 = 0x2c;
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x20;
      *(int *)param_2 = ((int)param_1 / 0xb) * 0x41 + 1;
      *(int *)param_3 = ((int)param_1 % 0xb) * 0x21 + 1;
      break;
    case 8:
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x20;
      if ((int)param_1 < 0x40) {
        *(uint *)param_2 = (((param_1 ^ uVar1) - uVar1 & 7 ^ uVar1) - uVar1) * 0x41 + 1;
        *(uint *)param_3 =
             (((int)(((param_1 ^ uVar1) - uVar1 & 0xf ^ uVar1) - uVar1) < 8) - 1 & 0x21) +
             ((int)(param_1 + (uVar1 & 0xf)) >> 4) * 0x42 + 0x43;
      }
      else {
        *(uint *)param_2 = (param_1 - 0x40) * 0x41 + 1;
        *(i32 *)param_3 = 0x14b;
      }
      local_8 = 0x44;
      break;
    case 9:
      *(i32 *)param_4 = 0x20;
      *(i32 *)param_5 = 0x10;
      *(i32 *)param_2 = 1;
      *(i32 *)param_3 = 0x1ad;
      switch(((param_1 ^ uVar1) - uVar1 & 3 ^ uVar1) - uVar1) {
      case 0:
        break;
      case 1:
        *(int *)param_3 = *(int *)param_3 + 0x22;
        *(int *)param_2 = *(int *)param_2 + 0x21;
        break;
      case 2:
        *(int *)param_3 = *(int *)param_3 + 0x11;
        break;
      case 3:
        *(int *)param_3 = *(int *)param_3 + 0x22;
      }
      *(int *)param_2 = *(int *)param_2 + ((int)(param_1 + (uVar1 & 3)) >> 2) * 0x42;
      local_8 = 0x20;
      break;
    case 10:
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x20;
      *(i32 *)param_2 = 0x1c8;
      if ((int)param_1 < 6) {
        *(uint *)param_3 = param_1 * 0x21 + 100;
      }
      else {
        *(int *)param_2 = ((int)(param_1 - 6) % 9) * 0x41 + 1;
        *(int *)param_3 = ((int)(param_1 - 6) / 9) * 0x21 + 0x16c;
      }
      local_8 = 0x18;
      break;
    case 0xb:
      local_8 = 0x3f;
      *(int *)param_3 = ((int)param_1 / 9) * 0x31 + 1;
      *(int *)param_2 = ((int)param_1 % 9) * 0x41 + 1;
      *(i32 *)param_4 = 0x40;
      *(i32 *)param_5 = 0x30;
    }
  }
  return local_8;
}
#undef sprite_sheet_mode
#undef local_8

/* 00574c47 auto */
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl sprite_picker_select_cell(i32 param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_editor_cell_rect(param_1,(iptr)&local_10,(iptr)&local_14,(iptr)&local_8,(iptr)&local_c);
  sprite_free((Sprite *)&sprite_picker_sprite);
  sprite_grab_from_surface
            ((Sprite *)&sprite_picker_sprite,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),7,local_10,local_14,local_8,local_c);
  sprite_picker_redraw_cb();
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00574ca6 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define sprite_picker_style_flags_i32 (*(i32 *)((u8 *)&g.d_006ac59c))
#define sprite_picker_caption_button_count_i32 (*(i32 *)((u8 *)&g.d_006ac684))
#define sprite_picker_caption_button_cb_i32 (*(i32 *)((u8 *)&g.d_006ac730))
#define sprite_picker_title_font_i32 (*(i32 *)((u8 *)&g.d_006ac754))
#define sprite_picker_title_small_font_i32 (*(i32 *)((u8 *)&g.d_006ac758))
#define sprite_picker_text_font_i32 (*(i32 *)((u8 *)&g.d_006ac75c))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* WARNING: Removing unreachable block (ram,0x00574e18) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
sprite_picker_create_window(int param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    crt_strcpy(&sprite_picker_title,&sprite_picker_default_title);
  }
  else {
    crt_strcpy(&sprite_picker_title,param_1);
  }
  sprite_picker_text_font_i32 = &ui_text_font;
  sprite_picker_title_font_i32 = &caption_font;
  sprite_picker_title_small_font_i32 = &caption_small_font;
  sprite_picker_style_flags_i32 = param_2;
  sprite_picker_caption_height = param_8;
  sprite_picker_border_width = param_9;
  sprite_picker_resize_border = param_7;
  sprite_picker_caption_button_count_i32 = 0;
  sprite_picker_caption_button_cb_i32 = 0;
  if ((param_2 & 4) != 0) {
    sprite_picker_caption_height = frame_caption_height;
    sprite_picker_border_width = frame_border_width;
  }
  if ((param_2 & 8) == 0) {
    local_8 = 0x202;
  }
  else {
    local_8 = 0x802;
  }
  if (sprite_picker_caption_height != 0) {
    local_8 = local_8 | 0x400;
  }
  if (param_7 != 0) {
    local_8 = local_8 | 0x1000;
  }
  if ((param_2 & 2) == 0) {
    param_5 += sprite_picker_border_width * 2;
    param_6 = param_6 + sprite_picker_caption_height + sprite_picker_border_width;
  }
  if ((param_2 & 1) != 0) {
    param_3 = (screen_width >> 1) - (param_5 >> 1);
    param_4 = (screen_height >> 1) - (param_6 >> 1);
  }
  wnd_create_with_surface
            ((DibSurface *)&sprite_picker_window,0,local_8,param_3,param_4,param_5,param_6,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),
             ADDR(0x6ac1f8, ((u8 *)&g.d_006ac1f8)));
  if (sprite_picker_caption_height != 0) {
    wnd_set_caption_height((WndBase *)&sprite_picker_wnd,sprite_picker_caption_height);
  }
  if (sprite_picker_resize_border != 0) {
    wnd_set_resize_border((WndBase *)&sprite_picker_wnd,sprite_picker_resize_border);
  }
  frame_wnd_layout((FrameWindow *)&sprite_picker_window);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef sprite_picker_style_flags_i32
#undef sprite_picker_caption_button_count_i32
#undef sprite_picker_caption_button_cb_i32
#undef sprite_picker_title_font_i32
#undef sprite_picker_title_small_font_i32
#undef sprite_picker_text_font_i32
#undef local_8

/* 00574e98 auto */
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define sprite_picker_dialog (*(int *)((u8 *)&g.d_006ac11c))
#define sprite_picker_running (*(i32 *)((u8 *)&g.d_006ac890))
#define local_2c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(28)))
void __cdecl sprite_picker_ok_clicked(void)

{
  byte bVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_replace_color((Sprite *)&sprite_picker_sprite,9,7);
  local_18 = sprite_width((Sprite *)&sprite_picker_sprite);
  local_1c = sprite_height((Sprite *)&sprite_picker_sprite);
  bVar1 = sprite_get_key_color((Sprite *)&sprite_picker_sprite);
  sprite_editor_key_color = (uint)bVar1;
  sprite_editor_draw_backdrop();
  sprite_draw((Sprite *)&sprite_picker_sprite,(iptr)local_2c,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0,0);
  sprite_free((Sprite *)&sprite_editor_orig_sprite);
  rect_set_xywh((iptr)local_14,0,0,local_18,local_1c);
  sprite_grab_surface_rect((Sprite *)&sprite_editor_orig_sprite,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),(iptr)local_14);
  sprite_picker_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(sprite_picker_dialog + 0x48));
  return;
}
#undef sprite_editor_key_color
#undef sprite_picker_dialog
#undef sprite_picker_running
#undef local_2c
#undef local_1c
#undef local_18
#undef local_14

/* 00574f50 auto */
#define sprite_editor_height (*(i32 *)((u8 *)&g.d_006ac87c))
#define sprite_editor_width (*(i32 *)((u8 *)&g.d_006ac878))
#define sprite_picker_dialog (*(int *)((u8 *)&g.d_006ac11c))
#define sprite_picker_running (*(i32 *)((u8 *)&g.d_006ac890))
#define sprite_sheet_mode (*(i32 *)((u8 *)&g.d_006ac924))
#define local_3c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
/* WARNING: Removing unreachable block (ram,0x00574f76) */

void __cdecl sprite_picker_import_all_clicked(void)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  dlg_push_parent_window(ADDR(0x6ac4d0, ((u8 *)&g.d_006ac4d0)));
  local_8 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6341f8, ((u8 *)&g.d_006341f8)),1);
  dlg_pop_parent_window();
  if (local_8 == 0) {
    switch(sprite_sheet_mode) {
    case 0:
      for (local_20 = 0; (int)local_20 < sprite_sheet_cell_count; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        uVar1 = (int)local_20 >> 0x1f;
        sprite_free
                  ((Sprite *)
                   (&advance_category_icon_sprites +
                   (((local_20 ^ uVar1) - uVar1 & 3 ^ uVar1) - uVar1) * 0x3c +
                   ((int)(local_20 + (uVar1 & 3)) >> 2) * 0xf0));
        uVar1 = (int)local_20 >> 0x1f;
        sprite_editor_grab_from_sheet((iptr)(&advance_category_icon_sprites +
                           ((int)(local_20 + (uVar1 & 3)) >> 2) * 0xf0 +
                           (((local_20 ^ uVar1) - uVar1 & 3 ^ uVar1) - uVar1) * 0x3c),local_18,
                     local_1c,local_10,local_14);
      }
      break;
    case 1:
      for (local_20 = 0; (int)local_20 < sprite_sheet_cell_count; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        local_c = (int)local_20 % 0x18;
        uVar1 = (int)local_c >> 0x1f;
        local_24 = (int)(local_c + (uVar1 & 3)) >> 2;
        local_28 = ((local_c ^ uVar1) - uVar1 & 3 ^ uVar1) - uVar1;
        local_2c = (int)local_20 / 0x18;
        sprite_free
                  ((Sprite *)
                   (&city_sprites + local_28 * 0x78 + local_24 * 0x1e0 + local_2c * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&city_sprites + local_24 * 0x1e0 + local_2c * 0x3c + local_28 * 0x78),
                     local_18,local_1c,local_10,local_14);
      }
      break;
    case 2:
      for (local_20 = 0; (int)local_20 < sprite_sheet_cell_count; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        switch(local_20) {
        case 0:
          sprite_free((Sprite *)&fortify_overlay_sprites);
          sprite_editor_grab_from_sheet(ADDR(0x6465d8, ((u8 *)&g.d_006465d8)),local_18,local_1c,local_10,local_14);
          break;
        case 1:
          sprite_free((Sprite *)&fortress_sprite);
          sprite_editor_grab_from_sheet(ADDR(0x646650, ((u8 *)&g.d_00646650)),local_18,local_1c,local_10,local_14);
          break;
        case 2:
          sprite_free((Sprite *)&airbase_sprites);
          sprite_editor_grab_from_sheet(ADDR(0x647fa0, ((u8 *)&g.d_00647fa0)),local_18,local_1c,local_10,local_14);
          break;
        case 3:
          sprite_free((Sprite *)&airbase_occupied_sprite);
          sprite_editor_grab_from_sheet(ADDR(0x647fdc, ((u8 *)&g.d_00647fdc)),local_18,local_1c,local_10,local_14);
        }
      }
      break;
    case 3:
      for (local_20 = 0; (int)local_20 < 8; local_20++) {
        sprite_editor_cell_rect(local_20 * 2,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&civ_flag_sprites + local_20 * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&civ_flag_sprites + local_20 * 0x78),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 * 2 + 1,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&civ_flag_dark_sprites + local_20 * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&civ_flag_dark_sprites + local_20 * 0x78),local_18,local_1c,local_10,local_14);
      }
      break;
    case 4:
      for (local_20 = 0; (int)local_20 < sprite_sheet_cell_count; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        if ((int)local_20 < 0x26) {
          sprite_free((Sprite *)(&improvement_icon_sprites + (local_20 * 4 + 4) * 0xf));
          sprite_editor_grab_from_sheet((iptr)(&improvement_icon_sprites + (local_20 * 4 + 4) * 0xf),local_18,local_1c,local_10,
                       local_14);
        }
        else {
          sprite_free
                    ((Sprite *)(&wonder_icon_sprites + (local_20 * 4 - 0x98) * 0xf));
          sprite_editor_grab_from_sheet((iptr)(&wonder_icon_sprites + (local_20 * 4 - 0x98) * 0xf),local_18,local_1c,
                       local_10,local_14);
        }
      }
      break;
    case 5:
      break;
    case 6:
      for (local_20 = 0; (int)local_20 < sprite_sheet_cell_count; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        sprite_free((Sprite *)(&explosion_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&explosion_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
      }
      break;
    case 7:
      for (local_20 = 0; (int)local_20 < 0xb; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        sprite_free((Sprite *)(&terrain_base_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&terrain_base_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 + 0x16,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&terrain_resource_sprites + local_20 * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&terrain_resource_sprites + local_20 * 0x78),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 + 0x21,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&terrain_resource2_sprites + local_20 * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&terrain_resource2_sprites + local_20 * 0x78),local_18,local_1c,local_10,local_14);
      }
      break;
    case 8:
      for (local_20 = 0; (int)local_20 < 0x10; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        sprite_free((Sprite *)(&river_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&river_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 + 0x10,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&forest_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&forest_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 + 0x20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&mountain_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&mountain_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 + 0x30,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&hill_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&hill_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
      }
      for (local_20 = 0; (int)local_20 < 4; local_20++) {
        sprite_editor_cell_rect(local_20 + 0x40,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&river_mouth_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&river_mouth_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
      }
      break;
    case 9:
      for (local_20 = 0; (int)local_20 < 8; local_20++) {
        sprite_editor_cell_rect(local_20 << 2,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&coast_quarter_sprites + local_20 * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_sprites + local_20 * 0xf0),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 * 4 + 1,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&coast_quarter_east_sprites + local_20 * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_east_sprites + local_20 * 0xf0),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 * 4 + 2,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&coast_quarter_south_sprites + local_20 * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_south_sprites + local_20 * 0xf0),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 * 4 + 3,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&coast_quarter_west_sprites + local_20 * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_west_sprites + local_20 * 0xf0),local_18,local_1c,local_10,local_14);
      }
      break;
    case 10:
      for (local_20 = 0; (int)local_20 < 3; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        sprite_free((Sprite *)(&land_improvement_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&land_improvement_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
      }
      sprite_editor_cell_rect(3,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14);
      sprite_free((Sprite *)&pollution_sprite);
      sprite_editor_grab_from_sheet(ADDR(0x641808, ((u8 *)&g.d_00641808)),local_18,local_1c,local_10,local_14);
      sprite_editor_cell_rect(4,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14);
      sprite_free((Sprite *)&grassland_shield_sprite);
      sprite_editor_grab_from_sheet(ADDR(0x63fc18, ((u8 *)&g.d_0063fc18)),local_18,local_1c,local_10,local_14);
      sprite_editor_cell_rect(5,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14);
      sprite_free((Sprite *)&hut_sprite);
      sprite_editor_grab_from_sheet(ADDR(0x646158, ((u8 *)&g.d_00646158)),local_18,local_1c,local_10,local_14);
      for (local_20 = 0; (int)local_20 < 9; local_20++) {
        sprite_editor_cell_rect(local_20 + 6,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&road_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&road_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
        sprite_editor_cell_rect(local_20 + 0xf,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,
                           (iptr)&local_14);
        sprite_free((Sprite *)(&railroad_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&railroad_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
      }
      break;
    case 0xb:
      for (local_20 = 0; (int)local_20 < sprite_sheet_cell_count; local_20++) {
        sprite_editor_cell_rect(local_20,(iptr)&local_18,(iptr)&local_1c,(iptr)&local_10,(iptr)&local_14)
        ;
        sprite_free((Sprite *)(&unit_sprites + local_20 * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&unit_sprites + local_20 * 0x3c),local_18,local_1c,local_10,local_14);
      }
    }
    sprite_free((Sprite *)&sprite_editor_orig_sprite);
    sprite_merge_onto(sprite_editor_target_sprite,ADDR(0x6ac170, ((u8 *)&g.d_006ac170)));
    surface_create((DibSurface *)&sprite_editor_surface,sprite_editor_width,sprite_editor_height);
    sprite_editor_draw_backdrop();
    sprite_draw((Sprite *)&sprite_editor_orig_sprite,(iptr)local_3c,ADDR(0x6ac128, ((u8 *)&g.d_006ac128)),0,0);
    sprite_free((Sprite *)&sprite_editor_result_sprite);
    sprite_merge_onto(sprite_editor_target_sprite,ADDR(0x6ac8a8, ((u8 *)&g.d_006ac8a8)));
    sprite_picker_running = 0;
    wnd_end_modal_loop((ModalMenuWindow *)(sprite_picker_dialog + 0x48));
    wnd_repaint((SurfaceWindow *)&map_views);
  }
  return;
}
#undef sprite_editor_height
#undef sprite_editor_width
#undef sprite_picker_dialog
#undef sprite_picker_running
#undef sprite_sheet_mode
#undef local_3c
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

/* 00575d89 auto */
void __cdecl
sprite_editor_grab_from_sheet(iptr param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5)

{
  sprite_grab_from_surface((Sprite *)param_1,ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),7,param_2,param_3,param_4,param_5);
  sprite_replace_color((Sprite *)param_1,9,7);
  return;
}

/* 00575dc4 auto */
#define sprite_picker_dialog (*(int *)((u8 *)&g.d_006ac11c))
#define sprite_picker_running (*(i32 *)((u8 *)&g.d_006ac890))
void __cdecl sprite_picker_cancel_clicked(void)

{
  sprite_picker_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(sprite_picker_dialog + 0x48));
  return;
}
#undef sprite_picker_dialog
#undef sprite_picker_running

/* 00575dec auto */
#define sprite_picker_dialog (*(ViewWindow * *)((u8 *)&g.d_006ac11c))
#define sprite_picker_running (*(int *)((u8 *)&g.d_006ac890))
#define sprite_sheet_mode (*(int *)((u8 *)&g.d_006ac924))
#define local_34 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(i8 (*)[4])(frame_ + FRAME_OFF(20)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(48)))
void __thiscall sprite_picker_run(ViewWindow *this)

{
  i32 uVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  u32 uVar7;
  u32 uVar8;
  i32 uVar9;
  i32 uVar10;
  i32 uVar11;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_picker_dialog = this;
  this->field_2d8 = 0xf0;
  this->field_2dc = 0xf0;
  uVar11 = 0;
  uVar10 = 0;
  uVar9 = 0;
  uVar8 = this->field_2dc;
  uVar7 = this->field_2d8;
  uVar6 = 0;
  uVar5 = 0;
  uVar4 = 0xd;
  uVar1 = label_string(*(i32 *)(label_string_ids + 0x950));
  sprite_picker_create_window(uVar1,uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11);
  iVar2 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2f4 = iVar2 + 8;
  this->field_2f0 = this->client_width - 4;
  iVar2 = GetSystemMetrics(3);
  local_8 = iVar2 + 2;
  this->field_2e8 = this->client_width - 4;
  local_20 = ((this->client_y + this->client_height) - (this->field_2f4 + 2)) - (iVar2 + 4);
  local_1c = this->client_x + 2;
  sprite_sheet_cell_count = sprite_editor_cell_rect(0,(iptr)local_24,(iptr)local_24,(iptr)local_24,(iptr)local_24);
  rect_set_xywh((iptr)local_18,local_1c,local_20,this->field_2e8,local_8);
  if (this == (ViewWindow *)0x0) {
    local_28 = (u8 *)0x0;
  }
  else {
    local_28 = this->pad_48;
  }
  scrollbar_create
            ((Control *)&this->field_2f8,(iptr)local_28,0x65,(iptr)local_18,0);
  scrollbar_set_range((Control *)&this->field_2f8,0,sprite_sheet_cell_count - 1);
  scrollbar_set_pos((ClickControl *)&this->field_2f8,0);
  scrollbar_set_callback((Control *)&this->field_2f8,ADDR(0x401550, sprite_picker_select_cell));
  sprite_picker_select_cell(0);
  ctrl_show_and_redraw((Control *)&this->field_2f8);
  this->field_2f0 = (int)(this->client_width - 8) / 3;
  local_20 = (this->client_y + this->client_height) - (this->field_2f4 + 2);
  local_1c = this->client_x + 2;
  rect_set_xywh((iptr)local_18,local_1c,local_20,this->field_2f0,this->field_2f4);
  if (this == (ViewWindow *)0x0) {
    local_2c = (u8 *)0x0;
  }
  else {
    local_2c = this->pad_48;
  }
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this->field_338,(iptr)local_2c,0xc9,(iptr)local_18,iVar3);
  button_set_callback((Control *)&this->field_338,ADDR(0x4013c5, sprite_picker_ok_clicked));
  ctrl_set_default_button((Control *)&this->field_338);
  local_1c = local_1c + this->field_2f0 + 2;
  rect_set_xywh((iptr)local_18,local_1c,local_20,this->field_2f0,this->field_2f4);
  if (this == (ViewWindow *)0x0) {
    local_30 = (u8 *)0x0;
  }
  else {
    local_30 = this->pad_48;
  }
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x954));
  button_create
            ((Control *)(this->pad_364 + 0x10),(iptr)local_30,0xc9,(iptr)local_18,iVar3);
  button_set_callback((Control *)(this->pad_364 + 0x10),ADDR(0x4029a5, sprite_picker_import_all_clicked));
  ctrl_set_default_button((Control *)(this->pad_364 + 0x10));
  if (sprite_sheet_mode == 5) {
    ctrl_disable((Control *)(this->pad_364 + 0x10));
  }
  local_1c = local_1c + this->field_2f0 + 2;
  rect_set_xywh((iptr)local_18,local_1c,local_20,this->field_2f0,this->field_2f4);
  if (this == (ViewWindow *)0x0) {
    local_34 = (u8 *)0x0;
  }
  else {
    local_34 = this->pad_48;
  }
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this->field_3b0,(iptr)local_34,0xca,(iptr)local_18,iVar3);
  button_set_callback((Control *)&this->field_3b0,ADDR(0x402cde, sprite_picker_cancel_clicked));
  ctrl_set_cancel_button((Control *)&this->field_3b0);
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x403887, sprite_picker_redraw_cb));
  wnd_repaint((SurfaceWindow *)this);
  window_show((WindowObjectView *)this);
  wnd_run_modal_loop((ModalMenuWindow *)this->pad_48);
  while (sprite_picker_running != 0) {
    win_pump_one_message();
  }
  frame_wnd_close((DibSurface *)this);
  return;
}
#undef sprite_picker_dialog
#undef sprite_picker_running
#undef sprite_sheet_mode
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 0057624d auto */
void __cdecl sprite_picker_show(void)

{
  sprite_picker_run((ViewWindow *)&sprite_picker_window);
  return;
}

/* 00576267 auto */
#define sprite_sheet_mode (*(int *)((u8 *)&g.d_006ac924))
#define local_9d0 (*(char (*)[132])(frame_ + FRAME_OFF(0)))
#define local_94c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_948 (*(char (*)[260])(frame_ + FRAME_OFF(136)))
#define local_844 (*(char * *)(frame_ + FRAME_OFF(396)))
#define local_840 (*(char (*)[260])(frame_ + FRAME_OFF(400)))
#define local_73c (*(GamePalette *)(frame_ + FRAME_OFF(660)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(1736)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(2492)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2496)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2500)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(2504)))
/* WARNING: Removing unreachable block (ram,0x0057656d) */
/* WARNING: Removing unreachable block (ram,0x005763fb) */
/* WARNING: Removing unreachable block (ram,0x00576601) */

void __cdecl sprite_editor_import_sheet(void)

{
  i32 uVar1;
  iptr iVar2;
  size_t _MaxCount;
  iptr iVar3;
  int iVar4;
  char *pcVar5;
  i32 uVar6;
  char *pcVar7;
  i32 uVar8;
  LPCSTR pCVar9;
  LPCSTR pCVar10;
  i32 uVar11;
  UINT UVar12;
  i8 frame_[FRAME_OFF(2512)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_73c);
  local_8 = 0;
  dialog_ctor(&local_308,0x4000);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  switch(sprite_sheet_mode) {
  case 0:
  case 4:
  case 5:
  case 6:
    local_844 = s_ICONS_00634210;
    break;
  case 1:
  case 2:
  case 3:
    local_844 = s_CITIES_00634218;
    break;
  case 7:
  case 8:
  case 9:
  case 10:
    local_844 = s_TERRAIN_00634208;
    break;
  case 0xb:
    local_844 = s_UNITS_00634200;
  }
  do {
    uVar11 = 0;
    uVar8 = 0;
    uVar6 = 0;
    pcVar5 = local_844;
    pcVar7 = local_844;
    uVar1 = label_string(*(i32 *)(label_string_ids + 0x958));
    _sprintf(local_840,s__s__s_c_s__BMP__s__GIF_c_c_00634220,local_844,uVar1,uVar6,pcVar5,pcVar7,
             uVar8,uVar11);
    _sprintf(local_948,s__s__BMP__s__GIF_0063423c,local_844,local_844);
    pcVar5 = local_844;
    uVar1 = label_string(*(i32 *)(label_string_ids + 0x95c));
    _sprintf(local_9d0,s__s__s_0063424c,uVar1,pcVar5);
    iVar2 = ui_file_name_dialog(ADDR(0x6ac1f8, ((u8 *)&g.d_006ac1f8)),(iptr)local_9d0,(iptr)local_948,(iptr)local_840,ADDR(0x634254, ((u8 *)&g.d_00634254)),1,0
                              );
    if (iVar2 == 0) goto LAB_00576783;
    __strupr(local_948);
    local_94c = 1;
    local_14 = _strrchr(local_948,0x5c);
    if (local_14 == (char *)0x0) {
      local_14 = local_948;
    }
    else {
      local_14++;
    }
    _MaxCount = _strlen(local_844);
    iVar3 = _strncmp(local_14,local_844,_MaxCount);
    if (iVar3 == 0) {
      if ((sprite_sheet_mode == 7) || (sprite_sheet_mode == 10)) {
        iVar4 = _isdigit((int)local_14[7]);
        if ((iVar4 != 0) && ((local_14[7] & 1U) != 0)) goto LAB_00576631;
        dlg_push_parent_window(ADDR(0x6ac4d0, ((u8 *)&g.d_006ac4d0)));
        popup_debug_text(ADDR(0x634264, ((u8 *)&g.d_00634264)));
        dlg_pop_parent_window();
      }
      else if (((sprite_sheet_mode == 8) || (sprite_sheet_mode == 9)) &&
              ((iVar4 = _isdigit((int)local_14[7]), iVar4 == 0 || ((local_14[7] & 1U) != 0)))) {
        dlg_push_parent_window(ADDR(0x6ac4d0, ((u8 *)&g.d_006ac4d0)));
        popup_debug_text(ADDR(0x634270, ((u8 *)&g.d_00634270)));
        dlg_pop_parent_window();
      }
      else {
LAB_00576631:
        pcVar5 = _strstr(local_948,&sprite_import_bmp_ext_str);
        if (pcVar5 == (char *)0x0) {
          pcVar5 = _strstr(local_948,&sprite_import_gif_ext_str);
          if (pcVar5 == (char *)0x0) {
            UVar12 = 0x10;
            pCVar10 = (LPCSTR)0x0;
            pCVar9 = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x968));
            iVar4 = wnd_get_window((WndBase *)&sprite_editor_wnd);
            MessageBoxA(*(HWND *)(iVar4 + 4),pCVar9,pCVar10,UVar12);
          }
          else {
            iVar4 = surface_load_gif_file
                              ((DibSurface *)&sprite_sheet_surface,(iptr)local_948,10,0xc0,
                               (iptr)&local_73c);
            if (iVar4 == 0) {
              UVar12 = 0x10;
              pCVar10 = (LPCSTR)0x0;
              pCVar9 = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x964));
              iVar4 = wnd_get_window((WndBase *)&sprite_editor_wnd);
              MessageBoxA(*(HWND *)(iVar4 + 4),pCVar9,pCVar10,UVar12);
            }
            else {
              local_94c = 0;
            }
          }
        }
        else {
          iVar4 = gfx_load_bmp_640x480(ADDR(0x6ac0a8, ((u8 *)&g.d_006ac0a8)),(iptr)local_948,10,0xc0,(iptr)&local_73c);
          if (iVar4 == 0) {
            UVar12 = 0x10;
            pCVar10 = (LPCSTR)0x0;
            pCVar9 = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x964));
            iVar4 = wnd_get_window((WndBase *)&sprite_editor_wnd);
            MessageBoxA(*(HWND *)(iVar4 + 4),pCVar9,pCVar10,UVar12);
          }
          else {
            local_94c = 0;
          }
        }
      }
    }
    else {
      pcVar5 = local_844;
      uVar1 = label_string(*(i32 *)(label_string_ids + 0x960));
      _sprintf(local_9d0,s__s___s__0063425c,uVar1,pcVar5);
      UVar12 = 0x40;
      pCVar9 = (LPCSTR)0x0;
      pcVar5 = local_9d0;
      iVar4 = wnd_get_window((WndBase *)&sprite_editor_wnd);
      MessageBoxA(*(HWND *)(iVar4 + 4),pcVar5,pCVar9,UVar12);
    }
  } while (local_94c != 0);
  sprite_picker_show();
  sprite_editor_redraw();
LAB_00576783:
  surface_release((DibSurface *)&sprite_sheet_surface);
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet 005767a7 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005767b3 */ { palette_destroy((GamePalette *)((iptr)&local_73c)); }
  return;
}
#undef sprite_sheet_mode
#undef local_9d0
#undef local_94c
#undef local_948
#undef local_844
#undef local_840
#undef local_73c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00578390 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CBitmapButton::~CBitmapButton(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall sprite_picker_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 00578402 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x3b0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 00578411 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x374)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 00578420 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x338)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 0057842f */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x2f8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0057843e */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005784a0 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
ViewWindow * __thiscall sprite_picker_ctor(ViewWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  scrollbar_ctor((Control *)&this->field_2f8);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  button_ctor((Control *)&this->field_338);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  button_ctor((Control *)(this->pad_364 + 0x10));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),3);
  button_ctor((Control *)&this->field_3b0);
  this->vtable = (u32)&PTR_FUN_0061d6fc;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 005a9780 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl gfx_set_draw_target(iptr param_1)

{
  gfx_draw_target = param_1;
  return;
}
#undef gfx_draw_target

/* 005a9798 auto */
void __cdecl
gfx_draw_line_color(iptr param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6)

{
  gfx_set_text_color_index(param_6);
  surface_draw_line((DibSurface *)param_1,param_2,param_3,param_4,param_5);
  return;
}

/* 005a97cc auto */
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl
gfx_draw_hline(iptr param_1,i32 param_2,int param_3,int param_4,i32 param_5)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set((iptr)local_14,param_2,param_4,param_3 + 1,param_4 + 1);
  gfx_fill_rect(param_1,(iptr)local_14,param_5);
  return;
}
#undef local_14

/* 005a9858 auto */
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl
gfx_draw_vline(iptr param_1,int param_2,i32 param_3,int param_4,i32 param_5)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set((iptr)local_14,param_2,param_3,param_2 + 1,param_4 + 1);
  gfx_fill_rect(param_1,(iptr)local_14,param_5);
  return;
}
#undef local_14

/* 005a98e4 auto */
void __cdecl
gfx_draw_box_ltrb(iptr param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6)

{
  gfx_draw_hline(param_1,param_2,param_4,param_3,param_6);
  gfx_draw_hline(param_1,param_2,param_4,param_5,param_6);
  gfx_draw_vline(param_1,param_2,param_3,param_5,param_6);
  gfx_draw_vline(param_1,param_4,param_3,param_5,param_6);
  return;
}

/* 005a9964 auto */
void __cdecl
gfx_draw_frame_rect(iptr param_1,int param_2,int param_3,int param_4,iptr param_5,i32 param_6)

{
  gfx_draw_hline(param_1,param_2,param_4 + param_2 - 1,param_3,param_6);
  gfx_draw_hline(param_1,param_2,param_4 + param_2 - 1,param_5 + param_3 - 1,param_6);
  gfx_draw_vline(param_1,param_2,param_3,param_5 + param_3 - 1,param_6);
  gfx_draw_vline(param_1,param_4 + param_2 - 1,param_3,param_5 + param_3 - 1,param_6);
  return;
}

/* 005a99fc auto */
void __cdecl gfx_draw_bevel_rect(iptr param_1,iptr param_2,i32 param_3,i32 param_4)

{
  gfx_draw_hline(param_1,*(i32 *)param_2,*(int *)(param_2 + 8) - 1,
                     *(i32 *)(param_2 + 4),param_3);
  gfx_draw_vline(param_1,*(i32 *)param_2,*(i32 *)(param_2 + 4),
                     *(int *)(param_2 + 0xc) - 1,param_3);
  gfx_draw_hline(param_1,*(i32 *)param_2,*(int *)(param_2 + 8) - 1,
                     *(int *)(param_2 + 0xc) - 1,param_4);
  gfx_draw_vline(param_1,*(int *)(param_2 + 8) - 1,*(i32 *)(param_2 + 4),
                     *(int *)(param_2 + 0xc) - 1,param_4);
  return;
}

/* 005a9aa3 auto */
void __cdecl gfx_fill_surface(iptr param_1,i32 param_2)

{
  surface_fill((DibSurface *)param_1,param_2);
  return;
}

/* 005a9abf auto */
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl
gfx_fill_rect_xywh(iptr param_1,i32 param_2,i32 param_3,iptr param_4,iptr param_5,
            i32 param_6)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,param_2,param_3,param_4,param_5);
  surface_fill_rect((DibSurface *)param_1,(iptr)local_14,param_6);
  return;
}
#undef local_14

/* 005a9afe auto */
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl
gfx_copy_rect_xywh(iptr param_1,iptr param_2,i32 param_3,i32 param_4,i32 param_5,
            i32 param_6,iptr param_7,iptr param_8)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,param_3,param_4,param_7,param_8);
  rect_set_xywh((iptr)local_24,param_5,param_6,param_7,param_8);
  surface_blit((DibSurface *)param_1,param_2,(iptr)local_14,(iptr)local_24);
  return;
}
#undef local_24
#undef local_14

/* 005a9b5d auto */
#define local_38 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
int __cdecl
gfx_tile_fill(iptr param_1,iptr param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = surface_width((DibSurface *)param_2);
  iVar2 = surface_height((DibSurface *)param_2);
  local_8 = iVar2;
  if ((iVar1 != 0) && (iVar2 != 0)) {
    if (param_3 == param_7 || param_3 - param_7 < 0) {
      local_34 = ~(param_3 - param_7) + 1;
    }
    else {
      local_34 = param_3 - param_7;
    }
    if (param_4 == param_8 || param_4 - param_8 < 0) {
      local_38 = ~(param_4 - param_8) + 1;
    }
    else {
      local_38 = param_4 - param_8;
    }
    local_2c = local_38 % iVar2;
    iVar3 = param_5 + param_3;
    iVar4 = param_6 + param_4;
    for (local_8 = param_4; local_8 < iVar4; local_8 += iVar6) {
      local_28 = local_34 % iVar1;
      for (local_30 = param_3; local_30 < iVar3; local_30 += iVar6) {
        iVar5 = (local_30 + iVar1) - local_28;
        iVar6 = (iVar2 + local_8) - local_2c;
        if (iVar3 <= iVar5) {
          iVar5 = iVar3;
        }
        if (iVar4 <= iVar6) {
          iVar6 = iVar4;
        }
        gfx_copy_rect_xywh(param_2,param_1,local_28,local_2c,local_30,local_8,iVar5 - local_30,
                           iVar6 - local_8);
        iVar6 = iVar1 - local_28;
        local_28 = 0;
      }
      iVar6 = iVar2 - local_2c;
      local_2c = 0;
    }
  }
  return local_8;
}
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_8

/* 005ae006 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl bits_count8(uint param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 0; local_c < 8; local_c++) {
    if ((param_1 & 1) != 0) {
      local_8++;
    }
    param_1 = (int)param_1 >> 1;
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 005ae3bf auto */
void __cdecl bit_index_split(iptr param_1,iptr param_2,iptr param_3)

{
  *(iptr *)param_2 = param_1 >> 3;
  *(int *)param_3 = 1 << ((byte)param_1 & 7);
  return;
}

/* 005bb3f0 auto */
void __thiscall
surface_wnd_create
          (DibSurface *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4
          ,i32 param_5,i32 param_6,iptr param_7)

{
  iptr iVar1;
  
  wnd_create_framed
            ((WndBase *)(this + 1),param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  surface_create(this,param_5,param_6);
  surface_set_palette(this,param_7);
  iVar1 = wnd_get_window((WndBase *)(this + 1));
  wnd_install_paint_proc((iptr)this,iVar1);
  return;
}

/* 005bcaa7 auto */
void __cdecl gfx_get_screen_rect(iptr param_1)

{
  int yBottom;
  int xRight;
  
  yBottom = GetSystemMetrics(1);
  xRight = GetSystemMetrics(0);
  SetRect((LPRECT)param_1,0,0,xRight,yBottom);
  return;
}

/* 005bcc11 auto */
void __cdecl
dib_blit_to_wnd_obj(iptr param_1,int param_2,int param_3,int param_4,int param_5,iptr param_6,int param_7,
            int param_8)

{
  if ((param_1 != 0) && (param_6 != 0)) {
    if ((*(int *)(param_6 + 0x18) != 0) && (gfx_palettized_display == 1)) {
      RealizePalette(*(HDC *)(param_6 + 8));
    }
    BitBlt(*(HDC *)(param_6 + 8),param_7,param_8,param_4,param_5,*(HDC *)(param_1 + 4),param_2,
           param_3,0xcc0020);
  }
  return;
}

/* 005bd630 auto */
DibSurface * __thiscall surface_ctor(DibSurface *this)

{
  this->vtable = (u32)&PTR_FUN_0061d70c;
  surface_set_dims(this,0);
  return this;
}

/* 005bd65c auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall surface_create(DibSurface *this,int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&local_14,0,0,param_1,param_2);
  surface_alloc_dib8(this,(iptr)&local_14);
  return;
}
#undef local_14

/* 005bd696 auto */
i32 __thiscall surface_alloc_dib8(DibSurface *this,iptr param_1)

{
  char cVar1;
  u32 uVar2;
  int iVar3;
  
  if (this->dib != 0) {
    cVar1 = surface_is_locked(this);
    if (cVar1 != '\0') {
      surface_unlock(this);
    }
    uVar2 = dib_destroy(this->dib);
    this->dib = uVar2;
  }
  if (((param_1 != 0) && (iVar3 = rect_width(param_1), iVar3 != 0)) &&
     (iVar3 = rect_height(param_1), iVar3 != 0)) {
    surface_set_dims(this,param_1);
    uVar2 = dib_create((iptr)&this->bounds_rect);
    this->dib = uVar2;
    if (this->dib != 0) {
      uVar2 = dib_get_stride(this->dib);
      this->stride = uVar2;
      iVar3 = dib_is_top_down(this->dib);
      if (iVar3 == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,ADDR(0x636774, ((u8 *)&g.d_00636774)),ADDR(0x63675c, ((u8 *)&g.d_0063675c)),0x71);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005bd813 auto */
void __thiscall surface_set_dims(DibSurface *this,int *param_1)

{
  this->bits = 0;
  this->dib = 0;
  this->palette_version = 0;
  this->stride = 0;
  this->signed_pitch = 0;
  this->bytes_per_pixel = 1;
  if (param_1 == (int *)0x0) {
    this->pixel_height = 0;
    this->pixel_width = 0;
    SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
    SetRect((LPRECT)&this->clip_left,0,0,0,0);
  }
  else {
    this->pixel_height = param_1[3] - param_1[1];
    this->pixel_width = param_1[2] - *param_1;
    SetRect((LPRECT)&this->bounds_rect,0,0,this->pixel_width,this->pixel_height);
    SetRect((LPRECT)&this->clip_left,0,0,this->pixel_width,this->pixel_height);
  }
  return;
}

/* 005bd915 auto */
#define draw_current_surface (*(DibSurface * *)((u8 *)&g.d_00637e58))
DibSurface * __thiscall surface_dtor(DibSurface *this)

{
  char cVar1;
  u32 uVar2;
  
  this->vtable = (u32)&PTR_FUN_0061d70c;
  cVar1 = surface_is_locked(this);
  if (cVar1 != '\0') {
    surface_unlock(this);
  }
  uVar2 = dib_destroy(this->dib);
  this->dib = uVar2;
  surface_set_dims(this,0);
  if (draw_current_surface == this) {
    draw_current_surface = (DibSurface *)0x0;
  }
  return this;
}
#undef draw_current_surface

/* 005bf071 auto */
#define local_dc (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(20)))
#define local_c8 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_c4 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_c0 (*(FileObject *)(frame_ + FRAME_OFF(32)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(184)))
#define local_24 (*(byte *)(frame_ + FRAME_OFF(188)))
#define local_20 (*(char * *)(frame_ + FRAME_OFF(192)))
#define local_1c (*(char * *)(frame_ + FRAME_OFF(196)))
#define local_18 (*(char * *)(frame_ + FRAME_OFF(200)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(204)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(208)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(212)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(216)))
i32 __thiscall
surface_load_gif_file(DibSurface *this,iptr param_1,uint param_2,uint param_3,iptr param_4)

{
  int iVar1;
  i32 uVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(224)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  file_obj_init(&local_c0);
  local_8 = 0;
  iVar1 = file_obj_open(&local_c0,param_1);
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
    uVar2 = 0;
  }
  else {
    uVar2 = file_obj_get_size(&local_c0);
    local_cc = mem_handle_alloc(uVar2);
    win_flush_pending_msgs();
    if (local_cc == 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
      uVar2 = 0;
    }
    else {
      local_c8 = mem_handle_lock(local_cc);
      uVar2 = file_obj_get_size(&local_c0);
      file_obj_read(&local_c0,local_c8,uVar2);
      local_c8 = mem_handle_unlock(local_cc);
      win_flush_pending_msgs();
      if (local_cc == 0) {
        dbg_logf_str(ADDR(0x636c40, ((u8 *)&g.d_00636c40)),param_1);
        err_report((ErrorContext *)&err_report_ctx,3,ADDR(0x636c7c, ((u8 *)&g.d_00636c7c)),ADDR(0x636c64, ((u8 *)&g.d_00636c64)),0x382);
        local_8 = 0xffffffff;
        /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
        uVar2 = 0;
      }
      else {
        local_20 = (char *)mem_handle_lock(local_cc);
        iVar1 = _strncmp(local_20,&gif_sig_file,3);
        if (iVar1 == 0) {
          if ((local_20[10] & 0x80U) == 0) {
            dbg_logf_str(ADDR(0x636ce4, ((u8 *)&g.d_00636ce4)),param_1);
            mem_handle_unlock(local_cc);
            mem_handle_free(local_cc);
            err_report((ErrorContext *)&err_report_ctx,4,ADDR(0x636d28, ((u8 *)&g.d_00636d28)),ADDR(0x636d10, ((u8 *)&g.d_00636d10)),0x396);
            local_8 = 0xffffffff;
            /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
            uVar2 = 0;
          }
          else {
            uVar3 = 1 << (local_20[10] & 7U) + 1;
            local_1c = local_20 + 0xd;
            win_flush_pending_msgs();
            if (param_4 != 0) {
              win_flush_pending_msgs();
              if (0x100 < (int)(param_3 + param_2)) {
                param_3 = 0x100 - param_2;
              }
              if (uVar3 <= param_3) {
                param_3 = uVar3;
              }
              palette_set_rgb((GamePalette *)param_4,param_2,param_3,(iptr)local_1c)
              ;
              win_flush_pending_msgs();
            }
            for (local_1c = local_20 + uVar3 * 3 + 0xd; *local_1c == '\0'; local_1c++)
            {
            }
            if ((*local_1c == ',') || (*local_1c == '!')) {
              local_18 = local_1c + 1;
              local_28 = endian_from_le((uint)*(ushort *)(local_1c + 5));
              local_c4 = endian_from_le((uint)*(ushort *)(local_18 + 6));
              if ((local_18[8] & 0x80U) != 0) {
                dbg_log(ADDR(0x636d8c, ((u8 *)&g.d_00636d8c)));
              }
              SetRect(&local_dc,0,0,local_28,local_c4);
              iVar1 = surface_resize(this,(iptr)&local_dc);
              if (iVar1 == 0) {
                mem_handle_unlock(local_cc);
                mem_handle_free(local_cc);
                local_8 = 0xffffffff;
                /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
                uVar2 = 0;
              }
              else {
                local_24 = local_18[9];
                local_14 = local_18 + 10;
                win_flush_pending_msgs();
                gif_lzw_decode((iptr)local_14,param_2,
                             CONCAT22((short)(this->stride >> 0x10),(ushort)local_24),this->stride
                             ,local_28,local_c4,this->bits);
                win_flush_pending_msgs();
                surface_set_palette(this,param_4);
                iVar1 = dib_is_top_down(this->dib);
                if (iVar1 == 0) {
                  dib_flip_vertical(this->dib);
                }
                mem_handle_unlock(local_cc);
                mem_handle_free(local_cc);
                file_map_close(&local_c0);
                local_8 = 0xffffffff;
                /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
                uVar2 = 1;
              }
            }
            else {
              dbg_logf_str(ADDR(0x636d3c, ((u8 *)&g.d_00636d3c)),param_1);
              mem_handle_unlock(local_cc);
              mem_handle_free(local_cc);
              err_report((ErrorContext *)&err_report_ctx,4,ADDR(0x636d78, ((u8 *)&g.d_00636d78)),ADDR(0x636d60, ((u8 *)&g.d_00636d60)),0x3b3);
              local_8 = 0xffffffff;
              /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
              uVar2 = 0;
            }
          }
        }
        else {
          dbg_logf_str(ADDR(0x636c98, ((u8 *)&g.d_00636c98)),param_1);
          mem_handle_unlock(local_cc);
          mem_handle_free(local_cc);
          err_report((ErrorContext *)&err_report_ctx,4,ADDR(0x636cd0, ((u8 *)&g.d_00636cd0)),ADDR(0x636cb8, ((u8 *)&g.d_00636cb8)),0x38d);
          local_8 = 0xffffffff;
          /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&local_c0)); }
          uVar2 = 0;
        }
      }
    }
  }
  return uVar2;
}
#undef local_dc
#undef local_cc
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005bf5e1 auto */
#define local_38 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(i8 *)(frame_ + FRAME_OFF(20)))
#define local_23 (*(i8 *)(frame_ + FRAME_OFF(21)))
#define local_22 (*(i8 *)(frame_ + FRAME_OFF(22)))
#define local_21 (*(i8 *)(frame_ + FRAME_OFF(23)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(byte *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(char * *)(frame_ + FRAME_OFF(40)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(48)))
i32 __thiscall
surface_load_gif_resource(DibSurface *this,iptr param_1,uint param_2,uint param_3,iptr param_4)

{
  i32 uVar1;
  int iVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_24 = 0x47;
  local_23 = 0x49;
  local_22 = 0x46;
  local_21 = 0x53;
  local_28 = res_load((iptr)&local_24,param_1);
  if (local_28 == 0) {
    dbg_logf(ADDR(0x636db0, ((u8 *)&g.d_00636db0)),param_1);
    err_report((ErrorContext *)&err_report_ctx,3,ADDR(0x636dec, ((u8 *)&g.d_00636dec)),ADDR(0x636dd4, ((u8 *)&g.d_00636dd4)),0x3f4);
    uVar1 = 0;
  }
  else {
    local_14 = (char *)res_lock(local_28);
    iVar2 = _strcmp(local_14,&gif_sig_resource);
    if (iVar2 == 0) {
      dbg_logf(ADDR(0x636e08, ((u8 *)&g.d_00636e08)),param_1);
      res_unlock(local_28);
      res_free(local_28);
      err_report((ErrorContext *)&err_report_ctx,4,ADDR(0x636e40, ((u8 *)&g.d_00636e40)),ADDR(0x636e28, ((u8 *)&g.d_00636e28)),0x3ff);
      uVar1 = 0;
    }
    else if ((local_14[10] & 0x80U) == 0) {
      dbg_logf(ADDR(0x636e54, ((u8 *)&g.d_00636e54)),param_1);
      res_unlock(local_28);
      res_free(local_28);
      err_report((ErrorContext *)&err_report_ctx,4,ADDR(0x636e98, ((u8 *)&g.d_00636e98)),ADDR(0x636e80, ((u8 *)&g.d_00636e80)),0x408);
      uVar1 = 0;
    }
    else {
      uVar3 = 1 << (local_14[10] & 7U) + 1;
      local_10 = local_14 + 0xd;
      if (param_4 != 0) {
        if (0x100 < (int)(param_3 + param_2)) {
          param_3 = 0x100 - param_2;
        }
        if (uVar3 <= param_3) {
          param_3 = uVar3;
        }
        palette_set_rgb((GamePalette *)param_4,param_2,param_3,(iptr)local_10);
      }
      win_flush_pending_msgs();
      for (local_10 = local_14 + uVar3 * 3 + 0xd; *local_10 == '\0'; local_10++) {
      }
      if ((*local_10 == ',') || (*local_10 == '!')) {
        local_c = local_10 + 1;
        local_1c = endian_from_le((uint)*(ushort *)(local_10 + 5));
        local_20 = endian_from_le((uint)*(ushort *)(local_c + 6));
        if ((local_c[8] & 0x80U) != 0) {
          dbg_log(ADDR(0x636efc, ((u8 *)&g.d_00636efc)));
        }
        SetRect(&local_38,0,0,local_1c,local_20);
        surface_resize(this,(iptr)&local_38);
        local_18 = local_c[9];
        local_8 = local_c + 10;
        win_flush_pending_msgs();
        gif_lzw_decode((iptr)local_8,param_2,CONCAT22((short)(this->stride >> 0x10),(ushort)local_18)
                     ,this->stride,local_1c,local_20,this->bits);
        win_flush_pending_msgs();
        surface_set_palette(this,param_4);
        iVar2 = dib_is_top_down(this->dib);
        if (iVar2 == 0) {
          dib_flip_vertical(this->dib);
        }
        res_unlock(local_28);
        res_free(local_28);
        uVar1 = 1;
      }
      else {
        dbg_logf(ADDR(0x636eac, ((u8 *)&g.d_00636eac)),param_1);
        res_unlock(local_28);
        res_free(local_28);
        err_report((ErrorContext *)&err_report_ctx,4,ADDR(0x636ee8, ((u8 *)&g.d_00636ee8)),ADDR(0x636ed0, ((u8 *)&g.d_00636ed0)),0x424);
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}
#undef local_38
#undef local_28
#undef local_24
#undef local_23
#undef local_22
#undef local_21
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005c0034 auto */
void __thiscall surface_reset_clip(DibSurface *this)

{
  SetRect((LPRECT)&this->clip_left,this->bounds_rect,this->bounds_top,this->bounds_right,this->bounds_bottom);
  return;
}

/* 005c0073 auto */
void __thiscall surface_set_clip(DibSurface *this,iptr param_1)

{
  SetRect((LPRECT)&this->clip_left,*(int *)param_1,*(int *)(param_1 + 4),*(int *)(param_1 + 8),
          *(int *)(param_1 + 0xc));
  IntersectRect((LPRECT)&this->clip_left,(RECT *)&this->clip_left,(RECT *)&this->bounds_rect);
  return;
}

/* 005c00ce auto */
void __thiscall surface_get_clip(DibSurface *this,iptr param_1)

{
  *(u32 *)param_1 = this->clip_left;
  *(u32 *)(param_1 + 4) = this->clip_top;
  *(u32 *)(param_1 + 8) = this->clip_right;
  *(u32 *)(param_1 + 0xc) = this->clip_bottom;
  return;
}

/* 005c0105 auto */
i32 __thiscall surface_alloc_dib_by_bpp(DibSurface *this,iptr param_1)

{
  i32 uVar1;
  
  switch(this->bytes_per_pixel) {
  case 1:
    uVar1 = surface_alloc_dib8(this,param_1);
    break;
  case 2:
    uVar1 = surface_alloc_dib16(this,param_1);
    break;
  case 3:
    uVar1 = surface_alloc_dib24(this,param_1);
    break;
  case 4:
    uVar1 = surface_alloc_dib32(this,param_1);
    break;
  default:
    uVar1 = 0;
  }
  return uVar1;
}

/* 005c019d auto */
i32 __thiscall surface_resize(DibSurface *this,iptr param_1)

{
  i32 uVar1;
  
  uVar1 = surface_alloc_dib8(this,param_1);
  return uVar1;
}

/* 005c01c1 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall surface_lock(DibSurface *this)

{
  uptr uVar1;
  void *pvVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->bits == 0) {
    uVar1 = dib_get_bits(this->dib);
    this->bits = uVar1;
    if (this->bits != 0) {
      pvVar2 = operator_new(this->pixel_height << 2);
      this->row_offsets = (uptr)pvVar2;
      iVar3 = dib_is_top_down(this->dib);
      if (iVar3 == 0) {
        *(u32 *)this->row_offsets = (this->pixel_height - 1) * this->stride;
        for (local_8 = 1; local_8 < (int)this->pixel_height; local_8++) {
          *(u32 *)(this->row_offsets + local_8 * 4) =
               *(int *)((this->row_offsets - 4) + local_8 * 4) - this->stride;
        }
      }
      else {
        *(i32 *)this->row_offsets = 0;
        for (local_8 = 1; local_8 < (int)this->pixel_height; local_8++) {
          *(u32 *)(this->row_offsets + local_8 * 4) =
               *(int *)((this->row_offsets - 4) + local_8 * 4) + this->stride;
        }
      }
    }
  }
  return;
}
#undef local_8

/* 005c02e0 auto */
void __thiscall surface_unlock(DibSurface *this)

{
  uptr uVar1;
  
  if (this->bits != 0) {
    uVar1 = dib_unlock_bits(this->dib);
    this->bits = uVar1;
    operator_delete((void *)this->row_offsets);
  }
  return;
}

/* 005c0333 auto */
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(24)))
void __thiscall surface_fill_rect(DibSurface *this,iptr param_1,i32 param_2)

{
  char cVar1;
  i32 uVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  cVar1 = surface_is_locked(this);
  if (cVar1 == '\0') {
    dbg_log(ADDR(0x6370c4, ((u8 *)&g.d_006370c4)));
    local_8 = 0;
    surface_lock(this);
  }
  IntersectRect(&local_20,(RECT *)param_1,(RECT *)&this->clip_left);
  local_c = rect_width((iptr)&local_20);
  if ((local_c != 0) && (local_10 = rect_height((iptr)&local_20), local_10 != 0)) {
    uVar2 = surface_height(this);
    iVar3 = surface_get_dib(this);
    iVar4 = dib_is_top_down(iVar3);
    iVar5 = surface_get_pitch(this);
    dib_fill_rect8(this->bits,param_2,local_20.left,local_20.top,local_c,local_10,
                 ((-(uint)(iVar4 == 0) & 0xfffffffe) + 1) * iVar5,uVar2);
  }
  return;
}
#undef local_20
#undef local_10
#undef local_c
#undef local_8

/* 005c041f auto */
void __thiscall surface_fill(DibSurface *this,i32 param_1)

{
  surface_fill_rect(this,(iptr)&this->clip_left,param_1);
  return;
}

/* 005c044a auto */
void __thiscall
surface_replace_color_clip(DibSurface *this,i32 param_1,i32 param_2)

{
  surface_replace_color(this,(iptr)&this->clip_left,param_1,param_2);
  return;
}

/* 005c0479 auto */
#define local_28 (*(char * *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __thiscall
surface_replace_color(DibSurface *this,iptr param_1,i32 param_2,i32 param_3)

{
  char cVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  cVar1 = surface_is_locked(this);
  if (cVar1 == '\0') {
    dbg_log(ADDR(0x6370ec, ((u8 *)&g.d_006370ec)));
    local_8 = 0;
    surface_lock(this);
  }
  IntersectRect(&local_24,(RECT *)param_1,(RECT *)&this->clip_left);
  local_c = rect_width((iptr)&local_24);
  local_28 = (char *)surface_pixel_ptr(this,local_24.left,local_24.top);
  local_14 = 0;
  while( true ) {
    iVar2 = rect_height((iptr)&local_24);
    if (iVar2 <= local_14) break;
    local_10 = 0;
    while( true ) {
      iVar3 = rect_width((iptr)&local_24);
      if (iVar3 <= local_10) break;
      if (*local_28 == (char)param_2) {
        *local_28 = (char)param_3;
      }
      local_28++;
      local_10++;
    }
    iVar4 = surface_next_row(this,(iptr)local_28);
    local_28 = (char *)(iVar4 - local_c);
    local_14++;
  }
  if (local_8 == 0) {
    surface_unlock(this);
  }
  return;
}
#undef local_28
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005c0593 auto */
#define local_30 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(16)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall
surface_blit(DibSurface *this,iptr param_1,iptr param_2,iptr param_3)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  i32 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  i32 uVar10;
  i32 uVar11;
  bool bVar12;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 1;
  bVar12 = this->bits == 0;
  if (bVar12) {
    dbg_log(ADDR(0x637114, ((u8 *)&g.d_00637114)));
    surface_lock(this);
  }
  if (*(int *)(param_1 + 0x34) == 0) {
    dbg_log(ADDR(0x637144, ((u8 *)&g.d_00637144)));
    surface_lock((DibSurface *)param_1);
    local_10 = 0;
  }
  IntersectRect(&local_20,(RECT *)param_2,(RECT *)&this->clip_left);
  IntersectRect(&local_30,(RECT *)param_3,(RECT *)(param_1 + 0x14));
  local_8 = local_30.right - local_30.left;
  if (local_20.right - local_20.left <= local_30.right - local_30.left) {
    local_8 = local_20.right - local_20.left;
  }
  local_c = local_30.bottom - local_30.top;
  if (local_20.bottom - local_20.top <= local_30.bottom - local_30.top) {
    local_c = local_20.bottom - local_20.top;
  }
  if ((local_8 != 0) && (local_c != 0)) {
    iVar1 = surface_get_dib((DibSurface *)param_1);
    iVar2 = dib_is_top_down(iVar1);
    iVar3 = surface_get_pitch((DibSurface *)param_1);
    iVar3 = ((-(uint)(iVar2 == 0) & 0xfffffffe) + 1) * iVar3;
    iVar1 = surface_get_dib(this);
    iVar2 = dib_is_top_down(iVar1);
    iVar4 = surface_get_pitch(this);
    iVar4 = ((-(uint)(iVar2 == 0) & 0xfffffffe) + 1) * iVar4;
    uVar5 = surface_height((DibSurface *)param_1);
    uVar6 = surface_height(this);
    iVar7 = this->bytes_per_pixel * local_8;
    iVar8 = this->bytes_per_pixel * local_30.left;
    iVar9 = this->bytes_per_pixel * local_20.left;
    iVar2 = local_c;
    uVar10 = surface_get_bits((DibSurface *)param_1);
    uVar11 = surface_get_bits(this);
    gfx_copy_pixels(uVar11,uVar10,iVar9,local_20.top,iVar8,local_30.top,iVar7,iVar2,uVar6,uVar5,iVar4,
                 iVar3);
  }
  if (bVar12) {
    surface_unlock(this);
  }
  if (local_10 == 0) {
    surface_unlock((DibSurface *)param_1);
  }
  return;
}
#undef local_30
#undef local_20
#undef local_10
#undef local_c
#undef local_8

/* 005c0979 auto */
void __thiscall
surface_blit_to_wnd(DibSurface *this,iptr param_1,iptr param_2,iptr param_3)

{
  char cVar1;
  i32 uVar2;
  iptr iVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  
  if (this->dib == 0) {
    dbg_log(ADDR(0x6371a8, ((u8 *)&g.d_006371a8)));
  }
  else {
    cVar1 = surface_is_locked(this);
    if (cVar1 == '\0') {
      dbg_log(ADDR(0x6371cc, ((u8 *)&g.d_006371cc)));
      surface_lock(this);
    }
    uVar2 = wnd_get_palette_obj((WndPaletteObjView *)param_1);
    surface_apply_palette(this,uVar2);
    uVar2 = *(i32 *)(param_3 + 4);
    uVar6 = *(i32 *)param_3;
    iVar3 = wnd_get_window((WndBase *)param_1);
    uVar4 = rect_height(param_2);
    uVar5 = rect_width(param_2);
    dib_blit_to_wnd_obj(this->dib,*(i32 *)param_2,*(i32 *)(param_2 + 4),uVar5,uVar4,
                 iVar3,uVar6,uVar2);
    if (cVar1 == '\0') {
      surface_unlock(this);
    }
  }
  return;
}

/* 005c0bf2 auto */
uint __thiscall
surface_get_pixel(DibSurface *this,i32 param_1,i32 param_2)

{
  char cVar1;
  uint uVar2;
  byte *pbVar3;
  
  cVar1 = surface_in_clip(this,param_1,param_2);
  if (cVar1 == '\0') {
    dbg_logf_int2(ADDR(0x637250, ((u8 *)&g.d_00637250)),param_1,param_2);
    uVar2 = 0;
  }
  else {
    pbVar3 = (byte *)surface_pixel_ptr(this,param_1,param_2);
    uVar2 = (uint)*pbVar3;
  }
  return uVar2;
}

/* 005c0c5d auto */
void __thiscall
surface_set_pixel
          (DibSurface *this,i32 param_1,i32 param_2,i32 param_3)

{
  char cVar1;
  i8 *puVar2;
  
  cVar1 = surface_in_clip(this,param_1,param_2);
  if (cVar1 == '\0') {
    dbg_logf_int2(ADDR(0x637278, ((u8 *)&g.d_00637278)),param_1,param_2);
  }
  else {
    puVar2 = (i8 *)surface_pixel_ptr(this,param_1,param_2);
    *puVar2 = (i8)param_3;
  }
  return;
}

/* 005c0cc5 auto */
void __thiscall surface_set_palette(DibSurface *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = palette_get_version((PaletteVersionView *)param_1);
  if (uVar1 != this->palette_version) {
    dib_set_palette(this->dib,param_1);
    uVar1 = palette_get_version((PaletteVersionView *)param_1);
    this->palette_version = uVar1;
  }
  return;
}

/* 005c0d12 auto */
void __thiscall surface_apply_palette(DibSurface *this,PaletteVersionView *param_1)

{
  u32 uVar1;
  
  if (param_1 != (PaletteVersionView *)0x0) {
    uVar1 = palette_get_version(param_1);
    if (uVar1 != this->palette_version) {
      dib_set_palette(this->dib,(iptr)param_1);
      uVar1 = palette_get_version(param_1);
      this->palette_version = uVar1;
    }
  }
  return;
}

/* 005c0d69 auto */
#define gfx_black_color_index (*(i8 *)((u8 *)&g.d_00638b40))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
void __thiscall
surface_draw_text_cur_font(SurfaceTextCurFontView *this,i32 param_1,int param_2,int param_3,uint param_4)

{
  i8 uVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (draw_current_font == (i8 *)0x0) {
    dbg_log(ADDR(0x6372a0, ((u8 *)&g.d_006372a0)));
  }
  else if (this->dib != 0) {
    if ((param_4 & 0x10) != 0) {
      iVar2 = font_measure_height(*(i32 *)draw_current_font);
      iVar2 += (iVar2 >> 0x1f & 7U);
      iVar3 = iVar2 >> 3;
      uVar1 = gfx_set_text_color_index(CONCAT31((int3)(iVar2 >> 0xb),gfx_black_color_index));
      local_c = CONCAT31((*(i32 *)((char *)&local_c + 1)),uVar1);
      dib_draw_text_at(this->dib,*(i32 *)draw_current_font,param_1,iVar3 + param_2,
                   iVar3 + param_3,(iptr)(this->pad_0 + 0x14),param_4);
      gfx_set_text_color_index(local_c);
    }
    dib_draw_text_at(this->dib,*(i32 *)draw_current_font,param_1,param_2,param_3,
                 (iptr)(this->pad_0 + 0x14),param_4);
  }
  return;
}
#undef gfx_black_color_index
#undef local_c

/* 005c0f57 auto */
#define gfx_black_color_index (*(i8 *)((u8 *)&g.d_00638b40))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
void __thiscall
surface_draw_text
          (DibSurface *this,iptr param_1,iptr param_2,iptr param_3,int param_4,uint param_5)

{
  i8 uVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->dib != 0) {
    if ((param_5 & 0x10) != 0) {
      iVar2 = font_measure_height(*(i32 *)param_1);
      iVar2 += (iVar2 >> 0x1f & 7U);
      iVar3 = iVar2 >> 3;
      uVar1 = gfx_set_text_color_index(CONCAT31((int3)(iVar2 >> 0xb),gfx_black_color_index));
      local_c = CONCAT31((*(i32 *)((char *)&local_c + 1)),uVar1);
      dib_draw_text_at(this->dib,*(i32 *)param_1,param_2,param_3 + iVar3,param_4 + iVar3,
                   (iptr)&this->clip_left,param_5);
      gfx_set_text_color_index(local_c);
    }
    dib_draw_text_at(this->dib,*(i32 *)param_1,param_2,param_3,param_4,(iptr)&this->clip_left
                 ,param_5);
  }
  return;
}
#undef gfx_black_color_index
#undef local_c

/* 005c1020 auto */
#define gfx_black_color_index (*(i8 *)((u8 *)&g.d_00638b40))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __thiscall
surface_draw_text_in_rect(DibSurface *this,iptr param_1,iptr param_2,iptr param_3,uint param_4)

{
  i8 uVar1;
  int iVar2;
  BOOL BVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->dib != 0) {
    if ((param_4 & 0x10) != 0) {
      iVar2 = font_measure_height(*(i32 *)param_1);
      iVar2 = (int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3;
      local_14.left = *(LONG *)param_3;
      local_14.top = *(LONG *)(param_3 + 4);
      local_14.right = *(LONG *)(param_3 + 8);
      local_14.bottom = *(LONG *)(param_3 + 0xc);
      BVar3 = OffsetRect(&local_14,iVar2,iVar2);
      uVar1 = gfx_set_text_color_index(CONCAT31((int3)((uint)BVar3 >> 8),gfx_black_color_index));
      local_1c = CONCAT31((*(i32 *)((char *)&local_1c + 1)),uVar1);
      dib_draw_text_rect(this->dib,*(i32 *)param_1,param_2,(iptr)&local_14,param_4);
      gfx_set_text_color_index(local_1c);
    }
    dib_draw_text_rect(this->dib,*(i32 *)param_1,param_2,param_3,param_4);
  }
  return;
}
#undef gfx_black_color_index
#undef local_1c
#undef local_14

/* 005c1167 auto */
void __thiscall
surface_draw_text_rect
          (DibSurface *this,iptr param_1,iptr param_2,iptr param_3,i32 param_4)

{
  if (this->dib != 0) {
    dib_draw_text_wrap(this->dib,*(i32 *)param_1,param_2,param_3,param_4);
  }
  return;
}

/* 005c11b2 auto */
#define gfx_text_color_index (*(i8 *)((u8 *)&g.d_00637e78))
void __thiscall
surface_draw_line(DibSurface *this,u32 param_1,u32 param_2,u32 param_3,u32 param_4)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  i32 uVar4;
  i32 uVar5;
  u32 uVar6;
  
  if (((((((int)this->clip_left <= (int)param_1) || ((int)this->clip_left <= (int)param_3)) &&
        (((int)param_3 < (int)this->clip_right || ((int)param_1 < (int)this->clip_right)))) &&
       (((int)this->clip_top <= (int)param_2 || ((int)this->clip_top <= (int)param_4)))) &&
      (((int)param_2 < (int)this->clip_bottom || ((int)param_4 < (int)this->clip_bottom)))) &&
     (this->dib != 0)) {
    if (param_4 == param_2) {
      if ((int)param_1 < (int)this->clip_left) {
        param_1 = this->clip_left;
      }
      if ((int)this->clip_right <= (int)param_1) {
        param_1 = this->clip_right - 1;
      }
      if ((int)param_3 < (int)this->clip_left) {
        param_3 = this->clip_left;
      }
      if ((int)this->clip_right <= (int)param_3) {
        param_3 = this->clip_right - 1;
      }
      if (param_3 != param_1) {
        iVar1 = surface_get_dib(this);
        iVar2 = dib_is_top_down(iVar1);
        iVar3 = surface_get_pitch(this);
        iVar3 = ((-(uint)(iVar2 == 0) & 0xfffffffe) + 1) * iVar3;
        uVar4 = surface_height(this);
        uVar6 = param_3;
        if ((int)param_1 <= (int)param_3) {
          uVar6 = param_1;
        }
        iVar2 = crt_abs(param_3 - param_1);
        iVar2++;
        uVar5 = CONCAT31((int3)((uint)iVar2 >> 8),gfx_text_color_index);
        iVar1 = surface_get_bits(this);
        dib_hline8(iVar1,uVar5,iVar2,uVar6,param_2,uVar4,iVar3);
      }
    }
    else if (param_3 == param_1) {
      if ((int)param_2 < (int)this->clip_top) {
        param_2 = this->clip_top;
      }
      if ((int)this->clip_bottom <= (int)param_2) {
        param_2 = this->clip_bottom - 1;
      }
      if ((int)param_4 < (int)this->clip_top) {
        param_4 = this->clip_top;
      }
      if ((int)this->clip_bottom <= (int)param_4) {
        param_4 = this->clip_bottom - 1;
      }
      if (param_4 != param_2) {
        iVar1 = surface_get_dib(this);
        iVar2 = dib_is_top_down(iVar1);
        iVar3 = surface_get_pitch(this);
        iVar3 = ((-(uint)(iVar2 == 0) & 0xfffffffe) + 1) * iVar3;
        uVar4 = surface_height(this);
        uVar6 = param_4;
        if ((int)param_2 <= (int)param_4) {
          uVar6 = param_2;
        }
        iVar2 = crt_abs(param_4 - param_2);
        iVar2++;
        uVar5 = CONCAT31((int3)((uint)iVar2 >> 8),gfx_text_color_index);
        iVar1 = surface_get_bits(this);
        dib_vline8(iVar1,uVar5,iVar2,param_1,uVar6,uVar4,iVar3);
      }
    }
    else {
      dib_draw_line(this->dib,param_1,param_2,param_3,param_4);
    }
  }
  return;
}
#undef gfx_text_color_index

/* 005c19ad auto */
#define gfx_text_color_index (*(i8 *)((u8 *)&g.d_00637e78))
i8 __cdecl gfx_set_text_color_index(i32 param_1)

{
  i8 uVar1;
  
  uVar1 = gfx_text_color_index;
  gfx_text_color_index = (i8)param_1;
  return uVar1;
}
#undef gfx_text_color_index

/* 005c19d3 auto */
int __thiscall surface_pixel_ptr(DibSurface *this,int param_1,int param_2)

{
  return *(int *)(this->row_offsets + param_2 * 4) + this->bits + param_1;
}

/* 005c1a00 auto */
i8 __thiscall surface_in_clip(DibSurface *this,int param_1,int param_2)

{
  i8 uVar1;
  
  if ((((param_1 < (int)this->clip_left) || ((int)this->clip_right <= param_1)) ||
      (param_2 < (int)this->clip_top)) || ((int)this->clip_bottom <= param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 005c1a62 auto */
#define local_10 (*(byte * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall
surface_remap_colors(DibSurface *this,iptr param_1,iptr param_2,i32 param_3)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->bits != 0) {
    local_10 = (byte *)this->bits;
    for (local_8 = 0; local_8 < (int)this->pixel_height; local_8++) {
      for (local_c = 0; local_c < (int)this->pixel_width; local_c++) {
        if (-1 < (int)((uint)*local_10 - param_2)) {
          *local_10 = *(byte *)(((uint)*local_10 - param_2) + param_1);
        }
        local_10++;
      }
      local_10 += (this->stride - this->pixel_width);
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 005c1b47 auto */
i32 __thiscall surface_alloc_dib16(DibSurface *this,iptr param_1)

{
  char cVar1;
  u32 uVar2;
  int iVar3;
  
  if (this->dib != 0) {
    cVar1 = surface_is_locked(this);
    if (cVar1 != '\0') {
      surface_unlock(this);
    }
    uVar2 = dib_destroy(this->dib);
    this->dib = uVar2;
  }
  if (((param_1 != 0) && (iVar3 = rect_width(param_1), iVar3 != 0)) &&
     (iVar3 = rect_height(param_1), iVar3 != 0)) {
    surface_set_dims(this,param_1);
    uVar2 = dib_create16((iptr)&this->bounds_rect);
    this->dib = uVar2;
    if (this->dib != 0) {
      uVar2 = dib_get_stride(this->dib);
      this->stride = uVar2;
      iVar3 = dib_is_top_down(this->dib);
      if (iVar3 == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      this->bytes_per_pixel = 2;
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,ADDR(0x637318, ((u8 *)&g.d_00637318)),ADDR(0x637300, ((u8 *)&g.d_00637300)),0x86c);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005c1cf7 auto */
i32 __thiscall surface_alloc_dib24(DibSurface *this,iptr param_1)

{
  char cVar1;
  u32 uVar2;
  int iVar3;
  
  if (this->dib != 0) {
    cVar1 = surface_is_locked(this);
    if (cVar1 != '\0') {
      surface_unlock(this);
    }
    uVar2 = dib_destroy(this->dib);
    this->dib = uVar2;
  }
  if (((param_1 != 0) && (iVar3 = rect_width(param_1), iVar3 != 0)) &&
     (iVar3 = rect_height(param_1), iVar3 != 0)) {
    surface_set_dims(this,param_1);
    uVar2 = dib_create24((iptr)&this->bounds_rect);
    this->dib = uVar2;
    if (this->dib != 0) {
      uVar2 = dib_get_stride(this->dib);
      this->stride = uVar2;
      iVar3 = dib_is_top_down(this->dib);
      if (iVar3 == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      this->bytes_per_pixel = 3;
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,ADDR(0x637344, ((u8 *)&g.d_00637344)),ADDR(0x63732c, ((u8 *)&g.d_0063732c)),0x8a1);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005c1ea7 auto */
i32 __thiscall surface_alloc_dib32(DibSurface *this,iptr param_1)

{
  char cVar1;
  u32 uVar2;
  int iVar3;
  
  if (this->dib != 0) {
    cVar1 = surface_is_locked(this);
    if (cVar1 != '\0') {
      surface_unlock(this);
    }
    uVar2 = dib_destroy(this->dib);
    this->dib = uVar2;
  }
  if (((param_1 != 0) && (iVar3 = rect_width(param_1), iVar3 != 0)) &&
     (iVar3 = rect_height(param_1), iVar3 != 0)) {
    surface_set_dims(this,param_1);
    uVar2 = dib_create32((iptr)&this->bounds_rect);
    this->dib = uVar2;
    if (this->dib != 0) {
      uVar2 = dib_get_stride(this->dib);
      this->stride = uVar2;
      iVar3 = dib_is_top_down(this->dib);
      if (iVar3 == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      this->bytes_per_pixel = 4;
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,ADDR(0x637370, ((u8 *)&g.d_00637370)),ADDR(0x637358, ((u8 *)&g.d_00637358)),0x8d6);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005c54f0 auto */
bool __thiscall surface_is_locked(DibSurface *this)

{
  return this->bits != 0;
}

/* 005c55a0 auto */
int __cdecl dib_row_align4(int param_1)

{
  return ((int)(param_1 + 3 + (param_1 + 3 >> 0x1f & 3U)) >> 2) << 2;
}

/* 005c55d0 auto */
u32 __thiscall surface_get_pitch(DibSurface *this)

{
  return this->stride;
}

/* 005c55f0 auto */
/* Library Function - Single Match
    public: unsigned int __thiscall CCheckListBox::GetCheckStyle(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall surface_get_dib(DibSurface *this)

{
  return this->dib;
}

/* 005c5610 auto */
int __thiscall surface_next_row(DibSurface *this,iptr param_1)

{
  return this->signed_pitch + param_1;
}

/* 005c5640 auto */
uptr __thiscall surface_get_bits(DibSurface *this)

{
  return this->bits;
}

/* 005c56f0 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall palette_get_version(PaletteVersionView *this)

{
  return this->pal_version;
}

/* 005c5710 auto */
int __thiscall surface_prev_row(DibSurface *this,iptr param_1)

{
  return param_1 - this->signed_pitch;
}

/* 005c6480 auto */
void __thiscall palette_commit_range(GamePalette *this,int param_1,int param_2)

{
  if (0x100 < param_2 + param_1) {
    param_2 = 0x100 - param_1;
  }
  logpal_apply_range((iptr)this,this->hpalette,param_1,param_2);
  palette_new_version(this);
  return;
}

/* 005c64da auto */
GamePalette * __thiscall palette_init(GamePalette *this)

{
  u32 uVar1;
  
  logpal_init_from_system((iptr)this);
  uVar1 = logpal_create_hpalette((iptr)this);
  this->hpalette = uVar1;
  palette_new_version(this);
  this->tint_red = '\0';
  this->tint_green = '\0';
  this->tint_blue = '\0';
  this->tint_saved_rgb = 0;
  this->fade_dst_rgb = this->tint_saved_rgb;
  this->fade_src_rgb = this->fade_dst_rgb;
  return this;
}

/* 005c656b auto */
GamePalette * __thiscall palette_destroy(GamePalette *this)

{
  logpal_delete_hpalette(this->hpalette);
  if (this->fade_src_rgb != 0) {
    mem_handle_free(this->fade_src_rgb);
  }
  if (this->fade_dst_rgb != 0) {
    mem_handle_free(this->fade_dst_rgb);
  }
  if (this->tint_saved_rgb != 0) {
    this = (GamePalette *)mem_handle_free(this->tint_saved_rgb);
  }
  return this;
}

/* 005c65f9 auto */
#define local_8 (*(i8 *)(frame_ + FRAME_OFF(0)))
#define local_7 (*(i8 *)(frame_ + FRAME_OFF(1)))
#define local_6 (*(i8 *)(frame_ + FRAME_OFF(2)))
#define local_5 (*(i8 *)(frame_ + FRAME_OFF(3)))
void __thiscall palette_load_ctab_res(GamePalette *this,i32 param_1)

{
  int iVar1;
  i32 *puVar2;
  i32 uVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0x43;
  local_7 = 0x54;
  local_6 = 0x41;
  local_5 = 0x42;
  iVar1 = res_load((iptr)&local_8,param_1);
  if (iVar1 == 0) {
    dbg_logf_noret(ADDR(0x637bec, ((u8 *)&g.d_00637bec)),param_1);
  }
  else {
    puVar2 = (i32 *)res_lock(iVar1);
    uVar3 = endian_from_le(*puVar2);
    uVar4 = endian_from_le(puVar2[1]);
    palette_set_rgb(this,uVar3,uVar4,(iptr)(puVar2 + 2));
    res_unlock(iVar1);
    res_free(iVar1);
  }
  return;
}
#undef local_8
#undef local_7
#undef local_6
#undef local_5

/* 005c6a42 auto */
void __thiscall palette_new_version(GamePalette *this)

{
  uint uVar1;
  
  this->pal_version = 0;
  while (this->pal_version == 0) {
    uVar1 = _rand();
    this->pal_version = uVar1 & 0x7fff;
  }
  return;
}

/* 005c6a8d auto */
void __thiscall
palette_reserve_range(GamePalette *this,i32 param_1,i32 param_2)

{
  logpal_reserve_range((iptr)this,param_1,param_2);
  palette_commit_range(this,param_1,param_2);
  return;
}

/* 005c6b63 auto */
void __thiscall
palette_get_rgb
          (GamePalette *this,iptr param_1,i32 param_2,i32 param_3)

{
  palette_copy_rgb_range((iptr)this,param_1,param_2,param_3);
  return;
}

/* 005c6b93 auto */
void __thiscall
palette_set_entry
          (GamePalette *this,i32 param_1,i32 param_2,i32 param_3,
          i32 param_4)

{
  palette_set_entry_rgb((iptr)this,param_1,param_2,param_3,param_4);
  palette_commit_range(this,param_1,1);
  return;
}

/* 005c6da8 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall
palette_set_rgb(GamePalette *this,int param_1,int param_2,iptr param_3)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (0x100 < param_2 + param_1) {
    param_2 = 0x100 - param_1;
  }
  for (local_8 = param_1; local_8 < param_2 + param_1; local_8++) {
    uVar1 = (i32)((uint)param_3 >> 8);
    palette_set_entry_rgb((iptr)this,local_8,CONCAT31(uVar1,*(i8 *)param_3),
                 CONCAT31(uVar1,*(i8 *)(param_3 + 1)),
                 CONCAT31(uVar1,*(i8 *)(param_3 + 2)));
    param_3 += 3;
  }
  palette_commit_range(this,param_1,param_2);
  return;
}
#undef local_8

/* 005c71f3 auto */
void __thiscall
palette_fade_begin(GamePalette *this,u32 param_1,u32 param_2,u32 param_3,iptr param_4)

{
  u32 uVar1;
  iptr iVar2;
  iptr iVar3;
  u32 uVar4;
  
  this->fade_steps = param_3;
  this->fade_first = param_1;
  this->fade_count = param_2;
  uVar1 = mem_handle_alloc(param_2 * 3);
  this->fade_src_rgb = uVar1;
  uVar1 = mem_handle_alloc(param_2 * 3);
  this->fade_dst_rgb = uVar1;
  iVar2 = mem_handle_lock(this->fade_src_rgb);
  palette_copy_rgb_range((iptr)this,iVar2,param_1,param_2);
  mem_handle_unlock(this->fade_src_rgb);
  iVar2 = mem_handle_lock(this->fade_dst_rgb);
  uVar1 = param_1;
  uVar4 = param_2;
  iVar3 = palette_get_logpalette((GamePalette *)param_4);
  palette_copy_rgb_range(iVar3,iVar2,uVar1,uVar4);
  mem_handle_unlock(this->fade_dst_rgb);
  palette_reserve_range(this,param_1,param_2);
  return;
}

/* 005c72f8 auto */
void __thiscall palette_fade_end(GamePalette *this)

{
  iptr iVar1;
  u32 uVar2;
  
  iVar1 = mem_handle_lock(this->fade_src_rgb);
  palette_set_rgb(this,this->fade_first,this->fade_count,iVar1);
  mem_handle_unlock(this->fade_src_rgb);
  uVar2 = mem_handle_free(this->fade_src_rgb);
  this->fade_src_rgb = uVar2;
  uVar2 = mem_handle_free(this->fade_dst_rgb);
  this->fade_dst_rgb = uVar2;
  return;
}

/* 005c738e auto */
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
void __thiscall palette_fade_step(GamePalette *this,int param_1)

{
  char cVar1;
  char cVar2;
  iptr iVar3;
  iptr iVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 < 0) || ((int)this->fade_steps < param_1)) {
    dbg_logf(ADDR(0x637c54, ((u8 *)&g.d_00637c54)),param_1);
  }
  else {
    cVar2 = (char)param_1;
    cVar1 = (char)this->fade_steps - cVar2;
    iVar3 = mem_handle_lock(this->fade_src_rgb);
    iVar4 = mem_handle_lock(this->fade_dst_rgb);
    for (local_18 = 0; local_18 < (int)(this->fade_count * 3); local_18 += 3) {
      local_10 = CONCAT31((*(i32 *)((char *)&local_10 + 1)),
                          (char)((longlong)(ulonglong)*(byte *)(local_18 + iVar4) /
                                (longlong)(int)this->fade_steps) * cVar1 +
                          (char)((longlong)(ulonglong)*(byte *)(local_18 + iVar3) /
                                (longlong)(int)this->fade_steps) * cVar2);
      local_14 = CONCAT31((*(i32 *)((char *)&local_14 + 1)),
                          (char)((longlong)(ulonglong)*(byte *)(local_18 + 1 + iVar3) /
                                (longlong)(int)this->fade_steps) * cVar2 +
                          (char)((longlong)(ulonglong)*(byte *)(local_18 + 1 + iVar4) /
                                (longlong)(int)this->fade_steps) * cVar1);
      local_c = CONCAT31((*(i32 *)((char *)&local_c + 1)),
                         (char)((longlong)(ulonglong)*(byte *)(local_18 + 2 + iVar4) /
                               (longlong)(int)this->fade_steps) * cVar1 +
                         (char)((longlong)(ulonglong)*(byte *)(local_18 + 2 + iVar3) /
                               (longlong)(int)this->fade_steps) * cVar2);
      logpal_set_entry((iptr)this,this->fade_first + local_18 / 3,local_10,local_14,local_c);
    }
    palette_animate((iptr)this,this->hpalette,this->fade_first,this->fade_count);
    mem_handle_unlock(this->fade_src_rgb);
    mem_handle_unlock(this->fade_dst_rgb);
  }
  return;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 005c8200 auto */
#define local_4c (*(LOGFONTA *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(64)))
#define local_c (*(HFONT *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(72)))
i32 __cdecl font_handle_create(i32 param_1,int param_2,i32 param_3)

{
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_4c.lfHeight = -param_2;
  local_4c.lfWidth = 0;
  local_4c.lfEscapement = 0;
  local_4c.lfOrientation = 0;
  local_4c.lfCharSet = 1;
  local_4c.lfOutPrecision = 4;
  local_4c.lfClipPrecision = 1;
  local_4c.lfQuality = '\0';
  local_4c.lfPitchAndFamily = '\0';
  if (((byte)param_3 & 1) == 0) {
    local_4c.lfWeight = 400;
  }
  else {
    local_4c.lfWeight = 700;
  }
  local_4c.lfItalic = (byte)param_3 & 2;
  local_4c.lfUnderline = (byte)param_3 & 4;
  local_4c.lfStrikeOut = (byte)param_3 & 8;
  switch(param_1) {
  case 0:
    local_4c.lfPitchAndFamily = 16;
    crt_strcpy(local_4c.lfFaceName,s_Times_New_Roman_00637c74);
    break;
  case 1:
    local_4c.lfPitchAndFamily = ' ';
    crt_strcpy(local_4c.lfFaceName,s_Arial_00637c84);
    break;
  case 2:
    crt_strcpy(local_4c.lfFaceName,s_System_00637c94);
    break;
  case 3:
    local_4c.lfPitchAndFamily = '0';
    crt_strcpy(local_4c.lfFaceName,s_Courier_00637c8c);
  }
  local_10 = 0;
  local_c = CreateFontIndirectA(&local_4c);
  if (local_c != (HFONT)0x0) {
    local_10 = mem_handle_alloc(8);
    local_8 = (i32 *)mem_handle_lock(local_10);
    *local_8 = local_c;
    local_8[1] = 1;
    mem_handle_unlock(local_10);
  }
  return local_10;
}
#undef local_4c
#undef local_10
#undef local_c
#undef local_8

/* 005c841d auto */
i32 __cdecl font_handle_destroy(i32 param_1)

{
  i32 *puVar1;
  i32 uVar2;
  
  puVar1 = (i32 *)mem_handle_lock(param_1);
  if (puVar1 == (i32 *)0x0) {
    uVar2 = 0;
  }
  else {
    if (puVar1[1] == 1) {
      DeleteObject((HGDIOBJ)*puVar1);
    }
    mem_handle_unlock(param_1);
    uVar2 = mem_handle_free(param_1);
  }
  return uVar2;
}

/* 005c847f auto */
#define local_40 (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(56)))
LONG __cdecl font_measure_height(i32 param_1)

{
  int iVar1;
  HDC hdc;
  HGDIOBJ h;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = mem_handle_size(param_1);
  if (iVar1 == 0) {
    local_40.tmHeight = 1;
  }
  else {
    local_8 = (i32 *)mem_handle_lock(param_1);
    hdc = GetDC((HWND)0x0);
    h = SelectObject(hdc,(HGDIOBJ)*local_8);
    GetTextMetricsA(hdc,&local_40);
    SelectObject(hdc,h);
    ReleaseDC((HWND)0x0,hdc);
    mem_handle_unlock(param_1);
  }
  return local_40.tmHeight;
}
#undef local_40
#undef local_8

/* 005c8514 auto */
#define local_40 (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(56)))
int __cdecl font_handle_line_spacing(i32 param_1)

{
  HDC hdc;
  HGDIOBJ h;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (i32 *)mem_handle_lock(param_1);
  hdc = GetDC((HWND)0x0);
  h = SelectObject(hdc,(HGDIOBJ)*local_8);
  GetTextMetricsA(hdc,&local_40);
  SelectObject(hdc,h);
  ReleaseDC((HWND)0x0,hdc);
  mem_handle_unlock(param_1);
  return local_40.tmExternalLeading + local_40.tmHeight;
}
#undef local_40
#undef local_8

/* 005c858e auto */
#define local_10 (*(tagSIZE *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(8)))
LONG __cdecl font_measure_width(i32 param_1,iptr param_2)

{
  HDC hdc;
  HGDIOBJ h;
  size_t c;
  tagSIZE *lpsz;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (i32 *)mem_handle_lock(param_1);
  hdc = GetDC((HWND)0x0);
  h = SelectObject(hdc,(HGDIOBJ)*local_8);
  lpsz = &local_10;
  c = _strlen((char *)param_2);
  GetTextExtentPointA(hdc,(LPCSTR)param_2,c,lpsz);
  SelectObject(hdc,h);
  ReleaseDC((HWND)0x0,hdc);
  mem_handle_unlock(param_1);
  return local_10.cx;
}
#undef local_10
#undef local_8

/* 005c8791: written by hand in src/game/fixups.c */

/* 005c8c83 auto */
void __cdecl region_dispose(int param_1)

{
  if (param_1 == 0) {
    dbg_log(ADDR(0x637cb8, ((u8 *)&g.d_00637cb8)));
  }
  return;
}

/* 005c8caf: written by hand in src/game/fixups.c */

/* 005cbdb0 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall palette_get_hpalette(PaletteHandleView *this)

{
  return this->hpalette;
}

/* 005cd6e0 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl gfx_scale_init(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    *(i32 *)(&gfx_scale_cache_last_used + local_8 * 0x100c) = 0;
    *(i32 *)(&gfx_scale_cache_num + local_8 * 0x100c) = 0;
    *(i32 *)(&gfx_scale_cache_den + local_8 * 0x100c) = 0;
  }
  gfx_set_scale_ratio(1,1);
  gfx_set_scale_tables(1,1,1,1);
  return;
}
#undef local_8

/* 005cd775 auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_set_scale_ratio(int param_1,int param_2)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 < 2) {
    param_1 = 1;
  }
  if (param_2 < 2) {
    param_2 = 1;
  }
  gfx_scale_num = param_1;
  gfx_scale_den = param_2;
  local_10 = timer_ticks();
  local_18 = -1;
  local_14 = 0;
  do {
    if (0xf < local_14) {
      *(int *)(&gfx_scale_cache_num + local_18 * 0x100c) = gfx_scale_num;
      *(int *)(&gfx_scale_cache_den + local_18 * 0x100c) = gfx_scale_den;
      uVar1 = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + local_18 * 0x100c) = uVar1;
      local_8 = 0;
      if (gfx_scale_num < gfx_scale_den) {
        local_c = 0;
        local_14 = 0;
        while (local_14 < 0x400) {
          for (; (-1 < local_c && (local_14 < 0x400)); local_14++) {
            *(int *)(&gfx_scale_cache_tables + local_14 * 4 + local_18 * 0x100c) = local_8;
            local_c -= gfx_scale_den;
          }
          local_c += gfx_scale_num;
          local_8++;
        }
      }
      else {
        local_c = gfx_scale_num;
        local_14 = 0;
        while (local_14 < 0x400) {
          for (; (gfx_scale_den <= local_c && (local_14 < 0x400)); local_14++) {
            *(int *)(&gfx_scale_cache_tables + local_14 * 4 + local_18 * 0x100c) = local_8;
            local_c -= gfx_scale_den;
          }
          local_c += gfx_scale_num;
          local_8++;
        }
      }
LAB_005cda01:
      gfx_scale_table = (int)&gfx_scale_cache_tables + local_18 * 0x100c;
      return;
    }
    if ((*(int *)(&gfx_scale_cache_num + local_14 * 0x100c) == gfx_scale_num) &&
       (*(int *)(&gfx_scale_cache_den + local_14 * 0x100c) == gfx_scale_den)) {
      uVar1 = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + local_14 * 0x100c) = uVar1;
      local_18 = local_14;
      goto LAB_005cda01;
    }
    if (*(int *)(&gfx_scale_cache_last_used + local_14 * 0x100c) <= local_10) {
      local_10 = *(int *)(&gfx_scale_cache_last_used + local_14 * 0x100c);
      local_18 = local_14;
    }
    local_14++;
  } while( true );
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005cda06 auto */
#define gfx_scale_den (*(i32 *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(i32 *)((u8 *)&g.d_00637f98))
void __cdecl gfx_get_scale_ratio(iptr param_1,iptr param_2)

{
  *(i32 *)param_1 = gfx_scale_num;
  *(i32 *)param_2 = gfx_scale_den;
  return;
}
#undef gfx_scale_den
#undef gfx_scale_num

/* 005cda2a auto */
#define gfx_scale_x_table (*(i8 * *)((u8 *)&g.d_006e47c0))
#define gfx_scale_y_table (*(i8 * *)((u8 *)&g.d_006e47c4))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_set_scale_tables(int param_1,int param_2,int param_3,int param_4)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 < 2) {
    param_1 = 1;
  }
  if (param_2 < 2) {
    param_2 = 1;
  }
  if (param_3 < 2) {
    param_3 = 1;
  }
  if (param_4 < 2) {
    param_4 = 1;
  }
  gfx_scale_x_num = param_1;
  gfx_scale_x_den = param_2;
  gfx_scale_y_num = param_3;
  gfx_scale_y_den = param_4;
  local_10 = timer_ticks();
  local_8 = -1;
  for (local_14 = 0; local_14 < 0x10; local_14++) {
    if ((*(int *)(&gfx_scale_cache_num + local_14 * 0x100c) == gfx_scale_x_num) &&
       (*(int *)(&gfx_scale_cache_den + local_14 * 0x100c) == gfx_scale_x_den)) {
      uVar1 = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + local_14 * 0x100c) = uVar1;
      local_8 = local_14;
      goto LAB_005cdbab;
    }
    if (*(int *)(&gfx_scale_cache_last_used + local_14 * 0x100c) <= local_10) {
      local_10 = *(int *)(&gfx_scale_cache_last_used + local_14 * 0x100c);
      local_8 = local_14;
    }
  }
  gfx_scale_build_table(local_8,gfx_scale_x_num,gfx_scale_x_den);
LAB_005cdbab:
  gfx_scale_x_table = &gfx_scale_cache_tables + local_8 * 0x100c;
  local_10 = timer_ticks();
  local_c = -1;
  local_14 = 0;
  do {
    if (0xf < local_14) {
      gfx_scale_build_table(local_c,gfx_scale_y_num,gfx_scale_y_den);
      local_14 = local_c;
LAB_005cdcd6:
      gfx_scale_y_table = &gfx_scale_cache_tables + local_14 * 0x100c;
      return;
    }
    if ((*(int *)(&gfx_scale_cache_num + local_14 * 0x100c) == gfx_scale_y_num) &&
       (*(int *)(&gfx_scale_cache_den + local_14 * 0x100c) == gfx_scale_y_den)) {
      uVar1 = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + local_14 * 0x100c) = uVar1;
      goto LAB_005cdcd6;
    }
    if ((*(int *)(&gfx_scale_cache_last_used + local_14 * 0x100c) <= local_10) && (local_8 != local_14)) {
      local_10 = *(int *)(&gfx_scale_cache_last_used + local_14 * 0x100c);
      local_c = local_14;
    }
    local_14++;
  } while( true );
}
#undef gfx_scale_x_table
#undef gfx_scale_y_table
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005cdcdb auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl gfx_scale_build_table(int param_1,int param_2,int param_3)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(int *)(&gfx_scale_cache_num + param_1 * 0x100c) = param_2;
  *(int *)(&gfx_scale_cache_den + param_1 * 0x100c) = param_3;
  uVar1 = timer_ticks();
  *(i32 *)(&gfx_scale_cache_last_used + param_1 * 0x100c) = uVar1;
  local_8 = 0;
  if (param_2 < param_3) {
    local_c = 0;
    local_10 = 0;
    while (local_10 < 0x400) {
      for (; (-1 < local_c && (local_10 < 0x400)); local_10++) {
        *(int *)(&gfx_scale_cache_tables + local_10 * 4 + param_1 * 0x100c) = local_8;
        local_c -= param_3;
      }
      local_c += param_2;
      local_8++;
    }
  }
  else {
    local_c = param_2;
    local_10 = 0;
    while (local_10 < 0x400) {
      for (; (param_3 <= local_c && (local_10 < 0x400)); local_10++) {
        *(int *)(&gfx_scale_cache_tables + local_10 * 4 + param_1 * 0x100c) = local_8;
        local_c -= param_3;
      }
      local_c += param_2;
      local_8++;
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 005cde2c auto */
/* Library Function - Single Match
    public: __thiscall CString::CString(void)
   
   Library: Visual Studio 1998 Debug */

Sprite * __thiscall sprite_init(Sprite *this)

{
  sprite_clear_fields(this);
  return this;
}

/* 005cde4d auto */
Sprite * __thiscall sprite_destroy(Sprite *this)

{
  uptr uVar1;
  
  if (this->data_handle != 0) {
    if (this->data_ptr != 0) {
      uVar1 = mem_handle_unlock(this->data_handle);
      this->data_ptr = uVar1;
    }
    this = (Sprite *)mem_handle_free(this->data_handle);
  }
  return this;
}

/* 005cdea1 auto */
#define local_58 (*(DibSurface *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(76)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(80)))
i32 __thiscall
sprite_create_solid(Sprite *this,i32 param_1,i32 param_2,uint param_3)

{
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_58);
  local_8 = 0;
  surface_create(&local_58,param_1,param_2);
  surface_fill(&local_58,param_3 & 0xff);
  sprite_encode_rect(this,(iptr)&local_58,0,0,param_1,param_2);
  SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005cdf2d */ { surface_dtor((DibSurface *)((iptr)&local_58)); }
  return uStack_10;
}
#undef local_58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005cdf50 auto */
void __thiscall sprite_free(Sprite *this)

{
  uptr uVar1;
  u32 uVar2;
  
  if (this->data_ptr != 0) {
    uVar1 = mem_handle_unlock(this->data_handle);
    this->data_ptr = uVar1;
  }
  if (this->data_handle != 0) {
    uVar2 = mem_handle_free(this->data_handle);
    this->data_handle = uVar2;
  }
  sprite_clear_fields(this);
  return;
}

/* 005cebb4 auto */
void __thiscall sprite_grab_surface_rect(Sprite *this,iptr param_1,iptr param_2)

{
  u32 uVar1;
  
  uVar1 = sprite_encode_from_surface(this,param_1,0xffffffff,param_2);
  this->data_handle = uVar1;
  sprite_lock(this);
  return;
}

/* 005cebec auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall
sprite_encode_rect
          (Sprite *this,iptr param_1,int param_2,int param_3,int param_4,int param_5)

{
  u32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&local_14,param_2,param_3,param_2 + param_4,param_5 + param_3);
  uVar1 = sprite_encode_from_surface(this,param_1,0xffffffff,(iptr)&local_14);
  this->data_handle = uVar1;
  sprite_lock(this);
  return;
}
#undef local_14

/* 005cec44 auto */
void __thiscall
sprite_grab_rect(Sprite *this,iptr param_1,uint param_2,iptr param_3)

{
  u32 uVar1;
  
  uVar1 = sprite_encode_from_surface(this,param_1,param_2 & 0xff,param_3);
  this->data_handle = uVar1;
  sprite_lock(this);
  return;
}

/* 005cedad auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall
sprite_grab_from_surface
          (Sprite *this,iptr param_1,uint param_2,int param_3,int param_4,int param_5,
          int param_6)

{
  u32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&local_14,param_3,param_4,param_5 + param_3,param_6 + param_4);
  uVar1 = sprite_encode_from_surface(this,param_1,param_2 & 0xff,(iptr)&local_14);
  this->data_handle = uVar1;
  sprite_lock(this);
  return;
}
#undef local_14

/* 005cef31 auto */
iptr __thiscall
sprite_draw
          (Sprite *this,iptr param_1,iptr param_2,i32 param_3,i32 param_4)

{
  sprite_blit_to_surface(this,param_1,param_2,0xffffffff,param_3,param_4);
  return param_1;
}

/* 005cef66 auto */
iptr __thiscall
sprite_draw_keyed
          (Sprite *this,iptr param_1,iptr param_2,uint param_3,i32 param_4,
          i32 param_5)

{
  sprite_blit_to_surface(this,param_1,param_2,param_3 & 0xff,param_4,param_5);
  return param_1;
}

/* 005cf126 auto */
iptr __thiscall
sprite_draw_silhouette
          (Sprite *this,iptr param_1,iptr param_2,i32 param_3,i32 param_4,
          i32 param_5)

{
  sprite_blit_silhouette_to_surface(this,param_1,param_2,0xffffffff,param_3,param_4,param_5);
  return param_1;
}

/* 005cf23f auto */
void __thiscall sprite_merge_onto(Sprite *this,iptr param_1)

{
  sprite_merge_at(this,(iptr)this,param_1,0,0,0);
  return;
}

/* 005cf2ff auto */
void __thiscall sprite_lock(Sprite *this)

{
  uptr uVar1;
  
  if (this->data_ptr == 0) {
    uVar1 = mem_handle_lock(this->data_handle);
    this->data_ptr = uVar1;
  }
  return;
}

/* 005cf337 auto */
void __thiscall sprite_unlock(Sprite *this)

{
  uptr uVar1;
  
  if (this->data_ptr != 0) {
    uVar1 = mem_handle_unlock(this->data_handle);
    this->data_ptr = uVar1;
  }
  return;
}

/* 005cf36f auto */
bool __thiscall sprite_has_data(Sprite *this)

{
  return this->data_ptr != 0;
}

/* 005cf39b auto */
void __thiscall sprite_set_origin(SpriteOriginSetView *this,u32 param_1,u32 param_2)

{
  this->origin_x = param_1;
  this->origin_y = param_2;
  return;
}

/* 005cf3c5 auto */
void __thiscall sprite_get_origin(SpriteOriginGetView *this,iptr param_1,iptr param_2)

{
  *(u32 *)param_1 = this->origin_x;
  *(u32 *)param_2 = this->origin_y;
  return;
}

/* 005cf467 auto */
#define local_14 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall
sprite_replace_color(Sprite *this,i32 param_1,i32 param_2)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  cVar3 = sprite_has_data(this);
  if (cVar3 == '\0') {
    sprite_lock(this);
    dbg_log(ADDR(0x637ff8, ((u8 *)&g.d_00637ff8)));
  }
  local_8 = rect_height((iptr)&this->bounds_rect);
  local_14 = (char *)this->data_ptr;
  while (iVar1 = local_8 - 1, local_8 != 0) {
    piVar2 = (int *)(local_14 + 4);
    local_14 += 8;
    local_c = *piVar2;
    while (local_8 = iVar1, local_c != 0) {
      if (*local_14 == (char)param_1) {
        *local_14 = (char)param_2;
      }
      local_14++;
      local_c--;
    }
  }
  if (cVar3 == '\0') {
    sprite_unlock(this);
  }
  return;
}
#undef local_14
#undef local_c
#undef local_8

/* 005cf64c auto */
#define local_64 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_54 (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_4c (*(i32 * *)(frame_ + FRAME_OFF(28)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_40 (*(u8 *)(frame_ + FRAME_OFF(40)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_38 (*(void * *)(frame_ + FRAME_OFF(48)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_2c (*(u8 * *)(frame_ + FRAME_OFF(60)))
#define local_28 (*(u8 * *)(frame_ + FRAME_OFF(64)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(68)))
#define local_20 (*(void * *)(frame_ + FRAME_OFF(72)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_8 (*(void * *)(frame_ + FRAME_OFF(96)))
int __thiscall
sprite_encode_from_surface(Sprite *this,iptr param_1,int param_2,iptr param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  u32 uVar4;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 1;
  local_48 = 1;
  SetRect(&local_64,*(int *)param_3,*(int *)(param_3 + 4),*(int *)(param_3 + 8),
          *(int *)(param_3 + 0xc));
  IntersectRect(&local_64,&local_64,(RECT *)(param_1 + 0x14));
  local_1c = 10000;
  local_14 = 0;
  local_c = 0;
  local_24 = local_64.right - local_64.left;
  local_50 = local_64.bottom - local_64.top;
  cVar1 = surface_is_locked((DibSurface *)param_1);
  if (cVar1 == '\0') {
    dbg_log(ADDR(0x638050, ((u8 *)&g.d_00638050)));
    local_34 = 0;
    surface_lock((DibSurface *)param_1);
  }
  local_2c = (u8 *)surface_pixel_ptr((DibSurface *)param_1,local_64.left,local_64.top);
  if (local_2c == (u8 *)0x0) {
    dbg_logf_int2(ADDR(0x63807c, ((u8 *)&g.d_0063807c)),local_64.left,local_64.top);
    if (local_34 == 0) {
      surface_unlock((DibSurface *)param_1);
    }
    local_30 = 0;
  }
  else {
    if (param_2 == -1) {
      local_40 = *local_2c;
    }
    else if (param_2 != -2) {
      local_40 = (u8)param_2;
    }
    local_44 = 0;
    while (local_44 < local_50) {
      local_54 = local_2c;
      for (local_3c = 0; local_3c < local_24; local_3c++) {
        if ((*local_54 != local_40) || (param_2 == -2)) {
          local_18 = local_44;
          local_54++;
          local_2c = (u8 *)surface_prev_row((DibSurface *)param_1,(iptr)local_2c);
          local_44 = local_50;
          local_48 = 0;
          break;
        }
        local_54++;
      }
      local_44++;
      local_2c = (u8 *)surface_next_row((DibSurface *)param_1,(iptr)local_2c);
    }
    if (local_48 == 0) {
      local_28 = (u8 *)surface_pixel_ptr
                                 ((DibSurface *)param_1,local_64.left,
                                  local_64.top + local_50 - 1);
      local_44 = 0;
      while (local_44 < local_50) {
        local_54 = local_28;
        for (local_3c = 0; local_3c < local_24; local_3c++) {
          if ((*local_54 != local_40) || (param_2 == -2)) {
            local_10 = local_50 - local_44;
            local_44 = local_50;
            local_54++;
            break;
          }
          local_54++;
        }
        local_44++;
        local_28 = (u8 *)surface_prev_row((DibSurface *)param_1,(iptr)local_28);
      }
      local_8 = operator_new(0xa00);
      local_20 = operator_new(0xa00);
      local_38 = operator_new(0xa00);
      if (((local_8 == (void *)0x0) || (local_20 == (void *)0x0)) || (local_38 == (void *)0x0)) {
        dbg_log(ADDR(0x6380b0, ((u8 *)&g.d_006380b0)));
        local_30 = 0;
      }
      else {
        local_44 = 0;
        while (local_44 < local_10 - local_18) {
          local_c += 8;
          *(i32 *)((int)local_20 + local_44 * 4) = 0;
          *(i32 *)((int)local_38 + local_44 * 4) = 0;
          local_54 = local_2c;
          for (local_3c = 0; local_3c < local_24; local_3c++) {
            if ((*local_54 != local_40) || (param_2 == -2)) {
              *(u8 **)((int)local_8 + local_44 * 4) = local_54;
              *(int *)((int)local_20 + local_44 * 4) = local_3c;
              break;
            }
            local_54++;
          }
          if ((local_24 != local_3c) && (*(int *)((int)local_20 + local_44 * 4) < local_1c)) {
            local_1c = *(int *)((int)local_20 + local_44 * 4);
          }
          local_54 = local_2c + local_24;
          for (local_3c = 0; local_54 = local_54 - 1, local_3c < local_24; local_3c++)
          {
            if ((*local_54 != local_40) || (param_2 == -2)) {
              *(iptr *)((int)local_38 + local_44 * 4) =
                   (local_24 - local_3c) - *(int *)((int)local_20 + local_44 * 4);
              local_c += *(int *)((int)local_38 + local_44 * 4);
              break;
            }
          }
          if ((local_24 != local_3c) &&
             (local_14 <
              *(int *)((int)local_38 + local_44 * 4) + *(int *)((int)local_20 + local_44 * 4))) {
            local_14 = *(int *)((int)local_38 + local_44 * 4) +
                       *(int *)((int)local_20 + local_44 * 4);
          }
          local_44++;
          local_2c = (u8 *)surface_next_row((DibSurface *)param_1,(iptr)local_2c);
        }
        if (this->data_ptr != 0) {
          sprite_unlock(this);
        }
        if (this->data_handle != 0) {
          uVar4 = mem_handle_free(this->data_handle);
          this->data_handle = uVar4;
        }
        local_c += 8;
        local_30 = mem_handle_alloc(local_c);
        if (local_30 == 0) {
          dbg_logf(ADDR(0x6380ec, ((u8 *)&g.d_006380ec)),local_c);
          if (local_34 == 0) {
            surface_unlock((DibSurface *)param_1);
          }
          operator_delete(local_8);
          operator_delete(local_20);
          operator_delete(local_38);
        }
        else {
          SetRect((LPRECT)&this->bounds_rect,local_1c,local_18,local_14,local_10);
          iVar2 = rect_height((iptr)&local_64);
          iVar3 = rect_width((iptr)&local_64);
          SetRect((LPRECT)this,0,0,iVar3,iVar2);
          if (param_2 == -2) {
            this->key_color = '\0';
          }
          else {
            this->key_color = local_40;
          }
          this->offset_x = 0;
          this->full_height = 0;
          local_4c = (i32 *)mem_handle_lock(local_30);
          for (local_44 = 0; local_44 < local_10 - local_18; local_44++) {
            *local_4c = *(i32 *)((int)local_20 + local_44 * 4);
            local_4c[1] = *(i32 *)((int)local_38 + local_44 * 4);
            local_4c += 2;
            mem_move_src_dst(*(iptr *)((int)local_8 + local_44 * 4),(iptr)local_4c,
                         *(i32 *)((int)local_38 + local_44 * 4));
            local_4c = (i32 *)((int)local_4c + *(int *)((int)local_38 + local_44 * 4));
          }
          *local_4c = 0;
          local_4c = (i32 *)mem_handle_unlock(local_30);
          if (local_34 == 0) {
            surface_unlock((DibSurface *)param_1);
          }
          operator_delete(local_8);
          operator_delete(local_20);
          operator_delete(local_38);
        }
      }
    }
    else {
      SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
      iVar2 = rect_height((iptr)&local_64);
      iVar3 = rect_width((iptr)&local_64);
      SetRect((LPRECT)this,0,0,iVar3,iVar2);
      if (param_2 == -2) {
        this->key_color = '\0';
      }
      else {
        this->key_color = local_40;
      }
      this->offset_x = 0;
      this->full_height = 0;
      if (local_34 == 0) {
        surface_unlock((DibSurface *)param_1);
      }
      this->data_ptr = 0;
      local_30 = 0;
    }
  }
  return local_30;
}
#undef local_64
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
#undef local_8

/* 005d056c auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define local_30 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_1c (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
int * __thiscall
sprite_blit_to_surface
          (Sprite *this,int *param_1,DibSurface *param_2,int param_3,int param_4,
          int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  int iVar6;
  BOOL BVar7;
  i32 uVar8;
  iptr iVar9;
  int iVar10;
  int iVar11;
  i32 uVar12;
  iptr iVar13;
  i32 uVar14;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_3 == -1) {
    (*(i8 *)((char *)&param_3 + 0)) = this->key_color;
  }
  else {
  }
  local_24 = CONCAT31((*(i32 *)((char *)&local_24 + 1)),(u8)param_3);
  local_8 = this->bounds_rect - this->frame_rect;
  iVar1 = this->bounds_top - this->frame_top;
  iVar2 = sprite_width(this);
  if (((iVar2 * gfx_scale_num) / gfx_scale_den < 0x401) &&
     (iVar2 = sprite_height(this), (iVar2 * gfx_scale_num) / gfx_scale_den < 0x401)) {
    iVar3 = gfx_scale_length(local_8,0,1);
    iVar4 = gfx_scale_length(iVar1,0,1);
    iVar2 = gfx_scale_length(this->offset_x,0,0);
    local_28 = iVar3 + iVar2 + param_4;
    iVar2 = gfx_scale_length(this->full_height,0,0);
    local_2c = iVar4 + iVar2 + param_5;
    uVar14 = 0;
    iVar2 = iVar4;
    uVar5 = sprite_get_height(this);
    iVar6 = gfx_scale_length(uVar5,iVar2,uVar14);
    uVar14 = 0;
    iVar2 = iVar3;
    uVar5 = sprite_get_width(this);
    iVar2 = gfx_scale_length(uVar5,iVar2,uVar14);
    SetRect(&local_1c,0,0,iVar2,iVar6);
    OffsetRect(&local_1c,local_28,local_2c);
    BVar7 = IntersectRect(&local_1c,&local_1c,(RECT *)&param_2->field_14);
    if (BVar7 != 0) {
      local_30 = 0;
      uVar5 = rect_width((iptr)&local_1c);
      if (local_28 < local_1c.left) {
        local_30 = local_1c.left - local_28;
        local_28 = local_1c.left;
      }
      local_c = 0;
      uVar14 = rect_height((iptr)&local_1c);
      if (local_2c < local_1c.top) {
        local_c = local_1c.top - local_2c;
        local_2c = local_1c.top;
      }
      iVar2 = local_c;
      iVar6 = local_8;
      uVar8 = surface_height(param_2);
      iVar9 = surface_get_dib(param_2);
      iVar10 = dib_is_top_down(iVar9);
      iVar11 = surface_get_pitch(param_2);
      iVar11 = ((-(uint)(iVar10 == 0) & 0xfffffffe) + 1) * iVar11;
      iVar13 = gfx_scale_table;
      uVar12 = surface_get_bits(param_2);
      sprite_blit_rows_keyed(this->data_ptr,uVar12,iVar13,local_24,local_28,local_2c,iVar11,uVar8,uVar5,uVar14
                   ,local_30,iVar2,iVar6,iVar1,iVar3,iVar4);
    }
    *param_1 = local_1c.left;
    param_1[1] = local_1c.top;
    param_1[2] = local_1c.right;
    param_1[3] = local_1c.bottom;
    return param_1;
  }
  dbg_log(ADDR(0x6381cc, ((u8 *)&g.d_006381cc)));
  SetRect(&local_1c,0,0,0,0);
  *param_1 = local_1c.left;
  param_1[1] = local_1c.top;
  param_1[2] = local_1c.right;
  param_1[3] = local_1c.bottom;
  return param_1;
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_1c
#undef local_c
#undef local_8

/* 005d10cd auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define local_30 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_1c (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
int * __thiscall
sprite_blit_silhouette_to_surface
          (Sprite *this,int *param_1,DibSurface *param_2,int param_3,int param_4,
          int param_5,i32 param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  int iVar6;
  BOOL BVar7;
  i32 uVar8;
  iptr iVar9;
  int iVar10;
  int iVar11;
  i32 uVar12;
  iptr iVar13;
  i32 uVar14;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_3 == -1) {
    (*(i8 *)((char *)&param_3 + 0)) = this->key_color;
  }
  else {
  }
  local_24 = CONCAT31((*(i32 *)((char *)&local_24 + 1)),(u8)param_3);
  local_8 = this->bounds_rect - this->frame_rect;
  iVar1 = this->bounds_top - this->frame_top;
  iVar2 = sprite_width(this);
  if (((iVar2 * gfx_scale_num) / gfx_scale_den < 0x401) &&
     (iVar2 = sprite_height(this), (iVar2 * gfx_scale_num) / gfx_scale_den < 0x401)) {
    iVar3 = gfx_scale_length(local_8,0,1);
    iVar4 = gfx_scale_length(iVar1,0,1);
    iVar2 = gfx_scale_length(this->offset_x,0,0);
    local_28 = param_4 + iVar2 + iVar3;
    iVar2 = gfx_scale_length(this->full_height,0,0);
    local_2c = param_5 + iVar2 + iVar4;
    uVar14 = 0;
    iVar2 = iVar4;
    uVar5 = sprite_get_height(this);
    iVar6 = gfx_scale_length(uVar5,iVar2,uVar14);
    uVar14 = 0;
    iVar2 = iVar3;
    uVar5 = sprite_get_width(this);
    iVar2 = gfx_scale_length(uVar5,iVar2,uVar14);
    SetRect(&local_1c,0,0,iVar2,iVar6);
    OffsetRect(&local_1c,local_28,local_2c);
    BVar7 = IntersectRect(&local_1c,&local_1c,(RECT *)&param_2->field_14);
    if (BVar7 != 0) {
      local_30 = 0;
      uVar5 = rect_width((iptr)&local_1c);
      if (local_28 < local_1c.left) {
        local_30 = local_1c.left - local_28;
        local_28 = local_1c.left;
      }
      local_c = 0;
      uVar14 = rect_height((iptr)&local_1c);
      if (local_2c < local_1c.top) {
        local_c = local_1c.top - local_2c;
        local_2c = local_1c.top;
      }
      iVar2 = local_c;
      iVar6 = local_8;
      uVar8 = surface_height(param_2);
      iVar9 = surface_get_dib(param_2);
      iVar10 = dib_is_top_down(iVar9);
      iVar11 = surface_get_pitch(param_2);
      iVar11 = ((-(uint)(iVar10 == 0) & 0xfffffffe) + 1) * iVar11;
      iVar13 = gfx_scale_table;
      uVar12 = surface_get_bits(param_2);
      sprite_blit_rows_solid(this->data_ptr,uVar12,iVar13,local_24,local_28,local_2c,iVar11,uVar8,uVar5,uVar14
                   ,local_30,iVar2,iVar6,iVar1,iVar3,iVar4,param_6);
    }
    *param_1 = local_1c.left;
    param_1[1] = local_1c.top;
    param_1[2] = local_1c.right;
    param_1[3] = local_1c.bottom;
    return param_1;
  }
  dbg_log(ADDR(0x63827c, ((u8 *)&g.d_0063827c)));
  SetRect(&local_1c,0,0,0,0);
  *param_1 = local_1c.left;
  param_1[1] = local_1c.top;
  param_1[2] = local_1c.right;
  param_1[3] = local_1c.bottom;
  return param_1;
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_1c
#undef local_c
#undef local_8

/* 005d1612 auto */
#define local_60 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_5c (*(int * *)(frame_ + FRAME_OFF(4)))
#define local_54 (*(int * *)(frame_ + FRAME_OFF(12)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_20 (*(int * *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(76)))
void __thiscall
sprite_merge_at
          (Sprite *this,iptr param_1,Sprite *param_2,i32 param_3,int param_4,
          int param_5)

{
  byte bVar1;
  LONG LVar2;
  LONG LVar3;
  int iVar4;
  iptr iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  iptr iVar9;
  int iVar10;
  u32 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  u32 uVar15;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0x34) != 0) {
    if (param_2->field_34 == 0) {
      SetRect((LPRECT)param_2,*(int *)param_1,*(int *)(param_1 + 4),*(int *)(param_1 + 8) + param_4,
              *(int *)(param_1 + 0xc) + param_5);
      param_2->field_10 = *(u32 *)(param_1 + 0x10);
      param_2->field_14 = *(u32 *)(param_1 + 0x14);
      *(i32 *)param_2->pad_18 = *(i32 *)(param_1 + 0x18);
      *(i32 *)(param_2->pad_18 + 4) = *(i32 *)(param_1 + 0x1c);
      OffsetRect((LPRECT)&param_2->field_10,param_4,param_5);
      param_2->field_20 = *(int *)(param_1 + 0x20) + param_4;
      param_2->field_24 = *(int *)(param_1 + 0x24) + param_5;
      param_2->field_28 = *(u32 *)(param_1 + 0x28);
      param_2->field_2c = *(u32 *)(param_1 + 0x2c);
      param_2->field_30 = *(u8 *)(param_1 + 0x30);
      param_2->field_34 = *(u32 *)(param_1 + 0x34);
      mem_handle_clone((iptr)&param_2->field_34);
      sprite_lock(param_2);
    }
    else {
      iVar4 = (*(int *)(param_1 + 0x14) + param_5) - param_2->field_14;
      iVar5 = rect_width(param_1 + 0x10);
      iVar10 = *(int *)(param_1 + 0x10);
      iVar6 = rect_height(param_1 + 0x10);
      iVar7 = rect_width((iptr)&param_2->field_10);
      iVar7 = param_2->field_10 + iVar7;
      iVar8 = rect_height((iptr)&param_2->field_10);
      iVar9 = iVar6 + iVar4;
      if (iVar6 + iVar4 <= iVar8) {
        iVar9 = iVar8;
      }
      iVar10 = iVar10 + iVar5 + param_4;
      if (iVar10 <= iVar7) {
        iVar10 = iVar7;
      }
      SetRect(&local_14,0,0,iVar10,iVar9);
      LVar3 = local_14.bottom;
      LVar2 = local_14.right;
      sprite_lock((Sprite *)param_1);
      sprite_lock(param_2);
      local_54 = *(int **)(param_1 + 0x38);
      local_5c = (int *)param_2->field_38;
      uVar11 = mem_handle_alloc(LVar2 * LVar3 + LVar3 * 8);
      local_20 = (int *)mem_handle_lock(uVar11);
      for (local_40 = 0; local_40 < LVar3; local_40++) {
        bVar1 = local_40 < iVar8;
        if ((iVar4 <= local_40) && (local_40 < iVar6 + iVar4)) {
          bVar1 = bVar1 | 2;
        }
        switch(bVar1) {
        case 0:
          *local_20 = 0;
          local_20[1] = 0;
          local_20 += 2;
          break;
        case 1:
          *local_20 = *local_5c;
          local_20[1] = local_5c[1];
          iVar10 = local_20[1];
          mem_move_src_dst((iptr)(local_5c + 2),(iptr)(local_20 + 2),iVar10);
          local_5c = (int *)((int)(local_5c + 2) + iVar10);
          local_20 = (int *)((int)(local_20 + 2) + iVar10);
          break;
        case 2:
          *local_20 = *local_54 + param_4;
          local_20[1] = local_54[1];
          iVar10 = local_20[1];
          mem_move_src_dst((iptr)(local_54 + 2),(iptr)(local_20 + 2),iVar10);
          local_54 = (int *)((int)(local_54 + 2) + iVar10);
          local_20 = (int *)((int)(local_20 + 2) + iVar10);
          break;
        case 3:
          iVar10 = *local_5c;
          iVar12 = local_5c[1] + iVar10;
          local_5c += 2;
          iVar13 = *local_54 + param_4;
          iVar14 = local_54[1] + iVar13;
          local_54 += 2;
          iVar7 = iVar10;
          if (iVar13 <= iVar10) {
            iVar7 = iVar13;
          }
          *local_20 = iVar7;
          iVar7 = iVar12;
          if (iVar12 <= iVar14) {
            iVar7 = iVar14;
          }
          local_20[1] = iVar7 - *local_20;
          local_20 += 2;
          local_24 = LVar2;
          local_34 = 0;
          while (local_24 != 0) {
            local_60 = 0;
            if ((iVar10 <= local_34) && (local_34 < iVar12)) {
              *(char *)local_20 = (char)*local_5c;
              local_5c = (int *)((int)local_5c + 1);
              local_60 = 1;
            }
            if ((iVar13 <= local_34) && (local_34 < iVar14)) {
              if ((uint)*(byte *)(param_1 + 0x30) == (int)(char)*local_54) {
                if (local_60 == 0) {
                  *(u8 *)local_20 = param_2->field_30;
                }
              }
              else {
                *(char *)local_20 = (char)*local_54;
              }
              local_54 = (int *)((int)local_54 + 1);
              local_60++;
            }
            if (local_60 != 0) {
              local_20 = (int *)((int)local_20 + 1);
            }
            local_34++;
            local_24--;
          }
        }
      }
      OffsetRect(&local_14,param_2->field_10,param_2->field_14);
      param_2->field_10 = local_14.left;
      param_2->field_14 = local_14.top;
      *(LONG *)param_2->pad_18 = local_14.right;
      *(LONG *)(param_2->pad_18 + 4) = local_14.bottom;
      param_2->field_0 = local_14.left;
      param_2->field_4 = local_14.top;
      *(LONG *)param_2->pad_8 = local_14.right;
      *(LONG *)(param_2->pad_8 + 4) = local_14.bottom;
      if (param_2->field_38 != 0) {
        sprite_unlock(param_2);
      }
      if (param_2->field_34 != 0) {
        uVar15 = mem_handle_free(param_2->field_34);
        param_2->field_34 = uVar15;
      }
      mem_handle_unlock(uVar11);
      param_2->field_34 = uVar11;
      sprite_lock(param_2);
    }
  }
  return;
}
#undef local_60
#undef local_5c
#undef local_54
#undef local_40
#undef local_34
#undef local_24
#undef local_20
#undef local_14

/* 005d1b38 auto */
void __thiscall sprite_clear_fields(Sprite *this)

{
  SetRect((LPRECT)this,0,0,0,0);
  SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
  this->offset_x = 0;
  this->full_height = 0;
  this->field_28 = 1;
  this->field_2c = 1;
  this->key_color = '\0';
  this->data_handle = 0;
  this->data_ptr = 0;
  return;
}

/* 005d1d00 auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl gfx_scale_length(int param_1,int param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    bVar2 = -1 < param_1;
    if (!bVar2) {
      param_1 = -param_1;
    }
    if (gfx_scale_num < gfx_scale_den) {
      local_10 = param_2;
      iVar1 = *(int *)(gfx_scale_table + param_2 * 4) + param_1;
      for (; *(int *)(gfx_scale_table + local_10 * 4) < iVar1; local_10++) {
      }
      if ((param_3 == 0) && (*(int *)(gfx_scale_table + local_10 * 4) != iVar1)) {
        local_10--;
      }
    }
    else {
      local_10 = param_2;
      for (; *(int *)(gfx_scale_table + local_10 * 4) <
             *(int *)(gfx_scale_table + param_2 * 4) + param_1; local_10++) {
      }
    }
    iVar1 = ((-(uint)bVar2 & 2) - 1) * (local_10 - param_2);
  }
  return iVar1;
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef local_10

/* 005de780 auto */
#define local_10 (*(i8 * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl logpal_init_from_system(iptr param_1)

{
  HDC hdc;
  uint uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i16 *)param_1 = 0x300;
  *(i16 *)(param_1 + 2) = 0x100;
  hdc = GetDC((HWND)0x0);
  uVar1 = GetDeviceCaps(hdc,0x26);
  if ((uVar1 & 0x100) == 0) {
    palette_static_half_count = 0;
    gfx_palettized_display = 0;
  }
  else {
    iVar2 = GetDeviceCaps(hdc,0x18);
    palette_static_half_count = iVar2 / 2;
    GetSystemPaletteEntries(hdc,0,0x100,(LPPALETTEENTRY)(param_1 + 4));
  }
  for (local_c = 0; local_c < palette_static_half_count; local_c++) {
    *(i8 *)(param_1 + 7 + local_c * 4) = 0;
  }
  for (; local_c < 0x100 - palette_static_half_count; local_c++) {
    *(i8 *)(param_1 + 4 + local_c * 4) = 0;
    *(i8 *)(param_1 + 5 + local_c * 4) = 0;
    *(i8 *)(param_1 + 6 + local_c * 4) = 0;
    *(i8 *)(param_1 + 7 + local_c * 4) = 4;
  }
  for (; local_c < 0x100; local_c++) {
    *(i8 *)(param_1 + 7 + local_c * 4) = 0;
  }
  if (gfx_palettized_display == 0) {
    local_10 = &logpal_static_system_colors;
    for (local_c = 0; local_c < 10; local_c++) {
      *(i8 *)(param_1 + 4 + local_c * 4) = *local_10;
      *(i8 *)(param_1 + 5 + local_c * 4) = local_10[1];
      *(i8 *)(param_1 + 6 + local_c * 4) = local_10[2];
      local_10 += 3;
    }
    for (local_c = 0xf6; local_c < 0x100; local_c++) {
      *(i8 *)(param_1 + 4 + local_c * 4) = *local_10;
      *(i8 *)(param_1 + 5 + local_c * 4) = local_10[1];
      *(i8 *)(param_1 + 6 + local_c * 4) = local_10[2];
      local_10 += 3;
    }
  }
  ReleaseDC((HWND)0x0,hdc);
  return;
}
#undef local_10
#undef local_c

/* 005de984 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl logpal_reserve_range(iptr param_1,int param_2,int param_3)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (0x100 < param_3 + param_2) {
    param_3 = 0x100 - param_2;
  }
  for (local_8 = param_2; local_8 < param_3 + param_2; local_8++) {
    *(i8 *)(param_1 + 7 + local_8 * 4) = 1;
  }
  return;
}
#undef local_8

/* 005dea62 auto */
void __cdecl palette_animate(iptr param_1,HPALETTE param_2,UINT param_3,UINT param_4)

{
  if (gfx_palettized_display == 1) {
    AnimatePalette(param_2,param_3,param_4,(PALETTEENTRY *)(param_3 * 4 + param_1 + 4));
  }
  return;
}

/* 005dea9e auto */
void __cdecl palette_get_entry_rgb(iptr param_1,int param_2,iptr param_3,iptr param_4,iptr param_5)

{
  *(i8 *)param_3 = *(i8 *)(param_1 + 4 + param_2 * 4);
  *(i8 *)param_4 = *(i8 *)(param_1 + 5 + param_2 * 4);
  *(i8 *)param_5 = *(i8 *)(param_1 + 6 + param_2 * 4);
  return;
}

/* 005deadb auto */
void __cdecl
logpal_set_entry(iptr param_1,int param_2,i32 param_3,i32 param_4,i32 param_5)

{
  *(i8 *)(param_1 + 4 + param_2 * 4) = (i8)param_3;
  *(i8 *)(param_1 + 5 + param_2 * 4) = (i8)param_4;
  *(i8 *)(param_1 + 6 + param_2 * 4) = (i8)param_5;
  return;
}

/* 005deb12 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl
palette_set_entry_rgb(iptr param_1,int param_2,i32 param_3,i32 param_4,i32 param_5)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(char *)(param_1 + 4 + param_2 * 4) = (char)param_3;
  *(char *)(param_1 + 5 + param_2 * 4) = (char)param_4;
  *(char *)(param_1 + 6 + param_2 * 4) = (char)param_5;
  *(i8 *)(param_1 + 7 + param_2 * 4) = 4;
  for (local_8 = 0; local_8 < palette_static_half_count; local_8++) {
    if (((*(char *)(param_1 + 4 + local_8 * 4) == (char)param_3) &&
        (*(char *)(param_1 + 5 + local_8 * 4) == (char)param_4)) &&
       (*(char *)(param_1 + 6 + local_8 * 4) == (char)param_5)) {
      *(i8 *)(param_1 + 7 + param_2 * 4) = 1;
    }
  }
  for (local_8 = 0x100 - palette_static_half_count; local_8 < 0x100; local_8++) {
    if (((*(char *)(param_1 + 4 + local_8 * 4) == (char)param_3) &&
        (*(char *)(param_1 + 5 + local_8 * 4) == (char)param_4)) &&
       (*(char *)(param_1 + 6 + local_8 * 4) == (char)param_5)) {
      *(i8 *)(param_1 + 7 + param_2 * 4) = 1;
    }
  }
  return;
}
#undef local_8

/* 005dec4e auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
HPALETTE __cdecl logpal_create_hpalette(iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (gfx_palettized_display == 1) {
    local_8 = CreatePalette((LOGPALETTE *)param_1);
  }
  else {
    local_8 = (HPALETTE)0x0;
  }
  return local_8;
}
#undef local_8

/* 005dec8a auto */
void __cdecl logpal_delete_hpalette(HGDIOBJ param_1)

{
  if (gfx_palettized_display == 1) {
    DeleteObject(param_1);
  }
  return;
}

/* 005decb1 auto */
void __cdecl logpal_apply_range(iptr param_1,HPALETTE param_2,UINT param_3,UINT param_4)

{
  if (gfx_palettized_display == 1) {
    SetPaletteEntries(param_2,param_3,param_4,(PALETTEENTRY *)(param_3 * 4 + param_1 + 4));
  }
  return;
}

/* 005ded12 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl palette_copy_rgb_range(iptr param_1,iptr param_2,int param_3,int param_4)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = param_3; local_c < param_4 + param_3; local_c++) {
    *(i8 *)(local_8 + param_2) = *(i8 *)(param_1 + 4 + local_c * 4);
    *(i8 *)(local_8 + 1 + param_2) = *(i8 *)(param_1 + 5 + local_c * 4);
    *(i8 *)(local_8 + 2 + param_2) = *(i8 *)(param_1 + 6 + local_c * 4);
    local_8 += 3;
  }
  return;
}
#undef local_c
#undef local_8

/* 005e35b0 auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define local_444 (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_434 (*(BITMAPINFO (*)[24])(frame_ + FRAME_OFF(20)))
#define local_c (*(int *)(frame_ + FRAME_OFF(1084)))
#define local_8 (*(void * *)(frame_ + FRAME_OFF(1088)))
i32 * __cdecl dib_create(iptr param_1)

{
  int iVar1;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ pvVar2;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_444 = (i32 *)0x0;
  iVar1 = *(int *)(param_1 + 8) - *(int *)param_1;
  local_c = *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4);
  if ((iVar1 < 1) || (local_c < 1)) {
    local_444 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log(ADDR(0x638e74, ((u8 *)&g.d_00638e74)));
    }
    else {
      _memset(local_434,0,0x28);
      local_434[0].bmiHeader.biSize = 0x28;
      local_434[0].bmiHeader.biPlanes = 1;
      local_434[0].bmiHeader.biBitCount = 8;
      local_434[0].bmiHeader.biHeight = 1;
      local_434[0].bmiHeader.biWidth = dib_row_align4(iVar1);
      if (0 < local_434[0].bmiHeader.biHeight) {
        if (dib_bottom_up_logged == 0) {
          dbg_log(ADDR(0x638e20, ((u8 *)&g.d_00638e20)));
        }
        dib_bottom_up_logged = 1;
      }
      if (dib_row_order == -1) {
        local_434[0].bmiHeader.biHeight = local_c;
      }
      else if (dib_row_order == 1) {
        local_434[0].bmiHeader.biHeight = -local_c;
      }
      else {
        local_434[0].bmiHeader.biHeight = local_434[0].bmiHeader.biHeight * local_c;
      }
      _memset(local_434[0].bmiColors,0,0x400);
      h = CreateDIBSection(hdc,local_434,0,&local_8,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log(ADDR(0x638e44, ((u8 *)&g.d_00638e44)));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        local_444 = GlobalLock(hMem);
        *local_444 = hMem;
        local_444[1] = hdc;
        local_444[2] = 0;
        local_444[3] = h;
        local_444[8] = local_434[0].bmiHeader.biWidth;
        local_444[6] = iVar1;
        local_444[7] = local_c;
        pvVar2 = SelectObject(hdc,h);
        local_444[4] = pvVar2;
        local_444[9] = local_8;
        if (local_434[0].bmiHeader.biHeight < 0) {
          local_444[5] = 1;
        }
        else {
          local_444[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return local_444;
}
#undef dib_row_order
#undef local_444
#undef local_434
#undef local_c
#undef local_8

/* 005e388f auto */
i32 __cdecl dib_destroy(iptr param_1)

{
  i32 uVar1;
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 4) != 0) {
      SelectObject(*(HDC *)(param_1 + 4),*(HGDIOBJ *)(param_1 + 0x10));
      DeleteObject(*(HGDIOBJ *)(param_1 + 0xc));
      DeleteDC(*(HDC *)(param_1 + 4));
    }
    if (*(int *)(param_1 + 8) != 0) {
      DeleteObject(*(HGDIOBJ *)(param_1 + 8));
    }
    uVar1 = *(i32 *)param_1;
    mem_handle_unlock(uVar1);
    mem_handle_free(uVar1);
  }
  return 0;
}

/* 005e392a auto */
i32 __cdecl dib_get_stride(iptr param_1)

{
  i32 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(i32 *)(param_1 + 0x20);
  }
  return uVar1;
}

/* 005e395a auto */
uint __cdecl dib_is_top_down(iptr param_1)

{
  return (uint)(*(int *)(param_1 + 0x14) == 1);
}

/* 005e3988 auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
void __cdecl dib_flip_vertical(iptr param_1)

{
  i32 uVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = dib_get_bits(param_1);
  uVar1 = mem_handle_alloc(*(i32 *)(param_1 + 0x20));
  uVar2 = mem_handle_lock(uVar1);
  local_14 = (*(int *)(param_1 + 0x1c) - 1) * *(int *)(param_1 + 0x20) + local_c;
  for (local_18 = 0; local_18 < *(int *)(param_1 + 0x1c) / 2; local_18++) {
    crt_memmove(uVar2,local_14,*(i32 *)(param_1 + 0x20));
    crt_memmove(local_14,local_c,*(i32 *)(param_1 + 0x20));
    crt_memmove(local_c,uVar2,*(i32 *)(param_1 + 0x20));
    local_c += *(int *)(param_1 + 0x20);
    local_14 -= *(int *)(param_1 + 0x20);
  }
  mem_handle_unlock(uVar1);
  mem_handle_free(uVar1);
  return;
}
#undef local_18
#undef local_14
#undef local_c

/* 005e3a81 auto */
i32 __cdecl dib_get_bits(iptr param_1)

{
  i32 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(i32 *)(param_1 + 0x24);
  }
  return uVar1;
}

/* 005e3aa8 auto */
i32 __cdecl dib_unlock_bits(int param_1)

{
  return 0;
}

/* 005e3b4c auto */
#define local_408 (*(RGBQUAD (*)[256])(frame_ + FRAME_OFF(0)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(1024)))
void __cdecl dib_set_color_table_range(iptr param_1,GamePalette *param_2,UINT param_3,UINT param_4)

{
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = param_3; (int)local_8 < (int)(param_4 + param_3); local_8++) {
    palette_get_entry
              (param_2,local_8,(iptr)&local_408[local_8].rgbRed,(iptr)&local_408[local_8].rgbGreen,
               (iptr)(local_408 + local_8));
    local_408[local_8].rgbReserved = '\0';
  }
  SetDIBColorTable(*(HDC *)(param_1 + 4),param_3,param_4,local_408);
  return;
}
#undef local_408
#undef local_8

/* 005e3bdc auto */
void __cdecl dib_set_palette(iptr param_1,iptr param_2)

{
  dib_set_color_table_range(param_1,param_2,0,0x100);
  return;
}

/* 005e3cb4 auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define local_24 (*(RGBQUAD *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(HGDIOBJ *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(UINT *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(32)))
void __cdecl
dib_draw_text_at(iptr param_1,int param_2,char *param_3,int param_4,int param_5,iptr param_6,
            uint param_7)

{
  int iVar1;
  int iVar2;
  size_t cchText;
  tagRECT *lprc;
  UINT format;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    dbg_log(ADDR(0x638ea0, ((u8 *)&g.d_00638ea0)));
  }
  else {
    local_8 = (i32 *)mem_handle_lock(param_2);
    iVar1 = font_measure_height(param_2);
    iVar1 = param_5 + iVar1;
    iVar2 = font_measure_width(param_2,(iptr)param_3);
    SetRect(&local_18,param_4,param_5,param_4 + iVar2,iVar1);
    local_20 = SelectObject(*(HDC *)(param_1 + 4),(HGDIOBJ)*local_8);
    GetDIBColorTable(*(HDC *)(param_1 + 4),(uint)gfx_text_color_index,1,&local_24);
    SetTextColor(*(HDC *)(param_1 + 4),
                 (uint)CONCAT12(local_24.rgbBlue,CONCAT11(local_24.rgbGreen,local_24.rgbRed)));
    iVar1 = rect_height((iptr)&local_18);
    iVar1 = iVar1 / 2;
    iVar2 = rect_width((iptr)&local_18);
    iVar2 = iVar2 / 2;
    OffsetRect(&local_18,-iVar2,-iVar1);
    if ((param_7 & 1) != 0) {
      OffsetRect(&local_18,iVar2,0);
    }
    if ((param_7 & 4) != 0) {
      OffsetRect(&local_18,0,iVar1);
    }
    if ((param_7 & 8) != 0) {
      OffsetRect(&local_18,0,-iVar1);
    }
    if ((param_7 & 2) != 0) {
      OffsetRect(&local_18,-iVar2,0);
    }
    local_1c = GetTextAlign(*(HDC *)(param_1 + 4));
    SetTextAlign(*(HDC *)(param_1 + 4),1);
    MoveToEx(*(HDC *)(param_1 + 4),local_18.left,local_18.top,(LPPOINT)0x0);
    IntersectRect(&local_18,&local_18,(RECT *)param_6);
    format = 0;
    lprc = &local_18;
    cchText = _strlen(param_3);
    DrawTextA(*(HDC *)(param_1 + 4),param_3,cchText,lprc,format);
    SetTextAlign(*(HDC *)(param_1 + 4),local_1c);
    SelectObject(*(HDC *)(param_1 + 4),local_20);
    mem_handle_unlock(param_2);
  }
  return;
}
#undef gfx_text_color_index
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 005e3eca auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(RGBQUAD *)(frame_ + FRAME_OFF(8)))
#define local_c (*(HGDIOBJ *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(16)))
void __cdecl dib_draw_text_rect(iptr param_1,int param_2,char *param_3,iptr param_4,uint param_5)

{
  size_t cchText;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    dbg_log(ADDR(0x638ec4, ((u8 *)&g.d_00638ec4)));
  }
  else if (param_1 != 0) {
    local_8 = (i32 *)mem_handle_lock(param_2);
    local_c = SelectObject(*(HDC *)(param_1 + 4),(HGDIOBJ)*local_8);
    GetDIBColorTable(*(HDC *)(param_1 + 4),(uint)gfx_text_color_index,1,&local_10);
    SetTextColor(*(HDC *)(param_1 + 4),
                 (uint)CONCAT12(local_10.rgbBlue,CONCAT11(local_10.rgbGreen,local_10.rgbRed)));
    local_14 = 0;
    if (param_5 == 0) {
      local_14 = 0x25;
    }
    else {
      if ((param_5 & 8) != 0) {
        local_14 = 8;
      }
      if ((param_5 & 2) != 0) {
        local_14 = local_14 | 2;
      }
    }
    cchText = _strlen(param_3);
    DrawTextA(*(HDC *)(param_1 + 4),param_3,cchText,(LPRECT)param_4,local_14);
    SelectObject(*(HDC *)(param_1 + 4),local_c);
    mem_handle_unlock(param_2);
  }
  return;
}
#undef gfx_text_color_index
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005e3feb auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define local_14 (*(UINT *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(RGBQUAD *)(frame_ + FRAME_OFF(8)))
#define local_c (*(HGDIOBJ *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(16)))
void __cdecl dib_draw_text_wrap(iptr param_1,int param_2,char *param_3,LPRECT param_4,uint param_5)

{
  size_t cchText;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    dbg_log(ADDR(0x638ee8, ((u8 *)&g.d_00638ee8)));
  }
  else if (param_1 != 0) {
    local_8 = (i32 *)mem_handle_lock(param_2);
    local_c = SelectObject(*(HDC *)(param_1 + 4),(HGDIOBJ)*local_8);
    GetDIBColorTable(*(HDC *)(param_1 + 4),(uint)gfx_text_color_index,1,&local_10);
    SetTextColor(*(HDC *)(param_1 + 4),
                 (uint)CONCAT12(local_10.rgbBlue,CONCAT11(local_10.rgbGreen,local_10.rgbRed)));
    local_14 = 0x10;
    if (param_5 == 0) {
      local_14 = 0x11;
    }
    else if ((param_5 & 2) != 0) {
      local_14 = 0x12;
    }
    cchText = _strlen(param_3);
    DrawTextA(*(HDC *)(param_1 + 4),param_3,cchText,param_4,local_14);
    SelectObject(*(HDC *)(param_1 + 4),local_c);
    mem_handle_unlock(param_2);
  }
  return;
}
#undef gfx_text_color_index
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005e40fb auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define local_10 (*(RGBQUAD *)(frame_ + FRAME_OFF(0)))
#define local_c (*(HPEN *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(HGDIOBJ *)(frame_ + FRAME_OFF(8)))
void __cdecl dib_draw_line(iptr param_1,int param_2,int param_3,int param_4,int param_5)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    GetDIBColorTable(*(HDC *)(param_1 + 4),(uint)gfx_text_color_index,1,&local_10);
    local_c = CreatePen(0,1,(uint)CONCAT12(local_10.rgbBlue,
                                           CONCAT11(local_10.rgbGreen,local_10.rgbRed)));
    local_8 = SelectObject(*(HDC *)(param_1 + 4),local_c);
    MoveToEx(*(HDC *)(param_1 + 4),param_2,param_3,(LPPOINT)0x0);
    LineTo(*(HDC *)(param_1 + 4),param_4,param_5);
    SelectObject(*(HDC *)(param_1 + 4),local_8);
    DeleteObject(local_c);
  }
  return;
}
#undef gfx_text_color_index
#undef local_10
#undef local_c
#undef local_8

/* 005e41ba auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define local_50 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define local_3c (*(BITMAPINFO *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(64)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(void * *)(frame_ + FRAME_OFF(72)))
i32 * __cdecl dib_create16(iptr param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ pvVar4;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_50 = (i32 *)0x0;
  iVar2 = *(int *)(param_1 + 8) - *(int *)param_1;
  iVar3 = *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4);
  if ((iVar2 < 1) || (iVar3 < 1)) {
    local_50 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log(ADDR(0x638f38, ((u8 *)&g.d_00638f38)));
    }
    else {
      _memset(&local_3c,0,0x34);
      local_3c.bmiHeader.biSize = 0x28;
      local_3c.bmiHeader.biPlanes = 1;
      local_3c.bmiHeader.biBitCount = 0x10;
      local_3c.bmiHeader.biHeight = 1;
      local_3c.bmiHeader.biCompression = 3;
      local_3c.bmiColors[0].rgbBlue = '\0';
      local_3c.bmiColors[0].rgbGreen = '|';
      local_3c.bmiColors[0].rgbRed = '\0';
      local_3c.bmiColors[0].rgbReserved = '\0';
      local_10 = 0x3e0;
      local_c = 0x1f;
      local_3c.bmiHeader.biWidth = dib_row_align4(iVar2);
      iVar1 = iVar3;
      if (dib_row_order != -1) {
        if (dib_row_order == 1) {
          iVar1 = -iVar3;
        }
        else {
          iVar1 = local_3c.bmiHeader.biHeight * iVar3;
        }
      }
      local_3c.bmiHeader.biHeight = iVar1;
      h = CreateDIBSection(hdc,&local_3c,0,&local_8,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log(ADDR(0x638f08, ((u8 *)&g.d_00638f08)));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        local_50 = GlobalLock(hMem);
        *local_50 = hMem;
        local_50[1] = hdc;
        local_50[2] = 0;
        local_50[3] = h;
        local_50[8] = local_3c.bmiHeader.biWidth * 2;
        local_50[6] = iVar2;
        local_50[7] = iVar3;
        pvVar4 = SelectObject(hdc,h);
        local_50[4] = pvVar4;
        local_50[9] = local_8;
        if (local_3c.bmiHeader.biHeight < 0) {
          local_50[5] = 1;
        }
        else {
          local_50[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return local_50;
}
#undef dib_row_order
#undef local_50
#undef local_3c
#undef local_10
#undef local_c
#undef local_8

/* 005e43c5 auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define local_48 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(BITMAPINFO *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(void * *)(frame_ + FRAME_OFF(64)))
i32 * __cdecl dib_create24(iptr param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ pvVar4;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_48 = (i32 *)0x0;
  iVar2 = *(int *)(param_1 + 8) - *(int *)param_1;
  iVar3 = *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4);
  if ((iVar2 < 1) || (iVar3 < 1)) {
    local_48 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log(ADDR(0x638f94, ((u8 *)&g.d_00638f94)));
    }
    else {
      _memset(&local_34,0,0x2c);
      local_34.bmiHeader.biSize = 0x28;
      local_34.bmiHeader.biPlanes = 1;
      local_34.bmiHeader.biBitCount = 0x18;
      local_34.bmiHeader.biHeight = 1;
      local_34.bmiHeader.biWidth = dib_row_align4(iVar2);
      iVar1 = iVar3;
      if (dib_row_order != -1) {
        if (dib_row_order == 1) {
          iVar1 = -iVar3;
        }
        else {
          iVar1 = local_34.bmiHeader.biHeight * iVar3;
        }
      }
      local_34.bmiHeader.biHeight = iVar1;
      h = CreateDIBSection(hdc,&local_34,0,&local_8,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log(ADDR(0x638f64, ((u8 *)&g.d_00638f64)));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        local_48 = GlobalLock(hMem);
        *local_48 = hMem;
        local_48[1] = hdc;
        local_48[2] = 0;
        local_48[3] = h;
        local_48[8] = local_34.bmiHeader.biWidth * 3;
        local_48[6] = iVar2;
        local_48[7] = iVar3;
        pvVar4 = SelectObject(hdc,h);
        local_48[4] = pvVar4;
        local_48[9] = local_8;
        if (local_34.bmiHeader.biHeight < 0) {
          local_48[5] = 1;
        }
        else {
          local_48[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return local_48;
}
#undef dib_row_order
#undef local_48
#undef local_34
#undef local_8

/* 005e45b5 auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define local_48 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(BITMAPINFO *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(void * *)(frame_ + FRAME_OFF(64)))
i32 * __cdecl dib_create32(iptr param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ pvVar4;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_48 = (i32 *)0x0;
  iVar2 = *(int *)(param_1 + 8) - *(int *)param_1;
  iVar3 = *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4);
  if ((iVar2 < 1) || (iVar3 < 1)) {
    local_48 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log(ADDR(0x638ff0, ((u8 *)&g.d_00638ff0)));
    }
    else {
      _memset(&local_34,0,0x2c);
      local_34.bmiHeader.biSize = 0x28;
      local_34.bmiHeader.biPlanes = 1;
      local_34.bmiHeader.biBitCount = 0x20;
      local_34.bmiHeader.biHeight = 1;
      local_34.bmiHeader.biWidth = dib_row_align4(iVar2);
      iVar1 = iVar3;
      if (dib_row_order != -1) {
        if (dib_row_order == 1) {
          iVar1 = -iVar3;
        }
        else {
          iVar1 = local_34.bmiHeader.biHeight * iVar3;
        }
      }
      local_34.bmiHeader.biHeight = iVar1;
      h = CreateDIBSection(hdc,&local_34,0,&local_8,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log(ADDR(0x638fc0, ((u8 *)&g.d_00638fc0)));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        local_48 = GlobalLock(hMem);
        *local_48 = hMem;
        local_48[1] = hdc;
        local_48[2] = 0;
        local_48[3] = h;
        local_48[8] = local_34.bmiHeader.biWidth << 2;
        local_48[6] = iVar2;
        local_48[7] = iVar3;
        pvVar4 = SelectObject(hdc,h);
        local_48[4] = pvVar4;
        local_48[9] = local_8;
        if (local_34.bmiHeader.biHeight < 0) {
          local_48[5] = 1;
        }
        else {
          local_48[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return local_48;
}
#undef dib_row_order
#undef local_48
#undef local_34
#undef local_8

/* 005e4d60 auto */
#define local_18 (*(i16 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl
gif_lzw_decode(iptr param_1,uint param_2,i32 param_3,uint param_4,int param_5,uint param_6,
            iptr param_7)

{
  int iVar1;
  i32 uVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = mem_handle_alloc(0x6000);
  if (iVar1 == 0) {
    dbg_log(ADDR(0x639084, ((u8 *)&g.d_00639084)));
    uVar2 = 0;
  }
  else {
    iVar3 = mem_handle_lock(iVar1);
    for (local_18 = 0; local_18 < 0x1000; local_18++) {
      *(i16 *)(iVar3 + local_18 * 2) = 0xffff;
      *(ushort *)(iVar3 + 0x2000 + local_18 * 2) = (ushort)(byte)param_2 + local_18;
      *(i16 *)(iVar3 + 0x4000 + local_18 * 2) = 1;
    }
    gif_lzw_decode_stream(param_1,param_7,iVar3,param_5,param_6,param_4,param_3);
    mem_handle_unlock(iVar1);
    mem_handle_free(iVar1);
    uVar2 = 1;
  }
  return uVar2;
}
#undef local_18

/* 005e4e60 auto */
void __cdecl
dib_fill_rect8(iptr param_1,uint param_2,int param_3,int param_4,uint param_5,int param_6,int param_7,
            int param_8)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  
  iVar3 = param_7;
  if (param_7 < 1) {
    param_4 = (param_8 - 1) - param_4;
    iVar3 = -param_7;
  }
  puVar4 = (uint *)(param_1 + param_4 * iVar3 + param_3);
  uVar1 = param_2 | param_2 << 8;
  do {
    uVar2 = param_5 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2--) {
        *puVar4 = uVar1 | param_2 << 0x10 | param_2 << 0x18;
        puVar4++;
      }
    }
    if ((param_5 & 2) != 0) {
      *(short *)puVar4 = (short)uVar1;
      puVar4 = (uint *)((int)puVar4 + 2);
    }
    if ((param_5 & 1) != 0) {
      *(char *)puVar4 = (char)param_2;
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    puVar4 = (uint *)((int)puVar4 + (param_7 - param_5));
    param_6--;
  } while (param_6 != 0);
  return;
}

/* 005e4f9b auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl
gfx_copy_pixels(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,uint param_7,
            int param_8,int param_9,int param_10,int param_11,int param_12)

{
  i8 uVar1;
  uint uVar2;
  int iVar3;
  i32 *puVar4;
  i32 *puVar5;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = param_11;
  if (param_11 < 1) {
    param_4 = (param_9 - 1) - param_4;
    iVar3 = -param_11;
  }
  puVar4 = (i32 *)(param_1 + param_4 * iVar3 + param_3);
  iVar3 = param_12;
  if (param_12 < 1) {
    param_6 = (param_10 - 1) - param_6;
    iVar3 = -param_12;
  }
  puVar5 = (i32 *)(param_2 + param_6 * iVar3 + param_5);
  local_8 = param_8;
  do {
    uVar2 = param_7 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2--) {
        *puVar5 = *puVar4;
        puVar4++;
        puVar5++;
      }
    }
    for (uVar2 = param_7 & 3; uVar2 != 0; uVar2--) {
      uVar1 = *(i8 *)puVar4;
      puVar4 = (i32 *)((int)puVar4 + 1);
      *(i8 *)puVar5 = uVar1;
      puVar5 = (i32 *)((int)puVar5 + 1);
    }
    puVar4 = (i32 *)((int)puVar4 + (param_11 - param_7));
    puVar5 = (i32 *)((int)puVar5 + (param_12 - param_7));
    local_8--;
  } while (local_8 != 0);
  return;
}
#undef local_8

/* 005e518e auto */
#define local_20 (*(int * *)(frame_ + FRAME_OFF(0)))
/* WARNING: Unable to use type for symbol iVar2 */

void __cdecl
sprite_blit_rows_keyed(iptr param_1,int param_2,iptr param_3,i32 param_4,int param_5,int param_6,
            int param_7,int param_8,int param_9,int param_10,int param_11,int param_12,
            i32 param_13,int param_14,int param_15,int param_16)

{
  int *piVar1;
  int iVar3;
  int iVar4;
  iptr iVar6;
  iptr iVar7;
  char *pcVar5;
  char *pcVar6;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar4 = param_7;
  if (param_7 < 1) {
    param_6 = (param_8 - 1) - param_6;
    iVar4 = -param_7;
  }
  pcVar5 = (char *)(param_2 + param_6 * iVar4 + param_5);
  local_20 = (int *)((param_12 + param_16) * 4 + param_3);
  iVar7 = param_1 + 8;
  do {
    for (; param_14 < *local_20; param_14++) {
      iVar7 = iVar7 + *(int *)(iVar7 - 4) + 8;
    }
    iVar2 = *(int *)(iVar7 - 8);
    iVar4 = *(int *)(iVar7 - 4);
    if (iVar4 != 0) {
      iVar3 = param_9;
      pcVar6 = pcVar5;
      for (piVar1 = (int *)((param_11 + param_15) * 4 + param_3); *piVar1 < iVar2;
          piVar1 = piVar1 + 1) {
        pcVar6++;
        iVar3--;
      }
      if (0 < iVar3) {
        do {
          iVar6 = *piVar1 - iVar2;
          if (iVar4 <= iVar6) break;
          if (*(char *)(iVar6 + iVar7) != (char)param_4) {
            *pcVar6 = *(char *)(iVar6 + iVar7);
          }
          piVar1++;
          pcVar6++;
          iVar3--;
        } while (iVar3 != 0);
      }
    }
    pcVar5 += param_7;
    local_20++;
    param_10--;
    if (param_10 < 1) {
      return;
    }
  } while( true );
}
#undef local_20

/* 005e52bf auto */
#define local_20 (*(int * *)(frame_ + FRAME_OFF(0)))
/* WARNING: Unable to use type for symbol iVar1 */

void __cdecl
sprite_blit_rows_solid(iptr param_1,int param_2,iptr param_3,i32 param_4,int param_5,int param_6,
            int param_7,int param_8,int param_9,int param_10,int param_11,int param_12,
            i32 param_13,int param_14,int param_15,int param_16,i32 param_17)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  iptr iVar5;
  iptr iVar6;
  i8 *puVar4;
  i8 *puVar5;
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = param_7;
  if (param_7 < 1) {
    param_6 = (param_8 - 1) - param_6;
    iVar3 = -param_7;
  }
  puVar4 = (i8 *)(param_2 + param_6 * iVar3 + param_5);
  local_20 = (int *)((param_12 + param_16) * 4 + param_3);
  iVar6 = param_1 + 8;
  do {
    for (; param_14 < *local_20; param_14++) {
      iVar6 = iVar6 + *(int *)(iVar6 - 4) + 8;
    }
    iVar1 = *(int *)(iVar6 - 8);
    iVar3 = *(int *)(iVar6 - 4);
    if (iVar3 != 0) {
      iVar2 = param_9;
      puVar5 = puVar4;
      for (piVar1 = (int *)((param_11 + param_15) * 4 + param_3); *piVar1 < iVar1;
          piVar1 = piVar1 + 1) {
        puVar5++;
        iVar2--;
      }
      if (0 < iVar2) {
        do {
          iVar5 = *piVar1 - iVar1;
          if (iVar3 <= iVar5) break;
          if (*(char *)(iVar5 + iVar6) != (char)param_4) {
            *puVar5 = (i8)param_17;
          }
          piVar1++;
          puVar5++;
          iVar2--;
        } while (iVar2 != 0);
      }
    }
    puVar4 += param_7;
    local_20++;
    param_10--;
    if (param_10 < 1) {
      return;
    }
  } while( true );
}
#undef local_20

/* 005e53f3 auto */
#define local_5c (*(byte * *)(frame_ + FRAME_OFF(4)))
#define local_58 (*(i8 * *)(frame_ + FRAME_OFF(8)))
#define local_54 (*(ushort *)(frame_ + FRAME_OFF(12)))
#define local_50 (*(ushort *)(frame_ + FRAME_OFF(16)))
#define local_4c (*(ushort *)(frame_ + FRAME_OFF(20)))
#define local_44 (*(uint *)(frame_ + FRAME_OFF(28)))
#define local_40 (*(ushort *)(frame_ + FRAME_OFF(32)))
#define local_24 (*(i8 * *)(frame_ + FRAME_OFF(60)))
#define local_20 (*(ushort *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(ushort *)(frame_ + FRAME_OFF(76)))
#define local_c (*(ushort *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(byte * *)(frame_ + FRAME_OFF(88)))
void __cdecl
gif_lzw_decode_stream(byte *param_1,i8 *param_2,iptr param_3,int param_4,uint param_5,uint param_6,
            i32 param_7)

{
  byte *pbVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  i8 *puVar7;
  uptr uVar8;
  iptr iVar9;
  uptr uVar9;
  iptr iVar10;
  iptr iVar11;
  i8 *puVar8;
  i8 *puVar9;
  i8 *puVar10;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar10 = param_3 + 0x2000;
  iVar11 = param_3 + 0x4000;
  local_40 = 0;
  local_5c = param_1;
  local_8 = param_1;
  local_24 = param_2;
  puVar7 = param_2 + (param_5 & 0xffff) * (param_6 & 0xffff) + 1;
  uVar3 = 2 << ((byte)param_7 & 0x1f);
  local_54 = uVar3 + 4;
  uVar4 = (short)param_7 + 1;
  uVar5 = (2 << ((byte)uVar4 & 0x1f)) - 2;
  local_44 = 0;
  local_14 = 0;
  local_50 = uVar4;
  local_20 = uVar5;
  local_c = uVar3;
LAB_005e549a:
  do {
    while( true ) {
      if (((short)param_4 <= (short)local_40) &&
         (local_40 = local_40 - (short)param_4, (ushort)((short)param_6 - (short)param_4) != 0)) {
        puVar9 = local_24 + (ushort)((short)param_6 - (short)param_4);
        puVar10 = puVar9;
        puVar8 = local_24;
        for (uVar8 = (uptr)local_40; local_24 = puVar9, uVar8 != 0; uVar8--) {
          puVar8--;
          puVar10--;
          *puVar10 = *puVar8;
        }
      }
      pbVar1 = local_5c;
      for (; local_5c = pbVar1, local_14 < local_50; local_14 += 8) {
        if (local_8 == pbVar1) {
          local_5c = pbVar1 + 1;
          local_8 = pbVar1 + *pbVar1 + 1;
        }
        pbVar1 = local_5c + 1;
        local_44 = (uint)*local_5c << ((byte)local_14 & 0x1f) | local_44;
      }
      uVar6 = (short)local_44 << 1 & local_20;
      if (local_54 < uVar6) {
        return;
      }
      local_44 = local_44 >> ((byte)local_50 & 0x1f);
      local_14 -= local_50;
      if (uVar6 == (ushort)(uVar3 + 2)) {
        return;
      }
      if (uVar6 != uVar3) break;
      local_54 = uVar3 + 4;
      local_50 = uVar4;
      local_20 = uVar5;
      local_c = uVar3;
    }
    local_4c = uVar6;
    if (local_c != uVar3) {
      uVar9 = (uptr)local_54;
      *(ushort *)(param_3 + uVar9) = local_c;
      *(i16 *)(iVar11 + uVar9) = *(i16 *)(iVar11 + (uint)local_c);
      *(short *)(iVar11 + uVar9) = *(short *)(iVar11 + uVar9) + 1;
      if (uVar6 < local_54) {
        local_24 += *(ushort *)(iVar11 + (uint)uVar6);
        local_40 += *(ushort *)(iVar11 + (uint)uVar6);
        local_58 = local_24;
        if ((int)puVar7 <= (int)local_24) {
          return;
        }
        do {
          puVar10 = local_58 - 1;
          *puVar10 = *(i8 *)(iVar10 + (uint)local_4c);
          uVar2 = *(ushort *)(param_3 + (uint)local_4c);
          if (uVar2 == 0xffff) break;
          puVar10 = local_58 - 2;
          *puVar10 = *(i8 *)(iVar10 + (uint)uVar2);
          local_4c = *(ushort *)(param_3 + (uint)uVar2);
          local_58 = puVar10;
        } while (local_4c != 0xffff);
      }
      else {
        iVar9 = *(ushort *)(iVar11 + (uint)local_c) + 1;
        local_24 += iVar9;
        local_58 = local_24 - 1;
        local_40 += (short)iVar9;
        if ((int)puVar7 <= (int)local_24) {
          return;
        }
        do {
          puVar10 = local_58 - 1;
          *puVar10 = *(i8 *)(iVar10 + (uint)local_c);
          uVar2 = *(ushort *)(param_3 + (uint)local_c);
          if (uVar2 == 0xffff) break;
          puVar10 = local_58 - 2;
          *puVar10 = *(i8 *)(iVar10 + (uint)uVar2);
          local_c = *(ushort *)(param_3 + (uint)uVar2);
          local_58 = puVar10;
        } while (local_c != 0xffff);
        local_24[-1] = *puVar10;
      }
      *(i8 *)(iVar10 + (uint)local_54) = *puVar10;
      local_54 += 2;
      local_c = uVar6;
      if ((local_20 < local_54) && (local_50 != 0xc)) {
        local_50++;
        local_20 = local_20 * 2 + 2;
      }
      goto LAB_005e549a;
    }
    local_24 += *(ushort *)(iVar11 + (uint)uVar6);
    local_40 += *(ushort *)(iVar11 + (uint)uVar6);
    local_58 = local_24;
    if ((int)puVar7 <= (int)local_24) {
      return;
    }
    do {
      local_58[-1] = *(i8 *)(iVar10 + (uint)local_4c);
      uVar2 = *(ushort *)(param_3 + (uint)local_4c);
      local_c = uVar6;
      if (uVar2 == 0xffff) break;
      local_58[-2] = *(i8 *)(iVar10 + (uint)uVar2);
      local_4c = *(ushort *)(param_3 + (uint)uVar2);
      local_58 -= 2;
    } while (local_4c != 0xffff);
  } while( true );
}
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_44
#undef local_40
#undef local_24
#undef local_20
#undef local_14
#undef local_c
#undef local_8

/* 005e5869 auto */
void __cdecl
dib_hline8(iptr param_1,i32 param_2,uint param_3,int param_4,int param_5,int param_6,
            int param_7)

{
  ushort uVar1;
  int iVar2;
  i32 *puVar3;
  
  if (param_7 < 1) {
    param_7 = -param_7;
    param_5 = (param_6 - 1) - param_5;
  }
  puVar3 = (i32 *)(param_1 + param_5 * param_7 + param_4);
  uVar1 = (ushort)param_3 >> 2;
  iVar2 = CONCAT22((short)(param_3 >> 0x10),uVar1);
  if (uVar1 != 0) {
    for (; iVar2 != 0; iVar2--) {
      *puVar3 = CONCAT22(CONCAT11((i8)param_2,(i8)param_2),
                         CONCAT11((i8)param_2,(i8)param_2));
      puVar3++;
    }
  }
  if ((param_3 & 2) != 0) {
    *(ushort *)puVar3 = CONCAT11((i8)param_2,(i8)param_2);
    puVar3 = (i32 *)((int)puVar3 + 2);
  }
  if ((param_3 & 1) != 0) {
    *(i8 *)puVar3 = (i8)param_2;
  }
  return;
}

/* 005e58e7 auto */
void __cdecl
dib_vline8(iptr param_1,i32 param_2,int param_3,iptr param_4,int param_5,int param_6,
            iptr param_7)

{
  iptr iVar1;
  i8 *puVar1;
  
  iVar1 = param_7;
  if (param_7 < 1) {
    iVar1 = -param_7;
    param_5 = (param_6 - 1) - param_5;
  }
  puVar1 = (i8 *)(param_1 + param_5 * iVar1 + param_4);
  do {
    *puVar1 = (i8)param_2;
    puVar1 += param_7;
    param_3--;
  } while (param_3 != 0);
  return;
}

/* 005e5ee0 auto */
void __thiscall ddsurf_dtor(void *this)

{
  return;
}

/* 005e89d0: written by hand in src/game/fixups.c */

/* 005ea578: written by hand in src/game/regargs.c */

/* 005ea677: written by hand in src/game/regargs.c */

/* 005ed710 auto */
void __cdecl
gdi_blit_transparent(HDC param_1,HGDIOBJ param_2,int param_3,int param_4,int param_5,int param_6,int param_7
            ,int param_8)

{
  HDC hdc;
  HGDIOBJ h;
  HDC hdc_00;
  HDC hdc_01;
  HBITMAP h_00;
  HGDIOBJ h_01;
  HBITMAP h_02;
  HGDIOBJ h_03;
  
  hdc = CreateCompatibleDC(param_1);
  h = SelectObject(hdc,param_2);
  hdc_00 = CreateCompatibleDC(param_1);
  hdc_01 = CreateCompatibleDC(param_1);
  h_00 = CreateCompatibleBitmap(param_1,param_5,param_6);
  h_01 = SelectObject(hdc_01,h_00);
  h_02 = CreateBitmap(param_5,param_6,1,1,(void *)0x0);
  h_03 = SelectObject(hdc_00,h_02);
  SetBkColor(hdc_01,0xffffff);
  SetTextColor(hdc_01,0);
  SetBkColor(hdc,0x808000);
  BitBlt(hdc_00,0,0,param_5,param_6,hdc,param_7,param_8,0xcc0020);
  BitBlt(hdc_01,0,0,param_5,param_6,param_1,param_3,param_4,0xcc0020);
  BitBlt(hdc_01,0,0,param_5,param_6,hdc,param_7,param_8,0x660046);
  BitBlt(hdc_01,0,0,param_5,param_6,hdc_00,0,0,0x8800c6);
  BitBlt(hdc_01,0,0,param_5,param_6,hdc,param_7,param_8,0x660046);
  BitBlt(param_1,param_3,param_4,param_5,param_6,hdc_01,0,0,0xcc0020);
  SelectObject(hdc_00,h_03);
  DeleteObject(h_02);
  SelectObject(hdc_01,h_01);
  DeleteObject(h_00);
  DeleteDC(hdc_00);
  DeleteDC(hdc_01);
  SelectObject(hdc,h);
  DeleteDC(hdc);
  return;
}
