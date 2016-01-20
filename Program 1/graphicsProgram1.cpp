/*
* Copyright (c) 1993-1997, Silicon Graphics, Inc.
* ALL RIGHTS RESERVED
*
*/

/*
* hello.c
* This is a simple, introductory OpenGL program.
*/
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <time.h>

GLfloat X0, X1 = 0.25f, X2 = 0.75f, X3 = 0.5f;
GLfloat Y0, Y1 = 0.25f, Y2 = 0.25f, Y3 = 0.75f;

void display(void)
{
   /* clear all pixels  */
   glClear(GL_COLOR_BUFFER_BIT);

   /* draw white polygon (rectangle) with corners at
   * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
   */
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POINTS);
   glVertex3f(X1, Y1, 0.0); // bottom left corner
   glVertex3f(X2, Y2, 0.0); // bottom right corner
   glVertex3f(X3, Y3, 0.0); // top of triangle

   X0 = ((rand() % 100) + 1) / 100.0; // initial x posstion 
   Y0 = ((rand() % 100) + 1) / 100.0; // initial y posstion 

   int n = 60000;
   for(int i = 0; i < n; i++){
      int num;
      num = rand() % 3;
      
      if (num == 0){
         if (X0 > X1){
            X0 = X0 - ((X0 - X1) / 2);
         }
         else if (X0 < X1){
            X0 = X0 + ((X1 - X0) / 2);
         }
         if (Y0 > Y1){
            Y0 = Y0 - ((Y0 - Y1) / 2);
         }
         else if (Y0 < Y1){
            Y0 = Y0 + ((Y1 - Y0) / 2);
         }
      }
      else if (num == 1){
         if (X0 > X2){
            X0 = X0 - ((X0 - X2) / 2);
         }
         else if (X0 < X2){
            X0 = X0 + ((X2 - X0) / 2);
         }
         if (Y0 > Y2){
            Y0 = Y0 - ((Y0 - Y2) / 2);
         }
         else if (Y0 < Y2){
            Y0 = Y0 + ((Y2 - Y0) / 2);
         }
      }
      else if (num == 2){
         if (X0 > X3){
            X0 = X0 - ((X0 - X3) / 2);
         }
         else if (X0 < X3){
            X0 = X0 + ((X3 - X0) / 2);
         }
         if (Y0 > Y3){
            Y0 = Y0 - ((Y0 - Y3) / 2);
         }
         else if (Y0 < Y3){
            Y0 = Y0 + ((Y3 - Y0) / 2);
         }
      }

      glVertex3f(X0, Y0, 0.0);
   }
   glEnd();

   /* don't wait!
   * start processing buffered OpenGL routines
   */
   glFlush();
}

void init(void)
{
   /* select clearing color   */
   glClearColor(0.0, 0.0, 0.0, 0.0);

   /* initialize viewing values
   */ 
   glViewport(100, 100, 500, 500);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

/*
* Declare initial window size, position, and display mode

* (single buffer and RGBA).  Open window with "hello"
* in its title bar.  Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{
   srand(time(NULL));
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("hello");
   init();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
