/* Windows, dialogs and menus.
 * Declarations only, in the original's address order; the definitions are in
 * src/data/gamedata.cpp (see src/data/gamedata.h). */
#ifndef CIV2_STATE_WINDOW_H
#define CIV2_STATE_WINDOW_H

extern int mp_cheat_menu_allowed[1];
extern RODATA i8 game_options_version_sep_str[4];
extern RODATA i8 mp_options_vote_sep_str[4];
extern int dialog_clamp_overflow;
extern RODATA i8 dialog_title_label_space_str[4];
extern RODATA i8 caption_status_open_paren_str[4];
extern RODATA i8 caption_ai_fr_str[4];
extern RODATA i8 caption_ai_str[4];
extern RODATA i8 caption_moves_space_str[4];
extern RODATA i8 caption_timer_sep_str[4];
extern RODATA i8 caption_close_paren_str[4];
extern RODATA i8 caption_simul_open_paren_str[4];
extern RODATA i8 caption_simul_ai_fr_str[4];
extern RODATA i8 caption_simul_ai_str[4];
extern RODATA i8 caption_simul_space_str[4];
extern RODATA i8 caption_simul_timer_sep_str[4];
extern RODATA i8 caption_simul_close_paren_str[4];
extern RODATA i8 caption_timer_open_paren_str[4];
extern RODATA i8 caption_timer_close_paren_str[4];
extern i8 frame_default_title_str[24];  /* only FrameWindow::create uses it */
extern i32 frame_texture_loaded_i32;  /* only frame_texture_load uses it */
/* The menu being tracked. */
#pragma pack(push, 1)
typedef struct MenuState {
    ModalMenuWindow *owner_window;  /* 00634304 */
    GameMenu *active_object;  /* 00634308 */
    MenuCommandFn command_callback;  /* 0063430c */
} MenuState;
#pragma pack(pop)
extern MenuState menu_state;
extern RODATA i8 menu_title_sep_str[8];
extern int main_frame_created;
extern u8 main_frame_created_rest[4];
/* Where the next dialog opens. */
#pragma pack(push, 1)
typedef struct DialogDefaults {
    iptr palette;  /* 006359c0 */
    iptr parent_window;  /* 006359c4 */
    i32 saved_parent_window;  /* 006359c8 */
    i32 x;  /* 006359cc */
    i32 y;  /* 006359d0 */
} DialogDefaults;
#pragma pack(pop)
extern DialogDefaults dlg_defaults;
extern RODATA i8 dialog_wrap_space_str[4];
extern RODATA i8 dlg_key_text_str[8];
extern RODATA i8 dlg_key_y_prefix[4];
extern RODATA i8 dlg_key_x_prefix[4];
extern int ms_window_stack_count;
extern i8 hotspot_wnd_title[4];  /* only hotspot_create_hwnd uses it */
extern HMENU menu_next_item_id;
extern RODATA i8 menu_separator_tag[8];
extern uint ddwin_last_activate_app;  /* only ddwin_native_wndproc uses it */
extern u8 scroll_up_button_sprite[64];
extern u8 caption_view_mode_button_sprite[64];
extern u8 caption_zoom_out_sprite[64];
#pragma pack(push, 1)
struct caption_small_font_block {
    GameFont caption_small_font;  /* 006ab178 */
    i32 screen_rect[1];  /* 006ab180 */
    i32 screen_rect_top;  /* 006ab184 */
    i32 ui_screen_rect_right;  /* 006ab188 */
    i32 ui_screen_rect_bottom;  /* 006ab18c */
};
#pragma pack(pop)
extern struct caption_small_font_block caption_small_font_block;
extern GameFont ui_text_font[3];
/* The dialog running and when its timeout started. */
#pragma pack(push, 1)
typedef struct DialogState {
    i32 timeout_start;  /* 006cec80 */
    Dialog *active;  /* 006cec84 */
} DialogState;
#pragma pack(pop)
#pragma pack(push, 1)
struct dialog_title_font_obj_block {
    GameFont dialog_title_font_obj;  /* 006cec78 */
    DialogState dialog_state;  /* 006cec80 */
};
#pragma pack(pop)
extern struct dialog_title_font_obj_block dialog_title_font_obj_block;
inline constexpr DialogState &dialog_state = dialog_title_font_obj_block.dialog_state;
extern GameFont dialog_list_font_obj;
#pragma pack(push, 1)
struct dialog_plain_font_obj_block {
    GameFont dialog_plain_font_obj;  /* 006cec90 */
    i32 dialog_button_label_ids[4];  /* 006cec98 */
};
#pragma pack(pop)
extern struct dialog_plain_font_obj_block dialog_plain_font_obj_block;
extern int moving_units_mode;
extern u8 moving_units_mode_rest[12];
#pragma pack(push, 1)
struct ms_window_stack_block {
    union {
        struct {
            i8 ms_window_stack[4];  /* 006d1db8 */
            i8 ms_window_stack_elem1[268];  /* 006d1dbc */
        };
        i32 ms_window_stack_entries[68];  /* 006d1db8 */
    };
};
#pragma pack(pop)
extern struct ms_window_stack_block ms_window_stack_block;

#endif
