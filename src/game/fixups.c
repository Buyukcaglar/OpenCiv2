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
void __cdecl FUN_005c8791(undefined4 param_1)
{
    char *font;
    undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */

    font = (char *)FUN_005dcdf9(param_1);
    for (local_c = 0; local_c < *(int *)(font + 0x100); local_c = local_c + 1) {
        if (*(int *)(font + local_c * 4 + 0x108) != 0) {
            DeleteObject(*(HGDIOBJ *)(font + local_c * 4 + 0x108));
            *(int *)(font + local_c * 4 + 0x108) = 0;
        }
    }
    RemoveFontResourceA(font);   /* file name at the start of the block */
    FUN_005dce29(param_1);
    FUN_005dce96(param_1);
}
#undef local_c

/* ------------------------------------------------------------------------ */
#define g_btn_hover     (*(int *)((u8 *)&g.d_00637c9c))
#define g_btn_pressed   (*(int *)((u8 *)&g.d_00637ca0))

/* 0x005c8caf: hover-tracking button window procedure. */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
undefined4 __stdcall FUN_005c8caf(HWND param_1,undefined4 param_2,undefined4 param_3,uint param_4)
{
    void *this;
    int iVar1;
    int *piVar2;
    BOOL BVar3;
    undefined4 uVar4;
    POINT pt;
    undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */

    iVar1 = FUN_005c9563(param_1);
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
                    uVar4 = thunk_FUN_0040f810(this);
                    FUN_005c6303(uVar4);
                    uVar4 = thunk_FUN_00418740(this);
                    FUN_005c8f70(this, uVar4);
                }
            }
        }
        else {
            piVar2 = (int *)FUN_005c8f50(this);
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
                        uVar4 = thunk_FUN_0040f810(this);
                        FUN_005c6303(uVar4);
                        uVar4 = thunk_FUN_00418740(this);
                        FUN_005c8fb0(this, uVar4);
                    }
                }
            }
        }
        break;
    case 0x201:     /* WM_LBUTTONDOWN */
        if (g_btn_hover != 0) {
            g_btn_pressed = 1;
            uVar4 = thunk_FUN_0040f810(this);
            FUN_005c6303(uVar4);
            uVar4 = thunk_FUN_00418740(this);
            FUN_005c9030(this, uVar4);
        }
        break;
    case 0x202:     /* WM_LBUTTONUP */
        if (g_btn_pressed != 0) {
            g_btn_pressed = 0;
            if (g_btn_hover != 0) {
                if (this != (void *)0x0) {
                    uVar4 = thunk_FUN_0040f810(this);
                    FUN_005c6303(uVar4);
                    uVar4 = thunk_FUN_00418740(this);
                    FUN_005c8ff0(this, uVar4);
                }
            }
            else {
                ReleaseCapture();
                if (this != (void *)0x0) {
                    uVar4 = thunk_FUN_0040f810(this);
                    FUN_005c6303(uVar4);
                    uVar4 = thunk_FUN_00418740(this);
                    FUN_005c8fb0(this, uVar4);
                }
            }
        }
        break;
    case 0x203:     /* WM_LBUTTONDBLCLK */
        if (g_btn_hover != 0) {
            uVar4 = thunk_FUN_0040f810(this);
            FUN_005c6303(uVar4);
            uVar4 = thunk_FUN_00418740(this);
            FUN_005c9070(this, uVar4);
        }
        break;
    default:
        return FUN_005c9307(param_1, param_2, param_3, param_4);
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
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(128)))
undefined4 __stdcall FUN_005cacd4(HWND param_1,uint param_2,WPARAM param_3,uint param_4)
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
    undefined4 uVar9;
    POINT pt;
    undefined1 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */

    local_44 = FUN_005c9563(param_1);
    if (local_44 == 0)
        return 0;
    local_28 = *(void **)(local_44 + 4);
    switch (param_2) {
    case 0x201:     /* WM_LBUTTONDOWN */
        iVar7 = thunk_FUN_00530e80(local_28);
        if (iVar7 == 0)
            break;
        *(undefined4 *)(local_44 + 0x1c) = 1;
        SetFocus(param_1);
        SetCapture(param_1);
        /* fall through */
    case 0x200:     /* WM_MOUSEMOVE */
        if (*(int *)(local_44 + 0x1c) != 0) {
            pt.x = param_4 & 0xffff;
            pt.y = (param_4 >> 0x10) & 0xffff;
            piVar3 = (int *)FUN_005c8f50(local_28);
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
        *(undefined4 *)(local_44 + 0x1c) = 0;
        pt.x = param_4 & 0xffff;
        pt.y = (param_4 >> 0x10) & 0xffff;
        piVar3 = (int *)FUN_005c8f50(local_28);
        local_38.left = piVar3[0];
        local_38.top = piVar3[1];
        local_38.right = piVar3[2];
        local_38.bottom = piVar3[3];
        OffsetRect(&local_38, -local_38.left, -local_38.top);
        InvalidateRect(param_1, &local_38, 0);
        *(undefined4 *)(local_44 + 0x18) = 0;
        BVar4 = PtInRect(&local_38, pt);
        if (BVar4 != 0) {
            FUN_005cacd4(param_1, 0xf, 0, 0);
            uVar9 = thunk_FUN_0040f810(local_28);
            FUN_005c6303(uVar9);
            uVar9 = thunk_FUN_00418740(local_28);
            FUN_005cbdf0(local_28, uVar9);
        }
        break;
    case 0xf:       /* WM_PAINT */
        local_40 = BeginPaint(param_1, &local_84);
        piVar3 = (int *)FUN_005c8f50(local_28);
        local_38.left = piVar3[0];
        local_38.top = piVar3[1];
        local_38.right = piVar3[2];
        local_38.bottom = piVar3[3];
        ValidateRect(GetParent(param_1), &local_38);
        iVar7 = thunk_FUN_00530e80(local_28);
        if (iVar7 == 0) {
            pHVar6 = GetFocus();
            if (pHVar6 == param_1) {
                pvVar8 = (void *)thunk_FUN_0040f810(local_28);
                cVar1 = FUN_005cbdd0(pvVar8);
                if (cVar1 == '\0') {
                    pvVar8 = (void *)thunk_FUN_0040f810(local_28);
                    iVar7 = thunk_FUN_00414d10(pvVar8);
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
        iVar7 = thunk_FUN_00407fc0(&local_38);      /* height */
        cx = thunk_FUN_00407f90(&local_38);         /* width */
        BitBlt(local_40, 0, 0, cx, iVar7, local_24, 0, 0, 0xcc0020);
        SelectObject(local_24, h);
        DeleteDC(local_24);
        EndPaint(param_1, &local_84);
        if (GetFocus() == param_1)
            FUN_005cacd4(param_1, 7, 0, 0);
        break;
    case 0x100:     /* WM_KEYDOWN */
        if (param_3 == 9) {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        else if (param_3 == 0x20 && (iVar7 = thunk_FUN_00530e80(local_28), iVar7 != 0) &&
                 (pvVar8 = (void *)thunk_FUN_0040f810(local_28),
                  cVar1 = FUN_005cbdd0(pvVar8), cVar1 != '\0')) {
            *(undefined4 *)(local_44 + 0x18) = 1;
            FUN_005c96cc(param_1);
            *(undefined4 *)(local_44 + 0x18) = 0;
            SVar2 = GetAsyncKeyState(0x20);
            local_8 = (int)SVar2;
            thunk_FUN_00453af0();
            while (*(undefined1 *)((char *)&local_8 + 1) != '\0') {
                SVar2 = GetAsyncKeyState(0x20);
                local_8 = (int)SVar2;
            }
            FUN_005c96cc(param_1);
            uVar9 = thunk_FUN_0040f810(local_28);
            FUN_005c6303(uVar9);
            uVar9 = thunk_FUN_00418740(local_28);
            FUN_005cbdf0(local_28, uVar9);
        }
        else {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        break;
    case 7:         /* WM_SETFOCUS: draw the focus frame */
        pvVar8 = (void *)thunk_FUN_0040f810(local_28);
        cVar1 = FUN_005cbdd0(pvVar8);
        if (cVar1 == '\0')
            return FUN_005c9307(param_1, param_2, param_3, param_4);
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
        FUN_005c96cc(param_1);
        break;
    default:
        return FUN_005c9307(param_1, param_2, param_3, param_4);
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
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(96)))
undefined4 __stdcall FUN_005cb6eb(HWND param_1,uint param_2,WPARAM param_3,uint param_4)
{
    char cVar1;
    int iVar3;
    int *piVar4;
    HPALETTE hPal;
    int iVar6;
    int iVar7;
    void *pvVar8;
    undefined4 uVar9;
    HDC hdcSrc;
    BOOL BVar12;
    POINT pt;
    undefined1 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */

    iVar3 = FUN_005c9563(param_1);
    if (iVar3 == 0)
        return 1;
    local_10 = *(void **)(iVar3 + 4);
    switch (param_2) {
    case 0x201:     /* WM_LBUTTONDOWN */
        *(undefined4 *)(iVar3 + 0x1c) = 1;
        SetFocus(param_1);
        SetCapture(param_1);
        /* fall through */
    case 0x200:     /* WM_MOUSEMOVE */
        if (*(int *)(iVar3 + 0x1c) != 0) {
            pt.x = param_4 & 0xffff;
            pt.y = (param_4 >> 0x10) & 0xffff;
            piVar4 = (int *)FUN_005c8f50(local_10);
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
            *(undefined4 *)(iVar3 + 0x1c) = 0;
            pt.x = param_4 & 0xffff;
            pt.y = (param_4 >> 0x10) & 0xffff;
            piVar4 = (int *)FUN_005c8f50(local_10);
            local_20.left = piVar4[0];
            local_20.top = piVar4[1];
            local_20.right = piVar4[2];
            local_20.bottom = piVar4[3];
            OffsetRect(&local_20, -local_20.left, -local_20.top);
            InvalidateRect(param_1, &local_20, 0);
            *(undefined4 *)(iVar3 + 0x18) = 0;
            BVar12 = PtInRect(&local_20, pt);
            if (BVar12 != 0) {
                FUN_005cb6eb(param_1, 0xf, 0, 0);
                uVar9 = thunk_FUN_0040f810(local_10);
                FUN_005c6303(uVar9);
                uVar9 = thunk_FUN_00418740(local_10);
                if (param_2 == 0x202)
                    FUN_005cbe30(local_10, uVar9);
                else
                    FUN_005cbe70(local_10, uVar9);
            }
        }
        break;
    case 0x204:     /* WM_RBUTTONDOWN */
        *(undefined4 *)(iVar3 + 0x1c) = 1;
        SetFocus(param_1);
        SetCapture(param_1);
        break;
    case 0xf:       /* WM_PAINT */
        local_24 = BeginPaint(param_1, &local_64);
        piVar4 = (int *)FUN_005c8f50(local_10);
        local_20.left = piVar4[0];
        local_20.top = piVar4[1];
        local_20.right = piVar4[2];
        local_20.bottom = piVar4[3];
        ValidateRect(GetParent(param_1), &local_20);
        OffsetRect(&local_20, -local_20.left, -local_20.top);
        ValidateRect(param_1, &local_20);
        if (g_palette_mode == 1) {
            pvVar8 = (void *)thunk_FUN_0040f810(local_10);
            pvVar8 = (void *)thunk_FUN_00511320(pvVar8);
            hPal = (HPALETTE)FUN_005cbdb0(pvVar8);
            SelectPalette(local_24, hPal, 0);
        }
        if (*(int *)(iVar3 + 0x18) == 0) {
            FUN_005c01c1((void *)((int)local_10 + 0x34));
            pvVar8 = (void *)thunk_FUN_0040f810(local_10);
            uVar9 = thunk_FUN_00511320(pvVar8);
            FUN_005c0d12((void *)((int)local_10 + 0x34), (void *)uVar9);
            if (g_palette_mode == 1)
                RealizePalette(local_24);
            iVar6 = FUN_005c55f0((void *)((int)local_10 + 0x34));
            hdcSrc = *(HDC *)(iVar6 + 4);
            iVar6 = thunk_FUN_0043c560((void *)((int)local_10 + 0x34));
            iVar7 = thunk_FUN_0043c590((void *)((int)local_10 + 0x34));
            BitBlt(local_24, 0, 0, iVar7, iVar6, hdcSrc, 0, 0, 0xcc0020);
            FUN_005c02e0((void *)((int)local_10 + 0x34));
        }
        if (*(int *)(iVar3 + 0x18) == 1) {
            FUN_005c01c1((void *)((int)local_10 + 0x7c));
            pvVar8 = (void *)thunk_FUN_0040f810(local_10);
            uVar9 = thunk_FUN_00511320(pvVar8);
            FUN_005c0d12((void *)((int)local_10 + 0x7c), (void *)uVar9);
            RealizePalette(local_24);
            iVar6 = FUN_005c55f0((void *)((int)local_10 + 0x7c));
            hdcSrc = *(HDC *)(iVar6 + 4);
            /* The original uses the same accessor for both dimensions here. */
            iVar6 = thunk_FUN_0043c590((void *)((int)local_10 + 0x7c));
            iVar7 = thunk_FUN_0043c590((void *)((int)local_10 + 0x7c));
            BitBlt(local_24, 0, 0, iVar7, iVar6, hdcSrc, 0, 0, 0xcc0020);
            FUN_005c02e0((void *)((int)local_10 + 0x7c));
        }
        EndPaint(param_1, &local_64);
        if (GetFocus() == param_1)
            FUN_005cb6eb(param_1, 7, 0, 0);
        break;
    case 0x100:     /* WM_KEYDOWN */
        if (param_3 == 9) {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        else if (param_3 == 0x20 && (pvVar8 = (void *)thunk_FUN_0040f810(local_10),
                                     cVar1 = FUN_005cbdd0(pvVar8), cVar1 != '\0')) {
            *(undefined4 *)(iVar3 + 0x18) = 1;
            FUN_005c96cc(param_1);
            *(undefined4 *)(iVar3 + 0x18) = 0;
            local_8 = (int)GetAsyncKeyState(0x20);
            while (*(undefined1 *)((char *)&local_8 + 1) != '\0')
                local_8 = (int)GetAsyncKeyState(0x20);
            FUN_005c96cc(param_1);
            uVar9 = thunk_FUN_0040f810(local_10);
            FUN_005c6303(uVar9);
            uVar9 = thunk_FUN_00418740(local_10);
            FUN_005cbe30(local_10, uVar9);
        }
        else {
            SendMessageA(GetParent(param_1), param_2, param_3, param_4);
        }
        break;
    case 7:         /* WM_SETFOCUS */
        pvVar8 = (void *)thunk_FUN_0040f810(local_10);
        cVar1 = FUN_005cbdd0(pvVar8);
        if (cVar1 == '\0')
            return 0;
        return FUN_005c9307(param_1, 7, param_3, param_4);
    case 8:         /* WM_KILLFOCUS */
        FUN_005c96cc(param_1);
        break;
    default:
        return FUN_005c9307(param_1, param_2, param_3, param_4);
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
void __cdecl FUN_005e22ed(int param_1)
{
    LONG t_end, t_start;

    if (param_1 == 0 || g_video_open == 0)
        return;
    if (g_video_playing != 0)
        FUN_005e2675(param_1);
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
        FUN_005e250c((undefined4)g_video_ic, 0, param_1 + 0x5c0, 0, 0, 0,
                     *(undefined4 *)(param_1 + 0x5c4), *(undefined4 *)(param_1 + 0x5c8),
                     param_1 + 0x5e8, 0, 0, 0,
                     *(int *)(param_1 + 0x5c4) * 2, *(int *)(param_1 + 0x5c8) * 2);
        *(int *)(param_1 + 0x5f0) >>= 1;
        *(int *)(param_1 + 0x5ec) >>= 1;
    }
    if (*(int *)(param_1 + 0x5a8) != 0) {
        t_end = AVIStreamSampleToTime(g_video_stream, *(LONG *)(param_1 + 0xa14));
        t_start = AVIStreamSampleToTime(g_video_stream, *(LONG *)(param_1 + 0xa18));
        FUN_005eedec((void *)(param_1 + 0x11c), t_start, t_end);
    }
    if (g_video_open != 0) {
        if (*(int *)(param_1 + 0x5a4) == 0)
            FUN_005e2cd1(param_1);
        g_video_started = 1;
        g_video_playing = 1;
        g_video_frame_count = 0;
        if (*(int *)(param_1 + 0x5a8) == 0) {
            g_video_start_time = timeGetTime();
        }
        else {
            FUN_005eee4f((void *)(param_1 + 0x11c));
            *(undefined4 *)(param_1 + 0x5b0) = 1;
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
undefined4 __cdecl FUN_005e89d0(void)
{
    HRESULT hr;
    undefined1 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */

    local_2c.style = 0xb;
    local_2c.lpfnWndProc = (WNDPROC)FUN_005ef6cb;
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
        FUN_005d225b(s_Error__DirectDrawInitialize_Fail_006394d4);
        return 0;
    }
    g_ddcaps_driver = 0x13c;
    g_ddcaps_hel = 0x13c;
    /* IDirectDraw::GetCaps (vtable slot 11) */
    ((dd_getcaps_fn)(*(void ***)g_ddraw)[11])(g_ddraw, (void *)ADDR(0x006e50e8, ((u8 *)&g.d_006e50e8)), (void *)ADDR(0x006e5228, ((u8 *)&g.d_006e5228)));
    if ((DAT_006e50ec & 0x40) == 0)
        FUN_005d225b(s_Direct_Draw__Doesn_t_Supports_Ha_006394f8);
    if ((DAT_006e50ee & 0x40) == 0)
        FUN_005d225b(s_Direct_Draw__Doesn_t_Supports_Co_00639524);
    if ((DAT_006e50ef & 4) == 0)
        FUN_005d225b(s_Direct_Draw__Doesn_t_Supports_Co_0063954c);
    if ((DAT_006e50ef & 8) != 0)
        FUN_005d225b(s_Direct_Draw__Device_is_Bank_Swit_00639578);
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
uint __stdcall FUN_005eb447(HWND param_1,uint param_2,HWND param_3,uint param_4)
{
    int iVar4;
    int iVar5;
    int owner;
    void *view;
    WPARAM wp = (WPARAM)param_3;
    short x = (short)param_4;
    short y = (short)(param_4 >> 0x10);
    undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */

    local_14 = (void *)GetWindowLongA(param_1, 4);
    if (local_14 == (void *)0x0)
        return FUN_005dbe88(param_1, param_2, wp, param_4);
    view = (void *)((int)local_14 + 0x10);

    switch (param_2) {
    case 0x210:     /* WM_PARENTNOTIFY */
        switch (wp & 0xffff) {
        case 0x201:
            g_active_child = local_14;
            FUN_005ecf90(view, param_4 & 0xffff, param_4 >> 0x10);
            break;
        case 0x204:
            g_active_child = local_14;
            FUN_005ed050(view, param_4 & 0xffff, param_4 >> 0x10);
            break;
        }
        break;

    case 0x4c8:
        if (param_4 == 0x20d)
            FUN_005ed4e0(view, 0);
        break;

    case 0x24: {    /* WM_GETMINMAXINFO */
        int *mmi = (int *)param_4;
        int border_y, border_x;
        border_y = FUN_005bca3d(thunk_FUN_00414d10(local_14));
        border_x = FUN_005bc9d3(thunk_FUN_00414d10(local_14));
        FUN_005bb910(local_14, (undefined4 *)&local_20, (undefined4 *)&local_24);
        FUN_005bb950(local_14, (undefined4 *)&local_8, (undefined4 *)&local_c);
        mmi[8] = border_x + local_8;        /* ptMaxTrackSize */
        mmi[9] = border_y + local_c;
        mmi[6] = border_x + local_20;       /* ptMinTrackSize */
        mmi[7] = border_y + local_24;
        break;
    }

    case 0x201:     /* WM_LBUTTONDOWN */
        owner = thunk_FUN_00414d10((void *)GetWindowLongA(param_1, 0));
        g_active_child = local_14;
        if ((*(byte *)(owner + 0x49) & 2) != 0) {
            SetFocus(*(HWND *)(owner + 4));
            BringWindowToTop(param_1);
        }
        *(undefined4 *)((int)local_14 + 0xa8) = 1;
        FUN_005ecf90(view, (int)x, (int)y);
        break;
    case 0x202:     /* WM_LBUTTONUP */
        g_active_child = local_14;
        if (*(int *)((int)local_14 + 0xa8) == 1) {
            *(undefined4 *)((int)local_14 + 0xa8) = 0;
            FUN_005ed010(view, (int)x, (int)y);
        }
        FUN_005ecfd0(view, param_4 & 0xffff, param_4 >> 0x10);
        break;
    case 0x204:     /* WM_RBUTTONDOWN */
        owner = thunk_FUN_00414d10((void *)GetWindowLongA(param_1, 0));
        if ((*(byte *)(owner + 0x49) & 2) != 0) {
            SetFocus(*(HWND *)(owner + 4));
            BringWindowToTop(param_1);
        }
        g_active_child = local_14;
        *(undefined4 *)((int)local_14 + 0xac) = 1;
        FUN_005ed050(view, (int)x, (int)y);
        break;
    case 0x205:     /* WM_RBUTTONUP */
        g_active_child = local_14;
        if (*(int *)((int)local_14 + 0xac) == 1) {
            g_active_child = local_14;
            *(undefined4 *)((int)local_14 + 0xac) = 0;
            FUN_005ed0d0(view, (int)x, (int)y);
        }
        FUN_005ed090(view, (int)x, (int)y);
        break;
    case 0x200:     /* WM_MOUSEMOVE */
        g_active_child = local_14;
        FUN_005ecf50(view, (int)x, (int)y);
        break;
    case 0x203:     /* WM_LBUTTONDBLCLK */
        g_active_child = local_14;
        FUN_005ed110(view, (int)x, (int)y);
        break;

    case 0x100:     /* WM_KEYDOWN */
        g_active_child = local_14;
        FUN_005ed150(view, FUN_005eb3ed(wp));
        FUN_005ed1d0(view, FUN_005eb3ed(wp));
        break;
    case 0x102:     /* WM_CHAR */
        g_active_child = local_14;
        FUN_005ed210(view, wp & 0xff);
        break;
    case 0x101:     /* WM_KEYUP */
        g_active_child = local_14;
        FUN_005ed190(view, FUN_005eb3ed(wp));
        break;

    case 7:         /* WM_SETFOCUS */
        g_active_child = local_14;
        FUN_005ed2f0(view);
        break;

    case 0x311:     /* WM_PALETTECHANGED */
        if (param_3 == param_1)
            return FUN_005dbe88(param_1, param_2, wp, param_4);
        /* fall through */
    case 0x30f:     /* WM_QUERYNEWPALETTE */
        local_18 = GetDC(param_1);
        iVar5 = thunk_FUN_00414d10(local_14);
        if (*(int *)(iVar5 + 0x18) != 0) {
            iVar5 = thunk_FUN_00414d10(local_14);
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
            FUN_005ed580(local_14, (int)x, (int)y);
            FUN_005ed320(view, wp);
        }
        return FUN_005dbe88(param_1, param_2, wp, param_4);
    case 3:         /* WM_MOVE */
        g_active_child = local_14;
        FUN_005ed360(view, (int)x, (int)y);
        return FUN_005dbe88(param_1, param_2, wp, param_4);

    case 0x111:     /* WM_COMMAND */
        g_active_child = local_14;
        if ((short)param_4 == 0)
            FUN_005ec1a1(param_1, param_3);
        break;
    case 0x3bd:
        FUN_005d6c99(param_3, param_4);
        return 0;

    case 0x11f:     /* WM_MENUSELECT */
        g_active_child = local_14;
        if ((wp >> 0x10 & 0xffff) == 0xffff && param_4 == 0)
            FUN_005c63af(local_14, 0xffffffff);
        else
            FUN_005c63af(local_14, wp & 0xffff);
        break;

    case 0x112:     /* WM_SYSCOMMAND */
        g_active_child = local_14;
        switch (wp) {
        case 0xf020:    /* SC_MINIMIZE */
            FUN_005ed290(view);
            break;
        case 0xf120:    /* SC_RESTORE */
            FUN_005ed2c0(view);
            break;
        }
        return FUN_005dbe88(param_1, param_2, wp, param_4);

    case 0x10:      /* WM_CLOSE */
        g_active_child = local_14;
        iVar5 = FUN_005ed250(view);
        if (iVar5 == 0)
            break;
        return FUN_005dbe88(param_1, param_2, wp, param_4);

    case 0x44:
        g_active_child = local_14;
        FUN_005ed3a0(view, param_4 & 0xffff);
        return 1;

    case 0x114:     /* WM_HSCROLL */
        local_1c = FUN_005ed640(local_14);
        switch (wp) {
        case 4:     /* SB_THUMBPOSITION */
            local_1c = (int)(short)(wp >> 0x10);
            SetScrollPos(param_1, 0, local_1c, 1);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb0) = local_1c;
            FUN_005ed3e0(view, *(undefined4 *)((int)local_14 + 0xb0));
            break;
        case 5:     /* SB_THUMBTRACK */
            g_active_child = local_14;
            FUN_005ed420(view, (int)(short)(wp >> 0x10));
            break;
        case 1:     /* SB_LINEDOWN */
            local_1c = local_1c + 1;
            goto hscroll_set;
        case 0:     /* SB_LINEUP */
            local_1c = local_1c - 1;
            goto hscroll_set;
        case 3:     /* SB_PAGEDOWN */
            iVar4 = FUN_005ed680(local_14);
            local_1c = local_1c + iVar4;
            goto hscroll_set;
        case 2:     /* SB_PAGEUP */
            iVar4 = FUN_005ed680(local_14);
            local_1c = local_1c - iVar4;
        hscroll_set:
            SetScrollPos(param_1, 0, local_1c, 1);
            local_1c = GetScrollPos(param_1, 0);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb0) = local_1c;
            FUN_005ed3e0(view, local_1c);
            break;
        }
        break;

    case 0x115:     /* WM_VSCROLL */
        local_1c = FUN_005ed660(local_14);
        switch (wp) {
        case 4:     /* SB_THUMBPOSITION */
            local_1c = (int)(short)(wp >> 0x10);
            SetScrollPos(param_1, 1, local_1c, 1);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb4) = local_1c;
            FUN_005ed460(view, *(undefined4 *)((int)local_14 + 0xb4));
            break;
        case 5:     /* SB_THUMBTRACK */
            g_active_child = local_14;
            FUN_005ed4a0(view, (int)(short)(wp >> 0x10));
            break;
        case 1:
            local_1c = local_1c + 1;
            goto vscroll_set;
        case 0:
            local_1c = local_1c - 1;
            goto vscroll_set;
        case 3:
            iVar4 = FUN_005ed6a0(local_14);
            local_1c = local_1c + iVar4;
            goto vscroll_set;
        case 2:
            iVar4 = FUN_005ed6a0(local_14);
            local_1c = local_1c - iVar4;
        vscroll_set:
            SetScrollPos(param_1, 1, local_1c, 1);
            local_1c = GetScrollPos(param_1, 1);
            g_active_child = local_14;
            *(int *)((int)local_14 + 0xb4) = local_1c;
            FUN_005ed460(view, local_1c);
            break;
        }
        break;

    case 2:         /* WM_DESTROY */
        SetWindowLongA(param_1, 4, 0);
        return FUN_005dbe88(param_1, param_2, wp, param_4);

    case 0x231:     /* WM_ENTERSIZEMOVE */
        owner = thunk_FUN_00414d10((void *)GetWindowLongA(param_1, 0));
        (void)owner;
        g_active_child = local_14;
        FUN_005ed520(view);
        return FUN_005dbe88(param_1, param_2, wp, param_4);
    case 0x232:     /* WM_EXITSIZEMOVE */
        owner = thunk_FUN_00414d10((void *)GetWindowLongA(param_1, 0));
        (void)owner;
        g_active_child = local_14;
        FUN_005ed550(view);
        return FUN_005dbe88(param_1, param_2, wp, param_4);

    default:
        return FUN_005dbe88(param_1, param_2, wp, param_4);
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
