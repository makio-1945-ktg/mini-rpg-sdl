#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "equipment.h"

void buy_sword(Player *player)
{
    if(player->equipment.sword)
    {
        printf("すでに装備している！\n");
        return;
    }

    if(player->gold < 20)
    {
        printf("お金が足りない！\n");
        return;
    }

    player->gold -= 20;

    player->equipment.sword = true;

    calc_player_status(player);

    printf("剣を購入した！\n");

    printf("ATK:%d\n",
            player->attack);

    printf("所持金:%dG\n",
            player->gold);
}

void buy_leather_armor(Player *player)
{
    if(player->equipment.leather_armor)
    {
        printf("すでに装備している！\n");
        return;
    }

    if(player->gold < 30)
    {
        printf("お金が足りない！\n");
        return;
    }

    player->gold -= 30;

    player->equipment.leather_armor = true;

    calc_player_status(player);

    printf("皮の鎧を購入した！\n");

    printf("DEF:%d\n",
            player->defense);

    printf("所持金:%dG\n",
            player->gold);
}

void equipment_shop_event(Player *player)
{
    int choice;

    bool shopping = true;

    while(shopping)
    {
        printf("=== 武器屋 ===\n");

        printf("1. 剣 20G\n");
        printf("2. 皮の鎧 30G\n");
        printf("3. 買わない\n");

        printf(">");

        if(scanf("%d", &choice) != 1)
        {
            printf("無効な入力！\n");
            return;
        }

        switch(choice)
        {
            case 1:

                buy_sword(player);
                break;

            case 2:

                buy_leather_armor(player);
                break;

            case 3:
                printf("またのお越しを！\n");
                shopping = false;
                break;

            default:
                printf("無効な入力！\n");
                break;
        }
    }
}
