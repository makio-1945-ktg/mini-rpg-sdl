#include <stdio.h>
#include <stdbool.h>

#include "battle.h"

bool battle_attack(
    Player *player,
    Enemy *enemy
    )
    {
    int player_damage =
        player->attack - enemy->defense;

    if(player_damage < 1)
    {
        player_damage = 1;
    }

    enemy->hp -= player_damage;

        printf("攻撃！\n");
        printf("プレイヤーダメージ:%d\n",
               player_damage);

        printf("%s HP:%d\n",
               enemy->name,
               enemy->hp);

        if(enemy->hp <= 0)
        {
            printf("敵を倒した！\n");

            return true;
        }
    int enemy_damage =

        enemy->attack - player->defense;

    if(enemy_damage < 1)
    {
        enemy_damage = 1;
    }

        player->hp -= enemy_damage;

        printf("敵の攻撃！\n");
        printf("敵ダメージ:%d\n",
               enemy_damage);
        printf("プレイヤーHP:%d\n", player->hp);

        if(player->hp <= 0)
        {
            printf("ゲームオーバー！\n");

            return true;
        }
        return false;
    }
