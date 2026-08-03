#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "player.h"

typedef enum
{
    ENEMY_SLIME,
    ENEMY_GOBLIN,
    ENEMY_ORC,

    ENEMY_BAT,
    ENEMY_SKELETON,
    ENEMY_GOLEM,

    ENEMY_SCORPION,
    ENEMY_LUCKY_FAIRY,
    ENEMY_WIZARD,

    ENEMY_KOBOLD,
    ENEMY_WISP,
    ENEMY_LAMIA
} EnemyType;

typedef struct {

    char name[40];

    int hp;
    int max_hp;

    int attack;
    int defense;

    int exp;
    int gold;

    int fire_resist;
    int ice_resist;
    int thunder_resist;

    bool frozen;
    int frozen_timer;

    bool burning;
    int burn_timer;

    bool stunned;
    int stun_timer;

    bool charging;

    EnemyType type;

} Enemy;

typedef struct {
    EnemyType type;

    char name[40];

    int hp;

    int attack;
    int defense;

    int exp;
    int gold;

    int fire_resist;
    int ice_resist;
    int thunder_resist;

} EnemyData;

void setup_field_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
);

void setup_cave_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *bat_texture,
    SDL_Texture *skeleton_texture,
    SDL_Texture *golem_texture
);

void setup_cave_b1_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *scorpion_texture,
    SDL_Texture *luckyfairy_texture,
    SDL_Texture *wizard_texture
);

void setup_cave_b2_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *kobold_texture,
    SDL_Texture *wisp_texture,
    SDL_Texture *lamia_texture
);

#endif
