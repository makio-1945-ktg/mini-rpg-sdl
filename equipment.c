#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "equipment.h"
#include "message_ui.h"
#include "shop.h"

void handle_shop_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *shop_cursor,
    Player *player
)
{
    if(event->key.keysym.sym == SDLK_UP)
    {
        (*shop_cursor)--;

        if(*shop_cursor < 0)
            *shop_cursor = 2;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*shop_cursor)++;

        if(*shop_cursor > 2)
            *shop_cursor = 0;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*shop_cursor)
        {
            case 0:
                buy_sword(player);
                break;

            case 1:
                buy_leather_armor(player);
                break;

            case 2:
                show_message("またのお越しを！");
                *battle_mode = MODE_FIELD;
                break;
        }
    }
}

void buy_sword(Player *player)
{
    if(player->equipment.sword)
    {
        show_message("すでに装備している！");
        return;
    }

    if(player->gold < 20)
    {
        show_message("お金が足りない！");
        return;
    }

    player->gold -= 20;

    player->equipment.sword = true;

    calc_player_status(player);

    show_message("剣を購入した！");
}

void buy_leather_armor(Player *player)
{
    if(player->equipment.leather_armor)
    {
        show_message("すでに装備している！");
        return;
    }

    if(player->gold < 30)
    {
        show_message("お金が足りない！");
        return;
    }

    player->gold -= 30;

    player->equipment.leather_armor = true;

    calc_player_status(player);

    show_message("皮の鎧を購入した！");
}

