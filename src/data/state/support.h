/* Errors, memory and debugging.
 * Declarations only, in the original's address order; the definitions are in
 * src/data/gamedata.cpp (see src/data/gamedata.h). */
#ifndef CIV2_STATE_SUPPORT_H
#define CIV2_STATE_SUPPORT_H

/* The last error and what was being done (error reports). */
#pragma pack(push, 1)
typedef struct ErrorState {
    int cleanup_count;  /* 00634768 */
    u8 cleanup_count_rest[4];
    i8 context_text[80];  /* 00634770 */
    i8 last_open_path[80];  /* 006347c0 */
    int last_open_failed;  /* 00634810 */
    uint last_alloc_failed;  /* 00634814 */
    i32 last_alloc_size;  /* 00634818 */
} ErrorState;
#pragma pack(pop)
extern ErrorState error_state;
extern RODATA i8 err_comment_prefix_str[4];
extern RODATA i8 err_dump_line_fmt[4];
extern RODATA i8 err_data_sep_str[4];
extern RODATA i8 err_fatal_msg_fmt[4];
extern RODATA i8 fatal_alloc_line_fmt[4];
extern RODATA i8 fatal_alloc_newline_str[4];
extern RODATA i8 fatal_dos_error_line_fmt[4];
extern RODATA i8 fatal_dos_error_newline_str[4];
extern int g_nr_seed;
/* Where debug messages go. */
#pragma pack(push, 1)
typedef struct DebugLogTargets {
    char file;  /* 00638304 */
    u8 file_rest[3];
    char debugger;  /* 00638308 */
    u8 debugger_rest[3];
} DebugLogTargets;
#pragma pack(pop)
extern DebugLogTargets dbg_log_to;
extern i8 err_format_empty_str[4];  /* only ErrorContext::format_message uses it */
extern char smeds_log_enabled;
extern u8 smeds_log_enabled_rest[3];
extern RODATA i8 dbg_log_header_crlf[4];
extern RODATA i8 dbg_log_header_blank_lines[8];
extern RODATA i8 dbg_log_file_crlf[4];
extern RODATA i8 dbg_log_debugger_crlf[8];

#endif
