#include "enemy.h"

EnemyData field_enemy_table[] = {

    {"スライム", 10, 2, 1, 5, 3, -50, 0, 50},
    {"ゴブリン", 15, 3, 2, 10, 8, 0, 0, 0},
    {"オーク", 20, 5, 3, 20, 15, 50, -50, 0}
};

EnemyData cave_enemy_table[] = {

    {"こうもり", 20, 4, 2, 15, 10, 0, 0, -50},
    {"スケルトン", 25, 6, 4, 25, 15, -50, 0, 0},
    {"ゴーレム", 40, 10, 8, 40, 25, 50, 50, -50}
};


void setup_field_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
)
{
    int enemy_type = rand() % 3;

    if(enemy_type == 0)
    {
        *current_enemy_texture = slime_texture;
    }
    else if(enemy_type == 1)
    {
        *current_enemy_texture = goblin_texture;
    }
    else
    {
        *current_enemy_texture = orc_texture;
    }

    strcpy(
        enemy->name,
        field_enemy_table[enemy_type].name
    );

    enemy->hp =
        field_enemy_table[enemy_type].hp;

    enemy->max_hp =
        field_enemy_table[enemy_type].hp;

    enemy->attack =
        field_enemy_table[enemy_type].attack;

    enemy->defense =
        field_enemy_table[enemy_type].defense;

    enemy->exp =
        field_enemy_table[enemy_type].exp;

    enemy->gold =
        field_enemy_table[enemy_type].gold;

    enemy->fire_resist =
        field_enemy_table[enemy_type].fire_resist;

    enemy->ice_resist =
        field_enemy_table[enemy_type].ice_resist;

    enemy->thunder_resist =
        field_enemy_table[enemy_type].thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;
}

void setup_cave_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *bat_texture,
    SDL_Texture *skeleton_texture,
    SDL_Texture *golem_texture
)
{
    int enemy_type = rand() % 3;

    if(enemy_type == 0)
    {
        *current_enemy_texture = bat_texture;
    }
    else if(enemy_type == 1)
    {
        *current_enemy_texture = skeleton_texture;
    }
    else
    {
        *current_enemy_texture = golem_texture;
    }

    strcpy(
        enemy->name,
        cave_enemy_table[enemy_type].name
    );

    enemy->hp =
        cave_enemy_table[enemy_type].hp;

    enemy->max_hp =
        cave_enemy_table[enemy_type].hp;

    enemy->attack =
        cave_enemy_table[enemy_type].attack;

    enemy->defense =
        cave_enemy_table[enemy_type].defense;

    enemy->exp =
        cave_enemy_table[enemy_type].exp;

    enemy->gold =
        cave_enemy_table[enemy_type].gold;

    enemy->fire_resist =
        cave_enemy_table[enemy_type].fire_resist;

    enemy->ice_resist =
        cave_enemy_table[enemy_type].ice_resist;

    enemy->thunder_resist =
        cave_enemy_table[enemy_type].thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;
}
