#ifndef LINE
#define LINE
#include "vector.h"
#include "ball.h"
#include "corner.h"
struct line{
    int isExist;
    struct vector start;
    struct vector end;
    double e;
};

struct line line(int, struct vector, struct vector, double);
int lineCollision(struct line, struct ball);
#endif