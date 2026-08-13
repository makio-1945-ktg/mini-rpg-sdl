#include <stdio.h>

#include "save.h"

bool save_game(GameState *game)
{
    FILE *fp = fopen("save.dat", "wb");

    if(fp == NULL)
    {
        return false;
    }

    if(fwrite(game, sizeof(GameState), 1, fp) != 1)
    {
        fclose(fp);
        return false;
    }

    fclose(fp);

    return true;
}

bool load_game(GameState *game)
{
    FILE *fp = fopen("save.dat", "rb");

    if(fp == NULL)
    {
        return false;
    }

    if(fread(game, sizeof(GameState), 1, fp) != 1)
    {
        fclose(fp);
        return false;
    }

    fclose(fp);

    calc_player_status(&game->player);

    return true;
}
