#include <stdlib.h>
#include "graphics/window.h"
#include "physics/physics.h"

typedef struct {
    object_t* array;
    size_t used;
    size_t size;
} object_array;

object_array
init_object_array() {
    object_t* array = malloc(sizeof(object_t));
    return (object_array) {array, 0, 1};
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
    add_object(&objects, (object_t) {});

    world_t world = init_world(objects.array);

    draw_app();
}
