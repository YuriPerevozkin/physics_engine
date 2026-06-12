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
    transform_t transform = {
        .velocity = zero_vec,
        .acceleration = zero_vec,
        .force_accum = zero_vec,
        .position = position,
        .inverse_mass = inverse_mass,
    };
    world->transforms[world->circles_n] = transform;
    world->circles[world->circles_n] = circle;
    world->circles_n++;
}

void remove_circle(world_t* world, int i) {
    world->transforms[i] = world->transforms[world->circles_n - 1];
    world->circles[i] = world->circles[world->circles_n - 1];
    world->circles_n--;
}

void
apply_gravity(world_t* world) {
    for (int i = 0; i < world->circles_n; i++) {
        transform_t* transform = &world->transforms[i];
        transform->force_accum = vec_plus_vec(transform->force_accum, (vec2_t) {0.0f, world->g / transform->inverse_mass});
    }
}

void
update_circles(world_t* world) {
    apply_gravity(world);
    for (int i = 0; i < world->circles_n; i++) {
        transform_t* transform = &world->transforms[i];
        circle_t circle = world->circles[i];

        vec2_t acc = scaled_vec(transform->force_accum, transform->inverse_mass);
        transform->velocity = vec_plus_vec(transform->velocity, scaled_vec(acc, DT));

        transform->velocity = scaled_vec(transform->velocity,  world->damping);

        transform->position = vec_plus_vec(transform->position, scaled_vec(transform->velocity, DT));

        if (transform->position.x < 0
                || transform->position.x > GetScreenWidth()
                || transform->position.y < 0
                || transform->position.y > GetScreenHeight()) {
            remove_circle(world, i);
            continue;
        }
        transform->force_accum = zero_vec;
    }
}
