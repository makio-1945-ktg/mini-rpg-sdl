// input_save.c
#include <string.h>

#include "input_save.h"
#include "save.h"
#include "game_state.h"
#include "map.h"
#include "cave.h"
#include "cave_b1.h"
#include "cave_b2.h"
#include "temple.h"
#include "message_ui.h"

static void copy_maps_to_state(GameState *game)
{
    memcpy(game->field_map, field_map, sizeof(field_map));
    memcpy(game->town_map, town_map, sizeof(town_map));
    memcpy(game->cave_map, cave_map, sizeof(cave_map));
    memcpy(game->cave_b1_map, cave_b1_map, sizeof(cave_b1_map));
    memcpy(game->cave_b2_map, cave_b2_map, sizeof(cave_b2_map));
    memcpy(game->temple_map, temple_map, sizeof(temple_map));
}

static void copy_maps_from_state(const GameState *game)
{
    memcpy(field_map, game->field_map, sizeof(field_map));
    memcpy(town_map, game->town_map, sizeof(town_map));
    memcpy(cave_map, game->cave_map, sizeof(cave_map));
    memcpy(cave_b1_map, game->cave_b1_map, sizeof(cave_b1_map));
    memcpy(cave_b2_map, game->cave_b2_map, sizeof(cave_b2_map));
    memcpy(temple_map, game->temple_map, sizeof(temple_map));
}

void handle_save_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *save_cursor,
    Player *player,
    bool *in_town,
    bool *in_cave,
    bool *in_cave_b1,
    bool *in_cave_b2,
    bool *in_temple
)
{
    if(event->key.keysym.sym == SDLK_ESCAPE)
    {
        *battle_mode = MODE_FIELD;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*save_cursor)
        {
            case 0:
            {
                GameState game;

                game.player = *player;
                game.in_town = *in_town;
                game.in_cave = *in_cave;
                game.in_cave_b1 = *in_cave_b1;
                game.in_cave_b2 = *in_cave_b2;
                game.in_temple = *in_temple;

                copy_maps_to_state(&game);

                if(save_game(&game))
                {
                    show_message("セーブしました！");
                }
                else
                {
                    show_message("セーブに失敗しました");
                }
                break;
            }

            case 1:
            {
                GameState game;

                if(load_game(&game))
                {
                    *player = game.player;
                    *in_town = game.in_town;
                    *in_cave = game.in_cave;
                    *in_cave_b1 = game.in_cave_b1;
                    *in_cave_b2 = game.in_cave_b2;
                    *in_temple = game.in_temple;

                    copy_maps_from_state(&game);

                    show_message("ロードしました！");
                }
                else
                {
                    show_message("ロードに失敗しました");
                }
                break;
            }
        }
    }

    if(event->key.keysym.sym == SDLK_UP)
    {
        (*save_cursor)--;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*save_cursor)++;
    }

    if(*save_cursor < 0)
    {
        *save_cursor = 1;
    }

    if(*save_cursor > 1)
    {
        *save_cursor = 0;
    }
}
