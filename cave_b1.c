#include <stdio.h>

#include "cave_b1.h"
#include "battle.h"
#include "chest.h"
#include "magic.h"
#include "enemy.h"

char cave_b1_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MFFFFFFFFFFFFFFFFFFM",
    "MFMMMMMMMMMMMMMMMMFM",
    "MFMFFFFFMFFFFMFFFMFM",
    "MFMEMMMFMFMFFMFMFMFM",
    "MFMFFCMEFFMCDMOMFMFM",
    "MFMMMMMFMMMMMMMMFMFM",
    "MFFFFFMFFFFFFFMMFFFM",
    "MMMMMFMMMMMMMFMMMMMM",
    "MFFEMFFFFFFFMFFEFFFM",
    "MFMFMMMMMMMFMFMFMMFM",
    "MFMFFFFFFFFFMFMFMCFM",
    "MFMMMMMMMMMMMFMFMMMM",
    "MFFFFFFFFFFFFFMFFFUM",
    "MMMMMMMMMMMMMMMMMMMM"
};

char get_cave_b1_tile(int x, int y)
{
    return cave_b1_map[y][x];
}

void handle_cave_b1_event(
    char tile,
    bool *in_cave,
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
    SDL_Texture *scorpion_texture,
    SDL_Texture *luckyfairy_texture,
    SDL_Texture *wizard_texture

)
{
    if(tile == 'U')
    {
        *in_cave_b1 = false;

        player->x = 18;
        player->y = 12;

        printf("洞窟１階へ戻った！");
    }

    if(tile == 'D')
    {
        *in_cave_b2 = true;

        player->x = 11;
        player->y = 5;

        printf("洞窟地下２階へ潜った！");
    }

    if(tile == 'O')
    {
        *in_cave_b2 = true;

        player->x = 14;
        player->y = 5;

        printf("洞窟地下２階へ潜った！");
    }

    if(tile == 'C')
    {
        cave_b1_chest_event(
            player,
            cave_b1_map,
            new_x,
            new_y
        );
    }
    if(tile == 'E')
    {
        start_cave_b1_battle(
            battle_mode,
            battle_cursor,
            magic_cursor,
            use_item_cursor,
            enemy,
            current_enemy_texture,
            scorpion_texture,
            luckyfairy_texture,
            wizard_texture,
            player,
            new_x,
            new_y
        );
    }
}
