#ifndef WORLD_EDIT_H
#define WORLD_EDIT_H


#include <raylib.h>
#include <stddef.h>

typedef struct variable variable_t;
typedef void (*editor_f)(variable_t*);
typedef const char* (*get_text_f)(void);

struct variable {
    Rectangle text_rect;
    Color text_color;
    char input[64];
    editor_f editor;
    get_text_f get_text;
};

typedef struct world_edit {
    variable_t* variables;
    size_t variables_n;
    size_t cap;
} world_edit_t;

/* src/graphics/world_edit.c */
world_edit_t init_world_edit();
void add_variable(world_edit_t* world_edit, Rectangle rect, const char* placeholder, editor_f editor, get_text_f get_text);

#endif // WORLD_EDIT_H
