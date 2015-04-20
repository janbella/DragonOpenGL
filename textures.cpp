#include "textures.h"
#include "glCheck.h"

#include <QKeyEvent>

#include <iostream>
#include <cstdio>
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <QGLViewer/qglviewer.h>

Textures::Textures() :
    filteringMode( 0 ),
    mipmapFilteringMode( 0 ),
    show_mipmap_example(false)
{
}

void Textures::init(Viewer&)
{
    // load textures
    tex_grass = loadTexture("textures/grass.jpg");

    // TODO... YOU MAY ADD MORE HERE
    tex_crate = loadTexture("textures/crate.jpg");

    program.load("shaders/texture.vert", "shaders/texture.frag");
    // get the program id and use it to have access to uniforms
    GLint program_id = (GLint)program;
    GLCHECK(glUseProgram( program_id ) );
    // get uniform locations (see the fragment shader)
    GLCHECK(texture0 = glGetUniformLocation( program_id, "texture0"));
    // get vertex texture coordinate locations
    GLCHECK(texcoord0 = glGetAttribLocation( program_id, "texcoord0"));
    // tex0 on the sampler will use the texture unit #0
    GLCHECK(glUniform1i( texture0, 0 ) );

    // TODO... YOU MAY ADD MORE HERE
    GLCHECK(texture1 = glGetUniformLocation( program_id, "texture1"));
    GLCHECK(texcoord1 = glGetAttribLocation( program_id, "texcoord1"));
    GLCHECK(glUniform1i( texture1, 0 ) );

    // special mipmap example
    initMipmapExample();
}


void Textures::draw()
{
        // load the texture shader program: use this program instead of the fixed pipeline
        GLCHECK(glUseProgram( (GLint)program ));

    if (show_mipmap_example)
        drawMipmapExample();
    else
        drawGrassPlane(100.0);

    drawCrate(2.0);
    drawMultiTexturing();
    drawBillBoard();


    GLCHECK(glUseProgram( 0 )); //after this point, the fixed pipeline is in use
}


///////////////////////////////////////////////////////////////////////////////
GLuint Textures::loadTexture(const char *filename, bool mipmap)
{
    // generates an OpenGL texture id, and store it
    GLuint id;
    GLCHECK(glGenTextures(1, &id));

    // load a texture file as a QImage
    QImage img = QGLWidget::convertToGLFormat(QImage(filename));

    // specify the texture(2D texture, rgba, single file)
    GLCHECK(glBindTexture(GL_TEXTURE_2D, id));

    if (mipmap) {
        GLCHECK(gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.width(), img.height(),
                    GL_RGBA, GL_UNSIGNED_BYTE, img.bits()));
    }
    else {
        GLCHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, img.bits()));
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    return id;
}


///////////////////////////////////////////////////////////////////////////////
//   PLANE TEXTURE WITH GRASS
void Textures::drawGrassPlane(float s)
{
        // active texture unit is 0
    GLCHECK(glActiveTexture(GL_TEXTURE0));

    // bind the crate texture for texture unit 0
    GLCHECK(glBindTexture(GL_TEXTURE_2D, tex_grass));

    // set the texture sampler id in shader to active texture unit number
    GLCHECK(glUniform1i(texture0, 0));

    // set filtering accordingly
    setFiltering(filteringMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    // draw a plane
    drawPlane(s);
}


void Textures::drawPlane(float s)
{
    glNormal3f(0.0, 0.0, 1.0);
    float height = 0;

    glPushMatrix();
    glTranslatef(-s / 2.0, -s / 2.0, 0.0);

    // TODO... improve code for arbitrary scaling and texture tiling
    glBegin(GL_QUADS);
    glVertexAttrib2f(texcoord0, 0, 0);
    glVertex3f(0, 0, height);
    glVertexAttrib2f(texcoord0, 10, 0);
    glVertex3f(s, 0, height);
    glVertexAttrib2f(texcoord0, 10, 10);
    glVertex3f(s, s, height);
    glVertexAttrib2f(texcoord0, 0, 10);
    glVertex3f(0, s, height);
    glEnd();
    glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////
//   CRATE
void Textures::drawCrate(float size)
{
    // TODO - question 1.2
    // - load another texture, crate.tiff, in addition to grass.tiff
    //   (several methods/attributes should be modified)
    // - uncomment the following code, drawing a crate
    // - define the texture coordinates to map the crate texture
    //  texture on each face. Of course, the text must) be well oriented!


    GLCHECK(glActiveTexture(GL_TEXTURE0));

    // bind the crate texture for texture unit 0
    GLCHECK(glBindTexture(GL_TEXTURE_2D, tex_crate));

    // set the texture sampler id in shader to active texture unit number
    GLCHECK(glUniform1i(texture1, 0));

    // set filtering accordingly
    setFiltering(filteringMode);

    glBegin(GL_QUADS);

    glVertexAttrib2f(texcoord1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertexAttrib2f(texcoord1, 1, 0);
    glVertex3f(size, 0, 0);
    glVertexAttrib2f(texcoord1, 1, 1);
    glVertex3f(size, 0, size);
    glVertexAttrib2f(texcoord1, 0, 1);
    glVertex3f(0, 0, size);

    glVertexAttrib2f(texcoord1, 0, 0);
    glVertex3f(size, 0, 0);
    glVertexAttrib2f(texcoord1, 1, 0);
    glVertex3f(size, size, 0);
    glVertexAttrib2f(texcoord1, 1, 1);
    glVertex3f(size, size, size);
    glVertexAttrib2f(texcoord1, 0, 1);
    glVertex3f(size, 0, size);

    glVertexAttrib2f(texcoord1, 0, 0);
    glVertex3f(size, size, 0);
    glVertexAttrib2f(texcoord1, 1, 0);
    glVertex3f(0, size, 0);
    glVertexAttrib2f(texcoord1, 1, 1);
    glVertex3f(0, size, size);
    glVertexAttrib2f(texcoord1, 0, 1);
    glVertex3f(size, size, size);

    glVertexAttrib2f(texcoord1, 0, 0);
    glVertex3f(0, size, 0);
    glVertexAttrib2f(texcoord1, 1, 0);
    glVertex3f(0, 0, 0);
    glVertexAttrib2f(texcoord1, 1, 1);
    glVertex3f(0, 0, size);
    glVertexAttrib2f(texcoord1, 0, 1);
    glVertex3f(0, size, size);

    glVertexAttrib2f(texcoord1, 0, 0);
    glVertex3f(0, 0, size);
    glVertexAttrib2f(texcoord1, 1, 0);
    glVertex3f(size, 0, size);
    glVertexAttrib2f(texcoord1, 1, 1);
    glVertex3f(size, size, size);
    glVertexAttrib2f(texcoord1, 0, 1);
    glVertex3f(0, size, size);

    glEnd();

}

///////////////////////////////////////////////////////////////////////////////
//   BILLBOARDS
void Textures::drawBillBoard()
{
    // TODO...
}

///////////////////////////////////////////////////////////////////////////////
//   MULTI-TEXTURING
void Textures::drawMultiTexturing()
{
    // TODO...
}

///////////////////////////////////////////////////////////////////////////////
//   MIPMAP

void Textures::initMipmapExample()
{
    // a single texture object is created, but multiple images are loaded
    // for different resolutions.
    // Note: an image must be loaded for EACH level of resolution, until 1x1.
    // If one is missing, mipmapping will not work and the quad will appear
    // plain white...
    // In this case there is 9 images: 256x256, 128x128, ..., 2x2, 1x1

    // generates an OpenGL texture id
    GLuint id;
    glGenTextures(1, &id);
    tex_mipmap = id;

    glBindTexture(GL_TEXTURE_2D, tex_mipmap);

    // load images of different resolutions
    for (unsigned int i = 0; i <= 8; i++) {
        char filename[256];
        sprintf(filename, "images/mipmap%d.tiff", i);
        QImage img = QGLWidget::convertToGLFormat(QImage(filename));
        glTexImage2D(GL_TEXTURE_2D,
                i,			// level of the image
                GL_RGBA, img.width(), img.height(), 0,
                GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Textures::drawMipmapExample()
{
    // use the mipmap texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_mipmap);
    setFiltering(mipmapFilteringMode); // set the parameters for mipmapping

    // draw a plane
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertexAttrib2f(texcoord0, -3, -3);
    glVertex3f(-20, -20, 0);
    glVertexAttrib2f(texcoord0,  3, -3);
    glVertex3f(20,  -20, 0);
    glVertexAttrib2f(texcoord0,  3,  3);
    glVertex3f(20,   20, 0);
    glVertexAttrib2f(texcoord0, -3,  3);
    glVertex3f(-20,  20, 0);
    glEnd();
}

///////////////////////////////////////////////////////////////////////////////
// CONTROLS

// filteringMode (for GL_TEXTURE_MIN_FILTER) can be
//	GL_NEAREST, GL_LINEAR,
//	GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST,
//	GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR

void Textures::printFilteringMode(int mode)
{
    switch (mode) {
    case 0: std::cout << "GL_NEAREST"; break;
    case 1: std::cout << "GL_LINEAR"; break;
    case 2: std::cout << "GL_NEAREST_MIPMAP_NEAREST"; break;
    case 3: std::cout << "GL_LINEAR_MIPMAP_NEAREST"; break;
    case 4: std::cout << "GL_NEAREST_MIPMAP_LINEAR"; break;
    case 5: std::cout << "GL_LINEAR_MIPMAP_LINEAR"; break;
    default: std::cout << "GL_NEAREST" << std::endl;
    }
    std::cout << std::endl;
}

void Textures::toggleFiltering()
{
    filteringMode = ++(int&)filteringMode % 2;
    std::cout << "Filtering mode: ";
    printFilteringMode(filteringMode);
}

void Textures::toggleMipMapFiltering() {
    mipmapFilteringMode = ++(int&)mipmapFilteringMode % 6;
    std::cout << "Mipmap Filtering mode: ";
    printFilteringMode(mipmapFilteringMode);
}

void Textures::setFiltering(int mode)
{
    // MIN FILTER
    switch (mode) {
        case 0:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        case 1:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;
        case 2:
            // nearest ds les levels, puis nearest
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            break;
        case 3:
            // interp ds les levels, puis nearest
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            break;
        case 4:
            // nearest ds les levels, puis interpolation
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            break;
        case 5:
            // interp ds les levels, puis interpolation
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            break;
        default:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    // MAG FILTER
    switch (filteringMode) {
        case 0:
        case 2:
        case 4:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case 1:
        case 3:
        case 5:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }
}

void Textures::keyPressEvent(QKeyEvent *e, Viewer&)
{
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    // Toggle filtering modes to render the textures
    if ((e->key()==Qt::Key_F) && (modifiers==Qt::NoButton)) {
        toggleFiltering();
    } else if ((e->key()==Qt::Key_M) && (modifiers==Qt::NoButton)) {
        toggleMipMapFiltering();
    } else if ((e->key()==Qt::Key_E) && (modifiers==Qt::NoButton)) {
        show_mipmap_example = !show_mipmap_example;
    }
}
