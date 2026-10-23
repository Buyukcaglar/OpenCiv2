/* The game, graphics: sprites, surfaces, palettes, fonts: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00407f90 auto */
int __cdecl rect_width(iptr rect)

{
  return *(int *)(rect + 8) - *(int *)rect;
}

/* 00407fc0 auto */
int __cdecl rect_height(iptr rect)

{
  return *(int *)(rect + 0xc) - *(int *)(rect + 4);
}

/* 004083f0 auto */
void __thiscall surface_release(DibSurface *this)

{
  surface_create(this,0,0);
  return;
}

/* 00408680 auto */
void __cdecl rect_set(iptr rect,int left,int top,int right,int bottom)

{
  SetRect((LPRECT)rect,left,top,right,bottom);
  return;
}

/* 004086c0 auto */
void __cdecl rect_set_xywh(iptr rect,int x,int y,iptr width,iptr height)

{
  SetRect((LPRECT)rect,x,y,width + x,height + y);
  return;
}

/* 00408700 auto */
#define gfx_draw_target (*(i32 *)((u8 *)&g.d_00635c64))
void __cdecl gfx_target_frame_rect(iptr rect,i32 color)

{
  gfx_draw_box_ltrb(gfx_draw_target,*(i32 *)rect,*(i32 *)(rect + 4),
                     *(int *)(rect + 8) - 1,*(int *)(rect + 0xc) - 1,color);
  return;
}
#undef gfx_draw_target

/* 00408750 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl gfx_fill_draw_target(i32 color)

{
  gfx_fill_surface(gfx_draw_target,color);
  return;
}
#undef gfx_draw_target

/* 00408780 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl
gfx_target_fill_rect(i32 x,i32 y,i32 width,iptr height,
            i32 color)

{
  gfx_fill_rect_xywh(gfx_draw_target,x,y,width,height,color);
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
  i32 spacing;
  
  spacing = font_handle_line_spacing(this->hfont);
  return spacing;
}

/* 0040efd0 auto */
i32 __thiscall font_text_width(GameFont *this,iptr text)

{
  i32 width;
  
  width = font_measure_width(this->hfont,text);
  return width;
}

/* 0040f010 auto */
DibSurface * __thiscall surface_delete(DibSurface *this,uint flags)

{
  surface_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 0040fdb0 auto */
void __cdecl gfx_fill_rect(iptr surface,iptr rect,i32 color)

{
  iptr height;
  i32 width;
  
  height = rect_height(rect);
  width = rect_width(rect);
  gfx_fill_rect_xywh(surface,*(i32 *)rect,*(i32 *)(rect + 4),width,height,color
                    );
  return;
}

/* 00417ef0 auto */
void __thiscall font_set(GameFont *this,i32 face,iptr size)

{
  u32 handle;
  
  if (this->hfont != 0) {
    font_handle_destroy(this->hfont);
  }
  handle = font_handle_create(face,size,0);
  this->hfont = handle;
  handle = font_measure_height(this->hfont);
  this->cached_height = handle;
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
font_init(GameFont *this,i32 face,i32 size)

{
  u32 handle;
  
  handle = font_handle_create(face,size,0);
  this->hfont = handle;
  handle = font_measure_height(this->hfont);
  this->cached_height = handle;
  return this;
}

/* 0043c4c0 auto */
GameFont * __thiscall
font_init_styled
          (GameFont *this,i32 face,i32 size,i32 style)

{
  u32 handle;
  
  handle = font_handle_create(face,size,style);
  this->hfont = handle;
  handle = font_measure_height(this->hfont);
  this->cached_height = handle;
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
          (GameFont *this,i32 face,i32 size,i32 style)

{
  u32 handle;
  
  if (this->hfont != 0) {
    font_handle_destroy(this->hfont);
  }
  handle = font_handle_create(face,size,style);
  this->hfont = handle;
  handle = font_measure_height(this->hfont);
  this->cached_height = handle;
  return;
}

/* 0043c740 auto */
GamePalette * __thiscall palette_scalar_dtor(GamePalette *this,uint flags)

{
  palette_destroy(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 0043c790 auto */
void __cdecl rect_offset(iptr rect,int dx,int dy)

{
  OffsetRect((LPRECT)rect,dx,dy);
  return;
}

/* 0043c7c0 auto */
void __cdecl gfx_draw_rect_frame(iptr surface,iptr rect,i32 color)

{
  gfx_draw_box_ltrb(surface,*(i32 *)rect,*(i32 *)(rect + 4),
                     *(int *)(rect + 8) - 1,*(int *)(rect + 0xc) - 1,color);
  return;
}

/* 0043c8d0 auto */
i32 __cdecl gfx_draw_text(iptr text,i32 x,iptr y)

{
  i32 end_x;
  
  end_x = text_draw_shadowed(text_draw_surface,text,x,y);
  return end_x;
}

/* 0043c910 auto */
void __cdecl gfx_draw_text_centered(iptr text,i32 x,iptr y,i32 width)

{
  text_draw_centered(text_draw_surface,text,x,y,width);
  return;
}

/* 0043c950 auto */
i32 __cdecl
gfx_draw_text_right(iptr text,i32 right_x,i32 y,i32 flags)

{
  i32 result;
  
  result = text_draw_right_aligned(text_draw_surface,text,right_x,y,flags);
  return result;
}

/* 0043cbb0 auto */
Sprite * __thiscall sprite_scalar_dtor(Sprite *this,uint flags)

{
  sprite_destroy(this);
  if ((flags & 1) != 0) {
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
#define grab_rect_d (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define grab_rect_c (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define grab_rect_b (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define grab_rect_a (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define coast_idx (*(int *)(frame_ + FRAME_OFF(64)))
#define blank_sprite (*(Sprite *)(frame_ + FRAME_OFF(68)))
#define base_y (*(int *)(frame_ + FRAME_OFF(128)))
#define quarter (*(int *)(frame_ + FRAME_OFF(132)))
#define res2_x (*(i32 *)(frame_ + FRAME_OFF(136)))
#define y2 (*(int *)(frame_ + FRAME_OFF(140)))
#define res_x (*(i32 *)(frame_ + FRAME_OFF(144)))
#define x2 (*(int *)(frame_ + FRAME_OFF(148)))
#define base_x (*(int *)(frame_ + FRAME_OFF(152)))
#define terrain2 (*(int *)(frame_ + FRAME_OFF(156)))
#define i (*(uint *)(frame_ + FRAME_OFF(160)))
#define dither_mask (*(Sprite *)(frame_ + FRAME_OFF(164)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(224)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(228)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(232)))
void __cdecl gfx_load_terrain_sprites(void)

{
  int loaded;
  i8 frame_[FRAME_OFF(240)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  sprite_init(&dither_mask);
  eh_state = 0;
  sprite_init(&blank_sprite);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
  __chdir(&scenario_dir_path);
  loaded = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_006266e0),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (loaded == 0) {
    loaded = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_006266f0),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    if (loaded == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_00626700),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  x2 = 1;
  res_x = 0x83;
  res2_x = 0xc4;
  y2 = 1;
  for (terrain2 = 0; terrain2 < 0xb; terrain2++) {
    sprite_free((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c));
    sprite_free((Sprite *)(&terrain_resource_sprites + terrain2 * 0x78));
    sprite_free((Sprite *)(&terrain_resource2_sprites + terrain2 * 0x78));
    sprite_grab_tile_cell((iptr)(&terrain_base_sprites + terrain2 * 0x3c),x2,y2);
    sprite_grab_tile_cell((iptr)(&terrain_resource_sprites + terrain2 * 0x78),res_x,y2);
    sprite_grab_tile_cell((iptr)(&terrain_resource2_sprites + terrain2 * 0x78),res2_x,y2);
    y2 += 0x21;
  }
  x2 = 0x1c8;
  y2 = 100;
  for (i = 0; (int)i < 3; i++) {
    sprite_free((Sprite *)(&land_improvement_sprites + i * 0x3c));
    sprite_grab_tile_cell((iptr)(&land_improvement_sprites + i * 0x3c),x2,y2);
    y2 += 0x21;
  }
  sprite_free((Sprite *)&pollution_sprite);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00641808),x2,y2);
  y2 += 0x21;
  sprite_free((Sprite *)&grassland_shield_sprite);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_0063fc18),x2,y2);
  y2 += 0x21;
  sprite_free((Sprite *)&hut_sprite);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00646158),x2,y2);
  y2 = 0x16c;
  x2 = 1;
  for (i = 0; (int)i < 9; i++) {
    sprite_free((Sprite *)(&road_sprites + i * 0x3c));
    sprite_free((Sprite *)(&railroad_sprites + i * 0x3c));
    sprite_grab_tile_cell((iptr)(&road_sprites + i * 0x3c),x2,y2);
    sprite_grab_tile_cell((iptr)(&railroad_sprites + i * 0x3c),x2,y2 + 0x21);
    x2 += 0x41;
  }
  sprite_free(&dither_mask);
  sprite_grab_tile_cell((iptr)&dither_mask,1,0x1bf);
  sprite_free((Sprite *)&tile_pick_mask_sprite);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_0063fcd8),0x42,0x1bf);
  sprite_free((Sprite *)&unexplored_tile_sprite);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00646118),0x83,0x1bf);
  sprite_free((Sprite *)&tile_direction_mask_sprite);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00647ed8),0x105,0x1bf);
  sprite_free(&blank_sprite);
  sprite_grab_tile_cell((iptr)&blank_sprite,0xc4,0x1bf);
  for (terrain2 = 0; terrain2 < 0xd; terrain2++) {
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_0063fe08),0,0,0x40,0x20,7);
    if (terrain2 < 0xb) {
      sprite_draw
                ((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c),(iptr)grab_rect_a,(iptr)((u8 *)&g.d_0063fe08),0,0);
    }
    else if (terrain2 == 0xb) {
      sprite_draw((Sprite *)&unexplored_tile_sprite,(iptr)grab_rect_b,(iptr)((u8 *)&g.d_0063fe08),0,0);
    }
    else {
      sprite_draw(&blank_sprite,(iptr)grab_rect_c,(iptr)((u8 *)&g.d_0063fe08),0,0);
    }
    sprite_draw_keyed(&dither_mask,(iptr)grab_rect_d,(iptr)((u8 *)&g.d_0063fe08),10,0,0);
    for (quarter = 0; quarter < 4; quarter++) {
      if (quarter < 2) {
        x2 = 0x20;
      }
      else {
        x2 = 0;
      }
      if ((quarter < 1) || (2 < quarter)) {
        y2 = 0;
      }
      else {
        y2 = 0x10;
      }
      sprite_free
                ((Sprite *)(&terrain_dither_sprites + quarter * 0x3c + terrain2 * 0xf0));
      sprite_grab_from_sheet((iptr)(&terrain_dither_sprites + terrain2 * 0xf0 + quarter * 0x3c),x2,y2,0x20,
                   0x10);
    }
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  loaded = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_00626710),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (loaded == 0) {
    loaded = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_00626720),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    if (loaded == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_00626730),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  base_x = 1;
  base_y = 0x43;
  for (i = 0; (int)i < 0x10; i++) {
    x2 = (i & 7) * 0x41;
    y2 = ((int)i >> 3) * 0x21;
    sprite_free((Sprite *)(&river_sprites + i * 0x3c));
    sprite_free((Sprite *)(&forest_sprites + i * 0x3c));
    sprite_free((Sprite *)(&mountain_sprites + i * 0x3c));
    sprite_free((Sprite *)(&hill_sprites + i * 0x3c));
    sprite_grab_tile_cell((iptr)(&river_sprites + i * 0x3c),base_x + x2,base_y + y2);
    sprite_grab_tile_cell((iptr)(&forest_sprites + i * 0x3c),base_x + x2,
                 base_y + y2 + 0x42);
    sprite_grab_tile_cell((iptr)(&mountain_sprites + i * 0x3c),base_x + x2,
                 base_y + y2 + 0x84);
    sprite_grab_tile_cell((iptr)(&hill_sprites + i * 0x3c),base_x + x2,
                 base_y + y2 + 0xc6);
  }
  base_x = 1;
  base_y = 0x1ad;
  for (coast_idx = 0; coast_idx < 8; coast_idx++) {
    sprite_free((Sprite *)(&coast_quarter_sprites + coast_idx * 0xf0));
    sprite_free((Sprite *)(&coast_quarter_east_sprites + coast_idx * 0xf0));
    sprite_free((Sprite *)(&coast_quarter_south_sprites + coast_idx * 0xf0));
    sprite_free((Sprite *)(&coast_quarter_west_sprites + coast_idx * 0xf0));
    sprite_grab_from_sheet((iptr)(&coast_quarter_sprites + coast_idx * 0xf0),base_x,base_y,0x20,0x10);
    sprite_grab_from_sheet((iptr)(&coast_quarter_east_sprites + coast_idx * 0xf0),base_x + 0x21,base_y + 0x22,0x20,0x10);
    sprite_grab_from_sheet((iptr)(&coast_quarter_south_sprites + coast_idx * 0xf0),base_x,base_y + 0x11,0x20,0x10);
    sprite_grab_from_sheet((iptr)(&coast_quarter_west_sprites + coast_idx * 0xf0),base_x,base_y + 0x22,0x20,0x10);
    base_x += 0x42;
  }
  base_x = 1;
  base_y = 0x14b;
  for (i = 0; (int)i < 4; i++) {
    sprite_free((Sprite *)(&river_mouth_sprites + i * 0x3c));
    sprite_grab_tile_cell((iptr)(&river_mouth_sprites + i * 0x3c),base_x,base_y);
    base_x += 0x41;
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 0044996f */ { sprite_destroy((Sprite *)((iptr)&blank_sprite)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0044997b */ { sprite_destroy((Sprite *)((iptr)&dither_mask)); }
  return;
}
#undef grab_rect_d
#undef grab_rect_c
#undef grab_rect_b
#undef grab_rect_a
#undef coast_idx
#undef blank_sprite
#undef base_y
#undef quarter
#undef res2_x
#undef y2
#undef res_x
#undef x2
#undef base_x
#undef terrain2
#undef i
#undef dither_mask
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0044999c auto */
void __cdecl sprite_grab_tile_cell(iptr sprite,i32 x,i32 y)

{
  sprite_grab_from_surface((Sprite *)sprite,(iptr)((u8 *)&g.d_0063fe08),7,x,y,0x40,0x20);
  sprite_replace_color((Sprite *)sprite,9,7);
  return;
}

/* 004499d3 auto */
void __cdecl
sprite_grab_from_sheet(iptr sprite,i32 x,i32 y,i32 width,
            i32 height)

{
  sprite_grab_from_surface((Sprite *)sprite,(iptr)((u8 *)&g.d_0063fe08),7,x,y,width,height);
  sprite_replace_color((Sprite *)sprite,9,7);
  return;
}

/* 00449a0e auto */
#define dlg_client_tile_surface (*(i8 * *)((u8 *)&g.d_00635aa4))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define col (*(int *)(frame_ + FRAME_OFF(12)))
#define frame_count (*(int *)(frame_ + FRAME_OFF(16)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(20)))
#define k (*(int *)(frame_ + FRAME_OFF(1096)))
#define y2 (*(int *)(frame_ + FRAME_OFF(1100)))
#define x2 (*(int *)(frame_ + FRAME_OFF(1104)))
#define j (*(int *)(frame_ + FRAME_OFF(1108)))
#define i (*(int *)(frame_ + FRAME_OFF(1112)))
#define row (*(int *)(frame_ + FRAME_OFF(1116)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1120)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1124)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(1128)))
void __cdecl gfx_load_icon_sprites(void)

{
  int loaded;
  i8 frame_[FRAME_OFF(1136)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  __chdir(&scenario_dir_path);
  loaded = surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x55,10,0xc0,(iptr)&palette);
  if (loaded == 0) {
    __chdir(&game_home_dir);
    surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x55,10,0xc0,(iptr)&palette);
  }
  __chdir(&game_home_dir);
  x2 = 1;
  y2 = 1;
  frame_count = 0;
  for (i = 0; i < 0xb; i++) {
    sprite_free((Sprite *)(&nuke_anim_sprites + i * 0x3c));
    sprite_grab_from_sheet((iptr)(&nuke_anim_sprites + i * 0x3c),x2,y2,0x5b,0x48);
    x2 += 0x5c;
    frame_count++;
    if (frame_count == 6) {
      x2 = 1;
      y2 += 0x49;
    }
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  loaded = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_00626740),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (loaded == 0) {
    loaded = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_0062674c),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    if (loaded == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_00626758),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
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
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00640b98),199,0x100);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00646198),199,0x121);
  sprite_grab_tile_cell((iptr)((u8 *)&g.d_00647bc8),0xf8,0x1ae);
  sprite_free((Sprite *)&fortify_overlay_alt_sprite);
  gfx_grab_fortify_overlay(1,0x20,0xbb);
  sprite_free((Sprite *)&icon_sprite_6);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_0064668c),0x22,0xdf);
  sprite_free((Sprite *)&pollution_icon_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006466c8),0x43,0xdf,0x20,0x20);
  sprite_free((Sprite *)&icon_sprite_7);
  sprite_free((Sprite *)&icon_sprite_8);
  sprite_free((Sprite *)&city_disorder_icon_sprite);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_00646704),100,0xdf);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_00646740),0x85,0xdf);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_0064677c),0xa6,0xdf,0x1e,0x1e);
  sprite_free((Sprite *)&icon_misc_sprites);
  sprite_free((Sprite *)&icon_sprite_1);
  sprite_free((Sprite *)&icon_sprite_4);
  sprite_free((Sprite *)&icon_sprite_5);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_0063f6f0),199,0x100);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_0063f72c),0xe8,0x100);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_0063f7e0),0x109,0x100);
  sprite_grab_icon_cell_keyed((iptr)((u8 *)&g.d_0063f81c),0x12a,0x100);
  sprite_free((Sprite *)&icon_sprite_2);
  sprite_free((Sprite *)&icon_sprite_3);
  sprite_free((Sprite *)&icons_unused_tall_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_0063f768),0x137,1,0x1f,0x60);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_0063f7a4),0x137,0x62,0x1f,0x60);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00648098),0x109,0x121,0x38,0x83);
  x2 = 1;
  y2 = 0x122;
  for (i = 0; i < 3; i++) {
    for (k = 0; k < 2; k++) {
      sprite_free((Sprite *)(&resource_shortage_icon_sprites + i * 0x78));
      sprite_free((Sprite *)(&resource_icon_sprites + i * 0x78));
      sprite_grab_square((iptr)(&resource_shortage_icon_sprites + i * 0x78),x2,y2,0xe);
      sprite_grab_square((iptr)(&resource_icon_sprites + i * 0x78),x2,y2 + 0xf,0xe);
    }
    x2 += 0xf;
  }
  x2 = 1;
  y2 = 0x140;
  for (i = 0; i < 3; i++) {
    sprite_free((Sprite *)(&tax_rate_icon_sprites + i * 0x3c));
    sprite_grab_square((iptr)(&tax_rate_icon_sprites + i * 0x3c),x2,y2,0xe);
    x2 += 0xf;
  }
  x2 = 0x31;
  y2 = 0x14e;
  for (i = 0; i < 3; i++) {
    sprite_free((Sprite *)(&small_resource_icon_sprites + i * 0x3c));
    sprite_grab_square((iptr)(&small_resource_icon_sprites + i * 0x3c),x2,y2,10);
    x2 += 0xb;
  }
  x2 = 0x31;
  y2 = 0x159;
  for (i = 0; i < 3; i++) {
    sprite_free((Sprite *)(&lux_tax_sci_icon_sprites + i * 0x3c));
    sprite_grab_square((iptr)(&lux_tax_sci_icon_sprites + i * 0x3c),x2,y2,10);
    x2 += 0xb;
  }
  sprite_free((Sprite *)&small_unhappy_icon_sprite);
  sprite_free((Sprite *)&unhappy_suppressed_icon_sprite);
  sprite_grab_square((iptr)((u8 *)&g.d_00646598),0x52,0x14e,10);
  sprite_grab_square((iptr)((u8 *)&g.d_00648058),0x52,0x159,10);
  x2 = 0x31;
  y2 = 0x122;
  for (i = 0; i < 4; i++) {
    sprite_free((Sprite *)(&research_flask_sprites + i * 0x3c));
    sprite_free((Sprite *)(&global_warming_sprites + i * 0x3c));
    sprite_grab_square((iptr)(&research_flask_sprites + i * 0x3c),x2,y2,0xe);
    sprite_grab_square((iptr)(&global_warming_sprites + i * 0x3c),x2,0x131,0xe);
    x2 += 0xf;
  }
  x2 = 1;
  y2 = 0x164;
  for (i = 0; i < 8; i++) {
    sprite_free((Sprite *)(&explosion_sprites + i * 0x3c));
    sprite_grab_from_sheet((iptr)(&explosion_sprites + i * 0x3c),x2,y2,0x20,0x20);
    x2 += 0x21;
  }
  surface_create((DibSurface *)&window_border_tile_surface,0x40,0x20);
  gfx_copy_rect_xywh((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_00647f18),199,0x142,0,0,0x40,0x20);
  dialog_set_frame_tile_surface((iptr)((u8 *)&g.d_00647f18));
  frame_set_border_tile((iptr)((u8 *)&g.d_00647f18));
  surface_create((DibSurface *)&panel_texture_surface,0x20,0x20);
  gfx_copy_rect_xywh((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_00640990),0x12a,0xbe,0,0,0x20,0x20);
  dlg_client_tile_surface = &panel_texture_surface;
  x2 = 0x157;
  y2 = 1;
  col = 0;
  for (i = 1; i < 0x27; i++) {
    sprite_free((Sprite *)(&improvement_icon_sprites + i * 0x3c));
    sprite_grab_from_sheet((iptr)(&improvement_icon_sprites + i * 0x3c),x2,y2,0x24,0x14);
    x2 += 0x25;
    col++;
    if (7 < col) {
      col = 0;
      y2 += 0x15;
      x2 = 0x157;
    }
  }
  x2 = 0x157;
  y2 = 0x6a;
  col = 0;
  for (i = 0; i < 0x1c; i++) {
    sprite_free((Sprite *)(&wonder_icon_sprites + i * 0x3c));
    sprite_grab_from_sheet((iptr)(&wonder_icon_sprites + i * 0x3c),x2,y2,0x24,0x14);
    x2 += 0x25;
    col++;
    if (6 < col) {
      col = 0;
      y2 += 0x15;
      x2 = 0x157;
    }
  }
  y2 = 0xd3;
  for (i = 0; i < 4; i++) {
    x2 = 0x157;
    for (j = 0; j < 5; j++) {
      sprite_free
                ((Sprite *)(&advance_category_icon_sprites + j * 0xf0 + i * 0x3c));
      sprite_grab_from_sheet((iptr)(&advance_category_icon_sprites + i * 0x3c + j * 0xf0),x2,y2,0x24,
                   0x14);
      x2 += 0x25;
    }
    y2 += 0x15;
  }
  sprite_free((Sprite *)&icons_pair_sprites);
  sprite_free((Sprite *)&icon_sprite_9);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00647b50),0x15e,0xff,0x40,0x20);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00647b8c),0x15e,0x120,0x40,0x20);
  sprite_free((Sprite *)&caption_close_button_sprite);
  sprite_free((Sprite *)&caption_zoom_out_sprite);
  sprite_free((Sprite *)&caption_zoom_out_button_sprite);
  sprite_free((Sprite *)&caption_view_mode_button_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00645120),1,0x185,0x10,0x10);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00648820),0x12,0x185,0x10,0x10);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00647788),0x23,0x185,0x10,0x10);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00647348),0x34,0x185,0x10,0x10);
  sprite_free((Sprite *)&scroll_up_button_sprite);
  sprite_free((Sprite *)&city_down_arrow_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00644770),0xe3,0x185,0x12,0x18);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006480d8),0xf6,0x185,0x12,0x18);
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&game_home_dir);
  loaded = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_00626764),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (loaded != 0) {
    x2 = 1;
    y2 = 0x1bf;
    for (i = 0; i < 0xf; i++) {
      sprite_free((Sprite *)(&sprite_editor_tool_sprites + i * 0x3c));
      sprite_grab_from_sheet((iptr)(&sprite_editor_tool_sprites + i * 0x3c),x2,y2,0x20,0x20);
      x2 += 0x21;
    }
  }
  sprite_free((Sprite *)&editor_unit_backdrop_sprite);
  sprite_grab_from_surface((Sprite *)&editor_unit_backdrop_sprite,(iptr)((u8 *)&g.d_0063fe08),7,0x23f,1,0x40,0x30);
  sprite_free((Sprite *)&editor_tile_backdrop_sprite);
  sprite_grab_from_surface((Sprite *)&editor_tile_backdrop_sprite,(iptr)((u8 *)&g.d_0063fe08),7,0x23f,0x32,0x40,0x20);
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  loaded = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_00626774),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (loaded == 0) {
    loaded = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_00626780),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    if (loaded == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_0062678c),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  y2 = 6;
  for (row = 0; row < 4; row++) {
    x2 = 2;
    for (i = 0; i < 0xb; i++) {
      sprite_free
                ((Sprite *)(&citizen_sprites + row * 0x294 + i * 0x3c));
      sprite_grab_from_sheet((iptr)(&citizen_sprites + i * 0x3c + row * 0x294),x2,y2,0x1b
                   ,0x1e);
      x2 += 0x1c;
    }
    y2 += 0x1f;
  }
  x2 = 2;
  y2 = 0x89;
  for (i = 0; i < 0xb; i++) {
    sprite_free((Sprite *)(&small_citizen_sprites + i * 0x3c));
    sprite_grab_from_sheet((iptr)(&small_citizen_sprites + i * 0x3c),x2,y2,0xf,0x1a);
    x2 += 0x10;
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  __chdir(&scenario_dir_path);
  loaded = surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x56,10,0xc0,(iptr)&palette);
  if (loaded == 0) {
    __chdir(&game_home_dir);
    surface_load_gif_resource((DibSurface *)&gfx_sheet_surface,0x56,10,0xc0,(iptr)&palette);
  }
  __chdir(&game_home_dir);
  x2 = 2;
  y2 = 0x44;
  sprite_free((Sprite *)&government_sprites);
  sprite_free((Sprite *)&government_despotism_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00646878),x2,y2,0x22,0x22);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006468b4),x2,y2,0x22,0x22);
  x2 += 0x42;
  sprite_free((Sprite *)&government_sprite_communism);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_0064692c),x2,y2,0x22,0x22);
  x2 += 0x42;
  sprite_free((Sprite *)&government_sprite_fundamentalism);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00646968),x2,y2,0x22,0x22);
  x2 += 0x42;
  sprite_free((Sprite *)&government_monarchy_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006468f0),x2,y2,0x22,0x22);
  x2 += 0x42;
  sprite_free((Sprite *)&government_sprite_democracy);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006469e0),x2,y2,0x22,0x22);
  x2 += 0x42;
  sprite_free((Sprite *)&government_sprite_republic);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006469a4),x2,y2,0x22,0x22);
  x2 = 2;
  y2 = 200;
  sprite_free((Sprite *)&ceasefire_icon_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00647748),x2,y2,0x40,0x40);
  x2 += 0x42;
  sprite_free((Sprite *)&peace_treaty_icon_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_006409d8),x2,y2,0x40,0x40);
  x2 += 0x42;
  sprite_free((Sprite *)&war_icon_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00644e48),x2,y2,0x40,0x40);
  x2 += 0x42;
  sprite_free((Sprite *)&signal_allied_icon_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_0063fc98),x2,y2,0x40,0x40);
  x2 += 0x42;
  sprite_free((Sprite *)&diplo_popup_portrait_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00648018),x2,y2,0x40,0x40);
  sprite_free((Sprite *)&popup_info_icon_sprite);
  sprite_free((Sprite *)&tutorial_icon_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_0063fc58),0x18e,0x86,0x40,0x40);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00643af8),0x86,0x18e,0x40,0x40);
  for (civ = 0; civ < 8; civ++) {
    sprite_free((Sprite *)(&civ_portrait_sprites + civ * 0x3c));
    sprite_grab_from_sheet((iptr)(&civ_portrait_sprites + civ * 0x3c),2,0x18e,0x40,0x40);
    sprite_replace_color
              ((Sprite *)(&civ_portrait_sprites + civ * 0x3c),8,
               *(i32 *)(&civ_primary_colors + civ * 0x10));
  }
  surface_release((DibSurface *)&gfx_sheet_surface);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0044ab4e */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef dlg_client_tile_surface
#undef civ
#undef col
#undef frame_count
#undef palette
#undef k
#undef y2
#undef x2
#undef j
#undef i
#undef row
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0044ab72 auto */
void __cdecl sprite_grab_icon_cell_keyed(iptr sprite,i32 x,i32 y)

{
  sprite_grab_from_surface((Sprite *)sprite,(iptr)((u8 *)&g.d_0063fe08),7,x,y,0x20,0x20);
  sprite_replace_color((Sprite *)sprite,9,7);
  return;
}

/* 0044aba9 auto */
void __cdecl sprite_grab_square(iptr sprite,i32 x,i32 y,i32 size)

{
  sprite_grab_from_sheet(sprite,x,y,size,size);
  return;
}

/* 0044abd5 auto */
void __cdecl gfx_grab_fortify_overlay(int index,i32 x,i32 y)

{
  sprite_grab_city_cell((iptr)(&fortify_overlay_sprites + index * 0x3c),x,y);
  return;
}

/* 0044ac07 auto */
void __cdecl sprite_grab_city_cell(iptr sprite,i32 x,i32 y)

{
  sprite_grab_from_surface((Sprite *)sprite,(iptr)((u8 *)&g.d_0063fe08),7,x,y,0x40,0x30);
  sprite_replace_color((Sprite *)sprite,9,7);
  return;
}

/* 0044ae4c auto */
#define style2 (*(int *)(frame_ + FRAME_OFF(0)))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(20)))
#define flag_x (*(int *)(frame_ + FRAME_OFF(28)))
#define size_idx (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl gfx_load_city_sprites(void)

{
  int cell_x;
  i32 color;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  __chdir(&scenario_dir_path);
  cell_x = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_00626798),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (cell_x == 0) {
    cell_x = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_006267a4),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    if (cell_x == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_006267b0),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  y2 = 0x27;
  for (style2 = 0; style2 < 6; style2++) {
    for (size_idx = 0; size_idx < 4; size_idx++) {
      sprite_free
                ((Sprite *)(&city_sprites + size_idx * 0x78 + style2 * 0x1e0));
      sprite_free
                ((Sprite *)(&city_walled_sprites + size_idx * 0x78 + style2 * 0x1e0));
      cell_x = size_idx * 0x41;
      sprite_grab_city_cell((iptr)(&city_sprites + style2 * 0x1e0 + size_idx * 0x78),cell_x + 1,y2);
      city_sprite_scan_flag_offset(style2,size_idx,0,cell_x + 1,y2);
      city_sprite_scan_size_box_offset(style2,size_idx,0,cell_x + 1,y2);
      sprite_grab_city_cell((iptr)(&city_walled_sprites + style2 * 0x1e0 + size_idx * 0x78),cell_x + 0x14e,y2)
      ;
      city_sprite_scan_flag_offset(style2,size_idx,1,cell_x + 0x14e,y2);
      city_sprite_scan_size_box_offset(style2,size_idx,1,cell_x + 0x14e,y2);
    }
    y2 += 0x31;
  }
  flag_x = 1;
  for (civ = 0; civ < 8; civ++) {
    sprite_free((Sprite *)(&civ_flag_sprites + civ * 0x78));
    sprite_free((Sprite *)(&civ_flag_dark_sprites + civ * 0x78));
    sprite_grab_from_sheet((iptr)(&civ_flag_sprites + civ * 0x78),flag_x,0x1a9,0xe,0x16);
    sprite_grab_from_sheet((iptr)(&civ_flag_dark_sprites + civ * 0x78),flag_x,0x1c0,0xe,0x16);
    color = surface_get_pixel((DibSurface *)&gfx_sheet_surface,flag_x + 3,0x1ad);
    *(i32 *)(&civ_primary_colors + civ * 0x10) = color;
    color = surface_get_pixel((DibSurface *)&gfx_sheet_surface,flag_x + 6,0x1ad);
    *(i32 *)(&civ_mid_colors + civ * 0x10) = color;
    color = surface_get_pixel((DibSurface *)&gfx_sheet_surface,flag_x,0x1a7);
    *(i32 *)(&civ_secondary_colors + civ * 0x10) = color;
    flag_x += 0xf;
  }
  sprite_free((Sprite *)&fortify_overlay_sprites);
  sprite_free((Sprite *)&fortress_sprite);
  sprite_grab_city_cell((iptr)((u8 *)&g.d_006465d8),0x8f,0x1a7);
  sprite_grab_city_cell((iptr)((u8 *)&g.d_00646650),0xd0,0x1a7);
  sprite_free((Sprite *)&airbase_sprites);
  sprite_free((Sprite *)&airbase_occupied_sprite);
  sprite_grab_city_cell((iptr)((u8 *)&g.d_00647fa0),0x111,0x1a7);
  sprite_grab_city_cell((iptr)((u8 *)&g.d_00647fdc),0x152,0x1a7);
  surface_release((DibSurface *)&gfx_sheet_surface);
  return;
}
#undef style2
#undef civ
#undef y2
#undef flag_x
#undef size_idx

/* 0044b30e auto */
#define col (*(int *)(frame_ + FRAME_OFF(0)))
#define unit_type (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(12)))
#define x2 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_load_unit_sprites(void)

{
  int loaded;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __chdir(&scenario_dir_path);
  loaded = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_0063fe08),(iptr)((u8 *)&g.d_006267bc),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
  if (loaded == 0) {
    loaded = surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_006267c8),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    if (loaded == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&gfx_sheet_surface,(iptr)((u8 *)&g.d_006267d4),10,0xc0,(iptr)((u8 *)&g.d_006a8c00));
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  col = 0;
  y2 = 1;
  x2 = 1;
  for (unit_type = 0; unit_type < 0x3f; unit_type++) {
    sprite_free((Sprite *)(&unit_sprites + unit_type * 0x3c));
    sprite_grab_city_cell((iptr)(&unit_sprites + unit_type * 0x3c),x2,y2);
    unit_sprite_scan_shield_offset(unit_type,x2,y2);
    col++;
    x2 += 0x41;
    if (8 < col) {
      col = 0;
      y2 += 0x31;
      x2 = 1;
    }
  }
  sprite_free((Sprite *)&unit_shield_sprite);
  sprite_grab_from_sheet((iptr)((u8 *)&g.d_00647f60),0x24a,1,0xc,0x14);
  surface_release((DibSurface *)&gfx_sheet_surface);
  return;
}
#undef col
#undef unit_type
#undef y2
#undef x2

/* 0044b49e auto */
#define surf_wnd2 (*(SurfaceWindow *)(frame_ + FRAME_OFF(4)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(280)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(284)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(288)))
void __cdecl gfx_load_game_sprites(void)

{
  i8 frame_[FRAME_OFF(296)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surfwnd_ctor(&surf_wnd2);
  eh_state = 0;
  gfx_load_city_sprites();
  gfx_load_icon_sprites();
  gfx_load_terrain_sprites();
  gfx_load_unit_sprites();
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0044b4f6 */ { surfwnd_dtor((SurfaceWindow *)((iptr)&surf_wnd2)); }
  return;
}
#undef surf_wnd2
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00451830 auto */
i32 __thiscall sprite_get_width(Sprite *this)

{
  i32 width;
  
  width = rect_width((iptr)&this->bounds_rect);
  return width;
}

/* 00451860 auto */
i32 __thiscall sprite_get_height(Sprite *this)

{
  i32 height;
  
  height = rect_height((iptr)&this->bounds_rect);
  return height;
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
#define offset (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl gfx_build_grey_remap(void)

{
  int rgb_handle;
  iptr rgb_data;
  int handle;
  LOGPALETTE *plpal;
  HPALETTE h;
  iptr full_rgb;
  iptr remap_table;
  UINT UVar4;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rgb_handle = mem_handle_alloc(0x2c4);
  if (rgb_handle == 0) {
    err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_0062b56c),(iptr)((u8 *)&g.d_0062b550),0x22);
  }
  else {
    rgb_data = mem_handle_lock(rgb_handle);
    palette_get_rgb((GamePalette *)&game_palette,rgb_data,10,0x20);
    handle = mem_handle_alloc(0x88);
    if (handle == 0) {
      err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_0062b59c),(iptr)((u8 *)&g.d_0062b580),0x2a);
      mem_handle_unlock(rgb_handle);
      mem_handle_free(rgb_handle);
    }
    else {
      plpal = (LOGPALETTE *)mem_handle_lock(handle);
      plpal->palVersion = 0x300;
      plpal->palNumEntries = 0x20;
      for (offset = 0; offset < 0x60; offset += 3) {
        plpal->palPalEntry[offset / 3].peRed = *(BYTE *)(offset + rgb_data);
        plpal->palPalEntry[offset / 3].peGreen = *(BYTE *)(offset + 1 + rgb_data);
        plpal->palPalEntry[offset / 3].peBlue = *(BYTE *)(offset + 2 + rgb_data);
        plpal->palPalEntry[offset / 3].peFlags = 4;
      }
      h = CreatePalette(plpal);
      if (h == (HPALETTE)0x0) {
        err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_0062b5c0),(iptr)((u8 *)&g.d_0062b5a4),0x3e);
        mem_handle_unlock(rgb_handle);
        mem_handle_free(rgb_handle);
      }
      else {
        mem_handle_unlock(handle);
        mem_handle_free(handle);
        handle = mem_handle_alloc(0x2c4);
        if (handle == 0) {
          err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_0062b5ec),(iptr)((u8 *)&g.d_0062b5d0),0x48);
          mem_handle_unlock(rgb_handle);
          mem_handle_free(rgb_handle);
        }
        else {
          full_rgb = mem_handle_lock(handle);
          grey_remap_handle = mem_handle_alloc(0xec);
          if (grey_remap_handle == 0) {
            err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_0062b618),(iptr)((u8 *)&g.d_0062b5fc),0x51);
            mem_handle_unlock(rgb_handle);
            mem_handle_free(rgb_handle);
            mem_handle_unlock(handle);
            mem_handle_free(handle);
          }
          else {
            remap_table = mem_handle_lock(grey_remap_handle);
            palette_get_rgb((GamePalette *)&game_palette,full_rgb,10,0xec);
            for (offset = 0; offset < 0x2c4; offset += 3) {
              UVar4 = GetNearestPaletteIndex
                                (h,(uint)CONCAT12(*(i8 *)(offset + 2 + full_rgb),
                                                  CONCAT11(*(i8 *)(offset + 1 + full_rgb),
                                                           *(i8 *)(offset + full_rgb))));
              *(char *)(remap_table + offset / 3) = (char)UVar4 + '\n';
              palette_set_entry
                        ((GamePalette *)&grey_palette,offset / 3 + 10,
                         CONCAT31((int3)(UVar4 * 3 >> 8),*(i8 *)(UVar4 * 3 + rgb_data)),
                         CONCAT31((int3)(UVar4 * 3 >> 8),*(i8 *)(UVar4 * 3 + 1 + rgb_data)),
                         CONCAT31((int3)(UVar4 * 3 >> 8),*(i8 *)(UVar4 * 3 + 2 + rgb_data)));
            }
            DeleteObject(h);
            mem_handle_unlock(handle);
            mem_handle_free(handle);
            mem_handle_unlock(rgb_handle);
            mem_handle_free(rgb_handle);
            mem_handle_unlock(grey_remap_handle);
          }
        }
      }
    }
  }
  return;
}
#undef grey_remap_handle
#undef offset

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
#define view (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl gfx_grey_out_windows(void)

{
  int remap_table;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  remap_table = mem_handle_lock(grey_remap_handle);
  if (remap_table != 0) {
    for (view = 0; view < 8; view++) {
      if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
        surface_remap_colors
                  ((DibSurface *)(&map_views + view * 0x3f0),remap_table,10,0xec);
      }
    }
    surface_remap_colors((DibSurface *)&status_window,remap_table,10,0xec);
    surface_remap_colors((DibSurface *)&minimap_window,remap_table,10,0xec);
    surface_remap_colors((DibSurface *)&city_window,remap_table,10,0xec);
    mem_handle_unlock(grey_remap_handle);
    ui_blit_all_windows();
  }
  return;
}
#undef grey_remap_handle
#undef view

/* 0046ef3f auto */
#define view (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl gfx_repaint_main_windows(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      wnd_repaint((SurfaceWindow *)(&map_views + view * 0x3f0));
    }
  }
  wnd_repaint((SurfaceWindow *)&minimap_window);
  wnd_repaint((SurfaceWindow *)&status_window);
  wnd_repaint((SurfaceWindow *)&city_window);
  wnd_flush_paint();
  return;
}
#undef view

/* 0046efd6 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define step (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl screen_fade_out(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  if (gfx_palettized_display != 0) {
    palette_fade_begin((GamePalette *)&game_palette,10,0xec,10,(iptr)((u8 *)&g.d_0066bfd0));
    ui_blit_all_windows();
    step = 10;
    while (-1 < step) {
      palette_fade_step((GamePalette *)&game_palette,step);
      ui_delay_ticks(1);
      step--;
    }
    palette_set_nocollapse_all();
    gfx_grey_out_windows();
    palette_fade_end((GamePalette *)&game_palette);
    palette_set_nocollapse_all();
  }
  return;
}
#undef unit_blink_active
#undef step

/* 0046f06f auto */
#define step (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl screen_fade_in(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (gfx_palettized_display != 0) {
    palette_fade_begin((GamePalette *)&game_palette,10,0xec,10,(iptr)((u8 *)&g.d_0066bfd0));
    palette_fade_step((GamePalette *)&game_palette,0);
    gfx_repaint_main_windows();
    ui_blit_all_windows();
    step = 0;
    while (step < 0xb) {
      palette_fade_step((GamePalette *)&game_palette,step);
      ui_delay_ticks(1);
      step++;
    }
    palette_fade_end((GamePalette *)&game_palette);
    palette_set_nocollapse_all();
  }
  return;
}
#undef step

/* 0046f108 auto */
#define i (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl palette_set_nocollapse_all(void)

{
  iptr logpal;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  logpal = palette_get_logpalette((GamePalette *)&game_palette);
  if (logpal == 0) {
    err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_0062b640),(iptr)((u8 *)&g.d_0062b624),0xbc);
  }
  for (i = 0; i < 0x100; i++) {
    *(i8 *)(logpal + 7 + i * 4) = 4;
  }
  palette_commit_range((GamePalette *)&game_palette,10,0xec);
  return;
}
#undef i

/* 0046f440 auto */
GamePalette * __thiscall palette_get_logpalette(GamePalette *this)

{
  return this;
}

/* 0046f460 auto */
#define pixel (*(char *)(frame_ + FRAME_OFF(0)))
#define info_size (*(int *)(frame_ + FRAME_OFF(4)))
#define width2 (*(int *)(frame_ + FRAME_OFF(8)))
#define height2 (*(int *)(frame_ + FRAME_OFF(12)))
#define bit_count (*(short *)(frame_ + FRAME_OFF(18)))
#define compression (*(int *)(frame_ + FRAME_OFF(20)))
#define colors_used (*(int *)(frame_ + FRAME_OFF(36)))
#define file (*(FILE * *)(frame_ + FRAME_OFF(44)))
#define ok (*(int *)(frame_ + FRAME_OFF(48)))
#define src_index (*(int *)(frame_ + FRAME_OFF(52)))
#define i (*(int *)(frame_ + FRAME_OFF(56)))
#define row (*(int *)(frame_ + FRAME_OFF(60)))
#define col (*(int *)(frame_ + FRAME_OFF(64)))
#define run_value (*(uint *)(frame_ + FRAME_OFF(68)))
#define dst (*(char * *)(frame_ + FRAME_OFF(72)))
#define file_header (*(uint (*)[4])(frame_ + FRAME_OFF(76)))
#define code (*(uint *)(frame_ + FRAME_OFF(92)))
#define error_msg (*(char * *)(frame_ + FRAME_OFF(96)))
#define bmp_palette (*(i8 (*)[2])(frame_ + FRAME_OFF(100)))
#define bmp_palette_rest (*(i32 (*)[255])(frame_ + FRAME_OFF(102)))
int __cdecl gfx_load_bmp_640x480(iptr surface,iptr filename,int first_color,int num_colors,iptr palette)

{
  char color_base;
  size_t nread;
  iptr logpal;
  int tmp;
  i32 blue;
  i32 green;
  i32 red;
  i8 frame_[FRAME_OFF(1128)] __attribute__((aligned(8)));  /* original stack frame */
  
  error_msg = &gfx_load_bmp_no_error_str;
  ok = 0;
  file = __fsopen((char *)filename,&gfx_bmp_read_mode,0x40);
  if (file == (FILE *)0x0) {
    ok = 0;
  }
  else {
    nread = _fread(file_header,0xe,1,file);
    if (nread == 0) {
      error_msg = s_Error_reading_file_header_0062b67c;
    }
    else if ((file_header[0] & 0xffff) == 0x4d42) {
      nread = _fread(&info_size,4,1,file);
      if ((nread == 0) || (nread = _fread(&width2,info_size - 4,1,file), nread == 0)) {
        error_msg = s_Error_reading_info_header_0062b6ac;
      }
      else {
        nread = _fread(bmp_palette,0x400,1,file);
        if (nread == 0) {
          error_msg = s_Error_reading_file_palette_0062b6c8;
        }
        else if (((width2 == 0x280) && (height2 == 0x1e0)) && (bit_count == 8)) {
          ok = 1;
          if (palette != 0) {
            tmp = num_colors;
            if ((colors_used != 0) && (tmp = colors_used, num_colors <= colors_used)) {
              tmp = num_colors;
            }
            num_colors = tmp;
            if (0x100 < num_colors + first_color) {
              num_colors = 0x100 - first_color;
            }
            src_index = 0;
            for (i = first_color; i < num_colors + first_color; i++) {
              red = *(i32 *)(bmp_palette + src_index * 4);
              green = *(i32 *)(bmp_palette + src_index * 4 + 1);
              blue = *(i32 *)(bmp_palette + src_index * 4 + 2);
              tmp = i;
              logpal = palette_get_logpalette((GamePalette *)palette);
              palette_set_entry_rgb(logpal,tmp,blue,green,red);
              src_index++;
            }
            palette_commit_range((GamePalette *)palette,first_color,num_colors);
          }
          surface_create((DibSurface *)surface,width2,height2);
          color_base = (char)first_color;
          if (compression == 0) {
            do {
              row = height2 - 1;
              if ((row < 0) || (ok == 0)) goto LAB_0046fbb4;
              dst = (char *)surface_pixel_ptr((DibSurface *)surface,0,row);
              for (col = 0; height2 = row, col < width2;
                  col = col + 1) {
                code = CRT_GETC(file);
                if (code == 0xffffffff) {
                  error_msg = s_Error_reading_bitmap_image_0062b704;
                  ok = 0;
                  height2 = row;
                  break;
                }
                *dst = (char)code + color_base;
                dst++;
              }
            } while( true );
          }
          if (compression == 1) {
            row = height2 - 1;
            dst = (char *)surface_pixel_ptr((DibSurface *)surface,0,row);
            while( true ) {
              code = CRT_GETC(file);
              if (code == 0xffffffff) break;
              if (code == 0) {
                code = CRT_GETC(file);
                if (code == 0) {
                  row--;
                  dst = (char *)surface_pixel_ptr
                                                ((DibSurface *)surface,0,row);
                }
                else {
                  if (code == 1) break;
                  if (code == 2) {
                    tmp = CRT_GETC(file);
                    row -= tmp;
                    tmp = CRT_GETC(file);
                    col += tmp;
                    dst = (char *)surface_pixel_ptr
                                                  ((DibSurface *)surface,col,row);
                  }
                  else {
                    for (i = 0; i < (int)code; i++) {
                      tmp = CRT_GETC(file);
                      pixel = (char)tmp;
                      *dst = pixel + color_base;
                      dst++;
                    }
                    if ((code & 1) != 0) {
                      CRT_GETC(file);
                    }
                    col += code;
                  }
                }
              }
              else {
                run_value = CRT_GETC(file);
                for (i = 0; i < (int)code; i++) {
                  *dst = color_base + (char)run_value;
                  dst++;
                }
                col += code;
              }
            }
          }
          else if (compression == 2) {
            ok = 0;
            error_msg = s_Incompatable_compression_mode__B_0062b720;
          }
        }
        else {
          error_msg = s_Image_not_640_x_480_x_256_color_0062b6e4;
        }
      }
    }
    else {
      error_msg = s_Invalid_bitmap_file_0062b698;
    }
LAB_0046fbb4:
    _fclose(file);
    if (ok == 0) {
      MessageBoxA((HWND)0x0,error_msg,(LPCSTR)0x0,0);
    }
  }
  return ok;
}
#undef pixel
#undef info_size
#undef width2
#undef height2
#undef bit_count
#undef compression
#undef colors_used
#undef file
#undef ok
#undef src_index
#undef i
#undef row
#undef col
#undef run_value
#undef dst
#undef file_header
#undef code
#undef error_msg
#undef bmp_palette
#undef bmp_palette_rest

/* 0046fbf3 auto */
#define info_size (*(i32 *)(frame_ + FRAME_OFF(0)))
#define width2 (*(int *)(frame_ + FRAME_OFF(4)))
#define height2 (*(int *)(frame_ + FRAME_OFF(8)))
#define planes (*(i16 *)(frame_ + FRAME_OFF(12)))
#define bit_count (*(i16 *)(frame_ + FRAME_OFF(14)))
#define compression (*(i32 *)(frame_ + FRAME_OFF(16)))
#define image_size (*(i32 *)(frame_ + FRAME_OFF(20)))
#define x_ppm (*(i32 *)(frame_ + FRAME_OFF(24)))
#define y_ppm (*(i32 *)(frame_ + FRAME_OFF(28)))
#define colors_used (*(i32 *)(frame_ + FRAME_OFF(32)))
#define colors_important (*(i32 *)(frame_ + FRAME_OFF(36)))
#define file (*(FILE * *)(frame_ + FRAME_OFF(40)))
#define ok (*(int *)(frame_ + FRAME_OFF(44)))
#define dst_index (*(int *)(frame_ + FRAME_OFF(48)))
#define i (*(int *)(frame_ + FRAME_OFF(52)))
#define row (*(int *)(frame_ + FRAME_OFF(56)))
#define col (*(int *)(frame_ + FRAME_OFF(60)))
#define src (*(byte * *)(frame_ + FRAME_OFF(64)))
#define file_type (*(i16 *)(frame_ + FRAME_OFF(68)))
#define file_size (*(i32 *)(frame_ + FRAME_OFF(70)))
#define reserved1 (*(i16 *)(frame_ + FRAME_OFF(74)))
#define reserved2 (*(i16 *)(frame_ + FRAME_OFF(76)))
#define bits_offset (*(i32 *)(frame_ + FRAME_OFF(78)))
#define pixel (*(int *)(frame_ + FRAME_OFF(84)))
#define error_msg (*(char * *)(frame_ + FRAME_OFF(88)))
#define bmp_palette (*(i8 (*)[1024])(frame_ + FRAME_OFF(92)))
int __cdecl gfx_save_bmp_640x480(iptr surface,iptr filename,int first_color,int num_colors,iptr palette)

{
  iptr logpal;
  size_t nwritten;
  int tmp;
  i8 *red_ptr;
  i8 *green_ptr;
  i8 *blue_ptr;
  i8 frame_[FRAME_OFF(1120)] __attribute__((aligned(8)));  /* original stack frame */
  
  ok = 0;
  error_msg = &gfx_save_bmp_no_error_str;
  file_type = 0x4d42;
  file_size = 0x4b436;
  reserved1 = 0;
  reserved2 = 0;
  bits_offset = 0x436;
  info_size = 0x28;
  width2 = 0x280;
  height2 = 0x1e0;
  planes = 1;
  bit_count = 8;
  compression = 0;
  image_size = 0x4b000;
  x_ppm = 0;
  y_ppm = 0;
  colors_used = 0;
  colors_important = 0;
  for (i = 0; i < 0x100; i++) {
    bmp_palette[i * 4] = 0;
    bmp_palette[i * 4 + 1] = bmp_palette[i * 4];
    bmp_palette[i * 4 + 2] = bmp_palette[i * 4 + 1];
  }
  for (i = 0xec; i < 0xfa; i++) {
    bmp_palette[i * 4] = 0xff;
    bmp_palette[i * 4 + 1] = bmp_palette[i * 4];
  }
  bmp_palette[1000] = 0xff;
  bmp_palette[0x3ee] = 0x7f;
  bmp_palette[0x3f2] = 0xff;
  bmp_palette[0x3f4] = 0xff;
  bmp_palette[0x3f6] = 0xff;
  bmp_palette[0x3f9] = 0xff;
  bmp_palette[0x3fc] = 0x87;
  bmp_palette[0x3fe] = 0x87;
  bmp_palette[0x3fd] = 0x54;
  if (palette != 0) {
    dst_index = 0;
    for (i = first_color; i < num_colors + first_color; i++) {
      blue_ptr = bmp_palette + dst_index * 4;
      green_ptr = bmp_palette + dst_index * 4 + 1;
      red_ptr = bmp_palette + dst_index * 4 + 2;
      tmp = i;
      logpal = palette_get_logpalette((GamePalette *)palette);
      palette_get_entry_rgb(logpal,tmp,(iptr)red_ptr,(iptr)green_ptr,(iptr)blue_ptr);
      dst_index++;
    }
  }
  file = __fsopen((char *)filename,&gfx_bmp_write_mode,0x40);
  if (file == (FILE *)0x0) {
    ok = 0;
  }
  else {
    nwritten = _fwrite(&file_type,0xe,1,file);
    if (nwritten == 0) {
      error_msg = s_Error_writing_file_header_0062b750;
    }
    else {
      nwritten = _fwrite(&info_size,0x28,1,file);
      if (nwritten == 0) {
        error_msg = s_Error_writing_info_header_0062b76c;
      }
      else {
        nwritten = _fwrite(bmp_palette,0x400,1,file);
        if (nwritten != 0) {
          ok = 1;
          row = height2;
          do {
            row--;
            if ((row < 0) || (ok == 0)) goto LAB_0046ffb7;
            src = (byte *)surface_pixel_ptr((DibSurface *)surface,0,row);
            for (col = 0; col < width2; col++) {
              pixel = (uint)*src - first_color;
              src++;
              tmp = _fputc(pixel,file);
              if (tmp == -1) {
                error_msg = s_Error_writing_bitmap_image_0062b7a4;
                ok = 0;
                break;
              }
            }
          } while( true );
        }
        error_msg = s_Error_writing_file_palette_0062b788;
      }
    }
LAB_0046ffb7:
    _fclose(file);
    if (ok == 0) {
      MessageBoxA((HWND)0x0,error_msg,(LPCSTR)0x0,0);
    }
  }
  return ok;
}
#undef info_size
#undef width2
#undef height2
#undef planes
#undef bit_count
#undef compression
#undef image_size
#undef x_ppm
#undef y_ppm
#undef colors_used
#undef colors_important
#undef file
#undef ok
#undef dst_index
#undef i
#undef row
#undef col
#undef src
#undef file_type
#undef file_size
#undef reserved1
#undef reserved2
#undef bits_offset
#undef pixel
#undef error_msg
#undef bmp_palette

/* 00471070 auto */
/* Library Function - Single Match
    public: class CRichEditView * __thiscall CRichEditCntrItem::GetActiveView(void)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall surface_get_width(DibSurface *this)

{
  i32 width;
  
  width = surface_width(this);
  return width;
}

/* 004710a0 auto */
/* Library Function - Single Match
    public: class CRichEditView * __thiscall CRichEditCntrItem::GetActiveView(void)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall surface_get_height(DibSurface *this)

{
  i32 height;
  
  height = surface_height(this);
  return height;
}

/* 00472cf0 auto */
int __cdecl gfx_zoom_scale(int value,int zoom)

{
  int scaled;
  
  scaled = (zoom + 8) * value;
  return (int)(scaled + (scaled >> 0x1f & 7U)) >> 3;
}

/* 0047314e auto */
void __cdecl rect_pack_to_short(iptr rect,iptr short_rect)

{
  *(short *)short_rect = (short)*(i32 *)rect;
  *(short *)(short_rect + 4) = (short)*(i32 *)(rect + 8);
  *(short *)(short_rect + 2) = (short)*(i32 *)(rect + 4);
  *(short *)(short_rect + 6) = (short)*(i32 *)(rect + 0xc);
  return;
}

/* 00473190 auto */
void __cdecl rect_unpack_from_short(iptr short_rect,iptr rect)

{
  *(int *)rect = (int)*(short *)short_rect;
  *(int *)(rect + 8) = (int)*(short *)(short_rect + 4);
  *(int *)(rect + 4) = (int)*(short *)(short_rect + 2);
  *(int *)(rect + 0xc) = (int)*(short *)(short_rect + 6);
  return;
}

/* 0047df20 auto */
void __cdecl gfx_set_zoom_scale(int zoom)

{
  gfx_set_scale_ratio(zoom + 8,8);
  return;
}

/* 0047df50 auto */
void __cdecl gfx_reset_zoom_scale(void)

{
  gfx_set_scale_ratio(1,1);
  return;
}

/* 0047df80 auto */
void __cdecl rect_intersect_into(LPRECT dest,iptr rect_a,iptr rect_b)

{
  IntersectRect(dest,(RECT *)rect_a,(RECT *)rect_b);
  return;
}

/* 0049621d auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
PortraitDialog * __thiscall portrait_dlg_ctor(PortraitDialog *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  eh_state = 0;
  surface_ctor((DibSurface *)&this->style_flags);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  button_ctor((Control *)this->parley_title);
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  button_ctor((Control *)(this->accept_button_2));
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),3);
  dll_handle_init((DllHandle *)(this->portrait_dll));
  this->vtable = (u32)&PTR_FUN_0061d6c0;
  this->portrait_civ = 0;
  this->show_turn_timer = 0;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0049632a auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CCommandLineInfo::~CCommandLineInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall portrait_dlg_dtor(PortraitDlgDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->window_base = &PTR_FUN_0061d6c0;
  (*(i32 *)((char *)&eh_state + 1)) = 0;
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 004963a5 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x1d4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 004963b4 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x198)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 004963c3 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x15c)); }
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 004963d2 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x114)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004963e1 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00496402 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
i32 __thiscall portrait_dlg_create(PortraitDialog *this)

{
  wnd_create_with_surface
            ((DibSurface *)this,(iptr)((u8 *)&g.d_0062cbc8),0xc00,0,0,frame_border_width * 8 + 0x276,
             frame_border_width * 4 + frame_caption_height + 0x16e,(iptr)((u8 *)&g.d_006a8c00),(iptr)((u8 *)&g.d_006553d8));
  portrait_dlg_create_buttons((WindowObjectView *)this);
  wnd_set_caption_height((WndBase *)this->window_2,frame_caption_height);
  wnd_set_lbuttonup_handler((WndEventHandlers *)(this->event_handlers),(iptr)portrait_dlg_on_click);
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)(this->event_handlers),(iptr)portrait_dlg_on_dblclick);
  portrait_dlg_paint(this);
  wnd_repaint((SurfaceWindow *)this);
  wnd_center((WndCenterView *)this->window_2);
  return 1;
}
#undef frame_border_width
#undef frame_caption_height

/* 004964b3 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define parent_b (*(WindowObjectView * *)(frame_ + FRAME_OFF(4)))
#define parent_a (*(WindowObjectView * *)(frame_ + FRAME_OFF(8)))
#define button_rect (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __thiscall portrait_dlg_create_buttons(WindowObjectView *this)

{
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&button_rect,frame_border_width + 2,frame_border_width * 3 + frame_caption_height + frame_bevel_width + 0x14a,
          (frame_border_width * 8 + 0x276 >> 1) - 2,
          frame_border_width * 3 + frame_caption_height + 0x16e + frame_bevel_width);
  if (this == (WindowObjectView *)0x0) {
    parent_a = (WindowObjectView *)0x0;
  }
  else {
    parent_a = this + 0x12;
  }
  button_create_with_callback
            ((Control *)(this + 0x66),(iptr)parent_a,0x65,(iptr)&button_rect,0x21,(iptr)((u8 *)&g.d_0062cbcc));
  OffsetRect(&button_rect,((frame_border_width * 8 + 0x276 >> 1) + 2) - frame_border_width,0);
  if (this == (WindowObjectView *)0x0) {
    parent_b = (WindowObjectView *)0x0;
  }
  else {
    parent_b = this + 0x12;
  }
  button_create_with_callback
            ((Control *)(this + 0x57),(iptr)parent_b,100,(iptr)&button_rect,0x21,(iptr)((u8 *)&g.d_0062cbd0));
  button_set_callback((Control *)(this + 0x57),(iptr)portrait_dlg_on_button);
  button_set_callback((Control *)(this + 0x66),(iptr)portrait_dlg_on_button);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef parent_b
#undef parent_a
#undef button_rect

/* 004965ff auto */
void __thiscall portrait_dlg_run(PortraitDialog *this)

{
  ctrl_show_and_redraw((Control *)this->parley_title);
  ctrl_show_and_redraw((Control *)(this->accept_button_2));
  window_show((WindowObjectView *)this);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)this->window_2,(iptr)net_modal_idle_poll);
  }
  wnd_run_modal_loop((ModalMenuWindow *)this->window_2);
  wnd_set_modal_idle_callback((ModalMenuWindow *)this->window_2,0);
  wnd_hide((WndBase *)this->window_2);
  wnd_flush_paint();
  control_hide((Control *)this->parley_title);
  control_hide((Control *)(this->accept_button_2));
  civs[this->portrait_civ].leader_portrait = (u8)this->show_turn_status;
  return;
}

/* 004966c4 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define col (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(8)))
#define i (*(int *)(frame_ + FRAME_OFF(12)))
#define x2 (*(int *)(frame_ + FRAME_OFF(16)))
#define b (*(int *)(frame_ + FRAME_OFF(20)))
#define dst_rect (*(tagRECT *)(frame_ + FRAME_OFF(24)))
#define src_rect (*(tagRECT *)(frame_ + FRAME_OFF(40)))
#define title (*(iptr *)(frame_ + FRAME_OFF(56)))
void __thiscall portrait_dlg_paint(PortraitDialog *this)

{
  int loaded;
  i32 height;
  int tmp_a;
  int tmp_b;
  int tmp_c;
  int tmp_d;
  RECT *lprcSrc;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  title = label_string(*(i32 *)(label_string_ids + 0x4a8));
  dll_handle_load((DllHandle *)(this->portrait_dll),(iptr)((u8 *)&g.d_0062cbd8));
  loaded = surface_load_gif_resource
                    ((DibSurface *)&this->style_flags,
                     0xd3 - (uint)(leaders[civs[this->portrait_civ].tribe].female == '\0'),10,0xec,
                     (iptr)((u8 *)&g.d_006a8c00));
  if (loaded != 0) {
    dll_handle_free((DllHandle *)(this->portrait_dll));
    loaded = frame_caption_height + frame_bevel_width * -2;
    height = surface_get_width((DibSurface *)this);
    gfx_tile_fill((iptr)this,frame_border_tile,0,frame_bevel_width,height,loaded,0,frame_bevel_width);
    height = surface_get_height((DibSurface *)this);
    loaded = frame_border_width + frame_bevel_width * -2;
    x2 = frame_bevel_width;
    tmp_a = frame_caption_height - frame_bevel_width;
    for (i = 0; i < 8; i++) {
      gfx_tile_fill((iptr)this,frame_border_tile,x2,tmp_a,loaded,height,x2,tmp_a);
      x2 = x2 + frame_border_width + 0x5a;
    }
    tmp_b = frame_border_width + frame_bevel_width * -2;
    y2 = frame_bevel_width + frame_caption_height + 0x6e;
    tmp_c = surface_get_width((DibSurface *)this);
    tmp_a = frame_bevel_width;
    loaded = frame_bevel_width * -2;
    for (i = 0; i < 2; i++) {
      gfx_tile_fill((iptr)this,frame_border_tile,tmp_a,y2,tmp_c + loaded,tmp_b,tmp_a,y2);
      y2 = y2 + frame_border_width + 0x6e;
    }
    loaded = frame_border_width * 2;
    tmp_c = surface_get_width((DibSurface *)this);
    tmp_b = frame_bevel_width;
    tmp_a = frame_bevel_width * -2;
    tmp_d = surface_get_height((DibSurface *)this);
    tmp_d = tmp_d + frame_border_width * -2 - 0x24 + frame_bevel_width;
    gfx_tile_fill((iptr)this,frame_border_tile,tmp_b,tmp_d,tmp_c + tmp_a,loaded + 0x24,tmp_b,tmp_d);
    SetRect(&dst_rect,frame_border_width - frame_bevel_width,frame_caption_height - frame_bevel_width,
            frame_bevel_width * 2 + (frame_border_width - frame_bevel_width) + 0x5a,
            frame_bevel_width * 2 + (frame_caption_height - frame_bevel_width) + 0x6e);
    SetRect(&src_rect,1,1,0x5b,0x6f);
    for (i = 0; i < 3; i++) {
      for (col = 0; col < 7; col++) {
        for (b = 0; b < frame_bevel_width; b++) {
          gfx_draw_bevel_rect((iptr)this,(iptr)&dst_rect,frame_shadow_color,frame_highlight_color);
          InflateRect(&dst_rect,-1,-1);
        }
        surface_blit
                  ((DibSurface *)&this->style_flags,(iptr)this,(iptr)&src_rect,(iptr)&dst_rect);
        OffsetRect(&src_rect,0x5b,0);
        InflateRect(&dst_rect,frame_bevel_width,frame_bevel_width);
        OffsetRect(&dst_rect,frame_border_width + 0x5a,0);
      }
      OffsetRect(&src_rect,-0x27d,0x6f);
      OffsetRect(&dst_rect,(frame_border_width + 0x5a) * -7,frame_border_width + 0x6e);
    }
    lprcSrc = (RECT *)surface_get_rect((DibSurface *)this);
    CopyRect(&dst_rect,lprcSrc);
    for (b = 0; b < frame_bevel_width; b++) {
      gfx_draw_bevel_rect((iptr)this,(iptr)&dst_rect,frame_highlight_color,frame_shadow_color);
      InflateRect(&dst_rect,-1,-1);
    }
    SetRect(&dst_rect,frame_border_width - frame_bevel_width,frame_caption_height - frame_bevel_width,
            frame_bevel_width * 2 + (frame_border_width - frame_bevel_width) + 0x5a,
            frame_bevel_width * 2 + (frame_caption_height - frame_bevel_width) + 0x6e);
    for (b = 0; b < frame_bevel_width; b++) {
      gfx_draw_bevel_rect((iptr)this,(iptr)&dst_rect,0x5e,0x5e);
      InflateRect(&dst_rect,-1,-1);
    }
    tmp_a = surface_get_width((DibSurface *)this);
    tmp_b = font_text_width((GameFont *)&caption_font,title);
    loaded = frame_bevel_width;
    tmp_b = (tmp_a >> 1) - (tmp_b + 4 >> 1);
    tmp_a = frame_bevel_width + 1;
    gfx_set_text_color_index(0x12);
    surface_draw_text((DibSurface *)this,(iptr)((u8 *)&g.d_006ab190),title,tmp_b + 3,loaded + 2,5);
    gfx_set_text_color_index(0x29);
    surface_draw_text((DibSurface *)this,(iptr)((u8 *)&g.d_006ab190),title,tmp_b + 1,tmp_a,5);
    surface_draw_text((DibSurface *)this,(iptr)((u8 *)&g.d_006ab190),title,tmp_b,tmp_a,5);
  }
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef col
#undef y2
#undef i
#undef x2
#undef b
#undef dst_rect
#undef src_rect
#undef title

/* 00496c3c auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define old_rect (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define old_y (*(int *)(frame_ + FRAME_OFF(16)))
#define new_rect (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define new_y (*(int *)(frame_ + FRAME_OFF(36)))
#define old_x (*(int *)(frame_ + FRAME_OFF(40)))
#define old_sel (*(u32 *)(frame_ + FRAME_OFF(44)))
#define new_x (*(int *)(frame_ + FRAME_OFF(48)))
#define b (*(int *)(frame_ + FRAME_OFF(52)))
#define dlg (*(DibSurface * *)(frame_ + FRAME_OFF(56)))
void __cdecl portrait_dlg_on_click(int x,int y)

{
  int tmp;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  tmp = wnd_get_active_child();
  if (tmp == 0) {
    dlg = (DibSurface *)0x0;
  }
  else {
    dlg = (DibSurface *)(tmp - 0x48);
  }
  old_sel = dlg[6].bounds_bottom;
  tmp = surface_get_height(dlg);
  if (y <= tmp - 0x24 + frame_border_width * -2) {
    tmp = (y - frame_caption_height) / (frame_border_width + 0x6e);
    dlg[6].bounds_bottom =
         ((x - (frame_border_width >> 1)) / (frame_border_width + 0x5a) - tmp) + tmp * 8;
    new_x = (((int)dlg[6].bounds_bottom % 7) * (frame_border_width + 0x5a) + frame_border_width) -
               frame_bevel_width;
    new_y = (((int)dlg[6].bounds_bottom / 7) * (frame_border_width + 0x6e) + frame_caption_height) -
               frame_bevel_width;
    old_x = ((frame_border_width + 0x5a) * ((int)old_sel % 7) + frame_border_width) - frame_bevel_width;
    old_y = ((frame_border_width + 0x6e) * ((int)old_sel / 7) + frame_caption_height) - frame_bevel_width;
    SetRect(&new_rect,new_x,new_y,frame_bevel_width * 2 + new_x + 0x5a,
            frame_bevel_width * 2 + new_y + 0x6e);
    SetRect(&old_rect,old_x,old_y,frame_bevel_width * 2 + old_x + 0x5a,
            frame_bevel_width * 2 + old_y + 0x6e);
    for (b = 0; b < frame_bevel_width; b++) {
      gfx_draw_bevel_rect((iptr)dlg,(iptr)&new_rect,0x5e,0x5e);
      InflateRect(&new_rect,-1,-1);
      gfx_draw_bevel_rect((iptr)dlg,(iptr)&old_rect,frame_shadow_color,frame_highlight_color);
      InflateRect(&old_rect,-1,-1);
    }
    wnd_blit_surface(dlg);
  }
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef old_rect
#undef old_y
#undef new_rect
#undef new_y
#undef old_x
#undef old_sel
#undef new_x
#undef b
#undef dlg

/* 00496e5d auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define dlg (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl portrait_dlg_on_dblclick(i32 x,int y)

{
  int tmp;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  tmp = wnd_get_active_child();
  if (tmp == 0) {
    dlg = 0;
  }
  else {
    dlg = tmp - 0x48;
  }
  portrait_dlg_on_click(x,y);
  tmp = surface_get_height((DibSurface *)dlg);
  if (y < tmp - 0x24 + frame_border_width * -2) {
    portrait_dlg_on_button(100);
  }
  return;
}
#undef frame_border_width
#undef dlg

/* 00496ecf auto */
#define dlg (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl portrait_dlg_on_button(int button_id)

{
  iptr child;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  child = wnd_get_active_child();
  if (child == 0) {
    dlg = 0;
  }
  else {
    dlg = child - 0x48;
  }
  if (((button_id != 100) && (button_id == 0x65)) &&
     (*(i32 *)(dlg + 0x1e4) = *(i32 *)(dlg + 0x1e0),
     leaders[civs[*(int *)(dlg + 0x1dc)].tribe].female != '\0')) {
    *(int *)(dlg + 0x1e4) = *(int *)(dlg + 0x1e4) + 0x15;
  }
  wnd_end_modal_loop((ModalMenuWindow *)(dlg + 0x48));
  return;
}
#undef dlg

/* 00497c40 auto */
void __thiscall
palette_get_entry
          (GamePalette *this,iptr index,iptr red,iptr green,iptr blue)

{
  palette_get_entry_rgb((iptr)this,index,red,green,blue);
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
  i32 width;
  
  width = rect_width((iptr)this);
  return width;
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
  i32 height;
  
  height = rect_height((iptr)this);
  return height;
}

/* 004bb800 auto */
void __cdecl rect_deflate(iptr rect,int dx,int dy)

{
  rect_inflate(rect,-dx,-dy);
  return;
}

/* 004bb840 auto */
void __cdecl rect_inflate(iptr rect,int dx,int dy)

{
  InflateRect((LPRECT)rect,dx,dy);
  return;
}

/* 004ccb6a auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
#define rect (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define rect_top2 (*(int *)(frame_ + FRAME_OFF(8)))
#define rect_bottom2 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_draw_tiled_frame(iptr surface,int x,int y,int width,int height,int border)

{
  int left;
  int top;
  i32 extent;
  int offset;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  left = x - border;
  top = y - border;
  rect_set_xywh((iptr)rect,left,top,width + border * 2,height + border * 2);
  extent = rect_width((iptr)rect);
  gfx_tile_fill(surface,(iptr)((u8 *)&g.d_00647f18),left,top + 2,extent,border - 4,0,2);
  offset = rect_height((iptr)rect);
  offset -= (border - 2);
  gfx_tile_fill(surface,(iptr)((u8 *)&g.d_00647f18),left,offset + top,extent,border - 4,0,offset);
  extent = rect_height((iptr)rect);
  gfx_tile_fill(surface,(iptr)((u8 *)&g.d_00647f18),left + 2,top,border - 4,extent,2,0);
  offset = rect_width((iptr)rect);
  offset -= (border - 2);
  gfx_tile_fill(surface,(iptr)((u8 *)&g.d_00647f18),offset + left,top,border - 4,extent,offset,0);
  for (i = 0; i < 2; i++) {
    gfx_draw_bevel_rect(surface,(iptr)rect,0x25,0x12);
    rect_deflate((iptr)rect,1,1);
  }
  rect_deflate((iptr)rect,border - 4,0);
  rect_top2 = rect_top2 + border - 4;
  rect_bottom2 -= (border - 4);
  for (i = 0; i < 2; i++) {
    gfx_draw_bevel_rect(surface,(iptr)rect,0x12,0x25);
    rect_deflate((iptr)rect,1,1);
  }
  return;
}
#undef i
#undef rect
#undef rect_top2
#undef rect_bottom2

/* 004d8af0 auto */
u32 __thiscall font_get_handle(GameFont *this)

{
  return this->hfont;
}

/* 00548c78 auto */
#define clip_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define remainder (*(int *)(frame_ + FRAME_OFF(20)))
#define error_acc (*(int *)(frame_ + FRAME_OFF(24)))
#define i (*(int *)(frame_ + FRAME_OFF(28)))
#define orig_slots (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl
sprite_draw_spaced_row(iptr surface,iptr sprite,int x,i32 y,int count,int slots,
            int spacing,i32 item_width,int spread_extra)

{
  int limit;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  u32 pargs_[4] = {(u32)(uptr)slots, (u32)(uptr)spacing, (u32)(uptr)item_width, (u32)(uptr)spread_extra};  /* the arguments, contiguous as on the original stack */
#define slots (*(int *)&pargs_[0])
#define spacing (*(int *)&pargs_[1])
#define item_width (*(i32 *)&pargs_[2])
#define spread_extra (*(int *)&pargs_[3])
  
  error_acc = 0;
  orig_slots = slots;
  spacing = ui_calc_item_spacing(slots,spacing,item_width,(iptr)&slots,(iptr)&remainder);
  if (((orig_slots != 0) && (slots != orig_slots)) && (count != orig_slots)) {
    count = (slots * count) / orig_slots;
  }
  i = 0;
  while( true ) {
    limit = slots;
    if (count <= slots) {
      limit = count;
    }
    if (limit <= i) break;
    sprite_draw((Sprite *)sprite,(iptr)clip_rect,surface,x,y);
    x += spacing;
    if ((spread_extra != 0) && (1 < slots)) {
      for (error_acc = error_acc + remainder; slots - 1 <= error_acc;
          error_acc = error_acc - (slots - 1)) {
        x++;
      }
    }
    i++;
  }
  return;
}
#undef clip_rect
#undef remainder
#undef error_acc
#undef i
#undef orig_slots
#undef slots
#undef spacing
#undef item_width
#undef spread_extra

/* 0054a874 auto */
#define bit (*(i32 *)(frame_ + FRAME_OFF(0)))
uint __cdecl bits_nth_set(int n,uint mask)

{
  bool more;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  bit = 0;
  do {
    if (bit == 0) {
      bit = 1;
    }
    else {
      bit = bit << 1;
    }
    for (; (mask & bit) == 0; bit = bit << 1) {
    }
    more = n != 0;
    n--;
  } while (more);
  return bit;
}
#undef bit

/* 0054a8d3 auto */
#define index (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl bits_index_of(uint bit,uint mask)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  index = 0;
  while (bit = bit >> 1, bit != 0) {
    if ((mask & bit) != 0) {
      index++;
    }
  }
  return index;
}
#undef index

/* 0055a930 auto */
void __cdecl
gfx_copy_rect_same_pos(iptr src,iptr dst,i32 x,i32 y,i32 width,
            i32 height)

{
  gfx_copy_rect_xywh(src,dst,x,y,x,y,width,height);
  return;
}

/* 005683c5 auto */
#define row (*(uint *)(frame_ + FRAME_OFF(4)))
#define col (*(uint *)(frame_ + FRAME_OFF(12)))
#define remaining (*(int *)(frame_ + FRAME_OFF(20)))
#define area2 (*(tagRECT *)(frame_ + FRAME_OFF(32)))
#define cell_rect (*(tagRECT *)(frame_ + FRAME_OFF(48)))
#define cells (*(LPVOID *)(frame_ + FRAME_OFF(64)))
i32 __cdecl gfx_dissolve_blit(iptr surface,iptr rect,uint cell_size,int mode)

{
  int lo;
  int pick;
  uint cols;
  uint rows;
  HGLOBAL mem;
  i32 result;
  int cell_x;
  int cell_y;
  int cell_right;
  int right_edge;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (rect == 0) {
    lo = surface_get_height((DibSurface *)surface);
    pick = surface_get_width((DibSurface *)surface);
    SetRect(&area2,0,0,pick,lo);
  }
  else {
    CopyRect(&area2,(RECT *)rect);
  }
  lo = rect_width((iptr)&area2);
  cols = lo / (int)cell_size;
  lo = rect_height((iptr)&area2);
  rows = lo / (int)cell_size;
  remaining = rows * cols;
  mem = GlobalAlloc(0x40,remaining * 8);
  cells = GlobalLock(mem);
  if (cells == (LPVOID)0x0) {
    result = 0;
  }
  else {
    switch(mode) {
    case 1:
      for (col = 0; col < cols; col++) {
        for (row = 0; row < rows; row++) {
          win_flush_pending_msgs();
          *(uint *)((int)cells + (col * rows + row) * 8) =
               ((cols - col) - 1) * cell_size;
          *(uint *)((int)cells + (col * rows + row) * 8 + 4) = row * cell_size;
        }
      }
      break;
    case 2:
    case 5:
      for (col = 0; col < cols; col++) {
        for (row = 0; row < rows; row++) {
          win_flush_pending_msgs();
          *(uint *)((int)cells + (col * rows + row) * 8) = col * cell_size;
          *(uint *)((int)cells + (col * rows + row) * 8 + 4) = row * cell_size;
        }
      }
      break;
    case 3:
      for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
          win_flush_pending_msgs();
          *(uint *)((int)cells + (row * cols + col) * 8) = col * cell_size;
          *(uint *)((int)cells + (row * cols + col) * 8 + 4) = row * cell_size;
        }
      }
      break;
    case 4:
      for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
          win_flush_pending_msgs();
          *(uint *)((int)cells + (row * cols + col) * 8) = col * cell_size;
          *(uint *)((int)cells + (row * cols + col) * 8 + 4) =
               ((rows - row) - 1) * cell_size;
        }
      }
    }
    if (mode == 5) {
      while (remaining != 0) {
        win_flush_pending_msgs();
        pick = rand_range(0,remaining - 1);
        cell_x = *(int *)((int)cells + pick * 8) + area2.left;
        cell_y = *(int *)((int)cells + pick * 8 + 4) + area2.top;
        lo = cell_size + cell_y;
        if (area2.bottom - 1 <= lo) {
          lo = area2.bottom - 1;
        }
        right_edge = cell_size + cell_x;
        cell_right = area2.right - 1;
        if (right_edge <= area2.right - 1) {
          cell_right = right_edge;
        }
        SetRect(&cell_rect,cell_x,cell_y,cell_right,lo);
        wnd_blit_surface_rect((DibSurface *)surface,(iptr)&cell_rect);
        remaining--;
        *(i32 *)((int)cells + pick * 8) = *(i32 *)((int)cells + remaining * 8);
        *(i32 *)((int)cells + pick * 8 + 4) =
             *(i32 *)((int)cells + remaining * 8 + 4);
      }
    }
    else {
      while (remaining != 0) {
        win_flush_pending_msgs();
        lo = (remaining - 1) - (rows * 0x14) / cell_size;
        if (lo < 1) {
          lo = 0;
        }
        pick = rand_range(lo,remaining - 1);
        cell_x = *(int *)((int)cells + pick * 8) + area2.left;
        cell_y = *(int *)((int)cells + pick * 8 + 4) + area2.top;
        lo = cell_size + cell_y;
        if (area2.bottom - 1 <= lo) {
          lo = area2.bottom - 1;
        }
        right_edge = cell_size + cell_x;
        cell_right = area2.right - 1;
        if (right_edge <= area2.right - 1) {
          cell_right = right_edge;
        }
        SetRect(&cell_rect,cell_x,cell_y,cell_right,lo);
        wnd_blit_surface_rect((DibSurface *)surface,(iptr)&cell_rect);
        remaining--;
        *(i32 *)((int)cells + pick * 8) = *(i32 *)((int)cells + remaining * 8);
        *(i32 *)((int)cells + pick * 8 + 4) =
             *(i32 *)((int)cells + remaining * 8 + 4);
      }
    }
    mem = GlobalHandle(cells);
    GlobalUnlock(mem);
    mem = GlobalHandle(cells);
    GlobalFree(mem);
    result = 1;
  }
  return result;
}
#undef row
#undef col
#undef remaining
#undef area2
#undef cell_rect
#undef cells

/* 0056b90b auto */
#define font_size (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl gfx_select_zoom_font(i32 zoom)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  font_size = gfx_zoom_scale(0x20,zoom);
  font_size = font_size / 3;
  if (font_size == 10) {
    font_size = 0xb;
  }
  if (font_size != map_label_font_size) {
    font_set((GameFont *)&map_label_font,1,font_size);
    map_label_font_size = font_size;
  }
  return;
}
#undef font_size

/* 0056baff auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define abs_dx (*(uint *)(frame_ + FRAME_OFF(4)))
#define clip_fortress (*(i8 (*)[16])(frame_ + FRAME_OFF(8)))
#define clip_fortify (*(i8 (*)[16])(frame_ + FRAME_OFF(24)))
#define clip_unit (*(i8 (*)[16])(frame_ + FRAME_OFF(40)))
#define clip_silhouette (*(i8 (*)[16])(frame_ + FRAME_OFF(56)))
#define clip_shield (*(i8 (*)[16])(frame_ + FRAME_OFF(72)))
#define clip_shield_shadow (*(i8 (*)[16])(frame_ + FRAME_OFF(88)))
#define clip_stack (*(i8 (*)[16])(frame_ + FRAME_OFF(104)))
#define clip_stack_shadow (*(i8 (*)[16])(frame_ + FRAME_OFF(120)))
#define order (*(uptr *)(frame_ + FRAME_OFF(136)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(140)))
#define shield_x (*(int *)(frame_ + FRAME_OFF(144)))
#define stack_dy (*(int *)(frame_ + FRAME_OFF(148)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(152)))
#define stack_dx (*(uint *)(frame_ + FRAME_OFF(156)))
#define shield_height (*(iptr *)(frame_ + FRAME_OFF(160)))
#define silhouette (*(uint *)(frame_ + FRAME_OFF(164)))
#define dmg (*(uint *)(frame_ + FRAME_OFF(168)))
#define shield_rect (*(int *)(frame_ + FRAME_OFF(172)))
#define shield_top (*(int *)(frame_ + FRAME_OFF(176)))
#define shield_bottom (*(int *)(frame_ + FRAME_OFF(184)))
#define band_rect (*(i32 *)(frame_ + FRAME_OFF(188)))
#define band_top (*(i32 *)(frame_ + FRAME_OFF(192)))
#define band_right (*(int *)(frame_ + FRAME_OFF(196)))
#define band_bottom (*(i32 *)(frame_ + FRAME_OFF(200)))
#define sprite_type (*(uint *)(frame_ + FRAME_OFF(204)))
#define unit_type (*(uint *)(frame_ + FRAME_OFF(208)))
#define shield_width (*(iptr *)(frame_ + FRAME_OFF(212)))
#define max_hp (*(int *)(frame_ + FRAME_OFF(216)))
#define bar_width (*(int *)(frame_ + FRAME_OFF(220)))
#define color_mid (*(i32 *)(frame_ + FRAME_OFF(224)))
#define hp_color (*(i32 *)(frame_ + FRAME_OFF(228)))
#define color_primary (*(i32 *)(frame_ + FRAME_OFF(232)))
#define shield_y (*(int *)(frame_ + FRAME_OFF(236)))
#define order_text (*(u8 (*)[80])(frame_ + FRAME_OFF(240)))
#define hp_width (*(int *)(frame_ + FRAME_OFF(320)))
#define side (*(int *)(frame_ + FRAME_OFF(324)))
#define order_char (*(u8 *)(frame_ + FRAME_OFF(328)))
#define hp_rect (*(i32 *)(frame_ + FRAME_OFF(332)))
#define hp_top (*(i32 *)(frame_ + FRAME_OFF(336)))
#define hp_right (*(int *)(frame_ + FRAME_OFF(340)))
#define hp_bottom (*(i32 *)(frame_ + FRAME_OFF(344)))
void __cdecl
gfx_draw_unit(iptr surface,iptr unit,uint draw_flags,int px,int py,int zoom,int no_fortress)

{
  int tmp;
  iptr scaled;
  int text_y;
  i32 value;
  i8 frame_[FRAME_OFF(352)] __attribute__((aligned(8)));  /* original stack frame */
  
  order_char = '\0';
  gfx_set_zoom_scale(zoom);
  unit2 = unit;
  if (((draw_flags & 2) != 0) && (unit2 = unit_stack_pick_display_unit(unit), unit2 < 0))
  goto LAB_0056c5e8;
  civ = (iptr)units[unit2].owner;
  unit_type = (uint)units[unit2].type;
  sprite_type = unit_type;
  if ((unit_type == 0x2e) && (civ == 0)) {
    sprite_type = 0x3e;
  }
  color_primary = civ_color_primary(civ);
  color_mid = civ_color_mid(civ);
  shield_x = gfx_zoom_scale(*(i32 *)(&unit_shield_x_offsets + sprite_type * 4),zoom);
  shield_x = px + shield_x;
  shield_y = gfx_zoom_scale(*(i32 *)(&unit_shield_y_offsets + sprite_type * 4),zoom);
  shield_y = py + shield_y;
  shield_width = gfx_zoom_scale(0xc,zoom);
  shield_height = gfx_zoom_scale(0x14,zoom);
  side = 1;
  if (*(int *)(&unit_shield_x_offsets + sprite_type * 4) < 0x20) {
    side = -1;
  }
  if (((draw_flags & 1) != 0) &&
     ((-1 < units[unit2].prev_in_stack || (-1 < units[unit2].next_in_stack)))) {
    tmp = gfx_zoom_scale(4,zoom);
    stack_dx = tmp * side;
    stack_dy = 0;
    rect_set_xywh((iptr)&shield_rect,stack_dx + shield_x,shield_y,shield_width,shield_height);
    if ((int)stack_dx < 1) {
      abs_dx = ~stack_dx + 1;
    }
    else {
      abs_dx = stack_dx;
    }
    if (2 < (int)abs_dx) {
      sprite_draw
                ((Sprite *)&unit_shield_sprite,(iptr)clip_stack_shadow,surface,
                 side + stack_dx + shield_x,stack_dy + shield_y + 1);
      rect_offset((iptr)&shield_rect,side,1);
      surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x106,0xf);
      surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x105,0xf);
      rect_offset((iptr)&shield_rect,-side,0xffffffff);
    }
    sprite_draw
              ((Sprite *)&unit_shield_sprite,(iptr)clip_stack,surface,stack_dx + shield_x,
               stack_dy + shield_y);
    surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x106,color_mid);
    surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x105,color_mid);
  }
  rect_set_xywh((iptr)&shield_rect,shield_x,shield_y,shield_width,shield_height);
  sprite_draw
            ((Sprite *)&unit_shield_sprite,(iptr)clip_shield_shadow,surface,side + shield_x,shield_y + 1
            );
  rect_offset((iptr)&shield_rect,side,1);
  surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x106,0x10);
  surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x105,0x10);
  rect_offset((iptr)&shield_rect,-side,0xffffffff);
  sprite_draw
            ((Sprite *)&unit_shield_sprite,(iptr)clip_shield,surface,shield_x,shield_y);
  surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x106,color_primary);
  surface_replace_color((DibSurface *)surface,(iptr)&shield_rect,0x105,color_mid);
  scaled = gfx_zoom_scale(2,zoom);
  rect_set_xywh((iptr)&band_rect,shield_x,shield_y,shield_width,scaled);
  gfx_fill_rect(surface,(iptr)&band_rect,10);
  tmp = rect_height((iptr)&band_rect);
  shield_top += tmp;
  scaled = gfx_zoom_scale(3,zoom);
  rect_set_xywh((iptr)&hp_rect,shield_x,shield_top,shield_width,scaled);
  tmp = rect_height((iptr)&hp_rect);
  shield_top += tmp;
  scaled = gfx_zoom_scale(2,zoom);
  rect_set_xywh((iptr)&band_rect,shield_x,shield_top,shield_width,scaled);
  gfx_fill_rect(surface,(iptr)&band_rect,10);
  tmp = rect_height((iptr)&band_rect);
  shield_top += tmp;
  bar_width = rect_width((iptr)&hp_rect);
  max_hp = (int)(char)unit_types[units[unit2].type].hit_points;
  dmg = (uint)units[unit2].damage;
  if (max_hp == 0) {
    max_hp = 10;
  }
  if ((game.rules & 0x10) == 0) {
    dmg = 0;
  }
  if ((draw_flags & 4) == 0) {
    dmg = 0;
  }
  if (zoom < -3) {
    dmg = 0;
  }
  hp_width = (int)((max_hp - dmg) * bar_width) / max_hp;
  if ((int)dmg < max_hp / 3) {
    hp_color = 0x2a;
  }
  else if ((int)dmg < (max_hp * 2) / 3) {
    hp_color = 0x7a;
  }
  else {
    hp_color = 0x6a;
  }
  if (bar_width != hp_width) {
    gfx_fill_rect(surface,(iptr)&hp_rect,10);
  }
  if (hp_width != 0) {
    band_rect = hp_rect;
    band_top = hp_top;
    band_bottom = hp_bottom;
    band_right = hp_right - (bar_width - hp_width);
    gfx_fill_rect(surface,(iptr)&band_rect,hp_color);
  }
  order = (int)units[unit2].orders & 0xf;
  if (units[unit2].orders == 16) {
    order = 0xffffffff;
  }
  if ((int)order < 1) {
LAB_0056c269:
    order_char = '-';
    if (((int)(short)units[unit2].flags & 0x8000U) != 0) {
      order_char = '*';
    }
  }
  else if ((int)order < 0xb) {
    order_char = order_names[order].key;
  }
  else {
    if (order != 0xb) goto LAB_0056c269;
    if ((game.reveal_map == '\0') ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        order_char = '-';
      }
      else {
        order_char = order_names[0xb].key;
      }
    }
    else {
      order_char = units[unit2].ai_task;
    }
  }
  if (order_char != '\0') {
    order_text[0] = order_char;
    order_text[1] = 0;
    tmp = gfx_zoom_scale(3,zoom);
    shield_bottom -= tmp;
    tmp = crt_toupper((int)(char)order_char);
    if (tmp == 0x4d) {
      tmp = gfx_zoom_scale(1,zoom);
      shield_top -= tmp;
      tmp = gfx_zoom_scale(1,zoom);
      shield_bottom -= tmp;
    }
    gfx_select_zoom_font(zoom);
    gfx_set_text_color_index(10);
    if (((int)(short)units[unit2].flags & 0x8000U) != 0) {
      gfx_set_text_color_index(0x1d);
    }
    value = 0;
    tmp = rect_height((iptr)&shield_rect);
    text_y = shield_top + tmp / 2;
    tmp = rect_width((iptr)&shield_rect);
    surface_draw_text
              ((DibSurface *)surface,(iptr)((u8 *)&g.d_006ac090),(iptr)order_text,shield_rect + tmp / 2,text_y,value);
  }
  silhouette = (uint)(units[unit2].orders == 3);
  if ((((unit_types[units[unit2].type].domain == 1) &&
       (tmp = map_in_bounds((int)units[unit2].x,(int)units[unit2].y), tmp != 0)) &&
      (tmp = tile_airbase_owner((int)units[unit2].x,(int)units[unit2].y), -1 < tmp)) &&
     (((game.active_unit != unit2 || (moving_units_mode != 1)) || (unit_blink_active == '\0')))) {
    silhouette = 1;
  }
  if (silhouette == 0) {
    sprite_draw
              ((Sprite *)(&unit_sprites + sprite_type * 0x3c),(iptr)clip_unit,surface,px,
               py);
  }
  else {
    sprite_draw_silhouette
              ((Sprite *)(&unit_sprites + sprite_type * 0x3c),(iptr)clip_silhouette,surface,px,
               py,0x1a);
  }
  if (units[unit2].orders == 2) {
    sprite_draw
              ((Sprite *)&fortify_overlay_sprites,(iptr)clip_fortify,surface,px,py);
  }
  tmp = map_in_bounds((int)units[unit2].x,(int)units[unit2].y);
  if (((tmp != 0) &&
      (value = tile_improvements((int)units[unit2].x,(int)units[unit2].y),
      ((byte)value & 0x42) == 0x40)) && (no_fortress == 0)) {
    sprite_draw
              ((Sprite *)&fortress_sprite,(iptr)clip_fortress,surface,px,py);
  }
LAB_0056c5e8:
  gfx_reset_zoom_scale();
  return;
}
#undef moving_units_mode
#undef unit_blink_active
#undef abs_dx
#undef clip_fortress
#undef clip_fortify
#undef clip_unit
#undef clip_silhouette
#undef clip_shield
#undef clip_shield_shadow
#undef clip_stack
#undef clip_stack_shadow
#undef order
#undef civ
#undef shield_x
#undef stack_dy
#undef unit2
#undef stack_dx
#undef shield_height
#undef silhouette
#undef dmg
#undef shield_rect
#undef shield_top
#undef shield_bottom
#undef band_rect
#undef band_top
#undef band_right
#undef band_bottom
#undef sprite_type
#undef unit_type
#undef shield_width
#undef max_hp
#undef bar_width
#undef color_mid
#undef hp_color
#undef color_primary
#undef shield_y
#undef order_text
#undef hp_width
#undef side
#undef order_char
#undef hp_rect
#undef hp_top
#undef hp_right
#undef hp_bottom

/* 0056c5fc auto */
void __cdecl
gfx_copy_rect_clipped(iptr src,iptr dst,int src_x,int src_y,int src_origin_x,int src_origin_y,int dst_x,
            int dst_y,int dst_origin_x,int dst_origin_y,int width,int height)

{
  src_x -= src_origin_x;
  src_y -= src_origin_y;
  dst_x -= dst_origin_x;
  dst_y -= dst_origin_y;
  if (src_x < 0) {
    dst_x -= src_x;
    width += src_x;
    src_x = 0;
  }
  if (dst_x < 0) {
    src_x -= dst_x;
    width += dst_x;
    dst_x = 0;
  }
  if (src_y < 0) {
    dst_y -= src_y;
    height += src_y;
    src_y = 0;
  }
  if (dst_y < 0) {
    src_y -= dst_y;
    height += dst_y;
    dst_y = 0;
  }
  if ((0 < width) && (0 < height)) {
    gfx_copy_rect_xywh(src,dst,src_origin_x + src_x,src_origin_y + src_y,dst_origin_x + dst_x,
                       dst_origin_y + dst_y,width,height);
  }
  return;
}

/* 0056d289 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define clip_disorder (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define clip_flag (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define clip_city (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(52)))
#define style2 (*(int *)(frame_ + FRAME_OFF(56)))
#define height2 (*(int *)(frame_ + FRAME_OFF(60)))
#define width2 (*(iptr *)(frame_ + FRAME_OFF(64)))
#define size_idx (*(int *)(frame_ + FRAME_OFF(68)))
#define color_mid (*(i32 *)(frame_ + FRAME_OFF(72)))
#define flag_y (*(int *)(frame_ + FRAME_OFF(76)))
#define color_primary (*(i32 *)(frame_ + FRAME_OFF(80)))
#define scale_factor (*(int *)(frame_ + FRAME_OFF(84)))
#define flag_x (*(int *)(frame_ + FRAME_OFF(88)))
#define pad (*(int *)(frame_ + FRAME_OFF(92)))
#define template_text (*(i8 (*)[8])(frame_ + FRAME_OFF(96)))
#define occupied (*(uint *)(frame_ + FRAME_OFF(104)))
#define walled (*(int *)(frame_ + FRAME_OFF(108)))
#define size_text (*(char (*)[8])(frame_ + FRAME_OFF(112)))
#define label_rect (*(int *)(frame_ + FRAME_OFF(120)))
#define label_top (*(iptr *)(frame_ + FRAME_OFF(124)))
#define city_size (*(int *)(frame_ + FRAME_OFF(136)))
void __cdecl
gfx_draw_city(iptr surface,iptr city,uint draw_flags,int px,int py,int zoom)

{
  char shown_size;
  short style_id;
  int tmp;
  size_t text_len;
  int box_dx;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_set_zoom_scale(zoom);
  width2 = gfx_zoom_scale(0x40,zoom);
  height2 = gfx_zoom_scale(0x30,zoom);
  civ = (iptr)cities[city].owner;
  rect_set_xywh((iptr)&label_rect,px,py,width2,height2);
  gfx_set_draw_target(surface);
  color_mid = civ_color_mid(civ);
  color_primary = civ_color_primary(civ);
  tmp = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
  occupied = (uint)(-1 < tmp);
  tmp = city_has_improvement(city,8);
  if ((tmp == 0) && (tmp = civ_has_wonder(civ,6), tmp == 0)) {
    walled = 0;
  }
  else {
    walled = 1;
  }
  scale_factor = (-1 < zoom) + 1;
  style_id = leaders[civs[civ].tribe].city_style;
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
    style_id = civ_names[civ].city_style;
  }
  style2 = (int)style_id;
  tmp = civ_has_advance(civ,0x25);
  if (tmp != 0) {
    style2 = 4;
  }
  tmp = civ_has_advance(civ,5);
  if ((tmp != 0) && (tmp = civ_has_advance(civ,0x18), tmp != 0)) {
    style2 = 5;
  }
  if ((((human_civ == civ) || (game.reveal_map != '\0')) ||
      (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) || ((draw_flags & 0x1000) != 0))
  {
    shown_size = cities[city].size;
  }
  else {
    shown_size = *(char *)&cities[city].revealed_size[human_civ];
  }
  city_size = (int)shown_size;
  if (style2 < 4) {
    if (city_size < 4) {
      size_idx = 0;
    }
    else if (city_size < 6) {
      size_idx = 1;
    }
    else if (city_size < 8) {
      size_idx = 2;
    }
    else {
      size_idx = 3;
    }
  }
  else if (style2 == 4) {
    if (city_size < 5) {
      size_idx = 0;
    }
    else if (city_size < 8) {
      size_idx = 1;
    }
    else if (city_size < 0xb) {
      size_idx = 2;
    }
    else {
      size_idx = 3;
    }
  }
  else if (city_size < 5) {
    size_idx = 0;
  }
  else if (city_size < 0xb) {
    size_idx = 1;
  }
  else if (city_size < 0x13) {
    size_idx = 2;
  }
  else {
    size_idx = 3;
  }
  tmp = city_has_improvement(city,1);
  if ((tmp != 0) &&
     (((human_civ == civ ||
       ((game.difficulty < 3 && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0))))
      && (size_idx < 3)))) {
    size_idx++;
  }
  sprite_draw
            ((Sprite *)(&city_sprites + size_idx * 0x78 + walled * 0x3c + style2 * 0x1e0)
             ,(iptr)clip_city,surface,px,py);
  tmp = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
  if ((-1 < tmp) && ((draw_flags & 2) == 0)) {
    flag_x = gfx_zoom_scale(*(i32 *)
                                   (&city_flag_x_offsets + style2 * 0x20 + walled * 4 + size_idx * 8),
                                  zoom);
    flag_x = px + flag_x;
    flag_y = gfx_zoom_scale(*(i32 *)
                                   (&city_flag_y_offsets + style2 * 0x20 + walled * 4 + size_idx * 8),
                                  zoom);
    flag_y = py + flag_y;
    sprite_draw
              ((Sprite *)(&civ_flag_sprites + civ * 0x78),(iptr)clip_flag,surface,flag_x,
               flag_y);
  }
  if ((draw_flags & 1) == 0) {
    if ((cities[city].flags & 1) == 0) {
      gfx_select_zoom_font(zoom);
      text_set_font((iptr)((u8 *)&g.d_006ac090));
      text_set_surface(surface);
      __itoa(city_size,size_text,10);
      width2 = font_text_width((GameFont *)&map_label_font,(iptr)size_text);
      height2 = font_cached_height((GameFont *)&map_label_font);
      crt_strcpy(template_text,&city_size_digit_str);
      text_len = _strlen(size_text);
      if (1 < text_len) {
        crt_strcat(template_text,&city_size_digit2_str);
      }
      pad = font_text_width((GameFont *)&map_label_font,(iptr)template_text);
      pad -= width2;
      if (pad < 0) {
        pad = 0;
      }
      width2 = width2 + pad + 5;
      height2 += 2;
      rect_set_xywh((iptr)&label_rect,0,0,width2,height2);
      tmp = gfx_zoom_scale(*(i32 *)
                                  (&city_label_y_offsets + style2 * 0x20 + walled * 4 + size_idx * 8),
                                 zoom);
      tmp = py + tmp;
      box_dx = gfx_zoom_scale(*(i32 *)
                                  (&city_size_box_x_offsets + style2 * 0x20 + walled * 4 + size_idx * 8),
                                 zoom);
      rect_offset((iptr)&label_rect,px + box_dx,tmp);
      gfx_draw_rect_frame(surface,(iptr)&label_rect,10);
      rect_deflate((iptr)&label_rect,1,1);
      gfx_fill_rect(surface,(iptr)&label_rect,color_primary);
      text_set_colors(10,10,1,0);
      gfx_draw_text((iptr)size_text,label_rect + (pad >> 1) + 1,label_top);
    }
    else {
      sprite_draw
                ((Sprite *)&city_disorder_icon_sprite,(iptr)clip_disorder,surface,px,py);
      surface_replace_color((DibSurface *)surface,(iptr)&label_rect,0x106,color_primary);
    }
  }
  gfx_reset_zoom_scale();
  return;
}
#undef human_civ
#undef scenario_flags
#undef clip_disorder
#undef clip_flag
#undef clip_city
#undef civ
#undef style2
#undef height2
#undef width2
#undef size_idx
#undef color_mid
#undef flag_y
#undef color_primary
#undef scale_factor
#undef flag_x
#undef pad
#undef template_text
#undef occupied
#undef walled
#undef size_text
#undef label_rect
#undef label_top
#undef city_size

/* 0056e1c0 auto */
int __cdecl gfx_zoom_scale_round(int value,int zoom)

{
  int scaled;
  
  scaled = (zoom + 8) * value + 4;
  return (int)(scaled + (scaled >> 0x1f & 7U)) >> 3;
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
#define dy (*(int *)(frame_ + FRAME_OFF(4)))
#define dx (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl sprite_sheet_draw_shield_marks(int unit_type,int x,int y)

{
  int left;
  int top;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  left = x - 1;
  top = y - 1;
  for (dx = 0; dx < 0x40; dx++) {
    surface_set_pixel((DibSurface *)&sprite_sheet_surface,left + dx + 1,top,8);
  }
  surface_set_pixel
            ((DibSurface *)&sprite_sheet_surface,left + *(int *)(&unit_shield_x_offsets + unit_type * 4) + 1,top,
             4);
  for (dy = 0; dy < 0x30; dy++) {
    surface_set_pixel((DibSurface *)&sprite_sheet_surface,left,dy + top + 1,8);
  }
  surface_set_pixel
            ((DibSurface *)&sprite_sheet_surface,left,*(int *)(&unit_shield_y_offsets + unit_type * 4) + top + 1,
             4);
  return;
}
#undef dy
#undef dx

/* 0056fce4 auto */
#define clip_unit (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define clip_backdrop (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define row (*(int *)(frame_ + FRAME_OFF(32)))
#define col (*(int *)(frame_ + FRAME_OFF(36)))
#define unit_type (*(int *)(frame_ + FRAME_OFF(40)))
#define start_x2 (*(int *)(frame_ + FRAME_OFF(44)))
#define y2 (*(int *)(frame_ + FRAME_OFF(48)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(52)))
#define saved_dir (*(char (*)[260])(frame_ + FRAME_OFF(1128)))
#define x2 (*(int *)(frame_ + FRAME_OFF(1388)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1392)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1396)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(1400)))
void __cdecl sprite_sheet_save_units(void)

{
  byte key_color;
  int result;
  iptr height;
  i32 width;
  uint fill_color;
  i8 frame_[FRAME_OFF(1408)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  __getcwd(saved_dir,0x104);
  __chdir(&scenario_dir_path);
  result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_00634010),10,0xc0,(iptr)&palette);
  if (result == 0) {
    result = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_0063401c),10,0xc0,(iptr)&palette);
    if (result == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_00634028),10,0xc0,(iptr)&palette);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  start_x2 = 1;
  row = 0;
  col = 0;
  y2 = 1;
  x2 = 1;
  for (unit_type = 0; unit_type < 0x3f; unit_type++) {
    key_color = sprite_get_key_color((Sprite *)(&unit_sprites + unit_type * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
    width = sprite_width((Sprite *)(&unit_sprites + unit_type * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_backdrop,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
    sprite_draw
              ((Sprite *)(&unit_sprites + unit_type * 0x3c),(iptr)clip_unit,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    sprite_sheet_draw_shield_marks(unit_type,x2,y2);
    col++;
    x2 += 0x41;
    if (8 < col) {
      col = 0;
      row++;
      y2 += 0x31;
      x2 = start_x2;
    }
  }
  __chdir(&scenario_dir_path);
  result = file_exists((iptr)((u8 *)&g.d_00634034));
  if (result != 0) {
    result = crt_remove(s_UNITS_BMP_00634040);
    if (result != 0) goto LAB_0056ff8c;
  }
  gfx_save_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_0063404c),10,0xc0,(iptr)&palette);
LAB_0056ff8c:
  __chdir(saved_dir);
  surface_release((DibSurface *)&sprite_sheet_surface);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0056ffb6 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef clip_unit
#undef clip_backdrop
#undef row
#undef col
#undef unit_type
#undef start_x2
#undef y2
#undef palette
#undef saved_dir
#undef x2
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 0056ffda auto */
#define clip_airbase_occ (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define clip_airbase_occ_bg (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define clip_airbase (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define clip_airbase_bg (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define clip_fortress (*(i8 (*)[16])(frame_ + FRAME_OFF(68)))
#define clip_fortress_bg (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define clip_fortify (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define clip_fortify_bg (*(i8 (*)[16])(frame_ + FRAME_OFF(116)))
#define clip_flag_dark (*(i8 (*)[16])(frame_ + FRAME_OFF(132)))
#define clip_flag (*(i8 (*)[16])(frame_ + FRAME_OFF(148)))
#define clip_walled (*(i8 (*)[16])(frame_ + FRAME_OFF(164)))
#define clip_walled_bg (*(i8 (*)[16])(frame_ + FRAME_OFF(180)))
#define clip_city (*(i8 (*)[16])(frame_ + FRAME_OFF(196)))
#define clip_city_bg (*(i8 (*)[16])(frame_ + FRAME_OFF(212)))
#define style2 (*(int *)(frame_ + FRAME_OFF(228)))
#define civ (*(int *)(frame_ + FRAME_OFF(232)))
#define cell_x (*(int *)(frame_ + FRAME_OFF(236)))
#define flag_dark_y (*(i32 *)(frame_ + FRAME_OFF(240)))
#define flag_y (*(i32 *)(frame_ + FRAME_OFF(244)))
#define walled_x (*(int *)(frame_ + FRAME_OFF(248)))
#define y2 (*(int *)(frame_ + FRAME_OFF(252)))
#define x2 (*(int *)(frame_ + FRAME_OFF(256)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(260)))
#define saved_dir (*(char (*)[260])(frame_ + FRAME_OFF(1336)))
#define size_idx (*(int *)(frame_ + FRAME_OFF(1596)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1600)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1604)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(1608)))
void __cdecl sprite_sheet_save_cities(void)

{
  byte key_color;
  int result;
  iptr height;
  i32 width;
  uint fill_color;
  i8 frame_[FRAME_OFF(1616)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  __getcwd(saved_dir,0x104);
  __chdir(&scenario_dir_path);
  result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_00634058),10,0xc0,(iptr)&palette);
  if (result == 0) {
    result = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_00634064),10,0xc0,(iptr)&palette);
    if (result == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_00634070),10,0xc0,(iptr)&palette);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  x2 = 1;
  y2 = 0x27;
  walled_x = 0x14e;
  for (style2 = 0; style2 < 6; style2++) {
    for (size_idx = 0; size_idx < 4; size_idx++) {
      cell_x = size_idx * 0x41;
      key_color = sprite_get_key_color
                        ((Sprite *)(&city_sprites + size_idx * 0x78 + style2 * 0x1e0));
      fill_color = (uint)key_color;
      height = sprite_height
                        ((Sprite *)(&city_sprites + size_idx * 0x78 + style2 * 0x1e0));
      width = sprite_width
                        ((Sprite *)(&city_sprites + size_idx * 0x78 + style2 * 0x1e0));
      gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),cell_x + x2,y2,width,height,fill_color);
      sprite_draw
                ((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_city_bg,(iptr)((u8 *)&g.d_006ac0a8),cell_x + x2,
                 y2);
      sprite_draw
                ((Sprite *)(&city_sprites + size_idx * 0x78 + style2 * 0x1e0),
                 (iptr)clip_city,(iptr)((u8 *)&g.d_006ac0a8),cell_x + x2,y2);
      key_color = sprite_get_key_color
                        ((Sprite *)(&city_walled_sprites + size_idx * 0x78 + style2 * 0x1e0));
      fill_color = (uint)key_color;
      height = sprite_height
                        ((Sprite *)(&city_walled_sprites + size_idx * 0x78 + style2 * 0x1e0));
      width = sprite_width
                        ((Sprite *)(&city_walled_sprites + size_idx * 0x78 + style2 * 0x1e0));
      gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),cell_x + walled_x,y2,width,height,fill_color);
      sprite_draw
                ((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_walled_bg,(iptr)((u8 *)&g.d_006ac0a8),cell_x + walled_x,
                 y2);
      sprite_draw
                ((Sprite *)(&city_walled_sprites + size_idx * 0x78 + style2 * 0x1e0),
                 (iptr)clip_walled,(iptr)((u8 *)&g.d_006ac0a8),cell_x + walled_x,y2);
    }
    y2 += 0x31;
  }
  x2 = 1;
  flag_y = 0x1a9;
  flag_dark_y = 0x1c0;
  for (civ = 0; civ < 8; civ++) {
    key_color = sprite_get_key_color((Sprite *)(&civ_flag_sprites + civ * 0x78));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&civ_flag_sprites + civ * 0x78));
    width = sprite_width((Sprite *)(&civ_flag_sprites + civ * 0x78));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,flag_y,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&civ_flag_sprites + civ * 0x78),(iptr)clip_flag,(iptr)((u8 *)&g.d_006ac0a8),
               x2,flag_y);
    key_color = sprite_get_key_color((Sprite *)(&civ_flag_dark_sprites + civ * 0x78));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&civ_flag_dark_sprites + civ * 0x78));
    width = sprite_width((Sprite *)(&civ_flag_dark_sprites + civ * 0x78));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,flag_dark_y,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&civ_flag_dark_sprites + civ * 0x78),(iptr)clip_flag_dark,(iptr)((u8 *)&g.d_006ac0a8),
               x2,flag_dark_y);
    x2 += 0xf;
  }
  key_color = sprite_get_key_color((Sprite *)&fortify_overlay_sprites);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&fortify_overlay_sprites);
  width = sprite_width((Sprite *)&fortify_overlay_sprites);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),0x8f,0x1a7,width,height,fill_color);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_fortify_bg,(iptr)((u8 *)&g.d_006ac0a8),0x8f,0x1a7);
  sprite_draw((Sprite *)&fortify_overlay_sprites,(iptr)clip_fortify,(iptr)((u8 *)&g.d_006ac0a8),0x8f,0x1a7);
  key_color = sprite_get_key_color((Sprite *)&fortress_sprite);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&fortress_sprite);
  width = sprite_width((Sprite *)&fortress_sprite);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),0xd0,0x1a7,width,height,fill_color);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_fortress_bg,(iptr)((u8 *)&g.d_006ac0a8),0xd0,0x1a7);
  sprite_draw((Sprite *)&fortress_sprite,(iptr)clip_fortress,(iptr)((u8 *)&g.d_006ac0a8),0xd0,0x1a7);
  key_color = sprite_get_key_color((Sprite *)&airbase_sprites);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&airbase_sprites);
  width = sprite_width((Sprite *)&airbase_sprites);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),0x111,0x1a7,width,height,fill_color);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_airbase_bg,(iptr)((u8 *)&g.d_006ac0a8),0x111,0x1a7);
  sprite_draw((Sprite *)&airbase_sprites,(iptr)clip_airbase,(iptr)((u8 *)&g.d_006ac0a8),0x111,0x1a7);
  key_color = sprite_get_key_color((Sprite *)&airbase_occupied_sprite);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&airbase_occupied_sprite);
  width = sprite_width((Sprite *)&airbase_occupied_sprite);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),0x152,0x1a7,width,height,fill_color);
  sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)clip_airbase_occ_bg,(iptr)((u8 *)&g.d_006ac0a8),0x152,0x1a7);
  sprite_draw((Sprite *)&airbase_occupied_sprite,(iptr)clip_airbase_occ,(iptr)((u8 *)&g.d_006ac0a8),0x152,0x1a7);
  __chdir(&scenario_dir_path);
  result = file_exists((iptr)((u8 *)&g.d_0063407c));
  if (result != 0) {
    result = crt_remove(s_CITIES_BMP_00634088);
    if (result != 0) goto LAB_00570732;
  }
  gfx_save_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_00634094),10,0xc0,(iptr)&palette);
LAB_00570732:
  __chdir(saved_dir);
  surface_release((DibSurface *)&sprite_sheet_surface);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0057075c */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef clip_airbase_occ
#undef clip_airbase_occ_bg
#undef clip_airbase
#undef clip_airbase_bg
#undef clip_fortress
#undef clip_fortress_bg
#undef clip_fortify
#undef clip_fortify_bg
#undef clip_flag_dark
#undef clip_flag
#undef clip_walled
#undef clip_walled_bg
#undef clip_city
#undef clip_city_bg
#undef style2
#undef civ
#undef cell_x
#undef flag_dark_y
#undef flag_y
#undef walled_x
#undef y2
#undef x2
#undef palette
#undef saved_dir
#undef size_idx
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00570780 auto */
#define rail_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define rail_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define road_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define road_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define hut_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define hut_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define shield_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define shield_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define pollution_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define pollution_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define impr_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define impr_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define res2_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define res2_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define res_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(224)))
#define res_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(240)))
#define base_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(256)))
#define base_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(272)))
#define res2_x (*(i32 *)(frame_ + FRAME_OFF(288)))
#define res_x (*(i32 *)(frame_ + FRAME_OFF(292)))
#define y2 (*(int *)(frame_ + FRAME_OFF(296)))
#define x2 (*(int *)(frame_ + FRAME_OFF(300)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(304)))
#define saved_cwd (*(char (*)[260])(frame_ + FRAME_OFF(1380)))
#define terrain2 (*(int *)(frame_ + FRAME_OFF(1640)))
#define i (*(int *)(frame_ + FRAME_OFF(1644)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1648)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(1652)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(1656)))
void __cdecl sprite_sheet_save_terrain1(void)

{
  byte key_color;
  int result;
  iptr height;
  i32 width;
  uint fill_color;
  i8 frame_[FRAME_OFF(1664)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  palette_init(&palette);
  seh_state = 0;
  __getcwd(saved_cwd,0x104);
  __chdir(&scenario_dir_path);
  result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_006340a0),10,0xc0,(iptr)&palette);
  if (result == 0) {
    result = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_006340b0),10,0xc0,(iptr)&palette);
    if (result == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_006340c0),10,0xc0,(iptr)&palette);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  x2 = 1;
  res_x = 0x83;
  res2_x = 0xc4;
  y2 = 1;
  for (terrain2 = 0; terrain2 < 0xb; terrain2++) {
    key_color = sprite_get_key_color((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c));
    width = sprite_width((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)base_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
    sprite_draw
              ((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c),(iptr)base_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    key_color = sprite_get_key_color((Sprite *)(&terrain_resource_sprites + terrain2 * 0x78));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&terrain_resource_sprites + terrain2 * 0x78));
    width = sprite_width((Sprite *)(&terrain_resource_sprites + terrain2 * 0x78));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),res_x,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)res_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),res_x,y2);
    sprite_draw
              ((Sprite *)(&terrain_resource_sprites + terrain2 * 0x78),(iptr)res_rect,(iptr)((u8 *)&g.d_006ac0a8),res_x
               ,y2);
    key_color = sprite_get_key_color((Sprite *)(&terrain_resource2_sprites + terrain2 * 0x78));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&terrain_resource2_sprites + terrain2 * 0x78));
    width = sprite_width((Sprite *)(&terrain_resource2_sprites + terrain2 * 0x78));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),res2_x,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)res2_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),res2_x,y2);
    sprite_draw
              ((Sprite *)(&terrain_resource2_sprites + terrain2 * 0x78),(iptr)res2_rect,(iptr)((u8 *)&g.d_006ac0a8),res2_x
               ,y2);
    y2 += 0x21;
  }
  x2 = 0x1c8;
  y2 = 100;
  for (i = 0; i < 3; i++) {
    key_color = sprite_get_key_color((Sprite *)(&land_improvement_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&land_improvement_sprites + terrain2 * 0x3c));
    width = sprite_width((Sprite *)(&land_improvement_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)impr_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
    sprite_draw
              ((Sprite *)(&land_improvement_sprites + i * 0x3c),(iptr)impr_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    y2 += 0x21;
  }
  key_color = sprite_get_key_color((Sprite *)&pollution_sprite);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&pollution_sprite);
  width = sprite_width((Sprite *)&pollution_sprite);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
  sprite_draw
            ((Sprite *)&editor_tile_backdrop_sprite,(iptr)pollution_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
  sprite_draw
            ((Sprite *)&pollution_sprite,(iptr)pollution_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
  y2 += 0x21;
  key_color = sprite_get_key_color((Sprite *)&grassland_shield_sprite);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&grassland_shield_sprite);
  width = sprite_width((Sprite *)&grassland_shield_sprite);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
  sprite_draw
            ((Sprite *)&editor_tile_backdrop_sprite,(iptr)shield_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
  sprite_draw
            ((Sprite *)&grassland_shield_sprite,(iptr)shield_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
  y2 += 0x21;
  key_color = sprite_get_key_color((Sprite *)&hut_sprite);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&hut_sprite);
  width = sprite_width((Sprite *)&hut_sprite);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
  sprite_draw
            ((Sprite *)&editor_tile_backdrop_sprite,(iptr)hut_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
  sprite_draw
            ((Sprite *)&hut_sprite,(iptr)hut_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
  y2 = 0x16c;
  x2 = 1;
  for (i = 0; i < 9; i++) {
    key_color = sprite_get_key_color((Sprite *)(&road_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&road_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&road_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)road_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
    sprite_draw
              ((Sprite *)(&road_sprites + i * 0x3c),(iptr)road_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    key_color = sprite_get_key_color((Sprite *)(&railroad_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&railroad_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&railroad_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2 + 0x21,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)rail_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2 + 0x21);
    sprite_draw
              ((Sprite *)(&railroad_sprites + i * 0x3c),(iptr)rail_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2 + 0x21);
    x2 += 0x41;
  }
  __chdir(&scenario_dir_path);
  result = file_exists((iptr)((u8 *)&g.d_006340d0));
  if (result != 0) {
    result = crt_remove(s_TERRAIN1_BMP_006340e0);
    if (result != 0) goto LAB_00570f78;
  }
  gfx_save_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_006340f0),10,0xc0,(iptr)&palette);
LAB_00570f78:
  __chdir(saved_cwd);
  surface_release((DibSurface *)&sprite_sheet_surface);
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00570fa2 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef rail_rect
#undef rail_bg_rect
#undef road_rect
#undef road_bg_rect
#undef hut_rect
#undef hut_bg_rect
#undef shield_rect
#undef shield_bg_rect
#undef pollution_rect
#undef pollution_bg_rect
#undef impr_rect
#undef impr_bg_rect
#undef res2_rect
#undef res2_bg_rect
#undef res_rect
#undef res_bg_rect
#undef base_rect
#undef base_bg_rect
#undef res2_x
#undef res_x
#undef y2
#undef x2
#undef palette
#undef saved_cwd
#undef terrain2
#undef i
#undef seh_handler
#undef seh_next
#undef seh_state

/* 00570fc6 auto */
#define coast_w_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define coast_s_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define coast_e_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define coast_n_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define mouth_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define mouth_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define hill_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define hill_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define mountain_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define mountain_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define forest_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define forest_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define river_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define river_bg_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define coast_idx (*(int *)(frame_ + FRAME_OFF(224)))
#define base_y (*(int *)(frame_ + FRAME_OFF(228)))
#define cell_y (*(int *)(frame_ + FRAME_OFF(232)))
#define cell_x (*(int *)(frame_ + FRAME_OFF(236)))
#define base_x (*(int *)(frame_ + FRAME_OFF(240)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(244)))
#define saved_cwd (*(char (*)[260])(frame_ + FRAME_OFF(1320)))
#define i (*(uint *)(frame_ + FRAME_OFF(1580)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1584)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(1588)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(1592)))
void __cdecl sprite_sheet_save_terrain2(void)

{
  byte key_color;
  int result;
  iptr height;
  i32 width;
  uint fill_color;
  i8 frame_[FRAME_OFF(1600)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  palette_init(&palette);
  seh_state = 0;
  __getcwd(saved_cwd,0x104);
  __chdir(&scenario_dir_path);
  result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_00634100),10,0xc0,(iptr)&palette);
  if (result == 0) {
    result = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_00634110),10,0xc0,(iptr)&palette);
    if (result == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_00634120),10,0xc0,(iptr)&palette);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  base_x = 1;
  base_y = 0x43;
  for (i = 0; (int)i < 0x10; i++) {
    cell_x = (i & 7) * 0x41;
    cell_y = ((int)i >> 3) * 0x21;
    key_color = sprite_get_key_color((Sprite *)(&river_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&river_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&river_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,base_y + cell_y,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)river_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,
               base_y + cell_y);
    sprite_draw
              ((Sprite *)(&river_sprites + i * 0x3c),(iptr)river_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x + cell_x,base_y + cell_y);
    key_color = sprite_get_key_color((Sprite *)(&forest_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&forest_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&forest_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,base_y + cell_y + 0x42,width,height,fill_color
                      );
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)forest_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,
               base_y + cell_y + 0x42);
    sprite_draw
              ((Sprite *)(&forest_sprites + i * 0x3c),(iptr)forest_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x + cell_x,base_y + cell_y + 0x42);
    key_color = sprite_get_key_color((Sprite *)(&mountain_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&mountain_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&mountain_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,base_y + cell_y + 0x84,width,height,fill_color
                      );
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)mountain_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,
               base_y + cell_y + 0x84);
    sprite_draw
              ((Sprite *)(&mountain_sprites + i * 0x3c),(iptr)mountain_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x + cell_x,base_y + cell_y + 0x84);
    key_color = sprite_get_key_color((Sprite *)(&hill_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&hill_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&hill_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,base_y + cell_y + 0xc6,width,height,fill_color
                      );
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)hill_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),base_x + cell_x,
               base_y + cell_y + 0xc6);
    sprite_draw
              ((Sprite *)(&hill_sprites + i * 0x3c),(iptr)hill_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x + cell_x,base_y + cell_y + 0xc6);
  }
  base_x = 1;
  base_y = 0x14b;
  for (i = 0; (int)i < 4; i++) {
    key_color = sprite_get_key_color((Sprite *)(&river_mouth_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&river_mouth_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&river_mouth_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x,base_y,width,height,fill_color);
    sprite_draw
              ((Sprite *)&editor_tile_backdrop_sprite,(iptr)mouth_bg_rect,(iptr)((u8 *)&g.d_006ac0a8),base_x,base_y);
    sprite_draw
              ((Sprite *)(&river_mouth_sprites + i * 0x3c),(iptr)mouth_rect,(iptr)((u8 *)&g.d_006ac0a8),base_x
               ,base_y);
    base_x += 0x41;
  }
  base_x = 1;
  base_y = 0x1ad;
  for (coast_idx = 0; coast_idx < 8; coast_idx++) {
    key_color = sprite_get_key_color((Sprite *)(&coast_quarter_sprites + coast_idx * 0xf0));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&coast_quarter_sprites + coast_idx * 0xf0));
    width = sprite_width((Sprite *)(&coast_quarter_sprites + coast_idx * 0xf0));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x,base_y,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&coast_quarter_sprites + coast_idx * 0xf0),(iptr)coast_n_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x,base_y);
    key_color = sprite_get_key_color((Sprite *)(&coast_quarter_east_sprites + coast_idx * 0xf0));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&coast_quarter_east_sprites + coast_idx * 0xf0));
    width = sprite_width((Sprite *)(&coast_quarter_east_sprites + coast_idx * 0xf0));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x + 0x21,base_y + 0x22,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&coast_quarter_east_sprites + coast_idx * 0xf0),(iptr)coast_e_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x + 0x21,base_y + 0x22);
    key_color = sprite_get_key_color((Sprite *)(&coast_quarter_south_sprites + coast_idx * 0xf0));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&coast_quarter_south_sprites + coast_idx * 0xf0));
    width = sprite_width((Sprite *)(&coast_quarter_south_sprites + coast_idx * 0xf0));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x,base_y + 0x11,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&coast_quarter_south_sprites + coast_idx * 0xf0),(iptr)coast_s_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x,base_y + 0x11);
    key_color = sprite_get_key_color((Sprite *)(&coast_quarter_west_sprites + coast_idx * 0xf0));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&coast_quarter_west_sprites + coast_idx * 0xf0));
    width = sprite_width((Sprite *)(&coast_quarter_west_sprites + coast_idx * 0xf0));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),base_x,base_y + 0x22,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&coast_quarter_west_sprites + coast_idx * 0xf0),(iptr)coast_w_rect,(iptr)((u8 *)&g.d_006ac0a8),
               base_x,base_y + 0x22);
    base_x += 0x42;
  }
  __chdir(&scenario_dir_path);
  result = file_exists((iptr)((u8 *)&g.d_00634130));
  if (result != 0) {
    result = crt_remove(s_TERRAIN2_BMP_00634140);
    if (result != 0) goto LAB_005718c2;
  }
  gfx_save_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_00634150),10,0xc0,(iptr)&palette);
LAB_005718c2:
  __chdir(saved_cwd);
  surface_release((DibSurface *)&sprite_sheet_surface);
  seh_state = 0xffffffff;
  /* inlined unwind funclet 005718ec */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef coast_w_rect
#undef coast_s_rect
#undef coast_e_rect
#undef coast_n_rect
#undef mouth_rect
#undef mouth_bg_rect
#undef hill_rect
#undef hill_bg_rect
#undef mountain_rect
#undef mountain_bg_rect
#undef forest_rect
#undef forest_bg_rect
#undef river_rect
#undef river_bg_rect
#undef coast_idx
#undef base_y
#undef cell_y
#undef cell_x
#undef base_x
#undef palette
#undef saved_cwd
#undef i
#undef seh_handler
#undef seh_next
#undef seh_state

/* 00571910 auto */
#define icon_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define y2 (*(int *)(frame_ + FRAME_OFF(16)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(1096)))
#define saved_cwd (*(char (*)[260])(frame_ + FRAME_OFF(1100)))
#define category2 (*(int *)(frame_ + FRAME_OFF(1360)))
#define row (*(int *)(frame_ + FRAME_OFF(1364)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1368)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(1372)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(1376)))
void __cdecl sprite_sheet_save_tech_icons(void)

{
  byte key_color;
  int result;
  iptr height;
  i32 width;
  uint fill_color;
  i8 frame_[FRAME_OFF(1384)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  palette_init(&palette);
  seh_state = 0;
  __getcwd(saved_cwd,0x104);
  __chdir(&scenario_dir_path);
  result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_00634160),10,0xc0,(iptr)&palette);
  if (result == 0) {
    result = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_0063416c),10,0xc0,(iptr)&palette);
    if (result == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_00634178),10,0xc0,(iptr)&palette);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  y2 = 0xd3;
  for (row = 0; row < 4; row++) {
    x2 = 0x157;
    for (category2 = 0; category2 < 5; category2++) {
      key_color = sprite_get_key_color
                        ((Sprite *)(&advance_category_icon_sprites + category2 * 0xf0 + row * 0x3c));
      fill_color = (uint)key_color;
      height = sprite_height
                        ((Sprite *)(&advance_category_icon_sprites + category2 * 0xf0 + row * 0x3c));
      width = sprite_width
                        ((Sprite *)(&advance_category_icon_sprites + category2 * 0xf0 + row * 0x3c));
      gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
      sprite_draw
                ((Sprite *)(&advance_category_icon_sprites + category2 * 0xf0 + row * 0x3c),
                 (iptr)icon_rect,(iptr)((u8 *)&g.d_006ac0a8),x2,y2);
      x2 += 0x25;
    }
    y2 += 0x15;
  }
  __chdir(&scenario_dir_path);
  result = file_exists((iptr)((u8 *)&g.d_00634184));
  if (result != 0) {
    result = crt_remove(s_ICONS_BMP_00634190);
    if (result != 0) goto LAB_00571b80;
  }
  gfx_save_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_0063419c),10,0xc0,(iptr)&palette);
LAB_00571b80:
  __chdir(saved_cwd);
  surface_release((DibSurface *)&sprite_sheet_surface);
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00571baa */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef icon_rect
#undef y2
#undef palette
#undef x2
#undef saved_cwd
#undef category2
#undef row
#undef seh_handler
#undef seh_next
#undef seh_state

/* 00571bce auto */
#define explosion_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define cursor_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define wonder_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define improvement_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define column (*(int *)(frame_ + FRAME_OFF(64)))
#define y2 (*(int *)(frame_ + FRAME_OFF(68)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(72)))
#define x2 (*(int *)(frame_ + FRAME_OFF(1148)))
#define saved_cwd (*(char (*)[260])(frame_ + FRAME_OFF(1152)))
#define i (*(int *)(frame_ + FRAME_OFF(1412)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1416)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(1420)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(1424)))
void __cdecl sprite_sheet_save_building_icons(void)

{
  byte key_color;
  int result;
  iptr height;
  i32 width;
  uint fill_color;
  i8 frame_[FRAME_OFF(1432)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  palette_init(&palette);
  seh_state = 0;
  __getcwd(saved_cwd,0x104);
  __chdir(&scenario_dir_path);
  result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_006341a8),10,0xc0,(iptr)&palette);
  if (result == 0) {
    result = surface_load_gif_file
                      ((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_006341b4),10,0xc0,(iptr)&palette);
    if (result == 0) {
      __chdir(&game_home_dir);
      surface_load_gif_file((DibSurface *)&sprite_sheet_surface,(iptr)((u8 *)&g.d_006341c0),10,0xc0,(iptr)&palette);
    }
    else {
      __chdir(&game_home_dir);
    }
  }
  else {
    __chdir(&game_home_dir);
  }
  x2 = 0x157;
  y2 = 1;
  column = 0;
  for (i = 1; i < 0x27; i++) {
    key_color = sprite_get_key_color((Sprite *)(&improvement_icon_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&improvement_icon_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&improvement_icon_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&improvement_icon_sprites + i * 0x3c),(iptr)improvement_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    x2 += 0x25;
    column++;
    if (7 < column) {
      column = 0;
      y2 += 0x15;
      x2 = 0x157;
    }
  }
  x2 = 0x157;
  y2 = 0x6a;
  column = 0;
  for (i = 0; i < 0x1c; i++) {
    key_color = sprite_get_key_color((Sprite *)(&wonder_icon_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&wonder_icon_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&wonder_icon_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&wonder_icon_sprites + i * 0x3c),(iptr)wonder_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    x2 += 0x25;
    column++;
    if (6 < column) {
      column = 0;
      y2 += 0x15;
      x2 = 0x157;
    }
  }
  key_color = sprite_get_key_color((Sprite *)&map_cursor_sprite);
  fill_color = (uint)key_color;
  height = sprite_height((Sprite *)&map_cursor_sprite);
  width = sprite_width((Sprite *)&map_cursor_sprite);
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),199,0x100,width,height,fill_color);
  sprite_draw((Sprite *)&map_cursor_sprite,(iptr)cursor_rect,(iptr)((u8 *)&g.d_006ac0a8),199,0x100);
  x2 = 1;
  y2 = 0x164;
  for (i = 0; i < 8; i++) {
    key_color = sprite_get_key_color((Sprite *)(&explosion_sprites + i * 0x3c));
    fill_color = (uint)key_color;
    height = sprite_height((Sprite *)(&explosion_sprites + i * 0x3c));
    width = sprite_width((Sprite *)(&explosion_sprites + i * 0x3c));
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac0a8),x2,y2,width,height,fill_color);
    sprite_draw
              ((Sprite *)(&explosion_sprites + i * 0x3c),(iptr)explosion_rect,(iptr)((u8 *)&g.d_006ac0a8),x2
               ,y2);
    x2 += 0x21;
  }
  __chdir(&scenario_dir_path);
  result = file_exists((iptr)((u8 *)&g.d_006341cc));
  if (result != 0) {
    result = crt_remove(s_ICONS_BMP_006341d8);
    if (result != 0) goto LAB_0057203b;
  }
  gfx_save_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)((u8 *)&g.d_006341e4),10,0xc0,(iptr)&palette);
LAB_0057203b:
  __chdir(saved_cwd);
  surface_release((DibSurface *)&sprite_sheet_surface);
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00572065 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef explosion_rect
#undef cursor_rect
#undef wonder_rect
#undef improvement_rect
#undef column
#undef y2
#undef palette
#undef x2
#undef saved_cwd
#undef i
#undef seh_handler
#undef seh_next
#undef seh_state

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
#define parent_hwnd (*(iptr *)(frame_ + FRAME_OFF(4)))
#define wnd_style (*(uint *)(frame_ + FRAME_OFF(8)))
/* WARNING: Removing unreachable block (ram,0x0057228e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
sprite_editor_create_window(int title,uint style_flags,int x,int y,int width,int height,int resize_border,
            int caption_height,int border_width)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (title == 0) {
    crt_strcpy(&sprite_editor_title,&sprite_editor_default_title);
  }
  else {
    crt_strcpy(&sprite_editor_title,title);
  }
  sprite_editor_text_font_i32 = &ui_text_font;
  sprite_editor_title_font_i32 = &caption_font;
  sprite_editor_title_small_font_i32 = &caption_small_font;
  sprite_editor_style_flags_i32 = style_flags;
  sprite_editor_caption_height = caption_height;
  sprite_editor_border_width = border_width;
  sprite_editor_resize_border = resize_border;
  sprite_editor_caption_button_count_i32 = 0;
  sprite_editor_caption_button_cb_i32 = 0;
  if ((style_flags & 4) != 0) {
    sprite_editor_caption_height = frame_caption_height;
    sprite_editor_border_width = frame_border_width;
  }
  if ((style_flags & 8) == 0) {
    wnd_style = 0x202;
  }
  else {
    wnd_style = 0x802;
  }
  if (sprite_editor_caption_height != 0) {
    wnd_style = wnd_style | 0x400;
  }
  if (resize_border != 0) {
    wnd_style = wnd_style | 0x1000;
  }
  if ((style_flags & 2) == 0) {
    width += sprite_editor_border_width * 2;
    height = height + sprite_editor_caption_height + sprite_editor_border_width;
  }
  if ((style_flags & 1) != 0) {
    x = (screen_width >> 1) - (width >> 1);
    y = (screen_height >> 1) - (height >> 1);
  }
  if (active_editor_wnd == 0) {
    parent_hwnd = 0;
  }
  else {
    parent_hwnd = active_editor_wnd + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)&sprite_editor_window,0,wnd_style,x,y,width,height,(iptr)((u8 *)&g.d_006a8c00),
             parent_hwnd);
  if (sprite_editor_caption_height != 0) {
    wnd_set_caption_height((WndBase *)&sprite_editor_wnd,sprite_editor_caption_height);
  }
  if (sprite_editor_resize_border != 0) {
    wnd_set_resize_border((WndBase *)&sprite_editor_wnd,sprite_editor_resize_border);
  }
  frame_wnd_layout((FrameWindow *)&sprite_editor_window);
  dlg_set_parent_window((iptr)((u8 *)&g.d_006ac1f8));
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
#undef parent_hwnd
#undef wnd_style

/* 005722ab auto */
#define sprite_editor_flag_x (*(i32 *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(i32 *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(iptr *)((u8 *)&g.d_006ac87c))
#define sprite_editor_ok_callback (*(code * *)((u8 *)&g.d_006ac888))
#define sprite_editor_running (*(i32 *)((u8 *)&g.d_006ac88c))
#define sprite_editor_width (*(iptr *)((u8 *)&g.d_006ac878))
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl sprite_editor_ok_clicked(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)rect,0,0,sprite_editor_width,sprite_editor_height);
  surface_replace_color_clip((DibSurface *)&sprite_editor_surface,0x109,0x107);
  sprite_grab_surface_rect(sprite_editor_target_sprite,(iptr)((u8 *)&g.d_006ac128),(iptr)rect);
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
#undef rect

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
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl sprite_editor_rebuild_sprite(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_free((Sprite *)&sprite_editor_result_sprite);
  rect_set_xywh((iptr)rect,0,0,sprite_editor_width,sprite_editor_height);
  sprite_grab_rect((Sprite *)&sprite_editor_result_sprite,(iptr)((u8 *)&g.d_006ac128),0xfe,(iptr)rect);
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
#undef rect

/* 005723ee auto */
#define sprite_editor_key_color (*(int *)((u8 *)&g.d_006ac874))
#define sprite_sheet_mode (*(int *)((u8 *)&g.d_006ac924))
#define prev_right_color (*(int *)(frame_ + FRAME_OFF(4)))
#define prev_left_color (*(int *)(frame_ + FRAME_OFF(8)))
#define left_color (*(int *)(frame_ + FRAME_OFF(12)))
#define right_color (*(int *)(frame_ + FRAME_OFF(16)))
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl sprite_editor_draw_swatches(void)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (sprite_editor_right_color == 0) {
    right_color = sprite_editor_key_color;
  }
  else {
    right_color = sprite_editor_right_color;
  }
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x142,sprite_editor_origin_y + 0xac,0x20,0x20,right_color);
  gfx_draw_frame_rect((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x142,sprite_editor_origin_y + 0xac,0x20,0x20,10);
  if (sprite_editor_left_color == 0) {
    left_color = sprite_editor_key_color;
  }
  else {
    left_color = sprite_editor_left_color;
  }
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x14a,sprite_editor_origin_y + 0xb4,0x10,0x10,left_color);
  gfx_draw_frame_rect((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x14a,sprite_editor_origin_y + 0xb4,0x10,0x10,10);
  if (sprite_editor_prev_left_color == 0) {
    prev_left_color = sprite_editor_key_color;
  }
  else {
    prev_left_color = sprite_editor_prev_left_color;
  }
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x11e,sprite_editor_origin_y + 0xac,0x20,0x20,prev_left_color);
  gfx_draw_frame_rect((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x11e,sprite_editor_origin_y + 0xac,0x20,0x20,10);
  if (sprite_sheet_mode != 0xb) {
    if (sprite_editor_prev_right_color == 0) {
      prev_right_color = sprite_editor_key_color;
    }
    else {
      prev_right_color = sprite_editor_prev_right_color;
    }
    gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x166,sprite_editor_origin_y + 0xac,0x20,0x20,prev_right_color);
    gfx_draw_frame_rect((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 0x166,sprite_editor_origin_y + 0xac,0x20,0x20,10);
  }
  rect_set_xywh((iptr)rect,sprite_editor_origin_x + 0x11e,sprite_editor_origin_y + 0xac,0x68,0x20);
  wnd_blit_surface_rect((DibSurface *)&sprite_editor_window,(iptr)rect);
  return;
}
#undef sprite_editor_key_color
#undef sprite_sheet_mode
#undef prev_right_color
#undef prev_left_color
#undef left_color
#undef right_color
#undef rect

/* 0057261a auto */
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl sprite_editor_draw_palette_cell(iptr surface,int origin_x,int origin_y,int color)

{
  int col;
  int row;
  uint sign;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((9 < color) && (color < 0xca)) {
    sign = (int)(color - 10U) >> 0x1f;
    col = ((color - 10U ^ sign) - sign & 0x1f ^ sign) - sign;
    row = (int)(color - 10 + (color - 10 >> 0x1f & 0x1fU)) >> 5;
    rect_set_xywh((iptr)rect,col * 0xc + origin_x,row * 0xc + origin_y,10,10);
    gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)rect,color);
    gfx_draw_bevel_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)rect,10,10);
    rect_set_xywh((iptr)rect,col * 0xc + origin_x - 1,row * 0xc + origin_y - 1,0xc,0xc)
    ;
    if ((color == sprite_editor_right_color) || (color == sprite_editor_left_color)) {
      gfx_draw_bevel_rect(surface,(iptr)rect,0x29,0x29);
    }
    else {
      gfx_draw_bevel_rect(surface,(iptr)rect,0x1d,0x1d);
    }
    wnd_blit_surface_rect((DibSurface *)surface,(iptr)rect);
  }
  return;
}
#undef rect

/* 00572740 auto */
int __cdecl sprite_editor_tool_hit_test(int x,int y)

{
  int rel_y;
  int rel_x;
  
  rel_x = x - 0x11e;
  rel_y = y - 0x14;
  if ((((rel_x < 0) || (0x6c < rel_x)) || (rel_y < 0)) ||
     (((0xbe < rel_y || (0x20 < rel_x % 0x24)) || (0x20 < rel_y % 0x26)))) {
    rel_x = -1;
  }
  else {
    rel_x = rel_x / 0x24 + (rel_y / 0x26) * 3;
  }
  return rel_x;
}

/* 005727d8 auto */
#define sprite_editor_key_color (*(i32 *)((u8 *)&g.d_006ac874))
#define sprite_sheet_mode (*(i32 *)((u8 *)&g.d_006ac924))
#define tile_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define unit_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl sprite_editor_draw_backdrop(void)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_fill((DibSurface *)&sprite_editor_surface,sprite_editor_key_color);
  switch(sprite_sheet_mode) {
  case 1:
  case 2:
  case 0xb:
    sprite_draw((Sprite *)&editor_unit_backdrop_sprite,(iptr)unit_rect,(iptr)((u8 *)&g.d_006ac128),0,0);
    break;
  case 5:
  case 7:
  case 8:
  case 10:
    sprite_draw((Sprite *)&editor_tile_backdrop_sprite,(iptr)tile_rect,(iptr)((u8 *)&g.d_006ac128),0,0);
  case 3:
  case 4:
  case 6:
  case 9: ;
  }
  return;
}
#undef sprite_editor_key_color
#undef sprite_sheet_mode
#undef tile_rect
#undef unit_rect

/* 00572887 auto */
#define sprite_editor_brush_size (*(int *)((u8 *)&g.d_006ac124))
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_key_color (*(int *)((u8 *)&g.d_006ac874))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define color8 (*(int *)(frame_ + FRAME_OFF(4)))
#define color7 (*(int *)(frame_ + FRAME_OFF(8)))
#define color6 (*(int *)(frame_ + FRAME_OFF(12)))
#define color5 (*(int *)(frame_ + FRAME_OFF(16)))
#define color4 (*(int *)(frame_ + FRAME_OFF(20)))
#define color3 (*(int *)(frame_ + FRAME_OFF(24)))
#define color2 (*(int *)(frame_ + FRAME_OFF(28)))
#define color1 (*(int *)(frame_ + FRAME_OFF(32)))
#define screen_color (*(int *)(frame_ + FRAME_OFF(36)))
#define pixel_color (*(int *)(frame_ + FRAME_OFF(40)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(44)))
i8 * __cdecl sprite_editor_plot_pixel(int px,int py)

{
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (sprite_editor_brush_size == 0) {
    if (sprite_editor_paint_color == 0) {
      pixel_color = sprite_editor_key_color;
    }
    else {
      pixel_color = sprite_editor_paint_color;
    }
    surface_set_pixel((DibSurface *)&sprite_editor_surface,px,py,pixel_color);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0x10,sprite_editor_origin_y + py * 4 + 0x10,
                       4,4);
    if (sprite_editor_paint_color == 0) {
      screen_color = sprite_editor_key_color;
    }
    else {
      screen_color = sprite_editor_paint_color;
    }
    gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac108),screen_color);
  }
  else if (sprite_editor_brush_size == 1) {
    surface_get_clip((DibSurface *)&sprite_editor_window,(iptr)saved_clip);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),sprite_editor_origin_x + 0x10,sprite_editor_origin_y + 0x10,sprite_editor_width << 2,
                       sprite_editor_height << 2);
    surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)((u8 *)&g.d_006ac108));
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px - 1,py,3,1);
    if (sprite_editor_paint_color == 0) {
      color1 = sprite_editor_key_color;
    }
    else {
      color1 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,(iptr)((u8 *)&g.d_006ac108),color1);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0xc,sprite_editor_origin_y + py * 4 + 0x10,
                       0xc,4);
    if (sprite_editor_paint_color == 0) {
      color2 = sprite_editor_key_color;
    }
    else {
      color2 = sprite_editor_paint_color;
    }
    gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac108),color2);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px,py - 1,1,3);
    if (sprite_editor_paint_color == 0) {
      color3 = sprite_editor_key_color;
    }
    else {
      color3 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,(iptr)((u8 *)&g.d_006ac108),color3);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0x10,py * 4 + sprite_editor_origin_y + 0xc,4
                       ,0xc);
    if (sprite_editor_paint_color == 0) {
      color4 = sprite_editor_key_color;
    }
    else {
      color4 = sprite_editor_paint_color;
    }
    gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac108),color4);
    surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)saved_clip);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0xc,py * 4 + sprite_editor_origin_y + 0xc,
                       0xc,0xc);
  }
  else if (sprite_editor_brush_size == 2) {
    surface_get_clip((DibSurface *)&sprite_editor_window,(iptr)saved_clip);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),sprite_editor_origin_x + 0x10,sprite_editor_origin_y + 0x10,sprite_editor_width << 2,
                       sprite_editor_height << 2);
    surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)((u8 *)&g.d_006ac108));
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px - 1,py,4,2);
    if (sprite_editor_paint_color == 0) {
      color5 = sprite_editor_key_color;
    }
    else {
      color5 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,(iptr)((u8 *)&g.d_006ac108),color5);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0xc,sprite_editor_origin_y + py * 4 + 0x10,
                       0x10,8);
    if (sprite_editor_paint_color == 0) {
      color6 = sprite_editor_key_color;
    }
    else {
      color6 = sprite_editor_paint_color;
    }
    gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac108),color6);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px,py - 1,2,4);
    if (sprite_editor_paint_color == 0) {
      color7 = sprite_editor_key_color;
    }
    else {
      color7 = sprite_editor_paint_color;
    }
    surface_fill_rect((DibSurface *)&sprite_editor_surface,(iptr)((u8 *)&g.d_006ac108),color7);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0x10,py * 4 + sprite_editor_origin_y + 0xc,8
                       ,0x10);
    if (sprite_editor_paint_color == 0) {
      color8 = sprite_editor_key_color;
    }
    else {
      color8 = sprite_editor_paint_color;
    }
    gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac108),color8);
    surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)saved_clip);
    rect_set_xywh((iptr)((u8 *)&g.d_006ac108),px * 4 + sprite_editor_origin_x + 0xc,py * 4 + sprite_editor_origin_y + 0xc,
                       0x10,0x10);
  }
  return &sprite_editor_plot_rect;
}
#undef sprite_editor_brush_size
#undef sprite_editor_height
#undef sprite_editor_key_color
#undef sprite_editor_width
#undef color8
#undef color7
#undef color6
#undef color5
#undef color4
#undef color3
#undef color2
#undef color1
#undef screen_color
#undef pixel_color
#undef saved_clip

/* 00572da0 auto */
#define sprite_editor_flag_x (*(int *)((u8 *)&g.d_006ac0f4))
#define sprite_editor_flag_y (*(int *)((u8 *)&g.d_006ac0f0))
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define flag_x (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl sprite_editor_draw_flag_marker(void)

{
  int flag_y;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_repaint((SurfaceWindow *)&sprite_editor_window);
  flag_y = sprite_editor_flag_y;
  flag_x = sprite_editor_flag_x;
  surface_get_clip((DibSurface *)&sprite_editor_window,(iptr)saved_clip);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),sprite_editor_origin_x + 0x10,sprite_editor_origin_y + 0x10,sprite_editor_width << 2,
                     sprite_editor_height << 2);
  surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)((u8 *)&g.d_006ac0f8));
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),sprite_editor_origin_x + 0x20,sprite_editor_origin_y + 0x10,4,0x3c);
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),0x6a);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),sprite_editor_origin_x + 0x20,sprite_editor_origin_y + 0x4c,0xb4,4);
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),0x6a);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),sprite_editor_origin_x + 0xd0,sprite_editor_origin_y + 0x10,4,0x3c);
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),0x6a);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),flag_x * 4 + sprite_editor_origin_x + 8,sprite_editor_origin_y + flag_y * 4 + 0x10,0x14,4)
  ;
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),10);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),flag_x * 4 + sprite_editor_origin_x + 0x10,flag_y * 4 + sprite_editor_origin_y + 8,4,0x14)
  ;
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),10);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),flag_x * 4 + sprite_editor_origin_x + 9,sprite_editor_origin_y + flag_y * 4 + 0x11,0x12,2)
  ;
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),0x29);
  rect_set_xywh((iptr)((u8 *)&g.d_006ac0f8),flag_x * 4 + sprite_editor_origin_x + 0x11,flag_y * 4 + sprite_editor_origin_y + 9,2,0x12)
  ;
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac0f8),0x29);
  surface_set_clip((DibSurface *)&sprite_editor_window,(iptr)saved_clip);
  wnd_blit_surface((DibSurface *)&sprite_editor_window);
  return;
}
#undef sprite_editor_flag_x
#undef sprite_editor_flag_y
#undef sprite_editor_height
#undef sprite_editor_width
#undef saved_clip
#undef flag_x

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
#define draw_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define old_color (*(int *)(frame_ + FRAME_OFF(16)))
#define saved_flag_y (*(iptr *)(frame_ + FRAME_OFF(20)))
#define saved_flag_x (*(iptr *)(frame_ + FRAME_OFF(24)))
#define dirty_rect (*(iptr *)(frame_ + FRAME_OFF(28)))
#define new_color (*(int *)(frame_ + FRAME_OFF(32)))
#define grab_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define temp_sprite (*(Sprite *)(frame_ + FRAME_OFF(52)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(112)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(116)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(120)))
void __cdecl sprite_editor_on_mouse_down(int x,int y)

{
  iptr old_flag_y;
  iptr old_flag_x;
  SHORT SVar3;
  iptr window;
  i32 tool_index;
  int temp_x;
  int temp_y;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  sprite_init(&temp_sprite);
  seh_state = 0;
  window = wnd_get_window((WndBase *)&sprite_editor_wnd);
  SetCapture(*(HWND *)(window + 4));
  x -= sprite_editor_origin_x;
  y -= sprite_editor_origin_y;
  tool_index = sprite_editor_tool_hit_test(x,y);
  old_flag_x = sprite_editor_flag_x;
  old_flag_y = sprite_editor_flag_y;
  switch(tool_index) {
  case 0:
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
    SVar3 = GetKeyState(1);
    if (((int)SVar3 & 0x8000U) != 0) {
      sprite_editor_prev_left_color = sprite_editor_left_color;
      old_color = sprite_editor_left_color;
      sprite_editor_left_color = 0;
    }
    SVar3 = GetKeyState(2);
    if (((int)SVar3 & 0x8000U) != 0) {
      sprite_editor_prev_right_color = sprite_editor_right_color;
      old_color = sprite_editor_right_color;
      sprite_editor_right_color = 0;
    }
    sprite_editor_draw_swatches();
    sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),sprite_editor_origin_x + 10,sprite_editor_origin_y + 0xe0,old_color);
    y = 0;
    x = 0;
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
    saved_flag_x = sprite_editor_flag_x;
    saved_flag_y = sprite_editor_flag_y;
    sprite_editor_flag_x = sprite_editor_undo_flag_x;
    sprite_editor_flag_y = sprite_editor_undo_flag_y;
    sprite_editor_undo_flag_x = old_flag_x;
    sprite_editor_undo_flag_y = old_flag_y;
    sprite_free(&temp_sprite);
    rect_set_xywh((iptr)grab_rect,0,0,sprite_editor_width,sprite_editor_height);
    sprite_grab_rect(&temp_sprite,(iptr)((u8 *)&g.d_006ac128),0xfe,(iptr)grab_rect);
    sprite_draw_keyed((Sprite *)&sprite_editor_result_sprite,(iptr)draw_rect,(iptr)((u8 *)&g.d_006ac128),0xfe,0,0);
    sprite_free((Sprite *)&sprite_editor_result_sprite);
    sprite_merge_onto(&temp_sprite,(iptr)((u8 *)&g.d_006ac8a8));
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
    temp_x = sprite_editor_left_color;
    if (((int)SVar3 & 0x8000U) != 0) {
      old_color = sprite_editor_left_color;
      sprite_editor_left_color = sprite_editor_prev_left_color;
      new_color = sprite_editor_prev_left_color;
      sprite_editor_prev_left_color = temp_x;
    }
    SVar3 = GetKeyState(2);
    temp_x = sprite_editor_right_color;
    if (((int)SVar3 & 0x8000U) != 0) {
      old_color = sprite_editor_right_color;
      sprite_editor_right_color = sprite_editor_prev_left_color;
      new_color = sprite_editor_prev_left_color;
      sprite_editor_prev_right_color = temp_x;
    }
    sprite_editor_draw_swatches();
    temp_x = sprite_editor_origin_x + 10;
    temp_y = sprite_editor_origin_y + 0xe0;
    sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,old_color);
    sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,new_color);
    y = 0;
    x = 0;
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
      temp_x = sprite_editor_left_color;
      if (((int)SVar3 & 0x8000U) != 0) {
        old_color = sprite_editor_left_color;
        sprite_editor_left_color = sprite_editor_prev_right_color;
        new_color = sprite_editor_prev_right_color;
        sprite_editor_prev_left_color = temp_x;
      }
      SVar3 = GetKeyState(2);
      temp_x = sprite_editor_right_color;
      if (((int)SVar3 & 0x8000U) != 0) {
        old_color = sprite_editor_right_color;
        sprite_editor_right_color = sprite_editor_prev_right_color;
        new_color = sprite_editor_prev_right_color;
        sprite_editor_prev_right_color = temp_x;
      }
      sprite_editor_draw_swatches();
      temp_x = sprite_editor_origin_x + 10;
      temp_y = sprite_editor_origin_y + 0xe0;
      sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,old_color);
      sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,new_color);
      y = 0;
      x = 0;
    }
  }
  if ((((x < 9) || (0x187 < x)) || (y < 0xdf)) || (0x125 < y)) {
    if (((0xf < x) && (x < sprite_editor_width * 4 + 0x10)) &&
       ((0xf < y && (y < sprite_editor_height * 4 + 0x10)))) {
      switch(sprite_editor_tool) {
      case 0:
        new_color = surface_get_pixel
                             ((DibSurface *)&sprite_editor_surface,x - 0x10 >> 2,
                              y - 0x10 >> 2);
        SVar3 = GetKeyState(1);
        if (((int)SVar3 & 0x8000U) == 0) {
          SVar3 = GetKeyState(2);
          if (((int)SVar3 & 0x8000U) != 0) {
            sprite_editor_prev_right_color = sprite_editor_right_color;
            old_color = sprite_editor_right_color;
            sprite_editor_right_color = new_color;
          }
        }
        else {
          sprite_editor_prev_left_color = sprite_editor_left_color;
          old_color = sprite_editor_left_color;
          sprite_editor_left_color = new_color;
        }
        sprite_editor_draw_swatches();
        temp_x = sprite_editor_origin_x + 10;
        temp_y = sprite_editor_origin_y + 0xe0;
        sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,old_color);
        sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,new_color);
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
        temp_x = (int)(x - 0x10 + (x - 0x10 >> 0x1f & 3U)) >> 2;
        temp_y = (int)(y - 0x10 + (y - 0x10 >> 0x1f & 3U)) >> 2;
        sprite_editor_last_px = temp_x;
        sprite_editor_last_py = temp_y;
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
        dirty_rect = sprite_editor_plot_pixel(temp_x,temp_y);
        wnd_blit_surface_rect((DibSurface *)&sprite_editor_window,dirty_rect);
        break;
      case 3:
        sprite_editor_rebuild_sprite();
        sprite_editor_flag_x = int_clamp((int)(x - 0x10 + (x - 0x10 >> 0x1f & 3U)) >>
                                          2,5,0x2f);
        sprite_editor_flag_y = int_clamp((int)(y - 0x10 + (y - 0x10 >> 0x1f & 3U)) >>
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
        old_color = sprite_editor_right_color;
        sprite_editor_right_color = ((y - 0xdf) / 0xc) * 0x20 + (x - 9) / 0xc + 10;
        new_color = sprite_editor_right_color;
      }
    }
    else {
      sprite_editor_prev_left_color = sprite_editor_left_color;
      old_color = sprite_editor_left_color;
      sprite_editor_left_color = ((y - 0xdf) / 0xc) * 0x20 + (x - 9) / 0xc + 10;
      new_color = sprite_editor_left_color;
    }
    sprite_editor_draw_swatches();
    temp_x = sprite_editor_origin_x + 10;
    temp_y = sprite_editor_origin_y + 0xe0;
    sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,old_color);
    sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),temp_x,temp_y,new_color);
    if (sprite_editor_tool == 3) {
      wnd_repaint((SurfaceWindow *)&sprite_editor_window);
    }
    sprite_editor_tool = sprite_editor_paint_tool;
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00573adc */ { sprite_destroy((Sprite *)((iptr)&temp_sprite)); }
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
#undef draw_rect
#undef old_color
#undef saved_flag_y
#undef saved_flag_x
#undef dirty_rect
#undef new_color
#undef grab_rect
#undef temp_sprite
#undef seh_handler
#undef seh_next
#undef seh_state

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
#define prev_x (*(int *)(frame_ + FRAME_OFF(0)))
#define fixed_y (*(int *)(frame_ + FRAME_OFF(4)))
#define fixed_x (*(int *)(frame_ + FRAME_OFF(8)))
#define prev_y (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl sprite_editor_on_mouse_move(int x,int y)

{
  int px;
  int py;
  iptr dirty_rect;
  int dx;
  int dy;
  int cur_x;
  int cur_y;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  x -= sprite_editor_origin_x;
  y -= sprite_editor_origin_y;
  if ((((x < 9) || (0x187 < x)) || (y < 0xdf)) || (0x125 < y)) {
    if (((x < 0x10) || (sprite_editor_width * 4 + 0x10 <= x)) ||
       ((y < 0x10 || (sprite_editor_height * 4 + 0x10 <= y)))) {
      if (sprite_editor_cursor_id != 0x201) {
        sprite_editor_cursor_id = 0x201;
        wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x201);
        ui_flush_input();
      }
      sprite_editor_last_py = -1;
      sprite_editor_last_px = -1;
      px = sprite_editor_last_px;
      py = sprite_editor_last_py;
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
      px = sprite_editor_last_px;
      py = sprite_editor_last_py;
      if (sprite_editor_painting != 0) {
        px = (int)(x - 0x10 + (x - 0x10 >> 0x1f & 3U)) >> 2;
        py = (int)(y - 0x10 + (y - 0x10 >> 0x1f & 3U)) >> 2;
        if (sprite_editor_tool == 1) {
          if ((sprite_editor_last_px < 0) || (sprite_editor_last_py < 0)) {
            sprite_editor_last_px = px;
            sprite_editor_last_py = py;
          }
          dx = px - sprite_editor_last_px;
          dy = py - sprite_editor_last_py;
          prev_y = -1;
          prev_x = -1;
          fixed_x = sprite_editor_last_px << 8;
          fixed_y = sprite_editor_last_py << 8;
          while( true ) {
            cur_x = fixed_x >> 8;
            cur_y = fixed_y >> 8;
            if ((cur_x == px) && (cur_y == py)) break;
            if ((cur_x != prev_x) || (cur_y != prev_y)) {
              sprite_editor_plot_pixel(cur_x,cur_y);
              prev_x = cur_x;
              prev_y = cur_y;
            }
            fixed_x += dx;
            fixed_y += dy;
          }
          wnd_blit_surface((DibSurface *)&sprite_editor_window);
        }
        else if (sprite_editor_tool == 2) {
          dirty_rect = sprite_editor_plot_pixel(px,py);
          wnd_blit_surface_rect((DibSurface *)&sprite_editor_window,dirty_rect);
        }
      }
    }
  }
  else {
    px = sprite_editor_last_px;
    py = sprite_editor_last_py;
    if (sprite_editor_cursor_id != 0x205) {
      sprite_editor_cursor_id = 0x205;
      wnd_set_cursor((WndBase *)&sprite_editor_wnd,0x205);
      ui_flush_input();
      px = sprite_editor_last_px;
      py = sprite_editor_last_py;
    }
  }
  sprite_editor_last_py = py;
  sprite_editor_last_px = px;
  return;
}
#undef sprite_editor_cursor_id
#undef sprite_editor_height
#undef sprite_editor_painting
#undef sprite_editor_tool
#undef sprite_editor_width
#undef prev_x
#undef fixed_y
#undef fixed_x
#undef prev_y

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
#define draw_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define button_y2 (*(int *)(frame_ + FRAME_OFF(16)))
#define cancel_button (*(Control *)(frame_ + FRAME_OFF(20)))
#define button_height (*(int *)(frame_ + FRAME_OFF(80)))
#define button_x (*(int *)(frame_ + FRAME_OFF(84)))
#define button_width2 (*(int *)(frame_ + FRAME_OFF(88)))
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(92)))
#define ok_button (*(Control *)(frame_ + FRAME_OFF(108)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(168)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(172)))
#define seh_state (*(uint *)(frame_ + FRAME_OFF(176)))
/* WARNING: Removing unreachable block (ram,0x0057405e) */
/* WARNING: Removing unreachable block (ram,0x005740e7) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl sprite_editor_run(iptr sprite,i32 title,i32 sheet_mode,iptr ok_callback)

{
  byte key_color;
  int line_height;
  iptr label;
  i8 frame_[FRAME_OFF(184)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  button_ctor(&ok_button);
  seh_state = 0;
  button_ctor(&cancel_button);
  seh_state = CONCAT31((*(i32 *)((char *)&seh_state + 1)),1);
  sprite_sheet_mode = sheet_mode;
  sprite_editor_target_sprite = (Sprite *)sprite;
  sprite_editor_width = sprite_width((Sprite *)sprite);
  sprite_editor_height = sprite_height(sprite_editor_target_sprite);
  key_color = sprite_get_key_color(sprite_editor_target_sprite);
  sprite_editor_key_color = (uint)key_color;
  sprite_editor_ok_callback = ok_callback;
  sprite_free((Sprite *)&sprite_editor_orig_sprite);
  sprite_merge_onto(sprite_editor_target_sprite,(iptr)((u8 *)&g.d_006ac170));
  surface_create((DibSurface *)&sprite_editor_surface,sprite_editor_width,sprite_editor_height);
  sprite_editor_draw_backdrop();
  sprite_draw((Sprite *)&sprite_editor_orig_sprite,(iptr)draw_rect,(iptr)((u8 *)&g.d_006ac128),0,0);
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
  sprite_editor_create_window(title,0xd,0,0,0x192,0x14e,0,0,0);
  line_height = font_line_spacing((GameFont *)dialog_font_ptr);
  button_height = line_height + 8;
  button_width2 = (sprite_editor_client_width - 6) / 2;
  button_y2 = (sprite_editor_origin_y + sprite_editor_client_height_i32) - (line_height + 10);
  button_x = sprite_editor_origin_x + 2;
  rect_set_xywh((iptr)button_rect,button_x,button_y2,button_width2,button_height);
  label = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create(&ok_button,(iptr)((u8 *)&g.d_006ac1f8),0x65,(iptr)button_rect,label);
  button_set_callback(&ok_button,(iptr)sprite_editor_ok_clicked);
  button_x = button_x + button_width2 + 2;
  rect_set_xywh((iptr)button_rect,button_x,button_y2,button_width2,button_height);
  label = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create(&cancel_button,(iptr)((u8 *)&g.d_006ac1f8),0x66,(iptr)button_rect,label);
  button_set_callback(&cancel_button,(iptr)sprite_editor_cancel_clicked);
  ctrl_set_cancel_button(&cancel_button);
  wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,(iptr)sprite_editor_on_mouse_down);
  wnd_set_rbuttondown_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,(iptr)sprite_editor_on_mouse_down);
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,(iptr)sprite_editor_on_mouse_down);
  wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,(iptr)sprite_editor_on_mouse_up);
  wnd_set_rbuttonup_any_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,(iptr)sprite_editor_on_mouse_up);
  wnd_set_mousemove_handler((WndHandlersMouseSetView *)&sprite_editor_wnd_events,(iptr)sprite_editor_on_mouse_move);
  wnd_set_redraw_callback((SurfaceWindow *)&sprite_editor_window,(iptr)sprite_editor_redraw);
  wnd_repaint((SurfaceWindow *)&sprite_editor_window);
  window_show((WindowObjectView *)&sprite_editor_window);
  wnd_run_modal_loop((ModalMenuWindow *)&sprite_editor_wnd);
  while (sprite_editor_running != 0) {
    win_pump_one_message();
  }
  dlg_set_parent_window(0);
  frame_wnd_close((DibSurface *)&sprite_editor_window);
  seh_state = seh_state & 0xffffff00;
  /* inlined unwind funclet 0057420c */ { ctrl_dtor((Control *)((iptr)&cancel_button)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00574218 */ { ctrl_dtor((Control *)((iptr)&ok_button)); }
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
#undef draw_rect
#undef button_y2
#undef cancel_button
#undef button_height
#undef button_x
#undef button_width2
#undef button_rect
#undef ok_button
#undef seh_handler
#undef seh_next
#undef seh_state

/* 00574239 auto */
#define sprite_editor_height (*(int *)((u8 *)&g.d_006ac87c))
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define sprite_editor_width (*(int *)((u8 *)&g.d_006ac878))
#define tool_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define sprite_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define row (*(int *)(frame_ + FRAME_OFF(32)))
#define col (*(int *)(frame_ + FRAME_OFF(36)))
#define i (*(int *)(frame_ + FRAME_OFF(40)))
#define y2 (*(int *)(frame_ + FRAME_OFF(44)))
#define x2 (*(int *)(frame_ + FRAME_OFF(48)))
#define height2 (*(int *)(frame_ + FRAME_OFF(52)))
#define width2 (*(int *)(frame_ + FRAME_OFF(56)))
#define grab_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(60)))
void __cdecl sprite_editor_redraw(void)

{
  byte key_color;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption((FrameWindow *)&sprite_editor_window);
  gfx_fill_rect((iptr)((u8 *)&g.d_006ac1b0),(iptr)((u8 *)&g.d_006ac46c),0x1d);
  x2 = sprite_editor_origin_x + 0x10;
  y2 = sprite_editor_origin_y + 0x10;
  width2 = sprite_editor_width << 2;
  height2 = sprite_editor_height << 2;
  rect_set_xywh((iptr)grab_rect,0,0,sprite_editor_width,sprite_editor_height);
  sprite_grab_surface_rect((Sprite *)&sprite_editor_orig_sprite,(iptr)((u8 *)&g.d_006ac128),(iptr)grab_rect);
  key_color = sprite_get_key_color((Sprite *)&sprite_editor_orig_sprite);
  sprite_editor_key_color = (uint)key_color;
  gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),x2,y2,width2,height2,sprite_editor_key_color);
  gfx_set_scale_ratio(4,1);
  sprite_draw_keyed
            ((Sprite *)&sprite_editor_orig_sprite,(iptr)sprite_rect,(iptr)((u8 *)&g.d_006ac1b0),0,x2,y2);
  gfx_set_scale_ratio(1,1);
  gfx_draw_tiled_frame((iptr)((u8 *)&g.d_006ac1b0),x2,y2,width2,height2,6);
  x2 = sprite_editor_origin_x + 10;
  y2 = sprite_editor_origin_y + 0xe0;
  for (i = 0; i < 0xc0; i++) {
    sprite_editor_draw_palette_cell((iptr)((u8 *)&g.d_006ac1b0),x2,y2,i + 10);
  }
  x2 = sprite_editor_origin_x + 0x11e;
  y2 = sprite_editor_origin_y + 0x14;
  for (col = 0; col < 3; col++) {
    for (row = 0; row < 5; row++) {
      if (row == 0 && col == 0) {
        gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),col * 0x24 + x2,row * 0x26 + y2,0x20,0x20,
                           sprite_editor_key_color);
      }
      else {
        gfx_fill_rect_xywh((iptr)((u8 *)&g.d_006ac1b0),col * 0x24 + x2,row * 0x26 + y2,0x20,0x20,
                           0x29);
        sprite_draw
                  ((Sprite *)(&sprite_editor_tool_sprites + (row * 3 + col) * 0x3c),
                   (iptr)tool_rect,(iptr)((u8 *)&g.d_006ac1b0),col * 0x24 + x2,row * 0x26 + y2);
      }
      gfx_draw_frame_rect((iptr)((u8 *)&g.d_006ac1b0),col * 0x24 + x2,row * 0x26 + y2,0x20,0x20,10
                        );
    }
  }
  sprite_editor_draw_swatches();
  text_set_surface((iptr)((u8 *)&g.d_006ac1b0));
  text_set_font((iptr)((u8 *)&g.d_006a4f90));
  text_set_colors(0x29,0x12,1,1);
  wnd_blit_surface((DibSurface *)&sprite_editor_window);
  return;
}
#undef sprite_editor_height
#undef sprite_editor_key_color
#undef sprite_editor_width
#undef tool_rect
#undef sprite_rect
#undef row
#undef col
#undef i
#undef y2
#undef x2
#undef height2
#undef width2
#undef grab_rect

/* 00574522 auto */
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define draw_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define button_height (*(int *)(frame_ + FRAME_OFF(20)))
#define y2 (*(int *)(frame_ + FRAME_OFF(24)))
#define x2 (*(int *)(frame_ + FRAME_OFF(28)))
#define height2 (*(int *)(frame_ + FRAME_OFF(32)))
#define width2 (*(int *)(frame_ + FRAME_OFF(36)))
#define hscroll_height (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall sprite_picker_draw(FrameWindow *this)

{
  byte key_color;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption(this);
  gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1d);
  text_set_surface((iptr)this);
  text_set_font((iptr)((u8 *)&g.d_006ab1a0));
  key_color = sprite_get_key_color((Sprite *)&sprite_picker_sprite);
  sprite_editor_key_color = (uint)key_color;
  width2 = sprite_width((Sprite *)&sprite_picker_sprite);
  width2 = width2 * 2;
  height2 = sprite_height((Sprite *)&sprite_picker_sprite);
  height2 = height2 * 2;
  button_height = font_line_spacing((GameFont *)dialog_font_ptr);
  button_height += 8;
  hscroll_height = GetSystemMetrics(3);
  hscroll_height += 2;
  x2 = this->client_x + (int)(this->client_width - width2) / 2;
  y2 = this->client_y + (int)((((this->client_height - height2) - button_height) - hscroll_height) - 4) / 2
  ;
  gfx_fill_rect_xywh((iptr)this,x2,y2,width2,height2,sprite_editor_key_color);
  gfx_set_scale_ratio(2,1);
  sprite_draw_keyed
            ((Sprite *)&sprite_picker_sprite,(iptr)draw_rect,(iptr)this,0,x2,y2);
  gfx_set_scale_ratio(1,1);
  gfx_draw_tiled_frame((iptr)this,x2,y2,width2,height2,6);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef sprite_editor_key_color
#undef draw_rect
#undef button_height
#undef y2
#undef x2
#undef height2
#undef width2
#undef hscroll_height

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
#define cell_count (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl sprite_editor_cell_rect(uint cell,iptr out_x,iptr out_y,iptr out_width,iptr out_height)

{
  uint sign;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)out_height = 0;
  *(i32 *)out_width = *(i32 *)out_height;
  *(i32 *)out_y = *(i32 *)out_width;
  *(i32 *)out_x = *(i32 *)out_y;
  cell_count = *(i32 *)out_x;
  if (sprite_sheet_mode < 0xc) {
    sign = (int)cell >> 0x1f;
    switch(sprite_sheet_mode) {
    case 0:
      cell_count = 0x14;
      *(int *)out_x = ((int)(cell + (sign & 3)) >> 2) * 0x25 + 0x157;
      *(uint *)out_y = (((cell ^ sign) - sign & 3 ^ sign) - sign) * 0x15 + 0xd3;
      *(i32 *)out_width = 0x24;
      *(i32 *)out_height = 0x14;
      break;
    case 1:
      if ((int)cell < 0x18) {
        *(i32 *)out_x = 1;
      }
      else {
        *(i32 *)out_x = 0x14e;
        cell -= 0x18;
      }
      sign = (int)cell >> 0x1f;
      *(uint *)out_x = *(int *)out_x + (((cell ^ sign) - sign & 3 ^ sign) - sign) * 0x41;
      *(int *)out_y = ((int)(cell + (sign & 3)) >> 2) * 0x31 + 0x27;
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x30;
      cell_count = 0x30;
      break;
    case 2:
      cell_count = 4;
      *(uint *)out_x = cell * 0x41 + 0x8f;
      *(i32 *)out_y = 0x1a7;
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x30;
      break;
    case 3:
      cell_count = 0x12;
      *(i32 *)out_width = 0xe;
      *(i32 *)out_height = 0x16;
      *(int *)out_x = (((int)cell >> 1) % 9) * (*(int *)out_width + 1) + 1;
      *(uint *)out_y = (*(int *)out_height + 1) * (cell & 1) + 0x1a9;
      break;
    case 4:
      cell_count = 0x42;
      *(i32 *)out_width = 0x24;
      *(i32 *)out_height = 0x14;
      if ((int)cell < 0x26) {
        *(uint *)out_x = (((cell ^ sign) - sign & 7 ^ sign) - sign) * 0x25 + 0x157;
        *(int *)out_y = ((int)(cell + (sign & 7)) >> 3) * 0x15 + 1;
      }
      else {
        *(int *)out_x = ((int)(cell - 0x26) % 7) * 0x25 + 0x157;
        *(int *)out_y = ((int)(cell - 0x26) / 7) * 0x15 + 0x6a;
      }
      break;
    case 5:
      cell_count = 1;
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x20;
      *(i32 *)out_x = 199;
      *(i32 *)out_y = 0x100;
      break;
    case 6:
      cell_count = 8;
      *(i32 *)out_width = 0x20;
      *(i32 *)out_height = 0x20;
      *(uint *)out_x = (*(int *)out_width + 1) * cell + 1;
      *(i32 *)out_y = 0x164;
      break;
    case 7:
      cell_count = 0x2c;
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x20;
      *(int *)out_x = ((int)cell / 0xb) * 0x41 + 1;
      *(int *)out_y = ((int)cell % 0xb) * 0x21 + 1;
      break;
    case 8:
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x20;
      if ((int)cell < 0x40) {
        *(uint *)out_x = (((cell ^ sign) - sign & 7 ^ sign) - sign) * 0x41 + 1;
        *(uint *)out_y =
             (((int)(((cell ^ sign) - sign & 0xf ^ sign) - sign) < 8) - 1 & 0x21) +
             ((int)(cell + (sign & 0xf)) >> 4) * 0x42 + 0x43;
      }
      else {
        *(uint *)out_x = (cell - 0x40) * 0x41 + 1;
        *(i32 *)out_y = 0x14b;
      }
      cell_count = 0x44;
      break;
    case 9:
      *(i32 *)out_width = 0x20;
      *(i32 *)out_height = 0x10;
      *(i32 *)out_x = 1;
      *(i32 *)out_y = 0x1ad;
      switch(((cell ^ sign) - sign & 3 ^ sign) - sign) {
      case 0:
        break;
      case 1:
        *(int *)out_y = *(int *)out_y + 0x22;
        *(int *)out_x = *(int *)out_x + 0x21;
        break;
      case 2:
        *(int *)out_y = *(int *)out_y + 0x11;
        break;
      case 3:
        *(int *)out_y = *(int *)out_y + 0x22;
      }
      *(int *)out_x = *(int *)out_x + ((int)(cell + (sign & 3)) >> 2) * 0x42;
      cell_count = 0x20;
      break;
    case 10:
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x20;
      *(i32 *)out_x = 0x1c8;
      if ((int)cell < 6) {
        *(uint *)out_y = cell * 0x21 + 100;
      }
      else {
        *(int *)out_x = ((int)(cell - 6) % 9) * 0x41 + 1;
        *(int *)out_y = ((int)(cell - 6) / 9) * 0x21 + 0x16c;
      }
      cell_count = 0x18;
      break;
    case 0xb:
      cell_count = 0x3f;
      *(int *)out_y = ((int)cell / 9) * 0x31 + 1;
      *(int *)out_x = ((int)cell % 9) * 0x41 + 1;
      *(i32 *)out_width = 0x40;
      *(i32 *)out_height = 0x30;
    }
  }
  return cell_count;
}
#undef sprite_sheet_mode
#undef cell_count

/* 00574c47 auto */
#define y2 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define x2 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define height2 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define width2 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl sprite_picker_select_cell(i32 cell)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2);
  sprite_free((Sprite *)&sprite_picker_sprite);
  sprite_grab_from_surface
            ((Sprite *)&sprite_picker_sprite,(iptr)((u8 *)&g.d_006ac0a8),7,x2,y2,width2,height2);
  sprite_picker_redraw_cb();
  return;
}
#undef y2
#undef x2
#undef height2
#undef width2

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
#define wnd_style (*(uint *)(frame_ + FRAME_OFF(0)))
/* WARNING: Removing unreachable block (ram,0x00574e18) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
sprite_picker_create_window(int title,uint style_flags,int x,int y,int width,int height,int resize_border,
            int caption_height,int border_width)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (title == 0) {
    crt_strcpy(&sprite_picker_title,&sprite_picker_default_title);
  }
  else {
    crt_strcpy(&sprite_picker_title,title);
  }
  sprite_picker_text_font_i32 = &ui_text_font;
  sprite_picker_title_font_i32 = &caption_font;
  sprite_picker_title_small_font_i32 = &caption_small_font;
  sprite_picker_style_flags_i32 = style_flags;
  sprite_picker_caption_height = caption_height;
  sprite_picker_border_width = border_width;
  sprite_picker_resize_border = resize_border;
  sprite_picker_caption_button_count_i32 = 0;
  sprite_picker_caption_button_cb_i32 = 0;
  if ((style_flags & 4) != 0) {
    sprite_picker_caption_height = frame_caption_height;
    sprite_picker_border_width = frame_border_width;
  }
  if ((style_flags & 8) == 0) {
    wnd_style = 0x202;
  }
  else {
    wnd_style = 0x802;
  }
  if (sprite_picker_caption_height != 0) {
    wnd_style = wnd_style | 0x400;
  }
  if (resize_border != 0) {
    wnd_style = wnd_style | 0x1000;
  }
  if ((style_flags & 2) == 0) {
    width += sprite_picker_border_width * 2;
    height = height + sprite_picker_caption_height + sprite_picker_border_width;
  }
  if ((style_flags & 1) != 0) {
    x = (screen_width >> 1) - (width >> 1);
    y = (screen_height >> 1) - (height >> 1);
  }
  wnd_create_with_surface
            ((DibSurface *)&sprite_picker_window,0,wnd_style,x,y,width,height,(iptr)((u8 *)&g.d_006a8c00),
             (iptr)((u8 *)&g.d_006ac1f8));
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
#undef wnd_style

/* 00574e98 auto */
#define sprite_editor_key_color (*(uint *)((u8 *)&g.d_006ac874))
#define sprite_picker_dialog (*(int *)((u8 *)&g.d_006ac11c))
#define sprite_picker_running (*(i32 *)((u8 *)&g.d_006ac890))
#define draw_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define height2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define width2 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define grab_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(28)))
void __cdecl sprite_picker_ok_clicked(void)

{
  byte key_color;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_replace_color((Sprite *)&sprite_picker_sprite,9,7);
  width2 = sprite_width((Sprite *)&sprite_picker_sprite);
  height2 = sprite_height((Sprite *)&sprite_picker_sprite);
  key_color = sprite_get_key_color((Sprite *)&sprite_picker_sprite);
  sprite_editor_key_color = (uint)key_color;
  sprite_editor_draw_backdrop();
  sprite_draw((Sprite *)&sprite_picker_sprite,(iptr)draw_rect,(iptr)((u8 *)&g.d_006ac128),0,0);
  sprite_free((Sprite *)&sprite_editor_orig_sprite);
  rect_set_xywh((iptr)grab_rect,0,0,width2,height2);
  sprite_grab_surface_rect((Sprite *)&sprite_editor_orig_sprite,(iptr)((u8 *)&g.d_006ac128),(iptr)grab_rect);
  sprite_picker_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(sprite_picker_dialog + 0x48));
  return;
}
#undef sprite_editor_key_color
#undef sprite_picker_dialog
#undef sprite_picker_running
#undef draw_rect
#undef height2
#undef width2
#undef grab_rect

/* 00574f50 auto */
#define sprite_editor_height (*(i32 *)((u8 *)&g.d_006ac87c))
#define sprite_editor_width (*(i32 *)((u8 *)&g.d_006ac878))
#define sprite_picker_dialog (*(int *)((u8 *)&g.d_006ac11c))
#define sprite_picker_running (*(i32 *)((u8 *)&g.d_006ac890))
#define sprite_sheet_mode (*(i32 *)((u8 *)&g.d_006ac924))
#define draw_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define sheet_half (*(int *)(frame_ + FRAME_OFF(20)))
#define size_col (*(int *)(frame_ + FRAME_OFF(24)))
#define era_row (*(int *)(frame_ + FRAME_OFF(28)))
#define cell (*(uint *)(frame_ + FRAME_OFF(32)))
#define y2 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define x2 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define height2 (*(i32 *)(frame_ + FRAME_OFF(44)))
#define width2 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define half_cell (*(uint *)(frame_ + FRAME_OFF(52)))
#define answer (*(int *)(frame_ + FRAME_OFF(56)))
/* WARNING: Removing unreachable block (ram,0x00574f76) */

void __cdecl sprite_picker_import_all_clicked(void)

{
  uint sign;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  dlg_push_parent_window((iptr)((u8 *)&g.d_006ac4d0));
  answer = popup_text_flags((iptr)((u8 *)&g.d_006359dc),(iptr)((u8 *)&g.d_006341f8),1);
  dlg_pop_parent_window();
  if (answer == 0) {
    switch(sprite_sheet_mode) {
    case 0:
      for (cell = 0; (int)cell < sprite_sheet_cell_count; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        sign = (int)cell >> 0x1f;
        sprite_free
                  ((Sprite *)
                   (&advance_category_icon_sprites +
                   (((cell ^ sign) - sign & 3 ^ sign) - sign) * 0x3c +
                   ((int)(cell + (sign & 3)) >> 2) * 0xf0));
        sign = (int)cell >> 0x1f;
        sprite_editor_grab_from_sheet((iptr)(&advance_category_icon_sprites +
                           ((int)(cell + (sign & 3)) >> 2) * 0xf0 +
                           (((cell ^ sign) - sign & 3 ^ sign) - sign) * 0x3c),x2,
                     y2,width2,height2);
      }
      break;
    case 1:
      for (cell = 0; (int)cell < sprite_sheet_cell_count; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        half_cell = (int)cell % 0x18;
        sign = (int)half_cell >> 0x1f;
        era_row = (int)(half_cell + (sign & 3)) >> 2;
        size_col = ((half_cell ^ sign) - sign & 3 ^ sign) - sign;
        sheet_half = (int)cell / 0x18;
        sprite_free
                  ((Sprite *)
                   (&city_sprites + size_col * 0x78 + era_row * 0x1e0 + sheet_half * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&city_sprites + era_row * 0x1e0 + sheet_half * 0x3c + size_col * 0x78),
                     x2,y2,width2,height2);
      }
      break;
    case 2:
      for (cell = 0; (int)cell < sprite_sheet_cell_count; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        switch(cell) {
        case 0:
          sprite_free((Sprite *)&fortify_overlay_sprites);
          sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_006465d8),x2,y2,width2,height2);
          break;
        case 1:
          sprite_free((Sprite *)&fortress_sprite);
          sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_00646650),x2,y2,width2,height2);
          break;
        case 2:
          sprite_free((Sprite *)&airbase_sprites);
          sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_00647fa0),x2,y2,width2,height2);
          break;
        case 3:
          sprite_free((Sprite *)&airbase_occupied_sprite);
          sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_00647fdc),x2,y2,width2,height2);
        }
      }
      break;
    case 3:
      for (cell = 0; (int)cell < 8; cell++) {
        sprite_editor_cell_rect(cell * 2,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&civ_flag_sprites + cell * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&civ_flag_sprites + cell * 0x78),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell * 2 + 1,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&civ_flag_dark_sprites + cell * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&civ_flag_dark_sprites + cell * 0x78),x2,y2,width2,height2);
      }
      break;
    case 4:
      for (cell = 0; (int)cell < sprite_sheet_cell_count; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        if ((int)cell < 0x26) {
          sprite_free((Sprite *)(&improvement_icon_sprites + (cell * 4 + 4) * 0xf));
          sprite_editor_grab_from_sheet((iptr)(&improvement_icon_sprites + (cell * 4 + 4) * 0xf),x2,y2,width2,
                       height2);
        }
        else {
          sprite_free
                    ((Sprite *)(&wonder_icon_sprites + (cell * 4 - 0x98) * 0xf));
          sprite_editor_grab_from_sheet((iptr)(&wonder_icon_sprites + (cell * 4 - 0x98) * 0xf),x2,y2,
                       width2,height2);
        }
      }
      break;
    case 5:
      break;
    case 6:
      for (cell = 0; (int)cell < sprite_sheet_cell_count; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        sprite_free((Sprite *)(&explosion_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&explosion_sprites + cell * 0x3c),x2,y2,width2,height2);
      }
      break;
    case 7:
      for (cell = 0; (int)cell < 0xb; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        sprite_free((Sprite *)(&terrain_base_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&terrain_base_sprites + cell * 0x3c),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell + 0x16,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&terrain_resource_sprites + cell * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&terrain_resource_sprites + cell * 0x78),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell + 0x21,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&terrain_resource2_sprites + cell * 0x78));
        sprite_editor_grab_from_sheet((iptr)(&terrain_resource2_sprites + cell * 0x78),x2,y2,width2,height2);
      }
      break;
    case 8:
      for (cell = 0; (int)cell < 0x10; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        sprite_free((Sprite *)(&river_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&river_sprites + cell * 0x3c),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell + 0x10,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&forest_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&forest_sprites + cell * 0x3c),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell + 0x20,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&mountain_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&mountain_sprites + cell * 0x3c),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell + 0x30,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&hill_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&hill_sprites + cell * 0x3c),x2,y2,width2,height2);
      }
      for (cell = 0; (int)cell < 4; cell++) {
        sprite_editor_cell_rect(cell + 0x40,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&river_mouth_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&river_mouth_sprites + cell * 0x3c),x2,y2,width2,height2);
      }
      break;
    case 9:
      for (cell = 0; (int)cell < 8; cell++) {
        sprite_editor_cell_rect(cell << 2,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&coast_quarter_sprites + cell * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_sprites + cell * 0xf0),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell * 4 + 1,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&coast_quarter_east_sprites + cell * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_east_sprites + cell * 0xf0),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell * 4 + 2,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&coast_quarter_south_sprites + cell * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_south_sprites + cell * 0xf0),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell * 4 + 3,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&coast_quarter_west_sprites + cell * 0xf0));
        sprite_editor_grab_from_sheet((iptr)(&coast_quarter_west_sprites + cell * 0xf0),x2,y2,width2,height2);
      }
      break;
    case 10:
      for (cell = 0; (int)cell < 3; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        sprite_free((Sprite *)(&land_improvement_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&land_improvement_sprites + cell * 0x3c),x2,y2,width2,height2);
      }
      sprite_editor_cell_rect(3,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2);
      sprite_free((Sprite *)&pollution_sprite);
      sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_00641808),x2,y2,width2,height2);
      sprite_editor_cell_rect(4,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2);
      sprite_free((Sprite *)&grassland_shield_sprite);
      sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_0063fc18),x2,y2,width2,height2);
      sprite_editor_cell_rect(5,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2);
      sprite_free((Sprite *)&hut_sprite);
      sprite_editor_grab_from_sheet((iptr)((u8 *)&g.d_00646158),x2,y2,width2,height2);
      for (cell = 0; (int)cell < 9; cell++) {
        sprite_editor_cell_rect(cell + 6,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&road_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&road_sprites + cell * 0x3c),x2,y2,width2,height2);
        sprite_editor_cell_rect(cell + 0xf,(iptr)&x2,(iptr)&y2,(iptr)&width2,
                           (iptr)&height2);
        sprite_free((Sprite *)(&railroad_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&railroad_sprites + cell * 0x3c),x2,y2,width2,height2);
      }
      break;
    case 0xb:
      for (cell = 0; (int)cell < sprite_sheet_cell_count; cell++) {
        sprite_editor_cell_rect(cell,(iptr)&x2,(iptr)&y2,(iptr)&width2,(iptr)&height2)
        ;
        sprite_free((Sprite *)(&unit_sprites + cell * 0x3c));
        sprite_editor_grab_from_sheet((iptr)(&unit_sprites + cell * 0x3c),x2,y2,width2,height2);
      }
    }
    sprite_free((Sprite *)&sprite_editor_orig_sprite);
    sprite_merge_onto(sprite_editor_target_sprite,(iptr)((u8 *)&g.d_006ac170));
    surface_create((DibSurface *)&sprite_editor_surface,sprite_editor_width,sprite_editor_height);
    sprite_editor_draw_backdrop();
    sprite_draw((Sprite *)&sprite_editor_orig_sprite,(iptr)draw_rect,(iptr)((u8 *)&g.d_006ac128),0,0);
    sprite_free((Sprite *)&sprite_editor_result_sprite);
    sprite_merge_onto(sprite_editor_target_sprite,(iptr)((u8 *)&g.d_006ac8a8));
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
#undef draw_rect
#undef sheet_half
#undef size_col
#undef era_row
#undef cell
#undef y2
#undef x2
#undef height2
#undef width2
#undef half_cell
#undef answer

/* 00575d89 auto */
void __cdecl
sprite_editor_grab_from_sheet(iptr sprite,i32 x,i32 y,i32 width,
            i32 height)

{
  sprite_grab_from_surface((Sprite *)sprite,(iptr)((u8 *)&g.d_006ac0a8),7,x,y,width,height);
  sprite_replace_color((Sprite *)sprite,9,7);
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
#define cancel_parent (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define import_parent (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define ok_parent (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define scroll_parent (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define dummy_out (*(i8 (*)[4])(frame_ + FRAME_OFF(20)))
#define y2 (*(int *)(frame_ + FRAME_OFF(24)))
#define x2 (*(int *)(frame_ + FRAME_OFF(28)))
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define scroll_height (*(iptr *)(frame_ + FRAME_OFF(48)))
void __thiscall sprite_picker_run(ViewWindow *this)

{
  i32 title;
  int metric;
  iptr label;
  i32 style_flags;
  i32 win_x;
  i32 win_y;
  u32 win_width;
  u32 win_height;
  i32 resize_border;
  i32 caption_height;
  i32 border_width;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  sprite_picker_dialog = this;
  this->rates_civ = 0xf0;
  this->max_rate_value = 0xf0;
  border_width = 0;
  caption_height = 0;
  resize_border = 0;
  win_height = this->max_rate_value;
  win_width = this->rates_civ;
  win_y = 0;
  win_x = 0;
  style_flags = 0xd;
  title = label_string(*(i32 *)(label_string_ids + 0x950));
  sprite_picker_create_window(title,style_flags,win_x,win_y,win_width,win_height,resize_border,caption_height,border_width);
  metric = font_line_spacing((GameFont *)dialog_font_ptr);
  this->init_sci_rate = metric + 8;
  this->init_lux_rate = this->client_width - 4;
  metric = GetSystemMetrics(3);
  scroll_height = metric + 2;
  this->sci_rate_sel = this->client_width - 4;
  y2 = ((this->client_y + this->client_height) - (this->init_sci_rate + 2)) - (metric + 4);
  x2 = this->client_x + 2;
  sprite_sheet_cell_count = sprite_editor_cell_rect(0,(iptr)dummy_out,(iptr)dummy_out,(iptr)dummy_out,(iptr)dummy_out);
  rect_set_xywh((iptr)rect,x2,y2,this->sci_rate_sel,scroll_height);
  if (this == (ViewWindow *)0x0) {
    scroll_parent = (u8 *)0x0;
  }
  else {
    scroll_parent = this->window_2;
  }
  scrollbar_create
            ((Control *)&this->dialog_w,(iptr)scroll_parent,0x65,(iptr)rect,0);
  scrollbar_set_range((Control *)&this->dialog_w,0,sprite_sheet_cell_count - 1);
  scrollbar_set_pos((ClickControl *)&this->dialog_w,0);
  scrollbar_set_callback((Control *)&this->dialog_w,(iptr)sprite_picker_select_cell);
  sprite_picker_select_cell(0);
  ctrl_show_and_redraw((Control *)&this->dialog_w);
  this->init_lux_rate = (int)(this->client_width - 8) / 3;
  y2 = (this->client_y + this->client_height) - (this->init_sci_rate + 2);
  x2 = this->client_x + 2;
  rect_set_xywh((iptr)rect,x2,y2,this->init_lux_rate,this->init_sci_rate);
  if (this == (ViewWindow *)0x0) {
    ok_parent = (u8 *)0x0;
  }
  else {
    ok_parent = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this->sci_label_y,(iptr)ok_parent,0xc9,(iptr)rect,label);
  button_set_callback((Control *)&this->sci_label_y,(iptr)sprite_picker_ok_clicked);
  ctrl_set_default_button((Control *)&this->sci_label_y);
  x2 = x2 + this->init_lux_rate + 2;
  rect_set_xywh((iptr)rect,x2,y2,this->init_lux_rate,this->init_sci_rate);
  if (this == (ViewWindow *)0x0) {
    import_parent = (u8 *)0x0;
  }
  else {
    import_parent = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x954));
  button_create
            ((Control *)(this->import_all_button),(iptr)import_parent,0xc9,(iptr)rect,label);
  button_set_callback((Control *)(this->import_all_button),(iptr)sprite_picker_import_all_clicked);
  ctrl_set_default_button((Control *)(this->import_all_button));
  if (sprite_sheet_mode == 5) {
    ctrl_disable((Control *)(this->import_all_button));
  }
  x2 = x2 + this->init_lux_rate + 2;
  rect_set_xywh((iptr)rect,x2,y2,this->init_lux_rate,this->init_sci_rate);
  if (this == (ViewWindow *)0x0) {
    cancel_parent = (u8 *)0x0;
  }
  else {
    cancel_parent = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this->fill_rect_top,(iptr)cancel_parent,0xca,(iptr)rect,label);
  button_set_callback((Control *)&this->fill_rect_top,(iptr)sprite_picker_cancel_clicked);
  ctrl_set_cancel_button((Control *)&this->fill_rect_top);
  wnd_set_redraw_callback((SurfaceWindow *)this,(iptr)sprite_picker_redraw_cb);
  wnd_repaint((SurfaceWindow *)this);
  window_show((WindowObjectView *)this);
  wnd_run_modal_loop((ModalMenuWindow *)this->window_2);
  while (sprite_picker_running != 0) {
    win_pump_one_message();
  }
  frame_wnd_close((DibSurface *)this);
  return;
}
#undef sprite_picker_dialog
#undef sprite_picker_running
#undef sprite_sheet_mode
#undef cancel_parent
#undef import_parent
#undef ok_parent
#undef scroll_parent
#undef dummy_out
#undef y2
#undef x2
#undef rect
#undef scroll_height

/* 0057624d auto */
void __cdecl sprite_picker_show(void)

{
  sprite_picker_run((ViewWindow *)&sprite_picker_window);
  return;
}

/* 00576267 auto */
#define sprite_sheet_mode (*(int *)((u8 *)&g.d_006ac924))
#define prompt (*(char (*)[132])(frame_ + FRAME_OFF(0)))
#define retry (*(int *)(frame_ + FRAME_OFF(132)))
#define file_path (*(char (*)[260])(frame_ + FRAME_OFF(136)))
#define sheet_name (*(char * *)(frame_ + FRAME_OFF(396)))
#define filter (*(char (*)[260])(frame_ + FRAME_OFF(400)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(660)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(1736)))
#define file_name (*(char * *)(frame_ + FRAME_OFF(2492)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(2496)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(2500)))
#define seh_state (*(uint *)(frame_ + FRAME_OFF(2504)))
/* WARNING: Removing unreachable block (ram,0x0057656d) */
/* WARNING: Removing unreachable block (ram,0x005763fb) */
/* WARNING: Removing unreachable block (ram,0x00576601) */

void __cdecl sprite_editor_import_sheet(void)

{
  i32 label;
  iptr ok;
  size_t _MaxCount;
  iptr cmp;
  int result;
  char *str;
  i32 arg_a;
  char *arg_name;
  i32 arg_b;
  LPCSTR pCVar9;
  LPCSTR pCVar10;
  i32 arg_c;
  UINT UVar12;
  i8 frame_[FRAME_OFF(2512)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  palette_init(&palette);
  seh_state = 0;
  dialog_ctor(&dialog2,0x4000);
  seh_state = CONCAT31((*(i32 *)((char *)&seh_state + 1)),1);
  switch(sprite_sheet_mode) {
  case 0:
  case 4:
  case 5:
  case 6:
    sheet_name = s_ICONS_00634210;
    break;
  case 1:
  case 2:
  case 3:
    sheet_name = s_CITIES_00634218;
    break;
  case 7:
  case 8:
  case 9:
  case 10:
    sheet_name = s_TERRAIN_00634208;
    break;
  case 0xb:
    sheet_name = s_UNITS_00634200;
  }
  do {
    arg_c = 0;
    arg_b = 0;
    arg_a = 0;
    str = sheet_name;
    arg_name = sheet_name;
    label = label_string(*(i32 *)(label_string_ids + 0x958));
    _sprintf(filter,s__s__s_c_s__BMP__s__GIF_c_c_00634220,sheet_name,label,arg_a,str,arg_name,
             arg_b,arg_c);
    _sprintf(file_path,s__s__BMP__s__GIF_0063423c,sheet_name,sheet_name);
    str = sheet_name;
    label = label_string(*(i32 *)(label_string_ids + 0x95c));
    _sprintf(prompt,s__s__s_0063424c,label,str);
    ok = ui_file_name_dialog((iptr)((u8 *)&g.d_006ac1f8),(iptr)prompt,(iptr)file_path,(iptr)filter,(iptr)((u8 *)&g.d_00634254),1,0
                              );
    if (ok == 0) goto LAB_00576783;
    __strupr(file_path);
    retry = 1;
    file_name = _strrchr(file_path,0x5c);
    if (file_name == (char *)0x0) {
      file_name = file_path;
    }
    else {
      file_name++;
    }
    _MaxCount = _strlen(sheet_name);
    cmp = _strncmp(file_name,sheet_name,_MaxCount);
    if (cmp == 0) {
      if ((sprite_sheet_mode == 7) || (sprite_sheet_mode == 10)) {
        result = _isdigit((int)file_name[7]);
        if ((result != 0) && ((file_name[7] & 1U) != 0)) goto LAB_00576631;
        dlg_push_parent_window((iptr)((u8 *)&g.d_006ac4d0));
        popup_debug_text((iptr)((u8 *)&g.d_00634264));
        dlg_pop_parent_window();
      }
      else if (((sprite_sheet_mode == 8) || (sprite_sheet_mode == 9)) &&
              ((result = _isdigit((int)file_name[7]), result == 0 || ((file_name[7] & 1U) != 0)))) {
        dlg_push_parent_window((iptr)((u8 *)&g.d_006ac4d0));
        popup_debug_text((iptr)((u8 *)&g.d_00634270));
        dlg_pop_parent_window();
      }
      else {
LAB_00576631:
        str = _strstr(file_path,&sprite_import_bmp_ext_str);
        if (str == (char *)0x0) {
          str = _strstr(file_path,&sprite_import_gif_ext_str);
          if (str == (char *)0x0) {
            UVar12 = 0x10;
            pCVar10 = (LPCSTR)0x0;
            pCVar9 = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x968));
            result = wnd_get_window((WndBase *)&sprite_editor_wnd);
            MessageBoxA(*(HWND *)(result + 4),pCVar9,pCVar10,UVar12);
          }
          else {
            result = surface_load_gif_file
                              ((DibSurface *)&sprite_sheet_surface,(iptr)file_path,10,0xc0,
                               (iptr)&palette);
            if (result == 0) {
              UVar12 = 0x10;
              pCVar10 = (LPCSTR)0x0;
              pCVar9 = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x964));
              result = wnd_get_window((WndBase *)&sprite_editor_wnd);
              MessageBoxA(*(HWND *)(result + 4),pCVar9,pCVar10,UVar12);
            }
            else {
              retry = 0;
            }
          }
        }
        else {
          result = gfx_load_bmp_640x480((iptr)((u8 *)&g.d_006ac0a8),(iptr)file_path,10,0xc0,(iptr)&palette);
          if (result == 0) {
            UVar12 = 0x10;
            pCVar10 = (LPCSTR)0x0;
            pCVar9 = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x964));
            result = wnd_get_window((WndBase *)&sprite_editor_wnd);
            MessageBoxA(*(HWND *)(result + 4),pCVar9,pCVar10,UVar12);
          }
          else {
            retry = 0;
          }
        }
      }
    }
    else {
      str = sheet_name;
      label = label_string(*(i32 *)(label_string_ids + 0x960));
      _sprintf(prompt,s__s___s__0063425c,label,str);
      UVar12 = 0x40;
      pCVar9 = (LPCSTR)0x0;
      str = prompt;
      result = wnd_get_window((WndBase *)&sprite_editor_wnd);
      MessageBoxA(*(HWND *)(result + 4),str,pCVar9,UVar12);
    }
  } while (retry != 0);
  sprite_picker_show();
  sprite_editor_redraw();
LAB_00576783:
  surface_release((DibSurface *)&sprite_sheet_surface);
  seh_state = seh_state & 0xffffff00;
  /* inlined unwind funclet 005767a7 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 005767b3 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef sprite_sheet_mode
#undef prompt
#undef retry
#undef file_path
#undef sheet_name
#undef filter
#undef palette
#undef dialog2
#undef file_name
#undef seh_handler
#undef seh_next
#undef seh_state

/* 00578390 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CBitmapButton::~CBitmapButton(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall sprite_picker_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&seh_state + 1)) = 0;
  (*(i8 *)((char *)&seh_state + 0)) = 3;
  /* inlined unwind funclet 00578402 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x3b0)); }
  (*(i8 *)((char *)&seh_state + 0)) = 2;
  /* inlined unwind funclet 00578411 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x374)); }
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  /* inlined unwind funclet 00578420 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x338)); }
  seh_state = (uint)(*(i32 *)((char *)&seh_state + 1)) << 8;
  /* inlined unwind funclet 0057842f */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x2f8)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0057843e */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef seh_handler
#undef seh_next
#undef seh_state

/* 005784a0 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
ViewWindow * __thiscall sprite_picker_ctor(ViewWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  seh_state = 0;
  scrollbar_ctor((Control *)&this->dialog_w);
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  button_ctor((Control *)&this->sci_label_y);
  (*(i8 *)((char *)&seh_state + 0)) = 2;
  button_ctor((Control *)(this->import_all_button));
  seh_state = CONCAT31((*(i32 *)((char *)&seh_state + 1)),3);
  button_ctor((Control *)&this->fill_rect_top);
  this->vtable = (u32)&PTR_FUN_0061d6fc;
  return this;
}
#undef seh_handler
#undef seh_next
#undef seh_state

/* 005a9780 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl gfx_set_draw_target(iptr surface)

{
  gfx_draw_target = surface;
  return;
}
#undef gfx_draw_target

/* 005a9798 auto */
void __cdecl
gfx_draw_line_color(iptr surface,i32 x1,i32 y1,i32 x2,
            i32 y2,i32 color)

{
  gfx_set_text_color_index(color);
  surface_draw_line((DibSurface *)surface,x1,y1,x2,y2);
  return;
}

/* 005a97cc auto */
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl
gfx_draw_hline(iptr surface,i32 x1,int x2,int y,i32 color)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set((iptr)rect,x1,y,x2 + 1,y + 1);
  gfx_fill_rect(surface,(iptr)rect,color);
  return;
}
#undef rect

/* 005a9858 auto */
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl
gfx_draw_vline(iptr surface,int x,i32 y1,int y2,i32 color)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set((iptr)rect,x,y1,x + 1,y2 + 1);
  gfx_fill_rect(surface,(iptr)rect,color);
  return;
}
#undef rect

/* 005a98e4 auto */
void __cdecl
gfx_draw_box_ltrb(iptr surface,i32 left,i32 top,i32 right,
            i32 bottom,i32 color)

{
  gfx_draw_hline(surface,left,right,top,color);
  gfx_draw_hline(surface,left,right,bottom,color);
  gfx_draw_vline(surface,left,top,bottom,color);
  gfx_draw_vline(surface,right,top,bottom,color);
  return;
}

/* 005a9964 auto */
void __cdecl
gfx_draw_frame_rect(iptr surface,int x,int y,int width,iptr height,i32 color)

{
  gfx_draw_hline(surface,x,width + x - 1,y,color);
  gfx_draw_hline(surface,x,width + x - 1,height + y - 1,color);
  gfx_draw_vline(surface,x,y,height + y - 1,color);
  gfx_draw_vline(surface,width + x - 1,y,height + y - 1,color);
  return;
}

/* 005a99fc auto */
void __cdecl gfx_draw_bevel_rect(iptr surface,iptr rect,i32 light_color,i32 dark_color)

{
  gfx_draw_hline(surface,*(i32 *)rect,*(int *)(rect + 8) - 1,
                     *(i32 *)(rect + 4),light_color);
  gfx_draw_vline(surface,*(i32 *)rect,*(i32 *)(rect + 4),
                     *(int *)(rect + 0xc) - 1,light_color);
  gfx_draw_hline(surface,*(i32 *)rect,*(int *)(rect + 8) - 1,
                     *(int *)(rect + 0xc) - 1,dark_color);
  gfx_draw_vline(surface,*(int *)(rect + 8) - 1,*(i32 *)(rect + 4),
                     *(int *)(rect + 0xc) - 1,dark_color);
  return;
}

/* 005a9aa3 auto */
void __cdecl gfx_fill_surface(iptr surface,i32 color)

{
  surface_fill((DibSurface *)surface,color);
  return;
}

/* 005a9abf auto */
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl
gfx_fill_rect_xywh(iptr surface,i32 x,i32 y,iptr width,iptr height,
            i32 color)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)rect,x,y,width,height);
  surface_fill_rect((DibSurface *)surface,(iptr)rect,color);
  return;
}
#undef rect

/* 005a9afe auto */
#define dest_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define src_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl
gfx_copy_rect_xywh(iptr src,iptr dest,i32 src_x,i32 src_y,i32 dest_x,
            i32 dest_y,iptr width,iptr height)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)src_rect,src_x,src_y,width,height);
  rect_set_xywh((iptr)dest_rect,dest_x,dest_y,width,height);
  surface_blit((DibSurface *)src,dest,(iptr)src_rect,(iptr)dest_rect);
  return;
}
#undef dest_rect
#undef src_rect

/* 005a9b5d auto */
#define dist_y (*(int *)(frame_ + FRAME_OFF(0)))
#define dist_x (*(int *)(frame_ + FRAME_OFF(4)))
#define cur_x (*(int *)(frame_ + FRAME_OFF(8)))
#define src_y (*(int *)(frame_ + FRAME_OFF(12)))
#define src_x (*(int *)(frame_ + FRAME_OFF(16)))
#define cur_y (*(int *)(frame_ + FRAME_OFF(48)))
int __cdecl
gfx_tile_fill(iptr dest,iptr tile,int x,int y,int width,int height,int origin_x,
            int origin_y)

{
  int tile_width;
  int tile_height;
  int right;
  int bottom;
  int end_x;
  int span;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  tile_width = surface_width((DibSurface *)tile);
  tile_height = surface_height((DibSurface *)tile);
  cur_y = tile_height;
  if ((tile_width != 0) && (tile_height != 0)) {
    if (x == origin_x || x - origin_x < 0) {
      dist_x = ~(x - origin_x) + 1;
    }
    else {
      dist_x = x - origin_x;
    }
    if (y == origin_y || y - origin_y < 0) {
      dist_y = ~(y - origin_y) + 1;
    }
    else {
      dist_y = y - origin_y;
    }
    src_y = dist_y % tile_height;
    right = width + x;
    bottom = height + y;
    for (cur_y = y; cur_y < bottom; cur_y += span) {
      src_x = dist_x % tile_width;
      for (cur_x = x; cur_x < right; cur_x += span) {
        end_x = (cur_x + tile_width) - src_x;
        span = (tile_height + cur_y) - src_y;
        if (right <= end_x) {
          end_x = right;
        }
        if (bottom <= span) {
          span = bottom;
        }
        gfx_copy_rect_xywh(tile,dest,src_x,src_y,cur_x,cur_y,end_x - cur_x,
                           span - cur_y);
        span = tile_width - src_x;
        src_x = 0;
      }
      span = tile_height - src_y;
      src_y = 0;
    }
  }
  return cur_y;
}
#undef dist_y
#undef dist_x
#undef cur_x
#undef src_y
#undef src_x
#undef cur_y

/* 005ae006 auto */
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define count (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl bits_count8(uint bits)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  count = 0;
  for (i = 0; i < 8; i++) {
    if ((bits & 1) != 0) {
      count++;
    }
    bits = (int)bits >> 1;
  }
  return count;
}
#undef i
#undef count

/* 005ae3bf auto */
void __cdecl bit_index_split(iptr bit_index,iptr out_byte,iptr out_mask)

{
  *(iptr *)out_byte = bit_index >> 3;
  *(int *)out_mask = 1 << ((byte)bit_index & 7);
  return;
}

/* 005bb3f0 auto */
void __thiscall
surface_wnd_create
          (DibSurface *this,iptr parent,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette)

{
  iptr window;
  
  wnd_create_framed
            ((WndBase *)(this + 1),parent,style,x,y,width,height,palette);
  surface_create(this,width,height);
  surface_set_palette(this,palette);
  window = wnd_get_window((WndBase *)(this + 1));
  wnd_install_paint_proc((iptr)this,window);
  return;
}

/* 005bcaa7 auto */
void __cdecl gfx_get_screen_rect(iptr rect)

{
  int yBottom;
  int xRight;
  
  yBottom = GetSystemMetrics(1);
  xRight = GetSystemMetrics(0);
  SetRect((LPRECT)rect,0,0,xRight,yBottom);
  return;
}

/* 005bcc11 auto */
void __cdecl
dib_blit_to_wnd_obj(iptr src,int src_x,int src_y,int width,int height,iptr dest,int dest_x,
            int dest_y)

{
  if ((src != 0) && (dest != 0)) {
    if ((*(int *)(dest + 0x18) != 0) && (gfx_palettized_display == 1)) {
      RealizePalette(*(HDC *)(dest + 8));
    }
    BitBlt(*(HDC *)(dest + 8),dest_x,dest_y,width,height,*(HDC *)(src + 4),src_x,
           src_y,0xcc0020);
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
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall surface_create(DibSurface *this,int width,int height)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&rect,0,0,width,height);
  surface_alloc_dib8(this,(iptr)&rect);
  return;
}
#undef rect

/* 005bd696 auto */
i32 __thiscall surface_alloc_dib8(DibSurface *this,iptr rect)

{
  char locked;
  u32 new_dib;
  int dim;
  
  if (this->dib != 0) {
    locked = surface_is_locked(this);
    if (locked != '\0') {
      surface_unlock(this);
    }
    new_dib = dib_destroy(this->dib);
    this->dib = new_dib;
  }
  if (((rect != 0) && (dim = rect_width(rect), dim != 0)) &&
     (dim = rect_height(rect), dim != 0)) {
    surface_set_dims(this,rect);
    new_dib = dib_create((iptr)&this->bounds_rect);
    this->dib = new_dib;
    if (this->dib != 0) {
      new_dib = dib_get_stride(this->dib);
      this->stride = new_dib;
      dim = dib_is_top_down(this->dib);
      if (dim == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,(iptr)((u8 *)&g.d_00636774),(iptr)((u8 *)&g.d_0063675c),0x71);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005bd813 auto */
void __thiscall surface_set_dims(DibSurface *this,int *rect)

{
  this->bits = 0;
  this->dib = 0;
  this->palette_version = 0;
  this->stride = 0;
  this->signed_pitch = 0;
  this->bytes_per_pixel = 1;
  if (rect == (int *)0x0) {
    this->pixel_height = 0;
    this->pixel_width = 0;
    SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
    SetRect((LPRECT)&this->clip_left,0,0,0,0);
  }
  else {
    this->pixel_height = rect[3] - rect[1];
    this->pixel_width = rect[2] - *rect;
    SetRect((LPRECT)&this->bounds_rect,0,0,this->pixel_width,this->pixel_height);
    SetRect((LPRECT)&this->clip_left,0,0,this->pixel_width,this->pixel_height);
  }
  return;
}

/* 005bd915 auto */
#define draw_current_surface (*(DibSurface * *)((u8 *)&g.d_00637e58))
DibSurface * __thiscall surface_dtor(DibSurface *this)

{
  char locked;
  u32 new_dib;
  
  this->vtable = (u32)&PTR_FUN_0061d70c;
  locked = surface_is_locked(this);
  if (locked != '\0') {
    surface_unlock(this);
  }
  new_dib = dib_destroy(this->dib);
  this->dib = new_dib;
  surface_set_dims(this,0);
  if (draw_current_surface == this) {
    draw_current_surface = (DibSurface *)0x0;
  }
  return this;
}
#undef draw_current_surface

/* 005bf071 auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define mem (*(int *)(frame_ + FRAME_OFF(20)))
#define buffer (*(iptr *)(frame_ + FRAME_OFF(24)))
#define height2 (*(int *)(frame_ + FRAME_OFF(28)))
#define file (*(FileObject *)(frame_ + FRAME_OFF(32)))
#define width2 (*(int *)(frame_ + FRAME_OFF(184)))
#define lzw_min_code (*(byte *)(frame_ + FRAME_OFF(188)))
#define data (*(char * *)(frame_ + FRAME_OFF(192)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(196)))
#define image_desc (*(char * *)(frame_ + FRAME_OFF(200)))
#define image_data (*(char * *)(frame_ + FRAME_OFF(204)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(208)))
#define seh_next (*(i8 * *)(frame_ + FRAME_OFF(212)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(216)))
i32 __thiscall
surface_load_gif_file(DibSurface *this,iptr filename,uint first_color,uint color_count,iptr palette)

{
  int result;
  i32 ret;
  uint table_size;
  i8 frame_[FRAME_OFF(224)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  file_obj_init(&file);
  seh_state = 0;
  result = file_obj_open(&file,filename);
  if (result == 0) {
    seh_state = 0xffffffff;
    /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
    ret = 0;
  }
  else {
    ret = file_obj_get_size(&file);
    mem = mem_handle_alloc(ret);
    win_flush_pending_msgs();
    if (mem == 0) {
      seh_state = 0xffffffff;
      /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
      ret = 0;
    }
    else {
      buffer = mem_handle_lock(mem);
      ret = file_obj_get_size(&file);
      file_obj_read(&file,buffer,ret);
      buffer = mem_handle_unlock(mem);
      win_flush_pending_msgs();
      if (mem == 0) {
        dbg_logf_str((iptr)((u8 *)&g.d_00636c40),filename);
        err_report((ErrorContext *)&err_report_ctx,3,(iptr)((u8 *)&g.d_00636c7c),(iptr)((u8 *)&g.d_00636c64),0x382);
        seh_state = 0xffffffff;
        /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
        ret = 0;
      }
      else {
        data = (char *)mem_handle_lock(mem);
        result = _strncmp(data,&gif_sig_file,3);
        if (result == 0) {
          if ((data[10] & 0x80U) == 0) {
            dbg_logf_str((iptr)((u8 *)&g.d_00636ce4),filename);
            mem_handle_unlock(mem);
            mem_handle_free(mem);
            err_report((ErrorContext *)&err_report_ctx,4,(iptr)((u8 *)&g.d_00636d28),(iptr)((u8 *)&g.d_00636d10),0x396);
            seh_state = 0xffffffff;
            /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
            ret = 0;
          }
          else {
            table_size = 1 << (data[10] & 7U) + 1;
            cursor = data + 0xd;
            win_flush_pending_msgs();
            if (palette != 0) {
              win_flush_pending_msgs();
              if (0x100 < (int)(color_count + first_color)) {
                color_count = 0x100 - first_color;
              }
              if (table_size <= color_count) {
                color_count = table_size;
              }
              palette_set_rgb((GamePalette *)palette,first_color,color_count,(iptr)cursor)
              ;
              win_flush_pending_msgs();
            }
            for (cursor = data + table_size * 3 + 0xd; *cursor == '\0'; cursor++)
            {
            }
            if ((*cursor == ',') || (*cursor == '!')) {
              image_desc = cursor + 1;
              width2 = endian_from_le((uint)*(ushort *)(cursor + 5));
              height2 = endian_from_le((uint)*(ushort *)(image_desc + 6));
              if ((image_desc[8] & 0x80U) != 0) {
                dbg_log((iptr)((u8 *)&g.d_00636d8c));
              }
              SetRect(&rect,0,0,width2,height2);
              result = surface_resize(this,(iptr)&rect);
              if (result == 0) {
                mem_handle_unlock(mem);
                mem_handle_free(mem);
                seh_state = 0xffffffff;
                /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
                ret = 0;
              }
              else {
                lzw_min_code = image_desc[9];
                image_data = image_desc + 10;
                win_flush_pending_msgs();
                gif_lzw_decode((iptr)image_data,first_color,
                             CONCAT22((short)(this->stride >> 0x10),(ushort)lzw_min_code),this->stride
                             ,width2,height2,this->bits);
                win_flush_pending_msgs();
                surface_set_palette(this,palette);
                result = dib_is_top_down(this->dib);
                if (result == 0) {
                  dib_flip_vertical(this->dib);
                }
                mem_handle_unlock(mem);
                mem_handle_free(mem);
                file_map_close(&file);
                seh_state = 0xffffffff;
                /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
                ret = 1;
              }
            }
            else {
              dbg_logf_str((iptr)((u8 *)&g.d_00636d3c),filename);
              mem_handle_unlock(mem);
              mem_handle_free(mem);
              err_report((ErrorContext *)&err_report_ctx,4,(iptr)((u8 *)&g.d_00636d78),(iptr)((u8 *)&g.d_00636d60),0x3b3);
              seh_state = 0xffffffff;
              /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
              ret = 0;
            }
          }
        }
        else {
          dbg_logf_str((iptr)((u8 *)&g.d_00636c98),filename);
          mem_handle_unlock(mem);
          mem_handle_free(mem);
          err_report((ErrorContext *)&err_report_ctx,4,(iptr)((u8 *)&g.d_00636cd0),(iptr)((u8 *)&g.d_00636cb8),0x38d);
          seh_state = 0xffffffff;
          /* inlined unwind funclet 005bf5ba */ { file_obj_close((FileObject *)((iptr)&file)); }
          ret = 0;
        }
      }
    }
  }
  return ret;
}
#undef rect
#undef mem
#undef buffer
#undef height2
#undef file
#undef width2
#undef lzw_min_code
#undef data
#undef cursor
#undef image_desc
#undef image_data
#undef seh_handler
#undef seh_next
#undef seh_state

/* 005bf5e1 auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define res (*(int *)(frame_ + FRAME_OFF(16)))
#define res_type (*(i8 *)(frame_ + FRAME_OFF(20)))
#define res_type_1 (*(i8 *)(frame_ + FRAME_OFF(21)))
#define res_type_2 (*(i8 *)(frame_ + FRAME_OFF(22)))
#define res_type_3 (*(i8 *)(frame_ + FRAME_OFF(23)))
#define height2 (*(int *)(frame_ + FRAME_OFF(24)))
#define width2 (*(int *)(frame_ + FRAME_OFF(28)))
#define lzw_min_code (*(byte *)(frame_ + FRAME_OFF(32)))
#define data (*(char * *)(frame_ + FRAME_OFF(36)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(40)))
#define image_desc (*(char * *)(frame_ + FRAME_OFF(44)))
#define image_data (*(char * *)(frame_ + FRAME_OFF(48)))
i32 __thiscall
surface_load_gif_resource(DibSurface *this,iptr res_id,uint first_color,uint color_count,iptr palette)

{
  i32 ret;
  int result;
  uint table_size;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  res_type = 0x47;
  res_type_1 = 0x49;
  res_type_2 = 0x46;
  res_type_3 = 0x53;
  res = res_load((iptr)&res_type,res_id);
  if (res == 0) {
    dbg_logf((iptr)((u8 *)&g.d_00636db0),res_id);
    err_report((ErrorContext *)&err_report_ctx,3,(iptr)((u8 *)&g.d_00636dec),(iptr)((u8 *)&g.d_00636dd4),0x3f4);
    ret = 0;
  }
  else {
    data = (char *)res_lock(res);
    result = _strcmp(data,&gif_sig_resource);
    if (result == 0) {
      dbg_logf((iptr)((u8 *)&g.d_00636e08),res_id);
      res_unlock(res);
      res_free(res);
      err_report((ErrorContext *)&err_report_ctx,4,(iptr)((u8 *)&g.d_00636e40),(iptr)((u8 *)&g.d_00636e28),0x3ff);
      ret = 0;
    }
    else if ((data[10] & 0x80U) == 0) {
      dbg_logf((iptr)((u8 *)&g.d_00636e54),res_id);
      res_unlock(res);
      res_free(res);
      err_report((ErrorContext *)&err_report_ctx,4,(iptr)((u8 *)&g.d_00636e98),(iptr)((u8 *)&g.d_00636e80),0x408);
      ret = 0;
    }
    else {
      table_size = 1 << (data[10] & 7U) + 1;
      cursor = data + 0xd;
      if (palette != 0) {
        if (0x100 < (int)(color_count + first_color)) {
          color_count = 0x100 - first_color;
        }
        if (table_size <= color_count) {
          color_count = table_size;
        }
        palette_set_rgb((GamePalette *)palette,first_color,color_count,(iptr)cursor);
      }
      win_flush_pending_msgs();
      for (cursor = data + table_size * 3 + 0xd; *cursor == '\0'; cursor++) {
      }
      if ((*cursor == ',') || (*cursor == '!')) {
        image_desc = cursor + 1;
        width2 = endian_from_le((uint)*(ushort *)(cursor + 5));
        height2 = endian_from_le((uint)*(ushort *)(image_desc + 6));
        if ((image_desc[8] & 0x80U) != 0) {
          dbg_log((iptr)((u8 *)&g.d_00636efc));
        }
        SetRect(&rect,0,0,width2,height2);
        surface_resize(this,(iptr)&rect);
        lzw_min_code = image_desc[9];
        image_data = image_desc + 10;
        win_flush_pending_msgs();
        gif_lzw_decode((iptr)image_data,first_color,CONCAT22((short)(this->stride >> 0x10),(ushort)lzw_min_code)
                     ,this->stride,width2,height2,this->bits);
        win_flush_pending_msgs();
        surface_set_palette(this,palette);
        result = dib_is_top_down(this->dib);
        if (result == 0) {
          dib_flip_vertical(this->dib);
        }
        res_unlock(res);
        res_free(res);
        ret = 1;
      }
      else {
        dbg_logf((iptr)((u8 *)&g.d_00636eac),res_id);
        res_unlock(res);
        res_free(res);
        err_report((ErrorContext *)&err_report_ctx,4,(iptr)((u8 *)&g.d_00636ee8),(iptr)((u8 *)&g.d_00636ed0),0x424);
        ret = 0;
      }
    }
  }
  return ret;
}
#undef rect
#undef res
#undef res_type
#undef res_type_1
#undef res_type_2
#undef res_type_3
#undef height2
#undef width2
#undef lzw_min_code
#undef data
#undef cursor
#undef image_desc
#undef image_data

/* 005c0034 auto */
void __thiscall surface_reset_clip(DibSurface *this)

{
  SetRect((LPRECT)&this->clip_left,this->bounds_rect,this->bounds_top,this->bounds_right,this->bounds_bottom);
  return;
}

/* 005c0073 auto */
void __thiscall surface_set_clip(DibSurface *this,iptr rect)

{
  SetRect((LPRECT)&this->clip_left,*(int *)rect,*(int *)(rect + 4),*(int *)(rect + 8),
          *(int *)(rect + 0xc));
  IntersectRect((LPRECT)&this->clip_left,(RECT *)&this->clip_left,(RECT *)&this->bounds_rect);
  return;
}

/* 005c00ce auto */
void __thiscall surface_get_clip(DibSurface *this,iptr out_rect)

{
  *(u32 *)out_rect = this->clip_left;
  *(u32 *)(out_rect + 4) = this->clip_top;
  *(u32 *)(out_rect + 8) = this->clip_right;
  *(u32 *)(out_rect + 0xc) = this->clip_bottom;
  return;
}

/* 005c0105 auto */
i32 __thiscall surface_alloc_dib_by_bpp(DibSurface *this,iptr rect)

{
  i32 result;
  
  switch(this->bytes_per_pixel) {
  case 1:
    result = surface_alloc_dib8(this,rect);
    break;
  case 2:
    result = surface_alloc_dib16(this,rect);
    break;
  case 3:
    result = surface_alloc_dib24(this,rect);
    break;
  case 4:
    result = surface_alloc_dib32(this,rect);
    break;
  default:
    result = 0;
  }
  return result;
}

/* 005c019d auto */
i32 __thiscall surface_resize(DibSurface *this,iptr rect)

{
  i32 result;
  
  result = surface_alloc_dib8(this,rect);
  return result;
}

/* 005c01c1 auto */
#define row (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall surface_lock(DibSurface *this)

{
  uptr new_bits;
  void *offsets;
  int top_down;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->bits == 0) {
    new_bits = dib_get_bits(this->dib);
    this->bits = new_bits;
    if (this->bits != 0) {
      offsets = operator_new(this->pixel_height << 2);
      this->row_offsets = (uptr)offsets;
      top_down = dib_is_top_down(this->dib);
      if (top_down == 0) {
        *(u32 *)this->row_offsets = (this->pixel_height - 1) * this->stride;
        for (row = 1; row < (int)this->pixel_height; row++) {
          *(u32 *)(this->row_offsets + row * 4) =
               *(int *)((this->row_offsets - 4) + row * 4) - this->stride;
        }
      }
      else {
        *(i32 *)this->row_offsets = 0;
        for (row = 1; row < (int)this->pixel_height; row++) {
          *(u32 *)(this->row_offsets + row * 4) =
               *(int *)((this->row_offsets - 4) + row * 4) + this->stride;
        }
      }
    }
  }
  return;
}
#undef row

/* 005c02e0 auto */
void __thiscall surface_unlock(DibSurface *this)

{
  uptr new_bits;
  
  if (this->bits != 0) {
    new_bits = dib_unlock_bits(this->dib);
    this->bits = new_bits;
    operator_delete((void *)this->row_offsets);
  }
  return;
}

/* 005c0333 auto */
#define clipped (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define height2 (*(int *)(frame_ + FRAME_OFF(16)))
#define width2 (*(int *)(frame_ + FRAME_OFF(20)))
#define was_locked (*(i32 *)(frame_ + FRAME_OFF(24)))
void __thiscall surface_fill_rect(DibSurface *this,iptr rect,i32 color)

{
  char locked;
  i32 surf_height;
  iptr dib;
  int top_down;
  int pitch;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  was_locked = 1;
  locked = surface_is_locked(this);
  if (locked == '\0') {
    dbg_log((iptr)((u8 *)&g.d_006370c4));
    was_locked = 0;
    surface_lock(this);
  }
  IntersectRect(&clipped,(RECT *)rect,(RECT *)&this->clip_left);
  width2 = rect_width((iptr)&clipped);
  if ((width2 != 0) && (height2 = rect_height((iptr)&clipped), height2 != 0)) {
    surf_height = surface_height(this);
    dib = surface_get_dib(this);
    top_down = dib_is_top_down(dib);
    pitch = surface_get_pitch(this);
    dib_fill_rect8(this->bits,color,clipped.left,clipped.top,width2,height2,
                 ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * pitch,surf_height);
  }
  return;
}
#undef clipped
#undef height2
#undef width2
#undef was_locked

/* 005c041f auto */
void __thiscall surface_fill(DibSurface *this,i32 color)

{
  surface_fill_rect(this,(iptr)&this->clip_left,color);
  return;
}

/* 005c044a auto */
void __thiscall
surface_replace_color_clip(DibSurface *this,i32 from_color,i32 to_color)

{
  surface_replace_color(this,(iptr)&this->clip_left,from_color,to_color);
  return;
}

/* 005c0479 auto */
#define pixel (*(char * *)(frame_ + FRAME_OFF(0)))
#define clipped (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define row (*(int *)(frame_ + FRAME_OFF(20)))
#define col (*(int *)(frame_ + FRAME_OFF(24)))
#define width2 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define was_locked (*(int *)(frame_ + FRAME_OFF(32)))
void __thiscall
surface_replace_color(DibSurface *this,iptr rect,i32 from_color,i32 to_color)

{
  char locked;
  iptr height;
  iptr row_width;
  int next_row;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  was_locked = 1;
  locked = surface_is_locked(this);
  if (locked == '\0') {
    dbg_log((iptr)((u8 *)&g.d_006370ec));
    was_locked = 0;
    surface_lock(this);
  }
  IntersectRect(&clipped,(RECT *)rect,(RECT *)&this->clip_left);
  width2 = rect_width((iptr)&clipped);
  pixel = (char *)surface_pixel_ptr(this,clipped.left,clipped.top);
  row = 0;
  while( true ) {
    height = rect_height((iptr)&clipped);
    if (height <= row) break;
    col = 0;
    while( true ) {
      row_width = rect_width((iptr)&clipped);
      if (row_width <= col) break;
      if (*pixel == (char)from_color) {
        *pixel = (char)to_color;
      }
      pixel++;
      col++;
    }
    next_row = surface_next_row(this,(iptr)pixel);
    pixel = (char *)(next_row - width2);
    row++;
  }
  if (was_locked == 0) {
    surface_unlock(this);
  }
  return;
}
#undef pixel
#undef clipped
#undef row
#undef col
#undef width2
#undef was_locked

/* 005c0593 auto */
#define src_clip (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define dest_clip (*(tagRECT *)(frame_ + FRAME_OFF(16)))
#define src_was_locked (*(int *)(frame_ + FRAME_OFF(32)))
#define height2 (*(int *)(frame_ + FRAME_OFF(36)))
#define width2 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall
surface_blit(DibSurface *this,iptr src,iptr dest_rect,iptr src_rect)

{
  iptr dib;
  int top_down;
  int src_pitch;
  int dest_pitch;
  i32 src_height;
  i32 dest_height;
  int row_bytes;
  int src_x_bytes;
  int dest_x_bytes;
  i32 src_bits;
  i32 dest_bits;
  bool was_unlocked;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  src_was_locked = 1;
  was_unlocked = this->bits == 0;
  if (was_unlocked) {
    dbg_log((iptr)((u8 *)&g.d_00637114));
    surface_lock(this);
  }
  if (*(int *)(src + 0x34) == 0) {
    dbg_log((iptr)((u8 *)&g.d_00637144));
    surface_lock((DibSurface *)src);
    src_was_locked = 0;
  }
  IntersectRect(&dest_clip,(RECT *)dest_rect,(RECT *)&this->clip_left);
  IntersectRect(&src_clip,(RECT *)src_rect,(RECT *)(src + 0x14));
  width2 = src_clip.right - src_clip.left;
  if (dest_clip.right - dest_clip.left <= src_clip.right - src_clip.left) {
    width2 = dest_clip.right - dest_clip.left;
  }
  height2 = src_clip.bottom - src_clip.top;
  if (dest_clip.bottom - dest_clip.top <= src_clip.bottom - src_clip.top) {
    height2 = dest_clip.bottom - dest_clip.top;
  }
  if ((width2 != 0) && (height2 != 0)) {
    dib = surface_get_dib((DibSurface *)src);
    top_down = dib_is_top_down(dib);
    src_pitch = surface_get_pitch((DibSurface *)src);
    src_pitch = ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * src_pitch;
    dib = surface_get_dib(this);
    top_down = dib_is_top_down(dib);
    dest_pitch = surface_get_pitch(this);
    dest_pitch = ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * dest_pitch;
    src_height = surface_height((DibSurface *)src);
    dest_height = surface_height(this);
    row_bytes = this->bytes_per_pixel * width2;
    src_x_bytes = this->bytes_per_pixel * src_clip.left;
    dest_x_bytes = this->bytes_per_pixel * dest_clip.left;
    top_down = height2;
    src_bits = surface_get_bits((DibSurface *)src);
    dest_bits = surface_get_bits(this);
    gfx_copy_pixels(dest_bits,src_bits,dest_x_bytes,dest_clip.top,src_x_bytes,src_clip.top,row_bytes,top_down,dest_height,src_height,dest_pitch,
                 src_pitch);
  }
  if (was_unlocked) {
    surface_unlock(this);
  }
  if (src_was_locked == 0) {
    surface_unlock((DibSurface *)src);
  }
  return;
}
#undef src_clip
#undef dest_clip
#undef src_was_locked
#undef height2
#undef width2

/* 005c0979 auto */
void __thiscall
surface_blit_to_wnd(DibSurface *this,iptr wnd,iptr src_rect,iptr dest_pt)

{
  char locked;
  i32 dest_y;
  iptr window;
  i32 height;
  i32 width;
  i32 dest_x;
  
  if (this->dib == 0) {
    dbg_log((iptr)((u8 *)&g.d_006371a8));
  }
  else {
    locked = surface_is_locked(this);
    if (locked == '\0') {
      dbg_log((iptr)((u8 *)&g.d_006371cc));
      surface_lock(this);
    }
    dest_y = wnd_get_palette_obj((WndPaletteObjView *)wnd);
    surface_apply_palette(this,dest_y);
    dest_y = *(i32 *)(dest_pt + 4);
    dest_x = *(i32 *)dest_pt;
    window = wnd_get_window((WndBase *)wnd);
    height = rect_height(src_rect);
    width = rect_width(src_rect);
    dib_blit_to_wnd_obj(this->dib,*(i32 *)src_rect,*(i32 *)(src_rect + 4),width,height,
                 window,dest_x,dest_y);
    if (locked == '\0') {
      surface_unlock(this);
    }
  }
  return;
}

/* 005c0bf2 auto */
uint __thiscall
surface_get_pixel(DibSurface *this,i32 x,i32 y)

{
  char in_clip;
  uint color;
  byte *pixel;
  
  in_clip = surface_in_clip(this,x,y);
  if (in_clip == '\0') {
    dbg_logf_int2((iptr)((u8 *)&g.d_00637250),x,y);
    color = 0;
  }
  else {
    pixel = (byte *)surface_pixel_ptr(this,x,y);
    color = (uint)*pixel;
  }
  return color;
}

/* 005c0c5d auto */
void __thiscall
surface_set_pixel
          (DibSurface *this,i32 x,i32 y,i32 color)

{
  char in_clip;
  i8 *pixel;
  
  in_clip = surface_in_clip(this,x,y);
  if (in_clip == '\0') {
    dbg_logf_int2((iptr)((u8 *)&g.d_00637278),x,y);
  }
  else {
    pixel = (i8 *)surface_pixel_ptr(this,x,y);
    *pixel = (i8)color;
  }
  return;
}

/* 005c0cc5 auto */
void __thiscall surface_set_palette(DibSurface *this,iptr palette)

{
  u32 version;
  
  version = palette_get_version((PaletteVersionView *)palette);
  if (version != this->palette_version) {
    dib_set_palette(this->dib,palette);
    version = palette_get_version((PaletteVersionView *)palette);
    this->palette_version = version;
  }
  return;
}

/* 005c0d12 auto */
void __thiscall surface_apply_palette(DibSurface *this,PaletteVersionView *palette)

{
  u32 version;
  
  if (palette != (PaletteVersionView *)0x0) {
    version = palette_get_version(palette);
    if (version != this->palette_version) {
      dib_set_palette(this->dib,(iptr)palette);
      version = palette_get_version(palette);
      this->palette_version = version;
    }
  }
  return;
}

/* 005c0d69 auto */
#define gfx_black_color_index (*(i8 *)((u8 *)&g.d_00638b40))
#define saved_color (*(i32 *)(frame_ + FRAME_OFF(4)))
void __thiscall
surface_draw_text_cur_font(SurfaceTextCurFontView *this,i32 text,int x,int y,uint flags)

{
  i8 old_color;
  int font_height;
  int shadow_offset;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (draw_current_font == (i8 *)0x0) {
    dbg_log((iptr)((u8 *)&g.d_006372a0));
  }
  else if (this->dib != 0) {
    if ((flags & 0x10) != 0) {
      font_height = font_measure_height(*(i32 *)draw_current_font);
      font_height += (font_height >> 0x1f & 7U);
      shadow_offset = font_height >> 3;
      old_color = gfx_set_text_color_index(CONCAT31((int3)(font_height >> 0xb),gfx_black_color_index));
      saved_color = CONCAT31((*(i32 *)((char *)&saved_color + 1)),old_color);
      dib_draw_text_at(this->dib,*(i32 *)draw_current_font,text,shadow_offset + x,
                   shadow_offset + y,(iptr)(this->clip_rect_2),flags);
      gfx_set_text_color_index(saved_color);
    }
    dib_draw_text_at(this->dib,*(i32 *)draw_current_font,text,x,y,
                 (iptr)(this->clip_rect_2),flags);
  }
  return;
}
#undef gfx_black_color_index
#undef saved_color

/* 005c0f57 auto */
#define gfx_black_color_index (*(i8 *)((u8 *)&g.d_00638b40))
#define saved_color (*(i32 *)(frame_ + FRAME_OFF(4)))
void __thiscall
surface_draw_text
          (DibSurface *this,iptr font,iptr text,iptr x,int y,uint flags)

{
  i8 old_color;
  int font_height;
  int shadow_offset;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->dib != 0) {
    if ((flags & 0x10) != 0) {
      font_height = font_measure_height(*(i32 *)font);
      font_height += (font_height >> 0x1f & 7U);
      shadow_offset = font_height >> 3;
      old_color = gfx_set_text_color_index(CONCAT31((int3)(font_height >> 0xb),gfx_black_color_index));
      saved_color = CONCAT31((*(i32 *)((char *)&saved_color + 1)),old_color);
      dib_draw_text_at(this->dib,*(i32 *)font,text,x + shadow_offset,y + shadow_offset,
                   (iptr)&this->clip_left,flags);
      gfx_set_text_color_index(saved_color);
    }
    dib_draw_text_at(this->dib,*(i32 *)font,text,x,y,(iptr)&this->clip_left
                 ,flags);
  }
  return;
}
#undef gfx_black_color_index
#undef saved_color

/* 005c1020 auto */
#define gfx_black_color_index (*(i8 *)((u8 *)&g.d_00638b40))
#define saved_color (*(i32 *)(frame_ + FRAME_OFF(4)))
#define shadow_rect (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __thiscall
surface_draw_text_in_rect(DibSurface *this,iptr font,iptr text,iptr rect,uint flags)

{
  i8 old_color;
  int shadow_offset;
  BOOL BVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->dib != 0) {
    if ((flags & 0x10) != 0) {
      shadow_offset = font_measure_height(*(i32 *)font);
      shadow_offset = (int)(shadow_offset + (shadow_offset >> 0x1f & 7U)) >> 3;
      shadow_rect.left = *(LONG *)rect;
      shadow_rect.top = *(LONG *)(rect + 4);
      shadow_rect.right = *(LONG *)(rect + 8);
      shadow_rect.bottom = *(LONG *)(rect + 0xc);
      BVar3 = OffsetRect(&shadow_rect,shadow_offset,shadow_offset);
      old_color = gfx_set_text_color_index(CONCAT31((int3)((uint)BVar3 >> 8),gfx_black_color_index));
      saved_color = CONCAT31((*(i32 *)((char *)&saved_color + 1)),old_color);
      dib_draw_text_rect(this->dib,*(i32 *)font,text,(iptr)&shadow_rect,flags);
      gfx_set_text_color_index(saved_color);
    }
    dib_draw_text_rect(this->dib,*(i32 *)font,text,rect,flags);
  }
  return;
}
#undef gfx_black_color_index
#undef saved_color
#undef shadow_rect

/* 005c1167 auto */
void __thiscall
surface_draw_text_rect
          (DibSurface *this,iptr font,iptr text,iptr rect,i32 flags)

{
  if (this->dib != 0) {
    dib_draw_text_wrap(this->dib,*(i32 *)font,text,rect,flags);
  }
  return;
}

/* 005c11b2 auto */
#define gfx_text_color_index (*(i8 *)((u8 *)&g.d_00637e78))
void __thiscall
surface_draw_line(DibSurface *this,u32 x1,u32 y1,u32 x2,u32 y2)

{
  iptr handle;
  int top_down;
  int pitch;
  i32 height;
  i32 color;
  u32 start;
  
  if (((((((int)this->clip_left <= (int)x1) || ((int)this->clip_left <= (int)x2)) &&
        (((int)x2 < (int)this->clip_right || ((int)x1 < (int)this->clip_right)))) &&
       (((int)this->clip_top <= (int)y1 || ((int)this->clip_top <= (int)y2)))) &&
      (((int)y1 < (int)this->clip_bottom || ((int)y2 < (int)this->clip_bottom)))) &&
     (this->dib != 0)) {
    if (y2 == y1) {
      if ((int)x1 < (int)this->clip_left) {
        x1 = this->clip_left;
      }
      if ((int)this->clip_right <= (int)x1) {
        x1 = this->clip_right - 1;
      }
      if ((int)x2 < (int)this->clip_left) {
        x2 = this->clip_left;
      }
      if ((int)this->clip_right <= (int)x2) {
        x2 = this->clip_right - 1;
      }
      if (x2 != x1) {
        handle = surface_get_dib(this);
        top_down = dib_is_top_down(handle);
        pitch = surface_get_pitch(this);
        pitch = ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * pitch;
        height = surface_height(this);
        start = x2;
        if ((int)x1 <= (int)x2) {
          start = x1;
        }
        top_down = crt_abs(x2 - x1);
        top_down++;
        color = CONCAT31((int3)((uint)top_down >> 8),gfx_text_color_index);
        handle = surface_get_bits(this);
        dib_hline8(handle,color,top_down,start,y1,height,pitch);
      }
    }
    else if (x2 == x1) {
      if ((int)y1 < (int)this->clip_top) {
        y1 = this->clip_top;
      }
      if ((int)this->clip_bottom <= (int)y1) {
        y1 = this->clip_bottom - 1;
      }
      if ((int)y2 < (int)this->clip_top) {
        y2 = this->clip_top;
      }
      if ((int)this->clip_bottom <= (int)y2) {
        y2 = this->clip_bottom - 1;
      }
      if (y2 != y1) {
        handle = surface_get_dib(this);
        top_down = dib_is_top_down(handle);
        pitch = surface_get_pitch(this);
        pitch = ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * pitch;
        height = surface_height(this);
        start = y2;
        if ((int)y1 <= (int)y2) {
          start = y1;
        }
        top_down = crt_abs(y2 - y1);
        top_down++;
        color = CONCAT31((int3)((uint)top_down >> 8),gfx_text_color_index);
        handle = surface_get_bits(this);
        dib_vline8(handle,color,top_down,x1,start,height,pitch);
      }
    }
    else {
      dib_draw_line(this->dib,x1,y1,x2,y2);
    }
  }
  return;
}
#undef gfx_text_color_index

/* 005c19ad auto */
#define gfx_text_color_index (*(i8 *)((u8 *)&g.d_00637e78))
i8 __cdecl gfx_set_text_color_index(i32 color_index)

{
  i8 prev_index;
  
  prev_index = gfx_text_color_index;
  gfx_text_color_index = (i8)color_index;
  return prev_index;
}
#undef gfx_text_color_index

/* 005c19d3 auto */
int __thiscall surface_pixel_ptr(DibSurface *this,int x,int y)

{
  return *(int *)(this->row_offsets + y * 4) + this->bits + x;
}

/* 005c1a00 auto */
i8 __thiscall surface_in_clip(DibSurface *this,int x,int y)

{
  i8 inside;
  
  if ((((x < (int)this->clip_left) || ((int)this->clip_right <= x)) ||
      (y < (int)this->clip_top)) || ((int)this->clip_bottom <= y)) {
    inside = 0;
  }
  else {
    inside = 1;
  }
  return inside;
}

/* 005c1a62 auto */
#define pixel (*(byte * *)(frame_ + FRAME_OFF(0)))
#define col (*(int *)(frame_ + FRAME_OFF(4)))
#define row (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall
surface_remap_colors(DibSurface *this,iptr remap_table,iptr base_index,i32 unused)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->bits != 0) {
    pixel = (byte *)this->bits;
    for (row = 0; row < (int)this->pixel_height; row++) {
      for (col = 0; col < (int)this->pixel_width; col++) {
        if (-1 < (int)((uint)*pixel - base_index)) {
          *pixel = *(byte *)(((uint)*pixel - base_index) + remap_table);
        }
        pixel++;
      }
      pixel += (this->stride - this->pixel_width);
    }
  }
  return;
}
#undef pixel
#undef col
#undef row

/* 005c1b47 auto */
i32 __thiscall surface_alloc_dib16(DibSurface *this,iptr rect)

{
  char locked;
  u32 value;
  int dim;
  
  if (this->dib != 0) {
    locked = surface_is_locked(this);
    if (locked != '\0') {
      surface_unlock(this);
    }
    value = dib_destroy(this->dib);
    this->dib = value;
  }
  if (((rect != 0) && (dim = rect_width(rect), dim != 0)) &&
     (dim = rect_height(rect), dim != 0)) {
    surface_set_dims(this,rect);
    value = dib_create16((iptr)&this->bounds_rect);
    this->dib = value;
    if (this->dib != 0) {
      value = dib_get_stride(this->dib);
      this->stride = value;
      dim = dib_is_top_down(this->dib);
      if (dim == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      this->bytes_per_pixel = 2;
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,(iptr)((u8 *)&g.d_00637318),(iptr)((u8 *)&g.d_00637300),0x86c);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005c1cf7 auto */
i32 __thiscall surface_alloc_dib24(DibSurface *this,iptr rect)

{
  char locked;
  u32 value;
  int dim;
  
  if (this->dib != 0) {
    locked = surface_is_locked(this);
    if (locked != '\0') {
      surface_unlock(this);
    }
    value = dib_destroy(this->dib);
    this->dib = value;
  }
  if (((rect != 0) && (dim = rect_width(rect), dim != 0)) &&
     (dim = rect_height(rect), dim != 0)) {
    surface_set_dims(this,rect);
    value = dib_create24((iptr)&this->bounds_rect);
    this->dib = value;
    if (this->dib != 0) {
      value = dib_get_stride(this->dib);
      this->stride = value;
      dim = dib_is_top_down(this->dib);
      if (dim == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      this->bytes_per_pixel = 3;
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,(iptr)((u8 *)&g.d_00637344),(iptr)((u8 *)&g.d_0063732c),0x8a1);
    return 0;
  }
  surface_set_dims(this,0);
  return 1;
}

/* 005c1ea7 auto */
i32 __thiscall surface_alloc_dib32(DibSurface *this,iptr rect)

{
  char locked;
  u32 value;
  int dim;
  
  if (this->dib != 0) {
    locked = surface_is_locked(this);
    if (locked != '\0') {
      surface_unlock(this);
    }
    value = dib_destroy(this->dib);
    this->dib = value;
  }
  if (((rect != 0) && (dim = rect_width(rect), dim != 0)) &&
     (dim = rect_height(rect), dim != 0)) {
    surface_set_dims(this,rect);
    value = dib_create32((iptr)&this->bounds_rect);
    this->dib = value;
    if (this->dib != 0) {
      value = dib_get_stride(this->dib);
      this->stride = value;
      dim = dib_is_top_down(this->dib);
      if (dim == 0) {
        this->signed_pitch = -this->stride;
      }
      else {
        this->signed_pitch = this->stride;
      }
      this->bytes_per_pixel = 4;
      surface_lock(this);
      return 1;
    }
    err_report((ErrorContext *)&err_report_ctx,2,(iptr)((u8 *)&g.d_00637370),(iptr)((u8 *)&g.d_00637358),0x8d6);
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
int __cdecl dib_row_align4(int width)

{
  return ((int)(width + 3 + (width + 3 >> 0x1f & 3U)) >> 2) << 2;
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
int __thiscall surface_next_row(DibSurface *this,iptr row_ptr)

{
  return this->signed_pitch + row_ptr;
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
int __thiscall surface_prev_row(DibSurface *this,iptr row_ptr)

{
  return row_ptr - this->signed_pitch;
}

/* 005c6480 auto */
void __thiscall palette_commit_range(GamePalette *this,int first,int count)

{
  if (0x100 < count + first) {
    count = 0x100 - first;
  }
  logpal_apply_range((iptr)this,this->hpalette,first,count);
  palette_new_version(this);
  return;
}

/* 005c64da auto */
GamePalette * __thiscall palette_init(GamePalette *this)

{
  u32 hpal;
  
  logpal_init_from_system((iptr)this);
  hpal = logpal_create_hpalette((iptr)this);
  this->hpalette = hpal;
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
#define type_c (*(i8 *)(frame_ + FRAME_OFF(0)))
#define type_t (*(i8 *)(frame_ + FRAME_OFF(1)))
#define type_a (*(i8 *)(frame_ + FRAME_OFF(2)))
#define type_b (*(i8 *)(frame_ + FRAME_OFF(3)))
void __thiscall palette_load_ctab_res(GamePalette *this,i32 res_id)

{
  int res;
  i32 *data;
  i32 first;
  i32 count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  type_c = 0x43;
  type_t = 0x54;
  type_a = 0x41;
  type_b = 0x42;
  res = res_load((iptr)&type_c,res_id);
  if (res == 0) {
    dbg_logf_noret((iptr)((u8 *)&g.d_00637bec),res_id);
  }
  else {
    data = (i32 *)res_lock(res);
    first = endian_from_le(*data);
    count = endian_from_le(data[1]);
    palette_set_rgb(this,first,count,(iptr)(data + 2));
    res_unlock(res);
    res_free(res);
  }
  return;
}
#undef type_c
#undef type_t
#undef type_a
#undef type_b

/* 005c6a42 auto */
void __thiscall palette_new_version(GamePalette *this)

{
  uint rnd;
  
  this->pal_version = 0;
  while (this->pal_version == 0) {
    rnd = _rand();
    this->pal_version = rnd & 0x7fff;
  }
  return;
}

/* 005c6a8d auto */
void __thiscall
palette_reserve_range(GamePalette *this,i32 first,i32 count)

{
  logpal_reserve_range((iptr)this,first,count);
  palette_commit_range(this,first,count);
  return;
}

/* 005c6b63 auto */
void __thiscall
palette_get_rgb
          (GamePalette *this,iptr dest,i32 first,i32 count)

{
  palette_copy_rgb_range((iptr)this,dest,first,count);
  return;
}

/* 005c6b93 auto */
void __thiscall
palette_set_entry
          (GamePalette *this,i32 index,i32 red,i32 green,
          i32 blue)

{
  palette_set_entry_rgb((iptr)this,index,red,green,blue);
  palette_commit_range(this,index,1);
  return;
}

/* 005c6da8 auto */
#define index (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall
palette_set_rgb(GamePalette *this,int first,int count,iptr rgb)

{
  i32 hi_bits;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (0x100 < count + first) {
    count = 0x100 - first;
  }
  for (index = first; index < count + first; index++) {
    hi_bits = (i32)((uint)rgb >> 8);
    palette_set_entry_rgb((iptr)this,index,CONCAT31(hi_bits,*(i8 *)rgb),
                 CONCAT31(hi_bits,*(i8 *)(rgb + 1)),
                 CONCAT31(hi_bits,*(i8 *)(rgb + 2)));
    rgb += 3;
  }
  palette_commit_range(this,first,count);
  return;
}
#undef index

/* 005c71f3 auto */
void __thiscall
palette_fade_begin(GamePalette *this,u32 first,u32 count,u32 steps,iptr target_pal)

{
  u32 handle;
  iptr dst_buf;
  iptr target_logpal;
  u32 count_arg;
  
  this->fade_steps = steps;
  this->fade_first = first;
  this->fade_count = count;
  handle = mem_handle_alloc(count * 3);
  this->fade_src_rgb = handle;
  handle = mem_handle_alloc(count * 3);
  this->fade_dst_rgb = handle;
  dst_buf = mem_handle_lock(this->fade_src_rgb);
  palette_copy_rgb_range((iptr)this,dst_buf,first,count);
  mem_handle_unlock(this->fade_src_rgb);
  dst_buf = mem_handle_lock(this->fade_dst_rgb);
  handle = first;
  count_arg = count;
  target_logpal = palette_get_logpalette((GamePalette *)target_pal);
  palette_copy_rgb_range(target_logpal,dst_buf,handle,count_arg);
  mem_handle_unlock(this->fade_dst_rgb);
  palette_reserve_range(this,first,count);
  return;
}

/* 005c72f8 auto */
void __thiscall palette_fade_end(GamePalette *this)

{
  iptr src_buf;
  u32 handle;
  
  src_buf = mem_handle_lock(this->fade_src_rgb);
  palette_set_rgb(this,this->fade_first,this->fade_count,src_buf);
  mem_handle_unlock(this->fade_src_rgb);
  handle = mem_handle_free(this->fade_src_rgb);
  this->fade_src_rgb = handle;
  handle = mem_handle_free(this->fade_dst_rgb);
  this->fade_dst_rgb = handle;
  return;
}

/* 005c738e auto */
#define offset (*(iptr *)(frame_ + FRAME_OFF(0)))
#define green (*(i32 *)(frame_ + FRAME_OFF(4)))
#define red (*(i32 *)(frame_ + FRAME_OFF(8)))
#define blue (*(i32 *)(frame_ + FRAME_OFF(12)))
void __thiscall palette_fade_step(GamePalette *this,int step)

{
  char dst_weight;
  char src_weight;
  iptr src_buf;
  iptr dst_buf;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((step < 0) || ((int)this->fade_steps < step)) {
    dbg_logf((iptr)((u8 *)&g.d_00637c54),step);
  }
  else {
    src_weight = (char)step;
    dst_weight = (char)this->fade_steps - src_weight;
    src_buf = mem_handle_lock(this->fade_src_rgb);
    dst_buf = mem_handle_lock(this->fade_dst_rgb);
    for (offset = 0; offset < (int)(this->fade_count * 3); offset += 3) {
      red = CONCAT31((*(i32 *)((char *)&red + 1)),
                          (char)((longlong)(ulonglong)*(byte *)(offset + dst_buf) /
                                (longlong)(int)this->fade_steps) * dst_weight +
                          (char)((longlong)(ulonglong)*(byte *)(offset + src_buf) /
                                (longlong)(int)this->fade_steps) * src_weight);
      green = CONCAT31((*(i32 *)((char *)&green + 1)),
                          (char)((longlong)(ulonglong)*(byte *)(offset + 1 + src_buf) /
                                (longlong)(int)this->fade_steps) * src_weight +
                          (char)((longlong)(ulonglong)*(byte *)(offset + 1 + dst_buf) /
                                (longlong)(int)this->fade_steps) * dst_weight);
      blue = CONCAT31((*(i32 *)((char *)&blue + 1)),
                         (char)((longlong)(ulonglong)*(byte *)(offset + 2 + dst_buf) /
                               (longlong)(int)this->fade_steps) * dst_weight +
                         (char)((longlong)(ulonglong)*(byte *)(offset + 2 + src_buf) /
                               (longlong)(int)this->fade_steps) * src_weight);
      logpal_set_entry((iptr)this,this->fade_first + offset / 3,red,green,blue);
    }
    palette_animate((iptr)this,this->hpalette,this->fade_first,this->fade_count);
    mem_handle_unlock(this->fade_src_rgb);
    mem_handle_unlock(this->fade_dst_rgb);
  }
  return;
}
#undef offset
#undef green
#undef red
#undef blue

/* 005c8200 auto */
#define logfont (*(LOGFONTA *)(frame_ + FRAME_OFF(4)))
#define handle (*(i32 *)(frame_ + FRAME_OFF(64)))
#define hfont2 (*(HFONT *)(frame_ + FRAME_OFF(68)))
#define data (*(i32 * *)(frame_ + FRAME_OFF(72)))
i32 __cdecl font_handle_create(i32 face,int size,i32 style)

{
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  logfont.lfHeight = -size;
  logfont.lfWidth = 0;
  logfont.lfEscapement = 0;
  logfont.lfOrientation = 0;
  logfont.lfCharSet = 1;
  logfont.lfOutPrecision = 4;
  logfont.lfClipPrecision = 1;
  logfont.lfQuality = '\0';
  logfont.lfPitchAndFamily = '\0';
  if (((byte)style & 1) == 0) {
    logfont.lfWeight = 400;
  }
  else {
    logfont.lfWeight = 700;
  }
  logfont.lfItalic = (byte)style & 2;
  logfont.lfUnderline = (byte)style & 4;
  logfont.lfStrikeOut = (byte)style & 8;
  switch(face) {
  case 0:
    logfont.lfPitchAndFamily = 16;
    crt_strcpy(logfont.lfFaceName,s_Times_New_Roman_00637c74);
    break;
  case 1:
    logfont.lfPitchAndFamily = ' ';
    crt_strcpy(logfont.lfFaceName,s_Arial_00637c84);
    break;
  case 2:
    crt_strcpy(logfont.lfFaceName,s_System_00637c94);
    break;
  case 3:
    logfont.lfPitchAndFamily = '0';
    crt_strcpy(logfont.lfFaceName,s_Courier_00637c8c);
  }
  handle = 0;
  hfont2 = CreateFontIndirectA(&logfont);
  if (hfont2 != (HFONT)0x0) {
    handle = mem_handle_alloc(8);
    data = (i32 *)mem_handle_lock(handle);
    *data = hfont2;
    data[1] = 1;
    mem_handle_unlock(handle);
  }
  return handle;
}
#undef logfont
#undef handle
#undef hfont2
#undef data

/* 005c841d auto */
i32 __cdecl font_handle_destroy(i32 handle)

{
  i32 *data;
  i32 result;
  
  data = (i32 *)mem_handle_lock(handle);
  if (data == (i32 *)0x0) {
    result = 0;
  }
  else {
    if (data[1] == 1) {
      DeleteObject((HGDIOBJ)*data);
    }
    mem_handle_unlock(handle);
    result = mem_handle_free(handle);
  }
  return result;
}

/* 005c847f auto */
#define metrics (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(0)))
#define data (*(i32 * *)(frame_ + FRAME_OFF(56)))
LONG __cdecl font_measure_height(i32 handle)

{
  int size;
  HDC hdc;
  HGDIOBJ h;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  size = mem_handle_size(handle);
  if (size == 0) {
    metrics.tmHeight = 1;
  }
  else {
    data = (i32 *)mem_handle_lock(handle);
    hdc = GetDC((HWND)0x0);
    h = SelectObject(hdc,(HGDIOBJ)*data);
    GetTextMetricsA(hdc,&metrics);
    SelectObject(hdc,h);
    ReleaseDC((HWND)0x0,hdc);
    mem_handle_unlock(handle);
  }
  return metrics.tmHeight;
}
#undef metrics
#undef data

/* 005c8514 auto */
#define metrics (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(0)))
#define data (*(i32 * *)(frame_ + FRAME_OFF(56)))
int __cdecl font_handle_line_spacing(i32 handle)

{
  HDC hdc;
  HGDIOBJ h;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  data = (i32 *)mem_handle_lock(handle);
  hdc = GetDC((HWND)0x0);
  h = SelectObject(hdc,(HGDIOBJ)*data);
  GetTextMetricsA(hdc,&metrics);
  SelectObject(hdc,h);
  ReleaseDC((HWND)0x0,hdc);
  mem_handle_unlock(handle);
  return metrics.tmExternalLeading + metrics.tmHeight;
}
#undef metrics
#undef data

/* 005c858e auto */
#define extent (*(tagSIZE *)(frame_ + FRAME_OFF(0)))
#define data (*(i32 * *)(frame_ + FRAME_OFF(8)))
LONG __cdecl font_measure_width(i32 handle,iptr text)

{
  HDC hdc;
  HGDIOBJ h;
  size_t c;
  tagSIZE *lpsz;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  data = (i32 *)mem_handle_lock(handle);
  hdc = GetDC((HWND)0x0);
  h = SelectObject(hdc,(HGDIOBJ)*data);
  lpsz = &extent;
  c = _strlen((char *)text);
  GetTextExtentPointA(hdc,(LPCSTR)text,c,lpsz);
  SelectObject(hdc,h);
  ReleaseDC((HWND)0x0,hdc);
  mem_handle_unlock(handle);
  return extent.cx;
}
#undef extent
#undef data

/* 005c8791: written by hand in src/game/fixups.c */

/* 005c8c83 auto */
void __cdecl region_dispose(int region)

{
  if (region == 0) {
    dbg_log((iptr)((u8 *)&g.d_00637cb8));
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
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl gfx_scale_init(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 0x10; i++) {
    *(i32 *)(&gfx_scale_cache_last_used + i * 0x100c) = 0;
    *(i32 *)(&gfx_scale_cache_num + i * 0x100c) = 0;
    *(i32 *)(&gfx_scale_cache_den + i * 0x100c) = 0;
  }
  gfx_set_scale_ratio(1,1);
  gfx_set_scale_tables(1,1,1,1);
  return;
}
#undef i

/* 005cd775 auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define slot (*(int *)(frame_ + FRAME_OFF(0)))
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define oldest_tick (*(int *)(frame_ + FRAME_OFF(8)))
#define accum (*(int *)(frame_ + FRAME_OFF(12)))
#define value (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_set_scale_ratio(int num,int den)

{
  i32 now;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (num < 2) {
    num = 1;
  }
  if (den < 2) {
    den = 1;
  }
  gfx_scale_num = num;
  gfx_scale_den = den;
  oldest_tick = timer_ticks();
  slot = -1;
  index = 0;
  do {
    if (0xf < index) {
      *(int *)(&gfx_scale_cache_num + slot * 0x100c) = gfx_scale_num;
      *(int *)(&gfx_scale_cache_den + slot * 0x100c) = gfx_scale_den;
      now = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + slot * 0x100c) = now;
      value = 0;
      if (gfx_scale_num < gfx_scale_den) {
        accum = 0;
        index = 0;
        while (index < 0x400) {
          for (; (-1 < accum && (index < 0x400)); index++) {
            *(int *)(&gfx_scale_cache_tables + index * 4 + slot * 0x100c) = value;
            accum -= gfx_scale_den;
          }
          accum += gfx_scale_num;
          value++;
        }
      }
      else {
        accum = gfx_scale_num;
        index = 0;
        while (index < 0x400) {
          for (; (gfx_scale_den <= accum && (index < 0x400)); index++) {
            *(int *)(&gfx_scale_cache_tables + index * 4 + slot * 0x100c) = value;
            accum -= gfx_scale_den;
          }
          accum += gfx_scale_num;
          value++;
        }
      }
LAB_005cda01:
      gfx_scale_table = (int)&gfx_scale_cache_tables + slot * 0x100c;
      return;
    }
    if ((*(int *)(&gfx_scale_cache_num + index * 0x100c) == gfx_scale_num) &&
       (*(int *)(&gfx_scale_cache_den + index * 0x100c) == gfx_scale_den)) {
      now = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + index * 0x100c) = now;
      slot = index;
      goto LAB_005cda01;
    }
    if (*(int *)(&gfx_scale_cache_last_used + index * 0x100c) <= oldest_tick) {
      oldest_tick = *(int *)(&gfx_scale_cache_last_used + index * 0x100c);
      slot = index;
    }
    index++;
  } while( true );
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef slot
#undef index
#undef oldest_tick
#undef accum
#undef value

/* 005cda06 auto */
#define gfx_scale_den (*(i32 *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(i32 *)((u8 *)&g.d_00637f98))
void __cdecl gfx_get_scale_ratio(iptr out_num,iptr out_den)

{
  *(i32 *)out_num = gfx_scale_num;
  *(i32 *)out_den = gfx_scale_den;
  return;
}
#undef gfx_scale_den
#undef gfx_scale_num

/* 005cda2a auto */
#define gfx_scale_x_table (*(i8 * *)((u8 *)&g.d_006e47c0))
#define gfx_scale_y_table (*(i8 * *)((u8 *)&g.d_006e47c4))
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define oldest_tick (*(int *)(frame_ + FRAME_OFF(8)))
#define y_slot (*(int *)(frame_ + FRAME_OFF(12)))
#define x_slot (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl gfx_set_scale_tables(int x_num,int x_den,int y_num,int y_den)

{
  i32 now;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (x_num < 2) {
    x_num = 1;
  }
  if (x_den < 2) {
    x_den = 1;
  }
  if (y_num < 2) {
    y_num = 1;
  }
  if (y_den < 2) {
    y_den = 1;
  }
  gfx_scale_x_num = x_num;
  gfx_scale_x_den = x_den;
  gfx_scale_y_num = y_num;
  gfx_scale_y_den = y_den;
  oldest_tick = timer_ticks();
  x_slot = -1;
  for (index = 0; index < 0x10; index++) {
    if ((*(int *)(&gfx_scale_cache_num + index * 0x100c) == gfx_scale_x_num) &&
       (*(int *)(&gfx_scale_cache_den + index * 0x100c) == gfx_scale_x_den)) {
      now = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + index * 0x100c) = now;
      x_slot = index;
      goto LAB_005cdbab;
    }
    if (*(int *)(&gfx_scale_cache_last_used + index * 0x100c) <= oldest_tick) {
      oldest_tick = *(int *)(&gfx_scale_cache_last_used + index * 0x100c);
      x_slot = index;
    }
  }
  gfx_scale_build_table(x_slot,gfx_scale_x_num,gfx_scale_x_den);
LAB_005cdbab:
  gfx_scale_x_table = &gfx_scale_cache_tables + x_slot * 0x100c;
  oldest_tick = timer_ticks();
  y_slot = -1;
  index = 0;
  do {
    if (0xf < index) {
      gfx_scale_build_table(y_slot,gfx_scale_y_num,gfx_scale_y_den);
      index = y_slot;
LAB_005cdcd6:
      gfx_scale_y_table = &gfx_scale_cache_tables + index * 0x100c;
      return;
    }
    if ((*(int *)(&gfx_scale_cache_num + index * 0x100c) == gfx_scale_y_num) &&
       (*(int *)(&gfx_scale_cache_den + index * 0x100c) == gfx_scale_y_den)) {
      now = timer_ticks();
      *(i32 *)(&gfx_scale_cache_last_used + index * 0x100c) = now;
      goto LAB_005cdcd6;
    }
    if ((*(int *)(&gfx_scale_cache_last_used + index * 0x100c) <= oldest_tick) && (x_slot != index)) {
      oldest_tick = *(int *)(&gfx_scale_cache_last_used + index * 0x100c);
      y_slot = index;
    }
    index++;
  } while( true );
}
#undef gfx_scale_x_table
#undef gfx_scale_y_table
#undef index
#undef oldest_tick
#undef y_slot
#undef x_slot

/* 005cdcdb auto */
#define index (*(int *)(frame_ + FRAME_OFF(0)))
#define accum (*(int *)(frame_ + FRAME_OFF(4)))
#define value (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl gfx_scale_build_table(int slot,int num,int den)

{
  i32 now;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(int *)(&gfx_scale_cache_num + slot * 0x100c) = num;
  *(int *)(&gfx_scale_cache_den + slot * 0x100c) = den;
  now = timer_ticks();
  *(i32 *)(&gfx_scale_cache_last_used + slot * 0x100c) = now;
  value = 0;
  if (num < den) {
    accum = 0;
    index = 0;
    while (index < 0x400) {
      for (; (-1 < accum && (index < 0x400)); index++) {
        *(int *)(&gfx_scale_cache_tables + index * 4 + slot * 0x100c) = value;
        accum -= den;
      }
      accum += num;
      value++;
    }
  }
  else {
    accum = num;
    index = 0;
    while (index < 0x400) {
      for (; (den <= accum && (index < 0x400)); index++) {
        *(int *)(&gfx_scale_cache_tables + index * 4 + slot * 0x100c) = value;
        accum -= den;
      }
      accum += num;
      value++;
    }
  }
  return;
}
#undef index
#undef accum
#undef value

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
  uptr ptr;
  
  if (this->data_handle != 0) {
    if (this->data_ptr != 0) {
      ptr = mem_handle_unlock(this->data_handle);
      this->data_ptr = ptr;
    }
    this = (Sprite *)mem_handle_free(this->data_handle);
  }
  return this;
}

/* 005cdea1 auto */
#define surface (*(DibSurface *)(frame_ + FRAME_OFF(0)))
#define result (*(i32 *)(frame_ + FRAME_OFF(72)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(76)))
#define unwind_state (*(i32 *)(frame_ + FRAME_OFF(80)))
i32 __thiscall
sprite_create_solid(Sprite *this,i32 width,i32 height,uint color)

{
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  unwind_state = 0xffffffff;
  surface_ctor(&surface);
  unwind_state = 0;
  surface_create(&surface,width,height);
  surface_fill(&surface,color & 0xff);
  sprite_encode_rect(this,(iptr)&surface,0,0,width,height);
  SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
  unwind_state = 0xffffffff;
  /* inlined unwind funclet 005cdf2d */ { surface_dtor((DibSurface *)((iptr)&surface)); }
  return result;
}
#undef surface
#undef result
#undef seh_handler
#undef unwind_state

/* 005cdf50 auto */
void __thiscall sprite_free(Sprite *this)

{
  uptr ptr;
  u32 handle;
  
  if (this->data_ptr != 0) {
    ptr = mem_handle_unlock(this->data_handle);
    this->data_ptr = ptr;
  }
  if (this->data_handle != 0) {
    handle = mem_handle_free(this->data_handle);
    this->data_handle = handle;
  }
  sprite_clear_fields(this);
  return;
}

/* 005cebb4 auto */
void __thiscall sprite_grab_surface_rect(Sprite *this,iptr surface,iptr rect)

{
  u32 handle;
  
  handle = sprite_encode_from_surface(this,surface,0xffffffff,rect);
  this->data_handle = handle;
  sprite_lock(this);
  return;
}

/* 005cebec auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall
sprite_encode_rect
          (Sprite *this,iptr surface,int x,int y,int width,int height)

{
  u32 handle;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&rect,x,y,x + width,height + y);
  handle = sprite_encode_from_surface(this,surface,0xffffffff,(iptr)&rect);
  this->data_handle = handle;
  sprite_lock(this);
  return;
}
#undef rect

/* 005cec44 auto */
void __thiscall
sprite_grab_rect(Sprite *this,iptr surface,uint key_color,iptr rect)

{
  u32 handle;
  
  handle = sprite_encode_from_surface(this,surface,key_color & 0xff,rect);
  this->data_handle = handle;
  sprite_lock(this);
  return;
}

/* 005cedad auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall
sprite_grab_from_surface
          (Sprite *this,iptr surface,uint key_color,int x,int y,int width,
          int height)

{
  u32 handle;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&rect,x,y,width + x,height + y);
  handle = sprite_encode_from_surface(this,surface,key_color & 0xff,(iptr)&rect);
  this->data_handle = handle;
  sprite_lock(this);
  return;
}
#undef rect

/* 005cef31 auto */
iptr __thiscall
sprite_draw
          (Sprite *this,iptr dest,iptr surface,i32 x,i32 y)

{
  sprite_blit_to_surface(this,dest,surface,0xffffffff,x,y);
  return dest;
}

/* 005cef66 auto */
iptr __thiscall
sprite_draw_keyed
          (Sprite *this,iptr dest,iptr surface,uint key_color,i32 x,
          i32 y)

{
  sprite_blit_to_surface(this,dest,surface,key_color & 0xff,x,y);
  return dest;
}

/* 005cf126 auto */
iptr __thiscall
sprite_draw_silhouette
          (Sprite *this,iptr dest,iptr surface,i32 x,i32 y,
          i32 color)

{
  sprite_blit_silhouette_to_surface(this,dest,surface,0xffffffff,x,y,color);
  return dest;
}

/* 005cf23f auto */
void __thiscall sprite_merge_onto(Sprite *this,iptr dest)

{
  sprite_merge_at(this,(iptr)this,dest,0,0,0);
  return;
}

/* 005cf2ff auto */
void __thiscall sprite_lock(Sprite *this)

{
  uptr ptr;
  
  if (this->data_ptr == 0) {
    ptr = mem_handle_lock(this->data_handle);
    this->data_ptr = ptr;
  }
  return;
}

/* 005cf337 auto */
void __thiscall sprite_unlock(Sprite *this)

{
  uptr ptr;
  
  if (this->data_ptr != 0) {
    ptr = mem_handle_unlock(this->data_handle);
    this->data_ptr = ptr;
  }
  return;
}

/* 005cf36f auto */
bool __thiscall sprite_has_data(Sprite *this)

{
  return this->data_ptr != 0;
}

/* 005cf39b auto */
void __thiscall sprite_set_origin(SpriteOriginSetView *this,u32 x,u32 y)

{
  this->origin_x = x;
  this->origin_y = y;
  return;
}

/* 005cf3c5 auto */
void __thiscall sprite_get_origin(SpriteOriginGetView *this,iptr out_x,iptr out_y)

{
  *(u32 *)out_x = this->origin_x;
  *(u32 *)out_y = this->origin_y;
  return;
}

/* 005cf467 auto */
#define cursor (*(char * *)(frame_ + FRAME_OFF(4)))
#define run_len (*(int *)(frame_ + FRAME_OFF(12)))
#define rows (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall
sprite_replace_color(Sprite *this,i32 old_color,i32 new_color)

{
  int rows_left;
  int *len_ptr;
  char had_data;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  had_data = sprite_has_data(this);
  if (had_data == '\0') {
    sprite_lock(this);
    dbg_log((iptr)((u8 *)&g.d_00637ff8));
  }
  rows = rect_height((iptr)&this->bounds_rect);
  cursor = (char *)this->data_ptr;
  while (rows_left = rows - 1, rows != 0) {
    len_ptr = (int *)(cursor + 4);
    cursor += 8;
    run_len = *len_ptr;
    while (rows = rows_left, run_len != 0) {
      if (*cursor == (char)old_color) {
        *cursor = (char)new_color;
      }
      cursor++;
      run_len--;
    }
  }
  if (had_data == '\0') {
    sprite_unlock(this);
  }
  return;
}
#undef cursor
#undef run_len
#undef rows

/* 005cf64c auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define scan (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define height2 (*(int *)(frame_ + FRAME_OFF(24)))
#define out (*(i32 * *)(frame_ + FRAME_OFF(28)))
#define all_empty (*(int *)(frame_ + FRAME_OFF(32)))
#define row (*(int *)(frame_ + FRAME_OFF(36)))
#define key2 (*(u8 *)(frame_ + FRAME_OFF(40)))
#define col (*(int *)(frame_ + FRAME_OFF(44)))
#define run_lens (*(void * *)(frame_ + FRAME_OFF(48)))
#define was_locked (*(int *)(frame_ + FRAME_OFF(52)))
#define handle (*(int *)(frame_ + FRAME_OFF(56)))
#define top_row (*(u8 * *)(frame_ + FRAME_OFF(60)))
#define bottom_row (*(u8 * *)(frame_ + FRAME_OFF(64)))
#define width2 (*(iptr *)(frame_ + FRAME_OFF(68)))
#define run_starts (*(void * *)(frame_ + FRAME_OFF(72)))
#define min_left (*(int *)(frame_ + FRAME_OFF(76)))
#define first_row2 (*(int *)(frame_ + FRAME_OFF(80)))
#define max_right (*(int *)(frame_ + FRAME_OFF(84)))
#define last_row (*(int *)(frame_ + FRAME_OFF(88)))
#define total_size (*(int *)(frame_ + FRAME_OFF(92)))
#define run_ptrs (*(void * *)(frame_ + FRAME_OFF(96)))
int __thiscall
sprite_encode_from_surface(Sprite *this,iptr surface,int key_mode,iptr src_rect)

{
  char locked;
  int rect_h;
  int rect_w;
  u32 freed;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  was_locked = 1;
  all_empty = 1;
  SetRect(&rect,*(int *)src_rect,*(int *)(src_rect + 4),*(int *)(src_rect + 8),
          *(int *)(src_rect + 0xc));
  IntersectRect(&rect,&rect,(RECT *)(surface + 0x14));
  min_left = 10000;
  max_right = 0;
  total_size = 0;
  width2 = rect.right - rect.left;
  height2 = rect.bottom - rect.top;
  locked = surface_is_locked((DibSurface *)surface);
  if (locked == '\0') {
    dbg_log((iptr)((u8 *)&g.d_00638050));
    was_locked = 0;
    surface_lock((DibSurface *)surface);
  }
  top_row = (u8 *)surface_pixel_ptr((DibSurface *)surface,rect.left,rect.top);
  if (top_row == (u8 *)0x0) {
    dbg_logf_int2((iptr)((u8 *)&g.d_0063807c),rect.left,rect.top);
    if (was_locked == 0) {
      surface_unlock((DibSurface *)surface);
    }
    handle = 0;
  }
  else {
    if (key_mode == -1) {
      key2 = *top_row;
    }
    else if (key_mode != -2) {
      key2 = (u8)key_mode;
    }
    row = 0;
    while (row < height2) {
      scan = top_row;
      for (col = 0; col < width2; col++) {
        if ((*scan != key2) || (key_mode == -2)) {
          first_row2 = row;
          scan++;
          top_row = (u8 *)surface_prev_row((DibSurface *)surface,(iptr)top_row);
          row = height2;
          all_empty = 0;
          break;
        }
        scan++;
      }
      row++;
      top_row = (u8 *)surface_next_row((DibSurface *)surface,(iptr)top_row);
    }
    if (all_empty == 0) {
      bottom_row = (u8 *)surface_pixel_ptr
                                 ((DibSurface *)surface,rect.left,
                                  rect.top + height2 - 1);
      row = 0;
      while (row < height2) {
        scan = bottom_row;
        for (col = 0; col < width2; col++) {
          if ((*scan != key2) || (key_mode == -2)) {
            last_row = height2 - row;
            row = height2;
            scan++;
            break;
          }
          scan++;
        }
        row++;
        bottom_row = (u8 *)surface_prev_row((DibSurface *)surface,(iptr)bottom_row);
      }
      run_ptrs = operator_new(0xa00);
      run_starts = operator_new(0xa00);
      run_lens = operator_new(0xa00);
      if (((run_ptrs == (void *)0x0) || (run_starts == (void *)0x0)) || (run_lens == (void *)0x0)) {
        dbg_log((iptr)((u8 *)&g.d_006380b0));
        handle = 0;
      }
      else {
        row = 0;
        while (row < last_row - first_row2) {
          total_size += 8;
          *(i32 *)((int)run_starts + row * 4) = 0;
          *(i32 *)((int)run_lens + row * 4) = 0;
          scan = top_row;
          for (col = 0; col < width2; col++) {
            if ((*scan != key2) || (key_mode == -2)) {
              *(u8 **)((int)run_ptrs + row * 4) = scan;
              *(int *)((int)run_starts + row * 4) = col;
              break;
            }
            scan++;
          }
          if ((width2 != col) && (*(int *)((int)run_starts + row * 4) < min_left)) {
            min_left = *(int *)((int)run_starts + row * 4);
          }
          scan = top_row + width2;
          for (col = 0; scan = scan - 1, col < width2; col++)
          {
            if ((*scan != key2) || (key_mode == -2)) {
              *(iptr *)((int)run_lens + row * 4) =
                   (width2 - col) - *(int *)((int)run_starts + row * 4);
              total_size += *(int *)((int)run_lens + row * 4);
              break;
            }
          }
          if ((width2 != col) &&
             (max_right <
              *(int *)((int)run_lens + row * 4) + *(int *)((int)run_starts + row * 4))) {
            max_right = *(int *)((int)run_lens + row * 4) +
                       *(int *)((int)run_starts + row * 4);
          }
          row++;
          top_row = (u8 *)surface_next_row((DibSurface *)surface,(iptr)top_row);
        }
        if (this->data_ptr != 0) {
          sprite_unlock(this);
        }
        if (this->data_handle != 0) {
          freed = mem_handle_free(this->data_handle);
          this->data_handle = freed;
        }
        total_size += 8;
        handle = mem_handle_alloc(total_size);
        if (handle == 0) {
          dbg_logf((iptr)((u8 *)&g.d_006380ec),total_size);
          if (was_locked == 0) {
            surface_unlock((DibSurface *)surface);
          }
          operator_delete(run_ptrs);
          operator_delete(run_starts);
          operator_delete(run_lens);
        }
        else {
          SetRect((LPRECT)&this->bounds_rect,min_left,first_row2,max_right,last_row);
          rect_h = rect_height((iptr)&rect);
          rect_w = rect_width((iptr)&rect);
          SetRect((LPRECT)this,0,0,rect_w,rect_h);
          if (key_mode == -2) {
            this->key_color = '\0';
          }
          else {
            this->key_color = key2;
          }
          this->offset_x = 0;
          this->full_height = 0;
          out = (i32 *)mem_handle_lock(handle);
          for (row = 0; row < last_row - first_row2; row++) {
            *out = *(i32 *)((int)run_starts + row * 4);
            out[1] = *(i32 *)((int)run_lens + row * 4);
            out += 2;
            mem_move_src_dst(*(iptr *)((int)run_ptrs + row * 4),(iptr)out,
                         *(i32 *)((int)run_lens + row * 4));
            out = (i32 *)((int)out + *(int *)((int)run_lens + row * 4));
          }
          *out = 0;
          out = (i32 *)mem_handle_unlock(handle);
          if (was_locked == 0) {
            surface_unlock((DibSurface *)surface);
          }
          operator_delete(run_ptrs);
          operator_delete(run_starts);
          operator_delete(run_lens);
        }
      }
    }
    else {
      SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
      rect_h = rect_height((iptr)&rect);
      rect_w = rect_width((iptr)&rect);
      SetRect((LPRECT)this,0,0,rect_w,rect_h);
      if (key_mode == -2) {
        this->key_color = '\0';
      }
      else {
        this->key_color = key2;
      }
      this->offset_x = 0;
      this->full_height = 0;
      if (was_locked == 0) {
        surface_unlock((DibSurface *)surface);
      }
      this->data_ptr = 0;
      handle = 0;
    }
  }
  return handle;
}
#undef rect
#undef scan
#undef height2
#undef out
#undef all_empty
#undef row
#undef key2
#undef col
#undef run_lens
#undef was_locked
#undef handle
#undef top_row
#undef bottom_row
#undef width2
#undef run_starts
#undef min_left
#undef first_row2
#undef max_right
#undef last_row
#undef total_size
#undef run_ptrs

/* 005d056c auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define skip_x (*(int *)(frame_ + FRAME_OFF(0)))
#define dst_y (*(int *)(frame_ + FRAME_OFF(4)))
#define dst_x (*(int *)(frame_ + FRAME_OFF(8)))
#define key2 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define clip_rect (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define skip_y (*(int *)(frame_ + FRAME_OFF(36)))
#define trim_x (*(int *)(frame_ + FRAME_OFF(40)))
int * __thiscall
sprite_blit_to_surface
          (Sprite *this,int *out_rect,DibSurface *surface,int key_arg,int x,
          int y)

{
  int trim_y;
  int tmp;
  int scaled_trim_x;
  int scaled_trim_y;
  i32 clip_w;
  int scaled_h;
  BOOL BVar7;
  i32 surf_height;
  iptr dib;
  int top_down;
  int pitch;
  i32 bits;
  iptr scale_tbl;
  i32 clip_h;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (key_arg == -1) {
    (*(i8 *)((char *)&key_arg + 0)) = this->key_color;
  }
  else {
  }
  key2 = CONCAT31((*(i32 *)((char *)&key2 + 1)),(u8)key_arg);
  trim_x = this->bounds_rect - this->frame_rect;
  trim_y = this->bounds_top - this->frame_top;
  tmp = sprite_width(this);
  if (((tmp * gfx_scale_num) / gfx_scale_den < 0x401) &&
     (tmp = sprite_height(this), (tmp * gfx_scale_num) / gfx_scale_den < 0x401)) {
    scaled_trim_x = gfx_scale_length(trim_x,0,1);
    scaled_trim_y = gfx_scale_length(trim_y,0,1);
    tmp = gfx_scale_length(this->offset_x,0,0);
    dst_x = scaled_trim_x + tmp + x;
    tmp = gfx_scale_length(this->full_height,0,0);
    dst_y = scaled_trim_y + tmp + y;
    clip_h = 0;
    tmp = scaled_trim_y;
    clip_w = sprite_get_height(this);
    scaled_h = gfx_scale_length(clip_w,tmp,clip_h);
    clip_h = 0;
    tmp = scaled_trim_x;
    clip_w = sprite_get_width(this);
    tmp = gfx_scale_length(clip_w,tmp,clip_h);
    SetRect(&clip_rect,0,0,tmp,scaled_h);
    OffsetRect(&clip_rect,dst_x,dst_y);
    BVar7 = IntersectRect(&clip_rect,&clip_rect,(RECT *)&surface->clip_left);
    if (BVar7 != 0) {
      skip_x = 0;
      clip_w = rect_width((iptr)&clip_rect);
      if (dst_x < clip_rect.left) {
        skip_x = clip_rect.left - dst_x;
        dst_x = clip_rect.left;
      }
      skip_y = 0;
      clip_h = rect_height((iptr)&clip_rect);
      if (dst_y < clip_rect.top) {
        skip_y = clip_rect.top - dst_y;
        dst_y = clip_rect.top;
      }
      tmp = skip_y;
      scaled_h = trim_x;
      surf_height = surface_height(surface);
      dib = surface_get_dib(surface);
      top_down = dib_is_top_down(dib);
      pitch = surface_get_pitch(surface);
      pitch = ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * pitch;
      scale_tbl = gfx_scale_table;
      bits = surface_get_bits(surface);
      sprite_blit_rows_keyed(this->data_ptr,bits,scale_tbl,key2,dst_x,dst_y,pitch,surf_height,clip_w,clip_h
                   ,skip_x,tmp,scaled_h,trim_y,scaled_trim_x,scaled_trim_y);
    }
    *out_rect = clip_rect.left;
    out_rect[1] = clip_rect.top;
    out_rect[2] = clip_rect.right;
    out_rect[3] = clip_rect.bottom;
    return out_rect;
  }
  dbg_log((iptr)((u8 *)&g.d_006381cc));
  SetRect(&clip_rect,0,0,0,0);
  *out_rect = clip_rect.left;
  out_rect[1] = clip_rect.top;
  out_rect[2] = clip_rect.right;
  out_rect[3] = clip_rect.bottom;
  return out_rect;
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef skip_x
#undef dst_y
#undef dst_x
#undef key2
#undef clip_rect
#undef skip_y
#undef trim_x

/* 005d10cd auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define skip_x (*(int *)(frame_ + FRAME_OFF(0)))
#define dst_y (*(int *)(frame_ + FRAME_OFF(4)))
#define dst_x (*(int *)(frame_ + FRAME_OFF(8)))
#define key2 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define clip_rect (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define skip_y (*(int *)(frame_ + FRAME_OFF(36)))
#define trim_x (*(int *)(frame_ + FRAME_OFF(40)))
int * __thiscall
sprite_blit_silhouette_to_surface
          (Sprite *this,int *out_rect,DibSurface *surface,int key_arg,int x,
          int y,i32 color)

{
  int trim_y;
  int tmp;
  int scaled_trim_x;
  int scaled_trim_y;
  i32 clip_w;
  int scaled_h;
  BOOL BVar7;
  i32 surf_height;
  iptr dib;
  int top_down;
  int pitch;
  i32 bits;
  iptr scale_tbl;
  i32 clip_h;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (key_arg == -1) {
    (*(i8 *)((char *)&key_arg + 0)) = this->key_color;
  }
  else {
  }
  key2 = CONCAT31((*(i32 *)((char *)&key2 + 1)),(u8)key_arg);
  trim_x = this->bounds_rect - this->frame_rect;
  trim_y = this->bounds_top - this->frame_top;
  tmp = sprite_width(this);
  if (((tmp * gfx_scale_num) / gfx_scale_den < 0x401) &&
     (tmp = sprite_height(this), (tmp * gfx_scale_num) / gfx_scale_den < 0x401)) {
    scaled_trim_x = gfx_scale_length(trim_x,0,1);
    scaled_trim_y = gfx_scale_length(trim_y,0,1);
    tmp = gfx_scale_length(this->offset_x,0,0);
    dst_x = x + tmp + scaled_trim_x;
    tmp = gfx_scale_length(this->full_height,0,0);
    dst_y = y + tmp + scaled_trim_y;
    clip_h = 0;
    tmp = scaled_trim_y;
    clip_w = sprite_get_height(this);
    scaled_h = gfx_scale_length(clip_w,tmp,clip_h);
    clip_h = 0;
    tmp = scaled_trim_x;
    clip_w = sprite_get_width(this);
    tmp = gfx_scale_length(clip_w,tmp,clip_h);
    SetRect(&clip_rect,0,0,tmp,scaled_h);
    OffsetRect(&clip_rect,dst_x,dst_y);
    BVar7 = IntersectRect(&clip_rect,&clip_rect,(RECT *)&surface->clip_left);
    if (BVar7 != 0) {
      skip_x = 0;
      clip_w = rect_width((iptr)&clip_rect);
      if (dst_x < clip_rect.left) {
        skip_x = clip_rect.left - dst_x;
        dst_x = clip_rect.left;
      }
      skip_y = 0;
      clip_h = rect_height((iptr)&clip_rect);
      if (dst_y < clip_rect.top) {
        skip_y = clip_rect.top - dst_y;
        dst_y = clip_rect.top;
      }
      tmp = skip_y;
      scaled_h = trim_x;
      surf_height = surface_height(surface);
      dib = surface_get_dib(surface);
      top_down = dib_is_top_down(dib);
      pitch = surface_get_pitch(surface);
      pitch = ((-(uint)(top_down == 0) & 0xfffffffe) + 1) * pitch;
      scale_tbl = gfx_scale_table;
      bits = surface_get_bits(surface);
      sprite_blit_rows_solid(this->data_ptr,bits,scale_tbl,key2,dst_x,dst_y,pitch,surf_height,clip_w,clip_h
                   ,skip_x,tmp,scaled_h,trim_y,scaled_trim_x,scaled_trim_y,color);
    }
    *out_rect = clip_rect.left;
    out_rect[1] = clip_rect.top;
    out_rect[2] = clip_rect.right;
    out_rect[3] = clip_rect.bottom;
    return out_rect;
  }
  dbg_log((iptr)((u8 *)&g.d_0063827c));
  SetRect(&clip_rect,0,0,0,0);
  *out_rect = clip_rect.left;
  out_rect[1] = clip_rect.top;
  out_rect[2] = clip_rect.right;
  out_rect[3] = clip_rect.bottom;
  return out_rect;
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef skip_x
#undef dst_y
#undef dst_x
#undef key2
#undef clip_rect
#undef skip_y
#undef trim_x

/* 005d1612 auto */
#define written (*(int *)(frame_ + FRAME_OFF(0)))
#define dst_cursor (*(int * *)(frame_ + FRAME_OFF(4)))
#define src_cursor (*(int * *)(frame_ + FRAME_OFF(12)))
#define row (*(int *)(frame_ + FRAME_OFF(32)))
#define col (*(int *)(frame_ + FRAME_OFF(44)))
#define cols_left (*(int *)(frame_ + FRAME_OFF(60)))
#define out (*(int * *)(frame_ + FRAME_OFF(64)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(76)))
void __thiscall
sprite_merge_at
          (Sprite *this,iptr src,Sprite *dst,i32 unused,int dx,
          int dy)

{
  byte row_mask;
  LONG LVar2;
  LONG LVar3;
  int src_top;
  iptr src_w;
  int src_h;
  int merged;
  int dst_h;
  iptr new_h;
  int value;
  u32 new_handle;
  int dst_end;
  int src_start;
  int src_end;
  u32 freed;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(src + 0x34) != 0) {
    if (dst->data_handle == 0) {
      SetRect((LPRECT)dst,*(int *)src,*(int *)(src + 4),*(int *)(src + 8) + dx,
              *(int *)(src + 0xc) + dy);
      dst->bounds_rect = *(u32 *)(src + 0x10);
      dst->bounds_top = *(u32 *)(src + 0x14);
      *(i32 *)dst->bounds_right = *(i32 *)(src + 0x18);
      *(i32 *)(dst->bounds_bottom) = *(i32 *)(src + 0x1c);
      OffsetRect((LPRECT)&dst->bounds_rect,dx,dy);
      dst->offset_x = *(int *)(src + 0x20) + dx;
      dst->full_height = *(int *)(src + 0x24) + dy;
      dst->load_scale_num = *(u32 *)(src + 0x28);
      dst->load_scale_den = *(u32 *)(src + 0x2c);
      dst->key_color = *(u8 *)(src + 0x30);
      dst->data_handle = *(u32 *)(src + 0x34);
      mem_handle_clone((iptr)&dst->data_handle);
      sprite_lock(dst);
    }
    else {
      src_top = (*(int *)(src + 0x14) + dy) - dst->bounds_top;
      src_w = rect_width(src + 0x10);
      value = *(int *)(src + 0x10);
      src_h = rect_height(src + 0x10);
      merged = rect_width((iptr)&dst->bounds_rect);
      merged = dst->bounds_rect + merged;
      dst_h = rect_height((iptr)&dst->bounds_rect);
      new_h = src_h + src_top;
      if (src_h + src_top <= dst_h) {
        new_h = dst_h;
      }
      value = value + src_w + dx;
      if (value <= merged) {
        value = merged;
      }
      SetRect(&rect,0,0,value,new_h);
      LVar3 = rect.bottom;
      LVar2 = rect.right;
      sprite_lock((Sprite *)src);
      sprite_lock(dst);
      src_cursor = *(int **)(src + 0x38);
      dst_cursor = (int *)dst->data_ptr;
      new_handle = mem_handle_alloc(LVar2 * LVar3 + LVar3 * 8);
      out = (int *)mem_handle_lock(new_handle);
      for (row = 0; row < LVar3; row++) {
        row_mask = row < dst_h;
        if ((src_top <= row) && (row < src_h + src_top)) {
          row_mask = row_mask | 2;
        }
        switch(row_mask) {
        case 0:
          *out = 0;
          out[1] = 0;
          out += 2;
          break;
        case 1:
          *out = *dst_cursor;
          out[1] = dst_cursor[1];
          value = out[1];
          mem_move_src_dst((iptr)(dst_cursor + 2),(iptr)(out + 2),value);
          dst_cursor = (int *)((int)(dst_cursor + 2) + value);
          out = (int *)((int)(out + 2) + value);
          break;
        case 2:
          *out = *src_cursor + dx;
          out[1] = src_cursor[1];
          value = out[1];
          mem_move_src_dst((iptr)(src_cursor + 2),(iptr)(out + 2),value);
          src_cursor = (int *)((int)(src_cursor + 2) + value);
          out = (int *)((int)(out + 2) + value);
          break;
        case 3:
          value = *dst_cursor;
          dst_end = dst_cursor[1] + value;
          dst_cursor += 2;
          src_start = *src_cursor + dx;
          src_end = src_cursor[1] + src_start;
          src_cursor += 2;
          merged = value;
          if (src_start <= value) {
            merged = src_start;
          }
          *out = merged;
          merged = dst_end;
          if (dst_end <= src_end) {
            merged = src_end;
          }
          out[1] = merged - *out;
          out += 2;
          cols_left = LVar2;
          col = 0;
          while (cols_left != 0) {
            written = 0;
            if ((value <= col) && (col < dst_end)) {
              *(char *)out = (char)*dst_cursor;
              dst_cursor = (int *)((int)dst_cursor + 1);
              written = 1;
            }
            if ((src_start <= col) && (col < src_end)) {
              if ((uint)*(byte *)(src + 0x30) == (int)(char)*src_cursor) {
                if (written == 0) {
                  *(u8 *)out = dst->key_color;
                }
              }
              else {
                *(char *)out = (char)*src_cursor;
              }
              src_cursor = (int *)((int)src_cursor + 1);
              written++;
            }
            if (written != 0) {
              out = (int *)((int)out + 1);
            }
            col++;
            cols_left--;
          }
        }
      }
      OffsetRect(&rect,dst->bounds_rect,dst->bounds_top);
      dst->bounds_rect = rect.left;
      dst->bounds_top = rect.top;
      *(LONG *)dst->bounds_right = rect.right;
      *(LONG *)(dst->bounds_bottom) = rect.bottom;
      dst->frame_rect = rect.left;
      dst->frame_top = rect.top;
      *(LONG *)dst->frame_right = rect.right;
      *(LONG *)(dst->frame_bottom) = rect.bottom;
      if (dst->data_ptr != 0) {
        sprite_unlock(dst);
      }
      if (dst->data_handle != 0) {
        freed = mem_handle_free(dst->data_handle);
        dst->data_handle = freed;
      }
      mem_handle_unlock(new_handle);
      dst->data_handle = new_handle;
      sprite_lock(dst);
    }
  }
  return;
}
#undef written
#undef dst_cursor
#undef src_cursor
#undef row
#undef col
#undef cols_left
#undef out
#undef rect

/* 005d1b38 auto */
void __thiscall sprite_clear_fields(Sprite *this)

{
  SetRect((LPRECT)this,0,0,0,0);
  SetRect((LPRECT)&this->bounds_rect,0,0,0,0);
  this->offset_x = 0;
  this->full_height = 0;
  this->load_scale_num = 1;
  this->load_scale_den = 1;
  this->key_color = '\0';
  this->data_handle = 0;
  this->data_ptr = 0;
  return;
}

/* 005d1d00 auto */
#define gfx_scale_den (*(int *)((u8 *)&g.d_00637f9c))
#define gfx_scale_num (*(int *)((u8 *)&g.d_00637f98))
#define index (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl gfx_scale_length(int length,int start,int round_up)

{
  int result;
  bool positive;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (length == 0) {
    result = 0;
  }
  else {
    positive = -1 < length;
    if (!positive) {
      length = -length;
    }
    if (gfx_scale_num < gfx_scale_den) {
      index = start;
      result = *(int *)(gfx_scale_table + start * 4) + length;
      for (; *(int *)(gfx_scale_table + index * 4) < result; index++) {
      }
      if ((round_up == 0) && (*(int *)(gfx_scale_table + index * 4) != result)) {
        index--;
      }
    }
    else {
      index = start;
      for (; *(int *)(gfx_scale_table + index * 4) <
             *(int *)(gfx_scale_table + start * 4) + length; index++) {
      }
    }
    result = ((-(uint)positive & 2) - 1) * (index - start);
  }
  return result;
}
#undef gfx_scale_den
#undef gfx_scale_num
#undef index

/* 005de780 auto */
#define sys_color (*(i8 * *)(frame_ + FRAME_OFF(0)))
#define i (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl logpal_init_from_system(iptr logpal)

{
  HDC hdc;
  uint raster_caps;
  int num_reserved;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i16 *)logpal = 0x300;
  *(i16 *)(logpal + 2) = 0x100;
  hdc = GetDC((HWND)0x0);
  raster_caps = GetDeviceCaps(hdc,0x26);
  if ((raster_caps & 0x100) == 0) {
    palette_static_half_count = 0;
    gfx_palettized_display = 0;
  }
  else {
    num_reserved = GetDeviceCaps(hdc,0x18);
    palette_static_half_count = num_reserved / 2;
    GetSystemPaletteEntries(hdc,0,0x100,(LPPALETTEENTRY)(logpal + 4));
  }
  for (i = 0; i < palette_static_half_count; i++) {
    *(i8 *)(logpal + 7 + i * 4) = 0;
  }
  for (; i < 0x100 - palette_static_half_count; i++) {
    *(i8 *)(logpal + 4 + i * 4) = 0;
    *(i8 *)(logpal + 5 + i * 4) = 0;
    *(i8 *)(logpal + 6 + i * 4) = 0;
    *(i8 *)(logpal + 7 + i * 4) = 4;
  }
  for (; i < 0x100; i++) {
    *(i8 *)(logpal + 7 + i * 4) = 0;
  }
  if (gfx_palettized_display == 0) {
    sys_color = &logpal_static_system_colors;
    for (i = 0; i < 10; i++) {
      *(i8 *)(logpal + 4 + i * 4) = *sys_color;
      *(i8 *)(logpal + 5 + i * 4) = sys_color[1];
      *(i8 *)(logpal + 6 + i * 4) = sys_color[2];
      sys_color += 3;
    }
    for (i = 0xf6; i < 0x100; i++) {
      *(i8 *)(logpal + 4 + i * 4) = *sys_color;
      *(i8 *)(logpal + 5 + i * 4) = sys_color[1];
      *(i8 *)(logpal + 6 + i * 4) = sys_color[2];
      sys_color += 3;
    }
  }
  ReleaseDC((HWND)0x0,hdc);
  return;
}
#undef sys_color
#undef i

/* 005de984 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl logpal_reserve_range(iptr logpal,int first,int count)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (0x100 < count + first) {
    count = 0x100 - first;
  }
  for (i = first; i < count + first; i++) {
    *(i8 *)(logpal + 7 + i * 4) = 1;
  }
  return;
}
#undef i

/* 005dea62 auto */
void __cdecl palette_animate(iptr logpal,HPALETTE hpal,UINT first,UINT count)

{
  if (gfx_palettized_display == 1) {
    AnimatePalette(hpal,first,count,(PALETTEENTRY *)(first * 4 + logpal + 4));
  }
  return;
}

/* 005dea9e auto */
void __cdecl palette_get_entry_rgb(iptr logpal,int index,iptr out_red,iptr out_green,iptr out_blue)

{
  *(i8 *)out_red = *(i8 *)(logpal + 4 + index * 4);
  *(i8 *)out_green = *(i8 *)(logpal + 5 + index * 4);
  *(i8 *)out_blue = *(i8 *)(logpal + 6 + index * 4);
  return;
}

/* 005deadb auto */
void __cdecl
logpal_set_entry(iptr logpal,int index,i32 red,i32 green,i32 blue)

{
  *(i8 *)(logpal + 4 + index * 4) = (i8)red;
  *(i8 *)(logpal + 5 + index * 4) = (i8)green;
  *(i8 *)(logpal + 6 + index * 4) = (i8)blue;
  return;
}

/* 005deb12 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl
palette_set_entry_rgb(iptr logpal,int index,i32 red,i32 green,i32 blue)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(char *)(logpal + 4 + index * 4) = (char)red;
  *(char *)(logpal + 5 + index * 4) = (char)green;
  *(char *)(logpal + 6 + index * 4) = (char)blue;
  *(i8 *)(logpal + 7 + index * 4) = 4;
  for (i = 0; i < palette_static_half_count; i++) {
    if (((*(char *)(logpal + 4 + i * 4) == (char)red) &&
        (*(char *)(logpal + 5 + i * 4) == (char)green)) &&
       (*(char *)(logpal + 6 + i * 4) == (char)blue)) {
      *(i8 *)(logpal + 7 + index * 4) = 1;
    }
  }
  for (i = 0x100 - palette_static_half_count; i < 0x100; i++) {
    if (((*(char *)(logpal + 4 + i * 4) == (char)red) &&
        (*(char *)(logpal + 5 + i * 4) == (char)green)) &&
       (*(char *)(logpal + 6 + i * 4) == (char)blue)) {
      *(i8 *)(logpal + 7 + index * 4) = 1;
    }
  }
  return;
}
#undef i

/* 005dec4e auto */
#define hpal (*(i32 *)(frame_ + FRAME_OFF(0)))
HPALETTE __cdecl logpal_create_hpalette(iptr logpal)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (gfx_palettized_display == 1) {
    hpal = CreatePalette((LOGPALETTE *)logpal);
  }
  else {
    hpal = (HPALETTE)0x0;
  }
  return hpal;
}
#undef hpal

/* 005dec8a auto */
void __cdecl logpal_delete_hpalette(HGDIOBJ hpal)

{
  if (gfx_palettized_display == 1) {
    DeleteObject(hpal);
  }
  return;
}

/* 005decb1 auto */
void __cdecl logpal_apply_range(iptr logpal,HPALETTE hpal,UINT first,UINT count)

{
  if (gfx_palettized_display == 1) {
    SetPaletteEntries(hpal,first,count,(PALETTEENTRY *)(first * 4 + logpal + 4));
  }
  return;
}

/* 005ded12 auto */
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define offset (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl palette_copy_rgb_range(iptr logpal,iptr dest,int first,int count)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  offset = 0;
  for (index = first; index < count + first; index++) {
    *(i8 *)(offset + dest) = *(i8 *)(logpal + 4 + index * 4);
    *(i8 *)(offset + 1 + dest) = *(i8 *)(logpal + 5 + index * 4);
    *(i8 *)(offset + 2 + dest) = *(i8 *)(logpal + 6 + index * 4);
    offset += 3;
  }
  return;
}
#undef index
#undef offset

/* 005e35b0 auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define dib2 (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define bmi (*(BITMAPINFO (*)[24])(frame_ + FRAME_OFF(20)))
#define height2 (*(int *)(frame_ + FRAME_OFF(1084)))
#define bits2 (*(void * *)(frame_ + FRAME_OFF(1088)))
i32 * __cdecl dib_create(iptr rect)

{
  int width;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ old_bitmap;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  dib2 = (i32 *)0x0;
  width = *(int *)(rect + 8) - *(int *)rect;
  height2 = *(int *)(rect + 0xc) - *(int *)(rect + 4);
  if ((width < 1) || (height2 < 1)) {
    dib2 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log((iptr)((u8 *)&g.d_00638e74));
    }
    else {
      _memset(bmi,0,0x28);
      bmi[0].bmiHeader.biSize = 0x28;
      bmi[0].bmiHeader.biPlanes = 1;
      bmi[0].bmiHeader.biBitCount = 8;
      bmi[0].bmiHeader.biHeight = 1;
      bmi[0].bmiHeader.biWidth = dib_row_align4(width);
      if (0 < bmi[0].bmiHeader.biHeight) {
        if (dib_bottom_up_logged == 0) {
          dbg_log((iptr)((u8 *)&g.d_00638e20));
        }
        dib_bottom_up_logged = 1;
      }
      if (dib_row_order == -1) {
        bmi[0].bmiHeader.biHeight = height2;
      }
      else if (dib_row_order == 1) {
        bmi[0].bmiHeader.biHeight = -height2;
      }
      else {
        bmi[0].bmiHeader.biHeight = bmi[0].bmiHeader.biHeight * height2;
      }
      _memset(bmi[0].bmiColors,0,0x400);
      h = CreateDIBSection(hdc,bmi,0,&bits2,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log((iptr)((u8 *)&g.d_00638e44));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        dib2 = GlobalLock(hMem);
        *dib2 = hMem;
        dib2[1] = hdc;
        dib2[2] = 0;
        dib2[3] = h;
        dib2[8] = bmi[0].bmiHeader.biWidth;
        dib2[6] = width;
        dib2[7] = height2;
        old_bitmap = SelectObject(hdc,h);
        dib2[4] = old_bitmap;
        dib2[9] = bits2;
        if (bmi[0].bmiHeader.biHeight < 0) {
          dib2[5] = 1;
        }
        else {
          dib2[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return dib2;
}
#undef dib_row_order
#undef dib2
#undef bmi
#undef height2
#undef bits2

/* 005e388f auto */
i32 __cdecl dib_destroy(iptr dib)

{
  i32 handle;
  
  if (dib != 0) {
    if (*(int *)(dib + 4) != 0) {
      SelectObject(*(HDC *)(dib + 4),*(HGDIOBJ *)(dib + 0x10));
      DeleteObject(*(HGDIOBJ *)(dib + 0xc));
      DeleteDC(*(HDC *)(dib + 4));
    }
    if (*(int *)(dib + 8) != 0) {
      DeleteObject(*(HGDIOBJ *)(dib + 8));
    }
    handle = *(i32 *)dib;
    mem_handle_unlock(handle);
    mem_handle_free(handle);
  }
  return 0;
}

/* 005e392a auto */
i32 __cdecl dib_get_stride(iptr dib)

{
  i32 stride;
  
  if (dib == 0) {
    stride = 0;
  }
  else {
    stride = *(i32 *)(dib + 0x20);
  }
  return stride;
}

/* 005e395a auto */
uint __cdecl dib_is_top_down(iptr dib)

{
  return (uint)(*(int *)(dib + 0x14) == 1);
}

/* 005e3988 auto */
#define row (*(int *)(frame_ + FRAME_OFF(0)))
#define bottom_row (*(i32 *)(frame_ + FRAME_OFF(4)))
#define top_row (*(i32 *)(frame_ + FRAME_OFF(12)))
void __cdecl dib_flip_vertical(iptr dib)

{
  i32 tmp_handle;
  i32 tmp_row;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  top_row = dib_get_bits(dib);
  tmp_handle = mem_handle_alloc(*(i32 *)(dib + 0x20));
  tmp_row = mem_handle_lock(tmp_handle);
  bottom_row = (*(int *)(dib + 0x1c) - 1) * *(int *)(dib + 0x20) + top_row;
  for (row = 0; row < *(int *)(dib + 0x1c) / 2; row++) {
    crt_memmove(tmp_row,bottom_row,*(i32 *)(dib + 0x20));
    crt_memmove(bottom_row,top_row,*(i32 *)(dib + 0x20));
    crt_memmove(top_row,tmp_row,*(i32 *)(dib + 0x20));
    top_row += *(int *)(dib + 0x20);
    bottom_row -= *(int *)(dib + 0x20);
  }
  mem_handle_unlock(tmp_handle);
  mem_handle_free(tmp_handle);
  return;
}
#undef row
#undef bottom_row
#undef top_row

/* 005e3a81 auto */
i32 __cdecl dib_get_bits(iptr dib)

{
  i32 bits;
  
  if (dib == 0) {
    bits = 0;
  }
  else {
    bits = *(i32 *)(dib + 0x24);
  }
  return bits;
}

/* 005e3aa8 auto */
i32 __cdecl dib_unlock_bits(int dib)

{
  return 0;
}

/* 005e3b4c auto */
#define colors (*(RGBQUAD (*)[256])(frame_ + FRAME_OFF(0)))
#define index (*(uptr *)(frame_ + FRAME_OFF(1024)))
void __cdecl dib_set_color_table_range(iptr dib,GamePalette *palette,UINT first,UINT count)

{
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (index = first; (int)index < (int)(count + first); index++) {
    palette_get_entry
              (palette,index,(iptr)&colors[index].rgbRed,(iptr)&colors[index].rgbGreen,
               (iptr)(colors + index));
    colors[index].rgbReserved = '\0';
  }
  SetDIBColorTable(*(HDC *)(dib + 4),first,count,colors);
  return;
}
#undef colors
#undef index

/* 005e3bdc auto */
void __cdecl dib_set_palette(iptr dib,iptr palette)

{
  dib_set_color_table_range(dib,palette,0,0x100);
  return;
}

/* 005e3cb4 auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define color2 (*(RGBQUAD *)(frame_ + FRAME_OFF(4)))
#define old_font (*(HGDIOBJ *)(frame_ + FRAME_OFF(8)))
#define old_align (*(UINT *)(frame_ + FRAME_OFF(12)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(16)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(32)))
void __cdecl
dib_draw_text_at(iptr dib,int font,char *text,int x,int y,iptr clip_rect,
            uint align)

{
  int half_h;
  int half_w;
  size_t cchText;
  tagRECT *lprc;
  UINT format;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (font == 0) {
    dbg_log((iptr)((u8 *)&g.d_00638ea0));
  }
  else {
    font_data = (i32 *)mem_handle_lock(font);
    half_h = font_measure_height(font);
    half_h = y + half_h;
    half_w = font_measure_width(font,(iptr)text);
    SetRect(&text_rect,x,y,x + half_w,half_h);
    old_font = SelectObject(*(HDC *)(dib + 4),(HGDIOBJ)*font_data);
    GetDIBColorTable(*(HDC *)(dib + 4),(uint)gfx_text_color_index,1,&color2);
    SetTextColor(*(HDC *)(dib + 4),
                 (uint)CONCAT12(color2.rgbBlue,CONCAT11(color2.rgbGreen,color2.rgbRed)));
    half_h = rect_height((iptr)&text_rect);
    half_h = half_h / 2;
    half_w = rect_width((iptr)&text_rect);
    half_w = half_w / 2;
    OffsetRect(&text_rect,-half_w,-half_h);
    if ((align & 1) != 0) {
      OffsetRect(&text_rect,half_w,0);
    }
    if ((align & 4) != 0) {
      OffsetRect(&text_rect,0,half_h);
    }
    if ((align & 8) != 0) {
      OffsetRect(&text_rect,0,-half_h);
    }
    if ((align & 2) != 0) {
      OffsetRect(&text_rect,-half_w,0);
    }
    old_align = GetTextAlign(*(HDC *)(dib + 4));
    SetTextAlign(*(HDC *)(dib + 4),1);
    MoveToEx(*(HDC *)(dib + 4),text_rect.left,text_rect.top,(LPPOINT)0x0);
    IntersectRect(&text_rect,&text_rect,(RECT *)clip_rect);
    format = 0;
    lprc = &text_rect;
    cchText = _strlen(text);
    DrawTextA(*(HDC *)(dib + 4),text,cchText,lprc,format);
    SetTextAlign(*(HDC *)(dib + 4),old_align);
    SelectObject(*(HDC *)(dib + 4),old_font);
    mem_handle_unlock(font);
  }
  return;
}
#undef gfx_text_color_index
#undef color2
#undef old_font
#undef old_align
#undef text_rect
#undef font_data

/* 005e3eca auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define format (*(uint *)(frame_ + FRAME_OFF(4)))
#define color2 (*(RGBQUAD *)(frame_ + FRAME_OFF(8)))
#define old_font (*(HGDIOBJ *)(frame_ + FRAME_OFF(12)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(16)))
void __cdecl dib_draw_text_rect(iptr dib,int font,char *text,iptr rect,uint align)

{
  size_t cchText;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (font == 0) {
    dbg_log((iptr)((u8 *)&g.d_00638ec4));
  }
  else if (dib != 0) {
    font_data = (i32 *)mem_handle_lock(font);
    old_font = SelectObject(*(HDC *)(dib + 4),(HGDIOBJ)*font_data);
    GetDIBColorTable(*(HDC *)(dib + 4),(uint)gfx_text_color_index,1,&color2);
    SetTextColor(*(HDC *)(dib + 4),
                 (uint)CONCAT12(color2.rgbBlue,CONCAT11(color2.rgbGreen,color2.rgbRed)));
    format = 0;
    if (align == 0) {
      format = 0x25;
    }
    else {
      if ((align & 8) != 0) {
        format = 8;
      }
      if ((align & 2) != 0) {
        format = format | 2;
      }
    }
    cchText = _strlen(text);
    DrawTextA(*(HDC *)(dib + 4),text,cchText,(LPRECT)rect,format);
    SelectObject(*(HDC *)(dib + 4),old_font);
    mem_handle_unlock(font);
  }
  return;
}
#undef gfx_text_color_index
#undef format
#undef color2
#undef old_font
#undef font_data

/* 005e3feb auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define format (*(UINT *)(frame_ + FRAME_OFF(4)))
#define color2 (*(RGBQUAD *)(frame_ + FRAME_OFF(8)))
#define old_font (*(HGDIOBJ *)(frame_ + FRAME_OFF(12)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(16)))
void __cdecl dib_draw_text_wrap(iptr dib,int font,char *text,LPRECT rect,uint align)

{
  size_t cchText;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (font == 0) {
    dbg_log((iptr)((u8 *)&g.d_00638ee8));
  }
  else if (dib != 0) {
    font_data = (i32 *)mem_handle_lock(font);
    old_font = SelectObject(*(HDC *)(dib + 4),(HGDIOBJ)*font_data);
    GetDIBColorTable(*(HDC *)(dib + 4),(uint)gfx_text_color_index,1,&color2);
    SetTextColor(*(HDC *)(dib + 4),
                 (uint)CONCAT12(color2.rgbBlue,CONCAT11(color2.rgbGreen,color2.rgbRed)));
    format = 0x10;
    if (align == 0) {
      format = 0x11;
    }
    else if ((align & 2) != 0) {
      format = 0x12;
    }
    cchText = _strlen(text);
    DrawTextA(*(HDC *)(dib + 4),text,cchText,rect,format);
    SelectObject(*(HDC *)(dib + 4),old_font);
    mem_handle_unlock(font);
  }
  return;
}
#undef gfx_text_color_index
#undef format
#undef color2
#undef old_font
#undef font_data

/* 005e40fb auto */
#define gfx_text_color_index (*(byte *)((u8 *)&g.d_00637e78))
#define color2 (*(RGBQUAD *)(frame_ + FRAME_OFF(0)))
#define pen (*(HPEN *)(frame_ + FRAME_OFF(4)))
#define old_pen (*(HGDIOBJ *)(frame_ + FRAME_OFF(8)))
void __cdecl dib_draw_line(iptr dib,int x1,int y1,int x2,int y2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (dib != 0) {
    GetDIBColorTable(*(HDC *)(dib + 4),(uint)gfx_text_color_index,1,&color2);
    pen = CreatePen(0,1,(uint)CONCAT12(color2.rgbBlue,
                                           CONCAT11(color2.rgbGreen,color2.rgbRed)));
    old_pen = SelectObject(*(HDC *)(dib + 4),pen);
    MoveToEx(*(HDC *)(dib + 4),x1,y1,(LPPOINT)0x0);
    LineTo(*(HDC *)(dib + 4),x2,y2);
    SelectObject(*(HDC *)(dib + 4),old_pen);
    DeleteObject(pen);
  }
  return;
}
#undef gfx_text_color_index
#undef color2
#undef pen
#undef old_pen

/* 005e41ba auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define dib2 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define bmi (*(BITMAPINFO *)(frame_ + FRAME_OFF(20)))
#define green_mask (*(i32 *)(frame_ + FRAME_OFF(64)))
#define blue_mask (*(i32 *)(frame_ + FRAME_OFF(68)))
#define bits2 (*(void * *)(frame_ + FRAME_OFF(72)))
i32 * __cdecl dib_create16(iptr rect)

{
  int bmp_height;
  int width;
  int height;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ old_bitmap;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  dib2 = (i32 *)0x0;
  width = *(int *)(rect + 8) - *(int *)rect;
  height = *(int *)(rect + 0xc) - *(int *)(rect + 4);
  if ((width < 1) || (height < 1)) {
    dib2 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log((iptr)((u8 *)&g.d_00638f38));
    }
    else {
      _memset(&bmi,0,0x34);
      bmi.bmiHeader.biSize = 0x28;
      bmi.bmiHeader.biPlanes = 1;
      bmi.bmiHeader.biBitCount = 0x10;
      bmi.bmiHeader.biHeight = 1;
      bmi.bmiHeader.biCompression = 3;
      bmi.bmiColors[0].rgbBlue = '\0';
      bmi.bmiColors[0].rgbGreen = '|';
      bmi.bmiColors[0].rgbRed = '\0';
      bmi.bmiColors[0].rgbReserved = '\0';
      green_mask = 0x3e0;
      blue_mask = 0x1f;
      bmi.bmiHeader.biWidth = dib_row_align4(width);
      bmp_height = height;
      if (dib_row_order != -1) {
        if (dib_row_order == 1) {
          bmp_height = -height;
        }
        else {
          bmp_height = bmi.bmiHeader.biHeight * height;
        }
      }
      bmi.bmiHeader.biHeight = bmp_height;
      h = CreateDIBSection(hdc,&bmi,0,&bits2,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log((iptr)((u8 *)&g.d_00638f08));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        dib2 = GlobalLock(hMem);
        *dib2 = hMem;
        dib2[1] = hdc;
        dib2[2] = 0;
        dib2[3] = h;
        dib2[8] = bmi.bmiHeader.biWidth * 2;
        dib2[6] = width;
        dib2[7] = height;
        old_bitmap = SelectObject(hdc,h);
        dib2[4] = old_bitmap;
        dib2[9] = bits2;
        if (bmi.bmiHeader.biHeight < 0) {
          dib2[5] = 1;
        }
        else {
          dib2[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return dib2;
}
#undef dib_row_order
#undef dib2
#undef bmi
#undef green_mask
#undef blue_mask
#undef bits2

/* 005e43c5 auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define dib2 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define bmi (*(BITMAPINFO *)(frame_ + FRAME_OFF(20)))
#define bits2 (*(void * *)(frame_ + FRAME_OFF(64)))
i32 * __cdecl dib_create24(iptr rect)

{
  int bmp_height;
  int width;
  int height;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ old_bitmap;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  dib2 = (i32 *)0x0;
  width = *(int *)(rect + 8) - *(int *)rect;
  height = *(int *)(rect + 0xc) - *(int *)(rect + 4);
  if ((width < 1) || (height < 1)) {
    dib2 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log((iptr)((u8 *)&g.d_00638f94));
    }
    else {
      _memset(&bmi,0,0x2c);
      bmi.bmiHeader.biSize = 0x28;
      bmi.bmiHeader.biPlanes = 1;
      bmi.bmiHeader.biBitCount = 0x18;
      bmi.bmiHeader.biHeight = 1;
      bmi.bmiHeader.biWidth = dib_row_align4(width);
      bmp_height = height;
      if (dib_row_order != -1) {
        if (dib_row_order == 1) {
          bmp_height = -height;
        }
        else {
          bmp_height = bmi.bmiHeader.biHeight * height;
        }
      }
      bmi.bmiHeader.biHeight = bmp_height;
      h = CreateDIBSection(hdc,&bmi,0,&bits2,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log((iptr)((u8 *)&g.d_00638f64));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        dib2 = GlobalLock(hMem);
        *dib2 = hMem;
        dib2[1] = hdc;
        dib2[2] = 0;
        dib2[3] = h;
        dib2[8] = bmi.bmiHeader.biWidth * 3;
        dib2[6] = width;
        dib2[7] = height;
        old_bitmap = SelectObject(hdc,h);
        dib2[4] = old_bitmap;
        dib2[9] = bits2;
        if (bmi.bmiHeader.biHeight < 0) {
          dib2[5] = 1;
        }
        else {
          dib2[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return dib2;
}
#undef dib_row_order
#undef dib2
#undef bmi
#undef bits2

/* 005e45b5 auto */
#define dib_row_order (*(int *)((u8 *)&g.d_00638e18))
#define dib2 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define bmi (*(BITMAPINFO *)(frame_ + FRAME_OFF(20)))
#define bits2 (*(void * *)(frame_ + FRAME_OFF(64)))
i32 * __cdecl dib_create32(iptr rect)

{
  int bmp_height;
  int width;
  int height;
  HDC hdc;
  HBITMAP h;
  HGLOBAL hMem;
  HGDIOBJ old_bitmap;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  dib2 = (i32 *)0x0;
  width = *(int *)(rect + 8) - *(int *)rect;
  height = *(int *)(rect + 0xc) - *(int *)(rect + 4);
  if ((width < 1) || (height < 1)) {
    dib2 = (i32 *)0x0;
  }
  else {
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      dbg_log((iptr)((u8 *)&g.d_00638ff0));
    }
    else {
      _memset(&bmi,0,0x2c);
      bmi.bmiHeader.biSize = 0x28;
      bmi.bmiHeader.biPlanes = 1;
      bmi.bmiHeader.biBitCount = 0x20;
      bmi.bmiHeader.biHeight = 1;
      bmi.bmiHeader.biWidth = dib_row_align4(width);
      bmp_height = height;
      if (dib_row_order != -1) {
        if (dib_row_order == 1) {
          bmp_height = -height;
        }
        else {
          bmp_height = bmi.bmiHeader.biHeight * height;
        }
      }
      bmi.bmiHeader.biHeight = bmp_height;
      h = CreateDIBSection(hdc,&bmi,0,&bits2,(HANDLE)0x0,0);
      if (h == (HBITMAP)0x0) {
        dbg_log((iptr)((u8 *)&g.d_00638fc0));
        DeleteDC(hdc);
      }
      else {
        hMem = (HGLOBAL)mem_handle_alloc(0x28);
        dib2 = GlobalLock(hMem);
        *dib2 = hMem;
        dib2[1] = hdc;
        dib2[2] = 0;
        dib2[3] = h;
        dib2[8] = bmi.bmiHeader.biWidth << 2;
        dib2[6] = width;
        dib2[7] = height;
        old_bitmap = SelectObject(hdc,h);
        dib2[4] = old_bitmap;
        dib2[9] = bits2;
        if (bmi.bmiHeader.biHeight < 0) {
          dib2[5] = 1;
        }
        else {
          dib2[5] = 0;
        }
        SetBkMode(hdc,1);
      }
    }
  }
  return dib2;
}
#undef dib_row_order
#undef dib2
#undef bmi
#undef bits2

/* 005e4d60 auto */
#define code (*(i16 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl
gif_lzw_decode(iptr src,uint code_base,i32 min_code_size,uint pitch,int width,uint height,
            iptr dest)

{
  int table_handle;
  i32 result;
  iptr table;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  table_handle = mem_handle_alloc(0x6000);
  if (table_handle == 0) {
    dbg_log((iptr)((u8 *)&g.d_00639084));
    result = 0;
  }
  else {
    table = mem_handle_lock(table_handle);
    for (code = 0; code < 0x1000; code++) {
      *(i16 *)(table + code * 2) = 0xffff;
      *(ushort *)(table + 0x2000 + code * 2) = (ushort)(byte)code_base + code;
      *(i16 *)(table + 0x4000 + code * 2) = 1;
    }
    gif_lzw_decode_stream(src,dest,table,width,height,pitch,min_code_size);
    mem_handle_unlock(table_handle);
    mem_handle_free(table_handle);
    result = 1;
  }
  return result;
}
#undef code

/* 005e4e60 auto */
void __cdecl
dib_fill_rect8(iptr bits,uint color,int x,int y,uint width,int height,int pitch,
            int surf_height)

{
  uint color16;
  uint dwords;
  int abs_pitch;
  uint *dst;
  
  abs_pitch = pitch;
  if (pitch < 1) {
    y = (surf_height - 1) - y;
    abs_pitch = -pitch;
  }
  dst = (uint *)(bits + y * abs_pitch + x);
  color16 = color | color << 8;
  do {
    dwords = width >> 2;
    if (dwords != 0) {
      for (; dwords != 0; dwords--) {
        *dst = color16 | color << 0x10 | color << 0x18;
        dst++;
      }
    }
    if ((width & 2) != 0) {
      *(short *)dst = (short)color16;
      dst = (uint *)((int)dst + 2);
    }
    if ((width & 1) != 0) {
      *(char *)dst = (char)color;
      dst = (uint *)((int)dst + 1);
    }
    dst = (uint *)((int)dst + (pitch - width));
    height--;
  } while (height != 0);
  return;
}

/* 005e4f9b auto */
#define rows_left (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl
gfx_copy_pixels(int src_bits,int dst_bits,int src_x,int src_y,int dst_x,int dst_y,uint width,
            int height,int src_height,int dst_height,int src_pitch,int dst_pitch)

{
  i8 pixel;
  uint count;
  int abs_pitch;
  i32 *src;
  i32 *dst;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  abs_pitch = src_pitch;
  if (src_pitch < 1) {
    src_y = (src_height - 1) - src_y;
    abs_pitch = -src_pitch;
  }
  src = (i32 *)(src_bits + src_y * abs_pitch + src_x);
  abs_pitch = dst_pitch;
  if (dst_pitch < 1) {
    dst_y = (dst_height - 1) - dst_y;
    abs_pitch = -dst_pitch;
  }
  dst = (i32 *)(dst_bits + dst_y * abs_pitch + dst_x);
  rows_left = height;
  do {
    count = width >> 2;
    if (count != 0) {
      for (; count != 0; count--) {
        *dst = *src;
        src++;
        dst++;
      }
    }
    for (count = width & 3; count != 0; count--) {
      pixel = *(i8 *)src;
      src = (i32 *)((int)src + 1);
      *(i8 *)dst = pixel;
      dst = (i32 *)((int)dst + 1);
    }
    src = (i32 *)((int)src + (src_pitch - width));
    dst = (i32 *)((int)dst + (dst_pitch - width));
    rows_left--;
  } while (rows_left != 0);
  return;
}
#undef rows_left

/* 005e518e auto */
#define row_map (*(int * *)(frame_ + FRAME_OFF(0)))
/* WARNING: Unable to use type for symbol run_start */

void __cdecl
sprite_blit_rows_keyed(iptr sprite_data,int dst_bits,iptr scale_tbl,i32 key,int dst_x,int dst_y,
            int pitch,int surf_height,int width,int height,int skip_x,int skip_y,
            i32 trim_x,int src_row,int scaled_trim_x,int scaled_trim_y)

{
  int *col_map;
  int cols_left;
  int run_len;
  iptr offset;
  iptr row_data;
  char *dst_row;
  char *dst;
  int run_start;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  run_len = pitch;
  if (pitch < 1) {
    dst_y = (surf_height - 1) - dst_y;
    run_len = -pitch;
  }
  dst_row = (char *)(dst_bits + dst_y * run_len + dst_x);
  row_map = (int *)((skip_y + scaled_trim_y) * 4 + scale_tbl);
  row_data = sprite_data + 8;
  do {
    for (; src_row < *row_map; src_row++) {
      row_data = row_data + *(int *)(row_data - 4) + 8;
    }
    run_start = *(int *)(row_data - 8);
    run_len = *(int *)(row_data - 4);
    if (run_len != 0) {
      cols_left = width;
      dst = dst_row;
      for (col_map = (int *)((skip_x + scaled_trim_x) * 4 + scale_tbl); *col_map < run_start;
          col_map = col_map + 1) {
        dst++;
        cols_left--;
      }
      if (0 < cols_left) {
        do {
          offset = *col_map - run_start;
          if (run_len <= offset) break;
          if (*(char *)(offset + row_data) != (char)key) {
            *dst = *(char *)(offset + row_data);
          }
          col_map++;
          dst++;
          cols_left--;
        } while (cols_left != 0);
      }
    }
    dst_row += pitch;
    row_map++;
    height--;
    if (height < 1) {
      return;
    }
  } while( true );
}
#undef row_map

/* 005e52bf auto */
#define row_map (*(int * *)(frame_ + FRAME_OFF(0)))
/* WARNING: Unable to use type for symbol run_start */

void __cdecl
sprite_blit_rows_solid(iptr sprite_data,int dst_bits,iptr scale_tbl,i32 key,int dst_x,int dst_y,
            int pitch,int surf_height,int width,int height,int skip_x,int skip_y,
            i32 trim_x,int src_row,int scaled_trim_x,int scaled_trim_y,i32 color)

{
  int *col_map;
  int cols_left;
  int run_len;
  iptr offset;
  iptr row_data;
  i8 *dst_row;
  i8 *dst;
  int run_start;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  run_len = pitch;
  if (pitch < 1) {
    dst_y = (surf_height - 1) - dst_y;
    run_len = -pitch;
  }
  dst_row = (i8 *)(dst_bits + dst_y * run_len + dst_x);
  row_map = (int *)((skip_y + scaled_trim_y) * 4 + scale_tbl);
  row_data = sprite_data + 8;
  do {
    for (; src_row < *row_map; src_row++) {
      row_data = row_data + *(int *)(row_data - 4) + 8;
    }
    run_start = *(int *)(row_data - 8);
    run_len = *(int *)(row_data - 4);
    if (run_len != 0) {
      cols_left = width;
      dst = dst_row;
      for (col_map = (int *)((skip_x + scaled_trim_x) * 4 + scale_tbl); *col_map < run_start;
          col_map = col_map + 1) {
        dst++;
        cols_left--;
      }
      if (0 < cols_left) {
        do {
          offset = *col_map - run_start;
          if (run_len <= offset) break;
          if (*(char *)(offset + row_data) != (char)key) {
            *dst = (i8)color;
          }
          col_map++;
          dst++;
          cols_left--;
        } while (cols_left != 0);
      }
    }
    dst_row += pitch;
    row_map++;
    height--;
    if (height < 1) {
      return;
    }
  } while( true );
}
#undef row_map

/* 005e53f3 auto */
#define src_ptr (*(byte * *)(frame_ + FRAME_OFF(4)))
#define out_ptr (*(i8 * *)(frame_ + FRAME_OFF(8)))
#define next_code (*(ushort *)(frame_ + FRAME_OFF(12)))
#define code_bits (*(ushort *)(frame_ + FRAME_OFF(16)))
#define cur_code (*(ushort *)(frame_ + FRAME_OFF(20)))
#define bit_buf (*(uint *)(frame_ + FRAME_OFF(28)))
#define row_pos (*(ushort *)(frame_ + FRAME_OFF(32)))
#define dst (*(i8 * *)(frame_ + FRAME_OFF(60)))
#define code_mask (*(ushort *)(frame_ + FRAME_OFF(64)))
#define bit_count (*(ushort *)(frame_ + FRAME_OFF(76)))
#define prev_code (*(ushort *)(frame_ + FRAME_OFF(84)))
#define block_end (*(byte * *)(frame_ + FRAME_OFF(88)))
void __cdecl
gif_lzw_decode_stream(byte *src,i8 *dest,iptr prefix_tbl,int pitch,uint width,uint height,
            i32 min_code_size)

{
  byte *next_src;
  ushort prefix;
  ushort clear_code;
  ushort init_bits;
  ushort init_mask;
  ushort code;
  i8 *dst_end;
  uptr n;
  iptr len;
  uptr slot;
  iptr suffix_tbl;
  iptr length_tbl;
  i8 *from;
  i8 *row_next;
  i8 *to;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  suffix_tbl = prefix_tbl + 0x2000;
  length_tbl = prefix_tbl + 0x4000;
  row_pos = 0;
  src_ptr = src;
  block_end = src;
  dst = dest;
  dst_end = dest + (width & 0xffff) * (height & 0xffff) + 1;
  clear_code = 2 << ((byte)min_code_size & 0x1f);
  next_code = clear_code + 4;
  init_bits = (short)min_code_size + 1;
  init_mask = (2 << ((byte)init_bits & 0x1f)) - 2;
  bit_buf = 0;
  bit_count = 0;
  code_bits = init_bits;
  code_mask = init_mask;
  prev_code = clear_code;
LAB_005e549a:
  do {
    while( true ) {
      if (((short)pitch <= (short)row_pos) &&
         (row_pos = row_pos - (short)pitch, (ushort)((short)height - (short)pitch) != 0)) {
        row_next = dst + (ushort)((short)height - (short)pitch);
        to = row_next;
        from = dst;
        for (n = (uptr)row_pos; dst = row_next, n != 0; n--) {
          from--;
          to--;
          *to = *from;
        }
      }
      next_src = src_ptr;
      for (; src_ptr = next_src, bit_count < code_bits; bit_count += 8) {
        if (block_end == next_src) {
          src_ptr = next_src + 1;
          block_end = next_src + *next_src + 1;
        }
        next_src = src_ptr + 1;
        bit_buf = (uint)*src_ptr << ((byte)bit_count & 0x1f) | bit_buf;
      }
      code = (short)bit_buf << 1 & code_mask;
      if (next_code < code) {
        return;
      }
      bit_buf = bit_buf >> ((byte)code_bits & 0x1f);
      bit_count -= code_bits;
      if (code == (ushort)(clear_code + 2)) {
        return;
      }
      if (code != clear_code) break;
      next_code = clear_code + 4;
      code_bits = init_bits;
      code_mask = init_mask;
      prev_code = clear_code;
    }
    cur_code = code;
    if (prev_code != clear_code) {
      slot = (uptr)next_code;
      *(ushort *)(prefix_tbl + slot) = prev_code;
      *(i16 *)(length_tbl + slot) = *(i16 *)(length_tbl + (uint)prev_code);
      *(short *)(length_tbl + slot) = *(short *)(length_tbl + slot) + 1;
      if (code < next_code) {
        dst += *(ushort *)(length_tbl + (uint)code);
        row_pos += *(ushort *)(length_tbl + (uint)code);
        out_ptr = dst;
        if ((int)dst_end <= (int)dst) {
          return;
        }
        do {
          to = out_ptr - 1;
          *to = *(i8 *)(suffix_tbl + (uint)cur_code);
          prefix = *(ushort *)(prefix_tbl + (uint)cur_code);
          if (prefix == 0xffff) break;
          to = out_ptr - 2;
          *to = *(i8 *)(suffix_tbl + (uint)prefix);
          cur_code = *(ushort *)(prefix_tbl + (uint)prefix);
          out_ptr = to;
        } while (cur_code != 0xffff);
      }
      else {
        len = *(ushort *)(length_tbl + (uint)prev_code) + 1;
        dst += len;
        out_ptr = dst - 1;
        row_pos += (short)len;
        if ((int)dst_end <= (int)dst) {
          return;
        }
        do {
          to = out_ptr - 1;
          *to = *(i8 *)(suffix_tbl + (uint)prev_code);
          prefix = *(ushort *)(prefix_tbl + (uint)prev_code);
          if (prefix == 0xffff) break;
          to = out_ptr - 2;
          *to = *(i8 *)(suffix_tbl + (uint)prefix);
          prev_code = *(ushort *)(prefix_tbl + (uint)prefix);
          out_ptr = to;
        } while (prev_code != 0xffff);
        dst[-1] = *to;
      }
      *(i8 *)(suffix_tbl + (uint)next_code) = *to;
      next_code += 2;
      prev_code = code;
      if ((code_mask < next_code) && (code_bits != 0xc)) {
        code_bits++;
        code_mask = code_mask * 2 + 2;
      }
      goto LAB_005e549a;
    }
    dst += *(ushort *)(length_tbl + (uint)code);
    row_pos += *(ushort *)(length_tbl + (uint)code);
    out_ptr = dst;
    if ((int)dst_end <= (int)dst) {
      return;
    }
    do {
      out_ptr[-1] = *(i8 *)(suffix_tbl + (uint)cur_code);
      prefix = *(ushort *)(prefix_tbl + (uint)cur_code);
      prev_code = code;
      if (prefix == 0xffff) break;
      out_ptr[-2] = *(i8 *)(suffix_tbl + (uint)prefix);
      cur_code = *(ushort *)(prefix_tbl + (uint)prefix);
      out_ptr -= 2;
    } while (cur_code != 0xffff);
  } while( true );
}
#undef src_ptr
#undef out_ptr
#undef next_code
#undef code_bits
#undef cur_code
#undef bit_buf
#undef row_pos
#undef dst
#undef code_mask
#undef bit_count
#undef prev_code
#undef block_end

/* 005e5869 auto */
void __cdecl
dib_hline8(iptr bits,i32 color,uint length,int x,int y,int surf_height,
            int pitch)

{
  ushort dwords;
  int count;
  i32 *dst;
  
  if (pitch < 1) {
    pitch = -pitch;
    y = (surf_height - 1) - y;
  }
  dst = (i32 *)(bits + y * pitch + x);
  dwords = (ushort)length >> 2;
  count = CONCAT22((short)(length >> 0x10),dwords);
  if (dwords != 0) {
    for (; count != 0; count--) {
      *dst = CONCAT22(CONCAT11((i8)color,(i8)color),
                         CONCAT11((i8)color,(i8)color));
      dst++;
    }
  }
  if ((length & 2) != 0) {
    *(ushort *)dst = CONCAT11((i8)color,(i8)color);
    dst = (i32 *)((int)dst + 2);
  }
  if ((length & 1) != 0) {
    *(i8 *)dst = (i8)color;
  }
  return;
}

/* 005e58e7 auto */
void __cdecl
dib_vline8(iptr bits,i32 color,int length,iptr x,int y,int surf_height,
            iptr pitch)

{
  iptr abs_pitch;
  i8 *dst;
  
  abs_pitch = pitch;
  if (pitch < 1) {
    abs_pitch = -pitch;
    y = (surf_height - 1) - y;
  }
  dst = (i8 *)(bits + y * abs_pitch + x);
  do {
    *dst = (i8)color;
    dst += pitch;
    length--;
  } while (length != 0);
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
gdi_blit_transparent(HDC dst_dc,HGDIOBJ bitmap,int dst_x,int dst_y,int width,int height,int src_x
            ,int src_y)

{
  HDC hdc;
  HGDIOBJ h;
  HDC hdc_00;
  HDC hdc_01;
  HBITMAP h_00;
  HGDIOBJ h_01;
  HBITMAP h_02;
  HGDIOBJ h_03;
  
  hdc = CreateCompatibleDC(dst_dc);
  h = SelectObject(hdc,bitmap);
  hdc_00 = CreateCompatibleDC(dst_dc);
  hdc_01 = CreateCompatibleDC(dst_dc);
  h_00 = CreateCompatibleBitmap(dst_dc,width,height);
  h_01 = SelectObject(hdc_01,h_00);
  h_02 = CreateBitmap(width,height,1,1,(void *)0x0);
  h_03 = SelectObject(hdc_00,h_02);
  SetBkColor(hdc_01,0xffffff);
  SetTextColor(hdc_01,0);
  SetBkColor(hdc,0x808000);
  BitBlt(hdc_00,0,0,width,height,hdc,src_x,src_y,0xcc0020);
  BitBlt(hdc_01,0,0,width,height,dst_dc,dst_x,dst_y,0xcc0020);
  BitBlt(hdc_01,0,0,width,height,hdc,src_x,src_y,0x660046);
  BitBlt(hdc_01,0,0,width,height,hdc_00,0,0,0x8800c6);
  BitBlt(hdc_01,0,0,width,height,hdc,src_x,src_y,0x660046);
  BitBlt(dst_dc,dst_x,dst_y,width,height,hdc_01,0,0,0xcc0020);
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
