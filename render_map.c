#include "render.h"
#include "map.h"
#include "cave.h"
#include "cave_b1.h"
#include "cave_b2.h"
#include "temple.h"

#define TILE_SIZE 32

static const TileColor field_colors[] = {
    {'M', 100,100,100,255},
    {'W', 0,100,255,255},
    {'.', 0,255,0,255},
    {'G', 0,255,0,255},
    {'T', 255,255,0,255},
    {'V', 200,200,200,255},
    {'S', 100,100,0,255},
    {'C', 50,200,200,255},
    {'E', 255,0,0,255},
};

static const TileColor town_colors[] = {
    {'M', 100,100,100,255},
    {'G', 0,255,0,255},
    {'N', 255,0,255,255},
    {'I', 0,255,255,255},
    {'Q', 255,128,0,255},
    {'O', 255,255,255,255},
};

static const TileColor cave_colors[] = {
    {'M', 100,100,100,255},
    {'W', 0,100,255,255},
    {'.', 30,30,30,255},
    {'F', 30,30,30,255},
    {'U', 0,200,0,255},
    {'D', 200,0,0,255},
    {'C', 150,75,0,255},
    {'E', 255,0,0,255},
};

static const TileColor cave_b1_colors[] = {
    {'M', 100,100,100,255},
    {'W', 0,100,255,255},
    {'.', 30,30,30,255},
    {'F', 30,30,30,255},
    {'U', 0,200,0,255},
    {'D', 200,0,0,255},
    {'O', 0,0,200,255},
    {'C', 150,75,0,255},
    {'E', 255,0,0,255},
};

static const TileColor temple_colors[] = {
    {'M', 100,100,100,255},
    {'G', 0,255,0,255},
    {'N', 255,0,255,255},
    {'D', 255,100,0,255},
    {'O', 255,255,255,255},
};

static const TileColor cave_b2_colors[] = {
    {'M', 100,100,100,255},
    {'W', 0,100,255,255},
    {'.', 30,30,30,255},
    {'F', 30,30,30,255},
    {'U', 200,0,0,255},
    {'P', 0,100,200,255},
    {'C', 50,200,200,255},
    {'E', 255,0,0,255},
};

void draw_map(SDL_Renderer *renderer)
{
    draw_tile_map(renderer, (const char *)field_map, 21, 20, 15,
        field_colors, sizeof(field_colors) / sizeof(field_colors[0]));
}

void draw_town_map(SDL_Renderer *renderer)
{
    draw_tile_map(renderer, (const char *)town_map, 9, 8, 8,
        town_colors, sizeof(town_colors) / sizeof(town_colors[0]));
}

void draw_cave_map(SDL_Renderer *renderer)
{
    draw_tile_map(renderer, (const char *)cave_map, 21, 20, 15,
        cave_colors, sizeof(cave_colors) / sizeof(cave_colors[0]));
}

void draw_cave_b1_map(SDL_Renderer *renderer)
{
    draw_tile_map(renderer, (const char *)cave_b1_map, 21, 20, 15,
        cave_b1_colors, sizeof(cave_b1_colors) / sizeof(cave_b1_colors[0]));
}

void draw_cave_b2_map(SDL_Renderer *renderer)
{
    draw_tile_map(renderer, (const char *)cave_b2_map, 21, 20, 15,
        cave_b2_colors, sizeof(cave_b2_colors) / sizeof(cave_b2_colors[0]));
}

void draw_temple_map(SDL_Renderer *renderer)
{
    draw_tile_map(renderer, (const char *)temple_map, 10, 9, 11,
        temple_colors, sizeof(temple_colors) / sizeof(temple_colors[0]));
}
