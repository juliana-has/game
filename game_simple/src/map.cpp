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

    room(0, 0,  8, 17);   // hab 1 - arriba izquierda
    room(0, 21, 8, 39);   // hab 2 - arriba derecha
    room(9, 0,  16,17);   // hab 3 - medio izquierda
    room(9, 21, 16,39);   // hab 4 - medio derecha
    room(17,0,  21,17);   // hab 5 - abajo izquierda
    room(17,21, 21,39);   // hab 6 - abajo derecha (final)

    // armario hab 1
    gMap[1][1] = TILE_CLOSET;
    // armario hab 6 (objetivo)
    gMap[20][38]= TILE_CLOSET;

    // puertas entre hab 1 y hab 2 (fila 3, col 18-20)
    gMap[3][17]= TILE_DOOR;
    gMap[3][18]= TILE_FLOOR;
    gMap[3][19]= TILE_FLOOR;
    gMap[3][20]= TILE_FLOOR;
    gMap[3][21]= TILE_DOOR;

    // puertas hab 1 -> hab 3 (col 8, fila 8-9)
    gMap[8][8] = TILE_DOOR;
    gMap[9][8] = TILE_FLOOR;

    // puertas hab 2 -> hab 4 (col 30, fila 8-9)
    gMap[8][30]= TILE_DOOR;
    gMap[9][30]= TILE_FLOOR;

    // puertas hab 3 -> hab 4 (fila 12, col 17-21)
    gMap[12][17]= TILE_DOOR;
    gMap[12][18]= TILE_FLOOR;
    gMap[12][19]= TILE_FLOOR;
    gMap[12][20]= TILE_FLOOR;
    gMap[12][21]= TILE_DOOR;

    // puertas hab 3 -> hab 5 (col 8, fila 16-17)
    gMap[16][8] = TILE_DOOR;
    gMap[17][8] = TILE_FLOOR;

    // puertas hab 4 -> hab 6 (col 30, fila 16-17)
    gMap[16][30]= TILE_DOOR;
    gMap[17][30]= TILE_FLOOR;
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
