#include <stdio.h>
#include <stdbool.h>

#include "battle.h"
#include "magic.h"

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
    if(player->stunned)
    {
        add_battle_log("スタンで身動きが取れない！");

        player->stun_timer--;

        if(player->stun_timer <= 0)
        {
            player->stunned = false;
        }

        enemy_turn(
            player,
            enemy,
            battle_mode
        );
        return;
    }

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
                *battle_mode = MODE_USE_ITEM;
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

void handle_item_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *use_item_cursor,
    Player *player,
    Enemy *enemy
)
{
    if(event->key.keysym.sym == SDLK_UP)
    {
        (*use_item_cursor)--;

        if(*use_item_cursor < 0)
            *use_item_cursor = 2;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*use_item_cursor)++;

        if(*use_item_cursor > 2)
            *use_item_cursor = 0;
    }

    if(event->key.keysym.sym == SDLK_ESCAPE)
    {
        *battle_mode = MODE_BATTLE;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*use_item_cursor)
        {
            case 0:
                battle_potion(
                    player,
                    enemy,
                    battle_mode
                );
                break;

            case 1:
                battle_ether(
                    player,
                    enemy,
                    battle_mode
                );
                break;

            case 2:
                battle_bomb(
                    player,
                    enemy,
                    battle_mode
                );
                break;
        }
    }
}
