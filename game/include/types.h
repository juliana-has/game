#ifndef TYPES_H
#define TYPES_H
static const int COLS     = 30;
static const int ROWS     = 22;
static const int TILE     = 2;
static const int T_EMPTY  = 0;
static const int T_WALL   = 1;
static const int T_FLOOR  = 2;
static const int T_DOOR   = 3;
static const int T_CLOSET = 4;
static const int ROOM_NONE = 0;
static const int ROOM_1    = 1;
static const int ROOM_2    = 2;
static const int ROOM_3    = 3;
static const int ROOM_4    = 4;
static const int ROOM_5    = 5;
static const int ROOM_6    = 6;
static const int ROOM_7    = 7;
static const int ITEM_NONE   = 0;
static const int ITEM_PAPER1 = 1;
static const int ITEM_KEY    = 2;
static const int ITEM_CANDLE = 3;
static const int ITEM_PHONE  = 4;
static const int ITEM_PAPER2 = 5;
static const int ITEM_MAX    = 5;
static const int ENT_PLAYER    = 0;
static const int ENT_BOYFRIEND = 1;
static const int ENT_CONSCIENCE = 2;
static const int MAX_ITEMS   = 8;
static const int MAX_ENEMIES = 4;
static const int MAX_PATROL  = 16;
static const int PHASE_INTRO1   = 0;
static const int PHASE_INTRO2   = 1;
static const int PHASE_RUN      = 2;
static const int PHASE_PLAY     = 3;
static const int PHASE_READING  = 4;
static const int PHASE_DEAD     = 5;
static const int PHASE_WIN      = 6;
static const int PLAYER_SPEED    = 1;
static const int ENEMY_SPEED     = 4;
static const int CONSCIENCE_SPEED = 3;
static const int CHASE_RANGE     = 7;
static const int MAX_ROOMS = 8;
struct Vec2 {
    int r;
    int c;
};
#endif
