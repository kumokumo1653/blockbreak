#ifndef BLOCK_H
#define BLOCK_H
#include "vector.h"
#include "line.h"
#include "ball.h"

struct block{
    int isExist;
    int isBreak;
    int untilBreak;
    struct vector center;
    double width;
    double height;
    double angle;
    double e;
    struct line side[4];

};

struct block block(int, int, int, struct vector, double, double, double, double);
void blockCollision(struct block*, struct ball*);
#endif