#ifndef RAIN_H
#define RAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "renderable.h"

class Rain : public Renderable
{
public:
void initParticles(int i);
void initRain();

virtual void init(Viewer&);
virtual void draw();
virtual void animate();

private:
#define MAX_PARTICLES 100000

#define RAIN	0
#define SNOW	1
#define	HAIL	2


float slowdown = 2.0;
float velocity = -10000.0;
float zoom = -40.0;
float pan = 1.0;
float tilt = 1.0;
float hailsize = 0.1;

int loop;
int fall;
};
#endif // RAIN_H
