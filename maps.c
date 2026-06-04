#include "maps.h"
#include "tile.h"

const char *field_map[] = {

    "MMMMM",
    "MGGGM",
    "MG@GM",
    "MGTGM",
    "MMMMM",
};

Map field = {

    field_map,

    FIELD_WIDTH,
    FIELD_HEIGHT,

};
