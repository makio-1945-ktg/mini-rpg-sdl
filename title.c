#include "title.h"
#include "render.h"

void handle_title_input(
    SDL_Event *event,
    GameScreen *screen
)
{
    if(event->key.keysym.sym == SDLK_RETURN)
    {
        *screen = SCREEN_PLAYING;
    }
}

void draw_title(
    SDL_Renderer *renderer,
    TTF_Font *font
)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 40, 255);
    SDL_RenderClear(renderer);

    draw_text(renderer, font, "Mini RPG", 280, 200);
    draw_text(renderer, font, "Enterで　はじめから", 220, 300);
}

void handle_game_over_input(
    SDL_Event *event,
    GameScreen *screen
)
{
    if(event->key.keysym.sym == SDLK_RETURN)
    {
        *screen = SCREEN_TITLE;
    }
}

void draw_game_over(
    SDL_Renderer *renderer,
    TTF_Font *font
)
{
    SDL_SetRenderDrawColor(renderer, 40, 10, 10, 255);
    SDL_RenderClear(renderer);

    draw_text(renderer, font, "GAME OVER", 260, 200);
    draw_text(renderer, font, "Enterで　タイトルへ", 220, 300);
}
