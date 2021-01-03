#include "line.h"
struct line line(int exist, struct vector start, struct vector end, double e){
    struct line temp = {exist, start, end, e};
    return temp;
}

//衝突したかどうか
int lineCollision(struct line line, struct ball ball){
    //lineベクトル
    struct vector l = sub(line.end, line.start);

    //片側
    struct vector n = mult(normalP(l), ball.r);
    struct vector wallStart = vector(line.start.x + n.x, line.start.y + n.y);
    struct vector wallEnd = vector(line.end.x + n.x, line.end.y + n.y);
    //lineの始点とボールのベクトル
    struct vector a = sub(ball.p, wallStart);
    struct vector b = sub(ball.prevP, wallStart);
    struct vector movement = sub(ball.p, ball.prevP);
    if(outer(l, a) * outer(l, b) <= 0 && outer(movement, wallStart) * outer(movement, wallEnd) <= 0)
        return 1;
    //もう一方
    n = mult(normalN(l), ball.r);
    wallStart = vector(line.start.x + n.x, line.start.y + n.y);
    wallEnd = vector(line.end.x + n.x, line.end.y + n.y);
    //lineの始点とボールのベクトル
    a = sub(ball.p, wallStart);
    b = sub(ball.prevP, wallStart);
    movement = sub(ball.p, ball.prevP);
    if(outer(l, a) * outer(l, b) <= 0 && outer(movement, wallStart) * outer(movement, wallEnd) <= 0)
        return 1;
    
    //線分端の円弧部の当たり判定
    //始点の円弧
    struct corner s = corner(1, 0, line.start, ball.r, angle(normalP(l)), angle(normalN(l)), 1.0);
    //終点の円弧
    struct corner e = corner(1, 0, line.end, ball.r, angle(normalN(l)), angle(normalN(l)), 1.0);
    //接線と交差しているか
    //一方を採用
    struct vector normal = mult(normalP(movement), ball.r);
    //成す角が鈍角ならもう一方
    if(angle2(normal, sub(ball.p, s.center)) > 90)
        normal = mult(normalN(movement), ball.r);
    struct vector p = add(s.center, normal);
    
    a = sub(ball.p, s.center);
    b = sub(ball.prevP, s.center);
    if(outer(normal, a) * outer(normal, b) <= 0 && outer(movement, sub(s.center, ball.prevP)) * outer(movement, sub(p, ball.prevP)) <= 0)
        return 1;
    
    return 0;

}