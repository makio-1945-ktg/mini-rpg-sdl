#include <stdio.h>

#include "battle.h"

void battle_start(void)
{
    int enemy_hp = 10;

    printf("\n");
    printf("=== BATTLE ===\n");
    printf("スライムが現れた！\n");

    while(enemy_hp > 0)
    {
        printf("\n");
        printf("スライム HP:%d\n", enemy_hp);
        printf("1:攻撃\n");

        int cmd;
        scanf("%d", &cmd);

        if(cmd == 1)
        {
            printf("攻撃！\n");

            enemy_hp -= 3;
        }
    }

    printf("スライムを倒した！\n");
}
