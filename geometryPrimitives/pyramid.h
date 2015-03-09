#ifndef PYRAMID_H
#define PYRAMID_H

#include "renderable.h"
#include <GL/glut.h>


class Pyramid : public Renderable
{
public:
    void draw();

private:
    void drawImmediate();
    void drawElements();
    void drawArrays();
};

#endif // PYRAMID_H
