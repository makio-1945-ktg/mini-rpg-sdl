#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <stdbool.h>

typedef struct Player Player;

typedef struct {

    bool sword;
    bool sword_equipped;

    bool leather_armor;
    bool leather_armor_equipped;

    bool wooden_shield;
    bool wooden_shield_equipped;

    bool broad_sword;
    bool broad_sword_equipped;

    bool rune_sword;
    bool rune_sword_equipped;

    bool rune_armor;
    bool rune_armor_equipped;

    bool rune_shield;
    bool rune_shield_equipped;

} Equipment;

void buy_sword(
    Player *player
);

void buy_leather_armor(
    Player *player
);

#endif
