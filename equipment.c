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
        show_message("すでに持っている！");
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
        show_message("すでに持っている！");
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

void equip_sword(Player *player)
{
    if(!player->equipment.sword)
    {
        show_message("剣を持ってない！");
        return;
    }

    if(player->equipment.sword_equipped)
    {
        player->equipment.sword_equipped = false;

        calc_player_status(player);

        show_message("剣を外した！");
        return;
    }

    player->equipment.sword_equipped = true;

    player->equipment.broad_sword_equipped = false;
    player->equipment.rune_sword_equipped = false;

    calc_player_status(player);

    show_message("剣を装備した！");
}
//装備着脱
void equip_broad_sword(Player *player)
{
    if(!player->equipment.broad_sword)
    {
        show_message("ブロードソードを持ってない！");
        return;
    }

    if(player->equipment.broad_sword_equipped)
    {
        player->equipment.broad_sword_equipped = false;

        calc_player_status(player);

        show_message("ブロードソードを外した！");
        return;
    }

    player->equipment.sword_equipped = false;
    player->equipment.broad_sword_equipped = true;
    player->equipment.rune_sword_equipped = false;

    calc_player_status(player);

    show_message("ブロードソードを装備した！");
}

void equip_rune_sword(Player *player)
{
    if(!player->equipment.rune_sword)
    {
        show_message("ルーンソードを持ってない！");
        return;
    }

    if(player->equipment.rune_sword_equipped)
    {
        player->equipment.rune_sword_equipped = false;

        calc_player_status(player);

        show_message("ルーンソードを外した！");
        return;
    }

    player->equipment.sword_equipped = false;
    player->equipment.broad_sword_equipped = false;
    player->equipment.rune_sword_equipped = true;

    calc_player_status(player);

    show_message("ルーンソードを装備した！");
}

void equip_leather_armor(Player *player)
{
    if(!player->equipment.leather_armor)
    {
        show_message("革の鎧を持ってない！");
        return;
    }

    if(player->equipment.leather_armor_equipped)
    {
        player->equipment.leather_armor_equipped = false;

        calc_player_status(player);

        show_message("革の鎧を外した！");
        return;
    }

    player->equipment.leather_armor_equipped = true;
    player->equipment.rune_armor_equipped = false;

    calc_player_status(player);

    show_message("革の鎧を装備した！");
}

void equip_rune_armor(Player *player)
{
    if(!player->equipment.rune_armor)
    {
        show_message("ルーンアーマーを持ってない！");
        return;
    }

    if(player->equipment.rune_armor_equipped)
    {
        player->equipment.rune_armor_equipped = false;

        calc_player_status(player);

        show_message("ルーンアーマーを外した！");
        return;
    }

    player->equipment.leather_armor_equipped = false;
    player->equipment.rune_armor_equipped = true;

    calc_player_status(player);

    show_message("ルーンアーマーを装備した！");
}

void equip_wooden_shield(Player *player)
{
    if(!player->equipment.wooden_shield)
    {
        show_message("木の盾を持ってない！");
        return;
    }

    if(player->equipment.wooden_shield_equipped)
    {
        player->equipment.wooden_shield_equipped = false;

        calc_player_status(player);

        show_message("木の盾を外した！");
        return;
    }

    player->equipment.wooden_shield_equipped = true;
    player->equipment.rune_shield_equipped = false;

    calc_player_status(player);

    show_message("木の盾を装備した！");
}

void equip_rune_shield(Player *player)
{
    if(!player->equipment.rune_shield)
    {
        show_message("ルーンシールドを持ってない！");
        return;
    }

    if(player->equipment.rune_shield_equipped)
    {
        player->equipment.rune_shield_equipped = false;

        calc_player_status(player);

        show_message("ルーンシールドを外した！");
        return;
    }

    player->equipment.wooden_shield_equipped = false;
    player->equipment.rune_shield_equipped = true;

    calc_player_status(player);

    show_message("ルーンシールドを装備した！");
}
