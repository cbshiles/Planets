struct Color {
    double r, g, b;

    Color(int rr, int gg, int bb) :
	r(rr/255.0), g(gg/255.0), b(bb/255.0) {}
    
    void set() {glColor3f(r, g, b);}

    void setBackground() {glClearColor(r,g,b,0);}

    void print() {printf("%f %f %f\n",r*255,g*255,b*255);}
};

Color* orange = new Color(200, 127, 0);
Color* red_orange = new Color(255,100,20);
Color* white = new Color(255, 255, 255);
Color* black = new Color(0,0,0);
Color* blue = new Color(0,0,255);
Color* red = new Color(255,0,0);
Color* green = new Color(0,255,0);
Color* grey = new Color(127,127,127);
Color* yellow = new Color(255,255,0);

// Color* mercury = new Color();
// Color* venus = new Color();
Color* earth = blue;
Color* mars = red;
// Color* jupiter = new Color();
// Color* saturn = new Color();
// Color* uranus = new Color();
// Color* neptune = new Color();
// Color* pluto = new Color();
