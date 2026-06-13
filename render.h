#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_map(
    SDL_Renderer *renderer
);

void draw_text(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *text,
    int x,
    int y
);

void draw_town_map(
    SDL_Renderer *renderer
);

void draw_player(
    SDL_Renderer *renderer,
    int x,
    int y
);

#endif
