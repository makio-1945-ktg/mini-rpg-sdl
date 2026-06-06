#ifndef ENEMY_H
#define ENEMY_H

typedef struct {
    int hp;
    int attack;
} Enemy;

void init_enemy(Enemy *e);

#endif
