#ifndef CHEST_H
#define CHEST_H

#include "player.h"

void chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
);

void cave_chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
);

void cave_b1_chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
);

void open_chest(
    char map[15][21],
    int x,
    int y
);

#endif
