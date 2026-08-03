#ifndef CAVE_B2_H
#define CAVE_B2_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "battle.h"

extern char cave_b2_map[15][21];

char get_cave_b2_tile(int x, int y);

void handle_cave_b2_event(
    char tile,
    bool *in_cave_b1,
    bool *in_cave_b2,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *kobold_texture,
    SDL_Texture *wisp_texture,
    SDL_Texture *lamia_texture
);

#endif
