#include <stdio.h>
#include <string.h>

#include "enemy_skill.h"

void normal_enemy_attack(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    int enemy_damage =
        attack - player->defense;

    if(player->defending)
    {
        enemy_damage /= 2;
    }

    if(enemy_damage < 1)
    {
        enemy_damage = 1;
    }

    player->hp -= enemy_damage;

    char msg[128];
    sprintf(msg, "敵の攻撃！%dダメージ！", enemy_damage);
    add_battle_log(msg);

    printf("プレイヤーHP:%d\n",
           player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");
        end_battle(battle_mode);
        return;
    }
}

static void orc_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    int enemy_damage =
        attack * 2 - player->defense;

    if(player->defending)
    {
        enemy_damage /= 2;
    }

    if(enemy_damage < 1)
    {
        enemy_damage = 1;
    }

    player->hp -= enemy_damage;

    char msg[128];
    sprintf(msg,
            "オークは棍棒を振り回した！%dダメージ！",
            enemy_damage
    );

    add_battle_log(msg);

    printf("プレイヤーHP:%d\n",
           player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");
        end_battle(battle_mode);
    }
}

static void bat_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
//コウモリの吸血攻撃は防御無視
    int enemy_damage = attack + 1;

    enemy->hp += 3;

    if(enemy->hp > enemy->max_hp)
    {
       enemy->hp = enemy->max_hp;
    }

    char msg[128];
    sprintf(msg,
            "コウモリの吸血攻撃！ HPを%d奪われた！",
            enemy_damage
    );

    add_battle_log(msg);

    printf("プレイヤーHP:%d\n",
           player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");
        end_battle(battle_mode);
    }
}
void enemy_action(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    switch(enemy->type)
    {
        case ENEMY_ORC:

            if(rand() % 4 == 0)
            {
                orc_special_move(
                    player,
                    enemy,
                    attack,
                    battle_mode
                );
            }
            else
            {
                normal_enemy_attack(
                    player,
                    enemy,
                    attack,
                    battle_mode
                );
            }
            break;

        case ENEMY_BAT:

            if(rand() % 3 == 0)
            {
                bat_special_move(
                    player,
                    enemy,
                    attack,
                    battle_mode
                );
            }
            else
            {
                normal_enemy_attack(
                    player,
                    enemy,
                    attack,
                    battle_mode
                );
            }
            break;

        default:

            normal_enemy_attack(
                player,
                enemy,
                attack,
                battle_mode
            );
            break;
    }
}
