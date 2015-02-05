#include "../inlcudes/algorithm.h"
/*
*已知四个点（x1, y1）,(x1, y2),(x2, y1), (x2, y2)的值
*要求点(x, y)点值，先求点(x, y1),再求点(x, y2)
*最后求出(x, y)的值。如果选择四个点(0, 0), (0, 1), (1, 0), (1, 1)
*求得公式f(x, 0) = (1-x)/1*f(0, 0) + x/1*f(1, 0)
*        f(x, 1) = (1-x)/1*f(0, 1) + x/1*f(1, 1)
*        f(x, y) = (1-y)/1*f(x, 0) + y/1*f(x, 1) = (1-x)(1-y)f(0, 0) + (1-y)xf(1, 0) + y(1-x)f(0, 1) + yxf(1, 1)
**/
void g_bilinear_interp(float64_t x, float64_t y, ...) {
    va_list     args;

    va_start(y, args);
    find
}

static g_bilinear_t *g_find_linear() {

}
