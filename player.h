#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include "equipment.h"

typedef struct {
//プレイヤー座標
    int x;
    int y;
//プレイヤーステータス
    int hp;
    int max_hp;

    int mp;
    int max_mp;

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

#endif
