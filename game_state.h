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

    char field_map[15][21];
    char town_map[8][9];
    char cave_map[15][21];
    char cave_b1_map[15][21];
    char cave_b2_map[15][21];
    char temple_map[11][10];

} GameState;

#endif
