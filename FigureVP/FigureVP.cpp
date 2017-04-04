// FigureVP.cpp : �������̨Ӧ�ó������ڵ㡣
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




//������
void drawFace() {
	//����
	int n = 200; double t;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		t = i*2.0*3.14159 / n;
		glVertex2f(2.2*cos(t), 2.2*sin(t) + 3.7);
	}
	glEnd();
	glBegin(GL_POLYGON);
	//����
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, 3.0);   glVertex2f(0, 2.9);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0, 2.9);   glVertex2f(-0.2, 3.0);
	glEnd();
	//���
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

void drawCloth() {//���·�������
	glBegin(GL_POLYGON);
	glVertex2f(1.1, 1.8);   glVertex2f(3, -3.4);
	glVertex2f(-3, -3.4);   glVertex2f(-1.1, 1.8);
	glEnd();
	glBegin(GL_POLYGON);//�ұߵ�����
	glVertex2f(3.5, 0.6);
	glVertex2f(3.5, -0.3);
	glVertex2f(1.2, 0.3);
	glVertex2f(1.2, 1.2);
	glEnd();
	glBegin(GL_POLYGON);//��ߵ�����
	glVertex2f(-3.5, 0.6);
	glVertex2f(-3.5, -0.3);
	glVertex2f(-1.2, 0.3);
	glVertex2f(-1.2, 1.2);
	glEnd();


}

void drawHat() {
	//ñ��	
	glBegin(GL_TRIANGLES);
	glVertex2f(-2.5, 4.4);  glVertex2f(0, 8.0);   glVertex2f(2.5, 4.4);
	glEnd();
}


void drawPants() {
	//�ұߵĿ���
	glBegin(GL_POLYGON);
	glVertex2f(1.5, -3.4);
	glVertex2f(0.5, -3.4);
	glVertex2f(0.5, -5.5);
	glVertex2f(1.5, -5.5);
	glEnd();
	//��ߵĿ���
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
		glLoadName(Hands);//����ͼԪ����
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
{//ʰȡ
	unsigned int i, j;
	GLuint names, *ptr;

	printf("hits=%d\n", hits);
	ptr = (GLuint *)buffer;
	//�����еĴ�������ѭ��
	for (i = 0; i < hits; i++)
	{
		names = *ptr;
		//�������Ƶ������������Ϣ
		ptr += 3;
		//������м�¼�е�ÿ������
		for (j = 0; j < names; j++)
		{
			if (*ptr == 0)
			{
				printf("ñ��\n");
				part = Hat;
			}
			else if (*ptr == 1)
			{
				printf("����\n");
				part = Clothes;
			}
			else if (*ptr == 2)
			{
				printf("����\n");
				part = Pants;
			}
			else if (*ptr == 3)
			{
				printf("Ь��\n");
				part = Shoes;
			}
			else if (*ptr == 4)
			{
				printf("��\n");
				part = Face;
			}
			else if (*ptr == 5)
			{
				printf("����\n");
				part = Body;
			}
			else if (*ptr == 6)
			{
				printf("����\n");
				part = LeftEye;
			}
			else if (*ptr == 7)
			{
				printf("����\n");
				part = RightEye;
			}

			else if (*ptr == 8)
			{
				printf("��\n");
				part = Hands;
			}
			//ѭ������һ�����м�¼
			ptr++;
		}
	}
	printf("part:%d\n", part);
}

void Mouse(int button, int state, int x, int y) {
	GLuint SelectBuf[SIZE];//����һ������ѡ����������
	GLint hits;
	GLint viewport[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LEFT_DOWN = true;
		X = x;
		Y = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		glGetIntegerv(GL_VIEWPORT, viewport);//����һ���۲�ռ�
		glSelectBuffer(SIZE, SelectBuf); //����OpenGL��ʼ�� selectbuffer
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(0);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();//���浱ǰ����ѹ��ջ�У�
		glLoadIdentity();//���õ�ǰ�任����Ϊ��λ����
		gluPickMatrix(x, viewport[3] - y, 2.0, 2.0, viewport);//����һ��ʰȡ���Ӵ������浽viewport���У�Ϊʲô��viewport[3] - y������
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
		GLfloat OriginY = 10 - (GLfloat)Y * 20 / (GLfloat)WindowHeight;//��ʼ��X,Y���Ӵ����λ��
		GLfloat MovedX = -10 + (GLfloat)x * 20 / (GLfloat)WindowWidth;
		GLfloat MovedY = 10 - (GLfloat)y * 20 / (GLfloat)WindowWidth;//����ƶ�����λ�����Ӵ����λ�ã������Ǵ���Ļ���굽�Ӵ������ת��
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
	case(2): {//�򿪷�����
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
	/*��ʼ��*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//�����塢RGBģʽ
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("Figure");//���ڱ���
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(RenderScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(myMotion);
	glutKeyboardFunc(Scale);
	glutSpecialFunc(Rotate);

	//�����˵�

	int submenu = glutCreateMenu(ChooseColor);
	glutAddMenuEntry("Black", 0);
	glutAddMenuEntry("White", 1);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Green", 4);
	int mainmenu = glutCreateMenu(myMenu);
	glutAddSubMenu("ѡ����ɫ", submenu);
	glutAddMenuEntry("�򿪷�����", 2);
	glutAddMenuEntry("�رշ�����", 3);


	glutAttachMenu(GLUT_RIGHT_BUTTON);


	system("pause");
	glutMainLoop();




}




