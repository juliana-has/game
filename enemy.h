#ifndef TYPES_H
#define TYPES_H

const int ROWS = 22;
const int COLS = 40;

const int TILE_EMPTY  = 0;
const int TILE_WALL   = 1;
const int TILE_FLOOR  = 2;
const int TILE_DOOR   = 3;
const int TILE_CLOSET = 4;

const int ITEM_NONE   = 0;
const int ITEM_PAPER  = 1;
const int ITEM_KEY    = 2;
const int ITEM_CANDLE = 3;
const int ITEM_PHONE  = 4;
const int ITEM_LETTER = 5;

const int MAX_ITEMS   = 5;
const int MAX_ENEMIES = 2;

const int PHASE_INTRO = 0;
const int PHASE_PLAY  = 1;
const int PHASE_DEAD  = 2;
const int PHASE_WIN   = 3;

struct Vec2 {
    int r;
    int c;
};

#endif
