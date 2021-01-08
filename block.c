#include "block.h"

struct block block(int exist, int isBreak, int times, struct vector center, double w, double h, double angle, double e){
    struct block temp;
    temp.isExist = exist;
    temp.isBreak = isBreak;
    temp.untilBreak = times;
    temp.center = center;
    temp.width = w;
    temp.height = h;
    temp.angle = angle;
    temp.e = e;
    //辺の指定
    struct vector a = add(center, rotate(vector(w / 2, h / 2), angle));
    struct vector b = add(center, rotate(vector(-w / 2, h / 2), angle));
    struct vector c = add(center, rotate(vector(-w / 2, -h / 2), angle));
    struct vector d = add(center, rotate(vector(w / 2, -h / 2), angle));
    temp.side[0] = line(a, b, e);
    temp.side[1] = line(b, c, e);
    temp.side[2] = line(c, d, e);
    temp.side[3] = line(d, a, e);

    return temp;
}

void blockCollision(struct block* block, struct ball* ball){
    int i;
    int index;
    struct vector p;
    struct vector temp = ball->p;
    int flag = 0;
    if(block->isExist){
        for(i = 0; i < 4; i++){
            if(lineCollision(block->side[i],*ball, &p)){
                flag = 1;
                printf("%lf,%lf\n", p.x, p.y);
                if(mag(sub(temp, ball->prevP)) > mag(sub(p, ball->prevP))){
                    index = i;
                    temp = p;
                }
                printf("len:%lf,%lf\n", mag(sub(temp, ball->prevP)), mag(sub(p, ball->prevP)));
            }
        }
        if(flag){
            //printf("%lf,%lf\n", ball->prevP.x, ball->prevP.y);
            //printf("%lf,%lf\n", ball->p.x, ball->p.y);
            printf("%d:%lf,%lf\n", index, temp.x, temp.y);
            lineReflection(ball, block->side[index], temp);
            printf("v:%lf,%lf\n", ball->v.x, ball->v.y);
            //ブロック破壊の処理
            if(block->isBreak){
                block->untilBreak--;
                if(block->untilBreak <= 0){
                    //破壊
                    block->isExist = 0;
                }
            }
        }
    }
}