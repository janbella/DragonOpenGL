#include "scene.h"

#include "glCheck.h"
#include "texturingtools.h"

#include <cmath>

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::init(Viewer&)
{
    Texturing::init(textureGrassPath,&textureShader,&textureGrass,&texture0,&texcoord0);
    Texturing::init(textureTreePath,&textureShader,&textureTree,&texture0,&texcoord0);
    Texturing::init(textureFlowersPath,&textureShader,&textureFlowers,&texture1,&texcoord1);
}


void Scene::draw()
{
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawGrassPlane(1000);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(200,0,200);
        drawLake(100,180);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400,0,-80);
    glScalef(3,6,3);
    drawForest(15, 20);
    glPopMatrix();

}


void Scene::animate()
{

}


void Scene::keyPressEvent(QKeyEvent*, Viewer&)
{

}


void Scene::mouseMoveEvent(QMouseEvent*, Viewer&)
{

}

void Scene::drawGrassPlane(float s)
{
    GLCHECK(glUseProgram( (GLint)textureShader ));

    GLCHECK(glActiveTexture(GL_TEXTURE0));
    glEnable(GL_TEXTURE_2D);
    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureGrass));
    GLCHECK(glUniform1i(texture0, 0));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

//    GLCHECK(glActiveTexture(GL_TEXTURE1));
//    glEnable(GL_TEXTURE_2D);
//    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureFlowers));
//    GLCHECK(glUniform1i(texture1,1));

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    // draw a plane
    glNormal3f(0.0, 0.0, 1.0);
    float height = 0.1;

    glPushMatrix();
    glTranslatef(-s / 2.0, -s / 2.0, 0.0);

    glBegin(GL_QUADS);
        glVertexAttrib2f(texcoord0, 0, 0);
        glVertexAttrib2f(texcoord1, 0, 0);
        glVertex3f(0, 0, height);
        glVertexAttrib2f(texcoord0, 10, 0);
        glVertexAttrib2f(texcoord1, 25, 0);
        glVertex3f(s, 0, height);
        glVertexAttrib2f(texcoord0, 10, 10);
        glVertexAttrib2f(texcoord1, 25, 25);
        glVertex3f(s, s, height);
        glVertexAttrib2f(texcoord0, 0, 10);
        glVertexAttrib2f(texcoord1, 0, 25);
        glVertex3f(0, s, height);
    glEnd();

    glPopMatrix();
    GLCHECK(glUseProgram( 0 ));

}

void Scene::drawLake(float r, float precision)
{
    glNormal3f(0.0, 1.0, 0.0);
    float height = 0.11;


    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,height,0.0f);
        glVertex3f(0.5f,height,0.0f);

        glVertex3f((cos((2.0f*M_PI/precision)*1))*r,height,(sin((2.0f*M_PI/precision)*1))*r);

        for(float i = 1;i<=precision+1;i++)
        {
            glNormal3f(0.0f,0.0f,1.0f);
            glVertex3f((cos((2.0f*M_PI/precision)*i))*r,height,(sin((2.0f*M_PI/precision)*i))*r);
        }
    glEnd();

}


void Scene::drawForest(int num_X, int num_Z)
{
    GLCHECK(glUseProgram( (GLint)textureShader ));

    GLCHECK(glActiveTexture(GL_TEXTURE0));
    glEnable(GL_TEXTURE_2D);
    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureTree));
    GLCHECK(glUniform1i(texture0, 0));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


    glNormal3f(0.0, 0.0, 1.0);
    float s = 10;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glTranslatef(-s / 2.0, 0.0, -s / 2.0);

    for(int i = 0;i<num_X;i++)
    {
        for(int j = 0;j<num_Z;j++)
        {
            glPushMatrix();
            glTranslatef(i*s, 0.0, j*s);
            glBegin(GL_QUADS);
                glVertexAttrib2f(texcoord0, 0, 0);
                glVertex3f(-s/2.0f, 0, 0.0);
                glVertexAttrib2f(texcoord0, 1, 0);
                glVertex3f(s/2.0f,0, 0.0 );
                glVertexAttrib2f(texcoord0, 1, 1);
                glVertex3f(s/2.0f,s,  0.0);
                glVertexAttrib2f(texcoord0, 0, 1);
                glVertex3f(-s/2.0f,s, 0.0 );
            glEnd();
            glRotatef(90,0,1,0);
            glBegin(GL_QUADS);
            glVertexAttrib2f(texcoord0, 0, 0);
            glVertex3f(-s/2.0f, 0, 0.0);
            glVertexAttrib2f(texcoord0, 1, 0);
            glVertex3f(s/2.0f,0, 0.0 );
            glVertexAttrib2f(texcoord0, 1, 1);
            glVertex3f(s/2.0f,s,  0.0);
            glVertexAttrib2f(texcoord0, 0, 1);
            glVertex3f(-s/2.0f,s, 0.0 );
            glEnd();

            glPopMatrix();
        }
    }

    glPopMatrix();
    glDisable(GL_BLEND);

    GLCHECK(glUseProgram( 0 ));


}
