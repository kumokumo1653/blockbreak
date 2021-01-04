#ifndef BALL
#define BALL
#include <float.h>
#include <stdlib.h>
#include "vector.h"
#include "line.h"

struct line;
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
void lineReflection(struct ball*, struct line , struct vector );
#endif