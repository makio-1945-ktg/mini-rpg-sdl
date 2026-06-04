#include <SDL2/SDL.h>
#include <stdio.h>

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window =
        SDL_CreateWindow(
            "Move Test",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            480,
            SDL_WINDOW_SHOWN
        );

    SDL_Renderer *renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_SOFTWARE
        );

    SDL_Rect player = {
        64,
        64,
        32,
        32
    };

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                        player.y -= 32;
                        break;

                    case SDLK_s:
                        player.y += 32;
                        break;

                    case SDLK_a:
                        player.x -= 32;
                        break;

                    case SDLK_d:
                        player.x += 32;
                        break;
                }
            }
        }

        /* 背景　赤 */
        SDL_SetRenderDrawColor(
            renderer,
            255,
            0,
            0,
            255
        );
        SDL_RenderClear(renderer);

        /* プレイヤー白色 */
        SDL_SetRenderDrawColor(
            renderer,
            255,
            255,
            255,
            255
        );
        SDL_RenderFillRect(
            renderer,
            &player
        );

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
