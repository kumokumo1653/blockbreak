#ifndef PADDLE_H
#define PADDLE_H
#include "vector.h"
#include "line.h"
#define H 10
struct paddle{
    struct vector p;
    struct vector v;
    double e;
    double width;
    struct line side[4];
};

void initPaddle(struct paddle*, struct vector, double, double);
#endif