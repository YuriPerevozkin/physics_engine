#include <stdio.h>
#include <stdlib.h>
#include "math/vec2.h"
#include "physics.h"
#include "object.h"

static const size_t DEFAULT_CAP = 5;
static const real DURATION = 1.0f / FPS;
real g = 9.807f;

world_t
init_world() {
    return (world_t) {
        .objects = malloc(DEFAULT_CAP * sizeof(object_t)),
        .objects_n = 0,
        .cap = DEFAULT_CAP,
    };
}

void
add_object(world_t* world, object_t object) {
    if (world->objects_n == world->cap) {
        world->cap *= 2;
        world->objects = realloc(world->objects, world->cap * sizeof(object_t));
    }
    world->objects[world->objects_n] = object;
    world->objects_n += 1;
}

void
apply_physics(object_t* object) {
    switch (object->type) {
        case PARTICLE:;
            particle_t* particle = &object->shape.particle;
            particle->position = vec_plus_vec(particle->position, scaled_vec(object->velocity, DURATION));

            real mass = 1.0f / object->inverse_mass;
            vec2_t force = {0.0f, mass*g};
            vec2_t resulting_acc = object->acceleration;
            resulting_acc = vec_plus_vec(resulting_acc, scaled_vec(force, object->inverse_mass));

            object->velocity = vec_plus_vec(object->velocity, scaled_vec(resulting_acc, DURATION));
            break;
    }
}
