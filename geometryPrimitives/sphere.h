#ifndef SPHERE_H
#define SPHERE_H

#include "renderable.h"
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415f
#endif

class Sphere : public Renderable
{
public:
    Sphere();
    Sphere(int precision);
    virtual ~Sphere();
    void draw();

private:
    int precision;

    void drawImmediate();

};

#endif // SPHERE_H
