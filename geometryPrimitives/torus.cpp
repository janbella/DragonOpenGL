#include "torus.h"
#include <cmath>
#include <iostream>

Torus::Torus():inner_radius(1),outer_radius(4),precision(4)
{

}

Torus::Torus(float inner_radius, float outer_radius, int precision):
    inner_radius(inner_radius),outer_radius(outer_radius),precision(precision)
{

}

Torus::~Torus()
{

}


void Torus::draw()
{
    glPushMatrix();

    drawImmediate();

    glTranslatef(-2, 0, 0);
    drawArrays();

    glTranslatef(+4, 0, 0);
    drawElements();

    glPopMatrix();
}


//==================== 1. Immediate method ===================================
// immediate definition of individual vertex properties

void Torus::drawImmediate()
{
    glEnable(GL_NORMALIZE);
    float radius = (outer_radius - inner_radius) / 2.0f;

    float factor = (2.0f*M_PI/(float)precision);


    for(int i = 0; i< precision;i++) // precision - kružnica XY
    {
        float p = (cos(factor*i));
        float cx1 = (p * outer_radius + p * inner_radius) / 2.0f;
        p = (sin(factor*i));
        float cy1 = (p * outer_radius + p * inner_radius) / 2.0f;

        p = (cos(factor*(i+1)));
        float cx2 = (p * outer_radius + p * inner_radius) / 2.0f;
        p = (sin(factor*(i+1)));
        float cy2 = (p * outer_radius + p * inner_radius) / 2.0f;

        glBegin(GL_QUAD_STRIP);
            for(int j = 0;j < precision;j++)   // precision - kružnica kolmá - XZ
            {
                glPushMatrix();
                    glRotatef(-360.0f / (float)precision * i,0,0,1);glutSolidSphere(0.3,10,10);
                    std::cout << "Rotating " << -360.0f / (float)precision * i << std::endl;
                    glTranslatef(cx1,cy1,0);

                    glNormal3f(cos(factor * j),0,sin(factor * j));
                    glVertex3f(cos(factor * j) * radius,0,sin(factor * j) * radius);
                glPopMatrix();
                glPushMatrix();
                    glRotatef(-360.0f / (float)precision * (i + 1),0,0,1);
                    std::cout << "Rotating " << -360.0f / (float)precision * (i+1) << std::endl;
                    glTranslatef(cx2,cy2,0);

                    glNormal3f(cos(factor * j),0,sin(factor * j));
                    glVertex3f(cos(factor * j) * radius,0,sin(factor * j) * radius);
                glPopMatrix();
            }
        glEnd();
    }
}




//==================== 2. Arrays - drawArrays ================================
// - store vertex-related data (coordinates, normals, colors, etc) in arrays
//   => reduces the number of function calls

// Define the coordinates of all vertices, ordered face by face.
// Since a vertex is shared by 3 faces, it is repeated 3 times!
static GLfloat allVertices[] = {
    +0.5, -0.5, -0.5,   -0.5, -0.5, -0.5,   -0.5, +0.5, -0.5,   +0.5, +0.5, -0.5,  // 0 3 2 1
    +0.5, -0.5, -0.5,   +0.5, -0.5, +0.5,   -0.5, -0.5, +0.5,   -0.5, -0.5, -0.5,  // 0 4 7 3
    +0.5, +0.5, -0.5,   +0.5, +0.5, +0.5,   +0.5, -0.5, +0.5,   +0.5, -0.5, -0.5,  // 1 5 4 0
    -0.5, +0.5, -0.5,   -0.5, +0.5, +0.5,   +0.5, +0.5, +0.5,   +0.5, +0.5, -0.5,  // 2 6 5 1
    -0.5, -0.5, -0.5,   -0.5, -0.5, +0.5,   -0.5, +0.5, +0.5,   -0.5, +0.5, -0.5,  // 3 7 6 2
    +0.5, -0.5, +0.5,   +0.5, +0.5, +0.5,   -0.5, +0.5, +0.5,   -0.5, -0.5, +0.5,  // 4 5 6 7
};

// Define the normals of vertices, using the same vertex order.
static GLfloat allNormals[] = {
     0.0,  0.0, -1.0,    0.0,  0.0, -1.0,    0.0,  0.0, -1.0,    0.0,  0.0, -1.0,  // 0 3 2 1
     0.0, -1.0,  0.0,    0.0, -1.0,  0.0,    0.0, -1.0,  0.0,    0.0, -1.0,  0.0,  // 0 4 7 3
     1.0,  0.0,  0.0,    1.0,  0.0,  0.0,    1.0,  0.0,  0.0,    1.0,  0.0,  0.0,  // 1 5 4 0
     0.0,  1.0,  0.0,    0.0,  1.0,  0.0,    0.0,  1.0,  0.0,    0.0,  1.0,  0.0,  // 2 6 5 1
    -1.0,  0.0,  0.0,   -1.0,  0.0,  0.0,   -1.0,  0.0,  0.0,   -1.0,  0.0,  0.0,  // 3 7 6 2
     0.0,  0.0,  1.0,    0.0,  0.0,  1.0,    0.0,  0.0,  1.0,    0.0,  0.0,  1.0,  // 4 5 6 7
};


void Torus::drawArrays()
{
    // activate the use of GL_VERTEX_ARRAY and GL_NORMAL_ARRAY
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    // specify the arrays to use
    glNormalPointer(GL_FLOAT, 0, allNormals);
    glVertexPointer(3, GL_FLOAT, 0 , allVertices);

    // draw quads using 24 data stored in arrays, starting at index 0
    glDrawArrays(GL_QUADS, 0, 24);

    // disable the use of arrays (do not forget!)
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // Others arrays could also be used:
    // GL_COLOR_ARRAY, GL_INDEX_ARRAY, GL_TEXTURE_COORD_ARRAY, ...
}



//==================== 3. Arrays - drawElements ==============================
// - single definition of shared data
// - draw face by face, using face indices

// vertex coordinates (defined once only)
static GLfloat vertices[] = {
    +0.5, -0.5, -0.5,  // 0
    +0.5, +0.5, -0.5,  // 1
    -0.5, +0.5, -0.5,  // 2
    -0.5, -0.5, -0.5,  // 3
    +0.5, -0.5, +0.5,  // 4
    +0.5, +0.5, +0.5,  // 5
    -0.5, +0.5, +0.5,  // 6
    -0.5, -0.5, +0.5,  // 7
};

// indexes of the 6 faces (in a 2D array)
static GLubyte indices[6][4] = {
    {0, 3, 2, 1},
    {0, 4, 7, 3},
    {1, 5, 4, 0},
    {2, 6, 5, 1},
    {3, 7, 6, 2},
    {4, 5, 6, 7}
};

// normals (defined once only)
static GLfloat normals[6][3] = {
    { 0.0,  0.0, -1.0},
    { 0.0, -1.0,  0.0},
    { 1.0,  0.0,  0.0},
    { 0.0,  1.0,  0.0},
    {-1.0,  0.0,  0.0},
    { 0.0,  0.0,  1.0}
};


void Torus::drawElements()
{
    // activate the use of GL_VERTEX_ARRAY (not GL_NORMALS_ARRAY)
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0 , vertices);

    // for each face:
    //   - set the current normal (state machine)
    //   - draw a face using glDrawElements with the indices of the face

    glNormal3fv(normals[0]);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices[0]);
    glNormal3fv(normals[1]);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices[1]);
    glNormal3fv(normals[2]);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices[2]);
    glNormal3fv(normals[3]);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices[3]);
    glNormal3fv(normals[4]);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices[4]);
    glNormal3fv(normals[5]);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices[5]);

    glDisableClientState(GL_VERTEX_ARRAY);
}





