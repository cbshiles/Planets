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

double rads = M_PI/180.0;
double sz = 124;

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

        my_x - 5*sin((rads) * my_angle),
        my_y - 5*cos((rads) * my_angle_y),
        my_z - 5*cos((rads) * my_angle),

        0,
        1,
        0);


    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);

    //create a box around the current viewpoint
    //front
    glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sz, -sz, sz);
    glTexCoord2f(1, 0.0);
    glVertex3f(sz, -sz, sz);
    glTexCoord2f(1, 1);
    glVertex3f(sz, sz, sz);
    glTexCoord2f(0.0, 1);
    glVertex3f(-sz, sz, sz);
    glEnd();

    //bottom
    glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sz, -sz, sz);
    glTexCoord2f(1, 0.0);
    glVertex3f(sz, -sz, sz);
    glTexCoord2f(1, 1);
    glVertex3f(sz, -sz, -sz);
    glTexCoord2f(0.0, 1);
    glVertex3f(-sz, -sz, -sz);
    glEnd();

    //top
    glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sz, sz, sz);
    glTexCoord2f(1, 0.0);
    glVertex3f(sz, sz, sz);
    glTexCoord2f(1, 1);
    glVertex3f(sz, sz, -sz);
    glTexCoord2f(0.0, 1);
    glVertex3f(-sz, sz, -sz);
    glEnd();

    //left
    glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sz, -sz, sz);
    glTexCoord2f(1, 0.0);
    glVertex3f(-sz, sz, sz);
    glTexCoord2f(1, 1);
    glVertex3f(-sz, sz, -sz);;
    glTexCoord2f(0.0, 1);
    glVertex3f(-sz, -sz, -sz);
    glEnd();

    //right
    glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(sz, sz, sz);
    glTexCoord2f(1, 0.0);
    glVertex3f(sz, -sz, sz);
    glTexCoord2f(1, 1);
    glVertex3f(sz, -sz, -sz);;
    glTexCoord2f(0.0, 1);
    glVertex3f(sz, sz, -sz);
    glEnd();

    //back
    glBindTexture(GL_TEXTURE_2D, externalTextures[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sz, -sz, -sz);
    glTexCoord2f(1, 0.0);
    glVertex3f(sz, -sz, -sz);
    glTexCoord2f(1, 1);
    glVertex3f(sz, sz, -sz);
    glTexCoord2f(0.0, 1);
    glVertex3f(-sz, sz, -sz);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 0, 1);
    //glTranslatef(0, 0, -20);
    //  glutSolidSphere(5, 50, 50);

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
    glGenTextures(1, externalTextures);
    loadBackgroundTexture();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    float aspect = w*1.0/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, aspect, 0.1, 2*sz*1.414);//250);
    width=w;
    height=h;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setPos(double ang){
    ang += my_angle;
    my_x += sin(rads*ang);
    my_z += cos(rads*ang);
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
	 setPos(90);
	 break;
     case 'a':
	 setPos(270);
	 break;
     case 'w':
	 setPos(180);
	 break;
     case 's':
	 setPos(0);
	 break;
    }

    if (my_angle > 360.0) my_angle -= 360;
    if (my_angle < 0) my_angle += 360;

    if (my_x+5>sz) my_x = sz;
    else if (my_x-5<-sz) my_x = -sz;


    if (my_y+5>sz) my_y = sz;
    else if (my_y-5<-sz) my_y = -sz;

    if (my_z+5>sz) my_z = sz;
    else if (my_z-5<-sz) my_z = -sz;


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
    if (last_mouse_x<20) my_angle+=0.5;
    if (last_mouse_x>480) my_angle-=0.5;

    if (my_angle > 360.0) my_angle -= 360;
    if (my_angle < 0) my_angle += 360;

    //up down
    if (last_mouse_y>20) my_angle_y+=0.5;
    if (last_mouse_y<480) my_angle_y-=0.5;

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

    setup();

    glutMainLoop();
}
