#ifndef _CUBE_
#define _CUBE_

#include "renderable.h"
#include <GL/glut.h>

class Cube : public Renderable
{
public:
	void draw();

private:
	void drawImmediate();
	void drawElements();
	void drawArrays();
};

#endif

