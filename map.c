#include <stdio.h>

#include "map.h"
#include "chest.h"
#include "equipment.h"
#include "message_ui.h"

char field_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MGGGGGGTGGGGGGGGGGGM",
    "MCGEGGGGEGGGGGGGGGGM",
    "MEGGGGEGGGGGGGGWWWGM",
    "MGGGGGGGGGGGGGWWWVGM",
    "MGGGGGGGGGGGGGGWWWGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGGGGGGGGGGGGGGGM",
    "MGGGGWWWGGGGGGGGGGGM",
    "MGGGGGWWWGGGGGGGGGGM",
    "MGGGSGGGGGGGGGGGGGGM",
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
    show_message("町に到着しました！");
}

void inn_event(Player *player)
{
    if(player->gold < 10)
    {
        show_message("お金が足りない！");
        return;
    }

    player->gold -= 10;

    player->hp = player->max_hp;
    player->mp = player->max_mp;

    show_message("宿屋に泊まってステータス全快！");
}

void npc_event(void)
{
    show_message("こんにちは！");
}

void enemy_event(
    char map[15][21],
    int x,
    int y
)
{
    map[y][x] = '.';
}

void handle_field_event(
    char tile,
    bool *in_town,
    bool *in_cave,
    bool *in_temple,
    Player *player,
    int new_x,
    int new_y,
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
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
        show_message("町を出た！");
    }

    if(tile == 'V')
    {
        *in_cave = true;

        player->x = 1;
        player->y = 1;

        show_message("洞窟に入った！");
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

    if(tile == 'S')
    {
        *in_temple = true;

        player->x = 4;
        player->y = 8;

        show_message("謎の神殿に入った！");
    }

    if(tile == 'E')
    {
        start_battle(
            battle_mode,
            battle_cursor,
            magic_cursor,
            use_item_cursor,
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
