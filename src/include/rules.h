/*
 * (port) The game's rules, in the code: what RULES.TXT's sections @COSMIC to
 * @LEADERS hold, as tables (src/game/rules.cpp).  Their names are texts by
 * key (lang.h), from the game's RULES.TXT:
 *   rules.advance.<n>, rules.improvement.<n>, rules.unit.<n>,
 *   rules.terrain.<n>, rules.government.<n> (.male, .female: the titles),
 *   rules.leader.<n>.male / .female / .plural / .adjective,
 *   rules.leader.<n>.title.<government>.male / .female,
 *   rules.commodity.<n>, rules.order.<n> (.key: its key), rules.difficulty.<n>,
 *   rules.attitude.<n>.
 * The rules loaders (src/auto/civ.cpp, rules_load_*) take them from here,
 * unless the scenario has a RULES.TXT of its own: that is read as before.
 */
#ifndef CIV2_RULES_H
#define CIV2_RULES_H

typedef struct RulesAdvance {
    i8 ai_value;
    i8 civilized_mod;
    i8 preq[2];             /* -1 nil, -2 no */
    u8 epoch;
    u8 category;
} RulesAdvance;

typedef struct RulesImprovement {
    u8 cost;
    u8 upkeep;
    i8 preq;
} RulesImprovement;

typedef struct RulesUnit {
    i8 obsolete_by;
    u8 domain;
    u8 move;                /* as in RULES.TXT: times cosmic.road_move_mult */
    u8 range;
    u8 attack;
    u8 defense;
    u8 hit_points;          /* as in RULES.TXT: times 10 */
    u8 firepower;
    u8 cost;
    u8 hold;
    u8 role;
    i8 prerequisite;
    u16 flags;
} RulesUnit;

typedef struct RulesTerrain {
    u8 move_cost;
    u8 defense;
    u8 yields[3];
    i8 improve_to[2];       /* the first 11 terrains only, as the rest below */
    u8 improve_bonus[2];
    u8 improve_turns[2];
    u8 improve_ai_govt[2];
    i8 transform_to;
} RulesTerrain;

typedef struct RulesLeader {
    u8 female;
    i16 color;
    i16 city_style;
    i8 attack;
    i8 expand;
    i8 civilize;
    int title_count;        /* the governments it has titles of its own for */
    int title_govts[7];
} RulesLeader;

#define RULES_COSMIC_SIZE 0x16      /* Cosmic's fields up to reserved */
extern const u8 rules_cosmic[RULES_COSMIC_SIZE];
extern const RulesAdvance rules_advances[];
extern const int rules_advance_count;
extern const RulesImprovement rules_improvements[67];
extern const i8 rules_wonder_expires[28];
extern const RulesUnit rules_units[];
extern const int rules_unit_count;
extern const RulesTerrain rules_terrain[33];
extern const RulesLeader rules_leaders[21];

/* Whether the rules are the scenario's own RULES.TXT (else these tables). */
int rules_from_scenario(void);

/* key's name (rules.unit.3 ...) added to the string pool as the parser
   added the name it read: padded to min_size / as it is. */
i32 rules_name(const char *key, int min_size);
i32 rules_name_pooled(const char *key);

#endif
