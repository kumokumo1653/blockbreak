#ifndef FIELD
#define FIELD
#define WALL 1
#include "line.h"
#include "vector.h"
struct field{
    double width;
    double height;
    struct line wall[WALL];
};

void initField(struct field*, double, double);
#endif