#include "render.h"
#include "map.h"

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
