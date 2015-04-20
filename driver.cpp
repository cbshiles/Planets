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

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

static unsigned int externalTextures[1];

//size of our openGL window
int width, height;

//mouse coordinates
double last_mouse_x;
double last_mouse_y;

//global variables for camera motion
static float my_x=0;
static float my_y=0;
static float my_z=0;
static float my_angle=0;
static float my_angle_y=91;

#include "getbmp.h"
#include "System.hpp"

System* sys;

void resize(int w, int h){sys->resize(w,h);}

void keyInput(unsigned char key, int x, int y)
{sys->keyInput(key,x,y);}

void drawScene(void)
{sys->drawScene();}

void tick(int val)
{
    glutPostRedisplay(); // tell glut to redraw the window
    glutTimerFunc(50, tick, 0); // tell glut to call update again in 100 m
//50
}

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

// Initialization routine.
void setup(void) 
{
    glClearColor(.5, .0, .5, 0.0); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset( 1, 1);
    
    //TEXTURES
    glGenTextures(1, externalTextures);
    
    loadBackgroundTexture();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
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

int main(int argc, char **argv){

    glutInit(&argc, argv);
    sys =  new System("../data_sheet.txt");

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("The Planets");

    glutDisplayFunc(drawScene); 
    glutReshapeFunc(resize);  
    glutKeyboardFunc(keyInput);
    glutPassiveMotionFunc(trackMouse);
    glutIdleFunc(mouseMotion);

    glewExperimental = GL_TRUE;
    glewInit();

    setup(); 
    glutTimerFunc(0,tick,0);   
    glutMainLoop(); 

    return 0;
}
//    for (int i =0; i<PLANETS; i++)
//	planets[i].print();
