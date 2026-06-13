#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
//プレイヤー座標
    int x;
    int y;
//プレイヤーステータス
    int hp;
    int max_hp;

    int mp;
    int max_mp;

    int attack;
    int defense;

    int level;

    int exp;

    int gold;
//プレイヤーアイテム
    int potion;
//プレイヤー装備
    int sword;

}Player;

#endif
