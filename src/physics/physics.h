#include "object.h"

typedef struct world {
    object_t* objects;
} world_t;

world_t init_world(object_t* objects);
