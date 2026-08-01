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

void cave_chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
)
{
    if(x == 18 && y == 5)
    {
        player->gold += 50;

        printf("50Gを入手した！\n");
        printf(
            "所持金:%dG\n",
            player->gold
        );
    }
    else if(x == 1 && y == 8)
    {
        player->equipment.wooden_shield = 1;

        calc_player_status(player);

        printf("木の盾を入手した！\n");
        printf(
            "DEF:%d\n",
            player->defense
        );
    }
    else if(x == 3 && y == 8)
    {
        player->inventory.ether++;

        printf("エーテルを入手した！\n");
        printf(
            "現在:%d個\n",
            player->inventory.ether
        );
    }

    open_chest(map, x, y);
}

void cave_b1_chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
)
{
    if(x == 5 && y == 5)
    {
        player->equipment.broad_sword = 1;

        calc_player_status(player);

        printf("ブロードソードを入手した！\n");
    }
    else if(x == 11 && y == 5)
    {
        player->inventory.potion++;

        printf("ポーションを入手した！\n");
        printf(
            "現在:%d個\n",
            player->inventory.potion
        );
    }
    else if(x == 17 && y == 11)
    {
        player->inventory.bomb++;

        printf("爆薬を入手した！\n");
        printf(
            "現在:%d個\n",
            player->inventory.bomb
        );
    }

    open_chest(map, x, y);
}

void cave_b2_chest_event(
    Player *player,
    char map[15][21],
    int x,
    int y
)
{
    if(x == 3 && y == 3)
    {
        player->equipment.rune_sword = 1;

        calc_player_status(player);

        printf("ルーンソードを手に入れた！\n");
    }

    if(x == 10 && y == 3)
    {
        player->equipment.rune_armor = 1;

        calc_player_status(player);

        printf("ルーンアーマーを手に入れた！\n");
    }

    if(x == 12 && y == 7)
    {
        printf("ドラゴンオーブ実装予定です\n");
    }

    if(x == 13 && y == 18)
    {
        player->equipment.rune_shield = 1;

        calc_player_status(player);

        printf("ルーンシールドを手に入れた！\n");
    }
    open_chest(map, x, y);
}

