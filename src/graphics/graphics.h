#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <raylib.h>
#include "../physics/physics.h"

/* src/graphics/object.c */
void draw_circles(world_t world, Texture2D texture);
Texture2D CreateCircleTexture(int size, Color color);

#endif // GRAPHICS_H
