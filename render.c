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
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
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

