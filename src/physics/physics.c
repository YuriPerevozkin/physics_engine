#include <stdlib.h>
#include "math/vec2.h"
#include "physics.h"
#include "object.h"

static const size_t DEFAULT_CAP = 5;
static const float DURATION = 1.0f / FPS;
static const float SLEEP_THRESHOLD = 0.001;

float g = 9.807f;
float damping = 0.997;

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
remove_object(world_t* world, int index) {
    world->objects[index] = world->objects[world->objects_n - 1];
    world->objects_n--;
}

void
apply_physics_particle(object_t* object) {
    particle_t* particle = &object->shape.particle;
    particle->position = vec_plus_vec(particle->position, scaled_vec(object->velocity, DURATION));

    object->force_accum = (vec2_t) {0.0f, g / object->inverse_mass};
    vec2_t resulting_acc = object->acceleration;
    resulting_acc = vec_plus_vec(resulting_acc, scaled_vec(object->force_accum, object->inverse_mass));

    object->velocity = vec_plus_vec(object->velocity, scaled_vec(resulting_acc, DURATION));
    object->velocity.x = object->velocity.x * damping;
    object->velocity.y = object->velocity.y * damping;
    if (vec_length(object->velocity) < SLEEP_THRESHOLD) {
        object->velocity = zero_vec;
    }
}
