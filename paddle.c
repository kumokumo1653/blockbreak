#include "paddle.h"
void initPaddle(struct paddle* paddle, struct vector p, double w, double e){
    paddle->p = p;
    paddle->prevP = p;
    paddle->v = 0;
    paddle->e = e;
    paddle->width = w;

    struct vector a = add(p, vector(w / 2, PADDLE_HEIGHT / 2));
    struct vector b = add(p, vector(-w / 2, PADDLE_HEIGHT / 2));
    paddle->side = line(a, b, e);
}


void paddleChangePosition(struct paddle* paddle, struct vector p,double time,  double width){
    //速度決定
    struct vector temp = sub(p, paddle->p);
    temp.y = 0;
    struct vector v = mult(unit(temp), paddle->v); 
    if(!isZero(v)){
        paddle->prevP = paddle->p;
        paddle->p = add(paddle->p, mult(v, time));
    }

    //通り過ぎたら修正
    if(( paddle->prevP.x < p.x && paddle->p.x > p.x) || (paddle->prevP.x > p.x && paddle->p.x < p.x)){
        paddle->prevP = paddle->p;
        paddle->p.x = p.x;
    }

    if(paddle->p.x + paddle->width / 2 > width){
        paddle->p.x = width - paddle->width / 2;
        paddle->prevP.x = paddle->p.x;
    }
    
    if(paddle->p.x - paddle->width / 2 < 0){
        paddle->p.x = paddle->width / 2;
        paddle->prevP.x = paddle->p.x;
    }
    struct vector a = add(paddle->p, vector( paddle->width / 2, PADDLE_HEIGHT / 2));
    struct vector b = add(paddle->p, vector(-paddle->width / 2, PADDLE_HEIGHT / 2));
    paddle->side = line(a, b, paddle->e);
}

void paddleCollision(struct paddle paddle, struct ball* ball){
    struct vector p;
    if(lineCollision(paddle.side,*ball, &p)){
        lineReflection(ball, paddle.side, p);
    }
}