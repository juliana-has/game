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

    room(0, 0,  8, 18);
    room(0, 21, 8, 39);
    room(10,0,  18,18);
    room(10,21, 18,39);
    room(20,0,  ROWS-1,18);
    room(20,21, ROWS-1,39);

    gMap[1][1]       = TILE_CLOSET;
    gMap[ROWS-2][38] = TILE_CLOSET;

    gMap[4][18] = TILE_DOOR; gMap[4][19] = TILE_FLOOR; gMap[4][20] = TILE_FLOOR; gMap[4][21] = TILE_DOOR;
    gMap[9][8]  = TILE_DOOR; gMap[10][8] = TILE_FLOOR;
    gMap[9][30] = TILE_DOOR; gMap[10][30]= TILE_FLOOR;
    gMap[14][18]= TILE_DOOR; gMap[14][19]= TILE_FLOOR; gMap[14][20]= TILE_FLOOR; gMap[14][21]= TILE_DOOR;
    gMap[19][8] = TILE_DOOR; gMap[20][8] = TILE_FLOOR;
    gMap[19][30]= TILE_DOOR; gMap[20][30]= TILE_FLOOR;
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
    if(r>=0  && r<=8  && c>=0  && c<=18) return 1;
    if(r>=0  && r<=8  && c>=21 && c<=39) return 2;
    if(r>=10 && r<=18 && c>=0  && c<=18) return 3;
    if(r>=10 && r<=18 && c>=21 && c<=39) return 4;
    if(r>=20 && r<=ROWS-1 && c>=0  && c<=18) return 5;
    if(r>=20 && r<=ROWS-1 && c>=21 && c<=39) return 6;
    return 0;
}
