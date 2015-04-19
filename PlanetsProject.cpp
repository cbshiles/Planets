//
// PlanetsProject.cpp
// By Brenan Shiles, David Tulis, and Robby Harris

// to define exit(0)
#include <stdlib.h>

#ifdef __APPLE__
#  include <GL/glew.h>

#include <GLUT/glut.h>
#  include <GLUT/glut.h>

#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "getbmp.h"

//mouse coordinates
double last_mouse_x;
double last_mouse_y;

//size of our openGL window
int width, height;

//global variables for camera motion
static float my_x=0;
static float my_y=0;
static float my_z=0;
static float my_angle=0;
static float my_angle_y=91;

static unsigned int externalTextures[1];


void loadBackgroundTexture()
{
		// Local storage for bmp image data.
		BitMapFile *image[1];

		image[0] = getbmp("background.bmp");

		// Bind background image to texture object internalTextures[0].
		glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

}

void drawScene(void)
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
    my_x,
    my_y,
    my_z,

    my_x - 5*sin((M_PI/180.0) * my_angle),
    my_y - 5*cos((M_PI/180.0) * my_angle_y),
    my_z - 5*cos((M_PI/180.0) * my_angle),

    0,
    1,
    0);

    //glColor3f(1, 1, 1);
    //create a box around the current viewpoint
    	//front
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, -100.0, 100.0);
		glTexCoord2f(1, 0.0); glVertex3f(100.0, -100.0, 100.0);
		glTexCoord2f(1, 1); glVertex3f(100.0, 100.0, 100.0);
		glTexCoord2f(0.0, 1); glVertex3f(-100.0, 100.0, 100.0);
	glEnd();

    //glColor3f(0, 1, 0);
	//bottom
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, -100.0, 100.0);
		glTexCoord2f(1, 0.0); glVertex3f(100.0, -100.0, 100.0);
		glTexCoord2f(1, 1); glVertex3f(100.0, -100.0, -100.0);
		glTexCoord2f(0.0, 1); glVertex3f(-100.0, -100.0, -100.0);
	glEnd();

    //glColor3f(0, 0, 1);
	//top
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, 100.0, 100.0);
		glTexCoord2f(1, 0.0); glVertex3f(100.0, 100.0, 100.0);
		glTexCoord2f(1, 1); glVertex3f(100.0, 100.0, -100.0);
		glTexCoord2f(0.0, 1); glVertex3f(-100.0, 100.0, -100.0);
	glEnd();

    //glColor3f(1, 1, 0); //purple
	//left
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, -100.0, 100.0);
		glTexCoord2f(1, 0.0); glVertex3f(-100.0, 100.0, 100.0);
		glTexCoord2f(1, 1); glVertex3f(-100.0, 100.0, -100.0);;
		glTexCoord2f(0.0, 1); glVertex3f(-100.0, -100.0, -100.0);
	glEnd();

    //glColor3f(1, 0, 1); //yellow
	//right
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(100.0, 100.0, 100.0);
		glTexCoord2f(1, 0.0); glVertex3f(100.0, -100.0, 100.0);
		glTexCoord2f(1, 1); glVertex3f(100.0, -100.0, -100.0);;
		glTexCoord2f(0.0, 1); glVertex3f(100.0, 100.0, -100.0);
	glEnd();

    //glColor3f(0, 1, 1); //cyan
	//back
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, -100.0, -100.0);
		glTexCoord2f(1, 0.0); glVertex3f(100.0, -100.0, -100.0);
		glTexCoord2f(1, 1); glVertex3f(100.0, 100.0, -100.0);
		glTexCoord2f(0.0, 1); glVertex3f(-100.0, 100.0, -100.0);
	glEnd();


    glColor3f(1, 1, 1);
    glTranslatef(0, 0, -20);
    glutSolidSphere(5, 50, 50);

    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset( 1, 1);

    //TEXTURES
    //glGenTextures(1, externalTextures);

		glPushMatrix();
		glTranslatef(0, 0, -100);
		loadBackgroundTexture();
		glPopMatrix();

		// Specify how texture values combine with current surface color values.
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// Turn on OpenGL texturing.
		glEnable(GL_TEXTURE_2D);

}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    float aspect = w*1.0/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, aspect, 0.1, 250);
		width=w;
		height=h;
		glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key)
   {
		case 27:                  // escape
			exit(0);
			break;
		case 'd':
			if(my_x < 100){
                my_x+=sin(M_PI/180*(my_angle + 90));
			}
			if(my_z < 100 && my_z > 0.1){
                my_z+=cos(M_PI/180*(my_angle + 90));
			}
			break;
		case 'a':
			if(my_x > -100){
                my_x-=sin(M_PI/180*(my_angle + 90));
			}
			if(my_z < -100 && my_z > 0.1){
                my_z-=cos(M_PI/180*(my_angle + 90));
			}
			break;
		case 'w':
            if(my_x < 100 && my_x > -100){
                my_x -= sin((M_PI/180.0)*my_angle);
            }
			if(my_z > -100){
                my_z -= cos((M_PI/180.0)*my_angle);
			}
			break;
		case 's':
            if(my_x < 100 && my_x > -100){
                my_x -= sin((M_PI/180.0)*my_angle);
            }
			if(my_z < 0.1)
			break;
   }

    if (my_angle > 360.0) my_angle -= 360;
    if (my_angle < 0) my_angle += 360;

    if (my_x>180)
    {
				my_x=180;
		}

		if (my_y>180) {
				my_y=180;
		}

		if (my_z>180) {
				my_z=180;
    }

    glutPostRedisplay();
}

//used to constantly update the global mouse variables with the position of the mouse
void trackMouse (int x, int y)
{
	last_mouse_x=x;
	last_mouse_y=height-y;
}

//moves the camera depending on the location of the mouse
void mouseMotion()
{
	//left right
	if (last_mouse_x<20) my_angle+=0.1;
	if (last_mouse_x>480) my_angle-=0.1;

	if (my_angle > 360.0) my_angle -= 360;
    if (my_angle < 0) my_angle += 360;

	//up down
	if (last_mouse_y>20) my_angle_y+=0.1;
	if (last_mouse_y<480) my_angle_y-=0.1;

	if (my_angle_y >= 180.0) my_angle_y = 180;
    if (my_angle_y < 75) my_angle_y = 75;

   glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("planets");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutPassiveMotionFunc(trackMouse);
	glutIdleFunc(mouseMotion);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
