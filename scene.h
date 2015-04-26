#ifndef SCENE_H
#define SCENE_H

#include "renderable.h"

class Scene : public Renderable
{
public:
    Scene();
    ~Scene();

    virtual void init(Viewer&);


    virtual void draw() ;


    virtual void animate() ;


    virtual void keyPressEvent(QKeyEvent*, Viewer&);


    virtual void mouseMoveEvent(QMouseEvent*, Viewer&);
};

#endif // SCENE_H
