#ifndef FLIPPER
#define FLIPPER
#include <math.h>
#include "vector.h"
struct flipper{
    struct vector start;
    struct vector end;
    double sr;
    double er;
    double omega;
};

void initFlipper(struct flipper *, struct vector, struct vector, double , double);
#endif