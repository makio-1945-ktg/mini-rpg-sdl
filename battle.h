#ifndef BATTLE_H
#define BATTLE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "player.h"

typedef enum {
    MODE_FIELD,
    MODE_BATTLE,
    MODE_MAGIC
} BattleMode;

#define LOG_LINES 3

extern char battle_logs[LOG_LINES][128];

void add_battle_log(const char *message);

typedef struct {

    char text[32];
    int x;
    int y;
    int timer;
    bool active;

} DamagePopup;

typedef struct {

    char name[20];

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

} Enemy;

typedef struct {

    char name[20];

    int hp;
    int attack;
    int defense;

    int exp;
    int gold;

    int fire_resist;
    int ice_resist;
    int thunder_resist;
} EnemyData;

extern EnemyData enemy_table[];

typedef struct {
    int x;
    int y;
    int shake_timer;
} EnemySprite;

typedef struct {
    int timer;
    bool active;
} HitEffect;

typedef struct {
    int timer;
    bool active;
} SlashEffect;

typedef struct {
    int timer;
    bool active;
} FireEffect;

typedef struct {
    int timer;
    bool active;
} IceEffect;

typedef struct {
    int timer;
    bool active;
} ThunderEffect;

void battle_start(void);

bool battle_attack(
    Player *player,
    Enemy *enemy,
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect
);

bool battle_defend(
    Player *player,
    Enemy *enemy
);

bool battle_heal(
    Player *player,
    Enemy *enemy
);

bool battle_fire(
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect
);

bool battle_ice(
    Player *player,
    Enemy *enemy,
    IceEffect *ice_effect
);

bool battle_thunder(
    Player *player,
    Enemy *enemy,
    ThunderEffect *thunder_effect
);

bool battle_item(
    Player *player,
    Enemy *enemy
);

bool enemy_turn(
    Player *player,
    Enemy *enemy
);

void handle_normal_battle_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *battle_cursor,
    Player *player,
    Enemy *enemy,
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    EnemySprite *enemy_sprite
);

void handle_magic_input(
    SDL_Event *event,
    BattleMode *battle_mode,
    int *magic_cursor,
    Player *player,
    Enemy *enemy,
    FireEffect *fire_effect,
    IceEffect *ice_effect,
    ThunderEffect *thunder_effect
);

void start_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture,
    Player *player,
    int new_x,
    int new_y
);

#endif
