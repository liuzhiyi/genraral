#include "../inlcudes/algorithm.h"
/*
*已知四个点（x1, y1）,(x1, y2),(x2, y1), (x2, y2)的值
*要求点(x, y)点值，先求点(x, y1),再求点(x, y2)
*最后求出(x, y)的值。如果选择四个点(0, 0), (0, 1), (1, 0), (1, 1)
*求得公式f(x, 0) = (1-x)/1*f(0, 0) + x/1*f(1, 0)
*        f(x, 1) = (1-x)/1*f(0, 1) + x/1*f(1, 1)
*        f(x, y) = (1-y)/1*f(x, 0) + y/1*f(x, 1) = (1-x)(1-y)f(0, 0) + (1-y)xf(1, 0) + y(1-x)f(0, 1) + yxf(1, 1)
**/
void g_bilinear_interp(float64_t x, float64_t y, g_bilinear_t *b, ...) {
    va_list     args;
    float64_t   *r;

    va_start(y, args);
    g_find_linear(b, x, y);
    while(r = var_arg(args, *float64_t) != NULL) {
        *r = b->b1*f(b->low.x, b->low.y) + b->b2*f(b->high.x, b->low.y) +
            b->b3*f(b->low.x, b->high.y) + b->b3*f(b->high.x, b->high.y);
    }
    va_end(args);
}

static void g_find_linear(g_bilinear_t *b, float64_t x, float64_t y) {
    float64_t i, j;

    i = x - b->low.x;
    j = y - b->low.y;
    b->b1 = (1-i)*(1-j);
    b->b2 = (1-j)*i;
    b->b3 = j*(1-i);
    b->b4 = i*j;
}
