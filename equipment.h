#ifndef EQUIPMENT_H
#define EQUIPMENT_H

typedef struct Player Player;

typedef struct {

    int sword;

    int leather_armor;

    int wooden_shield;

} Equipment;

void equipment_shop_event(
    Player *player
);

#endif
