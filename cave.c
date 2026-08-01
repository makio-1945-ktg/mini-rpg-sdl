#include <stdio.h>

#include "cave.h"
#include "battle.h"
#include "chest.h"
#include "magic.h"
#include "enemy.h"

char cave_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MUFFMFFFFFFFFFFFFFFM",
    "MFFFMFMFMMMMMMMMMMFM",
    "MFEFMFMFFFFFFFFMEFFM",
    "MFFFFFMFMMMMMMFMFMMM",
    "MMMMMMMFFFFFFFEMFFCM",
    "MFFFFFFFMMMMMMFMMMMM",
    "MMMMMMMMMFFFFFFMFFFM",
    "MCMCFFEFFFMMMMFMFMFM",
    "MFMFFWWWFFMFFMFMFMFM",
    "MFMFWWWWFFMFFMFMFMFM",
    "MEFFFWWFFFFFFFEMFMEM",
    "MFMMMMMMMMMMMMFMFMFM",
    "MFFFFFFFFFFFFMFFFMDM",
    "MMMMMMMMMMMMMMMMMMMM"
};

char get_cave_tile(int x, int y)
{
    return cave_map[y][x];
}

void handle_cave_event(
    char tile,
    bool *in_cave,
    bool *in_cave_b1,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *bat_texture,
    SDL_Texture *skeleton_texture,
    SDL_Texture *golem_texture
)
{
    if(tile == 'U')
    {
        *in_cave = false;

        player->x = 18;
        player->y = 4;

        printf("洞窟を出た！");
    }
    if(tile == 'D')
    {
        *in_cave_b1 = true;

        player->x = 18;
        player->y = 13;

        printf("地下１階へ降りた！");
    }
    if(tile == 'C')
    {
        cave_chest_event(
            player,
            cave_map,
            new_x,
            new_y
        );
    }
    if(tile == 'E')
    {
        start_cave_battle(
            battle_mode,
            battle_cursor,
            magic_cursor,
            use_item_cursor,
            enemy,
            current_enemy_texture,
            bat_texture,
            skeleton_texture,
            golem_texture,
            player,
            new_x,
            new_y
        );
    }
}

