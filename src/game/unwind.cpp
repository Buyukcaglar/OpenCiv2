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
static inline i32 seh_list_head(void)
{
    i32 r;
    r = 0;      /* no SEH chain outside 32-bit Windows */
    return r;
}

/* 0x0044ca60: destructor - destroys the member at this+0x10, then the base. */
i32 __thiscall wnd_dtor(void *self)
{
    void *member;

    /* funclet 0044caab */
    member = (self != NULL) ? (void *)((iptr)self + 0x10) : NULL;
    wnd_handlers_dtor(member);
    /* funclet 0044cad3 */
    wnd_record_destroy((WndDestroyView *)self);
    return seh_list_head();
}

/* 0x0044cba0: destructor - resets the vtable, clears this+0x110, destroys
   the member at this+0x48, then the base. */
void __thiscall surfwnd_dtor(void *self)
{
    void *member;

    *(i8 ***)self = (i8 **)((pointer *)(ptr_fun_rest + 8));
    *(i32 *)((iptr)self + 0x110) = 0;
    /* funclet 0044cc01 */
    member = (self != NULL) ? (void *)((iptr)self + 0x48) : NULL;
    surfwnd_wnd_dtor(member);
    /* funclet 0044cc29 */
    surface_dtor((DibSurface *)self);
}

/* 0x004f3e70: destructor - destroys the member at this+0x4a4, then the base. */
void __thiscall city_picture_popup_dtor(void *self)
{
    void *member;

    /* funclet 004f3ebb */
    member = (self != NULL) ? (void *)((iptr)self + 0x4a4) : NULL;
    dialog_dtor((Dialog *)member);
    /* funclet 004f3ee5 */
    picwnd_dtor(self);
}

/* 0x005efeb0: destructor - releases the handle at this+0xb0, runs the
   cleanup, destroys the members at this+0xc0 and this+0x44, then the base. */
void __thiscall ddwin_dtor(void *self)
{
    void *member;

    *(i32 *)((iptr)self + 0xb0) = ddwin_destroy_native((i32 *)*(i32 *)((iptr)self + 0xb0));
    ddwin_remove_all_controls(self);
    /* funclet 005eff2b */
    ptrlist_dtor((void *)((iptr)self + 0xc0));
    /* funclet 005eff3a */
    member = (self != NULL) ? (void *)((iptr)self + 0x44) : NULL;
    wnd_handlers_dtor(member);
    /* funclet 005eff62 */
    ddsurf_dtor(self);
}

/* 0x0055c3d3: "PICKGOVT" dialog - lets civ civ2 pick a government
   (all_govs != 0: all of them, including anarchy) and applies the choice. */
void __cdecl civ_select_government_dialog(int civ2, int all_govs)
{
    i32 text_arg;
    int choice2;
    Dialog dlg;
    int gov;

    dialog_ctor(&dlg, 0x4000);
    if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
        /* nothing */
    }
    else if ((game.multiplayer < 3) || (human_civ[0] == civ2)) {
        dialog_load_game_text(&dlg, (iptr)str_pickgovt);
        for (gov = (all_govs != 0) ? 0 : 1; gov < 7; gov = gov + 1) {
            /* (civ_can_choose_government's last 19 parameters are a decompiler artifact) */
            if ((all_govs != 0) || (civ_can_choose_government(civ2, gov, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) != 0)) {
                text_clear();
                text_append_string_id(government_names[gov]);
                dialog_add_option((DialogOptionList*)(&dlg), (iptr)&map_views_block.text_buffer, gov, 0);
            }
        }
        choice2 = dlg_show_modal(&dlg, 0);
        if (-1 < choice2) {
            civ_set_government(civ2, choice2);
            snd_play_effect(0x14, 1, 0, 0);
            text_arg = (i32)civ_leader_name(civ2);
            text_set_string_arg(0, text_arg);
            text_arg = (i32)civ_leader_title(civ2);
            text_set_string_arg(1, text_arg);
            text_arg = civ_get_adjective(civ2);
            text_set_string_arg(2, text_arg);
            text_set_label_arg(3, government_names[choice2]);
            popup_game_with_sprite((iptr)str_newgovt, (iptr)(((i8 *)&government_sprites_block.government_sprites) + choice2 * 0x3c), 0);
            if (((4 < choice2) && (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0)) &&
                ((game.field_0c & 0x20) == 0)) {
                text_set_label_arg(0, government_names[choice2]);
                popup_file_with_sprite((iptr)(*(i8 * *)str_ptr_labels_rest), (iptr)str_democrats, (iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite, 0);
                game.field_0c = game.field_0c | 0x20;
            }
        }
    }
    else {
        net_send_message(0x9f, *(i32 *)
                                 (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ2 * 4) * 0x54),
                           all_govs, 0, 0, 0, 0, 0, 0, 0);
    }
    /* funclet 0055c679 */
    dialog_dtor(&dlg);
}

/* 0x00493e83: builds a temporary object, stores civ in it, runs it if
   its check succeeds, then destroys it. */
void __cdecl portrait_dlg_show(i32 civ)
{
    int created;
    PortraitDialog portrait_dlg;

    portrait_dlg_ctor(&portrait_dlg);
    portrait_dlg.portrait_civ = civ;
    created = portrait_dlg_create(&portrait_dlg);
    if (created != 0) {
        portrait_dlg_run(&portrait_dlg);
    }
    /* funclet 00493eeb: lea ecx,[ebp-0x1f4] */
    portrait_dlg_dtor((PortraitDlgDtorView*)(&portrait_dlg));
}

/* 0x005e0863: builds a window with "OK"/"Cancel" buttons on the stack and
   tears it all down again; returns 0. */
i32 __cdecl FUN_005e0863(void)
{
    int btn_y;
    int btn_x;
    i8 ok_button[60];
    i8 font2[8];
    i8 palette[1076];
    SurfaceWindow surf_wnd2;
    i8 cancel_button[60];
    i8 edit[72];
    tagRECT btn_rect;

    palette_init((GamePalette*)(palette));
    surfwnd_ctor(&surf_wnd2);
    font_init_empty((GameFont*)(font2));
    button_ctor((Control*)(ok_button));
    button_ctor((Control*)(cancel_button));
    edit_ctor((InputControl*)(edit));
    font_set((GameFont*)(font2), 0, 0x11);
    ui_set_button_font((iptr)font2);
    ui_set_default_font((iptr)font2);
    SetRect(&btn_rect, 0, 0, 0x3c, 0x19);
    btn_y = surface_get_height((DibSurface*)(&surf_wnd2));
    btn_y = btn_y + -0x23;
    btn_x = surface_get_width((DibSurface*)(&surf_wnd2));
    OffsetRect(&btn_rect, btn_x + -0x46, btn_y);
    button_create((Control*)(ok_button), (i32)surf_wnd2.window_2, 0x65, (i32)&btn_rect,
                       (i32)((i32 *)&str_ok_3));
    button_set_callback((Control*)(ok_button), (i32)dlg_radio_choice_button_cb);
    OffsetRect(&btn_rect, 0, -0x23);
    button_create((Control*)(cancel_button), (i32)surf_wnd2.window_2, 0x66, (i32)&btn_rect,
                       (i32)str_cancel_3);
    button_set_callback((Control*)(cancel_button), (i32)dlg_radio_choice_button_cb);
    /* funclets 005e0a31..005e0a6a: destroy the locals in reverse order */
    edit_dtor((Control*)(edit));
    ctrl_dtor((Control*)(cancel_button));
    ctrl_dtor((Control*)(ok_button));
    font_destroy((GameFont*)(font2));
    surfwnd_dtor(&surf_wnd2);
    palette_destroy((GamePalette*)(palette));
    return 0;
}

/* 0x004d53ab: loads picture 0x1f1 and cuts it into six button images
   (two rows of three; the second row's caption depends on the language). */
void __thiscall spaceship_wnd_make_button_sprites(void *self)
{
    int loaded;
    i32 label_text;
    i8 surface[72];
    tagRECT rect;

    surface_ctor((DibSurface*)(surface));
    gfx_set_text_color_index(0x8b);
    loaded = surface_load_gif_resource((DibSurface*)(surface), 0x1f1, 10, 0xec, (iptr)self + 0x1f8);
    if (loaded != 0) {
        text_clear();
        label_text = (i32)label_string(*(i32 *)(label_string_ids + 0x3f8));
        text_append(label_text);
        SetRect(&rect, 0, 0, 0x34, 0x24);
        OffsetRect(&rect, 1, 1);
        surface_draw_text_in_rect((DibSurface*)(surface), (iptr)self + 0x8d4, (i32)((i8 *)&map_views_block.text_buffer), (iptr)&rect, 0);
        sprite_grab_from_surface((Sprite *)((iptr)self + 0x978), (i32)surface, 9, 1, 1, 0x34, 0x24);
        OffsetRect(&rect, 0x35, 0);
        surface_draw_text_in_rect((DibSurface*)(surface), (iptr)self + 0x8d4, (i32)((i8 *)&map_views_block.text_buffer), (iptr)&rect, 0);
        sprite_grab_from_surface((Sprite *)((iptr)self + 0x9f0), (i32)surface, 9, 0x36, 1, 0x34, 0x24);
        OffsetRect(&rect, 0x35, 0);
        surface_draw_text_in_rect((DibSurface*)(surface), (iptr)self + 0x8d4, (i32)((i8 *)&map_views_block.text_buffer), (iptr)&rect, 0);
        sprite_grab_from_surface((Sprite *)((iptr)self + 0x9b4), (i32)surface, 9, 0x6b, 1, 0x34, 0x24);
        gfx_set_text_color_index(0xc6);
        text_clear();
        if (game_language == 0) {
            label_text = (i32)label_string(*(i32 *)(label_string_ids + 0x354));
            text_append(label_text);
        }
        else if (game_language == 1) {
            text_append((iptr)str_lancer);
        }
        else if (game_language == 2) {
            text_append((iptr)str_starten);
        }
        SetRect(&rect, 0, 0, 0x43, 0x24);
        OffsetRect(&rect, 1, 0x26);
        surface_draw_text_in_rect((DibSurface*)(surface), (iptr)self + 0x8d4, (i32)((i8 *)&map_views_block.text_buffer), (iptr)&rect, 0);
        sprite_grab_from_surface((Sprite *)((iptr)self + 0xa2c), (i32)surface, 9, 1, 0x26, 0x43, 0x24);
        OffsetRect(&rect, 0x44, 0);
        surface_draw_text_in_rect((DibSurface*)(surface), (iptr)self + 0x8d4, (i32)((i8 *)&map_views_block.text_buffer), (iptr)&rect, 0);
        sprite_grab_from_surface((Sprite *)((iptr)self + 0xaa4), (i32)surface, 9, 0x45, 0x26, 0x43, 0x24);
        OffsetRect(&rect, 0x44, 0);
        surface_draw_text_in_rect((DibSurface*)(surface), (iptr)self + 0x8d4, (i32)((i8 *)&map_views_block.text_buffer), (iptr)&rect, 0);
        sprite_grab_from_surface((Sprite *)((iptr)self + 0xa68), (i32)surface, 9, 0x89, 0x26, 0x43, 0x24);
    }
    /* funclet 004d56ea: lea ecx,[ebp-0x64] */
    surface_dtor((DibSurface*)(surface));
}
