#ifndef CORNER
#define CORNER
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "ball.h"
#include "vector.h"
struct ball;
struct corner{
    int isExist;
    struct vector center;
    double r;
    double startAngle; // 中心を原点とした角度
    double endAngle;    //中心を原点とした角度
    double e;
};

struct corner corner(int, struct vector, double, double, double, double);
int cornerCollision(struct corner, struct ball, struct vector*);
#endif