#include "render.h"

#include <SDL2/SDL_ttf.h>

#define TILE_SIZE 32
#define PLAYER_FRAME_SIZE 104

void draw_player(SDL_Renderer *renderer, SDL_Texture *player_texture,
    int x, int y, int direction, int frame)
{
    SDL_Rect src = {frame * PLAYER_FRAME_SIZE, direction * PLAYER_FRAME_SIZE,
        PLAYER_FRAME_SIZE, PLAYER_FRAME_SIZE};

    SDL_Rect dst = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

    SDL_RenderCopy(renderer, player_texture, &src, &dst);
}


void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text,
    int x, int y)
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
}

void draw_menu_item(SDL_Renderer *renderer, TTF_Font *font,
    const char *label,int x, int y, bool selected)
{
   char buf[64];

    snprintf(
        buf,
        sizeof(buf),
        "%s %s",
        selected ? "▶ " : " ",
        label
    );

    draw_text(renderer, font, buf, x, y);
}
void draw_equip_state(SDL_Renderer *renderer, TTF_Font *font,
    bool owned, bool equipped, int x, int y)
{
    const char *label;

    if(!owned)
    {
        label = "【未所持】";
    }
    else if(equipped)
    {
        label = "【装備中】";
    }
    else
    {
        label = "【未装備】";
    }

    draw_text(renderer, font, label, x, y);
}

