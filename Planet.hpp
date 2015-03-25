// structs are exactly the same as classes, except everything is automatically public

struct Planet {
    std::string name;
    Color* color;
    float diameter;
    float perihelion, aphelion;
    float period; //Orbital period, time for this planet to rotate sun
    float eccentricity, tilt;

    Planet(const char* n, Color* c): name(std::string(n)), color(c)
    {

    }
};
