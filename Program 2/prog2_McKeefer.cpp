/***************
Name: Scott McKeefer
Course: CSCE 4230
Assignment: Program 2 - prog2_McKeefer.c
Due Date: February 19, 2015
****************/

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>



static GLfloat spin = 0.0;
GLfloat r = 1.0;
GLfloat l = 8.0;
GLfloat a = 1.3*l;
GLfloat RADIANS = 180.0 / 3.14159265359;
GLfloat speed;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	
	
	
	//line segment of width 2 for the wire
	glColor3f(1.0, 0.0, 1.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0, -l, 0);
	glEnd();

	//5-pixel dot for the anchor point
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();


	//makes the hexagon
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_POLYGON);
	glVertex3f(r, -l, 0);
	glVertex3f(r - cos(RADIANS * 60.0), -l - r/*sin(RADIANS * 60.0)*/, 0);
	glVertex3f(-r + cos(RADIANS * 60.0), -l - r/*sin(RADIANS * 60.0)*/, 0);
	glVertex3f(-r, -l, 0);
	glVertex3f(-r + cos(RADIANS * 60.0), -l + r/*sin(RADIANS * 60.0)*/, 0);
	glVertex3f(r - cos(RADIANS * 60.0), -l + r/*sin(RADIANS * 60.0)*/, 0);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void spinDisplay(void)
{
	spin = spin + speed;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-a, a, -a, a, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			speed = 2.0;
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void mainMenu(int id){
	switch (id){
	case 1:
		speed = 2.0;
		glutIdleFunc(spinDisplay);
		break;
	case 2:
		speed = -2.0;
		glutIdleFunc(spinDisplay);
		break;
	case 3:
		glutIdleFunc(NULL);
		break;
	case 4:
		if (speed < 20.0 && speed >= 1.0)
			speed = speed + 0.5;
		else if (speed > -20.0 && speed <= -1.0)
			speed = speed - 0.5;
		break;
	case 5:
		if (speed <= 20.0 && speed > 1.0)
			speed = speed - 0.5;
		else if (speed >= -20.0 && speed < -1.0)
			speed = speed + 0.5;
		break;
	case 6:
		exit(0);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '=':
	case '+':
		mainMenu(1);
		break;
	case '-':
		mainMenu(2);
		break;
	case 32:
		mainMenu(3);
		break;
	case '.':
	case '>':
		mainMenu(4);
		break;
	case ',':
	case '<':
		mainMenu(5);
		break;
	case 27:
		mainMenu(6);
		break;
	default:
		break;
	}
}

/*
*  Request double buffer display mode.
*  Register mouse input callback functions
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutCreateMenu(mainMenu);
		glutAddMenuEntry("Rotate Counter Clockwise", 1);
		glutAddMenuEntry("Rotate Clockwise", 2);
		glutAddMenuEntry("Stop Rotation", 3);
		glutAddMenuEntry("Speed Up", 4);
		glutAddMenuEntry("Slow Down", 5);
		glutAddMenuEntry("Exit", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}