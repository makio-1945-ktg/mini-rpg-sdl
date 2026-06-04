#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

void draw_map(SDL_Renderer *renderer);

void draw_player(
    SDL_Renderer *renderer,
    int x,
    int y
);

#endif
