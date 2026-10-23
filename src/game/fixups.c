/*
 * Assorted window procedures and helpers whose machine translation did not
 * compile (struct values treated as scalars, wrong Win32 argument lists,
 * a switch on a handle).  Rewritten following the original machine code.
 */
#include "game.h"

/* ------------------------------------------------------------------------ */
/* 0x005c8791: unload a font resource: delete its cached GDI fonts, remove
 * the font file, then free the resource block. */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl font_file_unload(i32 param_1)
{
    char *font;
    i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */

    font = (char *)mem_handle_lock(param_1);
    for (local_c = 0; local_c < *(int *)(font + 0x100); local_c = local_c + 1) {
        if (*(int *)(font + local_c * 4 + 0x108) != 0) {
            DeleteObject(*(HGDIOBJ *)(font + local_c * 4 + 0x108));
            *(int *)(font + local_c * 4 + 0x108) = 0;
        }
    }
    RemoveFontResourceA(font);   /* file name at the start of the block */
    mem_handle_unlock(param_1);
    mem_handle_free(param_1);
}
#undef local_c

/* ------------------------------------------------------------------------ */
#define g_btn_hover     (*(int *)((u8 *)&g.d_00637c9c))
#define g_btn_pressed   (*(int *)((u8 *)&g.d_00637ca0))

/* 0x005c8caf: hover-tracking button window procedure. */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
i32 __stdcall hotspot_wndproc(HWND param_1,i32 param_2,i32 param_3,uint param_4)
{
    void *this;
    int iVar1;
    int *piVar2;
    BOOL BVar3;
    i32 uVar4;
    POINT pt;
    i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */

    iVar1 = wnd_from_hwnd(param_1);
    this = *(void **)(iVar1 + 4);
    switch (param_2) {
    case 0x200:     /* WM_MOUSEMOVE */
        pt.x = param_4 & 0xffff;
        pt.y = (param_4 >> 0x10) & 0xffff;
        if (g_btn_hover == 0) {
            if (g_btn_pressed == 0) {
                g_btn_hover = 1;
                SetCapture(param_1);
                if (this != (void *)0x0) {
                    uVar4 = ctrl_get_parent(this);
                    wnd_set_active_child(uVar4);
                    uVar4 = ctrl_get_id(this);
                    hotspot_fire_enter(this, uVar4);
                }
            }
        }
        else {
            piVar2 = (int *)ctrl_get_rect(this);
            local_14.left = piVar2[0];
            local_14.top = piVar2[1];
            local_14.right = piVar2[2];
            local_14.bottom = piVar2[3];
            OffsetRect(&local_14, -local_14.left, -local_14.top);
            BVar3 = PtInRect(&local_14, pt);
            if (BVar3 == 0) {
                g_btn_hover = 0;
                if (g_btn_pressed == 0) {
                    ReleaseCapture();
                    if (this != (void *)0x0) {
                        uVar4 = ctrl_get_parent(this);
                        wnd_set_active_child(uVar4);
                        uVar4 = ctrl_get_id(this);
                        hotspot_fire_leave(this, uVar4);
                    }
                }
            }
        }
        break;
    case 0x201:     /* WM_LBUTTONDOWN */
        if (g_btn_hover != 0) {
            g_btn_pressed = 1;
            uVar4 = ctrl_get_parent(this);
            wnd_set_active_child(uVar4);
            uVar4 = ctrl_get_id(this);
            hotspot_fire_press(this, uVar4);
        }
        break;
    case 0x202:     /* WM_LBUTTONUP */
        if (g_btn_pressed != 0) {
            g_btn_pressed = 0;
            if (g_btn_hover != 0) {
                if (this != (void *)0x0) {
                    uVar4 = ctrl_get_parent(this);
                    wnd_set_active_child(uVar4);
                    uVar4 = ctrl_get_id(this);
                    hotspot_fire_click(this, uVar4);
                }
            }
            else {
                ReleaseCapture();
                if (this != (void *)0x0) {
                    uVar4 = ctrl_get_parent(this);
                    wnd_set_active_child(uVar4);
                    uVar4 = ctrl_get_id(this);
                    hotspot_fire_leave(this, uVar4);
                }
            }
        }
        break;
    case 0x203:     /* WM_LBUTTONDBLCLK */
        if (g_btn_hover != 0) {
            uVar4 = ctrl_get_parent(this);
            wnd_set_active_child(uVar4);
            uVar4 = ctrl_get_id(this);
            hotspot_fire_dblclick(this, uVar4);
        }
        break;
    default:
        return ctrl_default_wndproc(param_1, param_2, param_3, param_4);
    }
    return 0;
}
#undef local_14

/* ------------------------------------------------------------------------ */
/* 0x005cacd4: bitmap push-button window procedure (normal / pressed /
 * disabled bitmaps, focus frame, space bar activation). */
#define local_84 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(4)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_40 (*(HDC *)(frame_ + FRAME_OFF(72)))
#define local_3c (*(HGDIOBJ *)(frame_ + FRAME_OFF(76)))
#define local_38 (*(tagRECT *)(frame_ + FRAME_OFF(80)))
#define local_28 (*(void * *)(frame_ + FRAME_OFF(96)))
#define local_24 (*(HDC *)(frame_ + FRAME_OFF(100)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(104)))
#define local_1c (*(HBRUSH *)(frame_ + FRAME_OFF(108)))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(112)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(128)))
i32 __stdcall button_wndproc(HWND param_1,uint param_2,WPARAM param_3,uint param_4)
{
    char cVar1;
    SHORT SVar2;
    int *piVar3;
    BOOL BVar4;
    HWND pHVar6;
    int iVar7;
    HGDIOBJ h;
    int cx;
    void *pvVar8;
    i32 uVar9;
    POINT pt;
    i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */

    local_44 = wnd_from_hwnd(param_1);
    if (local_44 == 0)
        return 0;
    local_28 = *(void **)(local_44 + 4);
    switch (param_2) {
    case 0x201:     /* WM_LBUTTONDOWN */
        iVar7 = ctrl_is_enabled(local_28);
        if (iVar7 == 0)
            break;
        *(i32 *)(local_44 + 0x1c) = 1;
        SetFocus(param_1);
        SetCapture(param_1);
        /* fall through */
    case 0x200:     /* WM_MOUSEMOVE */
        if (*(int *)(local_44 + 0x1c) != 0) {
            pt.x = param_4 & 0xffff;
            pt.y = (param_4 >> 0x10) & 0xffff;
            piVar3 = (int *)ctrl_get_rect(local_28);
            local_38.left = piVar3[0];
            local_38.top = piVar3[1];
            local_38.right = piVar3[2];
            local_38.bottom = piVar3[3];
            OffsetRect(&local_38, -local_38.left, -local_38.top);
            BVar4 = PtInRect(&local_38, pt);
            local_20 = (uint)(BVar4 != 0);
            if (*(uint *)(local_44 + 0x18) != local_20) {
                *(uint *)(local_44 + 0x18) = local_20;
                InvalidateRect(param_1, &local_38, 0);
            }
        }
        break;
    case 0x202:     /* WM_LBUTTONUP */
        if (*(int *)(local_44 + 0x1c) == 0)
            break;
        ReleaseCapture();
        *(i32 *)(local_44 + 0x1c) = 0;
        pt.x = param_4 & 0xffff;
        pt.y = (param_4 >> 0x10) & 0xffff;
        piVar3 = (int *)ctrl_get_rect(local_28);
        local_38.left = piVar3[0];
        local_38.top = piVar3[1];
        local_38.right = piVar3[2];
        local_38.bottom = piVar3[3];
        OffsetRect(&local_38, -local_38.left, -local_38.top);
        InvalidateRect(param_1, &local_38, 0);
        *(i32 *)(local_44 + 0x18) = 0;
        BVar4 = PtInRect(&local_38, pt);
        if (BVar4 != 0) {
            button_wndproc(param_1, 0xf, 0, 0);
            uVar9 = ctrl_get_parent(local_28);
            wnd_set_active_child(uVar9);
            uVar9 = ctrl_get_id(local_28);
            button_fire_callback(local_28, uVar9);
        }
        break;
    case 0xf:       /* WM_PAINT */
        local_40 = BeginPaint(param_1, &local_84);
        piVar3 = (int *)ctrl_get_rect(local_28);
        local_38.left = piVar3[0];
        local_38.top = piVar3[1];
        local_38.right = piVar3[2];
        local_38.bottom = piVar3[3];
        ValidateRect(GetParent(param_1), &local_38);
        iVar7 = ctrl_is_enabled(local_28);
        if (iVar7 == 0) {
            pHVar6 = GetFocus();
            if (pHVar6 == param_1) {
                pvVar8 = (void *)ctrl_get_parent(local_28);
                cVar1 = wnd_keyboard_nav_enabled(pvVar8);
                if (cVar1 == '\0') {
                    pvVar8 = (void *)ctrl_get_parent(local_28);
                    iVar7 = wnd_get_window(pvVar8);
                    SetFocus(*(HWND *)(iVar7 + 4));
                }
                else {
                    SetFocus((HWND)0x0);
                }
            }
            local_3c = *(HGDIOBJ *)(local_44 + 0x14);
        }
        else {
            if (*(int *)(local_44 + 0x18) == 0)
                local_3c = *(HGDIOBJ *)(local_44 + 0xc);
            if (*(int *)(local_44 + 0x18) == 1)
                local_3c = *(HGDIOBJ *)(local_44 + 0x10);
        }
        local_24 = CreateCompatibleDC(local_40);
        RealizePalette(local_24);
        h = SelectObject(local_24, local_3c);
        iVar7 = rect_height(&local_38);      /* height */
        cx = rect_width(&local_38);         /* width */
        BitBlt(local_40, 0, 0, cx, iVar7, local_24, 0, 0, 0xcc0020);
        SelectObject(local_24, h);
        DeleteDC(local_24);
        EndPaint(param_1, &local_84);
        if (GetFocus() == param_1)
            button_wndproc(param_1, 7, 0, 0);
        break;
    case 0x100:     /* WM_KEYDOWN */
        if (param_3 == 9) {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        else if (param_3 == 0x20 && (iVar7 = ctrl_is_enabled(local_28), iVar7 != 0) &&
                 (pvVar8 = (void *)ctrl_get_parent(local_28),
                  cVar1 = wnd_keyboard_nav_enabled(pvVar8), cVar1 != '\0')) {
            *(i32 *)(local_44 + 0x18) = 1;
            wnd_redraw_client(param_1);
            *(i32 *)(local_44 + 0x18) = 0;
            SVar2 = GetAsyncKeyState(0x20);
            local_8 = (int)SVar2;
            ui_pump_messages();
            while (*(i8 *)((char *)&local_8 + 1) != '\0') {
                SVar2 = GetAsyncKeyState(0x20);
                local_8 = (int)SVar2;
            }
            wnd_redraw_client(param_1);
            uVar9 = ctrl_get_parent(local_28);
            wnd_set_active_child(uVar9);
            uVar9 = ctrl_get_id(local_28);
            button_fire_callback(local_28, uVar9);
        }
        else {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        break;
    case 7:         /* WM_SETFOCUS: draw the focus frame */
        pvVar8 = (void *)ctrl_get_parent(local_28);
        cVar1 = wnd_keyboard_nav_enabled(pvVar8);
        if (cVar1 == '\0')
            return ctrl_default_wndproc(param_1, param_2, param_3, param_4);
        local_40 = GetDC(param_1);
        local_1c = GetStockObject(3);
        GetClientRect(param_1, &local_18);
        SelectObject(local_40, local_1c);
        FrameRect(local_40, &local_18, local_1c);
        SetRect(&local_18, local_18.left + 4, local_18.top + 4, local_18.right - 4,
                local_18.bottom - 4);
        FrameRect(local_40, &local_18, local_1c);
        DeleteObject(local_1c);
        ReleaseDC(param_1, local_40);
        break;
    case 8:         /* WM_KILLFOCUS */
        wnd_redraw_client(param_1);
        break;
    default:
        return ctrl_default_wndproc(param_1, param_2, param_3, param_4);
    }
    return 0;
}
#undef local_84
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* ------------------------------------------------------------------------ */
#define g_palette_mode  (*(int *)((u8 *)&g.d_00638b48))

/* 0x005cb6eb: sprite push-button window procedure (left and right click). */
#define local_64 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(HDC *)(frame_ + FRAME_OFF(68)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(72)))
#define local_10 (*(void * *)(frame_ + FRAME_OFF(88)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(92)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(96)))
i32 __stdcall spritebtn_wndproc(HWND param_1,uint param_2,WPARAM param_3,uint param_4)
{
    char cVar1;
    int iVar3;
    int *piVar4;
    HPALETTE hPal;
    int iVar6;
    int iVar7;
    void *pvVar8;
    i32 uVar9;
    HDC hdcSrc;
    BOOL BVar12;
    POINT pt;
    i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */

    iVar3 = wnd_from_hwnd(param_1);
    if (iVar3 == 0)
        return 1;
    local_10 = *(void **)(iVar3 + 4);
    switch (param_2) {
    case 0x201:     /* WM_LBUTTONDOWN */
        *(i32 *)(iVar3 + 0x1c) = 1;
        SetFocus(param_1);
        SetCapture(param_1);
        /* fall through */
    case 0x200:     /* WM_MOUSEMOVE */
        if (*(int *)(iVar3 + 0x1c) != 0) {
            pt.x = param_4 & 0xffff;
            pt.y = (param_4 >> 0x10) & 0xffff;
            piVar4 = (int *)ctrl_get_rect(local_10);
            local_20.left = piVar4[0];
            local_20.top = piVar4[1];
            local_20.right = piVar4[2];
            local_20.bottom = piVar4[3];
            OffsetRect(&local_20, -local_20.left, -local_20.top);
            BVar12 = PtInRect(&local_20, pt);
            local_c = (uint)(BVar12 != 0);
            if (*(uint *)(iVar3 + 0x18) != local_c) {
                *(uint *)(iVar3 + 0x18) = local_c;
                InvalidateRect(param_1, &local_20, 0);
            }
        }
        break;
    case 0x202:     /* WM_LBUTTONUP */
    case 0x205:     /* WM_RBUTTONUP */
        if (*(int *)(iVar3 + 0x1c) != 0) {
            ReleaseCapture();
            *(i32 *)(iVar3 + 0x1c) = 0;
            pt.x = param_4 & 0xffff;
            pt.y = (param_4 >> 0x10) & 0xffff;
            piVar4 = (int *)ctrl_get_rect(local_10);
            local_20.left = piVar4[0];
            local_20.top = piVar4[1];
            local_20.right = piVar4[2];
            local_20.bottom = piVar4[3];
            OffsetRect(&local_20, -local_20.left, -local_20.top);
            InvalidateRect(param_1, &local_20, 0);
            *(i32 *)(iVar3 + 0x18) = 0;
            BVar12 = PtInRect(&local_20, pt);
            if (BVar12 != 0) {
                spritebtn_wndproc(param_1, 0xf, 0, 0);
                uVar9 = ctrl_get_parent(local_10);
                wnd_set_active_child(uVar9);
                uVar9 = ctrl_get_id(local_10);
                if (param_2 == 0x202)
                    spritebtn_fire_click(local_10, uVar9);
                else
                    spritebtn_fire_rclick(local_10, uVar9);
            }
        }
        break;
    case 0x204:     /* WM_RBUTTONDOWN */
        *(i32 *)(iVar3 + 0x1c) = 1;
        SetFocus(param_1);
        SetCapture(param_1);
        break;
    case 0xf:       /* WM_PAINT */
        local_24 = BeginPaint(param_1, &local_64);
        piVar4 = (int *)ctrl_get_rect(local_10);
        local_20.left = piVar4[0];
        local_20.top = piVar4[1];
        local_20.right = piVar4[2];
        local_20.bottom = piVar4[3];
        ValidateRect(GetParent(param_1), &local_20);
        OffsetRect(&local_20, -local_20.left, -local_20.top);
        ValidateRect(param_1, &local_20);
        if (g_palette_mode == 1) {
            pvVar8 = (void *)ctrl_get_parent(local_10);
            pvVar8 = (void *)wnd_get_palette(pvVar8);
            hPal = (HPALETTE)palette_get_hpalette(pvVar8);
            SelectPalette(local_24, hPal, 0);
        }
        if (*(int *)(iVar3 + 0x18) == 0) {
            surface_lock((void *)((int)local_10 + 0x34));
            pvVar8 = (void *)ctrl_get_parent(local_10);
            uVar9 = wnd_get_palette(pvVar8);
            surface_apply_palette((void *)((int)local_10 + 0x34), (void *)uVar9);
            if (g_palette_mode == 1)
                RealizePalette(local_24);
            iVar6 = surface_get_dib((void *)((int)local_10 + 0x34));
            hdcSrc = *(HDC *)(iVar6 + 4);
            iVar6 = surface_height((void *)((int)local_10 + 0x34));
            iVar7 = surface_width((void *)((int)local_10 + 0x34));
            BitBlt(local_24, 0, 0, iVar7, iVar6, hdcSrc, 0, 0, 0xcc0020);
            surface_unlock((void *)((int)local_10 + 0x34));
        }
        if (*(int *)(iVar3 + 0x18) == 1) {
            surface_lock((void *)((int)local_10 + 0x7c));
            pvVar8 = (void *)ctrl_get_parent(local_10);
            uVar9 = wnd_get_palette(pvVar8);
            surface_apply_palette((void *)((int)local_10 + 0x7c), (void *)uVar9);
            RealizePalette(local_24);
            iVar6 = surface_get_dib((void *)((int)local_10 + 0x7c));
            hdcSrc = *(HDC *)(iVar6 + 4);
            /* The original uses the same accessor for both dimensions here. */
            iVar6 = surface_width((void *)((int)local_10 + 0x7c));
            iVar7 = surface_width((void *)((int)local_10 + 0x7c));
            BitBlt(local_24, 0, 0, iVar7, iVar6, hdcSrc, 0, 0, 0xcc0020);
            surface_unlock((void *)((int)local_10 + 0x7c));
        }
        EndPaint(param_1, &local_64);
        if (GetFocus() == param_1)
            spritebtn_wndproc(param_1, 7, 0, 0);
        break;
    case 0x100:     /* WM_KEYDOWN */
        if (param_3 == 9) {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        else if (param_3 == 0x20 && (pvVar8 = (void *)ctrl_get_parent(local_10),
                                     cVar1 = wnd_keyboard_nav_enabled(pvVar8), cVar1 != '\0')) {
            *(i32 *)(iVar3 + 0x18) = 1;
            wnd_redraw_client(param_1);
            *(i32 *)(iVar3 + 0x18) = 0;
            local_8 = (int)GetAsyncKeyState(0x20);
            while (*(i8 *)((char *)&local_8 + 1) != '\0')
                local_8 = (int)GetAsyncKeyState(0x20);
            wnd_redraw_client(param_1);
            uVar9 = ctrl_get_parent(local_10);
            wnd_set_active_child(uVar9);
            uVar9 = ctrl_get_id(local_10);
            spritebtn_fire_click(local_10, uVar9);
        }
        else {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        break;
    case 7:         /* WM_SETFOCUS */
        pvVar8 = (void *)ctrl_get_parent(local_10);
        cVar1 = wnd_keyboard_nav_enabled(pvVar8);
        if (cVar1 == '\0')
            return 0;
        return ctrl_default_wndproc(param_1, 7, param_3, param_4);
    case 8:         /* WM_KILLFOCUS */
        wnd_redraw_client(param_1);
        break;
    default:
        return ctrl_default_wndproc(param_1, param_2, param_3, param_4);
    }
    return 0;
}
#undef local_64
#undef local_24
#undef local_20
#undef local_10
#undef local_c
#undef local_8

/* ------------------------------------------------------------------------ */
#define g_video_ic          (*(HIC *)((u8 *)&g.d_00638db0))
#define g_video_stream      (*(PAVISTREAM *)((u8 *)&g.d_00638dc4))
#define g_video_open        (*(int *)((u8 *)&g.d_00638dcc))
#define g_video_playing     (*(int *)((u8 *)&g.d_00638dd0))
#define g_video_started     (*(int *)((u8 *)&g.d_00637efc))
#define g_video_start_time  (*(DWORD *)((u8 *)&g.d_00638dbc))
#define g_video_frame_count (*(int *)((u8 *)&g.d_00638dec))
#define g_video_flags_a     (*(uint *)((u8 *)&g.d_006e50ac))
#define g_video_flags_b     (*(uint *)((u8 *)&g.d_006e503c))

/* 0x005e22ed: start playing a video (decompressor setup, audio sync). */
void __cdecl avi_play_start(int param_1)
{
    LONG t_end, t_start;

    if (param_1 == 0 || g_video_open == 0)
        return;
    if (g_video_playing != 0)
        avi_play_pause(param_1);
    if (*(int *)(param_1 + 0x5a0) != 0) {
        ICSendMessage(g_video_ic, 0x403f, 0, 0);
        g_video_flags_a = 8;
        if (*(int *)(param_1 + 0x5a4) != 0)
            g_video_flags_a |= 0x80000004;
        g_video_flags_b = 0x80000008;
        ICSendMessage(g_video_ic, 0x5001, (DWORD_PTR)ADDR(0x006e5098, ((u8 *)&g.d_006e5098)), 0x2c);
        ICSendMessage(g_video_ic, 0x5001, (DWORD_PTR)ADDR(0x006e5028, ((u8 *)&g.d_006e5028)), 0x70);
        *(int *)(param_1 + 0x5f0) <<= 1;
        *(int *)(param_1 + 0x5ec) <<= 1;
        avi_ic_decompress_ex_begin((i32)g_video_ic, 0, param_1 + 0x5c0, 0, 0, 0,
                     *(i32 *)(param_1 + 0x5c4), *(i32 *)(param_1 + 0x5c8),
                     param_1 + 0x5e8, 0, 0, 0,
                     *(int *)(param_1 + 0x5c4) * 2, *(int *)(param_1 + 0x5c8) * 2);
        *(int *)(param_1 + 0x5f0) >>= 1;
        *(int *)(param_1 + 0x5ec) >>= 1;
    }
    if (*(int *)(param_1 + 0x5a8) != 0) {
        t_end = AVIStreamSampleToTime(g_video_stream, *(LONG *)(param_1 + 0xa14));
        t_start = AVIStreamSampleToTime(g_video_stream, *(LONG *)(param_1 + 0xa18));
        avi_audio_prepare_range((void *)(param_1 + 0x11c), t_start, t_end);
    }
    if (g_video_open != 0) {
        if (*(int *)(param_1 + 0x5a4) == 0)
            avi_update_frame(param_1);
        g_video_started = 1;
        g_video_playing = 1;
        g_video_frame_count = 0;
        if (*(int *)(param_1 + 0x5a8) == 0) {
            g_video_start_time = timeGetTime();
        }
        else {
            avi_audio_start((void *)(param_1 + 0x11c));
            *(i32 *)(param_1 + 0x5b0) = 1;
        }
    }
}

/* ------------------------------------------------------------------------ */
#define g_ddraw         (*(void ** *)((u8 *)&g.d_006394c0))    /* IDirectDraw * */
#define g_hinstance     (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define g_ddcaps_driver (*(DWORD *)((u8 *)&g.d_006e50e8))      /* DDCAPS.dwSize */
#define g_ddcaps_hel    (*(DWORD *)((u8 *)&g.d_006e5228))

typedef HRESULT (__stdcall *dd_getcaps_fn)(void *dd, void *driver_caps, void *hel_caps);

/* 0x005e89d0: register the DirectDraw window class, create DirectDraw and
 * check the hardware capabilities. */
#define local_2c (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
i32 __cdecl ddraw_init(void)
{
    HRESULT hr;
    i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */

    local_2c.style = 0xb;
    local_2c.lpfnWndProc = (WNDPROC)ddwin_native_wndproc;
    local_2c.cbClsExtra = 8;
    local_2c.cbWndExtra = 0;
    local_2c.hInstance = g_hinstance;
    local_2c.hIcon = (HICON)0x0;
    local_2c.hCursor = LoadCursorA((HINSTANCE)0x0, (LPCSTR)0x7f00);
    local_2c.hbrBackground = (HBRUSH)0x0;
    local_2c.lpszMenuName = (LPCSTR)0x0;
    local_2c.lpszClassName = s_MSDirectWindow_006394c4;
    RegisterClassA(&local_2c);
    hr = DirectDrawCreate((GUID *)0x0, (LPDIRECTDRAW *)ADDR(0x006394c0, ((u8 *)&g.d_006394c0)), (IUnknown *)0x0);
    if (hr != 0) {
        dbg_log(s_Error__DirectDrawInitialize_Fail_006394d4);
        return 0;
    }
    g_ddcaps_driver = 0x13c;
    g_ddcaps_hel = 0x13c;
    /* IDirectDraw::GetCaps (vtable slot 11) */
    ((dd_getcaps_fn)(*(void ***)g_ddraw)[11])(g_ddraw, (void *)ADDR(0x006e50e8, ((u8 *)&g.d_006e50e8)), (void *)ADDR(0x006e5228, ((u8 *)&g.d_006e5228)));
    if ((ddraw_hw_caps_byte0 & 0x40) == 0)
        dbg_log(s_Direct_Draw__Doesn_t_Supports_Ha_006394f8);
    if ((ddraw_hw_caps_byte2 & 0x40) == 0)
        dbg_log(s_Direct_Draw__Doesn_t_Supports_Co_00639524);
    if ((ddraw_hw_caps_byte3 & 4) == 0)
        dbg_log(s_Direct_Draw__Doesn_t_Supports_Co_0063954c);
    if ((ddraw_hw_caps_byte3 & 8) != 0)
        dbg_log(s_Direct_Draw__Device_is_Bank_Swit_00639578);
    return 1;
}
#undef local_2c

/* ------------------------------------------------------------------------ */
#define g_active_child  (*(void * *)((u8 *)&g.d_00637ea4))

/* 0x005eb447: MDI-style child window procedure: forwards input, sizing,
 * scrolling and palette messages to the window object (GWL 4). */
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(HDC *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(void * *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(UINT *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
uint __stdcall wnd_child_wndproc(HWND param_1,uint param_2,HWND param_3,uint param_4)
{
    int iVar4;
    int iVar5;
    int owner;
    void *view;
    WPARAM wp = (WPARAM)param_3;
    short x = (short)param_4;
    short y = (short)(param_4 >> 0x10);
    i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */

    local_14 = (void *)GetWindowLongA(param_1, 4);
    if (local_14 == (void *)0x0)
        return wnd_base_wndproc(param_1, param_2, wp, param_4);
    view = (void *)((int)local_14 + 0x10);

    switch (param_2) {
    case 0x210:     /* WM_PARENTNOTIFY */
        switch (wp & 0xffff) {
        case 0x201:
            g_active_child = local_14;
            wnd_call_lbuttondown(view, param_4 & 0xffff, param_4 >> 0x10);
            break;
        case 0x204:
            g_active_child = local_14;
            wnd_call_rbuttondown(view, param_4 & 0xffff, param_4 >> 0x10);
            break;
        }
        break;

    case 0x4c8:
        if (param_4 == 0x20d)
            wnd_call_msg4c8(view, 0);
        break;

    case 0x24: {    /* WM_GETMINMAXINFO */
        int *mmi = (int *)param_4;
        int border_y, border_x;
        border_y = wnd_obj_frame_height(wnd_get_window(local_14));
        border_x = wnd_obj_frame_width(wnd_get_window(local_14));
        wnd_get_min_size(local_14, (i32 *)&local_20, (i32 *)&local_24);
        wnd_get_max_size(local_14, (i32 *)&local_8, (i32 *)&local_c);
        mmi[8] = border_x + local_8;        /* ptMaxTrackSize */
        mmi[9] = border_y + local_c;
        mmi[6] = border_x + local_20;       /* ptMinTrackSize */
        mmi[7] = border_y + local_24;
        break;
    }

    case 0x201:     /* WM_LBUTTONDOWN */
        owner = wnd_get_window((void *)GetWindowLongA(param_1, 0));
        g_active_child = local_14;
        if ((*(byte *)(owner + 0x49) & 2) != 0) {
            SetFocus(*(HWND *)(owner + 4));
            BringWindowToTop(param_1);
        }
        *(i32 *)((int)local_14 + 0xa8) = 1;
        wnd_call_lbuttondown(view, (int)x, (int)y);
        break;
    case 0x202:     /* WM_LBUTTONUP */
        g_active_child = local_14;
        if (*(int *)((int)local_14 + 0xa8) == 1) {
            *(i32 *)((int)local_14 + 0xa8) = 0;
            wnd_call_lbuttonup(view, (int)x, (int)y);
        }
        wnd_call_lbuttonup_raw(view, param_4 & 0xffff, param_4 >> 0x10);
        break;
    case 0x204:     /* WM_RBUTTONDOWN */
        owner = wnd_get_window((void *)GetWindowLongA(param_1, 0));
        if ((*(byte *)(owner + 0x49) & 2) != 0) {
            SetFocus(*(HWND *)(owner + 4));
            BringWindowToTop(param_1);
        }
        g_active_child = local_14;
        *(i32 *)((int)local_14 + 0xac) = 1;
        wnd_call_rbuttondown(view, (int)x, (int)y);
        break;
    case 0x205:     /* WM_RBUTTONUP */
        g_active_child = local_14;
        if (*(int *)((int)local_14 + 0xac) == 1) {
            g_active_child = local_14;
            *(i32 *)((int)local_14 + 0xac) = 0;
            wnd_call_rbuttonup(view, (int)x, (int)y);
        }
        wnd_call_rbuttonup_raw(view, (int)x, (int)y);
        break;
    case 0x200:     /* WM_MOUSEMOVE */
        g_active_child = local_14;
        wnd_call_mousemove(view, (int)x, (int)y);
        break;
    case 0x203:     /* WM_LBUTTONDBLCLK */
        g_active_child = local_14;
        wnd_call_dblclick(view, (int)x, (int)y);
        break;

    case 0x100:     /* WM_KEYDOWN */
        g_active_child = local_14;
        wnd_call_keydown_pre(view, input_map_vkey(wp));
        wnd_call_keydown(view, input_map_vkey(wp));
        break;
    case 0x102:     /* WM_CHAR */
        g_active_child = local_14;
        wnd_call_char(view, wp & 0xff);
        break;
    case 0x101:     /* WM_KEYUP */
        g_active_child = local_14;
        wnd_call_keyup(view, input_map_vkey(wp));
        break;

    case 7:         /* WM_SETFOCUS */
        g_active_child = local_14;
        wnd_call_setfocus(view);
        break;

    case 0x311:     /* WM_PALETTECHANGED */
        if (param_3 == param_1)
            return wnd_base_wndproc(param_1, param_2, wp, param_4);
        /* fall through */
    case 0x30f:     /* WM_QUERYNEWPALETTE */
        local_18 = GetDC(param_1);
        iVar5 = wnd_get_window(local_14);
        if (*(int *)(iVar5 + 0x18) != 0) {
            iVar5 = wnd_get_window(local_14);
            SelectPalette(local_18, *(HPALETTE *)(iVar5 + 0x18), 0);
            local_10 = RealizePalette(local_18);
            InvalidateRect(param_1, (RECT *)0x0, 1);
        }
        ReleaseDC(param_1, local_18);
        /* local_10 is left unset when there is no palette (as in the original). */
        return (uint)(local_10 != 0);

    case 5:         /* WM_SIZE */
        g_active_child = local_14;
        if (IsIconic(param_1) == 0) {
            wnd_on_size_nop(local_14, (int)x, (int)y);
            wnd_call_size(view, wp);
        }
        return wnd_base_wndproc(param_1, param_2, wp, param_4);
    case 3:         /* WM_MOVE */
        g_active_child = local_14;
        wnd_call_move(view, (int)x, (int)y);
        return wnd_base_wndproc(param_1, param_2, wp, param_4);

    case 0x111:     /* WM_COMMAND */
        g_active_child = local_14;
        if ((short)param_4 == 0)
            wnd_on_menu_command(param_1, param_3);
        break;
    case 0x3bd:
        snd_wave_on_buffer_done(param_3, param_4);
        return 0;

    case 0x11f:     /* WM_MENUSELECT */
        g_active_child = local_14;
        if ((wp >> 0x10 & 0xffff) == 0xffff && param_4 == 0)
            wnd_fire_menu_select(local_14, 0xffffffff);
        else
            wnd_fire_menu_select(local_14, wp & 0xffff);
        break;

    case 0x112:     /* WM_SYSCOMMAND */
        g_active_child = local_14;
        switch (wp) {
        case 0xf020:    /* SC_MINIMIZE */
            wnd_call_minimize(view);
            break;
        case 0xf120:    /* SC_RESTORE */
            wnd_call_restore(view);
            break;
        }
        return wnd_base_wndproc(param_1, param_2, wp, param_4);

    case 0x10:      /* WM_CLOSE */
        g_active_child = local_14;
        iVar5 = wnd_call_close(view);
        if (iVar5 == 0)
            break;
        return wnd_base_wndproc(param_1, param_2, wp, param_4);

    case 0x44:
        g_active_child = local_14;
        wnd_call_msg44(view, param_4 & 0xffff);
        return 1;

    case 0x114:     /* WM_HSCROLL */
        local_1c = wnd_get_hscroll_pos(local_14);
        switch (wp) {
        case 4:     /* SB_THUMBPOSITION */
            local_1c = (int)(short)(wp >> 0x10);
            SetScrollPos(param_1, 0, local_1c, 1);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb0) = local_1c;
            wnd_call_hscroll(view, *(i32 *)((int)local_14 + 0xb0));
            break;
        case 5:     /* SB_THUMBTRACK */
            g_active_child = local_14;
            wnd_call_hscroll_track(view, (int)(short)(wp >> 0x10));
            break;
        case 1:     /* SB_LINEDOWN */
            local_1c = local_1c + 1;
            goto hscroll_set;
        case 0:     /* SB_LINEUP */
            local_1c = local_1c - 1;
            goto hscroll_set;
        case 3:     /* SB_PAGEDOWN */
            iVar4 = wnd_get_hscroll_page(local_14);
            local_1c = local_1c + iVar4;
            goto hscroll_set;
        case 2:     /* SB_PAGEUP */
            iVar4 = wnd_get_hscroll_page(local_14);
            local_1c = local_1c - iVar4;
        hscroll_set:
            SetScrollPos(param_1, 0, local_1c, 1);
            local_1c = GetScrollPos(param_1, 0);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb0) = local_1c;
            wnd_call_hscroll(view, local_1c);
            break;
        }
        break;

    case 0x115:     /* WM_VSCROLL */
        local_1c = wnd_get_vscroll_pos(local_14);
        switch (wp) {
        case 4:     /* SB_THUMBPOSITION */
            local_1c = (int)(short)(wp >> 0x10);
            SetScrollPos(param_1, 1, local_1c, 1);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb4) = local_1c;
            wnd_call_vscroll(view, *(i32 *)((int)local_14 + 0xb4));
            break;
        case 5:     /* SB_THUMBTRACK */
            g_active_child = local_14;
            wnd_call_vscroll_track(view, (int)(short)(wp >> 0x10));
            break;
        case 1:
            local_1c = local_1c + 1;
            goto vscroll_set;
        case 0:
            local_1c = local_1c - 1;
            goto vscroll_set;
        case 3:
            iVar4 = wnd_get_vscroll_page(local_14);
            local_1c = local_1c + iVar4;
            goto vscroll_set;
        case 2:
            iVar4 = wnd_get_vscroll_page(local_14);
            local_1c = local_1c - iVar4;
        vscroll_set:
            SetScrollPos(param_1, 1, local_1c, 1);
            local_1c = GetScrollPos(param_1, 1);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb4) = local_1c;
            wnd_call_vscroll(view, local_1c);
            break;
        }
        break;

    case 2:         /* WM_DESTROY */
        SetWindowLongA(param_1, 4, 0);
        return wnd_base_wndproc(param_1, param_2, wp, param_4);

    case 0x231:     /* WM_ENTERSIZEMOVE */
        owner = wnd_get_window((void *)GetWindowLongA(param_1, 0));
        (void)owner;
        g_active_child = local_14;
        wnd_call_entersizemove(view);
        return wnd_base_wndproc(param_1, param_2, wp, param_4);
    case 0x232:     /* WM_EXITSIZEMOVE */
        owner = wnd_get_window((void *)GetWindowLongA(param_1, 0));
        (void)owner;
        g_active_child = local_14;
        wnd_call_exitsizemove(view);
        return wnd_base_wndproc(param_1, param_2, wp, param_4);

    default:
        return wnd_base_wndproc(param_1, param_2, wp, param_4);
    }
    return 0;
}
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8
