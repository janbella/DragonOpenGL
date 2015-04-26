#include "dragon.h"
#include "geometryprimitives.h"
#include "objectloader.h"
#include "glCheck.h"

#include <QImage>
#include <QGLWidget>

Dragon::Dragon()
{
    loaded = false;
}

void Dragon::init(Viewer& v)
{
    // load textures
    textureId = loadTexture(dragonTexture);

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


void Dragon::initDispLists()
{
    dispListIndex = glGenLists(8);

    ObjectLoader objLoader(bodyObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + BODY, texcoord);
    }

    objLoader.setFilename(leftWingObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + LEFTWING, texcoord);
    }

    objLoader.setFilename(rightWingObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + RIGHTWING, texcoord);
    }

    objLoader.setFilename(leftFrontLegObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + LEFTFRONTLEG, texcoord);
    }

    objLoader.setFilename(rightFrontLegObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + RIGHTFRONTLEG, texcoord);
    }

    objLoader.setFilename(leftBackLegObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + LEFTBACKLEG, texcoord);
    }

    objLoader.setFilename(rightBackLegObj);
    if(objLoader.loadObj())
    {
        objLoader.createDisplayList(dispListIndex + RIGHTBACKLEG, texcoord);
    }
}

void Dragon::initVBOs()
{
    glGenBuffers(8,&vertVBOIndex);
    glGenBuffers(8,&normVBOIndex);
    glGenBuffers(8,&texVBOIndex);

    numVBOitems.reserve(8);

    ObjectLoader objLoader(bodyObj);

    if(objLoader.loadObj())
    {
        numVBOitems[BODY] = objLoader.createVBO(vertVBOIndex + BODY,vertVBOIndex + BODY,vertVBOIndex + BODY);
    }

    objLoader.setFilename(leftWingObj);
    if(objLoader.loadObj())
    {
        numVBOitems[LEFTWING] = objLoader.createVBO(vertVBOIndex + LEFTWING,vertVBOIndex + LEFTWING,vertVBOIndex + LEFTWING);
    }

    objLoader.setFilename(rightWingObj);
    if(objLoader.loadObj())
    {
        numVBOitems[RIGHTWING] = objLoader.createVBO(vertVBOIndex + RIGHTWING,vertVBOIndex + RIGHTWING,vertVBOIndex + RIGHTWING);
    }

    objLoader.setFilename(leftFrontLegObj);
    if(objLoader.loadObj())
    {
        numVBOitems[LEFTFRONTLEG] = objLoader.createVBO(vertVBOIndex + LEFTFRONTLEG,vertVBOIndex + LEFTFRONTLEG,vertVBOIndex + LEFTWING);
    }

    objLoader.setFilename(rightFrontLegObj);
    if(objLoader.loadObj())
    {
        numVBOitems[RIGHTFRONTLEG] = objLoader.createVBO(vertVBOIndex + RIGHTFRONTLEG,vertVBOIndex + RIGHTFRONTLEG,vertVBOIndex + RIGHTFRONTLEG);
    }

    objLoader.setFilename(leftBackLegObj);
    if(objLoader.loadObj())
    {
        numVBOitems[LEFTBACKLEG] = objLoader.createVBO(vertVBOIndex + LEFTBACKLEG,vertVBOIndex + LEFTBACKLEG,vertVBOIndex + LEFTBACKLEG);
    }

    objLoader.setFilename(rightBackLegObj);
    if(objLoader.loadObj())
    {
        numVBOitems[RIGHTBACKLEG] = objLoader.createVBO(vertVBOIndex + RIGHTBACKLEG,vertVBOIndex + RIGHTBACKLEG,vertVBOIndex + RIGHTBACKLEG);
    }
}

Dragon::~Dragon()
{
}

// inherited from Renderable, should be edited
void Dragon::draw()
{
    if(!loaded)
    {
        initDispLists();
        loaded = true;
    }
    GLCHECK(glUseProgram( (GLint)program ));

    GLCHECK(glActiveTexture(GL_TEXTURE0));

    // bind the crate texture for texture unit 0
    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureId));

    // set the texture sampler id in shader to active texture unit number
    GLCHECK(glUniform1i(texture, 0));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    for(size_t i =0;i<8;i++)
    {
        glPushMatrix();
        glRotatef(0,0,1,0);
            glCallList(this->dispListIndex + i);
        glPopMatrix();
    }

    GLCHECK(glUseProgram( 0 ));



#ifdef USE_VBO
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawArrays(GL_TRIANGLES , 0, numVBO);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
}

// inherited from Renderable, should be edited
void Dragon::animate()
{

}


// inherited from Renderable, should be edited
void Dragon::keyPressEvent(QKeyEvent*, Viewer&)
{
}


// inherited from Renderable, should be edited
void Dragon::mouseMoveEvent(QMouseEvent*, Viewer&)
{
}

GLuint Dragon::loadTexture(const char *filename)
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
