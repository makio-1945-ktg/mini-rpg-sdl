#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "inventory.h"
#include "message_ui.h"
#include "shop.h"
#include "item_shop.h"

void handle_item_shop_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *item_shop_cursor,
    Player *player
)
{
    if(event->key.keysym.sym == SDLK_UP)
    {
        (*item_shop_cursor)--;

        if(*item_shop_cursor < 0)
            *item_shop_cursor = 3;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*item_shop_cursor)++;

        if(*item_shop_cursor > 3)
            *item_shop_cursor = 0;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*item_shop_cursor)
        {
            case 0:
                buy_potion(player);
                break;

            case 1:
                buy_ether(player);
                break;

            case 2:
                buy_rope(player);
                break;

            case 3:
                show_message("またのお越しを！");
                *battle_mode = MODE_FIELD;
                break;
        }
    }
}

void buy_potion(Player *player)
{
    if(player->gold < 10)
    {
        show_message("お金が足りない！");
        return;
    }

    player->gold -= 10;

    player->inventory.potion++;

    show_message("ポーションを購入した！");
}

void buy_ether(Player *player)
{
    if(player->gold < 30)
    {
        show_message("お金が足りない！");
        return;
    }

    player->gold -= 30;

    player->inventory.ether++;

    show_message("エーテルを購入した！");
}

void buy_rope(Player *player)
{
    if(player->gold < 50)
    {
        show_message("お金が足りない！");
        return;
    }

    player->gold -= 50;

    player->inventory.rope++;

    show_message("戻りの紐を購入した！");
}
