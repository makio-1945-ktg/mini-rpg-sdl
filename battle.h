#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"

typedef struct {

    char name[20];

    int hp;
    int max_hp;

    int attack;
    int defense;

    int exp;
    int gold;

} Enemy;

typedef struct {

    char name[20];

    int hp;
    int attack;
    int defense;

    int exp;
    int gold;

} EnemyData;

void battle_start(void);

bool battle_attack(
    Player *player,
    Enemy *enemy
);

bool battle_defend(
    Player *player,
    Enemy *enemy
);

bool battle_heal(
    Player *player,
    Enemy *enemy
);

bool battle_item(
    Player *player,
    Enemy *enemy
);

bool enemy_turn(
    Player *player,
    Enemy *enemy
);

#endif
