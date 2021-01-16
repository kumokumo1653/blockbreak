#include "shape.h"

void DrawCircle(struct vector center, int r, GLenum mode,double stheta, double etheta, float stroke, GLubyte color[]){
    int i;
    //分割数
    int n = 360;
    //円描画
    glLineWidth(stroke);
    glBegin(mode); 
    glColor4ub(color[0], color[1], color[2], color[3]);
    double range = etheta - stheta;
    for (i = 0; i < n; i++) {
        double rate = (double)i / n;
        double x = r * cos(range * rate + stheta);
        double y = r * sin(range * rate + stheta);
        glVertex2i(center.x + x, center.y - y); // 頂点座標を指定
        
    }
    glEnd(); 
}

void DrawEllipse(struct vector center, int w_r, int h_r, GLenum mode,double stheta, double etheta, float stroke, GLubyte color[]){
    int i;
    //分割数
    int n = 360;
    double range = etheta - stheta;
    glLineWidth(stroke);    
    glBegin(mode);
    glColor4ub(color[0], color[1], color[2], color[3]);
    for (i = 0; i < n; i++) {
        double rate = (double)i / n;
        double x = w_r * cos(range * rate + stheta);
        double y = h_r * sin(range * rate + stheta);
        glVertex2i(center.x + x, center.y + y); // 頂点座標を指定
    }
    glEnd();    
}
