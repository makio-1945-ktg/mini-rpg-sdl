#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"

typedef struct {

    char name[20];

    int hp;
    int max_hp;

    int attack;
    int defense;

} Enemy;

typedef struct {

    char name[20];

    int hp;
    int attack;
    int defense;

} EnemyData;

void battle_start(void);

bool battle_attack(
    Player *player,
    Enemy *enemy
);

#endif
