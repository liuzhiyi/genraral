#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_
#include "../includes/os.h"

typedef void (*g_bilinear_value_pt)(float64_t x, float64_t y, ...);

typedef struct g_bilinear_point_s {
    float64_t x;
    float64_t y;
} g_bilinear_point_t;

typedef struct g_bilinear_s {
    g_bilinear_point_t  low;
    g_bilinear_point_t  hight;
    float64_t           b1;
    float64_t           b2;
    float64_t           b3;
    float64_t           b4;
} g_bilinear_t;

#endif
