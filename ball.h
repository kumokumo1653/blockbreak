#ifndef BALL_H
#define BALL_H
#include <float.h>
#include <stdlib.h>
#include "vector.h"
#include "line.h"
#include "corner.h"

struct line;
struct corner;
struct ball{
    double r;
    struct vector p;
    struct vector prevP;
    struct vector v;
    struct vector a;
};

void initBall(struct ball*, double, struct vector);
void ballChangeVelocity(struct ball*, double);
void ballChangePosition(struct ball*, double);
void lineReflection(struct ball*, struct line , struct vector );
void cornerReflection(struct ball*, struct corner , struct vector );
int  isCircumference(struct vector , struct vector, double);

#endif