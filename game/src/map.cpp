#include "../include/map.h"
#include "../include/renderer.h"
#include <cstring>
#include <cstdio>
int gMap[ROWS][COLS];
static void fill_rect(int r1, int c1, int r2, int c2, int tile) {
    for (int r = r1; r <= r2; r++)
        for (int c = c1; c <= c2; c++)
            gMap[r][c] = tile;
}
static void wall_rect(int r1, int c1, int r2, int c2) {
    for (int r = r1; r <= r2; r++) {
        for (int c = c1; c <= c2; c++) {
            if (r == r1 || r == r2 || c == c1 || c == c2)
                gMap[r][c] = T_WALL;
            else if (gMap[r][c] != T_WALL)
                gMap[r][c] = T_FLOOR;
        }
    }
}
void map_init() {
    fill_rect(0, 0, ROWS - 1, COLS - 1, T_EMPTY);
    wall_rect(1, 1, 8, 12);
    wall_rect(1, 14, 8, 28);
    wall_rect(10, 1, 15, 12);
    wall_rect(10, 14, 15, 28);
    wall_rect(16, 12, 18, 17);
    wall_rect(17, 1, 21, 11);
    wall_rect(17, 14, 21, 28);
    gMap[2][13] = T_FLOOR;
    gMap[3][13] = T_DOOR;
    gMap[4][13] = T_FLOOR;
    gMap[5][13] = T_FLOOR;
    gMap[9][3]  = T_FLOOR;
    gMap[9][4]  = T_DOOR;
    gMap[9][5]  = T_FLOOR;
    gMap[9][15] = T_FLOOR;
    gMap[9][16] = T_DOOR;
    gMap[9][17] = T_FLOOR;
    gMap[12][13] = T_FLOOR;
    gMap[13][13] = T_DOOR;
    gMap[13][14] = T_FLOOR;
    gMap[16][3]  = T_FLOOR;
    gMap[16][4]  = T_DOOR;
    gMap[16][5]  = T_FLOOR;
    gMap[16][14] = T_FLOOR;
    gMap[16][15] = T_DOOR;
    gMap[16][16] = T_FLOOR;
    gMap[19][12] = T_FLOOR;
    gMap[19][13] = T_DOOR;
    gMap[19][14] = T_FLOOR;
    gMap[18][17] = T_FLOOR;
    gMap[18][18] = T_DOOR;
    gMap[2][2]  = T_CLOSET;
    gMap[18][15] = T_CLOSET;
}
bool map_can_walk(int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return false;
    int t = gMap[r][c];
    return (t == T_FLOOR || t == T_DOOR || t == T_CLOSET);
}
int map_get_tile(int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return T_EMPTY;
    return gMap[r][c];
}
int map_get_room(int r, int c) {
    if (r >= 1  && r <= 8  && c >= 1  && c <= 12) return ROOM_1;
    if (r >= 1  && r <= 8  && c >= 14 && c <= 28) return ROOM_5;
    if (r >= 10 && r <= 15 && c >= 1  && c <= 12) return ROOM_2;
    if (r >= 10 && r <= 15 && c >= 14 && c <= 28) return ROOM_6;
    if (r >= 16 && r <= 18 && c >= 12 && c <= 17) return ROOM_4;
    if (r >= 17 && r <= 21 && c >= 1  && c <= 11) return ROOM_3;
    if (r >= 17 && r <= 21 && c >= 14 && c <= 28) return ROOM_7;
    return ROOM_NONE;
}
void map_draw(const DrawData *dd) {
    static char buf[ROWS][COLS * 2 + 4];
    static char col[ROWS][COLS];
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int t = gMap[r][c];
            char ch = ' ';
            if      (t == T_WALL)   ch = '#';
            else if (t == T_FLOOR)  ch = '.';
            else if (t == T_DOOR)   ch = '+';
            else if (t == T_CLOSET) ch = 'C';
            buf[r][c] = ch;
            col[r][c] = 0;
        }
    }
    for (int i = 0; i < dd->itemCount; i++) {
        const ItemDraw *it = &dd->items[i];
        if (!it->collected && it->r >= 0 && it->r < ROWS && it->c >= 0 && it->c < COLS) {
            buf[it->r][it->c] = it->symbol;
            col[it->r][it->c] = 3;
        }
    }
    for (int i = 0; i < dd->entityCount; i++) {
        const EntityDraw *e = &dd->entities[i];
        if (e->active && e->r >= 0 && e->r < ROWS && e->c >= 0 && e->c < COLS) {
            buf[e->r][e->c] = e->symbol;
            col[e->r][e->c] = (i == 0) ? 4 : (i == 1 ? 1 : 2);
        }
    }
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int cc = col[r][c];
            if      (cc == 1) printf("%s", Color::RED);
            else if (cc == 2) printf("%s", Color::MAGENTA);
            else if (cc == 3) printf("%s", Color::YELLOW);
            else if (cc == 4) printf("%s", Color::CYAN);
            else if (gMap[r][c] == T_WALL) printf("%s", Color::DIM);
            printf("%c", buf[r][c]);
            printf("%s", Color::RESET);
        }
        printf("\n");
    }
}
