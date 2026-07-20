#include <stdio.h>

#include "save.h"

bool save_game(Player *player)
{
    FILE *fp = fopen("save.dat", "wb");

    if(fp == NULL)
    {
        return false;
    }

    if(fwrite(player, sizeof(Player), 1, fp) != 1)
    {
        fclose(fp);
        return false;
    }

    fclose(fp);

    return true;
}

bool load_game(Player *player)
{
    FILE *fp = fopen("save.dat", "rb");

    if(fp == NULL)
    {
        return false;
    }

    if(fread(player, sizeof(Player), 1, fp) != 1)
    {
        fclose(fp);
        return false;
    }

    fclose(fp);

    calc_player_status(player);

    return true;
}
