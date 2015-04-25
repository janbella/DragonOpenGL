#ifndef TEMPORARYDRAGON
#define TEMPORARYDRAGON

#include <list>
#include <GL/glew.h>
#include <GL/glut.h>

#include "renderable.h"
#include "objectloader.h"
#include "glCheck.h"

#include "shader.h"

// the dragon model drawing and manipulating
class TemporaryDragon : public Renderable
{
public:
    TemporaryDragon()
    {
        loaded = false;
    };

    void load()
    {
        dispListIndex = glGenLists(1);

        ObjectLoader objLoader(dragonOBJ);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex, texcoord);
        }
        loaded = true;
    }

    GLuint loadTexture(const char *filename)
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

    virtual void init(Viewer&)
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


    ~TemporaryDragon() {};

    // inherited from Renderable, should be edited
    virtual void draw()
    {
        if(!loaded) load();
        GLCHECK(glUseProgram( (GLint)program ));

        GLCHECK(glActiveTexture(GL_TEXTURE0));

        // bind the crate texture for texture unit 0
        GLCHECK(glBindTexture(GL_TEXTURE_2D, textureId));

        // set the texture sampler id in shader to active texture unit number
        GLCHECK(glUniform1i(texture, 0));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glPushMatrix();
            glCallList(dispListIndex);
        glPopMatrix();

        GLCHECK(glUseProgram( 0 ));

    };


private:

    const std::string dragonOBJ = "models/THE_BEAST.obj";
    const char* dragonTexture = "textures/Dragon_ground_color.jpg";

    GLuint dispListIndex;

    const char* texturePath = "textures/skybox.jpg";

    GLuint textureId;

    // texture unit shader binding
    GLint texture;

    // texture coordinate bindings
    GLint texcoord;

    // shader program
    ShaderProgram program;

    bool loaded = false;

    // load a single texture file to associate with a Textureid
};

#endif // TEMPORARYDRAGON

