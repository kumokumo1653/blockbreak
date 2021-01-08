#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "field.h"
#include "ball.h"
#include "line.h"
#include "paddle.h"
#include "vector.h"
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
void Mouse(int, int, int, int);
void PossiveMotion(int, int);
struct vector convertCoordinate(struct vector);
struct vector inverseConvertCoordinate(struct vector);

struct field field;
struct ball ball;
struct paddle paddle;
struct vector pointer;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("サンプル");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
	glutTimerFunc(FRAME * 1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(PossiveMotion);
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

	for(i = 0; i < BLOCK; i++){
		if(field.blocks[i].isExist){
			struct vector a = convertCoordinate(add(field.blocks[i].center, rotate(vector( field.blocks[i].width / 2, field.blocks[i].height / 2), field.blocks[i].angle)));
			struct vector b = convertCoordinate(add(field.blocks[i].center, rotate(vector(-field.blocks[i].width / 2, field.blocks[i].height / 2), field.blocks[i].angle)));
			struct vector c = convertCoordinate(add(field.blocks[i].center, rotate(vector(-field.blocks[i].width / 2, -field.blocks[i].height / 2), field.blocks[i].angle)));
			struct vector d = convertCoordinate(add(field.blocks[i].center, rotate(vector( field.blocks[i].width / 2, -field.blocks[i].height / 2), field.blocks[i].angle)));

			glBegin(GL_QUADS);
				glVertex2i(a.x, a.y);
				glVertex2i(b.x, b.y);
				glVertex2i(c.x, c.y);
				glVertex2i(d.x, d.y);
			glEnd();
		}
	}


	glBegin(GL_QUADS);
		struct vector a = convertCoordinate(add(paddle.p, vector( paddle.width / 2, H / 2)));
		struct vector b = convertCoordinate(add(paddle.p, vector(-paddle.width / 2, H / 2)));
		struct vector c = convertCoordinate(add(paddle.p, vector(-paddle.width / 2, -H / 2)));
		struct vector d = convertCoordinate(add(paddle.p, vector( paddle.width / 2, -H / 2)));
		glVertex2i(a.x, a.y);
		glVertex2i(b.x, b.y);
		glVertex2i(c.x, c.y);
		glVertex2i(d.x, d.y);
	glEnd();
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
	initBall(&ball, BALL_R, vector(100,100));
	ball.v = vector(100,50);
	initPaddle(&paddle, vector(WIDTH / 2, 50), 50, 1.0);
	
}

//時間経過
void Update(){
	//時間経過
	int i;
	paddleChangePosition(&paddle, pointer, field.width);
	ballChangeVelocity(&ball, FRAME);
	ballChangePosition(&ball, FRAME);
	struct vector temp;
	for(i = 0; i < WALL;i++){
		if(lineCollision(field.wall[i], ball, &temp)){
			lineReflection(&ball, field.wall[i], temp);
		}
	}
	for(i = 0;i < BLOCK;i++){
		blockCollision(&(field.blocks[i]), &ball);
	}

	paddleCollision(paddle, &ball);
}

void Mouse(int button, int status, int x, int y){
}

void PossiveMotion(int x, int y){
	pointer = inverseConvertCoordinate(vector(x, y));
}
struct vector convertCoordinate(struct vector a){
	struct vector temp = vector(a.x, HEIGHT - a.y);
	return temp;
}

struct vector inverseConvertCoordinate(struct vector a){
	struct vector temp = vector(a.x, HEIGHT - a.y);
	return temp;
}