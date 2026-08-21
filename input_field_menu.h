#ifndef INPUT_FIELD_MENU_H
#define INPUT_FIELD_MENU_H

#include <SDL2/SDL.h>
#include "player.h"
#include "battle.h"

void handle_status_input(
    SDL_Event *event,
    BattleMode *battle_mode
);

void handle_item_menu_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *item_cursor,
    Player *player,
    bool *in_cave,
    bool *in_cave_b1,
    bool *in_cave_b2
);

void handle_equipment_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *equipment_cursor,
    Player *player
);

#endif
