#ifndef MAP_H
#define MAP_H

extern char field_map[5][6];

char get_tile(int x, int y);

//イベント関数
void town_event(void);

void npc_event(void);

void chest_event(int x, int y);

void enemy_event(int x, int y);

#endif
