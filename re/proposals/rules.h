/*
 * Proposal: RULES.TXT tables (@COSMIC, @CIVILIZE, @IMPROVE, @ENDWONDER,
 * @TERRAIN, @GOVERNMENTS, @LEADERS, @CARAVAN, @ORDERS, @DIFFICULTY,
 * @ATTITUDES).
 *
 * Evidence:
 *  - Loader rules_parse_sections calls the per-section parsers rules_load_cosmic (COSMIC),
 *    rules_load_advances (CIVILIZE), rules_load_improvements (IMPROVE+ENDWONDER), rules_load_units
 *    (UNITS), FUN_0041a95f (TERRAIN), FUN_0041ab18 (GOVERNMENTS+LEADERS) and
 *    then parses CARAVAN/ORDERS/DIFFICULTY/ATTITUDES inline.
 *  - The multiplayer table-sync switch (net_msg_build_packet / FUN_005f2110 callers,
 *    cases 0x17..0x24) sends each table as one block with its exact size:
 *    cosmic 0x64bcc8/0x29, advances 0x627680/0x640, improvements
 *    0x64c488/0x218, endwonder 0x64ba28/0x1c, unit types 0x64b1b8/0x4d8,
 *    terrain 0x627cc0/0x318, gov names 0x64b9a0/0x1c, gov titles
 *    0x654fe0/0x38, leaders 0x6554f8/0x3f0, commodities 0x64b168/0x40,
 *    orders 0x655490/0x68, difficulty 0x64ba10/0x18, attitudes 0x64b9c0/0x24.
 *    This fixes the bases: advances and terrain start 4 bytes before the
 *    name field, with a static 4-char abbreviation ("AFl", "Drt") that the
 *    prerequisite lookups rules_parse_advance_abbrev / rules_parse_terrain_abbrev strcmp against.
 *  - "Names" are NOT char pointers: text_next_token_str_id -> strpool_add_padded and
 *    text_next_token_pooled -> strpool_add copy the text into a string pool and return
 *    a running string id (strpool_count++); readers turn ids back into text
 *    with label_string(id).  So every name field is a fixed-width integer id
 *    and all these tables have the same layout on 32/64-bit.  (NB: the same
 *    holds for UnitType.name at +0x00 -- it is an i32 string id, not char *;
 *    rules_load_units stores the real pointer separately in unit_type_name_ptrs[62].)
 *  - Leader records are written to save files 0x30 bytes at a time
 *    (FUN at decomp.c:46406 fwrite(&leaders[i], 0x30)) and fields +3/+4/+5
 *    are saved individually, so Leader goes inside the pack(1) block.
 *  - Value meanings from the RULES.TXT comments; ranges are those of the
 *    clamp int_clamp(v, lo, hi) used by the parser.
 *  - Prerequisite/terrain-result codes: advances "nil" = -1 (none),
 *    "no" = -2 (never); terrain "no" = -1 (cannot), "yes" = -2 (improves in
 *    place); -3 = parse error.  Both compared signed -> i8.
 */

#pragma pack(push, 1)

/* One civilization (tribe) definition from @LEADERS (0x30 bytes; 21 slots,
 * saved verbatim).  All "name" fields are string ids (label_string). */
typedef struct Leader {
    i8 attack;              /* 0x00 1 aggressive, -1 rational */
    i8 expand;              /* 0x01 1 expansionist, -1 perfectionist */
    i8 civilize;            /* 0x02 1 civilized, -1 militaristic */
    u8 times_used;          /* 0x03 incremented each time the tribe is picked for a civ */
    u8 female;              /* 0x04 0 male leader, 1 female (clamped 0..1) */
    u8 city_name_index;     /* 0x05 next city name to take from the tribe's list */
    i16 color;              /* 0x06 colour set 1..7 */
    i16 city_style;         /* 0x08 0 bronze age, 1 classical, 2 far east, 3 medieval */
    i16 leader_name;        /* 0x0a current leader name = names[female] */
    i16 plural;             /* 0x0c "Romans" */
    i16 adjective;          /* 0x0e "Roman" */
    i16 names[2];           /* 0x10 leader name: [0] male, [1] female */
    i16 titles[7][2];       /* 0x14 per government: [0] male, [1] female title */
} Leader;

#pragma pack(pop)

/* @COSMIC (0x29 bytes; one block, synced over the network as a whole). */
typedef struct Cosmic {
    u8 road_move_mult;          /* 0x00 road movement multiplier (1..10) */
    u8 trireme_loss_chance;     /* 0x01 1 in x chance trireme lost (1..100) */
    u8 food_per_citizen;        /* 0x02 food eaten per citizen per turn (0..10) */
    u8 food_box_rows;           /* 0x03 rows in food box (4..20, forced even) */
    u8 shield_box_rows;         /* 0x04 rows in shield box (4..20) */
    u8 settler_food_low;        /* 0x05 settlers eat, govt <= Monarchy (0..10) */
    u8 settler_food_high;       /* 0x06 settlers eat, govt >= Communism (0..10) */
    u8 unhappy_size;            /* 0x07 city size for first unhappiness at Chieftain (4..12) */
    u8 riot_factor;             /* 0x08 riot factor based on number of cities (10..100) */
    u8 aqueduct_size;           /* 0x09 aqueduct needed to exceed this size (4..50) */
    u8 sewer_size;              /* 0x0a sewer system needed to exceed this size (4..50) */
    u8 tech_paradigm;           /* 0x0b higher slows research (3..10) */
    u8 transform_time;          /* 0x0c base engineer transform time, x2 (5..100) */
    u8 monarchy_free_support;   /* 0x0d monarchy pays support past this (0..8) */
    u8 communism_free_support;  /* 0x0e (0..8) */
    u8 fundamentalism_free_support; /* 0x0f (0..8) */
    u8 communism_palace_dist;   /* 0x10 communism equivalent palace distance (1..20) */
    u8 fund_science_loss;       /* 0x11 percent science lost under fundamentalism (0..100) */
    u8 change_penalty;          /* 0x12 percent shield penalty for production change (0..100) */
    u8 paradrop_range;          /* 0x13 max paradrop range (4..100) */
    u8 mass_thrust_paradigm;    /* 0x14 spaceship mass/thrust paradigm (25..200) */
    u8 fund_max_science;        /* 0x15 max science rate under fundamentalism, x10 (0..10) */
    u8 reserved[19];            /* 0x16 never accessed; part of the 0x29-byte sync block */
} Cosmic;

/* One civilization advance from @CIVILIZE (0x10 bytes; 100 slots). */
typedef struct Advance {
    char abbrev[4];         /* 0x00 static "AFl", "Alp", ... (not from RULES.TXT) */
    i32 name;               /* 0x04 string id */
    u8 field_08;            /* 0x08 never accessed */
    u8 enabled;             /* 0x09 0 when preq[0] == -2 ("no": never available) */
    i8 ai_value;            /* 0x0a basic AI value */
    i8 civilized_mod;       /* 0x0b AI value modifier for civilized leaders */
    u8 category;            /* 0x0c 0 military, 1 economic, 2 social, 3 academic, 4 applied */
    u8 epoch;               /* 0x0d 0 ancient, 1 renaissance, 2 industrial, 3 modern */
    i8 preq[2];             /* 0x0e prerequisites; -1 nil, -2 no */
} Advance;

/* One city improvement or wonder from @IMPROVE (8 bytes; 67 slots:
 * 0..38 improvements, 39..66 wonders). */
typedef struct Improvement {
    i32 name;               /* 0x00 string id */
    u8 cost;                /* 0x04 shields x10 */
    u8 upkeep;              /* 0x05 gold per turn */
    i8 preq;                /* 0x06 advance required, -1 nil, -2 no */
    u8 pad_07;
} Improvement;

/* One terrain type from @TERRAIN (0x18 bytes; 33 slots: 0..10 base
 * terrains, 11..32 two special resources per base terrain). */
typedef struct Terrain {
    char abbrev[4];         /* 0x00 static "Drt", "Pln", ... */
    i32 name;               /* 0x04 string id */
    u8 move_cost;           /* 0x08 */
    u8 defense;             /* 0x09 x50% */
    u8 food;                /* 0x0a */
    u8 shields;             /* 0x0b */
    u8 trade;               /* 0x0c */
    i8 transform_to;        /* 0x0d terrain engineers transform to, -1 no */
    i8 irrigate_to;         /* 0x0e -2 yes (bonus), -1 no, else terrain it becomes */
    i8 mine_to;             /* 0x0f */
    u8 irrigate_bonus;      /* 0x10 extra production from irrigating */
    u8 mine_bonus;          /* 0x11 */
    u8 irrigate_turns;      /* 0x12 settler turns */
    u8 mine_turns;          /* 0x13 */
    u8 irrigate_ai_govt;    /* 0x14 min govt for AI to irrigate (0 never .. 6 democracy) */
    u8 mine_ai_govt;        /* 0x15 */
    u8 pad_16[2];
} Terrain;

/* Male/female leader title for one government from @GOVERNMENTS (8 bytes). */
typedef struct GovTitle {
    i32 male;               /* 0x00 string id */
    i32 female;             /* 0x04 string id */
} GovTitle;

/* One unit order from @ORDERS (8 bytes; index = Unit.orders, 0 unused). */
typedef struct OrderName {
    i32 name;               /* 0x00 string id */
    char key;               /* 0x04 first char of the key column */
    u8 pad_05[3];
} OrderName;
