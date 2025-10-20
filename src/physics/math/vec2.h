#include "precision.h"

typedef struct vec2 {
    real x;
    real y;
} vec2_t;

real vec_length(vec2_t vec);
vec2_t vec_plus_vec(vec2_t vec1, vec2_t vec2);
vec2_t vec_minus_vec(vec2_t vec1, vec2_t vec2);
vec2_t vec_mult_by_number(vec2_t vec, real n);
real get_scalar_product(vec2_t vec1, vec2_t vec2);
real get_cross_product(vec2_t vec1, vec2_t vec2);
vec2_t get_comp_product(vec2_t vec1, vec2_t vec2);
