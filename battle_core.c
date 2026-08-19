#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "battle.h"
#include "enemy_skill.h"
#include "map.h"
#include "magic.h"
#include "cave.h"
#include "cave_b1.h"
#include "cave_b2.h"
#include "temple.h"
#include "message_ui.h"

//必要累積EXP計算式
int required_exp(int level)
{
    return 10 * level * (level + 1);
}
//属性魔法関連
int apply_element_resistance(
    int damage,
    int resist
)
{
    return damage * (100 - resist) / 100;
}

static bool apply_burn_damage(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(!enemy->burning)
    {
        return false;
    }

    int burn_damage =
        enemy->max_hp * 5 /100;

    if(burn_damage < 1)
    {
        burn_damage = 1;
    }

    enemy->hp -= burn_damage;
    enemy->burn_timer--;

    char msg[128];
    sprintf(
        msg,
        "火傷で%dダメージ！",
        burn_damage
    );
    add_battle_log(msg);

    if(enemy->hp <= 0)
    {
        enemy->hp = 0;
        enemy->burning = false;

        enemy_defeat(
            player,
            enemy,
            battle_mode
        );
        return true;
    }

    if(enemy->burn_timer <=0)
    {
        enemy->burning = false;
        add_battle_log("敵の火傷が治った！");
    }
    return false;
}

char battle_logs[LOG_LINES][128] = {
    "",
    "",
    ""
};

void add_battle_log(const char *message)
{
    strcpy(battle_logs[0], battle_logs[1]);
    strcpy(battle_logs[1], battle_logs[2]);
    strcpy(battle_logs[2], message);
}

void show_damage_popup(
    DamagePopup *popup,
    int damage,
    int x,
    int y
)
{
    sprintf(popup->text, "-%d", damage);

    popup->x = x;
    popup->y = y;

    popup->timer = 60;
    popup->active = true;
}

void enemy_defeat(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    player->exp += enemy->exp;
    player->gold += enemy->gold;

    char msg[64];
    sprintf(msg, "敵を倒した！%d EXP %d G獲得！", enemy->exp, enemy->gold);
    show_message(msg);

    while(player->exp >= required_exp(player->level))
    {
        player->level++;

        player->max_hp += 10;
        player->hp = player->max_hp;

        player->max_mp += 5;
        player->mp = player->max_mp;

        player->base_attack += 1;
        player->base_defense += 1;

        calc_player_status(player);

        show_message("レベルアップ！");
        printf("Lv:%d\n", player->level);
    }
    end_battle(battle_mode);
}

void end_battle(
    BattleMode *battle_mode
)
{
    *battle_mode = MODE_FIELD;
}

void battle_attack(
    Player *player,
    Enemy *enemy,
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    BattleMode *battle_mode
    )
    {
    int player_attack = player->attack;

    if(player->frozen)
    {
        player_attack /= 2;

        add_battle_log(
            "凍結で攻撃力が低下中！"
        );
    }

    int player_damage =
        player_attack - enemy->defense;

    if(player_damage < 1)
    {
        player_damage = 1;
    }

    show_damage_popup(
        popup,
        player_damage,
        460,
        90
    );

    hit_effect->active = true;
    hit_effect->timer = 8;

    slash_effect->active = true;
    slash_effect->timer = 8;

    enemy->hp -= player_damage;

        char msg[128];
        sprintf(
            msg,
            "プレイヤーの攻撃！%dダメージ！",
            player_damage
        );

        add_battle_log(msg);

        printf("%s HP:%d\n",
               enemy->name,
               enemy->hp);

        if(enemy->hp <= 0)
        {
            enemy->hp = 0;
            enemy_defeat(
                player,
                enemy,
                battle_mode
            );
            return;
        }

        enemy_turn(
            player,
            enemy,
            battle_mode
        );
        return;
    }

void battle_defend(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    player->defending = true;

    add_battle_log("防御した！");

    enemy_turn(
        player,
        enemy,
        battle_mode
    );
    return;
}

void battle_heal(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(player->mp < 3)
    {
        add_battle_log("MPが足りない！");
        *battle_mode = MODE_BATTLE;
        return;
    }

    player->mp -= 3;

    int heal_amount = player->max_hp * 3 / 10;

    if(heal_amount < 1)
    {
        heal_amount = 1;
    }

    player->hp += heal_amount;

    if(player->hp > player->max_hp)
    {
        player->hp = player->max_hp;
    }

    char msg[64];
    sprintf(msg, "ヒール！ HP+%d", heal_amount);
    add_battle_log(msg);

    printf("HP:%d\n",
           player->hp);

    printf("MP:%d\n",
           player->mp);

    enemy_turn(
        player,
        enemy,
        battle_mode
    );
    return;
}

void battle_potion(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(player->inventory.potion <= 0)
    {
        add_battle_log("ポーションが無い！");
        *battle_mode = MODE_BATTLE;
        return;
    }

    player->inventory.potion--;

    player->hp += 20;

    if(player->hp > player->max_hp)
    {
        player->hp = player->max_hp;

    }

    add_battle_log("ポーションを使った！");

    printf("HP:%d\n",
           player->hp);

    printf("残り:%d個\n",
           player->inventory.potion);

    enemy_turn(
        player,
        enemy,
        battle_mode
    );
    return;
}

void battle_ether(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(player->inventory.ether <= 0)
    {
        add_battle_log("エーテルが無い！");
        *battle_mode = MODE_BATTLE;
        return;
    }

    player->inventory.ether--;

    player->mp += 10;

    if(player->mp > player->max_mp)
    {
        player->mp = player->max_mp;

    }

    add_battle_log("エーテルを使った！");

    printf("MP:%d\n",
           player->mp);

    printf("残り:%d個\n",
           player->inventory.ether);

    enemy_turn(
        player,
        enemy,
        battle_mode
    );
    return;
}

void battle_bomb(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(player->inventory.bomb <= 0)
    {
        add_battle_log("爆薬が無い！");
        *battle_mode = MODE_BATTLE;
        return;
    }

    player->inventory.bomb--;

    int damage = 40;

    enemy->hp -= damage;

    char msg[64];
    sprintf(msg,
            "爆薬を使った！%dダメージ！",
            damage);

    add_battle_log(msg);

    if(enemy->hp < 0)
        enemy->hp = 0;

    printf("%s HP:%d\n",
           enemy->name,
           enemy->hp);

    if(enemy->hp <= 0)
    {
        enemy_defeat(
            player,
            enemy,
            battle_mode
        );
        return;
    }

    printf("残り:%d個\n",
           player->inventory.bomb);

    enemy_turn(
        player,
        enemy,
        battle_mode
    );
    return;
}

void enemy_turn(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(player->frozen)
    {
        player->frozen_timer--;

        if(player->frozen_timer <= 0)
        {
            player->frozen = false;
            add_battle_log("凍結が解けた！");
        }
    }

    if(apply_burn_damage(
        player,
        enemy,
        battle_mode
    ))
    {
        return;
    }

    if(enemy->stunned)
    {
        add_battle_log("敵はスタンして動けない！");

        enemy->stun_timer--;

        if(enemy->stun_timer <= 0)
        {
            enemy->stunned = false;
            add_battle_log("敵のスタンが解けた！");
        }
        return;
    }

    int enemy_attack = enemy->attack;

    if(enemy->frozen)
    {
        enemy_attack /= 2;

        add_battle_log(
            "凍結で敵の攻撃力が低下中！"
        );

        enemy->frozen_timer--;

        if(enemy->frozen_timer <= 0)
        {
            enemy->frozen = false;
            add_battle_log("敵の凍結が解けた！");
        }
    }
//敵の攻撃行動
    enemy_action(
        player,
        enemy,
        enemy_attack,
        battle_mode
    );

    if(player->poisoned)
    {
        add_battle_log("毒のダメージを受けている！");

        player->hp -= 3;

        printf("プレイヤーHP:%d\n",
               player->hp);

        if(player->hp <= 0)
        {
            printf("ゲームオーバー！\n");
            end_battle(battle_mode);
        }

        player->poison_timer--;

        if(player->poison_timer <= 0)
        {
            player->poisoned = false;
            add_battle_log("体の毒が中和された！");
        }
    }

    if(player->burning)
    {
        add_battle_log("火傷ダメージを受けている！");

        player->hp -= 5;

        printf("プレイヤーHP:%d\n",
               player->hp);

        if(player->hp <= 0)
        {
            printf("ゲームオーバー！\n");
            end_battle(battle_mode);
        }

        player->burn_timer--;

        if(player->burn_timer <= 0)
        {
            player->burning = false;
            add_battle_log("火傷が治った！");
        }
    }

    player->defending = false;
}

