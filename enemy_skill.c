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

static void wizard_magic_fire(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("まどうしはファイアを唱えた！");

    int enemy_damage = attack * 2;

    player->hp -= enemy_damage;

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

    if(rand() % 5 == 0)
    {
        player->burning = true;
        player->burn_timer = 3;

        add_battle_log("火傷を負った！");
    }
}

static void wizard_magic_ice(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("まどうしはアイスを唱えた！");

    int enemy_damage = attack;

    player->hp -= enemy_damage;

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

    if(rand() % 5 == 0)
    {
        player->frozen = true;
        player->frozen_timer = 1;

        add_battle_log("凍結状態になった！");
    }
}

static void wizard_magic_thunder(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("まどうしはサンダーを唱えた！");

    int enemy_damage = attack * 2;

    player->hp -= enemy_damage;

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

    if(rand() % 5 == 0)
    {
        player->stunned = true;
        player->stun_timer = 1;

        add_battle_log("スタン状態になった！");
    }
}

static void wizard_magic_heal(
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    add_battle_log("まどうしはヒールを唱えた！");

    enemy->hp += 15;

    if(enemy->hp > enemy->max_hp)
    {
        enemy->hp = enemy->max_hp;
    }
}

static void kobold_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("コボルトの短剣が赤く光った！");
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

    enemy->hp += enemy_damage;

    if(enemy->hp > enemy->max_hp)
    {
        enemy->hp = enemy->max_hp;
    }

    char msg[128];
    sprintf(msg,
            "HPを%d吸収された！！",
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

static void wisp_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    if(enemy->charging)
    {
        add_battle_log("ウィスプは自爆した！");

        enemy->charging = false;

        int enemy_damage = attack * 3;

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
        return;
    }

    if(rand() % 3 == 0)
    {
        enemy->charging = true;

        add_battle_log("ウィスプは様子を見ている…");

        return;
    }

    normal_enemy_attack(
        player,
        enemy,
        attack,
        battle_mode
    );
}

static void lamia_magic_ice(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("ラミアはアイスを唱えた！");

    int enemy_damage = attack;

    player->hp -= enemy_damage;

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

    if(rand() % 5 == 0)
    {
        player->frozen = true;
        player->frozen_timer = 1;

        add_battle_log("凍結状態になった！");
    }
}

static void lamia_special_move(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("ラミアは胴体でしめつけてきた！！");
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

    player->stunned = true;
    player->stun_timer = 1;

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

static void dragon_smash(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("竜神は鋭い爪で襲いかかった！");

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

static void dragon_breath(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
)
{
    add_battle_log("竜神のブレス攻撃！");

    int enemy_damage = attack * 2;

    player->hp -= enemy_damage;

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

    if(rand() % 4 == 0)
    {
        player->burning = true;
        player->burn_timer = 3;

        add_battle_log("火傷を負った！");
    }
}

static void dragon_heal(
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    add_battle_log("竜神は目を閉じて傷を癒やした！");

    enemy->hp += 30;

    if(enemy->hp > enemy->max_hp)
    {
       enemy->hp = enemy->max_hp;
    }

}

static void dragon_charge_breath(
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    enemy->charging = true;

    add_battle_log("竜神は大きく息を吸い込んだ！");

    return;
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
        case ENEMY_SLIME:

            normal_enemy_attack(
                player,
                enemy,
                attack,
                battle_mode
            );
        break;

        case ENEMY_GOBLIN:

            normal_enemy_attack(
                player,
                enemy,
                attack,
                battle_mode
            );
        break;

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

        case ENEMY_WIZARD:
        {

            int magic = rand() % 5;

            switch(magic)
            {
                case 0:
                    wizard_magic_fire(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 1:
                    wizard_magic_ice(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 2:
                     wizard_magic_thunder(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 3:
                    if(enemy->hp <= 30)
                    {
                        wizard_magic_heal(
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
            break;
        }

        case ENEMY_KOBOLD:

            if(rand() % 4 == 0)
            {
                kobold_special_move(
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

        case ENEMY_WISP:

            wisp_special_move(
                player,
                enemy,
                attack,
                battle_mode
            );
            break;

        case ENEMY_LAMIA:
        {
            int special_move = rand() % 5;

            switch(special_move)
            {
                case 0:
                    normal_enemy_attack(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 1:
                    lamia_magic_ice(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 2:
                    lamia_special_move(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 3:
                    lamia_magic_ice(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;

                case 4:
                    normal_enemy_attack(
                        player,
                        enemy,
                        attack,
                        battle_mode
                    );
                    break;
            }
            break;
        }

        case ENEMY_DRAGON:
        {
            if(enemy->charging)
            {
                add_battle_log("岩をも溶かす灼熱の息を吐いた！");

                enemy->charging = false;

                int enemy_damage = attack * 3;

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
                return;
            }
            else
            {
                int boss_move = rand() % 5;

                switch(boss_move)
                {
                    case 0:
                        normal_enemy_attack(
                            player,
                            enemy,
                            attack,
                            battle_mode
                        );
                        break;

                    case 1:
                        dragon_smash(
                            player,
                            enemy,
                            attack,
                            battle_mode
                        );
                        break;

                    case 2:
                        dragon_breath(
                            player,
                            enemy,
                            attack,
                            battle_mode
                        );
                        break;

                    case 3:
                        if(enemy->hp <= 50)
                        {
                            dragon_heal(
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

                    case 4:
                        if(enemy->hp <= 70)
                        {
                            dragon_charge_breath(
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
                }
                break;
            }
        }
    }
}
