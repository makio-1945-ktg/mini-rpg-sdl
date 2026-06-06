#include "player.h"

void init_player(Player *p) {
    p->max_hp = 30;
    p->hp = 30;
    p->attack = 15;
    p->defense = 10;
}
