#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"
#include "physics/object.h"
#include "physics/physics.h"
#include "physics/math/vec2.h"
#include "graphics/graphics.h"
#include "graphics/world_edit.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;

static int show_input = 0;
static int shown_input_index = -1;

void g_editor(variable_t* variable) {
    int result = GuiTextInputBox((Rectangle) {50, 50, 200, 120},
            "World Edit", "Change g:", "save;cancel",
            variable->input, sizeof(variable->input), NULL);

    if (result >= 1) {
        show_input = 0;
        shown_input_index = -1;
        g = atof(variable->input);
    }
}

void damping_editor(variable_t* variable) {
    int result = GuiTextInputBox((Rectangle) {50, 50, 200, 120},
            "World Edit", "Change damping:", "save;cancel",
            variable->input, sizeof(variable->input), NULL);

    if (result >= 1) {
        show_input = 0;
        shown_input_index = -1;
        damping = atof(variable->input);
    }
}
const char* g_get_text() {
    return TextFormat("g = %.3f", g);
}

const char* damping_get_text() {
    return TextFormat("damping = %.3f", damping);
}

int
main() {
    srand(time(NULL));

    world_t world = init_world();

    world_edit_t world_edit = init_world_edit();
    add_variable(&world_edit, (Rectangle) {10, 10, 100, 20}, "9.807", &g_editor, &g_get_text);
    add_variable(&world_edit, (Rectangle) {10, 40, 100, 20}, "0.997", &damping_editor, &damping_get_text);

    add_object(&world, create_particle((vec2_t) {500.0f, 500.0f}, 1.0f/100));
    world.objects[world.objects_n-1].velocity.y = -60.0f;
    world.objects[world.objects_n-1].acceleration.y = -20.0f;
    int firework_life = 200;
    int firework_alive = 1;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine");

    SetTargetFPS(FPS);

    static int creating_object = 0;
    static vec2_t mouse_start;
    static vec2_t mouse_end;

    while (!WindowShouldClose())
    {
        if (firework_alive) {
            firework_life--;
            if (firework_life <= 0) {
                for (int i = 0; i < 500; i++) {
                    add_object(&world, create_particle(world.objects[0].shape.particle.position, 1.0f/10.0f));
                    real random_angle = ((real) rand() / RAND_MAX) * 2.0f * PI;
                    real random_speed = ((real) rand() / RAND_MAX) * 100.0f;
                    world.objects[world.objects_n-1].velocity.x = cosf(random_angle) * random_speed;
                    world.objects[world.objects_n-1].velocity.y = sinf(random_angle) * random_speed;
                }
                remove_object(&world, 0);
                firework_alive = 0;
            }
        }

        Vector2 mouse_pos = GetMousePosition();

        for (int i = 0; i < world_edit.variables_n; i++) {
            if (CheckCollisionPointRec(mouse_pos, world_edit.variables[i].text_rect)) {
                world_edit.variables[i].text_color = GREEN;
                if (!show_input) {
                    shown_input_index = i;
                    break;
                }
            }
            else {
                world_edit.variables[i].text_color = WHITE;
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (!creating_object) {
                if (!show_input) {
                    if (shown_input_index != -1) {
                        show_input = 1;
                    } else {
                        creating_object = 1;
                        mouse_start = (vec2_t){mouse_pos.x, mouse_pos.y};
                    }
                }
            }
        }
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
            if (creating_object) {
                mouse_end = (vec2_t){mouse_pos.x, mouse_pos.y};
                vec2_t drag_vector = vec_minus_vec(mouse_end, mouse_start);
                add_object(&world, create_particle((vec2_t) {mouse_start.x, mouse_start.y}, 1.0f/1));
                world.objects[world.objects_n-1].velocity = drag_vector;
                creating_object = 0;
            }
        }

        if (show_input) {
            world_edit.variables[shown_input_index].editor(&world_edit.variables[shown_input_index]);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < world_edit.variables_n; i++) {
                DrawText(world_edit.variables[i].get_text(), world_edit.variables[i].text_rect.x, world_edit.variables[i].text_rect.y, 20, world_edit.variables[i].text_color);
            }

            for (int i = 0; i < world.objects_n; i++) {
                apply_physics(&world.objects[i]);
                draw_object(world.objects[i]);
            }
        EndDrawing();
    }
    CloseWindow();
}
