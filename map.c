#include <stdio.h>

#include "map.h"

char field_map[5][6] = {

    "MMMMM",
    "MGNGM",
    "MCGGM",
    "MGTGM",
    "MMMMM"
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

void chest_event(int x, int y)
{
    printf("50G入手した！\n");

    field_map[y][x] = 'G';
}
