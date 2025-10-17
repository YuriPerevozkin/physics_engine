#include "raylib.h"
#include "graphics.h"

static const int screenWidth = 800;
static const int screenHeight = 450;

void
draw_app(world_t world)
{
    InitWindow(screenWidth, screenHeight, "Physics Engine");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            for (int i = 0; i < world.object_count; i++) {
                draw_object(world.objects[i]);
            }
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}
