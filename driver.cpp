#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

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

void setup(void)
{    
    glClearColor(1, 1, 1, 0);


//    glGenTextures(8, textureid);

    // Specify how texture values combine with current surface color values.
    //  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

    //loadExternalTextures();
    // Turn on OpenGL texturing.
    //glEnable(GL_TEXTURE_2D);

    // glEnable(GL_LIGHTING); // Re-enable lighting.

    // glEnable(GL_COLOR_MATERIAL);

    // // color response coming from glColor3f
    // glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // // glColorMaterial(GL_FRONT, GL_AMBIENT);
    // // glColorMaterial(GL_FRONT, GL_DIFFUSE);
    // // glColorMaterial(GL_FRONT, GL_SPECULAR);


    // // set up lighting
    // float lightAmb[] = { 0., 0., 0., 1.0 };
    // float lightDif[] = { 1.0, 1.0, 1.0, 1.0 };
    // float lightSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    // float lightZero[] = { 0, 0, 0, 1 };
    // float glb = 0.5;
    // float globAmb[] = { glb,glb,glb,1.0};

   
    // // Light0 properties.
    // glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    // //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZero); // Global ambient light.

    // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint
    // glEnable(GL_LIGHT0); // Enable particular light source.

    // // material properties
    // // float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    // float matSpec[] = {.2,.2,.2,1};
    // float matAmb[] = {1.0, 1.0, 1.0, 1.0};
    // float matDiff[] = {1.0, 1.0, 1.0, 1.0};
    // float matShine[] = {50.0};

    // glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    // glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
}

int main(int argc, char **argv){

    glutInit(&argc, argv);
    sys =  new System("../data_sheet.txt");

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
    glutInitWindowSize(1250, 800);
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("The Planets");
    glutDisplayFunc(drawScene); 
    glutReshapeFunc(resize);  
    glutKeyboardFunc(keyInput);
    glewExperimental = GL_TRUE;
    glewInit();

    setup(); 
    glutTimerFunc(0,tick,0);   
    glutMainLoop(); 

    return 0;
}
//    for (int i =0; i<PLANETS; i++)
//	planets[i].print();
