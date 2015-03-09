#ifndef CYLINDER_H
#define CYLINDER_H

#include "renderable.h"
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415f
#endif

class Cylinder : public Renderable
{
public:
    void draw();
    Cylinder();
    Cylinder(int precision);
    virtual ~Cylinder();

private:
    int precision;

    // arrays method data
    GLfloat* topVertices;
    GLfloat* middleVertices;
    GLfloat* bottomVertices;

    GLfloat* topNormals;
    GLfloat* middleNormals;
    GLfloat* bottomNormals;

    // elements method data
    GLfloat* vertices;
    GLubyte** triangleIndices;
    GLubyte** quadIndices;
    GLfloat** normals;

    void drawImmediate();
    void drawElements();
    void drawArrays();

    void allocateArrays();
};

#endif // CYLINDER_H
