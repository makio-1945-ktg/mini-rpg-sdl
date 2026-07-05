#include <stdio.h>

#include "chest.h"
#include "map.h"

void chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
)
{
    player->inventory.potion++;

    printf("ポーションを入手した！\n");
    printf(
        "現在:%d個\n",
        player->inventory.potion
    );

    open_chest(map, x, y);
}

void open_chest(
    char map[15][21],
    int x,
    int y
)
{
    map[y][x] = '.';
}
