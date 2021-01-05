#include "line.h"
struct line line(int exist, struct vector start, struct vector end, double e){
    struct line temp = {exist, start, end, e};
    return temp;
}

//衝突したかどうか交点を返す
struct vector* lineCollision(struct line line, struct ball ball){
    //lineベクトル
    struct vector l = sub(line.end, line.start);

    //片側
    struct vector n = mult(normalP(l), ball.r);
    struct vector wallStart = add(line.start, n);
    struct vector wallEnd = add(line.end, n);
    //lineの始点とボールのベクトル
    struct vector a = sub(ball.p, wallStart);
    struct vector b = sub(ball.prevP, wallStart);
    struct vector movement = sub(ball.p, ball.prevP);

    struct vector* val;

    //線分端の円弧部の当たり判定
    //始点の円弧
    struct corner s = corner(1, line.start, ball.r, angle(normalP(l)), angle(normalN(l)), 1.0);
    //終点の円弧
    struct corner e = corner(1, line.end, ball.r, angle(normalN(l)), angle(normalN(l)), 1.0);

    //移動ベクトルが円弧範囲内にある場合
    if(angle2(normalP(l), sub(ball.p, s.center)) <= M_PI && angle2(normalP(l), sub(ball.prevP, s.center)) <= M_PI ){
        if(mag(sub(ball.p, s.center)) <= s.r && mag(sub(ball.prevP, s.center)) <= s.r){
            return NULL;
        }
    }
    if(angle2(normalN(l), sub(ball.p, e.center)) <= M_PI && angle2(normalN(l), sub(ball.prevP, e.center)) <= M_PI ){
        if(mag(sub(ball.p, e.center)) <= e.r && mag(sub(ball.prevP, e.center)) <= e.r){
            return NULL;
        }
    }

    if(outer(l, a) * outer(l, b) < 0 && outer(movement, sub(wallStart, ball.p)) * outer(movement, sub(wallEnd, ball.p)) < 0){
        struct vector temp;
        double alpha = (wallEnd.x - wallStart.x) * (ball.p.y - ball.prevP.y) - (ball.p.x - ball.prevP.x) * (wallEnd.y - wallStart.y);
        double beta = ((ball.p.y - ball.prevP.y) * (ball.p.x - wallStart.x) + (ball.prevP.x - ball.p.x) * (ball.p.y - wallStart.y)) / alpha;
        temp = add(wallStart, mult(l, beta));
        return val = &temp;
    }
    //もう一方
    n = mult(normalN(l), ball.r);
    wallStart = vector(line.start.x + n.x, line.start.y + n.y);
    wallEnd = vector(line.end.x + n.x, line.end.y + n.y);
    //lineの始点とボールのベクトル
    a = sub(ball.p, wallStart);
    b = sub(ball.prevP, wallStart);
    movement = sub(ball.p, ball.prevP);
    if(outer(l, a) * outer(l, b) < 0 && outer(movement, sub(wallStart, ball.p)) * outer(movement, sub(wallEnd, ball.p)) < 0){
        struct vector temp;
        double alpha = (wallEnd.x - wallStart.x) * (ball.p.y - ball.prevP.y) - (ball.p.x - ball.prevP.x) * (wallEnd.y - wallStart.y);
        double beta = ((ball.p.y - ball.prevP.y) * (ball.p.x - wallStart.x) + (ball.prevP.x - ball.p.x) * (ball.p.y - wallStart.y)) / alpha;
        temp = add(wallStart, mult(l, beta));
        return val = &temp;
    } 

    //接線と交差しているか始点側
    //一方を採用
    struct vector normal = mult(normalP(movement), ball.r);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, s.center)) > M_PI / 2 && angle2(sub(ball.p, s.center), normal) > M_PI / 2)
        normal = mult(normalN(movement), ball.r);
    struct vector p = add(s.center, normal);
    
    a = sub(ball.p, s.center);
    b = sub(ball.prevP, s.center);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(s.center, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        //円弧の角度の範囲内に移動ベクトルの片方でも入っているか
        if(angle2(normalP(l), sub(ball.p, s.center)) <= M_PI || angle2(normalP(l), sub(ball.prevP, s.center)) <= M_PI ){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(s.center, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(s.r * s.r - mag(ch) * mag(ch)));
            struct vector temp = add(s.center, (add(ch, ha)));
            return val = &temp;
        }
    }

    //現在位置が領域内にあるか
    if(angle2(normalP(l), sub(ball.p, s.center)) <= M_PI){
        if(mag(sub(ball.p, s.center)) <= s.r){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(s.center, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(s.r * s.r - mag(ch) * mag(ch)));
            struct vector temp = add(s.center, (add(ch, ha)));
            return val = &temp;
        }
    }


    //接線と交差しているか終点側
    //一方を採用
    normal = mult(normalP(movement), ball.r);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, e.center)) > M_PI / 2 && angle2(sub(ball.p, e.center), normal) > M_PI / 2)
        normal = mult(normalN(movement), ball.r);
    p = add(e.center, normal);
    
    a = sub(ball.p, e.center);
    b = sub(ball.prevP, e.center);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(e.center, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        //円弧の角度の範囲内に移動ベクトルの片方でも入っているか
        if(angle2(normalN(l), sub(ball.p, e.center)) <= M_PI || angle2(normalN(l), sub(ball.prevP, e.center)) <= M_PI ){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(e.center, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(e.r * e.r - mag(ch) * mag(ch)));
            struct vector temp = add(e.center, (add(ch, ha)));
            return val = &temp;
        }
    }

    //現在位置が領域内にあるか
    if(angle2(normalN(l), sub(ball.p, e.center)) <= M_PI){
        if(mag(sub(ball.p, e.center)) <= s.r){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(e.center, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(e.r * e.r - mag(ch) * mag(ch)));
            struct vector temp = add(e.center, (add(ch, ha)));
            return val = &temp;
        }
    }
    
    return NULL;

}