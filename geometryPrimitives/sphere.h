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

#endif // SPHERE_H
