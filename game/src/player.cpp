#include "../include/player.h"
#include "../include/map.h"
void player_init(Player *p) {
    p->pos.r        = 3;
    p->pos.c        = 13;
    p->inventoryItem = ITEM_NONE;
    p->inCloset      = false;
    p->alive         = true;
}
bool player_move(Player *p, int dr, int dc) {
    int nr = p->pos.r + dr;
    int nc = p->pos.c + dc;
    if (!map_can_walk(nr, nc)) return false;
    p->pos.r   = nr;
    p->pos.c   = nc;
    p->inCloset = (map_get_tile(nr, nc) == T_CLOSET);
    return true;
}
bool player_pick(Player *p, int itemId) {
    if (p->inventoryItem != ITEM_NONE) return false;
    p->inventoryItem = itemId;
    return true;
}
void player_drop(Player *p) {
    p->inventoryItem = ITEM_NONE;
}
bool player_is_in_closet(const Player *p) {
    return p->inCloset;
}
