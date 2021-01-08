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
    struct vector p;
    if(block->isExist){
        for(i = 0; i < 4; i++){
            if(lineCollision(block->side[i],*ball, &p)){
                lineReflection(ball, block->side[i], p);
                //ブロック破壊の処理
                if(block->isBreak){
                    block->untilBreak--;
                    if(block->untilBreak <= 0){
                        //破壊
                        block->isExist = 0;
                    }
                }
                break;
            }
        }
    }
}