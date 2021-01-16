#ifndef ITEM_H
#define ITEM_H
#include "vector.h"
#include "paddle.h"
#include <GL/glut.h>
enum type{
    ballSpeedUp,
    paddleSpeedDown,
    paddleShort,
    paddleLong,
    ITEM
};
struct item{
    int isExist;
    struct vector p;
    struct vector prevP;
    double v;
    double r;
    enum type type;
    double effectTime;
    GLuint image;
};
struct item item(enum type, double, GLuint);
int itemCollision(struct item, struct paddle);
void itemChangePosition(struct item*, double);
#endif