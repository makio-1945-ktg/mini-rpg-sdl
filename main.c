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

EnemyData enemy_table[] = {

    {"スライム", 10, 2, 1, 5, 3},
    {"ゴブリン", 15, 3, 2, 10, 8},
    {"オーク", 20, 5, 3, 20, 15}
};

int main(void)
{
    srand(time(NULL));

    Player player = {
//プレイヤー初期位置
        2,
        2,
//プレイヤーHP
        30,
        30,
//プレイヤーMP
        10,
        10,
//プレイヤー攻撃力・防御力
        6,
        2,
//プレイヤーLV & EXP & GOLD
        1,

        0,

        10,
//プレイヤーアイテム
        2,
//プレイヤー装備
        0

    };

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

    if(!slime_texture) {
        printf("%s\n", IMG_GetError());
    }

    SDL_Texture *current_enemy_texture = NULL;

//戦闘・MAP関数呼び出し
    bool running = true;
    bool menu_open = false;
    bool battle_mode = false;
    bool magic_menu = false;
    bool in_town =false;
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
//プレイヤー操作
            if(event.type == SDL_KEYDOWN && !battle_mode)
            {
                int new_x = player.x;
                int new_y = player.y;

                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menu_open = !menu_open;
                }

                if(menu_open)
                {
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

                char tile = get_tile(new_x, new_y);

                if(get_tile(new_x, new_y) != 'M')
                {
                    player.x = new_x;
                    player.y = new_y;
                }

                if(get_tile(new_x, new_y) != 'W')
                {
                    player.x = new_x;
                    player.y = new_y;
                }

                if(in_town)
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

                if(tile == 'T')
                {
                    town_event();

                    in_town = true;

                    player.x = 3;
                    player.y = 6;
                }

                if(in_town && tile == 'O')
                {
                    printf("町を出た！\n");

                    in_town = false;

                    player.x = 6;
                    player.y = 1;
                }

                if(tile == 'N')
                {
                    npc_event();
                }

                if(tile == 'I')
                {
                    inn_event(
                        &player
                    );
                }

                if(tile == 'Q')
                {
                    equipment_shop_event(
                        &player
                    );
                }

                if(tile == 'C')
                {
                    chest_event(
                        &player,
                        new_x,
                        new_y
                    );
                }

                else
                {
                    printf(" \n");
                }
//敵情報セット段階
                if(tile == 'E')
                {
                    battle_mode =true;

                    int enemy_type = rand() % 3;

                    if(enemy_type == 0)
                    {
                        current_enemy_texture = slime_texture;
                    }

                    else if(enemy_type == 1)
                    {
                        current_enemy_texture = goblin_texture;
                    }

                    else
                    {
                        current_enemy_texture = orc_texture;
                    }

                    strcpy(
                        enemy.name,
                        enemy_table[enemy_type].name
                    );

                    enemy.hp =
                        enemy_table[enemy_type].hp;

                    enemy.max_hp =
                        enemy_table[enemy_type].hp;

                    enemy.attack =
                        enemy_table[enemy_type].attack;

                    enemy.defense =
                        enemy_table[enemy_type].defense;

                    enemy.exp =
                        enemy_table[enemy_type].exp;

                    enemy.gold =
                        enemy_table[enemy_type].gold;

                    enemy.frozen = false;
                    enemy.frozen_timer = 0;

                        printf("プレイヤーHP:%d\n",
                                player.hp);
                        printf("プレイヤーMP:%d\n",
                                player.mp);
                        printf("プレイヤーLv:%d\n",
                                player.level);
                        printf("プレイヤーATK:%d\n",
                                player.attack);
                        printf("プレイヤーDEF:%d\n",
                                player.defense);

                        enemy_event(new_x, new_y);

                        add_battle_log("敵が現れた！");
                }
            }
//戦闘中コマンド処理
            if(event.type == SDL_KEYDOWN && battle_mode)
            {
                if(!magic_menu)
                {
                    if(event.key.keysym.sym == SDLK_1)
                    {
                        enemy_sprite.shake_timer = 12;

                        if(battle_attack(
                                &player,
                                &enemy,
                                &popup,
                                &hit_effect,
                            &slash_effect
                         ))
                        {
                            battle_mode = false;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_2)
                    {
                        if(battle_defend(&player, &enemy))
                        {
                            battle_mode = false;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_3)
                    {
                        magic_menu = !magic_menu;
                    }

                    if(event.key.keysym.sym == SDLK_4)
                    {
                        if(battle_item(&player, &enemy))
                        {
                            battle_mode = false;
                        }
                    }
                }
//魔法選択処理
                else
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        magic_menu = false;
                    }

                    if(event.key.keysym.sym == SDLK_1)
                    {
                        if(battle_heal(&player, &enemy))
                        {
                            battle_mode = false;
                        }
                        magic_menu = false;
                    }

                    if(event.key.keysym.sym == SDLK_2)
                    {
                        if(battle_fire(
                                &player,
                                &enemy,
                                &fire_effect
                        ))
                        {
                            battle_mode = false;
                        }
                        magic_menu = false;
                    }

                    if(event.key.keysym.sym == SDLK_3)
                    {
                        if(battle_ice(
                                &player,
                                &enemy,
                                &ice_effect
                        ))
                        {
                            battle_mode = false;
                        }
                        magic_menu = false;
                    }

                     if(event.key.keysym.sym == SDLK_4)
                    {
                        if(battle_thunder(
                                &player,
                                &enemy,
                                &thunder_effect
                        ))
                        {
                            battle_mode = false;
                        }
                        magic_menu = false;
                    }
                }
            }
        }
//プレイヤー表示
        SDL_SetRenderDrawColor(
            renderer,
            0, 0, 0, 255
        );

        SDL_RenderClear(renderer);

        if(in_town)
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
                180,
                80,
                280,
                200
            };

            SDL_SetRenderDrawColor(
                renderer,
                50,50,50,255
            );

            SDL_RenderFillRect(
                renderer,
                &menu
            );
        }
//戦闘特殊エフェクト描画
        if(popup.active)
        {
            popup.y--;
            popup.timer--;

            if(popup.timer <= 0)
            {
                popup.active = false;
            }
        }

        if(hit_effect.active)
        {
            hit_effect.timer--;

            if(hit_effect.timer <= 0)
            {
                hit_effect.active = false;
            }
        }

        if(slash_effect.active)
        {
            slash_effect.timer--;

            if(slash_effect.timer <= 0)
            {
                slash_effect.active = false;
            }
        }

        int enemy_draw_x = enemy_sprite.x;

        if(enemy_sprite.shake_timer > 0)
        {
            if(enemy_sprite.shake_timer % 2 == 0)
                enemy_draw_x += 5;
            else
                enemy_draw_x -= 5;

            enemy_sprite.shake_timer--;
        }

        if(fire_effect.active)
        {
            fire_effect.timer--;

            if(fire_effect.timer <= 0)
            {
                fire_effect.active = false;
            }
        }

        if(ice_effect.active)
        {
            ice_effect.timer--;

            if(ice_effect.timer <= 0)
            {
                ice_effect.active = false;
            }
        }

        if(thunder_effect.active)
        {
            thunder_effect.timer--;

            if(thunder_effect.timer <= 0)
            {
                thunder_effect.active = false;
            }
        }

//戦闘描画
        if(battle_mode)
        {
            SDL_Rect battle = {
                80,
                40,
                552,
                452
            };
//エネミー描画
            char enemy_info[64];

            sprintf(
                enemy_info,
                "%s HP:%d/%d",
                enemy.name,
                enemy.hp,
                enemy.max_hp
            );

            SDL_SetRenderDrawColor(
                renderer,
                120,0,0,255
            );

            SDL_RenderFillRect(
                renderer,
                &battle
            );

            draw_text(
                renderer,
                font,
                "Battle!",
                100,
                50
            );

            draw_text(
                renderer,
                font,
                enemy_info,
                100,
                80
            );

            draw_hp_bar(
                renderer,
                430,
                90,
                enemy.hp,
                enemy.max_hp
            );

            SDL_Rect enemy_rect = {
                enemy_draw_x,
                enemy_sprite.y,
                96,
                96
            };

            SDL_RenderCopy(
                renderer,
                current_enemy_texture,
                NULL,
                &enemy_rect
            );
//呪文エフェクト描画
            if(fire_effect.active)
            {
                SDL_SetRenderDrawBlendMode(
                    renderer,
                    SDL_BLENDMODE_BLEND
                );

                for(int i = 0; i < 6; i++)
                {
                    SDL_Rect flame = {
                        440 + rand() % 40,
                        120 + rand() % 60,
                        20,
                        20
                    };

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,
                        120 + rand() % 100,
                        0,
                        160
                    );

                    SDL_RenderFillRect(
                        renderer,
                        &flame
                    );
                }
            }

            if(ice_effect.active)
            {
                SDL_SetRenderDrawBlendMode(
                    renderer,
                    SDL_BLENDMODE_BLEND
                );

                SDL_SetRenderDrawColor(
                    renderer,
                    100, 220, 255, 180
                );

                for(int i = 0; i < 4; i++)
                {
                    int x = 440 + i * 18;
                    int y = 120 + rand() % 40;

                    SDL_RenderDrawLine(
                        renderer,
                        x, y,
                        x + 8, y + 20
                    );

                    SDL_RenderDrawLine(
                        renderer,
                        x + 8, y + 20,
                        x + 16, y
                    );
                }
            }

            if(thunder_effect.active)
            {
                SDL_SetRenderDrawBlendMode(
                    renderer,
                    SDL_BLENDMODE_BLEND
                );

                SDL_SetRenderDrawColor(
                    renderer,
                    255, 255, 200, 255
                );

                int start_x = 470;
                int start_y = 80;

                int x = start_x;
                int y = start_y;

                for(int i = 0; i < 6; i++)
                {
                    int next_x = x + (rand() % 21 - 10);
                    int next_y = y + 20;

                    SDL_RenderDrawLine(
                        renderer,
                        x, y,
                        next_x, next_y
                    );

                    SDL_RenderDrawLine(
                        renderer,
                        x + 1, y,
                        next_x + 1, next_y
                    );

                    x = next_x;
                    y = next_y;
                }

                SDL_SetRenderDrawColor(
                    renderer,
                    255,255,255,120
                );

                SDL_Rect flash = {
                    enemy_draw_x,
                    enemy_sprite.y,
                    96,
                    96
                };

                SDL_RenderFillRect(
                    renderer,
                    &flash
                );
            }

            if(hit_effect.active)
            {
                SDL_Rect flash = {
                    enemy_draw_x,
                    enemy_sprite.y,
                    96,
                    96
                };

                SDL_SetRenderDrawBlendMode(
                    renderer,
                    SDL_BLENDMODE_BLEND
                );

                SDL_SetRenderDrawColor(
                    renderer,
                    255,255,255,160
                );

                SDL_RenderFillRect(
                    renderer,
                    &flash
                );
            }

            if(slash_effect.active)
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    150,150,150,255
                );

                for(int i = 0; i < 5; i++)
                {
                    SDL_RenderDrawLine(
                        renderer,
                        450 + i * 8,
                        140,
                        490 + i * 8,
                        180
                    );
                }
            }
//プレイヤー描画
            draw_text(renderer, font, "1: Attack", 100, 120);
            draw_text(renderer, font, "2: Defend", 100, 150);
            draw_text(renderer, font, "3: Magic", 100, 180);
            draw_text(renderer, font, "4: Item", 100, 210);
            char player_info[64];

            sprintf(
                player_info,
                "HP:%d/%d MP:%d/%d",
                player.hp,
                player.max_hp,
                player.mp,
                player.max_mp
            );

            draw_text(
                renderer,
                font,
                player_info,
                100,
                330
            );

            draw_hp_bar(
                renderer,
                430,
                340,
                player.hp,
                player.max_hp
            );

            for(int i = 0; i < LOG_LINES; i++)
            {
                draw_text(
                    renderer,
                    font,
                    battle_logs[i],
                    120,
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
//魔法メニュー表示
            if(magic_menu)
            {
                SDL_Rect magic_box = {
                    220, 120, 180, 190
                };

                SDL_SetRenderDrawColor(
                    renderer,
                    40, 40, 80, 220
                );

                SDL_RenderFillRect(
                    renderer,
                    &magic_box
                );

                draw_text(renderer, font, "Magic", 250, 120);
                draw_text(renderer, font, "1: Heal", 250, 150);
                draw_text(renderer, font, "2: Fire", 250, 180);
                draw_text(renderer, font, "3: Ice", 250, 210);
                draw_text(renderer, font, "4: Thunder", 250, 240);
            }
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

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();

    return 0;
}
