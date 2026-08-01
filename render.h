#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "player.h"
#include "battle.h"

void draw_player(
    SDL_Renderer *renderer,
    int x,
    int y
);

void draw_text(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *text,
    int x,
    int y
);

void draw_status(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player
);

void draw_item(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int item_cursor
);

void draw_equipment(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int equipment_cursor
);

void draw_save(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int save_cursor
);

void draw_map(
    SDL_Renderer *renderer
);

void draw_town_map(
    SDL_Renderer *renderer
);

void draw_cave_map(
    SDL_Renderer *renderer
);

void draw_cave_b1_map(
    SDL_Renderer *renderer
);

void draw_cave_b2_map(
    SDL_Renderer *renderer
);

void draw_battle_background(
    SDL_Renderer *renderer
);

void draw_battle_ui(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    Enemy *enemy,
    EnemySprite *enemy_sprite,
    SDL_Texture *enemy_texture,
    int battle_cursor
);

void draw_hp_bar(
    SDL_Renderer *renderer,
    int x,
    int y,
    int current_hp,
    int max_hp
);

void draw_magic_menu(
    SDL_Renderer *renderer,
    TTF_Font *font,
    int magic_cursor
);

void draw_item_menu(
    SDL_Renderer *renderer,
    TTF_Font *font,
    int use_item_cursor
);

void draw_battle_effects(
    SDL_Renderer *renderer,
    FireEffect *fire_effect,
    IceEffect *ice_effect,
    ThunderEffect *thunder_effect,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    EnemySprite *enemy_sprite
);

void update_battle_effects(
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    FireEffect *fire_effect,
    IceEffect *ice_effect,
    ThunderEffect *thunder_effect,
    EnemySprite *enemy_sprite
);

void draw_message(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *message
);

#endif
