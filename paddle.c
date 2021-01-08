#include "paddle.h"
void initPaddle(struct paddle* paddle, struct vector p, double w, double e){
    paddle->p = p;
    paddle->prevP = p;
    paddle->e = e;
    paddle->width = w;

    struct vector a = add(p, vector(w / 2, H / 2));
    struct vector b = add(p, vector(-w / 2, H / 2));
    paddle->side = line(a, b, e);
}


void paddleChangePosition(struct paddle* paddle, struct vector p, double width){
    paddle->prevP.x = paddle->p.x;
    paddle->p.x = p.x;

    if(p.x + paddle->width / 2 > width)
        paddle->p.x = width - paddle->width / 2;
    
    if(p.x - paddle->width / 2 < 0)
        paddle->p.x = paddle->width / 2;
    
    struct vector a = add(paddle->p, vector( paddle->width / 2, H));
    struct vector b = add(paddle->p, vector(-paddle->width / 2, H));
    paddle->side = line(a, b, paddle->e);
}

void paddleCollision(struct paddle paddle, struct ball* ball){
    int i;
    struct vector p;
    if(lineCollision(paddle.side,*ball, &p)){
        lineReflection(ball, paddle.side, p);
    }
}