#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <string>

#include "shader.h"

#include "renderable.h"


class Skybox : public Renderable
{
public:
    Skybox();
    ~Skybox();

    virtual void draw();
    virtual void init(Viewer&);


private:
    const char* texturePath = "textures/skybox.jpg";

    GLuint textureId;

    // texture unit shader binding
    GLint texture;

    // texture coordinate bindings
    GLint texcoord;

    // shader program
    ShaderProgram program;

    // draw a quad centered in the XY place (z=0), of size s
    void drawSkyboxCube(float size = 1000.0);
};

#endif // SKYBOX_H
