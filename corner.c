#include "corner.h"
struct corner corner(int exist, struct vector center, double r, double startAngle, double endAngle, double e){
    struct corner temp = {exist, center, r, startAngle, endAngle, e};
    return temp;
}

//交点を返す。
struct vector* cornerCollision(struct corner tar, struct ball ball){
    struct vector movement = sub(ball.p, ball.prevP);
    struct vector start = add(tar.center, mult(rotate(unitX, tar.startAngle), tar.r));
    struct vector end = add(tar.center, mult(rotate(unitX, tar.endAngle), tar.r));
    //コーナーの範囲
    double theta = tar.endAngle - tar.startAngle < 0 ? tar.endAngle - tar.startAngle + 2 * M_PI : tar.endAngle - tar.startAngle;
    double out = tar.r + ball.r;
    double in = tar.r - ball.r;
    struct vector* val;

    //外側
    struct vector normal = mult(normalP(movement), out);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, tar.center)) > M_PI / 2 && angle2(sub(ball.p, tar.center), normal) > M_PI / 2)
        normal = mult(normalN(movement), out);
    struct vector p = add(tar.center, normal);
    
    struct vector a = sub(ball.p, tar.center);
    struct vector b = sub(ball.prevP, tar.center);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(tar.center, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(tar.center, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(out * out - mag(ch) * mag(ch)));
        struct vector temp = add(tar.center, (add(ch, ha)));
        if(angle2(rotate(unitX, tar.startAngle), add(ch, ha)) <= theta)
            return val = &temp;
        
    }

    //現在位置が領域内にあるか
    if(mag(sub(ball.p, tar.center)) <= out){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(tar.center, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(out * out - mag(ch) * mag(ch)));
        struct vector temp = add(tar.center, (add(ch, ha)));
        if(angle2(rotate(unitX, tar.startAngle), add(ch, ha)) <= theta)
            return val = &temp;
    }

    //内側
    normal = mult(normalP(movement), in);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, tar.center)) > M_PI / 2 && angle2(sub(ball.p, tar.center), normal) > M_PI / 2)
        normal = mult(normalN(movement), in);
    //移動前の位置が領域内にあるか
    if(mag(sub(ball.prevP, tar.center)) <= in){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(tar.center, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(in * in - mag(ch) * mag(ch)));
        struct vector temp = add(tar.center, (add(ch, ha)));
        if(angle2(rotate(unitX, tar.startAngle), add(ch, ha)) <= theta)
            return val = &temp;
    }

    //始点円弧部
    normal = mult(normalP(movement), ball.r);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, start)) > M_PI / 2 && angle2(sub(ball.p, start), normal) > M_PI / 2)
        normal = mult(normalN(movement), ball.r);
    
    a = sub(ball.p, start);
    b = sub(ball.prevP, start);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(start, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(start, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        struct vector temp = add(start, (add(ch, ha)));
        if(angle2(inverse(rotate(unitX, tar.startAngle)), add(ch, ha)) <= M_PI)
            return val = &temp;
    }

    //現在位置が領域内にあるか
    if(mag(sub(ball.p, start)) <= ball.r){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(start, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        struct vector temp = add(start, (add(ch, ha)));
        if(angle2(inverse(rotate(unitX, tar.startAngle)), add(ch, ha)) <= M_PI)
            return val = &temp;
    }

    //終点円弧
    normal = mult(normalP(movement), ball.r);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, end)) > M_PI / 2 && angle2(sub(ball.p, end), normal) > M_PI / 2)
        normal = mult(normalN(movement), ball.r);
    
    a = sub(ball.p, end);
    b = sub(ball.prevP, end);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(end, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(end, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        struct vector temp = add(end, (add(ch, ha)));
        if(angle2(rotate(unitX, tar.endAngle), add(ch, ha)) <= M_PI)
            return val = &temp;
    }

    //現在位置が領域内にあるか
    if(mag(sub(ball.p, end)) <= ball.r){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(end, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        struct vector temp = add(end, (add(ch, ha)));
        if(angle2(rotate(unitX, tar.endAngle), add(ch, ha)) <= M_PI)
            return val = &temp;
    }
    
    return NULL;
}