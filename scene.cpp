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

    materialShader.load("shaders/material.vert", "shaders/material.frag");
    GLCHECK( glUseProgram( materialShader ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_1.ambient"  ), 1, &light_1.ambient.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_1.diffuse"  ), 1, &light_1.diffuse.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_1.specular" ), 1, &light_1.specular.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_1.position" ), 1, &light_1.position.x ) );

    GLCHECK( glUniform1i ( glGetUniformLocation( materialShader, "enabled_light2"   ), true));
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_2.ambient"  ), 1, &light_2.ambient.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_2.diffuse"  ), 1, &light_2.diffuse.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_2.specular" ), 1, &light_2.specular.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_2.position" ), 1, &light_2.position.x ) );

    GLCHECK( glUseProgram(0));

    glEnable(GL_LIGHTING);
    // disable the default qglviewer light !!
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glClearColor(0.0f, 0.1f, 0.1f, 0.0f);

    glClearColor(0.5, 0.5, 0.5, 1);
    glClearDepth(1);
    GLfloat density = 0.3;
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);
}


void Scene::draw()
{
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawGrassPlane(1000);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(200,0,200);
        drawLake(150,180);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-450,0,-460);
    glScalef(3,6,3);
    drawForest(17, 33);
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
    GLCHECK( glUseProgram( materialShader ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_1.position" ), 1, &light_1.position.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "light_2.position" ), 1, &light_2.position.x ) );

    glDisable(GL_COLOR_MATERIAL);

    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "material.ambient" ), 1, &waterMaterial.ambient.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "material.diffuse" ), 1, &waterMaterial.diffuse.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( materialShader, "material.specular" ), 1, &waterMaterial.specular.x ) );
    GLCHECK( glUniform1f(  glGetUniformLocation( materialShader, "material.shininess" ), waterMaterial.shininess ) );


    float height = 0.11;

    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,height,0.0f);
        glVertex3f(0.5f,height,0.0f);

        glVertex3f((cos((2.0f*M_PI/precision)*1))*r,height,(sin((2.0f*M_PI/precision)*1))*r);

        for(float i = 1;i<=precision+1;i++)
        {
            glNormal3f(0.0f,1.0f,0.0f);
            glVertex3f((cos((2.0f*M_PI/precision)*i))*r,height,(sin((2.0f*M_PI/precision)*i))*r);
        }
    glEnd();

    glEnable(GL_COLOR_MATERIAL);

    GLCHECK( glUseProgram(0) );
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
