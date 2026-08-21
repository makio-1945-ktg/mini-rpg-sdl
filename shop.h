#ifndef SHOP_H
#define SHOP_H

#include <SDL2/SDL.h>
#include "player.h"
#include "battle.h"

void handle_shop_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *shop_cursor,
    Player *player
);

void handle_item_shop_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *item_shop_cursor,
    Player *player
);

#endif
