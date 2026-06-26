#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

static void enemy_defeat(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
)
void battle_fire(
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect,
    BattleMode *battle_mode
)
{
    if(player->mp < 4)
    {
        add_battle_log("MPが足りない！");
        *battle_mode = MODE_BATTLE;
        return;
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

