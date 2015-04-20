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

	double sm = 1;//.15;

	width = w;
	height = h;

//glOrtho

	//glFrustum(-maxpr*sm, maxar*sm, -maxbr*sm, maxbr*sm, fz+sun.radius-10, fz+sun.radius);
	glFrustum(-maxpr*sm, maxar*sm, -maxbr*sm, maxbr*sm, fz, fz+sun.radius);
//glFrustum(-maxpr*GLD*sm, maxar*GLD*sm, -maxbr*GLD*sm, maxbr*GLD*sm, fz, fz+sun.radius);
//	printf("Sun radius %lf - Mercury aphelion %lf \n", sun.radius, planets[0].aphelion);
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
	     my_x+=sin(M_PI/180*(my_angle + 90));
	     my_z+=cos(M_PI/180*(my_angle + 90));
	     break;
	 case 'a': 
	     my_x-=sin(M_PI/180*(my_angle + 90));
	     my_z-=cos(M_PI/180*(my_angle + 90));
	     break;
	 case 'w':
	     my_x -= sin((M_PI/180.0)*my_angle);
	     my_z -= cos((M_PI/180.0)*my_angle);
	     break;
	 case 's':
	     my_x += sin((M_PI/180.0)*my_angle);
	     my_z += cos((M_PI/180.0)*my_angle);
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

    void drawScene(void)
    {
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

	//glScalef(1.0,1.0,1.0/SFAT);
	// Map the background texture onto a rectangle parallel to the xy-plane.
    
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);        
//    orange->set();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); 
	glVertex3f(-maxpr, -maxbr, 0); 
	glTexCoord2f(1.0, 0.0); 
	glVertex3f(maxar, -maxbr, 0);
	glTexCoord2f(1.0, 1.0); 
	glVertex3f(maxar, maxbr, 0);
	glTexCoord2f(0.0, 1.0); 
	glVertex3f(-maxpr,maxbr , 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	sun.draw();

	int i;
	for (i=0; i<PLANETS; i++){   
	    planets[i].draw();
	}
	glutSwapBuffers();
    }

};
