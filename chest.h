#ifndef CHEST_H
#define CHEST_H

#include "player.h"

void chest_event(
    Player *player,
    int x,
    int y
);

void open_chest(
    int x,
    int y
);

#endif
