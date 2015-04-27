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

    glTranslatef(100,0,0);
    glRotatef(90,0,1,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glPushMatrix();
    glRotatef(0,0,1,0);
    glScalef(2,2,2);
    //for(size_t i =0;i<8;i++)
    //{
    //    glCallList(this->dispListIndex + i);
    //}

    if (s)
    {
        //	glPushMatrix();
        if (step>360)
        {
            s=!s;
            step = 0;

        }
        glTranslatef(0.0,15.0,0.0);
        glRotatef(step,1.0,0.0,0.0);
        //glRotatef(step,0.0,1.0,0);
        glCallList(0);
        glCallList(1);
        glCallList(2);
        glCallList(3);
        glCallList(4);
        glCallList(5);
        glCallList(6);
        glCallList(7);
        //glPopMatrix();
    }
    if (f || fall) // falling or flying
    {
        glTranslatef(0.0,flight,0.0);

        glCallList(1);
        glCallList(2);
        glCallList(3);
        glCallList(4);
        glCallList(6);
        glPushMatrix();

        glRotatef(angle, 0.0f, -1.0f, -1.0f);
        glPushMatrix();
        glCallList(5);
        glPopMatrix();
        glPopMatrix();


        glRotatef(angle, 0.0f, 1.0f, 1.0f);
        glPushMatrix();
        glCallList(7);

        glPopMatrix();
    }
    else // static movement
    {
        if (!f && timer!=0)
        {
            timer = 0;
        }
        else
        {
            glTranslatef(0.0,0.0,go);
            if(!loaded)
            {
                initDispLists();
                loaded = true;
            }
            if(!r)
            {
                glCallList(1);
                glCallList(2);
            }
            glCallList(3);
            glCallList(4);
            glCallList(5);
            glCallList(6);
            glCallList(7);
        }
    };
    if(glIsList(changedDispListId))
    {

        glCallList(changedDispListId);
        glCallList(changedDispListId+1);
    };

    //glPopMatrix();


    GLCHECK(glUseProgram( 0 ));

    //glPushMatrix();
    //glTranslatef(0,10,10);
    glTranslatef(0,5,5);
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

    //// ANIMATION

    if (s)
    {
        step+=5;
    }
    if (f)
    {
        timer++;
        if (flight<10)
        {
            flight+=0.02*speed;
            if (timer>7)
            {
                speed*=1.3;
                timer = 0;
            }
        }


        if (angle>10 || angle<-10)
        {
            increase=!increase;
        }
        if (increase)
        {
            angle+=angleChange*speed;
        }
        else
        {
            angle-=angleChange*speed;
        }

    }
    else if (fall)
    {
        if (flight>0)
        {
            flight-=0.02*speed;
        }
        timer++;

        if (timer>10)
        {
            speed*=1.3;
            timer = 0;
        }
    }
    if (r)
    {
        go+=0.1;
        if (shift>0.2 || shift<-0)
        {
            up=!up;
        }
        if (!up)
        {
            shift+=0.03;
        }
        else
        {
            shift-=0.03;
        }

        if(!glIsList(changedDispListId))
        {
            changedDispListId = glGenLists(2);
        }

        glNewList(changedDispListId,GL_COMPILE);

        ObjectLoader objLoader(cylinder);
        if(objLoader.loadObj())
        {
            std::vector<QVector3D> vertices = objLoader.getVertices();
            std::vector<QVector3D> normals = objLoader.getNormals();
            std::vector<QVector2D> texCoords = objLoader.getTexCoords();
            std::vector<Triangle> faces =objLoader.getFaces();
            std::vector<QVector3D> skeleton = objLoader.getSkeleton();

            std::vector<QVector3D> verticesNew=skeleton;
            verticesNew[1].setY(verticesNew[1].y()+2*shift);
            verticesNew[2].setY(verticesNew[2].y()+2*shift);
            verticesNew[3].setY(verticesNew[3].y()+shift);
            verticesNew[4].setY(verticesNew[4].y());
            verticesNew[5].setY(verticesNew[5].y());

            verticesNew[1].setZ(verticesNew[1].z()+2*shift);
            verticesNew[2].setZ(verticesNew[2].z()+2*shift);
            verticesNew[3].setZ(verticesNew[3].z()+shift);
            verticesNew[4].setZ(verticesNew[4].z());
            verticesNew[5].setZ(verticesNew[5].z());

            glPushMatrix();
            glBegin(GL_TRIANGLES);

            for(std::vector<Triangle>::const_iterator iter = faces.cbegin(); iter!=faces.cend();iter++)
            {
                glNormal3f(normals[iter->n1].x(),normals[iter->n1].y(),normals[iter->n1].z());
                glVertexAttrib2f(texcoord, texCoords[iter->t1].x(),texCoords[iter->t1].y());
                glVertex3f(vertices[iter->v1].x(),meaning(skeleton,verticesNew,vertices[iter->v1].y()),meaning(skeleton,verticesNew,vertices[iter->v1].y(),vertices[iter->v1].z()));

                glNormal3f(normals[iter->n2].x(),normals[iter->n2].y(),normals[iter->n2].z());
                glVertexAttrib2f(texcoord, texCoords[iter->t2].x(),texCoords[iter->t2].y());
                glVertex3f(vertices[iter->v2].x(),meaning(skeleton,verticesNew,vertices[iter->v2].y()),meaning(skeleton,verticesNew,vertices[iter->v2].y(),vertices[iter->v2].z()));

                glNormal3f(normals[iter->n3].x(),normals[iter->n3].y(),normals[iter->n3].z());
                glVertexAttrib2f(texcoord, texCoords[iter->t3].x(),texCoords[iter->t3].y());
                glVertex3f(vertices[iter->v3].x(),meaning(skeleton,verticesNew,vertices[iter->v3].y()),meaning(skeleton,verticesNew,vertices[iter->v3].y(),vertices[iter->v3].z()));
            }
        }
        glEnd();

        glPopMatrix();
        glEndList();

        glNewList(changedDispListId+1,GL_COMPILE);
        objLoader.setFilename(cylinder2);
        if(objLoader.loadObj())
        {
            std::vector<QVector3D> vertices = objLoader.getVertices();
            std::vector<QVector3D> normals = objLoader.getNormals();
            std::vector<QVector2D> texCoords = objLoader.getTexCoords();
            std::vector<Triangle> faces =objLoader.getFaces();
            std::vector<QVector3D> skeleton = objLoader.getSkeleton();

            std::vector<QVector3D> verticesNew=skeleton;
            verticesNew[1].setY(verticesNew[1].y()+2*shift);
            verticesNew[2].setY(verticesNew[2].y()+2*shift);
            verticesNew[3].setY(verticesNew[3].y()+shift);
            verticesNew[4].setY(verticesNew[4].y());
            verticesNew[5].setY(verticesNew[5].y());

            verticesNew[1].setZ(verticesNew[1].z()+2*shift);
            verticesNew[2].setZ(verticesNew[2].z()+2*shift);
            verticesNew[3].setZ(verticesNew[3].z()+shift);
            verticesNew[4].setZ(verticesNew[4].z());
            verticesNew[5].setZ(verticesNew[5].z());

            glPushMatrix();
            glBegin(GL_TRIANGLES);

            for(std::vector<Triangle>::const_iterator iter = faces.cbegin(); iter!=faces.cend();iter++)
            {
                glNormal3f(normals[iter->n1].x(),normals[iter->n1].y(),normals[iter->n1].z());
                glVertexAttrib2f(texcoord, texCoords[iter->t1].x(),texCoords[iter->t1].y());
                glVertex3f(vertices[iter->v1].x(),meaning(skeleton,verticesNew,vertices[iter->v1].y()),meaning(skeleton,verticesNew,vertices[iter->v1].y(),vertices[iter->v1].z()));

                glNormal3f(normals[iter->n2].x(),normals[iter->n2].y(),normals[iter->n2].z());
                glVertexAttrib2f(texcoord, texCoords[iter->t2].x(),texCoords[iter->t2].y());
                glVertex3f(vertices[iter->v2].x(),meaning(skeleton,verticesNew,vertices[iter->v2].y()),meaning(skeleton,verticesNew,vertices[iter->v2].y(),vertices[iter->v2].z()));

                glNormal3f(normals[iter->n3].x(),normals[iter->n3].y(),normals[iter->n3].z());
                glVertexAttrib2f(texcoord, texCoords[iter->t3].x(),texCoords[iter->t3].y());
                glVertex3f(vertices[iter->v3].x(),meaning(skeleton,verticesNew,vertices[iter->v3].y()),meaning(skeleton,verticesNew,vertices[iter->v3].y(),vertices[iter->v3].z()));
            }
        }
        glEnd();

        glPopMatrix();
        glEndList();
    }
}

double Dragon::meaning(std::vector<QVector3D> skeleton,std::vector<QVector3D> verticesNew,float ytemp)
{
    double newY = 0;
    int i=-1;
    //double sk0 = (skeleton[0].y());
    double sk1 = (skeleton[1].y());
    double sk2 = (skeleton[2].y());
    double sk3 = (skeleton[3].y());
    double sk4 = (skeleton[4].y());
    double sk5 = (skeleton[5].y());

    if (ytemp>=sk1 && ytemp<sk2)
        i=1;
    if (ytemp>=sk2 && ytemp<sk3 )
        i=2;
    if (ytemp>=sk3 && ytemp<sk4 )
        i=3;
    if (ytemp>=sk4 && ytemp<sk5 )
        i=4;
    if (i!=-1)
    {
        if (skeleton[i].y()==verticesNew[i].y())
            return ytemp;
        double _y1 = skeleton[i].y();
        double _y2 = skeleton[i+1].y();

        double _y11 = verticesNew[i].y();
        double _y21 = verticesNew[i+1].y();

        double dy = _y2-_y1;

        double yofPoint = (_y2-ytemp)/dy;
        double dy1 = (_y21 - _y11)*yofPoint;
        double Ynew = _y21 -dy1;

        newY = Ynew;
    }

    return newY;

}

double Dragon::meaning(std::vector<QVector3D> skeleton,std::vector<QVector3D> verticesNew,float ytemp,float ztemp)
{
    double newY = 0;
    int i=-1;
    double sk1 = (skeleton[1].y());
    double sk2 = (skeleton[2].y());
    double sk3 = (skeleton[3].y());
    double sk4 = (skeleton[4].y());
    double sk5 = (skeleton[5].y());

    if (ytemp>=sk1 && ytemp<sk2)
        i=1;
    if (ytemp>=sk2 && ytemp<sk3 )
        i=2;
    if (ytemp>=sk3 && ytemp<sk4 )
        i=3;
    if (ytemp>=sk4 && ytemp<sk5 )
        i=4;
    if (i!=-1)
    {
        double _y1 = skeleton[i].z();
        double _y2 = skeleton[i+1].z();

        double _y11 = verticesNew[i].z();
        double _y21 = verticesNew[i+1].z();

        double dy = _y2-_y1;

        double yofPoint = (_y2-ztemp)/dy;
        double dy1 = (_y21 - _y11)*yofPoint;
        double Ynew = _y21 -dy1;

        newY = Ynew;
    }

    return newY;

}



// inherited from Renderable, should be edited
void Dragon::keyPressEvent(QKeyEvent* e, Viewer&)
{
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    if ((e->key()==Qt::Key_F) && (modifiers==Qt::NoButton))
    {
        toggleFire = true;
        std::cout << "Fire toggled" << std::endl;
    }
    /// ANIMATION
    else if (e->key()==Qt::Key_Space)
    {
        if (f){
            speed = 3;
            fall = true;
        }
        f=!f;
    }
    else if (e->key()==Qt::Key_Plus)
    {
        if (angleChange<0.5)
            angleChange*=1.1;

    }

    else if (e->key()==Qt::Key_R)
    {
        r=!r;
    }
    else if (e->key()==Qt::Key_Minus)
    {
        angleChange/=1.1;
    }
    else if (e->key()==Qt::Key_S)
    {

        s=!s;
    }
}

void Dragon::keyReleaseEvent(QKeyEvent* e, Viewer&)
{
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    if ((e->key()==Qt::Key_F) && (modifiers==Qt::NoButton))
    {
        toggleFire = false;
        std::cout << "Fire off" << std::endl;
        for(Particles* p : fireParticles)
        {
            p->setPosition(0,0,0);
        }
        fireParticlesEnabledCount = 0;
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
