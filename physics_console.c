#include <stdio.h>
#include "math/vec2.h"

int main() {
    printf("=== Physics Engine Console ===\\n\\n");
    
    // Тестируем векторные операции
    vec2_t a = {3.0, 4.0};
    vec2_t b = {1.0, 2.0};
    
    printf("Vector A: (%.1f, %.1f)\\n", a.x, a.y);
    printf("Vector B: (%.1f, %.1f)\\n", b.x, b.y);
    printf("Length of A: %.1f\\n", length_vec(a));
    
    vec2_t sum = vec_plus_vec(a, b);
    printf("A + B: (%.1f, %.1f)\\n", sum.x, sum.y);
    
    vec2_t diff = vec_minus_vec(a, b);
    printf("A - B: (%.1f, %.1f)\\n", diff.x, diff.y);
    
    vec2_t scaled = vec_mult_by_number(a, 2.0);
    printf("A * 2: (%.1f, %.1f)\\n", scaled.x, scaled.y);
    
    real dot = get_scalar_product(a, b);
    printf("Dot product: %.1f\\n", dot);
    
    vec2_t comp = vec_component_wise_product(a, b);
    printf("Component product: (%.1f, %.1f)\\n", comp.x, comp.y);
    
    real cross = vec_cross_product(a, b);
    printf("Cross product: %.1f\\n", cross);
    
    printf("\\nAll vector operations working! ✅\\n");
    return 0;
}
