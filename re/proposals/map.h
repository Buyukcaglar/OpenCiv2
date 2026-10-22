/*
 * Proposal: world map (header, tile record, map layers).
 *
 * Evidence:
 *  - map_write 005b8635 / map_read 005b8783 fwrite/fread exactly 0xe bytes at
 *    0x6d1160 (the header), then (non-scenario) 7 per-civ layers of
 *    map.area bytes from 0x6365c0[1..7] (scenario: 2 x 0x2a bytes of start
 *    positions at 0x627fe0/0x628010 instead), then map.area*6 bytes of tiles
 *    from *0x636598.  So the tile record is 6 bytes and map.area = tile count.
 *  - map_alloc 005b7fe0: quarter_w = (width+3)>>2, quarter_h = (height+3)>>2,
 *    area = (width/2)*height; tiles initialised to {10,0,0,0,0,0} (ocean);
 *    allocates handles 0x6d1170 (tiles), 0x6365a0[1..7] (per-civ), 0x6d1174..
 *    0x6d1180 (4 coarse grids of quarter_w*quarter_h bytes), locks each into
 *    the pointer globals 0x636598 / 0x6365c0[] / 0x6365e0..0x6365ec, and sets
 *    0x6365f0 = 1.  map_free 005b8416 undoes it.
 *  - tile_at 005b8931: off-map -> &0x6d1188 (dummy tile), else
 *    tiles + (width&~1)*y*3 + (x&~1)*3, i.e. tiles[(width/2)*y + x/2]:
 *    width counts doubled (isometric) x coordinates, one record per x pair.
 *  - map.flat: set from game flag 0x655ae8 & 0x8000; when that flag is clear
 *    map_wrap_x 005ae052 wraps x around width (round world).
 *  - map.seed: map_new_seed 005b85fe = rand() & 0x7fff (never 0); used by
 *    tile_resource 005b8ee1 and tile_has_hut 005b8ffa to place specials/huts.
 *  - Tile bytes, from the accessors/setters:
 *      +0 terrain: tile_terrain = &0xf (10 = ocean, tile_is_ocean); bit 0x40
 *         suppresses the special resource (tile_resource); bit 0x80 river
 *         (tested all over movement/production code); tile_set_terrain keeps
 *         the high nibble.
 *      +1 improvements: tile_improvements; 0x01 unit present (tile_unit_owner),
 *         0x02 city ((&0x42)==2, tile_city_owner), 0x42 airbase
 *         (tile_airbase_owner), 0x40 fortress, 0x20 railroad, 0x08 mine,
 *         0x04 irrigation, 0x0c farmland, 0x80 pollution (tile_add_pollution
 *         sets 0x80).  Nuclear blast 005b9179 clears 0x40/0x20/0x08/0x04.
 *         0x10 = road per save-format knowledge (only weakly seen in code).
 *      +2 bits 5-7: civ whose city radius covers the tile (city founding
 *         0x43f7a7 writes the owner into the 21 radius tiles via
 *         tile_set_radius_civ 005b9c49); bits 0-4 unknown.
 *      +3 landmass / body of water id (tile_landmass, tile_set_landmass).
 *      +4 visibility: bit per civ (tile_visible_to 005b8b65, setter 005b976d).
 *      +5 high nibble: civ owning the unit/city on the tile, 0xf = none
 *         (tile_owner returns -1); low nibble unknown (setter 005b98b7,
 *         code keeps &7 / sets |8).
 *  - Per-civ layer 0x6365c0[civ] (civ 1..7): one byte per tile, the tile
 *    improvements as last seen by that civ (005b8b1a copies tile byte +1 into
 *    it; known_at 005b898b = layer + (width>>1)*y + (x>>1)).
 *  - Coarse grids 0x6365e0[0..3]: quarter_w x quarter_h bytes (one per 4x4
 *    block), cell = grid + quarter_w*y + x.  0055a980 fills [0] and [1] with
 *    per-direction connectivity bits (domain 0 / 1, likely land / sea path
 *    finding); [0],[1] are saved with the game.  Exact meaning of [2],[3]
 *    not recovered.
 *  - Start positions 0x627fe0 / 0x628010: 21 i16 each (-1 = none), indexed by
 *    tribe, passed as (x, y) to map_in_bounds; loaded only from scenarios
 *    (USESTARTLOC).
 */

#pragma pack(push, 1)

/* World map header (0x0e bytes at 0x6d1160, saved verbatim). */
typedef struct MapHeader {
    i16 width;          /* 0x00 in doubled x coordinates (tiles per row * 2) */
    i16 height;         /* 0x02 rows */
    i16 area;           /* 0x04 number of tiles = (width/2)*height */
    u16 flat;           /* 0x06 nonzero: flat world (no x wrap) */
    u16 seed;           /* 0x08 resource/hut placement seed, 1..0x7fff */
    i16 quarter_w;      /* 0x0a (width+3)/4: coarse-grid width */
    i16 quarter_h;      /* 0x0c (height+3)/4: coarse-grid height */
} MapHeader;

/* One map tile (6 bytes; area tiles, saved verbatim). */
typedef struct Tile {
    u8 terrain;         /* 0x00 bits 0-3 type (10 = ocean), 0x40 no special, 0x80 river */
    u8 improvements;    /* 0x01 0x01 unit, 0x02 city, 0x04 irrigation, 0x08 mine, 0x10 road,
                           0x20 railroad, 0x40 fortress, 0x42 airbase, 0x80 pollution */
    u8 radius;          /* 0x02 bits 5-7 civ whose city radius covers it; bits 0-4 unknown */
    u8 landmass;        /* 0x03 continent / body of water id */
    u8 visible;         /* 0x04 bit per civilization that has seen it */
    u8 owner;           /* 0x05 bits 4-7 civ of unit/city on it (0xf none); bits 0-3 unknown */
} Tile;

#pragma pack(pop)
