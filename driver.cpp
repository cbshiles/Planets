#include <string>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

#include "Color.hpp"
#include "Planet.hpp"

using namespace std;

int main(){
    Planet earth("Earth", blue);
    cout << earth.name << endl;
}
