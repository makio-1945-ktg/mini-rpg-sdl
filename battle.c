#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "battle.h"

#define LOG_LINES 3

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

bool battle_attack(
    Player *player,
    Enemy *enemy,
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect
    )
    {
    int player_damage =
        player->attack - enemy->defense;

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
        sprintf(msg,"プレイヤーの攻撃！%dダメージ！", player_damage);
        add_battle_log(msg);

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
                   player->exp);

            player->gold += enemy->gold;

            printf("%d GOLD獲得！\n",
                    enemy->gold);

            printf("所持金:%d G\n",
                    player->gold);

        if(player->exp >= 30)
        {

            player->level++;

            player->exp -= 30;

            player->max_hp += 5;
            player->hp = player->max_hp;

            player->max_mp += 2;
            player->mp = player->max_mp;

            player->attack += 1;
            player->defense += 1;

            printf("レベルアップ！\n");
            printf("Lv:%d\n", player->level);
            printf("HP:%d\n", player->hp);
            printf("MP:%d\n", player->mp);
            printf("ATK:%d\n", player->attack);
            printf("DEF:%d\n", player->defense);
        }
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

    char msg[128];
    sprintf(msg,"防御！%dダメージ！", enemy_damage);
    add_battle_log(msg);
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
        return false;
    }

    player->mp -= 3;

    player->hp += 10;

    if(player->hp > player->max_hp)
    {
        player->hp = player->max_hp;
    }

    add_battle_log("ヒール！ HP+10");

    printf("HP:%d\n",
           player->hp);

    printf("MP:%d\n",
           player->mp);

    return enemy_turn(
        player,
        enemy
    );
}

bool battle_fire(
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect
)
{
    if(player->mp < 4)
    {
        add_battle_log("MPが足りない！");
        return false;
    }

    player->mp -= 4;

    fire_effect->active = true;
    fire_effect->timer = 20;

    int fire_damage =
        player->attack + 8
        - enemy->defense / 2;

    if(fire_damage < 1)
    {
        fire_damage = 1;
    }

    enemy->hp -= fire_damage;

    char msg[128];
    sprintf(
        msg,
        "ファイアを唱えた！ %dダメージ！",
        fire_damage
    );

    add_battle_log(msg);

    if(enemy->hp <= 0)
    {
        enemy->hp = 0;
        return true;
    }

    return enemy_turn(
        player,
        enemy
    );
}

bool battle_ice(
    Player *player,
    Enemy *enemy,
    IceEffect *ice_effect
)
{
    if(player->mp < 4)
    {
        add_battle_log("MPが足りない！");
        return false;
    }

    player->mp -= 4;

    ice_effect->active = true;
    ice_effect->timer = 20;

    int ice_damage =
        player->attack + 6
        - enemy->defense;

    if(ice_damage < 1)
    {
        ice_damage = 1;
    }

    enemy->hp -= ice_damage;

    char msg[128];
    sprintf(
        msg,
        "アイスを唱えた！ %dダメージ！",
        ice_damage
    );

    add_battle_log(msg);

    if(enemy->hp <= 0)
    {
        enemy->hp = 0;
        return true;
    }

    return enemy_turn(
        player,
        enemy
    );
}

bool battle_item(
    Player *player,
    Enemy *enemy
)
{
    if(player->potion <= 0)
    {
        printf("ポーションが無い！\n");

        return false;
    }

    player->potion--;

    player->hp += 20;

    if(player->hp > player->max_hp)
    {
        player->hp = player->max_hp;
    }

    printf("ポーションを使った！\n");

    printf("HP:%d\n",
           player->hp);

    printf("残り:%d個\n",
           player->potion);

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

    char msg[128];
    sprintf(msg,"敵の攻撃！%dダメージ！", enemy_damage);
    add_battle_log(msg);

    printf("プレイヤーHP:%d\n",
           player->hp);

    if(player->hp <= 0)
    {
        printf("ゲームオーバー！\n");

        return true;
    }

    return false;
}

