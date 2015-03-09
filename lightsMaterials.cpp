# include "lightsMaterials.h"
# include "shader.h"
# include "material.h"
# include "light.h"

# ifndef __APPLE__
#   include <GL/glew.h>
#   include <GL/glut.h>
# else
#   include <GLUT/glut.h>
# endif


// init of colors
static const vec4 black( 0.0f, 0.0f, 0.0f, 1.0f );
static const vec4 white( 1.0f, 1.0f, 1.0f, 1.0f );
static const vec4 red( 1.0f, 0.0f, 0.0f, 1.0f );

// fields for materials
static vec4 mat_ambient( 0.7f, 0.7f, 0.7f, 1.0f );
static vec4 mat_ambient_color( 0.8f, 0.8f, 0.2f, 1.0f );
static vec4 mat_diffuse( 0.1f, 0.5f, 0.8f, 1.0f );
static float no_shininess( 0.0f );
static float low_shininess( 5.0f );
static float high_shininess( 50.0f );
static vec4 no_color = black;

static Material materials[ 9 ] = {
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
// static Light light( vec4( 0, 0, 1, 1 ), black, white, white );
static Light light_1( vec4( 0, 0, 1, 1 ), white, white, white );
static Light light_2( vec4( 0.0f, 0.0f, 3.0f, 1.0f ), white, red, white );

LightsMaterials::LightsMaterials()
{
}

void LightsMaterials::init(Viewer &v)
{
  (void)v;

  program.load("shaders/material.vert", "shaders/material.frag");
  GLCHECK( glUseProgram( program ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.la" ), 1, &light_1.la.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.ld" ), 1, &light_1.ld.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.ls" ), 1, &light_1.ls.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_1.position" ), 1, &light_1.position.x ) );

  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.la" ), 1, &light_2.la.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.ld" ), 1, &light_2.ld.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.ls" ), 1, &light_2.ls.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "light_2.position" ), 1, &light_2.position.x ) );


  GLCHECK( glUseProgram( 0 ) );

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
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &no_color.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &mat_diffuse.x ) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &no_color.x ) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), no_shininess ) );

  glTranslatef(-3.75F, 3.0f, 0.0f);
  glutSolidSphere(1.0f, 24, 24);

  // then add more and more shininess!
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &white.x ) );
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
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[0].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[0].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[0].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[0].shininess ) );
  glutSolidSphere(1.0f,24,24);
  glPopMatrix();
   
  glPushMatrix();
  glTranslatef(-1.25, 3.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[1].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[1].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[1].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[1].shininess ) );
  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.25, 3.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[2].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[2].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[2].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[2].shininess ) );
  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3.75, 0.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[3].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[3].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[3].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[3].shininess ) );
  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1.25f, 0.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[4].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[4].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[4].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[4].shininess ) );
  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.25, 0.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[5].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[5].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[5].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[5].shininess ) );
  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3.75f, -3.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[6].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[6].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[6].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[6].shininess ) );

  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1.25, -3.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[7].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[7].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[7].ks.x) );
  GLCHECK( glUniform1f( glGetUniformLocation( program, "material.shininess" ), materials[7].shininess ) );

  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.25, -3.0f, 0.0f);
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ka" ), 1, &materials[8].ka.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.kd" ), 1, &materials[8].kd.x) );
  GLCHECK( glUniform4fv( glGetUniformLocation( program, "material.ks" ), 1, &materials[8].ks.x) );
  GLCHECK( glUniform1f(  glGetUniformLocation( program, "material.shininess" ), materials[8].shininess ) );

  glutSolidSphere(1.0f, 24, 24);
  glPopMatrix();

  glPopMatrix();

  glUseProgram( 0 );
}
