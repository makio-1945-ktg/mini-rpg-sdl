// input_field_menu.c
#include "input_field_menu.h"
#include "equipment.h"
#include "message_ui.h"

void handle_status_input(
    SDL_Event *event,
    BattleMode *battle_mode
)
{
    if(event->key.keysym.sym == SDLK_ESCAPE)
    {
        *battle_mode = MODE_FIELD;
    }
}

void handle_item_menu_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *item_cursor,
    Player *player,
    bool *in_cave,
    bool *in_cave_b1,
    bool *in_cave_b2
)
{
    if(event->key.keysym.sym == SDLK_ESCAPE)
    {
        *battle_mode = MODE_FIELD;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*item_cursor)
        {
            case 0:
                if(player->inventory.potion > 0)
                {
                    player->inventory.potion--;
                    player->hp += 20;

                    if(player->hp > player->max_hp)
                    {
                        player->hp = player->max_hp;
                    }

                    show_message("ポーションを使った！");
                }
                else
                {
                    show_message("ポーションがない！");
                }
                break;

            case 1:
                if(player->inventory.ether > 0)
                {
                    player->inventory.ether--;
                    player->mp += 10;

                    if(player->mp > player->max_mp)
                    {
                        player->mp = player->max_mp;
                    }

                    show_message("エーテルを使った！");
                }
                else
                {
                    show_message("エーテルがない！");
                }
                break;

            case 2:
                if(player->inventory.rope <= 0)
                {
                    show_message("戻りの紐がない！");
                    break;
                }
                if(*in_cave || *in_cave_b1 || *in_cave_b2)
                {
                    player->inventory.rope--;

                    *in_cave = false;
                    *in_cave_b1 = false;
                    *in_cave_b2 = false;

                    player->x = 18;
                    player->y = 4;

                    show_message("戻りの紐で入口へ戻った！");
                }
                else
                {
                    show_message("ここでは使えない！");
                }
                break;

            case 3:
                show_message("戦闘中に使おう！");
                break;

            case 4:
                show_message("？？？？？？");
                break;
        }
    }

    if(event->key.keysym.sym == SDLK_UP)
    {
        (*item_cursor)--;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*item_cursor)++;
    }

    if(*item_cursor < 0)
    {
        *item_cursor = 4;
    }

    if(*item_cursor > 4)
    {
        *item_cursor = 0;
    }
}

void handle_equipment_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *equipment_cursor,
    Player *player
)
{
    if(event->key.keysym.sym == SDLK_ESCAPE)
    {
        *battle_mode = MODE_FIELD;
    }

    if(event->key.keysym.sym == SDLK_RETURN)
    {
        switch(*equipment_cursor)
        {
            case 0: equip_sword(player); break;
            case 1: equip_leather_armor(player); break;
            case 2: equip_wooden_shield(player); break;
            case 3: equip_broad_sword(player); break;
            case 4: equip_rune_sword(player); break;
            case 5: equip_rune_armor(player); break;
            case 6: equip_rune_shield(player); break;
        }
    }

    if(event->key.keysym.sym == SDLK_UP)
    {
        (*equipment_cursor)--;
    }

    if(event->key.keysym.sym == SDLK_DOWN)
    {
        (*equipment_cursor)++;
    }

    if(*equipment_cursor < 0)
    {
        *equipment_cursor = 6;
    }

    if(*equipment_cursor > 6)
    {
        *equipment_cursor = 0;
    }
}
