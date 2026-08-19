// input_save.h
#ifndef INPUT_SAVE_H
#define INPUT_SAVE_H

#include <SDL2/SDL.h>
#include "player.h"
#include "battle.h"

void handle_save_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *save_cursor,
    Player *player,
    bool *in_town,
    bool *in_cave,
    bool *in_cave_b1,
    bool *in_cave_b2,
    bool *in_temple
);

#endif
