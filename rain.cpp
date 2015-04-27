#include "rain.h"

typedef struct {
    // Life
    bool alive;	// is the particle alive?
    float life;	// particle lifespan
    float fade;   // decay
    // color
    float red;
    float green;
    float blue;
    // Position/direction
    float xpos;
    float ypos;
    float zpos;
    // Velocity/Direction, only goes down in y dir
    float vel;
    // Gravity
    float gravity;
}particles;


// Paticle System
particles par_sys[MAX_PARTICLES];

void Rain::init(Viewer&)
{
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        initParticles(loop);
    }
}

void Rain::draw()
{
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+2)
    {
        if (par_sys[loop].alive == true)
        {
            float x = par_sys[loop].xpos;
            float y = par_sys[loop].ypos;
            float z = par_sys[loop].zpos + zoom;

            // Draw particles
            glColor3f(0.5, 0.5, 1.0);
            glBegin(GL_LINES);
            glVertex3f(x, y, z);
            glVertex3f(x, y+0.5, z);
            glEnd();
        }
    }
}

void Rain::animate()
{
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+2)
    {
        if (par_sys[loop].alive == true) {

            // Update values
            //Move
            // Adjust slowdown for speed!
            //printf("%f ",par_sys[loop].ypos);
            par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);

            par_sys[loop].vel += par_sys[loop].gravity;
            // Decay
            par_sys[loop].life -= par_sys[loop].fade;

            if (par_sys[loop].ypos <= 0) {
                par_sys[loop].life = -1.0;
            }
            //Revive
            if (par_sys[loop].life < 0.0) {
                initParticles(loop);
            }
        }
    }
}


// Initialize/Reset Particles - give them their attributes
void Rain::initParticles(int i)
{
    par_sys[i].alive = true;
    par_sys[i].life = 1.0;
    par_sys[i].fade =float(rand()%100)/1000.0f+0.003f;
    //printf("%f",float(rand()%100)/1000.0f+0.003f);
    par_sys[i].xpos = (float) (rand() % 1000) - 500;

    par_sys[i].ypos = 1000.0;
    par_sys[i].zpos = (float) (rand() % 1000) - 500;

    par_sys[i].red = 0.5;
    par_sys[i].green = 0.5;
    par_sys[i].blue = 1.0;

    par_sys[i].vel = velocity;
    par_sys[i].gravity = -0.8;//-0.8;
}
