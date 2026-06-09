#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"
#include "graphics/graphics.h"
#include "physics/math/vec2.h"
#include "physics/object.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;

int
main() {
    world_t world = init_world();

    // add_object(&world, create_circle((vec2_t) {400.0f, 200.0f}, 20.0f));
    // add_object(&world, create_triangle((vec2_t) {200.0f, 100.0f}, 
    //                                      (vec2_t) {130.0f, 170.0f},
    //                                      (vec2_t) {270.0f, 170.0f}));
    // add_object(&world, create_rectangle((vec2_t) {500.0f, 150.0f}, 40, 40));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine");

    SetTargetFPS(FPS);

    Rectangle g_text_rec = {10, 10, 100, 20};
    Color g_text_color = WHITE;
    static int mouse_on_g_text = 0;
    static int show_input = 0;
    static char g_input[64] = "9.807";

    while (!WindowShouldClose())
    {
        Vector2 mouse_pos = GetMousePosition();
        if (CheckCollisionPointRec(mouse_pos, g_text_rec)) {
            mouse_on_g_text = 1;
            g_text_color = GREEN;
        } else {
            mouse_on_g_text = 0;
            g_text_color = WHITE;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!show_input) {
                if (mouse_on_g_text) {
                    show_input = 1;
                }
                else {
                    add_object(&world, create_particle((vec2_t) {mouse_pos.x, mouse_pos.y}, 1.0f/1));
                }
            }
        }

        if (show_input) {
            int result = GuiTextInputBox((Rectangle) {50, 50, 200, 120},
                    "World Edit", "Change g:", "save;cancel",
                    g_input, sizeof(g_input), NULL);

            if (result >= 1) {
                show_input = 0;
                g = atof(g_input);
            }
        }
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("g = %.3f", g), 10, 10, 20, g_text_color);

            for (int i = 0; i < world.objects_n; i++) {
                apply_physics(&world.objects[i]);
                draw_object(world.objects[i]);
            }
        EndDrawing();
    }
    CloseWindow();
}
