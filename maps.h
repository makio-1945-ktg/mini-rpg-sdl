#ifndef MAPS_H
#define MAPS_H

#define TILE_SIZE 32
#define FIELD_WIDTH 5
#define FIELD_HEIGHT 5

typedef struct {

    const char **tiles;

    int width;
    int height;

} Map;

extern const char *field_map[];

extern Map field;

#endif
