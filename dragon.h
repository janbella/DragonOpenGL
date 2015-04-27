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

    virtual void keyReleaseEvent(QKeyEvent*, Viewer&);

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

#define BODY 5
#define LEFTWING 4
#define RIGHTWING 6
#define LEFTFRONTLEG 3
#define RIGHTFRONTLEG 2
#define LEFTBACKLEG 1
#define RIGHTBACKLEG 0

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

/// FOR ANIMATION
double go = 0;
int timer;
int counter = -50;
double testscale = 1;
double angle = 0.0;
double angle_ = 0.0;
double angleChange = 0.2;
bool increase = false;
bool up = false;
bool up_ = false;
double flight = 0.0;
double shift = 0.0;
double speed = 2.0;
bool r = false;
bool f = false;
bool fall = false;
bool s = false;
int step  = 0;

GLuint changedDispListId = 0;

const std::string cylinder = "models/backleg_skeleton.obj";
const std::string cylinder2 = "models/backleg_left_skeleton.obj";

double meaning(std::vector<QVector3D> skeleton,std::vector<QVector3D> verticesNew,float ytemp);

double meaning(std::vector<QVector3D> skeleton,std::vector<QVector3D> verticesNew,float ytemp,float ztemp);

};

#endif // DRAGON_H
