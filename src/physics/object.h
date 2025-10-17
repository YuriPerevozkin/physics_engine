#include "math/vec2.h"

typedef enum {
    CIRCLE,
    RECTANGLE,
    TRIANGLE,
} object_type_e;

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

typedef struct object {
    object_type_e type;
    union {
        circle_t circle;
        rectangle_t rectangle;
        triangle_t triangle;
    } shape;
} object_t;

object_t create_circle(vec2_t center, real radius);
object_t create_rectangle(vec2_t start, int height, int width);
object_t create_triangle(vec2_t a, vec2_t b, vec2_t c);
