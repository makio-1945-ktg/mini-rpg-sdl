#include "render.h"
#include "map.h"

#include <SDL2/SDL_ttf.h>

#define TILE_SIZE 32

void draw_player(
    SDL_Renderer *renderer,
    int x,
    int y
)
{
    SDL_Rect rect = {
        x * TILE_SIZE,
        y * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE
    };

    SDL_SetRenderDrawColor(
        renderer,
        0,0,255,255
    );

    SDL_RenderFillRect(
        renderer,
        &rect
    );
}

void draw_map(SDL_Renderer *renderer)
{
    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            SDL_Rect rect = {
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

//画面描画
            switch(field_map[y][x])
            {
                case 'M':
                    SDL_SetRenderDrawColor(
                        renderer,
                        100,100,100,255
                    );
                    break;

                case 'W':
                    SDL_SetRenderDrawColor(
                        renderer,
                        0,100,255,255
                    );
                    break;

                case 'G':
                    SDL_SetRenderDrawColor(
                        renderer,
                        0,255,0,255
                    );
                    break;

                case 'T':

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,255,0,255
                    );
                    break;

                case 'N':

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,0,255,0
                    );
                    break;

                case 'C':

                    SDL_SetRenderDrawColor(
                        renderer,
                        50,200,200,255
                    );
                    break;

                case 'E':

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,0,0,255
                    );
                    break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
//文字メニュー

void draw_text(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *text,
    int x,
    int y
)
{
    SDL_Color color = {255,255,255,255};

    SDL_Surface *surface =
        TTF_RenderUTF8_Blended(
            font,
            text,
            color
        );

    if(surface == NULL)
    {
        return;
    }

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(
            renderer,
            surface
        );

    if(texture == NULL)
    {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst = {
        x,
        y,
        surface->w,
        surface->h
    };

    SDL_FreeSurface(surface);

    SDL_RenderCopy(
        renderer,
        texture,
        NULL,
        &dst
    );

    SDL_DestroyTexture(texture);
}

void draw_town_map(
    SDL_Renderer *renderer
)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            SDL_Rect rect = {
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

            switch(town_map[y][x])
            {
                case 'M':
                    SDL_SetRenderDrawColor(
                        renderer,
                        100,100,100,255
                    );
                    break;

                case 'G':
                    SDL_SetRenderDrawColor(
                        renderer,
                        0,255,0,255
                    );
                    break;

                case 'N':

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,0,255,255
                    );
                    break;

                case 'I':

                    SDL_SetRenderDrawColor(
                        renderer,
                        0,255,255,255
                    );
                    break;

                case 'Q':

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,128,0,255
                    );
                    break;

                case 'O':

                    SDL_SetRenderDrawColor(
                        renderer,
                        255,255,255,255
                    );
                    break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void draw_hp_bar(
    SDL_Renderer *renderer,
    int x,
    int y,
    int current_hp,
    int max_hp
)
{
    SDL_Rect border = {
        x,
        y,
        104,
        24
    };

    SDL_SetRenderDrawColor(
        renderer,
        255,255,255,255
    );
    SDL_RenderDrawRect(
        renderer,
        &border
    );

    int bar_width =
        (100 * current_hp) / max_hp;

    SDL_Rect hp_bar = {
        x + 2,
        y + 2,
        bar_width,
        20
    };

    int percent =
        (100 * current_hp) / max_hp;

    if(percent > 60)
        SDL_SetRenderDrawColor(
            renderer,
            0,255,0,255
        );
    else if(percent > 20)
        SDL_SetRenderDrawColor(
            renderer,
            160,255,0,255
        );
    else
        SDL_SetRenderDrawColor(
            renderer,
            255,0,0,255
        );

    SDL_RenderFillRect(
        renderer,
        &hp_bar
    );
}

void draw_battle_background(
    SDL_Renderer *renderer
)
{
    SDL_Rect battle = {
        80,
        40,
        552,
        452
    };

    SDL_SetRenderDrawColor(
        renderer,
        50, 50, 50, 255
    );

    SDL_RenderFillRect(
        renderer,
        &battle
    );
}

void draw_magic_menu(
    SDL_Renderer *renderer,
    TTF_Font *font,
    int magic_cursor
)
{
    SDL_Rect magic_box = {
        80, 130, 130, 160
    };

    SDL_SetRenderDrawColor(
        renderer,
        0, 50, 150, 150
    );

    SDL_RenderFillRect(
        renderer,
        &magic_box
    );

    SDL_SetRenderDrawColor(
        renderer,
        255,255,255,255
    );

    SDL_RenderDrawRect(
        renderer,
        &magic_box
    );

    SDL_Rect magic_cursor_box = {
        80,
        135 + magic_cursor * 30,
        120,
        28
    };

    SDL_RenderDrawRect(
        renderer,
        &magic_cursor_box
    );

    draw_text(renderer, font, "Heal", 90, 130);
    draw_text(renderer, font, "Fire", 90, 160);
    draw_text(renderer, font, "Ice", 90, 190);
    draw_text(renderer, font, "Thunder", 90, 220);
}

void draw_battle_ui(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    Enemy *enemy,
    EnemySprite *enemy_sprite,
    SDL_Texture *enemy_texture,
    int battle_cursor
)
{
    SDL_Rect command_box = {
        80,
        130,
        130,
        160
    };

    SDL_SetRenderDrawColor(
        renderer,
        0, 50, 250, 250
    );

    SDL_RenderFillRect(
        renderer,
        &command_box
    );

    SDL_SetRenderDrawColor(
        renderer,
        255,255,255,255
    );

    SDL_RenderDrawRect(
        renderer,
        &command_box
    );

    SDL_Rect cursor_box = {
        80,
        135 + battle_cursor * 30,
        120,
        28
    };

    SDL_RenderDrawRect(
        renderer,
        &cursor_box
    );

    SDL_Rect status_box = {
        80,
        300,
        130,
        70
    };

    SDL_SetRenderDrawColor(
        renderer,
        40,100,100,255
    );

    SDL_RenderFillRect(
        renderer,
        &status_box
    );

    SDL_SetRenderDrawColor(
        renderer,
        255,255,255,255
    );

    SDL_RenderDrawRect(
        renderer,
        &status_box
    );

    SDL_Rect log_box = {
        165,
        390,
        400,
        100
    };

    SDL_SetRenderDrawColor(
        renderer,
        40,40,80,220
    );

    SDL_RenderFillRect(
        renderer,
        &log_box
    );

    SDL_SetRenderDrawColor(
        renderer,
        255,255,255,255
    );

    SDL_RenderDrawRect(
        renderer,
        &log_box
    );

    char enemy_info[64];

        sprintf(
            enemy_info,
            "%s HP:%d/%d",
            enemy->name,
            enemy->hp,
            enemy->max_hp
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
            enemy->hp,
            enemy->max_hp
        );
//敵スプライト
        SDL_Rect enemy_rect = {
            enemy_sprite->x,
            enemy_sprite->y,
            96,
            96
        };

        SDL_RenderCopy(
            renderer,
            enemy_texture,
            NULL,
            &enemy_rect
        );

        char player_hp_info[64];
        char player_mp_info[64];

        sprintf(
            player_hp_info,
            "HP:%d/%d",
            player->hp,
            player->max_hp
        );

        sprintf(
            player_mp_info,
            "MP:%d/%d",
            player->mp,
            player->max_mp
        );

        draw_text(renderer, font, player_hp_info, 90, 300);

        draw_text(renderer, font, player_mp_info, 90, 325);
           
        draw_hp_bar(
            renderer,
            430,
            310,
            player->hp,
            player->max_hp
        );

            draw_text(renderer, font, "Attack", 90, 130);
            draw_text(renderer, font, "Defend", 90, 160);
            draw_text(renderer, font, "Magic", 90, 190);
            draw_text(renderer, font, "Item", 90, 220);
}

void update_battle_effects(
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    FireEffect *fire_effect,
    IceEffect *ice_effect,
    ThunderEffect *thunder_effect,
    EnemySprite *enemy_sprite
)
{

    if(popup->active)
    {
        popup->y--;
        popup->timer--;

        if(popup->timer <= 0)
        {
            popup->active = false;
        }
    }

    if(hit_effect->active)
    {
        hit_effect->timer--;

        if(hit_effect->timer <= 0)
        {
            hit_effect->active = false;
        }
    }

    if(slash_effect->active)
    {
        slash_effect->timer--;

        if(slash_effect->timer <= 0)
        {
            slash_effect->active = false;
        }
    }

    if(enemy_sprite->shake_timer > 0)
    {
        enemy_sprite->shake_timer--;
    }

    if(fire_effect->active)
    {
        fire_effect->timer--;

        if(fire_effect->timer <= 0)
        {
            fire_effect->active = false;
        }
    }

    if(ice_effect->active)
    {
        ice_effect->timer--;

        if(ice_effect->timer <= 0)
        {
            ice_effect->active = false;
        }
    }

    if(thunder_effect->active)
    {
        thunder_effect->timer--;

        if(thunder_effect->timer <= 0)
        {
            thunder_effect->active = false;
        }
    }
}
