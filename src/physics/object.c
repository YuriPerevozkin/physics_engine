#include "physics.h"
#include "math/vec2.h"
#include "object.h"

object_t
create_particle(vec2_t position, real inverse_mass) {
    return (object_t) {
        .type = PARTICLE,
        .shape.particle = {
            .position = position,
        },
        .velocity = zero_vec,
        .acceleration = zero_vec,
        .force_accum = zero_vec,
        .inverse_mass = inverse_mass,
        .apply_physics = &apply_physics_particle,
    };
}

object_t
create_circle(vec2_t center, real radius) {
    return (object_t) {
        .type = CIRCLE,
        .shape.circle = {
            .center = center,
            .radius = radius,
        },
    };
}

object_t
create_rectangle(vec2_t start, int width, int height) {
    return (object_t) {
        .type = RECTANGLE,
        .shape.rectangle = {
            .start = start,
            .width = width,
            .height = height,
        },
    };
}

object_t
create_triangle(vec2_t a, vec2_t b, vec2_t c) {
    return (object_t) {
        .type = TRIANGLE,
        .shape.triangle = {
            .a = a,
            .b = b,
            .c = c,
        },
    };
}
