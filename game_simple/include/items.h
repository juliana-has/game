#ifndef ITEMS_H
#define ITEMS_H

#include "types.h"

struct Item {
    int  id;
    Vec2 pos;
    bool collected;
};

void  items_init(Item *items);
Item* items_nearby(Item *items, int r, int c);
int   items_collected(Item *items);
const char* items_name(int id);
const char* items_text(int id);

#endif
