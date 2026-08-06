#include <stdio.h>

#include "temple.h"
#include "battle.h"
#include "magic.h"
#include "enemy.h"

char temple_map[11][10] = {

    "MMMMMMMMM",
    "MMMMGMMMM",
    "MMMGDGMMM",
    "MMGGGGGMM",
    "MGGGGGGGM",
    "MGGGGGGGM",
    "MGNGGGGGM",
    "MMGGGGGMM",
    "MMMGGGMMM",
    "MMMMOMMMM",
    "MMMMMMMMM"
};

char get_temple_tile(int x, int y)
{
    return temple_map[y][x];
}

void npc_event(void)
{
    printf("龍神様はドラゴンの宝玉を持つものにのみ姿を表すという…\n");
}

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
)
{
    if(tile == 'O')
    {
        *in_temple = false;

        player->x = 4;
        player->y = 11;

        printf("神殿を出た！\n");
    }

    if(tile == 'N')
    {
        npc_event();
    }

    if(tile == 'D')
    {
        if(player->inventory.dragon_jewel > 0)
        {
            start_boss_battle(
                battle_mode,
                battle_cursor,
                magic_cursor,
                use_item_cursor,
                enemy,
                current_enemy_texture,
                dragon_texture,
                player,
                new_x,
                new_y
            );
        }
        else
        {
            printf("巨大な龍の石像がある。\n");
        }
    }
}
