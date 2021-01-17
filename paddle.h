#ifndef PADDLE_H
#define PADDLE_H
#include "vector.h"
#include "line.h"
#define PADDLE_HEIGHT 10
struct paddle{
    struct vector p;
    double v;
    struct vector prevP;
    double e;
    double width;
    struct line side;
};

void initPaddle(struct paddle*, struct vector, double, double);
void paddleChangePosition(struct paddle*, struct vector, double, double);
void paddleCollision(struct paddle, struct ball*);
#endif