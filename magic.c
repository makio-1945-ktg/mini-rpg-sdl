#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "magic.h"
#include "battle.h"

typedef struct {
    const char *name;
    int mp_cost;
    int effect_timer;
    int bonus_attack;
    int defense_divisor;
} MagicConfig;

static const MagicConfig FIRE_CONFIG = {"ファイア", 4, 20, 8, 2};

static const MagicConfig ICE_CONFIG = {"アイス", 4, 20, 6, 1};

static const MagicConfig THUNDER_CONFIG = {"サンダー", 5, 15, 10, 2};

static void start_magic_effect(
    MagicEffect *effect,
    int timer
)
{
    effect->active = true;
    effect->timer = timer;
}

static void show_element_message(int resist)
{
    if(resist == 100)
    {
        add_battle_log("効果がない！");
    }
    else if(resist >= 50)
    {
        add_battle_log("あまり効いてないようだ…");
    }
    else if(resist < 0)
    {
        add_battle_log("弱点をついた！");
    }
}

static int calculate_magic_damage(
    int base_damage,
    int resist
)
{
    int damage =
        apply_element_resistance(
            base_damage,
            resist
        );

    show_element_message(resist);

    if(damage < 1)
    {
        damage = 1;
    }

    return damage;
}

static int calculate_spell_damage(
    Player *player,
    Enemy *enemy,
    MagicConfig config,
    int resist
)
{
    int base_damage =
        player->attack
        + config.bonus_attack
        - enemy->defense / config.defense_divisor;

    return calculate_magic_damage(
        base_damage,
        resist
    );
}

static bool consume_mp(
    Player *player,
    int cost,
    BattleMode *battle_mode
)
{
    if(player->mp < cost)
    {
        add_battle_log("MPが足りない！");
        *battle_mode = MODE_BATTLE;
        return false;
    }

    player->mp -= cost;
    return true;
}

static void build_spell_message(
    char *buffer,
    const char *spell_name,
    int damage
)
{
    sprintf(
        buffer,
        "%sを唱えた！ %dダメージ！",
        spell_name,
        damage
    );
}

static void finish_magic_attack(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode,
    int damage,
    const char *message
)
{
    enemy->hp -= damage;

    add_battle_log(message);

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
}

static int cast_magic(
    Player *player,
    Enemy *enemy,
    MagicEffect *effect,
    BattleMode *battle_mode,
    MagicConfig config,
    int resist
)
{
    if(!consume_mp(player, config.mp_cost, battle_mode))
    {
        return -1;
    }

    start_magic_effect(
        effect,
        config.effect_timer
    );

    int damage =
        calculate_spell_damage(
            player,
            enemy,
            config,
            resist
        );

    char msg[128];
    build_spell_message(
        msg,
        config.name,
        damage
    );

    finish_magic_attack(
        player,
        enemy,
        battle_mode,
        damage,
        msg
    );
    return damage;
}

void battle_fire(
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect,
    BattleMode *battle_mode
)
{
    int damage =
        cast_magic(
            player,
            enemy,
            fire_effect,
            battle_mode,
            FIRE_CONFIG,
            enemy->fire_resist
        );

    if(damage < 0)
    {
        return;
    }

    if(rand() % 100 < 30)
    {
        enemy->burning = true;
        enemy->burn_timer = 3;

        add_battle_log("敵は火傷を負った！");
    }
}

void battle_ice(
    Player *player,
    Enemy *enemy,
    IceEffect *ice_effect,
    BattleMode *battle_mode
)
{
    int damage =
        cast_magic(
            player,
            enemy,
            ice_effect,
            battle_mode,
            ICE_CONFIG,
            enemy->ice_resist
        );

    if(damage < 0)
    {
        return;
    }

    if(rand() % 100 < 25)
    {
        enemy->frozen = true;
        enemy->frozen_timer = 1;

        add_battle_log("敵が凍った！");
    }
}

void battle_thunder(
    Player *player,
    Enemy *enemy,
    ThunderEffect *thunder_effect,
    BattleMode *battle_mode
)
{
    int damage =
        cast_magic(
            player,
            enemy,
            thunder_effect,
            battle_mode,
            THUNDER_CONFIG,
            enemy->thunder_resist
        );

    if(damage < 0)
    {
        return;
    }

    if(rand() % 100 < 20)
    {
        enemy->stunned = true;
        enemy->stun_timer = 1;

        add_battle_log("敵は感電した！");
    }
}
