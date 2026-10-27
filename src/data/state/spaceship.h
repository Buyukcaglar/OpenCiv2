/* The spaceship.
 * Declarations only, in the original's address order; the definitions are in
 * src/data/gamedata.cpp (see src/data/gamedata.h). */
#ifndef CIV2_STATE_SPACESHIP_H
#define CIV2_STATE_SPACESHIP_H

#pragma pack(push, 1)
struct spaceship_launch_sprite_xs_block {
    i8 spaceship_launch_sprite_xs[4];  /* 0062e250 */
    i8 spaceship_launch_sprite_ys[4];  /* 0062e254 */
    i8 spaceship_launch_sprite_widths[4];  /* 0062e258 */
    i8 spaceship_part_sprite_heights[116];  /* 0062e25c */
    SpaceshipWindow *spaceship_wnd;  /* 0062e2d0 */
};
#pragma pack(pop)
extern struct spaceship_launch_sprite_xs_block spaceship_launch_sprite_xs_block;
extern u8 str_empty_125[4];  /* only SpaceshipWindow::create uses it */
extern u8 str_empty_126[4];  /* only SpaceshipWindow::create uses it */
extern u8 str_empty_136[4];  /* only SpaceshipWindow::play_launch_video uses it */
#pragma pack(push, 1)
struct spaceship_part_table_block {
    union {
        struct {
            i8 spaceship_part_table[4];  /* 00634f60 */
            int spaceship_part_max_counts[1];  /* 00634f64 */
            i8 spaceship_part_masses[8];  /* 00634f68 */
            int spaceship_propulsion_max;  /* 00634f70 */
            u8 spaceship_propulsion_max_rest[8];
            int spaceship_fuel_max;  /* 00634f7c */
            u8 spaceship_fuel_max_rest[8];
            int spaceship_habitation_max;  /* 00634f88 */
            u8 spaceship_habitation_max_rest[8];
            int spaceship_life_support_max;  /* 00634f94 */
            u8 spaceship_life_support_max_rest[8];
            int spaceship_solar_panel_max;  /* 00634fa0 */
            u8 spaceship_solar_panel_max_rest[4];
        };
        SpaceshipPartKind spaceship_parts[6];  /* 00634f60 */
    };
};
#pragma pack(pop)
extern struct spaceship_part_table_block spaceship_part_table_block;
#pragma pack(push, 1)
struct editor_text_edit_block {
    u8 editor_text_edit[2920];  /* 006a4fa0 */
    i32 spaceship_wnd_open_ticks_i32;  /* 006a5b08 */
    u8 spaceship_wnd_open_ticks_i32_rest[4];
    union {
        struct {
            i8 spaceship_wnd_part_counts[4];  /* 006a5b10 */
            int spaceship_wnd_component_count;  /* 006a5b14 */
            u8 spaceship_wnd_component_count_rest[32];
        };
        i32 spaceship_wnd_part_count_list[10];  /* 006a5b10 */
    };
};
#pragma pack(pop)
extern struct editor_text_edit_block editor_text_edit_block;

#endif
