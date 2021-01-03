#ifndef VECTOR
#define VECTOR

#include <math.h>
#include <float.h>
struct vector{
    double x;
    double y;
};

struct vector vector(double, double);
struct vector add(struct vector, struct vector);
struct vector sub(struct vector, struct vector);
struct vector mult(struct vector, double);
struct vector divi(struct vector, double);
double mag(struct vector);
struct vector unit(struct vector);
struct vector normalP(struct vector);
struct vector normalN(struct vector);
struct vector inverse(struct vector);
double angle(struct vector);
double angle2(struct vector, struct vector);
double inner(struct vector, struct vector);
double outer(struct vector, struct vector);

extern const struct vector zero;
extern const struct vector unitX;

#endif