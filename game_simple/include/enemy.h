#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

struct Enemy {
    Vec2 pos;
    bool active;
    int  type;
    int  tick;
    Vec2 patrol[8];
    int  patrolLen;
    int  patrolIdx;
};

void  enemy_init_all(Enemy *enemies);
void  enemy_update(Enemy *e, Vec2 player);
bool  enemy_catches(Enemy *e, Vec2 player);
int   enemy_dist(Vec2 a, Vec2 b);

#endif
