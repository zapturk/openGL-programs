/***************
Name: Scott McKeefer
Course: CSCE 4230
Assignment: Program 7 - prog7_McKeefer.cpp
Due Date: May 5, 2015
****************/

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

GLfloat size = .01;
GLfloat amount = .01;
GLfloat tAmout = 0.0;
GLfloat height = 500.0;
GLfloat width = 500.0;

GLfloat p0[3] = { -8.0, -4.0, 0.0 };
GLfloat p1[3] = { -6.0, 4.0, 0.0 };
GLfloat p2[3] = { -2.0, -4.0, 0.0 };
GLfloat p3[3] = { 0.0, -4.0, 0.0 };
GLfloat p4[3] = { 2.0, -4.0, 0.0 };
GLfloat p5[3] = { 2.0, 4.0, 0.0 };
GLfloat p6[3] = { 4.0, -4.0, 0.0 };
GLint viewport[4];
GLdouble modelview[16], projection[16];
int btn;
int startMouseX = 0;
int startMouseY = 0;
int startTransX = 0;
int startTransY = 0;
int curTransX = 0;
int curTransY = 0;

GLfloat ctrlpoints[7][3] = {
	{ p0[0], p0[1], p0[2] }, { p1[0], p1[1], p1[2] },
	{ p2[0], p2[1], p2[2] }, { p3[0], p3[1], p3[2] }, { p4[0], p4[1], p4[2] },
	{ p5[0], p5[1], p5[2] }, { p6[0], p6[1], p6[2] } };

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);// first curve
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[3][0]);// secconed curve
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();

	/* The following code displays the control points as dots. */
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 7; i++){
		glVertex3fv(&ctrlpoints[i][0]);
	}
	glEnd();
	glFlush();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0 + (size + amount), 10.0 - (size + amount), (-10.0*(GLfloat)h / (GLfloat)w) + (size + amount), (10.0*(GLfloat)h / (GLfloat)w) - (size + amount), -10.0, 10.0);
	else
		glOrtho(-5.0*(GLfloat)w / (GLfloat)h, 5.0*(GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(tAmout, 0, 0);
}

void mouse(int button, int state, int x, int y)
{
	GLdouble tempX[1], tempY[1], tempZ[1];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	switch (button) {
	case GLUT_LEFT_BUTTON:
		gluUnProject(x, y, 0.0, modelview, projection, viewport, tempX, tempY, tempZ);
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
		amount = amount + .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 2:
		amount = amount - .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 3:
		tAmout = tAmout + .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 4:
		tAmout = tAmout - .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		amount = amount + .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		amount = amount - .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		tAmout = tAmout + .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		tAmout = tAmout - .05;
		reshape(width, height);
		glutPostRedisplay();
		break;
	default:
		break;
	}
	
}

void keyboard(unsigned char key, int x, int y)
{
	mainMenu(key);
}

void MotionCallback(int x, int y)
{
	int curMouseX = x;
	int curMouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
	if (btn == GLUT_LEFT_BUTTON)
	{
		curTransX = startTransX + (curMouseX - startMouseX);
		curTransY = startTransY + (curMouseY - startMouseY);
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(height, width);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMotionFunc(MotionCallback);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(processSpecialKeys);
	glutCreateMenu(mainMenu);
		glutAddMenuEntry("UP ARROW: Zoom In", 1);
		glutAddMenuEntry("DOWN ARROW: Zoom Out", 2);
		glutAddMenuEntry("RIGHT ARROW: Move To The Right", 3);
		glutAddMenuEntry("LEFT ARROW: Move To The Left", 4);
		glutAddMenuEntry("Esc: Exit", 27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
