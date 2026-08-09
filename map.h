#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "battle.h"

extern char field_map[15][21];

extern char town_map[8][9];

char get_tile(int x, int y);

char get_town_tile(int x, int y);

//イベント関数
void town_event(void);

void npc_event(void);

void inn_event(
    Player *player
);

void equipment_shop_event(
    Player *player
);

void enemy_event(
    char map[15][21],
    int x,
    int y
);

void handle_field_event(
    char tile,
    bool *in_town,
    bool *in_cave,
    bool *in_temple,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    int *shop_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
);

#endif
