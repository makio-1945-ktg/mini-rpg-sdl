#ifndef PLAYER_H
#define PLAYER_H

typedef struct {

    int x;
    int y;

    int hp;
    int max_hp;

    int mp;
    int max_mp;

    int attack;
    int defense;

    int level;

    int exp;

}Player;

#endif
