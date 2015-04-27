#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/glew.h>

#include <QImage>
#include <QGLWidget>
#include <QVector4D>
#include <vector>

#include "geometryprimitives.h"
#include "objectloader.h"
#include "glCheck.h"
#include "shader.h"



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

    void setPosition(float x, float y, float z);

private:
    const char* filename = "textures/smoke.png";

    ShaderProgram program;

    GLuint textureId;
    GLint texture;
    GLint texCoords;

    bool loaded = false;

    GLuint partDispList;

    void createDispList();

    float x = 0;
    float y = 0;
    float z = 0;

    int id;
};

#endif // PARTICLES_H
