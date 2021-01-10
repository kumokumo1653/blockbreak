#include "block.h"

struct block block(int exist, int isBreak, int times, struct vector center, double w, double h, double angle, double e, int score,  GLuint image){
    struct block temp;
    temp.isExist = exist;
    temp.isBreak = isBreak;
    temp.untilBreak = times;
    temp.center = center;
    temp.width = w;
    temp.height = h;
    temp.angle = angle;
    temp.e = e;
    temp.score = score;
    temp.image = image;
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

//あたったどうかを返す
int blockCollision(struct block* block, struct ball* ball, int* score){
    int i;
    int index;
    struct vector p;
    struct vector temp = ball->p;
    int flag = 0;
    if(block->isExist){
        for(i = 0; i < 4; i++){
            if(lineCollision(block->side[i],*ball, &p)){
                flag = 1;
                if(mag(sub(temp, ball->prevP)) > mag(sub(p, ball->prevP))){
                    index = i;
                    temp = p;
                }
            }
        }
        if(flag){
            //printf("%lf,%lf\n", ball->prevP.x, ball->prevP.y);
            //printf("%lf,%lf\n", ball->p.x, ball->p.y);
            lineReflection(ball, block->side[index], temp);
            //ブロック破壊の処理
            if(block->isBreak){
                block->untilBreak--;
                if(block->untilBreak <= 0){
                    //破壊
                    block->isExist = 0;
                    *score += block->score;
                    return 1;
                }
            }
        }
        return 0;
    }else{
        return 0;
    }
}
