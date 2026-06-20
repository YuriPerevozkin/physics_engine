#ifndef PHYSICS_H
#define PHYSICS_H


#include <stdint.h>
#include "math/precision.h"
#include "math/vec2.h"

#define FPS 60
#define INITIAL_G 9.807
#define INITIAL_DAMPING 0.997
#define MAX_ENTITIES 100000

typedef struct world {
    float g;
    float damping;

    uint32_t n_entities;
    uint32_t n_free;
    uint32_t free_ids[MAX_ENTITIES];

    vec2_t positions[MAX_ENTITIES];
    vec2_t velocities[MAX_ENTITIES];
    vec2_t accelerations[MAX_ENTITIES];
    vec2_t force_accums[MAX_ENTITIES];
    float inverse_masses[MAX_ENTITIES];

    uint32_t n_circles;
    uint32_t circles_ids[MAX_ENTITIES];
    float radii[MAX_ENTITIES];
} world_t;

/* physics.c */
void add_circle(world_t* world, vec2_t position, float inverse_mass, float radius);
void remove_circle(world_t* world, int i);
void apply_gravity(world_t* world);
void integrate(world_t* world);

#endif // PHYSICS_H
