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
	sun.color = yellow;

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
	pt = maxpd/144000.0;
	pl = &planets[0];
	for (i=0; i<PLANETS; i++){
	    pl->calc2(pt);
	    pl++;
	}	
    }

    void resize(int w, int h)
    {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double sm = .25;
	maxpr *= sm;
	maxar *= sm;
	maxbr *= sm;

	glFrustum(-maxpr*GLD, maxar*GLD, -maxbr*GLD, maxbr*GLD, fz, fz+sun.radius);
//	printf("Sun radius %lf - Mercury aphelion %lf \n", sun.radius, planets[0].aphelion);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    }

// Keyboard input processing routine.
    void keyInput(unsigned char key, int x, int y)
    {
	switch(key) 
	{
	 case 27:
	     exit(0);
	     break;
	}
    }

void drawScene(void)
{
    glClearColor(.5, .0, .5, 0.0); 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // position the light
    //   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);  
//    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);    
    //  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);


    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glTranslatef(0, 0, -fz-sun.radius+1);


    glScalef(1.0,1.0,1.0/SFAT);
   // Map the background texture onto a rectangle parallel to the xy-plane.
//   glBindTexture(GL_TEXTURE_2D, textureid[7]);        
  glBegin(GL_POLYGON);
//   maxpr=maxpr*GLD;
//   maxar=maxar*GLD;
//   maxbr=maxbr*GLD;
// z=
  green->set();
   /* glTexCoord2f(0.0, 0.0); */ glVertex3f(-maxpr, -maxbr, 0); 
  black->set();
      /*    glTexCoord2f(1.0, 0.0); */ glVertex3f(maxar, -maxbr, 0);
  grey->set();
      /* glTexCoord2f(1.0, 1.0); */ glVertex3f(maxar, maxbr, 0);
  blue->set();
     /*  glTexCoord2f(0.0, 1.0); */ glVertex3f(-maxpr,maxbr , 0);
  glEnd();

   sun.draw();

   int i;
   for (i=0; i<PLANETS; i++){   
       planets[i].draw();
   }
   glutSwapBuffers();
}



};
