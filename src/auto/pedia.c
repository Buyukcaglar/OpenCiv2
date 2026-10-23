/* The game, the Civilopedia: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00451af0 auto */
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall
pedia_draw_category_body(DocumentWindow *this,i32 param_1,i32 param_2)

{
  int xLeft;
  int yTop;
  int iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_set_text_color_index(10);
  xLeft = this->content_left + panel_margin_x;
  yTop = this->content_top + panel_margin_y;
  iVar1 = rect_width((iptr)&this->content_left);
  iVar1 = (iVar1 + panel_margin_x * -2) / 2 - panel_margin_x;
  iVar2 = font_cached_height((GameFont *)&font_size21);
  iVar3 = font_cached_height((GameFont *)&font_size24_bold);
  local_8 = iVar2 * 9 + iVar3 + panel_margin_y * 0xd;
  SetRect(&local_18,xLeft,yTop,iVar1 + xLeft,local_8 + yTop);
  gfx_set_draw_target(ADDR(0x6a6668, ((u8 *)&g.d_006a6668)));
  pedia_dispatch_category_draw(this,local_18.left,local_18.top,local_18.right,local_18.bottom,param_1);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)this->pad_608);
  return;
}
#undef panel_margin_x
#undef local_18
#undef local_8

/* 00451bf0 auto */
#define local_40 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_3c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(u32 *)(frame_ + FRAME_OFF(8)))
#define local_30 (*(u32 *)(frame_ + FRAME_OFF(16)))
#define local_20 (*(u32 *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(u32 *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(u32 *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(u32 *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(56)))
void __thiscall pedia_update_controls(MediaWindow *this)

{
  u32 uVar1;
  int iVar2;
  Control *pCVar3;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  control_hide((Control *)(this[3].pad_4a4 + 0x1c));
  control_hide((Control *)(this[3].pad_4a4 + 0x58));
  control_hide((Control *)(this[3].pad_4a4 + 0x94));
  control_hide((Control *)(this[3].pad_4a4 + 0xd0));
  control_hide((Control *)&this[3].field_5b0);
  control_hide((Control *)(this[3].pad_5e8 + 4));
  control_hide((Control *)&this[4].field_c);
  control_hide((Control *)&this[4].field_270);
  control_hide((Control *)this[4].pad_48);
  control_hide((Control *)(this[4].pad_48 + 0x3c));
  control_hide((Control *)(this[4].pad_48 + 0x78));
  control_hide((Control *)(this[4].pad_48 + 0xb4));
  control_hide((Control *)&this[4].field_138);
  control_hide((Control *)(this[4].pad_15c + 0x18));
  control_hide((Control *)(this[4].pad_15c + 0x54));
  control_hide((Control *)&this[4].field_1ec);
  control_hide((Control *)&this[4].field_228);
  ctrl_set_text((ControlTextView *)&this[4].field_228,ADDR(0x626854, ((u8 *)&g.d_00626854)));
  if (this[4].field_2b0 != 0) {
    if ((Hotspot *)this[4].field_2b0 != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)this[4].field_2b0,1);
    }
    this[4].field_2b0 = 0;
  }
  uVar1 = this->border_width;
  if (uVar1 == 0) {
    this[4].field_2b4 = this->content_left;
    this[4].field_2b8 = this->content_top;
    this[4].field_2bc = this->content_right;
    this[4].field_2c0 = this->content_bottom;
    iVar2 = GetSystemMetrics(3);
    this[4].field_2c0 -= iVar2;
    if (this->caption_height == 8) {
      ctrl_show_and_redraw((Control *)this[4].pad_48);
      ctrl_show_and_redraw((Control *)(this[3].pad_4a4 + 0x58));
    }
    else if (this->caption_height == 1) {
      ctrl_show_and_redraw((Control *)(this[4].pad_48 + 0x3c));
      ctrl_show_and_redraw((Control *)(this[4].pad_48 + 0x78));
      ctrl_show_and_redraw((Control *)(this[4].pad_48 + 0xb4));
      ctrl_show_and_redraw((Control *)&this[4].field_270);
      if (this[4].field_2b0 == 0) {
        local_20 = this->content_left;
        local_1c = this->content_top;
        local_18 = this->content_right;
        local_14 = this->content_bottom;
        iVar2 = GetSystemMetrics(3);
        local_14 -= iVar2;
        pCVar3 = operator_new(0x40);
        local_8 = 0;
        if (pCVar3 == (Control *)0x0) {
          local_30 = 0;
        }
        else {
          local_30 = hotspot_ctor(pCVar3);
        }
        local_8 = 0xffffffff;
        this[4].field_2b0 = local_30;
        if (this == (MediaWindow *)0x0) {
          local_3c = (u8 *)0x0;
        }
        else {
          local_3c = this->pad_48;
        }
        hotspot_create
                  ((ClickControl *)this[4].field_2b0,(iptr)local_3c,0xfa9,(iptr)&local_20);
        hotspot_set_click_callback((HotspotClickSetView *)this[4].field_2b0,ADDR(0x402270, pedia_list_on_click));
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)this[4].field_2b0,ADDR(0x40196f, pedia_toggle_describe));
        ctrl_show_and_redraw((Control *)this[4].field_2b0);
      }
    }
    else {
      ctrl_show_and_redraw((Control *)(this[3].pad_4a4 + 0x1c));
      ctrl_show_and_redraw((Control *)&this[4].field_270);
      ctrl_show_and_redraw((Control *)(this[3].pad_4a4 + 0x58));
      if (this[4].field_2b0 == 0) {
        local_20 = this->content_left;
        local_1c = this->content_top;
        local_18 = this->content_right;
        local_14 = this->content_bottom;
        iVar2 = GetSystemMetrics(3);
        local_14 -= iVar2;
        pCVar3 = operator_new(0x40);
        local_8 = 1;
        if (pCVar3 == (Control *)0x0) {
          local_38 = 0;
        }
        else {
          local_38 = hotspot_ctor(pCVar3);
        }
        local_8 = 0xffffffff;
        this[4].field_2b0 = local_38;
        if (this == (MediaWindow *)0x0) {
          local_40 = (u8 *)0x0;
        }
        else {
          local_40 = this->pad_48;
        }
        hotspot_create
                  ((ClickControl *)this[4].field_2b0,(iptr)local_40,0xfa9,(iptr)&local_20);
        hotspot_set_click_callback((HotspotClickSetView *)this[4].field_2b0,ADDR(0x402270, pedia_list_on_click));
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)this[4].field_2b0,ADDR(0x40196f, pedia_toggle_describe));
        ctrl_show_and_redraw((Control *)this[4].field_2b0);
      }
    }
  }
  else if (uVar1 == 1) {
    if ((this->caption_height == 6) || (this->caption_height == 7)) {
      ctrl_show_and_redraw((Control *)(this[3].pad_5e8 + 4));
      ctrl_show_and_redraw((Control *)&this[4].field_c);
    }
    else if (this->caption_height == 1) {
      ctrl_show_and_redraw((Control *)&this[4].field_138);
      ctrl_show_and_redraw((Control *)(this[4].pad_15c + 0x18));
      ctrl_show_and_redraw((Control *)(this[4].pad_15c + 0x54));
      ctrl_show_and_redraw((Control *)&this[4].field_1ec);
    }
    else {
      ctrl_show_and_redraw((Control *)(this[3].pad_4a4 + 0x94));
      ctrl_show_and_redraw((Control *)(this[3].pad_4a4 + 0xd0));
      ctrl_show_and_redraw((Control *)&this[3].field_5b0);
    }
  }
  else if (uVar1 == 2) {
    ctrl_show_and_redraw((Control *)(this[3].pad_5e8 + 4));
    ctrl_show_and_redraw((Control *)&this[4].field_c);
  }
  ui_pump_messages();
  return;
}
#undef local_40
#undef local_3c
#undef local_38
#undef local_30
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 00452188 auto */
void __thiscall
pedia_dispatch_category_draw
          (DocumentWindow *this,i32 param_1,i32 param_2,i32 param_3,
          i32 param_4,i32 param_5)

{
  u32 pargs_[5] = {(u32)(uptr)param_1, (u32)(uptr)param_2, (u32)(uptr)param_3, (u32)(uptr)param_4, (u32)(uptr)param_5};  /* the arguments, contiguous as on the original stack */
#define param_1 (*(i32 *)&pargs_[0])
#define param_2 (*(i32 *)&pargs_[1])
#define param_3 (*(i32 *)&pargs_[2])
#define param_4 (*(i32 *)&pargs_[3])
#define param_5 (*(i32 *)&pargs_[4])
  switch(param_5) {
  case 0:
    break;
  case 1:
    if (this->border_width == 0) {
      pedia_init_advance_list((PediaAdvanceListView *)this,(iptr)&param_1);
    }
    else {
      pedia_draw_advance_page(this);
    }
    break;
  case 2:
    if (this->border_width == 0) {
      pedia_init_improvement_list(this,(iptr)&param_1);
    }
    else {
      pedia_draw_improvement_page(this);
    }
    break;
  case 3:
    if (this->border_width == 0) {
      pedia_init_wonder_list((MediaWindow *)this,(iptr)&param_1);
    }
    else {
      pedia_draw_improvement(this);
    }
    break;
  case 4:
    if (this->border_width == 0) {
      pedia_show_unit_list((MediaWindow *)this,(iptr)&param_1);
    }
    else {
      pedia_draw_unit_page(this);
    }
    break;
  case 5:
    if (this->border_width == 0) {
      pedia_init_terrain_list((MediaWindow *)this,(iptr)&param_1);
    }
    break;
  case 6:
    if (this->border_width == 0) {
      pedia_init_government_list((MediaWindow *)this,(iptr)&param_1);
    }
    break;
  case 7:
    if (this->border_width == 0) {
      pedia_init_concept_list((MediaWindow *)this,(iptr)&param_1);
    }
    break;
  case 8:
    pedia_draw_advance_tree(this);
  }
  return;
}
#undef param_1
#undef param_2
#undef param_3
#undef param_4
#undef param_5

/* 00452315: written by hand in src/game/retvals.c */

/* 00452768 auto */
#define local_10c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_108 (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
void __thiscall pedia_update_describe_button(ListPaneWindow *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((game.game_flags & 0x80) != 0) && (this->caption_height != 7)) &&
     (iVar1 = _strcmp(&scenario_dir_path,&game_home_dir), iVar1 != 0)) {
    __chdir(&scenario_dir_path);
    crt_strcpy(local_108,s_describe__006268fc);
    crt_strcat(local_108,&lang_file_ext);
    iVar1 = file_exists((iptr)local_108);
    if (iVar1 == 0) {
      ctrl_disable((Control *)(this[0x15].pad_48 + 0x34));
      __chdir(&game_home_dir);
      return;
    }
    __chdir(&game_home_dir);
  }
  switch(this->caption_height) {
  case 1:
    local_10c = *(int *)(this[5].pad_48 + param_1 * 4 + 0x88);
    break;
  case 2:
    local_10c = *(int *)(this[8].pad_48 + param_1 * 4 + 0x58);
    break;
  case 3:
    local_10c = *(int *)(this[9].pad_48 + param_1 * 4 + 0x78);
    break;
  case 4:
    local_10c = *(int *)(this[10].pad_48 + param_1 * 4 + 0x40);
    break;
  case 5:
    local_10c = *(int *)(this[0xc].pad_48 + param_1 * 4 + 0x38);
    break;
  case 6:
    local_10c = *(int *)(this[0xc].pad_48 + param_1 * 4 - 4);
    break;
  case 7:
    local_10c = *(int *)(this[0xd].pad_48 + param_1 * 4 + 0x28);
  }
  if (local_10c < 0) {
    if (this->caption_height == 1) {
      ctrl_disable((Control *)(this[0x17].pad_48 + 0x54));
    }
    else {
      ctrl_disable((Control *)(this[0x15].pad_48 + 0x34));
    }
  }
  else if (this->caption_height == 1) {
    ctrl_enable((Control *)(this[0x17].pad_48 + 0x54));
  }
  else {
    ctrl_enable((Control *)(this[0x15].pad_48 + 0x34));
  }
  return;
}
#undef local_10c
#undef local_108

/* 004529df auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_2c (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
void __cdecl hyperlink_register_class(void)

{
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (hyperlink_class_registered == 0) {
    hyperlink_class_registered = 1;
    local_2c.style = 0x88;
    local_2c.lpfnWndProc = ctrl_default_wndproc;
    local_2c.cbClsExtra = 0;
    local_2c.cbWndExtra = 0x10;
    local_2c.hInstance = app_hinstance;
    local_2c.hIcon = (HICON)0x0;
    local_2c.hCursor = LoadCursorA(app_hinstance,(LPCSTR)0x212);
    local_2c.hbrBackground = (HBRUSH)0x0;
    local_2c.lpszMenuName = (LPCSTR)0x0;
    local_2c.lpszClassName = s_MSHyperTextClass_00626908;
    RegisterClassA(&local_2c);
  }
  return;
}
#undef app_hinstance
#undef local_2c

/* 00452a67 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall hyperlink_dtor(HyperlinkDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    region_dispose(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00452ac1 */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00452ae2 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
HWND __cdecl hyperlink_create_hwnd(int *param_1,iptr param_2)

{
  WndBase *this;
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  HWND pHVar4;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  
  hyperlink_register_class();
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar1 = wnd_get_window(this);
  pHVar4 = *(HWND *)(iVar1 + 4);
  iVar2 = rect_height((iptr)param_1);
  iVar3 = rect_width((iptr)param_1);
  pHVar4 = CreateWindowExA(4,s_MSHyperTextClass_00626920,&hyperlink_window_title_str,0x50000000,*param_1,
                           param_1[1],iVar3,iVar2,pHVar4,hMenu,hInstance,lpParam);
  iVar3 = ctrl_init_block(pHVar4,param_2);
  *(i32 *)(iVar3 + 0x2c) = 1;
  SetWindowLongA(pHVar4,-4,ADDR(0x5c8caf, hotspot_wndproc));
  return pHVar4;
}
#undef app_hinstance

/* 00452b89 auto */
void __thiscall
hyperlink_create(ClickControl *this,iptr param_1,i32 param_2,iptr param_3)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  ctrl_init((Control *)this,param_1,1,param_2,param_3);
  this->is_enabled = 0;
  this->on_click = 0;
  this->on_select = 0;
  this->font = 0;
  this->scroll_pos = 0;
  uVar1 = hyperlink_create_hwnd(param_3,(iptr)this);
  this->hwnd = uVar1;
  return;
}

/* 00452c14 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_34 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_2c (*(u32 * *)(frame_ + FRAME_OFF(12)))
#define local_24 (*(u32 *)(frame_ + FRAME_OFF(20)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(48)))
void __thiscall
pedia_add_link
          (DocumentWindow *this,iptr param_1,int param_2,int param_3,i32 param_4,
          i32 param_5,i32 param_6,i32 param_7,i32 param_8)

{
  int iVar1;
  int iVar2;
  uptr sVar3;
  PediaLinkCtorView *pCVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  u32 pargs_[4] = {(u32)(uptr)param_5, (u32)(uptr)param_6, (u32)(uptr)param_7, (u32)(uptr)param_8};  /* the arguments, contiguous as on the original stack */
#define param_5 (*(i32 *)&pargs_[0])
#define param_6 (*(i32 *)&pargs_[1])
#define param_7 (*(i32 *)&pargs_[2])
#define param_8 (*(i32 *)&pargs_[3])
  
  local_8 = 0xffffffff;
  switch(param_4) {
  case 0:
    local_24 = 0;
    while (((int)local_24 < (int)this->pedia_advance_count &&
           (*(int *)(this->pad_65c + local_24 * 4 + 400) != param_1))) {
      local_24++;
    }
    if (this->pedia_advance_count == local_24) goto switchD_00452e28_default;
    break;
  case 1:
    local_24 = 0;
    while (((int)local_24 < (int)this->pedia_improve_count &&
           (*(int *)(this->pad_980 + local_24 * 4 + 0x9c) != param_1))) {
      local_24++;
    }
    if (this->pedia_improve_count == local_24) goto switchD_00452e28_default;
    break;
  case 2:
    for (local_24 = 0;
        ((int)local_24 < *(int *)(this[1].pad_48 + 0x48) &&
        (*(int *)(this[1].pad_104 + local_24 * 4) != param_1)); local_24++) {
    }
    if (*(u32 *)(this[1].pad_48 + 0x48) == local_24) goto switchD_00452e28_default;
    break;
  case 3:
    local_24 = 0;
    while (((int)local_24 < *(int *)(this[1].pad_15c + 0x18) &&
           (*(int *)(this[1].pad_274 + local_24 * 4 - 4) != param_1))) {
      local_24++;
    }
    if (*(u32 *)(this[1].pad_15c + 0x18) == local_24) goto switchD_00452e28_default;
    break;
  case 4:
    local_24 = 0;
    while (((int)local_24 < (int)this[1].field_3a4 &&
           (*(int *)(this[1].pad_3c0 + local_24 * 4 + 0x6c) != param_1))) {
      local_24++;
    }
    if (this[1].field_3a4 == local_24) goto switchD_00452e28_default;
    break;
  default:
    goto switchD_00452e28_default;
  }
  while( true ) {
    iVar1 = font_text_width((GameFont *)&font_size21,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    iVar2 = rect_width((iptr)&param_5);
    if (iVar1 <= iVar2) break;
    sVar3 = _strlen(&text_buffer);
    (&text_buffer_minus1)[sVar3] = 0;
  }
  if ((this->caption_height == 8) && (iVar1 = civ_has_advance(human_civ,param_1), iVar1 != 0)) {
    gfx_set_text_color_index(0x6a);
  }
  else {
    gfx_set_text_color_index(0x55);
  }
  iVar1 = font_cached_height((GameFont *)&font_size21);
  iVar4 = param_3 + iVar1 - 2;
  iVar1 = font_text_width((GameFont *)&font_size21,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  iVar1 = param_2 + iVar1;
  iVar2 = font_cached_height((GameFont *)&font_size21);
  surface_draw_line((DibSurface *)this,param_2,param_3 + iVar2 - 2,iVar1,iVar4);
  gfx_set_text_color_index(10);
  surface_draw_text((DibSurface *)this,ADDR(0x67a798, ((u8 *)&g.d_0067a798)),ADDR(0x679640, ((u8 *)&g.d_00679640)),param_2 + 1,param_3,5);
  if ((this->caption_height == 8) && (iVar1 = civ_has_advance(human_civ,param_1), iVar1 != 0)) {
    gfx_set_text_color_index(0x6a);
  }
  else {
    gfx_set_text_color_index(0x55);
  }
  surface_draw_text((DibSurface *)this,ADDR(0x67a798, ((u8 *)&g.d_0067a798)),ADDR(0x679640, ((u8 *)&g.d_00679640)),param_2,param_3,5);
  gfx_set_text_color_index(10);
  pCVar3 = operator_new(0x48);
  local_8 = 0;
  if (pCVar3 == (PediaLinkCtorView *)0x0) {
    local_2c = (u32 *)0x0;
  }
  else {
    local_2c = (u32 *)pedia_link_ctor(pCVar3);
  }
  local_8 = 0xffffffff;
  *local_2c = local_24;
  local_2c[0x11] = 0;
  local_1c = 0;
  if (*(int *)(this[3].pad_48 + 0x80) == 0) {
    *(u32 **)(this[3].pad_48 + 0x80) = local_2c;
  }
  else {
    local_1c = 1;
    for (local_18 = *(iptr *)(this[3].pad_48 + 0x80); *(int *)(local_18 + 0x44) != 0;
        local_18 = *(iptr *)(local_18 + 0x44)) {
      local_1c++;
    }
    *(u32 **)(local_18 + 0x44) = local_2c;
  }
  if (this == (DocumentWindow *)0x0) {
    local_34 = (u8 *)0x0;
  }
  else {
    local_34 = this->pad_48;
  }
  hyperlink_create
            ((ClickControl *)(local_2c + 1),(iptr)local_34,local_1c + 0xfb4,(iptr)&param_5);
  switch(param_4) {
  case 0:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(local_2c + 1),ADDR(0x401c76, pedia_link_on_click_advance));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(local_2c + 1),ADDR(0x401c76, pedia_link_on_click_advance));
    break;
  case 1:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(local_2c + 1),ADDR(0x4019ce, pedia_link_on_click_improvement));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(local_2c + 1),ADDR(0x4019ce, pedia_link_on_click_improvement));
    break;
  case 2:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(local_2c + 1),ADDR(0x403729, pedia_link_on_click_wonder));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(local_2c + 1),ADDR(0x403729, pedia_link_on_click_wonder));
    break;
  case 3:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(local_2c + 1),ADDR(0x402333, pedia_link_on_click_unit));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(local_2c + 1),ADDR(0x402333, pedia_link_on_click_unit));
    break;
  case 4:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(local_2c + 1),ADDR(0x4019b0, pedia_link_on_click_terrain));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(local_2c + 1),ADDR(0x4019b0, pedia_link_on_click_terrain));
  }
  ctrl_show_and_redraw((Control *)(local_2c + 1));
switchD_00452e28_default:
  return;
}
#undef human_civ
#undef text_buffer
#undef local_34
#undef local_2c
#undef local_24
#undef local_1c
#undef local_18
#undef local_10
#undef puStack_c
#undef local_8
#undef param_5
#undef param_6
#undef param_7
#undef param_8

/* 004531b8 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_advance(int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1 - 0xfb4;
  for (local_c = pedia_link_list; (local_8 != 0 && (local_c != (i32 *)0x0));
      local_c = (i32 *)local_c[0x11]) {
    local_8--;
  }
  if (local_c != (i32 *)0x0) {
    pedia_category = 1;
    pedia_page_mode = 0;
    pedia_selected_item = *local_c;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef local_c
#undef local_8

/* 0045323a auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_improvement(int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1 - 0xfb4;
  for (local_c = pedia_link_list; (local_8 != 0 && (local_c != (i32 *)0x0));
      local_c = (i32 *)local_c[0x11]) {
    local_8--;
  }
  if (local_c != (i32 *)0x0) {
    pedia_category = 2;
    pedia_page_mode = 0;
    pedia_selected_item = *local_c;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef local_c
#undef local_8

/* 004532bc auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_wonder(int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1 - 0xfb4;
  for (local_c = pedia_link_list; (local_8 != 0 && (local_c != (i32 *)0x0));
      local_c = (i32 *)local_c[0x11]) {
    local_8--;
  }
  if (local_c != (i32 *)0x0) {
    pedia_category = 3;
    pedia_page_mode = 0;
    pedia_selected_item = *local_c;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef local_c
#undef local_8

/* 0045333e auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_unit(int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1 - 0xfb4;
  for (local_c = pedia_link_list; (local_8 != 0 && (local_c != (i32 *)0x0));
      local_c = (i32 *)local_c[0x11]) {
    local_8--;
  }
  if (local_c != (i32 *)0x0) {
    pedia_category = 4;
    pedia_page_mode = 0;
    pedia_selected_item = *local_c;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef local_c
#undef local_8

/* 004533c0 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_terrain(int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1 - 0xfb4;
  for (local_c = pedia_link_list; (local_8 != 0 && (local_c != (i32 *)0x0));
      local_c = (i32 *)local_c[0x11]) {
    local_8--;
  }
  if (local_c != (i32 *)0x0) {
    pedia_category = 5;
    pedia_page_mode = 0;
    pedia_selected_item = *local_c;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef local_c
#undef local_8

/* 00453b10 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
PediaLinkCtorView * __thiscall pedia_link_ctor(PediaLinkCtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  hyperlink_ctor((Control *)(this->pad_0 + 4));
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00453cc0 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall hyperlink_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00453d40 auto */
void __thiscall hyperlink_set_click_callback(HyperlinkSetClickCallbackView *this,iptr param_1)

{
  this->on_click = param_1;
  return;
}

/* 00453d70 auto */
/* Library Function - Single Match
    public: void __thiscall CDialog::SetHelpID(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall hyperlink_set_dblclick_callback(HyperlinkSetDblclickCallbackView *this,iptr param_1)

{
  this->on_dblclick = param_1;
  return;
}

/* 00490590 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_terrain_list(MediaWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || (*(int *)(this[2].pad_15c + 0x38) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(i32 *)this[4].pad_2c4 = *(i32 *)(this[2].pad_15c + 0x38);
  *(u32 *)(this[5].pad_48 + 100) = this->resize_border;
  *(u32 *)(this[5].pad_48 + 0x68) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[5].pad_48 + 0x68) = *(int *)(this[5].pad_48 + 0x68) - 1;
  }
  for (local_8 = 0; local_8 < *(int *)(this[2].pad_15c + 0x38); local_8++) {
    *(i32 *)(this[4].pad_2c4 + local_8 * 4 + 4) =
         *(i32 *)(this[2].pad_200 + local_8 * 4 + 0x1c);
  }
  scrollbar_set_range
            ((Control *)&this[4].field_270,0,*(int *)this[4].pad_2c4 / 9);
  scrollbar_set_pos
            ((ClickControl *)&this[4].field_270,*(int *)(this[5].pad_48 + 0x68) / 9);
  if (*(int *)this[4].pad_2c4 < 1) {
    this[5].pad_48[0x68] = 0xff;
    this[5].pad_48[0x69] = 0xff;
    this[5].pad_48[0x6a] = 0xff;
    this[5].pad_48[0x6b] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 004906fd auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_2a0 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_290 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_280 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_270 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_260 (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define local_250 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define local_240 (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define local_230 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define local_220 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_210 (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define local_200 (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define local_1f0 (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define local_1e0 (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define local_1d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define local_1c0 (*(char (*)[256])(frame_ + FRAME_OFF(224)))
#define local_c0 (*(int *)(frame_ + FRAME_OFF(480)))
#define local_bc (*(i8 (*)[40])(frame_ + FRAME_OFF(484)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(524)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(528)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(532)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(536)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(540)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(544)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(548)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(552)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(556)))
#define terrain3 (*(iptr *)(frame_ + FRAME_OFF(560)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(564)))
#define local_68 (*(iptr *)(frame_ + FRAME_OFF(568)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(572)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(576)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(580)))
#define local_58 (*(u32 *)(frame_ + FRAME_OFF(584)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(588)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(592)))
#define local_4c (*(uint *)(frame_ + FRAME_OFF(596)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(600)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(604)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(608)))
#define local_3c (*(i32 *)(frame_ + FRAME_OFF(612)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(616)))
#define local_34 (*(tagRECT *)(frame_ + FRAME_OFF(620)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(636)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(640)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(644)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(648)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(664)))
void __thiscall pedia_draw_terrain_page(DocumentWindow *this)

{
  u8 uVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  char *_Format;
  int iVar5;
  i8 *puVar6;
  i8 frame_[FRAME_OFF(672)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)local_18);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  local_8 = (GameFont *)&font_size21;
  local_58 = this->content_left;
  local_44 = 10;
  local_54 = rect_width((iptr)&this->content_left);
  local_78 = local_54 / 2;
  local_1c = rect_height((iptr)&this->content_left);
  local_1c = local_1c / 0xc;
  local_80 = font_cached_height(local_8);
  local_5c = this->content_top + 8;
  terrain2 = *(iptr *)(this[1].pad_3c0 + this->resize_border * 4 + 0x6c);
  gfx_get_scale_ratio((iptr)&local_20,(iptr)&local_24);
  gfx_set_scale_ratio(local_20 * 2,local_24);
  local_64 = sprite_get_height((Sprite *)&terrain_base_sprites);
  local_48 = sprite_get_width((Sprite *)&terrain_base_sprites);
  local_58 += local_44;
  local_5c += (local_1c / 2 - local_64 / 2);
  terrain3 = terrain2 % 0xb;
  local_6c = local_48 * 2 + panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(&terrain_base_sprites + terrain3 * 0x3c),(iptr)local_1d0,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
             local_5c);
  if (terrain2 < 0xb) {
    if (terrain2 == 3) {
      sprite_draw
                ((Sprite *)&forest_sprites,(iptr)local_1e0,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
    }
    else if (terrain2 == 4) {
      sprite_draw
                ((Sprite *)&hill_sprites,(iptr)local_1f0,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
    }
    else if (terrain2 == 5) {
      sprite_draw
                ((Sprite *)&mountain_sprites,(iptr)local_200,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
    }
  }
  else {
    local_4c = (uint)(0x15 < terrain2);
    switch(terrain2) {
    case 0xd:
    case 0x18:
      sprite_draw
                ((Sprite *)&grassland_shield_sprite,(iptr)local_210,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
      goto LAB_00490a7d;
    case 0xe:
    case 0x19:
      sprite_draw
                ((Sprite *)&forest_sprites,(iptr)local_220,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
      break;
    case 0xf:
    case 0x1a:
      sprite_draw
                ((Sprite *)&hill_sprites,(iptr)local_230,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
      break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17: ;
    }
    sprite_draw
              ((Sprite *)(&terrain_resource_sprites + terrain3 * 0x78 + local_4c * 0x3c),(iptr)local_240,
               ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,local_5c);
  }
LAB_00490a7d:
  gfx_set_scale_ratio(local_20,local_24);
  local_3c = list_text_color;
  gfx_set_text_color_index(list_text_color);
  local_58 = this->content_left + local_44;
  local_40 = rect_width((iptr)&this->content_left);
  local_40 = local_40 / 2;
  local_50 = local_40 - 100;
  if ((terrain2 < 0) || (10 < terrain2)) {
    local_58 = local_58 + local_6c + 0x1e;
    local_5c += local_80;
    text_clear();
    text_append_label(0x295);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    iVar2 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_58 = local_58 + iVar2 + 10;
    text_clear();
    iVar3 = pedia_find_terrain_index(terrain3);
    uVar4 = pedia_lookup_text(pedia_terrain_names,iVar3);
    crt_strcpy(&text_buffer,uVar4);
    local_38 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_74 = font_line_spacing(local_8);
    SetRect(&local_34,local_58,local_5c,local_58 + local_38 + 5,local_5c + local_74);
    pedia_add_link(this,terrain3,local_58,local_5c,4,local_34.left,local_34.top,local_34.right,
                       local_34.bottom);
    local_5c += ((local_64 * 2 + 10) - local_80);
  }
  else {
    local_60 = local_5c + local_64 * 2 + 10;
    local_5c = local_60;
    text_clear();
    text_append_label(0x293);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    text_clear();
    _sprintf(&text_buffer,&pedia_terrain_move_cost_fmt,(int)(char)terrain_types[terrain2].move_cost);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
    local_58 = this->content_left + local_44;
    local_5c += local_80;
    text_clear();
    text_append_label(0x294);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    text_clear();
    if (terrain_types[terrain2].defense == 6) {
      crt_strcpy(&text_buffer,s__200__0062c948);
    }
    else if (terrain_types[terrain2].defense == 3) {
      crt_strcpy(&text_buffer,&pedia_terrain_defense_50_str);
    }
    else if (terrain_types[terrain2].defense == 4) {
      crt_strcpy(&text_buffer,s__100__0062c958);
    }
    else if (terrain_types[terrain2].defense == 5) {
      crt_strcpy(&text_buffer,s__150__0062c960);
    }
    else {
      iVar3 = label_string(*(i32 *)(label_string_ids + 0xb08));
      text_append(iVar3);
    }
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
  }
  local_58 = this->content_left + local_44;
  local_5c += local_80;
  text_clear();
  text_append_label(0x40);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_terrain_food_fmt,(int)(char)terrain_types[terrain2].food);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
  iVar2 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_58 = local_50 + iVar2 + 3;
  iVar5 = local_5c + local_1c / 2;
  iVar2 = sprite_get_height((Sprite *)&resource_icon_sprites);
  sprite_draw
            ((Sprite *)&resource_icon_sprites,(iptr)local_250,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
             (iVar5 - 2) - iVar2 / 2);
  local_58 = this->content_left + local_44;
  local_5c += local_80;
  text_clear();
  text_append_label(0x296);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
  text_clear();
  if (terrain2 == 2) {
    uVar1 = '\0';
  }
  else {
    uVar1 = terrain_types[terrain2].shields;
  }
  _sprintf(&text_buffer,&pedia_terrain_shields_fmt,(int)(char)uVar1);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
  iVar2 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_58 = local_50 + iVar2 + 3;
  iVar5 = local_5c + local_1c / 2;
  iVar2 = sprite_get_height((Sprite *)&shield_icon_sprite);
  sprite_draw
            ((Sprite *)&shield_icon_sprite,(iptr)local_260,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
             (iVar5 - 2) - iVar2 / 2);
  local_58 = this->content_left + local_44;
  local_5c += local_80;
  text_clear();
  text_append_label(0x45);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_terrain_trade_fmt,(int)(char)terrain_types[terrain2].trade);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
  iVar2 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_58 = local_50 + iVar2 + 3;
  iVar5 = local_5c + local_1c / 2;
  iVar2 = sprite_get_height((Sprite *)&trade_icon_sprite);
  sprite_draw
            ((Sprite *)&trade_icon_sprite,(iptr)local_270,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
             (iVar5 - 2) - iVar2 / 2);
  if ((terrain2 < 0) || (10 < terrain2)) {
    local_58 = this->content_left + local_44;
    local_5c += local_80 * 2;
    iVar3 = pedia_find_terrain_index(terrain3);
    uVar4 = pedia_lookup_text(pedia_terrain_names,iVar3);
    crt_strcpy(local_bc,uVar4);
    local_8c = (int)(char)terrain_types[terrain3].food;
    if (terrain3 == 2) {
      uVar1 = '\0';
    }
    else {
      uVar1 = terrain_types[terrain3].shields;
    }
    local_94 = (int)(char)uVar1;
    local_c0 = (int)(char)terrain_types[terrain3].trade;
    local_84 = (int)(char)terrain_types[terrain2].food;
    local_88 = (int)(char)terrain_types[terrain2].shields;
    local_90 = (int)(char)terrain_types[terrain2].trade;
    text_clear();
    if (local_8c < local_84) {
      puVar6 = local_bc;
      iVar2 = local_8c;
      iVar5 = local_84;
      _Format = (char *)label_string(*(i32 *)(label_string_ids + 0xb10));
      _sprintf(&text_buffer,_Format,puVar6,iVar2,iVar5);
    }
    else {
      uVar4 = label_string(*(i32 *)(label_string_ids + 0xb14));
      crt_strcpy(&text_buffer,uVar4);
    }
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    local_5c += local_80;
    text_clear();
    str_clear((iptr)local_1c0);
    if (local_94 < local_88) {
      uVar4 = label_string(*(i32 *)(label_string_ids + 0xb18));
      crt_strcpy(local_1c0,uVar4);
      _sprintf(&text_buffer,local_1c0,local_94,local_88);
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
      local_5c += local_80;
      text_clear();
      str_clear((iptr)local_1c0);
      if (local_c0 < local_90) {
        uVar4 = label_string(*(i32 *)(label_string_ids + 0xb1c));
        crt_strcat(local_1c0,uVar4);
        _sprintf(&text_buffer,local_1c0,local_c0,local_90);
      }
      else {
        uVar4 = label_string(*(i32 *)(label_string_ids + 0xb20));
        crt_strcat(&text_buffer,uVar4);
      }
    }
    else {
      uVar4 = label_string(*(i32 *)(label_string_ids + 0xb24));
      crt_strcpy(&text_buffer,uVar4);
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
      local_5c += local_80;
      text_clear();
      str_clear((iptr)local_1c0);
      if (local_c0 < local_90) {
        uVar4 = label_string(*(i32 *)(label_string_ids + 0xb1c));
        crt_strcat(local_1c0,uVar4);
        _sprintf(&text_buffer,local_1c0,local_c0,local_90);
      }
      else {
        uVar4 = label_string(*(i32 *)(label_string_ids + 0xb28));
        crt_strcat(&text_buffer,uVar4);
      }
    }
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
  }
  else {
    for (local_68 = 0; local_68 < 2; local_68++) {
      local_58 = this->content_left + local_44;
      local_5c += local_80;
      text_clear();
      if (local_68 == 0) {
        text_append_label(0x297);
      }
      else {
        text_append_label(0x299);
      }
      text_append_colon();
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
      text_clear();
      if (*(char *)(local_68 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18) < '\0') {
        if (*(char *)(local_68 + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18) < 1) {
          text_append_label(0x29b);
          surface_draw_text
                    ((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
        }
        else {
          _sprintf(&text_buffer,&pedia_terrain_improve_bonus_fmt,(int)*(char *)(local_68 + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18)
                  );
          surface_draw_text
                    ((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
          iVar2 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
          local_58 = local_50 + iVar2 + 3;
          if (local_68 == 0) {
            iVar5 = local_5c + local_1c / 2;
            iVar2 = sprite_get_height((Sprite *)&resource_icon_sprites);
            sprite_draw
                      ((Sprite *)&resource_icon_sprites,(iptr)local_280,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
                       (iVar5 - 2) - iVar2 / 2);
          }
          else {
            iVar5 = local_5c + local_1c / 2;
            iVar2 = sprite_get_height((Sprite *)&shield_icon_sprite);
            sprite_draw
                      ((Sprite *)&shield_icon_sprite,(iptr)local_290,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
                       (iVar5 - 2) - iVar2 / 2);
          }
        }
      }
      else {
        iVar3 = pedia_find_terrain_index((int)*(char *)(local_68 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18));
        uVar4 = pedia_lookup_text(pedia_terrain_names,iVar3);
        crt_strcpy(&text_buffer,uVar4);
        local_38 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_74 = font_line_spacing(local_8);
        SetRect(&local_34,local_50,local_5c,local_38 + local_50 + 5,local_5c + local_74);
        pedia_add_link(this,(int)*(char *)(local_68 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18),local_50,
                           local_5c,4,local_34.left,local_34.top,local_34.right,local_34.bottom);
      }
      local_58 = this->content_left + local_44;
      local_5c += local_80;
      text_clear();
      if (local_68 == 0) {
        text_append_label(0x298);
      }
      else {
        text_append_label(0x29a);
      }
      text_append_colon();
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
      text_clear();
      if (*(char *)(local_68 + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18) < 1) {
        text_append_label(0x29b);
      }
      else {
        _sprintf(&text_buffer,&pedia_terrain_improve_turns_fmt,(int)*(char *)(local_68 + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18));
      }
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_50,local_5c,5);
    }
    local_58 = local_40;
    text_clear();
    local_5c = local_60;
    text_append_label(0x29c);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    local_58 += 0x14;
    local_5c += local_80;
    text_clear();
    if (terrain_types[terrain2].transform_to < '\0') {
      text_append_label(0x29b);
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    }
    else {
      iVar3 = pedia_find_terrain_index((int)terrain_types[terrain2].transform_to);
      uVar4 = pedia_lookup_text(pedia_terrain_names,iVar3);
      crt_strcpy(&text_buffer,uVar4);
      local_38 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_74 = font_line_spacing(local_8);
      SetRect(&local_34,local_58,local_5c,local_58 + local_38 + 5,local_5c + local_74);
      pedia_add_link(this,(int)terrain_types[terrain2].transform_to,local_58,local_5c,4,
                         local_34.left,local_34.top,local_34.right,local_34.bottom);
    }
    if (terrain2 != 10) {
      local_58 = local_40;
      local_5c += local_80;
      text_clear();
      text_append_label(0x29d);
      text_append_colon();
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
      text_clear();
      local_58 += 0x14;
      local_5c += local_80;
      text_append_label(0x293);
      text_append_colon();
      text_append_space();
      iVar3 = label_string(*(i32 *)(label_string_ids + 0xb0c));
      text_append(iVar3);
      surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
      if (((terrain2 == 0) || (terrain2 == 2)) || (terrain2 == 1)) {
        local_5c += local_80;
        text_clear();
        text_append_label(0x45);
        text_append_colon();
        text_append(ADDR(0x62c980, ((u8 *)&g.d_0062c980)));
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
        iVar2 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_58 = local_58 + iVar2 + 3;
        iVar5 = local_5c + local_1c / 2;
        iVar2 = sprite_get_height((Sprite *)&trade_icon_sprite);
        sprite_draw
                  ((Sprite *)&trade_icon_sprite,(iptr)local_2a0,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_58,
                   (iVar5 - 2) - iVar2 / 2);
      }
    }
    local_58 = local_40;
    local_5c += local_80;
    text_clear();
    text_append_label(0x29e);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_58,local_5c,5);
    local_58 += 0x14;
    local_5c += local_80;
    text_clear();
    iVar3 = pedia_find_terrain_index(terrain2 + 0xb);
    uVar4 = pedia_lookup_text(pedia_terrain_names,iVar3);
    crt_strcpy(&text_buffer,uVar4);
    local_38 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_74 = font_line_spacing(local_8);
    SetRect(&local_34,local_58,local_5c,local_58 + local_38 + 5,local_5c + local_74);
    pedia_add_link(this,terrain2 + 0xb,local_58,local_5c,4,local_34.left,local_34.top,
                       local_34.right,local_34.bottom);
    if (terrain2 != 2) {
      text_clear();
      local_5c += local_80;
      iVar3 = pedia_find_terrain_index(terrain2 + 0x16);
      uVar4 = pedia_lookup_text(pedia_terrain_names,iVar3);
      crt_strcpy(&text_buffer,uVar4);
      local_38 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_74 = font_line_spacing(local_8);
      SetRect(&local_34,local_58,local_5c,local_58 + local_38 + 5,local_5c + local_74);
      pedia_add_link(this,terrain2 + 0x16,local_58,local_5c,4,local_34.left,local_34.top,
                         local_34.right,local_34.bottom);
    }
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)local_18);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef pedia_terrain_names
#undef text_buffer
#undef local_2a0
#undef local_290
#undef local_280
#undef local_270
#undef local_260
#undef local_250
#undef local_240
#undef local_230
#undef local_220
#undef local_210
#undef local_200
#undef local_1f0
#undef local_1e0
#undef local_1d0
#undef local_1c0
#undef local_c0
#undef local_bc
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef terrain2
#undef local_78
#undef local_74
#undef terrain3
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
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 00491c20 auto */
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_terrain_modal(DocumentWindow *this,int param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (pedia_closed != 0) {
    local_8 = 0;
    while (((int)local_8 < (int)this[1].field_3a4 &&
           (*(int *)(this[1].pad_3c0 + local_8 * 4 + 0x6c) != param_1))) {
      local_8++;
    }
    if (this[1].field_3a4 != local_8) {
      pedia_open_category((MediaWindow *)this,5,1);
      this->resize_border = local_8;
      *(uptr *)(this[3].pad_48 + 0x78) = local_8;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      uVar1 = pedia_lookup_text(pedia_terrain_names,local_8);
      crt_strcpy(this->pad_608 + 0x10,uVar1);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_terrain_page(this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef pedia_closed
#undef pedia_terrain_names
#undef local_8

/* 00491d61 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl pedia_find_terrain_index(iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while( true ) {
    if (pedia_terrain_count <= local_8) {
      return 0xffffffff;
    }
    if (*(int *)(&pedia_terrain_ids + local_8 * 4) == param_1) break;
    local_8++;
  }
  return local_8;
}
#undef local_8

/* 004a69b0 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_concept_list(MediaWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this[2].field_2a0 <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(uptr *)this[4].pad_2c4 = this[2].field_2a0;
  *(u32 *)(this[5].pad_48 + 100) = this->resize_border;
  *(u32 *)(this[5].pad_48 + 0x68) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[5].pad_48 + 0x68) = *(int *)(this[5].pad_48 + 0x68) - 1;
  }
  for (local_8 = 0; local_8 < (int)this[2].field_2a0; local_8++) {
    *(i32 *)(this[4].pad_2c4 + local_8 * 4 + 4) =
         *(i32 *)(this[3].pad_48 + local_8 * 4 + 0x40);
  }
  scrollbar_set_range
            ((Control *)&this[4].field_270,0,*(int *)this[4].pad_2c4 / 9);
  scrollbar_set_pos
            ((ClickControl *)&this[4].field_270,*(int *)(this[5].pad_48 + 0x68) / 9);
  if (*(int *)this[4].pad_2c4 < 1) {
    this[5].pad_48[0x68] = 0xff;
    this[5].pad_48[0x69] = 0xff;
    this[5].pad_48[0x6a] = 0xff;
    this[5].pad_48[0x6b] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 004f3f80 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl pedia_window_global_init(void)

{
  pedia_window_static_init();
  pedia_window_reg_atexit();
  return;
}

/* 004f3f9a auto */
void __cdecl pedia_window_static_init(void)

{
  pedia_window_ctor((ScaledWindowView *)&pedia_window);
  return;
}

/* 004f3fb4 auto */
void __cdecl pedia_window_reg_atexit(void)

{
  _atexit(pedia_window_static_dtor);
  return;
}

/* 004f3fd1 auto */
void __cdecl pedia_window_static_dtor(void)

{
  pedia_window_dtor((DibSurface *)&pedia_window);
  return;
}

/* 004f3feb auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
ScaledWindowView * __thiscall pedia_window_ctor(ScaledWindowView *this)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  button_ctor((Control *)(this[0x13].pad_48 + 0x88));
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  button_ctor((Control *)(this[0x13].pad_104 + 8));
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  button_ctor((Control *)&this[0x14].field_1c);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  button_ctor((Control *)(this[0x14].pad_48 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  button_ctor((Control *)(this[0x14].pad_48 + 0x4c));
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  button_ctor((Control *)(this[0x14].pad_48 + 0x88));
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  button_ctor((Control *)(this[0x14].pad_104 + 8));
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  button_ctor((Control *)&this[0x15].field_1c);
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  button_ctor((Control *)(this[0x15].pad_48 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  button_ctor((Control *)(this[0x15].pad_48 + 0x4c));
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  button_ctor((Control *)(this[0x15].pad_48 + 0x88));
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  button_ctor((Control *)(this[0x15].pad_104 + 8));
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  button_ctor((Control *)&this[0x16].field_1c);
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  button_ctor((Control *)(this[0x16].pad_48 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 0xe;
  button_ctor((Control *)(this[0x16].pad_48 + 0x4c));
  (*(i8 *)((char *)&local_8 + 0)) = 0xf;
  edit_ctor((InputControl *)(this[0x16].pad_48 + 0x88));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),0x10);
  scrollbar_ctor((Control *)&this[0x16].field_118);
  this->vtable = (u32)&PTR_FUN_0061d6d0;
  this->style_flags = 1;
  this->border_width = 0;
  this->resize_border = 0;
  this->client_x = 0;
  this[0x13].pad_48[0x84] = '\0';
  this[0x13].pad_48[0x85] = '\0';
  this[0x13].pad_48[0x86] = '\0';
  this[0x13].pad_48[0x87] = '\0';
  this[0x1a].pad_48[0x80] = '\0';
  this[0x1a].pad_48[0x81] = '\0';
  this[0x1a].pad_48[0x82] = '\0';
  this[0x1a].pad_48[0x83] = '\0';
  this->caption_height = 0;
  for (local_14 = 0; local_14 < 100; local_14++) {
    puVar1 = this[5].pad_48 + local_14 * 4 + 0x38;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_14 = 0; local_14 < 0x27; local_14++) {
    puVar1 = this[8].pad_48 + local_14 * 4 - 0x28;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_14 = 0; local_14 < 0x1c; local_14++) {
    puVar1 = this[9].pad_48 + local_14 * 4 - 0x18;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_14 = 0; local_14 < 0x3e; local_14++) {
    puVar1 = this[9].pad_104 + local_14 * 4 + 0x10;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_14 = 0; local_14 < 7; local_14++) {
    puVar1 = this[0xb].pad_48 + local_14 * 4 + 0x68;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_14 = 0; local_14 < 0x21; local_14++) {
    puVar1 = this[0xb].pad_48 + local_14 * 4 + 0xa4;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_14 = 0; local_14 < 0x100; local_14++) {
    puVar1 = this[0xc].pad_48 + local_14 * 4 + 0x84;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  this[0x13].pad_48[0x50] = '\0';
  this[0x13].pad_48[0x51] = '\0';
  this[0x13].pad_48[0x52] = '\0';
  this[0x13].pad_48[0x53] = '\0';
  this[0x13].pad_48[0x54] = '\0';
  this[0x13].pad_48[0x55] = '\0';
  this[0x13].pad_48[0x56] = '\0';
  this[0x13].pad_48[0x57] = '\0';
  this[0x13].pad_48[0x58] = '\0';
  this[0x13].pad_48[0x59] = '\0';
  this[0x13].pad_48[0x5a] = '\0';
  this[0x13].pad_48[0x5b] = '\0';
  this[0x13].pad_48[0x5c] = '\0';
  this[0x13].pad_48[0x5d] = '\0';
  this[0x13].pad_48[0x5e] = '\0';
  this[0x13].pad_48[0x5f] = '\0';
  this[0x13].pad_48[0x60] = '\0';
  this[0x13].pad_48[0x61] = '\0';
  this[0x13].pad_48[0x62] = '\0';
  this[0x13].pad_48[99] = '\0';
  this[0x13].pad_48[100] = '\0';
  this[0x13].pad_48[0x65] = '\0';
  this[0x13].pad_48[0x66] = '\0';
  this[0x13].pad_48[0x67] = '\0';
  this[0x13].pad_48[0x68] = '\0';
  this[0x13].pad_48[0x69] = '\0';
  this[0x13].pad_48[0x6a] = '\0';
  this[0x13].pad_48[0x6b] = '\0';
  this[0x17].field_2c = 0;
  this->client_y = 0;
  return this;
}
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 004f44a7 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall pedia_window_dtor(DibSurface *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6d0;
  local_8 = 0x11;
  pedia_free_lists((WindowObjectView *)this);
  pedia_clear_links((WindowObjectView *)this);
  if (this[0x52].field_0 != 0) {
    if ((Hotspot *)this[0x52].field_0 != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)this[0x52].field_0,1);
    }
    this[0x52].field_0 = 0;
  }
  if (this[0x60].field_20 != 0) {
    if ((Hotspot *)this[0x60].field_20 != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)this[0x60].field_20,1);
    }
    this[0x60].field_20 = 0;
  }
  wnd_destroy_with_surface(this);
  (*(i8 *)((char *)&local_8 + 0)) = 0x10;
  /* inlined unwind funclet 004f4673 */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x1ae0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xf;
  /* inlined unwind funclet 004f4682 */ { edit_dtor((Control *)(*(int *)((iptr)&this) + 0x1a98)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xe;
  /* inlined unwind funclet 004f4691 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1a5c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  /* inlined unwind funclet 004f46a0 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1a20)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  /* inlined unwind funclet 004f46af */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x19e4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  /* inlined unwind funclet 004f46be */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x19a8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  /* inlined unwind funclet 004f46cd */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x196c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  /* inlined unwind funclet 004f46dc */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1930)); }
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  /* inlined unwind funclet 004f46eb */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x18f4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  /* inlined unwind funclet 004f46fa */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x18b8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet 004f4709 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x187c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet 004f4718 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1840)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 004f4727 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1804)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 004f4736 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x17c8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 004f4745 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x178c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 004f4754 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1750)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 004f4763 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1714)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004f4772 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004f4793 auto */
void __thiscall pedia_clear_links(WindowObjectView *this)

{
  u32 uVar1;
  
  while (this[2000].field_0 != 0) {
    uVar1 = *(u32 *)(this[2000].field_0 + 0x44);
    if ((void *)this[2000].field_0 != (void *)0x0) {
      pedia_link_scalar_dtor((void *)this[2000].field_0,1);
    }
    this[2000].field_0 = uVar1;
  }
  wnd_flush_paint();
  return;
}

/* 004f4809 auto */
void __thiscall pedia_free_lists(WindowObjectView *this)

{
  u32 uVar1;
  
  while (this[0x5b7].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5b7].field_0 + 8);
    if (*(int *)this[0x5b7].field_0 != 0) {
      operator_delete(*(void **)this[0x5b7].field_0);
    }
    operator_delete((void *)this[0x5b7].field_0);
    this[0x5b7].field_0 = uVar1;
  }
  while (this[0x5b8].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5b8].field_0 + 8);
    if (*(int *)this[0x5b8].field_0 != 0) {
      operator_delete(*(void **)this[0x5b8].field_0);
    }
    operator_delete((void *)this[0x5b8].field_0);
    this[0x5b8].field_0 = uVar1;
  }
  while (this[0x5b9].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5b9].field_0 + 8);
    if (*(int *)this[0x5b9].field_0 != 0) {
      operator_delete(*(void **)this[0x5b9].field_0);
    }
    operator_delete((void *)this[0x5b9].field_0);
    this[0x5b9].field_0 = uVar1;
  }
  while (this[0x5ba].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5ba].field_0 + 8);
    if (*(int *)this[0x5ba].field_0 != 0) {
      operator_delete(*(void **)this[0x5ba].field_0);
    }
    operator_delete((void *)this[0x5ba].field_0);
    this[0x5ba].field_0 = uVar1;
  }
  while (this[0x5bb].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5bb].field_0 + 8);
    if (*(int *)this[0x5bb].field_0 != 0) {
      operator_delete(*(void **)this[0x5bb].field_0);
    }
    operator_delete((void *)this[0x5bb].field_0);
    this[0x5bb].field_0 = uVar1;
  }
  while (this[0x5bc].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5bc].field_0 + 8);
    if (*(int *)this[0x5bc].field_0 != 0) {
      operator_delete(*(void **)this[0x5bc].field_0);
    }
    operator_delete((void *)this[0x5bc].field_0);
    this[0x5bc].field_0 = uVar1;
  }
  while (this[0x5bd].field_0 != 0) {
    uVar1 = *(u32 *)(this[0x5bd].field_0 + 8);
    if (*(int *)this[0x5bd].field_0 != 0) {
      operator_delete(*(void **)this[0x5bd].field_0);
    }
    operator_delete((void *)this[0x5bd].field_0);
    this[0x5bd].field_0 = uVar1;
  }
  return;
}

/* 004f4b9f auto */
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_8c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_88 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_84 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_80 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_7c (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_78 (*(u8 * *)(frame_ + FRAME_OFF(24)))
#define local_74 (*(u8 * *)(frame_ + FRAME_OFF(28)))
#define local_70 (*(u8 * *)(frame_ + FRAME_OFF(32)))
#define local_6c (*(u8 * *)(frame_ + FRAME_OFF(36)))
#define local_68 (*(u8 * *)(frame_ + FRAME_OFF(40)))
#define local_64 (*(u8 * *)(frame_ + FRAME_OFF(44)))
#define local_60 (*(u8 * *)(frame_ + FRAME_OFF(48)))
#define local_5c (*(u8 * *)(frame_ + FRAME_OFF(52)))
#define local_58 (*(u8 * *)(frame_ + FRAME_OFF(56)))
#define local_54 (*(u8 * *)(frame_ + FRAME_OFF(60)))
#define local_50 (*(u8 * *)(frame_ + FRAME_OFF(64)))
#define local_4c (*(u8 * *)(frame_ + FRAME_OFF(68)))
#define local_48 (*(u8 * *)(frame_ + FRAME_OFF(72)))
#define local_44 (*(u32 *)(frame_ + FRAME_OFF(76)))
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(108)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(128)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(132)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(136)))
void __thiscall pedia_window_create(DocumentWindow *this)

{
  int iVar1;
  int iVar2;
  u32 uVar3;
  Control *this_00;
  int iVar4;
  iptr iVar5;
  int yTop;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  pedia_free_lists((WindowObjectView *)this);
  pedia_clear_links((WindowObjectView *)this);
  this->client_y = 0;
  if (this[2].field_2c0 != 0) {
    if ((Hotspot *)this[2].field_2c0 != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)this[2].field_2c0,1);
    }
    this[2].field_2c0 = 0;
  }
  this->panel_width = 0x280;
  this->panel_height = 400;
  iVar1 = font_cached_height((GameFont *)&font_size30);
  this->field_5e4 = iVar1 + panel_bevel_width * 2 + panel_margin_y * 2;
  SetRect((LPRECT)this->pad_5e8,0,0,this->panel_width,this->panel_height);
  uVar3 = this->panel_height;
  iVar1 = this->field_5e4 + panel_margin_y;
  iVar2 = font_line_spacing((GameFont *)&font_size24);
  SetRect((LPRECT)&this->content_left,0,0,this->panel_width + (panel_padding_x + panel_margin_x) * -2,
          (uVar3 - iVar1) + ((panel_margin_y * -3 + panel_padding_y * -2) - iVar2) + panel_bevel_width * -2);
  OffsetRect((LPRECT)&this->content_left,panel_padding_x + panel_margin_x,this->field_5e4 + panel_margin_y);
  iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
  iVar2 = wnd_client_height((WndBase *)&main_frame_wnd);
  crt_strcpy(this->pad_608 + 0x10,&pedia_window_empty_title_str);
  wnd_create_with_surface
            ((DibSurface *)this,0,0xe02,iVar1 / 2 - (int)this->panel_width / 2,
             iVar2 / 2 - (int)this->panel_height / 2,this->panel_width,this->panel_height,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)))
  ;
  wnd_set_close_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x401dcf, pedia_close));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x40272a, pedia_redraw_page));
  wnd_set_caption_height((WndBase *)this->pad_48,this->field_5e4);
  wnd_set_keydown_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x4026bc, pedia_list_on_key));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  iVar1 = panel_padding_x;
  this[2].field_2bc = (u32)&caption_close_button_sprite;
  this[2].field_2a8 = 1;
  uVar3 = sprite_width((Sprite *)this[2].field_2bc);
  this[2].field_2b4 = uVar3;
  uVar3 = sprite_height((Sprite *)this[2].field_2bc);
  this[2].field_2b8 = uVar3;
  local_14 = (int)(this[2].field_2b8 * this->field_5e4) / 0x18;
  iVar2 = ((int)this->field_5e4 >> 1) - (local_14 >> 1);
  SetRect(&local_24,iVar1,iVar2,(int)(this[2].field_2b4 * this->field_5e4) / 0x18 + iVar1,
          local_14 + iVar2);
  this_00 = operator_new(0x40);
  local_8 = 0;
  if (this_00 == (Control *)0x0) {
    local_44 = 0;
  }
  else {
    local_44 = hotspot_ctor(this_00);
  }
  local_8 = 0xffffffff;
  this[2].field_2c0 = local_44;
  if (this == (DocumentWindow *)0x0) {
    local_48 = (u8 *)0x0;
  }
  else {
    local_48 = this->pad_48;
  }
  hotspot_create
            ((ClickControl *)this[2].field_2c0,(iptr)local_48,4000,(iptr)&local_24);
  hotspot_set_click_callback((HotspotClickSetView *)this[2].field_2c0,ADDR(0x4037fb, pedia_on_close));
  iVar1 = panel_bevel_width + panel_margin_x + 2;
  uVar3 = this->panel_height;
  iVar2 = font_line_spacing((GameFont *)&font_size24);
  yTop = uVar3 - (iVar2 + (panel_margin_y + panel_padding_y) * 2);
  iVar4 = this->panel_width - (panel_margin_x * 2 + panel_bevel_width * 2 + 5);
  local_14 = font_line_spacing((GameFont *)&font_size24);
  local_14 += panel_padding_y * 2;
  iVar2 = iVar4 / 2;
  SetRect(&local_24,iVar1,yTop,iVar2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_4c = (u8 *)0x0;
  }
  else {
    local_4c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x9c));
  button_create
            ((Control *)this[2].pad_2c4,(iptr)local_4c,0xfa1,(iptr)&local_24,iVar5);
  button_set_callback((Control *)this[2].pad_2c4,ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&local_24,iVar2 + iVar1,yTop,iVar2 * 2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_50 = (u8 *)0x0;
  }
  else {
    local_50 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&this[2].field_300,(iptr)local_50,0xfa2,(iptr)&local_24,iVar5);
  ctrl_set_default_button((Control *)&this[2].field_300);
  ctrl_set_cancel_button((Control *)&this[2].field_300);
  button_set_callback((Control *)&this[2].field_300,ADDR(0x4037fb, pedia_on_close));
  SetRect(&local_24,iVar1,yTop,iVar4 / 2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_54 = (u8 *)0x0;
  }
  else {
    local_54 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)(this[2].pad_464 + 4),(iptr)local_54,0xfb2,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_464 + 4),ADDR(0x4018ed, pedia_on_back));
  iVar2 = iVar4 / 3;
  SetRect(&local_24,iVar1,yTop,iVar2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_58 = (u8 *)0x0;
  }
  else {
    local_58 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x9c));
  button_create
            ((Control *)this[2].pad_4a4,(iptr)local_58,0xfab,(iptr)&local_24,iVar5);
  button_set_callback((Control *)this[2].pad_4a4,ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&local_24,iVar2 + iVar1,yTop,iVar2 * 2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_5c = (u8 *)0x0;
  }
  else {
    local_5c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xd80));
  button_create
            ((Control *)(this[2].pad_4a4 + 0x3c),(iptr)local_5c,0xfac,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_4a4 + 0x3c),ADDR(0x401ec4, pedia_show_tech_tree));
  SetRect(&local_24,iVar2 * 2 + iVar1,yTop,iVar2 * 3 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_60 = (u8 *)0x0;
  }
  else {
    local_60 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)(this[2].pad_4a4 + 0x78),(iptr)local_60,0xfad,(iptr)&local_24,iVar5);
  ctrl_set_default_button((Control *)(this[2].pad_4a4 + 0x78));
  ctrl_set_cancel_button((Control *)(this[2].pad_4a4 + 0x78));
  button_set_callback((Control *)(this[2].pad_4a4 + 0x78),ADDR(0x4037fb, pedia_on_close));
  iVar2 = (int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2;
  SetRect(&local_24,iVar1,yTop,iVar2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_64 = (u8 *)0x0;
  }
  else {
    local_64 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)(this[2].pad_4a4 + 0xb4),(iptr)local_64,0xfae,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_4a4 + 0xb4),ADDR(0x4018ed, pedia_on_back));
  SetRect(&local_24,iVar2 + iVar1,yTop,iVar2 * 2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_68 = (u8 *)0x0;
  }
  else {
    local_68 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xd80));
  button_create
            ((Control *)(this[2].pad_4a4 + 0xf0),(iptr)local_68,0xfaf,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_4a4 + 0xf0),ADDR(0x401ec4, pedia_show_tech_tree));
  SetRect(&local_24,iVar2 * 2 + iVar1,yTop,iVar2 * 3 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_6c = (u8 *)0x0;
  }
  else {
    local_6c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xb04));
  button_create
            ((Control *)(this[2].pad_5c0 + 0x10),(iptr)local_6c,0xfb0,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_5c0 + 0x10),ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&local_24,iVar2 * 3 + iVar1,yTop,iVar2 * 4 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_70 = (u8 *)0x0;
  }
  else {
    local_70 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)(this[2].pad_608 + 4),(iptr)local_70,0xfb1,(iptr)&local_24,iVar5);
  ctrl_set_default_button((Control *)(this[2].pad_608 + 4));
  ctrl_set_cancel_button((Control *)(this[2].pad_608 + 4));
  button_set_callback((Control *)(this[2].pad_608 + 4),ADDR(0x4037fb, pedia_on_close));
  iVar2 = iVar4 / 3;
  SetRect(&local_24,iVar1,yTop,iVar2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_74 = (u8 *)0x0;
  }
  else {
    local_74 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)&this[2].field_33c,(iptr)local_74,0xfa3,(iptr)&local_24,iVar5);
  button_set_callback((Control *)&this[2].field_33c,ADDR(0x4018ed, pedia_on_back));
  SetRect(&local_24,iVar2 + iVar1,yTop,iVar2 * 2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_78 = (u8 *)0x0;
  }
  else {
    local_78 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xb04));
  button_create
            ((Control *)(this[2].pad_364 + 0x14),(iptr)local_78,0xfa4,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_364 + 0x14),ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&local_24,iVar2 * 2 + iVar1,yTop,iVar2 * 3 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_7c = (u8 *)0x0;
  }
  else {
    local_7c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&this[2].field_3b4,(iptr)local_7c,0xfa5,(iptr)&local_24,iVar5);
  button_set_callback((Control *)&this[2].field_3b4,ADDR(0x4037fb, pedia_on_close));
  iVar4 = iVar4 / 2;
  SetRect(&local_24,iVar1,yTop,iVar4 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_80 = (u8 *)0x0;
  }
  else {
    local_80 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)(this[2].pad_3c0 + 0x30),(iptr)local_80,0xfa6,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_3c0 + 0x30),ADDR(0x4018ed, pedia_on_back));
  SetRect(&local_24,iVar4 + iVar1,yTop,iVar4 * 2 + iVar1,local_14 + yTop);
  if (this == (DocumentWindow *)0x0) {
    local_84 = (u8 *)0x0;
  }
  else {
    local_84 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)(this[2].pad_3c0 + 0x6c),(iptr)local_84,0xfa7,(iptr)&local_24,iVar5);
  button_set_callback((Control *)(this[2].pad_3c0 + 0x6c),ADDR(0x4037fb, pedia_on_close));
  ui_set_button_font(ADDR(0x68abe0, ((u8 *)&g.d_0068abe0)));
  pedia_clear_links((WindowObjectView *)this);
  ui_set_default_font(ADDR(0x67a798, ((u8 *)&g.d_0067a798)));
  if (this == (DocumentWindow *)0x0) {
    local_88 = (u8 *)0x0;
  }
  else {
    local_88 = this->pad_48;
  }
  edit_create_styled
            ((EditControl *)(this[2].pad_608 + 0x40),(iptr)local_88,0xfaa,(iptr)&this->content_left,
             ADDR(0x62f01c, ((u8 *)&g.d_0062f01c)),0x122,0);
  local_24.left = this->content_left;
  local_24.top = this->content_top;
  local_24.right = this->content_right;
  uVar3 = this->content_bottom;
  local_24.bottom = uVar3;
  iVar1 = GetSystemMetrics(3);
  local_24.top = uVar3 - iVar1;
  if (this == (DocumentWindow *)0x0) {
    local_8c = (u8 *)0x0;
  }
  else {
    local_8c = this->pad_48;
  }
  scrollbar_create
            ((Control *)(this[2].pad_65c + 0x34),(iptr)local_8c,0xfa8,(iptr)&local_24,0);
  scrollbar_set_callback((Control *)(this[2].pad_65c + 0x34),ADDR(0x403c51, pedia_list_on_scroll));
  scrollbar_set_track_callback((ScrollbarTrackSetView *)(this[2].pad_65c + 0x34),ADDR(0x403c51, pedia_list_on_scroll));
  scrollbar_set_page_size((Control *)(this[2].pad_65c + 0x34),2);
  pedia_load_indexes(this);
  return;
}
#undef panel_margin_x
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
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
#undef local_24
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 004f5b24 auto */
#define pedia_history_count (*(i32 *)((u8 *)&g.d_006a6790))
void __cdecl pedia_on_close(void)

{
  if (pedia_modal_active == 1) {
    wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
    pedia_modal_active = 0;
  }
  pedia_clear_links((WindowObjectView *)&pedia_window);
  pedia_history_count = 0;
  pedia_close();
  return;
}
#undef pedia_history_count

/* 004f5b6f auto */
#define pedia_back_topic (*(i32 *)((u8 *)&g.d_0062f010))
#define pedia_category (*(int *)((u8 *)&g.d_006a6780))
#define pedia_going_back (*(i32 *)((u8 *)&g.d_0062f00c))
#define pedia_history_count (*(int *)((u8 *)&g.d_006a6790))
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(int *)((u8 *)&g.d_006a6788))
void __cdecl pedia_on_back(void)

{
  if (pedia_history_count != 0) {
    do {
      pedia_history_count--;
      if (((pedia_history_count == 0) || (*(int *)(&pedia_history_categories + pedia_history_count * 4) != pedia_category)) ||
         (*(int *)(&pedia_history_page_modes + pedia_history_count * 4) != pedia_page_mode)) break;
    } while (*(int *)(&pedia_history_topics + pedia_history_count * 4) == pedia_topic);
    if (pedia_history_count != 0) {
      pedia_going_back = 1;
      pedia_back_topic = *(i32 *)(&pedia_history_topics + pedia_history_count * 4);
      pedia_popped_page_mode = *(i32 *)(&pedia_history_page_modes + pedia_history_count * 4);
      pedia_popped_category = *(i32 *)(&pedia_history_categories + pedia_history_count * 4);
    }
    if (*(int *)(&pedia_history_page_modes + pedia_history_count * 4) != 0) {
      pedia_category = *(int *)(&pedia_history_categories + pedia_history_count * 4);
      pedia_page_mode = *(int *)(&pedia_history_page_modes + pedia_history_count * 4) - 1;
      pedia_topic = *(int *)(&pedia_history_topics + pedia_history_count * 4);
      pedia_selected_item = pedia_topic;
      pedia_toggle_describe(1);
      return;
    }
    pedia_category = *(int *)(&pedia_history_categories + pedia_history_count * 4);
    pedia_page_mode = 1;
    pedia_topic = *(int *)(&pedia_history_topics + pedia_history_count * 4);
    pedia_selected_item = pedia_topic;
  }
  if (pedia_page_mode == 0) {
    if (pedia_modal_active == 1) {
      wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      pedia_modal_active = 0;
    }
    pedia_close();
  }
  else {
    if (pedia_page_mode == 1) {
      pedia_page_mode = 0;
      pedia_update_controls((MediaWindow *)&pedia_window);
      pedia_redraw_page();
      pedia_selected_item = pedia_topic;
      pedia_redraw((PediaRedrawView *)&pedia_window);
    }
    else if ((pedia_category == 6) || (pedia_category == 7)) {
      pedia_page_mode = 0;
      pedia_update_controls((MediaWindow *)&pedia_window);
      pedia_redraw_page();
      pedia_selected_item = pedia_topic;
      pedia_redraw((PediaRedrawView *)&pedia_window);
    }
    else {
      pedia_page_mode = 0;
      pedia_toggle_describe(1);
    }
    pedia_history_push((ScaledWindowView *)&pedia_window);
  }
  return;
}
#undef pedia_back_topic
#undef pedia_category
#undef pedia_going_back
#undef pedia_history_count
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic

/* 004f5dd1 auto */
#define pedia_closed (*(i32 *)((u8 *)&g.d_006a677c))
#define pedia_history_count (*(i32 *)((u8 *)&g.d_006a6790))
i32 __cdecl pedia_close(void)

{
  pedia_closed = 1;
  pedia_history_count = 0;
  if (pedia_close_hotspot != (Hotspot *)0x0) {
    if (pedia_close_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor(pedia_close_hotspot,1);
    }
    pedia_close_hotspot = (Hotspot *)0x0;
  }
  wnd_hide((WndBase *)&pedia_window_wnd);
  wnd_focus_and_raise((WndBase *)&main_frame_wnd);
  ui_flush_input();
  return 0;
}
#undef pedia_closed
#undef pedia_history_count

/* 004f5e52 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
void __cdecl pedia_redraw_page(void)

{
  if (pedia_closed == 0) {
    if (pedia_page_mode == 0) {
      pedia_set_category_title((WindowObjectView *)&pedia_window,pedia_category);
    }
    pedia_clear_links((WindowObjectView *)&pedia_window);
    gfx_set_draw_target(ADDR(0x6a6668, ((u8 *)&g.d_006a6668)));
    pedia_draw_frame((MediaWindow *)&pedia_window);
    pedia_draw_category_body((DocumentWindow *)&pedia_window,pedia_category,pedia_page_mode);
    wnd_blit_surface((DibSurface *)&pedia_window);
  }
  return;
}
#undef pedia_category
#undef pedia_closed
#undef pedia_page_mode

/* 004f5ed2 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(i32 *)((u8 *)&g.d_006a6788))
void __cdecl pedia_show_tech_tree(void)

{
  pedia_page_mode = 0;
  pedia_category = 8;
  pedia_update_controls((MediaWindow *)&pedia_window);
  pedia_redraw_page();
  pedia_selected_item = pedia_topic;
  pedia_redraw((PediaRedrawView *)&pedia_window);
  pedia_history_push((ScaledWindowView *)&pedia_window);
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic

/* 004f5f23 auto */
#define pedia_advance_names (*(i32 *)((u8 *)&g.d_006a7d44))
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_concept_names (*(i32 *)((u8 *)&g.d_006a7d5c))
#define pedia_government_names (*(i32 *)((u8 *)&g.d_006a7d54))
#define pedia_improvement_names (*(i32 *)((u8 *)&g.d_006a7d48))
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(uptr *)((u8 *)&g.d_006a85a0))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define pedia_topic (*(uptr *)((u8 *)&g.d_006a6788))
#define pedia_unit_names (*(i32 *)((u8 *)&g.d_006a7d50))
#define pedia_wonder_names (*(i32 *)((u8 *)&g.d_006a7d4c))
void __cdecl pedia_toggle_describe(i32 param_1)

{
  i32 uVar2;
  uptr uVar1;
  
  uVar1 = pedia_selected_item;
  if (pedia_page_mode == 0) {
    pedia_topic = pedia_selected_item;
    pedia_page_mode = 1;
    pedia_clear_links((WindowObjectView *)&pedia_window);
    pedia_update_controls((MediaWindow *)&pedia_window);
    switch(pedia_category) {
    case 1:
    case 8:
      uVar2 = pedia_lookup_text(pedia_advance_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_advance_page((DocumentWindow *)&pedia_window);
      break;
    case 2:
      uVar2 = pedia_lookup_text(pedia_improvement_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_improvement_page((DocumentWindow *)&pedia_window);
      break;
    case 3:
      uVar2 = pedia_lookup_text(pedia_wonder_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_improvement((DocumentWindow *)&pedia_window);
      break;
    case 4:
      uVar2 = pedia_lookup_text(pedia_unit_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_unit_page((DocumentWindow *)&pedia_window);
      break;
    case 5:
      uVar2 = pedia_lookup_text(pedia_terrain_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_terrain_page((DocumentWindow *)&pedia_window);
      break;
    case 6:
      pedia_page_mode = 2;
      uVar2 = pedia_lookup_text(pedia_government_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_fill_background((WindowObjectView *)&pedia_window,ADDR(0x6a6c60, ((u8 *)&g.d_006a6c60)),1);
      pedia_load_description((WindowObjectView *)&pedia_window,uVar1);
      break;
    case 7:
      pedia_page_mode = 2;
      uVar2 = pedia_lookup_text(pedia_concept_names,uVar1);
      crt_strcpy(&pedia_title_text,uVar2);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_fill_background((WindowObjectView *)&pedia_window,ADDR(0x6a6c60, ((u8 *)&g.d_006a6c60)),1);
      pedia_load_description((WindowObjectView *)&pedia_window,uVar1);
      break;
    default:
      text_append(ADDR(0x62f020, ((u8 *)&g.d_0062f020)));
    }
    wnd_blit_surface((DibSurface *)&pedia_window);
  }
  else if (pedia_page_mode == 1) {
    pedia_page_mode = 2;
    pedia_clear_links((WindowObjectView *)&pedia_window);
    pedia_update_controls((MediaWindow *)&pedia_window);
    pedia_draw_frame((MediaWindow *)&pedia_window);
    pedia_fill_background((WindowObjectView *)&pedia_window,ADDR(0x6a6c60, ((u8 *)&g.d_006a6c60)),0);
    pedia_load_description((WindowObjectView *)&pedia_window,uVar1);
  }
  pedia_history_push((ScaledWindowView *)&pedia_window);
  return;
}
#undef pedia_advance_names
#undef pedia_category
#undef pedia_concept_names
#undef pedia_government_names
#undef pedia_improvement_names
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_terrain_names
#undef pedia_topic
#undef pedia_unit_names
#undef pedia_wonder_names

/* 004f6244 auto */
#define dlg_bevel_dark_color (*(byte *)((u8 *)&g.d_00635a0c))
#define dlg_bevel_light_color (*(byte *)((u8 *)&g.d_00635a08))
#define panel_margin_x (*(i32 *)((u8 *)&g.d_0062d858))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(i8 * *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(36)))
void __thiscall pedia_draw_frame(MediaWindow *this)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_reset_clip((DibSurface *)this);
  crt_memcpy(&local_14,this->pad_5e8,0x10);
  for (local_18 = 0; local_18 < panel_bevel_width; local_18++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,(uint)dlg_bevel_light_color,(uint)dlg_bevel_dark_color);
    rect_deflate((iptr)&local_14,1,1);
  }
  pedia_fill_background((WindowObjectView *)this,(iptr)&local_14,1);
  rect_deflate((iptr)&local_14,panel_padding_x + panel_bevel_width * -2,0);
  local_14.top = local_14.top + this->field_5e4 + panel_bevel_width * -2;
  iVar1 = rect_height((iptr)this->pad_5e8);
  iVar2 = font_line_spacing((GameFont *)&font_size24);
  local_14.bottom = iVar1 + ((panel_margin_y * -3 + panel_padding_y * -2) - iVar2);
  for (local_18 = 0; local_18 < panel_bevel_width; local_18++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,(uint)dlg_bevel_dark_color,(uint)dlg_bevel_light_color);
    rect_deflate((iptr)&local_14,1,1);
  }
  pedia_fill_background((WindowObjectView *)this,(iptr)&local_14,2);
  iVar1 = panel_padding_x;
  local_20 = panel_padding_x;
  this->panel_width = (int)(*(int *)(this[3].pad_4a4 + 0xc) * this->field_5e4) / 0x18;
  this->panel_height = (int)(*(int *)(this[3].pad_4a4 + 0x10) * this->field_5e4) / 0x18;
  local_24 = ((int)this->field_5e4 >> 1) - ((int)this->panel_height >> 1);
  SetRect(&local_14,iVar1,local_24,this->panel_width + iVar1,this->panel_height + local_24);
  gfx_set_scale_ratio(this->field_5e4,0x18);
  sprite_draw
            (*(Sprite **)(this[3].pad_4a4 + 0x14),(iptr)local_34,(iptr)this,local_20,local_24
            );
  gfx_reset_zoom_scale();
  local_20 += this->panel_width;
  local_1c = &font_size30;
  iVar1 = (this->frame_rect_right - local_20) - panel_padding_x;
  iVar2 = font_text_width
                    ((GameFont *)&font_size30,(iptr)(this->pad_608 + 0x10));
  local_20 += (iVar1 / 2 - (iVar2 >> 1));
  local_24 = panel_bevel_width + panel_margin_y;
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_1c,(iptr)(this->pad_608 + 0x10),local_20 + 2,
             local_24 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_1c,(iptr)(this->pad_608 + 0x10),local_20 + 1,local_24
             ,5);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_1c,(iptr)(this->pad_608 + 0x10),local_20,local_24,5);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef dlg_bevel_dark_color
#undef dlg_bevel_light_color
#undef panel_margin_x
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 004f6564 auto */
#define dlg_bg_color (*(byte *)((u8 *)&g.d_00635a04))
#define dlg_client_tile_surface (*(int *)((u8 *)&g.d_00635aa4))
#define dlg_frame_tile_surface (*(int *)((u8 *)&g.d_00635aa0))
void __thiscall pedia_fill_background(WindowObjectView *this,iptr param_1,int param_2)

{
  i32 uVar1;
  i32 uVar2;
  i32 uVar3;
  i32 uVar4;
  
  if ((dlg_frame_tile_surface == 0) || (param_2 != 1)) {
    if ((dlg_client_tile_surface == 0) || (param_2 != 2)) {
      gfx_fill_rect((iptr)this,param_1,(uint)dlg_bg_color);
    }
    else {
      uVar4 = 0;
      uVar3 = 0;
      uVar1 = rect_height(param_1);
      uVar2 = rect_width(param_1);
      gfx_tile_fill((iptr)this,dlg_client_tile_surface,*(i32 *)param_1,*(i32 *)(param_1 + 4)
                         ,uVar2,uVar1,uVar3,uVar4);
    }
  }
  else {
    uVar4 = 0;
    uVar3 = 0;
    uVar1 = rect_height(param_1);
    uVar2 = rect_width(param_1);
    gfx_tile_fill((iptr)this,dlg_frame_tile_surface,*(i32 *)param_1,*(i32 *)(param_1 + 4),
                       uVar2,uVar1,uVar3,uVar4);
  }
  return;
}
#undef dlg_bg_color
#undef dlg_client_tile_surface
#undef dlg_frame_tile_surface

/* 004f6646 auto */
void __thiscall pedia_redraw(PediaRedrawView *this)

{
  u32 uVar1;
  
  uVar1 = this->border_width;
  if (uVar1 == 0) {
    if (this->caption_height != 8) {
      pedia_draw_item_list((ListPaneWindow *)this);
    }
  }
  else if ((uVar1 != 1) && (uVar1 != 2)) {
    pedia_close();
  }
  return;
}

/* 004f66c6 auto */
#define dlg_sel_text_color (*(int *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(int *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(int *)((u8 *)&g.d_00635a20))
#define list_text_color (*(int *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define pedia_advance_names (*(i32 *)((u8 *)&g.d_006a7d44))
#define pedia_concept_names (*(i32 *)((u8 *)&g.d_006a7d5c))
#define pedia_government_names (*(i32 *)((u8 *)&g.d_006a7d54))
#define pedia_improvement_names (*(i32 *)((u8 *)&g.d_006a7d48))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define pedia_unit_names (*(i32 *)((u8 *)&g.d_006a7d50))
#define pedia_wonder_names (*(i32 *)((u8 *)&g.d_006a7d4c))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_14c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_148 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_144 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_140 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_13c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_138 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_134 (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_130 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_12c (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_11c (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_10c (*(i8 (*)[16])(frame_ + FRAME_OFF(68)))
#define local_fc (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define local_ec (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define local_dc (*(i8 (*)[16])(frame_ + FRAME_OFF(116)))
#define local_cc (*(i8 (*)[16])(frame_ + FRAME_OFF(132)))
#define local_bc (*(i8 (*)[16])(frame_ + FRAME_OFF(148)))
#define local_ac (*(i8 (*)[16])(frame_ + FRAME_OFF(164)))
#define local_9c (*(i8 (*)[16])(frame_ + FRAME_OFF(180)))
#define local_8c (*(i8 (*)[16])(frame_ + FRAME_OFF(196)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(212)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(216)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(220)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(224)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(228)))
#define local_68 (*(i32 *)(frame_ + FRAME_OFF(232)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(236)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(240)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(244)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(248)))
#define local_54 (*(i32 *)(frame_ + FRAME_OFF(252)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(256)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(260)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(264)))
#define local_44 (*(uint *)(frame_ + FRAME_OFF(268)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(272)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_38 (*(Sprite * *)(frame_ + FRAME_OFF(280)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(284)))
#define local_30 (*(uint *)(frame_ + FRAME_OFF(288)))
#define local_2c (*(tagRECT *)(frame_ + FRAME_OFF(292)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(308)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(312)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(328)))
void __thiscall pedia_draw_item_list(ListPaneWindow *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(336)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_3c = 0;
  pedia_history_push((ScaledWindowView *)&pedia_window);
  surface_get_clip((DibSurface *)this,(iptr)local_18);
  surface_set_clip((DibSurface *)this,(iptr)(this[0x18].pad_48 + 0x3c));
  surface_fill_rect((DibSurface *)this,(iptr)(this[0x18].pad_48 + 0x3c),list_bg_color);
  local_8 = (GameFont *)&font_size21;
  local_50 = *(int *)(this[0x18].pad_48 + 0x3c);
  local_4c = rect_width((iptr)(this[0x18].pad_48 + 0x3c));
  local_74 = local_4c / 2;
  local_1c = rect_height((iptr)(this[0x18].pad_48 + 0x3c));
  local_1c = local_1c / 9;
  iVar1 = local_1c / 2;
  iVar2 = font_cached_height(local_8);
  local_7c = iVar1 - iVar2 / 2;
  local_64 = 0;
  do {
    if (1 < local_64) {
      surface_set_clip((DibSurface *)this,(iptr)local_18);
      ctrl_show_and_redraw(*(Control **)(this[0x18].pad_48 + 0x38));
      return;
    }
    local_60 = local_64 * 9;
    for (local_5c = 0; local_5c < 9; local_5c++) {
      local_58 = *(int *)(this[0x18].pad_48 + 0x40) + local_1c * local_5c;
      SetRect(&local_2c,local_50,local_58,local_74 + local_50 - 2,local_1c + local_58);
      if ((this[0x1c].field_2c != 0xffffffff) &&
         ((int)(this[0x1c].field_2c + local_60 + local_5c) < *(int *)(this[0x18].pad_48 + 0x4c))) {
        advance = *(iptr *)(this[0x18].pad_48 +
                            (this[0x1c].field_2c + local_60 + local_5c) * 4 + 0x50);
        local_30 = (uint)(this[0x1c].field_2c + local_60 + local_5c == pedia_selected_item);
        if (local_30 == 0) {
          local_34 = list_text_color;
          local_48 = list_shadow_color;
        }
        else {
          local_34 = dlg_sel_text_color;
          local_48 = dlg_sel_text_shadow_color;
        }
        gfx_get_scale_ratio((iptr)&local_68,(iptr)&local_54);
        switch(this->caption_height) {
        case 1:
          local_38 = (Sprite *)
                     (&advance_category_icon_sprites +
                     (char)advances[advance].epoch * 0x3c +
                     (char)advances[advance].category * 0xf0);
          gfx_set_scale_ratio(3,2);
          local_3c = 3;
          break;
        case 2:
          local_38 = (Sprite *)(&improvement_icon_sprites + advance * 0x3c);
          gfx_set_scale_ratio(3,2);
          local_3c = 3;
          break;
        case 3:
          local_38 = (Sprite *)(&improvement_icon_sprites + advance * 0x3c);
          gfx_set_scale_ratio(3,2);
          local_3c = 3;
          break;
        case 4:
          local_38 = (Sprite *)(&unit_sprites + advance * 0x3c);
          break;
        case 5:
          local_3c = -5;
          local_70 = advance % 0xb;
          if ((this[0x1c].field_2c + local_60 + local_5c & 1) == 0) {
            local_6c = panel_margin_x;
          }
          else {
            iVar1 = sprite_width((Sprite *)&forest_sprites);
            local_6c = panel_margin_x + iVar1 / 2;
          }
          iVar1 = sprite_width((Sprite *)&forest_sprites);
          local_40 = panel_margin_x + (iVar1 * 3) / 2 + 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_130 = list_bg_color;
          }
          else {
            local_130 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&local_2c,local_130);
          sprite_draw
                    ((Sprite *)(&terrain_base_sprites + local_70 * 0x3c),(iptr)local_8c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),
                     local_6c + local_50,local_58);
          if (advance < 0xb) {
            if (advance == 3) {
              sprite_draw
                        ((Sprite *)&forest_sprites,(iptr)local_9c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,
                         local_58);
            }
            else if (advance == 4) {
              sprite_draw
                        ((Sprite *)&hill_sprites,(iptr)local_ac,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,
                         local_58);
            }
            else if (advance == 5) {
              sprite_draw
                        ((Sprite *)&mountain_sprites,(iptr)local_bc,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,
                         local_58);
            }
          }
          else {
            local_44 = (uint)(0x15 < advance);
            switch(advance) {
            case 0xd:
            case 0x18:
              sprite_draw
                        ((Sprite *)&grassland_shield_sprite,(iptr)local_cc,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,
                         local_58);
              goto LAB_004f6d04;
            case 0xe:
            case 0x19:
              sprite_draw
                        ((Sprite *)&forest_sprites,(iptr)local_dc,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,
                         local_58);
              break;
            case 0xf:
            case 0x1a:
              sprite_draw
                        ((Sprite *)&hill_sprites,(iptr)local_ec,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,
                         local_58);
              break;
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17: ;
            }
            sprite_draw
                      ((Sprite *)(&terrain_resource_sprites + local_70 * 0x78 + local_44 * 0x3c),
                       (iptr)local_fc,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_6c + local_50,local_58);
          }
          break;
        case 6:
        case 7:
          local_3c = -2;
          break;
        default:
          text_append(ADDR(0x62f03c, ((u8 *)&g.d_0062f03c)));
        }
LAB_004f6d04:
        if (local_3c == 3) {
          iVar1 = sprite_width(local_38);
          local_40 = (iVar1 * 3) / 2 + panel_margin_x * 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_134 = list_bg_color;
          }
          else {
            local_134 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&local_2c,local_134);
          sprite_draw
                    (local_38,(iptr)local_10c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),panel_margin_x + local_50,local_2c.top + 1);
        }
        else if (local_3c == 0) {
          iVar1 = sprite_width(local_38);
          local_40 = panel_margin_x * 3 + iVar1 * 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_138 = list_bg_color;
          }
          else {
            local_138 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&local_2c,local_138);
          local_6c = sprite_width(local_38);
          local_6c += panel_margin_x * 2;
          local_13c = local_6c;
          if ((this[0x1c].field_2c + local_60 + local_5c & 1) == 0) {
            local_13c = panel_margin_x;
          }
          iVar2 = local_58 + local_1c / 2;
          iVar1 = sprite_get_height(local_38);
          sprite_draw
                    (local_38,(iptr)local_11c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_50 + local_13c,iVar2 - iVar1 / 2);
        }
        else if (local_3c == 2) {
          iVar1 = sprite_width(local_38);
          local_40 = panel_margin_x * 3 + iVar1 * 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_140 = list_bg_color;
          }
          else {
            local_140 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&local_2c,local_140);
          iVar1 = sprite_width(local_38);
          iVar2 = sprite_width(local_38);
          iVar3 = sprite_width(local_38);
          local_6c = ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) + iVar2 / 6 + iVar3 +
                     panel_margin_x * 2;
          local_38 = (Sprite *)&shield_icon_sprite;
          local_144 = local_6c;
          if ((this[0x1c].field_2c + local_60 + local_5c & 1) == 0) {
            local_144 = panel_margin_x;
          }
          iVar2 = local_58 + local_1c / 2;
          iVar1 = sprite_get_height((Sprite *)&shield_icon_sprite);
          sprite_draw
                    (local_38,(iptr)local_12c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_50 + local_144,iVar2 - iVar1 / 2);
        }
        else if (local_3c == -1) {
          iVar1 = sprite_width(local_38);
          local_40 = panel_margin_x * 3 + iVar1 * 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_148 = list_bg_color;
          }
          else {
            local_148 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&local_2c,local_148);
        }
        else if (local_3c != -5) {
          local_40 = panel_margin_x * 5 + 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_14c = list_bg_color;
          }
          else {
            local_14c = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&local_2c,local_14c);
        }
        local_3c = 0;
        gfx_set_scale_ratio(local_68,local_54);
        text_clear();
        advance = this[0x1c].field_2c + local_60 + local_5c;
        switch(this->caption_height) {
        case 1:
          uVar4 = pedia_lookup_text(pedia_advance_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        case 2:
          uVar4 = pedia_lookup_text(pedia_improvement_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        case 3:
          uVar4 = pedia_lookup_text(pedia_wonder_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        case 4:
          uVar4 = pedia_lookup_text(pedia_unit_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        case 5:
          uVar4 = pedia_lookup_text(pedia_terrain_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        case 6:
          uVar4 = pedia_lookup_text(pedia_government_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        case 7:
          uVar4 = pedia_lookup_text(pedia_concept_names,advance);
          crt_strcpy(&text_buffer,uVar4);
          break;
        default:
          text_append(ADDR(0x62f058, ((u8 *)&g.d_0062f058)));
        }
        surface_set_clip((DibSurface *)this,(iptr)&local_2c);
        if (local_48 != local_34) {
          gfx_set_text_color_index(local_48);
          surface_draw_text
                    ((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40 + local_50 + 2,
                     local_7c + local_58 + 1,5);
          gfx_set_text_color_index(local_34);
          surface_draw_text
                    ((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40 + local_50 + 1,
                     local_7c + local_58,5);
        }
        gfx_set_text_color_index(local_34);
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40 + local_50,
                   local_7c + local_58,5);
        surface_set_clip((DibSurface *)this,(iptr)(this[0x18].pad_48 + 0x3c));
      }
    }
    local_50 = *(int *)(this[0x18].pad_48 + 0x3c) + (local_64 + 1) * local_74;
    local_64++;
  } while( true );
}
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef panel_margin_x
#undef pedia_advance_names
#undef pedia_concept_names
#undef pedia_government_names
#undef pedia_improvement_names
#undef pedia_selected_item
#undef pedia_terrain_names
#undef pedia_unit_names
#undef pedia_wonder_names
#undef text_buffer
#undef local_14c
#undef local_148
#undef local_144
#undef local_140
#undef local_13c
#undef local_138
#undef local_134
#undef local_130
#undef local_12c
#undef local_11c
#undef local_10c
#undef local_fc
#undef local_ec
#undef local_dc
#undef local_cc
#undef local_bc
#undef local_ac
#undef local_9c
#undef local_8c
#undef local_7c
#undef advance
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
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_1c
#undef local_18
#undef local_8

/* 004f7313 auto */
void __cdecl pedia_list_on_scroll(int param_1)

{
  if (pedia_list_top != param_1 * 9) {
    pedia_list_top = param_1 * 9;
    pedia_draw_item_list((ListPaneWindow *)&pedia_window);
  }
  return;
}

/* 004f734a auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
int __cdecl pedia_list_hit_test(int param_1,int param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 < pedia_list_rect_top) {
    local_14 = -1;
  }
  else if (param_2 < pedia_list_rect_bottom) {
    if (param_1 < pedia_list_rect) {
      local_14 = -3;
    }
    else if (param_1 < pedia_list_rect_right) {
      iVar1 = rect_width(ADDR(0x6a818c, ((u8 *)&g.d_006a818c)));
      local_c = (uint)(pedia_list_rect + iVar1 / 2 <= param_1);
      iVar1 = rect_height(ADDR(0x6a818c, ((u8 *)&g.d_006a818c)));
      local_14 = (param_2 - pedia_list_rect_top) / (iVar1 / 9) + local_c * 9 + pedia_list_top;
      if (pedia_list_count <= local_14) {
        local_14 = -5;
      }
    }
    else {
      local_14 = -4;
    }
  }
  else {
    local_14 = -2;
  }
  return local_14;
}
#undef local_14
#undef local_c

/* 004f7454 auto */
void __thiscall pedia_scroll_to_item(WindowObjectView *this,int param_1)

{
  if (param_1 < pedia_list_top) {
    for (pedia_list_top = param_1; pedia_list_top % 9 != 0; pedia_list_top--) {
    }
  }
  else if (pedia_list_top + 0x12 <= param_1) {
    for (pedia_list_top = param_1; pedia_list_top % 9 != 0; pedia_list_top--) {
    }
  }
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}

/* 004f74eb auto */
#define pedia_advance_names (*(i32 * *)((u8 *)&g.d_006a7d44))
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_concept_names (*(i32 * *)((u8 *)&g.d_006a7d5c))
#define pedia_government_names (*(i32 * *)((u8 *)&g.d_006a7d54))
#define pedia_improvement_names (*(i32 * *)((u8 *)&g.d_006a7d48))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_terrain_names (*(i32 * *)((u8 *)&g.d_006a7d58))
#define pedia_unit_names (*(i32 * *)((u8 *)&g.d_006a7d50))
#define pedia_wonder_names (*(i32 * *)((u8 *)&g.d_006a7d4c))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 * *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(16)))
int __cdecl pedia_find_item_by_key(int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(pedia_category) {
  case 1:
    local_10 = pedia_advance_names;
    local_14 = pedia_advance_entry_count;
    break;
  case 2:
    local_10 = pedia_improvement_names;
    local_14 = pedia_improvement_entry_count;
    break;
  case 3:
    local_10 = pedia_wonder_names;
    local_14 = pedia_wonder_entry_count;
    break;
  case 4:
    local_10 = pedia_unit_names;
    local_14 = pedia_unit_entry_count;
    break;
  case 5:
    local_10 = pedia_terrain_names;
    local_14 = pedia_terrain_count;
    break;
  case 6:
    local_10 = pedia_government_names;
    local_14 = pedia_government_entry_count;
    break;
  case 7:
    local_10 = pedia_concept_names;
    local_14 = pedia_concept_entry_count;
    break;
  default:
    return 0xffffffff;
  }
  local_8 = local_10;
  local_c = pedia_selected_item + 1;
  if (pedia_list_count <= local_c) {
    local_c = 0;
  }
  for (; local_c != 0; local_c--) {
    if (local_8[2] == 0) {
      local_8 = local_10;
    }
    else {
      local_8 = (i32 *)local_8[2];
    }
  }
  local_c = pedia_selected_item + 1;
  if (pedia_list_count <= local_c) {
    local_c = 0;
  }
  while ((local_14 != 0 && (iVar1 = crt_toupper((int)*(char *)*local_8), iVar1 != param_1))) {
    if (local_8[2] == 0) {
      local_8 = local_10;
      local_c = 0;
    }
    else {
      local_8 = (i32 *)local_8[2];
      local_c++;
    }
    local_14--;
  }
  if (local_14 == 0) {
    local_c = -1;
  }
  return local_c;
}
#undef pedia_advance_names
#undef pedia_category
#undef pedia_concept_names
#undef pedia_government_names
#undef pedia_improvement_names
#undef pedia_selected_item
#undef pedia_terrain_names
#undef pedia_unit_names
#undef pedia_wonder_names
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004f76ce auto */
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(int *)((u8 *)&g.d_006a6788))
void __cdecl pedia_list_on_key(i32 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = pedia_selected_item;
  if (pedia_page_mode == 0) {
    iVar1 = crt_toupper(param_1);
    if ((iVar1 < 0x41) || (0x5a < iVar1)) {
      switch(iVar1) {
      case 0xa1:
      case 199:
        pedia_topic = pedia_list_count - 1;
        for (pedia_list_top = pedia_topic; pedia_list_top % 9 != 0; pedia_list_top--) {
        }
        pedia_selected_item = pedia_topic;
        pedia_redraw((PediaRedrawView *)&pedia_window);
        scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        break;
      case 0xa2:
      case 0xc1:
        iVar2++;
        if (iVar2 < pedia_list_count) {
          pedia_topic = iVar2;
          pedia_selected_item = iVar2;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,iVar2);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xa3:
      case 0xa6:
      case 0xc3:
      case 0xc6:
        iVar2 += 9;
        if (iVar2 < pedia_list_count) {
          pedia_topic = iVar2;
          pedia_selected_item = iVar2;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,iVar2);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xa4:
      case 0xa9:
      case 0xc2:
      case 0xc5:
        iVar2 -= 9;
        if (-1 < iVar2) {
          pedia_topic = iVar2;
          pedia_selected_item = iVar2;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,iVar2);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xa7:
      case 0xc4:
        pedia_topic = 0;
        pedia_selected_item = 0;
        pedia_list_top = 0;
        scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,0);
        pedia_redraw((PediaRedrawView *)&pedia_window);
        break;
      case 0xa8:
      case 0xc0:
        iVar2--;
        if (-1 < iVar2) {
          pedia_topic = iVar2;
          pedia_selected_item = iVar2;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,iVar2);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xd0: ;
      }
    }
    else {
      iVar2 = pedia_find_item_by_key(iVar1);
      if (-1 < iVar2) {
        pedia_topic = iVar2;
        pedia_selected_item = iVar2;
        pedia_scroll_to_item((WindowObjectView *)&pedia_window,iVar2);
        scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
      }
    }
  }
  return;
}
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic

/* 004f7a30 auto */
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(int *)((u8 *)&g.d_006a6788))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_list_on_click(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((pedia_page_mode == 0) &&
       (wnd_get_cursor_pos
                  ((WndBase *)&pedia_window_wnd,(iptr)&local_8,(iptr)&local_c), pedia_list_count != 0)
       ) && (iVar1 = pedia_list_hit_test(local_8,local_c), -1 < iVar1)) && (iVar1 < pedia_list_count)) {
    pedia_topic = iVar1;
    pedia_selected_item = iVar1;
    pedia_redraw((PediaRedrawView *)&pedia_window);
  }
  return;
}
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic
#undef local_c
#undef local_8

/* 004f7ac7 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __thiscall pedia_set_category_title(WindowObjectView *this,i32 param_1)

{
  text_clear();
  switch(param_1) {
  case 1:
  case 8:
    text_append_label(0x29f);
    break;
  case 2:
    text_append_label(0x2a0);
    break;
  case 3:
    text_append_label(0x2a1);
    break;
  case 4:
    text_append_label(0x2a2);
    break;
  case 5:
    text_append_label(0x2a3);
    break;
  case 6:
    text_append_label(0x2a4);
    break;
  case 7:
    text_append_label(0x2a5);
    break;
  default:
    text_append(ADDR(0x62f078, ((u8 *)&g.d_0062f078)));
  }
  crt_strcpy(this + 0x186,&text_buffer);
  return;
}
#undef text_buffer

/* 004f7bd1 auto */
#define pedia_back_topic (*(i32 *)((u8 *)&g.d_0062f010))
#define pedia_going_back (*(i32 *)((u8 *)&g.d_0062f00c))
void __thiscall pedia_open_category(MediaWindow *this,u32 param_1,int param_2)

{
  this->style_flags = 0;
  this->border_width = 0;
  this->resize_border = 0;
  this->caption_height = param_1;
  this->client_y = 0;
  pedia_back_topic = 0xffffffff;
  pedia_going_back = 0;
  pedia_set_category_title((WindowObjectView *)this,param_1);
  pedia_update_controls(this);
  this->caption_height = param_1;
  wnd_repaint((SurfaceWindow *)this);
  if (param_2 != 0) {
    window_show((WindowObjectView *)this);
  }
  wnd_set_keyboard_nav((Wnd *)&pedia_window_wnd,0);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_history_push((ScaledWindowView *)&pedia_window);
  return;
}
#undef pedia_back_topic
#undef pedia_going_back

/* 004f7c99 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_buffer_plus2 (*(i8 *)((u8 *)&g.d_00679642))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(char (*)[2])(frame_ + FRAME_OFF(16)))
#define local_e (*(i8 *)(frame_ + FRAME_OFF(18)))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(24)))
void __thiscall pedia_load_indexes(DocumentWindow *this)

{
  u8 *puVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  size_t sVar5;
  void *pvVar6;
  i32 uVar7;
  iptr iVar8;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_18 = 0; local_18 < 100; local_18++) {
    puVar1 = this->pad_65c + local_18 * 4;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_18 = 0; local_18 < 0x27; local_18++) {
    puVar1 = this->pad_980 + local_18 * 4;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_18 = 0; local_18 < 0x1c; local_18++) {
    puVar1 = this[1].pad_48 + local_18 * 4 + 0x4c;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_18 = 0; local_18 < 0x3e; local_18++) {
    puVar1 = this[1].pad_15c + local_18 * 4 + 0x1c;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_18 = 0; local_18 < 7; local_18++) {
    puVar1 = this[1].pad_364 + local_18 * 4 + 8;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_18 = 0; local_18 < 0x21; local_18++) {
    puVar1 = this[1].pad_3c0 + local_18 * 4 - 0x18;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  for (local_18 = 0; local_18 < 0x100; local_18++) {
    puVar1 = this[1].pad_4a4 + local_18 * 4 + 0x10;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  pedia_free_lists((WindowObjectView *)this);
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0a0, ((u8 *)&g.d_0062f0a0)));
  if (iVar3 == 0) {
    text_read_line(1);
    local_14 = text_next_int();
    this->pedia_advance_count = 0;
    improvement = 0;
    while (local_14 != -2) {
      if (advances[improvement].enabled != '\0') {
        *(int *)(this->pad_65c + this->pedia_advance_count * 4) = local_14;
        *(iptr *)(this->pad_65c + this->pedia_advance_count * 4 + 400) = improvement;
        local_c = operator_new(0xc);
        local_c[1] = this->pedia_advance_count;
        if (this[2].field_28c == 0) {
          this[2].field_28c = (u32)local_c;
        }
        else {
          local_8[2] = local_c;
        }
        local_c[2] = 0;
        pcVar4 = (char *)label_string(advances[improvement].name);
        sVar5 = _strlen(pcVar4);
        pvVar6 = operator_new(sVar5 + 1);
        *local_c = pvVar6;
        uVar7 = label_string(advances[improvement].name);
        crt_strcpy(*local_c,uVar7);
        local_8 = local_c;
        this->pedia_advance_count++;
      }
      improvement++;
      text_read_line(1);
      local_14 = text_next_int();
    }
    text_close_file();
    if (this[2].field_28c != 0) {
      pedia_sort_list(this,this[2].field_28c,(iptr)this->pad_65c,(iptr)(this->pad_65c + 400),
                         this->pedia_advance_count);
    }
  }
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0b0, ((u8 *)&g.d_0062f0b0)));
  if (iVar3 == 0) {
    text_read_line(1);
    text_read_line(1);
    local_14 = text_next_int();
    this->pedia_improve_count = 0;
    improvement = 1;
    while (local_14 != -2) {
      if (-2 < improvements[improvement].preq) {
        *(int *)(this->pad_980 + this->pedia_improve_count * 4) = local_14;
        *(iptr *)(this->pad_980 + this->pedia_improve_count * 4 + 0x9c) = improvement;
        local_c = operator_new(0xc);
        local_c[1] = this->pedia_improve_count;
        if (this[2].field_290 == 0) {
          this[2].field_290 = (uptr)local_c;
        }
        else {
          local_8[2] = local_c;
        }
        local_c[2] = 0;
        pcVar4 = (char *)label_string(improvements[improvement].name);
        sVar5 = _strlen(pcVar4);
        pvVar6 = operator_new(sVar5 + 1);
        *local_c = pvVar6;
        uVar7 = label_string(improvements[improvement].name);
        crt_strcpy(*local_c,uVar7);
        local_8 = local_c;
        this->pedia_improve_count++;
      }
      improvement++;
      text_read_line(1);
      local_14 = text_next_int();
    }
    text_close_file();
    if (this[2].field_290 != 0) {
      pedia_sort_list(this,this[2].field_290,(iptr)this->pad_980,(iptr)&this->edit_action_button,
                         this->pedia_improve_count);
    }
  }
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0c4, ((u8 *)&g.d_0062f0c4)));
  if (iVar3 == 0) {
    text_read_line(1);
    local_14 = text_next_int();
    this[1].pad_48[0x48] = '\0';
    this[1].pad_48[0x49] = '\0';
    this[1].pad_48[0x4a] = '\0';
    this[1].pad_48[0x4b] = '\0';
    improvement = 0x27;
    while (local_14 != -2) {
      if (-2 < improvements[improvement].preq) {
        *(int *)(this[1].pad_48 + *(int *)(this[1].pad_48 + 0x48) * 4 + 0x4c) = local_14;
        *(iptr *)(this[1].pad_104 + *(int *)(this[1].pad_48 + 0x48) * 4) = improvement;
        local_c = operator_new(0xc);
        local_c[1] = *(i32 *)(this[1].pad_48 + 0x48);
        if (this[2].field_294 == 0) {
          this[2].field_294 = (uptr)local_c;
        }
        else {
          local_8[2] = local_c;
        }
        local_c[2] = 0;
        pcVar4 = (char *)label_string(improvements[improvement].name);
        sVar5 = _strlen(pcVar4);
        pvVar6 = operator_new(sVar5 + 1);
        *local_c = pvVar6;
        uVar7 = label_string(improvements[improvement].name);
        crt_strcpy(*local_c,uVar7);
        local_8 = local_c;
        *(int *)(this[1].pad_48 + 0x48) = *(int *)(this[1].pad_48 + 0x48) + 1;
      }
      improvement++;
      text_read_line(1);
      local_14 = text_next_int();
    }
    text_close_file();
    if (this[2].field_294 != 0) {
      pedia_sort_list(this,this[2].field_294,(iptr)(this[1].pad_48 + 0x4c),(iptr)this[1].pad_104,
                         *(iptr *)(this[1].pad_48 + 0x48));
    }
  }
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0d4, ((u8 *)&g.d_0062f0d4)));
  if (iVar3 == 0) {
    text_read_line(1);
    local_14 = text_next_int();
    this[1].pad_15c[0x18] = '\0';
    this[1].pad_15c[0x19] = '\0';
    this[1].pad_15c[0x1a] = '\0';
    this[1].pad_15c[0x1b] = '\0';
    improvement = 0;
    while (local_14 != -2) {
      if (-2 < unit_types[improvement].prerequisite) {
        *(int *)(this[1].pad_15c + *(int *)(this[1].pad_15c + 0x18) * 4 + 0x1c) = local_14;
        *(iptr *)(this[1].pad_274 + *(int *)(this[1].pad_15c + 0x18) * 4 - 4) = improvement;
        local_c = operator_new(0xc);
        local_c[1] = *(i32 *)(this[1].pad_15c + 0x18);
        if (this[2].field_298 == 0) {
          this[2].field_298 = (uptr)local_c;
        }
        else {
          local_8[2] = local_c;
        }
        local_c[2] = 0;
        pcVar4 = (char *)label_string(unit_types[improvement].name);
        sVar5 = _strlen(pcVar4);
        pvVar6 = operator_new(sVar5 + 1);
        *local_c = pvVar6;
        uVar7 = label_string(unit_types[improvement].name);
        crt_strcpy(*local_c,uVar7);
        local_8 = local_c;
        *(int *)(this[1].pad_15c + 0x18) = *(int *)(this[1].pad_15c + 0x18) + 1;
      }
      improvement++;
      text_read_line(1);
      local_14 = text_next_int();
    }
    text_close_file();
    if (this[2].field_298 != 0) {
      pedia_sort_list(this,this[2].field_298,(iptr)(this[1].pad_15c + 0x1c),
                         (iptr)&this[1].field_270,*(iptr *)(this[1].pad_15c + 0x18));
    }
  }
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0e0, ((u8 *)&g.d_0062f0e0)));
  if (iVar3 == 0) {
    text_read_line(1);
    local_14 = text_next_int();
    this[1].pad_364[4] = '\0';
    this[1].pad_364[5] = '\0';
    this[1].pad_364[6] = '\0';
    this[1].pad_364[7] = '\0';
    improvement = 0;
    while (local_14 != -2) {
      *(int *)(this[1].pad_364 + *(int *)(this[1].pad_364 + 4) * 4 + 8) = local_14;
      *(iptr *)(this[1].pad_364 + *(int *)(this[1].pad_364 + 4) * 4 + 0x24) = improvement;
      local_c = operator_new(0xc);
      local_c[1] = *(i32 *)(this[1].pad_364 + 4);
      if (this[2].field_29c == 0) {
        this[2].field_29c = (uptr)local_c;
      }
      else {
        local_8[2] = local_c;
      }
      local_c[2] = 0;
      pcVar4 = (char *)label_string(government_names[improvement]);
      sVar5 = _strlen(pcVar4);
      pvVar6 = operator_new(sVar5 + 1);
      *local_c = pvVar6;
      uVar7 = label_string(government_names[improvement]);
      crt_strcpy(*local_c,uVar7);
      local_8 = local_c;
      *(int *)(this[1].pad_364 + 4) = *(int *)(this[1].pad_364 + 4) + 1;
      improvement++;
      text_read_line(1);
      local_14 = text_next_int();
    }
    text_close_file();
    if (this[2].field_29c != 0) {
      pedia_sort_list(this,this[2].field_29c,(iptr)(this[1].pad_364 + 8),
                         (iptr)(this[1].pad_364 + 0x24),*(iptr *)(this[1].pad_364 + 4));
    }
  }
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0f4, ((u8 *)&g.d_0062f0f4)));
  if (iVar3 == 0) {
    text_read_line(1);
    local_14 = text_next_int();
    this[1].field_3a4 = 0;
    improvement = 0;
    while (local_14 != -2) {
      if (improvement != 0x18) {
        *(int *)(this[1].pad_3c0 + this[1].field_3a4 * 4 - 0x18) = local_14;
        *(iptr *)(this[1].pad_3c0 + this[1].field_3a4 * 4 + 0x6c) = improvement;
        local_c = operator_new(0xc);
        local_c[1] = this[1].field_3a4;
        if (this[2].field_2a0 == 0) {
          this[2].field_2a0 = (uptr)local_c;
        }
        else {
          local_8[2] = local_c;
        }
        local_c[2] = 0;
        text_clear();
        iVar8 = label_string(terrain_types[improvement].name);
        text_append(iVar8);
        if ((0xc < improvement) &&
           (iVar3 = _strcmp(terrain_types[improvement].abbrev,&pedia_grassland_shield_abbrev_str), iVar3 == 0)) {
          text_append_space();
          uVar7 = label_string(*(i32 *)(label_string_ids + 0xb00));
          crt_strcat(&text_buffer,uVar7);
        }
        sVar5 = _strlen(&text_buffer);
        pvVar6 = operator_new(sVar5 + 1);
        *local_c = pvVar6;
        crt_strcpy(*local_c,&text_buffer);
        local_8 = local_c;
        this[1].field_3a4++;
      }
      improvement++;
      text_read_line(1);
      local_14 = text_next_int();
    }
    text_close_file();
    if (this[2].field_2a0 != 0) {
      pedia_sort_list(this,this[2].field_2a0,(iptr)&this[1].field_3a8,
                         (iptr)(this[1].pad_3c0 + 0x6c),this[1].field_3a4);
    }
  }
  iVar3 = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f108, ((u8 *)&g.d_0062f108)));
  if (iVar3 == 0) {
    bVar2 = true;
    this[1].pad_4a4[0xc] = '\0';
    this[1].pad_4a4[0xd] = '\0';
    this[1].pad_4a4[0xe] = '\0';
    this[1].pad_4a4[0xf] = '\0';
    local_e = 0;
    improvement = 0;
    while (bVar2) {
      text_read_line(1);
      _strncpy(local_10,&text_buffer,2);
      iVar3 = _strcmp(local_10,&pedia_index_marker_str);
      if (iVar3 == 0) {
        *(i32 *)(this[1].pad_4a4 + *(int *)(this[1].pad_4a4 + 0xc) * 4 + 0x10) =
             *(i32 *)(this[1].pad_4a4 + 0xc);
        *(iptr *)(this[1].pad_65c + *(int *)(this[1].pad_4a4 + 0xc) * 4 + 600) = improvement;
        local_c = operator_new(0xc);
        local_c[1] = *(i32 *)(this[1].pad_4a4 + 0xc);
        if (this[2].field_2a4 == 0) {
          this[2].field_2a4 = (uptr)local_c;
        }
        else {
          local_8[2] = local_c;
        }
        local_c[2] = 0;
        sVar5 = _strlen(&text_buffer_plus2);
        pvVar6 = operator_new(sVar5 + 1);
        *local_c = pvVar6;
        crt_strcpy(*local_c,&text_buffer_plus2);
        local_8 = local_c;
        improvement++;
        *(int *)(this[1].pad_4a4 + 0xc) = *(int *)(this[1].pad_4a4 + 0xc) + 1;
      }
      else if (local_10[0] == '@') {
        bVar2 = false;
      }
    }
    if (this[2].field_2a4 != 0) {
      pedia_sort_list(this,this[2].field_2a4,(iptr)(this[1].pad_4a4 + 0x10),
                         (iptr)(this[1].pad_65c + 600),*(iptr *)(this[1].pad_4a4 + 0xc));
    }
  }
  return;
}
#undef text_buffer
#undef text_buffer_plus2
#undef improvement
#undef local_18
#undef local_14
#undef local_10
#undef local_e
#undef local_c
#undef local_8

/* 004f896a auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(16)))
void __thiscall pedia_sort_list(void *this,iptr param_1,iptr param_2,iptr param_3,iptr param_4)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (i32 *)param_1;
  local_8 = (i32 *)param_1;
  for (local_14 = 0; local_14 < param_4 - 1; local_14++) {
    local_18 = local_14;
    if (local_8[2] != 0) {
      local_c = (i32 *)local_8[2];
    }
    while (local_18 = local_18 + 1, local_18 < param_4) {
      iVar2 = _strcmp((char *)*local_8,(char *)*local_c);
      if (0 < iVar2) {
        uVar1 = *(i32 *)(param_2 + local_14 * 4);
        *(i32 *)(param_2 + local_14 * 4) = *(i32 *)(param_2 + local_18 * 4);
        *(i32 *)(param_2 + local_18 * 4) = uVar1;
        uVar1 = *(i32 *)(param_3 + local_14 * 4);
        *(i32 *)(param_3 + local_14 * 4) = *(i32 *)(param_3 + local_18 * 4);
        *(i32 *)(param_3 + local_18 * 4) = uVar1;
        uVar1 = *local_8;
        *local_8 = *local_c;
        *local_c = uVar1;
      }
      if (local_c[2] != 0) {
        local_c = (i32 *)local_c[2];
      }
    }
    if (local_8[2] != 0) {
      local_8 = (i32 *)local_8[2];
    }
  }
  return;
}
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 004f8a9b auto */
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl pedia_lookup_text(i32 *param_1,iptr param_2)

{
  i8 *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = param_1; (local_8 != (i32 *)0x0 && (local_8[1] != param_2));
      local_8 = (i32 *)local_8[2]) {
  }
  puVar1 = pedia_missing_text;
  if (local_8 != (i32 *)0x0) {
    puVar1 = (i8 *)*local_8;
  }
  return puVar1;
}
#undef local_8

/* 004f8af9 auto */
#define pedia_back_topic (*(int *)((u8 *)&g.d_0062f010))
#define pedia_going_back (*(int *)((u8 *)&g.d_0062f00c))
#define pedia_history_count (*(int *)((u8 *)&g.d_006a6790))
void __thiscall pedia_history_push(ScaledWindowView *this)

{
  if (((int)this->client_y < 99) && (pedia_going_back == 0)) {
    if (((this->client_y == 0) ||
        (((*(u32 *)(this[2].pad_48 + this->client_y * 4 + 0x18) != this->border_width ||
          (*(int *)(this[2].pad_48 + this->client_y * 4 + 0x18) != 0)) ||
         (*(int *)(this[3].pad_48 + this->client_y * 4 + 0x7c) == 8)))) || (this->caption_height == 8))
    {
      if (((this->client_y == 0) ||
          (*(u32 *)(this[3].pad_48 + this->client_y * 4 + 0x7c) != this->caption_height)) ||
         ((*(u32 *)(this[2].pad_48 + this->client_y * 4 + 0x18) != this->border_width ||
          (*(u32 *)(this->pad_104 + pedia_history_count * 4 + 0x24) != this->resize_border)))) {
        if (-1 < pedia_back_topic) {
          *(int *)(this[1].pad_48 + this->client_y * 4 - 0x48) = pedia_back_topic;
          *(i32 *)(this[2].pad_48 + this->client_y * 4 + 0x1c) = pedia_popped_page_mode;
          *(i32 *)(this[3].pad_48 + this->client_y * 4 + 0x80) = pedia_popped_category;
          this->client_y++;
        }
        *(u32 *)(this[1].pad_48 + this->client_y * 4 - 0x48) = this->resize_border;
        *(u32 *)(this[2].pad_48 + this->client_y * 4 + 0x1c) = this->border_width;
        *(u32 *)(this[3].pad_48 + this->client_y * 4 + 0x80) = this->caption_height;
        this->client_y++;
      }
    }
    else {
      *(u32 *)(this->pad_104 + this->client_y * 4 + 0x24) = this->resize_border;
    }
  }
  pedia_back_topic = 0xffffffff;
  pedia_going_back = 0;
  return;
}
#undef pedia_back_topic
#undef pedia_going_back
#undef pedia_history_count

/* 004f8d04 auto */
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
void __cdecl pedia_modal_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if ((pedia_modal_active == 0) || (pedia_closed == 1)) {
    wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
    pedia_modal_active = 0;
  }
  return;
}
#undef pedia_closed

/* 004f8d51 auto */
void __cdecl pedia_end_modal(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
  return;
}

/* 004fa0f0 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CControlBarInfo::`scalar deleting destructor'(unsigned int)
    public: virtual void * __thiscall __non_rtti_object::`scalar deleting destructor'(unsigned int)
    public: virtual void * __thiscall bad_cast::`scalar deleting destructor'(unsigned int)
    public: virtual void * __thiscall bad_typeid::`scalar deleting destructor'(unsigned int)
     9 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void * __thiscall pedia_link_scalar_dtor(void *this,uint param_1)

{
  pedia_link_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004fa140 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: __thiscall CControlBarInfo::~CControlBarInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall pedia_link_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004fa17e */ { hyperlink_dtor((HyperlinkDtorView *)(*(int *)((iptr)&this) + 4)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00518f00 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_government_list(MediaWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this[2].field_158 <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)this[4].pad_2c4 = this[2].field_158;
  *(u32 *)(this[5].pad_48 + 100) = this->resize_border;
  *(u32 *)(this[5].pad_48 + 0x68) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[5].pad_48 + 0x68) = *(int *)(this[5].pad_48 + 0x68) - 1;
  }
  for (local_8 = 0; local_8 < (int)this[2].field_158; local_8++) {
    *(i32 *)(this[4].pad_2c4 + local_8 * 4 + 4) =
         *(i32 *)(this[2].pad_15c + local_8 * 4 + 0x1c);
  }
  scrollbar_set_range
            ((Control *)&this[4].field_270,0,*(int *)this[4].pad_2c4 / 9);
  scrollbar_set_pos
            ((ClickControl *)&this[4].field_270,*(int *)(this[5].pad_48 + 0x68) / 9);
  if (*(int *)this[4].pad_2c4 < 1) {
    this[5].pad_48[0x68] = 0xff;
    this[5].pad_48[0x69] = 0xff;
    this[5].pad_48[0x6a] = 0xff;
    this[5].pad_48[0x6b] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 005190d0 auto */
void __cdecl notice_dlg_global_init(void)

{
  notice_dlg_static_init();
  notice_dlg_reg_atexit();
  return;
}

/* 005190ea auto */
void __cdecl notice_dlg_static_init(void)

{
  dialog_ctor((Dialog *)&game_section_dialog,0x4000);
  return;
}

/* 00519109 auto */
void __cdecl notice_dlg_reg_atexit(void)

{
  _atexit(notice_dlg_static_dtor);
  return;
}

/* 00519126 auto */
void __cdecl notice_dlg_static_dtor(void)

{
  dialog_dtor((Dialog *)&game_section_dialog);
  return;
}

/* 005261a0 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_wonder_list(MediaWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this[1].field_49c <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)this[4].pad_2c4 = this[1].field_49c;
  *(u32 *)(this[5].pad_48 + 100) = this->resize_border;
  *(u32 *)(this[5].pad_48 + 0x68) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[5].pad_48 + 0x68) = *(int *)(this[5].pad_48 + 0x68) - 1;
  }
  for (local_8 = 0; local_8 < (int)this[1].field_49c; local_8++) {
    *(i32 *)(this[4].pad_2c4 + local_8 * 4 + 4) =
         *(i32 *)(this[1].pad_4a4 + local_8 * 4 + 0x6c);
  }
  scrollbar_set_range
            ((Control *)&this[4].field_270,0,*(int *)this[4].pad_2c4 / 9);
  scrollbar_set_pos
            ((ClickControl *)&this[4].field_270,*(int *)(this[5].pad_48 + 0x68) / 9);
  if (*(int *)this[4].pad_2c4 < 1) {
    this[5].pad_48[0x68] = 0xff;
    this[5].pad_48[0x69] = 0xff;
    this[5].pad_48[0x6a] = 0xff;
    this[5].pad_48[0x6b] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 0052630d auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_88 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_78 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_64 (*(tagRECT *)(frame_ + FRAME_OFF(36)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_4c (*(i32 *)(frame_ + FRAME_OFF(60)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_44 (*(i32 *)(frame_ + FRAME_OFF(68)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_34 (*(i32 *)(frame_ + FRAME_OFF(84)))
#define local_30 (*(tagRECT *)(frame_ + FRAME_OFF(88)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(128)))
/* WARNING: Removing unreachable block (ram,0x0052661a) */

void __thiscall pedia_draw_improvement(DocumentWindow *this)

{
  int iVar1;
  iptr iVar2;
  size_t sVar3;
  int iVar4;
  u32 yBottom;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 0;
  surface_get_clip((DibSurface *)this,(iptr)local_18);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  local_8 = (GameFont *)&font_size21;
  local_40 = this->content_left + 10;
  local_3c = rect_width((iptr)&this->content_left);
  local_1c = font_cached_height(local_8);
  local_48 = this->content_top + 8;
  local_38 = local_3c / 2 - 100;
  improvement = *(iptr *)(this[1].pad_104 + this->resize_border * 4);
  gfx_get_scale_ratio((iptr)&local_4c,(iptr)&local_44);
  gfx_set_scale_ratio(2,1);
  local_50 = sprite_get_width((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  local_50 += panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)local_78,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_40,
             local_48);
  gfx_set_scale_ratio(local_4c,local_44);
  gfx_set_text_color_index(list_text_color);
  local_40 = this->content_left + 10;
  iVar1 = sprite_height((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  local_48 = local_48 + iVar1 * 2 + 5;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_40 = local_40 + iVar1 + 5;
  text_clear();
  if (improvements[improvement].preq < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  }
  else {
    text_append_string_id(advances[improvements[improvement].preq].name);
    local_20 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_54 = font_line_spacing(local_8);
    SetRect(&local_30,local_40,local_48,local_40 + local_20 + 5,local_48 + local_54);
    pedia_add_link(this,(int)improvements[improvement].preq,local_40,local_48,0,local_30.left,
                       local_30.top,local_30.right,local_30.bottom);
  }
  local_38 = local_40;
  local_40 = this->content_left + 10;
  local_48 += local_1c;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_improvement_cost_fmt,(uint)improvements[improvement].cost * 10);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_48,5);
  iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_40 = local_38 + iVar1 + 3;
  iVar4 = local_48 + local_1c / 2;
  iVar1 = sprite_get_height((Sprite *)&shield_icon_sprite);
  sprite_draw
            ((Sprite *)&shield_icon_sprite,(iptr)local_88,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_40,iVar4 - iVar1 / 2);
  local_40 = this->content_left + 10;
  local_48 += local_1c;
  text_clear();
  text_append_label(0x9f);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  text_clear();
  if (improvement < 0x17) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_48,5);
  }
  else if ((char)(&wonder_expires_by_impr)[improvement] < 1) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_48,5);
  }
  else {
    iVar2 = label_string(advances[(char)(&wonder_expires_by_impr)[improvement]].name);
    text_append(iVar2);
    local_20 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_54 = font_line_spacing(local_8);
    SetRect(&local_30,local_38,local_48,local_38 + local_20 + 5,local_48 + local_54);
    pedia_add_link(this,(int)(char)(&wonder_expires_by_impr)[improvement],local_38,local_48,0,local_30.left,
                       local_30.top,local_30.right,local_30.bottom);
  }
  local_40 = this->content_left + 10;
  local_48 += local_1c * 2;
  pedia_load_improvement_text((WindowObjectView *)this,improvement);
  sVar3 = _strlen(&text_buffer);
  if (sVar3 != 0) {
    yBottom = this->content_bottom;
    iVar1 = rect_width((iptr)&this->content_left);
    SetRect(&local_64,local_40,local_48,iVar1 - 10 + local_40,yBottom);
    surface_draw_text_rect((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&local_64,5);
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)local_18);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef text_buffer
#undef local_88
#undef local_78
#undef improvement
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
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 00526913 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_wonder_names (*(i32 *)((u8 *)&g.d_006a7d4c))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_wonder_modal(DocumentWindow *this,int param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    for (local_8 = 0;
        ((int)local_8 < *(int *)(this[1].pad_48 + 0x48) &&
        (*(int *)(this[1].pad_104 + local_8 * 4) != param_1)); local_8++) {
    }
    if (*(u32 *)(this[1].pad_48 + 0x48) != local_8) {
      pedia_open_category((MediaWindow *)this,3,1);
      this->resize_border = local_8;
      *(u32 *)(this[3].pad_48 + 0x78) = local_8;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      uVar1 = pedia_lookup_text(pedia_wonder_names,local_8);
      crt_strcpy(this->pad_608 + 0x10,uVar1);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_improvement(this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_closed
#undef pedia_wonder_names
#undef local_8

/* 00564d00 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_advance_list(PediaAdvanceListView *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this->pedia_advance_count <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)(this[3].pad_464 + 8) = this->pedia_advance_count;
  *(u32 *)(this[4].pad_48 + 0x90) = this->resize_border;
  *(u32 *)(this[4].pad_48 + 0x94) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[4].pad_48 + 0x94) = *(int *)(this[4].pad_48 + 0x94) - 1;
  }
  for (local_8 = 0; local_8 < (int)this->pedia_advance_count; local_8++) {
    *(i32 *)(this[3].pad_464 + local_8 * 4 + 0xc) =
         *(i32 *)(this[1].pad_48 + local_8 * 4 + 0xc);
  }
  scrollbar_set_range
            ((Control *)(this[3].pad_3c0 + 0x58),0,*(int *)(this[3].pad_464 + 8) / 9);
  scrollbar_set_pos
            ((ClickControl *)(this[3].pad_3c0 + 0x58),*(int *)(this[4].pad_48 + 0x94) / 9);
  if (*(int *)(this[3].pad_464 + 8) < 1) {
    this[4].pad_48[0x94] = 0xff;
    this[4].pad_48[0x95] = 0xff;
    this[4].pad_48[0x96] = 0xff;
    this[4].pad_48[0x97] = 0xff;
  }
  pedia_update_controls((MediaWindow *)this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 00564e6d auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_1ac (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_19c (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_18c (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_17c (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_178 (*(int *)(frame_ + FRAME_OFF(56)))
#define advance3 (*(iptr *)(frame_ + FRAME_OFF(60)))
#define local_170 (*(int *)(frame_ + FRAME_OFF(64)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(68)))
#define local_168 (*(char * *)(frame_ + FRAME_OFF(72)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(76)))
#define local_160 (*(int *)(frame_ + FRAME_OFF(80)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(84)))
#define local_158 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_154 (*(u32 *)(frame_ + FRAME_OFF(92)))
#define local_150 (*(char * *)(frame_ + FRAME_OFF(96)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(100)))
#define local_148 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_144 (*(int *)(frame_ + FRAME_OFF(108)))
#define local_140 (*(tagRECT *)(frame_ + FRAME_OFF(112)))
#define local_130 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_12c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_128 (*(char *)(frame_ + FRAME_OFF(136)))
#define local_127 (*(char (*)[259])(frame_ + FRAME_OFF(137)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(396)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(400)))
#define local_1c (*(i8 (*)[16])(frame_ + FRAME_OFF(404)))
#define local_c (*(GameFont * *)(frame_ + FRAME_OFF(420)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(424)))
void __thiscall pedia_draw_advance_page(DocumentWindow *this)

{
  int iVar1;
  iptr iVar2;
  size_t sVar3;
  int iVar4;
  bool bVar5;
  i8 frame_[FRAME_OFF(432)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)local_1c);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  local_c = (GameFont *)&font_size21;
  local_154 = this->content_left;
  local_24 = font_cached_height((GameFont *)&font_size21);
  local_158 = this->content_top + 5;
  advance = *(iptr *)(this->pad_65c + this->resize_border * 4 + 400);
  sprite_draw
            ((Sprite *)
             (&advance_category_icon_sprites +
             (char)advances[advance].epoch * 0x3c + (char)advances[advance].category * 0xf0),
             (iptr)local_18c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),panel_margin_x + local_154,local_158);
  gfx_set_text_color_index(list_text_color);
  local_12c = 0;
  for (advance2 = 0; advance2 < 100; advance2++) {
    if ((advances[advance2].preq[0] == advance) || (advances[advance2].preq[1] == advance)) {
      local_12c++;
    }
  }
  for (improvement = 1; improvement < 0x43; improvement++) {
    if (improvements[improvement].preq == advance) {
      local_12c++;
    }
  }
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if (unit_types[unit_type].prerequisite == advance) {
      local_12c++;
    }
  }
  local_154 = this->content_left + 0x32;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
  iVar1 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_154 = local_154 + iVar1 + 5;
  text_clear();
  if ((advances[advance].preq[0] < '\0') && (advances[advance].preq[1] < '\0')) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
  }
  else {
    if (-1 < advances[advance].preq[0]) {
      text_append_string_id(advances[advances[advance].preq[0]].name);
      local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_160 = font_line_spacing(local_c);
      SetRect(&local_140,local_154,local_158,local_130 + local_154 + 5,local_160 + local_158);
      pedia_add_link(this,(int)advances[advance].preq[0],local_154,local_158,0,local_140.left,
                         local_140.top,local_140.right,local_140.bottom);
    }
    if (-1 < advances[advance].preq[1]) {
      if (-1 < advances[advance].preq[0]) {
        local_154 = local_154 + local_130 + 3;
        text_clear();
        text_append_comma();
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
        local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_130 += 4;
        local_154 += local_130;
      }
      text_clear();
      text_append_string_id(advances[advances[advance].preq[1]].name);
      local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_160 = font_line_spacing(local_c);
      SetRect(&local_140,local_154,local_158,local_130 + local_154 + 5,local_160 + local_158);
      pedia_add_link(this,(int)advances[advance].preq[1],local_154,local_158,0,local_140.left,
                         local_140.top,local_140.right,local_140.bottom);
    }
  }
  local_158 += local_24;
  local_154 = this->content_left + 2;
  text_clear();
  text_append_label(0x7a);
  text_append_colon();
  iVar1 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_20 = local_154 + iVar1 + 2;
  if (local_12c != 0) {
    surface_draw_text((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
  }
  text_clear();
  for (advance2 = 0; advance2 < 100; advance2++) {
    local_178 = 0;
    advance3 = -1;
    if (advances[advance2].preq[0] == advance) {
      local_178 = 1;
      advance3 = (iptr)advances[advance2].preq[1];
    }
    else if (advances[advance2].preq[1] == advance) {
      local_178 = 1;
      advance3 = (iptr)advances[advance2].preq[0];
    }
    if (local_178 != 0) {
      local_154 = local_20;
      text_clear();
      text_append_string_id(advances[advance2].name);
      local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_160 = font_line_spacing(local_c);
      SetRect(&local_140,local_154,local_158,local_130 + local_154 + 2,local_160 + local_158);
      pedia_add_link(this,advance2,local_154,local_158,0,local_140.left,local_140.top,
                         local_140.right,local_140.bottom);
      iVar1 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_154 = local_154 + iVar1 + 2;
      if (-1 < advance3) {
        text_clear();
        text_append_space();
        text_append_lparen();
        text_append_label(0x7b);
        text_append_space();
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
        iVar1 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_154 = local_154 + iVar1 + 2;
        text_clear();
        text_append_string_id(advances[advance3].name);
        local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_160 = font_line_spacing(local_c);
        SetRect(&local_140,local_154,local_158,local_130 + local_154 + 2,local_160 + local_158);
        pedia_add_link(this,advance3,local_154,local_158,0,local_140.left,local_140.top,
                           local_140.right,local_140.bottom);
        iVar1 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_154 = local_154 + iVar1 + 2;
        text_clear();
        text_append_rparen();
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
      }
      local_158 += local_24;
    }
  }
  local_8 = 0;
  local_154 = local_20;
  for (improvement = 1; improvement < 0x43; improvement++) {
    if (improvements[improvement].preq == advance) {
      sprite_draw
                ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)local_19c,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),
                 local_154,local_158);
      iVar1 = sprite_get_width((Sprite *)(&improvement_icon_sprites + improvement * 0x3c))
      ;
      local_154 = local_154 + iVar1 + 5;
      text_clear();
      text_append_string_id(improvements[improvement].name);
      local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_160 = font_line_spacing(local_c);
      if ((local_8 == 0) &&
         (iVar1 = rect_width((iptr)&this->content_left),
         iVar1 / 2 <= (int)(local_130 + local_154 + 5))) {
        iVar1 = rect_width((iptr)&this->content_left);
        local_130 = (iVar1 / 2 - 5) - local_154;
      }
      SetRect(&local_140,local_154,local_158,local_130 + local_154 + 5,local_160 + local_158);
      if (improvement < 0x27) {
        pedia_add_link(this,improvement,local_154,local_158,1,local_140.left,local_140.top,
                           local_140.right,local_140.bottom);
      }
      else {
        pedia_add_link(this,improvement,local_154,local_158,2,local_140.left,local_140.top,
                           local_140.right,local_140.bottom);
      }
      bVar5 = local_8 != 0;
      if (bVar5) {
        local_158 += local_24;
        local_154 = local_20;
      }
      else {
        iVar1 = rect_width((iptr)&this->content_left);
        local_154 = iVar1 / 2;
      }
      local_8 = (uint)!bVar5;
    }
  }
  local_154 = local_20;
  if (local_8 == 1) {
    local_158 += local_24;
  }
  local_8 = 0;
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if (unit_types[unit_type].prerequisite == advance) {
      if (local_12c < 0xb) {
        iVar1 = sprite_height
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        iVar4 = local_158 + iVar1 / 2;
        iVar1 = sprite_get_height
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        sprite_draw
                  ((Sprite *)(&unit_sprites + unit_type * 0x3c),(iptr)local_1ac,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),
                   local_154,iVar4 - iVar1 / 2);
        iVar1 = sprite_width
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        local_154 = local_154 + iVar1 + 5;
        iVar1 = sprite_height
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        iVar4 = font_line_spacing(local_c);
        local_148 = (iVar1 / 2 - iVar4 / 2) + local_158;
      }
      else {
        local_148 = local_158;
      }
      text_clear();
      iVar2 = label_string(unit_types[unit_type].name);
      text_append(iVar2);
      local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_160 = font_line_spacing(local_c);
      SetRect(&local_140,local_154,local_148,local_130 + local_154 + 5,local_160 + local_148);
      pedia_add_link(this,unit_type,local_154,local_148,3,local_140.left,local_140.top,
                         local_140.right,local_140.bottom);
      if (local_8 == 0) {
        iVar1 = rect_width((iptr)&this->content_left);
        local_154 = iVar1 / 2;
        local_8 = 1;
        local_170 = sprite_get_height
                              ((Sprite *)(&unit_sprites + unit_type * 0x3c));
      }
      else {
        local_154 = local_20;
        local_8 = 0;
        if (local_12c < 0xb) {
          iVar1 = sprite_get_height
                            ((Sprite *)(&unit_sprites + unit_type * 0x3c));
          if (iVar1 < local_170) {
            local_158 += local_170;
          }
          else {
            iVar1 = sprite_get_height
                              ((Sprite *)(&unit_sprites + unit_type * 0x3c));
            local_158 += iVar1;
          }
        }
        else {
          local_158 += local_24;
        }
      }
    }
  }
  local_154 = local_20;
  if (local_8 == 1) {
    iVar1 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
    if (iVar1 < local_170) {
      local_158 += local_170;
    }
    else {
      iVar1 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c))
      ;
      local_158 += iVar1;
    }
  }
  local_168 = s_PEDIA_00633d74;
  iVar1 = _strcmp(&scenario_dir_path,&game_home_dir);
  if (iVar1 != 0) {
    __chdir(&scenario_dir_path);
    crt_strcpy(&local_128,s_describe__00633d7c);
    crt_strcat(&local_128,&lang_file_ext);
    iVar1 = file_exists((iptr)&local_128);
    if (iVar1 == 0) {
      ctrl_disable((Control *)(this[2].pad_5c0 + 0x10));
      __chdir(&game_home_dir);
      return;
    }
    __chdir(&game_home_dir);
  }
  local_144 = _strcmp(&scenario_dir_path,&game_home_dir);
  if (local_144 != 0) {
    __chdir(&scenario_dir_path);
    crt_strcpy(&local_128,s_pedia__00633d88);
    crt_strcat(&local_128,&lang_file_ext);
    iVar1 = file_exists((iptr)&local_128);
    if (iVar1 == 0) {
      local_144 = 0;
    }
    __chdir(&game_home_dir);
  }
  str_clear((iptr)&local_128);
  iVar1 = text_open_section((iptr)local_168,ADDR(0x633d90, ((u8 *)&g.d_00633d90)));
  if (iVar1 == 0) {
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) &&
       ((((advance == 0x36 || (advance == 0xf)) || (advance == 0x1f)) ||
        ((advance == 0x47 || (advance == 0x15)))))) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x12)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x42)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x43)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x46)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x38)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x18)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x59)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x3b)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x20)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0x3c)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    if ((local_144 == 0) && (advance == 0xf)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)local_c,(iptr)(local_150 + (*local_150 == '^')),
                 local_154,local_158,5);
      local_158 += local_24;
    }
    local_150 = (char *)text_read_line(1);
    str_append_space((iptr)local_150);
    crt_strcpy(&local_128,local_150);
    if (local_128 == '^') {
      sVar3 = _strlen(local_127);
      crt_memmove(&local_128,local_127,sVar3);
    }
    for (local_17c = 0; local_17c < 0x1c; local_17c++) {
      if (wonder_expires[local_17c] == advance) {
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_c,(iptr)&local_128,local_154,local_158,5);
        iVar1 = font_text_width(local_c,(iptr)&local_128);
        local_154 += iVar1;
        text_clear();
        text_append_string_id(improvements[local_17c + 0x27].name);
        local_130 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_160 = font_line_spacing(local_c);
        SetRect(&local_140,local_154,local_158,local_130 + local_154,local_160 + local_158);
        pedia_add_link(this,local_17c + 0x27,local_154,local_158,2,local_140.left,local_140.top,
                           local_140.right,local_140.bottom);
        iVar1 = font_text_width(local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_154 = local_154 + iVar1 + 2;
        text_clear();
        text_append_period();
        surface_draw_text
                  ((DibSurface *)this,(iptr)local_c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_154,local_158,5);
        local_154 = local_20;
        local_158 += local_24;
      }
    }
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)local_1c);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef local_1ac
#undef local_19c
#undef local_18c
#undef local_17c
#undef local_178
#undef advance3
#undef local_170
#undef advance
#undef local_168
#undef improvement
#undef local_160
#undef unit_type
#undef local_158
#undef local_154
#undef local_150
#undef advance2
#undef local_148
#undef local_144
#undef local_140
#undef local_130
#undef local_12c
#undef local_128
#undef local_127
#undef local_24
#undef local_20
#undef local_1c
#undef local_c
#undef local_8

/* 00566584 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_advance_names (*(i32 *)((u8 *)&g.d_006a7d44))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_topic_modal(DocumentWindow *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    local_8 = 0;
    while (((int)local_8 < (int)this->pedia_advance_count &&
           (*(int *)(this->pad_65c + local_8 * 4 + 400) != param_1))) {
      local_8++;
    }
    if (this->pedia_advance_count != local_8) {
      pedia_open_category((MediaWindow *)this,1,0);
      this->resize_border = local_8;
      *(u32 *)(this[3].pad_48 + 0x78) = local_8;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      uVar1 = pedia_lookup_text(pedia_advance_names,local_8);
      crt_strcpy(this->pad_608 + 0x10,uVar1);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_advance_page(this);
      window_show((WindowObjectView *)this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_advance_names
#undef pedia_closed
#undef local_8

/* 005666da auto */
#define local_154 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_150 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_148 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_138 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_128 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_118 (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_104 (*(int *)(frame_ + FRAME_OFF(84)))
#define aiStack_100 (*(int (*)[8])(frame_ + FRAME_OFF(88)))
#define local_e0 (*(Sprite * *)(frame_ + FRAME_OFF(120)))
#define aiStack_dc (*(int (*)[8])(frame_ + FRAME_OFF(124)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(156)))
#define local_b8 (*(iptr *)(frame_ + FRAME_OFF(160)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(164)))
#define local_b0 (*(iptr *)(frame_ + FRAME_OFF(168)))
#define aiStack_ac (*(int (*)[8])(frame_ + FRAME_OFF(172)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(204)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(208)))
#define aiStack_84 (*(int (*)[4])(frame_ + FRAME_OFF(212)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(228)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(232)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(252)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(256)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(260)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(264)))
#define local_4c (*(int (*)[3])(frame_ + FRAME_OFF(268)))
#define local_40 (*(tagRECT *)(frame_ + FRAME_OFF(280)))
#define aiStack_30 (*(int (*)[4])(frame_ + FRAME_OFF(296)))
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(312)))
#define local_10 (*(GameFont * *)(frame_ + FRAME_OFF(328)))
#define local_c (*(int (*)[2])(frame_ + FRAME_OFF(332)))
void __thiscall pedia_draw_advance_tree(DocumentWindow *this)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(344)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)local_20);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_clear_links((WindowObjectView *)this);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  local_10 = (GameFont *)&font_size21;
  advance = *(iptr *)(this->pad_65c + this->resize_border * 4 + 400);
  text_clear();
  text_append_string_id(advances[advance].name);
  local_4c[2] = font_text_width(local_10,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_104 = font_line_spacing(local_10);
  local_e0 = (Sprite *)
             (&advance_category_icon_sprites +
             (char)advances[advance].category * 0xf0 + (char)advances[advance].epoch * 0x3c);
  local_88 = sprite_get_width(local_e0);
  local_88 += 3;
  local_8c = (this->content_right - 3) - (local_88 + local_4c[2]);
  iVar1 = rect_height((iptr)&this->content_left);
  local_b4 = (this->content_top + iVar1 / 2) - local_104 / 2;
  piVar2 = (int *)sprite_draw(local_e0,(iptr)local_118,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_8c,local_b4);
  local_5c = *piVar2;
  local_58 = piVar2[1];
  local_54 = piVar2[2];
  local_50 = piVar2[3];
  local_8c += local_88;
  SetRect(&local_40,local_8c - local_88,local_b4,local_4c[2] + local_8c + 5,local_104 + local_b4);
  pedia_add_link(this,advance,local_8c,local_b4,0,local_40.left,local_40.top,local_40.right,
                     local_40.bottom);
  local_c[0] = (int)advances[advance].preq[0];
  local_c[1] = (int)advances[advance].preq[1];
  local_4c[1] = local_5c;
  local_4c[0] = local_5c;
  iVar1 = rect_height((iptr)(aiStack_84 + 10));
  local_74 = local_58 + iVar1 / 2;
  local_70 = local_74;
  local_104 = font_line_spacing(local_10);
  iVar1 = rect_height((iptr)&this->content_left);
  local_b4 = (this->content_top + ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2)) - local_104 / 2;
  for (local_b0 = 0; local_b0 < 2; local_b0++) {
    aiStack_30[local_b0 * 2] = -1;
    aiStack_30[local_b0 * 2 + 1] = -1;
    if (-1 < local_c[local_b0]) {
      text_clear();
      text_append_string_id(advances[local_c[local_b0]].name);
      local_4c[2] = font_text_width(local_10,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_e0 = (Sprite *)
                 (&advance_category_icon_sprites +
                 (char)advances[local_c[local_b0]].category * 0xf0 +
                 (char)advances[local_c[local_b0]].epoch * 0x3c);
      local_88 = sprite_get_width(local_e0);
      local_88 += 3;
      iVar1 = rect_width((iptr)&this->content_left);
      iVar3 = rect_width((iptr)&this->content_left);
      local_8c = ((int)(iVar1 * 2 + (iVar1 * 2 >> 0x1f & 3U)) >> 2) +
                 ((int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3) + this->content_left;
      piVar2 = (int *)sprite_draw
                                (local_e0,(iptr)local_128,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_8c,local_b4);
      local_5c = *piVar2;
      local_58 = piVar2[1];
      local_54 = piVar2[2];
      local_14c = piVar2[3];
      local_50 = local_14c;
      if (local_b0 != 0) {
        local_14c = piVar2[1] - 1;
      }
      iVar1 = aiStack_84[local_b0 + 4];
      iVar3 = local_4c[local_b0];
      iVar4 = rect_width((iptr)(aiStack_84 + 10));
      pedia_draw_tree_connector
                ((DibSurface *)this,local_5c + iVar4 / 2,local_14c,iVar3,iVar1);
      local_8c += local_88;
      aiStack_30[local_b0 * 2] = (int)advances[local_c[local_b0]].preq[0];
      aiStack_30[local_b0 * 2 + 1] = (int)advances[local_c[local_b0]].preq[1];
      aiStack_84[local_b0 * 2 + 7] = local_5c;
      aiStack_84[local_b0 * 2 + 6] = aiStack_84[local_b0 * 2 + 7];
      iVar1 = rect_height((iptr)(aiStack_84 + 10));
      aiStack_84[local_b0 * 2 + 1] = local_58 + iVar1 / 2;
      aiStack_84[local_b0 * 2] = aiStack_84[local_b0 * 2 + 1];
      SetRect(&local_40,local_8c - local_88,local_b4,local_4c[2] + local_8c + 5,local_104 + local_b4
             );
      pedia_add_link(this,local_c[local_b0],local_8c,local_b4,0,local_40.left,local_40.top,
                         local_40.right,local_40.bottom);
    }
    iVar1 = rect_height((iptr)&this->content_left);
    local_b4 += iVar1 / 2;
  }
  local_104 = font_line_spacing(local_10);
  iVar1 = rect_height((iptr)&this->content_left);
  local_b4 = (this->content_top + ((int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3)) - local_104 / 2;
  for (local_b0 = 0; local_b0 < 2; local_b0++) {
    for (local_b8 = 0; local_b8 < 2; local_b8++) {
      aiStack_ac[(local_b0 * 2 + local_b8) * 2] = -1;
      aiStack_ac[(local_b0 * 2 + local_b8) * 2 + 1] = -1;
      if (-1 < aiStack_30[local_b0 * 2 + local_b8]) {
        text_clear();
        text_append_string_id(advances[aiStack_30[local_b0 * 2 + local_b8]].name);
        local_4c[2] = font_text_width(local_10,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_e0 = (Sprite *)
                   (&advance_category_icon_sprites +
                   (char)advances[aiStack_30[local_b0 * 2 + local_b8]].epoch * 0x3c +
                   (char)advances[aiStack_30[local_b0 * 2 + local_b8]].category * 0xf0);
        local_88 = sprite_get_width(local_e0);
        local_88 += 3;
        iVar1 = rect_width((iptr)&this->content_left);
        iVar3 = rect_width((iptr)&this->content_left);
        local_8c = ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) +
                   ((int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3) + this->content_left;
        piVar2 = (int *)sprite_draw
                                  (local_e0,(iptr)local_138,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_8c,local_b4);
        local_5c = *piVar2;
        local_58 = piVar2[1];
        local_54 = piVar2[2];
        local_150 = piVar2[3];
        local_50 = local_150;
        if (local_b8 != 0) {
          local_150 = piVar2[1] - 1;
        }
        iVar1 = aiStack_84[local_b0 * 2 + local_b8];
        iVar3 = aiStack_84[local_b0 * 2 + local_b8 + 6];
        iVar4 = rect_width((iptr)(aiStack_84 + 10));
        pedia_draw_tree_connector
                  ((DibSurface *)this,local_5c + iVar4 / 2,local_150,iVar3,iVar1);
        local_8c += local_88;
        aiStack_ac[(local_b0 * 2 + local_b8) * 2] =
             (int)advances[aiStack_30[local_b0 * 2 + local_b8]].preq[0];
        aiStack_ac[(local_b0 * 2 + local_b8) * 2 + 1] =
             (int)advances[aiStack_30[local_b0 * 2 + local_b8]].preq[1];
        aiStack_dc[(local_b0 * 2 + local_b8) * 2 + 1] = local_5c;
        aiStack_dc[(local_b0 * 2 + local_b8) * 2] = aiStack_dc[(local_b0 * 2 + local_b8) * 2 + 1];
        iVar1 = rect_height((iptr)(aiStack_84 + 10));
        aiStack_100[(local_b0 * 2 + local_b8) * 2 + 1] = local_58 + iVar1 / 2;
        aiStack_100[(local_b0 * 2 + local_b8) * 2] = aiStack_100[(local_b0 * 2 + local_b8) * 2 + 1];
        SetRect(&local_40,local_8c - local_88,local_b4,local_4c[2] + local_8c + 5,
                local_104 + local_b4);
        pedia_add_link(this,aiStack_30[local_b0 * 2 + local_b8],local_8c,local_b4,0,
                           local_40.left,local_40.top,local_40.right,local_40.bottom);
      }
      iVar1 = rect_height((iptr)&this->content_left);
      local_b4 += ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2);
    }
  }
  iVar1 = rect_height((iptr)&this->content_left);
  local_bc = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
  local_104 = font_line_spacing(local_10);
  local_8c = this->content_left + 2;
  for (local_b0 = 0; local_b0 < 4; local_b0++) {
    for (local_b8 = 0; local_b8 < 2; local_b8++) {
      local_b4 = ((local_b0 * 2 + local_b8) * local_bc + this->content_top + local_bc / 2) -
                 local_104 / 2;
      if (-1 < aiStack_ac[local_b0 * 2 + local_b8]) {
        text_clear();
        text_append_string_id(advances[aiStack_ac[local_b0 * 2 + local_b8]].name);
        local_4c[2] = font_text_width(local_10,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_e0 = (Sprite *)
                   (&advance_category_icon_sprites +
                   (char)advances[aiStack_ac[local_b0 * 2 + local_b8]].category * 0xf0 +
                   (char)advances[aiStack_ac[local_b0 * 2 + local_b8]].epoch * 0x3c);
        local_88 = sprite_get_width(local_e0);
        local_88 += 3;
        piVar2 = (int *)sprite_draw
                                  (local_e0,(iptr)local_148,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_8c,local_b4);
        local_5c = *piVar2;
        local_58 = piVar2[1];
        local_54 = piVar2[2];
        local_154 = piVar2[3];
        local_50 = local_154;
        if (local_b8 != 0) {
          local_154 = piVar2[1] - 1;
        }
        iVar1 = aiStack_100[local_b0 * 2 + local_b8];
        iVar3 = aiStack_dc[local_b0 * 2 + local_b8];
        iVar4 = rect_width((iptr)(aiStack_84 + 10));
        pedia_draw_tree_connector
                  ((DibSurface *)this,local_5c + iVar4 / 2,local_154,iVar3,iVar1);
        if ((-1 < advances[aiStack_ac[local_b0 * 2 + local_b8]].preq[0]) ||
           (-1 < advances[aiStack_ac[local_b0 * 2 + local_b8]].preq[1])) {
          iVar1 = rect_height((iptr)(aiStack_84 + 10));
          pedia_draw_tree_stub((MediaWindow *)this,local_5c,local_58 + iVar1 / 2);
        }
        SetRect(&local_40,local_8c,local_b4,local_88 + local_4c[2] + local_8c + 5,
                local_104 + local_b4);
        pedia_add_link(this,aiStack_ac[local_b0 * 2 + local_b8],local_88 + local_8c,local_b4,0,
                           local_40.left,local_40.top,local_40.right,local_40.bottom);
      }
      iVar1 = rect_height((iptr)&this->content_left);
      local_b4 += ((int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3);
    }
  }
  surface_set_clip((DibSurface *)this,(iptr)local_20);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef local_154
#undef local_150
#undef local_14c
#undef local_148
#undef local_138
#undef local_128
#undef local_118
#undef advance
#undef local_104
#undef aiStack_100
#undef local_e0
#undef aiStack_dc
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef aiStack_ac
#undef local_8c
#undef local_88
#undef aiStack_84
#undef local_74
#undef local_70
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_40
#undef aiStack_30
#undef local_20
#undef local_10
#undef local_c

/* 005674b9 auto */
void __thiscall
pedia_draw_tree_connector(DibSurface *this,int param_1,int param_2,int param_3,int param_4)

{
  if (param_4 < param_2) {
    param_2++;
  }
  else {
    param_2--;
  }
  gfx_set_text_color_index(10);
  surface_draw_line(this,param_1 - 1,param_2,param_1 - 1,param_4);
  surface_draw_line(this,param_1 + 1,param_2,param_1 + 1,param_4);
  gfx_set_text_color_index(0x7a);
  surface_draw_line(this,param_1,param_2,param_1,param_4);
  if (param_1 < param_3) {
    gfx_set_text_color_index(10);
    surface_draw_line(this,param_1 + 1,param_4 - 1,param_3,param_4 - 1);
    surface_draw_line(this,param_1 + 1,param_4 + 1,param_3,param_4 + 1);
    gfx_set_text_color_index(0x7a);
    surface_draw_line(this,param_1 + 1,param_4,param_3,param_4);
  }
  return;
}

/* 005675b7 auto */
void __thiscall pedia_draw_tree_stub(MediaWindow *this,i32 param_1,int param_2)

{
  gfx_set_text_color_index(10);
  surface_draw_line
            ((DibSurface *)this,param_1,param_2 - 1,this->content_left,param_2 - 1);
  surface_draw_line((DibSurface *)this,param_1,param_2 + 1,this->content_left,param_2 + 1)
  ;
  gfx_set_text_color_index(0x7a);
  surface_draw_line((DibSurface *)this,param_1,param_2,this->content_left,param_2);
  return;
}

/* 005680a0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl shared_palette_global_init(void)

{
  shared_palette_static_init();
  shared_palette_reg_atexit();
  return;
}

/* 005680ba auto */
void __cdecl shared_palette_static_init(void)

{
  palette_init((GamePalette *)&art_palette);
  return;
}

/* 005680d4 auto */
void __cdecl shared_palette_reg_atexit(void)

{
  _atexit(shared_palette_static_dtor);
  return;
}

/* 005680f1 auto */
void __cdecl shared_palette_static_dtor(void)

{
  palette_destroy((GamePalette *)&art_palette);
  return;
}

/* 00599a20 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_improvement_list(DocumentWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this->pedia_improve_count <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)(this[2].pad_65c + 0x88) = this->pedia_improve_count;
  *(u32 *)(this[3].pad_48 + 0x78) = this->resize_border;
  *(u32 *)(this[3].pad_48 + 0x7c) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[3].pad_48 + 0x7c) = *(int *)(this[3].pad_48 + 0x7c) - 1;
  }
  for (local_8 = 0; local_8 < (int)this->pedia_improve_count; local_8++) {
    *(i32 *)(this[2].pad_65c + local_8 * 4 + 0x8c) =
         *(i32 *)(this->pad_980 + local_8 * 4 + 0x9c);
  }
  scrollbar_set_range
            ((Control *)(this[2].pad_65c + 0x34),0,*(int *)(this[2].pad_65c + 0x88) / 9);
  scrollbar_set_pos
            ((ClickControl *)(this[2].pad_65c + 0x34),*(int *)(this[3].pad_48 + 0x7c) / 9);
  if (*(int *)(this[2].pad_65c + 0x88) < 1) {
    this[3].pad_48[0x7c] = 0xff;
    this[3].pad_48[0x7d] = 0xff;
    this[3].pad_48[0x7e] = 0xff;
    this[3].pad_48[0x7f] = 0xff;
  }
  pedia_update_controls((MediaWindow *)this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 00599b8d auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_98 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_88 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_78 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_64 (*(tagRECT *)(frame_ + FRAME_OFF(52)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_4c (*(i32 *)(frame_ + FRAME_OFF(76)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_44 (*(i32 *)(frame_ + FRAME_OFF(84)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_34 (*(i32 *)(frame_ + FRAME_OFF(100)))
#define local_30 (*(tagRECT *)(frame_ + FRAME_OFF(104)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(124)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(144)))
/* WARNING: Removing unreachable block (ram,0x00599e9a) */
/* WARNING: Removing unreachable block (ram,0x00599fc4) */

void __thiscall pedia_draw_improvement_page(DocumentWindow *this)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  u32 yBottom;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 0;
  surface_get_clip((DibSurface *)this,(iptr)local_18);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  local_8 = (GameFont *)&font_size21;
  local_40 = this->content_left + 10;
  local_3c = rect_width((iptr)&this->content_left);
  local_1c = font_cached_height(local_8);
  local_48 = this->content_top + 8;
  local_38 = local_3c / 2 - 100;
  improvement = *(iptr *)(this->pad_980 + this->resize_border * 4 + 0x9c);
  gfx_get_scale_ratio((iptr)&local_4c,(iptr)&local_44);
  gfx_set_scale_ratio(2,1);
  local_50 = sprite_get_width((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  local_50 += panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)local_78,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_40,
             local_48);
  gfx_set_scale_ratio(local_4c,local_44);
  gfx_set_text_color_index(list_text_color);
  local_40 = this->content_left + 10;
  iVar1 = sprite_height((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  local_48 = local_48 + iVar1 * 2 + 5;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_40 = local_40 + iVar1 + 5;
  text_clear();
  if (improvements[improvement].preq < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  }
  else {
    text_append_string_id(advances[improvements[improvement].preq].name);
    local_20 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_54 = font_line_spacing(local_8);
    SetRect(&local_30,local_40,local_48,local_40 + local_20 + 5,local_48 + local_54);
    pedia_add_link(this,(int)improvements[improvement].preq,local_40,local_48,0,local_30.left,
                       local_30.top,local_30.right,local_30.bottom);
  }
  local_38 = local_40;
  local_40 = this->content_left + 10;
  local_48 += local_1c;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_improve_cost_fmt,(uint)improvements[improvement].cost * 10);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_48,5);
  iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_40 = local_38 + iVar1 + 3;
  iVar3 = local_48 + local_1c / 2;
  iVar1 = sprite_get_height((Sprite *)&shield_icon_sprite);
  sprite_draw
            ((Sprite *)&shield_icon_sprite,(iptr)local_88,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_40,iVar3 - iVar1 / 2);
  local_40 = this->content_left + 10;
  local_48 += local_1c;
  text_clear();
  text_append_label(0x9e);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_improve_upkeep_fmt,(uint)improvements[improvement].upkeep);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_48,5);
  iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_40 = local_38 + iVar1 + 3;
  iVar3 = local_48 + local_1c / 2;
  iVar1 = sprite_get_height((Sprite *)&gold_coin_icon_sprite);
  sprite_draw
            ((Sprite *)&gold_coin_icon_sprite,(iptr)local_98,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_40,iVar3 - iVar1 / 2);
  local_40 = this->content_left + 10;
  local_48 += local_1c * 2;
  pedia_load_improvement_text((WindowObjectView *)this,improvement);
  sVar2 = _strlen(&text_buffer);
  if (sVar2 != 0) {
    yBottom = this->content_bottom;
    iVar1 = rect_width((iptr)&this->content_left);
    SetRect(&local_64,local_40,local_48,iVar1 - 10 + local_40,yBottom);
    surface_draw_text_rect((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&local_64,5);
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)local_18);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef text_buffer
#undef local_98
#undef local_88
#undef local_78
#undef improvement
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
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 0059a15d auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_1124 (*(char (*)[4096])(frame_ + FRAME_OFF(4)))
#define local_124 (*(i8 (*)[256])(frame_ + FRAME_OFF(4100)))
#define local_24 (*(i8 (*)[8])(frame_ + FRAME_OFF(4356)))
void __thiscall pedia_load_improvement_text(WindowObjectView *this,iptr param_1)

{
  int iVar1;
  char *_Str;
  size_t sVar2;
  i32 uStackY_1c;
  i8 frame_[FRAME_OFF(4392)] __attribute__((aligned(8)));  /* original stack frame */
  str_clear((iptr)local_1124);
  uStackY_1c = 0x59a190;
  crt_strcpy(local_24,s_PEDIAIMPROVE_00635074);
  uStackY_1c = 0x59a1a0;
  str_append_int((iptr)local_24,param_1);
  uStackY_1c = 0x59a1b1;
  iVar1 = text_open_section(ADDR(0x635084, ((u8 *)&g.d_00635084)),(iptr)local_24);
  if (iVar1 == 0) {
    text_clear();
    while (_Str = (char *)text_read_line(1), *_Str != '@') {
      if ((*_Str != ';') && (sVar2 = _strlen(_Str), sVar2 != 0)) {
        while ((*_Str == '^' || (*_Str == '*'))) {
          uStackY_1c = 0x59a253;
          crt_strcpy(local_124,_Str + 1);
          uStackY_1c = 0x59a269;
          crt_strcpy(_Str,local_124);
        }
        str_trim((iptr)_Str);
        sVar2 = _strlen(local_1124);
        if (sVar2 != 0) {
          uStackY_1c = 0x59a2a8;
          crt_strcat(local_1124,&pedia_improve_text_space_str);
        }
        uStackY_1c = 0x59a2be;
        crt_strcat(local_1124,_Str);
      }
    }
  }
  uStackY_1c = 0x59a2d7;
  crt_strcpy(&text_buffer,local_1124);
  return;
}
#undef text_buffer
#undef local_1124
#undef local_124
#undef local_24

/* 0059a2e6 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_improvement_names (*(i32 *)((u8 *)&g.d_006a7d48))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_improvement_modal(DocumentWindow *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    if (param_1 < 0x27) {
      local_8 = 0;
      while (((int)local_8 < (int)this->pedia_improve_count &&
             (*(int *)(this->pad_980 + local_8 * 4 + 0x9c) != param_1))) {
        local_8++;
      }
      if (this->pedia_improve_count != local_8) {
        pedia_open_category((MediaWindow *)this,2,0);
        this->resize_border = local_8;
        *(u32 *)(this[3].pad_48 + 0x78) = local_8;
        this->client_x = 1;
        this->border_width = 1;
        pedia_clear_links((WindowObjectView *)this);
        pedia_update_controls((MediaWindow *)this);
        uVar1 = pedia_lookup_text(pedia_improvement_names,local_8);
        crt_strcpy(this->pad_608 + 0x10,uVar1);
        pedia_draw_frame((MediaWindow *)this);
        pedia_draw_improvement_page(this);
        window_show((WindowObjectView *)this);
        wnd_blit_surface((DibSurface *)&pedia_window);
        wnd_activate((Wnd *)&pedia_window_wnd);
        wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
        wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
        wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
      }
    }
    else {
      pedia_show_wonder_modal(this,param_1);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_closed
#undef pedia_improvement_names
#undef local_8

/* 005ac840 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_unit_list(MediaWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || (*(int *)(this[1].pad_4a4 + 0xdc) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(i32 *)this[4].pad_2c4 = *(i32 *)(this[1].pad_4a4 + 0xdc);
  *(u32 *)(this[5].pad_48 + 100) = this->resize_border;
  *(u32 *)(this[5].pad_48 + 0x68) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(this[5].pad_48 + 0x68) = *(int *)(this[5].pad_48 + 0x68) - 1;
  }
  for (local_8 = 0; local_8 < *(int *)(this[1].pad_4a4 + 0xdc); local_8++) {
    *(i32 *)(this[4].pad_2c4 + local_8 * 4 + 4) =
         *(i32 *)(this[2].pad_48 + local_8 * 4 + 0x18);
  }
  scrollbar_set_range
            ((Control *)&this[4].field_270,0,*(int *)this[4].pad_2c4 / 9);
  scrollbar_set_pos
            ((ClickControl *)&this[4].field_270,*(int *)(this[5].pad_48 + 0x68) / 9);
  if (*(int *)this[4].pad_2c4 < 1) {
    this[5].pad_48[0x68] = 0xff;
    this[5].pad_48[0x69] = 0xff;
    this[5].pad_48[0x6a] = 0xff;
    this[5].pad_48[0x6b] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef local_8

/* 005ac9ad auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_498 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_488 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_478 (*(tagRECT *)(frame_ + FRAME_OFF(32)))
#define local_468 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_464 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_460 (*(tagRECT *)(frame_ + FRAME_OFF(56)))
#define local_450 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_44c (*(int *)(frame_ + FRAME_OFF(76)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_444 (*(char * *)(frame_ + FRAME_OFF(84)))
#define local_440 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_43c (*(i32 *)(frame_ + FRAME_OFF(92)))
#define local_438 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_434 (*(char (*)[1000])(frame_ + FRAME_OFF(100)))
#define local_4c (*(i32 *)(frame_ + FRAME_OFF(1100)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(1104)))
#define local_44 (*(u32 *)(frame_ + FRAME_OFF(1108)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(1112)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(1116)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(1120)))
#define local_34 (*(i32 *)(frame_ + FRAME_OFF(1124)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(1128)))
#define local_2c (*(i32 *)(frame_ + FRAME_OFF(1132)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(1136)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(1140)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(1144)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(1148)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(1152)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(1168)))
void __thiscall pedia_draw_unit_page(DocumentWindow *this)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  u32 yBottom;
  i8 frame_[FRAME_OFF(1176)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)local_18);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  local_8 = (GameFont *)&font_size21;
  local_44 = this->content_left;
  local_30 = 10;
  local_40 = rect_width((iptr)&this->content_left);
  local_440 = local_40 / 2;
  local_1c = rect_height((iptr)&this->content_left);
  local_1c = local_1c / 0xc;
  local_44c = font_cached_height(local_8);
  local_48 = this->content_top + 0xf;
  unit_type = *(iptr *)(this[1].pad_274 + this->resize_border * 4 - 4);
  local_44 += local_30;
  gfx_get_scale_ratio((iptr)&local_20,(iptr)&local_24);
  gfx_set_scale_ratio(2,1);
  local_438 = sprite_get_width((Sprite *)(&unit_sprites + unit_type * 0x3c))
  ;
  local_438 += panel_margin_x * 2;
  iVar3 = local_48 + local_1c / 2;
  iVar1 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
  sprite_draw
            ((Sprite *)(&unit_sprites + unit_type * 0x3c),(iptr)local_488,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_44,
             iVar3 - iVar1 / 2);
  gfx_set_scale_ratio(local_20,local_24);
  local_2c = list_text_color;
  gfx_set_text_color_index(list_text_color);
  iVar1 = sprite_get_width((Sprite *)(&unit_sprites + unit_type * 0x3c));
  local_44 = local_44 + local_438 + iVar1 + 0x32;
  local_48 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
  local_48 = this->content_top + local_48;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_44 = local_44 + iVar1 + 5;
  text_clear();
  if (unit_types[unit_type].prerequisite < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  }
  else {
    text_append_string_id(advances[unit_types[unit_type].prerequisite].name);
    local_450 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_464 = font_line_spacing(local_8);
    SetRect(&local_460,local_44,local_48,local_450 + local_44 + 5,local_464 + local_48);
    pedia_add_link(this,(int)unit_types[unit_type].prerequisite,local_44,local_48,0,
                       local_460.left,local_460.top,local_460.right,local_460.bottom);
  }
  local_3c = local_440 - 0x4b;
  local_44 = this->content_left + local_30;
  iVar1 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
  local_48 = iVar1 * 2 + this->content_top + local_44c;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  text_clear();
  if ((char)unit_types[unit_type].cost < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
  }
  else {
    _sprintf(&text_buffer,&pedia_unit_cost_fmt,(char)unit_types[unit_type].cost * 10);
    surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
    iVar1 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    local_44 = local_3c + iVar1 + 5;
    iVar3 = local_48 + local_1c / 2;
    iVar1 = sprite_get_height((Sprite *)&shield_icon_sprite);
    sprite_draw
              ((Sprite *)&shield_icon_sprite,(iptr)local_498,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),local_44,
               (iVar3 - 2) - iVar1 / 2);
  }
  local_44 = this->content_left + local_30;
  local_48 += local_44c;
  text_clear();
  text_append_label(0x7f);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_attack_fmt,(int)(char)unit_types[unit_type].attack);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
  local_48 += local_44c;
  text_clear();
  text_append_label(0x80);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_defense_fmt,(int)(char)unit_types[unit_type].defense);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
  local_48 += local_44c;
  text_clear();
  text_append_label(0x82);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_hp_fmt,(int)(char)unit_types[unit_type].hit_points / 10);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
  local_48 += local_44c;
  text_clear();
  text_append_label(0x83);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_firepower_fmt,(int)(char)unit_types[unit_type].firepower);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
  local_48 += local_44c;
  text_clear();
  text_append_label(0x81);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_44,local_48,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_move_fmt,(int)(char)unit_types[unit_type].move / 3);
  surface_draw_text((DibSurface *)this,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_3c,local_48,5);
  local_444 = s_PEDIA_00635dac;
  text_clear();
  text_append_int(unit_type);
  local_43c = 0;
  local_34 = 0;
  local_28 = 7;
  local_4c = 0;
  iVar1 = text_open_section((iptr)local_444,ADDR(0x635db4, ((u8 *)&g.d_00635db4)));
  if (iVar1 == 0) {
    local_468 = 0;
    str_clear((iptr)local_434);
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 1) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 2) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 4) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 8) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x10) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x20) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x40) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x80) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x100) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x200) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x400) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x800) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x1000) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x2000) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    local_38 = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x4000) != 0) {
      if (local_468 == 0) {
        crt_strcpy(local_434,local_38 + 1);
        local_468 = 1;
      }
      else {
        crt_strcat(local_434,local_38 + 1);
      }
      str_append_space((iptr)local_434);
    }
    text_close_file();
    local_44 = this->content_left + local_440;
    iVar1 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
    local_48 = iVar1 * 2 + this->content_top + local_44c;
    sVar2 = _strlen(local_434);
    if (sVar2 != 0) {
      yBottom = this->content_bottom;
      iVar1 = rect_width((iptr)&this->content_left);
      SetRect(&local_478,local_44,local_48,local_44 + iVar1 / 2,yBottom);
      surface_draw_text_rect
                ((DibSurface *)this,(iptr)local_8,(iptr)local_434,(iptr)&local_478,5);
    }
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)local_18);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef text_buffer
#undef local_498
#undef local_488
#undef local_478
#undef local_468
#undef local_464
#undef local_460
#undef local_450
#undef local_44c
#undef unit_type
#undef local_444
#undef local_440
#undef local_43c
#undef local_438
#undef local_434
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
#undef local_8

/* 005ad998 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_unit_names (*(i32 *)((u8 *)&g.d_006a7d50))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_unit_modal(DocumentWindow *this,iptr param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    local_8 = 0;
    while (((int)local_8 < *(int *)(this[1].pad_15c + 0x18) &&
           (*(int *)(this[1].pad_274 + local_8 * 4 - 4) != param_1))) {
      local_8++;
    }
    if (*(u32 *)(this[1].pad_15c + 0x18) != local_8) {
      pedia_open_category((MediaWindow *)this,4,0);
      this->resize_border = local_8;
      *(u32 *)(this[3].pad_48 + 0x78) = local_8;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      uVar1 = pedia_lookup_text(pedia_unit_names,local_8);
      crt_strcpy(this->pad_608 + 0x10,uVar1);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_unit_page(this);
      window_show((WindowObjectView *)this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_closed
#undef pedia_unit_names
#undef local_8
