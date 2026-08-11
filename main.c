#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "battle.h"
#include "player.h"
#include "render.h"
#include "cave.h"
#include "cave_b1.h"
#include "cave_b2.h"
#include "temple.h"
#include "message_ui.h"
#include "save.h"
#include "shop.h"

int main(void)
{
    srand(time(NULL));

    Player player = create_player();

    Enemy enemy = {"",0,0,0,0,0,0};

    DamagePopup popup = {"", 0, 0, 0, false};

    HitEffect hit_effect = {0, false};
    SlashEffect slash_effect = {0, false};
    FireEffect fire_effect = {0, false};
    IceEffect ice_effect = {0, false};
    ThunderEffect thunder_effect = {0, false};

    EnemySprite enemy_sprite = {
        430,
        120,
        0
    };

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("IMG error: %s\n", IMG_GetError());
        return 1;
    }

    if(TTF_Init() != 0)
    {
        printf("TTF error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window *window =
        SDL_CreateWindow(
            "Mini RPG",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            720,
            560,
            0
        );

    SDL_Renderer *renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
            );

    SDL_Texture *slime_texture =
        IMG_LoadTexture(
            renderer,
            "assets/slime.png"
        );

    SDL_Texture *goblin_texture =
        IMG_LoadTexture(
            renderer,
            "assets/goblin.png"
        );

    SDL_Texture *orc_texture =
        IMG_LoadTexture(
            renderer,
            "assets/orc.png"
        );

    SDL_Texture *bat_texture =
        IMG_LoadTexture(
            renderer,
            "assets/bat.png"
        );

    SDL_Texture *skeleton_texture =
        IMG_LoadTexture(
            renderer,
            "assets/skeleton.png"
        );

    SDL_Texture *golem_texture =
        IMG_LoadTexture(
            renderer,
            "assets/golem.png"
        );

    SDL_Texture *scorpion_texture =
        IMG_LoadTexture(
            renderer,
            "assets/scorpion.png"
        );

    SDL_Texture *luckyfairy_texture =
        IMG_LoadTexture(
            renderer,
            "assets/luckyfairy.png"
        );

    SDL_Texture *wizard_texture =
        IMG_LoadTexture(
            renderer,
            "assets/wizard.png"
        );

    SDL_Texture *kobold_texture =
        IMG_LoadTexture(
            renderer,
            "assets/kobold.png"
        );

    SDL_Texture *wisp_texture =
        IMG_LoadTexture(
            renderer,
            "assets/wisp.png"
        );

    SDL_Texture *lamia_texture =
        IMG_LoadTexture(
            renderer,
            "assets/lamia.png"
        );

    SDL_Texture *dragon_texture =
        IMG_LoadTexture(
            renderer,
            "assets/dragon.png"
        );

    if(!slime_texture) {
        printf("%s\n", IMG_GetError());
    }

    SDL_Texture *current_enemy_texture = NULL;

//戦闘・MAP関数呼び出し
    bool running = true;
    bool menu_open = false;
    BattleMode battle_mode = MODE_FIELD;

    int menu_cursor = 0;
    int item_cursor = 0;
    int equipment_cursor = 0;
    int save_cursor = 0;
    int battle_cursor = 0;
    int magic_cursor = 0;
    int use_item_cursor = 0;
    int shop_cursor = 0;

    bool in_town = false;
    bool in_cave = false;
    bool in_cave_b1 = false;
    bool in_cave_b2 = false;
    bool in_temple = false;
//フォント
    TTF_Font *font =
        TTF_OpenFont(
            "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
            24
        );

    if(font == NULL)
    {
        printf("font load error: %s\n",
               TTF_GetError());
        return 1;
    }

    while(running)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
//フィールドイベント処理
            if(event.type == SDL_KEYDOWN)
            {
                if(battle_mode == MODE_FIELD)
                {
                    int new_x = player.x;
                    int new_y = player.y;

                    if(menu_open &&
                        event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(menu_cursor)
                        {
                            case 0:
                                battle_mode = MODE_STATUS;
                                menu_open = false;
                                break;

                            case 1:
                                battle_mode = MODE_ITEM;
                                menu_open = false;
                                item_cursor = 0;
                                break;

                            case 2:
                                battle_mode = MODE_EQUIPMENT;
                                menu_open = false;
                                break;

                            case 3:
                                battle_mode = MODE_SAVE;
                                menu_open = false;
                                break;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        menu_open = !menu_open;

                        if(menu_open)
                        {
                            menu_cursor = 0;
                        }
                    }

                    if(menu_open)
                    {
                        if(event.key.keysym.sym == SDLK_UP)
                        {
                            menu_cursor--;
                        }

                        if(event.key.keysym.sym == SDLK_DOWN)
                        {
                            menu_cursor++;
                        }

                        if(menu_cursor < 0)
                        {
                            menu_cursor = 3;
                        }

                        if(menu_cursor > 3)
                        {
                            menu_cursor = 0;
                        }
                            continue;
                    }

                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            new_y--;
                            break;

                        case SDLK_DOWN:
                            new_y++;
                            break;

                        case SDLK_LEFT:
                            new_x--;
                            break;

                        case SDLK_RIGHT:
                            new_x++;
                            break;
                    }

                    char tile;

                    if(in_temple)
                    {
                        tile = get_temple_tile(
                            new_x,
                            new_y
                        );
                    }
                    else if(in_cave_b2)
                    {
                        tile = get_cave_b2_tile(
                            new_x,
                            new_y
                        );
                    }
                    else if(in_cave_b1)
                    {
                        tile = get_cave_b1_tile(
                            new_x,
                            new_y
                        );
                    }
                    else if(in_cave)
                    {
                        tile = get_cave_tile(
                            new_x,
                            new_y
                        );
                    }
                    else if(in_town)
                    {
                        tile = get_town_tile(
                            new_x,
                            new_y
                        );
                    }
                    else
                    {
                        tile = get_tile(
                            new_x,
                            new_y
                        );
                    }

                    if(tile != 'M' && tile != 'W')
                    {
                        player.x = new_x;
                        player.y = new_y;
                    }

                    if(in_temple)
                    {
                        handle_temple_event(
                            tile,
                            &in_temple,
                            &player,
                            new_x,
                            new_y,
                            &battle_mode,
                            &battle_cursor,
                            &magic_cursor,
                            &use_item_cursor,
                            &enemy,
                            &current_enemy_texture,
                            dragon_texture
                        );
                    }
 
                    else if(in_cave_b2)
                    {
                        handle_cave_b2_event(
                            tile,
                            &in_cave_b1,
                            &in_cave_b2,
                            &player,
                            new_x,
                            new_y,
                            &battle_mode,
                            &battle_cursor,
                            &magic_cursor,
                            &use_item_cursor,
                            &enemy,
                            &current_enemy_texture,
                            kobold_texture,
                            wisp_texture,
                            lamia_texture
                        );
                    }
                    else if(in_cave_b1)
                    {
                        handle_cave_b1_event(
                            tile,
                            &in_cave,
                            &in_cave_b1,
                            &in_cave_b2,
                            &player,
                            new_x,
                            new_y,
                            &battle_mode,
                            &battle_cursor,
                            &magic_cursor,
                            &use_item_cursor,
                            &enemy,
                            &current_enemy_texture,
                            scorpion_texture,
                            luckyfairy_texture,
                            wizard_texture
                        );
                    }
                    else if(in_cave)
                    {
                        handle_cave_event(
                            tile,
                            &in_cave,
                            &in_cave_b1,
                            &player,
                            new_x,
                            new_y,
                            &battle_mode,
                            &battle_cursor,
                            &magic_cursor,
                            &use_item_cursor,
                            &enemy,
                            &current_enemy_texture,
                            bat_texture,
                            skeleton_texture,
                            golem_texture
                        );
                    }
                    else
                    {
                        handle_field_event(
                            tile,
                            &in_town,
                            &in_cave,
                            &in_temple,
                            &player,
                            new_x,
                            new_y,
                            &battle_mode,
                            &battle_cursor,
                            &magic_cursor,
                            &use_item_cursor,
                            &shop_cursor,
                            &enemy,
                            &current_enemy_texture,
                            slime_texture,
                            goblin_texture,
                            orc_texture
                        );
                    }
                }
//ステータス処理
                else if(battle_mode == MODE_STATUS)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        battle_mode = MODE_FIELD;
                    }
                }
//アイテム処理
                else if(battle_mode == MODE_ITEM)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        battle_mode = MODE_FIELD;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(item_cursor)
                        {
                        case 0:
                            if(player.inventory.potion > 0)
                            {
                                player.inventory.potion--;

                                player.hp += 20;

                                if(player.hp > player.max_hp)
                                {
                                    player.hp = player.max_hp;
                                }

                                show_message("ポーションを使った！");
                            }
                            else
                            {
                                show_message("ポーションがない！");
                            }
                            break;

                            case 1:
                            if(player.inventory.ether > 0)
                            {
                                player.inventory.ether--;

                                player.mp += 10;

                                if(player.mp > player.max_mp)
                                {
                                    player.mp = player.max_mp;
                                }

                                show_message("エーテルを使った！");
                            }
                            else
                            {
                                show_message("エーテルがない！");
                            }
                            break;

                            case 2:
                                show_message("戦闘中に使おう！");
                            break;

                            case 3:
                                show_message("？？？？？？");
                            break;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        item_cursor--;
                    }

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        item_cursor++;
                    }

                    if(item_cursor < 0)
                    {
                        item_cursor = 4;
                    }

                    if(item_cursor > 4)
                    {
                        item_cursor = 0;
                    }
                }
//装備処理
                else if(battle_mode == MODE_EQUIPMENT)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        battle_mode = MODE_FIELD;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(equipment_cursor)
                        {
                        case 0:
                            equip_sword(&player);
                            break;

                        case 1:
                            equip_leather_armor(&player);
                            break;

                        case 2:
                            equip_wooden_shield(&player);
                            break;

                        case 3:
                            equip_broad_sword(&player);
                            break;

                        case 4:
                            equip_rune_sword(&player);
                            break;

                        case 5:
                            equip_rune_armor(&player);
                            break;

                        case 6:
                            equip_rune_shield(&player);
                            break;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        equipment_cursor--;
                    }

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        equipment_cursor++;
                    }

                    if(equipment_cursor < 0)
                    {
                        equipment_cursor = 6;
                    }

                    if(equipment_cursor > 6)
                    {
                        equipment_cursor = 0;
                    }
                }

//セーブ管理処理
                else if(battle_mode == MODE_SAVE)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        battle_mode = MODE_FIELD;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(save_cursor)
                        {
                        case 0:
                            if(save_game(&player))
                            {
                                show_message("セーブしました！");
                            }
                            else
                            {
                                show_message("セーブに失敗しました");
                            }
                            break;

                        case 1:
                            if(load_game(&player))
                            {
                                show_message("ロードしました！");
                            }
                            else
                            {
                                show_message("ロードに失敗しました");
                            }
                            break;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        save_cursor--;
                    }

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        save_cursor++;
                    }

                    if(save_cursor < 0)
                    {
                        save_cursor = 1;
                    }

                    if(save_cursor > 1)
                    {
                        save_cursor = 0;
                    }
                }
//通常戦闘処理
                else if(battle_mode == MODE_BATTLE)
                {
                    handle_normal_battle_input(
                        &event,
                        &battle_mode,
                        &battle_cursor,
                        &player,
                        &enemy,
                        &popup,
                        &hit_effect,
                        &slash_effect,
                        &enemy_sprite
                    );
                }
//魔法メニュー処理
                else if(battle_mode == MODE_MAGIC)
                {
                    handle_magic_input(
                        &event,
                        &battle_mode,
                        &magic_cursor,
                        &player,
                        &enemy,
                        &fire_effect,
                        &ice_effect,
                        &thunder_effect
                    );
                }
//アイテム使用処理
                else if(battle_mode == MODE_USE_ITEM)
                {
                    handle_item_input(
                        &event,
                        &battle_mode,
                        &use_item_cursor,
                        &player,
                        &enemy
                    );
                }
//ショップイベント処理
                else if(battle_mode == MODE_SHOP)
                {
                    handle_shop_input(
                        &event,
                        &battle_mode,
                        &shop_cursor,
                        &player
                    );
                }
            }
        }
//プレイヤー表示
        SDL_SetRenderDrawColor(
            renderer,
            0, 0, 0, 255
        );

        SDL_RenderClear(renderer);

        update_battle_effects(
            &popup,
            &hit_effect,
            &slash_effect,
            &fire_effect,
            &ice_effect,
            &thunder_effect,
            &enemy_sprite
        );

        if(in_temple)
        {
            draw_temple_map(renderer);
        }
        else if(in_cave_b2)
        {
            draw_cave_b2_map(renderer);
        }
        else if(in_cave_b1)
        {
            draw_cave_b1_map(renderer);
        }
        else if(in_cave)
        {
            draw_cave_map(renderer);
        }
        else if(in_town)
        {
            draw_town_map(renderer);
        }
        else
        {
            draw_map(renderer);
        }

        draw_player(
            renderer,
            player.x,
            player.y
        );

        if(menu_open)
        {
            SDL_Rect menu = {
                80,
                150,
                280,
                200
            };

            SDL_SetRenderDrawColor(
                renderer,
                50,50,50,255
            );

            SDL_RenderFillRect(renderer, &menu);

            if(menu_cursor == 0)
            {
                draw_text(
                    renderer,
                    font,
                    "▶　ステータス",
                    110,
                    180
                );
            }
            else
            {
                draw_text(
                    renderer,
                    font,
                    " 　ステータス",
                    110,
                    180
                );
            }

            if(menu_cursor == 1)
            {
                draw_text(
                    renderer,
                    font,
                    "▶　アイテム",
                    110,
                    210
                );
            }
            else
            {
                draw_text(
                    renderer,
                    font,
                    " 　アイテム",
                    110,
                    210
                );
            }

            if(menu_cursor == 2)
            {
                draw_text(
                    renderer,
                    font,
                    "▶　装備",
                    110,
                    240
                );
            }
            else
            {
                draw_text(
                    renderer,
                    font,
                    " 　装備",
                    110,
                    240
                );
            }
            if(menu_cursor == 3)
            {
                draw_text(
                    renderer,
                    font,
                    "▶　セーブ＆ロード",
                    110,
                    270
                );
            }
            else
            {
                draw_text(
                    renderer,
                    font,
                    " 　セーブ＆ロード",
                    110,
                    270
                );
            }
        }
//フィールドメニュー描画
        if(battle_mode == MODE_STATUS)
        {
            draw_status(
                renderer,
                font,
                &player
            );
        }

        if(battle_mode == MODE_ITEM)
        {
            draw_item(
                renderer,
                font,
                &player,
                item_cursor
            );
        }

        if(battle_mode == MODE_EQUIPMENT)
        {
            draw_equipment(
                renderer,
                font,
                &player,
                equipment_cursor
            );
        }

        if(battle_mode == MODE_SAVE)
        {
            draw_save(
                renderer,
                font,
                &player,
                save_cursor
            );
        }

//戦闘描画
        if(battle_mode == MODE_BATTLE ||
           battle_mode == MODE_MAGIC ||
           battle_mode == MODE_USE_ITEM)
        {
            draw_battle_background(renderer);

            draw_battle_ui(
                renderer,
                font,
                &player,
                &enemy,
                &enemy_sprite,
                current_enemy_texture,
                battle_cursor
            );
//魔法メニュー表示
            if(battle_mode == MODE_MAGIC)
            {
                draw_magic_menu(
                    renderer,
                    font,
                    magic_cursor
                );
            }
//アイテムメニュー表示
            if(battle_mode == MODE_USE_ITEM)
            {
                draw_item_menu(
                    renderer,
                    font,
                    use_item_cursor
                );
            }
//呪文エフェクト描画
            draw_battle_effects(
                renderer,
                &fire_effect,
                &ice_effect,
                &thunder_effect,
                &hit_effect,
                &slash_effect,
                &enemy_sprite
            );
//戦闘ログ描画
            for(int i = 0; i < LOG_LINES; i++)
            {
                draw_text(
                    renderer,
                    font,
                    battle_logs[i],
                    100,
                    380 + i * 25
                );
            }

            if(popup.active)
            {
                draw_text(
                    renderer,
                    font,
                    popup.text,
                    popup.x,
                    popup.y
                );
            }
        }
//武器屋購入画面描画
        if(battle_mode == MODE_SHOP)
        {
            draw_shop(
                renderer,
                font,
                &player,
                shop_cursor
            );
        }

        update_message();

        if(get_message()[0] != '\0')
        {
            draw_message(
                renderer,
                font,
                get_message()
            );
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(slime_texture);
    SDL_DestroyTexture(goblin_texture);
    SDL_DestroyTexture(orc_texture);
    SDL_DestroyTexture(bat_texture);
    SDL_DestroyTexture(skeleton_texture);
    SDL_DestroyTexture(golem_texture);
    SDL_DestroyTexture(scorpion_texture);
    SDL_DestroyTexture(luckyfairy_texture);
    SDL_DestroyTexture(wizard_texture);
    SDL_DestroyTexture(kobold_texture);
    SDL_DestroyTexture(wisp_texture);
    SDL_DestroyTexture(lamia_texture);
    SDL_DestroyTexture(dragon_texture);

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();

    return 0;
}
