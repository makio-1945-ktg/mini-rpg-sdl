#include <stdio.h>

#include "chest.h"
#include "map.h"

void chest_event(
    Player *player,
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

    open_chest(x, y);
}

void open_chest(
    int x,
    int y
)
{
    field_map[y][x] = '.';
}
