/***************
Name: Scott McKeefer
Course: CSCE 4230
Assignment: Program 4 - prog4_McKeefer.c
Due Date: March 26, 2015
****************/

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

static int shoulder = 0, elbow = 0, hand = 0, xrot = 0, yrot = 0;
int  solid = 0;
bool view = true, rota = true;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glutInitDisplayMode(GLUT_DEPTH);
	if (rota){
		glRotatef(0.5, (GLfloat)xrot, 0.0, 0.0);
		glRotatef(0.5, 0.0, (GLfloat)yrot, 0.0);
	}

	glColor3d(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(-2.5, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(2.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(5.0, 1.0, 1.0);

	if (solid == 1)
		glutSolidCube(1.0);
	else if (solid == 0)
		glutWireCube(1.0);
	glPopMatrix();

	glColor3d(0.0, 1.0, 0.0);
	glTranslatef(2.5, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(2.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(4.0, 1.0, 1.0);

	if (solid == 1)
		glutSolidCube(1.0);
	else if (solid == 0)
		glutWireCube(1.0);
	glPopMatrix();
	
	glColor3d(1.0, 0.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 1.0, 1.0);

	if (solid == 1)
		glutSolidCube(1.0);
	else if (solid == 0)
		glutWireCube(1.0);
	glPopMatrix();
	
	glPopMatrix();
	glutSwapBuffers();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (view)
		glOrtho(-15.0, 15.0, -15.0, 15.0, 3.0, 15.0);
	else
		glFrustum(-15.0, 15.0, -15, 15.0, 3.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
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
		shoulder = (shoulder + 5) % 360;
		rota = false;
		glutPostRedisplay();
		break;
	case 2:
		shoulder = (shoulder - 5) % 360;
		rota = false;
		glutPostRedisplay();
		break;
	case 3:
		elbow = (elbow + 5) % 360;
		rota = false;
		glutPostRedisplay();
		break;
	case 4:
		elbow = (elbow - 5) % 360;
		rota = false;
		glutPostRedisplay();
		break;
	case 5:
		hand = (hand + 5) % 360;
		rota = false;
		glutPostRedisplay();
		break;
	case 6:
		hand = (hand - 5) % 360;
		rota = false;
		glutPostRedisplay();
		break;
	case 7:
		if (view)
			view = false;
		else
			view = true;
		rota = true;
		reshape(500, 500);
		glutPostRedisplay();
		break;
	case 8:
		if (solid == 0)
			solid = 1;
		else if (solid == 1)
			solid = 0;
		glutPostRedisplay();
		break;
	case 9:
		xrot = (xrot + 1) % 360;
		rota = true;
		glutPostRedisplay();
		break;
	case 10:
		xrot = (xrot - 1) % 360;
		rota = true;
		glutPostRedisplay();
		break;
	case 11:
		yrot = (yrot + 1) % 360;
		rota = true;
		glutPostRedisplay();
		break;
	case 12:
		yrot = (yrot - 1) % 360;
		rota = true;
		glutPostRedisplay();
		break;
	case 13:
		exit(0);
		break;
	default:
		break;
	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
		mainMenu(1);
		break;
	case 'S':
		mainMenu(2);
		break;
	case 'e':
		mainMenu(3);
		break;
	case 'E':
		mainMenu(4);
		break;
	case 'w':
		mainMenu(5);
		break;
	case 'W':
		mainMenu(6);
		break;
	case 'p':
	case 'P':
		mainMenu(7);
		break;
	case 'h':
	case 'H':
		mainMenu(8);
		break;
	case 'x':
		mainMenu(9);
		break;
	case 'X':
		mainMenu(10);
		break;
	case 'y':
		mainMenu(11);
		break;
	case 'Y':
		mainMenu(12);
		break;
	case 27:
		mainMenu(13);
		break;
	default:
		break;
	}
}

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
		glutAddMenuEntry("s: CCW Arm", 1);
		glutAddMenuEntry("S: CW Arm", 2);
		glutAddMenuEntry("e: CCW Forarm", 3);
		glutAddMenuEntry("E: CW Forarm", 4);
		glutAddMenuEntry("w: CCW Hand", 5);
		glutAddMenuEntry("W: CW Hand", 6);
		glutAddMenuEntry("p: Change Perspective", 7);
		glutAddMenuEntry("h: Wireframe/Solid", 8);
		glutAddMenuEntry("x: Increase xrot", 9);
		glutAddMenuEntry("X: Decrease xrot", 10);
		glutAddMenuEntry("y: Increase yrot", 11);
		glutAddMenuEntry("Y: Decrease yrot", 12);
		glutAddMenuEntry("ESC: Exit", 13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}