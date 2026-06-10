#ifndef ENEMY_H
#define ENEMY_H

typedef struct {

    char name[20];

    int hp;
    int max_hp;

    int attack;
    int defense;

    int exp;

} Enemy;

void init_enemy(Enemy *e);

#endif
