#ifndef OBJECT_H
#define OBJECT_H


#include "math/vec2.h"

typedef struct object object_t;
typedef void (*physics_strategy)(object_t*);

typedef enum {
    PARTICLE,
    CIRCLE,
    RECTANGLE,
    TRIANGLE,
} object_type_e;

typedef struct particle {
    vec2_t position;
} particle_t;

typedef struct circle {
    vec2_t center;
    real radius;
} circle_t;

typedef struct rectangle {
    vec2_t start;
    int width;
    int height;
} rectangle_t;

typedef struct triangle {
    vec2_t a;
    vec2_t b;
    vec2_t c;
} triangle_t;

struct object {
    object_type_e type;
    union {
        particle_t particle;
        circle_t circle;
        rectangle_t rectangle;
        triangle_t triangle;
    } shape;
    vec2_t velocity;
    vec2_t acceleration;
    vec2_t force_accum;
    real inverse_mass;
    physics_strategy apply_physics;
};

/* object.c */
object_t create_particle(vec2_t position, real inverse_mass);
object_t create_circle(vec2_t center, real radius);
object_t create_rectangle(vec2_t start, int height, int width);
object_t create_triangle(vec2_t a, vec2_t b, vec2_t c);


#endif // OBJECT_H
