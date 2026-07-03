#ifndef CAVE_H
#define CAVE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "battle.h"

extern char cave_map[15][21];

char get_cave_tile(int x, int y);

void handle_cave_event(
    char tile,
    bool *in_cave,
    Player *player,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
);

#endif
