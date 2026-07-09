#include <stdio.h>

#include "map.h"
#include "chest.h"
#include "equipment.h"

char field_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MVGGGGGTGGGGGGGGGGGM",
    "MCGEGGGGEGGGGGGGGGGM",
    "MEGGGGEGGGGGGGGWWWGM",
    "MGGGGGGGGGGGGGWWWGGM",
    "MGGGGGGGGGGGGGGWWWGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGEEGGGGGGGM",
    "MGGGGGGGGGEEGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MMMMMMMMMMMMMMMMMMMM"
};

char get_tile(int x, int y)
{
    return field_map[y][x];
}

void town_event(void)
{
    printf("町に到着しました！\n");
}

void inn_event(Player *player)
{
    if(player->gold < 10)
    {
        printf("お金が足りない！\n");
        return;
    }

    player->gold -= 10;

    player->hp = player->max_hp;
    player->mp = player->max_mp;

    printf("宿屋に泊まった！\n");

    printf("HP:%d\n",
           player->hp);

    printf("MP:%d\n",
           player->mp);

    printf("所持金:%dG\n",
           player->gold);
}

void npc_event(void)
{
    printf("こんにちは！\n");
}

void enemy_event(int x, int y)
{
    printf("敵が現れた！\n");

    field_map[y][x] = 'G';
}

void handle_field_event(
    char tile,
    bool *in_town,
    bool *in_cave,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
)
{
    if(tile == 'T')
    {
        town_event();

        *in_town = true;

        player->x = 3;
        player->y = 5;
    }

    if(tile == 'O')
    {
        *in_town = false;
        player->x = 7;
        player->y = 1;
        printf("町を出た！\n");
    }

    if(tile == 'V')
    {
        *in_cave = true;

        player->x = 1;
        player->y = 1;

        printf("洞窟に入った！\n");
    }

    if(tile == 'N')
    {
        npc_event();
    }

    if(tile == 'I')
    {
        inn_event(player);
    }

    if(tile == 'Q')
    {
        equipment_shop_event(player);
    }

    if(tile == 'C')
    {
        chest_event(
            player,
            field_map,
            new_x,
            new_y
        );
    }

    if(tile == 'E')
    {
        start_battle(
            battle_mode,
            battle_cursor,
            magic_cursor,
            enemy,
            current_enemy_texture,
            slime_texture,
            goblin_texture,
            orc_texture,
            player,
            new_x,
            new_y
        );
    }
}
char town_map[8][9] = {

    "MMMMMMM",
    "MGGGGGM",
    "MGIGQGM",
    "MGGGGGM",
    "MGNGGGM",
    "MGGGGGM",
    "MGGOGGM",
    "MMMMMMM"
};

char get_town_tile(int x, int y)
{
    return town_map[y][x];
}
