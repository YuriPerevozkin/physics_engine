#include <stddef.h>
#include "object.h"

typedef struct world {
    object_t* objects;
    size_t object_count;
} world_t;

world_t init_world(object_t* objects, size_t object_count);
