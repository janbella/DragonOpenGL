#ifndef SKYBOX_H
#define SKYBOX_H

#include <glew.h>
#include <glut.h>
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
    const char* texturePath;

    GLuint textureId;

    // texture unit shader binding
    GLint texture;

    // texture coordinate bindings
    GLint texcoord;

    // shader program
    ShaderProgram program;

    // load a single texture file to associate with a Textureid
    GLuint loadTexture(const char *filename);

    // draw a quad centered in the XY place (z=0), of size s
    void drawSkyboxCube(float size = 100.0);
};

#endif // SKYBOX_H
