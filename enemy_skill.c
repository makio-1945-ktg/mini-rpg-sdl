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
    add_battle_log("オークの強烈なラリアット！");
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
            "%dダメージ！",
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
    add_battle_log("コウモリの吸血攻撃！");
//コウモリの吸血攻撃は防御無視
    int enemy_damage = attack + 1;

    player->hp -= enemy_damage;

    enemy->hp += 5;

    if(enemy->hp > enemy->max_hp)
    {
       enemy->hp = enemy->max_hp;
    }

    char msg[128];
    sprintf(msg,
            "HPを%d奪われた！",
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

static void skeleton_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("スケルトンは肋骨を投げつけた！");

    int enemy_damage =
        attack * 3 - player->defense;

    enemy->hp = 1;

    if(player->defending)
    {
        enemy_damage /= 2;
    }

    if(enemy_damage < 1)
    {
        enemy_damage = 1;
    }

    char msg[128];
    sprintf(msg, "%dダメージ！", enemy_damage);

    add_battle_log(msg);

    printf("プレイヤーHP:%d\n",
            player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");
        end_battle(battle_mode);
    }

    player->hp -= enemy_damage;

    enemy->hp = 3;

    add_battle_log("肋骨を失い体が崩れそうだ！");
}

static void golem_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    if(enemy->charging)
    {
        add_battle_log("両腕で地震を起こした！");

        enemy->charging = false;

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
                "%dダメージ！",
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

        player->stunned = true;
        player->stun_timer = 1;

        return;
    }

    if(rand() % 4 == 0)
    {
        enemy->charging = true;

        add_battle_log("ゴーレムは力を溜めている！");

        return;
    }

    normal_enemy_attack(
        player,
        enemy,
        attack,
        battle_mode
    );
}

void static scorpion_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("スコーピオンは毒針を刺してきた！");
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

    player->poisoned = true;
    player->poison_timer = 3;

    char msg[128];
    sprintf(msg, "%dダメージ！", enemy_damage);

    add_battle_log(msg);

    printf("プレイヤーHP:%d\n",
            player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");
        end_battle(battle_mode);
    }
}

static void lucky_fairy_special_move(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    add_battle_log("ラッキーフェアリーは逃げ出した！");

    end_battle(battle_mode);
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

        case ENEMY_SKELETON:

            if(enemy->hp >= 4 && rand() % 4 == 0)
            {
                skeleton_special_move(
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

        case ENEMY_GOLEM:

            golem_special_move(
                player,
                enemy,
                attack,
                battle_mode
            );
            break;

        case ENEMY_SCORPION:

            if(rand() % 3 == 0)
            {
                scorpion_special_move(
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

        case ENEMY_LUCKY_FAIRY:

            if(enemy->hp <= 20 && rand() % 2 == 0)
            {
                lucky_fairy_special_move(
                    player,
                    enemy,
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
