#ifndef OBJECT_H
#define OBJECT_H


#include "math/vec2.h"

typedef struct {
    vec2_t position;
    vec2_t velocity;
    vec2_t acceleration;
    vec2_t force_accum;
    real inverse_mass;
} transform_t;

typedef struct circle {
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


#endif // OBJECT_H
