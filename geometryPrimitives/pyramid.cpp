#include "pyramid.h"


/*
          Z
          |
          ++ 4
        // | \
     3+-/--|--+ 2   ---> Y
     / /   |  /
    / /    | /
 0 +-------+ 1
      /
     X
*/


void Pyramid::draw()
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
void Pyramid::drawImmediate()
{
    GLfloat s0[] = {+0.5, -0.5, -0.5};
    GLfloat s1[] = {+0.5, +0.5, -0.5};
    GLfloat s2[] = {-0.5, +0.5, -0.5};
    GLfloat s3[] = {-0.5, -0.5, -0.5};
    GLfloat s4[] = { 0.0,  0.0, +0.5};

    glEnable(GL_NORMALIZE);
    glBegin(GL_TRIANGLES);

        glNormal3f(0.0, 0.0, -1.0);
        glVertex3fv(s0);
        glVertex3fv(s2);
        glVertex3fv(s1);

        glNormal3f(0.0, 0.0, -1.0);
        glVertex3fv(s0);
        glVertex3fv(s3);
        glVertex3fv(s2);

        glNormal3f(1.0, 0.0, 2.0);
        glVertex3fv(s0);
        glVertex3fv(s1);
        glVertex3fv(s4);

        glNormal3f(0.0, 1.0, 2.0);
        glVertex3fv(s1);
        glVertex3fv(s2);
        glVertex3fv(s4);

        glNormal3f(-1.0, 0.0, 2.0);
        glVertex3fv(s2);
        glVertex3fv(s3);
        glVertex3fv(s4);

        glNormal3f(0.0, -1.0, 2.0);
        glVertex3fv(s3);
        glVertex3fv(s0);
        glVertex3fv(s4);

    glEnd();
}
/*
GLfloat s0[] = {+0.5, -0.5, -0.5};
GLfloat s1[] = {+0.5, +0.5, -0.5};
GLfloat s2[] = {-0.5, +0.5, -0.5};
GLfloat s3[] = {-0.5, -0.5, -0.5};
GLfloat s4[] = { 0.0,  0.0, +0.5};
0 2 1 0 3 2 0 1 4 1 2 4 2 3 4 3 0 4
*/

//==================== 2. Arrays - drawArrays ================================
static GLfloat allVertices[] = {
    +0.5, -0.5, -0.5,   -0.5, +0.5, -0.5,   +0.5, +0.5, -0.5,   // 0 2 1
    +0.5, -0.5, -0.5,   -0.5, -0.5, -0.5,   -0.5, +0.5, -0.5,   // 0 3 2
    +0.5, -0.5, -0.5,   +0.5, +0.5, -0.5,    0.0,  0.0, +0.5,   // 0 1 4
    +0.5, +0.5, -0.5,   -0.5, +0.5, -0.5,    0.0,  0.0, +0.5,   // 1 2 4
    -0.5, +0.5, -0.5,   -0.5, -0.5, -0.5,    0.0,  0.0, +0.5,   // 2 3 4
    -0.5, -0.5, -0.5,   +0.5, -0.5, -0.5,    0.0,  0.0, +0.5    // 3 0 4
};

static GLfloat allNormals[] = {
     0.0,  0.0, -1.0,    0.0,  0.0, -1.0,     0.0,  0.0, -1.0,    // 0 2 1
     0.0,  0.0, -1.0,    0.0,  0.0, -1.0,     0.0,  0.0, -1.0,    // 0 3 2
     1.0,  0.0,  2.0,    1.0,  0.0,  2.0,     1.0,  0.0,  2.0,    // 0 1 4
     0.0,  1.0,  2.0,    0.0,  1.0,  2.0,     0.0,  1.0,  2.0,    // 1 2 4
    -1.0,  0.0,  2.0,   -1.0,  0.0,  2.0,    -1.0,  0.0,  2.0,    // 2 3 4
     0.0, -1.0,  2.0,    0.0, -1.0,  2.0,     0.0, -1.0,  2.0     // 3 0 4
};


void Pyramid::drawArrays()
{
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, allNormals);
    glVertexPointer(3, GL_FLOAT, 0 , allVertices);

    glDrawArrays(GL_TRIANGLES, 0, 18);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}



//==================== 3. Arrays - drawElements ==============================
// - single definition of shared data
// - draw face by face, using face indices

// vertex coordinates (defined once only)
static GLfloat vertices[] = {
    +0.5, -0.5, -0.5,   // 0
    +0.5, +0.5, -0.5,   // 1
    -0.5, +0.5, -0.5,   // 2
    -0.5, -0.5, -0.5,   // 3
     0.0,  0.0, +0.5    // 4
};

// indexes of the 6 faces (in a 2D array)
static GLubyte indices[6][3] = {
    {0, 2, 1},
    {0, 3, 2},
    {0, 1, 4},
    {1, 2, 4},
    {2, 3, 4},
    {3, 0, 4}
};

// normals (defined once only)
static GLfloat normals[5][3] = {
   { 0.0,  0.0, -1.0},
   { 1.0,  0.0,  2.0},
   { 0.0,  1.0,  2.0},
   {-1.0,  0.0,  2.0},
   { 0.0, -1.0,  2.0},
};


void Pyramid::drawElements()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0 , vertices);

    glNormal3fv(normals[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[0]);
    glNormal3fv(normals[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[1]);
    glNormal3fv(normals[1]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[2]);
    glNormal3fv(normals[2]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[3]);
    glNormal3fv(normals[3]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[4]);
    glNormal3fv(normals[4]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices[5]);

    glDisableClientState(GL_VERTEX_ARRAY);
}



