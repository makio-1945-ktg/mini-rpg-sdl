#include <stdio.h>

#include "cave_b2.h"
#include "battle.h"
#include "chest.h"
#include "magic.h"
#include "enemy.h"

char cave_b2_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MFFFFFFFFFFFFFEMFFEM",
    "MFMMMMMMMMMMMMFMFMFM",
    "MFMCEFFFFMCFFMFMFMFM",
    "MFMMMMMMFMFFFMFMFMFM",
    "MFFFFFFFFMFFUMPFFMFM",
    "MMMMMMMMMMMMMMMMMMFM",
    "MFFFFFFMFFFECMFFFFFM",
    "MFMMMMMMFMMMMMFMFMMM",
    "MFFEFFFFFMFFFMFMFMFM",
    "MMMFMMMMMMFMFMFMFMFM",
    "MFMFFFFFFFFMFMFMFFFM",
    "MFMMMMMMMMFMFMFMMMMM",
    "MEFFFFFFFFEMFFFFFECM",
    "MMMMMMMMMMMMMMMMMMMM",
};

char get_cave_b2_tile(int x, int y)
{
    return cave_b2_map[y][x];
}

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
)
{
    if(tile == 'U')
    {
        *in_cave_b2 = false;

        player->x = 12;
        player->y = 4;

        printf("洞窟地下１階へ戻った！");
    }

    if(tile == 'P')
    {
        *in_cave_b2 = false;

        player->x = 14;
        player->y = 4;

        printf("洞窟地下１階へ戻った！");
    }
    
    if(tile == 'C')
    {
        cave_b2_chest_event(
            player,
            cave_b2_map,
            new_x,
            new_y
        );
    }

    if(tile == 'E')
    {
        start_cave_b2_battle(
            battle_mode,
            battle_cursor,
            magic_cursor,
            use_item_cursor,
            enemy,
            current_enemy_texture,
            kobold_texture,
            wisp_texture,
            lamia_texture,
            player,
            new_x,
            new_y
        );
    }
}
