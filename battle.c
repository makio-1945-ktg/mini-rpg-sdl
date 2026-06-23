#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "battle.h"
#include "map.h"

int apply_element_resistance(
    int damage,
    int resist
)
{
    return damage * resist / 100;
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

    fire_damage = 
        fire_damage *
        (100 - enemy->fire_resist)
        / 100;

    if(enemy->fire_resist == 100)
    {
        add_battle_log("効果がない！");
    }
    else if(enemy->fire_resist >= 50)
    {
        add_battle_log("あまり効いてないようだ…");
    }
    else if(enemy->fire_resist < 0)
    {
        add_battle_log("弱点を突いた！");
    }

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

    ice_damage =
        ice_damage *
        (100 - enemy->ice_resist)
        / 100;

    if(enemy->ice_resist == 100)
    {
        add_battle_log("効果がない！");
    }
    else if(enemy->ice_resist >= 50)
    {
        add_battle_log("あまり効いてないようだ…");
    }
    else if(enemy->ice_resist < 0)
    {
        add_battle_log("弱点を突いた！");
    }

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

    if(rand() % 4 == 0)
    {
        enemy->frozen = true;
        enemy->frozen_timer = 1;

        add_battle_log("敵が凍った！攻撃力低下！");
    }

    return enemy_turn(
        player,
        enemy
    );
}

bool battle_thunder(
    Player *player,
    Enemy *enemy,
    ThunderEffect *thunder_effect
)
{
    if(player->mp < 5)
    {
        add_battle_log("MPが足りない！");
        return false;
    }

    player->mp -= 5;

    thunder_effect->active = true;
    thunder_effect->timer = 15;

    int thunder_damage =
        player->attack + 10
        - enemy->defense / 2;

    thunder_damage =
        thunder_damage *
        (100 - enemy->thunder_resist)
        / 100;

    if(enemy->thunder_resist == 100)
    {
        add_battle_log("効果がない！");
    }
    else if(enemy->thunder_resist >= 50)
    {
        add_battle_log("あまり効いてないようだ…");
    }
    else if(enemy->thunder_resist < 0)
    {
        add_battle_log("弱点を突いた！");
    }

    if(thunder_damage < 1)
    {
        thunder_damage = 1;
    }

    bool critical = false;

    if(rand() % 4 == 0)
    {
        thunder_damage += 8;
        critical = true;
    }

    enemy->hp -= thunder_damage;

    char msg[128];

    if(critical)
    {
        sprintf(
            msg,
            "唱えたサンダーが直撃した！ %dダメージ！",
            thunder_damage
        );
    }
    else
    {
        sprintf(
            msg,
            "サンダーを唱えた！ %dダメージ！",
            thunder_damage
        );
    }

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
    int enemy_attack = enemy->attack;

    if(enemy->frozen)
    {
            enemy_attack /= 2;
    }

    int enemy_damage =
        enemy_attack
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

    if(enemy->frozen)
    {
        enemy->frozen_timer--;

        if(enemy->frozen_timer <= 0)
        {
            enemy->frozen = false;
            add_battle_log("敵の凍結が溶けた！");
        }
    }

    return false;
}

void handle_normal_battle_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *battle_cursor,
    Player *player,
    Enemy *enemy,
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    EnemySprite *enemy_sprite
)
{
    if(event->key.keysym.sym == SDLK_UP)
    {
        (*battle_cursor)--;

        if(*battle_cursor < 0)
            *battle_cursor = 3;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*battle_cursor)++;

        if(*battle_cursor > 3)
            *battle_cursor = 0;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*battle_cursor)
        {
            case 0:
                enemy_sprite->shake_timer = 12;

                if(battle_attack(
                    player,
                    enemy,
                    popup,
                    hit_effect,
                    slash_effect
                ))
                {
                    *battle_mode = MODE_FIELD;
                }
                break;

            case 1:
                if(battle_defend(player, enemy))
                {
                    *battle_mode = MODE_FIELD;
                }
                break;

            case 2:
                *battle_mode = MODE_MAGIC;
                break;

            case 3:
                if(battle_item(player, enemy))
                {
                    *battle_mode = MODE_FIELD;
                }
                break;
        }
    }
}

void handle_magic_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *magic_cursor,
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect,
    IceEffect *ice_effect,
    ThunderEffect *thunder_effect
)
{
    if(event->key.keysym.sym == SDLK_UP)
    {
        (*magic_cursor)--;

        if(*magic_cursor < 0)
            *magic_cursor = 3;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*magic_cursor)++;

        if(*magic_cursor > 3)
            *magic_cursor = 0;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*magic_cursor)
        {
            case 0:
                if(battle_heal(player, enemy))
                    *battle_mode = MODE_FIELD;
                else
                    *battle_mode = MODE_BATTLE;
                break;

            case 1:
                if(battle_fire(player, enemy, fire_effect))
                    *battle_mode = MODE_FIELD;
                else
                    *battle_mode = MODE_BATTLE;
                break;

            case 2:
                if(battle_ice(player, enemy, ice_effect))
                    *battle_mode = MODE_FIELD;
                else
                    *battle_mode = MODE_BATTLE;
                break;

            case 3:
                if(battle_thunder(player, enemy, thunder_effect))
                    *battle_mode = MODE_FIELD;
                else
                    *battle_mode = MODE_BATTLE;
                break;
        }
    }
}

void start_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture,
    Player *player,
    int new_x,
    int new_y
)
{
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;

    int enemy_type = rand() % 3;

    if(enemy_type == 0)
    {
        *current_enemy_texture = slime_texture;
    }
    else if(enemy_type == 1)
    {
        *current_enemy_texture = goblin_texture;
    }
    else
    {
        *current_enemy_texture = orc_texture;
    }

    strcpy(
        enemy->name,
        enemy_table[enemy_type].name
    );

    enemy->hp =
        enemy_table[enemy_type].hp;

    enemy->max_hp =
        enemy_table[enemy_type].hp;

    enemy->attack =
        enemy_table[enemy_type].attack;

    enemy->defense =
        enemy_table[enemy_type].defense;

    enemy->exp =
        enemy_table[enemy_type].exp;

    enemy->gold =
        enemy_table[enemy_type].gold;

    enemy->fire_resist =
        enemy_table[enemy_type].fire_resist;

    enemy->ice_resist =
        enemy_table[enemy_type].ice_resist;

    enemy->thunder_resist =
        enemy_table[enemy_type].thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;

    enemy_event(new_x, new_y);

    add_battle_log("敵が現れた！");
}

