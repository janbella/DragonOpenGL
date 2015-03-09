#include "cylinder.h"
#include <iostream>

Cylinder::Cylinder() : precision(100)
{
    allocateArrays();
}

Cylinder::Cylinder(int precision) : precision(precision)
{
    allocateArrays();
}

void Cylinder::allocateArrays()
{
    // For arrays method
    topVertices = new GLfloat[(precision+2)*3];
    middleVertices = new GLfloat[(precision+1)*6];
    bottomVertices = new GLfloat[(precision+2)*3];

    topNormals = new GLfloat[(precision+2)*3];
    middleNormals = new GLfloat[(precision+1)*6];
    bottomNormals = new GLfloat[(precision+2)*3];

    topVertices[0] = 0.0f;
    topVertices[1] = 0.0f;
    topVertices[2] = 0.5f;

    topNormals[0] = 0.0f;
    topNormals[1] = 0.0f;
    topNormals[2] = 1.0f;

    for(int i = 0;i<=precision;i++)
    {
        topVertices[3*(i+1)] = (cos((2.0f*M_PI/(float)precision)*i))/2.0f;
        topVertices[3*(i+1)+1] = (sin((2.0f*M_PI/(float)precision)*i))/2.0f;
        topVertices[3*(i+1)+2] = 0.5f;

        topNormals[3*(i+1)] = 0.0f;
        topNormals[3*(i+1)+1] = 0.0f;
        topNormals[3*(i+1)+2] = 1.0f;
    }


    for(int i=0;i<=precision;i++)
    {
        middleVertices[6*i] = (cos((2.0f*M_PI/precision)*i))/2.0f;
        middleVertices[6*i+1] = (sin((2.0f*M_PI/precision)*i))/2.0f;
        middleVertices[6*i+2] = 0.5f;

        middleVertices[6*i+3] = (cos((2.0f*M_PI/precision)*i))/2.0f;
        middleVertices[6*i+4] = (sin((2.0f*M_PI/precision)*i))/2.0f;
        middleVertices[6*i+5] = -0.5f;

        middleNormals[6*i] = (cos((2.0f*M_PI/precision)*i));
        middleNormals[6*i+1] = (sin((2.0f*M_PI/precision)*i));
        middleNormals[6*i+2] = 0.0f;

        middleNormals[6*i+3] = (cos((2.0f*M_PI/precision)*i));
        middleNormals[6*i+4] = (sin((2.0f*M_PI/precision)*i));
        middleNormals[6*i+5] = 0.0f;
    }


    bottomVertices[0] = 0.0f;
    bottomVertices[1] = 0.0f;
    bottomVertices[2] = -0.5f;

    bottomNormals[0] = 0.0f;
    bottomNormals[1] = 0.0f;
    bottomNormals[2] = -1.0f;

    for(int i = (precision);i>=0;i--)
    {
        bottomVertices[3*(precision - i+1)] = (cos((2.0f*M_PI/(float)precision)*i))/2.0f;
        bottomVertices[3*(precision - i+1) + 1] = (sin((2.0f*M_PI/(float)precision)*i))/2.0f;
        bottomVertices[3*(precision - i+1) + 2] = -0.5f;

        bottomNormals[3*(precision - i+1)] = 0.0f;
        bottomNormals[3*(precision - i+1) + 1] = 0.0f;
        bottomNormals[3*(precision - i+1) + 2] = -1.0f;
    }


    // for elements method
    vertices = new GLfloat[(precision+1)*6];

    triangleIndices = new GLubyte*[precision*2];
    for(int i = 0; i < (precision*2); ++i)
        triangleIndices[i] = new GLubyte[3];


    quadIndices = new GLubyte*[(precision)];
    for(int i = 0; i < (precision); ++i)
        quadIndices[i] = new GLubyte[4];


    normals = new GLfloat*[(precision+2)];
    for(int i = 0; i < (precision+2); ++i)
        normals[i] = new GLfloat[3];


    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.5f;

    vertices[3] = 0.0f;
    vertices[4] = 0.0f;
    vertices[5] = -0.5f;


    for(int i=1;i<=precision;i++)
    {
        vertices[6*i] = (cos((2.0f*M_PI/precision)*i))/2.0f;
        vertices[6*i+1] = (sin((2.0f*M_PI/precision)*i))/2.0f;
        vertices[6*i+2] = 0.5f;

        vertices[6*i+3] = (cos((2.0f*M_PI/precision)*i))/2.0f;
        vertices[6*i+4] = (sin((2.0f*M_PI/precision)*i))/2.0f;
        vertices[6*i+5] = -0.5f;
    }

    normals[0][0] = 0.0f;
    normals[0][1] = 0.0f;
    normals[0][2] = 1.0f;

    normals[1][0] = 0.0f;
    normals[1][1] = 0.0f;
    normals[1][2] = -1.0f;


    for(int i=0;i<precision;i++)
    {
        normals[i+2][0] = cos(M_PI*(2*i+1)/precision);
        normals[i+2][1] = sin(M_PI*(2*i+1)/precision);
        normals[i+2][2] = 0.0f;
    }


    for(int i=0;i<precision-1;i++)
    {
        triangleIndices[i][0] = 0;
        triangleIndices[i][1] = (i+1)*2;
        triangleIndices[i][2] = (i+2)*2;
    }

    triangleIndices[precision-1][0] = 0;
    triangleIndices[precision-1][1] = (precision)*2;
    triangleIndices[precision-1][2] = (1)*2;

    for(int i=0;i<precision-1;i++)
    {
        triangleIndices[precision + i][0] = 1;
        triangleIndices[precision + i][1] = 2*(precision-i)+1;
        triangleIndices[precision + i][2] = 2*(precision-i-1)+1;
    }

    triangleIndices[2*precision - 1][0] = 1;
    triangleIndices[2*precision - 1][1] = 2*(1)+1;
    triangleIndices[2*precision - 1][2] = 2*(precision)+1;

    for(int i=0;i<precision-1;i++)
    {
        quadIndices[i][0] = 2*(i+1);
        quadIndices[i][1] = 2*(i+1)+1;
        quadIndices[i][3] = 2*(i+1)+2;
        quadIndices[i][2] = 2*(i+1)+3;
    }

    quadIndices[precision-1][0] = 2*(precision);
    quadIndices[precision-1][1] = 2*(precision)+1;
    quadIndices[precision-1][3] = 2;
    quadIndices[precision-1][2] = 3;
}

Cylinder::~Cylinder()
{
    delete[] topVertices;
    delete[] middleVertices;
    delete[] bottomVertices;

    delete[] topNormals;
    delete[] middleNormals;
    delete[] bottomNormals;

    delete[] vertices;

    for(int i = 0; i < (precision*2); ++i)
        delete[] triangleIndices[i];

    for(int i = 0; i < (precision); ++i)
        delete[] quadIndices[i];

    for(int i = 0; i < (precision+2); ++i)
        delete[] normals[i];

    delete[] triangleIndices;
    delete[] quadIndices;
    delete[] normals;
}

void Cylinder::draw()
{
    glPushMatrix();

    // draw immediate (center cylinder)
//    drawImmediate();

    // draw arrays (left cube)
//    glTranslatef(-2, 0, 0);
//    drawArrays();

    // draw elements (right cube)
//    glTranslatef(+4, 0, 0);
    drawElements();

    glPopMatrix();
}


void Cylinder::drawImmediate()
{

    // top face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.5f);
        glVertex3f(0.5f,0.0f,0.5f);

        //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*1))/2.0f << ", " << (sin((2.0f*M_PI/precision)*1))/2.0f << ", " << 0.5f << std::endl;
        glVertex3f((cos((2.0f*M_PI/precision)*1))/2.0f,(sin((2.0f*M_PI/precision)*1))/2.0f,0.5f);

        for(float i = 2;i<=precision;i++)
        {
            glNormal3f(0.0f,0.0f,1.0f);
            //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*i))/2.0f << ", " << (sin((2.0f*M_PI/precision)*i))/2.0f << ", " << 0.5f << std::endl;
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,0.5f);
        }
    glEnd();


    //middle part
    glBegin(GL_QUAD_STRIP);

        for(float i=0;i<=precision;i++)
        {
            glNormal3f((cos((2.0f*M_PI/precision)*i)),(sin((2.0f*M_PI/precision)*i)),0.0f);
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,0.5f);
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,-0.5f);
        }

    glEnd();

    // bottom face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f,0.0f,-1.0f);
        glVertex3f(0.0f,0.0f,-0.5f);
        glVertex3f(0.5f,0.0f,-0.5f);

        //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*(precision-1)))/2.0f << ", " << (sin((2.0f*M_PI/precision)*(precision-1)))/2.0f << ", " << -0.5f << std::endl;

        glVertex3f((cos((2.0f*M_PI/precision)*(precision-1)))/2.0f,(sin((2.0f*M_PI/precision)*(precision-1)))/2.0f,-0.5f);

        for(float i = (precision-2);i>=0;i--)
        {
            glNormal3f(0.0f,0.0f,-1.0f);
            //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*i))/2.0f << ", " << (sin((2.0f*M_PI/precision)*i))/2.0f << ", " << -0.5f << std::endl;
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,-0.5f);
        }
    glEnd();
}


void Cylinder::drawArrays()
{


    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    // specify the arrays to use
    glNormalPointer(GL_FLOAT, 0, topNormals);
    glVertexPointer(3, GL_FLOAT, 0 , topVertices);

    // draw quads using 24 data stored in arrays, starting at index 0
    glDrawArrays(GL_TRIANGLE_FAN, 0, precision+2);

    glNormalPointer(GL_FLOAT, 0, middleNormals);
    glVertexPointer(3, GL_FLOAT, 0 , middleVertices);


     // draw quads using 24 data stored in arrays, starting at index 0
    glDrawArrays(GL_QUAD_STRIP, 0, 2*(precision+1));

    glNormalPointer(GL_FLOAT, 0, bottomNormals);
    glVertexPointer(3, GL_FLOAT, 0 , bottomVertices);

    // draw quads using 24 data stored in arrays, starting at index 0
    glDrawArrays(GL_TRIANGLE_FAN, 0, precision+2);


    // disable the use of arrays (do not forget!)
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
};


void Cylinder::drawElements()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0 , vertices);

    glNormal3fv(normals[0]);
    for(int i=0;i<precision;i++)
    {
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triangleIndices[i]);
    }

    glNormal3fv(normals[1]);
    for(int i=0;i<precision;i++)
    {
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triangleIndices[precision + i]);
    }

    for(int i=0;i<precision;i++)
    {
        glNormal3fv(normals[i+2]);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quadIndices[i]);
    }


    glDisableClientState(GL_VERTEX_ARRAY);
}



