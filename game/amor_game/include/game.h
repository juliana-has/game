#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "player.h"
#include "enemy.h"
#include "items.h"

struct GameState {
    Player player;
    Enemy  enemies[MAX_ENEMIES];
    Item   items[MAX_ITEMS];
    int    itemCount;
    int    enemyCount;
    int    phase;
    int    introStep;
    bool   conscienceActive;
    bool   phoneRead;
    bool   allCollected;
    int    readingItem;
    int    tickCount;
    bool   roomVisited[MAX_ROOMS];   
    int    lastRoom;                 
    int    elapsedSeconds;          
    int    bestScore;                
    char   hudMessage[128];         
    int    hudMessageTicks;          
    int    killedBy;                 
};

void game_init(GameState *gs);
void game_tick(GameState *gs);
void game_handle_intro(GameState *gs);
bool game_is_over(const GameState *gs);
void game_reset(GameState *gs);

#endif 
