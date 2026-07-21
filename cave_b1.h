#ifndef CAVE_B1_H
#define CAVE_B1_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "battle.h"

extern char cave_b1_map[15][21];

char get_cave_b1_tile(int x, int y);

void handle_cave_b1_event(
    char tile,
    bool *in_cave,
    bool *in_cave_b1,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *scorpion_texture,
    SDL_Texture *luckyfairy_texture,
    SDL_Texture *wizard_texture
);

#endif
