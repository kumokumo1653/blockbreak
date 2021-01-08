#ifndef FIELD_H
#define FIELD_H
#define WALL 4
#define BLOCK 1
#include "line.h"
#include "vector.h"
#include "block.h"
struct block;
struct field{
    double width;
    double height;
    struct line wall[WALL];
    struct block blocks[BLOCK];
};

void initField(struct field*, double, double);
#endif