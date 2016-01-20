/***************
Name: Scott McKeefer
Course: CSCE 4230
Assignment: Program 5 - prog5_McKeefer.c
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

const GLint k = 40;
int width = 500, height = 500;
bool rotx = false, roty = false;
GLfloat xrot = 1, yrot = 1;
GLint indv;
GLint indt;
GLint NV;
GLint NT;
GLfloat size = .01;
GLfloat amount = .01;
GLint i1, i2, i3;
GLfloat v[5000000][3];
GLfloat vn[5000000][3];
unsigned int ltri[5000000][3];
GLfloat tn[3];

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (rotx)
		glRotatef((GLfloat)xrot, 1.0, 0.0, 0.0);
	if (roty)
		glRotatef((GLfloat)yrot, 0.0, 1.0, 0.0);
	glDrawElements(GL_TRIANGLES, NT*3, GL_UNSIGNED_INT, ltri);
	glutSwapBuffers();
}

GLfloat f(GLfloat x, GLfloat y){
	GLfloat xCom = (pow((80.0f * x) - 40.0f, 2));
	GLfloat yCom = (pow((90.0f * y) - 45.0f, 2));

	GLfloat expCom = -.04f * sqrt(xCom + yCom);
	GLfloat cosCom = .15f * sqrt(xCom + yCom);

	GLfloat result = .5f * exp(expCom) * cos(cosCom);

	return result;

}

void normalize(GLfloat *vector){
	GLfloat lenght = sqrtf((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));

	vector[0] = vector[0] / lenght;
	vector[1] = vector[1] / lenght;
	vector[2] = vector[2] / lenght;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	//lights 
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE | GL_NORMAL_ARRAY_POINTER | GL_LIGHTING | GL_COLOR_MATERIAL);
	

	GLfloat h, y, x;
	GLint i, j;
	NV = (k+1) * (k+1);
	NT = 2 * (k*k);

	//store vertices
	h = 1.0 / k;
	indv = 0;
	for (j = 0; j <= k; j++){
		y = j * h;
		for (i = 0; i <= k; i++){
			x = i * h;
			v[indv][0] = x;
			v[indv][1] = y;
			v[indv][2] = f(x,y);
			indv++;
		}
	}

	//indv indexes the upper right corner of a cell
	indt = 0;
	for (j = 1; j <= k; j++){
		for (i = 1; i <= k; i++){
			indv = j * (k + 1) + i;
			ltri[indt][0] = indv - k - 2;
			ltri[indt][1] = indv - k - 1;
			ltri[indt][2] = indv;
			ltri[indt+1][0] = indv - k - 2;
			ltri[indt+1][1] = indv;
			ltri[indt+1][2] = indv - 1;
			indt = indt + 2;
		}
	}

	//initialize nomrals
	for (indv = 0; indv <= (NV - 1); indv++){
		vn[indv][0] = 0;
		vn[indv][1] = 0;
		vn[indv][2] = 0;
	}

	//add triangles normals to vector n ormals
	for (indt = 0; indt <= NT-1; indt++){
		i1 = ltri[indt][0];
		i2 = ltri[indt][1];
		i3 = ltri[indt][2];
		tn[0] = (v[i2][1] - v[i1][1])*(v[i3][2] - v[i1][2]) - (v[i2][2] - v[i1][2])*(v[i3][1] - v[i1][1]);
		tn[1] = (v[i2][2] - v[i1][2])*(v[i3][0] - v[i1][0]) - (v[i2][0] - v[i1][0])*(v[i3][2] - v[i1][2]);
		tn[2] = (v[i2][0] - v[i1][0])*(v[i3][1] - v[i1][1]) - (v[i2][1] - v[i1][1])*(v[i3][0] - v[i1][0]);
		normalize(tn);
		vn[i1][0] += tn[0]; vn[i1][1] += tn[1]; vn[i1][2] += tn[2];
		vn[i2][0] += tn[0]; vn[i2][1] += tn[1]; vn[i2][2] += tn[2];
		vn[i3][0] += tn[0]; vn[i3][1] += tn[1]; vn[i3][2] += tn[2];
	}

	//normalize vectex normals
	for (indv = 0; indv <= NV - 1; indv++){
		normalize(vn[indv]);
	}

	glEnable(GL_DEPTH_TEST);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 3*sizeof(GLfloat), v);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 3*sizeof(GLfloat), vn);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5 + (size + amount), 0.5 - (size + amount), -0.5 + (size + amount), 0.5 - (size + amount), 1.0, 7.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.5, -0.5, -2.0);
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
		amount = amount + .01;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 2:
		amount = amount - .01;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 3:
		if (yrot < 0)
			yrot = -yrot;
		roty = true;
		rotx = false;
		glutPostRedisplay();
		break;
	case 4:
		if (yrot > 0)
			yrot = -yrot;
		roty = true;
		rotx = false;
		glutPostRedisplay();
		break;
		break;
	case 5:
		if (xrot < 0)
			xrot = -xrot;
		rotx = true;
		roty = false;
		glutPostRedisplay();
		break;
	case 6:
		if (xrot > 0)
			xrot = -xrot;
		rotx = true;
		roty = false;
		glutPostRedisplay();
		break;
	case 7:
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
	case 'l':
	case 'L':
		mainMenu(3);
		break;
	case 'k':
	case 'K':
		mainMenu(4);
		break;
	case '.':
	case '>':
		mainMenu(5);
		break;
	case ',':
	case '<':
		mainMenu(6);
		break;
	case 27:
		mainMenu(7);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutCreateMenu(mainMenu);
		glutAddMenuEntry("+: Zoom In", 1);
		glutAddMenuEntry("-: Zoom Out", 2);
		glutAddMenuEntry("L: Rotate Y+", 3);
		glutAddMenuEntry("K: Rotate Y-", 4);
		glutAddMenuEntry(">: Rotate X+", 5);
		glutAddMenuEntry("<: Rotate X-", 6);
		glutAddMenuEntry("Exit", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}