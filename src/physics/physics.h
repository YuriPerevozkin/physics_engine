#ifndef PHYSICS_H
#define PHYSICS_H


#include <stddef.h>
#include "object.h"

#define FPS 60

typedef struct world {
    object_t* objects;
    size_t objects_n;
    size_t cap;
} world_t;

extern real g;

/* physics.c */
world_t init_world();
void add_object(world_t* world, object_t object);
void apply_physics(object_t* object);
void remove_object(world_t* world, int index);

#endif // PHYSICS_H
