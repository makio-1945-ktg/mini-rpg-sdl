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

            player->exp += enemy->exp;

            printf("%d EXP獲得！\n",
                   enemy->exp);

            printf("現在EXP:%d\n",
                   enemy->exp);

            return true;
        }

        return enemy_turn(
            player,
            enemy
        );
    }

bool battle_defend(
    Player *player,
    Enemy *enemy
)
{
    printf("防御した！\n");

    int enemy_damage =
        enemy->attack
        - player->defense;

    enemy_damage /= 2;

    if(enemy_damage < 1)
    {
        enemy_damage = 1;
    }

    player->hp -= enemy_damage;

    printf("敵の攻撃！\n");
    printf("敵ダメージ:%d\n",
           enemy_damage);
    printf("プレイヤーHP:%d\n",
           player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");

        return true;
    }

    return false;
}

bool battle_heal(
    Player *player,
    Enemy *enemy
)
{
    if(player->mp < 3)
    {
        printf("MPが足りない！\n");
    }

    player->mp -= 3;

    player->hp += 10;

    if(player->hp > player->max_hp)
    {
        player->hp = player->max_hp;
    }

    printf("ヒールを唱えた！\n");
    printf("HPが10回復した！\n");

    printf("HP:%d\n",
           player->hp);

    printf("MP:%d\n",
           player->mp);

    return enemy_turn(
        player,
        enemy
    );
}

bool enemy_turn(
    Player *player,
    Enemy *enemy
)
{
    int enemy_damage =
        enemy->attack
        - player->defense;

    if(enemy_damage < 1)
    {
        enemy_damage = 1;
    }

    player->hp -= enemy_damage;

    printf("敵の攻撃！\n");
    printf("敵ダメージ:%d\n",
           enemy_damage);
    printf("プレイヤーHP:%d\n",
           player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");

        return true;
    }

    return false;
}
