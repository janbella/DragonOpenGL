#ifndef TORUS_H
#define TORUS_H

#include <GL/glut.h>
#include "renderable.h"

class Torus : public Renderable
{
public:
    Torus();
    Torus(float inner_radius, float outer_radius, int precision = 500);
    void draw();

    ~Torus();

private:
    float inner_radius;
    float outer_radius;
    int precision;

    void drawImmediate();
    void drawElements();
    void drawArrays();
};

#endif // TORUS_H
