#ifndef SCENE_H
#define SCENE_H

#include<GL/glew.h>
#include<GL/glut.h>
#include<QImage>
#include<QGLViewer/qglviewer.h>


#include "shader.h"
#include "renderable.h"
#include "light.h"
#include "material.h"
#include "vector4.h"
#include "rain.h"



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

    // colour constants
    const  Vector4 black = Vector4( 0.0f, 0.0f, 0.0f, 1.0f );  // black colour
    const  Vector4 white = Vector4( 1.0f, 1.0f, 1.0f, 1.0f );  // white colour
    const  Vector4 red = Vector4( 1.0f, 0.0f, 0.0f, 1.0f );    // red colour

    Light light_1 = Light( Vector4( 000, 300, 000, 1 ), white, white, white );
    Light light_2 = Light( Vector4( 0.0f, 0.0f, 0.0f, 1.0f ), black, red, red );

    // fields for materials
    const Vector4 mat_ambient = Vector4( 0.7f, 0.7f, 0.7f, 1.0f );  // ambient material
    const Vector4 mat_diffuse = Vector4( 0.2f, 0.2f, 0.8f, 1.0f );

    const float no_shininess = ( 0.0f );
    const float low_shininess = ( 5.0f );
    const float high_shininess = ( 50.0f );

    const Material waterMaterial = Material(mat_ambient, mat_diffuse, white, high_shininess);

    Rain rain;
};

#endif // SCENE_H
