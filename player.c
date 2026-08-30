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

        player.attack = 6,
        player.defense = 2,

        .level = 1,
        .exp = 0,
        .gold = 20,

        .inventory = {
            .potion = 2,
            .ether = 0,
            .bomb = 0,
            .dragon_jewel = 0
        },
//この部分は　equipment = {0}　でも動作可能
        .equipment = {
            .sword = false,
            .sword_equipped = false,

            .leather_armor = false,
            .leather_armor_equipped = false,

            .wooden_shield = false,
            .wooden_shield_equipped = false,

            .broad_sword = false,
            .broad_sword_equipped = false,

            .rune_sword = false,
            .rune_sword_equipped = false,

            .rune_armor = false,
            .rune_armor_equipped = false,

            .rune_shield = false,
            .rune_shield_equipped = false

        }
    };

    calc_player_status(&player);

    return player;
}

void calc_player_status(Player *player)
{
    player->attack = player->base_attack;
    player->defense = player->base_defense;

    if(player->equipment.sword_equipped)
    {
        player->attack += 2;
    }

    if(player->equipment.leather_armor_equipped)
    {
        player->defense += 4;
    }

    if(player->equipment.wooden_shield_equipped)
    {
        player->defense += 2;
    }

    if(player->equipment.broad_sword_equipped)
    {
        player->attack += 5;
    }

    if(player->equipment.rune_sword_equipped)
    {
        player->attack += 9;
    }

    if(player->equipment.rune_armor_equipped)
    {
        player->defense += 8;
    }

    if(player->equipment.rune_shield_equipped)
    {
        player->defense += 5;
    }
}

