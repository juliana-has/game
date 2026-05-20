#ifndef ITEMS_H
#define ITEMS_H

#include "types.h"

struct Item {
    int  id;          
    Vec2 pos;
    bool collected;
    char symbol;      
};

void items_init(Item *items, int *count);


Item* items_find_nearby(Item *items, int count, int r, int c);
void items_collect(Item *item);
int  items_count_collected(const Item *items, int count);
const char* items_get_content(int itemId);
const char* items_get_name(int itemId);

#endif 
