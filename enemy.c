#include "enemy.h"

EnemyData field_enemy_table[] = {

    {ENEMY_SLIME, "スライム", 10, 2, 1, 5, 3, -50, 0, 50},
    {ENEMY_GOBLIN, "ゴブリン", 15, 3, 2, 10, 8, 0, 0, 0},
    {ENEMY_ORC, "オーク", 20, 5, 3, 20, 15, 50, -50, 0}
};

EnemyData cave_enemy_table[] = {

    {ENEMY_BAT, "こうもり", 30, 4, 2, 15, 10, 0, 0, -50},
    {ENEMY_SKELETON, "スケルトン", 35, 6, 4, 25, 15, -50, 0, 0},
    {ENEMY_GOLEM, "ゴーレム", 50, 10, 8, 40, 25, 50, 50, -50}
};

EnemyData cave_b1_enemy_table[] = {

    {ENEMY_SCORPION, "スコルピオ", 40, 8, 8, 30, 20, 0, -50, 50},
    {ENEMY_LUCKY_FAIRY, "ラッキーフェアリー", 30, 30, 4, 80, 25, 50, 50, 50},
    {ENEMY_WIZARD, "まどうし", 60, 6, 4, 50, 30, 50, 50, 50}
};

EnemyData cave_b2_enemy_table[] = {

    {ENEMY_KOBOLD, "コボルト", 80, 12, 10, 40, 30, 0, 0, 0},
    {ENEMY_WISP, "ウィスプ", 70, 8, 12, 45, 25, 100, -100, 0},
    {ENEMY_LAMIA, "ラミア", 90, 10, 10, 60, 50, 0, 100, 0}
};

EnemyData temple_enemy_table[] = {

    {ENEMY_DRAGON, "", 200, 14, 14, 0, 0, 100, 0, 50}
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

    enemy->type =
        field_enemy_table[enemy_type].type;

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

    enemy->burning = false;
    enemy->burn_timer = 0;

    enemy->stunned = false;
    enemy->stun_timer = 0;
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

    enemy->type =
        cave_enemy_table[enemy_type].type;

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

    enemy->burning = false;
    enemy->burn_timer = 0;

    enemy->stunned = false;
    enemy->stun_timer = 0;

    enemy->charging = false;
}

void setup_cave_b1_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *scorpion_texture,
    SDL_Texture *luckyfairy_texture,
    SDL_Texture *wizard_texture
)
{
    int enemy_type = rand() % 3;

    if(enemy_type == 0)
    {
        *current_enemy_texture = scorpion_texture;
    }
    else if(enemy_type == 1)
    {
        *current_enemy_texture = luckyfairy_texture;
    }
    else
    {
        *current_enemy_texture = wizard_texture;
    }

    strcpy(
        enemy->name,
        cave_b1_enemy_table[enemy_type].name
    );

    enemy->type =
        cave_b1_enemy_table[enemy_type].type;

    enemy->hp =
        cave_b1_enemy_table[enemy_type].hp;

    enemy->max_hp =
        cave_b1_enemy_table[enemy_type].hp;

    enemy->attack =
        cave_b1_enemy_table[enemy_type].attack;

    enemy->defense =
        cave_b1_enemy_table[enemy_type].defense;

    enemy->exp =
        cave_b1_enemy_table[enemy_type].exp;

    enemy->gold =
        cave_b1_enemy_table[enemy_type].gold;

    enemy->fire_resist =
        cave_b1_enemy_table[enemy_type].fire_resist;

    enemy->ice_resist =
        cave_b1_enemy_table[enemy_type].ice_resist;

    enemy->thunder_resist =
        cave_b1_enemy_table[enemy_type].thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;

    enemy->burning = false;
    enemy->burn_timer = 0;

    enemy->stunned = false;
    enemy->stun_timer = 0;

}

void setup_cave_b2_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *kobold_texture,
    SDL_Texture *wisp_texture,
    SDL_Texture *lamia_texture
)
{
    int enemy_type = rand() % 3;

    if(enemy_type == 0)
    {
        *current_enemy_texture = kobold_texture;
    }
    else if(enemy_type == 1)
    {
        *current_enemy_texture = wisp_texture;
    }
    else
    {
        *current_enemy_texture = lamia_texture;
    }

    strcpy(
        enemy->name,
        cave_b2_enemy_table[enemy_type].name
    );

    enemy->type =
        cave_b2_enemy_table[enemy_type].type;

    enemy->hp =
        cave_b2_enemy_table[enemy_type].hp;

    enemy->max_hp =
        cave_b2_enemy_table[enemy_type].hp;

    enemy->attack =
        cave_b2_enemy_table[enemy_type].attack;

    enemy->defense =
        cave_b2_enemy_table[enemy_type].defense;

    enemy->exp =
        cave_b2_enemy_table[enemy_type].exp;

    enemy->gold =
        cave_b2_enemy_table[enemy_type].gold;

    enemy->fire_resist =
        cave_b2_enemy_table[enemy_type].fire_resist;

    enemy->ice_resist =
        cave_b2_enemy_table[enemy_type].ice_resist;

    enemy->thunder_resist =
        cave_b2_enemy_table[enemy_type].thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;

    enemy->burning = false;
    enemy->burn_timer = 0;

    enemy->stunned = false;
    enemy->stun_timer = 0;

}

void setup_temple_enemy(
    Enemy *enemy,
    SDL_Texture **current_enemy_texture,
    SDL_Texture *dragon_texture
)
{
    int enemy_type = ENEMY_DRAGON;

    enemy->type =
        temple_enemy_table[enemy_type].type;

    enemy->hp =
        temple_enemy_table[enemy_type].hp;

    enemy->max_hp =
        temple_enemy_table[enemy_type].hp;

    enemy->attack =
        temple_enemy_table[enemy_type].attack;

    enemy->defense =
        temple_enemy_table[enemy_type].defense;

    enemy->exp =
        temple_enemy_table[enemy_type].exp;

    enemy->gold =
        temple_enemy_table[enemy_type].gold;

    enemy->fire_resist =
        temple_enemy_table[enemy_type].fire_resist;

    enemy->ice_resist =
        temple_enemy_table[enemy_type].ice_resist;

    enemy->thunder_resist =
        temple_enemy_table[enemy_type].thunder_resist;

    enemy->frozen = false;
    enemy->frozen_timer = 0;

    enemy->burning = false;
    enemy->burn_timer = 0;

    enemy->stunned = false;
    enemy->stun_timer = 0;
}
