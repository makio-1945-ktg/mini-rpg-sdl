//#ifndef TEMPLE_H
//#define TEMPLE_H

//#include <stdbool.h>
//#include <SDL2/SDL.h>

//#include "player.h"
//#include "battle.h"

extern char temple_map[10][11];

char get_cave_tile(int x, int y);

void handle_cave_event(
    char tile,
    bool *in_temple,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy
);

#endif
