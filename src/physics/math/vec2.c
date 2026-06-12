#include "vec2.h"
#include "precision.h"

vec2_t zero_vec = {0.0f, 0.0f};

real
vec_length(vec2_t vec) {
    return real_sqrt(vec.x * vec.x + vec.y * vec.y);    
}

vec2_t
normilize(vec2_t vec) {
    real length = vec_length(vec);
    return (vec2_t){
        .x = vec.x / length,
        .y = vec.y / length,
    };
}

vec2_t
vec_plus_vec(vec2_t vec1, vec2_t vec2) {
    return (vec2_t) {
        .x = vec1.x + vec2.x,
        .y = vec1.y + vec2.y,
    };
}

vec2_t
vec_minus_vec(vec2_t vec1, vec2_t vec2) {
    return (vec2_t) {
        .x = vec1.x - vec2.x,
        .y = vec1.y - vec2.y,
    };
}

vec2_t
scaled_vec(vec2_t vec, real n) {
    return (vec2_t) {
        .x = vec.x * n,
        .y = vec.y * n,
    };
}

real
get_scalar_product(vec2_t vec1, vec2_t vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

real
get_cross_product(vec2_t vec1, vec2_t vec2) {
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

vec2_t
get_comp_product(vec2_t vec1,vec2_t vec2) {
    return(vec2_t) {
        .x = vec1.x * vec2.x,
        .y = vec1.y * vec2.y,
    };
}
