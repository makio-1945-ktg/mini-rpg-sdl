#ifndef ENEMY_SKILL_H
#define ENEMY_SKILL_H

#include "player.h"
#include "enemy.h"
#include "battle.h"

void normal_enemy_attack(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
);

void enemy_action(
    Player *player,
    Enemy *enemy,
    int attack,
    BattleMode *battle_mode
);

#endif
