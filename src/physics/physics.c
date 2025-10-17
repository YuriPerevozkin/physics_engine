#include "physics.h"

world_t
init_world(object_t* objects, size_t object_count) {
    return (world_t) { .objects = objects, .object_count = object_count };
}
