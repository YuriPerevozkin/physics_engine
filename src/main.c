#include <stddef.h>
#include <stdlib.h>
#include "graphics/graphics.h"

typedef struct {
    object_t* array;
    size_t used;
    size_t size;
} object_array;

object_array
init_object_array() {
    size_t default_size = 5;
    object_t* array = malloc(sizeof(object_t) * default_size);
    return (object_array) {array, 0, default_size};
}

void
add_object(object_array* array, object_t object) {
    if (array->used == array->size) {
        array->size *= 2;
        array->array = realloc(array->array, array->size * sizeof(object_t));
    }
    array->array[array->used++] = object;
}

int
main() {
    object_array objects = init_object_array();
    add_object(&objects, create_circle((vec2_t) {400.0f, 200.0f}, 20.0f));
    add_object(&objects, create_triangle((vec2_t) {200.0f, 100.0f}, 
                                         (vec2_t) {130.0f, 170.0f},
                                         (vec2_t) {270.0f, 170.0f}));
    add_object(&objects, create_rectangle((vec2_t) {500.0f, 150.0f}, 40, 40));

    world_t world = init_world(objects.array, objects.used);

    draw_app(world);
}
