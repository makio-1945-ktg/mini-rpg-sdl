#include <stdio.h>

#include "map.h"

char field_map[15][21] = {

    "MMMMMMMMMMMMMMMMMMMM",
    "MGGGGGGTGGGGGGGGGGGM",
    "MCGEGGGGEGGGGGGGGGGM",
    "MEGGGGEGGGGGGGGWWWGM",
    "MMMMMMMMGGGGGGWWWGGM",
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

void equipment_shop_event(Player *player)
{
    if(player->sword)
    {
        printf("既に剣を持っている！\n");
        return;
    }

    if(player->gold < 20)
    {
        printf("お金が足りない！\n");
        return;
    }

    player->gold -= 20;

    player->attack++;

    player->sword = 1;

    printf("剣を購入した！\n");

    printf("ATK:%d\n",
           player->attack);

    printf("所持金:%dG\n",
           player->gold);
}

void npc_event(void)
{
    printf("こんにちは！\n");
}

void chest_event(
    Player *player,
    int x,
    int y
)

{
    player->potion++;

    printf("ポーションを入手した！\n");
    printf("現在:%d個\n",
           player->potion);

    open_chest(
        x,
        y
    );
}

void open_chest(
    int x,
    int y
)

{
    field_map[y][x] = '.';
}

void enemy_event(int x, int y)
{
    printf("敵が現れた！\n");

    field_map[y][x] = 'G';
}

void handle_field_event(
    char tile,
    bool *in_town,
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

        player->x = 6;
        player->y = 1;
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
