/***************
Name: Scott McKeefer
Course: CSCE 4230
Assignment: Program 6 - prog6_McKeefer.cpp
Due Date: April 23, 2015
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
GLfloat e = 12.5f;
bool smooth = true;
bool boundBox = false;
int rotXCou = 0, rotYCou = 0;
GLfloat zScale = 1.0f;
bool fill = true;


void drawBoundingBox(){
	GLfloat myVar = 0.5f;
	GLfloat zMax = 0.5f * zScale;
	GLfloat zMin = -0.23f * zScale;

	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);

	glVertex3f(myVar, myVar, zMax);
	glVertex3f(-myVar, myVar, zMax);
	glVertex3f(-myVar, -myVar, zMax);
	glVertex3f(myVar, -myVar, zMax);

	glVertex3f(myVar, myVar, zMin);
	glVertex3f(-myVar, myVar, zMin);
	glVertex3f(-myVar, -myVar, zMin);
	glVertex3f(myVar, -myVar, zMin);

	glVertex3f(myVar, myVar, zMax);
	glVertex3f(myVar, -myVar, zMax);
	glVertex3f(myVar, -myVar, zMin);
	glVertex3f(myVar, myVar, zMin);

	glVertex3f(-myVar, myVar, zMax);
	glVertex3f(-myVar, -myVar, zMax);
	glVertex3f(-myVar, -myVar, zMin);
	glVertex3f(-myVar, myVar, zMin);

	glVertex3f(myVar, myVar, zMax);
	glVertex3f(-myVar, myVar, zMax);
	glVertex3f(-myVar, myVar, zMin);
	glVertex3f(myVar, myVar, zMin);

	glVertex3f(myVar, -myVar, zMax);
	glVertex3f(-myVar, -myVar, zMax);
	glVertex3f(-myVar, -myVar, zMin);
	glVertex3f(myVar, -myVar, zMin);

	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0.5, 0.5, 0.0);
	if (rotx)
		glRotatef((GLfloat)xrot, 1.0, 0.0, 0.0);
	if (roty)
		glRotatef((GLfloat)yrot, 0.0, 1.0, 0.0);
	if (boundBox)
		drawBoundingBox();
	glTranslatef(-0.5, -0.5, 0.0);
	
	if (fill)// true filled, false line
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glEnable(GL_LIGHTING);
	if (smooth)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	glDrawElements(GL_TRIANGLES, NT * 3, GL_UNSIGNED_INT, ltri);
	
	glutSwapBuffers();
}

GLfloat f(GLfloat x, GLfloat y){
	GLfloat xCom = (pow((80.0f * x) - 40.0f, 2));
	GLfloat yCom = (pow((90.0f * y) - 45.0f, 2));

	GLfloat expCom = -.04f * sqrt(xCom + yCom);
	GLfloat cosCom = .15f * sqrt(xCom + yCom);

	GLfloat result = .5f * exp(expCom) * cos(cosCom);

	return result * zScale;

}

void normalize(GLfloat *vector){
	GLfloat lenght = sqrtf((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));

	vector[0] = vector[0] / lenght;
	vector[1] = vector[1] / lenght;
	vector[2] = vector[2] / lenght;
}

void initlights(void)
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 1.0, 2.0, 3.0, 0.0 };
	GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, e);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/*if (smooth)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);*/

	glEnable(GL_NORMALIZE | GL_NORMAL_ARRAY_POINTER | GL_COLOR_MATERIAL);

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

	//light 
	initlights();

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
	case 61:
	case 43:// zoom in
		amount = amount + .01;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 45:
	case 95:// zoom out 
		amount = amount - .01;
		reshape(width, height);
		glutPostRedisplay();
		break;
	case 108:
	case 76:// rotate y+
		if (yrot < 0)
			yrot = -yrot;
		roty = true;
		rotx = false;
		rotYCou++;
		glutPostRedisplay();
		break;
	case 107:
	case 75:// rotate y-
		if (yrot > 0)
			yrot = -yrot;
		roty = true;
		rotx = false;
		rotYCou--;
		glutPostRedisplay();
		break;
		break;
	case 46:
	case 62:// rotate x+
		if (xrot > 0)
			xrot = -xrot;
		roty = false;
		rotx = true;
		rotXCou++;
		glutPostRedisplay();
		break;
	case 44:
	case 60:// rotate x-
		if (xrot < 0)
			xrot = -xrot;
		roty = false;
		rotx = true;
		rotXCou--;
		glutPostRedisplay();
		break;
	case 98:// bound box off/on
		if (boundBox){
			boundBox = false;
			roty = false;
			rotx = false;
		}
		else{
			boundBox = true;
			roty = false;
			rotx = false;
		}
		glutPostRedisplay();
		break;
	case 100://scale down
		if (zScale > 0.5f)
			zScale = zScale / 2;
		roty = false;
		rotx = false;
		init();
		glutPostRedisplay();
		break;
	case 68://scale up
		if (zScale < 2.0f)
			zScale = zScale * 2;
		roty = false;
		rotx = false;
		init();
		glutPostRedisplay();
		break;
	case 101://Shininess Up
		e = e / 2.0f;
		roty = false;
		rotx = false;
		init();
		glutPostRedisplay();
		break;
	case 69://Shininess down
		e = e * 2.0f;
		roty = false;
		rotx = false;
		init();
		glutPostRedisplay();
		break;
	case 102:// wireframe toggle
		if (fill)
			fill = false;
		else
			fill = true;
		roty = false;
		rotx = false;
		glutPostRedisplay();
		break;
	case 115:// smooth toggle
		if (smooth)
			smooth = false;
		else
			smooth = true;
		init();
		roty = false;
		rotx = false;
		glutPostRedisplay();
		break;
	case 114:// reset
		amount = .01;
		fill = true;
		smooth = true;
		e = 5.0f;
		boundBox = false;
		zScale = 1.0f;
		init();
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

void keyboard(unsigned char key, int x, int y)
{
	mainMenu(key);
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
		glutAddMenuEntry("+: Zoom In", 61);
		glutAddMenuEntry("-: Zoom Out", 45);
		glutAddMenuEntry("L: Rotate Y+", 76);
		glutAddMenuEntry("K: Rotate Y-", 75);
		glutAddMenuEntry(">: Rotate X+", 62);
		glutAddMenuEntry("<: Rotate X-", 60);
		glutAddMenuEntry("b: Bounding Box", 98);
		glutAddMenuEntry("d: Scale Down", 100);
		glutAddMenuEntry("D: Scale Up", 68);
		glutAddMenuEntry("e: Shininess Up", 101);
		glutAddMenuEntry("E: Shininess Down", 69);
		glutAddMenuEntry("f: Fill/Wireframe", 102);
		glutAddMenuEntry("s: Smooth/Flat", 115);
		glutAddMenuEntry("r: Reset", 114);
		glutAddMenuEntry("Exit", 27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}