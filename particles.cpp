#include "particles.h"
#include "texturingtools.h"
#include <cstdlib>

Particles::Particles(const char* texturePath, float ydistance, float xspread, float zspread, float scaleSize, bool fire)
    :filename(texturePath), ydistance(ydistance), xspread(xspread), zspread(zspread), scaleSize(scaleSize), fire(fire)
{

}

Particles::~Particles()
{

}

void Particles::animate()
{
    //std::cout << "Animate called" << std::endl;

    if(fire)
    {
        z =  z + (rand()%10) * xspread +0.3;
        y =  y + pow((-1),(rand()%2)+1) * (rand()%10) * zspread;
        x =  x + pow((-1),(rand()%2)+1) * (rand()%10) * xspread;

        if(z>ydistance)
        {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
    }
    else
    {
        x = x + pow((-1),(rand()%2)+1) * (rand()%10) * xspread;
        y -= 0.1;
        z = z + pow((-1),(rand()%2)+1) * (rand()%10) * zspread;

        if(y<-ydistance)
        {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
    }
}

void Particles::keyPressEvent(QKeyEvent*, Viewer&)
{

}

void Particles::mouseMoveEvent(QMouseEvent*, Viewer&)
{

}


void Particles::createDispList()
{
    partDispList = glGenLists(1);

    glNewList(partDispList,GL_COMPILE);

    glPushMatrix();
    glEnable ( GL_BLEND );
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);


    glBegin(GL_QUADS);

    // glNormal3f(1,0,0);

    glVertexAttrib2f(texCoords, 0,0);
    glVertex3f(-0.5,-0.5,0);

    glVertexAttrib2f(texCoords, 0,1);
    glVertex3f(-0.5,0.5,0);

    glVertexAttrib2f(texCoords, 1,1);
    glVertex3f(0.5,0.5,0);

    glVertexAttrib2f(texCoords, 1,0);
    glVertex3f(0.5,-0.5,0);

    glEnd();

    glRotatef(90,1,0,0);

    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    /* glBegin(GL_QUADS);
    glVertexAttrib2f(texCoords, 0,0);
    glVertex3f(-0.5,0,-0.5);

    glVertexAttrib2f(texCoords, 0,1);
    glVertex3f(-0.5,0,0.5);

    glVertexAttrib2f(texCoords, 1,1);
    glVertex3f(0.5,0,0.5);

    glVertexAttrib2f(texCoords, 1,0);
    glVertex3f(0.5,0,-0.5);

    glEnd();

    glRotatef(90,0,0,1);
glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
    glBegin(GL_QUADS);
    glVertexAttrib2f(texCoords, 0,0);
    glVertex3f(-0.5,0,-0.5);

    glVertexAttrib2f(texCoords, 0,1);
    glVertex3f(-0.5,0,0.5);

    glVertexAttrib2f(texCoords, 1,1);
    glVertex3f(0.5,0,0.5);

    glVertexAttrib2f(texCoords, 1,0);
    glVertex3f(0.5,0,-0.5);

    glEnd();*/

    glDisable ( GL_BLEND );


    glPopMatrix();
    glEndList();
}

void Particles::draw()
{
    if(!glIsList(partDispList))
    {
        createDispList();
        //loaded = true;
    }
    GLCHECK(glUseProgram( (GLint)program ));

    GLCHECK(glActiveTexture(GL_TEXTURE0));

    GLCHECK(glBindTexture(GL_TEXTURE_2D, textureId));

    GLCHECK(glUniform1i(texture, 0));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glPushMatrix();

    //if(!fire)
    {
        float modelview[16];
        int i,j;

        // save the current modelview matrix

        // get the current modelview matrix
        glGetFloatv(GL_MODELVIEW_MATRIX , modelview);


        // undo all rotations
        // beware all scaling is lost as well
        for( i=0; i<3; i++ )
            for( j=0; j<3; j++ ) {
                if ( i==j )
                    modelview[i*4+j] = 1.0;
                else
                    modelview[i*4+j] = 0.0;
            }

        // set the modelview with no rotations and scaling
        glLoadMatrixf(modelview);
    }

    glTranslatef(x,y,z);
    /*if(fire)
    {
        glRotatef(90,1,0,0);
    }*/
    glScalef(scaleSize,scaleSize,scaleSize);

    glCallList(partDispList);
    glPopMatrix();

    GLCHECK(glUseProgram( 0 ));
}

void Particles::init(Viewer&)
{
    Texturing::init(filename,&program,&textureId,&texture,&texCoords);
}

void Particles::setPosition(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
