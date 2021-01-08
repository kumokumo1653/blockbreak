#ifndef LINE_H
#define LINE_H
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "ball.h"
#include "corner.h"
struct ball;
struct line{
    struct vector start;
    struct vector end;
    double e;
};

struct line line(struct vector, struct vector, double);
int lineCollision(struct line, struct ball, struct vector*);
#endif