#include "equipment.h"

void equipment_shop_event(Player *player)
{
    if(player->equipment.sword)
    {
        printf("既に剣を持っている！\n");
        return;
    }

    if(player->gold < 20)
    {
        printf("お金が足りない！\n");
        return;
    }

    player->gold -= 20;

    player->equipment.sword = 1;

    player->attack =
        player->base_attack + 2;

    printf("剣を購入した！\n");

    printf("ATK:%d\n",
           player->attack);

    printf("所持金:%dG\n",
           player->gold);
}


