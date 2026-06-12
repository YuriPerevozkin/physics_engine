#ifndef PHYSICS_H
#define PHYSICS_H


#include "object.h"

#define FPS 60
#define INITIAL_G 9.807
#define INITIAL_DAMPING 0.997
#define MAX_BODIES 100000

typedef struct world {
    vec2_t positions[MAX_BODIES];
    vec2_t velocities[MAX_BODIES];
    vec2_t accelerations[MAX_BODIES];
    vec2_t force_accums[MAX_BODIES];
    real inverse_masses[MAX_BODIES];

    circle_t circles[MAX_BODIES];
    int circles_n;

    real g;
    real damping;
} world_t;

/* physics.c */
world_t init_world();
void add_circle(world_t* world, vec2_t position, real inverse_mass, real radius);
void remove_circle(world_t* world, int i);
void update_circles(world_t* world);

#endif // PHYSICS_H
