#include "../include/map.h"

int gMap[ROWS][COLS];

static void fill(int r1,int c1,int r2,int c2,int t){
    for(int r=r1;r<=r2;r++)
        for(int c=c1;c<=c2;c++)
            gMap[r][c]=t;
}

static void room(int r1,int c1,int r2,int c2){
    for(int r=r1;r<=r2;r++)
        for(int c=c1;c<=c2;c++)
            if(r==r1||r==r2||c==c1||c==c2) gMap[r][c]=TILE_WALL;
            else gMap[r][c]=TILE_FLOOR;
}

void map_init(){
    fill(0,0,ROWS-1,COLS-1,TILE_EMPTY);

    room(0, 0,  9, 19);
    room(0, 20, 9, 39);
    room(10,0,  19,19);
    room(10,20, 19,39);
    room(20,0,  ROWS-1,19);
    room(20,20, ROWS-1,39);

    gMap[1][1]       = TILE_CLOSET;
    gMap[ROWS-2][38] = TILE_CLOSET;

    gMap[4][19] = TILE_DOOR;
    gMap[4][20] = TILE_DOOR;

    gMap[9][9]  = TILE_DOOR;
    gMap[10][9] = TILE_DOOR;

    gMap[9][29] = TILE_DOOR;
    gMap[10][29]= TILE_DOOR;

    gMap[14][19]= TILE_DOOR;
    gMap[14][20]= TILE_DOOR;

    gMap[19][9] = TILE_DOOR;
    gMap[20][9] = TILE_DOOR;

    gMap[19][29]= TILE_DOOR;
    gMap[20][29]= TILE_DOOR;
}

bool map_can_walk(int r,int c){
    if(r<0||r>=ROWS||c<0||c>=COLS) return false;
    int t=gMap[r][c];
    return t==TILE_FLOOR||t==TILE_DOOR||t==TILE_CLOSET;
}

int map_get_tile(int r,int c){
    if(r<0||r>=ROWS||c<0||c>=COLS) return TILE_EMPTY;
    return gMap[r][c];
}

int map_get_room(int r,int c){
    if(r>=0  && r<=9  && c>=0  && c<=19) return 1;
    if(r>=0  && r<=9  && c>=20 && c<=39) return 2;
    if(r>=10 && r<=19 && c>=0  && c<=19) return 3;
    if(r>=10 && r<=19 && c>=20 && c<=39) return 4;
    if(r>=20 && r<=ROWS-1 && c>=0  && c<=19) return 5;
    if(r>=20 && r<=ROWS-1 && c>=20 && c<=39) return 6;
    return 1;
}
