#ifndef SAVE_H
#define SAVE_H

#include <stdbool.h>

#include "game_state.h"

bool save_game(GameState *game);

bool load_game(GameState *game);

#endif
