# include "lightsMaterials.h"
# include "shader.h"
# include "material.h"
# include "light.h"

# ifndef __APPLE__
#   include <glew.h>
#   include <glut.h>
# else
#   include <glut.h>
# endif

// colour constants
static const Vector4 black( 0.0f, 0.0f, 0.0f, 1.0f );  // black colour
static const Vector4 white( 1.0f, 1.0f, 1.0f, 1.0f );  // white colour
static const Vector4 red( 1.0f, 0.0f, 0.0f, 1.0f );    // red colour

// fields for materials
static Vector4 mat_ambient( 0.7f, 0.7f, 0.7f, 1.0f );  // ambient material
static Vector4 mat_ambient_color( 0.8f, 0.8f, 0.2f, 1.0f );
static Vector4 mat_diffuse( 0.1f, 0.5f, 0.8f, 1.0f );

static float no_shininess( 0.0f );
static float low_shininess( 5.0f );
static float high_shininess( 50.0f );

static Vector4 no_color = black;

static Material materials[9] =
{
    Material(         no_color, mat_diffuse, no_color,  no_shininess),
    Material(         no_color, mat_diffuse, white   , low_shininess),
    Material(         no_color, mat_diffuse, white   ,high_shininess),
    Material(      mat_ambient, mat_diffuse, no_color,  no_shininess),
    Material(      mat_ambient, mat_diffuse,    white, low_shininess),
    Material(      mat_ambient, mat_diffuse,    white,high_shininess),
    Material(mat_ambient_color, mat_diffuse, no_color,  no_shininess),
    Material(mat_ambient_color, mat_diffuse,    white, low_shininess),
    Material(mat_ambient_color, mat_diffuse,    white,high_shininess),
};


// light used to render the balls:
// directional light (4th parameter w=0), coming along +z axis
static Light light(   Vector4( 0, 0, 1, 1 ), black, white, white );
static Light light_1( Vector4( 0, 0, 1, 1 ), white, white, white );
static Light light_2( Vector4( 0.0f, 0.0f, 0.0f, 1.0f ), black, red, red );

LightsMaterials::LightsMaterials()
{
}

void LightsMaterials::init(Viewer &v)
{
/*
////    (void)v; для верности  ^^
*/
    program.load("shaders/material.vert", "shaders/material.frag");
    GLCHECK( glUseProgram( program ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.ambient"  ), 1, &light_1.ambient.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.diffuse"  ), 1, &light_1.diffuse.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.specular" ), 1, &light_1.specular.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.position" ), 1, &light_1.position.x ) );

    GLCHECK( glUniform1i ( glGetUniformLocation( program, "enabled_light2"   ), true));
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.ambient"  ), 1, &light_2.ambient.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.diffuse"  ), 1, &light_2.diffuse.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.specular" ), 1, &light_2.specular.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.position" ), 1, &light_2.position.x ) );


    GLCHECK( glUseProgram(0));

    // ==== SET UP LIGHTS
    glEnable(GL_LIGHTING);
    // disable the default qglviewer light !!
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glClearColor(0.0f, 0.1f, 0.1f, 0.0f);
}

void LightsMaterials::draw()
{
    // ==== PLACE LIGHTS
    // Most set up are in the init() method.
    // However, lights defined in the scene referentiel must be positionned
    // at each draw() invocation.

    GLCHECK( glUseProgram( program ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.position" ), 1, &light_1.position.x ) );

    GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.position" ), 1, &light_2.position.x ) );

    // TODO ?
    //  1. animated light: change the position at each draw?
    exampleMaterial();
    GLCHECK( glUseProgram( 0 ) );
}


void LightsMaterials::exampleMaterial()
{
    // === CREATE SPHERES WITH DIFFERENT MATERIALS
    // Exemple adapted from the OpenGL Programming Guide (The Red Book)
    // Note that since OpenGL is a state machine, some glMaterial* calls
    // are only here for clarity.

    glDisable(GL_COLOR_MATERIAL);  // MANDATORY to use glMaterial!!


    // First line of spheres
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);


    // let's start with just diffuse light only
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &no_color.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &mat_diffuse.x ) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &no_color.x ) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), no_shininess ) );

    glTranslatef(-3.75f, 3.0f, 0.0f);
    glutSolidSphere(1.0f, 24, 24);

    // then add more and more shininess!
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &white.x ) );
    GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), low_shininess ) );
    glTranslatef(2.5f, 0.0f, 0.0f);
    glutSolidSphere(1.0f, 24, 24);

    GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), high_shininess ) );
    glTranslatef(2.5f, 0.0f, 0.0f);
    glutSolidSphere(1.0f, 24, 24);

    // suppress shininess and add emission light
    glPopMatrix();



    glPushMatrix();
    glPushMatrix();
    glTranslatef(-3.75F, 3.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[0].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[0].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[0].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[0].shininess ) );
    glutSolidSphere(1.0f,24,24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25, 3.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[1].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[1].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[1].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[1].shininess ) );
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, 3.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[2].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[2].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[2].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[2].shininess ) );
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.75, 0.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[3].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[3].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[3].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[3].shininess ) );
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25f, 0.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[4].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[4].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[4].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[4].shininess ) );
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, 0.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[5].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[5].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[5].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[5].shininess ) );
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.75f, -3.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[6].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[6].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[6].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[6].shininess ) );

    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25, -3.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[7].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[7].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[7].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[7].shininess ) );

    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, -3.0f, 0.0f);
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1, &materials[8].ambient.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1, &materials[8].diffuse.x) );
    GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1, &materials[8].specular.x) );
    GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[8].shininess ) );

    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPopMatrix();

    glUseProgram( 0 );
}
