#include "../include/game.h"
#include "../include/map.h"
#include "../include/audio.h"
#include <cstring>

static void setmsg(Game *g,const char *msg,int ticks){
    int i=0;
    while(msg[i]&&i<79){g->message[i]=msg[i];i++;}
    g->message[i]='\0';
    g->messageTicks=ticks;
}

void game_init(Game *g){
    map_init();
    player_init(&g->player);
    enemy_init_all(g->enemies);
    items_init(g->items);
    g->phase=PHASE_INTRO;
    g->killedBy=-1;
    g->conscienceOn=false;
    g->allCollected=false;
    g->message[0]='\0';
    g->messageTicks=0;
    g->ticks=0;
}

void game_update(Game *g,char key){
    if(g->phase!=PHASE_PLAY) return;
    g->ticks++;
    if(g->messageTicks>0) g->messageTicks--;

    int dr=0,dc=0;
    if(key=='w'||key=='W') dr=-1;
    if(key=='s'||key=='S') dr=1;
    if(key=='a'||key=='A') dc=-1;
    if(key=='d'||key=='D') dc=1;
    if(dr||dc){ bool moved=player_move(&g->player,dr,dc); if(moved) audio_play(SND_STEP); }

    if(key=='e'||key=='E'){
        if(g->player.item==ITEM_NONE){
            Item *it=items_nearby(g->items,g->player.pos.r,g->player.pos.c);
            if(it){
                it->collected=true;
                g->player.item=it->id;
                audio_play(SND_PICK);
                setmsg(g,"Recogiste un objeto. [R] para leer.",80);
            }
        }
    }

    if(key=='q'||key=='Q') g->player.item=ITEM_NONE;

    g->allCollected=(items_collected(g->items)>=MAX_ITEMS);

    for(int i=0;i<MAX_ENEMIES;i++) enemy_update(&g->enemies[i],g->player.pos);

    if(!g->player.hidden){
        for(int i=0;i<MAX_ENEMIES;i++){
            if(g->enemies[i].active&&enemy_dist(g->enemies[i].pos,g->player.pos)<=3)
                if(g->ticks%6==0) audio_play(SND_CHASE);
            if(enemy_catches(&g->enemies[i],g->player.pos)){
                audio_play(SND_DEAD);
                g->killedBy=i;
                g->phase=PHASE_DEAD;
                return;
            }
        }
    }

    if(g->player.hidden){ audio_play(SND_HIDE); }
    if(g->player.hidden&&g->allCollected){
        if(g->player.pos.r>=18&&g->player.pos.c>=36){
            g->phase=PHASE_WIN;
        }
    }
}
