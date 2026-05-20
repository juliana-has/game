#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

// ============================================================
//  Módulo del jugador (Eli)
// ============================================================

struct Player {
    Vec2 pos;
    int  inventoryItem;   // ITEM_NONE o un ITEM_*
    bool inCloset;
    bool alive;
};

// Inicializa el jugador en la posicion de inicio
void player_init(Player *p);

// Intenta mover al jugador segun entrada (dr, dc).
// Retorna true si se movio.
bool player_move(Player *p, int dr, int dc);

// El jugador recoge el item (si hay espacio en inventario)
bool player_pick(Player *p, int itemId);

// El jugador suelta el item actual
void player_drop(Player *p);

// Devuelve true si el jugador esta parado sobre un armario
bool player_is_in_closet(const Player *p);

#endif // PLAYER_H
