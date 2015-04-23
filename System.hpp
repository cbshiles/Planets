#include "TextRead.hpp"

#define GLD 0.61803398875

struct System{ //Solar system

    vector<Planet> planets;
    Sun sun;
    double maxpr, maxar, maxbr, maxpd, fz, pt;

    System(const char* filen): planets(read_planets(filen)),
			       maxpr(0), maxar(0), maxbr(0), maxpd(0)
    {
	sun.radius = 695800;
	sun.color = sunc;

	int i; Planet* pl = &planets[0];

	fz = sun.radius/GLD;

	for (i=0; i<PLANETS; i++){
	    pl->calculate();
	    if (pl->pr > maxpr) maxpr = pl->pr;
	    if (pl->ar > maxar) maxar = pl->ar;
	    if (pl->br > maxbr) maxbr = pl->br;
	    if (pl->period > maxpd) maxpd = pl->period;
	    pl++;
	}
	pt = maxpd/144000.0; //144000 ticks is 2 hours
	printf("MAXPD: %lf PT: %lf",maxpd,pt);
	pl = &planets[0];
	for (i=0; i<PLANETS; i++){
	    pl->calc2(pt);
	    pl++;
	}	
    }

//     void resize(int w, int h)
//     {
// 	glViewport(0, 0, w, h);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();

// 	double sm = 1.05;

// 	width = w;
// 	height = h;

// /*
// The bounds are -maxpr to maxar; -maxbr to maxbr (all-ways times GLD)
// sm is our zooom variable, tells us how deep in we are
//  */

// 	glFrustum(-maxpr*GLD*sm, maxar*GLD*sm, -maxbr*GLD*sm, maxbr*GLD*sm, fz, fz+sun.radius);

// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();

//     }
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

    double k = 0;

    if (my_x+k>sz) my_x = sz;
    else if (my_x-k<-sz) my_x = -sz;


    if (my_y+k>sz) my_y = sz;
    else if (my_y-k<-sz) my_y = -sz;

    if (my_z+k>sz) my_z = sz;
    else if (my_z-k<-sz) my_z = -sz;


    glutPostRedisplay();
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

    white->set(); //cuz

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

// The bounds are -maxpr to maxar; -maxbr to maxbr (all-ways times GLD)
// sm is our zooom variable, tells us how deep in we are

    glPushMatrix();

    double xrat = 2*sz/(maxpr+maxar);
    double yrat = sz/maxbr;
    double zrat = sz/sun.radius;

    glTranslatef(0,0,-sz/2);

    glScalef(xrat,yrat,yrat);

	sun.draw();

	int i;
	for (i=0; i<PLANETS; i++){   
	    planets[i].draw();
	}

	glPopMatrix();
	glutSwapBuffers();
    }

};
