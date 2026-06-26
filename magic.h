#ifndef MAGIC_H
#define MAGIC_H

#include "battle.h"

void battle_fire(
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect,
    BattleMode *battle_mode
);

void battle_ice(
    Player *player,
    Enemy *enemy,
    IceEffect *ice_effect,
    BattleMode *battle_mode
);

void battle_thunder(
    Player *player,
    Enemy *enemy,
    ThunderEffect *thunder_effect,
    BattleMode *battle_mode
);

#endif
