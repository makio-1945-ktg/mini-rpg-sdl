#include <stdbool.h>

#include <SDL2/SDL.h>

#include "render.h"
#include "player.h"
#include "map.h"

int main(void)
{
    Player player = {
        2,
        2
    };

    SDL_Init(SDL_INIT_VIDEO);

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
            if(event.type == SDL_KEYDOWN && !menu_open)
            {

                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menu_open = !menu_open;
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
                if(get_tile(new_x, new_y) != 'M')
                {
                    player.x = new_x;
                    player.y = new_y;
                }

                char tile = get_tile(new_x, new_y);

                if(tile != 'M')
                {
                    player.x = new_x;
                    player.y = new_y;
                }

                if(tile == 'T')
                {
                    town_event();
                }
                else
                {
                    printf(" \n");
                }

                if(tile == 'N')
                {
                    npc_event();
                }

                if(tile == 'C')
                {
                    chest_event(new_x, new_y);
                }
            }
        }
//プレイヤー表示
        SDL_SetRenderDrawColor(
            renderer,
            0, 0, 0, 255
        );

        SDL_RenderClear(renderer);

        draw_map(renderer);

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

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
