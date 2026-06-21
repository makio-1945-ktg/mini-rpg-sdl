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

    {"スライム", 10, 2, 1, 5, 3, -50, 0, 50},
    {"ゴブリン", 15, 3, 2, 10, 8, 0, 0, 0},
    {"オーク", 20, 5, 3, 20, 15, 50, -50, 0}
};

typedef enum {
    MODE_FIELD,
    MODE_BATTLE,
    MODE_MAGIC
} BattleMode;

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
    BattleMode battle_mode = MODE_FIELD;

    int battle_cursor = 0;
    int magic_cursor = 0;

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
            if(event.type == SDL_KEYDOWN &&
                battle_mode == MODE_FIELD)
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

                if(tile != 'M' && tile != 'W')
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
                    battle_mode = MODE_BATTLE;
                    battle_cursor = 0;
                    magic_cursor = 0;

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

                    enemy.fire_resist =
                        enemy_table[enemy_type].fire_resist;

                    enemy.ice_resist =
                        enemy_table[enemy_type].ice_resist;

                    enemy.thunder_resist =
                        enemy_table[enemy_type].thunder_resist;

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
            if(event.type == SDL_KEYDOWN &&
                (battle_mode == MODE_BATTLE ||
                 battle_mode == MODE_MAGIC))
            {
//魔法メニュー処理
                if(battle_mode == MODE_MAGIC)
                {
                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        magic_cursor--;

                        if(magic_cursor < 0)
                            magic_cursor = 3;
                    }

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        magic_cursor++;

                        if(magic_cursor > 3)
                            magic_cursor = 0;
                    }

                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        battle_mode = MODE_BATTLE;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(magic_cursor)
                        {
                            case 0:
                                if(battle_heal(&player, &enemy))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                else
                                {
                                    battle_mode = MODE_BATTLE;
                                }
                                break;

                            case 1:
                                if(battle_fire(
                                    &player,
                                    &enemy,
                                    &fire_effect))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                else
                                {
                                    battle_mode = MODE_BATTLE;
                                }
                                break;

                            case 2:
                                if(battle_ice(
                                    &player,
                                    &enemy,
                                    &ice_effect))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                else
                                {
                                    battle_mode = MODE_BATTLE;
                                }
                                break;

                            case 3:
                                if(battle_thunder(
                                    &player,
                                    &enemy,
                                    &thunder_effect))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                else
                                {
                                    battle_mode = MODE_BATTLE;
                                }
                                break;
                        }
                    }
                }
//通常戦闘処理
                else
                {
                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        battle_cursor--;

                        if(battle_cursor < 0)
                            battle_cursor = 3;
                    }

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        battle_cursor++;

                        if(battle_cursor > 3)
                            battle_cursor = 0;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(battle_cursor)
                        {
                            case 0:
                                enemy_sprite.shake_timer = 12;

                                if(battle_attack(
                                        &player,
                                        &enemy,
                                        &popup,
                                        &hit_effect,
                                        &slash_effect))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                break;

                            case 1:
                                if(battle_defend(&player, &enemy))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                break;

                            case 2:
                                battle_mode = MODE_MAGIC;
                                break;

                            case 3:
                                if(battle_item(&player, &enemy))
                                {
                                    battle_mode = MODE_FIELD;
                                }
                                break;
                        }
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

        update_battle_effects(
            &popup,
            &hit_effect,
            &slash_effect,
            &fire_effect,
            &ice_effect,
            &thunder_effect,
            &enemy_sprite
        );

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
                80,
                150,
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
        if(battle_mode == MODE_BATTLE ||
           battle_mode == MODE_MAGIC)
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
                    200,
                    390 + i * 25
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
