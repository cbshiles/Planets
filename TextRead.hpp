#include "Planet.hpp"

#define PLANETS 9

vector<Planet> read_planets(const char* fname)
{
    ifstream rFile;
    rFile.open(fname);

    vector<Planet> system(PLANETS);

    int ii = 0;

    system[ii++].color = mercury;
    system[ii++].color = venus;
    system[ii++].color = earth;
    system[ii++].color = mars;
    system[ii++].color = jupiter;
    system[ii++].color = saturn;
    system[ii++].color = uranus;
    system[ii++].color = neptune;
    system[ii++].color = pluto;

    char strBuff [100];

    if (! rFile.is_open()){
	cout << "Error opening file." << endl;
	return system; }

    int line = 0, i=0;

    while (! rFile.eof()){
	rFile >> strBuff;

	if (strBuff[0] == ';') {
	    i = 0;
	    line++;
	}
	else if (strBuff[0] == '~') break;    
	else {
	    if (line == 0)
		system[i].name = string(strBuff);
	    else {
		double tmp = atof(strBuff);
		double m = 1000000;
		if (line == 1) system[i].radius = tmp/2;
		else if (line == 2) system[i].escape_v = tmp;
		else if (line == 3) system[i].dfromsun = m*tmp;
		else if (line == 4) system[i].perihelion =m* tmp;
		else if (line == 5) system[i].aphelion = m*tmp;
		else if (line == 6) system[i].period = tmp;
		else if (line == 7) system[i].orbital_v = tmp;
		else if (line == 8) system[i].inclination = tmp;
		else if (line == 9) system[i].eccentricity = tmp;
		else if (line == 10) system[i].tilt = tmp;
		else break;
	    }
	    i++;
	}
    }

    rFile.close();
    return system;
}

