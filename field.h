#ifndef FIELD
#define FIELD
#define WALL 1
#define C 1
#include "line.h"
#include "vector.h"
struct field{
    double width;
    double height;
    struct line wall[WALL];
    struct corner circle[C];
};

void initField(struct field*, double, double);
#endif