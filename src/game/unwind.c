/*
 * Functions whose cleanup runs through MSVC unwind funclets (small `call $L`
 * blocks executing with the parent's EBP) that the generator could not
 * translate.  The funclets are inlined here as plain destructor calls on the
 * parent's own locals; exception-frame bookkeeping (fs:[0], trylevel) is
 * dropped.
 */
#include "game.h"

/* Value an MSVC function returns in EAX after its epilogue restored fs:[0]:
   the previous SEH list head, i.e. the current fs:[0] (we push no frame). */
static inline undefined4 seh_list_head(void)
{
    undefined4 r;
#if defined(__i386__) && !defined(CIV2_NATIVE)
    __asm__ volatile ("movl %%fs:0, %0" : "=r"(r));
#else
    r = 0;      /* no SEH chain outside 32-bit Windows */
#endif
    return r;
}

/* 0x0044ca60: destructor - destroys the member at this+0x10, then the base. */
undefined4 __thiscall wnd_dtor(void *this)
{
    void *member;

    /* funclet 0044caab */
    member = (this != NULL) ? (void *)((iptr)this + 0x10) : NULL;
    wnd_handlers_dtor(member);
    /* funclet 0044cad3 */
    wnd_record_destroy(this);
    return seh_list_head();
}

/* 0x0044cba0: destructor - resets the vtable, clears this+0x110, destroys
   the member at this+0x48, then the base. */
void __thiscall surfwnd_dtor(void *this)
{
    void *member;

    *(undefined ***)this = &PTR_FUN_0061c060;
    *(undefined4 *)((iptr)this + 0x110) = 0;
    /* funclet 0044cc01 */
    member = (this != NULL) ? (void *)((iptr)this + 0x48) : NULL;
    surfwnd_wnd_dtor(member);
    /* funclet 0044cc29 */
    surface_dtor(this);
}

/* 0x004f3e70: destructor - destroys the member at this+0x4a4, then the base. */
void __thiscall city_picture_popup_dtor(void *this)
{
    void *member;

    /* funclet 004f3ebb */
    member = (this != NULL) ? (void *)((iptr)this + 0x4a4) : NULL;
    dialog_dtor(member);
    /* funclet 004f3ee5 */
    picwnd_dtor(this);
}

/* 0x005efeb0: destructor - releases the handle at this+0xb0, runs the
   cleanup, destroys the members at this+0xc0 and this+0x44, then the base. */
void __thiscall ddwin_dtor(void *this)
{
    void *member;

    *(undefined4 *)((iptr)this + 0xb0) = ddwin_destroy_native(*(undefined4 *)((iptr)this + 0xb0));
    ddwin_remove_all_controls(this);
    /* funclet 005eff2b */
    ptrlist_dtor((void *)((iptr)this + 0xc0));
    /* funclet 005eff3a */
    member = (this != NULL) ? (void *)((iptr)this + 0x44) : NULL;
    wnd_handlers_dtor(member);
    /* funclet 005eff62 */
    ddsurf_dtor(this);
}

/* 0x0055c3d3: "PICKGOVT" dialog - lets civ param_1 pick a government
   (param_2 != 0: all of them, including anarchy) and applies the choice. */
#define DAT_006d1da0 (*(int *)((u8 *)&g.d_006d1da0))
#define local_30c (*(int *)(frame_ + FRAME_OFF(0)))
#define local_308 (*(undefined1 (*)[756])(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(760)))
void __cdecl civ_select_government_dialog(int param_1, int param_2)
{
    undefined4 uVar2;
    undefined1 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */

    dialog_ctor(local_308, 0x4000);
    if ((1 << ((byte)param_1 & 0x1f) & (uint)game.human_players) == 0) {
        /* nothing */
    }
    else if ((game.multiplayer < 3) || (DAT_006d1da0 == param_1)) {
        dialog_load_game_text(local_308, s_PICKGOVT_00633acc);
        for (local_14 = (param_2 != 0) ? 0 : 1; local_14 < 7; local_14 = local_14 + 1) {
            /* (civ_can_choose_government's last 19 parameters are a decompiler artifact) */
            if ((param_2 != 0) || (civ_can_choose_government(param_1, local_14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) != 0)) {
                text_clear();
                text_append_string_id(government_names[local_14]);
                dialog_add_option(local_308, &text_buffer, local_14, 0);
            }
        }
        local_30c = dlg_show_modal(local_308, 0);
        if (-1 < local_30c) {
            civ_set_government(param_1, local_30c);
            snd_play_effect(0x14, 1, 0, 0);
            uVar2 = (undefined4)civ_leader_name(param_1);
            text_set_string_arg(0, uVar2);
            uVar2 = (undefined4)civ_leader_title(param_1);
            text_set_string_arg(1, uVar2);
            uVar2 = civ_get_adjective(param_1);
            text_set_string_arg(2, uVar2);
            text_set_label_arg(3, government_names[local_30c]);
            popup_game_with_sprite(s_NEWGOVT_00633ad8, &government_sprites + local_30c * 0x3c, 0);
            if (((4 < local_30c) && (((*(undefined1 *)((char *)&game.game_options + 1)) & 1) != 0)) &&
                ((game.field_0c & 0x20) == 0)) {
                text_set_label_arg(0, government_names[local_30c]);
                popup_file_with_sprite(PTR_s_TUTORIAL_00627678, s_DEMOCRATS_00633ae0, &tutorial_icon_sprite, 0);
                game.field_0c = game.field_0c | 0x20;
            }
        }
    }
    else {
        net_send_message(0x9f, *(undefined4 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + param_1 * 4) * 0x54),
                           param_2, 0, 0, 0, 0, 0, 0, 0);
    }
    /* funclet 0055c679 */
    dialog_dtor(local_308);
}
#undef DAT_006d1da0
#undef local_30c
#undef local_308
#undef local_14

/* 0x00493e83: builds a temporary object, stores param_1 in it, runs it if
   its check succeeds, then destroys it. */
#define local_1f8 (*(undefined1 (*)[476])(frame_ + FRAME_OFF(0)))
#define local_1c (*(undefined4 *)(frame_ + FRAME_OFF(476)))
void __cdecl portrait_dlg_show(undefined4 param_1)
{
    int iVar1;
    undefined1 frame_[FRAME_OFF(504)] __attribute__((aligned(8)));  /* original stack frame */

    portrait_dlg_ctor(local_1f8);
    local_1c = param_1;
    iVar1 = portrait_dlg_create(local_1f8);
    if (iVar1 != 0) {
        portrait_dlg_run(local_1f8);
    }
    /* funclet 00493eeb: lea ecx,[ebp-0x1f4] */
    portrait_dlg_dtor(local_1f8);
}
#undef local_1f8
#undef local_1c

/* 0x005e0863: builds a window with "OK"/"Cancel" buttons on the stack and
   tears it all down again; returns 0. */
#define local_630 (*(undefined1 (*)[60])(frame_ + FRAME_OFF(0)))
#define local_5f4 (*(undefined1 (*)[8])(frame_ + FRAME_OFF(60)))
#define local_5ec (*(undefined1 (*)[1076])(frame_ + FRAME_OFF(68)))
#define local_1b8 (*(undefined1 (*)[72])(frame_ + FRAME_OFF(1144)))
#define local_170 (*(undefined1 (*)[204])(frame_ + FRAME_OFF(1216)))
#define local_a4 (*(undefined1 (*)[60])(frame_ + FRAME_OFF(1420)))
#define local_68 (*(undefined1 (*)[72])(frame_ + FRAME_OFF(1480)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(1552)))
undefined4 __cdecl FUN_005e0863(void)
{
    int iVar1;
    int iVar2;
    undefined1 frame_[FRAME_OFF(1584)] __attribute__((aligned(8)));  /* original stack frame */

    palette_init(local_5ec);
    surfwnd_ctor(local_1b8);
    font_init_empty(local_5f4);
    button_ctor(local_630);
    button_ctor(local_a4);
    edit_ctor(local_68);
    font_set(local_5f4, 0, 0x11);
    ui_set_button_font(local_5f4);
    ui_set_default_font(local_5f4);
    SetRect(&local_20, 0, 0, 0x3c, 0x19);
    iVar1 = surface_get_height(local_1b8);
    iVar1 = iVar1 + -0x23;
    iVar2 = surface_get_width(local_1b8);
    OffsetRect(&local_20, iVar2 + -0x46, iVar1);
    button_create(local_630, (undefined4)local_170, 0x65, (undefined4)&local_20,
                       (undefined4)&DAT_00638d90);
    button_set_callback(local_630, (undefined4)dlg_radio_choice_button_cb);
    OffsetRect(&local_20, 0, -0x23);
    button_create(local_a4, (undefined4)local_170, 0x66, (undefined4)&local_20,
                       (undefined4)s_Cancel_00638d94);
    button_set_callback(local_a4, (undefined4)dlg_radio_choice_button_cb);
    /* funclets 005e0a31..005e0a6a: destroy the locals in reverse order */
    edit_dtor(local_68);
    ctrl_dtor(local_a4);
    ctrl_dtor(local_630);
    font_destroy(local_5f4);
    surfwnd_dtor(local_1b8);
    palette_destroy(local_5ec);
    return 0;
}
#undef local_630
#undef local_5f4
#undef local_5ec
#undef local_1b8
#undef local_170
#undef local_a4
#undef local_68
#undef local_20

/* 0x004d53ab: loads picture 0x1f1 and cuts it into six button images
   (two rows of three; the second row's caption depends on the language). */
#define local_68 (*(undefined1 (*)[72])(frame_ + FRAME_OFF(0)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(72)))
void __thiscall spaceship_wnd_make_button_sprites(void *this)
{
    int iVar1;
    undefined4 uVar2;
    undefined1 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */

    surface_ctor(local_68);
    gfx_set_text_color_index(0x8b);
    iVar1 = surface_load_gif_resource(local_68, 0x1f1, 10, 0xec, (void *)((iptr)this + 0x1f8));
    if (iVar1 != 0) {
        text_clear();
        uVar2 = (undefined4)label_string(*(undefined4 *)(DAT_00628420 + 0x3f8));
        text_append(uVar2);
        SetRect(&local_20, 0, 0, 0x34, 0x24);
        OffsetRect(&local_20, 1, 1);
        surface_draw_text_in_rect(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&text_buffer, (LONG *)&local_20, 0);
        sprite_grab_from_surface((void *)((iptr)this + 0x978), (undefined4)local_68, 9, 1, 1, 0x34, 0x24);
        OffsetRect(&local_20, 0x35, 0);
        surface_draw_text_in_rect(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&text_buffer, (LONG *)&local_20, 0);
        sprite_grab_from_surface((void *)((iptr)this + 0x9f0), (undefined4)local_68, 9, 0x36, 1, 0x34, 0x24);
        OffsetRect(&local_20, 0x35, 0);
        surface_draw_text_in_rect(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&text_buffer, (LONG *)&local_20, 0);
        sprite_grab_from_surface((void *)((iptr)this + 0x9b4), (undefined4)local_68, 9, 0x6b, 1, 0x34, 0x24);
        gfx_set_text_color_index(0xc6);
        text_clear();
        if (game_language == 0) {
            uVar2 = (undefined4)label_string(*(undefined4 *)(DAT_00628420 + 0x354));
            text_append(uVar2);
        }
        else if (game_language == 1) {
            text_append(s_Lancer_0062e324);
        }
        else if (game_language == 2) {
            text_append(s_Starten_0062e32c);
        }
        SetRect(&local_20, 0, 0, 0x43, 0x24);
        OffsetRect(&local_20, 1, 0x26);
        surface_draw_text_in_rect(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&text_buffer, (LONG *)&local_20, 0);
        sprite_grab_from_surface((void *)((iptr)this + 0xa2c), (undefined4)local_68, 9, 1, 0x26, 0x43, 0x24);
        OffsetRect(&local_20, 0x44, 0);
        surface_draw_text_in_rect(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&text_buffer, (LONG *)&local_20, 0);
        sprite_grab_from_surface((void *)((iptr)this + 0xaa4), (undefined4)local_68, 9, 0x45, 0x26, 0x43, 0x24);
        OffsetRect(&local_20, 0x44, 0);
        surface_draw_text_in_rect(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&text_buffer, (LONG *)&local_20, 0);
        sprite_grab_from_surface((void *)((iptr)this + 0xa68), (undefined4)local_68, 9, 0x89, 0x26, 0x43, 0x24);
    }
    /* funclet 004d56ea: lea ecx,[ebp-0x64] */
    surface_dtor(local_68);
}
#undef local_68
#undef local_20
