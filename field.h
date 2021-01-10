#ifndef FIELD_H
#define FIELD_H
#define WALL 4
#define BLOCK 15
#define ITEM 4
#define EFFECT 20
#include <GL/glut.h>
#include <GL/glpng.h>
#include "line.h"
#include "vector.h"
#include "block.h"
#include "item.h"
struct block;
struct field{
    double width;
    double height;
    struct line wall[WALL];
    struct block blocks[BLOCK];
    struct item items[ITEM];
};

void initField(struct field*, double, double, GLuint[], GLuint[]);
#endif