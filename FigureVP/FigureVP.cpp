// FigureVP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h> 
#include <math.h>
#include<iostream>
using namespace std;

#define SIZE 256
#define Hat 0
#define Clothes 1
#define Pants 2
#define Shoes 3
#define Face 4
#define Body 5
#define LeftEye 6
#define RightEye 7
#define Hands 8

GLint WindowWidth = 800;
GLint WindowHeight = 800;
GLint HatColor = 0;
GLint ClothColor = 1;
GLint PantsColor = 2;
GLint ShoesColor = 3;
GLint FaceAndBodyColor = 4;
GLint EyesColor = 5;


GLint part;
static bool LEFT_DOWN = false;
static GLint X = 0;
static GLint Y = 0;

GLfloat theta = 0.0;
GLfloat sx = 1.0;
GLfloat sy = 1.0;
GLfloat sz = 1.0;
GLfloat s = 1.0;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Reshape(GLint w, GLint h) {
	WindowWidth = w;
	WindowHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}




//画人脸
void drawFace() {
	//人脸
	int n = 200; double t;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(2.2*cos(t), 2.2*sin(t) + 3.7);
	}
	glEnd();
	glBegin(GL_POLYGON);
	//鼻子
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, 3.0);   glVertex2f(0, 2.9);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0, 2.9);   glVertex2f(-0.2, 3.0);
	glEnd();
	//嘴巴
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 2.2);
	glVertex2f(0.2, 2.1);
	glVertex2f(0, 2.2);
	glVertex2f(-0.2, 2.1);
	glVertex2f(-0.4, 2.2);
	glEnd();
}

void drawNose() {
}

float EyeLX = -1.0;
float EyeLY = 3.7;
void drawLeftEye(float x, float y) {
	EyeLX = x;
	EyeLY = y;
	int n = 20; double t;
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(0.25*cos(t) + EyeLX, 0.3*sin(t) + EyeLY);
	}
	glEnd();
}

float EyeRX = 1.0;
float  EyeRY = 3.7;
void drawRightEye(float x, float y) {
	EyeRX = x;
	EyeRY = y;
	int n = 20; double t;
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(0.25*cos(t) + EyeRX, 0.3*sin(t) + EyeRY);
	}
	glEnd();
}

void drawCloth() {//画衣服，梯形
	glBegin(GL_POLYGON);
	glVertex2f(1.1, 1.8);   glVertex2f(3, -3.4);
	glVertex2f(-3, -3.4);   glVertex2f(-1.1, 1.8);
	glEnd();
	glBegin(GL_POLYGON);//右边的袖子
	glVertex2f(3.5, 0.6);
	glVertex2f(3.5, -0.3);
	glVertex2f(1.2, 0.3);
	glVertex2f(1.2, 1.2);
	glEnd();
	glBegin(GL_POLYGON);//左边的袖子
	glVertex2f(-3.5, 0.6);
	glVertex2f(-3.5, -0.3);
	glVertex2f(-1.2, 0.3);
	glVertex2f(-1.2, 1.2);
	glEnd();


}

void drawHat() {
	//帽子	
	glBegin(GL_TRIANGLES);
	glVertex2f(-2.5, 4.4);  glVertex2f(0, 8.0);   glVertex2f(2.5, 4.4);
	glEnd();
}


void drawPants() {
	//右边的裤子
	glBegin(GL_POLYGON);
	glVertex2f(1.5, -3.4);
	glVertex2f(0.5, -3.4);
	glVertex2f(0.5, -5.5);
	glVertex2f(1.5, -5.5);
	glEnd();
	//左边的裤子
	glBegin(GL_POLYGON);
	glVertex2f(-1.5, -3.4);
	glVertex2f(-0.5, -3.4);
	glVertex2f(-0.5, -5.5);
	glVertex2f(-1.5, -5.5);
	glEnd();
}

void drawHands() {
	int n = 20; double t;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(0.45*cos(t) - 3.6, 0.45*sin(t) + 0.12);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(0.45*cos(t) + 3.6, 0.45*sin(t) + 0.12);
	}
	glEnd();
}

void drawShoes() {
	int n = 20; double t;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(0.5*cos(t) - 1, 0.5*sin(t) - 5.7);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(0.5*cos(t) + 1, 0.5*sin(t) - 5.7);
	}
	glEnd();
}

void drawFigure(GLenum mode) {
	if (mode == GL_SELECT)
	{
		glLoadName(Hands);//加载图元名称
	}
	glColor3f(1.0, 1.0, 1.0);
	drawHands();
	if (mode == GL_SELECT)
		glLoadName(Shoes);
	drawShoes();
	if (mode == GL_SELECT)
		glLoadName(Pants);
	glColor3f(1.0, 0.0, 0.0);
	drawPants();
	if (mode == GL_SELECT)
		glLoadName(Clothes);
	glColor3f(0.0, 0.0, 1.0);
	drawCloth();
	if (mode == GL_SELECT)
		glLoadName(Face);
	glColor3f(1.0, 1.0, 1.0);
	drawFace();
	if (mode == GL_SELECT)
		glLoadName(LeftEye);
	glColor3f(0.0, 0.0, 0.0);
	drawLeftEye(EyeLX, EyeLY);
	if (mode == GL_SELECT)
		glLoadName(RightEye);
	drawRightEye(EyeRX, EyeRY);
	if (mode == GL_SELECT)
		glLoadName(Hat);
	glColor3f(1.0, 0.0, 0.0);
	drawHat();
}


void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta, 0.0, 0.0, 1.0);
	glScalef(s, s, s);
	drawFigure(GL_RENDER);

	glFlush();
}

void processHits(GLint hits, GLuint buffer[])
{//拾取
	unsigned int i, j;
	GLuint names, *ptr;

	printf("hits=%d\n", hits);
	ptr = (GLuint *)buffer;
	//对命中的次数进行循环
	for (i = 0; i < hits; i++)
	{
		names = *ptr;
		//忽略名称的数量和深度信息
		ptr += 3;
		//检查命中纪录中的每个名称
		for (j = 0; j < names; j++)
		{
			if (*ptr == 0)
			{
				printf("帽子\n");
				part = Hat;
			}
			else if (*ptr == 1)
			{
				printf("上衣\n");
				part = Clothes;
			}
			else if (*ptr == 2)
			{
				printf("裤子\n");
				part = Pants;
			}
			else if (*ptr == 3)
			{
				printf("鞋子\n");
				part = Shoes;
			}
			else if (*ptr == 4)
			{
				printf("脸\n");
				part = Face;
			}
			else if (*ptr == 5)
			{
				printf("身体\n");
				part = Body;
			}
			else if (*ptr == 6)
			{
				printf("左眼\n");
				part = LeftEye;
			}
			else if (*ptr == 7)
			{
				printf("右眼\n");
				part = RightEye;
			}

			else if (*ptr == 8)
			{
				printf("手\n");
				part = Hands;
			}
			//循环到下一个命中记录
			ptr++;
		}
	}
	printf("part:%d\n", part);
}

void Mouse(int button, int state, int x, int y) {
	GLuint SelectBuf[SIZE];//创建一个保存选择结果的数组
	GLint hits;
	GLint viewport[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LEFT_DOWN = true;
		X = x;
		Y = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		glGetIntegerv(GL_VIEWPORT, viewport);//设置一个观察空间
		glSelectBuffer(SIZE, SelectBuf); //告诉OpenGL初始化 selectbuffer
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(0);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();//保存当前矩阵压入栈中；
		glLoadIdentity();//重置当前变换矩阵为单位矩阵；
		gluPickMatrix(x, viewport[3] - y, 2.0, 2.0, viewport);//建立一个拾取的视窗，保存到viewport当中，为什么是viewport[3] - y？？？
		gluOrtho2D(-10, 10, -10, 10);
		drawFigure(GL_SELECT);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		hits = glRenderMode(GL_RENDER);
		processHits(hits, SelectBuf);
		glutPostRedisplay();


	}


}

void myMotion(int x, int y) {

	if (LEFT_DOWN) {
		GLfloat OriginX = -10 + (GLfloat)X * 20 / (GLfloat)WindowWidth;
		GLfloat OriginY = 10 - (GLfloat)Y * 20 / (GLfloat)WindowHeight;//初始的X,Y在视窗里的位置
		GLfloat MovedX = -10 + (GLfloat)x * 20 / (GLfloat)WindowWidth;
		GLfloat MovedY = 10 - (GLfloat)y * 20 / (GLfloat)WindowWidth;//鼠标移动到的位置在视窗里的位置，这里是从屏幕坐标到视窗坐标的转换
		GLfloat DX = MovedX - OriginX;
		GLfloat DY = MovedY - OriginY;
		if (part == LeftEye) {
			EyeLX += DX;
			EyeLY += DY;
			glColor3f(0, 0, 0);
			drawLeftEye(EyeLX, EyeLY);
			glutPostRedisplay();
		}
		if (part == RightEye) {

			EyeRX += DX;
			EyeRY += DY;
			glColor3f(0, 0, 0);
			drawRightEye(EyeRX, EyeRY);
			glutPostRedisplay();
		}
		X = x;
		Y = y;
	}

}

void Scale(unsigned char key, int x, int y) {
	switch (key)
	{

	case'z':
		s += 0.1;
		glutPostRedisplay();
		break;
	case'x':
		s -= 0.1;
		glutPostRedisplay();
		break;
	}
}

void Rotate(int key, int x, int y) {
	switch (key)
	{
	case 101:
		theta += 5.0;
		glutPostRedisplay();
		break;
	case 103:
		theta -= 5.0;
		glutPostRedisplay();
		break;
	}
}




void myMenu(int id) {
	switch (id)
	{
	case(2): {//打开反走样
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		break;
	}
	case(3): {
		glDisable(GL_BLEND);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		break;
	}
	default:
		break;
	}
}

void ChooseColor(int id) {
	switch (id)
	{
	case(0): {//black
		if (part = Hat) {
			glRenderMode(GL_RENDER);
			glColor3f(0, 0, 0);
			drawHat();
			glFlush();
		}
		break;
	}
	case(1): {//white

	}
	case(2): {//red
	}
	case(3): {//blue
	}
	case(4): {//green
	}
	default:
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char ** argv)
{
	/*初始化*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//单缓冲、RGB模式
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("Figure");//窗口标题
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(RenderScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(myMotion);
	glutKeyboardFunc(Scale);
	glutSpecialFunc(Rotate);

	//制作菜单

	int submenu = glutCreateMenu(ChooseColor);
	glutAddMenuEntry("Black", 0);
	glutAddMenuEntry("White", 1);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Green", 4);
	int mainmenu = glutCreateMenu(myMenu);
	glutAddSubMenu("选择颜色", submenu);
	glutAddMenuEntry("打开反走样", 2);
	glutAddMenuEntry("关闭反走样", 3);


	glutAttachMenu(GLUT_RIGHT_BUTTON);


	system("pause");
	glutMainLoop();




}




