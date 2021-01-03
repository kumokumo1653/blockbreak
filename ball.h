#ifndef BALL
#define BALL
#include "vector.h"
struct ball{
    double r;
    struct vector p;
    struct vector prevP;
    struct vector v;
    struct vector a;
};

void initBall(struct ball*, double, struct vector);
void changeVelocity(struct ball*, double);
void changePosition(struct ball*, double);
#endif