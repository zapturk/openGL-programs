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
GLfloat l = 4.0;
GLfloat a = 1.3*8;
GLfloat x = -9.0;
GLfloat tSpeed = 0.0;
GLfloat RADIANS = 180.0 / 3.14159265359;
GLfloat speed;
int play = 0;
int playSpeed = 2;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	//makes a trapazoid
	glTranslatef(x, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(0.0, 8.0, 0.0);
		glVertex3f(1.0, 9.0, 0.0);
		glVertex3f(2.0, 9.0, 0.0);
		glVertex3f(3.0, 8.0, 0.0);
	glEnd();
	glTranslatef(-x, 0, 0);

	//make a pintagon line loop
	glTranslatef(-x, 0, 0);
	glColor3f(0.5, 0.0, 1.0);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, -8.0, 0.0);
		glVertex3f(-1.0, -7.0, 0.0);
		glVertex3f(-2.0, -8.0, 0.0);
		glVertex3f(-1.5, -9.0, 0.0);
		glVertex3f(-0.5, -9.0, 0.0);
	glEnd();
	glTranslatef(x, 0, 0);

	glRotatef(spin, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, .0);
	glBegin(GL_TRIANGLES);
		//right triangle
		glVertex3f(6.0, 0.0, 0.0);
		glVertex3f(7.0, 0.5, 0.0);
		glVertex3f(7.0, -0.5, 0.0);

		glVertex3f(7.0, 0.5, 0.0);
		glVertex3f(8.0, 1, 0.0);
		glVertex3f(8.0, 0.0, 0.0);

		glVertex3f(7.0, -0.5, 0.0);
		glVertex3f(8.0, -1, 0.0);
		glVertex3f(8.0, 0.0, 0.0);

		//left triangle
		glVertex3f(-6.0, 0.0, 0.0);
		glVertex3f(-7.0, 0.5, 0.0);
		glVertex3f(-7.0, -0.5, 0.0);

		glVertex3f(-7.0, 0.5, 0.0);
		glVertex3f(-8.0, 1, 0.0);
		glVertex3f(-8.0, 0.0, 0.0);

		glVertex3f(-7.0, -0.5, 0.0);
		glVertex3f(-8.0, -1, 0.0);
		glVertex3f(-8.0, 0.0, 0.0);
	glEnd();
	glRotatef(-spin, 1.0, 0.0, 0.0);
	
	//line segment of width 2 for the wire
	glRotatef(-spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, -l - 1, 0);
	glEnd();

	//make an arrowhead in the middle
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-.5, .5, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(.5, .5, 0.0);
	glEnd();
	
	//pivot point
	glTranslated(0.0, -l - 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(7.0);
	glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glRotatef(spin, 0.0, 0.0, 1.0);

	//line to connect the arrow
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, -l, 0.0);
	glEnd();

	//makes the arrow
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_POLYGON);
		glVertex3f(r, -l, 0);
		glVertex3f(0, -l - r, 0);
		glVertex3f(0, -l - .5, 0);
		glVertex3f(-r, -l - .5, 0);
		glVertex3f(-r, -l + .5, 0);
		glVertex3f(0, -l + .5, 0);
		glVertex3f(0, -l + r, 0);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void spinDisplay(void)
{
	//anagle speed
	spin = spin + speed;
	if (spin > 360.0)
		spin = spin - 360.0;

	//traslation speed
	x = x + tSpeed;
	if (x > 9.0)
		x = -9.0;
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
	glOrtho(-a, a, -a, a, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			speed = 4.0;
			tSpeed = 0.4;
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
		tSpeed = 0.2;
		play = 0;
		playSpeed = 1;
		glutIdleFunc(spinDisplay);
		break;
	case 2:
		speed = 4.0;
		tSpeed = 0.4;
		play = 0;
		playSpeed = 2;
		glutIdleFunc(spinDisplay);
		break;
	case 3:
		speed = 6.0;
		tSpeed = 0.6;
		play = 0;
		playSpeed = 3;
		glutIdleFunc(spinDisplay);
		break;
	case 4:
		if (play == 0){
			glutIdleFunc(NULL);
			play = 1;
		}
		else if (play == 1){
			speed = playSpeed * 2.0;
			tSpeed = playSpeed * 0.2;
			play = 0;
			glutIdleFunc(spinDisplay);
		}
		
		break;
	case 5:
		exit(0);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		mainMenu(1);
		break;
	case '2':
		mainMenu(2);
		break;
	case '3':
		mainMenu(3);
		break;
	case 32:
		mainMenu(4);
		break;
	case 27:
		mainMenu(5);
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
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutCreateMenu(mainMenu);
		glutAddMenuEntry("1: Slow Speed", 1);
		glutAddMenuEntry("2: Normal Speed", 2);
		glutAddMenuEntry("3: Fast Speed", 3);
		glutAddMenuEntry("Space: Stop/Resume", 4);
		glutAddMenuEntry("ESC: Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}