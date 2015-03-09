#include "tetrahedron.h"
#include <cmath>
/*
         Z
         |

         2
       / | \
      /  3  \   ---> Y
     /  /  \ \
    / /     \ \
 0 +----------+ 1
      /
     X
*/

void Tetrahedron::draw()
{
    glPushMatrix();

    // draw immediate (center cube)
    drawImmediate();

    // draw arrays (left cube)
    glTranslatef(-2, 0, 0);
    drawArrays();

    // draw elements (right cube)
    glTranslatef(+4, 0, 0);
    drawElements();

    glPopMatrix();
}


//==================== 1. Immediate method ===================================
void Tetrahedron::drawImmediate()
{
    GLfloat s0[] = {+0.5, -0.5, -0.5}; // 0
    GLfloat s1[] = {-0.5, +0.5, -0.5}; // 2
    GLfloat s2[] = {+0.5, +0.5, +0.5}; // 5
    GLfloat s3[] = {-0.5, -0.5, +0.5}; // 7

    GLfloat n0[] = {+0.5, +0.5, -0.5};
    GLfloat n1[] = {-0.5, +0.5, +0.5};
    GLfloat n2[] = {-0.5, -0.5, -0.5};
    GLfloat n3[] = {+0.5, -0.5, +0.5};


    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT_AND_BACK);
    glBegin(GL_TRIANGLES);

        glNormal3fv(n0);
        glVertex3fv(s0);
        glVertex3fv(s1);
        glVertex3fv(s2);


        glNormal3fv(n1);
        glVertex3fv(s2);
        glVertex3fv(s1);
        glVertex3fv(s3);

        glNormal3fv(n2);
        glVertex3fv(s0);
        glVertex3fv(s3);
        glVertex3fv(s1);

        glNormal3fv(n3);
        glVertex3fv(s0);
        glVertex3fv(s2);
        glVertex3fv(s3);

    glEnd();
}


//==================== 2. Arrays - drawArrays ================================
static GLfloat allVertices[] = {
    +0.5, -0.5, -0.5,   -0.5, +0.5, -0.5,   +0.5, +0.5, +0.5,   // 0 1 2
    +0.5, +0.5, +0.5,   -0.5, +0.5, -0.5,   -0.5, -0.5, +0.5,   // 2 1 3
    +0.5, -0.5, -0.5,   -0.5, -0.5, +0.5,   -0.5, +0.5, -0.5,   // 0 3 1
    +0.5, -0.5, -0.5,   +0.5, +0.5, +0.5,   -0.5, -0.5, +0.5,   // 0 2 3
};

static GLfloat allNormals[] = {
    +0.5, +0.5, -0.5,   +0.5, +0.5, -0.5,   +0.5, +0.5, -0.5,
    -0.5, +0.5, +0.5,   -0.5, +0.5, +0.5,   -0.5, +0.5, +0.5,
    -0.5, -0.5, -0.5,   -0.5, -0.5, -0.5,   -0.5, -0.5, -0.5,
    +0.5, -0.5, +0.5,   +0.5, -0.5, +0.5,   +0.5, -0.5, +0.5
};


void Tetrahedron::drawArrays()
{
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, allNormals);
    glVertexPointer(3, GL_FLOAT, 0 , allVertices);

    glDrawArrays(GL_TRIANGLES, 0, 12);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
};


//==================== 3. Arrays - drawElements ==============================
// vertex coordinates (defined once only)
static GLfloat vertices[] = {
    +0.5, -0.5, -0.5,   // 0
    -0.5, +0.5, -0.5,   // 1
    +0.5, +0.5, +0.5,   // 2
    -0.5, -0.5, +0.5    // 3
};

// indexes of the 4 faces (in a 2D array)
static GLubyte indices[4][3] = {
    {0, 1, 2},
    {2, 1, 3},
    {0, 3, 1},
    {0, 2, 3}
};

// normals (defined once only)
static GLfloat normals[4][3] = {
    {+0.5, +0.5, -0.5},
    {-0.5, +0.5, +0.5},
    {-0.5, -0.5, -0.5},
    {+0.5, -0.5, +0.5}
};


void Tetrahedron::drawElements()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0 , vertices);

    glNormal3fv(normals[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[0]);
    glNormal3fv(normals[1]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[1]);
    glNormal3fv(normals[2]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[2]);
    glNormal3fv(normals[3]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[3]);


    glDisableClientState(GL_VERTEX_ARRAY);
}




