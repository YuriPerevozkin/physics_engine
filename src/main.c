#include <stddef.h>
#include <raylib.h>
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

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("g: %.3f", g), 10, 10, 20, WHITE);
            for (int i = 0; i < world.objects_n; i++) {
                apply_physics(&world.objects[i]);
                draw_object(world.objects[i]);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                real x = GetMouseX();
                real y = GetMouseY();
                add_object(&world, create_particle((vec2_t) {x, y}, 1.0f/10));
            }
        EndDrawing();
    }

    CloseWindow();
}
