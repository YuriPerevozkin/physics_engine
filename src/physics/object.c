#include "object.h"

object_t
create_particle(vec2_t position, real inverse_mass) {
    vec2_t velocity = {0.0f, 0.0f};
    return (object_t) {
        .type = PARTICLE,
        .shape.particle = {
            .position = position,
        },
        .velocity = velocity,
        .acceleration = velocity,
        .inverse_mass = inverse_mass,
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
