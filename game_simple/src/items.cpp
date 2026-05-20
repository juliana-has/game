#include "../include/items.h"

static int absi2(int x){return x<0?-x:x;}

void items_init(Item *items){
    items[0].id=ITEM_PAPER;  items[0].pos.r=13; items[0].pos.c=5;  items[0].collected=false;
    items[1].id=ITEM_KEY;    items[1].pos.r=3;  items[1].pos.c=28; items[1].collected=false;
    items[2].id=ITEM_CANDLE; items[2].pos.r=14; items[2].pos.c=12; items[2].collected=false;
    items[3].id=ITEM_PHONE;  items[3].pos.r=13; items[3].pos.c=30; items[3].collected=false;
    items[4].id=ITEM_LETTER; items[4].pos.r=ROWS-3; items[4].pos.c=28; items[4].collected=false;
}

Item* items_nearby(Item *items,int r,int c){
    for(int i=0;i<MAX_ITEMS;i++){
        Item *it=&items[i];
        if(!it->collected&&absi2(it->pos.r-r)<=1&&absi2(it->pos.c-c)<=1)
            return it;
    }
    return 0;
}

int items_collected(Item *items){
    int n=0;
    for(int i=0;i<MAX_ITEMS;i++) if(items[i].collected) n++;
    return n;
}

const char* items_name(int id){
    if(id==ITEM_PAPER)  return "Su carta";
    if(id==ITEM_KEY)    return "Llave";
    if(id==ITEM_CANDLE) return "Vela";
    if(id==ITEM_PHONE)  return "Celular";
    if(id==ITEM_LETTER) return "Carta tuya";
    return "?";
}

const char* items_text(int id){
    if(id==ITEM_PAPER)
        return "  \"Hola. Se que aun me amas.\n   Juro que ese dia no era yo.\n   Solo necesito que no te vayas.\"";
    if(id==ITEM_PHONE)
        return "  [Papa: Hija donde estas?]\n  [Yo: Voy con el, ya vuelvo.]\n  [Papa: Cuando es ya.]\n  [Yo: Pronto.]";
    if(id==ITEM_LETTER)
        return "  \"El dia que decidi quedarme\n   decidi creer que lograrias\n   simplemente amarme bien.\"";
    return 0;
}
