#include <stdio.h>
#include <stdbool.h>

#include "battle.h"

bool battle_attack(
    Player *player,
    Enemy *enemy
    )
    {
        enemy->hp -= 3;

        printf("攻撃！\n");

        printf("敵HP:%d\n", enemy->hp);

        if(enemy->hp <= 0)
        {
            printf("敵を倒した！\n");

            return true;
        }

        player->hp -= 2;

        printf("敵の攻撃！\n");
        printf("プレイヤーHP:%d\n", player->hp);

        return false;
    }
