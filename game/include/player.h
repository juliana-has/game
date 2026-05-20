#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"
struct Player {
    Vec2 pos;
    int  inventoryItem;
    bool inCloset;
    bool alive;
};
void player_init(Player *p);
bool player_move(Player *p, int dr, int dc);
bool player_pick(Player *p, int itemId);
void player_drop(Player *p);
bool player_is_in_closet(const Player *p);
#endif
