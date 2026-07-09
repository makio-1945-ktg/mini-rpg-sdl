#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include "equipment.h"

typedef struct Player {
//プレイヤー座標
    int x;
    int y;
//プレイヤーステータス
    int hp;
    int max_hp;

    int mp;
    int max_mp;

    int base_attack;
    int base_defense;

    int attack;
    int defense;

    int level;
    int exp;
    int gold;
//プレイヤーアイテム
    Inventory inventory;
//プレイヤー装備
    Equipment equipment;
} Player;

Player create_player(void);

void calc_player_status(
    Player *player
);

#endif
