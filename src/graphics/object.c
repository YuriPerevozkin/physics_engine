#include <raylib.h>
#include "../physics/object.h"

void
draw_object(object_t object) {
    switch (object.type) {
        case CIRCLE: {
            DrawCircle(object.shape.circle.center.x, object.shape.circle.center.y, object.shape.circle.radius, RED);
            break;
        };
        case RECTANGLE: {
            DrawRectangle(object.shape.rectangle.start.x, object.shape.rectangle.start.y, 
                          object.shape.rectangle.width, object.shape.rectangle.height, GREEN);
            break;
        };
        case TRIANGLE: {
            DrawTriangle((Vector2) {object.shape.triangle.a.x, object.shape.triangle.a.y}, 
                         (Vector2) {object.shape.triangle.b.x, object.shape.triangle.b.y}, 
                         (Vector2) {object.shape.triangle.c.x, object.shape.triangle.c.y}, BLUE);
            break;
        };
    }
}
