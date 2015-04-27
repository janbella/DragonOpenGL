#include "dragon.h"
#include "geometryprimitives.h"
#include "objectloader.h"
#include "glCheck.h"
#include "texturingtools.h"

#include <QImage>
#include <QGLWidget>
#include <QVector4D>
#include <cmath>

Dragon::Dragon()
{
    loaded = false;
    smokeParticlesEnabledCount = 0;

    smokeParticles.reserve(20);

    while(smokeParticles.size()<20)
    {
        smokeParticles.push_back(new Particles(smokeTex,1.5,0.005,0.005, 0.2, false));
    }

    fireParticles.reserve(60);
    while(fireParticles.size()<60)
    {
        fireParticles.push_back(new Particles(fireTex,20,0.05,0.005,1, true));
    }

    toggleFire = false;


}

void Dragon::init(Viewer& v)
{
    // load textures
    Texturing::init(dragonTexture,&program,&textureId,&texture,&texcoord);

    for(Particles* p : smokeParticles)
    {
        p->init(v);
    }

    for(Particles* p : fireParticles)
    {
        p->init(v);
    }
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
    for(Particles* p : smokeParticles)
    {
        delete p;
    }
    smokeParticles.clear();

    for(Particles* p : fireParticles)
    {
        delete p;
    }
    fireParticles.clear();
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

    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureId));

    GLCHECK(glUniform1i(texture, 0));

    glPushMatrix();
    glRotatef(90,0,1,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    for(size_t i =0;i<8;i++)
    {
        glPushMatrix();
        glRotatef(0,0,1,0);
        glScalef(2,2,2);
            glCallList(this->dispListIndex + i);
        glPopMatrix();
    }

    GLCHECK(glUseProgram( 0 ));

    glPushMatrix();
    glTranslatef(0,10,10);
    for(int i = 0; i< fmin(smokeParticles.size(), abs(smokeParticlesEnabledCount));i++)
    {
        smokeParticles[i]->draw();
    }
    if(toggleFire)
    {
        //glRotatef(90,1,0,0);
        for(int i = 0; i< fmin(fireParticles.size(), abs(fireParticlesEnabledCount));i++)
        {
            fireParticles[i]->draw();
        }
    }
    glPopMatrix();
    glPopMatrix();



//#ifdef USE_VBO
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    glDrawArrays(GL_TRIANGLES , 0, numVBO);

//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_NORMAL_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//#endif
}

// inherited from Renderable, should be edited
void Dragon::animate()
{

        if(smokeParticlesEnabledCount<smokeParticles.size())
            smokeParticlesEnabledCount += 0.2;
        else
            smokeParticlesEnabledCount = -smokeParticlesEnabledCount;

        if(toggleFire)
        {
        if(fireParticlesEnabledCount<fireParticles.size())
            fireParticlesEnabledCount += 0.5;
        }

    for(int i = 0; i< fmin(smokeParticles.size(), abs(smokeParticlesEnabledCount));i++)
    {
        smokeParticles[i]->animate();
    }

    if(toggleFire)
    {
    for(int i = 0; i< fmin(fireParticles.size(), (int)(fireParticlesEnabledCount));i++)
    {
        fireParticles[i]->animate();
    }
    }
}


// inherited from Renderable, should be edited
void Dragon::keyPressEvent(QKeyEvent* e, Viewer&)
{
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    if ((e->key()==Qt::Key_F) && (modifiers==Qt::NoButton) && e->KeyPress)
    {
        toggleFire = !toggleFire;
        std::cout << "Fire toggled" << std::endl;
        if(!toggleFire)
        {
            for(Particles* p : fireParticles)
            {
                p->setPosition(0,0,0);
            }
            fireParticlesEnabledCount = 0;
        }
    }
}


// inherited from Renderable, should be edited
void Dragon::mouseMoveEvent(QMouseEvent* event, Viewer&)
{
    /*if(event->KeyPress)
    {
        std::cout << "Mouse pressed" << std::endl;
    }*/
}
