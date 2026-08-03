//#include <stdio.h>

//#include "temple.h"
//#include "battle.h"
//#include "magic.h"
//#include "enemy.h"

char temple_map[9][11] = {

    "MMMMMMMMM",
    "MMMMGMMMM",
    "MMMGGGMMM",
    "MMGGGGGMM",
    "MGGGGGGGM",
    "MGGGGGGGM",
    "MGGGGGGGM",
    "MMGGGGGMM",
    "MMMGGGMMM",
    "MMMMOMMMM",
    "MMMMMMMMM"
};

char get_temple_tile(int x, int y)
{
    return temple_map[y][x];
}

void handle_temple_event(
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
)
{
    if(tile == 'O')
    {
        *in_temple = false;

        player->x = ;
        player->y = ;

        printf("神殿を出た！\n");
    }
}
