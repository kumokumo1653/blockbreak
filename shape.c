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

void putSprite(GLuint image, struct vector p, double width, double height, double angle){
    struct vector a = add(p, rotate(vector( width / 2,  height / 2), -angle));
    struct vector b = add(p, rotate(vector(-width / 2,  height / 2), -angle));
    struct vector c = add(p, rotate(vector(-width / 2, -height / 2), -angle));
    struct vector d = add(p, rotate(vector( width / 2, -height / 2), -angle));
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);

    glTexCoord2d(0, 0);
    glVertex2d(c.x, c.y);

    glTexCoord2d(0, 1);
    glVertex2d(b.x, b.y);

    glTexCoord2d(1, 1);
    glVertex2d(a.x, a.y);

    glTexCoord2d(1, 0);
    glVertex2d(d.x, d.y);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}