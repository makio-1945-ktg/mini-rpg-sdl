#include "enemy.h"

#include <string.h>

static void apply_enemy_data(
    Enemy *enemy,
    const EnemyData *data
)
{
    strcpy(enemy->name, data->name);
    enemy->type = data->type;
    enemy->hp = data->hp;
    enemy->max_hp = data->hp;
    enemy->attack = data->attack;
    enemy->defense = data->defense;
    enemy->exp = data->exp;
    enemy->gold = data->gold;
    enemy->fire_resist = data->fire_resist;
    enemy->ice_resist = data->ice_resist;
    enemy->thunder_resist = data->thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;
    enemy->burning = false;
    enemy->burn_timer = 0;
    enemy->stunned = false;
    enemy->stun_timer = 0;
    enemy->charging = false;
}

EnemyData field_enemy_table[] = {

    {ENEMY_SLIME, "スライム", 10, 2, 1, 5, 3, -50, 0, 50},
    {ENEMY_GOBLIN, "ゴブリン", 15, 3, 2, 8, 5, 0, 0, 0},
    {ENEMY_ORC, "オーク", 20, 5, 3, 12, 8, 50, -50, 0}
};

EnemyData cave_enemy_table[] = {

    {ENEMY_BAT, "こうもり", 30, 4, 2, 12, 7, 0, 0, -50},
    {ENEMY_SKELETON, "スケルトン", 35, 6, 4, 18, 8, -50, 0, 0},
    {ENEMY_GOLEM, "ゴーレム", 50, 10, 8, 40, 25, 50, 50, -50}
};

EnemyData cave_b1_enemy_table[] = {

    {ENEMY_SCORPION, "スコルピオ", 40, 8, 8, 20, 10, 0, -50, 50},
    {ENEMY_LUCKY_FAIRY, "ラッキーフェアリー", 30, 30, 4, 80, 25, 50, 50, 50},
    {ENEMY_WIZARD, "まどうし", 60, 6, 4, 50, 15, 50, 50, 50}
};

EnemyData cave_b2_enemy_table[] = {

    {ENEMY_KOBOLD, "コボルト", 80, 12, 10, 25, 13, 0, 0, 0},
    {ENEMY_WISP, "ウィスプ", 70, 8, 12, 35, 8, 100, -100, 0},
    {ENEMY_LAMIA, "ラミア", 90, 10, 10, 60, 20, 0, 100, 0}
};

EnemyData temple_enemy_table[] = {

    {ENEMY_DRAGON, "竜神", 200, 14, 14, 0, 0, 100, 0, 50}
};

void setup_field_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *slime_texture,
    SDL_Texture *goblin_texture,
    SDL_Texture *orc_texture
)
{
    int index = rand() % 3;
    SDL_Texture *textures[] = {slime_texture, goblin_texture, orc_texture};

    *current_enemy_texture = textures[index];
    apply_enemy_data(enemy, &field_enemy_table[index]);
}

void setup_cave_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *bat_texture,
    SDL_Texture *skeleton_texture,
    SDL_Texture *golem_texture
)
{
    int roll = rand() % 10;
    int index = (roll < 5) ? 0 : (roll < 8) ? 1 : 2;
    SDL_Texture *textures[] = {bat_texture, skeleton_texture, golem_texture};

    *current_enemy_texture = textures[index];
    apply_enemy_data(enemy, &cave_enemy_table[index]);
}

void setup_cave_b1_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *scorpion_texture,
    SDL_Texture *luckyfairy_texture,
    SDL_Texture *wizard_texture
)
{
    int roll = rand() % 10;
    int index = (roll < 6) ? 0 : (roll < 8) ? 1 : 2;
    SDL_Texture *textures[] = {scorpion_texture, luckyfairy_texture, wizard_texture};

    *current_enemy_texture = textures[index];
    apply_enemy_data(enemy, &cave_b1_enemy_table[index]);
}

void setup_cave_b2_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *kobold_texture,
    SDL_Texture *wisp_texture,
    SDL_Texture *lamia_texture
)
{
    int roll = rand() % 10;
    int index = (roll < 4) ? 0 : (roll < 9) ? 1 : 2;
    SDL_Texture *textures[] = {kobold_texture, wisp_texture, lamia_texture};

    *current_enemy_texture = textures[index];
    apply_enemy_data(enemy, &cave_b2_enemy_table[index]);
}

void setup_temple_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *dragon_texture
)
{
    *current_enemy_texture = dragon_texture;
    apply_enemy_data(enemy, &temple_enemy_table[0]);
}

