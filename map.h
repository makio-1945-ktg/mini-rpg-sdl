#ifndef MAP_H
#define MAP_H

#include "player.h"

extern char field_map[10][11];

char get_tile(int x, int y);

//イベント関数
void town_event(void);

void npc_event(void);

void chest_event(
    Player *player,
    int x,
    int y
);

void open_chest(
    int x,
    int y
);

void enemy_event(int x, int y);

#endif
