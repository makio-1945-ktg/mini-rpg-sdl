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

    bool burning;
    int burn_timer;

    bool stunned;
    int stun_timer;

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
} MagicEffect;

typedef MagicEffect FireEffect;
typedef MagicEffect IceEffect;
typedef MagicEffect ThunderEffect;

void battle_start(void);

void battle_attack(
    Player *player,
    Enemy *enemy,
    DamagePopup *popup,
    HitEffect *hit_effect,
    SlashEffect *slash_effect,
    BattleMode *battle_mode
);

void battle_defend(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
);

void battle_heal(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
);

void battle_item(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
);

void enemy_defeat(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
);

int apply_element_resistance(
    int damage,
    int resist
);

void enemy_turn(
    Player *player,
    Enemy *enemy,
    BattleMode *battle_mode
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

void end_battle(
    BattleMode *battle_mode
);

#endif
