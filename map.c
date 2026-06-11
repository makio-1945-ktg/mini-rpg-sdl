#include <stdio.h>

#include "map.h"

char field_map[10][11] = {

    "MMMMMMMMMM",
    "MNGGGGGTGM",
    "MCGEGGGGEM",
    "MEGGGGEGGM",
    "MMMMMMMMGM",
    "MGGGGGGGGM",
    "MGGGGGGGGM",
    "MGGGGGGGGM",
    "MGGGGGGGGM",
    "MMMMMMMMMM"
};

char get_tile(int x, int y)
{
    return field_map[y][x];
}

void town_event(void)
{
    printf("町に到着しました！\n");
}

void npc_event(void)
{
    printf("こんにちは！\n");
}

void chest_event(
    Player *player,
    int x,
    int y
)

{
    player->potion++;

    printf("ポーションを入手した！\n");
    printf("現在:%d個\n",
           player->potion);

    open_chest(
        x,
        y
    );
}

void open_chest(
    int x,
    int y
)

{
    field_map[y][x] = '.';
}

void enemy_event(int x, int y)
{
    printf("敵が現れた！\n");

    field_map[y][x] = 'G';
}
