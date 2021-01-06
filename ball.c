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

//進行ベクトルと接線、壁のベクトルのなす角が同一のとき動作未確定
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
    }else if (isCircumference(p, line.start, ball->r)){
        //始点部の円弧
        l = vector(p.y - line.start.y, line.start.x - p.x);
        normal = normalP(l);
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
    }else if(isCircumference(p, line.end, ball->r)){
        //終点部の円弧
        l = vector(p.y - line.end.y, line.end.x - p.x);
        normal = normalP(l);
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
    }
    printf("error\n");
}

void cornerReflection(struct ball* ball, struct corner corner, struct vector p){
    //進行ベクトル
    struct vector f = sub(p, ball->prevP);
    struct vector start = add(corner.center, rotate(mult(unitX, corner.r), corner.startAngle));
    struct vector end = add(corner.center, rotate(mult(unitX, corner.r), corner.endAngle));
    //接線ベクトル
    struct vector l;
    //法線ベクトル
    struct vector normal;

    if (isCircumference(p, start, ball->r)){
        //始点部の円弧
        l = vector(p.y - start.y, start.x - p.x);
        normal = normalP(l);
        //進行ベクトル成す角が鈍角ならもう一方
        if(angle2(normal, inverse(f)) > M_PI / 2 && angle2(inverse(f), normal) > M_PI / 2)
            normal = normalN(l);
        
        //反射単位ベクトル
        struct vector r = unit(add(f, mult(normal, 2 * inner(inverse(f), normal))));

        ball -> v = mult(r, mag(ball -> v) * corner.e);
        if(isZero(ball->v))
            ball -> v = zero;
        //位置補正
        ball -> p.x = p.x;
        ball -> p.y = p.y;
        return;
    }else if(isCircumference(p, end, ball->r)){
        //終点部の円弧
        l = vector(p.y - end.y, end.x - p.x);
        normal = normalP(l);
        //進行ベクトル成す角が鈍角ならもう一方
        if(angle2(normal, inverse(f)) > M_PI / 2 && angle2(inverse(f), normal) > M_PI / 2)
            normal = normalN(l);
        
        //反射単位ベクトル
        struct vector r = unit(add(f, mult(normal, 2 * inner(inverse(f), normal))));

        ball -> v = mult(r, mag(ball -> v) * corner.e);
        if(isZero(ball->v))
            ball -> v = zero;
        //位置補正
        ball -> p.x = p.x;
        ball -> p.y = p.y;
        return;
    }else if(isCircumference(p, corner.center, corner.r + ball->r) || isCircumference(p, corner.center, corner.r - ball->r)){
        //外側か内側
        l = vector(p.y - corner.center.y, corner.center.x - p.x);
        normal = normalP(l);
        //進行ベクトル成す角が鈍角ならもう一方
        if(angle2(normal, inverse(f)) > M_PI / 2 && angle2(inverse(f), normal) > M_PI / 2)
            normal = normalN(l);
        
        //反射単位ベクトル
        struct vector r = unit(add(f, mult(normal, 2 * inner(inverse(f), normal))));

        printf("s\n");
        printf("v:%lf,%lf\n", ball -> v.x, ball -> v.y);
        ball -> v = mult(r, mag(ball -> v) * corner.e);
        if(isZero(ball->v))
            ball -> v = zero;
        //位置補正
        ball -> p.x = p.x;
        ball -> p.y = p.y;
        return;
    }
    printf("error\n");
}

//半径rの中心cの円の円周上にaがあるかどうか
int  isCircumference(struct vector a, struct vector c, double r){

    if(fabs(pow(a.x - c.x, 2) + pow(a.y - c.y, 2) - r * r) <= DBL_EPSILON * 5 * (fmax( fmax(1, r * r), pow(a.x - c.x, 2) + pow(a.y - c.y, 2))))
        return 1;
    else return 0;
}