#include "render.h"

void draw_status(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player
)
{
    SDL_Rect window = {80, 100, 400, 280};

    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, "ステータス画面", 130, 110);

    char text[64];

    sprintf(
        text,
        "LV : %d",
        player->level
    );

    draw_text(renderer, font, text, 120, 150);

    sprintf(text, "HP : %d / %d", player->hp, player->max_hp);

    draw_text(renderer, font, text, 120, 180);

    sprintf(text, "MP : %d / %d", player->mp, player->max_mp);

    draw_text(renderer, font, text, 120, 210);

    sprintf(text, "ATK : %d", player->attack);

    draw_text(renderer, font, text, 120, 240);

    sprintf(text, "DEF : %d", player->defense);

    draw_text(renderer, font, text, 120, 270);

    sprintf(text, "EXP : %d", player->exp);

    draw_text(renderer, font, text, 120, 300);

    sprintf(text, "GOLD : %d", player->gold);

    draw_text(renderer, font, text, 120, 330);
}

void draw_item(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int item_cursor
)
{
    SDL_Rect window = {80, 100, 400, 280};

    SDL_SetRenderDrawColor(renderer, 40, 80, 40, 255);
    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, "所持アイテム", 130, 110);

    draw_menu_item(renderer, font, "ポーション", 120, 150, item_cursor == 0);
    draw_menu_item(renderer, font, "エーテル", 120, 180, item_cursor == 1);
    draw_menu_item(renderer, font, "戻りの紐", 120, 210, item_cursor == 2);
    draw_menu_item(renderer, font, "爆薬", 120, 240, item_cursor == 3);
    draw_menu_item(renderer, font, "ドラゴンの宝玉", 120, 270, item_cursor == 4);
}

void draw_equipment(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int equipment_cursor
)
{
    SDL_Rect window = {100, 30, 400, 480};

    SDL_SetRenderDrawColor(renderer, 40, 80, 40, 255);
    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, "装備一覧", 220, 40);

    draw_menu_item(renderer, font, "剣", 120, 80, equipment_cursor == 0);
    draw_equip_state(renderer, font,
        player->equipment.sword,
        player->equipment.sword_equipped,
        350, 80);

    draw_menu_item(renderer, font, "革の鎧", 120, 110, equipment_cursor == 1);
    draw_equip_state(renderer, font,
        player->equipment.leather_armor,
        player->equipment.leather_armor_equipped,
        350, 110);

    draw_menu_item(renderer, font, "木の盾", 120, 140, equipment_cursor == 2);
    draw_equip_state(renderer, font,
        player->equipment.wooden_shield,
        player->equipment.wooden_shield_equipped,
        350, 140);

    draw_menu_item(renderer, font, "ブロードソード", 120, 170, equipment_cursor == 3);
    draw_equip_state(renderer, font,
        player->equipment.broad_sword,
        player->equipment.broad_sword_equipped,
        350, 170);

    draw_menu_item(renderer, font, "ルーンソード", 120, 200, equipment_cursor == 4);
    draw_equip_state(renderer, font,
        player->equipment.rune_sword,
        player->equipment.rune_sword_equipped,
        350, 200);

    draw_menu_item(renderer, font, "ルーンアーマー", 120, 230, equipment_cursor == 5);
    draw_equip_state(renderer, font,
        player->equipment.rune_armor,
        player->equipment.rune_armor_equipped,
        350, 230);

    draw_menu_item(renderer, font, "ルーンシールド", 120, 260, equipment_cursor == 6);
    draw_equip_state(renderer, font,
        player->equipment.rune_shield,
        player->equipment.rune_shield_equipped,
        350, 260);

    draw_text(renderer, font, "ATK:", 120, 330);

    char status[32];
    sprintf(status, "%d", player->attack);
    draw_text(renderer, font, status, 190, 330);

    draw_text(renderer, font, "DEF:", 120, 360);

    sprintf(status, "%d", player->defense);
    draw_text(renderer, font, status, 190, 360);

    draw_text(renderer, font, "===装備説明===", 120, 400);
    draw_text(renderer, font, "ENTER：装備/解除", 290, 430);
    draw_text(renderer, font, "ESC：戻る", 290, 460);

    static const char *equip_desc[] = {
        "攻撃力 +2",
        "防御力 +4",
        "防御力 +2",
        "攻撃力 +5",
        "攻撃力 +9",
        "防御力 +8",
        "防御力 +5"
    };

    if(equipment_cursor >= 0 && equipment_cursor < 7)
    {
        draw_text(renderer, font, equip_desc[equipment_cursor], 120, 430);
    }
}

void draw_save(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int save_cursor
)
{
    SDL_Rect window = {80, 100, 400, 280};

    SDL_SetRenderDrawColor(renderer, 40, 80, 80, 255);
    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, "セーブ管理", 130, 110);

    draw_menu_item(renderer, font, "セーブ", 120, 150, save_cursor == 0);
    draw_menu_item(renderer, font, "ロード", 120, 180, save_cursor == 1);
}

