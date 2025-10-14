#include "raylib.h"

static const int screenWidth = 800;
static const int screenHeight = 450;

void draw_app()
{
    InitWindow(screenWidth, screenHeight, "Physics Engine");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawCircle(100, 200, 20, RED);
            DrawRectangle(200, 200, 100, 50, GREEN);
            DrawTriangle((Vector2) {screenWidth/4.0f *2.0f, 80.0f}, 
                         (Vector2) {screenWidth/4.0f *2.0f - 60.0f, 150.0f}, 
                         (Vector2) {screenWidth/4.0f *2.0f + 60.0f, 150.0f}, BLUE);
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}
