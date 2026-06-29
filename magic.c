#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "magic.h"
#include "battle.h"

typedef struct
{
    int mp_cost;
    int effect_timer;
    int bonus_attack;
    int defense_divisor;
} MagicConfig;

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

static void cast_magic(
    Player *player,
    Enemy *enemy,
    MagicEffect *effect,
    BattleMode *battle_mode,
    MagicConfig config,
    int resist,
    const char *spell_name
)
{
    if(!consume_mp(player, config.mp_cost, battle_mode))
    {
        return;
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
    sprintf(
        msg,
        "%sを唱えた！ %dダメージ！",
        spell_name,
        damage
    );

    finish_magic_attack(
        player,
        enemy,
        battle_mode,
        damage,
        msg
    );
}

void battle_fire(
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect,
    BattleMode *battle_mode
)
{
    MagicConfig fire = {4, 20, 8, 2};

    cast_magic(
        player,
        enemy,
        fire_effect,
        battle_mode,
        fire,
        enemy->fire_resist,
        "ファイア"
    );
}

void battle_ice(
    Player *player,
    Enemy *enemy,
    IceEffect *ice_effect,
    BattleMode *battle_mode
)
{
    MagicConfig ice = {4, 20, 6, 1};

    if(!consume_mp(player, ice.mp_cost, battle_mode))
    {
        return;
    }

    start_magic_effect(
        ice_effect,
        ice.effect_timer
    );

    int ice_damage =
        calculate_spell_damage(
            player,
            enemy,
            ice,
            enemy->ice_resist
        );

    char msg[128];
    sprintf(
        msg,
        "アイスを唱えた！ %dダメージ！",
        ice_damage
    );

    if(rand() % 4 == 0)
    {
        enemy->frozen = true;
        enemy->frozen_timer = 1;

        add_battle_log("敵が凍った！攻撃力低下！");
    }

    finish_magic_attack(
        player,
        enemy,
        battle_mode,
        ice_damage,
        msg
    );
}

void battle_thunder(
    Player *player,
    Enemy *enemy,
    ThunderEffect *thunder_effect,
    BattleMode *battle_mode
)
{
    MagicConfig thunder = {5, 15, 10, 2};

    if(!consume_mp(player, thunder.mp_cost, battle_mode))
    {
        return;
    }

    start_magic_effect(
        thunder_effect,
        thunder.effect_timer
    );

    int thunder_damage =
        calculate_spell_damage(
            player,
            enemy,
            thunder,
            enemy->thunder_resist
        );

    bool critical = false;

    if(rand() % 4 == 0)
    {
        thunder_damage += 8;
        critical = true;
    }
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

    finish_magic_attack(
        player,
        enemy,
        battle_mode,
        thunder_damage,
        msg
    );
}
