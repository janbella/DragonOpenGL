#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "renderable.h"
#include <GL/glut.h>


class Tetrahedron : public Renderable
{
public:
    void draw();

private:
    void drawImmediate();
    void drawElements();
    void drawArrays();
};

#endif // TETRAHEDRON_H
