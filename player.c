#include "player.h"

Player create_player(void)
{
    Player player = {
        .x = 2,
        .y = 2,

        .hp = 30,
        .max_hp = 30,

        .mp = 10,
        .max_mp = 10,

        player.base_attack = 6,
        player.base_defense = 2,

        player.attack = player.base_attack,
        player.defense = player.base_defense,

        .level = 1,
        .exp = 0,
        .gold = 10,

        .inventory = {
            .potion = 2,
            .ether = 0
        },

        .equipment = {
            .sword = 0
        }
    };

    calc_player_status(&player);

    return player;
}

void calc_player_status(Player *player)
{
    player->attack = player->base_attack;
    player->defense = player->base_defense;

    if(player->equipment.sword)
    {
        player->attack += 2;
    }

    if(player->equipment.leather_armor)
    {
        player->defense += 4;
    }

    if(player->equipment.wooden_shield)
    {
        player->defense += 2;
    }
}

