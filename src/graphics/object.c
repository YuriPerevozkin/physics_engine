#include <raylib.h>
#include "../physics/physics.h"

Texture2D
CreateCircleTexture(int size, Color color) {
    // 1. Create an empty image
    Image img = GenImageColor(size, size, BLANK);
    
    int center = size / 2;
    int radius = size / 2 - 1; // Leave 1px padding

    // 2. Manually draw the circle onto the CPU image
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // Calculate distance from center
            float dx = x - center;
            float dy = y - center;
            
            // If inside radius, color the pixel
            if ((dx*dx + dy*dy) <= (radius*radius)) {
                ImageDrawPixel(&img, x, y, color);
            }
        }
    }

    // 3. Upload to GPU
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img); // Free CPU memory
    
    // 4. Important: Set filtering so scaling doesn't look pixelated
    SetTextureFilter(tex, TEXTURE_FILTER_BILINEAR);
    
    return tex;
}

void
draw_circles(world_t world, Texture2D texture) {
    for (int i = 0; i < world.circles_n; i++) {
        vec2_t position = world.positions[i];
        circle_t* circle = &world.circles[i];
        DrawTexture(texture, position.x, position.y, RED);
    }
}
