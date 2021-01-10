#include "line.h"
struct line line(struct vector start, struct vector end, double e){
    struct line temp = {start, end, e};
    return temp;
}

//衝突したかどうか交点を返す
int lineCollision(struct line line, struct ball ball, struct vector* temp){
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


    //線分端の円弧部の当たり判定

    //移動ベクトルが円弧範囲内にある場合
    if(angle2(normalP(l), sub(ball.p, line.start)) <= M_PI && angle2(normalP(l), sub(ball.prevP, line.start)) <= M_PI ){
        if(mag(sub(ball.p, line.start)) <= ball.r && mag(sub(ball.prevP, line.start)) <= ball.r){
            temp = NULL;
            return 0;
        }
    }
    if(angle2(normalN(l), sub(ball.p, line.end)) <= M_PI && angle2(normalN(l), sub(ball.prevP, line.end)) <= M_PI ){
        if(mag(sub(ball.p, line.end)) <= ball.r && mag(sub(ball.prevP, line.end)) <= ball.r){
            temp = NULL;
            return 0;
        }
    }

    if(outer(l, a) * outer(l, b) < 0 && outer(movement, sub(wallStart, ball.p)) * outer(movement, sub(wallEnd, ball.p)) < 0){
        //内側からだったら当たらない
        if(angle2(n, movement) < M_PI / 2 || angle2(movement, n) < M_PI / 2){
            temp = NULL;
            return 0;
        }
        double alpha = (wallEnd.x - wallStart.x) * (ball.p.y - ball.prevP.y) - (ball.p.x - ball.prevP.x) * (wallEnd.y - wallStart.y);
        double beta = ((ball.p.y - ball.prevP.y) * (ball.p.x - wallStart.x) + (ball.prevP.x - ball.p.x) * (ball.p.y - wallStart.y)) / alpha;
        *temp = add(wallStart, mult(l, beta));
        return 1;
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
        //内側からだったら当たらない
        if(angle2(n, movement) < M_PI / 2 || angle2(movement, n) < M_PI / 2){
            temp = NULL;
            return 0;
        }
        double alpha = (wallEnd.x - wallStart.x) * (ball.p.y - ball.prevP.y) - (ball.p.x - ball.prevP.x) * (wallEnd.y - wallStart.y);
        double beta = ((ball.p.y - ball.prevP.y) * (ball.p.x - wallStart.x) + (ball.prevP.x - ball.p.x) * (ball.p.y - wallStart.y)) / alpha;
        *temp = add(wallStart, mult(l, beta));
        return 1;
    } 

    //接線と交差しているか始点側
    struct vector normal = normalP(movement);
    if(angle2(normal, sub(ball.p, line.end)) > M_PI / 2 && angle2(normal, sub(ball.prevP, line.end)) > M_PI / 2)
    normal = normalN(movement);
    struct vector p = add(line.start, normal);
    
    a = sub(ball.p, line.start);
    b = sub(ball.prevP, line.start);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(line.start, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        //円弧の角度の範囲内に移動ベクトルの片方でも入っているか
        if(angle2(normalP(l), sub(ball.p, line.start)) <= M_PI || angle2(normalP(l), sub(ball.prevP, line.start)) <= M_PI ){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(line.start, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
            *temp = add(line.start, (add(ch, ha)));
            return 1;
        }
    }

    //現在位置が領域内にあるか
    if(angle2(normalP(l), sub(ball.p, line.start)) <= M_PI){
        if(mag(sub(ball.p, line.start)) <= ball.r && mag(sub(ball.prevP, line.start)) > ball.r){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(line.start, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
            *temp = add(line.start, (add(ch, ha)));
            return 1;
        }
    }


    //接線と交差しているか終点側
    normal = normalP(movement);
    if(angle2(normal, sub(ball.p, line.end)) > M_PI / 2 && angle2(normal, sub(ball.prevP, line.end)) > M_PI / 2)
        normal = normalN(movement);
    
    p = add(line.end, normal);
    
    a = sub(ball.p, line.end);
    b = sub(ball.prevP, line.end);
    //交差しているか
    if(outer(normal, a) * outer(normal, b) < 0 && outer(movement, sub(line.end, ball.prevP)) * outer(movement, sub(p, ball.prevP)) < 0){
        //円弧の角度の範囲内に移動ベクトルの片方でも入っているか
        if(angle2(normalN(l), sub(ball.p, line.end)) <= M_PI || angle2(normalN(l), sub(ball.prevP, line.end)) <= M_PI ){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(line.end, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
            *temp = add(line.end, (add(ch, ha)));
            return 1;
        }
    }

    //現在位置が領域内にあるか
    if(angle2(normalN(l), sub(ball.p, line.end)) <= M_PI){
        if(mag(sub(ball.p, line.end)) <= ball.r && mag(sub(ball.prevP, line.end)) > ball.r){
            double a, b, c;
            equation(ball.prevP, ball.p, &a, &b, &c);
            struct vector ch = mult(unit(normal), dist(line.end, a, b, c));
            struct vector ha = mult(unit(inverse(movement)), sqrt(ball.r * ball.r - mag(ch) * mag(ch)));
            *temp = add(line.end, (add(ch, ha)));
            return 1;
        }
    }
    
    temp = NULL;
    return 0;

}