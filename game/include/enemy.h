#ifndef ENEMY_H
#define ENEMY_H
#include "types.h"
struct Enemy {
    Vec2 pos;
    int  type;
    bool active;
    int  patrolIdx;
    bool chasing;
    int  tickCounter;
    Vec2 patrol[MAX_PATROL];
    int  patrolLen;
    Vec2 lastKnownPlayer;
};
void enemy_init_all(Enemy *enemies, int maxCount);
void enemy_update(Enemy *e, Vec2 playerPos);
int  enemy_dist(Vec2 a, Vec2 b);
bool enemy_catches(const Enemy *e, Vec2 playerPos);
void enemy_activate_conscience(Enemy *enemies, int maxCount);
int  enemy_who_caught(const Enemy *enemies, int count, Vec2 playerPos);
#endif
