#ifndef PLAYER_H
#define PLAYER_H

typedef struct {

    int x;
    int y;

    int hp;
    int max_hp;
    int attack;
    int defense;
}Player;

void init_player(Player *p);

#endif
