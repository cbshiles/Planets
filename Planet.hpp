#include "Color.hpp"

using namespace std;

#define SFAT 50.0
#define PFAT 200.0

#define PI 3.14159265

void fatSphere(double r){glutSolidSphere(r,50,50);}

double quadratic(double a, double b, double c, int choice){
    double z = b*b - 4*a*c;
    if (z < 0){
	printf("ERROR- Quadratic getting imaginary #s\n");
	return 0;
    }
    if (choice)
	return (-b + sqrt(z))/(2*a);
    else 
	return (-b - sqrt(z))/(2*a);
};

struct Sun {
    Color* color;
    double radius;

    void draw(){
	color->set();
	fatSphere(radius*SFAT);
    }
};


struct Planet {
    string name;
    Color* color;
    double radius, escape_v, dfromsun;
    double perihelion, aphelion;
    double period, orbital_v, inclination; //Orbital period, time for this planet to rotate sun
    double eccentricity, tilt;

    double pr, ar, a, b, br;
    double aoe; //area of ellipse
    double asw; //area swept per update
    double ax, ay, bx, by;
    int nx, ny;

    Planet(): color(white) {}

    void calculate(){
	pr = perihelion + radius;
	ar = aphelion + radius;
	a =  (perihelion + aphelion)/2;
	b = a*sqrt(1-eccentricity*eccentricity);
	br = b + radius;
	aoe = PI*a*b;

    }

    void calc2(double pt){
	printf("%lf\n",pt/period);
	asw = aoe * pt/period;
	ax = perihelion;
	printf("Ticks: %lf\n",aoe/asw);
	ay = 0;
	nx = ny = 1;
    }

    void draw(){
	color->set();
	glPushMatrix();
	glTranslatef(ax,ay,0);
	fatSphere(radius*PFAT);
	glPopMatrix();

	double tx, ty, zu = ax*ax*b*b;
	tx = quadratic(1.0/(a*a) + ay*ay/zu,
		       4*asw*ay/zu,
			  4*asw*asw/zu - 1, (nx+1)/2);
	ty = ny*b*sqrt(1- tx*tx/(a*a));
//	printf("dat %d\n",(nx+1)/2);
	double str = 10000;
//	printf("subz %lf %lf \n", tx-bx,ty-by);

	if(abs(tx-bx)+abs(ty-by) < 1){
	    cout << name << endl;
	    if (abs(tx) > abs(ty)) {ny *= -1; by = -by;}
	    else nx *= -1;

	}

//	if (by < 0 && ny == 1) ny *= -1;

//	if (by > 0 && ny == -1) ny *= -1;

	// if (nx == 1){
	//     if (bx-tx < 0) {nx *= -1; return;}
	// }
// 	if (tx-bx) < str && abs(ty-by) < str){
// 	    printf("(%lf, %lf) (%lf, %lf)\n",bx,by,tx,ty);

// 	    nx *= -1;
// 	    return;
// //	    if (
// 	}
	bx = ax; by=ay;
	ax = tx; ay = ty;

    }


    void print(){
	cout  << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout  << name << endl <<     radius  << endl << escape_v << endl << dfromsun << endl <<     perihelion << endl << aphelion << endl <<     period << endl << orbital_v << endl << inclination << endl <<   eccentricity << endl << tilt << endl;
	cout  << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    }
};
