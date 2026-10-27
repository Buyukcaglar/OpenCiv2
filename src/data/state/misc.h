/* Data no code names: kept so that everything else lies where the original has it.
 * Declarations only, in the original's address order; the definitions are in
 * src/data/gamedata.cpp (see src/data/gamedata.h). */
#ifndef CIV2_STATE_MISC_H
#define CIV2_STATE_MISC_H

#pragma pack(push, 1)
struct throneroom_piece_rect_x_block {
    i8 throneroom_piece_rect_x[4];  /* 0061c068 */
    i8 throneroom_piece_rect_y[4];  /* 0061c06c */
    i8 throneroom_piece_rect_w[4];  /* 0061c070 */
    i8 throneroom_piece_rect_h[180];  /* 0061c074 */
    i8 throneroom_piece3_rect_x[4];  /* 0061c128 */
    i8 throneroom_piece3_rect_y[60];  /* 0061c12c */
};
#pragma pack(pop)
extern struct throneroom_piece_rect_x_block throneroom_piece_rect_x_block;
extern char str_r6002_floating_point_not_loaded[25600];
extern RODATA u8 tech_prereq_walk_count_rest[84];
extern u8 str_empty_142[4];
extern RODATA u8 ddwin_last_activate_app_rest[80];
extern RODATA u8 ddctrl_current_target_rest[60];
extern char str_empty_187[926];
extern char str_pdt[5376];

#endif
