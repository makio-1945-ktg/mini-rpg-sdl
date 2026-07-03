#include <stdio.h>

#include "cave.h"

char cave_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MUFFMFFFFFFFFFFFFFFM",
    "MFFFMFMFMMMMMMMMMMFM",
    "MFFFMFMFFFFFFFFMFFFM",
    "MFFFFFMFMMMMMMFMFMMM",
    "MMMMMMMFFFFFFFFMFFCM",
    "MFFFFFFFMMMMMMFMMMMM",
    "MMMMMMMMMFFFFFFMFFFM",
    "MCMCFFFFFFMMMMFMFMFM",
    "MFMFFWWWFFMFFMFMFMFM",
    "MFMFWWWWFFMFFMFMFMFM",
    "MFFFFWWFFFFFFFFMFMFM",
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
    Player *player,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
)
{
    if(tile == 'U')
    {
        *in_cave = false;

        player->x = 1;
        player->y = 1;

        printf("洞窟を出た！");
    }
}

