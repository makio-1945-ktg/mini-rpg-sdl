#ifndef SAVE_H
#define SAVE_H

#include <stdbool.h>

#include "player.h"

bool save_game(Player *player);

bool load_game(Player *player);

#endif
