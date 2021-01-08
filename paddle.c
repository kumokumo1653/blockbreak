#include "paddle.h"
void initPaddle(struct paddle* paddle, struct vector p, double w, double e){
    paddle->p = p;
    paddle->v = zero;
    paddle->e = e;
    paddle->width = w;

    struct vector a = add(center, rotate(vector(w / 2, h / 2), angle));
    struct vector b = add(center, rotate(vector(-w / 2, h / 2), angle));
    struct vector c = add(center, rotate(vector(-w / 2, -h / 2), angle));
    struct vector d = add(center, rotate(vector(w / 2, -h / 2), angle));
    temp.side[0] = line(a, b, e);
    temp.side[1] = line(b, c, e);
    temp.side[2] = line(c, d, e);
    temp.side[3] = line(d, a, e);
}