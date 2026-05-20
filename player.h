#ifndef MAP_H
#define MAP_H

#include "types.h"

extern int gMap[ROWS][COLS];

void map_init();
bool map_can_walk(int r, int c);
int  map_get_tile(int r, int c);

#endif
