/*
 * (port) The game's text by key, not by its place in the game's text files.
 *
 * The program's structure (which menu item runs which command, ...) is in
 * the code; its text is looked up here by key ("menu.title.1",
 * "menu.1f1", ...).  The English text is built from the game's own files
 * (src/game/lang.cpp knows their layouts and versions); a translation is a
 * file of the same keys (lang/<code>.txt in the data directory, chosen with
 * CIV2_LANG=<code>) whose texts replace the English ones.  CIV2_EXPORT_TEXT=
 * <path> writes the English text as such a file, the start of a translation.
 *
 * Text file format: a line "@@key" starts an entry, the following lines up
 * to the next "@@" line are its text (one line for most keys); lines before
 * the first key are comments.
 */
#ifndef CIV2_LANG_H
#define CIV2_LANG_H

/* The text of key: its translation if there is one, else the English text;
   "" if neither has the key. */
const char *lang_text(const char *key);

/* Whether key has a text (a translation's or the English). */
int lang_has(const char *key);

/* The English menu texts, from MENU.TXT (the scenario's first, as the game
   reads its text files); called before the menus are built. */
void lang_load_menus(void);

/* The labels (LABELS.TXT, label_string_ids[n]: key "label.<n>"), once
   labels_load has read them: their English texts recorded, a translation's
   put in their place. */
void lang_add_labels(int count);

/* The translation of the string pool's string_id (a label), or 0. */
char *lang_pool_text(int string_id);

/* (port) The main menu bar: one row per menu title, item or separator, in
   order.  cmd: the command id (0 a separator, MENU_TITLE the menu's title);
   key: its text's key; room: the bytes its text has room for (the Orders
   items whose label the game changes, as for Build Road / Railroad). */
#define MENU_TITLE (-1)
typedef struct MenuRow {
    int menu;
    int cmd;
    const char *key;
    int room;
} MenuRow;
extern const MenuRow menu_rows[];
extern const int menu_row_count;

#endif
