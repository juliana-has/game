#ifndef MAP_H
#define MAP_H
#include "types.h"
extern int gMap[ROWS][COLS];
void map_init();
bool map_can_walk(int r, int c);
int  map_get_tile(int r, int c);
int  map_get_room(int r, int c);
void map_draw(const struct DrawData *dd);
struct EntityDraw {
    int  r;
    int  c;
    char symbol;
    bool active;
};
struct ItemDraw {
    int  r;
    int  c;
    char symbol;
    bool collected;
};
struct DrawData {
    EntityDraw entities[MAX_ENEMIES + 1];
    ItemDraw   items[MAX_ITEMS];
    int        itemCount;
    int        entityCount;
};
#endif
