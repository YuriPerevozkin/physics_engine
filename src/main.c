#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"
#include "physics/physics.h"
#include "physics/object.h"
#include "physics/math/vec2.h"
#include "graphics/graphics.h"
#include "graphics/world_edit.h"


static const int SCREEN_WIDTH = 1400;
static const int SCREEN_HEIGHT = 850;

world_t world = {
    .circles_n = 0,
    .g = INITIAL_G,
    .damping = INITIAL_DAMPING,
};

static int show_input = 0;
static int shown_input_index = -1;

void g_editor(variable_t* variable) {
    int result = GuiTextInputBox((Rectangle) {50, 50, 200, 120},
            "World Edit", "Change g:", "save;cancel",
            variable->input, sizeof(variable->input), NULL);

    if (result >= 1) {
        show_input = 0;
        shown_input_index = -1;
        world.g = atof(variable->input);
    }
}

void damping_editor(variable_t* variable) {
    int result = GuiTextInputBox((Rectangle) {50, 50, 200, 120},
            "World Edit", "Change damping:", "save;cancel",
            variable->input, sizeof(variable->input), NULL);

    if (result >= 1) {
        show_input = 0;
        shown_input_index = -1;
        world.damping = atof(variable->input);
    }
}
const char* g_get_text() {
    return TextFormat("g = %.3f", world.g);
}

const char* damping_get_text() {
    return TextFormat("damping = %.3f", world.damping);
}

int
main() {
    srand(time(NULL));

    world_edit_t world_edit = init_world_edit();
    add_variable(&world_edit, (Rectangle) {10, 40, 100, 20}, "9.807", &g_editor, &g_get_text);
    add_variable(&world_edit, (Rectangle) {10, 70, 100, 20}, "0.997", &damping_editor, &damping_get_text);

    add_circle(&world, (vec2_t){500.0f, 400.0f}, 1.0f/100, 1);
    world.transforms[0].velocity.y = -60.0f;
    world.transforms[0].acceleration.y = -20.0f;
    int firework_life = 100;
    int firework_alive = 1;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine");

    SetTargetFPS(FPS);

    static int creating_object = 0;
    static vec2_t mouse_start;
    static vec2_t mouse_end;
    Texture2D circle_text = CreateCircleTexture(4, RED);

    while (!WindowShouldClose())
    {
        if (firework_alive) {
            firework_life--;
            if (firework_life <= 0) {
                for (int i = 0; i < 900; i++) {
                    add_circle(&world, world.transforms[0].position, 1.0f/10.0f, 1);
                    real random_angle = ((real) rand() / RAND_MAX) * 2.0f * PI;
                    real random_speed = ((real) rand() / RAND_MAX) * 100.0f;
                    world.transforms[world.circles_n-1].velocity.x = cosf(random_angle) * random_speed;
                    world.transforms[world.circles_n-1].velocity.y = sinf(random_angle) * random_speed;
                }
                remove_circle(&world, 0);
                firework_alive = 0;
            }
        }

        Vector2 mouse_pos = GetMousePosition();

        for (int i = 0; i < world_edit.variables_n; i++) {
            if (CheckCollisionPointRec(mouse_pos, world_edit.variables[i].text_rect)) {
                world_edit.variables[i].text_color = BLUE;
                if (!show_input) {
                    shown_input_index = i;
                    break;
                }
            }
            else {
                if (!show_input) {
                    shown_input_index = -1;
                }
                world_edit.variables[i].text_color = WHITE;
            }
        }

        if (!creating_object && !show_input && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (shown_input_index != -1) {
                show_input = 1;
            } else {
                creating_object = 1;
                mouse_start = (vec2_t){mouse_pos.x, mouse_pos.y};
            }
        }
        if (creating_object && IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
            mouse_end = (vec2_t){mouse_pos.x, mouse_pos.y};
            vec2_t drag_vector = vec_minus_vec(mouse_end, mouse_start);
            add_circle(&world, (vec2_t) {mouse_start.x, mouse_start.y}, 1, 1.0f/1);
            world.transforms[world.circles_n - 1].velocity = drag_vector;
            creating_object = 0;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            update_circles(&world);
            draw_circles(world, circle_text);

            DrawText("World Edit:", 10, 10, 20, WHITE);
            for (int i = 0; i < world_edit.variables_n; i++) {
                DrawText(world_edit.variables[i].get_text(), world_edit.variables[i].text_rect.x, world_edit.variables[i].text_rect.y, 20, world_edit.variables[i].text_color);
            }

            DrawFPS(500, 10);
            DrawText(TextFormat("Objects: %d", world.circles_n), 500, 40, 20, WHITE);

            if (show_input) {
                world_edit.variables[shown_input_index].editor(&world_edit.variables[shown_input_index]);
            }

        EndDrawing();
    }
    CloseWindow();
}
