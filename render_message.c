#include "render.h"

void draw_message(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *message
)
{
    SDL_Rect window = {40, 480, 560, 60};

    SDL_SetRenderDrawColor(renderer, 20, 120, 20, 255);

    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, message, 60, 480);
}
