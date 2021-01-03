#include "ball.h"
void initBall(struct ball* temp, double r, struct vector p){
    temp -> p = p;
    temp -> prevP = p;
    temp -> r = r;
    temp -> v = zero;
    temp -> a = zero;
    
}

void changeVelocity(struct ball* ball, double time){
    ball -> v = add(ball -> v, mult(ball -> a, time));
}

void changePosition(struct ball* ball, double time){
    ball -> prevP = ball -> p;
    ball -> p = add(ball -> p, mult(ball -> v, time));
}