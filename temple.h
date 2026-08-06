#ifndef TEMPLE_H
#define TEMPLE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "battle.h"

extern char temple_map[11][10];

char get_temple_tile(int x, int y);

void temple_npc_event(void);

void handle_temple_event(
    char tile,
    bool *in_temple,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *dragon_texture
);

#endif
