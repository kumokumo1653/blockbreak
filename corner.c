#include "corner.h"
struct corner corner(int exist, struct vector center, double r, double startAngle, double endAngle, double e){
    struct corner temp = {exist, center, r, startAngle, endAngle, e};
    return temp;
}

//交点を返す。
int cornerCollision(struct corner tar, struct ball ball, struct vector *temp){
    struct vector movement = sub(ball.p, ball.prevP);
    struct vector start = add(tar.center, mult(rotate(unitX, tar.startAngle), tar.r));
    struct vector end = add(tar.center, mult(rotate(unitX, tar.endAngle), tar.r));
    //コーナーの範囲
    double theta = tar.endAngle - tar.startAngle < 0 ? tar.endAngle - tar.startAngle + 2 * M_PI : tar.endAngle - tar.startAngle;
    double out = tar.r + ball.r;
    double in = tar.r - ball.r;

    //移動ベクトルがどちらも内側の円より内側なら当たらない
    if(mag(sub(ball.p, tar.center)) < in && mag(sub(ball.prevP, tar.center)) < in){
        temp = NULL;
        return 0;
    }
    //外側
    struct vector normal = mult(normalization(ball.p, ball.prevP, tar.center), out);
    struct vector p = add(tar.center, normal);
    
    struct vector a = sub(ball.p, tar.center);
    struct vector b = sub(ball.prevP, tar.center);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(tar.center, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(tar.center, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(out * out - mag(ch) * mag(ch)));
        if(angle2(rotate(unitX, tar.startAngle), add(ch, ha)) <= theta){
            printf("kousa\n");
            printf("prev:%lf,%lf\n", ball.prevP.x, ball.prevP.y);
            printf("p:%lf,%lf\n", ball.p.x, ball.p.y);
            *temp = add(tar.center, (add(ch, ha)));
            return 1;
        }
        
    }

    //現在位置が領域内にあるか
    if(mag(sub(ball.p, tar.center)) <= out && mag(sub(ball.prevP, tar.center)) > out){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(tar.center, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(out * out - mag(ch) * mag(ch)));
        if(angle2(rotate(unitX, tar.startAngle), add(ch, ha)) <= theta){
            *temp = add(tar.center, (add(ch, ha)));
            printf("%lf,%lf\n", ball.p.x, ball.p.y);
            return 1;
        }
    }

    //内側
    normal = mult(normalization(ball.p, ball.prevP, tar.center), in);
    //移動前の位置が領域内にあるか
    if(mag(sub(ball.prevP, tar.center)) <= in && mag(sub(ball.p, tar.center)) > in){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(tar.center, a, b, c));
        struct vector ha = mult(unit(movement), sqrt(in * in - mag(ch) * mag(ch)));
        if(angle2(rotate(unitX, tar.startAngle), add(ch, ha)) <= theta){
            *temp = add(tar.center, (add(ch, ha)));
            return 1;
        }
    }

    //始点円弧部
    normal = mult(normalization(ball.p, ball.prevP, start), ball.r);
    
    a = sub(ball.p, start);
    b = sub(ball.prevP, start);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(start, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(start, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        if(angle2(inverse(rotate(unitX, tar.startAngle)), add(ch, ha)) <= M_PI){
            *temp = add(start, (add(ch, ha)));
            return 1;
        }
    }

    //現在位置が領域内にあるか
    if(mag(sub(ball.p, start)) <= ball.r && mag(sub(ball.prevP, start)) > ball.r){
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(start, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        if(angle2(inverse(rotate(unitX, tar.startAngle)), add(ch, ha)) <= M_PI){
            *temp = add(start, (add(ch, ha)));
            return 1;
        }
    }

    //終点円弧
    normal = mult(normalization(ball.p, ball.prevP, end), ball.r);
    
    a = sub(ball.p, end);
    b = sub(ball.prevP, end);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(end, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        printf("kosa\n");
        printf("p:%lf,%lf\n",ball.p.x, ball.p.y);
        printf("prevP:%lf,%lf\n",ball.prevP.x, ball.prevP.y);
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(end, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        if(angle2(rotate(unitX, tar.endAngle), add(ch, ha)) <= M_PI){

            *temp = add(end, add(ch, ha));
            return 1;
        }
    }

    //現在位置が領域内にあるか
    if(mag(sub(ball.p, end)) <= ball.r && mag(sub(ball.prevP, end)) > ball.r){
        printf("ryoiki\n");
        printf("p:%lf,%lf\n",ball.p.x, ball.p.y);
        printf("prevP:%lf,%lf\n",ball.prevP.x, ball.prevP.y);
        double a, b, c;
        equation(ball.prevP, ball.p, &a, &b, &c);
        struct vector ch = mult(unit(normal), dist(end, a, b, c));
        struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
        if(angle2(rotate(unitX, tar.endAngle), add(ch, ha)) <= M_PI){
            *temp = add(end, (add(ch, ha)));
            return 1;
        }
    }
    temp = NULL; 
    return 0;
}