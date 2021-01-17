#include "item.h"
struct item item(enum type type, double time, GLuint image){
    struct item temp;
    temp.isExist = 0;
    temp.type = type;
    temp.effectTime = time;
    temp.image = image;
    return temp;
}

int itemCollision(struct item item, struct paddle paddle){
    struct vector paddleStart = add(paddle.p, vector(paddle.width / 2, PADDLE_HEIGHT / 2 + item.r));
    struct vector paddleEnd = add(paddle.p, vector(-paddle.width / 2, PADDLE_HEIGHT / 2 + item.r));
    struct vector l = sub(paddleEnd, paddleStart);
    struct vector movement = sub(item.p, item.prevP);
    //線分が交差していれば衝突
    if(outer(l, sub(item.prevP, paddleStart)) * outer(l, sub(item.p, paddleStart)) < 0 && outer(movement, sub(paddleStart, item.p)) * outer(movement, sub(paddleEnd, item.p)) < 0)
        return 1;
    else 
        return 0;
}
void itemChangePosition(struct item* item, double time){
    item->prevP = item->p;
    item->p = add(item->p, mult(vector(0,item->v), time));
}