#include "render.h"

void draw_shop(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int shop_cursor
)
{
    SDL_Rect window = {80, 100, 400, 280};

    SDL_SetRenderDrawColor(renderer, 100, 40, 40, 255);
    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, "購入選択", 130, 110);

    draw_menu_item(renderer, font, "　剣　 20G", 120, 150, shop_cursor == 0);
    draw_menu_item(renderer, font, "革の鎧 30G", 120, 180, shop_cursor == 1);
    draw_menu_item(renderer, font, "店を出る", 120, 210, shop_cursor == 2);

    draw_text(renderer, font, "===装備説明===", 120, 280);

    if(shop_cursor == 0)
    {
        draw_text(renderer, font, "攻撃力 +2", 120, 310);
    }
    else if(shop_cursor == 1)
    {
        draw_text(renderer, font, "防御力 +4", 120, 310);
    }

    draw_text(renderer, font, "所持金:", 300, 120);

    char status[32];
    sprintf(status, "%d", player->gold);
    draw_text(renderer, font, status, 420, 120);
}

void draw_item_shop(
    SDL_Renderer *renderer,
    TTF_Font *font,
    Player *player,
    int item_shop_cursor
)
{
    SDL_Rect window = {80, 100, 450, 280};

    SDL_SetRenderDrawColor(renderer, 100, 200, 40, 255);
    SDL_RenderFillRect(renderer, &window);

    draw_text(renderer, font, "購入選択", 130, 110);

    draw_menu_item(renderer, font, "ポーション 10G", 120, 150, item_shop_cursor == 0);
    draw_menu_item(renderer, font, "エーテル　 30G", 120, 180, item_shop_cursor == 1);
    draw_menu_item(renderer, font, "戻りの紐　 50G", 120, 210, item_shop_cursor == 2);
    draw_menu_item(renderer, font, "店を出る", 120, 240, item_shop_cursor == 3);

    draw_text(renderer, font, "===アイテム説明===", 120, 300);

    if(item_shop_cursor == 0)
    {
        draw_text(renderer, font, "HPを20回復", 120, 330);
    }
    else if(item_shop_cursor == 1)
    {
        draw_text(renderer, font, "MPを40回復", 120, 330);
    }
    else if(item_shop_cursor == 2)
    {
        draw_text(renderer, font, "ダンジョンから脱出", 120, 330);
    }
    draw_text(renderer, font, "所持金:", 300, 120);

    char status[32];
    sprintf(status, "%d", player->gold);
    draw_text(renderer, font, status, 420, 120);
}

