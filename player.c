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

        .attack = 6,
        .defense = 2,

        .level = 1,
        .exp = 0,
        .gold = 10,

        .inventory = {
            .potion = 2
        },

        .equipment = {
            .sword = 0
        }
    };

    return player;
}
