#ifndef SHAPE_H
#define SHAPE_H
#include "vector.h"
#include <math.h>
#include <GL/glut.h>
void DrawCircle(struct vector, int, GLenum, double, double, float, GLubyte []);
void DrawEllipse(struct vector, int, int, GLenum ,double, double, float ,GLubyte []);

#endif
