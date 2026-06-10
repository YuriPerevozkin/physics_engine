#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "world_edit.h"

static const size_t DEFAULT_CAP = 5;

world_edit_t
init_world_edit() {
    return (world_edit_t) {
        .variables = malloc(DEFAULT_CAP * sizeof(variable_t)),
        .variables_n = 0,
        .cap = DEFAULT_CAP,
    };
}

void
add_variable(world_edit_t* world_edit, Rectangle rect, const char* placeholder, editor_f editor, get_text_f get_text) {
    variable_t variable = {
        .text_rect = rect,
        .text_color = WHITE,
        .editor = editor,
        .get_text = get_text
    };
    snprintf(variable.input, sizeof(placeholder), "%s", placeholder);

    if (world_edit->variables_n == world_edit->cap) {
        world_edit->cap *= 2;
    }
    world_edit->variables[world_edit->variables_n] = variable;
    world_edit->variables_n += 1;
}
