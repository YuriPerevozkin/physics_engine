#include <raylib.h>
#include "math/vec2.h"
#include "physics.h"
#include "object.h"

static const float DT = 1.0f / FPS;

void
add_circle(world_t* world, vec2_t position, real inverse_mass, real radius) {
    circle_t circle = {
        .radius = radius
    };
    world->positions[world->circles_n] = position;
    world->velocities[world->circles_n] = zero_vec;
    world->accelerations[world->circles_n] = zero_vec;
    world->force_accums[world->circles_n] = zero_vec;
    world->inverse_masses[world->circles_n] = inverse_mass;

    world->circles[world->circles_n] = circle;
    world->circles_n++;
}

void remove_circle(world_t* world, int i) {
    world->positions[i] = world->positions[world->circles_n - 1];
    world->velocities[i] = world->velocities[world->circles_n - 1];
    world->accelerations[i] = world->accelerations[world->circles_n - 1];
    world->force_accums[i] = world->force_accums[world->circles_n - 1];
    world->inverse_masses[i] = world->inverse_masses[world->circles_n - 1];

    world->circles[i] = world->circles[world->circles_n - 1];
    world->circles_n--;
}

void
apply_gravity(world_t* world) {
    for (int i = 0; i < world->circles_n; i++) {
        vec2_t* force_accum = &world->force_accums[i];
        real inverse_mass = world->inverse_masses[i];
        *force_accum = (vec2_t) {0.0f, world->g / inverse_mass};
    }
}

void
update_circles(world_t* world) {
    apply_gravity(world);
    for (int i = 0; i < world->circles_n; i++) {
        vec2_t* velocity = &world->velocities[i];
        vec2_t* force_accum = &world->force_accums[i];
        vec2_t* position = &world->positions[i];
        real inverse_mass = world->inverse_masses[i];
        circle_t circle = world->circles[i];

        vec2_t acc = scaled_vec(*force_accum, inverse_mass);
        *velocity = vec_plus_vec(*velocity, scaled_vec(acc, DT));

        *velocity = scaled_vec(*velocity,  world->damping);

        *position = vec_plus_vec(*position, scaled_vec(*velocity, DT));

        if (position->x < 0
                || position->x > GetScreenWidth()
                || position->y < 0
                || position->y > GetScreenHeight()) {
            remove_circle(world, i);
            continue;
        }
        *force_accum = zero_vec;
    }
}
