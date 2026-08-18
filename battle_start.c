#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "battle.h"
#include "enemy_skill.h"
#include "map.h"
#include "magic.h"
#include "cave.h"
#include "cave_b1.h"
#include "cave_b2.h"
#include "temple.h"
#include "message_ui.h"

void start_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture,
    Player *player,
    int new_x,
    int new_y
)
{
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;
    *use_item_cursor = 0;

    setup_field_enemy(
        enemy,
        current_enemy_texture,
        slime_texture,
        goblin_texture,
        orc_texture
    );

    enemy_event(field_map, new_x, new_y);

    add_battle_log("敵が現れた！");
}

void start_cave_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *bat_texture,
    SDL_Texture *skeleton_texture,
    SDL_Texture *golem_texture,
    Player *player,
    int new_x,
    int new_y
)
{
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;
    *use_item_cursor = 0;

    setup_cave_enemy(
        enemy,
        current_enemy_texture,
        bat_texture,
        skeleton_texture,
        golem_texture
    );

    enemy_event(cave_map, new_x, new_y);

    add_battle_log("敵が現れた！");
}

void start_cave_b1_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *scorpion_texture,
    SDL_Texture *luckyfairy_texture,
    SDL_Texture *wizard_texture,
    Player *player,
    int new_x,
    int new_y
)
{
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;
    *use_item_cursor = 0;

    setup_cave_b1_enemy(
        enemy,
        current_enemy_texture,
        scorpion_texture,
        luckyfairy_texture,
        wizard_texture
    );

    enemy_event(cave_b1_map, new_x, new_y);

    add_battle_log("敵が現れた！");
}

void start_cave_b2_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *kobold_texture,
    SDL_Texture *wisp_texture,
    SDL_Texture *lamia_texture,
    Player *player,
    int new_x,
    int new_y
)
{
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;
    *use_item_cursor = 0;

    setup_cave_b2_enemy(
        enemy,
        current_enemy_texture,
        kobold_texture,
        wisp_texture,
        lamia_texture
    );

    enemy_event(cave_b2_map, new_x, new_y);

    add_battle_log("敵が現れた！");
}

void start_boss_battle(
    BattleMode *battle_mode,
    int *battle_cursor,
    int *magic_cursor,
    int *use_item_cursor,
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *dragon_texture,
    Player *player,
    int new_x,
    int new_y
)
{ 
    *battle_mode = MODE_BATTLE;
    *battle_cursor = 0;
    *magic_cursor = 0;
    *use_item_cursor = 0;

    setup_temple_enemy(
        enemy,
        current_enemy_texture,
        dragon_texture
    );

    temple_map[new_y][new_x] = 'G';

    add_battle_log("石像の封印が解かれて竜神が姿を現した！");
}
