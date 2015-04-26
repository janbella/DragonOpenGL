#ifndef PARTICLES_H
#define PARTICLES_H

#include "dragon.h"
#include "geometryprimitives.h"
#include "objectloader.h"
#include "glCheck.h"
#include "shader.h"

#include <QImage>
#include <QGLWidget>

class Particles : public Renderable
{
public:
    Particles();
    ~Particles();

    virtual void init(Viewer&);

    virtual void draw() ;

    virtual void animate();

    virtual void keyPressEvent(QKeyEvent*, Viewer&);

    virtual void mouseMoveEvent(QMouseEvent*, Viewer&);

private:
    const char* filename = "textures/tree.png";

    ShaderProgram program;

    GLuint textureId;
    GLint texture;
    GLint texCoords;

    bool loaded = false;

    GLuint partDispList;

    void createDispList();
};

#endif // PARTICLES_H
