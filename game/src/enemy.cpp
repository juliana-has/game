#include "../include/enemy.h"
#include "../include/map.h"

static int absi(int x){return x<0?-x:x;}
static int signi(int x){return x>0?1:x<0?-1:0;}

int enemy_dist(Vec2 a,Vec2 b){return absi(a.r-b.r)+absi(a.c-b.c);}

static Vec2 step(Vec2 from,Vec2 to){
    int dr=to.r-from.r;
    int dc=to.c-from.c;
    Vec2 n=from;
    if(dr==0&&dc==0) return from;
    if(absi(dr)>=absi(dc)){
        int nr=from.r+signi(dr);
        if(map_can_walk(nr,from.c)){n.r=nr;return n;}
        if(dc!=0){
            int nc=from.c+signi(dc);
            if(map_can_walk(from.r,nc)){n.c=nc;return n;}
        }
        int nc2=from.c+(dc>=0?1:-1);
        if(map_can_walk(from.r,nc2)){n.c=nc2;return n;}
        nc2=from.c+(dc>=0?-1:1);
        if(map_can_walk(from.r,nc2)){n.c=nc2;return n;}
    } else {
        int nc=from.c+signi(dc);
        if(map_can_walk(from.r,nc)){n.c=nc;return n;}
        if(dr!=0){
            int nr=from.r+signi(dr);
            if(map_can_walk(nr,from.c)){n.r=nr;return n;}
        }
        int nr2=from.r+(dr>=0?1:-1);
        if(map_can_walk(nr2,from.c)){n.r=nr2;return n;}
        nr2=from.r+(dr>=0?-1:1);
        if(map_can_walk(nr2,from.c)){n.r=nr2;return n;}
    }
    return from;
}

void enemy_init_all(Enemy *enemies){
    Enemy *bf=&enemies[0];
    bf->type=0; bf->active=true; bf->tick=0; bf->patrolIdx=0;
    bf->pos.r=3; bf->pos.c=3;
    Vec2 p0[8]={{2,2},{2,17},{7,17},{7,2},{13,2},{13,17},{ROWS-3,2},{ROWS-3,17}};
    bf->patrolLen=8;
    for(int i=0;i<8;i++) bf->patrol[i]=p0[i];

    Enemy *con=&enemies[1];
    con->type=1; con->active=false; con->tick=0; con->patrolIdx=0;
    con->pos.r=ROWS-3; con->pos.c=37;
    Vec2 p1[4]={{ROWS-3,37},{ROWS-3,22},{ROWS-5,22},{ROWS-5,37}};
    con->patrolLen=4;
    for(int i=0;i<4;i++) con->patrol[i]=p1[i];
}

void enemy_update(Enemy *e,Vec2 player){
    if(!e->active) return;
    int speed=(e->type==0)?4:7;
    e->tick++;
    if(e->tick<speed) return;
    e->tick=0;

    int d=enemy_dist(e->pos,player);
    if(e->type==0){
        if(d<=12){
            e->pos=step(e->pos,player);
        } else {
            Vec2 wp=e->patrol[e->patrolIdx%e->patrolLen];
            if(enemy_dist(e->pos,wp)<=1) e->patrolIdx=(e->patrolIdx+1)%e->patrolLen;
            e->pos=step(e->pos,wp);
        }
    } else {
        e->pos=step(e->pos,player);
    }
}

bool enemy_catches(Enemy *e,Vec2 player){
    if(!e->active) return false;
    return enemy_dist(e->pos,player)<=1;
}
