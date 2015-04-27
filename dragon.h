#ifndef DRAGON_H
#define DRAGON_H

#include <list>
#include <GL/glew.h>
#include <GL/glut.h>

#include "renderable.h"
#include "shader.h"
#include "particles.h"

//#define USE_VBO

// the dragon model drawing and manipulating
class Dragon : public Renderable
{
public:
    Dragon();
    ~Dragon();

    void init(Viewer&);

    // inherited from Renderable, should be edited
    virtual void draw();

    // inherited from Renderable, should be edited
    virtual void animate();

    // inherited from Renderable, should be edited
    virtual void keyPressEvent(QKeyEvent*, Viewer&);

     // inherited from Renderable, should be edited
    virtual void mouseMoveEvent(QMouseEvent*, Viewer&);


private:
    //const std::string headObj = "models/???";
    //const std::string neckObj = "models/???";
    const std::string bodyObj = "models/better dragon/torso.obj";
    //const std::string tailObj = "models/???";
    const std::string leftWingObj = "models/better dragon/wing.obj";
    const std::string rightWingObj = "models/better dragon/right_wing.obj";
    const std::string leftFrontLegObj = "models/better dragon/leg_left.obj";
    const std::string rightFrontLegObj = "models/better dragon/leg.obj";
    const std::string leftBackLegObj = "models/better dragon/backleg_left.obj";
    const std::string rightBackLegObj = "models/better dragon/backleg.obj";

    const char* dragonTexture = "textures/Dragon_ground_color.jpg";

#define BODY 0
#define LEFTWING 1
#define RIGHTWING 2
#define LEFTFRONTLEG 3
#define RIGHTFRONTLEG 4
#define LEFTBACKLEG 5
#define RIGHTBACKLEG 6

unsigned int numVBO;

GLuint vertVBOIndex;
GLuint normVBOIndex;
GLuint texVBOIndex;

std::vector<unsigned int> numVBOitems;

GLuint dispListIndex;

void initDispLists();

void initVBOs();

GLuint loadTexture(const char *filename);

bool loaded = false;

const char* texturePath = "textures/Dragon_ground_color.jpg";

const char* smokeTex = "textures/smoke.png";
const char* fireTex = "textures/fire.png";

GLuint textureId;

// texture unit shader binding
GLint texture;

// texture coordinate bindings
GLint texcoord;

// shader program
ShaderProgram program;

float smokeParticlesEnabledCount = 0;
float fireParticlesEnabledCount = 0;

bool toggleFire = false;

// xyz give coordinates, w time to live
std::vector<Particles*> smokeParticles;
std::vector<Particles*> fireParticles;
};

#endif // DRAGON_H
