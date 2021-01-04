#ifndef LINE
#define LINE
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "ball.h"
#include "corner.h"
struct ball;
struct line{
    int isExist;
    struct vector start;
    struct vector end;
    double e;
};

struct line line(int, struct vector, struct vector, double);
struct vector* lineCollision(struct line, struct ball);
#endif