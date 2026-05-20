#include "../include/player.h"
#include "../include/map.h"

void player_init(Player *p){
    p->pos.r=4;
    p->pos.c=19;
    p->item=ITEM_NONE;
    p->alive=true;
    p->hidden=false;
}

bool player_move(Player *p,int dr,int dc){
    int nr=p->pos.r+dr;
    int nc=p->pos.c+dc;
    if(!map_can_walk(nr,nc)) return false;
    p->pos.r=nr;
    p->pos.c=nc;
    p->hidden=(map_get_tile(nr,nc)==TILE_CLOSET);
    return true;
}
