#ifndef SCENE_H
#define SCENE_H

#include<GL/glew.h>
#include<GL/glut.h>
#include<QImage>
#include<QGLViewer/qglviewer.h>


#include "shader.h"
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

private:
    void drawGrassPlane(float s);
    void drawLake(float r,  float precision);
    void drawForest(int num_X, int num_Z);

    GLuint textureGrass;
    GLuint textureFlowers;
    GLuint textureTree;

    const char* textureGrassPath = "textures/grass.png";
    const char* textureFlowersPath = "textures/flowers.png";
    const char* textureTreePath = "textures/tree.png";

    // texture unit shader binding
    GLint texture0;
    GLint texture1;

    // texture coordinate bindings
    GLint texcoord0;
    GLint texcoord1;

    // shader program
    ShaderProgram textureShader;
    ShaderProgram materialShader;


};

#endif // SCENE_H
