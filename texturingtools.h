#ifndef TEXTURINGTOOLS
#define TEXTURINGTOOLS

#include <GL/glew.h>
#include <GL/glut.h>
#include <QImage>
#include <QGLViewer/qglviewer.h>

#include "glCheck.h"
#include "shader.h"

namespace Texturing
{


GLuint loadTexture(const char *filename);

void init(const char* textureFile, ShaderProgram* program, GLuint* textureId, GLint* texture, GLint* texcoord );


}

#endif // TEXTURINGTOOLS

