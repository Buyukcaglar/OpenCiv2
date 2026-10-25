/*
 * (port) The game's text by key (src/include/lang.h).  The English text is
 * built from the game's text files with the game's own readers
 * (text_open_section, text_read_line: same trimming, the scenario's files
 * first), so it is the text the original shows; what each line of those
 * files is for, and how it differs between their versions, is known here
 * only.  A translation (lang/<code>.txt) replaces texts by key.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "game.h"
#include "lang.h"

EXTERN_C char plat_data_dir[];

/* The main menu bar, as menu_build_main built it from MENU.TXT. */
const MenuRow menu_rows[] = {
    {1, MENU_TITLE, "menu.title.1"},
    {1, 0x101, "menu.101"}, {1, 0x102, "menu.102"}, {1, 0x103, "menu.103"}, {1, 0x104, "menu.104"},
    {1, 0x105, "menu.105"}, {1, 0, 0}, {1, 0x106, "menu.106"}, {1, 0, 0},
    {1, 0x110, "menu.110"}, {1, 0x120, "menu.120"}, {1, 0x130, "menu.130"}, {1, 0, 0},
    {1, 0x131, "menu.131"}, {1, 0x132, "menu.132"}, {1, 0, 0}, {1, 0x1f0, "menu.1f0"}, {1, 0x1f1, "menu.1f1"},
    {2, MENU_TITLE, "menu.title.2"},
    {2, 0x201, "menu.201"}, {2, 0, 0}, {2, 0x205, "menu.205"}, {2, 0x210, "menu.210"}, {2, 0, 0},
    {2, 0x220, "menu.220"},
    {3, MENU_TITLE, "menu.title.3"},
    {3, 0x301, "menu.301"}, {3, 0x302, "menu.302"}, {3, 0, 0}, {3, 0x310, "menu.310"}, {3, 0x311, "menu.311"},
    {3, 0, 0}, {3, 0x321, "menu.321"}, {3, 0x322, "menu.322"}, {3, 0x324, "menu.324"}, {3, 0, 0},
    {3, 0x327, "menu.327"}, {3, 0x328, "menu.328"}, {3, 0x330, "menu.330"}, {3, 0x340, "menu.340"},
    {4, MENU_TITLE, "menu.title.4"},
    {4, 0x401, "menu.401", 0x3c}, {4, 0x410, "menu.410", 0x3c}, {4, 0x411, "menu.411", 0x3c}, {4, 0x412, "menu.412", 0x3c},
    {4, 0x413, "menu.413", 0x3c}, {4, 0, 0}, {4, 0x417, "menu.417"}, {4, 0x418, "menu.418"}, {4, 0x41b, "menu.41b"},
    {4, 0x420, "menu.420"}, {4, 0x421, "menu.421"}, {4, 0, 0}, {4, 0x430, "menu.430"}, {4, 0x440, "menu.440"},
    {4, 0x441, "menu.441"}, {4, 0x442, "menu.442"}, {4, 0x445, "menu.445", 0x3c}, {4, 0, 0}, {4, 0x450, "menu.450"},
    {4, 0x451, "menu.451"}, {4, 0, 0}, {4, 0x460, "menu.460"}, {4, 0x468, "menu.468"}, {4, 0x470, "menu.470"},
    {4, 0x480, "menu.480"}, {4, 0, 0}, {4, 0x490, "menu.490"},
    {5, MENU_TITLE, "menu.title.5"},
    {5, 0x507, "menu.507"}, {5, 0x500, "menu.500"}, {5, 0, 0}, {5, 0x501, "menu.501"}, {5, 0x502, "menu.502"},
    {5, 0x503, "menu.503"}, {5, 0, 0}, {5, 0x504, "menu.504"}, {5, 0x505, "menu.505"}, {5, 0x506, "menu.506"},
    {5, 0, 0}, {5, 0x508, "menu.508"},
    {6, MENU_TITLE, "menu.title.6"},
    {6, 0x601, "menu.601"}, {6, 0x602, "menu.602"}, {6, 0x603, "menu.603"}, {6, 0, 0}, {6, 0x605, "menu.605"},
    {6, 0x606, "menu.606"},
    {7, MENU_TITLE, "menu.title.7"},
    {7, 0x701, "menu.701"}, {7, 0, 0}, {7, 0x711, "menu.711"}, {7, 0x712, "menu.712"}, {7, 0x713, "menu.713"},
    {7, 0, 0}, {7, 0x721, "menu.721"}, {7, 0x722, "menu.722"}, {7, 0, 0}, {7, 0x731, "menu.731"},
    {7, 0x732, "menu.732"}, {7, 0x740, "menu.740"}, {7, 0x748, "menu.748"}, {7, 0x750, "menu.750"},
    {7, 0x752, "menu.752"}, {7, 0, 0}, {7, 0x755, "menu.755"}, {7, 0x760, "menu.760"}, {7, 0x765, "menu.765"},
    {7, 0, 0}, {7, 0x768, "menu.768"}, {7, 0x770, "menu.770"},
    {8, MENU_TITLE, "menu.title.8"},
    {8, 0x801, "menu.801"}, {8, 0, 0}, {8, 0x802, "menu.802"}, {8, 0x803, "menu.803"}, {8, 0x804, "menu.804"},
    {8, 0x805, "menu.805"}, {8, 0x806, "menu.806"}, {8, 0x807, "menu.807"}, {8, 0x808, "menu.808"},
    {8, 0x809, "menu.809"},
    {9, MENU_TITLE, "menu.title.9"},
    {9, 0x901, "menu.901"}, {9, 0x903, "menu.903"}, {9, 0x905, "menu.905"}, {9, 0x907, "menu.907"}, {9, 0, 0},
    {9, 0x909, "menu.909"}, {9, 0x90b, "menu.90b"}, {9, 0, 0}, {9, 0x90d, "menu.90d"}, {9, 0, 0},
    {9, 0x9f0, "menu.9f0"},
};
const int menu_row_count = (int)(sizeof menu_rows / sizeof menu_rows[0]);

/* English (from the game's files) and the translation's texts by key; the
   English keys in the order they were first set (for the export). */
static std::unordered_map<std::string, std::string> english, translated;
static std::vector<std::string> english_order;
static int translation_loaded;

static void set_english(const char *key, const char *text)
{
    std::string k(key);
    if (english.find(k) == english.end())
        english_order.push_back(k);
    english[k] = text ? text : "";
}

static void load_translation(void)
{
    const char *code = getenv("CIV2_LANG");
    char path[1200];
    char line[1024];
    std::string key, text;
    int lines = 0;
    FILE *f;

    translation_loaded = 1;
    if (!code || !*code || !strcmp(code, "en"))
        return;
    snprintf(path, sizeof path, "%s/lang/%s.txt", plat_data_dir, code);
    f = fopen(path, "r");
    if (!f)
        return;
    while (fgets(line, sizeof line, f)) {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0] == '@' && line[1] == '@') {
            if (!key.empty())
                translated[key] = text;
            key = line + 2;
            text.clear();
            lines = 0;
        } else if (!key.empty()) {
            if (lines++)
                text += '\n';
            text += line[0] == '\\' ? line + 1 : line;
        }
    }
    if (!key.empty())
        translated[key] = text;
    fclose(f);
}

/* A line that starts a section: "@NAME", NAME in capitals, digits and '_'
   (the lines in a section that start with '@' are in small letters:
   @title=, @width=, @options, ...).  name: NAME. */
static int section_header(const char *line, std::string *name)
{
    const char *p = line, *end;
    while (*p == ' ' || *p == '\t')
        p++;
    if (*p++ != '@')
        return 0;
    for (end = p; (*end >= 'A' && *end <= 'Z') || (*end >= '0' && *end <= '9') || *end == '_'; end++)
        ;
    if (end == p)
        return 0;
    if (name)
        name->assign(p, end);
    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')
        end++;
    return *end == 0;
}

/* The game's text files whose sections are keyed by file and section, in
   lower case ("game.MAINMENU"): their popups and other texts.  (MENU and
   LABELS have keys of their own; RULES is the game's rules; DESCRIBE, the
   Civilopedia's descriptions, has its own reader: add_descriptions.) */
static const char *const section_files[] = {
    "GAME", "CITY", "ADVICE", "HELP", "TUTORIAL", "COUNCIL0", "COUNCIL1", "COUNCIL2", "HERALD", "PEDIA",
    "MAPMENU", "DEBUG", "CREDITS", "SCREDITS", "FCREDITS", "MPCREDITS",
};

/* file's sections, as English texts: each one's lines (as the game's reader
   reads them, without the newline) up to the next section.  A name used
   twice: the first, the one the game finds.  @STOP and @END end lists (city
   names), they are no sections. */
static void add_file_sections(const char *file)
{
    char line[0x100];
    std::string prefix(file), name, text;
    int in_section = 0, lines = 0;
    size_t i;

    if (text_open_section(file, 0) != 0)
        return;
    for (i = 0; i < prefix.size(); i++)
        prefix[i] = (char)tolower((unsigned char)prefix[i]);
    prefix += '.';
    for (;;) {
        char *got = _fgets(line, 0xff, text_file_handle);
        if (got)
            line[strcspn(line, "\r\n")] = 0;
        if (!got || section_header(line, 0)) {
            if (in_section && !english.count(prefix + name))
                set_english((prefix + name).c_str(), text.c_str());
            if (!got)
                break;
            section_header(line, &name);
            in_section = name != "STOP" && name != "END";
            text.clear();
            lines = 0;
            continue;
        }
        if (lines++)
            text += '\n';
        text += line;
    }
    text_close_file();
}

/* RULES.TXT, its names: per section the lines the rules loaders read
   (rules_load_*, rules_parse_sections), their names the tokens they put in
   the string pool.  Read once, from the game's RULES.TXT (the rules of a
   scenario with its own are read from it, names and all). */
static void rules_section_names(const char *section, int count, const char *format, int stop_at_blank)
{
    char key[64];
    int i;
    if (text_open_section(0, section) != 0)
        return;
    for (i = 0; i < count; i++) {
        i8 *line = text_read_line(1);
        if (stop_at_blank && (!line || !*line || *line == ';'))
            break;
        snprintf(key, sizeof key, format, i);
        set_english(key, (const char *)text_next_token());
    }
}

void lang_load_rules(void)
{
    static int loaded;
    char key[64];
    int i, g;
    i8 *line;

    if (loaded)
        return;
    loaded = 1;
    if (text_open_section("RULES", 0) != 0)
        return;
    rules_section_names("CIVILIZE", 100, "rules.advance.%d", 1);
    rules_section_names("IMPROVE", 67, "rules.improvement.%d", 0);
    rules_section_names("UNITS", 62, "rules.unit.%d", 1);
    rules_section_names("TERRAIN", 33, "rules.terrain.%d", 0);
    if (text_open_section(0, "GOVERNMENTS") == 0)
        for (i = 0; i < 7; i++) {
            text_read_line(1);
            snprintf(key, sizeof key, "rules.government.%d", i);
            set_english(key, (const char *)text_next_token());
            snprintf(key, sizeof key, "rules.government.%d.male", i);
            set_english(key, (const char *)text_next_token());
            snprintf(key, sizeof key, "rules.government.%d.female", i);
            set_english(key, (const char *)text_next_token());
        }
    if (text_open_section(0, "LEADERS") == 0)
        for (i = 0; i < 21; i++) {
            static const char *const fields[] = {"male", "female", 0, 0, 0, "plural", "adjective", 0, 0, 0};
            size_t f;
            text_read_line(1);
            for (f = 0; f < sizeof fields / sizeof fields[0]; f++) {
                if (!fields[f]) {
                    text_next_int();
                    continue;
                }
                snprintf(key, sizeof key, "rules.leader.%d.%s", i, fields[f]);
                set_english(key, (const char *)text_next_token());
            }
            while ((g = text_next_int()) > 0) {
                snprintf(key, sizeof key, "rules.leader.%d.title.%d.male", i, g);
                set_english(key, (const char *)text_next_token());
                snprintf(key, sizeof key, "rules.leader.%d.title.%d.female", i, g);
                set_english(key, (const char *)text_next_token());
            }
        }
    rules_section_names("CARAVAN", 16, "rules.commodity.%d", 0);
    if (text_open_section(0, "ORDERS") == 0)
        for (i = 1; i < 13; i++) {
            text_read_line(1);
            snprintf(key, sizeof key, "rules.order.%d", i);
            set_english(key, (const char *)text_next_token());
            snprintf(key, sizeof key, "rules.order.%d.key", i);
            set_english(key, (const char *)text_next_token());
        }
    if (text_open_section(0, "DIFFICULTY") == 0)
        for (i = 0; i < 6; i++) {
            line = text_read_line(1);
            snprintf(key, sizeof key, "rules.difficulty.%d", i);
            set_english(key, line ? (const char *)line : "");
        }
    if (text_open_section(0, "ATTITUDES") == 0)
        for (i = 0; i < 9; i++) {
            line = text_read_line(1);
            snprintf(key, sizeof key, "rules.attitude.%d", i);
            set_english(key, line ? (const char *)line : "");
        }
    text_close_file();
}

/* "@ADVANCE_INDEX", "ADVANCE_DESCRIPTIONS", "TERRAIN_INDEX": the group of
   descriptions, "ADVANCE" ... (DESCRIBE.TXT's terrain is in the section
   TERRAIN_AND_RESOURCE_DESCRIPTIONS, after its @@TERRAIN_INDEX). */
static std::string description_group(const char *name)
{
    std::string g(name + strspn(name, "@"));
    size_t n;
    if ((n = g.rfind("_INDEX")) != std::string::npos && n + 6 == g.size())
        g.erase(n);
    else if ((n = g.rfind("_DESCRIPTIONS")) != std::string::npos && n + 13 == g.size())
        g.erase(n);
    return g;
}

/* DESCRIBE.TXT: per group an index (@@ADVANCE_INDEX, the rules' entries'
   descriptions: structure, no text) and the descriptions, each a line
   "@@name" and its paragraphs, one per line, up to the next line starting
   with '@' (pedia_load_description; it passes over ';' lines). */
static void add_descriptions(void)
{
    static char line[0x800];
    std::string group, key, text;
    int in_entry = 0, lines = 0;

    if (text_open_section("DESCRIBE", 0) != 0)
        return;
    for (;;) {
        char *got = _fgets(line, 0x800, text_file_handle);
        if (got)
            line[strcspn(line, "\r\n")] = 0;
        if (!got || line[0] == '@') {
            if (in_entry && !english.count(key))
                set_english(key.c_str(), text.c_str());
            if (!got)
                break;
            in_entry = 0;
            if (line[1] != '@') {
                group = description_group(line + 1);
            } else if (strstr(line, "_INDEX")) {
                group = description_group(line + 2);
            } else {
                std::string name(line + 2);
                name.erase(name.find_last_not_of(" \t") + 1);
                key = "describe." + group + "." + name;
                in_entry = 1;
                text.clear();
                lines = 0;
            }
            continue;
        }
        if (!in_entry || line[0] == ';')
            continue;
        if (lines++)
            text += '\n';
        text += line;
    }
    text_close_file();
}

const char *lang_description(const char *group, const char *entry)
{
    std::unordered_map<std::string, std::string>::const_iterator it;
    if (!translation_loaded)
        load_translation();
    if (translated.empty())
        return 0;
    it = translated.find("describe." + description_group(group) + "." + entry);
    return it != translated.end() ? it->second.c_str() : 0;
}

static void export_english(void)
{
    static int sections_added;
    const char *path = getenv("CIV2_EXPORT_TEXT");
    FILE *f;
    size_t i, start, end;
    if (!path || !*path)
        return;
    if (!sections_added) {
        sections_added = 1;
        for (i = 0; i < sizeof section_files / sizeof section_files[0]; i++)
            add_file_sections(section_files[i]);
        add_descriptions();
        lang_load_rules();
    }
    if (!(f = fopen(path, "w")))
        return;
    fprintf(f, "; OpenCiv2 text (English), keyed: \"@@key\" and its text on the lines after it\n"
               "; (a line of text that starts with \"@@\" or \"\\\" has a \"\\\" put before it).\n");
    for (i = 0; i < english_order.size(); i++) {
        const std::string &text = english[english_order[i]];
        fprintf(f, "@@%s\n", english_order[i].c_str());
        for (start = 0;; start = end + 1) {
            end = text.find('\n', start);
            if (end == std::string::npos)
                end = text.size();
            if (text.compare(start, 2, "@@") == 0 || text.compare(start, 1, "\\") == 0)
                fputc('\\', f);
            fprintf(f, "%.*s\n", (int)(end - start), text.c_str() + start);
            if (end == text.size())
                break;
        }
    }
    fclose(f);
}

const char *lang_text(const char *key)
{
    std::unordered_map<std::string, std::string>::const_iterator it;
    if (!translation_loaded)
        load_translation();
    it = translated.find(key);
    if (it != translated.end())
        return it->second.c_str();
    it = english.find(key);
    return it != english.end() ? it->second.c_str() : "";
}

int lang_has(const char *key)
{
    if (!translation_loaded)
        load_translation();
    return translated.count(key) || english.count(key);
}

/* MENU.TXT: per menu a section (@GAME ...), its title, then one line per
   item in the menu's order (menu_rows; separators have none).  Its
   versions: the 5.4.0f patch's @GAME has 13 items (with Game Profile,
   0x105), the CD's 12, without it (a 13th line that is no label: blank,
   the next @section, a comment).  The sections are read in one pass as
   the original did, which stopped at the first one missing. */
void lang_load_menus(void)
{
    static const char *const sections[9] = {
        str_game_5, str_kingdom, str_view, str_orders_2, str_advisors, str_world, str_cheat, str_editor, str_pedia_2,
    };
    char game_lines[13][0x100];
    int menu, row, n, has_profile;
    i32 pos = 0;
    i8 *line;

    for (menu = 1; menu <= 9; menu++) {
        if (text_open_section(menu == 1 ? str_menu : 0, sections[menu - 1]) != 0)
            break;
        for (row = 0; row < menu_row_count; row++)
            if (menu_rows[row].menu == menu && menu_rows[row].cmd == MENU_TITLE)
                set_english(menu_rows[row].key, text_read_line(1));
        if (menu == 1) {
            for (n = 0; n < 13; n++) {
                if (n == 12)
                    pos = _ftell(text_file_handle);
                line = text_read_line(1);
                snprintf(game_lines[n], sizeof game_lines[n], "%s", line ? (char *)line : "");
            }
            has_profile = game_lines[12][0] != 0 && game_lines[12][0] != '@' && game_lines[12][0] != ';';
            if (!has_profile && line)
                _fseek(text_file_handle, pos, 0);
            n = 0;
            for (row = 0; row < menu_row_count; row++)
                if (menu_rows[row].menu == 1 && menu_rows[row].cmd > 0 && (menu_rows[row].cmd != 0x105 || has_profile))
                    set_english(menu_rows[row].key, game_lines[n++]);
            continue;
        }
        for (row = 0; row < menu_row_count; row++)
            if (menu_rows[row].menu == menu && menu_rows[row].cmd > 0)
                set_english(menu_rows[row].key, text_read_line(1));
    }
    text_close_file();
    export_english();
}

/* LABELS.TXT is a numbered list (labels_load: label_string_ids[n] is the
   n-th line's string in the string pool); n is the structure, "label.<n>"
   the key.  A translated label is given by label_string in place of its
   pool string (the pool has a fixed size: translations are kept here). */
static std::unordered_map<int, std::string> pool_translated;

void lang_add_labels(int count)
{
    char key[32];
    int i;
    pool_translated.clear();        /* (a new pool: labels reloaded) */
    for (i = 0; i < count; i++) {
        snprintf(key, sizeof key, "label.%d", i);
        set_english(key, label_string(label_string_ids[i]));
    }
    if (!translation_loaded)
        load_translation();
    for (i = 0; i < count; i++) {
        snprintf(key, sizeof key, "label.%d", i);
        std::unordered_map<std::string, std::string>::const_iterator it = translated.find(key);
        if (it != translated.end())
            pool_translated[label_string_ids[i]] = it->second;
    }
    export_english();
}

char *lang_pool_text(int string_id)
{
    std::unordered_map<int, std::string>::iterator it;
    if (pool_translated.empty())
        return 0;
    it = pool_translated.find(string_id);
    return it != pool_translated.end() ? &it->second[0] : 0;
}

/* The translated section text_read_line reads: its lines, the next one, in
   which file; the file of the last section opened by name. */
static std::vector<std::string> section_lines;
static size_t section_next;
static FILE *section_file;
static std::string section_last_file;

void lang_section_opened(const char *filename, const char *section, int in_scenario)
{
    std::unordered_map<std::string, std::string>::const_iterator it;
    std::string key;
    const char *base;
    char line[0x100];
    i32 pos;
    size_t i, start, end;

    lang_section_closed();
    if (filename) {
        base = filename;
        for (i = 0; filename[i]; i++)
            if (filename[i] == '\\' || filename[i] == '/' || filename[i] == ':')
                base = filename + i + 1;
        section_last_file.assign(base, strcspn(base, "."));
        for (i = 0; i < section_last_file.size(); i++)
            section_last_file[i] = (char)tolower((unsigned char)section_last_file[i]);
    }
    if (!translation_loaded)
        load_translation();
    if (translated.empty() || in_scenario || !section)
        return;
    key = section_last_file + '.';
    for (i = 0; section[i]; i++)
        key += (char)toupper((unsigned char)section[i]);
    it = translated.find(key);
    if (it == translated.end())
        return;
    for (start = 0;; start = end + 1) {
        end = it->second.find('\n', start);
        if (end == std::string::npos)
            end = it->second.size();
        section_lines.push_back(it->second.substr(start, end - start));
        if (end == it->second.size())
            break;
    }
    /* the file's own lines of the section passed over: what comes after
       the translation is the file's next section */
    for (;;) {
        pos = _ftell(text_file_handle);
        if (!_fgets(line, 0xff, text_file_handle))
            break;
        if (section_header(line, 0)) {
            _fseek(text_file_handle, pos, 0);
            break;
        }
    }
    section_next = 0;
    section_file = text_file_handle;
}

int lang_section_line(char *buf)
{
    if (!section_file || section_file != text_file_handle)
        return 0;
    if (section_next >= section_lines.size()) {
        lang_section_closed();
        return 0;
    }
    snprintf(buf, 0xff, "%s", section_lines[section_next++].c_str());
    return 1;
}

void lang_section_closed(void)
{
    section_file = 0;
    section_lines.clear();
    section_next = 0;
}
