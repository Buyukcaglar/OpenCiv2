/*
 * Proposal: per-civilization records (civs[8] at 0x64c6a0), their name block
 * (civ_names[8] at 0x64bcf8) and the global game state (game at 0x655ae8).
 *
 * Evidence:
 *  - Save routine FUN_004741be (writes "CIVILIZE", then version 0x2c) and
 *    loader FUN_00473660 move these as single blocks, in this order:
 *      fwrite(&0x655ae8, 0x14a)  game state
 *      fwrite(&0x64bcf8, 0x790)  8 x 0xf2 civ names
 *      fwrite(&0x64c6a0, 0x2ca0) 8 x 0x594 civ records
 *    So all three are saved verbatim -> pack(1), fixed-width fields only.
 *    (Save file offset = 0x0c + offset in GameState; matches the known .SAV
 *    format: difficulty at file 0x2c, human mask 0x2f, unit count 0x3a, ...)
 *  - The pre-0x28 loader branch of FUN_00473660 reads the same records
 *    piecewise, which gives the array boundaries exactly:
 *      game:  0x36 header | 0x5d @0x36 | 0x5d @0x9a | 0x4c @0xfe
 *      civ:   0x58 header | 0x0c @0x58 | 0x0e @0x66 | 0x5d @0x74 |
 *             3 x 0x36 @0xd8/0x116/0x154 | (1 byte skipped) | 0x402 @0x192
 *    (old saves had 93 advances / 54 unit types; now 100 / 62).
 *  - Field meanings from the code that uses them (function addresses are
 *    the original FUN_xxxxxxxx), checked against orig/Ca_Auto.SAV (turn 81,
 *    year -2400, Romans/Caesar human civ 1, despotism, rates sum <= 10, ...).
 *  - Key functions: FUN_004a7ce9 (initialise a civ), FUN_0053184d (AI
 *    per-turn census of units/cities, per-continent tables), FUN_004bf05b
 *    (give advance), FUN_004bd9f0 (civ knows advance), FUN_004c2788
 *    (research cost), FUN_004ea1f6 (split city trade by rates), FUN_00487a41
 *    (AI rates / government scores), FUN_0055f5a3 (AI picks government),
 *    FUN_004853e7 (power ranking), FUN_0049301b (add AI goal), FUN_00596eec
 *    (spaceship launch), FUN_0044cc80/0044db92 (throne room),
 *    FUN_0041ba52 (new game setup dialogs), FUN_00486c2e (global warming),
 *    FUN_00432611 (historians' report), FUN_00484fec (turn -> year).
 *
 * Uncertain: everything named field_XX; bit meanings of flags words are only
 * listed where the code makes them clear.  GameState.field_138/139 are
 * computed as power RANKS of the best/worst-ranked human civ, but several
 * readers index civs[] with them (probably an original bug or a
 * rank==civ confusion), so they are left unnamed.
 */

#pragma pack(push, 1)

/* An AI goal: go to / act at (x, y) with units of a role (6 bytes). */
typedef struct CivGoal {
    i16 x;                  /* 0x00 */
    i16 y;                  /* 0x02 */
    i8 role;                /* 0x04 unit role (UnitType.role), -1 = free slot */
    i8 priority;            /* 0x05 (negative = expires at end of turn) */
} CivGoal;

/* One civilization (0x594 bytes; 8 slots, index = civ id, 0 = barbarians;
 * saved verbatim). */
typedef struct Civ {
    u16 flags;                      /* 0x000 status bits (0x20 set on getting advance 60, 0x100 diplomacy, 0x200 ...) */
    i32 gold;                       /* 0x002 treasury */
    i16 tribe;                      /* 0x006 index into leaders[] (RULES.TXT @LEADERS) */
    i16 research_progress;          /* 0x008 beakers accumulated */
    i16 researching;                /* 0x00a advance being researched, -1 none */
    i16 capital_x;                  /* 0x00c x of the capital (palace) / start position; centres the world map */
    i16 last_city_turn;             /* 0x00e turn the last city was founded */
    u8 num_advances;                /* 0x010 advances known */
    u8 future_techs;                /* 0x011 future technologies discovered */
    u8 field_12;                    /* 0x012 added to num_advances in the research cost; only ever zeroed */
    u8 science_rate;                /* 0x013 in tenths; luxury = 10 - science - tax */
    u8 tax_rate;                    /* 0x014 in tenths */
    u8 government;                  /* 0x015 0 anarchy .. 6 democracy */
    u8 field_16;                    /* 0x016 rand() % 100, re-rolled every turn (FUN_00560084); AI diplomacy threshold */
    u8 wonders_by_group[4];         /* 0x017 wonders owned, counted per group of 7 (wonder index / 7) */
    u8 pad_1b;                      /* 0x01b */
    i16 field_1c;                   /* 0x01c +1 when a unit changes owner for gold (net handler FUN_0047e94e); AI gold logic */
    u8 reputation;                  /* 0x01e 0 spotless .. 7; incremented when a treaty is broken */
    i8 field_1f;                    /* 0x01f diplomacy counter: +1/+2 per request granted, AI refuses above 4 */
    u32 treaties[8];                /* 0x020 relationship flags toward each civ (contact, peace, alliance, war, ...) */
    u8 attitude[8];                 /* 0x040 AI attitude toward each civ (0..100) */
    i8 field_48[8];                 /* 0x048 per-civ incident counter (FUN_0045ac71), signed */
    u8 field_50[8];                 /* 0x050 per-civ counter updated by combat (FUN_00580341), reset at > 9 */
    u8 advances[13];                /* 0x058 bit per advance (100 bits), see FUN_004bd9f0 */
    u8 pad_65;                      /* 0x065 */
    i16 num_military_units;         /* 0x066 units with role < 5 (census FUN_0053184d) */
    i16 num_cities;                 /* 0x068 */
    i16 num_ships;                  /* 0x06a units of domain 2 (sea) */
    i16 total_city_size;            /* 0x06c sum of city sizes */
    u16 military_strength;          /* 0x06e sum of attack + defence of all units */
    i16 total_attack;               /* 0x070 sum of attack of all units */
    i16 population_milestone;       /* 0x072 last population milestone announced (FUN_00489292) */
    u8 advance_source[100];         /* 0x074 per advance: civ it was obtained from (0xff = none/initial) */
    u8 units_active[62];            /* 0x0d8 units alive, per unit type */
    u8 units_lost[62];              /* 0x116 units killed, per unit type (saturates at 255) */
    u8 units_in_production[62];     /* 0x154 cities building each unit type */
    u16 continent_military[64];     /* 0x192 military units per landmass */
    u16 continent_attack[64];       /* 0x212 total attack strength per landmass */
    u8 continent_cities[64];        /* 0x292 cities per landmass */
    u8 continent_city_size[64];     /* 0x2d2 sum of city sizes per landmass */
    u8 continent_trade_units[64];   /* 0x312 role-7 (trade) units per landmass */
    u8 continent_flags[64];         /* 0x352 AI: other civs present (1/2 cities, 4/8 units, 0x10 threat) */
    u8 continent_policy[64];        /* 0x392 AI posture per landmass (0..5) */
    i16 field_3d2;                  /* 0x3d2 zeroed each turn (FUN_00487a41), compared in FUN_00498e8b */
    i16 government_score[7];        /* 0x3d4 AI preference for each government, accumulated over cities */
    i16 last_treaty_turn[8];        /* 0x3e2 turn of the last treaty event with each civ, -1 never */
    u8 leader_portrait;             /* 0x3f2 tribe index, +21 if the leader is female */
    u8 throne_room[10];             /* 0x3f3 throne-room piece levels; [8] is a bitmask */
    u8 pad_3fd;                     /* 0x3fd */
    i16 throne_room_upgrades;       /* 0x3fe throne-room improvements earned */
    u8 spaceship_flags;             /* 0x400 bit 0x02 launched, 0x04, 0x08, 0x10 ... */
    u8 pad_401;                     /* 0x401 */
    i16 spaceship_arrival_year;     /* 0x402 */
    i16 spaceship_launch_year;      /* 0x404 */
    i16 spaceship_population;       /* 0x406 colonists, thousands */
    i16 spaceship_parts[6];         /* 0x408 structurals, 2 component kinds, 3 module kinds (costs at 0x634f68) */
    CivGoal ai_goals[48];           /* 0x414 current AI goals, sorted by priority */
    CivGoal ai_standing_goals[16];  /* 0x534 goals re-posted into ai_goals every turn (FUN_00493602) */
} Civ;

/* Names of one civilization (0xf2 bytes; 8 slots, saved verbatim).  Empty
 * strings mean "use the leaders[] defaults". */
typedef struct CivNames {
    i16 city_style;                 /* 0x00 overrides leaders[tribe].city_style for human civs */
    char leader_name[24];           /* 0x02 */
    char tribe_name[24];            /* 0x1a plural noun ("Romans") */
    char adjective[24];             /* 0x32 */
    char titles[7][24];             /* 0x4a leader title per government */
} CivNames;

/* Global game state (0x14a bytes, saved verbatim right after the header). */
typedef struct GameState {
    u16 rules;                      /* 0x000 custom features: 0x10 set unless Simplified Combat, 0x80 Bloodlust,
                                       0x100 Don't Restart Eliminated, 0x8000 Flat World */
    u32 game_options;               /* 0x002 @GAMEOPTIONS / @GRAPHICOPTIONS bits (saved to CIV.INI as 0x64bc1e) */
    u16 field_06;                   /* 0x006 transient flag bits (1, 2, 4) */
    u16 game_flags;                 /* 0x008 0x01 AI ganging up, 0x04 large map, 0x08 small map, 0x40 saved as
                                       scenario, 0x80 scenario */
    u16 message_options;            /* 0x00a @MESSAGEOPTIONS, bit set = message off */
    u16 field_0c;                   /* 0x00c one-shot event bits (each set once when its message is shown) */
    u16 field_0e;                   /* 0x00e only ever zeroed */
    i16 turn;                       /* 0x010 */
    i16 year;                       /* 0x012 negative = BC */
    i16 first_launch_turn;          /* 0x014 turn the first spaceship was launched, -1 none (years then +1/turn) */
    i16 active_unit;                /* 0x016 selected unit, -1 none */
    i16 moving_unit;                /* 0x018 unit being moved (kept across combat) */
    u8 multiplayer;                 /* 0x01a 0 single player, 1 hot seat, > 2 network */
    i8 player_civ;                  /* 0x01b the human player's civ */
    i8 field_1c;                    /* 0x01c copy of the current player civ (0x6d1da0) at save; restored on load */
    i8 turn_civ;                    /* 0x01d civ whose turn is being played */
    i8 view_civ;                    /* 0x01e cheat "view as" civ, -1 none */
    u8 reveal_map;                  /* 0x01f cheat: whole map visible */
    u8 difficulty;                  /* 0x020 0 chieftain .. 5 deity */
    u8 barbarian_activity;          /* 0x021 */
    u8 civs_alive;                  /* 0x022 bit per civilization in play */
    u8 human_players;               /* 0x023 bit per civilization */
    u8 civs_at_start;               /* 0x024 civs_alive when the game began */
    u8 num_enemies;                 /* 0x025 AI opponents (recomputed on load from civs_alive) */
    i8 warming_counter;             /* 0x026 global warming pressure 0..99, event above 16 */
    i8 global_warmings;             /* 0x027 global warming events so far */
    i16 field_28;                   /* 0x028 polluted-tile count weighted 1/2 in the warming check; reset after it */
    i16 polluted_tiles;             /* 0x02a */
    i16 field_2c;                   /* 0x02c +1 per turn after turn 200, reset in combat; AI chance factor */
    i16 num_units;                  /* 0x02e unit slots in use */
    i16 num_cities;                 /* 0x030 city slots in use */
    i16 num_advances;               /* 0x032 advances defined in RULES.TXT */
    i16 field_34;                   /* 0x034 only ever zeroed */
    u8 first_discoverer[100];       /* 0x036 per advance: civ that discovered it first (8 = several, scenarios) */
    u8 advance_known_by[100];       /* 0x09a per advance: bit per civ that knows it */
    i16 wonder_city[28];            /* 0x0fe city holding each wonder, -1 not built */
    i16 next_history_turn;          /* 0x136 turn of the next historians' report */
    u8 field_138;                   /* 0x138 power rank of the best-ranked human civ (see header note) */
    u8 field_139;                   /* 0x139 power rank of the worst-ranked human civ (see header note) */
    u8 power_rank[8];               /* 0x13a rank of each civ (7 = strongest) */
    u8 civ_by_rank[8];              /* 0x142 civ at each rank; [7] = strongest civ */
} GameState;

#pragma pack(pop)
