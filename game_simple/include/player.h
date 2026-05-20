#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

struct Player {
    Vec2 pos;
    int  item;
    bool alive;
    bool hidden;
};

void player_init(Player *p);
bool player_move(Player *p, int dr, int dc);

#endif
