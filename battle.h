#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"

typedef struct {

    int hp;
    int max_hp;

} Enemy;

void battle_start(void);

bool battle_attack(
    Player *player,
    Enemy *enemy
);

#endif
