#include "vector.h"

const struct vector zero = {0, 0};
const struct vector unitX = {1, 0};

struct vector vector(double x, double y){
    struct vector temp = {x, y};
    return temp;
}

struct vector add(struct vector a, struct vector b){
    struct vector temp = {a.x + b.x, a.y + b.y};
    return temp;
}

struct vector sub(struct vector a, struct vector b){
    struct vector temp = {a.x - b.x, a.y - b.y};
    return temp;
}

struct vector mult(struct vector a, double b){
    struct vector temp = {a.x * b, a.y * b};
    return temp;
}

struct vector divi(struct vector a, double b){
    struct vector temp = {a.x / b, a.y / b};
    return temp;
}

double mag(struct vector a){
    return sqrt(a.x * a.x + a.y * a.y);
}

struct vector unit(struct vector a){
    return divi(a, mag(a));
}

//ベクトルの終点にむかって左側の法線ベクトル
struct vector normalP(struct vector a){
    struct vector temp = unit(vector(-a.y, a.x));
    return temp;
}

//ベクトルの終点にむかって右側の法線ベクトル
struct vector normalN(struct vector a){
    struct vector temp = unit(vector(a.y, -a.x));
    return temp;
}

struct vector inverse(struct vector a){
    struct vector temp = {-a.x, -a.y};
    return temp;
}

struct vector rotate(struct vector a, double theta){
    struct vector temp = {a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta)};
    return temp;
}

//ax + by + c = 0
void equation(struct vector start, struct vector end, double* a, double* b, double* c){
    *a = end.y - start.y;
    *b = start.x - end.x;
    *c = start.y * end.x - start.x * end.y;
}

//ax + by + c = 0とpの距離
double dist(struct vector p, double a, double b, double c){
    return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
}

double angle(struct vector a){
    return angle2(unitX, a);
}
//0 <= theta <2piの範囲で
double angle2(struct vector a, struct vector b){
    double angle = acos(inner(a, b) / (mag(a) * mag(b)));
    if(outer(a, b) < 0)
        return 2 * M_PI - angle;
    else 
        return angle;
}

double inner(struct vector a, struct vector b){
    return a.x * b.x + a.y * b.y;
}

double outer(struct vector a, struct vector b){
    return a.x * b.y - a.y * b.x;
}

//2ベクトルが作る直線のうちcを基準に近い方の単位法線を返す。
struct vector normalization(struct vector a, struct vector b, struct vector c){
    struct vector l = sub(b, a);
    struct vector normal = normalP(l);
    //成す角がともに鋭角なら
    if(angle2(normal, sub(a, c)) > M_PI / 2 && angle2(normal, sub(b,c)) > M_PI / 2)
        normal = normalN(l);
        
    return normal;
}   

int isZero(struct vector a){
    if(mag(a) <= DBL_EPSILON)
        return 1;
    else 
        return 0;
}