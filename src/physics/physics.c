#include <stddef.h>
#include <raylib.h>
#include <stdint.h>
#include "math/vec2.h"
#include "physics.h"

static const float DT = 1.0f / FPS;

inline static uint32_t
add_generic(world_t* world, vec2_t position, float inverse_mass) {
    uint32_t id;
    if (world->n_free > 0) {
        id = world->free_ids[--world->n_free];
    } else {
        id = world->n_entities;
    }

    world->positions[id] = position;
    world->velocities[id] = zero_vec;
    world->accelerations[id] = zero_vec;
    world->force_accums[id] = zero_vec;
    world->inverse_masses[id] = inverse_mass;
    world->n_entities++;
    return id;
}

void
add_circle(world_t* world, vec2_t position, float inverse_mass, float radius) {
    uint32_t id = add_generic(world, position, inverse_mass);
    if (id > MAX_ENTITIES) {
        return;
    }
    world->circles_ids[world->n_circles] = id;
    world->radii[world->n_circles] = radius;

    world->n_circles++;
}

/* TODO: add generic remove function, or system for removing all objects */
void
remove_circle(world_t* world, int i) {
    uint32_t victim_id = world->circles_ids[i];
    uint32_t last_id = world->circles_ids[world->n_circles - 1];

    world->circles_ids[i] = last_id;
    world->radii[i] = world->radii[world->n_circles - 1];
    world->n_circles--;

    world->free_ids[world->n_free++] = victim_id;
    world->n_entities--;
}

void
apply_gravity(world_t* world) {
    for (size_t i = 0; i < world->n_entities; i++) {
        vec2_t* force_accum = &world->force_accums[i];
        float inverse_mass = world->inverse_masses[i];
        if (inverse_mass) {
            *force_accum = vec_plus_vec(*force_accum, (vec2_t) {0.0f, world->g / inverse_mass});
        }
    }
}

void
integrate(world_t* world) {
    for (size_t i = 0; i < world->n_entities; i++) {
        vec2_t* velocity = &world->velocities[i];
        vec2_t* force_accum = &world->force_accums[i];
        vec2_t* position = &world->positions[i];
        float inverse_mass = world->inverse_masses[i];

        vec2_t acc = scaled_vec(*force_accum, inverse_mass);
        *velocity = vec_plus_vec(*velocity, scaled_vec(acc, DT));

        *velocity = scaled_vec(*velocity, world->damping);

        *position = vec_plus_vec(*position, scaled_vec(*velocity, DT));

        *force_accum = zero_vec;
    }
}
