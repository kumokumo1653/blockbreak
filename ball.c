#include "ball.h"
void initBall(struct ball* temp, double r, struct vector p){
    temp -> p = p;
    temp -> prevP = p;
    temp -> r = r;
    temp -> v = zero;
    temp -> a = zero;
    
}

void changeVelocity(struct ball* ball, double time){
    ball -> v = add(ball -> v, mult(ball -> a, time));
}

void changePosition(struct ball* ball, double time){
    ball -> prevP = ball -> p;
    ball -> p = add(ball -> p, mult(ball -> v, time));
}

//反射時の速度処理
void lineReflection(struct ball* ball, struct line line, struct vector p){
    //進行ベクトル
    struct vector f = sub(p, ball->prevP);
    //壁ベクトル
    struct vector l = sub(line.end, line.start);
    //法線ベクトルの決定
    struct vector normal = normalP(l);

    //直線部
    struct vector n = mult(normalP(l), ball -> r);
    struct vector wallStart = add(line.start, n);
    struct vector wallEnd = add(line.end, n);
    double a, b, c, g, h ,i; 
    equation(wallStart, wallEnd, &a, &b, &c);
    n = mult(normalN(l), ball -> r);
    wallStart = add(line.start, n);
    wallEnd = add(line.end, n);
    equation(wallStart, wallEnd, &g, &h, &i);

    if(fabs(a * p.x + b * p.y + c) <= DBL_EPSILON || fabs(g * p.x + h * p.y + i) <= DBL_EPSILON){
        //直線部
        //進行ベクトル成す角が鈍角ならもう一方
        if(angle2(normal, inverse(f)) > M_PI / 2 && angle2(inverse(f), normal) > M_PI / 2)
            normal = normalN(l);
        
        //反射単位ベクトル
        struct vector r = unit(add(f, mult(normal, 2 * inner(inverse(f), normal))));

        ball -> v = mult(r, mag(ball -> v) * line.e);
        if(isZero(ball->v))
            ball -> v = zero;
        //位置補正
        ball -> p.x = p.x;
        ball -> p.y = p.y;
        return;
    }else if (fabs(pow(p.x - line.start.x, 2) + pow(p.y - line.start.y, 2) - ball->r * ball->r) <= DBL_EPSILON * (fmax( fmax(1, ball->r * ball->r), pow(p.x - line.end.x, 2) + pow(p.y - line.end.y, 2)))){
        //始点部の円弧
        l = vector(p.y - line.start.y, line.start.x - p.x);
        normal = normalP(l);
        //進行ベクトル成す角が鈍角ならもう一方
        if(angle2(normal, inverse(f)) > M_PI / 2 && angle2(inverse(f), normal) > M_PI / 2)
            normal = normalN(l);
        
        //反射単位ベクトル
        struct vector r = unit(add(f, mult(normal, 2 * inner(inverse(f), normal))));

        ball -> v = mult(r, mag(ball -> v) * line.e);
        printf("v:%lf,%lf\n", ball -> v.x, ball -> v.y);
        if(isZero(ball->v))
            ball -> v = zero;
        //位置補正
        ball -> p.x = p.x;
        ball -> p.y = p.y;
        return;
    }else if(fabs(pow(p.x - line.end.x, 2) + pow(p.y - line.end.y, 2) - ball->r * ball->r) <= DBL_EPSILON * (fmax( fmax(1, ball->r * ball->r), pow(p.x - line.end.x, 2) + pow(p.y - line.end.y, 2)))){
        //終点部の円弧
        l = vector(p.y - line.end.y, line.end.x - p.x);
        normal = normalP(l);
        //進行ベクトル成す角が鈍角ならもう一方
        if(angle2(normal, inverse(f)) > M_PI / 2 && angle2(inverse(f), normal) > M_PI / 2)
            normal = normalN(l);
        
        //反射単位ベクトル
        struct vector r = unit(add(f, mult(normal, 2 * inner(inverse(f), normal))));

        ball -> v = mult(r, mag(ball -> v) * line.e);
        printf("v:%lf,%lf\n", ball -> v.x, ball -> v.y);
        if(isZero(ball->v))
            ball -> v = zero;
        //位置補正
        ball -> p.x = p.x;
        ball -> p.y = p.y;
        return;
    }
    printf("error\n");
}