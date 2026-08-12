#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

#include "player.h"

typedef struct
{
    Player player;

    bool in_town;
    bool in_cave;
    bool in_cave_b1;
    bool in_cave_b2;
    bool in_temple;

} GameState;

#endif
