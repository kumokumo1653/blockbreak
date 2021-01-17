#include <GL/glut.h>
#include <GL/glpng.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "field.h"
#include "block.h"
#include "ball.h"
#include "line.h"
#include "paddle.h"
#include "vector.h"
#include "shape.h"

#define FPS 60.0
#define FRAME 1.0 / FPS
#define WIDTH 900
#define HEIGHT 600
#define BLOCK_SIZE 30
#define BALL_R 10
#define BALL_S 300
#define PADDLE_W 75
#define PADDLE_S 500
#define LIFE 3
#define TIME 300
#define POPRATE 0.3
#define FALL_SPEED 100
void Display(void);
void Reshape(int ,int);
void Timer(int);
void gameTimer(int);
void itemTimer(int);
void Init();
void Update();
void Mouse(int, int, int, int);
void PassiveMotion(int, int);
void putString(struct vector, char[]);
void putSprite(GLuint, struct vector , double, double, double);
struct vector convertCoordinate(struct vector);
struct vector inverseConvertCoordinate(struct vector);

enum status{
	title,
	game,
	result
};
enum status status = title;
struct field field;
struct ball ball;
struct paddle paddle;
struct vector pointer;
GLuint blockImage[6];
GLuint itemImage[ITEM];
GLuint paddleImage;
GLuint ballImage;
GLuint arrowImage;
GLuint titleImage;
GLuint pushImage;
int firingFlag = 0;
double firingAngle = M_PI / 10;
double rotateDirection = 0.1;
int life;
int score;
int gameTime;
int replaytime = 0;
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH + BLOCK_SIZE * 2, HEIGHT + BLOCK_SIZE * 3);
    glutCreateWindow("ブロック崩し");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
	glutTimerFunc(FRAME * 1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(PassiveMotion);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);

	//igame読み込み
	blockImage[0] = pngBind("resources/block.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	blockImage[1] = pngBind("resources/red.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	blockImage[2] = pngBind("resources/yellow.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	blockImage[3] = pngBind("resources/green.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	blockImage[4] = pngBind("resources/bule.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	blockImage[5] = pngBind("resources/pink.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);

	itemImage[0] = pngBind("resources/ballSpeedUp.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	itemImage[1] = pngBind("resources/paddleSpeedDown.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	itemImage[2] = pngBind("resources/paddleShort.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	itemImage[3] = pngBind("resources/paddleLong.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);

	paddleImage = pngBind("resources/paddle.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	ballImage = pngBind("resources/ball.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	arrowImage = pngBind("resources/arrow.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	titleImage = pngBind("resources/title.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	pushImage = pngBind("resources/pushtext.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);

	srand((unsigned)time(NULL));

	pointer = zero;
    glutMainLoop();
    return 0;
}

void Display(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
		if(status == game){
		if(!firingFlag){
			putSprite(arrowImage, convertCoordinate(vector(ball.p.x, ball.p.y + 20)), 30, 30, M_PI / 2 - firingAngle);
		}
		for(i = 0; i < BLOCK; i++){
			if(field.blocks[i].isExist){
				putSprite(field.blocks[i].image, convertCoordinate(field.blocks[i].center), field.blocks[i].width, field.blocks[i].height, 0);
			}
		}


		//paddle
		putSprite(paddleImage, convertCoordinate(paddle.p), paddle.width, H, 0);
		//ball
		putSprite(ballImage, convertCoordinate(ball.p), ball.r * 2, ball.r * 2, 0);
		//item
		for(i = 0; i < ITEM; i++){
			if(field.items[i].isExist)
				putSprite(field.items[i].image, convertCoordinate(field.items[i].p), field.items[i].r * 2, field.items[i].r * 2, 0);
		}
		//wall
		for(i = 0; i < WALL;i++){
			struct vector wall = sub(convertCoordinate(field.wall[i].end), convertCoordinate(field.wall[i].start));
			struct vector start = convertCoordinate(field.wall[i].start);
			if(i <= 1)
				start = add(start, vector(-BLOCK_SIZE / 2, BLOCK_SIZE / 2));
			else
				start = add(start, vector(BLOCK_SIZE / 2, -BLOCK_SIZE / 2));
			
			for(j = 0;j <= mag(wall) / BLOCK_SIZE + 1; j++){
				putSprite(blockImage[0], add(start, mult(unit(wall), BLOCK_SIZE * j)), BLOCK_SIZE, BLOCK_SIZE, 0);
			}
		}

		//text
		char strLife[20];
		char strScore[20];
		char strTime[20];
		sprintf(strLife, "LIFE:%d", life);
		sprintf(strScore, "SCORE:%d", score);
		sprintf(strTime, "TIME:%d", gameTime);
		putString(vector(0,25), strLife);
		putString(vector(100, 25), strScore);
		putString(vector(850, 25), strTime);
	}else if (status == title){
		putSprite(titleImage,convertCoordinate(vector(WIDTH / 2, HEIGHT / 2)), WIDTH, HEIGHT, 0);
		putSprite(pushImage, convertCoordinate(vector(WIDTH / 2, HEIGHT / 2 - 200)), 200, 120, 0);
	}else if (status == result){
		char result[20];
		sprintf(result, "SCORE:%d", score);
		putSprite(titleImage,convertCoordinate(vector(WIDTH / 2, HEIGHT / 2)), WIDTH, HEIGHT, 0);
		putSprite(pushImage, convertCoordinate(vector(WIDTH / 2 + 200, HEIGHT / 2 - 200)), 200, 120, 0);
		putString(convertCoordinate(vector(WIDTH / 2 - 100, 150)), result);
	}
	glFlush();
}

void Reshape(int w, int h){
    glutReshapeWindow(WIDTH + BLOCK_SIZE * 2, HEIGHT + BLOCK_SIZE * 3);
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
	score = 0;
	firingFlag = 0;
	life = LIFE;
	gameTime = TIME;
	glutTimerFunc(1000, gameTimer, replaytime);
	initField(&field, WIDTH, HEIGHT, blockImage, itemImage);
	initBall(&ball, BALL_R, vector(WIDTH / 2,50 + H / 2 +  BALL_R));
	initPaddle(&paddle, vector(WIDTH / 2, 50), PADDLE_W, 1.0);
	paddle.v = PADDLE_S;
}

//時間経過
void Update(){
	//時間経過
	int i;
	int flag = 0;
	if(status == game){
		paddleChangePosition(&paddle, pointer, FRAME, field.width);
		if(firingFlag){
			ballChangeVelocity(&ball, FRAME);
			ballChangePosition(&ball, FRAME);
			struct vector temp;
			for(i = 0; i < WALL;i++){
				if(lineCollision(field.wall[i], ball, &temp)){
					if(i == 0){
						//地面なら
						life--;
						if(life <= 0){
							status = result;
						}else{
							//ボールの初期化
							firingFlag = 0;
							initBall(&ball, BALL_R, vector(pointer.x, 50 + H / 2 +  BALL_R));
							initPaddle(&paddle, vector(pointer.x, 50), PADDLE_W, 1.0);
							paddle.v = 500;
						}
					}else{
						lineReflection(&ball, field.wall[i], temp);
					}
				}
			}
			for(i = 0;i < BLOCK;i++){
				//あたったとき
				if(blockCollision(&(field.blocks[i]), &ball, &score)){
					if((double)rand() / RAND_MAX < POPRATE){
						//アイテム
						int type = rand() % ITEM;
						if(!field.items[type].isExist){
							field.items[type].isExist = 1;
							field.items[type].p = field.blocks[i].center;
							field.items[type].prevP = field.items[i].p;
							field.items[type].v = -FALL_SPEED;
							field.items[type].r = BALL_R;
						}
					}
				}

				if(field.blocks[i].isExist)
					flag = 1;
			}
			if (!flag){
				//全破壊
				score += gameTime * 100;
				status = result;
			}
		}else{
			//ボールの位置を補正
			ball.prevP = ball.p;
			ball.p.x = paddle.p.x;

			if(firingAngle < M_PI / 10){
				firingAngle = M_PI / 10;
				rotateDirection = -rotateDirection;
			}else if(firingAngle > 9 * M_PI / 10){
				firingAngle = 9 * M_PI / 10;
				rotateDirection = -rotateDirection;
			}
			firingAngle += rotateDirection;
		}
		paddleCollision(paddle, &ball);
		//item処理
		for(i = 0; i < ITEM; i++){
			if(field.items[i].isExist){
				itemChangePosition(&(field.items[i]), FRAME);
				if(itemCollision(field.items[i], paddle)){
					//アイテム使用
					glutTimerFunc(1000 * field.items[i].effectTime , itemTimer, i + 10 * replaytime);
					field.items[i].isExist = 0;
					switch (i) {
					case ballSpeedUp:
						ball.v = mult(unit(ball.v), BALL_S + 150);
						break;

					case paddleSpeedDown:
						paddle.v = PADDLE_S - 200;
					break;

					case paddleShort:
						paddle.width = PADDLE_W - 25;
					break;
					case paddleLong:
						paddle.width = PADDLE_W + 50;
					break;
					
					default:
						break;
					}
				}

				if(field.items[i].p.y < 0){
					//アイテム消去
					field.items[i].isExist = 0;
				}
			}
		}
	}
}

void Mouse(int button, int sts, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(sts == GLUT_UP){
			if(status == game){
				firingFlag = 1;
				ball.prevP = ball.p;
				ball.v = mult(rotate(unitX,firingAngle), BALL_S);
			}else if(status == title){
				status = game;
				Init();
			}else if (status == result){
				status = game;
				replaytime++;
				Init();
			}
		}
	}
}

void PassiveMotion(int x, int y){
	pointer = inverseConvertCoordinate(vector(x, y));
}

void gameTimer(int v){
	if(v == replaytime){
		gameTime--;
		if(gameTime <= 0)
			status = result;
		else
			glutTimerFunc(1000, gameTimer, v);
	}
}

void itemTimer(int v){
	//アイテム効果を戻す。
	if(v / 10 == replaytime){
		switch (v % 10) {
		case ballSpeedUp:
			ball.v = mult(unit(ball.v), BALL_S);
			break;

		case paddleSpeedDown:
			paddle.v = PADDLE_S;
		break;

		case paddleShort:
		case paddleLong:
			paddle.width = PADDLE_W;
		break;
		
		default:
			break;
		}
	}
}
void putString(struct vector first, char str[]){
	int i;
	glColor3ub(255,255,255);
	glRasterPos2i(first.x, first.y);
	for (i = 0; i < strlen(str); i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void putSprite(GLuint image, struct vector p, double width, double height, double angle){
    struct vector a = add(p, rotate(vector( width / 2,  height / 2), angle));
    struct vector b = add(p, rotate(vector(-width / 2,  height / 2), angle));
    struct vector c = add(p, rotate(vector(-width / 2, -height / 2), angle));
    struct vector d = add(p, rotate(vector( width / 2, -height / 2), angle));
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
//表示用座標に変換
struct vector convertCoordinate(struct vector a ){
	struct vector temp = vector(a.x + BLOCK_SIZE, HEIGHT - a.y + BLOCK_SIZE * 2);
	return temp;
}

//処理用の座標に変換
struct vector inverseConvertCoordinate(struct vector a){
	struct vector temp = vector(a.x - BLOCK_SIZE, HEIGHT - a.y + BLOCK_SIZE * 2);
	return temp;
}