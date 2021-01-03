#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "field.h"
#include "ball.h"
#include "shape.h"

#define FPS 60.0
#define FRAME 1.0 / FPS
#define G -9.8
#define WIDTH 400
#define HEIGHT 600
#define BALL_R 10
void Display(void);
void Reshape(int ,int);
void Timer(int);
void Init();
void Update();
struct vector convertCoordinate(struct vector);

struct field field;
struct ball ball;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("サンプル");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
	glutTimerFunc(FRAME * 1000, Timer, 0);
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(0.0, 0.0, 1.0, 1.0);

	Init();
	printf("x:%lf, y:%lf\n", ball.p.x, ball.p.y);
    glutMainLoop();
    return 0;
}

void Display(void){
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	for(i = 0; i < WALL;i++){
		struct vector start = convertCoordinate(field.wall[i].start);
		struct vector end = convertCoordinate(field.wall[i].end);
		glBegin(GL_LINES);
			glVertex2i(start.x, start.y);
			glVertex2i(end.x, end.y);
		glEnd();
	}
	struct vector center = convertCoordinate(ball.p);
	DrawCircle(center, ball.r, GL_POLYGON, 0, 2 * M_PI, 2.0, (GLubyte[]){255,255,255,255});
	glFlush();
}

void Reshape(int w, int h){
    glutReshapeWindow(WIDTH, HEIGHT);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1, -1, 1);
    glTranslated(0, -h, 0);
}

void Timer(int value){
	glutTimerFunc(FRAME * 1000, Timer, 0);
	Update();
	Display();
}

//ステージの初期化
void Init(){
	initField(&field, WIDTH, HEIGHT);
	initBall(&ball, BALL_R, vector(95,200));
}

//時間経過
void Update(){
	//重力加速度を設定
	ball.a = vector(0,G);
	//時間経過
	changeVelocity(&ball, FRAME);
	changePosition(&ball, FRAME);
	struct vector *temp = lineCollision(field.wall[0], ball);
	if(temp != NULL)
		printf("x:%lfy:%lf\n", temp -> x, temp -> y);

}

struct vector convertCoordinate(struct vector a){
	struct vector temp = {a.x, HEIGHT - a.y};
	return temp;
}