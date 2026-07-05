#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "battle.h"
#include "map.h"
#include "magic.h"
#include "enemy.h"
#include "cave.h"
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
    printf("敵を倒した！\n");

    player->exp += enemy->exp;
    player->gold += enemy->gold;

    printf("%d EXP獲得！\n", enemy->exp);
    printf("%d GOLD獲得！\n", enemy->gold);

    if(player->exp >= 30)
    {
        player->level++;
        player->exp -= 30;

        player->max_hp += 5;
        player->hp = player->max_hp;

        player->max_mp += 5;
        player->mp = player->max_mp;

        player->attack += 1;
        player->defense += 1;

        printf("レベルアップ！\n");
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
        end_battle(battle_mode);
    }
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

    enemy_turn(
        player,
        enemy,
        battle_mode
    );
    return;
}

void battle_item(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
    if(player->inventory.potion <= 0)
    {
        printf("ポーションが無い！\n");
        *battle_mode = MODE_BATTLE;
        return;
    }

    player->inventory.potion--;

    player->hp += 20;

    if(player->hp > player->max_hp)
    {
        player->hp = player->max_hp;

    }

    printf("ポーションを使った！\n");

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
void enemy_turn(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
{
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
        end_battle(battle_mode);
        return;
    }
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

                battle_attack(
                    player,
                    enemy,
                    popup,
                    hit_effect,
                    slash_effect,
                    battle_mode
                );
                break;

            case 1:
                battle_defend(
                    player,
                    enemy,
                    battle_mode
                );
                break;

            case 2:
                *battle_mode = MODE_MAGIC;
                break;

            case 3:
                battle_item(
                    player,
                    enemy,
                    battle_mode
                );
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

    if(event->key.keysym.sym == SDLK_ESCAPE)
    {
        *battle_mode = MODE_BATTLE;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*magic_cursor)
        {
            case 0:
                battle_heal(
                    player,
                    enemy,
                    battle_mode
                );
                break;

            case 1:
                battle_fire(
                    player,
                    enemy,
                    fire_effect,
                    battle_mode
                );
                break;

            case 2:
                battle_ice(
                    player,
                    enemy,
                    ice_effect,
                    battle_mode
                );
                break;

            case 3:
                battle_thunder(
                    player,
                    enemy,
                    thunder_effect,
                    battle_mode
                );
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

    setup_field_enemy(
        enemy,
        current_enemy_texture,
        slime_texture,
        goblin_texture,
        orc_texture
    );

    enemy_event(new_x, new_y);

    add_battle_log("敵が現れた！");
}

void start_cave_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *bat_texture,
    SDL_Texture *skeleton_texture,
    SDL_Texture *golem_texture,
    Player *player,
    int new_x,
    int new_y
)
{
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;

    setup_cave_enemy(
        enemy,
        current_enemy_texture,
        bat_texture,
        skeleton_texture,
        golem_texture
    );

    enemy_event(new_x, new_y);

    add_battle_log("敵が現れた！");
}

