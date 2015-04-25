#ifndef DRAGON_H
#define DRAGON_H

#include <list>
#include <GL/glew.h>
#include <GL/glut.h>

#include "renderable.h"

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
    const std::string bodyObj = "models/dragon_torso.obj";
    //const std::string tailObj = "models/???";
    const std::string leftWingObj = "models/left_wing.obj";
    const std::string rightWingObj = "models/wing_right.obj";
    const std::string leftFrontLegObj = "models/left_front_better.obj";
    const std::string rightFrontLegObj = "models/right_front_better.obj";
    const std::string leftBackLegObj = "models/back_left.obj";
    const std::string rightBackLegObj = "models/easyleg.obj";

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
};

#endif // DRAGON_H
