#ifndef CORNER
#define CORNER
#include "vector.h"
struct corner{
    int isExist;
    int isOut;
    struct vector center;
    double r;
    double startAngle;
    double endAngle;
    double e;
};

struct corner corner(int, int, struct vector, double, double, double, double);
#endif