#include "skybox.h"

#include <QGLViewer/qglviewer.h>
#include <QImage>

#include "geometryprimitives.h"


Skybox::Skybox()
{
	texturePath = "textures/skybox.jpg";
}

void Skybox::init(Viewer&)
{
    // load textures
    textureId = loadTexture(texturePath);

    program.load("shaders/texture.vert", "shaders/texture.frag");
    // get the program id and use it to have access to uniforms
    GLint program_id = (GLint)program;
    GLCHECK(glUseProgram( program_id ) );
    // get uniform locations (see the fragment shader)
    GLCHECK(texture = glGetUniformLocation( program_id, "texture0"));
    // get vertex texture coordinate locations
    GLCHECK(texcoord = glGetAttribLocation( program_id, "texcoord0"));
    // tex0 on the sampler will use the texture unit #0
    GLCHECK(glUniform1i( texture, 0 ) );
}

Skybox::~Skybox()
{

}

// load a single texture file to associate with a Textureid
GLuint Skybox::loadTexture(const char *filename)
{
    // generates an OpenGL texture id, and store it
    GLuint id;
    GLCHECK(glGenTextures(1, &id));

    // load a texture file as a QImage
    QImage img = QGLWidget::convertToGLFormat(QImage(filename));

    // specify the texture(2D texture, rgba, single file)
    GLCHECK(glBindTexture(GL_TEXTURE_2D, id));

    GLCHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, img.bits()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    return id;
}

// draw a quad centered in the XY place (z=0), of size s
void Skybox::drawSkyboxCube(float size)
{
    GLint OldDepthFuncMode;
       glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

       GLint OldCullFaceMode;
           glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);

           glCullFace(GL_FRONT);

       glDepthFunc(GL_LEQUAL);

    GLCHECK(glActiveTexture(GL_TEXTURE0));

    // bind the crate texture for texture unit 0
    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureId));

    // set the texture sampler id in shader to active texture unit number
    GLCHECK(glUniform1i(texture, 0));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(1,1,1);
    glScalef(size,size,size);

    GLfloat s0[] = {+0.5, -0.5, -0.5};
    GLfloat s1[] = {+0.5, +0.5, -0.5};
    GLfloat s2[] = {-0.5, +0.5, -0.5};
    GLfloat s3[] = {-0.5, -0.5, -0.5};
    GLfloat s4[] = {+0.5, -0.5, +0.5};
    GLfloat s5[] = {+0.5, +0.5, +0.5};
    GLfloat s6[] = {-0.5, +0.5, +0.5};
    GLfloat s7[] = {-0.5, -0.5, +0.5};

    glBegin(GL_QUADS);

        // 0 1 2 3 bottom
        glNormal3f(0.0, 0.0, -1.0);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 3.0f/3.0f);
        glVertex3fv(s0);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 3.0f/3.0f);
        glVertex3fv(s1);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s2);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s3);

        // 0 4 7 3
        glNormal3f(0.0, -1.0, 0.0);
        glVertexAttrib2f(texcoord, 0.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s0);
        glVertexAttrib2f(texcoord, 0.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s4);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s7);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s3);

        // 1 5 4 0
        glNormal3f(1.0, 0.0, 0.0);
        glVertexAttrib2f(texcoord, 3.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s1);
        glVertexAttrib2f(texcoord, 3.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s5);
        glVertexAttrib2f(texcoord, 4.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s4);
        glVertexAttrib2f(texcoord, 4.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s0);

        // 2 6 5 1
        glNormal3f(0.0, 1.0, 0.0);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s2);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s6);
        glVertexAttrib2f(texcoord, 3.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s5);
        glVertexAttrib2f(texcoord, 3.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s1);

        // 3 7 6 2
        glNormal3f(-1.0, 0.0, 0.0);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s3);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s7);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s6);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 2.0f/3.0f);
        glVertex3fv(s2);

        // 4 5 6 7
        glNormal3f(0.0, 0.0, 1.0);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 0.0f/3.0f);
        glVertex3fv(s4);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 0.0f/3.0f);
        glVertex3fv(s5);
        glVertexAttrib2f(texcoord, 2.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s6);
        glVertexAttrib2f(texcoord, 1.0f/4.0f, 1.0f/3.0f);
        glVertex3fv(s7);

    glEnd();
    glPopMatrix();
    glDepthFunc(OldDepthFuncMode);
    glCullFace(OldCullFaceMode);
}

void Skybox::draw()
{
    GLCHECK(glUseProgram( (GLint)program ));
    drawSkyboxCube(100);
    GLCHECK(glUseProgram( 0 ));
}
