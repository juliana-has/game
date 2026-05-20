#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "player.h"
#include "enemy.h"
#include "items.h"

struct Game {
    Player player;
    Enemy  enemies[MAX_ENEMIES];
    Item   items[MAX_ITEMS];
    int    phase;
    int    killedBy;
    bool   conscienceOn;
    bool   allCollected;
    char   message[80];
    int    messageTicks;
    int    ticks;
};

void game_init(Game *g);
void game_update(Game *g, char key);

#endif
