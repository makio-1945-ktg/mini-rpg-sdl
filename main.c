#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "render.h"
#include "map.h"
#include "battle.h"
#include "player.h"

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
        60,
        60,
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

    Enemy enemy = {"",0,0,0,0,0};

    SDL_Init(SDL_INIT_VIDEO);

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL error: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Init();

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
            640,
            480,
            0
        );

    SDL_Renderer *renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
            );
    bool running = true;
    bool menu_open = false;
    bool battle_mode = false;
    bool in_town =false;

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

                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menu_open = !menu_open;
                }

                if(menu_open)
                {
                    continue;
                }

                int new_x = player.x;
                int new_y = player.y;

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

                //壁判定
                char tile;

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

                if(tile != 'M')
                {
                    player.x = new_x;
                    player.y = new_y;
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

                if(tile == 'E')
                {
                    battle_mode =true;

                    int enemy_type = rand() % 3;

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

                        printf("%sが現れた！\n", enemy.name);
                        printf("敵HP:%d\n", enemy.hp);
                }
            }

            if(event.type == SDL_KEYDOWN && battle_mode)
            {
//攻撃コマンド
                if(event.key.keysym.sym == SDLK_1)
                {
                    if(battle_attack(&player, &enemy))
                    {
                        battle_mode = false;
                    }
                }
//防御コマンド
                if(event.key.keysym.sym == SDLK_2)
                {
                    if(battle_defend(&player, &enemy))
                    {
                        battle_mode = false;
                    }
                }
//魔法コマンド
                if(event.key.keysym.sym == SDLK_3)
                {
                    if(battle_heal(&player, &enemy))
                    {
                        battle_mode = false;
                    }
                }
//アイテムコマンド
                if(event.key.keysym.sym == SDLK_4)
                {
                    if(battle_item(&player, &enemy))
                    {
                        battle_mode = false;
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
//戦闘描画
        if(battle_mode)
        {
            SDL_Rect battle = {
                80,
                50,
                480,
                320
            };

            char enemy_info[64];

            sprintf(
                enemy_info,
                "%s HP:%d",
                enemy.name,
                enemy.hp
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
                70
            );

            draw_text(
                renderer,
                font,
                enemy_info,
                100,
                110
            );

            draw_text(renderer, font, "1: Attack", 100, 160);
            draw_text(renderer, font, "2: Defend", 100, 200);
            draw_text(renderer, font, "3: Heal", 100, 240);
            draw_text(renderer, font, "4: Item", 100, 280);

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
                320,
                320
            );
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);

    }

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
